//
// Created by vladislav on 19.10.2019.
//

#ifndef POINT3D_H
#define POINT3D_H

#include "point2d.h"

typedef struct point3D point3D;

typedef struct
{
    int (* getZ)(point3D*);

    void (* setZ)(point3D*, int);
} Point3DVTable;

typedef struct point3D
{
    point2D* base;

    void* prvtPoint3D;

    Point2DVTable* pBaseVTable;
    Point3DVTable* pVTable;
} point3D;

point3D* newPoint3D();

void deletePoint3D(point3D*);

#endif //POINT3D_H
