#include "KeyboardProcessing.h"

//---> KeyboardProcessing
//========================================================================================================================//

namespace DUBGUI {

	// Конструктор: пустой.
	KeyboardProcessing::KeyboardProcessing() {

	}

	// Конструктор: добавляет клавишу в обработчик.
	KeyboardProcessing::KeyboardProcessing(sf::Keyboard::Key Key) {
		KeyInPreviousCycleStatus[Key] = false;
	}

	// Удаляет клавишу из обработчика.
	void KeyboardProcessing::removeKey(sf::Keyboard::Key Key) {
		KeyInPreviousCycleStatus.erase(Key);
	}

	// Добавляет клавишу в обработчик.
	void KeyboardProcessing::setKey(sf::Keyboard::Key Key) {
		KeyInPreviousCycleStatus[Key] = false;
	}

	// Обрабатывает взаимодействие с указанной клавишей.
	bool KeyboardProcessing::updateKey(sf::Keyboard::Key Key) {
		// Статус: произошло ли в данном цикле нажатие клавиши.
		bool IsKeyPressed = false;

		// Нажата ли клавиша в данный момент при условии, что в предыдущем цикле она не была нажата.
		if (sf::Keyboard::isKeyPressed(Key) && !KeyInPreviousCycleStatus[Key]) {
			KeyInPreviousCycleStatus[Key] = true;
			IsKeyPressed = true;
		}

		// Если клавишу отпустили, снять активный статус (предотвращает множественное возвращение активного статуса).
		if (!sf::Keyboard::isKeyPressed(Key)) KeyInPreviousCycleStatus[Key] = false;

		return IsKeyPressed;
	}

	// Обрабатывает взаимодействие с указанной клавишей, а также позволяет использовать обработку залипания.
	bool KeyboardProcessing::updateKey(sf::Keyboard::Key Key, bool EnableSticking) {
		// Статус: произошло ли в данном цикле нажатие клавиши.
		bool IsKeyPressed = false;

		// Нажата ли клавиша в данный момент при условии активированной обработки залипания.
		if (sf::Keyboard::isKeyPressed(Key) && EnableSticking) IsKeyPressed = true;

		// Нажата ли клавиша в данный момент при условии, что в предыдущем цикле она не была нажата.
		if (sf::Keyboard::isKeyPressed(Key) && !KeyInPreviousCycleStatus[Key]) {
			KeyInPreviousCycleStatus[Key] = true;
			if (!EnableSticking) IsKeyPressed = true;
		}

		// Если клавишу отпустили, снять активный статус (предотвращает множественное возвращение активного статуса).
		if (!sf::Keyboard::isKeyPressed(Key)) KeyInPreviousCycleStatus[Key] = false;

		return IsKeyPressed;
	}

}