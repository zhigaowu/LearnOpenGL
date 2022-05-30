#include "opengl/core/Texture.h"

namespace opengl {
    namespace core {
        Texture::Texture(GLsizei element_size_)
            : element_size(element_size_)
            , id(new GLuint[element_size])
        {
            glGenTextures(element_size, id);
        }

        Texture::~Texture()
        {
            glDeleteTextures(element_size, id);
            delete[] id;
        }

        void Texture::Active(GLuint element_index, GLenum unit)
        {
            glActiveTexture(unit);
            glBindTexture(GL_TEXTURE_2D, id[element_index]);
        }

        void Texture::Active(GLuint element_index, GLenum unit) const
        {
            glActiveTexture(unit);
            glBindTexture(GL_TEXTURE_2D, id[element_index]);
        }

        void Texture::SetParameter(GLenum name, GLint value)
        {
            glTexParameteri(GL_TEXTURE_2D, name, value);
        }

        void Texture::Upload(const void* data, GLenum data_type, GLenum data_format, GLsizei width, GLsizei height, GLint internalformat, GLint level, GLint border)
        {
            glTexImage2D(GL_TEXTURE_2D, level, internalformat, width, height, border, data_format, data_type, data);
        }

        void Texture::Transfer(const void* data, GLsizei width, GLsizei height)
        {

        }

        void Texture::GenerateMipmap()
        {
            glGenerateMipmap(GL_TEXTURE_2D);
        }
    };
};

