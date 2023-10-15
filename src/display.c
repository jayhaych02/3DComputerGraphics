#include "display.h"

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
SDL_Texture* color_buffer_texture = NULL;
uint32_t* color_buffer = NULL;
int window_width = 800;
int window_height = 600;

bool initialize_window(void){
 if(SDL_Init(SDL_INIT_EVERYTHING) != 0 ){
 	fprintf(stderr,"Error initializing SDL.\n");
	return false;		
 }
	//Query SDL --> Full Screen Max Width & Height of current Monitor?
	SDL_DisplayMode display_mode;//struct
	SDL_GetCurrentDisplayMode(0,&display_mode);// index 0 = main monitor
	
	window_width = display_mode.w;
	window_height = display_mode.h;

 	//Create SDL Window
	window = SDL_CreateWindow(
			NULL,
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			window_width,
			window_height,
			SDL_WINDOW_BORDERLESS
			);
	if(!window){
	 fprintf(stderr,"Error creating SDL window.\n");
	 return false;
	}

	// Create SDL Renderer
	renderer = SDL_CreateRenderer(window,-1,0);
	if(!renderer){
	 fprintf(stderr,"Error creating SDL Renderer!\n");
	}


	SDL_SetWindowFullscreen(window,SDL_WINDOW_FULLSCREEN);


	return true;	
}

void draw_grid(void){
	for(int y=0;y<window_height;y+=10){
		for(int x=0;x<window_width;x+=10){
			color_buffer[(window_width *y )+x] = 0xFF333333;
		}
	}

}

void draw_rect(int x, int y, int width, int height, uint32_t color ){
	//x y is the top left corner =  start pos of the rectangle
	for(int xstart = x; xstart<width; xstart++){
		for(int ystart = y; ystart<height; ystart++){
			color_buffer[(window_width*ystart) + xstart] = color;
		}
	}
}

void render_color_buffer(void){
	SDL_UpdateTexture(
			color_buffer_texture,
			NULL,
			color_buffer,
			(int)(window_width * sizeof(uint32_t)));

	SDL_RenderCopy(renderer,color_buffer_texture,NULL,NULL);
}

// Resets Color Buffer to specified argument color
void clear_color_buffer(uint32_t color){
	for(int y = 0;y<window_height;y++){
		for(int x=0;x<window_width;x++){
			color_buffer[(window_width * y)+x] = color;		
		}
	}
			
}

void destroy_window(void){
    free(color_buffer);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}


