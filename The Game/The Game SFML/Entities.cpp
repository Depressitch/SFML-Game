#pragma once
#include <SFML/Graphics.hpp>
#include "Consts.cpp"

//"базовый" класс объекта в игре, который наследуетс€ от sf::Drawable Ч класса SFML, который позвол€ет рисовать объект
struct Entity : public sf::Drawable
{
	sf::Texture texture;
	sf::Sprite sprite;
	

	Entity() = default;
	//конструктор с передачей текстуры
	Entity(sf::Texture const& texture, sf::Vector2f position = sf::Vector2f(0, 0)) : texture(texture)
	{
		sprite.setTexture(this->texture);

		//в параметрах мы передаЄм "виртуальные" x,y, а потом фактически мен€ем значени€ по пиксел€м
		position.x = (position.x + OFFSET) * TILE;
		position.y = (position.y + OFFSET) * TILE;
		sprite.setPosition(position);
	} 
	//конструктор с указанием пути дл€ файла, из которого будет вз€та текстура
	Entity(const std::string& filename, sf::Vector2f position = sf::Vector2f(0, 0))
	{
		texture.loadFromFile(filename);
		sprite.setTexture(texture);

		//в параметрах мы передаЄм "виртуальные" x,y, а потом фактически мен€ем значени€ по пиксел€м
		position.x = (position.x + OFFSET) * TILE;
		position.y = (position.y + OFFSET) * TILE;
		sprite.setPosition(position);
	} 
	//запретить копирование
	Entity(const Entity&) = delete;
	//запретить перемещение
	Entity(Entity&&) = delete;


	//делаем методы, аналогичные таковым в sf::Transformable и sf::Drawable, дл€ облегчени€ чтени€ кода
	//то есть мы будем писать entity.move(offset) вместо entity.sprite.move(offset) 
	//и window.draw(entity) вместо window.draw(entity.sprite)
	void move(const sf::Vector2f& offset) 
	{
		sprite.move(offset);
	}
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override
	{
		target.draw(sprite, states);
	}
};