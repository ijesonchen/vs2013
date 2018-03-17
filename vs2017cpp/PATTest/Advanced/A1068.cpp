/*
1068. Find More Coins (30)
150 ms
65536 kB

17:20

Eva loves to collect coins from all over the universe, including some other planets like Mars. 
One day she visited a universal shopping mall which could accept all kinds of coins as payments.
However, there was a special requirement of the payment: for each bill, she must pay the exact amount. 
Since she has as many as 10^4 coins with her, she definitely needs your help. 
You are supposed to tell her, for any given amount of money, whether or not she can find some coins to pay for it.

Input Specification:

Each input file contains one test case. 
For each case, the first line contains 2 positive numbers: 
N (<=10^4, the total number of coins) and 
M(<=10^2, the amount of money Eva has to pay). 
The second line contains N face values of the coins, which are all positive numbers. All the numbers in a line are separated by a space.

Output Specification:

For each test case, print in one line the face values V1 <= V2 <= ... <= Vk such that V1 + V2 + ... + Vk = M. 
All the numbers must be separated by a space, and there must be no extra space at the end of the line. 
If such a solution is not unique, output the smallest sequence. 
If there is no solution, output "No Solution" instead.

Note: sequence {A[1], A[2], ...} is said to be "smaller" than sequence {B[1], B[2], ...} if there exists k >= 1 such that A[i]=B[i] for all i < k, and A[k] < B[k].

Sample Input 1:
8 9
5 9 8 7 2 3 4 1
Sample Output 1:
1 3 5
Sample Input 2:
4 8
7 2 4 3
Sample Output 2:
No Solution
*/

#include "..\patMain.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/*
17:20 
�ƺ��Ǳ������⣿
������������п������У��ҵ���һ�������
18:10 29/30 PT6 TLE

PT6Ϊno sln
������ǰ�˳� 
18:20 2/30
*/

namespace nsA1068A
{
	vector<int> vCoin(0);
	vector<int> vResult;
	int maxCoin = 0;
	int nCoin = 0;
	int dstCoin = 0;

	void PrintCoin(int n)
	{
		cout << vCoin[0];
		for (int j = 1; j < n; ++j)
		{
			cout << " " << vCoin[j];
		}
		cout << endl;
		return;
	}

	bool found = false;
	void Search(int start, int amount)
	{
		if (found || amount > dstCoin)
		{
			return;
		}
		if (amount == dstCoin)
		{
			if (!found)
			{
				vResult.assign(vCoin.begin(), vCoin.begin() + start);
				found = true;
			}

			return;
		}
		for (int i = start; i < nCoin; ++i)
		{
			swap(vCoin[i], vCoin[start]);
			Search(start + 1, amount + vCoin[start]);
			swap(vCoin[i], vCoin[start]);
		}
	}

	void main(void)
	{
		found = false;
		cin >> nCoin >> dstCoin;
		vCoin.resize(nCoin);
		vResult = vCoin;
		for (int i = 0; i < nCoin; ++i)
		{
			cin >> vCoin[i];
		}
		sort(vCoin.begin(), vCoin.end());
		maxCoin = 0;
		int total = 0;
		for (int i = 0; i < nCoin; ++i)
		{
			total += vCoin[i];
			if (total == dstCoin)
			{
				PrintCoin(i + 1);
				return;
			}
			if (total >= dstCoin)
			{
				maxCoin = i + 1;
				break;
			}
		}
		if (!maxCoin)
		{
			cout << "No Solution" << endl;
		}
		Search(0, 0);
		if (!found)
		{
			cout << "No Solution" << endl;
			return;
		}
		sort(vResult.begin(), vResult.end());

		cout << vResult[0];
		for (size_t j = 1; j < vResult.size(); ++j)
		{
			cout << " " << vResult[j];
		}
		cout << endl;
	}
}

/*
21:20
ref�� Liuchuo
01��������̬�滮
����
��������min(n,m)�����m��1�֣�
A[i,x]: ǰi��Ӳ�ң�����Ϊx�ļ�ֵ
���������⡣��Ҫ�ο�Liuchuo�����������������
*/

namespace nsA1068B
{
	int Value(vector<vector<int>>& vv, int i, int x, int v)
	{
		if (x < 0) { return 0; }
		return vv[i][x] + v;
	}
	
	void main(void)
	{
		int n, m;
		scanf("%d %d", &n, &m);
		vector<int> vCoin(n+1);
		for (int i = 0; i < n; ++i)
		{
			scanf("%d", &vCoin[i+1]);
		}
		sort(vCoin.rbegin(), vCoin.rend()-1);
		int nKnapsack = std::min(n, m);
		vector<vector<int>> vvA(n + 1, vector<int>(nKnapsack + 1));
		vector<int> vPath;
		for (int i = 1; i <=n; ++i)
		{
			for (int j = 0; j <= nKnapsack; ++j)
			{
				int v1 = Value(vvA, i - 1, j, 0);
				int v2 = Value(vvA, i - 1, j - 1, vCoin[i]);
				vvA[i][j] = std::max(v1, v2);
				if (vvA[i][j] == m)
				{
					// build path
					vector<int> vTmpPath;
					int a = i, b = j;
					while (a>0)
					{
						if (vvA[a][b] != vvA[a-1][b])
						{
							// sel coin i
							vTmpPath.push_back(vCoin[a]);
							--b;
						}
						--a;
					}
					reverse(vTmpPath.begin(), vTmpPath.end());
					if (!vPath.empty())
					{
						if (vTmpPath < vPath)
						{
							vPath.swap(vTmpPath);
						}
					}
					else
					{
						vPath.swap(vTmpPath);
					}
				}
			}
		}
	}
}

/*
22:30
���ǣ���С��������ͼ������С������·��
�������п���·����2^m,��֦
*/

namespace nsA1068C
{
	int nTarget;
	int nCoin;
	vector<int> vCoins;
	vector<bool> vVisit;
	bool bFound;

	vector<int> vPath;

	// u: current idx, total current coin;
	void dfs(int u, int total)
	{
		if (bFound || total > nTarget) { return; }
		if (total == nTarget)
		{
			cout << vPath.front();
			for (size_t i = 1; i < vPath.size(); ++i)
			{
				cout << " " << vPath[i];
			}
			cout << endl;
			bFound = true;
			return;
		}
		for (int i = u + 1; i < nCoin; ++i)
		{
			if (!vVisit[i])
			{
				int next = total + vCoins[i];
				if (next > nTarget)
				{
					return;
				}
				vVisit[i] = true;
				vPath.push_back(vCoins[i]);
				dfs(i, total + vCoins[i]);
				vPath.pop_back();
				vVisit[i] = false;
			}
		}
	}

	void main(void)
	{
		cin >> nCoin >> nTarget;
		vCoins.resize(nCoin);
		for (int i = 0; i < nCoin; ++i)
		{
			cin >> vCoins[i];
		}
		sort(vCoins.begin(), vCoins.end());
		vVisit.assign(nCoin, false);

		vPath.clear();
		bFound = false;
		for (int i = 0; i < nCoin; ++i)
		{
			if (bFound) { return; }
			vVisit[i] = true;
			// dfs
			int u = i;
			int total = vCoins[i];
			vPath.clear();
			vPath.push_back(total);
			dfs(u, total);
		}
		if (!bFound)
		{
			cout << "No Solution" << endl;
		}
	}
}


// rename this to main int PAT
int A1068Func(void)
{
	nsA1068C::main();
	return 0;
}


void A1068(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1068Func();
	cout << endl;
}

void A1068(void)
{
	A1068("data\\A1068-1.txt"); // 
//	A1068("data\\A1068-2.txt"); // 
}

