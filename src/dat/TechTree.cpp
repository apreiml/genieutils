/*
    genie/dat - A library for reading and writing data files of genie
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


#include "genie/dat/TechTree.h"

namespace genie
{

//------------------------------------------------------------------------------
TechTree::TechTree()
{
  Unknown2 = -1;
}

//------------------------------------------------------------------------------
TechTree::~TechTree()
{
}

//------------------------------------------------------------------------------
void TechTree::serializeObject(void )
{
  serializeSize<unsigned char>(age_count_, TechTreeAges.size());
  
  serializeSize<unsigned char>(total_building_count_, BuildingConnections.size());
  
  if (getGameVersion() >= genie::GV_SWGB)
   serializeSize<unsigned short>(total_unit_count_, UnitConnections.size());
  else
  {
    unsigned char tbc = total_unit_count_;
    serializeSize<unsigned char>(tbc, UnitConnections.size());
    total_unit_count_ = tbc;
  }
  
  serializeSize<unsigned char>(total_research_count_, ResearchConnections.size());
  
  serializeSub<TechTreeAge>(TechTreeAges, age_count_);
  
  serialize<long>(Unknown2);
  
  serializeSub<BuildingConnection>(BuildingConnections, total_building_count_);
  serializeSub<UnitConnection>(UnitConnections, total_unit_count_);
  serializeSub<ResearchConnection>(ResearchConnections, total_research_count_);
}

//------------------------------------------------------------------------------
TechTreeAge::TechTreeAge()
{
  Unknown1 = 0;
  ID = 0;
  Unknown2 = 2;
  Unknown3 = 0;
  Unknown4 = 0;
}

//------------------------------------------------------------------------------
TechTreeAge::~TechTreeAge()
{
}

//------------------------------------------------------------------------------
unsigned short TechTreeAge::getZeroesSize() 
{
  if (getGameVersion() >= genie::GV_AoK)
  {
    if (getGameVersion() >= genie::GV_SWGB)
      return 99;
    else
      return 49;
  }
  else
    return 0;
}


//------------------------------------------------------------------------------
void TechTreeAge::serializeObject(void )
{
  serialize<long>(Unknown1);
  serialize<long>(ID);
  serialize<char>(Unknown2);
  
  serializeSize<unsigned char>(building_count_, Buildings.size());
  serialize<long>(Buildings, building_count_);
  
  serializeSize<unsigned char>(unit_count_, Units.size());
  serialize<long>(Units, unit_count_);
  
  serializeSize<unsigned char>(research_count_, Researches.size());
  serialize<long>(Researches, research_count_);
  
  serialize<long>(Unknown3);
  serialize<long>(Unknown4);
  
  serialize<short>(Zeroes, getZeroesSize());
} 

//------------------------------------------------------------------------------
BuildingConnection::BuildingConnection()
{
  ID = 0;
  Unknown1 = 2;
  RequiredResearches = 0;
  Age = 0;
  UnitOrResearch1 = 0;
  UnitOrResearch2 = 0;
  Mode1 = 0;
  Mode2 = 0;
  Connections = 0;
  EnablingResearch = -1;
}

//------------------------------------------------------------------------------
BuildingConnection::~BuildingConnection()
{
}

//------------------------------------------------------------------------------
unsigned int BuildingConnection::getUnknown2aSize()
{
  if (getGameVersion() >= genie::GV_SWGB)
    return 18;
  else
    return 8;  
}

//------------------------------------------------------------------------------
unsigned int BuildingConnection::getUnknown2bSize()
{
  if (getGameVersion() >= genie::GV_SWGB)
    return 17;
  else
    return 7;  
}

//------------------------------------------------------------------------------
void BuildingConnection::serializeObject(void)
{
  serialize<long>(ID);
  serialize<char>(Unknown1);
  
  serializeSize<unsigned char>(building_count_, Buildings.size());
  serialize<long>(Buildings, building_count_);
  
  serializeSize<unsigned char>(unit_count_, Units.size());
  serialize<long>(Units, unit_count_);
  
  serializeSize<unsigned char>(research_count_, Researches.size());
  serialize<long>(Researches, research_count_);
  
  serialize<long>(RequiredResearches);
  serialize<long>(Age);
  serialize<long>(UnitOrResearch1);
  serialize<long>(UnitOrResearch2);
  
  serialize<long>(Unknown2a, getUnknown2aSize());
  
  serialize<long>(Mode1);
  serialize<long>(Mode2);
  
  serialize<long>(Unknown2b, getUnknown2bSize());
  
  serialize<char>(Unknown3, getUnknown3Size());
  
  serialize<long>(Connections);
  serialize<long>(EnablingResearch); 
}

//------------------------------------------------------------------------------
UnitConnection::UnitConnection() 
{
  ID = 0;
  Unknown1 = 2;
  UpperBuilding = -1;
  RequiredResearches = 0;
  Age = 0;
  UnitOrResearch1 = 0;
  UnitOrResearch2 = 0;
  Mode1 = 0;
  Mode2 = 0;
  VerticalLine = 0;
  LocationInAge = 0;
  RequiredResearch = -1;
  LineMode = 0;
  EnablingResearch = -1;
}

//------------------------------------------------------------------------------
UnitConnection::~UnitConnection()
{
}

//------------------------------------------------------------------------------
unsigned int UnitConnection::getUnknown2aSize()
{
  if (getGameVersion() >= genie::GV_SWGB)
    return 18;
  else
    return 8;
}

//------------------------------------------------------------------------------
unsigned int UnitConnection::getUnknown2bSize()
{
  if (getGameVersion() >= genie::GV_SWGB)
    return 17;
  else
    return 7;
}

//------------------------------------------------------------------------------
void UnitConnection::serializeObject(void)
{
  serialize<long>(ID);
  serialize<char>(Unknown1);
  serialize<long>(UpperBuilding);
  serialize<long>(RequiredResearches);
  serialize<long>(Age);
  serialize<long>(UnitOrResearch1);
  serialize<long>(UnitOrResearch2);

  serialize<long>(Unknown2a, getUnknown2aSize());
  
  serialize<long>(Mode1);
  serialize<long>(Mode2);
  
  serialize<long>(Unknown2b, getUnknown2bSize());
  
  serialize<long>(VerticalLine);
  
  serializeSize<unsigned char>(unit_count_, Units.size());
  serialize<long>(Units, unit_count_);
  
  serialize<long>(LocationInAge);
  serialize<long>(RequiredResearch);
  serialize<long>(LineMode);
  
  serialize<long>(EnablingResearch);  
}

//------------------------------------------------------------------------------
ResearchConnection::ResearchConnection()
{
  ID = 0;
  Unknown1 = 2;
  UpperBuilding = -1;
  RequiredResearches = 0;
  Age = 0;
  UpperResearch = -1;
  LineMode = 0;
  VerticalLine = 0;
  LocationInAge = 0;
  Unknown9 = 0;
}

//------------------------------------------------------------------------------
ResearchConnection::~ResearchConnection()
{
}

//------------------------------------------------------------------------------
unsigned int ResearchConnection::getUnknown2aSize()
{
  if (getGameVersion() >= genie::GV_SWGB)
    return 19;
  else
    return 9;
}

//------------------------------------------------------------------------------
unsigned int ResearchConnection::getUnknown2bSize()
{
  if (getGameVersion() >= genie::GV_SWGB)
    return 18;
  else
    return 8;
}

//------------------------------------------------------------------------------
void ResearchConnection::serializeObject(void)
{
  serialize<long>(ID);
  serialize<char>(Unknown1);
  serialize<long>(UpperBuilding);
  
  serializeSize<unsigned char>(building_count_, Buildings.size());
  serialize<long>(Buildings, building_count_);
  
  serializeSize<unsigned char>(unit_count_, Units.size());
  serialize<long>(Units, unit_count_);
  
  serializeSize<unsigned char>(research_count_, Researches.size());
  serialize<long>(Researches, research_count_);
  
  serialize<long>(RequiredResearches);
  serialize<long>(Age);
  serialize<long>(UpperResearch);
  
  serialize<long>(Unknown2a, getUnknown2aSize());
  
  serialize<long>(LineMode);
  
  serialize<long>(Unknown2b, getUnknown2bSize());
  
  serialize<long>(VerticalLine);
  serialize<long>(LocationInAge);
  serialize<long>(Unknown9);
}

}
