#ifndef IDSSTORAGE_H
#define IDSSTORAGE_H

#include <cstdint>
#include <glm.hpp>

typedef uint32_t IdType;

class IdsStorage {
public:
    IdsStorage(uint32_t width, uint32_t height, IdType* ids);

    uint32_t getWidth();
    uint32_t getHeight();
    IdType getId(uint32_t row, uint32_t col);
    IdType getId(glm::i32vec2 point);
    bool hasNeighbourWithId(glm::i32vec2 point, uint32_t id);

private:
    uint32_t width;
    uint32_t height;
    IdType* ids;
};

#endif // IDSSTORAGE_H
