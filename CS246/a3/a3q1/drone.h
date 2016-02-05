#ifndef __DRONE_H__
#define __DRONE_H__

struct Position
{
	int ew;//x index
	int ns;//y index
};

struct Drone
{
/*************** Drone **************
     Purpose: Constructor of Drone
     Returns: Constructor returns nothing
     Error: None
************************************/
	Drone();
	Position currentPos;//current position
	Position allPos[50];//passed position
	int fx;//forward change in x
	int fy;//forward change in y
	int step;//how many steps drone take already

/************* forward *************
     Purpose: This function moves the drone one unit forward
     Returns: None
     Error: None
************************************/
	void forward();
/*************** backward **************
     Purpose: This function moves the drone one unit backward
     Returns: None
     Error: None
************************************/
	void backward();
/************** left ***************
     Purpose: This function turns the drone 90 degrees to the left, while remaining in the same location
     Returns: None
     Error: None
************************************/
	void left();
/************** right **************
     Purpose: This function turns the drone 90 degrees to the right, while remaining in the same location
     Returns: None
     Error: None
************************************/
	void right();
/************* current *************
     Purpose: This function returns the current position
     Returns: A Position which is the current position
     Error: None
************************************/
	Position current();
/********** totalDistance **********
     Purpose: This function returns the total units of distance travelled by the drone
     Returns: An integer which is the total units of distance travelled by the drone
     Error: None
************************************/
	int totalDistance();
/******** manhattanDistance ********
     Purpose: This function returns the manhattan distance between current position and origin (Manhattan distance is absolute north-south displacement plus absolute east-west dis- placement).
     Returns: An integer which is the manhattan distance the drone took
     Error: None
************************************/
	int manhattanDistance();
/************* repeated *************
     Purpose: This function returns a boolean value, which is: true if the current position is one that the drone has previously visited
     Returns: A boolean value, which is: true if the current position is one that the drone has previously visited
     Error: None
************************************/
	bool repeated();
};

#endif
