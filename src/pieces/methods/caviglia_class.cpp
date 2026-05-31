#include "../headers/caviglia.hpp"

Caviglia::Caviglia(rb::Vector3 coords, _Float16 mass){
    size = caviglia_Dim;
    rb::Vector3 com = {size.x/2,0, size.y/2};
    body = rb::rigidbody(coords, com, mass);
    color = caviglia_Col;
    shape = new sf::RectangleShape(size);
    shape->setOrigin({size.x/2,size.y/2});
    globalPos = {0,0,0};
}

Caviglia::~Caviglia(){
    delete shape;
}

void Caviglia::update(sf::Clock cl){
    //body.step(cl);
}

sf::Shape* Caviglia::draw(ReferencePlane plane){
    shape->setFillColor(color);
    rb::Vector3 tmpPos = body.getPos();
    rb::Vector3_s tmpRot = body.getRot();

    switch (plane)
    {
    case ReferencePlane::XZ:
        shape->setPosition({tmpPos[0]+globalPos[0],tmpPos[2]+globalPos[2]});
        shape->setRotation(sf::Angle(sf::radians(tmpRot[2])));
        break;
    

    default:
        break;
    }

   
    return shape;
}