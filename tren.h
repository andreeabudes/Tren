#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct TVagon {
    char info; 
    struct TVagon* ant; 
    struct TVagon* urm; 
} TVagon;

typedef struct TTren {
    TVagon* locomotiva;         // Santinela 
    TVagon* mecanic;            
} TTren;

typedef struct celula {
    char* info;
    struct celula *urm;
    struct celula *ant;
} TCelula;

typedef struct TCoada {
    TCelula* inc;
    TCelula* sf;
} TCoada;

TTren* Init_tren ();
void MOVE_LEFT (TTren* tren, TVagon* prim_vagon);
void MOVE_RIGHT (TTren* tren);
void WRITE(TTren* tren, char inscript);
void CLEAR_CELL(TTren* tren, TVagon* prim_vagon);
void CLEAR_ALL(TTren* tren);
void INSERT_LEFT (TTren* tren, char inscript, FILE *file);
void INSERT_RIGHT (TTren* tren, char inscript);
void SHOW_CURRENT(TTren *tren, FILE *file);
void SHOW(TTren *tren, FILE *file);
void SWITCH(TCoada *coada);
TCoada* InitQ ();
int IntrQ (TCoada *coada, char *comanda);
int ExtrQ(TCoada *coada, char **comanda);
void CitireComenzi(FILE *fisier, TCoada *coada);
void EXECUTE(TTren *tren, TCoada *coada, FILE *file);
void free_tren(TTren* tren);
void free_coada(TCoada* coada);