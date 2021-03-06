//
// Created by Randy Mei on 2020/4/3.
//

#ifndef CACHE_SIM_BLOCK_POLICY_H
#define CACHE_SIM_BLOCK_POLICY_H

#include <cstdio>
#include <cmath>

#include "defines.h"
#include "Handler.h"

class BlockPolicy {

public:
    explicit BlockPolicy(const u32 size = 8) {
        switch (size) {
            case 64u: _shift = 9; break;
            case 32u: _shift = 8; break;
            case  8u: _shift = 6; break;
            default : printf("Invalid block size: %u\n", size); exit(0);
        }
        _blockSize = size << 3u;
    }

    void registerHandler(Handler *handler) {
        _handler = handler;
        _blockNum = handler->capacity() / blockSize();
    }

    inline bool inBlock(const u64 address, const u32 index) const {
        return (address >> shift()) == index;
    }

    inline u64 getIndex(const u64 address) const { // physical memory block index
        return address >> shift();
    }

    inline u32 getOffset(const u64 address) const { // physical memory block offset
        switch (blockSize() >> 3u) {
            case 64u: return address & 0b111111111u;
            case 32u: return address & 0b011111111u;
            case  8u: return address & 0b000111111u;
            default : printf("Invalid block size: %uB\n", blockSize() >> 3u); exit(0);
        }
    }

    inline u32 blockSize() const {
        return _blockSize;
    }

    inline u32 blockNum() const {
        return _blockNum;
    }

    inline u32 shift() const {
        return _shift;
    }

    inline void print() {
        printf("Block Policy\n");
        printf("\tBlock size: %dB\n", blockSize() >> 3u);
        printf("\tBlock number: %d (2^%d)\n", blockNum(), static_cast<u32>(log2(handler()->capacity())) - shift());
    }

    inline Handler *handler() const {
        return _handler;
    }

private:
    Handler *_handler{};

    u32 _blockSize;
    u32 _blockNum{};
    u32 _shift;

};

#endif //CACHE_SIM_BLOCK_POLICY_H
