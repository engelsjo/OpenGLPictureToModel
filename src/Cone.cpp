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
void Cone::build(void* data) {
    
    glGenBuffers(1, &vertex_buffer);
    glGenBuffers(1, &index_buffer);
    
    vec3 topPt = vec3{0, 0, HEIGHT};
    vec3 centerPt = vec3{0, 0, 0};
    all_points.push_back(topPt);
    all_points.push_back(centerPt);
    
    float anglePart = 360.0 / SUB_DIVIDE;
    float angleCounter = 0;
    
    /**************    all vertices of the cone    **************/
    for(int i = 0; i < SUB_DIVIDE; i ++){ //vertices
        float x = RADIUS * cos(angleCounter);
        float y = RADIUS * sin(angleCounter);
        vec3 v0 = vec3{x, y, 0};
        all_points.push_back(v0);
        angleCounter += anglePart;
    }
    
    /**************    'side' wrapping of cone'    **************/
    for(int i = 2; i < SUB_DIVIDE + 1; i++){ //indices
        all_index.push_back(i);
        all_index.push_back(i + 1);
        all_index.push_back(0);
    }
    
    all_index.push_back(1); //make sure that cone wraps around
    all_index.push_back(2);
    all_index.push_back(0);
    
    /**************    'bottom face of cone'    **************/
    for(int i = 2; i < SUB_DIVIDE + 1; i++){ //indices
        all_index.push_back(i);
        all_index.push_back(i + 1);
        all_index.push_back(1);
    }
    
    all_index.push_back(2); //make sure that base wraps around
    all_index.push_back(3);
    all_index.push_back(1);
    
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

void Cone::render(bool outline) const {
    /* bind vertex buffer */
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glVertexPointer(3, GL_FLOAT, 0, 0);
    glDisableClientState(GL_COLOR_ARRAY);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
    /* render the polygon */
    glPolygonMode(GL_FRONT, GL_FILL);
    glColor3ub (255, 0, 0);
    glDrawRangeElements(GL_TRIANGLES, 0, 0, all_index.size(), GL_UNSIGNED_SHORT, 0);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    
    glEnableClientState(GL_COLOR_ARRAY);

}