/*
debugģʽ�¶���ջ���
releaseģʽ�£�TailRecurFunc�Ż�Ϊβ�ݹ鲻�����
*/

#include <iostream>


using namespace std;

using TailRecurType = uint64_t;

TailRecurType NonTailRecurFunc(TailRecurType n)
{
	if (n <= 1) return 1;

	return (n * NonTailRecurFunc(n - 1));
}

TailRecurType TailRecurFunc(TailRecurType n, TailRecurType res)
{
	if (n <= 1) return res;

	return TailRecurFunc(n - 1, n * res);
}


void TailRecurTest(void)
{
	auto n = 100;
	auto n2 = TailRecurFunc(n, 1);
	cout << "TailRecurFunc " << n2 << endl;
	auto n1 = NonTailRecurFunc(n);
	cout << "NonTailRecurFunc " << n1 << endl;
}