#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPoint>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void setupDrawingArea() ;
    void plotPoint( int x , int y ) ;
    void plotPointTranslate( int x , int y ) ;
    void drawLineDDA( float x1 , float y1 , float x2 , float y2 ) ;
    void drawLineDDATranslate( float x1 , float y1 , float x2 , float y2 ) ;
    void drawAxes() ;

    QPoint transformScale( float x , float y , float sx , float sy ) ;
    QPoint transformTranslate( float x , float y , float tx , float ty ) ;
    QPoint transformRotate( float x , float y , float thetaDegrees ) ;


private slots:
    void on_draw_clicked();
    void on_scale_clicked();
    void on_translate_clicked();
    void on_rotate_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
