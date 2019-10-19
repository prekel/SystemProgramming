#include <stdio.h>
#include "point2d.h"
#include "point3d.h"
#include "points.h"

int main()
{
    point3D* point = newPoint3D();



    point->pBaseVTable->setX(point->base, 11);
    point->pBaseVTable->setY(point->base, 12);
    point->pVTable->setZ(point, 13);
    printf("d = %f\n", doSomething(point));
    printf("x = %d\n", point->pBaseVTable->getX(point->base));
    printf("y = %d\n", point->pBaseVTable->getY(point->base));
    printf("z = %d\n", point->pVTable->getZ(point));
    deletePoint3D(point);
    return 0;
}
