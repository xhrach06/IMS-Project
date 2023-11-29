#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>

const int SCREEN_WIDTH = 939;
const int SCREEN_HEIGHT = 533;
const int GRID_SIZE_X = 939; // Number of squares in each row and column
const int GRID_SIZE_Y = 553;
const int SQUARE_SIZE = 1;

SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;

bool init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL initialization failed: " << SDL_GetError() << std::endl;
        return false;
    }

    if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG) {
        std::cerr << "SDL_image initialization failed: " << IMG_GetError() << std::endl;
        return false;
    }

    window = SDL_CreateWindow("Grid UI Example", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        std::cerr << "Window creation failed: " << SDL_GetError() << std::endl;
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        std::cerr << "Renderer creation failed: " << SDL_GetError() << std::endl;
        return false;
    }

    return true;
}

void close() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
}

std::vector<std::vector<SDL_Color>> getPixelColors(const std::string& imagePath) {
    SDL_Surface* surface = IMG_Load(imagePath.c_str());
    if (surface == nullptr) {
        std::cerr << "Failed to load image: " << IMG_GetError() << std::endl;
        return {};
    }

    std::vector<std::vector<SDL_Color>> pixelColors(surface->w, std::vector<SDL_Color>(surface->h));

    for (int x = 0; x < surface->w; ++x) {
        for (int y = 0; y < surface->h; ++y) {
            Uint32 pixel = static_cast<Uint32*>(surface->pixels)[y * surface->w + x];
            SDL_Color color;
            SDL_GetRGB(pixel, surface->format, &color.r, &color.g, &color.b);
            pixelColors[x][y] = color;
        }
    }

    SDL_FreeSurface(surface);
    return pixelColors;
}

void drawGridInitial(const std::vector<std::vector<SDL_Color>>& pixelColors) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Set background color to white
    SDL_RenderClear(renderer);

    for (int x = 0; x < GRID_SIZE_X; ++x) {
        for (int y = 0; y < GRID_SIZE_Y; ++y) {
            SDL_Color pixelColor = pixelColors[x][y];

            if (pixelColor.r == 34 && pixelColor.g == 177 && pixelColor.b == 76) {
                // If the color is #22B14C (RGB values)
                SDL_SetRenderDrawColor(renderer, 34, 177, 76, 255); // Green
            } else if (pixelColor.r == 153 && pixelColor.g == 217 && pixelColor.b == 234) {
                // If the color is #99D9EA (RGB values)
                SDL_SetRenderDrawColor(renderer, 153, 217, 234, 255); // Light blue
            } else if (pixelColor.r == 0 && pixelColor.g == 0 && pixelColor.b == 0) {
                // If the color is black
                // Store the pixel value in an array or perform other actions
                // For simplicity, we'll print the pixel values here

                // Set the grid color to black
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            } else {
                // Default color
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            }

            SDL_Rect squareRect = {x * SQUARE_SIZE, y * SQUARE_SIZE, SQUARE_SIZE, SQUARE_SIZE};
            SDL_RenderFillRect(renderer, &squareRect);
        }
    }

    SDL_RenderPresent(renderer);
}

int main(int argc, char* args[]) {
    if (!init()) {
        std::cerr << "Initialization failed." << std::endl;
        return -1;
    }

    // Path to your image file
    std::string imagePath = "after.png";
    
    // Get pixel colors from the image
    std::vector<std::vector<SDL_Color>> pixelColors = getPixelColors(imagePath);

    bool quit = false;
    SDL_Event e;

    drawGridInitial(pixelColors);

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }
    }

    close();
    return 0;
}
