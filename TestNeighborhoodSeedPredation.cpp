//---------------------------------------------------------------------------
// TestNeighbhorhoodSeedPredation.cpp
//---------------------------------------------------------------------------
#include "TestNeighborhoodSeedPredation.h"
#include <gtest/gtest.h>
#include "SimManager.h"
#include "TreePopulation.h"
#include "Grid.h"
#include <fstream>
#include <math.h>

/////////////////////////////////////////////////////////////////////////////
// TestNormalProcessingRun1()
// First normal processing run. WriteNeighborhoodSeedPredationXMLFile1() does setup. Seed predation is
// applied to species 1, 2, and 4. This run tests not counting seeds of
// unapplied species when checking the masting threshold, and choosing the
// correct parameters in a non-mast situation. This uses non-spatial disperse
// to drop 1 seed/m2 of each species, plus 2 of species 3 (5 seeds/m2 total).
// After a run occurs, the number of new seedlings is verified.
/////////////////////////////////////////////////////////////////////////////
TEST(NeighborhoodSeedPredation, TestNormalProcessingRun1)
{
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    //Feed our file to the sim manager
    p_oSimManager->ReadFile(WriteNeighborhoodSeedPredationXMLFile1());
    TestRun1And5(p_oSimManager);
    delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

/////////////////////////////////////////////////////////////////////////////
// TestNormalProcessingRun2()
// Second normal processing run. WriteNeighborhoodSeedPredationXMLFile2() does setup. This tests
// choosing the correct parameters in a mast situation, and correctly
// calculating mast density. This puts 10000 seeds of species 1 in seed grid
// cell (0,0) and 100 seeds of species 2 in grid cell (4,4). After a run
// occurs, the number of new seedlings is verified.
/////////////////////////////////////////////////////////////////////////////
TEST(NeighborhoodSeedPredation, TestNormalProcessingRun2) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    p_oSimManager->ReadFile(WriteNeighborhoodSeedPredationXMLFile2());
    TestRun2And6(p_oSimManager);
    delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

/////////////////////////////////////////////////////////////////////////////
// TestNormalProcessingRun3()
// Third normal processing run. WriteNeighborhoodSeedPredationXMLFile3() does setup. Seed predation is
// applied to species 1, 2, and 4. This run tests multi-year timesteps. This
// uses non-spatial disperse to drop 3 seeds/m2 of each species, plus 2 of
// species 3 (11 seeds/m2 total). After a run occurs, the number of new
// seedlings is verified.
/////////////////////////////////////////////////////////////////////////////
TEST(NeighborhoodSeedPredation, TestNormalProcessingRun3) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );

  clTreePopulation *p_oPop;
  clTreeSearch *p_oAllSeedlings;
  clTree *p_oTree;
  float fX, fY, fXMin, fXMax, fYMin, fYMax,
        fDbh,
        fXCellLength = 8, fYCellLength = 8;
  int *p_iNumSeedlings = new int[4], iSp, i;
  try {
    //Feed our file to the sim manager
    p_oSimManager->ReadFile(WriteNeighborhoodSeedPredationXMLFile3());
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );

    //Add our trees
    fX = 4; fY = 4;
    iSp = 0;
    fDbh = 5;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::sapling, fDbh);

    iSp = 1;
    fDbh = 10;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDbh);

    iSp = 2;
    fDbh = 20;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDbh);

    iSp = 3;
    fDbh = 15;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDbh);

    iSp = 0;
    fDbh = 30;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDbh);

    iSp = 1;
    fDbh = 35;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDbh);

    iSp = 2;
    fDbh = 50;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDbh);

    iSp = 3;
    fDbh = 21;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDbh);

    fX = 34; fY = 34;
    iSp = 0;
    fDbh = 5;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::sapling, fDbh);

    iSp = 1;
    fDbh = 10;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDbh);

    iSp = 2;
    fDbh = 5;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDbh);

    iSp = 3;
    fDbh = 5;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDbh);

    iSp = 0;
    fDbh = 30;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDbh);

    iSp = 1;
    fDbh = 35;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDbh);

    iSp = 2;
    fDbh = 5;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDbh);

    iSp = 3;
    fDbh = 5;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDbh);

    //Run a timestep
    p_oSimManager->RunSim(1);

    //Count the number of seedlings in each grid cell
    p_oAllSeedlings = p_oPop->Find("type=1");

    //Check our values for cell 0, 0
    for (i = 0; i < 4; i++) {
      p_iNumSeedlings[i] = 0;
    }
    fYMin = 0;
    fYMax = fYCellLength;
    fXMin = 0;
    fXMax = fXCellLength;
    p_oTree = p_oAllSeedlings->NextTree();
    while (p_oTree) {
      p_oTree->GetValue(p_oPop->GetXCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fX);
      p_oTree->GetValue(p_oPop->GetYCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fY);
      if (fX >= fXMin && fX < fXMax && fY >= fYMin && fY < fYMax) {
        p_iNumSeedlings[p_oTree->GetSpecies()]++;
      }
      p_oTree = p_oAllSeedlings->NextTree();
    }
    EXPECT_TRUE(79 == p_iNumSeedlings[0] || 80 == p_iNumSeedlings[0]);
    EXPECT_TRUE(190 == p_iNumSeedlings[1] || 191 == p_iNumSeedlings[1]);
    EXPECT_EQ(384, p_iNumSeedlings[2]);
    EXPECT_EQ(192, p_iNumSeedlings[3]);

    //Check our values for cell 4, 4
    for (i = 0; i < 4; i++) {
      p_iNumSeedlings[i] = 0;
    }
    fXMin = 4 * fXCellLength;
    fXMax = (4 + 1) * fXCellLength;
    fYMin = 4 * fYCellLength;
    fYMax = (4 + 1) * fYCellLength;
    p_oAllSeedlings->StartOver();
    p_oTree = p_oAllSeedlings->NextTree();
    while (p_oTree) {
      p_oTree->GetValue(p_oPop->GetXCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fX);
      p_oTree->GetValue(p_oPop->GetYCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fY);
      if (fX >= fXMin && fX <= fXMax && fY >= fYMin && fY <= fYMax) {
        p_iNumSeedlings[p_oTree->GetSpecies()]++;
      }
      p_oTree = p_oAllSeedlings->NextTree();
    }
    EXPECT_TRUE(36 == p_iNumSeedlings[0] || 37 == p_iNumSeedlings[0]);
    EXPECT_TRUE(102 == p_iNumSeedlings[1] || 103 == p_iNumSeedlings[1]);
    EXPECT_EQ(384, p_iNumSeedlings[2]);
    EXPECT_EQ(192, p_iNumSeedlings[3]);

    delete[] p_iNumSeedlings;
    delete p_oSimManager;
  } catch (modelErr &e) {
    delete[] p_iNumSeedlings;
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

/////////////////////////////////////////////////////////////////////////////
// TestNormalProcessingRun4()
// Fourth normal processing run. WriteNeighborhoodSeedPredationXMLFile4() does setup. Linked seed
// predation is applied to species 1, 2, and 4, and unlinked to species 5.
// This run tests linked vs. standalone predation. After a run occurs, the
// number of new seedlings is verified.
/////////////////////////////////////////////////////////////////////////////
TEST(NeighborhoodSeedPredation, TestNormalProcessingRun4)
{
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    clTreePopulation *p_oPop;
    clTreeSearch *p_oAllSeedlings;
    clGrid *p_oGrid;
    clTree *p_oTree;
    float fX, fY, fXMin, fXMax, fYMin, fYMax,
    fDbh,
    fValue, fExpectedValue,
    fXCellLength = 50, fYCellLength = 50;
    int *p_iNumSeedlings = new int[5], iSp, i;

    //Feed our file to the sim manager
    p_oSimManager->ReadFile(WriteNeighborhoodSeedPredationXMLFile4());
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );
    p_oGrid = p_oSimManager->GetGridObject("Neighborhood Seed Predation");
    ASSERT_TRUE(NULL != p_oGrid);

    //Add our trees
    fX = 25; fY = 25;
    iSp = 0;
    fDbh = 5;
    for (i = 0; i < 100; i++)
      p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::sapling, fDbh);

    iSp = 1;
    fDbh = 10;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDbh);

    iSp = 2;
    fDbh = 20;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDbh);

    iSp = 3;
    fDbh = 15;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDbh);

    iSp = 0;
    fDbh = 30;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDbh);

    iSp = 1;
    fDbh = 35;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDbh);

    iSp = 2;
    fDbh = 50;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDbh);

    iSp = 3;
    fDbh = 21;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDbh);

    fX = 25; fY = 75;
    iSp = 0;
    fDbh = 5;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::sapling, fDbh);

    iSp = 1;
    fDbh = 10;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDbh);

    iSp = 2;
    fDbh = 5;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::sapling, fDbh);

    iSp = 3;
    fDbh = 5;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::sapling, fDbh);

    iSp = 0;
    fDbh = 30;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDbh);

    iSp = 1;
    fDbh = 35;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDbh);

    iSp = 2;
    fDbh = 5;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::sapling, fDbh);

    iSp = 3;
    fDbh = 5;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::sapling, fDbh);

    fX = 75; fY = 75;
    iSp = 0;
    fDbh = 10;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDbh);

    iSp = 1;
    fDbh = 20;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDbh);

    iSp = 2;
    fDbh = 30;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDbh);

    iSp = 3;
    fDbh = 40;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDbh);

    iSp = 3;
    fDbh = 50;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDbh);

    iSp = 3;
    fDbh = 60;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDbh);

    iSp = 3;
    fDbh = 70;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDbh);

    iSp = 3;
    fDbh = 80;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDbh);

    iSp = 3;
    fDbh = 90;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDbh);

    iSp = 3;
    fDbh = 100;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDbh);

    iSp = 3;
    fDbh = 110;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDbh);

    //Run a timestep
    p_oSimManager->RunSim(1);

    //Count the number of seedlings in each grid cell
    p_oAllSeedlings = p_oPop->Find("type=1");

    //Check our values for cell 0, 0
    for (i = 0; i < 5; i++) {
      p_iNumSeedlings[i] = 0;
    }
    fYMin = 0;
    fYMax = fYCellLength;
    fXMin = 0;
    fXMax = fXCellLength;
    p_oTree = p_oAllSeedlings->NextTree();
    while (p_oTree) {
      p_oTree->GetValue(p_oPop->GetXCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fX);
      p_oTree->GetValue(p_oPop->GetYCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fY);
      if (fX >= fXMin && fX < fXMax && fY >= fYMin && fY < fYMax) {
        p_iNumSeedlings[p_oTree->GetSpecies()]++;
      }
      p_oTree = p_oAllSeedlings->NextTree();
    }
    EXPECT_TRUE(p_iNumSeedlings[0] >= 1996 && p_iNumSeedlings[0] <= 1997);
    EXPECT_TRUE(p_iNumSeedlings[1] >= 1526 && p_iNumSeedlings[1] <= 1527);
    EXPECT_EQ(5000, p_iNumSeedlings[2]);
    EXPECT_TRUE(p_iNumSeedlings[3] >= 1868 && p_iNumSeedlings[3] <= 1869);
    EXPECT_TRUE(p_iNumSeedlings[4] >= 298 && p_iNumSeedlings[4] <= 301);

    //Check our values for cell 1, 0
    for (i = 0; i < 5; i++) {
      p_iNumSeedlings[i] = 0;
    }
    fXMin = fXCellLength;
    fXMax = (1 + 1) * fXCellLength;
    fYMin = 0;
    fYMax = fYCellLength;
    p_oAllSeedlings->StartOver();
    p_oTree = p_oAllSeedlings->NextTree();
    while (p_oTree) {
      p_oTree->GetValue(p_oPop->GetXCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fX);
      p_oTree->GetValue(p_oPop->GetYCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fY);
      if (fX >= fXMin && fX <= fXMax && fY >= fYMin && fY <= fYMax) {
        p_iNumSeedlings[p_oTree->GetSpecies()]++;
      }
      p_oTree = p_oAllSeedlings->NextTree();
    }
    EXPECT_TRUE(p_iNumSeedlings[0] >= 1785 && p_iNumSeedlings[0] <= 1786);
    EXPECT_TRUE(p_iNumSeedlings[1] >= 1870 && p_iNumSeedlings[1] <= 1871);
    EXPECT_EQ(5000, p_iNumSeedlings[2]);
    EXPECT_TRUE(p_iNumSeedlings[3] >= 2131 && p_iNumSeedlings[3] <= 2132);
    EXPECT_TRUE(p_iNumSeedlings[4] >= 2271 && p_iNumSeedlings[4] <= 2274);

    //Check our values for cell 0, 1
    for (i = 0; i < 5; i++) {
      p_iNumSeedlings[i] = 0;
    }
    fXMin = 0;
    fXMax = fXCellLength;
    fYMin = fYCellLength;
    fYMax = (1 + 1) * fYCellLength;
    p_oAllSeedlings->StartOver();
    p_oTree = p_oAllSeedlings->NextTree();
    while (p_oTree) {
      p_oTree->GetValue(p_oPop->GetXCode(p_oTree->GetSpecies(),
          p_oTree->GetType()), &fX);
      p_oTree->GetValue(p_oPop->GetYCode(p_oTree->GetSpecies(),
          p_oTree->GetType()), &fY);
      if (fX >= fXMin && fX <= fXMax && fY >= fYMin && fY <= fYMax) {
        p_iNumSeedlings[p_oTree->GetSpecies()]++;
      }
      p_oTree = p_oAllSeedlings->NextTree();
    }
    EXPECT_TRUE(p_iNumSeedlings[0] >= 1917 && p_iNumSeedlings[0] <= 1918);
    EXPECT_TRUE(p_iNumSeedlings[1] >= 1495 && p_iNumSeedlings[1] <= 1496);
    EXPECT_EQ(5000, p_iNumSeedlings[2]);
    EXPECT_TRUE(p_iNumSeedlings[3] >= 2261 && p_iNumSeedlings[3] <= 2263);
    EXPECT_TRUE(p_iNumSeedlings[4] >= 181 && p_iNumSeedlings[4] <= 184);

    //Check our values for cell 1, 1
    for (i = 0; i < 5; i++) {
      p_iNumSeedlings[i] = 0;
    }
    fXMin = fXCellLength;
    fXMax = (1 + 1) * fXCellLength;
    fYMin = fYCellLength;
    fYMax = (1 + 1) * fYCellLength;
    p_oAllSeedlings->StartOver();
    p_oTree = p_oAllSeedlings->NextTree();
    while (p_oTree) {
      p_oTree->GetValue(p_oPop->GetXCode(p_oTree->GetSpecies(),
          p_oTree->GetType()), &fX);
      p_oTree->GetValue(p_oPop->GetYCode(p_oTree->GetSpecies(),
          p_oTree->GetType()), &fY);
      if (fX >= fXMin && fX <= fXMax && fY >= fYMin && fY <= fYMax) {
        p_iNumSeedlings[p_oTree->GetSpecies()]++;
      }
      p_oTree = p_oAllSeedlings->NextTree();
    }
    EXPECT_TRUE(p_iNumSeedlings[0] >= 1790 && p_iNumSeedlings[0] <= 1791);
    EXPECT_TRUE(p_iNumSeedlings[1] >= 1854 && p_iNumSeedlings[1] <= 1856);
    EXPECT_EQ(5000, p_iNumSeedlings[2]);
    EXPECT_TRUE(p_iNumSeedlings[3] >= 992 && p_iNumSeedlings[3] <= 993);
    EXPECT_TRUE(p_iNumSeedlings[4] >= 0 && p_iNumSeedlings[4] <= 3);

    delete[] p_iNumSeedlings;

    //Check our grid values
    //Cell 0, 0
    fExpectedValue = 2500;
    p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("startseeds_0"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 2500;
    p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("startseeds_1"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("startseeds_2"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 2500;
    p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("startseeds_3"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 2500;
    p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("startseeds_4"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

    fExpectedValue = 0.201459072;
    p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("propeaten_0"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.05);
    fExpectedValue = 0.389408398;
    p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("propeaten_1"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.05);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("propeaten_2"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.05);
    fExpectedValue = 0.252504483;
    p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("propeaten_3"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.05);
    fExpectedValue = 0.88025482;
    p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("propeaten_4"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.05);

    //Cell 1, 0
    fExpectedValue = 2500;
    p_oGrid->GetValueOfCell(1, 0, p_oGrid->GetFloatDataCode("startseeds_0"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 2500;
    p_oGrid->GetValueOfCell(1, 0, p_oGrid->GetFloatDataCode("startseeds_1"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(1, 0, p_oGrid->GetFloatDataCode("startseeds_2"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 2500;
    p_oGrid->GetValueOfCell(1, 0, p_oGrid->GetFloatDataCode("startseeds_3"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 2500;
    p_oGrid->GetValueOfCell(1, 0, p_oGrid->GetFloatDataCode("startseeds_4"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

    fExpectedValue = 0.285720283;
    p_oGrid->GetValueOfCell(1, 0, p_oGrid->GetFloatDataCode("propeaten_0"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.05);
    fExpectedValue = 0.251978413;
    p_oGrid->GetValueOfCell(1, 0, p_oGrid->GetFloatDataCode("propeaten_1"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.05);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(1, 0, p_oGrid->GetFloatDataCode("propeaten_2"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.05);
    fExpectedValue = 0.147201632;
    p_oGrid->GetValueOfCell(1, 0, p_oGrid->GetFloatDataCode("propeaten_3"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.05);
    fExpectedValue = 0.091122961;
    p_oGrid->GetValueOfCell(1, 0, p_oGrid->GetFloatDataCode("propeaten_4"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.05);

    //Cell 0, 1
    fExpectedValue = 2500;
    p_oGrid->GetValueOfCell(0, 1, p_oGrid->GetFloatDataCode("startseeds_0"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 2500;
    p_oGrid->GetValueOfCell(0, 1, p_oGrid->GetFloatDataCode("startseeds_1"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(0, 1, p_oGrid->GetFloatDataCode("startseeds_2"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 2500;
    p_oGrid->GetValueOfCell(0, 1, p_oGrid->GetFloatDataCode("startseeds_3"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 2500;
    p_oGrid->GetValueOfCell(0, 1, p_oGrid->GetFloatDataCode("startseeds_4"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

    fExpectedValue = 0.233095142;
    p_oGrid->GetValueOfCell(0, 1, p_oGrid->GetFloatDataCode("propeaten_0"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.05);
    fExpectedValue = 0.401669486;
    p_oGrid->GetValueOfCell(0, 1, p_oGrid->GetFloatDataCode("propeaten_1"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.05);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(0, 1, p_oGrid->GetFloatDataCode("propeaten_2"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.05);
    fExpectedValue = 0.095378545;
    p_oGrid->GetValueOfCell(0, 1, p_oGrid->GetFloatDataCode("propeaten_3"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.05);
    fExpectedValue = 0.927028145;
    p_oGrid->GetValueOfCell(0, 1, p_oGrid->GetFloatDataCode("propeaten_4"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.05);

    //Cell 1, 1
    fExpectedValue = 2500;
    p_oGrid->GetValueOfCell(1, 1, p_oGrid->GetFloatDataCode("startseeds_0"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 2500;
    p_oGrid->GetValueOfCell(1, 1, p_oGrid->GetFloatDataCode("startseeds_1"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(1, 1, p_oGrid->GetFloatDataCode("startseeds_2"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 2500;
    p_oGrid->GetValueOfCell(1, 1, p_oGrid->GetFloatDataCode("startseeds_3"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 2500;
    p_oGrid->GetValueOfCell(1, 1, p_oGrid->GetFloatDataCode("startseeds_4"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

    fExpectedValue = 0.283940005;
    p_oGrid->GetValueOfCell(1, 1, p_oGrid->GetFloatDataCode("propeaten_0"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.05);
    fExpectedValue = 0.257988172;
    p_oGrid->GetValueOfCell(1, 1, p_oGrid->GetFloatDataCode("propeaten_1"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.05);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(1, 1, p_oGrid->GetFloatDataCode("propeaten_2"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.05);
    fExpectedValue = 0.603012682;
    p_oGrid->GetValueOfCell(1, 1, p_oGrid->GetFloatDataCode("propeaten_3"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.05);
    fExpectedValue = 0.999975593;
    p_oGrid->GetValueOfCell(1, 1, p_oGrid->GetFloatDataCode("propeaten_4"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.05);
    delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

/////////////////////////////////////////////////////////////////////////////
// TestNormalProcessingRun5()
// Fifth normal processing run. WriteNeighborhoodSeedPredationXMLFile5() does
// setup. Clone of run 1, except the method of determining masting is asking the
// disperse behaviors.
/////////////////////////////////////////////////////////////////////////////
TEST(NeighborhoodSeedPredation, TestNormalProcessingRun5)
{
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    //Feed our file to the sim manager
    p_oSimManager->ReadFile(WriteNeighborhoodSeedPredationXMLFile5());
    TestRun1And5(p_oSimManager);
    delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

/////////////////////////////////////////////////////////////////////////////
// TestNormalProcessingRun6()
// Sixth normal processing run. WriteNeighborhoodSeedPredationXMLFile6() does
// setup. Clone of run 2, except the method of determining masting is asking the
// disperse behaviors.
/////////////////////////////////////////////////////////////////////////////
TEST(NeighborhoodSeedPredation, TestNormalProcessingRun6)
{
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    p_oSimManager->ReadFile(WriteNeighborhoodSeedPredationXMLFile6());
    TestRun2And6(p_oSimManager);
    delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

/////////////////////////////////////////////////////////////////////////////
// TestNormalProcessingRun7()
// Seventh normal processing run. WriteNeighborhoodSeedPredationXMLFile7() does
// setup. Clone of run 2, except the method of determining masting is asking the
// disperse behaviors.
/////////////////////////////////////////////////////////////////////////////
TEST(NeighborhoodSeedPredation, TestNormalProcessingRun7) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    clTreePopulation *p_oPop;
    clTreeSearch *p_oAllSeedlings;
    clGrid *p_oGrid;
    clTree *p_oTree;
    float fX, fY, fXMin, fXMax, fYMin, fYMax,
    fValue, fExpectedValue,
    fXCellLength = 8, fYCellLength = 8;
    int *p_iNumSeedlings = new int[4], i;
    //Feed our file to the sim manager
    p_oSimManager->ReadFile(WriteNeighborhoodSeedPredationXMLFile7());
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );
    p_oGrid = p_oSimManager->GetGridObject("Neighborhood Seed Predation");
    ASSERT_TRUE(NULL != p_oGrid);

    //Run a timestep
    p_oSimManager->RunSim(1);

    //Count the number of seedlings in each grid cell
    p_oAllSeedlings = p_oPop->Find("type=1");

    //Check our values for cell 0, 0
    for (i = 0; i < 4; i++) {
      p_iNumSeedlings[i] = 0;
    }
    fYMin = 0;
    fYMax = fYCellLength;
    fXMin = 0;
    fXMax = fXCellLength;
    p_oTree = p_oAllSeedlings->NextTree();
    while (p_oTree) {
      p_oTree->GetValue(p_oPop->GetXCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fX);
      p_oTree->GetValue(p_oPop->GetYCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fY);
      if (fX >= fXMin && fX < fXMax && fY >= fYMin && fY < fYMax) {
        p_iNumSeedlings[p_oTree->GetSpecies()]++;
      }
      p_oTree = p_oAllSeedlings->NextTree();
    }
    EXPECT_TRUE(59 == p_iNumSeedlings[0] || 60 == p_iNumSeedlings[0]);
    EXPECT_TRUE(203 == p_iNumSeedlings[1] || 204 == p_iNumSeedlings[1]);
    EXPECT_EQ(128, p_iNumSeedlings[2]);
    EXPECT_EQ(64, p_iNumSeedlings[3]);

    //Check our values for cell 4, 4
    for (i = 0; i < 4; i++) {
      p_iNumSeedlings[i] = 0;
    }
    fXMin = 4 * fXCellLength;
    fXMax = (4 + 1) * fXCellLength;
    fYMin = 4 * fYCellLength;
    fYMax = (4 + 1) * fYCellLength;
    p_oAllSeedlings->StartOver();
    p_oTree = p_oAllSeedlings->NextTree();
    while (p_oTree) {
      p_oTree->GetValue(p_oPop->GetXCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fX);
      p_oTree->GetValue(p_oPop->GetYCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fY);
      if (fX >= fXMin && fX <= fXMax && fY >= fYMin && fY <= fYMax) {
        p_iNumSeedlings[p_oTree->GetSpecies()]++;
      }
      p_oTree = p_oAllSeedlings->NextTree();
    }
    EXPECT_TRUE(59 == p_iNumSeedlings[0] || 60 == p_iNumSeedlings[0]);
    EXPECT_TRUE(203 == p_iNumSeedlings[1] || 204 == p_iNumSeedlings[1]);
    EXPECT_EQ(128, p_iNumSeedlings[2]);
    EXPECT_EQ(64, p_iNumSeedlings[3]);

    //Check our grid values
    fExpectedValue = 64;
    p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("startseeds_0"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 256;
    p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("startseeds_1"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("startseeds_2"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 64;
    p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("startseeds_3"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

    fExpectedValue = 0.075160109;
    p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("propeaten_0"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.1);
    fExpectedValue = 0.204240302;
    p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("propeaten_1"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.1);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("propeaten_2"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.1);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("propeaten_3"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.1);

    fExpectedValue = 64;
    p_oGrid->GetValueOfCell(4, 4, p_oGrid->GetFloatDataCode("startseeds_0"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 256;
    p_oGrid->GetValueOfCell(4, 4, p_oGrid->GetFloatDataCode("startseeds_1"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(4, 4, p_oGrid->GetFloatDataCode("startseeds_2"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    fExpectedValue = 64;
    p_oGrid->GetValueOfCell(4, 4, p_oGrid->GetFloatDataCode("startseeds_3"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

    fExpectedValue = 0.075160109;
    p_oGrid->GetValueOfCell(4, 4, p_oGrid->GetFloatDataCode("propeaten_0"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.1);
    fExpectedValue = 0.204240302;
    p_oGrid->GetValueOfCell(4, 4, p_oGrid->GetFloatDataCode("propeaten_1"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.1);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(4, 4, p_oGrid->GetFloatDataCode("propeaten_2"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.1);
    fExpectedValue = 0;
    p_oGrid->GetValueOfCell(4, 4, p_oGrid->GetFloatDataCode("propeaten_3"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.1);

    delete[] p_iNumSeedlings;
    delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

/////////////////////////////////////////////////////////////////////////////
// TestRun1And5()
/////////////////////////////////////////////////////////////////////////////
void TestRun1And5(clSimManager *p_oSimManager) {
  clTreePopulation *p_oPop;
  clTreeSearch *p_oAllSeedlings;
  clGrid *p_oGrid;
  clTree *p_oTree;
  float fX, fY, fXMin, fXMax, fYMin, fYMax,
        fDbh,
        fValue, fExpectedValue,
        fXCellLength = 8, fYCellLength = 8;
  int *p_iNumSeedlings = new int[4], iSp, i;

  p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );
  p_oGrid = p_oSimManager->GetGridObject("Neighborhood Seed Predation");
  ASSERT_TRUE(NULL != p_oGrid);

  //Add our trees
  fX = 4; fY = 4;
  iSp = 0;
  fDbh = 5;
  for (i = 0; i < 100; i++)
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::sapling, fDbh);

  iSp = 2;
  fDbh = 14 ;
  for (i = 0; i < 100; i++)
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDbh);

  iSp = 1;
  fDbh = 10;
  p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDbh);

  iSp = 2;
  fDbh = 20;
  p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDbh);

  iSp = 3;
  fDbh = 15;
  p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDbh);

  iSp = 0;
  fDbh = 30;
  p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDbh);

  iSp = 1;
  fDbh = 35;
  p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDbh);

  iSp = 2;
  fDbh = 50;
  p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDbh);

  iSp = 3;
  fDbh = 21;
  p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDbh);

  fX = 34; fY = 34;
  iSp = 0;
  fDbh = 5;
  p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::sapling, fDbh);

  iSp = 1;
  fDbh = 10;
  p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDbh);

  iSp = 2;
  fDbh = 5;
  p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::sapling, fDbh);

  iSp = 3;
  fDbh = 5;
  p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::sapling, fDbh);

  iSp = 0;
  fDbh = 30;
  p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDbh);

  iSp = 1;
  fDbh = 35;
  p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDbh);

  iSp = 2;
  fDbh = 5;
  p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::sapling, fDbh);

  iSp = 3;
  fDbh = 5;
  p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::sapling, fDbh);

  //Run a timestep
  p_oSimManager->RunSim(1);

  //Count the number of seedlings in each grid cell
  p_oAllSeedlings = p_oPop->Find("type=1");

  //Check our values for cell 0, 0
  for (i = 0; i < 4; i++) {
    p_iNumSeedlings[i] = 0;
  }
  fYMin = 0;
  fYMax = fYCellLength;
  fXMin = 0;
  fXMax = fXCellLength;
  p_oTree = p_oAllSeedlings->NextTree();
  while (p_oTree) {
    p_oTree->GetValue(p_oPop->GetXCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fX);
    p_oTree->GetValue(p_oPop->GetYCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fY);
    if (fX >= fXMin && fX < fXMax && fY >= fYMin && fY < fYMax) {
      p_iNumSeedlings[p_oTree->GetSpecies()]++;
    }
    p_oTree = p_oAllSeedlings->NextTree();
  }
  EXPECT_TRUE(26 == p_iNumSeedlings[0] || 27 == p_iNumSeedlings[0]);
  EXPECT_TRUE(253 == p_iNumSeedlings[1] || 254 == p_iNumSeedlings[1]);
  EXPECT_EQ(128, p_iNumSeedlings[2]);
  EXPECT_EQ(64, p_iNumSeedlings[3]);

  //Check our values for cell 4, 4
  for (i = 0; i < 4; i++) {
    p_iNumSeedlings[i] = 0;
  }
  fXMin = 4 * fXCellLength;
  fXMax = (4 + 1) * fXCellLength;
  fYMin = 4 * fYCellLength;
  fYMax = (4 + 1) * fYCellLength;
  p_oAllSeedlings->StartOver();
  p_oTree = p_oAllSeedlings->NextTree();
  while (p_oTree) {
    p_oTree->GetValue(p_oPop->GetXCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fX);
    p_oTree->GetValue(p_oPop->GetYCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fY);
    if (fX >= fXMin && fX <= fXMax && fY >= fYMin && fY <= fYMax) {
      p_iNumSeedlings[p_oTree->GetSpecies()]++;
    }
    p_oTree = p_oAllSeedlings->NextTree();
  }
  EXPECT_TRUE(12 == p_iNumSeedlings[0] || 13 == p_iNumSeedlings[0]);
  EXPECT_TRUE(136 == p_iNumSeedlings[1] || 137 == p_iNumSeedlings[1]);
  EXPECT_EQ(128, p_iNumSeedlings[2]);
  EXPECT_EQ(64, p_iNumSeedlings[3]);

  //Check our grid values
  fExpectedValue = 64;
  p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("startseeds_0"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 256;
  p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("startseeds_1"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("startseeds_2"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 64;
  p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("startseeds_3"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

  fExpectedValue = 0.585715849;
  p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("propeaten_0"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.1);
  fExpectedValue = 0.009568214;
  p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("propeaten_1"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.1);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("propeaten_2"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.1);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("propeaten_3"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.1);

  fExpectedValue = 64;
  p_oGrid->GetValueOfCell(4, 4, p_oGrid->GetFloatDataCode("startseeds_0"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 256;
  p_oGrid->GetValueOfCell(4, 4, p_oGrid->GetFloatDataCode("startseeds_1"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(4, 4, p_oGrid->GetFloatDataCode("startseeds_2"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
  fExpectedValue = 64;
  p_oGrid->GetValueOfCell(4, 4, p_oGrid->GetFloatDataCode("startseeds_3"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

  fExpectedValue = 0.809911958;
  p_oGrid->GetValueOfCell(4, 4, p_oGrid->GetFloatDataCode("propeaten_0"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.1);
  fExpectedValue = 0.466175336;
  p_oGrid->GetValueOfCell(4, 4, p_oGrid->GetFloatDataCode("propeaten_1"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.1);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(4, 4, p_oGrid->GetFloatDataCode("propeaten_2"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.1);
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(4, 4, p_oGrid->GetFloatDataCode("propeaten_3"), &fValue);
  EXPECT_LT(fabs(fExpectedValue - fValue), 0.1);

  delete[] p_iNumSeedlings;
}

/////////////////////////////////////////////////////////////////////////////
// TestRun2And6()
/////////////////////////////////////////////////////////////////////////////
void TestRun2And6(clSimManager *p_oSimManager) {
  clTreePopulation *p_oPop;
  clTreeSearch *p_oAllSeedlings;
  clTree *p_oTree;
  clGrid *p_oSeeds;
  float fX, fY, fXMin, fXMax, fYMin, fYMax,
        fDbh, fValue,
        fXCellLength = 8, fYCellLength = 8;
  int *p_iNumSeedlings = new int[4], i, iSp;

  //Feed our file to the sim manager
  p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );

  //Add our trees
  fX = 4; fY = 4;
  iSp = 0;
  fDbh = 5;
  p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::sapling, fDbh);

  fDbh = 10;
  p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDbh);

  fDbh = 20;
  p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDbh);

  fDbh = 15;
  p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDbh);

  fDbh = 30;
  p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDbh);

  fDbh = 35;
  p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDbh);

  fDbh = 50;
  p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDbh);

  fDbh = 21;
  p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDbh);

  //Add the seeds to the appropriate grid cells
  p_oSeeds = p_oSimManager->GetGridObject("Dispersed Seeds");
  fValue = 10000;
  p_oSeeds->SetValueOfCell(0, 0, p_oSeeds->GetFloatDataCode("seeds_0"), fValue);
  fValue = 100;
  p_oSeeds->SetValueOfCell(4, 4, p_oSeeds->GetFloatDataCode("seeds_1"), fValue);

  //Run a timestep
  p_oSimManager->RunSim(1);

  //Count the number of seedlings in each grid cell
  p_oAllSeedlings = p_oPop->Find("type=1");

  //Check our values for cell 0, 0
  for (i = 0; i < 4; i++) {
    p_iNumSeedlings[i] = 0;
  }
  fYMin = 0;
  fYMax = fYCellLength;
  fXMin = 0;
  fXMax = fXCellLength;
  p_oTree = p_oAllSeedlings->NextTree();
  while (p_oTree) {
    p_oTree->GetValue(p_oPop->GetXCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fX);
    p_oTree->GetValue(p_oPop->GetYCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fY);
    if (fX >= fXMin && fX < fXMax && fY >= fYMin && fY < fYMax) {
      p_iNumSeedlings[p_oTree->GetSpecies()]++;
    }
    p_oTree = p_oAllSeedlings->NextTree();
  }
  EXPECT_TRUE(9902 == p_iNumSeedlings[0] || 9903 == p_iNumSeedlings[0]);
  EXPECT_EQ(0, p_iNumSeedlings[1]);
  EXPECT_EQ(0, p_iNumSeedlings[2]);
  EXPECT_EQ(0, p_iNumSeedlings[3]);

  //Check our values for cell 4, 4
  for (i = 0; i < 4; i++) {
    p_iNumSeedlings[i] = 0;
  }
  fXMin = 4 * fXCellLength;
  fXMax = (4 + 1) * fXCellLength;
  fYMin = 4 * fYCellLength;
  fYMax = (4 + 1) * fYCellLength;
  p_oAllSeedlings->StartOver();
  p_oTree = p_oAllSeedlings->NextTree();
  while (p_oTree) {
    p_oTree->GetValue(p_oPop->GetXCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fX);
    p_oTree->GetValue(p_oPop->GetYCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fY);
    if (fX >= fXMin && fX <= fXMax && fY >= fYMin && fY <= fYMax) {
      p_iNumSeedlings[p_oTree->GetSpecies()]++;
    }
    p_oTree = p_oAllSeedlings->NextTree();
  }
  EXPECT_EQ(0, p_iNumSeedlings[0]);
  EXPECT_TRUE(29 == p_iNumSeedlings[1] || 30 == p_iNumSeedlings[1]);
  EXPECT_EQ(0, p_iNumSeedlings[2]);
  EXPECT_EQ(0, p_iNumSeedlings[3]);

  delete[] p_iNumSeedlings;
}

/////////////////////////////////////////////////////////////////////////////
// TestErrorProcessing()
/////////////////////////////////////////////////////////////////////////////
TEST(NeighborhoodSeedPredation, TestErrorProcessing)
{
  using namespace std;
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try
  {
    p_oSimManager->ReadFile(WriteNeighborhoodSeedPredationXMLErrorFile1());
    FAIL() << "TestNeighborhoodSeedPredation error processing didn't catch error for WriteNeighborhoodSeedPredationXMLErrorFile1.";
  }
  catch (modelErr& err)
  {
    if (err.sFunction.compare("clNeighborhoodSeedPredation::ReadParameterFileData") != 0 ||
        err.sMoreInfo.find("Minimum neighbor DBH") == string::npos)
    {
      FAIL() << "TestNeighborhoodSeedPredation error processing caught wrong error for WriteNeighborhoodSeedPredationXMLErrorFile1.";
    }
    ;
  }

  try
  {
    p_oSimManager->ReadFile(WriteNeighborhoodSeedPredationXMLErrorFile2());
    FAIL() << "TestNeighborhoodSeedPredation error processing didn't catch error for WriteNeighborhoodSeedPredationXMLErrorFile2.";
  }
  catch (modelErr& err)
  {
    if (err.sFunction.compare("clNeighborhoodSeedPredation::ReadParameterFileData") != 0 ||
        err.sMoreInfo.find("Masting seed density threshold") == string::npos)
    {
      FAIL() << "TestNeighborhoodSeedPredation error processing caught wrong error for WriteNeighborhoodSeedPredationXMLErrorFile2.";
    }
    ;
  }

  try
  {
    p_oSimManager->ReadFile(WriteNeighborhoodSeedPredationXMLErrorFile3());
    FAIL() << "TestNeighborhoodSeedPredation error processing didn't catch error for WriteNeighborhoodSeedPredationXMLErrorFile3.";
  }
  catch (modelErr& err)
  {
    if (err.sFunction.compare("clNeighborhoodSeedPredation::ReadParameterFileData") != 0 ||
        err.sMoreInfo.find("Neighborhood radius") == string::npos)
    {
      FAIL() << "TestNeighborhoodSeedPredation error processing caught wrong error for WriteNeighborhoodSeedPredationXMLErrorFile3.";
    }
    ;
  }

  try
  {
    p_oSimManager->ReadFile(WriteNeighborhoodSeedPredationXMLErrorFile4());
    FAIL() << "TestNeighborhoodSeedPredation error processing didn't catch error for WriteNeighborhoodSeedPredationXMLErrorFile4.";
  }
  catch (modelErr& err)
  {
    if (err.sFunction.compare("clNeighborhoodSeedPredation::SetupGrids") != 0 ||
        err.sMoreInfo.find("Disperse behavior") == string::npos)
    {
      FAIL() << "TestNeighborhoodSeedPredation error processing caught wrong error for WriteNeighborhoodSeedPredationXMLErrorFile4.";
    }
    ;
  }

  try
  {
    p_oSimManager->ReadFile(WriteNeighborhoodSeedPredationXMLErrorFile5());
    FAIL() << "TestNeighborhoodSeedPredation error processing didn't catch error for WriteNeighborhoodSeedPredationXMLErrorFile5.";
  }
  catch (modelErr& err)
  {
    if (err.sFunction.compare("clNeighborhoodSeedPredation::GetData") != 0 ||
        err.sMoreInfo.find("functional response") == string::npos)
    {
      FAIL() << "TestNeighborhoodSeedPredation error processing caught wrong error for WriteNeighborhoodSeedPredationXMLErrorFile5.";
    }
    ;
  }
  delete p_oSimManager;
}

/////////////////////////////////////////////////////////////////////////////
// WriteNeighborhoodSeedPredationXMLFile1()
/////////////////////////////////////////////////////////////////////////////
const char* WriteNeighborhoodSeedPredationXMLFile1()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06010101\">" << "<plot>"
       << "<timesteps>1</timesteps>"
       << "<yearsPerTimestep>1</yearsPerTimestep>"
       << "<randomSeed>1</randomSeed>"
       << "<plot_lenX>96</plot_lenX>"
       << "<plot_lenY>96</plot_lenY>"
       << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
       << "<plot_temp_C>12.88171785</plot_temp_C>"
       << "<plot_latitude>55.37</plot_latitude>"
       << "</plot>";

  WriteNeighborhoodSeedPredationTreesAllometry(oOut);

  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>NonSpatialDisperse</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_4\" type=\"Adult\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>NeighborhoodSeedPredation</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>2</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Seed\"/>"
       << "<applyTo species=\"Species_2\" type=\"Seed\"/>"
       << "<applyTo species=\"Species_4\" type=\"Seed\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>Establishment</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>3</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Seed\"/>"
       << "<applyTo species=\"Species_2\" type=\"Seed\"/>"
       << "<applyTo species=\"Species_3\" type=\"Seed\"/>"
       << "<applyTo species=\"Species_4\" type=\"Seed\"/>"
       << "</behavior>"
       << "</behaviorList>"
       << "<GeneralDisperse>"
       << "<di_seedDistributionMethod>0</di_seedDistributionMethod>"
       << "</GeneralDisperse>"
       << "<NonSpatialDisperse1>"
       << "<di_minDbhForReproduction>"
       << "<di_mdfrVal species=\"Species_1\">15.0</di_mdfrVal>"
       << "<di_mdfrVal species=\"Species_2\">15.0</di_mdfrVal>"
       << "<di_mdfrVal species=\"Species_3\">15.0</di_mdfrVal>"
       << "<di_mdfrVal species=\"Species_4\">15.0</di_mdfrVal>"
       << "</di_minDbhForReproduction>"
       << "<di_nonSpatialSlopeOfLambda>"
       << "<di_nssolVal species=\"Species_4\">0</di_nssolVal>"
       << "<di_nssolVal species=\"Species_2\">0</di_nssolVal>"
       << "<di_nssolVal species=\"Species_3\">0</di_nssolVal>"
       << "<di_nssolVal species=\"Species_1\">0</di_nssolVal>"
       << "</di_nonSpatialSlopeOfLambda>"
       << "<di_nonSpatialInterceptOfLambda>"
       << "<di_nsiolVal species=\"Species_1\">1</di_nsiolVal>"
       << "<di_nsiolVal species=\"Species_2\">4</di_nsiolVal>"
       << "<di_nsiolVal species=\"Species_3\">2</di_nsiolVal>"
       << "<di_nsiolVal species=\"Species_4\">1</di_nsiolVal>"
       << "</di_nonSpatialInterceptOfLambda>"
       << "</NonSpatialDisperse1>"
       << "<NeighborhoodSeedPredation2>";

  WriteNeighborhoodSeedPredationCommonPredationParameters(oOut);

  oOut << "<pr_neighPredMastDecisionMethod>0</pr_neighPredMastDecisionMethod>"
       << "<pr_neighPredMastingDensity>4</pr_neighPredMastingDensity>"
       << "<pr_neighPredRadius>10</pr_neighPredRadius>"
       << "<pr_neighPredMinNeighDBH>"
       << "<pr_npmndVal species=\"Species_1\">10</pr_npmndVal>"
       << "<pr_npmndVal species=\"Species_2\">10</pr_npmndVal>"
       << "<pr_npmndVal species=\"Species_3\">15</pr_npmndVal>"
       << "<pr_npmndVal species=\"Species_4\">10</pr_npmndVal>"
       << "</pr_neighPredMinNeighDBH>"
       << "<pr_neighPredCounts4Mast>"
       << "<pr_npc4mVal species=\"Species_1\">1</pr_npc4mVal>"
       << "<pr_npc4mVal species=\"Species_2\">0</pr_npc4mVal>"
       << "<pr_npc4mVal species=\"Species_4\">1</pr_npc4mVal>"
       << "</pr_neighPredCounts4Mast>"
       << "</NeighborhoodSeedPredation2>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}


/////////////////////////////////////////////////////////////////////////////
// WriteNeighborhoodSeedPredationXMLFile2()
/////////////////////////////////////////////////////////////////////////////
const char* WriteNeighborhoodSeedPredationXMLFile2()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06010101\">" << "<plot>"
       << "<timesteps>1</timesteps>"
       << "<yearsPerTimestep>1</yearsPerTimestep>"
       << "<randomSeed>1</randomSeed>"
       << "<plot_lenX>96</plot_lenX>"
       << "<plot_lenY>96</plot_lenY>"
       << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
       << "<plot_temp_C>12.88171785</plot_temp_C>"
       << "<plot_latitude>55.37</plot_latitude>"
       << "</plot>";

  WriteNeighborhoodSeedPredationTreesAllometry(oOut);

  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>NonSpatialDisperse</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_4\" type=\"Adult\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>NeighborhoodSeedPredation</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>2</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Seed\"/>"
       << "<applyTo species=\"Species_2\" type=\"Seed\"/>"
       << "<applyTo species=\"Species_4\" type=\"Seed\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>Establishment</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>3</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Seed\"/>"
       << "<applyTo species=\"Species_2\" type=\"Seed\"/>"
       << "<applyTo species=\"Species_3\" type=\"Seed\"/>"
       << "<applyTo species=\"Species_4\" type=\"Seed\"/>"
       << "</behavior>"
       << "</behaviorList>"
       << "<GeneralDisperse>"
       << "<di_seedDistributionMethod>0</di_seedDistributionMethod>"
       << "</GeneralDisperse>"
       << "<NonSpatialDisperse1>"
       << "<di_minDbhForReproduction>"
       << "<di_mdfrVal species=\"Species_1\">15.0</di_mdfrVal>"
       << "<di_mdfrVal species=\"Species_2\">15.0</di_mdfrVal>"
       << "<di_mdfrVal species=\"Species_3\">15.0</di_mdfrVal>"
       << "<di_mdfrVal species=\"Species_4\">15.0</di_mdfrVal>"
       << "</di_minDbhForReproduction>"
       << "<di_nonSpatialSlopeOfLambda>"
       << "<di_nssolVal species=\"Species_4\">0</di_nssolVal>"
       << "<di_nssolVal species=\"Species_2\">0</di_nssolVal>"
       << "<di_nssolVal species=\"Species_3\">0</di_nssolVal>"
       << "<di_nssolVal species=\"Species_1\">0</di_nssolVal>"
       << "</di_nonSpatialSlopeOfLambda>"
       << "<di_nonSpatialInterceptOfLambda>"
       << "<di_nsiolVal species=\"Species_1\">0</di_nsiolVal>"
       << "<di_nsiolVal species=\"Species_2\">0</di_nsiolVal>"
       << "<di_nsiolVal species=\"Species_3\">0</di_nsiolVal>"
       << "<di_nsiolVal species=\"Species_4\">0</di_nsiolVal>"
       << "</di_nonSpatialInterceptOfLambda>"
       << "</NonSpatialDisperse1>"
       << "<NeighborhoodSeedPredation2>"
       << "<pr_neighPredMastDecisionMethod>0</pr_neighPredMastDecisionMethod>"
       << "<pr_neighPredMastingDensity>1</pr_neighPredMastingDensity>"
       << "<pr_neighPredRadius>10</pr_neighPredRadius>"
       << "<pr_neighPredMinNeighDBH>"
       << "<pr_npmndVal species=\"Species_1\">10</pr_npmndVal>"
       << "<pr_npmndVal species=\"Species_2\">10</pr_npmndVal>"
       << "<pr_npmndVal species=\"Species_3\">10</pr_npmndVal>"
       << "<pr_npmndVal species=\"Species_4\">10</pr_npmndVal>"
       << "</pr_neighPredMinNeighDBH>";

  WriteNeighborhoodSeedPredationCommonPredationParameters(oOut);

  oOut << "<pr_neighPredCounts4Mast>"
       << "<pr_npc4mVal species=\"Species_1\">1</pr_npc4mVal>"
       << "<pr_npc4mVal species=\"Species_2\">1</pr_npc4mVal>"
       << "<pr_npc4mVal species=\"Species_4\">1</pr_npc4mVal>"
       << "</pr_neighPredCounts4Mast>"
       << "</NeighborhoodSeedPredation2>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteNeighborhoodSeedPredationXMLFile3()
/////////////////////////////////////////////////////////////////////////////
const char* WriteNeighborhoodSeedPredationXMLFile3()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06010101\">"
       << "<plot>"
       << "<timesteps>1</timesteps>"
       << "<yearsPerTimestep>3</yearsPerTimestep>"
       << "<randomSeed>1</randomSeed>"
       << "<plot_lenX>96</plot_lenX>"
       << "<plot_lenY>96</plot_lenY>"
       << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
       << "<plot_temp_C>12.88171785</plot_temp_C>"
       << "<plot_latitude>55.37</plot_latitude>"
       << "</plot>";

  WriteNeighborhoodSeedPredationTreesAllometry(oOut);

  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>NonSpatialDisperse</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_4\" type=\"Adult\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>NeighborhoodSeedPredation</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>2</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Seed\"/>"
       << "<applyTo species=\"Species_2\" type=\"Seed\"/>"
       << "<applyTo species=\"Species_4\" type=\"Seed\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>Establishment</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>3</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Seed\"/>"
       << "<applyTo species=\"Species_2\" type=\"Seed\"/>"
       << "<applyTo species=\"Species_3\" type=\"Seed\"/>"
       << "<applyTo species=\"Species_4\" type=\"Seed\"/>"
       << "</behavior>"
       << "</behaviorList>"
       << "<GeneralDisperse>"
       << "<di_seedDistributionMethod>0</di_seedDistributionMethod>"
       << "</GeneralDisperse>"
       << "<NonSpatialDisperse1>"
       << "<di_minDbhForReproduction>"
       << "<di_mdfrVal species=\"Species_1\">15.0</di_mdfrVal>"
       << "<di_mdfrVal species=\"Species_2\">15.0</di_mdfrVal>"
       << "<di_mdfrVal species=\"Species_3\">15.0</di_mdfrVal>"
       << "<di_mdfrVal species=\"Species_4\">15.0</di_mdfrVal>"
       << "</di_minDbhForReproduction>"
       << "<di_nonSpatialSlopeOfLambda>"
       << "<di_nssolVal species=\"Species_4\">0</di_nssolVal>"
       << "<di_nssolVal species=\"Species_2\">0</di_nssolVal>"
       << "<di_nssolVal species=\"Species_3\">0</di_nssolVal>"
       << "<di_nssolVal species=\"Species_1\">0</di_nssolVal>"
       << "</di_nonSpatialSlopeOfLambda>"
       << "<di_nonSpatialInterceptOfLambda>"
       << "<di_nsiolVal species=\"Species_1\">1</di_nsiolVal>"
       << "<di_nsiolVal species=\"Species_2\">1</di_nsiolVal>"
       << "<di_nsiolVal species=\"Species_3\">2</di_nsiolVal>"
       << "<di_nsiolVal species=\"Species_4\">1</di_nsiolVal>"
       << "</di_nonSpatialInterceptOfLambda>"
       << "</NonSpatialDisperse1>"
       << "<NeighborhoodSeedPredation2>"
       << "<pr_neighPredMastDecisionMethod>0</pr_neighPredMastDecisionMethod>"
       << "<pr_neighPredMastingDensity>4</pr_neighPredMastingDensity>"
       << "<pr_neighPredRadius>10</pr_neighPredRadius>"
       << "<pr_neighPredMinNeighDBH>"
       << "<pr_npmndVal species=\"Species_1\">10</pr_npmndVal>"
       << "<pr_npmndVal species=\"Species_2\">10</pr_npmndVal>"
       << "<pr_npmndVal species=\"Species_3\">10</pr_npmndVal>"
       << "<pr_npmndVal species=\"Species_4\">10</pr_npmndVal>"
       << "</pr_neighPredMinNeighDBH>";

  WriteNeighborhoodSeedPredationCommonPredationParameters(oOut);

  oOut << "<pr_neighPredCounts4Mast>"
       << "<pr_npc4mVal species=\"Species_1\">1</pr_npc4mVal>"
       << "<pr_npc4mVal species=\"Species_2\">1</pr_npc4mVal>"
       << "<pr_npc4mVal species=\"Species_4\">1</pr_npc4mVal>"
       << "</pr_neighPredCounts4Mast>"
       << "</NeighborhoodSeedPredation2>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteNeighborhoodSeedPredationXMLFile4()
/////////////////////////////////////////////////////////////////////////////
const char* WriteNeighborhoodSeedPredationXMLFile4()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06010101\">"
       << "<plot>"
       << "<timesteps>1</timesteps>"
       << "<yearsPerTimestep>1</yearsPerTimestep>"
       << "<randomSeed>1</randomSeed>"
       << "<plot_lenX>100</plot_lenX>"
       << "<plot_lenY>100</plot_lenY>"
       << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
       << "<plot_temp_C>12.88171785</plot_temp_C>"
       << "<plot_latitude>55.37</plot_latitude>"
       << "</plot>";

  oOut << "<trees>"
       << "<tr_speciesList>"
       << "<tr_species speciesName=\"Species_1\"/>"
       << "<tr_species speciesName=\"Species_2\"/>"
       << "<tr_species speciesName=\"Species_3\"/>"
       << "<tr_species speciesName=\"Species_4\"/>"
       << "<tr_species speciesName=\"Species_5\"/>"
       << "</tr_speciesList>"
       << "<tr_seedDiam10Cm>0.1</tr_seedDiam10Cm>"
       << "<tr_minAdultDBH>"
       << "<tr_madVal species=\"Species_1\">10.0</tr_madVal>"
       << "<tr_madVal species=\"Species_2\">10.0</tr_madVal>"
       << "<tr_madVal species=\"Species_3\">10.0</tr_madVal>"
       << "<tr_madVal species=\"Species_4\">10.0</tr_madVal>"
       << "<tr_madVal species=\"Species_5\">10.0</tr_madVal>"
       << "</tr_minAdultDBH>"
       << "<tr_maxSeedlingHeight>"
       << "<tr_mshVal species=\"Species_1\">1.35</tr_mshVal>"
       << "<tr_mshVal species=\"Species_2\">1.35</tr_mshVal>"
       << "<tr_mshVal species=\"Species_3\">1.35</tr_mshVal>"
       << "<tr_mshVal species=\"Species_4\">1.35</tr_mshVal>"
       << "<tr_mshVal species=\"Species_5\">1.35</tr_mshVal>"
       << "</tr_maxSeedlingHeight>"
       << "</trees>"
       << "<allometry>"
       << "<tr_canopyHeight>"
       << "<tr_chVal species=\"Species_1\">39.48</tr_chVal>"
       << "<tr_chVal species=\"Species_2\">39.54</tr_chVal>"
       << "<tr_chVal species=\"Species_3\">40.0</tr_chVal>"
       << "<tr_chVal species=\"Species_4\">40.0</tr_chVal>"
       << "<tr_chVal species=\"Species_5\">40.0</tr_chVal>"
       << "</tr_canopyHeight>"
       << "<tr_stdAsympCrownRad>"
       << "<tr_sacrVal species=\"Species_1\">0.0549</tr_sacrVal>"
       << "<tr_sacrVal species=\"Species_2\">0.0614</tr_sacrVal>"
       << "<tr_sacrVal species=\"Species_3\">0.0242</tr_sacrVal>"
       << "<tr_sacrVal species=\"Species_4\">0.0242</tr_sacrVal>"
       << "<tr_sacrVal species=\"Species_5\">0.0242</tr_sacrVal>"
       << "</tr_stdAsympCrownRad>"
       << "<tr_stdCrownRadExp>"
       << "<tr_screVal species=\"Species_1\">1.0</tr_screVal>"
       << "<tr_screVal species=\"Species_2\">1.0</tr_screVal>"
       << "<tr_screVal species=\"Species_3\">1.0</tr_screVal>"
       << "<tr_screVal species=\"Species_4\">1.0</tr_screVal>"
       << "<tr_screVal species=\"Species_5\">1.0</tr_screVal>"
       << "</tr_stdCrownRadExp>"
       << "<tr_conversionDiam10ToDBH>"
       << "<tr_cdtdVal species=\"Species_1\">0.8008</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_2\">0.5944</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_3\">0.7059</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_4\">0.7059</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_5\">0.7059</tr_cdtdVal>"
       << "</tr_conversionDiam10ToDBH>"
       << "<tr_interceptDiam10ToDBH>"
       << "<tr_idtdVal species=\"Species_1\">0</tr_idtdVal>"
       << "<tr_idtdVal species=\"Species_2\">0</tr_idtdVal>"
       << "<tr_idtdVal species=\"Species_3\">0</tr_idtdVal>"
       << "<tr_idtdVal species=\"Species_4\">0</tr_idtdVal>"
       << "<tr_idtdVal species=\"Species_5\">0</tr_idtdVal>"
       << "</tr_interceptDiam10ToDBH>"
       << "<tr_stdAsympCrownHt>"
       << "<tr_sachVal species=\"Species_1\">0.389</tr_sachVal>"
       << "<tr_sachVal species=\"Species_2\">0.368</tr_sachVal>"
       << "<tr_sachVal species=\"Species_3\">0.464</tr_sachVal>"
       << "<tr_sachVal species=\"Species_4\">0.464</tr_sachVal>"
       << "<tr_sachVal species=\"Species_5\">0.464</tr_sachVal>"
       << "</tr_stdAsympCrownHt>"
       << "<tr_stdCrownHtExp>"
       << "<tr_scheVal species=\"Species_1\">1.0</tr_scheVal>"
       << "<tr_scheVal species=\"Species_2\">1.0</tr_scheVal>"
       << "<tr_scheVal species=\"Species_3\">1.0</tr_scheVal>"
       << "<tr_scheVal species=\"Species_4\">1.0</tr_scheVal>"
       << "<tr_scheVal species=\"Species_5\">1.0</tr_scheVal>"
       << "</tr_stdCrownHtExp>"
       << "<tr_slopeOfHeight-Diam10>"
       << "<tr_sohdVal species=\"Species_1\">0.03418</tr_sohdVal>"
       << "<tr_sohdVal species=\"Species_2\">0.0269</tr_sohdVal>"
       << "<tr_sohdVal species=\"Species_3\">0.02871</tr_sohdVal>"
       << "<tr_sohdVal species=\"Species_4\">0.02871</tr_sohdVal>"
       << "<tr_sohdVal species=\"Species_5\">0.02871</tr_sohdVal>"
       << "</tr_slopeOfHeight-Diam10>"
       << "<tr_slopeOfAsymHeight>"
       << "<tr_soahVal species=\"Species_1\">0.0299</tr_soahVal>"
       << "<tr_soahVal species=\"Species_2\">0.0241</tr_soahVal>"
       << "<tr_soahVal species=\"Species_3\">0.0263</tr_soahVal>"
       << "<tr_soahVal species=\"Species_4\">0.0263</tr_soahVal>"
       << "<tr_soahVal species=\"Species_5\">0.0263</tr_soahVal>"
       << "</tr_slopeOfAsymHeight>"
       << "<tr_whatSeedlingHeightDiam>"
       << "<tr_wsehdVal species=\"Species_1\">0</tr_wsehdVal>"
       << "<tr_wsehdVal species=\"Species_2\">0</tr_wsehdVal>"
       << "<tr_wsehdVal species=\"Species_3\">0</tr_wsehdVal>"
       << "<tr_wsehdVal species=\"Species_4\">0</tr_wsehdVal>"
       << "<tr_wsehdVal species=\"Species_5\">0</tr_wsehdVal>"
       << "</tr_whatSeedlingHeightDiam>"
       << "<tr_whatSaplingHeightDiam>"
       << "<tr_wsahdVal species=\"Species_1\">0</tr_wsahdVal>"
       << "<tr_wsahdVal species=\"Species_2\">0</tr_wsahdVal>"
       << "<tr_wsahdVal species=\"Species_3\">0</tr_wsahdVal>"
       << "<tr_wsahdVal species=\"Species_4\">0</tr_wsahdVal>"
       << "<tr_wsahdVal species=\"Species_5\">0</tr_wsahdVal>"
       << "</tr_whatSaplingHeightDiam>"
       << "<tr_whatAdultHeightDiam>"
       << "<tr_wahdVal species=\"Species_1\">0</tr_wahdVal>"
       << "<tr_wahdVal species=\"Species_2\">0</tr_wahdVal>"
       << "<tr_wahdVal species=\"Species_3\">0</tr_wahdVal>"
       << "<tr_wahdVal species=\"Species_4\">0</tr_wahdVal>"
       << "<tr_wahdVal species=\"Species_5\">0</tr_wahdVal>"
       << "</tr_whatAdultHeightDiam>"
       << "<tr_whatAdultCrownRadDiam>"
       << "<tr_wacrdVal species=\"Species_1\">0</tr_wacrdVal>"
       << "<tr_wacrdVal species=\"Species_2\">0</tr_wacrdVal>"
       << "<tr_wacrdVal species=\"Species_3\">0</tr_wacrdVal>"
       << "<tr_wacrdVal species=\"Species_4\">0</tr_wacrdVal>"
       << "<tr_wacrdVal species=\"Species_5\">0</tr_wacrdVal>"
       << "</tr_whatAdultCrownRadDiam>"
       << "<tr_whatAdultCrownHeightHeight>"
       << "<tr_wachhVal species=\"Species_1\">0</tr_wachhVal>"
       << "<tr_wachhVal species=\"Species_2\">0</tr_wachhVal>"
       << "<tr_wachhVal species=\"Species_3\">0</tr_wachhVal>"
       << "<tr_wachhVal species=\"Species_4\">0</tr_wachhVal>"
       << "<tr_wachhVal species=\"Species_5\">0</tr_wachhVal>"
       << "</tr_whatAdultCrownHeightHeight>"
       << "<tr_whatSaplingCrownRadDiam>"
       << "<tr_wscrdVal species=\"Species_1\">0</tr_wscrdVal>"
       << "<tr_wscrdVal species=\"Species_2\">0</tr_wscrdVal>"
       << "<tr_wscrdVal species=\"Species_3\">0</tr_wscrdVal>"
       << "<tr_wscrdVal species=\"Species_4\">0</tr_wscrdVal>"
       << "<tr_wscrdVal species=\"Species_5\">0</tr_wscrdVal>"
       << "</tr_whatSaplingCrownRadDiam>"
       << "<tr_whatSaplingCrownHeightHeight>"
       << "<tr_wschhVal species=\"Species_1\">0</tr_wschhVal>"
       << "<tr_wschhVal species=\"Species_2\">0</tr_wschhVal>"
       << "<tr_wschhVal species=\"Species_3\">0</tr_wschhVal>"
       << "<tr_wschhVal species=\"Species_4\">0</tr_wschhVal>"
       << "<tr_wschhVal species=\"Species_5\">0</tr_wschhVal>"
       << "</tr_whatSaplingCrownHeightHeight>"
       << "</allometry>";

  oOut << "<grid gridName=\"Dispersed Seeds\">"
       << "<ma_floatCodes>"
       << "<ma_floatCode label=\"seeds_0\">0</ma_floatCode>"
       << "<ma_floatCode label=\"seeds_1\">1</ma_floatCode>"
       << "<ma_floatCode label=\"seeds_2\">2</ma_floatCode>"
       << "<ma_floatCode label=\"seeds_3\">3</ma_floatCode>"
       << "<ma_floatCode label=\"seeds_4\">4</ma_floatCode>"
       << "</ma_floatCodes>"
       << "<ma_intCodes>"
       << "<ma_intCode label=\"count\">0</ma_intCode>"
       << "</ma_intCodes>"
       << "<ma_boolCodes>"
       << "<ma_boolCode label=\"Is Gap\">0</ma_boolCode>"
       << "</ma_boolCodes>"
       << "<ma_lengthXCells>50</ma_lengthXCells>"
       << "<ma_lengthYCells>50</ma_lengthYCells>"
       << "</grid>";

  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>NonSpatialDisperse</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_4\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_5\" type=\"Adult\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>LinkedFunctionalResponseSeedPredation</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>2</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Seed\"/>"
       << "<applyTo species=\"Species_2\" type=\"Seed\"/>"
       << "<applyTo species=\"Species_4\" type=\"Seed\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>LinkedNeighborhoodSeedPredation</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>3</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Seed\"/>"
       << "<applyTo species=\"Species_2\" type=\"Seed\"/>"
       << "<applyTo species=\"Species_4\" type=\"Seed\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>NeighborhoodSeedPredation</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>4</listPosition>"
       << "<applyTo species=\"Species_5\" type=\"Seed\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>Establishment</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>5</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Seed\"/>"
       << "<applyTo species=\"Species_2\" type=\"Seed\"/>"
       << "<applyTo species=\"Species_3\" type=\"Seed\"/>"
       << "<applyTo species=\"Species_4\" type=\"Seed\"/>"
       << "<applyTo species=\"Species_5\" type=\"Seed\"/>"
       << "</behavior>"
       << "</behaviorList>"
       << "<GeneralDisperse>"
       << "<di_seedDistributionMethod>0</di_seedDistributionMethod>"
       << "</GeneralDisperse>"
       << "<NonSpatialDisperse1>"
       << "<di_minDbhForReproduction>"
       << "<di_mdfrVal species=\"Species_1\">15.0</di_mdfrVal>"
       << "<di_mdfrVal species=\"Species_2\">15.0</di_mdfrVal>"
       << "<di_mdfrVal species=\"Species_3\">15.0</di_mdfrVal>"
       << "<di_mdfrVal species=\"Species_4\">15.0</di_mdfrVal>"
       << "<di_mdfrVal species=\"Species_5\">15.0</di_mdfrVal>"
       << "</di_minDbhForReproduction>"
       << "<di_nonSpatialSlopeOfLambda>"
       << "<di_nssolVal species=\"Species_5\">0</di_nssolVal>"
       << "<di_nssolVal species=\"Species_4\">0</di_nssolVal>"
       << "<di_nssolVal species=\"Species_2\">0</di_nssolVal>"
       << "<di_nssolVal species=\"Species_3\">0</di_nssolVal>"
       << "<di_nssolVal species=\"Species_1\">0</di_nssolVal>"
       << "</di_nonSpatialSlopeOfLambda>"
       << "<di_nonSpatialInterceptOfLambda>"
       << "<di_nsiolVal species=\"Species_1\">1</di_nsiolVal>"
       << "<di_nsiolVal species=\"Species_2\">1</di_nsiolVal>"
       << "<di_nsiolVal species=\"Species_3\">2</di_nsiolVal>"
       << "<di_nsiolVal species=\"Species_4\">1</di_nsiolVal>"
       << "<di_nsiolVal species=\"Species_5\">1</di_nsiolVal>"
       << "</di_nonSpatialInterceptOfLambda>"
       << "</NonSpatialDisperse1>"
       << "<FunctionalResponseSeedPredation2>"
       << "<pr_funcRespMaxInstDeclineRate1>-0.04</pr_funcRespMaxInstDeclineRate1>"
       << "<pr_funcRespMaxInstDeclineRate2>-0.04</pr_funcRespMaxInstDeclineRate2>"
       << "<pr_funcRespDemographicEfficiency1>0.0002</pr_funcRespDemographicEfficiency1>"
       << "<pr_funcRespDemographicEfficiency2>0.0002</pr_funcRespDemographicEfficiency2>"
       << "<pr_funcRespDensityDependentCoefficient1>-0.008</pr_funcRespDensityDependentCoefficient1>"
       << "<pr_funcRespDensityDependentCoefficient2>-0.008</pr_funcRespDensityDependentCoefficient2>"
       << "<pr_funcRespPredatorInitialDensity>0.002</pr_funcRespPredatorInitialDensity>"
       << "<pr_maxIntakeRate>20</pr_maxIntakeRate>"
       << "<pr_funcRespMaxIntakeRate>"
       << "<pr_frmirVal species=\"Species_1\">20</pr_frmirVal>"
       << "<pr_frmirVal species=\"Species_2\">20</pr_frmirVal>"
       << "<pr_frmirVal species=\"Species_4\">20</pr_frmirVal>"
       << "</pr_funcRespMaxIntakeRate>"
       << "<pr_funcRespForagingEfficiency>"
       << "<pr_frfeVal species=\"Species_1\">0.002</pr_frfeVal>"
       << "<pr_frfeVal species=\"Species_2\">0.002</pr_frfeVal>"
       << "<pr_frfeVal species=\"Species_4\">0.002</pr_frfeVal>"
       << "</pr_funcRespForagingEfficiency>"
       << "<pr_funcRespWeekSeason2Starts>12</pr_funcRespWeekSeason2Starts>"
       << "<pr_funcRespNumWeeksSeedFall>12</pr_funcRespNumWeeksSeedFall>"
       << "<pr_funcRespNumWeeksToModel>45</pr_funcRespNumWeeksToModel>"
       << "<pr_funcRespWeekGerminationStarts>30</pr_funcRespWeekGerminationStarts>"
       << "<pr_funcRespPreservePredatorDensities>0</pr_funcRespPreservePredatorDensities>"
       << "<pr_funcRespProportionGerminating>0.4</pr_funcRespProportionGerminating>"
       << "</FunctionalResponseSeedPredation2>"
       << "<NeighborhoodSeedPredation3>"
       << "<pr_neighPredRadius>10</pr_neighPredRadius>"
       << "<pr_neighPredMinNeighDBH>"
       << "<pr_npmndVal species=\"Species_1\">10</pr_npmndVal>"
       << "<pr_npmndVal species=\"Species_2\">10</pr_npmndVal>"
       << "<pr_npmndVal species=\"Species_3\">10</pr_npmndVal>"
       << "<pr_npmndVal species=\"Species_4\">10</pr_npmndVal>"
       << "<pr_npmndVal species=\"Species_5\">10</pr_npmndVal>"
       << "</pr_neighPredMinNeighDBH>"
       << "<pr_neighPredP0>"
       << "<pr_npmp0Val species=\"Species_1\">1.32</pr_npmp0Val>"
       << "<pr_npmp0Val species=\"Species_2\">0.86</pr_npmp0Val>"
       << "<pr_npmp0Val species=\"Species_4\">-0.93</pr_npmp0Val>"
       << "</pr_neighPredP0>"
       << "<pr_neighPredPnSpecies_1>"
       << "<pr_nppnVal species=\"Species_1\">-5.94</pr_nppnVal>"
       << "<pr_nppnVal species=\"Species_2\">0</pr_nppnVal>"
       << "<pr_nppnVal species=\"Species_4\">-4.72</pr_nppnVal>"
       << "</pr_neighPredPnSpecies_1>"
       << "<pr_neighPredPnSpecies_2>"
       << "<pr_nppnVal species=\"Species_1\">2.8</pr_nppnVal>"
       << "<pr_nppnVal species=\"Species_2\">3.1</pr_nppnVal>"
       << "<pr_nppnVal species=\"Species_4\">0.99</pr_nppnVal>"
       << "</pr_neighPredPnSpecies_2>"
       << "<pr_neighPredPnSpecies_3>"
       << "<pr_nppnVal species=\"Species_1\">-1.9</pr_nppnVal>"
       << "<pr_nppnVal species=\"Species_2\">1.99</pr_nppnVal>"
       << "<pr_nppnVal species=\"Species_4\">3.24</pr_nppnVal>"
       << "</pr_neighPredPnSpecies_3>"
       << "<pr_neighPredPnSpecies_4>"
       << "<pr_nppnVal species=\"Species_1\">0.00000228</pr_nppnVal>"
       << "<pr_nppnVal species=\"Species_2\">0.0255</pr_nppnVal>"
       << "<pr_nppnVal species=\"Species_4\">5.93</pr_nppnVal>"
       << "</pr_neighPredPnSpecies_4>"
       << "<pr_neighPredPnSpecies_5>"
       << "<pr_nppnVal species=\"Species_1\">0.00000228</pr_nppnVal>"
       << "<pr_nppnVal species=\"Species_2\">0.0255</pr_nppnVal>"
       << "<pr_nppnVal species=\"Species_4\">5.93</pr_nppnVal>"
       << "</pr_neighPredPnSpecies_5>"
       << "</NeighborhoodSeedPredation3>"
       << "<NeighborhoodSeedPredation4>"
       << "<pr_neighPredMastingDensity>4</pr_neighPredMastingDensity>"
       << "<pr_neighPredMastDecisionMethod>0</pr_neighPredMastDecisionMethod>"
       << "<pr_neighPredRadius>10</pr_neighPredRadius>"
       << "<pr_neighPredMinNeighDBH>"
       << "<pr_npmndVal species=\"Species_1\">10</pr_npmndVal>"
       << "<pr_npmndVal species=\"Species_2\">10</pr_npmndVal>"
       << "<pr_npmndVal species=\"Species_3\">10</pr_npmndVal>"
       << "<pr_npmndVal species=\"Species_4\">10</pr_npmndVal>"
       << "<pr_npmndVal species=\"Species_5\">10</pr_npmndVal>"
       << "</pr_neighPredMinNeighDBH>"
       << "<pr_neighPredMastingP0>"
       << "<pr_npmp0Val species=\"Species_5\">-2.51</pr_npmp0Val>"
       << "</pr_neighPredMastingP0>"
       << "<pr_neighPredMastingPnSpecies_1>"
       << "<pr_npmpnVal species=\"Species_5\">2.56</pr_npmpnVal>"
       << "</pr_neighPredMastingPnSpecies_1>"
       << "<pr_neighPredMastingPnSpecies_2>"
       << "<pr_npmpnVal species=\"Species_5\">4.91</pr_npmpnVal>"
       << "</pr_neighPredMastingPnSpecies_2>"
       << "<pr_neighPredMastingPnSpecies_3>"
       << "<pr_npmpnVal species=\"Species_5\">2.66</pr_npmpnVal>"
       << "</pr_neighPredMastingPnSpecies_3>"
       << "<pr_neighPredMastingPnSpecies_4>"
       << "<pr_npmpnVal species=\"Species_5\">0.0255</pr_npmpnVal>"
       << "</pr_neighPredMastingPnSpecies_4>"
       << "<pr_neighPredMastingPnSpecies_5>"
       << "<pr_npmpnVal species=\"Species_5\">0.0255</pr_npmpnVal>"
       << "</pr_neighPredMastingPnSpecies_5>"
       << "<pr_neighPredNonMastingP0>"
       << "<pr_npnmp0Val species=\"Species_5\">-2.3</pr_npnmp0Val>"
       << "</pr_neighPredNonMastingP0>"
       << "<pr_neighPredNonMastingPnSpecies_1>"
       << "<pr_npnmpnVal species=\"Species_5\">3.24</pr_npnmpnVal>"
       << "</pr_neighPredNonMastingPnSpecies_1>"
       << "<pr_neighPredNonMastingPnSpecies_2>"
       << "<pr_npnmpnVal species=\"Species_5\">5.93</pr_npnmpnVal>"
       << "</pr_neighPredNonMastingPnSpecies_2>"
       << "<pr_neighPredNonMastingPnSpecies_3>"
       << "<pr_npnmpnVal species=\"Species_5\">1.83</pr_npnmpnVal>"
       << "</pr_neighPredNonMastingPnSpecies_3>"
       << "<pr_neighPredNonMastingPnSpecies_4>"
       << "<pr_npnmpnVal species=\"Species_5\">13.2</pr_npnmpnVal>"
       << "</pr_neighPredNonMastingPnSpecies_4>"
       << "<pr_neighPredNonMastingPnSpecies_5>"
       << "<pr_npnmpnVal species=\"Species_5\">13.2</pr_npnmpnVal>"
       << "</pr_neighPredNonMastingPnSpecies_5>"
       << "<pr_neighPredCounts4Mast>"
       << "<pr_npc4mVal species=\"Species_5\">1</pr_npc4mVal>"
       << "</pr_neighPredCounts4Mast>"
       << "</NeighborhoodSeedPredation4>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteNeighborhoodSeedPredationXMLFile5()
/////////////////////////////////////////////////////////////////////////////
const char* WriteNeighborhoodSeedPredationXMLFile5()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06010101\">" << "<plot>"
       << "<timesteps>1</timesteps>"
       << "<yearsPerTimestep>1</yearsPerTimestep>"
       << "<randomSeed>1</randomSeed>"
       << "<plot_lenX>96</plot_lenX>"
       << "<plot_lenY>96</plot_lenY>"
       << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
       << "<plot_temp_C>12.88171785</plot_temp_C>"
       << "<plot_latitude>55.37</plot_latitude>"
       << "</plot>";

  WriteNeighborhoodSeedPredationTreesAllometry(oOut);

  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>MastingNonSpatialDisperse</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_4\" type=\"Adult\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>NeighborhoodSeedPredation</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>2</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Seed\"/>"
       << "<applyTo species=\"Species_2\" type=\"Seed\"/>"
       << "<applyTo species=\"Species_4\" type=\"Seed\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>Establishment</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>3</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Seed\"/>"
       << "<applyTo species=\"Species_2\" type=\"Seed\"/>"
       << "<applyTo species=\"Species_3\" type=\"Seed\"/>"
       << "<applyTo species=\"Species_4\" type=\"Seed\"/>"
       << "</behavior>"
       << "</behaviorList>"
       << "<MastingNonSpatialDisperse1>"
       << "<di_nonSpatialMastMastFunction>"
       << "<di_nsmmfVal species=\"Species_1\">3</di_nsmmfVal>"
       << "<di_nsmmfVal species=\"Species_2\">3</di_nsmmfVal>"
       << "<di_nsmmfVal species=\"Species_3\">3</di_nsmmfVal>"
       << "<di_nsmmfVal species=\"Species_4\">3</di_nsmmfVal>"
       << "</di_nonSpatialMastMastFunction>"
       << "<di_nonSpatialNonMastFunction>"
       << "<di_nsnmfVal species=\"Species_1\">3</di_nsnmfVal>"
       << "<di_nsnmfVal species=\"Species_2\">3</di_nsnmfVal>"
       << "<di_nsnmfVal species=\"Species_3\">3</di_nsnmfVal>"
       << "<di_nsnmfVal species=\"Species_4\">3</di_nsnmfVal>"
       << "</di_nonSpatialNonMastFunction>"
       << "<di_nonSpatialMastBinomialP>"
       << "<di_nsmbpVal species=\"Species_1\">0</di_nsmbpVal>"
       << "<di_nsmbpVal species=\"Species_2\">0</di_nsmbpVal>"
       << "<di_nsmbpVal species=\"Species_3\">0</di_nsmbpVal>"
       << "<di_nsmbpVal species=\"Species_4\">0</di_nsmbpVal>"
       << "</di_nonSpatialMastBinomialP>"
       << "<di_nonSpatialMastNormalMean>"
       << "<di_nsmnmVal species=\"Species_1\">1</di_nsmnmVal>"
       << "<di_nsmnmVal species=\"Species_2\">4</di_nsmnmVal>"
       << "<di_nsmnmVal species=\"Species_3\">2</di_nsmnmVal>"
       << "<di_nsmnmVal species=\"Species_4\">1</di_nsmnmVal>"
       << "</di_nonSpatialMastNormalMean>"
       << "<di_nonSpatialMastNormalStdDev>"
       << "<di_nsmnsdVal species=\"Species_1\">0</di_nsmnsdVal>"
       << "<di_nsmnsdVal species=\"Species_2\">0</di_nsmnsdVal>"
       << "<di_nsmnsdVal species=\"Species_3\">0</di_nsmnsdVal>"
       << "<di_nsmnsdVal species=\"Species_4\">0</di_nsmnsdVal>"
       << "</di_nonSpatialMastNormalStdDev>"
       << "<di_nonSpatialNonMastNormalMean>"
       << "<di_nsnmnmVal species=\"Species_1\">1</di_nsnmnmVal>"
       << "<di_nsnmnmVal species=\"Species_2\">4</di_nsnmnmVal>"
       << "<di_nsnmnmVal species=\"Species_3\">2</di_nsnmnmVal>"
       << "<di_nsnmnmVal species=\"Species_4\">1</di_nsnmnmVal>"
       << "</di_nonSpatialNonMastNormalMean>"
       << "<di_nonSpatialNonMastNormalStdDev>"
       << "<di_nsnmnsdVal species=\"Species_1\">0</di_nsnmnsdVal>"
       << "<di_nsnmnsdVal species=\"Species_2\">0</di_nsnmnsdVal>"
       << "<di_nsnmnsdVal species=\"Species_3\">0</di_nsnmnsdVal>"
       << "<di_nsnmnsdVal species=\"Species_4\">0</di_nsnmnsdVal>"
       << "</di_nonSpatialNonMastNormalStdDev>"
       << "<di_nonSpatialMastGroup>"
       << "<di_nsmgVal species=\"Species_1\">1</di_nsmgVal>"
       << "<di_nsmgVal species=\"Species_2\">2</di_nsmgVal>"
       << "<di_nsmgVal species=\"Species_3\">3</di_nsmgVal>"
       << "<di_nsmgVal species=\"Species_4\">5</di_nsmgVal>"
       << "</di_nonSpatialMastGroup>"
       << "<di_seedDistributionMethod>0</di_seedDistributionMethod>"
       << "</MastingNonSpatialDisperse1>"
       << "<NeighborhoodSeedPredation2>";

  WriteNeighborhoodSeedPredationCommonPredationParameters(oOut);

  oOut << "<pr_neighPredMastDecisionMethod>1</pr_neighPredMastDecisionMethod>"
       << "<pr_neighPredMastingDensity>4</pr_neighPredMastingDensity>"
       << "<pr_neighPredRadius>10</pr_neighPredRadius>"
       << "<pr_neighPredMinNeighDBH>"
       << "<pr_npmndVal species=\"Species_1\">10</pr_npmndVal>"
       << "<pr_npmndVal species=\"Species_2\">10</pr_npmndVal>"
       << "<pr_npmndVal species=\"Species_3\">15</pr_npmndVal>"
       << "<pr_npmndVal species=\"Species_4\">10</pr_npmndVal>"
       << "</pr_neighPredMinNeighDBH>"
       << "<pr_neighPredCounts4Mast>"
       << "<pr_npc4mVal species=\"Species_1\">1</pr_npc4mVal>"
       << "<pr_npc4mVal species=\"Species_2\">0</pr_npc4mVal>"
       << "<pr_npc4mVal species=\"Species_4\">1</pr_npc4mVal>"
       << "</pr_neighPredCounts4Mast>"
       << "</NeighborhoodSeedPredation2>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteNeighborhoodSeedPredationXMLFile6()
/////////////////////////////////////////////////////////////////////////////
const char* WriteNeighborhoodSeedPredationXMLFile6()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06010101\">" << "<plot>"
       << "<timesteps>1</timesteps>"
       << "<yearsPerTimestep>1</yearsPerTimestep>"
       << "<randomSeed>1</randomSeed>"
       << "<plot_lenX>96</plot_lenX>"
       << "<plot_lenY>96</plot_lenY>"
       << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
       << "<plot_temp_C>12.88171785</plot_temp_C>"
       << "<plot_latitude>55.37</plot_latitude>"
       << "</plot>";

  WriteNeighborhoodSeedPredationTreesAllometry(oOut);

  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>MastingSpatialDisperse</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_4\" type=\"Adult\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>NeighborhoodSeedPredation</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>2</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Seed\"/>"
       << "<applyTo species=\"Species_2\" type=\"Seed\"/>"
       << "<applyTo species=\"Species_4\" type=\"Seed\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>Establishment</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>3</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Seed\"/>"
       << "<applyTo species=\"Species_2\" type=\"Seed\"/>"
       << "<applyTo species=\"Species_3\" type=\"Seed\"/>"
       << "<applyTo species=\"Species_4\" type=\"Seed\"/>"
       << "</behavior>"
       << "</behaviorList>"
       << "<GeneralDisperse>"
       << "<di_seedDistributionMethod>0</di_seedDistributionMethod>"
       << "</GeneralDisperse>"
       << "<MastingSpatialDisperse1>"
       << "<di_minDbhForReproduction>"
       << "<di_mdfrVal species=\"Species_1\">15.0</di_mdfrVal>"
       << "<di_mdfrVal species=\"Species_2\">15.0</di_mdfrVal>"
       << "<di_mdfrVal species=\"Species_3\">15.0</di_mdfrVal>"
       << "<di_mdfrVal species=\"Species_4\">15.0</di_mdfrVal>"
       << "</di_minDbhForReproduction>"
       << "<di_mastCDFA>"
       << "<di_mcdfaVal species=\"Species_1\">0.00001</di_mcdfaVal>"
       << "<di_mcdfaVal species=\"Species_2\">1000</di_mcdfaVal>"
       << "<di_mcdfaVal species=\"Species_3\">1000</di_mcdfaVal>"
       << "<di_mcdfaVal species=\"Species_4\">1000</di_mcdfaVal>"
       << "</di_mastCDFA>"
       << "<di_mastCDFB>"
       << "<di_mcdfbVal species=\"Species_1\">-5</di_mcdfbVal>"
       << "<di_mcdfbVal species=\"Species_2\">-5</di_mcdfbVal>"
       << "<di_mcdfbVal species=\"Species_3\">-5</di_mcdfbVal>"
       << "<di_mcdfbVal species=\"Species_4\">-5</di_mcdfbVal>"
       << "</di_mastCDFB>"
       << "<di_mastSTRPDF>"
       << "<di_mstrpdfVal species=\"Species_1\">0</di_mstrpdfVal>"
       << "<di_mstrpdfVal species=\"Species_2\">0</di_mstrpdfVal>"
       << "<di_mstrpdfVal species=\"Species_3\">0</di_mstrpdfVal>"
       << "<di_mstrpdfVal species=\"Species_4\">0</di_mstrpdfVal>"
       << "</di_mastSTRPDF>"
       << "<di_spatialSTR>"
       << "<di_sstrVal species=\"Species_1\">0</di_sstrVal>"
       << "<di_sstrVal species=\"Species_2\">0</di_sstrVal>"
       << "<di_sstrVal species=\"Species_3\">0</di_sstrVal>"
       << "<di_sstrVal species=\"Species_4\">0</di_sstrVal>"
       << "</di_spatialSTR>"
       << "<di_spatialSTRStdDev>"
       << "<di_sstrsdVal species=\"Species_1\">0</di_sstrsdVal>"
       << "<di_sstrsdVal species=\"Species_2\">0</di_sstrsdVal>"
       << "<di_sstrsdVal species=\"Species_3\">0</di_sstrsdVal>"
       << "<di_sstrsdVal species=\"Species_4\">0</di_sstrsdVal>"
       << "</di_spatialSTRStdDev>"
       << "<di_mastingSTR>"
       << "<di_mstrVal species=\"Species_1\">0</di_mstrVal>"
       << "<di_mstrVal species=\"Species_2\">0</di_mstrVal>"
       << "<di_mstrVal species=\"Species_3\">0</di_mstrVal>"
       << "<di_mstrVal species=\"Species_4\">0</di_mstrVal>"
       << "</di_mastingSTR>"
       << "<di_mastingSTRStdDev>"
       << "<di_mstrsdVal species=\"Species_1\">0</di_mstrsdVal>"
       << "<di_mstrsdVal species=\"Species_2\">0</di_mstrsdVal>"
       << "<di_mstrsdVal species=\"Species_3\">0</di_mstrsdVal>"
       << "<di_mstrsdVal species=\"Species_4\">0</di_mstrsdVal>"
       << "</di_mastingSTRStdDev>"
       << "<di_spatialBeta>"
       << "<di_sbVal species=\"Species_1\">1</di_sbVal>"
       << "<di_sbVal species=\"Species_2\">3.5</di_sbVal>"
       << "<di_sbVal species=\"Species_3\">3.5</di_sbVal>"
       << "<di_sbVal species=\"Species_4\">2</di_sbVal>"
       << "</di_spatialBeta>"
       << "<di_mastingBeta>"
       << "<di_mbVal species=\"Species_1\">2</di_mbVal>"
       << "<di_mbVal species=\"Species_2\">2.5</di_mbVal>"
       << "<di_mbVal species=\"Species_3\">2.5</di_mbVal>"
       << "<di_mbVal species=\"Species_4\">1</di_mbVal>"
       << "</di_mastingBeta>"
       << "<di_canopyFunction>"
       << "<di_cfVal species=\"Species_1\">0</di_cfVal>"
       << "<di_cfVal species=\"Species_2\">0</di_cfVal>"
       << "<di_cfVal species=\"Species_3\">0</di_cfVal>"
       << "<di_cfVal species=\"Species_4\">0</di_cfVal>"
       << "</di_canopyFunction>"
       << "<di_weibullCanopyDispersal>"
       << "<di_wcdVal species=\"Species_1\">1.76E-04</di_wcdVal>"
       << "<di_wcdVal species=\"Species_2\">1.82E-04</di_wcdVal>"
       << "<di_wcdVal species=\"Species_3\">1.82E-04</di_wcdVal>"
       << "<di_wcdVal species=\"Species_4\">9.61E-05</di_wcdVal>"
       << "</di_weibullCanopyDispersal>"
       << "<di_weibullCanopyTheta>"
       << "<di_wctVal species=\"Species_1\">3</di_wctVal>"
       << "<di_wctVal species=\"Species_2\">3</di_wctVal>"
       << "<di_wctVal species=\"Species_3\">3</di_wctVal>"
       << "<di_wctVal species=\"Species_4\">3</di_wctVal>"
       << "</di_weibullCanopyTheta>"
       << "<di_weibullMastingDispersal>"
       << "<di_wmdVal species=\"Species_1\">1.76E-04</di_wmdVal>"
       << "<di_wmdVal species=\"Species_2\">1.82E-04</di_wmdVal>"
       << "<di_wmdVal species=\"Species_3\">1.82E-04</di_wmdVal>"
       << "<di_wmdVal species=\"Species_4\">9.61E-05</di_wmdVal>"
       << "</di_weibullMastingDispersal>"
       << "<di_weibullMastingTheta>"
       << "<di_wmtVal species=\"Species_1\">3</di_wmtVal>"
       << "<di_wmtVal species=\"Species_2\">3</di_wmtVal>"
       << "<di_wmtVal species=\"Species_3\">3</di_wmtVal>"
       << "<di_wmtVal species=\"Species_4\">3</di_wmtVal>"
       << "</di_weibullMastingTheta>"
       << "<di_mastGroup>"
       << "<di_mgVal species=\"Species_1\">1</di_mgVal>"
       << "<di_mgVal species=\"Species_2\">2</di_mgVal>"
       << "<di_mgVal species=\"Species_3\">2</di_mgVal>"
       << "<di_mgVal species=\"Species_4\">1</di_mgVal>"
       << "</di_mastGroup>"
       << "<di_mastDrawPerSpecies>"
       << "<di_mdpsVal species=\"Species_1\">0</di_mdpsVal>"
       << "<di_mdpsVal species=\"Species_2\">0</di_mdpsVal>"
       << "<di_mdpsVal species=\"Species_3\">0</di_mdpsVal>"
       << "<di_mdpsVal species=\"Species_4\">0</di_mdpsVal>"
       << "</di_mastDrawPerSpecies>"
       << "<di_mastPropParticipating>"
       << "<di_mppVal species=\"Species_1\">1</di_mppVal>"
       << "<di_mppVal species=\"Species_2\">1</di_mppVal>"
       << "<di_mppVal species=\"Species_3\">1</di_mppVal>"
       << "<di_mppVal species=\"Species_4\">1</di_mppVal>"
       << "</di_mastPropParticipating>"
       << "<di_spatialPropParticipating>"
       << "<di_sppVal species=\"Species_1\">1</di_sppVal>"
       << "<di_sppVal species=\"Species_2\">1</di_sppVal>"
       << "<di_sppVal species=\"Species_3\">1</di_sppVal>"
       << "<di_sppVal species=\"Species_4\">1</di_sppVal>"
       << "</di_spatialPropParticipating>"
       << "</MastingSpatialDisperse1>"
       << "<NeighborhoodSeedPredation2>"
       << "<pr_neighPredMastDecisionMethod>0</pr_neighPredMastDecisionMethod>"
       << "<pr_neighPredMastingDensity>1</pr_neighPredMastingDensity>"
       << "<pr_neighPredRadius>10</pr_neighPredRadius>"
       << "<pr_neighPredMinNeighDBH>"
       << "<pr_npmndVal species=\"Species_1\">10</pr_npmndVal>"
       << "<pr_npmndVal species=\"Species_2\">10</pr_npmndVal>"
       << "<pr_npmndVal species=\"Species_3\">10</pr_npmndVal>"
       << "<pr_npmndVal species=\"Species_4\">10</pr_npmndVal>"
       << "</pr_neighPredMinNeighDBH>"
       << "<pr_neighPredMastingP0>"
       << "<pr_npmp0Val species=\"Species_1\">1.32</pr_npmp0Val>"
       << "<pr_npmp0Val species=\"Species_2\">0.86</pr_npmp0Val>"
       << "<pr_npmp0Val species=\"Species_4\">-0.93</pr_npmp0Val>"
       << "</pr_neighPredMastingP0>"
       << "<pr_neighPredMastingPnSpecies_1>"
       << "<pr_npmpnVal species=\"Species_1\">-5.94</pr_npmpnVal>"
       << "<pr_npmpnVal species=\"Species_2\">0</pr_npmpnVal>"
       << "<pr_npmpnVal species=\"Species_4\">-4.72</pr_npmpnVal>"
       << "</pr_neighPredMastingPnSpecies_1>"
       << "<pr_neighPredMastingPnSpecies_2>"
       << "<pr_npmpnVal species=\"Species_1\">2.8</pr_npmpnVal>"
       << "<pr_npmpnVal species=\"Species_2\">3.1</pr_npmpnVal>"
       << "<pr_npmpnVal species=\"Species_4\">0.99</pr_npmpnVal>"
       << "</pr_neighPredMastingPnSpecies_2>"
       << "<pr_neighPredMastingPnSpecies_3>"
       << "<pr_npmpnVal species=\"Species_1\">-1.9</pr_npmpnVal>"
       << "<pr_npmpnVal species=\"Species_2\">1.99</pr_npmpnVal>"
       << "<pr_npmpnVal species=\"Species_4\">3.24</pr_npmpnVal>"
       << "</pr_neighPredMastingPnSpecies_3>"
       << "<pr_neighPredMastingPnSpecies_4>"
       << "<pr_npmpnVal species=\"Species_1\">0.00000228</pr_npmpnVal>"
       << "<pr_npmpnVal species=\"Species_2\">0.0255</pr_npmpnVal>"
       << "<pr_npmpnVal species=\"Species_4\">5.93</pr_npmpnVal>"
       << "</pr_neighPredMastingPnSpecies_4>"
       << "<pr_neighPredNonMastingP0>"
       << "<pr_npnmp0Val species=\"Species_1\">-2.51</pr_npnmp0Val>"
       << "<pr_npnmp0Val species=\"Species_2\">-1.36</pr_npnmp0Val>"
       << "<pr_npnmp0Val species=\"Species_4\">-99</pr_npnmp0Val>"
       << "</pr_neighPredNonMastingP0>"
       << "<pr_neighPredNonMastingPnSpecies_1>"
       << "<pr_npnmpnVal species=\"Species_1\">2.56</pr_npnmpnVal>"
       << "<pr_npnmpnVal species=\"Species_2\">0.23</pr_npnmpnVal>"
       << "<pr_npnmpnVal species=\"Species_4\">3.24</pr_npnmpnVal>"
       << "</pr_neighPredNonMastingPnSpecies_1>"
       << "<pr_neighPredNonMastingPnSpecies_2>"
       << "<pr_npnmpnVal species=\"Species_1\">4.91</pr_npnmpnVal>"
       << "<pr_npnmpnVal species=\"Species_2\">1.9</pr_npnmpnVal>"
       << "<pr_npnmpnVal species=\"Species_4\">5.93</pr_npnmpnVal>"
       << "</pr_neighPredNonMastingPnSpecies_2>"
       << "<pr_neighPredNonMastingPnSpecies_3>"
       << "<pr_npnmpnVal species=\"Species_1\">2.66</pr_npnmpnVal>"
       << "<pr_npnmpnVal species=\"Species_2\">-7.49</pr_npnmpnVal>"
       << "<pr_npnmpnVal species=\"Species_4\">1.83</pr_npnmpnVal>"
       << "</pr_neighPredNonMastingPnSpecies_3>"
       << "<pr_neighPredNonMastingPnSpecies_4>"
       << "<pr_npnmpnVal species=\"Species_1\">0.0255</pr_npnmpnVal>"
       << "<pr_npnmpnVal species=\"Species_2\">0.00569</pr_npnmpnVal>"
       << "<pr_npnmpnVal species=\"Species_4\">13.2</pr_npnmpnVal>"
       << "</pr_neighPredNonMastingPnSpecies_4>"
       << "<pr_neighPredCounts4Mast>"
       << "<pr_npc4mVal species=\"Species_1\">1</pr_npc4mVal>"
       << "<pr_npc4mVal species=\"Species_2\">1</pr_npc4mVal>"
       << "<pr_npc4mVal species=\"Species_4\">1</pr_npc4mVal>"
       << "</pr_neighPredCounts4Mast>"
       << "</NeighborhoodSeedPredation2>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}


/////////////////////////////////////////////////////////////////////////////
// WriteNeighborhoodSeedPredationXMLFile7()
/////////////////////////////////////////////////////////////////////////////
const char* WriteNeighborhoodSeedPredationXMLFile7()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06010101\">"
       << "<plot>"
       << "<timesteps>1</timesteps>"
       << "<yearsPerTimestep>1</yearsPerTimestep>"
       << "<randomSeed>1</randomSeed>"
       << "<plot_lenX>96</plot_lenX>"
       << "<plot_lenY>96</plot_lenY>"
       << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
       << "<plot_temp_C>12.88171785</plot_temp_C>"
       << "<plot_latitude>55.37</plot_latitude>"
       << "</plot>";

  WriteNeighborhoodSeedPredationTreesAllometry(oOut);

  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>NonSpatialDisperse</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_4\" type=\"Adult\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>NeighborhoodSeedPredation</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>2</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Seed\"/>"
       << "<applyTo species=\"Species_2\" type=\"Seed\"/>"
       << "<applyTo species=\"Species_4\" type=\"Seed\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>Establishment</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>3</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Seed\"/>"
       << "<applyTo species=\"Species_2\" type=\"Seed\"/>"
       << "<applyTo species=\"Species_3\" type=\"Seed\"/>"
       << "<applyTo species=\"Species_4\" type=\"Seed\"/>"
       << "</behavior>"
       << "</behaviorList>"
       << "<GeneralDisperse>"
       << "<di_seedDistributionMethod>0</di_seedDistributionMethod>"
       << "</GeneralDisperse>"
       << "<NonSpatialDisperse1>"
       << "<di_minDbhForReproduction>"
       << "<di_mdfrVal species=\"Species_1\">15.0</di_mdfrVal>"
       << "<di_mdfrVal species=\"Species_2\">15.0</di_mdfrVal>"
       << "<di_mdfrVal species=\"Species_3\">15.0</di_mdfrVal>"
       << "<di_mdfrVal species=\"Species_4\">15.0</di_mdfrVal>"
       << "</di_minDbhForReproduction>"
       << "<di_nonSpatialSlopeOfLambda>"
       << "<di_nssolVal species=\"Species_4\">0</di_nssolVal>"
       << "<di_nssolVal species=\"Species_2\">0</di_nssolVal>"
       << "<di_nssolVal species=\"Species_3\">0</di_nssolVal>"
       << "<di_nssolVal species=\"Species_1\">0</di_nssolVal>"
       << "</di_nonSpatialSlopeOfLambda>"
       << "<di_nonSpatialInterceptOfLambda>"
       << "<di_nsiolVal species=\"Species_1\">1</di_nsiolVal>"
       << "<di_nsiolVal species=\"Species_2\">4</di_nsiolVal>"
       << "<di_nsiolVal species=\"Species_3\">2</di_nsiolVal>"
       << "<di_nsiolVal species=\"Species_4\">1</di_nsiolVal>"
       << "</di_nonSpatialInterceptOfLambda>"
       << "</NonSpatialDisperse1>"
       << "<NeighborhoodSeedPredation2>";

  WriteNeighborhoodSeedPredationCommonPredationParameters(oOut);

  oOut << "<pr_neighPredMastDecisionMethod>0</pr_neighPredMastDecisionMethod>"
       << "<pr_neighPredMastingDensity>1</pr_neighPredMastingDensity>"
       << "<pr_neighPredRadius>10</pr_neighPredRadius>"
       << "<pr_neighPredMinNeighDBH>"
       << "<pr_npmndVal species=\"Species_1\">10</pr_npmndVal>"
       << "<pr_npmndVal species=\"Species_2\">10</pr_npmndVal>"
       << "<pr_npmndVal species=\"Species_3\">15</pr_npmndVal>"
       << "<pr_npmndVal species=\"Species_4\">10</pr_npmndVal>"
       << "</pr_neighPredMinNeighDBH>"
       << "<pr_neighPredCounts4Mast>"
       << "<pr_npc4mVal species=\"Species_1\">1</pr_npc4mVal>"
       << "<pr_npc4mVal species=\"Species_2\">0</pr_npc4mVal>"
       << "<pr_npc4mVal species=\"Species_4\">1</pr_npc4mVal>"
       << "</pr_neighPredCounts4Mast>"
       << "</NeighborhoodSeedPredation2>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}


/////////////////////////////////////////////////////////////////////////////
// WriteNeighborhoodSeedPredationXMLErrorFile1()
/////////////////////////////////////////////////////////////////////////////
const char* WriteNeighborhoodSeedPredationXMLErrorFile1()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06010101\">" << "<plot>"
       << "<timesteps>1</timesteps>"
       << "<yearsPerTimestep>1</yearsPerTimestep>"
       << "<randomSeed>1</randomSeed>"
       << "<plot_lenX>96</plot_lenX>"
       << "<plot_lenY>96</plot_lenY>"
       << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
       << "<plot_temp_C>12.88171785</plot_temp_C>"
       << "<plot_latitude>55.37</plot_latitude>"
       << "</plot>";

  WriteNeighborhoodSeedPredationTreesAllometry(oOut);

  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>NonSpatialDisperse</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_4\" type=\"Adult\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>NeighborhoodSeedPredation</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>2</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Seed\"/>"
       << "<applyTo species=\"Species_2\" type=\"Seed\"/>"
       << "<applyTo species=\"Species_4\" type=\"Seed\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>Establishment</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>3</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Seed\"/>"
       << "<applyTo species=\"Species_2\" type=\"Seed\"/>"
       << "<applyTo species=\"Species_3\" type=\"Seed\"/>"
       << "<applyTo species=\"Species_4\" type=\"Seed\"/>"
       << "</behavior>"
       << "</behaviorList>"
       << "<GeneralDisperse>"
       << "<di_seedDistributionMethod>0</di_seedDistributionMethod>"
       << "</GeneralDisperse>"
       << "<NonSpatialDisperse1>"
       << "<di_minDbhForReproduction>"
       << "<di_mdfrVal species=\"Species_1\">15.0</di_mdfrVal>"
       << "<di_mdfrVal species=\"Species_2\">15.0</di_mdfrVal>"
       << "<di_mdfrVal species=\"Species_3\">15.0</di_mdfrVal>"
       << "<di_mdfrVal species=\"Species_4\">15.0</di_mdfrVal>"
       << "</di_minDbhForReproduction>"
       << "<di_nonSpatialSlopeOfLambda>"
       << "<di_nssolVal species=\"Species_4\">0</di_nssolVal>"
       << "<di_nssolVal species=\"Species_2\">0</di_nssolVal>"
       << "<di_nssolVal species=\"Species_3\">0</di_nssolVal>"
       << "<di_nssolVal species=\"Species_1\">0</di_nssolVal>"
       << "</di_nonSpatialSlopeOfLambda>"
       << "<di_nonSpatialInterceptOfLambda>"
       << "<di_nsiolVal species=\"Species_1\">1</di_nsiolVal>"
       << "<di_nsiolVal species=\"Species_2\">1</di_nsiolVal>"
       << "<di_nsiolVal species=\"Species_3\">2</di_nsiolVal>"
       << "<di_nsiolVal species=\"Species_4\">1</di_nsiolVal>"
       << "</di_nonSpatialInterceptOfLambda>"
       << "</NonSpatialDisperse1>"
       << "<NeighborhoodSeedPredation2>"
       << "<pr_neighPredMastDecisionMethod>0</pr_neighPredMastDecisionMethod>"
       << "<pr_neighPredMastingDensity>4</pr_neighPredMastingDensity>"
       << "<pr_neighPredRadius>10</pr_neighPredRadius>"
       << "<pr_neighPredMinNeighDBH>"
       << "<pr_npmndVal species=\"Species_1\">10</pr_npmndVal>"
       << "<pr_npmndVal species=\"Species_2\">-10</pr_npmndVal>"
       << "<pr_npmndVal species=\"Species_3\">10</pr_npmndVal>"
       << "<pr_npmndVal species=\"Species_4\">10</pr_npmndVal>"
       << "</pr_neighPredMinNeighDBH>";

  WriteNeighborhoodSeedPredationCommonPredationParameters(oOut);

  oOut << "<pr_neighPredCounts4Mast>"
       << "<pr_npc4mVal species=\"Species_1\">1</pr_npc4mVal>"
       << "<pr_npc4mVal species=\"Species_2\">1</pr_npc4mVal>"
       << "<pr_npc4mVal species=\"Species_4\">1</pr_npc4mVal>"
       << "</pr_neighPredCounts4Mast>"
       << "</NeighborhoodSeedPredation2>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteNeighborhoodSeedPredationXMLErrorFile2()
/////////////////////////////////////////////////////////////////////////////
const char* WriteNeighborhoodSeedPredationXMLErrorFile2()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06010101\">" << "<plot>"
       << "<timesteps>1</timesteps>"
       << "<yearsPerTimestep>1</yearsPerTimestep>"
       << "<randomSeed>1</randomSeed>"
       << "<plot_lenX>96</plot_lenX>"
       << "<plot_lenY>96</plot_lenY>"
       << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
       << "<plot_temp_C>12.88171785</plot_temp_C>"
       << "<plot_latitude>55.37</plot_latitude>"
       << "</plot>";

  WriteNeighborhoodSeedPredationTreesAllometry(oOut);

  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>NonSpatialDisperse</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_4\" type=\"Adult\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>NeighborhoodSeedPredation</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>2</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Seed\"/>"
       << "<applyTo species=\"Species_2\" type=\"Seed\"/>"
       << "<applyTo species=\"Species_4\" type=\"Seed\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>Establishment</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>3</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Seed\"/>"
       << "<applyTo species=\"Species_2\" type=\"Seed\"/>"
       << "<applyTo species=\"Species_3\" type=\"Seed\"/>"
       << "<applyTo species=\"Species_4\" type=\"Seed\"/>"
       << "</behavior>"
       << "</behaviorList>"
       << "<GeneralDisperse>"
       << "<di_seedDistributionMethod>0</di_seedDistributionMethod>"
       << "</GeneralDisperse>"
       << "<NonSpatialDisperse1>"
       << "<di_minDbhForReproduction>"
       << "<di_mdfrVal species=\"Species_1\">15.0</di_mdfrVal>"
       << "<di_mdfrVal species=\"Species_2\">15.0</di_mdfrVal>"
       << "<di_mdfrVal species=\"Species_3\">15.0</di_mdfrVal>"
       << "<di_mdfrVal species=\"Species_4\">15.0</di_mdfrVal>"
       << "</di_minDbhForReproduction>"
       << "<di_nonSpatialSlopeOfLambda>"
       << "<di_nssolVal species=\"Species_4\">0</di_nssolVal>"
       << "<di_nssolVal species=\"Species_2\">0</di_nssolVal>"
       << "<di_nssolVal species=\"Species_3\">0</di_nssolVal>"
       << "<di_nssolVal species=\"Species_1\">0</di_nssolVal>"
       << "</di_nonSpatialSlopeOfLambda>"
       << "<di_nonSpatialInterceptOfLambda>"
       << "<di_nsiolVal species=\"Species_1\">1</di_nsiolVal>"
       << "<di_nsiolVal species=\"Species_2\">1</di_nsiolVal>"
       << "<di_nsiolVal species=\"Species_3\">2</di_nsiolVal>"
       << "<di_nsiolVal species=\"Species_4\">1</di_nsiolVal>"
       << "</di_nonSpatialInterceptOfLambda>"
       << "</NonSpatialDisperse1>"
       << "<NeighborhoodSeedPredation2>"
       << "<pr_neighPredMastDecisionMethod>0</pr_neighPredMastDecisionMethod>"
       << "<pr_neighPredMastingDensity>-4</pr_neighPredMastingDensity>"
       << "<pr_neighPredRadius>10</pr_neighPredRadius>"
       << "<pr_neighPredMinNeighDBH>"
       << "<pr_npmndVal species=\"Species_1\">10</pr_npmndVal>"
       << "<pr_npmndVal species=\"Species_2\">10</pr_npmndVal>"
       << "<pr_npmndVal species=\"Species_3\">10</pr_npmndVal>"
       << "<pr_npmndVal species=\"Species_4\">10</pr_npmndVal>"
       << "</pr_neighPredMinNeighDBH>";

  WriteNeighborhoodSeedPredationCommonPredationParameters(oOut);

  oOut << "<pr_neighPredCounts4Mast>"
       << "<pr_npc4mVal species=\"Species_1\">1</pr_npc4mVal>"
       << "<pr_npc4mVal species=\"Species_2\">1</pr_npc4mVal>"
       << "<pr_npc4mVal species=\"Species_4\">1</pr_npc4mVal>"
       << "</pr_neighPredCounts4Mast>"
       << "</NeighborhoodSeedPredation2>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteNeighborhoodSeedPredationXMLErrorFile3()
/////////////////////////////////////////////////////////////////////////////
const char* WriteNeighborhoodSeedPredationXMLErrorFile3()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06010101\">" << "<plot>"
       << "<timesteps>1</timesteps>"
       << "<yearsPerTimestep>1</yearsPerTimestep>"
       << "<randomSeed>1</randomSeed>"
       << "<plot_lenX>96</plot_lenX>"
       << "<plot_lenY>96</plot_lenY>"
       << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
       << "<plot_temp_C>12.88171785</plot_temp_C>"
       << "<plot_latitude>55.37</plot_latitude>"
       << "</plot>";

  WriteNeighborhoodSeedPredationTreesAllometry(oOut);

  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>NonSpatialDisperse</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_4\" type=\"Adult\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>NeighborhoodSeedPredation</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>2</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Seed\"/>"
       << "<applyTo species=\"Species_2\" type=\"Seed\"/>"
       << "<applyTo species=\"Species_4\" type=\"Seed\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>Establishment</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>3</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Seed\"/>"
       << "<applyTo species=\"Species_2\" type=\"Seed\"/>"
       << "<applyTo species=\"Species_3\" type=\"Seed\"/>"
       << "<applyTo species=\"Species_4\" type=\"Seed\"/>"
       << "</behavior>"
       << "</behaviorList>"
       << "<GeneralDisperse>"
       << "<di_seedDistributionMethod>0</di_seedDistributionMethod>"
       << "</GeneralDisperse>"
       << "<NonSpatialDisperse1>"
       << "<di_minDbhForReproduction>"
       << "<di_mdfrVal species=\"Species_1\">15.0</di_mdfrVal>"
       << "<di_mdfrVal species=\"Species_2\">15.0</di_mdfrVal>"
       << "<di_mdfrVal species=\"Species_3\">15.0</di_mdfrVal>"
       << "<di_mdfrVal species=\"Species_4\">15.0</di_mdfrVal>"
       << "</di_minDbhForReproduction>"
       << "<di_nonSpatialSlopeOfLambda>"
       << "<di_nssolVal species=\"Species_4\">0</di_nssolVal>"
       << "<di_nssolVal species=\"Species_2\">0</di_nssolVal>"
       << "<di_nssolVal species=\"Species_3\">0</di_nssolVal>"
       << "<di_nssolVal species=\"Species_1\">0</di_nssolVal>"
       << "</di_nonSpatialSlopeOfLambda>"
       << "<di_nonSpatialInterceptOfLambda>"
       << "<di_nsiolVal species=\"Species_1\">1</di_nsiolVal>"
       << "<di_nsiolVal species=\"Species_2\">1</di_nsiolVal>"
       << "<di_nsiolVal species=\"Species_3\">2</di_nsiolVal>"
       << "<di_nsiolVal species=\"Species_4\">1</di_nsiolVal>"
       << "</di_nonSpatialInterceptOfLambda>"
       << "</NonSpatialDisperse1>"
       << "<NeighborhoodSeedPredation2>"
       << "<pr_neighPredMastDecisionMethod>0</pr_neighPredMastDecisionMethod>"
       << "<pr_neighPredMastingDensity>4</pr_neighPredMastingDensity>"
       << "<pr_neighPredRadius>-10</pr_neighPredRadius>"
       << "<pr_neighPredMinNeighDBH>"
       << "<pr_npmndVal species=\"Species_1\">10</pr_npmndVal>"
       << "<pr_npmndVal species=\"Species_2\">10</pr_npmndVal>"
       << "<pr_npmndVal species=\"Species_3\">10</pr_npmndVal>"
       << "<pr_npmndVal species=\"Species_4\">10</pr_npmndVal>"
       << "</pr_neighPredMinNeighDBH>";

  WriteNeighborhoodSeedPredationCommonPredationParameters(oOut);

  oOut << "<pr_neighPredCounts4Mast>"
       << "<pr_npc4mVal species=\"Species_1\">1</pr_npc4mVal>"
       << "<pr_npc4mVal species=\"Species_2\">1</pr_npc4mVal>"
       << "<pr_npc4mVal species=\"Species_4\">1</pr_npc4mVal>"
       << "</pr_neighPredCounts4Mast>"
       << "</NeighborhoodSeedPredation2>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteNeighborhoodSeedPredationXMLErrorFile4()
/////////////////////////////////////////////////////////////////////////////
const char* WriteNeighborhoodSeedPredationXMLErrorFile4()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06010101\">" << "<plot>"
       << "<timesteps>1</timesteps>"
       << "<yearsPerTimestep>1</yearsPerTimestep>"
       << "<randomSeed>1</randomSeed>"
       << "<plot_lenX>96</plot_lenX>"
       << "<plot_lenY>96</plot_lenY>"
       << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
       << "<plot_temp_C>12.88171785</plot_temp_C>"
       << "<plot_latitude>55.37</plot_latitude>"
       << "</plot>";

  WriteNeighborhoodSeedPredationTreesAllometry(oOut);

  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>NeighborhoodSeedPredation</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Seed\"/>"
       << "<applyTo species=\"Species_2\" type=\"Seed\"/>"
       << "<applyTo species=\"Species_4\" type=\"Seed\"/>"
       << "</behavior>"
       << "</behaviorList>"
       << "<NeighborhoodSeedPredation1>"
       << "<pr_neighPredMastDecisionMethod>0</pr_neighPredMastDecisionMethod>"
       << "<pr_neighPredMastingDensity>4</pr_neighPredMastingDensity>"
       << "<pr_neighPredRadius>10</pr_neighPredRadius>"
       << "<pr_neighPredMinNeighDBH>"
       << "<pr_npmndVal species=\"Species_1\">10</pr_npmndVal>"
       << "<pr_npmndVal species=\"Species_2\">10</pr_npmndVal>"
       << "<pr_npmndVal species=\"Species_3\">10</pr_npmndVal>"
       << "<pr_npmndVal species=\"Species_4\">10</pr_npmndVal>"
       << "</pr_neighPredMinNeighDBH>";

  WriteNeighborhoodSeedPredationCommonPredationParameters(oOut);

  oOut << "<pr_neighPredCounts4Mast>"
       << "<pr_npc4mVal species=\"Species_1\">1</pr_npc4mVal>"
       << "<pr_npc4mVal species=\"Species_2\">1</pr_npc4mVal>"
       << "<pr_npc4mVal species=\"Species_4\">1</pr_npc4mVal>"
       << "</pr_neighPredCounts4Mast>"
       << "</NeighborhoodSeedPredation1>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteNeighborhoodSeedPredationXMLErrorFile5()
/////////////////////////////////////////////////////////////////////////////
const char* WriteNeighborhoodSeedPredationXMLErrorFile5()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06010101\">"
       << "<plot>"
       << "<timesteps>1</timesteps>"
       << "<yearsPerTimestep>1</yearsPerTimestep>"
       << "<randomSeed>1</randomSeed>"
       << "<plot_lenX>100</plot_lenX>"
       << "<plot_lenY>100</plot_lenY>"
       << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
       << "<plot_temp_C>12.88171785</plot_temp_C>"
       << "<plot_latitude>55.37</plot_latitude>"
       << "</plot>";

  oOut << "<trees>"
       << "<tr_speciesList>"
       << "<tr_species speciesName=\"Species_1\"/>"
       << "</tr_speciesList>"
       << "<tr_seedDiam10Cm>0.1</tr_seedDiam10Cm>"
       << "<tr_minAdultDBH>"
       << "<tr_madVal species=\"Species_1\">10.0</tr_madVal>"
       << "</tr_minAdultDBH>"
       << "<tr_maxSeedlingHeight>"
       << "<tr_mshVal species=\"Species_1\">1.35</tr_mshVal>"
       << "</tr_maxSeedlingHeight>"
       << "</trees>"
       << "<allometry>"
       << "<tr_canopyHeight>"
       << "<tr_chVal species=\"Species_1\">39.48</tr_chVal>"
       << "</tr_canopyHeight>"
       << "<tr_stdAsympCrownRad>"
       << "<tr_sacrVal species=\"Species_1\">0.0549</tr_sacrVal>"
       << "</tr_stdAsympCrownRad>"
       << "<tr_stdCrownRadExp>"
       << "<tr_screVal species=\"Species_1\">1.0</tr_screVal>"
       << "</tr_stdCrownRadExp>"
       << "<tr_conversionDiam10ToDBH>"
       << "<tr_cdtdVal species=\"Species_1\">0.8008</tr_cdtdVal>"
       << "</tr_conversionDiam10ToDBH>"
       << "<tr_interceptDiam10ToDBH>"
       << "<tr_idtdVal species=\"Species_1\">0</tr_idtdVal>"
       << "</tr_interceptDiam10ToDBH>"
       << "<tr_stdAsympCrownHt>"
       << "<tr_sachVal species=\"Species_1\">0.389</tr_sachVal>"
       << "</tr_stdAsympCrownHt>"
       << "<tr_stdCrownHtExp>"
       << "<tr_scheVal species=\"Species_1\">1.0</tr_scheVal>"
       << "</tr_stdCrownHtExp>"
       << "<tr_slopeOfHeight-Diam10>"
       << "<tr_sohdVal species=\"Species_1\">0.03418</tr_sohdVal>"
       << "</tr_slopeOfHeight-Diam10>"
       << "<tr_slopeOfAsymHeight>"
       << "<tr_soahVal species=\"Species_1\">0.0299</tr_soahVal>"
       << "</tr_slopeOfAsymHeight>"
       << "<tr_whatSeedlingHeightDiam>"
       << "<tr_wsehdVal species=\"Species_1\">0</tr_wsehdVal>"
       << "</tr_whatSeedlingHeightDiam>"
       << "<tr_whatSaplingHeightDiam>"
       << "<tr_wsahdVal species=\"Species_1\">0</tr_wsahdVal>"
       << "</tr_whatSaplingHeightDiam>"
       << "<tr_whatAdultHeightDiam>"
       << "<tr_wahdVal species=\"Species_1\">0</tr_wahdVal>"
       << "</tr_whatAdultHeightDiam>"
       << "<tr_whatAdultCrownRadDiam>"
       << "<tr_wacrdVal species=\"Species_1\">0</tr_wacrdVal>"
       << "</tr_whatAdultCrownRadDiam>"
       << "<tr_whatAdultCrownHeightHeight>"
       << "<tr_wachhVal species=\"Species_1\">0</tr_wachhVal>"
       << "</tr_whatAdultCrownHeightHeight>"
       << "<tr_whatSaplingCrownRadDiam>"
       << "<tr_wscrdVal species=\"Species_1\">0</tr_wscrdVal>"
       << "</tr_whatSaplingCrownRadDiam>"
       << "<tr_whatSaplingCrownHeightHeight>"
       << "<tr_wschhVal species=\"Species_1\">0</tr_wschhVal>"
       << "</tr_whatSaplingCrownHeightHeight>"
       << "</allometry>";

  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>NonSpatialDisperse</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>LinkedNeighborhoodSeedPredation</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>2</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Seed\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>Establishment</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>3</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Seed\"/>"
       << "</behavior>"
       << "</behaviorList>"
       << "<GeneralDisperse>"
       << "<di_seedDistributionMethod>0</di_seedDistributionMethod>"
       << "</GeneralDisperse>"
       << "<NonSpatialDisperse1>"
       << "<di_minDbhForReproduction>"
       << "<di_mdfrVal species=\"Species_1\">15.0</di_mdfrVal>"
       << "</di_minDbhForReproduction>"
       << "<di_nonSpatialSlopeOfLambda>"
       << "<di_nssolVal species=\"Species_1\">0</di_nssolVal>"
       << "</di_nonSpatialSlopeOfLambda>"
       << "<di_nonSpatialInterceptOfLambda>"
       << "<di_nsiolVal species=\"Species_1\">1</di_nsiolVal>"
       << "</di_nonSpatialInterceptOfLambda>"
       << "</NonSpatialDisperse1>"
       << "<NeighborhoodSeedPredation2>"
       << "<pr_neighPredMastDecisionMethod>0</pr_neighPredMastDecisionMethod>"
       << "<pr_predatorInitialDensity>0.002</pr_predatorInitialDensity>"
       << "<pr_maxInstantaneousDeclineRate>-0.04</pr_maxInstantaneousDeclineRate>"
       << "<pr_demographicEfficiency>0.0002</pr_demographicEfficiency>"
       << "<pr_densityDependentCoefficient>-0.008</pr_densityDependentCoefficient>"
       << "<pr_maxIntakeRate>20</pr_maxIntakeRate>"
       << "<pr_foragingEfficiency>0.002</pr_foragingEfficiency>"
       << "<pr_numWeeksSeedFall>12</pr_numWeeksSeedFall>"
       << "<pr_numWeeksToModel>45</pr_numWeeksToModel>"
       << "<pr_weekGerminationStarts>30</pr_weekGerminationStarts>"
       << "<pr_preservePredatorDensities>0</pr_preservePredatorDensities>"
       << "<pr_proportionGerminating>0.4</pr_proportionGerminating>"
       << "<pr_neighPredRadius>10</pr_neighPredRadius>"
       << "<pr_neighPredMinNeighDBH>"
       << "<pr_npmndVal species=\"Species_1\">10</pr_npmndVal>"
       << "</pr_neighPredMinNeighDBH>"
       << "<pr_neighPredP0>"
       << "<pr_npmp0Val species=\"Species_1\">1.32</pr_npmp0Val>"
       << "</pr_neighPredP0>"
       << "<pr_neighPredPnSpecies_1>"
       << "<pr_nppnVal species=\"Species_1\">-5.94</pr_nppnVal>"
       << "</pr_neighPredPnSpecies_1>"
       << "</NeighborhoodSeedPredation2>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}


/////////////////////////////////////////////////////////////////////////////
// WriteNeighborhoodSeedPredationTreesAllometry()
/////////////////////////////////////////////////////////////////////////////
void WriteNeighborhoodSeedPredationTreesAllometry(std::fstream &oOut)
{
  oOut << "<trees>"
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
       << "<tr_mshVal species=\"Species_1\">1.35</tr_mshVal>"
       << "<tr_mshVal species=\"Species_2\">1.35</tr_mshVal>"
       << "<tr_mshVal species=\"Species_3\">1.35</tr_mshVal>"
       << "<tr_mshVal species=\"Species_4\">1.35</tr_mshVal>"
       << "</tr_maxSeedlingHeight>"
       << "</trees>"
       << "<allometry>"
       << "<tr_canopyHeight>"
       << "<tr_chVal species=\"Species_1\">39.48</tr_chVal>"
       << "<tr_chVal species=\"Species_2\">39.54</tr_chVal>"
       << "<tr_chVal species=\"Species_3\">40.0</tr_chVal>"
       << "<tr_chVal species=\"Species_4\">40.0</tr_chVal>"
       << "</tr_canopyHeight>"
       << "<tr_stdAsympCrownRad>"
       << "<tr_sacrVal species=\"Species_1\">0.0549</tr_sacrVal>"
       << "<tr_sacrVal species=\"Species_2\">0.0614</tr_sacrVal>"
       << "<tr_sacrVal species=\"Species_3\">0.0242</tr_sacrVal>"
       << "<tr_sacrVal species=\"Species_4\">0.0242</tr_sacrVal>"
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
       << "<tr_cdtdVal species=\"Species_3\">0.7059</tr_cdtdVal>"
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
       << "<tr_sachVal species=\"Species_2\">0.368</tr_sachVal>"
       << "<tr_sachVal species=\"Species_3\">0.464</tr_sachVal>"
       << "<tr_sachVal species=\"Species_4\">0.464</tr_sachVal>"
       << "</tr_stdAsympCrownHt>"
       << "<tr_stdCrownHtExp>"
       << "<tr_scheVal species=\"Species_1\">1.0</tr_scheVal>"
       << "<tr_scheVal species=\"Species_2\">1.0</tr_scheVal>"
       << "<tr_scheVal species=\"Species_3\">1.0</tr_scheVal>"
       << "<tr_scheVal species=\"Species_4\">1.0</tr_scheVal>"
       << "</tr_stdCrownHtExp>"
       << "<tr_slopeOfHeight-Diam10>"
       << "<tr_sohdVal species=\"Species_1\">0.03418</tr_sohdVal>"
       << "<tr_sohdVal species=\"Species_2\">0.0269</tr_sohdVal>"
       << "<tr_sohdVal species=\"Species_3\">0.02871</tr_sohdVal>"
       << "<tr_sohdVal species=\"Species_4\">0.02871</tr_sohdVal>"
       << "</tr_slopeOfHeight-Diam10>"
       << "<tr_slopeOfAsymHeight>"
       << "<tr_soahVal species=\"Species_1\">0.0299</tr_soahVal>"
       << "<tr_soahVal species=\"Species_2\">0.0241</tr_soahVal>"
       << "<tr_soahVal species=\"Species_3\">0.0263</tr_soahVal>"
       << "<tr_soahVal species=\"Species_4\">0.0263</tr_soahVal>"
       << "</tr_slopeOfAsymHeight>"
       << "<tr_whatSeedlingHeightDiam>"
       << "<tr_wsehdVal species=\"Species_1\">0</tr_wsehdVal>"
       << "<tr_wsehdVal species=\"Species_2\">0</tr_wsehdVal>"
       << "<tr_wsehdVal species=\"Species_3\">0</tr_wsehdVal>"
       << "<tr_wsehdVal species=\"Species_4\">0</tr_wsehdVal>"
       << "</tr_whatSeedlingHeightDiam>"
       << "<tr_whatSaplingHeightDiam>"
       << "<tr_wsahdVal species=\"Species_1\">0</tr_wsahdVal>"
       << "<tr_wsahdVal species=\"Species_2\">0</tr_wsahdVal>"
       << "<tr_wsahdVal species=\"Species_3\">0</tr_wsahdVal>"
       << "<tr_wsahdVal species=\"Species_4\">0</tr_wsahdVal>"
       << "</tr_whatSaplingHeightDiam>"
       << "<tr_whatAdultHeightDiam>"
       << "<tr_wahdVal species=\"Species_1\">0</tr_wahdVal>"
       << "<tr_wahdVal species=\"Species_2\">0</tr_wahdVal>"
       << "<tr_wahdVal species=\"Species_3\">0</tr_wahdVal>"
       << "<tr_wahdVal species=\"Species_4\">0</tr_wahdVal>"
       << "</tr_whatAdultHeightDiam>"
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
// WriteNeighborhoodSeedPredationCommonPredationParameters
/////////////////////////////////////////////////////////////////////////////
void WriteNeighborhoodSeedPredationCommonPredationParameters(std::fstream &oOut)
{
  oOut << "<pr_neighPredMastingP0>"
       << "<pr_npmp0Val species=\"Species_1\">1.32</pr_npmp0Val>"
       << "<pr_npmp0Val species=\"Species_2\">0.86</pr_npmp0Val>"
       << "<pr_npmp0Val species=\"Species_4\">-0.93</pr_npmp0Val>"
       << "</pr_neighPredMastingP0>"
       << "<pr_neighPredMastingPnSpecies_1>"
       << "<pr_npmpnVal species=\"Species_1\">-5.94</pr_npmpnVal>"
       << "<pr_npmpnVal species=\"Species_2\">0</pr_npmpnVal>"
       << "<pr_npmpnVal species=\"Species_4\">-4.72</pr_npmpnVal>"
       << "</pr_neighPredMastingPnSpecies_1>"
       << "<pr_neighPredMastingPnSpecies_2>"
       << "<pr_npmpnVal species=\"Species_1\">2.8</pr_npmpnVal>"
       << "<pr_npmpnVal species=\"Species_2\">3.1</pr_npmpnVal>"
       << "<pr_npmpnVal species=\"Species_4\">0.99</pr_npmpnVal>"
       << "</pr_neighPredMastingPnSpecies_2>"
       << "<pr_neighPredMastingPnSpecies_3>"
       << "<pr_npmpnVal species=\"Species_1\">-1.9</pr_npmpnVal>"
       << "<pr_npmpnVal species=\"Species_2\">1.99</pr_npmpnVal>"
       << "<pr_npmpnVal species=\"Species_4\">3.24</pr_npmpnVal>"
       << "</pr_neighPredMastingPnSpecies_3>"
       << "<pr_neighPredMastingPnSpecies_4>"
       << "<pr_npmpnVal species=\"Species_1\">0.00000228</pr_npmpnVal>"
       << "<pr_npmpnVal species=\"Species_2\">0.0255</pr_npmpnVal>"
       << "<pr_npmpnVal species=\"Species_4\">5.93</pr_npmpnVal>"
       << "</pr_neighPredMastingPnSpecies_4>"
       << "<pr_neighPredNonMastingP0>"
       << "<pr_npnmp0Val species=\"Species_1\">-2.51</pr_npnmp0Val>"
       << "<pr_npnmp0Val species=\"Species_2\">-1.36</pr_npnmp0Val>"
       << "<pr_npnmp0Val species=\"Species_4\">-99</pr_npnmp0Val>"
       << "</pr_neighPredNonMastingP0>"
       << "<pr_neighPredNonMastingPnSpecies_1>"
       << "<pr_npnmpnVal species=\"Species_1\">2.56</pr_npnmpnVal>"
       << "<pr_npnmpnVal species=\"Species_2\">0.23</pr_npnmpnVal>"
       << "<pr_npnmpnVal species=\"Species_4\">3.24</pr_npnmpnVal>"
       << "</pr_neighPredNonMastingPnSpecies_1>"
       << "<pr_neighPredNonMastingPnSpecies_2>"
       << "<pr_npnmpnVal species=\"Species_1\">4.91</pr_npnmpnVal>"
       << "<pr_npnmpnVal species=\"Species_2\">1.9</pr_npnmpnVal>"
       << "<pr_npnmpnVal species=\"Species_4\">5.93</pr_npnmpnVal>"
       << "</pr_neighPredNonMastingPnSpecies_2>"
       << "<pr_neighPredNonMastingPnSpecies_3>"
       << "<pr_npnmpnVal species=\"Species_1\">2.66</pr_npnmpnVal>"
       << "<pr_npnmpnVal species=\"Species_2\">-7.49</pr_npnmpnVal>"
       << "<pr_npnmpnVal species=\"Species_4\">1.83</pr_npnmpnVal>"
       << "</pr_neighPredNonMastingPnSpecies_3>"
       << "<pr_neighPredNonMastingPnSpecies_4>"
       << "<pr_npnmpnVal species=\"Species_1\">0.0255</pr_npnmpnVal>"
       << "<pr_npnmpnVal species=\"Species_2\">0.00569</pr_npnmpnVal>"
       << "<pr_npnmpnVal species=\"Species_4\">13.2</pr_npnmpnVal>"
       << "</pr_neighPredNonMastingPnSpecies_4>";
}
