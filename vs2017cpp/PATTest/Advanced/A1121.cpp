/*
1121. Damn Single (25)

cost: 14:45

300ms

"Damn Single (����)" is the Chinese nickname for someone who is being single. 
You are supposed to find those who are alone in a big party, so they can be taken care of.

Input Specification:

Each input file contains one test case. 
For each case, the first line gives a positive integer N (<=50000), 
the total number of couples.
Then N lines of the couples follow, 
each gives a couple of ID's which are 5-digit numbers (i.e. from 00000 to 99999). 
After the list of couples, there is a positive integer M (<=10000) followed by M ID's of the party guests.
The numbers are separated by spaces. 
It is guaranteed that nobody is having bigamous marriage (�ػ�) or dangling with more than one companion.

Output Specification:

First print in a line the total number of lonely guests. 
Then in the next line, print their ID's in increasing order. 
The numbers must be separated by exactly 1 space, and there must be no extra space at the end of the line.

Sample Input:
3
11111 22222
33333 44444
55555 66666
7
55555 44444 10000 88888 22222 11111 23333
Sample Output:
5
10000 23333 44444 55555 88888

*/

#include "..\patMain.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/*
14:45 15min 23/25 pt1 wa
*/
namespace nsA1121A
{
	const int MAXNODE = 100000;
	vector<short> vCouples;

	int main(void)
	{
		vCouples.assign(MAXNODE, -1);
		int n, a, b;
		cin >> n;
		for (int i = 0; i < n; ++i)
		{
			cin >> a >> b;
			vCouples[a] = b;
			vCouples[b] = a;
		}
		int k;
		cin >> k;
		vector<int> vGuest;
		for (int i = 0; i < k; ++i)
		{
			int m;
			cin >> m;
			vGuest.push_back(m);
		}
		vector<bool> vVisit(k, false);
		vector<int> vSingle;
		for (int i = 0; i < k; ++i)
		{
			if (vVisit[i])
			{
				continue;
			}
			a = vGuest[i];
			b = vCouples[a];
			bool bFound = false;
			for (int j = i + 1; j < k; ++j)
			{
				if (vGuest[j] == b)
				{
					bFound = true;
					vVisit[j] = true;
					break;
				}
			}
			if (!bFound)
			{
				vSingle.push_back(a);
			}
		}
		sort(vSingle.begin(), vSingle.end());
		size_t len = vSingle.size();
		cout << len << endl;
		if (len)
		{
			printf("%05d", vSingle.front());
			for (size_t i = 1; i < len; ++i)
			{
				printf(" %05d", vSingle[i]);
			}
			cout << endl;
		}
		return 0;
	}
}

// rename this to main int PAT
int A1121Func(void)
{
	nsA1121A::main();
	return 0;
}


void A1121(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1121Func();
	cout << endl;
}

void A1121(void)
{
	A1121("data\\A1121-1.txt"); // 
}

