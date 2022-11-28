


#include <GL/glut.h>
#include "object_player.h"

using namespace std;

//colide quando o nariz de um jogador encosta na barreira do outro jogador
void object_player :: FixPlayerCollision(GLfloat &incX, GLfloat &incY, object_player &player, GLdouble state) const{
   
//calcula colisão do jogador
    GLfloat normalX;
    GLfloat normalY;
    double calculation;

    bool collision=Tools::DistanceTools(gX_head + incX, gY_head + incY, player.getHeadX(), player.getHeadY()) <= getBarrier() + player.getRadius();
    if (collision) {
        GLfloat normalX = getHeadX() - player.getHeadX();
        GLfloat normalY = getHeadY() - player.getHeadY();
        double calculation = Tools::MagnitudeTools(normalX, normalY);

        normalX /= calculation;
        normalY /= calculation;

        //linear velocidade = 0.5
        incX += state * LINEAR_VELOCITY * normalX;
        incY += state * LINEAR_VELOCITY * normalY;
       // cout<< "players collided in x: "<< normalX <<  "and y: " << normalY << endl;
    }

}

bool object_player ::IfRightHandCollision(object_player &player){


    GLfloat newHandX = 0;
    GLfloat newHandY = 0;
    
    Tools:: FixHandTools(gX_head, gY_head, gTheta_Head, newHandX, newHandY, gX_rightHand, gY_rightHand, gX_rightForearm, gX_rightArm, gY_rightArm, gY_rightForearm, gTheta_rightForearm, gTheta_rightArmAngle, gRotation_rightForearm, gRotation_rightArm);
    
    setRightGripX(newHandX);
    setRightGripY(newHandY);
    
    return Tools::DistanceTools(player.gX_head, player.gY_head, gX_rightGrip, gX_rightGrip) < getHandSize() + player.getRadius();
}

bool object_player :: IfLeftHandCollision(object_player &player){
  
    GLfloat newHandX = 0;
    GLfloat newHandY = 0;
    
    Tools:: FixHandTools(gX_head, gY_head, gTheta_Head, newHandX, newHandY, gX_leftHand, gY_leftHand, gX_leftForearm, gX_leftArm, gY_leftArm, gY_leftForearm, gTheta_leftForearm, gTheta_leftArmAngle, gRotation_leftForearm, gRotation_leftArm);
 
    setLeftGripX(newHandX);
    setLeftGripY(newHandY);
  
    //return Tools::DistanceTools(player.gX_head, player.gY_head, gX_leftGrip, gY_leftGrip) < getHandSize() + player.getRadius();
    return Tools::DistanceTools(player.gX_head, player.gY_head, newHandX, newHandY) < getHandSize() + player.getRadius();
}

/*
bool object_player::getLeftHandCollision(object_player &player) {
   // getLeftHandPosition();
       GLfloat handX = 0;
    GLfloat handY = 0;
    Tools::TranslateTools(handX, handY, gX_leftHand, gY_leftHand);

    Tools::RotateTools(handX, handY, gTheta_leftForearm + gRotation_leftForearm);
    Tools::TranslateTools(handX, handY, gX_leftForearm, gY_leftForearm);

    Tools::RotateTools(handX, handY, gTheta_leftArmAngle + gRotation_leftArm);
    Tools::TranslateTools(handX, handY, gX_leftArm, gY_leftArm);

    Tools::RotateTools(handX, handY, gTheta_Head);
    Tools::TranslateTools(handX, handY, gX_head, gY_head);

    gX_leftGrip = handX;
    gY_leftGrip = handY;
    return Tools::DistanceTools(player.gX_head, player.gY_head, handX, handY) < getHandSize() + player.getRadius();

}
void  object_player:: getLeftHandPosition(){

}

void  object_player:: getRightHandPosition(){
    GLfloat handX = 0;
    GLfloat handY = 0;
    Tools::TranslateTools(handX, handY, gX_rightHand, gY_rightHand);

    Tools::RotateTools(handX, handY, gTheta_rightForearm + gRotation_rightForearm);
    Tools::TranslateTools(handX, handY, gX_rightForearm, gY_rightForearm);

    Tools::RotateTools(handX, handY, gTheta_rightArmAngle + gRotation_rightArm);
    Tools::TranslateTools(handX, handY, gX_rightArm, gY_rightArm);

    Tools::RotateTools(handX, handY, gTheta_Head);
    Tools::TranslateTools(handX, handY, gX_head, gY_head);

    gX_rightGrip = handX;
    gY_rightGrip = handY;
}

bool object_player::getRightHandCollision(object_player &player) {
    getLeftHandPosition();

    return Tools::DistanceTools(player.gX_head, player.gY_head, gX_rightGrip, gX_rightGrip) < getHandSize() + player.getRadius();

}

*/


//entre o joador e a arena
void  object_player ::FixArenaCollision(object_arena &FightField, GLfloat &incX, GLfloat &incY) const{
    if (getHeadX() + incX + getRadius() >= FightField.arena_x + FightField.arena_width || getHeadX() + incX - getRadius() <= FightField.arena_x) {
        incX = 0;
    }
    if (getHeadY() + incY + getRadius() >= FightField.arena_y + FightField.arena_height || getHeadY() + incY - getRadius() <= FightField.arena_y) {
        incY = 0;
    }
}

void  object_player :: DrawObjects(GLfloat p_radius,  const string &p_color){
//circulos    
    circle_head = new object_circle(p_radius,p_color);    //cabeça
    circle_nose = new object_circle(p_radius * 0.2, p_color);    //nariz
    circle_leftHand = new object_circle(p_radius * 0.4, 1,0,1); //mao esquerda
    circle_rightHand = new object_circle(p_radius * 0.4, 1, 0, 1); //mao direita

//retangulos
    recltangle_leftArm = new object_rectangle(p_radius * 2.2, p_radius * 0.25, 0, 0, 0);  //braço esquerdo
    recltangle_rightArm = new object_rectangle(p_radius * 2.2, p_radius * 0.25, 0, 0, 0); //braço direiro
    rectangle_leftForearm = new object_rectangle(p_radius * 2, p_radius * 0.25, 0, 0, 0); //antebraço esquerdo
    rectangle_rightForearm = new object_rectangle(p_radius * 2, p_radius * 0.25, 0, 0, 0);//antebraço direito
}

//iniciação dos jogadores
void object_player:: ReadPlayer(GLfloat p_x, GLfloat p_y, GLfloat p_theta, GLfloat p_radius, const string &color){

//cabeça   
    gX_head = p_x;
    gY_head = p_y;
    gTheta_Head = p_theta;

//nariz
    gX_nose = p_radius * 1.01;
    gY_nose = 0;

//mãos
    gX_leftHand = 0;
    gY_leftHand = p_radius * 2;
    gX_rightHand = 0;
    gY_rightHand = p_radius * 2;

//braço
    gX_leftArm = 0;
    gY_leftArm = +p_radius;
    gTheta_leftArmAngle = +30;
    gRotation_leftArm = 0;

    gX_rightArm = 0;
    gY_rightArm = -p_radius;
    gTheta_rightArmAngle = 150;
    gRotation_rightArm = 0;

//punho (vai ser setado na colisão)

//antebraço
    gX_leftForearm = 0;
    gY_leftForearm = p_radius * 2.2;
    gTheta_leftForearm = -110;
    gRotation_leftForearm = 0;

    gX_rightForearm = 0;
    gY_rightForearm = p_radius * 2.2;
    gTheta_rightForearm = +110;
    gRotation_rightForearm = 0;
//placar
    points =0;
    DrawObjects( p_radius,color);


}

void object_player::FixVelAngular(GLdouble state) {
    gTheta_Head += state * 0.2; //velocidade angular
}

//desenhos 

//Area do jogo
void object_player ::DrawGameArea(){
    
    glPushMatrix();

    GLfloat d_Rotation =0;
    Tools::trTools(gX_head, gY_head,gTheta_Head, d_Rotation);


    DrawPlayerHeadCommand();
    DrawPlayerNose();

    DrawPlayerLeftArm();
    DrawPlayerRightArm();

    DrawGameBarrier();

    glPopMatrix(); 
}
    
void  object_player ::DrawGameBarrier() const{
    glPushMatrix();
    Tools::CircleTraceTools( getRadius() * 2);
    glPopMatrix();

}
    
//comandos de desenho
void object_player::DrawPlayerHeadCommand() {
    circle_head->DrawCircle();
}
void object_player::DrawPlayerNoseCommand() {
    circle_nose->DrawCircle();
}
void object_player::DrawRightArmCommand() {
    recltangle_rightArm->DrawRectangle();
}
void object_player::DrawRightForearmCommand() {
    rectangle_rightForearm->DrawRectangle();
}
void object_player::DrawRightHandCommand() {
    circle_rightHand->DrawCircle();
}
void object_player::DrawLeftArmCommand() {
    recltangle_leftArm->DrawRectangle();
}
void object_player::DrawLeftForearmCommand() {
    rectangle_leftForearm->DrawRectangle();
}
void object_player::DrawLeftHandCommand() {
    circle_leftHand->DrawCircle();
}
//jogador

void object_player::DrawPlayerNose() {
    glPushMatrix();

   Tools::tTools(gX_nose, gY_nose);

    DrawPlayerNoseCommand();

    glPopMatrix();
}          
void object_player::DrawPlayerRightArm() {
    glPushMatrix();

    Tools::trTools(gX_rightArm,gY_rightArm, gTheta_rightArmAngle, gRotation_rightArm);
    DrawRightArmCommand();



   Tools::trTools(gX_rightForearm,gY_rightForearm, gTheta_rightForearm, gRotation_rightForearm);
    DrawRightForearmCommand();

   Tools::tTools(gX_rightHand, gY_rightHand);
    DrawRightHandCommand();

    glPopMatrix();
}
void object_player::DrawPlayerLeftArm() {
    glPushMatrix();

   Tools::trTools(gX_leftArm,gY_leftArm, gTheta_leftArmAngle, gRotation_leftArm);


    DrawLeftArmCommand();
   Tools::trTools(gX_leftForearm,gY_leftForearm, gTheta_leftForearm, gRotation_leftForearm);


    DrawLeftForearmCommand();

    Tools::tTools(gX_leftHand, gY_leftHand);
    circle_leftHand->DrawCircle();

/*

    
*/
    glPopMatrix();
}
//placar
void object_player:: DrawPlayerPoints(GLfloat p_x, GLfloat p_y,object_player &p_One,object_player &p_Two){
    static char string[1000];
    void *latterFont = GLUT_BITMAP_TIMES_ROMAN_24;
    glColor3f(1, 1, 1);
    //Cria a string a ser impressa
    char *pString;
    sprintf(string, "PlayerOne: %d                                                     PlayerTwo: %d", p_One.getPlayerPoints(), p_Two.getPlayerPoints());
    //Define a posicao onde vai comecar a imprimir
    glRasterPos2f(p_x, p_y);
    //Imprime um caractere por vez
    pString = string;
    while (*pString) {
        glutBitmapCharacter(latterFont, *pString);
        pString++;
    }    
}
void  object_player::DrawPlayerGameOver(GLfloat x, GLfloat y, object_player &player) {
    static char string[1000];
    void *latterFont = GLUT_BITMAP_TIMES_ROMAN_24;
    glColor3f(1, 1, 1);
    //Cria a string a ser impressa
    char *pString;
    if(player.getPlayerPoints() >= 10) {
        sprintf(string, "YOU WIN");
    } else {
        sprintf(string, "YOU LOST HAHAHA");
    }
    //Define a posicao onde vai comecar a imprimir
    glRasterPos2f(x, y);
    //Imprime um caractere por vez
    pString = string;
    while (*pString ) {
        glutBitmapCharacter(latterFont, *pString);
        pString++;
    }

}
//ações do jogador no ringue de luta
void object_player::FixWalk(GLdouble state, object_player &player, object_arena &FightField){
    GLfloat incX = (state * 0.5 * cos(Tools::DegressToRadiansTools(gTheta_Head)));
    GLfloat incY = (state * 0.5 * sin(Tools::DegressToRadiansTools(gTheta_Head)));
    if(state >0){ 
        FixPlayerCollision( incX, incY, player, state);
    }
    else{
        FixPlayerCollision( incX, incY, player, -state);
    }
 
    FixArenaCollision(FightField, incX, incY);
    gX_head += incX;
    gY_head += incY;

}
    
    

//voltar aqui
void  object_player::FixPunch(GLdouble state, object_mouse &mouse, object_arena &FightField, object_player &player){
    GLfloat arenaWidthPercent = (FightField.arena_width / 2);
    GLfloat mousePercent = (mouse.mouse_movedX - mouse.mouse_clickX);
    GLfloat rotationPlayerPercent = mousePercent / arenaWidthPercent;
    GLfloat rotArm = 130 * rotationPlayerPercent;
    GLfloat rotForearm = -45 * rotationPlayerPercent;
    GLfloat stateArm =  0.8 * state;
    GLfloat stateForearm = 0.8 * state;

    //gRotation_rightArm e gRotation_rightForearm
    if (mouse.mouse_button == 0 && mouse.mouse_state == 0 && mouse.mouse_movedX - mouse.mouse_clickX <= FightField.arena_width / 2) {
        if(rotArm >=0)
            gRotation_rightArm = rotArm; 
        if(rotArm <0)
            gRotation_rightArm =0;

        if( rotForearm<= 0)
            gRotation_rightForearm = rotForearm;
        if(rotForearm >=0)
            gRotation_rightForearm =0;
    }

    //rotArm e gRotation_leftForearm
    if (mouse.mouse_button == 0 && mouse.mouse_state == 0 && -(mouse.mouse_movedX - mouse.mouse_clickX) <= FightField.arena_width / 2) {
        if( rotArm <= 0)
            gRotation_leftArm = rotArm;
        if (rotArm > 0)
            gRotation_leftArm = 0;

        if (rotForearm >= 0)
            gRotation_leftForearm =rotForearm; 
        if(rotForearm <0)
            gRotation_leftForearm = 0;
    }

    //gRotation_rightArm
    if (mouse.mouse_state == 1 && (gRotation_rightArm > 0 || gRotation_rightForearm < 0)) {
        if(gRotation_rightArm - stateArm >= 0 )
            gRotation_rightArm = gRotation_rightArm - stateArm;
        if (gRotation_rightArm - stateArm < 0)
            gRotation_rightArm = 0;

        if(gRotation_rightForearm + stateForearm  <= 0)
            gRotation_rightForearm = gRotation_rightForearm + stateForearm;
        if (gRotation_rightForearm + stateForearm > 0)
            gRotation_rightForearm = 0;

    }

    //gRotation_leftForearm
    if (mouse.mouse_state == 1 && (gRotation_leftArm < 0 || gRotation_leftForearm > 0)) {
        if(gRotation_leftArm + stateArm <= 0)
            gRotation_leftArm = gRotation_leftArm + stateArm;
        if(gRotation_leftArm + stateArm > 0)
            gRotation_leftArm = 0;

        if(gRotation_leftForearm - stateForearm >= 0)
            gRotation_leftForearm = gRotation_leftForearm - stateForearm;
        if (gRotation_leftForearm - stateForearm < 0)
            gRotation_leftForearm = 0;
    }

    if ((IfRightHandCollision(player) || IfLeftHandCollision(player)) && mouse.mouse_state == 0) {
        mouse.mouse_state = 1;
        points++;
    }

}


//gets e sets auxiliares
void object_player:: setTheta(GLfloat _theta){
    gTheta_Head = _theta;
}
void object_player:: setLeftGripX(GLfloat newLeftGripPositionX){
    gX_leftGrip = newLeftGripPositionX;

};
void object_player:: setLeftGripY(GLfloat newLeftGripPositionY){
    gY_leftGrip = newLeftGripPositionY;

};
void object_player:: setRightGripX(GLfloat newRightGripPositionX){
    gX_rightGrip = newRightGripPositionX;

};
void object_player:: setRightGripY(GLfloat newRightGripPositionY){
    gY_rightGrip = newRightGripPositionY;

};


int  object_player::getPlayerPoints() const {
    return points;
}  
GLfloat  object_player::getHeadX() const {
    return gX_head;
}
GLfloat  object_player::getHeadY() const{
    return gY_head;
}
GLfloat  object_player::getRadius() const{
    return circle_head->circle_radius;
}
GLfloat  object_player::getHandSize() const{
    return getRadius() * 0.4;
}
GLfloat  object_player::getBarrier()  const {
    return getRadius() * 2 ;
}



