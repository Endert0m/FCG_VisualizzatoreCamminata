#include "../headers/lower_body.hpp"

Lower_Body::Lower_Body(rb::Vector3 pos,std::vector<gamba_data> data){
    if (data.size() != 2) throw "Lower_Body_Error: data vector size must be 2";

    sx = new Gamba({pos[0],pos[1],pos[2]+150},data[0].dataPos,data[0].cosciaData,data[0].cavigliaData);
    dx = new Gamba({pos[0],pos[1]+200,pos[2]+150},data[1].dataPos,data[1].cosciaData,data[1].cavigliaData);
    t = new Torso({pos[0],pos[1]+100,pos[2]},_Float16(3.0));

    PieceInterface* psx = sx->getJointPiece();
    PieceInterface* pdx = dx->getJointPiece();

    jsx = new PivotJoint(t, {psx}, rb::Vector3{0,-100,50});
    jdx = new PivotJoint(t, {pdx}, rb::Vector3{0,100,50});
}


collection Lower_Body::create(ReferencePlane plane){
    collection coll;
    dx->setDirection(Direction::R);
    sx->setTransparency(1);
    dx->setTransparency(1);

    switch (plane)
    {
    case ReferencePlane::XZN: 
        dx->setTransparency(0.5);
        coll = coll + dx->create(plane);
        coll = coll + sx->create(plane);
        break;
    case ReferencePlane::XZ:
        sx->setTransparency(0.5);
        coll = coll + sx->create(plane);
        coll = coll + dx->create(plane);
        break;
    case ReferencePlane::YZ:
        coll = coll + dx->create(plane);
        coll = coll + sx->create(plane);
        break;

    default:
        break;
    }
    coll.pieces.push_back(t);
    coll.joints.push_back(jsx);
    coll.joints.push_back(jdx);
    
    
    return coll;
}

Lower_Body::~Lower_Body(){
    delete sx;
    delete dx;
    delete t;
    delete jdx;
    delete jsx;
}

void Lower_Body::setVisibility(bool c){

}

bool Lower_Body::setTransparency(float alpha){
    if (!sx->setTransparency(alpha)) return false;
    dx->setTransparency(alpha);
    t->setTransparency(alpha);
    return true;
}