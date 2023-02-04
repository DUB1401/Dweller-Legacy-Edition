#include "WorldRenderer.h"

//---> WorldRenderer
//=======================================================================================================================//

// Конструктор: задаёт окно отрисовки мира, ссылку на настройки, время кадра.
WorldRenderer::WorldRenderer(sf::RenderWindow* MainWindow, Settings* ObjectSettings, double* GlobalTimeAsSeconds) {

	//---> Передача аргументов.
	//=======================================================================================================================//
	this->MainWindow = MainWindow;
	this->ObjectSettings = ObjectSettings;
	this->GlobalTimeAsSeconds = GlobalTimeAsSeconds;

	//---> Чтение списка текстовых ID слайдов.
	//=======================================================================================================================//
	// Поток чтения файла со списком тайлов текстурпака.
	std::ifstream TileListReader("Data\\Texturepacks\\" + ObjectSettings->Texturepack.AsString() + "\\TileList.txt");
	// Буфер чтения.
	std::string *TileListBufer = new std::string;
	// Чтение всех строк файла.
	if (TileListReader.is_open()) while (std::getline(TileListReader, *TileListBufer)) TileList.push_back(DUBLIB::Trim(*TileListBufer));
	// Закрытие потока чтения.
	TileListReader.close();
	// Удаление буфера.
	delete TileListBufer;

	//---> Загрузка текстур и формирование спрайтов.
	//=======================================================================================================================//
	// Буферная текстура.
	sf::Texture *TextureBufer = new sf::Texture;
	// Загрузка текстур.
	for (unsigned int i = 0; i < TileList.size(); i++) {
		TextureBufer->loadFromFile("Data\\Texturepacks\\" + ObjectSettings->Texturepack.AsString() + "\\Tiles\\" + TileList[i] + ".png");
		WorldTextures[TileList[i]] = *TextureBufer;
	}
	// Удаление буфера.
	delete TextureBufer;
	// Буферный спрайт.
	sf::Sprite *SpriteBufer = new sf::Sprite;
	// Формирование спрайтов.
	for (unsigned int i = 0; i < TileList.size(); i++) {
		WorldSprites[TileList[i]] = *SpriteBufer;
		WorldSprites[TileList[i]].setTexture(WorldTextures[TileList[i]]);
	}
	// Удаление буфера.
	delete SpriteBufer;
}

// Выполнение цикла обновления класса.
LayoutAnswer WorldRenderer::Update() {

	// Координаты отрисовываемого слайда.
	sf::Vector2f CurrentTitleCoords = { 0, 0 };

	// Отрисовка тайлов на координатах.
	for (unsigned int X = 0; X < World.size(); X++) for (unsigned int Y = 0; Y < World[X].size(); Y++) {
		WorldSprites[World[X][Y]].setPosition(48 * X, 48 * Y);
		WorldSprites[World[X][Y]].setScale(2.0, 2.0);
		MainWindow->draw(WorldSprites[World[X][Y]]);
	}

	return Answer;

}
