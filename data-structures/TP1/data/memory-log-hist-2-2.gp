set term postscript eps color 14
set output "../data/memory-log-hist-2-2.eps"
set style fill solid 1.0
set title "Distancia de Pilha (Total 327 # 89 Media 3.67) - Fase  2 - ID 2"
set xlabel "Distancia"
set ylabel "Frequencia"
plot [-1:9] "../data/memory-log-hist-2-2.gpdat" u 3:4 w boxes t ""
