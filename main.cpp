#include "searchEngine.h"

int main()
{
    // set console screen
    resizeConsole(1270, 600); // width, height
    DisableCtrButton(0, 0, 1); // 1: off, 0: on     lần lượt là tắt - thu nhỏ - full screen

    // khởi tạo các biến ban đầu
    vector <string> history;
    Node* rootTrie = nullptr;
    History* rootHis = nullptr;
    Node* stopWord = nullptr;
    Title* rootTitle = nullptr;
    map <string, int> result;
    
    // load data
    loadStopword(stopWord);
    loadTitle(rootTitle);
    createMap(result);
    init(rootTrie);

    // biến menu
    int key = 0;
    string input;

    while (true) {
        system("cls");
        SEARCH_ENGINE();
        SetColor(31);
        menu(key);

        if (key == 0) { // search
            menuSearch(input);
            system("cls");
            mainSearch(input, result, rootTrie, stopWord, rootTitle, history, rootHis);
            sort(result);
            insertHistory(rootHis, input);
            writeHistory(input, history);
        }

        else if (key == 1) { // history
            system("cls");
            menuHistory(key);
            if (key == 0) {
                //view history
                printHistory(history);
            }
            else if (key == 1) {
                //search history
                string query;
                cout << "Search History: ";
                getline(cin, query);
                printAutoSugg(rootHis, query);
            }
            else if (key == 2) {
                //delete history
                deleteHistory(rootHis);
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

    deleteTree(rootTrie);
    deleteTree(stopWord);
    deleteTreeHis(rootHis);


    system("pause");

    return 0;
}