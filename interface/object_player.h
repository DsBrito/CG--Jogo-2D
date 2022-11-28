
#ifndef OBJECT_PLAYER_H
#define OBJECT_PLAYER_H


#include <stack>
#include "../tools/tools.h"
#include "object_rectangle.h"
#include "object_circle.h"
#include "object_mouse.h"
#include <iostream>
#include "object_arena.h"

#define ANGULAR_VELOCITY 0.2
#define LINEAR_VELOCITY 0.5

#define BARRIER_SIZE_MULTIPLIER 2.5

#define NOSE_SIZE_MULTIPLIER 0.2
#define NOSE_DISTANCE_MULTIPLIER 1.01

#define ARM_LENGTH_MULTIPLIER 2.2
#define ARM_WIDTH_MULTIPLIER 0.25

#define FOREARM_LENGTH_MULTIPLIER 2
#define FOREARM_WIDTH_MULTIPLIER 0.25

#define HAND_SIZE_MULTIPLIER 0.4

#define ARM_ANGULAR_AMPLITUDE 130
#define FOREARM_ANGULAR_AMPLITUDE 45

#define ARM_ANGULAR_VELOCITY 0.8
#define FOREARM_ANGULAR_VELOCITY 0.8


using namespace std;


class object_player{
private:
//circulos
    object_circle *circle_head;
    object_circle *circle_nose;
    object_circle *circle_leftHand;
    object_circle *circle_rightHand;

//varaiveis retangulo
    object_rectangle *recltangle_leftArm;
    object_rectangle *recltangle_rightArm;
    object_rectangle *rectangle_leftForearm;
    object_rectangle *rectangle_rightForearm;


//variaveis GL/player
//cabeça
    GLfloat gX_head;
    GLfloat gY_head;
    GLfloat gTheta_Head;

// nariz
    GLfloat gX_nose;
    GLfloat gY_nose;

//mãos
    GLfloat gX_leftHand;
    GLfloat gY_leftHand;  
    GLfloat gX_rightHand;
    GLfloat gY_rightHand;

//braço
    GLfloat gX_leftArm;
    GLfloat gY_leftArm;
    GLfloat gTheta_leftArmAngle;
    GLfloat gRotation_leftArm;

    GLfloat gX_rightArm;
    GLfloat gY_rightArm;
    GLfloat gTheta_rightArmAngle;
    GLfloat gRotation_rightArm;

//punho
    GLfloat gX_leftGrip;
    GLfloat gY_leftGrip;
    GLfloat gX_rightGrip;
    GLfloat gY_rightGrip;

//antebraço
    GLfloat gX_leftForearm;
    GLfloat gY_leftForearm;
    GLfloat gTheta_leftForearm;
    GLfloat gRotation_leftForearm;

    GLfloat gX_rightForearm;
    GLfloat gY_rightForearm;
    GLfloat gTheta_rightForearm;
    GLfloat gRotation_rightForearm;


//placar
    int points;

//tratamento de colisões 
    //entre jogadores
    void FixPlayerCollision(GLfloat &incX, GLfloat &incY, object_player &player, GLdouble state) const;
    //void treatPlayerCollision(GLfloat &xIncrement, GLfloat &yIncrement, object_player &player, GLdouble deltaTime)const;


    bool IfLeftHandCollision(object_player &player);
    bool IfRightHandCollision(object_player &player);

    //entre o joador e a arena
    void FixArenaCollision(object_arena &ringue, GLfloat &incX, GLfloat &incY) const;

public:
//iniciação dos jogadores
    void ReadPlayer(GLfloat p_x, GLfloat p_y, GLfloat p_theta, GLfloat p_radius, const string &color);


//desenhos 
    //Area e barreira
    void DrawGameArea();
    void DrawGameBarrier() const;
    //comandos de desenhos    
    void DrawPlayerHeadCommand() ;
    void DrawPlayerNoseCommand() ;
    void DrawRightArmCommand() ;
    void DrawRightForearmCommand() ;
    void DrawRightHandCommand() ;
    void DrawLeftArmCommand() ;
    void DrawLeftForearmCommand() ;
    void DrawLeftHandCommand();
    
    //jogador
   //desenha objetos que formam o jogador
    void DrawObjects(GLfloat p_radius, const string &p_color);
    void DrawPlayerNose();         //nariz
    void DrawPlayerRightArm();    //braço direito 
    void DrawPlayerLeftArm();           //braço esquerdo
   
   
    //placar
    void DrawPlayerPoints(GLfloat p_x, GLfloat p_y,object_player &p_One,object_player &p_Two);
    void DrawPlayerGameOver(GLfloat x, GLfloat y, object_player &player);


//ações do jogador no ringue de luta
    void FixWalk(GLdouble state, object_player &player, object_arena &arena); //andar
    void FixPunch(GLdouble state, object_mouse &mouse, object_arena &arena, object_player &player);
    void FixVelAngular(GLdouble state);

//gets e sets auxiliares
    void setLeftGripX(GLfloat h);
    void setLeftGripY(GLfloat h);

    void setRightGripX(GLfloat h);
    void setRightGripY(GLfloat h);

    void setTheta(GLfloat _theta);
    GLfloat getBarrier() const;
    GLfloat getHeadX() const;
    GLfloat getHeadY() const;
    GLfloat getRadius() const;
    GLfloat getHandSize() const;

    int getPlayerPoints() const;
    




void treatPunch(GLdouble deltaTime, object_mouse &mouse, object_arena &arena, object_player &player) ;
void  getLeftHandPosition();
void  getRightHandPosition();
    bool getLeftHandCollision(object_player &player);
    bool getRightHandCollision(object_player &player);
};
#endif //OBJECT_PLAYER_H
