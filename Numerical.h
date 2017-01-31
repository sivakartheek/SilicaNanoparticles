#ifndef NUMERICAL_H
#define NUMERICAL_H
#include<cmath>

// Computes the norm 
inline double norm(double x,double y,double z)
{
  return sqrt(x*x+y*y+z*z);
}

// Computes the dot product of two vector
inline double dp(double x,double y,double z,double xx,double yy,double zz)
{
  return x*xx+y*yy+z*zz;
}

// Computes the minimum distance between two positions
inline double mindis(double dx,double dy,double dz,double a,double b,double c)
{
  return norm(dx - a * round(dx/a),dy - b * round(dy/b),dz - c * round(dz/c));
}

// generates a random integer
inline int Rand_INT(int min,int max) //[min,max)
{
  return rand()%(max-min)+min;
}

// generates a random number between 0 and 1
inline double Rand_DOUBLE() //(0,1)
{
  return (double) rand() / (double) RAND_MAX;
}

// Finds the minimum of 2 numbers 
inline double min(double a,double b)
{
  return (a>b) ? b : a;
}

// Finds the maximum of 2 numbers   
inline double max(double a,double b)
{
  return (a>b) ? a : b;
}  

#endif
