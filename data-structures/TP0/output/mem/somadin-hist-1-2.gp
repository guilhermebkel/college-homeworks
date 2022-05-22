set term postscript eps color 14
set output "../output/mem/somadin-hist-1-2.eps"
set style fill solid 1.0
set title "Distancia de Pilha (Total 625 # 75 Media 8.33) - Fase  1 - ID 2"
set xlabel "Distancia"
set ylabel "Frequencia"
plot [-1:26] "../output/mem/somadin-hist-1-2.gpdat" u 3:4 w boxes t ""
