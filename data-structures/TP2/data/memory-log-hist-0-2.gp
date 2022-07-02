set term postscript eps color 14
set output "../data/memory-log-hist-0-2.eps"
set style fill solid 1.0
set title "Distancia de Pilha (Total 22 # 14 Media 1.57) - Fase  0 - ID 2"
set xlabel "Distancia"
set ylabel "Frequencia"
plot [-1:4] "../data/memory-log-hist-0-2.gpdat" u 3:4 w boxes t ""
