set term postscript eps color 14
set output "../output/mem/multdin-hist-1-2.eps"
set style fill solid 1.0
set title "Distancia de Pilha (Total 725 # 175 Media 4.14) - Fase  1 - ID 2"
set xlabel "Distancia"
set ylabel "Frequencia"
plot [-1:26] "../output/mem/multdin-hist-1-2.gpdat" u 3:4 w boxes t ""
