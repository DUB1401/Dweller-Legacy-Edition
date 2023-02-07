#include "KeystrokesProcessing.h"

//--->KeystrokesProcessing
//========================================================================================================================//

// Конструктор: пустой.
KeystrokesProcessing::KeystrokesProcessing() {

}

// Конструктор: задаёт обрабатываемую клавишу.
KeystrokesProcessing::KeystrokesProcessing(sf::Keyboard::Key TargetKey) {
	this->TargetKey = TargetKey;
}

// Задаёт клавишу для обработки.
void KeystrokesProcessing::SetKey(sf::Keyboard::Key TargetKey) {
	this->TargetKey = TargetKey;
}

// Проверка состояния клавиши.
bool KeystrokesProcessing::Update() {
	// Результат проверки.
	bool Result = false;

	// Проверка нажатия клавиши.
	if (sf::Keyboard::isKeyPressed(TargetKey) && !IsKeyWasPressed) {
		IsKeyWasPressed = true;
		Result = true;
	}

	// Снятие залипания, если клавишу отпустили.
	if (!sf::Keyboard::isKeyPressed(TargetKey)) IsKeyWasPressed = false;

	return Result;
}