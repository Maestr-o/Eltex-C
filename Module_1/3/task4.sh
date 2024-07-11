#!/bin/bash
echo "Создание архива с одним файлом:"
tar -cvf archive1.tar file1.txt
echo "Весь архив:"
tar -tf archive1.tar
echo "Добавление второго файла:"
tar -rvf archive1.tar file2.txt
echo "Весь архив:"
tar -tf archive1.tar
echo "Добавление третьего файла:"
tar -rvf archive1.tar file3.txt
echo "Весь архив:"
tar -tf archive1.tar
echo "Удаление 2-го файла"
tar --delete -f archive1.tar file2.txt
echo "Весь архив:"
tar -tf archive1.tar
mkdir folder
tar -C "folder" -xf archive1.tar