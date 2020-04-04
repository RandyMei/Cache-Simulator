//
// Created by Randy Mei on 2020/4/3.
//

#ifndef CACHE_SIM_HANDLER_H
#define CACHE_SIM_HANDLER_H

#include "defines.h"
#include "Op.h"
#include "Reader.h"
#include "Writer.h"

class BlockPolicy;
class MappingPolicy;
class ReplacementPolicy;
class WritemissPolicy;

class Handler {
public:
    Handler(BlockPolicy *block, MappingPolicy *mapping, ReplacementPolicy *replacement,
                     WritemissPolicy *writemiss, Reader *reader, Writer *writer, u32 capacity = 128u << 13u);

    inline u32 capacity() const { return _capacity; }

    bool processSingleLine(Op &op);

    void processAll() {
        Op op;
        printf("start process\n");
        while (processSingleLine(op));
        printf("process finished\n");
    }

    inline bool getNextOp(Op &op) {
        if (_reader->getNextOp(op)) {
            opNum++;
            return true;
        } else {
            return false;
        }
    }

    inline void hit() {
        hitNum++;
        _writer->hit();
    }

    inline void miss() {
        _writer->miss();
    }

    // getters: const provided

    inline BlockPolicy *block() const {
        return _block;
    }

    inline MappingPolicy *mapping() const {
        return _mapping;
    }

    inline ReplacementPolicy *replacement() const {
        return _replacement;
    }

    inline WritemissPolicy *writemiss() const {
        return _writemiss;
    }

private:
    const u32 _capacity{};

    Reader *_reader{};
    Writer *_writer{};
    BlockPolicy *_block{};
    MappingPolicy *_mapping{};
    ReplacementPolicy *_replacement{};
    WritemissPolicy *_writemiss{};

    u32 opNum = 0;
    u32 hitNum = 0;
};

#endif //CACHE_SIM_HANDLER_H