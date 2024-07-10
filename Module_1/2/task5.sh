#!/bin/bash
main_folder="$1"
if [ -z "$main_folder" ]; then
    echo "Пожалуйста, введите путь."
    exit 1
fi
for i in {1..5}; do
    folder="${main_folder}/folder_${i}"
    mkdir -p "$folder"

    for j in {1..10}; do
        subfolder="${folder}/subfolder_${j}"
        mkdir -p "$subfolder"

        for k in {1..20}; do
            file="${subfolder}/file_${k}"
            touch "$file"
        done
    done
done