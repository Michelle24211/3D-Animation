#include <GLUT/glut.h>
GLfloat pos[] = {-2, 4, 5, 1}, amb[] = {0.3, 0.3, 0.3, 1.0};
GLfloat back_amb_diff[] = {0.4, 0.7, 0.1, 1.0};
GLfloat spe[] = {0.25, 0.25, 0.25, 1.0};
GLfloat front_amb_diff[] = {0.7, 0.5, 0.1, 1};
double tran = -4, deltatran = 0.1;
int theta = 15, deltatheta = 15;
bool flag = true;

void building(){
    glPushMatrix();
    glColor3f(0, 0.1, 0.2);
    glRotated(25, 1, 0, 0);
    glutSolidCube(0.6);
    glColor3f(0.3, 0, 0.4);
    glTranslated(0, 0, 0.4);
    glutSolidCube(0.3);
    glTranslated(0, 0.30, -0.45);
    glRotated(-90, 1, 0, 0);
    glColor3f(0.3, 0, 0);
    glutSolidCone(0.4, 0.5, 48, 96);
    glPopMatrix();
}

void idle(){
    if(flag){
        if(tran > 0)
            tran = -4;
        else
            tran = tran + deltatran;
        if(theta > 360)
            theta = 15;
        else
            theta  = theta + deltatheta;
        glutPostRedisplay();
    }
}

void wheel(){
    glPushMatrix();
    glTranslated(0, -0.2, 0.3);
    glColor3f(0.6, 0.1, 0.1);
    glutSolidSphere(0.2, 45, 96);
    glRotated(theta + 15, 0, 0, 1);
    glTranslated(0, 0.2, 0);
    glColor3f(0.3, 0.2, 0.4);
    glutSolidSphere(0.1, 45, 96);
    glTranslated(0, -0.4, 0);
    glutSolidSphere(0.1, 45, 96);
    glPopMatrix();
}


void display(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glBegin(GL_LINES);
    glColor3f(1, 1, 0);
    glVertex2i(2, -0.9);
    glVertex2i(-2, -0.9);
    glVertex2i(2, -1.7);
    glVertex2i(-2, -1.7);
    glEnd();
    
    glPushMatrix();
    glColor3f(0.4, 0.2, 0.3);
    glTranslated(0, -0.5, 0);
    glutSolidCube(0.5);
    wheel();
    glTranslated(-0.5, 0, 0);
    glColor3f(0.4, 0.2, 0.3);
    glutSolidCube(0.5);
    wheel();
    glTranslated(-0.4, -0.1, 0);
    glColor3f(0.4, 0.2, 0.3);
    glutSolidCube(0.45);
    glPopMatrix();
    
    glPushMatrix();
    glTranslated(0, 1, 0);
    glTranslated(tran, 0, 0);
    building();
    glTranslated(2, 0, 0);
    building();
    glTranslated(2, 0, 0);
    building();
    glTranslated(2, 0, 0);
    building();
    glPopMatrix();
    
    glPushMatrix();
    glTranslated(0, -2, 0);
    glTranslated(tran, 0, 0);
    building();
    glTranslated(2, 0, 0);
    building();
    glTranslated(2, 0, 0);
    building();
    glTranslated(2, 0, 0);
    building();
    glPopMatrix();
    glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y){
    switch (key) {
        case '+':
            flag = true;
            deltatheta = deltatheta + 5;
            deltatran = deltatran + 0.03;
            break;
            
        case '-':
            if(deltatheta > 5 && theta > 5){
                deltatheta = deltatheta - 5;
                deltatran = deltatran - 0.03;
            }
            else
                flag = false;
                
            break;
            
        case 'p':
            if(flag)
                flag = false;
            else
                 flag = true;
            break;
            
        case 'r':
            flag = true;
            deltatran = 0.1;
            deltatheta = 15;
            break;
            
        default:
            break;
    }
}

int main(int argc, char ** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(600,600);
    glutInitWindowPosition(200, 100);
    glutCreateWindow("Project 3");
    glClearColor(0, 0, 0, 0);
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, 1, 2 , 8);
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, front_amb_diff);
    glMaterialfv(GL_BACK, GL_AMBIENT_AND_DIFFUSE, back_amb_diff);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, spe);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 75);
    glLightfv(GL_LIGHT0, GL_AMBIENT, amb);
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslated(0,0,-5);
    glLightfv(GL_LIGHT0, GL_POSITION, pos);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutIdleFunc(idle);
    glutMainLoop();
}
