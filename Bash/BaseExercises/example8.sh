#!/bin/bash
# Script para revisar los recrusos utilizados por la computadora

# Thresholds para los recursos del sistema
cpu_threshold=80
memory_threshold=80
disk_threshold=80

# Funcion para revisar el uso del CPU
check_cpu() {
    local cpu_usage=$(top -bn1 | grep "Cpu(s)" | sed "s/.*, *\([0-9.]*\)%* id.*/\1/" | awk '{print 100 - $1}')
    if (( $(echo "$cpu_usage > $cpu_threshold" | bc -l) )); then
        echo "High CPU usage: $cpu_usage%"
    fi
}

# Funcion para revisar el uso de la memoria
check_memory() {
    local memory_usage=$(free | grep Mem | awk '{print $3/$2 * 100.0}')
    if (( $(echo "$memory_usage > $memory_threshold" | bc -l) )); then
        echo "High memory usage: $memory_usage%"
    fi
}

# Funcion para revisar el uso del disco
check_disk() {
    local disk_usage=$(df -h --output=pcent / | sed 1d | cut -d'%' -f1)
    if (( $(echo "$disk_usage > $disk_threshold" | bc -l) )); then
        echo "High disk usage: $disk_usage%"
    fi
}

# Main 
echo "System monitoring started..."
check_cpu
check_memory
check_disk
echo "System monitoring completed!"

