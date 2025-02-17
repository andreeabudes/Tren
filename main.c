#include "tren.h"

int main () {
    TTren* t;
    t = Init_tren();
    
    if(!t) {
        return 1;
    }
   
    FILE *fisier;
    FILE *fisier2;
    TCoada *coadaOperatii = InitQ();

    fisier = fopen("tema1.in", "r");
    fisier2 = fopen("tema1.out", "w");
    if (fisier == NULL) {
        perror("Eroare");
        return 1;
    }
    if (fisier2 == NULL) {
        perror("Eroare");
        return 1;
    }

    int numar_comenzi;
    char *command = (char*)malloc(sizeof(char) * 100);
    if(!command) {
       return 0;
    }
    if (fscanf(fisier, "%d", &numar_comenzi) != 1) {
        return 0;
    }
    fgets(command, 100, fisier);

    TCoada *coada = InitQ();
    if (!coada) {
        perror("Eroare la inițializarea cozi de comenzi");
        return 0;
    }

    int i = 0;
    for ( i = 0; i < numar_comenzi; i++) {
        if (fgets(command, 100, fisier) == NULL) {
            break; 
        }
        command[strlen(command) - 1] = '\0';
        if (strncmp(command, "MOVE_LEFT", 9) == 0) {
            IntrQ(coada, command);
        } else if (strncmp(command, "MOVE_RIGHT", 10) == 0) {
            IntrQ(coada, command);
        } else if (strncmp(command, "WRITE", 5) == 0) {
            IntrQ(coada, command);
        } else if (strncmp(command, "CLEAR_CELL", 10) == 0) {
            IntrQ(coada, command);
        } else if (strncmp(command, "CLEAR_ALL", 9) == 0) {
           IntrQ(coada, command);
        } else if (strncmp(command, "INSERT_LEFT", 11) == 0) {
            IntrQ(coada, command);
        } else if (strncmp(command, "INSERT_RIGHT", 12) == 0) {
            IntrQ(coada, command);
        } else if (strncmp(command, "SHOW_CURRENT", 12) == 0) {
            SHOW_CURRENT(t, fisier2);
        } else if (strncmp(command, "SHOW", 4) == 0) {
            SHOW(t, fisier2);
        } else if (strncmp(command, "SWITCH", 6) == 0) {
            SWITCH(coada);
        } else if (strncmp(command, "EXECUTE", 7) == 0) {
            EXECUTE(t, coada, fisier2);
        }
    }
   
    fclose(fisier);
    free(command);

    return 0;
}