#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
using namespace std;

const int maxCandidate=10;//# of candidate max
int candidate=0;//# of candidate we count
string nameList[maxCandidate];//candidate name list
int voteList[maxCandidate];//vote list
int total=0;//total vote
int valid=0;//valid vote
int spoilt=0;//spoilt vote
int voteNow=0;//a boolean tells we done with names lets begin with count votes

/*********** checkVote *************
     Purpose: This function checks if the vote is valid or not
     Returns: This function returns nothing but will change global variables which counts votes
************************************/
void checkVote(string ticket)
{
  stringstream maStringStream(ticket);
  int n;//temp int to check if the vote is valid or not
  while(maStringStream >> n)
  {
    if((n<1) || (n>candidate))
      spoilt++;
    else
    {
      valid++;
      voteList[n-1]++;
    }
    total++;
  }
}
/*********** addCandidate **********
     Purpose: This function consume a string which is candidate's name and we store it in the name list
     Returns: This function returns nothing but will change global variable which is the name list
************************************/
void addCandidate(string name)
{
  if(candidate<10)
  {
    nameList[candidate]=name;
    candidate++;
  }
}
/*********** nameOrVote ************
     Purpose: This function consume a string and check if its a candidate name or vote
     Returns: This function returns nothing but will call vote/name function
************************************/
void nameOrVote(string line)
{
   stringstream maStringStream(line);
   int n;//temp int to check if the line is a vote or string
   if(voteNow==1)
     checkVote(line);
   else
   {
     if(maStringStream >> n)
     {
       checkVote(line);
       voteNow=1;
     }
     else
       addCandidate(line);
   }
}
/*********** readVotes *************
     Purpose: This function read inputs and call nameOrVote to let it decide whatever its a name or vote
     Returns: This function returns nothing
************************************/
void readVotes()
{
  string s;
  getline(cin,s);
  while(!cin.eof())
  {
    nameOrVote(s);
    getline(cin,s);
  }
}
/*********** printResults **********
     Purpose: This function print all the information we get from cin and count
     Returns: This function returns nothing
************************************/
void printResults()
{
  cout << "Number of voters: " << total << endl;
  cout << "Number of valid votes: " << valid << endl;
  cout << "Number of spoilt votes: " << spoilt << endl << endl;

  cout << left << setw(15) << "Candidate" << right << setw(3) << "Score" << endl << endl;
  for(int i=0; i<candidate; i++)
  {
    cout << left << setw(15) << nameList[i] << right << setw(3) << voteList[i] << endl;
  }
}
/*********** main ******************
     Purpose: Main 
     Returns: state
************************************/
int main()
{
  readVotes();
  printResults();
  return 0;
}
