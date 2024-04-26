#!/bin/bash
# Script para imprimir un texto que indica el numero de iteración actual durante un ciclo do while
n=1
while [ $n -le 5 ]
do 
  echo "Running $n time"
  ((n++))
done
