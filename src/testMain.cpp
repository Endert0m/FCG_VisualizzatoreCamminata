#include "include.hpp"

#define DATA_PATH std::string("./../../data/")

int main() {
    CSVProcessor processor;
    try {
        processor.readCSVFile("data.csv");

        // Access headers
        const auto& headers = processor.getHeaders();
        for (const auto& header : headers) {
            std::cout << header << "\t";
        }
        std::cout << std::endl;

        // Access data
        int n = 0;
        const auto& data = processor.getData();
        for (const auto& row : data) {
            if (n++ >40) break;
            for (float value : row) {
                std::cout << value << "\t";
            }
            std::cout << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    // inizializzo variabili per gestire l'intervallo di visualizzazione

    unsigned int min = 0;
    unsigned int pos = 0;
    unsigned int maj = 100;

    //Costruisco la GUI 
    State gs(800, 600, "Visualizzatore passo",&maj,&min,&pos);
    gs.window.setFramerateLimit(70);
    printf("Costruisco gli oggetti\n");

    try{
        processor.readCSVFile (DATA_PATH + "coscia_filt.csv");
        const auto& coscia = processor.getData();
        gs.setIntervall(coscia.size());


        gs.pieces.push_back(new Coscia (rb::Vector3{300,300,300},2));
        gs.pieces.push_back(new Sensore (rb::Vector3{300,300,300},_Float16( 0.2 ),&pos,coscia));
        gs.pieces.push_back(new Caviglia (rb::Vector3{300,300,500},1));

        gs.pieces[1]->body.setRot({0,0,0});


        processor.readCSVFile(DATA_PATH + "caviglia_filt.csv");
        const auto& caviglia = processor.getData();
        gs.pieces.push_back(new Sensore (rb::Vector3{300,300,500},_Float16( 0.2 ),&pos,caviglia));

        gs.pieces.push_back(new Torso(rb::Vector3{300,400,150},2));

        // modifico la rotazione relativa della gamba
        gs.pieces[1]->body.setRot({_Float16 (1.3),_Float16 (1.5),0});
        gs.pieces[3]->body.setRot({_Float16 (1.8),_Float16 (1.5),0});



        // aggiungo i joint
        gs.joints.push_back(new PivotJoint(gs.pieces[4], {gs.pieces[1]}, rb::Vector3{0,-100,50}));
        gs.joints.push_back(new RigidJoint(gs.pieces[1], {gs.pieces[0]}));
        gs.joints.push_back(new PivotJoint(gs.pieces[1], {gs.pieces[3]}, rb::Vector3{0,0,100}));
        gs.joints.push_back(new RigidJoint(gs.pieces[3], {gs.pieces[2]}));
        

        printf("Ho costruito tutto!\n");
    }
    catch(char* e){
        printf("%s\n",e);
    }
    printf("Avvio l'interfaccia grafica\n");


    unsigned int curTime = 0;
    unsigned int freq = 50;
    const unsigned int T = 1000/freq; //i sensori hanno una freq di campionamento di 50hz

    //Avvio il loop della GUI
    gs.clock.start();

    sf::Clock mainClock;
    while (gs.window.isOpen()) 
    {
        curTime += mainClock.restart().asMilliseconds();
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

