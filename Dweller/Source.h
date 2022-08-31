#pragma once

#include "GameComponents/MainMenu.h"
#include "GameComponents/Credits.h"
#include "GameComponents/Intro.h"

//Переключатель слоёв отрисовки и обработчик выделения памяти.
class LayoutsController {
private:

	//---> Объекты слоёв.
	//=======================================================================================================================//
	//Вступительный ролик.
	Intro* ObjectIntro;
	//Главное меню.
	MainMenu* ObjectMainMenu;
	//Титры.
	Credits* ObjectCredits;

	//---> Данные.
	//=======================================================================================================================//
	//Определения индексов слоёв.
	std::map <std::string, unsigned int> LayoutsDefinitions;
	//Глобальные настройки.
	Settings* ObjectSettings;
	//Индекс текущего слоя.
	unsigned int MenuUpdateIndex;
	//Ответ текущего слоя.
	LayoutAnswer Answer;
	//Окно отрисовки.
	sf::RenderWindow* MainWindow;
	//Время кадра в секундах.
	double* GlobalTimeAsSeconds;
	//Время кадра в миллисекундах.
	double* GlobalTimeAsMiliseconds;
	//Время кадра в микросекундах.
	unsigned long long int* GlobalTimeAsMicroseconds;

	//---> Методы работы.
	//=======================================================================================================================//
	//Обновляет текущий слой.
	void Processing();
	//Выделить память.
	void AllocateMemory();
	//Освободить память.
	void FreeMemory();
	//Устанавливает индекс целевого слоя на основе ответа.
	void SetNewUpdateIndex();

public:

	//Конструктор: инициалзиация объекта.
	LayoutsController(sf::RenderWindow* MainWindow, Settings* ObjectSettings);

	//Устанавливает указатели на время кадра.
	void SetElapsedTimeContainers(double* GlobalTimeAsSeconds, double* GlobalTimeAsMiliseconds, unsigned long long int* GlobalTimeAsMicroseconds);

	//Обновление текущего слоя и его ответа.
	void Update();

};





