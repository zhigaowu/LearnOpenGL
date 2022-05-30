// LearnOpenGL.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//


#include "opengl/core/Buffers.h"
#include "opengl/core/VertexArrays.h"
#include "opengl/core/Shader.h"
#include "opengl/core/Program.h"

#include "opengl/core/Texture.h"

#include "opengl/core/Uniform.h"

#include "opengl/io/Image.h"

#include "opengl/scene/Camera.h"

#include "opengl/scene/Light.h"
#include "opengl/scene/Cube.h"

#include "opengl/renderer/ColorRenderer.h"
#include "opengl/renderer/TextureRenderer.h"

#include <GLFW/glfw3.h>

#include <iostream>

static glm::vec3 camera_up(0.0f, 1.0f, 0.0f);
static opengl::scene::Camera camera = opengl::scene::Camera(glm::vec3(0.0f, 0.0f, 5.0f), glm::vec3(0.0f, 0.0f, 0.0f), camera_up);
static glm::vec3 move_front_step(0.0f, 0.0f, -1.0f);
static glm::vec3 move_right_step = glm::normalize(glm::cross(move_front_step, camera_up));
// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
float deltaTime = 0.0f;	// Time between current frame and last frame
float lastFrame = 0.0f; // Time of last frame
static void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    bool moved = false;
    const float cameraSpeed = 2.5f * deltaTime; // adjust accordingly
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        camera.Move(cameraSpeed * move_front_step, move_front_step);
        moved = true;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        camera.Move(-cameraSpeed * move_front_step, move_front_step);
        moved = true;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        camera.Move(cameraSpeed * move_right_step, move_front_step);
        moved = true;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        camera.Move(-cameraSpeed * move_right_step, move_front_step);
        moved = true;
    }

    if (moved)
    {
        std::cout << camera.position.x << ", " << camera.position.y << ", " << camera.position.z << std::endl;
    }
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
static void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

bool firstMouse = true;
float yaw = -90.0f;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
float pitch = 0.0f;
float lastX = 800.0f / 2.0;
float lastY = 600.0 / 2.0;
float fov = 45.0f;

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

    float sensitivity = 0.01f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    camera.LookDirection(yaw, pitch);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    fov -= (float)yoffset;
    if (fov < 1.0f)
        fov = 1.0f;
    if (fov > 45.0f)
        fov = 45.0f;
}

int main(int argc, char** argv)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    do 
    {
        int width = atoi(argv[2]), height = atoi(argv[3]);
        lastX = width / 2.0f;
        lastY = height / 2.0f;

        // glfw window creation
        // --------------------
        GLFWwindow* window = glfwCreateWindow(width, height, argv[1], nullptr, nullptr);
        if (window == nullptr)
        {
            std::cout << "Failed to create GLFW window" << std::endl;
            break;
        }
        glfwMakeContextCurrent(window);

        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
        glfwSetCursorPosCallback(window, mouse_callback);
        glfwSetScrollCallback(window, scroll_callback);
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

        // glad: load all OpenGL function pointers
        // ---------------------------------------
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            std::cout << "Failed to initialize GLAD" << std::endl;
            break;
        }

        char error_string[512] = { 0 };


        using DirectionalLight = opengl::scene::Light<opengl::scene::Cube, opengl::scene::Directional_Light>;
        using PointLight = opengl::scene::Light<opengl::scene::Cube, opengl::scene::Point_Light>;
        using SpotLight = opengl::scene::Light<opengl::scene::Cube, opengl::scene::Spot_Light>;

        // light
        using LightInUsage = SpotLight;
        LightInUsage light(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
        light.direction = glm::vec3(0.0f, -1.0f, -2.0f);

        opengl::scene::Cube cube(glm::vec4(1.0f, 0.5f, 0.31f, 1.0f));

        opengl::scene::LightParameter light_no_effect;

        opengl::scene::LightParameter light_parameter = opengl::scene::LightParameter_Normal;
        light_parameter.diffuse = glm::vec4(0.8f, 0.8f, 0.8f, 1.0f);
        light_parameter.parameter = opengl::scene::PointLight_Parameter_Distance_32(30.0f);

        opengl::renderer::ColorRenderer<LightInUsage> color_renderer;
        if (!color_renderer.Create(error_string, 512))
        {
            std::cout << "Failed to create color renderer: " << error_string << std::endl;
            break;
        }

        opengl::material::TextureMaterial cube_texture(GL_TEXTURE0, opengl::io::Image("../container2.png"), GL_TEXTURE1, opengl::io::Image("../container2_specular.png"), 64.0f);

        opengl::renderer::TextureRenderer<LightInUsage> texture_renderer;
        if (!texture_renderer.Create(error_string, 512))
        {
            std::cout << "Failed to create texture renderer: " << error_string << std::endl;
            break;
        }

        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

        glm::vec3 cube_positions[] = {
            glm::vec3(0.0f,  0.0f,  0.0f),
            glm::vec3(2.0f,  5.0f, -15.0f),
            glm::vec3(-1.5f, -2.2f, -2.5f),
            glm::vec3(-3.8f, -2.0f, -12.3f),
            glm::vec3(2.4f, -0.4f, -3.5f),
            glm::vec3(-1.7f,  3.0f, -7.5f),
            glm::vec3(1.3f, -2.0f, -2.5f),
            glm::vec3(1.5f,  2.0f, -2.5f),
            glm::vec3(1.5f,  0.2f, -1.5f),
            glm::vec3(-1.3f,  1.0f, -1.5f)
        };

        const float radius = 10.0f;

        lastFrame = glfwGetTime(); // Time of last frame
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        // initialize light
        light.MoveTo(glm::vec3(0.0f, 2.0f, 2.0f), 30.0f, glm::vec3(0.0f, 1.0f, 6.0f));
        light.Show(true);

        // initialize cube
        cube.Show(true);

        float angle = 0.0f;
        // render loop
        // -----------
        while (!glfwWindowShouldClose(window))
        {
            float currentFrame = glfwGetTime();
            deltaTime = currentFrame - lastFrame;
            lastFrame = currentFrame;

            // input
            // -----
            processInput(window);

            // render
            // ------
            glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            camera.ChangeViewport(width, height, fov, 0.1f, 100.0f);

            //light.color.x = sin(glfwGetTime() * 0.0f);
            //light.color.y = sin(glfwGetTime() * 0.7f);
            //light.color.z = sin(glfwGetTime() * 1.3f);

            // draw scene
            color_renderer.Render(light, opengl::material::Material_No_Effect, light, light_no_effect, camera);

            for (int i1 = 0; i1 < 5; ++i1)
            {
                cube.MoveTo(cube_positions[i1], angle, glm::vec3(1.0f, 1.0f, 0.0f));
                color_renderer.Render(cube, opengl::material::Material_Ruby, light, light_parameter, camera);
            }
            for (int i2 = 5; i2 < 10; ++i2)
            {
                cube.MoveTo(cube_positions[i2], angle, glm::vec3(1.0f, 1.0f, 0.0f));
                texture_renderer.Render(cube, cube_texture, light, light_parameter, camera);
            }

            angle += 1.0f;
            
            // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
            // -------------------------------------------------------------------------------
            glfwSwapBuffers(window);
            glfwPollEvents();
        }
    } while (false);

    glfwTerminate();

    return 0;
}


