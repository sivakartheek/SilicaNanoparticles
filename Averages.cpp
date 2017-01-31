#include "Averages.h"
#include "Configuration.h"
#include<vector>
#include<fstream>
#include<iostream>


// Computes the Radial distribution and density function for the given
// atomic coordinatoes and stores them.
void Averages::store_AveragesCalculation(const Configuration& config)
{
  const double Pi = 3.1415926536;
  double V = (4/3)*Pi*pow(diameter*0.5,3);

  // center position (x,y,z) of the particle
  double x_ = 0,y_ = 0,z_ = 0;
  for(unsigned int i = 0;i < config.N * 4;i = i + 4)
    {
      x_ += config.r[0+i]/config.N;
      y_ += config.r[1+i]/config.N;
      z_ += config.r[2+i]/config.N;          
    }

  // 1. Density profile
  for(unsigned int i = 1;i < RDP_size;i++)
    {
      unsigned int N_All = 0,N_Si = 0,N_O = 0;
      double rij = 0;
      for(unsigned int j = 0;j < config.N * 4;j = j + 4)
        {
          rij = norm(config.r[0+j] - x_, config.r[1+j] - y_, config.r[2+j] - z_);

          if(rij <= x[i] + (RDP_h/2) && rij > x[i] - (RDP_h/2)) //Total
            {
              N_All = N_All + 1;
            }
          if(rij <= x[i] + (RDP_h/2) && rij > x[i] - (RDP_h/2) && config.r[3+j] == config.q1 ) //Silicon
            {
              N_Si = N_Si + 1;
            }
          else if(rij <= x[i] + (RDP_h/2) && rij > x[i] - (RDP_h/2) && config.r[3+j] == config.q2 )//Oxygen
            {
              N_O = N_O + 1;
            }
        }

      Density_all[i] += N_All / (4 * Pi * x[i] * x[i] * RDP_h);
      Density_O[i]   += N_O  / (4 * Pi * x[i] * x[i] * RDP_h);
      Density_Si[i]  += N_Si  / (4 * Pi * x[i] * x[i] * RDP_h);
    }

  // 2. Radial Distribution Function
  for(unsigned int i = 1;i < RDF_size;i++)
    {
      unsigned int N_All = 0,N_Si = 0,N_O = 0,N_SiO = 0;
      double rij = 0;
      for(unsigned int j = 0;j < (config.N * 4) - 4 ;j = j + 4)
        {
          for(unsigned int k = j + 4;k < (config.N * 4) ;k = k + 4)
            {
              rij = norm(config.r[0+j]-config.r[0+k], config.r[1+j]-config.r[1+k], config.r[2+j]-config.r[2+k]);
              if(rij <= r[i] + (RDF_h/2) && rij > r[i] - (RDF_h/2) )
              {
                N_All += 1;
              }
              if(rij <= r[i] + (RDF_h/2) && rij > r[i] - (RDF_h/2) && config.r[k+3] == config.r[j+3] && config.r[k+3] == config.q2)
              {
                N_O += 1;
              }
              if(rij <= r[i] + (RDF_h/2) && rij > r[i] - (RDF_h/2) && config.r[k+3] == config.r[j+3] && config.r[k+3] == config.q1 )
              {
                N_Si += 1;
              }
              if(rij <= r[i] + (RDF_h/2) && rij > r[i] - (RDF_h/2) && config.r[k+3] != config.r[j+3] && config.r[k+3] != config.q2)
              {
                N_SiO += 1;
              }
            }
        }

      RDF_all[i] += 2 * N_All  / ( (config.N/V) * 4 * Pi * r[i] * r[i] *  RDF_h);
      RDF_Si[i]  += 2 * N_Si  / ( (config.N_si/V) * 4 * Pi * r[i] * r[i] *  RDF_h);
      RDF_O [i]  += 2 * N_O   / ( (config.N_o/V) * 4 * Pi * r[i] * r[i] *  RDF_h);
      RDF_SiO[i] += 2 * N_SiO / ( (config.N_o/V) * 4 * Pi * r[i] * r[i] *  RDF_h);
    }
     
}

// Stores the energy of the system in Energy.dat file
void Averages::EnergyDataWriter()
{
  ofstream outfile("output/data/Energy.dat");
  if(!outfile.is_open())
    {
      cout << "Error Opening file - Cannot open file!" << endl;
    }
  for(unsigned int i = 0; i < steps.size(); ++i)
    { 
      outfile << steps[i] <<"  "<< Energy[i]<< "\n";
    }
  outfile.close();
  outfile.clear(); 
}


// Stores the radial density function of the system in RadialDensity.dat file
void Averages::DensityDataWriter(unsigned int mean)
{
  ofstream outfile("output/data/RadialDensity.dat");
  if(!outfile.is_open())
    {
      cout << "Error Opening file - Cannot open file!" << endl;
    }
  for(unsigned int i = 0; i < RDP_size; ++i)
    { 
      outfile << x[i] <<" \t "<< Density_all[i]/mean <<" \t "<< Density_O[i]/mean <<" \t "<< Density_Si[i]/mean << "\n";
    }
  outfile.close();
  outfile.clear(); 
}

// Stores the radial distribution function of the system in RDF.dat file
void Averages::RDFWriter(unsigned int mean,unsigned int N,unsigned int N_si,unsigned int N_o)
{
  ofstream outfile("output/data/RDF.dat");
  if(!outfile.is_open())
    {
      cout << "Error Opening file - Cannot open file!" << endl;
    }
  for(unsigned int i = 0; i < RDF_size; ++i)
    { 
      outfile << r[i] <<" \t "<< RDF_all[i]/(mean*N) <<" \t "<< RDF_Si[i]/(mean*N_si) <<" \t "<< RDF_O[i]/(mean*N_o) <<" \t "<< RDF_SiO[i]/(mean*N_o) << "\n";
    }
  outfile.close();
  outfile.clear(); 
}

// Stores the final atomic coordinates in the position.dat file
void Averages::PositionWriter(const Configuration & config)
{
  ofstream outfile("output/data/Position.dat");
  if(!outfile.is_open())
    {
      cout << "Error Opening file - Cannot open file!" << endl;
    }
  for(unsigned int i = 0; i < config.N * 4; i = i + 4)
    { 
      outfile << config.r[i+0] <<" \t "<< config.r[i+1] <<" \t "<< config.r[i+2] <<" \t "<< config.r[i+3] << "\n";
    } 
}
