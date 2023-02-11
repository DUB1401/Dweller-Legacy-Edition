#pragma once

#include "../MouseProcessing/MouseProcessing.h"
#include "../EvolvGen.h"
#include "../GUI.h"

namespace DUBGUI {

	// Текстовое поле.
	class TextBox : public ObjectGUI {
	private:

		//---> Данные.
		//======================================================================================================================//
		// Контейнер значений: является ли строка первой в параграфе.
		std::vector<bool> IsFirstStringOfParagraph;
		// Строки оригинального текста.
		std::vector<std::wstring> StringsArray;
		// Текущее состояние кнопки.
		Status TextBoxStatus = Status::Normal;
		// Количество отображаемых строк. При значении 0 отображение не ограничивается.
		unsigned int DisplayedStringsCount = 0;
		// Координаты в окне.
		sf::Vector2f Position = { 0.f, 0.f };
		// Промежуток между параграфами в долях высоты строки при указанном шрифте.
		unsigned int ParagraphSpacing = 0.f;
		// Индекс верхней отображаемой строки.
		int UpperDisplayedStringIndex = 0;
		// Индекс нижней отображаемой строки.
		int LowerDisplayedStringIndex;
		// Указатель на окно отрисовки.
		sf::RenderWindow* MainWindow;
		// Размер блока, внутри которого находится текст.
		sf::Vector2u BlockSize;
		// Межстрочный промежуток в долях от установленного шрифтом.
		float LineSpacing = 1.f;

		//---> Свойства графических компонентов.
		//========================================================================================================================//
		// Цвет обводки.
		sf::Color OutlineColor = sf::Color::Black;
		// Цвет надписи.
		sf::Color TextColor = sf::Color::White;
		// Размер символа.
		unsigned int CharacterSize = 12;
		// Дополнительные стили текста.
		sf::Text::Style TextStyle;
		// Толщина обводки.
		float OutlineThickness = 0.f;
		// Шрифт.
		sf::Font* TextFont;

		//---> Графические компоненты.
		//======================================================================================================================//
		// Обработчик взаимодействия с кнопками мыши.
		MouseProcessing MouseProcessingObject;
		// Отрисовываемая строка.
		std::vector<sf::Text> LabelStrings;

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

		// Прокручивает текст по переданному дельта-значению.
		void scroll(int ScrollDelta);

		// Устанавливает размер символа в пикселях.
		void setCharacterSize(unsigned int Size);

		// Устанавливает цвет текста.
		void setColor(sf::Color TextColor);

		// Устанавливает количество одновременно отображаемых строк.
		void setDisplayedStringsCount(unsigned int DisplayedStringsCount);

		// Устанавливает указатель на шрифт.
		void setFont(sf::Font* TextFont);

		// Устанавливает межстрочный интервал в долях от заданного шрифтом.
		void setLineSpacing(float LineSpacing);

		// Устанавливает цвет и толщину обводки.
		void setOutline(sf::Color OutlineColor, float Thickness);

		// Устанавливает список параграфов.
		void setParagraphsArray(std::vector<std::wstring> ParagraphsArray);

		// Устанавливает интервал между парграфами в долях от заданного шрифтом.
		void setParagraphSpacing(float ParagraphSpacing);

		// Устанавливает позицию в окне.
		void setPosition(float PositionX, float PositionY);

		// Устанавливает позицию в окне.
		void setPosition(sf::Vector2f Position);

		// Устанавливает дополнительные стили.
		void setStyle(sf::Text::Style TextStyle);

		// Отрисовывает и обновляет текстовое поле.
		Status update();

	};

}