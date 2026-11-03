#include "raylib.h"
#include <cmath>
int main()
{
    InitWindow(800, 600, "Jump Lab");
    SetTargetFPS(60);

    int score{ 0 };
    int randomNumber{ GetRandomValue(1, 800) };
    float obstacleX{ static_cast<float>(randomNumber) };

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
		int leftWall{ 0 };
		int rightWall{ 760 };
		float groundY{ 500.0f };
	};

    Boundary wall;
    Player Player;



    while (!WindowShouldClose())
    {
        float deltaTime{ GetFrameTime() };

        if (IsKeyPressed(KEY_SPACE) && Player.isGrounded)
        {
            Player.velocityY = -Player.jumpStrength;
            Player.isGrounded = false;
        }

		Player.velocityY = Player.velocityY + Player.gravity * deltaTime;
        Player.y += Player.velocityY * deltaTime;

        if (IsKeyDown(KEY_A)) {
            Player.x -= Player.speed * deltaTime;
        }
        if (IsKeyDown(KEY_D)) {
            Player.x += Player.speed * deltaTime;
        }

  

        Vector2 obstacleCenter{ obstacleX, 450.0f };

        if (CheckCollisionCircleRec(obstacleCenter, 20.0f, PlayerRect))
        {
            obstacleX = static_cast<float>(GetRandomValue(20, 780));
            score++;
        }

        // Resolve ground collision
        if (Player.y >= wall.groundY)
        {
            Player.y = wall.groundY;
            Player.velocityY = 0.0f;
            Player.isGrounded = true;
        }

       
        Rectangle PlayerRect{
            Player.x,
            Player.y - 40.0f,
            40.0f,
            40.0f
        };

        if (Player.x <= wall.leftWall)
        {
            Player.x = wall.leftWall;
        }

        if (Player.x >= wall.rightWall)
        {
            Player.x = wall.rightWall;
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawRectangle(
            static_cast<int>(Player.x),
            static_cast<int>(Player.y - 40),
            40, 40, BLUE
        );
        DrawCircle(
            static_cast<int>(obstacleX),
            static_cast<int>(450.0f),
            20, GREEN
        );

        DrawLine(0, 500, 800, 500, DARKGRAY);

        DrawText(TextFormat("Score: %d", score), 10, 10, 20, BLACK);


        EndDrawing();
    }

    CloseWindow();
    return 0;
}
