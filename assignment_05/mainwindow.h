#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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
    void drawLineDDA( float x1 , float y1 , float x2 , float y2 ) ;
    void drawRect( float x , float y , float w , float h ) ;

private slots:

    void on_clip_button_clicked();
    void on_draw_button_clicked();
    void mousePressEvent( QMouseEvent* event ) ;


private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
