Использование seminfo
=====================

Утилита позволяет по идентификатору семафора получить информацию:

	* PID процесса
	* время последней модификации
	* время последней операции
	* значение
	* количество процессов, ожидающих обнуления
	* количество процессов, ожидающих увеличения

Например, получим массив семафоров:

	# ipcs -s

	------ Semaphore Arrays --------
	key        semid      owner      perms      nsems     
	0x00000000 0          root       600        1         
	0x00000000 65537      root       600        1         
	0x7a0004f3 131074     zabbix     600        12        
	0x9b1a8534 2621443    oracle     660        125       
	0x9b1a8535 2654212    oracle     660        125       
	0x9b1a8536 2686981    oracle     660        125       
	0x9b1a8537 2719750    oracle     660        125       
	0x9b1a8538 2752519    oracle     660        125       
	0x9b1a8539 2785288    oracle     660        125       
	0x9b1a853a 2818057    oracle     660        125       
	0x9b1a853b 2850826    oracle     660        125       
	0x9b1a853c 2883595    oracle     660        125 

Получим информацию о семафоре 2686981:

	# ./seminfo 2686981
	Last modification time in Mon May 16 09:14:22 2016 by PID 7243
	Last operation time in           : Mon May 16 09:14:22 2016
	Semaphore value is               : 1
	Number of processes waiting zero : 0
	Number of processes waiting inc  : 0

Компиляция
==========

# gcc seminfo.c -o seminfo
# ./seminfo
Usage:
	seminfo <semaphore_id>
