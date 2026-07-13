#include "../headers/sensore.hpp"


Sensore::Sensore(rb::Vector3 coords, _Float16 mass){
    rb::Vector3 com = {sensore_Dim.x/2,sensore_Dim.z/2, sensore_Dim.y/2};
    body = rb::rigidbody(coords, com, mass, sensore_Dim.z/2);
    color = sensore_Col;
    globalPos = {0,0,0};
    initialize_shapes(sensore_Dim);
}

Sensore::Sensore(rb::Vector3 coords, _Float16 mass, unsigned int* st, std::vector<std::vector<float>> data) : Sensore(coords, mass){
        dataPos = st;
        initCSV(data);
}


Sensore::~Sensore(){
    delete shapeXZ;
    delete shapeYZ;
}

void Sensore::initCSV(std::vector<std::vector<float>> data){
    //timestamp_ns, wx, wy, wz, ax, ay, az, gx, gy, gz
    if (data.size() < 10) throw "Sensor data empty";
    float stTime = int64_t( data[0][0] ) ;

    for (std::vector<float> row : data){
        timeData.push_back(int64_t( row[0] ) - stTime);

        std::vector<float> tmpR = {row[2],row[3],row[1]}; 
        std::vector<float> tmpA = {row[5],row[6],row[4]};
        std::vector<float> tmpG = {-row[8],-row[9],-row[7]};

        
        rotData.push_back(tmpR);
        accData.push_back(tmpA);
        gData.push_back(tmpG);
    }

    //trovo il modulo di g facendo la media del modulo nei primi 1000 campioni
    gModule = 0;
    int nCampioni = int(data.size())>1000 ? 1000 : 10;
    for(int i = 0; i<nCampioni ;i++) {
        gModule +=  sqrt(pow(gData[i][0],2)+pow(gData[i][1],2)+pow(gData[i][2],2));
    }
    gModule = gModule / 1000;

}


void Sensore::update(sf::Clock cl, float multiplier){
   
    //calcolo la posizione e velocità
    if (*dataPos >= gData.size()) *dataPos = gData.size()-1;

    calcRotWithG(*dataPos);


    body.setAcc(rb::Vector3{accData[*dataPos]});
    body.step(cl, multiplier);
   
}

sf::Shape* Sensore::draw(ReferencePlane plane){
    this->plane = plane;
    rb::Vector3 tmpRot = body.getRot();
    rb::Vector3 tmpPos = body.getPos();

    switch (plane)
    {
    case ReferencePlane::XZ : case ReferencePlane::XZN:
        {
       
        sf::Shape* shape = shapeXZ;
        shape->setRotation(sf::Angle(sf::radians(tmpRot[1])));
        shape->setPosition({tmpPos[0]+globalPos[0],tmpPos[2]+globalPos[2]});
        shape->setFillColor(color*sf::Color(255*multColor[0],255*multColor[1],255*multColor[2],transparency*255));
        shape->setScale({plane == ReferencePlane::XZ ? float(1.0) : float(-1.0),1});
        return shape;}
        break;
    
    case ReferencePlane::YZ:
        {
        sf::Shape* shape = shapeYZ;
        shape->setRotation(sf::Angle(sf::radians(tmpRot[0])));
        shape->setPosition({tmpPos[1]+globalPos[1],tmpPos[2]+globalPos[2]});
        shape->setFillColor(color*sf::Color(255*multColor[0],255*multColor[1],255*multColor[2],transparency*255));
        shape->setScale({direction == Direction::R ? float(1.0) : float(-1.0),1});
        return shape;}
        break;
    
    default:
        break;
    }

    return nullptr;
}


void Sensore::calcRotWithG(unsigned int index){ // calcolo rotazione con valori della gravità
    int dir = direction == Direction::R ? -1 : 1;
    int ydir = plane == ReferencePlane::XZ ? -1 : 1;
    std::vector<float> grav = gData[index];

    //x = mod * cosX -> mod = x/cosx -> cosx = x/mod

    float tmpSinX = -grav[0] / gModule;
    float tmpSinY = -grav[1] / gModule;
    float tmpSinZ = -grav[2] / gModule;

    float tmpAX = acos(dir*tmpSinX);
    float tmpAY = acos(ydir*dir*tmpSinY);
    float tmpAZ = acos(tmpSinZ);

    if (isnanf(tmpAX)) tmpAX = 0;
    if (isnanf(tmpAY)) tmpAY = 0;
    if (isnanf(tmpAZ)) tmpAZ = 0;

    body.setRot(rb::Vector3{tmpAY, tmpAX, tmpAZ });

}

float Sensore::getZ_Acc(){
    //int id = *dataPos;
    float tmpAcc = 0;
    
    rb::Vector3 acc = body.getAcc();
    rb::Vector3 rot = body.getRot();

    float modAcc = sqrt(pow(acc[0],2)+pow(acc[1],2)+pow(acc[2],2));

    float zAcc = cos(rot[2]) * modAcc;

    //dipende se il sensore conta la gravità nell'accelerazione sugli assi
    tmpAcc = zAcc - gModule;
    //tmpAcc = gModule - sqrt(pow(gData[id][0],2)+pow(gData[id][1],2)+pow(gData[id][2],2));
    return tmpAcc;
}


rb::Vector3 Sensore::calibrateRotation(unsigned int nFrames){
    rb::Vector3 tmpRot = {0,0,0};
    for (unsigned int i = 0; i<nFrames; i++){
        calcRotWithG(i);
        tmpRot = tmpRot + body.getRot();
    }
    tmpRot = tmpRot / nFrames;
    return tmpRot;
}
