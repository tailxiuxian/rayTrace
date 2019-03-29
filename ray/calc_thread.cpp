#include "calc_thread.h"
#include "calc_thread_mgr.h"
#include "vec3.h"
#include "comm.h"
#include "camara.h"

void CCalcThread::calc_ray_trace_pic()
{
	SPixelColor pixelcolor;
	for (int j = _rightbottom.y - 1; j >= _leftup.y; j--)
	{
		for (int i = _leftup.x; i < _rightbottom.x; i++)
		{
			CVec3 vecColor(0.0f, 0.0f, 0.0f);
			for (int k = 0; k < _ns; k++)
			{
				float u = float(i + randf()) / float(_nx);
				float v = float(j + randf()) / float(_ny);
				CRay ray = _cam->get_ray(u, v);
				CVec3 vec = color(ray, _world, 0);
				vecColor += vec;
			}

			vecColor /= float(_ns);
			vecColor = CVec3(sqrt(vecColor.r()), sqrt(vecColor.g()), sqrt(vecColor.b()));
			pixelcolor.ir = int(255.99 * vecColor.r());
			pixelcolor.ig = int(255.99 * vecColor.g());
			pixelcolor.ib = int(255.99 * vecColor.b());

			int iIndex = j * _nx + i;
			_color_pic.insert(std::make_pair(iIndex, pixelcolor));
		}
	}
}

void CCalcThread::bind_ray_trace_pic()
{
	_calc_mgr->_bind_result_lock.lock();

	std::unordered_map<int, SPixelColor>::iterator iter = _color_pic.begin();
	for (; iter != _color_pic.end(); iter++)
	{
		_calc_mgr->_full_pic.insert(std::make_pair(iter->first, iter->second));
	}

	_done = true;

	_calc_mgr->_bind_result_lock.unlock();
}

bool CCalcThread::isdone()
{
	return _done;
}

unsigned int CCalcThread::execute(void* pParam)
{
	return static_cast<CCalcThread*>(pParam)->doexecute();
}

unsigned int CCalcThread::doexecute()
{
	calc_ray_trace_pic();
	bind_ray_trace_pic();
}