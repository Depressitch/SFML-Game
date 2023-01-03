#pragma once
#include <SFML/Graphics.hpp>
#include "Level.cpp"

struct Game
{
    sf::RenderWindow window;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    sf::ContextSettings settings;
    sf::Event event;

    Level level;
    Entity& player;

    //������������� ����� ����� ��� �������� ������� ����, ��� ��� level ������� ������ ���� �������� (&), � player � ���� ��������
    Game() : level(window), player(level.player) 
    {
        Initialize();
    }

    //���������, ���������� �� ����� �����-���� ������ �������
    void isPlayerIntersected(sf::Vector2f backOffset)
    {
        sf::Rect playerBounds = player.sprite.getGlobalBounds();
        for (Entity const& outliner : level.outliner.sides)
        {
            if (playerBounds.intersects(outliner.sprite.getGlobalBounds()))
            {
                player.move(-backOffset);
                break;
            }
        }
        for (Entity const& entity : level.entities)
        {
            if (playerBounds.intersects(entity.sprite.getGlobalBounds()))
            {
                player.move(-backOffset);
                break;
            }
        }
    }
    
    //��������� �����
    void HandlePlayerInput(sf::Time deltaTime)
    {
        sf::Vector2f direction;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            direction.x = -speed;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            direction.x = speed;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            direction.y = -speed;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            direction.y = speed;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
        {
            direction.x *= 2;
            direction.y *= 2;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
        {
            direction.x /= 2;
            direction.y /= 2;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
            player.sprite.setPosition(TILE * (OFFSET + 0), TILE * (OFFSET + 8)); //������� �� ������ ������
        else
        {
            player.move(direction * deltaTime.asSeconds());
            isPlayerIntersected(direction * deltaTime.asSeconds());
        }
    }
   
    void Run() 
    {
        sf::Clock clock;
        while (window.isOpen())
        {
            HandleEvents();

            //"������������" ����, ����� ��� ������ ���������� � 60 FPS
            timeSinceLastUpdate += clock.restart(); //.restart() �������� ���������� clock � ���������� �����, ��������� �� ��������
            while (timeSinceLastUpdate > TimePerFrame)
            {
                timeSinceLastUpdate -= TimePerFrame;
                HandleEvents();
                HandlePlayerInput(TimePerFrame);
            }

            Render();
        }
    }


    /* ��������� �������
    ������ ������� �������� ���� ����� �������� �����������:
    ����� ���� ����������, �������� ��� ������, ����� �����, ������������ �����/�������, ������ ������
    */
    void HandleEvents() 
    {
        //���� ���� �������������� ������� � �������, �� �� ����� ������������
        while (window.pollEvent(event))
        {
            //�������� ����: ��� � ALT+F4, � ������� �� �������; �����, ��������, ������� forced ���������� ���� ��� �������� ���� ��� � Dark Souls
            if (event.type == sf::Event::Closed) 
            {
                window.close(); 
            }
        }
    }
    
    //����� ����� �� �����
    void Render() 
    {
        //����� ������� ���� ���������
        window.clear(sf::Color::Blue); 

        //����� ������� �������������� � ����
        level.Render();
        window.draw(player);

        //� ����� ��������� �������� �� ���������� ���������� ����
        window.display();
    }
   
    //������ ����
    void Initialize()
    {
        settings.antialiasingLevel = 8; //������� �����������
        CreateWindow();
    }


    //������������� ������ ��� ����
    void SetIcon()
    {
        sf::Image icon;
        if (icon.loadFromFile("Images/icon.png"))
        {
            window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
        }
        else
        {
            //��� ��������� ������
        }
    }
    
    //�������� ���� ����
    void CreateWindow()
    {
        window.create(sf::VideoMode(wWidth, wHeight), "Tactical Espionage Action", sf::Style::Close, settings);
        SetIcon(); 
        
        //�������� ������������ ������������� ��� ��������� ������� �����������
        window.setVerticalSyncEnabled(true); 
        //��������� ���������� ����� ��� ������� ������� � ����� ���� ����� �� �������, ��� ���� �������� ��� ����������� ���������� �����
        window.setKeyRepeatEnabled(false);
    }
};
