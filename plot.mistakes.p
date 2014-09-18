reset
algorithm1="perceptron"
algorithm2="passiveAgressive"
data1="training"
data2="validation"
set output "result.png"
#set title "Online learning curve for perceptron and PA algorithm"
set xlabel "training iteration"
set ylabel "mistake count"
set term png size 1024,1024
#set logscale x 2
#set logscale y 2
set grid
set key reverse Left
plot \
algorithm1.".".data1.".tsv" using ($1):($2) title algorithm1 with linespoints, \
   algorithm2.".".data1.".tsv" using ($1):($2) title algorithm2 with linespoints
