#include<GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <MMSystem.h>
#include<math.h>
#include <iostream>
#include<bits/stdc++.h>
#include <string.h>//includes the opengl, glu, and glut header files
#include<bits/stdc++.h> //includes the standard library header file
using namespace std;
float r,g,b,x,y;
//bool check=true;

bool ai = false;
bool flag = true;
bool ok = true, finish = false;
int point_size = 25, block_no = 0;
class node
{
public:
    int x;
    int y;
    float r = 0;
    float g = 1;
    float b = 0;
    bool status = false;
} points[400];
int arr[10] = {0};
map<int,int> mp;
map<int,int> iteams;

void show_()
{
    for(int px=220; px<=450; px+=30)
    {
        cout<<mp[px]<<" ";

    }
    cout<<endl;
}

void mp_update()
{
    mp.clear();
    block_no = 0;
    for(int i=0; i<=250; i++)
    {
        if(points[i].status == true)
        {
            mp[points[i].x]++;
            block_no++;
        }

    }
}

void action_ai(int st,int p,int num)
{

    if(st)
    {
        cout<<"num="<<num<<"mp[pos]="<<mp[p]<<endl;
        for(int i=0; i<=250; i++)
        {
            if(points[i].x == p && points[i].status == true)
            {
                while(i+1<=250 && points[i+1].status == true && points[i].x == points[i+1].x  )
                {
                    i++;
                }
                //mp[p]-=num;
                int tcnt=0;

                for(int j=i;; j--,num--)
                {
                    if(num<=0)
                        break;
                    cout<<"here falsing"<<endl;
                    points[j].status = false;
                    //mp[points[j].x]--;
                    tcnt++;

                }
                cout<<"after a1 num="<<num<<" tcnt = "<<tcnt<<endl;
                break;
            }
        }
        cout<<"after a1"<<endl;
        mp_update();
        show_();
    }
    else
    {
        for(int i=0; i<400; i++)
        {
            if(points[i].status == true)
            {
                int cnt = 1;
                while(i+1 <=250 && points[i+1].status == true && points[i+1].x == points[i].x)
                {
                    i++;
                    cnt++;
                }

//                if(cnt%2)
//                {
//                    //odd
//                    cnt--;
//
//                }
//                cout<<"cnt="<<cnt<<endl;
//                for(int j=i;;j--,cnt--)
//                    {
//
//                        if(cnt<=0)
//                            break;
//                        points[j].status = false;
//                        mp[points[j].x]--;
//
//                    }
                points[i].status = false;
//                i--;
//                points[i].status = false;
                //mp[points[i].x]--;
                mp_update();
                break;
            }
        }

    }

    ai = !ai;
}

void decide(map<int,int>np)
{
    for(int px=220; px<=450; px+=30)
    {
        for(int i=220; i<=450; i+=30)
        {
            if(px==i)
                continue;
            else if(np[px]>0)
            {
                if(np[px]>=np[i])
                {
                    np[px] = np[px] - np[i];
                    np[i] = 0;
                }
                else
                {
                    np[i] = np[i]-np[px];
                    np[px] = 0;
                }

            }
            else if(np[px]<=0)
                break;
        }
    }
    //showing np
//    for(int px=220; px<=450; px+=30)
//    {
//        cout<<np[px]<<" ";
//    }
//    cout<<endl;

    int pos ;
    int got = 0;
    for(int px=220; px<=450; px+=30)
    {
        if(np[px]>0)
        {
            pos = px;
            got = 1;
            cout<<"ai 1"<<endl;
            break;
        }

    }

    if(got)
    {
        //unbalanced
        action_ai(1,pos,np[pos]);

    }
    else
    {
        //balanced
        action_ai(0,0,0);
        cout<<"ai 2"<<endl;
    }
}




void aiTimer(int val)
{
    //Ai;
    decide(mp);
    glutPostRedisplay();
}

void player_action(int l)
{

    points[l].status = false;
    mp[points[l].x]--;
    while(l+1<=250 && points[l+1].status==true && points[l+1].x==points[l].x )
    {
        //mp[points[l+1].x]--;
        points[l+1].status = false;
        l++;
    }
    mp_update();


}

void mouse(int button, int state, int mousex, int mousey)
{
    if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
    {
        //check=true;

        x = mousex;
        y = 480-mousey;

        for(int i=0; i<=250; i++)
        {
            if(points[i].status)
            {

                if((points[i].x+point_size/2>x && points[i].x-point_size/2<x) && (points[i].y+point_size/2>y && points[i].y-point_size/2<y))
                {


                    points[i].r = 1;
                    points[i].g = 0;
                    points[i].b = 0;

                    glutTimerFunc(100,player_action,i);

                    ai = ! ai;
                    if(ai && block_no)
                    {
                        glutTimerFunc(1000,aiTimer,0);

                    }


                    //cout<<"here"<<endl;
                    show_();

                }
            }
        }
    }

    else if(button==GLUT_RIGHT_BUTTON && state==GLUT_DOWN)//undo(clear)the drawing
    {

    }
    glutPostRedisplay();
}

void create()
{
    int i =0;


    if(flag)
    {
        for(int px=220; px<=450; px+=30)
        {
            int num = max(rand()%9,1);
            //arr[ind] = num;
            for(int py=50; py<=50*num; py+=30)
            {
                points[i].x=px;
                points[i].y=py;
                points[i].status = true;
                mp[px]++;
                block_no++;
                i++;
            }



        }
        flag = !flag;
    }

}
void scene()
{
    if(ok)
    {
        for(int i=0; i<300; i++)
        {
            if(points[i].status)
            {
                glBegin(GL_POINTS);
                glColor3f(points[i].r, points[i].g, points[i].b);
                // writes pixels on the frame buffer with the current drawing color
                glVertex2i(points[i].x, points[i].y);   // sets vertex
                //cout<<points[i].x<<" "<<points[i].y<<endl;
                glEnd();

                //cout<<i<<" point status of"<<" "<<points[i].x <<" & "<<points[i].y<<" is: "<<points[i].status<<endl;
            }
        }
    }


    glutMouseFunc(mouse);
}

void text(int fin)
{

    if(fin && !finish)
    {
        glEnable(GL_LINE_SMOOTH);
        glLineWidth(10.0);
        glPushMatrix();
        glRasterPos3f(250,450,0);
        glScalef(100,100,10);
        //glTranslatef(-150,800,-400);
        char msg[] = "Your_Turn";
        for(int i=0; i<strlen(msg); i++)
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,msg[i]);
        glPopMatrix();
    }

    else
    {
        cout<<"in text"<<endl;
        string s;
        if(!ai)
            s = "You Lose";
        else
            s= "Congrats!!!!!!";


        glPushMatrix();
        glEnable(GL_LINE_SMOOTH);
        glLineWidth(0.0);
        //glColor3b(1,1,1);
        glRasterPos3f(260,350,0);
        glScalef(10,10,10);
        for(int i=0; i<s.size(); i++)
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,s[i]);
        glPopMatrix();
    }


}



void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // sets the current drawing (foreground) color to blue
    glPointSize(point_size); // sets the size of points to be drawn (in pixels)

    glMatrixMode(GL_PROJECTION);// sets the current matrix to projection
    glLoadIdentity();//multiply the current matrix by identity matrix
    gluOrtho2D(0.0, 640.0, 0.0, 480.0);//sets the parallel(orthographic) projection of the full frame buffer


    create();
    scene();
    if(block_no == 0 && !finish)
        finish = true;
    if(!ai && block_no && !finish)
        text(1);
    else if(!block_no && finish)
    {
        block_no = -1;
        finish = !finish;
        text(0);
    }



    glFlush();     // flushes the frame buffer to the screen
    glutSwapBuffers();
}
static void key(unsigned char key, int x, int y)
{
    switch (key)
    {
    case '1':
        ok = !ok;
        break;
    }

    glutPostRedisplay();
}
void sound()
{
    sndPlaySound("E:\\Ai_project\\test\\background_sound.wav", SND_ASYNC);
    //E:\\Ai_project\\test\\background_sound.wav

    glutPostRedisplay();
}
int main(int argc,char** argv)
{
    glutInit(&argc,argv);
    glutInitWindowSize(640,480);   //sets the width and height of the window in pixels
    glutInitWindowPosition(300,10);//sets the position of the window in pixels from top left corner
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);//creates a single frame buffer of RGB color capacity.
    glutCreateWindow("Green_Hackenbush");//creates the window as specified by the user as above.

    glClearColor(0.1, 0.1, 0.1, 0); // sets the backgraound color to white light


    glClear(GL_COLOR_BUFFER_BIT); // clears the frame buffer and set values defined in glClearColor() function call

    glutDisplayFunc(display);//links the display event with the display event handler(display)
    //keyboard event handler
    glutMouseFunc(mouse);

    glutKeyboardFunc(key);
    sound();
    glutMainLoop();//loops the current event
    return EXIT_SUCCESS;
}
