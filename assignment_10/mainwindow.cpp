#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <cmath>
#include <iostream>
#include <QTime>
#include <QCoreApplication>
#include <QEventLoop>
using namespace std;

QImage img( 500 , 500 , QImage::Format_RGB888 ) ;
float angle = 1.0472f ;
float COS_60 = 0.5 ;
float SIN_60 = 0.866 ;


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);
    setupDrawingArea() ;
}

MainWindow::~MainWindow() {
    delete ui;
}

// Plot the given point in the drawing area
void MainWindow::plotPoint( int x , int y , int r , int g , int b ) {
    img.setPixel( x , y, qRgb( r , g , b ) ) ;
}

// Set color of all pixels in drawing area to BLACK
void MainWindow::setupDrawingArea() {
    img.fill( QColor( qRgb( 0 , 0 , 0 ) ) ) ;
    ui -> drawingArea -> setPixmap( QPixmap::fromImage( img ) ) ;
}

void MainWindow::drawLineDDA( int x1 , int y1 , int x2 , int y2 , int r , int g , int b ) {
    float dx = (float) x2 - x1 ;
    float dy = (float) y2 - y1 ;
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

void MainWindow::delay( int ms ) {
    QTime dieTime = QTime::currentTime().addMSecs( ms ) ;
    while( QTime::currentTime() < dieTime ) {
        QCoreApplication::processEvents( QEventLoop::AllEvents , 100 ) ;
    }
}


void MainWindow::drawKochCurve( int x1 , int y1 , int x2 , int y2 , int iterations ) {
    // Use section formula to find the coordinates of the point that divides line in ratio 2 : 1
    int x3 = ( 0.67 * x1 + 0.33 * x2 ) ;
    int y3 = ( 0.67 * y1 + 0.33 * y2 ) ;

    // Use section formula to find the coordinates of the point that divides line in ratio 1 : 2
    int x4 = ( 0.33 * x1 + 0.67 * x2 ) ;
    int y4 = ( 0.33 * y1 + 0.67 * y2 ) ;

    // Rotate 60 degrees about point ( x3 , y3 )
    int x = x3 + (x4 - x3) * COS_60 + ( y4 - y3 ) * SIN_60;
    int y = y3 - (x4 - x3) * SIN_60 + ( y4 - y3 ) * COS_60;

    if( iterations > 1 ) {
        drawKochCurve( x1 , y1 , x3 , y3 , iterations - 1 ) ;
        drawKochCurve( x3 , y3 , x , y , iterations - 1 ) ;
        drawKochCurve( x , y , x4 , y4 , iterations - 1 ) ;
        drawKochCurve( x4 , y4 , x2 , y2 , iterations - 1 ) ;
    }
    else {
        drawLineDDA( x1 , y1 , x3 , y3 , 255 , 255 , 0 ) ;
        drawLineDDA( x3 , y3 , x , y ) ;
        drawLineDDA( x , y , x4 , y4 ) ;
        drawLineDDA( x4 , y4 , x2 , y2 ) ;
    }
    delay( 10 ) ;
}


void MainWindow::on_draw_clicked() {
    int numIterations = ui -> numIterations -> text().toInt() ;
    drawKochCurve( 150 , 300 , 350 , 300 , numIterations ) ;
    drawKochCurve( 350 , 300 , 350 , 100 , numIterations ) ;
    drawKochCurve( 350 , 100 , 150 , 100 , numIterations ) ;
    drawKochCurve( 150 , 100 , 150 , 300 , numIterations ) ;
}

