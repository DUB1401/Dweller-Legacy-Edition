#pragma once

#include "../GUI/EvolvGen.h"

// Ответ от обновляемых слоёв.
struct LayoutAnswer {
	// Откуда пришёл ответ.
	std::string from;
	// На какой слой переключиться.
	std::string to;
	// Очистка контейнера.
	void Clear();
	// Проверка на пустоту.
	bool Empty();
	// Задаёт новое значение, если оно не пустое.
	void Assign(LayoutAnswer Value);
};

// Структура коммуникаций с модулями.
struct CommunicationData {
	// Указатель на окно отрисовки.
	sf::RenderWindow* MainWindow;
	// Указатель на время кадра в секундах.
	double* GlobalTimeAsSeconds;
	// Указатель на время исполнения кадра в миллисекундах.
	double* GlobalTimeAsMilliseconds;
	// Указатель на время исполнения кадра в микросекундах.
	unsigned long long int* GlobalTimeAsMicroseconds;
	// Дельта прокрутки колёсика мыши.
	int* MouseWheelScrollDelta;

};