//
// Created by vladislav on 19.10.2019.
//

#ifndef POINT2D_H
#define POINT2D_H

typedef struct point2D {
    void *prvtPoint2D;
    int (*getX) (struct point2D*);
    void (*setX)(struct point2D*, int);
    //...
} point2D;
point2D* newPoint2D();
void deletePoint2D(point2D*);

#endif //POINT2D_H
