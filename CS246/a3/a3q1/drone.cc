#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <cassert>
#include <cstdlib>
#include "drone.h"

//see header file
Drone::Drone()
{
	this->currentPos.ew=0;
	this->currentPos.ns=0;
	this->fx=0;
	this->fy=1;
	this->step=0;
}

//see header file
void Drone::forward()
{
	this->allPos[this->step].ew = this->currentPos.ew;
	this->allPos[this->step].ns = this->currentPos.ns;
	this->currentPos.ew += this->fx;
        this->currentPos.ns += this->fy;
	this->step++;
}

//see header file
void Drone::backward()
{
	this->allPos[this->step].ew = this->currentPos.ew;
        this->allPos[this->step].ns = this->currentPos.ns;
        this->currentPos.ew -= this->fx;
        this->currentPos.ns -= this->fy;
	this->step++;
}

//see header file
void Drone::left()
{
	if(this->fx==0)
	{
		if(this->fy==1) //face to north
		{
			this->fx=-1;
			this->fy=0;
		}
		else //face to south
		{
                        this->fx=1;
                        this->fy=0;
		}
	}
	else
	{
		if(this->fx==1) //face to east
                {
                        this->fx=0;
                        this->fy=1;
                }
		else //face to west
                {
                        this->fx=0;
                        this->fy=-1;
                }
	}
}

//see header file
void Drone::right()
{
        if(this->fx==0)
        {
                if(this->fy==1) //face to north
                {
                        this->fx=1;
                        this->fy=0;
                }
                else //face to south
                {
                        this->fx=-1;
                        this->fy=0;
                }
        }
        else 
	{
		if(this->fx==1) //face to east
       		{
			this->fx=0;
			this->fy=-1;
		}
		else //face to west
		{
			this->fx=0;
			this->fy=1;
		}
	}
}

//see header file
Position Drone::current()
{
	return this->currentPos;
}

//see header file
int Drone::totalDistance()
{
	return this->step;
}

//see header file
int Drone::manhattanDistance()
{
	return (((this->currentPos.ns > 0) ? this->currentPos.ns : (this->currentPos.ns * -1)) + ((this->currentPos.ew > 0) ? this->currentPos.ew : (this->currentPos.ew * -1)));
}

//see header file
bool Drone::repeated()
{
	for(int i=0; i<step; i++)
	{
		if((this->allPos[i].ew == this->currentPos.ew) && (this->allPos[i].ns == this->currentPos.ns))
			return true;
	}
	return false;
}
