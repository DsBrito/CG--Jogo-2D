


#include "object_circle.h"

object_circle::object_circle(GLfloat c_r,const string &c_color) {
    circle_radius = c_r;
    
    if (strcmp(c_color.c_str(),"blue")==0) {
        circle_R = 0;
        circle_G = 0;
        circle_B = 1;
    } else if(strcmp(c_color.c_str(),"red")==0) {
        circle_R = 1;
        circle_G = 0;
        circle_B = 0;
    } else if (strcmp(c_color.c_str(),"green")==0)  {
        circle_R = 0;
        circle_G = 1;
        circle_B = 0;
    }
}

//retirada do lab robo
void object_circle::DrawCircle() const {
     //passar pra RGB
    glColor3f(circle_R,circle_G,circle_B);

    //tamanho dos pontos
    glPointSize(3.0);
    
    //desenhando o circulo em  20 graus até 360
    glBegin(GL_POLYGON); ////GL_POINST Só desenha os pontos e não perenche
        for (int i = 0; i < 18; i++){
            glVertex2f(circle_radius* cos(2*M_PI*i/18),circle_radius*sin(2*M_PI*i/18));
        }
    glEnd();
}


//circulo das mãos  (menores)
object_circle::object_circle(GLfloat c_radius, GLfloat c_R, GLfloat c_G, GLfloat c_B) {

    object_circle:: circle_radius = c_radius;
                    circle_R = c_R;
                    circle_G = c_G;
                    circle_B = c_B;
}

//object_circle::object_circle() {

//}