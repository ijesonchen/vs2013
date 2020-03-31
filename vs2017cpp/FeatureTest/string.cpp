#include <string>
#include <iostream>

void StringTest(void);

using namespace std;

/*
0. string�ڲ��洢���1�ֽڣ�����data(), c_str()ת��Ϊ0β��char*��
1. �Ż�������ʵ��Ԥ����16�ֽ�ջ�ռ䣬ĩβ��0������15����ֱ��ʹ�á�
2. (p, len)����´���ڴ档
*/

void StringTest(void) {
	int len = 16;
	auto p = new char[len];
	for (int i = 0; i < len; i++) {
		p[i] = 'a' + i;
	}
	string s(p, len); 
	printf("p %p s %p %p %zd\n", p, s.data(), s.c_str(), s.length());
	delete []p;
	p = s.data();
	printf("hex %x %x %x %x %x\n", p[0], p[1], p[2], p[3], p[len]);
	cout << s << endl;
}