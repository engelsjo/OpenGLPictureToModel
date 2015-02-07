//
//  TCone.cpp
//  ProjectOne
//
//  Created by Joshua Engelsma on 2/5/15.
//
//

#include "TCone.h"

using glm::vec3;
void TCone::build_with_params(float height, float x_rad_t, float
                              y_rad_t, float x_rad_b, float y_rad_b, float subdivisions){
    CONE_HEIGHT = height;
    
    x_rad_top = x_rad_t;
    y_rad_top = y_rad_t;
    
    x_rad_bot = x_rad_b;
    y_rad_bot = y_rad_b;
    
    N_POINTS = subdivisions;
    build((void*)0);
}

void TCone::build(void* data) {
    
    glGenBuffers(1, &vertex_buffer);
    glGenBuffers(1, &index_buffer);
    
    float delta  = 2 * M_PI / N_POINTS;
    float angle = 0;
    for(int k = 0; k < N_POINTS; k++){ //top circle points
        float x = x_rad_top * cos(angle);
        float y = y_rad_top * sin(angle);
        vec3 vertex = vec3{x, y, CONE_HEIGHT};
        all_points.push_back(vertex);
        angle += delta;
    }
    
    for(int k = 0; k < N_POINTS; k++){ //bottom circle points
        float x = x_rad_bot * cos(angle);
        float y = y_rad_bot * sin(angle);
        vec3 vertex = vec3{x, y, -CONE_HEIGHT};
        all_points.push_back(vertex);
        angle += delta;
    }
    vec3 top_center = vec3{0, 0, CONE_HEIGHT}; //origin
    all_points.push_back(top_center);
    vec3 bot_center = vec3{0, 0, -CONE_HEIGHT};
    all_points.push_back(bot_center);
    
    
    for(int k = 0; k < N_POINTS; k++){ //indices
        all_index.push_back(k);
        all_index.push_back(k + N_POINTS);
    }
    
    all_index.push_back(0); //wrap around
    all_index.push_back(N_POINTS);
    
    //first index of triangle fan for top_center
    all_index.push_back(N_POINTS * 2);
    for (int k = 0; k < N_POINTS; k++){
        //index of rest of triangle fan
        all_index.push_back(k);
    }
    all_index.push_back(0); //close the triangle fan
    
    //first index of triangle fan for bot_center
    all_index.push_back(N_POINTS * 2 + 1);
    for(int k = (2 * N_POINTS -1); k >=  N_POINTS; k--){ //ccw
        all_index.push_back(k);
    }
    all_index.push_back(2 * N_POINTS - 1); //wrap around
    
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

void TCone::render(bool outline) const {
    /* bind vertex buffer */
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glVertexPointer(3, GL_FLOAT, 0, 0);
    glDisableClientState(GL_COLOR_ARRAY);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
    /* render the polygon */
    glPolygonMode(GL_FRONT, GL_FILL);
    glColor3ub (255, 0, 0);
    
    int N = 2* N_POINTS + 2;
    int Z = N + N_POINTS + 2;
    glDrawElements(GL_QUAD_STRIP, N, GL_UNSIGNED_SHORT, 0);
    glDrawElements(GL_TRIANGLE_FAN, N_POINTS + 2, GL_UNSIGNED_SHORT, (void*) (sizeof(GLushort) * N));
    glDrawElements(GL_TRIANGLE_FAN, N_POINTS + 2, GL_UNSIGNED_SHORT, (void*) (sizeof(GLushort) * Z));
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    
    glEnableClientState(GL_COLOR_ARRAY);
    
}