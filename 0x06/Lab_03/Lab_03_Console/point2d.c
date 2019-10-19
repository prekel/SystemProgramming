#include <stdlib.h>
#include "point2d.h"


typedef struct private
{
    int x;
    int y;
} private;

static int getx(struct point2D* p)
{
    return ((struct private*) (p->pPrivate))->x;
}

static void setx(struct point2D* p, int val)
{
    ((struct private*) (p->pPrivate))->x = val;
}

static int gety(struct point2D* p)
{
    return ((struct private*) (p->pPrivate))->y;
}

static void sety(struct point2D* p, int val)
{
    ((struct private*) (p->pPrivate))->y = val;
}

static Point2DVTable g_Point2DvTable = {getx, setx, gety, sety};

point2D* newPoint2D()
{
    point2D* ptr;
    ptr = (point2D*) malloc(sizeof(point2D));
    ptr->pPrivate = malloc(sizeof(private));

    ptr->pVTable = &g_Point2DvTable;

//    ptr->getX = &getx;
//    ptr->setX = &setx;
//    ptr->getY = &gety;
//    ptr->setY = &sety;
    return ptr;
}

void deletePoint2D(point2D* p)
{
    free(p);
}
