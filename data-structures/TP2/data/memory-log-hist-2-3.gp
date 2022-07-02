set term postscript eps color 14
set output "../data/memory-log-hist-2-3.eps"
set style fill solid 1.0
set title "Distancia de Pilha (Total 79 # 36 Media 2.19) - Fase  2 - ID 3"
set xlabel "Distancia"
set ylabel "Frequencia"
plot [-1:6] "../data/memory-log-hist-2-3.gpdat" u 3:4 w boxes t ""
