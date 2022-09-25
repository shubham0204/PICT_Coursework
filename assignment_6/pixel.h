#ifndef PIXEL_H
#define PIXEL_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class Pixel; }
QT_END_NAMESPACE

class Pixel : public QMainWindow
{
    Q_OBJECT

public:
    Pixel(QWidget *parent = nullptr);
    ~Pixel();

private slots:
    void on_draw_b_button_clicked();
    void on_draw_a_button_clicked();

    void plotPoint( int x , int y ) ;
    void setupDrawingArea() ;

    void drawLineDDA( int x1 , int y1 , int x2 , int y2 ) ;
    void drawBresenhamCircle( QPoint centre , float radius ) ;
    void drawTriangle( QPoint p1 , QPoint p2 , QPoint p3 ) ;
    float drawTriangleInCircle( QPoint centre , float radius ) ;
    void drawRectangle( int x , int y , int w , int h ) ;
    void drawQuadrilateral( QPoint p1 , QPoint p2 , QPoint p3 , QPoint p4 ) ;


private:
    Ui::Pixel *ui;
};
#endif // PIXEL_H
