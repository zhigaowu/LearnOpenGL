#ifndef _OPENGL_SCENE_CAMERA_HEADER_H_
#define _OPENGL_SCENE_CAMERA_HEADER_H_

#include "opengl/Implement.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace opengl {
    namespace scene {
        // https://learnopengl.com/Getting-started/Camera
        class Camera
        {
        public:
            explicit Camera();
            explicit Camera(const glm::vec3& position, const glm::vec3& target, const glm::vec3& up);
            ~Camera();

            // move camera and keep the target
            const glm::mat4& Move(const glm::vec3& change);

            // move camera and change the target with relative vector
            const glm::mat4& Move(const glm::vec3& change, const glm::vec3& relative);

            void ChangeViewport(GLint width, GLint height, GLfloat fov, GLfloat near_plane, GLfloat far_plane);

            // change direction
            const glm::mat4& LookDirection(float yaw, float pitch, float roll = 0.0f);

            // change target
            const glm::mat4& LookAt(const glm::vec3& target);

        public:
            glm::vec3 position;
            glm::vec3 target;
            glm::vec3 up;

        public:
            glm::mat4 view;

        public:
            glm::mat4 projection;
        };
    };
};

#endif

