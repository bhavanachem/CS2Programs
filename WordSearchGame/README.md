# Word Search Movie Finder

This program searches for movie titles in a word search puzzle stored in a text file. The user provides the file location, and the program reads the file, searching for the word search grid and a list of movie titles to try to find. The word search is searched in all eight possible directions (Northwest, North, Northeast, West, East, Southwest, South, Southeast). If a movie title is found, its location (row, column) and direction are displayed. The program also reports any movie titles that were not found.

## Features

- Loads a word search from a text file.
- Searches for movie titles in the word search grid.
- Reports the location and direction of any found titles.
- Displays a message for each movie title that was not found.
- Handles input validation for file loading.
- Handles both uppercase and lowercase movie titles.
- Provides an option to quit at any time.
## Technical Details

### Data Structures

- **2D Array (Matrix)**:  
  The word search grid is represented as a **2D array** (`char` array). This array holds the characters of the word search puzzle and is used to search for movie titles in all eight possible directions.


## Usage

1. The program will prompt you to enter the name and location of the word search file. Enter the full path to the file or type `quit` to exit.
2. If the file is successfully loaded, the program will attempt to find the movie titles listed in the file within the word search grid.
3. For each movie title found, the program will display the row, column, and direction (e.g., "heading North").
4. If a movie title is not found, it will be reported in a separate list.


## Installation

1. Clone this repository
2. Open the project in your preferred C++ IDE (e.g., Visual Studio, Code::Blocks).
3. Build and run the program.
