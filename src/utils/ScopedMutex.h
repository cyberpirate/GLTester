//
// Created by joevi on 1/7/2018.
//

#ifndef GLTESTER_SCOPEDMUTEX_H
#define GLTESTER_SCOPEDMUTEX_H

#include <mutex>

class ScopedMutex {
    std::mutex* mtx;


    ScopedMutex(std::mutex* m) {
        mtx = m;
        mtx->lock();
    }

    ~ScopedMutex() {
        mtx->unlock();
    }
};

#endif //GLTESTER_SCOPEDMUTEX_H
