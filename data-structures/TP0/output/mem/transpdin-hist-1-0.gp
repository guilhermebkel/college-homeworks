set term postscript eps color 14
set output "../output/mem/transpdin-hist-1-0.eps"
set style fill solid 1.0
set title "Distancia de Pilha (Total 415 # 45 Media 9.22) - Fase  1 - ID 0"
set xlabel "Distancia"
set ylabel "Frequencia"
plot [-1:25] "../output/mem/transpdin-hist-1-0.gpdat" u 3:4 w boxes t ""
