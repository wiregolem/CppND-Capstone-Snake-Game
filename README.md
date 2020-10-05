# CPPND: Capstone Snake Game 

This is an expantion of the Snake Game starter repo for the Capstone project in the [Udacity C++ Nanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213). The code for this repo was inspired by [this](https://codereview.stackexchange.com/questions/212296/snake-game-in-c-with-sdl) excellent StackOverflow post and set of responses.

<img src="snake_game.gif"/>

# Extended Features
- Title screen
- Pausing the game to display the pause overlay by pressing SPACE at anytime during gameplay
- Game-over overlay
- Close the game with the ESC key at any time
- An option to reset the game on death
- Fixed a critical bug in the starter repo where food would spawn inedibly out-of-bounds rendering the game unplayable 

## Dependencies for Running Locally
* cmake >= 3.7
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* SDL2 >= 2.0
  * All installation instructions can be found [here](https://wiki.libsdl.org/Installation)
  * Note that for Linux, an `apt` or `apt-get` installation is preferred to building from source.
* SDL2_image >=2.0 
  * Linux:  [Click here for installation instructions](https://lazyfoo.net/tutorials/SDL/06_extension_libraries_and_loading_other_image_formats/linux/index.php)
  * Note that for Linux, an `apt` or `apt-get` installation is preferred to building from source.
  * Mac: [Click here for installation instructions and XCode setup](https://lazyfoo.net/tutorials/SDL/06_extension_libraries_and_loading_other_image_formats/mac/index.php)
  * Windows: [Click here for installation instructions](https://lazyfoo.net/tutorials/SDL/06_extension_libraries_and_loading_other_image_formats/windows/index.php)
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./SnakeGame`.

# Expected behavior
* Once the game is running the user will see the Snake title screen!
* Following the instructions on screen, the user may press SPACE to begin gameplay or ESC to close the window
* When gameplay begins a blue square snake head is rendered on a grey background, moving slowly, along with a yellow food block
* At any time during gameplay, pressing SPACE will pause and unpause the game, displaying the PAUSED info screen to indicate pause
* Pressing the ARROW KEYS will change the snakes direction
* If the snake's head occupies the same square as a food block the user's score increases, the snake grows, it's speed increases and a new food block will spawn
* The current score and the games frame rate per second (FPS) is updated and displayed in the game window
* If the snake runs into it's own body it has died. It's head will turn read and movement will stop
* Upon death, the game over screen is displayed, prompting the user to start a new game with SPACE or exiting the game with ESC
* When the game is exited a termination success message as well as the previous games score and snake size will be displayed to console. 

   
# Source File, Class structure, and function organization
* **Main.cpp** instantiates a Renderer object to display graphics, a Controller object to handle user input, and a Game object to run the control loop.
  * Main.cpp then calls the Game object's Run function to begin the loop.
  * When the game loop returns, a termination success message is written to the console along with the score and size achieved durring the last game.
* **Renderer.cpp** defines the Renderer class whose constructor initializes SDL, and  SDL_image, creates the application window and instantiates a renderer to display graphics.
  * It's desctructor cleans up resources when it's object leaves scope, destroying the window and signaling to terminate the application.   
  * `Render()` draws the game background, the snakes body, and the food at their current locations.
  * An overloaded `Render()` takes the gamestate and renders the appropriate texture to the screen.
    * The overloaded Render function makes use of the static function, LoadTexture provided by the TextureLoader class.
  *`UpdateWindowTitle()` set's the windows title to display the current score and frame rate.
* **TextureLoader.cpp** defines a _TextureLoader_ class with static members to provide utility to the renderer. 
  * `LoadTexture()` loads an image from disk and stores it as an SDL_Surface, it then creates a texture from the surface for use by the renderer and frees the surface resource. The texture is returned to the functions caller.
* **Controller.cpp** defines the _Controller_ class which handles user input 
  * `HandleInput()` polls SDL_events,key presses in this case, to read user input and make changes to the game state and the snake's direction
  * `ChangeDirection()` ensures that the snake's direction is only updated if the game is not paused and the requested direction is not the opposite of the snake's current facing
* **Snake.cpp** defines the Snake class which represents the player's character in this game
  * The _Snake_ class comprises a head (point), a body (vector of points), a direction, a speed, and functions for updating each
    * `Update()`  stores the snake's head position before and after calling the Update Head function and calls UpdateBody if the snake's head has moved to a new point
    * `UpdateHead()` changes the snake's head position +/- the snake's speed, depending on it's current direction
    * `UpdateBody()`  adds the snakes previous head position to the body vector, if the snake's growing boolean is false its tail is removed from it's vector, if true the snakes size is increased. The function then checks if the snake has run into itself which if true, would end the current game
    * `SnakeCell()` returns true if it's x and y parameters represent a point occupied by the snake
    * `Growbody()`  simply toggles its growing boolean to true.
    * `Respawn()` resets the snakes attributes to their initial states for playing a new game
* **Game.cpp** defines the _Game_ class wich implements the game loop and keeps score of the game the _Gamestate_ class which holds game state information as public boolean members
   *  Game's constructor is initialized with the games grid_width and grid_height as upper bounds for a random number generator which is used to randomly determine the game's food's spawn location within the game grid
     * `PlaceFood()` sets the food location, for use by the renderer, using the random number generator in a location not occupied by the snake, determined with a call to the SnakeCell() function
     * `Update()` calls snake.Update() to update the snake's data at each pass through the game loop, if the snake's head occupies the location of the food the game's score is incremented, new food is placed, snake.GrowBody() is called and the snakes speed is incremented.
     * `GetScore()` simply return's game's score member variable.
     * `GetSize()` simply returns's the snake's size.
     * `Reset()` calls snake.Respawn(), reinitializes the gamestate variables, sets the score to zero, and calls PlaceFood(). This function is used when the player has reached the game over screen and indicates a desire to play a new game 
     * `Run()` is the the heart of the program, it instatiates a gamestate object and implements the game's main game loop,
       * A stopwatch is initialized before and ended after the main game loop to count frames
       * The main game loop comprises 4 phases: Handle input, Checkgamestate, Update, Render
         * The Handle Input phase calls the controller.HandleInput() function
         * The Check game state phase calls gamestate's Check() function (which is outlined below)
         * The Update phase calls the game's Update() function
         * The Render phase calls the renderer's Render() function
       * If at least 1 second has passed, the Run() function then calls the renderer's UpdateWindow() function to display score and frames per second as counted by the stopwatch    
       * To prevent the main game loop from running too quickly, if this iteration of the loop was a shorter duration than a predefined target duration, the game is delayed by the difference.
   * The _Gamestate_ class holds booleans to determine if the game is running, paused, on the titlescreen, on the gameover screen, or has been reset. 
     * `Check()` determines if an info screen(title, gameover, or paused) should be displayed if any and if appropriate, passes the gamestate to the renderer. While an info screen is being displayed, check also delays the game loop and waits for user input. It then checks if the game should be reset. 
  
 

## Required Project Rubric Points 

1. README with instructions included
   - The README is included with the project and has instructions for running/building
   - Additional libraries needed to run the project are indicated with cross-platform installation instructions (see Dependencies -SDL2_image)
   - README submitted as markdown (README.md)
2. README indicates which project is chosen
   - The README describes the project 
   - The README indiciates the file and class structure along with expected behavior or output
3. README includes information about each rubric point addressed
   - The README indicates which points have been addressed and their locations via filename and line number
4. The submission must compile and run
   - See Basic Build Instructions above

# 5 Elective Project Rubric Points

1. The Project Demonstrates an understanding of C++ functions and control structures
   - A variety of control structures are used in the project 
     - `while` loop -game.cpp line 15 (et al.), `if-else` statement renderer.cpp line 58 (et al.), `switch` controller.cpp line 19 and extended `case`s lines 39 and 47, range based `for` loop  snake.cpp line 59, et cetera.  
   - The project code is clearly organized into functions
     - See Sourcefile, Class structure, and Function organization above 
2. The project reads data from a file
   - The project reads png's from a file, loads them as textures and displays them on screen
     - See TextureLoader.cpp lines 3 and 6, used in Renderer.cpp line 62, using files names from Renderer.h on lines 31,32 and 33
3. The project accepts input from a user as part of the necessary operation of the program.
   - See game.cpp controller.HandleInput() calls on lines 16 and 57, see controller.cpp Controller::HandleInput() from line 12 to 68
4. The project makes use of references in function declarations.
   - At least two functions use pass-by-reference in the project code
     -See renderer.cpp line 54 Renderer::Render(Gamestate &gamestate), see game.cpp line 8 Gamestate::Check(Game &game,Renderer &renderer,Snake &snake, Controller const &controller)
5. Overloaded functions allow the same function to operate on different parameters
   - One function is overloaded with different signatures for the same function name
     - see renderer.h line 16 `void Render(Gamestate&);` and line 17 `void Render(Snake const snake, SDL_Point const &food);` 
