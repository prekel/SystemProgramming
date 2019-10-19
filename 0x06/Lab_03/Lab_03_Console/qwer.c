#include "qwer.h"

#include <stdio.h>
#include <stdlib.h>

typedef struct _Point2DPrivate
{
    int x;
    int y;
} Point2DPrivate;

typedef struct _Point2D
{
    Point2DPrivate* private;
} Point2D;

void Point2D_Constructor(Point2D* point)
{
    point->private = malloc(sizeof(Point2DPrivate));
    point->private->x = 0;
    point->private->y = 0;
}

void Point2D_Destructor(Point2D* point)
{
    free(point->private);
}

void Point2D_SetX(Point2D* point, int x)
{
    point->private->x = x;
}

int Point2D_GetX(Point2D* point)
{
    return point->private->x;
}

void Point2D_SetY(Point2D* point, int y)
{
    point->private->y = y;
}

int Point2D_GetY(Point2D* point)
{
    return point->private->y;
}

Point2D* Point2D_New(void)
{
    Point2D* point = malloc(sizeof(Point2D));
    Point2D_Constructor(point); /* <-- Вызываем конструктор */
    return point;
}

void Point2D_Delete(Point2D* point)
{
    Point2D_Destructor(point); /* <-- Вызываем деструктор */
    free(point);
}

typedef struct _Point3DPrivate
{
    int z;
} Point3DPrivate;

typedef struct _Point3D
{
    Point2D parent;
    Point3DPrivate* private;
} Point3D;

void Point3D_Constructor(Point3D* point)
{
    Point2D_Constructor(
            &point->parent); /* <-- Вызываем родительский конструктор! */
    point->private = malloc(sizeof(Point3DPrivate));
    point->private->z = 0;
}

void Point3D_Destructor(Point3D* point)
{
    Point2D_Destructor(
            &point->parent); /* <-- Вызываем родительский деструктор! */
    free(point->private);
}

void Point3D_SetZ(Point3D* point, int z)
{
    point->private->z = z;
}

int Point3D_GetZ(Point3D* point)
{
    return point->private->z;
}

Point3D* Point3D_New(void)
{
    Point3D* point = malloc(sizeof(Point3D));
    Point3D_Constructor(point); /* <-- Вызываем конструктор */
    return point;
}

void Point3D_Delete(Point3D* point)
{
    Point3D_Destructor(point); /* <-- Вызываем деструктор */
    free(point);
}

int main(int argc, char** argv)
{
    /* Создаем экземпляр класса Point3D */
    Point3D* point = Point3D_New();

    Point2D* point2d = (Point2D*) point;

    /* Устанавливаем x и y координаты */
    Point2D_SetX((Point2D*) point, 10);
    Point2D_SetY((Point2D*) point, 15);

    /* Теперь z координата */
    Point3D_SetZ(point, 20);

    /* Должно вывести: x = 10, y = 15, z = 20 */
    printf("x = %d, y = %d, z = %d\n",
           Point2D_GetX((Point2D*) point),
           Point2D_GetY((Point2D*) point),
           Point3D_GetZ(point));

    /* Удаляем объект */
    Point3D_Delete(point);

    return 0;
}