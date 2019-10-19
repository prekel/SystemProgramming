//
// Created by vladislav on 19.10.2019.
//

#include <stdlib.h>
#include "point2d.h"

typedef struct private {
    int x;
    int y;
} private;

static int getx(struct point2D*p) {
    return ((struct private*)(p->prvtPoint2D))->x;
}
static void setx(struct point2D *p, int val) {
    ((struct private*)(p->prvtPoint2D))->x = val;
}

point2D* newPoint2D()  {
    point2D* ptr;
    ptr = (point2D*) malloc(sizeof(point2D));
    ptr -> prvtPoint2D = malloc(sizeof(private));
    ptr -> getX = &getx;
    ptr -> setX = &setx;
    // ....
    return ptr;
}
