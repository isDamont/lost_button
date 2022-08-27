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

System::System() : lines(0), admin(false), pass_entered(false), bomb_counter(0), bomb(new char[42]), minutes(108),
did_minus(false) {
    set_font("../ttf/ModernDOS8x8.ttf");
    set_cursor_settings(L"\u25a0", 50);
    set_input_settings();
    set_system_message_settings();
    set_time_str_settings();
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

        if(system_time.getElapsedTime().asSeconds() > 6240){ //104 minute
        input(event);     // input function (cursor + keyboard)
        }

        if(static_cast<int>(system_time.getElapsedTime().asSeconds())==6470){time_is_up();} //107 minute and 50 second

        if(static_cast<int>(system_time.getElapsedTime().asSeconds())>6480){blow_up();}  //108 minute

        system_commands();
        time_on_screen();

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
        switch (get_resolution()) {    //type of resolution
            case 19201080:{
//get cursor back if there's no symbols
                if (static_cast<float>(str.size()-str.find_last_of('\n')) == 1){
                    cursor_symbol.setPosition(60,7);
                }

                if (_event.type == sf::Event::TextEntered){
//ignore keys
                    if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Backspace) &&
                        !sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) &&
                        !sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
                        cursor_symbol.setPosition(cursor_symbol.getPosition().x+SYMBOL_SIZE1,   //SYMBOL_SIZE1 - one symbol
                                                  cursor_symbol.getPosition().y); //cursor
                        str += static_cast<char>(_event.text.unicode);
                    }
//backspace
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Backspace)) {
                        if (!str.empty() && *(str.end() - 1) != '\n') {
                            cursor_symbol.setPosition(cursor_symbol.getPosition().x-SYMBOL_SIZE1,
                                                      cursor_symbol.getPosition().y); //cursor
                            str.pop_back();
                        }
                        if (*(str.end() - 1) == '\n') {
                            str.pop_back();
                            lines -= 1;
                            if (static_cast<float>(str.size()-str.find_last_of('\n')) == 1){  //if there's no symbols in line
                                cursor_symbol.setPosition(cursor_symbol.getPosition().x,
                                                          cursor_symbol.getPosition().y - SYMBOL_SIZE1);
                            }else{
                                cursor_symbol.setPosition(cursor_symbol.getPosition().x +
                                                          ((static_cast<float>(str.size()-str.find_last_of('\n')-2))*
                                                          SYMBOL_SIZE1)+SYMBOL_SIZE1,
                                                          cursor_symbol.getPosition().y - SYMBOL_SIZE1);
                            }
                            backspace = true;
                        }
                    }
//enter
                    /*
                            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
                                unsigned long long last_space = -1;
                                if(lines != 0){
                                 last_space = str.find_last_of('\n');
                                }
                                str.push_back('\n');
                                lines += 1;
                                cursor_symbol.setPosition(cursor_symbol.getPosition().x-
                                                                    ((static_cast<float>(str.find_last_of('\n')-last_space))*
                                                                    SYMBOL_SIZE1)+SYMBOL_SIZE1,
                                                          cursor_symbol.getPosition().y+SYMBOL_SIZE1); //cursor

                            }
                    */
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
                                                  ((static_cast<float>(str.find_last_of('\n')-last_space))*
                                                  SYMBOL_SIZE1)+SYMBOL_SIZE1,
                                                  cursor_symbol.getPosition().y+SYMBOL_SIZE1); //cursor
                    }
                }
                break;
            }
            default: {
                //other resolution...
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
    system_message.setCharacterSize(30);
    system_message.setFillColor(sf::Color::Red);
}

void System::system_commands() {
 if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)){
     if (str == "a d m i n"){
         admin = true;
        system_welcome.setFillColor(sf::Color::Red);
        cursor_symbol.setFillColor(sf::Color::Red);
     } else if(str == "u s e r"){
         admin = false;
         system_welcome.setFillColor(sf::Color::Green);
         cursor_symbol.setFillColor(sf::Color::Green);
     } else if(admin && str == "exit"){
         system_stop();
     } else if(str == "4 8 15 16 23 42"){
         pass_entered = true;
         system_time.restart();
         m_str = "SUCCESS !!!";
         set_system_welcome(">:", 30);
         set_cursor_settings(L"\u25a0", 50);
         system_message.setFillColor(sf::Color::Red);
         system_message.setString(m_str);
         system_message.setPosition(system_welcome.getPosition().x, system_welcome.getPosition().y+SYMBOL_SIZE1*2);
     }
     else{
         if (!str.empty()){
         m_str = "Incorrect code !!!";
         system_message.setFillColor(sf::Color::Red);
         system_message.setString('"'+ str + '"' + ": " + m_str);
         system_message.setPosition(system_welcome.getPosition().x, system_welcome.getPosition().y+SYMBOL_SIZE1*2);
         }
     }
 }

if(pass_entered){if(system_time.getElapsedTime().asSeconds()>5)clear_after_pass();} //clear str and system message after
                                                                                    //pass entered
    main.draw(system_message);
}

void System::system_stop() {
    exit(EXIT_SUCCESS);
}

void System::clear_after_pass() {
        str.clear();
        system_message.setString("");
        pass_entered = false;
}

void System::time_is_up() {
    std::wstring X0X = L"\u25B2";
    std::wstring X1X = L"\u25B6";
    std::wstring X2X = L"\u25BE";

    system_welcome.setFillColor(sf::Color::Red);
    system_welcome.setString(X0X+X1X);


    cursor_symbol.setFillColor(sf::Color::Red);
    cursor_symbol.setString(X2X);

    input_keyboard.setFillColor(sf::Color::Red);

    system_message.setPosition(system_welcome.getPosition().x, system_welcome.getPosition().y+SYMBOL_SIZE1*2);
    system_message.setString("ATTENTION !!!, ATTENTION !!!, ATTENTION !!!, ATTENTION !!!");
}

void System::blow_up() {
system_message.setString(*(bomb+bomb_counter));
bomb_counter++;
}

System::~System() {
delete[] bomb;
}

void System::time_on_screen() {

    std::ostringstream to_str;

    if(static_cast<int>(system_time.getElapsedTime().asSeconds())==0){
        minutes = 108;
    }

     if(system_time.getElapsedTime().asSeconds()>1){
    if(static_cast<int>(system_time.getElapsedTime().asSeconds())%60==0 && !did_minus){
minutes--;
        did_minus = true;
    }
     if(static_cast<int>(system_time.getElapsedTime().asSeconds())%61==0){
             did_minus = false;
         }
     }
     to_str << minutes;
    time_str.setString(to_str.str());
    main.draw(time_str);
}

void System::set_time_str_settings() {
    time_str.setFont(font);
    time_str.setCharacterSize(30);
    time_str.setFillColor(sf::Color::Green);
    time_str.setPosition(1850,0);
}

