#include "Menu.hpp"

void Menu::newPhoto() {
	p = new Photo();
}
void Menu::deletePhoto() {
	delete p;
	p = nullptr;
}

void Menu::functionShow() {
	cout << "=============功能选择=============" << endl;
	cout << "==    1、行像素合并             ==" << endl;
	cout << "==    2、列像素合并             ==" << endl;
	cout << "==    3、行像素区间平均合并     ==" << endl;
	cout << "==    4、列像素区间平均合并     ==" << endl;
	cout << "==    0、退出                   ==" << endl;
	cout << "==================================" << endl;
	cout << "请选择功能： " << endl;
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
				cout << "路径有误！" << endl;
				break;
			}
			if (p->beginRowMerge() == -1) {
				cout << "图片数量不足！" << endl;
				break;
			}
			photoSave();
			deletePhoto();
			break;
		case '2':
			setDirctoryPath();
			newPhoto();
			if (p->initMergePhotoProrertyAndFileName(dirctory_path) != 0) {
				cout << "路径有误！" << endl;
				break;
			}
			if (p->beginColumnMerge() == -1) {
				cout << "图片数量不足！" << endl;
				break;
			}
			photoSave();
			deletePhoto();
			break;
		case '3':
			setDirctoryPath();
			newPhoto();
			if (p->initMergePhotoProrertyAndFileName(dirctory_path) != 0) {
				cout << "路径有误！" << endl;
				break;
			}
			if (p->beginRowIntervalAverageMerge() == -1) {
				cout << "图片数量不足！" << endl;
				break;
			}
			photoSave();
			deletePhoto();
			break;
		case '4':
			setDirctoryPath();
			newPhoto();
			if (p->initMergePhotoProrertyAndFileName(dirctory_path) != 0) {
				cout << "路径有误！" << endl;
				break;
			}
			if (p->beginColumnIntervalAverageMerge() == -1) {
				cout << "图片数量不足！" << endl;
				break;
			}
			photoSave();
			deletePhoto();
			break;
		case '0':
			cout << "谢谢使用！" << endl;
			return;
		default:
			cout << "输入有误！" << endl;
		}
	}
}

void Menu::setDirctoryPath() {
	cout << "请输入图片所在路径：";
	cin >> dirctory_path;
}

void Menu::photoSave() {
	p->mergePhotoDerive();
}
