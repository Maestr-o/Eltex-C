#!/bin/bash
read -p "Введите имя процесса: " process_name
read -p "Введите периодичность проверки (в секундах): " interval

while true; do
    if ! pgrep -x "$process_name" > /dev/null; then
        echo "Процесс $process_name не найден, запуск..."
        $process_name
    fi
    sleep "$interval"
done