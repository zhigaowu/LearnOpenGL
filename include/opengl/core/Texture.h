#ifndef _OPENGL_CORE_TEXTURE_HEADER_H_
#define _OPENGL_CORE_TEXTURE_HEADER_H_

#include "opengl/Implement.h"

namespace opengl {
    namespace core {
        class Texture
        {
        public:
            explicit Texture(GLsizei element_size = 1);
            ~Texture();

            void Active(GLuint element_index = 0, GLenum unit = GL_TEXTURE0);
            void Active(GLuint element_index = 0, GLenum unit = GL_TEXTURE0) const;

            void SetParameter(GLenum name, GLint value);

            void Upload(const void* data, GLenum data_type, GLenum data_format, GLsizei width, GLsizei height, GLint internalformat, GLint level = 0, GLint border = 0);

            void Transfer(const void* data, GLsizei width, GLsizei height);

            void GenerateMipmap();

        public:
            GLsizei element_size;
            GLuint* id;

        private:
            Texture(const Texture&) = delete;
            Texture& operator=(const Texture&) = delete;
            Texture(const Texture&&) = delete;
            Texture& operator=(const Texture&&) = delete;
        };
    }
};

#endif

