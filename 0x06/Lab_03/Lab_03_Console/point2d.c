#include <stdlib.h>
#include "point2d.h"

typedef struct private
{
    int x;
    int y;
} private;

static int getx(struct point2D* p)
{
    return ((struct private*) (p->prvtPoint2D))->x;
}

static void setx(struct point2D* p, int val)
{
    ((struct private*) (p->prvtPoint2D))->x = val;
}

static int gety(struct point2D* p)
{
    return ((struct private*) (p->prvtPoint2D))->y;
}

static void sety(struct point2D* p, int val)
{
    ((struct private*) (p->prvtPoint2D))->y = val;
}

point2D* newPoint2D()
{
    point2D* ptr;
    ptr = (point2D*) malloc(sizeof(point2D));
    ptr->prvtPoint2D = malloc(sizeof(private));
    ptr->getX = &getx;
    ptr->setX = &setx;
    ptr->getY = &gety;
    ptr->setY = &sety;
    return ptr;
}

void deletePoint2D(point2D* p)
{
    free(p);
}
