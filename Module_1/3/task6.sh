#!/bin/bash
read -p "Введите имя процесса: " process_name
read -p "Введите начало промежутка времени (формат: Jul 14 00:00:01): " start_time
read -p "Введите конец промежутка времени (формат: Jul 14 23:59:59): " end_time

start_epoch=$(date -d "$start_time" --utc +%s)
end_epoch=$(date -d "$end_time" --utc +%s)

while IFS= read -r line; do
    log_time=$(echo "$line" | awk '{print $1, $2, $3}')
    log_epoch=$(date -d "$log_time" --utc +%s)
    if [ $log_epoch -ge $start_epoch ] && [ $log_epoch -le $end_epoch ]; then
        process=$(echo "$line" | awk '{print $5}')
        if echo "$process" | grep -q "$process_name"; then
            echo "$line"
        fi
    fi
done < /var/log/syslog