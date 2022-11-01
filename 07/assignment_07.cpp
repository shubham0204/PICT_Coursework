#include <iostream>
#include <fstream>
#include <ios>
#include <vector>

using namespace std ;

class Student {

private:
    string name ;
    string division ;
    static int rollNumber ;

public:

    Student() {
        name = "" ;
        division = "" ;
    }

    Student( string name , string division ) {
        this -> name = name ;
        this -> division = division ;
        rollNumber += 1 ;
    }

    friend class StudentDatabase ;

};

class StudentDatabase {

private:
    string dataFilename ;
    Student* data ;
    int numStudents ;

    void readData() {
        fstream fileInputStream( dataFilename , ios::in ) ;
        int counter = 0 ;
        while( fileInputStream.eof() ){
            fileInputStream >> data[ counter ].name ;
            fileInputStream >> data[ counter ].division ;
            fileInputStream >> data[ counter ].rollNumber ;
            counter += 1 ;
        }
        fileInputStream.close() ;
    }

    void writeData() {
        fstream fileOutputStream( dataFilename , ios::out ) ;
        int counter = 0 ;
        while( fileOutputStream.eof() ){
            fileOutputStream << data[ counter ].name ;
            fileOutputStream << data[ counter ].division ;
            fileOutputStream << data[ counter ].rollNumber ;
            counter += 1 ;
        }
        fileOutputStream.close() ;
    }

public:

    StudentDatabase( string& dataFilename , int& numStudents ) {
        this -> dataFilename = dataFilename ;
        this -> numStudents = numStudents ;
        this -> data = new Student[ numStudents ] ;
    }






};

int Student::rollNumber = 21100 ;

int main() {

    fstream fileStream( "sample.txt" , ios::in ) ;

    ofstream outputStream( "sample.txt" ) ;
    outputStream << "Hello World" ;
    outputStream.close() ;

    ifstream inputStream( "sample.txt" ) ;
    string contents ;
    inputStream >> contents ;
    inputStream.close() ;

    cout << contents ;

    return 0 ;
}