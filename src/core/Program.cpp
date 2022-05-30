#include "opengl/core/Program.h"

namespace opengl {
    namespace core {
        Program::Program()
            : id(glCreateProgram())
        {
        }

        Program::~Program()
        {
            glDeleteProgram(id);
        }

        void Program::Attach(const Shader& shader)
        {
            glAttachShader(id, shader.id);
        }

        bool Program::Link(GLchar* error_string, GLsizei error_string_size)
        {
            glLinkProgram(id);

            // check for errors
            GLint res = 0; glGetProgramiv(id, GL_LINK_STATUS, &res);
            if (0 == res)
            {
                glGetProgramInfoLog(id, error_string_size, nullptr, error_string);
            }
            return 0 != res;
        }

        void Program::Use()
        {
            glUseProgram(id);
        }

        GLint Program::GetUniformLocation(const GLchar* name)
        {
            return glGetUniformLocation(id, name);
        }
    };
};

