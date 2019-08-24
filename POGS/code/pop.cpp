#include "pop.h"

pop::pop(int posx,int posy)
{
    m_pos_x=m_target_x=posx;
    m_pos_y=m_target_y=posy;
    m_state=ps_work;
    m_speed=0.2+rand()%100*0.001-0.05;
    m_productivity=0.5;
    m_fertility=0.5;
    m_criminality=0;
    m_age_start=m_age_curr=60;

    m_idle_timer=0;
    m_break_timer=_break_time;
    m_work_timer=_work_time;
    m_birth_timer=_birth_time;
    m_crime_timer=_crime_time;
    m_walk_anim=rand()%100*0.01;
    m_anim_dir=1;
    m_offset_la=rand()%100*0.01;
    m_offset_ra=rand()%100*0.01;
    m_offset_ll=rand()%100*0.01;
    m_offset_rl=rand()%100*0.01;

    m_size=5;

    //cout<<m_pos_x<<endl;
    //cout<<m_pos_y<<endl;
}

int pop::update()
{
    //age test
    if(m_age_curr<=0)
    {
        //death
        return 2;
    }
    else m_age_curr-=_time_dif;

    //break time
    if(m_state==ps_idle || m_state==ps_walk)
    {
        if(m_break_timer<=0)
        {
            //start work
            m_state=ps_work;
            m_work_timer=_work_time;
        }
        else m_break_timer-=_time_dif;

        //birth time
        if(m_birth_timer>0)
        {
            m_birth_timer-=_time_dif;
        }
    }

    //crime timer
    if(m_crime_timer>0)
    {
        m_crime_timer-=_time_dif;
    }

    //walk anim timer
    if(m_state==ps_work || m_state==ps_walk)
    {
        m_walk_anim+=_time_dif*m_speed*10;
        if(m_walk_anim>1) m_walk_anim-=1;

        /*m_walk_anim+=_time_dif*m_anim_dir;
        if(m_walk_anim>=1)
        {
            m_anim_dir*=-1;
            m_walk_anim=1;
        }
        if(m_walk_anim<=0)
        {
            m_anim_dir*=-1;
            m_walk_anim=0;
        }*/
    }

    switch(m_state)
    {
        case ps_idle:
        {
            if(m_idle_timer<=0)
            {
                m_state=ps_walk;
                //set random target
                m_target_x=m_pos_x+rand()%61-30;
                m_target_y=m_pos_y+rand()%61-30;

                //cout<<"walking"<<endl;
            }
            else m_idle_timer-=_time_dif;
        }break;

        case ps_walk:
        {
            //test if within target
            if(fabs(m_pos_x-m_target_x)<m_size &&
               fabs(m_pos_y-m_target_y)<m_size)
            {
                m_state=ps_idle;
                m_idle_timer=float(rand()%20)/10;

                //cout<<"idle"<<endl;
            }
            else
            {
                float dir_x=m_target_x-m_pos_x;
                float dir_y=m_target_y-m_pos_y;
                float length=sqrt(dir_x*dir_x+dir_y*dir_y);
                if(length>1)
                {
                    dir_x/=length;
                    dir_y/=length;

                    m_pos_x+=dir_x*m_speed;
                    m_pos_y+=dir_y*m_speed;
                }
            }

        }break;

        case ps_work:
        {
            if(m_work_timer<=0)
            {
                //do break test
                if(rand()%100>m_productivity*100)
                {
                    m_state=ps_idle;
                    m_break_timer=_break_time+(1-m_productivity)*_break_time;
                }
            }
            else m_work_timer-=_time_dif;

            //test if within target
            if(fabs(m_pos_x-m_workpos_x[m_currworkplace])<m_size*2 &&
               fabs(m_pos_y-m_workpos_y[m_currworkplace])<m_size*2 )
            {
                if(m_currworkplace==0) m_currworkplace=1;
                else m_currworkplace=0;

                //cout<<"pop arrived at work target\n";
                //cout<<m_pos_x-m_workpos_x[m_currworkplace]<<endl;

                return 1;
            }
            else //go towards target
            {
                float dir_x=m_workpos_x[m_currworkplace]-m_pos_x;
                float dir_y=m_workpos_y[m_currworkplace]-m_pos_y;
                float length=sqrt(dir_x*dir_x+dir_y*dir_y);
                if(length>1)
                {
                    dir_x/=length;
                    dir_y/=length;

                    m_pos_x+=dir_x*m_speed;
                    m_pos_y+=dir_y*m_speed;
                }
            }

        }break;
    }




    return 0;
}

bool pop::draw()
{
    glPushMatrix();

    glColor3f(1,1,1);
    if(m_age_curr/m_age_start<0.5)
    {
        float color=m_age_curr/m_age_start*2;
        glColor3f(color,color,color);
    }

    glTranslatef(m_pos_x,m_pos_y,0);
    //triangle
    /*//glRotatef(m_rotation,0,0,1);

    glBegin(GL_TRIANGLES);
    glVertex2f(0,-m_size);
    glVertex2f(-m_size,m_size);
    glVertex2f(m_size,m_size);
    glEnd();*/

    //stickman
    float leftarm=m_walk_anim+m_offset_la;
    if(leftarm>1) leftarm-=1;
    leftarm=sinf(leftarm*_pi);
    float rightarm=m_walk_anim+m_offset_ra;
    if(rightarm>1) rightarm-=1;
    rightarm=sinf(rightarm*_pi);
    float leftleg=m_walk_anim+m_offset_ll;
    if(leftleg>1) leftleg-=1;
    leftleg=sinf(leftleg*_pi);
    float rightleg=m_walk_anim+m_offset_rl;
    if(rightleg>1) rightleg-=1;
    rightleg=sinf(rightleg*_pi);

    glScalef(m_size,m_size,m_size);
    glBegin(GL_LINES);
    //left leg
    glVertex2f(0,0);
    glVertex2f(-0.5*leftleg,0.8);
    //right leg
    glVertex2f(0,0);
    glVertex2f(0.5*rightleg,0.8);
    //left arm
    glVertex2f(0,-0.5);
    glVertex2f(-0.5*leftarm,0);
    //right arm
    glVertex2f(0,-0.5);
    glVertex2f(0.5*rightarm,0);
    //body
    glVertex2f(0,0);
    glVertex2f(0,-1);
    //head
    glVertex2f(-0.2,-0.8);
    glVertex2f(0.3,-0.8);
    glEnd();

    glPopMatrix();

    return true;
}
