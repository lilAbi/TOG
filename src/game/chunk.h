#ifndef TOG_CHUNK_H
#define TOG_CHUNK_H

#include "graphics/meshNode.h"

#include <vector>

constexpr int CHUNK_MAX_X = 8;
constexpr int CHUNK_MAX_Y = 8;
constexpr int CHUNK_MAX_Z = 8;

enum class ChunkStatus {
    EMPTY,
    UNLOADED,
    READY
};

//container for chunk block data and mesh data
class Chunk {
public:
    Chunk();
public:
    ChunkStatus chunkStatus{ChunkStatus::EMPTY};
    std::vector<int> blockData;
    Mesh mesh{};
    bool dirty{false};
};


#endif //TOG_CHUNK_H