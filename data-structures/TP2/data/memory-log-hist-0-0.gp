set term postscript eps color 14
set output "../data/memory-log-hist-0-0.eps"
set style fill solid 1.0
set title "Distancia de Pilha (Total 1 # 3 Media 0.33) - Fase  0 - ID 0"
set xlabel "Distancia"
set ylabel "Frequencia"
plot [-1:2] "../data/memory-log-hist-0-0.gpdat" u 3:4 w boxes t ""
