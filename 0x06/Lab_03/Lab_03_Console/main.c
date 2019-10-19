#include <stdio.h>
#include "point2d.h"
#include "point3d.h"
#include "points.h"

int main()
{
    point3D* point = newPoint3D();
    point->base->setX(point->base, 11);
    point->base->setY(point->base, 12);
    point->setZ(point, 13);
    printf("d = %f\n", doSomething(point));
    printf("x = %d\n", point->base->getX(point->base));
    printf("y = %d\n", point->base->getY(point->base));
    printf("z = %d\n", point->getZ(point));
    deletePoint3D(point);
    return 0;
}
