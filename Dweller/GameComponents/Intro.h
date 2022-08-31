#pragma once

#include "../EvolvGen.h"

#include "../GUI/KeystrokesProcessing.h"
#include "../GUI/CenteredLabel.h"

#include "../Source/Settings.h"
#include "../Source/Data.h"

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
	//Указатель на глобальные настройки.
	Settings* ObjectSettings;
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
	//Ответ для обработчика слоёв.
	LayoutAnswer Answer;

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
	Intro(sf::RenderWindow* MainWindow, Settings* ObjectSettings, double* GlobalTimeAsSeconds, unsigned long long int* GlobalTimeAsMicroseconds);

	//Запускает вступительный ролик. Возвращает false, если не удалось или возникли ошибки.
	bool Start();

	//Останавливает вступительный ролик.
	void End(std::string To, std::string From);

	//Выполнение цикла обновления класса.
	LayoutAnswer Update();
};