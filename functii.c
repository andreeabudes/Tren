#include "tren.h"

TTren* Init_tren () {
    TTren* tren = (TTren*)malloc(sizeof(TTren));
    if (!tren) {
        return NULL;
    }
    TVagon* locomotiva = (TVagon*)malloc(sizeof(TVagon));
    if (!locomotiva) {
        free(tren);
        return NULL;
    }
    locomotiva->info = '\0';
    locomotiva->ant = NULL;
    locomotiva->urm = NULL;
    TVagon *prim_vagon = (TVagon*)malloc(sizeof(TVagon));
    if(!prim_vagon) {
        free(tren);
        free(locomotiva);
        return NULL;
    }
    prim_vagon->info = '#';
    prim_vagon->ant = locomotiva;
    prim_vagon->urm = locomotiva;
    locomotiva->ant = prim_vagon;
    locomotiva->urm = prim_vagon;
    tren->locomotiva = locomotiva;
    tren->mecanic = prim_vagon;
    
    return tren;
}

TCoada* InitQ () {
    TCoada* coada = (TCoada*)malloc(sizeof(TCoada));
    if (coada == NULL) {
        return NULL;
    }
    coada->inc = NULL;
    coada->sf = NULL;
    return coada;
}

int IntrQ (TCoada *coada, char *command) {
    TCelula* new_cell= (TCelula*)malloc(sizeof(TCelula));
    if (!new_cell) {
        return 0;
    }
    new_cell->info = (char*)malloc((strlen(command) + 1) * sizeof(char));
     if (!new_cell->info) {
        free(new_cell); 
        return 0;
    }
    strcpy(new_cell->info, command);
    new_cell->urm = NULL;
    if (coada->inc == NULL) {
        coada->inc = new_cell;
        coada->sf = new_cell;
    } else {
        new_cell->ant = coada->sf;
        coada->sf->urm = new_cell;
        coada->sf = new_cell;
    }
    return 1;
}

int ExtrQ(TCoada *coada, char **command)  { 
    if (coada->inc == NULL) {
        return 0;
    }
    TCelula* extr = coada->inc;
    strcpy(*command, coada->inc->info);
    
    if (coada->inc == NULL) {
        coada->sf = NULL;
    }
    coada->inc = coada->inc->urm;
    
    free(extr);
    return 1;   
                       
}

void MOVE_LEFT (TTren* tren, TVagon* prim_vagon) {
    if (tren->mecanic == prim_vagon) {
        tren->mecanic = tren->locomotiva->ant;
    } else {
        tren->mecanic = tren->mecanic->ant;
    }
}

void MOVE_RIGHT (TTren* tren) {
    if (tren->mecanic->urm == tren->locomotiva) {                         //verific daca mecanicul e in ultimul vagon
        TVagon* vagon_nou = (TVagon*)malloc(sizeof(TVagon));
        if (!vagon_nou) {
            return; 
       }
        vagon_nou->info = '#';
        vagon_nou->ant = tren->mecanic;                                 //leg noul vagon de cel din stanga lui
        vagon_nou->urm = tren->locomotiva;   
        tren->locomotiva->ant = vagon_nou;                              //stabilesc ca vagonul nou este ultimul
        tren->mecanic->urm = vagon_nou;
        tren->mecanic = vagon_nou;                                       //mut mecanicul in noul vagon
    } else {
        tren->mecanic = tren->mecanic->urm;
    }
}

void WRITE(TTren* tren, char inscript) {
    tren->mecanic->info = inscript;
}

void CLEAR_CELL(TTren* tren, TVagon* prim_vagon) {
    TVagon* vagon_eliminat = tren->mecanic;
    if (vagon_eliminat->ant != NULL) {
        vagon_eliminat->ant->urm = vagon_eliminat->urm;
    }
    if (vagon_eliminat->urm != NULL) {
        vagon_eliminat->urm->ant = vagon_eliminat->ant;
    }
    tren->mecanic = tren->mecanic->ant;
    if (vagon_eliminat == prim_vagon) {
        tren->mecanic = tren->locomotiva->ant;
        free(prim_vagon);
    }
    if (vagon_eliminat->urm == NULL && vagon_eliminat->ant == tren->locomotiva) {
        vagon_eliminat->info = '#';
    }
    free(vagon_eliminat);
}

void CLEAR_ALL(TTren* tren) {
    TVagon* vagon_curent = tren->locomotiva->urm;
    if (!vagon_curent) {
        return;
    }
    while (vagon_curent != tren->locomotiva) {
        TVagon* vagon_urmator = vagon_curent->urm; 
        free(vagon_curent);
        vagon_curent = vagon_urmator;
    }
    tren->mecanic = tren->locomotiva->urm;
    tren->mecanic->info = '#';
    tren->locomotiva->ant = tren->mecanic;
}

void INSERT_LEFT (TTren* tren, char inscript, FILE *file) {
    if (tren->mecanic == tren->locomotiva->urm) {
        fprintf(file, "ERROR\n");
        return;
    }
    TVagon* vagon_nou = (TVagon*)malloc(sizeof(TVagon));
    if (!vagon_nou) {
        return;
    }
    
    vagon_nou->info = inscript;
    vagon_nou->ant = tren->mecanic->ant;  
    tren->mecanic->ant->urm = vagon_nou;                                    
    tren->mecanic->ant = vagon_nou;
    vagon_nou->urm = tren->mecanic; 
    tren->mecanic = vagon_nou;
}

void INSERT_RIGHT (TTren* tren, char inscript) {                       //la ambele functii de inserare m-am folosit de ce scria in curs
    TVagon* vagon_nou = (TVagon*)malloc(sizeof(TVagon));
    if (!vagon_nou) {
        return;
    }
    vagon_nou->info = inscript;
    vagon_nou->urm = tren->mecanic->urm;
    tren->mecanic->urm->ant = vagon_nou;
    vagon_nou->ant = tren->mecanic;
    tren->mecanic->urm = vagon_nou;
    tren->mecanic = vagon_nou;
}
void SHOW_CURRENT(TTren *tren, FILE *file) {
    fprintf(file,"%c\n", tren->mecanic->info);
}

void SHOW(TTren *tren, FILE *file) {
    TVagon *curent = tren->locomotiva->urm;
    if(!curent) {
        return;
    }
    while (curent != tren->locomotiva) {
        if (curent == tren->mecanic) {
            fprintf(file, "|%c|", curent->info);
        } else {
            fprintf(file, "%c", curent->info);
        }
        curent = curent->urm;
    }
    fprintf(file, "\n");
}

void SWITCH(TCoada *coada) {
    TCelula *p = coada->inc;
    TCelula *q = coada->sf;
    while (p != q && p->urm != q) {
        char *aux = (char*)malloc(sizeof(char) * 100);
        strcpy(aux, p->info);
        strcpy(p->info, q->info);
        strcpy(q->info, aux);
        p = p->urm;
        q = q->ant;
    }
}

void EXECUTE(TTren *tren, TCoada *coada, FILE *file) {
    char *command = (char*)malloc(sizeof(char) * 100);
    if (!command) {
        return;
    }
    TVagon *prim_vagon = (TVagon*)malloc(sizeof(TVagon));
    if(!prim_vagon) {
        free(command);
        return;
    }
    ExtrQ(coada, &command);
        if (strncmp(command, "MOVE_LEFT", 9) == 0) {
            MOVE_LEFT(tren, prim_vagon);
        } else if (strncmp(command, "MOVE_RIGHT", 10) == 0) {
            MOVE_RIGHT(tren);
        } else if (strncmp(command, "WRITE", 5) == 0) {
            char inscript = command[6];
            WRITE(tren, inscript);
        } else if (strncmp(command, "CLEAR_CELL", 10) == 0) {
            CLEAR_CELL(tren, prim_vagon);
        } else if (strncmp(command, "CLEAR_ALL", 9) == 0) {
            CLEAR_ALL(tren);
        } else if (strncmp(command, "INSERT_LEFT", 11) == 0) {
            char inscript = command[12];
            INSERT_LEFT(tren, inscript, file);
        } else if (strncmp(command, "INSERT_RIGHT", 12) == 0) {
            char inscript = command[13];
            INSERT_RIGHT(tren, inscript);
        }
    free (command);
    free(prim_vagon);
    }

void free_tren(TTren* tren) {
    if (tren == NULL) return;
    TVagon* curent = tren->locomotiva;
    while (curent != NULL) {
        TVagon* aux = curent;
        curent = curent->urm;
        free(aux);
    }
    free(tren);
}

void free_coada(TCoada* coada) {
    if (coada == NULL) return;
    TCelula* curent = coada->inc;
    while (curent != NULL) {
        TCelula* aux = curent;
        curent = curent->urm;
        free(aux);
    }
    free(coada);
}