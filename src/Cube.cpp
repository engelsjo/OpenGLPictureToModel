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
void Cube::build_with_params(float length, float width, float height, float r, float g, float b){
    LENGTH = length;
    WIDTH = width;
    HEIGHT = height;
    
    COLOR_R = r / 255.0f;
    COLOR_G = g / 255.0f;
    COLOR_B = b / 255.0f;
    
    build((void*)0);
}

void Cube::build(void* data) {
    
    glGenBuffers(1, &vertex_buffer);
    glGenBuffers(1, &index_buffer);
    glGenBuffers(1, &color_buffer);
    
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
    all_colors.push_back(vec3{COLOR_R, COLOR_G, COLOR_B});
    all_points.push_back(v1);
    all_colors.push_back(vec3{COLOR_R + 20/255.0f, COLOR_G + 20/255.0f, COLOR_B + 20/255.0f});
    all_points.push_back(v2);
    all_colors.push_back(vec3{COLOR_R + 30/255.0f, COLOR_G + 30/255.0f, COLOR_B + 30/255.0f});
    all_points.push_back(v3);
    all_colors.push_back(vec3{COLOR_R + 40/255.0f, COLOR_G + 40/255.0f, COLOR_B + 40/255.0f});
    all_points.push_back(v4);
    all_colors.push_back(vec3{COLOR_R + 50/255.0f, COLOR_G + 50/255.0f, COLOR_B + 50/255.0f});
    all_points.push_back(v5);
    all_colors.push_back(vec3{COLOR_R - 20/255.0f, COLOR_G - 20/255.0f, COLOR_B - 20/255.0f});
    all_points.push_back(v6);
    all_colors.push_back(vec3{COLOR_R - 30/255.0f, COLOR_G - 30/255.0f, COLOR_B - 30/255.0f});
    all_points.push_back(v7);
    all_colors.push_back(vec3{COLOR_R - 40/255.0f, COLOR_G - 40/255.0f, COLOR_B - 40/255.0f});
    
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
    //post_build();
    top_count = 24;
}


void Cube::render(bool outline) const {
    glPushAttrib(GL_ENABLE_BIT);
    /* bind vertex buffer */
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glVertexPointer(3, GL_FLOAT, 0, 0);
    glBindBuffer(GL_ARRAY_BUFFER, color_buffer);
    glColorPointer(3, GL_FLOAT, 0, 0);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
    glDrawRangeElements(GL_QUADS, 0, 0, top_count, GL_UNSIGNED_SHORT, 0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    
    glPopAttrib();
}