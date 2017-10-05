#include <cstdio>
#include <iostream>
#include <fstream>
#include <sstream>

#include <string>
#include <vector>
#include <deque>
#include <list>

#include <cstdint>
#include <cinttypes>
#include <cassert>

#include <ctime>
#include <chrono>

#include <memory>

#include <algorithm>
#include <functional>

#pragma warning(disable: 4267 4244 4018 4800)

void CHECK(bool b);
std::vector<std::int64_t> ReadInt(const std::string& filename);
std::vector<std::int64_t> ReadIntWithCount(const std::string& filename);
void SleepMs(int millisec);
void SleepSec(int sec);
void TimeCost(const std::chrono::high_resolution_clock::time_point& tp);

inline std::chrono::steady_clock::time_point Now(void) 
	{ return std::chrono::high_resolution_clock::now(); }
inline float Tock(const std::chrono::steady_clock::time_point& tp)
	{ return std::chrono::duration_cast<std::chrono::duration<float>>(std::chrono::high_resolution_clock::now() - tp).count(); }

// not thread-safe:
extern std::chrono::steady_clock::time_point g_tp;
inline void Tick(void)
	{ g_tp = std::chrono::high_resolution_clock::now(); }
inline float Tock(void)
	{ return std::chrono::duration_cast<std::chrono::duration<float>>(std::chrono::high_resolution_clock::now() - g_tp).count(); }

// ReturnExecutor var([&](){ f; })
#define ReturnGuard(name, func)	\
		ReturnExecutor name([&](){ func; });


class ReturnExecutor
{
public:
	ReturnExecutor(ReturnExecutor& another) = delete;
	ReturnExecutor& operator=(ReturnExecutor&) = delete;

	ReturnExecutor() {};
	ReturnExecutor(ReturnExecutor&& another) { f = std::move(another.f); };
	void operator=(ReturnExecutor&& another) { f = std::move(another.f); };

	ReturnExecutor(std::function<void()> i) :f(std::move(i)){}

	~ReturnExecutor(void){ if (f) f(); }

	void Release(void) { f = nullptr; }
private:
	std::function<void()> f = nullptr;
};



