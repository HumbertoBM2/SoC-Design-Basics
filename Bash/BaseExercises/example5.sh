#!/bin/bash
# Script que declara una función que retorna un string en la variable val,
# la cual se imprime posteriormente

function greeting() {
  str="Hello, $name"
  echo $str
}

echo "Enter your name"
read name

val=$(greeting)
echo "Return value of the function is $val"
