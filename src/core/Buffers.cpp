#include "opengl/core/Buffers.h"

namespace opengl {
    namespace core {
        template<GLenum Element_Type>
        struct UnBindOperator
        {
            void operator()()
            {
                glBindBuffer(Element_Type, 0);
            }
        };

        template<>
        struct UnBindOperator<GL_ELEMENT_ARRAY_BUFFER>
        {
            void operator()()
            {}
        };

        template<GLenum Element_Type>
        Buffers<Element_Type>::Buffers(GLsizei element_size_)
            : element_size(element_size_)
            , id(new GLuint[element_size])
        {
            glGenBuffers(element_size, id);
        }

        template<GLenum Element_Type>
        Buffers<Element_Type>::~Buffers()
        {
            glDeleteBuffers(element_size, id);
            delete[] id;
        }

        template<GLenum Element_Type>
        void Buffers<Element_Type>::Bind(GLuint element_index)
        {
            glBindBuffer(Element_Type, id[element_index]);
        }

        template<GLenum Element_Type>
        void Buffers<Element_Type>::Unbind()
        {
            UnBindOperator<Element_Type> unbind;
            unbind();
        }

        template<GLenum Element_Type>
        void Buffers<Element_Type>::Upload(const void *data, GLsizeiptr size, GLenum usage)
        {
            glBufferData(Element_Type, size, data, usage);
        }

        template class Buffers<GL_ELEMENT_ARRAY_BUFFER>;
        template class Buffers<GL_ARRAY_BUFFER>;
    };
};

