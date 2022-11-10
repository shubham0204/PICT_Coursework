#include <cmath>


// class that stores data of each line drawn, like,
// region codes, y_min, y_max, slope, slope inverse
class Line {

private:

    int TOP = 8 ;    // 1000
    int BOTTOM = 4 ; // 0100
    int RIGHT = 2 ;  // 0010
    int LEFT = 1 ;   // 0001

    float slope = 0.0f ;
    float slopeInv = 0.0f ;

    // Compute region code of point ( x , y ) given bounds of the clipping window
    int getRegionCode( float x_min , float y_min , float x_max , float y_max ,
                       float x , float y  ) {
        int code = 0;
        // TBRL codes
        // If none of the below conditions are satisfied, the code remains 0000 ( completely inside the clipping
        // window )
        if( x > x_max ) {
            // Change 'R' bit from 0 to 1
            code |= RIGHT ;
        }
        else if( x < x_min ) {
            // Change 'L' bit from 0 to 1
            code |= LEFT ;
        }
        if( y > y_max ) {
            // Change 'T' bit from 0 to 1
            code |= TOP ;
        }
        else if( y < y_min ) {
            // Change 'B' bit from 0 to 1
            code |= BOTTOM ;
        }
        return code ;
    }

public:

    // Coordinates of first point
    float x1 ;
    float y1 ;

    // Coordinates of second point
    float x2 ;
    float y2 ;

    int x_TOP ;    // X-coordinate of intersection with TOP of clipping window
    int x_BOTTOM ; // X-coordinate of intersection with BOTTOM of clipping window
    int y_LEFT ;   // Y-coordinate of intersection with LEFT of clipping window
    int y_RIGHT ;  // Y-coordinate of intersection with RIGHT of clipping window

    int code1 ; // Region code for point ( x1 , y1 )
    int code2 ; // Region code for point ( x2 , y2 )


    Line( float x1_ , float y1_ , float x2_ , float y2_ ) {
        x1 = x1_ ;
        y1 = y1_ ;
        x2 = x2_ ;
        y2 = y2_ ;
        // Calculate slope and its inverse in the constructor
        slope = ( y2 - y1 ) / ( x2 - x1 ) ;
        slopeInv = 1.0f / slope ;
    }


    // Initialize region codes for ( x1 , y1 ) and ( x2 , y2 )
    // along with intersection points
    void initializePositionCodes( float x_min , float y_min , float x_max , float y_max ) {

        code1 = getRegionCode( x_min , y_min , x_max , y_max , x1 , y1 ) ;
        code2 = getRegionCode( x_min , y_min , x_max , y_max , x2 , y2 ) ;

        // For x coordinates, use x = x1 + ( y - y1 ) * ( 1 / m )
        x_TOP = (int) x1 + ( slopeInv * ( y_max - y1 ) ) ;
        x_BOTTOM = (int) x1 + ( slopeInv * ( y_min - y1 ) ) ;

        // For y coordinates, use y = y1 + ( x - y1 ) * ( m )
        y_LEFT = (int) y1 + ( slope * ( x_min - x1 ) ) ;
        y_RIGHT = (int) y1 + ( slope * ( x_max - x1 ) ) ;
    }
    
};
