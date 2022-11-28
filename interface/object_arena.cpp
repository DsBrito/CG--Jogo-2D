


#include "object_arena.h"
#include "object_player.h"

#include <cstring>
#include <string>

using namespace std;

void object_arena::ReadArena(GLfloat a_x, GLfloat a_y, GLfloat a_height, GLfloat a_width, const string &a_color) {


    arena_x = a_x;
    arena_y = a_y;
    arena_height = a_height;
    arena_width = a_width;


    if (strcmp(a_color.c_str(),"blue")==0) {
        arena_R = 0;
        arena_G = 0;
        arena_B = 1;
    } else if(strcmp(a_color.c_str(),"red")==0) {
        arena_R = 1;
        arena_G = 0;
        arena_B = 0;
    } else if (strcmp(a_color.c_str(),"gren")==0)  {
        arena_R = 0;
        arena_G = 1;
        arena_B = 0;
    }
}