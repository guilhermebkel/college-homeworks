set term postscript eps color 14
set output "../output/mem/somadin-distp-0.eps"
set title "Evolucao Distancia de Pilha - ID 0"
set xlabel "Acesso"
set ylabel "Distancia de Pilha"
plot "../output/mem/somadin-acesso-2-0.gpdat" u 2:5 w impulses t ""
