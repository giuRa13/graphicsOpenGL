#include "Model.hpp"
#include "Utility.hpp"
#include <fstream>
#include <iostream>
#include <unordered_map>



Model::Model()
{
    m_meshes.reserve(10);
    m_buffers.reserve(10);
}


bool Model::Load(const std::string &filename)
{
    std::fstream file(filename, std::ios_base::in); // (read only)

    if(!file)
    {
        std::cout <<"Error loading model file" <<std::endl;
        return false;
    }

    Mesh rawMesh;
    std::string lastMaterialName;

    std::string line;
    std::string lastName;
    std::vector<Face> faces;

    std::vector<std::string> subStrings;
    subStrings.reserve(10);

    while(!file.eof())
    {
        std::getline(file, line);
        subStrings.clear();
        
        if(!line.empty() && line[0] != '#')
        {
            Utility::ParseString(line, subStrings, ' ');
           
            //Vertex data
            if(subStrings[0] == "v")
            {
                rawMesh.vertices.push_back(glm::vec3(std::stof(subStrings[1]), //stof() = convert to float
                                                     std::stof(subStrings[2]),
                                                     std::stof(subStrings[3])));
                continue;
            }

            //Normal data
            if(subStrings[0] == "vn")
            {
                rawMesh.normals.push_back(glm::vec3(std::stof(subStrings[1]), //stof() = convert to float
                                                     std::stof(subStrings[2]),
                                                     std::stof(subStrings[3])));
                continue;
            }
            
            //Texture coordinate
            if(subStrings[0] == "vt")
            {
                rawMesh.textureCoords.push_back(glm::vec2(std::stof(subStrings[1]), //stof() = convert to float
                                                     std::stof(subStrings[2])));
                continue;
            }            
            
            //Faces
            if(subStrings[0] == "f")
            {
                Face face;
                std::vector<std::string> numbers;
                numbers.reserve(10);

                for(int i = 1; i <= 3; i++)
                {
                    numbers.clear();
                    VertexGroup vertexGroup;
                    Utility::ParseString(subStrings[i], numbers, '/');

                    vertexGroup.v = std::stoi(numbers[0]) - 1;
                    vertexGroup.t = std::stoi(numbers[1]) - 1;
                    vertexGroup.n = std::stoi(numbers[2]) - 1;
                
                    face.push_back(vertexGroup);
                }
                faces.push_back(face);
                continue;
            }

            //Material group
            if(subStrings[0] == "usemtl1")//(use the foolowing material for the following faces)
            {
                lastMaterialName = subStrings[1];
                continue;
            }

            //Material file
            if (subStrings[0] == "mtllib")
            {
                //load material file
                continue;
            }

            //Group data
            if(subStrings[0] == "g" || subStrings[0] == "o")
            {
                if(!faces.empty())
                {
                    Mesh mesh;
                    mesh.name = lastName;
                    mesh.materialName = lastMaterialName;

                    SortVertexData(mesh, rawMesh, faces);
                    
                    m_meshes.push_back(mesh);
                }
                lastName = subStrings[1];
                faces.clear();
                continue;
            }
        }
    }

    file.close();
   
    if(!faces.empty())
    {
        Mesh mesh;
        mesh.name = lastName;
        mesh.materialName = lastMaterialName;

        SortVertexData(mesh, rawMesh, faces);
        m_meshes.push_back(mesh);
    }

    return true;
}


void Model::Update()
{

}

void Model::Render(const Shader &shader)
{

}

// build EBO
void Model::SortVertexData(Mesh& newMesh, const Mesh& oldMesh, const std::vector<Face>& faces )
{
    GLuint count = 0;
    std::unordered_map<VertexGroup, GLuint, HashFunction> map; //key, value, hoe to insert
                                                               
    for (const auto& face : faces)
    {
        for(auto i=0; i<3; i++)
        {
            auto it = map.find(face[i]);

            if(it == map.end())
            {
                newMesh.vertices.push_back(oldMesh.vertices[face[i].v]);
                newMesh.textureCoords.push_back(oldMesh.textureCoords[face[i].t]);
                newMesh.normals.push_back(oldMesh.normals[face[i].n]);
                newMesh.indices.push_back(count);

                map[face[i]] = count;
                count++;
            }
            else 
            {
                newMesh.indices.push_back(it->second);
            }
        }
    }
}



