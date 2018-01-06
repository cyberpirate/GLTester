//
// Created by joevi on 1/5/2018.
//

#include <memory>
#include <vector>
#include "Drawable.h"

using namespace std;

BoxDrawable* originBox;

void initialize(vector<unique_ptr<Drawable>>& drawables) {

    originBox = new BoxDrawable();

    drawables.push_back(unique_ptr<Drawable>(originBox));
}

void update(float dt) {

}