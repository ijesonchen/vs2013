/*
1067. Sort with Swap(0,*) (25)
150 ms
65536 kB

Given any permutation of the numbers {0, 1, 2,..., N-1}, 
it is easy to sort them in increasing order. 
But what if Swap(0, *) is the ONLY operation that is allowed to use? 
For example, to sort {4, 0, 2, 1, 3} we may apply the swap operations in the following way:

Swap(0, 1) => {4, 1, 2, 0, 3}
Swap(0, 3) => {4, 1, 2, 3, 0}
Swap(0, 4) => {0, 1, 2, 3, 4}

Now you are asked to find the minimum number of swaps need to sort the given permutation of the first N nonnegative integers.

Input Specification:

Each input file contains one test case, which gives a positive N (<=10^5) followed by a permutation sequence of {0, 1, ..., N-1}. 
All the numbers in a line are separated by a space.

Output Specification:

For each case, simply print in a line the minimum number of swaps need to sort the given permutation.

Sample Input:
10 3 5 7 2 6 4 9 0 8 1

Sample Output:
9
*/

#include "..\patMain.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

/*
17:15
17:20 ��˼·��������

18:20
����󣬽����Ľ��

*/

namespace nsA1067A
{

	void main(void)
	{
		int numbers, n;
		cin >> numbers;

		vector<int> vData;
		while (cin >> n)
		{
			vData.push_back(n);
		}
		vector<int> vRef(numbers); // data to sort index
		for (int i = 0; i < numbers; ++i)
		{
			vRef[vData[i]] = i;
		}
		int cnt = 0;
		for (int i = 0; i < numbers; ++i)
		{
			int u = vData[i];
			if (u != i)
			{
				int ui = vRef[u];
				int ii = vRef[i];
				swap(vData[ui], vData[ii]);
				swap(vRef[u], vRef[i]);
				++cnt;
			}
		}
		cout << cnt << endl;
	}
}

/*
9:10
���⣺ֻ�ܺ�0����
·����0�͵�ǰλ�õ����ֵ���
0�ڶԵ�λ��ʱ���ҵ���һ�����λ�õ���
9:40 29/25 pt1,2 tle

��Ϊscanf
9:48 29/25 1,2TLE

ʹ��vDataIndex
10:20 29/25 1,2TLE

v[0]==0������һ������ʱ�����ϴ�����λ�ÿ�ʼ
10:30 pass
*/
namespace nsA1067B
{
	void main(void)
	{
		int n, t;
		scanf("%d", &n);

		vector<int> vData(n);
		vector<int> vDataIndex(n);
		int& idx0 = vDataIndex[0];
		int left = 0;
		for (int i = 0; i < n; ++i)
		{
			scanf("%d", &t);
			if (t != i) { ++left; }
			vData[i] = t;
			vDataIndex[t] = i;
		}
		int cnt = 0;
		int idxi = 0;
		int istart = 1;
		while (left)
		{
			// vdata[idx0] = 0, vdata[idxi] = i;
			if (!idx0)
			{
				// find next pos
				idxi = istart;
				while (idxi < n && vData[idxi] == idxi)
				{
					++idxi;
				}
				if (idxi == n)
				{
					break;
				}
				istart = idxi + 1;
				swap(vData[idx0], vData[idxi]);
				swap(vDataIndex[vData[idx0]], vDataIndex[0]);
				++cnt;
				++left;
			}
			while (idx0)
			{
				idxi = vDataIndex[idx0];
				swap(vData[idx0], vData[idxi]);
				swap(vDataIndex[idx0], vDataIndex[0]); // vData[idxi] = idx0, vData[idx0] = 0;
				++cnt;
				--left;
			}
			--left;
		}
		cout << cnt << endl;
	}
}

/*
11��00
ʹ��umap�滻vData2Index
11:10 8/25 1tle, 3wa��˵�������д�������ѭ�����ߴ�����

*/
namespace nsA1067C
{
	void main(void)
	{
		int n, t;
		scanf("%d", &n);

		vector<int> vData(n);
		unordered_map<int, int> mapDataIndex;
		int left = 0;
		for (int i = 0; i < n; ++i)
		{
			scanf("%d", &t);
			if (t != i) { ++left; }
			vData[i] = t;
			mapDataIndex[t] = i;
		}
		int cnt = 0;
		int idxi = 0;
		int istart = 1;
		while (left)
		{
			// vdata[idx0] = 0, vdata[idxi] = i;
			if (!mapDataIndex[0])
			{
				// find next pos
				idxi = istart;
				while (idxi < n && vData[idxi] == idxi)
				{
					++idxi;
				}
				if (idxi == n)
				{
					break;
				}
				istart = idxi + 1;
				mapDataIndex[0] = idxi;
				mapDataIndex[vData[idxi]] = 0;
				swap(vData[0], vData[idxi]);
				++cnt;
				++left;
			}
			int idx0 = mapDataIndex[0];
			while (idx0)
			{
				// swap(0, di=idx0) 
				idxi = mapDataIndex[idx0];
				// data:0,   di = idx0 -> di=idx0, 0
				// pos:idx0, idxi      -> idx0   , idxi
				mapDataIndex[0] = idxi;
				idx0 = idxi;
				mapDataIndex[idx0] = idx0;
				swap(vData[idx0], vData[idxi]);
				++cnt;
				--left;
			}
			--left;
		}
		cout << cnt << endl;
	}
}

// rename this to main int PAT
int A1067Func(void)
{
	nsA1067C::main();
	return 0;
}


void A1067(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1067Func();
	cout << endl;
}

void A1067(void)
{
	A1067("data\\A1067-1.txt"); // 
}

