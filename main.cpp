/*

Centro Tecnológico Departamento de Informática
Disciplina: Computação Gráfica
Código: INF09282 e INF09284
Prof. Thiago Oliveira dos Santos

Trabalho 2D
Autor: DIONATAS SANTOS BRITO

Especificação Chek
[OK]- Criar um Makefile com > make all, make clean e execultavel com o nome de trabalhocg
[]- Ao rodar, o programa deverá ler e interpretar os elementos da arena do arquivo do tipo SVG informado pela linha de comando
[]- A arena será composta por uma série de elementos um círculo verde representando o personagem do jogador e um círculo vermelho representando o oponente (controlado pelo computador). 
[]- Um arquivo SVG será fornecido como exemplo juntamente com a descrição do trabalho, porém é responsabilidade do aluno testar outros arquivos com configurações (posições e tamanhos) diferentes para os elementos. 
[OK]- A leitura do SVG poderá ser feita utilizando-se um parser para XML. Sugiro utilizar a Tinyxml que é simples e pode ser enviada juntamente com o código para ser compilada.

Desenho Personagem Chek
[]- Os círculos representarão a cabeça dos jogadores e estarão sempre dentro da arena
[]- Os outros elementos para compor os jogadores devem escolhidos e desenhados pelo aluno usando uma escala controlada pelo tamanho da cabeça. 
    Por exemplo, se o personagem tiver uma cabeça de raio X e um braço de comprimento Y, um personagem com a cabeça de raio X/2 deverá ter um braço de comprimento Y/2. 
[]- Os personagens serão compostos pelos elementos descritos na Figura (no pdf), nariz indica a frente do personagem. 
[]- Ao iniciar o jogo os personagens devem estar de frente um para o outro.

Andar do Personagem Chek
[]- O controle do movimento de andar será feito com teclas a, s, d e w do teclado. 
[]- As teclas a e d servirão para girar o corpo do jogador no sentido anti-horário e horário respectivamente. 
[]- As teclas w e s servirão para mover o jogador para frente (direção do nariz) e para trás respectivamente. 
[]- A combinação de duas teclas, uma de giro e uma de movimento, deverão causar um movimento curvilíneo, como se estivesse fazendo uma curva.

Colisão do Personagem Chek
[]- Os jogadores não deverão sair da arena (a cabeça não deve sair) e não deverão ocupar um mesmo espaço.
[]- Para não ocupar o mesmo espaço, a colisão deverá ser calculada considerando um círculo imaginário envolvendo o jogador. 
[]- O círculo imaginário não poderá entrar no espaço da cabeça do outro jogador, conforme representado (no pdf). Perceba que o círculo imaginário não precisa ser desenhado.

Soco do Personagem Check
[]- O jogador poderá dar socos com os dois braços, um por vez.
[]- O soco será controlado pelo mouse. 
[]- Para disparar um soco, o usuário deverá clicar o botão esquerdo do mouse e mantê-lo pressionado para controlar os braços. Após o clique, o jogador entrará em situação de soco e ao mover o mouse para a direita o braço direito iniciará o movimento de soco para frente. 
[]- O braço chegará em sua posição máxima após o mouse percorrer uma distância equivalente à metade da largura da janela (considerando a posição inicial como ponto de partida). 
[]- Após essa distância, o braço deve permanecer na posição máxima mesmo que o mouse continue se afastando com o botão clicado.
[]- O braço retornará à posição inicial ao retornar com o mouse para a posição inicial do clique. 
[]- Só é necessário considerar o movimento horizontal do mouse para disparar o soco. O movimento análogo pode ser feito para o braço esquerdo. Portanto, para dar vários socos na sequência, basta manter o mouse pressionado e movê-lo de um lado para o outro. 
[]- Ao soltar o botão ou andar com o jogador, o jogador sairá da situação de soco e o braço deverá retornar para a posição inicial mesmo que o movimento não tenha terminado.
[]- Durante o movimento de soco, o braço move a junta do ombro e do cotovelo até sair do círculo imaginário de colisão. A proporção de movimento das juntas deve ser calibrada para fazer o movimento visualmente apropriado.

Pontuação do Personagem Check
[]- Toda vez que uma das luvas colidir com a cabeça do adversário enquanto o usuário estiver em situação de soco], um ponto deve ser marcado.
[]- A cabeça atingida deverá mudar de cor enquanto houver a colisão. 
[]- Perceba que que para contar dois pontos a luva deve colidir com a cabeça, deixar de colidir e depois colidir novamente. 
[]- O jogo acaba com a vitória de quem atingir 10 pontos. O placar deve ser mostrado no canto inferior esquerdo da tela. 
[]- Ao finalizar o jogo, deve-se mostrar uma mensagem na nela com o vencedor.

Movimento do oponente
[]- O oponente deverá ter algum movimento “aleatório” para atacar o jogador. 
[]- Ele deverá dar socos e buscar a luta com o jogador, porém respeitando as ações de movimento estabelecidas para andar e para dar socos. 
[]- O movimento “aleatório” é de livre escolha, mas ele deve buscar a luta.
[]- O aluno deverá tratar os movimentos para funcionar de forma equivalente em máquinas diferentes (ou seja, tratar o tempo decorrido entre chamadas idle), conforme vista em sala. 
[]- Ele deverá também utilizar os conceitos de double buffer e variável de estado das teclas para interação com teclado (usando o evento KeyUp como visto em aula). 

Testes Finais
#DESENHO
[]- Arquivo dado

#ANDAR
[]- Andar corretamente
[]- Manter as partes do corpo

#COLISÃO
[]- Não sair da arena
[]- Não invadir o oponente
[]- Não ser invadido pelo oponente

#DAR SOCOS
[]- Movimento
[]- Movimento em posições/ângulos diferentes
[]- Socos em sequêencia

#PONTUAR
[]- Colisão/Mudar de cor
[]- Contagem escrita 

#MOVIMENTO DO OPONENTE
[]- Anda corretamente
[]- Da socos corretamente

*/
#include <cstring>
#include <cmath>
#include <iostream>
#include <cstdlib>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include "tinyxml/tinystr.h"
#include "tinyxml/tinyxml.h"

#include "interface/object_rectangle.h"
#include "interface/object_circle.h"
#include "interface/object_player.h"
#include "interface/object_arena.h"
#include "interface/object_mouse.h"


using namespace std;

GLdouble PlayerWidth;
GLdouble PlayerHeight;

object_mouse MouseOne;
object_mouse MouseTwo;
object_player PlayerOne;
object_player PlayerTwo;
object_arena FightField;


int keyStatus[256];
bool GameOver = false; //Controla a animacao do game

/*____________________________________________________________________________________________________
|Função:                    Leitura do arquivo XML                                                   |
|----------------------------------------------------------------------------------------------------|                                                        
|Comentários:  Seguindo a recomendação do professor de utilizar o Tinyxml para realizar a leitura    | 
|----------------------------------------------------------------------------------------------------|
|Fonte: Carregar XML de um arquivo                                                                   |
|        https://www.cs.cmu.edu/~preethi/src/tinyxml/docs/tutorial0.html                             |
|____   
        Parse XML 
        https://gitee.com/dustinksi/tinyxml2/blob/master/xmltest.cpp
        https://stackoverflow.com/questions/52543335/why-is-tinyxml2s-xmldocumentfirstchild-function-returning-null-when-attempt        
        
        
        ________________________________________________________________________________________________|*/
void parseXML(TiXmlNode *root);
void ReadImput(char *const pfileName) {
    //carregar o arquivo
    TiXmlDocument doc(pfileName);
    bool load = doc.LoadFile();   //elemento carregado na estrutura
    if (load) {
       cout <<  pfileName << endl;
    } else {
       cout << "Failed to load the file"<< pfileName << endl;
        exit(0);
    }

    TiXmlNode *root = doc.FirstChild();
    parseXML(root);//fazer o parse de XML

}
//str funções =https://cplusplus.com/reference/cstdlib/strtod/
//20 = https://cpp.hotexamples.com/examples/-/TiXmlNode/ToElement/cpp-tixmlnode-toelement-method-examples.html
void parseXML(TiXmlNode *root){
    GLfloat playerx;
    string color = "green"; //PlayerOne = green,  PlayerTwo = red (para trocar jogador basta inverter as cores)
    TiXmlNode* node;

    //~~ analogia for(p=lista->primeiro;p!=NULL;p=p->proximo){
	for(node= root->FirstChild(); node!=nullptr; node=node->NextSibling() ) {
        TiXmlElement *copy = node->ToElement();
        if(copy==NULL)
            cout << "Falied! the node is null " << endl;

        else{
            string str = (copy->Value());
            const char* ch_prt = str.c_str();
            //arena
            if(strcmp(copy->Value(),"rect")==0){
                PlayerWidth = strtod(copy->Attribute("width"),NULL);
                PlayerHeight =strtod(copy->Attribute("height"),NULL);

                FightField.ReadArena(strtof(copy->Attribute("x"),NULL),strtof(copy->Attribute("y"),NULL),strtof(copy->Attribute("height"),NULL),strtof(copy->Attribute("width"),NULL),copy->Attribute("fill"));
                cout <<"[FightField] <"<< ch_prt<<" x="<< copy->Attribute("x") << " y="<<  copy->Attribute("y")<< " width="<< copy->Attribute("width") << " height="<< copy->Attribute("height") << " fill=" << copy->Attribute("fill") << "/>" << endl;

            }else if (strcmp(copy->Value(),"circle")==0) {
                playerx = FightField.arena_y + (FightField.arena_y + FightField.arena_height) - strtof(copy->Attribute("cy"),NULL);

                if (strcmp(color.c_str(),copy->Attribute("fill"))==0 ){
                    PlayerOne.ReadPlayer(strtof(copy->Attribute("cx"),NULL),playerx, 0,strtof(copy->Attribute("r"),NULL),copy->Attribute("fill"));
                    cout <<"[PlayerOne] <"<< ch_prt <<" x="<< copy->Attribute("cx") << " y="<<  copy->Attribute("cy")<< " r="<< copy->Attribute("r") << " fill=" << copy->Attribute("fill") << "/>" << endl;
                }
                else{
                    PlayerTwo.ReadPlayer(strtof(copy->Attribute("cx"),NULL),playerx, 0,strtof(copy->Attribute("r"),NULL),copy->Attribute("fill"));
                    cout <<"[PlayerTwo] <"<< ch_prt <<" x="<< copy->Attribute("cx") << " y="<<  copy->Attribute("cy")<< " r="<< copy->Attribute("r") << " fill=" << copy->Attribute("fill") << "/>" << endl;
                }
            }
        }
    }
    //graus
    double degrees = Tools::RadiansToDegressTools(atan2(PlayerOne.getHeadY() - PlayerTwo.getHeadY(), PlayerOne.getHeadX() - PlayerTwo.getHeadX()));
    PlayerOne.setTheta(degrees + 180);
    PlayerTwo.setTheta(degrees);

}
void keyPress(unsigned char key, int x, int y) {
    switch (key) {
        case 'a':
        case 'A':
            keyStatus[(int) ('a')] = 1;
            break;
        case 'd':
        case 'D':
            keyStatus[(int) ('d')] = 1;
            break;
        case 'w':
        case 'W':
            keyStatus[(int) ('w')] = 1;
            break;
        case 's':
        case 'S':
            keyStatus[(int) ('s')] = 1;
            break;
        case 'y':
        case 'Y':
            break;
        case 'n':
        case 'N':
        case 27:
            exit(0);
        case ' ':
            keyStatus[(int) (' ')] = !keyStatus[(int) (' ')];
            break;
        default:
            break;
    }
    glutPostRedisplay();
}

void keyup(unsigned char key, int x, int y) {
    if (key != ' ') {
        keyStatus[(int) (key)] = 0;
    }
    glutPostRedisplay();
}

void ResetKeyStatus() {
    for (int i = 0; i < 256; i++) {
        keyStatus[i] = 0;
    }
}
//nao tem

void motion(int x, int y) {
    MouseOne.mouse_movedX = (GLfloat) x + FightField.arena_y;
    MouseOne.mouse_movedY = FightField.arena_y + FightField.arena_height - (GLfloat) y;
    glutPostRedisplay();
}

void mouseFunc(int button, int state, int x, int y) {
    MouseOne.mouse_button = button;
    MouseOne.mouse_state = state;
    MouseOne.mouse_clickX = (GLfloat) x + FightField.arena_x;
    MouseOne.mouse_clickY =FightField.arena_y + FightField.arena_height - (GLfloat) y;
    motion(x, y);
}


//retirada do lab robo
void init() {
    MouseOne.mouse_state = 1;
    MouseTwo.mouse_state = 1;  //adaptado para o mouse
    ResetKeyStatus();
    // The color the windows will redraw. Its done to erase the previous frame.
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);  // Black, no opacity(alpha).

    glMatrixMode(GL_PROJECTION);// Select the projection matrix   
    glOrtho(FightField.arena_x,
            FightField.arena_x + FightField.arena_width,// X coordinate of right edge   
            FightField.arena_y, // Y coordinate of bottom edge   
            FightField.arena_y + FightField.arena_height,// Y coordinate of top edge    
            -100, // Z coordinate of the “near” plane   
            100); // Z coordinate of the “far” plane
    glMatrixMode(GL_MODELVIEW);// Select the projection matrix    
    glLoadIdentity();
}


//retirado do lab robo (renderScene)
void display() {
    glClearColor(FightField.arena_R, FightField.arena_G, FightField.arena_B, 0.0);

    // Clear the screen.
    glClear(GL_COLOR_BUFFER_BIT);

    GameOver = PlayerOne.getPlayerPoints() >= 10 || PlayerTwo.getPlayerPoints() >= 10;

    if (!GameOver) {
        PlayerOne.DrawGameArea();
        PlayerTwo.DrawGameArea();

        PlayerOne.DrawPlayerPoints(FightField.arena_x + 10, FightField.arena_y + 10,PlayerOne,PlayerTwo);
    } else {
        PlayerOne.DrawPlayerGameOver(FightField.arena_x  + FightField.arena_width / 2, FightField.arena_y + FightField.arena_height / 2, PlayerOne);
    }

    glutSwapBuffers();
}





void idle() {
    static GLdouble previousTime = glutGet(GLUT_ELAPSED_TIME);
    static GLdouble punchCurrentTime = 0;
    static GLdouble punchCurrentVelocity = PlayerWidth / 700;
    static bool inc = true;
    GLdouble currentTime, timeDifference;
    currentTime = glutGet(GLUT_ELAPSED_TIME);
    timeDifference = currentTime - previousTime;
    previousTime = currentTime;

    if (!keyStatus[(int) (' ')]) {
        if (inc) {
            punchCurrentTime += timeDifference;
        } else {
            punchCurrentTime -= timeDifference;
        }

        if (punchCurrentTime < -700 || punchCurrentTime > 700) {
            inc = !inc;
            MouseTwo.mouse_state = 0;
        }
        double PlayerTwoX = PlayerTwo.getHeadX();
        double PlayerTwoY = PlayerTwo.getHeadY();
        MouseTwo.mouse_button = 0;
        MouseTwo.mouse_clickX = 0;
        MouseTwo.mouse_movedX = punchCurrentTime * punchCurrentVelocity;
        PlayerTwo.FixWalk(0.1 * timeDifference, PlayerOne, FightField);
        PlayerTwo.setTheta(Tools::RadiansToDegressTools(atan2(PlayerOne.getHeadY() - PlayerTwo.getHeadY(), PlayerOne.getHeadX() - PlayerTwo.getHeadX())));
        if (PlayerTwoX != PlayerTwo.getHeadX() || PlayerTwoY != PlayerTwo.getHeadY()) {
            MouseTwo.mouse_state = 1;
        }
    } else {
        MouseTwo.mouse_state = 1;
    }
    if (keyStatus[(int) ('w')]) {
        PlayerOne.FixWalk(timeDifference, PlayerTwo, FightField);
        MouseOne.mouse_state = 1;
    }
    if (keyStatus[(int) ('s')]) {
        PlayerOne.FixWalk(-timeDifference, PlayerTwo, FightField);
        MouseOne.mouse_state = 1;
    }
    if (keyStatus[(int) ('a')]) {
        PlayerOne.FixVelAngular(timeDifference);
    }
    if (keyStatus[(int) ('d')]) {
        PlayerOne.FixVelAngular(-timeDifference);
    }

    PlayerOne.FixPunch(timeDifference, MouseOne, FightField, PlayerTwo);
    PlayerTwo.FixPunch(timeDifference, MouseTwo, FightField, PlayerOne);

    glutPostRedisplay();
}
int main(int argc, char *argv[]) {
 
	printf("\n\nExemplo de entrada: ./execultavel pasta/arena_x.svg ...\n");
    printf("Carregando a Arena de Batalha: %s ...\n",argv[1]);
    ReadImput(argv[1]);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

    //Create window
    glutInitWindowSize(PlayerWidth, PlayerHeight);
    glutInitWindowPosition(150, 50);
    glutCreateWindow("Trabalho 2D - Luta Boxe");
    init();

    glutDisplayFunc(display);
    glutIdleFunc(idle);

   glutKeyboardFunc(keyPress);
    glutKeyboardUpFunc(keyup);

   glutMotionFunc(motion);
    glutMouseFunc(mouseFunc);

    glutMainLoop();


    return 0;
}


 
