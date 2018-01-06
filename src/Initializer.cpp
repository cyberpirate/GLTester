//
// Created by joevi on 1/5/2018.
//

#include <memory>
#include <vector>
#include <iostream>
#include "Drawables.h"

using namespace std;

BoxDrawable* originBox;
LineSegmentDrawable* cameraLine;

void initialize(vector<unique_ptr<Drawable>>& drawables) {

    originBox = new BoxDrawable();

    cameraLine = new LineSegmentDrawable();


    drawables.push_back(unique_ptr<Drawable>(originBox));
    drawables.push_back(unique_ptr<Drawable>(cameraLine));
}

void update(float dt) {

    // float r = originBox->mColorMod.r;

    // r += dt*0.5;

    // if(r >= 1) r = -1;

    // originBox->mColorMod.r = r;
}