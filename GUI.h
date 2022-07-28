#pragma once

#include <SFML/Graphics.hpp>

#include <Windows.h>

#include "EvolvGen.h"

//Обработка нажатия клавиши.
//TO-DO: подсчёт времени залипания, нажатие типа AnyKey.
class KeystrokesProcessing {
private:

	//Целевая клавиша.
	sf::Keyboard::Key TargetKey;
	//Была ли нажата клавиша в прошлом цикле.
	bool IsKeyWasPressed = false;


public:

	//Конструктор: пустой.
	KeystrokesProcessing();

	//Конструктор: задаёт обрабатываемую клавишу.
	KeystrokesProcessing(sf::Keyboard::Key TargetKey);

	//Задаёт клавишу для обработки.
	void SetKey(sf::Keyboard::Key TargetKe);

	//Проверка состояния клавиши.
	bool Update();


};

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

//Центрируемая надпись.
//TO-DO: обработка ошибок: высота надписи больше высоты блока, слово длиннее блока.
class CenteredLabel {
private:

	//---> Данные.
	//=======================================================================================================================//
	//Координаты в окне.
	sf::Vector2f WindowCoords = { 0.f, 0.f };
	//Размер блока, внутри которого происходит выравнивание.
	sf::Vector2u BlockSize;
	//Центрируемая строка.
	std::wstring Str;
	//Используемое пространство ширины блока.
	float UsedSpace = 1.f;
	//Межстрочный интервал в долях размера символа.
	float LineSpacing = 0.05;
	//Положение начала блока.
	sf::Vector2f Position = { 0, 0 };

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
	//Дополнительный стиль текста.
	sf::Text::Style TextStyle;
	//Вектор отрисовываемых строчек надписи.
	std::vector<sf::Text> Label;

protected:

	//---> Функции обработки.
	//=======================================================================================================================//
	//Позиционирование строки по середине блока.
	void Centering();
	//Применение стиля ко всем спрайтам надписи.
	void AppendStyle();

public:

	//Конструктор: пустой.
	CenteredLabel();

	//Задаёт окно отрисовки, центрируемую строку и размеры блока отображения. Вызывать после установки всех стилей.
	void Initialize(sf::RenderWindow* MainWindow, std::wstring Str, sf::Vector2u BlockSize);

	//Передача указателя на шрифт.
	void SetFont(sf::Font* TextFont);

	//Задаёт долю ширины блока, в которую нужно вписать текст (отступ от левого и правого края). По умолчанию 1.
	void SetUsedSpace(float UsedSpace);

	//Устанавливает координаты блока.
	void SetPosition(sf::Vector2f Postion);

	//Устанавливает координаты блока.
	void SetPosition(float PostionX, float PostionY);

	//Установка цвета надписи. По умолчанию белый.
	void SetColor(sf::Color TextColor);

	//Установка дополнительного стиля для текста.
	void SetStyle(sf::Text::Style TextStyle);

	//Устанавливает межстрочный интервал в долях размера символа. По умолчанию 0.05 для компенсации артефактов шрифта.
	void SetLineSpacing(float LineSpacing);

	//Установка размера символов. По умолчанию равно 12.
	void SetCharacterSize(unsigned int Size);

	//Установка новой строки и перерасчёт выравнивания.
	void SetString(std::wstring Str);

	//Отрисовка центрированной надписи.
	void Update();

};

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