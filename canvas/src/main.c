#include "types.h"

int main(void) {
    if (!WindowInit()) {
        return EXIT_FAILURE;
    }

    /* Initialize matrices */
    DrawInit(WINDOW_WIDTH, WINDOW_HEIGHT);

    int rows = 10;
    int cols = 10;
    GLuint console = ConsoleInit(rows, cols, 18, 18);
    ConsolePushString("It is a long established fact that a reader will be distracted by the readable content of a page when looking at its layout. The point of using Lorem Ipsum is that it has a more-or-less normal distribution of letters, as opposed to using 'Content here, content here', making it look like readable English. Many desktop publishing packages and web page editors now use Lorem Ipsum as their default model text, and a search for 'lorem ipsum' will uncover many web sites still in their infancy. Various versions have evolved over the years, sometimes by accident, sometimes on purpose (injected humour and the like). It is a long established fact that a reader will be distracted by the readable content of a page when looking at its layout. The point of using Lorem Ipsum is that it has a more-or-less normal distribution of letters, as opposed to using 'Content here, content here', making it look like readable English. Many desktop publishing packages and web page editors now use Lorem Ipsum as their default model text, and a search for 'lorem ipsum' will uncover many web sites still in their infancy. Various versions have evolved over the years, sometimes by accident, sometimes on purpose (injected humour and the like).");

    Image image = ImageCreate(PROJECT_ASSETS "/font.png", GL_CLAMP_TO_EDGE, GL_NEAREST);
    GLuint sprite = GeomImage(image);
    ImageArray font_atlas = ImageCreateArray(PROJECT_ASSETS "/font.png", 18, 18, GL_CLAMP_TO_EDGE, GL_NEAREST);

    vec3 color = {1.0, 0.0, 0.0};
    GLuint rect = GeomRect(50, 50);

    /* Loop until the user closes the window */
    while (WindowActive()) {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        // DrawRect(rect, 0, 0, color);
        DrawText(console, font_atlas, rows * cols);
        // DrawImage(sprite, image, 0, 0);

        /* Swap front and back buffers */
        WindowSwap();

        /* Poll for and process events */
        WindowPollEvents();
    }

    ConsoleDestroy();

    WindowClose();

    return 0;
}