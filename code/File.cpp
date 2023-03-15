#include "File.hpp"

File::File() {}

void File::setFileNameRes() {
	
	string cmd = "dir " + file_path + " /b /o-d/tc > " + "name_list.txt"; // ���ļ�����ʱ��
	//string cmd = "dir " + file_path + " /b > " + "name_list.txt";		// ���ļ��ַ���
	system(cmd.c_str());
	file_name.open("name_list.txt", ios::in);
	if (!file_name.is_open()) {
		cout << "�ļ�δ��! �������˳���" << endl;
		exit(-1);
	}

	string name;
	
	while (getline(file_name, name, '\n')) {
		if (name != "." || name != ".." || name != "") file_name_res.push_back(name);
	}
	/*while (!file_name.eof()) {
		string name;
		file_name >> name;
		if (name != "." || name != "..") file_name_res.push_back(name);
	}
	file_name_res.pop_back();
	*/

	sortFile();

	int n = 3;
	while (n--) {
		system("cls");
		cout << "��" << file_name_res.size() << "���ļ������£�" << n + 1 << "s����ʾ" << endl;
		Sleep(1000);
		system("cls");
		cout << "��" << file_name_res.size() << "���ļ������£�" << n + 1 << "s����ʾ" << endl;
	}

	for (auto s : file_name_res) {
		cout << s << endl;
	}
	file_name.close();
	system("del name_list.txt");
}

void File::setBatchName() {
	cout << "ͼƬ����ʾ��������ǰ׺1������ǰ׺2������ǰ׺3" << endl;
	cout << "����������ǰ׺��";
	string pre;
	while (true) {
		cin >> pre;
		if (pre[pre.size() - 1] == '.') {
			cout << "ǰ׺���һ���ַ�����Ϊ�� . ��" << endl;
		}
		else break;
	}
	cout << "��������ʼ��ţ�";
	int begin;
	cin >> begin;
	cout << "����������ţ�";
	int n;
	cin >> n;
	cout << "�������ļ���׺��";
	string suffix;
	cin >> suffix;
	for (int i = 0; i < file_name_res.size(); i++) {
		string rename = "rename " + file_path + '\\' + file_name_res[i] + " " + pre + to_string(begin + i + n - 1) + '.' + suffix;
		cout << file_name_res[i] << " -> " << pre + to_string(begin + i + n - 1) + "." + suffix << endl;
		system(rename.c_str());
	}
	cout << "��������ɣ�" << endl;

}

size_t File::size() {
	return file_name_res.size();
}

void File::setFilePath(string path) {
	file_path = path;
}

string File::operator[](size_t n) {
	return file_name_res[n];
}

bool File::openDirctory(string path) {
	if (_access(path.c_str(), 0) != 0) {
		return false;
	}
	return true;
}

bool File::openDirctory() {
	if (_access(file_path.c_str(), 0) != 0) {
		return false;
	}
	return true;
}

bool compareNat(const std::string& a, const std::string& b)
{
	if (a.empty())
		return true;
	if (b.empty())
		return false;
	if (std::isdigit(a[0]) && !std::isdigit(b[0]))
		return true;
	if (!std::isdigit(a[0]) && std::isdigit(b[0]))
		return false;
	if (!std::isdigit(a[0]) && !std::isdigit(b[0]))
	{
		if (std::toupper(a[0]) == std::toupper(b[0]))
			return compareNat(a.substr(1), b.substr(1));
		return (std::toupper(a[0]) < std::toupper(b[0]));
	}

	// Both strings begin with digit --> parse both numbers
	std::istringstream issa(a);
	std::istringstream issb(b);
	int ia, ib;
	issa >> ia;
	issb >> ib;
	if (ia != ib)
		return ia < ib;

	// Numbers are the same --> remove numbers and recurse
	std::string anew, bnew;
	std::getline(issa, anew);
	std::getline(issb, bnew);
	return (compareNat(anew, bnew));
}

void File::sortFile() {
	sort(file_name_res.begin(), file_name_res.end(), compareNat);
}


