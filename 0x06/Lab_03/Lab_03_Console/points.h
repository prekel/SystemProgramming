//
// Created by vladislav on 19.10.2019.
//

#ifndef POINTS_H
#define POINTS_H

#include "point2d.h"
#include "point3d.h"

double do2D(point2D *p);
double do3D(point3D *p);

#define doSomething(X) _Generic((X), \
  point3D* : do3D, \
  point2D* : do2D \
) (X)

#endif //POINTS_H
