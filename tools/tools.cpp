#include "tools.h"


using namespace std;

double Tools::DistanceTools(GLfloat _xTools, GLfloat _yTools, GLfloat x_Tools, GLfloat y_Tools){
    return sqrt(pow(_xTools - x_Tools, 2) + pow(_yTools - y_Tools, 2));

}
double Tools::MagnitudeTools(GLfloat _xTools, GLfloat _yTools){
    return sqrt(pow(_xTools, 2) + pow(_yTools, 2));

}

void Tools::TranslateTools(GLfloat &_xTools, GLfloat &_yTools, GLfloat _tTollsX, GLfloat _tTollsY) {
    _xTools += _tTollsX;
    _yTools += _tTollsY;
}

double Tools::DegressToRadiansTools(GLfloat degress) {
    return degress * (M_PI / 180);
}
double Tools::RadiansToDegressTools(GLfloat radians) {
    return radians * (180 / M_PI);
}

void Tools::RotateTools(GLfloat &_xTools, GLfloat &_yTools, GLfloat degress) {
    double radians = DegressToRadiansTools(degress);
    GLfloat timeX = _xTools;
    GLfloat timeY = _yTools;

    _xTools = timeX * cos(radians) - timeY * sin(radians);
    _yTools = timeX * sin(radians) + timeY * cos(radians);
}

void Tools::FixHandTools(GLfloat &gX_head,GLfloat &gY_head,GLfloat &gTheta_Head,GLfloat &newHandX,GLfloat &newHandY,GLfloat &d_HandX,GLfloat &d_HandY,GLfloat &d_ForearmX,GLfloat &d_ArmX,GLfloat &d_ArmY,GLfloat &d_ForearmY,GLfloat &d_ForearmAngle,GLfloat &d_ArmAngle,GLfloat &d_ForearmRotation,GLfloat &d_ArmRotation){
    TranslateTools(newHandX, newHandY, d_HandX, d_HandY);
    RotateTools(newHandX, newHandY, d_ForearmAngle + d_ForearmRotation);
    TranslateTools(newHandX, newHandY, d_ForearmX, d_ForearmY);

    RotateTools(newHandX, newHandY, d_ArmAngle + d_ArmRotation);
    TranslateTools(newHandX, newHandY, d_ArmX, d_ArmY);

    RotateTools(newHandX, newHandY, gTheta_Head);
    TranslateTools(newHandX, newHandY, gX_head, gY_head);
}

void Tools::CircleTraceTools(GLfloat p_radius){
    double inc = 2 * M_PI / 36;
    glBegin(GL_LINES);
    glColor3f(0, 0, 0);
    for (int i = 0; i < 36; i++) {
        glVertex3f(p_radius * cos(inc * i), p_radius * sin(inc * i), 0);
    }
    glEnd();

}



 void Tools:: trTools(GLfloat &d_X,GLfloat &d_Y, GLfloat &d_Angle, GLfloat &d_Rotation){
    
    glTranslatef(d_X, d_Y, 0);
    glRotatef(d_Angle+ d_Rotation, 0, 0, 1);
  
 }

void Tools::tTools(GLfloat &d_X, GLfloat &d_Y){
    glTranslatef(d_X, d_Y, 0);
}