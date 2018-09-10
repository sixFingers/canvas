#include "types.h"

GLuint GeomRect(int w, int h) {
    Point rect[] = {
        {w, h},
        {w, 0},
        {0, h},
        {w, 0},
        {0, 0},
        {0, h},
    };

    GLuint vao, vbo;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(rect), rect, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Point), (void*)0);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);

    return vao;
}

GLuint GeomImage(Image image) {
    int w = image.width;
    int h = image.height;

    PointTextured rect[] = {
        {{w, h}, {1, 1}},
        {{w, 0}, {1, 0}},
        {{0, h}, {0, 1}},
        {{w, 0}, {1, 0}},
        {{0, 0}, {0, 0}},
        {{0, h}, {0, 1}},
    };

    GLuint vao, vbo;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(rect), rect, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(PointTextured), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(PointTextured), (void*)sizeof(Point));
    glEnableVertexAttribArray(1);
    glBindVertexArray(0);

    return vao;
}
