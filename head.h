//
// Created by isDamont on 06.08.2022.
//

#ifndef LOST_BUTTON_HEAD_H
#define LOST_BUTTON_HEAD_H

#include <iostream>
#include <SFML/Graphics.hpp>

class window{
private:
    int resolution;
    sf::RenderWindow set_main() const;
public:
    window();
    sf::RenderWindow main;
    int get_resolution() const;
};

class System : public window{
private:
    std::string str;
    sf::Font font;
    sf::Text cursor_symbol;
    sf::Text system_welcome;
    sf::Text input_keyboard;
    sf::Clock system_time;
    sf::Sprite background;
    int lines;
    void set_position(int _resolution);
    void input(sf::Event _event);
public:
    System();
    void set_font(const std::string& _font);
    void set_cursor_settings(const std::wstring& _cursor, unsigned int size);
    void set_input_settings();
    void set_system_welcome(const std::string& _system_welcome, unsigned int size);
    void system_start();
};



#endif //LOST_BUTTON_HEAD_H
