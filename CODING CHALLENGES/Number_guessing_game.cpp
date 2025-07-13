#define _WIN32_WINNT 0x0600
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "rang.hpp"
using namespace rang;
using namespace std;

int main()
{
    char playAgain = 'y';
    srand(time(0));

    system("chcp 65001");

    while (playAgain == 'y' || playAgain == 'Y')
    {
        cout << fg::magenta << "\n🎲 Welcome to the Number Guessing Game------" << endl;
        cout << "\nChoose Difficulty Levels: " << endl;
        cout << "1. Easy -> 1 to 20\n2. Medium -> 1 to 100\n3. Hard -> 1 to 1000" << endl;

        int max;
        int max_attempts;

        int choice;
        cout << "\nYour Choice(1/2/3) = ";
        cin >> choice;

        if (choice == 1)
        {
            max = 20;
            max_attempts = 5;
        }
        else if (choice == 2)
        {
            max = 100;
            max_attempts = 7;
        }
        else
        {
            max = 1000;
            max_attempts = 15;
        }

        int num = (rand() % max) + 1;

        int n;
        cout << fg::yellow << "Enter your guess: ";

        int attempts = 0;

        while (n != num && attempts < max_attempts)
        {
            cin >> n;
            attempts++;

            if (n < num)
            {
                cout << fg::red << "Too low! Try again." << endl;
            }

            else if (n > num)
            {
                cout << fg::red << "Too high! Try again." << endl;
            }
            else
            {
                break;
            }
        }
        if (n == num)
        {
            cout << fg::green << "🎉 You guessed it in " << attempts << " attempts!" << endl;
        }
        else
        {
            cout << fg::red << "💥 You've used all your attempts! The number was:" << num << endl;
        }

        cout << fg::blue << "Do You Want to Play Again? (y/n): ";
        cin >> playAgain;
    }
    return 0;
}