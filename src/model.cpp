#include "model.h"

#include <fstream>
#include <sstream>
#include <iterator> // istream_iterator
#include <exception>


size_t Model::sizeVert() { return m_vertexes.size(); }
size_t Model::sizeFace() { return m_faces.size(); }
Vec3f Model::getVertex(size_t num) { return m_vertexes[num]; }

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
            Vec3f p = {std::stof(results[1]),
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


Face Model::face(size_t i) {
    return m_faces[i];
}
