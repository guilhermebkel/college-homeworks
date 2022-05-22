set term postscript eps color 14
set output "../output/mem/multdin-acesso-2.eps"
set title "Grafico de acesso - ID 2"
set xlabel "Acesso"
set ylabel "Endereco"
plot "../output/mem/multdin-acesso-0-2.gpdat" u 2:4 w points t "L", "../output/mem/multdin-acesso-1-2.gpdat" u 2:4 w points t "E"
