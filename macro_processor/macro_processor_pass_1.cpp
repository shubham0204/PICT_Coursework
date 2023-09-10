#include <tuple>
#include <vector>
#include <algorithm>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

#define LBR '\n'

class Pass1 {

    vector<tuple<string,int,int,int,int>> mntab ; 
    vector<tuple<string,string>> kpdtab ;
    vector<string> pntab ; 
    vector<string> aptab ; 
    vector<vector<string>> tokens ; 

    public:

    Pass1( string filepath ) {
        vector<string> lines = Pass1::readLines( Pass1::readTextFile( filepath ) ) ;
        for( const string& line : lines ) {
            tokens.push_back( Pass1::splitBySpace( line ) ) ; 
        }
    }

    void perform() {
        for( int i = 1 ; i < tokens.size() ; i++ ) {
            vector<string> lineTokens = tokens[ i ] ; 
            if( tokens[ i - 1 ][0] == "MACRO" ) {
                // Process macro prototype
                string macroName = lineTokens[0] ; 
                int numKPD = 0; 
                int numPP = 0;
                for( int j = 1 ; j < lineTokens.size() ; j++ ) {
                    // Parse parameters
                    string parameter = lineTokens[ j ] ; 
                    if( parameter.find( "=" ) != string::npos ) {
                        // Keyword parameter
                        numKPD++ ;
                        string name = parameter.substr( 0,parameter.find( "=" ) ) ; 
                        string defaultValue = parameter.substr( parameter.find( "=" ) + 1, parameter.length() ) ; 
                        kpdtab.push_back( { name , defaultValue } ) ;  
                        pntab.push_back( name ) ;
                    }
                    else {
                        // Positional parameters
                        numPP++ ;    
                        pntab.push_back( parameter ) ; 
                    }
                }
                mntab.push_back( { macroName , numPP , numKPD , 0 , 0  } ) ; 
            }
            else {
                cout << lineTokens[0] << " " ; 
                for( int j = 1 ; j < lineTokens.size() ; j++ ) {
                    if( lineTokens[j][0] == '&' ) {
                        int index = std::find( pntab.begin() , pntab.end() , lineTokens[j] ) - pntab.begin() ; 
                        if( index >= 0 ) {
                            cout << "( P , " << index+1 << " )" << " " ; 
                        }
                    }
                }
                cout << LBR ; 
            }
        }
        printMNTAB() ; 
        printKPDTAB() ;
        printPNTAB() ;  
    }

    void printMNTAB() {
        for( const tuple<string,int,int,int,int>& entry : mntab ) {
            cout << get<0>( entry ) << ' ' ; 
            cout << get<1>( entry ) << ' ' ; 
            cout << get<2>( entry ) << ' ' ; 
            cout << get<3>( entry ) << ' ' ; 
            cout << get<4>( entry ) << ' ' ; 
            cout << LBR ; 
        }
    }

     void printPNTAB() {
        for( const string entry : pntab ) {
            cout << entry << LBR ; 
        }
    }

    void printKPDTAB() {
        for( const tuple<string,string>& entry : kpdtab ) {
            cout << get<0>( entry ) << ' ' ; 
            cout << get<1>( entry ) << ' ' ; 
            cout << LBR ; 
        }
    }

    static string readTextFile( string filepath ) {
        fstream inputStream( filepath,ios::in ) ; 
        string sourceContents = "" ;
        char c = inputStream.get() ; 
        while( !inputStream.eof() ) {
            sourceContents += c;
            c = inputStream.get();  
        }
        return sourceContents ;
    }

    static vector<string> readLines( string sourceContents ) {
        vector<string> lines;
        stringstream ss( sourceContents );
        string line;
        while( getline( ss, line,'\n')) {
            lines.push_back( line );
        }
        return lines;
    }

    static vector<string> splitBySpace( const string& line ) {
        stringstream stream( line ) ; 
        string token = "";
        vector<string> tokens;
        while( stream >> token ) {
            tokens.push_back( token ) ; 
        }
        return tokens;
    }


} ; 

