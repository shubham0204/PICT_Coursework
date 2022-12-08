#define GLUT_DISABLE_ATEXIT_HACK
#include <iostream>
#include <GL/glut.h>
#include <windows.h>
#include <cmath>
using namespace std;
float y_inc = 0.0f ;
float color_inc = 0.0f ;
bool flag_position = 0 ; // UP
bool flag_color = 0 ;

void init() {
    glClearColor( 0.0 , 0.0 , 0.0 , 1.0 ) ;
    glMatrixMode( GL_PROJECTION ) ;
    glLoadIdentity() ;
    gluOrtho2D( 0.0 , 500.0 , 0.0 , 500.0 ) ;
}

void draw_circle(float x, float y, float radius) {
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glTranslatef(x, y, 0.0f);
    int circle_points = 100;
    float angle = 2.0f * 3.1416f / circle_points;
    glBegin(GL_POLYGON);
    double angle1 = 0.0 ;
    glVertex2d(radius * cos(0.0) , radius * sin(0.0));
    for ( int i=0; i<circle_points; i++) {
        glVertex2d(radius * cos(angle1), radius *sin(angle1));
        angle1 += angle;
    }
    glEnd();
    glPopMatrix();
}


void display() {
    glClear( GL_COLOR_BUFFER_BIT ) ;

    glColor3f( 1.0f - (color_inc/200) , 0.64f + (color_inc/500) , 0.0f + (color_inc/102) ) ;
    glBegin( GL_QUADS ) ;
    glVertex2i( 0 , 0 ) ;
    glVertex2i( 0 , 500 ) ;
    glVertex2i( 500 , 500 ) ;
    glVertex2i( 500 , 0 ) ;
    glEnd() ;


    glColor3f( 1.0 , 1.0 , 0.0 ) ;
    draw_circle( y_inc * 2.5f  , 250.0f + 200.0f * sin( y_inc / 25.0f ) , 30.0f ) ;


    glFlush() ;
}

void idle() {
    glutPostRedisplay() ;

    if( flag_position == 0 ) {
        y_inc += 0.020f ;
    }
    else {
        y_inc -= 0.020f ;
    }

    if( y_inc >= 250.0f || y_inc <= 0.0f ) {
        flag_position = !flag_position ;
    }

    if( flag_color == 0 ) {
        color_inc += 0.008 ;
    }
    else {
        color_inc -= 0.008 ;
    }

    if( color_inc >= 100.0f || color_inc <= 0.0f ) {
        flag_color = !flag_color ;
    }

}


int main( int argc, char **argv ) {
    glutInit( &argc , argv ) ;
    // Initialize Window size and its position
    glutInitWindowSize( 500 , 500 );
    glutInitWindowPosition( 0 , 0 ) ;
    glutCreateWindow( "Sunrise and Sunset" );
    glutDisplayFunc( display ) ;
    glutIdleFunc( idle ) ;
    init() ;
    glutMainLoop() ;
    return 0;
}
