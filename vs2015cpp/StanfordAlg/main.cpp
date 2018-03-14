#include "common.h"
#include <iostream>
#include <string>


void MulInteger(void); 
void CountInversions(void);
void QuickSortPartition(void);
void Contraction(void);
void SCC(void);
void DijkstraShortestPath(void);
void DijkstraShortestPath2(void);
void MedianHeap(void);
void TwoSum(void);
void Greedy(void);
// wk10 bitDiff���Խ�24bitת��Ϊ3��4bit, diffΪ256/2�����ܣ�Ȼ���ÿһ��diff����͡�
// ��Ҫ�����Ƿ��ܹ��ӿ��ٶȡ�
void Clustering(void);
void DynamicProgramming(void);
void KnapSack(void);
// wk13: try Johnson alg, correct CLRS 25.3 pseudo code.
void AllPairShortestPath(void);
// wk14
void TravelingSalesmanProblem(void);
void ApproxTravelingSalesmanProblem(void);
void Test2Sat(void);

// for test
void TestKnapsack(void);
void TestClrs22(void);
using namespace std;

void main(void)
{
	auto tp = chrono::high_resolution_clock::now();

	DijkstraShortestPath();

	TimeCost(tp);
	cout << "enter to exit." << endl;
	getchar();
}
