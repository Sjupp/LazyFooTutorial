#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>

#include <string>
#include <sstream>
#include <map>

#include "Ltexture.h"
#include "KeyboardHandler.h"
#include "LTimer.h"
#include "Dot.h"
#include "constants.h"
#include "PuzzlePiece.h"
#include "PuzzleGrid.h"

// consts
extern constexpr int kScreenFps{ 60 };

// function prototypes
bool init();
bool loadMedia();
void close();

// global vars
SDL_Window* gWindow{ nullptr };
SDL_Renderer* gRenderer{ nullptr };
KeyboardHandler* gKeyboardHandler{ nullptr };

//LTexture gPngTexture;
LTexture gSheetTexture;
LTexture gBoxTexture;

TTF_Font* gFont{ nullptr };
LTexture gTextTexture;

bool init()
{
	bool success{ true };

	if (!SDL_Init(SDL_INIT_VIDEO))
	{
		SDL_Log("SDL could not initialize! SDL error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		if (!SDL_CreateWindowAndRenderer("Title", ScreenDimensions::kScreenWidth, ScreenDimensions::kScreenHeight, 0, &gWindow, &gRenderer))
		{
			SDL_Log("Window could not be created! SDL error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			if (!SDL_SetRenderVSync(gRenderer, 1))
			{
				SDL_Log("Could not enable VSync!");
				success = false;
			}

			if (!TTF_Init())
			{
				SDL_Log("Could not initialize SDL_ttf");
			}
		}
	}

	return success;
}

bool loadMedia()
{
	bool success{ true };

	//success = gPngTexture.loadFromFile(gRenderer, "dot.png", true);
	success = gSheetTexture.loadFromFile(gRenderer, "dots.png", true);
	success = gBoxTexture.loadFromFile(gRenderer, "PuzzleSquare16.png", true);

	std::string fontPath = "assets/lazy.ttf";
	gFont = TTF_OpenFont(fontPath.c_str(), 28);
	if (gFont == nullptr)
	{
		SDL_Log("Could not load font via path: %s", fontPath.c_str());
		success = false;
	}
	else
	{
		SDL_Color textColor = { 0x00, 0x00, 0x00, 0xFF };
		if (!gTextTexture.loadFromRenderedText(gRenderer, gFont, "Hello World", textColor))
		{
			SDL_Log("Could not load text texture!");
			success = false;
		}
	}

	return success;
}

void close()
{
	//gPngTexture.destroy();
	gSheetTexture.destroy();
	gTextTexture.destroy();
	gBoxTexture.destroy();

	TTF_CloseFont(gFont);
	gFont = nullptr;

	SDL_DestroyRenderer(gRenderer);
	gRenderer = nullptr;
	SDL_DestroyWindow(gWindow);
	gWindow = nullptr;

	TTF_Quit();
	SDL_Quit();
}

int main(int argc, char* argv[]) {

	int exitCode{ 0 };

	if (!init())
	{
		SDL_Log("Unable to initialize program!");
		exitCode = 1;
	}
	else
	{
		if (!loadMedia())
		{
			SDL_Log("Unable to load media!");
			exitCode = 2;
		}
		else
		{
			bool quit{ false };

			SDL_Event e;
			SDL_zero(e);

			KeyboardHandler keyHandler;
			LTimer timer;

			bool vSyncEnabled{ true };
			bool fpsCapEnabled{ true };
			LTimer fpsTimer;
			LTimer capTimer;
			Uint64 renderedFrames = 0;
			Uint64 renderingNS = 0;
			bool resetFps = true;
			std::stringstream timeText;
			
			//double degrees = 0.0;
			//Dot dot(gPngTexture.getWidth(), gPngTexture.getHeight());

			PuzzlePiece puzzlePiece;
			PuzzleGrid puzzleGrid;

			puzzleGrid.tryAddPuzzlePieceToGrid(&puzzlePiece, 5, 5);

			while (quit == false)
			{
				if (resetFps)
				{
					fpsTimer.start();
					renderedFrames = 0;
					renderingNS = 0;
					resetFps = false;
				}
				capTimer.start();

				keyHandler.update();
				while (SDL_PollEvent(&e))
				{
					if (e.type == SDL_EVENT_QUIT)
					{
						quit = true;
					}

					switch (e.type)
					{
					case SDL_EVENT_KEY_DOWN:
					case SDL_EVENT_KEY_UP:
						keyHandler.handleKeyboardEvent(e);
						break;
					default:
						break;
					}

					//dot.handleEvent(e);
				}
				if (keyHandler.isPressedThisFrame(SDLK_SPACE))
				{
					puzzlePiece.rotateClockwise();
				}
				if (keyHandler.isPressedThisFrame(SDLK_1))
				{
					vSyncEnabled = !vSyncEnabled;
					SDL_SetRenderVSync(gRenderer, vSyncEnabled);
					resetFps = true;
				}
				if (keyHandler.isPressedThisFrame(SDLK_2))
				{
					fpsCapEnabled = !fpsCapEnabled;
					resetFps = true;
				}
				if (keyHandler.isPressedThisFrame(SDLK_LEFT))
				{
					auto coords = puzzlePiece.getCoordinates();
					puzzleGrid.tryMovePuzzlePieceToGridPosition(&puzzlePiece, coords.first - 1, coords.second);
				}
				if (keyHandler.isPressedThisFrame(SDLK_LEFT))
				{
					auto coords = puzzlePiece.getCoordinates();
					puzzleGrid.tryMovePuzzlePieceToGridPosition(&puzzlePiece, coords.first + 1, coords.second);
				}

				//dot.move();
				timeText.str("");
				timeText << "Frames per second "
					<< (vSyncEnabled ? "VSYNC " : "")
					<< (fpsCapEnabled ? "CAP" : "")
					<< static_cast<double>(renderedFrames) / (static_cast<double>(renderingNS) / 1000000000.0);

				SDL_Color textColor = { 0x00, 0x00, 0x00, 0xFF };
				gTextTexture.loadFromRenderedText(gRenderer, gFont, timeText.str().c_str(), textColor);

				// ------------------- Render Begin -------------------
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(gRenderer);

				//dot.handleEvent()
				//dot.render(gRenderer, &gPngTexture);
				//degrees += 0.1;
				//gPngTexture.render(gRenderer, 0.f, 0.f, nullptr, LTexture::kOriginalSize, LTexture::kOriginalSize, degrees, nullptr, SDL_FLIP_NONE);
				
				gTextTexture.render(gRenderer, (ScreenDimensions::kScreenWidth - gTextTexture.getWidth()) / 2.f, (ScreenDimensions::kScreenHeight - gTextTexture.getHeight())/ 2.f);
				
				puzzleGrid.render(gRenderer, &gBoxTexture);


				SDL_RenderPresent(gRenderer);
				// ------------------- Render End -------------------


				renderingNS = fpsTimer.getTicksNS();
				renderedFrames++;
				
				Uint64 frameNs = capTimer.getTicksNS();
				constexpr Uint64 nsPerFrame = 1000000000 / kScreenFps;
				if (fpsCapEnabled && frameNs < nsPerFrame)
				{
					SDL_DelayNS(nsPerFrame - frameNs);
				}
			}
		}
	}

	close();

	return exitCode;
}