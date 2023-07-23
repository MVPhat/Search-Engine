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
            result.clear();
            input.clear();
            while (input == "") {
                menuSearch(input);
            }
            system("cls");
            clock_t t;
            t = clock();
            mainSearch(input, result, rootTrie, stopWord, rootTitle, history, rootHis);
            t = clock() - t;
            //cout << "\nTime: " << ((float)t) / CLOCKS_PER_SEC << " seconds\n\n";
            cout << result.size() << " results in " << ((float)t) / CLOCKS_PER_SEC << " seconds...\n\n\n";
            sort(result, input);
            insertHistory(rootHis, input);
            writeHistory(input, history);
            result.clear();
            system("pause");
            system("cls");
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
                query.clear();
                cout << "Search History: ";
                while (query == "") {
                    getline(cin, query);
                }
                printAutoSugg(rootHis, query, result, rootTrie, stopWord, rootTitle, history);
            }
            else if (key == 2) {
                //delete history
                deleteHistory(rootHis, history);
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

    return 0;
}
