#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void mousePressEvent( QMouseEvent* event ) ;

    // Plot point in the drawing area
    void plotPoint( int x , int y ) ;
    // Set drawing area color to white
    void setupDrawingArea() ;


    void drawLineDDA( float x1 , float y1 , float x2 , float y2 ) ;



private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
