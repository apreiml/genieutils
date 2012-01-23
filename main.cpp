#include <iostream>
#include <genie/file/ICompressedFile.h>

class TestFile : public genie::IFile
{
public:
  TestFile() : test(0xEFBE) {}
  
  short test;
protected:
  virtual void serializeObject(void )
  {
    serialize<short>(test);
  }
};


int main(int argc, char **argv) {
    std::cout << "Hello, world!" << std::endl;
    
    TestFile file;
    
    try
    {
    
    file.load("asdf.test");    
    file.saveAs("xx");
    }
    catch (std::ios_base::failure e)
    {
      std::cout << e.what() << std::endl;
    }
    
    return 0;
}
