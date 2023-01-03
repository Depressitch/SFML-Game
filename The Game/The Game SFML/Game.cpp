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

    //инициализаци€ полей сразу при создании объекта игры, так как level требует внутри себ€ референс (&), а player и есть референс
    Game() : level(window), player(level.player) 
    {
        Initialize();
    }

    //провер€ем, пересекает ли игрок какие-либо другие объекты
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
    
    //обработка ввода
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
            player.sprite.setPosition(TILE * (OFFSET + 0), TILE * (OFFSET + 8)); //возврат на начало уровн€
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

            //"выравнивание" игры, чтобы она всегда отражалась в 60 FPS
            timeSinceLastUpdate += clock.restart(); //.restart() обнул€ет переменную clock и возвращает врем€, прошедшее до рестарта
            while (timeSinceLastUpdate > TimePerFrame)
            {
                timeSinceLastUpdate -= TimePerFrame;
                HandleEvents();
                HandlePlayerInput(TimePerFrame);
            }

            Render();
        }
    }


    /* обработка событий
    помимо событи€ закрыти€ окна также возможно отслеживать:
    когда окно скрываетс€, мен€етс€ его размер, введЄн текст, использована мышка/геймпад, нажата кнопка
    */
    void HandleEvents() 
    {
        //пока есть необработанные событи€ в очереди, мы их будем обрабатывать
        while (window.pollEvent(event))
        {
            //закрытие окна: это и ALT+F4, и нажатие на крестик; можно, например, сделать forced сохранение игры при закрытии окна как в Dark Souls
            if (event.type == sf::Event::Closed) 
            {
                window.close(); 
            }
        }
    }
    
    //вывод всего на экран
    void Render() 
    {
        //перед выводом окно очищаетс€
        window.clear(sf::Color::Blue); 

        //затем объекты отрисовываютс€ в окно
        level.Render();
        window.draw(player);

        //и после отрисовки объектов мы показываем обновлЄнное окно
        window.display();
    }
   
    //запуск игры
    void Initialize()
    {
        settings.antialiasingLevel = 8; //уровень сглаживани€
        CreateWindow();
    }


    //устанавливаем иконку дл€ игры
    void SetIcon()
    {
        sf::Image icon;
        if (icon.loadFromFile("Images/icon.png"))
        {
            window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
        }
        else
        {
            //дл€ обработки ошибок
        }
    }
    
    //создание окна игры
    void CreateWindow()
    {
        window.create(sf::VideoMode(wWidth, wHeight), "Tactical Espionage Action", sf::Style::Close, settings);
        SetIcon(); 
        
        //включаем вертикальную синхронизацию дл€ избежани€ разрыва изображени€
        window.setVerticalSyncEnabled(true); 
        //отключаем повторение ввода при зажатии клавиши Ч иначе ввод будет не плавный, ибо есть задержка при обнаружении повторени€ ввода
        window.setKeyRepeatEnabled(false);
    }
};
