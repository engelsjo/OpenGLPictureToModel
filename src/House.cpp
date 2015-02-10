//
//  House.cpp
//  ProjectOne
//
//  Created by Joshua Engelsma on 2/7/15.
//
//

#include "House.h"
#define FOOT .1

Cube MainFrame;
Cube MiddleRoofPc;

TPillar roofHalf1;
TPillar roofHalf2;

Cube DoorPost1;
Cube DoorPost2;
TPillar roofHeader;
Cube Door;
Cube Chimmeny;

void House::build (void*){
    
    MainFrame.build_with_params(20 * FOOT, 10 * FOOT, 10 * FOOT, 123, 123, 123);
    
    MiddleRoofPc.build_with_params(24 * FOOT, 2 * FOOT, 10 * FOOT, 64, 64, 64);
    
    roofHalf1.build_with_params(5 * FOOT, 24 * FOOT, 8 * FOOT,102, 51, 0);
    
    roofHalf2.build_with_params(5 * FOOT, 24 * FOOT, 8 * FOOT,102, 51, 0);
    
    DoorPost1.build_with_params(1 * FOOT, 3 * FOOT, 10 * FOOT, 64, 64, 64);
    
    DoorPost2.build_with_params(1 * FOOT, 3 * FOOT, 10 * FOOT, 64, 64, 64);
    
    roofHeader.build_with_params(7 * FOOT, 7 * FOOT, 7 * FOOT, 64, 64, 64);
    
    Door.build_with_params(3 * FOOT, 1 * FOOT, 10 * FOOT, 255, 204, 153);
    
    Chimmeny.build_with_params(4 * FOOT, 4 * FOOT, 8 * FOOT, 128, 128, 128);
}


void House::render(bool outline) const{
    glColor3ub (123, 123, 123);
    
    glPushMatrix(); //main body of house
    glTranslatef(5 * FOOT, 5 * FOOT, 10 * FOOT);
    MainFrame.render(outline);
    glPopMatrix();
    
    glColor3ub (64, 64, 64);
    glPushMatrix(); //middle roof piece
    glTranslatef(5 * FOOT, 15 * FOOT, 10 * FOOT);
    MiddleRoofPc.render(outline);
    glPopMatrix();
    
    glColor3ub (102, 51, 0); //first half of roof
    glPushMatrix();
    glTranslatef(-FOOT, 10 * FOOT, 22 * FOOT);
    glRotatef(-90, 1, 0, 0);
    roofHalf1.render(outline);
    glPopMatrix();
    
    glPushMatrix();  //second half of roof
    glTranslatef(11 * FOOT, 10 * FOOT, -2 * FOOT);
    glRotatef(180, 0, 1, 0);
    glRotatef(-90, 1, 0, 0);
    roofHalf2.render(outline);
    glPopMatrix();
    
    glColor3ub (64, 64, 64);
    glPushMatrix(); //first door post
    glTranslatef(-1.5 * FOOT, 5 * FOOT, 7.5 * FOOT);
    DoorPost1.render(outline);
    glPopMatrix();
    
    glPushMatrix(); //second door post
    glTranslatef(-1.5 * FOOT, 5 * FOOT, 12.5 * FOOT);
    DoorPost2.render(outline);
    glPopMatrix();
    
    glPushMatrix(); //roof top
    glTranslatef(-3* FOOT, 10 * FOOT, 13.5 * FOOT);
    glRotatef(-90, 1, 0, 0);
    roofHeader.render(outline);
    glPopMatrix();
    
    
    glColor3ub (255, 204, 153);
    glPushMatrix(); //door
    glTranslatef(-2.0 * FOOT, 5 * FOOT, 10 * FOOT);
    Door.render(outline);
    glPopMatrix();
    
    glColor3ub (128, 128, 128);
    glPushMatrix();
    glTranslatef(2 * FOOT, 16 * FOOT, 3 * FOOT);
    Chimmeny.render(outline);
    glPopMatrix();
}

