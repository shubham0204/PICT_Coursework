#include <iostream>
#include <vector>
using namespace std;

class Student {

private:

	string name ;

	int studentClass ;
	int studentRollNumber ; 
	static int count ;
	char division ;

	string dateOfBirth ;
	string bloodGroup ;
	string contactAddress ;
	string mobileNumber ;
	string drivingLicenseNum;

public:

	// Default Constructor
	Student(){
		name = "" ;
		studentClass = 0 ;
		count += 1 ;
		studentRollNumber = count ; 
		division = '0' ;
		dateOfBirth = "" ;
		bloodGroup = "" ;
		contactAddress = "" ;
		mobileNumber = "" ;
		drivingLicenseNum = "" ;
	} ;

	// Copy Constructor
	Student( Student& copyStudent ) {
		name = copyStudent.name ;
		studentClass = copyStudent.studentClass ;
		studentRollNumber = copyStudent.studentRollNumber ; 
		count += 1 ; // Roll number is not copied
		division = copyStudent.division ;
		bloodGroup = copyStudent.bloodGroup ;
		contactAddress = copyStudent.contactAddress ;
		mobileNumber = copyStudent.mobileNumber ;
		drivingLicenseNum = copyStudent.drivingLicenseNum ;
	}

	// Destructor
	~Student() {
		cout << "Student object " << name << " destructed" << endl ;
		count -= 1 ;
	}

	// Static method to get count of students
	static int getCount() {
		return count ;
	}

	// Creating Student object dynamically with a static method
	static Student* createStudentEntry() {
		Student* newStudent = new( Student ) ;

		cout << "Enter student name : " << endl ;
		string name_ ;
		cin >> name_ ;
		cout << name_ << endl ;
		newStudent -> name = name_ ;

		return newStudent ;
	}

	static void deleteStudentEntry( Student* deleteStudent ) {
		delete deleteStudent ;
	}

	friend void print( Student& student ) ;
	friend void printDatabase( vector<Student*> db ) ; 

};

void print( Student& student ) {
	cout << "Name : " << student.name << endl ;
	cout << "Roll number : " << student.studentRollNumber << endl ;
}

void printDatabase( vector<Student*> db ) {
    cout << "----------------------" << endl ; 
	for( Student* student : db ) {
		cout << "Name : " << student -> name << endl ; 
		cout << "Roll number : " << student -> studentRollNumber << endl ; 
	}
	cout << "----------------------" << endl ; 
}


int Student::count = 0 ;

int main() {

	vector<Student*> database ; 

	while ( true ) {
		cout << " Choose an operation : " << endl ; 
		cout << "1 -> Enter student data " << endl ; 
		cout << "2 -> Delete student " << endl ; 
		cout << "0 -> Exit " << endl ; 
		int option ; 
		cin >> option ; 
		if( option == 1 ) {
			database.push_back( Student::createStudentEntry() );
			printDatabase( database ) ; 
		} 
		else if( option == 2 ) {
			cout << "Enter roll number " << endl ; 
			int index ;
			cin >> index ;
			database.erase( database.begin() + index - 1 ) ; 
			printDatabase( database ) ;
		} 
		else if( option == 0 ) {
			break ; 
		}
	}
	
	return 0;
}
