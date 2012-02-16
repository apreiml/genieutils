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
#include "genie/resource/SlpFile.h"
#include "genie/resource/Color.h"

sf::Image createSfImage(uint32_t width, uint32_t height, const uint8_t* pixels, 
                        genie::PalFilePtr palette, uint8_t transparent_pixel)
{
  sf::Image img;
  
  img.Create(width, height, sf::Color::Transparent);
  
  for (uint32_t row=0; row < width; row++)
    for (uint32_t col=0; col < height; col++)
    {
      uint8_t c_index = pixels[row * width + col];
      
      if (c_index != transparent_pixel)
      {
        genie::Color g_color = (*palette)[c_index];
        img.SetPixel(col, row, sf::Color(g_color.r, g_color.g, g_color.b));
      }           
    }
  
  return img;
}

sf::Image createSfImage(genie::SlpFrame &frame, genie::PalFilePtr palette)
{
  return createSfImage(frame.getWidth(), frame.getHeight(), 
                       frame.getPixelIndexes(), palette, 
                       frame.getTransparentPixelIndex());
}


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
  
  slp.load("slptest/backgrd1.slp");
  
  genie::DrsFile drs;
  
  drs.load("slptest/graphics.drs");
  
  sf::RenderWindow App(sf::VideoMode(800, 600, 32), "SFML Graphics");

    // Create the sprite

    sf::Texture text;
    sf::Texture text2;
    
    text2.LoadFromImage(createSfImage(drs.getSlpFile(2)->getFrame(), pal));
 
    genie::SlpFilePtr slpf = drs.getSlpFile(2);
    //text.LoadFromImage(*drs.getSlpFile(2)->getFrame().getPlayerColorMask(3));
    
    text.LoadFromImage(createSfImage(slpf->getFrame(1), pal));
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
