#include "GameManager.h"
#include <iostream>

using namespace std;

int main(int argc, char* args[]){
	GameManager *ptr = new GameManager();

	if(ptr->Initialize() == false){
		ptr = nullptr;
		delete ptr;
		cout << "Game Manager failed to init!" << endl;
	}

	ptr->Run();

	ptr = nullptr;
	delete ptr;

	cout << "Program has ended run" << endl;

	cin.get();

	return 0;
}