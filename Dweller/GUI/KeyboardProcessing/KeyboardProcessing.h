#pragma once

#include "../EvolvGen.h"
#include "../GUI.h"

namespace DUBGUI {

	// Обработчик взаимодействий с клавиатурой.
	class KeyboardProcessing {
	private:

		//---> Данные
		//========================================================================================================================//
		// Двусвязный контейнер значений обрабатываемых клавиш: была ли нажата клавиша в предыдущем цикле.
		std::map<sf::Keyboard::Key, bool> KeyInPreviousCycleStatus;

	public:

		// Конструктор: пустой.
		KeyboardProcessing();

		// Конструктор: добавляет клавишу в обработчик.
		KeyboardProcessing(sf::Keyboard::Key Key);

		// Удаляет клавишу из обработчика.
		void removeKey(sf::Keyboard::Key Key);

		// Добавляет клавишу в обработчик.
		void setKey(sf::Keyboard::Key Key);

		// Обрабатывает взаимодействие с указанной клавишей.
		bool updateKey(sf::Keyboard::Key Key);

		// Обрабатывает взаимодействие с указанной клавишей, а также позволяет использовать обработку залипания.
		bool updateKey(sf::Keyboard::Key Key, bool EnableSticking);

	};

}