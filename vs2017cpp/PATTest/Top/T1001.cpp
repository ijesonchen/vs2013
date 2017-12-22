/*
1001. Battle Over Cities - Hard Version (35)

sln1: ���+BFS, MST
	19/35 pt2,3 �쳣(buildCostδ�ҵ�·��)�� pt5 ��ʱ
	1. ͼ����·�����ٻ�·���ֱ𱣴�
		vector<vector<int>> adjGood
		vector<vector<Edge>> adjBad
	2. ���������i��
		a) ��Ǹó��к�BFS��ʣ���������ͨ����
			map<int, vector<int>> mapCC
		b) ��ͨ����Ϊ1�������ؽ�
		c) ����������ǿ��ͨ�������ӻٻ�·����ѡȡ
		��̵�����·������¼cost��������ͨ����ͼ��
		d) ����ͨ����ͼ����С����������Ϊi���ж�Ӧ�Ļ���
	3. ��¼��߻��Ѽ���Ӧ����(ͬһ���ѿ��ܶ����

It is vitally important to have all the cities connected by 
highways in a war. If a city is conquered by the enemy, all 
the highways from/toward that city will be closed. To keep
the rest of the cities connected, we must repair some highways
with the minimum cost. On the other hand, if losing a city
will cost us too much to rebuild the connection, we must pay
more attention to that city.

Given the map of cities which have all the destroyed and 
remaining highways marked, you are supposed to point out the 
city to which we must pay the most attention.

Input Specification:

Each input file contains one test case. Each case starts with
a line containing 2 numbers N (<=500), and M, which are the
total number of cities, and the number of highways, respectively. 
Then M lines follow, each describes a highway by 4 integers:

City1 City2 Cost Status
where City1 and City2 are the numbers of the cities the highway
connects (the cities are numbered from 1 to N), Cost is the effort
taken to repair that highway if necessary, and Status is either 0,
meaning that highway is destroyed, or 1, meaning that highway 
is in use.

Note: It is guaranteed that the whole country was connected 
before the war.

Output Specification:

For each test case, just print in a line the city we must protest 
the most, that is, it will take us the maximum effort to rebuild 
the connection if that city is conquered by the enemy.

In case there is more than one city to be printed, output them 
in increasing order of the city numbers, separated by one space,
but no extra space at the end of the line. In case there is no 
need to repair any highway at all, simply output 0.

Sample Input 1:
4 5
1 2 1 1
1 3 1 1
2 3 1 0
2 4 1 1
3 4 1 0
Sample Output 1:
1 2

Sample Input 2:
4 5
1 2 1 1
1 3 1 1
2 3 1 0
2 4 1 1
3 4 2 1
Sample Output 2:
0
*/
#include "..\patMain.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <deque>

using namespace std;

struct T1001E
{
	int u = 0;
	int v = 0;
	int c = 0;
	bool ok = false;
	T1001E(int _u, int _v, int _c, bool _ok)
		:u(_u), v(_v), c(_c), ok(_ok) {};

	bool operator<(const T1001E& e)
	{
		return c < e.c;
	}
};

bool T1001ELess(T1001E* const p1, T1001E* const p2)
{
	return *p1 < *p2;
}

class T1001G
{
public:
	void Read(void);
	void SearchCity();
private:
	// do not return 0;
	int CityCost(int iCity);
	int BuildCost(vector<int>& v1, vector<int>& v2);
	void Bfs(int start);

	// for BFS group
	void ResetBfsAssist(int ibad);
	int badCity = -1;
	unordered_map<int, vector<int>> mapCC;
	vector<bool> visited;

	vector<vector<int>> adjGood;
	vector<vector<T1001E>> adjBad;
	int cityCount = 0;
};

class T1001Mst
{
	void SetData(const vector<T1001E>* const p)
	{
		pvtEdges = p;
	}

	int PrimWithMinHeap(void);
	int KruskalWithUnionfind(void);
private:
	vector<T1001E>* pvtEdges;
};


void T1001G::Read(void)
{
	int n, m;
	cin >> n >> m;
	cityCount = n;
	adjGood.assign(n, vector<int>());
	adjBad.assign(n, vector<T1001E>());
	int u, v, c;
	bool ok;
	for (int i = 0; i < m; ++i)
	{
		cin >> u >> v >> c >> ok;
		if (u == v) { continue; }
		--u; --v;
		if (ok)
		{
			adjGood[u].emplace_back(v);
			adjGood[v].emplace_back(u);
		}
		else
		{
			adjBad[u].emplace_back(T1001E(u, v, c, ok));
			adjBad[v].emplace_back(T1001E(v, u, c, ok));
		}
	}
}

void T1001G::SearchCity(void)
{
	int maxCost = 0;
	int cost = 0;
	vector<int> cities;
	for (int i = 0; i < cityCount; ++i)
	{
		cost = CityCost(i);
		if (cost > maxCost)
		{
			maxCost = cost;
			cities.clear();
			cities.push_back(i);
		}
		else if (cost == maxCost)
		{
			cities.push_back(i);
		}
	}

	// output result
	if (cities.empty())
	{
		cout << "0" << endl;
		return;
	}
	set<int> s;
	for (auto i : cities)
	{
		s.insert(i);
	}
	auto its = s.begin();
	cout << *its + 1;
	for (++its; its != s.end(); ++its)
	{
		cout << " " << *its + 1;
	}
	cout << endl;
}

void T1001G::Bfs(int start)
{
	vector<int> vleft;
	vleft.push_back(start);
	while (!vleft.empty())
	{
		int next = vleft.back();
		vleft.pop_back();
		auto& subs = adjGood[next];
		for (auto v : subs)
		{
			if (visited[v])
			{
				continue;
			}
			visited[v] = true;
			vleft.push_back(v);
			mapCC[start].push_back(v);
		}
	}
}

int T1001G::CityCost(int iCity)
{
	ResetBfsAssist(iCity);
	for (int i = 0; i < cityCount; ++i)
	{
		if (i == badCity) { continue; }
		if (!visited[i])
		{
			visited[i] = true;
			mapCC[i].push_back(i);
			Bfs(i);
		}
	}

	int msize = (int)mapCC.size();
	if (msize == 1)
	{
		return -1;
	}
	// mapCC -> graphCC
	int buildcost = 0;
	vector<T1001E> groupEdges;
	vector<vector<int>*> vCC;
	for (auto& it : mapCC)
	{
		vCC.push_back(&(it.second));
	}
	int nCC = (int)vCC.size();
	for (int i = 0; i < nCC; ++i)
	{
		for (int j = i + 1; j < nCC; ++j)
		{
			buildcost = BuildCost(*vCC[i], *vCC[j]);
			groupEdges.push_back(T1001E(i, j, buildcost, true));
		}
	}
	// MST for groupCC
	vector<T1001E*> pgEdges;
	for (auto& e : groupEdges)
	{
		pgEdges.push_back(&e);
	}
	sort(pgEdges.begin(), pgEdges.end(), T1001ELess);
	int totalCost = 0;

	unordered_set<int> setGroup;
	bool hasU, hasV;
	int geSize = (int)pgEdges.size();
	for (int i = 0; i < geSize; ++i)
	{
		T1001E& e = *pgEdges[i];
		hasU = setGroup.find(e.u) != setGroup.end();
		hasV = setGroup.find(e.v) != setGroup.end();
		if (hasU && hasV) { continue; }
		totalCost += e.c;
		if (!hasU) { setGroup.insert(e.u); }
		if (!hasV) { setGroup.insert(e.v); }
	}
	return totalCost;
}

int T1001G::BuildCost(vector<int>& v1, vector<int>& v2)
{
	int cost = 0x7FFFFFFF;
	for (auto const u : v1)
	{
		vector<T1001E>& edges = adjBad[u];
		for (const auto e : edges)
		{
			if (e.v == badCity)
			{
				continue;
			}
			for (const auto v : v2)
			{
				if (e.v == v)
				{
					if (e.c < cost)
					{
						cost = e.c;
					}
				}
			}
		}
	}
	if (cost == 0x7FFFFFFF)
	{
		abort();
	}
	return cost;
}


void T1001G::ResetBfsAssist(int ibad)
{
	mapCC.clear();
	visited.assign(cityCount, false);
	badCity = ibad;
	visited[badCity] = true;
}


int T1001Mst::PrimWithMinHeap(void)
{
	return -1;
}

int T1001Mst::KruskalWithUnionfind(void)
{
	return -1;
}

// rename this to main int PAT
int T1001Func(void)
{
	T1001G g;
	g.Read();
	g.SearchCity();
	return 0;
}


void T1001(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	T1001Func();
	cout << endl;
}

void T1001(void)
{
	T1001("data\\T1001-1.txt"); // 1 2
	T1001("data\\T1001-2.txt"); // 0
	T1001("data\\T1001-3.txt"); // 3
}
