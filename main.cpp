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
  
  std::fstream file;
  
 // file.open("slptest/50500.pal", std::ios::in | std::ios::binary);
  
  pal->load("slptest/50500.pal");
  
  //(*pal)[1000];
  
  //pal->parsePalette(file);
  
  
  genie::SlpFile slp;
  slp.setColorPalette(pal);
  
  slp.load("slptest/backgrd1.slp");
  
  std::cout << "Framecount: " <<  slp.getFrameCount() << std::endl;
  std::cout << " " <<  slp.getFrame(0) << std::endl;
    
  genie::DrsFile drs;
  
  drs.pal_ = pal;
  
  drs.load("slptest/graphics.drs");
  
  sf::RenderWindow App(sf::VideoMode(800, 600, 32), "SFML Graphics");

    // Create the sprite

    sf::Texture text;
    
 
    text.LoadFromImage(*drs.getSlpFile(2)->getFrame()->getImage());
    //text.LoadFromImage(*slp.getFrame()->getImage());
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
