#include "opengl/scene/Camera.h"

namespace opengl {
    namespace scene {

        Camera::Camera()
            : position()
            , target()
            , up()
            , view()
            , projection()
        {
        }

        Camera::Camera(const glm::vec3& position_, const glm::vec3& target_, const glm::vec3& up_)
            : position(position_)
            , target(target_)
            , up(up_)
            , view(glm::lookAt(position, target, up))
            , projection()
        {
        }

        Camera::~Camera()
        {
        }

        const glm::mat4& Camera::Move(const glm::vec3& change)
        {
            position += change;
            view = glm::lookAt(position, target, up);
            return view;
        }

        const glm::mat4& Camera::Move(const glm::vec3& change, const glm::vec3& relative)
        {
            position += change;
            target = position + relative;
            view = glm::lookAt(position, target, up);
            return view;
        }

        void Camera::ChangeViewport(GLint width, GLint height, GLfloat fov, GLfloat near_plane, GLfloat far_plane)
        {
            projection = glm::perspective(glm::radians(fov), static_cast<GLfloat>(width) / static_cast<GLfloat>(height), near_plane, far_plane);
        }

        const glm::mat4& Camera::LookDirection(float yaw, float pitch, float/* roll*/)
        {
            target = position + glm::vec3(cos(glm::radians(yaw)) * cos(glm::radians(pitch)), sin(glm::radians(pitch)), sin(glm::radians(yaw)) * cos(glm::radians(pitch)));
            view = glm::lookAt(position, target, up);
            return view;
        }

        const glm::mat4& Camera::LookAt(const glm::vec3& target_)
        {
            target = target_;
            view = glm::lookAt(position, target, up);
            return view;
        }
    };
};

