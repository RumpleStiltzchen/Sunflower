#include "raylib.h"
#include "Utils.cpp"
#include "math.h"
#include <iostream>
#include <vector>
#include "shaders.h"
#define GLSL_VERSION 330
#define TWO_PI 6.2831855
#define PI 3.141592
using std::vector;

int main(int argc,  char** argv)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_WINDOW_UNDECORATED | FLAG_VSYNC_HINT); 
    
    int width = 1920;
    int height = 1080;

    float angle = 137;
    
    InitWindow(width, height, "Sunflower - Russell");
    int display = GetCurrentMonitor();
    SetWindowSize(GetMonitorWidth(display), GetMonitorHeight(display));
    width = GetMonitorWidth(display);
    height = GetMonitorHeight(display);
    ToggleFullscreen();
    int delay = 3;
    int colorOffset = 360 * 10;
    int n = 0;
    int c = (int)((height/75) * 0.75);
    

    Shader shader = LoadShaderFromMemory(0, fragmentShaderCode);
    RenderTexture2D target = LoadRenderTexture(width, height);
    RenderTexture2D prev = LoadRenderTexture(width, height);

    SetTextureFilter(target.texture, TEXTURE_FILTER_POINT);
    BlendMode(BLEND_ALPHA);
    SetTargetFPS(144);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------
    
    BeginDrawing();
    ClearBackground(BLACK);
    EndDrawing();
    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------
        if(n < 4000)
            n+=2;
        if(delay > 0)
            delay--;
        else
        {
            delay = 3;    
            colorOffset -= 1;
        }
        if(colorOffset < 0)
            colorOffset = 360 * 10;
        // Draw
        //----------------------------------------------------------------------------------
        BeginTextureMode(prev);
            BeginShaderMode(shader);
                DrawTextureRec(target.texture, (Rectangle){ 0, 0, (float)target.texture.width, (float)-target.texture.height }, (Vector2){ 0, 0 }, WHITE);
            EndShaderMode();
        EndTextureMode();

        //clear Target

        BeginTextureMode(target);
            //ClearBackground(BLANK);
            BeginShaderMode(shader);
                DrawTextureRec(prev.texture, (Rectangle){ 0, 0, (float)target.texture.width, (float)-target.texture.height }, (Vector2){ 0, 0 }, WHITE);
            EndShaderMode();
            for(int i = 0; i < n; i++)
                {
                    float theta = i * angle;
                    float r = (c) * std::sqrt(i);
                    Color lineColor = ColorFromHSV(colorOffset + i , 1, 1);
                    DrawCircle(r * cos(theta * PI/180) + width/2,r * sin(theta * PI/180) + height/2, 5, lineColor);
                }
            angle+= 0.0001;

            
        EndTextureMode();
        

        BeginDrawing();
            ClearBackground(BLACK);
            
            DrawTextureRec(target.texture, (Rectangle){ 0, 0, (float)target.texture.width, (float)-target.texture.height }, (Vector2){ 0, 0 }, WHITE);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }
    
    // De-Initialization
            // Unload shader
    UnloadRenderTexture(target);
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}


