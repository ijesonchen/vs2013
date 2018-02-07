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
	������������ʹ��send/take����
	15min 27/30 pt7����
	30min add testcase

sln7: �ο�sln5�е���⣬�������·�����ɶ����������������
	ԭ��BFSʱͬʱ�ж�send��take�����ܵ��´����̰���߼�
	60min pass

sln7: �ο�sln5����⣬��dijkstra��Ȼ��bfs��֦����CalcByDfs
	(ԭ�㷨��ΪCalcByDijkstra��
	40min 29/30 pt9�쳣
	

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
#include <algorithm>

using namespace std;

const int A1018MaxDist = 1000000;

class A1018AdjGraph
{
public:
	void ReadData(void);
	int FindMinDist(void) const;
	void Update(const int u, const int v);
	void CalcByDijkstra(void);
	void CalcByDfs(void);
protected:
	void Dijkstra(void);
	void CalcPathByDijkstra(void);
	void CalcPathByDfsSearch(void);
	void BuildPathByDijkstra(int n, vector<int> prev);
	void DfsPath(void);
	void DfsAllPath(int udist);
	struct Edge
	{
		int v = 0;
		int d = 0;

		Edge() : v(0), d(0) {};
		Edge(int _v, int _t) : v(_v), d(_t) {}
	};
	struct Path
	{		
		vector<int> revPath;
		vector<int> directPath;
		int send = 0;
		int take = 0;
		void CalcRev(const vector<int>& bikes, int perfect);
		void CalcDirect(const vector<int>& bikes, int perfect);
		bool operator<(const Path& p);
	};
	int nodes = 0;
	int edges = 0;
	int problemStation = 0;
	int capPerNode = 0;
	int capPerfect = 0;

	vector<vector<Edge>> adjs;
	vector<int> nodeBikes;

	vector<bool> visit;
	vector<int> dist;
	vector<vector<int>> lastHops;
	vector<Path> allPaths;
	vector<int> vPath;
};


void A1018AdjGraph::Path::CalcRev(const vector<int>& bikes, int perfect)
{
	for (auto it = revPath.rbegin(); it != revPath.rend(); ++it)
	{
		auto u = *it;
		auto takeuv = bikes[u] - perfect;
		if (takeuv > 0)
		{
			take += takeuv;
		}
		else if (takeuv < 0)
		{
			takeuv = -takeuv;
			if (take > takeuv)
			{
				take -= takeuv;
			}
			else
			{
				send += takeuv - take;
				take = 0;
			}
		}
	}
}

void A1018AdjGraph::Path::CalcDirect(const vector<int>& bikes, int perfect)
{
	for (auto it = ++directPath.begin(); it != directPath.end(); ++it)
	{
		auto u = *it;
		auto takeuv = bikes[u] - perfect;
		if (takeuv > 0)
		{
			take += takeuv;
		}
		else if (takeuv < 0)
		{
			takeuv = -takeuv;
			if (take > takeuv)
			{
				take -= takeuv;
			}
			else
			{
				send += takeuv - take;
				take = 0;
			}
		}
	}
}

bool A1018AdjGraph::Path::operator<(const Path& p)
{
	if (send < p.send)
	{
		return true;
	}
	else if (send == p.send)
	{
		if (take == p.take)
		{
			throw 0;
		}
		return take < p.take;
	}
	else
	{
		return false;
	}
}


void A1018AdjGraph::CalcByDijkstra(void)
{
	Dijkstra();
	CalcPathByDijkstra();
}

void A1018AdjGraph::CalcByDfs(void)
{
	Dijkstra();
	CalcPathByDfsSearch();
}

void A1018AdjGraph::CalcPathByDijkstra(void)
{
	vector<int> vp;
	BuildPathByDijkstra(problemStation, vp);

	auto pmin = *min_element(allPaths.begin(), allPaths.end());

	cout << pmin.send << " 0";

	for (auto it = pmin.revPath.rbegin(); it != pmin.revPath.rend(); ++it)
	{
		cout << "->" << *it;
	}
	cout << " " << pmin.take << endl;
}


void A1018AdjGraph::CalcPathByDfsSearch(void)
{
	DfsPath();

	auto pmin = *min_element(allPaths.begin(), allPaths.end());

	cout << pmin.send << " " << pmin.directPath.front();

	for (auto it = ++pmin.directPath.begin(); it != pmin.directPath.end(); ++it)
	{
		cout << "->" << *it;
	}
	cout << " " << pmin.take << endl;

}

void A1018AdjGraph::DfsPath(void)
{
	visit.assign(nodes, false);
	visit[0] = true;
	vPath.clear();
	vPath.push_back(0);
	DfsAllPath(0);
}

void A1018AdjGraph::DfsAllPath(int udist)
{
	auto u = vPath.back();

	if (u == problemStation)
	{
		Path p;
		p.directPath = vPath;
		p.CalcDirect(nodeBikes, capPerfect);
		allPaths.push_back(p);
		return;
	}

	auto& vAdju = adjs[u];
	size_t nv = 0;
	for (auto ev : vAdju)
	{
		auto v = ev.v;
		auto vdist = udist + ev.d;
		if (visit[v] || vdist > dist[v])
		{
			continue;
		}
		visit[v] = true;
		vPath.push_back(v);
		DfsAllPath(vdist);
		visit[v] = false;
		vPath.pop_back();
	}
}


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
	visit.assign(nodes, false);
	dist.assign(nodes, A1018MaxDist);
	lastHops.assign(nodes, vector<int>());
}

void A1018AdjGraph::BuildPathByDijkstra(int n, vector<int> prev)
{
	if (n == 0)
	{
		Path p;
		p.revPath = prev;

		p.CalcRev(nodeBikes, capPerfect);
		allPaths.push_back(p);

		return;
	}
	prev.push_back(n);
	for (auto k : lastHops[n])
	{
		BuildPathByDijkstra(k, prev);
	}
}

void A1018AdjGraph::Dijkstra(void)
{
	dist[0] = 0;
	int total = nodes;
	int last = 0;
	dist[0] = 0;
	do
	{
		int next = FindMinDist();
		visit[next] = true;
		Update(last, next);
		last = next;
	} while (--total > 0);
}

int A1018AdjGraph::FindMinDist(void) const
{
	int idx = -1;
	int minDist = A1018MaxDist + 1;
	for (int i = 0; i < nodes; ++i)
	{
		if (!visit[i] && dist[i] < minDist)
		{
			minDist = dist[i];
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
		auto distv = dist[v];
		if (distuv < distv)
		{
			dist[v] = distuv;
			lastHops[v].assign(1, next);
		}
		else if (distuv == distv)
		{
			lastHops[v].push_back(next);
		}
	}
}

// rename this to main int PAT
int A1018Func(void)
{
	A1018AdjGraph g;
	g.ReadData();
	g.CalcByDfs();

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
	A1018("data\\A1018-1.txt"); // 3 0->2->3 0
	A1018("data\\A1018-2.txt"); // 2 0->2->4->6->7 0
	A1018("data\\A1018-3.txt"); // 0 0->2->4->6->7 3
	A1018("data\\A1018-4.txt"); // 1 0->6->7->8->9->5 2
}
