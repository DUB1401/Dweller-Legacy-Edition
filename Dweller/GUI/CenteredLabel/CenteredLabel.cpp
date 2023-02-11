#include "CenteredLabel.h"

//---> CenteredLabel
//========================================================================================================================//

namespace DUBGUI {

	// Подсчитывает занимаемое надписью пространство в окне и её координаты.
	void CenteredLabel::CalculateOnWindowSpaceAndCoords() {
		// Вектор ширин и высот строк.
		std::vector<unsigned int> StringsGlobalBoundsWidth, StringsGlobalBoundsHeight;
		// Ширина и высота надписи.
		unsigned int LabelWidth, LabelHeight;
		// Вектор координат областей строк по оси X.
		std::vector<unsigned int> StringsGlobalBoundsLeft;
		// Координаты надписи.
		unsigned int LabelX, LabelY;

		// Получение размеров и координат по оси X строк надписи.
		for (unsigned int i = 0; i < Label.size(); i++) {
			StringsGlobalBoundsWidth.push_back(Label[i].getGlobalBounds().width);
			StringsGlobalBoundsHeight.push_back(Label[i].getGlobalBounds().height);

			StringsGlobalBoundsLeft.push_back(Label[i].getGlobalBounds().left);
		}

		// Подсчёт ширины надписи: наибольшее значение элемента вектора.
		LabelWidth = *std::max_element(StringsGlobalBoundsWidth.begin(), StringsGlobalBoundsWidth.end());
		// Подсчёт высоты надписи: из координаты области последней строки по оси Y и её высоты вычесть координаты по оси Y первой строки.
		LabelHeight = Label.back().getGlobalBounds().top + Label.back().getGlobalBounds().height - Label.front().getPosition().y;

		// Получение координаты надписи по оси X: наименьшее значение элемента вектора.
		LabelX = *std::min_element(StringsGlobalBoundsLeft.begin(), StringsGlobalBoundsLeft.end());
		// Получение координаты надписи по оси Y: наименьшее значение элемента вектора.
		LabelY = Label.front().getPosition().y;

		// Сохранение результата.
		OnWindowSpace = sf::Vector2u(LabelWidth, LabelHeight);
		LabelCoords = sf::Vector2f(LabelX, LabelY);
		
	}

	// Позиционирует строки по середине блока.
	void CenteredLabel::Centering() {
		// Выравнивание по ширине блока.
		for (unsigned int i = 0; i < Label.size(); i++) {
			Label[i].setOrigin(Label[i].getLocalBounds().width / 2, 0);
			Label[i].setPosition((float)BlockSize.x / 2.0, Label[i].getPosition().y);
		}
		// Расчёт модификатора для выравнивания по высоте блока.
		float HeightModificator = 0;
		for (unsigned int i = 0; i < Label.size(); i++) HeightModificator += Label[i].getLocalBounds().height;
		HeightModificator = BlockSize.y - HeightModificator;
		HeightModificator /= 2;
		HeightModificator -= LineSpacing * CharacterSize * Label.size();
		HeightModificator += LineSpacing * CharacterSize;

		// Простановка координат по оси Y.
		for (unsigned int i = 0; i < Label.size(); i++) {
			// Модификатор межстрочного интервала.
			float LSC = CharacterSize * LineSpacing;

			if (i == 0) Label[i].setPosition(Label[i].getPosition().x + Position.x, HeightModificator - Label[i].getLocalBounds().top + Position.y);
			else Label[i].setPosition(Label[i].getPosition().x + Position.x, Label[i - 1].getPosition().y + Label[i - 1].getLocalBounds().height + LSC + Position.y);
		}

	}

	// Применяет стили ко всем спрайтам надписи.
	void CenteredLabel::AppendStyle() {
		for (unsigned int i = 0; i < Label.size(); i++) {
			Label[i].setFont(*TextFont);
			Label[i].setCharacterSize(CharacterSize);
			Label[i].setFillColor(TextColor);
			Label[i].setStyle(TextStyle);
			Label[i].setOutlineColor(OutlineColor);
			Label[i].setOutlineThickness(OutlineThickness);
		}
	}

	// Конструктор: пустой.
	CenteredLabel::CenteredLabel() {

	}

	// Инициализатор: задаёт окно отрисовки, центрируемую строку и размер блока отображения. Вызывать после установки всех свойств.
	void CenteredLabel::initialize(sf::RenderWindow* MainWindow, std::wstring Str, sf::Vector2u BlockSize) {

		//---> Передача аргументов.
		//========================================================================================================================//
		this->MainWindow = MainWindow;
		this->Str = Str;
		this->BlockSize = BlockSize;

		setString(Str);

		// Настройка обработчика взаимодействия с мышью.
		MouseProcessingObject.setPosition(LabelCoords);
		MouseProcessingObject.setSize(OnWindowSpace);
		MouseProcessingObject.initialize(MainWindow);
	}

	// Устанавливает размера символов.
	void CenteredLabel::setCharacterSize(unsigned int Size) {
		this->CharacterSize = Size;
	}

	// Устанавливает цвет надписи.
	void CenteredLabel::setColor(sf::Color TextColor) {
		this->TextColor = TextColor;
	}

	// Устанавливает указатель на шрифт.
	void CenteredLabel::setFont(sf::Font* TextFont) {
		this->TextFont = TextFont;
	}

	// Устанавливает межстрочный интервал в долях от заданного шрифтом.
	void CenteredLabel::setLineSpacing(float LineSpacing) {
		this->LineSpacing = LineSpacing;
	}

	// Устанавливает цвет и толщину обводки.
	void CenteredLabel::setOutline(sf::Color OutlineColor, float OutlineThickness) {
		this->OutlineColor = OutlineColor;
		this->OutlineThickness = OutlineThickness;
	}

	// Устанавливает координаты блока.
	void CenteredLabel::setPosition(float PostionX, float PostionY) {
		this->Position = sf::Vector2f(PostionX, PostionY);
	}

	// Устанавливает координаты блока.
	void CenteredLabel::setPosition(sf::Vector2f Postion) {
		this->Position = Position;
	}

	// Устанавливает долю ширины блока, в которую нужно вписать текст.
	void CenteredLabel::setUsedSpace(float UsedSpace) {
		this->UsedSpace = UsedSpace;
	}

	// Устанавливает строку.
	void CenteredLabel::setString(std::wstring Str) {
		// Проверка на пустоту строки.
		if (Str != L"") {
			// Очистка контейнера для перезаписи.
			Label.clear();
			// Буферный текст SFML для расчёта величины надписи.
			sf::Text TextBufer;
			TextBufer.setCharacterSize(CharacterSize);
			TextBufer.setFillColor(TextColor);
			TextBufer.setStyle(TextStyle);
			TextBufer.setFont(*TextFont);
			// Вектор слов после разбития строки по символам пробела.
			std::vector<std::wstring> StrBufer = DUBLIB::Split(Str, L' ');
			// После каждого слова добавить пробел для удобства.
			for (unsigned int i = 0; i < StrBufer.size(); i++) StrBufer[i] += L" ";
			// Буфер для прошлой строчки.
			std::wstring BuferStrOne = StrBufer[0];
			// Буфер для текущей строчки.
			std::wstring BuferStrTwo = L"";
			// Буфер текста для помещения в вектор строчек.
			sf::Text TextResultString;
			// Пока размер строчки не будет выходить за пределы блока, добавлять по слову в буфер.
			for (unsigned int i = 0; i < StrBufer.size(); i++) {
				// Ко второму буферу строки добавить слово и пробел.
				BuferStrTwo += StrBufer[i];
				// Задать текущий буфер строки для расчёта размеров надписи.
				TextBufer.setString(sf::String::fromUtf8(BuferStrTwo.begin(), BuferStrTwo.end()));
				// Если надпись шире блока, то прежний буфер добавить в вектор для отрисовки, иначе добавить обновить старый буфер.
				if (TextBufer.getLocalBounds().width > (float)BlockSize.x * UsedSpace) {
					// Убрать пробел на конце.
					BuferStrOne = DUBLIB::DeleteLastCharacters(BuferStrOne, 1);
					// Буферному спрайту строчки поставить текст без пробела на конце.
					TextResultString.setString(sf::String::fromUtf8(BuferStrOne.begin(), BuferStrOne.end()));
					Label.push_back(TextResultString);
					BuferStrOne = StrBufer[i];
					BuferStrTwo = L"";
					// Компенсация сдвига при добавлении в вектор окончательной строчки.
					i--;
				}
				else BuferStrOne = BuferStrTwo;
			}
			// Записать последнюю строчку.
			TextResultString.setString(sf::String::fromUtf8(BuferStrOne.begin(), BuferStrOne.end()));
			Label.push_back(TextResultString);

			AppendStyle();
			Centering();
			CalculateOnWindowSpaceAndCoords();
		}
	}

	// Устанавливает дополнительные стили.
	void CenteredLabel::setStyle(sf::Text::Style TextStyle) {
		this->TextStyle = TextStyle;
	}

	// Отрисовывает и обновляет центрируемую надпись.
	CenteredLabel::Status CenteredLabel::update() {

		// Отрисовка центрируемой надписи.
		for (unsigned int i = 0; i < Label.size(); i++) MainWindow->draw(Label[i]);

		// Обновление статуса центрируемой надписи.
		CenteredLabelStatus = MouseProcessingObject.updateMouseButton(sf::Mouse::Left);

		return CenteredLabelStatus;

	}

}