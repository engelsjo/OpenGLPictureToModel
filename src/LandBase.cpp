//
//  LandBase.cpp
//  ProjectOne
//
//  Created by Joshua Engelsma on 2/2/15.
//
//

#include "LandBase.h"


using glm::vec3;
void LandBase::build(void* data) {
    glGenBuffers(1, &vertex_buffer);
    glGenBuffers(1, &index_buffer);
    
    float Z = THICKNESS;
    vec3 c1, c2, c3, c4;
    
    //top face
    c1 = vec3{-.5*WIDTH, -.5*LENGTH, Z}; //bottom-left
    c2 = vec3{.5*WIDTH, -.5*LENGTH, Z};  //bottom-right
    c3 = vec3{.5*WIDTH, .5*LENGTH, Z};   //top-right
    c4 = vec3{-.5*WIDTH, .5*LENGTH, Z};  //top-left
        
    all_index.push_back(all_points.size());
    all_points.push_back(c1);
    all_index.push_back(all_points.size());
    all_points.push_back(c2);
    all_index.push_back(all_points.size());
    all_points.push_back(c3);
    all_index.push_back(all_points.size());
    all_points.push_back(c4);
    
    top_count = all_index.size();
    
    //bottom face
    Z = -THICKNESS;
    c1 = vec3{-.5*WIDTH, -.5*LENGTH, Z}; //bottom-left
    c2 = vec3{.5*WIDTH, -.5*LENGTH, Z};  //bottom-right
    c3 = vec3{.5*WIDTH, .5*LENGTH, Z};   //top-right
    c4 = vec3{-.5*WIDTH, .5*LENGTH, Z};  //top-left
    
    all_index.push_back(all_points.size());
    all_points.push_back(c1);
    all_index.push_back(all_points.size());
    all_points.push_back(c2);
    all_index.push_back(all_points.size());
    all_points.push_back(c3);
    all_index.push_back(all_points.size());
    all_points.push_back(c4);
    
    
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


void LandBase::render(bool outline) const {
    
    /* bind vertex buffer */
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glVertexPointer(3, GL_FLOAT, 0, 0);
    glDisableClientState(GL_COLOR_ARRAY);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
    /* render the polygon */
    glPolygonMode(GL_FRONT, GL_FILL);
    glFrontFace(GL_CCW);
    glColor3ub (255, 0, 0);
    glDrawRangeElements(GL_QUAD_STRIP, 0, 0, top_count, GL_UNSIGNED_SHORT, 0);
    glFrontFace(GL_CW);
    glColor3ub (255, 0, 0);
    glDrawRangeElements(GL_QUAD_STRIP, 0, 0, top_count, GL_UNSIGNED_SHORT,
                        (void *) (sizeof(GLushort) * (top_count)));
    glFrontFace(GL_CCW);
    glColor3ub (200, 30, 0);
    glDrawRangeElements(GL_QUAD_STRIP, 0, 0, top_count, GL_UNSIGNED_SHORT,
                        (void *) (sizeof(GLushort) * (2*top_count)));
    glFrontFace(GL_CCW);
    glColor3ub (120, 120, 120);
    glDrawRangeElements(GL_QUAD_STRIP, 0, 0, top_count, GL_UNSIGNED_SHORT,
                        (void *) (sizeof(GLushort) * (3*top_count)));
    /* unbind the buffers */
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    
    glEnableClientState(GL_COLOR_ARRAY);

}