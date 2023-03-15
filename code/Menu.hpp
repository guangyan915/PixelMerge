#pragma once
#include "PhotoMerg.hpp"

class Menu {
private:
	Photo* p;
	string dirctory_path;
public:
	void newPhoto();
	void deletePhoto();
	void functionShow();
	void selectFunction();
	void setDirctoryPath();
	void photoSave();
};