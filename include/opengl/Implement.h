#ifndef _OPENGL_IMPLEMENT_HEADER_H_
#define _OPENGL_IMPLEMENT_HEADER_H_

#include "glad/glad.h"

namespace opengl {

    template<typename ValueType>
    inline void glGetTypev(GLenum key, ValueType& value)
    {
        glGetIntegerv(key, &value);
    }

    template<>
    inline void glGetTypev<GLfloat>(GLenum key, GLfloat& value)
    {
        glGetFloatv(key, &value);
    }

    template<>
    inline void glGetTypev<GLdouble>(GLenum key, GLdouble& value)
    {
        glGetDoublev(key, &value);
    }

    template<>
    inline void glGetTypev<GLboolean>(GLenum key, GLboolean& value)
    {
        glGetBooleanv(key, &value);
    }

    template<>
    inline void glGetTypev<const GLubyte*>(GLenum key, const GLubyte*& value)
    {
        value = glGetString(key);
    }

    template<GLenum KeyValue, typename ValueType>
    struct Property
    {
        ValueType value;

        Property()
        {
            glGetTypev(KeyValue, value);
        }

        ValueType operator()()
        {
            return value;
        }
    };

    inline GLsizei SizeOfGL(GLenum gltype)
    {
        GLsizei size = 0;
        switch (gltype)
        {
        case GL_INT:
        case GL_UNSIGNED_INT:
        {
            size = sizeof(GLint);
            break;
        }
        case GL_SHORT:
        case GL_UNSIGNED_SHORT:
        {
            size = sizeof(GLshort);
            break;
        }
        case GL_BYTE:
        case GL_UNSIGNED_BYTE:
        {
            size = sizeof(GLbyte);
            break;
        }
        default:
        {
            size = sizeof(GLfloat);
        }
        }
        return size;
    }
};

#endif

