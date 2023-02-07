#pragma once

#include "../EvolvGen.h"

// Центрируемая надпись.
// TO-DO: обработка ошибок: высота надписи больше высоты блока, слово длиннее блока.
class CenteredLabel {
private:

	//---> Данные.
	//========================================================================================================================//
	// Координаты в окне.
	sf::Vector2f WindowCoords = { 0.f, 0.f };
	// Размер блока, внутри которого происходит выравнивание.
	sf::Vector2u BlockSize;
	// Центрируемая строка.
	std::wstring Str;
	// Используемое пространство ширины блока.
	float UsedSpace = 1.f;
	// Межстрочный интервал в долях размера символа.
	float LineSpacing = 0.05;
	// Положение начала блока.
	sf::Vector2f Position = { 0, 0 };
	// Ширина обводки.
	float OutlineThickness = 0;
	// Цвет обводки.
	sf::Color OutlineColor = sf::Color::Black;

	//---> Графические компоненты.
	//========================================================================================================================//
	// Указатель на окно отрисовки.
	sf::RenderWindow* MainWindow;
	// Цвет надписи.
	sf::Color TextColor = sf::Color::White;
	// Шрифт.
	sf::Font* TextFont;
	// Размер символа.
	unsigned int CharacterSize = 12;
	// Дополнительный стиль текста.
	sf::Text::Style TextStyle;
	// Вектор отрисовываемых строчек надписи.
	std::vector<sf::Text> Label;

protected:

	//---> Функции обработки.
	//========================================================================================================================//
	// Позиционирование строки по середине блока.
	void Centering();
	// Применение стиля ко всем спрайтам надписи.
	void AppendStyle();

public:

	// Конструктор: пустой.
	CenteredLabel();

	// Задаёт окно отрисовки, центрируемую строку и размеры блока отображения. Вызывать после установки всех стилей.
	void Initialize(sf::RenderWindow* MainWindow, std::wstring Str, sf::Vector2u BlockSize);

	// Передача указателя на шрифт.
	void SetFont(sf::Font* TextFont);

	// Задаёт долю ширины блока, в которую нужно вписать текст (отступ от левого и правого края). По умолчанию 1.
	void SetUsedSpace(float UsedSpace);

	// Устанавливает координаты блока.
	void SetPosition(sf::Vector2f Postion);

	// Устанавливает координаты блока.
	void SetPosition(float PostionX, float PostionY);

	// Установка цвета надписи. По умолчанию белый.
	void SetColor(sf::Color TextColor);

	// Установка дополнительного стиля для текста.
	void SetStyle(sf::Text::Style TextStyle);

	// Устанавливает межстрочный интервал в долях размера символа. По умолчанию 0.05 для компенсации артефактов шрифта.
	void SetLineSpacing(float LineSpacing);

	// Установка размера символов. По умолчанию равно 12.
	void SetCharacterSize(unsigned int Size);

	// Задаёт обводку.
	void SetOutline(sf::Color OutlineColor, float OutlineThickness);

	// Установка новой строки и перерасчёт выравнивания.
	void SetString(std::wstring Str);

	// Отрисовка центрированной надписи.
	void Update();

};