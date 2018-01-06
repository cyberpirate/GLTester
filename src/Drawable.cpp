//
// Created by joevi on 1/5/2018.
//

#include "Drawable.h"

BoxDrawable::BoxDrawable() {
    //allocate vertex buffer
    glGenBuffers(1, &mVertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(box_vertex_buffer_data), box_vertex_buffer_data, GL_STATIC_DRAW);

    //allocate color buffer
    glGenBuffers(1, &mColorBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, mColorBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(box_color_buffer_data), box_color_buffer_data, GL_STATIC_DRAW);

    mProgram =  LoadShaders( "assets/shaders/box.verts", "assets/shaders/box.frags" );

    mMatrixID = glGetUniformLocation(mProgram, "MVP");
}

void BoxDrawable::draw(glm::mat4 mViewProjection) {

    glm::mat4 finalMatrix = mViewProjection * mModelMatrix;

    glUseProgram(mProgram);

    glUniformMatrix4fv(mMatrixID, 1, GL_FALSE, &finalMatrix[0][0]);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);
    glVertexAttribPointer(
            0,
            3,
            GL_FLOAT,
            GL_FALSE,
            0,
            (void*) 0
    );

    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, mColorBuffer);
    glVertexAttribPointer(
            1,
            3,
            GL_FLOAT,
            GL_FALSE,
            0,
            (void*) 0
    );

    glDrawArrays(GL_TRIANGLES, 0, 12*3);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
}
