#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include<stdio.h>
#include<windows.h>
#include<mmsystem.h>
#include<direct.h>


using namespace sf;
using namespace std;


struct Data
{
    string Name;
    string Genre;
    string Year;
    string Rating;
    string ID;   //path for poster
};


int main()
{

    //----------------------------------------------------------Variable------------------------------------------------------------------------------------//

    const int TotalMovies = 11;
    int size = 0;
    bool SearchChecker[TotalMovies];      //to be replaced
    bool inputIndicator = 0;    //

    Data T[TotalMovies];

    //----------------------------------------------------------States--------------------------------------------------------------------------------------//

    int MenuState = 1;

    //int AddState = 1;

    int SearchState = 1;
    int ScreenState = 1;
    bool RandomChecker = true;

    //----------------------------------------------------------Delay Timers--------------------------------------------------------------------------------//

    int Delay = 3;
    int Timer = 3;

    //----------------------------------------------------------File creation and initalization-------------------------------------------------------------//

    fstream file("record.txt");
    if (!file.is_open())
        cout << "File not created";
    string line, fileContent;
    int n = 0, index = 0;
    while (getline(file, line))
    {
        if (n == 0)
        {
            T[index].Name = line;
            n++;
        }
        else if (n == 1)
        {
            T[index].Genre = line;
            n++;
        }
        else if (n == 2)
        {
            T[index].Year = line;
            n++;
        }
        else if (n == 3)
        {
            T[index].Rating = line;
            n++;
        }
        else if (n == 4)
        {
            T[index].ID = line;
            n = 0;
            index++;
        }

    }
    file.close();

    //----------------------------------------------------------Fonts and text------------------------------------------------------------------------------//

    Font font;
    font.loadFromFile("font/LibreFranklin-ExtraBoldItalic.ttf");
    Text SearchBarText;
    SearchBarText.setFont(font);
    SearchBarText.setCharacterSize(30);
    SearchBarText.setFillColor(sf::Color::White);
    SearchBarText.setPosition(450.f, 140.f);

    Text SearchTrailer, RandomTrailer, MovingBackText;

    SearchTrailer.setString("[Type full name than press 'enter key' to display Trailer]");

    SearchTrailer.setFont(font);
    SearchTrailer.setCharacterSize(30);
    SearchTrailer.setFillColor(sf::Color::White);
    SearchTrailer.setPosition(230.f, 665.f);

    RandomTrailer.setString("[Press the 'right shift key' to display Trailer]");

    RandomTrailer.setFont(font);
    RandomTrailer.setCharacterSize(30);
    RandomTrailer.setFillColor(sf::Color::White);
    RandomTrailer.setPosition(310.f, 665.f);

    MovingBackText.setString("[Press 'TAB' to go Back]");

    MovingBackText.setFont(font);
    MovingBackText.setCharacterSize(20);
    MovingBackText.setFillColor(sf::Color::White);
    MovingBackText.setPosition(1030.f, 40.f);


    Text FindName[TotalMovies], FindGenre[TotalMovies], FindYear[TotalMovies], FindRating[TotalMovies];


    for (int m = 0; m < TotalMovies; m++)
    {
        FindName[m].setFont(font);
        FindName[m].setCharacterSize(30);
        FindName[m].setFillColor(Color::White);
        FindName[m].setPosition(450, 300);

        FindGenre[m].setFont(font);
        FindGenre[m].setCharacterSize(30);
        FindGenre[m].setFillColor(Color::White);
        FindGenre[m].setPosition(450, 350);

        FindYear[m].setFont(font);
        FindYear[m].setCharacterSize(30);
        FindYear[m].setFillColor(Color::White);
        FindYear[m].setPosition(450, 400);

        FindRating[m].setFont(font);
        FindRating[m].setCharacterSize(30);
        FindRating[m].setFillColor(Color::White);
        FindRating[m].setPosition(450, 450);

        FindName[m].setString(T[m].Name);
        FindGenre[m].setString(T[m].Genre);
        FindYear[m].setString(T[m].Year);
        FindRating[m].setString(T[m].Rating);
    }

    //----------------------------------------------------------Textures------------------------------------------------------------------------------------//

    Texture M1, M2, M3, M4; //-
    Texture S1;

    //Texture A1, A2, A3, A4, A5;

    Texture Random;
    Texture PT1, PT2, PT3, PT4;
    Texture About;

    Texture MovieTextureArray[TotalMovies];
    for (int m = 0; m < TotalMovies; m++)
        MovieTextureArray[m].loadFromFile(T[m].ID);

    //----------------------------------------------------------Sprites-------------------------------------------------------------------------------------//

    Sprite Background;          //-
    Sprite P1, P2, P3, P4, P5;  //-

    Sprite MovieSpriteArray[TotalMovies];
    for (int m = 0; m < TotalMovies; m++)
    {
        MovieSpriteArray[m].setTexture(MovieTextureArray[m]);
        MovieSpriteArray[m].setPosition(80, 265);
    }

    //----------------------------------------------------------Loading Textures----------------------------------------------------------------------------//

    M1.loadFromFile("images/menu/1.png");
    M2.loadFromFile("images/menu/2.png");
    M3.loadFromFile("images/menu/3.png");
    M4.loadFromFile("images/menu/4.png");

    S1.loadFromFile("images/searchbar/1.png");

    Random.loadFromFile("images/random/1.png");

    About.loadFromFile("images/about/1.png");

    PT1.loadFromFile("images/poster/1.jpg");
    PT2.loadFromFile("images/poster/2.jpg");
    PT3.loadFromFile("images/poster/3.jpg");
    PT4.loadFromFile("images/poster/4.jpg");



    //----------------------------------------------------------setting Textures-----------------------------------------------------------------------------//

    Background.setTexture(M1);
    P1.setTexture(PT1);
    P2.setTexture(PT2);
    P3.setTexture(PT3);
    P4.setTexture(PT4);



    //----------------------------------------------------------Search Checker -----------------------------------------------------------------------------//



    for (int m = 0; m < TotalMovies; m++) //error for searching-half fixed
    {
        SearchChecker[m] = true;
    }

    RenderWindow window(VideoMode(1280, 720), "Movie Search Engine");
    window.setFramerateLimit(30);

    //

    string UserInputSearch;



    while (window.isOpen())
    {
        //-----------------------------------------------------------------------------------------------------------------------------------//

        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
            if (event.key.code == Keyboard::Escape)
                window.close();
            else if (event.type == Event::TextEntered && MenuState == 0 && ScreenState == 2)
            {
                if (event.text.unicode == 8 && size > 0)
                {
                    inputIndicator = 1;
                    UserInputSearch.pop_back();
                    size--;
                    SearchBarText.setString(UserInputSearch);
                }
                else if (event.text.unicode >= 32 && event.text.unicode <= 126)
                {
                    inputIndicator = 1;
                    char letter = static_cast<char>(event.text.unicode);
                    UserInputSearch += letter;
                    size++;
                    SearchBarText.setString(UserInputSearch);

                }
                if (Keyboard::isKeyPressed(Keyboard::Enter))
                {
                    //_chdir("C:\\ProgramData\\Microsoft\\Windows\\Start Menu\\Programs\\Accessories\\Windows Media Player Legacy.lnk");
                    
                           //----  change this path to the media player path in your device,but keep the format same ---- //

                    _chdir("C:\\Program Files (x86)\\Windows Media Player\\wmplayer.exe");

                    if (UserInputSearch == "John Wick")

                        system("trailers\\d.mp4");

                    else if (UserInputSearch == "Kung Fu Panda 3")
                        system("trailers\\e.mp4");

                    else if (UserInputSearch == "Annabelle")
                        system("trailers\\b.mp4");

                    else if (UserInputSearch == "Hotel transylvania : transformania")
                        system("trailers\\c.mp4");

                    else if (UserInputSearch == "The Batman")
                        system("trailers\\f.mp4");

                    else if (UserInputSearch == "Peaky Blinders")
                        system("trailers\\a.mp4");

                    else if (UserInputSearch == "Interstellar")
                        system("trailers\\g.mp4");

                    else if (UserInputSearch == "Logan")
                        system("trailers\\h.mp4");


                    else if (UserInputSearch == "Venom")
                        system("trailers\\i.mp4");

                    else if (UserInputSearch == "Dictator")
                        system("trailers\\j.mp4");

                    else if (UserInputSearch == "kurulus osman")
                        system("trailers\\l.mp4");


                }


            }




        }

        //------------------------------------------------------Name Searching-------------------------------------------------------------------------------//

        for (int m = 0; m < TotalMovies; m++)
        {
            for (int i = 0; i < size; i++)
            {
                if (T[m].Name[i] == UserInputSearch[i])
                {
                    SearchChecker[m] = true;
                    continue;
                }
                else
                {
                    SearchChecker[m] = false;
                    break;
                }
            }
        }

        //------------------------------------------------------Option Choosing Function---------------------------------------------------------------------//

        if (Timer < Delay)
            Timer++;
        else if (Timer >= Delay)   //Up/Down
        {
            if (Keyboard::isKeyPressed(Keyboard::Down) && ScreenState == 1)
            {
                MenuState++;
                if (MenuState == 5)
                    MenuState = 1;
            }
            else if (Keyboard::isKeyPressed(Keyboard::Up) && ScreenState == 1)
            {
                MenuState--;
                if (MenuState == 0)
                    MenuState = 4;
            }



            if (Keyboard::isKeyPressed(Keyboard::Enter) && MenuState == 1 && ScreenState == 1)
            {
                MenuState = 0;
                ScreenState = 2;
            }



            if (Keyboard::isKeyPressed(Keyboard::Enter) && MenuState == 2 && ScreenState == 1)
            {
                MenuState = 0;
                ScreenState = 3;     //random
            }
            if (Keyboard::isKeyPressed(Keyboard::Enter) && MenuState == 3 && ScreenState == 1)
            {
                MenuState = 0;
                ScreenState = 4;    //about
            }
            if (Keyboard::isKeyPressed(Keyboard::Enter) && MenuState == 4 && ScreenState == 1)
            {
                MenuState = 0;
                window.close();     //quit
            }



            if (Keyboard::isKeyPressed(Keyboard::Tab) && MenuState == 0 && ScreenState == 2)
            {
                MenuState = 1;
                ScreenState = 1;
               
                if (size <= 0)
                {
                    inputIndicator = 0;
                }
                

            }


            if (Keyboard::isKeyPressed(Keyboard::Tab) && MenuState == 0 && ScreenState == 3)
            {
                MenuState = 1;
                ScreenState = 1;
                RandomChecker = true;
            }
            if (Keyboard::isKeyPressed(Keyboard::Tab) && MenuState == 0 && ScreenState == 4)
            {
                MenuState = 1;
                ScreenState = 1;

            }


            Timer = 0;
        }

        //------------------------------------------------------Background Selector--------------------------------------------------------------------------//

        if (true)
        {
            if (MenuState == 1 && ScreenState == 1)
                Background.setTexture(M1);
            else if (MenuState == 2 && ScreenState == 1)
                Background.setTexture(M2);
            else if (MenuState == 3 && ScreenState == 1)
                Background.setTexture(M3);
            else if (MenuState == 4 && ScreenState == 1)
                Background.setTexture(M4);
            else if (MenuState == 0 && ScreenState == 2)
                Background.setTexture(S1);

            else if (MenuState == 0 && ScreenState == 3)
                Background.setTexture(Random);
            else if (MenuState == 0 && ScreenState == 4)
                Background.setTexture(About);
        }

        //------------------------------------------------------Display Functions-----------------------------------------------------------------------------//

        window.clear(Color::Black);
        window.draw(Background);

        if (ScreenState == 2)
        {
            window.draw(MovingBackText);

            if (inputIndicator == 0)
            {
                P1.setPosition(80, 265);
                P2.setPosition(370, 265);
                P3.setPosition(660, 265);
                P4.setPosition(950, 265);
                window.draw(P1);
                window.draw(P2);
                window.draw(P3);
                window.draw(P4);
            }
            else if (inputIndicator == 1)        
            {
                for (int m = 0; m < TotalMovies; m++)
                {
                    if (SearchChecker[m])
                    {
                        MovieSpriteArray[m].setPosition(80, 265);
                        window.draw(MovieSpriteArray[m]);
                        window.draw(FindName[m]);
                        window.draw(FindGenre[m]);
                        window.draw(FindYear[m]);
                        window.draw(FindRating[m]);
                    }

                }
                window.draw(SearchTrailer);
            }
            window.draw(SearchBarText);
        }



        //------------------------------------------------------Random function-----------------------------------------------------------------------------//



        if (ScreenState == 3)
        {

            window.draw(MovingBackText);

            static int Temp;
            while (RandomChecker)
            {
                Temp = rand() % TotalMovies;
                RandomChecker = false;

            }

            window.draw(MovieSpriteArray[Temp]);
            window.draw(FindName[Temp]);
            window.draw(FindGenre[Temp]);
            window.draw(FindRating[Temp]);
            window.draw(FindYear[Temp]);


            window.draw(RandomTrailer);


            if (Keyboard::isKeyPressed(Keyboard::RShift)) {
                //_chdir("C:\\ProgramData\\Microsoft\\Windows\\Start Menu\\Programs\\Accessories\\Windows Media Player Legacy.lnk");

                    //----  change this path to the media player path in your device,but keep the format same ---- //

                _chdir("C:\\Program Files(x86)\\Windows Media Player\\wmplayer.exe");
                if (FindName[Temp].getString() == "John Wick")
                    system("trailers\\d.mp4");

                else if (FindName[Temp].getString() == "Kung Fu Panda 3")
                    system("trailers\\e.mp4");

                else if (FindName[Temp].getString() == "Annabelle")
                    system("trailers\\b.mp4");

                else if (FindName[Temp].getString() == "Hotel transylvania : transformania")
                    system("trailers\\k.mp4");

                else if (FindName[Temp].getString() == "The Batman")
                    system("trailers\\f.mp4");

                else if (FindName[Temp].getString() == "Peaky Blinders")
                    system("trailers\\a.mp4");

                else if (FindName[Temp].getString() == "Logan")
                    system("trailers\\h.mp4");

                else if (FindName[Temp].getString() == "Interstellar")
                    system("trailers\\g.mp4");

                else if (FindName[Temp].getString() == "Venom")
                    system("trailers\\i.mp4");

                else if (FindName[Temp].getString() == "Dictator")
                    system("trailers\\j.mp4");

                else if (FindName[Temp].getString() == "kurulus osman")
                    system("trailers\\l.mp4");


            }



        }
        window.display();
    }

    for (int n = 0; n < TotalMovies; n++)
    {
        cout << T[n].Name << endl;
        cout << T[n].Genre << endl;
        cout << T[n].Year << endl;
        cout << T[n].Rating << endl;
        cout << T[n].ID << endl;
    }


    
    return 0;


}