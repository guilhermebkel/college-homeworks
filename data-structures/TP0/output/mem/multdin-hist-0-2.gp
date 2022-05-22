set term postscript eps color 14
set output "../output/mem/multdin-hist-0-2.eps"
set style fill solid 1.0
set title "Distancia de Pilha (Total 0 # 25 Media 0.00) - Fase  0 - ID 2"
set xlabel "Distancia"
set ylabel "Frequencia"
plot [-1:1] "../output/mem/multdin-hist-0-2.gpdat" u 3:4 w boxes t ""
