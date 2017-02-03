#include <iostream>

using namespace std;

struct Dot
{
	int x;
	int y;
	int color;
};

int dominanceCount(struct Dot * dotArray, int length)
{
	if(length == 1)
	{
		return 0;
	}

	int lengthL = length / 2;
	int lengthR = length - lengthL;
	
	struct Dot * dotArrayL = new Dot[lengthL];
	for (int i = 0; i < lengthL; i++)
	{
		dotArrayL[i].x = dotArray[i].x;
		dotArrayL[i].y = dotArray[i].y;
		dotArrayL[i].color = dotArray[i].color;
	}
	int cL = dominanceCount(dotArrayL, lengthL);

	struct Dot * dotArrayR = new Dot[lengthR];
	for (int i = 0; i < lengthR; i++)
	{
		dotArrayR[i].x = dotArray[i+lengthL].x;
		dotArrayR[i].y = dotArray[i+lengthL].y;
		dotArrayR[i].color = dotArray[i+lengthL].color;
	}
	int cR = dominanceCount(dotArrayR, lengthR);

	int i = 0;
	int j = 0;
	int nBlueLeft = 0;
	int cRL = 0;
	
	for (int k = 0; k < length; k++)
	{
		
		if ((i == lengthL) && (j < lengthR))
		{
			dotArray[k].x = dotArrayR[j].x;
			dotArray[k].y = dotArrayR[j].y;
			dotArray[k].color = dotArrayR[j].color;
			j++;
			if (dotArray[k].color == 0)
			{
				cRL += nBlueLeft;
			}
			continue;
		}
		if (j == lengthR)
		{
			break;
		}

		if (dotArrayL[i].y < dotArrayR[j].y)
		{
			dotArray[k].x = dotArrayL[i].x;
			dotArray[k].y = dotArrayL[i].y;
			dotArray[k].color = dotArrayL[i].color;
			i++;
			if (dotArray[k].color == 1)
			{
				nBlueLeft++;
			}
		}
		else
		{
			dotArray[k].x = dotArrayR[j].x;
			dotArray[k].y = dotArrayR[j].y;
			dotArray[k].color = dotArrayR[j].color;
			j++;
			if (dotArray[k].color == 0)
			{
				cRL += nBlueLeft;
			}
		}
	}
	int total = cL + cRL + cR;
	return total;
}

int main()
{
	int numOfPoint;
	cin >> numOfPoint;

	struct Dot * dotArray = new Dot[numOfPoint];
	
	for (int i = 0; i < numOfPoint; i++)
	{
		cin >> dotArray[i].x >> dotArray[i].y >> dotArray[i].color;
	}

	cout << dominanceCount(dotArray, numOfPoint) << endl;
}