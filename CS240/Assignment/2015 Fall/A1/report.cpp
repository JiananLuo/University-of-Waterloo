#include <iostream>
using namespace std;

void helper(int height, int c, int *array, int size)
{
	if(height == 0)
	{
		if(array[0] >= c)
		{
			cout << array[0] << endl;
		}
	}

		int left = 2 * height + 1;
		if((left < size) && (array[left] >= c))
		{
			cout << array[left] << endl;
			helper(height+1, c, array, size);
		}
		int right = 2 * height + 2;
		if((right < size) && (array[right] >= c))
		{
			cout << array[right] << endl;
			helper(height+2, c, array, size);
		}
}

int main()
{
	int size;
	int c;
	cin >> size;
	int array[size];

	for(int i=0; i<size; i++)
	{
		cin >> array[i];
	}
	cin >> c;
	helper(0, c, array, size);
}