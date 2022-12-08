#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

    void setupDrawingArea() ;
    void plotPoint( int x , int y , int r = 255 , int g = 255 , int b = 0 ) ;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void delay( int ms ) ;

    void drawKochCurve( int x1 , int y1 , int x2 , int y2 , int iterations ) ;
    void drawLineDDA( int x1 , int y1 , int x2 , int y2 , int r = 255 , int g = 255 , int b = 0 ) ;


private slots:
    void on_draw_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
