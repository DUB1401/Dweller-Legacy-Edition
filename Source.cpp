#include "Source.h"
#include "EvolvGen.h"

// --->CenteredLabel
//=======================================================================================================================//

//���������������� ������ �� �������� �����.
void CenteredLabel::Centering() {
	//������������ �� ������ �����.
	for (unsigned int i = 0; i < Label.size(); i++) {
		Label[i].setOrigin(Label[i].getLocalBounds().width / 2, Label[i].getOrigin().y);
		Label[i].setPosition((float)BlockSize.x / 2.0, Label[i].getPosition().y);
	}
	//������ ������������ ��� ������������ �� ������ �����.
	float HeightModificator = 0;
	for (unsigned int i = 0; i < Label.size(); i++) HeightModificator += Label[i].getLocalBounds().height;
	HeightModificator = BlockSize.y - HeightModificator;
	HeightModificator /= 2;
	HeightModificator -= LineSpacing * CharacterSize * Label.size();
	HeightModificator += LineSpacing * CharacterSize;
	
	//����������� ��������� �� ��� Y.
	for (unsigned int i = 0; i < Label.size(); i++) {
		float LSC = CharacterSize * LineSpacing;
		if (i == 0) Label[i].setPosition(Label[i].getPosition().x, HeightModificator - Label[i].getLocalBounds().top);
		else Label[i].setPosition(Label[i].getPosition().x, Label[i - 1].getPosition().y + Label[i - 1].getLocalBounds().height + LSC);
	}

	/*
	//����������� ��������� �� ��� Y.
	for (unsigned int i = 0; i < Label.size(); i++) {
		float LSC = CharacterSize * LineSpacing * i;
		if (i == 0) Label[i].setPosition(Label[i].getPosition().x, HeightModificator - Label[i].getLocalBounds().top);
		else Label[i].setPosition(Label[i].getPosition().x, LSC + HeightModificator - Label[i].getLocalBounds().top + CharacterSize * i);
	}
	*/

}

//���������� ����� �� ���� �������� �������.
void CenteredLabel::AppendStyle() {
	for (unsigned int i = 0; i < Label.size(); i++) {
		Label[i].setFont(*TextFont);
		Label[i].setCharacterSize(CharacterSize);
		Label[i].setFillColor(TextColor);
		Label[i].setStyle(TextStyle);
	}
}

//�����������: ������.
CenteredLabel::CenteredLabel() {

}

//����� ���� ���������, ������������ ������ � ������� ����� �����������. �������� ����� ��������� ���� ������.
void CenteredLabel::Initialize(sf::RenderWindow* MainWindow, std::wstring Str, sf::Vector2u BlockSize) {

	//---> �������� ����������.
	//=======================================================================================================================//
	this->MainWindow = MainWindow;
	this->Str = Str;
	this->BlockSize = BlockSize;

	//---> ��������� ������� � ��������� ���������� �������.
	//=======================================================================================================================//
	//�������� ����� SFML ��� ������� �������� �������.
	sf::Text TextBufer;
	TextBufer.setCharacterSize(CharacterSize);
	TextBufer.setFillColor(TextColor);
	TextBufer.setStyle(TextStyle);
	TextBufer.setFont(*TextFont);
	//������ ���� ����� �������� ������ �� �������� �������.
	std::vector<std::wstring> StrBufer = DUBLIB::Split(Str, L' ');
	//����� ������� ����� �������� ������ ��� ��������.
	for (unsigned int i = 0; i < StrBufer.size(); i++) StrBufer[i] += L" ";
	//����� ��� ������� �������.
	std::wstring BuferStrOne = StrBufer[0];
	//����� ��� ������� �������.
	std::wstring BuferStrTwo = L"";
	//����� ������ ��� ��������� � ������ �������.
	sf::Text TextResultString;
	//���� ������ ������� �� ����� �������� �� ������� �����, ��������� �� ����� � �����.
	for (unsigned int i = 0; i < StrBufer.size(); i++) {
		//�� ������� ������ ������ �������� ����� � ������.
		BuferStrTwo += StrBufer[i];
		//������ ������� ����� ������ ��� ������� �������� �������.
		TextBufer.setString(sf::String::fromUtf8(BuferStrTwo.begin(), BuferStrTwo.end()));
		//���� ������� ���� �����, �� ������� ����� �������� � ������ ��� ���������, ����� �������� �������� ������ �����.
		if (TextBufer.getLocalBounds().width > (float)BlockSize.x * UsedSpace) {
			//������ ������ �� �����.
			BuferStrOne = DUBLIB::DeleteLastCharacters(BuferStrOne, 1);
			//��������� ������� ������� ��������� ����� ��� ������� �� �����.
			TextResultString.setString(sf::String::fromUtf8(BuferStrOne.begin(), BuferStrOne.end()));
			Label.push_back(TextResultString);
			BuferStrOne = StrBufer[i];
			BuferStrTwo = L"";
			//����������� ������ ��� ���������� � ������ ������������� �������.
			i--;
		}
		else BuferStrOne = BuferStrTwo;
	}
	//�������� ��������� �������.
	TextResultString.setString(sf::String::fromUtf8(BuferStrOne.begin(), BuferStrOne.end()));
	Label.push_back(TextResultString);

	AppendStyle();
	Centering();
}

//�������� ��������� �� �����.
void CenteredLabel::SetFont(sf::Font* TextFont) {
	this->TextFont = TextFont;
}

//����� ���� ������ �����, � ������� ����� ������� ����� (������ �� ������ � ������� ����). �� ��������� 1.
void CenteredLabel::SetUsedSpace(float UsedSpace) {
	this->UsedSpace = UsedSpace;
}

//��������� ����� �������. �� ��������� �����.
void CenteredLabel::SetColor(sf::Color TextColor) {
	this->TextColor = TextColor;
}

//��������� ��������������� ����� ��� ������.
void CenteredLabel::SetStyle(sf::Text::Style TextStyle) {
	this->TextStyle = TextStyle;
}

//������������� ����������� �������� � ����� ������� �������. �� ��������� 0.05 ��� ����������� ���������� ������.
void CenteredLabel::SetLineSpacing(float LineSpacing) {
	this->LineSpacing = LineSpacing;
}

//��������� ������� ��������. �� ��������� ����� 12.
void CenteredLabel::SetCharacterSize(unsigned int Size) {
	this->CharacterSize = Size;
}

//��������� �������������� �������.
void CenteredLabel::Update() {
	for (unsigned int i = 0; i < Label.size(); i++) MainWindow->draw(Label[i]); 

}

// --->CenteredLabel
//=======================================================================================================================//

//���������� ������ � �������� � �������.
void TextBox::AppendStyle() {
	Label.setFont(*TextFont);
	Label.setCharacterSize(CharacterSize);
	Label.setFillColor(TextColor);
	Label.setStyle(TextStyle);
	Label.setLineSpacing(LineSpacing);
	Label.setOutlineColor(OutlineColor);
	Label.setOutlineThickness(Thickness);
	Label.setPosition(Position);

}

//�������� ������ �� ��������� ������� ����������� �������� ������� ������ Windows.
std::wstring TextBox::LineBreak(sf::Text TextBufer, sf::Font* TextFont, std::wstring Str, unsigned int BlockSizeX) {
	//��������� ������ ��������� �� ����� ��� �����������.
	TextBufer.setFont(*TextFont);
	//��������� ����������.
	std::wstring Result = L"";

	//�������� ������������� ��������.
	TextBufer.setString(sf::String::fromUtf8(Str.begin(), Str.end()));
	if (TextBufer.getLocalBounds().width >= BlockSizeX) {
		//������ ����������� �� ��������.
		std::vector<std::wstring> StringsBufer = DUBLIB::Split(Str, L' ');
		//������ �����: ������ �������� �� ����������� �����, ����� �������� � ������ ���������� ������ ����� ����������� �����.
		std::wstring StrBuferOne = L"";
		//������ �����: � ���� ����������� �����, � ����� �� ��� ������ �������� ��������� ������.
		std::wstring StrBuferTwo = L"";

		//���������� ������� � ����� ���� �����.
		for (unsigned int i = 0; i < StringsBufer.size(); i++) StringsBufer[i] += L" ";

		//�������� ������ �� ������� �������.
		for (unsigned int i = 0; i < StringsBufer.size(); i++) {
			//���������� ����� �� ������ �����, ����������� � �������� �� ���������� ������ �����.
			StrBuferTwo += StringsBufer[i];
			TextBufer.setString(sf::String::fromUtf8(StrBuferTwo.begin(), StrBuferTwo.end()));
			///���� ����� ������ ������ ������ �����.
			if (TextBufer.getLocalBounds().width > BlockSizeX) {
				//���������� ���������� � ���������� ������� ������� ������ Windows.
				Result += StrBuferOne;
				Result = DUBLIB::Trim(Result);
				Result += L"\n";
				//������� �������.
				StrBuferOne.clear();
				StrBuferTwo = StringsBufer[i];
			}
			else StrBuferOne = StrBuferTwo;
		}
		//���� �� ������ ������ ���-�� ��������, �� �������� � ������.
		Result += StrBuferTwo;
	}
	else Result = Str;
	return Result;
}

//�����������: ������.
TextBox::TextBox() {

}

//����� ���� ��������� � ������� ����� �����������. �������� ����� ��������� ���� ������.
void TextBox::Initialize(sf::RenderWindow* MainWindow, sf::Vector2u BlockSize) {

	//---> �������� ����������.
	//=======================================================================================================================//
	this->MainWindow = MainWindow;
	this->BlockSize = BlockSize;

	//---> ��������� ��������.
	//=======================================================================================================================//
	AppendStyle();
	std::wstring ResultString = L"";
	for (unsigned int i = 0; i < StringsArray.size(); i++) ResultString += LineBreak(Label, TextFont, StringsArray[i], BlockSize.x) + L"\n\n";
	Label.setString(sf::String::fromUtf8(ResultString.begin(), ResultString.end()));
}

//������������� ������� � ����.
void TextBox::SetPosition(sf::Vector2f Position) {
	this->Position = Position;
}

//������������� ������� � ����.
void TextBox::SetPosition(float PositionX, float PositionY) {
	this->Position = sf::Vector2f(PositionX, PositionY);
}

//�������� ��������� �� �����.
void TextBox::SetFont(sf::Font* TextFont) {
	this->TextFont = TextFont;
}

//����� ����������� ���������� � ����� �� �������������� �������. �� ��������� 1.
void TextBox::SetLineSpacing(float LineSpacing) {
	this->LineSpacing = LineSpacing;
}

//��������� ����� �������. �� ��������� �����.
void TextBox::SetColor(sf::Color TextColor) {
	this->TextColor = TextColor;
}

//��������� ��������������� ����� ��� ������.
void TextBox::SetStyle(sf::Text::Style TextStyle) {
	this->TextStyle = TextStyle;
}

//��������� ������ � ������� �������.
void TextBox::SetOutline(sf::Color OutlineColor, float Thickness) {
	this->OutlineColor = OutlineColor;
	this->Thickness = Thickness;
}

//��������� ������� ��������. �� ��������� ����� 12.
void TextBox::SetCharacterSize(unsigned int Size) {
	this->CharacterSize = Size;
}

//��������� ������.
void TextBox::SetStringsArray(std::vector<std::wstring> StringsArray) {
	this->StringsArray = StringsArray;
}

//��������� ���������� ����.
void TextBox::Update() {
	MainWindow->draw(Label);
}

//---> Intro
//=======================================================================================================================//

//��������� �������� ����������.
void Intro::InitializeAppearancesAnimation() {
	TransparencyCoefficient = 255;
	StartAppearancesAnimation = true;
}

//��������������� �������� ����������.
void Intro::PlayAppearancesAnimation() {
	TransparencyCoefficient -= 0.2 * *GlobalTimeAsMicroseconds / 800;
	if (TransparencyCoefficient < 0) {
		TransparencyCoefficient = 0;
		StartAppearancesAnimation = false;
	}
	BlackRect.setFillColor(sf::Color(0, 0, 0, TransparencyCoefficient));
	MainWindow->draw(BlackRect);
}

//��������� �������� ���������.
void Intro::InitializeAttenuationAnimation() {
	TransparencyCoefficient = 0;
	StartAttenuationAnimation = true;
}

//��������������� �������� ���������.
void Intro::PlayAttenuationAnimation() {
	TransparencyCoefficient += 0.2 * *GlobalTimeAsMicroseconds / 800;
	if (TransparencyCoefficient > 255) {
		TransparencyCoefficient = 255;
		StartAttenuationAnimation = false;
	}
	BlackRect.setFillColor(sf::Color(0, 0, 0, TransparencyCoefficient));
	MainWindow->draw(BlackRect);
}

//�����������: ��������� ������������ �������������� ������.
Intro::Intro(sf::RenderWindow* MainWindow, double* GlobalTimeAsSeconds, unsigned long long int* GlobalTimeAsMicroseconds) {

	//---> �������� ����������.
	//=======================================================================================================================//
	this->MainWindow = MainWindow;
	this->GlobalTimeAsSeconds = GlobalTimeAsSeconds;
	this->GlobalTimeAsMicroseconds = GlobalTimeAsMicroseconds;

	//---> �������� ������� �� ���������� ����� � ������.
	//=======================================================================================================================//
	Book = DUBLIB::GetMarkeredStringsArrayFromFile(L"Data\\Local\\" + DUBLIB::GetMarkeredStringFromFile(L"Settings.txt", L"game-local") + L".txt", L"intro");
	TextFont.loadFromFile("Data\\Fonts\\" + DUBLIB::GetMarkeredStringFromFile("Settings.txt", "game-font"));

	//---> �������� ����������� � ��������� �� ��������� �� ������ ������. 
	//=======================================================================================================================//
	//������.
	sf::Texture BufferTexture;
	sf::Sprite BufferSprite;
	std::string Path;
	//��������� �������� � ����������������.
	for (unsigned int i = 0; i < 9; i++) {
		Path = "Data\\Texturepacks\\" + DUBLIB::GetMarkeredStringFromFile("Settings.txt", "game-texturepack") + "\\Story\\Story" + DUBLIB::ConvertNumberToString(i + 1) + ".png";

		StoryTextures.push_back(BufferTexture);
		StoryTextures[i].loadFromFile(Path.c_str());

		StorySprites.push_back(BufferSprite);
		StorySprites[i].setTexture(StoryTextures[i]);
		StorySprites[i].setScale(DUBLIB::CalculateScaleY(MainWindow->getSize(), StoryTextures[i].getSize(), 0.70));
		StorySprites[i].setOrigin(StorySprites[i].getLocalBounds().width / 2, StorySprites[i].getLocalBounds().height / 2);
		StorySprites[i].setPosition((float)MainWindow->getSize().x / 2, (float)MainWindow->getSize().y / 2);
	}
	//������������ ������� �������������� ��� ��������.
	BlackRect.setSize(sf::Vector2f(MainWindow->getSize().x, MainWindow->getSize().y));

	//---> ��������� �������.
	//=======================================================================================================================//
	//���������� ������� ���������.
	CenteredLabel* CL_Bufer = new CenteredLabel;
	for (unsigned int i = 0; i < 9; i++) {
		StoryText.push_back(*CL_Bufer);
		StoryText[i].SetCharacterSize(32);
		StoryText[i].SetFont(&TextFont);
		StoryText[i].SetStyle(sf::Text::Style::Italic);
		StoryText[i].SetUsedSpace(0.70);
		StoryText[i].SetLineSpacing(0.35);
		StoryText[i].Initialize(MainWindow, Book[i], MainWindow->getSize());
	}
	delete CL_Bufer;
}

//��������� ������������� �����. ���������� false, ���� �� ������� ��� �������� ������.
bool Intro::Start() {
	//��������� ���������� �������.
	bool IsSuccessfully = true;
	//�������� � ��������������� �����.
	if (!IntroMusic.openFromFile("Data\\Sounds\\Intro.ogg")) IsSuccessfully = false;
	IntroMusic.play();

	IsEnabled = true;

	return IsSuccessfully;
}

//������������� ������������� �����.
void Intro::End() {
	IntroMusic.stop();
	ElapsedTime = 0;
	IllustrationIndex = 0;
	BookIndex = 0;
	IsEnabled = false;
	TransparencyCoefficient = 255;
	StartAppearancesAnimation = true;
	StartAttenuationAnimation = false;
	IsAttenuationAnimationWasPlayed = false;
}

//���������� ����� ���������� ������.
void Intro::Update() {
	//���� ������� �����.
	if (IsEnabled) {
		//���� ������ ����, �� ���������� �������� ��������� �� ��������.
		if (ElapsedTime == 0) StorySprites[IllustrationIndex].setTexture(StoryTextures[IllustrationIndex]);
		//���������� ������� �����.
		ElapsedTime += *GlobalTimeAsSeconds;
		//����� ������ ������ �������.
		unsigned int FrameIndex = IllustrationIndex + BookIndex;

		//���� ������ �� ���������� � ������ ������ ����� � ��������, �� ������� ����.
		if (FrameIndex < 17 && ElapsedTime > EveryFrameTime[TimeIndex]) {
			ElapsedTime -= EveryFrameTime[TimeIndex];
			TimeIndex++;
			IsAttenuationAnimationWasPlayed = false; StartAttenuationAnimation = false;
			InitializeAppearancesAnimation();
			//���� ������, ������������ �����������, ����� ������������ ����� �������.
			if (FrameIndex % 2 == 0) BookIndex++; else {
				//������������ ����.
				IllustrationIndex++;
				//����� ��� ���������� ������ �� ��������.
				StorySprites[IllustrationIndex].setTexture(StoryTextures[IllustrationIndex]);
			}
		}

		//���� ��������� ���� ��� ���������, �� ��������� ������������� �����, ����� ������������.
		if (FrameIndex % 2 == 0 && BookIndex < 9) StoryText[BookIndex].Update();
		if (FrameIndex % 2 != 0 && IllustrationIndex < 9) MainWindow->draw(StorySprites[IllustrationIndex]);

		//���� �� ����� ����� �������� ������ 0.5 �������, �� ������ �������� ���������.
		if (EveryFrameTime[TimeIndex] - ElapsedTime < 1.00 && !StartAttenuationAnimation && !IsAttenuationAnimationWasPlayed && FrameIndex < 17) {
			IsAttenuationAnimationWasPlayed = true;
			InitializeAttenuationAnimation();
		}

		//������������ ��������.
		if (StartAppearancesAnimation) PlayAppearancesAnimation();
		if (StartAttenuationAnimation) PlayAttenuationAnimation();
	}
}

//---> Credits
//=======================================================================================================================//

//�����������: ����� ���� ��������� ����������� ������.
Credits::Credits(sf::RenderWindow* MainWindow, double* GlobalTimeAsSeconds) {

	//---> �������� ����������.
	//=======================================================================================================================//
	this->MainWindow = MainWindow;
	this->GlobalTimeAsSeconds = GlobalTimeAsSeconds;

	//---> �������� ������ � ��������� ��������� �������.
	//=======================================================================================================================//
	TextFont.loadFromFile("Data\\Fonts\\" + DUBLIB::GetMarkeredStringFromFile("Settings.txt", "game-font"));
	TextBoxObject.SetCharacterSize(18);
	TextBoxObject.SetFont(&TextFont);
	TextBoxObject.SetPosition(28, 28 + 96);
	TextBoxObject.SetOutline(sf::Color::Black, 0.5);
	TextBoxObject.SetStringsArray(DUBLIB::GetMarkeredStringsArrayFromFile(L"Data\\Local\\" + DUBLIB::GetMarkeredStringFromFile(L"Settings.txt", L"game-local") + L".txt", L"credits"));
	TextBoxObject.Initialize(MainWindow, sf::Vector2u(MainWindow->getSize().x - 56, MainWindow->getSize().y));

	//---> �������� �������.
	//=======================================================================================================================//
	BorderAmountX = MainWindow->getSize().x / 48;
	BorderAmountY = MainWindow->getSize().y / 28;
	std::string *TexturepackName = new std::string;
	*TexturepackName = DUBLIB::GetMarkeredStringFromFile("Settings.txt", "game-texturepack");
	BorderTexture.loadFromFile("Data\\Texturepacks\\" + *TexturepackName + "\\GUI\\border.png");
	BorderSprite.setTexture(BorderTexture);
	HeaderTexture.loadFromFile("Data\\Texturepacks\\" + *TexturepackName + "\\GUI\\header.png");
	HeaderSprite.setTexture(HeaderTexture);
	EmblemTexture.loadFromFile("Data\\Texturepacks\\" + *TexturepackName + "\\GUI\\emblem.png");
	EmblemSprite.setTexture(EmblemTexture);
	EmblemSprite.setOrigin(EmblemTexture.getSize().x / 2, EmblemTexture.getSize().y / 2);
	EmblemSprite.setPosition(MainWindow->getSize().x / 2, MainWindow->getSize().y / 2 + 48);
	EmblemSprite.setScale(MainWindow->getSize().y / EmblemTexture.getSize().y / 1.25, MainWindow->getSize().y / EmblemTexture.getSize().y / 1.25);
	
	delete TexturepackName;

	//---> �������� ������������ ������� ���������.
	//=======================================================================================================================//
	CenteredLabelObject.SetCharacterSize(48);
	CenteredLabelObject.SetFont(&TextFont);
	CenteredLabelObject.SetLineSpacing(0);
	CenteredLabelObject.SetStyle(sf::Text::Style::Bold);
	CenteredLabelObject.Initialize(MainWindow, DUBLIB::GetMarkeredStringFromFile(L"Data\\Local\\" + DUBLIB::GetMarkeredStringFromFile(L"Settings.txt", L"game-local") + L".txt", L"credits-header"), sf::Vector2u(HeaderSprite.getTextureRect().width, HeaderSprite.getTextureRect().height));
}

//���������� ����� ���������� ������.
void Credits::Update() {
	//������� ������.
	MainWindow->clear(sf::Color(158, 120, 119));

	MainWindow->draw(EmblemSprite);
	TextBoxObject.Update();
	//��������� ���������.
	MainWindow->draw(HeaderSprite);
	CenteredLabelObject.Update();

	//��������� ������� �����. ����� �� 12px ��� ���������.
	BorderSprite.setTextureRect(sf::IntRect(0, 0, 48, 28));
	for (unsigned int i = 0; i < BorderAmountX; i++) {
		BorderSprite.setPosition(48 * i + 28 - 12, 96);
		MainWindow->draw(BorderSprite);
	}
	//��������� ����� �����.
	BorderSprite.setTextureRect(sf::IntRect(0, 28, 28, 48));
	for (unsigned int i = 0; i < BorderAmountY; i++) {
		BorderSprite.setPosition(0, 48 * i + 28 + 96);
		MainWindow->draw(BorderSprite);
	}
	//��������� ������ �����.
	BorderSprite.setTextureRect(sf::IntRect(28, 28, 28, 48));
	for (unsigned int i = 0; i < BorderAmountY; i++) {
		BorderSprite.setPosition(MainWindow->getSize().x - 28, 48 * i + 28 + 96);
		MainWindow->draw(BorderSprite);
	}
	//��������� ������ �����. ����� �� 12px ��� ���������.
	BorderSprite.setTextureRect(sf::IntRect(48, 0, 48, 28));
	for (unsigned int i = 0; i < BorderAmountX; i++) {
		BorderSprite.setPosition(48 * i + 28 - 12, MainWindow->getSize().y - 28);
		MainWindow->draw(BorderSprite);
	}
	//��������� �������.
	BorderSprite.setTextureRect(sf::IntRect(56, 28, 28, 28));
	BorderSprite.setPosition(0, 96);
	MainWindow->draw(BorderSprite);
	BorderSprite.setPosition(MainWindow->getSize().x - 28, 96);
	MainWindow->draw(BorderSprite);
	BorderSprite.setPosition(MainWindow->getSize().x - 28, MainWindow->getSize().y - 28);
	MainWindow->draw(BorderSprite);
	BorderSprite.setPosition(0, MainWindow->getSize().y - 28);
	MainWindow->draw(BorderSprite);
}








































//�����������: ��������� ���� � �������� � ���������.
Game::Game(sf::RenderWindow* MainWindow, double* GlobalTimeAsSeconds) {

	//---> �������� ����������.
	//=======================================================================================================================//
	this->MainWindow = MainWindow;
	this->GlobalTimeAsSeconds = GlobalTimeAsSeconds;
}

//�����������: ����� ���� ��������� ����������� ������ � ������� �������.
World::World(sf::RenderWindow* MainWindow, double* GlobalTimeAsSeconds) {

	//---> �������� ����������.
	//=======================================================================================================================//
	this->MainWindow = MainWindow;
	this->GlobalTimeAsSeconds = GlobalTimeAsSeconds;
}

//���������� ����� ���������� ������.
void World::Update() {

}