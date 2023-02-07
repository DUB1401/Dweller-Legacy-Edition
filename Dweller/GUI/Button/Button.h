#pragma once

#include "../EvolvGen.h"
#include "../GUI.h"

namespace DUBGUI {

	// Кнопка.
	class Button : public ObjectGUI {
	private:

		//---> Данные.
		//========================================================================================================================//
		// Координаты в окне.
		sf::Vector2f Position = { 0.f, 0.f };
		// Размер кнопки.
		sf::Vector2u Size;
		// Текущее состояние кнопки.
		Status ButtonStatus = Status::Normal;
		// Была ли нажата ЛКМ в предыдущем цикле.
		bool ButtonWasPressed = false;
		// Была ли нажата ЛКМ до наведения на кнопку.
		bool ButtonWasPressedOnAway = false;
		// Масштаб спрайта.
		sf::Vector2f Scale = { 1.f, 1.f };
		// Количество спрайтов для каждой вариации кнопки.
		unsigned int SpriteLinesCount = 3;

		//---> Графические компоненты.
		//========================================================================================================================//
		// Указатель на окно отрисовки.
		sf::RenderWindow* MainWindow;
		// Текстура кнопки.
		sf::Texture ButtonTexture;
		// Спрайты кнопки.
		std::vector<sf::Sprite> ButtonSprites;

	protected:

		//---> Функции обработки.
		//========================================================================================================================//
		// Проверяет попадание курсора в область кнопки.
		bool CheckMouseHover();
		// Возвращает индекс спрайта в зависимости от настроек, статуса и значения кнопки.
		unsigned int GetSpriteIndex();

	public:

		// Конструктор: стандартный.
		Button();

		// Инициализатор: задаёт окно отрисовки. Вызывать после установки всех свойств и загрузки текстуры.
		void initialize(sf::RenderWindow* MainWindow);

		// Устанавливает позицию в окне.
		void setPosition(sf::Vector2f Position);

		// Устанавливает позицию в окне.
		void setPosition(float PositionX, float PositionY);

		// Устанавливает масштаб спрайта.
		void setScale(float Scale);

		// Загружает текстуру кнопки и разрезает её на спрайты согласно выбранному режиму.
		bool loadTexture(std::string Path, sf::Vector2u SpriteSize, SlicingType Type);

		// Загружает текстуру кнопки и разрезает её на спрайты согласно выбранному режиму и направлению.
		bool loadTexture(std::string Path, sf::Vector2u SpriteSize, SlicingType SlicingType, SlicingOrientation Orientation);

		// Отрисовывание и обновление кнопки.
		Status update();

	};

}