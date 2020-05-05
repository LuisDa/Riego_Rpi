#!/bin/bash

echo "Número de parámetros $#"
echo " "
echo "Interfaz $1"
echo "IP $2"
echo "Puerto $3"
echo "Mensaje $4"
echo "Continuidad $5"
echo "Ciclo $6"

if [ "$#" -lt 5 ]; then

	echo "Usage: $0 <Net_Interface> <IP_address> <Port_number> <Message_to_send> [<Continuous(0=false, other=true)>] [<delay(ms)>]"
else
	export LD_LIBRARY_PATH=.:$LD_LIBRARY_PATH

	./sendAndReceive $1 $2 $3 $4 $5 $6
fi	
