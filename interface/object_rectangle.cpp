
#include "object_rectangle.h"


object_rectangle::object_rectangle() {}

object_rectangle::object_rectangle(GLfloat r_height, GLfloat r_width, GLfloat r_R, GLfloat r_G, GLfloat r_B) {
    retangle_height = r_height;
    retangle_width = r_width;
    retangle_R = r_R;
    retangle_G = r_G;
    retangle_B = r_B;
}

//RETIRADO  lab robo
void object_rectangle::DrawRectangle(){

  /* Limpar todos os pixels  */
  //glClear (GL_COLOR_BUFFER_BIT);

  /* Define cor dos vértices com os valores R, G e B variando de 0.0 a 1.0 */
  glColor3f (retangle_R, retangle_G, retangle_B);
  /* Desenhar um polígono branco (retângulo) */
    glBegin(GL_POLYGON);
    glVertex2f((retangle_width/2), 0.0 );
    glVertex2f((retangle_width/2), retangle_height );
    glVertex2f(-(retangle_width/2), retangle_height);
    glVertex2f(-(retangle_width/2),0);
    glEnd();
  
}