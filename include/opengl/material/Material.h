#ifndef _OPENGL_MATERIAL_MATERIAL_HEADER_H_
#define _OPENGL_MATERIAL_MATERIAL_HEADER_H_

#include "opengl/core/Texture.h"

#include "opengl/io/Image.h"

#include <glm/glm.hpp>

namespace opengl {
    namespace material {

        struct MaterialUniform
        {
            GLint ambient = -1;
            GLint diffuse = -1;
            GLint specular = -1;

            GLint shininess = -1;
        };

        struct ColorMaterial 
        {
            glm::vec4 ambient;
            glm::vec4 diffuse;
            glm::vec4 specular;

            GLfloat shininess;

            ColorMaterial()
                : ambient(1.0f, 1.0f, 1.0f, 1.0f)
                , diffuse(1.0f, 1.0f, 1.0f, 1.0f)
                , specular(1.0f, 1.0f, 1.0f, 1.0f)
                , shininess(1.0f)
            {}

            ColorMaterial(const glm::vec4& a, const glm::vec4& d, const glm::vec4& s, GLfloat sh)
                : ambient(a)
                , diffuse(d)
                , specular(s)
                , shininess(sh)
            {}

            ColorMaterial(const glm::vec3& a, const glm::vec3& d, const glm::vec3& s, GLfloat sh)
                : ambient(a, 1.0f)
                , diffuse(d, 1.0f)
                , specular(s, 1.0f)
                , shininess(sh)
            {}
        };

        static const ColorMaterial Material_No_Effect;

        // http://devernay.free.fr/cours/opengl/materials.html
        static const ColorMaterial Material_Emerald = ColorMaterial(glm::vec3(0.0215f, 0.1745f, 0.0215f), glm::vec3(0.07568f, 0.61424f, 0.07568f), glm::vec3(0.633f, 0.727811f, 0.633f), 0.6f * 128.f);
        static const ColorMaterial Material_Jade = ColorMaterial(glm::vec3(0.135f, 0.2225f, 0.1575f), glm::vec3(0.54f, 0.89f, 0.63f), glm::vec3(0.316228f, 0.316228f, 0.316228f), 0.1f * 128.f);
        static const ColorMaterial Material_Obsidian = ColorMaterial(glm::vec3(0.05375f, 0.05f, 0.06625f), glm::vec3(0.18275f, 0.17f, 0.22525f), glm::vec3(0.332741f, 0.328634f, 0.346435f), 0.3f * 128.f);
        static const ColorMaterial Material_Pearl = ColorMaterial(glm::vec3(0.25f, 0.20725f, 0.20725f), glm::vec3(1.0f, 0.829f, 0.829f), glm::vec3(0.296648f, 0.296648f, 0.296648f), 0.088f * 128.f);
        static const ColorMaterial Material_Ruby = ColorMaterial(glm::vec3(0.1745f, 0.01175f, 0.01175f), glm::vec3(0.61424f, 0.04136f, 0.04136f), glm::vec3(0.727811f, 0.626959f, 0.626959f), 0.6f * 128.f);
        static const ColorMaterial Material_Turquoise = ColorMaterial(glm::vec3(0.1f, 0.18725f, 0.1745f), glm::vec3(0.396f, 0.74151f, 0.69102f), glm::vec3(0.297254f, 0.30829f, 0.306678f), 0.1f * 128.f);
        static const ColorMaterial Material_Brass = ColorMaterial(glm::vec3(0.329412f, 0.223529f, 0.027451f), glm::vec3(0.780392f, 0.568627f, 0.113725f), glm::vec3(0.992157f, 0.941176f, 0.807843f), 0.21794872f * 128.f);
        static const ColorMaterial Material_Bronze = ColorMaterial(glm::vec3(0.2125f, 0.1275f, 0.054f), glm::vec3(0.714f, 0.4284f, 0.18144f), glm::vec3(0.393548f, 0.271906f, 0.166721f), 0.2f * 128.f);
        static const ColorMaterial Material_Chrome = ColorMaterial(glm::vec3(0.25f, 0.25f, 0.25f), glm::vec3(0.4f, 0.4f, 0.4f), glm::vec3(0.774597f, 0.774597f, 0.774597f), 0.6f * 128.f);
        static const ColorMaterial Material_Copper = ColorMaterial(glm::vec3(0.19125f, 0.0735f, 0.0225f), glm::vec3(0.7038f, 0.27048f, 0.0828f), glm::vec3(0.256777f, 0.137622f, 0.086014f), 0.1f * 128.f);
        static const ColorMaterial Material_Gold = ColorMaterial(glm::vec3(0.24725f, 0.1995f, 0.0745f), glm::vec3(0.75164f, 0.60648f, 0.22648f), glm::vec3(0.628281f, 0.555802f, 0.366065f), 0.4f * 128.f);
        static const ColorMaterial Material_Silver = ColorMaterial(glm::vec3(0.19225f, 0.19225f, 0.19225f), glm::vec3(0.50754f, 0.50754f, 0.50754f), glm::vec3(0.508273f, 0.508273f, 0.508273f), 0.4f * 128.f);

        static const ColorMaterial Material_Plastic_Black = ColorMaterial(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.01f, 0.01f, 0.01f), glm::vec3(0.50f, 0.50f, 0.50f), 0.25f * 128.f);
        static const ColorMaterial Material_Plastic_Cyan = ColorMaterial(glm::vec3(0.0f, 0.1f, 0.06f), glm::vec3(0.0f, 0.50980392f, 0.50980392f), glm::vec3(0.50196078f, 0.50196078f, 0.50196078f), 0.25f * 128.f);
        static const ColorMaterial Material_Plastic_Green = ColorMaterial(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.1f, 0.35f, 0.1f), glm::vec3(0.45f, 0.55f, 0.45f), 0.25f * 128.f);
        static const ColorMaterial Material_Plastic_Red = ColorMaterial(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.5f, 0.0f, 0.0f), glm::vec3(0.7f, 0.6f, 0.6f), 0.25f * 128.f);
        static const ColorMaterial Material_Plastic_White = ColorMaterial(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.55f, 0.55f, 0.55f), glm::vec3(0.70f, 0.70f, 0.70f), 0.25f * 128.f);
        static const ColorMaterial Material_Plastic_Yellow = ColorMaterial(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.5f, 0.5f, 0.0f), glm::vec3(0.60f, 0.60f, 0.50f), 0.25f * 128.f);

        static const ColorMaterial Material_Rubber_Black = ColorMaterial(glm::vec3(0.02f, 0.02f, 0.02f), glm::vec3(0.01f, 0.01f, 0.01f), glm::vec3(0.4f, 0.4f, 0.4f), 0.078125f * 128.f);
        static const ColorMaterial Material_Rubber_Cyan = ColorMaterial(glm::vec3(0.0f, 0.05f, 0.05f), glm::vec3(0.4f, 0.5f, 0.5f), glm::vec3(0.04f, 0.7f, 0.7f), 0.078125f * 128.f);
        static const ColorMaterial Material_Rubber_Green = ColorMaterial(glm::vec3(0.0f, 0.05f, 0.0f), glm::vec3(0.4f, 0.5f, 0.4f), glm::vec3(0.04f, 0.7f, 0.04f), 0.078125f * 128.f);
        static const ColorMaterial Material_Rubber_Red = ColorMaterial(glm::vec3(0.05f, 0.0f, 0.0f), glm::vec3(0.5f, 0.4f, 0.4f), glm::vec3(0.7f, 0.04f, 0.04f), 0.078125f * 128.f);
        static const ColorMaterial Material_Rubber_White = ColorMaterial(glm::vec3(0.05f, 0.05f, 0.05f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.7f, 0.7f, 0.7f), 0.078125f * 128.f);
        static const ColorMaterial Material_Rubber_Yellow = ColorMaterial(glm::vec3(0.05f, 0.05f, 0.0f), glm::vec3(0.5f, 0.5f, 0.4f), glm::vec3(0.7f, 0.7f, 0.04f), 0.078125f * 128.f);

        struct TextureMaterial
        {
            GLenum diffuse_unit;
            GLenum specular_unit;

            opengl::core::Texture texture;

            GLfloat shininess;

            TextureMaterial(GLenum diffuse_unit_, const opengl::io::Image& texture_image, GLenum specular_unit_, const opengl::io::Image& specular_image, GLfloat shininess_)
                : diffuse_unit(diffuse_unit_)
                , specular_unit(specular_unit_)
                , texture(2)
                , shininess(shininess_)
            {
                texture.Active(0, diffuse_unit);
                texture.SetParameter(GL_TEXTURE_WRAP_S, GL_REPEAT);
                texture.SetParameter(GL_TEXTURE_WRAP_T, GL_REPEAT);
                texture.SetParameter(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                texture.SetParameter(GL_TEXTURE_MAG_FILTER, GL_LINEAR);

                texture.Upload(texture_image.data, GL_UNSIGNED_BYTE, texture_image.format, texture_image.width, texture_image.height, texture_image.format);
                texture.GenerateMipmap();

                texture.Active(1, specular_unit);
                texture.SetParameter(GL_TEXTURE_WRAP_S, GL_REPEAT);
                texture.SetParameter(GL_TEXTURE_WRAP_T, GL_REPEAT);
                texture.SetParameter(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                texture.SetParameter(GL_TEXTURE_MAG_FILTER, GL_LINEAR);

                texture.Upload(specular_image.data, GL_UNSIGNED_BYTE, specular_image.format, specular_image.width, specular_image.height, specular_image.format);
                texture.GenerateMipmap();
            }

            inline void Activate() const
            {
                texture.Active(0, diffuse_unit);
                texture.Active(1, specular_unit);
            }

        private:
            TextureMaterial() = delete;
            TextureMaterial(const TextureMaterial&) = delete;
            TextureMaterial& operator=(const TextureMaterial&) = delete;
            TextureMaterial(const TextureMaterial&&) = delete;
            TextureMaterial& operator=(const TextureMaterial&&) = delete;
        };
    };
};

#endif

