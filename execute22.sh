#!/bin/bash
file=$1
times=(10) #(60 120 300 600)#final experiment
path="instances/"

for t in "${times[@]}"
do
    j=0

    input="in/instances_$file.txt"
    inst=()
	while IFS= read -r line
	do
	    #echo "$line"
	    inst+=("${line}")
	done < "$input"
    
    timeLimit=$t
    output="salida"_"$timeLimit"
    for k in "${inst[@]}"
    do
	tiempo=$timeLimit
	# echo "$tiempo $j"
	let j+=1
	for seed in {0..9}
	do
	#echo $k
	instance="$k"

	# run
	echo "./pc_gmstp $instance.GTP $output.txt $tiempo $seed"
	./pc_gmstp $instance.GTP $output.txt $tiempo $seed

	done
    done
done
