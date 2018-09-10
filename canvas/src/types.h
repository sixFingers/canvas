#ifndef TYPES_H
#define TYPES_H

/* System headers */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/* Library headers */
#include <GLFW/glfw3.h>
#include <glad/glad.h>

/* Types */
typedef struct vec2 {
    float x, y;
} vec2;

typedef struct vec3 {
    GLfloat v[3];
} vec3;

typedef struct mat4 {
    GLfloat v[16];
} mat4;

typedef struct Point {
    vec2 position;
} Point;

typedef struct PointTextured {
    vec2 position;
    vec2 uv;
} PointTextured;

typedef struct Vertex {
    vec3 position;
    vec2 uv;
} Vertex;

typedef struct Image {
    int width;
    int height;
    GLuint texture;
} Image;

typedef struct ImageArray {
    int width;
    int height;
    int layers;
    GLuint texture;
} ImageArray;

typedef struct Glyph {
    vec2 position;
    float code;
} Glyph;

/* Window */
#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

int WindowInit();
int WindowActive();
void WindowSwap();
void WindowPollEvents();
void WindowClose();

/* Math */
void mat4_print(mat4 m);
mat4 mat4_identity();
void mat4_set_identity(mat4* out);
mat4 mat4_translate(vec3 t);
void mat4_set_translate(mat4* out, vec3 t);
mat4 mat4_ortho(float left, float right, float bottom, float top, float near, float far);

/* Geometry */
GLuint GeomRect(int w, int h);
GLuint GeomGrid(int cols, int rows, int w, int h, int padding);
GLuint GeomImage(Image image);

/* Images */
Image ImageCreate(const char* path, GLint wrap, GLint filter);
ImageArray ImageCreateArray(const char* path, int rows, int cols, GLint wrap, GLint filter);

/* Console */
#define ASCII_OFFSET 32

GLuint ConsoleInit(int _rows, int _cols, float kerning, float line_height);
void ConsolePushString(const char* string);
void ConsoleOffset(int offset);
void ConsolePrint();
void ConsoleDestroy();

/* Shaders */
#define MULTILINE_STRING(...) #__VA_ARGS__

GLuint ShaderCompile(GLenum type, const char* source);
GLuint ShaderProgramLink(int num_shaders, const GLuint* shaders);
GLuint ShaderProgramCreate(const char* vs, const char* fs);

extern const char* VERTEX_2D_COLOR;
extern const char* FRAGMENT_2D_COLOR;
extern const char* VERTEX_2D_TEXTURE;
extern const char* FRAGMENT_2D_TEXTURE;
extern const char* VERTEX_TEXT;
extern const char* FRAGMENT_TEXT;

/* Drawing */
void DrawInit(int width, int height);
void DrawRect(GLuint rect, int x, int y, vec3 color);
void DrawImage(GLuint quad, Image image, int x, int y);
void DrawText(GLuint glyphs, ImageArray image, int count);

#endif