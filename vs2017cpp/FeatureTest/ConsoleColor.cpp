#include <windows.h>
#include <iostream>
#include <cstdio>

using namespace std;

void ConsoleColorTest(void)
{
	auto handle = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED);//����Ϊ��ɫ
	printf("red\n");
	SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY);//�ָ�Ĭ��
	printf("default\n");

	SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED);//����Ϊ��ɫ
	cout << "red" << endl;
	SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY);//�ָ�Ĭ��
	cout << "default" << endl;
}