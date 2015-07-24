//---------------------------------------------------------------------------
// TestLogBiLevelGrowth.cpp
//---------------------------------------------------------------------------
#include "TestLogBiLevelGrowth.h"
#include <gtest/gtest.h>
#include <fstream>
#include <math.h>
#include "TreePopulation.h"
#include "SimManager.h"
#include "BehaviorBase.h"
#include "Grid.h"

////////////////////////////////////////////////////////////////////////////
// NormalProcessingRun1()
// Tests normal processing run 1. WriteLogBiLevelGrowthXMLFile1() does setup.
// Timestep length is 1 year and there is a light grid present. 27 trees are
// created of 3 species and assigned to a mix of light levels. Then growth is
// run. Their heights are checked to make sure they are correct.
////////////////////////////////////////////////////////////////////////////
TEST(LogBiLevelGrowth, NormalProcessingRun1) {
  clTreePopulation * p_oPop;
  clGrid *p_oStormLight;
  clTree **p_oTrees = new clTree*[27];
  float fDiam, fHeight, fExpectedHeight;
  int iIndex, iSpecies, iType;

  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {

    //Load our test file and get our tree population and grid pointers
    p_oSimManager->ReadFile( WriteLogBiLevelGrowthXMLFile1() );
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
    p_oTrees[iIndex]->SetValue(p_oPop->GetHeightCode(iSpecies, iType), fDiam);
    iIndex++;

    fDiam = 0.2;
    iSpecies = 1;
    iType = clTreePopulation::seedling;
    p_oTrees[iIndex] = p_oPop->CreateTree(1, 1, iSpecies, iType, fDiam);
    p_oTrees[iIndex]->SetValue(p_oPop->GetHeightCode(iSpecies, iType), fDiam);
    iIndex++;

    fDiam = 0.3;
    iSpecies = 3;
    iType = clTreePopulation::seedling;
    p_oTrees[iIndex] = p_oPop->CreateTree(1, 1, iSpecies, iType, fDiam);
    p_oTrees[iIndex]->SetValue(p_oPop->GetHeightCode(iSpecies, iType), fDiam);
    iIndex++;

    fDiam = 2.5;
    iSpecies = 0;
    iType = clTreePopulation::sapling;
    p_oTrees[iIndex] = p_oPop->CreateTree(1, 1, iSpecies, iType, fDiam);
    p_oTrees[iIndex]->SetValue(p_oPop->GetHeightCode(iSpecies, iType), fDiam);
    iIndex++;

    fDiam = 3.4;
    iSpecies = 1;
    iType = clTreePopulation::sapling;
    p_oTrees[iIndex] = p_oPop->CreateTree(1, 1, iSpecies, iType, fDiam);
    p_oTrees[iIndex]->SetValue(p_oPop->GetHeightCode(iSpecies, iType), fDiam);
    iIndex++;

    fDiam = 5.4;
    iSpecies = 3;
    iType = clTreePopulation::sapling;
    p_oTrees[iIndex] = p_oPop->CreateTree(1, 1, iSpecies, iType, fDiam);
    p_oTrees[iIndex]->SetValue(p_oPop->GetHeightCode(iSpecies, iType), fDiam);
    iIndex++;

    fDiam = 12.6;
    iSpecies = 0;
    iType = clTreePopulation::adult;
    p_oTrees[iIndex] = p_oPop->CreateTree(1, 1, iSpecies, iType, fDiam);
    p_oTrees[iIndex]->SetValue(p_oPop->GetHeightCode(iSpecies, iType), fDiam);
    iIndex++;

    fDiam = 45.2;
    iSpecies = 1;
    iType = clTreePopulation::adult;
    p_oTrees[iIndex] = p_oPop->CreateTree(1, 1, iSpecies, iType, fDiam);
    p_oTrees[iIndex]->SetValue(p_oPop->GetHeightCode(iSpecies, iType), fDiam);
    iIndex++;

    fDiam = 23.3;
    iSpecies = 3;
    iType = clTreePopulation::adult;
    p_oTrees[iIndex] = p_oPop->CreateTree(1, 1, iSpecies, iType, fDiam);
    p_oTrees[iIndex]->SetValue(p_oPop->GetHeightCode(iSpecies, iType), fDiam);
    iIndex++;

    fDiam = 0.1;
    iSpecies = 0;
    iType = clTreePopulation::seedling;
    p_oTrees[iIndex] = p_oPop->CreateTree(1, 9, iSpecies, iType, fDiam);
    p_oTrees[iIndex]->SetValue(p_oPop->GetHeightCode(iSpecies, iType), fDiam);
    iIndex++;

    fDiam = 0.2;
    iSpecies = 1;
    iType = clTreePopulation::seedling;
    p_oTrees[iIndex] = p_oPop->CreateTree(1, 9, iSpecies, iType, fDiam);
    p_oTrees[iIndex]->SetValue(p_oPop->GetHeightCode(iSpecies, iType), fDiam);
    iIndex++;

    fDiam = 0.3;
    iSpecies = 3;
    iType = clTreePopulation::seedling;
    p_oTrees[iIndex] = p_oPop->CreateTree(1, 9, iSpecies, iType, fDiam);
    p_oTrees[iIndex]->SetValue(p_oPop->GetHeightCode(iSpecies, iType), fDiam);
    iIndex++;

    fDiam = 2.5;
    iSpecies = 0;
    iType = clTreePopulation::sapling;
    p_oTrees[iIndex] = p_oPop->CreateTree(1, 9, iSpecies, iType, fDiam);
    p_oTrees[iIndex]->SetValue(p_oPop->GetHeightCode(iSpecies, iType), fDiam);
    iIndex++;

    fDiam = 3.4;
    iSpecies = 1;
    iType = clTreePopulation::sapling;
    p_oTrees[iIndex] = p_oPop->CreateTree(1, 9, iSpecies, iType, fDiam);
    p_oTrees[iIndex]->SetValue(p_oPop->GetHeightCode(iSpecies, iType), fDiam);
    iIndex++;

    fDiam = 5.4;
    iSpecies = 3;
    iType = clTreePopulation::sapling;
    p_oTrees[iIndex] = p_oPop->CreateTree(1, 9, iSpecies, iType, fDiam);
    p_oTrees[iIndex]->SetValue(p_oPop->GetHeightCode(iSpecies, iType), fDiam);
    iIndex++;

    fDiam = 12.6;
    iSpecies = 0;
    iType = clTreePopulation::adult;
    p_oTrees[iIndex] = p_oPop->CreateTree(1, 9, iSpecies, iType, fDiam);
    p_oTrees[iIndex]->SetValue(p_oPop->GetHeightCode(iSpecies, iType), fDiam);
    iIndex++;

    fDiam = 45.2;
    iSpecies = 1;
    iType = clTreePopulation::adult;
    p_oTrees[iIndex] = p_oPop->CreateTree(1, 9, iSpecies, iType, fDiam);
    p_oTrees[iIndex]->SetValue(p_oPop->GetHeightCode(iSpecies, iType), fDiam);
    iIndex++;

    fDiam = 23.3;
    iSpecies = 3;
    iType = clTreePopulation::adult;
    p_oTrees[iIndex] = p_oPop->CreateTree(1, 9, iSpecies, iType, fDiam);
    p_oTrees[iIndex]->SetValue(p_oPop->GetHeightCode(iSpecies, iType), fDiam);
    iIndex++;

    fDiam = 0.1;
    iSpecies = 0;
    iType = clTreePopulation::seedling;
    p_oTrees[iIndex] = p_oPop->CreateTree(1, 17, iSpecies, iType, fDiam);
    p_oTrees[iIndex]->SetValue(p_oPop->GetHeightCode(iSpecies, iType), fDiam);
    iIndex++;

    fDiam = 0.2;
    iSpecies = 1;
    iType = clTreePopulation::seedling;
    p_oTrees[iIndex] = p_oPop->CreateTree(1, 17, iSpecies, iType, fDiam);
    p_oTrees[iIndex]->SetValue(p_oPop->GetHeightCode(iSpecies, iType), fDiam);
    iIndex++;

    fDiam = 0.3;
    iSpecies = 3;
    iType = clTreePopulation::seedling;
    p_oTrees[iIndex] = p_oPop->CreateTree(1, 17, iSpecies, iType, fDiam);
    p_oTrees[iIndex]->SetValue(p_oPop->GetHeightCode(iSpecies, iType), fDiam);
    iIndex++;

    fDiam = 2.5;
    iSpecies = 0;
    iType = clTreePopulation::sapling;
    p_oTrees[iIndex] = p_oPop->CreateTree(1, 17, iSpecies, iType, fDiam);
    p_oTrees[iIndex]->SetValue(p_oPop->GetHeightCode(iSpecies, iType), fDiam);
    iIndex++;

    fDiam = 3.4;
    iSpecies = 1;
    iType = clTreePopulation::sapling;
    p_oTrees[iIndex] = p_oPop->CreateTree(1, 17, iSpecies, iType, fDiam);
    p_oTrees[iIndex]->SetValue(p_oPop->GetHeightCode(iSpecies, iType), fDiam);
    iIndex++;

    fDiam = 5.4;
    iSpecies = 3;
    iType = clTreePopulation::sapling;
    p_oTrees[iIndex] = p_oPop->CreateTree(1, 17, iSpecies, iType, fDiam);
    p_oTrees[iIndex]->SetValue(p_oPop->GetHeightCode(iSpecies, iType), fDiam);
    iIndex++;

    fDiam = 12.6;
    iSpecies = 0;
    iType = clTreePopulation::adult;
    p_oTrees[iIndex] = p_oPop->CreateTree(1, 17, iSpecies, iType, fDiam);
    p_oTrees[iIndex]->SetValue(p_oPop->GetHeightCode(iSpecies, iType), fDiam);
    iIndex++;

    fDiam = 45.2;
    iSpecies = 1;
    iType = clTreePopulation::adult;
    p_oTrees[iIndex] = p_oPop->CreateTree(1, 17, iSpecies, iType, fDiam);
    p_oTrees[iIndex]->SetValue(p_oPop->GetHeightCode(iSpecies, iType), fDiam);
    iIndex++;

    fDiam = 23.3;
    iSpecies = 3;
    iType = clTreePopulation::adult;
    p_oTrees[iIndex] = p_oPop->CreateTree(1, 17, iSpecies, iType, fDiam);
    p_oTrees[iIndex]->SetValue(p_oPop->GetHeightCode(iSpecies, iType), fDiam);
    iIndex++;

    //Now run growth, but skip storm light
    int i;
    for (i = 1; i < p_oSimManager->GetNumberOfBehaviors(); i++) {
      clBehaviorBase *p_oBase = p_oSimManager->GetBehaviorObject(i);
      p_oBase->Action();
    }

    //Confirm all trees
    iIndex = 0;
    fExpectedHeight = 0.163229353;
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedHeight = 0.232478126;
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedHeight = 0.303195532;
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedHeight = 2.595198013;
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedHeight = 3.55586166;
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedHeight = 5.51536841;
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedHeight = 12.69999524;
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedHeight = 45.38534401;
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedHeight = 23.44285874;
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedHeight = 0.288584278;
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedHeight = 0.232478126;
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedHeight = 0.303195532;
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedHeight = 2.727679018;
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedHeight = 3.55586166;
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedHeight = 5.51536841;
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedHeight = 12.82879175;
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedHeight = 45.38534401;
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedHeight = 23.44285874;
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedHeight = 0.288584278;
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedHeight = 0.484835377;
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedHeight = 0.383113573;
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedHeight = 2.727679018;
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedHeight = 3.738652909;
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedHeight = 5.569690561;
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedHeight = 12.82879175;
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedHeight = 45.51716191;
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedHeight = 23.43342813;
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

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
// Tests normal processing run 2. WriteLogBiLevelGrowthXMLFile2() does setup.
// Timestep length is 3 years and there is a light grid present. 27 trees are
// created of 3 species and assigned to a mix of light levels. Then growth is
// run. Their heights are checked to make sure they are correct.
////////////////////////////////////////////////////////////////////////////
TEST(LogBiLevelGrowth, NormalProcessingRun2) {
  clTreePopulation * p_oPop;
  clGrid *p_oStormLight;
  clTree **p_oTrees = new clTree*[27];
  float fDiam, fHeight, fExpectedHeight;
  int iIndex, iSpecies, iType;

  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {

    //Load our test file and get our tree population and grid pointers
    p_oSimManager->ReadFile( WriteLogBiLevelGrowthXMLFile2() );
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
    p_oTrees[iIndex]->SetValue(p_oPop->GetHeightCode(iSpecies, iType), fDiam);
    iIndex++;

    fDiam = 0.2;
    iSpecies = 1;
    iType = clTreePopulation::seedling;
    p_oTrees[iIndex] = p_oPop->CreateTree(1, 1, iSpecies, iType, fDiam);
    p_oTrees[iIndex]->SetValue(p_oPop->GetHeightCode(iSpecies, iType), fDiam);
    iIndex++;

    fDiam = 0.3;
    iSpecies = 3;
    iType = clTreePopulation::seedling;
    p_oTrees[iIndex] = p_oPop->CreateTree(1, 1, iSpecies, iType, fDiam);
    p_oTrees[iIndex]->SetValue(p_oPop->GetHeightCode(iSpecies, iType), fDiam);
    iIndex++;

    fDiam = 2.5;
    iSpecies = 0;
    iType = clTreePopulation::sapling;
    p_oTrees[iIndex] = p_oPop->CreateTree(1, 1, iSpecies, iType, fDiam);
    p_oTrees[iIndex]->SetValue(p_oPop->GetHeightCode(iSpecies, iType), fDiam);
    iIndex++;

    fDiam = 3.4;
    iSpecies = 1;
    iType = clTreePopulation::sapling;
    p_oTrees[iIndex] = p_oPop->CreateTree(1, 1, iSpecies, iType, fDiam);
    p_oTrees[iIndex]->SetValue(p_oPop->GetHeightCode(iSpecies, iType), fDiam);
    iIndex++;

    fDiam = 5.4;
    iSpecies = 3;
    iType = clTreePopulation::sapling;
    p_oTrees[iIndex] = p_oPop->CreateTree(1, 1, iSpecies, iType, fDiam);
    p_oTrees[iIndex]->SetValue(p_oPop->GetHeightCode(iSpecies, iType), fDiam);
    iIndex++;

    fDiam = 12.6;
    iSpecies = 0;
    iType = clTreePopulation::adult;
    p_oTrees[iIndex] = p_oPop->CreateTree(1, 1, iSpecies, iType, fDiam);
    p_oTrees[iIndex]->SetValue(p_oPop->GetHeightCode(iSpecies, iType), fDiam);
    iIndex++;

    fDiam = 45.2;
    iSpecies = 1;
    iType = clTreePopulation::adult;
    p_oTrees[iIndex] = p_oPop->CreateTree(1, 1, iSpecies, iType, fDiam);
    p_oTrees[iIndex]->SetValue(p_oPop->GetHeightCode(iSpecies, iType), fDiam);
    iIndex++;

    fDiam = 23.3;
    iSpecies = 3;
    iType = clTreePopulation::adult;
    p_oTrees[iIndex] = p_oPop->CreateTree(1, 1, iSpecies, iType, fDiam);
    p_oTrees[iIndex]->SetValue(p_oPop->GetHeightCode(iSpecies, iType), fDiam);
    iIndex++;

    fDiam = 0.1;
    iSpecies = 0;
    iType = clTreePopulation::seedling;
    p_oTrees[iIndex] = p_oPop->CreateTree(1, 9, iSpecies, iType, fDiam);
    p_oTrees[iIndex]->SetValue(p_oPop->GetHeightCode(iSpecies, iType), fDiam);
    iIndex++;

    fDiam = 0.2;
    iSpecies = 1;
    iType = clTreePopulation::seedling;
    p_oTrees[iIndex] = p_oPop->CreateTree(1, 9, iSpecies, iType, fDiam);
    p_oTrees[iIndex]->SetValue(p_oPop->GetHeightCode(iSpecies, iType), fDiam);
    iIndex++;

    fDiam = 0.3;
    iSpecies = 3;
    iType = clTreePopulation::seedling;
    p_oTrees[iIndex] = p_oPop->CreateTree(1, 9, iSpecies, iType, fDiam);
    p_oTrees[iIndex]->SetValue(p_oPop->GetHeightCode(iSpecies, iType), fDiam);
    iIndex++;

    fDiam = 2.5;
    iSpecies = 0;
    iType = clTreePopulation::sapling;
    p_oTrees[iIndex] = p_oPop->CreateTree(1, 9, iSpecies, iType, fDiam);
    p_oTrees[iIndex]->SetValue(p_oPop->GetHeightCode(iSpecies, iType), fDiam);
    iIndex++;

    fDiam = 3.4;
    iSpecies = 1;
    iType = clTreePopulation::sapling;
    p_oTrees[iIndex] = p_oPop->CreateTree(1, 9, iSpecies, iType, fDiam);
    p_oTrees[iIndex]->SetValue(p_oPop->GetHeightCode(iSpecies, iType), fDiam);
    iIndex++;

    fDiam = 5.4;
    iSpecies = 3;
    iType = clTreePopulation::sapling;
    p_oTrees[iIndex] = p_oPop->CreateTree(1, 9, iSpecies, iType, fDiam);
    p_oTrees[iIndex]->SetValue(p_oPop->GetHeightCode(iSpecies, iType), fDiam);
    iIndex++;

    fDiam = 12.6;
    iSpecies = 0;
    iType = clTreePopulation::adult;
    p_oTrees[iIndex] = p_oPop->CreateTree(1, 9, iSpecies, iType, fDiam);
    p_oTrees[iIndex]->SetValue(p_oPop->GetHeightCode(iSpecies, iType), fDiam);
    iIndex++;

    fDiam = 45.2;
    iSpecies = 1;
    iType = clTreePopulation::adult;
    p_oTrees[iIndex] = p_oPop->CreateTree(1, 9, iSpecies, iType, fDiam);
    p_oTrees[iIndex]->SetValue(p_oPop->GetHeightCode(iSpecies, iType), fDiam);
    iIndex++;

    fDiam = 23.3;
    iSpecies = 3;
    iType = clTreePopulation::adult;
    p_oTrees[iIndex] = p_oPop->CreateTree(1, 9, iSpecies, iType, fDiam);
    p_oTrees[iIndex]->SetValue(p_oPop->GetHeightCode(iSpecies, iType), fDiam);
    iIndex++;

    fDiam = 0.1;
    iSpecies = 0;
    iType = clTreePopulation::seedling;
    p_oTrees[iIndex] = p_oPop->CreateTree(1, 17, iSpecies, iType, fDiam);
    p_oTrees[iIndex]->SetValue(p_oPop->GetHeightCode(iSpecies, iType), fDiam);
    iIndex++;

    fDiam = 0.2;
    iSpecies = 1;
    iType = clTreePopulation::seedling;
    p_oTrees[iIndex] = p_oPop->CreateTree(1, 17, iSpecies, iType, fDiam);
    p_oTrees[iIndex]->SetValue(p_oPop->GetHeightCode(iSpecies, iType), fDiam);
    iIndex++;

    fDiam = 0.3;
    iSpecies = 3;
    iType = clTreePopulation::seedling;
    p_oTrees[iIndex] = p_oPop->CreateTree(1, 17, iSpecies, iType, fDiam);
    p_oTrees[iIndex]->SetValue(p_oPop->GetHeightCode(iSpecies, iType), fDiam);
    iIndex++;

    fDiam = 2.5;
    iSpecies = 0;
    iType = clTreePopulation::sapling;
    p_oTrees[iIndex] = p_oPop->CreateTree(1, 17, iSpecies, iType, fDiam);
    p_oTrees[iIndex]->SetValue(p_oPop->GetHeightCode(iSpecies, iType), fDiam);
    iIndex++;

    fDiam = 3.4;
    iSpecies = 1;
    iType = clTreePopulation::sapling;
    p_oTrees[iIndex] = p_oPop->CreateTree(1, 17, iSpecies, iType, fDiam);
    p_oTrees[iIndex]->SetValue(p_oPop->GetHeightCode(iSpecies, iType), fDiam);
    iIndex++;

    fDiam = 5.4;
    iSpecies = 3;
    iType = clTreePopulation::sapling;
    p_oTrees[iIndex] = p_oPop->CreateTree(1, 17, iSpecies, iType, fDiam);
    p_oTrees[iIndex]->SetValue(p_oPop->GetHeightCode(iSpecies, iType), fDiam);
    iIndex++;

    fDiam = 12.6;
    iSpecies = 0;
    iType = clTreePopulation::adult;
    p_oTrees[iIndex] = p_oPop->CreateTree(1, 17, iSpecies, iType, fDiam);
    p_oTrees[iIndex]->SetValue(p_oPop->GetHeightCode(iSpecies, iType), fDiam);
    iIndex++;

    fDiam = 45.2;
    iSpecies = 1;
    iType = clTreePopulation::adult;
    p_oTrees[iIndex] = p_oPop->CreateTree(1, 17, iSpecies, iType, fDiam);
    p_oTrees[iIndex]->SetValue(p_oPop->GetHeightCode(iSpecies, iType), fDiam);
    iIndex++;

    fDiam = 23.3;
    iSpecies = 3;
    iType = clTreePopulation::adult;
    p_oTrees[iIndex] = p_oPop->CreateTree(1, 17, iSpecies, iType, fDiam);
    p_oTrees[iIndex]->SetValue(p_oPop->GetHeightCode(iSpecies, iType), fDiam);
    iIndex++;

    //Now run growth, but skip storm light
    int i;
    for (i = 1; i < p_oSimManager->GetNumberOfBehaviors(); i++) {
      clBehaviorBase *p_oBase = p_oSimManager->GetBehaviorObject(i);
      p_oBase->Action();
    }

    //Confirm all trees
    iIndex = 0;
    fExpectedHeight = 0.28968806;
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedHeight = 0.297434377;
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedHeight = 0.309586595;
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedHeight = 2.785594039;
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedHeight = 3.867584981;
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedHeight = 5.74610523;
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedHeight = 12.89998572;
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedHeight = 45.75603202;
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedHeight = 23.72857623;
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedHeight = 0.665752834;
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedHeight = 0.297434377;
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedHeight = 0.309586595;
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedHeight = 3.183037053;
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedHeight = 3.867584981;
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedHeight = 5.74610523;
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedHeight = 13.28637526;
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedHeight = 45.75603202;
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedHeight = 23.72857623;
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedHeight = 0.665752834;
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedHeight = 1.05450613;
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedHeight = 0.549340719;
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedHeight = 3.183037053;
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedHeight = 4.415958728;
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedHeight = 5.909071684;
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedHeight = 13.28637526;
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedHeight = 46;
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedHeight = 23.70028438;
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

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
// Tests normal processing run 3. WriteLogBiLevelGrowthXMLFile3() does setup. Timestep
// length is 1 year and there is no light grid present. 27 trees are created
// of 3 species. Then growth is run. Their heights are checked to make sure
// they are correct.
////////////////////////////////////////////////////////////////////////////
TEST(LogBiLevelGrowth, NormalProcessingRun3) {
  clTreePopulation * p_oPop;
  clTree **p_oTrees = new clTree*[27];
  float fDiam, fHeight, fExpectedHeight;
  int iIndex, iSpecies, iType;

  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    //Load our test file and get our tree population and grid pointers
    p_oSimManager->ReadFile( WriteLogBiLevelGrowthXMLFile3() );
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );

    //Create our trees
    iIndex = 0;

    fDiam = 0.1;
    iSpecies = 0;
    iType = clTreePopulation::seedling;
    p_oTrees[iIndex] = p_oPop->CreateTree(1, 1, iSpecies, iType, fDiam);
    p_oTrees[iIndex]->SetValue(p_oPop->GetHeightCode(iSpecies, iType), fDiam);
    iIndex++;

    fDiam = 0.2;
    iSpecies = 1;
    iType = clTreePopulation::seedling;
    p_oTrees[iIndex] = p_oPop->CreateTree(1, 1, iSpecies, iType, fDiam);
    p_oTrees[iIndex]->SetValue(p_oPop->GetHeightCode(iSpecies, iType), fDiam);
    iIndex++;

    fDiam = 0.3;
    iSpecies = 3;
    iType = clTreePopulation::seedling;
    p_oTrees[iIndex] = p_oPop->CreateTree(1, 1, iSpecies, iType, fDiam);
    p_oTrees[iIndex]->SetValue(p_oPop->GetHeightCode(iSpecies, iType), fDiam);
    iIndex++;

    fDiam = 2.5;
    iSpecies = 0;
    iType = clTreePopulation::sapling;
    p_oTrees[iIndex] = p_oPop->CreateTree(1, 1, iSpecies, iType, fDiam);
    p_oTrees[iIndex]->SetValue(p_oPop->GetHeightCode(iSpecies, iType), fDiam);
    iIndex++;

    fDiam = 3.4;
    iSpecies = 1;
    iType = clTreePopulation::sapling;
    p_oTrees[iIndex] = p_oPop->CreateTree(1, 1, iSpecies, iType, fDiam);
    p_oTrees[iIndex]->SetValue(p_oPop->GetHeightCode(iSpecies, iType), fDiam);
    iIndex++;

    fDiam = 5.4;
    iSpecies = 3;
    iType = clTreePopulation::sapling;
    p_oTrees[iIndex] = p_oPop->CreateTree(1, 1, iSpecies, iType, fDiam);
    p_oTrees[iIndex]->SetValue(p_oPop->GetHeightCode(iSpecies, iType), fDiam);
    iIndex++;

    fDiam = 12.6;
    iSpecies = 0;
    iType = clTreePopulation::adult;
    p_oTrees[iIndex] = p_oPop->CreateTree(1, 1, iSpecies, iType, fDiam);
    p_oTrees[iIndex]->SetValue(p_oPop->GetHeightCode(iSpecies, iType), fDiam);
    iIndex++;

    fDiam = 45.2;
    iSpecies = 1;
    iType = clTreePopulation::adult;
    p_oTrees[iIndex] = p_oPop->CreateTree(1, 1, iSpecies, iType, fDiam);
    p_oTrees[iIndex]->SetValue(p_oPop->GetHeightCode(iSpecies, iType), fDiam);
    iIndex++;

    fDiam = 23.3;
    iSpecies = 3;
    iType = clTreePopulation::adult;
    p_oTrees[iIndex] = p_oPop->CreateTree(1, 1, iSpecies, iType, fDiam);
    p_oTrees[iIndex]->SetValue(p_oPop->GetHeightCode(iSpecies, iType), fDiam);
    iIndex++;

    fDiam = 0.1;
    iSpecies = 0;
    iType = clTreePopulation::seedling;
    p_oTrees[iIndex] = p_oPop->CreateTree(1, 9, iSpecies, iType, fDiam);
    p_oTrees[iIndex]->SetValue(p_oPop->GetHeightCode(iSpecies, iType), fDiam);
    iIndex++;

    fDiam = 0.2;
    iSpecies = 1;
    iType = clTreePopulation::seedling;
    p_oTrees[iIndex] = p_oPop->CreateTree(1, 9, iSpecies, iType, fDiam);
    p_oTrees[iIndex]->SetValue(p_oPop->GetHeightCode(iSpecies, iType), fDiam);
    iIndex++;

    fDiam = 0.3;
    iSpecies = 3;
    iType = clTreePopulation::seedling;
    p_oTrees[iIndex] = p_oPop->CreateTree(1, 9, iSpecies, iType, fDiam);
    p_oTrees[iIndex]->SetValue(p_oPop->GetHeightCode(iSpecies, iType), fDiam);
    iIndex++;

    fDiam = 2.5;
    iSpecies = 0;
    iType = clTreePopulation::sapling;
    p_oTrees[iIndex] = p_oPop->CreateTree(1, 9, iSpecies, iType, fDiam);
    p_oTrees[iIndex]->SetValue(p_oPop->GetHeightCode(iSpecies, iType), fDiam);
    iIndex++;

    fDiam = 3.4;
    iSpecies = 1;
    iType = clTreePopulation::sapling;
    p_oTrees[iIndex] = p_oPop->CreateTree(1, 9, iSpecies, iType, fDiam);
    p_oTrees[iIndex]->SetValue(p_oPop->GetHeightCode(iSpecies, iType), fDiam);
    iIndex++;

    fDiam = 5.4;
    iSpecies = 3;
    iType = clTreePopulation::sapling;
    p_oTrees[iIndex] = p_oPop->CreateTree(1, 9, iSpecies, iType, fDiam);
    p_oTrees[iIndex]->SetValue(p_oPop->GetHeightCode(iSpecies, iType), fDiam);
    iIndex++;

    fDiam = 12.6;
    iSpecies = 0;
    iType = clTreePopulation::adult;
    p_oTrees[iIndex] = p_oPop->CreateTree(1, 9, iSpecies, iType, fDiam);
    p_oTrees[iIndex]->SetValue(p_oPop->GetHeightCode(iSpecies, iType), fDiam);
    iIndex++;

    fDiam = 45.2;
    iSpecies = 1;
    iType = clTreePopulation::adult;
    p_oTrees[iIndex] = p_oPop->CreateTree(1, 9, iSpecies, iType, fDiam);
    p_oTrees[iIndex]->SetValue(p_oPop->GetHeightCode(iSpecies, iType), fDiam);
    iIndex++;

    fDiam = 23.3;
    iSpecies = 3;
    iType = clTreePopulation::adult;
    p_oTrees[iIndex] = p_oPop->CreateTree(1, 9, iSpecies, iType, fDiam);
    p_oTrees[iIndex]->SetValue(p_oPop->GetHeightCode(iSpecies, iType), fDiam);
    iIndex++;

    fDiam = 0.1;
    iSpecies = 0;
    iType = clTreePopulation::seedling;
    p_oTrees[iIndex] = p_oPop->CreateTree(1, 17, iSpecies, iType, fDiam);
    p_oTrees[iIndex]->SetValue(p_oPop->GetHeightCode(iSpecies, iType), fDiam);
    iIndex++;

    fDiam = 0.2;
    iSpecies = 1;
    iType = clTreePopulation::seedling;
    p_oTrees[iIndex] = p_oPop->CreateTree(1, 17, iSpecies, iType, fDiam);
    p_oTrees[iIndex]->SetValue(p_oPop->GetHeightCode(iSpecies, iType), fDiam);
    iIndex++;

    fDiam = 0.3;
    iSpecies = 3;
    iType = clTreePopulation::seedling;
    p_oTrees[iIndex] = p_oPop->CreateTree(1, 17, iSpecies, iType, fDiam);
    p_oTrees[iIndex]->SetValue(p_oPop->GetHeightCode(iSpecies, iType), fDiam);
    iIndex++;

    fDiam = 2.5;
    iSpecies = 0;
    iType = clTreePopulation::sapling;
    p_oTrees[iIndex] = p_oPop->CreateTree(1, 17, iSpecies, iType, fDiam);
    p_oTrees[iIndex]->SetValue(p_oPop->GetHeightCode(iSpecies, iType), fDiam);
    iIndex++;

    fDiam = 3.4;
    iSpecies = 1;
    iType = clTreePopulation::sapling;
    p_oTrees[iIndex] = p_oPop->CreateTree(1, 17, iSpecies, iType, fDiam);
    p_oTrees[iIndex]->SetValue(p_oPop->GetHeightCode(iSpecies, iType), fDiam);
    iIndex++;

    fDiam = 5.4;
    iSpecies = 3;
    iType = clTreePopulation::sapling;
    p_oTrees[iIndex] = p_oPop->CreateTree(1, 17, iSpecies, iType, fDiam);
    p_oTrees[iIndex]->SetValue(p_oPop->GetHeightCode(iSpecies, iType), fDiam);
    iIndex++;

    fDiam = 12.6;
    iSpecies = 0;
    iType = clTreePopulation::adult;
    p_oTrees[iIndex] = p_oPop->CreateTree(1, 17, iSpecies, iType, fDiam);
    p_oTrees[iIndex]->SetValue(p_oPop->GetHeightCode(iSpecies, iType), fDiam);
    iIndex++;

    fDiam = 45.2;
    iSpecies = 1;
    iType = clTreePopulation::adult;
    p_oTrees[iIndex] = p_oPop->CreateTree(1, 17, iSpecies, iType, fDiam);
    p_oTrees[iIndex]->SetValue(p_oPop->GetHeightCode(iSpecies, iType), fDiam);
    iIndex++;

    fDiam = 23.3;
    iSpecies = 3;
    iType = clTreePopulation::adult;
    p_oTrees[iIndex] = p_oPop->CreateTree(1, 17, iSpecies, iType, fDiam);
    p_oTrees[iIndex]->SetValue(p_oPop->GetHeightCode(iSpecies, iType), fDiam);
    iIndex++;

    //Now run growth, but skip storm light
    int i;
    for (i = 1; i < p_oSimManager->GetNumberOfBehaviors(); i++) {
      clBehaviorBase *p_oBase = p_oSimManager->GetBehaviorObject(i);
      p_oBase->Action();
    }

    //Confirm all trees
    iIndex = 0;
    fExpectedHeight = 0.163229353;
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedHeight = 0.232478126;
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedHeight = 0.303195532;
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedHeight = 2.595198013;
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedHeight = 3.55586166;
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedHeight = 5.51536841;
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedHeight = 12.69999524;
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedHeight = 45.38534401;
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedHeight = 23.44285874;
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedHeight = 0.163229353;
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedHeight = 0.232478126;
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedHeight = 0.303195532;
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedHeight = 2.595198013;
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedHeight = 3.55586166;
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedHeight = 5.51536841;
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedHeight = 12.69999524;
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedHeight = 45.38534401;
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedHeight = 23.44285874;
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedHeight = 0.163229353;
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedHeight = 0.232478126;
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedHeight = 0.303195532;
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedHeight = 2.595198013;
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedHeight = 3.55586166;
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedHeight = 5.51536841;
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedHeight = 12.69999524;
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedHeight = 45.38534401;
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fExpectedHeight = 23.44285874;
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

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
TEST(LogBiLevelGrowth, ErrorProcessing)
{
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try
  {
    p_oSimManager->ReadFile( WriteLogBiLevelGrowthXMLErrorFile1() );
    FAIL() << "TestLogBiLevelGrowth error processing didn't catch error for WriteLogBiLevelGrowthXMLErrorFile1.";
  }
  catch ( modelErr& err )
  {
    if ( err.sFunction.compare("clLogBiLevelGrowth::DoShellSetup" ) != 0 )
    {
      FAIL() << "TestLogBiLevelGrowth error processing caught wrong error for WriteLogBiLevelGrowthXMLErrorFile1.";
    }
    ;
  }

  try
  {
    p_oSimManager->ReadFile( WriteLogBiLevelGrowthXMLErrorFile2() );
    FAIL() << "TestLogBiLevelGrowth error processing didn't catch error for WriteLogBiLevelGrowthXMLErrorFile2.";
  }
  catch ( modelErr& err )
  {
    if ( err.sFunction.compare("clLogBiLevelGrowth::DoShellSetup" ) != 0 )
    {
      FAIL() << "TestLogBiLevelGrowth error processing caught wrong error for WriteLogBiLevelGrowthXMLErrorFile2.";
    }
    ;
  }

  try
  {
    p_oSimManager->ReadFile( WriteLogBiLevelGrowthXMLErrorFile3() );
    FAIL() << "TestLogBiLevelGrowth error processing didn't catch error for WriteLogBiLevelGrowthXMLErrorFile3.";
  }
  catch ( modelErr& err )
  {
    if ( err.sFunction.compare("clLogBiLevelGrowth::DoShellSetup" ) != 0 )
    {
      FAIL() << "TestLogBiLevelGrowth error processing caught wrong error for WriteLogBiLevelGrowthXMLErrorFile3.";
    }
    ;
  }

  try
  {
    p_oSimManager->ReadFile( WriteLogBiLevelGrowthXMLErrorFile4() );
    FAIL() << "TestLogBiLevelGrowth error processing didn't catch error for WriteLogBiLevelGrowthXMLErrorFile4.";
  }
  catch ( modelErr& err )
  {
    if ( err.sFunction.compare("clLogBiLevelGrowth::DoShellSetup" ) != 0 )
    {
      FAIL() << "TestLogBiLevelGrowth error processing caught wrong error for WriteLogBiLevelGrowthXMLErrorFile4.";
    }
    ;
  }

  try
  {
    p_oSimManager->ReadFile( WriteLogBiLevelGrowthXMLErrorFile5() );
    FAIL() << "TestLogBiLevelGrowth error processing didn't catch error for WriteLogBiLevelGrowthXMLErrorFile5.";
  }
  catch ( modelErr& err )
  {
    if ( err.sFunction.compare("clLogBiLevelGrowth::DoShellSetup" ) != 0 )
    {
      FAIL() << "TestLogBiLevelGrowth error processing caught wrong error for WriteLogBiLevelGrowthXMLErrorFile5.";
    }
    ;
  }

  try
  {
    p_oSimManager->ReadFile( WriteLogBiLevelGrowthXMLErrorFile6() );
    FAIL() << "TestLogBiLevelGrowth error processing didn't catch error for WriteLogBiLevelGrowthXMLErrorFile6.";
  }
  catch ( modelErr& err )
  {
    if ( err.sFunction.compare("clLogBiLevelGrowth::DoShellSetup" ) != 0 )
    {
      FAIL() << "TestLogBiLevelGrowth error processing caught wrong error for WriteLogBiLevelGrowthXMLErrorFile6.";
    }
    ;
  }

  try
  {
    p_oSimManager->ReadFile( WriteLogBiLevelGrowthXMLErrorFile7() );
    FAIL() << "TestLogBiLevelGrowth error processing didn't catch error for WriteLogBiLevelGrowthXMLErrorFile7.";
  }
  catch ( modelErr& err )
  {
    if ( err.sFunction.compare("clLogBiLevelGrowth::DoShellSetup" ) != 0 )
    {
      FAIL() << "TestLogBiLevelGrowth error processing caught wrong error for WriteLogBiLevelGrowthXMLErrorFile7.";
    }
    ;
  }
  delete p_oSimManager;
}

////////////////////////////////////////////////////////////////////////////
// WriteLogBiLevelGrowthXMLFile1()
////////////////////////////////////////////////////////////////////////////
const char* WriteLogBiLevelGrowthXMLFile1() {
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

  WriteLogBiLevelGrowthCommonStuff(oOut);

  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>StormLight</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>ConstantGLI</behaviorName>"
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
       << "<behaviorName>LogBilevelGrowth height only</behaviorName>"
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
       << "<behavior>"
       << "<behaviorName>ConstRadialGrowth diam only</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>4</listPosition>"
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
       << "<ConstantGLI2>"
       << "<li_constGLI>100</li_constGLI>"
       << "</ConstantGLI2>"
       << "<StormLight1>"
       << "<li_stormLightRadius>15</li_stormLightRadius>"
       << "<li_stormLightSlope>-4</li_stormLightSlope>"
       << "<li_stormLightIntercept>95</li_stormLightIntercept>"
       << "<li_stormLightMaxDmgTime>3</li_stormLightMaxDmgTime>"
       << "<li_stormLightSnagMaxDmgTime>2</li_stormLightSnagMaxDmgTime>"
       << "<li_stormLightStoch>0</li_stormLightStoch>"
       << "<li_stormLightMinFullCanopy>9</li_stormLightMinFullCanopy>"
       << "</StormLight1>";

  WriteLogBiLevelGrowthGrowthParameters(oOut);
  oOut << "</paramFile>";

  oOut.close();

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteLogBiLevelGrowthXMLFile2()
////////////////////////////////////////////////////////////////////////////
const char* WriteLogBiLevelGrowthXMLFile2() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  //Write file
  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06010101\">"
       << "<plot>"
       << "<timesteps>3</timesteps>"
       << "<yearsPerTimestep>3</yearsPerTimestep>";

  WriteLogBiLevelGrowthCommonStuff(oOut);

  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>StormLight</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>ConstantGLI</behaviorName>"
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
       << "<behaviorName>LogBilevelGrowth height only</behaviorName>"
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
       << "<behavior>"
       << "<behaviorName>ConstRadialGrowth diam only</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>4</listPosition>"
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
       << "<ConstantGLI2>"
       << "<li_constGLI>100</li_constGLI>"
       << "</ConstantGLI2>"
       << "<StormLight1>"
       << "<li_stormLightRadius>15</li_stormLightRadius>"
       << "<li_stormLightSlope>-4</li_stormLightSlope>"
       << "<li_stormLightIntercept>95</li_stormLightIntercept>"
       << "<li_stormLightMaxDmgTime>3</li_stormLightMaxDmgTime>"
       << "<li_stormLightSnagMaxDmgTime>2</li_stormLightSnagMaxDmgTime>"
       << "<li_stormLightStoch>0</li_stormLightStoch>"
       << "<li_stormLightMinFullCanopy>9</li_stormLightMinFullCanopy>"
       << "</StormLight1>";

  WriteLogBiLevelGrowthGrowthParameters(oOut);
  oOut << "</paramFile>";

  oOut.close();

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteLogBiLevelGrowthXMLFile3()
////////////////////////////////////////////////////////////////////////////
const char* WriteLogBiLevelGrowthXMLFile3() {
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

  WriteLogBiLevelGrowthCommonStuff(oOut);

  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>ConstantGLI</behaviorName>"
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
       << "<behavior>"
       << "<behaviorName>LogBilevelGrowth height only</behaviorName>"
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
       << "<behaviorName>ConstRadialGrowth diam only</behaviorName>"
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
       << "<ConstantGLI1>"
       << "<li_constGLI>100</li_constGLI>"
       << "</ConstantGLI1>";

  oOut << "<ConstRadialGrowth3>"
       << "<gr_adultConstRadialInc>"
       << "<gr_acriVal species=\"Species_1\">1</gr_acriVal>"
       << "<gr_acriVal species=\"Species_2\">1</gr_acriVal>"
       << "<gr_acriVal species=\"Species_4\">1</gr_acriVal>"
       << "</gr_adultConstRadialInc>"
       << "</ConstRadialGrowth3>"
       << "<LogBilevelGrowth2>"
       << "<gr_lognormalBilevLoLiteX0>"
       << "<gr_lbllx0Val species=\"Species_1\">12</gr_lbllx0Val>"
       << "<gr_lbllx0Val species=\"Species_2\">18</gr_lbllx0Val>"
       << "<gr_lbllx0Val species=\"Species_4\">15</gr_lbllx0Val>"
       << "</gr_lognormalBilevLoLiteX0>"
       << "<gr_lognormalBilevLoLiteXb>"
       << "<gr_lbllxbVal species=\"Species_1\">5</gr_lbllxbVal>"
       << "<gr_lbllxbVal species=\"Species_2\">2.36</gr_lbllxbVal>"
       << "<gr_lbllxbVal species=\"Species_4\">1.41</gr_lbllxbVal>"
       << "</gr_lognormalBilevLoLiteXb>"
       << "<gr_lognormalBilevLoLiteXb>"
       << "<gr_lbllxbVal species=\"Species_1\">5</gr_lbllxbVal>"
       << "<gr_lbllxbVal species=\"Species_2\">2.36</gr_lbllxbVal>"
       << "<gr_lbllxbVal species=\"Species_4\">1.41</gr_lbllxbVal>"
       << "</gr_lognormalBilevLoLiteXb>"
       << "<gr_lognormalBilevLoLiteMaxGrowth>"
       << "<gr_lbllmgVal species=\"Species_1\">0.1</gr_lbllmgVal>"
       << "<gr_lbllmgVal species=\"Species_2\">0.2</gr_lbllmgVal>"
       << "<gr_lbllmgVal species=\"Species_4\">0.15</gr_lbllmgVal>"
       << "</gr_lognormalBilevLoLiteMaxGrowth>"
       << "<gr_lognormalBilevHiLiteThreshold>"
       << "<gr_lobhltVal species=\"Species_1\">20</gr_lobhltVal>"
       << "<gr_lobhltVal species=\"Species_2\">50</gr_lobhltVal>"
       << "<gr_lobhltVal species=\"Species_4\">70</gr_lobhltVal>"
       << "</gr_lognormalBilevHiLiteThreshold>"
       << "</LogBilevelGrowth2>";

  oOut << "</paramFile>";

  oOut.close();

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteLogBiLevelGrowthXMLErrorFile1()
////////////////////////////////////////////////////////////////////////////
const char* WriteLogBiLevelGrowthXMLErrorFile1() {
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

  WriteLogBiLevelGrowthCommonStuff(oOut);

  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>StormLight</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>LogBilevelGrowth height only</behaviorName>"
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
       << "<behaviorName>ConstRadialGrowth diam only</behaviorName>"
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

  oOut << "<ConstRadialGrowth3>"
       << "<gr_adultConstRadialInc>"
       << "<gr_acriVal species=\"Species_1\">1</gr_acriVal>"
       << "<gr_acriVal species=\"Species_2\">1</gr_acriVal>"
       << "<gr_acriVal species=\"Species_4\">1</gr_acriVal>"
       << "</gr_adultConstRadialInc>"
       << "</ConstRadialGrowth3>"
       << "<LogBilevelGrowth2>"
       << "<gr_lognormalBilevLoLiteX0>"
       << "<gr_lbllx0Val species=\"Species_1\">12</gr_lbllx0Val>"
       << "<gr_lbllx0Val species=\"Species_2\">18</gr_lbllx0Val>"
       << "<gr_lbllx0Val species=\"Species_4\">15</gr_lbllx0Val>"
       << "</gr_lognormalBilevLoLiteX0>"
       << "<gr_lognormalBilevLoLiteXb>"
       << "<gr_lbllxbVal species=\"Species_1\">5</gr_lbllxbVal>"
       << "<gr_lbllxbVal species=\"Species_2\">2.36</gr_lbllxbVal>"
       << "<gr_lbllxbVal species=\"Species_4\">1.41</gr_lbllxbVal>"
       << "</gr_lognormalBilevLoLiteXb>"
       << "<gr_lognormalBilevLoLiteXb>"
       << "<gr_lbllxbVal species=\"Species_1\">5</gr_lbllxbVal>"
       << "<gr_lbllxbVal species=\"Species_2\">2.36</gr_lbllxbVal>"
       << "<gr_lbllxbVal species=\"Species_4\">1.41</gr_lbllxbVal>"
       << "</gr_lognormalBilevLoLiteXb>"
       << "<gr_lognormalBilevLoLiteMaxGrowth>"
       << "<gr_lbllmgVal species=\"Species_1\">0.1</gr_lbllmgVal>"
       << "<gr_lbllmgVal species=\"Species_2\">0.2</gr_lbllmgVal>"
       << "<gr_lbllmgVal species=\"Species_4\">0.15</gr_lbllmgVal>"
       << "</gr_lognormalBilevLoLiteMaxGrowth>"
       << "<gr_lognormalBilevHiLiteX0>"
       << "<gr_lbhlx0Val species=\"Species_1\">6.4</gr_lbhlx0Val>"
       << "<gr_lbhlx0Val species=\"Species_2\">5.6</gr_lbhlx0Val>"
       << "<gr_lbhlx0Val species=\"Species_4\">4.7</gr_lbhlx0Val>"
       << "</gr_lognormalBilevHiLiteX0>"
       << "<gr_lognormalBilevHiLiteXb>"
       << "<gr_lbhlxbVal species=\"Species_1\">6.6</gr_lbhlxbVal>"
       << "<gr_lbhlxbVal species=\"Species_2\">5.6</gr_lbhlxbVal>"
       << "<gr_lbhlxbVal species=\"Species_4\">2.3</gr_lbhlxbVal>"
       << "</gr_lognormalBilevHiLiteXb>"
       << "<gr_lognormalBilevHiLiteMaxGrowth>"
       << "<gr_lbhlmgVal species=\"Species_1\">0.23</gr_lbhlmgVal>"
       << "<gr_lbhlmgVal species=\"Species_2\">0.34</gr_lbhlmgVal>"
       << "<gr_lbhlmgVal species=\"Species_4\">0.17</gr_lbhlmgVal>"
       << "</gr_lognormalBilevHiLiteMaxGrowth>"
       << "<gr_lognormalBilevHiLiteThreshold>"
       << "<gr_lobhltVal species=\"Species_1\">20</gr_lobhltVal>"
       << "<gr_lobhltVal species=\"Species_2\">-50</gr_lobhltVal>"
       << "<gr_lobhltVal species=\"Species_4\">70</gr_lobhltVal>"
       << "</gr_lognormalBilevHiLiteThreshold>"
       << "</LogBilevelGrowth2>";

  oOut << "</paramFile>";

  oOut.close();

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteLogBiLevelGrowthXMLErrorFile2()
////////////////////////////////////////////////////////////////////////////
const char* WriteLogBiLevelGrowthXMLErrorFile2() {
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

  WriteLogBiLevelGrowthCommonStuff(oOut);

  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>StormLight</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>LogBilevelGrowth height only</behaviorName>"
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
       << "<behaviorName>ConstRadialGrowth diam only</behaviorName>"
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

  oOut << "<ConstRadialGrowth3>"
       << "<gr_adultConstRadialInc>"
       << "<gr_acriVal species=\"Species_1\">1</gr_acriVal>"
       << "<gr_acriVal species=\"Species_2\">1</gr_acriVal>"
       << "<gr_acriVal species=\"Species_4\">1</gr_acriVal>"
       << "</gr_adultConstRadialInc>"
       << "</ConstRadialGrowth3>"
       << "<LogBilevelGrowth2>"
       << "<gr_lognormalBilevLoLiteX0>"
       << "<gr_lbllx0Val species=\"Species_1\">12</gr_lbllx0Val>"
       << "<gr_lbllx0Val species=\"Species_2\">18</gr_lbllx0Val>"
       << "<gr_lbllx0Val species=\"Species_4\">15</gr_lbllx0Val>"
       << "</gr_lognormalBilevLoLiteX0>"
       << "<gr_lognormalBilevLoLiteXb>"
       << "<gr_lbllxbVal species=\"Species_1\">0</gr_lbllxbVal>"
       << "<gr_lbllxbVal species=\"Species_2\">2.36</gr_lbllxbVal>"
       << "<gr_lbllxbVal species=\"Species_4\">1.41</gr_lbllxbVal>"
       << "</gr_lognormalBilevLoLiteXb>"
       << "<gr_lognormalBilevLoLiteXb>"
       << "<gr_lbllxbVal species=\"Species_1\">5</gr_lbllxbVal>"
       << "<gr_lbllxbVal species=\"Species_2\">2.36</gr_lbllxbVal>"
       << "<gr_lbllxbVal species=\"Species_4\">1.41</gr_lbllxbVal>"
       << "</gr_lognormalBilevLoLiteXb>"
       << "<gr_lognormalBilevLoLiteMaxGrowth>"
       << "<gr_lbllmgVal species=\"Species_1\">0.1</gr_lbllmgVal>"
       << "<gr_lbllmgVal species=\"Species_2\">0.2</gr_lbllmgVal>"
       << "<gr_lbllmgVal species=\"Species_4\">0.15</gr_lbllmgVal>"
       << "</gr_lognormalBilevLoLiteMaxGrowth>"
       << "<gr_lognormalBilevHiLiteX0>"
       << "<gr_lbhlx0Val species=\"Species_1\">6.4</gr_lbhlx0Val>"
       << "<gr_lbhlx0Val species=\"Species_2\">5.6</gr_lbhlx0Val>"
       << "<gr_lbhlx0Val species=\"Species_4\">4.7</gr_lbhlx0Val>"
       << "</gr_lognormalBilevHiLiteX0>"
       << "<gr_lognormalBilevHiLiteXb>"
       << "<gr_lbhlxbVal species=\"Species_1\">6.6</gr_lbhlxbVal>"
       << "<gr_lbhlxbVal species=\"Species_2\">5.6</gr_lbhlxbVal>"
       << "<gr_lbhlxbVal species=\"Species_4\">2.3</gr_lbhlxbVal>"
       << "</gr_lognormalBilevHiLiteXb>"
       << "<gr_lognormalBilevHiLiteMaxGrowth>"
       << "<gr_lbhlmgVal species=\"Species_1\">0.23</gr_lbhlmgVal>"
       << "<gr_lbhlmgVal species=\"Species_2\">0.34</gr_lbhlmgVal>"
       << "<gr_lbhlmgVal species=\"Species_4\">0.17</gr_lbhlmgVal>"
       << "</gr_lognormalBilevHiLiteMaxGrowth>"
       << "<gr_lognormalBilevHiLiteThreshold>"
       << "<gr_lobhltVal species=\"Species_1\">20</gr_lobhltVal>"
       << "<gr_lobhltVal species=\"Species_2\">50</gr_lobhltVal>"
       << "<gr_lobhltVal species=\"Species_4\">70</gr_lobhltVal>"
       << "</gr_lognormalBilevHiLiteThreshold>"
       << "</LogBilevelGrowth2>";

  oOut << "</paramFile>";

  oOut.close();

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteLogBiLevelGrowthXMLErrorFile3()
////////////////////////////////////////////////////////////////////////////
const char* WriteLogBiLevelGrowthXMLErrorFile3() {
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

  WriteLogBiLevelGrowthCommonStuff(oOut);

  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>StormLight</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>LogBilevelGrowth height only</behaviorName>"
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
       << "<behaviorName>ConstRadialGrowth diam only</behaviorName>"
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

  oOut << "<ConstRadialGrowth3>"
       << "<gr_adultConstRadialInc>"
       << "<gr_acriVal species=\"Species_1\">1</gr_acriVal>"
       << "<gr_acriVal species=\"Species_2\">1</gr_acriVal>"
       << "<gr_acriVal species=\"Species_4\">1</gr_acriVal>"
       << "</gr_adultConstRadialInc>"
       << "</ConstRadialGrowth3>"
       << "<LogBilevelGrowth2>"
       << "<gr_lognormalBilevLoLiteX0>"
       << "<gr_lbllx0Val species=\"Species_1\">12</gr_lbllx0Val>"
       << "<gr_lbllx0Val species=\"Species_2\">18</gr_lbllx0Val>"
       << "<gr_lbllx0Val species=\"Species_4\">15</gr_lbllx0Val>"
       << "</gr_lognormalBilevLoLiteX0>"
       << "<gr_lognormalBilevLoLiteXb>"
       << "<gr_lbllxbVal species=\"Species_1\">5</gr_lbllxbVal>"
       << "<gr_lbllxbVal species=\"Species_2\">2.36</gr_lbllxbVal>"
       << "<gr_lbllxbVal species=\"Species_4\">1.41</gr_lbllxbVal>"
       << "</gr_lognormalBilevLoLiteXb>"
       << "<gr_lognormalBilevLoLiteXb>"
       << "<gr_lbllxbVal species=\"Species_1\">5</gr_lbllxbVal>"
       << "<gr_lbllxbVal species=\"Species_2\">2.36</gr_lbllxbVal>"
       << "<gr_lbllxbVal species=\"Species_4\">1.41</gr_lbllxbVal>"
       << "</gr_lognormalBilevLoLiteXb>"
       << "<gr_lognormalBilevLoLiteMaxGrowth>"
       << "<gr_lbllmgVal species=\"Species_1\">0.1</gr_lbllmgVal>"
       << "<gr_lbllmgVal species=\"Species_2\">0.2</gr_lbllmgVal>"
       << "<gr_lbllmgVal species=\"Species_4\">0.15</gr_lbllmgVal>"
       << "</gr_lognormalBilevLoLiteMaxGrowth>"
       << "<gr_lognormalBilevHiLiteX0>"
       << "<gr_lbhlx0Val species=\"Species_1\">6.4</gr_lbhlx0Val>"
       << "<gr_lbhlx0Val species=\"Species_2\">5.6</gr_lbhlx0Val>"
       << "<gr_lbhlx0Val species=\"Species_4\">4.7</gr_lbhlx0Val>"
       << "</gr_lognormalBilevHiLiteX0>"
       << "<gr_lognormalBilevHiLiteXb>"
       << "<gr_lbhlxbVal species=\"Species_1\">6.6</gr_lbhlxbVal>"
       << "<gr_lbhlxbVal species=\"Species_2\">5.6</gr_lbhlxbVal>"
       << "<gr_lbhlxbVal species=\"Species_4\">0</gr_lbhlxbVal>"
       << "</gr_lognormalBilevHiLiteXb>"
       << "<gr_lognormalBilevHiLiteMaxGrowth>"
       << "<gr_lbhlmgVal species=\"Species_1\">0.23</gr_lbhlmgVal>"
       << "<gr_lbhlmgVal species=\"Species_2\">0.34</gr_lbhlmgVal>"
       << "<gr_lbhlmgVal species=\"Species_4\">0.17</gr_lbhlmgVal>"
       << "</gr_lognormalBilevHiLiteMaxGrowth>"
       << "<gr_lognormalBilevHiLiteThreshold>"
       << "<gr_lobhltVal species=\"Species_1\">20</gr_lobhltVal>"
       << "<gr_lobhltVal species=\"Species_2\">50</gr_lobhltVal>"
       << "<gr_lobhltVal species=\"Species_4\">70</gr_lobhltVal>"
       << "</gr_lognormalBilevHiLiteThreshold>"
       << "</LogBilevelGrowth2>";

  oOut << "</paramFile>";

  oOut.close();

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteLogBiLevelGrowthXMLErrorFile4()
////////////////////////////////////////////////////////////////////////////
const char* WriteLogBiLevelGrowthXMLErrorFile4() {
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

  WriteLogBiLevelGrowthCommonStuff(oOut);

  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>StormLight</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>LogBilevelGrowth height only</behaviorName>"
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
       << "<behaviorName>ConstRadialGrowth diam only</behaviorName>"
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

  oOut << "<ConstRadialGrowth3>"
       << "<gr_adultConstRadialInc>"
       << "<gr_acriVal species=\"Species_1\">1</gr_acriVal>"
       << "<gr_acriVal species=\"Species_2\">1</gr_acriVal>"
       << "<gr_acriVal species=\"Species_4\">1</gr_acriVal>"
       << "</gr_adultConstRadialInc>"
       << "</ConstRadialGrowth3>"
       << "<LogBilevelGrowth2>"
       << "<gr_lognormalBilevLoLiteX0>"
       << "<gr_lbllx0Val species=\"Species_1\">12</gr_lbllx0Val>"
       << "<gr_lbllx0Val species=\"Species_2\">18</gr_lbllx0Val>"
       << "<gr_lbllx0Val species=\"Species_4\">15</gr_lbllx0Val>"
       << "</gr_lognormalBilevLoLiteX0>"
       << "<gr_lognormalBilevLoLiteXb>"
       << "<gr_lbllxbVal species=\"Species_1\">5</gr_lbllxbVal>"
       << "<gr_lbllxbVal species=\"Species_2\">2.36</gr_lbllxbVal>"
       << "<gr_lbllxbVal species=\"Species_4\">1.41</gr_lbllxbVal>"
       << "</gr_lognormalBilevLoLiteXb>"
       << "<gr_lognormalBilevLoLiteXb>"
       << "<gr_lbllxbVal species=\"Species_1\">5</gr_lbllxbVal>"
       << "<gr_lbllxbVal species=\"Species_2\">2.36</gr_lbllxbVal>"
       << "<gr_lbllxbVal species=\"Species_4\">1.41</gr_lbllxbVal>"
       << "</gr_lognormalBilevLoLiteXb>"
       << "<gr_lognormalBilevLoLiteMaxGrowth>"
       << "<gr_lbllmgVal species=\"Species_1\">-0.1</gr_lbllmgVal>"
       << "<gr_lbllmgVal species=\"Species_2\">0.2</gr_lbllmgVal>"
       << "<gr_lbllmgVal species=\"Species_4\">0.15</gr_lbllmgVal>"
       << "</gr_lognormalBilevLoLiteMaxGrowth>"
       << "<gr_lognormalBilevHiLiteX0>"
       << "<gr_lbhlx0Val species=\"Species_1\">6.4</gr_lbhlx0Val>"
       << "<gr_lbhlx0Val species=\"Species_2\">5.6</gr_lbhlx0Val>"
       << "<gr_lbhlx0Val species=\"Species_4\">4.7</gr_lbhlx0Val>"
       << "</gr_lognormalBilevHiLiteX0>"
       << "<gr_lognormalBilevHiLiteXb>"
       << "<gr_lbhlxbVal species=\"Species_1\">6.6</gr_lbhlxbVal>"
       << "<gr_lbhlxbVal species=\"Species_2\">5.6</gr_lbhlxbVal>"
       << "<gr_lbhlxbVal species=\"Species_4\">2.3</gr_lbhlxbVal>"
       << "</gr_lognormalBilevHiLiteXb>"
       << "<gr_lognormalBilevHiLiteMaxGrowth>"
       << "<gr_lbhlmgVal species=\"Species_1\">0.23</gr_lbhlmgVal>"
       << "<gr_lbhlmgVal species=\"Species_2\">0.34</gr_lbhlmgVal>"
       << "<gr_lbhlmgVal species=\"Species_4\">0.17</gr_lbhlmgVal>"
       << "</gr_lognormalBilevHiLiteMaxGrowth>"
       << "<gr_lognormalBilevHiLiteThreshold>"
       << "<gr_lobhltVal species=\"Species_1\">20</gr_lobhltVal>"
       << "<gr_lobhltVal species=\"Species_2\">50</gr_lobhltVal>"
       << "<gr_lobhltVal species=\"Species_4\">70</gr_lobhltVal>"
       << "</gr_lognormalBilevHiLiteThreshold>"
       << "</LogBilevelGrowth2>";

  oOut << "</paramFile>";

  oOut.close();

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteLogBiLevelGrowthXMLErrorFile5()
////////////////////////////////////////////////////////////////////////////
const char* WriteLogBiLevelGrowthXMLErrorFile5() {
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

  WriteLogBiLevelGrowthCommonStuff(oOut);

  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>StormLight</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>LogBilevelGrowth height only</behaviorName>"
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
       << "<behaviorName>ConstRadialGrowth diam only</behaviorName>"
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

  oOut << "<ConstRadialGrowth3>"
       << "<gr_adultConstRadialInc>"
       << "<gr_acriVal species=\"Species_1\">1</gr_acriVal>"
       << "<gr_acriVal species=\"Species_2\">1</gr_acriVal>"
       << "<gr_acriVal species=\"Species_4\">1</gr_acriVal>"
       << "</gr_adultConstRadialInc>"
       << "</ConstRadialGrowth3>"
       << "<LogBilevelGrowth2>"
       << "<gr_lognormalBilevLoLiteX0>"
       << "<gr_lbllx0Val species=\"Species_1\">12</gr_lbllx0Val>"
       << "<gr_lbllx0Val species=\"Species_2\">18</gr_lbllx0Val>"
       << "<gr_lbllx0Val species=\"Species_4\">15</gr_lbllx0Val>"
       << "</gr_lognormalBilevLoLiteX0>"
       << "<gr_lognormalBilevLoLiteXb>"
       << "<gr_lbllxbVal species=\"Species_1\">5</gr_lbllxbVal>"
       << "<gr_lbllxbVal species=\"Species_2\">2.36</gr_lbllxbVal>"
       << "<gr_lbllxbVal species=\"Species_4\">1.41</gr_lbllxbVal>"
       << "</gr_lognormalBilevLoLiteXb>"
       << "<gr_lognormalBilevLoLiteXb>"
       << "<gr_lbllxbVal species=\"Species_1\">5</gr_lbllxbVal>"
       << "<gr_lbllxbVal species=\"Species_2\">2.36</gr_lbllxbVal>"
       << "<gr_lbllxbVal species=\"Species_4\">1.41</gr_lbllxbVal>"
       << "</gr_lognormalBilevLoLiteXb>"
       << "<gr_lognormalBilevLoLiteMaxGrowth>"
       << "<gr_lbllmgVal species=\"Species_1\">0.1</gr_lbllmgVal>"
       << "<gr_lbllmgVal species=\"Species_2\">0.2</gr_lbllmgVal>"
       << "<gr_lbllmgVal species=\"Species_4\">0.15</gr_lbllmgVal>"
       << "</gr_lognormalBilevLoLiteMaxGrowth>"
       << "<gr_lognormalBilevHiLiteX0>"
       << "<gr_lbhlx0Val species=\"Species_1\">6.4</gr_lbhlx0Val>"
       << "<gr_lbhlx0Val species=\"Species_2\">5.6</gr_lbhlx0Val>"
       << "<gr_lbhlx0Val species=\"Species_4\">4.7</gr_lbhlx0Val>"
       << "</gr_lognormalBilevHiLiteX0>"
       << "<gr_lognormalBilevHiLiteXb>"
       << "<gr_lbhlxbVal species=\"Species_1\">6.6</gr_lbhlxbVal>"
       << "<gr_lbhlxbVal species=\"Species_2\">5.6</gr_lbhlxbVal>"
       << "<gr_lbhlxbVal species=\"Species_4\">2.3</gr_lbhlxbVal>"
       << "</gr_lognormalBilevHiLiteXb>"
       << "<gr_lognormalBilevHiLiteMaxGrowth>"
       << "<gr_lbhlmgVal species=\"Species_1\">0.23</gr_lbhlmgVal>"
       << "<gr_lbhlmgVal species=\"Species_2\">0.34</gr_lbhlmgVal>"
       << "<gr_lbhlmgVal species=\"Species_4\">-0.17</gr_lbhlmgVal>"
       << "</gr_lognormalBilevHiLiteMaxGrowth>"
       << "<gr_lognormalBilevHiLiteThreshold>"
       << "<gr_lobhltVal species=\"Species_1\">20</gr_lobhltVal>"
       << "<gr_lobhltVal species=\"Species_2\">50</gr_lobhltVal>"
       << "<gr_lobhltVal species=\"Species_4\">70</gr_lobhltVal>"
       << "</gr_lognormalBilevHiLiteThreshold>"
       << "</LogBilevelGrowth2>";

  oOut << "</paramFile>";

  oOut.close();

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteLogBiLevelGrowthXMLErrorFile6()
////////////////////////////////////////////////////////////////////////////
const char* WriteLogBiLevelGrowthXMLErrorFile6() {
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

  WriteLogBiLevelGrowthCommonStuff(oOut);

  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>StormLight</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>LogBilevelGrowth height only</behaviorName>"
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
       << "<behaviorName>ConstRadialGrowth diam only</behaviorName>"
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

  oOut << "<ConstRadialGrowth3>"
       << "<gr_adultConstRadialInc>"
       << "<gr_acriVal species=\"Species_1\">1</gr_acriVal>"
       << "<gr_acriVal species=\"Species_2\">1</gr_acriVal>"
       << "<gr_acriVal species=\"Species_4\">1</gr_acriVal>"
       << "</gr_adultConstRadialInc>"
       << "</ConstRadialGrowth3>"
       << "<LogBilevelGrowth2>"
       << "<gr_lognormalBilevLoLiteX0>"
       << "<gr_lbllx0Val species=\"Species_1\">12</gr_lbllx0Val>"
       << "<gr_lbllx0Val species=\"Species_2\">0</gr_lbllx0Val>"
       << "<gr_lbllx0Val species=\"Species_4\">15</gr_lbllx0Val>"
       << "</gr_lognormalBilevLoLiteX0>"
       << "<gr_lognormalBilevLoLiteXb>"
       << "<gr_lbllxbVal species=\"Species_1\">5</gr_lbllxbVal>"
       << "<gr_lbllxbVal species=\"Species_2\">2.36</gr_lbllxbVal>"
       << "<gr_lbllxbVal species=\"Species_4\">1.41</gr_lbllxbVal>"
       << "</gr_lognormalBilevLoLiteXb>"
       << "<gr_lognormalBilevLoLiteXb>"
       << "<gr_lbllxbVal species=\"Species_1\">5</gr_lbllxbVal>"
       << "<gr_lbllxbVal species=\"Species_2\">2.36</gr_lbllxbVal>"
       << "<gr_lbllxbVal species=\"Species_4\">1.41</gr_lbllxbVal>"
       << "</gr_lognormalBilevLoLiteXb>"
       << "<gr_lognormalBilevLoLiteMaxGrowth>"
       << "<gr_lbllmgVal species=\"Species_1\">0.1</gr_lbllmgVal>"
       << "<gr_lbllmgVal species=\"Species_2\">0.2</gr_lbllmgVal>"
       << "<gr_lbllmgVal species=\"Species_4\">0.15</gr_lbllmgVal>"
       << "</gr_lognormalBilevLoLiteMaxGrowth>"
       << "<gr_lognormalBilevHiLiteX0>"
       << "<gr_lbhlx0Val species=\"Species_1\">6.4</gr_lbhlx0Val>"
       << "<gr_lbhlx0Val species=\"Species_2\">5.6</gr_lbhlx0Val>"
       << "<gr_lbhlx0Val species=\"Species_4\">4.7</gr_lbhlx0Val>"
       << "</gr_lognormalBilevHiLiteX0>"
       << "<gr_lognormalBilevHiLiteXb>"
       << "<gr_lbhlxbVal species=\"Species_1\">6.6</gr_lbhlxbVal>"
       << "<gr_lbhlxbVal species=\"Species_2\">5.6</gr_lbhlxbVal>"
       << "<gr_lbhlxbVal species=\"Species_4\">2.3</gr_lbhlxbVal>"
       << "</gr_lognormalBilevHiLiteXb>"
       << "<gr_lognormalBilevHiLiteMaxGrowth>"
       << "<gr_lbhlmgVal species=\"Species_1\">0.23</gr_lbhlmgVal>"
       << "<gr_lbhlmgVal species=\"Species_2\">0.34</gr_lbhlmgVal>"
       << "<gr_lbhlmgVal species=\"Species_4\">0.17</gr_lbhlmgVal>"
       << "</gr_lognormalBilevHiLiteMaxGrowth>"
       << "<gr_lognormalBilevHiLiteThreshold>"
       << "<gr_lobhltVal species=\"Species_1\">20</gr_lobhltVal>"
       << "<gr_lobhltVal species=\"Species_2\">50</gr_lobhltVal>"
       << "<gr_lobhltVal species=\"Species_4\">70</gr_lobhltVal>"
       << "</gr_lognormalBilevHiLiteThreshold>"
       << "</LogBilevelGrowth2>";

  oOut << "</paramFile>";

  oOut.close();

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteLogBiLevelGrowthXMLErrorFile7()
////////////////////////////////////////////////////////////////////////////
const char* WriteLogBiLevelGrowthXMLErrorFile7() {
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

  WriteLogBiLevelGrowthCommonStuff(oOut);

  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>StormLight</behaviorName>"
       << "<listPosition>1</listPosition>"
       << "<version>1</version>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>LogBilevelGrowth height only</behaviorName>"
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
       << "<behaviorName>ConstRadialGrowth diam only</behaviorName>"
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

  oOut << "<ConstRadialGrowth3>"
       << "<gr_adultConstRadialInc>"
       << "<gr_acriVal species=\"Species_1\">1</gr_acriVal>"
       << "<gr_acriVal species=\"Species_2\">1</gr_acriVal>"
       << "<gr_acriVal species=\"Species_4\">1</gr_acriVal>"
       << "</gr_adultConstRadialInc>"
       << "</ConstRadialGrowth3>"
       << "<LogBilevelGrowth2>"
       << "<gr_lognormalBilevLoLiteX0>"
       << "<gr_lbllx0Val species=\"Species_1\">12</gr_lbllx0Val>"
       << "<gr_lbllx0Val species=\"Species_2\">18</gr_lbllx0Val>"
       << "<gr_lbllx0Val species=\"Species_4\">15</gr_lbllx0Val>"
       << "</gr_lognormalBilevLoLiteX0>"
       << "<gr_lognormalBilevLoLiteXb>"
       << "<gr_lbllxbVal species=\"Species_1\">5</gr_lbllxbVal>"
       << "<gr_lbllxbVal species=\"Species_2\">2.36</gr_lbllxbVal>"
       << "<gr_lbllxbVal species=\"Species_4\">1.41</gr_lbllxbVal>"
       << "</gr_lognormalBilevLoLiteXb>"
       << "<gr_lognormalBilevLoLiteXb>"
       << "<gr_lbllxbVal species=\"Species_1\">5</gr_lbllxbVal>"
       << "<gr_lbllxbVal species=\"Species_2\">2.36</gr_lbllxbVal>"
       << "<gr_lbllxbVal species=\"Species_4\">1.41</gr_lbllxbVal>"
       << "</gr_lognormalBilevLoLiteXb>"
       << "<gr_lognormalBilevLoLiteMaxGrowth>"
       << "<gr_lbllmgVal species=\"Species_1\">0.1</gr_lbllmgVal>"
       << "<gr_lbllmgVal species=\"Species_2\">0.2</gr_lbllmgVal>"
       << "<gr_lbllmgVal species=\"Species_4\">0.15</gr_lbllmgVal>"
       << "</gr_lognormalBilevLoLiteMaxGrowth>"
       << "<gr_lognormalBilevHiLiteX0>"
       << "<gr_lbhlx0Val species=\"Species_1\">0</gr_lbhlx0Val>"
       << "<gr_lbhlx0Val species=\"Species_2\">5.6</gr_lbhlx0Val>"
       << "<gr_lbhlx0Val species=\"Species_4\">4.7</gr_lbhlx0Val>"
       << "</gr_lognormalBilevHiLiteX0>"
       << "<gr_lognormalBilevHiLiteXb>"
       << "<gr_lbhlxbVal species=\"Species_1\">6.6</gr_lbhlxbVal>"
       << "<gr_lbhlxbVal species=\"Species_2\">5.6</gr_lbhlxbVal>"
       << "<gr_lbhlxbVal species=\"Species_4\">2.3</gr_lbhlxbVal>"
       << "</gr_lognormalBilevHiLiteXb>"
       << "<gr_lognormalBilevHiLiteMaxGrowth>"
       << "<gr_lbhlmgVal species=\"Species_1\">0.23</gr_lbhlmgVal>"
       << "<gr_lbhlmgVal species=\"Species_2\">0.34</gr_lbhlmgVal>"
       << "<gr_lbhlmgVal species=\"Species_4\">0.17</gr_lbhlmgVal>"
       << "</gr_lognormalBilevHiLiteMaxGrowth>"
       << "<gr_lognormalBilevHiLiteThreshold>"
       << "<gr_lobhltVal species=\"Species_1\">20</gr_lobhltVal>"
       << "<gr_lobhltVal species=\"Species_2\">50</gr_lobhltVal>"
       << "<gr_lobhltVal species=\"Species_4\">70</gr_lobhltVal>"
       << "</gr_lognormalBilevHiLiteThreshold>"
       << "</LogBilevelGrowth2>";

  oOut << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteLogBiLevelGrowthCommonStuff()
/////////////////////////////////////////////////////////////////////////////
void WriteLogBiLevelGrowthCommonStuff(std::fstream &oOut)
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
       << "<tr_chVal species=\"Species_1\">46</tr_chVal>"
       << "<tr_chVal species=\"Species_2\">46</tr_chVal>"
       << "<tr_chVal species=\"Species_3\">46</tr_chVal>"
       << "<tr_chVal species=\"Species_4\">46</tr_chVal>"
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
// WriteLogBiLevelGrowthGrowthParameters()
/////////////////////////////////////////////////////////////////////////////
void WriteLogBiLevelGrowthGrowthParameters(std::fstream &oOut)
{
  using namespace std;
  oOut << "<LogBilevelGrowth3>"
       << "<gr_lognormalBilevLoLiteX0>"
       << "<gr_lbllx0Val species=\"Species_1\">12</gr_lbllx0Val>"
       << "<gr_lbllx0Val species=\"Species_2\">18</gr_lbllx0Val>"
       << "<gr_lbllx0Val species=\"Species_4\">15</gr_lbllx0Val>"
       << "</gr_lognormalBilevLoLiteX0>"
       << "<gr_lognormalBilevLoLiteXb>"
       << "<gr_lbllxbVal species=\"Species_1\">5</gr_lbllxbVal>"
       << "<gr_lbllxbVal species=\"Species_2\">2.36</gr_lbllxbVal>"
       << "<gr_lbllxbVal species=\"Species_4\">1.41</gr_lbllxbVal>"
       << "</gr_lognormalBilevLoLiteXb>"
       << "<gr_lognormalBilevLoLiteXb>"
       << "<gr_lbllxbVal species=\"Species_1\">5</gr_lbllxbVal>"
       << "<gr_lbllxbVal species=\"Species_2\">2.36</gr_lbllxbVal>"
       << "<gr_lbllxbVal species=\"Species_4\">1.41</gr_lbllxbVal>"
       << "</gr_lognormalBilevLoLiteXb>"
       << "<gr_lognormalBilevLoLiteMaxGrowth>"
       << "<gr_lbllmgVal species=\"Species_1\">0.1</gr_lbllmgVal>"
       << "<gr_lbllmgVal species=\"Species_2\">0.2</gr_lbllmgVal>"
       << "<gr_lbllmgVal species=\"Species_4\">0.15</gr_lbllmgVal>"
       << "</gr_lognormalBilevLoLiteMaxGrowth>"
       << "<gr_lognormalBilevHiLiteX0>"
       << "<gr_lbhlx0Val species=\"Species_1\">6.4</gr_lbhlx0Val>"
       << "<gr_lbhlx0Val species=\"Species_2\">5.6</gr_lbhlx0Val>"
       << "<gr_lbhlx0Val species=\"Species_4\">4.7</gr_lbhlx0Val>"
       << "</gr_lognormalBilevHiLiteX0>"
       << "<gr_lognormalBilevHiLiteXb>"
       << "<gr_lbhlxbVal species=\"Species_1\">6.6</gr_lbhlxbVal>"
       << "<gr_lbhlxbVal species=\"Species_2\">5.6</gr_lbhlxbVal>"
       << "<gr_lbhlxbVal species=\"Species_4\">2.3</gr_lbhlxbVal>"
       << "</gr_lognormalBilevHiLiteXb>"
       << "<gr_lognormalBilevHiLiteMaxGrowth>"
       << "<gr_lbhlmgVal species=\"Species_1\">0.23</gr_lbhlmgVal>"
       << "<gr_lbhlmgVal species=\"Species_2\">0.34</gr_lbhlmgVal>"
       << "<gr_lbhlmgVal species=\"Species_4\">0.17</gr_lbhlmgVal>"
       << "</gr_lognormalBilevHiLiteMaxGrowth>"
       << "<gr_lognormalBilevHiLiteThreshold>"
       << "<gr_lobhltVal species=\"Species_1\">20</gr_lobhltVal>"
       << "<gr_lobhltVal species=\"Species_2\">50</gr_lobhltVal>"
       << "<gr_lobhltVal species=\"Species_4\">70</gr_lobhltVal>"
       << "</gr_lognormalBilevHiLiteThreshold>"
       << "</LogBilevelGrowth3>"
       << "<ConstRadialGrowth4>"
       << "<gr_adultConstRadialInc>"
       << "<gr_acriVal species=\"Species_1\">1</gr_acriVal>"
       << "<gr_acriVal species=\"Species_2\">1</gr_acriVal>"
       << "<gr_acriVal species=\"Species_4\">1</gr_acriVal>"
       << "</gr_adultConstRadialInc>"
       << "</ConstRadialGrowth4>";
}
