#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

#include "display.h"
#include "vector.h"

//Declare array of vectors/points
#define N_POINTS (9*9*9)
vec3_t cube_points[N_POINTS];


bool is_running = false;

void processInput(void){
	//Record Keyboard Stream Input
	SDL_Event event;
	SDL_PollEvent(&event);// seems like scanf - My own interpretation
	switch(event.type){
		case SDL_QUIT://"X" button to close a window
			is_running = false;
			break;
		case SDL_KEYDOWN:// "ESC" button on keyboard to close something
			if(event.key.keysym.sym == SDLK_ESCAPE){
				is_running = false;
				break;
			}
	}

}

vec2_t project(vec3_t point){
	
}

void setup(void){
	//Allocate the required memory in bytes to hold the color buffer
	color_buffer = (uint32_t*) malloc(sizeof(uint32_t)* window_width * window_height);
	if(color_buffer == NULL){
		fprintf(stderr,"Memory Allocation Failed! Exiting...");
		exit(1);
	}
	//Creating SDL texture that is used to display the color buffer
	color_buffer_texture = SDL_CreateTexture(
			renderer,
			SDL_PIXELFORMAT_ARGB8888,
			SDL_TEXTUREACCESS_STREAMING,
			window_width,
			window_height
		);

		//Startiloading my array of vectors --> From -1 to 1 (in this 9x9x9 cube)
		int point_count = 0;
		for(float x=-1; x<=1; x+=0.25){
			for(float y=-1; y<=1; y+=0.25){
				for(float z=-1; z<=1; z+=0.25){
					vec3_t new_point = {.x=x,.y=y,.z=z};//ref struct
					cube_points[point_count++] = new_point;
				}
			}
		}

}

void update(void){

}

void render(void){
	//All Colors & Alpha are from: 0-255 R,G,B,Alpha 255 = OPAQUE
	SDL_SetRenderDrawColor(renderer,255,0,0,255);
	SDL_RenderClear(renderer);
	
	draw_grid();
	draw_pixel(20,20,0xFFFFFF00);
	draw_rect(100,100,300,150,0xFFFFFFFF);

	render_color_buffer();
	clear_color_buffer(0xFF000000);

	SDL_RenderPresent(renderer);
}

int main(void){
	is_running = initialize_window();
	setup();

	while(is_running){
	 processInput();
	 update();
	 render();
	}

	destroy_window();




   return 0;
}
