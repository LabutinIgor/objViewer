#ifndef PIXELSFASTBRUSH_H
#define PIXELSFASTBRUSH_H

#include <vector>
#include <unordered_set>

#include "geometry.h"
#include "abstractbrush.h"
#include "brushutils.h"

class PixelsFastBrush : public AbstractBrush {
public:
    PixelsFastBrush(const ObjectModel& objectModel, TextureStorage& textureStorage);
    virtual BrushStroke paint(const glm::i32vec2& point, const glm::mat4x4& matrixModelView,
                              const glm::mat4x4& matrixProjection, const IdsStorage& idsStorage);

private:
    std::vector<std::vector<glm::u32vec2>> pixelsUvOfTriangle_;
    Matrix<glm::vec3> vertexFromUv_;
    const double_t MIN_ANGLE_COS = cos(M_PI / 2 + 10 * 2 * M_PI / 360.0);

    std::unordered_set<IdType> calculateIntersectedTrianglesIds(const glm::mat4x4& matrixModelView,
                                                                const glm::i32vec2& brushCenter,
                                                                const IdsStorage& idsStorage) const;
    void paintTriangle(IdType id, const glm::mat4x4& matrixModelView, const glm::mat4x4& matrixProjection,
                       const glm::i32vec2& brushCenter, const IdsStorage& idsStorage, BrushStroke &diff);
    bool hasVisibleTriangleAtPoint(const glm::vec2& point, const glm::mat4x4& matrixModelView,
                                   const IdsStorage& idsStorage) const;
    bool isVisible(const glm::vec2& screenPoint, IdType faceIdFromStorage, const IdsStorage& idsStorage) const;
};

#endif // PIXELSFASTBRUSH_H
