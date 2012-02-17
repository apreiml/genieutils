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
  
  for (uint32_t row=0; row < height; row++)
    for (uint32_t col=0; col < width; col++)
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

  genie::DrsFile interfac;
  
  interfac.setGameVersion(genie::GV_AoK);
  interfac.load("slptest/interfac.drs");
  
  genie::PalFilePtr pal = interfac.getPalFile(50500);
  
  genie::DrsFile drs;
  
//   drs.setGameVersion(genie::GV_AoE);
//   drs.load("slptest/graphics_aoe.drs");
  
//   drs.setGameVersion(genie::GV_SWGB);
//   drs.load("slptest/graphics_x1.drs");
  
  drs.setGameVersion(genie::GV_AoK);
  drs.load("slptest/graphics.drs");
  
  sf::RenderWindow App(sf::VideoMode(800, 600, 32), "SFML Graphics");

  uint32_t slp_id = 2;

  
  sf::Texture text;
    
  genie::SlpFilePtr slpf = drs.getSlpFile(slp_id);
    
  text.LoadFromImage(createSfImage(slpf->getFrame(0), pal));
  
  sf::Sprite Sprite(text);

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
