#!/bin/bash
# Script para alertar por correo cuando haya poco espacio en el disco

# Umbral mínimo de espacio libre (en MB)
threshold=1000

# Dirección de correo electrónico para enviar alertas
email="tu@email.com"

# Verificar espacio en disco
free_space=$(df -h --output=avail / | sed 1d)
if [ "$free_space" -lt "$threshold" ]; then
    echo "¡Alerta! Espacio en disco bajo: $free_space MB" | mail -s "Alerta de Espacio en Disco" "$email"
fi

