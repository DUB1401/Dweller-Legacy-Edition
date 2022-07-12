#pragma once

#include <SFML/Graphics.hpp>

//Обработка нажатия клавиши.
//TO-DO: обработка ошибок: высота надписи больше высоты блока, слово длиннее блока.
class KeystrokesProcessing {
private:

	//Целевая клавиша.
	sf::Keyboard::Key TargetKey;
	//Была ли нажата клавиша в прошлом цикле.
	bool IsKeyWasPressed = false;


public:

	//Конструктор: задаёт обрабатываемую клавишу и режим.
	KeystrokesProcessing(sf::Keyboard::Key TargetKey) {
		this->TargetKey = TargetKey;
	}

	//Проверка состояния клавиши.
	bool Update() {
		//Проверка нажатия клавиши.
		if (sf::Keyboard::isKeyPressed(TargetKey))

		return 1;
	}


};

