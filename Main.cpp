//#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")

#include "TechSupport.h"
#include "Source.h"
#include "EvolvGen.h"
#include "GUI.h"

int main(int argc, char* argv[]) {

	SetConsoleCP(CP_UTF8);
	SetConsoleOutputCP(CP_UTF8);

	sf::RenderWindow MainWindow(sf::VideoMode(1920, 1080 + 1), "Dweller: Legacy Edition", sf::Style::None);
	//sf::RenderWindow MainWindow(sf::VideoMode(1280, 720), "Dweller: Legacy Edition", sf::Style::Close);

	sf::Clock GlobalClock;
	double GlobalTimeAsSeconds;
	double GlobalTimeAsMiliseconds;
	unsigned long long int GlobalTimeAsMicroseconds;

	//Текущий слой обновления.
	unsigned int MenuUpdateIndex = 1;
	//Ответ от обновляемого слоя.
	std::string UpdateAnswer;

	MainWindow.setVerticalSyncEnabled(0);

	//Установка значка в заголовке окна.
	HICON hicon = LoadIcon(GetModuleHandleA(NULL), MAKEINTRESOURCEW(103));
	SendMessageA(MainWindow.getSystemHandle(), WM_SETICON, ICON_BIG, (LPARAM)hicon);

	//Создание необходимых объектов игры.
	TechSupport ObjTechSupport(&MainWindow, &GlobalTimeAsSeconds);
	Intro ObjectIntro(&MainWindow, &GlobalTimeAsSeconds, &GlobalTimeAsMicroseconds);
	MainMenu ObjectMainMenu(&MainWindow);
	Credits ObjectCredits(&MainWindow, &GlobalTimeAsSeconds);

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
			//UpdateAnswer = ObjectIntro.Update();
			break;

		//Главное меню.
		case 1:
			UpdateAnswer = ObjectMainMenu.Update();
			break;

		//Титры.
		case 2:
			UpdateAnswer = ObjectCredits.Update();
			break;
		}

		//Выход в меню.
		if (UpdateAnswer == "to_menu") { MenuUpdateIndex = 1; UpdateAnswer.clear(); }
		//Переход к титрам.
		if (UpdateAnswer == "to_credits") { MenuUpdateIndex = 2; UpdateAnswer.clear(); }
		//Выход из игры.
		if (UpdateAnswer == "exit") return EXIT_SUCCESS;

		ObjTechSupport.Update();
		MainWindow.display();
	}

	return EXIT_SUCCESS;
}