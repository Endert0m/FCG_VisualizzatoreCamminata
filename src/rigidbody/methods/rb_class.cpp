#include "../headers/rb.hpp"


using namespace rb ;

rigidbody::rigidbody(Vector3 coords, Vector3 centerOfMass, _Float16 mass, float radius)
{
    if (coords.size() != 3) throw "Coords must be 3";
    if (centerOfMass.size() != 3) throw "COM coords must be 3";

    this->coords = coords;
    this->centerOfMass = centerOfMass;
    this->mass = mass;
    this->R = radius;
    this->acc = {0,0,9.81};
}

rigidbody::~rigidbody()
{
}

Vector3 rigidbody::getPos(){
    return Vector3 {coords};
}
Vector3 rigidbody::getRot(){
    return Vector3 {rot};
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
    if (Nacc.size() != 3) throw "Acc vector must be 3 in lenght!";
    
    int i = 0;
    for (float axis : Nacc){
        acc[i] = axis;
        i++;
    }

}

void rigidbody::setRot(const Vector3 Nrot){
    if (Nrot.size() != 3) throw "Vel vector must be 3 in lenght!";
    
    int i = 0;
    for (float axis : Nrot){
        rot[i] = axis;
        i++;
    }

}

void rigidbody::calcVel(const float Dtime){
    if (!fixed){
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
    
}

void rigidbody::calcPos(const float Dtime){
    if (!fixed){
        Vector3 tmpPos;
    
        for (float v : vel){
            tmpPos.push_back( v*Dtime );
        }

        int i = 0;
        for (float np : tmpPos){
            coords[i++] += np *100;//(np* cos(float(rot[i]))) *100;
        }
    }
    
}

void rigidbody::step(const sf::Clock time, float multiplier){
    if (!fixed){
        int64_t Dtime = time.getElapsedTime().asMicroseconds();
        if (prevT == 0) prevT = Dtime;


        float dt = ((float(Dtime) / 1000000.0) - (float(prevT) / 1000000.0)) * multiplier;
        prevT = Dtime;

        calcRot(dt);
        calcPos(dt);
        calcVel(dt);
    }
   
}
    
void rigidbody::setTanAcc(const Vector3 Dacc){
    if (Dacc.size() != 3) throw "Vel vector must be 3 in lenght!";

    int i = 0;
    for (float a : Dacc ){
        tanAcc[i] = a;
        i++;
    }

}


void rigidbody::calcRot(const float Dtime){
    // Ds = wt +1/2*at^2 -> l'accelerazione angolare la trovo ac = v^2/R

    if (!fixed){
        Vector3 tmpVel;
        for (float a : tanAcc){
            tmpVel.push_back( a*Dtime );
        }
        int i = 0;
        for (float nv : tmpVel){
            tanVel[i++] += nv;
        }

        Vector3 tmpTanAcc;
        for (int i = 0; i<3; i++){
            tmpTanAcc.push_back( pow(tanVel[i],2) / R );
        }

        i=0;
        for (auto axes : rot){
            rot[i] = axes + (0.5 * tmpTanAcc[i] * pow(Dtime,2));
            i++;
        }
    }


}

rb::Vector3 rigidbody::getAcc(){
    return Vector3(acc);
}

void rigidbody::setVel(const Vector3 Nacc){
    if (Nacc.size() != 3) throw "Vel vector must be 3 in lenght!";

    vel = Nacc;
}