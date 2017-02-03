#include <types.h>
#include <kern/errno.h>
#include <kern/unistd.h>
#include <kern/wait.h>
#include <lib.h>
#include <syscall.h>
#include <current.h>
#include <proc.h>
#include <thread.h>
#include <addrspace.h>
#include <copyinout.h>

#include "opt-A2.h"
#include <mips/trapframe.h>
#include <vfs.h>
#include <kern/fcntl.h>
#include <test.h>

  /* this implementation of sys__exit does not do anything with the exit code */
  /* this needs to be fixed to get exit() and waitpid() working properly */

void sys__exit(int exitcode) {

  struct addrspace *as;
  struct proc *p = curproc;
  /* for now, just include this to keep the compiler from complaining about
     an unused variable */
  (void)exitcode;

  DEBUG(DB_SYSCALL,"Syscall: _exit(%d)\n",exitcode);

  KASSERT(curproc->p_addrspace != NULL);
  as_deactivate();
  /*
   * clear p_addrspace before calling as_destroy. Otherwise if
   * as_destroy sleeps (which is quite possible) when we
   * come back we'll be calling as_activate on a
   * half-destroyed address space. This tends to be
   * messily fatal.
   */
  as = curproc_setas(NULL);
  as_destroy(as);



#if OPT_A2
  struct proc * cp = curproc;
  struct proc * temp;

lock_acquire(pidTableLock);
  for(unsigned int i = 0; i < processTable->num; i++)
  {
      temp = array_get(processTable, i);
      if(temp != NULL && temp->parent_pid == cp->pid)
      {
          if(temp->exitState == true) // those child process will be destory
          {
              proc_destroy(temp);
          }
          else // parent will free the children
          {
              temp->parent_pid = -1;
          }
      }
  }
lock_release(pidTableLock);


  proc_remthread(curthread);
  if(cp->parent_pid == -1)
  {
      //父母双亡 直接走
      proc_destroy(p);
  }
  else
  {
      //父母健在 wocao
      cp->exitState = true;
      cp->exitCode = _MKWAIT_EXIT(exitcode);

      lock_acquire(cp->sleepLk);
          cv_signal(cp->sleepCv, cp->sleepLk);
      lock_release(cp->sleepLk);
  }
#else
  /* detach this thread from its process */
  /* note: curproc cannot be used after this call */
  proc_remthread(curthread);

  /* if this is the last user process in the system, proc_destroy()
     will wake up the kernel menu thread */
  proc_destroy(p);
#endif


  thread_exit();
  /* thread_exit() does not return, so we should never get here */
  panic("return from thread_exit in sys_exit\n");
}


/* stub handler for getpid() system call                */
int
sys_getpid(pid_t *retval)
{
  #if OPT_A2
    struct proc *p = curproc;
    *retval = p->pid;
  #else
    *retval = 1;
  #endif

  return(0);
}

/* stub handler for waitpid() system call                */

int
sys_waitpid(pid_t pid,
	    userptr_t status,
	    int options,
	    pid_t *retval)
{
  int exitstatus;
  int result;

  /* this is just a stub implementation that always reports an
     exit status of 0, regardless of the actual exit status of
     the specified process.
     In fact, this will return 0 even if the specified process
     is still running, and even if it never existed in the first place.

     Fix this!
  */

  if (options != 0) {
    return(EINVAL);
  }

  #if OPT_A2
    struct proc * child_process;
    lock_acquire(pidTableLock);
      child_process = array_get(processTable, pid - PID_MIN);
    lock_release(pidTableLock);
    if(child_process == NULL)
    {
        return ESRCH;
    }

    lock_acquire(child_process->sleepLk);
        if(child_process->exitState == false)
        {
            cv_wait(child_process->sleepCv, child_process->sleepLk);
        }
        exitstatus = child_process->exitCode;
    lock_release(child_process->sleepLk);
  #else
    /* for now, just pretend the exitstatus is 0 */
    exitstatus = 0;
  #endif

  result = copyout((void *)&exitstatus,status,sizeof(int));
  if (result) {
    return(result);
  }
  *retval = pid;
  return(0);
}

#if OPT_A2

int sys_fork(struct trapframe * parent_trapframe, pid_t * retval)
{
  int result;
  struct proc *cp = curproc;
  struct thread *ct = curthread;

  //Create process structure for child process
  struct proc * child_process;
  child_process = proc_create_runprogram(cp->p_name);

  //Create and copy address space
  struct addrspace * child_addrspace;
  result = as_copy(cp->p_addrspace, &child_addrspace);
  if(result)
  {
    proc_destroy(child_process);
    return result;
  }
  child_process->p_addrspace = child_addrspace;

  //Create the parent/child relationship
  child_process->parent_pid = cp->pid;

  //pass the trapframe to the child thread
  struct trapframe * child_trapframe;
  child_trapframe = kmalloc(sizeof(struct trapframe));
  memcpy(child_trapframe, parent_trapframe, sizeof(struct trapframe));

  //Create thread for child process
  result = thread_fork(ct->t_name, child_process, (void *)enter_forked_process, child_trapframe, 0);
  if(result)
  {
    kfree(child_addrspace);
    proc_destroy(child_process);
    return result;
  }

  *retval = child_process->pid;
  return 0;
}

int sys_execv(userptr_t progname, userptr_t args)
{
  char * name;
  name = (char *)progname;
  char ** arguments;
  arguments = (char **)args;

  int nargs = 0;
  while(arguments[nargs] != NULL)
  {
    nargs++;
  }
  char * kernelArguments[nargs];

  for(int i=0; i<nargs; i++)
  {
      int length = strlen(arguments[i]) + 1;
      kernelArguments[i] = kmalloc(sizeof(char) * length);
      copyin((const_userptr_t)arguments[i], (void *)kernelArguments[i], length);
  }

  runprogram(name, nargs, kernelArguments);

  return 1;
}

#endif
