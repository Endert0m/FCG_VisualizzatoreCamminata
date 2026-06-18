#include "gamba.hpp"

#ifndef LOWER_BODY_H
#define LOWER_BODY_H

struct gamba_data{
    rb::Vector3 pos; 
    unsigned int* dataPos; 
    std::string cosciaData; 
    std::string cavigliaData;
};


class lower_body
{
protected:
    Gamba sx;
    Gamba dx;
    Torso t;

public:
    lower_body(std::vector<gamba_data> data);
    ~lower_body();
};



#endif