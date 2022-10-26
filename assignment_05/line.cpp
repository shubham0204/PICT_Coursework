#include <cmath>

class Line {

private:


    float slope = 0.0f ;
    float slopeInv = 0.0f ;

    int getRegionCode( float x_min , float y_min , float x_max , float y_max ,
                       float x , float y  ) {
        int code = 0;
        if( x > x_max && y > y_max ) {
            code = 10 ; // 1010
        }
        else if( x > x_max && y <= y_max && y >= y_min ) {
            code = 2 ; // 0010 // Right
        }
        else if( x > x_max && y < y_min ) {
            code = 6 ; // 0110
        }
        else if( x < x_min && y > y_max ) {
            code = 9 ; // 1001
        }
        else if( x < x_min && y <= y_max && y >= y_min ) {
            code = 1 ; // 0001 // Left
        }
        else if( x < x_min && y < y_min ) {
            code = 5 ; // 0101
        }
        else if( x >= x_min && x <= x_max && y > y_max ) {
            code = 8 ; // 1000 // Top
        }
        else if( x >= x_min && x <= x_max && y <= y_max && y >= y_min ) {
            code = 0 ; // 0000
        }
        else if( x >= x_min && x <= x_max && y < y_min ) {
            code = 4 ; // 0100 // Bottom
        }
        return code ;
    }

public:

    float x1 ;
    float y1 ;
    float x2 ;
    float y2 ;

    int x_a ;
    int x_b ;
    int y_a ;
    int y_b ;
    /*/

    float x_min ;
    float x_max ;
    float y_min ;
    float y_max ;
    */

    int code1 ;
    int code2 ;

    Line( float x1_ , float y1_ , float x2_ , float y2_ ) {
        x1 = x1_ ;
        y1 = y1_ ;
        x2 = x2_ ;
        y2 = y2_ ;
        slope = ( y2 - y1 ) / ( x2 - x1 ) ;
        slopeInv = 1.0f / slope ;
        /*
        x_min = std::min( x1 , x2 ) ;
        x_max = std::max( x1 , x2 ) ;
        y_min = std::min( y1 , y2 ) ;
        y_max = std::max( y1 , y2 ) ;
        */
    }


    void initializePositionCodes( float x_min , float y_min , float x_max , float y_max ) {
        code1 = getRegionCode( x_min , y_min , x_max , y_max , x1 , y1 ) ;
        code2 = getRegionCode( x_min , y_min , x_max , y_max , x2 , y2 ) ;

        x_a = (int) x1 + ( slopeInv * ( y_max - y1 ) ) ;
        x_b = (int) x1 + ( slopeInv * ( y_min - y1 ) ) ;
        y_a = (int) y1 + ( slope * ( x_min - x1 ) ) ;
        y_b = (int) y1 + ( slope * ( x_max - x1 ) ) ;
    }

    void checkConditions() {

    }
    
};
