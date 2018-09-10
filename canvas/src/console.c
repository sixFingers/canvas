#include "types.h"

static int buffer_size = 0;
static int rows = 0;
static int cols = 0;
static char* buffer;
static int cursor = 0;
static GLuint vao, vbo;
static Glyph* glyphs;

static void UpdateVBO();

GLuint ConsoleInit(int _rows, int _cols, float kerning, float line_height) {
    buffer_size = _rows * _cols;
    rows = _rows;
    cols = _cols;
    buffer = calloc(buffer_size, sizeof(char));
    glyphs = calloc(buffer_size, sizeof(Glyph));

    int b = 0;
    int r = 0;
    int c = 0;

    for (b = 0; b < buffer_size; b ++) {
        r = floor(b / cols);
        c = (b - (r * cols));

        float x = kerning * c;
        float y = line_height * r;
        int g = buffer[b] - ASCII_OFFSET;
        float ox = (float)(kerning / 2.0);
        float oy = (float)(line_height / 2.0);

        g = g < 0 ? 0 : g > 128 ? 128 : g;

        Glyph glyph = {
            {ox + x, oy + y}, g
        };

        glyphs[b] = glyph;
    }

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, buffer_size * sizeof(Glyph), glyphs, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Glyph), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 1, GL_FLOAT, GL_FALSE, sizeof(Glyph), (void*)sizeof(vec2));
    glEnableVertexAttribArray(1);
    glBindVertexArray(0);

    return vao;
}

void ConsolePushString(const char* string) {
    int length = strlen(string);
    int chunk_length = length > buffer_size ? buffer_size : length;

    if (cursor + chunk_length > buffer_size) {
        int offset = cursor + chunk_length - buffer_size;
        ConsoleOffset(offset);
    }

    int from = length > buffer_size ? length - buffer_size : 0;
    int s;
    int c = 0;

    for (s = from; s < length; s ++) {
        buffer[cursor + c] = string[s];
        c ++;
    }

    cursor += chunk_length;

    UpdateVBO();
}

void ConsoleOffset(int offset) {
    int s, to;
    to = buffer_size - offset;

    for (s = 0; s < to; s ++) {
        buffer[s] = buffer[s + offset];
    }

    cursor -= offset;
}

void ConsolePrint() {
    printf("%s\n", buffer);
}

static void UpdateVBO() {
    int b = 0;

    for (b = 0; b < buffer_size; b ++) {
        int g = buffer[b] - ASCII_OFFSET;

        g = g < 0 ? 0 : g > 128 ? 128 : g;

        glyphs[b].code = g;
    }

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferSubData(GL_ARRAY_BUFFER, 0, buffer_size * sizeof(Glyph), glyphs);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void ConsoleDestroy() {
    free(buffer);
    free(glyphs);
}
