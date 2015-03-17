#!/bin/bash
#Run code for various values of E and plot in real time

COUNTER=0
NUM_EVALS=10
#Make an array of E/V0 values (spaced from -1 to 0)
while [ $COUNTER -lt NUM_EVALS ]; do
  EVALS[COUNTER]=-1+COUNTER*1/NUM_EVALS
  let COUNTER=COUNTER+1
done

foreach value ($EVALS)
  echo Starting run with value=$value
  ./shooting $value
  gnuplot -persist -e "plot 'output.dat'" loop.plt
  if ($status) echo WARNING: Problem during execution
end
