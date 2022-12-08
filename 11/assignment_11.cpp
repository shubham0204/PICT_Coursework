#include <iostream>
#include <vector>
#include <bits/stdc++.h>
using namespace std;

class PersonInfo {

	string name ;
	string dob ;
	string mobileNumber ;

public:

	PersonInfo() {
		this -> name = "" ;
		this -> dob = "" ;
		this -> mobileNumber = "" ;
	}

	PersonInfo( string name , string dob , string mobileNumber ) {
		this -> name = name ;
		this -> dob = dob ;
		this -> mobileNumber = mobileNumber ;
	}

	void create() {
		cout << "Enter name: " << "\n" ; cin >> name ;
		cout << "Enter DOB: " << "\n" ; cin >> dob ;
		cout << "Enter mobile number: " << "\n" ; cin >> mobileNumber ;
	}

	void print() {
		cout << name << "\n" ;
		cout << dob << "\n" ;
		cout << mobileNumber << "\n" ;
	}
	
	friend bool operator==( const PersonInfo& p1 , const PersonInfo& p2 ) {
	    return p1.name == p2.name ; 
	}

	string getName() {
		return this -> name ;
	}

};

int search( vector<PersonInfo>& records , string name ) {
    std::vector<PersonInfo>::iterator it ; 
	it = std::find( records.begin() , records.end() , PersonInfo( name , "" , "" )) ; 
	if( it != records.end() ) {
	    return int( it - records.begin() ) ;
	}
	else {
	    return -1 ; 
	}
}

bool compareNames( PersonInfo p1 , PersonInfo p2 ) {
	return p1.getName() < p2.getName() ;
}

int main() {

	vector<PersonInfo> data;

	cout << "options: " << "\n" ;
	cout << "1 -> Create record" << "\n" ;
	cout << "2 -> Print all records" << "\n" ;
	cout << "3 -> Search Record" << "\n" ;
	cout << "4 -> Sort records" << "\n" ;

	while( true ) {
		cout << "Enter option: " << "\n" ;
		int option = 0 ; cin >> option ;
		if( option == 1 ) {
			PersonInfo item ;
			item.create() ;
			data.push_back( item ) ;
		}
		else if( option == 2 ) {
			for( int i = 0 ; i < data.size() ; i++ ) {
				data[ i ].print() ;
			}
		}
		else if( option == 3 ) {
			cout << "Enter name to search: " << "\n" ;
			string name = "" ; cin >> name ;
			int index = search( data , name ) ;
			switch( index ) {
			case -1: cout << "No results found" << "\n" ;
			default: data[ index ].print() ;
			}
			cout << "Record found" << "\n" ;
		}
		else if( option == 4 ) {
			std::sort( data.begin() , data.end() , compareNames ) ;
			for( int i = 0 ; i < data.size() ; i++ ) {
				data[ i ].print() ;
			}
		}
	}


	return 0;
}
