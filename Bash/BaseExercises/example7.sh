#!/bin/bash
# Script que toma dos argumentos X y Y y los suma con una funcion
# Adicionalmente, se imprime el resultado 
for arg in "$@"
do
  index=$(echo $arg | cut -f1 -d=)
  val=$(echo $arg | cut -f2 -d=)
  case $index in
    X)x=$val;;
    Y)y=$val;;
    *)
  esac
done
((result=x+y))
echo "X+Y=$result"
