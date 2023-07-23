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

string printHistory(vector<string>& history) {
	cout << "\n\nHISTORY SEARCH\n";
	for (int i = history.size() - 1; i >= 0; i--) {
		cout << history.size() - i << ". " << history[i] << "\n";
	}
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
		return rec;
	}

	for (auto i = root->child.begin(); i != root->child.end(); i++) {
		s.push_back(i->first);
		suggestionRec(i->second, s, rec);
		s.pop_back();
	}

	return rec;
}

void printAutoSugg(History* root, string s) {
	History* cur = root;
	for (int i = 0; i < s.length(); i++) {
		if (!cur->child[s[i]]) return;
		cur = cur->child[s[i]];
	}
	if (cur->endOfNode == true) return;
	vector<string> rec;
	suggestionRec(cur, s, rec);
	for (int i = 0; i < rec.size(); i++) cout << rec[i] << "\n";
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

void deleteHistory(History*& root) {
	deleteTreeHis(root);
	root = NULL;
	ofstream out;
	out.open("history.txt");
	out.close();
	history.clear();
	return;
}
