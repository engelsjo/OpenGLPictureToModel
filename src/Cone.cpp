//
//  Cone.cpp
//  ProjectOne
//
//  Created by Joshua Engelsma on 2/3/15.
//
//

#include "Cone.h"
#include <cmath>

using glm::vec3;
void Cone::build_with_params(float radius, float height, float subdivisions, float r, float g, float b){
    RADIUS = radius;
    HEIGHT = height;
    SUB_DIVIDE = subdivisions;
    COLOR_R = r / 255.0f;
    COLOR_G = g / 255.0f;
    COLOR_B = b / 255.0f;
    build((void*)0);
}

void Cone::build(void* data) {
    
    float color_diff = 100;
    
    glGenBuffers(1, &vertex_buffer);
    glGenBuffers(1, &index_buffer);
    glGenBuffers(1, &color_buffer);
    
    vec3 topPt = vec3{0, 0, HEIGHT};
    vec3 centerPt = vec3{0, 0, 0};
    
    float delta  = 2 * M_PI / SUB_DIVIDE;
    float angle = 0;
    
    /**************    all vertices of the cone    **************/
    for(int i = 0; i < SUB_DIVIDE; i ++){ //vertices
        float x = RADIUS * cos(angle);
        float y = RADIUS * sin(angle);
        vec3 v0 = vec3{x, y, 0};
        all_points.push_back(v0);
        all_colors.push_back(vec3{COLOR_R, COLOR_G, COLOR_B});
        //all_colors.push_back(glm::vec3{.3, abs(cos(x)), abs(sin(y))});
        angle += delta;
    }
    all_points.push_back(topPt);
    all_colors.push_back(vec3{COLOR_R + color_diff/255.0f, COLOR_G+color_diff/255.0f, COLOR_B + color_diff/255.0f});
    //all_colors.push_back(glm::vec3{.999, 0, 0});
    all_points.push_back(centerPt);
    //all_colors.push_back(vec3{1, .9, 1});
    all_colors.push_back(vec3{COLOR_R - color_diff/255.0f, COLOR_G - color_diff/255.0f, COLOR_B - color_diff/255.0f});
    
    /**************    'side' wrapping of cone'    **************/
    all_index.push_back(SUB_DIVIDE); //top point is center of triangle fan
    for(int i = 0; i < SUB_DIVIDE; i++){
        all_index.push_back(i);
    }
    all_index.push_back(0); //wrap around
    
    /**************    'bottom face of cone'    **************/
    all_index.push_back(SUB_DIVIDE + 1); //bottom center is center of tri fan
    for(int i = SUB_DIVIDE - 1; i >= 0; i--){
        all_index.push_back(i);
    }
    all_index.push_back(SUB_DIVIDE - 1); //wrap around
    
    
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
    
    glBindBuffer(GL_ARRAY_BUFFER, color_buffer); //init the color buffer
    glBufferData(GL_ARRAY_BUFFER, all_colors.size() * sizeof(float) * 3, NULL, GL_DYNAMIC_DRAW);
    float *color_ptr = (float *) glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
    
    /* Initialize the vertices */
    float *p = color_ptr;
    for (auto v : all_colors) {
        p[0] = v.x;
        p[1] = v.y;
        p[2] = v.z;
        p += 3;
    }
    glUnmapBuffer(GL_ARRAY_BUFFER);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    
    /* Initialize the indices */
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, all_index.size() * sizeof(GLushort), all_index.data(), GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    
}

void Cone::render(bool outline) const {
    glPushAttrib(GL_ENABLE_BIT);
    /* bind vertex buffer */
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glVertexPointer(3, GL_FLOAT, 0, 0);
    glBindBuffer(GL_ARRAY_BUFFER, color_buffer);
    glColorPointer(3, GL_FLOAT, 0, 0);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
    int N = SUB_DIVIDE + 2;
    glDrawElements(GL_TRIANGLE_FAN, N, GL_UNSIGNED_SHORT, 0);
    glDrawElements(GL_TRIANGLE_FAN, SUB_DIVIDE + 2, GL_UNSIGNED_SHORT, (void*) (sizeof(GLushort) * N));
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    
    glPopAttrib();
}