#ifndef _OPENGL_CORE_VERTEX_ARRAYS_HEADER_H_
#define _OPENGL_CORE_VERTEX_ARRAYS_HEADER_H_

#include "opengl/Implement.h"

namespace opengl {
    namespace core {
        struct VerticesAttribute
        {
            GLuint index = 0;
            GLint element_count = 0;
            GLenum element_type = GL_FLOAT;
            GLboolean normalized = GL_FALSE;
        };

        class VertexArrays
        {
        public:
            explicit VertexArrays(GLsizei element_size = 1);
            ~VertexArrays();

            void Bind(GLuint element_index = 0);
            void Unbind();

            void SetAttribute(GLuint index, GLint data_element_count, GLenum data_element_type, GLboolean data_normalized, GLsizei data_stride, const void* data_offset);

        public:
            GLsizei element_size;
            GLuint* id;

        private:
            VertexArrays(const VertexArrays&) = delete;
            VertexArrays& operator=(const VertexArrays&) = delete;
            VertexArrays(const VertexArrays&&) = delete;
            VertexArrays& operator=(const VertexArrays&&) = delete;
        };
    };
};

#endif

