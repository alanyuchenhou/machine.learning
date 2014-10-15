reset
algorithm1="perceptron"
algorithm2="passiveAgressive"
data1="training"
data2="validation"
set output "variableTraining.png"
set xlabel "example count"
set ylabel "accuracy"
set term png size 1024,1024
#set logscale x 2
#set logscale y 2
set grid
set key reverse Left bottom

plot \
algorithm1.".".data1.".variableTraning.tsv" using ($1):($3) title algorithm1.".".data1 with linespoints, \
   algorithm2.".".data1.".variableTraning.tsv" using ($1):($3) title algorithm2.".".data1 with linespoints
