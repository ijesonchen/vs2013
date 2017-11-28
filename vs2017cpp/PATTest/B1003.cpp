#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

/*
1003. ��Ҫͨ����(20)

�÷֣���Ŀ�������
17/20;4/6;1,5

��������Ŀ��������ĵݹ���ʽ
c1+c2+c3��P��T�ָ�Ϊǰ�к�������
c2���м�����һ��A��ǰ��A������ȣ���ʼ��
c3:�м�ÿ����һ��A���������Ӻ�ǰ����ͬ������A
abcΪǰ�к�A�ĸ���
�ݹ飺b!=0, a*b=c

alg1: x �����ⲻͬ 
	�м�ΪPAT��PAAT��ǰ��ֻ��A��ո�

������ȷ�����Զ�����ϵͳ�����������˻�ϲ�Ļظ�����������PAT�ġ�����ȷ�������� ���� ֻҪ������ַ�����������������ϵͳ�����������ȷ��������������𰸴��󡱡�

�õ�������ȷ���������ǣ�

1. �ַ����б������P, A, T�������ַ��������԰��������ַ���
2. �������� xPATx ���ַ��������Ի�á�����ȷ�������� x �����ǿ��ַ����������ǽ�����ĸ A ��ɵ��ַ�����
3. ��� aPbTc ����ȷ�ģ���ô aPbATca Ҳ����ȷ�ģ����� a, b, c �������ǿ��ַ����������ǽ�����ĸ A ��ɵ��ַ�����

���ھ�����ΪPATдһ���Զ����г����ж���Щ�ַ����ǿ��Ի�á�����ȷ���ġ�
�����ʽ�� ÿ�������������1��������������1�и���һ����Ȼ��n (<10)������Ҫ�����ַ���������
������ÿ���ַ���ռһ�У��ַ������Ȳ�����100���Ҳ������ո�

�����ʽ��ÿ���ַ����ļ����ռһ�У�������ַ������Ի�á�����ȷ���������YES���������NO��

����������
8
PAT
PAAT
AAPATAA
AAPAATAAAA
xPATx
PT
Whatever
APAAATAA
���������
YES
YES
YES
YES
NO
NO
NO
NO

ʱ������
400 ms
�ڴ�����
65536 kB
���볤������
8000 B
�������
Standard
����
CHEN, Yue
*/

using namespace std;

bool IsPassAlg1(string& s)
{
	// this is wrong
	size_t p = s.find('P');
	for (size_t i = 0; i < p; ++i)
	{
		if (s[i] != 'A')
		{
			return false;
		}
	}
	if (p == string::npos)
	{
		return false;
	}
	size_t k = s.length() - p;
	if (k >= 3 && s.substr(p, 3) == "PAT")
	{
		p += 3;
		for (size_t i = p; i < s.length(); ++i)
		{
			if (s[i] != 'A')
			{
				return false;
			}
		}
		return true;
	}
	if (k >= 4 && s.substr(p, 4) == "PAAT")
	{
		p += 4;
		for (size_t i = p; i < s.length(); ++i)
		{
			if (s[i] != 'A')
			{
				return false;
			}
		}
		return true;
	}
	return false;
}

bool IsA(const string& s)
{
	return all_of(s.begin(), s.end(), [](char ch) { return ch == 'A'; });
}

bool IsPass(const string& s)
{
	auto n1 = s.find("P");
	auto n2 = s.find("T");
	if (n1 == string::npos || n2 == string::npos || n1 >= n2)
	{
		return false;
	}
	string s1;
	if (n1)
	{
		s1 = s.substr(0, n1);
	}
	auto s2 = s.substr(n1 + 1, n2 - n1 - 1);
	auto s3 = s.substr(n2 + 1, string::npos);
	if (s2.empty())
	{
		return false;
	}
	if (!IsA(s1) ||
		!IsA(s2) ||
		!IsA(s3))
	{
		return false;
	}
	if (s3.length() != s1.length() * s2.length())
	{
		return false;
	}
	return true;
}

void B1003(void)
{
	vector<string> v = {
		"PAT", // yes
		"PAAT",
		"AAPATAA",
		"AAPAATAAAA",
		"AAPAAATAAAAAA",
		"xPATx", // no 
		"PT",
		"Whatever",
		"APAAATAA",
		"TAP", // no 
	};

	for (auto& i : v)
	{
		auto b = IsPass(i);
		if (b)
		{
			cout << "Yes";
		}
		else
		{
			cout << "No";
		}
		cout << endl;
	}
}