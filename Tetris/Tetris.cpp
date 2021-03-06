// Tetris.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <Windows.h>
using namespace std;

wstring tetromino[7];
int nFieldWidth = 12;
int nFieldHeight = 18;
unsigned char *pField = nullptr;

int nScreenWidth = 80;		// Console Screen size x (col)
int nScreenHeight = 30;		// Console Screen size y (rows)

int Rotate(int px, int py, int r) {

	switch (r % 4)
	{
	case 0:
		return py * 4 + px;			// 0 degrees
		break;
	case 1:
		return 12 - (px * 4) + py;	// 90 degrees
		break;
	case 2:
		return 15 - (py * 4) - px;	// 180 degrees
		break;
	case 3:
		return 3 - py + (px * 4);	//270 degrees
		break;
	}
	return 0;
}

bool DoesPieceFit(int nTetromino, int nRotation, int nPosX, int nPosY) {

	for (int px = 0; px < 4; px++) {

		for (int py = 0; py < 4; py++) {

			// Get the index into piece
			// This is referring to the index in the 4x4 tetrominos that were created in main
			int pi = Rotate(px, py, nRotation);

			// Get index into field
			int fi = (nPosY + py) * nFieldWidth + (nPosX + px);

			if (nPosX + px >= 0 && nPosX + px < nFieldWidth) {
				if (nPosY + py >= 0 && nPosY + py < nFieldHeight) {
					if (tetromino[nTetromino][pi] == L'X' && pField[fi] != 0) {
						return false; // Fails on the first hit
					}
				}
			}
		}
	}

	// Default because anything else will return false
	return true;
}

int main() {
	// Create assets
	tetromino[0].append(L"..X.");
	tetromino[0].append(L"..X.");
	tetromino[0].append(L"..X.");
	tetromino[0].append(L"..X.");

	tetromino[1].append(L"..X.");
	tetromino[1].append(L".XX.");
	tetromino[1].append(L".X..");
	tetromino[1].append(L"....");

	tetromino[2].append(L".X..");
	tetromino[2].append(L".XX.");
	tetromino[2].append(L"..X.");
	tetromino[2].append(L"....");

	tetromino[3].append(L"....");
	tetromino[3].append(L".XX.");
	tetromino[3].append(L".XX.");
	tetromino[3].append(L"....");

	tetromino[4].append(L"..X.");
	tetromino[4].append(L".XX.");
	tetromino[4].append(L"..X.");
	tetromino[4].append(L"....");

	tetromino[5].append(L"....");
	tetromino[5].append(L".XX.");
	tetromino[5].append(L"..X.");
	tetromino[5].append(L"..X.");

	tetromino[6].append(L"....");
	tetromino[6].append(L".XX.");
	tetromino[6].append(L".X..");
	tetromino[6].append(L".X.");

	// Create the screen buffer
	pField = new unsigned char[nFieldWidth*nFieldHeight];
	// Create the boundaries
	for (int x = 0; x < nFieldWidth; x++) {
		for (int y = 0; y < nFieldHeight; y++) {
			pField[y*nFieldHeight + x] = (x == 0 || x == nFieldHeight - 1 || y == nFieldHeight) ? 9 : 0;
		}

	}

	// Creating the character array map (though, not sure about the syntax behind this code. Some use 'wchar_t (*screen) = new wchar_t[.....];' is there a difference, and why not just have a single/double pointer to the array?
	// Possibly ask professor if this is declaring a pointer to a dynamically sized array. (VLA)?
	wchar_t *screen = new wchar_t[nScreenWidth*nScreenHeight];
	for (int i = 0; i < nScreenWidth*nScreenHeight; i++)
	{
		screen[i] = L' ';
	}
	HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleActiveScreenBuffer(hConsole);
	DWORD dwBytesWritten = 0;

	// Game loop
	int nCurrentPiece = 0;
	int nCurrentRotation = 0;
	int nCurrentX = nFieldWidth / 2;
	int nCurrentY = 0;

	bool gameOver = false;
	while (!gameOver) {

		// Game timing		---------------------------

		// Input			---------------------------

		// Game Logic		---------------------------

		// Render Output	---------------------------

		// Draw the field
		for (int x = 0; x < nFieldWidth; x++) {
			for (int y = 0; y < nFieldHeight; y++) {
				screen[(y + 2)*nScreenWidth + (x + 2)] = L" ABCDEFG=#"[pField[y*nFieldWidth + x]];
			}

		}

		for (int px = 0; px < 4; px++) {
			for (int py = 0; py < 4; py++) {
				if (tetromino[nCurrentPiece][Rotate(px, py, nCurrentRotation)] == L'X') {
					screen[(nCurrentY + py + 2) * nScreenWidth + (nCurrentX + px + 2)] = nCurrentPiece + 65;
				}
			}
		}

		// Display the frame
		WriteConsoleOutputCharacter(hConsole, screen, nScreenWidth * nScreenHeight, { 0, 0 }, &dwBytesWritten);

	}

	return 0;
}