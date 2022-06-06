set term postscript eps color 14
set output "../data/memory-log-distp-2.eps"
set title "Evolucao Distancia de Pilha - ID 2"
set xlabel "Acesso"
set ylabel "Distancia de Pilha"
plot "../data/memory-log-acesso-2-2.gpdat" u 2:5 w impulses t ""
