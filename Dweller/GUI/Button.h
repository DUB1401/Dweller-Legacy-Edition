#pragma once

#include <SFML/Graphics.hpp>

#include "../EvolvGen.h"

//Графическое представление кнопки.
//TO-DO: круглая кнопка, одно- и двуспрайтовый режим.
class Button {
private:

	//---> Данные.
	//=======================================================================================================================//
	//Координаты в окне.
	sf::Vector2f Position = { 0.f, 0.f };
	//Размер кнопки.
	sf::Vector2u Size;
	//Текущее состояние кнопки.
	unsigned int ButtonStatus = 0;
	//Была ли нажата кнопка в прошлом цикле.
	bool ButtonWasPressed = false;
	//Масштаб спрайта.
	sf::Vector2f Scale = { 1.f, 1.f };

	//---> Графические компоненты.
	//=======================================================================================================================//
	//Указатель на окно отрисовки.
	sf::RenderWindow* MainWindow;
	//Текстура кнопки.
	sf::Texture ButtonTexture;
	//Спрайты кнопки.
	std::vector<sf::Sprite> ButtonSprites;

protected:

	//---> Функции обработки.
	//=======================================================================================================================//
	//Проверка попадания курсора в область кнопки.
	bool CheckMouseHover();
	//Удаляет неиспользуемые индексы для доступа к спрайтам из перечисления стилей.
	unsigned int Normalize(unsigned int Index);

public:

	//Перечисления стилей.
	enum { Normal = 0, Hover, Active, Clicked };

	//Конструктор: пустой.
	Button();

	//Задаёт окно отрисовки.
	void Initialize(sf::RenderWindow* MainWindow);

	//Задаёт окно отрисовки и базовый размер спрайта.
	void Initialize(sf::RenderWindow* MainWindow, sf::Vector2u Size);

	//Устанавливает позицию в окне.
	void SetPosition(sf::Vector2f Position);

	//Устанавливает позицию в окне.
	void SetPosition(float PositionX, float PositionY);

	//Задаёт базовый размер спрайта.
	void SetSize(sf::Vector2u Size);

	//Задаёт базовый размер спрайта.
	void SetSize(unsigned int SizeX, unsigned int SizeY);

	//Задаёт масштаб спрайта.
	void SetScale(float Scale);

	//Загружает текстуру кнопки.
	bool LoadTexture(std::string Path, unsigned int SpriteLinesCount);

	//Отрисовка центрированной надписи. Возвращает статус кнопки.
	unsigned int Update();

};