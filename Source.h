#pragma once

#pragma warning(disable : 4305)

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <iostream>
#include <Windows.h>

#include "GUI.h"
#include "EvolvGen.h"

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
//TO-DO: скроллинг титров.
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
	//Ответ для обработчика меню.
	std::string Answer = "";

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
	//Кнопка закрытия титров.
	Button BT_Close;
	//Обработчик закрытия по Escape.
	KeystrokesProcessing KP_Escape;

protected:

	//---> Функции обработки.
	//=======================================================================================================================//
	//Закрытие титров.
	void Close();

public:

	//Конструктор: задаёт окно отрисовки технических данных.
	Credits(sf::RenderWindow* MainWindow, double* GlobalTimeAsSeconds);

	//Выполнение цикла обновления класса.
	std::string Update();
};


//Главное меню.
//TO-DO: сплэш-надписи, включение вступительного ролика.
class MainMenu {
private:

	//---> Данные.
	//=======================================================================================================================//
	//Ответ для обработчика меню.
	std::string Answer = "";
	//Фоновая музыка.
	sf::Music BackgroundMusic;
	//Звуковые эффекты для кнопок меню.
	sf::Music SoundEffect;
	//Перечисление кнопок меню.
	enum MenuButtons { Game = 0, Settings, Credits, Exit };
	//Список звуковых эффектов.
	std::vector<std::string> SoundsNames = { "menu_game", "menu_settings", "menu_credits", "menu_exit" };
	//Буфер для статусов кнопок.
	std::vector<unsigned int> ButtonsStatus = { 0, 0, 0, 0 };
	//Индекс последнего проигранного звукового эффекта для предотвращения залипания.
	unsigned int LastSoundEffectIndex = 0;
	//Подписи кнопок.
	std::vector<std::wstring> ButtonsLabels;

	//---> Графические компоненты.
	//=======================================================================================================================//
	//Указатель на окно отрисовки.
	sf::RenderWindow* MainWindow;
	//Текстура лого.
	sf::Texture LogoTexture;
	//Спрайт лого.
	sf::Sprite LogoSprite;
	//Текстура фона.
	sf::Texture BackgroundTexture;
	//Спрайт фона.
	sf::Sprite BackgroundSprite;
	//Кнопка «играть».
	Button BT_Play;
	//Кнопка «настройки».
	Button BT_Settings;
	//Кнопка «титры».
	Button BT_Credits;
	//Кнопка «выйти из игры».
	Button BT_Exit;
	//Подписи кнопок.
	CenteredLabel CL_Description;
	//Шрифт текста.
	sf::Font TextFont;
	//Версия игры.
	sf::Text GameVersion;

	//Шейдер заливки фона меню.
	//sf::Shader BackgroundShader;
	//Сцена.
	//sf::RenderTexture Frame;

protected:

	//---> Функции обработки.
	//=======================================================================================================================//
	//Закрытие главного меню.
	void Close(std::string Message);
	//Открытие главного меню.
	void Open();
	//Проигрывает звуковой эффект.
	void PlaySoundEffect(unsigned int Index);
	//Проверяет и обрабатывает взаимодействие с кнопками.
	void ButtonInteraction(unsigned int Index);

public:

	//Конструктор: задаёт окно отрисовки технических данных.
	MainMenu(sf::RenderWindow* MainWindow);

	//Выполнение цикла обновления класса.
	std::string Update();
};

