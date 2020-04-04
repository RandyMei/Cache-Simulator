//
// Created by Randy Mei on 2020/4/3.
//

#ifndef CACHE_SIM_WRITE_MISS_POLICY_H
#define CACHE_SIM_WRITE_MISS_POLICY_H

#include "defines.h"
#include "Handler.h"

class WritemissPolicy {
public:
    explicit WritemissPolicy(bool writeBack = true, bool writeAllocate = true) :
            _writeBack(writeBack), _writeAllocate(writeAllocate) {}

    inline bool writeBack() const {
        return _writeBack;
    }

    inline bool writeAllocate() const {
        return _writeAllocate;
    }

private:
    bool _writeBack;
    bool _writeAllocate;
};

#endif //CACHE_SIM_WRITE_MISS_POLICY_H