void TestKnapsack(void);


/*
0-1���� ��̬�滮
����: n����Ʒ����ֵvi,����wi��������СW��
Ҫ�󣺱�������װ��Ʒ���ܼ�ֵV���
�����Ӽ�S��ʹsigma(wi) <= W ʱ��sigma(vi)���

˼·����֪S�����Ž⣬�������һ��Ԫ��n
1����ѡn����s    ��ǰn-1 ����W    ��ֵV    �����Ž�
2��ѡȡn����s-{n}��ǰn-1 ����W-wi ��ֵV-vi �����Ž�

�����ӽṹ
��A[i,x]��ʾ ǰi��Ԫ�أ�����x�µļ�ֵ
��A[i,x] = max{ A[i-1, x],    // ����n
		   vi + A[i-1, x-wi]} // ������n 
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

namespace nsKnapsack01 
{
	vector<int> vValue = { 3,2,4,4 };
	vector<int> vWeight = { 4,3,2,3 };
	int nSackVolume = 6;
	int nItem = (int)vValue.size();
	vector<vector<int>> vvValue(nItem + 1, vector<int>(nSackVolume + 1));

	int Value(int nFirst, int nTotal, int nItemValue)
	{
		if (nFirst < 0) { throw 0; };
		if (nTotal < 0) { return 0; };
		return vvValue[nFirst][nTotal] + nItemValue;
	}

	void PrintVV(void)
	{
		int n1 = (int)vvValue.size();
		int n2 = (int)vvValue.front().size();
		for (int j = 0; j < n2; ++j)
		{
			for (int i = 0; i < n1; ++i)
			{
				cout << vvValue[i][n2 - j - 1] << " ";
			}
			cout << endl;
		}
	}

	void main(void)
	{
		// a[i,x] = max{ a[i-1,x], vi + a[i-1, x-wi] }
		// i: [0, nItem], x: [0, nSackVolume]
		// vvValue[0][.] = 0;
		for (int i = 1; i <= nItem; ++i)
		{
			for (int j = 0; j <= nSackVolume; ++j)
			{
				int v1 = Value(i - 1, j, 0);
				int v2 = Value(i - 1, j - vWeight[i - 1], vValue[i - 1]);
				vvValue[i][j] = std::max(v1, v2);
			}
		}
		PrintVV();
	}
}


void TestKnapsack(void)
{
	nsKnapsack01::main();
}