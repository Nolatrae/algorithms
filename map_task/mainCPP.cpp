#include <iostream>
#include <map>
#include <cmath>
#include <cstdlib>
#include <time.h>

using namespace std;

int main()
{
	map <int, int> mp;
	int n = 1;
	for (int i = 0; i < 8; i++)
	{
		n *= 10;
		double startTime = clock();
		for (int j = 0; j < n; j++)
		{
			mp.insert(make_pair(j, j % 10));
		}
		double diffTime = clock() - startTime;
		cout << n << ' '  << sizeof(mp) + n * 2 * sizeof(int) << ' ' << diffTime << endl;
	}
	return 0;
}
