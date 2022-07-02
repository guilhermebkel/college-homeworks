set term postscript eps color 14
set output "../data/memlog/output-acesso-3.eps"
set title "Grafico de acesso - ID 3"
set xlabel "Acesso"
set ylabel "Endereco"
plot "../data/memlog/output-acesso-0-3.gpdat" u 2:4 w points t "L", "../data/memlog/output-acesso-1-3.gpdat" u 2:4 w points t "E"
