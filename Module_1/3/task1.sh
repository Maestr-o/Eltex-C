#!/bin/bash
file="$1"
if [ ! -e "$file" ]; then
    echo "Нет такого файла"
    exit 1
fi
letter_count=$(grep -o '[a-zA-Zа-яА-Я]' "$file" | wc -l)
echo "Кол-во букв: $letter_count"
word_count=$(grep -oE '[a-zA-Zа-яА-Я]+' "$file" | wc -l)
echo "Кол-во слов: $word_count"
first_queen=$(tr '\r\n' ' ' < "$file" | grep -o '[^.?!]*[Кк]оролев[а-яА-Я]*[^.?!]*[.?!]' | head -n 1 | sed 's/  / /g')
echo "Первое предложение с королевой: $first_queen"