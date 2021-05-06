#include <GL/glut.h>

GLchar *TITLE = "Lucas Camilo de Morais";

GLfloat angle, fAspect;

GLint xAngle = 0, yAngle = 0;

GLdouble base = 3, height = 7;
GLint slices = 50,
      stacks = 15;

void draw(void){
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(1.0f, 1.0f, 1.0f);

    glRotatef(xAngle, 0, 1, 0);
	glRotatef(yAngle, -1, 0, 0);

    glutWireCone(base,height,slices,stacks);

	glutSwapBuffers();
}

void setInitialConfig (void){ 
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    angle=5;
}

void adjustVisualizationConfig(void){
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(angle,fAspect,0.1,700);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(0,80,200, 0,0,0, 0,1,0);
}

void resizeWindow(GLsizei w, GLsizei h){
	h = h ==0? 1:h;

	glViewport(0, 0, w, h);

	fAspect = (GLfloat) w / h;

	adjustVisualizationConfig();
}
void zoom(GLint button, GLint state, GLint x, GLint y){
    if (button == 3 && angle >= 10){
        angle -= 5;
    }
	else if (button == 4 && angle <= 170){
        angle += 5;
    }
}


void rotate(GLint x, GLint y){
	xAngle = x;
    yAngle = y;

	adjustVisualizationConfig();
	glutPostRedisplay();
}

void mouseActionsHandler(GLint button, GLint state, GLint x, GLint y){
    zoom(button,state,x,y);

    adjustVisualizationConfig();
	glutPostRedisplay();
}

int main(GLint argc, GLchar** argv){
    glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(350,300);
	glutCreateWindow(TITLE);
	glutDisplayFunc(draw);
	glutReshapeFunc(resizeWindow);
	glutMouseFunc(mouseActionsHandler);
	glutMotionFunc(rotate);
	setInitialConfig();
	glutMainLoop();
}