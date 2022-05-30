#ifndef _OPENGL_SCENE_LIGHT_HEADER_H_
#define _OPENGL_SCENE_LIGHT_HEADER_H_

#include "opengl/Implement.h"

#include <glm/glm.hpp>

namespace opengl {
    namespace scene {

        static const GLint Directional_Light = 0;
        static const GLint Point_Light = 1;
        static const GLint Spot_Light = 2;

        template<typename GeometryType, GLint LightType = 0>
        class Light : public GeometryType
        {
        public:
            using DisplayGeometryType = GeometryType;

        public:
            static const GLint Type = LightType;

        public:
            explicit Light(const glm::vec4& color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f))
                : GeometryType(color)
            {}

            ~Light()
            {}
            
            glm::vec3 direction;
        };

        struct LightParameter
        {
            glm::vec4 ambient;
            glm::vec4 diffuse;
            glm::vec4 specular;

            glm::vec4 parameter;

            LightParameter()
                : ambient(1.0f, 1.0f, 1.0f, 1.0f)
                , diffuse(1.0f, 1.0f, 1.0f, 1.0f)
                , specular(1.0f, 1.0f, 1.0f, 1.0f)
                , parameter(0.0f, 0.0f, 0.0f, 0.0f)
            {}

            LightParameter(const glm::vec4& a, const glm::vec4& d, const glm::vec4& s)
                : ambient(a)
                , diffuse(d)
                , specular(s)
                , parameter(0.0f, 0.0f, 0.0f, 0.0f)
            {}

            LightParameter(const glm::vec3& a, const glm::vec3& d, const glm::vec3& s)
                : ambient(a, 1.0f)
                , diffuse(d, 1.0f)
                , specular(s, 1.0f)
                , parameter(0.0f, 0.0f, 0.0f, 0.0f)
            {}
        };

        static const LightParameter LightParameter_No_Effect = LightParameter();
        static const LightParameter LightParameter_Normal = LightParameter(glm::vec4(0.2f, 0.2f, 0.2f, 1.0f), glm::vec4(0.5f, 0.5f, 0.5f, 1.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

        /*
        http://www.ogre3d.org/tikiwiki/tiki-index.php?page=-Point+Light+Attenuation
        distance parameter(constant	linear quadratic)
        7	                 1.0	0.7     1.8
        13	                 1.0	0.35	0.44
        20	                 1.0	0.22	0.20
        32	                 1.0	0.14	0.07
        50	                 1.0	0.09	0.032
        65	                 1.0	0.07	0.017
        100	                 1.0	0.045	0.0075
        160	                 1.0	0.027	0.0028
        200	                 1.0	0.022	0.0019
        325	                 1.0	0.014	0.0007
        600	                 1.0	0.007	0.0002
        3250	             1.0	0.0014	0.000007
        */
        static inline glm::vec4 PointLight_Parameter_Distance_7(float cutoff_angle = 90.0f) { return glm::vec4(1.0f, 0.7f, 1.8f, glm::cos(glm::radians(cutoff_angle))); }
        static inline glm::vec4 PointLight_Parameter_Distance_13(float cutoff_angle = 90.0f) { return glm::vec4(1.0f, 0.35f, 0.44f, glm::cos(glm::radians(cutoff_angle))); }
        static inline glm::vec4 PointLight_Parameter_Distance_20(float cutoff_angle = 90.0f) { return glm::vec4(1.0f, 0.22f, 0.20f, glm::cos(glm::radians(cutoff_angle))); }
        static inline glm::vec4 PointLight_Parameter_Distance_32(float cutoff_angle = 90.0f) { return glm::vec4(1.0f, 0.14f, 0.07f, glm::cos(glm::radians(cutoff_angle))); }
        static inline glm::vec4 PointLight_Parameter_Distance_50(float cutoff_angle = 90.0f) { return glm::vec4(1.0f, 0.09f, 0.032f, glm::cos(glm::radians(cutoff_angle))); }
        static inline glm::vec4 PointLight_Parameter_Distance_65(float cutoff_angle = 90.0f) { return glm::vec4(1.0f, 0.07f, 0.017f, glm::cos(glm::radians(cutoff_angle))); }
        static inline glm::vec4 PointLight_Parameter_Distance_100(float cutoff_angle = 90.0f) { return glm::vec4(1.0f, 0.045f, 0.0075f, glm::cos(glm::radians(cutoff_angle))); }
        static inline glm::vec4 PointLight_Parameter_Distance_160(float cutoff_angle = 90.0f) { return glm::vec4(1.0f, 0.027f, 0.0028f, glm::cos(glm::radians(cutoff_angle))); }
        static inline glm::vec4 PointLight_Parameter_Distance_200(float cutoff_angle = 90.0f) { return glm::vec4(1.0f, 0.022f, 0.0019f, glm::cos(glm::radians(cutoff_angle))); }
        static inline glm::vec4 PointLight_Parameter_Distance_325(float cutoff_angle = 90.0f) { return glm::vec4(1.0f, 0.014f, 0.0007f, glm::cos(glm::radians(cutoff_angle))); }
        static inline glm::vec4 PointLight_Parameter_Distance_600(float cutoff_angle = 90.0f) { return glm::vec4(1.0f, 0.007f, 0.0002f, glm::cos(glm::radians(cutoff_angle))); }
        static inline glm::vec4 PointLight_Parameter_Distance_3250(float cutoff_angle = 90.0f) { return glm::vec4(1.0f, 0.0014f, 0.000007f, glm::cos(glm::radians(cutoff_angle))); }
        static inline glm::vec4 PointLight_Parameter_Distance(float constant, float linear, float quadratic, float cutoff_angle = 90.0f) { return glm::vec4(constant, linear, quadratic, glm::cos(glm::radians(cutoff_angle))); }

        struct LightUniform
        {
            GLint itype = -1;

            GLint ambient = -1;
            GLint diffuse = -1;
            GLint specular = -1;

            GLint parameter = -1;
        };
    };
};

#endif

