set term postscript eps color 14
set output "../data/memory-log-hist-1-0.eps"
set style fill solid 1.0
set title "Distancia de Pilha (Total 41 # 28 Media 1.46) - Fase  1 - ID 0"
set xlabel "Distancia"
set ylabel "Frequencia"
plot [-1:4] "../data/memory-log-hist-1-0.gpdat" u 3:4 w boxes t ""
