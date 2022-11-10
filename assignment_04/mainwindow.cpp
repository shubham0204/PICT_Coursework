#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <iostream>
#include <vector>
#include <string>
#include <QMouseEvent>
#include <QTimer>
#include "edge.h"
using namespace std ;

QImage img( 500 , 500 , QImage::Format_RGB888 ) ;
vector<QPoint> vertices ;
int numPolygonVertices ;
bool isUserDrawing = false ;
EdgeTable edgeTable;

QPoint initialPoint ;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui -> drawingArea -> setMouseTracking( true ) ;
    setupDrawingArea() ;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mousePressEvent( QMouseEvent* event )  {
    if( !isUserDrawing ) {
        return ;
    }
    int x = event -> pos().x() ;
    int y = event -> pos().y() ;
    int posX = ui -> drawingArea -> pos().x() ;
    int posY = ui -> drawingArea -> pos().y() ;
    if( x > posX && x < (posX + 500) && y > posY && y < ( posY + 500 ) ) {
        // Clicked inside the drawing area
        vertices.push_back( QPoint( x , y ) ) ;
        if( vertices.size() >= 2 ) {
            drawLineDDA( vertices[ vertices.size() - 1 ] , vertices[ vertices.size() - 2 ] ) ;
        }
        if( vertices.size() >= numPolygonVertices ){
            drawLineDDA( vertices[ vertices.size() - 1 ] , vertices[ 0 ] ) ;
            isUserDrawing = false ;
            ui -> startFillButton -> setEnabled( true ) ;
        }
    }
}


void MainWindow::on_startFillButton_clicked() {
    fillEdgeTable() ;
    fillPolygon() ;
}

void MainWindow::on_startButton_clicked() {
    int vertices = ui -> numVerticesSelector -> value() ;
    if( vertices > 2 ) {
        numPolygonVertices = vertices ;
        setupDrawingArea() ;
        isUserDrawing = true ;
    }
}

void MainWindow::fillPolygon() {
    for( int y = edgeTable.getYMin() ; y <= edgeTable.getYMax() ; y++ ) {
        vector<Edge> activeEdges = edgeTable.markActiveEdges( y ) ;
        vector<int> intersectionPoints ;
        for( Edge activeEdge : activeEdges ) {
            intersectionPoints.push_back( edgeTable.getIntersectionPoint( y , activeEdge ) ) ;
        }
        sort( intersectionPoints.begin() , intersectionPoints.end() ) ;
        if( intersectionPoints.size() % 2 == 0 ) {
            int i = 0;
            while( i < intersectionPoints.size() ) {
                QPoint p1( intersectionPoints[i] , y ) ;
                QPoint p2( intersectionPoints[i+1] , y ) ;
                drawLineDDA( p1 , p2 , 255 , 0 , 0 ) ;
                i += 2 ;
            }
        }
        else {
            int size = intersectionPoints.size() ;
            int i = 0 ;
            int end = size ;
            if( intersectionPoints[0] == intersectionPoints[1] ) {
                i = 1 ;
            }
            else if( intersectionPoints[size-1] == intersectionPoints[size-2] ) {
                end = size - 1 ;
            }
            while( i < end ) {
                QPoint p1( intersectionPoints[i] , y ) ;
                QPoint p2( intersectionPoints[i+1] , y ) ;
                drawLineDDA( p1 , p2 , 255 , 0 , 0 ) ;
                i += 2 ;
            }
        }
    }
    ui -> drawingArea -> setPixmap( QPixmap::fromImage( img ) ) ;
}

void MainWindow::delay( QPoint p1 , QPoint p2 ) {
    QTimer::singleShot( 1000 , [this, p1, p2]() { drawLineDDA( p1 , p2 , 255 , 0 , 0 ) ; } );
}

void MainWindow::fillEdgeTable() {
    for( int i = 0 ; i < vertices.size() - 1 ; i++ ) {
        edgeTable.addEdge( Edge( vertices[ i ] , vertices[ i + 1 ] ) ) ;
    }
    edgeTable.addEdge( Edge( vertices[ vertices.size() - 1 ] , vertices[ 0 ] )) ;
    edgeTable.print() ;
}

void MainWindow::drawPolygon( vector<QPoint> points ) {
    QPoint prevPoint = initialPoint ;
    for( QPoint vertex : points ) {
        drawLineDDA( prevPoint , vertex ) ;
        prevPoint = vertex ;
    }
    drawLineDDA( prevPoint , initialPoint ) ;
    ui -> drawingArea -> setPixmap( QPixmap::fromImage( img ) ) ;
}


void MainWindow::drawLineDDA( QPoint p1 , QPoint p2 , int r , int g , int b ) {
    float x1 , x2 , y1 , y2 ;
    x1 = p1.x() ;
    y1 = p1.y() ;
    x2 = p2.x() ;
    y2 = p2.y() ;
    float dx = x2 - x1 ;
    float dy = y2 - y1 ;
    float step ;
    if( abs( dx ) > abs( dy ) ) {
        step = abs(dx) ;
    }
    else {
        step = abs(dy) ;
    }
    float x_inc = dx / step ;
    float y_inc = dy / step ;
    float x = x1 ;
    float y = y1 ;
    plotPoint( x1 , y1 , r , g , b ) ;
    for( int i = 0 ; i < step ; i++ ){
        plotPoint( x , y , r , g , b ) ;
        x = x + x_inc ;
        y = y + y_inc ;
    }
    ui -> drawingArea -> setPixmap( QPixmap::fromImage( img ) ) ;
}

// Plot the given point in the drawing area
void MainWindow::plotPoint( int x , int y , int r , int g , int b ) {
    img.setPixel( x , y, qRgb( r , g , b ) ) ;
}

// Set color of all pixels in drawing area to WHITE
void MainWindow::setupDrawingArea() {
    img.fill( Qt::white ) ;
    ui -> drawingArea -> setPixmap( QPixmap::fromImage( img ) ) ;
}
