#ifndef _OPENGL_CORE_SHADER_HEADER_H_
#define _OPENGL_CORE_SHADER_HEADER_H_

#include "opengl/Implement.h"

namespace opengl {
    namespace core {
        class Shader
        {
        public:
            explicit Shader(GLenum shader_type);
            ~Shader();

            bool Compile(const char* shader_code, char* error_string, int error_string_size);

        public:
            GLuint id;

        private:
            Shader() = delete;
            Shader(const Shader&) = delete;
            Shader& operator=(const Shader&) = delete;
            Shader(const Shader&&) = delete;
            Shader& operator=(const Shader&&) = delete;
        };
    };
};

#endif

