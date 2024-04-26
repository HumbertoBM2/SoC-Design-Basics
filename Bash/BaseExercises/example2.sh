#!/bin/bash
# Script para correr un loop que se detendrá con un condicional
# El script incrementa el valor de n 10 veces pero se detiene cuando n es 6
n=1
while [ $n -le 10 ]
do
  if [ $n == 6 ]
  then
    echo "terminated"
    break
  fi
  echo "Position: $n"
  ((n++))
done
