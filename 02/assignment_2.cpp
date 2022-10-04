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
	}

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
		newStudent -> name = name_ ;
        newStudent -> studentRollNumber = 89 ;
		return newStudent ;
	}

	static void deleteStudentEntry( Student* deleteStudent ) {
		delete deleteStudent ;
	}

	friend class Database ;

};

// Friend class that can access details of Student
class Database {

private:
	vector<Student*> database ;

public:

	void addStudent( Student* student ) {
		database.push_back( student ) ;
	}

	void deleteStudent( int index ) {
		database.erase( database.begin() + index) ;
	}

	Student* getStudent( int index ) {
		return database[ index ] ;
	}

    void updateName( Student* student , string newName ) {
        student -> name = newName ;
    }

	void print() {
	    cout << "----------------------" << endl ;
		for( Student* student : database ) {
			cout << "Name : " << student -> name << endl ;
			cout << "Roll number : " << student -> studentRollNumber << endl ;
		}
		cout << "----------------------" << endl ;
	}

};

int Student::count = 0 ;

int main() {

	Database database;

	while ( true ) {
		cout << " Choose an operation : " << endl ; 
		cout << "1 -> Enter student data " << endl ; 
		cout << "2 -> Delete student " << endl ;
        cout << "3 -> Update" << endl ;
		cout << "0 -> Exit " << endl ; 
		int option ; 
		try {
			cin >> option ;
			if( option != 1 && option != 0 && option != 2 && option != 3 ) {
				throw option ;
			}
		}
		catch( int invalidOption ) {
			cout << "Invalid option " << invalidOption << endl ;
		}
		if( option == 1 ) {
			database.addStudent( Student::createStudentEntry() );
			database.print() ;
		} 
		else if( option == 2 ) {
			cout << "Enter roll number " << endl ;
			int index ;
			cin >> index ;
			Student::deleteStudentEntry( database.getStudent( index - 1 ) ) ;
			database.deleteStudent( index - 1 ) ;
			database.print() ;
		}
        else if( option == 3 ) {
            cout << "Enter roll number " << endl ;
            int index ;
            cin >> index ;
            cout << "Choose Update option" << endl ;
            cout << "1 -> Name" << endl ;
            int updateOption ;
            cin >> updateOption ;
            if ( updateOption == 1 ) {
                cout << "Enter new name :" << endl ;
                string name ;
                cin >> name ;
                Student* updateStudent = database.getStudent( index - 1 ) ;
                database.updateName( updateStudent , name ) ;
            }
            database.print() ;
        }
		else if( option == 0 ) {
			break ;
		}
	}
	
	return 0;
}
