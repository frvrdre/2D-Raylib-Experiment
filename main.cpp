
#include "raylib.h"

int main()
{
    constexpr int windowWidth{ 800 };
    constexpr int windowHeight{ 600 };

    InitWindow(windowWidth, windowHeight, "Grapple Along");
    SetTargetFPS(60);

    int score{ 0 };
    float obstacleX{ static_cast<float>(GetRandomValue(20, 780)) };
    float blockX{ static_cast<float>(GetRandomValue(20, 780)) };

    struct Player
    {
        float x{ 400.0f };
        float y{ 500.0f };
        float speed{ 400.0f };

        float velocityY{ 0.0f };
        float gravity{ 900.0f };
        float jumpStrength{ 260.0f };

        bool isGrounded{ true };
    };

    struct Boundary
    {
        float leftWall{ 0.0f };
        float rightWall{ 760.0f };
        float groundY{ 500.0f };
    };

    Player player{};
    Boundary wall{};

    while (!WindowShouldClose())
    {
        const float deltaTime{ GetFrameTime() };

        if (IsKeyPressed(KEY_SPACE) && player.isGrounded)
        {
            player.velocityY = -player.jumpStrength;
            player.isGrounded = false;
        }

        player.velocityY += player.gravity * deltaTime;
        player.y += player.velocityY * deltaTime;

        if (IsKeyDown(KEY_A))
        { 
            player.x -= player.speed * deltaTime;
        }

        if (IsKeyDown(KEY_D))
        {
            player.x += player.speed * deltaTime;
        }

        // Resolve ground collision
        if (player.y >= wall.groundY)
        {
            player.y = wall.groundY;
            player.velocityY = 0.0f;
            player.isGrounded = true;
        }

        // Keep player within screen boundaries
        if (player.x < wall.leftWall)
        {
            player.x = wall.leftWall;
        }

        if (player.x > wall.rightWall)
        {
            player.x = wall.rightWall;
        }

        Rectangle playerRect{
            player.x,
            player.y - 40.0f,
            40.0f,
            40.0f
        };

        Vector2 obstacleCenter{ obstacleX, 450.0f };

        if (CheckCollisionCircleRec(obstacleCenter, 20.0f, playerRect))
        {
            obstacleX = static_cast<float>(GetRandomValue(20, 780));
            score++;
        }
        // grabs the middle of the player for the grapple
        Vector2 playerPosition{
            player.x + 20.0f,
            player.y - 20.0f
        };

        Vector2 mousePosition{ GetMousePosition() };

        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawLine(0, 500, 800, 500, DARKGRAY);

        DrawCircle(
            static_cast<int>(obstacleX),
            450,
            20,
            GREEN
        );

        DrawCircle(
            static_cast<int>(blockX),
            250,
            20,
            GREEN
        );

        // grapple draw

        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
        {
            DrawLineV(playerPosition, mousePosition, BLACK);
        }
 

        DrawRectangleRec(playerRect, BLUE);

        DrawText(TextFormat("Score: %d", score), 10, 10, 20, BLACK);
        DrawText("A/D: Move | SPACE: Jump | Hold LMB: Grapple",
            10, 40, 18, DARKGRAY);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
