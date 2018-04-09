#include <cstdint>
#include <string>
#include <mutex>
#include <fstream>
#include <vector>
#include <atomic>
#include <thread>
#include <cstring>
#include <array>

/*
ʵ��һ�����ӳٵ���־ϵͳ�����ϵͳ��������д�볤��Ϊ128-256�ֽڵ��ַ���, �ַ���˳�����д���̵߳���
��(���ֽ�ASCII)����ȷ�������д��ʱ��(��ʮ��λ�����;���epoch������)���Լ���Ԥ�ȶ���ĳ���Ϊ
112-240�ֽڵ�1024���ַ��������ѡȡ��һ��

Ҫ��
ʵ������Ϊmodern c++, linuxƽ̨. x86������. �����������̲߳�����д��һ����Σ����̲߳��ƻ�
�����߳�д����ַ�����д��˳����Ҫ��ʱ��˳���������������.�ھ����̵ܶ�ʱ�����ȫ��д�룬����д��
����ƽ���ӳٵ���5������.֧������app����ʧ�Ѿ�д��ļ�¼

������ʹ�ð�����������boost�ĵ������⣬������ʹ��ԭ�����������Ժͱ�׼��,�ݽ�Դ�����븽�����˵��,��ʹ��������ı�������
��������һ����Ҫע���Ҫ��
*/

namespace nsFastLog
{
	class ThreadLogger;

	struct LogTime
	{
		std::int64_t tp;
		size_t hdrIdx;

		LogTime(std::int64_t t, size_t i)
			: tp(t)
			, hdrIdx(i)
		{}

		bool operator>(const LogTime& other) const
		{
			return tp > other.tp;
		}
	};

	typedef std::int64_t SLogItem;

// 	struct SLogItem
// 	{
// 		std::int64_t tp;
//		std::string log;
//		char log[256];
		
// 		SLogItem(std::int64_t t, const std::string& l)
// 			: tp(t)
//			, log(l)
//		{
//			memcpy(log, l.c_str(), l.length() + 1);
//		}
//	};

	struct SLogHeader
	{
		const unsigned PRESIZE = 1000000;
		std::string hdr;
		std::vector<SLogItem> vLogs;

		SLogHeader(void)
		{
			vLogs.reserve(PRESIZE);
		}

		void FlushFrom(SLogHeader& other)
		{
			hdr = other.hdr;
			vLogs.swap(other.vLogs);
		}
	};

	class Logger
	{
		const unsigned MAXCNTR = 8;
		std::fstream fsLog;
		
		std::vector<std::mutex> vMtx;
		std::vector<SLogHeader> vLogContent;
		std::vector<std::vector<std::array<char, 256>>> vLogContent2;
		std::atomic_uint idxCntr;
		unsigned nThread;

		std::thread thFlush;
		bool bRuning = false;
		static void ThreadFlush(Logger* pLogger);

		void FlushLog(void);
		void FlushLog2(void);
	public: 
		Logger() :vMtx(MAXCNTR), vLogContent(MAXCNTR), vLogContent2(MAXCNTR)
		{
		};
		bool Init(const std::string& logFile, unsigned threadCnt);
		void Stop(void);
		ThreadLogger GetThreadLogger(const std::string& hdr, Logger* pFastLogger);
		void GetCntr(std::vector<std::array<char, 256>>*& pv, std::mutex*& pMtx);
		inline void Log(const int idCntr, const std::string& logHdr, const std::string& log)
		{
			std::int64_t tp = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
			std::lock_guard<std::mutex> lk(vMtx[idCntr]);
			vLogContent[idCntr].vLogs.emplace_back(tp);
//			vLogContent2[idCntr].emplace_back();
//			memcpy(vLogContent2[idCntr].back().data(), log.c_str(), log.size());
		}

		void SigHandler(int signal_number);
	};


	class ThreadLogger
	{
		int idxLogCntr;
		Logger* pFastLogger;
		std::string logHdr;
	public:
		ThreadLogger(int idx, Logger* pLogger, const std::string& hdr)
			: idxLogCntr(idx)
			, pFastLogger(pLogger)
			, logHdr(hdr)
		{
		}

		inline void Log(const std::string& log)
		{
			pFastLogger->Log(idxLogCntr, logHdr, log);
		}
	};
}