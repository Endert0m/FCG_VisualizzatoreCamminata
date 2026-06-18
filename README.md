# FCG_VisualizzatoreCamminata


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

# Per compilare:

    cmake --build

# Per lanciare:

    ./build/bin/mainV5
