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

class Slots {

    private:

    struct Node {
        Appointment appointment ; 
        Node* pointerToNext ; 
    } ;

    int appointmentStartTime ; 
    int appointmentEndTime ; 

    Node* HEAD ; 
    Node* TAIL ;
    int numAppointments ; 
    int numSlots ; 

    public:

    Slots( int numSlotsInADay ) {
        numAppointments = 0 ; 
        numSlots = numSlotsInADay;
        TAIL = nullptr ; 
        HEAD = nullptr ; 
        int startTime = 9 ; // 9 AM
        for( int i = 0 ; i < numSlots ; i++ ) {
            Appointment app ; 
            app.isSlotAvailable = true ; 
            app.startTime = startTime ;
            app.endTime = startTime + 1 ; // After one hour
            app.minDuration = 30 ; // minutes
            app.maxDuration = 60 ; // minutes
            addAppointment( app ) ; 
            startTime++ ; 
        }
    }

    bool checkSlotAvailability( int slotTime ) {
        Node* currentNode = HEAD ;
        while( currentNode != nullptr ) {
            if( currentNode -> appointment.startTime == slotTime ){
                return currentNode -> appointment.isSlotAvailable ;
            }
            currentNode = currentNode -> pointerToNext ;
        }
        return true ; 
    }


    Node* getElement( int index ) {
        Node* currentNode = HEAD ;
        for ( int i = 0 ; i < numSlots ; i ++ ) {
            if( i == index ) {
                return currentNode ; 
            }
            currentNode = currentNode -> pointerToNext ;
        }
    }

    void sortFreeAppointments() {
        Node* firstElement ; 
        Node* secondElement ; 
        for( int i = 0 ; i < numSlots ; i++ ) {
            for( int j = 0 ; j < numSlots - 1 ; j++ ) {
                firstElement = getElement( i ) ; 
                secondElement = getElement( i + 1 ) ;
                if( firstElement -> appointment.startTime > secondElement -> appointment.startTime ) {
                    // Swapping
                    Appointment temp = firstElement -> appointment ; 
                    firstElement -> appointment = secondElement -> appointment ; 
                    secondElement -> appointment = temp ; 
                }
            }
        }
    }

    
    void bookAppointment( int startTime ) {
        Node* currentNode = HEAD ;
        while( currentNode != nullptr ) {
            if( currentNode -> appointment.startTime == startTime ){
                currentNode -> appointment.isSlotAvailable = false; 
                cout << "Slot for " << startTime << ":00 booked." << endl ; 
            }
            currentNode = currentNode -> pointerToNext ;
        }
    }

    void cancelAppointment( int startTime ) {
        Node* currentNode = HEAD ;
        while( currentNode != nullptr ) {
            if( currentNode -> appointment.startTime == startTime ){
                currentNode -> appointment.isSlotAvailable = true; 
                cout << "Slot for " << startTime << ":00 cancelled." << endl ; 
            }
            currentNode = currentNode -> pointerToNext ;
        }
    }

    void addAppointment( Appointment app ) {
        Node* newNode = new( Node ) ; 
        newNode -> appointment = app ; 
        if( numAppointments == 0 ) {
            newNode -> pointerToNext = nullptr ; 
            HEAD = TAIL = newNode ; 
        }
        else {
            TAIL -> pointerToNext = newNode ; 
            TAIL = newNode ; 
        }
        numAppointments++ ;
    }

    void printFreeSlots() {
        Node* currentNode = HEAD ;
        while( currentNode != nullptr ) {
            Appointment app = currentNode -> appointment ;
            if( app.isSlotAvailable ) {
                cout << " ----------------------------------------- " << endl ; 
                cout << "Status     : " << "Not booked" << endl ; 
                cout << "Start Time : " << app.startTime << "hrs" << endl ; 
                cout << "End Time   : " << app.endTime << "hrs" << endl ;  
            } 
            currentNode = currentNode -> pointerToNext ; 
        }
    }

    void printAllSlots() {
        Node* currentNode = HEAD ;
        while( currentNode != nullptr ) {
            Appointment app = currentNode -> appointment ; 
            cout << " ----------------------------------------- " << endl ; 
            if( app.isSlotAvailable ) {
                cout << "Status     : " << "Not booked" << endl ; 
            }
            else {
                cout << "Status     : " << "Booked" << endl ; 
            }
            cout << "Start Time : " << app.startTime << "hrs" << endl ; 
            cout << "End Time   : " << app.endTime << "hrs" << endl ; 
            currentNode = currentNode -> pointerToNext ; 
        }
    }

} ; 

int main() {
    int numSlots = 10 ; 
    Slots slots( 10 ) ;

    int numTrials = 0 ; 
    while( numTrials < 100 ) {
        cout << "Enter option -> " << endl ; 
        cout << "1 -> Show Appointment status" << endl ; 
        cout << "2 -> Book Appointment" << endl ;
        cout << "3 -> Show Free Slots" << endl ;
        cout << "4 -> Cancel Appointment" << endl ;
        int option ; 
        cin >> option ; 
       
        if( option == 1 ) {
            slots.printAllSlots() ; 
        }
        else if( option == 2 ) {
            int startTime ; 
            cout << "Enter start time : " << endl ; 
            cin >> startTime ; 
            slots.bookAppointment( startTime ) ; 
        }
        else if( option == 3 ) {
            cout << "Free Slots are ------------> " << endl ; 
            slots.printAllSlots() ; 
        }
        else if( option == 4 ) {
            int startTime ; 
            cout << "Enter start time : " << endl ; 
            cin >> startTime ; 
            slots.cancelAppointment( startTime ) ; 
        }
        else {
            break;
        }
        numTrials++ ; 
    }
    return 0;
}