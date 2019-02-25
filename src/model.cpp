#include "model.h"

#include <fstream>
#include <sstream>
#include <iterator> // istream_iterator
#include <exception>


size_t Model::sizeVert() { return m_vertexes.size(); }
size_t Model::sizeFace() { return m_faces.size(); }
Point3D Model::getVertex(size_t num) { return m_vertexes[num]; }

std::vector<std::string> split(const std::string& s, char delimiter)
{
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(s);
    while (std::getline(tokenStream, token, delimiter))
    {
        tokens.push_back(token);
    }
    return tokens;
}


void Model::readModel(std::string filename) {
    std::ifstream readFile(filename);
    if (readFile.fail())
        throw std::runtime_error("Could not open file");

    for (std::string line; std::getline(readFile, line);) {
        std::vector<std::string> results = ::split(line, ' ');
        if (results.size() && results[0] == "v") {
            Point3D p = {std::stof(results[1]),
                         std::stof(results[2]),
                         std::stof(results[3])};
            m_vertexes.push_back(p);
        }
        if (results.size() && results[0] == "f") {
            std::vector<std::string> f1 = ::split(results[1], '/');
            std::vector<std::string> f2 = ::split(results[2], '/');
            std::vector<std::string> f3 = ::split(results[3], '/');
            Face f = {std::stoi(f1[0]),
                      std::stoi(f2[0]),
                      std::stoi(f3[0])};
            m_faces.push_back(f);
        }
    }
}

std::vector<Segment2D> Model::getSegments(Projection p) {
    std::vector<Segment2D> segments;
    switch(p) {
    case x : {
        for (auto it = m_faces.begin(); it != m_faces.end(); ++it) {
            Point3D p1 = m_vertexes[static_cast<size_t>(it->f1-1)];
            Point3D p2 = m_vertexes[static_cast<size_t>(it->f2-1)];
            Point3D p3 = m_vertexes[static_cast<size_t>(it->f3-1)];
            Segment2D s1 = {{p1.y, p1.z}, {p2.y, p2.z}};
            Segment2D s2 = {{p2.y, p2.z}, {p3.y, p3.z}};
            Segment2D s3 = {{p3.y, p3.z}, {p1.y, p1.z}};
            segments.push_back(s1);
            segments.push_back(s2);
            segments.push_back(s3);
        }
        break;
    }
    case y : {
        for (auto it = m_faces.begin(); it != m_faces.end(); ++it) {
            Point3D p1 = m_vertexes[static_cast<size_t>(it->f1-1)];
            Point3D p2 = m_vertexes[static_cast<size_t>(it->f2-1)];
            Point3D p3 = m_vertexes[static_cast<size_t>(it->f3-1)];
            Segment2D s1 = {{p1.x, p1.z}, {p2.x, p2.z}};
            Segment2D s2 = {{p2.x, p2.z}, {p3.x, p3.z}};
            Segment2D s3 = {{p3.x, p3.z}, {p1.x, p1.z}};
            segments.push_back(s1);
            segments.push_back(s2);
            segments.push_back(s3);
        }
        break;
    }
    case z : {
        for (auto it = m_faces.begin(); it != m_faces.end(); ++it) {
            Point3D p1 = m_vertexes[static_cast<size_t>(it->f1-1)];
            Point3D p2 = m_vertexes[static_cast<size_t>(it->f2-1)];
            Point3D p3 = m_vertexes[static_cast<size_t>(it->f3-1)];
            Segment2D s1 = {{p1.x, p1.y}, {p2.x, p2.y}};
            Segment2D s2 = {{p2.x, p2.y}, {p3.x, p3.y}};
            Segment2D s3 = {{p3.x, p3.y}, {p1.x, p1.y}};
            segments.push_back(s1);
            segments.push_back(s2);
            segments.push_back(s3);
        }
    }
    }
    return segments;
}

std::vector<Triangle> Model::getTriangles(Projection p) {
    std::vector<Triangle> triangles;
    switch(p) {
    case x : {
        for (auto it = m_faces.begin(); it != m_faces.end(); ++it) {
            Point3D p1 = m_vertexes[static_cast<size_t>(it->f1-1)];
            Point3D p2 = m_vertexes[static_cast<size_t>(it->f2-1)];
            Point3D p3 = m_vertexes[static_cast<size_t>(it->f3-1)];
            triangles.push_back({{p1.y, p1.z}, {p2.y, p2.z}, {p3.y, p3.z}});
        }
        break;
    }
    case y : {
        for (auto it = m_faces.begin(); it != m_faces.end(); ++it) {
            Point3D p1 = m_vertexes[static_cast<size_t>(it->f1-1)];
            Point3D p2 = m_vertexes[static_cast<size_t>(it->f2-1)];
            Point3D p3 = m_vertexes[static_cast<size_t>(it->f3-1)];
            triangles.push_back({{p1.x, p1.z}, {p2.x, p2.z}, {p3.x, p3.z}});
        }
        break;
    }
    case z : {
        for (auto it = m_faces.begin(); it != m_faces.end(); ++it) {
            Point3D p1 = m_vertexes[static_cast<size_t>(it->f1-1)];
            Point3D p2 = m_vertexes[static_cast<size_t>(it->f2-1)];
            Point3D p3 = m_vertexes[static_cast<size_t>(it->f3-1)];
            triangles.push_back({{p1.x, p1.y}, {p2.x, p2.y}, {p3.x, p3.y}});
        }
    }
    }
    return triangles;
}
