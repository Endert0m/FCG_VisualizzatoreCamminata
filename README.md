# FCG_VisualizzatoreCamminata

## Per compilare:

    cd ./RELEASES
    mkdir build //se non esiste già
    cd build
    cmake ..
    cmake --build . -j$(nproc)

## Per lanciare:

    cd bin
    ./build/bin/mainV1 
    
    //Per eseguire le altre release cambiare mainV1 con mainV(1 - 11)


## Come utilizzare il software:
Sono stati inseriti dei dati di default per testare, non è necessario caricare altro per lanciare.

Per modificare i dati da visualizzare bisogna modificare il nome dei file all'interno del main **(non è supportato l'aggiornamento dei dati a runtime)**

Per muoversi nella scena:
 - Cliccare e tenere premuto tasto centrale del mouse.

Per le interazioni con la GUI:
 - Tutte le interazioni avvengono tramite cursore del mouse
   - per gli slider: click con tasto sinistro del mouse e trascinare 
   - per i checkbox basta click sulla spunta/rettangolino
   - per il tasto pause/resume (in basso a destra), click con tasto sinistro. Se il tasto è colorato di rosso vuol dire che la riproduzione è in pausa. 
