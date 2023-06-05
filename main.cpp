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

unsigned random(unsigned mi, unsigned ma) {
    return rand()%(ma+1-mi)+mi;
}

template<typename T>

T r_choice(const std::vector<T> &vec) {
    return vec.at(random(0, vec.size()-1));
}

std::string str_tolower(std::string);
bool str_isalpha(std::string);
bool is_valid_guess(std::string, std::string);
void game();
void print_wordle(std::string, std::string);

int main() {
    srand(time(nullptr));

    char op{'y'};

    while(op == 'y') {
        system(CLEAR_SCREEN);

        std::cout << dye::green("\tWordle\n").invert() << std::endl;

        game();

        std::cout << std::endl;

        while(true) {
            std::cout << "Do you want to play again? [Y/y, N/n] > ";
            std::cin >> op;
            op = tolower(op);

            if(op == 'y' || op == 'n')
                break;
            else
                std::cout << "Invalid input\n";
        }
    }

    return 0;
}

std::string str_tolower(std::string str) {
    for(char &c: str)
        c = tolower(c);

    return str;
}

bool str_isalpha(std::string str) {
    for(const char &c: str)
        if(!isalpha(c))
            return false;
    return true;
}

bool is_valid_guess(std::string wordle_word, std::string guess) {
    if(!str_isalpha(guess)) {
        std::cout << "Invalid characters";
        return false;
    }

    if(guess.size() != wordle_word.size()) {
        std::cout << "Invalid length";
        return false;
    }

    return true;
}

void game() {
    bool player_won{false};

    std::string wordle_word{r_choice(words)}, guess{};

    std::cout << "   ";
    for(const char &c: wordle_word)
        std::cout << "_";
    std::cout << std::endl;

    for(size_t i{0}; i < wordle_word.size() && !player_won; i++) {
        fflush(stdin);
        std::cout << "\n > ";
        getline(std::cin, guess);
        guess = str_tolower(guess);

        std::cout << std::endl;

        if(is_valid_guess(wordle_word, guess)) {
            if(guess == wordle_word) {
                player_won = true;
            }

            std::cout << i+1 << ". ";
            print_wordle(wordle_word, guess);
        } else {
            i--;
        }

        std::cout << std::endl;
    }

    std::cout << std::endl;

    if(player_won)
        std::cout << "Good job!";
    else
        std::cout << "The word you didn't guess was " << dye::colorize(wordle_word, "yellow").invert() << std::endl;
        std::cout << "Better luck next time!";

    std::cout << std::endl;
}


void print_wordle(std::string wordle_word, std::string guess) {
    std::string corresp_colors;

    for(const char &c: wordle_word)
        corresp_colors += '_';

    for(size_t i{0}; i < wordle_word.size(); i++) {
        if(guess.at(i) == wordle_word.at(i)) {
            corresp_colors.at(i) = 'y';

            wordle_word.at(i) = '_';
        }
    }

    size_t pos{};

    for(size_t i{0}; i < wordle_word.size(); i++) {
        pos = wordle_word.find(guess.at(i));

        if(pos != std::string::npos) {
            corresp_colors.at(i) = 'g';

            wordle_word.at(pos) = '_';
        }
    }

    std::string color;

    for(size_t i{0}; i < wordle_word.size(); i++) {
        switch(corresp_colors.at(i)) {
            case 'y':
                color = "yellow";
                break;
            case 'g':
                color = "green";
                break;
            case '_':
                color = "vanilla";
        }

        std::cout << dye::colorize(guess.at(i), color).invert(); //highlight
    }
}
