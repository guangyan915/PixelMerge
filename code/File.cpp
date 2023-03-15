#include "File.hpp"

File::File() {}

void File::setFileNameRes() {
	
	string cmd = "dir " + file_path + " /b /o-d/tc > " + "name_list.txt"; // 按文件创建时间
	//string cmd = "dir " + file_path + " /b > " + "name_list.txt";		// 按文件字符序
	system(cmd.c_str());
	file_name.open("name_list.txt", ios::in);
	if (!file_name.is_open()) {
		cout << "文件未打开! 程序已退出！" << endl;
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
		cout << "有" << file_name_res.size() << "个文件，如下：" << n + 1 << "s后显示" << endl;
		Sleep(1000);
		system("cls");
		cout << "有" << file_name_res.size() << "个文件，如下：" << n + 1 << "s后显示" << endl;
	}

	for (auto s : file_name_res) {
		cout << s << endl;
	}
	file_name.close();
	system("del name_list.txt");
}

void File::setBatchName() {
	cout << "图片命名示例：名称前缀1、名称前缀2、名称前缀3" << endl;
	cout << "请输入名称前缀：";
	string pre;
	while (true) {
		cin >> pre;
		if (pre[pre.size() - 1] == '.') {
			cout << "前缀最后一个字符不能为“ . ”" << endl;
		}
		else break;
	}
	cout << "请输入起始序号：";
	int begin;
	cin >> begin;
	cout << "请输入间隔序号：";
	int n;
	cin >> n;
	cout << "请输入文件后缀：";
	string suffix;
	cin >> suffix;
	for (int i = 0; i < file_name_res.size(); i++) {
		string rename = "rename " + file_path + '\\' + file_name_res[i] + " " + pre + to_string(begin + i + n - 1) + '.' + suffix;
		cout << file_name_res[i] << " -> " << pre + to_string(begin + i + n - 1) + "." + suffix << endl;
		system(rename.c_str());
	}
	cout << "重命名完成！" << endl;

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


