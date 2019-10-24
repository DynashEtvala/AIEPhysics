/*******************************************************************************************
*
*   raylib [core] example - basic window
*
*   This example has been created using raylib 1.0 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2013-2016 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "Global.h"
#include "HelperMain.h"

#include "MaterialIncludes.h"
#include "MatManager.h"
int main()
{
	// Initialization
	//--------------------------------------------------------------------------------------
	int screenWidth = 800;
	int screenHeight = screenWidth + 100;
	int playHeight = screenWidth; 
	int brushSize = 10;

	int speed = 0;
	int frameCount = 0;

	Point lastMouse{ 0, 0 };
	Point currMouse{ 0, 0 };

	MatType currBrush = WALL;

	GMaterial*** matList = new GMaterial**[playHeight];

	for (int i = 0; i < playHeight; i++)
	{
		matList[i] = new GMaterial*[screenWidth];
	}

	for (int i = playHeight - 1; i >= 0; i--)
	{
		for (int j = 0; j < screenWidth; j++)
		{
			if (j == 0 || j == 1 || j == screenWidth - 1 || j == screenWidth - 2)
			{
				matList[i][j] = new Wall(j, i);
				matList[i][j]->updatedFrame = true;
			}
			else
			{
				matList[i][j] = new GMaterial(j, i);
			}
		}
	}

	MatManager mMan = MatManager(playHeight, screenWidth);

	InitWindow(screenWidth, screenHeight, "Sand Game");

	HideCursor();

	SetTargetFPS(60);
	//--------------------------------------------------------------------------------------


	// Main game loop
	while (!WindowShouldClose())    // Detect window close button or ESC key
	{
		// Update
		//----------------------------------------------------------------------------------
		// TODO: Update your variables here
		//----------------------------------------------------------------------------------
		currMouse.X = GetMousePosition().x;
		currMouse.Y = GetMousePosition().y;
		
		if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
		{
			mMan.PaintCircleLine(matList, currMouse.X, currMouse.Y, lastMouse.X, lastMouse.Y, brushSize, currBrush);
		}
		else if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON))
		{
			switch (currBrush)
			{
			default:
			case AIR:
				currBrush = WALL;
				break;
			case WALL:
				currBrush = WATER;
				break;
			case WATER:
				currBrush = SAND;
				break;
			case SAND:
				currBrush = OIL;
				break;
			case OIL:
				currBrush = SALT;
				break;
			case SALT:
				currBrush = PLANT;
				break;
			case PLANT:
				currBrush = AIR;
				break;
			}
		}
		
		if (frameCount >= ExpoGrow(2, speed))
		{
			for (int i = playHeight - 1; i >= 0; i--)
			{
				for (int j = 0; j < screenWidth; j++)
				{
					matList[i][j]->Update(matList, playHeight, screenWidth, mMan);
					mMan.ExecuteChanges(matList);
				}
				mMan.ClearUpdatesLine(matList, i, screenWidth); 
				
				for (int j = screenWidth - 1; j >= 0; j--)
				{
					matList[i][j]->Update(matList, playHeight, screenWidth, mMan);
					mMan.ExecuteChanges(matList);
				}
				mMan.ClearUpdatesLine(matList, i, screenWidth);
			}
			mMan.ClearUpdatesFrame(matList, playHeight, screenWidth);
			frameCount = 0;
		}
		else
		{
			frameCount++;
		}

		lastMouse = currMouse;
		// Draw
		//----------------------------------------------------------------------------------
		BeginDrawing();

		ClearBackground(BLACK);

		DrawRectangle(0, screenHeight - 100, screenWidth, 100, GRAY);

		for (int i = 0; i < playHeight; i++)
		{
			for (int j = 0; j < screenWidth; j++)
			{
				if (matList[i][j]->type != AIR)
				{
					DrawPixel(matList[i][j]->posX, matList[i][j]->posY, matList[i][j]->color);
				}
			}
		}

		DrawPixel(currMouse.X, currMouse.Y, WHITE);

		mMan.PrintMatInfo(matList, currMouse.X, currMouse.Y);
		
		EndDrawing();
		//----------------------------------------------------------------------------------
	}

	// De-Initialization
	//--------------------------------------------------------------------------------------   
	CloseWindow();        // Close window and OpenGL context
	for (int i = 0; i < playHeight; i++)
	{
		for (int j = 0; j < screenWidth; j++)
		{
			delete matList[i][j];
		}
		delete[] matList[i];
	}
	delete[] matList;
	//--------------------------------------------------------------------------------------

	return 0;
}