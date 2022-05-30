#include "opengl/core/Shader.h"

namespace opengl {
    namespace core {
        Shader::Shader(GLenum shader_type)
            : id(glCreateShader(shader_type))
        {
        }

        Shader::~Shader()
        {
            glDeleteShader(id);
        }

        bool Shader::Compile(const char* shader_code, char* error_string, int error_string_size)
        {
            glShaderSource(id, 1, &shader_code, nullptr);
            glCompileShader(id);

            // check compile errors
            GLint res = 0; glGetShaderiv(id, GL_COMPILE_STATUS, &res);
            if (0 == res)
            {
                glGetShaderInfoLog(id, error_string_size, nullptr, error_string);
            }
            return 0 != res;
        }
    };
};

