reset
set ylabel 'time(sec)'
set xlabel 'N nodes'
set style fill solid
set title 'perfomance comparison'
set term png enhanced font 'Verdana,10'
set output 'runtime.png'

plot "bubble.txt" using 1:2 smooth bezier title "bubble", \
"merge.txt" using 1:2 smooth bezier title "merge"
