#include <iostream>

#include <vector>
#include <string>
#include <time.h>

#include "include/color.hpp" //A library to apply color to the text in console
#include "include/words.hpp" //5757 words

#ifdef _WIN32
    #define CLEAR_SCREEN "cls"
#else
    #define CLEAR_SCREEN "clear"
#endif

unsigned random(unsigned min, unsigned max) {
    return rand()%(max+1-min)+min;
}

#define r_choice(vec) vec.at(random(0, vec.size()-1))

using namespace std;

void game();
string str_tolower(string);
bool str_isalpha(string);
bool is_valid_guess(string, string);
void print_wordle(string, string);

int main() {
    //system("title Wordle by rikzy");

    srand(time(nullptr));

    char op{'y'};

    while(op == 'y') {
        system(CLEAR_SCREEN);

        cout << dye::green("\tWordle\n").invert() << endl;

        game();

        cout << endl;

        while(true) {
            cout << "Do you want to play again? [Y/y, N/n] > ";
            cin >> op;
            op = tolower(op);

            if(op == 'y' || op == 'n')
                break;
            else
                cout << "Invalid input\n";
        }
    }

    return 0;
}

void game() {
    bool player_won{false};

    string wordle_word{r_choice(words)}, guess{};

    cout << "   ";
    for(const char &c: wordle_word)
        cout << "_";
    cout << endl;

    for(size_t i{0}; i < wordle_word.size() && !player_won; i++) {
        fflush(stdin);
        cout << "\n > ";
        getline(cin, guess);
        guess = str_tolower(guess);

        cout << endl;

        if(is_valid_guess(wordle_word, guess)) {
            if(guess == wordle_word) {
                player_won = true;
            }

            cout << i+1 << ". ";
            print_wordle(wordle_word, guess);
        } else {
            i--;
        }

        cout << endl;
    }

    cout << endl;

    if(player_won)
        cout << "Good job!";
    else
        cout << "The word you didn't guess was " << dye::colorize(wordle_word, "yellow").invert() << "\n"
                "Better luck next time!";

    cout << endl;
}

string str_tolower(string str) {
    for(char &c: str)
        c = tolower(c);

    return str;
}

bool str_isalpha(string str) {
    for(const char &c: str)
        if(!isalpha(c))
            return false;
    return true;
}

bool is_valid_guess(string wordle_word, string guess) {
    if(!str_isalpha(guess)) {
        cout << "Invalid characters";
        return false;
    }

    if(guess.size() != wordle_word.size()) {
        cout << "Invalid length";
        return false;
    }

    return true;
}

void print_wordle(string wordle_word, string guess) {
    string color{""};
    size_t pos{};

    for(size_t i{0}; i < guess.size(); i++) {
        pos = wordle_word.find(guess.at(i));

        if(pos != string::npos) {
            if(guess.at(i) == wordle_word.at(i))
                color = "yellow";
            else
                color = "green";

            wordle_word.at(pos) = '_';
        } else
            color = "vanilla";

        cout << dye::colorize(guess.at(i), color).invert(); //highlight
    }
}
