#include "chunk.h"

Chunk::Chunk() {
    blockData = std::vector<int>(std::size_t{CHUNK_MAX_X*CHUNK_MAX_Z*CHUNK_MAX_Y}, int{0});
}
