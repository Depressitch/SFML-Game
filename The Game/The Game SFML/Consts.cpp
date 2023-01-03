#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <list>

const unsigned short int TILE = 32;
const unsigned short int OFFSET = 1;

const unsigned short int wWidth = TILE * (48 + 2 * OFFSET);
const unsigned short int wHeight = TILE * (24 + 2 * OFFSET);

const unsigned short int outlinerWidth = TILE * 48;
const unsigned short int outlinerHeight = TILE * 24;

const sf::Time TimePerFrame = sf::seconds(1.f / 60.f); //в одной секунде 60 кадров
const float speed = (float)(TILE * 4); //игрок проходит 4 тайла за одну секунду
const float size = (float)TILE;

enum Direction
{
	WRONG = -1,
	Up = 0,
	Down = 1,
	Left = 2,
	Right = 3
};