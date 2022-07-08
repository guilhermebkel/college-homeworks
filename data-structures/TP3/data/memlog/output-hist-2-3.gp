set term postscript eps color 14
set output "../data/memlog/output-hist-2-3.eps"
set style fill solid 1.0
set title "Distancia de Pilha (Total 22 # 12 Media 1.83) - Fase  2 - ID 3"
set xlabel "Distancia"
set ylabel "Frequencia"
plot [-1:6] "../data/memlog/output-hist-2-3.gpdat" u 3:4 w boxes t ""
