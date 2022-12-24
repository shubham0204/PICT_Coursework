#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPoint>
#include <cmath>
using namespace std ;

QImage img( 500 , 500 , QImage::Format_RGB888 ) ;
int x_1 , y_1 , x_2 , y_2 ;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);
    setupDrawingArea() ;

    drawAxes() ;
}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::drawAxes() {
    drawLineDDA( 250 , 0 , 250 , 500 ) ;
    drawLineDDA( 0 , 250 , 500 , 250 ) ;
}


// Plot the given point in the drawing area
void MainWindow::plotPoint( int x , int y ) {
    img.setPixel( x , y , qRgb( 0 , 0 , 0 ) ) ;
}

// Plot the given point in the drawing area
void MainWindow::plotPointTranslate( int x , int y ) {
    img.setPixel( x + 250 , -y + 250 , qRgb( 0 , 0 , 0 ) ) ;
}

// Set color of all pixels in drawing area to WHITE
void MainWindow::setupDrawingArea() {
    img.fill( Qt::white ) ;
    ui -> drawingArea -> setPixmap( QPixmap::fromImage( img ) ) ;
}

void MainWindow::drawLineDDA( float x1 , float y1 , float x2 , float y2 ) {
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

void MainWindow::drawLineDDATranslate(float x1, float y1, float x2, float y2) {
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
    plotPointTranslate( x1 , y1 ) ;
    for( int i = 0 ; i < step ; i++ ){
        plotPointTranslate( x , y ) ;
        x = x + x_inc ;
        y = y + y_inc ;
    }
    ui -> drawingArea -> setPixmap( QPixmap::fromImage( img ) ) ;
}

QPoint MainWindow::transformScale(float x, float y, float sx, float sy) {
    return QPoint( x * sx , y * sy ) ;
}

QPoint MainWindow::transformTranslate(float x, float y, float tx, float ty) {
    return QPoint( x + tx , y + ty ) ;
}

QPoint MainWindow::transformRotate(float x, float y, float thetaDegrees) {
    float rad = (thetaDegrees * 3.14) / 180 ;
    float x_ = (x * cos( rad )) - (y * sin( rad )) ;
    float y_ = (x * sin( rad )) + (y * cos( rad )) ;
    return QPoint( x_ , y_ ) ;
}

void MainWindow::on_draw_clicked() {
    x_1 = ui -> x1 -> text().toInt() ;
    y_1 = ui -> y1 -> text().toInt() ;
    x_2 = ui -> x2 -> text().toInt() ;
    y_2 = ui -> y2 -> text().toInt() ;

    drawLineDDATranslate( x_1 , y_1 , x_2 , y_2 ) ;

}

void MainWindow::on_scale_clicked(){
    float sx = ui -> sx -> text().toFloat() ;
    float sy = ui -> sy -> text().toFloat() ;

    // Reset
    img = QImage( 500 , 500 , QImage::Format_RGB888 ) ;
    setupDrawingArea() ;
    drawAxes() ;

    QPoint scaled1 = transformScale( x_1 , y_1 , sx , sy ) ;
    QPoint scaled2 = transformScale( x_2 , y_2 , sx , sy ) ;
    x_1 = scaled1.x() ;
    y_1 = scaled1.y() ;
    x_2 = scaled2.x() ;
    y_2 = scaled2.y() ;
    drawLineDDATranslate( x_1 , y_1 , x_2 , y_2 ) ;
}

void MainWindow::on_translate_clicked(){
    float tx = ui -> tx -> text().toFloat() ;
    float ty = ui -> ty -> text().toFloat() ;

    img = QImage( 500 , 500 , QImage::Format_RGB888 ) ;
    setupDrawingArea() ;
    drawAxes();

    QPoint translate1 = transformTranslate( x_1 , y_1 , tx , ty ) ;
    QPoint translate2 = transformTranslate( x_2 , y_2 , tx , ty ) ;
    x_1 = translate1.x() ;
    y_1 = translate1.y() ;
    x_2 = translate2.x() ;
    y_2 = translate2.y() ;
    drawLineDDATranslate( x_1 , y_1 , x_2 , y_2 ) ;
}

void MainWindow::on_rotate_clicked(){
    float theta = ui -> theta -> text().toFloat() ;

    img = QImage( 500 , 500 , QImage::Format_RGB888 ) ;
    setupDrawingArea() ;
    drawAxesy_1();

    QPoint rotate1 = transformRotate( x_1 , y_1 , theta ) ;
    QPoint rotate2 = transformRotate( x_2 , y_2 , theta ) ;
    x_1 = rotate1.x() ;
    y_1 = rotate1.y() ;
    x_2 = rotate2.x() ;
    y_2 = rotate2.y() ;
    drawLineDDATranslate( x_1 , y_1 , x_2 , y_2 ) ;
}
