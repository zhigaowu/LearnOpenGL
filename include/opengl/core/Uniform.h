#ifndef _OPENGL_CORE_UNIFORM_HEADER_H_
#define _OPENGL_CORE_UNIFORM_HEADER_H_

#include "opengl/Implement.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>

namespace opengl {
    namespace core {
#define Uniform_Parameter1(TypeName) TypeName v0
#define Uniform_Value1() v0
#define Uniform_Parameter2(TypeName) Uniform_Parameter1(TypeName), TypeName v1
#define Uniform_Value2() Uniform_Value1(), v1
#define Uniform_Parameter3(TypeName) Uniform_Parameter2(TypeName), TypeName v2
#define Uniform_Value3() Uniform_Value2(), v2
#define Uniform_Parameter4(TypeName) Uniform_Parameter3(TypeName), TypeName v3
#define Uniform_Value4() Uniform_Value3(), v3

#define Declare_Uniform_Scalar_Template(TypeName, n, t) template<typename TypeName>\
    inline void glUniform##n(GLint location, Uniform_Parameter##n(TypeName))\
    {\
        glUniform##n##t(location, Uniform_Value##n());\
    }

#define Declare_Uniform_Scalar_Specialization(TypeName, n, t) template<>\
    inline void glUniform##n<TypeName>(GLint location, Uniform_Parameter##n(TypeName))\
    {\
        glUniform##n##t(location, Uniform_Value##n());\
    }

        Declare_Uniform_Scalar_Template(TypeName, 1, f);
        Declare_Uniform_Scalar_Specialization(GLdouble, 1, d);
        Declare_Uniform_Scalar_Specialization(GLint, 1, i);
        Declare_Uniform_Scalar_Specialization(GLuint, 1, ui);

        Declare_Uniform_Scalar_Template(TypeName, 2, f);
        Declare_Uniform_Scalar_Specialization(GLdouble, 2, d);
        Declare_Uniform_Scalar_Specialization(GLint, 2, i);
        Declare_Uniform_Scalar_Specialization(GLuint, 2, ui);

        Declare_Uniform_Scalar_Template(TypeName, 3, f);
        Declare_Uniform_Scalar_Specialization(GLdouble, 3, d);
        Declare_Uniform_Scalar_Specialization(GLint, 3, i);
        Declare_Uniform_Scalar_Specialization(GLuint, 3, ui);

        Declare_Uniform_Scalar_Template(TypeName, 4, f);
        Declare_Uniform_Scalar_Specialization(GLdouble, 4, d);
        Declare_Uniform_Scalar_Specialization(GLint, 4, i);
        Declare_Uniform_Scalar_Specialization(GLuint, 4, ui);

#define Declare_Uniform_Vector_Template(TypeName, n, t) template<typename TypeName>\
    inline void glUniform##n##v(GLint location, GLsizei count, const TypeName* value)\
    {\
        glUniform##n##t##v(location, count, value);\
    }

#define Declare_Uniform_Vector_Specialization(TypeName, n, t) template<>\
    inline void glUniform##n##v<TypeName>(GLint location, GLsizei count, const TypeName* value)\
    {\
        glUniform##n##t##v(location, count, value);\
    }

        Declare_Uniform_Vector_Template(TypeName, 1, f);
        Declare_Uniform_Vector_Specialization(GLint, 1, i);

        Declare_Uniform_Vector_Template(TypeName, 2, f);
        Declare_Uniform_Vector_Specialization(GLint, 2, i);

        Declare_Uniform_Vector_Template(TypeName, 3, f);
        Declare_Uniform_Vector_Specialization(GLint, 3, i);

        Declare_Uniform_Vector_Template(TypeName, 4, f);
        Declare_Uniform_Vector_Specialization(GLint, 4, i);

        template<GLint dim, typename TypeName>
        struct glUniformVector
        {
            glUniformVector(GLint location, GLsizei count, const TypeName* value)
            {
                glUniform4v(location, count, value);
            }
        };

        template<typename TypeName>
        struct glUniformVector<2, TypeName>
        {
            glUniformVector(GLint location, GLsizei count, const TypeName* value)
            {
                glUniform2v(location, count, value);
            }
        };

        template<typename TypeName>
        struct glUniformVector<3, TypeName>
        {
            glUniformVector(GLint location, GLsizei count, const TypeName* value)
            {
                glUniform3v(location, count, value);
            }
        };

        template<typename TypeName>
        struct glUniformVector<1, TypeName>
        {
            glUniformVector(GLint location, GLsizei count, const TypeName* value)
            {
                glUniform1v(location, count, value);
            }
        };

#define Declare_Uniform_Matrix_Template(TypeName, n, t) template<typename TypeName>\
    inline void glUniformMatrix##n##v(GLint location, GLsizei count, const TypeName* value, GLboolean transpose)\
    {\
        glUniformMatrix##n##t##v(location, count, transpose, value);\
    }

#define Declare_Uniform_Matrix_Specialization(TypeName, n, t) template<>\
    inline void glUniformMatrix##n##v<TypeName>(GLint location, GLsizei count, const TypeName* value, GLboolean transpose)\
    {\
        glUniformMatrix##n##t##v(location, count, transpose, value);\
    }

        Declare_Uniform_Matrix_Template(TypeName, 2, f);
        Declare_Uniform_Matrix_Template(TypeName, 3, f);
        Declare_Uniform_Matrix_Template(TypeName, 4, f);

        template<GLint dim, typename TypeName>
        struct glUniformMatrix
        {
            glUniformMatrix(GLint location, GLsizei count, const TypeName* value, GLboolean transpose)
            {
                glUniformMatrix4v(location, count, value, transpose);
            }
        };

        template<typename TypeName>
        struct glUniformMatrix<2, TypeName>
        {
            glUniformMatrix(GLint location, GLsizei count, const TypeName* value, GLboolean transpose)
            {
                glUniformMatrix2v(location, count, value, transpose);
            }
        };

        template<typename TypeName>
        struct glUniformMatrix<3, TypeName>
        {
            glUniformMatrix(GLint location, GLsizei count, const TypeName* value, GLboolean transpose)
            {
                glUniformMatrix3v(location, count, value, transpose);
            }
        };

        struct Uniform
        {
            template<typename ValueType>
            static void Set(GLint location, const std::vector<ValueType>& value)
            {
                switch (value.size())
                {
                case 1:
                {
                    glUniform1(location, value[0]);
                    break;
                }
                case 2:
                {
                    glUniform2(location, value[0], value[1]);
                    break;
                }
                case 3:
                {
                    glUniform3(location, value[0], value[1], value[2]);
                    break;
                }
                case 4:
                {
                    glUniform4(location, value[0], value[1], value[2], value[3]);
                    break;
                }
                default:
                    break;
                }
            }

            template<GLint dim, typename ValueType>
            static void Set(GLint location, GLsizei count, const ValueType* value)
            {
                glUniformVector<dim, ValueType>(location, count, value);
            }

            template<GLint dim, typename ValueType>
            static void Set(GLint location, GLsizei count, const ValueType* value, GLboolean transpose)
            {
                glUniformMatrix<dim, ValueType>(location, count, value, transpose);
            }
        };
    };
};

#endif

