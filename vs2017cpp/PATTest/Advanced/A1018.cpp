/*
1018. Public Bike Management (30)

cost: 16:30
test: Tij <= 1000000;

sln1: shortest path, multiple: least number of bikes
	non-neg
	record: shortest path, total bike in path, path v<i>
	90min 20/30 pt5-9����

sln2: ���·����ͬʱ��ȡsend bike���ٵġ�
	20min pt0,3,4�쳣�˳��� pt5-9����
	�쳣��needBike - totalBike != sendBikes[problemStation]
	�����Ǽ��� ��ǰ·����Ҫbike��ʱ�����

	����������ʱsendBike���㷽��
	14/30 pt1,3,4�쳣��5-9����
	����������ʱsendBike���㷽��
	20/30 5-9����

sln3: ���·����ͬʱ��ȡtake back��send bikes��С
	15min 25/30 pt5,7����

sln4: �������ȼ�ȡ�����·����send bikes��С��take back��С
	5min 20/30 pt5-9����
	

sln5: ��⣺
	����������1.ʱ����� 2.�ͳ��������� 3.���ճ�������
	������һ������·����վ��ĳ�����Ŀʱ�����ܰѺ���վ�������ĳ���������ǰ�泵����������վ�㡣
	https://www.cnblogs.com/luojiahu/p/3892608.html
	�ֶμ���send
	25/30 pt5,7����
	�ֶμ���send/take
	25/30 pt5,6,7���� ʾ������
	send����ʱ���ǵ�ǰtake
	13/30 pt0,5,7����ʾ������
	20min

sln6: ����FindMinDist
	10min 8/30 pt0,5-9����ʾ����ȷ

There is a public bike service in Hangzhou City which provides great convenience to the tourists from all over the world. 
One may rent a bike at any station and return it to any other stations in the city.

The Public Bike Management Center (PBMC) keeps monitoring the real-time capacity of all the stations. 
A station is said to be in perfect condition if it is exactly half-full.
If a station is full or empty, PBMC will collect or send bikes to adjust the condition of that station to perfect. 
And more, all the stations on the way will be adjusted as well.

When a problem station is reported, PBMC will always choose the shortest path to reach that station. 
If there are more than one shortest path, the one that requires the least number of bikes sent from PBMC will be chosen.


                 PBMC
              1         1
	   S1(6)       3       S2(7)
              1         1
		         S3(0)
 BIKE 1:6 2:7 3:0
 PATH (PBMC IS 0):
 0 1 1
 0 2 1
 0 3 3
 1 3 1
 2 3 1
 
Figure 1 illustrates an example. 
The stations are represented by vertices and the roads correspond to the edges. 
The number on an edge is the time taken to reach one end station from another. 
The number written inside a vertex S is the current number of bikes stored at S.
Given that the maximum capacity of each station is 10. 
To solve the problem at S3, we have 2 different shortest paths:

1. PBMC -> S1 -> S3. 
  In this case, 4 bikes must be sent from PBMC,
  because we can collect 1 bike from S1 and then take 5 bikes to S3, 
  so that both stations will be in perfect conditions.

2. PBMC -> S2 -> S3. 
  This path requires the same time as path 1, 
  but only 3 bikes sent from PBMC and hence is the one that will be chosen.

Input Specification:
Each input file contains one test case.
For each case, the first line contains 4 numbers: 
Cmax (<= 100), always an even number, is the maximum capacity of each station; 
N (<= 500), the total number of stations; 
Sp, the index of the problem station 
  (the stations are numbered from 1 to N, and PBMC is represented by the vertex 0); and 
M, the number of roads. 

The second line contains N non-negative numbers Ci (i=1,...N) where 
each Ci is the current number of bikes at Si respectively. 

Then M lines follow, each contains 3 numbers: 
Si, Sj, and Tij which describe the time Tij taken to move betwen stations Si and Sj. 

All the numbers in a line are separated by a space.

Output Specification:

For each test case, print your results in one line. 
First output the number of bikes that PBMC must send. 
Then after one space, output the path in the format: 0->S1->...->Sp. 
Finally after another space, output the number of bikes that 
we must take back to PBMC after the condition of Sp is adjusted to perfect.

Note that if such a path is not unique, 
output the one that requires minimum number of bikes that we must take back to PBMC. 
The judge's data guarantee that such a path is unique.

Sample Input:
10 3 3 5
6 7 0
0 1 1
0 2 1
0 3 3
1 3 1
2 3 1
Sample Output:
3 0->2->3 0
*/

#include "..\patMain.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

const int A1018MaxDist = 1000000;

class A1018AdjGraph
{
public:
	void ReadData(void);
	void Calc(void);
	int FindMinDist(void) const;
	void Update(const int u, const int v);
protected:
	struct Edge
	{
		int v = 0;
		int d = 0;

		Edge() : v(0), d(0) {};
		Edge(int _v, int _t) : v(_v), d(_t) {}
	};
	int nodes = 0;
	int edges = 0;
	int problemStation = 0;
	int capPerNode = 0;
	int capPerfect = 0;

	vector<vector<Edge>> adjs;
	vector<int> nodeBikes;

	vector<bool> visit;
	// ���·��
	vector<int> dist;
	// ��ǰ·��������
	vector<int> pathBikes;
	vector<int> sendBikes;
	vector<int> absBikes;
	vector<int> takeBikes;
	vector<vector<int>> paths;
};


void A1018AdjGraph::ReadData(void)
{
	cin >> capPerNode >> nodes >> problemStation >> edges;
	capPerfect = capPerNode / 2;
	// count PBMC as 0
	++nodes;
	adjs.assign(nodes, vector<Edge>());
	nodeBikes.assign(nodes, 0);
	for (int i = 1; i < nodes; ++i)
	{
		cin >> nodeBikes[i];
	}
	for (int i = 0; i < edges; ++i)
	{
		int u, v, t;
		cin >> u >> v >> t;
		adjs[u].push_back(Edge(v, t));
		adjs[v].push_back(Edge(u, t));
	}
	dist.assign(nodes, A1018MaxDist);
	pathBikes.assign(nodes, A1018MaxDist);
	sendBikes.assign(nodes, A1018MaxDist);
	absBikes.assign(nodes, A1018MaxDist);
	takeBikes.assign(nodes, A1018MaxDist);
	visit.assign(nodes, false);
	paths.assign(nodes, vector<int>());
}


void A1018AdjGraph::Calc(void)
{
	dist[0] = 0;
	int total = nodes;
	int last = 0;
	pathBikes[0] = 0;
	dist[0] = 0;
	do
	{
		int next = FindMinDist();
		visit[next] = true;
		Update(last, next);
		last = next;
	} while (--total > 0);

	auto totalBike = pathBikes[problemStation];
	auto& procPath = paths[problemStation];

	auto needBike = procPath.size() * capPerfect;

	if (needBike > totalBike)
	{
		if (needBike - totalBike != absBikes[problemStation])
		{
			throw 0;
		}
		cout << needBike - totalBike << " 0";
		for (auto n : procPath)
		{
			cout << "->" << n;
		}
		cout << " 0" << endl;
	}
	else
	{
		cout << "0 0";
		for (auto n : procPath)
		{
			cout << "->" << n;
		}
		cout << " " << totalBike - needBike << endl;
	}
}

int A1018AdjGraph::FindMinDist(void) const
{
	int idx = -1;
	int minDist = A1018MaxDist + 1;
	int minSend = 0;
	int minTake = 0;
	for (int i = 0; i < nodes; ++i)
	{
		if (visit[i])
		{
			continue;
		}
		auto di = dist[i];
		if (di > minDist)
		{
			continue;
		}
		auto si = sendBikes[i];
		auto ti = takeBikes[i];
		if ((di < minDist) ||
			(di == minDist && si < minSend) ||
			(di == minDist && si == minSend && ti < minTake))
		{
			minDist = di;
			minSend = si;
			minTake = ti;
			idx = i;
		}
	}
	if (idx == -1)
	{
		throw 0;
	}
	return idx;
}

void A1018AdjGraph::Update(const int last, const int next)
{
	auto edgeu = adjs[next];
	auto distu = dist[next];
	for (auto& e : edgeu)
	{
		auto v = e.v;
		auto distuv = distu + e.d;
		auto bikeuv = pathBikes[next] + nodeBikes[v];
		auto totalv = capPerfect * (int)(paths[next].size() + 1);
		auto absv = std::abs(totalv - bikeuv);
		auto sendv = sendBikes[next];
		auto takev = takeBikes[next];
		auto takeDiff = capPerfect - nodeBikes[v];
		if (takeDiff > 0)
		{
			if (takev > takeDiff)
			{
				// ��һ�ڵ���ʣ��
				takev -= takeDiff;
			}
			else
			{
				sendv += takeDiff - takev;
				takev = 0;
			}
		}
		else
		{
			takev += takeDiff;
		}
		if (distuv < dist[v] ||
			(distuv == dist[v] && sendv > 0 && sendv < sendBikes[v]) ||
			(distuv == dist[v] && sendv == sendBikes[v] && takev < takeBikes[v]))
		{
			dist[v] = distuv;
			pathBikes[v] = bikeuv;
			sendBikes[v] = sendv;
			absBikes[v] = absv;
			takeBikes[v] = takev;
			paths[v] = paths[next];
			paths[v].push_back(v);
		}
	}
}

// rename this to main int PAT
int A1018Func(void)
{
	A1018AdjGraph g;
	g.ReadData();
	g.Calc();

	return 0;
}
void A1018(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1018Func();
	cout << endl;
}

void A1018(void)
{
	A1018("data\\A1018-1.txt"); // 
}

