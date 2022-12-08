#include <iostream>
#include <map>
using namespace std;

int main() {

    map<string,int> states ; 
    states[ "Uttar_Pradesh" ] = 199812341 ; 
    states[ "Maharashta" ] = 112372972;	
    states[ "Bihar" ] = 103804637;
    states[ "West_Bengal" ] = 91347736;
    states[ "Madhya_Pradesh" ] = 72597565;
    states[ "Tamil Nadu" ] = 72138958;	
    states[ "Rajasthan" ] = 68621012;	
    states[ "Karnataka" ] = 61130704;	
    states[ "Gujarat" ] = 60383628;	
    states[ "Andhra_Pradesh" ] = 49386799 ;
    try {
        string stateName ;
        cout << "Enter name of the state: " << "\n" ;
        cin >> stateName ;
        int population = states[ stateName ] ; 
        if( population == 0 ) {
                throw stateName ; 
        }
        else {
            cout << "Population is " << population << "\n" ;
        }
    }
    catch( string badName ) {
        cout << "State " << badName << " does not exist." << "\n" ; 
    }
    return 0 ;
}