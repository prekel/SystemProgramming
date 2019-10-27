/*! \file    circle.c
 *  \brief   Prints the areas of circles.
 *
 *  \details Prints the areas of circles.
 *           Uses circulararea.c for the math.
 */

#include <stdio.h>
double circularArea(double r);

/*! \brief Main function
 *
 *  \return Integer 0 upon exit success.
 */
int main()
{
  double radius = 1.0;
  double area = 0.0;
  printf("\tAreas of Circles\n\n");
  printf("\tRadius\tArea\n"
         "-------------------------\n" );
  area = circularArea(radius);
  printf("%10.1f %10.2f\n", radius, area);

  radius = 5.0;
  area = circularArea( radius );
  printf("%10.1f %10.2f\n", radius, area);

  return 0;
}
