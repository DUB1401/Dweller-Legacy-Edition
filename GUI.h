#pragma once

#include <SFML/Graphics.hpp>

//Обработка нажатия клавиши.
//TO-DO: смена обрабатываемой клавиши, подсчёт времени залипания.
class KeystrokesProcessing {
private:

	//Целевая клавиша.
	sf::Keyboard::Key TargetKey;
	//Была ли нажата клавиша в прошлом цикле.
	bool IsKeyWasPressed = false;


public:

	//Конструктор: пустой.
	KeystrokesProcessing();

	//Конструктор: задаёт обрабатываемую клавишу.
	KeystrokesProcessing(sf::Keyboard::Key TargetKey);

	//Задаёт клавишу для обработки.
	void SetKey(sf::Keyboard::Key TargetKe);

	//Проверка состояния клавиши.
	bool Update();


};

