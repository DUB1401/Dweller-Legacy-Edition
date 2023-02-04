#pragma once

#include "../EvolvGen.h"

// Ответ от обновляемых слоёв.
struct LayoutAnswer {
	//Откуда пришёл ответ.
	std::string from;
	//На какой слой переключиться.
	std::string to;
	//Очистка контейнера.
	void Clear();
	//Проверка на пустоту.
	bool Empty();
	//Задаёт новое значение, если оно не пустое.
	void Assign(LayoutAnswer Value);
};