#include "../headers/rigid_joint.hpp"

#define ZERO_INT 0.00001

void RigidJoint::rotate(unsigned int id){
    rb::Vector3_s fRot = father->body.getRot();
    rb::Vector3_s fRotOld = childs[id]->body.getRot() - rotOffset[id];

    rb::Vector3 cPos = childs[id]->body.getPos() + childs[id]->globalPos;

    childs[id]->body.setRot(fRot + rotOffset[id]);

    ////  sposto l'origine passivamente su tutti gli assi ////
    //se si muove il child devo muovere anche il padre -> devo trovare la differenza di posizione prima di ricalcolare l'offset
    /*
    if (cPos != oldCPos[id]);*/

    float r = sqrt(pow(offset[id][0],2)+pow(offset[id][2],2)); //calcolo modulo dell'offset (per ora solo sul piano xz)

    if (r>ZERO_INT){
        
        float sign = offset[id][2] >= 0 ? 1 : -1;
        

        sf::Angle alpha = sf::radians(fRot[2] - fRotOld[2]); // angolo aggiunto
        sf::Angle alpha1 = sf::radians(acos(sign * offset[id][0]/r)); // angolo rispetto alla posizione del child 
        sf::Angle beta = alpha + alpha1;

        sf::Vector2f tmpCoordsX = sf::Vector2f(r,beta);
        offset[id] = {sign * tmpCoordsX.x,offset[id][1],sign * tmpCoordsX.y};

        //ora devo muovere il child rispetto al nuovo offset 

        

        rb::Vector3 fPos = father->body.getPos() + father->globalPos;
        rb::Vector3 tmpChild =  fPos + offset[id];

        childs[id]->body.setPos(tmpChild - childs[id]->globalPos); 
    }
    else{
        childs[id]->body.setPos(father->body.getPos()+father->globalPos-childs[id]->globalPos);
    }


    // r cosA = x -> x/r = cosA

    /*
    Devo spostare l'offset per poter ricalcolare la posizione relativa dei child rispetto al father dopo aver eseguito la rotazione.
    La rotazione va eseguita nella posizione del mondo, ovvero sulle coordinate di body

    Le coordinate camera non vanno toccate, determinano solo lo spostamento rispetto alla telecamera
    */
}   

void RigidJoint::traslate(unsigned int id){
    

}

RigidJoint::RigidJoint(PieceInterface* father,std::vector<PieceInterface*> childs){
    this->childs = childs;
    this->father = father;
    rb::Vector3 fCoords = father->globalPos + father->body.getPos();
    rb::Vector3_s fRot = father->body.getRot();




    //mi calcolo l'offset per ogni child rispetto al padre
    for(PieceInterface* c : childs){
        rb::Vector3 tmpCoords;
        rb::Vector3_s tmpRot;

        rb::Vector3 cCoords = c->globalPos + c->body.getPos();

        tmpCoords = cCoords - fCoords;
        tmpRot = c->body.getRot() - fRot;

        
        offset.push_back(tmpCoords);
        rotOffset.push_back(tmpRot);
        
    }


}

RigidJoint::~RigidJoint(){

}

void RigidJoint::movechild(){
   
    for ( unsigned int i = 0; i < childs.size(); i++){
        traslate(i);
        rotate(i);
    }
}