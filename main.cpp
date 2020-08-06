#include <iostream>
#include <vector>
#include <ctime>

int getRandomNumber(int min, int max)
{
    static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
    return static_cast<int>(rand() * fraction * (max - min + 1) + min);
}

int getUserNumber()
{
    int user_number{ 0 };
    do
    {
        std::cout << "Enter a number: ";
        std::cin >> user_number;

        if(std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(INT_MAX, '\n');
            user_number = 0;
        }

    } while(user_number < 1000 || user_number > 9999);

    return user_number;
}

std::string converUserInput(int user_number) { return std::to_string(user_number); }

bool isGuessIndex(const std::vector<int> &guess_figures, int index)
{
    for(const auto &element : guess_figures)
        if(element == index)
            return true;

    return false;
}

void figuresRightPlace(const std::string &user_number, const std::string &necessary_number)
{
    int right_places{ 0 };

    for(int figure{ 0 }; figure < 4; ++figure)
        if(necessary_number[figure] == user_number[figure])
            ++right_places;

    std::cout << "F_R_P:" << right_places << "\n";
}

void guessFigures(const std::string &user_number, const std::string &necessary_number)
{
    std::vector<int> guess_figures;
    guess_figures.reserve(4);

    int quantity_guess_figures{ 0 };

    for(int u_n{ 0 }; u_n < 4; ++u_n)
        for(int n_n{ 0 }; n_n < 4; ++n_n)
        {
            if(isGuessIndex(guess_figures, n_n))
                continue;

            if(user_number[u_n] == necessary_number[n_n])
            {
                guess_figures.push_back(n_n);
                ++quantity_guess_figures;
                break;
            }
        }

    std::cout << "F_G:" << quantity_guess_figures << "\t";
}

void giveTip(const std::string &user_number, const std::string &necessary_number)
{
    guessFigures(user_number, necessary_number);
    figuresRightPlace(user_number, necessary_number);
}

void play()
{
    std::string necessary_number = std::to_string(getRandomNumber(1000, 9999));
    std::string user_number{ " " };
    int enter_number{ 0 };

    do
    {
        enter_number = getUserNumber();
        user_number = converUserInput(enter_number);
        giveTip(user_number, necessary_number);

    } while(necessary_number != user_number);

    std::cout << "You guessed! Thank you for playing\n";
}

int main()
{
    srand(static_cast<unsigned int>(time(0)));
    rand();
    play();
    return 0;
}
