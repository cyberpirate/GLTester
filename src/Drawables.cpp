//
// Created by joevi on 1/5/2018.
//

#include "Drawables.h"

using namespace glm;

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
    mColorModID = glGetUniformLocation(mProgram, "colorMod");
}

void BoxDrawable::draw(mat4 mViewProjection) {

    mat4 finalMatrix = mViewProjection * mModelMatrix;

    glUseProgram(mProgram);

    glUniformMatrix4fv(mMatrixID, 1, GL_FALSE, &finalMatrix[0][0]);
    glUniform3fv(mColorModID, 1, &mColorMod[0]);

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

LineSegmentDrawable::LineSegmentDrawable() :
    BoxDrawable(),
    wh(0.1f, 0.1f),
    length(2.0f),
    tipPercent(0.1f)
{
    
}

void LineSegmentDrawable::draw(mat4 mViewProjection) {

    mat4 cModelMatrix = mModelMatrix;
    vec3 cColorMod = mColorMod;

    mat4 lineModelMatrix;

    lineModelMatrix = translate(mat4(), pos) * toMat4(rot);

    //BODY
    mModelMatrix = scale(mModelMatrix, vec3(wh.x/2, wh.y/2, length * 0.5f * (1 - tipPercent)));
    mModelMatrix = translate(mModelMatrix, vec3(0, 0, -1.0f));
    BoxDrawable::draw(mViewProjection * lineModelMatrix);

    //TIP
    mModelMatrix = cModelMatrix;
    mModelMatrix = scale(mModelMatrix, vec3(wh.x/2, wh.y/2, length * 0.5f * tipPercent));
    mModelMatrix = translate(mModelMatrix, vec3(0, 0, 1 - ( length * 2 * (1 / (tipPercent*2))) ));
    mColorMod = vec3(-1, 1, -1);
    BoxDrawable::draw(mViewProjection * lineModelMatrix);

    mModelMatrix = cModelMatrix;
    mColorMod = cColorMod;

}
