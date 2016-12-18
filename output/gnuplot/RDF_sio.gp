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
set style line 1 lt 1 lw 3
set style line 2 lt 2 lw 3
set style line 3 lt 3 lw 3

plot 	"../data/RDF.dat" using 1:5  title "T = 300 K and P = 0 GPa" with line lt 1 lc 1 lw 3

set title "Silicon-Oxygen" font "arial,24"
set xlabel "r (Å)" font "arial,22"
set ylabel "RDF G_{Si-O}(r)" font "arial,22"
set xtics font "arial,18"
set xtics font "arial,18"
set terminal png font arial 22 size 1024,768
set output "../graph/RDF_sio.png"
replot

