#include <locale>
#include <iostream>
#include <string>
#include <algorithm>
#include <memory>
#include <cstdlib>
#include <windows.h>

void LocaleTest(void);
//////////////////////////////////////////////////////////////////////////

/*
win10 , vs2017 15.3 locale works with : chs, .936, zh-CN, chinese-simplified, CHN, CHS, but not china
Language Strings
https://msdn.microsoft.com/en-us/library/39cwe7zf.aspx
Country/Region Strings
https://msdn.microsoft.com/en-us/library/cdax410z.aspx

*/

using namespace std;

void SetLocaleAndIsDigit()
{
	setlocale(LC_ALL, "C");
	cout << "*���Ĳ���*" << endl;

	string id = "���";
	id = id.substr(0, find_if(id.begin(), id.end(), [](char ch) { return std::isdigit(ch, locale("chs")); }) - id.begin());
}

/*
1. cout locale test��IDE/����ϵͳ�汾��setlocale���ã�cout�ܷ�����������ġ�
*�����ϵͳ�޹ء�vs15 chs, win10�±��룬win10������08R2�쳣��
** win10 / 08R2 ������setlocale��ֱ��cout���Ŀ���������ʾ��

| vs/os        | locale  | cout |
| ------------ | ------- | ---- |
| 15/17, WIN10 | C / chs | V    |
| 15, 08R2     | C       | V    |
| 15, 08R2     | chs     | X    |

2. isdigitֱ�Ӵ���ansi�����ַ��������⡣���Կ���ʹ��std::isdigit(char, std::local&)��
find_if�е��б�ʽʹ��lambda���ʽ����:  [](const char ch){ return std::isdigit(ch, std::local("chs")); }

3. mbstowcs/wcstombs��locale��ء�������"chs"������ȷת����

4. ansi��Unicodeת������ʹ��ƽ̨��غ�����
	windows����ʹ��WideCharToMultiByte�������Զ���ȡϵͳ�ַ�������
	linux����ʹ��iconv
	����������
		mbstowcs/wcstombsȫ��locale��أ� mbstowcs_l����ָ��locale���ƺ���΢�����չ
		wstring_convert��C++11��׼���������⣺a)�ٶ���Խ���
											b)��Ҫ�õ�codecvtͷ�ļ���gcc 5.2��ʼ֧�֣���Ҫclang
    ** gcc 5.2 ��ʼ֧��codecvt
*/


std::wstring DecAnsi(const std::string& strAnsi)
{
	const char* pAnsi = strAnsi.c_str();
	size_t len = mbstowcs(nullptr, pAnsi, 0) + 1; // should work with locale "chs"
	if (len == (size_t)-1)
	{
		return L"";
	}
	wchar_t* wp = new wchar_t[len];
	std::unique_ptr<wchar_t> wup(wp);
	wp[0] = 0;
	wp[len - 1] = 0;

	len = mbstowcs(wp, pAnsi, len);
	if (len == (size_t)-1)
	{
		return L"";
	}
	return wp;
}



std::string EncAnsiWin(const std::wstring& strUnicode)
{
	const wchar_t* pUnicode = strUnicode.c_str();
	auto len = WideCharToMultiByte(CP_ACP, 0, pUnicode, (int)strUnicode.length(), nullptr, 0, nullptr, nullptr);
	if (!len)
	{
		return "";
	}
	char* ap = new char[len + 1];
	std::unique_ptr<char> aup(ap);
	ap[0] = 0;
	ap[len - 1] = 0;
	ap[len] = 0;


	len = WideCharToMultiByte(CP_ACP, 0, pUnicode, (int)strUnicode.length(), ap, len, nullptr, nullptr);

	if (len == (size_t)-1)
	{
		return "";
	}
	return ap;
}


std::wstring DecAnsiWin(const std::string& strAnsi)
{
	const char* pAnsi = strAnsi.c_str();
	auto len = MultiByteToWideChar(CP_ACP, 0, pAnsi, (int)strAnsi.length(), nullptr, 0);

	if (!len)
	{
		return L"";
	}
	wchar_t* wp = new wchar_t[len + 1];
	std::unique_ptr<wchar_t> wup(wp);
	wp[0] = 0;
	wp[len - 1] = 0;
	wp[len] = 0;

	len = MultiByteToWideChar(CP_ACP, 0, pAnsi, (int)strAnsi.length(), wp, len);

	if (!len)
	{
		return L"";
	}
	return wp;
}



void ClibConvTest()
{
	setlocale(LC_ALL, "C"); // wrong
//	setlocale(LC_ALL, "chs"); // right
	string s = "���test���";
	auto w = DecAnsi(s);
}

void Win32ConvTest()
{
	string s = "���test���";
	cout << 1 << s << endl;
	auto w = DecAnsiWin(s);
	wcout.imbue(locale(""));
	wcout << 2 << w << endl;
	auto ss = EncAnsiWin(w);
	cout << 3 << ss << endl;
}

void GetLocaleInfo(void)
{
	std::wcout << "User-preferred locale setting is " << std::locale("").name().c_str() << '\n';
	// on startup, the global locale is the "C" locale
	std::wcout << 1000.01 << '\n';
	// replace the C++ global locale as well as the C locale with the user-preferred locale
	std::locale::global(std::locale(""));
	// use the new global locale for future wide character output
	std::wcout.imbue(std::locale());
	// output the same number again
	std::wcout << 1000.01 << '\n';
}

void LocaleTest(void)
{
	GetLocaleInfo();
	SetLocaleAndIsDigit();
	ClibConvTest();
	Win32ConvTest();
}
