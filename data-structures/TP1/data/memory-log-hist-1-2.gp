set term postscript eps color 14
set output "../data/memory-log-hist-1-2.eps"
set style fill solid 1.0
set title "Distancia de Pilha (Total 395 # 95 Media 4.16) - Fase  1 - ID 2"
set xlabel "Distancia"
set ylabel "Frequencia"
plot [-1:18] "../data/memory-log-hist-1-2.gpdat" u 3:4 w boxes t ""
