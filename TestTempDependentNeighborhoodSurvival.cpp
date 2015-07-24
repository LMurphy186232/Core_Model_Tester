//---------------------------------------------------------------------------
// TestTempDependentNeighborhoodSurvival.cpp
//---------------------------------------------------------------------------
#include "TestTempDependentNeighborhoodSurvival.h"
#include <gtest/gtest.h>
#include "SimManager.h"
#include "TreePopulation.h"
#include "Grid.h"
#include "BehaviorBase.h"
#include "Plot.h"
#include <math.h>
#include <fstream>

/////////////////////////////////////////////////////////////////////////////
// TestTempDependentNeighborhoodSurvival1()
/////////////////////////////////////////////////////////////////////////////
TEST(TempDependentNeighborhoodSurvival, TestTempDependentNeighborhoodSurvival1) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
  //Feed our file to the sim manager
  p_oSimManager->ReadFile(WriteTempDependentNeighborhoodSurvivalXMLFile(1));

  clTreePopulation *p_oPop = (clTreePopulation *) p_oSimManager->GetPopulationObject("treepopulation");
  clTreeSearch *p_oAllTrees;
  clGrid *p_oSurvGrid;
  clTree *p_oTree;
  float fDiam, fX, fY, fExpectedSurvival1, fExpectedSurvival2,
        fExpectedSurvival3, fSurvival, fTreeX, fTreeY;
  int iSpecies, i, iCellX, iCellY,
      iExpectedSpecies1, iExpectedSpecies2, iExpectedSpecies3,
      iNumSpecies1, iNumSpecies2, iNumSpecies3;

  //Create all neighbors
  fDiam = 10.5;
  iSpecies = 1;
  p_oPop->CreateTree(50, 50, iSpecies, clTreePopulation::adult, fDiam);

  fDiam = 15;
  iSpecies = 2;
  p_oPop->CreateTree(53, 52, iSpecies, clTreePopulation::adult, fDiam);

  fDiam = 26;
  iSpecies = 2;
  p_oPop->CreateTree(55, 60, iSpecies, clTreePopulation::adult, fDiam);

  fDiam = 25;
  iSpecies = 3;
  p_oPop->CreateTree(59, 50, iSpecies, clTreePopulation::adult, fDiam);

  fDiam = 30;
  iSpecies = 1;
  p_oPop->CreateTree(50, 59, iSpecies, clTreePopulation::adult, fDiam);

  fDiam = 45;
  iSpecies = 2;
  p_oPop->CreateTree(55, 55, iSpecies, clTreePopulation::adult, fDiam);

  fDiam = 15;
  iSpecies = 3;
  p_oPop->CreateTree(60, 61, iSpecies, clTreePopulation::adult, fDiam);

  fDiam = 76;
  iSpecies = 2;
  p_oPop->CreateTree(44, 60, iSpecies, clTreePopulation::adult, fDiam);


  //Now create all the neighbors that are too small or dead to compete
  fDiam = 4;
  iSpecies = 1;
  p_oPop->CreateTree(52, 52, iSpecies, clTreePopulation::sapling, fDiam);
  fDiam = 4;
  iSpecies = 2;
  p_oPop->CreateTree(53, 53, iSpecies, clTreePopulation::sapling, fDiam);
  p_oPop->CreateTree(56, 56, 0, clTreePopulation::snag, 30);


  //Create seedlings subject to survival
  //Grid cell 2, 2
  fX = 20; fY = 20;
  for (i = 0; i < 1000; i++) {
    p_oPop->CreateTree(fX, fY, 1, clTreePopulation::seedling, 0.2);
    p_oPop->CreateTree(fX, fY, 2, clTreePopulation::seedling, 0.2);
    p_oPop->CreateTree(fX, fY, 3, clTreePopulation::seedling, 0.2);
  }

  //Grid cell 5, 6
  fX = 44; fY = 52;
  for (i = 0; i < 1000; i++) {
    p_oPop->CreateTree(fX, fY, 1, clTreePopulation::seedling, 0.2);
    p_oPop->CreateTree(fX, fY, 2, clTreePopulation::seedling, 0.2);
    p_oPop->CreateTree(fX, fY, 3, clTreePopulation::seedling, 0.2);
  }

  //Grid cell 6, 5
  fX = 52; fY = 44;
  for (i = 0; i < 1000; i++) {
    p_oPop->CreateTree(fX, fY, 1, clTreePopulation::seedling, 0.2);
    p_oPop->CreateTree(fX, fY, 2, clTreePopulation::seedling, 0.2);
    p_oPop->CreateTree(fX, fY, 3, clTreePopulation::seedling, 0.2);
  }

  //Grid cell 5, 5
  fX = 44; fY = 44;
  for (i = 0; i < 1000; i++) {
    p_oPop->CreateTree(fX, fY, 1, clTreePopulation::seedling, 0.2);
    p_oPop->CreateTree(fX, fY, 2, clTreePopulation::seedling, 0.2);
    p_oPop->CreateTree(fX, fY, 3, clTreePopulation::seedling, 0.2);
  }

  //Grid cell 6, 6
  fX = 52; fY = 52;
  for (i = 0; i < 1000; i++) {
    p_oPop->CreateTree(fX, fY, 1, clTreePopulation::seedling, 0.2);
    p_oPop->CreateTree(fX, fY, 2, clTreePopulation::seedling, 0.2);
    p_oPop->CreateTree(fX, fY, 3, clTreePopulation::seedling, 0.2);
  }

  //Grid cell 7, 6
  fX = 60; fY = 52;
  for (i = 0; i < 1000; i++) {
    p_oPop->CreateTree(fX, fY, 1, clTreePopulation::seedling, 0.2);
    p_oPop->CreateTree(fX, fY, 2, clTreePopulation::seedling, 0.2);
    p_oPop->CreateTree(fX, fY, 3, clTreePopulation::seedling, 0.2);
  }

  //Grid cell 6, 7
  fX = 52; fY = 60;
  for (i = 0; i < 1000; i++) {
    p_oPop->CreateTree(fX, fY, 1, clTreePopulation::seedling, 0.2);
    p_oPop->CreateTree(fX, fY, 2, clTreePopulation::seedling, 0.2);
    p_oPop->CreateTree(fX, fY, 3, clTreePopulation::seedling, 0.2);
  }

  //Run one timestep
  p_oSimManager->RunSim(1);

  p_oSurvGrid = p_oSimManager->GetGridObject("Temperature Dependent Neighborhood Survival");

  //Check the grid values
  iCellX = 2; iCellY = 2;
  fExpectedSurvival1 = 0.518820149;
  fExpectedSurvival2 = 0.999884833;
  fExpectedSurvival3 = 0.927429343;
  p_oSurvGrid->GetValueOfCell(iCellX, iCellY, p_oSurvGrid->GetFloatDataCode("survival_1"), &fSurvival);
  EXPECT_LT(fabs(fSurvival - fExpectedSurvival1), 0.0001);
  p_oSurvGrid->GetValueOfCell(iCellX, iCellY, p_oSurvGrid->GetFloatDataCode("survival_2"), &fSurvival);
  EXPECT_LT(fabs(fSurvival - fExpectedSurvival2), 0.0001);
  p_oSurvGrid->GetValueOfCell(iCellX, iCellY, p_oSurvGrid->GetFloatDataCode("survival_3"), &fSurvival);
  EXPECT_LT(fabs(fSurvival - fExpectedSurvival3), 0.0001);

  iCellX = 5; iCellY = 6;
  fExpectedSurvival1 = 0.472174739;
  fExpectedSurvival2 = 0.310631411;
  fExpectedSurvival3 = 0.056320859;
  p_oSurvGrid->GetValueOfCell(iCellX, iCellY, p_oSurvGrid->GetFloatDataCode("survival_1"), &fSurvival);
  EXPECT_LT(fabs(fSurvival - fExpectedSurvival1), 0.0001);
  p_oSurvGrid->GetValueOfCell(iCellX, iCellY, p_oSurvGrid->GetFloatDataCode("survival_2"), &fSurvival);
  EXPECT_LT(fabs(fSurvival - fExpectedSurvival2), 0.0001);
  p_oSurvGrid->GetValueOfCell(iCellX, iCellY, p_oSurvGrid->GetFloatDataCode("survival_3"), &fSurvival);
  EXPECT_LT(fabs(fSurvival - fExpectedSurvival3), 0.0001);

  iCellX = 6; iCellY = 5;
  fExpectedSurvival1 = 0.480263137;
  fExpectedSurvival2 = 0.82247294;
  fExpectedSurvival3 = 0.6771687;
  p_oSurvGrid->GetValueOfCell(iCellX, iCellY, p_oSurvGrid->GetFloatDataCode("survival_1"), &fSurvival);
  EXPECT_LT(fabs(fSurvival - fExpectedSurvival1), 0.0001);
  p_oSurvGrid->GetValueOfCell(iCellX, iCellY, p_oSurvGrid->GetFloatDataCode("survival_2"), &fSurvival);
  EXPECT_LT(fabs(fSurvival - fExpectedSurvival2), 0.0001);
  p_oSurvGrid->GetValueOfCell(iCellX, iCellY, p_oSurvGrid->GetFloatDataCode("survival_3"), &fSurvival);
  EXPECT_LT(fabs(fSurvival - fExpectedSurvival3), 0.0001);

  iCellX = 5; iCellY = 5;
  fExpectedSurvival1 = 0.487535703;
  fExpectedSurvival2 = 0.97242682;
  fExpectedSurvival3 = 0.900847177;
  p_oSurvGrid->GetValueOfCell(iCellX, iCellY, p_oSurvGrid->GetFloatDataCode("survival_1"), &fSurvival);
  EXPECT_LT(fabs(fSurvival - fExpectedSurvival1), 0.0001);
  p_oSurvGrid->GetValueOfCell(iCellX, iCellY, p_oSurvGrid->GetFloatDataCode("survival_2"), &fSurvival);
  EXPECT_LT(fabs(fSurvival - fExpectedSurvival2), 0.0001);
  p_oSurvGrid->GetValueOfCell(iCellX, iCellY, p_oSurvGrid->GetFloatDataCode("survival_3"), &fSurvival);
  EXPECT_LT(fabs(fSurvival - fExpectedSurvival3), 0.0001);

  iCellX = 6; iCellY = 6;
  fExpectedSurvival1 = 0.474050326;
  fExpectedSurvival2 = 0.452009181;
  fExpectedSurvival3 = 0.161847605;
  p_oSurvGrid->GetValueOfCell(iCellX, iCellY, p_oSurvGrid->GetFloatDataCode("survival_1"), &fSurvival);
  EXPECT_LT(fabs(fSurvival - fExpectedSurvival1), 0.0001);
  p_oSurvGrid->GetValueOfCell(iCellX, iCellY, p_oSurvGrid->GetFloatDataCode("survival_2"), &fSurvival);
  EXPECT_LT(fabs(fSurvival - fExpectedSurvival2), 0.0001);
  p_oSurvGrid->GetValueOfCell(iCellX, iCellY, p_oSurvGrid->GetFloatDataCode("survival_3"), &fSurvival);
  EXPECT_LT(fabs(fSurvival - fExpectedSurvival3), 0.0001);

  iCellX = 7; iCellY = 6;
  fExpectedSurvival1 = 0.474851666;
  fExpectedSurvival2 = 0.511756301;
  fExpectedSurvival3 = 0.224583636;
  p_oSurvGrid->GetValueOfCell(iCellX, iCellY, p_oSurvGrid->GetFloatDataCode("survival_1"), &fSurvival);
  EXPECT_LT(fabs(fSurvival - fExpectedSurvival1), 0.0001);
  p_oSurvGrid->GetValueOfCell(iCellX, iCellY, p_oSurvGrid->GetFloatDataCode("survival_2"), &fSurvival);
  EXPECT_LT(fabs(fSurvival - fExpectedSurvival2), 0.0001);
  p_oSurvGrid->GetValueOfCell(iCellX, iCellY, p_oSurvGrid->GetFloatDataCode("survival_3"), &fSurvival);
  EXPECT_LT(fabs(fSurvival - fExpectedSurvival3), 0.0001);

  iCellX = 6; iCellY = 7;
  fExpectedSurvival1 = 0.470649752;
  fExpectedSurvival2 = 0.205103351;
  fExpectedSurvival3 = 0.015977867;
  p_oSurvGrid->GetValueOfCell(iCellX, iCellY, p_oSurvGrid->GetFloatDataCode("survival_1"), &fSurvival);
  EXPECT_LT(fabs(fSurvival - fExpectedSurvival1), 0.0001);
  p_oSurvGrid->GetValueOfCell(iCellX, iCellY, p_oSurvGrid->GetFloatDataCode("survival_2"), &fSurvival);
  EXPECT_LT(fabs(fSurvival - fExpectedSurvival2), 0.0001);
  p_oSurvGrid->GetValueOfCell(iCellX, iCellY, p_oSurvGrid->GetFloatDataCode("survival_3"), &fSurvival);
  EXPECT_LT(fabs(fSurvival - fExpectedSurvival3), 0.0001);

  //Count the seedlings in each grid cell
  p_oAllTrees = p_oPop->Find("type=1");

  //Grid cell 2, 2
  iExpectedSpecies1 = 518;
  iExpectedSpecies2 = 999;
  iExpectedSpecies3 = 927;
  iNumSpecies1 = 0; iNumSpecies2 = 0; iNumSpecies3 = 0;
  fX = 20; fY = 20;
  p_oTree = p_oAllTrees->NextTree();
  while (p_oTree) {
    p_oTree->GetValue(p_oPop->GetXCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTreeX);
    p_oTree->GetValue(p_oPop->GetYCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTreeY);
    if (fabs(fX - fTreeX) < 1 && fabs(fY - fTreeY) < 1) {
      if (1 == p_oTree->GetSpecies()) iNumSpecies1++;
      else if (2 == p_oTree->GetSpecies()) iNumSpecies2++;
      else iNumSpecies3++;
    }
    p_oTree = p_oAllTrees->NextTree();
  }
  EXPECT_LT(fabs(iNumSpecies1 - iExpectedSpecies1)/iExpectedSpecies1, 0.1);
  EXPECT_LT(fabs(iNumSpecies2 - iExpectedSpecies2)/iExpectedSpecies2, 0.1);
  EXPECT_LT(fabs(iNumSpecies3 - iExpectedSpecies3)/iExpectedSpecies3, 0.1);
  p_oAllTrees->StartOver();

  //Grid cell 5, 6
  iExpectedSpecies1 = 472;
  iExpectedSpecies2 = 310;
  iExpectedSpecies3 = 56;
  iNumSpecies1 = 0; iNumSpecies2 = 0; iNumSpecies3 = 0;
  fX = 44; fY = 52;
  p_oTree = p_oAllTrees->NextTree();
  while (p_oTree) {
    p_oTree->GetValue(p_oPop->GetXCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTreeX);
    p_oTree->GetValue(p_oPop->GetYCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTreeY);
    if (fabs(fX - fTreeX) < 1 && fabs(fY - fTreeY) < 1) {
      if (1 == p_oTree->GetSpecies()) iNumSpecies1++;
      else if (2 == p_oTree->GetSpecies()) iNumSpecies2++;
      else iNumSpecies3++;
    }
    p_oTree = p_oAllTrees->NextTree();
  }
  EXPECT_LT(fabs(iNumSpecies1 - iExpectedSpecies1)/iExpectedSpecies1, 0.1);
  EXPECT_LT(fabs(iNumSpecies2 - iExpectedSpecies2)/iExpectedSpecies2, 0.1);
  EXPECT_LT(fabs(iNumSpecies3 - iExpectedSpecies3)/iExpectedSpecies3, 0.2);
  p_oAllTrees->StartOver();

  //Grid cell 6, 5
  iExpectedSpecies1 = 480;
  iExpectedSpecies2 = 822;
  iExpectedSpecies3 = 677;
  iNumSpecies1 = 0; iNumSpecies2 = 0; iNumSpecies3 = 0;
  fX = 52; fY = 44;
  p_oTree = p_oAllTrees->NextTree();
  while (p_oTree) {
    p_oTree->GetValue(p_oPop->GetXCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTreeX);
    p_oTree->GetValue(p_oPop->GetYCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTreeY);
    if (fabs(fX - fTreeX) < 1 && fabs(fY - fTreeY) < 1) {
      if (1 == p_oTree->GetSpecies()) iNumSpecies1++;
      else if (2 == p_oTree->GetSpecies()) iNumSpecies2++;
      else iNumSpecies3++;
    }
    p_oTree = p_oAllTrees->NextTree();
  }
  EXPECT_LT(fabs(iNumSpecies1 - iExpectedSpecies1)/iExpectedSpecies1, 0.1);
  EXPECT_LT(fabs(iNumSpecies2 - iExpectedSpecies2)/iExpectedSpecies2, 0.1);
  EXPECT_LT(fabs(iNumSpecies3 - iExpectedSpecies3)/iExpectedSpecies3, 0.1);
  p_oAllTrees->StartOver();

  //Grid cell 5, 5
  iExpectedSpecies1 = 487;
  iExpectedSpecies2 = 972;
  iExpectedSpecies3 = 900;
  iNumSpecies1 = 0; iNumSpecies2 = 0; iNumSpecies3 = 0;
  fX = 44; fY = 44;
  p_oTree = p_oAllTrees->NextTree();
  while (p_oTree) {
    p_oTree->GetValue(p_oPop->GetXCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTreeX);
    p_oTree->GetValue(p_oPop->GetYCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTreeY);
    if (fabs(fX - fTreeX) < 1 && fabs(fY - fTreeY) < 1) {
      if (1 == p_oTree->GetSpecies()) iNumSpecies1++;
      else if (2 == p_oTree->GetSpecies()) iNumSpecies2++;
      else iNumSpecies3++;
    }
    p_oTree = p_oAllTrees->NextTree();
  }
  EXPECT_LT(fabs(iNumSpecies1 - iExpectedSpecies1)/iExpectedSpecies1, 0.1);
  EXPECT_LT(fabs(iNumSpecies2 - iExpectedSpecies2)/iExpectedSpecies2, 0.1);
  EXPECT_LT(fabs(iNumSpecies3 - iExpectedSpecies3)/iExpectedSpecies3, 0.1);
  p_oAllTrees->StartOver();

  //Grid cell 6, 6
  iExpectedSpecies1 = 474;
  iExpectedSpecies2 = 452;
  iExpectedSpecies3 = 161;
  iNumSpecies1 = 0; iNumSpecies2 = 0; iNumSpecies3 = 0;
  fX = 52; fY = 52;
  p_oTree = p_oAllTrees->NextTree();
  while (p_oTree) {
    p_oTree->GetValue(p_oPop->GetXCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTreeX);
    p_oTree->GetValue(p_oPop->GetYCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTreeY);
    if (fabs(fX - fTreeX) < 1 && fabs(fY - fTreeY) < 1) {
      if (1 == p_oTree->GetSpecies()) iNumSpecies1++;
      else if (2 == p_oTree->GetSpecies()) iNumSpecies2++;
      else iNumSpecies3++;
    }
    p_oTree = p_oAllTrees->NextTree();
  }
  EXPECT_LT(fabs(iNumSpecies1 - iExpectedSpecies1)/iExpectedSpecies1, 0.1);
  EXPECT_LT(fabs(iNumSpecies2 - iExpectedSpecies2)/iExpectedSpecies2, 0.1);
  EXPECT_LT(fabs(iNumSpecies3 - iExpectedSpecies3)/iExpectedSpecies3, 0.1);
  p_oAllTrees->StartOver();

  //Grid cell 7, 6
  iExpectedSpecies1 = 474;
  iExpectedSpecies2 = 511;
  iExpectedSpecies3 = 224;
  iNumSpecies1 = 0; iNumSpecies2 = 0; iNumSpecies3 = 0;
  fX = 60; fY = 52;
  p_oTree = p_oAllTrees->NextTree();
  while (p_oTree) {
    p_oTree->GetValue(p_oPop->GetXCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTreeX);
    p_oTree->GetValue(p_oPop->GetYCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTreeY);
    if (fabs(fX - fTreeX) < 1 && fabs(fY - fTreeY) < 1) {
      if (1 == p_oTree->GetSpecies()) iNumSpecies1++;
      else if (2 == p_oTree->GetSpecies()) iNumSpecies2++;
      else iNumSpecies3++;
    }
    p_oTree = p_oAllTrees->NextTree();
  }
  EXPECT_LT(fabs(iNumSpecies1 - iExpectedSpecies1)/iExpectedSpecies1, 0.1);
  EXPECT_LT(fabs(iNumSpecies2 - iExpectedSpecies2)/iExpectedSpecies2, 0.1);
  EXPECT_LT(fabs(iNumSpecies3 - iExpectedSpecies3)/iExpectedSpecies3, 0.1);
  p_oAllTrees->StartOver();

  //Grid cell 6, 7
  iExpectedSpecies1 = 470;
  iExpectedSpecies2 = 205;
  iExpectedSpecies3 = 15;
  iNumSpecies1 = 0; iNumSpecies2 = 0; iNumSpecies3 = 0;
  fX = 52; fY = 60;
  p_oTree = p_oAllTrees->NextTree();
  while (p_oTree) {
    p_oTree->GetValue(p_oPop->GetXCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTreeX);
    p_oTree->GetValue(p_oPop->GetYCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTreeY);
    if (fabs(fX - fTreeX) < 1 && fabs(fY - fTreeY) < 1) {
      if (1 == p_oTree->GetSpecies()) iNumSpecies1++;
      else if (2 == p_oTree->GetSpecies()) iNumSpecies2++;
      else iNumSpecies3++;
    }
    p_oTree = p_oAllTrees->NextTree();
  }
  EXPECT_LT(fabs(iNumSpecies1 - iExpectedSpecies1)/iExpectedSpecies1, 0.1);
  EXPECT_LT(fabs(iNumSpecies2 - iExpectedSpecies2)/iExpectedSpecies2, 0.1);
  EXPECT_TRUE(iNumSpecies3 > 5 && iNumSpecies3 < 30);
  p_oAllTrees->StartOver();


  //Update temp, recharge the seedling pool, run again
  p_oTree = p_oAllTrees->NextTree();
  while (p_oTree) {
    p_oPop->KillTree(p_oTree, remove_tree);
    p_oTree = p_oAllTrees->NextTree();
  }
  clPlot *p_oPlot = p_oSimManager->GetPlotObject();
  p_oPlot->SetMeanAnnualTemp(20);

  //Grid cell 2, 2
  fX = 20; fY = 20;
  for (i = 0; i < 1000; i++) {
    p_oPop->CreateTree(fX, fY, 1, clTreePopulation::seedling, 0.2);
    p_oPop->CreateTree(fX, fY, 2, clTreePopulation::seedling, 0.2);
    p_oPop->CreateTree(fX, fY, 3, clTreePopulation::seedling, 0.2);
  }

  //Grid cell 5, 6
  fX = 44; fY = 52;
  for (i = 0; i < 1000; i++) {
    p_oPop->CreateTree(fX, fY, 1, clTreePopulation::seedling, 0.2);
    p_oPop->CreateTree(fX, fY, 2, clTreePopulation::seedling, 0.2);
    p_oPop->CreateTree(fX, fY, 3, clTreePopulation::seedling, 0.2);
  }

  //Grid cell 6, 5
  fX = 52; fY = 44;
  for (i = 0; i < 1000; i++) {
    p_oPop->CreateTree(fX, fY, 1, clTreePopulation::seedling, 0.2);
    p_oPop->CreateTree(fX, fY, 2, clTreePopulation::seedling, 0.2);
    p_oPop->CreateTree(fX, fY, 3, clTreePopulation::seedling, 0.2);
  }

  //Grid cell 5, 5
  fX = 44; fY = 44;
  for (i = 0; i < 1000; i++) {
    p_oPop->CreateTree(fX, fY, 1, clTreePopulation::seedling, 0.2);
    p_oPop->CreateTree(fX, fY, 2, clTreePopulation::seedling, 0.2);
    p_oPop->CreateTree(fX, fY, 3, clTreePopulation::seedling, 0.2);
  }

  //Grid cell 6, 6
  fX = 52; fY = 52;
  for (i = 0; i < 1000; i++) {
    p_oPop->CreateTree(fX, fY, 1, clTreePopulation::seedling, 0.2);
    p_oPop->CreateTree(fX, fY, 2, clTreePopulation::seedling, 0.2);
    p_oPop->CreateTree(fX, fY, 3, clTreePopulation::seedling, 0.2);
  }

  //Grid cell 7, 6
  fX = 60; fY = 52;
  for (i = 0; i < 1000; i++) {
    p_oPop->CreateTree(fX, fY, 1, clTreePopulation::seedling, 0.2);
    p_oPop->CreateTree(fX, fY, 2, clTreePopulation::seedling, 0.2);
    p_oPop->CreateTree(fX, fY, 3, clTreePopulation::seedling, 0.2);
  }

  //Grid cell 6, 7
  fX = 52; fY = 60;
  for (i = 0; i < 1000; i++) {
    p_oPop->CreateTree(fX, fY, 1, clTreePopulation::seedling, 0.2);
    p_oPop->CreateTree(fX, fY, 2, clTreePopulation::seedling, 0.2);
    p_oPop->CreateTree(fX, fY, 3, clTreePopulation::seedling, 0.2);
  }

  p_oSimManager->RunSim(1);

  //Time step 2
  //Check the grid values
  iCellX = 2; iCellY = 2;
  fExpectedSurvival1 = 0.092855849;
  fExpectedSurvival2 = 0.999358515;
  fExpectedSurvival3 = 0.546074427;
  p_oSurvGrid->GetValueOfCell(iCellX, iCellY, p_oSurvGrid->GetFloatDataCode("survival_1"), &fSurvival);
  EXPECT_LT(fabs(fSurvival - fExpectedSurvival1), 0.0001);
  p_oSurvGrid->GetValueOfCell(iCellX, iCellY, p_oSurvGrid->GetFloatDataCode("survival_2"), &fSurvival);
  EXPECT_LT(fabs(fSurvival - fExpectedSurvival2), 0.0001);
  p_oSurvGrid->GetValueOfCell(iCellX, iCellY, p_oSurvGrid->GetFloatDataCode("survival_3"), &fSurvival);
  EXPECT_LT(fabs(fSurvival - fExpectedSurvival3), 0.0001);

  iCellX = 5; iCellY = 6;
  fExpectedSurvival1 = 0.084507485;
  fExpectedSurvival2 = 0.310467901;
  fExpectedSurvival3 = 0.033161967;
  p_oSurvGrid->GetValueOfCell(iCellX, iCellY, p_oSurvGrid->GetFloatDataCode("survival_1"), &fSurvival);
  EXPECT_LT(fabs(fSurvival - fExpectedSurvival1), 0.0001);
  p_oSurvGrid->GetValueOfCell(iCellX, iCellY, p_oSurvGrid->GetFloatDataCode("survival_2"), &fSurvival);
  EXPECT_LT(fabs(fSurvival - fExpectedSurvival2), 0.0001);
  p_oSurvGrid->GetValueOfCell(iCellX, iCellY, p_oSurvGrid->GetFloatDataCode("survival_3"), &fSurvival);
  EXPECT_LT(fabs(fSurvival - fExpectedSurvival3), 0.0001);

  iCellX = 6; iCellY = 5;
  fExpectedSurvival1 = 0.085955106;
  fExpectedSurvival2 = 0.822040007;
  fExpectedSurvival3 = 0.398719873;
  p_oSurvGrid->GetValueOfCell(iCellX, iCellY, p_oSurvGrid->GetFloatDataCode("survival_1"), &fSurvival);
  EXPECT_LT(fabs(fSurvival - fExpectedSurvival1), 0.0001);
  p_oSurvGrid->GetValueOfCell(iCellX, iCellY, p_oSurvGrid->GetFloatDataCode("survival_2"), &fSurvival);
  EXPECT_LT(fabs(fSurvival - fExpectedSurvival2), 0.0001);
  p_oSurvGrid->GetValueOfCell(iCellX, iCellY, p_oSurvGrid->GetFloatDataCode("survival_3"), &fSurvival);
  EXPECT_LT(fabs(fSurvival - fExpectedSurvival3), 0.0001);

  iCellX = 5; iCellY = 5;
  fExpectedSurvival1 = 0.087256714;
  fExpectedSurvival2 = 0.971914955;
  fExpectedSurvival3 = 0.530422732;
  p_oSurvGrid->GetValueOfCell(iCellX, iCellY, p_oSurvGrid->GetFloatDataCode("survival_1"), &fSurvival);
  EXPECT_LT(fabs(fSurvival - fExpectedSurvival1), 0.0001);
  p_oSurvGrid->GetValueOfCell(iCellX, iCellY, p_oSurvGrid->GetFloatDataCode("survival_2"), &fSurvival);
  EXPECT_LT(fabs(fSurvival - fExpectedSurvival2), 0.0001);
  p_oSurvGrid->GetValueOfCell(iCellX, iCellY, p_oSurvGrid->GetFloatDataCode("survival_3"), &fSurvival);
  EXPECT_LT(fabs(fSurvival - fExpectedSurvival3), 0.0001);

  iCellX = 6; iCellY = 6;
  fExpectedSurvival1 = 0.084843168;
  fExpectedSurvival2 = 0.451771253;
  fExpectedSurvival3 = 0.095296573;
  p_oSurvGrid->GetValueOfCell(iCellX, iCellY, p_oSurvGrid->GetFloatDataCode("survival_1"), &fSurvival);
  EXPECT_LT(fabs(fSurvival - fExpectedSurvival1), 0.0001);
  p_oSurvGrid->GetValueOfCell(iCellX, iCellY, p_oSurvGrid->GetFloatDataCode("survival_2"), &fSurvival);
  EXPECT_LT(fabs(fSurvival - fExpectedSurvival2), 0.0001);
  p_oSurvGrid->GetValueOfCell(iCellX, iCellY, p_oSurvGrid->GetFloatDataCode("survival_3"), &fSurvival);
  EXPECT_LT(fabs(fSurvival - fExpectedSurvival3), 0.0001);

  iCellX = 7; iCellY = 6;
  fExpectedSurvival1 = 0.084986588;
  fExpectedSurvival2 = 0.511486923;
  fExpectedSurvival3 = 0.132235821;
  p_oSurvGrid->GetValueOfCell(iCellX, iCellY, p_oSurvGrid->GetFloatDataCode("survival_1"), &fSurvival);
  EXPECT_LT(fabs(fSurvival - fExpectedSurvival1), 0.0001);
  p_oSurvGrid->GetValueOfCell(iCellX, iCellY, p_oSurvGrid->GetFloatDataCode("survival_2"), &fSurvival);
  EXPECT_LT(fabs(fSurvival - fExpectedSurvival2), 0.0001);
  p_oSurvGrid->GetValueOfCell(iCellX, iCellY, p_oSurvGrid->GetFloatDataCode("survival_3"), &fSurvival);
  EXPECT_LT(fabs(fSurvival - fExpectedSurvival3), 0.0001);

  iCellX = 6; iCellY = 7;
  fExpectedSurvival1 = 0.084234551;
  fExpectedSurvival2 = 0.204995389;
  fExpectedSurvival3 = 0.009407837;
  p_oSurvGrid->GetValueOfCell(iCellX, iCellY, p_oSurvGrid->GetFloatDataCode("survival_1"), &fSurvival);
  EXPECT_LT(fabs(fSurvival - fExpectedSurvival1), 0.0001);
  p_oSurvGrid->GetValueOfCell(iCellX, iCellY, p_oSurvGrid->GetFloatDataCode("survival_2"), &fSurvival);
  EXPECT_LT(fabs(fSurvival - fExpectedSurvival2), 0.0001);
  p_oSurvGrid->GetValueOfCell(iCellX, iCellY, p_oSurvGrid->GetFloatDataCode("survival_3"), &fSurvival);
  EXPECT_LT(fabs(fSurvival - fExpectedSurvival3), 0.0001);

  //Count the seedlings in each grid cell
  p_oAllTrees = p_oPop->Find("type=1");

  //Grid cell 2, 2
  iExpectedSpecies1 = 92;
  iExpectedSpecies2 = 999;
  iExpectedSpecies3 = 546;
  iNumSpecies1 = 0; iNumSpecies2 = 0; iNumSpecies3 = 0;
  fX = 20; fY = 20;
  p_oTree = p_oAllTrees->NextTree();
  while (p_oTree) {
    p_oTree->GetValue(p_oPop->GetXCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTreeX);
    p_oTree->GetValue(p_oPop->GetYCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTreeY);
    if (fabs(fX - fTreeX) < 1 && fabs(fY - fTreeY) < 1) {
      if (1 == p_oTree->GetSpecies()) iNumSpecies1++;
      else if (2 == p_oTree->GetSpecies()) iNumSpecies2++;
      else iNumSpecies3++;
    }
    p_oTree = p_oAllTrees->NextTree();
  }
  EXPECT_LT(fabs(iNumSpecies1 - iExpectedSpecies1)/iExpectedSpecies1, 0.2);
  EXPECT_LT(fabs(iNumSpecies2 - iExpectedSpecies2)/iExpectedSpecies2, 0.1);
  EXPECT_LT(fabs(iNumSpecies3 - iExpectedSpecies3)/iExpectedSpecies3, 0.1);
  p_oAllTrees->StartOver();

  //Grid cell 5, 6
  iExpectedSpecies1 = 84;
  iExpectedSpecies2 = 310;
  iExpectedSpecies3 = 33;
  iNumSpecies1 = 0; iNumSpecies2 = 0; iNumSpecies3 = 0;
  fX = 44; fY = 52;
  p_oTree = p_oAllTrees->NextTree();
  while (p_oTree) {
    p_oTree->GetValue(p_oPop->GetXCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTreeX);
    p_oTree->GetValue(p_oPop->GetYCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTreeY);
    if (fabs(fX - fTreeX) < 1 && fabs(fY - fTreeY) < 1) {
      if (1 == p_oTree->GetSpecies()) iNumSpecies1++;
      else if (2 == p_oTree->GetSpecies()) iNumSpecies2++;
      else iNumSpecies3++;
    }
    p_oTree = p_oAllTrees->NextTree();
  }
  EXPECT_LT(fabs(iNumSpecies1 - iExpectedSpecies1)/iExpectedSpecies1, 0.2);
  EXPECT_LT(fabs(iNumSpecies2 - iExpectedSpecies2)/iExpectedSpecies2, 0.1);
  EXPECT_TRUE(iNumSpecies3 > 20 && iNumSpecies3 < 45);
  p_oAllTrees->StartOver();

  //Grid cell 6, 5
  iExpectedSpecies1 = 85;
  iExpectedSpecies2 = 822;
  iExpectedSpecies3 = 398;
  iNumSpecies1 = 0; iNumSpecies2 = 0; iNumSpecies3 = 0;
  fX = 52; fY = 44;
  p_oTree = p_oAllTrees->NextTree();
  while (p_oTree) {
    p_oTree->GetValue(p_oPop->GetXCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTreeX);
    p_oTree->GetValue(p_oPop->GetYCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTreeY);
    if (fabs(fX - fTreeX) < 1 && fabs(fY - fTreeY) < 1) {
      if (1 == p_oTree->GetSpecies()) iNumSpecies1++;
      else if (2 == p_oTree->GetSpecies()) iNumSpecies2++;
      else iNumSpecies3++;
    }
    p_oTree = p_oAllTrees->NextTree();
  }
  EXPECT_LT(fabs(iNumSpecies1 - iExpectedSpecies1)/iExpectedSpecies1, 0.2);
  EXPECT_LT(fabs(iNumSpecies2 - iExpectedSpecies2)/iExpectedSpecies2, 0.1);
  EXPECT_LT(fabs(iNumSpecies3 - iExpectedSpecies3)/iExpectedSpecies3, 0.1);
  p_oAllTrees->StartOver();

  //Grid cell 5, 5
  iExpectedSpecies1 = 87;
  iExpectedSpecies2 = 971;
  iExpectedSpecies3 = 530;
  iNumSpecies1 = 0; iNumSpecies2 = 0; iNumSpecies3 = 0;
  fX = 44; fY = 44;
  p_oTree = p_oAllTrees->NextTree();
  while (p_oTree) {
    p_oTree->GetValue(p_oPop->GetXCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTreeX);
    p_oTree->GetValue(p_oPop->GetYCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTreeY);
    if (fabs(fX - fTreeX) < 1 && fabs(fY - fTreeY) < 1) {
      if (1 == p_oTree->GetSpecies()) iNumSpecies1++;
      else if (2 == p_oTree->GetSpecies()) iNumSpecies2++;
      else iNumSpecies3++;
    }
    p_oTree = p_oAllTrees->NextTree();
  }
  EXPECT_LT(fabs(iNumSpecies1 - iExpectedSpecies1)/iExpectedSpecies1, 0.2);
  EXPECT_LT(fabs(iNumSpecies2 - iExpectedSpecies2)/iExpectedSpecies2, 0.1);
  EXPECT_LT(fabs(iNumSpecies3 - iExpectedSpecies3)/iExpectedSpecies3, 0.1);
  p_oAllTrees->StartOver();

  //Grid cell 6, 6
  iExpectedSpecies1 = 84;
  iExpectedSpecies2 = 451;
  iExpectedSpecies3 = 95;
  iNumSpecies1 = 0; iNumSpecies2 = 0; iNumSpecies3 = 0;
  fX = 52; fY = 52;
  p_oTree = p_oAllTrees->NextTree();
  while (p_oTree) {
    p_oTree->GetValue(p_oPop->GetXCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTreeX);
    p_oTree->GetValue(p_oPop->GetYCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTreeY);
    if (fabs(fX - fTreeX) < 1 && fabs(fY - fTreeY) < 1) {
      if (1 == p_oTree->GetSpecies()) iNumSpecies1++;
      else if (2 == p_oTree->GetSpecies()) iNumSpecies2++;
      else iNumSpecies3++;
    }
    p_oTree = p_oAllTrees->NextTree();
  }
  EXPECT_LT(fabs(iNumSpecies1 - iExpectedSpecies1)/iExpectedSpecies1, 0.2);
  EXPECT_LT(fabs(iNumSpecies2 - iExpectedSpecies2)/iExpectedSpecies2, 0.1);
  EXPECT_LT(fabs(iNumSpecies3 - iExpectedSpecies3)/iExpectedSpecies3, 0.1);
  p_oAllTrees->StartOver();

  //Grid cell 7, 6
  iExpectedSpecies1 = 84;
  iExpectedSpecies2 = 511;
  iExpectedSpecies3 = 132;
  iNumSpecies1 = 0; iNumSpecies2 = 0; iNumSpecies3 = 0;
  fX = 60; fY = 52;
  p_oTree = p_oAllTrees->NextTree();
  while (p_oTree) {
    p_oTree->GetValue(p_oPop->GetXCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTreeX);
    p_oTree->GetValue(p_oPop->GetYCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTreeY);
    if (fabs(fX - fTreeX) < 1 && fabs(fY - fTreeY) < 1) {
      if (1 == p_oTree->GetSpecies()) iNumSpecies1++;
      else if (2 == p_oTree->GetSpecies()) iNumSpecies2++;
      else iNumSpecies3++;
    }
    p_oTree = p_oAllTrees->NextTree();
  }
  EXPECT_LT(fabs(iNumSpecies1 - iExpectedSpecies1)/iExpectedSpecies1, 0.2);
  EXPECT_LT(fabs(iNumSpecies2 - iExpectedSpecies2)/iExpectedSpecies2, 0.1);
  EXPECT_LT(fabs(iNumSpecies3 - iExpectedSpecies3)/iExpectedSpecies3, 0.1);
  p_oAllTrees->StartOver();

  //Grid cell 6, 7
  iExpectedSpecies1 = 84;
  iExpectedSpecies2 = 204;
  iExpectedSpecies3 = 9;
  iNumSpecies1 = 0; iNumSpecies2 = 0; iNumSpecies3 = 0;
  fX = 52; fY = 60;
  p_oTree = p_oAllTrees->NextTree();
  while (p_oTree) {
    p_oTree->GetValue(p_oPop->GetXCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTreeX);
    p_oTree->GetValue(p_oPop->GetYCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTreeY);
    if (fabs(fX - fTreeX) < 1 && fabs(fY - fTreeY) < 1) {
      if (1 == p_oTree->GetSpecies()) iNumSpecies1++;
      else if (2 == p_oTree->GetSpecies()) iNumSpecies2++;
      else iNumSpecies3++;
    }
    p_oTree = p_oAllTrees->NextTree();
  }
  EXPECT_LT(fabs(iNumSpecies1 - iExpectedSpecies1)/iExpectedSpecies1, 0.2);
  EXPECT_LT(fabs(iNumSpecies2 - iExpectedSpecies2)/iExpectedSpecies2, 0.1);
  EXPECT_LT(iNumSpecies3, 20);

  delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}


/////////////////////////////////////////////////////////////////////////////
// TestTempDependentNeighborhoodSurvival2()
/////////////////////////////////////////////////////////////////////////////
TEST(TempDependentNeighborhoodSurvival, TestTempDependentNeighborhoodSurvival2) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
try {
  //Feed our file to the sim manager
  p_oSimManager->ReadFile(WriteTempDependentNeighborhoodSurvivalXMLFile(3));

  clTreePopulation *p_oPop = (clTreePopulation *) p_oSimManager->GetPopulationObject("treepopulation");
  clTreeSearch *p_oAllTrees;
  clGrid *p_oSurvGrid;
  clTree *p_oTree;
  float fDiam, fX, fY, fExpectedSurvival1, fExpectedSurvival2,
        fExpectedSurvival3, fSurvival, fTreeX, fTreeY;
  int iSpecies, i, iCellX, iCellY,
      iExpectedSpecies1, iExpectedSpecies2, iExpectedSpecies3,
      iNumSpecies1, iNumSpecies2, iNumSpecies3;

  //Create all neighbors
  fDiam = 10.5;
  iSpecies = 1;
  p_oPop->CreateTree(50, 50, iSpecies, clTreePopulation::adult, fDiam);

  fDiam = 15;
  iSpecies = 2;
  p_oPop->CreateTree(53, 52, iSpecies, clTreePopulation::adult, fDiam);

  fDiam = 26;
  iSpecies = 2;
  p_oPop->CreateTree(55, 60, iSpecies, clTreePopulation::adult, fDiam);

  fDiam = 25;
  iSpecies = 3;
  p_oPop->CreateTree(59, 50, iSpecies, clTreePopulation::adult, fDiam);

  fDiam = 30;
  iSpecies = 1;
  p_oPop->CreateTree(50, 59, iSpecies, clTreePopulation::adult, fDiam);

  fDiam = 45;
  iSpecies = 2;
  p_oPop->CreateTree(55, 55, iSpecies, clTreePopulation::adult, fDiam);

  fDiam = 15;
  iSpecies = 3;
  p_oPop->CreateTree(60, 61, iSpecies, clTreePopulation::adult, fDiam);

  fDiam = 76;
  iSpecies = 2;
  p_oPop->CreateTree(44, 60, iSpecies, clTreePopulation::adult, fDiam);


  //Now create all the neighbors that are too small or dead to compete
  fDiam = 4;
  iSpecies = 1;
  p_oPop->CreateTree(52, 52, iSpecies, clTreePopulation::sapling, fDiam);
  fDiam = 4;
  iSpecies = 2;
  p_oPop->CreateTree(53, 53, iSpecies, clTreePopulation::sapling, fDiam);
  p_oPop->CreateTree(56, 56, 0, clTreePopulation::snag, 30);


  //Create seedlings subject to survival
  //Grid cell 2, 2
  fX = 20; fY = 20;
  for (i = 0; i < 1000; i++) {
    p_oPop->CreateTree(fX, fY, 1, clTreePopulation::seedling, 0.2);
    p_oPop->CreateTree(fX, fY, 2, clTreePopulation::seedling, 0.2);
    p_oPop->CreateTree(fX, fY, 3, clTreePopulation::seedling, 0.2);
  }

  //Grid cell 5, 6
  fX = 44; fY = 52;
  for (i = 0; i < 1000; i++) {
    p_oPop->CreateTree(fX, fY, 1, clTreePopulation::seedling, 0.2);
    p_oPop->CreateTree(fX, fY, 2, clTreePopulation::seedling, 0.2);
    p_oPop->CreateTree(fX, fY, 3, clTreePopulation::seedling, 0.2);
  }

  //Grid cell 6, 5
  fX = 52; fY = 44;
  for (i = 0; i < 1000; i++) {
    p_oPop->CreateTree(fX, fY, 1, clTreePopulation::seedling, 0.2);
    p_oPop->CreateTree(fX, fY, 2, clTreePopulation::seedling, 0.2);
    p_oPop->CreateTree(fX, fY, 3, clTreePopulation::seedling, 0.2);
  }

  //Grid cell 5, 5
  fX = 44; fY = 44;
  for (i = 0; i < 1000; i++) {
    p_oPop->CreateTree(fX, fY, 1, clTreePopulation::seedling, 0.2);
    p_oPop->CreateTree(fX, fY, 2, clTreePopulation::seedling, 0.2);
    p_oPop->CreateTree(fX, fY, 3, clTreePopulation::seedling, 0.2);
  }

  //Grid cell 6, 6
  fX = 52; fY = 52;
  for (i = 0; i < 1000; i++) {
    p_oPop->CreateTree(fX, fY, 1, clTreePopulation::seedling, 0.2);
    p_oPop->CreateTree(fX, fY, 2, clTreePopulation::seedling, 0.2);
    p_oPop->CreateTree(fX, fY, 3, clTreePopulation::seedling, 0.2);
  }

  //Grid cell 7, 6
  fX = 60; fY = 52;
  for (i = 0; i < 1000; i++) {
    p_oPop->CreateTree(fX, fY, 1, clTreePopulation::seedling, 0.2);
    p_oPop->CreateTree(fX, fY, 2, clTreePopulation::seedling, 0.2);
    p_oPop->CreateTree(fX, fY, 3, clTreePopulation::seedling, 0.2);
  }

  //Grid cell 6, 7
  fX = 52; fY = 60;
  for (i = 0; i < 1000; i++) {
    p_oPop->CreateTree(fX, fY, 1, clTreePopulation::seedling, 0.2);
    p_oPop->CreateTree(fX, fY, 2, clTreePopulation::seedling, 0.2);
    p_oPop->CreateTree(fX, fY, 3, clTreePopulation::seedling, 0.2);
  }

  //Run one timestep
  p_oSimManager->RunSim(1);

  p_oSurvGrid = p_oSimManager->GetGridObject("Temperature Dependent Neighborhood Survival");

  //Check the grid values
  iCellX = 2; iCellY = 2;
  fExpectedSurvival1 = 0.139653074;
  fExpectedSurvival2 = 0.999654538;
  fExpectedSurvival3 = 0.797705336;
  p_oSurvGrid->GetValueOfCell(iCellX, iCellY, p_oSurvGrid->GetFloatDataCode("survival_1"), &fSurvival);
  EXPECT_LT(fabs(fSurvival - fExpectedSurvival1), 0.0001);
  p_oSurvGrid->GetValueOfCell(iCellX, iCellY, p_oSurvGrid->GetFloatDataCode("survival_2"), &fSurvival);
  EXPECT_LT(fabs(fSurvival - fExpectedSurvival2), 0.0001);
  p_oSurvGrid->GetValueOfCell(iCellX, iCellY, p_oSurvGrid->GetFloatDataCode("survival_3"), &fSurvival);
  EXPECT_LT(fabs(fSurvival - fExpectedSurvival3), 0.0001);

  iCellX = 5; iCellY = 6;
  fExpectedSurvival1 = 0.105270878;
  fExpectedSurvival2 = 0.029973407;
  fExpectedSurvival3 = 0.000178652;
  p_oSurvGrid->GetValueOfCell(iCellX, iCellY, p_oSurvGrid->GetFloatDataCode("survival_1"), &fSurvival);
  EXPECT_LT(fabs(fSurvival - fExpectedSurvival1), 0.0001);
  p_oSurvGrid->GetValueOfCell(iCellX, iCellY, p_oSurvGrid->GetFloatDataCode("survival_2"), &fSurvival);
  EXPECT_LT(fabs(fSurvival - fExpectedSurvival2), 0.0001);
  p_oSurvGrid->GetValueOfCell(iCellX, iCellY, p_oSurvGrid->GetFloatDataCode("survival_3"), &fSurvival);
  EXPECT_LT(fabs(fSurvival - fExpectedSurvival3), 0.0001);

  iCellX = 6; iCellY = 5;
  fExpectedSurvival1 = 0.11077398;
  fExpectedSurvival2 = 0.556371473;
  fExpectedSurvival3 = 0.310520752;
  p_oSurvGrid->GetValueOfCell(iCellX, iCellY, p_oSurvGrid->GetFloatDataCode("survival_1"), &fSurvival);
  EXPECT_LT(fabs(fSurvival - fExpectedSurvival1), 0.0001);
  p_oSurvGrid->GetValueOfCell(iCellX, iCellY, p_oSurvGrid->GetFloatDataCode("survival_2"), &fSurvival);
  EXPECT_LT(fabs(fSurvival - fExpectedSurvival2), 0.0001);
  p_oSurvGrid->GetValueOfCell(iCellX, iCellY, p_oSurvGrid->GetFloatDataCode("survival_3"), &fSurvival);
  EXPECT_LT(fabs(fSurvival - fExpectedSurvival3), 0.0001);

  iCellX = 5; iCellY = 5;
  fExpectedSurvival1 = 0.115882879;
  fExpectedSurvival2 = 0.919540336;
  fExpectedSurvival3 = 0.731060578;
  p_oSurvGrid->GetValueOfCell(iCellX, iCellY, p_oSurvGrid->GetFloatDataCode("survival_1"), &fSurvival);
  EXPECT_LT(fabs(fSurvival - fExpectedSurvival1), 0.0001);
  p_oSurvGrid->GetValueOfCell(iCellX, iCellY, p_oSurvGrid->GetFloatDataCode("survival_2"), &fSurvival);
  EXPECT_LT(fabs(fSurvival - fExpectedSurvival2), 0.0001);
  p_oSurvGrid->GetValueOfCell(iCellX, iCellY, p_oSurvGrid->GetFloatDataCode("survival_3"), &fSurvival);
  EXPECT_LT(fabs(fSurvival - fExpectedSurvival3), 0.0001);

  iCellX = 6; iCellY = 6;
  fExpectedSurvival1 = 0.106530348;
  fExpectedSurvival2 = 0.092351035;
  fExpectedSurvival3 = 0.004239541;
  p_oSurvGrid->GetValueOfCell(iCellX, iCellY, p_oSurvGrid->GetFloatDataCode("survival_1"), &fSurvival);
  EXPECT_LT(fabs(fSurvival - fExpectedSurvival1), 0.0001);
  p_oSurvGrid->GetValueOfCell(iCellX, iCellY, p_oSurvGrid->GetFloatDataCode("survival_2"), &fSurvival);
  EXPECT_LT(fabs(fSurvival - fExpectedSurvival2), 0.0001);
  p_oSurvGrid->GetValueOfCell(iCellX, iCellY, p_oSurvGrid->GetFloatDataCode("survival_3"), &fSurvival);
  EXPECT_LT(fabs(fSurvival - fExpectedSurvival3), 0.0001);

  iCellX = 7; iCellY = 6;
  fExpectedSurvival1 = 0.107071502;
  fExpectedSurvival2 = 0.134026167;
  fExpectedSurvival3 = 0.011327507;
  p_oSurvGrid->GetValueOfCell(iCellX, iCellY, p_oSurvGrid->GetFloatDataCode("survival_1"), &fSurvival);
  EXPECT_LT(fabs(fSurvival - fExpectedSurvival1), 0.0001);
  p_oSurvGrid->GetValueOfCell(iCellX, iCellY, p_oSurvGrid->GetFloatDataCode("survival_2"), &fSurvival);
  EXPECT_LT(fabs(fSurvival - fExpectedSurvival2), 0.0001);
  p_oSurvGrid->GetValueOfCell(iCellX, iCellY, p_oSurvGrid->GetFloatDataCode("survival_3"), &fSurvival);
  EXPECT_LT(fabs(fSurvival - fExpectedSurvival3), 0.0001);

  iCellX = 6; iCellY = 7;
  fExpectedSurvival1 = 0.104254186;
  fExpectedSurvival2 = 0.008628162;
  fExpectedSurvival3 = 4.07902E-06;
  p_oSurvGrid->GetValueOfCell(iCellX, iCellY, p_oSurvGrid->GetFloatDataCode("survival_1"), &fSurvival);
  EXPECT_LT(fabs(fSurvival - fExpectedSurvival1), 0.0001);
  p_oSurvGrid->GetValueOfCell(iCellX, iCellY, p_oSurvGrid->GetFloatDataCode("survival_2"), &fSurvival);
  EXPECT_LT(fabs(fSurvival - fExpectedSurvival2), 0.0001);
  p_oSurvGrid->GetValueOfCell(iCellX, iCellY, p_oSurvGrid->GetFloatDataCode("survival_3"), &fSurvival);
  EXPECT_LT(fabs(fSurvival - fExpectedSurvival3), 0.0001);

  //Count the seedlings in each grid cell
  p_oAllTrees = p_oPop->Find("type=1");

  //Grid cell 2, 2
  iExpectedSpecies1 = 139;
  iExpectedSpecies2 = 999;
  iExpectedSpecies3 = 797;
  iNumSpecies1 = 0; iNumSpecies2 = 0; iNumSpecies3 = 0;
  fX = 20; fY = 20;
  p_oTree = p_oAllTrees->NextTree();
  while (p_oTree) {
    p_oTree->GetValue(p_oPop->GetXCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTreeX);
    p_oTree->GetValue(p_oPop->GetYCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTreeY);
    if (fabs(fX - fTreeX) < 1 && fabs(fY - fTreeY) < 1) {
      if (1 == p_oTree->GetSpecies()) iNumSpecies1++;
      else if (2 == p_oTree->GetSpecies()) iNumSpecies2++;
      else iNumSpecies3++;
    }
    p_oTree = p_oAllTrees->NextTree();
  }
  EXPECT_LT(fabs(iNumSpecies1 - iExpectedSpecies1)/iExpectedSpecies1, 0.2);
  EXPECT_LT(fabs(iNumSpecies2 - iExpectedSpecies2)/iExpectedSpecies2, 0.1);
  EXPECT_LT(fabs(iNumSpecies3 - iExpectedSpecies3)/iExpectedSpecies3, 0.1);
  p_oAllTrees->StartOver();

  //Grid cell 5, 6
  iExpectedSpecies1 = 105;
  iExpectedSpecies2 = 29;
  iExpectedSpecies3 = 1;
  iNumSpecies1 = 0; iNumSpecies2 = 0; iNumSpecies3 = 0;
  fX = 44; fY = 52;
  p_oTree = p_oAllTrees->NextTree();
  while (p_oTree) {
    p_oTree->GetValue(p_oPop->GetXCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTreeX);
    p_oTree->GetValue(p_oPop->GetYCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTreeY);
    if (fabs(fX - fTreeX) < 1 && fabs(fY - fTreeY) < 1) {
      if (1 == p_oTree->GetSpecies()) iNumSpecies1++;
      else if (2 == p_oTree->GetSpecies()) iNumSpecies2++;
      else iNumSpecies3++;
    }
    p_oTree = p_oAllTrees->NextTree();
  }
  EXPECT_LT(fabs(iNumSpecies1 - iExpectedSpecies1)/iExpectedSpecies1, 0.312);
  EXPECT_TRUE(iNumSpecies2 > 10 && iNumSpecies2 < 45);
  EXPECT_LT(iNumSpecies3 , 10);
  p_oAllTrees->StartOver();

  //Grid cell 6, 5
  iExpectedSpecies1 = 110;
  iExpectedSpecies2 = 556;
  iExpectedSpecies3 = 310;
  iNumSpecies1 = 0; iNumSpecies2 = 0; iNumSpecies3 = 0;
  fX = 52; fY = 44;
  p_oTree = p_oAllTrees->NextTree();
  while (p_oTree) {
    p_oTree->GetValue(p_oPop->GetXCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTreeX);
    p_oTree->GetValue(p_oPop->GetYCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTreeY);
    if (fabs(fX - fTreeX) < 1 && fabs(fY - fTreeY) < 1) {
      if (1 == p_oTree->GetSpecies()) iNumSpecies1++;
      else if (2 == p_oTree->GetSpecies()) iNumSpecies2++;
      else iNumSpecies3++;
    }
    p_oTree = p_oAllTrees->NextTree();
  }
  EXPECT_LT(fabs(iNumSpecies1 - iExpectedSpecies1)/iExpectedSpecies1, 0.2);
  EXPECT_LT(fabs(iNumSpecies2 - iExpectedSpecies2)/iExpectedSpecies2, 0.1);
  EXPECT_LT(fabs(iNumSpecies3 - iExpectedSpecies3)/iExpectedSpecies3, 0.1);
  p_oAllTrees->StartOver();

  //Grid cell 5, 5
  iExpectedSpecies1 = 115;
  iExpectedSpecies2 = 919;
  iExpectedSpecies3 = 731;
  iNumSpecies1 = 0; iNumSpecies2 = 0; iNumSpecies3 = 0;
  fX = 44; fY = 44;
  p_oTree = p_oAllTrees->NextTree();
  while (p_oTree) {
    p_oTree->GetValue(p_oPop->GetXCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTreeX);
    p_oTree->GetValue(p_oPop->GetYCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTreeY);
    if (fabs(fX - fTreeX) < 1 && fabs(fY - fTreeY) < 1) {
      if (1 == p_oTree->GetSpecies()) iNumSpecies1++;
      else if (2 == p_oTree->GetSpecies()) iNumSpecies2++;
      else iNumSpecies3++;
    }
    p_oTree = p_oAllTrees->NextTree();
  }
  EXPECT_LT(fabs(iNumSpecies1 - iExpectedSpecies1)/iExpectedSpecies1, 0.2);
  EXPECT_LT(fabs(iNumSpecies2 - iExpectedSpecies2)/iExpectedSpecies2, 0.1);
  EXPECT_LT(fabs(iNumSpecies3 - iExpectedSpecies3)/iExpectedSpecies3, 0.1);
  p_oAllTrees->StartOver();

  //Grid cell 6, 6
  iExpectedSpecies1 = 106;
  iExpectedSpecies2 = 92;
  iExpectedSpecies3 = 4;
  iNumSpecies1 = 0; iNumSpecies2 = 0; iNumSpecies3 = 0;
  fX = 52; fY = 52;
  p_oTree = p_oAllTrees->NextTree();
  while (p_oTree) {
    p_oTree->GetValue(p_oPop->GetXCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTreeX);
    p_oTree->GetValue(p_oPop->GetYCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTreeY);
    if (fabs(fX - fTreeX) < 1 && fabs(fY - fTreeY) < 1) {
      if (1 == p_oTree->GetSpecies()) iNumSpecies1++;
      else if (2 == p_oTree->GetSpecies()) iNumSpecies2++;
      else iNumSpecies3++;
    }
    p_oTree = p_oAllTrees->NextTree();
  }
  EXPECT_LT(fabs(iNumSpecies1 - iExpectedSpecies1)/iExpectedSpecies1, 0.2);
  EXPECT_LT(fabs(iNumSpecies2 - iExpectedSpecies2)/iExpectedSpecies2, 0.2);
  EXPECT_LT(iNumSpecies3, 10);
  p_oAllTrees->StartOver();

  //Grid cell 7, 6
  iExpectedSpecies1 = 107;
  iExpectedSpecies2 = 134;
  iExpectedSpecies3 = 11;
  iNumSpecies1 = 0; iNumSpecies2 = 0; iNumSpecies3 = 0;
  fX = 60; fY = 52;
  p_oTree = p_oAllTrees->NextTree();
  while (p_oTree) {
    p_oTree->GetValue(p_oPop->GetXCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTreeX);
    p_oTree->GetValue(p_oPop->GetYCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTreeY);
    if (fabs(fX - fTreeX) < 1 && fabs(fY - fTreeY) < 1) {
      if (1 == p_oTree->GetSpecies()) iNumSpecies1++;
      else if (2 == p_oTree->GetSpecies()) iNumSpecies2++;
      else iNumSpecies3++;
    }
    p_oTree = p_oAllTrees->NextTree();
  }
  EXPECT_LT(fabs(iNumSpecies1 - iExpectedSpecies1)/iExpectedSpecies1, 0.1);
  EXPECT_LT(fabs(iNumSpecies2 - iExpectedSpecies2)/iExpectedSpecies2, 0.1);
  EXPECT_LT(iNumSpecies3, 20);
  p_oAllTrees->StartOver();

  //Grid cell 6, 7
  iExpectedSpecies1 = 104;
  iExpectedSpecies2 = 8;
  iExpectedSpecies3 = 0;
  iNumSpecies1 = 0; iNumSpecies2 = 0; iNumSpecies3 = 0;
  fX = 52; fY = 60;
  p_oTree = p_oAllTrees->NextTree();
  while (p_oTree) {
    p_oTree->GetValue(p_oPop->GetXCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTreeX);
    p_oTree->GetValue(p_oPop->GetYCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTreeY);
    if (fabs(fX - fTreeX) < 1 && fabs(fY - fTreeY) < 1) {
      if (1 == p_oTree->GetSpecies()) iNumSpecies1++;
      else if (2 == p_oTree->GetSpecies()) iNumSpecies2++;
      else iNumSpecies3++;
    }
    p_oTree = p_oAllTrees->NextTree();
  }
  EXPECT_LT(fabs(iNumSpecies1 - iExpectedSpecies1)/iExpectedSpecies1, 0.1);
  EXPECT_LT(iNumSpecies2, 20);
  EXPECT_LT(iNumSpecies3, 5);
  p_oAllTrees->StartOver();


  //Update temp, recharge the seedling pool, run again
  p_oTree = p_oAllTrees->NextTree();
  while (p_oTree) {
    p_oPop->KillTree(p_oTree, remove_tree);
    p_oTree = p_oAllTrees->NextTree();
  }
  clPlot *p_oPlot = p_oSimManager->GetPlotObject();
  p_oPlot->SetMeanAnnualTemp(20);

  //Grid cell 2, 2
  fX = 20; fY = 20;
  for (i = 0; i < 1000; i++) {
    p_oPop->CreateTree(fX, fY, 1, clTreePopulation::seedling, 0.2);
    p_oPop->CreateTree(fX, fY, 2, clTreePopulation::seedling, 0.2);
    p_oPop->CreateTree(fX, fY, 3, clTreePopulation::seedling, 0.2);
  }

  //Grid cell 5, 6
  fX = 44; fY = 52;
  for (i = 0; i < 1000; i++) {
    p_oPop->CreateTree(fX, fY, 1, clTreePopulation::seedling, 0.2);
    p_oPop->CreateTree(fX, fY, 2, clTreePopulation::seedling, 0.2);
    p_oPop->CreateTree(fX, fY, 3, clTreePopulation::seedling, 0.2);
  }

  //Grid cell 6, 5
  fX = 52; fY = 44;
  for (i = 0; i < 1000; i++) {
    p_oPop->CreateTree(fX, fY, 1, clTreePopulation::seedling, 0.2);
    p_oPop->CreateTree(fX, fY, 2, clTreePopulation::seedling, 0.2);
    p_oPop->CreateTree(fX, fY, 3, clTreePopulation::seedling, 0.2);
  }

  //Grid cell 5, 5
  fX = 44; fY = 44;
  for (i = 0; i < 1000; i++) {
    p_oPop->CreateTree(fX, fY, 1, clTreePopulation::seedling, 0.2);
    p_oPop->CreateTree(fX, fY, 2, clTreePopulation::seedling, 0.2);
    p_oPop->CreateTree(fX, fY, 3, clTreePopulation::seedling, 0.2);
  }

  //Grid cell 6, 6
  fX = 52; fY = 52;
  for (i = 0; i < 1000; i++) {
    p_oPop->CreateTree(fX, fY, 1, clTreePopulation::seedling, 0.2);
    p_oPop->CreateTree(fX, fY, 2, clTreePopulation::seedling, 0.2);
    p_oPop->CreateTree(fX, fY, 3, clTreePopulation::seedling, 0.2);
  }

  //Grid cell 7, 6
  fX = 60; fY = 52;
  for (i = 0; i < 1000; i++) {
    p_oPop->CreateTree(fX, fY, 1, clTreePopulation::seedling, 0.2);
    p_oPop->CreateTree(fX, fY, 2, clTreePopulation::seedling, 0.2);
    p_oPop->CreateTree(fX, fY, 3, clTreePopulation::seedling, 0.2);
  }

  //Grid cell 6, 7
  fX = 52; fY = 60;
  for (i = 0; i < 1000; i++) {
    p_oPop->CreateTree(fX, fY, 1, clTreePopulation::seedling, 0.2);
    p_oPop->CreateTree(fX, fY, 2, clTreePopulation::seedling, 0.2);
    p_oPop->CreateTree(fX, fY, 3, clTreePopulation::seedling, 0.2);
  }

  p_oSimManager->RunSim(1);

  //Time step 2
  //Check the grid values
  iCellX = 2; iCellY = 2;
  fExpectedSurvival1 = 0.000800622;
  fExpectedSurvival2 = 0.998076779;
  fExpectedSurvival3 = 0.162837908;
  p_oSurvGrid->GetValueOfCell(iCellX, iCellY, p_oSurvGrid->GetFloatDataCode("survival_1"), &fSurvival);
  EXPECT_LT(fabs(fSurvival - fExpectedSurvival1), 0.0001);
  p_oSurvGrid->GetValueOfCell(iCellX, iCellY, p_oSurvGrid->GetFloatDataCode("survival_2"), &fSurvival);
  EXPECT_LT(fabs(fSurvival - fExpectedSurvival2), 0.0001);
  p_oSurvGrid->GetValueOfCell(iCellX, iCellY, p_oSurvGrid->GetFloatDataCode("survival_3"), &fSurvival);
  EXPECT_LT(fabs(fSurvival - fExpectedSurvival3), 0.0001);

  iCellX = 5; iCellY = 6;
  fExpectedSurvival1 = 0.000603511;
  fExpectedSurvival2 = 0.0299261;
  fExpectedSurvival3 = 3.64687E-05;
  p_oSurvGrid->GetValueOfCell(iCellX, iCellY, p_oSurvGrid->GetFloatDataCode("survival_1"), &fSurvival);
  EXPECT_LT(fabs(fSurvival - fExpectedSurvival1), 0.0001);
  p_oSurvGrid->GetValueOfCell(iCellX, iCellY, p_oSurvGrid->GetFloatDataCode("survival_2"), &fSurvival);
  EXPECT_LT(fabs(fSurvival - fExpectedSurvival2), 0.0001);
  p_oSurvGrid->GetValueOfCell(iCellX, iCellY, p_oSurvGrid->GetFloatDataCode("survival_3"), &fSurvival);
  EXPECT_LT(fabs(fSurvival - fExpectedSurvival3), 0.0001);

  iCellX = 6; iCellY = 5;
  fExpectedSurvival1 = 0.00063506;
  fExpectedSurvival2 = 0.555493349;
  fExpectedSurvival3 = 0.063387503;
  p_oSurvGrid->GetValueOfCell(iCellX, iCellY, p_oSurvGrid->GetFloatDataCode("survival_1"), &fSurvival);
  EXPECT_LT(fabs(fSurvival - fExpectedSurvival1), 0.0001);
  p_oSurvGrid->GetValueOfCell(iCellX, iCellY, p_oSurvGrid->GetFloatDataCode("survival_2"), &fSurvival);
  EXPECT_LT(fabs(fSurvival - fExpectedSurvival2), 0.0001);
  p_oSurvGrid->GetValueOfCell(iCellX, iCellY, p_oSurvGrid->GetFloatDataCode("survival_3"), &fSurvival);
  EXPECT_LT(fabs(fSurvival - fExpectedSurvival3), 0.0001);

  iCellX = 5; iCellY = 5;
  fExpectedSurvival1 = 0.000664349;
  fExpectedSurvival2 = 0.918089021;
  fExpectedSurvival3 = 0.14923352;
  p_oSurvGrid->GetValueOfCell(iCellX, iCellY, p_oSurvGrid->GetFloatDataCode("survival_1"), &fSurvival);
  EXPECT_LT(fabs(fSurvival - fExpectedSurvival1), 0.0001);
  p_oSurvGrid->GetValueOfCell(iCellX, iCellY, p_oSurvGrid->GetFloatDataCode("survival_2"), &fSurvival);
  EXPECT_LT(fabs(fSurvival - fExpectedSurvival2), 0.0001);
  p_oSurvGrid->GetValueOfCell(iCellX, iCellY, p_oSurvGrid->GetFloatDataCode("survival_3"), &fSurvival);
  EXPECT_LT(fabs(fSurvival - fExpectedSurvival3), 0.0001);

  iCellX = 6; iCellY = 6;
  fExpectedSurvival1 = 0.000610732;
  fExpectedSurvival2 = 0.092205277;
  fExpectedSurvival3 = 0.00086543;
  p_oSurvGrid->GetValueOfCell(iCellX, iCellY, p_oSurvGrid->GetFloatDataCode("survival_1"), &fSurvival);
  EXPECT_LT(fabs(fSurvival - fExpectedSurvival1), 0.0001);
  p_oSurvGrid->GetValueOfCell(iCellX, iCellY, p_oSurvGrid->GetFloatDataCode("survival_2"), &fSurvival);
  EXPECT_LT(fabs(fSurvival - fExpectedSurvival2), 0.0001);
  p_oSurvGrid->GetValueOfCell(iCellX, iCellY, p_oSurvGrid->GetFloatDataCode("survival_3"), &fSurvival);
  EXPECT_LT(fabs(fSurvival - fExpectedSurvival3), 0.0001);

  iCellX = 7; iCellY = 6;
  fExpectedSurvival1 = 0.000613834;
  fExpectedSurvival2 = 0.133814632;
  fExpectedSurvival3 = 0.002312317;
  p_oSurvGrid->GetValueOfCell(iCellX, iCellY, p_oSurvGrid->GetFloatDataCode("survival_1"), &fSurvival);
  EXPECT_LT(fabs(fSurvival - fExpectedSurvival1), 0.0001);
  p_oSurvGrid->GetValueOfCell(iCellX, iCellY, p_oSurvGrid->GetFloatDataCode("survival_2"), &fSurvival);
  EXPECT_LT(fabs(fSurvival - fExpectedSurvival2), 0.0001);
  p_oSurvGrid->GetValueOfCell(iCellX, iCellY, p_oSurvGrid->GetFloatDataCode("survival_3"), &fSurvival);
  EXPECT_LT(fabs(fSurvival - fExpectedSurvival3), 0.0001);

  iCellX = 6; iCellY = 7;
  fExpectedSurvival1 = 0.000597683;
  fExpectedSurvival2 = 0.008614544;
  fExpectedSurvival3 = 8.32663E-07;
  p_oSurvGrid->GetValueOfCell(iCellX, iCellY, p_oSurvGrid->GetFloatDataCode("survival_1"), &fSurvival);
  EXPECT_LT(fabs(fSurvival - fExpectedSurvival1), 0.0001);
  p_oSurvGrid->GetValueOfCell(iCellX, iCellY, p_oSurvGrid->GetFloatDataCode("survival_2"), &fSurvival);
  EXPECT_LT(fabs(fSurvival - fExpectedSurvival2), 0.0001);
  p_oSurvGrid->GetValueOfCell(iCellX, iCellY, p_oSurvGrid->GetFloatDataCode("survival_3"), &fSurvival);
  EXPECT_LT(fabs(fSurvival - fExpectedSurvival3), 0.0001);

  //Count the seedlings in each grid cell
  p_oAllTrees = p_oPop->Find("type=1");

  //Grid cell 2, 2
  iExpectedSpecies1 = 1;
  iExpectedSpecies2 = 999;
  iExpectedSpecies3 = 162;
  iNumSpecies1 = 0; iNumSpecies2 = 0; iNumSpecies3 = 0;
  fX = 20; fY = 20;
  p_oTree = p_oAllTrees->NextTree();
  while (p_oTree) {
    p_oTree->GetValue(p_oPop->GetXCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTreeX);
    p_oTree->GetValue(p_oPop->GetYCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTreeY);
    if (fabs(fX - fTreeX) < 1 && fabs(fY - fTreeY) < 1) {
      if (1 == p_oTree->GetSpecies()) iNumSpecies1++;
      else if (2 == p_oTree->GetSpecies()) iNumSpecies2++;
      else iNumSpecies3++;
    }
    p_oTree = p_oAllTrees->NextTree();
  }
  EXPECT_LT(iNumSpecies1, 6);
  EXPECT_LT(fabs(iNumSpecies2 - iExpectedSpecies2)/iExpectedSpecies2, 0.1);
  EXPECT_LT(fabs(iNumSpecies3 - iExpectedSpecies3)/iExpectedSpecies3, 0.1);
  p_oAllTrees->StartOver();

  //Grid cell 5, 6
  iExpectedSpecies1 = 1;
  iExpectedSpecies2 = 29;
  iExpectedSpecies3 = 1;
  iNumSpecies1 = 0; iNumSpecies2 = 0; iNumSpecies3 = 0;
  fX = 44; fY = 52;
  p_oTree = p_oAllTrees->NextTree();
  while (p_oTree) {
    p_oTree->GetValue(p_oPop->GetXCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTreeX);
    p_oTree->GetValue(p_oPop->GetYCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTreeY);
    if (fabs(fX - fTreeX) < 1 && fabs(fY - fTreeY) < 1) {
      if (1 == p_oTree->GetSpecies()) iNumSpecies1++;
      else if (2 == p_oTree->GetSpecies()) iNumSpecies2++;
      else iNumSpecies3++;
    }
    p_oTree = p_oAllTrees->NextTree();
  }
  EXPECT_LT(iNumSpecies1, 6);
  EXPECT_TRUE(iNumSpecies2 > 15 && iNumSpecies2 < 40);
  EXPECT_LT(iNumSpecies3, 6);
  p_oAllTrees->StartOver();

  //Grid cell 6, 5
  iExpectedSpecies1 = 1;
  iExpectedSpecies2 = 555;
  iExpectedSpecies3 = 63;
  iNumSpecies1 = 0; iNumSpecies2 = 0; iNumSpecies3 = 0;
  fX = 52; fY = 44;
  p_oTree = p_oAllTrees->NextTree();
  while (p_oTree) {
    p_oTree->GetValue(p_oPop->GetXCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTreeX);
    p_oTree->GetValue(p_oPop->GetYCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTreeY);
    if (fabs(fX - fTreeX) < 1 && fabs(fY - fTreeY) < 1) {
      if (1 == p_oTree->GetSpecies()) iNumSpecies1++;
      else if (2 == p_oTree->GetSpecies()) iNumSpecies2++;
      else iNumSpecies3++;
    }
    p_oTree = p_oAllTrees->NextTree();
  }
  EXPECT_LT(iNumSpecies1, 6);
  EXPECT_LT(fabs(iNumSpecies2 - iExpectedSpecies2)/iExpectedSpecies2, 0.1);
  EXPECT_LT(fabs(iNumSpecies3 - iExpectedSpecies3)/iExpectedSpecies3, 0.2);
  p_oAllTrees->StartOver();

  //Grid cell 5, 5
  iExpectedSpecies1 = 1;
  iExpectedSpecies2 = 918;
  iExpectedSpecies3 = 149;
  iNumSpecies1 = 0; iNumSpecies2 = 0; iNumSpecies3 = 0;
  fX = 44; fY = 44;
  p_oTree = p_oAllTrees->NextTree();
  while (p_oTree) {
    p_oTree->GetValue(p_oPop->GetXCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTreeX);
    p_oTree->GetValue(p_oPop->GetYCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTreeY);
    if (fabs(fX - fTreeX) < 1 && fabs(fY - fTreeY) < 1) {
      if (1 == p_oTree->GetSpecies()) iNumSpecies1++;
      else if (2 == p_oTree->GetSpecies()) iNumSpecies2++;
      else iNumSpecies3++;
    }
    p_oTree = p_oAllTrees->NextTree();
  }
  EXPECT_LT(iNumSpecies1, 6);
  EXPECT_LT(fabs(iNumSpecies2 - iExpectedSpecies2)/iExpectedSpecies2, 0.1);
  EXPECT_LT(fabs(iNumSpecies3 - iExpectedSpecies3)/iExpectedSpecies3, 0.2);
  p_oAllTrees->StartOver();

  //Grid cell 6, 6
  iExpectedSpecies1 = 1;
  iExpectedSpecies2 = 92;
  iExpectedSpecies3 = 1;
  iNumSpecies1 = 0; iNumSpecies2 = 0; iNumSpecies3 = 0;
  fX = 52; fY = 52;
  p_oTree = p_oAllTrees->NextTree();
  while (p_oTree) {
    p_oTree->GetValue(p_oPop->GetXCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTreeX);
    p_oTree->GetValue(p_oPop->GetYCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTreeY);
    if (fabs(fX - fTreeX) < 1 && fabs(fY - fTreeY) < 1) {
      if (1 == p_oTree->GetSpecies()) iNumSpecies1++;
      else if (2 == p_oTree->GetSpecies()) iNumSpecies2++;
      else iNumSpecies3++;
    }
    p_oTree = p_oAllTrees->NextTree();
  }
  EXPECT_LT(iNumSpecies1, 6);
  EXPECT_LT(fabs(iNumSpecies2 - iExpectedSpecies2)/iExpectedSpecies2, 0.2);
  EXPECT_LT(iNumSpecies3, 6);
  p_oAllTrees->StartOver();

  //Grid cell 7, 6
  iExpectedSpecies1 = 1;
  iExpectedSpecies2 = 133;
  iExpectedSpecies3 = 2;
  iNumSpecies1 = 0; iNumSpecies2 = 0; iNumSpecies3 = 0;
  fX = 60; fY = 52;
  p_oTree = p_oAllTrees->NextTree();
  while (p_oTree) {
    p_oTree->GetValue(p_oPop->GetXCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTreeX);
    p_oTree->GetValue(p_oPop->GetYCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTreeY);
    if (fabs(fX - fTreeX) < 1 && fabs(fY - fTreeY) < 1) {
      if (1 == p_oTree->GetSpecies()) iNumSpecies1++;
      else if (2 == p_oTree->GetSpecies()) iNumSpecies2++;
      else iNumSpecies3++;
    }
    p_oTree = p_oAllTrees->NextTree();
  }
  EXPECT_LT(iNumSpecies1, 6);
  EXPECT_LT(fabs(iNumSpecies2 - iExpectedSpecies2)/iExpectedSpecies2, 0.1);
  EXPECT_LT(iNumSpecies3, 10);
  p_oAllTrees->StartOver();

  //Grid cell 6, 7
  iExpectedSpecies1 = 1;
  iExpectedSpecies2 = 8;
  iExpectedSpecies3 = 0;
  iNumSpecies1 = 0; iNumSpecies2 = 0; iNumSpecies3 = 0;
  fX = 52; fY = 60;
  p_oTree = p_oAllTrees->NextTree();
  while (p_oTree) {
    p_oTree->GetValue(p_oPop->GetXCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTreeX);
    p_oTree->GetValue(p_oPop->GetYCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTreeY);
    if (fabs(fX - fTreeX) < 1 && fabs(fY - fTreeY) < 1) {
      if (1 == p_oTree->GetSpecies()) iNumSpecies1++;
      else if (2 == p_oTree->GetSpecies()) iNumSpecies2++;
      else iNumSpecies3++;
    }
    p_oTree = p_oAllTrees->NextTree();
  }
  EXPECT_LT(iNumSpecies1, 6);
  EXPECT_LT(iNumSpecies2, 20);
  EXPECT_LT(iNumSpecies3, 20);
  delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

////////////////////////////////////////////////////////////////////////////
// TestErrorProcessing()
////////////////////////////////////////////////////////////////////////////
TEST(TempDependentNeighborhoodSurvival, TestErrorProcessing) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    p_oSimManager->ReadFile(WriteTempDependentNeighborhoodSurvivalXMLErrorFile1());
    FAIL() << "TestTempDependentNeighborhoodSurvival error processing didn't catch error for WriteTempDependentNeighborhoodSurvivalXMLErrorFile1.";
  } catch (modelErr& err) {
    if (err.sFunction.compare("clTempDependentNeighborhoodSurvival::ValidateData") != 0) {
      FAIL() << "TestTempDependentNeighborhoodSurvival error processing caught wrong error for WriteTempDependentNeighborhoodSurvivalXMLErrorFile1.";
    };
  }

  try {
    p_oSimManager->ReadFile(WriteTempDependentNeighborhoodSurvivalXMLErrorFile2());
    FAIL() << "TestTempDependentNeighborhoodSurvival error processing didn't catch error for WriteTempDependentNeighborhoodSurvivalXMLErrorFile1.";
  } catch (modelErr& err) {
    if (err.sFunction.compare("clTempDependentNeighborhoodSurvival::ValidateData") != 0) {
      FAIL() << "TestTempDependentNeighborhoodSurvival error processing caught wrong error for WriteTempDependentNeighborhoodSurvivalXMLErrorFile1.";
    };
  }
  delete p_oSimManager;
}


/////////////////////////////////////////////////////////////////////////////
// WriteTempDependentNeighborhoodSurvivalXMLFile1()
/////////////////////////////////////////////////////////////////////////////
const char* WriteTempDependentNeighborhoodSurvivalXMLFile(int iYearsPerTimestep) {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06010101\">"
       << "<plot>"
       << "<timesteps>4</timesteps>"
       << "<yearsPerTimestep>" << iYearsPerTimestep << "</yearsPerTimestep>"
       << "<randomSeed>1</randomSeed>"
       << "<plot_lenX>100.0</plot_lenX>"
       << "<plot_lenY>100.0</plot_lenY>"
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
       << "<tr_mshVal species=\"Species_1\">1.35</tr_mshVal>"
       << "<tr_mshVal species=\"Species_2\">1.35</tr_mshVal>"
       << "<tr_mshVal species=\"Species_3\">1.35</tr_mshVal>"
       << "<tr_mshVal species=\"Species_4\">1.35</tr_mshVal>"
       << "</tr_maxSeedlingHeight>"
       << "</trees>"
       << "<allometry>"
       << "<tr_canopyHeight>"
       << "<tr_chVal species=\"Species_1\">39.48</tr_chVal>"
       << "<tr_chVal species=\"Species_2\">39.48</tr_chVal>"
       << "<tr_chVal species=\"Species_3\">39.48</tr_chVal>"
       << "<tr_chVal species=\"Species_4\">39.48</tr_chVal>"
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
       << "<tr_cdtdVal species=\"Species_1\">1</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_2\">1</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_3\">1</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_4\">1</tr_cdtdVal>"
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
       << "<tr_slopeOfHeight-Diam10>"
       << "<tr_sohdVal species=\"Species_1\">0.03418</tr_sohdVal>"
       << "<tr_sohdVal species=\"Species_2\">0.03418</tr_sohdVal>"
       << "<tr_sohdVal species=\"Species_3\">0.03418</tr_sohdVal>"
       << "<tr_sohdVal species=\"Species_4\">0.03418</tr_sohdVal>"
       << "</tr_slopeOfHeight-Diam10>"
       << "<tr_slopeOfAsymHeight>"
       << "<tr_soahVal species=\"Species_1\">0.0299</tr_soahVal>"
       << "<tr_soahVal species=\"Species_2\">0.0299</tr_soahVal>"
       << "<tr_soahVal species=\"Species_3\">0.0299</tr_soahVal>"
       << "<tr_soahVal species=\"Species_4\">0.0299</tr_soahVal>"
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

  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>TempDependentNeighborhoodSurvival</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_2\" type=\"Seedling\"/>"
       << "<applyTo species=\"Species_3\" type=\"Seedling\"/>"
       << "<applyTo species=\"Species_4\" type=\"Seedling\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>RemoveDead</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>2</listPosition>"
       << "<applyTo species=\"Species_2\" type=\"Seedling\"/>"
       << "<applyTo species=\"Species_3\" type=\"Seedling\"/>"
       << "<applyTo species=\"Species_4\" type=\"Seedling\"/>"
       << "</behavior>"
       << "</behaviorList>"
       << "<TempDependentNeighborhoodSurvival1>"
       << "<mo_tempDepNeighM>"
       << "<mo_tdnmVal species=\"Species_2\">5</mo_tdnmVal>"
       << "<mo_tdnmVal species=\"Species_3\">15</mo_tdnmVal>"
       << "<mo_tdnmVal species=\"Species_4\">9</mo_tdnmVal>"
       << "</mo_tempDepNeighM>"
       << "<mo_tempDepNeighN>"
       << "<mo_tdnnVal species=\"Species_2\">6.88</mo_tdnnVal>"
       << "<mo_tdnnVal species=\"Species_3\">139.57</mo_tdnnVal>"
       << "<mo_tdnnVal species=\"Species_4\">10</mo_tdnnVal>"
       << "</mo_tempDepNeighN>"
       << "<mo_tempDepNeighA>"
       << "<mo_tdnaVal species=\"Species_2\">0.1</mo_tdnaVal>"
       << "<mo_tdnaVal species=\"Species_3\">2</mo_tdnaVal>"
       << "<mo_tdnaVal species=\"Species_4\">5.4</mo_tdnaVal>"
       << "</mo_tempDepNeighA>"
       << "<mo_tempDepNeighB>"
       << "<mo_tdnbVal species=\"Species_2\">0.1</mo_tdnbVal>"
       << "<mo_tdnbVal species=\"Species_3\">0.9</mo_tdnbVal>"
       << "<mo_tdnbVal species=\"Species_4\">1.1</mo_tdnbVal>"
       << "</mo_tempDepNeighB>"
       << "<mo_tempDepNeighRadius>10</mo_tempDepNeighRadius>"
       << "</TempDependentNeighborhoodSurvival1>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteTempDependentNeighborhoodSurvivalXMLErrorFile1()
/////////////////////////////////////////////////////////////////////////////
const char* WriteTempDependentNeighborhoodSurvivalXMLErrorFile1() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06010101\">"
       << "<plot>"
       << "<timesteps>4</timesteps>"
       << "<yearsPerTimestep>1</yearsPerTimestep>"
       << "<randomSeed>1</randomSeed>"
       << "<plot_lenX>100.0</plot_lenX>"
       << "<plot_lenY>100.0</plot_lenY>"
       << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
       << "<plot_temp_C>12.88171785</plot_temp_C>"
       << "<plot_latitude>55.37</plot_latitude>"
       << "</plot>"
       << "<trees>"
       << "<tr_speciesList>"
       << "<tr_species speciesName=\"Species_1\"/>"
       << "<tr_species speciesName=\"Species_2\"/>"
       << "</tr_speciesList>"
       << "<tr_seedDiam10Cm>0.1</tr_seedDiam10Cm>"
       << "<tr_minAdultDBH>"
       << "<tr_madVal species=\"Species_1\">10.0</tr_madVal>"
       << "<tr_madVal species=\"Species_2\">10.0</tr_madVal>"
       << "</tr_minAdultDBH>"
       << "<tr_maxSeedlingHeight>"
       << "<tr_mshVal species=\"Species_1\">1.35</tr_mshVal>"
       << "<tr_mshVal species=\"Species_2\">1.35</tr_mshVal>"
       << "</tr_maxSeedlingHeight>"
       << "</trees>"
       << "<allometry>"
       << "<tr_canopyHeight>"
       << "<tr_chVal species=\"Species_1\">39.48</tr_chVal>"
       << "<tr_chVal species=\"Species_2\">39.48</tr_chVal>"
       << "</tr_canopyHeight>"
       << "<tr_stdAsympCrownRad>"
       << "<tr_sacrVal species=\"Species_1\">0.0549</tr_sacrVal>"
       << "<tr_sacrVal species=\"Species_2\">0.0549</tr_sacrVal>"
       << "</tr_stdAsympCrownRad>"
       << "<tr_stdCrownRadExp>"
       << "<tr_screVal species=\"Species_1\">1.0</tr_screVal>"
       << "<tr_screVal species=\"Species_2\">1.0</tr_screVal>"
       << "</tr_stdCrownRadExp>"
       << "<tr_conversionDiam10ToDBH>"
       << "<tr_cdtdVal species=\"Species_1\">1</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_2\">1</tr_cdtdVal>"
       << "</tr_conversionDiam10ToDBH>"
       << "<tr_interceptDiam10ToDBH>"
       << "<tr_idtdVal species=\"Species_1\">0</tr_idtdVal>"
       << "<tr_idtdVal species=\"Species_2\">0</tr_idtdVal>"
       << "</tr_interceptDiam10ToDBH>"
       << "<tr_stdAsympCrownHt>"
       << "<tr_sachVal species=\"Species_1\">0.389</tr_sachVal>"
       << "<tr_sachVal species=\"Species_2\">0.389</tr_sachVal>"
       << "</tr_stdAsympCrownHt>"
       << "<tr_stdCrownHtExp>"
       << "<tr_scheVal species=\"Species_1\">1.0</tr_scheVal>"
       << "<tr_scheVal species=\"Species_2\">1.0</tr_scheVal>"
       << "</tr_stdCrownHtExp>"
       << "<tr_slopeOfHeight-Diam10>"
       << "<tr_sohdVal species=\"Species_1\">0.03418</tr_sohdVal>"
       << "<tr_sohdVal species=\"Species_2\">0.03418</tr_sohdVal>"
       << "</tr_slopeOfHeight-Diam10>"
       << "<tr_slopeOfAsymHeight>"
       << "<tr_soahVal species=\"Species_1\">0.0299</tr_soahVal>"
       << "<tr_soahVal species=\"Species_2\">0.0299</tr_soahVal>"
       << "</tr_slopeOfAsymHeight>"
       << "<tr_whatSeedlingHeightDiam>"
       << "<tr_wsehdVal species=\"Species_1\">0</tr_wsehdVal>"
       << "<tr_wsehdVal species=\"Species_2\">0</tr_wsehdVal>"
       << "</tr_whatSeedlingHeightDiam>"
       << "<tr_whatSaplingHeightDiam>"
       << "<tr_wsahdVal species=\"Species_1\">0</tr_wsahdVal>"
       << "<tr_wsahdVal species=\"Species_2\">0</tr_wsahdVal>"
       << "</tr_whatSaplingHeightDiam>"
       << "<tr_whatAdultHeightDiam>"
       << "<tr_wahdVal species=\"Species_1\">0</tr_wahdVal>"
       << "<tr_wahdVal species=\"Species_2\">0</tr_wahdVal>"
       << "</tr_whatAdultHeightDiam>"
       << "<tr_whatAdultCrownRadDiam>"
       << "<tr_wacrdVal species=\"Species_1\">0</tr_wacrdVal>"
       << "<tr_wacrdVal species=\"Species_2\">0</tr_wacrdVal>"
       << "</tr_whatAdultCrownRadDiam>"
       << "<tr_whatAdultCrownHeightHeight>"
       << "<tr_wachhVal species=\"Species_1\">0</tr_wachhVal>"
       << "<tr_wachhVal species=\"Species_2\">0</tr_wachhVal>"
       << "</tr_whatAdultCrownHeightHeight>"
       << "<tr_whatSaplingCrownRadDiam>"
       << "<tr_wscrdVal species=\"Species_1\">0</tr_wscrdVal>"
       << "<tr_wscrdVal species=\"Species_2\">0</tr_wscrdVal>"
       << "</tr_whatSaplingCrownRadDiam>"
       << "<tr_whatSaplingCrownHeightHeight>"
       << "<tr_wschhVal species=\"Species_1\">0</tr_wschhVal>"
       << "<tr_wschhVal species=\"Species_2\">0</tr_wschhVal>"
       << "</tr_whatSaplingCrownHeightHeight>"
       << "</allometry>";

  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>TempDependentNeighborhoodSurvival</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Seedling\"/>"
       << "<applyTo species=\"Species_2\" type=\"Seedling\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>RemoveDead</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>2</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Seedling\"/>"
       << "<applyTo species=\"Species_2\" type=\"Seedling\"/>"
       << "</behavior>"
       << "</behaviorList>"
       << "<TempDependentNeighborhoodSurvival1>"
       << "<mo_tempDepNeighM>"
       << "<mo_tdnmVal species=\"Species_1\">5</mo_tdnmVal>"
       << "<mo_tdnmVal species=\"Species_2\">15</mo_tdnmVal>"
       << "</mo_tempDepNeighM>"
       << "<mo_tempDepNeighN>"
       << "<mo_tdnnVal species=\"Species_1\">0</mo_tdnnVal>"
       << "<mo_tdnnVal species=\"Species_2\">139.57</mo_tdnnVal>"
       << "</mo_tempDepNeighN>"
       << "<mo_tempDepNeighA>"
       << "<mo_tdnaVal species=\"Species_1\">0.1</mo_tdnaVal>"
       << "<mo_tdnaVal species=\"Species_2\">2</mo_tdnaVal>"
       << "</mo_tempDepNeighA>"
       << "<mo_tempDepNeighB>"
       << "<mo_tdnbVal species=\"Species_1\">0.1</mo_tdnbVal>"
       << "<mo_tdnbVal species=\"Species_2\">0.9</mo_tdnbVal>"
       << "</mo_tempDepNeighB>"
       << "<mo_tempDepNeighRadius>10</mo_tempDepNeighRadius>"
       << "</TempDependentNeighborhoodSurvival1>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteTempDependentNeighborhoodSurvivalXMLErrorFile2()
/////////////////////////////////////////////////////////////////////////////
const char* WriteTempDependentNeighborhoodSurvivalXMLErrorFile2() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06010101\">"
       << "<plot>"
       << "<timesteps>4</timesteps>"
       << "<yearsPerTimestep>1</yearsPerTimestep>"
       << "<randomSeed>1</randomSeed>"
       << "<plot_lenX>100.0</plot_lenX>"
       << "<plot_lenY>100.0</plot_lenY>"
       << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
       << "<plot_temp_C>12.88171785</plot_temp_C>"
       << "<plot_latitude>55.37</plot_latitude>"
       << "</plot>"
       << "<trees>"
       << "<tr_speciesList>"
       << "<tr_species speciesName=\"Species_1\"/>"
       << "<tr_species speciesName=\"Species_2\"/>"
       << "</tr_speciesList>"
       << "<tr_seedDiam10Cm>0.1</tr_seedDiam10Cm>"
       << "<tr_minAdultDBH>"
       << "<tr_madVal species=\"Species_1\">10.0</tr_madVal>"
       << "<tr_madVal species=\"Species_2\">10.0</tr_madVal>"
       << "</tr_minAdultDBH>"
       << "<tr_maxSeedlingHeight>"
       << "<tr_mshVal species=\"Species_1\">1.35</tr_mshVal>"
       << "<tr_mshVal species=\"Species_2\">1.35</tr_mshVal>"
       << "</tr_maxSeedlingHeight>"
       << "</trees>"
       << "<allometry>"
       << "<tr_canopyHeight>"
       << "<tr_chVal species=\"Species_1\">39.48</tr_chVal>"
       << "<tr_chVal species=\"Species_2\">39.48</tr_chVal>"
       << "</tr_canopyHeight>"
       << "<tr_stdAsympCrownRad>"
       << "<tr_sacrVal species=\"Species_1\">0.0549</tr_sacrVal>"
       << "<tr_sacrVal species=\"Species_2\">0.0549</tr_sacrVal>"
       << "</tr_stdAsympCrownRad>"
       << "<tr_stdCrownRadExp>"
       << "<tr_screVal species=\"Species_1\">1.0</tr_screVal>"
       << "<tr_screVal species=\"Species_2\">1.0</tr_screVal>"
       << "</tr_stdCrownRadExp>"
       << "<tr_conversionDiam10ToDBH>"
       << "<tr_cdtdVal species=\"Species_1\">1</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_2\">1</tr_cdtdVal>"
       << "</tr_conversionDiam10ToDBH>"
       << "<tr_interceptDiam10ToDBH>"
       << "<tr_idtdVal species=\"Species_1\">0</tr_idtdVal>"
       << "<tr_idtdVal species=\"Species_2\">0</tr_idtdVal>"
       << "</tr_interceptDiam10ToDBH>"
       << "<tr_stdAsympCrownHt>"
       << "<tr_sachVal species=\"Species_1\">0.389</tr_sachVal>"
       << "<tr_sachVal species=\"Species_2\">0.389</tr_sachVal>"
       << "</tr_stdAsympCrownHt>"
       << "<tr_stdCrownHtExp>"
       << "<tr_scheVal species=\"Species_1\">1.0</tr_scheVal>"
       << "<tr_scheVal species=\"Species_2\">1.0</tr_scheVal>"
       << "</tr_stdCrownHtExp>"
       << "<tr_slopeOfHeight-Diam10>"
       << "<tr_sohdVal species=\"Species_1\">0.03418</tr_sohdVal>"
       << "<tr_sohdVal species=\"Species_2\">0.03418</tr_sohdVal>"
       << "</tr_slopeOfHeight-Diam10>"
       << "<tr_slopeOfAsymHeight>"
       << "<tr_soahVal species=\"Species_1\">0.0299</tr_soahVal>"
       << "<tr_soahVal species=\"Species_2\">0.0299</tr_soahVal>"
       << "</tr_slopeOfAsymHeight>"
       << "<tr_whatSeedlingHeightDiam>"
       << "<tr_wsehdVal species=\"Species_1\">0</tr_wsehdVal>"
       << "<tr_wsehdVal species=\"Species_2\">0</tr_wsehdVal>"
       << "</tr_whatSeedlingHeightDiam>"
       << "<tr_whatSaplingHeightDiam>"
       << "<tr_wsahdVal species=\"Species_1\">0</tr_wsahdVal>"
       << "<tr_wsahdVal species=\"Species_2\">0</tr_wsahdVal>"
       << "</tr_whatSaplingHeightDiam>"
       << "<tr_whatAdultHeightDiam>"
       << "<tr_wahdVal species=\"Species_1\">0</tr_wahdVal>"
       << "<tr_wahdVal species=\"Species_2\">0</tr_wahdVal>"
       << "</tr_whatAdultHeightDiam>"
       << "<tr_whatAdultCrownRadDiam>"
       << "<tr_wacrdVal species=\"Species_1\">0</tr_wacrdVal>"
       << "<tr_wacrdVal species=\"Species_2\">0</tr_wacrdVal>"
       << "</tr_whatAdultCrownRadDiam>"
       << "<tr_whatAdultCrownHeightHeight>"
       << "<tr_wachhVal species=\"Species_1\">0</tr_wachhVal>"
       << "<tr_wachhVal species=\"Species_2\">0</tr_wachhVal>"
       << "</tr_whatAdultCrownHeightHeight>"
       << "<tr_whatSaplingCrownRadDiam>"
       << "<tr_wscrdVal species=\"Species_1\">0</tr_wscrdVal>"
       << "<tr_wscrdVal species=\"Species_2\">0</tr_wscrdVal>"
       << "</tr_whatSaplingCrownRadDiam>"
       << "<tr_whatSaplingCrownHeightHeight>"
       << "<tr_wschhVal species=\"Species_1\">0</tr_wschhVal>"
       << "<tr_wschhVal species=\"Species_2\">0</tr_wschhVal>"
       << "</tr_whatSaplingCrownHeightHeight>"
       << "</allometry>";

  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>TempDependentNeighborhoodSurvival</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Seedling\"/>"
       << "<applyTo species=\"Species_2\" type=\"Seedling\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>RemoveDead</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>2</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Seedling\"/>"
       << "<applyTo species=\"Species_2\" type=\"Seedling\"/>"
       << "</behavior>"
       << "</behaviorList>"
       << "<TempDependentNeighborhoodSurvival1>"
       << "<mo_tempDepNeighM>"
       << "<mo_tdnmVal species=\"Species_1\">5</mo_tdnmVal>"
       << "<mo_tdnmVal species=\"Species_2\">15</mo_tdnmVal>"
       << "</mo_tempDepNeighM>"
       << "<mo_tempDepNeighN>"
       << "<mo_tdnnVal species=\"Species_1\">6.88</mo_tdnnVal>"
       << "<mo_tdnnVal species=\"Species_2\">139.57</mo_tdnnVal>"
       << "</mo_tempDepNeighN>"
       << "<mo_tempDepNeighA>"
       << "<mo_tdnaVal species=\"Species_1\">0.1</mo_tdnaVal>"
       << "<mo_tdnaVal species=\"Species_2\">2</mo_tdnaVal>"
       << "</mo_tempDepNeighA>"
       << "<mo_tempDepNeighB>"
       << "<mo_tdnbVal species=\"Species_1\">0.1</mo_tdnbVal>"
       << "<mo_tdnbVal species=\"Species_2\">0.9</mo_tdnbVal>"
       << "</mo_tempDepNeighB>"
       << "<mo_tempDepNeighRadius>-10</mo_tempDepNeighRadius>"
       << "</TempDependentNeighborhoodSurvival1>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}
