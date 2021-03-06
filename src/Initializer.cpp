//
// Created by joevi on 1/5/2018.
//

#include <memory>
#include <vector>
#include <iostream>
#include <thread>
#include <mutex>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Drawables.h"
#include "utils/strUtils.h"
#include "utils/ScopedMutex.h"

using namespace std;
using namespace glm;

BoxDrawable* originBox;
LineSegmentDrawable* cameraLine;

mutex mtx;

vec3 pos;
quat rot;

void read_cin() {

    for (std::string line; std::getline(std::cin, line);) {

        string name;

        name = "pos";
        pullFloats(name, line, &pos[0], 3);
        name = "rot";
        pullFloats(name, line, &rot[0], 4);
    }

}


void initialize(vector<unique_ptr<Drawable>>& drawables) {

    originBox = new BoxDrawable();

    cameraLine = new LineSegmentDrawable();

    drawables.push_back(unique_ptr<Drawable>(originBox));
    drawables.push_back(unique_ptr<Drawable>(cameraLine));
}

void update(float dt) {

    ScopedMutex sMtx(&mtx);

    cameraLine->pos = pos;
    cameraLine->rot = rot;

//    cameraLine->rot = toQuat(rotate(toMat4(cameraLine->rot), glm::radians(90.0f * dt), vec3(0, 1, 0)));
//    cameraLine->pos.y += dt;
//
//    if(cameraLine->pos.y > 1) cameraLine->pos.y = -1;



    // float r = originBox->mColorMod.r;
    // r += dt*0.5;
    // if(r >= 1) r = -1;
    // originBox->mColorMod.r = r;
}