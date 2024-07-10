#!/bin/bash
time="$1"
sound="$2"
if ! date -d "$time" >/dev/null 2>&1; then
    echo "Неправильный формат времени (HH:MM)."
    exit 1
fi
if [ ! -f "$sound" ]; then
    echo "Файл '$sound' не найден."
    exit 1
fi
echo "mplayer \"$sound\" &" | at "$time"