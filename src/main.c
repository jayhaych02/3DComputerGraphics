#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

#include "display.h"
#include "vector.h"

//Declare array of vectors/points
#define N_POINTS (9*9*9)
vec3_t cube_points[N_POINTS];
vec2_t projected_points[N_POINTS];

vec3_t camera_pos = {0,0,-5};

float fov_factor = 640;//play w/ number, so far this is a magic number
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

//Receives 3D Vector --> Returns projected 2D Point
vec2_t project(vec3_t point){
	vec2_t projected_point = { (fov_factor*point.x)/point.z , (fov_factor * point.y)/point.z};
	return projected_point;	
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
					cube_points[point_count++] = new_point;//every pt is vector3 so place pt --> move next index to place again
				}
			}
		}

}

void update(void){
	for(int i=0;i<N_POINTS;i++){//ignores z component and returns x&y of cube
		vec3_t point = cube_points[i];//each index i = Vector3 
		//move the pts away from the camera
		point.z-=camera_pos.z;
		vec2_t projected_point = project(point);
		projected_points[i] = projected_point;
	}
}

void render(void){
	draw_grid();
	
	for(int i=0;i<N_POINTS;i++){
		vec2_t projected_point = projected_points[i];
		draw_rect(
		projected_point.x +(window_width/2),// push pts to center of window
		projected_point.y + (window_height/2),
		4,
		4,
		0xFFFFFF00
		);
	}

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
