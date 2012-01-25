/*
    geniedat - A library for reading and writing data files of genie
               engine games.
    Copyright (C) 2011  Armin Preiml <email>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


#ifndef TECHTREE_H
#define TECHTREE_H
#include "genie/file/ISerializable.h"

namespace genie
{

class TechTreeAge;
class BuildingConnection;
class UnitConnection;
class ResearchConnection;

class TechTree : public ISerializable
{

public:
  TechTree();
  virtual ~TechTree();
  
  virtual void serializeObject(void);
  
  std::vector<TechTreeAge> TechTreeAges;
  
  long Unknown2; //1
  
  std::vector<BuildingConnection> BuildingConnections;
  
  std::vector<UnitConnection> UnitConnections;
  
  std::vector<ResearchConnection> ResearchConnections;
  
private:
  unsigned char age_count_;
  unsigned char total_building_count_;
  unsigned short total_unit_count_; // short in >= swgb
  unsigned char total_research_count_;
  
};

/// Contains all items of an age in techtree
class TechTreeAge : public ISerializable
{
public:
  TechTreeAge();
  virtual ~TechTreeAge();
  
  virtual void serializeObject(void);
  
  long Unknown1;
  long ID; //Age ID?
  char Unknown2; //Always 2
  
  std::vector<long> Buildings;
  std::vector<long> Units;
  std::vector<long> Researches;
  
  long Unknown3; //Always 1
  long Unknown4; //Second Age ID?
  
  unsigned short getZeroesSize(); 
  
  std::vector<short> Zeroes;
private:
  unsigned char building_count_;
  unsigned char unit_count_;
  unsigned char research_count_;
};

class BuildingConnection : public ISerializable
{
public:
  BuildingConnection();
  virtual ~BuildingConnection();
  
  virtual void serializeObject(void);
  
  long ID;
  char Unknown1; //always 2
  
  std::vector<long> Buildings;
  
  std::vector<long> Units;

  std::vector<long> Researches;

  /// Minimum amount of researches that need to be researched for this to be available.
  long RequiredResearches;
  long Age;
  long UnitOrResearch1;
  long UnitOrResearch2;
  
  unsigned int getUnknown2aSize();
  std::vector<long> Unknown2a;
  
  /// 0 Nothing, 1 Building, 2 Unit, 3 Research.
  long Mode1;
  long Mode2;
  
  unsigned int getUnknown2bSize();
  std::vector<long> Unknown2b;
  
  const unsigned int getUnknown3Size() { return 11; }
  std::vector<char> Unknown3;
  
  /// 5 One or more connections, 6 No connections.
  long Connections;
  /// Makes available. Used by buildings, which need a research to be available.
  long EnablingResearch;
  
private:
  
  unsigned char building_count_;
  unsigned char unit_count_;
  unsigned char research_count_;
};

class UnitConnection : public ISerializable
{
public:
  UnitConnection();
  virtual ~UnitConnection();
  
  virtual void serializeObject(void);
  
  long ID;
  char Unknown1; //always 2
  long UpperBuilding;

  /// Minimum amount of researches that need to be researched for this to be available.
  long RequiredResearches;
  long Age;
  long UnitOrResearch1; // unit or research
  long UnitOrResearch2; // unit or research
  
  unsigned int getUnknown2aSize();
  std::vector<long> Unknown2a;
  
  /// 0 Nothing, 1 Building, 2 Unit, 3 Research.
  long Mode1;
  long Mode2;
  
  unsigned int getUnknown2bSize();
  std::vector<long> Unknown2b;
  
  long VerticalLine;
  
  //char *connected unit count*
  std::vector<long> Units;
  
  /// 1 First, 2 Second.
  long LocationInAge;
  /// Upgrades unit. Used by units, which aren't first in upgrade line.
  long RequiredResearch;
  /// 2 First in vertical line. 3 Not first.
  long LineMode;
  /// Makes available. Used by units, which need a research to be available.
  long EnablingResearch;
  
private:
  unsigned char unit_count_;
  
};

class ResearchConnection : public ISerializable
{
public:
  ResearchConnection();
  virtual ~ResearchConnection();
  
  virtual void serializeObject(void);
  
  long ID;
  char Unknown1; //always 2
  long UpperBuilding;
  
  std::vector<long> Buildings;
  
  std::vector<long> Units;

  std::vector<long> Researches;

  /// Minimum amount of researches that need to be researched for this to be available.
  long RequiredResearches;
  long Age;
  long UpperResearch;
  
  unsigned int getUnknown2aSize();
  std::vector<long> Unknown2a;
  
  /// 0 Independent/new in its line. 3 Depends on a previous research in its line.
  long LineMode;
  
  unsigned int getUnknown2bSize();
  std::vector<long> Unknown2b;
  
  long VerticalLine;
  /// 0 Hidden, 1 First, 2 Second.
  long LocationInAge;
  /// 0 First Age. Others.
  long Unknown9;
 
private:
  unsigned char building_count_;
  unsigned char unit_count_;
  unsigned char research_count_;
};

}

#endif // TECHTREE_H
