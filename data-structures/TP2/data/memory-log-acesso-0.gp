set term postscript eps color 14
set output "../data/memory-log-acesso-0.eps"
set title "Grafico de acesso - ID 0"
set xlabel "Acesso"
set ylabel "Endereco"
plot "../data/memory-log-acesso-0-0.gpdat" u 2:4 w points t "L", "../data/memory-log-acesso-1-0.gpdat" u 2:4 w points t "E"
