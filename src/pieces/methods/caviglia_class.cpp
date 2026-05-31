#include "../headers/caviglia.hpp"

Caviglia::Caviglia(rb::Vector3 coords, _Float16 mass){
    rb::Vector3 com = {caviglia_Dim.x/2,caviglia_Dim.x/2, caviglia_Dim.y/2};
    body = rb::rigidbody(coords, com, mass);
    color = caviglia_Col;
    globalPos = {0,0,0};

    initialize_shapes(caviglia_Dim);
}


Caviglia::~Caviglia(){
    delete shapeXZ;
    delete shapeYZ;
}

void Caviglia::update(sf::Clock cl){
    //body.step(cl);
}

sf::Shape* Caviglia::draw(ReferencePlane plane){
    
    rb::Vector3 tmpPos = body.getPos();
    rb::Vector3 tmpRot = body.getRot();

    switch (plane)
    {
    case ReferencePlane::XZ:
        {
        sf::Shape* shape = shapeXZ;
        shape->setRotation(sf::Angle(sf::radians(tmpRot[1])));
        shape->setPosition({tmpPos[0]+globalPos[0],tmpPos[2]+globalPos[2]});
        shape->setScale({1,cos(float(tmpRot[0]))});
        return shape;}
        break;
    
    case ReferencePlane::YZ:
        {
        sf::Shape* shape = shapeYZ;
        shape->setRotation(sf::Angle(sf::radians(tmpRot[0])));
        shape->setPosition({tmpPos[1]+globalPos[1],tmpPos[2]+globalPos[2]});
        shape->setScale({1,cos(float(tmpRot[1]))});
        return shape;}
        break;
    
    default:
        break;
    }
   
    return nullptr;
}