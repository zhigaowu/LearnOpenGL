#ifndef _OPENGL_SCENE_CUBE_HEADER_H_
#define _OPENGL_SCENE_CUBE_HEADER_H_

#include "opengl/core/VertexArrays.h"

#include <glm/glm.hpp>

namespace opengl {
    namespace scene {
        class Cube
        {
        public:
            static const GLsizei VERTICES_ATTRIBUTE_COUNT = 3;
            static const core::VerticesAttribute VERTICES_ATTRIBUTE[VERTICES_ATTRIBUTE_COUNT];

            static const GLenum PRIMITIVE_SHAPE = GL_TRIANGLES;
            static const GLsizei PRIMITIVE_SHAPE_COUNT = 36;

            static const GLfloat VERTICES[PRIMITIVE_SHAPE_COUNT * 8];

        public:
            Cube(const glm::vec4& color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
            ~Cube();

            void MoveTo(const glm::vec3& position, float rotation_angle, const glm::vec3& rotation_axes);

            void Show(bool visible);

        public:
            glm::vec4 color;

        public:
            glm::vec3 position;
            glm::vec4 rotation; // (3: rotation axes, 1: rotation angle)

        public:
            glm::mat4 model;

        public:
            bool visible;
        };
    }
};

#endif

