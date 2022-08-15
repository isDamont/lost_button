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
    std::string m_str;
    sf::Font font;
    sf::Text cursor_symbol;
    sf::Text system_welcome;
    sf::Text input_keyboard;
    sf::Text system_message; // needs to get position (getting it from input())
    sf::Clock system_time;
    sf::Sprite background;
    int lines;
    void set_position(int _resolution);
    void set_font(const std::string& _font);
    void set_cursor_settings(const std::wstring& _cursor, unsigned int size);
    void set_input_settings();
    void set_system_message_settings();
    void set_system_welcome(const std::string& _system_welcome, unsigned int size);

    void input(sf::Event _event);
    void system_commands();
public:
    System();
    void system_start();
};



#endif //LOST_BUTTON_HEAD_H
