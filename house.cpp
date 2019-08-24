#include "house.h"

house::house(int posx,int posy,float wag)
{
    m_pos_x=posx;
    m_pos_y=posy;
    m_rotation=rand()%90;
    m_size=rand()%5+8;
    //cout<<m_size<<endl;
    m_type=rand()%6;
    m_wag_anim=wag;
}

bool house::update(float wag)
{
    m_wag_anim=wag;

    //m_wag_anim+=_time_dif*0.5;
    //if(m_wag_anim>1) m_wag_anim-=1;

    return true;
}

bool house::draw()
{
    glPushMatrix();

    float topshift=sinf(m_wag_anim*2*_pi)*10;

    glTranslatef(m_pos_x,m_pos_y,0);
    //glRotatef(m_rotation,0,0,1);
    glColor3f(0.6,0.6,0.6);
    glScalef(0.03*m_size,0.03*m_size,0.03*m_size);

    switch(m_type)
    {
        case 0:
        {
            glTranslatef(-50,-50,0);
            glColor3f(0.1,0.1,0.1);
            glBegin(GL_TRIANGLE_FAN);
            glVertex2f(50,50);
            glVertex2f(0+topshift,6);
            glVertex2f(5,61);
            glVertex2f(25,96);
            glVertex2f(93,78);
            glVertex2f(100+topshift,17);
            glVertex2f(60+topshift,0);
            glVertex2f(0+topshift,6);
            glEnd();
            glColor3f(0.6,0.6,0.6);
            glBegin(GL_LINE_STRIP);
            glVertex2f(0+topshift,6);
            glVertex2f(5,61);
            glVertex2f(25,96);
            glVertex2f(22,28);
            glVertex2f(0+topshift,6);
            glVertex2f(60+topshift,0);
            glVertex2f(100+topshift,17);
            glVertex2f(22,28);
            glVertex2f(25,96);
            glVertex2f(93,78);
            glVertex2f(100+topshift,17);
            glEnd();
        }break;

        case 1:
        {
            glTranslatef(-50,-50,0);
            glColor3f(0.1,0.1,0.1);
            glBegin(GL_TRIANGLE_FAN);
            glVertex2f(50,50);
            glVertex2f(0+topshift,18);
            glVertex2f(7,99);
            glVertex2f(91,95);
            glVertex2f(98+topshift,16);
            glVertex2f(78+topshift,0);
            glVertex2f(7+topshift,1);
            glVertex2f(0+topshift,18);
            glEnd();
            glColor3f(0.6,0.6,0.6);
            glBegin(GL_LINE_STRIP);
            glVertex2f(0+topshift,18);
            glVertex2f(7,99);
            glVertex2f(91,95);
            glVertex2f(98+topshift,16);
            glVertex2f(78+topshift,0);
            glVertex2f(7+topshift,1);
            glVertex2f(0+topshift,18);
            glVertex2f(98+topshift,16);
            glEnd();
        }break;

        case 2:
        {
            glTranslatef(-50,-50,0);
            glColor3f(0.1,0.1,0.1);
            glBegin(GL_TRIANGLE_FAN);
            glVertex2f(50,50);
            glVertex2f(1+topshift,6);
            glVertex2f(5,67);
            glVertex2f(38,99);
            glVertex2f(93,75);
            glVertex2f(100+topshift,10);
            glVertex2f(54+topshift,0);
            glVertex2f(1+topshift,6);
            glEnd();
            glColor3f(0.6,0.6,0.6);
            glBegin(GL_LINE_STRIP);
            glVertex2f(1+topshift,6);
            glVertex2f(5,67);
            glVertex2f(38,99);
            glVertex2f(93,75);
            glVertex2f(100+topshift,10);
            glVertex2f(54+topshift,0);
            glVertex2f(1+topshift,6);
            glVertex2f(36+topshift,21);
            glVertex2f(38,99);
            glVertex2f(36+topshift,21);
            glVertex2f(100+topshift,10);
            glEnd();
        }break;

        case 3:
        {
            glTranslatef(50,-50,0);
            glColor3f(0.1,0.1,0.1);
            glBegin(GL_TRIANGLE_FAN);
            glVertex2f(-50,50);
            glVertex2f(-0+topshift,6);
            glVertex2f(-5,61);
            glVertex2f(-25,96);
            glVertex2f(-93,78);
            glVertex2f(-100+topshift,17);
            glVertex2f(-60+topshift,0);
            glVertex2f(-0+topshift,6);
            glEnd();
            glColor3f(0.6,0.6,0.6);
            glBegin(GL_LINE_STRIP);
            glVertex2f(-0+topshift,6);
            glVertex2f(-5,61);
            glVertex2f(-25,96);
            glVertex2f(-22,28);
            glVertex2f(-0+topshift,6);
            glVertex2f(-60+topshift,0);
            glVertex2f(-100+topshift,17);
            glVertex2f(-22,28);
            glVertex2f(-25,96);
            glVertex2f(-93,78);
            glVertex2f(-100+topshift,17);
            glEnd();
        }break;

        case 4:
        {
            glTranslatef(50,-50,0);
            glColor3f(0.1,0.1,0.1);
            glBegin(GL_TRIANGLE_FAN);
            glVertex2f(-50,50);
            glVertex2f(-0+topshift,18);
            glVertex2f(-7,99);
            glVertex2f(-91,95);
            glVertex2f(-98+topshift,16);
            glVertex2f(-78+topshift,0);
            glVertex2f(-7+topshift,1);
            glVertex2f(-0+topshift,18);
            glEnd();
            glColor3f(0.6,0.6,0.6);
            glBegin(GL_LINE_STRIP);
            glVertex2f(-0+topshift,18);
            glVertex2f(-7,99);
            glVertex2f(-91,95);
            glVertex2f(-98+topshift,16);
            glVertex2f(-78+topshift,0);
            glVertex2f(-7+topshift,1);
            glVertex2f(-0+topshift,18);
            glVertex2f(-98+topshift,16);
            glEnd();
        }break;

        case 5:
        {
            glTranslatef(50,-50,0);
            glColor3f(0.1,0.1,0.1);
            glBegin(GL_TRIANGLE_FAN);
            glVertex2f(-50,50);
            glVertex2f(-1+topshift,6);
            glVertex2f(-5,67);
            glVertex2f(-38,99);
            glVertex2f(-93,75);
            glVertex2f(-100+topshift,10);
            glVertex2f(-54+topshift,0);
            glVertex2f(-1+topshift,6);
            glEnd();
            glColor3f(0.6,0.6,0.6);
            glBegin(GL_LINE_STRIP);
            glVertex2f(-1+topshift,6);
            glVertex2f(-5,67);
            glVertex2f(-38,99);
            glVertex2f(-93,75);
            glVertex2f(-100+topshift,10);
            glVertex2f(-54+topshift,0);
            glVertex2f(-1+topshift,6);
            glVertex2f(-36+topshift,21);
            glVertex2f(-38,99);
            glVertex2f(-36+topshift,21);
            glVertex2f(-100+topshift,10);
            glEnd();
        }break;
    }

    glPopMatrix();

    return true;
}
