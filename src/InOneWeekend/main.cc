//==============================================================================================
// Originally written in 2016 by Peter Shirley <ptrshrl@gmail.com>
//
// To the extent possible under law, the author(s) have dedicated all copyright and related and
// neighboring rights to this software to the public domain worldwide. This software is
// distributed without any warranty.
//
// You should have received a copy (see file COPYING.txt) of the CC0 Public Domain Dedication
// along with this software. If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.
//==============================================================================================

#include "rtweekend.h"

#include "camera.h"
#include "hittable.h"
#include "hittable_list.h"
#include "material.h"
#include "sphere.h"


using std::make_shared;

int main() {
    hittable_list world;

    // Terreno escuro e levemente variado
    auto ground_material = make_shared<lambertian>(color(0.05, 0.05, 0.1));
    world.add(make_shared<sphere>(point3(0, -1000, 0), 1000, ground_material));

    // Centro da estrela (energia cósmica)
    auto center_material = make_shared<metal>(color(1.0, 1.0, 1.0), 0.0);
    world.add(make_shared<sphere>(point3(0, 0.6, 0), 0.6, center_material));

    // Parâmetros de espaçamento e altura (ajustados para harmonia)
    double base_radius = 3.5;      // Raio da camada externa
    double base_height = 0.4;      // Altura camada externa
    double base_r = 0.8;           // Raio das esferas externas

    // --- Camada externa (5 pontas da estrela) ---
    for (int i = 0; i < 5; ++i) {
        double angle = i * 2.0 * M_PI / 5.0;
        double x = base_radius * cos(angle);
        double z = base_radius * sin(angle);

        shared_ptr<material> mat;
        switch(i) {
            case 0: mat = make_shared<metal>(color(0.9, 0.3, 0.1), 0.1); break;  // fogo
            case 1: mat = make_shared<dielectric>(1.33); break;                   // água
            case 2: mat = make_shared<lambertian>(color(0.2, 0.5, 0.2)); break;   // terra
            case 3: mat = make_shared<metal>(color(0.8, 0.8, 0.9), 0.15); break;  // ar
            case 4: mat = make_shared<metal>(color(1.0, 0.85, 0.3), 0.0); break;  // éter
        }

        world.add(make_shared<sphere>(point3(x, base_height, z), base_r, mat));
    }

    // --- Camada intermediária (10 esferas menores entre as pontas) ---
    double mid_radius = base_radius * 0.55;    // Raio um pouco menor que a externa
    double mid_r = base_r * 0.5;               // Esferas menores
    double mid_height = base_height + 0.6;     // Altura maior para formar "torre"

    for (int i = 0; i < 10; ++i) {
        double angle = i * 2.0 * M_PI / 10.0;
        double x = mid_radius * cos(angle);
        double z = mid_radius * sin(angle);

        shared_ptr<material> mat;
        if (i % 3 == 0)
            mat = make_shared<lambertian>(color(0.7, 0.2, 0.2));
        else if (i % 3 == 1)
            mat = make_shared<metal>(color(0.7, 0.7, 0.7), 0.3);
        else
            mat = make_shared<dielectric>(1.2);

        world.add(make_shared<sphere>(point3(x, mid_height, z), mid_r, mat));
    }

    // --- Camada interna (círculo central com pequenas esferas) ---
    double inner_radius = base_radius * 0.3;  // Raio menor ainda
    double inner_r = base_r * 0.3;             // Esferas bem pequenas
    double inner_height = mid_height + 0.7;    // Altura mais alta para formar a ponta da "torre"

    for (int i = 0; i < 6; ++i) {
        double angle = i * 2.0 * M_PI / 6.0;
        double x = inner_radius * cos(angle);
        double z = inner_radius * sin(angle);

        shared_ptr<material> mat;
        if (i % 2 == 0)
            mat = make_shared<metal>(color(0.9, 0.9, 0.4), 0.0);
        else
            mat = make_shared<lambertian>(color(0.1, 0.3, 0.1));

        world.add(make_shared<sphere>(point3(x, inner_height, z), inner_r, mat));
    }

    // Câmera ajustada para enquadrar a torre
    camera cam;
    cam.aspect_ratio      = 16.0 / 9.0;
    cam.image_width       = 1200;
    cam.samples_per_pixel = 300;
    cam.max_depth         = 50;

    cam.vfov     = 40;
    cam.lookfrom = point3(0, 8, 18);
    cam.lookat   = point3(0, 2, 0);
    cam.vup      = vec3(0, 1, 0);

    cam.defocus_angle = 0.1;
    cam.focus_dist    = (cam.lookfrom - cam.lookat).length();

    cam.render(world);
}
