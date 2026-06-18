#include "gamba.hpp"

#ifndef LOWER_BODY_H
#define LOWER_BODY_H

struct gamba_data{
    unsigned int* dataPos; 
    std::string cosciaData; 
    std::string cavigliaData;
};


class Lower_Body : CollectionInterface{
protected:
    Gamba* sx;
    Gamba* dx;
    Torso* t;

    PivotJoint* jsx;
    PivotJoint* jdx;

    bool visible = true;
    float alpha = 1;

public:
    Lower_Body(std::vector<gamba_data> data);
    ~Lower_Body();

    void setVisibility(bool c);
    collection create(ReferencePlane plane) override;
};



#endif