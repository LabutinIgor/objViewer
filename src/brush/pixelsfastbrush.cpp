#include "pixelsfastbrush.h"

PixelsFastBrush::PixelsFastBrush(const ObjectModel &objectModel, TextureStorage &textureStorage)
        : AbstractBrush(objectModel, textureStorage), pixelsUvOfTriangle_(objectModel.getFacesNumber()),
          vertexFromUv_(textureStorage.getWidth(), textureStorage.getHeight()) {
    size_t w = textureStorage.getWidth();
    size_t h = textureStorage.getHeight();

    for (IdType faceId = 0; faceId < objectModel.getFacesNumber(); ++faceId) {
        Face face(objectModel, faceId);
        int minX = (int) (fmax(0, BrushUtils::getMinUvX(face) * w));
        int maxX = (int) (fmin(BrushUtils::getMaxUvX(face) * w, w - 1));

        for (int x = minX; x <= maxX; ++x) {
            float xUv = (float) (x / (1.0 * w));
            int minY = (int) fmax(0, BrushUtils::getMinY(face, xUv) * h);
            int maxY = (int) fmin(h - 1, BrushUtils::getMaxY(face, xUv) * h);

            for (int y = minY; y <= maxY; ++y) {
                float yUv = (float) (y / (1.0 * h));
                glm::vec3 point = Geometry::getPointFromUVCoordinates(face.getUvs(), face.getPositions(),
                                                                      glm::vec2(xUv, yUv));
                vertexFromUv_.setValue(x, y, point);
                pixelsUvOfTriangle_[faceId].push_back(glm::u32vec2(x, y));
            }
        }
    }
}

BrushStroke PixelsFastBrush::paint(const glm::i32vec2 &point, const glm::mat4x4 &matrixModelView,
                                   const glm::mat4x4 &matrixProjection, const IdsStorage &idsStorage) {
    BrushStroke diff;
    auto ids = calculateIntersectedTrianglesIds(matrixModelView, point, idsStorage);
    for (IdType id : ids) {
        paintTriangle(id, matrixModelView, matrixProjection, point, idsStorage, diff);
    }
    return diff;
}

void PixelsFastBrush::paintTriangle(IdType id, const glm::mat4x4 &matrixModelView, const glm::mat4x4 &matrixProjection,
                                    const glm::i32vec2 &brushCenter, const IdsStorage &idsStorage, BrushStroke &diff) {
    for (glm::u32vec2 pixel : pixelsUvOfTriangle_[id]) {
        glm::vec3 point(matrixModelView * glm::vec4(vertexFromUv_.getValue(pixel), 1.0));

        glm::i32vec2 screenPoint(Geometry::toScreenCoordinates(point, matrixProjection, idsStorage.getSize()));

        if (BrushUtils::isInside(screenPoint, idsStorage.getSize())
            && isInsideBrush(screenPoint, brushCenter)
            && isVisible(screenPoint, id, idsStorage)) {
            diff.add(ColorChange(pixel, textureStorage_.getValue(pixel), getColor()));
            textureStorage_.setValue(pixel, getColor());
        }
    }
}

bool
PixelsFastBrush::isVisible(const glm::vec2 &screenPoint, IdType faceIdFromStorage, const IdsStorage &idsStorage) const {
    return BrushUtils::hasNeighbourWithId(idsStorage, screenPoint, faceIdFromStorage)
           || objectModel_.areAdjacentFaces(faceIdFromStorage, idsStorage.getValue(screenPoint));
}

std::unordered_set<IdType> PixelsFastBrush::calculateIntersectedTrianglesIds(const glm::mat4x4 &matrixModelView,
                                                                             const glm::i32vec2 &brushCenter,
                                                                             const IdsStorage &idsStorage) const {
    std::unordered_set<IdType> ids;
    for (int dx = (int) -getRadius(); dx <= getRadius(); ++dx) {
        for (int dy = (int) -getRadius(); dy <= getRadius(); ++dy) {
            if (dx * dx + dy * dy <= getRadius() * getRadius()) {
                glm::i32vec2 point(brushCenter.x + dx, brushCenter.y + dy);
                if (hasVisibleTriangleAtPoint(point, matrixModelView, idsStorage)) {
                    ids.insert(idsStorage.getValue(point));
                }
            }
        }
    }
    return ids;
}

bool PixelsFastBrush::hasVisibleTriangleAtPoint(const glm::vec2 &point, const glm::mat4x4 &matrixModelView,
                                                const IdsStorage &idsStorage) const {
    if (BrushUtils::isInside(point, idsStorage.getSize())) {
        size_t id = idsStorage.getValue(point);
        return (id < objectModel_.getFacesNumber()
                && Geometry::calculateFaceAngleCos(Face(objectModel_, id), matrixModelView) < MIN_ANGLE_COS);
    }
    return false;
}
