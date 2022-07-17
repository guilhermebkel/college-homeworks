set term postscript eps color 14
set output "../data/memlog/output-hist-0-0.eps"
set style fill solid 1.0
set title "Distancia de Pilha (Total 15 # 11 Media 1.36) - Fase  0 - ID 0"
set xlabel "Distancia"
set ylabel "Frequencia"
plot [-1:5] "../data/memlog/output-hist-0-0.gpdat" u 3:4 w boxes t ""
