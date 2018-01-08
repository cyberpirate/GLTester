//
// Created by joevi on 1/7/2018.
//

#ifndef GLTESTER_STRUTILS_H
#define GLTESTER_STRUTILS_H

#include <iostream>
#include <cstring>
#include <string>

void pullFloats(std::string& name, std::string& source, float* dst, int length) {

    int startIndex, endIndex;

    startIndex = source.find(name);
    if(startIndex == std::string::npos) return;


    float* buffer = new float[length];

    startIndex += name.length() + 1;

    for(int i = 0; i < length; i++) {

        if(startIndex >= source.length()) {
            buffer[i] = 0;
            continue;
        }

        endIndex = source.find(":", startIndex);
        if(endIndex == std::string::npos) endIndex = source.length();

        std::string numStr = source.substr(startIndex, endIndex - startIndex);
        buffer[i] = atof(numStr.c_str());
        startIndex = endIndex+1;
    }

    memcpy(dst, buffer, sizeof(float)*length);

    delete[] buffer;

}

#endif //GLTESTER_STRUTILS_H
