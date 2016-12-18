#!/bin/sh

cd Particle_generator/
make
./main
cd ../
make clean
echo 'Compiling'
make
echo 'Exectuing'
./main
make -C output/gnuplot
clear
echo 'The averages of the properties of interest are ploted in output/graph folder using Gnuplot. Please check it'
