#ifndef MODEL_H
#define MODEL_H

#include <vector>
#include <array>
#include <string>
#include <math.h>

typedef struct Point3D {
    float x;
    float y;
    float z;
    Point3D operator ^(Point3D other) {
        float _x = y * other.z - z * other.y;
        float _y = - x * other.z + z * other.x;
        float _z = x * other.y - y * other.x;
        return {_x, _y, _z};
    }
    Point3D operator -(Point3D other) {
        return {x - other.x, y - other.y, z - other.z};
    }
    void normalize() {
        float l = sqrt(x*x + y*y + z*z);
        x /= l;
        y /= l;
        z /= l;
    }
    float operator *(Point3D other) {
        return x * other.x + y * other.y + z * other.z;
    }
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
    std::vector<int> face(size_t i);

private:
    std::vector<Point3D> m_vertexes;
    std::vector<Face> m_faces;
};


#endif // MODEL_H
