//
//  TPillar.cpp
//  ProjectOne
//
//  Created by Joshua Engelsma on 2/7/15.
//
//

#include "TPillar.h"
#include <vector>

/* NOTE: Pillar is centered on bottom rectangular corner */

using glm::vec3;

void TPillar::build_with_params(float length, float width, float height){
    LENGTH = length;
    WIDTH = width;
    HEIGHT = height;
    build((void*)0);
}

void TPillar::build(void* data) {
    
    glGenBuffers(1, &vertex_buffer);
    glGenBuffers(1, &index_buffer);
    
    //build the 6 vertexes
    vec3 v0 = vec3{0, 0, 0};
    vec3 v1 = vec3{LENGTH, 0, 0};
    vec3 v2 = vec3{LENGTH, WIDTH, 0};
    vec3 v3 = vec3{0, WIDTH, 0};
    vec3 v4 = vec3{LENGTH, WIDTH, HEIGHT};
    vec3 v5 = vec3{LENGTH, 0, HEIGHT};
    
    all_points.push_back(v0); //add vertices
    all_points.push_back(v1);
    all_points.push_back(v2);
    all_points.push_back(v3);
    all_points.push_back(v4);
    all_points.push_back(v5);
    
    //quad - strip indices
    vector<int> quad_indices = vector<int>{0, 3, 1, 2, 5, 4, 0, 3};
    for (auto index : quad_indices){
        all_index.push_back(index);
    }
    
    //front triangle side
    vector<int> front_indices = vector<int>{5, 0, 1};
    for (auto index : front_indices){
        all_index.push_back(index);
    }
    
    //back triangle side
    vector<int> back_indices = vector<int>{2, 3, 4};
    for (auto index : back_indices){
        all_index.push_back(index);
    }
    
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
    
    /* Initialize the indices */
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, all_index.size() * sizeof(GLushort), all_index.data(), GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void TPillar::render(bool outline) const {
    /* bind vertex buffer */
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glVertexPointer(3, GL_FLOAT, 0, 0);
    glDisableClientState(GL_COLOR_ARRAY);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
    /* render the polygon */
    glPolygonMode(GL_FRONT, GL_FILL);
    glColor3ub (255, 0, 0);
    
    glDrawElements(GL_QUAD_STRIP, 8, GL_UNSIGNED_SHORT, 0);
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_SHORT, (void*) (sizeof(GLushort) * 8));
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_SHORT, (void*) (sizeof(GLushort) * 11));
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    
    glEnableClientState(GL_COLOR_ARRAY);
    
}