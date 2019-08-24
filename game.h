#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <SOIL/SOIL.h>
#include <gl/gl.h>
#include <vector>
#include <string>
#include <ctime>
#include <stdlib.h>
#include <sstream>
#include <fstream>

#include "definitions.h"
#include "sound.h"
#include "house.h"
#include "pop.h"


using namespace std;

enum gamestates
{
    gs_init=0,
    gs_main,
    gs_info,
    gs_run,
    gs_lost,
    gs_gameover,
    gs_win,
    gs_nextlevel
};

struct terrain_line
{
    vector<float> vec_x;
    vector<float> vec_y;
    float color;
};

struct flash
{
    vector<float> vec_x;
    vector<float> vec_y;
    float age;
};

struct road
{
    vector<float> vec_x;
    vector<float> vec_y;
    float age;
};

struct particle
{
    particle()
    {
        y_start=x=y=r=g=b=1;
        type=age=0;
    }
    particle(int _x,int _y,int _type)
    {
        x=_x;
        y_start=y=_y;
        r=g=b=1;
        type=_type;
        age_full=age=1;
    }
    particle(float _x,float _y,float _y_start,
             float _x_dir,float _y_dir,int _type,
             float _r,float _g,float _b,float _age)
    {
        x=_x;
        y=_y;
        y_start=_y_start;
        x_dir=_x_dir;
        y_dir=_y_dir;
        r=_r;
        g=_g;
        b=_b;
        type=_type;
        age_full=age=_age;
    }
    float x,y,y_start;
    int type; //0 off, 1 explosion, 2 birth
    float r,g,b;
    float age,age_full;
    float x_dir,y_dir;
};

class game
{
    public:
        game();

        ofstream logfile;
        bool m_logging;

        int game_state;
        int game_level;

        bool init(int screen_width,int screen_height);
        bool update();
        bool draw();
        bool reset();
        bool draw_number(char val);
        bool spawn_pop(int pop_ind,bool random_prop=false,float posx=0,float posy=0);

        int mouse_pos[2];
        int mouse_pos_world[2];
        int mouse_pos_last[2];
        bool mouse_but[4];
        bool rmb_pressed;
        bool lmb_pressed;
        float m_cam_pos_x,m_cam_pos_y;
        float m_shake_timer;
        float m_wag_anim;

        bool keys[256];
        int inactive_button;
        bool draw_help;

        string genetic_data;

        vector<house> mvec_house;
        vector<pop> mvec_pop;
        vector<particle> mvec_particle;
        vector<flash> mvec_flash;
        vector<terrain_line> mvec_terrain_line;
        vector<road> mvec_road;

        float m_pop_spawn_timer,m_pop_spawn_time;
        int m_res_count;
        int m_house_cost;
        int m_points_left;
        int m_house_cost_increase;

        float m_speed_min,m_speed_max;
        float m_age_min,m_age_max;
        float m_prod_min,m_prod_max;
        float m_fert_min,m_fert_max;
        float m_crime_min,m_crime_max;
        bool m_locked_statsview;
        int m_locked_statsview_ind;

        //sound
        bool sound_loaded;
        sound* pSound;
        //texture
        bool texture_loaded;
        int tex_main,tex_info,tex_gameover,tex_help,tex_win,tex_nextlevel;
        int tex_tut[7];

    private:

        int screen_width, screen_height;

};

#endif // GAME_H
