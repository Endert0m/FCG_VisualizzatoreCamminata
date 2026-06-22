#include "../headers/coscia.hpp"

Coscia::Coscia(rb::Vector3 coords, _Float16 mass){
    rb::Vector3 com = {coscia_Dim.x/2,coscia_Dim.z/2,coscia_Dim.y/2};
    body = rb::rigidbody(coords, com, mass, coscia_Dim.z/2);
    color = coscia_Col;
    globalPos = {0,0,0};
    initialize_shapes(coscia_Dim);

    try{
        setTextures(TEXTURE_F,TEXTURE_L);
    }
    catch (const char* &e ){
        printf("Caviglia: %s\n", e);
    }
}

Coscia::~Coscia(){
    delete shapeXZ;
    delete shapeYZ;
}

void Coscia::update(sf::Clock cl, float multiplier){
    //body.step(cl);
}

sf::Shape* Coscia::draw(ReferencePlane plane){
    
    rb::Vector3 tmpPos = body.getPos();
    rb::Vector3 tmpRot = body.getRot();


    switch (plane)
    {
    case ReferencePlane::XZ : case ReferencePlane::XZN:
        {
        sf::Shape* shape = shapeXZ;
        shape->setRotation(sf::Angle(sf::radians(tmpRot[1])));
        shape->setPosition({tmpPos[0]+globalPos[0],tmpPos[2]+globalPos[2]});
        shape->setScale({1,cos(float(tmpRot[0]))});
        shape->setFillColor(color*sf::Color(255,255,255,transparency*255));
        return shape;}
        break;
    
    case ReferencePlane::YZ:
        {
        sf::Shape* shape = shapeYZ;
        shape->setRotation(sf::Angle(sf::radians(tmpRot[0])));
        shape->setPosition({tmpPos[1]+globalPos[1],tmpPos[2]+globalPos[2]});
        shape->setFillColor(color*sf::Color(255,255,255,transparency*255));
        shape->setScale({1,cos(float(tmpRot[1]))});
        return shape;}
        break;
    
    default:
        break;
    }

   
    return nullptr;
}