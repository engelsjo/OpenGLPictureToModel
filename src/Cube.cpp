//
//  Cube.cpp
//  ProjectOne
//
//  Created by Joshua Engelsma on 2/3/15.
//
//

#include "Cube.h"
#include <cmath>
/**** NOTE: Cube is centered in the middle of the cube ***** */

using glm::vec3;
void Cube::build_with_params(float length, float width, float height){
    LENGTH = length;
    WIDTH = width;
    HEIGHT = height;
    build((void*)0);
}

void Cube::build(void* data) {
    
    glGenBuffers(1, &vertex_buffer);
    glGenBuffers(1, &index_buffer);
    
    //front face
    vec3 v0 = vec3{-.5 * WIDTH, -.5 * HEIGHT, .5 * LENGTH};
    vec3 v1 = vec3{.5 * WIDTH, -.5 * HEIGHT, .5 * LENGTH};
    vec3 v2 = vec3{.5 * WIDTH, .5 * HEIGHT, .5 * LENGTH};
    vec3 v3 = vec3{-.5 * WIDTH, .5 * HEIGHT, .5 * LENGTH};
    
    //back face
    vec3 v4 = vec3{-.5 * WIDTH, .5 * HEIGHT, -.5 * LENGTH};
    vec3 v5 = vec3{.5 * WIDTH, .5 * HEIGHT, -.5 * LENGTH};
    vec3 v6 = vec3{.5 * WIDTH, -.5 * HEIGHT, -.5 * LENGTH};
    vec3 v7 = vec3{-.5 * WIDTH, -.5 * HEIGHT, -.5 * LENGTH};
    
    //push back 8 vertices
    all_points.push_back(v0);
    all_points.push_back(v1);
    all_points.push_back(v2);
    all_points.push_back(v3);
    all_points.push_back(v4);
    all_points.push_back(v5);
    all_points.push_back(v6);
    all_points.push_back(v7);
    
    for (GLushort i = 0; i < 4; i++){ //front face indices
        all_index.push_back(i);
    }
    
    for (GLushort i = 4; i < 8; i++){ //back face indices
        all_index.push_back(i);
    }
    
    for (GLushort i = 5; i > 1; i--){ //top face indices
        all_index.push_back(i);
    }
    
    vector<GLushort> bottomIndices = {1, 0, 7, 6};
    for (auto i : bottomIndices){ //bottom face
        all_index.push_back(i);
    }
    
    vector<GLushort> rightIndices = {2, 1, 6, 5};
    for (auto i : rightIndices){ //right face
        all_index.push_back(i);
    }
    
    vector<GLushort> leftIndices = {7, 0, 3, 4};
    for (auto i : leftIndices){ //left face
        all_index.push_back(i);
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
    //post_build();
    top_count = 24;
}


void Cube::render(bool outline) const {
    /* bind vertex buffer */
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glVertexPointer(3, GL_FLOAT, 0, 0);
    glDisableClientState(GL_COLOR_ARRAY);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
    /* render the polygon */
    glPolygonMode(GL_FRONT, GL_FILL);
    glColor3ub (255, 0, 0);
    glDrawRangeElements(GL_QUADS, 0, 0, top_count, GL_UNSIGNED_SHORT, 0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    
    glEnableClientState(GL_COLOR_ARRAY);
    
}