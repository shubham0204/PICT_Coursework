#define GLUT_DISABLE_ATEXIT_HACK
#include <iostream>
#include <GL/glut.h>
#include <GL/gl.h>
#include <windows.h>
#include <cmath>
using namespace std;

/*
Sunrise and Sunset assignment, OpenGL
By making some simple modifications, we can also implement the bouncing-ball-sine-wave assignment along with the 
controlling-ball-arrow-keys assignment.

START FROM STEP 1 ( Scroll down to main() function )

Shubham Panchal 
*/

float y_inc = 0.0f ;        // Used to change the y-coordinate of the sun
float color_inc = 0.0f ;    // Used to change the color of the sky ( background )
bool flag_position = 0 ;    // To check/change the increment/decrement of y_inc
bool flag_color = 0 ;       // To check/change the increment/decrement of color_inc

/*
Step 2A
Create the `init` function that defines an orthographic projection for 2D graphics
OpenGL works with 3D coordinates, we only need a 2D plane, so we define an ortho projection
GO TO Step 2B
*/
void init() {
    glClearColor( 0.0 , 0.0 , 0.0 , 1.0 ) ;   // Clears the color buffers and sets display color to black
                                              // The first three zeros ( 0 , 0 , 0 ) indicate values for 
                                              // r, g and b and the last 1 indicates alpha ( transparency )
                                              // channel
    glMatrixMode( GL_PROJECTION ) ;           // Select the matrix on which we'll perform further operations
                                              // We'll be working on the projection ( projection space )
                                              // and not in the model space
    gluOrtho2D( 0.0 , 500.0 , 0.0 , 500.0 ) ; // Creates a projection matrix,
                                              // which maps 0 to the left border of the viewport, 
                                              // 500 to the right, 
                                              // 500 to the bottom and 0 to the top.
                                              // The values for left, right, bottom, top, near and far define a box.
                                              // All the geometry which is inside the volume of the box is "visible" on 
                                              // the viewport. ( from StackOverflow )
}

/*
Step 3
Function to draw a circle with centre at ( x , y ) and r=radius
We'll draw a polygon that has a large number of sides, so that it can closely resemble a circle
*/
void draw_circle(float x, float y, float radius) {
    glMatrixMode(GL_MODELVIEW);                         // Switch to model space
    glPushMatrix();                                     // Push/save the current matrix
    glLoadIdentity();                                   // Load a new/blank/identity matrix
    glTranslatef(x, y, 0.0f);                           // Perform translation to ( x , y )
    int circle_points = 100;
    float angle = 2.0f * 3.1416f / circle_points;
    glBegin( GL_POLYGON );                              // Start drawing a polygon
    double angle1 = 0.0 ;
    glVertex2d(radius * cos(0.0) , radius * sin(0.0));
    for ( int i=0; i<circle_points; i++) {
        // Draw vertices of the polygon.
        glVertex2d(
            radius * cos(angle1),
            radius *sin(angle1));
        angle1 += angle;
    }
    glEnd();                                  
    glPopMatrix();                                      // Reload the matrix that we've saved
}

/*
Step 2B
The display function that is called when a paint event is requested.
Whenever an event is triggered ( for ex. by glutPostRedisplay() ) this method will be called
*/
void display() {
    glClear( GL_COLOR_BUFFER_BIT ) ;  // Resets the color buffer to what we set in `init()`

    // Draw the quadrilateral that represents the sky
    // 1. Choose a color. `color_inc` increments and decrements continuous.
    // As color_inc increases, a transition from orange to blue color is made
    glColor3f( 
        1.0f - (color_inc/200) ,
        0.64f + (color_inc/500) ,
        0.0f + (color_inc/102) ) ; 
    // 2. Start drawing a quadrilateral
    glBegin( GL_QUADS ) ;
    glVertex2i( 0 , 0 ) ;     // Vertex 1
    glVertex2i( 0 , 500 ) ;   // Vertex 2
    glVertex2i( 500 , 500 ) ; // Vertex 3
    glVertex2i( 500 , 0 ) ;   // Vertex 4
    glEnd() ;

    // Draw the sun ( filled circle )
    // 1. Choose a fill color ( yellow here )
    glColor3f( 1.0 , 1.0 , 0.0 ) ;
    // 2. Draw the circle
    draw_circle( 250.0f  , 0.0f + y_inc , 60.0f ) ;

    // Deliver the changes we've made to the screen
    glFlush() ;
}

/*
Step 4
The idle function is called so that the program can perform background processing tasks or 
continuous animation when window system events are not being received.
*/
void idle() {
    // Refresh the display ( display function will be called )
    glutPostRedisplay() ;

    // 1. 
    // If FLAG == 0, increment y_inc, else decrement y_inc
    if( flag_position == 0 ) {
        y_inc += 0.020f ;
    }
    else {
        y_inc -= 0.020f ;
    }
    // If y_inc goes outside the range [ 0 , 250 ], invert the flag_position
    if( y_inc >= 250.0f || y_inc <= 0.0f ) {
        flag_position = !flag_position ;
    }

    // 2. Repeat the process for color_inc and flag_color
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

/*
Step 1
Create the main function that initializes a window for OpenGL and
set the display function and idle function ( required only for animation )
GO TO Step 2A
*/
int main( int argc, char **argv ) {
    glutInit( &argc , argv ) ;
    glutInitWindowSize( 500 , 500 );           // Initialize Window size and its position
    glutInitWindowPosition( 0 , 0 ) ;          // Set window position
    glutCreateWindow( "sSunrise and Sunset" );  // Add Window Title
    glutDisplayFunc( display ) ;               // Set a display function
    glutIdleFunc( idle ) ;                     // Set an idle function
    init() ;                                   // Initializes Orthographic projection for 2D graphics
    glutMainLoop() ;                           // Starts the OpenGL program
    return 0;
}
