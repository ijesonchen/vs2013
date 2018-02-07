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
#include <sstream>
#include <vector>

using namespace std;

namespace nsTestGraphAllPath
{
	class GraphAdj
	{
	public:
		void Read(void);
		void PrintDfs(int start);
		void DfsPath(void);
		void DfsAllPath(void);
		void PrintAllPath(void);
		void PrintPath(void);
	private:
		int nNode;
		vector<vector<int>> vvAdj;
		vector<bool> vVisit;
		vector<int> vPath;
		int nPath;
	};

	void GraphAdj::PrintPath(void)
	{
		++nPath;
		for (auto v : vPath)
		{
			cout << v << " ";
		}
		cout << endl;
	}

	void GraphAdj::Read(void)
	{
		cin >> nNode;
		vvAdj.assign(nNode, vector<int>());
		int u, v;
		while (cin >> u >> v)
		{
			if (u == v)
			{
				continue;
			}
			auto& vAdju = vvAdj[u];
			if (find(vAdju.begin(), vAdju.end(), v) == vAdju.end())
			{
				vAdju.push_back(v);
			}
			auto& vAdjv = vvAdj[v];
			if (find(vAdjv.begin(), vAdjv.end(), u) == vAdjv.end())
			{
				vAdjv.push_back(u);
			}
		}
	}

	void GraphAdj::DfsPath()
	{
		auto& vAdj = vvAdj[vPath.back()];
		size_t nv = 0;
		for (auto v : vAdj)
		{
			if (vVisit[v])
			{
				++nv;
				continue;
			}
			vVisit[v] = true;
			vPath.push_back(v);
			DfsPath();
			vPath.pop_back();
		}
		if (nv == vAdj.size())
		{
			PrintPath();
		}
	}

	void GraphAdj::DfsAllPath()
	{
		auto& vAdj = vvAdj[vPath.back()];
		size_t nv = 0;
		for (auto v : vAdj)
		{
			if (vVisit[v])
			{
				++nv;
				continue;
			}
			vVisit[v] = true;
			vPath.push_back(v);
			DfsAllPath();
			vPath.pop_back();
			vVisit[v] = false;
		}
		if (nv == vAdj.size())
		{
			PrintPath();
		}
	}

	void GraphAdj::PrintDfs(int start)
	{
		vVisit.assign(nNode, false);
		nPath = 0;
		vPath.clear();
		vPath.push_back(start);
		vVisit[start] = true;
		DfsPath();
		cout << "\t** total path: " << nPath << endl;
	}

	void GraphAdj::PrintAllPath(void)
	{
		vVisit.assign(nNode, false);
		nPath = 0;
		vPath.clear();
		vPath.push_back(0);
		vVisit[0] = true;
		DfsAllPath();
		cout << "\t** total path: " << nPath << endl;
	}

	void MainFunc(void)
	{
		GraphAdj g;
		g.Read();
		cout << "\t** dfs:" << endl;
		g.PrintDfs(0);
		cout << "\t** all path:" << endl;
		g.PrintAllPath();
	}
}

void TestGraphAllPath(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	nsTestGraphAllPath::MainFunc();
	cout << endl;
}

void TestGraphAllPath(void)
{
	TestGraphAllPath("data\\TestGraphAllPath-1.TXT"); // 
	TestGraphAllPath("data\\TestGraphAllPath-2.TXT"); // 
}

