#include <iostream>
#include <vector>
#include <genie/resource/PalFile.h>
#include <fstream>
#include <genie/resource/SlpFile.h>
#include <genie/resource/SlpFrame.h>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Texture.hpp>
#include "genie/resource/DrsFile.h"


int main(int argc, char **argv) {
  

  genie::PalFilePtr pal(new genie::PalFile());
  genie::PalFilePtr pal2(new genie::PalFile());
  
  std::fstream file;
  
 // file.open("slptest/50500.pal", std::ios::in | std::ios::binary);
  
  pal->load("slptest/50500.pal");
  
  std::cout << "50500_size: " << pal->objectSize() << std::endl;
  pal->saveAs("slptest/test.pal");
  
  pal2->load("slptest/test2.pal");
  std::cout << "test2_size: " << pal2->objectSize() << std::endl;
  //(*pal)[1000];
  
  //pal->parsePalette(file);
  
  
  genie::SlpFile slp;
  slp.setColorPalette(pal);
  
  slp.load("slptest/backgrd1.slp");
  
  genie::DrsFile drs;
  
  drs.setDefaultPalette(pal);
  
  drs.load("slptest/graphics.drs");
  
  sf::RenderWindow App(sf::VideoMode(800, 600, 32), "SFML Graphics");

    // Create the sprite

    sf::Texture text;
    sf::Texture text2;
    
    text2.LoadFromImage(*drs.getSlpFile(2)->getFrame().getImage());
 
    text.LoadFromImage(*drs.getSlpFile(2)->getFrame().getPlayerColorMask(3));
    //text.LoadFromImage(*slp.getFrame()->getImage());
    sf::Sprite Sprite(text);
    sf::Sprite s2(text2);

    // Change its properties
    Sprite.SetPosition(0, 0);
    s2.SetPosition(100,100);

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
        App.Draw(s2);

        // Display window contents on screen
        App.Display();
    }

  return 0;
}
