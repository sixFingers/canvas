#include "types.h"

static float screen_ratio;
static mat4 projection2D;
static mat4 view2D;
static mat4 model2D;

static GLint program2DColor;
static GLint projectionLocation2DColor;
static GLint modelLocation2DColor;
static GLint colorLocation2DColor;

static GLint program2DTexture;
static GLint projectionLocation2DTexture;
static GLint modelLocation2DTexture;

static GLint programText;
static GLint projectionLocationText;
static GLint modelLocationText;
static GLint layersLocationText;

void DrawInit(int width, int height) {
    screen_ratio = (float)width / height;
    projection2D = mat4_ortho(0, width, height, 0, -1, 1);
    model2D = mat4_identity();

    program2DColor = ShaderProgramCreate(VERTEX_2D_COLOR, FRAGMENT_2D_COLOR);
    projectionLocation2DColor = glGetUniformLocation(program2DColor, "Projection");
    modelLocation2DColor = glGetUniformLocation(program2DColor, "Model");
    colorLocation2DColor = glGetUniformLocation(program2DColor, "Color");

    program2DTexture = ShaderProgramCreate(VERTEX_2D_TEXTURE, FRAGMENT_2D_TEXTURE);
    projectionLocation2DTexture = glGetUniformLocation(program2DTexture, "Projection");
    modelLocation2DTexture = glGetUniformLocation(program2DTexture, "Model");

    programText = ShaderProgramCreate(VERTEX_TEXT, FRAGMENT_TEXT);
    projectionLocationText = glGetUniformLocation(programText, "Projection");
    modelLocationText = glGetUniformLocation(programText, "Model");
    layersLocationText = glGetUniformLocation(programText, "Layers");
}

void DrawRect(GLuint rect, int x, int y, vec3 color) {
    glUseProgram(program2DColor);

    glUniformMatrix4fv(projectionLocation2DColor, 1, GL_FALSE, projection2D.v);

    vec3 translation = {x, y, 0};
    mat4_set_identity(&model2D);
    mat4_set_translate(&model2D, translation);
    glUniformMatrix4fv(modelLocation2DColor, 1, GL_FALSE, model2D.v);

    glUniform3fv(colorLocation2DColor, 1, color.v);

    glBindVertexArray(rect);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void DrawImage(GLuint quad, Image image, int x, int y) {
    glUseProgram(program2DTexture);

    glUniformMatrix4fv(projectionLocation2DTexture, 1, GL_FALSE, projection2D.v);

    vec3 translation = {x, y, 0};
    mat4_set_identity(&model2D);
    mat4_set_translate(&model2D, translation);
    glUniformMatrix4fv(modelLocation2DTexture, 1, GL_FALSE, model2D.v);

    glBindTexture(GL_TEXTURE_2D, image.texture);

    glBindVertexArray(quad);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void DrawText(GLuint glyphs, ImageArray image, int count) {
    glUseProgram(programText);

    glUniformMatrix4fv(projectionLocationText, 1, GL_FALSE, projection2D.v);

    // vec3 translation = {x, y, 0};
    mat4_set_identity(&model2D);
    // mat4_set_translate(&model2D, translation);
    glUniformMatrix4fv(modelLocationText, 1, GL_FALSE, model2D.v);

    glUniform1f(layersLocationText, (float)image.layers);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D_ARRAY, image.texture);

    glPointSize(image.width);
    glPointParameteri(GL_POINT_SPRITE_COORD_ORIGIN, GL_UPPER_LEFT);

    glBindVertexArray(glyphs);
    glDrawArrays(GL_POINTS, 0, count);
}
