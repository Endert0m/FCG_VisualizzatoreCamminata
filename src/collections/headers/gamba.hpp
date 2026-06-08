#include "collection_interface.hpp"
#include "../../csv/headers/csv.hpp"
#include "../../pieces/headers/caviglia.hpp"
#include "../../pieces/headers/coscia.hpp"
#include "../../pieces/headers/sensore.hpp"
#include "../../joints/headers/rigid_joint.hpp"
#include "../../joints/headers/pivot_joint.hpp"

#ifndef GAMBA_H
#define GAMBA_H

class Gamba : public CollectionInterface {
    protected:
        std::vector<PieceInterface*> sensori;
        std::vector<PieceInterface*> pezzi;
        std::vector<JointInterface*> joints;
    public:
        Gamba(rb::Vector3 pos, unsigned int* dataPos, std::string cosciaData, std::string cavigliaData);
        collection create(ReferencePlane plane) override;
};

#endif