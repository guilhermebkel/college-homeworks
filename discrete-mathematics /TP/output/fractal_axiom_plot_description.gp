set terminal png
set output './output/fractal.png'
set xrange [-10:10]
set yrange [-10:10]
set yzeroaxis
set xzeroaxis
unset key


# Coordenadas da linha 1
x1 = -10
y1 = -10
x2 = -10
y2 = 0

# Coordenadas da linha 2
x3 = 0
y3 = 0
x4 = 5
y4 = -5

plot x, x1 + (x2 - x1)/(y2 - y1)*(x - y1)
