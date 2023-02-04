#pragma once

#include "../EvolvGen.h"

#include "../Source/Settings.h"
#include "../Source/Data.h"

// Отрисовка мира.
class WorldRenderer {
private:

	//---> Данные.
	//=======================================================================================================================//
	// Указатель на время последнего кадра в секундах.
	double* GlobalTimeAsSeconds;
	// Ответ для обработчика слоёв.
	LayoutAnswer Answer;
	// Указатель на глобальные настройки.
	Settings* ObjectSettings;
	// Список текстовых ID тайлов.
	std::vector<std::string> TileList;
	// Матрица тайлов мира.
	std::vector<std::vector<std::string>> World = {
		{"stone-wall", "stone-wall", "stone-wall", "stone-wall", "stone-wall", "stone-wall"},
		{"stone-wall", "grass", "grass", "grass", "grass", "stone-wall"},
		{"stone-wall", "grass", "grass", "grass", "grass", "stone-wall"},
		{"stone-wall", "grass", "grass", "grass", "grass", "stone-wall"},
		{"stone-wall", "grass", "grass", "grass", "grass", "stone-wall"},
		{"stone-wall", "grass", "grass", "grass", "grass", "stone-wall"},
		{"stone-wall", "grass", "grass", "grass", "grass", "stone-wall"},
		{"stone-wall", "grass", "grass", "grass", "grass", "stone-wall"},
		{"stone-wall", "grass", "grass", "grass", "grass", "stone-wall"},
		{"stone-wall", "grass", "grass", "grass", "grass", "stone-wall"},
		{"stone-wall", "grass", "grass", "grass", "grass", "stone-wall"},
		{"stone-wall", "grass", "grass", "grass", "grass", "stone-wall"},
		{"stone-wall", "grass", "grass", "grass", "grass", "stone-wall"},
		{"stone-wall", "grass", "grass", "grass", "grass", "stone-wall"},
		{"stone-wall", "grass", "grass", "grass", "grass", "stone-wall"},
		{"stone-wall", "grass", "grass", "grass", "grass", "stone-wall"},
		{"stone-wall", "grass", "grass", "grass", "grass", "stone-wall"},
		{"stone-wall", "grass", "grass", "grass", "grass", "stone-wall"},
		{"stone-wall", "grass", "grass", "grass", "grass", "stone-wall"},
		{"stone-wall", "grass", "grass", "grass", "grass", "stone-wall"},
		{"stone-wall", "grass", "grass", "grass", "grass", "stone-wall"},
		{"stone-wall", "grass", "grass", "grass", "grass", "stone-wall"},
		{"stone-wall", "grass", "grass", "grass", "grass", "stone-wall"},
		{"stone-wall", "grass", "grass", "grass", "grass", "stone-wall"},
		{"stone-wall", "grass", "grass", "grass", "grass", "stone-wall"},
		{"stone-wall", "grass", "grass", "grass", "grass", "stone-wall"},
		{"stone-wall", "grass", "grass", "grass", "grass", "stone-wall"},
		{"stone-wall", "grass", "grass", "grass", "grass", "stone-wall"},
		{"stone-wall", "grass", "grass", "grass", "grass", "stone-wall"},
		{"stone-wall", "grass", "grass", "grass", "grass", "stone-wall"},
		{"stone-wall", "grass", "grass", "grass", "grass", "stone-wall"},
		{"stone-wall", "stone-wall", "stone-wall", "stone-wall", "stone-wall", "stone-wall"}
	};

	//---> Графические компоненты.
	//=======================================================================================================================//
	// Указатель на окно отрисовки.
	sf::RenderWindow* MainWindow;
	// Хранилище текстур тайлов.
	std::map<std::string, sf::Texture> WorldTextures;
	// Хранилище спрайтов тайлов.
	std::map<std::string, sf::Sprite> WorldSprites;

public:

	// Конструктор: задаёт окно отрисовки мира, ссылку на настройки, время кадра.
	WorldRenderer(sf::RenderWindow* MainWindow, Settings* ObjectSettings, double* GlobalTimeAsSeconds);

	// Выполнение цикла обновления класса.
	LayoutAnswer Update();




};