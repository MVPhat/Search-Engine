#include "searchEngine.h"

//TRIE FUNCTIONS

void createMap(map<string, int>& result)
{
	ifstream in;
	in.open("NameOfFile.txt");
	if (in)
	{
		while (!in.eof())
		{
			string Tmp;
			in >> Tmp;
			result[Tmp] = 0;

		}
	}
	in.close();
}

Node* getNewTrieNode()
{
	Node* node = new Node;
	node->endOfNode = false;
	return node;
}

void filter(string& s)
{
	for (int i = 0; i < s.size(); i++)
	{
		if (s[i] >= 65 && s[i] <= 90)
		{
			s[i] = s[i] + 32;
		}
	}
}

void insert(string s, long nums, Node*& root, string nameOfFile)
{
	filter(s);
	Node* pCur = nullptr;
	pCur = root;
	for (int i = 0; i < s.size(); i++)
	{
		if (root == nullptr)
		{
			root = new Node;
			root->child[s[i]] = new Node;
			pCur = root->child[s[i]];
			pCur->Pre = root;
		}
		else
		{
			if (pCur->child[s[i]] == nullptr)
			{

				pCur->child[s[i]] = new Node;
				pCur->child[s[i]]->Pre = pCur;
				pCur = pCur->child[s[i]];
			}
			else
			{
				pCur->iSCommon = true;
				pCur = pCur->child[s[i]];
			}
		}

	}
	if (pCur != nullptr)
	{
		pCur->position[nameOfFile].push_back(nums);
		pCur->endOfNode = true;
	}
}

void display(Node* root, string word)
{
	if (!root)
		return;
	for (auto i = root->child.begin(); i != root->child.end(); i++)
	{
		string next_word = word + i->first;
		if (i->second)
		{
			if (i->second->endOfNode) cout << next_word << '\n';
		}
		display(i->second, next_word);
	}
}

void deleteTree(Node*& root)
{
	if (!root)
	{
		return;
	}
	for (auto i = root->child.begin(); i != root->child.end(); i++)
	{
		deleteTree(i->second);
	}
	delete root;
}

bool searchString(Node* root, string s)
{
	filter(s);
	if (root == nullptr)
	{
		return false;
	}
	else
	{
		Node* pCur = nullptr;
		pCur = root;
		for (int i = 0; i < s.size(); i++)
		{
			if (pCur->child[s[i]] == nullptr)
			{
				return false;
			}
			else
			{
				pCur = pCur->child[s[i]];
			}
		}
		if (pCur != nullptr)
		{
			if (pCur->endOfNode == true)
			{
				return true;
			}
			else
				return false;
		}
		return false;
	}
}

bool searchString2(Node* root, string s, map<string, int>& m)
{
	filter(s);
	if (root == nullptr)
	{
		return false;
	}
	else
	{
		Node* pCur = nullptr;
		pCur = root;
		for (int i = 0; i < s.size(); i++)
		{
			if (pCur->child[s[i]] == nullptr)
			{
				return false;
			}
			else
			{
				pCur = pCur->child[s[i]];
			}
		}
		if (pCur != nullptr)
		{
			if (pCur->endOfNode == true)
			{
				for (map<string, vector<long>>::iterator it = pCur->position.begin(); it != pCur->position.end(); ++it) {
					m[it->first]+= it->second.size(); //update score for file name in map
				}
				return true;
			}
			else
				return false;
		}
		return false;
	}
}

void deleteString(Node* root, string s)
{
	if (root == nullptr) return;
	if (searchString(root, s) == false) return;
	else
	{
		Node* pCur = root;
		int a = 0;
		for (int i = 0; i < s.size(); i++)
		{
			if (pCur->iSCommon == true) a = 1;
			pCur = pCur->child[s[i]];
		}
		if (a == 1)
		{
			if (pCur == nullptr) return;
			else pCur->endOfNode = false;
		}
		else
		{
			while (pCur != root)
			{
				Node* pTmp = pCur;
				pCur = pCur->Pre;
				delete pTmp;
			}
		}
	}
}

//STOPWORDS

void insertStopword(string s, Node*& root)
{
	filter(s);
	Node* pCur = nullptr;
	pCur = root;
	for (int i = 0; i < s.size(); i++)
	{
		if (root == nullptr)
		{
			root = new Node;
			root->child[s[i]] = new Node;
			pCur = root->child[s[i]];
			pCur->Pre = root;
		}
		else
		{
			if (pCur->child[s[i]] == nullptr)
			{
				pCur->child[s[i]] = new Node;
				pCur->child[s[i]]->Pre = pCur;
				pCur = pCur->child[s[i]];
			}
			else
			{
				pCur->iSCommon = true;
				pCur = pCur->child[s[i]];
			}
		}

	}
	if (pCur != nullptr)
	{
		pCur->endOfNode = true;
	}
}

void loadStopword(Node*& root) {
	ifstream input;
	input.open("stopwords.txt");
	if (!input.is_open()) return;
	while (!input.eof()) {
		string stopword;
		getline(input, stopword);
		insertStopword(stopword, root);
	}
	input.close();
}

//READ FILE

bool isNumber(char a) {
	return a >= '0' && a <= '9';
}

bool isChar(char a) {
	return ((a >= 'a' && a <= 'z') || (a >= 'A' && a <= 'Z'));
}

bool isSpecialChar(char a) {
	return (a != '%' && a != '#' && a != '$' && a!='.' && a!='-' && a != '!' && a != ',');
}

void inputSentence(Node*& root, long& num, string filename, string sentence) {
	stringstream ss(sentence);
	string tmp;
	while (ss >> tmp) {
		while (tmp.length() && tmp.back() == ',') tmp.pop_back();
		for (int i = 0; i < tmp.length(); i++) {
			if (!isChar(tmp[i]) && !isNumber(tmp[i]) && isSpecialChar(tmp[i])) tmp.erase(tmp.begin() + i);
		}
		insert(tmp, num, root, filename);
		num++;
	}
}

void inputFile(Node*& root, string filename) {
	string path = "Data\\" + filename;
	long num = 1;
	ifstream fin;
	fin.open(path, ios::in);
	if (!fin.is_open()) return;
	string currentSentence;
	while (!fin.eof()) {
		getline(fin, currentSentence, '.');
		if (currentSentence.length()) {
			string next;
			getline(fin, next, '.');
			if ((isNumber(currentSentence.back()) && next.length() && isNumber(next[0]))) { //trường hợp số thập phân
				currentSentence = currentSentence + '.' + next;
				inputSentence(root, num, filename, currentSentence);
				continue;
			}
			else {
				inputSentence(root, num, filename, currentSentence);
				inputSentence(root, num, filename, next);
				continue;
			}
		}
		inputSentence(root, num, filename, currentSentence);
	}

	fin.close();
}

void init(Node*& root) {
	string path = "Data\\___index.txt";
	ifstream fin;
	fin.open(path, ios::in);
	if (!fin.is_open()) {
		return;
	}
	string filename;
	while (!fin.eof()) {
		getline(fin, filename);
		inputFile(root, filename);
	}
	fin.close();
}

//PROCESSING WITH MAP

bool cmp(pair<string, int>& a, pair<string, int>& b)
{
	return a.second > b.second;
}

void sort(map<string, int>& M)
{
	vector<pair<string, int> > A;

	for (auto& it : M) {
		A.push_back(it);
	}

	sort(A.begin(), A.end(), cmp);

	for (auto& it : A) {

		cout << it.first << endl;
	}
}

void mainSearch(string userInput, map<string, int>& result, Node* root, Node* stopWord, Title* newRoot, vector<string>& history, History*& rootHis)
{
	filter(userInput);
	stringstream filter1;
	stringstream filter0;
	string newAnd = {};
	string newOr = {};
	string newOpe = {};
	string newString = {};
	filter0.str(userInput);
	vector<string> putString;
	while (!filter0.eof())
	{
		string word0;
		filter0 >> word0;
		putString.push_back(word0);
	}
	for (int i = 0; i + 1 < putString.size(); i++)
	{// Op1 : 
		if (putString[i] == "and")
		{
			newAnd += putString[i - 1] + " " + putString[i] + " " + putString[i + 1];
			if (i + 2 < putString.size() && (putString[i + 2] == "or" || putString[i + 2] == "and"))
			{
				putString.erase(putString.begin() + i - 1);
				putString.erase(putString.begin() + i - 1);
			}
			else
			{
				putString.erase(putString.begin() + i - 1);
				putString.erase(putString.begin() + i - 1);
				putString.erase(putString.begin() + i - 1);
			}
			searchAND(root, newAnd, result);

		}
		// Op2 :
		else if (putString[i] == "or")
		{
			newOr += putString[i - 1] + " " + putString[i] + " " + putString[i + 1];
			if (i + 2 < putString.size() && (putString[i + 2] == "or" || putString[i + 2] == "and"))
			{
				putString.erase(putString.begin() + i - 1);
				putString.erase(putString.begin() + i - 1);
			}
			else
			{
				putString.erase(putString.begin() + i - 1);
				putString.erase(putString.begin() + i - 1);
				putString.erase(putString.begin() + i - 1);
			}
			SearchOR(root, newOr, result);
		}
	}
	int isTrue = 1;
	// Op3 :
	for (int i = 0; i < putString.size(); i++)
	{
		for (int j = 0; j + 3 < putString[i].size(); j++)
		{
			if (putString[i][j] != putString[i][j + 1] && putString[i][j + 1] == '.' && putString[i][j + 1] == putString[i][j + 2] && putString[i][j + 2] != putString[i][j + 3])
			{
				newOpe = putString[i];
				searchRange(root, newOpe, result);
				isTrue = 0;
			}
		}
		if (isTrue != 0)
		{
			newString += putString[i] + " ";
		}
		isTrue = 1;
	}
	if (newString == "")
	{
		return;
	}
	while (newString.size() > 0 && newString[newString.size() - 1] == ' ')
	{
		newString.pop_back();
	}
	vector<string> normal;
	vector<string> stopWordList;
	vector<string> plusAndMinos;
	vector<string> filetype;
	string Tmp = "";
	filter1.str(newString);
	while (!filter1.eof())
	{
		string word;
		filter1 >> word;
		bool isNormal = true;
		if (word.size() > 7)
		{
			Tmp = "";
			for (int i = 0; i <= 7; i++)
			{
				Tmp += word[i];
			}
			if (Tmp == "intitle:")
			{
				Tmp = "";
				Tmp += word + " ";
				while (!filter1.eof())
				{
					filter1 >> word;
					Tmp += word + " ";
				}
				while (Tmp[Tmp.size() - 1] == ' ')
				{
					Tmp.pop_back();
				}
				searchIntitle(newRoot, Tmp, result);// phai la Title
				isNormal = false;
				return;
			}
		}
		if (searchString(stopWord, word) == true)
		{
			stopWordList.push_back(word);
		}
		else {
			//Op 4:
			if (word.length() >= 9 && word.substr(9) == "filetype:") {
				filetype.push_back(word);
				isNormal = false;
			}
			//Op 5:
			if (word[0] == '-')
			{
				plusAndMinos.push_back(word);
				isNormal = false;
			}
			//Op 6:
			if (word[0] == '+')
			{
				plusAndMinos.push_back(word);
				isNormal = false;
			}
			//Op 7:
			if (word[0] == '"')
			{
				Tmp = "";
				Tmp += word + " ";
				while (!filter1.eof() && word[word.size() - 1] != '"')
				{
					filter1 >> word;
					Tmp += word + " ";
				}
				while (Tmp[Tmp.size() - 1] == ' ')
				{
					Tmp.pop_back();
				}
				searchExactMatch(root, Tmp, result);
				isNormal = false;
			}
			//Op 8:
			if (word[0] == '#')
			{
				searchHashtag(root, word, result);
				isNormal = false;
			}
			//Op 9:
			if (word[0] == '$')
			{
				searchprice(root, word, result);
				isNormal = false;
			}
			if (word[0] == '~')
			{
				searchSynonym(root, word, result);
				isNormal = false;
			}
			if (isNormal)
			{
				normal.push_back(word);
			}
		}
	}
	if (normal.size() == 2)
	{
		string fast = normal[0] + " or " + normal[1];
		SearchOR(root, fast, result);
	}
	else
	{
		for (int i = 0; i < normal.size(); i++)
		{
			searchString2(root, normal[i], result);
		}
	}
	int count = 0;
	for (auto i = result.begin(); i != result.end(); i++)
	{
		if (i->second != 0)
		{
			count++;
		}
	}
	if (count == 0)
	{
		for (int i = 0; i < stopWordList.size(); i++)
		{
			searchString2(stopWord, stopWordList[i], result);
		}
	}
	for (int i = 0; i < plusAndMinos.size(); i++)
	{
		if (plusAndMinos[i][0] == '-')
		{
			specialCase3(plusAndMinos[i], root, result);
		}
		if (plusAndMinos[i][0] == '+')
		{
			SearchPlus(root, plusAndMinos[i], result);
		}
	}
	if (!filetype.empty()) {
		SearchType(newRoot, filetype[0], result);
	}
}
