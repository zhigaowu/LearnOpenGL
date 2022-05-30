#ifndef _OPENGL_CORE_BUFFERS_HEADER_H_
#define _OPENGL_CORE_BUFFERS_HEADER_H_

#include "opengl/Implement.h"

namespace opengl {
    namespace core {
        template<GLenum Element_Type>
        class Buffers
        {
        public:
            explicit Buffers(GLsizei element_size = 1);
            ~Buffers();

            void Bind(GLuint element_index = 0);
            void Unbind();

            void Upload(const void *data, GLsizeiptr size, GLenum usage);

        public:
            GLsizei element_size;
            GLuint* id;

        private:
            Buffers(const Buffers&) = delete;
            Buffers& operator=(const Buffers&) = delete;
            Buffers(const Buffers&&) = delete;
            Buffers& operator=(const Buffers&&) = delete;
        };
    };
};

#endif

