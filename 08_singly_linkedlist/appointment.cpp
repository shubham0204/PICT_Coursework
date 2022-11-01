#include <iostream>
using namespace std ; 

class Appointment {

    public:

    int startTime ; 
    int endTime ; 
    int minDuration ; 
    int maxDuration ;
    bool isSlotAvailable ; 

    // To access 
    friend class Slots ; 

} ; 