reset

set data style lines

plot 'bench.txt' using 1

pause -1 "Hit return to continue"

plot 'bench.txt' index 1

pause -1 "Hit return to continue"

plot 'bench.txt'   using 2 title "model", '' using 3 title "localmap", '' using 4 title "gmap", '' using 5 title"view"

pause -1 "Hit return to continue"

set xrange [400:800]
replot


# set style data histogram
# set style histogram rowstacked
# set style fill solid border -1
# set boxwidth 0.2
# 
# plot 'bench.txt'   using 2 title "model", '' using 3 title "localmap", '' using 4 title "gmap", '' using 5 title"view"

