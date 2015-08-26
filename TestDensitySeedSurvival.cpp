//---------------------------------------------------------------------------
// TestDensitySeedSurvival.cpp
//---------------------------------------------------------------------------
#include "TestDensitySeedSurvival.h"
#include <gtest/gtest.h>
#include "SimManager.h"
#include "TreePopulation.h"
#include "Grid.h"
#include "ModelMath.h"
#include <fstream>
#include <math.h>

/////////////////////////////////////////////////////////////////////////////
// TestDensityRun1()
// Tests normal processing of density-dependent seed survival.
// WriteDensitySeedSurvivalXMLFile1() does setup. After a run occurs, the
// number of seeds in the seed grid is verified.
/////////////////////////////////////////////////////////////////////////////
TEST(DensitySeedSurvival, TestDensityRun1)
{
  clTreePopulation *p_oPop;
  clTreeSearch *p_oAllSeedlings;
  clTree *p_oTree;
  clGrid *p_oSeeds;
  float fValue, fX, fY, fXMin, fXMax, fYMin, fYMax,
  fXCellLength = 8, fYCellLength = 8;
  int *p_iNumSeedlings = new int[4], i;

  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {

    //Feed our file to the sim manager
    p_oSimManager->ReadFile(WriteDensitySeedSurvivalXMLFile1());

    //Add the seeds to the appropriate grid cells
    p_oSeeds = p_oSimManager->GetGridObject("Dispersed Seeds");
    fValue = 100;
    p_oSeeds->SetValueOfCell(0, 0, p_oSeeds->GetFloatDataCode("seeds_1"), fValue);
    fValue = 200;
    p_oSeeds->SetValueOfCell(0, 0, p_oSeeds->GetFloatDataCode("seeds_2"), fValue);
    fValue = 300;
    p_oSeeds->SetValueOfCell(0, 0, p_oSeeds->GetFloatDataCode("seeds_3"), fValue);

    fValue = 300;
    p_oSeeds->SetValueOfCell(7, 0, p_oSeeds->GetFloatDataCode("seeds_1"), fValue);
    fValue = 100;
    p_oSeeds->SetValueOfCell(7, 0, p_oSeeds->GetFloatDataCode("seeds_2"), fValue);
    fValue = 200;
    p_oSeeds->SetValueOfCell(7, 0, p_oSeeds->GetFloatDataCode("seeds_3"), fValue);

    fValue = 100;
    p_oSeeds->SetValueOfCell(14, 0, p_oSeeds->GetFloatDataCode("seeds_1"), fValue);
    fValue = 200;
    p_oSeeds->SetValueOfCell(14, 0, p_oSeeds->GetFloatDataCode("seeds_2"), fValue);
    fValue = 300;
    p_oSeeds->SetValueOfCell(14, 0, p_oSeeds->GetFloatDataCode("seeds_3"), fValue);

    fValue = 300;
    p_oSeeds->SetValueOfCell(21, 0, p_oSeeds->GetFloatDataCode("seeds_1"), fValue);
    fValue = 100;
    p_oSeeds->SetValueOfCell(21, 0, p_oSeeds->GetFloatDataCode("seeds_2"), fValue);
    fValue = 200;
    p_oSeeds->SetValueOfCell(21, 0, p_oSeeds->GetFloatDataCode("seeds_3"), fValue);

    fValue = 100;
    p_oSeeds->SetValueOfCell(28, 0, p_oSeeds->GetFloatDataCode("seeds_1"), fValue);
    fValue = 200;
    p_oSeeds->SetValueOfCell(28, 0, p_oSeeds->GetFloatDataCode("seeds_2"), fValue);
    fValue = 300;
    p_oSeeds->SetValueOfCell(28, 0, p_oSeeds->GetFloatDataCode("seeds_3"), fValue);

    fValue = 200;
    p_oSeeds->SetValueOfCell(35, 0, p_oSeeds->GetFloatDataCode("seeds_1"), fValue);
    fValue = 300;
    p_oSeeds->SetValueOfCell(35, 0, p_oSeeds->GetFloatDataCode("seeds_2"), fValue);
    fValue = 100;
    p_oSeeds->SetValueOfCell(35, 0, p_oSeeds->GetFloatDataCode("seeds_3"), fValue);

    fValue = 300;
    p_oSeeds->SetValueOfCell(42, 0, p_oSeeds->GetFloatDataCode("seeds_1"), fValue);
    fValue = 100;
    p_oSeeds->SetValueOfCell(42, 0, p_oSeeds->GetFloatDataCode("seeds_2"), fValue);
    fValue = 200;
    p_oSeeds->SetValueOfCell(42, 0, p_oSeeds->GetFloatDataCode("seeds_3"), fValue);

    fValue = 100;
    p_oSeeds->SetValueOfCell(49, 0, p_oSeeds->GetFloatDataCode("seeds_1"), fValue);
    fValue = 200;
    p_oSeeds->SetValueOfCell(49, 0, p_oSeeds->GetFloatDataCode("seeds_2"), fValue);
    fValue = 300;
    p_oSeeds->SetValueOfCell(49, 0, p_oSeeds->GetFloatDataCode("seeds_3"), fValue);

    fValue = 200;
    p_oSeeds->SetValueOfCell(56, 0, p_oSeeds->GetFloatDataCode("seeds_1"), fValue);
    fValue = 300;
    p_oSeeds->SetValueOfCell(56, 0, p_oSeeds->GetFloatDataCode("seeds_2"), fValue);
    fValue = 100;
    p_oSeeds->SetValueOfCell(56, 0, p_oSeeds->GetFloatDataCode("seeds_3"), fValue);

    fValue = 200;
    p_oSeeds->SetValueOfCell(62, 0, p_oSeeds->GetFloatDataCode("seeds_1"), fValue);
    fValue = 300;
    p_oSeeds->SetValueOfCell(62, 0, p_oSeeds->GetFloatDataCode("seeds_2"), fValue);
    fValue = 100;
    p_oSeeds->SetValueOfCell(62, 0, p_oSeeds->GetFloatDataCode("seeds_3"), fValue);

    fValue = 200;
    p_oSeeds->SetValueOfCell(0, 12, p_oSeeds->GetFloatDataCode("seeds_1"), fValue);
    fValue = 300;
    p_oSeeds->SetValueOfCell(0, 12, p_oSeeds->GetFloatDataCode("seeds_2"), fValue);
    fValue = 100;
    p_oSeeds->SetValueOfCell(0, 12, p_oSeeds->GetFloatDataCode("seeds_3"), fValue);

    fValue = 200;
    p_oSeeds->SetValueOfCell(62, 12, p_oSeeds->GetFloatDataCode("seeds_1"), fValue);
    fValue = 300;
    p_oSeeds->SetValueOfCell(62, 12, p_oSeeds->GetFloatDataCode("seeds_2"), fValue);
    fValue = 100;
    p_oSeeds->SetValueOfCell(62, 12, p_oSeeds->GetFloatDataCode("seeds_3"), fValue);

    fValue = 1;
    p_oSeeds->SetValueOfCell(1, 7, p_oSeeds->GetFloatDataCode("seeds_1"), fValue);
    fValue = 1;
    p_oSeeds->SetValueOfCell(1, 7, p_oSeeds->GetFloatDataCode("seeds_2"), fValue);
    fValue = 1;
    p_oSeeds->SetValueOfCell(1, 7, p_oSeeds->GetFloatDataCode("seeds_3"), fValue);

    //Run a timestep
    p_oSimManager->RunSim(1);

    //Get the tree population
    p_oPop = (clTreePopulation*) p_oSimManager->GetPopulationObject("treepopulation");

    //Count the number of seedlings in each grid cell
    p_oAllSeedlings = p_oPop->Find("type=1");

    //Check our values for cell 0, 0
    for (i = 0; i < 4; i++) {
      p_iNumSeedlings[i] = 0;
    }
    fYMin = 0;
    fYMax = fYCellLength;
    fXMin = 0 * fXCellLength;
    fXMax = (0 + 1) * fXCellLength;
    p_oTree = p_oAllSeedlings->NextTree();
    while (p_oTree) {
      p_oTree->GetValue(p_oPop->GetXCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fX);
      p_oTree->GetValue(p_oPop->GetYCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fY);
      if (fX >= fXMin && fX < fXMax && fY >= fYMin && fY < fYMax) {
        p_iNumSeedlings[p_oTree->GetSpecies()]++;
      }
      p_oTree = p_oAllSeedlings->NextTree();
    }
    EXPECT_EQ(0, p_iNumSeedlings[0]);
    EXPECT_TRUE(83 == p_iNumSeedlings[1] || 84 == p_iNumSeedlings[1]);
    EXPECT_TRUE(139 == p_iNumSeedlings[2] || 140 == p_iNumSeedlings[2]);
    EXPECT_TRUE(181 == p_iNumSeedlings[3] || 182 == p_iNumSeedlings[3]);

    //Check our values for cell 7, 0
    for (i = 0; i < 4; i++) {
      p_iNumSeedlings[i] = 0;
    }
    fXMin = 7 * fXCellLength;
    fXMax = (7 + 1) * fXCellLength;
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
    EXPECT_TRUE(259 == p_iNumSeedlings[1] || 260 == p_iNumSeedlings[1]);
    EXPECT_TRUE(68 == p_iNumSeedlings[2] || 69 == p_iNumSeedlings[2]);
    EXPECT_TRUE(113 == p_iNumSeedlings[3] || 114 == p_iNumSeedlings[3]);

    //Check our values for cell 14, 0
    for (i = 0; i < 4; i++) {
      p_iNumSeedlings[i] = 0;
    }
    fXMin = 14 * fXCellLength;
    fXMax = (14 + 1) * fXCellLength;
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
    EXPECT_TRUE(83 == p_iNumSeedlings[1] || 84 == p_iNumSeedlings[1]);
    EXPECT_TRUE(139 == p_iNumSeedlings[2] || 140 == p_iNumSeedlings[2]);
    EXPECT_TRUE(181 == p_iNumSeedlings[3] || 182 == p_iNumSeedlings[3]);

    //Check our values for cell 21, 0
    for (i = 0; i < 4; i++) {
      p_iNumSeedlings[i] = 0;
    }
    fXMin = 21 * fXCellLength;
    fXMax = (21 + 1) * fXCellLength;
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
    EXPECT_TRUE(259 == p_iNumSeedlings[1] || 260 == p_iNumSeedlings[1]);
    EXPECT_TRUE(68 == p_iNumSeedlings[2] || 69 == p_iNumSeedlings[2]);
    EXPECT_TRUE(113 == p_iNumSeedlings[3] || 114 == p_iNumSeedlings[3]);

    //Check our values for cell 28, 0
    for (i = 0; i < 4; i++) {
      p_iNumSeedlings[i] = 0;
    }
    fXMin = 28 * fXCellLength;
    fXMax = (28 + 1) * fXCellLength;
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
    EXPECT_TRUE(83 == p_iNumSeedlings[1] || 84 == p_iNumSeedlings[1]);
    EXPECT_TRUE(139 == p_iNumSeedlings[2] || 140 == p_iNumSeedlings[2]);
    EXPECT_TRUE(181 == p_iNumSeedlings[3] || 182 == p_iNumSeedlings[3]);

    //Check our values for cell 35, 0
    for (i = 0; i < 4; i++) {
      p_iNumSeedlings[i] = 0;
    }
    fXMin = 35 * fXCellLength;
    fXMax = (35 + 1) * fXCellLength;
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
    EXPECT_TRUE(170 == p_iNumSeedlings[1] || 171 == p_iNumSeedlings[1]);
    EXPECT_TRUE(212 == p_iNumSeedlings[2] || 213 == p_iNumSeedlings[2]);
    EXPECT_TRUE(49 == p_iNumSeedlings[3] || 50 == p_iNumSeedlings[3]);

    //Check our values for cell 42, 0
    for (i = 0; i < 4; i++) {
      p_iNumSeedlings[i] = 0;
    }
    fXMin = 42 * fXCellLength;
    fXMax = (42 + 1) * fXCellLength;
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
    EXPECT_TRUE(259 == p_iNumSeedlings[1] || 260 == p_iNumSeedlings[1]);
    EXPECT_TRUE(68 == p_iNumSeedlings[2] || 69 == p_iNumSeedlings[2]);
    EXPECT_TRUE(113 == p_iNumSeedlings[3] || 114 == p_iNumSeedlings[3]);

    //Check our values for cell 49, 0
    for (i = 0; i < 4; i++) {
      p_iNumSeedlings[i] = 0;
    }
    fXMin = 49 * fXCellLength;
    fXMax = (49 + 1) * fXCellLength;
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
    EXPECT_TRUE(83 == p_iNumSeedlings[1] || 84 == p_iNumSeedlings[1]);
    EXPECT_TRUE(139 == p_iNumSeedlings[2] || 140 == p_iNumSeedlings[2]);
    EXPECT_TRUE(181 == p_iNumSeedlings[3] || 182 == p_iNumSeedlings[3]);

    //Check our values for cell 56, 0
    for (i = 0; i < 4; i++) {
      p_iNumSeedlings[i] = 0;
    }
    fXMin = 56 * fXCellLength;
    fXMax = (56 + 1) * fXCellLength;
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
    EXPECT_TRUE(170 == p_iNumSeedlings[1] || 171 == p_iNumSeedlings[1]);
    EXPECT_TRUE(212 == p_iNumSeedlings[2] || 213 == p_iNumSeedlings[2]);
    EXPECT_TRUE(49 == p_iNumSeedlings[3] || 50 == p_iNumSeedlings[3]);

    //Check our values for cell 62, 0
    for (i = 0; i < 4; i++) {
      p_iNumSeedlings[i] = 0;
    }
    fXMin = 62 * fXCellLength;
    fXMax = (62 + 1) * fXCellLength;
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
    EXPECT_TRUE(174 == p_iNumSeedlings[1] || 175 == p_iNumSeedlings[1]);
    EXPECT_TRUE(217 == p_iNumSeedlings[2] || 218 == p_iNumSeedlings[2]);
    EXPECT_TRUE(56 == p_iNumSeedlings[3] || 57 == p_iNumSeedlings[3]);

    //Check our values for cell 1, 0
    for (i = 0; i < 4; i++) {
      p_iNumSeedlings[i] = 0;
    }
    fXMin = 1 * fXCellLength;
    fXMax = (1 + 1) * fXCellLength;
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
    EXPECT_EQ(0, p_iNumSeedlings[1]);
    EXPECT_EQ(0, p_iNumSeedlings[2]);
    EXPECT_EQ(0, p_iNumSeedlings[3]);

    //Check our values for cell 0, 12
    for (i = 0; i < 4; i++) {
      p_iNumSeedlings[i] = 0;
    }
    fYMin = 12 * fYCellLength;
    fYMax = (12 + 1) * fYCellLength;
    fXMin = 0;
    fXMax = (0 + 1) * fXCellLength;
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
    EXPECT_TRUE(174 == p_iNumSeedlings[1] || 175 == p_iNumSeedlings[1]);
    EXPECT_TRUE(217 == p_iNumSeedlings[2] || 218 == p_iNumSeedlings[2]);
    EXPECT_TRUE(56 == p_iNumSeedlings[3] || 57 == p_iNumSeedlings[3]);

    //Check our values for cell 62, 12
    for (i = 0; i < 4; i++) {
      p_iNumSeedlings[i] = 0;
    }
    fYMin = 12 * fYCellLength;
    fYMax = (12 + 1) * fYCellLength;
    fXMin = 62 * fXCellLength;
    fXMax = (62 + 1) * fXCellLength;
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
    EXPECT_TRUE(177 == p_iNumSeedlings[1] || 178 == p_iNumSeedlings[1]);
    EXPECT_TRUE(222 == p_iNumSeedlings[2] || 223 == p_iNumSeedlings[2]);
    EXPECT_TRUE(63 == p_iNumSeedlings[3] || 64 == p_iNumSeedlings[3]);

    //Check our values for cell 1, 7
    for (i = 0; i < 4; i++) {
      p_iNumSeedlings[i] = 0;
    }
    fYMin = 7 * fYCellLength;
    fYMax = (7 + 1) * fYCellLength;
    fXMin = 1 * fYCellLength;
    fXMax = (1 + 1) * fXCellLength;
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
    EXPECT_EQ(1, p_iNumSeedlings[1]);
    EXPECT_EQ(1, p_iNumSeedlings[2]);
    EXPECT_EQ(1, p_iNumSeedlings[3]);

    delete[] p_iNumSeedlings;
    delete p_oSimManager;
  } catch (modelErr &e) {
    delete[] p_iNumSeedlings;
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

/////////////////////////////////////////////////////////////////////////////
// TestDensityRun2()
// Tests normal processing of density-dependent seed survival with different
// grid cell sizes. WriteDensitySeedSurvivalXMLFile2() does setup. After a run occurs, the
// number of seeds in the seed grid is verified.
/////////////////////////////////////////////////////////////////////////////
TEST(DensitySeedSurvival, TestDensityRun2)
{
  clTreePopulation *p_oPop;
  clTreeSearch *p_oAllSeedlings;
  clTree *p_oTree;
  clGrid *p_oSeeds;
  float fValue, fX, fY, fXMin, fXMax, fYMin, fYMax,
  fXCellLength = 3, fYCellLength = 5;
  int *p_iNumSeedlings = new int[4], i;

  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {

    //Feed our file to the sim manager
    p_oSimManager->ReadFile(WriteDensitySeedSurvivalXMLFile2());

    //Add the seeds to the appropriate grid cells
    p_oSeeds = p_oSimManager->GetGridObject("Dispersed Seeds");
    fValue = 100;
    p_oSeeds->SetValueOfCell(1, 0, p_oSeeds->GetFloatDataCode("seeds_1"), fValue);
    fValue = 200;
    p_oSeeds->SetValueOfCell(1, 0, p_oSeeds->GetFloatDataCode("seeds_2"), fValue);
    fValue = 300;
    p_oSeeds->SetValueOfCell(1, 0, p_oSeeds->GetFloatDataCode("seeds_3"), fValue);

    fValue = 300;
    p_oSeeds->SetValueOfCell(20, 0, p_oSeeds->GetFloatDataCode("seeds_1"), fValue);
    fValue = 100;
    p_oSeeds->SetValueOfCell(20, 0, p_oSeeds->GetFloatDataCode("seeds_2"), fValue);
    fValue = 200;
    p_oSeeds->SetValueOfCell(20, 0, p_oSeeds->GetFloatDataCode("seeds_3"), fValue);

    fValue = 100;
    p_oSeeds->SetValueOfCell(38, 0, p_oSeeds->GetFloatDataCode("seeds_1"), fValue);
    fValue = 200;
    p_oSeeds->SetValueOfCell(38, 0, p_oSeeds->GetFloatDataCode("seeds_2"), fValue);
    fValue = 300;
    p_oSeeds->SetValueOfCell(38, 0, p_oSeeds->GetFloatDataCode("seeds_3"), fValue);

    fValue = 300;
    p_oSeeds->SetValueOfCell(57, 0, p_oSeeds->GetFloatDataCode("seeds_1"), fValue);
    fValue = 100;
    p_oSeeds->SetValueOfCell(57, 0, p_oSeeds->GetFloatDataCode("seeds_2"), fValue);
    fValue = 200;
    p_oSeeds->SetValueOfCell(57, 0, p_oSeeds->GetFloatDataCode("seeds_3"), fValue);

    fValue = 100;
    p_oSeeds->SetValueOfCell(76, 0, p_oSeeds->GetFloatDataCode("seeds_1"), fValue);
    fValue = 200;
    p_oSeeds->SetValueOfCell(76, 0, p_oSeeds->GetFloatDataCode("seeds_2"), fValue);
    fValue = 300;
    p_oSeeds->SetValueOfCell(76, 0, p_oSeeds->GetFloatDataCode("seeds_3"), fValue);

    fValue = 200;
    p_oSeeds->SetValueOfCell(94, 0, p_oSeeds->GetFloatDataCode("seeds_1"), fValue);
    fValue = 300;
    p_oSeeds->SetValueOfCell(94, 0, p_oSeeds->GetFloatDataCode("seeds_2"), fValue);
    fValue = 100;
    p_oSeeds->SetValueOfCell(94, 0, p_oSeeds->GetFloatDataCode("seeds_3"), fValue);

    fValue = 300;
    p_oSeeds->SetValueOfCell(113, 0, p_oSeeds->GetFloatDataCode("seeds_1"), fValue);
    fValue = 100;
    p_oSeeds->SetValueOfCell(113, 0, p_oSeeds->GetFloatDataCode("seeds_2"), fValue);
    fValue = 200;
    p_oSeeds->SetValueOfCell(113, 0, p_oSeeds->GetFloatDataCode("seeds_3"), fValue);

    fValue = 100;
    p_oSeeds->SetValueOfCell(132, 0, p_oSeeds->GetFloatDataCode("seeds_1"), fValue);
    fValue = 200;
    p_oSeeds->SetValueOfCell(132, 0, p_oSeeds->GetFloatDataCode("seeds_2"), fValue);
    fValue = 300;
    p_oSeeds->SetValueOfCell(132, 0, p_oSeeds->GetFloatDataCode("seeds_3"), fValue);

    fValue = 200;
    p_oSeeds->SetValueOfCell(150, 0, p_oSeeds->GetFloatDataCode("seeds_1"), fValue);
    fValue = 300;
    p_oSeeds->SetValueOfCell(150, 0, p_oSeeds->GetFloatDataCode("seeds_2"), fValue);
    fValue = 100;
    p_oSeeds->SetValueOfCell(150, 0, p_oSeeds->GetFloatDataCode("seeds_3"), fValue);

    fValue = 200;
    p_oSeeds->SetValueOfCell(166, 0, p_oSeeds->GetFloatDataCode("seeds_1"), fValue);
    fValue = 300;
    p_oSeeds->SetValueOfCell(166, 0, p_oSeeds->GetFloatDataCode("seeds_2"), fValue);
    fValue = 100;
    p_oSeeds->SetValueOfCell(166, 0, p_oSeeds->GetFloatDataCode("seeds_3"), fValue);

    fValue = 200;
    p_oSeeds->SetValueOfCell(1, 19, p_oSeeds->GetFloatDataCode("seeds_1"), fValue);
    fValue = 300;
    p_oSeeds->SetValueOfCell(1, 19, p_oSeeds->GetFloatDataCode("seeds_2"), fValue);
    fValue = 100;
    p_oSeeds->SetValueOfCell(1, 19, p_oSeeds->GetFloatDataCode("seeds_3"), fValue);

    fValue = 200;
    p_oSeeds->SetValueOfCell(166, 19, p_oSeeds->GetFloatDataCode("seeds_1"), fValue);
    fValue = 300;
    p_oSeeds->SetValueOfCell(166, 19, p_oSeeds->GetFloatDataCode("seeds_2"), fValue);
    fValue = 100;
    p_oSeeds->SetValueOfCell(166, 19, p_oSeeds->GetFloatDataCode("seeds_3"), fValue);

    fValue = 1;
    p_oSeeds->SetValueOfCell(4, 12, p_oSeeds->GetFloatDataCode("seeds_1"), fValue);
    fValue = 1;
    p_oSeeds->SetValueOfCell(4, 12, p_oSeeds->GetFloatDataCode("seeds_2"), fValue);
    fValue = 1;
    p_oSeeds->SetValueOfCell(4, 12, p_oSeeds->GetFloatDataCode("seeds_3"), fValue);

    //Run a timestep
    p_oSimManager->RunSim(1);

    //Get the tree population
    p_oPop = (clTreePopulation*) p_oSimManager->GetPopulationObject("treepopulation");

    //Count the number of seedlings in each grid cell
    p_oAllSeedlings = p_oPop->Find("type=1");

    //Check our values for cell 1, 0
    for (i = 0; i < 4; i++) {
      p_iNumSeedlings[i] = 0;
    }
    fYMin = 0;
    fYMax = fYCellLength;
    fXMin = 1 * fXCellLength;
    fXMax = (1 + 1) * fXCellLength;
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
    EXPECT_EQ(0, p_iNumSeedlings[1]);
    EXPECT_TRUE(4 == p_iNumSeedlings[2] || 5 == p_iNumSeedlings[2]);
    EXPECT_TRUE(216 == p_iNumSeedlings[3] || 217 == p_iNumSeedlings[3]);

    //Check our values for cell 20, 0
    for (i = 0; i < 4; i++) {
      p_iNumSeedlings[i] = 0;
    }
    fXMin = 20 * fXCellLength;
    fXMax = (20 + 1) * fXCellLength;
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
    EXPECT_EQ(0, p_iNumSeedlings[1]);
    EXPECT_TRUE(2 == p_iNumSeedlings[2] || 3 == p_iNumSeedlings[2]);
    EXPECT_TRUE(138 == p_iNumSeedlings[3] || 139 == p_iNumSeedlings[3]);

    //Check our values for cell 38, 0
    for (i = 0; i < 4; i++) {
      p_iNumSeedlings[i] = 0;
    }
    fXMin = 38 * fXCellLength;
    fXMax = (38 + 1) * fXCellLength;
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
    EXPECT_EQ(0, p_iNumSeedlings[1]);
    EXPECT_TRUE(4 == p_iNumSeedlings[2] || 5 == p_iNumSeedlings[2]);
    EXPECT_TRUE(216 == p_iNumSeedlings[3] || 217 == p_iNumSeedlings[3]);

    //Check our values for cell 57, 0
    for (i = 0; i < 4; i++) {
      p_iNumSeedlings[i] = 0;
    }
    fXMin = 57 * fXCellLength;
    fXMax = (57 + 1) * fXCellLength;
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
    EXPECT_EQ(0, p_iNumSeedlings[1]);
    EXPECT_TRUE(2 == p_iNumSeedlings[2] || 3 == p_iNumSeedlings[2]);
    EXPECT_TRUE(138 == p_iNumSeedlings[3] || 139 == p_iNumSeedlings[3]);

    //Check our values for cell 76, 0
    for (i = 0; i < 4; i++) {
      p_iNumSeedlings[i] = 0;
    }
    fXMin = 76 * fXCellLength;
    fXMax = (76 + 1) * fXCellLength;
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
    EXPECT_EQ(0, p_iNumSeedlings[1]);
    EXPECT_TRUE(4 == p_iNumSeedlings[2] || 5 == p_iNumSeedlings[2]);
    EXPECT_TRUE(216 == p_iNumSeedlings[3] || 217 == p_iNumSeedlings[3]);

    //Check our values for cell 94, 0
    for (i = 0; i < 4; i++) {
      p_iNumSeedlings[i] = 0;
    }
    fXMin = 94 * fXCellLength;
    fXMax = (94 + 1) * fXCellLength;
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
    EXPECT_EQ(0, p_iNumSeedlings[1]);
    EXPECT_TRUE(5 == p_iNumSeedlings[2] || 6 == p_iNumSeedlings[2]);
    EXPECT_TRUE(63 == p_iNumSeedlings[3] || 64 == p_iNumSeedlings[3]);

    //Check our values for cell 113, 0
    for (i = 0; i < 4; i++) {
      p_iNumSeedlings[i] = 0;
    }
    fXMin = 113 * fXCellLength;
    fXMax = (113 + 1) * fXCellLength;
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
    EXPECT_EQ(0, p_iNumSeedlings[1]);
    EXPECT_TRUE(2 == p_iNumSeedlings[2] || 3 == p_iNumSeedlings[2]);
    EXPECT_TRUE(138 == p_iNumSeedlings[3] || 139 == p_iNumSeedlings[3]);

    //Check our values for cell 132, 0
    for (i = 0; i < 4; i++) {
      p_iNumSeedlings[i] = 0;
    }
    fXMin = 132 * fXCellLength;
    fXMax = (132 + 1) * fXCellLength;
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
    EXPECT_EQ(0, p_iNumSeedlings[1]);
    EXPECT_TRUE(4 == p_iNumSeedlings[2] || 5 == p_iNumSeedlings[2]);
    EXPECT_TRUE(216 == p_iNumSeedlings[3] || 217 == p_iNumSeedlings[3]);

    //Check our values for cell 150, 0
    for (i = 0; i < 4; i++) {
      p_iNumSeedlings[i] = 0;
    }
    fXMin = 150 * fXCellLength;
    fXMax = (150 + 1) * fXCellLength;
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
    EXPECT_EQ(0, p_iNumSeedlings[1]);
    EXPECT_TRUE(5 == p_iNumSeedlings[2] || 6 == p_iNumSeedlings[2]);
    EXPECT_TRUE(63 == p_iNumSeedlings[3] || 64 == p_iNumSeedlings[3]);

    //Check our values for cell 166, 0
    for (i = 0; i < 4; i++) {
      p_iNumSeedlings[i] = 0;
    }
    fXMin = 166 * fXCellLength;
    fXMax = (166 + 1) * fXCellLength;
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
    EXPECT_EQ(0, p_iNumSeedlings[1]);
    EXPECT_TRUE(4 == p_iNumSeedlings[2] || 5 == p_iNumSeedlings[2]);
    EXPECT_TRUE(66 == p_iNumSeedlings[3] || 67 == p_iNumSeedlings[3]);

    //Check our values for cell 1, 19
    for (i = 0; i < 4; i++) {
      p_iNumSeedlings[i] = 0;
    }
    fYMin = 19 * fYCellLength;
    fYMax = (19 + 1) * fYCellLength;
    fXMin = 1 * fXCellLength;
    fXMax = (1 + 1) * fXCellLength;
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
    EXPECT_EQ(0, p_iNumSeedlings[1]);
    EXPECT_TRUE(5 == p_iNumSeedlings[2] || 6 == p_iNumSeedlings[2]);
    EXPECT_TRUE(63 == p_iNumSeedlings[3] || 64 == p_iNumSeedlings[3]);

    //Check our values for cell 166, 19
    for (i = 0; i < 4; i++) {
      p_iNumSeedlings[i] = 0;
    }
    fYMin = 19 * fYCellLength;
    fYMax = (19 + 1) * fYCellLength;
    fXMin = 166 * fXCellLength;
    fXMax = (166 + 1) * fXCellLength;
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
    EXPECT_EQ(0, p_iNumSeedlings[1]);
    EXPECT_TRUE(4 == p_iNumSeedlings[2] || 5 == p_iNumSeedlings[2]);
    EXPECT_TRUE(66 == p_iNumSeedlings[3] || 67 == p_iNumSeedlings[3]);

    //Check our values for cell 4, 12
    for (i = 0; i < 4; i++) {
      p_iNumSeedlings[i] = 0;
    }
    fYMin = 12 * fYCellLength;
    fYMax = (12 + 1) * fYCellLength;
    fXMin = 4 * fXCellLength;
    fXMax = (4 + 1) * fXCellLength;
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
    EXPECT_EQ(1, p_iNumSeedlings[1]);
    EXPECT_EQ(1, p_iNumSeedlings[2]);
    EXPECT_EQ(1, p_iNumSeedlings[3]);

    //Check our values for cell 0, 0
    for (i = 0; i < 4; i++) {
      p_iNumSeedlings[i] = 0;
    }
    fXMin = 0;
    fXMax = fXCellLength;
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
    EXPECT_EQ(0, p_iNumSeedlings[0]);
    EXPECT_EQ(0, p_iNumSeedlings[1]);
    EXPECT_EQ(0, p_iNumSeedlings[2]);
    EXPECT_EQ(0, p_iNumSeedlings[3]);

    delete[] p_iNumSeedlings;
    delete p_oSimManager;
  } catch (modelErr &e) {
    delete[] p_iNumSeedlings;
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

/////////////////////////////////////////////////////////////////////////////
// TestDensityRun3()
// Tests normal processing of density-dependent seed survival with different
// grid cell sizes. WriteDensitySeedSurvivalXMLFile3() does setup. After a run occurs, the
// number of seeds in the seed grid is verified.
/////////////////////////////////////////////////////////////////////////////
TEST(DensitySeedSurvival, TestDensityRun3)
{
  clTreePopulation *p_oPop;
  clTreeSearch *p_oAllSeedlings;
  clTree *p_oTree;
  clGrid *p_oSeeds;
  float fValue, fX, fY, fXMin, fXMax, fYMin, fYMax,
  fXCellLength = 5, fYCellLength = 5;
  int *p_iNumSeedlings = new int[4], i;

  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {

    //Feed our file to the sim manager
    p_oSimManager->ReadFile(WriteDensitySeedSurvivalXMLFile3());

    //Add the seeds to the appropriate grid cells
    p_oSeeds = p_oSimManager->GetGridObject("Dispersed Seeds");
    fValue = 100;
    p_oSeeds->SetValueOfCell(19, 0, p_oSeeds->GetFloatDataCode("seeds_1"), fValue);
    fValue = 200;
    p_oSeeds->SetValueOfCell(19, 0, p_oSeeds->GetFloatDataCode("seeds_2"), fValue);
    fValue = 300;
    p_oSeeds->SetValueOfCell(19, 0, p_oSeeds->GetFloatDataCode("seeds_3"), fValue);

    fValue = 300;
    p_oSeeds->SetValueOfCell(0, 19, p_oSeeds->GetFloatDataCode("seeds_1"), fValue);
    fValue = 100;
    p_oSeeds->SetValueOfCell(0, 19, p_oSeeds->GetFloatDataCode("seeds_2"), fValue);
    fValue = 200;
    p_oSeeds->SetValueOfCell(0, 19, p_oSeeds->GetFloatDataCode("seeds_3"), fValue);

    fValue = 100;
    p_oSeeds->SetValueOfCell(0, 0, p_oSeeds->GetFloatDataCode("seeds_1"), fValue);
    fValue = 200;
    p_oSeeds->SetValueOfCell(0, 0, p_oSeeds->GetFloatDataCode("seeds_2"), fValue);
    fValue = 300;
    p_oSeeds->SetValueOfCell(0, 0, p_oSeeds->GetFloatDataCode("seeds_3"), fValue);

    fValue = 300;
    p_oSeeds->SetValueOfCell(19, 19, p_oSeeds->GetFloatDataCode("seeds_1"), fValue);
    fValue = 100;
    p_oSeeds->SetValueOfCell(19, 19, p_oSeeds->GetFloatDataCode("seeds_2"), fValue);
    fValue = 200;
    p_oSeeds->SetValueOfCell(19, 19, p_oSeeds->GetFloatDataCode("seeds_3"), fValue);

    //Run a timestep
    p_oSimManager->RunSim(1);

    //Get the tree population
    p_oPop = (clTreePopulation*) p_oSimManager->GetPopulationObject("treepopulation");

    //Count the number of seedlings in each grid cell
    p_oAllSeedlings = p_oPop->Find("type=1");

    //Check our values for cell 19, 0
    for (i = 0; i < 4; i++) {
      p_iNumSeedlings[i] = 0;
    }
    fYMin = 0;
    fYMax = fYCellLength;
    fXMin = 19 * fXCellLength;
    fXMax = (19 + 1) * fXCellLength;
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
    EXPECT_TRUE(85 == p_iNumSeedlings[1] || 86 == p_iNumSeedlings[1]);
    EXPECT_TRUE(144 == p_iNumSeedlings[2] || 145 == p_iNumSeedlings[2]);
    EXPECT_TRUE(205 == p_iNumSeedlings[3] || 206 == p_iNumSeedlings[3]);

    //Check our values for cell 0, 19
    for (i = 0; i < 4; i++) {
      p_iNumSeedlings[i] = 0;
    }
    fXMin = 0;
    fXMax = fXCellLength;
    fYMin = 19 * fYCellLength;
    fYMax = (19 + 1) * fYCellLength;
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
    EXPECT_TRUE(265 == p_iNumSeedlings[1] || 266 == p_iNumSeedlings[1]);
    EXPECT_TRUE(70 == p_iNumSeedlings[2] || 71 == p_iNumSeedlings[2]);
    EXPECT_TRUE(130 == p_iNumSeedlings[3] || 131 == p_iNumSeedlings[3]);

    //Check our values for cell 0, 0
    for (i = 0; i < 4; i++) {
      p_iNumSeedlings[i] = 0;
    }
    fXMin = 0;
    fXMax = fXCellLength;
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
    EXPECT_EQ(0, p_iNumSeedlings[0]);
    EXPECT_TRUE(85 == p_iNumSeedlings[1] || 86 == p_iNumSeedlings[1]);
    EXPECT_TRUE(144 == p_iNumSeedlings[2] || 145 == p_iNumSeedlings[2]);
    EXPECT_TRUE(205 == p_iNumSeedlings[3] || 206 == p_iNumSeedlings[3]);

    //Check our values for cell 19, 19
    for (i = 0; i < 4; i++) {
      p_iNumSeedlings[i] = 0;
    }
    fXMin = 19 * fXCellLength;
    fXMax = (19 + 1) * fXCellLength;
    fYMin = 19 * fYCellLength;
    fYMax = (19 + 1) * fYCellLength;
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
    EXPECT_TRUE(265 == p_iNumSeedlings[1] || 266 == p_iNumSeedlings[1]);
    EXPECT_TRUE(70 == p_iNumSeedlings[2] || 71 == p_iNumSeedlings[2]);
    EXPECT_TRUE(130 == p_iNumSeedlings[3] || 131 == p_iNumSeedlings[3]);

    delete[] p_iNumSeedlings;
    delete p_oSimManager;
  } catch (modelErr &e) {
    delete[] p_iNumSeedlings;
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

/////////////////////////////////////////////////////////////////////////////
// TestDensityRun4()
// Tests normal processing of seed survival dependent on density of conspecific
// neighbor trees. WriteDensitySeedSurvivalXMLFile4() does setup.  After a run occurs, the
// number of seeds in the seed grid is verified.
/////////////////////////////////////////////////////////////////////////////
TEST(DensitySeedSurvival, TestDensityRun4)
{
  clTreePopulation *p_oPop;
  clTreeSearch *p_oAllSeedlings;
  clTree *p_oTree;
  clGrid *p_oSeeds;
  float fValue, fX, fY, fXMin, fXMax, fYMin, fYMax,
  fXCellLength = 8, fYCellLength = 8, fDiam;
  int *p_iNumSeedlings = new int[4], i;

  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {

    //Feed our file to the sim manager
    p_oSimManager->ReadFile(WriteDensitySeedSurvivalXMLFile4());
    p_oPop = (clTreePopulation*) p_oSimManager->GetPopulationObject("treepopulation");

    //Add the seeds and neighbors to the appropriate grid cells
    //0, 0
    p_oSeeds = p_oSimManager->GetGridObject("Dispersed Seeds");
    fValue = 100;
    p_oSeeds->SetValueOfCell(0, 0, p_oSeeds->GetFloatDataCode("seeds_1"), fValue);
    fValue = 200;
    p_oSeeds->SetValueOfCell(0, 0, p_oSeeds->GetFloatDataCode("seeds_2"), fValue);
    fValue = 300;
    p_oSeeds->SetValueOfCell(0, 0, p_oSeeds->GetFloatDataCode("seeds_3"), fValue);

    for (i = 0; i < 100; i++) {
      fDiam = 1.414583333;
      fX = 2 + (clModelMath::GetRand() * 4);
      fY = 2 + (clModelMath::GetRand() * 4);
      p_oPop->CreateTree(fX, fY, 1, clTreePopulation::sapling, fDiam);
    }
    for (i = 0; i < 200; i++) {
      fDiam = 2.617977528;
      fX = 2 + (clModelMath::GetRand() * 4);
      fY = 2 + (clModelMath::GetRand() * 4);
      p_oPop->CreateTree(fX, fY, 2, clTreePopulation::sapling, fDiam);
    }
    for (i = 0; i < 300; i++) {
      fDiam = 5.796037296;
      fX = 2 + (clModelMath::GetRand() * 4);
      fY = 2 + (clModelMath::GetRand() * 4);
      p_oPop->CreateTree(fX, fY, 3, clTreePopulation::sapling, fDiam);
    }
    for (i = 0; i < 100; i++) {
      fDiam = 1.250582751;
      fX = 2 + (clModelMath::GetRand() * 4);
      fY = 2 + (clModelMath::GetRand() * 4);
      p_oPop->CreateTree(fX, fY, 3, clTreePopulation::sapling, fDiam);
    }

    //7, 0
    fValue = 300;
    p_oSeeds->SetValueOfCell(7, 0, p_oSeeds->GetFloatDataCode("seeds_1"), fValue);
    fValue = 100;
    p_oSeeds->SetValueOfCell(7, 0, p_oSeeds->GetFloatDataCode("seeds_2"), fValue);
    fValue = 200;
    p_oSeeds->SetValueOfCell(7, 0, p_oSeeds->GetFloatDataCode("seeds_3"), fValue);

    for (i = 0; i < 100; i++) {
      fDiam = 10.68541667;
      fX = 62 + (clModelMath::GetRand() * 4);
      fY = 2 + (clModelMath::GetRand() * 4);
      p_oPop->CreateTree(fX, fY, 1, clTreePopulation::sapling, fDiam);
    }
    for (i = 0; i < 200; i++) {
      fDiam = 11.60674157;
      fX = 62 + (clModelMath::GetRand() * 4);
      fY = 2 + (clModelMath::GetRand() * 4);
      p_oPop->CreateTree(fX, fY, 2, clTreePopulation::sapling, fDiam);
    }
    for (i = 0; i < 300; i++) {
      fDiam = 5.796037296;
      fX = 62 + (clModelMath::GetRand() * 4);
      fY = 2 + (clModelMath::GetRand() * 4);
      p_oPop->CreateTree(fX, fY, 3, clTreePopulation::sapling, fDiam);
    }
    for (i = 0; i < 100; i++) {
      fDiam = 1.250582751;
      fX = 62 + (clModelMath::GetRand() * 4);
      fY = 2 + (clModelMath::GetRand() * 4);
      p_oPop->CreateTree(fX, fY, 3, clTreePopulation::sapling, fDiam);
    }


    //14, 0
    fValue = 100;
    p_oSeeds->SetValueOfCell(14, 0, p_oSeeds->GetFloatDataCode("seeds_1"), fValue);
    fValue = 200;
    p_oSeeds->SetValueOfCell(14, 0, p_oSeeds->GetFloatDataCode("seeds_2"), fValue);
    fValue = 300;
    p_oSeeds->SetValueOfCell(14, 0, p_oSeeds->GetFloatDataCode("seeds_3"), fValue);

    for (i = 0; i < 200; i++) {
      fDiam = 22.84269663;
      fX = 118 + (clModelMath::GetRand() * 4);
      fY = 2 + (clModelMath::GetRand() * 4);
      p_oPop->CreateTree(fX, fY, 2, clTreePopulation::sapling, fDiam);
    }
    for (i = 0; i < 300; i++) {
      fDiam = 5.796037296;
      fX = 118 + (clModelMath::GetRand() * 4);
      fY = 2 + (clModelMath::GetRand() * 4);
      p_oPop->CreateTree(fX, fY, 3, clTreePopulation::sapling, fDiam);
    }
    for (i = 0; i < 100; i++) {
      fDiam = 1.250582751;
      fX = 118 + (clModelMath::GetRand() * 4);
      fY = 2 + (clModelMath::GetRand() * 4);
      p_oPop->CreateTree(fX, fY, 3, clTreePopulation::sapling, fDiam);
    }

    //21, 0
    fValue = 300;
    p_oSeeds->SetValueOfCell(21, 0, p_oSeeds->GetFloatDataCode("seeds_1"), fValue);
    fValue = 100;
    p_oSeeds->SetValueOfCell(21, 0, p_oSeeds->GetFloatDataCode("seeds_2"), fValue);
    fValue = 200;
    p_oSeeds->SetValueOfCell(21, 0, p_oSeeds->GetFloatDataCode("seeds_3"), fValue);

    for (i = 0; i < 200; i++) {
      fDiam = 1.414583333;
      fX = 174 + (clModelMath::GetRand() * 4);
      fY = 2 + (clModelMath::GetRand() * 4);
      p_oPop->CreateTree(fX, fY, 1, clTreePopulation::sapling, fDiam);
    }
    for (i = 0; i < 100; i++) {
      fDiam = 5.796037296;
      fX = 174 + (clModelMath::GetRand() * 4);
      fY = 2 + (clModelMath::GetRand() * 4);
      p_oPop->CreateTree(fX, fY, 3, clTreePopulation::sapling, fDiam);
    }
    for (i = 0; i < 100; i++) {
      fDiam = 1.250582751;
      fX = 174 + (clModelMath::GetRand() * 4);
      fY = 2 + (clModelMath::GetRand() * 4);
      p_oPop->CreateTree(fX, fY, 3, clTreePopulation::sapling, fDiam);
    }

    //28, 0
    fValue = 100;
    p_oSeeds->SetValueOfCell(28, 0, p_oSeeds->GetFloatDataCode("seeds_1"), fValue);
    fValue = 200;
    p_oSeeds->SetValueOfCell(28, 0, p_oSeeds->GetFloatDataCode("seeds_2"), fValue);
    fValue = 300;
    p_oSeeds->SetValueOfCell(28, 0, p_oSeeds->GetFloatDataCode("seeds_3"), fValue);

    for (i = 0; i < 300; i++) {
      fDiam = 10.68541667;
      fX = 230 + (clModelMath::GetRand() * 4);
      fY = 2 + (clModelMath::GetRand() * 4);
      p_oPop->CreateTree(fX, fY, 1, clTreePopulation::sapling, fDiam);
    }
    for (i = 0; i < 100; i++) {
      fDiam = 11.60674157;
      fX = 230 + (clModelMath::GetRand() * 4);
      fY = 2 + (clModelMath::GetRand() * 4);
      p_oPop->CreateTree(fX, fY, 2, clTreePopulation::sapling, fDiam);
    }
    for (i = 0; i < 100; i++) {
      fDiam = 1.250582751;
      fX = 62 + (clModelMath::GetRand() * 4);
      fY = 2 + (clModelMath::GetRand() * 4);
      p_oPop->CreateTree(fX, fY, 3, clTreePopulation::sapling, fDiam);
    }

    //35, 0
    fValue = 200;
    p_oSeeds->SetValueOfCell(35, 0, p_oSeeds->GetFloatDataCode("seeds_1"), fValue);
    fValue = 300;
    p_oSeeds->SetValueOfCell(35, 0, p_oSeeds->GetFloatDataCode("seeds_2"), fValue);
    fValue = 100;
    p_oSeeds->SetValueOfCell(35, 0, p_oSeeds->GetFloatDataCode("seeds_3"), fValue);

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
    fXMin = 0 * fXCellLength;
    fXMax = (0 + 1) * fXCellLength;
    p_oTree = p_oAllSeedlings->NextTree();
    while (p_oTree) {
      p_oTree->GetValue(p_oPop->GetXCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fX);
      p_oTree->GetValue(p_oPop->GetYCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fY);
      if (fX >= fXMin && fX < fXMax && fY >= fYMin && fY < fYMax) {
        p_iNumSeedlings[p_oTree->GetSpecies()]++;
      }
      p_oTree = p_oAllSeedlings->NextTree();
    }
    EXPECT_EQ(0, p_iNumSeedlings[0]);
    EXPECT_TRUE(79 == p_iNumSeedlings[1] || 80 == p_iNumSeedlings[1]);
    EXPECT_TRUE(134 == p_iNumSeedlings[2] || 135 == p_iNumSeedlings[2]);
    EXPECT_TRUE(147 == p_iNumSeedlings[3] || 148 == p_iNumSeedlings[3]);

    //Check our values for cell 7, 0
    for (i = 0; i < 4; i++) {
      p_iNumSeedlings[i] = 0;
    }
    fXMin = 7 * fXCellLength;
    fXMax = (7 + 1) * fXCellLength;
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
    EXPECT_TRUE(238 == p_iNumSeedlings[1] || 239 == p_iNumSeedlings[1]);
    EXPECT_TRUE(67 == p_iNumSeedlings[2] || 68 == p_iNumSeedlings[2]);
    EXPECT_TRUE(98 == p_iNumSeedlings[3] || 99 == p_iNumSeedlings[3]);

    //Check our values for cell 14, 0
    for (i = 0; i < 4; i++) {
      p_iNumSeedlings[i] = 0;
    }
    fXMin = 14 * fXCellLength;
    fXMax = (14 + 1) * fXCellLength;
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
    EXPECT_EQ(100, p_iNumSeedlings[1]);
    EXPECT_TRUE(134 == p_iNumSeedlings[2] || 135 == p_iNumSeedlings[2]);
    EXPECT_TRUE(147 == p_iNumSeedlings[3] || 148 == p_iNumSeedlings[3]);

    //Check our values for cell 21, 0
    for (i = 0; i < 4; i++) {
      p_iNumSeedlings[i] = 0;
    }
    fXMin = 21 * fXCellLength;
    fXMax = (21 + 1) * fXCellLength;
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
    EXPECT_TRUE(245 == p_iNumSeedlings[1] || 246 == p_iNumSeedlings[1]);
    EXPECT_EQ(100, p_iNumSeedlings[2]);
    EXPECT_TRUE(74 == p_iNumSeedlings[3] || 75 == p_iNumSeedlings[3]);

    //Check our values for cell 28, 0
    for (i = 0; i < 4; i++) {
      p_iNumSeedlings[i] = 0;
    }
    fXMin = 28 * fXCellLength;
    fXMax = (28 + 1) * fXCellLength;
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
    EXPECT_TRUE(83 == p_iNumSeedlings[1] || 84 == p_iNumSeedlings[1]);
    EXPECT_TRUE(130 == p_iNumSeedlings[2] || 131 == p_iNumSeedlings[2]);
    EXPECT_EQ(300, p_iNumSeedlings[3]);

    //Check our values for cell 35, 0
    for (i = 0; i < 4; i++) {
      p_iNumSeedlings[i] = 0;
    }
    fXMin = 35 * fXCellLength;
    fXMax = (35 + 1) * fXCellLength;
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
    EXPECT_EQ(200, p_iNumSeedlings[1]);
    EXPECT_EQ(300, p_iNumSeedlings[2]);
    EXPECT_EQ(100, p_iNumSeedlings[3]);

    delete[] p_iNumSeedlings;
    delete p_oSimManager;
  } catch (modelErr &e) {
    delete[] p_iNumSeedlings;
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

/////////////////////////////////////////////////////////////////////////////
// WriteDensitySeedSurvivalXMLFile1()
/////////////////////////////////////////////////////////////////////////////
const char* WriteDensitySeedSurvivalXMLFile1()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
      << "<paramFile fileCode=\"06010101\">" << "<plot>"
      << "<timesteps>1</timesteps>"
      << "<yearsPerTimestep>5</yearsPerTimestep>"
      << "<randomSeed>1</randomSeed>"
      << "<plot_lenX>500.0</plot_lenX>"
      << "<plot_lenY>100.0</plot_lenY>"
      << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
      << "<plot_temp_C>12.88171785</plot_temp_C>"
      << "<plot_latitude>55.37</plot_latitude>"
      << "</plot>";

  WriteDensitySeedSurvivalCommonStuff(oOut);

  oOut << "<behaviorList>"
      << "<behavior>"
      << "<behaviorName>NonSpatialDisperse</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>1</listPosition>"
      << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_4\" type=\"Adult\"/>"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>DensityDependentSeedSurvival</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>2</listPosition>"
      << "<applyTo species=\"Species_2\" type=\"Seed\"/>"
      << "<applyTo species=\"Species_3\" type=\"Seed\"/>"
      << "<applyTo species=\"Species_4\" type=\"Seed\"/>"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>Establishment</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>3</listPosition>"
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
      << "<di_mdfrVal species=\"Species_2\">15.0</di_mdfrVal>"
      << "<di_mdfrVal species=\"Species_3\">15.0</di_mdfrVal>"
      << "<di_mdfrVal species=\"Species_4\">15.0</di_mdfrVal>"
      << "</di_minDbhForReproduction>"
      << "<di_nonSpatialSlopeOfLambda>"
      << "<di_nssolVal species=\"Species_4\">0</di_nssolVal>"
      << "<di_nssolVal species=\"Species_2\">0</di_nssolVal>"
      << "<di_nssolVal species=\"Species_3\">0</di_nssolVal>"
      << "</di_nonSpatialSlopeOfLambda>"
      << "<di_nonSpatialInterceptOfLambda>"
      << "<di_nsiolVal species=\"Species_4\">0</di_nsiolVal>"
      << "<di_nsiolVal species=\"Species_2\">0</di_nsiolVal>"
      << "<di_nsiolVal species=\"Species_3\">0</di_nsiolVal>"
      << "</di_nonSpatialInterceptOfLambda>"
      << "</NonSpatialDisperse1>"
      << "<DensityDependentSeedSurvival2>"
      << "<es_densDepSlope>"
      << "<es_ddsVal species=\"Species_2\">0.2</es_ddsVal>"
      << "<es_ddsVal species=\"Species_3\">0.4</es_ddsVal>"
      << "<es_ddsVal species=\"Species_4\">0.8</es_ddsVal>"
      << "</es_densDepSlope>"
      << "<es_densDepSteepness>"
      << "<es_ddstVal species=\"Species_2\">-0.2</es_ddstVal>"
      << "<es_ddstVal species=\"Species_3\">-0.1</es_ddstVal>"
      << "<es_ddstVal species=\"Species_4\">-0.3</es_ddstVal>"
      << "</es_densDepSteepness>"
      << "</DensityDependentSeedSurvival2>"
      << "</paramFile>";

  oOut.close();

  return cFileString;
}


/////////////////////////////////////////////////////////////////////////////
// WriteDensitySeedSurvivalXMLFile2()
/////////////////////////////////////////////////////////////////////////////
const char* WriteDensitySeedSurvivalXMLFile2()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
      << "<paramFile fileCode=\"06010101\">" << "<plot>"
      << "<timesteps>1</timesteps>"
      << "<yearsPerTimestep>5</yearsPerTimestep>"
      << "<randomSeed>1</randomSeed>"
      << "<plot_lenX>500.0</plot_lenX>"
      << "<plot_lenY>100.0</plot_lenY>"
      << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
      << "<plot_temp_C>12.88171785</plot_temp_C>"
      << "<plot_latitude>55.37</plot_latitude>"
      << "</plot>";

  WriteDensitySeedSurvivalCommonStuff(oOut);

  oOut << "<grid gridName=\"Dispersed Seeds\">"
      << "<ma_floatCodes>"
      << "<ma_floatCode label=\"seeds_0\">0</ma_floatCode>"
      << "<ma_floatCode label=\"seeds_1\">1</ma_floatCode>"
      << "<ma_floatCode label=\"seeds_2\">2</ma_floatCode>"
      << "<ma_floatCode label=\"seeds_3\">3</ma_floatCode>"
      << "</ma_floatCodes>"
      << "<ma_boolCodes>"
      << "<ma_boolCode label=\"Is Gap\">0</ma_boolCode>"
      << "</ma_boolCodes>"
      << "<ma_intCodes>"
      << "<ma_intCode label=\"count\">0</ma_intCode>"
      << "</ma_intCodes>"
      << "<ma_lengthXCells>3</ma_lengthXCells>"
      << "<ma_lengthYCells>5</ma_lengthYCells>"
      << "</grid>";

  oOut << "<behaviorList>"
      << "<behavior>"
      << "<behaviorName>NonSpatialDisperse</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>1</listPosition>"
      << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_4\" type=\"Adult\"/>"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>DensityDependentSeedSurvival</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>2</listPosition>"
      << "<applyTo species=\"Species_2\" type=\"Seed\"/>"
      << "<applyTo species=\"Species_3\" type=\"Seed\"/>"
      << "<applyTo species=\"Species_4\" type=\"Seed\"/>"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>Establishment</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>3</listPosition>"
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
      << "<di_mdfrVal species=\"Species_2\">15.0</di_mdfrVal>"
      << "<di_mdfrVal species=\"Species_3\">15.0</di_mdfrVal>"
      << "<di_mdfrVal species=\"Species_4\">15.0</di_mdfrVal>"
      << "</di_minDbhForReproduction>"
      << "<di_nonSpatialSlopeOfLambda>"
      << "<di_nssolVal species=\"Species_4\">0</di_nssolVal>"
      << "<di_nssolVal species=\"Species_2\">0</di_nssolVal>"
      << "<di_nssolVal species=\"Species_3\">0</di_nssolVal>"
      << "</di_nonSpatialSlopeOfLambda>"
      << "<di_nonSpatialInterceptOfLambda>"
      << "<di_nsiolVal species=\"Species_4\">0</di_nsiolVal>"
      << "<di_nsiolVal species=\"Species_2\">0</di_nsiolVal>"
      << "<di_nsiolVal species=\"Species_3\">0</di_nsiolVal>"
      << "</di_nonSpatialInterceptOfLambda>"
      << "</NonSpatialDisperse1>"
      << "<DensityDependentSeedSurvival2>"
      << "<es_densDepSlope>"
      << "<es_ddsVal species=\"Species_2\">42.49</es_ddsVal>"
      << "<es_ddsVal species=\"Species_3\">3</es_ddsVal>"
      << "<es_ddsVal species=\"Species_4\">0.8</es_ddsVal>"
      << "</es_densDepSlope>"
      << "<es_densDepSteepness>"
      << "<es_ddstVal species=\"Species_2\">1.87</es_ddstVal>"
      << "<es_ddstVal species=\"Species_3\">0.1</es_ddstVal>"
      << "<es_ddstVal species=\"Species_4\">-0.3</es_ddstVal>"
      << "</es_densDepSteepness>"
      << "</DensityDependentSeedSurvival2>"
      << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteDensitySeedSurvivalXMLFile3()
/////////////////////////////////////////////////////////////////////////////
const char* WriteDensitySeedSurvivalXMLFile3()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
      << "<paramFile fileCode=\"06010101\">" << "<plot>"
      << "<timesteps>1</timesteps>"
      << "<yearsPerTimestep>5</yearsPerTimestep>"
      << "<randomSeed>1</randomSeed>"
      << "<plot_lenX>100.0</plot_lenX>"
      << "<plot_lenY>100.0</plot_lenY>"
      << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
      << "<plot_temp_C>12.88171785</plot_temp_C>"
      << "<plot_latitude>55.37</plot_latitude>"
      << "</plot>";

  WriteDensitySeedSurvivalCommonStuff(oOut);

  oOut << "<grid gridName=\"Dispersed Seeds\">"
      << "<ma_floatCodes>"
      << "<ma_floatCode label=\"seeds_0\">0</ma_floatCode>"
      << "<ma_floatCode label=\"seeds_1\">1</ma_floatCode>"
      << "<ma_floatCode label=\"seeds_2\">2</ma_floatCode>"
      << "<ma_floatCode label=\"seeds_3\">3</ma_floatCode>"
      << "</ma_floatCodes>"
      << "<ma_boolCodes>"
      << "<ma_boolCode label=\"Is Gap\">0</ma_boolCode>"
      << "</ma_boolCodes>"
      << "<ma_intCodes>"
      << "<ma_intCode label=\"count\">0</ma_intCode>"
      << "</ma_intCodes>"
      << "<ma_lengthXCells>5</ma_lengthXCells>"
      << "<ma_lengthYCells>5</ma_lengthYCells>"
      << "</grid>";

  oOut << "<behaviorList>"
      << "<behavior>"
      << "<behaviorName>NonSpatialDisperse</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>1</listPosition>"
      << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_4\" type=\"Adult\"/>"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>DensityDependentSeedSurvival</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>2</listPosition>"
      << "<applyTo species=\"Species_2\" type=\"Seed\"/>"
      << "<applyTo species=\"Species_3\" type=\"Seed\"/>"
      << "<applyTo species=\"Species_4\" type=\"Seed\"/>"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>Establishment</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>3</listPosition>"
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
      << "<di_mdfrVal species=\"Species_2\">15.0</di_mdfrVal>"
      << "<di_mdfrVal species=\"Species_3\">15.0</di_mdfrVal>"
      << "<di_mdfrVal species=\"Species_4\">15.0</di_mdfrVal>"
      << "</di_minDbhForReproduction>"
      << "<di_nonSpatialSlopeOfLambda>"
      << "<di_nssolVal species=\"Species_4\">0</di_nssolVal>"
      << "<di_nssolVal species=\"Species_2\">0</di_nssolVal>"
      << "<di_nssolVal species=\"Species_3\">0</di_nssolVal>"
      << "</di_nonSpatialSlopeOfLambda>"
      << "<di_nonSpatialInterceptOfLambda>"
      << "<di_nsiolVal species=\"Species_4\">0</di_nsiolVal>"
      << "<di_nsiolVal species=\"Species_2\">0</di_nsiolVal>"
      << "<di_nsiolVal species=\"Species_3\">0</di_nsiolVal>"
      << "</di_nonSpatialInterceptOfLambda>"
      << "</NonSpatialDisperse1>"
      << "<DensityDependentSeedSurvival2>"
      << "<es_densDepSlope>"
      << "<es_ddsVal species=\"Species_2\">0.2</es_ddsVal>"
      << "<es_ddsVal species=\"Species_3\">0.4</es_ddsVal>"
      << "<es_ddsVal species=\"Species_4\">0.8</es_ddsVal>"
      << "</es_densDepSlope>"
      << "<es_densDepSteepness>"
      << "<es_ddstVal species=\"Species_2\">-0.2</es_ddstVal>"
      << "<es_ddstVal species=\"Species_3\">-0.1</es_ddstVal>"
      << "<es_ddstVal species=\"Species_4\">-0.3</es_ddstVal>"
      << "</es_densDepSteepness>"
      << "</DensityDependentSeedSurvival2>"
      << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteDensitySeedSurvivalXMLFile4()
/////////////////////////////////////////////////////////////////////////////
const char* WriteDensitySeedSurvivalXMLFile4()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
      << "<paramFile fileCode=\"06010101\">" << "<plot>"
      << "<timesteps>1</timesteps>"
      << "<yearsPerTimestep>5</yearsPerTimestep>"
      << "<randomSeed>1</randomSeed>"
      << "<plot_lenX>500.0</plot_lenX>"
      << "<plot_lenY>100.0</plot_lenY>"
      << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
      << "<plot_temp_C>12.88171785</plot_temp_C>"
      << "<plot_latitude>55.37</plot_latitude>"
      << "</plot>";

  WriteDensitySeedSurvivalCommonStuff(oOut);

  oOut << "<behaviorList>"
      << "<behavior>"
      << "<behaviorName>NonSpatialDisperse</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>1</listPosition>"
      << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_4\" type=\"Adult\"/>"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>ConspecificTreeDensityDependentSeedSurvival</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>2</listPosition>"
      << "<applyTo species=\"Species_2\" type=\"Seed\"/>"
      << "<applyTo species=\"Species_3\" type=\"Seed\"/>"
      << "<applyTo species=\"Species_4\" type=\"Seed\"/>"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>Establishment</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>3</listPosition>"
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
      << "<di_mdfrVal species=\"Species_2\">15.0</di_mdfrVal>"
      << "<di_mdfrVal species=\"Species_3\">15.0</di_mdfrVal>"
      << "<di_mdfrVal species=\"Species_4\">15.0</di_mdfrVal>"
      << "</di_minDbhForReproduction>"
      << "<di_nonSpatialSlopeOfLambda>"
      << "<di_nssolVal species=\"Species_4\">0</di_nssolVal>"
      << "<di_nssolVal species=\"Species_2\">0</di_nssolVal>"
      << "<di_nssolVal species=\"Species_3\">0</di_nssolVal>"
      << "</di_nonSpatialSlopeOfLambda>"
      << "<di_nonSpatialInterceptOfLambda>"
      << "<di_nsiolVal species=\"Species_4\">0</di_nsiolVal>"
      << "<di_nsiolVal species=\"Species_2\">0</di_nsiolVal>"
      << "<di_nsiolVal species=\"Species_3\">0</di_nsiolVal>"
      << "</di_nonSpatialInterceptOfLambda>"
      << "</NonSpatialDisperse1>"
      << "<DensityDependentSeedSurvival2>"
      << "<es_densDepSlope>"
      << "<es_ddsVal species=\"Species_2\">0.2</es_ddsVal>"
      << "<es_ddsVal species=\"Species_3\">0.4</es_ddsVal>"
      << "<es_ddsVal species=\"Species_4\">0.8</es_ddsVal>"
      << "</es_densDepSlope>"
      << "<es_densDepSteepness>"
      << "<es_ddstVal species=\"Species_2\">-0.2</es_ddstVal>"
      << "<es_ddstVal species=\"Species_3\">-0.1</es_ddstVal>"
      << "<es_ddstVal species=\"Species_4\">-0.3</es_ddstVal>"
      << "</es_densDepSteepness>"
      << "<es_densDepMinNeighHeight>"
      << "<es_ddmnhVal species=\"Species_2\">0</es_ddmnhVal>"
      << "<es_ddmnhVal species=\"Species_3\">1.35</es_ddmnhVal>"
      << "<es_ddmnhVal species=\"Species_4\">2</es_ddmnhVal>"
      << "</es_densDepMinNeighHeight>"
      << "<es_densDepSearchRadius>8</es_densDepSearchRadius>"
      << "</DensityDependentSeedSurvival2>"
      << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteDensitySeedSurvivalCommonStuff()
/////////////////////////////////////////////////////////////////////////////
void WriteDensitySeedSurvivalCommonStuff(std::fstream &oOut) {
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
      << "<tr_stdMaxCrownRad>"
      << "<tr_smcrVal species=\"Species_1\">10</tr_smcrVal>"
      << "<tr_smcrVal species=\"Species_2\">10</tr_smcrVal>"
      << "<tr_smcrVal species=\"Species_3\">10</tr_smcrVal>"
      << "<tr_smcrVal species=\"Species_4\">10</tr_smcrVal>"
      << "</tr_stdMaxCrownRad>"
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
      << "<tr_adultLinearSlope>"
      << "<tr_alsVal species=\"Species_2\">0.96</tr_alsVal>"
      << "<tr_alsVal species=\"Species_3\">0.89</tr_alsVal>"
      << "<tr_alsVal species=\"Species_4\">0.858</tr_alsVal>"
      << "<tr_alsVal species=\"Species_1\">1.044</tr_alsVal>"
      << "</tr_adultLinearSlope>"
      << "<tr_adultLinearIntercept>"
      << "<tr_aliVal species=\"Species_2\">-0.258</tr_aliVal>"
      << "<tr_aliVal species=\"Species_3\">-0.33</tr_aliVal>"
      << "<tr_aliVal species=\"Species_4\">0.027</tr_aliVal>"
      << "<tr_aliVal species=\"Species_1\">0.015</tr_aliVal>"
      << "</tr_adultLinearIntercept>"
      << "<tr_saplingLinearSlope>"
      << "<tr_salsVal species=\"Species_2\">0.96</tr_salsVal>"
      << "<tr_salsVal species=\"Species_3\">0.89</tr_salsVal>"
      << "<tr_salsVal species=\"Species_4\">0.858</tr_salsVal>"
      << "<tr_salsVal species=\"Species_1\">1.044</tr_salsVal>"
      << "</tr_saplingLinearSlope>"
      << "<tr_saplingLinearIntercept>"
      << "<tr_saliVal species=\"Species_2\">-0.258</tr_saliVal>"
      << "<tr_saliVal species=\"Species_3\">-0.33</tr_saliVal>"
      << "<tr_saliVal species=\"Species_4\">0.027</tr_saliVal>"
      << "<tr_saliVal species=\"Species_1\">0.015</tr_saliVal>"
      << "</tr_saplingLinearIntercept>"
      << "<tr_seedlingLinearSlope>"
      << "<tr_selsVal species=\"Species_2\">0.96</tr_selsVal>"
      << "<tr_selsVal species=\"Species_3\">0.89</tr_selsVal>"
      << "<tr_selsVal species=\"Species_4\">0.858</tr_selsVal>"
      << "<tr_selsVal species=\"Species_1\">1.044</tr_selsVal>"
      << "</tr_seedlingLinearSlope>"
      << "<tr_seedlingLinearIntercept>"
      << "<tr_seliVal species=\"Species_2\">-0.258</tr_seliVal>"
      << "<tr_seliVal species=\"Species_3\">-0.33</tr_seliVal>"
      << "<tr_seliVal species=\"Species_4\">0.027</tr_seliVal>"
      << "<tr_seliVal species=\"Species_1\">0.015</tr_seliVal>"
      << "</tr_seedlingLinearIntercept>"
      << "<tr_whatSeedlingHeightDiam>"
      << "<tr_wsehdVal species=\"Species_1\">1</tr_wsehdVal>"
      << "<tr_wsehdVal species=\"Species_2\">1</tr_wsehdVal>"
      << "<tr_wsehdVal species=\"Species_3\">1</tr_wsehdVal>"
      << "<tr_wsehdVal species=\"Species_4\">1</tr_wsehdVal>"
      << "</tr_whatSeedlingHeightDiam>"
      << "<tr_whatSaplingHeightDiam>"
      << "<tr_wsahdVal species=\"Species_1\">1</tr_wsahdVal>"
      << "<tr_wsahdVal species=\"Species_2\">1</tr_wsahdVal>"
      << "<tr_wsahdVal species=\"Species_3\">1</tr_wsahdVal>"
      << "<tr_wsahdVal species=\"Species_4\">1</tr_wsahdVal>"
      << "</tr_whatSaplingHeightDiam>"
      << "<tr_whatAdultHeightDiam>"
      << "<tr_wahdVal species=\"Species_1\">1</tr_wahdVal>"
      << "<tr_wahdVal species=\"Species_2\">1</tr_wahdVal>"
      << "<tr_wahdVal species=\"Species_3\">1</tr_wahdVal>"
      << "<tr_wahdVal species=\"Species_4\">1</tr_wahdVal>"
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
