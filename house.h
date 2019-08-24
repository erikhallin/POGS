#ifndef HOUSE_H
#define HOUSE_H

#include "definitions.h"
#include <iostream>
#include <stdlib.h>
#include <gl/gl.h>
#include <cmath>

using namespace std;

class house
{
    public:
        house(int posx,int posy,float wag);

        bool update(float wag);
        bool draw();

        float m_pos_x,m_pos_y;
        float m_rotation,m_size;
        int m_type;
        float m_wag_anim;

    private:
};

#endif // HOUSE_H
