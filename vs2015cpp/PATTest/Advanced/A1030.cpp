/*
1030. Travel Plan (30)

cost 10:55 60min 15:55

���룺���Ի�

�ܽ᣺
	1.�����·��ʱ������dist[]�������·��Ҫ������Dijkstra��¼�ؽ��ٶȿ졣
	2.DFSͨ���ݹ�ʵ�ֱ�������ͨͼ����ѭ�����ಿ�ֵ�ʱ�����Ҫ������Ҫ�ж���visit[]
	3.rebuild�㷨�������⣬pt1δͨ����

sln1: Dijkstra sp
	dfs�������п���·��������SP��֦���ҵ���Сcost
	60min 24/30 pt2 TLE

sln2: ����Dijkstra�м������ؽ����·��
	30min 18/30 pt1 WA pt2 TLE

sln3: �����룬DFS�ݹ���ã�����Ҫforѭ������
	20min dfs������֦pass�� rebuild pt1 WA

sln4: ���rebuild�㷨 20min

A traveler's map gives the distances between cities along the highways, 
together with the cost of each highway. 
Now you are supposed to write a program to help a traveler to
decide the shortest path between his/her starting city and the destination. 
If such a shortest path is not unique, you are supposed to output 
the one with the minimum cost, which is guaranteed to be unique.

Input Specification:

Each input file contains one test case. 
Each case starts with a line containing 4 positive integers N, M, S, and D, 
where N (<=500) is the number of cities (and hence the cities are numbered from 0 to N-1); 
M is the number of highways; 
S and D are the starting and the destination cities, respectively. 
Then M lines follow, each provides the information of a highway, in the format:
City1 City2 Distance Cost
where the numbers are all integers no more than 500, and are separated by a space.

Output Specification:
For each test case, print in one line the cities along the shortest path 
from the starting point to the destination, 
followed by the total distance and the total cost of the path.
The numbers must be separated by a space and there must be no extra space at the end of output.

Sample Input
4 5 0 3
0 1 1 20
1 3 2 30
0 3 4 10
0 2 2 20
2 3 1 20
Sample Output
0 2 3 3 40
*/

#include "..\patMain.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

namespace nsA1030
{
	class Graph
	{
	public:
		void ReadData(void);
		void Dijkstra(void);
		void SearchPath(void);
		void RebuildPath(void);
		void RebuildPath2(void);
	private:
		void Dfs(int u);
		void DfsRebuild(int u);
		void DfsRebuild2(int u, vector<int> p);
		struct Edge
		{
			int u = 0;
			int v = 0;
			int d = 0;
			int c = 0;
			void Reverse(void) { swap(u, v); };
		};
		const int MAXDIST = 1000000;
		// graph info
		vector<vector<Edge>> vAdj;
		int node = 0;
		int start = 0;
		int dst = 0;
		int sp = 0;
		
		// for search
		vector<bool> vVisit;
		vector<int> vDist;
		vector<int> path;
		int cost = 0;
		vector<int> dstPath;
		int dstCost = MAXDIST;

		// rebuild path by Dijkstra
		vector<vector<Edge>> vDijk;
	};
	
	void Graph::ReadData(void)
	{
		int ne;
		cin >> node >> ne >> start >> dst;
		vAdj.assign(node, vector<Edge>());
		for (int i = 0; i < ne; ++i)
		{
			Edge e;
			cin >> e.u >> e.v >> e.d >> e.c;
			vAdj[e.u].push_back(e);
			e.Reverse();
			vAdj[e.u].push_back(e);			
		}
	}

	void Graph::Dijkstra(void)
	{
		vVisit.assign(node, false);
		vDist.assign(node, MAXDIST);
		vDijk.assign(node, vector<Edge>());
		vDist[start] = 0;
		for (int i = 0; i < node; ++i)
		{
			int u = 0;
			int minDist = MAXDIST;
			for (int i = 1; i < node; ++i)
			{
				if (!vVisit[i] && vDist[i] < minDist)
				{
					u = i;
					minDist = vDist[i];
				}
			}
			vVisit[u] = true;
			auto du = vDist[u];
			auto& uAdj = vAdj[u];
			for (auto& e : uAdj)
			{
				auto v = e.v;
				if (vVisit[v])
				{
					continue;
				}
				auto duv = du + e.d;
				if (duv < vDist[v])
				{
					vDist[v] = duv;
					vDijk[v].clear();
				}
				if (duv <= vDist[v])
				{
					auto e2 = e;
					e2.Reverse();
					vDijk[v].push_back(e2);
				}
			}
		}
	}
	
	void Graph::Dfs(int u)
	{
		if (u == dst)
		{
			if (cost < dstCost)
			{
				dstPath = path;
				dstCost = cost;
			}
			return;
		}
		auto& uAdj = vAdj[u];
		auto ud = vDist[u];
		for (auto& e : uAdj)
		{
			if (vVisit[e.v] || ud + e.d > vDist[e.v])
			{
				continue;
			}
			vVisit[e.v] = true;
			path.push_back(e.v);
			cost += e.c;
			Dfs(e.v);
			vVisit[e.v] = false;
			path.pop_back();
			cost -= e.c;
		}
	}

	void Graph::SearchPath(void)
	{
		vVisit.assign(node, false);
		vVisit[start] = true;
		path.push_back(start);
		cost = 0;
		Dfs(start);
		for (auto v : dstPath)
		{
			cout << v << " ";
		}
		cout << vDist[dst] << " " << dstCost << endl;
	}

	void Graph::DfsRebuild(int u)
	{
		if (u == start)
		{
			if (cost < dstCost)
			{
				dstPath = path;
				dstCost = cost;
			}
			return;
		}
		auto& uAdj = vDijk[u];
		for (auto& e : uAdj)
		{
			path.push_back(e.v);
			cost += e.c;
			DfsRebuild(e.v);
			path.pop_back();
			cost -= e.c;
		}
	}

	void Graph::RebuildPath(void)
	{
		path.push_back(dst);
		cost = 0;
		DfsRebuild(dst);
		for (auto it = dstPath.rbegin(); it != dstPath.rend(); ++it)
		{
			cout << *it << " ";
		}
		cout << vDist[dst] << " " << dstCost << endl;
	}

	void Graph::DfsRebuild2(int u, vector<int> p)
	{
		p.push_back(u);
		if (u == start)
		{
			if (cost < dstCost)
			{
				dstPath = p;
				dstCost = cost;
			}
			return;
		}
		auto& uAdj = vDijk[u];
		for (auto& e : uAdj)
		{
			path.push_back(e.v);
			cost += e.c;
			DfsRebuild2(e.v, p);
			path.pop_back();
			cost -= e.c;
		}
	}

	void Graph::RebuildPath2(void)
	{
		path.push_back(dst);
		cost = 0;
		vector<int> p;
		DfsRebuild2(dst, p);
		for (auto it = dstPath.rbegin(); it != dstPath.rend(); ++it)
		{
			cout << *it << " ";
		}
		cout << vDist[dst] << " " << dstCost << endl;
	}
}

// rename this to main int PAT
int A1030Func(void)
{
	using namespace nsA1030;
	Graph g;
	g.ReadData();
	g.Dijkstra();
	g.RebuildPath2();
	return 0;
}


void A1030(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1030Func();
	cout << endl;
}

void A1030(void)
{
	A1030("data\\A1030-1.txt"); // 
}
