#!/bin/bash
echo "Введите путь к файлу или папке:"
read import_path
if [ ! -e "$import_path" ]; then
    echo "Указанный путь '$import_path' не существует."
    exit 1
fi
echo "Введите путь, куда будут сохранятся данные:"
read export_path
if [ ! -d "$export_path" ]; then
    echo "Указанный путь для сохранения '$export_path' не является директорией."
    exit 1
fi
echo "Введите время запуска резервного копирования:"
read time
if ! date -d "$time" >/dev/null 2>&1; then
    echo "Неправильный формат времени (HH:MM)."
    exit 1
fi
echo "tar -cf \"$export_path/backup.tar\" \"$import_path\"" | at "$time"