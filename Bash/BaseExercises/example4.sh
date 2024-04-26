#!/bin/bash
# Script que lee un input y evalua si este es igual a 15 o 45
# Si lo es, se imprime You won the game, en caso contrario se imprime 
# You lost the game
echo "Enter any number"
read n

if [[ ($n -eq 15 || $n -eq 45) ]]
then
  echo "You won the game"
else
  echo "You lost the game"
fi
