set style data lines

set logscale y
set terminal png
set output "harmony.png"

set format y "10^{%L}"

plot "e-harmony.dat"