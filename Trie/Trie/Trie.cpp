#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <vector>
#include <filesystem>
#include <sstream>
#include <algorithm>
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
	vector<string> filename;
};

bool searchString2(Node* root, string s, map<string, int>& m)
{
//	filter(s);
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
					m[it->first]++; //update score for file name in map
				}
				return true;
			}
			else
				return false;
		}
		return false;
	}
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

bool searchAND(Node* root, string s, map<string, int> &res, int& score) {
	if (!root) return false;
	filter(s);
	int i = 0;
	string before, after, t;
	//example : "search and print"
	//before: search, after: print
	stringstream ss(s);
	while (t != "and") {
		before = t;
		ss >> t;
	}
	ss >> after;
	if (searchString2(root, before, res) && searchString2(root, after, res))
		return true;
	return false;
}

bool searchString(Node* root, string s) {
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

bool searchprice(Node* root, string s, map<string, int>& result) {
	// camera $400
	if (!root) return false;
	if (!root->child['$']) return false;
	stringstream ss(s);
	string key;
	ss >> key; // camera
	if (searchString2(root, key, result)) { //find "camera"
		ss >> key;
		if (searchString2(root, key, result)) // find "$400"
			return true;
	}
	return false;
}

bool searchwildcards(Node* root, string s, map<string, int>& res) {
//	hello * how are you
	string keybefore, keyafter;
	string tmp;
	stringstream ss(s);
	while (ss >> tmp) {
		if (tmp == "*")
			break;
		keybefore += tmp + " ";
	}
	while (ss >> tmp) {
		keyafter += tmp + " ";
	}
	if (wildcards(root, keybefore, keyafter, res))
		return true;
	return false;
}

bool wildcards(Node* root, string before, string after, map<string, int>& res) {
	if (!root) return;
	Node* pCur = root;
	string tmp, b, a;
	stringstream ss1(before), ss2(after);

	while (ss1 >> tmp) {
		if (searchString(root, tmp))
			continue;
		else
			return false;
	}
	while (ss2 >> tmp) {
		if (searchString(root, tmp))
			continue;
		else
			return false;
	}
	for (map <string, vector<long>> ::iterator mp = pCur->position.begin(); mp != pCur->position.end(); ++mp) {
		res[mp->first] += mp->second.size();
	}
	return true;
}

int main()
{
	Node* root = nullptr;


	return 0;
}