#include "game.h"
#define LINE_SIZE 5000

int main() {

    //shm
    int shmd, *value, semd;
    shmd = shmget(SHM_KEY, 1, 0);
    value = shmat(shmd, 0, 0);

    //sem
    semd = semget(SEM_KEY, 1, 0);
    struct sembuf sb;
    sb.sem_num = 0;
    sb.sem_op = -1;
    sb.sem_flg = SEM_UNDO;
    semop(semd, &sb, 1);

    //read file
    int file = open("game.txt", O_RDONLY);
    lseek(file,-1 * (*value), SEEK_END);
    char line[LINE_SIZE];
    read(file, line, *value);
    line[*value] = '\0';
    printf("Last line added: %s\n", line);

    //input
    char new[LINE_SIZE];
    printf("Next Line: ");
    fgets(new, LINE_SIZE, stdin);
    close(file);

    //write to file
    file = open("game.txt", O_WRONLY | O_APPEND);
    write(file, new, strlen(new));
    *value = strlen(new);

    shmdt(value);
    sb.sem_op = 1;
    semop(semd, &sb, 1);

    return 0;
}