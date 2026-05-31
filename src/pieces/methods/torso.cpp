#include "../headers/torso.hpp"

Torso::Torso(rb::Vector3 coords, _Float16 mass){
    rb::Vector3 com = {torso_Dim.x/2, torso_Dim.y/2, torso_Dim.z/2};
    body = rb::rigidbody(coords,com, mass);
    color = torso_Col;
    globalPos = {0,0,0};

    initialize_shapes(torso_Dim);
}

Torso::~Torso(){
    delete shapeXZ;
    delete shapeYZ;
}

void Torso::update(sf::Clock cl){
    
}

sf::Shape* Torso::draw(ReferencePlane plane){
   
    rb::Vector3_s tmpRot = body.getRot();
    rb::Vector3 tmpPos = body.getPos();


    switch (plane)
    {
    case ReferencePlane::XZ:
        {
        sf::Shape* shape = shapeXZ;
        shape->setRotation(sf::Angle(sf::radians(tmpRot[2])));
        shape->setPosition({tmpPos[0]+globalPos[0],tmpPos[2]+globalPos[2]});
        return shape;}
        break;
    
    case ReferencePlane::YZ:
        {
        sf::Shape* shape = shapeYZ;
        shape->setRotation(sf::Angle(sf::radians(tmpRot[1])));
        shape->setPosition({tmpPos[1]+globalPos[1],tmpPos[2]+globalPos[2]});
        return shape;}
        break;
    
    default:
        break;
    }

    return nullptr;
}