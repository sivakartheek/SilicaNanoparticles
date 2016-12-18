#include "Configuration.h"
#include<cmath>
#include<iostream>

using namespace std;

Configuration::Configuration(unsigned int N_, unsigned int N_si_, unsigned int N_o_, double* r_)
{
  N = N_;
  N_si = N_si_;
  N_o = N_o_;
  r = new double[N*4];    
  for(unsigned int i = 0;i < N * 4;i = i + 4)
    {
      r[0+i] = r_[0+i]; 
      r[1+i] = r_[1+i]; 
      r[2+i] = r_[2+i]; 
      r[3+i] = r_[3+i]; 
    }
}

Configuration::Configuration(const Configuration& config)
{
  N = config.N;
  N_si = config.N_si;
  N_o = config.N_o;
  r = new double[N*4];  
  for(unsigned int i = 0;i < N * 4;i = i + 4)
    {
      r[0+i] = config.r[0+i]; 
      r[1+i] = config.r[1+i]; 
      r[2+i] = config.r[2+i]; 
      r[3+i] = config.r[3+i]; 
    }
}

Configuration& Configuration::operator=(const Configuration& config)
{
  for(unsigned int i = 0;i < N * 4;i = i + 4)
    {
      r[0+i] = config.r[0+i]; 
      r[1+i] = config.r[1+i]; 
      r[2+i] = config.r[2+i]; 
      r[3+i] = config.r[3+i]; 
    }
  return *this;
}

void Configuration::ChangePosition(unsigned int P)
{
  r[P+0] += 0.075*(2*Rand_DOUBLE()-1); 
  r[P+1] += 0.075*(2*Rand_DOUBLE()-1);
  r[P+2] += 0.075*(2*Rand_DOUBLE()-1);
}


void Configuration::print_position()
{
  for(unsigned int i = 0;i < N * 4;i = i + 4)
    {
      cout << i <<" "<< r[0+i] <<" "<< r[1+i] <<" "<< r[2+i] <<" "<< r[3+i] << endl;
    }
}

void Configuration::print_particle_count()
{
  std::cout <<"Total number of atoms in the system = "<< N << std::endl;
  std::cout <<"Number of silicon atoms = "<< N_si << std::endl;
  std::cout <<"Number of oxygen atoms = "<< N_o << std::endl;
}
