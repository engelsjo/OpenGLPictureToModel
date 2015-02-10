#include <iostream>
#include <cmath>
#include <algorithm>
#include <ctime>
#include <time.h>

#define GLEW_STATIC
#include <GL/glew.h>
#ifdef __APPLE__
#include <OpenGL/glu.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#endif

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <glm/gtx/io.hpp>
#undef GLFW_DLL
#include <GLFW/glfw3.h>

#include <math.h>

#include "House.h"
#include "Trebuchet.h"
#include "Castle.h"
#include "Wall.h"
#include "Gate.h"
#include "Ram.h"
#include "Sphere.h"
#include "PalmTree.h"
#include "Cube.h" //for the ground surface

void init_model();
void win_refresh(GLFWwindow*);
float arc_ball_rad_square;
int screen_ctr_x, screen_ctr_y;

House house;
Trebuchet trebuchet;
Ram ram;
Castle castle;
Wall wall;
Cube ground;
Gate gate;
Sphere projectile;
PalmTree tree;
int tree_x1[25], tree_x2[25], tree_x3[25], tree_y1[25], tree_y2[25], tree_y3[25];

std::clock_t start_time;

glm::mat4 camera_cf;
glm::mat4 original_camera_cf;
using namespace std;
void err_function (int what, const char *msg) {
    cerr << what << " " << msg << endl;
}

void win_resize (GLFWwindow * win, int width, int height)
{
#ifdef DEBUG
    cout << __FUNCTION__ << " " << width << "x" << height << endl;
#endif
    int w, h;
    glfwGetWindowSize(win, &w, &h);
    screen_ctr_x = w / 2.0;
    screen_ctr_y = h / 2.0;
    float rad = min(h,w)/2;
    arc_ball_rad_square = rad * rad;
    /* Use the entire window for our view port */
    glViewport(0, 0, width, height);
    /* Use GL_PROJECTION to select the type of synthetic camera */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    /* near-plane(1) & far-plane(10) are always POSITIVE and they measure
     * the distances along the Z-axis in front of the camera */
    gluPerspective(60.0, static_cast<float> (width)/ static_cast<float> (height), 1, 10);
}

void win_refresh (GLFWwindow *win) {
    float time_elapsed = 10*(clock() - start_time) / (double) CLOCKS_PER_SEC;//sped up 3 times
    if(time_elapsed > 60) {// if the time passes the end of the camera motion
        start_time = clock(); // reset time
    }
    else {
        //If moving to point 2
        if(time_elapsed < 20) {
            camera_cf = original_camera_cf * glm::rotate(-160.0f/20/180 * (float)M_PI * time_elapsed, glm::vec3{0,0,1});
        }
        //If moving to point 3
        else if(time_elapsed < 30) {
            time_elapsed -= 20;
            camera_cf = original_camera_cf * glm::rotate(-160.0f/180 * (float)M_PI, glm::vec3{0,0,1});
            camera_cf *= glm::rotate(-80.0f/10/180 * (float)M_PI * time_elapsed, glm::vec3{0,1,0});
        }
        //If moving to point 4
        else if (time_elapsed < 45) {
            if(time_elapsed < 7.5) {
                camera_cf = glm::translate(glm::vec3{(20.0f/7.5f/180*time_elapsed*M_PI)*FOOT,0,0}) * camera_cf;
            }
            else{
                time_elapsed -= 7.5;
                camera_cf = glm::translate(glm::vec3{(20.0f/180*M_PI)*FOOT,0,0}) * camera_cf;
                camera_cf = glm::translate(glm::vec3{(-20.0f/7.5f/180*time_elapsed*M_PI)*FOOT,0,0}) * camera_cf;
            }
        }
        //If returning to point 1
        else {
            time_elapsed -= 30;
            camera_cf = original_camera_cf * glm::rotate(-160.0f/180 * (float)M_PI, glm::vec3{0,0,1});
            camera_cf *= glm::rotate(-60.0f/180 * (float)M_PI, glm::vec3{0,1,0});
            
            if(time_elapsed < 5) {
                camera_cf = glm::rotate(-180/5.0f/180 * (float)M_PI * time_elapsed, glm::vec3{0,0,1}) * camera_cf;
            }
            else {
                time_elapsed -= 5;
                camera_cf = glm::rotate(-180.0f/180 * (float)M_PI, glm::vec3{0,0,1}) * camera_cf;
                camera_cf *= glm::rotate(-90.0f/10/180 * time_elapsed * (float) M_PI, glm::vec3{0,1,0});
            }
        }
    }

    //    cout << __PRETTY_FUNCTION__ << endl;
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
    
    glMatrixMode (GL_MODELVIEW);
    glLoadIdentity();
    /* place the camera using the camera coordinate frame */
    glMultMatrixf (glm::value_ptr(camera_cf));
    
    glPushMatrix();
    glTranslatef(0, 0, -1 * FOOT);
    ground.render(false);
    glPopMatrix();
    
    glPushMatrix();
    castle.render(false);
    glPopMatrix();
    
    srand(clock());

    //render ring of trebuchets
    for(int i = 0; i < 11; i++) {
        float angle = i * M_PI / 10.0;
        bool launching = rand() % 2;
        glPushMatrix();
        glTranslatef(140 * cos(angle) * FOOT, 140 * sin(angle) * FOOT, 0);
        glRotatef(i*180/10 - 180, 0, 0, 1);
        trebuchet.render(launching);
        
        //render projectile
        if(launching) {
            int t = rand() % 50;
            glTranslatef((20 + t * 100 / 50.0) * FOOT, 0, (50 + (490 * t - 9.8 * t * t)/50.0) * FOOT);
            projectile.render(false);
        }
        
        glPopMatrix();
    }
    
    //render gate
    glPushMatrix();
    glTranslatef(0,40*FOOT,0);
    gate.render(false);
    glPopMatrix();
    
    //render square of walls
    for(int i = 0; i < 9; i++) {
        if(i < 3 || i > 5) {
            glPushMatrix();
            glTranslatef( (40 - 10 * i)*FOOT, 40*FOOT, 0);
            wall.render(false);
            glPopMatrix();
        }
    }
    
    for(int i = 0; i < 9; i++) {
        glPushMatrix();
        glTranslatef( (40 - 10 * i)*FOOT, -110*FOOT, 0);
        wall.render(false);
        glPopMatrix();
    }
    
    for(int i = 0; i < 15; i++) {
        glPushMatrix();
        glTranslatef(42.5*FOOT, (35 - 10 * i)*FOOT, 0);
        glRotatef(90, 0, 0, 1);
        wall.render(false);
        glPopMatrix();
    }
    
    
    for(int i = 0; i < 15; i++) {
        glPushMatrix();
        glTranslatef(-42.5*FOOT, (35 - 10 * i)*FOOT, 0);
        glRotatef(90, 0, 0, 1);
        wall.render(false);
        glPopMatrix();
    }
    
    //render grid of houses
    for(int x = -30; x <= 30; x+=20) {
        for(int y = -30; y >= -70; y-=20) {
            glPushMatrix();
            glTranslatef((x-2.5)*FOOT, y*FOOT, 0);
            glRotatef(90, 1,0,0);
            house.render(false);
            glPopMatrix();
        }
    }
    
    //render rams
    for (int i = 0; i < 5; i++) {
        int y = 48 + rand() % 7;
        glPushMatrix();
        glTranslatef((30 - 15*i)*FOOT, y*FOOT, 0);
        glRotatef(-90, 0, 0, 1);
        ram.render(false);
        glPopMatrix();
    }
    
    //render palm trees
    for(int i = 0; i < 25; i++) {
        glPushMatrix();
        glTranslatef(tree_x1[i] * FOOT, tree_y1[i] * FOOT, 0);
        tree.render(false);
        glPopMatrix();
        
        glPushMatrix();
        glTranslatef(tree_x2[i] * FOOT, tree_y2[i] * FOOT, 0);
        tree.render(false);
        glPopMatrix();
        
        glPushMatrix();
        glTranslatef(tree_x3[i] * FOOT, tree_y3[i] * FOOT, 0);
        tree.render(false);
        glPopMatrix();
    }
    
    
    /* must swap buffer at the end of render function */
    glfwSwapBuffers(win);
}

/* action: GLFW_PRESS, GLFW_RELEASE, or GLFW_REPEAT */
void key_handler (GLFWwindow *win, int key, int scan_code, int action, int mods)
{
    cout << __FUNCTION__ << endl;
    if (action != GLFW_PRESS) win_refresh(win);
    if (mods == GLFW_MOD_SHIFT) {
    }
    else {
        switch (key) {
            case GLFW_KEY_ESCAPE:
                glfwSetWindowShouldClose(win, true);
                break;
            case GLFW_KEY_0:
            case GLFW_KEY_W:
                glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                break;
            case GLFW_KEY_P:
                glPolygonMode(GL_FRONT, GL_FILL);
                break;
            case GLFW_KEY_1:
            case GLFW_KEY_2:
            case GLFW_KEY_3:
            case GLFW_KEY_4:
            case GLFW_KEY_5:
            case GLFW_KEY_6:
                /* rebuild the model at different level of detail */
                int N = key - GLFW_KEY_0;
                //one.build((void *)&N);
                break;
        }
    }
    win_refresh(win);
}

/*
 The virtual trackball technique implemented here is based on:
 https://www.opengl.org/wiki/Object_Mouse_Trackball
 */
void cursor_handler (GLFWwindow *win, double xpos, double ypos) {
    int state = glfwGetMouseButton(win, GLFW_MOUSE_BUTTON_LEFT);
    static glm::vec3 first_click;
    static glm::mat4 current_cam;
    static bool is_tracking = false;
    
    glm::vec3 this_vec;
    if (state == GLFW_PRESS) {
        /* TODO: use glUnproject? */
        float x = (xpos - screen_ctr_x);
        float y = -(ypos - screen_ctr_y);
        float hypot_square = x * x + y * y;
        float z;
        
        /* determine whether the mouse is on the sphere or on the hyperbolic sheet */
        if (2 * hypot_square < arc_ball_rad_square)
            z = sqrt(arc_ball_rad_square - hypot_square);
        else
            z = arc_ball_rad_square / 2.0 / sqrt(hypot_square);
        if (!is_tracking) {
            /* store the mouse position when the button was pressed for the first time */
            first_click = glm::normalize(glm::vec3{x, y, z});
            current_cam = camera_cf;
            is_tracking = true;
        }
        else {
            /* compute the rotation w.r.t the initial click */
            this_vec = glm::normalize(glm::vec3{x, y, z});
            /* determine axis of rotation */
            glm::vec3 N = glm::cross(first_click, this_vec);
            
            /* determine the angle of rotation */
            float theta = glm::angle(first_click, this_vec);
            
            /* create a quaternion of the rotation */
            glm::quat q{cos(theta / 2), sin(theta / 2) * N};
            /* apply the rotation w.r.t to the current camera CF */
            camera_cf = current_cam * glm::toMat4(glm::normalize(q));
        }
        win_refresh(win);
    }
    else {
        is_tracking = false;
    }
}

void scroll_handler (GLFWwindow *win, double xscroll, double yscroll) {
    /* translate along the camera Z-axis */
    glm::mat4 z_translate = glm::translate((float)yscroll * glm::vec3{0, 0, 1});
    camera_cf =  z_translate * camera_cf;
    win_refresh(win);
    
}

void init_gl() {
    glEnable (GL_DEPTH_TEST);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glEnable(GL_CULL_FACE);
    glLineWidth(3.0);
    
    /* place the camera at Z=+5 (notice that the sign is OPPOSITE!) */
    camera_cf *= glm::translate(glm::vec3{-180*FOOT, -70*FOOT, -45*FOOT});
    camera_cf = glm::rotate(-95.0f/180*(float)M_PI, glm::vec3{0,0,1}) * camera_cf;
    camera_cf = glm::rotate(-75.0f/180*(float)M_PI, glm::vec3{1, 0, 0}) * camera_cf;
    camera_cf = glm::scale(glm::vec3 {.2,.2,.2}) * camera_cf;
    original_camera_cf = camera_cf;
}

void make_model() {
    int N = 5;
    castle.build((void*)&N);
    tree.build((void*)&N);
    trebuchet.build((void*)&N);
    house.build((void*)&N);
    ram.build((void*)&N);
    wall.build((void*)&N);
    gate.build((void*)&N);
    projectile.setRadius(.5*FOOT);
    projectile.build((void*)&N);
    ground.build_with_params(2*FOOT, 400 * FOOT, 400 * FOOT, 0, 102, 0);
    
    srand(clock());
    for(int i = 0; i < 25; i++) {
        tree_x1[i] = -(rand() % 70) - 50;
        tree_x2[i] = rand() % 100 - 50;
        tree_x3[i] = rand() % 70 + 50;
        tree_y1[i] = -(rand() % 140) - 30;
        tree_y2[i] = -(rand() % 60) - 110;
        tree_y3[i] = -(rand() % 140) - 30;
    }
}

int main(){
    if(!glfwInit()) {
        cerr << "Can't initialize GLFW" << endl;
        glfwTerminate();
        exit (EXIT_FAILURE);
    }
    
    glfwSetErrorCallback(err_function);
    GLFWwindow * win;
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
    win = glfwCreateWindow(100, 50, "Age Of Empires 2", NULL, NULL);
    if (!win) {
        cerr << "Can't create window" << endl;
        exit (EXIT_FAILURE);
    }
    
    glfwSetWindowRefreshCallback(win, win_refresh);
    /* On Mac with Retina display there is a discrepancy between units measured in
     * "screen coordinates" and "pixels" */
    glfwSetWindowSizeCallback(win, win_resize);  /* use this for non-retina displays */
    //glfwSetFramebufferSizeCallback(win, win_resize); /* use this for retina displays */
    glfwSetKeyCallback(win, key_handler);
    glfwSetCursorPosCallback(win, cursor_handler);
    glfwSetScrollCallback(win, scroll_handler);
    glfwMakeContextCurrent(win);
    
    /* glewInit must be invoked AFTER glfwMakeContextCurrent() */
    GLenum err = glewInit();
    if (err != GLEW_OK) {
        fprintf (stderr, "GLEW init error %s\n", glewGetErrorString(err));
        exit (EXIT_FAILURE);
    }
    
    /* GL functions can be called, only AFTER the window is created */
    const GLubyte *version = glGetString (GL_VERSION);
    printf ("GL Version is %s\n", version);
    
    
    glfwSetWindowSize(win, 450, 300);
    glfwSwapInterval(1);
    init_gl();
    make_model();
    
    start_time = clock();
    win_refresh(win);
    while (!glfwWindowShouldClose(win)) {
        glfwWaitEvents();
    }
    glfwDestroyWindow(win);
    glfwTerminate();
    
    return 0;
}
