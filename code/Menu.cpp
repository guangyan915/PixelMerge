#include "Menu.hpp"

void Menu::newPhoto() {
	p = new Photo();
}
void Menu::deletePhoto() {
	delete p;
	p = nullptr;
}

void Menu::functionShow() {
	cout << "=============����ѡ��=============" << endl;
	cout << "==    1�������غϲ�             ==" << endl;
	cout << "==    2�������غϲ�             ==" << endl;
	cout << "==    3������������ƽ���ϲ�     ==" << endl;
	cout << "==    4������������ƽ���ϲ�     ==" << endl;
	cout << "==    0���˳�                   ==" << endl;
	cout << "==================================" << endl;
	cout << "��ѡ���ܣ� " << endl;
}

void Menu::selectFunction() {
	while (true) {
		functionShow();
		char c;
		cin >> c;
		switch (c) {
		case '1':
			setDirctoryPath();
			newPhoto();
			if (p->initMergePhotoProrertyAndFileName(dirctory_path) != 0) {
				cout << "·������" << endl;
				break;
			}
			if (p->beginRowMerge() == -1) {
				cout << "ͼƬ�������㣡" << endl;
				break;
			}
			photoSave();
			deletePhoto();
			break;
		case '2':
			setDirctoryPath();
			newPhoto();
			if (p->initMergePhotoProrertyAndFileName(dirctory_path) != 0) {
				cout << "·������" << endl;
				break;
			}
			if (p->beginColumnMerge() == -1) {
				cout << "ͼƬ�������㣡" << endl;
				break;
			}
			photoSave();
			deletePhoto();
			break;
		case '3':
			setDirctoryPath();
			newPhoto();
			if (p->initMergePhotoProrertyAndFileName(dirctory_path) != 0) {
				cout << "·������" << endl;
				break;
			}
			if (p->beginRowIntervalAverageMerge() == -1) {
				cout << "ͼƬ�������㣡" << endl;
				break;
			}
			photoSave();
			deletePhoto();
			break;
		case '4':
			setDirctoryPath();
			newPhoto();
			if (p->initMergePhotoProrertyAndFileName(dirctory_path) != 0) {
				cout << "·������" << endl;
				break;
			}
			if (p->beginColumnIntervalAverageMerge() == -1) {
				cout << "ͼƬ�������㣡" << endl;
				break;
			}
			photoSave();
			deletePhoto();
			break;
		case '0':
			cout << "ллʹ�ã�" << endl;
			return;
		default:
			cout << "��������" << endl;
		}
	}
}

void Menu::setDirctoryPath() {
	cout << "������ͼƬ����·����";
	cin >> dirctory_path;
}

void Menu::photoSave() {
	p->mergePhotoDerive();
}
