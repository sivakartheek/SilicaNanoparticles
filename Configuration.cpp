#include "Configuration.h"
#include<cmath>
#include<iostream>

using namespace std;

// Constructor to initialize the variables in the silica nanoparticle system
Configuration::Configuration(unsigned int N_, unsigned int N_si_, unsigned int N_o_, double* r_, double q1_, double q2_)
{
  N = N_;
  N_si = N_si_;
  N_o = N_o_;
  q1 = q1_;
  q2 = q2_;
  r = new double[N*4];    
  for(unsigned int i = 0;i < N * 4;i = i + 4)
    {
      r[0+i] = r_[0+i]; 
      r[1+i] = r_[1+i]; 
      r[2+i] = r_[2+i]; 
      r[3+i] = r_[3+i]; 
    }
}

// Copy constructor
Configuration::Configuration(const Configuration& config)
{
  N = config.N;
  N_si = config.N_si;
  N_o = config.N_o;
  q1 = config.q1;
  q2 = config.q2;
  r = new double[N*4];  
  for(unsigned int i = 0;i < N * 4;i = i + 4)
    {
      r[0+i] = config.r[0+i]; 
      r[1+i] = config.r[1+i]; 
      r[2+i] = config.r[2+i]; 
      r[3+i] = config.r[3+i]; 
    }
}

// Copies the atomic cooridnates from one to another.
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

// Randomly moves the atom
void Configuration::ChangePosition(unsigned int P)
{
  r[P+0] += 0.075*(2*Rand_DOUBLE()-1); 
  r[P+1] += 0.075*(2*Rand_DOUBLE()-1);
  r[P+2] += 0.075*(2*Rand_DOUBLE()-1);
}

// Prints the atomic coordinates
void Configuration::print_position()
{
  for(unsigned int i = 0;i < N * 4;i = i + 4)
    {
      cout << i <<" "<< r[0+i] <<" "<< r[1+i] <<" "<< r[2+i] <<" "<< r[3+i] << "\n";
    }
}

// Prints the number of silicon and oxygen atoms in the system
void Configuration::print_particle_count()
{
  std::cout <<"Total number of atoms in the system = "<< N << "\n";
  std::cout <<"Number of silicon atoms = "<< N_si << "\n";
  std::cout <<"Number of oxygen atoms = "<< N_o << "\n";
}
