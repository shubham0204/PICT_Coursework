#include "pixel.h"
#include "ui_pixel.h"
#include <cmath>
using namespace std ;

QImage img( 500 , 500 , QImage::Format_RGB888 ) ;
float COS_30 = 0.866f;
float SIN_30 = 0.5f;

Pixel::Pixel(QWidget *parent) : QMainWindow(parent), ui(new Ui::Pixel){
    ui -> setupUi(this);
}

Pixel::~Pixel(){
    delete ui;
}


void Pixel::on_draw_a_button_clicked() {
    int x = ui -> x_one -> toPlainText().toInt() ;
    int y = ui -> y_one -> toPlainText().toInt() ;
    float radius = ui -> x_two -> toPlainText().toFloat() ;
    setupDrawingArea() ;
    float triangleSideLength = drawTriangleInCircle( QPoint( x , y ) , radius ) ;
    float circleRadius = triangleSideLength / ( 2 * sqrt(3) ) ;
    drawBresenhamCircle( QPoint( x , y ) , circleRadius ) ;

    ui -> label -> setPixmap( QPixmap::fromImage( img ) ) ;
}

void Pixel::on_draw_b_button_clicked() {
    int x , y , w , h ;
    x = ui -> x_one -> toPlainText().toInt() ;
    y = ui -> y_one -> toPlainText().toInt() ;
    w = ui -> x_two -> toPlainText().toInt() ;
    h = ui -> y_two -> toPlainText().toInt() ;
    float w1 = w / 2 ;
    float h1 = h / 2 ;

    setupDrawingArea() ;
    drawRectangle( x , y , w , h ) ;
    drawQuadrilateral(
                QPoint( x + w1 , y ) ,
                QPoint( x + w , y + h1 ) ,
                QPoint( x + w1 , y + h ) ,
                QPoint( x , y + h1 )) ;
    float innerCircleRadius = ( w1 * h1 ) / sqrt( w1*w1 + h1*h1 ) ;
    drawBresenhamCircle( QPoint( x + w1 , y + h1 ) , innerCircleRadius )  ;
    ui -> label -> setPixmap( QPixmap::fromImage( img ) ) ;
}

// Plot the given point in the drawing area
void Pixel::plotPoint( int x , int y ) {
    img.setPixel( x , y, qRgb( 255 , 0 , 0 ) ) ;
}

// Set color of all pixels in drawing area to WHITE
void Pixel::setupDrawingArea() {
    img.fill( Qt::white ) ;
}

void Pixel::drawLineDDA( int x1 , int y1 , int x2 , int y2 ) {
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
}

void Pixel::drawBresenhamCircle( QPoint centre , float radius ) {
    int x_c = centre.x() ;
    int y_c = centre.y() ;
    int x = 0 ;
    int y = radius ;
    float d = 3 - ( 2 * radius ) ;
    while( x <= y ) {
        plotPoint( x + x_c , y + y_c ) ;
        plotPoint( -x + x_c , y + y_c ) ;
        plotPoint( -x + x_c , -y + y_c ) ;
        plotPoint( x + x_c , -y + y_c ) ;
        plotPoint( y + x_c , x + y_c ) ;
        plotPoint( -y + x_c , x + y_c ) ;
        plotPoint( -y + x_c , -x + y_c ) ;
        plotPoint( y + x_c , -x + y_c ) ;
        if( d < 0 ) {
            d = d + ( 4 * x ) + 6 ;
        }
        else {
            d = d + ( 4 * ( x - y ) ) + 10 ;
            y = y - 1 ;
        }
        x = x + 1 ;
    }
}

void Pixel::drawTriangle( QPoint p1 , QPoint p2 , QPoint p3 ) {
    drawLineDDA( p1.x() , p1.y() , p2.x() , p2.y() ) ;
    drawLineDDA( p2.x() , p2.y() , p3.x() , p3.y() ) ;
    drawLineDDA( p3.x() , p3.y() , p1.x() , p1.y() ) ;
}

float Pixel::drawTriangleInCircle( QPoint centre , float radius ) {
    drawBresenhamCircle( centre , radius ) ;
    int centreX = centre.x() ;
    int centreY = centre.y() ;
    QPoint topVertex = QPoint( centreX , -radius + centreY ) ;
    QPoint rightVertex = QPoint( ( radius * COS_30 ) + centreX ,
                                 ( radius * SIN_30 ) + centreY ) ;
    QPoint leftVertex = QPoint( -(radius * COS_30 ) + centreX ,
                                 ( radius * SIN_30 ) + centreY ) ;
    drawTriangle( topVertex , rightVertex , leftVertex ) ;
    float sideLength = sqrt(
                pow( ( topVertex.x() - leftVertex.x() ) , 2.0 ) +
                pow( ( topVertex.y() - leftVertex.x() ) , 2.0 )) ;
    return sideLength ;
}

void Pixel::drawQuadrilateral( QPoint p1 , QPoint p2 , QPoint p3 , QPoint p4 ) {
    drawLineDDA( p1.x() , p1.y() , p2.x() , p2.y() ) ;
    drawLineDDA( p2.x() , p2.y() , p3.x() , p3.y() ) ;
    drawLineDDA( p3.x() , p3.y() , p4.x() , p4.y() ) ;
    drawLineDDA( p4.x() , p4.y() , p1.x() , p1.y() ) ;
}

void Pixel::drawRectangle( int x , int y , int w , int h ) {
    drawLineDDA( x , y , x + w , y ) ;
    drawLineDDA( x + w , y , x + w , y + h ) ;
    drawLineDDA( x + w , y + h , x , y + h ) ;
    drawLineDDA( x , y + h , x , y ) ;
}

