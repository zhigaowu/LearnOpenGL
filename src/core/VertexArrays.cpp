#include "opengl/core/VertexArrays.h"

namespace opengl {
    namespace core {
        VertexArrays::VertexArrays(GLsizei element_size_)
            : element_size(element_size_)
            , id(new GLuint[element_size])
        {
            glGenVertexArrays(element_size, id);
        }

        VertexArrays::~VertexArrays()
        {
            glDeleteVertexArrays(element_size, id);
            delete[] id;
        }

        void VertexArrays::Bind(GLuint element_index)
        {
            glBindVertexArray(id[element_index]);
        }

        void VertexArrays::Unbind()
        {
            glBindVertexArray(0);
        }

        void VertexArrays::SetAttribute(GLuint index, GLint data_element_count, GLenum data_element_type, GLboolean data_normalized, GLsizei data_stride, const void* data_offset)
        {
            glVertexAttribPointer(index, data_element_count, data_element_type, data_normalized, data_stride, data_offset);
            glEnableVertexAttribArray(index);
        }
    };
};

