#include <bits/stdc++.h>
#include <conio.h>
#include <windows.h>
#include <time.h>

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

//Function to count the number of digits of a number
int numberOfDigits(int n)
{
    int count = 0;
    if (n == 0)
        return 1;
    while (n > 0)
    {
        n /= 10;
        count++;
    }
    return count;
}

//Function to color a number
void getColor(HANDLE h, int n)
{
        if (n == 0)
                SetConsoleTextAttribute(h, 7);
            else if (n == 2)
                    SetConsoleTextAttribute(h, 8);
                else if (n == 4)
                        SetConsoleTextAttribute(h, 15);
                    else if (n == 8)
                            SetConsoleTextAttribute(h, 10);
                        else if (n == 16)
                                SetConsoleTextAttribute(h, 9);
                            else if (n == 32)
                                    SetConsoleTextAttribute(h, 1);
                                else if (n == 64)
                                        SetConsoleTextAttribute(h, 11);
                                    else if (n == 128)
                                            SetConsoleTextAttribute(h, 3);
                                        else if (n == 256)
                                                SetConsoleTextAttribute(h, 12);
                                            else if (n == 512)
                                                    SetConsoleTextAttribute(h, 4);
                                                else
                                                        SetConsoleTextAttribute(h, 5);
        std::cout << n;
}

//Function to color the borders
void getColor(HANDLE h, std::string s)
{

    SetConsoleTextAttribute(h, 13);
    std::cout << s;
}

//Function print the Title
void printTitle(HANDLE h, int maxNum)
{
    SetConsoleTextAttribute(h, 2);
    for (int i = 0; i < (maxNum * 4 + 6) / 2; i++)
        std::cout << "*";
    std::cout << "2048";
    for (int i = 0; i < (maxNum * 4 + 6) / 2; i++)
        std::cout << "*";
    std::cout << std::endl;
}

//Function to print the table
void printTable(HANDLE h, int maxNum, int table[6][6])
{
    SetConsoleTextAttribute(h, 10);
    for (int i = 0; i < maxNum * 3 + 1; i++)
        getColor(h, "==");
    std::cout << std::endl;
    for (int i = 0; i < maxNum; i++)
    {
        getColor(h, "||");
        for (int j = 0; j < maxNum; j++)
            {
                int temp = numberOfDigits(table[i][j]);
                if (temp < maxNum)
                {
                    while (temp < maxNum)
                    {
                        std::cout << " ";
                        temp++;
                    }
                }
                if (table[i][j])
                    getColor(h, table[i][j]);
                else
                    std::cout << " ";
                if (j < maxNum - 1)
                    getColor(h, "||");
            }
        getColor(h, "||");
        std::cout << std::endl;
        for (int k = 0; k < maxNum * 3 + 1; k++)
            getColor(h, "==");
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

//Function to generate a number based on the player's Score
int generateNumber(int Score)
{
    int probability = (rand() % 100);
    switch(Score)
    {
        case 0 ... 999:
        {
            if (probability <= 85)
                return 0;
            else return 2;
        }
        case 1000 ... 4999:
        {
            if (probability <= 80)
                return 0;
            else if (probability <= 95)
                return 2;
                else return 4;
            break;
        }
        default:
        {
            if (probability <= 75)
                return 0;
            else if (probability <= 90)
                        return 2;
                else if (probability < 99)
                        return 4;
                    else return 8;
            break;
        }
    }
}

//Function to determine if there are any possible moves left or not
bool endGame(int table[6][6], int maxNum)
{
    for (int i = 0; i < maxNum; i++)
    {
        for (int j = 0; j < maxNum; j++)
        {
            if (!table[i][j])
                return false;
            else
            {
                if (!j)
                {
                    if (!i)
                    {
                        if (table[i][j] == table[i + 1][j] || table[i][j] == table[i][j + 1])
                            return false;
                    }
                    else if ( i == maxNum - 1)
                    {
                        if (table[i][j] == table[i - 1][j] || table[i][j] == table[i][j + 1])
                            return false;
                    }
                    else
                    {
                        if (table[i][j] == table[i + 1][j] || table[i][j] == table[i - 1][j] || table[i][j] == table[i][j + 1])
                            return false;
                    }
                }
                else if (j == maxNum - 1)
                {
                    if (!i)
                    {
                        if (table[i][j] == table[i + 1][j] || table[i][j] == table[i][j - 1])
                            return false;
                    }
                    else if (i == maxNum - 1)
                    {
                        if (table[i][j] == table[i - 1][j] || table[i][j] == table[i][j - 1])
                            return false;
                    }
                    else
                    {
                        if (table[i][j] == table[i + 1][j] || table[i][j] == table[i - 1][j] || table[i][j] == table[i][j - 1])
                            return false;
                    }
                }
                else
                    {
                        if (table[i][j] == table[i + 1][j] || table[i][j] == table[i - 1][j] || table[i][j] == table[i][j - 1] || table[i][j] == table[i][j - 1])
                            return false;
                    }
            }
        }
    }
    return true;
}

int main()
{
    while (true)
    {
        system("CLS");
        int Score = 0;
        int maxNum = 4;
        bool startFlag = true;
        bool newGame = true;
        int table[6][6];
        HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
        //Seed the random number generator
        srand((int)time(0));
        if (newGame)
        {
            newGame = false;

            //Print the Title.
            printTitle(h, maxNum);
            std::cout << std::endl;

            //Print a prompt to begin the game.
            std::cout << "Press any key to begin...";
            _getch();
            system("CLS");

            //Ask for Gamemode: 4x4, 5x5, 6x6?
            printTitle(h, maxNum);
            std::cout << std::endl;
            std::cout << "Press 1 for 4x4 mode, 2 for 5x5 mode, 5 for 6x6 mode." << "\t";
            char chooseGameMode;
            std::cin >> chooseGameMode;
            while (chooseGameMode != '1' && chooseGameMode != '2' && chooseGameMode != '3')
                {
                    std::cout << "Incorrect input. Please type again.";
                    std::cin >> chooseGameMode;
                }
            switch (chooseGameMode)
            {
                case '1':
                {
                    maxNum = 4;
                    break;
                }
                case '2':
                {
                    maxNum = 5;
                    break;
                }
                case '3':
                {
                    maxNum = 6;
                    break;
                }
            }

            //Generate a  matrix
            for (int i = 0; i < maxNum; i++)
                for (int j = 0; j < maxNum; j++)
                    table[i][j] = generateNumber(0);
            system("CLS");
        }

        //Begin the game!!!
        while (!newGame)
        {
            //Print the Title.
            printTitle(h, maxNum);

            //Print the Score.
            SetConsoleTextAttribute(h, 4);
            std::cout << std::endl << std::endl << "Your score: " << Score << std::endl << std::endl;

            //Print the matrix.
            printTable(h, maxNum, table);

            //Prompt for input.
            SetConsoleTextAttribute(h, 2);
            std::cout << "Choose a direction (Left, Right, Up, Down): ";

            //If input isn't appropriate, ask for another input.
            if (_getch() != 224)
                if (!startFlag)
                    while (true)
                    {
                        SetConsoleTextAttribute(h, 12);
                        std::cout << std::endl << "Incorrect direction! Please choose again (Left, Right, Up, Down): ";
                        if (_getch() == 224)
                            break;
                    }
                else _getch();
            startFlag = false;
            system("CLS");

            //Cases of Direction: Left, Right, Up, Down.
            switch (_getch())
            {
                case KEY_LEFT:
                    {
                        bool hasGeneratedANumber = false;
                        for (int i = 0; i < maxNum; i++)
                        {
                            int j = 0;
                            //Shift all 0s to the right.
                            while (j < maxNum - 1)
                            {
                                if (!table[i][j])
                                {
                                    int t = j + 1;
                                    while (!table[i][t])
                                        t++;
                                    if (t < maxNum)
                                        std::swap(table[i][j], table[i][t]);
                                }
                                j++;
                            }
                            j = 0;
                            //Count Score and shift all numbers to the left.
                            while (j < maxNum - 1)
                            {
                                if (table[i][j] == table[i][j + 1] && table[i][j] != 0)
                                {
                                    table[i][j] *= 2;
                                    Score += table[i][j];
                                    for (int k = j + 1; k < maxNum - 1; k++)
                                        table[i][k] = table[i][k + 1];
                                    table[i][maxNum - 1] = generateNumber(Score);
                                }
                                j++;
                            }
                            //Generate at most 1 number in a row.
                            //If 1 number has been generated, stop the function.
                            if (!hasGeneratedANumber)
                            {
                                int temp = maxNum - 1;
                                while (!table[i][temp])
                                    {
                                        table[i][temp] = generateNumber(Score);
                                        if (table[i][temp])
                                            {
                                                hasGeneratedANumber = true;
                                                break;
                                            }
                                        else temp--;
                                    }
                            }
                        }
                        break;
                    }
                case KEY_RIGHT:
                    {
                        bool hasGeneratedANumber = false;
                        for (int i = 0; i < maxNum; i++)
                        {
                            //Shift all 0s to the left.
                            int j = maxNum - 1;
                            while (j > 0)
                            {
                                if (!table[i][j])
                                {
                                    int t = j - 1;
                                    while (!table[i][t])
                                        t--;
                                    if (t >= 0)
                                        std::swap(table[i][j], table[i][t]);
                                }
                                j--;
                            }
                            //Count Score and shift all numbers to the right.
                            j = maxNum - 1;
                            while (j > 0)
                            {
                                if (table[i][j] == table[i][j - 1] && table[i][j] != 0)
                                {
                                    table[i][j] *= 2;
                                    Score += table[i][j];
                                    for (int k = j - 1; k >= 0; k--)
                                        table[i][k] = table[i][k - 1];
                                    table[i][0] = generateNumber(Score);
                                }
                                j--;
                            }
                            //Generate at most 1 number in a row.
                            //If 1 number has been generated, stop the function.
                            if (!hasGeneratedANumber)
                            {
                                int temp = 0;
                                while (!table[i][temp])
                                    {
                                        table[i][temp] = generateNumber(Score);
                                        if (table[i][temp])
                                            {
                                                hasGeneratedANumber = true;
                                                break;
                                            }
                                        else temp++;
                                    }
                            }
                        }
                        break;
                    }
                case KEY_UP:
                    {
                        bool hasGeneratedANumber = false;
                        for (int j = 0; j < maxNum; j++)
                        {
                            //Shift all 0s to the bottom.
                            int i = 0;
                            while (i < maxNum - 1)
                            {
                                if (!table[i][j])
                                {
                                    int t = i + 1;
                                    while (!table[t][j])
                                        t++;
                                    if (t < maxNum)
                                        std::swap(table[i][j], table[t][j]);
                                }
                                i++;
                            }
                            //Count Score and shift all numbers to the top.
                            i = 0;
                            while (i < maxNum - 1)
                            {
                                if (table[i][j] == table[i + 1][j] && table[i][j] != 0)
                                {
                                    table[i][j] *= 2;
                                    Score += table[i][j];
                                    for (int k = i + 1; k < maxNum - 1; k++)
                                        table[k][j] = table[k + 1][j];
                                    table[maxNum - 1][j] = generateNumber(Score);
                                }
                                i++;
                            }
                            //Generate at most 1 number in a column.
                            //If 1 number has been generated, stop the function.
                            if (!hasGeneratedANumber)
                            {
                                int temp = maxNum - 1;
                                while (!table[temp][j])
                                    {
                                        table[temp][j] = generateNumber(Score);
                                        if (table[temp][j])
                                            {
                                                hasGeneratedANumber = true;
                                                break;
                                            }
                                        else temp--;
                                    }
                            }
                        }
                        break;
                    }
                case KEY_DOWN:
                    {
                        bool hasGeneratedANumber = false;
                        for (int j = 0; j < maxNum; j++)
                        {
                            //Shift all 0s to the top.
                            int i = maxNum - 1;
                            while (i > 0)
                            {
                                if (!table[i][j])
                                {
                                    int t = i - 1;
                                    while (!table[t][j])
                                        t--;
                                    if (t >= 0)
                                        std::swap(table[i][j], table[t][j]);
                                }
                                i--;
                            }
                            //Count Score and shift all the numbers to the bottom.
                            i = maxNum - 1;
                            while (i > 0)
                            {
                                if (table[i][j] == table[i - 1][j] && table[i][j] != 0)
                                {
                                    table[i][j] *= 2;
                                    Score += table[i][j];
                                    for (int k = i - 1; k >= 0; k--)
                                        table[k][j] = table[k - 1][j];
                                    table[0][j] = generateNumber(Score);
                                }
                                i--;
                            }
                            //Generate at most 1 number in a column.
                            //If 1 number has been generated, stop the function.
                            if (!hasGeneratedANumber)
                            {
                                int temp = 0;
                                while (!table[temp][j])
                                    {
                                        table[temp][j] = generateNumber(Score);
                                        if (table[temp][j])
                                            {
                                                hasGeneratedANumber = true;
                                                break;
                                            }
                                        else temp++;
                                    }
                            }
                        }
                        break;
                    }
            }
            if (endGame(table, maxNum))
            {
                //Print the Title.
                printTitle(h, maxNum);

                //Print the table.
                printTable(h, maxNum, table);

                //Print the Game Over prompt and ask for new game.
                newGame = true;
                SetConsoleTextAttribute(h, 4);
                std::cout << std::endl << std:: endl<< "GAME OVER!!!";
                std::cout << std::endl << "Your total score: " << Score << std::endl << std::endl;
                system("pause");
                break;
            }
        }
    }
}

