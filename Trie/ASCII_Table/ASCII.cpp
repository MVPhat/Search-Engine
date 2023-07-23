#include <Phat/DepTraiSieuCapVuTru.h>

void remove (vector<int>& v1) {
	for (int i = 0; i < v1.size() - 1; ++i) {
		for (int j = i + 1; j < v1.size(); ++j) {
			if (v1[i] == v1[j]) {
				v1.erase(v1.begin() + j);
				--j;
			}
		}
	}
}

void readfile(string& a) {
	ifstream file;
	file.open("Data/da.txt");
	string cur;
	if (file.is_open()) {
		while (!file.eof()) {
			file >> cur;
			cout << cur << " ";
		}
	}
	file.close();
}

int main() {

	/*vector<int> v1;

	v1.push_back(1);
	v1.push_back(2);
	v1.push_back(1);
	v1.push_back(1); 
	v1.push_back(1);
	v1.push_back(2); 
	v1.push_back(1);
	v1.push_back(12);
	v1.push_back(1);
	v1.push_back(2);
	v1.push_back(3);
	v1.push_back(7);
	v1.push_back(7);
	v1.push_back(3);

	cout << "Size before remove = " << v1.size() << endl;
	cout << "Elements of vector v: ";
	for (int i = 0; i < v1.size(); ++i) cout << v1[i] << " ";
	
	remove(v1);

	cout << "\n\nAfter remove duplicated: ";
	for (auto i = v1.begin(); i != v1.end(); ++i) {
		cout << *i << ' ';
	}
	cout << endl;*/
	ifstream f;
	f.open("002.txt");
	string a;
	if (f.is_open()) {
		while (!f.eof()) {
			f >> a;
			cout << a << " ";
		}

	}


	//cout << a << endl;


	return 0;
}
