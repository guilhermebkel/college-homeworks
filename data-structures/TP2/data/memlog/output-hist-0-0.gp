set term postscript eps color 14
set output "../data/memlog/output-hist-0-0.eps"
set style fill solid 1.0
set title "Distancia de Pilha (Total 1930 # 693 Media 2.78) - Fase  0 - ID 0"
set xlabel "Distancia"
set ylabel "Frequencia"
plot [-1:6] "../data/memlog/output-hist-0-0.gpdat" u 3:4 w boxes t ""
