#!/bin/bash

validate_road_id () {
	re='^[1-9][0-9]*$'
	if ! [[ $1 =~ $re ]]
		then
			result=0
			return
	fi
	let result
	if [ $1 -ge 1 -a $1 -le 999 ]
		then result=1
	else
		result=0
	fi
}

if [ $# -lt 2 ]
	then
		echo "Wrong number of params, given: $#"
		exit 1
fi

declare -a ROADS_ID_ARR

param_number=0
PATH=$1

while [ $# -ne 0 ]; do
	if [ $param_number -ne 0 ]
		then
			validate_road_id $1
			if [ $result -ne 1 ]
				then
					echo "Param id invalid"
					exit 1
			fi
			ROADS_ID_ARR+=($1)
	fi
	let param_number++
	shift
done


#at this point all params are valid
while IFS=';' read -ra line || [ -n "$line" ]
	#TODO check if road id is given in param.
	do
		lineLen=${#line[@]}
		routeLen=0
		id=${line[0]}
		for j in ${ROADS_ID_ARR[@]}
		do
			if [ $id -eq $j ]
				then
					for ((i = 2; i < $lineLen; i += 3))
					do
						((  routeLen += ${line[$i]}  ))
					done
					echo "$id;$routeLen"
			fi
		done
done < "$PATH"
