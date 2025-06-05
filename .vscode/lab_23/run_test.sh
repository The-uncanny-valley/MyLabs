#!/bin/bash

# Компиляция
g++ main.cpp Container.cpp -o set_app
if [ $? -ne 0 ]; then
  echo "Ошибка компиляции"
  exit 1
fi

# Запуск с входным файлом
./set_app < test_input.txt > output.txt

# Показ результата
echo "=== ВЫВОД ПРОГРАММЫ ==="
cat output.txt
