#include <iostream>
#include <windows.h>
#include "calc_thread_mgr.h"
#include "calc_thread.h"
#include "comm.h"

void CCalcThreadMgr::insert_calc_thread(CCalcThread* pThread)
{
	_vec_calcthread.push_back(pThread);
}

void CCalcThreadMgr::do_thread_calc()
{
	for (int i = 0; i < _vec_calcthread.size(); i++)
	{
		std::thread* t = new std::thread(CCalcThread::execute, _vec_calcthread[i]);
		t->detach();
	}
}

bool CCalcThreadMgr::is_all_thread_done()
{
	for (int i = 0; i < _vec_calcthread.size(); i++)
	{
		if (_vec_calcthread[i]->isdone() == false)
		{
			return false;
		}
	}

	return true;
}

void CCalcThreadMgr::dump_full_pic(int nx, int ny)
{
	while (true)
	{
		Sleep(1000);

		if (is_all_thread_done() == false)
		{
			continue;
		}


		_bind_result_lock.lock();

		freopen("data.ppm", "w", stdout);

		std::cout << "P3\n" << nx << " " << ny << "\n255\n";
		for (int j = ny - 1; j >= 0; j--)
		{
			for (int i = 0; i < nx; i++)
			{
				int iIndex = j * nx + i;
				std::unordered_map<int, SPixelColor>::iterator iter = _full_pic.find(iIndex);
				std::cout << iter->second.ir << " " << iter->second.ig << " " << iter->second.ib << "\n";
			}
		}

		freopen("CON", "w", stdout);

		_bind_result_lock.unlock();

		return;
	}
}