//Programmer: Logan Markley
//Student ID: 12579435
//MST Username: lcmkbc
//Instructor Name: San Yeung
//Section: 109
//Date: 2/17/22
//File: hw3_MARKLEY2.cpp
//Purpose: Refine our "WORDLE" game in C++ (HW 3)

#include <iostream>
#include <string>
#include <ctype.h>
#include <stdio.h>

using namespace std;

// Description: print out a simple greeting message to the user when called (is called whenever the program opens)
// Pre: none
// Post: successful kind message is printed, returns nothing
void greet();

// Description: prints out the wordle menu options when called (is called when the user is selecting from the menu)
// Pre: none
// Post: successful wordle menu is printed, returns nothing
void printWordleMenu();

// Description: prints out the stats over all rounds played between the two players when chosen from the wordle menu, also can add 2 to their friendship level
// Pre: p1 must be player1name, p2 must be player2name, rounds must be roundCount, friendshipOld must be friendshipLevelOld
//      friendshipNew must be friendshipLevel | if these are not the called variables, the function WILL misbehave
// Post: game summary is successfully printed using the parameters, and friendship level may have been increased by 2, returns nothing
void printGameSummary(string p1, string p2, int rounds, int friendshipOld, int & friendshipNew);

// Description: prints out the words guessed in the last round using the symbols for each letter (^o^, ^-^, @.@). each line corresponds to a word attempt
// Pre: p1 must be player1name, p2 must be player2name, words must be wordleResults, rounds must be roundCount, and attempts must be attemptCount
//      if these are not the called variables, the function WILL misbehave
// Post: words guessed from last round are successfully printed out using the parameters, returns nothing.
void shareWordle(string p1, string p2, string words, int rounds, int attempts);

int main() {
  //---------variable declaration----------------------------------------

  string player1name;
  string player2name;

  string p1word;
  string p2guess;
  
  string wordleResults="";  //this string will have every @.@ ^-^ or ^o^ stored so that it can be printed out in shareWordle()

  int friendshipLevel = -1;    //this variable refers to the current friendship level
  int friendshipLevelOld = -1; //while this one refers to the level before playing each round

  int attemptCount = 1; //keeps track of what guess number player 2 is on
  int roundCount = 0;  //initialized to 0 because 0 rounds have been played yet

  bool playWordle = true;  //variable is set to false when the user exits from the menu
  bool rematch = false; //these variables deal with the replaying and start of the game
  bool newPlayer2 = true;  //variable is set to true when there is no player 2 yet, or if player 1 wants to play with a different player 2

  //------------introduction---------------------------------------------

  greet();
  
  do {
    int menuChoice = 0;
    bool leaveMenu = false;
    printWordleMenu();
    cout << "Enter the menu number you would like (1-5): ";
    do {       //this do while loop is to keep the user in the wordle menu until they make an appropriate choice
      cin >> menuChoice;
      switch (menuChoice) {
      case 1:
        cout << "Option selected: New Game." << endl;
        cout << "Hello Player 1! Your name please: ";
        cin >> player1name;
        newPlayer2 = true;
        attemptCount = 1;       //resets the attempt counter after each game
        leaveMenu = true;
        break;
      case 2:
        if (roundCount == 0) {
          cout << "No existing player info found! Please make a different selection: ";
        } else {
          cout << "Option selected: New Round." << endl;
          cout <<endl<< "Yay! Round " << roundCount + 1 << " with " << player1name << " and " << player2name << "!" << endl;
          newPlayer2 = false;
          rematch = true;
          leaveMenu = true;
        }
        break;
      case 3:
        if (roundCount == 0) {
          cout << "No previous game data found! Please make a different selection: ";
        } else {
          cout << "Option selected: Print Game Summary." << endl;
          printGameSummary(player1name, player2name, roundCount, friendshipLevelOld, friendshipLevel);
          printWordleMenu();
          cout << "Enter the menu number you would like (1-5): ";
        }
        break;
      case 4:
        if (roundCount == 0) {
          cout << "No previous game data found! Please make a different selection: ";
        } else {
          cout << "Option selected: Share Result." << endl;
          shareWordle(player1name, player2name, wordleResults, roundCount, attemptCount);
          printWordleMenu();
          cout << "Enter the menu number you would like (1-5): ";
        }
        break;
      case 5:
        cout << "OK, good bye! See you soon, Wordle Wordle! \nRemember, a real friend is one who always Wordles with you when the rest of the world won’t!"<<endl;
        leaveMenu = true;
        playWordle = false;
        break;
      default:
        cout << "This integer choice (" << menuChoice << ") is not recognized among the menu options! Please try again: ";
        break;
      }
    } while (leaveMenu == false);

    while (playWordle == true && (rematch == true || newPlayer2 == true)) {
      wordleResults=""; //resets the wordleResults because it only stores results from one round.
      attemptCount = 1; //resets the attempt counter after each game
      roundCount++; //adds one to round count because its the start of a new round
      if (newPlayer2 == true) //gets a new player 2 and friendship level if menu option 1 is selected
      {
        cout << "Player 2's name: ";
        cin >> player2name;

        friendshipLevel = -1; //resets the friendshipLevel when changing characters
        while (friendshipLevel < 0 || friendshipLevel > 100) //this while loop is to make sure that the friendship level is a valid number
        {
          cout << player1name << ", what is your friendship level with " << player2name << "? (integer value in [0, 100]): ";
          cin >> friendshipLevel;
          if (friendshipLevel < 0 || friendshipLevel > 100)
            cout << "That friendship level is not a valid entry." << endl;
        }
        cout << "Thanks! Let's begin.";
      }

      //-----start of the game------------------------------------------------------------------------------------------------------------------------

      bool fiveLetters = false; //these two variables must be turned true in order to continue the game
      bool alphabetical = false;
      while (fiveLetters == false || alphabetical == false) {
        cout << endl << player1name << ", enter your secret key word (five-letter word all UPPERCASE): ";
        cin >> p1word;

        if (p1word.length() == 5) //this if else is to make sure that the word is 5 letters
          fiveLetters = true;
        else
          fiveLetters = false;

        alphabetical = true; //sets alphabetical to true     
        int len = p1word.length();
        for (int i = 0; i < len; i++) //this for loop is to make sure that all characters are alphabetical
        {
          if (isalpha(p1word.at(i)) == 0) //changes alphabetical to false if non-alphabetic characters are detected
            alphabetical = false;
        }
        if (alphabetical == false)
          cout << "That word contains non-alphabetic characters! ";
        if (fiveLetters == false)
          cout << "That word is not 5 letters long!";
      }
      cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl; //creates a big break so that player 2 cannot see the word.

      //-------guessing part of the game-------------------------------------------------------------------------------------------------------

      bool guessingFinished = false; //this variable would be turned to true if the word is guessed.
      while (attemptCount < 7 && guessingFinished == false) {
        fiveLetters = false; //this segment of code is the same format as before. used to make sure player 2 enters a 5 letter word.
        alphabetical = false;
        while (fiveLetters == false || alphabetical == false) {
          cout << endl << player2name << ", this is attempt #" << attemptCount << ". Enter your guess (five-letter word all UPPERCASE): ";
          cin >> p2guess;

          if (p2guess.length() == 5) //this if else is to make sure that the word is 5 letters
            fiveLetters = true;
          else
            fiveLetters = false;

          alphabetical = true; //sets alphabetical to true   
          int len = p2guess.length();
          for (int i = 0; i < len; i++) //this for loop is to make sure that all characters are alphabetical
          {
            if (isalpha(p2guess.at(i)) == 0) //changes alphabetical to false if non-alphabetic characters are detected
              alphabetical = false;
          }
          if (alphabetical == false)
            cout << "That word contains non-alphabetic characters! ";
          if (fiveLetters == false)
            cout << "That word is not 5 letters long!";
        }

        if (p1word == p2guess) {
          cout << "You entered \"" << p2guess << "\". Great job! You got it in " << attemptCount << " tries!" << endl;
          guessingFinished = true;
        } else if (attemptCount == 6)
          cout << "You entered \"" << p2guess << "\". Dang, you didn't guess it!" << endl;
        else
          cout << "You entered \"" << p2guess << "\". Nice try, keep going!" << endl;
          
        int len = p1word.length();
        int len2 = p2guess.length();
        for (int i = 0; i < len; i++) //this for loop and nested for loop are used to compare the letters of the words.
        {
            bool isInWord=false;
            for (int j = 0; j < len2; j++)  //this loop is to see if the word contains the letter in any spot
            {
              if(p1word.at(j)==p2guess.at(i))
                isInWord=true;
            }
            
            if (p1word.at(i) == p2guess.at(i))       //if the letter is in the correct spot
            {
              cout << p2guess.at(i) << ": ^o^" << endl;
              wordleResults += "^o^ ";
            } else if (isInWord)                          //if the letter is in the wrong spot of the word
            {
              cout << p2guess.at(i) << ": ^-^" << endl;
              wordleResults += "^-^ ";
            } else  //at the last search, concludes the letter is not in the key word
            {
              cout << p2guess.at(i) << ": @.@" << endl;
              wordleResults += "@.@ ";
            }
          
        }
        wordleResults += "\n-------------------\n"; //creates a new line in wordleResults to separate the words from each attempt.
        
        if (guessingFinished == false)
          attemptCount++;

      }

      //-------end results part of the game-----------------------------------------------------------------------------------------------

      if (guessingFinished == false)
        cout << "Aww! You didn't get the word! :(";
      friendshipLevelOld = friendshipLevel;
      if (attemptCount == 7) //these if statements change friendship level depending on how many tries it took player 2.
      {
        friendshipLevel = friendshipLevelOld;
      } else if (attemptCount == 6) {
        if (friendshipLevel < 95) 
          friendshipLevel = friendshipLevelOld + 6;
        else
          friendshipLevel = 100;
      } else if (attemptCount == 5) {
        if (friendshipLevel < 96)
          friendshipLevel = friendshipLevelOld + 5;
        else
          friendshipLevel = 100;
      } else if (attemptCount == 4) {
        if (friendshipLevel < 97) 
          friendshipLevel = friendshipLevelOld + 4;
        else
          friendshipLevel = 100;
      } else if (attemptCount == 3) {
        if (friendshipLevel < 98) 
          friendshipLevel = friendshipLevelOld + 3;
        else
          friendshipLevel = 100;
      } else if (attemptCount == 2) {
        if (friendshipLevel < 99) 
          friendshipLevel = friendshipLevelOld + 2;
        else
          friendshipLevel = 100;
      } else {
        if (friendshipLevel < 100)
          friendshipLevel = friendshipLevel + 1;
        else
          friendshipLevel = 100;
      }
      cout << endl;
      
      cout << "Round " << roundCount << " Summary" << endl;          //these 4 lines are for the round summary.
      cout << "  Player 1: " << player1name << endl;
      cout << "  Player 2: " << player2name << endl;
      cout << "  Friendship Level: " << friendshipLevelOld << " -> " << friendshipLevel << endl;
      
      newPlayer2=false;
      rematch=false;
    }
  } while (playWordle == true);
  return 0;
}


//---------function definitions------------------------------------------------------------------------


void greet() {
  cout << "Welcome to Wordle For Friends!" << endl << "<^.^>" << endl;
  return;
}

void printWordleMenu() {
  cout << endl << "The Wordle's Menu" << endl << "-----------------" << endl;
  cout << "  1. Start a new game (with new Players)" << endl;
  cout << "  2. Start a new round (with existing players)" << endl;
  cout << "  3. Print game summary (of existing players)" << endl;
  cout << "  4. Share result (of last round)" << endl;
  cout << "  5. Exit the game (are you sure?)" << endl;
  return;
}

void printGameSummary(string p1, string p2, int rounds, int friendshipOld, int & friendshipNew) {
  cout <<endl<< "Game Summary" <<endl;
  cout << "  Player 1: " << p1 <<endl;
  cout << "  Player 2: " << p2 <<endl;
  cout << "  Number of rounds played: " << rounds <<endl;
  cout << "  Initial friendship level: " << friendshipOld <<endl;
  if(friendshipNew<20){
    friendshipNew+=2;
    cout << "  Current friendship level: " << friendshipNew << " (2 bonus levels added)" <<endl;
  }
  else
    cout << "  Current friendship level: " << friendshipNew <<endl;
  return;
}

void shareWordle(string p1, string p2, string words, int rounds, int attempts) {
  cout <<endl<< "Wordle for Friends (" << p1 << " and " << p2 << ")" <<endl;
  cout <<endl<< words <<endl<<endl;
  cout <<"Wordle Round "<<rounds<<" "<<attempts<<"/6"<<endl;
  cout <<"This is your Wordle journey for the day to be shared!"<<endl;
  return;
}





