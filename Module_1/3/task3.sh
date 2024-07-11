#!/bin/bash
file="task3.log"
if [ ! -e $file ]; then
    inc=1
else
    inc=$(wc -l "$file" | awk '{print $1}')
    ((inc++))
fi
time=$(date +%Y-%m-%d\ %H:%M:%S)
echo "$time I run $inc time" >> $file