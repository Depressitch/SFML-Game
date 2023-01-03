#pragma once
#include <SFML/Graphics.hpp>
#include "Entities.cpp"

//структура границ уровн€, состо€ща€ по сути из 4 entity
struct Outliner : sf::Drawable
{
	Entity sides[4]; //массив сторон


	Outliner() = default;
	Outliner(const std::string& filename)
	{
		for (int i = 0; i < 4; i++)
		{
			//текстура каждой стороны имеет название формата "filename + цифры +.png", цифры соответствуют enum Direction
			sides[i].texture.loadFromFile(filename + std::to_string(i) + ".png");
			//устанавливаем текстуру повтор€ющейс€, чтобы она не занимала всего один тайл
			sides[i].texture.setRepeated(true);
			sides[i].sprite.setTexture(sides[i].texture);
		}

		sides[Up].sprite.setTextureRect(sf::IntRect(TILE * Up, 0, outlinerWidth + 2 * TILE, TILE));
		sides[Down].sprite.setTextureRect(sf::IntRect(TILE * Down, 0, outlinerWidth + 2 * TILE, TILE));
		sides[Left].sprite.setTextureRect(sf::IntRect(TILE * Left, 0, TILE, outlinerHeight + 2 * TILE));
		sides[Right].sprite.setTextureRect(sf::IntRect(TILE * Right, 0, TILE, outlinerHeight + 2 * TILE));

		sides[Up].sprite.setPosition(TILE * (OFFSET - 1), TILE * (OFFSET - 1));
		sides[Down].sprite.setPosition(TILE * (OFFSET - 1), outlinerHeight + TILE * OFFSET);
		sides[Left].sprite.setPosition(TILE * (OFFSET - 1), TILE * (OFFSET - 1));
		sides[Right].sprite.setPosition(outlinerWidth + TILE * OFFSET, TILE * (OFFSET - 1));
	}


	void draw(sf::RenderTarget& target, sf::RenderStates states) const override
	{
		for (const Entity& Side : sides)
		{
			target.draw(Side, states);
		}
	};
};