#pragma once

#pragma warning(disable : 4305)

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <iostream>
#include <Windows.h>

#include "GUI.h"

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

//Вступительный ролик.
//TO-DO: выставить время кадров, исчезновение надписи с пропуском через 5 секунд.
class Intro {
private:

	//---> Данные.
	//=======================================================================================================================//
	//Указатель на время последнего кадра в секундах.
	double* GlobalTimeAsSeconds;
	//Указатель на время последнего кадра в микросекундах.
	unsigned long long int* GlobalTimeAsMicroseconds;
	//Воспроизводимая мелодия.
	sf::Music IntroMusic;
	//Прошедшее время для перелистывания иллюстраций.
	double ElapsedTime = 0;
	//Индекс отрисовываемой иллюстрации.
	unsigned int IllustrationIndex = 0;
	//Индекс отображаемой части пролога.
	unsigned int BookIndex = 0;
	//Индекс длительности кадра.
	unsigned int TimeIndex = 0;
	//Индекс длительности кадра.
	std::vector<double> EveryFrameTime = { 3.5, 3.0, 4.0, 3.0, 4.0, 3.0, 5.5, 3.0, 4.0, 3.0, 4.0, 3.0, 3.5, 3.0, 3.5, 3.0, 6.0, 1.5 };
	//Включено ли воспроизведение.
	bool IsEnabled = false;
	//Коэффициент прозрачности для анимации затухания.
	double TransparencyCoefficient = 255;
	//Начать проигрывание анимации проявления.
	bool StartAppearancesAnimation = true;
	//Начать проигрывание анимации затухания.
	bool StartAttenuationAnimation = false;
	//Проигрывалась ли в этом кадре анимация затухания.
	bool IsAttenuationAnimationWasPlayed = false;

	//Обработчик нажатий пробела для пропуска ролика.
	KeystrokesProcessing KP_Space;
	//Количество нажатий пробела.
	unsigned int SpaceWasPresed = 0;

	//---> Графические компоненты.
	//=======================================================================================================================//
	//Указатель на окно отрисовки.
	sf::RenderWindow* MainWindow;
	//Текст вступительного ролика.
	std::vector<std::wstring> Book;
	//Текстуры истории.
	std::vector<sf::Texture> StoryTextures;
	//Спрайты истории.
	std::vector<sf::Sprite> StorySprites;
	//Центрированные истории.
	std::vector<CenteredLabel> StoryText;
	//Шрифт надписей.
	sf::Font TextFont;
	//Чёрный прямоугольник для анимации затухания.
	sf::RectangleShape BlackRect;
	//Надпись для инструкции по прерыванию ролика.
	CenteredLabel PressAnyKey;

protected:

	//---> Анимация затухания и проявления.
	//=======================================================================================================================//
	//Установка анимации проявления.
	void InitializeAppearancesAnimation();
	//Воспроизведение анимации проявления.
	void PlayAppearancesAnimation();
	//Установка анимации затухания.
	void InitializeAttenuationAnimation();
	//Воспроизведение анимации затухания.
	void PlayAttenuationAnimation();

public:

	//Конструктор: задаёт окно отрисовки технических данных и счётчик времени.
	Intro(sf::RenderWindow* MainWindow, double* GlobalTimeAsSeconds, unsigned long long int* GlobalTimeAsMicroseconds);

	//Запускает вступительный ролик. Возвращает false, если не удалось или возникли ошибки.
	bool Start();

	//Останавливает вступительный ролик.
	void End();

	//Выполнение цикла обновления класса.
	void Update();
};

//Титры.
//TO-DO: кнопка закрытия, закрывать по нажатию на ESC.
class Credits {
private:

	//---> Данные.
	//=======================================================================================================================//
	//Указатель на время последнего кадра в секундах.
	double* GlobalTimeAsSeconds;
	//Количество отрисовываемых фрагментов рамок по оси Х.
	unsigned int BorderAmountX;
	//Количество отрисовываемых фрагментов рамок по оси Y.
	unsigned int BorderAmountY;

	//---> Графические компоненты.
	//=======================================================================================================================//
	//Указатель на окно отрисовки.
	sf::RenderWindow* MainWindow;
	//Текст титров.
	std::vector<std::wstring> CreditsLines;
	//Шрифт надписей.
	sf::Font TextFont;
	//Текстовый контейнер.
	TextBox TextBoxObject;
	//Текстура рамок.
	sf::Texture BorderTexture;
	//Спрайт рамок.
	sf::Sprite BorderSprite;
	//Текстура фона заголовка.
	sf::Texture HeaderTexture;
	//Спрайт фона заголовка.
	sf::Sprite HeaderSprite;
	//Центрируемая надпись заголовка.
	CenteredLabel CenteredLabelObject;
	//Текстура фоновой эмблемы.
	sf::Texture EmblemTexture;
	//Спрайт фоновой эмблемы.
	sf::Sprite EmblemSprite;


public:

	//Конструктор: задаёт окно отрисовки технических данных.
	Credits(sf::RenderWindow* MainWindow, double* GlobalTimeAsSeconds);

	//Выполнение цикла обновления класса.
	void Update();
};























//Перечисление типов играбельных классов.
enum CharacterClasses { Warrior = 1, Wizard = 2, Archer = 3 };

//Структура хараткеристик персонажа.
struct PlayerStats {
	unsigned int HP;
	unsigned int MP;
	unsigned int Damage;
	unsigned int Armor;
	unsigned int Intelligence;
};

class Player {
private:

	//---> Данные.
	//=======================================================================================================================//
	//Класс игрока.
	unsigned int PlayerClass;
	//Характеристики игрока.
	PlayerStats GamerStats;

public:



};

class World {
private:

	//---> Данные.
	//=======================================================================================================================//
	//Указатель на время последнего кадра в секундах.
	double* GlobalTimeAsSeconds;

	//---> Графические компоненты.
	//=======================================================================================================================//
	//Указатель на окно отрисовки.
	sf::RenderWindow* MainWindow;

public:

	//Конструктор: задаёт окно отрисовки технических данных и счётчик времени.
	World(sf::RenderWindow* MainWindow, double* GlobalTimeAsSeconds);

	//Выполнение цикла обновления класса.
	void Update();
};

class Game {
private:

	//---> Данные.
	//=======================================================================================================================//
	//Указатель на время последнего кадра в секундах.
	double* GlobalTimeAsSeconds;

	//---> Графические компоненты.
	//=======================================================================================================================//
	//Указатель на окно отрисовки.
	sf::RenderWindow* MainWindow;

	//---> Взаимодействие с миром.
	//=======================================================================================================================//
	//Отрисовка мира.
	void DrawMap();

public:

	//Конструктор: задаёт окно отрисовки технических данных и счётчик времени.
	Game(sf::RenderWindow* MainWindow, double* GlobalTimeAsSeconds);

	//Выполнение цикла обновления класса.
	void Update();
};