#pragma once

#include "../EvolvGen.h"
#include "../GUI.h"

namespace DUBGUI {

	// Флаговая кнопка.
	class CheckBox : public ObjectGUI {
	private:

		//---> Данные.
		//========================================================================================================================//
		// Координаты в окне.
		sf::Vector2f Position = { 0.f, 0.f };
		// Размер флаговой кнопки.
		sf::Vector2u Size;
		// Текущее состояние флаговой кнопки.
		Status CheckBoxStatus = Status::Normal;
		// Была ли нажата ЛКМ в предыдущем цикле.
		bool CheckBoxWasPressed = false;
		// Была ли нажата ЛКМ до наведения на флаговой кнопки.
		bool CheckBoxWasPressedOnAway = false;
		// Масштаб спрайта флаговой кнопки.
		sf::Vector2f Scale = { 1.f, 1.f };
		// Масштаб спрайта флага.
		sf::Vector2f FlagScale = { 1.f, 1.f };
		// Логический статус флаговой кнопки.
		bool CheckBoxValue = false;
		// Количество спрайтов для каждой вариации флаговой кнопки.
		unsigned int SpriteLinesCount = 3;

		//---> Графические компоненты.
		//========================================================================================================================//
		// Указатель на окно отрисовки.
		sf::RenderWindow* MainWindow;
		// Текстура флаговой кнопки.
		sf::Texture CheckBoxTexture;
		// Спрайты флаговой кнопки.
		std::vector<sf::Sprite> CheckBoxSprites;
		// Текстура флага.
		sf::Texture FlagTexture;
		// Спрайт флага.
		sf::Sprite FlagSprite;

	protected:

		//---> Функции обработки.
		//========================================================================================================================//
		// Проверяет попадание курсора в область флаговой кнопки.
		bool CheckMouseHover();
		// Возвращает индекс спрайта в зависимости от настроек, статуса и значения флаговой кнопки.
		unsigned int GetSpriteIndex();

	public:

		// Стандартный конструктор.
		CheckBox();

		// Инициализатор: задаёт окно отрисовки. Вызывать после установки всех свойств и загрузки текстур.
		void initialize(sf::RenderWindow* MainWindow);

		// Устанавливает позицию в окне.
		void setPosition(sf::Vector2f Position);

		// Устанавливает позицию в окне.
		void setPosition(float PositionX, float PositionY);

		// Устанавливает масштаб спрайта флаговой кнопки. Не применяется к спрайту флага.
		void setScale(float Scale);

		// Устанавливает масштаб спрайта флага. Не применяется к спрайту флаговой кнопки.
		void setFlagScale(float FlagScale);

		// Загружает текстуру флаговой кнопки и разрезает её на спрайты согласно выбранному режиму.
		bool loadTexture(std::string Path, sf::Vector2u SpriteSize, SlicingType Type);

		// Загружает текстуру флаговой кнопки и разрезает её на спрайты согласно выбранному режиму и направлению.
		bool loadTexture(std::string Path, sf::Vector2u SpriteSize, SlicingType SlicingType, SlicingOrientation Orientation);

		// Загружает текстуру флага. Текстура флага может быть больше размера флаговой кнопки.
		bool loadFlagTexture(std::string Path);

		// Возвращает значение флаговой кнопки.
		bool getValue();

		// Устанавливает значение флаговой кнопки.
		void setValue(bool Value);

		// Отрисовывание и обновление флаговой кнопки.
		Status update();

	};

}