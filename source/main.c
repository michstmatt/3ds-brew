// Simple citro2d untextured shape example
#include <citro2d.h>

#include <string.h>
#include <stdio.h>
#include <stdlib.h>


#define SCREEN_WIDTH  400
#define SCREEN_HEIGHT 240

typedef struct Pos
{
	float x;
	float y;
} Pos;
typedef struct Paddle
{
	int width;
	int height;
	Pos position;
} Paddle;

typedef struct Ball
{
	int radius;
	Pos position;
	Pos velocity;
} Ball;

void updateBall(Ball* ball)
{
	
}

void updateAI(Ball* ball, Paddle* aiPaddle, float paddleSpeed)
{
	if(ball->position.y < aiPaddle->position.y)
	{
		// Ball is above AI's paddle, move up
		aiPaddle->position.y -= paddleSpeed;
	}
	else if (ball->position.y > aiPaddle->position.y)
	{
		// Ball is below AI's paddle, move down
		aiPaddle->position.y += paddleSpeed;
	}
}

//---------------------------------------------------------------------------------
int main(int argc, char* argv[]) {
//---------------------------------------------------------------------------------
	// Init libs
	gfxInitDefault();
	C3D_Init(C3D_DEFAULT_CMDBUF_SIZE);
	C2D_Init(C2D_DEFAULT_MAX_OBJECTS);
	C2D_Prepare();
	consoleInit(GFX_BOTTOM, NULL);

	// Create screens
	C3D_RenderTarget* top = C2D_CreateScreenTarget(GFX_TOP, GFX_LEFT);
	/*
	PrintConsole topScreen, bottomScreen;
	consoleInit(GFX_TOP, &topScreen);
	consoleInit(GFX_BOTTOM, &bottomScreen);
	consoleSelect(&bottomScreen);*/

	// Create colors
	u32 clrWhite = C2D_Color32(0xFF, 0xFF, 0xFF, 0xFF);
	u32 clrGreen = C2D_Color32(0x00, 0xFF, 0x00, 0xFF);
	u32 clrRed   = C2D_Color32(0xFF, 0x00, 0x00, 0xFF);
	u32 clrBlue  = C2D_Color32(0x00, 0x00, 0xFF, 0xFF);

	u32 clrRec1 = C2D_Color32(0x9A, 0x6C, 0xB9, 0xFF);
	u32 clrRec2 = C2D_Color32(0xFF, 0xFF, 0x2C, 0xFF);
	u32 clrRec3 = C2D_Color32(0xD8, 0xF6, 0x0F, 0xFF);
	u32 clrRec4 = C2D_Color32(0x40, 0xEA, 0x87, 0xFF);

	u32 clrCircle1 = C2D_Color32(0xFF, 0x00, 0xFF, 0xFF);
	u32 clrCircle2 = C2D_Color32(0xFF, 0xFF, 0x00, 0xFF);
	u32 clrCircle3 = C2D_Color32(0x00, 0xFF, 0xFF, 0xFF);

	u32 clrClear = C2D_Color32(0x00, 0x00, 0x00, 0x00);

	int speed = 1;

	Paddle playerPaddle;
	playerPaddle.width = 10;
	playerPaddle.height = 50;
	playerPaddle.position.x = 25;
	playerPaddle.position.y = 0;

	Paddle aiPaddle;
	aiPaddle.width = 10;
	aiPaddle.height = 50;
	aiPaddle.position.x = SCREEN_WIDTH - 25;
	aiPaddle.position.y = 0;

	Ball ball;
	ball.radius = 10;
	ball.position.x = SCREEN_WIDTH / 2;
	ball.position.y = SCREEN_HEIGHT / 2;
	ball.velocity.x = 1;
	ball.velocity.y = 1.5;

	// Main loop
	while (aptMainLoop())
	{
		hidScanInput();

		// Respond to user input
		u32 kDown = hidKeysDown();
		u32 kHeld = hidKeysHeld();
		if (kDown & KEY_L)
			break; // break in order to return to hbmenu

		if (kHeld & KEY_UP)
			playerPaddle.position.y -= speed; // Move up
		if (kHeld & KEY_DOWN)
			playerPaddle.position.y += speed; // Move down

		printf("\x1b[1;1HSimple citro2d shapes example");
		printf("\x1b[2;1HCPU:     %6.2f%%\x1b[K", C3D_GetProcessingTime()*6.0f);
		printf("\x1b[3;1HGPU:     %6.2f%%\x1b[K", C3D_GetDrawingTime()*6.0f);
		printf("\x1b[4;1HCmdBuf:  %6.2f%%\x1b[K", C3D_GetCmdBufUsage()*100.0f);

		ball.position.x += ball.velocity.x;
		ball.position.y += ball.velocity.y;

		if (ball.position.x > SCREEN_WIDTH || ball.position.x < 0)
		{
			// Game over
			printf("GAME OVER\n");
			break;
		}
		
		if (ball.position.y > SCREEN_HEIGHT || ball.position.y < 0)
			ball.velocity.y = 0 - ball.velocity.y;


		// Update AI

		updateAI(&ball, &aiPaddle, speed);

		// Render the scene
		C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
		C2D_TargetClear(top, clrClear);
		C2D_SceneBegin(top);

		C2D_DrawRectangle(playerPaddle.position.x, playerPaddle.position.y, 0, playerPaddle.width, playerPaddle.height, clrRec1, clrRec2, clrRec3, clrRec4);
		C2D_DrawRectangle(aiPaddle.position.x, aiPaddle.position.y, 0, aiPaddle.width, aiPaddle.height, clrRec1, clrRec2, clrRec3, clrRec4);
		C2D_DrawCircle(ball.position.x, ball.position.y, 0, ball.radius, clrCircle3, clrWhite, clrCircle1, clrCircle2);

		C3D_FrameEnd(0);
	}

	// Deinit libs
	C2D_Fini();
	C3D_Fini();
	gfxExit();
	return 0;
}
