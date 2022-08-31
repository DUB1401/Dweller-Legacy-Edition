#pragma once

#include "../EvolvGen.h"

//Область для отображения текста с автопереносом строк.
//TO-DO: позиционирование контейнера, связать со скроллом.
class TextBox {
private:

	//---> Данные.
	//=======================================================================================================================//
	//Координаты в окне.
	sf::Vector2f Position = { 0, 0 };
	//Размер блока, внутри которого находится текст.
	sf::Vector2u BlockSize;
	//Межстрочный промежуток в долях от установленного шрифтом.
	float LineSpacing = 1.0;

	//---> Графические компоненты.
	//=======================================================================================================================//
	//Указатель на окно отрисовки.
	sf::RenderWindow* MainWindow;
	//Цвет надписи.
	sf::Color TextColor = sf::Color::White;
	//Шрифт.
	sf::Font* TextFont;
	//Размер символа.
	unsigned int CharacterSize = 12;
	//Цвет обводки.
	sf::Color OutlineColor = sf::Color::Black;
	//Толщина обводки.
	float Thickness = 0;
	//Дополнительный стиль текста.
	sf::Text::Style TextStyle;
	//Отрисовываемая строка.
	sf::Text Label;
	//Строки текста.
	std::vector<std::wstring> StringsArray;

protected:

	//---> Функции обработки.
	//=======================================================================================================================//
	//Применение стилей к надписи.
	void AppendStyle();
	//Разбитие строки на подстроки методом подстановки символов разрыва строки Windows.
	std::wstring LineBreak(sf::Text TextBufer, sf::Font* TextFont, std::wstring Str, unsigned int BlockSizeX);

public:

	//Конструктор: пустой.
	TextBox();

	//Задаёт окно отрисовки и размеры блока отображения. Вызывать после установки всех стилей.
	void Initialize(sf::RenderWindow* MainWindow, sf::Vector2u BlockSize);

	//Устанавливает позицию в окне.
	void SetPosition(sf::Vector2f Position);

	//Устанавливает позицию в окне.
	void SetPosition(float PositionX, float PositionY);

	//Передача указателя на шрифт.
	void SetFont(sf::Font* TextFont);

	//Задаёт межстрочный промежуток в долях от установленного шрифтом. По умолчанию 1.
	void SetLineSpacing(float LineSpacing);

	//Установка цвета надписи. По умолчанию белый.
	void SetColor(sf::Color TextColor);

	//Установка дополнительного стиля для текста.
	void SetStyle(sf::Text::Style TextStyle);

	//Установка текста и толщины обводки.
	void SetOutline(sf::Color OutlineColor, float Thickness);

	//Установка размера символов. По умолчанию равно 12.
	void SetCharacterSize(unsigned int Size);

	//Установка текста.
	void SetStringsArray(std::vector<std::wstring> StringsArray);

	//Отрисовка центрированной надписи.
	void Update();


};