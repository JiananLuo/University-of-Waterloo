#include <iostream>
#include <string>
#include <math.h>
#include <climits>

using namespace std;

//struct for coordnates
struct Coord
{
	int pnum;
	int x;
	int y;
};

//struct for edge
struct Edge
{
	double weight;
	int A;
	int B;
};

//helper function to help 
double distancee(Coord A, Coord B)
{
	double weight = sqrt(pow((A.x - B.x),2) + pow((A.y - B.y),2));
	return weight;
}

int main()
{
	//Readin all input points
	int numPoints;
	cin >> numPoints;
	Coord points[numPoints];
	int x, y;
	for(int i=0; i<numPoints; i++)
	{
		cin >> x >> y;
		points[i].pnum = i;
		points[i].x = x;
		points[i].y = y;
	}


	//Generate visit list to check if the point is visited already
	int visitedPoints[numPoints];
	for(int i=0; i<numPoints; i++)
	{
		// 0 = not visited; 1 = visited
		visitedPoints[i] = 0;
	}
	int currentPoint = 0;
	visitedPoints[0] = 1;


	//init values
	Edge MST[numPoints-1];
	Edge shortestWeight[numPoints]; // this is a value table for all points with the shortest weight 
	for(int i=0; i<numPoints; i++)
	{
		shortestWeight[i].weight = distancee(points[0], points[i]);
		shortestWeight[i].A = 0;
		shortestWeight[i].B = i;
	}

	for(int i=0; i<numPoints-1; i++)
	{
		//find shortest weight
		int minWeight = INT_MAX;
		int minPoint;
		for(int j=0; j<numPoints; j++)
		{
			//check if visited
			if(visitedPoints[j] == 1)
				continue;
			if(shortestWeight[j].weight < minWeight)
			{
				minWeight = shortestWeight[j].weight;
				minPoint = j;
			}
		}
		//Mark the point we found as visited
		visitedPoints[minPoint] = 1;

		//Add the edge to MST
		MST[i].weight = 1;
		MST[i].A = shortestWeight[minPoint].A;
		MST[i].B = minPoint;

		//Break when we reach to the end (t)
		if(currentPoint == 1)
			break;

		//update shortest weight table
		for(int j=0; j<numPoints; j++)
		{
			//check if visited
			if(visitedPoints[j] == 1)
			{
				continue;
			}
			double newDistance = distancee(points[minPoint], points[j]);
			if(newDistance < shortestWeight[j].weight)
			{
				shortestWeight[j].weight = newDistance;
				shortestWeight[j].A = minPoint;
				shortestWeight[j].B = j;
			}
		}
	}

	//we need to find the path back from t to s
	int endPoint = 1;
	int path[numPoints-1];
	int count = 0;
	for(int i=0; i<numPoints-1; i++)
	{
		for(int j=0; j<numPoints-1; j++)
		{
			if(MST[j].B == endPoint)
			{
				endPoint = MST[j].A;
				path[count] = MST[j].A;
				count++;
				break;
			}
		}
	}
	//print it from front to end
	for(int i=count-1; i>=0; i--)
	{
		cout << path[i]+1 << endl;
	}
	cout << 2 << endl;
}