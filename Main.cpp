//#include "SDL.h"
//
//int main(int args, char *argv[])
//{
//	SDL_Init(SDL_INIT_EVERYTHING);
//	SDL_Window *window = SDL_CreateWindow("Title", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 400, SDL_WINDOW_SHOWN);
//	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
//
//	SDL_SetRenderDrawColor(renderer, 0,255,0,255);
//
//	SDL_RenderClear(renderer);
//	SDL_RenderPresent(renderer);
//
//	SDL_Delay(3000);
//
//	return 0;
//}

#include <SDL.h>
#include <iostream>
#include <cmath>
#include <complex>

int main(int argc, char* argv[]) //Arguments required by SDL
{
	enum {Width = 1200, Height = 720};

	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		std::cerr << "SDL_Init(SDL_INIT_VIDEO)\n";
		return -1;
	}

	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_CreateWindowAndRenderer(Width, Height, SDL_WINDOW_OPENGL | SDL_WINDOW_BORDERLESS, &window, &renderer);
	SDL_SetWindowPosition(window, 65, 126);

	enum {PaletteSize = 32};
	int palette[PaletteSize + 1][3]; //Values RGB

	for (int i = 0; i <= PaletteSize; ++i)
	{
		palette[i][0] = i < 2 * PaletteSize / 3   ?   i * 255 * 3 / (2 * PaletteSize)   :  0;
		palette[i][1] = i < PaletteSize / 3       ?   0                                 :  (i - PaletteSize / 3) * 255 * 3 / (2 * PaletteSize);
		palette[i][2] = i < 2 * PaletteSize / 3   ?   0                                 :  (i - 2 * PaletteSize / 3) * 255 / (PaletteSize / 3);
	}

	for (int y = 0; y < Height; ++y)
		for (int x = 0; x < Width; ++x)
		{
			//std::complex<double> c(0.5 * x / Height * 4.0 - 2.0, 0.5 * y / Height * 4.0 - 2.0); //Left-Aligned zoomed X2
			std::complex<double> c(1.0 * (x - (Width - Height)/ 2)/ Height * 4.0 - 2.0 , 1.0 * y / Height * 4.0 - 2.0); //Centered
			std::complex<double> z(0.0, 0.0);

			int cnt = 0;
			while (cnt < PaletteSize)
			{
				z = z * z + c;
				if (abs(z) > 2.0)
					break;

				++cnt;
			}

			SDL_SetRenderDrawColor(renderer, palette[cnt][0], palette[cnt][1], palette[cnt][2], 0xFF);
			//SDL_SetRenderDrawColor(renderer, cnt, cnt, cnt, 0xFF);
			SDL_RenderDrawPoint(renderer, x, y);

		}

	SDL_RenderPresent(renderer);

	do{
		//spin wheels


	} while (std::cin.get() != 'q');
		
	//Cleanup
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	SDL_Quit();

	return 0;
}