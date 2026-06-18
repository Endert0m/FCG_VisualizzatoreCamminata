#include "../headers/lower_body.hpp"

Lower_Body::Lower_Body(std::vector<gamba_data> data){
    if (data.size() != 2) throw "Lower_Body_Error: data vector size must be 2";
    sx = new Gamba({0,0,150},data[0].dataPos,data[0].cosciaData,data[0].cavigliaData);
    dx = new Gamba({0,0,150},data[1].dataPos,data[1].cosciaData,data[1].cavigliaData);
    t = new Torso({0,100,0},_Float16(3.0));

    PieceInterface* psx = sx->getJointPiece();
    PieceInterface* pdx = dx->getJointPiece();

    jsx = new PivotJoint(t, {psx}, rb::Vector3{0,-100,50});
    jdx = new PivotJoint(t, {pdx}, rb::Vector3{0,100,50});
}


collection Lower_Body::create(ReferencePlane plane){
    collection coll;
    coll = coll + sx->create(plane);
    coll = coll + dx->create(plane);


}