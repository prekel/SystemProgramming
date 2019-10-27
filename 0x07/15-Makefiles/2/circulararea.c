/*! \file    circulararea.c
 *  \brief   Calculates the areas of circles.
 *
 *  \details Calculates the areas of circles.
 *           Called by main() in circle.c.
 */

/*! \brief Calculates the area of a circle.
 *
 *  \param r The radius of the circle
 *  \return  The area of the circle
 */
double circularArea(double r)
{
  const double pi = 3.1415926536; // Pi is a constant
  return pi * r * r;
}