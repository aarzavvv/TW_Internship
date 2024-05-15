// Importing all the necessary Libraries and Modules
fmx.h       :   FireMonkey Framework in C++
hdrstop     :   Stops the compiler From including more header files
package     :   Specifies the package initialization mode
resource    :   Specifies that this file is a resource file
rest files includes the FMX modules that are used in the code
//---------------------------------------------------------------------------


// Declaring variables and TForm
*Form       :   This is a pointer to an Object of type 'TForm1' (Main form)
cPlayer     :   Keeps track of the current player
gameEnded   :   Boolean variable that indicate that the game has ended or not
//---------------------------------------------------------------------------


// This contains all the conditions

// Winner
Winn()      :   This is a function that contains all the functionalitites of
                the winning conditions.

// Draw
IsDraw()    :   This is another function that checks that the game has ended
                in draw condition or not.
//---------------------------------------------------------------------------


// Initializing form
TForm1      :   This a a constructor for 'TForm1' class. It initializes form
                and sets the text of 'cPlay' Current Player.
//---------------------------------------------------------------------------


// Setting buttons functionalities

    // Check if the game has ended

    // No overwriting the button text

    // Change the color of the text based on the current player

    // Checking if there's a winner

    // Conditional Statement changing the player's turn in board
//---------------------------------------------------------------------------


// Replay Function

    // Resetting all buttons back to empty

    // Resetting the player back to 'x'

    // Game is still not ended
//---------------------------------------------------------------------------


// Exit Function

	// Exiting the Game
//---------------------------------------------------------------------------


// Event Handler for the form creation

	// Form Creation!!
//---------------------------------------------------------------------------