#include <iostream>
#include <vector>
#include "vec3.h"
#include "ray.h"
#include "sphere.h"
#include "hit_list.h"
#include "comm.h"
#include "camara.h"
#include "material.h"
#include "calc_thread.h"
#include "calc_thread_mgr.h"

hitable *random_scene() {
	int n = 500;
	hitable **list = new hitable*[n + 1];
	list[0] = new CSphere(CVec3(0, -1000, 0), 1000, new lambertian(CVec3(0.5, 0.5, 0.5)));
	int i = 1;
	for (int a = -11; a < 11; a++) {
		for (int b = -11; b < 11; b++) {
			float choose_mat = randf();
			CVec3 center(a + 0.9*randf(), 0.2, b + 0.9*randf());
			if ((center - CVec3(4, 0.2, 0)).length() > 0.9) {
				if (choose_mat < 0.8) {  // diffuse
					list[i++] = new CSphere(center, 0.2, new lambertian(CVec3(randf()*randf(), randf()*randf(), randf()*randf())));
				}
				else if (choose_mat < 0.95) { // metal
					list[i++] = new CSphere(center, 0.2,
						new metal(CVec3(0.5*(1 + randf()), 0.5*(1 + randf()), 0.5*(1 + randf())), 0.5*randf()));
				}
				else {  // glass
					list[i++] = new CSphere(center, 0.2, new dielectric(1.5));
				}
			}
		}
	}

	list[i++] = new CSphere(CVec3(0, 1, 0), 1.0, new dielectric(1.5));
	list[i++] = new CSphere(CVec3(-4, 1, 0), 1.0, new lambertian(CVec3(0.4, 0.2, 0.1)));
	list[i++] = new CSphere(CVec3(4, 1, 0), 1.0, new metal(CVec3(0.7, 0.6, 0.5), 0.0));

	return new Chitlist(list, i);
}

int main()
{
	time_t timeBegin = time(NULL);

	int nx = 1200;
	int ny = 800;
	int ns = 100;

	CVec3 lookfrom(13, 2, 3);
	CVec3 lookat(0, 0, 0);
	float dist_to_focus = 20.0f;
	float aperture = 0.01f;

	CCamara cam(lookfrom, lookat, CVec3(0, 1, 0), 20, float(nx) / float(ny), aperture, dist_to_focus);
	
	//hitable *list[4];
	//list[0] = new CSphere(CVec3(0.0f,0.0f,-1.0f),0.5f, new lambertian(CVec3(0.1f,0.2f,0.5f)));
	//list[1] = new CSphere(CVec3(0.0f,-100.5f, -1.0f), 100.0f, new lambertian(CVec3(0.8f, 0.8f, 0.0f)));
	//list[2] = new CSphere(CVec3(1.0f, 0.0f, -1.0f), 0.5f, new metal(CVec3(0.8f, 0.6f, 0.2f), 0.0f));
	//list[3] = new CSphere(CVec3(-1.0f, 0.0f, -1.0f), 0.5f, new dielectric(1.5f));

	//hitable *world = new Chitlist(list, 4);
	hitable *world = random_scene();

	int xsplit, ysplit;
	xsplit = ysplit = 4;
	int xstep = nx / xsplit;
	int ystep = ny / ysplit;

	CCalcThreadMgr g_calcthreadmgr;

	for (int x = 0; x < xsplit; x++)
	{
		for (int y = 0; y < ysplit; y++)
		{
			SPos2 posStart, posEnd;
			posStart.x = xstep * x;
			posStart.y = ystep * y;
			posEnd.x = posStart.x + xstep;
			posEnd.y = posStart.y + ystep;

			g_calcthreadmgr.insert_calc_thread(new CCalcThread(posStart, posEnd, ns, nx, ny, &cam, world, &g_calcthreadmgr));
		}
	}

	g_calcthreadmgr.do_thread_calc();
	g_calcthreadmgr.dump_full_pic(nx,ny);

	time_t timeEnd = time(NULL);

	std::cout<<"Elpased Time: "<<(timeEnd - timeBegin)<<"\n";

	system("pause");

	//for (int j = ny - 1; j >= 0; j--)
	//{
	//	for (int i = 0; i < nx; i++)
	//	{
	//		CVec3 vecColor(0.0f, 0.0f, 0.0f);
	//		for (int k = 0; k < ns; k++)
	//		{
	//			float u = float(i + randf()) / float(nx);
	//			float v = float(j + randf()) / float(ny);
	//			CRay ray = cam.get_ray(u, v);
	//			CVec3 vec = color(ray, world, 0);
	//			vecColor += vec;
	//		}

	//		vecColor /= float(ns);
	//		vecColor = CVec3(sqrt(vecColor.r()), sqrt(vecColor.g()), sqrt(vecColor.b()));
	//		int ir = int(255.99 * vecColor.r());
	//		int ig = int(255.99 * vecColor.g());
	//		int ib = int(255.99 * vecColor.b());
	//		std::cout << ir << " " << ig << " " << ib << "\n";
	//	}
	//}

	return 0;
}
