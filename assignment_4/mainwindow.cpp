#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <iostream>
#include <vector>
#include <string>
#include <QMouseEvent>
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
        ui -> points_info -> setText( QString( "Inside" ) ) ;
        std::cout << numPolygonVertices << std::endl ;
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

void MainWindow::fillScanline( QPoint p1 , QPoint p2 ) {
    for( int x = p1.x() ; x <= p2.x() ; x++ ) {
        plotPoint( x , p1.y() ) ;
    }
}


void MainWindow::fillPolygon() {
    cout << "Y Min" << edgeTable.getYMin() << endl ;
    cout << "Y Max" << edgeTable.getYMax() << endl ;
    for( int y = edgeTable.getYMin() ; y < edgeTable.getYMax() ; y++ ) {
        vector<Edge> activeEdges = edgeTable.markActiveEdges( y ) ;
        // cout << "Active Edges size " << activeEdges.size() << endl ;
        vector<QPoint> intersectionPoints ;
        for( Edge activeEdge : activeEdges ) {
            intersectionPoints.push_back( edgeTable.getIntersectionPoint( y , activeEdge ) ) ;
            QPoint p = edgeTable.getIntersectionPoint( y , activeEdge ) ;
            cout << " Int x " << p.x() << endl ;
            cout << " Int y " << p.y() << endl ;
        }
        if( intersectionPoints.size() % 2 ==0 ) {
            cout << "TRUE" << endl ;
            int i = 0;
            while( i < intersectionPoints.size() ) {
                for( int x = intersectionPoints[i].x() ; x <= intersectionPoints[i+1].x() ; x++ ) {
                    plotPoint( x , y ) ;
                    cout << "Y Max reached " << y << endl ;
                }
                i += 2 ;
            }
        }
        else {
            continue;
        }
        // for( int i = 0 ; i < intersectionPoints.size() - 2 ; i += 2 ) {
            // std::cout << "Int " << intersectionPoints[i].x() << " " << intersectionPoints[i+1].x()  << endl ;
            //fillScanline( intersectionPoints[i] , intersectionPoints[i+1] ) ;
        // }
        // fillScanline( intersectionPoints[0] , intersectionPoints[1] ) ;
    }
    cout << "Y Min" << edgeTable.getYMin() << endl ;
    cout << "Y Max" << edgeTable.getYMax() << endl ;
    ui -> drawingArea -> setPixmap( QPixmap::fromImage( img ) ) ;
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


void MainWindow::drawLineDDA( QPoint p1 , QPoint p2 ) {
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
    plotPoint( x1 , y1 ) ;
    for( int i = 0 ; i < step ; i++ ){
        plotPoint( x , y ) ;
        x = x + x_inc ;
        y = y + y_inc ;
    }
    ui -> drawingArea -> setPixmap( QPixmap::fromImage( img ) ) ;
}

// Plot the given point in the drawing area
void MainWindow::plotPoint( int x , int y ) {
    img.setPixel( x , y, qRgb( 0 , 0 , 0 ) ) ;
}

// Set color of all pixels in drawing area to WHITE
void MainWindow::setupDrawingArea() {
    img.fill( Qt::white ) ;
    ui -> drawingArea -> setPixmap( QPixmap::fromImage( img ) ) ;
}





