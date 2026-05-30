#include "../headers/pivot_joint.hpp"

#define ZERO_INT 0.00001

void PivotJoint::rotate(unsigned int id){
    rb::Vector3_s fRot = father->body.getRot();
    rb::Vector3_s cRot = childs[id]->body.getRot();
    
    ////  sposto l'origine passivamente su tutti gli assi ////

    float r1 = sqrt(pow(pivot[0],2)+pow(pivot[2],2)); //calcolo modulo dell'offset (per ora solo sul piano xz)
    float r2 = sqrt(pow(offset[id][0],2)+pow(offset[id][2],2)); 
    if (r1>ZERO_INT){
        
        float sign = pivot[2] >= 0 ? 1 : -1;


        sf::Angle alpha = sf::radians(fRot[2] - oldRot[2]); // angolo aggiunto
        sf::Angle alpha1 = sf::radians(acos(sign * pivot[0]/r1)); // angolo rispetto alla posizione del pivot 
        sf::Angle alpha2 = alpha + alpha1;

        sf::Vector2f tmpCoordsX = sf::Vector2f(r1,alpha2);
        pivot = {sign * tmpCoordsX.x,pivot[1],sign * tmpCoordsX.y};

        //calcolo la posizione in base alla rotazione del child 
        sign = offset[id][2] >= 0 ? 1 : -1;

        sf::Angle beta = sf::radians(cRot[2] - oldCRot[id][2]);
        sf::Angle beta1 = sf::radians(acos(sign * offset[id][0]/r2));
        sf::Angle beta2 = beta + beta1;
        sf::Vector2f tmpCoordsC = sf::Vector2f(r2,beta2);
        offset[id] = {sign * tmpCoordsC.x,offset[id][1],sign * tmpCoordsC.y};


        //ora devo muovere il child rispetto al nuovo offset 
        rb::Vector3 pivotPos = father->body.getPos()+father->globalPos+pivot;
        rb::Vector3 cPos = childs[id]->body.getPos() + childs[id]->globalPos;

        rb::Vector3 tmpChild =  pivotPos + offset[id];

        childs[id]->body.setPos(tmpChild - childs[id]->globalPos); 
    }


    oldRot = fRot; //aggiorno la rotazione per il ciclo successivo
    oldCRot[id] = cRot;

    // r cosA = x -> x/r = cosA

    /*
    Devo spostare l'offset per poter ricalcolare la posizione relativa dei child rispetto al father dopo aver eseguito la rotazione.
    La rotazione va eseguita nella posizione del mondo, ovvero sulle coordinate di body

    Le coordinate camera non vanno toccate, determinano solo lo spostamento rispetto alla telecamera
    */
}   

void PivotJoint::traslate(unsigned int id){

}


PivotJoint::PivotJoint(PieceInterface* father,std::vector<PieceInterface*> childs, rb::Vector3 pivotPoint){
    this->childs = childs;
    this->father = father;
    rb::Vector3 fCoords = father->globalPos + father->body.getPos();
    rb::Vector3_s fRot = father->body.getRot();

    pivot = pivotPoint;
    rb::Vector3 pivotCenter = father->globalPos + father->body.getPos() + pivot;

    /*
    float sign = pivot[2] >= 0 ? 1 : -1;
    float r = sqrt(pow(pivot[0],2)+pow(pivot[2],2));
    rotOffset.push_back(  rb::Vector3_s{0,0,_Float16( acos(sign * pivot[0]/r) )} );
    */


    oldRot = father->body.getRot();

    //mi calcolo l'offset per ogni child rispetto al pivot
    for(PieceInterface* c : childs){
        rb::Vector3 tmpCoords;
        rb::Vector3 cCoords = c->globalPos + c->body.getPos();
        tmpCoords = cCoords - pivotCenter;

        /*
        float r = sqrt(pow(tmpCoords[0],2)+pow(tmpCoords[2],2));
        oldCRot.push_back( rb::Vector3_s{0,0,_Float16( acos(tmpCoords[0]/r) )} );
        */
        oldCRot.push_back(c->body.getRot());

        offset.push_back(tmpCoords);
        
    }


}

PivotJoint::~PivotJoint(){

}


void PivotJoint::movechild(){
   
    for ( unsigned int i = 0; i < childs.size(); i++){
        traslate(i);
        rotate(i);
    }
}