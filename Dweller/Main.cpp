//#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")

#include "TechSupport.h"
#include "Source.h"

#include "GameComponents/MainMenu.h"
#include "GameComponents/Credits.h"
#include "GameComponents/Intro.h"


int main(int argc, char* argv[]) {
	SetConsoleCP(CP_UTF8);
	SetConsoleOutputCP(CP_UTF8);

	//Чтение настроек.
	Settings ObjectSettings(L"Settings.ini");
	ObjectSettings.Print();
	//Инициализация окна и фикс проблемы безрамочного окна.
	sf::RenderWindow MainWindow;
	if (ObjectSettings.Fullscreen) MainWindow.create(sf::VideoMode(ObjectSettings.WindowWidth, ObjectSettings.WindowHeight + 1), "Dweller: Legacy Edition", sf::Style::None);
	else MainWindow.create(sf::VideoMode(ObjectSettings.WindowWidth, ObjectSettings.WindowHeight), "Dweller: Legacy Edition", sf::Style::Close);
	//Установка настроек окна: вертикальная синхронизация и ограничение FPS.
	MainWindow.setVerticalSyncEnabled(ObjectSettings.VerticalSync);
	MainWindow.setFramerateLimit(ObjectSettings.FramerateLimit);

	sf::Clock GlobalClock;
	double GlobalTimeAsSeconds;
	double GlobalTimeAsMiliseconds;
	unsigned long long int GlobalTimeAsMicroseconds;

	//Текущий слой обновления.
	unsigned int MenuUpdateIndex = 1;
	//Ответ от обновляемого слоя.
	std::string UpdateAnswer;

	//Установка значка в заголовке окна.
	HICON hicon = LoadIcon(GetModuleHandleA(NULL), MAKEINTRESOURCEW(103));
	SendMessageA(MainWindow.getSystemHandle(), WM_SETICON, ICON_BIG, (LPARAM)hicon);

	//Создание необходимых объектов игры.
	TechSupport* ObjTechSupport = new TechSupport(&MainWindow, &GlobalTimeAsSeconds);
	Intro* ObjectIntro = new Intro(&MainWindow, &ObjectSettings, &GlobalTimeAsSeconds, &GlobalTimeAsMicroseconds);
	MainMenu* ObjectMainMenu = new MainMenu(&MainWindow, &ObjectSettings);
	Credits* ObjectCredits;// = new Credits(&MainWindow, &GlobalTimeAsSeconds);

	//delete ObjTechSupport;
	//delete ObjectIntro;
	//delete ObjectMainMenu;
	//delete ObjectCredits;

	//ObjectIntro.Start();

	while (MainWindow.isOpen()) {

		sf::Event MainEvent;
		while (MainWindow.pollEvent(MainEvent)) if (MainEvent.type == sf::Event::Closed) MainWindow.close();
		//else if (MainEvent.type == sf::Event::MouseWheelMoved) std::cout << MainEvent.mouseWheel.delta << '\n';

		GlobalTimeAsSeconds = GlobalClock.getElapsedTime().asSeconds();
		GlobalTimeAsMiliseconds = GlobalClock.getElapsedTime().asMilliseconds();
		GlobalTimeAsMicroseconds = GlobalClock.getElapsedTime().asMicroseconds();
		GlobalClock.restart();

		MainWindow.clear();

		//Отрисовка только одного слоя.
		switch (MenuUpdateIndex) {

		//Вступительный ролик.
		case 0:
			//UpdateAnswer = ObjectIntro->Update();
			break;

		//Главное меню.
		case 1:
			UpdateAnswer = ObjectMainMenu->Update();
			break;

		//Титры.
		case 2:
			//UpdateAnswer = ObjectCredits->Update();
			break;
		}

		//Выход в меню.
		if (UpdateAnswer == "to_menu") { MenuUpdateIndex = 1; UpdateAnswer.clear(); }
		//Переход к титрам.
		if (UpdateAnswer == "to_credits") { 
			MenuUpdateIndex = 2; 
			UpdateAnswer.clear();

		}
		//Выход из игры.
		if (UpdateAnswer == "exit") return EXIT_SUCCESS;

		ObjTechSupport->Update();
		MainWindow.display();
	}

	return EXIT_SUCCESS;
}