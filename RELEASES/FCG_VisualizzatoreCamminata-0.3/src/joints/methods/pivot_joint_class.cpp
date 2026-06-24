#include "../headers/pivot_joint.hpp"

#define ZERO_INT 0.00001

void PivotJoint::rotate(unsigned int id){
    rb::Vector3_s fRot = father->body.getRot();
    rb::Vector3 fPos = father->body.getPos();
    rb::Vector3_s cRot = childs[id]->body.getRot();
    
    ////  sposto l'origine passivamente su tutti gli assi ////

    float alpha = float (fRot[2] - oldRot[2]);
    float cosA = glm::cos(alpha);
    float sinA = glm::sin(alpha);

    float beta = float (cRot[2] - oldCRot[id][2]);
    float cosB = glm::cos(beta);
    float sinB = glm::sin(beta);

    glm::mat3 R1 = glm::mat3(
        /*cos*/ cosA, /*sin*/ sinA, 0,
        /*-sin*/ -sinA , /*cos*/  cosA, 0,
        0,      0,           1
    );

    glm::mat3 R2 = glm::mat3(
        /*cos*/ cosB, /*sin*/ sinB, 0,
        /*-sin*/ -sinB , /*cos*/  cosB, 0,
        0,      0,           1
    );

    glm::vec3 pivotNXZ = R1 * glm::vec3(pivot[0],pivot[2],1);
    pivot = rb::Vector3{pivotNXZ[0],pivot[1],pivotNXZ[1]};
    glm::vec3 offsetNXZ = R2 * glm::vec3(offset[id][0],offset[id][2],1);
    offset[id] = rb::Vector3{offsetNXZ[0],offset[id][1],offsetNXZ[1]};

    
    childs[id]->body.setPos(rb::Vector3{fPos[0]+offset[id][0]+pivot[0],fPos[1]+offset[id][1]+pivot[1],fPos[2]+offset[id][2]+pivot[2]});


    oldRot = fRot; //aggiorno la rotazione per il ciclo successivo
    oldCRot[id] = cRot;

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