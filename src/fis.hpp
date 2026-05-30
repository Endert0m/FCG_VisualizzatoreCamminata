#include<math.h>
#include"rb_class.cpp"
#include<time.h>

/*
Questo namespace deve contenere le funzioni di gestione della fisica del motore.
Ogni moto in questo engine sarà ti tipo uniformemente accelerato per dare una semplificazione della realtà.
Le funzioni necessarie sono:

- Calcolo velocità, richiede: 
    (Oggetto rigidbody)
    (time di partenza, time di arrivo o delta t)
    (Accelerazione media)
    (velocità iniziale)

- Calcolo rotazione, richiede:
    (Oggetto rigidbody)
    (time di partenza, time di arrivo o delta t)
    (Accelerazione tangenziale)
    (RAD/s iniziale)

- Calcolo accelerazione, deve modificare i valori di accelerazione su oggetti di tipo rigidbody, richiede:
    (Oggetto rigidbody)

- Calcolo posizione, deve calcolare la posizione di un rigidbody in in un intervallo di tempo

- Calcolo energia potenziale

- Calcolo inerzia 

- Calcolo energia meccanica 

*/
using namespace rb;

namespace fis{
    
    void calcVel(rigidbody body, const time_t Dtime);
    void calcRot(rigidbody body, const time_t Dtime);
    void calcAcc(rigidbody body, const std::vector<float> Dacc);
    void calcTanAcc(rigidbody body, const std::vector<float> Dacc);
    void calcPos(rigidbody body, const time_t Dtime);

}
