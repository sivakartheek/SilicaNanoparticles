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
plot "../data/RadialDensity.dat" using 1:2  title "All" with line ls 1 , "../data/RadialDensity.dat" using 1:3  title "Oxygen" with line ls 3 , "../data/RadialDensity.dat" using 1:4  title "Silicon" with line ls 2
set yrange [0.0:0.12]
set title "SiO{_2} nanoparticle" font "arial,25"
set xtics font "arial,18"
set xtics font "arial,18"
set xlabel " r(Å)"  font "arial,22"
set ylabel "Atom number density {/Symbol r}(r) in (Number/Å^{3}) " font "arial,22"
set terminal png font arial 22 size 1024,768
set output "../graph/Density_profile.png"
replot

