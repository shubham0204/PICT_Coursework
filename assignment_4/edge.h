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
    float xOfYMin ;
    float yMin , yMax ;
    float slopeInverse ;

public:

    Edge( QPoint& p1 , QPoint& p2 );
    friend class EdgeTable ;

};

class EdgeTable {

private:
    std::vector<Edge> edges ;

public:

    void addEdge( Edge edge ) ;
    int getYMin() ;
    int getYMax() ;
    std::vector<Edge> markActiveEdges( int currentY ) ;
    void print() ;
    QPoint getIntersectionPoint( int currentY , Edge activeEdge ) ;

};

#endif // EDGE_H
