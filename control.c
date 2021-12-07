#include "game.h"

int main(int argc, char *argv[]) {

    if (argc > 1) {
        if (!strcmp(argv[1], "create")) {

            //shm
            int shmd = shmget(SHM_KEY, sizeof(int), IPC_CREAT | 0600);

            //sem
            int semd = semget(SEM_KEY, 1, IPC_CREAT | IPC_EXCL | 0644);
            union semun us;
            us.val = 1;
            int r = semctl(semd, 0, SETVAL, us);

            //file
            open("game.txt", O_CREAT | O_TRUNC, 0644);

        }
        else if (!strcmp(argv[1], "remove")) {
            
            //shm
            int shmd = shmget(SHM_KEY, 1, 0);
            shmctl(shmd, IPC_RMID, 0);

            //sem
            int semd = semget(SEM_KEY, 1, 0);
            semctl(semd, IPC_RMID, 0);

            //disp
            int file = open("game.txt", O_RDONLY);
            struct stat stats;
            stat("game.txt", &stats);
            char * text = malloc(stats.st_size + 1);
            read(file, text, stats.st_size);
            text[stats.st_size] = '\0';
            printf("Text:\n%s\n", text);
            free(text);
        }
    }
   
    return 0;
}