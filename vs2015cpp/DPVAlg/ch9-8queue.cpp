#include "main.h"

using namespace std;

//////////////////////////////////////////////////////////////////////////
/*
��8X8��Ĺ��������ϰڷŰ˸��ʺ�ʹ�䲻�ܻ��๥����
�����������ʺ󶼲��ܴ���ͬһ�С�ͬһ�л�ͬһб���ϣ����ж����ְڷ���92��

8�ʺ��������������������⣬���õݹ��㷨��
*/


class QueueBoard
{
public:
	int Search(void)
	{
		Search(0);
		cout << "ANS: " << nCount << ", checked: " << nCheck << endl;
		return nCount;
	}
	
	void Search(int i)
	{
		if (i >= nBoardLength)
		{
			return;
		}
		for (int j = 0; j < nBoardLength; ++j)
		{
			pBoardQueuep[i] = j;
			if (!CheckValidLast(i))
			{
				continue;
			}
			if (i == nBoardLength - 1)
			{
				++nCount;
			}
 			Search(i + 1);
		}
	}

	bool CheckValidLast(int iLast)
	{
		++nCheck;
		auto length = iLast;
		auto jLast = pBoardQueuep[iLast];
		for (size_t i = 0; i < length; i++)
		{
			auto j = pBoardQueuep[i];
			if (j == jLast)
			{
				return false;
			}
			auto k = iLast - i;
			if (jLast > j && (k == jLast - j))
			{
				return false;
			}
			if (j > jLast && (k == j - jLast))
			{
				return false;
			}
		}
		return true;
	}
private:
	static const int nBoardLength = 8;
	int pBoardQueuep[nBoardLength] = { 0 };
	int nCount = 0;
	int nCheck = 0;
	bool bbb = true;

};


void EightQueue(void)
{
	QueueBoard q;
	q.Search();

}
