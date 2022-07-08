set term postscript eps color 14
set output "../data/memlog/output-distp-3.eps"
set title "Evolucao Distancia de Pilha - ID 3"
set xlabel "Acesso"
set ylabel "Distancia de Pilha"
plot "../data/memlog/output-acesso-2-3.gpdat" u 2:5 w impulses t ""
