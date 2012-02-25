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
#include <genie/script/ScnFile.h>
#include <genie/file/Compressor.h>
#include <boost/iostreams/copy.hpp>
#include <boost/smart_ptr.hpp>

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

sf::Image createSfImage(genie::SlpFramePtr frame, genie::PalFilePtr palette)
{
  return createSfImage(frame->getWidth(), frame->getHeight(), 
                       frame->getPixelIndexes(), palette, 
                       frame->getTransparentPixelIndex());
}


void testDrs()
{
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
//   drs.load("slptest/graphics.drs");
  drs.load("slptest/terrain.drs");
  
  sf::RenderWindow App(sf::VideoMode(800, 600, 32), "SFML Graphics");

  uint32_t slp_id = 15001;//1057 ;

  
  sf::Texture text, text2;
    
  genie::SlpFilePtr slpf = drs.getSlpFile(slp_id);
  drs.getSlpFile(slp_id);
    
  text.LoadFromImage(createSfImage(slpf->getFrame(1), pal));
  text2.LoadFromImage(createSfImage(slpf->getFrame(1), pal));
  
  
  sf::Sprite Sprite(text);
  sf::Sprite Sprite2(text2);

  Sprite.SetPosition(0, 0);
  Sprite2.SetPosition(100,50);

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
      App.Draw(Sprite2);

      // Display window contents on screen
      App.Display();
  }
}

void testScn()
{
  genie::ScnFile scn;
  
//   scn.extractRaw("small_crater_lake.scx", "raw.scx");
  scn.extractRaw("test2.scx", "raw.scx");
   
//   scn.load("small_crater_lake.scx");
  scn.load("test2.scx");
  
  std::cout << "Original filename: " << scn.originalFileName << std::endl;
  
  std::cout << scn.scenarioInstructions << std::endl;
  std::cout << scn.resource.instructions << std::endl;
  std::cout << scn.resource.scouts << std::endl;
  std::cout << scn.resource.bitmapIncluded << std::endl;
  
//   scn.saveAs("xxxx.scx");
  
//   genie::ScnFile scn2;
//   scn2.load("xxxx.scx");
  
  
//   std::cout << "Original filename: " << scn2.originalFileName << std::endl;
  
}

int main(int argc, char **argv) {

  genie::Logger::setLogLevel(genie::Logger::L_INFO);
  
//   testDrs();
  
  testScn();
  
  /*
  std::ifstream ifs;
  std::ofstream ofs;
  
  ifs.open("tmp/empires2.dat", std::ios::binary);
  ofs.open("q.dat", std::ios::binary);
 
  genie::Compressor c;
  
  boost::shared_ptr<std::istream> unc = c.startDecompression(&ifs);
  
  boost::iostreams::copy((*unc), ofs);
  
  c.stopDecompression();
  
//   delete unc;
  
  ifs.close();
  ofs.close();
   */
  return 0;
}
