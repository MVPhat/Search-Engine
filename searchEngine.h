#ifndef _SEARCHENGINE_H_
#define _SEARCHENGINE_H_

#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <vector>
#include <filesystem>
#include <sstream>
#include <algorithm>
#include <stack>
#include <Windows.h>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <time.h>
#include <mmsystem.h>

using namespace std;

struct Node
{
	Node* Pre = nullptr;
	map<char, Node*> child;
	map<string, vector<long>> position; //string : fileName, vector : position
	bool endOfNode = false;//check
	bool iSCommon = false;//check
};

//used for title trie

struct Title {
	map<char, Title*> child;
	bool endOfNode = false;
	map<string, int> filename;
};

//used for history trie

struct History {
	map<char, History*> child;
	bool endOfNode = false;
};

//MAIN SEARCH
void mainSearch(string userInput, map<string, int>& result, Node* root, Node* stopWord, Title* newRoot, vector<string>& history, History*& rootHis);


//UTILITY

void gotoxy(int x, int y);

//CREATING TRIE / BUILD TRIE / TRIE FUNCTIONS
void createMap(map<string, int>& result);
Node* getNewTrieNode();
void filter(string& s); //turn uppercase to lowercase
void insert(string s, long nums, Node*& root, string nameOfFile); //nums: position of character, nameOfFile: fine name
void display(Node* root, string word = {}); //print out trie
void deleteTree(Node*& root);
bool searchString(Node* root, string s); //search function used when filter out stopwords
bool searchString2(Node* root, string s, map<string, int>& m); //if string s is found, insert result to map m (string: file name, int: score)
void deleteString(Node* root, string s);

//READ FILE

bool isNumber(char a);
bool isChar(char a);
bool isSpecialChar(char a);
void inputSentence(Node*& root, long& num, string filename, string sentence); //read sentence to trie
void inputFile(Node*& root, string filename); //get sentences from a file text
void init(Node*& root); //get file name 

//STOPWORD

void insertStopword(string s, Node*& root); //creating a new trie containing stopwords
void loadStopword(Node*& root); //load stopwords and insert to stopword trie in a text file

//OPERATION 1: SEARND AND

//truyền vào A AND B
void searchAND(Node* root, string s, map<string, int>& res); 

//OPERATION 2: SEARCH OR

//truyền vào A OR B
void SearchOR(Node* root, string querry, map <string, int>& result);

//OPERATION 3: SEARCH -

//truyền vào -A
bool searchString4(Node* root, string s, vector<string>& nameOfFile);
void specialCase3(string userInput, Node* root, map<string, int>& result); //main function

//OPERATION 4: SEARCH INTITLE

//truyền vào intitle:...
void insertTitle(string s, Title*& root, string name); //insert title to trie
void loadTitle(Title*& root); //read file name
bool searchTitle(Title* root, string s, map<string, int>& m); //search string s in trie and update result to map m(string: file name, int: score)
void searchIntitle(Title* root, string query, map<string, int>& result); //main function for operation 4

//OPERATION 5: SEARCH +

//truyền vào +A
void SearchPlus(Node* root, string querry, map <string, int>& result);

//OPERATION 6

//search bình thường sau đó kiểm tra có phải file txt không nếu có cụm "filetype:txt". Lúc search nhớ bỏ cụm "filetype:txt" ra
void specialCase6(string type, map<string, int>& result);
void SearchType(Title* root, string query, map<string, int>& result);

//OPERATION 7: SEARCH $

void searchprice(Node* root, string s, map<string, int>& result);

//OPERATION 8: SEARCH HASHTAG

void searchHashtag(Node* root, string querry, map<string, int>& result);

//OPERATION 9: EXACT MATCH

//truyền vào "..."
bool inputIndex(Node* root, string s, vector<int>& sortList, string nameOfFile);
bool searchString3(Node* root, string s, string nameOfFile, int& cnt);
bool specialCase9_ss2(vector<int> sortList, int count, int& cnt);
bool specialCase9_ss1(Node* root, string importantString, string nameOfFile, int& cnt);
string specialCase9(string userInput, string fileName, Node* root, int& cnt);
bool searchTmp(Node* root, string s, map<string, int>& m);
void searchExactMatch(Node* root, string s, map<string, int>& result); //main function

//OPERATION 10: sEARCH WILDCARDS/UNKNOWN

void searchwildcards(Node* root, string s, map<string, int>& res, vector<string>& filename);
void removeDuplicated(vector<string>& filename);
void searchInfileName(Node* root, string before, string after, vector<string>& filenaeme);
void findFilename(Node* root, string before, string after, vector<string>& filename);
void saveope10(Node* root, string s, map<string, int>& res);

//OPERATION 11: SEARCH WITHIN A RANGE

//truyền vào number..number
void inRange(Node* root, string num, double low, double high, map<string, int>& m, string query);
void searchRange(Node* root, string querry, map<string, int>& result); //main function

//OPERATION 12: SYNONYM

//truyền vào ~A
vector<string> getSyn(string s);
void searchSynonym(Node* root, string s, map<string, int>& res); //main function

//PROCESSING WITH MAP

/*Idea là tạo một map<string, int> result để chứa tên file và điểm tương ứng mà file có được
sau đó print kết quả theo chiều từ file cao điểm xuống cho đủ năm file*/

bool cmp(pair<string, int>& a, pair<string, int>& b);
void sort(map<string, int>& M); //sort map from highest score to lowest score and print out file name

//HISTORY

void writeHistory(string s, vector<string>& history);
string printHistory(vector<string>& history);
void insertHistory(History*& root, string s);
bool searchHistory(History* root, string s);
void readHistoryToTrie(History*& root, vector<string>history);
void displayHis(History* root, string word = {});
vector<string> suggestionRec(History* root, string s, vector<string>& rec);
void printAutoSugg(History* root, string s);
void deleteTreeHis(History*& root);
void deleteHistory(History*& root);


//MENU - SCREEN

void SetColor(int ForgC);
void DisableCtrButton(bool Close, bool Min, bool Max);
void resizeConsole(int width, int height);
void ShowCur(bool a);
void SEARCH_ENGINE();
void menu(int& key);
void menuHistory(int& key);
void menuSearch(string& s);

void title();
void Menu();
void MenuHistory();
void searchbar(string& key);


#endif // !_SEARCHENGINE_H_
