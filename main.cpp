// A Metropolis Monte Carlo program for silica nanoparticles.
// The program uses free boundary conditions and BKS interatomic
// potential(proposed by Beest, Kramer and Van Saten).The methodology
// used in this algorithm and detailed explaination of the model is 
// explained in the paper (thesis in the link): 
//https://www.researchgate.net/publication/311138439_A_study_on_the_structure_and_properties_of_silica_glass_and_silica_nanoparticles_via_Monte_Carlo_simulations

// The algorithm provides the structural information for given silica
// particle size (angstrom) and temperature (in Kelvin)

// author: Naveen Kumar Kaliannan


#include<iostream>
#include <iomanip>  
#include<fstream>
#include<cstdlib>
#include<vector>
#include<cmath>
#include <ctime>

#include "Numerical.h"
#include "Configuration.h"
#include "Averages.h"


using namespace std;

//Constants
const double Pi = 3.1415926536;
const unsigned int dim = 3;// 3 spacial dimension
const double Unit_LJ = 96.49930; //(eV to KJ per mol unit conversion)
const double Unit_C = 1389.552281;
const double R = 0.0083144; // Gas constant
const double Temp     = 300;//300 in Kelvin
const unsigned int iter = 5000000; // maximum number of iterations
const double q1 = +2.4; //Silicon charge
const double q2 = -1.2; //Oxyegn charge

//Buckingham + Coloumb potentials (Total system)
double BKS_total(const Configuration& config)
{
  double u_BKS = 0;
  double rij  = 0;

  for(unsigned int i = 0;i < config.N * 4 - 4;i = i + 4)
    {
      for(unsigned int j = i + 4;j < config.N * 4;j = j + 4)
        {
          rij = norm(config.r[0+i]-config.r[0+j],config.r[1+i]-config.r[1+j],config.r[2+i]-config.r[2+j]);
          if(rij < 60 && i !=  j)//Potential truncation
            {
              if(config.r[i+3] == config.r[j+3] && config.r[i+3] == config.q1 )//Silicon - Silicon
                {
                  u_BKS += (1389.552 * (config.r[3+i] * config.r[3+j] / rij));
                }
              else if(config.r[i+3] == config.r[j+3] && config.r[i+3] == config.q2 )//Oxygen - Oxygen
                {
                  u_BKS += ((134015.6224*exp(-rij*2.7600)) - (16887.3775/pow(rij,6.0))) +   (1389.552 * config.r[3+i] * config.r[3+j] / rij);
                }
              else if(config.r[i+3] != config.r[j+3]) //Silica - Oxygen
                {
                  u_BKS += ((1737349.967*exp(-rij*4.87318)) - (12599.51795/pow(rij,6.0))) +  (1389.552 *  config.r[3+i] * config.r[3+j] / rij);
                }
           }
        }
    }

  return u_BKS*2;
}


//Buckingham + Coloumb potentials (single pair)
double BKS(const Configuration& config,unsigned int i)
{
  double u_BKS = 0;
  double rij  = 0;

  for(unsigned int j = 0;j < config.N * 4;j = j + 4)
    {
      rij = norm(config.r[0+i]-config.r[0+j],config.r[1+i]-config.r[1+j],config.r[2+i]-config.r[2+j]);
      if(rij < 60 && i !=  j)//Potential truncation
        {
          if(config.r[i+3] == config.r[j+3] && config.r[i+3] == config.q1 )//Silicon - Silicon
            {
              u_BKS += (1389.552 * config.r[3+i] * config.r[3+j] / rij);
            }
          else if(config.r[i+3] == config.r[j+3] && config.r[i+3] == config.q2 )//Oxygen - Oxygen
            {
              u_BKS += ((134015.6224*exp(-rij*2.7600)) - (16887.3775/pow(rij,6))) + (1389.552 * config.r[3+i] * config.r[3+j] / rij);
            }
          else if(config.r[i+3] != config.r[j+3]) //Silica - Oxygen
            {
              u_BKS += ((1737349.967*exp(-rij*4.87318)) - (12599.51795/pow(rij,6))) +  (1389.552 * config.r[3+i] * config.r[3+j] / rij);
            }
        }
    }

  return u_BKS;
}




int main()
{
  //Particle size
  double diameter = 0;
  ifstream infile("Particle_generator/melt_structure/Particle_Diameter_in_angstrom.txt");
  infile >> diameter;
  cout << "Diameter of the particle (in angstrom) = " << diameter << endl;
  infile.close();
  infile.clear();
  //Particle diameter constraint
  if(diameter < 10 || diameter > 100)
    {
      cerr << "Particle diameter constraint (diameter > 10 && diameter < 100)" << endl;
      exit(1);
    }
  
  //Si, O atom counts
  unsigned int N = 0, N_si = 0, N_o = 0;
  infile.open("inputs/Number.txt");
  infile >> N >> N_si >> N_o;
  infile.close();
  infile.clear();

  //atomic coordinates
  double* r = new double[N*4];
  infile.open("inputs/position.txt");
  for(unsigned int i = 0;i < N * 4;i = i + 4)
    {
      infile >> r[0+i] >> r[1+i] >> r[2+i] >> r[3+i];
    }
  infile.close();
  infile.clear();


  Configuration config_old (N, N_si, N_o, r, q1, q2);  delete[] r;  
  Configuration config_new (config_old);
  Averages average(600,diameter*8,diameter);

  srand (time(NULL));
  unsigned int P, Mean;
  double delta_U  = 0, weight = 0,temp  = 0, temp1 = 0;
  cout<<"No. of Iter."<<"\t Total P.E of the system (in eV)"<<"\t Potential energy change (in %)"<<endl;

  for(unsigned int i = 0;i <= (iter);++i)
    {
      //1. Select a new atom in the configuration
      P =  Rand_INT(0,N) * 4;

      //2. Change the selected atom position
      config_new.ChangePosition(P);

      //3. Calculate the potential energy change which results from the atomic displacement
      delta_U = BKS(config_new,P) - BKS(config_old,P);
     
      //4. Metropolis creterion -  new configuration is accepted based on the minimum condition
      weight = exp(-delta_U/(R * Temp));
      if(min(1,weight) >= Rand_DOUBLE())//-> minimum condition
        {
          config_old = config_new; 
        }
      else
        {
          config_new = config_old; 
        }  

      //The total potential energy of the system (in eV) is printed for every 100000 steps to observe the convergence.
      if(i%100000 == 0) 
        {
          temp1 = BKS_total(config_new)/96.49930; 
          cout<<i<<"\t \t \t"<<temp1<<"\t\t\t\t"<<abs(temp1-temp)*100/max(abs(temp1),abs(temp))<<endl;
          temp = temp1;
        }

      //The averages of the properties of the interest are computed in this loop.
      if(i%300000 == 0) 
        {
          Mean += 1;
          average.store_Energy(i, temp);
          average.store_AveragesCalculation(config_new);
        }
    }
  average.EnergyDataWriter();
  average.DensityDataWriter(Mean);
  average.RDFWriter(Mean,N,N_si,N_o);
  average.PositionWriter(config_new);

  return 0;
}
