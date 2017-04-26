/* 
 * Copyright (c) 2017 The Cool Group - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 *
 * Written by:
 * Harrison Read		<hread2@uncc.edu>
 * Pichsapa Kulapruk	<pkulapru@uncc.edu>
 * Aryan Gupta			<agupta40@uncc.edu>
 * 
 * =============================================================================
 * @author 			The Cool Group
 * @project 		GinRummy 		
 * @title 			
 * @date			(YYYY-MM-DD)
 * @fversion		1.0.0
 * @description 	
 * =============================================================================
 */

#ifndef WINDOW_H_INC
#define WINDOW_H_INC

#include <vector>

#include "./Resources.h" /// for HelpTextItems

extern const int SCRN_W;  ///< The Screen Width
extern const int SCRN_H;  ///< The Screen Height
extern const int WIN_PAD; ///< Padding for various elements

/// @brief Stores our Window, and all of the game functions. 
class Window {
public:
	Window();  ///< Creates our Window
	~Window(); ///< Destroys our Window and cleans up variables
	
	/// @brief initializes all the variables in our window
	/// The variables aren't done in the constructor because many of the
	/// variables used in this class need to be accessed after the main window 
	/// is created, but after the window is set up
	void initWindow();
	
	void renderAll(); ///< Renders all of the objects on the screen
	
	/// @brief Sets knocked flag to true
	/// @param [in] player - The knocker
	void knock(int player); 
	
	void finalizeRound(); ///< Finalizes the round (shows the hand of each player and counts up points etc.)
	
	/// @brief Change the help text text
	/// @param [in] helpToRender - The text index to change to. \sa HelpTextItems
	void changeHelp(HelpTextItems helpToRender);
	
	/// @brief checks of our click was in the knock button
	/// @param [in] x `int` The x coordinate of the click 
	/// @param [in] y `int` The y cordinate of the click
	bool checkKnockClick(const int x, const int y);
	
	/// @brief checks of our click was in the sort button
	/// @param [in] x `int` The x coordinate of the click 
	/// @param [in] y `int` The y cordinate of the click
	bool checkSortClick(const int x, const int y);
	
	/// @brief Get the current Window's renderer
	/// @return SDL_Renderer* A pointer to the current windows render
	inline SDL_Renderer* getRenderer();
	
	/// @brief Gets read-write access to the knock status
	/// @return bool the knock status
	inline bool& getKnockStatus();
	
private:
	SDL_Window* window;     ///< Stores our main Window
	SDL_Renderer* renderer; ///< Stores our main renderer
	
	bool soKnocked; ///< flag that stores if we have knocked or not
	std::vector<unsigned*> roundPoints; ///< Stores all the points for the rounds
	
	HelpTextItems helpToRender; ///< Which help text we should render
	
	void clear();  ///< Clear the window
	void renderBackground();    ///< Render the background
	void renderButtons();       ///< Render the buttons
	void renderMeldsDeadwood(); ///< Render the meld/deadwood texts
	void renderHelp();   ///< Render the help text and panel
	void layoffCards();  ///< Show the laying off screen
	void showPoints();   ///< Show the final screen
	
	/// @brief Render the final screen
	/// @param [in] displayPoints - Should we darken the screen and display the points
	void renderFinal(bool displayPoints);
	
	/// @brief Checks if or mouse click is on the continue button
	/// @param x - The x coordinate of the click
	/// @param y - The y coordinate of the click
	bool checkContinueClick(const int x, const int y);
	
	/// @brief draws a button
	/// @param [in] tex `SDL_Texture*` The texture to use when rendering
	/// @param [in] src `SDL_Rect` The clipping of the button on the texture
	/// @param [in] h_p `int` The vertical size of the border 
	/// @param [in] w_p `int` The horizontal size of the border 
	/// @param [in] dest `SDL_Rect` The position of the button on the screen
	void drawAButton(SDL_Texture* tex, SDL_Rect src, int h_p, int w_p, SDL_Rect dest);
};


inline
SDL_Renderer* Window::getRenderer()
{ return renderer; }

inline
bool& Window::getKnockStatus() 
{ return soKnocked; }

#endif