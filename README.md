# FCG_VisualizzatoreCamminata

- # **Nella branch All_Releases ci sono tutte le release con istruzioni per la compilazione e la relazione** 
# Rapida descrizione
Questo è un tool per la visualizzazione di dati derivanti da giroscopi.
Serve per visualizzare una camminata GAIT e permette di eseguire analisi visive su di esse.

Contiene:
- Visualizzazione ortogonale sui tre piani
- Controllo sul tempo di riproduzione e su posizione dei dati
- Controllo sovrapposizioni (permette di sovrapporre due camminate per confrontarle)
- Calcolo energia cinetica del sistema nell'intervallo selezionato ed esportazione dati


# Per compilare:

    mkdir build //se non esiste già
    cd build
    cmake ..
    cmake --build . -j$(nproc)

# Per lanciare:
    cd bin
    ./VisualCamm
