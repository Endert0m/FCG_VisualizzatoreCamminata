#include "../headers/lower_body.hpp"

Lower_Body::Lower_Body(rb::Vector3 pos,std::vector<gamba_data> data){
    if (data.size() != 2) throw "Lower_Body_Error: data vector size must be 2";

    sx = new Gamba({pos[0],pos[1]-60,pos[2]+150},data[0].dataPos,data[0].cosciaData,data[0].cavigliaData);
    dx = new Gamba({pos[0],pos[1]+60,pos[2]+150},data[1].dataPos,data[1].cosciaData,data[1].cavigliaData);
    t = new Torso({pos[0],pos[1],pos[2]},_Float16(3.0));

    PieceInterface* psx = sx->getJointPiece();
    PieceInterface* pdx = dx->getJointPiece();

    jsx = new PivotJoint(t, {psx}, rb::Vector3{0,-60,50});
    jdx = new PivotJoint(t, {pdx}, rb::Vector3{0,60,50});
}


collection Lower_Body::create(ReferencePlane plane){
    collection coll;
    
    sx->setTransparency(transparency);
    dx->setTransparency(transparency);
    t->setTransparency(transparency);
    
    if (isVisible){
        coll.joints.push_back(jsx);
        coll.joints.push_back(jdx);

        switch (plane)
        {
        case ReferencePlane::XZN: 
            dx->setTransparency(0.5 * transparency);
            dx->setDirection(Direction::L);
            sx->setDirection(Direction::R);
            coll = coll + dx->create(plane);
            coll = coll + sx->create(plane);
            break;
        case ReferencePlane::XZ:
            sx->setTransparency(0.5 * transparency);
            dx->setDirection(Direction::R);
            sx->setDirection(Direction::L);
            coll = coll + sx->create(plane);
            coll = coll + dx->create(plane);
            break;
        case ReferencePlane::YZ:
            sx->setDirection(Direction::R);
            dx->setDirection(Direction::L);
            coll = coll + dx->create(plane);
            coll = coll + sx->create(plane);
            break;

        default:
            break;
        }
        
        coll.pieces.push_back(t);
    }
    return coll;
}

Lower_Body::~Lower_Body(){
    delete sx;
    delete dx;
    delete t;
    delete jdx;
    delete jsx;
}


void Lower_Body::update(sf::Clock cl, float multiplier){
    float sxAcc = sx->getZ_Acc() ;
    float dxAcc = dx->getZ_Acc() ;

    int64_t Dtime = cl.getElapsedTime().asMicroseconds();
    if (prevT == 0) prevT = Dtime;
    float dt = (float(Dtime) / 1000000.0) - (float(prevT) / 1000000.0);
    prevT = Dtime;

    float tmpVelS = sxAcc*dt;
    float tmpVelD = dxAcc*dt;
    float tmpPosD =  tmpVelD *dt *500 + velD * 500 * dt; 
    float tmpPosS =  tmpVelS * 500 *dt + velS * 500 * dt;

    velD += tmpVelD; 
    velS += tmpVelS;

    // PosD + PosS + Z = 0
    float alpha = atan(tmpPosD/60.0 - tmpPosS/60); //il 60 è il raggio (dimesione del bacino)

    //applico smoothing e ritorno a zero
    velD -= velD * fabs(alpha);
    velS -= velS * fabs(alpha) ;
    
    t->body.setRot({alpha,0,0});
    auto tPos = t->body.getPos();
    

}