#ifndef AVERAGES_H
#define AVERAGES_H
#include<vector>
#include"Configuration.h"
#include<fstream>
#include<iostream>
using namespace std;

class Averages
{
  private:
    double diameter;

    //1. Potential Energy
    vector<int>steps;
    vector<double>Energy;

    //2. Radial Density Profile(RDP) 
    unsigned int RDP_size;
    double RDP_h; //(h-stepsize)
    double* x;
    double* Density_all;
    double* Density_Si;
    double* Density_O;

    //3. Radial Distribution Function(RDF)
    unsigned int RDF_size;
    double RDF_h;
    double* r;
    double* RDF_all;
    double* RDF_Si;
    double* RDF_O;
    double* RDF_SiO;

    //4. Bond Angle distribution(BAD)
    double angle_h;
    double SiOSi[2][360];
    double OSiO[2][360];

  public:

    Averages(unsigned int RDF_size_,unsigned int RDP_size_,double diameter_)
    {
      RDF_size = RDF_size_;
      RDP_size = RDP_size_;
      diameter = diameter_;
      RDP_h = 2;RDF_h = 0.05;angle_h = 0.25;

      //RDP
      x = new double[RDP_size];
      Density_all = new double[RDP_size];
      Density_Si = new double[RDP_size];
      Density_O = new double[RDP_size];
      for(unsigned int i = 1;i < RDP_size;i++)
        {
          x[i]          = i * 0.1;
          Density_all[i]= 0;
          Density_Si[i] = 0;
          Density_O[i]  = 0;
        } 

      //RDF
      r = new double[RDF_size];
      RDF_all = new double[RDF_size];
      RDF_Si = new double[RDF_size];
      RDF_O = new double[RDF_size];
      RDF_SiO = new double[RDF_size];
      for(unsigned int i = 1;i < RDF_size ;i++)
        {
          r[i]          = i * 0.01;
          RDF_all[i]    = 0;
          RDF_Si[i]     = 0;
          RDF_O [i]     = 0;
          RDF_SiO[i]    = 0;
        }

      //BAD
      unsigned int j = 0;
      for(double i = 1;i < 180.5;i = i + 0.5)
        {
          OSiO[0][j] = i;
          OSiO[1][j] = 0;
          SiOSi[0][j] = i;
          SiOSi[1][j] = 0;
          j = j + 1;
        }  
    } 
    void store_Energy(unsigned int steps_, double Energy_)
    {
      steps.push_back(steps_);
      Energy.push_back(Energy_);
    }
    void store_AveragesCalculation(const Configuration& config);
    void EnergyDataWriter();
    void DensityDataWriter(unsigned int mean); 
    void RDFWriter(unsigned int mean,unsigned int N,unsigned N_si,unsigned N_o);   
    void PositionWriter(const Configuration & config);
    inline double norm(double x,double y,double z)
    {
      return sqrt(x*x+y*y+z*z);
    }
    ~Averages()
    {
      delete[] x;
      delete[] Density_all;
      delete[] Density_Si;
      delete[] Density_O;

      delete[] r;
      delete[] RDF_all;
      delete[] RDF_Si;
      delete[] RDF_O;
      delete[] RDF_SiO;
    }
};

#endif
