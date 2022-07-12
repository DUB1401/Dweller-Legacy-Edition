//#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")

#include "TechSupport.h"
#include "Source.h"
#include "EvolvGen.h"

int main(int argc, char* argv[]) {

	SetConsoleCP(CP_UTF8);
	SetConsoleOutputCP(CP_UTF8);

	sf::RenderWindow MainWindow(sf::VideoMode(1920, 1080 + 1), "Dweller: Legacy Edition", sf::Style::None);
	sf::Clock GlobalClock;
	double GlobalTimeAsSeconds;
	double GlobalTimeAsMiliseconds;
	unsigned long long int GlobalTimeAsMicroseconds;

	MainWindow.setVerticalSyncEnabled(false);

	//Установка значка в заголовке окна.
	HICON hicon = LoadIcon(GetModuleHandleA(NULL), MAKEINTRESOURCEW(103));
	SendMessageA(MainWindow.getSystemHandle(), WM_SETICON, ICON_BIG, (LPARAM)hicon);

	//Создание необходимых объектов игры.
	TechSupport ObjTechSupport(&MainWindow, &GlobalTimeAsSeconds);
	//Intro ObjectIntro(&MainWindow, &GlobalTimeAsSeconds, &GlobalTimeAsMicroseconds);
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
		//ObjectIntro.Update();
		ObjectCredits.Update();
		ObjTechSupport.Update();
		MainWindow.display();
	}

	return EXIT_SUCCESS;
}