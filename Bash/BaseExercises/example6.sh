#!/bin/bash
# Script para contar el número total de caracteres de un archivo
filename=$1
totalchar=$(wc -c < "$filename")   
echo "Total number of characters are $totalchar"

# Para probar el script se corre el siguiente comando
# bash cmdline2.sh filename.txt
# Para corroborar que el calculo de caracteres es correcto se puede usar 
# wc -c filename.txt
