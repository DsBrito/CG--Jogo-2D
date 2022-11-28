//
// Created by otavio on 13/03/2021.
//

#ifndef OBJECT_MOUSE_H
#define OBJECT_MOUSE_H

#include <GL/gl.h>
#include <GL/glu.h>

class object_mouse {
public:
    GLfloat mouse_clickX;
    GLfloat mouse_clickY;

    GLfloat mouse_movedX;
    GLfloat mouse_movedY;

    int mouse_button;
    int mouse_state;
};


#endif //OBJECT_MOUSE_H
