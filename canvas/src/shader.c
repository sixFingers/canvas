#include "types.h"

GLuint ShaderCompile(GLenum type, const char* source) {
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);

    GLint status = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

    if (status != GL_TRUE) {
        GLint length = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);

        char message[length];
        glGetShaderInfoLog(shader, length, NULL, message);
        glDeleteShader(shader);

        const char* shader_type = "";

        switch (type) {
            case GL_VERTEX_SHADER: shader_type = "Vertex shader"; break;
            case GL_FRAGMENT_SHADER: shader_type = "Fragment shader"; break;
        }

        printf("%s %s\n", shader_type, message);

        return 0;
    }

    return shader;
}

GLuint ShaderProgramLink(int num_shaders, const GLuint* shaders) {
    GLuint program = glCreateProgram();

    if (program == 0) {
        printf("ERROR: Couldn't create a new shader program.\n");
        return 0;
    }

    int i = 0;

    for (i = 0; i < num_shaders; i ++) {
        glAttachShader(program, shaders[i]);
    }

    glLinkProgram(program);

    GLint status = 0;
    glGetProgramiv(program, GL_LINK_STATUS, &status);

    if (status != GL_TRUE) {
        GLint length = 0;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);

        char message[length];
        glGetProgramInfoLog(program, length, NULL, message);
        glDeleteProgram(program);

        printf("%s %s\n", "Program ", message);

        return 0;
    }

    // Detach shaders once done.
    for (i = 0; i < num_shaders; i ++) {
        glDetachShader(program, shaders[i]);
    }

    return program;
}

GLuint ShaderProgramCreate(const char* vs, const char* fs) {
    GLuint v, f;

    v = ShaderCompile(GL_VERTEX_SHADER, vs);

    if (v == 0) {
        return 0;
    }

    f = ShaderCompile(GL_FRAGMENT_SHADER, fs);

    if (f == 0) {
        return 0;
    }

    GLuint shader[2] = {v, f};
    GLuint program = ShaderProgramLink(2, shader);

    return program;
}

const char* VERTEX_BASIC = MULTILINE_STRING(#version 330\n

    uniform mat4 Projection;
    uniform mat4 View;
    uniform mat4 Model;

    layout(location = 0) in vec3 VertexPosition;

    void main() {
        vec4 position = Projection * View * Model * vec4(VertexPosition.xyz, 1.0);
        gl_Position = position;
    }
);

const char* FRAGMENT_BASIC = MULTILINE_STRING(#version 330\n

    out vec4 FragColor;

    void main() {
        FragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);
    }
);

const char* VERTEX_2D_COLOR = MULTILINE_STRING(#version 330\n

    uniform mat4 Projection;
    uniform mat4 Model;

    layout(location = 0) in vec2 Position;

    void main() {
        vec4 position = Projection * Model * vec4(Position.xy, 0.0, 1.0);
        gl_Position = position;
    }
);

const char* FRAGMENT_2D_COLOR = MULTILINE_STRING(#version 330\n

    uniform vec3 Color;

    out vec4 FragColor;

    void main() {
        FragColor = vec4(Color.xyz, 1.0);
    }
);

const char* VERTEX_2D_TEXTURE = MULTILINE_STRING(#version 330\n

    uniform mat4 Projection;
    uniform mat4 Model;

    layout(location = 0) in vec2 Position;
    layout(location = 1) in vec2 UV;

    out vec2 uv;

    void main() {
        uv = UV;
        vec4 position = Projection * Model * vec4(Position.xy, 0.0, 1.0);
        gl_Position = position;
    }
);

const char* FRAGMENT_2D_TEXTURE = MULTILINE_STRING(#version 330\n

    uniform sampler2D Texture;

    in vec2 uv;

    out vec4 FragColor;

    void main() {
        FragColor = texture(Texture, uv);
    }
);

const char* VERTEX_TEXT = MULTILINE_STRING(#version 330\n

    uniform mat4 Projection;
    uniform mat4 Model;
    uniform float Layers;

    layout(location = 0) in vec2 Position;
    layout(location = 1) in float Layer;

    out float layer;

    void main() {
        layer = max(0.0, min(Layers - 1.0, Layer));
        vec4 position = Projection * Model * vec4(Position.xy, 0.0, 1.0);
        gl_Position = position;
    }
);

const char* FRAGMENT_TEXT = MULTILINE_STRING(#version 330\n

    uniform sampler2DArray Texture;

    in float layer;

    out vec4 FragColor;

    void main() {
        FragColor = texture(Texture, vec3(gl_PointCoord.xy, layer));
    }
);
