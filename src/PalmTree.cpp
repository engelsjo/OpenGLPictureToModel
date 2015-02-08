//
//  PalmTree.cpp
//  ProjectOne
//
//  Created by Joshua Engelsma on 2/7/15.
//
//

#include "PalmTree.h"
#include <vector>
TCone cyl1; //build the tree trunk
TCone cyl2;
TCone cyl3;
TCone cyl4;
TCone cyl5;

TCone leaf1; //build 4 leaves
TCone leaf2;
TCone leaf3;
TCone leaf4;


void PalmTree::build(void*){
    /*                     HEIGHT   TOP RADX  TOP RADY   BOT X  BOT Y     */
    cyl1.build_with_params(5*FOOT, .9 * FOOT, .9 * FOOT, FOOT, FOOT, 25.0);
    cyl2.build_with_params(5*FOOT, .8 * FOOT, .8 * FOOT, .9 * FOOT, .9 * FOOT, 25.0);
    cyl3.build_with_params(5*FOOT, .7 * FOOT, .7 * FOOT, .8 * FOOT, .8 * FOOT, 25.0);
    cyl4.build_with_params(5*FOOT, .6 * FOOT, .6 * FOOT, .7 * FOOT, .7 * FOOT, 25.0);
    cyl5.build_with_params(5*FOOT, .5 * FOOT, .5 * FOOT, .6 * FOOT, .6 * FOOT, 25.0);
    
    leaf1.build_with_params(.01*FOOT, 4 * FOOT, FOOT, 4 * FOOT, FOOT, 25.0);
    leaf2.build_with_params(.01*FOOT, 4 * FOOT, FOOT, 4 * FOOT, FOOT, 25.0);
    leaf3.build_with_params(.01*FOOT, 4 * FOOT, FOOT, 4 * FOOT, FOOT, 25.0);
    leaf4.build_with_params(.01*FOOT, 4 * FOOT, FOOT, 4 * FOOT, FOOT, 25.0);
    
}


void PalmTree::render(bool outline) const{
    glColor3ub (102, 51, 0);
    vector<TCone> trunk_pieces = vector<TCone>{cyl1, cyl2, cyl3, cyl4, cyl5};
    for (int i = 1; i <= 5; i++){ //render the trunk
        glPushMatrix();
        double feet_to_translate = 5 * FOOT * i;
        glTranslatef(0.0, 0.0, feet_to_translate);
        trunk_pieces[i-1].render(outline);
        glPopMatrix();
    }
    
    glColor3ub(0, 153, 0); //leaf 1
    glPushMatrix();
    glTranslatef(4 * FOOT, 0, 30 * FOOT);
    glRotatef(15, 0, 1, 0);
    leaf1.render(outline);
    glPopMatrix();
    
    glPushMatrix(); //leaf 2
    glTranslatef(-4 * FOOT, 0, 30 * FOOT);
    glRotatef(-15, 0, 1, 0);
    leaf2.render(outline);
    glPopMatrix();
    
    glPushMatrix(); //leaf 3
    glRotatef(90, 0, 0, 1);
    glTranslatef(4 * FOOT, 0, 30 * FOOT);
    glRotatef(15, 0, 1, 0);
    leaf3.render(outline);
    glPopMatrix();
    
    glPushMatrix(); //leaf 4
    glRotatef(-90, 0, 0, 1);
    glTranslatef(4 * FOOT, 0, 30 * FOOT);
    glRotatef(15, 0, 1, 0);
    leaf4.render(outline);
    glPopMatrix();
    
}