Această implementare modelează un trenulet special format dintr-o locomotivă și un număr infinit de vagoane. Trenul este reprezentat utilizând o listă dublu înglănțuită circulară cu santinelă (locomotiva). 
Mecanicul se poate deplasa pe vagoane și poate modifica inscripțiile acestora.

## Funcționalități:

### Initializare tren: Creează un tren cu locomotiva, primul vagon (înitializat cu #) și mecanicul poziționat pe primul vagon.

  ### Initializare coadă de comenzi: Creează o coadă goală pentru stocarea comenzilor, folosind o listă dublu înglănțuită.

  
  

 ### Operatii de actualizare (UPDATE)

  MOVE_LEFT: Mecanicul se deplasează la stânga. Dacă este pe primul vagon, este mutat pe ultimul.

  MOVE_RIGHT: Mecanicul se deplasează la dreapta. Dacă este pe ultimul vagon, se alocă memorie pentru un nou vagon.

  WRITE ****<C>: Inscripționează vagonul curent cu caracterul <C>.

  CLEAR_CELL: Elimină vagonul curent și mută mecanicul pe vagonul anterior (sau ultimul, dacă a fost primul vagon).

  CLEAR_ALL: Eliberează memoria tuturor vagoanelor, readucând trenul la starea inițială.

  INSERT_LEFT ****<C>: Inserează un vagon la stânga vagonului curent (nu este permis la primul vagon).

  INSERT_RIGHT ****<C>: Inserează un vagon la dreapta vagonului curent.

  
  

### Operatii de interogare (QUERY)

  SHOW_CURRENT: Afișează caracterul din vagonul curent.

  SHOW: Afișează trenul, marcând poziția mecanicului cu |.

  SWITCH: Inversează ordinea comenzilor din coadă.

  

### EXECUTE: Execută prima comandă din coadă.


## Cum se Rulează:

Compilare:

    make build

Rulare checker:

    ./checker.sh
