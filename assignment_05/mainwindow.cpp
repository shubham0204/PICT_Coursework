#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMouseEvent>
#include "line.cpp"
#include <vector>
#include <iostream>
using namespace std ;

QImage img( 800 , 500 , QImage::Format_RGB888 ) ;
bool isPointSelected ;
QPoint prevPoint ;
vector<Line> lines ;

int TOP = 8 ;
int BOTTOM = 4 ;
int RIGHT = 2 ;
int LEFT = 1 ;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui -> drawingArea -> setMouseTracking( true ) ;
    setupDrawingArea() ;
}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::mousePressEvent( QMouseEvent* event )  {
    int x = event -> pos().x() ;
    int y = event -> pos().y() ;
    int posX = ui -> drawingArea -> pos().x() ;
    int posY = ui -> drawingArea -> pos().y() ;
    if( x > posX && x < (posX + 500) && y > posY && y < ( posY + 500 ) ) {
        if( !isPointSelected ) {
            prevPoint = QPoint( x , y ) ;
            isPointSelected = true ;
        }
        else {
            drawLineDDA( prevPoint.x() , prevPoint.y() , x , y ) ;
            lines.push_back( Line( prevPoint.x() , prevPoint.y() , x , y ) ) ;
            isPointSelected = false ;
        }
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


void MainWindow::drawRect(float x, float y, float w, float h) {
    drawLineDDA( x , y , x + w , y ) ;
    drawLineDDA( x + w , y , x + w , y + h ) ;
    drawLineDDA( x + w , y + h , x , y + h ) ;
    drawLineDDA( x , y + h , x , y ) ;
}

void MainWindow::on_clip_button_clicked() {
    int x = ui -> x -> toPlainText().toInt() ;
    int y = ui -> y -> toPlainText().toInt() ;
    int w = ui -> w -> toPlainText().toInt() ;
    int h = ui -> h -> toPlainText().toInt() ;

    float x_min = ( float ) x ;
    float x_max = ( float ) x + w ;
    float y_min = ( float ) y ;
    float y_max = ( float ) y + h ;

    // Reinitialize the `img` to remove all contents
    img = QImage( 500 , 500 , QImage::Format_RGB888 ) ;
    setupDrawingArea() ;
    drawRect( x , y , w , h ) ;
    ui -> drawingArea -> setPixmap( QPixmap::fromImage( img ) ) ;

    // Iterate through each line
    for( Line line : lines ) {
        // Call this method to initialize region codes and intersection points
        line.initializePositionCodes( x_min , y_min , x_max , y_max ) ;
        int code1 = line.code1 ;
        int code2 = line.code2 ;
        if( (code1 | code2) == 0 ) {
            // Completely inside
            drawLineDDA( line.x1 , line.y1 , line.x2 , line.y2 ) ;
        }
        else {
            if( ( code1 & code2 ) == 0 ) {
                // Clipping case
                int x1 = 0 ;
                int y1 = 0 ;
                int x2 = 0 ;
                int y2 = 0 ;

                if( code1 == 0 || code2 == 0 ) {
                    // Line intersects one boundary only
                    // Determine only one intersection point
                    int codeOut ; // Code of the point that lies outside the clipping window
                    if( code1 == 0 ) {
                        // First point inside, second point inside
                        codeOut = code2 ;
                        x1 = line.x1 ;
                        y1 = line.y1 ;
                    }
                    else {
                        // Second point inside, first point outside
                        codeOut = code1 ;
                        x1 = line.x2 ;
                        y1 = line.y2 ;
                    }
                    if( (codeOut & TOP) == TOP ) {
                        // Top Boundary
                        x2 = line.x_TOP ;
                        y2 = y_max ;
                    }
                    else if( (codeOut & BOTTOM) == BOTTOM ) {
                        // Bottom
                        x2 = line.x_BOTTOM ;
                        y2 = y_min ;
                    }
                    else if( (codeOut & RIGHT) == RIGHT ) {
                        // Right
                        x2 = x_max ;
                        y2 = line.y_RIGHT ;
                    }
                    else if( (codeOut & LEFT) == LEFT ) {
                        // Left
                        x2 = x_min ;
                        y2 = line.y_LEFT ;
                    }
                }
                else {
                    // Line intersects two boundaries
                    // Determine two intersection points

                    // Determine 1st intersection point ( x1 , y1 )
                    if( (code1 & TOP) == TOP ) {
                        // Top Boundary
                        x1 = line.x_TOP ;
                        y1 = y_max ;
                    }
                    else if( (code1 & BOTTOM) == BOTTOM ) {
                        // BOttom
                        x1 = line.x_BOTTOM ;
                        y1 = y_min ;
                    }
                    else if( (code1 & RIGHT) == RIGHT ) {
                        // Right
                        x1 = x_max ;
                        y1 = line.y_RIGHT ;
                    }
                    else if( (code1 & LEFT) == LEFT ) {
                        // Left
                        x1 = x_min ;
                        y1 = line.y_LEFT ;
                    }

                    // Determine 2nd intersection point ( x2 , y2 )
                    if( (code2 & TOP) == TOP ) {
                        // Top Boundary
                        x2 = line.x_TOP ;
                        y2 = y_max ;
                    }
                    else if( (code2 & BOTTOM) == BOTTOM ) {
                        // Bottom
                        x2 = line.x_BOTTOM ;
                        y2 = y_min ;
                    }
                    else if( (code2 & RIGHT) == RIGHT ) {
                        // Right
                        x2 = x_max ;
                        y2 = line.y_RIGHT ;
                    }
                    else if( (code2 & LEFT) == LEFT ) {
                        // Left
                        x2 = x_min ;
                        y2 = line.y_LEFT ;
                    }

                }
                drawLineDDA( x1 , y1 , x2 , y2 ) ;
            }
        }
        // If line is completely outside, we'll not draw it
    }

}

void MainWindow::on_draw_button_clicked() {
    // Draw clipping window
    int x = ui -> x -> toPlainText().toInt() ;
    int y = ui -> y -> toPlainText().toInt() ;
    int w = ui -> w -> toPlainText().toInt() ;
    int h = ui -> h -> toPlainText().toInt() ;
    drawRect( x , y , w , h ) ;
}



