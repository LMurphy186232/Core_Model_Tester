//---------------------------------------------------------------------------
// TestPRStormBiLevelGrowth.cpp
//---------------------------------------------------------------------------
#include "TestPRStormBiLevelGrowth.h"
#include <gtest/gtest.h>
#include <fstream>
#include <math.h>
#include "TreePopulation.h"
#include "SimManager.h"
#include "BehaviorBase.h"
#include "Grid.h"

////////////////////////////////////////////////////////////////////////////
// NormalProcessingRun1()
// Tests normal processing run 1. WritePRStormBiLevelGrowthXMLFile1() does
// setup. Timestep length is 1 year. The growth used is diam with auto height.
// 27 trees are created of 3 species and assigned to a mix of light levels and
// time-since-last-storm. Then growth is run. Tree diameters and heights are
// checked to make sure they are correct.
////////////////////////////////////////////////////////////////////////////
TEST(PRStormBiLevelGrowth, NormalProcessingRun1) {
  clTreePopulation * p_oPop;
  clGrid *p_oStormLight, *p_oStorm;
  clTree **p_oTrees = new clTree*[27];
  float fDiam, fHeight, fExpectedDiam, fExpectedHeight;
  int iIndex, iSpecies, iType;

  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    //Load our test file and get our tree population and grid pointers
    p_oSimManager->ReadFile( WritePRStormBiLevelGrowthXMLFile1() );
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );
    p_oStormLight = p_oSimManager->GetGridObject("Storm Light");
    p_oStorm = p_oSimManager->GetGridObject("Storm Damage");

    //Set our grid values
    fDiam = 15;
    p_oStormLight->SetValueOfCell(0, 0, p_oStormLight->GetFloatDataCode("Light"), fDiam);
    fDiam = 35;
    p_oStormLight->SetValueOfCell(0, 1, p_oStormLight->GetFloatDataCode("Light"), fDiam);
    fDiam = 80;
    p_oStormLight->SetValueOfCell(0, 2, p_oStormLight->GetFloatDataCode("Light"), fDiam);

    fDiam = 1;
    p_oStorm->SetValueOfCell(0, 0, p_oStorm->GetFloatDataCode("stormtime"), fDiam);
    fDiam = 0;
    p_oStorm->SetValueOfCell(0, 1, p_oStorm->GetFloatDataCode("stormtime"), fDiam);
    fDiam = 2;
    p_oStorm->SetValueOfCell(0, 2, p_oStorm->GetFloatDataCode("stormtime"), fDiam);

    //Create our trees
    iIndex = 0;

    fDiam = 0.1;
    iSpecies = 0;
    iType = clTreePopulation::seedling;
    p_oTrees[iIndex] = p_oPop->CreateTree(1, 1, iSpecies, iType, fDiam);
    iIndex++;

    fDiam = 0.2;
    iSpecies = 1;
    iType = clTreePopulation::seedling;
    p_oTrees[iIndex] = p_oPop->CreateTree(1, 1, iSpecies, iType, fDiam);
    iIndex++;

    fDiam = 0.3;
    iSpecies = 3;
    iType = clTreePopulation::seedling;
    p_oTrees[iIndex] = p_oPop->CreateTree(1, 1, iSpecies, iType, fDiam);
    iIndex++;

    fDiam = 2.5;
    iSpecies = 0;
    iType = clTreePopulation::sapling;
    p_oTrees[iIndex] = p_oPop->CreateTree(1, 1, iSpecies, iType, fDiam);
    iIndex++;

    fDiam = 3.4;
    iSpecies = 1;
    iType = clTreePopulation::sapling;
    p_oTrees[iIndex] = p_oPop->CreateTree(1, 1, iSpecies, iType, fDiam);
    iIndex++;

    fDiam = 5.4;
    iSpecies = 3;
    iType = clTreePopulation::sapling;
    p_oTrees[iIndex] = p_oPop->CreateTree(1, 1, iSpecies, iType, fDiam);
    iIndex++;

    fDiam = 12.6;
    iSpecies = 0;
    iType = clTreePopulation::adult;
    p_oTrees[iIndex] = p_oPop->CreateTree(1, 1, iSpecies, iType, fDiam);
    iIndex++;

    fDiam = 45.2;
    iSpecies = 1;
    iType = clTreePopulation::adult;
    p_oTrees[iIndex] = p_oPop->CreateTree(1, 1, iSpecies, iType, fDiam);
    iIndex++;

    fDiam = 23.3;
    iSpecies = 3;
    iType = clTreePopulation::adult;
    p_oTrees[iIndex] = p_oPop->CreateTree(1, 1, iSpecies, iType, fDiam);
    iIndex++;

    fDiam = 0.1;
    iSpecies = 0;
    iType = clTreePopulation::seedling;
    p_oTrees[iIndex] = p_oPop->CreateTree(1, 9, iSpecies, iType, fDiam);
    iIndex++;

    fDiam = 0.2;
    iSpecies = 1;
    iType = clTreePopulation::seedling;
    p_oTrees[iIndex] = p_oPop->CreateTree(1, 9, iSpecies, iType, fDiam);
    iIndex++;

    fDiam = 0.3;
    iSpecies = 3;
    iType = clTreePopulation::seedling;
    p_oTrees[iIndex] = p_oPop->CreateTree(1, 9, iSpecies, iType, fDiam);
    iIndex++;

    fDiam = 2.5;
    iSpecies = 0;
    iType = clTreePopulation::sapling;
    p_oTrees[iIndex] = p_oPop->CreateTree(1, 9, iSpecies, iType, fDiam);
    iIndex++;

    fDiam = 3.4;
    iSpecies = 1;
    iType = clTreePopulation::sapling;
    p_oTrees[iIndex] = p_oPop->CreateTree(1, 9, iSpecies, iType, fDiam);
    iIndex++;

    fDiam = 5.4;
    iSpecies = 3;
    iType = clTreePopulation::sapling;
    p_oTrees[iIndex] = p_oPop->CreateTree(1, 9, iSpecies, iType, fDiam);
    iIndex++;

    fDiam = 12.6;
    iSpecies = 0;
    iType = clTreePopulation::adult;
    p_oTrees[iIndex] = p_oPop->CreateTree(1, 9, iSpecies, iType, fDiam);
    iIndex++;

    fDiam = 45.2;
    iSpecies = 1;
    iType = clTreePopulation::adult;
    p_oTrees[iIndex] = p_oPop->CreateTree(1, 9, iSpecies, iType, fDiam);
    iIndex++;

    fDiam = 23.3;
    iSpecies = 3;
    iType = clTreePopulation::adult;
    p_oTrees[iIndex] = p_oPop->CreateTree(1, 9, iSpecies, iType, fDiam);
    iIndex++;

    fDiam = 0.1;
    iSpecies = 0;
    iType = clTreePopulation::seedling;
    p_oTrees[iIndex] = p_oPop->CreateTree(1, 17, iSpecies, iType, fDiam);
    iIndex++;

    fDiam = 0.2;
    iSpecies = 1;
    iType = clTreePopulation::seedling;
    p_oTrees[iIndex] = p_oPop->CreateTree(1, 17, iSpecies, iType, fDiam);
    iIndex++;

    fDiam = 0.3;
    iSpecies = 3;
    iType = clTreePopulation::seedling;
    p_oTrees[iIndex] = p_oPop->CreateTree(1, 17, iSpecies, iType, fDiam);
    iIndex++;

    fDiam = 2.5;
    iSpecies = 0;
    iType = clTreePopulation::sapling;
    p_oTrees[iIndex] = p_oPop->CreateTree(1, 17, iSpecies, iType, fDiam);
    iIndex++;

    fDiam = 3.4;
    iSpecies = 1;
    iType = clTreePopulation::sapling;
    p_oTrees[iIndex] = p_oPop->CreateTree(1, 17, iSpecies, iType, fDiam);
    iIndex++;

    fDiam = 5.4;
    iSpecies = 3;
    iType = clTreePopulation::sapling;
    p_oTrees[iIndex] = p_oPop->CreateTree(1, 17, iSpecies, iType, fDiam);
    iIndex++;

    fDiam = 12.6;
    iSpecies = 0;
    iType = clTreePopulation::adult;
    p_oTrees[iIndex] = p_oPop->CreateTree(1, 17, iSpecies, iType, fDiam);
    iIndex++;

    fDiam = 45.2;
    iSpecies = 1;
    iType = clTreePopulation::adult;
    p_oTrees[iIndex] = p_oPop->CreateTree(1, 17, iSpecies, iType, fDiam);
    iIndex++;

    fDiam = 23.3;
    iSpecies = 3;
    iType = clTreePopulation::adult;
    p_oTrees[iIndex] = p_oPop->CreateTree(1, 17, iSpecies, iType, fDiam);
    iIndex++;

    //Now run growth, but skip storms and storm light
    int i;
    for (i = 0; i < p_oSimManager->GetNumberOfBehaviors(); i++) {
      clBehaviorBase *p_oBase = p_oSimManager->GetBehaviorObject(i);
      if (p_oBase->GetName().compare("StormLight") != 0 &&
          p_oBase->GetName().compare("Storm") != 0)
        p_oBase->Action();
    }

    //Confirm all trees
    //#1
    iIndex = 0;
    fExpectedDiam = 0.201;
    fExpectedHeight = 0.19373548;
    EXPECT_EQ(clTreePopulation::seedling, p_oTrees[iIndex]->GetType());
    p_oTrees[iIndex]->GetValue(p_oPop->GetDiam10Code(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fDiam);
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    //#2
    fExpectedDiam = 0.206;
    fExpectedHeight = 0.1853382;
    EXPECT_EQ(clTreePopulation::seedling, p_oTrees[iIndex]->GetType());
    p_oTrees[iIndex]->GetValue(p_oPop->GetDiam10Code(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fDiam);
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    //#3
    fExpectedDiam = 0.5072;
    fExpectedHeight = 1.9562704;
    EXPECT_EQ(clTreePopulation::seedling, p_oTrees[iIndex]->GetType());
    p_oTrees[iIndex]->GetValue(p_oPop->GetDiam10Code(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fDiam);
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    //#4
    fExpectedDiam = 2.61008;
    fExpectedHeight = 4.2101;
    EXPECT_EQ(clTreePopulation::sapling, p_oTrees[iIndex]->GetType());
    p_oTrees[iIndex]->GetValue(p_oPop->GetDbhCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fDiam);
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    //#5
    fExpectedDiam = 3.502;
    fExpectedHeight = 5.474285714;
    EXPECT_EQ(clTreePopulation::sapling, p_oTrees[iIndex]->GetType());
    p_oTrees[iIndex]->GetValue(p_oPop->GetDbhCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fDiam);
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    //#6
    fExpectedDiam = 5.67078;
    fExpectedHeight = 9.089633333;
    EXPECT_EQ(clTreePopulation::sapling, p_oTrees[iIndex]->GetType());
    p_oTrees[iIndex]->GetValue(p_oPop->GetDbhCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fDiam);
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    //#7
    fExpectedDiam = 12.8512;
    fExpectedHeight = 13.5149736;
    EXPECT_EQ(clTreePopulation::adult, p_oTrees[iIndex]->GetType());
    p_oTrees[iIndex]->GetValue(p_oPop->GetDbhCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fDiam);
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    //#8
    fExpectedDiam = 46.556;
    fExpectedHeight = 27.10426602;
    EXPECT_EQ(clTreePopulation::adult, p_oTrees[iIndex]->GetType());
    p_oTrees[iIndex]->GetValue(p_oPop->GetDbhCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fDiam);
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    //#9
    fExpectedDiam = 24.0592;
    fExpectedHeight = 19.47199985;
    EXPECT_EQ(clTreePopulation::adult, p_oTrees[iIndex]->GetType());
    p_oTrees[iIndex]->GetValue(p_oPop->GetDbhCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fDiam);
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    //#10
    fExpectedDiam = 0.242278534;
    fExpectedHeight = 0.23329;
    EXPECT_EQ(clTreePopulation::seedling, p_oTrees[iIndex]->GetType());
    p_oTrees[iIndex]->GetValue(p_oPop->GetDiam10Code(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fDiam);
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    //#11
    fExpectedDiam = 0.206;
    fExpectedHeight = 0.1853382;
    EXPECT_EQ(clTreePopulation::seedling, p_oTrees[iIndex]->GetType());
    p_oTrees[iIndex]->GetValue(p_oPop->GetDiam10Code(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fDiam);
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    //#12
    fExpectedDiam = 0.5072;
    fExpectedHeight = 1.9562704;
    EXPECT_EQ(clTreePopulation::seedling, p_oTrees[iIndex]->GetType());
    p_oTrees[iIndex]->GetValue(p_oPop->GetDiam10Code(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fDiam);
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    //#13
    fExpectedDiam = 5.921578422;
    fExpectedHeight = 8.349473027;
    EXPECT_EQ(clTreePopulation::sapling, p_oTrees[iIndex]->GetType());
    p_oTrees[iIndex]->GetValue(p_oPop->GetDbhCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fDiam);
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    //#14
    fExpectedDiam = 3.502;
    fExpectedHeight = 5.474285714;
    EXPECT_EQ(clTreePopulation::sapling, p_oTrees[iIndex]->GetType());
    p_oTrees[iIndex]->GetValue(p_oPop->GetDbhCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fDiam);
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    //#15
    fExpectedDiam = 5.67078;
    fExpectedHeight = 9.089633333;
    EXPECT_EQ(clTreePopulation::sapling, p_oTrees[iIndex]->GetType());
    p_oTrees[iIndex]->GetValue(p_oPop->GetDbhCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fDiam);
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    //#16
    fExpectedDiam = 48.66512018;
    fExpectedHeight = 30.58121918;
    EXPECT_EQ(clTreePopulation::adult, p_oTrees[iIndex]->GetType());
    p_oTrees[iIndex]->GetValue(p_oPop->GetDbhCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fDiam);
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    //#17
    fExpectedDiam = 46.556;
    fExpectedHeight = 27.10426602;
    EXPECT_EQ(clTreePopulation::adult, p_oTrees[iIndex]->GetType());
    p_oTrees[iIndex]->GetValue(p_oPop->GetDbhCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fDiam);
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    //#18
    fExpectedDiam = 24.0592;
    fExpectedHeight = 19.47199985;
    EXPECT_EQ(clTreePopulation::adult, p_oTrees[iIndex]->GetType());
    p_oTrees[iIndex]->GetValue(p_oPop->GetDbhCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fDiam);
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    //#19
    fExpectedDiam = 0.118133964;
    fExpectedHeight = 0.113751194;
    EXPECT_EQ(clTreePopulation::seedling, p_oTrees[iIndex]->GetType());
    p_oTrees[iIndex]->GetValue(p_oPop->GetDiam10Code(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fDiam);
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    //#20
    fExpectedDiam = 0.201149554;
    fExpectedHeight = 0.180974254;
    EXPECT_EQ(clTreePopulation::seedling, p_oTrees[iIndex]->GetType());
    p_oTrees[iIndex]->GetValue(p_oPop->GetDiam10Code(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fDiam);
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    //#21
    fExpectedDiam = 0.30902565;
    fExpectedHeight = 1.191911931;
    EXPECT_EQ(clTreePopulation::seedling, p_oTrees[iIndex]->GetType());
    p_oTrees[iIndex]->GetValue(p_oPop->GetDiam10Code(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fDiam);
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedDiam = 2.936093753;
    fExpectedHeight = 4.617617191;
    EXPECT_EQ(clTreePopulation::sapling, p_oTrees[iIndex]->GetType());
    p_oTrees[iIndex]->GetValue(p_oPop->GetDbhCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fDiam);
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedDiam = 3.420705955;
    fExpectedHeight = 5.358151365;
    EXPECT_EQ(clTreePopulation::sapling, p_oTrees[iIndex]->GetType());
    p_oTrees[iIndex]->GetValue(p_oPop->GetDbhCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fDiam);
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedDiam = 5.932609228;
    fExpectedHeight = 9.52601538;
    EXPECT_EQ(clTreePopulation::sapling, p_oTrees[iIndex]->GetType());
    p_oTrees[iIndex]->GetValue(p_oPop->GetDbhCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fDiam);
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedDiam = 15.53804754;
    fExpectedHeight = 15.51932961;
    EXPECT_EQ(clTreePopulation::adult, p_oTrees[iIndex]->GetType());
    p_oTrees[iIndex]->GetValue(p_oPop->GetDbhCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fDiam);
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedDiam = 45.96178962;
    fExpectedHeight = 26.92489921;
    EXPECT_EQ(clTreePopulation::adult, p_oTrees[iIndex]->GetType());
    p_oTrees[iIndex]->GetValue(p_oPop->GetDbhCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fDiam);
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedDiam = 28.55606024;
    fExpectedHeight = 21.76172531;
    EXPECT_EQ(clTreePopulation::adult, p_oTrees[iIndex]->GetType());
    p_oTrees[iIndex]->GetValue(p_oPop->GetDbhCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fDiam);
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);

    delete[] p_oTrees;
    delete p_oSimManager;
  } catch (modelErr &e) {
    delete[] p_oTrees;
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

////////////////////////////////////////////////////////////////////////////
// NormalProcessingRun2()
// Tests normal processing run 2. WritePRStormBiLevelGrowthXMLFile2() does
// setup. Timestep length is 3 years. The growth used is diam with auto height.
// 27 trees are created of 3 species and assigned to a mix of light levels and
// time-since-last-storm. Then growth is run. Tree diameters and heights are
// checked to make sure they are correct.
////////////////////////////////////////////////////////////////////////////
TEST(PRStormBiLevelGrowth, NormalProcessingRun2) {
  clTreePopulation * p_oPop;
  clGrid *p_oStormLight, *p_oStorm;
  clTree **p_oTrees = new clTree*[27];
  float fDiam, fHeight, fExpectedDiam, fExpectedHeight;
  int iIndex, iSpecies, iType;

  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {

    //Load our test file and get our tree population and grid pointers
    p_oSimManager->ReadFile( WritePRStormBiLevelGrowthXMLFile2() );
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );
    p_oStormLight = p_oSimManager->GetGridObject("Storm Light");
    p_oStorm = p_oSimManager->GetGridObject("Storm Damage");

    //Set our grid values
    fDiam = 15;
    p_oStormLight->SetValueOfCell(0, 0, p_oStormLight->GetFloatDataCode("Light"), fDiam);
    fDiam = 35;
    p_oStormLight->SetValueOfCell(0, 1, p_oStormLight->GetFloatDataCode("Light"), fDiam);
    fDiam = 80;
    p_oStormLight->SetValueOfCell(0, 2, p_oStormLight->GetFloatDataCode("Light"), fDiam);

    fDiam = 1;
    p_oStorm->SetValueOfCell(0, 0, p_oStorm->GetFloatDataCode("stormtime"), fDiam);
    fDiam = 0;
    p_oStorm->SetValueOfCell(0, 1, p_oStorm->GetFloatDataCode("stormtime"), fDiam);
    fDiam = 2;
    p_oStorm->SetValueOfCell(0, 2, p_oStorm->GetFloatDataCode("stormtime"), fDiam);

    //Create our trees
    iIndex = 0;

    fDiam = 0.1;
    iSpecies = 0;
    iType = clTreePopulation::seedling;
    p_oTrees[iIndex] = p_oPop->CreateTree(1, 1, iSpecies, iType, fDiam);
    iIndex++;

    fDiam = 0.2;
    iSpecies = 1;
    iType = clTreePopulation::seedling;
    p_oTrees[iIndex] = p_oPop->CreateTree(1, 1, iSpecies, iType, fDiam);
    iIndex++;

    fDiam = 0.3;
    iSpecies = 3;
    iType = clTreePopulation::seedling;
    p_oTrees[iIndex] = p_oPop->CreateTree(1, 1, iSpecies, iType, fDiam);
    iIndex++;

    fDiam = 2.5;
    iSpecies = 0;
    iType = clTreePopulation::sapling;
    p_oTrees[iIndex] = p_oPop->CreateTree(1, 1, iSpecies, iType, fDiam);
    iIndex++;

    fDiam = 3.4;
    iSpecies = 1;
    iType = clTreePopulation::sapling;
    p_oTrees[iIndex] = p_oPop->CreateTree(1, 1, iSpecies, iType, fDiam);
    iIndex++;

    fDiam = 5.4;
    iSpecies = 3;
    iType = clTreePopulation::sapling;
    p_oTrees[iIndex] = p_oPop->CreateTree(1, 1, iSpecies, iType, fDiam);
    iIndex++;

    fDiam = 12.6;
    iSpecies = 0;
    iType = clTreePopulation::adult;
    p_oTrees[iIndex] = p_oPop->CreateTree(1, 1, iSpecies, iType, fDiam);
    iIndex++;

    fDiam = 45.2;
    iSpecies = 1;
    iType = clTreePopulation::adult;
    p_oTrees[iIndex] = p_oPop->CreateTree(1, 1, iSpecies, iType, fDiam);
    iIndex++;

    fDiam = 23.3;
    iSpecies = 3;
    iType = clTreePopulation::adult;
    p_oTrees[iIndex] = p_oPop->CreateTree(1, 1, iSpecies, iType, fDiam);
    iIndex++;

    fDiam = 0.1;
    iSpecies = 0;
    iType = clTreePopulation::seedling;
    p_oTrees[iIndex] = p_oPop->CreateTree(1, 9, iSpecies, iType, fDiam);
    iIndex++;

    fDiam = 0.2;
    iSpecies = 1;
    iType = clTreePopulation::seedling;
    p_oTrees[iIndex] = p_oPop->CreateTree(1, 9, iSpecies, iType, fDiam);
    iIndex++;

    fDiam = 0.3;
    iSpecies = 3;
    iType = clTreePopulation::seedling;
    p_oTrees[iIndex] = p_oPop->CreateTree(1, 9, iSpecies, iType, fDiam);
    iIndex++;

    fDiam = 2.5;
    iSpecies = 0;
    iType = clTreePopulation::sapling;
    p_oTrees[iIndex] = p_oPop->CreateTree(1, 9, iSpecies, iType, fDiam);
    iIndex++;

    fDiam = 3.4;
    iSpecies = 1;
    iType = clTreePopulation::sapling;
    p_oTrees[iIndex] = p_oPop->CreateTree(1, 9, iSpecies, iType, fDiam);
    iIndex++;

    fDiam = 5.4;
    iSpecies = 3;
    iType = clTreePopulation::sapling;
    p_oTrees[iIndex] = p_oPop->CreateTree(1, 9, iSpecies, iType, fDiam);
    iIndex++;

    fDiam = 12.6;
    iSpecies = 0;
    iType = clTreePopulation::adult;
    p_oTrees[iIndex] = p_oPop->CreateTree(1, 9, iSpecies, iType, fDiam);
    iIndex++;

    fDiam = 45.2;
    iSpecies = 1;
    iType = clTreePopulation::adult;
    p_oTrees[iIndex] = p_oPop->CreateTree(1, 9, iSpecies, iType, fDiam);
    iIndex++;

    fDiam = 23.3;
    iSpecies = 3;
    iType = clTreePopulation::adult;
    p_oTrees[iIndex] = p_oPop->CreateTree(1, 9, iSpecies, iType, fDiam);
    iIndex++;

    fDiam = 0.1;
    iSpecies = 0;
    iType = clTreePopulation::seedling;
    p_oTrees[iIndex] = p_oPop->CreateTree(1, 17, iSpecies, iType, fDiam);
    iIndex++;

    fDiam = 0.2;
    iSpecies = 1;
    iType = clTreePopulation::seedling;
    p_oTrees[iIndex] = p_oPop->CreateTree(1, 17, iSpecies, iType, fDiam);
    iIndex++;

    fDiam = 0.3;
    iSpecies = 3;
    iType = clTreePopulation::seedling;
    p_oTrees[iIndex] = p_oPop->CreateTree(1, 17, iSpecies, iType, fDiam);
    iIndex++;

    fDiam = 2.5;
    iSpecies = 0;
    iType = clTreePopulation::sapling;
    p_oTrees[iIndex] = p_oPop->CreateTree(1, 17, iSpecies, iType, fDiam);
    iIndex++;

    fDiam = 3.4;
    iSpecies = 1;
    iType = clTreePopulation::sapling;
    p_oTrees[iIndex] = p_oPop->CreateTree(1, 17, iSpecies, iType, fDiam);
    iIndex++;

    fDiam = 5.4;
    iSpecies = 3;
    iType = clTreePopulation::sapling;
    p_oTrees[iIndex] = p_oPop->CreateTree(1, 17, iSpecies, iType, fDiam);
    iIndex++;

    fDiam = 12.6;
    iSpecies = 0;
    iType = clTreePopulation::adult;
    p_oTrees[iIndex] = p_oPop->CreateTree(1, 17, iSpecies, iType, fDiam);
    iIndex++;

    fDiam = 45.2;
    iSpecies = 1;
    iType = clTreePopulation::adult;
    p_oTrees[iIndex] = p_oPop->CreateTree(1, 17, iSpecies, iType, fDiam);
    iIndex++;

    fDiam = 23.3;
    iSpecies = 3;
    iType = clTreePopulation::adult;
    p_oTrees[iIndex] = p_oPop->CreateTree(1, 17, iSpecies, iType, fDiam);
    iIndex++;

    //Now run growth, but skip storms and storm light
    int i;
    for (i = 0; i < p_oSimManager->GetNumberOfBehaviors(); i++) {
      clBehaviorBase *p_oBase = p_oSimManager->GetBehaviorObject(i);
      if (p_oBase->GetName().compare("StormLight") != 0 &&
          p_oBase->GetName().compare("Storm") != 0)
        p_oBase->Action();
    }

    //Confirm all trees
    iIndex = 0;
    fExpectedDiam = 0.4036;
    fExpectedHeight = 0.38862644;
    EXPECT_EQ(clTreePopulation::seedling, p_oTrees[iIndex]->GetType());
    p_oTrees[iIndex]->GetValue(p_oPop->GetDiam10Code(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fDiam);
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedDiam = 0.218;
    fExpectedHeight = 0.1961346;
    EXPECT_EQ(clTreePopulation::seedling, p_oTrees[iIndex]->GetType());
    p_oTrees[iIndex]->GetValue(p_oPop->GetDiam10Code(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fDiam);
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedDiam = 0.65055744;
    fExpectedHeight = 0.722595733;
    EXPECT_EQ(clTreePopulation::sapling, p_oTrees[iIndex]->GetType());
    p_oTrees[iIndex]->GetValue(p_oPop->GetDbhCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fDiam);
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedDiam = 2.83024;
    fExpectedHeight = 4.4853;
    EXPECT_EQ(clTreePopulation::sapling, p_oTrees[iIndex]->GetType());
    p_oTrees[iIndex]->GetValue(p_oPop->GetDbhCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fDiam);
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedDiam = 3.706;
    fExpectedHeight = 5.765714286;
    EXPECT_EQ(clTreePopulation::sapling, p_oTrees[iIndex]->GetType());
    p_oTrees[iIndex]->GetValue(p_oPop->GetDbhCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fDiam);
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedDiam = 6.21234;
    fExpectedHeight = 9.992233333;
    EXPECT_EQ(clTreePopulation::sapling, p_oTrees[iIndex]->GetType());
    p_oTrees[iIndex]->GetValue(p_oPop->GetDbhCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fDiam);
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedDiam = 13.3536;
    fExpectedHeight = 13.90209907;
    EXPECT_EQ(clTreePopulation::adult, p_oTrees[iIndex]->GetType());
    p_oTrees[iIndex]->GetValue(p_oPop->GetDbhCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fDiam);
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedDiam = 49.268;
    fExpectedHeight = 27.89106335;
    EXPECT_EQ(clTreePopulation::adult, p_oTrees[iIndex]->GetType());
    p_oTrees[iIndex]->GetValue(p_oPop->GetDbhCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fDiam);
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedDiam = 25.5776;
    fExpectedHeight = 20.27561091;
    EXPECT_EQ(clTreePopulation::adult, p_oTrees[iIndex]->GetType());
    p_oTrees[iIndex]->GetValue(p_oPop->GetDbhCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fDiam);
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedDiam = 0.526835601;
    fExpectedHeight = 0.5072;
    EXPECT_EQ(clTreePopulation::seedling, p_oTrees[iIndex]->GetType());
    p_oTrees[iIndex]->GetValue(p_oPop->GetDiam10Code(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fDiam);
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedDiam = 0.218;
    fExpectedHeight = 0.1961346;
    EXPECT_EQ(clTreePopulation::seedling, p_oTrees[iIndex]->GetType());
    p_oTrees[iIndex]->GetValue(p_oPop->GetDiam10Code(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fDiam);
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedDiam = 0.65055744;
    fExpectedHeight = 0.722595733;
    EXPECT_EQ(clTreePopulation::sapling, p_oTrees[iIndex]->GetType());
    p_oTrees[iIndex]->GetValue(p_oPop->GetDbhCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fDiam);
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedDiam = 12.76473526;
    fExpectedHeight = 13.44775949;
    EXPECT_EQ(clTreePopulation::adult, p_oTrees[iIndex]->GetType());
    p_oTrees[iIndex]->GetValue(p_oPop->GetDbhCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fDiam);
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedDiam = 3.706;
    fExpectedHeight = 5.765714286;
    EXPECT_EQ(clTreePopulation::sapling, p_oTrees[iIndex]->GetType());
    p_oTrees[iIndex]->GetValue(p_oPop->GetDbhCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fDiam);
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedDiam = 6.21234;
    fExpectedHeight = 9.992233333;
    EXPECT_EQ(clTreePopulation::sapling, p_oTrees[iIndex]->GetType());
    p_oTrees[iIndex]->GetValue(p_oPop->GetDbhCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fDiam);
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedDiam = 275.791691;
    fExpectedHeight = 39.47;
    EXPECT_EQ(clTreePopulation::adult, p_oTrees[iIndex]->GetType());
    p_oTrees[iIndex]->GetValue(p_oPop->GetDbhCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fDiam);
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    //Have more tolerance here - at the edges of logarithms, calculation
    //algorithms can cause differences between my Excel spreadsheet and the C++
    //math engine
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.01);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.01);
    iIndex++;

    fExpectedDiam = 49.268;
    fExpectedHeight = 27.89106335;
    EXPECT_EQ(clTreePopulation::adult, p_oTrees[iIndex]->GetType());
    p_oTrees[iIndex]->GetValue(p_oPop->GetDbhCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fDiam);
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedDiam = 25.5776;
    fExpectedHeight = 20.27561091;
    EXPECT_EQ(clTreePopulation::adult, p_oTrees[iIndex]->GetType());
    p_oTrees[iIndex]->GetValue(p_oPop->GetDbhCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fDiam);
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedDiam = 0.154401892;
    fExpectedHeight = 0.148673582;
    EXPECT_EQ(clTreePopulation::seedling, p_oTrees[iIndex]->GetType());
    p_oTrees[iIndex]->GetValue(p_oPop->GetDiam10Code(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fDiam);
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedDiam = 0.203448662;
    fExpectedHeight = 0.183042761;
    EXPECT_EQ(clTreePopulation::seedling, p_oTrees[iIndex]->GetType());
    p_oTrees[iIndex]->GetValue(p_oPop->GetDiam10Code(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fDiam);
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedDiam = 0.327076949;
    fExpectedHeight = 1.261535793;
    EXPECT_EQ(clTreePopulation::seedling, p_oTrees[iIndex]->GetType());
    p_oTrees[iIndex]->GetValue(p_oPop->GetDiam10Code(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fDiam);
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedDiam = 3.808281259;
    fExpectedHeight = 5.707851574;
    EXPECT_EQ(clTreePopulation::sapling, p_oTrees[iIndex]->GetType());
    p_oTrees[iIndex]->GetValue(p_oPop->GetDbhCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fDiam);
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedDiam = 3.462117866;
    fExpectedHeight = 5.417311237;
    EXPECT_EQ(clTreePopulation::sapling, p_oTrees[iIndex]->GetType());
    p_oTrees[iIndex]->GetValue(p_oPop->GetDbhCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fDiam);
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedDiam = 6.997827684;
    fExpectedHeight = 11.30137947;
    EXPECT_EQ(clTreePopulation::sapling, p_oTrees[iIndex]->GetType());
    p_oTrees[iIndex]->GetValue(p_oPop->GetDbhCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fDiam);
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedDiam = 22.32413804;
    fExpectedHeight = 19.91955047;
    EXPECT_EQ(clTreePopulation::adult, p_oTrees[iIndex]->GetType());
    p_oTrees[iIndex]->GetValue(p_oPop->GetDbhCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fDiam);
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedDiam = 47.52865532;
    fExpectedHeight = 27.39238192;
    EXPECT_EQ(clTreePopulation::adult, p_oTrees[iIndex]->GetType());
    p_oTrees[iIndex]->GetValue(p_oPop->GetDbhCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fDiam);
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedDiam = 41.92762644;
    fExpectedHeight = 27.16917858;
    EXPECT_EQ(clTreePopulation::adult, p_oTrees[iIndex]->GetType());
    p_oTrees[iIndex]->GetValue(p_oPop->GetDbhCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fDiam);
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);

    delete[] p_oTrees;
    delete p_oSimManager;
  } catch (modelErr &e) {
    delete[] p_oTrees;
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}


////////////////////////////////////////////////////////////////////////////
// ErrorProcessing()
////////////////////////////////////////////////////////////////////////////
TEST(PRStormBiLevelGrowth, ErrorProcessing) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try
  {
    p_oSimManager->ReadFile( WritePRStormBiLevelGrowthXMLErrorFile1() );
    FAIL() << "TestPRStormBiLevelGrowth error processing didn't catch error for WritePRStormBiLevelGrowthXMLErrorFile1.";
  }
  catch ( modelErr& err )
  {
    if ( err.sFunction.compare("clPRStormBiLevelGrowth::DoShellSetup" ) != 0 )
    {
      FAIL() << "TestPRStormBiLevelGrowth error processing caught wrong error for WritePRStormBiLevelGrowthXMLErrorFile1.";
    }
    ;
  }

  try
  {
    p_oSimManager->ReadFile( WritePRStormBiLevelGrowthXMLErrorFile2() );
    FAIL() << "TestPRStormBiLevelGrowth error processing didn't catch error for WritePRStormBiLevelGrowthXMLErrorFile2.";
  }
  catch ( modelErr& err )
  {
    if ( err.sFunction.compare("clPRStormBiLevelGrowth::DoShellSetup" ) != 0 )
    {
      FAIL() << "TestPRStormBiLevelGrowth error processing caught wrong error for WritePRStormBiLevelGrowthXMLErrorFile2.";
    }
    ;
  }

  try
  {
    p_oSimManager->ReadFile( WritePRStormBiLevelGrowthXMLErrorFile3() );
    FAIL() << "TestPRStormBiLevelGrowth error processing didn't catch error for WritePRStormBiLevelGrowthXMLErrorFile3.";
  }
  catch ( modelErr& err )
  {
    if ( err.sFunction.compare("clPRStormBiLevelGrowth::DoShellSetup" ) != 0 )
    {
      FAIL() << "TestPRStormBiLevelGrowth error processing caught wrong error for WritePRStormBiLevelGrowthXMLErrorFile3.";
    }
    ;
  }
  delete p_oSimManager;
}

////////////////////////////////////////////////////////////////////////////
// WritePRStormBiLevelGrowthXMLFile1()
////////////////////////////////////////////////////////////////////////////
const char* WritePRStormBiLevelGrowthXMLFile1() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  //Write file
  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06010101\">"
       << "<plot>"
       << "<timesteps>1</timesteps>"
       << "<yearsPerTimestep>1</yearsPerTimestep>";

  WritePRStormBiLevelGrowthCommonStuff(oOut);

  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>Storm</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>StormLight</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>2</listPosition>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>PRStormBilevelGrowth</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>3</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_1\" type=\"Seedling\"/>"
       << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Seedling\"/>"
       << "<applyTo species=\"Species_4\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_4\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_4\" type=\"Seedling\"/>"
       << "</behavior>"
       << "</behaviorList>"
       << "<Storm1>"
       << "<st_s1ReturnInterval>2</st_s1ReturnInterval>"
       << "<st_s2ReturnInterval>1</st_s2ReturnInterval>"
       << "<st_s3ReturnInterval>20</st_s3ReturnInterval>"
       << "<st_s4ReturnInterval>1.00E+28</st_s4ReturnInterval>"
       << "<st_s5ReturnInterval>13.2</st_s5ReturnInterval>"
       << "<st_s6ReturnInterval>45</st_s6ReturnInterval>"
       << "<st_s7ReturnInterval>50</st_s7ReturnInterval>"
       << "<st_s8ReturnInterval>55</st_s8ReturnInterval>"
       << "<st_s9ReturnInterval>60</st_s9ReturnInterval>"
       << "<st_s10ReturnInterval>65</st_s10ReturnInterval>"
       << "<st_susceptibility>1</st_susceptibility>"
       << "<st_stochasticity>0</st_stochasticity>"
       << "<st_stmSSTPeriod>1</st_stmSSTPeriod>"
       << "<st_stmSineD>0</st_stmSineD>"
       << "<st_stmSineF>1</st_stmSineF>"
       << "<st_stmSineG>1</st_stmSineG>"
       << "<st_stmTrendSlopeM>0</st_stmTrendSlopeM>"
       << "<st_stmTrendInterceptI>1</st_stmTrendInterceptI>"
       << "</Storm1>"
       << "<StormLight2>"
       << "<li_stormLightRadius>15</li_stormLightRadius>"
       << "<li_stormLightSlope>-4</li_stormLightSlope>"
       << "<li_stormLightIntercept>95</li_stormLightIntercept>"
       << "<li_stormLightMaxDmgTime>3</li_stormLightMaxDmgTime>"
       << "<li_stormLightSnagMaxDmgTime>2</li_stormLightSnagMaxDmgTime>"
       << "<li_stormLightStoch>0</li_stormLightStoch>"
       << "<li_stormLightMinFullCanopy>9</li_stormLightMinFullCanopy>"
       << "</StormLight2>";

  WritePRStormBiLevelGrowthGrowthParameters(oOut, 3);
  oOut << "</paramFile>";

  oOut.close();

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WritePRStormBiLevelGrowthXMLFile2()
////////////////////////////////////////////////////////////////////////////
const char* WritePRStormBiLevelGrowthXMLFile2() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  //Write file
  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06010101\">"
       << "<plot>"
       << "<timesteps>1</timesteps>"
       << "<yearsPerTimestep>3</yearsPerTimestep>";

  WritePRStormBiLevelGrowthCommonStuff(oOut);

  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>Storm</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>StormLight</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>2</listPosition>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>PRStormBilevelGrowth</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>3</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_1\" type=\"Seedling\"/>"
       << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Seedling\"/>"
       << "<applyTo species=\"Species_4\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_4\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_4\" type=\"Seedling\"/>"
       << "</behavior>"
       << "</behaviorList>"
       << "<Storm1>"
       << "<st_s1ReturnInterval>2</st_s1ReturnInterval>"
       << "<st_s2ReturnInterval>1</st_s2ReturnInterval>"
       << "<st_s3ReturnInterval>20</st_s3ReturnInterval>"
       << "<st_s4ReturnInterval>1.00E+28</st_s4ReturnInterval>"
       << "<st_s5ReturnInterval>13.2</st_s5ReturnInterval>"
       << "<st_s6ReturnInterval>45</st_s6ReturnInterval>"
       << "<st_s7ReturnInterval>50</st_s7ReturnInterval>"
       << "<st_s8ReturnInterval>55</st_s8ReturnInterval>"
       << "<st_s9ReturnInterval>60</st_s9ReturnInterval>"
       << "<st_s10ReturnInterval>65</st_s10ReturnInterval>"
       << "<st_susceptibility>1</st_susceptibility>"
       << "<st_stochasticity>0</st_stochasticity>"
       << "<st_stmSSTPeriod>1</st_stmSSTPeriod>"
       << "<st_stmSineD>0</st_stmSineD>"
       << "<st_stmSineF>1</st_stmSineF>"
       << "<st_stmSineG>1</st_stmSineG>"
       << "<st_stmTrendSlopeM>0</st_stmTrendSlopeM>"
       << "<st_stmTrendInterceptI>1</st_stmTrendInterceptI>"
       << "</Storm1>"
       << "<StormLight2>"
       << "<li_stormLightRadius>15</li_stormLightRadius>"
       << "<li_stormLightSlope>-4</li_stormLightSlope>"
       << "<li_stormLightIntercept>95</li_stormLightIntercept>"
       << "<li_stormLightMaxDmgTime>3</li_stormLightMaxDmgTime>"
       << "<li_stormLightSnagMaxDmgTime>2</li_stormLightSnagMaxDmgTime>"
       << "<li_stormLightStoch>0</li_stormLightStoch>"
       << "<li_stormLightMinFullCanopy>9</li_stormLightMinFullCanopy>"
       << "</StormLight2>";

  WritePRStormBiLevelGrowthGrowthParameters(oOut, 3);
  oOut << "</paramFile>";

  oOut.close();

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WritePRStormBiLevelGrowthXMLErrorFile1()
////////////////////////////////////////////////////////////////////////////
const char* WritePRStormBiLevelGrowthXMLErrorFile1() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  //Write file
  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06010101\">"
       << "<plot>"
       << "<timesteps>1</timesteps>"
       << "<yearsPerTimestep>1</yearsPerTimestep>";

  WritePRStormBiLevelGrowthCommonStuff(oOut);

  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>Storm</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>StormLight</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>2</listPosition>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>PRStormBilevelGrowth</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>3</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_1\" type=\"Seedling\"/>"
       << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Seedling\"/>"
       << "<applyTo species=\"Species_4\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_4\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_4\" type=\"Seedling\"/>"
       << "</behavior>"
       << "</behaviorList>"
       << "<Storm1>"
       << "<st_s1ReturnInterval>2</st_s1ReturnInterval>"
       << "<st_s2ReturnInterval>1</st_s2ReturnInterval>"
       << "<st_s3ReturnInterval>20</st_s3ReturnInterval>"
       << "<st_s4ReturnInterval>1.00E+28</st_s4ReturnInterval>"
       << "<st_s5ReturnInterval>13.2</st_s5ReturnInterval>"
       << "<st_s6ReturnInterval>45</st_s6ReturnInterval>"
       << "<st_s7ReturnInterval>50</st_s7ReturnInterval>"
       << "<st_s8ReturnInterval>55</st_s8ReturnInterval>"
       << "<st_s9ReturnInterval>60</st_s9ReturnInterval>"
       << "<st_s10ReturnInterval>65</st_s10ReturnInterval>"
       << "<st_susceptibility>1</st_susceptibility>"
       << "<st_stochasticity>0</st_stochasticity>"
       << "<st_stmSSTPeriod>1</st_stmSSTPeriod>"
       << "<st_stmSineD>0</st_stmSineD>"
       << "<st_stmSineF>1</st_stmSineF>"
       << "<st_stmSineG>1</st_stmSineG>"
       << "<st_stmTrendSlopeM>0</st_stmTrendSlopeM>"
       << "<st_stmTrendInterceptI>1</st_stmTrendInterceptI>"
       << "</Storm1>"
       << "<StormLight2>"
       << "<li_stormLightRadius>15</li_stormLightRadius>"
       << "<li_stormLightSlope>-4</li_stormLightSlope>"
       << "<li_stormLightIntercept>95</li_stormLightIntercept>"
       << "<li_stormLightMaxDmgTime>3</li_stormLightMaxDmgTime>"
       << "<li_stormLightSnagMaxDmgTime>2</li_stormLightSnagMaxDmgTime>"
       << "<li_stormLightStoch>0</li_stormLightStoch>"
       << "<li_stormLightMinFullCanopy>9</li_stormLightMinFullCanopy>"
       << "</StormLight2>";

  oOut << "<PRStormBilevelGrowth3>"
       << "<gr_prBilevStmGrwthLoLiteIntercept>"
       << "<gr_pbsglliVal species=\"Species_1\">0.1</gr_pbsglliVal>"
       << "<gr_pbsglliVal species=\"Species_2\">0</gr_pbsglliVal>"
       << "<gr_pbsglliVal species=\"Species_4\">0.2</gr_pbsglliVal>"
       << "</gr_prBilevStmGrwthLoLiteIntercept>"
       << "<gr_prBilevStmGrwthLoLiteSlope>"
       << "<gr_pbsgllsVal species=\"Species_1\">0.012</gr_pbsgllsVal>"
       << "<gr_pbsgllsVal species=\"Species_2\">0.03</gr_pbsgllsVal>"
       << "<gr_pbsgllsVal species=\"Species_4\">0.024</gr_pbsgllsVal>"
       << "</gr_prBilevStmGrwthLoLiteSlope>"
       << "<gr_prBilevStmGrwthHiLiteA>"
       << "<gr_pbsghlaVal species=\"Species_1\">137</gr_pbsghlaVal>"
       << "<gr_pbsghlaVal species=\"Species_2\">358</gr_pbsghlaVal>"
       << "<gr_pbsghlaVal species=\"Species_4\">109</gr_pbsghlaVal>"
       << "</gr_prBilevStmGrwthHiLiteA>"
       << "<gr_prBilevStmGrwthHiLiteB>"
       << "<gr_pbsghlbVal species=\"Species_1\">1.03</gr_pbsghlbVal>"
       << "<gr_pbsghlbVal species=\"Species_2\">3.27</gr_pbsghlbVal>"
       << "<gr_pbsghlbVal species=\"Species_4\">1.12</gr_pbsghlbVal>"
       << "</gr_prBilevStmGrwthHiLiteB>"
       << "<gr_prBilevStmGrwthHiLiteThreshold>"
       << "<gr_pbsghltVal species=\"Species_1\">20</gr_pbsghltVal>"
       << "<gr_pbsghltVal species=\"Species_2\">150</gr_pbsghltVal>"
       << "<gr_pbsghltVal species=\"Species_4\">70</gr_pbsghltVal>"
       << "</gr_prBilevStmGrwthHiLiteThreshold>"
       << "</PRStormBilevelGrowth3>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WritePRStormBiLevelGrowthXMLErrorFile2()
////////////////////////////////////////////////////////////////////////////
const char* WritePRStormBiLevelGrowthXMLErrorFile2() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  //Write file
  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06010101\">"
       << "<plot>"
       << "<timesteps>1</timesteps>"
       << "<yearsPerTimestep>1</yearsPerTimestep>";

  WritePRStormBiLevelGrowthCommonStuff(oOut);

  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>Storm</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>PRStormBilevelGrowth</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>2</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_1\" type=\"Seedling\"/>"
       << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Seedling\"/>"
       << "<applyTo species=\"Species_4\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_4\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_4\" type=\"Seedling\"/>"
       << "</behavior>"
       << "</behaviorList>"
       << "<Storm1>"
       << "<st_s1ReturnInterval>2</st_s1ReturnInterval>"
       << "<st_s2ReturnInterval>1</st_s2ReturnInterval>"
       << "<st_s3ReturnInterval>20</st_s3ReturnInterval>"
       << "<st_s4ReturnInterval>1.00E+28</st_s4ReturnInterval>"
       << "<st_s5ReturnInterval>13.2</st_s5ReturnInterval>"
       << "<st_s6ReturnInterval>45</st_s6ReturnInterval>"
       << "<st_s7ReturnInterval>50</st_s7ReturnInterval>"
       << "<st_s8ReturnInterval>55</st_s8ReturnInterval>"
       << "<st_s9ReturnInterval>60</st_s9ReturnInterval>"
       << "<st_s10ReturnInterval>65</st_s10ReturnInterval>"
       << "<st_susceptibility>1</st_susceptibility>"
       << "<st_stochasticity>0</st_stochasticity>"
       << "<st_stmSSTPeriod>1</st_stmSSTPeriod>"
       << "<st_stmSineD>0</st_stmSineD>"
       << "<st_stmSineF>1</st_stmSineF>"
       << "<st_stmSineG>1</st_stmSineG>"
       << "<st_stmTrendSlopeM>0</st_stmTrendSlopeM>"
       << "<st_stmTrendInterceptI>1</st_stmTrendInterceptI>"
       << "</Storm1>";

  WritePRStormBiLevelGrowthGrowthParameters(oOut, 2);
  oOut << "</paramFile>";

  oOut.close();

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WritePRStormBiLevelGrowthXMLErrorFile3()
////////////////////////////////////////////////////////////////////////////
const char* WritePRStormBiLevelGrowthXMLErrorFile3() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  //Write file
  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06010101\">"
       << "<plot>"
       << "<timesteps>1</timesteps>"
       << "<yearsPerTimestep>1</yearsPerTimestep>";

  WritePRStormBiLevelGrowthCommonStuff(oOut);

  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>StormLight</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>PRStormBilevelGrowth</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>2</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_1\" type=\"Seedling\"/>"
       << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Seedling\"/>"
       << "<applyTo species=\"Species_4\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_4\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_4\" type=\"Seedling\"/>"
       << "</behavior>"
       << "</behaviorList>"
       << "<StormLight1>"
       << "<li_stormLightRadius>15</li_stormLightRadius>"
       << "<li_stormLightSlope>-4</li_stormLightSlope>"
       << "<li_stormLightIntercept>95</li_stormLightIntercept>"
       << "<li_stormLightMaxDmgTime>3</li_stormLightMaxDmgTime>"
       << "<li_stormLightSnagMaxDmgTime>2</li_stormLightSnagMaxDmgTime>"
       << "<li_stormLightStoch>0</li_stormLightStoch>"
       << "<li_stormLightMinFullCanopy>9</li_stormLightMinFullCanopy>"
       << "</StormLight1>";

  WritePRStormBiLevelGrowthGrowthParameters(oOut, 2);
  oOut << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WritePRStormBiLevelGrowthCommonStuff()
/////////////////////////////////////////////////////////////////////////////
void WritePRStormBiLevelGrowthCommonStuff(std::fstream &oOut)
{
  using namespace std;
  oOut << "<randomSeed>1</randomSeed>"
       << "<plot_lenX>100</plot_lenX>"
       << "<plot_lenY>100</plot_lenY>"
       << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
       << "<plot_temp_C>12.88171785</plot_temp_C>"
       << "<plot_latitude>55.37</plot_latitude>"
       << "</plot>"
       << "<trees>"
       << "<tr_speciesList>"
       << "<tr_species speciesName=\"Species_1\"/>"
       << "<tr_species speciesName=\"Species_2\"/>"
       << "<tr_species speciesName=\"Species_3\"/>"
       << "<tr_species speciesName=\"Species_4\"/>"
       << "</tr_speciesList>"
       << "<tr_seedDiam10Cm>0.1</tr_seedDiam10Cm>"
       << "<tr_minAdultDBH>"
       << "<tr_madVal species=\"Species_1\">10.0</tr_madVal>"
       << "<tr_madVal species=\"Species_2\">10.0</tr_madVal>"
       << "<tr_madVal species=\"Species_3\">10.0</tr_madVal>"
       << "<tr_madVal species=\"Species_4\">10.0</tr_madVal>"
       << "</tr_minAdultDBH>"
       << "<tr_maxSeedlingHeight>"
       << "<tr_mshVal species=\"Species_1\">2</tr_mshVal>"
       << "<tr_mshVal species=\"Species_2\">2</tr_mshVal>"
       << "<tr_mshVal species=\"Species_3\">2</tr_mshVal>"
       << "<tr_mshVal species=\"Species_4\">2</tr_mshVal>"
       << "</tr_maxSeedlingHeight>"
       << "</trees>"
       << "<allometry>"
       << "<tr_slopeOfAsymHeight>"
       << "<tr_soahVal species=\"Species_1\">0.0299</tr_soahVal>"
       << "<tr_soahVal species=\"Species_2\">0.0241</tr_soahVal>"
       << "<tr_soahVal species=\"Species_3\">0.0241</tr_soahVal>"
       << "<tr_soahVal species=\"Species_4\">0.0263</tr_soahVal>"
       << "</tr_slopeOfAsymHeight>"
       << "<tr_canopyHeight>"
       << "<tr_chVal species=\"Species_1\">39.48</tr_chVal>"
       << "<tr_chVal species=\"Species_2\">39.54</tr_chVal>"
       << "<tr_chVal species=\"Species_3\">40</tr_chVal>"
       << "<tr_chVal species=\"Species_4\">40</tr_chVal>"
       << "</tr_canopyHeight>"
       << "<tr_stdAsympCrownRad>"
       << "<tr_sacrVal species=\"Species_1\">0.0549</tr_sacrVal>"
       << "<tr_sacrVal species=\"Species_2\">0.0549</tr_sacrVal>"
       << "<tr_sacrVal species=\"Species_3\">0.0549</tr_sacrVal>"
       << "<tr_sacrVal species=\"Species_4\">0.0549</tr_sacrVal>"
       << "</tr_stdAsympCrownRad>"
       << "<tr_stdCrownRadExp>"
       << "<tr_screVal species=\"Species_1\">1.0</tr_screVal>"
       << "<tr_screVal species=\"Species_2\">1.0</tr_screVal>"
       << "<tr_screVal species=\"Species_3\">1.0</tr_screVal>"
       << "<tr_screVal species=\"Species_4\">1.0</tr_screVal>"
       << "</tr_stdCrownRadExp>"
       << "<tr_stdMaxCrownRad>"
       << "<tr_smcrVal species=\"Species_1\">10</tr_smcrVal>"
       << "<tr_smcrVal species=\"Species_2\">10</tr_smcrVal>"
       << "<tr_smcrVal species=\"Species_3\">10</tr_smcrVal>"
       << "<tr_smcrVal species=\"Species_4\">10</tr_smcrVal>"
       << "</tr_stdMaxCrownRad>"
       << "<tr_conversionDiam10ToDBH>"
       << "<tr_cdtdVal species=\"Species_1\">0.8008</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_2\">0.5944</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_3\">0.8008</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_4\">0.7059</tr_cdtdVal>"
       << "</tr_conversionDiam10ToDBH>"
       << "<tr_interceptDiam10ToDBH>"
       << "<tr_idtdVal species=\"Species_1\">0</tr_idtdVal>"
       << "<tr_idtdVal species=\"Species_2\">0</tr_idtdVal>"
       << "<tr_idtdVal species=\"Species_3\">0</tr_idtdVal>"
       << "<tr_idtdVal species=\"Species_4\">0</tr_idtdVal>"
       << "</tr_interceptDiam10ToDBH>"
       << "<tr_stdAsympCrownHt>"
       << "<tr_sachVal species=\"Species_1\">0.389</tr_sachVal>"
       << "<tr_sachVal species=\"Species_2\">0.389</tr_sachVal>"
       << "<tr_sachVal species=\"Species_3\">0.389</tr_sachVal>"
       << "<tr_sachVal species=\"Species_4\">0.389</tr_sachVal>"
       << "</tr_stdAsympCrownHt>"
       << "<tr_stdCrownHtExp>"
       << "<tr_scheVal species=\"Species_1\">1.0</tr_scheVal>"
       << "<tr_scheVal species=\"Species_2\">1.0</tr_scheVal>"
       << "<tr_scheVal species=\"Species_3\">1.0</tr_scheVal>"
       << "<tr_scheVal species=\"Species_4\">1.0</tr_scheVal>"
       << "</tr_stdCrownHtExp>"
       << "<tr_whatSeedlingHeightDiam>"
       << "<tr_wsehdVal species=\"Species_1\">1</tr_wsehdVal>"
       << "<tr_wsehdVal species=\"Species_2\">1</tr_wsehdVal>"
       << "<tr_wsehdVal species=\"Species_3\">1</tr_wsehdVal>"
       << "<tr_wsehdVal species=\"Species_4\">1</tr_wsehdVal>"
       << "</tr_whatSeedlingHeightDiam>"
       << "<tr_whatSaplingHeightDiam>"
       << "<tr_wsahdVal species=\"Species_1\">2</tr_wsahdVal>"
       << "<tr_wsahdVal species=\"Species_2\">2</tr_wsahdVal>"
       << "<tr_wsahdVal species=\"Species_3\">2</tr_wsahdVal>"
       << "<tr_wsahdVal species=\"Species_4\">2</tr_wsahdVal>"
       << "</tr_whatSaplingHeightDiam>"
       << "<tr_whatAdultHeightDiam>"
       << "<tr_wahdVal species=\"Species_1\">0</tr_wahdVal>"
       << "<tr_wahdVal species=\"Species_2\">0</tr_wahdVal>"
       << "<tr_wahdVal species=\"Species_3\">0</tr_wahdVal>"
       << "<tr_wahdVal species=\"Species_4\">0</tr_wahdVal>"
       << "</tr_whatAdultHeightDiam>"
       << "<tr_seedlingLinearSlope>"
       << "<tr_selsVal species=\"Species_1\">0.9629</tr_selsVal>"
       << "<tr_selsVal species=\"Species_2\">0.8997</tr_selsVal>"
       << "<tr_selsVal species=\"Species_3\">0.8997</tr_selsVal>"
       << "<tr_selsVal species=\"Species_4\">3.857</tr_selsVal>"
       << "</tr_seedlingLinearSlope>"
       << "<tr_seedlingLinearIntercept>"
       << "<tr_seliVal species=\"Species_1\">0</tr_seliVal>"
       << "<tr_seliVal species=\"Species_2\">0</tr_seliVal>"
       << "<tr_seliVal species=\"Species_3\">0</tr_seliVal>"
       << "<tr_seliVal species=\"Species_4\">0</tr_seliVal>"
       << "</tr_seedlingLinearIntercept>"
       << "<tr_saplingReverseLinearSlope>"
       << "<tr_sarlsVal species=\"Species_1\">0.8</tr_sarlsVal>"
       << "<tr_sarlsVal species=\"Species_2\">0.7</tr_sarlsVal>"
       << "<tr_sarlsVal species=\"Species_3\">0.7</tr_sarlsVal>"
       << "<tr_sarlsVal species=\"Species_4\">0.6</tr_sarlsVal>"
       << "</tr_saplingReverseLinearSlope>"
       << "<tr_saplingReverseLinearIntercept>"
       << "<tr_sarliVal species=\"Species_1\">-0.758</tr_sarliVal>"
       << "<tr_sarliVal species=\"Species_2\">-0.33</tr_sarliVal>"
       << "<tr_sarliVal species=\"Species_3\">-0.33</tr_sarliVal>"
       << "<tr_sarliVal species=\"Species_4\">0.217</tr_sarliVal>"
       << "</tr_saplingReverseLinearIntercept>"
       << "<tr_whatAdultCrownRadDiam>"
       << "<tr_wacrdVal species=\"Species_1\">0</tr_wacrdVal>"
       << "<tr_wacrdVal species=\"Species_2\">0</tr_wacrdVal>"
       << "<tr_wacrdVal species=\"Species_3\">0</tr_wacrdVal>"
       << "<tr_wacrdVal species=\"Species_4\">0</tr_wacrdVal>"
       << "</tr_whatAdultCrownRadDiam>"
       << "<tr_whatAdultCrownHeightHeight>"
       << "<tr_wachhVal species=\"Species_1\">0</tr_wachhVal>"
       << "<tr_wachhVal species=\"Species_2\">0</tr_wachhVal>"
       << "<tr_wachhVal species=\"Species_3\">0</tr_wachhVal>"
       << "<tr_wachhVal species=\"Species_4\">0</tr_wachhVal>"
       << "</tr_whatAdultCrownHeightHeight>"
       << "<tr_whatSaplingCrownRadDiam>"
       << "<tr_wscrdVal species=\"Species_1\">0</tr_wscrdVal>"
       << "<tr_wscrdVal species=\"Species_2\">0</tr_wscrdVal>"
       << "<tr_wscrdVal species=\"Species_3\">0</tr_wscrdVal>"
       << "<tr_wscrdVal species=\"Species_4\">0</tr_wscrdVal>"
       << "</tr_whatSaplingCrownRadDiam>"
       << "<tr_whatSaplingCrownHeightHeight>"
       << "<tr_wschhVal species=\"Species_1\">0</tr_wschhVal>"
       << "<tr_wschhVal species=\"Species_2\">0</tr_wschhVal>"
       << "<tr_wschhVal species=\"Species_3\">0</tr_wschhVal>"
       << "<tr_wschhVal species=\"Species_4\">0</tr_wschhVal>"
       << "</tr_whatSaplingCrownHeightHeight>"
       << "</allometry>";
}

/////////////////////////////////////////////////////////////////////////////
// WritePRStormBiLevelGrowthGrowthParameters()
/////////////////////////////////////////////////////////////////////////////
void WritePRStormBiLevelGrowthGrowthParameters(std::fstream &oOut, int iListPosition)
{
  using namespace std;
  oOut << "<PRStormBilevelGrowth" << iListPosition << ">"
       << "<gr_prBilevStmGrwthLoLiteIntercept>"
       << "<gr_pbsglliVal species=\"Species_1\">0.1</gr_pbsglliVal>"
       << "<gr_pbsglliVal species=\"Species_2\">0</gr_pbsglliVal>"
       << "<gr_pbsglliVal species=\"Species_4\">0.2</gr_pbsglliVal>"
       << "</gr_prBilevStmGrwthLoLiteIntercept>"
       << "<gr_prBilevStmGrwthLoLiteSlope>"
       << "<gr_pbsgllsVal species=\"Species_1\">0.012</gr_pbsgllsVal>"
       << "<gr_pbsgllsVal species=\"Species_2\">0.03</gr_pbsgllsVal>"
       << "<gr_pbsgllsVal species=\"Species_4\">0.024</gr_pbsgllsVal>"
       << "</gr_prBilevStmGrwthLoLiteSlope>"
       << "<gr_prBilevStmGrwthHiLiteA>"
       << "<gr_pbsghlaVal species=\"Species_1\">137</gr_pbsghlaVal>"
       << "<gr_pbsghlaVal species=\"Species_2\">358</gr_pbsghlaVal>"
       << "<gr_pbsghlaVal species=\"Species_4\">109</gr_pbsghlaVal>"
       << "</gr_prBilevStmGrwthHiLiteA>"
       << "<gr_prBilevStmGrwthHiLiteB>"
       << "<gr_pbsghlbVal species=\"Species_1\">1.03</gr_pbsghlbVal>"
       << "<gr_pbsghlbVal species=\"Species_2\">3.27</gr_pbsghlbVal>"
       << "<gr_pbsghlbVal species=\"Species_4\">1.12</gr_pbsghlbVal>"
       << "</gr_prBilevStmGrwthHiLiteB>"
       << "<gr_prBilevStmGrwthHiLiteThreshold>"
       << "<gr_pbsghltVal species=\"Species_1\">20</gr_pbsghltVal>"
       << "<gr_pbsghltVal species=\"Species_2\">50</gr_pbsghltVal>"
       << "<gr_pbsghltVal species=\"Species_4\">70</gr_pbsghltVal>"
       << "</gr_prBilevStmGrwthHiLiteThreshold>"
       << "</PRStormBilevelGrowth" << iListPosition << ">";
}
