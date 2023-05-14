#include "rc_game.h"
#include <cstddef>
#include <iostream>
#include <vector>
#include <fstream>
#include <ostream>
#include <string>
#include <ncurses.h>

using std::string;
using std::cout;
using std::cin;
using std::endl;

void RCGameManager::printTitle() {
    system("clear");
    cout << "+----------------------+" << endl;
    cout << "|       縱橫殺棋       |" << endl;
    cout << "+----------------------+" << endl;
}

bool RCGameManager::run() {
    /* Start Menu */
    size_t choice = 0;
    std::vector<string> menu = {
        "Start a random game", 
        "Load a game from \"input.txt\"",
        "Test alpha-beta pruning", 
        "Quit"
    };

    // print start menu
    system("clear");
    printMenu("Start Menu", menu, choice);

    // read user input
    while (true) {
        initscr(); cbreak(); noecho();
        int ch = getchar();
        endwin();

        switch (ch) {
            case 'k':
            case 'K':
                if (choice > 0) choice -= 1;
                break;
            case 'j':
            case 'J':
                if (choice < menu.size() - 1) choice += 1;
                break;
            case ' ':
                break;
        }

        if (ch == ' ') break;

        system("clear");
        printMenu("Start Menu", menu, choice);
    }

    // handle user input
    switch (choice) {
        case 0:
            startRandomGame();
            break;
        case 1:
            startGame();
            break;
        case 2:
            testAlphaBetaPruning();
            break;
        case 3:
            quitGame();
            break;
    }

    if (choice == 3) return false;
    else return true;
}

void RCGameManager::pressAnyKeyToContinue() {
    cout << "Press any key to continue..." << endl;

    initscr(); cbreak(); noecho();
    getchar();
    endwin();
}    

void RCGameManager::startGame() {
    // select pvp or pvc
    size_t choice = 0;
    std::vector<string> menu = {
        "Player vs Player", 
        "Player vs AI (Player first)",
        "Player vs AI (AI first)",
    };

    //print menu
    system("clear");
    printMenu("Select Game Mode", menu, choice);

    // read user input 
    while (true) {
        initscr(); cbreak(); noecho();
        int ch = getchar();
        endwin();

        switch (ch) {
            case 'k':
            case 'K':
                if (choice > 0) choice -= 1;
                break;
            case 'j':
            case 'J':
                if (choice < menu.size() - 1) choice += 1;
                break;
            case ' ':
                break;
        }

        if (ch == ' ') break;

        system("clear");
        printMenu("Select Game Mode", menu, choice);
    }

    // start game 
    switch (choice) {
        case 0:
            pvpGame();
            break;
        case 1:
            pvcGame(true);
            break;
        case 2:
            pvcGame(false);
            break;
    }
}

void RCGameManager::pvpGame() {
    RCGame game("input.txt");
    char maxRow = std::to_string(game.getHeight())[0];
    char maxCol = (char)('A' + game.getWidth() - 1);

    std::vector<string> systemMessage;
    systemMessage.push_back("");
    systemMessage.push_back("");
    systemMessage.push_back("Game Start!");
    
    while (true) {
        // print title
        system("clear");
        cout << "+----------------------+" << endl;
        cout << "|   Player vs Player   |" << endl;
        cout << "+----------------------+" << endl;
        cout << endl;

        // print game status
        cout << "+----------Game Status----------+" << endl;
        cout << "Player " << game.getCurrentPlayer() + 1 << "'s turn." << endl;
            cout << "Player 1: " << game.getPlayerScore(0) << " points" << endl;
        cout << "Player 2: " << game.getPlayerScore(1) << " points" << endl;
        cout << "+-------------------------------+" << endl;
        cout << endl;

        game.printBoard();
        cout << endl;

        // print input message
        cout << "+------------------Input Menu-----------------+" << endl;
        cout << "Please enter the row(1 to "<< game.getHeight() 
             << ") or column(A to " << (char)('A' + game.getWidth() - 1) 
             << ") you want to kill," << endl;
        cout << "or enter character below to do other actions:" << endl;
        cout << "  's': back to start menu." << endl;
        cout << "  'r': restart game." << endl;
        cout << "  'h': get a hint." << endl;
        cout << "  'q': quit game." << endl;
        cout << "+---------------------------------------------+" << endl;
        cout << endl;

        // print system message 
        cout << "+------------------Message------------------+" << endl;
        for (size_t i = 0; i < systemMessage.size(); i++) {
            cout << systemMessage[i] << endl;
        }
        cout << "+-------------------------------------------+" << endl;
        cout << endl;
        cout << ">> ";

        // read user input 
        char in;
        cin >> in;

        // handle user input 
        switch (in) {
            case 's': system("clear"); return;    
            case 'r':{
                game = RCGame("input.txt");
                systemMessage.clear();
                systemMessage.push_back("");
                systemMessage.push_back("");
                systemMessage.push_back("Game Restart!");
                break;
            }
            case 'h':{ 
                // get hint
                auto hint = RCGame::minimax(game, RCGame::MAX_ROW+RCGame::MAX_COLUMN, -RCGame::MAX_BOARD_SIZE, RCGame::MAX_BOARD_SIZE, game.getCurrentPlayer());
                string hintMessage = "Hint: ";
                if (hint.first.first == RowColumn::Row) {
                    hintMessage += "Row " + std::to_string(hint.first.second + 1) + ".";
                } else {
                    hintMessage += "Column " + std::string(1, (char)('A' + hint.first.second)) + ".";
                }
                    
                systemMessage.erase(systemMessage.begin());
                systemMessage.push_back(hintMessage);
                break;
            }
            case 'q': quitGame(); break;
            default: {
                // check if input is valid
                systemMessage.erase(systemMessage.begin());

                if (in >= '1' && in <= maxRow) {
                    // kill row
                    int row = in - '1';
                    int score = game.clearLine(RCMove(RowColumn::Row, row));

                    if (score == 0) {
                        systemMessage.push_back("Invalid input!");
                        break;
                    }
                    else {
                        string message = "Player " + std::to_string(2-game.getCurrentPlayer());
                        message += " killed row " + std::to_string(row + 1);
                        message += " and got " + std::to_string(score) + " points.";
                        systemMessage.push_back(message);
                    }
                                    
                } else if (in >= 'A' && in <= maxCol) {
                    // kill column
                    int col = in - 'A';
                    int score = game.clearLine(RCMove(RowColumn::Column, col));

                    if (score == 0) {
                        systemMessage.push_back("Invalid input!");
                        break;
                    }
                    else {
                        string message = "Player " + std::to_string(2-game.getCurrentPlayer());
                        message += " killed column " + std::string(1, (char)('A' + col));
                        message += " and got " + std::to_string(score) + " points.";
                        systemMessage.push_back(message);
                    }
                } else {
                    systemMessage.push_back("Invalid input!");
                }
            }
        }

        // check if game is over
        if (game.isBoardEmpty()) break;
    }

    // game over
    // print title
    system("clear");
    cout << "+----------------------+" << endl;
    cout << "|   Player vs Player   |" << endl;
    cout << "+----------------------+" << endl;
    cout << endl;

    game.printBoard();
    cout << endl;

    cout << "+----------Game Status----------+" << endl;
    cout << "Game Over!" << endl;
    cout << "Player 1 got " << game.getPlayerScore(0) << " points." << endl;
    cout << "Player 2 got " << game.getPlayerScore(1) << " points." << endl;
    
    if (game.getPlayerScore(0) > game.getPlayerScore(1)) {
        cout << "Player 1 won!" << endl;
    }
    else if (game.getPlayerScore(0) < game.getPlayerScore(1)) {
        cout << "Player 2 won!" << endl;
    } else {
        cout << "Draw!" << endl;
    }
    cout << "+-------------------------------+" << endl;
    cout << endl;

    cin.ignore();

    pressAnyKeyToContinue();
}

void RCGameManager::pvcGame(bool isPlayerFirst) {
    RCGame game("input.txt");
    int player = isPlayerFirst ? 0 : 1;
    char maxRow = std::to_string(game.getHeight())[0];
    char maxCol = (char)('A' + game.getWidth() - 1);

    std::vector<string> systemMessage;
    systemMessage.push_back("");
    systemMessage.push_back("");
    systemMessage.push_back("Game Start!");
    
    while (true) {
        // print title
        system("clear");
        cout << "+-----------------------+" << endl;
        cout << "|     Player vs AI      |" << endl;
        cout << "+-----------------------+" << endl;
        cout << endl;

        // print game status
        cout << "+----------Game Status----------+" << endl;
        if (game.getCurrentPlayer() == player) {
            cout << "Player's turn." << endl;
        } else {
            cout << "AI's turn." << endl;
        }

        cout << "Player: " << game.getPlayerScore(player) << " points" << endl;
        cout << "AI: " << game.getPlayerScore(1-player) << " points" << endl;
        cout << "+-------------------------------+" << endl;
        cout << endl;

        game.printBoard();
        cout << endl;

        // print input message
        cout << "+------------------Input Menu-----------------+" << endl;
        cout << "Please enter the row(1 to "<< game.getHeight() 
             << ") or column(A to " << (char)('A' + game.getWidth() - 1) 
             << ") you want to kill," << endl;
        cout << "or enter character below to do other actions:" << endl;
        cout << "  's': back to start menu." << endl;
        cout << "  'r': restart game." << endl;
        cout << "  'h': get a hint." << endl;
        cout << "  'q': quit game." << endl;
        cout << "+---------------------------------------------+" << endl;
        cout << endl;

        // print system message 
        cout << "+------------------Message------------------+" << endl;
        for (size_t i = 0; i < systemMessage.size(); i++) {
            cout << systemMessage[i] << endl;
        }
        cout << "+-------------------------------------------+" << endl;
        cout << endl;
        cout << ">> ";

        // if it's AI's turn
        if (game.getCurrentPlayer() != player) {
            auto aiMove = RCGame::minimax(game, RCGame::MAX_ROW+RCGame::MAX_COLUMN, -RCGame::MAX_BOARD_SIZE, RCGame::MAX_BOARD_SIZE, game.getCurrentPlayer());
            systemMessage.erase(systemMessage.begin());

            if (aiMove.first.first == RowColumn::Row) {
                // kill row
                int row = aiMove.first.second;
                int score = game.clearLine(RCMove(RowColumn::Row, row));
                string message = "AI killed row " + std::to_string(row + 1);
                message += " and got " + std::to_string(score) + " points.";
                systemMessage.push_back(message);
            } else {
                // kill column
                int col = aiMove.first.second;
                int score = game.clearLine(RCMove(RowColumn::Column, col));
                string message = "AI killed column " + std::string(1, (char)('A' + col));
                message += " and got " + std::to_string(score) + " points.";
                systemMessage.push_back(message);
            }

            if (game.isBoardEmpty()) break;
            else continue;
        }

        // read user input 
        char in;
        cin >> in;

        cout << ">> ";
        // handle user input 
        switch (in) {
            case 's': system("clear"); return;    
            case 'r':{
                game = RCGame("input.txt");
                systemMessage.clear();
                systemMessage.push_back("");
                systemMessage.push_back("");
                systemMessage.push_back("Game Restart!");
                break;
            }
            case 'h':{ 
                // get hint
                auto hint = RCGame::minimax(game, RCGame::MAX_ROW+RCGame::MAX_COLUMN, -RCGame::MAX_BOARD_SIZE, RCGame::MAX_BOARD_SIZE, game.getCurrentPlayer());
                string hintMessage = "Hint: ";
                if (hint.first.first == RowColumn::Row) {
                    hintMessage += "Row " + std::to_string(hint.first.second + 1) + ".";
                } else {
                    hintMessage += "Column " + std::string(1, (char)('A' + hint.first.second)) + ".";
                }
                    
                systemMessage.erase(systemMessage.begin());
                systemMessage.push_back(hintMessage);
                break;
            }
            case 'q': quitGame(); break;
            default: {
                // check if input is valid
                systemMessage.erase(systemMessage.begin());

                if (in >= '1' && in <= maxRow) {
                    // kill row
                    int row = in - '1';
                    int score = game.clearLine(RCMove(RowColumn::Row, row));

                    if (score == 0) {
                        systemMessage.push_back("Invalid input!");
                        break;
                    }
                    else {
                        string message = "Player " + std::to_string(2-game.getCurrentPlayer());
                        message += " killed row " + std::to_string(row + 1);
                        message += " and got " + std::to_string(score) + " points.";
                        systemMessage.push_back(message);
                    }
                                    
                } else if (in >= 'A' && in <= maxCol) {
                    // kill column
                    int col = in - 'A';
                    int score = game.clearLine(RCMove(RowColumn::Column, col));

                    if (score == 0) {
                        systemMessage.push_back("Invalid input!");
                        break;
                    }
                    else {
                        string message = "Player " + std::to_string(2-game.getCurrentPlayer());
                        message += " killed column " + std::string(1, (char)('A' + col));
                        message += " and got " + std::to_string(score) + " points.";
                        systemMessage.push_back(message);
                    }
                } else {
                    systemMessage.push_back("Invalid input!");
                }
            }
        }

        // check if game is over
        if (game.isBoardEmpty()) break;
    }

    // game over
    // print title
    system("clear");
    cout << "+-----------------------+" << endl;
    cout << "|     Player vs AI      |" << endl;
    cout << "+-----------------------+" << endl;
    cout << endl;

    game.printBoard();
    cout << endl;

    cout << "+----------Game Status----------+" << endl;
    cout << "Game Over!" << endl;
    cout << "Player got " << game.getPlayerScore(player) << " points." << endl;
    cout << "AI got " << game.getPlayerScore(1-player) << " points." << endl;
    
    if (game.getPlayerScore(player) > game.getPlayerScore(1-player)) {
        cout << "Player won!" << endl;
    }
    else if (game.getPlayerScore(player) < game.getPlayerScore(1-player)) {
        cout << "AI won!" << endl;
    } else {
        cout << "Draw!" << endl;
    }
    cout << "+-------------------------------+" << endl;
    cout << endl;

    cin.ignore();

    pressAnyKeyToContinue();
}

void RCGameManager::startRandomGame() {
    // write random game to input.txt
    std::ofstream inputFile;

    inputFile.open("input.txt");

    size_t row = rand() % (RCGame::MAX_ROW - 2) + 3;
    size_t column = rand() % (RCGame::MAX_COLUMN - 2) + 3;

    inputFile << row << " " << column << endl;
    for (size_t i = 0; i < row; i++) {
        for (size_t j = 0; j < column; j++) {
            inputFile << rand() % 2 << " ";
        }
        inputFile << endl;
    }

    inputFile.close();

    // start game
    startGame();
}

void RCGameManager::testAlphaBetaPruning() {
    // print title 
    system("clear");
    cout << "+---------------------------+" << endl;
    cout << "|  Test Alpha-Beta Pruning  |" << endl;
    cout << "+---------------------------+" << endl;
    cout << endl;

    // read input file and print board
    RCGame game("input.txt");
    game.printBoard();
    cout << endl;

    // start minimax search
    clock_t start = clock();

    auto result = RCGame::minimax(game, RCGame::MAX_ROW+RCGame::MAX_COLUMN, -RCGame::MAX_BOARD_SIZE, RCGame::MAX_BOARD_SIZE, game.getCurrentPlayer());

    clock_t end = clock();
    double searchTime = (double)(end - start) / CLOCKS_PER_SEC;

    // print result
    cout << "Result of Alpha-Beta Pruning " << endl;
    cout << "+-------------------------------+" << endl;
    cout << "Move: " << (result.first.first == RowColumn::Row ? "Row" : "Column") << " # " << result.first.second + 1 << endl;
    cout << (result.second >= 0 ? "+" : "-") << result.second << " points" << endl;
    cout << "Total run time = " << searchTime << " seconds." << endl;
    cout << "+-------------------------------+" << endl;
    cout << endl;
    
    // write result to output.txt
    std::ofstream outputFile;
    outputFile.open("output.txt");

    outputFile << (result.first.first == RowColumn::Row ? "Row" : "Column") << " # : " << result.first.second + 1 << endl;
    outputFile << (result.second >= 0 ? "+" : "-") << result.second << " points" << endl;
    outputFile << "Total run time = " << searchTime << " seconds." << endl;

    outputFile.close();

    pressAnyKeyToContinue();
}

std::string RCGameManager::highlightSelection(std::string text, int width) {
    string result = text;
    int textLength = text.length();

    //fill result with spaces 
    for (int i = 0; i < width - textLength - 1; ++i) {
        result += " ";
    }

    result = "\033[7m" + result + "\033[0m";
    return result;
}

void RCGameManager::printMenu(string title, std::vector<string> menu, size_t choice) {
    cout << "+----------------------------------------+" << endl;
    cout << "|                                        |" << endl;

    string titleLine = "|";
    int titleFill = (34 - title.length())/2;
    for (int i = 0; i < titleFill; ++i) titleLine += " ";
    titleLine = titleLine + "< " + title + " >"; 
    while(titleLine.length() < 41) titleLine += " ";
    titleLine += "|";
    cout << titleLine << endl;

    cout << "|                                        |" << endl;
    for (size_t i = 0; i < menu.size(); ++i) {
        string tmp = "| " + std::to_string(i+1) + ". ";

        if (i == choice) {
            tmp += highlightSelection(menu[i], 30);
            while(tmp.length() - 8 < 41) tmp += " ";
        } else {
            tmp += menu[i];
            while(tmp.length() < 41) tmp += " ";
        }

        tmp += "|";
        cout << tmp << endl;
    }
    cout << "|                                        |" << endl;
    cout << "| Press k and j to move up and down,     |" << endl;
    cout << "| and Space to confirm your selection.   |" << endl;
    cout << "|                                        |" << endl;
    cout << "+----------------------------------------+" << endl;
}

void RCGameManager::quitGame() {
    system("clear");

    cout << "+----------------------+" << endl;
    cout << "|       Goodbye!       |" << endl;
    cout << "+----------------------+" << endl;
    exit(0);
}
