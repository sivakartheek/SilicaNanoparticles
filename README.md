# Silica Nanoparticle model

The structural properties  of the silica nanoparticles are determined numerically using the Metropolis Monte Carlo technique. The interactions between Si and O in the silica were modeled using the BKS interatomic potential (Proposed by Beest, Krammer and van Saten), which has long-range Coulomb and short-range Buckingham potentials. Free boundary condition was employed to simulate the nanoparticles with free surfaces. Since the simulation is non-periodic, Ewald summation is no more applicable for the calculation of long-range interactions. Instead a double over all pairs of atoms are implemented. The program was tested up to particle diameter 10 nm. Here we present the results for particle diameter 4nm.

## 1. Potential energy versus Monte Carlo steps
![alt tag](https://raw.githubusercontent.com/NaveenKaliannan/SilicaNanoparticles/master/output/graph/Energy.png)
The solution reaches equlibirum slowly after 4 million MC steps. The averages of the properties were taken from the final 1 million MC steps at regular 1000 intervals.

## 2. Radial distribution function
#### First peak  Si - O  Bond length  = 1.6 angstrom
#### Second peak O  - O  Bond length  = 2.6 angstrom
#### Third peak  Si - Si Bond length = 3.1 angstrom

![alt tag](https://raw.githubusercontent.com/NaveenKaliannan/SilicaNanoparticles/master/output/graph/Total_RDF.png
)

## 3. Radial number density function
#### Si     - 0.02 per cc angstrom
#### O      - 0.04 per cc angstrom
The ratio between oxygen and silicon number density is 2, which is the expected value.

![alt tag](https://raw.githubusercontent.com/NaveenKaliannan/SilicaNanoparticles/master/output/graph/Density_profile.png)
