#pragma once

#include <SFML/Graphics.hpp>

#include "../EvolvGen.h"

#include "../GUI/KeystrokesProcessing.h"
#include "../GUI/CenteredLabel.h"
#include "../GUI/TextBox.h"
#include "../GUI/Button.h"

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

	sf::Image Test;

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