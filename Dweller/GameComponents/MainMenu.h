#pragma once

#include "../EvolvGen.h"

#include "../GUI/CenteredLabel.h"
#include "../GUI/Button.h"

#include "../Source/Settings.h"
#include "../Source/Data.h"

//Главное меню.
//TO-DO: сплэш-надписи, включение вступительного ролика.
class MainMenu {
private:

	//---> Данные.
	//=======================================================================================================================//
	//Указатель на глобальные настройки.
	Settings* ObjectSettings;
	//Ответ для обработчика слоёв.
	LayoutAnswer Answer;
	//Фоновая музыка.
	sf::Music BackgroundMusic;
	//Звуковые эффекты для кнопок меню.
	sf::Music SoundEffect;
	//Перечисление кнопок меню.
	enum class MenuButtons { Game = 0, Settings, Credits, Exit };
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
	void Close(std::string To, std::string From);
	//Открытие главного меню.
	void Open();
	//Проигрывает звуковой эффект.
	void PlaySoundEffect(unsigned int Index);
	//Проверяет и обрабатывает взаимодействие с кнопками.
	void ButtonInteraction(unsigned int Index);

public:

	//Конструктор: задаёт окно отрисовки технических данных.
	MainMenu(sf::RenderWindow* MainWindow, Settings* ObjectSettings);

	//Выполнение цикла обновления класса.
	LayoutAnswer Update();
};