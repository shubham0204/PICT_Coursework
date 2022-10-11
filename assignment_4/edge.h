#ifndef EDGE_H
#define EDGE_H
#include <math.h>
#include <iostream>
#include <vector>
#include <QPoint>
using namespace std ;

class Edge {

private:

    float x1 , x2 , y1 , y2 ;
    float yMin , yMax ;
    float slopeInverse ;
    bool isActive = false;

public:

    Edge( QPoint& p1 , QPoint& p2 ){
        x1 = (float)p1.x() ;
        y1 = (float)p1.y() ;
        x2 = (float)p2.x() ;
        y2 = (float)p2.y() ;
        yMin = (float)std::min( p1.y() , p2.y() ) ;
        yMax = (float)std::max( p1.y() , p2.y() ) ;
        slopeInverse = ( x2 - x1 ) / ( y2 - y1 ) ;
    }

    friend class EdgeTable ;


};

class EdgeTable {

private:
    std::vector<Edge> edges ;

public:
    void addEdge( Edge edge ) {
        edges.push_back( edge ) ;
    }

    int getYMin() {
        int yMin = 1000 ;
        for( Edge edge : edges ) {
            if( edge.y1 < yMin ) {
                yMin = edge.y1 ;
            }
        }
        return yMin ;
    }

    int getYMax() {
        int yMax = -1000 ;
        for( Edge edge : edges ) {
            if( edge.y2 > yMax ) {
                yMax = edge.y2 ;
            }
        }
        return yMax ;
    }

    std::vector<Edge> markActiveEdges( int currentY ) {
        std::vector<Edge> activeEdges ;
        for( Edge polygonEdge : edges ) {
            if ( polygonEdge.yMax >= currentY && polygonEdge.yMin <= currentY ) {
                activeEdges.push_back( polygonEdge ) ;
            }
        }
        return activeEdges ;
    }

    void print() {
        for( Edge edge : edges ) {
            cout << edge.x1 << " " << edge.y1 << " " << edge.slopeInverse << " " << endl ;
        }
    }

    QPoint getIntersectionPoint( int currentY , Edge activeEdge ) {
        std::cout << "Slope inverse " << activeEdge.slopeInverse << std::endl ;
        float x = activeEdge.x1 + ( activeEdge.slopeInverse * ( currentY - activeEdge.y1) ) ;
        return QPoint( (int)x , currentY ) ;
    }


};

#endif // EDGE_H
