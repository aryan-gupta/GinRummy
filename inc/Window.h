/* 
 * Copyright (c) 2017 The Gupta Empire - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 *
 * Written by Aryan Gupta <me@theguptaempire.net>
 * 
 * =============================================================================
 * @author 			Aryan Gupta
 * @project 		
 * @title 			
 * @date			(YYYY-MM-DD)
 * @fversion		1.0.0
 * @description 	
 * =============================================================================
 */

#ifndef WINDOW_H_INC
#define WINDOW_H_INC

extern const int SCRN_W;
extern const int SCRN_H;
extern const int WIN_PAD;

class Window {
public:
	Window();  ///< Creates our Window
	~Window(); ///< Destroys our Window and cleans up variables
	
	/// @brief initializes all the variables in our window
	/// The variables aren't done in the constructor because many of the
	/// variables used in this class need to be accessed after the main window 
	/// is created, but after the window is set up
	void initWindow();
	
	void renderAll();            ///< Renders all of the objects on the screen
	
	inline SDL_Renderer*  getRenderer();       ///< Get the current Window's renderer
private:
	SDL_Window* window;     ///< Stores our main Window
	SDL_Renderer* renderer; ///< Stores our main renderer
	
	SDL_Texture* background; ///< The background texture, Points to texture in \ref Resources
	
	void clear();
	void renderBackground();
	
	void drawAButton(SDL_Texture* tex, SDL_Rect src, int h_p, int w_p, SDL_Rect dest);
};


inline
SDL_Renderer* Window::getRenderer()
{ return renderer; }

#endif