#include <iostream>
#include <genie/resource/ColorPalette.h>
#include <fstream>
#include <genie/resource/SlpFile.h>
#include <genie/resource/SlpFrame.h>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Texture.hpp>


int main(int argc, char **argv) {

  genie::ColorPalettePtr pal(new genie::ColorPalette());
  
  std::fstream file;
  
  file.open("slptest/backgrd1.pal", std::ios::in | std::ios::binary);
  
  
  pal->parsePalette(file);
  
  
  genie::SlpFile slp;
  slp.setColorPalette(pal);
  
  slp.load("slptest/backgrd1.slp");
  
  std::cout << "Framecount: " <<  slp.getFrameCount() << std::endl;
  std::cout << " " <<  slp.getFrame(0) << std::endl;
    
  
  sf::RenderWindow App(sf::VideoMode(800, 600, 32), "SFML Graphics");

    // Create the sprite

    sf::Texture text;
 
    text.LoadFromImage(*slp.getFrame()->getImage());
    sf::Sprite Sprite(text);

    // Change its properties
    Sprite.SetPosition(0, 0);

    // Start game loop
    while (App.IsOpen())
    {
        // Process events
        sf::Event Event;
        while (App.PollEvent(Event))
        {
            // Close window : exit
            if (Event.Type == sf::Event::Closed)
                App.Close();
        }

        // Clear screen
        App.Clear();

        // Display sprite in our window
        App.Draw(Sprite);

        // Display window contents on screen
        App.Display();
    }

  return 0;
}
