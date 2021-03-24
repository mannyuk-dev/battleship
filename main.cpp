#include "headers/Board.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <string.h>
#include <map>
#include <vector>
#include <ctime>
#include <limits>
#include <string>
#include <iomanip>


//Colors:
            //    \E[0;37m: Foreground, light grey
            //    \E[0;31m: Foregound, red
            //    \E[0;37m: Foregound, white
            //    \E[44m: Background, blue
            //    \E[47m: Background, light grey
            //    \E[0m: Resets to default colors


using namespace std;

std::vector<std::string> split(const std::string& str, const std::string& delim) {
    std::vector<std::string> tokens;
    size_t prev = 0, pos = 0;
    do
    {
        pos = str.find(delim, prev);
        if (pos == std::string::npos) pos = str.length();
        std::string token = str.substr(prev, pos - prev);
        if (!token.empty()) tokens.push_back(token);
        prev = pos + delim.length();
    } while (pos < str.length() && prev < str.length());
    return tokens;
}


//the singleton class typically defines the `get_instance` method that serves as an
//'constructor' thereby letting 'clients' access the same instance of the class
//by doing this no matter which instance is accessed it always points back to the 'one' instance

//potentially considered perhaps an antipattern due to initial possible overused and its potential 
//to introduce unnecessary issues in situations where an entire instance of a class may not be required
//in addition it introduces a possible 'global state' into solution.

class singleton {
private:
    struct Board {
        string height;
        string width;
    };
    struct Carrier {
        string length;
        string name;
    };
    struct Battleship {
        string length;
        string name;
    };
    struct Submarine {
        string length;
        string name;
    };
    struct Destroyer {
        string length;
        string name;
    };
    struct Patrol {
        string length;
        string name;
    };

    Board board_;

    const int width = 10;
    const int height = 10;

    singleton(const std::string reference, const int value) :
        reference_(reference), //initialise the variable 'singleton::reference_' with the value passed as 'reference' 
        value_(value)
    {
        //possible constructor code
        cout << "\nsingleton contructor code started";
    }

    static singleton* inst_; //a pointer to the 'one' cached (single) instance

protected: //essentially, protected stands for that members of subclasses are also allowed
    std::string reference_;
    int value_;

public:

    struct board_data
    {
        Board board;
        //Boat boat;
    };

    struct carrier_data {
        Carrier carrier;
    };

    struct battleship_data {
        Battleship battleship;
    };

    struct submarine_data {
        Submarine submarine;
    };

    struct destroyed_data {
        Destroyer destroyer;
    };

    struct patrol_data {
        Patrol patrol;
    };

    static singleton* get_instance(const std::string& reference, const int& value);

    singleton* read_config(string config);

    std::string reference() const {
        return reference_;
    }

    int value() const {
        return value_;
    }

    //used two config files initially but managed to reduce it to using one by spliting the boat file using split function

    board_data read_board() {
        board_data data = board_data();
        std::string line;
        std::ifstream boatFile("adaship_config.ini");
        if (boatFile.is_open()) {
            while (getline(boatFile, line)) {
                std::vector<std::string> parts = split(line, "=");
                if (parts[0] == "board") {
                    Board board = Board();
                    board.height = split(parts[1], "X")[0];
                    board.width = split(parts[1], "X")[1];
                    data.board = board;
                }
            }

            boatFile.close();
        }

        return data;
    }

    carrier_data read_carriers() {
        carrier_data data = carrier_data();
        std::string line;
        std::ifstream boatFile("adaship_config.ini");
        if (boatFile.is_open()) {
            while (getline(boatFile, line)) {
                std::vector<std::string> parts = split(line, "=");
                if (parts[0] == "carrier") {
                    Carrier carrier = Carrier();
                    carrier.name = parts[0];
                    carrier.length = parts[1];
                    data.carrier = carrier;
                }
            }
            boatFile.close();
        }

        return data;
    }

    battleship_data read_battleships() {
        battleship_data data = battleship_data();
        std::string line;
        std::ifstream boatFile("adaship_config.ini");
        if (boatFile.is_open()) {
            while (getline(boatFile, line)) {
                std::vector<std::string> parts = split(line, "=");
                if (parts[0] == "battleship") {
                    Battleship battleship = Battleship();
                    battleship.name = parts[0];
                    battleship.length = parts[1];
                    data.battleship = battleship;
                }
            }
            boatFile.close();
        }

        return data;
    }

    submarine_data read_submarines() {
        submarine_data data = submarine_data();
        std::string line;
        std::ifstream boatFile("adaship_config.ini");
        if (boatFile.is_open()) {
            while (getline(boatFile, line)) {
                std::vector<std::string> parts = split(line, "=");
                if (parts[0] == "submarine") {
                    Submarine submarine = Submarine();
                    submarine.name = parts[0];
                    submarine.length = parts[1];
                    data.submarine = submarine;
                }
            }
            boatFile.close();
        }

        return data;
    }

    destroyed_data read_destroyers() {
        destroyed_data data = destroyed_data();
        std::string line;
        std::ifstream boatFile("adaship_config.ini");
        if (boatFile.is_open()) {
            while (getline(boatFile, line)) {
                std::vector<std::string> parts = split(line, "=");
                if (parts[0] == "destroyer") {
                    Destroyer destroyer = Destroyer();
                    destroyer.name = parts[0];
                    destroyer.length = parts[1];
                    data.destroyer = destroyer;
                }
            }
            boatFile.close();
        }

        return data;
    }

    patrol_data read_patrols() {
        patrol_data data = patrol_data();
        std::string line;
        std::ifstream boatFile("adaship_config.ini");
        if (boatFile.is_open()) {
            while (getline(boatFile, line)) {
                std::vector<std::string> parts = split(line, "=");
                if (parts[0] == "patrol") {
                    Patrol patrol = Patrol();
                    patrol.name = parts[0];
                    patrol.length = parts[1];
                    data.patrol = patrol;
                }
            }
            boatFile.close();
        }

        return data;
    }
};

singleton* singleton::inst_ = nullptr;


singleton* singleton::get_instance(const std::string& reference, const int& value) {

    if (inst_ == nullptr) {
        inst_ = new singleton(reference, value); //no previous instance stored, create and store the original
    }
    return inst_; //return the stored instance
};




//Gets user input for where they want to place the battleship and returns a string
string get_ship_placement(int shipLength, string shipName) {
    string place;

    cout << "Length of ship: " << shipLength << endl;
    cout << "Length of ship: " << shipName<< endl;
    cout << "Location and heading for ship placement (ex. D4E): ";
    cin >> place;

    return place;
}


int main() {

    singleton* instanceFoo = singleton::get_instance("foo", 101);
    singleton* instanceBar = singleton::get_instance("bar", 101);

    singleton::board_data data = instanceFoo->read_board();
    singleton::carrier_data cdata = instanceFoo->read_carriers();
    singleton::battleship_data bdata = instanceFoo->read_battleships();
    singleton::destroyed_data ddata = instanceFoo->read_destroyers();
    singleton::submarine_data sdata = instanceFoo->read_submarines();
    singleton::patrol_data pdata = instanceFoo->read_patrols();


    //Passes values from ada config file to create the boards sizing 

    int width = stoi(data.board.width);
    int height = stoi(data.board.height);

    //Read carriers
    int carrier_length = stoi(cdata.carrier.length);
    string carrier_name = cdata.carrier.name;

    // Read battleships
    int battleship_length = stoi(bdata.battleship.length);
    string battleship_name = bdata.battleship.name;

    // Read destroyers
    int destroyer_length = stoi(ddata.destroyer.length);
    string destroyer_name = ddata.destroyer.name;

    // Read submarines
    int submarine_length = stoi(sdata.submarine.length);
    string submarineName = sdata.submarine.name;

    // Read patrols
    int patrol_length = stoi(pdata.patrol.length);
    string patrol_name = pdata.patrol.name;

    string guess, place; //Initialze variables
    int rand1, rand2;
    int ship_length_array[] = { carrier_length, battleship_length, destroyer_length,submarine_length,patrol_length };
    string ship_names_array[] = { carrier_name , battleship_name , destroyer_name , submarineName, patrol_name };

    //Put this all in a menu function

    cout << "\n" << "    ======= WELCOME TO BATTLESHIP! =======" << "\n\n\n";
    //start menu
    string user;
    cout << "Enter 1 To view rules" << "\n";
    cout << "Enter any letter to start the game" << "\n";
    cin >> user;
    system("clear");

    if (user == "1") {

        cout << "\nGame symbols" << endl;
        cout << "    Water/Empty Space: " << "\E[0;37m" << "\E[44m" << "0 " << "\E[0m" << endl;
        cout << "    Missed Guess: " << "\E[0;31m" << "\E[44m" << "# " << "\E[0m" << endl;
        cout << "    Battleship Hit: " << "\E[0;31m" << "\E[47m" << "X " << "\E[0m" << endl;
        cout << "    Battleship Not Hit: " << "\E[1;37m" << "\E[47m" << "+ " << "\E[0m" << endl;
        cout << "Entering coordinates" << "\n";
        cout << "example - enter B2E which targets coordinates B2 and the ship is placed east: " <<"\n";

        int clear;
        cout << "click any number to continue: ";
        cin >> clear;
        system("clear");
        //click keyboard to clear and continue 
    }
    else if(user == "2"){
        system("clear");
        cout << "You quit the game";
    }


    string type;
    cout << "Enter number for specifc game type" << "\n";
    cout << "Enter 1: Player vs Player" << "\n";
    cout << "Enter 2: Player vs CPU" << "\n";
    cin >> type;

    if (type == "1") {
        while (type == "1") {
           //player 1
           string place;
           cout << "You are playing player vs player" << "\n";
           cout << "Player 1 place ships" << "\n";

           Board player1_grid;
           player1_grid.draw_grid(1);
           for (int i = 0; i < 5; i++) {
               place = get_ship_placement(ship_length_array[i], ship_names_array[i]);
               player1_grid.place_ship(place[0], place[1], place[2], ship_length_array[i]);
           }

           system("clear");
           cout << "Player 1 has placed. Leave so Player 2 can place ships. DO NOT scroll up\n";

           Board player2_grid;
           player2_grid.draw_grid(1);
           for (int i = 0; i < 5; i++) {
               place = get_ship_placement(ship_length_array[i], ship_names_array[i]);
               player2_grid.place_ship(place[0], place[1], place[2], ship_length_array[i]);
           }

           int count = 1;
           string next;

           while (true) {
               if (player1_grid.is_loser() == 1) {
                   cout << "\n\nPLAYER 2 WINS!!!" << endl;
                   break;
               }
               if (player2_grid.is_loser() == 1) {
                   cout << "\n\nPLAYER 1 WINS!!!" << endl;
                   break;
               }
               else if (count % 2 == 1) {
                   cout << "It is player 1s turn to guess. Input any character and press enter to continue.";
                   cin >> next;
                   for (int i = 0; i < 100; i++) {
                       cout << " " << endl;
                   }
                   cout << "\nYour Board: " << endl;
                   player1_grid.draw_grid(1);
                   cout << "\nYour Guesses on Player 2s Board: " << endl;
                   player2_grid.draw_grid(0);
                   cout << "Player 1 New Guess (ex. D4): ";
                   cin >> guess;
                   cout << "\nYour Updated Guesses:" << endl;
                   player2_grid.player_guess(guess[0], guess[1]);
                   count++;
               }
               else if (count % 2 == 0) {
                   cout << "It is player 2s turn to guess. Input any character and press enter to continue.";
                   cin >> next;
                   for (int i = 0; i < 100; i++) {
                       cout << " " << endl;
                   }
                   cout << "\nYour Board: " << endl;
                   player2_grid.draw_grid(1);
                   cout << "\nYour Guesses on Players 1s Board: " << endl;
                   player1_grid.draw_grid(0);
                   cout << "Player 2 New Guess (ex. D4): ";
                   cin >> guess;
                   cout << "\nYour Updated Guesses:" << endl;
                   player1_grid.player_guess(guess[0], guess[1]);
                   count++;
               }
           }
        }
    }
    else if (type == "2") {
        while (type == "2") {
            string place;
            cout << "You are playing player vs computer" << "\n";
            cout << "Your turn to place ships on the board" << "\n";

            Board player1_grid;
            player1_grid.draw_grid(1);
            for (int i = 0; i < 5; i++) {
                place = get_ship_placement(ship_length_array[i], ship_names_array[i]);
                player1_grid.place_ship(place[0], place[1], place[2], ship_length_array[i]);
            }

            system("clear");
            cout << "Player has placed ships. Computer is now placing ships";
            //Computer place ships method

            Board computer_grid;
            computer_grid.draw_grid(1);
            for (int i = 0; i < 5; i++) {
                computer_grid.randomplace_ships(ship_length_array[i]);
            }

            int count = 1;
            string next;

            while (true) {
                if (player1_grid.is_loser() == 1) {
                    cout << "\n\nComputer Wins" << endl;
                    break;
                }
                if (computer_grid.is_loser() == 1) {
                    cout << "\n\nPLAYER 1 WINS!!!" << endl;
                    break;
                }
                else if (count % 2 == 1) {
                    cout << "It is your turn to guess. Input any character and press enter to continue.";
                    cin >> next;
                    for (int i = 0; i < 100; i++) {
                        cout << " " << endl;
                    }
                    cout << "\nYour Board: " << endl;
                    player1_grid.draw_grid(1);
                    cout << "\nYour Guesses on Player 2s Board: " << endl;
                    computer_grid.draw_grid(0);
                    cout << "Player 1 New Guess (ex. D4): ";
                    cin >> guess;
                    cout << "\nYour Updated Guesses:" << endl;
                    computer_grid.player_guess(guess[0], guess[1]);
                    count++;
                }
                else if (count % 2 == 0) {
                    cout << "It is player 2s turn to guess. Input any character and press enter to continue.";
                    cin >> next;
                    for (int i = 0; i < 100; i++) {
                        cout << " " << endl;
                    }
                    cout << "\nYour Board: " << endl;
                    computer_grid.draw_grid(0);
                    //Hide the computer grid to the user
                    cout << "\nYour Guesses on the Computers Board : " << endl;
                    player1_grid.draw_grid(0);
                    cout << "computer New Guess (ex. D4): ";
                    cin >> guess;
                    cout << "\nYour Updated Guesses:" << endl;
                    //player1_grid.player_guess(guess[0], guess[1]);
                    //player guess needs to be computer guess
                    count++;
                }
            }

        }
    }
    else {
        cout << "enter correct value: ";
        cin >> type;
        //run game method again
    }
    cout << "\n\nThank you for playing." << endl;

    return 0;
}
