#pragma once

#include "../MouseProcessing/MouseProcessing.h"
#include "../EvolvGen.h"
#include "../GUI.h"

namespace DUBGUI {

	// Кнопка.
	class Button : public TexturedObjectGUI {
	private:

		//---> Данные.
		//========================================================================================================================//
		// Текущее состояние кнопки.
		Status ButtonStatus = Status::Normal;
		// Количество спрайтов для вариаций кнопки.
		unsigned int SpriteLinesCount = 3;
		// Указатель на окно отрисовки.
		sf::RenderWindow* MainWindow;
		// Размер кнопки.
		sf::Vector2u Size;

		//---> Свойства графических компонентов.
		//========================================================================================================================//
		// Координаты кнопки в окне.
		sf::Vector2f Position = { 0.f, 0.f };
		// Масштаб спрайта.
		sf::Vector2f Scale = { 1.f, 1.f };
		// Текстура кнопки.
		sf::Texture ButtonTexture;

		//---> Графические компоненты.
		//========================================================================================================================//
		// Обработчик взаимодействия с кнопками мыши.
		MouseProcessing MouseProcessingObject;
		// Спрайты кнопки.
		std::vector<sf::Sprite> ButtonSprites;
		
	protected:

		//---> Функции обработки.
		//========================================================================================================================//
		// Возвращает индекс спрайта в зависимости от настроек, статуса и значения кнопки.
		unsigned int GetSpriteIndex();

	public:

		// Конструктор: стандартный.
		Button();

		// Инициализатор: задаёт окно отрисовки. Вызывать после установки всех свойств и загрузки текстуры.
		void initialize(sf::RenderWindow* MainWindow);

		// Загружает текстуру кнопки и разрезает её на спрайты согласно выбранному режиму.
		bool loadTexture(std::string Path, sf::Vector2u SpriteSize, SlicingType Type);

		// Загружает текстуру кнопки и разрезает её на спрайты согласно выбранному режиму и направлению.
		bool loadTexture(std::string Path, sf::Vector2u SpriteSize, SlicingType SlicingType, SlicingOrientation Orientation);

		// Устанавливает позицию в окне.
		void setPosition(float PositionX, float PositionY);

		// Устанавливает позицию в окне.
		void setPosition(sf::Vector2f Position);

		// Устанавливает масштаб спрайта.
		void setScale(float Scale);

		// Отрисовывает и обновляет кнопку.
		Status update();

	};

}