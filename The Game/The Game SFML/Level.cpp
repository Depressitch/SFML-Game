#pragma once
#include <SFML/Graphics.hpp>
#include "Entities.cpp"
#include "Outliner.cpp"

struct Level
{
	sf::RenderWindow& window; 
	Outliner outliner = Outliner("Images/Levels/Level 1/wallTile");
	Entity background = Entity("Images/Levels/Level 1/defaultBackground.png");
	Entity player;

	std::list<Entity> entities;

	Level(sf::RenderWindow& windowRef) : window(windowRef)
	{	
		SetBackground();
		SetPlayerParams(0, 8);
		AddWalls();
	}

	//устанавливаем задний фон
	void SetBackground()
	{
		background.texture.setRepeated(true);
		background.sprite.setTextureRect({ OFFSET, OFFSET, outlinerWidth, outlinerHeight});
	}
	//размещаем игрока
	void SetPlayerParams(float x, float y)
	{
		if (player.texture.loadFromFile("Images/playerTexture1.png"))
		{
			player.sprite.setTexture(player.texture);
		}
		else
		{
			//дя обработки ошибок
		}
		player.sprite.setPosition(TILE * (OFFSET + x), TILE * (OFFSET + y));
	}
	//добавляем стены по заранее установленным параметрам
	void AddWalls() 
	{
		AddWallsYXX("Images/Levels/Level 1/wallTile", Up,
			{
				{6, 0, 9},
				{14, 8, 15},
				{7, 15, 19},
				{14, 19, 22},
				{11, 22, 40},
				{1, 39, 44}
			});
		AddWallsYXX("Images/Levels/Level 1/wallTile", Down, {
				{11, 0, 4},
				{21, 4, 9},
				{11, 8, 9},
				{19, 9, 15},
				{19, 19, 26},
				{15, 26, 44},
				{5, 33, 40},
				{9, 35, 40}
			});
		AddWallsXYY("Images/Levels/Level 1/wallTile", Left, {
				{4, 20, 12},
				{15, 13, 8},
				{15, 23, 20},
				{22, 13, 12},
				{40, 10, 10},
				{35, 8, 6},
				{33, 4, 0}
			});
		AddWallsXYY("Images/Levels/Level 1/wallTile", Right, {
				{9, 10, 7},
				{8, 13, 12},
				{9, 20, 20},
				{19, 13, 8},
				{19, 23, 20},
				{26, 18, 16},
				{44, 14, 2},
				{39, 0, 0}
			});
	}
	

	//функция отрисовки всего уровня и объектов в нём
	void Render() 
	{
		window.draw(background);
		window.draw(outliner);

		for (const Entity& entity : entities) //const Entity для read-only 
		{
			window.draw(entity);
		}
	}


	//добавление горизонтальных (YXX) и вертикальных (XYY) стен
	//стены добавляются в формате "название текстуры + направление + координаты
	//для горизонтальных стен формат координат - y (высота, на которой стена находится), x1 (начало стены слева) и x2 (конец стены справа)
	//для вертикальных стен формат координат - x (расстояние, на которой стена находится), y1 (начало стены снизу) и y2 (конец стены сверху)
	//при этом можно передать неограниченное число таких координат, они будут записываться в формате { {x, y1, y2}, {x, y1, y2} }
	void AddWallsYXX(const std::string& filename, Direction side, std::initializer_list<std::tuple<int, int, int>> TopLeftRight)
	{
		for (auto& [y, x1, x2] : TopLeftRight)
		{
			entities.emplace_back(filename + std::to_string(side) + ".png", sf::Vector2f(x1, y));

			entities.back().texture.setRepeated(true);
			entities.back().sprite.setTextureRect(sf::Rect(
				(x1 + OFFSET) * TILE,
				(y + OFFSET) * TILE,
				(x2 - x1 + 1) * TILE,
				(int)TILE));
		}
	}
	void AddWallsXYY(const std::string& filename, Direction side, std::initializer_list<std::tuple<int, int, int>> LeftBottomTop)
	{
		for (auto& [x, y1, y2] : LeftBottomTop)
		{
			entities.emplace_back(filename + std::to_string(side) + ".png", sf::Vector2f(x, y2));

			entities.back().texture.setRepeated(true);
			entities.back().sprite.setTextureRect(sf::Rect(
				(x + OFFSET) * TILE,
				(y1 + OFFSET) * TILE,
				(int)TILE,
				(y1 - y2 + 1) * TILE));
		}
	}
};