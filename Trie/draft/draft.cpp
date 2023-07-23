#include <Phat/DepTraiSieuCapVuTru.h>
#include <stdio.h>
#include <conio.h>
using namespace std;

void resizeConsole(int width, int height);
void gotoxy(SHORT posX, SHORT posY);
void SetColor(int ForgC);
void ShowCur(bool a);
void SEARCH_ENGINE();
void DisableCtrButton(bool Close, bool Min, bool Max);
void menu(int& key);
void menuHistory(int& key);
void menuSearch(string &s);

// do cam vang luc lam cham tim 4 12 6 2 9 1 13
int main() {
    resizeConsole(1270, 600); // width, height
    DisableCtrButton(0, 0, 1); // 1: off, 0: on     lần lượt là tắt - thu nhỏ - full screen
    vector <string> history;
    /*Node* root = nullptr;
    History* rootHis = nullptr;
    Node* stopWord = nullptr;
    Title* newRoot = nullptr;
    loadStopword(stopWord);
    loadTitle(newRoot);
    map <string, int> result;
    createMap(result);
    init(root);*/
    int key = 0;
    string input;

    while (true) {
        system("cls");
        for (int i = 0; i < 30; ++i) {
            SetColor(i);
            SEARCH_ENGINE();
            Sleep(100);
        }
        SetColor(31);
        menu(key);

        if (key == 0) { // search
            menuSearch(input);
         //   mainSearch(input, result, root, stopWord, newRoot, history, rootHis);
           // sort(result);
        }

        else if (key == 1) { // history
            menuHistory(key);
            if (key == 0) {
                //view history
            }
            else if (key == 1) {
                //search history
            }
            else if (key == 2) {
                //delete history
            }
            else if (key == 3) {
                //exit
                continue;
            }
        }

        else if (key == 2) { // exit
            break;
        }
    }


    return 0;
}

void menuSearch(string& s) {
    SEARCH_ENGINE();
    SetColor(9);
    gotoxy(20, 18); cout << char(218);
    int i;
    for (i = 1; i < 114; ++i) {
        gotoxy(20 + i, 18); cout << char(196);
    }

    gotoxy(134, 18); cout << char(191);
    gotoxy(20, 19); cout << char(179);
    gotoxy(134, 19); cout << char(179);

    gotoxy(20, 20); cout << char(192);
    for (i = 1; i < 114; ++i) {
        gotoxy(20 + i, 20); cout << char(196);
    }
    gotoxy(134, 20); cout << char(217);

    SetColor(7);
    gotoxy(22, 19); getline(cin, s);
}

void menuHistory (int &key) {
    string* a = new string[4];
    SetColor(11);
    //print, search, delete
    gotoxy(63, 10); cout << "====== MENU HISTORY ======";
    a[0] = "VIEW";
    a[1] = "SEARCH";
    a[2] = "DELETE";
    a[3] = "EXIT";
    SetColor(4);
    gotoxy(70, 12); cout << a[0];
    SetColor(31);
    gotoxy(70, 14); cout << a[1];
    gotoxy(70, 16); cout << a[2];
    gotoxy(70, 18); cout << a[3];

    key = 0;
    int move;

    while (true) {
        move = _getch();
        if (move == 87 || move == 119 || move == 72) {
            key--;
            key = (key + 4) % 4;
            gotoxy(70, 12); cout << a[0];
            gotoxy(70, 14); cout << a[1];
            gotoxy(70, 16); cout << a[2];
            gotoxy(70, 18); cout << a[3];
            SetColor(4);
            gotoxy(70, 12 + key * 2); cout << a[key];
            SetColor(31);

        }
        if (move == 83 || move == 115 || move == 80) {
            key++;
            key = (key + 4) % 4;
            gotoxy(70, 12); cout << a[0];
            gotoxy(70, 14); cout << a[1];
            gotoxy(70, 16); cout << a[2];
            gotoxy(70, 18); cout << a[3];
            SetColor(4);
            gotoxy(70, 12 + key * 2); cout << a[key];
            SetColor(31);
        }

        if (move == 13) {
            system("cls");
            delete[] a;
            return;
        }
    }
}


void menu (int &key) {
    string* a = new string[3];
    a[0] = "SEARCH";
    a[1] = "HISTORY";
    a[2] = "EXIT";
    gotoxy(63, 16); cout << "WELCOME TO SEARCH ENGINE";
    SetColor(4);
    gotoxy(70, 18); cout << a[0];
    SetColor(31);
    gotoxy(70, 20); cout << a[1];
    gotoxy(70, 22); cout << a[2];

    int move;
    // W: 87, 119, 72 (phim len, w , W)
    // S: 83, 115, 80 (phim xuong, s, S)
    key = 0; // reset the key
    while (true) {
        move = _getch();
        if (move == 87 || move == 119 || move == 72) {
            key--;
            key = (key + 3) % 3;
            gotoxy(70, 18); cout << a[0];
            gotoxy(70, 20); cout << a[1];
            gotoxy(70, 22); cout << a[2];
            SetColor(4);
            gotoxy(70, 18 + key * 2); cout << a[key];
            SetColor(31);

        }
        if (move == 83 || move == 115 || move == 80) {
            key++;
            key = (key + 3) % 3;
            gotoxy(70, 18); cout << a[0];
            gotoxy(70, 20); cout << a[1];
            gotoxy(70, 22); cout << a[2];
            SetColor(4);
            gotoxy(70,18 + key * 2); cout << a[key];
            SetColor(31);
        }

        if (move == 13) {
            system("cls");
            delete[] a;
            return;
        }
    }
}

void SEARCH_ENGINE() {
    for (int i = 1; i <= 9; ++i) {
        if (i == 1) {
            gotoxy(6, 3); cout << char(201);
            for (int j = 1; j <= 140; ++j) {
                gotoxy(6 + j, 3); cout << char(205);
            }
            gotoxy(147, 3); cout << char(187);
        }
        else if (i == 9) {
            gotoxy(6, 11); cout << char(200);
            for (int j = 1; j <= 140; ++j) {
                gotoxy(6 + j, 11); cout << char(205);
            }
            gotoxy(147, 11); cout << char(188);
        }
        else {
            gotoxy(6, i + 2); cout << char(186);
            gotoxy(147, i + 2); cout << char(186);
        }
    }
    SetColor(4);
    gotoxy(8,4); cout << "   ====     =========        =         ====         ====  =        =        =========  ==      =      ====       ==   ==      =  =========" << endl;
    SetColor(12);
    gotoxy(8, 5); cout << "===     ==  ==              = =       ==   ==    ==       =        =        ==         = =     =   ==            ==   = =     =  ==" << endl;
    SetColor(6);
    gotoxy(8, 6);  cout << " ===        ==             =   =      ==    ==  =         =        =        ==         =  =    =  =              ==   =  =    =  ==" << endl;
    SetColor(2);
    gotoxy(8, 7); cout << "   ===      ========      =======     ==  ==    =         = ====== =        ========   =   =   =  =      ======  ==   =   =   =  ========" << endl;
    SetColor(9);
    gotoxy(8, 8); cout << "     ===    ==           =       =    ====      =         =        =        ==         =    =  =  =         =    ==   =    =  =  ==" << endl;
    SetColor(1);
    gotoxy(8, 9); cout << "==     ===  ==          =         =   ==  ==     ==       =        =        ==         =     = =   ==       =    ==   =     = =  ==" << endl;
    SetColor(13);
    gotoxy(8, 10); cout << "   ====     =========  =           =  ==    ==      ====  =        =        =========  =      ==      ======     ==   =      ==  =========" << endl;
}

/*
     ====     =========        =         ====         ====  =        =      =========  ==      =      ====       ==   ==      =  =========
  ===     ==  ==              = =       ==   ==    ==       =        =      ==         = =     =   ==            ==   = =     =  ==
   ===        ==             =   =      ==    ==  =         =        =      ==         =  =    =  =              ==   =  =    =  ==
     ===      ========      =======     ==  ==    =         = ====== =      ========   =   =   =  =      ======  ==   =   =   =  ========
       ===    ==           =       =    ====      =         =        =      ==         =    =  =  =         =    ==   =    =  =  ==
  ==     ===  ==          =         =   ==  ==     ==       =        =      ==         =     = =   ==       =    ==   =     = =  ==
     ====     =========  =           =  ==    ==      ====  =        =      =========  =      ==      ======     ==   =      ==  =========




*/

void SetColor(int ForgC) {
    WORD wColor;

    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (GetConsoleScreenBufferInfo(hStdOut, &csbi))
    {
        wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
        SetConsoleTextAttribute(hStdOut, wColor);
    }
    return;
}

void ShowCur(bool a) {
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO ConCurInf;

    ConCurInf.dwSize = 20;
    ConCurInf.bVisible = a;
    SetConsoleCursorInfo(handle, &ConCurInf);
}

void DisableCtrButton(bool Close, bool Min, bool Max)
{
    HWND hWnd = GetConsoleWindow();
    HMENU hMenu = GetSystemMenu(hWnd, false);

    if (Close == 1)
    {
        DeleteMenu(hMenu, SC_CLOSE, MF_BYCOMMAND);
    }
    if (Min == 1)
    {
        DeleteMenu(hMenu, SC_MINIMIZE, MF_BYCOMMAND);
    }
    if (Max == 1)
    {
        DeleteMenu(hMenu, SC_MAXIMIZE, MF_BYCOMMAND);
    }
}

void resizeConsole(int width, int height)
{
    HWND console = GetConsoleWindow();
    RECT r;
    GetWindowRect(console, &r);
    MoveWindow(console, r.left, r.top, width, height, TRUE);
}

void gotoxy(SHORT posX, SHORT posY)
{
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD Position;
    Position.X = posX;
    Position.Y = posY;

    SetConsoleCursorPosition(hStdout, Position);
}

// nhap vao 1 string userinput xong goi ham mainsearch... 
//goi ham sort
// lam xong het moi delete tree, stopword, tieu de 