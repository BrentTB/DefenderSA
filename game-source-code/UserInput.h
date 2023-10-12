#ifndef USERINPUT
#define USERINPUT

/**
 * @file UserInput.h
 * @brief The file that holds the UserInput enum
 *
 */

/**
 * @class UserInput
 * @brief Enum that holds the possible user inputs
 *
 */
enum class UserInput
{
	/**
	 * @enum UserInput
	 *
	 */
	KeyW = 0,  /*W key, moves up*/
	KeyA,	   /*A key, moves left*/
	KeyS,	   /*S ley, moved down*/
	KeyD,	   /*D key, moves right*/
	KeyP,	   /*P key, play and pause*/
	KeyI,	   /*I key, open the information screne*/
	KeyEscape, /*Esc key, closes game window*/
	KeyEnter,  /*Enter key, activates shield and restarts game after dying*/
	KeySpace   /*Space key, fires the PlayerLaser*/
};

#endif
