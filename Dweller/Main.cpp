//#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")

#include "TechSupport.h"
#include "Source.h"
#include "GameComponents/Intro.h"

int main(int argc, char* argv[]) {
	SetConsoleCP(CP_UTF8);
	SetConsoleOutputCP(CP_UTF8);

	// Чтение настроек.
	Settings ObjectSettings(L"Settings.ini");
	ObjectSettings.Print();

	// Инициализация окна и фикс проблемы безрамочного окна.
	sf::RenderWindow MainWindow;
	if (ObjectSettings.Fullscreen) MainWindow.create(sf::VideoMode(ObjectSettings.WindowWidth, ObjectSettings.WindowHeight + 1), "Dweller: Legacy Edition", sf::Style::None);
	else MainWindow.create(sf::VideoMode(ObjectSettings.WindowWidth, ObjectSettings.WindowHeight), "Dweller: Legacy Edition", sf::Style::Close);
	// Установка настроек окна: вертикальная синхронизация и ограничение FPS.
	MainWindow.setVerticalSyncEnabled(ObjectSettings.VerticalSync);
	MainWindow.setFramerateLimit(ObjectSettings.FramerateLimit);

	// Создание главных компонентов обработки.
	sf::Event MainEvent;
	sf::Clock GlobalClock;
	double GlobalTimeAsSeconds;
	double GlobalTimeAsMilliseconds;
	unsigned long long int GlobalTimeAsMicroseconds;
	int MouseWheelScrollDelta = 0;

	// Установка указателей на объекты общения модулей.
	CommunicationData ObjectCommunicationData;
	ObjectCommunicationData.MainWindow = &MainWindow;
	ObjectCommunicationData.GlobalTimeAsSeconds = &GlobalTimeAsSeconds;
	ObjectCommunicationData.GlobalTimeAsMilliseconds = &GlobalTimeAsMilliseconds;
	ObjectCommunicationData.GlobalTimeAsMicroseconds = &GlobalTimeAsMicroseconds;
	ObjectCommunicationData.MouseWheelScrollDelta = &MouseWheelScrollDelta;

	//Установка значка в заголовке окна.
	HICON hicon = LoadIcon(GetModuleHandleA(NULL), MAKEINTRESOURCEW(103));
	SendMessageA(MainWindow.getSystemHandle(), WM_SETICON, ICON_BIG, (LPARAM)hicon);

	//Создание необходимых объектов игры.
	TechSupport* ObjTechSupport = new TechSupport(&MainWindow, &GlobalTimeAsSeconds);
	LayoutsController ObjLayoutsController(&MainWindow, &ObjectCommunicationData, &ObjectSettings, &GlobalTimeAsSeconds, &GlobalTimeAsMilliseconds, &GlobalTimeAsMicroseconds);

	// Главный цикл процесса.
	while (MainWindow.isOpen()) {

		// Обнуление дельты прокрутки колёсика мышки.
		MouseWheelScrollDelta = 0;

		// Обработка событий.
		while (MainWindow.pollEvent(MainEvent)) {
			// Событие: закрытие окна.
			if (MainEvent.type == sf::Event::Closed) MainWindow.close();
			// Событие: прокрутка колёсика мыши.
			if (MainEvent.type == sf::Event::MouseWheelScrolled) MouseWheelScrollDelta = MainEvent.mouseWheelScroll.delta;
		}

		// Обработка времени исполнения кадров.
		GlobalTimeAsSeconds = GlobalClock.getElapsedTime().asSeconds();
		GlobalTimeAsMilliseconds = GlobalClock.getElapsedTime().asMilliseconds();
		GlobalTimeAsMicroseconds = GlobalClock.getElapsedTime().asMicroseconds();
		GlobalClock.restart();

		// Обработка слоёв взаимодействия.
		MainWindow.clear();
		ObjLayoutsController.Update();
		ObjTechSupport->Update();
		MainWindow.display();
		
	}

	return EXIT_SUCCESS;
}