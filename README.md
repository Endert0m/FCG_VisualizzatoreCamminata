# FCG_VisualizzatoreCamminata

- # **Nella branch All_Releases ci sono tutte le release con istruzioni per la compilazione e la relazione** 


## Nella versione versione v0.1 è presente la base del progetto.

- La gerarchia dei file e delle classi

    - Le classi sono divise in base allo scopo sotto directory diverse 

- Definizione di pezzi (coscia, caviglia e sensori)

- Definizione di joint (rigido e a pivot)

- Semplice main di test

Per questione di debug tutti i pezzi rappresentati si possono trascinare e ruotare con i rispettivi tasto sinistro e destro del mouse.

Per spostare l'intera scena si tiene premuto il tasto centrale del mouse.

## Nella versione v0.2:
- Applicato refactoring di diverse classi
- Aggiustato calcolo dei pivot implementando le rotazioni con algebra affine e glm
- Aggiuta classe caviglia (per differenziarla dalla coscia) 

## Nella versione v0.3:
- Applicato refactoring delle classi pieces
- Aggiunta pezzo torso
- Nel testMain vengono agganciate caviglia e coscia al nuovo torso

## Nella versione v0.4
- Aggiunta vista frontale (con spazio si può camnbiare vista)
- Modifica calcolo pivot per gestire spazio 3D
- Aggiustati assi di riferimento (ora sono coerenti su tutte le classi)

## Nella versione v0.5
- Aggiunta ImGUI
- Aggiunta selettore sulla posizione dei dati
- Refactoring classe sensore e state per gestire posizione dati da gui

## Nella versione v0.6
- Aggiunta collezioni
  - Servono a semplificare la struttura del main e il disegno degli elementi della gamba 
- Modifica di sfml_util per gestire le collezioni
- Aggiunta modalità debug  

## Nella versione v0.7
- Aggiunta impostazione di trasparenza dei pezzi
- Aggiustato cambio direzione della gamba (sulla visualizzazione dei piani XZ e -XZ)
- Aggiunto controllo trasparenza delle collezioni
- Modificato lower_body per gestire la trasparenza della gamba più lontana
- Ridimensionato bacino per migiore visualizzazione

## Nella versione v0.8
- Aggiunta oscillazione bacino 
- Aggiustato calcolo posizione con clock dedicato

## Nella versione v0.9
- Modificata la funzione update di pezzi e collezioni per implementare controllo sul tempo
- Aggiunta finestra con slider per selezione moltiplicatore del tempo

## Nella versione v1.0
- Aggiunta controllo texture 
- Aggiunta pavimento 
- Refactoring generale
- Definizione main finale (non più di test)

## Nella versione v1.1
- Aggiunta controllo visibilità collezioni su GUI
- Refactoring collezioni

## Nella versione v1.2
    
# Per compilare:

    mkdir build //se non esiste già
    cd build
    cmake ..
    cmake --build . -j$(nproc)

# Per lanciare:
    cd bin
    ./mainV11
