#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <string>
#include "fstream"
#include "player.h"
#include "enemy.h"
#include "menu.h"
#include "intersect.h"
#include "meteorites.h"

const char title[] = "Space Shooter | OOP Project 2023 | 22i-0900";

using namespace sf;
using namespace std;
//--------------------------------------------Game Class-------------------------------------------------//

class Game
{
protected:
    //--------------------------------------------Game Class Data Members-------------------------------------------------//

 //-----------------Score----------------//   
    int ScoreState;
 //-----------------Fonts----------------//  
    Font font;
    Text Name;
 //-----------------GameStatus----------------//   
    bool GameState;
    bool PauseState;
    int LevelState;
    int SelectorState;
    bool LevelActiveState;
    bool TransitionState;
    int MenuState;
 //-----------------EnemyStatus----------------//   
    int enemycounter;
    bool LaserChecker;
    int PowerupType;
    bool PowerState;
    int BossDamage;
    int GokuDirection;
    float GokuBeamX;
    float GokuBeamY;
 //-----------------Textures----------------//       
    Texture B1,B2,B3,B4,B5;
    Texture CursorTexture;
    Texture MenuTexture;
    Texture Selector;
    Texture Levels;
    Texture HighScore;
    Texture Help;
    Texture ScoreAdd;
 //-----------------player textures----------------//   
    Texture Playertexture;
    Texture PL,PR,PRU,PLU;   
 //-----------------Monster Texture----------------//  
    Texture MonsterBeam;
 //-----------------Audios----------------//   
    SoundBuffer BFB;   //Bullet Fire Audio Buffer
    Sound BFA;
    SoundBuffer EXPB;   //Explosion bufer
    Sound EXPA;         //Explosion addio
    SoundBuffer PDB;
    Sound PDA;
    Music BackgroundMusic;
 //-----------------Menu Sprite----------------//   
    Sprite BackgroundSprite;
    Sprite CursorSprite;
    Sprite MenuSprite;
    Sprite SelectorSprite;
    Sprite LevelsSprite;
    Sprite HelpSprite;
    Sprite HighScoreSprite;
    Sprite ScoreAddSprite;

 //-----------------Timers----------------//   
    //Rocks Timer
    int RockDelay;
    int RockTimer;
    int RockDurationTimer;
    int RockDurationDelay;
    //Bullet timer
    int BulletDelay;
    int BulletTimer;
    //Menu Timer
    int MenuDelay; 
    int MenuTimer;
    //Bomb Timer
    int BombDelay;
    int BombTimer;
    //Transition Timer
    int TransitionDelay;
    int TransitionTimer;
    //Boss Timer
    int BossLaserStart;
    int BossLaserStop;
    int BossLaserTimer;
    //Addon Timer
    int AddonStop;
    int AddonDelay;
    int AddonTimer;
    //Power Timer
    int PowerDelay;
    int PowerTimer;
    //Event Timer
    int EventTimer;
    int EventDelay;
    //Goku Direction Timer
    int GokuTimer;
    int GokuDelay;
 //-----------------Entities----------------//   
    Menu M;

    Player* SpaceShip;

    Enemy *E1;      //for alpha
    Enemy *E2;      //for beta
    Enemy *E3;      //for gamma
    Meteorites *R;
    Enemy *M1;      //Monsters
    Enemy *M2;      //Dragon

public:
    //--------------------------------------------Game Class Constructor-------------------------------------------------//
    Game()
    {        
        //--------------------------------------------Loading textures for whole game (almost)-------------------------------------------------//
        if(true)    //Textures loading
        {               
            B1.loadFromFile("img/background/B1.png");               //Background
            B2.loadFromFile("img/background/B2.png");  
            B3.loadFromFile("img/background/B3.png");  
            B4.loadFromFile("img/background/B4.png");  
            BackgroundSprite.setTexture(B1);
            BackgroundSprite.setPosition(0,-2100);

            CursorTexture.loadFromFile("img/UI/cursor.png");                //cursor
            CursorSprite.setTexture(CursorTexture);

            MenuTexture.loadFromFile("img/UI/menu.png");                    //menu
            MenuSprite.setTexture(MenuTexture); 
            Levels.loadFromFile("img/UI/levels.png");
            LevelsSprite.setTexture(Levels);
            HighScore.loadFromFile("img/UI/highscore.png");
            HighScoreSprite.setTexture(HighScore);
            Help.loadFromFile("img/UI/help.png");
            HelpSprite.setTexture(Help);
            ScoreAdd.loadFromFile("img/UI/addscore.png");
            ScoreAddSprite.setTexture(ScoreAdd);

            Selector.loadFromFile("img/UI/playerLife2_blue.png");           //menu spaceship
            SelectorSprite.setTexture(Selector);
            SelectorSprite.setScale(1.5,1.5);
            SelectorSprite.setPosition(420,345); 

            Playertexture.loadFromFile("img/player/player.png");            //Player
            PL.loadFromFile("img/player/player.png");
            PR.loadFromFile("img/player/player.png");
            PLU.loadFromFile("img/player/playerleft.png");
            PRU.loadFromFile("img/player/playerright.png");

        }
        //--------------------------------------------Loading Audios for whole Game-------------------------------------------------//      
        if(true)    //Audios Loading
        {
            BFB.loadFromFile("audio/shoot.wav");            //bullet fire buffer
            BFA.setBuffer(BFB);
            BFA.setVolume(10);
            EXPB.loadFromFile("audio/explosion.wav");
            EXPA.setBuffer(EXPB);
            EXPA.setVolume(40);
            PDB.loadFromFile("audio/mixkit-dramatic-metal-explosion-impact-1687.wav");
            PDA.setBuffer(PDB);
            PDA.setVolume(50);
            BackgroundMusic.openFromFile("audio/background.wav");
        }       
        //--------------------------------------------Loading Fonts for whole Game-------------------------------------------------//
        if(true)
        {
            font.loadFromFile("fonts/Avalors.ttf");
            Name.setFont(font);
            Name.setPosition(450,290);
            Name.setString("");
            Name.setCharacterSize(35);
            Name.setFillColor(Color::Black);
        }
        //--------------------------------------------Craeting new Player-------------------------------------------------//       
        SpaceShip=new Player(&Playertexture);

    }
    //--------------------------------------------Game Class Destructor-------------------------------------------------//
    ~Game()
    {    
        delete SpaceShip;
        SpaceShip=NULL;
        delete E1,E2,E3,R,M1,M2;

    }
    //----------------------------------------------------------------------------------------------------------------------//    
    //--------------------------------------------Game Class Start Function-------------------------------------------------//
    //----------------------------------------------------------------------------------------------------------------------//
    void StartGame()
    {
        PauseState=1;
        ScoreState=0;
        GameState=false;
        SelectorState=1;
        MenuState=1;   
        LevelState=1;
        LevelActiveState=0;
        TransitionState=0;

        BossDamage=0;
        LaserChecker=false;    
        PowerState=0;
        PowerupType=2;
        GokuDirection=30;
        GokuBeamX=0.33;
        GokuBeamY=0.67;

        //update start 
        srand(time(0));
        RenderWindow window(VideoMode(1200, 900),title);
        window.setFramerateLimit(144);
        Clock clock;
        float timer=0;
        Time deltatime;
        fstream RecordFile("Records.txt",ios::app);
        RecordFile.is_open();
        //--------------------------------------------Timers for game-------------------------------------------------//
        if(true)
        {
            //Rocks Timer
            RockDelay=50;
            RockTimer=0;
            RockDurationTimer=0;
            RockDurationDelay=4000;
            //Bullets Timer
            BulletDelay=30;         //orignal 30
            BulletTimer=0;
            //Menu Timer
            MenuDelay=20; 
            MenuTimer=0;
            //Bomb Timer
            BombDelay=100;
            BombTimer=0;
            //Transition Timer
            TransitionDelay=200;
            TransitionTimer=0;    
            //Boss Timer
            BossLaserStart=500;
            BossLaserStop=1500;
            BossLaserTimer=0;    
            //Addons Timer
            AddonDelay=500; //to be 100
            AddonTimer=0;
            //PowerUps Timer
            PowerDelay=1000;    //to be 1000
            PowerTimer=1;         
            //Event Timer
            EventDelay=10;
            EventTimer=0; 
            //Goku timer 
            GokuTimer=0;
            GokuDelay=10;    
        }
    
        //--------------------------------------------Background Audio initialization and begain-------------------------//
        BackgroundMusic.setLoop(true);
        BackgroundMusic.setVolume(50);
        BackgroundMusic.play();
           
        //--------------------------------------------Starting game window and updating it-------------------------------------------------//
        
        while (window.isOpen())
        {
            float time = clock.getElapsedTime().asSeconds(); 
            clock.restart();
            timer += time;
            //for custom cursor
            window.setMouseCursorVisible(false);    
            CursorSprite.setPosition(Mouse::getPosition(window).x,Mouse::getPosition(window).y);

            bool LeftChecker=0,RightChecker=0,TopChecker=0;

            //--------------------------------------------Level Initalization Part-------------------------------------------------//   
            if(true)
            {
                if(LevelState==1 && !LevelActiveState)                                     //Level 1
                {
                    BackgroundSprite.setTexture(B1);
                    E1=new Alpha(24);
                    E1->Shape1Alpha();
                    LevelActiveState=true;
                    SpaceShip->sprite.setPosition(600-SpaceShip->sprite.getGlobalBounds().width/2.f,700);
                    BombDelay=100;
                    BackgroundSprite.setPosition(0,-2100);
                } 
                else if(LevelState==2 && !LevelActiveState)                                     //Level 2
                {
                    E2=new Beta(15);
                    E2->Shape1Beta();
                    LevelActiveState=true;
                    SpaceShip->sprite.setPosition(600-SpaceShip->sprite.getGlobalBounds().width/2.f,700);
                    BombDelay=90;
                    BackgroundSprite.setPosition(0,-2100);
                } 
                else if(LevelState==3 && !LevelActiveState)                                     //Level 3
                {
                    BombDelay=80;
                    BackgroundSprite.setPosition(0,-2100);
                    E3=new Gamma(12);
                    E3->Shape1Gamma();
                    LevelActiveState=true;
                    SpaceShip->sprite.setPosition(600-SpaceShip->sprite.getGlobalBounds().width/2.f,700);
                }            
                else if(LevelState==4 && !LevelActiveState)                                     //Level 4
                {
                    BackgroundSprite.setTexture(B1);
                    BombDelay=90;
                    BackgroundSprite.setPosition(0,-2100);
                    E1=new Alpha(28);
                    E1->Shape2Alpha();
                    LevelActiveState=true;
                    SpaceShip->sprite.setPosition(600-SpaceShip->sprite.getGlobalBounds().width/2.f,700);
                } 
                else if(LevelState==5 && !LevelActiveState)                                     //Level 5
                {
                    BombDelay=80;
                    BackgroundSprite.setPosition(0,-2100);
                    E2=new Beta(30);
                    E2->Shape2Beta();
                    LevelActiveState=true;
                    SpaceShip->sprite.setPosition(600-SpaceShip->sprite.getGlobalBounds().width/2.f,700);
                } 
                else if(LevelState==6 && !LevelActiveState)                                     //Level 6
                {
                    BombDelay=70;
                    BackgroundSprite.setPosition(0,-2100);
                    E3=new Gamma(16);
                    E3->Shape2Gamma();
                    LevelActiveState=true;
                    SpaceShip->sprite.setPosition(600-SpaceShip->sprite.getGlobalBounds().width/2.f,700);
                }          
                else if(LevelState==7 && !LevelActiveState)                                     //Level 7
                {
                    BackgroundSprite.setTexture(B1);
                    BombDelay=80;
                    BackgroundSprite.setPosition(0,-2100);
                    E1=new Alpha(40);
                    E1->Shape3Alpha();
                    LevelActiveState=true;
                    SpaceShip->sprite.setPosition(600-SpaceShip->sprite.getGlobalBounds().width/2.f,700);
                } 
                else if(LevelState==8 && !LevelActiveState)                                     //Level 8
                {
                    BombDelay=70;
                    BackgroundSprite.setPosition(0,-2100);
                    E2=new Beta(35);
                    E2->Shape3Beta();
                    LevelActiveState=true;
                    SpaceShip->sprite.setPosition(600-SpaceShip->sprite.getGlobalBounds().width/2.f,700);
                } 
                else if(LevelState==9 && !LevelActiveState)                                     //Level 9
                {
                    BombDelay=60;
                    BackgroundSprite.setPosition(0,-2100);
                    E3=new Gamma(49);
                    E3->Shape3Gamma();
                    LevelActiveState=true;
                    SpaceShip->sprite.setPosition(600-SpaceShip->sprite.getGlobalBounds().width/2.f,700);
                } 
                else if(LevelState==10 && !LevelActiveState)
                {
                    BackgroundSprite.setTexture(B4);
                    R=new Meteorites;
                    LevelActiveState=true;
                    SpaceShip->sprite.setPosition(600-SpaceShip->sprite.getGlobalBounds().width/2.f,700);
                } 
                else if(LevelState==11 && !LevelActiveState)
                {
                    BackgroundSprite.setTexture(B2);
                    BackgroundSprite.setPosition(0,-2100);
                    M1=new Monster;
                    M1->Shape1Monster();
                    LevelActiveState=true;
                }
                else if(LevelState==12 && !LevelActiveState)
                {
                    BackgroundSprite.setTexture(B3);
                    BombDelay=100;
                    BackgroundSprite.setPosition(0,-2100);
                    M2=new Dragon;
                    M2->Shape1Monster();
                    LevelActiveState=true;
                }

            }
        //--------------------------------------------For Closing Game---------------------------------------------------------//            
            Event e;
            if(EventTimer<EventDelay)
                EventTimer++;
            while (window.pollEvent(e))
            {  
                if (e.type == Event::Closed) 
                    window.close();   
                if(e.key.code==Keyboard::Escape)
                    window.close();  
                if(e.key.code==Keyboard::Space && (EventTimer>=EventDelay))
                {
                    EventTimer=0;
                    PauseState=!PauseState;
                }
                if(MenuState==6)
                {
                    if (e.type == sf::Event::TextEntered)
                    {
                        if (e.text.unicode>='a' && e.text.unicode<='z')
                        {
                            string currentText=Name.getString();
                            Name.setString(currentText+static_cast<char>(e.text.unicode));
                        }
                    }
                    if(e.key.code==Keyboard::Enter && EventTimer>=EventDelay)
                    {   
                        EventTimer=0;
                        string contents = Name.getString();
                        RecordFile<<ScoreState<<" "<<contents<<'\n';

                        Name.setString("");
                        ScoreState=0;
                        MenuState=1;
                        LevelState=1;
                        GameState=0;  
                        LevelActiveState=false;
                        TransitionState=0; 

                    }
                } 
                 	    
            }        
//------------------------------------------------------------------------------------------------------------------------------------//   
//----------------------------------------------Actual game Working Part--------------------------------------------------------------//    
//------------------------------------------------------------------------------------------------------------------------------------//    

            if(!GameState && PauseState )  //--------------------------------------------Menu Displayer-------------------------------------------------//   
            {
                if(MenuTimer<MenuDelay)
                        MenuTimer++;
                if (Keyboard::isKeyPressed(Keyboard::Down) && MenuTimer>=MenuDelay && MenuState==1)
                {
                    if(SelectorState==1)
                    {
                        SelectorSprite.setPosition(335,490);
                        SelectorState=2;
                    }
                    else if(SelectorState==2)
                    {
                        SelectorSprite.setPosition(400,560);
                        SelectorState=3;
                    }
                    else if(SelectorState==3)
                    {
                        SelectorSprite.setPosition(310,630);
                        SelectorState=4;
                    }
                    else if(SelectorState==4)
                    {
                        SelectorSprite.setPosition(440,705);
                        SelectorState=5;
                    }
                    else if(SelectorState==5)
                    {
                        SelectorSprite.setPosition(440,773);
                        SelectorState=6;
                    }
                    else if(SelectorState==6)
                    {
                        SelectorSprite.setPosition(420,345);
                        SelectorState=1;
                    }
                    MenuTimer=0;
                }
                if (Keyboard::isKeyPressed(Keyboard::Up) && MenuTimer>=MenuDelay && MenuState==1 )
                {
                    if(SelectorState==1)
                    {
                        SelectorSprite.setPosition(440,773);
                        SelectorState=6;
                    }
                    else if(SelectorState==2)
                    {
                        SelectorSprite.setPosition(420,345);
                        SelectorState=1;
                    }
                    else if(SelectorState==3)
                    {
                        SelectorSprite.setPosition(335,490);
                        SelectorState=2;
                    }
                    else if(SelectorState==4)
                    {
                        SelectorSprite.setPosition(400,560);
                        SelectorState=3;
                    }
                    else if(SelectorState==5)
                    {
                        SelectorSprite.setPosition(310,630);
                        SelectorState=4;
                    }
                    else if(SelectorState==6)
                    {
                        SelectorSprite.setPosition(440,705);
                        SelectorState=5;
                    }
                    MenuTimer=0;
                }
            
                if (Keyboard::isKeyPressed(Keyboard::Enter) && (SelectorState==1 || SelectorState==2) && MenuState!=6)
                {
                    GameState=true;
                    SpaceShip->HP=3;
                    LevelActiveState=false;
                    TransitionState=1;
                }    
                if (Keyboard::isKeyPressed(Keyboard::Enter) && (SelectorState==3))
                {   
                    MenuState=3;
                }
                if (Keyboard::isKeyPressed(Keyboard::Enter) && (SelectorState==4))
                {
                    MenuState=4;
                }
                if (Keyboard::isKeyPressed(Keyboard::Enter) && (SelectorState==5))
                {
                    MenuState=5;                    
                }
                if (Keyboard::isKeyPressed(Keyboard::Enter) && (SelectorState==6))
                    window.close();
            }    
            else if(TransitionState && GameState && PauseState)    //--------------------------------------------Game Transition Slide-------------------------------------------------//
            {
                if(TransitionTimer<TransitionDelay)
                    TransitionTimer++;
                M.DisplayLevelTransition(LevelState);        
                if(TransitionTimer>=TransitionDelay)
                {
                    TransitionState=0;
                    TransitionTimer=0;
                }
            }
            else if(!TransitionState && GameState && PauseState) //--------------------------------------------Active Game Window-------------------------------------------------// 
            {
 //------------------------------------------------Levels Workings-------------------------------------------//
                if(true)
                {
                    if(LevelState==1 && LevelActiveState==true)
                    {              
                        E1->SetSpeed(0.5);        
                        E1->MoveA();
                        FloatRect A=SpaceShip->sprite.getGlobalBounds();
                        for(int m=0;m<E1->getEnemySize();m++)   //Play and enemy colision
                        {
                            FloatRect B=E1->getSprite(m).getGlobalBounds();
                            if(IntersectPlayerEnemy(A,B))
                            {
                                EXPA.play();
                                SpaceShip->sprite.setPosition(600-SpaceShip->sprite.getGlobalBounds().width/2.f,700);
                                SpaceShip->HP--;
                                E1->EnemyRemoval(m);
                            }
                        }
                        for(int n=0;n<SpaceShip->NumBullets;n++)        //Bullet and Enemy collision
                        {
                            for(int m=0;m<E1->getEnemySize();m++)
                            {
                                FloatRect B=E1->getSprite(m).getGlobalBounds();
                                FloatRect C=SpaceShip->B[n].sprite.getGlobalBounds();
                                if(IntersectBulletEnemy(B,C))
                                {
                                    SpaceShip->B[n].sprite.setPosition(0,-100);
                                    EXPA.play();
                                    E1->EnemyRemoval(m);
                                    ScoreState+=10;
                                    if(E1->getEnemySize()==0)
                                    {
                                        LevelState=2;
                                        LevelActiveState=false;
                                        TransitionState=1;
                                    }
                                }
                            }
                        }
                        if(BombTimer<BombDelay)
                            BombTimer++;
                        if(BombTimer>=BombDelay)
                        {
                            BombTimer=0;
                            E1->Fire();                            
                        }
                        for(int n=0;n<E1->getBombNum();n++)     //bomb and player collision
                        {
                            FloatRect D=E1->getBombSprite(n).getGlobalBounds();
                            if(IntersectPlayerEnemyBomb(A,D))
                            {
                                EXPA.play();
                                SpaceShip->sprite.setPosition(600-SpaceShip->sprite.getGlobalBounds().width/2.f,700);
                                SpaceShip->HP--;
                                E1->getBombSprite(n).setPosition(100,1000);

                            }
                        }
                        E1->BombUpdate();
                    }                 
                    else if(LevelState==2 && LevelActiveState==true)
                    {         
                        E2->SetSpeed(0.5);                 
                        E2->MoveA();
                        FloatRect A=SpaceShip->sprite.getGlobalBounds();
                        //bullet and enemy
                        for(int m=0;m<E2->getEnemySize();m++)   //player and enemy Collision
                        {
                            FloatRect B=E2->getSprite(m).getGlobalBounds();
                                if(IntersectPlayerEnemy(A,B))
                                {
                                    EXPA.play();
                                    SpaceShip->sprite.setPosition(600-SpaceShip->sprite.getGlobalBounds().width/2.f,700);
                                    SpaceShip->HP--;
                                    E2->EnemyRemoval(m);
                                }
                        }
                        for(int n=0;n<SpaceShip->NumBullets;n++)        //Bullet and enemy collision
                        {
                            for(int m=0;m<E2->getEnemySize();m++)
                            {
                                FloatRect B=E2->getSprite(m).getGlobalBounds();
                                FloatRect C=SpaceShip->B[n].sprite.getGlobalBounds();
                                if(IntersectBulletEnemy(B,C))
                                {
                                    SpaceShip->B[n].sprite.setPosition(0,-100);
                                    EXPA.play();
                                    E2->EnemyRemoval(m);
                                    ScoreState+=20;
                                    if(E2->getEnemySize()==0)
                                    {
                                        EXPA.play();
                                        LevelState=3;
                                        LevelActiveState=false;
                                        TransitionState=1;
                                    }
                                }
                            }
                        }
                        if(BombTimer<BombDelay)
                            BombTimer++;
                        if(BombTimer>=BombDelay)
                        {
                            BombTimer=0;
                            E2->Fire();                            
                        }
                        for(int n=0;n<E2->getBombNum();n++)     //bomb and player collision
                        {
                            FloatRect D=E2->getBombSprite(n).getGlobalBounds();
                            if(IntersectPlayerEnemyBomb(A,D))
                            {
                                EXPA.play();
                                SpaceShip->sprite.setPosition(600-SpaceShip->sprite.getGlobalBounds().width/2.f,700);
                                SpaceShip->HP--;
                                E2->getBombSprite(n).setPosition(100,1000);
                            }
                        }                    
                        E2->BombUpdate();
                    }                   
                    else if(LevelState==3 && LevelActiveState==true)
                    {                        
                        E3->MoveA();
                        E3->SetSpeed(0.5);
                        FloatRect A=SpaceShip->sprite.getGlobalBounds();
                        //bullet and enemy
                        for(int m=0;m<E3->getEnemySize();m++)   //Player and Enemy collision
                        {
                            FloatRect B=E3->getSprite(m).getGlobalBounds();
                            if(IntersectPlayerEnemy(A,B))
                            {
                                EXPA.play();
                                SpaceShip->sprite.setPosition(600-SpaceShip->sprite.getGlobalBounds().width/2.f,700);
                                SpaceShip->HP--;
                                E3->EnemyRemoval(m);
                            }
                        }
                        for(int n=0;n<SpaceShip->NumBullets;n++)        //Bullet and enemy collion
                        {
                            for(int m=0;m<E3->getEnemySize();m++)
                            {
                                FloatRect B=E3->getSprite(m).getGlobalBounds();
                                FloatRect C=SpaceShip->B[n].sprite.getGlobalBounds();
                                if(IntersectBulletEnemy(B,C))
                                {
                                    SpaceShip->B[n].sprite.setPosition(0,-100);
                                    EXPA.play();
                                    E3->EnemyRemoval(m);
                                    ScoreState+=30;
                                    if(E3->getEnemySize()==0)
                                    {
                                        LevelState=10;
                                        LevelActiveState=false;
                                        TransitionState=1;
                                    }
                                }
                            }
                        }
                        
                        if(BombTimer<BombDelay)
                            BombTimer++;
                        if(BombTimer>=BombDelay)
                        {
                            BombTimer=0;
                            E3->Fire();                            
                        }

                        for(int n=0;n<E3->getBombNum();n++)     //bomb and player collision
                        {
                            FloatRect D=E3->getBombSprite(n).getGlobalBounds();
                            if(IntersectPlayerEnemyBomb(A,D))
                            {
                                EXPA.play();
                                SpaceShip->sprite.setPosition(600-SpaceShip->sprite.getGlobalBounds().width/2.f,700);
                                SpaceShip->HP--;
                                E3->getBombSprite(n).setPosition(100,1000);

                            }
                        }
                        E3->BombUpdate();
                    }   
                    else if(LevelState==4 && LevelActiveState==true)
                    {              
                        E1->SetSpeed(1.0);        
                        E1->MoveA();
                        FloatRect A=SpaceShip->sprite.getGlobalBounds();
                        for(int m=0;m<E1->getEnemySize();m++)   //Play and enemy colision
                        {
                            FloatRect B=E1->getSprite(m).getGlobalBounds();
                            if(IntersectPlayerEnemy(A,B))
                            {
                                EXPA.play();
                                SpaceShip->sprite.setPosition(600-SpaceShip->sprite.getGlobalBounds().width/2.f,700);
                                SpaceShip->HP--;
                                E1->EnemyRemoval(m);
                            }
                        }
                        for(int n=0;n<SpaceShip->NumBullets;n++)        //Bullet and Enemy collision
                        {
                            for(int m=0;m<E1->getEnemySize();m++)
                            {
                                FloatRect B=E1->getSprite(m).getGlobalBounds();
                                FloatRect C=SpaceShip->B[n].sprite.getGlobalBounds();
                                if(IntersectBulletEnemy(B,C))
                                {
                                    SpaceShip->B[n].sprite.setPosition(0,-100);
                                    EXPA.play();
                                    E1->EnemyRemoval(m);
                                    ScoreState+=20;
                                    if(E1->getEnemySize()==0)
                                    {
                                        LevelState=5;
                                        LevelActiveState=false;
                                        TransitionState=1;
                                    }
                                }
                            }
                        }
                        if(BombTimer<BombDelay)
                            BombTimer++;
                        if(BombTimer>=BombDelay)
                        {
                            BombTimer=0;
                            E1->Fire();                            
                        }
                        for(int n=0;n<E1->getBombNum();n++)     //bomb and player collision
                        {
                            FloatRect D=E1->getBombSprite(n).getGlobalBounds();
                            if(IntersectPlayerEnemyBomb(A,D))
                            {
                                EXPA.play();
                                SpaceShip->sprite.setPosition(600-SpaceShip->sprite.getGlobalBounds().width/2.f,700);
                                SpaceShip->HP--;
                                E1->getBombSprite(n).setPosition(100,1000);

                            }
                        }
                        E1->BombUpdate();
                    }     
                    else if(LevelState==5 && LevelActiveState==true)
                    {         
                        E2->SetSpeed(1);                 
                        E2->MoveA();
                        FloatRect A=SpaceShip->sprite.getGlobalBounds();
                        //bullet and enemy
                        for(int m=0;m<E2->getEnemySize();m++)   //player and enemy Collision
                        {
                            FloatRect B=E2->getSprite(m).getGlobalBounds();
                                if(IntersectPlayerEnemy(A,B))
                                {
                                    EXPA.play();
                                    SpaceShip->sprite.setPosition(600-SpaceShip->sprite.getGlobalBounds().width/2.f,700);
                                    SpaceShip->HP--;
                                    E2->EnemyRemoval(m);
                                }
                        }
                        for(int n=0;n<SpaceShip->NumBullets;n++)        //Bullet and enemy collision
                        {
                            for(int m=0;m<E2->getEnemySize();m++)
                            {
                                FloatRect B=E2->getSprite(m).getGlobalBounds();
                                FloatRect C=SpaceShip->B[n].sprite.getGlobalBounds();
                                if(IntersectBulletEnemy(B,C))
                                {
                                    SpaceShip->B[n].sprite.setPosition(0,-100);
                                    EXPA.play();
                                    E2->EnemyRemoval(m);
                                    ScoreState+=40;
                                    if(E2->getEnemySize()==0)
                                    {
                                        EXPA.play();
                                        LevelState=6;
                                        LevelActiveState=false;
                                        TransitionState=1;
                                    }
                                }
                            }
                        }
                        if(BombTimer<BombDelay)
                            BombTimer++;
                        if(BombTimer>=BombDelay)
                        {
                            BombTimer=0;
                            E2->Fire();                            
                        }
                        for(int n=0;n<E2->getBombNum();n++)     //bomb and player collision
                        {
                            FloatRect D=E2->getBombSprite(n).getGlobalBounds();
                            if(IntersectPlayerEnemyBomb(A,D))
                            {
                                EXPA.play();
                                SpaceShip->sprite.setPosition(600-SpaceShip->sprite.getGlobalBounds().width/2.f,700);
                                SpaceShip->HP--;
                                E2->getBombSprite(n).setPosition(100,1000);
                            }
                        }                    
                            E2->BombUpdate();
                    }                    
                    else if(LevelState==6 && LevelActiveState==true)
                    {                        
                        E3->MoveA();
                        E3->SetSpeed(1.5);
                        FloatRect A=SpaceShip->sprite.getGlobalBounds();
                        //bullet and enemy
                        for(int m=0;m<E3->getEnemySize();m++)   //Player and Enemy collision
                        {
                            FloatRect B=E3->getSprite(m).getGlobalBounds();
                            if(IntersectPlayerEnemy(A,B))
                            {
                                EXPA.play();
                                SpaceShip->sprite.setPosition(600-SpaceShip->sprite.getGlobalBounds().width/2.f,700);
                                SpaceShip->HP--;
                                E3->EnemyRemoval(m);
                            }
                        }
                        for(int n=0;n<SpaceShip->NumBullets;n++)        //Bullet and enemy collion
                        {
                            for(int m=0;m<E3->getEnemySize();m++)
                            {
                                FloatRect B=E3->getSprite(m).getGlobalBounds();
                                FloatRect C=SpaceShip->B[n].sprite.getGlobalBounds();
                                if(IntersectBulletEnemy(B,C))
                                {
                                    SpaceShip->B[n].sprite.setPosition(0,-100);
                                    EXPA.play();
                                    E3->EnemyRemoval(m);
                                    ScoreState+=60;
                                    if(E3->getEnemySize()==0)
                                    {
                                        EXPA.play();
                                        LevelState=11;
                                        LevelActiveState=false;
                                        TransitionState=1;
                                    }
                                }
                            }
                        }
                        
                        if(BombTimer<BombDelay)
                            BombTimer++;
                        if(BombTimer>=BombDelay)
                        {
                            BombTimer=0;
                            E3->Fire();                            
                        }

                        for(int n=0;n<E3->getBombNum();n++)     //bomb and player collision
                        {
                            FloatRect D=E3->getBombSprite(n).getGlobalBounds();
                            if(IntersectPlayerEnemyBomb(A,D))
                            {
                                EXPA.play();
                                SpaceShip->sprite.setPosition(600-SpaceShip->sprite.getGlobalBounds().width/2.f,700);
                                SpaceShip->HP--;
                                E3->getBombSprite(n).setPosition(100,1000);

                            }
                        }
                        E3->BombUpdate();
                    }
                    else if(LevelState==7 && LevelActiveState==true)
                    {              
                        E1->SetSpeed(1.5);        
                        E1->MoveA();
                        FloatRect A=SpaceShip->sprite.getGlobalBounds();
                        for(int m=0;m<E1->getEnemySize();m++)   //Play and enemy colision
                        {
                            FloatRect B=E1->getSprite(m).getGlobalBounds();
                            if(IntersectPlayerEnemy(A,B))
                            {
                                EXPA.play();
                                SpaceShip->sprite.setPosition(600-SpaceShip->sprite.getGlobalBounds().width/2.f,700);
                                SpaceShip->HP--;
                                E1->EnemyRemoval(m);
                            }
                        }
                        for(int n=0;n<SpaceShip->NumBullets;n++)        //Bullet and Enemy collision
                        {
                            for(int m=0;m<E1->getEnemySize();m++)
                            {
                                FloatRect B=E1->getSprite(m).getGlobalBounds();
                                FloatRect C=SpaceShip->B[n].sprite.getGlobalBounds();
                                if(IntersectBulletEnemy(B,C))
                                {
                                    SpaceShip->B[n].sprite.setPosition(0,-100);
                                    EXPA.play();
                                    E1->EnemyRemoval(m);
                                    ScoreState+=30;
                                    if(E1->getEnemySize()==0)
                                    {
                                        EXPA.play();
                                        LevelState=8;
                                        LevelActiveState=false;
                                        TransitionState=1;
                                    }
                                }
                            }
                        }
                        if(BombTimer<BombDelay)
                            BombTimer++;
                        if(BombTimer>=BombDelay)
                        {
                            BombTimer=0;
                            E1->Fire();                            
                        }
                        for(int n=0;n<E1->getBombNum();n++)     //bomb and player collision
                        {
                            FloatRect D=E1->getBombSprite(n).getGlobalBounds();
                            if(IntersectPlayerEnemyBomb(A,D))
                            {
                                EXPA.play();
                                SpaceShip->sprite.setPosition(600-SpaceShip->sprite.getGlobalBounds().width/2.f,700);
                                SpaceShip->HP--;
                                E1->getBombSprite(n).setPosition(100,1000);

                            }
                        }
                        E1->BombUpdate();
                    }              
                    else if(LevelState==8 && LevelActiveState==true)
                    {         
                        E2->SetSpeed(1.5);                 
                        E2->MoveA();
                        FloatRect A=SpaceShip->sprite.getGlobalBounds();
                        //bullet and enemy
                        for(int m=0;m<E2->getEnemySize();m++)   //player and enemy Collision
                        {
                            FloatRect B=E2->getSprite(m).getGlobalBounds();
                                if(IntersectPlayerEnemy(A,B))
                                {
                                    EXPA.play();
                                    SpaceShip->sprite.setPosition(600-SpaceShip->sprite.getGlobalBounds().width/2.f,700);
                                    SpaceShip->HP--;
                                    E2->EnemyRemoval(m);
                                }
                        }
                        for(int n=0;n<SpaceShip->NumBullets;n++)        //Bullet and enemy collision
                        {
                            for(int m=0;m<E2->getEnemySize();m++)
                            {
                                FloatRect B=E2->getSprite(m).getGlobalBounds();
                                FloatRect C=SpaceShip->B[n].sprite.getGlobalBounds();
                                if(IntersectBulletEnemy(B,C))
                                {
                                    SpaceShip->B[n].sprite.setPosition(0,-100);
                                    EXPA.play();
                                    E2->EnemyRemoval(m);
                                    ScoreState+=60;
                                    if(E2->getEnemySize()==0)
                                    {
                                        EXPA.play();
                                        LevelState=9;
                                        LevelActiveState=false;
                                        TransitionState=1;
                                    }
                                }
                            }
                        }
                        if(BombTimer<BombDelay)
                            BombTimer++;
                        if(BombTimer>=BombDelay)
                        {
                            BombTimer=0;
                            E2->Fire();                            
                        }
                        for(int n=0;n<E2->getBombNum();n++)     //bomb and player collision
                        {
                            FloatRect D=E2->getBombSprite(n).getGlobalBounds();
                            if(IntersectPlayerEnemyBomb(A,D))
                            {
                                EXPA.play();
                                SpaceShip->sprite.setPosition(600-SpaceShip->sprite.getGlobalBounds().width/2.f,700);
                                SpaceShip->HP--;
                                E2->getBombSprite(n).setPosition(100,1000);
                            }
                        }                    
                        E2->BombUpdate();
                    }                  
                    else if(LevelState==9 && LevelActiveState==true)
                    {                        
                        E3->MoveA();
                        E3->SetSpeed(1.5);
                        FloatRect A=SpaceShip->sprite.getGlobalBounds();
                        //bullet and enemy
                        for(int m=0;m<E3->getEnemySize();m++)   //Player and Enemy collision
                        {
                            FloatRect B=E3->getSprite(m).getGlobalBounds();
                            if(IntersectPlayerEnemy(A,B))
                            {
                                EXPA.play();
                                SpaceShip->sprite.setPosition(600-SpaceShip->sprite.getGlobalBounds().width/2.f,700);
                                SpaceShip->HP--;
                                E3->EnemyRemoval(m);
                            }
                        }
                        for(int n=0;n<SpaceShip->NumBullets;n++)        //Bullet and enemy collion
                        {
                            for(int m=0;m<E3->getEnemySize();m++)
                            {
                                FloatRect B=E3->getSprite(m).getGlobalBounds();
                                FloatRect C=SpaceShip->B[n].sprite.getGlobalBounds();
                                if(IntersectBulletEnemy(B,C))
                                {
                                    SpaceShip->B[n].sprite.setPosition(0,-100);
                                    EXPA.play();
                                    E3->EnemyRemoval(m);
                                    ScoreState+=90;
                                    if(E3->getEnemySize()==0)
                                    {
                                        LevelState=12;
                                        LevelActiveState=false;
                                        TransitionState=1;
                                    }
                                }
                            }
                        }
                        
                        if(BombTimer<BombDelay)
                            BombTimer++;
                        if(BombTimer>=BombDelay)
                        {
                            BombTimer=0;
                            E3->Fire();                            
                        }

                        for(int n=0;n<E3->getBombNum();n++)     //bomb and player collision
                        {
                            FloatRect D=E3->getBombSprite(n).getGlobalBounds();
                            if(IntersectPlayerEnemyBomb(A,D))
                            {
                                EXPA.play();
                                SpaceShip->sprite.setPosition(600-SpaceShip->sprite.getGlobalBounds().width/2.f,700);
                                SpaceShip->HP--;
                                E3->getBombSprite(n).setPosition(100,1000);

                            }
                        }
                        E3->BombUpdate();
                    }
                    else if(LevelState==10 && LevelActiveState==true)
                    {
                        RockDurationTimer++;
                        if(RockDurationTimer>=RockDurationDelay)
                        {   
                            ScoreState+=500;
                            LevelState=4;
                            LevelActiveState=false;
                            TransitionState=1;
                            SpaceShip->HP++;
                        }
                        if(RockTimer<RockDelay)
                            RockTimer++;
                        if(RockTimer>=RockDelay)
                        {
                            R->RockSpawn();
                            RockTimer=0;
                        }
                        FloatRect A=SpaceShip->sprite.getGlobalBounds();
                        for(int n=0;n<R->NumRocks;n++)
                        {
                            FloatRect B=R->GetSprite(n).getGlobalBounds();
                            if(IntersectPlayerRock(A,B))
                            {
                                EXPA.play();
                                ScoreState-=500;
                                SpaceShip->HP--;
                                RockDurationTimer=RockDurationDelay;
                            }
                        }

                        R->RockUpdate();
                    }
                    else if(LevelState==11 && LevelActiveState==true)   //level 11   
                    {
                        M1->Move();
                        FloatRect A=SpaceShip->sprite.getGlobalBounds();
                        FloatRect B=M1->getSprite(0).getGlobalBounds();
                        if(IntersectPlayerMonster(A,B))     //Player Monster Collision
                        {
                            EXPA.play();
                            SpaceShip->HP--;
                            M1->getSprite(0).setPosition(10,10);
                            SpaceShip->sprite.setPosition(600,700);
                        }     
                        for(int n=0;n<SpaceShip->NumBullets;n++)        //Bullet and Enemy collision
                        {
                            FloatRect C=SpaceShip->B[n].sprite.getGlobalBounds();
                            if(IntersectBulletMonster(C,B))
                            {
                                SpaceShip->B[n].sprite.setPosition(0,-100);
                                EXPA.play();
                                BossDamage+=1;
                                ScoreState+=1;
                                if(M1->getHP()<=BossDamage)
                                {
                                    LevelState=7;
                                    LevelActiveState=false;
                                    TransitionState=1;
                                    BossDamage=0;
                                    ScoreState+=1000;
                                }
                            }
                        }
                        FloatRect D=M1->getLaser().getGlobalBounds();
                        if(IntersectPlayerMonsterBeam(A,D) && LaserChecker)     //Player Monster Beam Collision
                        {
                            EXPA.play();
                            SpaceShip->HP--;
                            SpaceShip->sprite.setPosition(50,700);
                        }
            
                        if(BossLaserTimer<=BossLaserStart)
                        {
                            BossLaserTimer++;
                            LaserChecker=false;
                        }
                        else if(BossLaserTimer>BossLaserStart && BossLaserTimer<=BossLaserStop)
                        {
                            BossLaserTimer++;
                            LaserChecker=true;
                        }    
                        else if(BossLaserTimer>BossLaserStop)
                        {
                            LaserChecker=false;
                            BossLaserTimer=0;
                        }
                    }
                    else if(LevelState==12 && LevelActiveState==true)   //level 12  
                    {
                        M2->SetSpeed(3);
                        M2->Move();
                        FloatRect A=SpaceShip->sprite.getGlobalBounds();
                        FloatRect B=M2->getSprite(0).getGlobalBounds();
                        if(IntersectPlayerGoku(A,B))     //Player Monster Collision
                        {
                            EXPA.play();
                            SpaceShip->HP--;
                            M2->getSprite(0).setPosition(10,10);
                            SpaceShip->sprite.setPosition(600,700);
                        } 
                        for(int n=0;n<SpaceShip->NumBullets;n++)        //Bullet and Enemy collision
                        {
                            FloatRect C=SpaceShip->B[n].sprite.getGlobalBounds();
                            if(IntersectBulletGoku(C,B))
                            {
                                SpaceShip->B[n].sprite.setPosition(0,-100);
                                EXPA.play();
                                BossDamage+=1;
                                ScoreState+=1;
                                if(M2->getHP()<=BossDamage)
                                {
                                    LevelState=1;
                                    LevelActiveState=false;
                                    TransitionState=1;
                                    BossDamage=0;
                                    ScoreState+=1000;
                                }
                            }
                        }
                       
                        if(BombTimer<BombDelay)
                            BombTimer++;
                        if(BombTimer>=50)
                        {
                            M2->SetDirectiion(GokuBeamX,GokuBeamY,GokuDirection);
                            BombTimer=0;
                            M2->GokuFire();
                            if(GokuTimer<GokuDelay)
                                GokuTimer++;
                            if(GokuTimer>=GokuDelay)
                            {
                                if(GokuDirection==0)
                                {
                                    GokuDirection=30;
                                    GokuBeamX=0.33;
                                    GokuBeamY=0.67;
                                }
                                else if(GokuDirection==30)
                                {
                                    GokuDirection=-30;
                                    GokuBeamX=-0.33;
                                    GokuBeamY=0.67;
                                }
                                else if(GokuDirection==-30)
                                {
                                    GokuDirection=0;
                                    GokuBeamX=0;
                                    GokuBeamY=1;
                                }
                                GokuTimer=0;
                            }    
                        }
                         
                        for(int n=0;n<M2->getBombNum();n++)
                        {
                            FloatRect C=M2->getBombSprite(n).getGlobalBounds();
                            if(IntersectPlayerGokuBeam(A,C))
                            {
                                EXPA.play();
                                SpaceShip->sprite.setPosition(100.f,700);
                                SpaceShip->HP--;
                                M2->getBombSprite(n).setPosition(100,1000);
                            }
                        }
                        M2->UpdateBeam();

                    }
                    
                }
//--------------------------------------------Player Movement and Pass Through window-------------------------------------------------// 
                if(true)    
                {
                    if (Keyboard::isKeyPressed(Keyboard::A))    //If left key is pressed
                    {
                        SpaceShip->move(-1.f,0.f);                      // Player will move to left
                        LeftChecker=1;
                    }
                    else if (Keyboard::isKeyPressed(Keyboard::D))    // If right key is pressed
                    {
                        SpaceShip->move(1.f,0.f);                       //player will move to right
                        RightChecker=1;
                    }   
                    if (Keyboard::isKeyPressed(Keyboard::W))    //If up key is pressed
                    {
                        SpaceShip->move(0.f,-1.f);                      //playet will move upwards SpaceShip->  SpaceShip->LivesDisplay(Lives);SpaceShip->LivesDisplay(Lives); SpaceShip->LivesDisplay(Lives);ivesDisplay(Lives);
                        TopChecker=1;
                    }
                    else if (Keyboard::isKeyPressed(Keyboard::S))    // If down key is pressed
                    {
                        SpaceShip->move(0.f,1.f);                       //player will move downwards  
                    }
                    if(Keyboard::isKeyPressed(Keyboard::Q))
                    {
                        LeftChecker=1;
                        TopChecker=1;
                        SpaceShip->SetTexture(&PLU);
                        SpaceShip->SetDirection(-0.33,-0.67,-30);
                    }
                    else if(Keyboard::isKeyPressed(Keyboard::E))
                    {
                        RightChecker=1;
                        TopChecker=1;
                        SpaceShip->SetTexture(&PRU);
                        SpaceShip->SetDirection(0.33,-0.67,30);
                    }
                    else if(LeftChecker==1 && RightChecker==0)
                    {
                        SpaceShip->SetTexture(&PL);
                        SpaceShip->SetDirection(0,-1,0);
                    } 
                    else if(LeftChecker==0 && RightChecker==1)
                    {
                        SpaceShip->SetTexture(&PR);
                    }
                    else if(TopChecker ==1)
                    {
                        SpaceShip->SetTexture(&Playertexture);
                        SpaceShip->SetDirection(0,-1,0);
                    }
                    else
                    {
                        SpaceShip->SetTexture(&Playertexture);
                        SpaceShip->SetDirection(0,-1,0);
                    }
                }     
//-----------------------------------------------------------Player Bullet Making Part-------------------------------------------------------//   
                if(true)  
                {
                    if(BulletTimer<BulletDelay)
                        BulletTimer++;
                    if (Keyboard::isKeyPressed(Keyboard::K) && BulletTimer>=BulletDelay)
                    {
                        BFA.play();
                        BulletTimer=0;
                        SpaceShip->Fire();
                    }
                    //Update Bullets
                    SpaceShip->BulletUpdate();
                }
//-----------------------------------------------------------Player Diagonal Wrape Conditions--------------------------------------------------------//   
                if(true)  
                {
                    if (SpaceShip->sprite.getPosition().x < 0)                                                                             //Left
                        SpaceShip->sprite.setPosition(window.getSize().x-SpaceShip->sprite.getGlobalBounds().width, SpaceShip->sprite.getPosition().y);
                    else if (SpaceShip->sprite.getPosition().x > window.getSize().x - SpaceShip->sprite.getGlobalBounds().width)                   //Right
                        SpaceShip->sprite.setPosition(0.f, SpaceShip->sprite.getPosition().y);
                    
                    if (SpaceShip->sprite.getPosition().y < 0) //Top
                        SpaceShip->sprite.setPosition(SpaceShip->sprite.getPosition().x, window.getSize().y-SpaceShip->sprite.getGlobalBounds().height);
                    else if (SpaceShip->sprite.getPosition().y > window.getSize().y - SpaceShip->sprite.getGlobalBounds().height) //Bottom
                        SpaceShip->sprite.setPosition(SpaceShip->sprite.getPosition().x, 0.f);
                }
//-----------------------------------------------------------Add Ons--------------------------------------------------------//  
                if(true)
                {
                    if(AddonTimer<=AddonDelay && PowerState==0)
                    {
                        AddonTimer++;
                    } 
                    if(AddonTimer>AddonDelay && PowerState==0)
                    {
                        AddonTimer=0;
                        PowerState=1;
                        PowerupType=SpaceShip->Power.RandomPower();
                        SpaceShip->Power.SpawnPower();

                    }
                    if(PowerState==1 && PowerTimer<PowerDelay)
                    {
                        SpaceShip->Power.Update();
                        if(SpaceShip->Power.IsOFFscreen())
                        {
                            PowerState=0;
                            PowerTimer=0;
                            PowerupType=1;
                        }    
                        if(PowerupType==1)  //life add
                        {
                            if(SpaceShip->sprite.getGlobalBounds().intersects(SpaceShip->Power.sprite.getGlobalBounds()))
                            {
                                SpaceShip->HP++;
                                PowerState=0;
                                SpaceShip->Power.SpawnPower();
                            }
                        }
                        else if (PowerupType==2)    //live remove
                        {
                            if(SpaceShip->sprite.getGlobalBounds().intersects(SpaceShip->Power.sprite.getGlobalBounds()))
                            {
                                SpaceShip->HP--;
                                PowerState=0;
                                SpaceShip->Power.SpawnPower();
                            }
                        }
                        else if (PowerupType==3)    //fire 2x
                        {
                            if(SpaceShip->sprite.getGlobalBounds().intersects(SpaceShip->Power.sprite.getGlobalBounds()))
                            {   
                                PowerState=1;
                                BulletDelay=15;
                                PowerupType=0;
                            }
                        }
                        else if (PowerupType==4)    //fire 0.5
                        {
                            if(SpaceShip->sprite.getGlobalBounds().intersects(SpaceShip->Power.sprite.getGlobalBounds()))
                            {
                                PowerState=1;
                                BulletDelay=60;
                                PowerupType=0;
                            }
                        }
                        else if (PowerupType==5)    //sheild to be updated
                        {
                            if(SpaceShip->sprite.getGlobalBounds().intersects(SpaceShip->Power.sprite.getGlobalBounds()))
                            {
                                PowerState=1;
                                BulletDelay=60;
                                PowerupType=0;
                            }   
                        }
                        PowerTimer++;
                    }
                    if(PowerState==1 && PowerTimer>=PowerDelay)
                    {
                        PowerState=0;
                        PowerTimer=0;
                        PowerupType=1;
                        BulletDelay=30;
                        AddonTimer=0;
                    }
                }
//-----------------------------------------------------------Player HP checker for game End-------------------------------------------------------//   
                if(SpaceShip->HP==0)
                { 
                    MenuState=6; 
                    GameState=0;
                    SelectorState=1;   
                    LevelActiveState=1;            
                }     
                BackgroundSprite.move(0.f,0.15f); //Background Movement
            }
                  
//------------------------------------------------------------------------------------------------------------------------------------//   
//----------------------------------------------Game Displaying Part------------------------------------------------------------------//    
//------------------------------------------------------------------------------------------------------------------------------------//                  
           
            window.clear(Color::White);     //clears the screen   

            if(!GameState)//----------------------------------------------Menue Displayer-----------------------------------------------//  
            {
                if(MenuState==1 || MenuState==2)
                {
                    window.draw(MenuSprite);
                    window.draw(SelectorSprite);
                }
                else if(MenuState==3)
                {
                    window.draw(LevelsSprite);
                }
                else if(MenuState==4)
                {
                    window.draw(HighScoreSprite);
                }
                else if(MenuState==5)
                {
                    window.draw(HelpSprite);
                }
                else if(MenuState==6)
                {
                    window.draw(ScoreAddSprite);
                    M.DisplayEndScore(ScoreState,window);
                    window.draw(Name);
                }
            }  
            else if(TransitionState && GameState)    //----------------------------------------------Game Transition Displayer---------------------//  
            {
                M.DisplayTransition(window);
                SpaceShip->NumBullets=0;
            }  
            else if(!TransitionState && GameState)   //----------------------------------------------Game Working-----------------------------------//  
            {
//----------------------------------------------Backgroung drawer------------------------------------------------------------------//  
                window.draw(BackgroundSprite);                              
//----------------------------------------------Bullet drawer------------------------------------------------------------------//                  
                SpaceShip->draw(&window);     
//----------------------------------------------Level Drawer------------------------------------------------------------------//  
                
                if(LevelState==1 && LevelActiveState)
                {
                    E1->BulletDraw(&window);
                    E1->draw(window);

                }   
                else if(LevelState==2 && LevelActiveState)
                {
                    E2->BulletDraw(&window);
                    E2->draw(window);

                }   
                else if(LevelState==3 && LevelActiveState)
                {
                    E3->BulletDraw(&window);
                    E3->draw(window);

                }   
                else if(LevelState==4 && LevelActiveState)
                {
                    E1->BulletDraw(&window);
                    E1->draw(window);

                }   
                else if(LevelState==5 && LevelActiveState)
                {
                    E2->BulletDraw(&window);
                    E2->draw(window);

                }   
                else if(LevelState==6 && LevelActiveState)
                {
                    E3->BulletDraw(&window);
                    E3->draw(window);

                }   
                else if(LevelState==7 && LevelActiveState)
                {
                    E1->BulletDraw(&window);
                    E1->draw(window);

                }   
                else if(LevelState==8 && LevelActiveState)
                {
                    E2->BulletDraw(&window);
                    E2->draw(window);

                }   
                else if(LevelState==9 && LevelActiveState)
                {
                    E3->BulletDraw(&window);
                    E3->draw(window);

                }                   
                else if(LevelState==10 && LevelActiveState)
                {
                    R->draw(window);
                }
                else if(LevelState==11 && LevelActiveState)
                {
                    if(LaserChecker)
                        M1->LaserDraw(window);
                    M1->draw(window);
                }
                else if(LevelState==12 && LevelActiveState)
                {

                    M2->draw(window);
                    M2->GokuBeamDraw(window);
                }


//----------------------------------------------Player Drawer------------------------------------------------------------------//  
                window.draw(SpaceShip->sprite);     
//----------------------------------------------Player Lives Drawer------------------------------------------------------------------//      
                M.DisplayLive(SpaceShip->HP,window);
//----------------------------------------------Score Drawer------------------------------------------------------------------//  
                M.DisplayScore(ScoreState,window);
//----------------------------------------------Addon Drawer------------------------------------------------------------------//  
                if(PowerState==1 && PowerupType)
                    SpaceShip->Power.Draw(window);
            }
            
            window.draw(CursorSprite);
            window.display();               //Displying all the sprites
        }
        RecordFile.close();
        BackgroundMusic.stop();
    }
};
