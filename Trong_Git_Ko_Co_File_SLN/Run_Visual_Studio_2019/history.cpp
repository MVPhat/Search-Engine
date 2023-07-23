#include "searchEngine.h"

void writeHistory(string s, vector<string>& history) {
	ofstream output;
	history.push_back(s);
	output.open("history.txt");
	if (!output.is_open()) return;
	string tmp;
	for (int i = history.size() - 1; i >= 0; i--) {
		output << history[i] << "\n";
	}
}

void printHistory(vector<string>& history) {
	gotoxy(70, 3);
	cout << "HISTORY SEARCH\n";
	for (int i = history.size() - 1; i >= 0; i--) {
		gotoxy(65, 5 + history.size() - i);
		cout << history.size() - i << ". " << history[i] << "\n";
	}
	gotoxy(65, 6 + history.size());
	system("pause");
}

void insertHistory(History*& root, string s) {
	History* pCur = nullptr;
	pCur = root;
	for (int i = 0; i < s.size(); i++)
	{

		if (root == nullptr)
		{
			root = new History;
			root->child[s[i]] = new History;
			pCur = root->child[s[i]];
		}
		else
		{
			if (pCur->child[s[i]] == nullptr)
			{
				pCur->child[s[i]] = new History;
				pCur = pCur->child[s[i]];
			}
			else
			{
				pCur = pCur->child[s[i]];
			}
		}

	}
	if (pCur != nullptr)
	{
		pCur->endOfNode = true;
	}
}

bool searchHistory(History* root, string s) {
	int l = s.length();
	History* cur = root;
	for (int i = 0; i < l; i++) {
		if (!cur->child[s[i]]) return false;
		cur = cur->child[s[i]];
	}
	return(cur != nullptr && cur->endOfNode == true);
}

void readHistoryToTrie(History*& root, vector<string>history) {
	for (int i = 0; i < history.size(); i++) insertHistory(root, history[i]);
}

void displayHis(History* root, string word) {
	if (!root)
		return;
	for (auto i = root->child.begin(); i != root->child.end(); i++)
	{
		string next_word = word + i->first;
		if (i->second)
		{
			if (i->second->endOfNode) cout << next_word << '\n';
		}
		displayHis(i->second, next_word);
	}
}

vector<string> suggestionRec(History* root, string s, vector<string>& rec) {
	if (!root) return rec;

	if (root->endOfNode) {
		rec.push_back(s);
	}

	for (auto i = root->child.begin(); i != root->child.end(); i++) {
		s.push_back(i->first);
		suggestionRec(i->second, s, rec);
		s.pop_back();
	}

	return rec;
}

void printAutoSugg(History* root, string s, map<string, int>& result, Node* rootTrie, Node* stopWord, Title* newRoot, vector<string>& history) {
	History* cur = root;
	for (int i = 0; i < s.length(); i++) {
		if (!cur->child[s[i]]) return;
		cur = cur->child[s[i]];
	}
	vector<string> rec;
	suggestionRec(cur, s, rec);
	for (int i = 0; i < rec.size(); i++) cout << i + 1 << ": " << rec[i] << "\n";
	int choice;
	do
	{
		gotoxy(0, rec.size() + 1);
		cout << "Choose history to search (From 1 to 10): ";
		cin >> choice;
		gotoxy(0, rec.size() + 1);
		cout << "                                               ";
	} while (choice <= 0 || choice > rec.size());
	string input = rec[choice - 1];
	result.clear();
	clock_t t;
	t = clock();
	mainSearch(input, result, rootTrie, stopWord, newRoot, history, root);
	system("cls");
	sort(result, input);
	t = clock() - t;
	cout << "\nTime: " << ((float)t) / CLOCKS_PER_SEC << " seconds\n";
	system("pause");
	system("cls");
}


void deleteTreeHis(History*& root)
{
	if (!root)
	{
		return;
	}
	for (auto i = root->child.begin(); i != root->child.end(); i++)
	{
		deleteTreeHis(i->second);
	}
	delete root;
}

void deleteHistory(History*& root, vector<string>& history) {
	deleteTreeHis(root);
	root = NULL;
	ofstream out;
	out.open("history.txt");
	out.close();
	history.clear();
	return;
}
