//---------------------------------------------------------------------------
// TestLinearBiLevelGrowth.cpp
//---------------------------------------------------------------------------
#include "TestLinearBiLevelGrowth.h"
#include <gtest/gtest.h>
#include <fstream>
#include <math.h>
#include "TreePopulation.h"
#include "SimManager.h"
#include "BehaviorBase.h"
#include "Grid.h"

////////////////////////////////////////////////////////////////////////////
// NormalProcessingRun1()
// Tests normal processing run 1. WriteLinearBiLevelGrowthXMLFile1() does setup.
// Timestep length is 1 year and there is a light grid present. The growth used
// is diam with auto height. 27 trees are created of 3 species and assigned to a
// mix of light levels. Then growth is run. Their diameters and heights are
// checked to make sure they are correct.
////////////////////////////////////////////////////////////////////////////
TEST(LinearBiLevelGrowth, NormalProcessingRun1) {
  clTreePopulation * p_oPop;
  clGrid *p_oStormLight;
  clTree **p_oTrees = new clTree*[27];
  float fDiam, fHeight, fExpectedDiam, fExpectedHeight;
  int iIndex, iSpecies, iType;

  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    //Load our test file and get our tree population and grid pointers
    p_oSimManager->ReadFile( WriteLinearBiLevelGrowthXMLFile1() );
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );
    p_oStormLight = p_oSimManager->GetGridObject("Storm Light");

    //Set our grid values
    fDiam = 15;
    p_oStormLight->SetValueOfCell(0, 0, p_oStormLight->GetFloatDataCode("Light"), fDiam);
    fDiam = 35;
    p_oStormLight->SetValueOfCell(0, 1, p_oStormLight->GetFloatDataCode("Light"), fDiam);
    fDiam = 80;
    p_oStormLight->SetValueOfCell(0, 2, p_oStormLight->GetFloatDataCode("Light"), fDiam);

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

    //Now run growth, but skip storm light
    int i;
    for (i = 1; i < p_oSimManager->GetNumberOfBehaviors(); i++) {
      clBehaviorBase *p_oBase = p_oSimManager->GetBehaviorObject(i);
      p_oBase->Action();
    }

    //Confirm all trees
    iIndex = 0;
    fExpectedDiam = 0.2012;
    fExpectedHeight = 0.19373548;
    EXPECT_EQ(clTreePopulation::seedling, p_oTrees[iIndex]->GetType());
    p_oTrees[iIndex]->GetValue(p_oPop->GetDiam10Code(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fDiam);
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedDiam = 0.206;
    fExpectedHeight = 0.1853382;
    EXPECT_EQ(clTreePopulation::seedling, p_oTrees[iIndex]->GetType());
    p_oTrees[iIndex]->GetValue(p_oPop->GetDiam10Code(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fDiam);
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedDiam = 0.5072;
    fExpectedHeight = 1.9562704;
    EXPECT_EQ(clTreePopulation::seedling, p_oTrees[iIndex]->GetType());
    p_oTrees[iIndex]->GetValue(p_oPop->GetDiam10Code(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fDiam);
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedDiam = 2.61008;
    fExpectedHeight = 4.2101;
    EXPECT_EQ(clTreePopulation::sapling, p_oTrees[iIndex]->GetType());
    p_oTrees[iIndex]->GetValue(p_oPop->GetDbhCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fDiam);
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedDiam = 3.502;
    fExpectedHeight = 5.474285714;
    EXPECT_EQ(clTreePopulation::sapling, p_oTrees[iIndex]->GetType());
    p_oTrees[iIndex]->GetValue(p_oPop->GetDbhCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fDiam);
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedDiam = 5.67078;
    fExpectedHeight = 9.089633333;
    EXPECT_EQ(clTreePopulation::sapling, p_oTrees[iIndex]->GetType());
    p_oTrees[iIndex]->GetValue(p_oPop->GetDbhCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fDiam);
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedDiam = 12.8512;
    fExpectedHeight = 13.5149736;
    EXPECT_EQ(clTreePopulation::adult, p_oTrees[iIndex]->GetType());
    p_oTrees[iIndex]->GetValue(p_oPop->GetDbhCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fDiam);
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedDiam = 46.556;
    fExpectedHeight = 27.10426602;
    EXPECT_EQ(clTreePopulation::adult, p_oTrees[iIndex]->GetType());
    p_oTrees[iIndex]->GetValue(p_oPop->GetDbhCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fDiam);
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedDiam = 24.0592;
    fExpectedHeight = 19.47199985;
    EXPECT_EQ(clTreePopulation::adult, p_oTrees[iIndex]->GetType());
    p_oTrees[iIndex]->GetValue(p_oPop->GetDbhCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fDiam);
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedDiam = 0.4045;
    fExpectedHeight = 0.38949305;
    EXPECT_EQ(clTreePopulation::seedling, p_oTrees[iIndex]->GetType());
    p_oTrees[iIndex]->GetValue(p_oPop->GetDiam10Code(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fDiam);
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedDiam = 0.206;
    fExpectedHeight = 0.1853382;
    EXPECT_EQ(clTreePopulation::seedling, p_oTrees[iIndex]->GetType());
    p_oTrees[iIndex]->GetValue(p_oPop->GetDiam10Code(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fDiam);
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedDiam = 0.5072;
    fExpectedHeight = 1.9562704;
    EXPECT_EQ(clTreePopulation::seedling, p_oTrees[iIndex]->GetType());
    p_oTrees[iIndex]->GetValue(p_oPop->GetDiam10Code(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fDiam);
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedDiam = 2.85274;
    fExpectedHeight = 4.513425;
    EXPECT_EQ(clTreePopulation::sapling, p_oTrees[iIndex]->GetType());
    p_oTrees[iIndex]->GetValue(p_oPop->GetDbhCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fDiam);
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedDiam = 3.502;
    fExpectedHeight = 5.474285714;
    EXPECT_EQ(clTreePopulation::sapling, p_oTrees[iIndex]->GetType());
    p_oTrees[iIndex]->GetValue(p_oPop->GetDbhCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fDiam);
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedDiam = 5.67078;
    fExpectedHeight = 9.089633333;
    EXPECT_EQ(clTreePopulation::sapling, p_oTrees[iIndex]->GetType());
    p_oTrees[iIndex]->GetValue(p_oPop->GetDbhCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fDiam);
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedDiam = 13.467;
    fExpectedHeight = 13.98867817;
    EXPECT_EQ(clTreePopulation::adult, p_oTrees[iIndex]->GetType());
    p_oTrees[iIndex]->GetValue(p_oPop->GetDbhCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fDiam);
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedDiam = 46.556;
    fExpectedHeight = 27.10426602;
    EXPECT_EQ(clTreePopulation::adult, p_oTrees[iIndex]->GetType());
    p_oTrees[iIndex]->GetValue(p_oPop->GetDbhCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fDiam);
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedDiam = 24.0592;
    fExpectedHeight = 19.47199985;
    EXPECT_EQ(clTreePopulation::adult, p_oTrees[iIndex]->GetType());
    p_oTrees[iIndex]->GetValue(p_oPop->GetDbhCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fDiam);
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedDiam = 0.4045;
    fExpectedHeight = 0.38949305;
    EXPECT_EQ(clTreePopulation::seedling, p_oTrees[iIndex]->GetType());
    p_oTrees[iIndex]->GetValue(p_oPop->GetDiam10Code(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fDiam);
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedDiam = 0.6112;
    fExpectedHeight = 0.54989664;
    EXPECT_EQ(clTreePopulation::seedling, p_oTrees[iIndex]->GetType());
    p_oTrees[iIndex]->GetValue(p_oPop->GetDiam10Code(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fDiam);
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedDiam = 0.57890859;
    fExpectedHeight = 0.603180983;
    EXPECT_EQ(clTreePopulation::sapling, p_oTrees[iIndex]->GetType());
    p_oTrees[iIndex]->GetValue(p_oPop->GetDbhCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fDiam);
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedDiam = 2.85274;
    fExpectedHeight = 4.513425;
    EXPECT_EQ(clTreePopulation::sapling, p_oTrees[iIndex]->GetType());
    p_oTrees[iIndex]->GetValue(p_oPop->GetDbhCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fDiam);
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedDiam = 3.82816;
    fExpectedHeight = 5.940228571;
    EXPECT_EQ(clTreePopulation::sapling, p_oTrees[iIndex]->GetType());
    p_oTrees[iIndex]->GetValue(p_oPop->GetDbhCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fDiam);
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedDiam = 6.11475;
    fExpectedHeight = 9.829583333;
    EXPECT_EQ(clTreePopulation::sapling, p_oTrees[iIndex]->GetType());
    p_oTrees[iIndex]->GetValue(p_oPop->GetDbhCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fDiam);
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedDiam = 13.467;
    fExpectedHeight = 13.98867817;
    EXPECT_EQ(clTreePopulation::adult, p_oTrees[iIndex]->GetType());
    p_oTrees[iIndex]->GetValue(p_oPop->GetDbhCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fDiam);
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedDiam = 48.1312;
    fExpectedHeight = 27.56750685;
    EXPECT_EQ(clTreePopulation::adult, p_oTrees[iIndex]->GetType());
    p_oTrees[iIndex]->GetValue(p_oPop->GetDbhCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fDiam);
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedDiam = 25.3611;
    fExpectedHeight = 20.16298087;
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
// Tests normal processing run 2. WriteLinearBiLevelGrowthXMLFile2() does setup.
// Timestep length is 3 years and there is a light grid present. The growth used
// is diam with auto height. 27 trees are created of 3 species and assigned to a
// mix of light levels. Then growth is run. Their diameters and heights are
// checked to make sure they are correct.
////////////////////////////////////////////////////////////////////////////
TEST(LinearBiLevelGrowth, NormalProcessingRun2) {
  clTreePopulation * p_oPop;
  clGrid *p_oStormLight;
  clTree **p_oTrees = new clTree*[27];
  float fDiam, fHeight, fExpectedDiam, fExpectedHeight;
  int iIndex, iSpecies, iType;

  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {

    //Load our test file and get our tree population and grid pointers
    p_oSimManager->ReadFile( WriteLinearBiLevelGrowthXMLFile2() );
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );
    p_oStormLight = p_oSimManager->GetGridObject("Storm Light");

    //Set our grid values
    fDiam = 15;
    p_oStormLight->SetValueOfCell(0, 0, p_oStormLight->GetFloatDataCode("Light"), fDiam);
    fDiam = 35;
    p_oStormLight->SetValueOfCell(0, 1, p_oStormLight->GetFloatDataCode("Light"), fDiam);
    fDiam = 80;
    p_oStormLight->SetValueOfCell(0, 2, p_oStormLight->GetFloatDataCode("Light"), fDiam);

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

    //Now run growth, but skip storm light
    int i;
    for (i = 1; i < p_oSimManager->GetNumberOfBehaviors(); i++) {
      clBehaviorBase *p_oBase = p_oSimManager->GetBehaviorObject(i);
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

    fExpectedDiam = 1.0135;
    fExpectedHeight = 0.97589915;
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

    fExpectedDiam = 3.55822;
    fExpectedHeight = 5.395275;
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

    fExpectedDiam = 15.201;
    fExpectedHeight = 15.27663982;
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

    fExpectedDiam = 1.0135;
    fExpectedHeight = 0.97589915;
    EXPECT_EQ(clTreePopulation::seedling, p_oTrees[iIndex]->GetType());
    p_oTrees[iIndex]->GetValue(p_oPop->GetDiam10Code(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fDiam);
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedDiam = 1.4336;
    fExpectedHeight = 1.28980992;
    EXPECT_EQ(clTreePopulation::seedling, p_oTrees[iIndex]->GetType());
    p_oTrees[iIndex]->GetValue(p_oPop->GetDiam10Code(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fDiam);
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedDiam = 1.31318577;
    fExpectedHeight = 1.826976283;
    EXPECT_EQ(clTreePopulation::sapling, p_oTrees[iIndex]->GetType());
    p_oTrees[iIndex]->GetValue(p_oPop->GetDbhCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fDiam);
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedDiam = 3.55822;
    fExpectedHeight = 5.395275;
    EXPECT_EQ(clTreePopulation::sapling, p_oTrees[iIndex]->GetType());
    p_oTrees[iIndex]->GetValue(p_oPop->GetDbhCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fDiam);
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedDiam = 4.68448;
    fExpectedHeight = 7.163542857;
    EXPECT_EQ(clTreePopulation::sapling, p_oTrees[iIndex]->GetType());
    p_oTrees[iIndex]->GetValue(p_oPop->GetDbhCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fDiam);
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedDiam = 7.54425;
    fExpectedHeight = 12.21208333;
    EXPECT_EQ(clTreePopulation::sapling, p_oTrees[iIndex]->GetType());
    p_oTrees[iIndex]->GetValue(p_oPop->GetDbhCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fDiam);
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedDiam = 15.201;
    fExpectedHeight = 15.27663982;
    EXPECT_EQ(clTreePopulation::adult, p_oTrees[iIndex]->GetType());
    p_oTrees[iIndex]->GetValue(p_oPop->GetDbhCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fDiam);
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedDiam = 53.9936;
    fExpectedHeight = 29.14496861;
    EXPECT_EQ(clTreePopulation::adult, p_oTrees[iIndex]->GetType());
    p_oTrees[iIndex]->GetValue(p_oPop->GetDbhCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fDiam);
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedDiam = 29.4833;
    fExpectedHeight = 22.20111197;
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
// NormalProcessingRun3()
// Tests normal processing run 3. WriteLinearBiLevelGrowthXMLFile3() does setup. Timestep
// length is 1 year and there is a light grid present. The growth used is
// diam only. 27 trees are created of 3 species and assigned to a mix of
// light levels. Then growth is run. Their diameters and heights are checked
// to make sure they are correct.
////////////////////////////////////////////////////////////////////////////
TEST(LinearBiLevelGrowth, NormalProcessingRun3) {
  clTreePopulation * p_oPop;
  clGrid *p_oStormLight;
  clTree **p_oTrees = new clTree*[27];
  float fDiam, fHeight, fExpectedDiam, fExpectedHeight;
  int iIndex, iSpecies, iType;

  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {

    //Load our test file and get our tree population and grid pointers
    p_oSimManager->ReadFile( WriteLinearBiLevelGrowthXMLFile3() );
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );
    p_oStormLight = p_oSimManager->GetGridObject("Storm Light");

    //Set our grid values
    fDiam = 15;
    p_oStormLight->SetValueOfCell(0, 0, p_oStormLight->GetFloatDataCode("Light"), fDiam);
    fDiam = 35;
    p_oStormLight->SetValueOfCell(0, 1, p_oStormLight->GetFloatDataCode("Light"), fDiam);
    fDiam = 80;
    p_oStormLight->SetValueOfCell(0, 2, p_oStormLight->GetFloatDataCode("Light"), fDiam);

    //Create our trees
    iIndex = 0;

    fDiam = 0.1;
    iSpecies = 0;
    fHeight = 0.7;
    iType = clTreePopulation::seedling;
    p_oTrees[iIndex] = p_oPop->CreateTree(1, 1, iSpecies, iType, fDiam);
    p_oTrees[iIndex]->SetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), fHeight, false, false);
    iIndex++;

    fDiam = 0.2;
    iSpecies = 1;
    fHeight = 0.7;
    iType = clTreePopulation::seedling;
    p_oTrees[iIndex] = p_oPop->CreateTree(1, 1, iSpecies, iType, fDiam);
    p_oTrees[iIndex]->SetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), fHeight, false, false);
    iIndex++;

    fDiam = 0.3;
    iSpecies = 3;
    fHeight = 0.7;
    iType = clTreePopulation::seedling;
    p_oTrees[iIndex] = p_oPop->CreateTree(1, 1, iSpecies, iType, fDiam);
    p_oTrees[iIndex]->SetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), fHeight, false, false);
    iIndex++;

    fDiam = 2.5;
    iSpecies = 0;
    fHeight = 5;
    iType = clTreePopulation::sapling;
    p_oTrees[iIndex] = p_oPop->CreateTree(1, 1, iSpecies, iType, fDiam);
    p_oTrees[iIndex]->SetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), fHeight, false, false);
    iIndex++;

    fDiam = 3.4;
    iSpecies = 1;
    fHeight = 5;
    iType = clTreePopulation::sapling;
    p_oTrees[iIndex] = p_oPop->CreateTree(1, 1, iSpecies, iType, fDiam);
    p_oTrees[iIndex]->SetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), fHeight, false, false);
    iIndex++;

    fDiam = 5.4;
    iSpecies = 3;
    fHeight = 5;
    iType = clTreePopulation::sapling;
    p_oTrees[iIndex] = p_oPop->CreateTree(1, 1, iSpecies, iType, fDiam);
    p_oTrees[iIndex]->SetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), fHeight, false, false);
    iIndex++;

    fDiam = 12.6;
    iSpecies = 0;
    fHeight = 12;
    iType = clTreePopulation::adult;
    p_oTrees[iIndex] = p_oPop->CreateTree(1, 1, iSpecies, iType, fDiam);
    p_oTrees[iIndex]->SetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), fHeight, false, false);
    iIndex++;

    fDiam = 45.2;
    iSpecies = 1;
    fHeight = 12;
    iType = clTreePopulation::adult;
    p_oTrees[iIndex] = p_oPop->CreateTree(1, 1, iSpecies, iType, fDiam);
    p_oTrees[iIndex]->SetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), fHeight, false, false);
    iIndex++;

    fDiam = 23.3;
    iSpecies = 3;
    fHeight = 12;
    iType = clTreePopulation::adult;
    p_oTrees[iIndex] = p_oPop->CreateTree(1, 1, iSpecies, iType, fDiam);
    p_oTrees[iIndex]->SetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), fHeight, false, false);
    iIndex++;

    fDiam = 0.1;
    iSpecies = 0;
    fHeight = 0.7;
    iType = clTreePopulation::seedling;
    p_oTrees[iIndex] = p_oPop->CreateTree(1, 9, iSpecies, iType, fDiam);
    p_oTrees[iIndex]->SetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), fHeight, false, false);
    iIndex++;

    fDiam = 0.2;
    iSpecies = 1;
    fHeight = 0.7;
    iType = clTreePopulation::seedling;
    p_oTrees[iIndex] = p_oPop->CreateTree(1, 9, iSpecies, iType, fDiam);
    p_oTrees[iIndex]->SetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), fHeight, false, false);
    iIndex++;

    fDiam = 0.3;
    iSpecies = 3;
    fHeight = 0.7;
    iType = clTreePopulation::seedling;
    p_oTrees[iIndex] = p_oPop->CreateTree(1, 9, iSpecies, iType, fDiam);
    p_oTrees[iIndex]->SetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), fHeight, false, false);
    iIndex++;

    fDiam = 2.5;
    iSpecies = 0;
    fHeight = 5;
    iType = clTreePopulation::sapling;
    p_oTrees[iIndex] = p_oPop->CreateTree(1, 9, iSpecies, iType, fDiam);
    p_oTrees[iIndex]->SetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), fHeight, false, false);
    iIndex++;

    fDiam = 3.4;
    iSpecies = 1;
    fHeight = 5;
    iType = clTreePopulation::sapling;
    p_oTrees[iIndex] = p_oPop->CreateTree(1, 9, iSpecies, iType, fDiam);
    p_oTrees[iIndex]->SetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), fHeight, false, false);
    iIndex++;

    fDiam = 5.4;
    iSpecies = 3;
    fHeight = 5;
    iType = clTreePopulation::sapling;
    p_oTrees[iIndex] = p_oPop->CreateTree(1, 9, iSpecies, iType, fDiam);
    p_oTrees[iIndex]->SetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), fHeight, false, false);
    iIndex++;

    fDiam = 12.6;
    iSpecies = 0;
    fHeight = 12;
    iType = clTreePopulation::adult;
    p_oTrees[iIndex] = p_oPop->CreateTree(1, 9, iSpecies, iType, fDiam);
    p_oTrees[iIndex]->SetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), fHeight, false, false);
    iIndex++;

    fDiam = 45.2;
    iSpecies = 1;
    fHeight = 12;
    iType = clTreePopulation::adult;
    p_oTrees[iIndex] = p_oPop->CreateTree(1, 9, iSpecies, iType, fDiam);
    p_oTrees[iIndex]->SetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), fHeight, false, false);
    iIndex++;

    fDiam = 23.3;
    iSpecies = 3;
    fHeight = 12;
    iType = clTreePopulation::adult;
    p_oTrees[iIndex] = p_oPop->CreateTree(1, 9, iSpecies, iType, fDiam);
    p_oTrees[iIndex]->SetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), fHeight, false, false);
    iIndex++;

    fDiam = 0.1;
    iSpecies = 0;
    fHeight = 0.7;
    iType = clTreePopulation::seedling;
    p_oTrees[iIndex] = p_oPop->CreateTree(1, 17, iSpecies, iType, fDiam);
    p_oTrees[iIndex]->SetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), fHeight, false, false);
    iIndex++;

    fDiam = 0.2;
    iSpecies = 1;
    fHeight = 0.7;
    iType = clTreePopulation::seedling;
    p_oTrees[iIndex] = p_oPop->CreateTree(1, 17, iSpecies, iType, fDiam);
    p_oTrees[iIndex]->SetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), fHeight, false, false);
    iIndex++;

    fDiam = 0.3;
    iSpecies = 3;
    fHeight = 0.7;
    iType = clTreePopulation::seedling;
    p_oTrees[iIndex] = p_oPop->CreateTree(1, 17, iSpecies, iType, fDiam);
    p_oTrees[iIndex]->SetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), fHeight, false, false);
    iIndex++;

    fDiam = 2.5;
    iSpecies = 0;
    fHeight = 5;
    iType = clTreePopulation::sapling;
    p_oTrees[iIndex] = p_oPop->CreateTree(1, 17, iSpecies, iType, fDiam);
    p_oTrees[iIndex]->SetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), fHeight, false, false);
    iIndex++;

    fDiam = 3.4;
    iSpecies = 1;
    fHeight = 5;
    iType = clTreePopulation::sapling;
    p_oTrees[iIndex] = p_oPop->CreateTree(1, 17, iSpecies, iType, fDiam);
    p_oTrees[iIndex]->SetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), fHeight, false, false);
    iIndex++;

    fDiam = 5.4;
    iSpecies = 3;
    fHeight = 5;
    iType = clTreePopulation::sapling;
    p_oTrees[iIndex] = p_oPop->CreateTree(1, 17, iSpecies, iType, fDiam);
    p_oTrees[iIndex]->SetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), fHeight, false, false);
    iIndex++;

    fDiam = 12.6;
    iSpecies = 0;
    fHeight = 12;
    iType = clTreePopulation::adult;
    p_oTrees[iIndex] = p_oPop->CreateTree(1, 17, iSpecies, iType, fDiam);
    p_oTrees[iIndex]->SetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), fHeight, false, false);
    iIndex++;

    fDiam = 45.2;
    iSpecies = 1;
    fHeight = 12;
    iType = clTreePopulation::adult;
    p_oTrees[iIndex] = p_oPop->CreateTree(1, 17, iSpecies, iType, fDiam);
    p_oTrees[iIndex]->SetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), fHeight, false, false);
    iIndex++;

    fDiam = 23.3;
    iSpecies = 3;
    fHeight = 12;
    iType = clTreePopulation::adult;
    p_oTrees[iIndex] = p_oPop->CreateTree(1, 17, iSpecies, iType, fDiam);
    p_oTrees[iIndex]->SetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), fHeight, false, false);
    iIndex++;

    //Now run growth, but skip storm light
    int i;
    for (i = 1; i < p_oSimManager->GetNumberOfBehaviors(); i++) {
      clBehaviorBase *p_oBase = p_oSimManager->GetBehaviorObject(i);
      p_oBase->Action();
    }

    //Confirm all trees
    iIndex = 0;
    fExpectedDiam = 0.2012;
    fExpectedHeight = 0.79744548;
    EXPECT_EQ(clTreePopulation::seedling, p_oTrees[iIndex]->GetType());
    p_oTrees[iIndex]->GetValue(p_oPop->GetDiam10Code(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fDiam);
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedDiam = 0.206;
    fExpectedHeight = 0.7053982;
    EXPECT_EQ(clTreePopulation::seedling, p_oTrees[iIndex]->GetType());
    p_oTrees[iIndex]->GetValue(p_oPop->GetDiam10Code(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fDiam);
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedDiam = 0.5072;
    fExpectedHeight = 1.4991704;
    EXPECT_EQ(clTreePopulation::seedling, p_oTrees[iIndex]->GetType());
    p_oTrees[iIndex]->GetValue(p_oPop->GetDiam10Code(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fDiam);
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedDiam = 2.61008;
    fExpectedHeight = 5.1376;
    EXPECT_EQ(clTreePopulation::sapling, p_oTrees[iIndex]->GetType());
    p_oTrees[iIndex]->GetValue(p_oPop->GetDbhCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fDiam);
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedDiam = 3.502;
    fExpectedHeight = 5.145714286;
    EXPECT_EQ(clTreePopulation::sapling, p_oTrees[iIndex]->GetType());
    p_oTrees[iIndex]->GetValue(p_oPop->GetDbhCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fDiam);
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedDiam = 5.67078;
    fExpectedHeight = 5.4513;
    EXPECT_EQ(clTreePopulation::sapling, p_oTrees[iIndex]->GetType());
    p_oTrees[iIndex]->GetValue(p_oPop->GetDbhCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fDiam);
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedDiam = 12.8512;
    fExpectedHeight = 12.19575442;
    EXPECT_EQ(clTreePopulation::adult, p_oTrees[iIndex]->GetType());
    p_oTrees[iIndex]->GetValue(p_oPop->GetDbhCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fDiam);
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedDiam = 46.556;
    fExpectedHeight = 12.41310815;
    EXPECT_EQ(clTreePopulation::adult, p_oTrees[iIndex]->GetType());
    p_oTrees[iIndex]->GetValue(p_oPop->GetDbhCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fDiam);
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedDiam = 24.0592;
    fExpectedHeight = 12.41400118;
    EXPECT_EQ(clTreePopulation::adult, p_oTrees[iIndex]->GetType());
    p_oTrees[iIndex]->GetValue(p_oPop->GetDbhCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fDiam);
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedDiam = 0.4045;
    fExpectedHeight = 0.99320305;
    EXPECT_EQ(clTreePopulation::seedling, p_oTrees[iIndex]->GetType());
    p_oTrees[iIndex]->GetValue(p_oPop->GetDiam10Code(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fDiam);
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedDiam = 0.206;
    fExpectedHeight = 0.7053982;
    EXPECT_EQ(clTreePopulation::seedling, p_oTrees[iIndex]->GetType());
    p_oTrees[iIndex]->GetValue(p_oPop->GetDiam10Code(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fDiam);
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedDiam = 0.5072;
    fExpectedHeight = 1.4991704;
    EXPECT_EQ(clTreePopulation::seedling, p_oTrees[iIndex]->GetType());
    p_oTrees[iIndex]->GetValue(p_oPop->GetDiam10Code(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fDiam);
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedDiam = 2.85274;
    fExpectedHeight = 5.440925;
    EXPECT_EQ(clTreePopulation::sapling, p_oTrees[iIndex]->GetType());
    p_oTrees[iIndex]->GetValue(p_oPop->GetDbhCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fDiam);
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedDiam = 3.502;
    fExpectedHeight = 5.145714286;
    EXPECT_EQ(clTreePopulation::sapling, p_oTrees[iIndex]->GetType());
    p_oTrees[iIndex]->GetValue(p_oPop->GetDbhCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fDiam);
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedDiam = 5.67078;
    fExpectedHeight = 5.4513;
    EXPECT_EQ(clTreePopulation::sapling, p_oTrees[iIndex]->GetType());
    p_oTrees[iIndex]->GetValue(p_oPop->GetDbhCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fDiam);
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedDiam = 13.467;
    fExpectedHeight = 12.66945899;
    EXPECT_EQ(clTreePopulation::adult, p_oTrees[iIndex]->GetType());
    p_oTrees[iIndex]->GetValue(p_oPop->GetDbhCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fDiam);
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedDiam = 46.556;
    fExpectedHeight = 12.41310815;
    EXPECT_EQ(clTreePopulation::adult, p_oTrees[iIndex]->GetType());
    p_oTrees[iIndex]->GetValue(p_oPop->GetDbhCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fDiam);
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedDiam = 24.0592;
    fExpectedHeight = 12.41400118;
    EXPECT_EQ(clTreePopulation::adult, p_oTrees[iIndex]->GetType());
    p_oTrees[iIndex]->GetValue(p_oPop->GetDbhCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fDiam);
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedDiam = 0.4045;
    fExpectedHeight = 0.99320305;
    EXPECT_EQ(clTreePopulation::seedling, p_oTrees[iIndex]->GetType());
    p_oTrees[iIndex]->GetValue(p_oPop->GetDiam10Code(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fDiam);
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedDiam = 0.6112;
    fExpectedHeight = 1.06995664;
    EXPECT_EQ(clTreePopulation::seedling, p_oTrees[iIndex]->GetType());
    p_oTrees[iIndex]->GetValue(p_oPop->GetDiam10Code(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fDiam);
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedDiam = 0.57890859;
    fExpectedHeight = 2.7060257;
    EXPECT_EQ(clTreePopulation::sapling, p_oTrees[iIndex]->GetType());
    p_oTrees[iIndex]->GetValue(p_oPop->GetDbhCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fDiam);
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedDiam = 2.85274;
    fExpectedHeight = 5.440925;
    EXPECT_EQ(clTreePopulation::sapling, p_oTrees[iIndex]->GetType());
    p_oTrees[iIndex]->GetValue(p_oPop->GetDbhCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fDiam);
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedDiam = 3.82816;
    fExpectedHeight = 5.611657143;
    EXPECT_EQ(clTreePopulation::sapling, p_oTrees[iIndex]->GetType());
    p_oTrees[iIndex]->GetValue(p_oPop->GetDbhCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fDiam);
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedDiam = 6.11475;
    fExpectedHeight = 6.19125;
    EXPECT_EQ(clTreePopulation::sapling, p_oTrees[iIndex]->GetType());
    p_oTrees[iIndex]->GetValue(p_oPop->GetDbhCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fDiam);
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedDiam = 13.467;
    fExpectedHeight = 12.66945899;
    EXPECT_EQ(clTreePopulation::adult, p_oTrees[iIndex]->GetType());
    p_oTrees[iIndex]->GetValue(p_oPop->GetDbhCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fDiam);
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedDiam = 48.1312;
    fExpectedHeight = 12.87634899;
    EXPECT_EQ(clTreePopulation::adult, p_oTrees[iIndex]->GetType());
    p_oTrees[iIndex]->GetValue(p_oPop->GetDbhCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fDiam);
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedDiam = 25.3611;
    fExpectedHeight = 13.10498219;
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
// NormalProcessingRun4()
// Tests normal processing run 4. WriteLinearBiLevelGrowthXMLFile4() does setup. Timestep
// length is 1 year and there is no light grid present. The growth used is
// diam with auto height. 27 trees are created of 3 species. Then growth is
// run. Their diameters and heights are checked to make sure they are
// correct.
////////////////////////////////////////////////////////////////////////////
TEST(LinearBiLevelGrowth, NormalProcessingRun4) {
  clTreePopulation * p_oPop;
  clTree **p_oTrees = new clTree*[27];
  float fDiam, fHeight, fExpectedDiam, fExpectedHeight;
  int iIndex, iSpecies, iType;

  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {

    //Load our test file and get our tree population pointer
    p_oSimManager->ReadFile( WriteLinearBiLevelGrowthXMLFile4() );
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );

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

    //Now run growth
    p_oSimManager->RunSim(1);

    //Confirm all trees
    iIndex = 0;
    fExpectedDiam = 0.2012;
    fExpectedHeight = 0.19373548;
    EXPECT_EQ(clTreePopulation::seedling, p_oTrees[iIndex]->GetType());
    p_oTrees[iIndex]->GetValue(p_oPop->GetDiam10Code(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fDiam);
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedDiam = 0.206;
    fExpectedHeight = 0.1853382;
    EXPECT_EQ(clTreePopulation::seedling, p_oTrees[iIndex]->GetType());
    p_oTrees[iIndex]->GetValue(p_oPop->GetDiam10Code(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fDiam);
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedDiam = 0.5072;
    fExpectedHeight = 1.9562704;
    EXPECT_EQ(clTreePopulation::seedling, p_oTrees[iIndex]->GetType());
    p_oTrees[iIndex]->GetValue(p_oPop->GetDiam10Code(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fDiam);
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedDiam = 2.61008;
    fExpectedHeight = 4.2101;
    EXPECT_EQ(clTreePopulation::sapling, p_oTrees[iIndex]->GetType());
    p_oTrees[iIndex]->GetValue(p_oPop->GetDbhCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fDiam);
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedDiam = 3.502;
    fExpectedHeight = 5.474285714;
    EXPECT_EQ(clTreePopulation::sapling, p_oTrees[iIndex]->GetType());
    p_oTrees[iIndex]->GetValue(p_oPop->GetDbhCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fDiam);
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedDiam = 5.67078;
    fExpectedHeight = 9.089633333;
    EXPECT_EQ(clTreePopulation::sapling, p_oTrees[iIndex]->GetType());
    p_oTrees[iIndex]->GetValue(p_oPop->GetDbhCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fDiam);
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedDiam = 12.8512;
    fExpectedHeight = 13.5149736;
    EXPECT_EQ(clTreePopulation::adult, p_oTrees[iIndex]->GetType());
    p_oTrees[iIndex]->GetValue(p_oPop->GetDbhCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fDiam);
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedDiam = 46.556;
    fExpectedHeight = 27.10426602;
    EXPECT_EQ(clTreePopulation::adult, p_oTrees[iIndex]->GetType());
    p_oTrees[iIndex]->GetValue(p_oPop->GetDbhCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fDiam);
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedDiam = 24.0592;
    fExpectedHeight = 19.47199985;
    EXPECT_EQ(clTreePopulation::adult, p_oTrees[iIndex]->GetType());
    p_oTrees[iIndex]->GetValue(p_oPop->GetDbhCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fDiam);
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedDiam = 0.2012;
    fExpectedHeight = 0.19373548;
    EXPECT_EQ(clTreePopulation::seedling, p_oTrees[iIndex]->GetType());
    p_oTrees[iIndex]->GetValue(p_oPop->GetDiam10Code(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fDiam);
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedDiam = 0.206;
    fExpectedHeight = 0.1853382;
    EXPECT_EQ(clTreePopulation::seedling, p_oTrees[iIndex]->GetType());
    p_oTrees[iIndex]->GetValue(p_oPop->GetDiam10Code(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fDiam);
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedDiam = 0.5072;
    fExpectedHeight = 1.9562704;
    EXPECT_EQ(clTreePopulation::seedling, p_oTrees[iIndex]->GetType());
    p_oTrees[iIndex]->GetValue(p_oPop->GetDiam10Code(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fDiam);
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedDiam = 2.61008;
    fExpectedHeight = 4.2101;
    EXPECT_EQ(clTreePopulation::sapling, p_oTrees[iIndex]->GetType());
    p_oTrees[iIndex]->GetValue(p_oPop->GetDbhCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fDiam);
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedDiam = 3.502;
    fExpectedHeight = 5.474285714;
    EXPECT_EQ(clTreePopulation::sapling, p_oTrees[iIndex]->GetType());
    p_oTrees[iIndex]->GetValue(p_oPop->GetDbhCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fDiam);
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedDiam = 5.67078;
    fExpectedHeight = 9.089633333;
    EXPECT_EQ(clTreePopulation::sapling, p_oTrees[iIndex]->GetType());
    p_oTrees[iIndex]->GetValue(p_oPop->GetDbhCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fDiam);
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedDiam = 12.8512;
    fExpectedHeight = 13.5149736;
    EXPECT_EQ(clTreePopulation::adult, p_oTrees[iIndex]->GetType());
    p_oTrees[iIndex]->GetValue(p_oPop->GetDbhCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fDiam);
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedDiam = 46.556;
    fExpectedHeight = 27.10426602;
    EXPECT_EQ(clTreePopulation::adult, p_oTrees[iIndex]->GetType());
    p_oTrees[iIndex]->GetValue(p_oPop->GetDbhCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fDiam);
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedDiam = 24.0592;
    fExpectedHeight = 19.47199985;
    EXPECT_EQ(clTreePopulation::adult, p_oTrees[iIndex]->GetType());
    p_oTrees[iIndex]->GetValue(p_oPop->GetDbhCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fDiam);
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedDiam = 0.2012;
    fExpectedHeight = 0.19373548;
    EXPECT_EQ(clTreePopulation::seedling, p_oTrees[iIndex]->GetType());
    p_oTrees[iIndex]->GetValue(p_oPop->GetDiam10Code(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fDiam);
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedDiam = 0.206;
    fExpectedHeight = 0.1853382;
    EXPECT_EQ(clTreePopulation::seedling, p_oTrees[iIndex]->GetType());
    p_oTrees[iIndex]->GetValue(p_oPop->GetDiam10Code(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fDiam);
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedDiam = 0.5072;
    fExpectedHeight = 1.9562704;
    EXPECT_EQ(clTreePopulation::seedling, p_oTrees[iIndex]->GetType());
    p_oTrees[iIndex]->GetValue(p_oPop->GetDiam10Code(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fDiam);
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedDiam = 2.61008;
    fExpectedHeight = 4.2101;
    EXPECT_EQ(clTreePopulation::sapling, p_oTrees[iIndex]->GetType());
    p_oTrees[iIndex]->GetValue(p_oPop->GetDbhCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fDiam);
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedDiam = 3.502;
    fExpectedHeight = 5.474285714;
    EXPECT_EQ(clTreePopulation::sapling, p_oTrees[iIndex]->GetType());
    p_oTrees[iIndex]->GetValue(p_oPop->GetDbhCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fDiam);
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedDiam = 5.67078;
    fExpectedHeight = 9.089633333;
    EXPECT_EQ(clTreePopulation::sapling, p_oTrees[iIndex]->GetType());
    p_oTrees[iIndex]->GetValue(p_oPop->GetDbhCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fDiam);
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedDiam = 12.8512;
    fExpectedHeight = 13.5149736;
    EXPECT_EQ(clTreePopulation::adult, p_oTrees[iIndex]->GetType());
    p_oTrees[iIndex]->GetValue(p_oPop->GetDbhCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fDiam);
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedDiam = 46.556;
    fExpectedHeight = 27.10426602;
    EXPECT_EQ(clTreePopulation::adult, p_oTrees[iIndex]->GetType());
    p_oTrees[iIndex]->GetValue(p_oPop->GetDbhCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fDiam);
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedDiam = 24.0592;
    fExpectedHeight = 19.47199985;
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
TEST(LinearBiLevelGrowth, ErrorProcessing)
{
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try
  {
    p_oSimManager->ReadFile( WriteLinearBiLevelGrowthXMLErrorFile1() );
    FAIL() << "TestLinearBiLevelGrowth error processing didn't catch error for WriteLinearBiLevelGrowthXMLErrorFile1.";
  }
  catch ( modelErr& err )
  {
    if ( err.sFunction.compare("clLinearBiLevelGrowth::DoShellSetup" ) != 0 )
    {
      FAIL() << "TestLinearBiLevelGrowth error processing caught wrong error for WriteLinearBiLevelGrowthXMLErrorFile1.";
    }
    ;
  }
  delete p_oSimManager;
}

////////////////////////////////////////////////////////////////////////////
// WriteLinearBiLevelGrowthXMLFile1()
////////////////////////////////////////////////////////////////////////////
const char* WriteLinearBiLevelGrowthXMLFile1() {
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

  WriteLinearBiLevelGrowthCommonStuff(oOut);

  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>StormLight</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>LinearBilevelGrowth</behaviorName>"
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

  WriteLinearBiLevelGrowthGrowthParameters(oOut);
  oOut << "</paramFile>";

  oOut.close();

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteLinearBiLevelGrowthXMLFile2()
////////////////////////////////////////////////////////////////////////////
const char* WriteLinearBiLevelGrowthXMLFile2() {
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

  WriteLinearBiLevelGrowthCommonStuff(oOut);

  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>StormLight</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>LinearBilevelGrowth</behaviorName>"
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

  WriteLinearBiLevelGrowthGrowthParameters(oOut);
  oOut << "</paramFile>";

  oOut.close();

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteLinearBiLevelGrowthXMLFile3()
////////////////////////////////////////////////////////////////////////////
const char* WriteLinearBiLevelGrowthXMLFile3() {
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

  WriteLinearBiLevelGrowthCommonStuff(oOut);

  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>StormLight</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>LinearBilevelGrowth diam only</behaviorName>"
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
       << "<behavior>"
       << "<behaviorName>HeightIncrementer</behaviorName>"
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
       << "<StormLight1>"
       << "<li_stormLightRadius>15</li_stormLightRadius>"
       << "<li_stormLightSlope>-4</li_stormLightSlope>"
       << "<li_stormLightIntercept>95</li_stormLightIntercept>"
       << "<li_stormLightMaxDmgTime>3</li_stormLightMaxDmgTime>"
       << "<li_stormLightSnagMaxDmgTime>2</li_stormLightSnagMaxDmgTime>"
       << "<li_stormLightStoch>0</li_stormLightStoch>"
       << "<li_stormLightMinFullCanopy>9</li_stormLightMinFullCanopy>"
       << "</StormLight1>";

  WriteLinearBiLevelGrowthGrowthParameters(oOut);
  oOut << "</paramFile>";

  oOut.close();

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteLinearBiLevelGrowthXMLFile4()
////////////////////////////////////////////////////////////////////////////
const char* WriteLinearBiLevelGrowthXMLFile4() {
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

  WriteLinearBiLevelGrowthCommonStuff(oOut);

  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>LinearBilevelGrowth</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
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
       << "</behaviorList>";

  oOut << "<LinearBilevelGrowth1>"
       << "<gr_linearBilevLoLiteIntercept>"
       << "<gr_lblliVal species=\"Species_1\">0.1</gr_lblliVal>"
       << "<gr_lblliVal species=\"Species_2\">0</gr_lblliVal>"
       << "<gr_lblliVal species=\"Species_4\">0.2</gr_lblliVal>"
       << "</gr_linearBilevLoLiteIntercept>"
       << "<gr_linearBilevLoLiteSlope>"
       << "<gr_lbllsVal species=\"Species_1\">0.012</gr_lbllsVal>"
       << "<gr_lbllsVal species=\"Species_2\">0.03</gr_lbllsVal>"
       << "<gr_lbllsVal species=\"Species_4\">0.024</gr_lbllsVal>"
       << "</gr_linearBilevLoLiteSlope>"
       << "</LinearBilevelGrowth1>";
  oOut << "</paramFile>";

  oOut.close();

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteLinearBiLevelGrowthXMLErrorFile1()
////////////////////////////////////////////////////////////////////////////
const char* WriteLinearBiLevelGrowthXMLErrorFile1() {
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

  WriteLinearBiLevelGrowthCommonStuff(oOut);

  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>StormLight</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>LinearBilevelGrowth</behaviorName>"
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

  oOut << "<LinearBilevelGrowth2>"
       << "<gr_linearBilevLoLiteIntercept>"
       << "<gr_lblliVal species=\"Species_1\">0.1</gr_lblliVal>"
       << "<gr_lblliVal species=\"Species_2\">0</gr_lblliVal>"
       << "<gr_lblliVal species=\"Species_4\">0.2</gr_lblliVal>"
       << "</gr_linearBilevLoLiteIntercept>"
       << "<gr_linearBilevHiLiteIntercept>"
       << "<gr_lbhliVal species=\"Species_1\">0.3</gr_lbhliVal>"
       << "<gr_lbhliVal species=\"Species_2\">0.4</gr_lbhliVal>"
       << "<gr_lbhliVal species=\"Species_4\">0.5</gr_lbhliVal>"
       << "</gr_linearBilevHiLiteIntercept>"
       << "<gr_linearBilevLoLiteSlope>"
       << "<gr_lbllsVal species=\"Species_1\">0.012</gr_lbllsVal>"
       << "<gr_lbllsVal species=\"Species_2\">0.03</gr_lbllsVal>"
       << "<gr_lbllsVal species=\"Species_4\">0.024</gr_lbllsVal>"
       << "</gr_linearBilevLoLiteSlope>"
       << "<gr_linearBilevHiLiteSlope>"
       << "<gr_lbhlsVal species=\"Species_1\">0.045</gr_lbhlsVal>"
       << "<gr_lbhlsVal species=\"Species_2\">0.056</gr_lbhlsVal>"
       << "<gr_lbhlsVal species=\"Species_4\">0.067</gr_lbhlsVal>"
       << "</gr_linearBilevHiLiteSlope>"
       << "<gr_linearBilevHiLiteThreshold>"
       << "<gr_lbhltVal species=\"Species_1\">120</gr_lbhltVal>"
       << "<gr_lbhltVal species=\"Species_2\">50</gr_lbhltVal>"
       << "<gr_lbhltVal species=\"Species_4\">70</gr_lbhltVal>"
       << "</gr_linearBilevHiLiteThreshold>"
       << "</LinearBilevelGrowth2>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteLinearBiLevelGrowthCommonStuff()
/////////////////////////////////////////////////////////////////////////////
void WriteLinearBiLevelGrowthCommonStuff(std::fstream &oOut)
{
  using namespace std;
  oOut << "<randomSeed>1</randomSeed>"
       << "<plot_lenX>100</plot_lenX>"
       << "<plot_lenY>100</plot_lenY>"
       << "<plot_latitude>55.37</plot_latitude>"
       << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
       << "<plot_temp_C>12.88171785</plot_temp_C>"
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
// WriteLinearBiLevelGrowthGrowthParameters()
/////////////////////////////////////////////////////////////////////////////
void WriteLinearBiLevelGrowthGrowthParameters(std::fstream &oOut)
{
  using namespace std;
  oOut << "<LinearBilevelGrowth2>"
       << "<gr_linearBilevLoLiteIntercept>"
       << "<gr_lblliVal species=\"Species_1\">0.1</gr_lblliVal>"
       << "<gr_lblliVal species=\"Species_2\">0</gr_lblliVal>"
       << "<gr_lblliVal species=\"Species_4\">0.2</gr_lblliVal>"
       << "</gr_linearBilevLoLiteIntercept>"
       << "<gr_linearBilevHiLiteIntercept>"
       << "<gr_lbhliVal species=\"Species_1\">0.3</gr_lbhliVal>"
       << "<gr_lbhliVal species=\"Species_2\">0.4</gr_lbhliVal>"
       << "<gr_lbhliVal species=\"Species_4\">0.5</gr_lbhliVal>"
       << "</gr_linearBilevHiLiteIntercept>"
       << "<gr_linearBilevLoLiteSlope>"
       << "<gr_lbllsVal species=\"Species_1\">0.012</gr_lbllsVal>"
       << "<gr_lbllsVal species=\"Species_2\">0.03</gr_lbllsVal>"
       << "<gr_lbllsVal species=\"Species_4\">0.024</gr_lbllsVal>"
       << "</gr_linearBilevLoLiteSlope>"
       << "<gr_linearBilevHiLiteSlope>"
       << "<gr_lbhlsVal species=\"Species_1\">0.045</gr_lbhlsVal>"
       << "<gr_lbhlsVal species=\"Species_2\">0.056</gr_lbhlsVal>"
       << "<gr_lbhlsVal species=\"Species_4\">0.067</gr_lbhlsVal>"
       << "</gr_linearBilevHiLiteSlope>"
       << "<gr_linearBilevHiLiteThreshold>"
       << "<gr_lbhltVal species=\"Species_1\">20</gr_lbhltVal>"
       << "<gr_lbhltVal species=\"Species_2\">50</gr_lbhltVal>"
       << "<gr_lbhltVal species=\"Species_4\">70</gr_lbhltVal>"
       << "</gr_linearBilevHiLiteThreshold>"
       << "</LinearBilevelGrowth2>";
}
