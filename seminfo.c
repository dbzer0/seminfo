#include <sys/sem.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXSETSIZE 25

int get_sem_pid(int semid) {
    // Получение PID по ID семафора
    return semctl(semid, 0, GETPID);
}

int get_sem_value(int semid) {
    // Получение значения семафора по его ID
    return semctl(semid, 0, GETVAL);
}

int get_proc_num_zero(int semid) {
    // Получение количества процессов, ожидающих обнуления значения семафора
    return semctl(semid, 0, GETZCNT);
}

int get_proc_num_inc(int semid) {
    // Получение количества процессов, ожидающих увеличение значения семафора
    return semctl(semid, 0, GETNCNT);
}

char *get_sem_mod_time(int semid) {
    // Получение даты (в человеко читаемом формате) последей модификации семафора

    struct semid_ds semid_ds;
    struct tm tm_val;

    union semun {
        int val;
        struct semid_ds *buf;
        ushort array [MAXSETSIZE];
    } arg;

    char *p;

    arg.buf = &semid_ds;

    // заполнение структуры
    semctl(semid, 0, IPC_STAT, arg.buf);

    // преобразование времени в строку
    gmtime_r(&arg.buf->sem_otime, &tm_val);
    p = asctime(&tm_val);
    
    // удаляем последний символ \n
    p[strlen(p)-1] = 0;

    return p;
}

char *get_sem_op_time(int semid) {
    // Получение даты (в человеко читаемом формате) последней операции по семафору

    struct semid_ds semid_ds;
    struct tm tm_val;

    union semun {
        int val;
        struct semid_ds *buf;
        ushort array [MAXSETSIZE];
    } arg;

    char *p;

    arg.buf = &semid_ds;

    // заполнение структуры
    semctl(semid, 0, IPC_STAT, arg.buf);

    // преобразование времени в строку
    gmtime_r(&arg.buf->sem_ctime, &tm_val);
    p = asctime(&tm_val);
    
    // удаляем последний символ \n
    p[strlen(p)-1] = 0;

    return p;
}

int main(int argc, char **argv)
{
    int semid;
    int pid, value, countz, counti, stat;
    char *mod_time, *op_time;

    if (argc != 2) {
        printf("Usage:\n\tseminfo <semaphore_id>\n");

        return 1;
    }

    semid = atoi(argv[1]);

    pid = get_sem_pid(semid);
    if (pid == -1) {
        fprintf(stderr, "Semaphore not found. Wrong semaphore id or do you not have permission?\n");
        return 2;
    }

    value = get_sem_value(semid);
    countz = get_proc_num_zero(semid);
    counti = get_proc_num_inc(semid);
    mod_time = get_sem_mod_time(semid);
    op_time = get_sem_op_time(semid);

    printf("Last modification time in %s by PID %d\n", mod_time, pid);
    printf("Last operation time in           : %s\n", op_time);
    printf("Semaphore value is               : %d\n", value);
    printf("Number of processes waiting zero : %d\n", countz);
    printf("Number of processes waiting inc  : %d\n", counti);

    return 0;
}

