#ifndef CONFIGURATION_H
#define CONFIGURATION_H
#include<cmath>
#include<cstdlib>



class Configuration
{
  private:
    unsigned int N, N_si, N_o;
    double q1, q2;
    double* r;
    friend double BKS(const Configuration& config,unsigned int i);
    friend double BKS_total(const Configuration& config);
    friend class Averages;
  public:
    Configuration(unsigned int N_, unsigned int N_si_, unsigned int N_o_, double* r_, double q1, double q2);
    Configuration(const Configuration& config);
    Configuration& operator=(const Configuration& config);
    void ChangePosition(unsigned int P);
    void print_position();
    void print_particle_count();
    inline double Rand_DOUBLE() //(0,1)
    {
      return (double) rand() / (double) RAND_MAX;
    }
    ~Configuration()
    {
      delete[] r;
    }
};

#endif
