#ifndef _OPENGL_RENDERER_COLOR_RENDERER_HEADER_H_
#define _OPENGL_RENDERER_COLOR_RENDERER_HEADER_H_

#include "opengl/core/VertexArrays.h"
#include "opengl/core/Buffers.h"

#include "opengl/core/Program.h"

#include "opengl/material/Material.h"

#include "opengl/scene/Light.h"

#include <glm/glm.hpp>

namespace opengl {
    namespace renderer {
        template<typename LightType>
        class ColorRenderer
        {
            using GeometryType = typename LightType::DisplayGeometryType;

        public:
            ColorRenderer() 
                : _vao(), _vbo()
                , _program()
                , _uniform_model(-1), _uniform_view(-1), _uniform_projection(-1)
                , _uniform_light_position(-1), _uniform_light_color(-1), _uniform_light_direction(-1)
                , _uniform_object_color(-1)
                , _uniform_camera_position(-1)
                , _uniform_object_material()
                , _uniform_light_parameter()
            {
            }

            ~ColorRenderer()
            {
            }

            bool Create(GLchar* error_string, GLsizei error_string_size)
            {
#pragma warning(disable: 4312)
                if (-1 == _uniform_object_color)
                {
                    _vao.Bind();
                    _vbo.Bind();

                    _vbo.Upload(GeometryType::VERTICES, sizeof(GeometryType::VERTICES), GL_STATIC_DRAW);

                    for (GLsizei ai = 0, offset = 0; ai < GeometryType::VERTICES_ATTRIBUTE_COUNT; ++ai)
                    {
                        const core::VerticesAttribute& attribute = GeometryType::VERTICES_ATTRIBUTE[ai];
                        _vao.SetAttribute(attribute.index, attribute.element_count, attribute.element_type, attribute.normalized, static_cast<GLsizei>(sizeof(GeometryType::VERTICES) / GeometryType::PRIMITIVE_SHAPE_COUNT), (void*)(offset));

                        offset += attribute.element_count * SizeOfGL(attribute.element_type);
                    }

                    _vbo.Unbind();
                    _vao.Unbind();

                    // create render shader with light
                    do
                    {
                        opengl::core::Shader vshader(GL_VERTEX_SHADER);
                        if (!vshader.Compile("#version 330 core                                      \n"
                            "layout (location = 0) in vec3 vec3_position;                            \n"
                            "layout (location = 1) in vec3 vec3_normal;                              \n"
                            "                                                                        \n"
                            "uniform mat4 model;                                                     \n"
                            "uniform mat4 view;                                                      \n"
                            "uniform mat4 projection;                                                \n"
                            "                                                                        \n"
                            "out vec3 vec3_fragment_position;                                        \n"
                            "out vec3 vec3_uniform_normal;                                           \n"
                            "                                                                        \n"
                            "void main()                                                             \n"
                            "{                                                                       \n"
                            "   vec3_fragment_position = vec3(model * vec4(vec3_position, 1.0));     \n"
                            "	gl_Position = projection * view * vec4(vec3_fragment_position, 1.0); \n"
                            "   vec3_uniform_normal = mat3(transpose(inverse(model))) * vec3_normal; \n"
                            "} \n", error_string, error_string_size))
                        {
                            break;
                        }

                        opengl::core::Shader fshader(GL_FRAGMENT_SHADER);
                        if (!fshader.Compile("#version 330 core                  \n"
                            "struct Material {                                   \n"
                            "    vec4 ambient;                                   \n"
                            "    vec4 diffuse;                                   \n"
                            "    vec4 specular;                                  \n"
                            "    float shininess;                                \n"
                            "};                                                  \n"
                            "uniform Material object_material;                   \n"
                            "                                                    \n"
                            "struct Light {                                      \n"
                            "    int  itype;                                     \n"
                            "    vec4 ambient;                                   \n"
                            "    vec4 diffuse;                                   \n"
                            "    vec4 specular;                                  \n"
                            "    vec4 parameter;                                 \n"
                            "};                                                  \n"
                            "uniform Light light_parameter;                      \n"
                            "                                                    \n"
                            "in vec3 vec3_fragment_position;                     \n"
                            "in vec3 vec3_uniform_normal;                        \n"
                            "out vec4 FragColor;                                 \n"
                            "                                                    \n"
                            "uniform vec3 vec3_uniform_light_position;           \n"
                            "uniform vec4 vec4_uniform_light_color;              \n"
                            "uniform vec3 vec3_uniform_light_direction;          \n"
                            "                                                    \n"
                            "uniform vec4 vec4_uniform_object_color;             \n"
                            "                                                    \n"
                            "uniform vec3 vec3_uniform_camera_position;          \n"
                            "                                                    \n"
                            "void main()                                         \n"
                            "{                                                                                                                   \n"
                            "   vec3 vec3_light_direction = vec3(1.0, 1.0, 1.0);                                                                 \n"
                            "   float float_attenuation_to_light = 1.0;                                                                          \n"
                            "   if (0 == light_parameter.itype) {                                                                                \n"
                            "       vec3_light_direction = normalize(-vec3_uniform_light_direction);                                             \n"
                            "   } else {                                                                                                         \n"
                            "       vec3_light_direction = vec3_uniform_light_position - vec3_fragment_position;                                 \n"
                            "       float float_distance_to_light = length(vec3_light_direction);                                                \n"
                            "       vec3_light_direction = normalize(vec3_light_direction);                                                      \n"
                            "       float_attenuation_to_light = 1.0 / (light_parameter.parameter.x + light_parameter.parameter.y * float_distance_to_light + light_parameter.parameter.z * float_distance_to_light * float_distance_to_light);\n"
                            "   }                                                                                                                \n"
                            "                                                                                                                    \n"
                            "   float float_theta = dot(vec3_light_direction, normalize(-vec3_uniform_light_direction));                         \n"
                            "   if (2 == light_parameter.itype && float_theta < light_parameter.parameter.w) {                                   \n"
                            "       FragColor = vec4((light_parameter.ambient * object_material.diffuse).rgb, vec4_uniform_object_color.w);      \n"
                            "   } else {                                                                                                         \n"
                            "       vec4 vec4_ambient = light_parameter.ambient * vec4_uniform_light_color * object_material.ambient;                \n"
                            "                                                                                                                        \n"
                            "       vec3 vec3_norm = normalize(vec3_uniform_normal);                                                                 \n"
                            "       float float_diff = max(dot(vec3_norm, vec3_light_direction), 0.0);                                               \n"
                            "       vec4 vec4_diffuse = light_parameter.diffuse * vec4_uniform_light_color * (float_diff * object_material.diffuse); \n"
                            "                                                                                                                        \n"
                            "       vec3 vec3_camera_direction = normalize(vec3_uniform_camera_position - vec3_fragment_position);                   \n"
                            "       vec3 vec3_light_reflect_direction = reflect(-vec3_light_direction, vec3_norm);                                   \n"
                            "       float float_spec = pow(max(dot(vec3_camera_direction, vec3_light_reflect_direction), 0.0), object_material.shininess);  \n"
                            "       vec4 vec4_specular = light_parameter.specular * vec4_uniform_light_color * (float_spec * object_material.specular); \n"
                            "                                                                                                                        \n"
                            "       vec4 vec4_result = float_attenuation_to_light * (vec4_ambient + vec4_diffuse + vec4_specular);                   \n"
                            "     	FragColor = vec4(vec4_result.xyz, vec4_uniform_object_color.w);                                                  \n"
                            "   }                                                                                                                    \n"
                            "} \n", error_string, error_string_size))
                        {
                            break;
                        }

                        _program.Attach(vshader);
                        _program.Attach(fshader);
                        if (!_program.Link(error_string, error_string_size))
                        {
                            break;
                        }

                        _uniform_model = _program.GetUniformLocation("model");
                        _uniform_view = _program.GetUniformLocation("view");
                        _uniform_projection = _program.GetUniformLocation("projection");

                        _uniform_object_material.ambient = _program.GetUniformLocation("object_material.ambient");
                        _uniform_object_material.diffuse = _program.GetUniformLocation("object_material.diffuse");
                        _uniform_object_material.specular = _program.GetUniformLocation("object_material.specular");
                        _uniform_object_material.shininess = _program.GetUniformLocation("object_material.shininess");

                        _uniform_light_parameter.itype = _program.GetUniformLocation("light_parameter.itype");
                        _uniform_light_parameter.ambient = _program.GetUniformLocation("light_parameter.ambient");
                        _uniform_light_parameter.diffuse = _program.GetUniformLocation("light_parameter.diffuse");
                        _uniform_light_parameter.specular = _program.GetUniformLocation("light_parameter.specular");
                        _uniform_light_parameter.parameter = _program.GetUniformLocation("light_parameter.parameter");

                        _uniform_light_position = _program.GetUniformLocation("vec3_uniform_light_position");
                        _uniform_light_color = _program.GetUniformLocation("vec4_uniform_light_color");
                        _uniform_light_direction = _program.GetUniformLocation("vec3_uniform_light_direction");

                        _uniform_object_color = _program.GetUniformLocation("vec4_uniform_object_color");

                        _uniform_camera_position = _program.GetUniformLocation("vec3_uniform_camera_position");
                    } while (false);
                }
                return  -1 != _uniform_object_color;
            }

            void Destroy()
            {

            }

            void Render(const GeometryType& geometry_object, const opengl::material::ColorMaterial& object_color, const LightType& light, const opengl::scene::LightParameter& light_parameter, const opengl::scene::Camera& camera)
            {
                if (geometry_object.visible)
                {
                    _program.Use();
                    opengl::core::Uniform::Set<4, GLfloat>(_uniform_model, 1, glm::value_ptr(geometry_object.model), GL_FALSE);
                    opengl::core::Uniform::Set<4, GLfloat>(_uniform_view, 1, glm::value_ptr(camera.view), GL_FALSE);
                    opengl::core::Uniform::Set<4, GLfloat>(_uniform_projection, 1, glm::value_ptr(camera.projection), GL_FALSE);

                    opengl::core::Uniform::Set<4, GLfloat>(_uniform_object_material.ambient, 1, glm::value_ptr(object_color.ambient));
                    opengl::core::Uniform::Set<4, GLfloat>(_uniform_object_material.diffuse, 1, glm::value_ptr(object_color.diffuse));
                    opengl::core::Uniform::Set<4, GLfloat>(_uniform_object_material.specular, 1, glm::value_ptr(object_color.specular));
                    opengl::core::Uniform::Set<GLfloat>(_uniform_object_material.shininess, std::vector<GLfloat>{object_color.shininess});

                    opengl::core::Uniform::Set<GLint>(_uniform_light_parameter.itype, std::vector<GLint>{light.Type});
                    opengl::core::Uniform::Set<4, GLfloat>(_uniform_light_parameter.ambient, 1, glm::value_ptr(light_parameter.ambient));
                    opengl::core::Uniform::Set<4, GLfloat>(_uniform_light_parameter.diffuse, 1, glm::value_ptr(light_parameter.diffuse));
                    opengl::core::Uniform::Set<4, GLfloat>(_uniform_light_parameter.specular, 1, glm::value_ptr(light_parameter.specular));
                    opengl::core::Uniform::Set<4, GLfloat>(_uniform_light_parameter.parameter, 1, glm::value_ptr(light_parameter.parameter));

                    opengl::core::Uniform::Set<3, GLfloat>(_uniform_light_position, 1, glm::value_ptr(light.position));
                    opengl::core::Uniform::Set<4, GLfloat>(_uniform_light_color, 1, glm::value_ptr(light.color));
                    opengl::core::Uniform::Set<3, GLfloat>(_uniform_light_direction, 1, glm::value_ptr(light.direction));

                    opengl::core::Uniform::Set<4, GLfloat>(_uniform_object_color, 1, glm::value_ptr(geometry_object.color));

                    opengl::core::Uniform::Set<3, GLfloat>(_uniform_camera_position, 1, glm::value_ptr(camera.position));

                    _vao.Bind();

                    glDrawArrays(GeometryType::PRIMITIVE_SHAPE, 0, GeometryType::PRIMITIVE_SHAPE_COUNT);
                }
            }
            
        protected:
            core::VertexArrays _vao;
            core::Buffers<GL_ARRAY_BUFFER> _vbo;

        protected:
            core::Program _program;

        protected:
            GLint _uniform_model;
            GLint _uniform_view;
            GLint _uniform_projection;

        protected:
            GLint _uniform_light_position;
            GLint _uniform_light_color;
            GLint _uniform_light_direction;

        protected:
            GLint _uniform_object_color;

        protected:
            GLint _uniform_camera_position;

        protected:
            opengl::material::MaterialUniform _uniform_object_material;

        protected:
            opengl::scene::LightUniform _uniform_light_parameter;

        private:
            ColorRenderer(const ColorRenderer&) = delete;
            ColorRenderer& operator=(const ColorRenderer&) = delete;
            ColorRenderer(const ColorRenderer&&) = delete;
            ColorRenderer& operator=(const ColorRenderer&&) = delete;
        };
    };
};

#endif

