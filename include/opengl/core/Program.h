#ifndef _OPENGL_CORE_PROGRAM_HEADER_H_
#define _OPENGL_CORE_PROGRAM_HEADER_H_

#include "opengl/core/Shader.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace opengl {
    namespace core {
        class Program
        {
        public:
            explicit Program();
            ~Program();

            void Attach(const Shader& shader);

            bool Link(GLchar* error_string, GLsizei error_string_size);

            void Use();

            GLint GetUniformLocation(const GLchar* name);

        public:
            GLuint id;

        private:
            Program(const Program&) = delete;
            Program& operator=(const Program&) = delete;
            Program(const Program&&) = delete;
            Program& operator=(const Program&&) = delete;
        };
    };
};

#endif

