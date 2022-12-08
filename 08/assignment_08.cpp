#include <iostream>
#include <fstream>
using namespace std ;

class StudentInfo {

public:

    char name[20];
    char division[20] ;
    char department[20];
    int rollNumber ;

    StudentInfo(){
    } ;

    void print() {
        //cout << name << division << department << endl ;
    }

    void save( string filename ) {
        fstream outputStream( filename , ios::out ) ;
        char* objectBytes = (char*)this ;
        outputStream.write( objectBytes , sizeof( *this ) ) ;
        outputStream.close() ;
    }

    void load( string filename ) {
        fstream inputStream( filename , ios::in ) ;
        StudentInfo studentInfo ;
        inputStream.read( (char*)&studentInfo , sizeof( studentInfo ) ) ;
        inputStream.close() ;
        cout << studentInfo.name << endl ;
    }

} ;

int main()  {

    StudentInfo student ;
    cout << "Enter student details" << endl ;
    cin.getline( student.name , sizeof( student.name ) ) ;
    cin.getline( student.division , sizeof( student.division ) ) ;
    cin.getline( student.department , sizeof( student.department ) ) ;
    cin.getline( student.name , sizeof( student.name ) ) ;
    student.save( "student.dat" ) ;

    StudentInfo newStudent;
    newStudent.load( "student.dat" ) ;
    newStudent.print() ;


    return 0;
}