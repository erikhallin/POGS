#ifndef POP_H
#define POP_H

#include "definitions.h"
#include <iostream>
#include <stdlib.h>
#include <cmath>
#include <gl/gl.h>

using namespace std;

enum popstates
{
    ps_idle=0,
    ps_walk,
    ps_work
};

class pop
{
    public:
        pop(int posx,int posy);

        int update();
        bool draw();

        int m_state;
        float m_pos_x,m_pos_y;
        float m_rotation,m_size;
        float m_target_x,m_target_y;
        float m_speed;
        float m_idle_timer;//standing still during break
        float m_break_timer;//duration of the break
        float m_work_timer;//length of work shift
        float m_birth_timer;//wait before birth
        float m_crime_timer;//wait until risk of crime
        float m_walk_anim;
        float m_anim_dir;
        float m_offset_la,m_offset_ra,m_offset_ll,m_offset_rl;

        float m_productivity,m_fertility,m_criminality;
        float m_age_start,m_age_curr;
        int m_currworkplace;
        float m_workpos_x[2];
        float m_workpos_y[2];

    private:
};

#endif // POP_H
