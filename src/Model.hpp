#pragma once

#include "../include/glad/glad.h"
#include <glm/glm.hpp>
#include <string>
#include <vector>
#include "Buffer.hpp"
#include "Shader.hpp"

struct Mesh
{
    std::string name;
    std::string materialName;

    std::vector<GLuint> indices;
    std::vector<glm::vec4> colors;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec2> textureCoords;
};

struct VertexGroup
{
    int v = -1;
    int t = -1;
    int n = -1;

    bool operator==(const VertexGroup& other) const
    {
        return (v == other.v && t == other.t && n == other.n);
    }
};

typedef std::vector<VertexGroup> Face; //triangles

class HashFunction
{   
public:
    //overload constructor
    size_t operator()(const VertexGroup& v) const
    {
        return v.v + v.t + v.n;
    }
};



class Model
{

public:
    
    Model();

    bool Load(const std::string& filename);
    
    void Update();
    
    void Render(const Shader& shader);
    

private:

    void FillBuffers();
    void SortVertexData(Mesh& newMesh, const Mesh& oldMesh, const std::vector<Face>& faces);

    std::vector<Mesh> m_meshes; //group of raw data
    std::vector<Buffer> m_buffers; //Sincronous (for every mesh group have a Buffer)

    glm::mat4 m_model;
    glm::mat3 m_normal;

    glm::vec3 m_position;
    glm::vec3 m_rotation;

    float m_shininess;
    glm::vec3 m_ambient;
    glm::vec3 m_diffuse;
    glm::vec3 m_specular;

};



