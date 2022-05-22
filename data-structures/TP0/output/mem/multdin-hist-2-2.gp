set term postscript eps color 14
set output "../output/mem/multdin-hist-2-2.eps"
set style fill solid 1.0
set title "Distancia de Pilha (Total 625 # 50 Media 12.50) - Fase  2 - ID 2"
set xlabel "Distancia"
set ylabel "Frequencia"
plot [-1:26] "../output/mem/multdin-hist-2-2.gpdat" u 3:4 w boxes t ""
