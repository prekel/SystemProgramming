#include <stdlib.h>

#include "point3d.h"

typedef struct private
{
    int z;
} private;

static int getz(struct point3D* p)
{
    return ((struct private*) (p->prvtPoint3D))->z;
}

static void setz(struct point3D* p, int val)
{
    ((struct private*) (p->prvtPoint3D))->z = val;
}

static Point3DVTable g_DvTable = {getz, setz};

point3D* newPoint3D()
{
    point3D* ptr;

    ptr = (point3D*) malloc(sizeof(point3D));
    ptr->base = newPoint2D();

    ptr->pVTable = &g_DvTable;
    ptr->pBaseVTable = ptr->base->pVTable;

    ptr->prvtPoint3D = malloc(sizeof(private));

    return ptr;
}

void deletePoint3D(point3D* p)
{
    deletePoint2D(p->base);
    free(p);
}
