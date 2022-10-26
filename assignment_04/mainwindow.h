#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>
using namespace std ;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void setupDrawingArea() ;
    void plotPoint( int x , int y , int = 0 , int = 0 , int = 0 ) ;
    void drawLineDDA( QPoint p1 , QPoint p2 , int = 0 , int = 0 , int = 0 ) ;
    void drawPolygon( vector<QPoint> points ) ;

    void fillPolygon() ;
    void fillEdgeTable() ;

    void delay( QPoint p1 , QPoint p2 ) ;

    void mousePressEvent( QMouseEvent* event ) ;
    void on_startButton_clicked();
    void on_startFillButton_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
