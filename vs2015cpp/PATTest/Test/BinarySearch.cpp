/*
��������·����
GraphAdj::PrintAllPath
���������0��ʼ�����п���·��
ԭ��
��¼��ǰ·��vPath,
ʹ��DFS�ݹ鴦��ǰ·��β�����з�֧
���޷�֧��β����·��������·���ѱ�������
�����ǰ·��
��;1�������п��ܵ����·�����ֲ���֦��
��������·������(��Dijkstra�����·�����飩
���Զ�ʹ�ø�������Ϊ��֦����
�������п��ܵ����·��
�Ǽ�ֱ֦�ӱ������Ӷ�(n-1)!
*/

#include "..\patMain.h"
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

namespace nsTestBinarySearchIter
{
	int BinarySearch(const vector<int>& vec, const int val, int left, int right)
	{
		if (right < left) { return -1; }
		int mid = left + (right - left) / 2;
		if (val == vec[mid])
		{
			return mid;
		}
		else if (val < vec[mid])
		{
			return BinarySearch(vec, val, left, mid - 1);
		}
		else
		{
			return BinarySearch(vec, val, mid + 1, right);
		}
	}


	void main(void)
	{
		int n,k, t;
		cin >> n;
		vector<int> vData(n);
		for (int i = 0; i < n; ++i)
		{
			cin >> vData[i];
		}
		sort(vData.begin(), vData.end());
		cin >> k;
		for (int i = 0; i < k; ++i)
		{
			cin >> t;
			cout << BinarySearch(vData, t, 0, n - 1) << " ";
		}
		cout << endl;
	}
}

namespace nsTestBinarySearchLoop
{
	int BinarySearch(const vector<int>& vec, const int val, int left, int right)
	{
		if (right < left) { throw 0; }
		while (left <= right)
		{
			int mid = left + (right - left) / 2;
			if (val == vec[mid])
			{
				return mid;
			}
			else if (val < vec[mid])
			{
				right = mid - 1;
			}
			else
			{
				left = mid + 1;
			}
		}
		return -1;
	}
	void main(void)
	{
		int n, k, t;
		cin >> n;
		vector<int> vData(n);
		for (int i = 0; i < n; ++i)
		{
			cin >> vData[i];
		}
		sort(vData.begin(), vData.end());
		cin >> k;
		for (int i = 0; i < k; ++i)
		{
			cin >> t;
			cout << BinarySearch(vData, t, 0, n - 1) << " ";
		}
		cout << endl;

	}

}

void TestBinarySearch(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	cout << "nsTestBinarySearchIter" << endl;
	nsTestBinarySearchIter::main();
	RedirCin(fn);
	cout << "nsTestBinarySearchLoop" << endl;
	nsTestBinarySearchLoop::main();
	cout << endl;
}

void TestBinarySearch(void)
{
	TestBinarySearch("data\\TBinarySearch-1.txt"); // 
}

