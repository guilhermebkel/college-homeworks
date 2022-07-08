set term postscript eps color 14
set output "../data/memlog/output-hist-2-2.eps"
set style fill solid 1.0
set title "Distancia de Pilha (Total 4472 # 324 Media 13.80) - Fase  2 - ID 2"
set xlabel "Distancia"
set ylabel "Frequencia"
plot [-1:29] "../data/memlog/output-hist-2-2.gpdat" u 3:4 w boxes t ""
