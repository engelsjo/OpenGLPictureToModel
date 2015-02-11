/*
 * Castle.cpp
 *
 *  Created on: Feb 7, 2015
 *      Author: Zachary Ash
 */

#include "Castle.h"

void Castle::build(void*) {
    glGenBuffers(1, &vertex_buffer);
    glGenBuffers(1, &index_buffer);
    glGenBuffers(1, &color_buffer);
    
    float z[] = {0*FOOT,7*FOOT,10*FOOT};
    float x[] = {5*FOOT,5*FOOT,3*FOOT};
    for(int i = 0; i < 3; i++) {
        all_points.push_back(glm::vec3{x[i], 20*FOOT,z[i]});
        all_colors.push_back(glm::vec3{0.0f, 0.0f, 0.0f});
        all_index.push_back(i);
    }
    for(int i = 0; i < 3; i++) {
        all_points.push_back(glm::vec3{-x[2-i], 20*FOOT,z[2-i]});
        all_colors.push_back(glm::vec3{0.0f, 0.0f, 0.0f});
        all_index.push_back(3+i);
    }
    all_index.push_back(0);
    
    
	castle.build_with_params(60 * FOOT, 40 * FOOT, 40 * FOOT, 75, 75, 75);
	tower.build_cylinder(5 * FOOT,  4* FOOT, 30, 200, 200, 200);
	roof.build_with_params(6 * FOOT, 10 * FOOT, 30, 102, 0, 0);
	bigTower.build_cylinder(10 * FOOT, 9 * FOOT, 30, 255, 255, 255);
	bigRoof.build_with_params(12 * FOOT, 20 * FOOT, 30, 255, 0, 0);
    
    
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, all_points.size() * sizeof(float) * 3, NULL, GL_DYNAMIC_DRAW);
    float *vertex_ptr = (float *) glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
    
    /* Initialize the vertices */
    float *ptr = vertex_ptr;
    for (auto v : all_points) {
        ptr[0] = v.x;
        ptr[1] = v.y;
        ptr[2] = v.z;
        ptr += 3;
    }
    glUnmapBuffer(GL_ARRAY_BUFFER);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    glBindBuffer(GL_ARRAY_BUFFER, color_buffer);
    glBufferData(GL_ARRAY_BUFFER, all_colors.size() * sizeof(float) * 3, NULL, GL_DYNAMIC_DRAW);
    float *color_ptr = (float *) glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
    
    /* Initialize the vertices */
    float *cptr = color_ptr;
    for (auto v : all_colors) {
        cptr[0] = v.x;
        cptr[1] = v.y;
        cptr[2] = v.z;
        cptr += 3;
    }
    glUnmapBuffer(GL_ARRAY_BUFFER);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    /* Initialize the indices */
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, all_index.size() * sizeof(GLushort), all_index.data(), GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Castle::render(bool) const {
    
    
    glPushAttrib(GL_ENABLE_BIT);
    /* bind vertex buffer */
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glVertexPointer(3, GL_FLOAT, 0, 0);
    glBindBuffer(GL_ARRAY_BUFFER, color_buffer);
    glColorPointer(3, GL_FLOAT, 0, 0);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
    glDrawElements(GL_LINE_STRIP, 7, GL_UNSIGNED_SHORT, 0);

    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    
    glPopAttrib();

	//render castle building

	glPushMatrix();
	glTranslatef(0, 0, 30 * FOOT);
	castle.render(false);
	glPopMatrix();

	//render towers

	glPushMatrix();
	glTranslatef(17 * FOOT, 17 * FOOT, 65 * FOOT);
	tower.render(false);

	glTranslatef(-34 * FOOT, 0, 0);
	tower.render(false);

	glTranslatef(0, -34 * FOOT, 0);
	tower.render(false);

	glTranslatef(34 * FOOT, 0, 0);
	tower.render(false);

	glTranslatef(0, 0, 5* FOOT);
	roof.render(false);

	glTranslatef(-34 * FOOT, 0, 0);
	roof.render(false);

	glTranslatef(0, 34 * FOOT, 0);
	roof.render(false);

	glTranslatef(34 * FOOT, 0, 0);
	roof.render(false);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0,0, 70 * FOOT);
	bigTower.render(false);

	glTranslatef(0, 0, 10 * FOOT);
	bigRoof.render(false);
	glPopMatrix();
    
    
}
