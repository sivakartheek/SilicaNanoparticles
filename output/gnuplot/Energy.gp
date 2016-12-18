set terminal png enhanced
set terminal postscript enhanced
set terminal postscript eps enhanced
set term postscript enhanced color
set output "colorindex.ps"
set key box lw 4
set key height 1
set border lw 4
set grid
set lmargin at screen 0.19
set style line 1 linecolor rgb '#0060ad' linetype 1 linewidth 2.5  # blue
plot "../data/Energy.dat"  title "T = 300 K and P = 0 GPa" with linespoints ls 1
set title "Total Potential Energy"  font "arial,24"
set xlabel "MC-steps" font "arial,22"
set xrange [0:5000000]
set ylabel "Potential energy (in eV)" font "arial,22"
set xtics font "arial,18"
set xtics font "arial,18"
set terminal png font arial 22 size 1024,768
set output "../graph/Energy.png"
replot

