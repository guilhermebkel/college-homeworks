set term postscript eps color 14
set output "../output/mem/transpdin-hist-0-0.eps"
set style fill solid 1.0
set title "Distancia de Pilha (Total 0 # 25 Media 0.00) - Fase  0 - ID 0"
set xlabel "Distancia"
set ylabel "Frequencia"
plot [-1:1] "../output/mem/transpdin-hist-0-0.gpdat" u 3:4 w boxes t ""
