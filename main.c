/*
 * main.c
 *
 *  Created on: Apr 29, 2015
 *      Author: nasm
 */
#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>

typedef enum {false, true} bool;

#define WIDTH 600
#define HEIGHT 600

#define X 0
#define Y 1

typedef struct{
	int x;
	int y;
	int width;
	int height;
}SQUARE,*P_SQUARE;


#define MAX_SQUARE 9

void apply_form(P_SQUARE square, P_SQUARE squares);

void transform(bool* pattern, P_SQUARE square, int iteration);

void draw_square(P_SQUARE square);

SDL_Window * init_display();

SDL_Window* window;

SDL_Renderer*  renderer;

int main()
{
	window = init_display();

	renderer = SDL_CreateRenderer(window, 0, SDL_RENDERER_ACCELERATED);

	SDL_SetRenderDrawColor( renderer, 255, 0, 0, 255 );

	SDL_RenderClear( renderer );

	bool pattern[MAX_SQUARE] = {false};
	pattern[4] = true;
	pattern[7] = true;
	pattern[0] = true;
	pattern[2] = true;

	SQUARE square;

	square.x = 0;
	square.y = 0;

	square.height = WIDTH;
	square.width = HEIGHT;

	transform(pattern,&square,5);

	SDL_Delay( 5000 );

	SDL_DestroyWindow(window);
	SDL_Quit();

	return true;
}

void transform(bool* pattern, P_SQUARE square, int iteration)
{
	if(iteration <= 0 )
		return;
	else
	{
		int i = 0;

		SQUARE squares[MAX_SQUARE];
		apply_form(square,squares);

		for(i=0; i<MAX_SQUARE; i++)
		{
			if(pattern[i] == true)
				draw_square(&squares[i]);
			else
				transform(pattern,&squares[i],iteration-1);
		}
	}
}

void apply_form(P_SQUARE square, P_SQUARE squares)
{
	int k;
	int w=square->width/3, h=square->height/3;
	for(k=0; k<MAX_SQUARE; k++)
	{
		int i=k/3, j=k%3;
		squares[k].x = w * j + square->x;
		squares[k].y = h * i + square->y;

		squares[k].width = w;
		squares[k].height = h;
	}
}

void draw_square(P_SQUARE square)
{
	SDL_Rect rect;
	rect.x = square->x;
	rect.y = square->y;
	rect.h = square->height;
	rect.w = square->width;

	// Set render color to blue ( rect will be rendered in this color )
	SDL_SetRenderDrawColor( renderer, 0, 0, 255, 255 );

	// Render rect
	SDL_RenderFillRect( renderer, &rect );

	// Render the rect to the screen
	SDL_RenderPresent(renderer);
}

SDL_Window * init_display()
{
	//Start up SDL and make sure it went ok
	if (SDL_Init(SDL_INIT_VIDEO) != 0){
		return NULL;
	}

	//Setup our window and renderer
	SDL_Window *window = SDL_CreateWindow("Fractal", 100, 100, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
	if (window == NULL){
		SDL_Quit();
		return NULL;
	}

	return window;
}
