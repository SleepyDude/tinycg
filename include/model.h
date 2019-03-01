#ifndef MODEL_H
#define MODEL_H

#include <vector>
#include <array>
#include <string>
#include "geometry.hpp"

typedef struct Face {
    std::array<int, 3> v;
    std::array<int, 3> t;
} Face;

class Model {
public:
    Model() = default;
    size_t sizeVert();
    size_t sizeFace();
    Vec3f getVertex(size_t num);
    Vec2f getTexVert(size_t num);
    void readModel(std::string filename);
    Face face(size_t i);

private:
    std::vector<Vec3f> m_vertexes;
    std::vector<Vec2f> m_textures;
    std::vector<Face> m_faces;
};


#endif // MODEL_H
