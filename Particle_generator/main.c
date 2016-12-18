#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>

int N = 192000 ;//65856;//1536;//192//5184;
int dim = 3;
double q1 =  2.4;
double q2 = -1.2; 


double norm(double x,double y,double z)
{
  return sqrt(x*x+y*y+z*z);
}

int main()
{
  //Particle Diamter 'C' in angstrom
  double c = 0;FILE *fp = fopen("melt_structure/Particle_Diameter_in_angstrom.txt","r+");fscanf(fp,"%lf",&c);fclose(fp);

  //Bulk silica Length 'l' in angstrom
  double l;fp = fopen("melt_structure/length.txt","r+");fscanf(fp,"%lf",&l);fclose(fp);

  double r[4][N];

  int count = 0;
  int si = 0;
  int o = 0;
  fp = fopen("melt_structure/position.txt","r+");
  FILE* outfile = fopen("../inputs/position.txt","w+");
  for(int i = 0;i < N;i++)
    {
      fscanf(fp,"%lf %lf %lf %lf",&r[0][i],&r[1][i],&r[2][i],&r[3][i]);
      if( norm(r[0][i]-(l/2),r[1][i]-(l/2),r[2][i]-(l/2)) < c * 0.5 )
        {
          count += 1;       
          if(r[3][i] > q1 || r[3][i] == q1)
            {
              si += 1;
              fprintf(outfile,"%f %f %lf %f \n",r[0][i],r[1][i],r[2][i],2.4);
            }
          if(r[3][i] < q2 || r[3][i] == q2)
            {
              o += 1;
              fprintf(outfile,"%f %f %lf %f \n",r[0][i],r[1][i],r[2][i],-1.2);
            }         
        }
    }
  fclose(fp);

  FILE *atom = fopen("../inputs/Number.txt","w+");
  fprintf(atom,"%i %i %i %i",count,si,o, si+o);

  printf("\n SiO2 spherical nanoparticles are generated in the inputs folder: position.txt and Number.txt files \n \n ");

  return 0;
}








