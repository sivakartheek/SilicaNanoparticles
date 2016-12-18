#ifndef NUMERICAL_H
#define NUMERICAL_H
#include<cmath>

inline double norm(double x,double y,double z)
{
  return sqrt(x*x+y*y+z*z);
}
inline double dp(double x,double y,double z,double xx,double yy,double zz)
{
  return x*xx+y*yy+z*zz;
}
inline double mindis(double dx,double dy,double dz,double a,double b,double c)
{
  return norm(dx - a * round(dx/a),dy - b * round(dy/b),dz - c * round(dz/c));
}
inline int Rand_INT(int min,int max) //[min,max)
{
  return rand()%(max-min)+min;
}
inline double Rand_DOUBLE() //(0,1)
{
  return (double) rand() / (double) RAND_MAX;
}
inline double min(double a,double b)
{
  return (a>b) ? b : a;
}   
inline double max(double a,double b)
{
  return (a>b) ? a : b;
}  

#endif