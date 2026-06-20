#include "gamba.hpp"
#include "collection_interface.hpp"

#ifndef LOWER_BODY_H
#define LOWER_BODY_H

struct gamba_data{
    unsigned int* dataPos; 
    std::string cosciaData; 
    std::string cavigliaData;
};


class Lower_Body : public CollectionInterface{
protected:
    Gamba* sx;
    Gamba* dx;
    Torso* t;

    PivotJoint* jsx;
    PivotJoint* jdx;

    bool visible = true;
    float alpha = 1;

public:
    Lower_Body(rb::Vector3 pos, std::vector<gamba_data> data);
    ~Lower_Body();
    void update() override;
    void setVisibility(bool c);
    bool setTransparency(float alpha) override;
    collection create(ReferencePlane plane) override;
};



#endif