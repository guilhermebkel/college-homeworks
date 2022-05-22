set term postscript eps color 14
set output "../output/mem/multdin-distp-1.eps"
set title "Evolucao Distancia de Pilha - ID 1"
set xlabel "Acesso"
set ylabel "Distancia de Pilha"
plot "../output/mem/multdin-acesso-2-1.gpdat" u 2:5 w impulses t ""
