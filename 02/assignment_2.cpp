#include <iostream>
using namespace std;

class Student {

private:

	string name ;

	int studentClass ;
	static int rollNumber ;
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
		rollNumber += 1 ;
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
		rollNumber += 1 ; // Roll number is not copied
		division = copyStudent.division ;
		bloodGroup = copyStudent.bloodGroup ;
		contactAddress = copyStudent.contactAddress ;
		mobileNumber = copyStudent.mobileNumber ;
		drivingLicenseNum = copyStudent.drivingLicenseNum ;
	}

	// Destructor
	~Student() {
		cout << "Student object " << name << " destructed" << endl ;
		rollNumber -= 1 ;
	}

	// Static method to get count of students
	static int getCount() {
		return rollNumber ;
	}

	// Creating Student object dynamically with a static method
	static Student* createStudentEntry() {
		Student* newStudent = new( Student ) ;

		cout << "Enter student name : " << endl ;
		string name_ ;
		cin >> name_ ;
		cout << name_ << endl ;
		newStudent -> name = name_ ;

		cout << "Enter student roll number : " << endl ;
		int rollNumber_ ;
		cin >> rollNumber_ ;
		newStudent -> rollNumber = rollNumber_ ;

		return newStudent ;
	}

	static void deleteStudentEntry( Student* deleteStudent ) {
		delete deleteStudent ;
	}


	friend void print( Student& student ) ;

};

void print( Student& student ) {
	cout << "Name : " << student.name << endl ;
	cout << "Roll number : " << student.rollNumber << endl ;
}


int Student::rollNumber = 0 ;

int main() {

	int numStudents ;
	cout << "Enter total number of students : " << endl ;
	cin >> numStudents ;
	// Array of pointers, to store pointer to each dynamically allocated object of Student
	Student* database[ numStudents ] ;

	for( int i = 0 ; i < numStudents ; i++ ) {
		database[ i ] = Student::createStudentEntry() ;
		print( *(database[i]) ) ;
	}

	for( int i = 0 ; i < numStudents - 1 ; i++ ) {
		Student::deleteStudentEntry( database[ i ] ) ;
	}

	cout << Student::getCount() << endl ;

	return 0;
}
