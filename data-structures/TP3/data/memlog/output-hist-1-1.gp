set term postscript eps color 14
set output "../data/memlog/output-hist-1-1.eps"
set style fill solid 1.0
set title "Distancia de Pilha (Total 62 # 20 Media 3.10) - Fase  1 - ID 1"
set xlabel "Distancia"
set ylabel "Frequencia"
plot [-1:8] "../data/memlog/output-hist-1-1.gpdat" u 3:4 w boxes t ""
