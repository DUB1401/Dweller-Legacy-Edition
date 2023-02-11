#pragma once

#include "../MouseProcessing/MouseProcessing.h"
#include "../EvolvGen.h"
#include "../GUI.h"

namespace DUBGUI {

	// Флаговая кнопка.
	class CheckBox : public TexturedObjectGUI {
	private:

		//---> Данные.
		//========================================================================================================================//
		// Текущее состояние флаговой кнопки.
		Status CheckBoxStatus = Status::Normal;
		// Количество спрайтов для вариаций флаговой кнопки.
		unsigned int SpriteLinesCount = 3;
		// Указатель на окно отрисовки.
		sf::RenderWindow* MainWindow;
		// Логический статус флаговой кнопки.
		bool CheckBoxValue = false;
		// Размер флаговой кнопки.
		sf::Vector2u Size;

		//---> Свойства графических компонентов.
		//========================================================================================================================//
		// Масштаб спрайта флага.
		sf::Vector2f FlagScale = { 1.f, 1.f };
		// Координаты в окне.
		sf::Vector2f Position = { 0.f, 0.f };
		// Масштаб спрайта флаговой кнопки.
		sf::Vector2f Scale = { 1.f, 1.f };
		// Текстура флаговой кнопки.
		sf::Texture CheckBoxTexture;
		// Текстура флага.
		sf::Texture FlagTexture;

		//---> Графические компоненты.
		//========================================================================================================================//
		// Обработчик взаимодействия с кнопками мыши.
		MouseProcessing MouseProcessingObject;
		// Спрайты флаговой кнопки.
		std::vector<sf::Sprite> CheckBoxSprites;
		// Спрайт флага.
		sf::Sprite FlagSprite;

	protected:

		//---> Функции обработки.
		//========================================================================================================================//
		// Возвращает индекс спрайта в зависимости от настроек, статуса и значения флаговой кнопки.
		unsigned int GetSpriteIndex();

	public:

		// Стандартный конструктор.
		CheckBox();

		// Инициализатор: задаёт окно отрисовки. Вызывать после установки всех свойств и загрузки текстур.
		void initialize(sf::RenderWindow* MainWindow);

		// Возвращает значение флаговой кнопки.
		bool getValue();

		// Загружает текстуру флага. Текстура флага может быть больше размера флаговой кнопки.
		bool loadFlagTexture(std::string Path);

		// Загружает текстуру флаговой кнопки и разрезает её на спрайты согласно выбранному режиму.
		bool loadTexture(std::string Path, sf::Vector2u SpriteSize, SlicingType Type);

		// Загружает текстуру флаговой кнопки и разрезает её на спрайты согласно выбранному режиму и направлению.
		bool loadTexture(std::string Path, sf::Vector2u SpriteSize, SlicingType SlicingType, SlicingOrientation Orientation);

		// Устанавливает масштаб спрайта флага. Не применяется к спрайту флаговой кнопки.
		void setFlagScale(float FlagScale);

		// Устанавливает позицию в окне.
		void setPosition(float PositionX, float PositionY);

		// Устанавливает позицию в окне.
		void setPosition(sf::Vector2f Position);

		// Устанавливает масштаб спрайта флаговой кнопки. Не применяется к спрайту флага.
		void setScale(float Scale);

		// Устанавливает логическое значение флаговой кнопки.
		void setValue(bool Value);

		// Отрисовывает и обновляет флаговую кнопку.
		Status update();

	};

}