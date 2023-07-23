#include "searchEngine.h"

//OPERATION 1

void searchAND(Node* root, string s, map<string, int>& res) {
	if (!root) return;
	filter(s);
	int i = 0;
	string before, after, t;
	stringstream ss(s);
	while (t != "and") {
		before = t;
		ss >> t;
	}
	ss >> after;
	map<string, int> m1, m2;
	searchString2(root, before, m1);
	searchString2(root, after, m2);
	//chạy trong map m1 để lấy tên file có string before, nếu map m2 cũng có thì thêm tên file vào result, điểm bằng điểm string đó ở map m1 và m2 cộng lại
	for (auto& i : m1) {
		map<string, int>::iterator it;
		it = m2.find(i.first);
		if (it != m2.end()) res[i.first] += i.second + it->second;
	}
}

//OPERATION 2

void SearchOR(Node* root, string querry, map <string, int>& result)
{
	filter(querry);
	stringstream ss(querry);
	string str1;
	string str2;
	string OR;
	ss >> str1;
	ss >> OR;
	ss >> str2;
	map<string, int> m1, m2;
	searchString2(root, str1, m1);
	searchString2(root, str2, m2);
	for (auto& i : m1) {
		map<string, int>::iterator it;
		it = m2.find(i.first);
		//nếu trong 1 file có cả hai từ thì ưu tiên file đó hơn -> cộng 100 phòng trường hợp các file khác có từ đơn nhiều hơn
		if (it != m2.end()) result[i.first] += i.second + it->second + 100;
		//file có từ đầu không có từ sau
		else result[i.first] += i.second;
	}
	for (auto& i : m2) {
		//file có từ sau không có từ đầu
		if (result[i.first] == 0) result[i.first] += i.second;
	}
}

//OPERATION 3

bool searchString4(Node* root, string s, vector<string>& nameOfFile)
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
					//lưu tên các file có string s
					nameOfFile.push_back(it->first);
				}
				return true;
			}
			else
				return false;
		}
		return false;
	}
}

void specialCase3(string userInput, Node* root, map<string, int>& result)// userInput phai la : -abcde, neu tim thay abcd trong file thi tra ve false, neu false thi khong tim o file do nua
{
	string newString = {};
	vector<string>filename;
	while (userInput.length() && userInput.back() == ' ') userInput.pop_back();
	if (userInput.size() == 1)
	{
		return;
	}
	else
	{
		for (int i = 1; i < userInput.size(); i++)
		{
			newString += userInput[i];
		}
	}
	if (searchString4(root, newString, filename) == true)
	{
		//tìm trong map result, xóa những tên file chứa string s
		for (int i = 0; i < filename.size(); i++) {
			map<string, int>::iterator it;
			it = result.find(filename[i]);
			if(it != result.end()) result.erase(it);
		}
	}
}

//OPERATION 4

void insertTitle(string s, Title*& root, string name)
{
	filter(s);
	Title* pCur = nullptr;
	pCur = root;
	for (int i = 0; i < s.size(); i++)
	{

		if (root == nullptr)
		{
			root = new Title;
			root->child[s[i]] = new Title;
			pCur = root->child[s[i]];
		}
		else
		{
			if (pCur->child[s[i]] == nullptr)
			{
				pCur->child[s[i]] = new Title;
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
		pCur->filename[name]++;
	}
}

//load title cùng lúc với build cây 
void loadTitle(Title*& root) {
	string path = "Data\\___index.txt";
	ifstream fin;
	fin.open(path, ios::in);
	if (!fin.is_open()) return;
	string filename;
	while (!fin.eof()) {
		getline(fin, filename);
		int last = filename.find_last_of('.');
		filename = filename.substr(0, last);
		stringstream ss(filename);
		string tmp;
		while (ss >> tmp) {
			insertTitle(tmp, root, filename);
		}
	}

	fin.close();
}

bool searchTitle(Title* root, string s, map<string, int>& m)
{
	filter(s);
	if (root == nullptr)
	{
		return false;
	}
	else
	{
		Title* pCur = root;
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
				for (map<string, int>::iterator it = pCur->filename.begin(); it != pCur->filename.end(); ++it) {
					string name = it->first + ".txt";
					m[name] += it->second; //update result
				}
				return true;
			}
			else
				return false;
		}
		return false;
	}
}

void searchIntitle(Title* root, string query, map<string, int>& result) {
	stringstream ss(query);
	string title;
	ss >> title;
	title = title.substr(8); //remove "intitle:" from the query
	searchTitle(root, title, result);
	while (ss >> title) {
		searchTitle(root, title, result);
	}
}

//OPERATION 5

void SearchPlus(Node* root, string querry, map <string, int>& result)
{
	filter(querry);
	string str = {};
	if (querry.size() == 1)
	{
		return;
	}
	else
	{
		for (int i = 1; i < querry.size(); i++)
		{
			str += querry[i];
		}
	}
	vector<string> filename;
	searchString4(root, str, filename);
	map<string, int>tmp(result); //copy map result vào map tmp
	//lấy tên các file trong chứa string querry
	for (int i = 0; i < filename.size(); i++) {
		map<string, int>::iterator it;
		it = tmp.find(filename[i]);
		if(it!=tmp.end()) tmp.erase(it);
	}
	//xóa những tên file không chứa string querry trong result
	for (auto itr = tmp.begin(); itr != tmp.end(); ++itr) {
		map<string, int>::iterator it;
		it = result.find(itr->first);
		if (it != result.end()) result.erase(it);
	}
	searchString2(root, str, result);
}

//OPERATION 6

void specialCase6(string type, map<string, int>& result)// filter2->ko lien quan chi la xet ten file
{
	for (auto i = result.begin(); i != result.end(); i++)
	{
		string checkType = {};
		for (int j = i->first.size() - 1; j >= 0; j--)
		{
			if (i->first[j] == '.')
			{
				if (checkType == type)
				{
					i->second += 2;
				}
				break;
			}
			checkType = i->first[j] + checkType;

		}
	}
}
void SearchType(Title* root, string query, map<string, int>& result)
{
	filter(query);
	query = query.substr(9);
	specialCase6(query, result);
}

//OPERATION 7

void searchprice(Node* root, string s, map<string, int>& result) {
	if (!root) return;
	if (!root->child['$']) return;
	searchString2(root, s, result);
}

//OPERATION 8

void searchHashtag(Node* root, string querry, map<string, int>& result) {
	if (!root) return;
	if (root->child['#'] == nullptr) return;
	searchString2(root, querry, result);
}

//OPERATION 9

bool inputIndex(Node* root, string s, vector<int>& sortList, string nameOfFile)// input vi tri string vo vector sortList
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
				for (int i = 0; i < pCur->position[nameOfFile].size(); i++)
					sortList.push_back(pCur->position[nameOfFile][i]);
				return true;
			}
			else
				return false;
		}
		return false;
	}
}

bool searchString3(Node* root, string s, string nameOfFile, int& cnt)
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
				cnt += pCur->position[nameOfFile].size();
				return true;
			}
			else
				return false;
		}
		return false;
	}
}

bool specialCase9_ss2(vector<int> sortList, int count, int& cnt)
{
	for (int i = 0; i + 1 < sortList.size(); i++)
	{
		if (sortList[i + 1] - sortList[i] == 1)
		{
			int newCount = count - 1;
			for (int j = i; j + 1 < sortList.size(); j++)
			{
				if (sortList[j + 1] - sortList[j] == 1)
				{
					newCount--;
				}
				if (sortList[j + 1] - sortList[j] != 1 && sortList[j + 1] - sortList[j] != 0)
				{
					break;
				}
				if (newCount == 0)
				{
					cnt++;
				}
			}
		}
	}
	if (cnt != 0) return true;
	else return false;
}

bool specialCase9_ss1(Node* root, string importantString, string nameOfFile, int& cnt)
{
	vector<int> sortList;
	stringstream InformationOfUser;
	InformationOfUser.str(importantString);
	string Tmp;
	int count2 = 0;// dem so string co trong " "
	int count = 0;// dem so string co trong " " nhung ton tai trong trie 
	while (!InformationOfUser.eof())
	{
		InformationOfUser >> Tmp;
		if (inputIndex(root, Tmp, sortList, nameOfFile) == true)
		{
			count++;
		}
		count2++;
	}
	if (count != count2)
	{
		return false;
	}
	if (count == 0)
	{
		return false;
	}
	if (count == 1)
	{
		searchString3(root, importantString, nameOfFile, cnt);
		if (cnt > 0)
		{
			return true;
		}
		return false;
	}
	sort(sortList.begin(), sortList.end());
	{
		if (specialCase9_ss2(sortList, count, cnt) == true)
		{
			return true;
		}
		return false;
	}

}

string specialCase9(string userInput, string fileName, Node* root, int& cnt)
{
	if (specialCase9_ss1(root, userInput, fileName, cnt) == true)
	{
		return fileName;
	}
	else
	{
		return "can't find!";
	}
}

bool searchTmp(Node* root, string s, map<string, int>& m) {
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
					//lưu tên file và số từ có trong string s xuất hiện trong file
					m[it->first]++;
				}
				return true;
			}
			else
				return false;
		}
		return false;
	}
}

void searchExactMatch(Node* root, string s, map<string, int>& result) {
	map<string, int> file;
	string importantString = {};
	for (int i = 1; i < s.size() - 1; i++)
	{
		importantString += s[i];
	}
	while (importantString.size() && importantString.back() == ' ')
	{
		importantString.pop_back();
	}
	string tmp;
	int cnt = 0;
	int cnt2 = 0; //điểm để thêm vào file
	stringstream ss(importantString);
	while (ss >> tmp) {
		cnt++;
		searchTmp(root, tmp, file);
	}
	for (auto& it : file) {
		if (it.second == cnt) {
			//lấy tên file
			string res = specialCase9(importantString, it.first, root, cnt2);
			if (res != "can't find!") result[res] += cnt2;
			cnt2 = 0;
		}
	}
}

// ======== OPERATION 10 ========

void searchwildcards(Node* root, string s, map<string, int>& res, vector<string>& filename) {
	//	example insert: find * print
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

	// tìm các file name có string before & after
	findFilename(root, keybefore, keyafter, filename);

	// xóa các file name trùng lặp
	removeDuplicated(filename);
}

void removeDuplicated(vector<string>& filename) {
	for (int i = 0; i < filename.size() - 1; ++i) {
		for (int j = i + 1; j < filename.size(); ++j) {
			if (filename[i] == filename[j]) {
				filename.erase(filename.begin() + j);
				--j;
			}
		}
	}
}

void saveope10(Node* root, string s, map<string, int>& res) {
	//save map result
	vector <string> filename;
	searchwildcards(root, s, res, filename);
	for (int i = 0; i < filename.size(); ++i) {
		res[filename[i]] += 2;
	}
}

void searchInfileName(Node* root, string before, string after, vector<string>& filename) {
	ifstream f;
	stringstream ss(before);
	string tmp, b, cur, unknownWord;
	stringstream safter(after);

	//example file co cac tu: this is a function to find the wildcard, unknown words, then print results on the screen.
	// cac tu trong unknownWord la: the wildcard unknown words (khong lay dau ',')

	while (ss >> tmp) {
		b = tmp; // tu cuoi cung cua before
	}
	safter >> tmp; // tu dau tien trong after

	bool isFound = 0;

	for (int i = 0; i < filename.size(); ++i) {
		f.open(filename[i] + ".txt");
		if (f.is_open()) {
			while (!f.eof()) {
				f >> cur;

				if (cur == b) {
					f >> cur;
					while (cur != tmp) {
						if (cur == ",") // not add ','
							continue;
						else if (cur == ".") // end of a sentence -> cannot find
							break;

						unknownWord += cur + " ";
						if (unknownWord[unknownWord.size() - 2] == ',')
						{
							unknownWord[unknownWord.size() - 2] = unknownWord[unknownWord.size() - 1];
							unknownWord.pop_back();
						}
						f >> cur;
					}
				}
			}

			if (f.eof())
				isFound = true;
			// search xong print luon
			if (isFound) {
				//print
			}
			else
				continue;
		}
		f.close();
	}
}

void findFilename(Node* root, string before, string after, vector<string>& filename) {
	stringstream ss1(before), ss2(after);
	string tmp;
	while (ss1 >> tmp) {
		searchString4(root, tmp, filename);
	}

	while (ss2 >> tmp) {
		searchString4(root, tmp, filename);
	}
}

//OPERATION 11

void inRange(Node* root, string num, double low, double high, map<string, int>& m, string query) {
	if (root == nullptr) return;
	if (root->endOfNode) {
		if (num.length()) {
			if (num[0] == '$') {
				if (query[0] == '$') {
					num = num.substr(1);
					double number = atof(num.c_str());
					if (number >= low && number <= high) {
						for (map<string, vector<long>>::iterator it = root->position.begin(); it != root->position.end(); ++it) {
							m[it->first] += it->second.size();
						}
					}
				}
			}
			else if (num.length() && num.back() == '%') {
				if (query.length() && query.back() == '%') {
					num.pop_back();
					double number = atof(num.c_str());
					if (number >= low && number <= high) {
						for (map<string, vector<long>>::iterator it = root->position.begin(); it != root->position.end(); ++it) {
							m[it->first] += it->second.size();
						}
					}
				}
			}
			else if ((num.length() && num.back() != '%') && num[0] != '$') {
				if ((query.length() && query.back() != '%') && query[0] != '$') {
					double number = atof(num.c_str());
					if (number >= low && number <= high) {
						for (map<string, vector<long>>::iterator it = root->position.begin(); it != root->position.end(); ++it) {
							m[it->first] += it->second.size();
						}
					}
				}
			}
		}
	}
	for (map<char, Node*>::iterator it = root->child.begin(); it != root->child.end(); ++it) {
		if (((it->first >= '0' && it->first <= '9') || it->first == '.' || it->first == '$' || it->first == '%' || it->first == ',')) {
			if (it->first == ',') num += ".";
			else num += it->first;
			inRange(it->second, num, low, high, m, query);
			num = num.substr(0, num.length() - 1);
		}
	}
}

void searchRange(Node* root, string querry, map<string, int>& result) {
	double lowRange, highRange;
	string tmpLow, tmpHigh;
	int length = querry.length(), i = 0;
	bool check = false;
	for (i; i < length - 1; i++) {
		if (querry[i] == '.' && querry[i + 1] == '.') {
			check = true;
			break;
		}
		tmpLow += querry[i];
	}
	if (!check) return;
	i += 2;
	for (i; i < length; i++) tmpHigh += querry[i];
	if (tmpLow[0] == '$') {
		tmpLow = tmpLow.substr(1);
		tmpHigh = tmpHigh.substr(1);
	}
	if (tmpLow.back() == '%') {
		tmpLow.pop_back();
		tmpHigh.pop_back();
	}
	lowRange = atof(tmpLow.c_str()); //convert string to float -> get the lower bound of range
	highRange = atof(tmpHigh.c_str()); //convert string to float -> get the upper bound of range
	string num;
	inRange(root, num, lowRange, highRange, result, querry);
}

//OPERATION 12

vector<string> getSyn(string s) {
	ifstream syn;
	syn.open("synonym.txt");
	string line;
	vector<string> res;
	res.push_back(s);
	while (!syn.eof()) {
		getline(syn, line);
		if (!line.length() || line == "=") continue;
		if (line.substr(0, 4) != "KEY:") continue;
		stringstream ss(line);
		string tmp;
		ss >> tmp;
		ss >> tmp;
		if (tmp[0] == '[') continue;
		filter(tmp);
		for (int i = 0; i < tmp.length(); i++) {
			if (!isChar(tmp[i])) tmp.erase(tmp.begin() + i);
		}
		if (tmp.length() && tmp[0] == '{') continue;
		if (tmp.compare(s) < 0) continue;
		if (tmp.compare(s) > 0) return res;
		do
		{
			getline(syn, line);
		} while (!line.length());
		ss.clear();
		if (line.length() < 4) return res;
		if (line.substr(0, 4) != "SYN:") return res;
		stringstream ss2(line);
		ss2 >> tmp;
		while (ss2 >> tmp) {
			if (tmp[0] != '{' && tmp[0] != '[') {
				while (tmp.length() && !isChar(tmp.back())) tmp.pop_back();
				int index = -1;
				index = tmp.find('_');
				if (index == -1) {
					filter(tmp);
					res.push_back(tmp);
				}
			}
		}
	}
	syn.close();
	return res;
}

void searchSynonym(Node* root, string s, map<string, int>& res) {
	if (!root) return;
	if (!s.length()) return;
	if (s[0] != '~') return;
	s = s.substr(1, s.length());
	vector<string> syn;
	syn = getSyn(s);
	for (int i = 0; i < syn.size(); i++) {
		searchString2(root, syn[i], res);
	}
}
