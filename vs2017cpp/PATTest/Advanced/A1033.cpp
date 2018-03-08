/*
1033. To Fill or Not to Fill (25)
100 ms
65536 kB

9:50


With highways available, driving a car from Hangzhou to any other city is easy. 
But since the tank capacity of a car is limited, we have to find gas stations on the way from time to time. 
Different gas station may give different price. You are asked to carefully design the cheapest route to go.

Input Specification:

Each input file contains one test case.
For each case, the first line contains 4 positive numbers: 
Cmax (<= 100), the maximum capacity of the tank; 
D (<=30000), the distance between Hangzhou and the destination city; 
Davg (<=20), the average distance per unit gas that the car can run; and 
N (<= 500), the total number of gas stations. 

Then N lines follow, each contains a pair of non-negative numbers:
Pi, the unit gas price, and Di (<=D), the distance between this station and Hangzhou, 
for i=1,...N. All the numbers in a line are separated by a space.

Output Specification:

For each test case, print the cheapest price in a line, accurate up to 2 decimal places. 
It is assumed that the tank is empty at the beginning.
If it is impossible to reach the destination, print "The maximum travel distance = X" 
where X is the maximum possible distance the car can run, accurate up to 2 decimal places.

Sample Input 1:
50 1300 12 8
6.00 1250
7.00 600
7.00 150
7.10 0
7.20 200
7.50 400
7.30 1000
6.85 300
Sample Output 1:
749.17
Sample Input 2:
50 1300 12 2
7.10 0
7.00 600
Sample Output 2:
The maximum travel distance = 1200.00
*/

#include "..\patMain.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/*
9:50
��ʼ����Ϊ��
������cmax��������100] D Ŀ�����30000] Davg��λ�;���20] N��վ����500]
�Ǹ���pi�ͼ� di������

.2f ��ͼ۸񣬻��޷�����ʱ������

��̬�滮���ݹ�
������30000/20=1500
���50����
ÿ�μ������distTank=cmax*davg��ҪС�ڸ���վ��ࣺ�޷�����ʱ�Ĵ���
ÿ�μ۸�p[i]��ʣ������gleft[i]��������gadd[i]����������dgas[i]���ܼ�total[i]

̰�ģ�
����Ŀ�ļ���վ���ͼ�Ϊ0
��ǰ��ʼ��������
��ǰ���串�ǵ�վ��
�����������ܸ��ǵ���վ
11��00 ����

*/

namespace nsA1033A
{
	struct Station 
	{
		float dist = 0;
		float p = 0;

		bool operator<(const Station& s)
		{ return dist != s.dist ? dist < s.dist : p < s.p; }
	};



	void main(void)
	{
		int n;
		float cMax, dist, davg;
		scanf("%f %f %f %d", &cMax, &dist, &davg, &n);
		vector<Station> vStation;
		for (int i = 0; i < n; ++i)
		{
			vStation.emplace_back();
			scanf("%f %f", &vStation.back().p, &vStation.back().dist);
		}
		vStation.emplace_back();
		vStation.back().p = 0; vStation.back().dist = dist;
		sort(vStation.begin(), vStation.end());
		if (vStation.front().dist != 0)
		{
			printf("The maximum travel distance = 0.00\n");
			return;
		}
		bool bImpossible = false;

		float pTotal = 0;
		float gLeft = 0;
		Station* pPrev = &vStation.front();
		float gPrice = pPrev->p;
		for (size_t i = 1; i < vStation.size(); ++i)
		{
			Station& next = vStation[i];
			if (next.dist >= dist)
			{
				break;
			}
			float gCost = (next.dist - pPrev->dist) / davg;
			if (gCost > cMax)
			{
				bImpossible = true;
				break;
			}
			float gNeed;
			if (pPrev->p < next.p) {  gNeed = cMax; } // fufill
			else { gNeed =  gCost; }
			pTotal = gPrice * (gNeed - gLeft);
			gPrice = next.p;
			gLeft = gNeed - gCost;
			pPrev = &next;
		}
		if (bImpossible)
		{
			float totolDist = pPrev->dist + gLeft * davg;
			printf("The maximum travel distance = %.2f\n", totolDist);
		}
		else
		{
			printf("%.2f\n", pTotal);
		}
	}
}


/*
14��30
̰�ģ�
վ�㰴�۸�����ÿ��ȡ��С�ļ���
ѡȡ��һ��Сվ��i���۸�pi������gLeft����������
δ����λ�������ʾ
15:30 ����
*/
namespace nsA1133B
{
	struct Station 
	{
		float d;
		float p;

		bool operator<(const Station& a) 
		{ return p != a.p ? p < a.p : d < a.d; }
	};

	struct Dist
	{
		float start = 0;
		float end = 0;
		bool filled = false;
		Dist* next = nullptr;

		Dist(float s, float e, bool f) : start(s), end(e), filled(f) {};

		bool Include(int d) 
			{ return start <= d && d >= end; }
		float MaxDist(void) const { return end - start; }
	};

	Dist* FindPos(Dist* pRoot, int d)
	{
		while (!pRoot->Include(d))
		{
			pRoot = pRoot->next;
		}
	}

	void main(void)
	{
		float tankCap, dstDist, distPerGas;
		int nStation;
		scanf("%f %f %f %d\n", &tankCap, &dstDist, &distPerGas, &nStation);
		float maxFullTankDist = tankCap * distPerGas;
		vector<Station> vStation;
		bool bImpossible = true;
		for (int i = 0; i < nStation; ++i)
		{
			vStation.emplace_back();
			scanf("%f %f\n", &vStation.back().p, &vStation.back().d);
			if (vStation.back().d == 0)
			{
				bImpossible = false;
			}
		}
		vStation.emplace_back();
		sort(vStation.begin(), vStation.end());
		
		// memory leakage
		Dist* pRoot = new Dist(0, dstDist, false);
		float totalPrice = 0;
		for (int i = 0; i < nStation; ++i)
		{
			auto& station = vStation[i];
			if (station.d >= dstDist) { continue; }
			Dist* pCurrent = FindPos(pRoot, station.d);
			// ����������������������
			if (pCurrent->filled)
			{
				if (!pCurrent->next) { continue; }
				Dist* pNext = pCurrent->next;
				float maxDist = pNext->MaxDist();
				if (maxDist == maxFullTankDist)
				{ 
				}
			}
		}
	}
}

// rename this to main int PAT
int A1033Func(void)
{
	nsA1033A::main();
	return 0;
}


void A1033(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1033Func();
	cout << endl;
}

void A1033(void)
{
	A1033("data\\A1033-1.txt"); // 
	A1033("data\\A1033-2.txt"); // 
}

