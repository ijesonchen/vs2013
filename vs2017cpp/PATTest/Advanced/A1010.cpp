/*
1010. Radix (25)
cost: 15:10

���ֲ������׳�ʱ�����벻�Ͻ�
�쳣���ԣ���ͷû�з���+-��radix ���Ϊ 0x7fffffff 
���ִ𰸣�14 17 18 19 2 impossible
pt0��[5,7]
	�����ҵ��Ľ�����ԣ������Ҳ�������������������
��������⣬��Ϊ������int64_t��ʾ�����
pt0�����⣺�Ʋ�����Ϊ�����ж�����������A1010-8.txt
	����Ҫ����high��ֵ��ȡ��minBase��N1���нϴ��Ϊ��׼��
	��֤ȡ������С��ֵ��

�ܽ᣺
	1. Advanced�����㷨�����ǲ����ر��ӡ�
	�����ȿ���һ�����������������ø��ӷ�ʽ��
	���ǳ�������ͼ
		���磬10λN���ƣ���int64_t�϶���ʾ���ˡ����Ǵ����˷����ӣ�����ʵ��testcaseû����ô�������
		���ǽ���ת����ʱ����ܳ�����Χ����������ų�����
	2. testcase���Ƿǳ��Ͻ�����ʱ�����ֲ�Ψһ�������������Ŀû�н�����
	��ʱ�򰴳����뷨������С�
		����PT0�����Ƕ����������ԣ�����ֻȡ��С�Ľ��ơ����Զ��������ҵ��ϴ�ֵ
	3. ��Χ����ʱ�����������С��Χ
		��Χ���󣬻��ж������������´���PT0
	4. �����и���Сֵ������ֱ�Ӵ�2��ʼ��
	5. �������̳������⣬ֱ�����쳣�Ϳ��ԡ������Է�ӳ�ڽ���ϡ�


sln1:
	n1, r
	n2, ?
	n2, [rmin, rmax] -> n3,r  n3?n1  binsearch

	void div(x,y,&a,&b): x/y=a...b
	dst RedixConv(src, r1, r2): src,r1 -> dst, r2
sln2: vector��Ϊ����������
	ʹ��һ��vector<int>��Ϊ�м������бȽ�
	����19/25 pt10,11��3,4,5,7 ����
	�ݹ�17/25 pt0,10,11,3,4,5,7,8 ����
    * �����ˣ��Ӵ����޸����radix��
	�ݹ�2,24/25 pt0 ����
	���� 17/25 pt14,17,18,19,2,7��ʱ
sln3: deque��Ϊ����������
	radix����Ϊ0x7fffffff
	������16/25 pt0,19 ���� pt14,17,18,2,7��ʱ
	���֣�23/25 pt0,19 ����
	�����������
	������17/25 pt14,17,18,19,2,7��ʱ
	���֣�24/25 pt0 ����
sln4��ֱ����int64_t��ʾ�����

Given a pair of positive integers, for example, 6 
and 110, can this equation 6 = 110 be true? The answer 
is "yes", if 6 is a decimal number and 110 is a 
binary number.

Now for any pair of positive integers N1 and N2, your 
task is to find the radix of one number while that of 
the other is given.

Input Specification:

Each input file contains one test case. Each case 
occupies a line which contains 4 positive integers:
N1 N2 tag radix
Here N1 and N2 each has no more than 10 digits. A digit
is less than its radix and is chosen from the set 
{0-9, a-z} where 0-9 represent the decimal numbers 0-9,
and a-z represent the decimal numbers 10-35. The last
number "radix" is the radix of N1 if "tag" is 1, or of 
N2 if "tag" is 2.

Output Specification:

For each test case, print in one line the radix of the 
other number so that the equation N1 = N2 is true. If 
the equation is impossible, print "Impossible". If the
solution is not unique, output the smallest possible radix.

Sample Input 1:
6 110 1 10
Sample Output 1:
2
Sample Input 2:
1 ab 1 2
Sample Output 2:
Impossible
*/

#include "..\patMain.h"
#include <sstream>

#include <iostream>
#include <string>
#include <vector>
#include <cstdint>
#include <deque>
#include <algorithm>

using namespace std;


//////////////////////////////////////////////////////////////////////////
// common function
int A1010ConvCh2I(const char c)
{
	if (c >= '0' && c <= '9') { return c - '0'; }
	else if (c >= 'a' && c <= 'z') { return c - 'a' + 10; }
	else if (c >= 'A' && c <= 'Z') { return c - 'A' + 10; }
	else { throw 1; return -1; }
}

int A1010MinBase(const string& s)
{
	int minBase = 1;
	for (auto c : s)
	{
		auto i = A1010ConvCh2I(c);
		if (i > minBase) { minBase = i; }
	}
	if (minBase > 35) { throw 1; }
	return minBase + 1;
}

//////////////////////////////////////////////////////////////////////////
// convert to int64_t
int64_t A1010Conv2Int64(const std::string& s, int radix)
{
	int carry = A1010ConvCh2I(s.front());
	int64_t result = carry;
	auto len = s.length();
	for (size_t i = 1; i < len; ++i)
	{
		result *= radix;
		if (result < 0)
		{
			return -1;
		}
		int n = A1010ConvCh2I(s[i]);
		result += n;
	}
	return result;
}

int A1010Func3(void)
{
	string s1, s2;
	int tag, b1;
	cin >> s1 >> s2 >> tag >> b1;

	if (tag == 2) { swap(s1, s2); };
	auto l1 = A1010Conv2Int64(s1, b1);
	int64_t low = A1010MinBase(s2);
	int64_t high = std::max(low, l1) + 1;
	int64_t mid = 0;
	while (low <= high)
	{
		mid = (high - low) / 2 + low;
		auto l2 = A1010Conv2Int64(s2, mid);
		if (l2 == l1)
		{
			cout << mid << endl;
			return 0;
		}
		if (l2 < 0 || l2 > l1)
		{
			high = mid - 1;
		}
		else
		{
			low = mid + 1;
		}
	}

	cout << "Impossible" << endl;
	return 0;
}


//////////////////////////////////////////////////////////////////////////
// deque large int

class A1010LI
{
public:
	A1010LI(int n) { result.push_front(n); };
	using ShortInt = uint32_t;
	using LongInt = uint64_t;

	A1010LI& operator*(A1010LI::ShortInt n);
	A1010LI& operator+(A1010LI::ShortInt n);
	bool operator==(const A1010LI& other) { return result == other.result; }
	bool operator<(const A1010LI& other);

	uint64_t A1010LI::ToInt64(void);
private:
	const int shift = sizeof(ShortInt) * 8;
	deque<ShortInt> result;
	deque<LongInt> assist;
};


A1010LI& A1010LI::operator*(A1010LI::ShortInt n)
{
	assist.assign(result.begin(), result.end());
	for (auto& it : assist)
	{
		it *= n;
	}
	ShortInt carry = 0;
	LongInt ass = 0;
	auto len = assist.size();
	for (int i = (int)len - 1; i >= 0; --i)
	{
		ass = assist[i] + carry;
		result[i] = (ShortInt)ass;
		carry = (ShortInt)(ass >> shift);
	}
	if (carry)
	{
		result.push_front(carry);
	}
	return *this;
}

A1010LI& A1010LI::operator+(A1010LI::ShortInt n)
{
	assist.assign(result.begin(), result.end());
	ShortInt carry = n;
	LongInt ass = 0;
	for (auto i = (int)assist.size() - 1; i >= 0; ++i)
	{
		ass = assist[i] + carry;
		result[i] = (ShortInt)ass;
		carry = (ShortInt)(ass >> shift);
		if (!carry)
		{
			break;
		}
	}
	if (carry)
	{
		result.push_front(carry);
	}
	return *this;
}


bool A1010LI::operator<(const A1010LI& other) 
{ 
	if (result.size() < other.result.size())
	{
		return true;
	}
	else if (result.size() == other.result.size())
	{
		return result < other.result;
	}
	else
	{
		return false;
	}
}


uint64_t A1010LI::ToInt64(void)
{
	if (result.size() * sizeof(ShortInt) >= sizeof(LongInt))
	{
		throw 0;
	}
	uint64_t u64 = 0;
	ShortInt* p = (ShortInt*)&u64;
	auto len = result.size();
	for (size_t i = 0; i < len; ++i)
	{
		p[i] = result[len - 1 - i];
	}
	return u64;
}

A1010LI A1010Str2LI(const string& s, int64_t base)
{
	int n = A1010ConvCh2I(s.front());
	A1010LI li(n);
	for (size_t i = 1; i < s.length(); ++i)
	{
		n = A1010ConvCh2I(s[i]);
		li * (A1010LI::ShortInt)base;
		li + n;
	}
	
	return li;
}

int A1010Func2(void)
{
	string s1, s2;
	int tag, b1;
	cin >> s1 >> s2 >> tag >> b1;

	if (tag == 2) { swap(s1, s2); };
	auto l1 = A1010Str2LI(s1, b1);
	int64_t low = A1010MinBase(s2);
	int64_t high = 0x7fffffff;
	int64_t mid = 0;
	while (low <= high)
	{
		mid = (high - low) / 2 + low;
		auto l2 = A1010Str2LI(s2, mid);
		if (l2 == l1)
		{
			cout << mid << endl;
			return 0;
		}
		else if (l2 < l1)
		{
			low = mid + 1;
		}
		else
		{
			high = mid - 1;
		}
	}

	cout << "Impossible" << endl;
	return 0;
}
//////////////////////////////////////////////////////////////////////////
// vector -> large int

class A1010LargeInt
{
public:
	bool LoadFrom(const string& s, int nBase);

	A1010LargeInt& operator*(const int n);
	A1010LargeInt& operator+(const int n);

	bool operator==(const A1010LargeInt& other);
	bool operator<(const A1010LargeInt& other);

	uint64_t ToInt64(void);
private:
	int base;
	using ShortInt = uint32_t;
	using LongInt = uint64_t;
	const int Shift = sizeof(ShortInt) * 8;
	vector<ShortInt> result;
	vector<LongInt> assist;
};


bool A1010LargeInt::LoadFrom(const string& s, int nBase)
{
	base = nBase;

	int n = 0;
	n = A1010ConvCh2I(s.front());
	if (n < 0 || n >= base)
	{
		throw 1;
		return false;
	}
	result.clear();
	result.push_back(n);

	auto len = s.length();
	for (size_t i = 1; i < len; ++i)
	{
		n = A1010ConvCh2I(s[i]);
		if (n < 0 || n >= base)
		{
			throw 1;
			return false;
		}
		operator*(base);
		operator+(n);
	}
	return true;
}

A1010LargeInt& A1010LargeInt::operator*(const int n)
{
	assist.assign(result.begin(), result.end());
	for (auto& i : assist)
	{
		i *= n;
	}
	ShortInt carry = 0;
	LongInt  ass = 0;
	auto len = result.size();
	for (auto i = 0; i < len; ++i)
	{
		ass = assist[i] + carry;
		result[i] = (ShortInt)ass;
		carry = (ShortInt)(ass >> Shift);
	}
	if (carry)
	{
		result.push_back(carry);
	}
	return *this;
}


A1010LargeInt& A1010LargeInt::operator+(const int n)
{
	assist.assign(result.begin(), result.end());
	ShortInt carry = n;
	LongInt  ass = 0;
	auto len = result.size();
	for (auto i = 0; i < len; ++i)
	{
		ass = assist[i] + carry;
		result[i] = (ShortInt)ass;
		carry = (ShortInt)(ass >> Shift);
		if (!carry)
		{
			break;
		}
	}
	if (carry)
	{
		result.push_back(carry);
	}
	return *this;
}

bool A1010LargeInt::operator==(const A1010LargeInt& other)
{
	return result == other.result;
}

bool A1010LargeInt::operator<(const A1010LargeInt& other)
{
	if (operator==(other))
	{
		return false;
	}
	auto s1 = result.size();
	auto s2 = other.result.size();
	if (s1 != s2)
	{
		return s1 < s2;
	}
	vector<ShortInt> v1(result.rbegin(), result.rend());
	vector<ShortInt> v2(other.result.rbegin(), other.result.rend());
	return v1 < v2;
}

uint64_t A1010LargeInt::ToInt64(void)
{
	if (result.size() * sizeof(ShortInt) >= sizeof(LongInt))
	{
		throw 0;
	}
	uint64_t u64 = 0;
	ShortInt* p = (ShortInt*)&u64;
	for (int i = 0; i < result.size(); ++i)
	{
		p[i] = result[i];
	}
	return u64;
}

// rename this to main int PAT
int A1010Func1(void)
{
	string s1, s2;
	int tag, b1;
	cin >> s1 >> s2 >> tag >> b1;
	if (tag == 2)
	{
		swap(s1, s2);
	}
	A1010LargeInt l1;
	l1.LoadFrom(s1, b1);
	A1010LargeInt l2;
	int64_t b2low = A1010MinBase(s2);
	int64_t b2high = 0x7fffffff;
	int64_t mid = 0;
	while (b2low <= b2high)
	{
		mid = (b2high - b2low) / 2 + b2low;
		l2.LoadFrom(s2, (int)mid);
		if (l2 == l1)
		{
			cout << mid << endl;
			return 0;
		}
		else if (l2 < l1)
		{
			b2low = mid + 1;
		}
		else
		{
			b2high = mid - 1;
		}
	}
	cout << "Impossible" << endl;
	return 0;
}

//////////////////////////////////////////////////////////////////////////
// test for binary search

class A1010V
{
public:
	int operator[](int n) { return n; }
};

const int64_t A1010BinSearchMax = 1000;
int64_t A1010BinSearch(A1010V v, const int n)
{
	int low = 0;
	int high = A1010BinSearchMax - 1;
	int mid = (high - low) / 2 + low;
	while (low <= high)
	{
		mid = (high - low) / 2 + low;
		if (n == v[mid])
		{
			return mid;
		}
		else if(n > v[mid])
		{
			low = mid + 1;
		}
		else
		{
			high = mid - 1;
		}
	}
	throw 0;
	return 0;
}

int64_t A1010BinSearch2(A1010V v, const int n)
{
	int64_t b2low = 0;
	int64_t b2high = A1010BinSearchMax - 1;
	int64_t mid = 0;
	int a = 0;
	while (b2low <= b2high)
	{
		mid = (b2high - b2low) / 2 + b2low;
		a = (int)v[mid];
		if (n == a)
		{
			cout << mid << endl;
			return mid;
		}
		else if (n > a)
		{
			b2low = mid + 1;
		}
		else
		{
			b2high = mid - 1;
		}
	}
	throw 0;
	return 0;
}

void A1010BinSearchTest(void)
{
	A1010V v;
	for (int64_t i = 1; i < A1010BinSearchMax; ++i)
	{
		auto ret = A1010BinSearch2(v, (int)i);
		if (ret != i)
		{
			cout << "error: " << i << " ret: " << ret << endl;
		}
	}
	cout << "passed." << endl;
}

//////////////////////////////////////////////////////////////////////////
// test funcion
void A1010(const string& fn)
{
	cout << fn << endl;
	RedirCin(fn);
	A1010Func3();
	cout << endl;
}

void A1010Comp(const string& s1, const string& s2)
{
	A1010LargeInt l1, l2;
	l1.LoadFrom(s1, 16);
	l2.LoadFrom(s2, 16);
	cout << s1 << " comp " << s2 << " : " << (l1 < l2) << endl;
}

uint64_t A1010StrConv1(const string& s, int radix)
{
	auto l1 = A1010Str2LI(s, radix);
	return l1.ToInt64();
}

uint64_t A1010StrConv2(const string& s, int radix)
{
	A1010LargeInt l1;
	l1.LoadFrom(s, radix);
	return l1.ToInt64();
}

void A1010TestStrConv(void)
{
	char buf[1024];
	stringstream ss;

	int minBase = 2;
	int maxBase = 36;
	int maxInt = 1000010000;
	for (uint64_t i = 1000000000; i < maxInt; ++i)
	{
		cout << "number: " << i << endl;
		for (int j = minBase; j <= maxBase; ++j)
		{
			string s = _ltoa(i, buf, j);

			char* p2ll = nullptr;			
			auto a1 = A1010StrConv1(s, j);
			auto a2 = A1010StrConv2(s, j);
			if (a1 == i && a2 == i)
			{
				continue;
			}
			cout << "i a1 a2: " << i << " " << a1 << " " << a2 << endl;
			abort();
		}
	}
}

void A1010(void)
{
	A1010("data\\A1010-1.txt"); // 2
	A1010("data\\A1010-2.txt"); // Impossible
	A1010("data\\A1010-3.txt"); // 36
	A1010("data\\A1010-4.txt"); // 10
	A1010("data\\A1010-5.txt"); // Impossible
	A1010("data\\A1010-6.txt"); // 3
	A1010("data\\A1010-7.txt"); // 35
	A1010("data\\A1010-8.txt"); // 2
	A1010("data\\A1010-9.txt"); // 2147483647
}

