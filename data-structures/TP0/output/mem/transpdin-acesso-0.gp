set term postscript eps color 14
set output "../output/mem/transpdin-acesso-0.eps"
set title "Grafico de acesso - ID 0"
set xlabel "Acesso"
set ylabel "Endereco"
plot "../output/mem/transpdin-acesso-0-0.gpdat" u 2:4 w points t "L", "../output/mem/transpdin-acesso-1-0.gpdat" u 2:4 w points t "E"
