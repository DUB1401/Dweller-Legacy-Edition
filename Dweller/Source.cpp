#include "Source.h"

//---> LayoutsController
//=======================================================================================================================//

//Обновляет текущий слой.
void LayoutsController::Processing() {
	Answer.Clear();
	switch (MenuUpdateIndex) {
	case 0:
		//Выход из игры.
		exit(EXIT_SUCCESS);
		break;
	case 1:
		//Вступительный ролик.
		Answer = ObjectIntro->Update();
		break;
	case 2:
		//Главное меню.
		Answer = ObjectMainMenu->Update();
		break;
	case 3:
		//Титры.
		Answer = ObjectCredits->Update();
		break;
	case 4:
		//Игра.
		Answer = ObjectWorldRenderer->Update();
		break;
	}
}

//Выделить память.
void LayoutsController::AllocateMemory() {
	//Выделение памяти: вступительный ролик.
	if (Answer.to == "intro") { 
		ObjectIntro = new Intro(MainWindow, ObjectSettings, GlobalTimeAsSeconds, GlobalTimeAsMicroseconds);
		ObjectIntro->Start();
	
	}
	//Выделение памяти: главное меню.
	if (Answer.to == "menu") ObjectMainMenu = new MainMenu(MainWindow, ObjectSettings);
	//Выделение памяти: титры.
	if (Answer.to == "credits") ObjectCredits = new Credits(MainWindow, ObjectSettings, GlobalTimeAsSeconds);
	//Выделение памяти: игра.
	if (Answer.to == "game") ObjectWorldRenderer = new WorldRenderer(MainWindow, ObjectSettings, GlobalTimeAsSeconds);
}

//Освободить память.
void LayoutsController::FreeMemory() {
	//Освобождение памяти: титры.
	if (Answer.from == "intro") delete ObjectIntro;
	//Освобождение памяти: главное меню.
	if (Answer.from == "menu") delete ObjectMainMenu;
	//Освобождение памяти: титры.
	if (Answer.from == "credits") delete ObjectCredits;
}

//Устанавливает индекс целевого слоя на основе ответа.
void LayoutsController::SetNewUpdateIndex() {
	//Если ответ не пустой, то обновить индекс.
	if (!Answer.Empty()) MenuUpdateIndex = LayoutsDefinitions[Answer.to];
}

//Конструктор: инициалзиация объекта.
LayoutsController::LayoutsController(sf::RenderWindow* MainWindow, Settings* ObjectSettings, double* GlobalTimeAsSeconds, double* GlobalTimeAsMiliseconds, unsigned long long int* GlobalTimeAsMicroseconds) {

	//---> Передача аргументов.
	//=======================================================================================================================//
	this->ObjectSettings = ObjectSettings;
	this->MainWindow = MainWindow;
	this->GlobalTimeAsSeconds = GlobalTimeAsSeconds;
	this->GlobalTimeAsMiliseconds = GlobalTimeAsMiliseconds;
	this->GlobalTimeAsMicroseconds = GlobalTimeAsMicroseconds;

	//---> Инициализация контейнера определений слоёв.
	//=======================================================================================================================//
	LayoutsDefinitions["exit"] = 0;
	LayoutsDefinitions["intro"] = 1;
	LayoutsDefinitions["menu"] = 2;
	LayoutsDefinitions["credits"] = 3;
	LayoutsDefinitions["game"] = 4;

	//---> Инициализация стартового слоя.
	//=======================================================================================================================//
	Answer.to = "intro";
	SetNewUpdateIndex();
	AllocateMemory();
	Answer.Clear();
}

//Обновление текущего слоя и его ответа.
void LayoutsController::Update() {
	Processing();
	//Если получен ответ, то обработать его.
	if (!Answer.Empty()) {
		SetNewUpdateIndex();
		FreeMemory();
		AllocateMemory();
	}

}





