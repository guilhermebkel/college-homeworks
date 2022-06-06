set term postscript eps color 14
set output "../data/memory-log-hist-1-3.eps"
set style fill solid 1.0
set title "Distancia de Pilha (Total 650 # 290 Media 2.24) - Fase  1 - ID 3"
set xlabel "Distancia"
set ylabel "Frequencia"
plot [-1:6] "../data/memory-log-hist-1-3.gpdat" u 3:4 w boxes t ""
