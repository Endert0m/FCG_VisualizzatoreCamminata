#include "../headers/torso.hpp"

Torso::Torso(rb::Vector3 coords, _Float16 mass){
    rb::Vector3 com = {torso_Dim.x/2, torso_Dim.y/2, torso_Dim.z/2};
    body = rb::rigidbody(coords,com, mass, torso_Dim.y/2);
    color = torso_Col;
    globalPos = {0,0,0};

    initialize_shapes(torso_Dim);

    try{
        setTextures(TEXTURE_F,TEXTURE_L);
    }
    catch (const char* &e){
        printf("Caviglia: %s\n", e);
    }
}

Torso::~Torso(){
    delete shapeXZ;
    delete shapeYZ;
}

void Torso::update(sf::Clock cl,float multiplier){
    body.step(cl, multiplier);
}

sf::Shape* Torso::draw(ReferencePlane plane){
   
    rb::Vector3 tmpRot = body.getRot();
    rb::Vector3 tmpPos = body.getPos();


    switch (plane)
    {
    case ReferencePlane::XZ: case ReferencePlane::XZN:
        {
        sf::Shape* shape = shapeXZ;
        shape->setRotation(sf::Angle(sf::radians(tmpRot[1])));
        shape->setPosition({tmpPos[0]+globalPos[0],tmpPos[2]+globalPos[2]});
        shape->setScale({plane == ReferencePlane::XZ ? float(1.0) : float(-1.0),cos(float(tmpRot[0]))});
        shape->setFillColor(color*sf::Color(255*multColor[0],255*multColor[1],255*multColor[2],transparency*255));
        return shape;}
        break;
    
    case ReferencePlane::YZ:
        {
        sf::Shape* shape = shapeYZ;
        shape->setRotation(sf::Angle(sf::radians(tmpRot[0])));
        shape->setPosition({tmpPos[1]+globalPos[1],tmpPos[2]+globalPos[2]});
        shape->setFillColor(color*sf::Color(255*multColor[0],255*multColor[1],255*multColor[2],transparency*255));
        return shape;}
        break;
    
    default:
        break;
    }

    return nullptr;
}