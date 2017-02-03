#include <types.h>
#include <lib.h>
#include <synchprobs.h>
#include <synch.h>
#include <opt-A1.h>

bool allowed(Direction origin, Direction destination);

static volatile int nw = 0;
static volatile int ne = 0;
static volatile int ns = 0;
static volatile int wn = 0;
static volatile int ws = 0;
static volatile int we = 0;
static volatile int en = 0;
static volatile int es = 0;
static volatile int ew = 0;
static volatile int sw = 0;
static volatile int se = 0;
static volatile int sn = 0;

/*
 * This simple default synchronization mechanism allows only vehicle at a time
 * into the intersection.   The intersectionSem is used as a a lock.
 * We use a semaphore rather than a lock so that this code will work even
 * before locks are implemented.
 */

/*
 * Replace this default synchronization mechanism with your own (better) mechanism
 * needed for your solution.   Your mechanism may use any of the available synchronzation
 * primitives, e.g., semaphores, locks, condition variables.   You are also free to
 * declare other global variables if your solution requires them.
 */

/*
 * replace this with declarations of any synchronization and other variables you need here
 */
static struct cv *maCv;
static struct lock *maLock;

/*
 * The simulation driver will call this function once before starting
 * the simulation
 *
 * You can use it to initialize synchronization and other variables.
 *
 */
void
intersection_sync_init(void)
{
  maCv = cv_create("maCv");
  if (maCv == NULL) {
    panic("could not create cv");
  }
  maLock = lock_create("maLock");
  if (maLock == NULL) {
    panic("could not create lock");
  }
  return;
}

/*
 * The simulation driver will call this function once after
 * the simulation has finished
 *
 * You can use it to clean up any synchronization and other variables.
 *
 */
void
intersection_sync_cleanup(void)
{
  KASSERT(maCv != NULL);
  cv_destroy(maCv);
  KASSERT(maLock != NULL);
  lock_destroy(maLock);
}


/*
 * The simulation driver will call this function each time a vehicle
 * tries to enter the intersection, before it enters.
 * This function should cause the calling simulation thread
 * to block until it is OK for the vehicle to enter the intersection.
 *
 * parameters:
 *    * origin: the Direction from which the vehicle is arriving
 *    * destination: the Direction in which the vehicle is trying to go
 *
 * return value: none
 */
bool allowed(Direction origin, Direction destination)
{
    if(origin == 0)//N
    {
        if(destination == 3)//NW
        {
          if(ew != 0 || sw != 0)
              return false;
          else
              nw++;
        }
        else if(destination == 2)//NS
        {
          if(wn != 0 || ws != 0 || we != 0 || es != 0 || ew != 0 || sw != 0)
              return false;
          else
              ns++;
        }
        else//NE
        {
          if(wn != 0 || we != 0 || es != 0 || ew != 0 || sn != 0 || sw != 0 || se != 0)
              return false;
          else
              ne++;
        }
    }
    else if(origin == 1)//E
    {
      if(destination == 0)//EN
      {
        if(wn != 0 || sn != 0)
            return false;
        else
            en++;
      }
      else if(destination == 2)//ES
      {
        if(ne != 0 || ns != 0 || wn != 0 || ws != 0 || we != 0 || sn != 0 || sw != 0)
            return false;
        else
            es++;
      }
      else//3 EW
      {
        if(ne != 0 || nw!=0 || ns != 0 || wn != 0 || sn != 0 || sw != 0)
            return false;
        else
            ew++;
      }
    }

    else if(origin == 2)//S
    {
        if(destination == 0)//SN
        {
          if(ne != 0 || wn != 0 || we != 0 || en != 0 || es != 0 || ew != 0)
              return false;
          else
              sn++;
        }
        else if(destination == 1)//SE
        {
          if(ne != 0 || we != 0)
              return false;
          else
              se++;
        }
        else//3 SW
        {
          if(nw != 0 || ne != 0 || ns != 0 || wn != 0 || we != 0 || es != 0 || ew != 0)
              return false;
          else
              sw++;
        }
    }
    else //W
    {
        if(destination == 0)//WN
        {
          if(ne != 0 || en != 0 || es != 0 || ew != 0 || sn != 0 || sw != 0)
              return false;
          else
              wn++;
        }
        else if(destination == 1)//WE
        {
          if(nw != 0 || ne != 0 || ns != 0 || es != 0 || sn != 0 || sw != 0)
              return false;
          else
              we++;
        }
        else//2 WS
        {
          if(ns != 0 || es != 0)
              return false;
          else
              ws++;
        }
    }
    return true;
}

void
intersection_before_entry(Direction origin, Direction destination)
{
  /* replace this default implementation with your own implementation */
KASSERT(maLock != NULL);
lock_acquire(maLock);
  while(allowed(origin, destination) == false)
  {
      cv_wait(maCv, maLock);
  }
  cv_signal(maCv, maLock);


  lock_release(maLock);
}


/*
 * The simulation driver will call this function each time a vehicle
 * leaves the intersection.
 *
 * parameters:
 *    * origin: the Direction from which the vehicle arrived
 *    * destination: the Direction in which the vehicle is going
 *
 * return value: none
 */

void
intersection_after_exit(Direction origin, Direction destination)
{
  KASSERT(maLock != NULL);
  lock_acquire(maLock);
  /* replace this default implementation with your own implementation */
  if(origin == 0)//N
  {
      if(destination == 1)//NE
          ne--;
      else if(destination == 2)//NS
          ns--;
      else//3 NW
          nw--;
  cv_signal(maCv, maLock);
  }
  else if(origin == 1)//E
  {
      if(destination == 0)//EN
          en--;
      else if(destination == 2)//ES
          es--;
      else//3 EW
          ew--;
  cv_signal(maCv, maLock);
  }
  else if(origin == 2)//S
  {
      if(destination == 0)//SN
          sn--;
      else if(destination == 1)//SE
          se--;
      else//3 SW
          sw--;
  cv_signal(maCv, maLock);
  }
  else//(origin == 3)W
  {
      if(destination == 0)//WN
          wn--;
      else if(destination == 1)//WE
          we--;
      else//2 WS
          ws--;

  cv_signal(maCv, maLock);
  }

  lock_release(maLock);
}
