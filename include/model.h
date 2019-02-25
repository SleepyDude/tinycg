#ifndef MODEL_H
#define MODEL_H

#include <vector>
#include <string>

typedef struct Point3D {
    float x;
    float y;
    float z;
} Point3D;

typedef struct Point2D {
    float x;
    float y;
} Point2D;

typedef struct Segment2D {
    Point2D p1;
    Point2D p2;
} Segment2D;

typedef struct Triangle {
    Point2D p1;
    Point2D p2;
    Point2D p3;
} Triangle;

typedef struct Face {
    int f1;
    int f2;
    int f3;
} Face;

enum Projection { x, y, z };

class Model {
public:
    Model() = default;
    size_t sizeVert();
    size_t sizeFace();
    Point3D getVertex(size_t num);

    void readModel(std::string filename);
    std::vector<Segment2D> getSegments(Projection p);
    std::vector<Triangle> getTriangles(Projection p);

private:
    std::vector<Point3D> m_vertexes;
    std::vector<Face> m_faces;
};


#endif // MODEL_H
