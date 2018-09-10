#include "types.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Image ImageCreate(const char* path, GLint wrap, GLint filter) {
    int width, height, nrChannels;
    unsigned char* data = stbi_load(path, &width, &height, &nrChannels, 4);

    Image image = {};

    if (data == NULL) {
        printf("Error loading image %s\n", path);
        return image;
    }

    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

    stbi_image_free(data);

    image.width = width;
    image.height = height;
    image.texture = texture;

    return image;
}

ImageArray ImageCreateArray(const char* path, int width, int height, GLint wrap, GLint filter) {
    int image_width, image_height, channels;
    unsigned char* data = stbi_load(path, &image_width, &image_height, &channels, 4);

    ImageArray image = {};

    if (data == NULL) {
        printf("Error loading image %s\n", path);
        return image;
    }

    int cols = image_width / width;
    int rows = image_height / height;
    int c = 0;
    int r = 0;
    int x = 0;
    int y = 0;
    int p = 0;
    int layers = cols * rows;
    int byte_count = image_width * image_height * 4;
    unsigned char vertical[byte_count];

    for (r = 0; r < rows; r ++) {
        for (c = 0; c < cols; c ++) {
            int o = (r * cols * height * width) + (c * width);

            for (y = 0; y < height; y ++) {
                for (x = 0; x < width; x ++) {
                    int s = (o + (y * image_width) + x) * 4;

                    vertical[p] = data[s];
                    vertical[p + 1] = data[s + 1];
                    vertical[p + 2] = data[s + 2];
                    vertical[p + 3] = data[s + 3];

                    p += 4;
                }
            }
        }
    }

    GLuint texture;
    glGenTextures(1, &texture);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D_ARRAY, texture);
    glTexStorage3D(GL_TEXTURE_2D_ARRAY, 1, GL_RGBA8, width, height, layers);
    glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, 0, width, height, layers, GL_RGBA, GL_UNSIGNED_BYTE, vertical);

    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, wrap);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, wrap);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, filter);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, filter);

    stbi_image_free(data);

    image.width = width;
    image.height = height;
    image.layers = layers;
    image.texture = texture;

    return image;
}
