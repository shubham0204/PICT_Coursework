#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMouseEvent>
#include <cmath>
#include <iostream>
using namespace std;

QImage img( 500 , 500 , QImage::Format_RGBA8888 ) ;
float verticesX[ 20 ] ; // Array for storing x coordinates of vertices
float verticesY[ 20 ] ; // Array for storing y coordinates of vertices
float slopes[ 20 ] ; // Array for slopes of edges
int numVerticesIndex = 0 ;
int numVertices ; // Number of vertices

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setupDrawingArea() ;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::plotPoint( int x , int y ) {
    img.setPixel( QPoint( x , y )  , qRgb( 0 , 0 , 0 ) ) ;
}

// Set drawing area color to white
void MainWindow::setupDrawingArea() {
    img.fill( Qt::white ) ;
    ui -> drawingArea -> setPixmap( QPixmap::fromImage( img ) ) ;
}

void MainWindow::drawLineDDA( float x1 , float y1 , float x2 , float y2 ) {
    float dx = x2 - x1 ;
    float dy = y2 - y1 ;
    float step = abs( dx ) ;
    if( abs(dy) > abs(dx) ) {
        step = abs(dy) ;
    }
    float xInc = dx / step ;
    float yInc = dy / step ;
    float x = x1 ;
    float y = y1 ;
    plotPoint( x , y ) ;
    for( int i = 0 ; i < step ; i++ ) {
        x += xInc ;
        y += yInc ;
        plotPoint( x , y ) ;
    }
    ui -> drawingArea -> setPixmap( QPixmap::fromImage( img ) ) ;
}

void MainWindow::mousePressEvent( QMouseEvent* event ) {
    int x = event -> pos().x() ;
    int y = event -> pos().y() ;
    if( x > 500 || y > 500 ) {
        // If mouse click occurs beyond window bounds, return
        return ;
    }
    if( event -> button() == Qt::RightButton ) {
        // Right mouse click
        verticesX[ numVerticesIndex ] = verticesX[ 0 ] ; // Append first vertex at last position to complete polygon
        verticesY[ numVerticesIndex ] = verticesY[ 0 ] ; // Append first vertex at last position to complete polygon
        drawLineDDA(
           verticesX[ numVerticesIndex - 1 ] , // Previous point/vertex
           verticesY[ numVerticesIndex - 1 ] , // Previous point/vertex
           verticesX[ 0 ] , // First/starting vertex
           verticesY[ 0 ]   // First/starting vertex
        ) ;
        numVertices = numVerticesIndex ;
    }
    else {
        // Left mouse click
        // Add vertex to an array
        verticesX[ numVerticesIndex ] = x ;
        verticesY[ numVerticesIndex ] = y ;
        if( numVerticesIndex > 0 ) {
            // This is not the first point that is clicked,
            // so draw a line connecting current point and previous point
            drawLineDDA(
               verticesX[ numVerticesIndex - 1 ] , // Previous point/vertex
               verticesY[ numVerticesIndex - 1 ] , // Previous point/vertex
                    x ,
                    y
            ) ;
        }
        numVerticesIndex++ ;
    }

}


void MainWindow::on_pushButton_clicked() {

    // From all vertices, compute smallest y-coordinate - y_min
    float y_min = 1000.0f ; // Largest value possible
    for( float y : verticesY ) {
        if( y < y_min && y != 0 ) { // y != 0 required as static array already contains zeros
            y_min = y ;
        }
    }

    // From all vertices, compute largest y-coordinate - y_max
    float y_max = 0.0f ; // Smallest value possible
    for( float y : verticesY ) {
        if( y > y_max) {
            y_max = y ;
        }
    }

    // Calculate slopes for each edge
    for( int i = 0 ; i < numVertices ; i++ ) {
        float dy = verticesY[i+1] - verticesY[i] ;
        float dx = verticesX[i+1] - verticesX[i] ;
        if( dx == 0 ) {
            slopes[ i ] = 1.0f ;
        }
        else {
            slopes[ i ] = dy / dx ;
        }
    }

    // Start scan line algorithm; Iterate from y_min to y_max
    for( int y = y_min ; y < y_max; y++ ) {
        cout << y << "\n" ;
        // Check for active edge and append x-intersection
        float x_inter[ numVertices ] ;
        int numActiveEdges = 0 ;
        for( int i = 0 ; i < numVertices ; i++ ) {
            // For each edge, calculate smaller and larger y-coordinates
            float yMinLine = std::min( verticesY[i] , verticesY[i+1] ) ;
            float yMaxLine = std::max( verticesY[i] , verticesY[i+1] ) ;
            // Check for active edge
            if( yMinLine < y && y <= yMaxLine ) {
                // Append x intersection if edge is active
                // Use: x = x1 + ( 1 / m ) * ( y - y1 )
                x_inter[ numActiveEdges ] = verticesX[ i ] + ( ( 1 / slopes[i] ) * ( y - verticesY[i] )  ) ;
                numActiveEdges++ ;
            }
        }

        // Sort x_inter with bubble sort
        for( int i = 0 ; i < numActiveEdges ; i++ ) {
            for( int j = 0 ; j < numActiveEdges - i - 1 ; j++ ) {
                if( x_inter[j] > x_inter[j+1] ) {
                    int temp = x_inter[j] ;
                    x_inter[j] = x_inter[j+1] ;
                    x_inter[j+1] = temp ;
                }
            }
        }

        // Draw lines ( fill ) with DDA
        // For ex. if x_inter = [ x1 , x2 , x3 , x4 ]
        // Fill between x1 to x2
        // and x3 to x4
        for( int i = 0 ; i < numActiveEdges ; i+=2 ) {
            drawLineDDA( x_inter[i] , y , x_inter[i+1]+1 , y ) ;
        }

    }

}






