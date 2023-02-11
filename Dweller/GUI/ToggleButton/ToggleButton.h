#pragma once

#include "../MouseProcessing/MouseProcessing.h"
#include "../EvolvGen.h"
#include "../GUI.h"

namespace DUBGUI {

	// Переключатель.
	class ToggleButton : public TexturedObjectGUI {
	private:

		//---> Данные.
		//========================================================================================================================//
		// Текущее состояние переключателя.
		Status ToggleButtonStatus = Status::Normal;
		// Количество спрайтов для каждой вариации переключателя.
		unsigned int SpriteLinesCount = 3;
		// Логический статус переключателя.
		bool ToggleButtonValue = false;
		// Указатель на окно отрисовки.
		sf::RenderWindow* MainWindow;
		// Размер переключателя.
		sf::Vector2u Size;

		//---> Свойства графических компонентов.
		//========================================================================================================================//
		// Координаты переключателя в окне.
		sf::Vector2f Position = { 0.f, 0.f };
		// Масштаб спрайта.
		sf::Vector2f Scale = { 1.f, 1.f };
		// Текстура переключателя.
		sf::Texture ToggleButtonTexture;
		
		//---> Графические компоненты.
		//========================================================================================================================//
		// Спрайты переключателя.
		std::vector<sf::Sprite> ToggleButtonSprites;
		// Обработчик взаимодействия с кнопками мыши.
		MouseProcessing MouseProcessingObject;

	protected:

		//---> Функции обработки.
		//========================================================================================================================//
		// Возвращает индекс спрайта в зависимости от настроек, статуса и значения переключателя.
		unsigned int GetSpriteIndex();

	public:

		// Стандартный конструктор.
		ToggleButton();

		// Инициализатор: задаёт окно отрисовки. Вызывать после установки всех свойств и загрузки текстуры.
		void initialize(sf::RenderWindow* MainWindow);

		// Возвращает значение переключателя.
		bool getValue();

		// Загружает текстуру переключателя и разрезает её на спрайты согласно выбранному режиму.
		bool loadTexture(std::string Path, sf::Vector2u SpriteSize, SlicingType Type);

		// Загружает текстуру переключателя и разрезает её на спрайты согласно выбранному режиму и направлению.
		bool loadTexture(std::string Path, sf::Vector2u SpriteSize, SlicingType SlicingType, SlicingOrientation Orientation);

		// Устанавливает позицию в окне.
		void setPosition(float PositionX, float PositionY);

		// Устанавливает позицию в окне.
		void setPosition(sf::Vector2f Position);

		// Устанавливает масштаб спрайта.
		void setScale(float Scale);

		// Устанавливает значение переключателя.
		void setValue(bool Value);

		// Отрисовывание и обновление переключателя.
		Status update();

	};

}