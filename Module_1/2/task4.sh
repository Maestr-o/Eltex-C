#!/bin/bash
if [ -z "$1" ]; then
  echo "Пожалуйста, введите строку."
  exit 1
fi
sed "y/абвгдеёжзийклмнопрстуфхцчшщъыьэюяАБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ/abvgdeezziiklmnoprstufhccssyyyeuaABVGDEEZZIIKLMNOPRSTUFHCCSSYYYEUA/" "$1"