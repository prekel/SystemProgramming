//
// Created by vladislav on 19.10.2019.
//

#ifndef POINT2D_H
#define POINT2D_H

struct point2D;

typedef struct
{
    int (* getX)(struct point2D*);

    void (* setX)(struct point2D*, int);

    int (* getY)(struct point2D*);

    void (* setY)(struct point2D*, int);
} Point2DVTable;

typedef struct point2D
{
    void* pPrivate;

    Point2DVTable* pVTable;
} point2D;

point2D* newPoint2D();

void deletePoint2D(point2D* ptr);

#endif //POINT2D_H
