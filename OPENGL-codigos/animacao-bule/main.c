#include <GL/glut.h>
#include <stdio.h>

// run on terminal:
// gcc main.c -o main -lglut -lGL -lGLU -lm 
// ./main
 
// rotation 
static GLfloat angulo = 0.0;
 
// func init 
int init(void){
 
    // set background color
    glClearColor(1.0, 1.0, 1.0, 0.0); 
    // depth test enable   
    glEnable(GL_DEPTH_TEST);            
    // load projection matrix to create crop window and view port
    glMatrixMode(GL_PROJECTION); 
    // load the identity matrix        
    glLoadIdentity();                    
    // def view port
    gluOrtho2D(-1.5, 1.72, -1.5, 1.5);  
}
 
// create new view port projection 
void newViewPortProjection(int xvmin, int yvmin, int nviewport){ 
    // def view port
    glViewport(xvmin, yvmin, 400, 400); 
    // to orthogonal projections
    glMatrixMode(GL_PROJECTION); 
    // loading the identity matrix for the new operation        
    glLoadIdentity();
    // if the number of viewport == 4
    if(nviewport == 4){ 
        // perspective projection
        gluPerspective(70, 1.0, 1.0, 50);   
    } else { 
        // else create orthogonal projection
        glOrtho(-3, 3, -3, 3, 1, 50);       
    }
}
 
// def the camera position
void cameraPosition(float x0, float y0, float z0, float vx, float vy, float vz, int nviewport){
    glMatrixMode(GL_MODELVIEW); 
    // loading the identity matrix for the new operation   
    glLoadIdentity(); 
    gluLookAt( x0,  y0,  z0,    // camera position
              0.0, 0.0, 0.0,    // camera pointing to the origin
               vx,  vy,  vz);   /// axis - x, y, z - of camera view
 
    
    float sizeTea = 2.0;

    if(nviewport == 4){
        glLoadIdentity();
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
 
        // type conversion float to integer
        float floatValue = angulo;
        int integerValue = floatValue;
        int graus = integerValue % 365;
 
        /// rotating 45 degrees on z axis
        glRotatef(angulo, 0.0, 0.0, 1.0); 
        /// rotating 45 degrees on x axis
        glRotatef(graus, 1.0, 0.0, 0.0);
        // size of bule
        sizeTea = 0.6;
    }
 
    // show bule
    glutWireTeapot(sizeTea);
}

void anguloRotacao(void){
   angulo = angulo + 0.4;
   if (angulo > 360.0)
      angulo = 0;

   glutPostRedisplay();
}

void createViewPort(){ 
    // upper left
    newViewPortProjection(000, 400, 1); 
    // camera position viewport number 1
    cameraPosition(0.0, 1.0, 0.0, 0.0, 0.0, -1.0, 1); 
    // upperright
    newViewPortProjection(400, 400, 2); 
    // camera position viewport number 2
    cameraPosition(1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 2); 
    // bottom left
    newViewPortProjection(000, 000, 3);  
    // camera position viewport number 3    
    cameraPosition(0.0, 0.0, 1.0, 0.0, 1.0, 0.0, 3); 
    // bottom right
    newViewPortProjection(400, 000, 4); 
    // camera position viewport number 4
    cameraPosition(1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 4);
}
// display func
void display(void){
    // set backgound and clear windown
    glClear(GL_COLOR_BUFFER_BIT |  GL_DEPTH_BUFFER_BIT); 
    // load model matrix
    glMatrixMode(GL_MODELVIEW); 
    // load indentity to new op
    glLoadIdentity();
 
    // golden color
    glColor3f(1.0f, 0.1f, 0.0f); 
    // create 4 viewports
    createViewPort();
    glFlush();
}
 
// main
int main(int argc, char** argv) {
    // start GLUT
    glutInit(&argc,argv); 
    // confs of display mode
    glutInitDisplayMode(GLUT_SINGLE| GLUT_RGB); 
    // set the width and height of the viewport
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(200, 200); 
    // create view port
    glutCreateWindow("Teapot In OpenGL by Soratto R.");
 
    // angle
    glutIdleFunc(anguloRotacao); 
    // set the display function to the display callback function.
    glutDisplayFunc(display);
    // func init
    init();
    // show all and wait
    glutMainLoop(); 

    return 0;
}