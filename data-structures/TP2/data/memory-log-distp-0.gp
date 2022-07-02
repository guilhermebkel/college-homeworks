set term postscript eps color 14
set output "../data/memory-log-distp-0.eps"
set title "Evolucao Distancia de Pilha - ID 0"
set xlabel "Acesso"
set ylabel "Distancia de Pilha"
plot "../data/memory-log-acesso-2-0.gpdat" u 2:5 w impulses t ""
