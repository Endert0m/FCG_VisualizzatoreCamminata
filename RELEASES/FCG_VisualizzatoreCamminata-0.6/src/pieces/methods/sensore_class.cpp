#include "../headers/sensore.hpp"


Sensore::Sensore(rb::Vector3 coords, _Float16 mass){
    rb::Vector3 com = {sensore_Dim.x/2,sensore_Dim.z/2, sensore_Dim.y/2};
    body = rb::rigidbody(coords, com, mass);
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
    if (data.size() < 1) throw "Sensor data empty";
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
}


void Sensore::update(sf::Clock cl){
   
    //calcolo la posizione e velocità
    if (*dataPos >= gData.size()) *dataPos = gData.size()-1;

    calcRotWithG(*dataPos);


    body.setAcc(rb::Vector3{accData[*dataPos]});
    body.step(cl);
   
}

sf::Shape* Sensore::draw(ReferencePlane plane){
    
    rb::Vector3 tmpRot = body.getRot();
    rb::Vector3 tmpPos = body.getPos();

    switch (plane)
    {
    case ReferencePlane::XZ:
        {
        sf::Shape* shape = shapeXZ;
        shape->setRotation(sf::Angle(sf::radians(tmpRot[1])));
        shape->setPosition({tmpPos[0]+globalPos[0],tmpPos[2]+globalPos[2]});
        return shape;}
        break;
    
    case ReferencePlane::YZ:
        {
        sf::Shape* shape = shapeYZ;
        shape->setRotation(sf::Angle(sf::radians(tmpRot[0])));
        shape->setPosition({tmpPos[1]+globalPos[1],tmpPos[2]+globalPos[2]});
        return shape;}
        break;
    
    default:
        break;
    }

    return nullptr;
}


void Sensore::calcRotWithG(unsigned int index){ // calcolo rotazione con valori della gravità

    std::vector<float> grav = gData[index];
    float modG = sqrt(pow(grav[0],2)+pow(grav[1],2)+pow(grav[2],2));

    //x = mod * cosX -> mod = x/cosx -> cosx = x/mod

    float tmpSinX = -grav[0] / modG;
    float tmpSinY = -grav[1] / modG;
    float tmpSinZ = -grav[2] / modG;

    float tmpAX = acos(tmpSinX);
    float tmpAY = acos(tmpSinY);
    float tmpAZ = acos(tmpSinZ);

    body.setRot(rb::Vector3{tmpAY, tmpAX, tmpAZ });

}


/////////////// cinematica inversa