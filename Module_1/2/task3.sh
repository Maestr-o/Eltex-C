#!/bin/bash
if [ -z "$1" ]; then
  echo "Пожалуйста, укажите пользователя."
  exit 1
fi
cat /var/log/auth.log | grep "$1" | grep 'session closed\|session opened' | awk -v user="$1" '{ print $2,$1,$3,user }' > auth.log