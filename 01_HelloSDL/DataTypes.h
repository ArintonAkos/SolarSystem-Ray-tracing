#include <string>
#include "glm/glm.hpp"

namespace DataTypes {
    
    struct Vertex {
        glm::vec3 position;
        glm::vec3 normal;
        glm::vec2 texCoords;
    };

    struct Texture {
        uint32_t id;
        std::string type;
        std::string path;
    };
}