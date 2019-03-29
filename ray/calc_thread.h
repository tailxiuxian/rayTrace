#pragma once

#include <unordered_map>

class CCamara;
class hitable;
struct SPixelColor;
class CCalcThreadMgr;

struct SPos2
{
	int x;
	int y;
};

class CCalcThread
{
public:
	CCalcThread(SPos2 leftup, SPos2 rightbottom, int ns, int nx, int ny, CCamara* cam, hitable* world, CCalcThreadMgr* calc_mgr)
		:_leftup(leftup)
		,_rightbottom(rightbottom)
		,_ns(ns)
		,_nx(nx)
		,_ny(ny)
		,_cam(cam)
		,_world(world)
		,_calc_mgr(calc_mgr)
		,_done(false)
	{
		_color_pic.clear();
	};

	virtual ~CCalcThread() {};

	void calc_ray_trace_pic();
	void bind_ray_trace_pic();
	bool isdone();

	static unsigned int execute(void* pParam);
	unsigned int doexecute();

private:
	SPos2 _leftup;
	SPos2 _rightbottom;
	int _ns;
	CCamara* _cam;
	int _nx;
	int _ny;
	hitable* _world;
	std::unordered_map<int,SPixelColor> _color_pic;
	CCalcThreadMgr* _calc_mgr;
	bool _done;
};