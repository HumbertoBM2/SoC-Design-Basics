#!/bin/bash
# Script para sumar, restar, multiplicar y dividir números usando funciones

# Función para sumar dos números
sumar() {
    local resultado=$(( $1 + $2 ))
    echo "La suma de $1 y $2 es: $resultado"
}

# Función para restar dos números
restar() {
    local resultado=$(( $1 - $2 ))
    echo "La resta de $1 y $2 es: $resultado"
}

# Función para multiplicar dos números
multiplicar() {
    local resultado=$(( $1 * $2 ))
    echo "La multiplicación de $1 y $2 es: $resultado"
}

# Función para dividir dos números
dividir() {
    local resultado=$(awk "BEGIN {printf \"%.2f\", $1 / $2}")
    echo "La división de $1 y $2 es: $resultado"
}

# Llamadas a las funciones con argumentos
sumar 10 5
restar 10 5
multiplicar 10 5
dividir 10 5

