#include "edge.h"

Edge::Edge( QPoint& p1 , QPoint& p2 ){
    x1 = (float)p1.x() ;
    y1 = (float)p1.y() ;
    x2 = (float)p2.x() ;
    y2 = (float)p2.y() ;
    if( p1.y() < p2.y() ) {
        yMin = (float) p1.y() ;
        yMax = (float) p2.y() ;
        xOfYMin = (float) p1.x() ;
    }
    else {
        yMin = (float) p2.y() ;
        yMax = (float) p1.y() ;
        xOfYMin = (float) p2.x() ;
    }
    slopeInverse = ( x2 - x1 ) / ( y2 - y1 ) ;
}

void EdgeTable::addEdge( Edge edge ) {
    edges.push_back( edge ) ;
}

int EdgeTable::getYMin() {
    int yMin = 1000 ;
    for( Edge edge : edges ) {
        if( edge.y1 < yMin ) {
            yMin = edge.y1 ;
        }
    }
    return yMin ;
}

int EdgeTable::getYMax() {
    int yMax = -1000 ;
    for( Edge edge : edges ) {
        if( edge.y2 > yMax ) {
            yMax = edge.y2 ;
        }
    }
    return yMax ;
}

std::vector<QPoint> EdgeTable::sortPoints( vector<int>& points ) {
    /*/
    for( int i = 0 ; i < points.size() ; i++ ) {
        for( int j = i ; j > 0 ; j-- ) {
            if( points[ j ].x() < points[ j - 1 ].x() ) {
                QPoint temp = points[ j ] ;
                points[ j ] = points[ j - 1 ] ;
                points[ j - 1 ] = temp ;
            }
        }
    }
    */


}

std::vector<Edge> EdgeTable::markActiveEdges( int currentY ) {
    std::vector<Edge> activeEdges ;
    for( Edge polygonEdge : edges ) {
        if ( polygonEdge.yMax >= currentY && polygonEdge.yMin <= currentY ) {
            activeEdges.push_back( polygonEdge ) ;
        }
    }
    return activeEdges ;
}

void EdgeTable::print() {
    for( Edge edge : edges ) {
        cout << edge.x1 << " " << edge.y1 << " " << edge.slopeInverse << " " << endl ;
    }
}

int EdgeTable::getIntersectionPoint( int currentY , Edge activeEdge ) {
    float x = activeEdge.xOfYMin + ( activeEdge.slopeInverse * ( currentY - activeEdge.yMin) ) ;
    return (int)x ;
}
