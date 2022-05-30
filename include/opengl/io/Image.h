#ifndef _OPENGL_IO_IMAGE_HEADER_H_
#define _OPENGL_IO_IMAGE_HEADER_H_

#include "opengl/Implement.h"

namespace opengl {
    namespace io {
        class Image
        {
        public:
            explicit Image(const GLchar* file);
            ~Image();

        public:
            void* data;
            GLenum format;
            GLsizei width;
            GLsizei height;
            GLint channels;

        private:
            Image() = delete;
            Image(const Image&) = delete;
            Image& operator=(const Image&) = delete;
            Image(const Image&&) = delete;
            Image& operator=(const Image&&) = delete;
        };
    };
};

#endif

