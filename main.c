#include "raylib.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

const int SCR_W = 1000;
const int SCR_H = SCR_W;
const char *SCR_TITLE = "Visualization";
const int FPS = 60;

const double MAX_SWEEP = 1.412; // Square root of 2
const double MAX_SIZE = ((double)SCR_W / 2) / MAX_SWEEP;
const int BORDER = 20;
const int SIZE = ((int)MAX_SIZE) - (2 * BORDER);
const double SPEED = 1.5;

const int CX = SCR_W / 2;
const int CY = SCR_H / 2;

void DrawDotM(int x, int y) {
	DrawCircle(x, y, 10, WHITE);
}

void mainloop(void) {
	int frames = 0;
	int phase = 1;
	while (frames++, !WindowShouldClose()) {
		double time = ((double)(frames) / FPS) * SPEED;
		double x = cos(time);
		double y = sin(time);
		int xp = CX + (x * SIZE);
		int yp = CY + (y * SIZE);
		double dx = cos(time + (M_PI / 2));
		double dy = sin(time + (M_PI / 2));
		int dxp = xp + (dx * SIZE);
		int dyp = yp + (dy * SIZE);
		if (IsKeyDown(KEY_ONE)) phase = 1;
		if (IsKeyDown(KEY_TWO)) phase = 2;
		if (IsKeyDown(KEY_THREE)) phase = 3;
		if (IsKeyDown(KEY_FOUR)) phase = 4;
		BeginDrawing();
			ClearBackground(BLACK);
			DrawLine(CX, CY, CX, yp, BLUE);
			if (phase != 4) {
				DrawLine(CX, yp, xp, yp, RED);
				DrawLine(CX, CY, xp, yp, PURPLE);
			}
			if (phase >= 3) {
				DrawLine(xp, yp, xp, dyp, RED);
				if (phase != 4) {
					DrawLine(xp, dyp, dxp, dyp, BLUE);
				}
			}
			if (phase >= 2 && phase != 4) {
				DrawLine(xp, yp, dxp, dyp, PURPLE);
			}
			DrawDotM(CX, CY);
			DrawDotM(xp, yp);
		EndDrawing();
	}
}

int main(void) {
	InitWindow(SCR_W, SCR_H, SCR_TITLE);
	SetTargetFPS(FPS);
	mainloop();
	CloseWindow();
	return 0;
}

