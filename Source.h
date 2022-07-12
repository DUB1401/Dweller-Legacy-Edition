#pragma once

#pragma warning(disable : 4305)

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <iostream>
#include <Windows.h>

//������������ �������.
//TO-DO: ��������� ������: ������ ������� ������ ������ �����, ����� ������� �����.
class CenteredLabel {
private:

	//---> ������.
	//=======================================================================================================================//
	//���������� � ����.
	sf::Vector2f WindowCoords = { 0.f, 0.f };
	//������ �����, ������ �������� ���������� ������������.
	sf::Vector2u BlockSize;
	//������������ ������.
	std::wstring Str;
	//������������ ������������ ������ �����.
	float UsedSpace = 1.f;
	//����������� �������� � ����� ������� �������.
	float LineSpacing = 0.05;
	
	//---> ����������� ����������.
	//=======================================================================================================================//
	//��������� �� ���� ���������.
	sf::RenderWindow* MainWindow;
	//���� �������.
	sf::Color TextColor = sf::Color::White;
	//�����.
	sf::Font* TextFont;
	//������ �������.
	unsigned int CharacterSize = 12;
	//�������������� ����� ������.
	sf::Text::Style TextStyle;
	//������ �������������� ������� �������.
	std::vector<sf::Text> Label;

protected:

	//---> ������� ���������.
	//=======================================================================================================================//
	//���������������� ������ �� �������� �����.
	void Centering();
	//���������� ����� �� ���� �������� �������.
	void AppendStyle();

public:

	//�����������: ������.
	CenteredLabel();

	//����� ���� ���������, ������������ ������ � ������� ����� �����������. �������� ����� ��������� ���� ������.
	void Initialize(sf::RenderWindow* MainWindow, std::wstring Str, sf::Vector2u BlockSize);

	//�������� ��������� �� �����.
	void SetFont(sf::Font* TextFont);

	//����� ���� ������ �����, � ������� ����� ������� ����� (������ �� ������ � ������� ����). �� ��������� 1.
	void SetUsedSpace(float UsedSpace);

	//��������� ����� �������. �� ��������� �����.
	void SetColor(sf::Color TextColor);

	//��������� ��������������� ����� ��� ������.
	void SetStyle(sf::Text::Style TextStyle);

	//������������� ����������� �������� � ����� ������� �������. �� ��������� 0.05 ��� ����������� ���������� ������.
	void SetLineSpacing(float LineSpacing);

	//��������� ������� ��������. �� ��������� ����� 12.
	void SetCharacterSize(unsigned int Size);

	//��������� �������������� �������.
	void Update();

};

//������� ��� ����������� ������ � ������������� �����.
//TO-DO: ���������������� ����������, ������� �� ��������.
class TextBox {
private:

	//---> ������.
	//=======================================================================================================================//
	//���������� � ����.
	sf::Vector2f Position = { 0, 0 };
	//������ �����, ������ �������� ��������� �����.
	sf::Vector2u BlockSize;
	//����������� ���������� � ����� �� �������������� �������.
	float LineSpacing = 1.0;

	//---> ����������� ����������.
	//=======================================================================================================================//
	//��������� �� ���� ���������.
	sf::RenderWindow* MainWindow;
	//���� �������.
	sf::Color TextColor = sf::Color::White;
	//�����.
	sf::Font* TextFont;
	//������ �������.
	unsigned int CharacterSize = 12;
	//���� �������.
	sf::Color OutlineColor = sf::Color::Black;
	//������� �������.
	float Thickness = 0;
	//�������������� ����� ������.
	sf::Text::Style TextStyle;
	//�������������� ������.
	sf::Text Label;
	//������ ������.
	std::vector<std::wstring> StringsArray;

protected:

	//---> ������� ���������.
	//=======================================================================================================================//
	//���������� ������ � �������.
	void AppendStyle();
	//�������� ������ �� ��������� ������� ����������� �������� ������� ������ Windows.
	std::wstring LineBreak(sf::Text TextBufer, sf::Font* TextFont, std::wstring Str, unsigned int BlockSizeX);

public:

	//�����������: ������.
	TextBox();

	//����� ���� ��������� � ������� ����� �����������. �������� ����� ��������� ���� ������.
	void Initialize(sf::RenderWindow* MainWindow, sf::Vector2u BlockSize);

	//������������� ������� � ����.
	void SetPosition(sf::Vector2f Position);

	//������������� ������� � ����.
	void SetPosition(float PositionX, float PositionY);

	//�������� ��������� �� �����.
	void SetFont(sf::Font* TextFont);

	//����� ����������� ���������� � ����� �� �������������� �������. �� ��������� 1.
	void SetLineSpacing(float LineSpacing);

	//��������� ����� �������. �� ��������� �����.
	void SetColor(sf::Color TextColor);

	//��������� ��������������� ����� ��� ������.
	void SetStyle(sf::Text::Style TextStyle);

	//��������� ������ � ������� �������.
	void SetOutline(sf::Color OutlineColor, float Thickness);

	//��������� ������� ��������. �� ��������� ����� 12.
	void SetCharacterSize(unsigned int Size);

	//��������� ������.
	void SetStringsArray(std::vector<std::wstring> StringsArray);

	//��������� �������������� �������.
	void Update();

};

//������������� �����.
//TO-DO: ��������� �� �������� ������� ����� �������.
class Intro {
private:

	//---> ������.
	//=======================================================================================================================//
	//��������� �� ����� ���������� ����� � ��������.
	double* GlobalTimeAsSeconds;
	//��������� �� ����� ���������� ����� � �������������.
	unsigned long long int* GlobalTimeAsMicroseconds;
	//��������������� �������.
	sf::Music IntroMusic;
	//��������� ����� ��� �������������� �����������.
	double ElapsedTime = 0;
	//������ �������������� �����������.
	unsigned int IllustrationIndex = 0;
	//������ ������������ ����� �������.
	unsigned int BookIndex = 0;
	//������ ������������ �����.
	unsigned int TimeIndex = 0;
	//������ ������������ �����.
	std::vector<double> EveryFrameTime = { 3.5, 3.0, 4.0, 3.0, 4.0, 3.0, 5.5, 3.0, 4.0, 3.0, 4.0, 3.0, 3.5, 3.0, 3.5, 3.0, 6.0, 1.5 };
	//�������� �� ���������������.
	bool IsEnabled = false;
	//����������� ������������ ��� �������� ���������.
	double TransparencyCoefficient = 255;
	//������ ������������ �������� ����������.
	bool StartAppearancesAnimation = true;
	//������ ������������ �������� ���������.
	bool StartAttenuationAnimation = false;
	//������������� �� � ���� ����� �������� ���������.
	bool IsAttenuationAnimationWasPlayed = false;

	//---> ����������� ����������.
	//=======================================================================================================================//
	//��������� �� ���� ���������.
	sf::RenderWindow* MainWindow;
	//����� �������������� ������.
	std::vector<std::wstring> Book;
	//�������� �������.
	std::vector<sf::Texture> StoryTextures;
	//������� �������.
	std::vector<sf::Sprite> StorySprites;
	//�������������� �������.
	std::vector<CenteredLabel> StoryText;
	//����� ��������.
	sf::Font TextFont;
	//׸���� ������������� ��� �������� ���������.
	sf::RectangleShape BlackRect;

protected:

	//---> �������� ��������� � ����������.
	//=======================================================================================================================//
	//��������� �������� ����������.
	void InitializeAppearancesAnimation();
	//��������������� �������� ����������.
	void PlayAppearancesAnimation();
	//��������� �������� ���������.
	void InitializeAttenuationAnimation();
	//��������������� �������� ���������.
	void PlayAttenuationAnimation();

public:

	//�����������: ����� ���� ��������� ����������� ������ � ������� �������.
	Intro(sf::RenderWindow* MainWindow, double* GlobalTimeAsSeconds, unsigned long long int* GlobalTimeAsMicroseconds);

	//��������� ������������� �����. ���������� false, ���� �� ������� ��� �������� ������.
	bool Start();

	//������������� ������������� �����.
	void End();

	//���������� ����� ���������� ������.
	void Update();
};

//�����.
//TO-DO: ������ ��������, ��������� �� ������� �� ESC.
class Credits {
private:

	//---> ������.
	//=======================================================================================================================//
	//��������� �� ����� ���������� ����� � ��������.
	double* GlobalTimeAsSeconds;
	//���������� �������������� ���������� ����� �� ��� �.
	unsigned int BorderAmountX;
	//���������� �������������� ���������� ����� �� ��� Y.
	unsigned int BorderAmountY;

	//---> ����������� ����������.
	//=======================================================================================================================//
	//��������� �� ���� ���������.
	sf::RenderWindow* MainWindow;
	//����� ������.
	std::vector<std::wstring> CreditsLines;
	//����� ��������.
	sf::Font TextFont;
	//��������� ���������.
	TextBox TextBoxObject;
	//�������� �����.
	sf::Texture BorderTexture;
	//������ �����.
	sf::Sprite BorderSprite;
	//�������� ���� ���������.
	sf::Texture HeaderTexture;
	//������ ���� ���������.
	sf::Sprite HeaderSprite;
	//������������ ������� ���������.
	CenteredLabel CenteredLabelObject;
	//�������� ������� �������.
	sf::Texture EmblemTexture;
	//������ ������� �������.
	sf::Sprite EmblemSprite;


public:

	//�����������: ����� ���� ��������� ����������� ������.
	Credits(sf::RenderWindow* MainWindow, double* GlobalTimeAsSeconds);

	//���������� ����� ���������� ������.
	void Update();
};























//������������ ����� ����������� �������.
enum CharacterClasses { Warrior = 1, Wizard = 2, Archer = 3 };

//��������� ������������� ���������.
struct PlayerStats {
	unsigned int HP;
	unsigned int MP;
	unsigned int Damage;
	unsigned int Armor;
	unsigned int Intelligence;
};

class Player {
private:

	//---> ������.
	//=======================================================================================================================//
	//����� ������.
	unsigned int PlayerClass;
	//�������������� ������.
	PlayerStats GamerStats;

public:



};

class World {
private:

	//---> ������.
	//=======================================================================================================================//
	//��������� �� ����� ���������� ����� � ��������.
	double* GlobalTimeAsSeconds;

	//---> ����������� ����������.
	//=======================================================================================================================//
	//��������� �� ���� ���������.
	sf::RenderWindow* MainWindow;

public:

	//�����������: ����� ���� ��������� ����������� ������ � ������� �������.
	World(sf::RenderWindow* MainWindow, double* GlobalTimeAsSeconds);

	//���������� ����� ���������� ������.
	void Update();
};

class Game {
private:

	//---> ������.
	//=======================================================================================================================//
	//��������� �� ����� ���������� ����� � ��������.
	double* GlobalTimeAsSeconds;

	//---> ����������� ����������.
	//=======================================================================================================================//
	//��������� �� ���� ���������.
	sf::RenderWindow* MainWindow;

	//---> �������������� � �����.
	//=======================================================================================================================//
	//��������� ����.
	void DrawMap();

public:

	//�����������: ����� ���� ��������� ����������� ������ � ������� �������.
	Game(sf::RenderWindow* MainWindow, double* GlobalTimeAsSeconds);

	//���������� ����� ���������� ������.
	void Update();
};