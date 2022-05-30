#include "opengl/io/Image.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace opengl {
    namespace io {
        Image::Image(const GLchar* file)
            : data(nullptr)
            , format(GL_RGB)
            , width(0), height(0)
            , channels(0)
        {
            data = stbi_load(file, &width, &height, &channels, 0);
            if (channels > 3)
            {
                format = GL_RGBA;
            }
        }

        Image::~Image()
        {
            if (data)
            {
                stbi_image_free(data);
            }
        }
    };
};

