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


#include "genie/dat/Unit.h"


namespace genie
{
 
//------------------------------------------------------------------------------
Unit::Unit() 
{
//    Type 10+

  Type = UT_EyeCandy;
  NameLength = 9;
  ID1 = -1;
  LanguageDllName = 5000;
  LanguageDllCreation = 6000;
  Class = -1;
  StandingGraphic.first = -1;
  StandingGraphic.second = -1;
  DyingGraphic.first = -1;
  DyingGraphic.second = -1;
  DeathMode = 0;
  HitPoints = 1;
  LineOfSight = 2;
  GarrisonCapacity = 0;
  SizeRadius.first = 0;
  SizeRadius.second = 0;
  HPBarHeight1 = 0;
  TrainSound.first = -1;
  TrainSound.second = -1;
  DeadUnitID = -1;
  PlacementMode = 0;
  AirMode = 0;
  IconID = -1;
  HideInEditor = 0;
  Unknown1 = -1;
  Enabled = 0;
  PlacementBypassTerrain.first = -1;
  PlacementBypassTerrain.second = -1;
  PlacementTerrain.first = -1;
  PlacementTerrain.second = -1;
  EditorRadius.first = 0;
  EditorRadius.second = 0;
  BuildingMode = 0;
  VisibleInFog = 0;
  TerrainRestriction = 0;
  FlyMode = 0;
  ResourceCapacity = 0;
  ResourceDecay = 0;
  BlastType = 0;
  Unknown2 = 0;
  InteractionMode = 0;
  MinimapMode = 0;
  CommandAttribute = 0;
  Unknown3 = 0;
  Unknown3B = 0;
  Unknown3a = 0;
  LanguageDllHelp = 39000;
  Unknown4 = 0;
  Unknown5 = 0;
  Unselectable = 0;
  Unknown6 = 0;
  Unknown7 = 0;
  Unknown8 = 0;
  SelectionMask = 0;
  SelectionShapeType = 0;
  SelectionShape = 0;
  Attribute = 0;
  Civilization = 0;
  SelectionEffect = 1;
  EditorSelectionColour = 52;
  SelectionRadius.first = 0;
  SelectionRadius.second = 0;
  HPBarHeight2 = 0;
  ResourceStorages.resize(RESOURCE_STORAGE_CNT);
  SelectionSound = -1;
  DyingSound = -1;
  AttackSound = -1;
  Name = "";
  NameLength2 = 9;
  Name2 = "";
  Unitline = -1;
  MinTechLevel = -1;
  ID2 = -1;
  ID3 = -1;

//  Type 20+

  Speed = 1;
}

//------------------------------------------------------------------------------
Unit::~Unit()
{
}

//------------------------------------------------------------------------------
short Unit::getHotKeySize()
{
  return 4;
}

//------------------------------------------------------------------------------
short Unit::getUnknown9Size()
{
  return 2;
}

//------------------------------------------------------------------------------
void Unit::serializeObject(void )
{
  //Type 10+
  serialize<char>(Type);
  
  serializeSize<unsigned short>(NameLength, Name);
  serialize<short>(ID1);        //TODO: Check
  serialize<unsigned short>(LanguageDllName);
  serialize<unsigned short>(LanguageDllCreation);
  serialize<short>(Class);
  
  if (getGameVersion() >= genie::GV_AoK)
    serialize<short>(StandingGraphic);
  else
    serialize<short>(StandingGraphic, true);
  
  serialize<short>(DyingGraphic);
  serialize<char>(DeathMode);
  serialize<short>(HitPoints);
  serialize<float>(LineOfSight);
  serialize<char>(GarrisonCapacity); 
  serialize<float>(SizeRadius);
  
  serialize<float>(HPBarHeight1);
  
  serialize<short>(TrainSound, (getGameVersion() >= genie::GV_AoK) ? false : true);
  serialize<short>(DeadUnitID);
  serialize<char>(PlacementMode);
  serialize<char>(AirMode);
  serialize<short>(IconID);
  serialize<char>(HideInEditor);
  serialize<short>(Unknown1);
  
  if (getGameVersion() >= genie::GV_AoK)
    serialize<short>(Enabled);
  else
  {
    char enabled = Enabled;
    serialize<char>(enabled);
    Enabled = enabled;
  }
  
  serialize<short>(PlacementBypassTerrain);
  serialize<short>(PlacementTerrain);
  serialize<float>(EditorRadius);
  serialize<char>(BuildingMode);
  serialize<char>(VisibleInFog);
  serialize<short>(TerrainRestriction);
  serialize<char>(FlyMode);
  serialize<short>(ResourceCapacity);
  serialize<float>(ResourceDecay);
  serialize<char>(BlastType); //TODO: AoE/ROR: [0]:blast_type?
  serialize<char>(Unknown2);
  serialize<char>(InteractionMode);
  serialize<char>(MinimapMode);
  
  if (getGameVersion() >= genie::GV_AoK)// || getGameVersion() == genie::GV_TC)
    serialize<short>(CommandAttribute);
  else
  {
    char attr = CommandAttribute;
    serialize<char>(attr);
    CommandAttribute = attr;
  }
  
  serialize<short>(Unknown3);
  serialize<short>(Unknown3B);
  
  if (getGameVersion() <= genie::GV_RoR)
    serialize<char>(Unknown3a);
  
  serialize<unsigned short>(LanguageDllHelp);
  serialize<short>(HotKey, getHotKeySize());
  serialize<char>(Unknown4);
  serialize<char>(Unknown5);
  serialize<bool>(Unselectable);
  serialize<char>(Unknown6);
  
  if (getGameVersion() >= genie::GV_AoK)
  {
    serialize<char>(Unknown7);
    serialize<char>(Unknown8);
  }
  
  serialize<char>(SelectionMask);
  
  if (getGameVersion() >= genie::GV_AoK)
    serialize<char>(SelectionShapeType);
  
  serialize<char>(SelectionShape);
  //AoE/RoR: [0] unit_attribute
  if (getGameVersion() != genie::GV_AoK)
  {
    serialize<char>(Attribute);
    serialize<char>(Civilization); // TODO: selection color in AoE/RoR?
  }

  if (getGameVersion() >= genie::GV_TC)
    serialize<char>(Unknown9, getUnknown9Size());
  
  
  if (getGameVersion() >= genie::GV_AoK)
  {
    serialize<char>(SelectionEffect);
    serialize<char>(EditorSelectionColour);
  }
  
  serialize<float>(SelectionRadius);
  serialize<float>(HPBarHeight2);
  
  serializeSub<ResourceStorage>(ResourceStorages, 3);
  
  serializeSize<unsigned char>(DamageGraphicCount, DamageGraphics.size());
  serializeSub<unit::DamageGraphic>(DamageGraphics, DamageGraphicCount);
  
  serialize<short>(SelectionSound);
  serialize<short>(DyingSound);
  serialize<short>(AttackSound);
  
  serialize<std::string>(Name, NameLength);
  
  if (getGameVersion() >= genie::GV_SWGB)
  {
    //serializeSize<unsigned short>(NameLength2, Name2.size());
    serializeSize<unsigned short>(NameLength2, Name2);
    serialize<std::string>(Name2, NameLength2);
    
    serialize<short>(Unitline);
    serialize<char>(MinTechLevel);
  }
  
  serialize<short>(ID2);
    
  if (getGameVersion() >= genie::GV_AoK)
    serialize<short>(ID3);
  
  if (Type == genie::UT_AoeTrees)
    return;
   
  if (Type >= genie::UT_Flag)
    serialize<float>(Speed);
  else
    return;
  
  if (Type >= genie::UT_Dead_Fish)
    serialize<ISerializable>(DeadFish);
  
  if (Type >= genie::UT_Bird)
    serialize<ISerializable>(Bird);
  
  if (Type >= genie::UT_Projectile)
    serialize<ISerializable>(Projectile);
  
  if (Type == genie::UT_Projectile)
    serialize<ISerializable>(ProjectileOnly);
  
  if (Type >= genie::UT_Creatable)
    serialize<ISerializable>(Creatable);
  
  if (Type >= genie::UT_Building)
    serialize<ISerializable>(Building);
}

  
}

