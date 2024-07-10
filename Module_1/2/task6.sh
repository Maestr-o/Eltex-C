#!/bin/bash

echo "Введите путь к основной директории:"
read main_folder

if [ -z "$main_folder" ]; then
    echo "Путь не указан."
    exit 1
fi

echo "Введите количество папок:"
read num_folders
num_folders=${num_folders:-5}

echo "Введите количество подпапок:"
read num_subfolders
num_subfolders=${num_subfolders:-10}

echo "Введите количество файлов:"
read num_files
num_files=${num_files:-20}

echo "Введите шаблон имени папок:"
read folder_prefix
folder_prefix=${folder_prefix:-"folder"}

echo "Введите шаблон имени подпапок:"
read subfolder_prefix
subfolder_prefix=${subfolder_prefix:-"subfolder"}

echo "Введите шаблон имени файлов:"
read file_prefix
file_prefix=${file_prefix:-"file"}

for ((i = 1; i <= num_folders; i++)); do
    folder="${main_folder}/${folder_prefix}_${i}"
    mkdir -p "$folder"

    for ((j = 1; j <= num_subfolders; j++)); do
        subfolder="${folder}/${subfolder_prefix}_${j}"
        mkdir -p "$subfolder"

        for ((k = 1; k <= num_files; k++)); do
            file="${subfolder}/${file_prefix}_${k}"
            touch "$file"
        done
    done
done