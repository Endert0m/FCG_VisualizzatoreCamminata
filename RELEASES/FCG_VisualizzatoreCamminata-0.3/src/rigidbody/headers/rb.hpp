#include<math.h>
#include<vector>
#include <SFML/Graphics.hpp>

#ifndef RB_H
#define RB_H

    namespace rb{
        typedef std::vector<float> Vector3;
        typedef std::vector<_Float16> Vector3_s;

        class rigidbody
        {
            private:
                Vector3 vel = {0,0,0};
                Vector3 acc = {0,0,0};
                Vector3_s rot = {0,0,0};
                Vector3 tanAcc = {0,0,0};

                _Float16 mass = 1;

                Vector3 coords = {0,0,0};
                Vector3 centerOfMass = {0,0,0};

                int64_t prevT = 0;

                //funzioni
                void calcVel(const float Dtime);
                void calcRot(const time_t Dtime);
                void calcAcc(const Vector3 Dacc);
                void calcTanAcc(const Vector3 Dacc);
                void calcPos(const float Dtime);



            public:
                rigidbody(){}
                rigidbody(Vector3 coords, Vector3 centerOfMass, _Float16 mass);
                ~rigidbody();

                
                Vector3 getPos();
                Vector3_s getRot();
                void setPos(const Vector3 Npos);
                void setRot(const Vector3_s Nrot);
                void setVel(const Vector3 Nacc);
                void setAcc(const Vector3 Nvel);
                void step(const sf::Clock time);

                //complesso, deve definire accelerazione e accelerazione tangenziale 
                void appForce(Vector3 f, Vector3 pos);
        };

    }


    
    inline rb::Vector3 operator+(const rb::Vector3& v1, const rb::Vector3& v2) {
            if (v1.size() != 3 || v2.size() != 3) {
                throw std::invalid_argument("I vettori devono avere esattamente 3 elementi.");
            }
            return rb::Vector3{
                v1[0] + v2[0],
                v1[1] + v2[1],
                v1[2] + v2[2]
            };
        }

     inline rb::Vector3 operator-(const rb::Vector3& v1, const rb::Vector3& v2) {
            if (v1.size() != 3 || v2.size() != 3) {
                throw std::invalid_argument("I vettori devono avere esattamente 3 elementi.");
            }
            return rb::Vector3{
                v1[0] - v2[0],
                v1[1] - v2[1],
                v1[2] - v2[2]
            };
        }

    inline rb::Vector3_s operator+(const rb::Vector3_s& v1, const rb::Vector3_s& v2) {
            if (v1.size() != 3 || v2.size() != 3) {
                throw std::invalid_argument("I vettori devono avere esattamente 3 elementi.");
            }
            return rb::Vector3_s{
                v1[0] + v2[0],
                v1[1] + v2[1],
                v1[2] + v2[2]
            };
        }

     inline rb::Vector3_s operator-(const rb::Vector3_s& v1, const rb::Vector3_s& v2) {
            if (v1.size() != 3 || v2.size() != 3) {
                throw std::invalid_argument("I vettori devono avere esattamente 3 elementi.");
            }
            return rb::Vector3_s{
                v1[0] - v2[0],
                v1[1] - v2[1],
                v1[2] - v2[2]
            };
        }
        /*
        inline bool operator!=(const rb::Vector3_s& v1, const rb::Vector3_s& v2) {
            if (v1.size() != 3 || v2.size() != 3) {
                throw std::invalid_argument("I vettori devono avere esattamente 3 elementi.");
            }
            return true;
        }*/
#endif