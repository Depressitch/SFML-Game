#pragma once
#include <SFML/Graphics.hpp>
#include "Consts.cpp"

//"�������" ����� ������� � ����, ������� ����������� �� sf::Drawable � ������ SFML, ������� ��������� �������� ������
struct Entity : public sf::Drawable
{
	sf::Texture texture;
	sf::Sprite sprite;
	

	Entity() = default;
	//����������� � ��������� ��������
	Entity(sf::Texture const& texture, sf::Vector2f position = sf::Vector2f(0, 0)) : texture(texture)
	{
		sprite.setTexture(this->texture);

		//� ���������� �� ������� "�����������" x,y, � ����� ���������� ������ �������� �� ��������
		position.x = (position.x + OFFSET) * TILE;
		position.y = (position.y + OFFSET) * TILE;
		sprite.setPosition(position);
	} 
	//����������� � ��������� ���� ��� �����, �� �������� ����� ����� ��������
	Entity(const std::string& filename, sf::Vector2f position = sf::Vector2f(0, 0))
	{
		texture.loadFromFile(filename);
		sprite.setTexture(texture);

		//� ���������� �� ������� "�����������" x,y, � ����� ���������� ������ �������� �� ��������
		position.x = (position.x + OFFSET) * TILE;
		position.y = (position.y + OFFSET) * TILE;
		sprite.setPosition(position);
	} 
	//��������� �����������
	Entity(const Entity&) = delete;
	//��������� �����������
	Entity(Entity&&) = delete;


	//������ ������, ����������� ������� � sf::Transformable � sf::Drawable, ��� ���������� ������ ����
	//�� ���� �� ����� ������ entity.move(offset) ������ entity.sprite.move(offset) 
	//� window.draw(entity) ������ window.draw(entity.sprite)
	void move(const sf::Vector2f& offset) 
	{
		sprite.move(offset);
	}
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override
	{
		target.draw(sprite, states);
	}
};