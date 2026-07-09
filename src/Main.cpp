#include "include.hpp"

int main() {
    CSVProcessor processor;

    // inizializzo variabili per gestire l'intervallo di visualizzazione

    unsigned int min = 0;
    unsigned int pos = 0;
    unsigned int maj = 100;

    //Costruisco la GUI 
    State gs(800, 700, "Visualizzatore passo",&maj,&min,&pos);
    gs.window.setFramerateLimit(70);
    printf("Costruisco gli oggetti\n");

    try{
        
        processor.readCSVFile (DATA_PATH + "caviglia_dx.csv"); //utilizzo questo file per definire la dimensione dei dati
        const auto& coscia = processor.getData();
        gs.setIntervall(coscia.size());

        //provo ad aggiungere una collection
        //gs.collections.push_back(new Gamba({220,0,220},&pos,"coscia_filt.csv","caviglia_filt.csv"));
        
        std::vector<gamba_data> data;
        {
            gamba_data d;
            d.dataPos = &pos;
            d.cavigliaData = "caviglia_dx.csv";
            d.cosciaData = "coscia_dx.csv";
            gamba_data s;
            s.dataPos = &pos;
            s.cavigliaData = "caviglia_sx.csv";
            s.cosciaData = "coscia_sx.csv";
            data.push_back(d);
            data.push_back(s);
        }
        gs.collections.push_back(new Lower_Body(rb::Vector3{200,200,100},data));


        // aggiunta sistema in sovvrapposizione (filtrato)
        data.clear();
        {
            gamba_data d;
            d.dataPos = &pos;
            d.cavigliaData = "FilteredData/caviglia_filtD.csv";
            d.cosciaData = "FilteredData/coscia_filtD.csv";
            gamba_data s;
            s.dataPos = &pos;
            s.cavigliaData = "FilteredData/caviglia_filtS.csv";
            s.cosciaData = "FilteredData/coscia_filtS.csv";
            data.push_back(d);
            data.push_back(s);
        }
        gs.collections.push_back(new Lower_Body(rb::Vector3{200,200,100},data));

        // aggiunta sistema in sovvrapposizione (corretto)
        
        data.clear();
        {
            gamba_data d;
            d.dataPos = &pos;
            d.cavigliaData = "CorrectedData/caviglia_CorrD.csv";
            d.cosciaData = "CorrectedData/coscia_CorrD.csv";
            gamba_data s;
            s.dataPos = &pos;
            s.cavigliaData = "CorrectedData/caviglia_CorrS.csv";
            s.cosciaData = "CorrectedData/coscia_CorrS.csv";
            data.push_back(d);
            data.push_back(s);
        }
        gs.collections.push_back(new Lower_Body(rb::Vector3{200,200,100},data));


        //aggiungo il pavimento 
        gs.pieces.push_back(new Pavimento({200,200,550},_Float16(0.2) ));
        //gs.pieces[0]->body.setRot({0.01,-0.03,0});
        gs.pieces[0]->body.setCollisions(true);
        gs.pieces[0]->body.setFixed(true);
        
        printf("Ho costruito tutto!\n");
    }
    catch(char* e){
        printf("%s\n",e);
    }
    printf("Avvio l'interfaccia grafica\n");


    unsigned int curTime = 0;
    unsigned int freq = 50; //frequenza campionamento sensori
    const unsigned int T = 1000/freq; //i sensori hanno una freq di campionamento di 50hz

    //Avvio il loop della GUI
    gs.clock.start();
    gs.updateCollections();

    sf::Clock mainClock;
    while (gs.window.isOpen()) 
    {
        curTime += mainClock.restart().asMilliseconds() *(*gs.tMul) ;
        if (curTime > T){
            if (gs.play && pos+curTime/T < maj) pos += curTime / T; 
            curTime = 0;
        }

        // Show update
        gs.update();
        doGraphics(gs);
    }
    
    return 0;
}

