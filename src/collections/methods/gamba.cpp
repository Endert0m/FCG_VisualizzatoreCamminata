#include "../headers/gamba.hpp"

Gamba::Gamba(rb::Vector3 pos, unsigned int* dataPos, std::string cosciaData, std::string cavigliaData){
    CSVProcessor processor;
    try {
        pezzi.push_back(new Coscia(pos,2));
        pezzi.push_back(new Caviglia(rb::Vector3{pos[0],pos[1],pos[2]+200},2));
        
        processor.readCSVFile (DATA_PATH + cosciaData);
        const auto& coscia = processor.getData();
        sensori.push_back(new Sensore(pos,_Float16( 0.2 ),dataPos,coscia));
        
        processor.readCSVFile(DATA_PATH + cavigliaData);
        const auto& caviglia = processor.getData();
        sensori.push_back(new Sensore (rb::Vector3{pos[0],pos[1],pos[2]+200},_Float16( 0.2 ),dataPos,caviglia));

        // modifico la rotazione relativa della gamba
        sensori[0]->body.setRot({_Float16 (1.5708),_Float16 (1.5708),0});
        sensori[1]->body.setRot({_Float16 (1.5708),_Float16 (1.5708),0});

        joints.push_back(new RigidJoint(sensori[0], {pezzi[0]}));
        joints.push_back(new PivotJoint(sensori[0], {sensori[1]}, rb::Vector3{0,0,100}));
        joints.push_back(new RigidJoint(sensori[1], {pezzi[1]}));

    }
    catch(char* e){
        throw "Gamba ERROR : "+ std::string(e) +" \n" ;
    }

}

collection Gamba::create(ReferencePlane plane){
    collection coll;
    for(auto e : pezzi){
        e->setTransparency(transparency);
        coll.pieces.push_back(e);
    }
    for(auto e : sensori){
        e->setTransparency(transparency);
        coll.pieces.push_back(e);
    }

    for(auto j : joints){
        coll.joints.push_back(j);
    }

    return coll;
}

PieceInterface* Gamba::getJointPiece(){
    return sensori[0];
}

void Gamba::setDirection(Direction dir){
    for (auto i : pezzi){
        i->setDirection(dir);
    }
    for (auto i : sensori){
        i->setDirection(dir);
    }
}

float Gamba::getZ_Acc(){
    
    float totZ_Acc = 0;
    totZ_Acc = sensori[0]->getZ_Acc() + sensori[1]->getZ_Acc();

    return totZ_Acc;
}