#pragma once

#include <unordered_map>
#include <mutex>

struct SPixelColor;
class CCalcThread;

class CCalcThreadMgr
{
public:
	CCalcThreadMgr()
	{
		_full_pic.clear();
		_vec_calcthread.clear();
	};

	virtual ~CCalcThreadMgr() 
	{
		_full_pic.clear();

		for (int i = 0; i < _vec_calcthread.size(); i++)
		{
			delete _vec_calcthread[i];
		}
		_vec_calcthread.clear();
	};

	void insert_calc_thread(CCalcThread* pThread);
	void do_thread_calc();
	void dump_full_pic(int nx, int ny);

	bool is_all_thread_done();

	std::mutex _bind_result_lock;
	std::unordered_map<int, SPixelColor> _full_pic;

private:
	std::vector<CCalcThread*> _vec_calcthread;
};