// ======== OPERATION 10 ========

void searchwildcards(Node* root, string s, vector<string>& filename) {
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

	// tìm và in
	searchInfileName(root, before, after, filename);
}

void removeDuplicated(vector<string>& filename) {
	for (int i = 0; i < filename.size(); ++i) {
		for (int j = i + 1; j < filename.size(); ++j) {
			if (filename[i] == filename[j]) {
				filename.earse(file.begin() + j);
			}
		}
	}
}

void searchInfileName(Node* root, string before, string after, vector<string>& filenaeme) {
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
	stringstream ss1(before), ss2 (after);
	string tmp;
	while (ss1 >> tmp) {
		searchString4(root, tmp, filename);
	}
	
	while (ss2 >> tmp) {
		searchString4(root, tmp, filename);
	}
}