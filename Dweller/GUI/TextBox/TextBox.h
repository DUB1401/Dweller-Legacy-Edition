#pragma once

#include "../EvolvGen.h"

// Область для отображения текста с автопереносом строк.
class TextBox {
private:

	//---> Данные.
	//======================================================================================================================//
	// Координаты в окне.
	sf::Vector2f Position = { 0.f, 0.f };
	// Размер блока, внутри которого находится текст.
	sf::Vector2u BlockSize;
	// Межстрочный промежуток в долях от установленного шрифтом.
	float LineSpacing = 1.f;
	// Промежуток между параграфами в долях высоты строки при указанном шрифте.
	unsigned int ParagraphSpacing = 0.f;
	// Отрисовываемая строка.
	std::vector<sf::Text> LabelStrings;
	// Строки оригинального текста.
	std::vector<std::wstring> StringsArray;
	// Контейнер значений: является ли строка первой в параграфе.
	std::vector<bool> IsFirstStringOfParagraph;
	// Количество отображаемых строк. При значении 0 отображение не ограничивается.
	unsigned int DisplayedStringsCount = 4;
	// Индекс верхней отображаемой строки.
	int UpperDisplayedStringIndex = 0;
	// Индекс нижней отображаемой строки.
	int LowerDisplayedStringIndex;

	//---> Графические компоненты.
	//======================================================================================================================//
	// Указатель на окно отрисовки.
	sf::RenderWindow* MainWindow;
	// Цвет надписи.
	sf::Color TextColor = sf::Color::White;
	// Шрифт.
	sf::Font* TextFont;
	// Размер символа.
	unsigned int CharacterSize = 12;
	// Цвет обводки.
	sf::Color OutlineColor = sf::Color::Black;
	// Толщина обводки.
	float Thickness = 0.f;
	// Дополнительные стили текста.
	sf::Text::Style TextStyle;

protected:

	//---> Функции обработки.
	//======================================================================================================================//
	// Рассчитывает индекс нижней отображаемой строки.
	void CalculateLowerDisplayedStringIndex();
	// Рассчитывает координаты строк.
	void CalculateLabelStringsCoords();
	// Применяет стили к строкам и проводит необходимые для инициализации расчёты.
	void AppendStyles();
	// Разбивает параграфы на строки при необходимости переноса.
	std::vector<std::wstring> ParagraphBreak(std::wstring Str, unsigned int BlockSizeX);

public:

	// Конструктор: пустой.
	TextBox();

	// Инициализатор: задаёт окно отрисовки и размеры блока отображения. Вызывать после установки всех свойств.
	void initialize(sf::RenderWindow* MainWindow, sf::Vector2u BlockSize);

	// Устанавливает позицию в окне.
	void setPosition(sf::Vector2f Position);

	// Устанавливает позицию в окне.
	void setPosition(float PositionX, float PositionY);

	// Устанавливает указатель на шрифт.
	void setFont(sf::Font* TextFont);

	// Устанавливает межстрочный интервал в долях от заданного шрифтом.
	void setLineSpacing(float LineSpacing);

	// Устанавливает интервал между парграфами в долях от заданного шрифтом.
	void setParagraphSpacing(float ParagraphSpacing);

	// Устанавливает цвет текста.
	void setColor(sf::Color TextColor);

	// Устанавливает дополнительные стили.
	void setStyle(sf::Text::Style TextStyle);

	// Устанавливает цвет и толщину обводки.
	void setOutline(sf::Color OutlineColor, float Thickness);

	// Устанавливает размер символа в пикселях.
	void setCharacterSize(unsigned int Size);

	// Устанавливает список параграфов.
	void setParagraphsArray(std::vector<std::wstring> ParagraphsArray);

	// Устанавливает количество одновременно отображаемых строк.
	void setDisplayedStringsCount(unsigned int DisplayedStringsCount);

	// Прокручивает текст по переданному дельта-значению.
	void scroll(int ScrollDelta);

	// Отрисовывает текст.
	void update();


};