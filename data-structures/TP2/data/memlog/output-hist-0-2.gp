set term postscript eps color 14
set output "../data/memlog/output-hist-0-2.eps"
set style fill solid 1.0
set title "Distancia de Pilha (Total 3553 # 1034 Media 3.44) - Fase  0 - ID 2"
set xlabel "Distancia"
set ylabel "Frequencia"
plot [-1:6] "../data/memlog/output-hist-0-2.gpdat" u 3:4 w boxes t ""
