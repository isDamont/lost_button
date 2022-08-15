//
// Created by isDamont on 06.08.2022.
//

#include "head.h"

window::window() : resolution(19201080), main(set_main()) {
   main.setVerticalSyncEnabled(true);
}

int window::get_resolution() const {
return resolution;
}

System::System() : lines(0) {
    set_font("../ttf/ModernDOS8x8.ttf");
    set_cursor_settings(L"\u25a0", 50);
    set_input_settings();
    set_system_message_settings();
    set_system_welcome(">:", 30);
    set_position(get_resolution());
    background.setColor(sf::Color::Black);
    main.setMouseCursorVisible(false);

}

void System::set_font(const std::string& _font) {
    font.loadFromFile(_font);
}

void System::set_cursor_settings(const std::wstring& _cursor, unsigned int size) {
    cursor_symbol.setFont(font);
    cursor_symbol.setCharacterSize(size);
    cursor_symbol.setFillColor(sf::Color::Green);
    cursor_symbol.setString(_cursor);
    cursor_symbol.setStyle(sf::Text::Bold);
}

void System::set_system_welcome(const std::string& _system_welcome, unsigned int size) {
    system_welcome.setFont(font);
    system_welcome.setCharacterSize(size);
    system_welcome.setFillColor(sf::Color::Green);
    system_welcome.setString(_system_welcome);
    system_welcome.setStyle(sf::Text::Bold);
}

void System::set_position(int _resolution) {
    switch (_resolution) {
        case 19201080: {
            cursor_symbol.setPosition(60,7);
            system_welcome.setPosition(25,25);
            input_keyboard.setPosition(65,25);
            break;
        }
        default:{
            //other resolution...
        }
    }
}

void System::system_start() {
    while (main.isOpen()){
        sf::Event event{};
        while (main.pollEvent(event)){
            if (event.type == sf::Event::Closed)
                main.close();
        }
        main.clear();
        main.draw(background);
        main.draw(system_welcome);
        input(event);     // input function (cursor + keyboard)
        system_commands();
        main.display();
    }

}

sf::RenderWindow window::set_main() const {
    switch (resolution) {
        case 19201080:{
            return sf::RenderWindow(sf::VideoMode(1920, 1080), "Station Swan", sf::Style::Fullscreen);
            break;
        }
        default:{
            //other resolution...
        }
    }
    return sf::RenderWindow(sf::VideoMode(1920, 1080), "Station Swan", sf::Style::Fullscreen);
}

void System::input(sf::Event _event) {
    bool backspace = false;
    if (_event.type == sf::Event::TextEntered){
        switch (get_resolution()) {    //type of resolution
            case 19201080:{
//ignore keys
                    if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Backspace) &&
                        !sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) &&
                        !sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
                        cursor_symbol.setPosition(cursor_symbol.getPosition().x+15,   //15 - one symbol
                                                  cursor_symbol.getPosition().y); //cursor
                        str += static_cast<char>(_event.text.unicode);
                    }
//backspace
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Backspace)) {
                    if (!str.empty() && *(str.end() - 1) != '\n') {
                        cursor_symbol.setPosition(cursor_symbol.getPosition().x-15,
                                                  cursor_symbol.getPosition().y); //cursor
                        str.pop_back();
                    }
                    if (*(str.end() - 1) == '\n') {
                        str.pop_back();
                        lines -= 1;
                        cursor_symbol.setPosition(cursor_symbol.getPosition().x +
                                                       ((static_cast<float>(str.size()-str.find_last_of('\n')-2))*15)+15,
                                                  cursor_symbol.getPosition().y - 15);

                        backspace = true;
                    }

                }
//enter
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
                    unsigned long long last_space = -1;
                    if(lines != 0){
                     last_space = str.find_last_of('\n');
                    }
                    str.push_back('\n');
                    lines += 1;
                    cursor_symbol.setPosition(cursor_symbol.getPosition().x-
                                                        ((static_cast<float>(str.find_last_of('\n')-last_space))*15)+15,
                                              cursor_symbol.getPosition().y+15); //cursor

                }

//lines
                if(cursor_symbol.getPosition().x == 1860 &&
                                                !backspace){
                    unsigned long long last_space = -1;
                    if(lines != 0){
                        last_space = str.find_last_of('\n');
                    }
                    str.push_back('\n');
                    lines += 1;
                    cursor_symbol.setPosition(cursor_symbol.getPosition().x-
                                              ((static_cast<float>(str.find_last_of('\n')-last_space))*15)+15,
                                              cursor_symbol.getPosition().y+15); //cursor
                }

                break;
            }
            default: {
                //other resolution...
            }
        }
    }
    input_keyboard.setString(str);
    main.draw(input_keyboard);
    //cursor on screen
    if(static_cast<int>(system_time.getElapsedTime().asSeconds()) % 2 == 0){main.draw(cursor_symbol);}
}

void System::set_input_settings() {
input_keyboard.setFont(font);
input_keyboard.setFillColor(sf::Color::Green);
}

void System::set_system_message_settings() {
    system_message.setFont(font);
    system_message.setFillColor(sf::Color::Red);
}

void System::system_commands() {
 if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)){
     if (str.empty()){
        m_str = "Invalid command !!!";
        system_message.setString(m_str);
        system_message.setPosition(60, cursor_symbol.getPosition().y+100);
     }
 }
 main.draw(system_message);
}

