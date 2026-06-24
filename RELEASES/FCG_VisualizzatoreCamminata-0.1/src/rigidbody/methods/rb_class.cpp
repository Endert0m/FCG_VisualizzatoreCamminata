#include "../headers/rb.hpp"


using namespace rb ;

rigidbody::rigidbody(Vector3 coords, Vector3 centerOfMass, _Float16 mass)
{
    if (coords.size() != 3) throw "Coords must be 3";
    if (centerOfMass.size() != 3) throw "COM coords must be 3";

    this->coords = coords;
    this->centerOfMass = centerOfMass;
    this->mass = mass;

}

rigidbody::~rigidbody()
{
}

Vector3 rigidbody::getPos(){
    return Vector3 {coords};
}
Vector3_s rigidbody::getRot(){
    return Vector3_s {rot};
}

void rigidbody::setPos(Vector3 Npos){
    if (Npos.size() != 3) throw "Pos must be 3 in lenght!";

    int i = 0;
    for (float axis : Npos){
        coords[i] = axis;
        i++;
    }

}

void rigidbody::setAcc(const Vector3 Nacc){
    if (Nacc.size() != 3) throw "Vel vector must be 3 in lenght!";
    
    int i = 0;
    for (float axis : Nacc){
        acc[i] = axis;
        i++;
    }

}

void rigidbody::setRot(const Vector3_s Nrot){
    if (Nrot.size() != 3) throw "Vel vector must be 3 in lenght!";
    
    int i = 0;
    for (float axis : Nrot){
        rot[i] = axis;
        i++;
    }

}

void rigidbody::calcVel(const float Dtime){
    Vector3 tmpVel;

    for (float a : acc){
        //if (a>0.8 || a<-0.8)
        tmpVel.push_back( a*Dtime );
    }

    int i = 0;
    for (float nv : tmpVel){
        vel[i++] += nv;
    }
}

void rigidbody::calcPos(const float Dtime){
    Vector3 tmpPos;
    
    for (float v : vel){
        tmpPos.push_back( v*Dtime );
    }

    int i = 0;
    for (float np : tmpPos){
        coords[i++] += np *100;//(np* cos(float(rot[i]))) *100;
    }
}

void rigidbody::step(const sf::Clock time){
    int64_t Dtime = time.getElapsedTime().asMicroseconds();
    if (prevT == 0) prevT = Dtime;


    float dt = (float(Dtime) / 1000000.0) - (float(prevT) / 1000000.0);
    prevT = Dtime;

    calcPos(dt);
    calcVel(dt);
}
    

