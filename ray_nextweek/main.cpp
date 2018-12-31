#include<iostream>
#include "vec3.h"
#include "ray.h"
#include "sphere.h"
#include "moving_sphere.h"
#include "hit_list.h"
#include "comm.h"
#include "camara.h"
#include "material.h"
#include "rect.h"

hitable *random_scene() {
	int n = 500;
	hitable **list = new hitable*[n + 1];
	list[0] = new CSphere(CVec3(0, -1000, 0), 1000, new lambertian(new checker_texture(CVec3(0.2, 0.3, 0.1), CVec3(0.9,0.9,0.9))));
	int i = 1;
	for (int a = -11; a < 11; a++) {
		for (int b = -11; b < 11; b++) {
			float choose_mat = randf();
			CVec3 center(a + 0.9*randf(), 0.2, b + 0.9*randf());
			if ((center - CVec3(4, 0.2, 0)).length() > 0.9) {
				if (choose_mat < 0.8) {  // diffuse
					//list[i++] = new moving_sphere(center, center + CVec3(0.0, 0.5 * randf(), 0.0), 0.0f, 1.0f, 0.2, new lambertian(new constant_texture(CVec3(randf()*randf(), randf()*randf(), randf()*randf()))));
					list[i++] = new moving_sphere(center, center, 0.0f, 1.0f, 0.2, new lambertian(new constant_texture(CVec3(randf()*randf(), randf()*randf(), randf()*randf()))));
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
	list[i++] = new CSphere(CVec3(-4, 1, 0), 1.0, new lambertian(new constant_texture(CVec3(0.4, 0.2, 0.1))));
	list[i++] = new CSphere(CVec3(4, 1, 0), 1.0, new metal(CVec3(0.7, 0.6, 0.5), 0.0));

	return new Chitlist(list, i);
}

hitable *two_checker_sphere() {
	int n = 2;
	hitable **list = new hitable*[n + 1];

	checker_texture* pTexture = new checker_texture(CVec3(0.2, 0.3, 0.1), CVec3(0.9, 0.9, 0.9));
	list[0] = new CSphere(CVec3(0, 10, 0), 10, new lambertian(pTexture));
	list[1] = new CSphere(CVec3(0, -10, 0), 10, new lambertian(pTexture));

	return new Chitlist(list, 2);
}

hitable *two_perlin_sphere() {
	int n = 2;
	hitable **list = new hitable*[n + 1];

	float scale = 6.0f;
	list[0] = new CSphere(CVec3(0, -1000, 0), 1000, new lambertian(new noise_texture(scale)));
	list[1] = new CSphere(CVec3(0, 2, 0), 2, new lambertian(new noise_texture(scale)));

	return new Chitlist(list, 2);
}

hitable *simple_light() {
	int n = 4;
	hitable **list = new hitable*[n + 1];

	float scale = 4.0f;
	list[0] = new CSphere(CVec3(0, -1000, 0), 1000, new lambertian(new noise_texture(scale)));
	list[1] = new CSphere(CVec3(0, 2, 0), 2, new lambertian(new noise_texture(scale)));
	list[2] = new CSphere(CVec3(0, 7, 0), 2, new diffuse_light(new constant_texture(CVec3(4.0f, 4.0f, 4.0f))));
	list[3] = new xy_rect(3, 5, 1, 3, -2 , new diffuse_light(new constant_texture(CVec3(4.0f, 4.0f, 4.0f))));

	return new Chitlist(list, 4);
}

int main()
{
	freopen("data.ppm", "w", stdout);

	int nx = 1200;
	int ny = 800;
	int ns = 120;

	CVec3 lookfrom_origin(13.0f, 2.0f, 5.0f);
	CVec3 lookfrom(lookfrom_origin * 3.0f);
	CVec3 lookat(0, 0, 0);
	float dist_to_focus = 10.0f;
	float aperture = 0.0f;

	CCamara cam(lookfrom, lookat, CVec3(0, 1, 0), 20, float(nx) / float(ny), aperture, dist_to_focus, 0.0f, 1.0f);
	
	//hitable *list[4];
	//list[0] = new CSphere(CVec3(0.0f,0.0f,-1.0f),0.5f, new lambertian(CVec3(0.1f,0.2f,0.5f)));
	//list[1] = new CSphere(CVec3(0.0f,-100.5f, -1.0f), 100.0f, new lambertian(CVec3(0.8f, 0.8f, 0.0f)));
	//list[2] = new CSphere(CVec3(1.0f, 0.0f, -1.0f), 0.5f, new metal(CVec3(0.8f, 0.6f, 0.2f), 0.0f));
	//list[3] = new CSphere(CVec3(-1.0f, 0.0f, -1.0f), 0.5f, new dielectric(1.5f));

	//hitable *world = new Chitlist(list, 4);
	//hitable *world = random_scene();
	//hitable *world = two_checker_sphere();
	//hitable *world = two_perlin_sphere();
	hitable *world = simple_light();

	std::cout << "P3\n" << nx << " " << ny << "\n255\n";
	for (int j = ny - 1; j >= 0; j--)
	{
		for (int i = 0; i < nx; i++)
		{
			CVec3 vecColor(0.0f, 0.0f, 0.0f);
			for (int k = 0; k < ns; k++)
			{
				float u = float(i + randf()) / float(nx);
				float v = float(j + randf()) / float(ny);
				CRay ray = cam.get_ray(u, v);
				CVec3 vec = color(ray, world, 0);
				vecColor += vec;
			}

			vecColor /= float(ns);
			vecColor = CVec3(sqrt(vecColor.r()), sqrt(vecColor.g()), sqrt(vecColor.b()));
			int ir = int(255.99 * vecColor.r());
			int ig = int(255.99 * vecColor.g());
			int ib = int(255.99 * vecColor.b());
			std::cout << ir << " " << ig << " " << ib << "\n";
		}
	}

	return 0;
}
