#include "game.h"

#include "definitions.h"

game::game()
{
    game_state=gs_init;
    texture_loaded=false;
    sound_loaded=false;
    game_level=1;
    game_state=gs_main;
}

bool game::init(int _screen_width,int _screen_height)
{
    m_logging=false;
    //logfile setup
    if(m_logging) logfile.open("log.txt");
    if(m_logging) logfile<<"1";

    srand(time(0));
    m_locked_statsview=false;
    m_res_count=0;
    m_cam_pos_x=m_cam_pos_y=0;
    draw_help=false;

    m_shake_timer=_shake_time*0.5;
    m_wag_anim=0;

    switch(game_level)
    {
        case 1:
        {
            m_house_cost_increase=5;
            m_points_left=4;//10
            m_pop_spawn_time=10;

            //start house
            mvec_house.push_back(house(_screen_width*0.5,_screen_height*0.5,m_wag_anim));
            mvec_house.push_back(house(_screen_width*0.4,_screen_height*0.5,m_wag_anim));

            //new road
            road new_road;
            new_road.vec_x.push_back(mvec_house[0].m_pos_x);
            new_road.vec_y.push_back(mvec_house[0].m_pos_y);
            new_road.vec_x.push_back(mvec_house[1].m_pos_x);
            new_road.vec_y.push_back(mvec_house[1].m_pos_y);
            mvec_road.push_back(new_road);

            //start worker
            mvec_pop.push_back(pop(350,430));
            mvec_pop.back().m_currworkplace=0;
            mvec_pop.back().m_workpos_x[0]=mvec_house[0].m_pos_x;
            mvec_pop.back().m_workpos_y[0]=mvec_house[0].m_pos_y;
            mvec_pop.back().m_workpos_x[1]=mvec_house[1].m_pos_x;
            mvec_pop.back().m_workpos_y[1]=mvec_house[1].m_pos_y;
            mvec_pop.back().m_productivity=1;
            mvec_pop.back().m_criminality=0;
            mvec_pop.back().m_age_curr=mvec_pop.back().m_age_start=99999999;
        }break;

        case 2:
        {
            m_house_cost_increase=5;
            m_points_left=6;//10
            m_pop_spawn_time=10;

            //start house
            mvec_house.push_back(house(_screen_width*0.5,_screen_height*0.5,m_wag_anim));
            mvec_house.push_back(house(_screen_width*0.6,_screen_height*0.6,m_wag_anim));

            //new road
            road new_road;
            new_road.vec_x.push_back(mvec_house[0].m_pos_x);
            new_road.vec_y.push_back(mvec_house[0].m_pos_y);
            new_road.vec_x.push_back(mvec_house[1].m_pos_x);
            new_road.vec_y.push_back(mvec_house[1].m_pos_y);
            mvec_road.push_back(new_road);

            //start worker
            mvec_pop.push_back(pop(450,500));
            mvec_pop.back().m_currworkplace=0;
            mvec_pop.back().m_workpos_x[0]=mvec_house[0].m_pos_x;
            mvec_pop.back().m_workpos_y[0]=mvec_house[0].m_pos_y;
            mvec_pop.back().m_workpos_x[1]=mvec_house[1].m_pos_x;
            mvec_pop.back().m_workpos_y[1]=mvec_house[1].m_pos_y;
            mvec_pop.back().m_productivity=0.5;
            mvec_pop.back().m_fertility=0;
            mvec_pop.back().m_criminality=0;
            mvec_pop.back().m_age_curr=mvec_pop.back().m_age_start=99999999;
        }break;

        case 3:
        {
            m_house_cost_increase=5;
            m_points_left=4;//20
            m_pop_spawn_time=10;

            //start house
            mvec_house.push_back(house(_screen_width*0.5,_screen_height*0.5,m_wag_anim));
            mvec_house.push_back(house(_screen_width*0.65,_screen_height*0.5,m_wag_anim));
            mvec_house.push_back(house(_screen_width*0.4,_screen_height*0.6,m_wag_anim));

            //new road
            road new_road;
            new_road.vec_x.push_back(mvec_house[0].m_pos_x);
            new_road.vec_y.push_back(mvec_house[0].m_pos_y);
            new_road.vec_x.push_back(mvec_house[1].m_pos_x);
            new_road.vec_y.push_back(mvec_house[1].m_pos_y);
            mvec_road.push_back(new_road);
            road new_road1;
            new_road1.vec_x.push_back(mvec_house[0].m_pos_x);
            new_road1.vec_y.push_back(mvec_house[0].m_pos_y);
            new_road1.vec_x.push_back(mvec_house[2].m_pos_x);
            new_road1.vec_y.push_back(mvec_house[2].m_pos_y);
            mvec_road.push_back(new_road1);

            //start worker
            mvec_pop.push_back(pop(450,500));
            mvec_pop.back().m_currworkplace=0;
            mvec_pop.back().m_workpos_x[0]=mvec_house[0].m_pos_x;
            mvec_pop.back().m_workpos_y[0]=mvec_house[0].m_pos_y;
            mvec_pop.back().m_workpos_x[1]=mvec_house[1].m_pos_x;
            mvec_pop.back().m_workpos_y[1]=mvec_house[1].m_pos_y;
            mvec_pop.back().m_productivity=0.5;
            mvec_pop.back().m_fertility=0;
            mvec_pop.back().m_criminality=0;
            mvec_pop.back().m_age_curr=mvec_pop.back().m_age_start=99999999;
            //second
            mvec_pop.push_back(pop(400,200));
            mvec_pop.back().m_currworkplace=0;
            mvec_pop.back().m_workpos_x[0]=mvec_house[0].m_pos_x;
            mvec_pop.back().m_workpos_y[0]=mvec_house[0].m_pos_y;
            mvec_pop.back().m_workpos_x[1]=mvec_house[1].m_pos_x;
            mvec_pop.back().m_workpos_y[1]=mvec_house[1].m_pos_y;
            mvec_pop.back().m_productivity=0.5;
            mvec_pop.back().m_fertility=0;
            mvec_pop.back().m_criminality=0;
            mvec_pop.back().m_age_curr=mvec_pop.back().m_age_start=99999999;
            //third
            mvec_pop.push_back(pop(700,300));
            mvec_pop.back().m_currworkplace=0;
            mvec_pop.back().m_workpos_x[0]=mvec_house[0].m_pos_x;
            mvec_pop.back().m_workpos_y[0]=mvec_house[0].m_pos_y;
            mvec_pop.back().m_workpos_x[1]=mvec_house[2].m_pos_x;
            mvec_pop.back().m_workpos_y[1]=mvec_house[2].m_pos_y;
            mvec_pop.back().m_productivity=0.5;
            mvec_pop.back().m_fertility=0;
            mvec_pop.back().m_criminality=0;
            mvec_pop.back().m_age_curr=mvec_pop.back().m_age_start=99999999;
        }break;

        case 4://age
        {
            m_house_cost_increase=5;
            m_points_left=10;//20
            m_pop_spawn_time=10;

            //start house
            mvec_house.push_back(house(_screen_width*0.5,_screen_height*0.57,m_wag_anim));
            mvec_house.push_back(house(_screen_width*0.4,_screen_height*0.5,m_wag_anim));
            mvec_house.push_back(house(_screen_width*0.7,_screen_height*0.55,m_wag_anim));

            //new road
            road new_road;
            new_road.vec_x.push_back(mvec_house[0].m_pos_x);
            new_road.vec_y.push_back(mvec_house[0].m_pos_y);
            new_road.vec_x.push_back(mvec_house[1].m_pos_x);
            new_road.vec_y.push_back(mvec_house[1].m_pos_y);
            mvec_road.push_back(new_road);
            road new_road1;
            new_road1.vec_x.push_back(mvec_house[0].m_pos_x);
            new_road1.vec_y.push_back(mvec_house[0].m_pos_y);
            new_road1.vec_x.push_back(mvec_house[2].m_pos_x);
            new_road1.vec_y.push_back(mvec_house[2].m_pos_y);
            mvec_road.push_back(new_road1);

            //start worker
            mvec_pop.push_back(pop(450,500));
            mvec_pop.back().m_currworkplace=0;
            mvec_pop.back().m_workpos_x[0]=mvec_house[0].m_pos_x;
            mvec_pop.back().m_workpos_y[0]=mvec_house[0].m_pos_y;
            mvec_pop.back().m_workpos_x[1]=mvec_house[1].m_pos_x;
            mvec_pop.back().m_workpos_y[1]=mvec_house[1].m_pos_y;
            mvec_pop.back().m_productivity=0.7;
            mvec_pop.back().m_fertility=0;
            mvec_pop.back().m_criminality=0;
            //second
            mvec_pop.push_back(pop(400,200));
            mvec_pop.back().m_currworkplace=0;
            mvec_pop.back().m_workpos_x[0]=mvec_house[0].m_pos_x;
            mvec_pop.back().m_workpos_y[0]=mvec_house[0].m_pos_y;
            mvec_pop.back().m_workpos_x[1]=mvec_house[1].m_pos_x;
            mvec_pop.back().m_workpos_y[1]=mvec_house[1].m_pos_y;
            mvec_pop.back().m_productivity=0.7;
            mvec_pop.back().m_fertility=0;
            mvec_pop.back().m_criminality=0;
            //third
            mvec_pop.push_back(pop(700,300));
            mvec_pop.back().m_currworkplace=0;
            mvec_pop.back().m_workpos_x[0]=mvec_house[0].m_pos_x;
            mvec_pop.back().m_workpos_y[0]=mvec_house[0].m_pos_y;
            mvec_pop.back().m_workpos_x[1]=mvec_house[2].m_pos_x;
            mvec_pop.back().m_workpos_y[1]=mvec_house[2].m_pos_y;
            mvec_pop.back().m_productivity=0.7;
            mvec_pop.back().m_fertility=0;
            mvec_pop.back().m_criminality=0;
        }break;

        case 5://fert
        {
            m_house_cost_increase=5;
            m_points_left=8;//20
            m_pop_spawn_time=30;

            //start house
            mvec_house.push_back(house(_screen_width*0.5,_screen_height*0.57,m_wag_anim));
            mvec_house.push_back(house(_screen_width*0.4,_screen_height*0.5,m_wag_anim));
            mvec_house.push_back(house(_screen_width*0.7,_screen_height*0.55,m_wag_anim));
            mvec_house.push_back(house(_screen_width*0.45,_screen_height*0.4,m_wag_anim));

            //new road
            road new_road;
            new_road.vec_x.push_back(mvec_house[0].m_pos_x);
            new_road.vec_y.push_back(mvec_house[0].m_pos_y);
            new_road.vec_x.push_back(mvec_house[1].m_pos_x);
            new_road.vec_y.push_back(mvec_house[1].m_pos_y);
            mvec_road.push_back(new_road);
            road new_road1;
            new_road1.vec_x.push_back(mvec_house[0].m_pos_x);
            new_road1.vec_y.push_back(mvec_house[0].m_pos_y);
            new_road1.vec_x.push_back(mvec_house[2].m_pos_x);
            new_road1.vec_y.push_back(mvec_house[2].m_pos_y);
            mvec_road.push_back(new_road1);
            road new_road2;
            new_road2.vec_x.push_back(mvec_house[1].m_pos_x);
            new_road2.vec_y.push_back(mvec_house[1].m_pos_y);
            new_road2.vec_x.push_back(mvec_house[3].m_pos_x);
            new_road2.vec_y.push_back(mvec_house[3].m_pos_y);
            mvec_road.push_back(new_road2);

            //start worker
            mvec_pop.push_back(pop(450,540));
            mvec_pop.back().m_currworkplace=0;
            mvec_pop.back().m_workpos_x[0]=mvec_house[0].m_pos_x;
            mvec_pop.back().m_workpos_y[0]=mvec_house[0].m_pos_y;
            mvec_pop.back().m_workpos_x[1]=mvec_house[1].m_pos_x;
            mvec_pop.back().m_workpos_y[1]=mvec_house[1].m_pos_y;
            mvec_pop.back().m_productivity=0.5;
            mvec_pop.back().m_fertility=0.5;
            mvec_pop.back().m_criminality=0;
            mvec_pop.back().m_state=ps_idle;
            //second
            mvec_pop.push_back(pop(500,555));
            mvec_pop.back().m_currworkplace=0;
            mvec_pop.back().m_workpos_x[0]=mvec_house[0].m_pos_x;
            mvec_pop.back().m_workpos_y[0]=mvec_house[0].m_pos_y;
            mvec_pop.back().m_workpos_x[1]=mvec_house[1].m_pos_x;
            mvec_pop.back().m_workpos_y[1]=mvec_house[1].m_pos_y;
            mvec_pop.back().m_productivity=0.5;
            mvec_pop.back().m_fertility=0.5;
            mvec_pop.back().m_criminality=0;
            mvec_pop.back().m_state=ps_idle;
            //third
            mvec_pop.push_back(pop(530,550));
            mvec_pop.back().m_currworkplace=0;
            mvec_pop.back().m_workpos_x[0]=mvec_house[0].m_pos_x;
            mvec_pop.back().m_workpos_y[0]=mvec_house[0].m_pos_y;
            mvec_pop.back().m_workpos_x[1]=mvec_house[2].m_pos_x;
            mvec_pop.back().m_workpos_y[1]=mvec_house[2].m_pos_y;
            mvec_pop.back().m_productivity=0.5;
            mvec_pop.back().m_fertility=0.5;
            mvec_pop.back().m_criminality=0;
            mvec_pop.back().m_state=ps_idle;
            //forth
            mvec_pop.push_back(pop(502,558));
            mvec_pop.back().m_currworkplace=0;
            mvec_pop.back().m_workpos_x[0]=mvec_house[0].m_pos_x;
            mvec_pop.back().m_workpos_y[0]=mvec_house[0].m_pos_y;
            mvec_pop.back().m_workpos_x[1]=mvec_house[3].m_pos_x;
            mvec_pop.back().m_workpos_y[1]=mvec_house[3].m_pos_y;
            mvec_pop.back().m_productivity=0.5;
            mvec_pop.back().m_fertility=0.5;
            mvec_pop.back().m_criminality=0;
            mvec_pop.back().m_state=ps_idle;
        }break;

        case 6://crim
        {
            m_house_cost_increase=5;
            m_points_left=8;//20
            m_pop_spawn_time=30;

            //start house
            mvec_house.push_back(house(_screen_width*0.4,_screen_height*0.45,m_wag_anim));
            mvec_house.push_back(house(_screen_width*0.45,_screen_height*0.48,m_wag_anim));
            mvec_house.push_back(house(_screen_width*0.55,_screen_height*0.52,m_wag_anim));
            mvec_house.push_back(house(_screen_width*0.52,_screen_height*0.6,m_wag_anim));
            mvec_house.push_back(house(_screen_width*0.43,_screen_height*0.56,m_wag_anim));

            //new road
            road new_road;
            new_road.vec_x.push_back(mvec_house[0].m_pos_x);
            new_road.vec_y.push_back(mvec_house[0].m_pos_y);
            new_road.vec_x.push_back(mvec_house[1].m_pos_x);
            new_road.vec_y.push_back(mvec_house[1].m_pos_y);
            mvec_road.push_back(new_road);
            road new_road1;
            new_road1.vec_x.push_back(mvec_house[1].m_pos_x);
            new_road1.vec_y.push_back(mvec_house[1].m_pos_y);
            new_road1.vec_x.push_back(mvec_house[2].m_pos_x);
            new_road1.vec_y.push_back(mvec_house[2].m_pos_y);
            mvec_road.push_back(new_road1);
            road new_road2;
            new_road2.vec_x.push_back(mvec_house[2].m_pos_x);
            new_road2.vec_y.push_back(mvec_house[2].m_pos_y);
            new_road2.vec_x.push_back(mvec_house[3].m_pos_x);
            new_road2.vec_y.push_back(mvec_house[3].m_pos_y);
            mvec_road.push_back(new_road2);
            road new_road3;
            new_road3.vec_x.push_back(mvec_house[3].m_pos_x);
            new_road3.vec_y.push_back(mvec_house[3].m_pos_y);
            new_road3.vec_x.push_back(mvec_house[4].m_pos_x);
            new_road3.vec_y.push_back(mvec_house[4].m_pos_y);
            mvec_road.push_back(new_road3);

            //start worker
            mvec_pop.push_back(pop(400,400));
            mvec_pop.back().m_currworkplace=0;
            mvec_pop.back().m_workpos_x[0]=mvec_house[0].m_pos_x;
            mvec_pop.back().m_workpos_y[0]=mvec_house[0].m_pos_y;
            mvec_pop.back().m_workpos_x[1]=mvec_house[1].m_pos_x;
            mvec_pop.back().m_workpos_y[1]=mvec_house[1].m_pos_y;
            mvec_pop.back().m_productivity=0.5;
            mvec_pop.back().m_fertility=0.5;
            mvec_pop.back().m_criminality=0.5;
            //second
            mvec_pop.push_back(pop(600,480));
            mvec_pop.back().m_currworkplace=0;
            mvec_pop.back().m_workpos_x[0]=mvec_house[0].m_pos_x;
            mvec_pop.back().m_workpos_y[0]=mvec_house[0].m_pos_y;
            mvec_pop.back().m_workpos_x[1]=mvec_house[1].m_pos_x;
            mvec_pop.back().m_workpos_y[1]=mvec_house[1].m_pos_y;
            mvec_pop.back().m_productivity=0.5;
            mvec_pop.back().m_fertility=0.5;
            mvec_pop.back().m_criminality=0.2;
            //third
            mvec_pop.push_back(pop(410,600));
            mvec_pop.back().m_currworkplace=0;
            mvec_pop.back().m_workpos_x[0]=mvec_house[0].m_pos_x;
            mvec_pop.back().m_workpos_y[0]=mvec_house[0].m_pos_y;
            mvec_pop.back().m_workpos_x[1]=mvec_house[2].m_pos_x;
            mvec_pop.back().m_workpos_y[1]=mvec_house[2].m_pos_y;
            mvec_pop.back().m_productivity=0.5;
            mvec_pop.back().m_fertility=0.5;
            mvec_pop.back().m_criminality=0.6;
            mvec_pop.back().m_state=ps_idle;
            //forth
            mvec_pop.push_back(pop(610,630));
            mvec_pop.back().m_currworkplace=0;
            mvec_pop.back().m_workpos_x[0]=mvec_house[0].m_pos_x;
            mvec_pop.back().m_workpos_y[0]=mvec_house[0].m_pos_y;
            mvec_pop.back().m_workpos_x[1]=mvec_house[3].m_pos_x;
            mvec_pop.back().m_workpos_y[1]=mvec_house[3].m_pos_y;
            mvec_pop.back().m_productivity=0.5;
            mvec_pop.back().m_fertility=0.5;
            mvec_pop.back().m_criminality=1;
            mvec_pop.back().m_state=ps_idle;
            //fifth
            mvec_pop.push_back(pop(580,610));
            mvec_pop.back().m_currworkplace=0;
            mvec_pop.back().m_workpos_x[0]=mvec_house[0].m_pos_x;
            mvec_pop.back().m_workpos_y[0]=mvec_house[0].m_pos_y;
            mvec_pop.back().m_workpos_x[1]=mvec_house[4].m_pos_x;
            mvec_pop.back().m_workpos_y[1]=mvec_house[4].m_pos_y;
            mvec_pop.back().m_productivity=0.5;
            mvec_pop.back().m_fertility=0.5;
            mvec_pop.back().m_criminality=1;
            mvec_pop.back().m_state=ps_idle;
        }break;

        case 7://real
        {
            m_house_cost_increase=8;
            m_points_left=100;//100
            m_pop_spawn_time=20;

            //start house
            mvec_house.push_back(house(_screen_width*0.45,_screen_height*0.45,m_wag_anim));
            mvec_house.push_back(house(_screen_width*0.55,_screen_height*0.48,m_wag_anim));

            //new road
            road new_road;
            new_road.vec_x.push_back(mvec_house[0].m_pos_x);
            new_road.vec_y.push_back(mvec_house[0].m_pos_y);
            new_road.vec_x.push_back(mvec_house[1].m_pos_x);
            new_road.vec_y.push_back(mvec_house[1].m_pos_y);
            mvec_road.push_back(new_road);

            //start worker
            mvec_pop.push_back(pop(400,550));
            mvec_pop.back().m_currworkplace=0;
            mvec_pop.back().m_workpos_x[0]=mvec_house[0].m_pos_x;
            mvec_pop.back().m_workpos_y[0]=mvec_house[0].m_pos_y;
            mvec_pop.back().m_workpos_x[1]=mvec_house[1].m_pos_x;
            mvec_pop.back().m_workpos_y[1]=mvec_house[1].m_pos_y;
            mvec_pop.back().m_productivity=0.9;
            mvec_pop.back().m_fertility=0.2;
            mvec_pop.back().m_criminality=0.1;
            //second
            mvec_pop.push_back(pop(440,480));
            mvec_pop.back().m_currworkplace=1;
            mvec_pop.back().m_workpos_x[0]=mvec_house[0].m_pos_x;
            mvec_pop.back().m_workpos_y[0]=mvec_house[0].m_pos_y;
            mvec_pop.back().m_workpos_x[1]=mvec_house[1].m_pos_x;
            mvec_pop.back().m_workpos_y[1]=mvec_house[1].m_pos_y;
            mvec_pop.back().m_productivity=0.7;
            mvec_pop.back().m_fertility=0.5;
            mvec_pop.back().m_criminality=0.2;
            //third
            mvec_pop.push_back(pop(500,500));
            mvec_pop.back().m_currworkplace=0;
            mvec_pop.back().m_workpos_x[0]=mvec_house[0].m_pos_x;
            mvec_pop.back().m_workpos_y[0]=mvec_house[0].m_pos_y;
            mvec_pop.back().m_workpos_x[1]=mvec_house[1].m_pos_x;
            mvec_pop.back().m_workpos_y[1]=mvec_house[1].m_pos_y;
            mvec_pop.back().m_productivity=0.5;
            mvec_pop.back().m_fertility=0.5;
            mvec_pop.back().m_criminality=0.1;
            mvec_pop.back().m_state=ps_idle;
            //forth
            mvec_pop.push_back(pop(450,630));
            mvec_pop.back().m_currworkplace=1;
            mvec_pop.back().m_workpos_x[0]=mvec_house[0].m_pos_x;
            mvec_pop.back().m_workpos_y[0]=mvec_house[0].m_pos_y;
            mvec_pop.back().m_workpos_x[1]=mvec_house[1].m_pos_x;
            mvec_pop.back().m_workpos_y[1]=mvec_house[1].m_pos_y;
            mvec_pop.back().m_productivity=0.5;
            mvec_pop.back().m_fertility=0.5;
            mvec_pop.back().m_criminality=0.3;
            mvec_pop.back().m_state=ps_idle;
            //fifth
            mvec_pop.push_back(pop(610,610));
            mvec_pop.back().m_currworkplace=1;
            mvec_pop.back().m_workpos_x[0]=mvec_house[0].m_pos_x;
            mvec_pop.back().m_workpos_y[0]=mvec_house[0].m_pos_y;
            mvec_pop.back().m_workpos_x[1]=mvec_house[1].m_pos_x;
            mvec_pop.back().m_workpos_y[1]=mvec_house[1].m_pos_y;
            mvec_pop.back().m_productivity=0.1;
            mvec_pop.back().m_fertility=0.6;
            mvec_pop.back().m_criminality=0.9;
            mvec_pop.back().m_state=ps_idle;
        }break;
    }
    m_pop_spawn_timer=m_pop_spawn_time;
    m_house_cost=m_house_cost_increase;

    //particle setup
    if((int)mvec_particle.size()!=1000)
    {
        mvec_particle.resize(1000,particle());
    }

    //terrain generation
    int world_size=10000;
    int numof_lines=4000;
    for(int i=0;i<numof_lines;i++)
    {
        float start_pos_x=rand()%world_size-world_size*0.5;
        float start_pos_y=rand()%world_size-world_size*0.5;
        //test if close to other
        bool col=false;
        for(int j=0;j<(int)mvec_terrain_line.size();j++)
        {
            if(fabs(mvec_terrain_line[j].vec_x[0]-start_pos_x)<250 &&
               fabs(mvec_terrain_line[j].vec_y[0]-start_pos_y)<70 )
            {
                col=true;
                break;
            }
        }
        if(col) continue;//skip one line

        float length=rand()%200+50;
        int numof_points=length/20;
        float amplitude=rand()%100*0.01;
        terrain_line line;
        float hill_count=rand()%4+1;
        float y_pos=start_pos_y;
        /*line.vec_x.push_back(start_pos_x-rand()%10-10);
        line.vec_y.push_back(y_pos+rand()%10+10);
        line.vec_x.push_back(start_pos_x-rand()%10-10);
        line.vec_y.push_back(y_pos+rand()%10+10);*/
        for(int j=0;j<numof_points;j++)
        {
            float x_pos=start_pos_x+length*j/numof_points;
            line.vec_x.push_back(x_pos);
            if(j==0)
            {
                //y_pos;
            }
            else if((float)j/(float)numof_points<0.5)
            {
                y_pos-=(rand()%10)*amplitude;
            }
            else
            {
                y_pos+=(rand()%10)*amplitude;
                if(y_pos>start_pos_y) y_pos=start_pos_y;
            }
            line.vec_y.push_back(y_pos);
            //line.vec_y.push_back(start_pos_y-fabs(amplitude*sinf((float)j/(float)numof_points*hill_count*_pi)));
        }
        /*line.vec_x.push_back(start_pos_x+length+rand()%10+10);
        line.vec_y.push_back(y_pos+rand()%10+10);*/
        line.color=rand()%30*0.01+0.05;
        mvec_terrain_line.push_back(line);
    }

    screen_width=_screen_width;
    screen_height=_screen_height;



    //load texture
    if(!texture_loaded)
    {
        tex_main=SOIL_load_OGL_texture
        (
            "data\\texture\\main.png",
            SOIL_LOAD_AUTO,
            SOIL_CREATE_NEW_ID,
            SOIL_FLAG_INVERT_Y | SOIL_FLAG_COMPRESS_TO_DXT
        );
        tex_info=SOIL_load_OGL_texture
        (
            "data\\texture\\info.png",
            SOIL_LOAD_AUTO,
            SOIL_CREATE_NEW_ID,
            SOIL_FLAG_INVERT_Y | SOIL_FLAG_COMPRESS_TO_DXT
        );
        tex_gameover=SOIL_load_OGL_texture
        (
            "data\\texture\\gameover.png",
            SOIL_LOAD_AUTO,
            SOIL_CREATE_NEW_ID,
            SOIL_FLAG_INVERT_Y | SOIL_FLAG_COMPRESS_TO_DXT
        );
        tex_tut[0]=SOIL_load_OGL_texture
        (
            "data\\texture\\tut1.png",
            SOIL_LOAD_AUTO,
            SOIL_CREATE_NEW_ID,
            SOIL_FLAG_INVERT_Y | SOIL_FLAG_COMPRESS_TO_DXT
        );
        tex_tut[1]=SOIL_load_OGL_texture
        (
            "data\\texture\\tut2.png",
            SOIL_LOAD_AUTO,
            SOIL_CREATE_NEW_ID,
            SOIL_FLAG_INVERT_Y | SOIL_FLAG_COMPRESS_TO_DXT
        );
        tex_tut[2]=SOIL_load_OGL_texture
        (
            "data\\texture\\tut3.png",
            SOIL_LOAD_AUTO,
            SOIL_CREATE_NEW_ID,
            SOIL_FLAG_INVERT_Y | SOIL_FLAG_COMPRESS_TO_DXT
        );
        tex_tut[3]=SOIL_load_OGL_texture
        (
            "data\\texture\\tut4.png",
            SOIL_LOAD_AUTO,
            SOIL_CREATE_NEW_ID,
            SOIL_FLAG_INVERT_Y | SOIL_FLAG_COMPRESS_TO_DXT
        );
        tex_tut[4]=SOIL_load_OGL_texture
        (
            "data\\texture\\tut5.png",
            SOIL_LOAD_AUTO,
            SOIL_CREATE_NEW_ID,
            SOIL_FLAG_INVERT_Y | SOIL_FLAG_COMPRESS_TO_DXT
        );
        tex_tut[5]=SOIL_load_OGL_texture
        (
            "data\\texture\\tut6.png",
            SOIL_LOAD_AUTO,
            SOIL_CREATE_NEW_ID,
            SOIL_FLAG_INVERT_Y | SOIL_FLAG_COMPRESS_TO_DXT
        );
        tex_tut[6]=SOIL_load_OGL_texture
        (
            "data\\texture\\tut7.png",
            SOIL_LOAD_AUTO,
            SOIL_CREATE_NEW_ID,
            SOIL_FLAG_INVERT_Y | SOIL_FLAG_COMPRESS_TO_DXT
        );
        tex_help=SOIL_load_OGL_texture
        (
            "data\\texture\\helpbox.png",
            SOIL_LOAD_AUTO,
            SOIL_CREATE_NEW_ID,
            SOIL_FLAG_INVERT_Y | SOIL_FLAG_COMPRESS_TO_DXT
        );
        tex_win=SOIL_load_OGL_texture
        (
            "data\\texture\\win.png",
            SOIL_LOAD_AUTO,
            SOIL_CREATE_NEW_ID,
            SOIL_FLAG_INVERT_Y | SOIL_FLAG_COMPRESS_TO_DXT
        );
        tex_nextlevel=SOIL_load_OGL_texture
        (
            "data\\texture\\next_level.png",
            SOIL_LOAD_AUTO,
            SOIL_CREATE_NEW_ID,
            SOIL_FLAG_INVERT_Y | SOIL_FLAG_COMPRESS_TO_DXT
        );
        if(tex_main==0 || tex_info==0 || tex_gameover==0 || tex_help==0 || tex_win==0 || tex_nextlevel==0 ||
           tex_tut[0]==0 || tex_tut[1]==0 || tex_tut[2]==0 || tex_tut[3]==0 ||
           tex_tut[4]==0 || tex_tut[5]==0 || tex_tut[6]==0 )
        {
            cout<<"ERROR: Could not load textures\n";
            return false;
        }
        else texture_loaded=true;
    }

    //load sound
    if(!sound_loaded)
    {
        pSound=new sound();
        bool error_flag=false;
        if( !pSound->load_WAVE_from_file( wav_flash1,"data\\sound\\flash1.wav" ) ) error_flag=true;
        if( !pSound->load_WAVE_from_file( wav_flash2,"data\\sound\\flash2.wav" ) ) error_flag=true;
        if( !pSound->load_WAVE_from_file( wav_flash3,"data\\sound\\flash3.wav" ) ) error_flag=true;
        if( !pSound->load_WAVE_from_file( wav_background,"data\\sound\\background.wav" ) ) error_flag=true;
        if( !pSound->load_WAVE_from_file( wav_spawn,"data\\sound\\spawn.wav" ) ) error_flag=true;
        if( !pSound->load_WAVE_from_file( wav_hurt,"data\\sound\\hurt.wav" ) ) error_flag=true;
        if( !pSound->load_WAVE_from_file( wav_build,"data\\sound\\build.wav" ) ) error_flag=true;
        if(error_flag)
        {
            cout<<"ERROR: Could not load sounds\n";
            //return false;
        }

        sound_loaded=true;
    }

    //play music
    pSound->playSimpleSound(wav_background,1,10,true);

    if(m_logging) logfile<<"2";

    return true;
}

bool game::update()
{
    if(game_state==gs_main)
    {
        /*//check for input to continue
        if(mouse_but[0])
        {
            if(!lmb_pressed)
            {
                lmb_pressed=true;
                game_state=gs_info;
            }
        }
        else lmb_pressed=false;*/

        //input keys
        for(int i=0;i<256;i++)
        {
            if(keys[i] && i!=inactive_button)
            {
                //cout<<i<<endl;
                inactive_button=i;
                //enter random char
                char input;
                switch(rand()%4)
                {
                    case 0: input='A'; break;
                    case 1: input='T'; break;
                    case 2: input='G'; break;
                    case 3: input='C'; break;
                }
                genetic_data.append(1,input);
                break;
            }
        }

        if((int)genetic_data.size()>=951 || ((int)genetic_data.size()>1 && keys[13]))
        {
            game_state=gs_info;
        }

        return true;
    }

    if(game_state==gs_info)
    {
        //check for input to continue
        if(mouse_but[0])
        {
            if(!lmb_pressed)
            {
                lmb_pressed=true;
                game_state=gs_run;

                //first click fix
                mouse_but[0]=false;
            }
        }
        else lmb_pressed=false;

        return true;
    }

    if(game_state==gs_gameover)
    {
        //check for input to continue
        if(mouse_but[0])
        {
            if(!lmb_pressed)
            {
                //reset
                reset();

                lmb_pressed=true;
                game_state=gs_run;

                //first click fix
                mouse_but[0]=false;
            }
        }
        else lmb_pressed=false;

        return true;
    }

    if(game_state==gs_win)
    {
        //check for input to continue
        if(mouse_but[0])
        {
            if(!lmb_pressed)
            {
                //reset
                genetic_data="";
                game_level=1;
                reset();

                lmb_pressed=true;
                game_state=gs_main;

                //first click fix
                mouse_but[0]=false;
            }
        }
        else lmb_pressed=false;

        return true;
    }

    if(game_state==gs_nextlevel)
    {
        //check for input to continue
        if(mouse_but[0])
        {
            if(!lmb_pressed)
            {
                lmb_pressed=true;
                game_state=gs_run;

                //first click fix
                mouse_but[0]=false;
            }
        }
        else lmb_pressed=false;

        for(int i=0;i<256;i++)
        {
            if(keys[i])
            {
                game_state=gs_run;
                break;
            }
        }

        return true;
    }

    //show help
    if(keys[32] || keys[9])
    {
        draw_help=true;

        return true;
    }
    else draw_help=false;

    if(m_logging) logfile<<"3";

    mouse_pos_world[0]=mouse_pos[0]-m_cam_pos_x;
    mouse_pos_world[1]=mouse_pos[1]-m_cam_pos_y;

    //common wag anim
    m_wag_anim+=_time_dif*0.2;
    if(m_wag_anim>1) m_wag_anim-=1;

    //screen shake
    if(m_shake_timer>0) m_shake_timer-=_time_dif;

    //win test
    if(m_points_left<=0)
    {
        //next level
        game_level++;
        reset();
        game_state=gs_nextlevel;

        if(game_level>7)
        {
            game_state=gs_win;
            //return true;
        }
        return true;

    }
    //game over test
    if((int)mvec_pop.size()<1)
    {
        game_state=gs_gameover;
    }

    //mouse drag
    if(mouse_but[0] && lmb_pressed)
    {
        m_cam_pos_x+=mouse_pos[0]-mouse_pos_last[0];
        m_cam_pos_y+=mouse_pos[1]-mouse_pos_last[1];

        mouse_pos_last[0]=mouse_pos[0];
        mouse_pos_last[1]=mouse_pos[1];
    }

    //selected statsview test
    if(mouse_but[0] && !lmb_pressed)
    {
        lmb_pressed=true;
        mouse_pos_last[0]=mouse_pos[0];
        mouse_pos_last[1]=mouse_pos[1];

        bool pop_found=false;
        for(int i=0;i<(int)mvec_pop.size();i++)
        {
            if(fabs(mouse_pos_world[0]-mvec_pop[i].m_pos_x)<mvec_pop[i].m_size &&
               fabs(mouse_pos_world[1]-mvec_pop[i].m_pos_y)<mvec_pop[i].m_size )
            {
                pop_found=true;

                //if already selected, make a copy
                if(m_locked_statsview && m_locked_statsview_ind==i && game_level>=3)
                {
                    //play sound
                    pSound->playSimpleSound(wav_spawn,0.2);

                    spawn_pop(i);
                    m_points_left+=2;

                    //particle spawn
                    int particles_to_spawn=20;
                    for(int j=0;j<(int)mvec_particle.size() && particles_to_spawn>0;j++)
                    {
                        if(mvec_particle[j].type==0)
                        {
                            particles_to_spawn--;

                            float xpos=mvec_pop[i].m_pos_x+rand()%61-30;
                            float ypos=mvec_pop[i].m_pos_y+rand()%31-5;

                            float time_factor=4;
                            float xdir=(mvec_pop[i].m_pos_x+rand()%11-5-xpos)*_time_dif*time_factor;
                            float ydir=(mvec_pop[i].m_pos_y+rand()%11-5-ypos)*_time_dif*time_factor;
                            float length=sqrt(xdir*xdir+ydir*ydir);
                            float age=1/time_factor;
                            float ystart=mvec_pop[i].m_pos_y+rand()%100*0.1-5;
                            float color=rand()%30*0.01+0.4;

                            mvec_particle[j]=particle(xpos,ypos,
                                                      ystart,xdir,ydir,2,color,color,color,age);
                        }
                    }
                }
                else
                {
                    m_locked_statsview=true;
                    m_locked_statsview_ind=i;
                }
                break;
            }
        }
        if(!pop_found)
        {
            m_locked_statsview=false;
        }
    }
    if(!mouse_but[0]) lmb_pressed=false;

    if(m_logging) logfile<<"4";

    //selected kill test RMB
    if(mouse_but[1] && !rmb_pressed)
    {
        rmb_pressed=true;

        for(int i=0;i<(int)mvec_pop.size();i++)
        {
            if(fabs(mouse_pos_world[0]-mvec_pop[i].m_pos_x)<mvec_pop[i].m_size &&
               fabs(mouse_pos_world[1]-mvec_pop[i].m_pos_y)<mvec_pop[i].m_size )
            {
                //sound
                switch(rand()%3)
                {
                    case 0: pSound->playSimpleSound(wav_flash1,1); break;
                    case 1: pSound->playSimpleSound(wav_flash2,1); break;
                    case 2: pSound->playSimpleSound(wav_flash3,1); break;
                }

                //shake
                m_shake_timer=_shake_time;

                //particles
                int particles_to_spawn=100;
                for(int j=0;j<(int)mvec_particle.size() && particles_to_spawn>0;j++)
                {
                    if(mvec_particle[j].type==0)
                    {
                        particles_to_spawn--;

                        float xdir=rand()%100*0.02-1;
                        float ydir=rand()%100*-0.02;
                        float ystart=mvec_pop[i].m_pos_y+rand()%100*0.1-5;
                        float age=rand()%100*0.010+0.1;
                        float r=rand()%30*0.01+0.7;
                        float g=rand()%50*0.01;
                        float b=rand()%50*0.01;

                        mvec_particle[j]=particle(mvec_pop[i].m_pos_x+rand()%100*0.10-5,mvec_pop[i].m_pos_y+rand()%100*0.10-5,
                                                  ystart,xdir,ydir,1,r,g,b,age);
                    }
                }

                //flash
                flash new_flash;
                new_flash.vec_x.push_back(mvec_pop[i].m_pos_x);
                new_flash.vec_y.push_back(mvec_pop[i].m_pos_y);
                int edges=rand()%4+3;
                for(int j=1;j<edges;j++)
                {
                    new_flash.vec_x.push_back(mvec_pop[i].m_pos_x+rand()%61-30);
                    new_flash.vec_y.push_back(mouse_pos_world[1]-mouse_pos[1]/edges*j);
                }
                new_flash.vec_x.push_back(mvec_pop[i].m_pos_x+rand()%61-30);
                new_flash.vec_y.push_back(-999999);
                new_flash.age=0.7;
                mvec_flash.push_back(new_flash);


                mvec_pop.erase(mvec_pop.begin()+i);
                i--;
                m_locked_statsview=false;

                //points
                m_points_left--;
                if(m_points_left<0) m_points_left=0;

                break;
            }
        }
    }
    if(!mouse_but[1]) rmb_pressed=false;

    if(m_logging) logfile<<"5";

    //spawn house
    if(m_res_count>m_house_cost)
    {
        cout<<"cost goal reached\n";
        m_house_cost+=m_house_cost_increase;
        m_res_count=0;

        //place near another house
        int try_count=0;
        while(true)
        {
            if(try_count++>100) break;

            int seleced_house=rand()%(int)mvec_house.size();
            float dist=rand()%50+20;
            float rot=rand()%360;
            float new_x=mvec_house[seleced_house].m_pos_x+dist*cosf(rot*_deg2rad);
            float new_y=mvec_house[seleced_house].m_pos_y+dist*sinf(rot*_deg2rad);
            //cout<<new_x<<", "<<new_y<<endl;

            //test if collision with other house
            bool col=false;
            for(int i=0;i<(int)mvec_house.size();i++)
            {

                if(fabs(new_x-mvec_house[i].m_pos_x)<mvec_house[i].m_size+30 &&
                   fabs(new_y-mvec_house[i].m_pos_y)<mvec_house[i].m_size+30 )
                {
                    col=true;
                    break;
                }
            }
            if(!col)
            {
                //spawn new house
                mvec_house.push_back(house(new_x,new_y,m_wag_anim));
                //cout<<new_x<<", "<<new_y<<endl;

                //sound
                pSound->playSimpleSound(wav_build,1);

                //new road
                road new_road;
                new_road.vec_x.push_back(mvec_house[seleced_house].m_pos_x);
                new_road.vec_y.push_back(mvec_house[seleced_house].m_pos_y);
                new_road.vec_x.push_back(new_x);
                new_road.vec_y.push_back(new_y);
                mvec_road.push_back(new_road);

                //and a new pop
                spawn_pop(-1,true,new_x,new_y);

                break;//the loop
            }
        }
    }

    if(m_logging) logfile<<"6";

    //crime event
    for(int i=0;i<(int)mvec_pop.size();i++)
    {
        if(mvec_pop[i].m_crime_timer<=0)
        {
            mvec_pop[i].m_crime_timer=_crime_time;
            //do crime test
            if(rand()%100<mvec_pop[i].m_criminality*100)
            {
                //see if any other pop within range
                float range=30;
                for(int j=0;j<(int)mvec_pop.size();j++)
                {
                    if(i==j) continue;
                    if(fabs(mvec_pop[i].m_pos_x-mvec_pop[j].m_pos_x)<range &&
                       fabs(mvec_pop[i].m_pos_y-mvec_pop[j].m_pos_y)<range)
                    {
                        //sound
                        pSound->playSimpleSound(wav_hurt,1);

                        //particles
                        int particles_to_spawn=50;
                        for(int j=0;j<(int)mvec_particle.size() && particles_to_spawn>0;j++)
                        {
                            if(mvec_particle[j].type==0)
                            {
                                particles_to_spawn--;

                                float xdir=rand()%50*0.01-0.25;
                                float ydir=rand()%100*-0.02;
                                float ystart=mvec_pop[i].m_pos_y+rand()%100*0.1-5;
                                float age=rand()%100*0.010+0.2;
                                float r=rand()%30*0.01+0.7;
                                float g=rand()%50*0.01;
                                float b=rand()%50*0.01;

                                mvec_particle[j]=particle(mvec_pop[i].m_pos_x+rand()%100*0.10-5,mvec_pop[i].m_pos_y+rand()%100*0.10-5,
                                                          ystart,xdir,ydir,1,r,g,b,age);
                            }
                        }

                        //murder event
                        cout<<"A crime was committed\n";
                        if(m_locked_statsview_ind==j) m_locked_statsview=false;
                        if(m_locked_statsview_ind>j) m_locked_statsview_ind--;
                        mvec_pop.erase(mvec_pop.begin()+j);
                        if(j<i) i--;

                        break;
                    }
                }
            }
        }
    }

    if(m_logging) logfile<<"7";

    //spawn pop based on fertility
    for(int i=0;i<(int)mvec_pop.size();i++)
    {
        if(mvec_pop[i].m_birth_timer<=0)
        {
            mvec_pop[i].m_birth_timer=_birth_time;
            //do birth test
            if(rand()%100<mvec_pop[i].m_fertility*100)
            {
                spawn_pop(i);
            }
        }
    }

    if(m_logging) logfile<<"8";

    //random spawn pop at other pop
    if(m_pop_spawn_timer<=0 && (int)mvec_pop.size()>0)
    {
        m_pop_spawn_timer=m_pop_spawn_time;
        int seleced_pop=rand()%(int)mvec_pop.size();
        spawn_pop(seleced_pop);
    }
    else m_pop_spawn_timer-=_time_dif;

    if(m_logging) logfile<<"9";


    //update houses
    for(int i=0;i<(int)mvec_house.size();i++)
    {
        mvec_house[i].update(m_wag_anim);
    }

    //update pops
    for(int i=0;i<(int)mvec_pop.size();i++)
    {
        int retval=mvec_pop[i].update();
        switch(retval)
        {
            case 0: //normal return
            {

            }break;

            case 1: //work return
            {
                m_res_count++;

            }break;

            case 2: //death by age
            {
                cout<<"a pop died of age\n";
                mvec_pop.erase(mvec_pop.begin()+i);
                if(m_locked_statsview_ind==i) m_locked_statsview=false;
                if(i<m_locked_statsview_ind) m_locked_statsview_ind--;
                i--;
                continue;
            }break;
        }

        /*//outside map test
        if(mvec_pop[i].m_pos_x+mvec_pop[i].m_size<0 ||
           mvec_pop[i].m_pos_x-mvec_pop[i].m_size>screen_width ||
           mvec_pop[i].m_pos_y+mvec_pop[i].m_size<0 ||
           mvec_pop[i].m_pos_y-mvec_pop[i].m_size>screen_height)
        {
            //delete
            mvec_pop.erase(mvec_pop.begin()+i);
            i--;
            cout<<"pop removed due to outside of map\n";
        }*/
    }

    if(m_logging) logfile<<"10";

    if((int)mvec_pop.size()<1) return false; //game over

    //update max/min stats
    m_speed_min=m_speed_max=mvec_pop[0].m_speed;
    m_age_min=m_age_max=mvec_pop[0].m_age_start;
    m_prod_min=m_prod_max=mvec_pop[0].m_productivity;
    m_fert_min=m_fert_max=mvec_pop[0].m_fertility;
    m_crime_min=m_crime_max=mvec_pop[0].m_criminality;
    for(int i=0;i<(int)mvec_pop.size();i++)
    {
        if(mvec_pop[i].m_speed>m_speed_max) m_speed_max=mvec_pop[i].m_speed;
        if(mvec_pop[i].m_speed<m_speed_min) m_speed_min=mvec_pop[i].m_speed;
        if(mvec_pop[i].m_age_start>m_age_max) m_age_max=mvec_pop[i].m_age_start;
        if(mvec_pop[i].m_age_start<m_age_min) m_age_min=mvec_pop[i].m_age_start;
        if(mvec_pop[i].m_productivity>m_prod_max) m_prod_max=mvec_pop[i].m_productivity;
        if(mvec_pop[i].m_productivity<m_prod_min) m_prod_min=mvec_pop[i].m_productivity;
        if(mvec_pop[i].m_fertility>m_fert_max) m_fert_max=mvec_pop[i].m_fertility;
        if(mvec_pop[i].m_fertility<m_fert_min) m_fert_min=mvec_pop[i].m_fertility;
        if(mvec_pop[i].m_criminality>m_crime_max) m_crime_max=mvec_pop[i].m_criminality;
        if(mvec_pop[i].m_criminality<m_crime_min) m_crime_min=mvec_pop[i].m_criminality;
    }

    /*//TEMP mouse part spawner
    for(int i=0;i<(int)mvec_particle.size();i++)
    {
        if(mvec_particle[i].type==0)
        {
            float xdir=rand()%100*0.02-1;
            float ydir=rand()%100*-0.04;
            float ystart=mouse_pos_world[1]+rand()%100*0.1-5;

            mvec_particle[i]=particle(mouse_pos_world[0],mouse_pos_world[1],ystart,xdir,ydir,1,1,1,1,0.3);
            break;
        }
    }*/

    //update flashes
    for(int i=0;i<(int)mvec_flash.size();i++)
    {
        if(mvec_flash[i].age>0)
        {
            mvec_flash[i].age-=_time_dif;
            if(mvec_flash[i].age<=0)
            {
                mvec_flash[i].vec_x.clear();
                mvec_flash[i].vec_y.clear();
            }
        }
    }

    //update particles
    for(int i=0;i<(int)mvec_particle.size();i++)
    {
        switch(mvec_particle[i].type)
        {
            case 0://off
            {
                ;
            }break;

            case 1://explosion
            {
                mvec_particle[i].age-=_time_dif;
                if(mvec_particle[i].age<=0)  mvec_particle[i].type=0;

                //pos update (on ground test)
                if(mvec_particle[i].y<mvec_particle[i].y_start)
                {
                    mvec_particle[i].x+=mvec_particle[i].x_dir;
                    mvec_particle[i].y+=mvec_particle[i].y_dir;
                    //gravity
                    mvec_particle[i].y_dir+=0.1;
                }
            }break;

            case 2://birth
            {
                mvec_particle[i].age-=_time_dif;
                if(mvec_particle[i].age<=0)  mvec_particle[i].type=0;

                mvec_particle[i].x+=mvec_particle[i].x_dir;
                mvec_particle[i].y+=mvec_particle[i].y_dir;
                if(mvec_particle[i].r<1)
                {
                    mvec_particle[i].r=mvec_particle[i].g=mvec_particle[i].b+=_time_dif*4;
                }
            }break;
        }
    }

    if(m_logging) logfile<<"11\n";

    return true;
}

bool game::draw()
{
    if(m_logging) logfile<<"12";

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1,1,1);

    glPushMatrix();

    if(game_state==gs_main)
    {
        glPushMatrix();
        glTranslatef(0,15,0);
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D,tex_main);
        glColor3f(1,1,1);
        glBegin(GL_QUADS);
        glTexCoord2f(0.0,1.0);
        glVertex2f(0,0);
        glTexCoord2f(0.0,0.0);
        glVertex2f(0,screen_height);
        glTexCoord2f(1.0,0.0);
        glVertex2f(screen_width,screen_height);
        glTexCoord2f(1.0,1.0);
        glVertex2f(screen_width,0);
        glEnd();
        glDisable(GL_TEXTURE_2D);
        glPopMatrix();

        //draw dna
        glPushMatrix();
        glTranslatef(15,65,0);
        glLineWidth(2);
        glColor3f(0.8,0.8,0.8);
        glScalef(20,20,20);
        int counter=0;
        int cut_val=37;
        for(int i=0;i<(int)genetic_data.size();i++)
        {
            counter++;
            draw_number(genetic_data[i]);
            glTranslatef(1.3,0,0);
            if(counter>cut_val)
            {
                counter=0;
                glTranslatef(-1.3*(cut_val+1),1.4,0);
            }
        }
        glLineWidth(1);
        glPopMatrix();

        return true;
    }

    if(game_state==gs_info)
    {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D,tex_info);
        glColor3f(1,1,1);
        glBegin(GL_QUADS);
        glTexCoord2f(0.0,1.0);
        glVertex2f(0,0);
        glTexCoord2f(0.0,0.0);
        glVertex2f(0,screen_height);
        glTexCoord2f(1.0,0.0);
        glVertex2f(screen_width,screen_height);
        glTexCoord2f(1.0,1.0);
        glVertex2f(screen_width,0);
        glEnd();
        glDisable(GL_TEXTURE_2D);

        return true;
    }

    if(game_state==gs_gameover)
    {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D,tex_gameover);
        glColor3f(1,1,1);
        glBegin(GL_QUADS);
        glTexCoord2f(0.0,1.0);
        glVertex2f(0,0);
        glTexCoord2f(0.0,0.0);
        glVertex2f(0,screen_height);
        glTexCoord2f(1.0,0.0);
        glVertex2f(screen_width,screen_height);
        glTexCoord2f(1.0,1.0);
        glVertex2f(screen_width,0);
        glEnd();
        glDisable(GL_TEXTURE_2D);

        /*//draw score HUD
        int minutes_passed=int( game_timer/60.0 );
        stringstream ss;
        ss<<minutes_passed;
        string minutes_pased_string(ss.str());

        glPushMatrix();
        glTranslatef(screen_width-22,48,0);
        glLineWidth(2);
        glColor3f(0.8,0.8,0.8);
        glScalef(20,20,20);
        for(int i=(int)minutes_pased_string.size();i>=0;i--)
        {
            draw_number(minutes_pased_string[i]);
            glTranslatef(-1.3,0,0);
        }
        glLineWidth(1);
        glPopMatrix();*/

        return true;
    }

    if(game_state==gs_win)
    {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D,tex_win);
        glColor3f(1,1,1);
        glBegin(GL_QUADS);
        glTexCoord2f(0.0,1.0);
        glVertex2f(0,0);
        glTexCoord2f(0.0,0.0);
        glVertex2f(0,screen_height);
        glTexCoord2f(1.0,0.0);
        glVertex2f(screen_width,screen_height);
        glTexCoord2f(1.0,1.0);
        glVertex2f(screen_width,0);
        glEnd();
        glDisable(GL_TEXTURE_2D);

        return true;
    }

    if(game_state==gs_nextlevel)
    {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D,tex_nextlevel);
        glColor3f(1,1,1);
        glBegin(GL_QUADS);
        glTexCoord2f(0.0,1.0);
        glVertex2f(0,0);
        glTexCoord2f(0.0,0.0);
        glVertex2f(0,screen_height);
        glTexCoord2f(1.0,0.0);
        glVertex2f(screen_width,screen_height);
        glTexCoord2f(1.0,1.0);
        glVertex2f(screen_width,0);
        glEnd();
        glDisable(GL_TEXTURE_2D);

        return true;
    }

    if(draw_help)
    {
        glPushMatrix();
        glTranslatef(0,15,0);
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D,tex_help);
        glColor3f(1,1,1);
        glBegin(GL_QUADS);
        glTexCoord2f(0.0,1.0);
        glVertex2f(0,0);
        glTexCoord2f(0.0,0.0);
        glVertex2f(0,screen_height);
        glTexCoord2f(1.0,0.0);
        glVertex2f(screen_width,screen_height);
        glTexCoord2f(1.0,1.0);
        glVertex2f(screen_width,0);
        glEnd();
        glDisable(GL_TEXTURE_2D);
        glPopMatrix();

        //hide text
        switch(game_level)
        {
            case 1:
            {
                glColor3f(0,0,0);
                glBegin(GL_QUADS);
                glVertex2f(0,670);
                glVertex2f(0,screen_height);
                glVertex2f(screen_width,screen_height);
                glVertex2f(screen_width,670);
                glEnd();

                glColor3f(0,0,0);
                glBegin(GL_QUADS);
                glVertex2f(0,450);
                glVertex2f(0,515);
                glVertex2f(screen_width,515);
                glVertex2f(screen_width,450);
                glEnd();
            }break;

            case 2:
            {
                glColor3f(0,0,0);
                glBegin(GL_QUADS);
                glVertex2f(0,688);
                glVertex2f(0,screen_height);
                glVertex2f(screen_width,screen_height);
                glVertex2f(screen_width,688);
                glEnd();

                glColor3f(0,0,0);
                glBegin(GL_QUADS);
                glVertex2f(0,450);
                glVertex2f(0,515);
                glVertex2f(screen_width,515);
                glVertex2f(screen_width,450);
                glEnd();
            }break;

            case 3:
            {
                glColor3f(0,0,0);
                glBegin(GL_QUADS);
                glVertex2f(0,688);
                glVertex2f(0,screen_height);
                glVertex2f(screen_width,screen_height);
                glVertex2f(screen_width,688);
                glEnd();

                glColor3f(0,0,0);
                glBegin(GL_QUADS);
                glVertex2f(0,450);
                glVertex2f(0,515);
                glVertex2f(screen_width,515);
                glVertex2f(screen_width,450);
                glEnd();
            }break;

            case 4:
            {
                glColor3f(0,0,0);
                glBegin(GL_QUADS);
                glVertex2f(0,716);
                glVertex2f(0,screen_height);
                glVertex2f(screen_width,screen_height);
                glVertex2f(screen_width,716);
                glEnd();

                glColor3f(0,0,0);
                glBegin(GL_QUADS);
                glVertex2f(0,450);
                glVertex2f(0,515);
                glVertex2f(screen_width,515);
                glVertex2f(screen_width,450);
                glEnd();
            }break;

            case 5:
            {
                glColor3f(0,0,0);
                glBegin(GL_QUADS);
                glVertex2f(0,739);
                glVertex2f(0,screen_height);
                glVertex2f(screen_width,screen_height);
                glVertex2f(screen_width,739);
                glEnd();
            }break;
        }

        return true;
    }


    //view translation
    glTranslatef(m_cam_pos_x,m_cam_pos_y,0);

    //translate shake
    if(m_shake_timer>0)
    {
        float range=10*m_shake_timer/_shake_time;
        float x_move=rand()%int(range+1)-range/2;
        float y_move=rand()%int(range+1)-range/2;
        glTranslatef(x_move,y_move,0);
    }

    //draw terrain
    float topshift=sinf(m_wag_anim*2*_pi)*5;
    for(int i=0;i<(int)mvec_terrain_line.size();i++)
    {
        int line_counter=0;
        glColor3f(mvec_terrain_line[i].color,mvec_terrain_line[i].color,mvec_terrain_line[i].color);
        glBegin(GL_LINE_STRIP);
        for(int j=0;j<(int)mvec_terrain_line[i].vec_x.size();j++)
        {
            line_counter++;
            if(line_counter>3 && j<(int)mvec_terrain_line[i].vec_x.size()-3)
             glVertex2f(mvec_terrain_line[i].vec_x[j]+topshift,mvec_terrain_line[i].vec_y[j]);
            else
             glVertex2f(mvec_terrain_line[i].vec_x[j],mvec_terrain_line[i].vec_y[j]);
        }
        glEnd();
    }

    //draw road
    glLineWidth(3);
    for(int i=0;i<(int)mvec_road.size();i++)
    {
        float color=0.5;
        glColor3f(color,color,color);
        glBegin(GL_LINE_STRIP);
        for(int j=0;j<(int)mvec_road[i].vec_x.size();j++)
            glVertex2f(mvec_road[i].vec_x[j],mvec_road[i].vec_y[j]);
        glEnd();
    }
    glLineWidth(1);

    //draw pops
    for(int i=0;i<(int)mvec_pop.size();i++)
    {
        mvec_pop[i].draw();
    }

    //draw houses
    for(int i=0;i<(int)mvec_house.size();i++)
    {
        mvec_house[i].draw();
    }

    if(m_logging) logfile<<"13";

    //draw mouse cursor
    glColor3f(1,1,1);
    glBegin(GL_POINTS);
    glVertex2f(mouse_pos_world[0],mouse_pos_world[1]);
    glEnd();

    //draw particles
    glBegin(GL_POINTS);
    for(int i=0;i<(int)mvec_particle.size();i++)
    {
        if(mvec_particle[i].type!=0)
        {
            glColor3f(mvec_particle[i].r,mvec_particle[i].g,mvec_particle[i].b);
            glVertex2f(mvec_particle[i].x,mvec_particle[i].y);
        }
    }
    glEnd();

    //draw flash
    for(int i=0;i<(int)mvec_flash.size();i++)
    {
        float color=mvec_flash[i].age/0.2;
        if(color>1) color=1;
        glColor3f(color,color,color);
        glBegin(GL_LINE_STRIP);
        for(int j=0;j<(int)mvec_flash[i].vec_x.size();j++)
            glVertex2f(mvec_flash[i].vec_x[j],mvec_flash[i].vec_y[j]);
        glEnd();
    }

    //draw pop stats
    int pop_ind=-1;
    for(int i=0;i<(int)mvec_pop.size();i++)
    {
        if(fabs(mouse_pos_world[0]-mvec_pop[i].m_pos_x)<mvec_pop[i].m_size &&
           fabs(mouse_pos_world[1]-mvec_pop[i].m_pos_y)<mvec_pop[i].m_size )
        {
            pop_ind=i;
            break;
        }
    }
    if(m_locked_statsview) pop_ind=m_locked_statsview_ind;
    if(pop_ind!=-1)
    {
        //calc bar pos
        float bar_length=25;
        float bar_speed=0;
        if(m_speed_max-m_speed_min!=0) bar_speed=((mvec_pop[pop_ind].m_speed-m_speed_min)/(m_speed_max-m_speed_min)-0.5)*2;
        float bar_prod=(mvec_pop[pop_ind].m_productivity-0.5)*2;
        //if(m_prod_max-m_prod_min!=0) bar_prod=((mvec_pop[pop_ind].m_productivity-m_prod_min)/(m_prod_max-m_prod_min)-0.5)*2;
        float bar_age=0;
        if(m_age_max-m_age_min!=0) bar_age=((mvec_pop[pop_ind].m_age_start-m_age_min)/(m_age_max-m_age_min)-0.5)*2;
        float bar_fert=(mvec_pop[pop_ind].m_fertility-0.5)*2;
        //if(m_fert_max-m_fert_min!=0) bar_fert=((mvec_pop[pop_ind].m_fertility-m_fert_min)/(m_fert_max-m_fert_min)-0.5)*2;
        float bar_crime=(1-mvec_pop[pop_ind].m_criminality-0.5)*2;
        //if(m_crime_max-m_crime_min!=0) bar_crime=((mvec_pop[pop_ind].m_criminality-m_crime_min)/(m_crime_max-m_crime_min)-0.5)*2;

        glPushMatrix();
        glTranslatef(mvec_pop[pop_ind].m_pos_x,mvec_pop[pop_ind].m_pos_y,0);
        switch(game_level)
        {
            case 1:
            {
                //box
                glColor3f(0.3,0.3,0.3);
                glBegin(GL_QUADS);
                glVertex2f(-28,-20);
                glVertex2f(-28,-10);
                glVertex2f(28,-10);
                glVertex2f(28,-20);
                glEnd();
                //frame
                glColor3f(0.8,0.8,0.8);
                glBegin(GL_LINE_STRIP);
                glVertex2f(-28,-20);
                glVertex2f(-28,-10);
                glVertex2f(28,-10);
                glVertex2f(28,-20);
                glVertex2f(-28,-20);
                glEnd();
                //speed
                glColor3f(1,1,0);
                glBegin(GL_LINES);
                glVertex2f(-bar_length,-15);
                glVertex2f(bar_length,-15);
                glVertex2f(bar_length*bar_speed,-17);
                glVertex2f(bar_length*bar_speed,-13);
                glEnd();

            }break;

            case 2:
            {
                //box
                glColor3f(0.3,0.3,0.3);
                glBegin(GL_QUADS);
                glVertex2f(-28,-25);
                glVertex2f(-28,-10);
                glVertex2f(28,-10);
                glVertex2f(28,-25);
                glEnd();
                //frame
                glColor3f(0.8,0.8,0.8);
                glBegin(GL_LINE_STRIP);
                glVertex2f(-28,-25);
                glVertex2f(-28,-10);
                glVertex2f(28,-10);
                glVertex2f(28,-25);
                glVertex2f(-28,-25);
                glEnd();
                //speed
                glColor3f(1,1,0);
                glBegin(GL_LINES);
                glVertex2f(-bar_length,-20);
                glVertex2f(bar_length,-20);
                glVertex2f(bar_length*bar_speed,-22);
                glVertex2f(bar_length*bar_speed,-18);
                glEnd();
                //prod
                glColor3f(1.0,0.6,1);
                glBegin(GL_LINES);
                glVertex2f(-bar_length,-15);
                glVertex2f(bar_length,-15);
                glVertex2f(bar_length*bar_prod,-17);
                glVertex2f(bar_length*bar_prod,-13);
                glEnd();

            }break;

            case 3:
            {
                //box
                glColor3f(0.3,0.3,0.3);
                glBegin(GL_QUADS);
                glVertex2f(-28,-25);
                glVertex2f(-28,-10);
                glVertex2f(28,-10);
                glVertex2f(28,-25);
                glEnd();
                //frame
                glColor3f(0.8,0.8,0.8);
                glBegin(GL_LINE_STRIP);
                glVertex2f(-28,-25);
                glVertex2f(-28,-10);
                glVertex2f(28,-10);
                glVertex2f(28,-25);
                glVertex2f(-28,-25);
                glEnd();
                //speed
                glColor3f(1,1,0);
                glBegin(GL_LINES);
                glVertex2f(-bar_length,-20);
                glVertex2f(bar_length,-20);
                glVertex2f(bar_length*bar_speed,-22);
                glVertex2f(bar_length*bar_speed,-18);
                glEnd();
                //prod
                glColor3f(1.0,0.6,1);
                glBegin(GL_LINES);
                glVertex2f(-bar_length,-15);
                glVertex2f(bar_length,-15);
                glVertex2f(bar_length*bar_prod,-17);
                glVertex2f(bar_length*bar_prod,-13);
                glEnd();

            }break;

            case 4://age
            {
                //box
                glColor3f(0.3,0.3,0.3);
                glBegin(GL_QUADS);
                glVertex2f(-28,-30);
                glVertex2f(-28,-10);
                glVertex2f(28,-10);
                glVertex2f(28,-30);
                glEnd();
                //frame
                glColor3f(0.8,0.8,0.8);
                glBegin(GL_LINE_STRIP);
                glVertex2f(-28,-30);
                glVertex2f(-28,-10);
                glVertex2f(28,-10);
                glVertex2f(28,-30);
                glVertex2f(-28,-30);
                glEnd();
                //speed
                glColor3f(1,1,0);
                glBegin(GL_LINES);
                glVertex2f(-bar_length,-25);
                glVertex2f(bar_length,-25);
                glVertex2f(bar_length*bar_speed,-27);
                glVertex2f(bar_length*bar_speed,-23);
                glEnd();
                //prod
                glColor3f(1.0,0.6,1);
                glBegin(GL_LINES);
                glVertex2f(-bar_length,-20);
                glVertex2f(bar_length,-20);
                glVertex2f(bar_length*bar_prod,-22);
                glVertex2f(bar_length*bar_prod,-18);
                glEnd();
                //age/health
                glColor3f(0,1,0);
                glBegin(GL_LINES);
                glVertex2f(-bar_length,-15);
                glVertex2f(bar_length,-15);
                glVertex2f(bar_length*bar_age,-17);
                glVertex2f(bar_length*bar_age,-13);
                glEnd();

            }break;

            case 5:
            {
                //box
                glColor3f(0.3,0.3,0.3);
                glBegin(GL_QUADS);
                glVertex2f(-28,-35);
                glVertex2f(-28,-10);
                glVertex2f(28,-10);
                glVertex2f(28,-35);
                glEnd();
                //frame
                glColor3f(0.8,0.8,0.8);
                glBegin(GL_LINE_STRIP);
                glVertex2f(-28,-35);
                glVertex2f(-28,-10);
                glVertex2f(28,-10);
                glVertex2f(28,-35);
                glVertex2f(-28,-35);
                glEnd();
                //speed
                glColor3f(1,1,0);
                glBegin(GL_LINES);
                glVertex2f(-bar_length,-30);
                glVertex2f(bar_length,-30);
                glVertex2f(bar_length*bar_speed,-32);
                glVertex2f(bar_length*bar_speed,-28);
                glEnd();
                //prod
                glColor3f(1.0,0.6,1);
                glBegin(GL_LINES);
                glVertex2f(-bar_length,-25);
                glVertex2f(bar_length,-25);
                glVertex2f(bar_length*bar_prod,-27);
                glVertex2f(bar_length*bar_prod,-23);
                glEnd();
                //age/health
                glColor3f(0,1,0);
                glBegin(GL_LINES);
                glVertex2f(-bar_length,-20);
                glVertex2f(bar_length,-20);
                glVertex2f(bar_length*bar_age,-22);
                glVertex2f(bar_length*bar_age,-18);
                glEnd();
                //fertility
                glColor3f(1,1,1);
                glBegin(GL_LINES);
                glVertex2f(-bar_length,-15);
                glVertex2f(bar_length,-15);
                glVertex2f(bar_length*bar_fert,-17);
                glVertex2f(bar_length*bar_fert,-13);
                glEnd();

            }break;

            default:
            {
                //box
                glColor3f(0.3,0.3,0.3);
                glBegin(GL_QUADS);
                glVertex2f(-28,-40);
                glVertex2f(-28,-10);
                glVertex2f(28,-10);
                glVertex2f(28,-40);
                glEnd();
                //speed
                glColor3f(1,1,0);
                glBegin(GL_LINES);
                glVertex2f(-bar_length,-35);
                glVertex2f(bar_length,-35);
                glVertex2f(bar_length*bar_speed,-37);
                glVertex2f(bar_length*bar_speed,-33);
                glEnd();
                //prod
                glColor3f(1.0,0.6,1);
                glBegin(GL_LINES);
                glVertex2f(-bar_length,-30);
                glVertex2f(bar_length,-30);
                glVertex2f(bar_length*bar_prod,-32);
                glVertex2f(bar_length*bar_prod,-28);
                glEnd();
                //age/health
                glColor3f(0,1,0);
                glBegin(GL_LINES);
                glVertex2f(-bar_length,-25);
                glVertex2f(bar_length,-25);
                glVertex2f(bar_length*bar_age,-27);
                glVertex2f(bar_length*bar_age,-23);
                glEnd();
                //fertility
                glColor3f(1,1,1);
                glBegin(GL_LINES);
                glVertex2f(-bar_length,-20);
                glVertex2f(bar_length,-20);
                glVertex2f(bar_length*bar_fert,-22);
                glVertex2f(bar_length*bar_fert,-18);
                glEnd();
                //crime
                glColor3f(1,0,0);
                glBegin(GL_LINES);
                glVertex2f(-bar_length,-15);
                glVertex2f(bar_length,-15);
                glVertex2f(bar_length*bar_crime,-17);
                glVertex2f(bar_length*bar_crime,-13);
                glEnd();
            }break;
        }

        glPopMatrix();
    }

    if(m_logging) logfile<<"14";

    glPopMatrix();

    //draw score HUD
    stringstream ss;
    ss<<m_points_left;
    string points_left_string(ss.str());

    glPushMatrix();
    glTranslatef(screen_width-22,48,0);
    glLineWidth(2);
    glColor3f(0.8,0.8,0.8);
    glScalef(20,20,20);
    for(int i=(int)points_left_string.size();i>=0;i--)
    {
        draw_number(points_left_string[i]);
        glTranslatef(-1.3,0,0);
    }
    glLineWidth(1);
    glPopMatrix();

    //draw tutorial text
    glPushMatrix();
    glTranslatef(0,screen_height-41,0);
    glEnable(GL_TEXTURE_2D);
    switch(game_level)
    {
        case 1: glBindTexture(GL_TEXTURE_2D,tex_tut[0]); break;
        case 2: glBindTexture(GL_TEXTURE_2D,tex_tut[1]); break;
        case 3: glBindTexture(GL_TEXTURE_2D,tex_tut[2]); break;
        case 4: glBindTexture(GL_TEXTURE_2D,tex_tut[3]); break;
        case 5: glBindTexture(GL_TEXTURE_2D,tex_tut[4]); break;
        case 6: glBindTexture(GL_TEXTURE_2D,tex_tut[5]); break;
        case 7: glBindTexture(GL_TEXTURE_2D,tex_tut[6]); break;
    }
    glColor3f(1,1,1);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0,1.0);
    glVertex2f(0,0);
    glTexCoord2f(0.0,0.0);
    glVertex2f(0,41);
    glTexCoord2f(1.0,0.0);
    glVertex2f(screen_width,41);
    glTexCoord2f(1.0,1.0);
    glVertex2f(screen_width,0);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    if(m_logging) logfile<<"15";

    return true;
}

bool game::reset()
{
    if(m_logging) logfile<<"16";

    mvec_pop.clear();
    mvec_house.clear();
    mvec_particle.clear();
    mvec_flash.clear();
    for(int i=0;i<(int)mvec_terrain_line.size();i++)
    {
        mvec_terrain_line[i].vec_x.clear();
        mvec_terrain_line[i].vec_y.clear();
    }
    mvec_terrain_line.clear();
    for(int i=0;i<(int)mvec_road.size();i++)
    {
        mvec_road[i].vec_x.clear();
        mvec_road[i].vec_y.clear();
    }
    mvec_road.clear();


    if(m_logging) logfile<<"17";
    if(m_logging) logfile.close();

    init(screen_width,screen_height);

    return true;
}

bool game::draw_number(char val)
{
    switch(val)
    {
        case 'A':
        {
            glBegin(GL_LINES);
            glVertex2f(0,0);
            glVertex2f(0,0.5);

            glVertex2f(0,0.5);
            glVertex2f(0,1);

            glVertex2f(0,0.5);
            glVertex2f(1,0.5);

            glVertex2f(1,1);
            glVertex2f(1,0.5);

            glVertex2f(1,0.5);
            glVertex2f(1,0);

            glVertex2f(1,0);
            glVertex2f(0,0);
            glEnd();
        }break;

        case 'T':
        {
            glBegin(GL_LINES);
            glVertex2f(0.5,0);
            glVertex2f(0.5,0.5);

            glVertex2f(0.5,0.5);
            glVertex2f(0.5,1);

            glVertex2f(1,0);
            glVertex2f(0,0);
            glEnd();
        }break;

        case 'G':
        {
            glBegin(GL_LINES);
            glVertex2f(0,0);
            glVertex2f(0,0.5);

            glVertex2f(0,0.5);
            glVertex2f(0,1);

            glVertex2f(0,1);
            glVertex2f(1,1);

            glVertex2f(1,1);
            glVertex2f(1,0.5);

            glVertex2f(1,0);
            glVertex2f(0,0);

            glVertex2f(0.5,0.5);
            glVertex2f(1,0.5);

            glEnd();
        }break;

        case 'C':
        {
            glBegin(GL_LINES);
            glVertex2f(0,0);
            glVertex2f(0,0.5);

            glVertex2f(0,0.5);
            glVertex2f(0,1);

            glVertex2f(0,1);
            glVertex2f(1,1);

            glVertex2f(1,0);
            glVertex2f(0,0);
            glEnd();
        }break;

        case '0':
        {
            glBegin(GL_LINES);
            glVertex2f(0,0);
            glVertex2f(0,0.5);

            glVertex2f(0,0.5);
            glVertex2f(0,1);

            glVertex2f(0,1);
            glVertex2f(1,1);

            glVertex2f(1,1);
            glVertex2f(1,0.5);

            glVertex2f(1,0.5);
            glVertex2f(1,0);

            glVertex2f(1,0);
            glVertex2f(0,0);
            glEnd();
        }break;

        case '1':
        {
            glBegin(GL_LINES);
            glVertex2f(1,1);
            glVertex2f(1,0.5);

            glVertex2f(1,0.5);
            glVertex2f(1,0);
            glEnd();
        }break;

        case '2':
        {
            glBegin(GL_LINES);
            glVertex2f(0,1);
            glVertex2f(1,1);

            glVertex2f(1,0);
            glVertex2f(0,1);

            glVertex2f(1,0);
            glVertex2f(0,0);
            glEnd();
        }break;

        case '3':
        {
            glBegin(GL_LINES);
            glVertex2f(0,0.5);
            glVertex2f(1,0.5);

            glVertex2f(0,1);
            glVertex2f(1,1);

            glVertex2f(1,1);
            glVertex2f(1,0.5);

            glVertex2f(1,0.5);
            glVertex2f(1,0);

            glVertex2f(1,0);
            glVertex2f(0,0);
            glEnd();
        }break;

        case '4':
        {
            glBegin(GL_LINES);
            glVertex2f(0,0);
            glVertex2f(0,0.5);

            glVertex2f(0,0.5);
            glVertex2f(1,0.5);

            glVertex2f(1,1);
            glVertex2f(1,0.5);

            glVertex2f(1,0.5);
            glVertex2f(1,0);
            glEnd();
        }break;

        case '5':
        {
            glBegin(GL_LINES);
            glVertex2f(0,1);
            glVertex2f(1,1);

            glVertex2f(0,0);
            glVertex2f(1,1);

            glVertex2f(1,0);
            glVertex2f(0,0);
            glEnd();
        }break;

        case '6':
        {
            glBegin(GL_LINES);
            glVertex2f(0,0);
            glVertex2f(0,0.5);

            glVertex2f(0,0.5);
            glVertex2f(0,1);

            glVertex2f(0,1);
            glVertex2f(1,1);

            glVertex2f(1,1);
            glVertex2f(1,0.5);

            glVertex2f(0,0.5);
            glVertex2f(1,0.5);

            glVertex2f(1,0);
            glVertex2f(0,0);
            glEnd();
        }break;

        case '7':
        {
            glBegin(GL_LINES);
            glVertex2f(1,1);
            glVertex2f(1,0.5);

            glVertex2f(1,0.5);
            glVertex2f(1,0);

            glVertex2f(1,0);
            glVertex2f(0,0);
            glEnd();
        }break;

        case '8':
        {
            glBegin(GL_LINES);
            glVertex2f(0,0);
            glVertex2f(0,0.5);

            glVertex2f(0,0.5);
            glVertex2f(0,1);

            glVertex2f(0,1);
            glVertex2f(1,1);

            glVertex2f(1,1);
            glVertex2f(1,0.5);

            glVertex2f(1,0.5);
            glVertex2f(1,0);

            glVertex2f(1,0);
            glVertex2f(0,0);

            glVertex2f(0,0.5);
            glVertex2f(1,0.5);
            glEnd();
        }break;

        case '9':
        {
            glBegin(GL_LINES);
            glVertex2f(0,0);
            glVertex2f(0,0.5);

            glVertex2f(1,1);
            glVertex2f(1,0.5);

            glVertex2f(1,0.5);
            glVertex2f(1,0);

            glVertex2f(1,0);
            glVertex2f(0,0);

            glVertex2f(0,0.5);
            glVertex2f(1,0.5);
            glEnd();
        }break;
    }

    return true;
}

bool game::spawn_pop(int pop_ind,bool random_prop,float posx,float posy)
{
    if(m_logging) logfile<<"18";

    int seleced_pop=pop_ind;
    if(pop_ind==-1)
    {
        //selected spawn point
        mvec_pop.push_back(pop(posx,posy));
    }
    else//spawn at other pop
    {
        mvec_pop.push_back(pop(mvec_pop[seleced_pop].m_pos_x+rand()%5,
                               mvec_pop[seleced_pop].m_pos_y+rand()%5));
        //assign properties
        mvec_pop.back().m_speed=mvec_pop[seleced_pop].m_speed+float(rand()%11-5)*0.01;
        if(mvec_pop.back().m_speed<0.1) mvec_pop.back().m_speed=0.1;
        mvec_pop.back().m_productivity=mvec_pop[seleced_pop].m_productivity+float(rand()%11-5)*0.01;
        if(mvec_pop.back().m_productivity<0.1) mvec_pop.back().m_productivity=0.1;
        if(mvec_pop.back().m_productivity>1) mvec_pop.back().m_productivity=1;
        mvec_pop.back().m_fertility=mvec_pop[seleced_pop].m_fertility+float(rand()%11-5)*0.01;
        if(mvec_pop.back().m_fertility<0.1) mvec_pop.back().m_fertility=0.1;
        if(mvec_pop.back().m_fertility>1) mvec_pop.back().m_fertility=1;
        mvec_pop.back().m_criminality=mvec_pop[seleced_pop].m_criminality+float(rand()%11-5)*0.01;
        if(mvec_pop.back().m_criminality<0) mvec_pop.back().m_criminality=0;
        if(mvec_pop.back().m_criminality>1) mvec_pop.back().m_criminality=1;
        mvec_pop.back().m_age_start=mvec_pop[seleced_pop].m_age_start+float(rand()%11-5);
        if(mvec_pop.back().m_age_start<10) mvec_pop.back().m_age_start=10;
        mvec_pop.back().m_age_curr=mvec_pop.back().m_age_start;
    }

    if(random_prop)
    {
        if(m_logging) logfile<<"19";

        mvec_pop.back().m_speed=rand()%100*0.005;
        if(mvec_pop.back().m_speed<0.1) mvec_pop.back().m_speed=0.1;
        mvec_pop.back().m_productivity=float(rand()%100)*0.01;
        if(mvec_pop.back().m_productivity<0.1) mvec_pop.back().m_productivity=0.1;
        if(mvec_pop.back().m_productivity>1) mvec_pop.back().m_productivity=1;
        mvec_pop.back().m_fertility=float(rand()%100)*0.01;
        if(mvec_pop.back().m_fertility<0.1) mvec_pop.back().m_fertility=0.1;
        if(mvec_pop.back().m_fertility>1) mvec_pop.back().m_fertility=1;
        mvec_pop.back().m_criminality=float(rand()%100)*0.01;
        mvec_pop.back().m_age_start=rand()%100;
        if(mvec_pop.back().m_age_start<10) mvec_pop.back().m_age_start=10;
        mvec_pop.back().m_age_curr=mvec_pop.back().m_age_start;
    }

    switch(game_level)
    {
        case 1:
        {
            mvec_pop.back().m_productivity=1;
            mvec_pop.back().m_fertility=0;
            mvec_pop.back().m_criminality=0;
            mvec_pop.back().m_age_curr=mvec_pop.back().m_age_start=99999999;
        }break;

        case 2:
        {
            mvec_pop.back().m_fertility=0;
            mvec_pop.back().m_criminality=0;
            mvec_pop.back().m_age_curr=mvec_pop.back().m_age_start=99999999;
        }break;

        case 3:
        {
            mvec_pop.back().m_fertility=0;
            mvec_pop.back().m_criminality=0;
            mvec_pop.back().m_age_curr=mvec_pop.back().m_age_start=99999999;
        }break;

        case 4:
        {
            mvec_pop.back().m_fertility=0;
            mvec_pop.back().m_criminality=0;
        }break;

        case 5:
        {
            mvec_pop.back().m_criminality=0;
        }break;

        default:
        {
            ;
        }break;
    }

    //assign work
    if((int)mvec_house.size()<2) cout<<"WARNING: Only one house\n";
    mvec_pop.back().m_currworkplace=rand()%2;
    int seleced_house1=rand()%(int)mvec_house.size();
    if(pop_ind==-1)
    {
        seleced_house1=(int)mvec_house.size()-1;
    }
    int seleced_house2=rand()%(int)mvec_house.size();
    while (seleced_house1==seleced_house2 && (int)mvec_house.size()>1)
    {
        seleced_house2=rand()%(int)mvec_house.size();
    }
    mvec_pop.back().m_workpos_x[0]=mvec_house[seleced_house1].m_pos_x;
    mvec_pop.back().m_workpos_y[0]=mvec_house[seleced_house1].m_pos_y;
    mvec_pop.back().m_workpos_x[1]=mvec_house[seleced_house2].m_pos_x;
    mvec_pop.back().m_workpos_y[1]=mvec_house[seleced_house2].m_pos_y;

    if(m_logging) logfile<<"20";

    return true;
}
