# Как шелл только мини

## Установка и запуск

git clone https://github.com/evsyukoov/minishell.git

make

./minishell

##  Использование


##  Команды

Все комманды из PATH
Собственная реализация команд echo, cd, pwd, export, unset, env, exit

	### Поддержка множественных команд
	Пример: echo abc ; ls -l ; cd ..

	###  Поддержка конвейера
	Пример: ls -l | grep a | wc

	###  Поддержка редиректов
	Пример: echo "abc" > file1 ; echo "ert" > file2 >> file3

##  Сигналы

CTRL+C ; CTRL + \ ; CTRL + D


