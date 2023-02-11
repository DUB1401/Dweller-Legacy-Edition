#pragma once

#include "../MouseProcessing/MouseProcessing.h"
#include "../EvolvGen.h"
#include "../GUI.h"

#include <numeric>

namespace DUBGUI {

	// Центрируемая надпись.
	class CenteredLabel : public ObjectGUI {
	private:

		//---> Данные.
		//========================================================================================================================//
		// Текущее состояние центрируемой надписи.
		Status CenteredLabelStatus = Status::Normal;
		// Положение начала блока.
		sf::Vector2f Position = { 0.f, 0.f };
		// Указатель на окно отрисовки.
		sf::RenderWindow* MainWindow;
		// Размер блока, внутрь которого происходит выравнивание.
		sf::Vector2u BlockSize;
		// Используемое пространство ширины блока.
		float UsedSpace = 1.f;
		// Центрируемая строка.
		std::wstring Str;

		//---> Свойства графических компонентов.
		//========================================================================================================================//
		// // Цвет обводки.
		sf::Color OutlineColor = sf::Color::Black;
		// Цвет надписи.
		sf::Color TextColor = sf::Color::White;
		// Размер символа.
		unsigned int CharacterSize = 12;
		// Ширина обводки.
		float OutlineThickness = 0.f;
		// Дополнительный стиль текста.
		sf::Text::Style TextStyle;
		// Межстрочный интервал в долях размера символа.
		float LineSpacing = 0.f;
		// Занимаемое надписью пространство в окне (используется для обработки взаимодействий с кнопками мыши).
		sf::Vector2u OnWindowSpace;
		// Координаты надписи (используются для обработки взаимодействий с кнопками мыши).
		sf::Vector2f LabelCoords = { 0.f, 0.f };

		//---> Графические компоненты.
		//========================================================================================================================//
		// Обработчик взаимодействий с кнопками мыши.
		MouseProcessing MouseProcessingObject;
		// Вектор отрисовываемых строчек надписи.
		std::vector<sf::Text> Label;
		// Шрифт.
		sf::Font* TextFont;

	protected:

		//---> Функции обработки.
		//========================================================================================================================//
		// Подсчитывает занимаемое надписью пространство в окне и её координаты.
		void CalculateOnWindowSpaceAndCoords();
		// Позиционирует строки по середине блока.
		void Centering();
		// Применяет стили ко всем спрайтам надписи.
		void AppendStyle();

	public:

		// Конструктор: пустой.
		CenteredLabel();

		// Инициализатор: задаёт окно отрисовки, центрируемую строку и размер блока отображения. Вызывать после установки всех свойств.
		void initialize(sf::RenderWindow* MainWindow, std::wstring Str, sf::Vector2u BlockSize);

		// Устанавливает размера символов.
		void setCharacterSize(unsigned int Size);

		// Устанавливает цвет надписи.
		void setColor(sf::Color TextColor);

		// Устанавливает указатель на шрифт.
		void setFont(sf::Font* TextFont);

		// Устанавливает межстрочный интервал в долях от заданного шрифтом.
		void setLineSpacing(float LineSpacing);

		// Устанавливает цвет и толщину обводки.
		void setOutline(sf::Color OutlineColor, float OutlineThickness);

		// Устанавливает координаты блока.
		void setPosition(float PostionX, float PostionY);

		// Устанавливает координаты блока.
		void setPosition(sf::Vector2f Postion);

		// Устанавливает долю ширины блока, в которую нужно вписать текст.
		void setUsedSpace(float UsedSpace);

		// Устанавливает строку.
		void setString(std::wstring Str);

		// Устанавливает дополнительные стили.
		void setStyle(sf::Text::Style TextStyle);

		// Отрисовывает и обновляет центрируемую надпись.
		Status update();

	};

}