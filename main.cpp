//Bhavana Chemuturi
//HW2-CS2337-Bhavana-Chemuturi.cpp
//9/27 Creation Date


/*----------------ChangeLog--------------------
9/27 - Made basic template to ask user for file and load into our program.
    problems: Find a way to tell user if they upload a valid file,
                    but it doesn't contain the word search
9/27 First run + Debugging
9/28 Notes taken in Class for Program
        -Need to use spaces when report back if movie found or not
        -Solution: skip space while searching in matrix
        -isalpha(), ispunct(), isdigit()
Problem: Asking multiple times to enter file name
            when user inputs words, not path
    Sol: Taking multiple inputs when user enters a space
Problem : Fix row and column, it is only reading one int
    Sol: Researched on it, solution in line 129
10/1 Note: ignore Upper case
---------------ChangeLog-End------------------*/

#include <iostream> // cout and cin
#include <conio.h> // console input and output
#include <windows.h>
#include <fstream> // for file reading
#include <string> // for using strings
#include <cstdlib> //for exit function
#include <vector> // for vectors
#include <cctype> // isalpha, isspace, etc

using namespace std;

//global variables
string fileName;
ifstream infile(fileName);
int wordSearchRow , wordSearchCol;
char wordSearch[40][40];
int xDir[] = {-1, -1, -1, 0, 0, 1, 1, 1}; //for searching
int yDir[] = {-1, 0, 1, -1, 1, -1, 0, 1};
vector<string> movieTitles;
vector<string> moviesNotFound;
//end of variables

//------------------- program starts---------------------------------

bool askUserFile()
{
    cout<< "Enter the name and location of the word search file to read: " <<endl;
    getline(cin, fileName); //reading user input
    if(fileName == "quit" || fileName == "QUIT"){
        cout<< "Quitting at user request.\n";
        exit(EXIT_SUCCESS); //quitting program
        return false;
    }
    ifstream infile(fileName);
    if (infile.good()){
        cout << "Success. File opening.\n"<< endl;
        return true;
    }
    else{
        cout << "The file: " + (fileName) + " was not found. Please try again. Or type quit to exit. \n";
        return false;
    }
}//end of askUserFile()

void uploadFile()
{//continue looping until user is able to successfully input file
    bool filePassed = false;
    while (!filePassed){
        filePassed=askUserFile();
    }
}//end of uploadFile()

bool checkCount(string line)
{
    int letterCount = 0;
    for(char letter : line)
    {
        if(letter == ' ')
        {
            return false;
        }
        letterCount++;
    }
    if(letterCount == wordSearchRow){
        return true;
    }
    return false;
}//end of checkCount()

void addToWordSearch(string line, int row)
{//add each line of the word search into char array
    for (int col =0; col < wordSearchCol;col++)
    {
        wordSearch[row][col] = line[col];
    }
}// end of addToWordSearch()

void readFile()
{// make 2d array of word search and make vector of movies to find
    ifstream infile(fileName);
    string textLine;
    char nextCh;
    int alphaCount=0;

    while (getline(infile, textLine))
    {
        // Iterate through lines, skipping comment lines (#) and empty lines
        nextCh = textLine[0];
        if (textLine.empty() || textLine[0] == '#') {
            continue;
        }

        // process the line as needed
        if (isalpha(nextCh)) {
            if(checkCount(textLine)){
                //add this to word search
                addToWordSearch(textLine, alphaCount);
            }
            else{
                //this is a movie title to find
                movieTitles.push_back(textLine);
            }
            alphaCount++;
        }
        else if (isdigit(nextCh)) {
                int rows, cols;
                sscanf(textLine.c_str(), "%d %d", &rows, &cols) == 2;
                wordSearchRow = rows;
                wordSearchCol = cols;
               // cout << "row" + to_string(rows)+ " col "+ to_string(cols);
        }
        else {
            continue;
        }
    }//end of iterating through file
/*
    //print movies (debugging)
    for (const string& element : movieTitles) {
            cout << element << " / ";
        }
        cout << endl;
*/
    //print array (debugging)
    for (int row = 0; row < wordSearchRow; ++row) {
        for (int col = 0; col < wordSearchCol; ++col) {
            cout << wordSearch[row][col] << " ";
        }
        cout << endl;
    }
    cout<< "\n" <<endl;
} //showTheFile

string removeSpaces(string str) {
    string strRemoved;
    for(char c : str){
        if(!isspace(c)){
            strRemoved += c;
        }
    }
    return strRemoved;
}//end of removeSpaces()

string getDir(int dir)
{
    if(dir == 0)
    {
        return " heading Northwest.";
    }
    if(dir == 1){
        return " heading North.";
    }
    if(dir == 2){
        return " heading Northeast.";
    }
    if(dir == 3){
        return " heading West";
    }
    if(dir == 4){
        return " heading East.";
    }
    if(dir == 5){
        return " heading Southwest.";
    }
    if(dir == 6){
        return " heading South.";
    }
    if(dir == 7){
        return " heading Southeast.";
    }
}//end of getDir()

string findWords(string movieTitle)
{
    string title = removeSpaces(movieTitle);
    string direction;
    for (int row = 0; row < wordSearchRow; row++) {
        for (int col = 0; col < wordSearchCol; col++) {
                //iterating through each Coord
            if (wordSearch[row][col] != toupper(title[0]))
            { //if first letter doesnt match, do next Coord
                continue;
            }

            int len = title.length();
            bool found = true;

            // search word in all 8 directions starting from (row, col)
            for (int dir = 0; dir < 8; dir++) {
                int nthLetter;
                // starting point for current direction
                int rowCord = row + xDir[dir];
                int colCord = col + yDir[dir];

                for (nthLetter = 1; nthLetter < len; nthLetter++) {
                    // if out of bounds, break

                    if (rowCord >= wordSearchRow || rowCord < 0 || colCord >= wordSearchCol || colCord < 0) {
                        found = false;
                        break;
                    }
                    // if not matched, break
                    if (wordSearch[rowCord][colCord] != toupper(title[nthLetter])) {
                        found = false;
                        break;
                    }

                    // moving in particular direction
                    rowCord += xDir[dir];
                    colCord += yDir[dir];
                }

                // If all characters matched, then value of k must
                // be equal to length of word
                if (nthLetter == len) {
                    return "Found " + movieTitle + " at row " + to_string(row + 1) + " and col " + to_string(col + 1) + getDir(dir);
                }
            }
        }
    }// end of coord iteration
    moviesNotFound.push_back(movieTitle);
    return "";
}//end of findWords()


void isMovieFound()
{
    string result;
    for (string movie : movieTitles){
        result = findWords(movie);
        if(result!=""){
            cout << result << endl;
        }
    }
    cout << "\n" <<endl;
    for (string notFound : moviesNotFound){
        cout << "Could not find "+ notFound << endl;
    }
}//end of isMovieFound()

int main()
{
    uploadFile();
    readFile();
    isMovieFound();
}// end of main()
