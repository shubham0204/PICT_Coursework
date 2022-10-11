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
    void plotPoint( int x , int y ) ;
    void drawLineDDA( QPoint p1 , QPoint p2 ) ;
    void drawPolygon( vector<QPoint> points ) ;
    void fillScanline( QPoint p1 , QPoint p2 ) ;

    void fillPolygon() ;
    void fillEdgeTable() ;

    void mousePressEvent( QMouseEvent* event ) ;
    void on_startButton_clicked();
    void on_startFillButton_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
