#include "ToggleButton.h"

//---> ToggleButton
//========================================================================================================================//

namespace DUBGUI {

	// Возвращает индекс спрайта в зависимости от настроек, статуса и значения.
	unsigned int ToggleButton::GetSpriteIndex() {
		// Индекс спрайта.
		unsigned int SpriteIndex = 0;
		// Модификатор статуса переключателя.
		unsigned int ToggleButtonStatusModificator;

		// Если переключатель имеет статус без соответствующего спрайта, дать ей максимальный индекс, иначе преобразовать статус в индекс.
		if (ToggleButtonStatus == Status::Clicked) ToggleButtonStatusModificator = 3;
		else ToggleButtonStatusModificator = static_cast<unsigned int>(ToggleButtonStatus) + 1;
		// Если индекс спрайта больше заданного количества спрайтов на значение переключателя, то установить максимально возможный индекс.
		if (ToggleButtonStatusModificator > SpriteLinesCount) ToggleButtonStatusModificator = SpriteLinesCount;
		// Если переключатель включен, то задать индекс со сдвигом, иначе к индексу со сдвигом прибавить количество спрайтов включённой формы переключателя.
		if (ToggleButtonValue) SpriteIndex = ToggleButtonStatusModificator - 1;
		else SpriteIndex = ToggleButtonStatusModificator - 1 + SpriteLinesCount;

		return SpriteIndex;
	}

	// Стандартный конструктор.
	ToggleButton::ToggleButton() {

	}

	// Инициализатор: задаёт окно отрисовки. Вызывать после установки всех свойств и загрузки текстуры.
	void ToggleButton::initialize(sf::RenderWindow* MainWindow) {
		//---> Передача аргументов.
		//========================================================================================================================//
		this->MainWindow = MainWindow;

		// Настройка спрайтов.
		for (unsigned int i = 0; i < SpriteLinesCount * 2; i++) {
			ToggleButtonSprites[i].setPosition(Position);
			ToggleButtonSprites[i].setScale(Scale);
		}

		// Настройка обработчика взаимодействия с мышью.
		MouseProcessingObject.setPosition(Position);
		MouseProcessingObject.setScale(Scale);
		MouseProcessingObject.setSize(Size);
		MouseProcessingObject.initialize(MainWindow);
	}

	// Возвращает значение переключателя.
	bool ToggleButton::getValue() {
		return ToggleButtonValue;
	}

	// Загружает текстуру переключателя и разрезает её на спрайты согласно выбранному режиму.
	bool ToggleButton::loadTexture(std::string Path, sf::Vector2u SpriteSize, SlicingType SlicingType) {

		//---> Передача аргументов.
		//========================================================================================================================//
		this->SpriteLinesCount = static_cast<unsigned int>(SlicingType);
		this->Size = SpriteSize;

		// Проверка загрузки текстуры.
		if (ToggleButtonTexture.loadFromFile(Path)) {
			// Буфер подгрузки спрайтов.
			sf::Sprite ToggleButtonSpriteBufer;

			// Настройка спрайтов.
			for (unsigned int i = 0; i < SpriteLinesCount * 2; i++) {
				ToggleButtonSprites.push_back(ToggleButtonSpriteBufer);
				ToggleButtonSprites[i].setPosition(Position);
				ToggleButtonSprites[i].setTexture(ToggleButtonTexture);
				ToggleButtonSprites[i].setTextureRect(sf::IntRect(0, Size.y * i, Size.x, Size.y));
				ToggleButtonSprites[i].setScale(Scale);
			}
			return true;
		}
		else return false;
	}

	// Загружает текстуру переключателя и разрезает её на спрайты согласно выбранному режиму и направлению.
	bool ToggleButton::loadTexture(std::string Path, sf::Vector2u SpriteSize, SlicingType SlicingType, SlicingOrientation Orientation) {

		//---> Передача аргументов.
		//========================================================================================================================//
		this->SpriteLinesCount = static_cast<unsigned int>(SlicingType);
		this->Size = SpriteSize;

		// Проверка загрузки текстуры.
		if (ToggleButtonTexture.loadFromFile(Path)) {
			// Буфер подгрузки спрайтов.
			sf::Sprite ToggleButtonSpriteBufer;

			// Настройка спрайтов.
			for (unsigned int i = 0; i < SpriteLinesCount * 2; i++) {
				ToggleButtonSprites.push_back(ToggleButtonSpriteBufer);
				ToggleButtonSprites[i].setPosition(Position);
				ToggleButtonSprites[i].setTexture(ToggleButtonTexture);
				if (Orientation == SlicingOrientation::Vertical) ToggleButtonSprites[i].setTextureRect(sf::IntRect(0, Size.y * i, Size.x, Size.y));
				else ToggleButtonSprites[i].setTextureRect(sf::IntRect(Size.x * i, 0, Size.x, Size.y));
				ToggleButtonSprites[i].setScale(Scale);
			}
			return true;
		}
		else return false;
	}

	// Устанавливает позицию в окне.
	void ToggleButton::setPosition(float PositionX, float PositionY) {
		this->Position = sf::Vector2f(PositionX, PositionY);
	}

	// Устанавливает позицию в окне.
	void ToggleButton::setPosition(sf::Vector2f Position) {
		this->Position = Position;
	}

	// Устанавливает масштаб спрайта.
	void ToggleButton::setScale(float Scale) {
		this->Scale = sf::Vector2f(Scale, Scale);
	}

	// Устанавливает значение переключателя.
	void ToggleButton::setValue(bool Value) {
		ToggleButtonValue = Value;
	}

	// Отрисовывает и обновляет переключатель.
	ToggleButton::Status ToggleButton::update() {

		// Отрисовка кнопки-переключателя.
		MainWindow->draw(ToggleButtonSprites[GetSpriteIndex()]);

		// Обновление статуса кнопки.
		ToggleButtonStatus = MouseProcessingObject.updateMouseButton(sf::Mouse::Left);

		return ToggleButtonStatus;
	}

}