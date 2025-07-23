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

    // Terreno escuro e levemente variado, azul
    auto ground_material = make_shared<lambertian>(color(0.05, 0.05, 0.1));
    world.add(make_shared<sphere>(point3(0, -1000, 0), 1000, ground_material));
    
    //Esfera Central Metálica inserida
    auto center_material = make_shared<metal>(color(1.0, 1.0, 1.0), 0.0);
    world.add(make_shared<sphere>(point3(0, 0.6, 0), 0.6, center_material));
    
    //Adicionando a camada externa, 5 esferas elementares
    int layer1_count = 5;
    double layer1_radius = 1.8;
    double height1 = 1.2;

    for (int i = 0; i < layer1_count; ++i) {
        double angle = 2 * pi * i / layer1_count;
        double x = layer1_radius * cos(angle);
        double z = layer1_radius * sin(angle);

        shared_ptr<material> mat;

        if (i == 0)
            mat = make_shared<lambertian>(color(0.9, 0.1, 0.1));  // fogo
        else if (i == 1)
            mat = make_shared<lambertian>(color(0.1, 0.1, 0.9));  // água
        else if (i == 2)
            mat = make_shared<lambertian>(color(0.4, 0.2, 0.1));  // terra
        else if (i == 3)
            mat = make_shared<lambertian>(color(0.6, 0.6, 0.6));  // ar
        else
            mat = make_shared<lambertian>(color(0.7, 0.7, 0.9));  // éter

        world.add(make_shared<sphere>(point3(x, height1, z), 0.4, mat));
    }
      //adicionando camada intermediária, 10 esferas menores
      int layer2_count = 10;
      double layer2_radius = 1.2;
      double height2 = 0.8;

      for (int i = 0; i < layer2_count; ++i) {
          double angle = 2 * pi * i / layer2_count;
          double x = layer2_radius * cos(angle);
          double z = layer2_radius * sin(angle);

          shared_ptr<material> mat;
          if (i % 3 == 0)
              mat = make_shared<metal>(color(0.8, 0.8, 0.9), 0.1);
          else if (i % 3 == 1)
              mat = make_shared<dielectric>(1.5);
          else
              mat = make_shared<lambertian>(color(0.3, 0.7, 0.3));

          world.add(make_shared<sphere>(point3(x, height2, z), 0.25, mat));
}



   
}
