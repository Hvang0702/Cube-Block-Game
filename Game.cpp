#include "Game.h"


//Private functions
void Game::initVariables()
{
	this->window = nullptr;

    //Game logic
    this->endGame = false;
    this->points = 0;
    this->health = 10;
    this->enemySpawnTimerMax = 20.f;
    this->enemySpawnTimer = this->enemySpawnTimerMax;
    this->maxEnemies = 5;
    this->mouseHeld = false;

}

void Game::initWindow()
{
	this->videoMode.height = 700; //630
	this->videoMode.width = 800;  //800
	//this->videoMode.getDesktopMode;

	this->window = new sf::RenderWindow(this->videoMode, "My first game", sf::Style::Titlebar | sf::Style::Close);
    
    this->window->setFramerateLimit(60); //Framerate limit
}

void Game::initFonts()
{

    if (!this->font.loadFromFile("C:/Users/Hue/source/repos/Fonts/CascadiaCode.ttf"))
    {
        std::cout << "ERROR::GAME::INITFONTS::Failed to load font!" << "\n";
    }
}

void Game::initText()
{
    this->uiText.setFont(this->font);
    this->uiText.setCharacterSize(20);
    this->uiText.setFillColor(sf::Color::White); 
    this->uiText.setLetterSpacing(1.f);
    this->uiText.setString("NONE");
}

void Game::initEnemies()
{
    this->enemy.setPosition(10.f,10.f);
    this->enemy.setSize(sf::Vector2f(100.f, 100.f));
    //this->enemy.setScale(sf::Vector2f(0.5f, 0.5f));
    this->enemy.setFillColor((sf::Color(rand() % 255, rand() % 200, rand() % 200))); //sf::Color::Cyan for Cyan enemies

}


//Constructors / Destructors
Game::Game() 
{
	this->initVariables();
	this->initWindow();
    this->initFonts();
    this->initText();
    this->initEnemies();
}

Game::~Game() 
{
	delete this->window;
}

//Accessors
const bool Game::running() const
{
	return this->window->isOpen();
}

const bool Game::getEndGame() const
{
    return this->endGame;
}

//Functions
void Game::update()
{
    this->pollEvents();

    if (this->endGame == false)
    {
        this->updateMousePositions();

        this->updateText();

        this->updateEnemies();
    }

    if (this->health <= 0)
        this->endGame = true;
}
 
void Game::spawnEnemy()
{
    /*
        @return void

        Spawns enemies and sets their types and colors. Spawns them at random positions.
        * Sets a random type (diff)
        *Sets a random position.
        * Sets a random color
        * Adds enemy to the vector.
    */

    this->enemy.setPosition(
        static_cast<float>(rand() % static_cast<int>(this->window->getSize().x - this->enemy.getSize().x)),
        0.f
    );

    //Randomize enemy type
    int type = rand() % 4;

    switch (type)
    {
    case 0:
        this->enemy.setFillColor(sf::Color::Magenta);
        this->enemy.setSize(sf::Vector2f(20.f, 20.f));

        break;

    case 1:
        this->enemy.setFillColor(sf::Color::Blue);
        this->enemy.setSize(sf::Vector2f(30.f, 30.f));

        break;

    case 2:
        this->enemy.setFillColor(sf::Color::Yellow);
        this->enemy.setSize(sf::Vector2f(50.f, 50.f));

        break;

    case 3:
        this->enemy.setFillColor(sf::Color::Red);
        this->enemy.setSize(sf::Vector2f(70.f, 70.f));

        break;

    case 4:
        this->enemy.setFillColor(sf::Color::Green);
        this->enemy.setSize(sf::Vector2f(100.f, 100.f));

        break;

    default: 
        this->enemy.setFillColor(sf::Color::White);
        this->enemy.setSize(sf::Vector2f(100.f, 100.f));
        break;

    }

    //Enemies are now randomized colors
    //this->enemy.setFillColor(((sf::Color(rand() % 255, rand() % 255, rand() % 255)))); //sf::Color::Green (Enemies are green color)

    //Sets the outline color and thickness to stand out more
    this->enemy.setOutlineColor(sf::Color::Cyan);
    this->enemy.setOutlineThickness(2.f);

    //Spawn the enemy
    this->enemies.push_back(this->enemy);

    //Remove the enemies at end of screen



}

void Game::pollEvents()
{
        //Event polling
        while (this->window->pollEvent(this->ev)) {

            switch (this->ev.type) 
            {

            case sf::Event::Closed:
                this->window->close();
                break;

            case sf::Event::KeyPressed:
                if (this->ev.key.code == sf::Keyboard::Escape)
                    this->window->close();
                break;

            }
        }
}

void Game::updateMousePositions()
{
    /*
    @ return void

    Updates the mouse positions:
        * Mouse position relative to window (Vector2i)
    */

    this->mousePosWindow = sf::Mouse::getPosition(*this->window);
    this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);

}

void Game::updateText()
{
    std::stringstream ss;

    ss << "Points: " << this->points << "\n" << "Health: " << this->health << "\n";

    this->uiText.setString(ss.str());
}

void Game::updateEnemies()
{
    /*
     @return void

     Updates the enemy spawn timer and spawns enemies
     when the total amount of enemies is smaller than the max.
     Moves the enemies downwards
     Removes the enemies at the edge of the screen //TODO
    */
    //Updating the timer for enemy spawning
    if (this->enemies.size() < this->maxEnemies)
    {
        if (this->enemySpawnTimer >= this->enemySpawnTimerMax)
        {
            //Spawn the enemy and reset the timer
            this->spawnEnemy();
            this->enemySpawnTimer = 0.f;
        }
        else
            this->enemySpawnTimer += 1.f;
    }

    //Move and updating the enemies
    for (int i = 0; i < this->enemies.size(); i++)
    {
        bool deleted = false;

        //Adjusting the game speed by using the points
        /*
            The more points the user has the faster the speed gets
        */
        if (this->points <= 99) {
            this->enemies[i].move(0.f, 3.f);
        }
        if (this->points >= 100 && this->points <= 199) {
            this->enemies[i].move(0.f, 4.f);
        }
        if (this->points >= 200 && this->points <= 299) {
            this->enemies[i].move(0.f, 5.f);
        }
        if (this->points >= 300 && this->points <= 399) {
            this->enemies[i].move(0.f, 6.f);
        }
        
        //If the enemy is past the bottom of the screen then delete
        if (this->enemies[i].getPosition().y > this->window->getSize().y)
        {
            this->enemies.erase(this->enemies.begin() + i);
            this->health -= 1;
            std::cout << "Health: " << this->health << "\n";

        }

       
    }

    //Check if clicked upon
    
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        if (this->mouseHeld == false)
        {
            this->mouseHeld = true;
            bool deleted = false;
            for (size_t i = 0; i < this->enemies.size() && deleted == false; i++)
            {
                if (this->enemies[i].getGlobalBounds().contains(this->mousePosView))
                {
                  
                    //Gain points
                    if(this->enemies[i].getFillColor() == sf::Color::Magenta)
                        this->points += 10.f;
                    else if(this->enemies[i].getFillColor() == sf::Color::Blue)
                        this->points += 7.f;
                    else if (this->enemies[i].getFillColor() == sf::Color::Yellow)
                        this->points += 5.f;
                    else if (this->enemies[i].getFillColor() == sf::Color::Red)
                        this->points += 3.f;
                    else if (this->enemies[i].getFillColor() == sf::Color::Green)
                        this->points += 1.f;

                    std::cout << "Points: " << this->points << "\n";

                    //Delete the enemy
                    deleted = true;
                    this->enemies.erase(this->enemies.begin() + i);
                }
            }
        }
    }
    else
    {
        this->mouseHeld = false;
    }
}

void Game::renderText(sf::RenderTarget& target)
{
    target.draw(this->uiText);
}

void Game::renderEnemies(sf::RenderTarget& target)
{
    //Rendering all the enemies
    for (auto& e : this->enemies)
    {
        target.draw(e);
    }
}

void Game::render()
{
        /*
        @Return void

            *Clear old frame
            * Render objects
            * Display frame in window
            Renders the game objects.
        */

        this->window->clear(); //sf::Color(137,207,240) for baby blue

        //Draw game objects
        this->renderEnemies(*this->window); 

        this->renderText(*this->window);

        this->window->display();
}



