#include <iostream>
#include <atomic>
#include <thread>
#include <chrono>
#include <cstdlib>
#include <string>


#include "socketLinux.h"
#include "socketWindows.h"

using namespace std;
using namespace chrono;

extern const int RECVCHECKTV = 1024;
extern unsigned short Port = 27015;
atomic_uint bufIdx = 0;



int main(int argc, char** argv)
{
	cout << "exec [ipaddr packageSize packageCount]" << endl;
	cout << "if param is set, then send mode, otherwise recv mode." << endl;

	if (argc == 1)
	{
		Recv();
	}
	else if (argc == 4)
	{
		string targetIp = argv[1];
		auto nPackSize = atoi(argv[2]);
		auto nPackCount = atoi(argv[3]);
		cout << "ip " << targetIp << ",size " << nPackSize << ", count " << nPackCount << endl;
		Send(targetIp, nPackSize, nPackCount);
	}
	else
	{
		cout << "param error" << endl;
		return -1;
	}
	return 0;
}