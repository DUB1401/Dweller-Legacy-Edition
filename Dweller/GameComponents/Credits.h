#pragma once

#include "../GUI/KeyboardProcessing/KeyboardProcessing.h"
#include "../GUI/CenteredLabel/CenteredLabel.h"
#include "../GUI/TextBox/TextBox.h"
#include "../GUI/Button/Button.h"
#include "../GUI/EvolvGen.h"

#include "../Source/Settings.h"
#include "../Source/Data.h"

// Об игре.
class Credits {
private:

	//---> Данные.
	//========================================================================================================================//
	// Указатель на время последнего кадра в секундах.
	double* GlobalTimeAsSeconds;
	// Количество отрисовываемых фрагментов рамок по оси Х.
	unsigned int BorderAmountX;
	// Количество отрисовываемых фрагментов рамок по оси Y.
	unsigned int BorderAmountY;
	// Ответ для обработчика слоёв.
	LayoutAnswer Answer;
	// Указатель на глобальные настройки.
	Settings* ObjectSettings;

	//---> Графические компоненты.
	//========================================================================================================================//
	// Указатель на окно отрисовки.
	sf::RenderWindow* MainWindow;
	// Структура коммуникаций с модулями.
	CommunicationData* ComData;
	// Текст титров.
	std::vector<std::wstring> CreditsLines;
	// Шрифт надписей.
	sf::Font TextFont;
	// Текстовый контейнер.
	DUBGUI::TextBox TextBoxObject;
	// Текстура рамок.
	sf::Texture BorderTexture;
	// Спрайт рамок.
	sf::Sprite BorderSprite;
	// Текстура фона заголовка.
	sf::Texture HeaderTexture;
	// Спрайт фона заголовка.
	sf::Sprite HeaderSprite;
	// Центрируемая надпись заголовка.
	DUBGUI::CenteredLabel CenteredLabelObject;
	// Текстура фоновой эмблемы.
	sf::Texture EmblemTexture;
	// Спрайт фоновой эмблемы.
	sf::Sprite EmblemSprite;
	// Кнопка закрытия титров.
	DUBGUI::Button BT_Close;
	// Обработчик взаимодействий с клавиатурой.
	DUBGUI::KeyboardProcessing KeyboardProcessingObject;

protected:

	//---> Функции обработки.
	//========================================================================================================================//
	// Закрытие титров.
	void Close(std::string To, std::string From);

public:

	// Конструктор: задаёт окно отрисовки технических данных.
	Credits(sf::RenderWindow* MainWindow, CommunicationData* ComData, Settings* ObjectSettings, double* GlobalTimeAsSeconds);

	// Выполнение цикла обновления класса.
	LayoutAnswer Update();

};