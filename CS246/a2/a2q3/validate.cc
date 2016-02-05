#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>

using namespace std;

int counter=1; // determain which info are we cin currently
int n=0; // # of trans are made
struct Trade
{
  string name; //name

  string cardNum; //cardNum

  int expiryMonth; //expiryMonth
  int expiryYear; //expiryYear
  int transactionNum; //transactionNum
  int date; //date
  int month; //month
  int year; //year
  int hour; //hour
  int minute; //minute
  string amount; //amount

  string valid; //valid
};//structure record transcation information

/*********** main *************
     Purpose: This function is the main function it does anything
     Returns: STATE
************************************/
int main()
{
  Trade *myTrade=new Trade[500];
  string s;
  int t;
  getline(cin,s);
  while(!cin.eof())
  {
    if(counter==1)
    {
      myTrade->name = s;
      counter++;//set the counter to read card number
      n++;
    }//read name
    else if(counter==2)
    {
      myTrade->cardNum=s;
      counter++;//set the counter to read other information
    }//read card Number
    else
    {
      int time;
      stringstream tmp(s);
      tmp >> myTrade->expiryMonth >> myTrade->expiryYear >> myTrade->transactionNum >> myTrade->date >> myTrade->month >> myTrade->year >> time >> myTrade->amount;
      myTrade->hour = time/100;//hour
      myTrade->minute = time%100;//minute
      if(myTrade->cardNum[0]!='4')
        myTrade->valid="invalid";//if the card number is not begin with 4, invalid
      else if(myTrade->cardNum.length() == 13 || myTrade->cardNum.length() == 16)
      {
        int countUp=0;//total count up of a card number
        int length=myTrade->cardNum.length();//the length of the card number
        for(int j=0; j<length; j+=1)
        {
          int cc=myTrade->cardNum[j]-48;//convert char to int
          if((j%2==0 && length%2==1) || (j%2!=0 && length%2==0))
            countUp+=cc;//add the digit up
          else
          {
            cc*=2;
            if(cc>9)
              cc-=9;
            countUp+=cc;
          }//add the digit times 2 up
        }
        if(countUp%10==0)
          myTrade->valid="valid";//if the add up of the card number can be divide by 10, valid
        else
          myTrade->valid="invalid";//if the add up of the card number can't divide by 10, invalid
      }
      else
        myTrade->valid="invalid";//if the card number is not either 13 or 16 digits, invalid
      myTrade++;
      counter=1;//reset the counter to read name
    }//read other information
    getline(cin,s);
  }
  myTrade-=n;//set the pointer to where it begins
//start print
  for(int i=0; i<n; i++)
  {
    cout << setfill('0') << setw(5) << myTrade->transactionNum << " ";
    cout << setfill('0') << setw(2) << myTrade->date << "/" << setfill('0') << setw(2) << myTrade->month << "/" << myTrade->year << " ";
    cout << setfill('0') << setw(2) << myTrade->hour << ":" << setfill('0') << setw(2) << myTrade->minute << " ";
    cout << "$" << myTrade->amount << " ";
    cout << "(" << myTrade->cardNum << ", " << myTrade->name << ", " << setfill('0') << setw(2) << myTrade->expiryMonth << "/" << myTrade->expiryYear << ") ";
    cout << myTrade->valid << endl;
    myTrade++;
  }
  myTrade-=n;//set the pointer to where it begins
  delete [] myTrade;//delete the struct array
}

