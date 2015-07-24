//---------------------------------------------------------------------------
// TestClimateCompDepNeighborhoodSurvival.cpp
//---------------------------------------------------------------------------
#include "TestClimateCompDepNeighborhoodSurvival.h"
#include <gtest/gtest.h>
#include "SimManager.h"
#include "TreePopulation.h"
#include "Grid.h"
#include "BehaviorBase.h"
#include "Plot.h"
#include <math.h>
#include <fstream>

/////////////////////////////////////////////////////////////////////////////
// TestClimateCompDepNeighborhoodSurvival1()
/////////////////////////////////////////////////////////////////////////////
TEST(ClimateCompDepNeighborhoodSurvival, TestClimateCompDepNeighborhoodSurvival1) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
  //Feed our file to the sim manager
  p_oSimManager->ReadFile(WriteClimateCompDepNeighborhoodSurvivalXMLFile(1));

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

  p_oSurvGrid = p_oSimManager->GetGridObject("Climate Comp Dep Neighborhood Survival");

  //Check the grid values
  iCellX = 2; iCellY = 2;
  fExpectedSurvival1 = 0.361816526;
  fExpectedSurvival2 = 0.905386815;
  fExpectedSurvival3 = 0.664333738;
  p_oSurvGrid->GetValueOfCell(iCellX, iCellY, p_oSurvGrid->GetFloatDataCode("survival_1"), &fSurvival);
  EXPECT_LT(fabs(fSurvival - fExpectedSurvival1), 0.0001);
  p_oSurvGrid->GetValueOfCell(iCellX, iCellY, p_oSurvGrid->GetFloatDataCode("survival_2"), &fSurvival);
  EXPECT_LT(fabs(fSurvival - fExpectedSurvival2), 0.0001);
  p_oSurvGrid->GetValueOfCell(iCellX, iCellY, p_oSurvGrid->GetFloatDataCode("survival_3"), &fSurvival);
  EXPECT_LT(fabs(fSurvival - fExpectedSurvival3), 0.0001);

  iCellX = 5; iCellY = 6;
  fExpectedSurvival1 = 0.329286795;
  fExpectedSurvival2 = 0.281273977;
  fExpectedSurvival3 = 0.040343609;
  p_oSurvGrid->GetValueOfCell(iCellX, iCellY, p_oSurvGrid->GetFloatDataCode("survival_1"), &fSurvival);
  EXPECT_LT(fabs(fSurvival - fExpectedSurvival1), 0.0001);
  p_oSurvGrid->GetValueOfCell(iCellX, iCellY, p_oSurvGrid->GetFloatDataCode("survival_2"), &fSurvival);
  EXPECT_LT(fabs(fSurvival - fExpectedSurvival2), 0.0001);
  p_oSurvGrid->GetValueOfCell(iCellX, iCellY, p_oSurvGrid->GetFloatDataCode("survival_3"), &fSurvival);
  EXPECT_LT(fabs(fSurvival - fExpectedSurvival3), 0.0001);

  iCellX = 6; iCellY = 5;
  fExpectedSurvival1 = 0.334927509;
  fExpectedSurvival2 = 0.744741925;
  fExpectedSurvival3 = 0.485067696;
  p_oSurvGrid->GetValueOfCell(iCellX, iCellY, p_oSurvGrid->GetFloatDataCode("survival_1"), &fSurvival);
  EXPECT_LT(fabs(fSurvival - fExpectedSurvival1), 0.0001);
  p_oSurvGrid->GetValueOfCell(iCellX, iCellY, p_oSurvGrid->GetFloatDataCode("survival_2"), &fSurvival);
  EXPECT_LT(fabs(fSurvival - fExpectedSurvival2), 0.0001);
  p_oSurvGrid->GetValueOfCell(iCellX, iCellY, p_oSurvGrid->GetFloatDataCode("survival_3"), &fSurvival);
  EXPECT_LT(fabs(fSurvival - fExpectedSurvival3), 0.0001);

  iCellX = 5; iCellY = 5;
  fExpectedSurvival1 = 0.339999275;
  fExpectedSurvival2 = 0.880523828;
  fExpectedSurvival3 = 0.645292471;
  p_oSurvGrid->GetValueOfCell(iCellX, iCellY, p_oSurvGrid->GetFloatDataCode("survival_1"), &fSurvival);
  EXPECT_LT(fabs(fSurvival - fExpectedSurvival1), 0.0001);
  p_oSurvGrid->GetValueOfCell(iCellX, iCellY, p_oSurvGrid->GetFloatDataCode("survival_2"), &fSurvival);
  EXPECT_LT(fabs(fSurvival - fExpectedSurvival2), 0.0001);
  p_oSurvGrid->GetValueOfCell(iCellX, iCellY, p_oSurvGrid->GetFloatDataCode("survival_3"), &fSurvival);
  EXPECT_LT(fabs(fSurvival - fExpectedSurvival3), 0.0001);

  iCellX = 6; iCellY = 6;
  fExpectedSurvival1 = 0.330594798;
  fExpectedSurvival2 = 0.40929029;
  fExpectedSurvival3 = 0.115934249;
  p_oSurvGrid->GetValueOfCell(iCellX, iCellY, p_oSurvGrid->GetFloatDataCode("survival_1"), &fSurvival);
  EXPECT_LT(fabs(fSurvival - fExpectedSurvival1), 0.0001);
  p_oSurvGrid->GetValueOfCell(iCellX, iCellY, p_oSurvGrid->GetFloatDataCode("survival_2"), &fSurvival);
  EXPECT_LT(fabs(fSurvival - fExpectedSurvival2), 0.0001);
  p_oSurvGrid->GetValueOfCell(iCellX, iCellY, p_oSurvGrid->GetFloatDataCode("survival_3"), &fSurvival);
  EXPECT_LT(fabs(fSurvival - fExpectedSurvival3), 0.0001);

  iCellX = 7; iCellY = 6;
  fExpectedSurvival1 = 0.331153639;
  fExpectedSurvival2 = 0.463390775;
  fExpectedSurvival3 = 0.160873157;
  p_oSurvGrid->GetValueOfCell(iCellX, iCellY, p_oSurvGrid->GetFloatDataCode("survival_1"), &fSurvival);
  EXPECT_LT(fabs(fSurvival - fExpectedSurvival1), 0.0001);
  p_oSurvGrid->GetValueOfCell(iCellX, iCellY, p_oSurvGrid->GetFloatDataCode("survival_2"), &fSurvival);
  EXPECT_LT(fabs(fSurvival - fExpectedSurvival2), 0.0001);
  p_oSurvGrid->GetValueOfCell(iCellX, iCellY, p_oSurvGrid->GetFloatDataCode("survival_3"), &fSurvival);
  EXPECT_LT(fabs(fSurvival - fExpectedSurvival3), 0.0001);

  iCellX = 6; iCellY = 7;
  fExpectedSurvival1 = 0.328223294;
  fExpectedSurvival2 = 0.185719259;
  fExpectedSurvival3 = 0.011445223;
  p_oSurvGrid->GetValueOfCell(iCellX, iCellY, p_oSurvGrid->GetFloatDataCode("survival_1"), &fSurvival);
  EXPECT_LT(fabs(fSurvival - fExpectedSurvival1), 0.0001);
  p_oSurvGrid->GetValueOfCell(iCellX, iCellY, p_oSurvGrid->GetFloatDataCode("survival_2"), &fSurvival);
  EXPECT_LT(fabs(fSurvival - fExpectedSurvival2), 0.0001);
  p_oSurvGrid->GetValueOfCell(iCellX, iCellY, p_oSurvGrid->GetFloatDataCode("survival_3"), &fSurvival);
  EXPECT_LT(fabs(fSurvival - fExpectedSurvival3), 0.0001);

  //Count the seedlings in each grid cell
  p_oAllTrees = p_oPop->Find("type=1");

  //Grid cell 2, 2
  iExpectedSpecies1 = 361;
  iExpectedSpecies2 = 905;
  iExpectedSpecies3 = 664;
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
  iExpectedSpecies1 = 329;
  iExpectedSpecies2 = 281;
  iExpectedSpecies3 = 40;
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
  EXPECT_LT(fabs(iNumSpecies1 - iExpectedSpecies1)/iExpectedSpecies1, 0.15);
  EXPECT_LT(fabs(iNumSpecies2 - iExpectedSpecies2)/iExpectedSpecies2, 0.1);
  EXPECT_LT(fabs(iNumSpecies3 - iExpectedSpecies3)/iExpectedSpecies3, 0.2);
  p_oAllTrees->StartOver();

  //Grid cell 6, 5
  iExpectedSpecies1 = 334;
  iExpectedSpecies2 = 744;
  iExpectedSpecies3 = 485;
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
  iExpectedSpecies1 = 339;
  iExpectedSpecies2 = 880;
  iExpectedSpecies3 = 645;
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
  iExpectedSpecies1 = 330;
  iExpectedSpecies2 = 409;
  iExpectedSpecies3 = 115;
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
  iExpectedSpecies1 = 331;
  iExpectedSpecies2 = 463;
  iExpectedSpecies3 = 160;
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
  iExpectedSpecies1 = 328;
  iExpectedSpecies2 = 185;
  iExpectedSpecies3 = 11;
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
  EXPECT_TRUE(iNumSpecies3 > 3 && iNumSpecies3 < 20);
  p_oAllTrees->StartOver();


  //Update temp, recharge the seedling pool, run again
  p_oTree = p_oAllTrees->NextTree();
  while (p_oTree) {
    p_oPop->KillTree(p_oTree, remove_tree);
    p_oTree = p_oAllTrees->NextTree();
  }
  clPlot *p_oPlot = p_oSimManager->GetPlotObject();
  p_oPlot->SetMeanAnnualTemp(20);
  p_oPlot->SetWaterDeficit(320);

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
  fExpectedSurvival1 = 0.426546141;
  fExpectedSurvival2 = 0.90904958;
  fExpectedSurvival3 = 0.458388037;
  p_oSurvGrid->GetValueOfCell(iCellX, iCellY, p_oSurvGrid->GetFloatDataCode("survival_1"), &fSurvival);
  EXPECT_LT(fabs(fSurvival - fExpectedSurvival1), 0.0001);
  p_oSurvGrid->GetValueOfCell(iCellX, iCellY, p_oSurvGrid->GetFloatDataCode("survival_2"), &fSurvival);
  EXPECT_LT(fabs(fSurvival - fExpectedSurvival2), 0.0001);
  p_oSurvGrid->GetValueOfCell(iCellX, iCellY, p_oSurvGrid->GetFloatDataCode("survival_3"), &fSurvival);
  EXPECT_LT(fabs(fSurvival - fExpectedSurvival3), 0.0001);

  iCellX = 5; iCellY = 6;
  fExpectedSurvival1 = 0.388196783;
  fExpectedSurvival2 = 0.282411878;
  fExpectedSurvival3 = 0.027836954;
  p_oSurvGrid->GetValueOfCell(iCellX, iCellY, p_oSurvGrid->GetFloatDataCode("survival_1"), &fSurvival);
  EXPECT_LT(fabs(fSurvival - fExpectedSurvival1), 0.0001);
  p_oSurvGrid->GetValueOfCell(iCellX, iCellY, p_oSurvGrid->GetFloatDataCode("survival_2"), &fSurvival);
  EXPECT_LT(fabs(fSurvival - fExpectedSurvival2), 0.0001);
  p_oSurvGrid->GetValueOfCell(iCellX, iCellY, p_oSurvGrid->GetFloatDataCode("survival_3"), &fSurvival);
  EXPECT_LT(fabs(fSurvival - fExpectedSurvival3), 0.0001);

  iCellX = 6; iCellY = 5;
  fExpectedSurvival1 = 0.394846631;
  fExpectedSurvival2 = 0.747754797;
  fExpectedSurvival3 = 0.334695073;
  p_oSurvGrid->GetValueOfCell(iCellX, iCellY, p_oSurvGrid->GetFloatDataCode("survival_1"), &fSurvival);
  EXPECT_LT(fabs(fSurvival - fExpectedSurvival1), 0.0001);
  p_oSurvGrid->GetValueOfCell(iCellX, iCellY, p_oSurvGrid->GetFloatDataCode("survival_2"), &fSurvival);
  EXPECT_LT(fabs(fSurvival - fExpectedSurvival2), 0.0001);
  p_oSurvGrid->GetValueOfCell(iCellX, iCellY, p_oSurvGrid->GetFloatDataCode("survival_3"), &fSurvival);
  EXPECT_LT(fabs(fSurvival - fExpectedSurvival3), 0.0001);

  iCellX = 5; iCellY = 5;
  fExpectedSurvival1 = 0.400825745;
  fExpectedSurvival2 = 0.884086009;
  fExpectedSurvival3 = 0.445249627;
  p_oSurvGrid->GetValueOfCell(iCellX, iCellY, p_oSurvGrid->GetFloatDataCode("survival_1"), &fSurvival);
  EXPECT_LT(fabs(fSurvival - fExpectedSurvival1), 0.0001);
  p_oSurvGrid->GetValueOfCell(iCellX, iCellY, p_oSurvGrid->GetFloatDataCode("survival_2"), &fSurvival);
  EXPECT_LT(fabs(fSurvival - fExpectedSurvival2), 0.0001);
  p_oSurvGrid->GetValueOfCell(iCellX, iCellY, p_oSurvGrid->GetFloatDataCode("survival_3"), &fSurvival);
  EXPECT_LT(fabs(fSurvival - fExpectedSurvival3), 0.0001);

  iCellX = 6; iCellY = 6;
  fExpectedSurvival1 = 0.38973879;
  fExpectedSurvival2 = 0.410946084;
  fExpectedSurvival3 = 0.079994241;
  p_oSurvGrid->GetValueOfCell(iCellX, iCellY, p_oSurvGrid->GetFloatDataCode("survival_1"), &fSurvival);
  EXPECT_LT(fabs(fSurvival - fExpectedSurvival1), 0.0001);
  p_oSurvGrid->GetValueOfCell(iCellX, iCellY, p_oSurvGrid->GetFloatDataCode("survival_2"), &fSurvival);
  EXPECT_LT(fabs(fSurvival - fExpectedSurvival2), 0.0001);
  p_oSurvGrid->GetValueOfCell(iCellX, iCellY, p_oSurvGrid->GetFloatDataCode("survival_3"), &fSurvival);
  EXPECT_LT(fabs(fSurvival - fExpectedSurvival3), 0.0001);

  iCellX = 7; iCellY = 6;
  fExpectedSurvival1 = 0.390397609;
  fExpectedSurvival2 = 0.465265434;
  fExpectedSurvival3 = 0.111001935;
  p_oSurvGrid->GetValueOfCell(iCellX, iCellY, p_oSurvGrid->GetFloatDataCode("survival_1"), &fSurvival);
  EXPECT_LT(fabs(fSurvival - fExpectedSurvival1), 0.0001);
  p_oSurvGrid->GetValueOfCell(iCellX, iCellY, p_oSurvGrid->GetFloatDataCode("survival_2"), &fSurvival);
  EXPECT_LT(fabs(fSurvival - fExpectedSurvival2), 0.0001);
  p_oSurvGrid->GetValueOfCell(iCellX, iCellY, p_oSurvGrid->GetFloatDataCode("survival_3"), &fSurvival);
  EXPECT_LT(fabs(fSurvival - fExpectedSurvival3), 0.0001);

  iCellX = 6; iCellY = 7;
  fExpectedSurvival1 = 0.386943021;
  fExpectedSurvival2 = 0.186470591;
  fExpectedSurvival3 = 0.007897165;
  p_oSurvGrid->GetValueOfCell(iCellX, iCellY, p_oSurvGrid->GetFloatDataCode("survival_1"), &fSurvival);
  EXPECT_LT(fabs(fSurvival - fExpectedSurvival1), 0.0001);
  p_oSurvGrid->GetValueOfCell(iCellX, iCellY, p_oSurvGrid->GetFloatDataCode("survival_2"), &fSurvival);
  EXPECT_LT(fabs(fSurvival - fExpectedSurvival2), 0.0001);
  p_oSurvGrid->GetValueOfCell(iCellX, iCellY, p_oSurvGrid->GetFloatDataCode("survival_3"), &fSurvival);
  EXPECT_LT(fabs(fSurvival - fExpectedSurvival3), 0.0001);

  //Count the seedlings in each grid cell
  p_oAllTrees = p_oPop->Find("type=1");

  //Grid cell 2, 2
  iExpectedSpecies1 = 426;
  iExpectedSpecies2 = 909;
  iExpectedSpecies3 = 458;
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
  iExpectedSpecies1 = 388;
  iExpectedSpecies2 = 282;
  iExpectedSpecies3 = 27;
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
  EXPECT_TRUE(iNumSpecies3 > 15 && iNumSpecies3 < 45);
  p_oAllTrees->StartOver();

  //Grid cell 6, 5
  iExpectedSpecies1 = 394;
  iExpectedSpecies2 = 747;
  iExpectedSpecies3 = 334;
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
  iExpectedSpecies1 = 400;
  iExpectedSpecies2 = 884;
  iExpectedSpecies3 = 445;
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
  iExpectedSpecies1 = 389;
  iExpectedSpecies2 = 410;
  iExpectedSpecies3 = 79;
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
  EXPECT_LT(fabs(iNumSpecies3 - iExpectedSpecies3)/iExpectedSpecies3, 0.2);
  p_oAllTrees->StartOver();

  //Grid cell 7, 6
  iExpectedSpecies1 = 390;
  iExpectedSpecies2 = 465;
  iExpectedSpecies3 = 111;
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
  iExpectedSpecies1 = 386;
  iExpectedSpecies2 = 186;
  iExpectedSpecies3 = 7;
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
  EXPECT_LT(iNumSpecies3, 20);

  delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}


/////////////////////////////////////////////////////////////////////////////
// TestClimateCompDepNeighborhoodSurvival2()
/////////////////////////////////////////////////////////////////////////////
TEST(ClimateCompDepNeighborhoodSurvival, TestClimateCompDepNeighborhoodSurvival2) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
try {
  //Feed our file to the sim manager
  p_oSimManager->ReadFile(WriteClimateCompDepNeighborhoodSurvivalXMLFile(3));

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

  p_oSurvGrid = p_oSimManager->GetGridObject("Climate Comp Dep Neighborhood Survival");

  //Check the grid values
  iCellX = 2; iCellY = 2;
  fExpectedSurvival1 = 0.047365835;
  fExpectedSurvival2 = 0.742168465;
  fExpectedSurvival3 = 0.293196598;
  p_oSurvGrid->GetValueOfCell(iCellX, iCellY, p_oSurvGrid->GetFloatDataCode("survival_1"), &fSurvival);
  EXPECT_LT(fabs(fSurvival - fExpectedSurvival1), 0.0001);
  p_oSurvGrid->GetValueOfCell(iCellX, iCellY, p_oSurvGrid->GetFloatDataCode("survival_2"), &fSurvival);
  EXPECT_LT(fabs(fSurvival - fExpectedSurvival2), 0.0001);
  p_oSurvGrid->GetValueOfCell(iCellX, iCellY, p_oSurvGrid->GetFloatDataCode("survival_3"), &fSurvival);
  EXPECT_LT(fabs(fSurvival - fExpectedSurvival3), 0.0001);

  iCellX = 5; iCellY = 6;
  fExpectedSurvival1 = 0.035704499;
  fExpectedSurvival2 = 0.022253005;
  fExpectedSurvival3 = 6.56635E-05;
  p_oSurvGrid->GetValueOfCell(iCellX, iCellY, p_oSurvGrid->GetFloatDataCode("survival_1"), &fSurvival);
  EXPECT_LT(fabs(fSurvival - fExpectedSurvival1), 0.0001);
  p_oSurvGrid->GetValueOfCell(iCellX, iCellY, p_oSurvGrid->GetFloatDataCode("survival_2"), &fSurvival);
  EXPECT_LT(fabs(fSurvival - fExpectedSurvival2), 0.0001);
  p_oSurvGrid->GetValueOfCell(iCellX, iCellY, p_oSurvGrid->GetFloatDataCode("survival_3"), &fSurvival);
  EXPECT_LT(fabs(fSurvival - fExpectedSurvival3), 0.0001);

  iCellX = 6; iCellY = 5;
  fExpectedSurvival1 = 0.037570974;
  fExpectedSurvival2 = 0.41306406;
  fExpectedSurvival3 = 0.114131903;
  p_oSurvGrid->GetValueOfCell(iCellX, iCellY, p_oSurvGrid->GetFloatDataCode("survival_1"), &fSurvival);
  EXPECT_LT(fabs(fSurvival - fExpectedSurvival1), 0.0001);
  p_oSurvGrid->GetValueOfCell(iCellX, iCellY, p_oSurvGrid->GetFloatDataCode("survival_2"), &fSurvival);
  EXPECT_LT(fabs(fSurvival - fExpectedSurvival2), 0.0001);
  p_oSurvGrid->GetValueOfCell(iCellX, iCellY, p_oSurvGrid->GetFloatDataCode("survival_3"), &fSurvival);
  EXPECT_LT(fabs(fSurvival - fExpectedSurvival3), 0.0001);

  iCellX = 5; iCellY = 5;
  fExpectedSurvival1 = 0.039303748;
  fExpectedSurvival2 = 0.682689683;
  fExpectedSurvival3 = 0.268701317;
  p_oSurvGrid->GetValueOfCell(iCellX, iCellY, p_oSurvGrid->GetFloatDataCode("survival_1"), &fSurvival);
  EXPECT_LT(fabs(fSurvival - fExpectedSurvival1), 0.0001);
  p_oSurvGrid->GetValueOfCell(iCellX, iCellY, p_oSurvGrid->GetFloatDataCode("survival_2"), &fSurvival);
  EXPECT_LT(fabs(fSurvival - fExpectedSurvival2), 0.0001);
  p_oSurvGrid->GetValueOfCell(iCellX, iCellY, p_oSurvGrid->GetFloatDataCode("survival_3"), &fSurvival);
  EXPECT_LT(fabs(fSurvival - fExpectedSurvival3), 0.0001);

  iCellX = 6; iCellY = 6;
  fExpectedSurvival1 = 0.036131671;
  fExpectedSurvival2 = 0.068563712;
  fExpectedSurvival3 = 0.001558243;
  p_oSurvGrid->GetValueOfCell(iCellX, iCellY, p_oSurvGrid->GetFloatDataCode("survival_1"), &fSurvival);
  EXPECT_LT(fabs(fSurvival - fExpectedSurvival1), 0.0001);
  p_oSurvGrid->GetValueOfCell(iCellX, iCellY, p_oSurvGrid->GetFloatDataCode("survival_2"), &fSurvival);
  EXPECT_LT(fabs(fSurvival - fExpectedSurvival2), 0.0001);
  p_oSurvGrid->GetValueOfCell(iCellX, iCellY, p_oSurvGrid->GetFloatDataCode("survival_3"), &fSurvival);
  EXPECT_LT(fabs(fSurvival - fExpectedSurvival3), 0.0001);

  iCellX = 7; iCellY = 6;
  fExpectedSurvival1 = 0.036315213;
  fExpectedSurvival2 = 0.099504369;
  fExpectedSurvival3 = 0.004163425;
  p_oSurvGrid->GetValueOfCell(iCellX, iCellY, p_oSurvGrid->GetFloatDataCode("survival_1"), &fSurvival);
  EXPECT_LT(fabs(fSurvival - fExpectedSurvival1), 0.0001);
  p_oSurvGrid->GetValueOfCell(iCellX, iCellY, p_oSurvGrid->GetFloatDataCode("survival_2"), &fSurvival);
  EXPECT_LT(fabs(fSurvival - fExpectedSurvival2), 0.0001);
  p_oSurvGrid->GetValueOfCell(iCellX, iCellY, p_oSurvGrid->GetFloatDataCode("survival_3"), &fSurvival);
  EXPECT_LT(fabs(fSurvival - fExpectedSurvival3), 0.0001);

  iCellX = 6; iCellY = 7;
  fExpectedSurvival1 = 0.03535967;
  fExpectedSurvival2 = 0.006405762;
  fExpectedSurvival3 = 1.49925E-06;
  p_oSurvGrid->GetValueOfCell(iCellX, iCellY, p_oSurvGrid->GetFloatDataCode("survival_1"), &fSurvival);
  EXPECT_LT(fabs(fSurvival - fExpectedSurvival1), 0.0001);
  p_oSurvGrid->GetValueOfCell(iCellX, iCellY, p_oSurvGrid->GetFloatDataCode("survival_2"), &fSurvival);
  EXPECT_LT(fabs(fSurvival - fExpectedSurvival2), 0.0001);
  p_oSurvGrid->GetValueOfCell(iCellX, iCellY, p_oSurvGrid->GetFloatDataCode("survival_3"), &fSurvival);
  EXPECT_LT(fabs(fSurvival - fExpectedSurvival3), 0.0001);

  //Count the seedlings in each grid cell
  p_oAllTrees = p_oPop->Find("type=1");

  //Grid cell 2, 2
  iExpectedSpecies1 = 47;
  iExpectedSpecies2 = 742;
  iExpectedSpecies3 = 293;
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
  EXPECT_TRUE(iNumSpecies1 > 30 && iNumSpecies1 < 65);
  EXPECT_LT(fabs(iNumSpecies2 - iExpectedSpecies2)/iExpectedSpecies2, 0.1);
  EXPECT_LT(fabs(iNumSpecies3 - iExpectedSpecies3)/iExpectedSpecies3, 0.1);
  p_oAllTrees->StartOver();

  //Grid cell 5, 6
  iExpectedSpecies1 = 35;
  iExpectedSpecies2 = 22;
  iExpectedSpecies3 = 0.06;
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
  EXPECT_TRUE(iNumSpecies1 > 20 && iNumSpecies1 < 50);
  EXPECT_TRUE(iNumSpecies2 > 10 && iNumSpecies2 < 45);
  EXPECT_LT(iNumSpecies3 , 10);
  p_oAllTrees->StartOver();

  //Grid cell 6, 5
  iExpectedSpecies1 = 37;
  iExpectedSpecies2 = 413;
  iExpectedSpecies3 = 114;
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
  EXPECT_TRUE(iNumSpecies1 > 20 && iNumSpecies1 < 50);
  EXPECT_LT(fabs(iNumSpecies2 - iExpectedSpecies2)/iExpectedSpecies2, 0.1);
  EXPECT_LT(fabs(iNumSpecies3 - iExpectedSpecies3)/iExpectedSpecies3, 0.1);
  p_oAllTrees->StartOver();

  //Grid cell 5, 5
  iExpectedSpecies1 = 39;
  iExpectedSpecies2 = 682;
  iExpectedSpecies3 = 268;
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
  EXPECT_TRUE(iNumSpecies1 > 20 && iNumSpecies1 < 60);
  EXPECT_LT(fabs(iNumSpecies2 - iExpectedSpecies2)/iExpectedSpecies2, 0.1);
  EXPECT_LT(fabs(iNumSpecies3 - iExpectedSpecies3)/iExpectedSpecies3, 0.1);
  p_oAllTrees->StartOver();

  //Grid cell 6, 6
  iExpectedSpecies1 = 36;
  iExpectedSpecies2 = 68;
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
  EXPECT_TRUE(iNumSpecies1 > 20 && iNumSpecies1 < 50);
  EXPECT_LT(fabs(iNumSpecies2 - iExpectedSpecies2)/iExpectedSpecies2, 0.2);
  EXPECT_LT(iNumSpecies3, 7);
  p_oAllTrees->StartOver();

  //Grid cell 7, 6
  iExpectedSpecies1 = 36;
  iExpectedSpecies2 = 99;
  iExpectedSpecies3 = 4;
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
  EXPECT_TRUE(iNumSpecies1 > 20 && iNumSpecies1 < 50);
  EXPECT_LT(fabs(iNumSpecies2 - iExpectedSpecies2)/iExpectedSpecies2, 0.1);
  EXPECT_LT(iNumSpecies3, 5);
  p_oAllTrees->StartOver();

  //Grid cell 6, 7
  iExpectedSpecies1 = 35;
  iExpectedSpecies2 = 6;
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
  EXPECT_TRUE(iNumSpecies1 > 20 && iNumSpecies1 < 50);
  EXPECT_LT(iNumSpecies2, 15);
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
  p_oPlot->SetWaterDeficit(320);

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
  fExpectedSurvival1 = 0.077606492;
  fExpectedSurvival2 = 0.751212337;
  fExpectedSurvival3 = 0.096316308;
  p_oSurvGrid->GetValueOfCell(iCellX, iCellY, p_oSurvGrid->GetFloatDataCode("survival_1"), &fSurvival);
  EXPECT_LT(fabs(fSurvival - fExpectedSurvival1), 0.0001);
  p_oSurvGrid->GetValueOfCell(iCellX, iCellY, p_oSurvGrid->GetFloatDataCode("survival_2"), &fSurvival);
  EXPECT_LT(fabs(fSurvival - fExpectedSurvival2), 0.0001);
  p_oSurvGrid->GetValueOfCell(iCellX, iCellY, p_oSurvGrid->GetFloatDataCode("survival_3"), &fSurvival);
  EXPECT_LT(fabs(fSurvival - fExpectedSurvival3), 0.0001);

  iCellX = 5; iCellY = 6;
  fExpectedSurvival1 = 0.058499991;
  fExpectedSurvival2 = 0.022524174;
  fExpectedSurvival3 = 2.15707E-05;
  p_oSurvGrid->GetValueOfCell(iCellX, iCellY, p_oSurvGrid->GetFloatDataCode("survival_1"), &fSurvival);
  EXPECT_LT(fabs(fSurvival - fExpectedSurvival1), 0.0001);
  p_oSurvGrid->GetValueOfCell(iCellX, iCellY, p_oSurvGrid->GetFloatDataCode("survival_2"), &fSurvival);
  EXPECT_LT(fabs(fSurvival - fExpectedSurvival2), 0.0001);
  p_oSurvGrid->GetValueOfCell(iCellX, iCellY, p_oSurvGrid->GetFloatDataCode("survival_3"), &fSurvival);
  EXPECT_LT(fabs(fSurvival - fExpectedSurvival3), 0.0001);

  iCellX = 6; iCellY = 5;
  fExpectedSurvival1 = 0.061558115;
  fExpectedSurvival2 = 0.418097551;
  fExpectedSurvival3 = 0.037492807;
  p_oSurvGrid->GetValueOfCell(iCellX, iCellY, p_oSurvGrid->GetFloatDataCode("survival_1"), &fSurvival);
  EXPECT_LT(fabs(fSurvival - fExpectedSurvival1), 0.0001);
  p_oSurvGrid->GetValueOfCell(iCellX, iCellY, p_oSurvGrid->GetFloatDataCode("survival_2"), &fSurvival);
  EXPECT_LT(fabs(fSurvival - fExpectedSurvival2), 0.0001);
  p_oSurvGrid->GetValueOfCell(iCellX, iCellY, p_oSurvGrid->GetFloatDataCode("survival_3"), &fSurvival);
  EXPECT_LT(fabs(fSurvival - fExpectedSurvival3), 0.0001);

  iCellX = 5; iCellY = 5;
  fExpectedSurvival1 = 0.064397176;
  fExpectedSurvival2 = 0.691008761;
  fExpectedSurvival3 = 0.088269506;
  p_oSurvGrid->GetValueOfCell(iCellX, iCellY, p_oSurvGrid->GetFloatDataCode("survival_1"), &fSurvival);
  EXPECT_LT(fabs(fSurvival - fExpectedSurvival1), 0.0001);
  p_oSurvGrid->GetValueOfCell(iCellX, iCellY, p_oSurvGrid->GetFloatDataCode("survival_2"), &fSurvival);
  EXPECT_LT(fabs(fSurvival - fExpectedSurvival2), 0.0001);
  p_oSurvGrid->GetValueOfCell(iCellX, iCellY, p_oSurvGrid->GetFloatDataCode("survival_3"), &fSurvival);
  EXPECT_LT(fabs(fSurvival - fExpectedSurvival3), 0.0001);

  iCellX = 6; iCellY = 6;
  fExpectedSurvival1 = 0.05919989;
  fExpectedSurvival2 = 0.069399212;
  fExpectedSurvival3 = 0.000511889;
  p_oSurvGrid->GetValueOfCell(iCellX, iCellY, p_oSurvGrid->GetFloatDataCode("survival_1"), &fSurvival);
  EXPECT_LT(fabs(fSurvival - fExpectedSurvival1), 0.0001);
  p_oSurvGrid->GetValueOfCell(iCellX, iCellY, p_oSurvGrid->GetFloatDataCode("survival_2"), &fSurvival);
  EXPECT_LT(fabs(fSurvival - fExpectedSurvival2), 0.0001);
  p_oSurvGrid->GetValueOfCell(iCellX, iCellY, p_oSurvGrid->GetFloatDataCode("survival_3"), &fSurvival);
  EXPECT_LT(fabs(fSurvival - fExpectedSurvival3), 0.0001);

  iCellX = 7; iCellY = 6;
  fExpectedSurvival1 = 0.059500614;
  fExpectedSurvival2 = 0.100716904;
  fExpectedSurvival3 = 0.001367703;
  p_oSurvGrid->GetValueOfCell(iCellX, iCellY, p_oSurvGrid->GetFloatDataCode("survival_1"), &fSurvival);
  EXPECT_LT(fabs(fSurvival - fExpectedSurvival1), 0.0001);
  p_oSurvGrid->GetValueOfCell(iCellX, iCellY, p_oSurvGrid->GetFloatDataCode("survival_2"), &fSurvival);
  EXPECT_LT(fabs(fSurvival - fExpectedSurvival2), 0.0001);
  p_oSurvGrid->GetValueOfCell(iCellX, iCellY, p_oSurvGrid->GetFloatDataCode("survival_3"), &fSurvival);
  EXPECT_LT(fabs(fSurvival - fExpectedSurvival3), 0.0001);

  iCellX = 6; iCellY = 7;
  fExpectedSurvival1 = 0.057935005;
  fExpectedSurvival2 = 0.006483821;
  fExpectedSurvival3 = 4.92508E-07;
  p_oSurvGrid->GetValueOfCell(iCellX, iCellY, p_oSurvGrid->GetFloatDataCode("survival_1"), &fSurvival);
  EXPECT_LT(fabs(fSurvival - fExpectedSurvival1), 0.0001);
  p_oSurvGrid->GetValueOfCell(iCellX, iCellY, p_oSurvGrid->GetFloatDataCode("survival_2"), &fSurvival);
  EXPECT_LT(fabs(fSurvival - fExpectedSurvival2), 0.0001);
  p_oSurvGrid->GetValueOfCell(iCellX, iCellY, p_oSurvGrid->GetFloatDataCode("survival_3"), &fSurvival);
  EXPECT_LT(fabs(fSurvival - fExpectedSurvival3), 0.0001);

  //Count the seedlings in each grid cell
  p_oAllTrees = p_oPop->Find("type=1");

  //Grid cell 2, 2
  iExpectedSpecies1 = 77;
  iExpectedSpecies2 = 751;
  iExpectedSpecies3 = 96;
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
  EXPECT_LT(fabs(iNumSpecies3 - iExpectedSpecies3)/iExpectedSpecies3, 0.2);
  p_oAllTrees->StartOver();

  //Grid cell 5, 6
  iExpectedSpecies1 = 58;
  iExpectedSpecies2 = 22;
  iExpectedSpecies3 = 0;
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
  EXPECT_TRUE(iNumSpecies2 > 10 && iNumSpecies2 < 40);
  EXPECT_LT(iNumSpecies3, 6);
  p_oAllTrees->StartOver();

  //Grid cell 6, 5
  iExpectedSpecies1 = 61;
  iExpectedSpecies2 = 418;
  iExpectedSpecies3 = 37;
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
  EXPECT_TRUE(iNumSpecies3 > 25 && iNumSpecies3 < 55);
  p_oAllTrees->StartOver();

  //Grid cell 5, 5
  iExpectedSpecies1 = 64;
  iExpectedSpecies2 = 691;
  iExpectedSpecies3 = 88;
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
  EXPECT_LT(fabs(iNumSpecies3 - iExpectedSpecies3)/iExpectedSpecies3, 0.2);
  p_oAllTrees->StartOver();

  //Grid cell 6, 6
  iExpectedSpecies1 = 59;
  iExpectedSpecies2 = 69;
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
  EXPECT_TRUE(iNumSpecies1 > 40 && iNumSpecies1 < 80);
  EXPECT_TRUE(iNumSpecies2 > 50 && iNumSpecies2 < 90);
  EXPECT_LT(iNumSpecies3, 6);
  p_oAllTrees->StartOver();

  //Grid cell 7, 6
  iExpectedSpecies1 = 59;
  iExpectedSpecies2 = 100;
  iExpectedSpecies3 = 1;
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
  EXPECT_TRUE(iNumSpecies1 > 50 && iNumSpecies1 < 90);
  EXPECT_LT(fabs(iNumSpecies2 - iExpectedSpecies2)/iExpectedSpecies2, 0.2);
  EXPECT_LT(iNumSpecies3, 6);
  p_oAllTrees->StartOver();

  //Grid cell 6, 7
  iExpectedSpecies1 = 57;
  iExpectedSpecies2 = 6;
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
  EXPECT_LT(fabs(iNumSpecies1 - iExpectedSpecies1)/iExpectedSpecies1, 0.2);
  EXPECT_LT(iNumSpecies2, 12);
  EXPECT_LT(iNumSpecies3, 5);
  delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

////////////////////////////////////////////////////////////////////////////
// TestErrorProcessing()
////////////////////////////////////////////////////////////////////////////
TEST(ClimateCompDepNeighborhoodSurvival, TestErrorProcessing) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    p_oSimManager->ReadFile(WriteClimateCompDepNeighborhoodSurvivalXMLErrorFile1());
    FAIL() << "TestClimateCompDepNeighborhoodSurvival error processing didn't catch error for WriteClimateCompDepNeighborhoodSurvivalXMLErrorFile1.";
  } catch (modelErr& err) {
    if (err.sFunction.compare("clClimateCompDepNeighborhoodSurvival::ValidateData") != 0) {
      FAIL() << "TestClimateCompDepNeighborhoodSurvival error processing caught wrong error for WriteClimateCompDepNeighborhoodSurvivalXMLErrorFile1.";
    };
  }

  try {
    p_oSimManager->ReadFile(WriteClimateCompDepNeighborhoodSurvivalXMLErrorFile2());
    FAIL() << "TestClimateCompDepNeighborhoodSurvival error processing didn't catch error for WriteClimateCompDepNeighborhoodSurvivalXMLErrorFile1.";
  } catch (modelErr& err) {
    if (err.sFunction.compare("clClimateCompDepNeighborhoodSurvival::ValidateData") != 0) {
      FAIL() << "TestClimateCompDepNeighborhoodSurvival error processing caught wrong error for WriteClimateCompDepNeighborhoodSurvivalXMLErrorFile1.";
    };
  }

  try {
    p_oSimManager->ReadFile(WriteClimateCompDepNeighborhoodSurvivalXMLErrorFile3());
    FAIL() << "TestClimateCompDepNeighborhoodSurvival error processing didn't catch error for WriteClimateCompDepNeighborhoodSurvivalXMLErrorFile3.";
  } catch (modelErr& err) {
    if (err.sFunction.compare("clClimateCompDepNeighborhoodSurvival::ValidateData") != 0) {
      FAIL() << "TestClimateCompDepNeighborhoodSurvival error processing caught wrong error for WriteClimateCompDepNeighborhoodSurvivalXMLErrorFile3.";
    };
  }

  delete p_oSimManager;
}


/////////////////////////////////////////////////////////////////////////////
// WriteClimateCompDepNeighborhoodSurvivalXMLFile1()
/////////////////////////////////////////////////////////////////////////////
const char* WriteClimateCompDepNeighborhoodSurvivalXMLFile(int iYearsPerTimestep) {
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
       << "<plot_water_deficit>235</plot_water_deficit>"
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
       << "<behaviorName>ClimateCompDepNeighborhoodSurvival</behaviorName>"
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
       << "<ClimateCompDepNeighborhoodSurvival1>"
       << "<mo_climCompDepNeighM>"
       << "<mo_ccdnmVal species=\"Species_2\">9</mo_ccdnmVal>"
       << "<mo_ccdnmVal species=\"Species_3\">15</mo_ccdnmVal>"
       << "<mo_ccdnmVal species=\"Species_4\">9.8</mo_ccdnmVal>"
       << "</mo_climCompDepNeighM>"
       << "<mo_climCompDepNeighN>"
       << "<mo_ccdnnVal species=\"Species_2\">8.53</mo_ccdnnVal>"
       << "<mo_ccdnnVal species=\"Species_3\">139.57</mo_ccdnnVal>"
       << "<mo_ccdnnVal species=\"Species_4\">10</mo_ccdnnVal>"
       << "</mo_climCompDepNeighN>"
       << "<mo_climCompDepNeighA>"
       << "<mo_ccdnaVal species=\"Species_2\">0.1</mo_ccdnaVal>"
       << "<mo_ccdnaVal species=\"Species_3\">2</mo_ccdnaVal>"
       << "<mo_ccdnaVal species=\"Species_4\">5.4</mo_ccdnaVal>"
       << "</mo_climCompDepNeighA>"
       << "<mo_climCompDepNeighB>"
       << "<mo_ccdnbVal species=\"Species_2\">0.1</mo_ccdnbVal>"
       << "<mo_ccdnbVal species=\"Species_3\">0.9</mo_ccdnbVal>"
       << "<mo_ccdnbVal species=\"Species_4\">1.1</mo_ccdnbVal>"
       << "</mo_climCompDepNeighB>"
       << "<mo_climCompDepNeighC>"
       << "<mo_ccdncVal species=\"Species_2\">335</mo_ccdncVal>"
       << "<mo_ccdncVal species=\"Species_3\">278</mo_ccdncVal>"
       << "<mo_ccdncVal species=\"Species_4\">281</mo_ccdncVal>"
       << "</mo_climCompDepNeighC>"
       << "<mo_climCompDepNeighD>"
       << "<mo_ccdndVal species=\"Species_2\">74</mo_ccdndVal>"
       << "<mo_ccdndVal species=\"Species_3\">96.5</mo_ccdndVal>"
       << "<mo_ccdndVal species=\"Species_4\">54.1</mo_ccdndVal>"
       << "</mo_climCompDepNeighD>"
       << "<mo_climCompDepNeighRadius>10</mo_climCompDepNeighRadius>"
       << "</ClimateCompDepNeighborhoodSurvival1>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteClimateCompDepNeighborhoodSurvivalXMLErrorFile1()
/////////////////////////////////////////////////////////////////////////////
const char* WriteClimateCompDepNeighborhoodSurvivalXMLErrorFile1() {
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
       << "<plot_water_deficit>235</plot_water_deficit>"
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
       << "<behaviorName>ClimateCompDepNeighborhoodSurvival</behaviorName>"
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
       << "<ClimateCompDepNeighborhoodSurvival1>"
       << "<mo_climCompDepNeighM>"
       << "<mo_ccdnmVal species=\"Species_1\">5</mo_ccdnmVal>"
       << "<mo_ccdnmVal species=\"Species_2\">15</mo_ccdnmVal>"
       << "</mo_climCompDepNeighM>"
       << "<mo_climCompDepNeighN>"
       << "<mo_ccdnnVal species=\"Species_1\">0</mo_ccdnnVal>"
       << "<mo_ccdnnVal species=\"Species_2\">139.57</mo_ccdnnVal>"
       << "</mo_climCompDepNeighN>"
       << "<mo_climCompDepNeighA>"
       << "<mo_ccdnaVal species=\"Species_1\">0.1</mo_ccdnaVal>"
       << "<mo_ccdnaVal species=\"Species_2\">2</mo_ccdnaVal>"
       << "</mo_climCompDepNeighA>"
       << "<mo_climCompDepNeighB>"
       << "<mo_ccdnbVal species=\"Species_1\">0.1</mo_ccdnbVal>"
       << "<mo_ccdnbVal species=\"Species_2\">0.9</mo_ccdnbVal>"
       << "</mo_climCompDepNeighB>"
       << "<mo_climCompDepNeighC>"
       << "<mo_ccdncVal species=\"Species_1\">335</mo_ccdncVal>"
       << "<mo_ccdncVal species=\"Species_2\">278</mo_ccdncVal>"
       << "</mo_climCompDepNeighC>"
       << "<mo_climCompDepNeighD>"
       << "<mo_ccdndVal species=\"Species_1\">74</mo_ccdndVal>"
       << "<mo_ccdndVal species=\"Species_2\">96.5</mo_ccdndVal>"
       << "</mo_climCompDepNeighD>"

       << "<mo_climCompDepNeighRadius>10</mo_climCompDepNeighRadius>"
       << "</ClimateCompDepNeighborhoodSurvival1>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteClimateCompDepNeighborhoodSurvivalXMLErrorFile2()
/////////////////////////////////////////////////////////////////////////////
const char* WriteClimateCompDepNeighborhoodSurvivalXMLErrorFile2() {
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
       << "<plot_water_deficit>235</plot_water_deficit>"
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
       << "<behaviorName>ClimateCompDepNeighborhoodSurvival</behaviorName>"
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
       << "<ClimateCompDepNeighborhoodSurvival1>"
       << "<mo_climCompDepNeighM>"
       << "<mo_ccdnmVal species=\"Species_1\">5</mo_ccdnmVal>"
       << "<mo_ccdnmVal species=\"Species_2\">15</mo_ccdnmVal>"
       << "</mo_climCompDepNeighM>"
       << "<mo_climCompDepNeighN>"
       << "<mo_ccdnnVal species=\"Species_1\">6.88</mo_ccdnnVal>"
       << "<mo_ccdnnVal species=\"Species_2\">139.57</mo_ccdnnVal>"
       << "</mo_climCompDepNeighN>"
       << "<mo_climCompDepNeighA>"
       << "<mo_ccdnaVal species=\"Species_1\">0.1</mo_ccdnaVal>"
       << "<mo_ccdnaVal species=\"Species_2\">2</mo_ccdnaVal>"
       << "</mo_climCompDepNeighA>"
       << "<mo_climCompDepNeighB>"
       << "<mo_ccdnbVal species=\"Species_1\">0.1</mo_ccdnbVal>"
       << "<mo_ccdnbVal species=\"Species_2\">0.9</mo_ccdnbVal>"
       << "</mo_climCompDepNeighB>"
       << "<mo_climCompDepNeighC>"
       << "<mo_ccdncVal species=\"Species_1\">335</mo_ccdncVal>"
       << "<mo_ccdncVal species=\"Species_2\">278</mo_ccdncVal>"
       << "</mo_climCompDepNeighC>"
       << "<mo_climCompDepNeighD>"
       << "<mo_ccdndVal species=\"Species_1\">74</mo_ccdndVal>"
       << "<mo_ccdndVal species=\"Species_2\">96.5</mo_ccdndVal>"
       << "</mo_climCompDepNeighD>"
       << "<mo_climCompDepNeighRadius>-10</mo_climCompDepNeighRadius>"
       << "</ClimateCompDepNeighborhoodSurvival1>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}


/////////////////////////////////////////////////////////////////////////////
// WriteClimateCompDepNeighborhoodSurvivalXMLErrorFile3()
/////////////////////////////////////////////////////////////////////////////
const char* WriteClimateCompDepNeighborhoodSurvivalXMLErrorFile3() {
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
       << "<plot_water_deficit>235</plot_water_deficit>"
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
       << "<behaviorName>ClimateCompDepNeighborhoodSurvival</behaviorName>"
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
       << "<ClimateCompDepNeighborhoodSurvival1>"
       << "<mo_climCompDepNeighM>"
       << "<mo_ccdnmVal species=\"Species_1\">5</mo_ccdnmVal>"
       << "<mo_ccdnmVal species=\"Species_2\">15</mo_ccdnmVal>"
       << "</mo_climCompDepNeighM>"
       << "<mo_climCompDepNeighN>"
       << "<mo_ccdnnVal species=\"Species_1\">6.88</mo_ccdnnVal>"
       << "<mo_ccdnnVal species=\"Species_2\">139.57</mo_ccdnnVal>"
       << "</mo_climCompDepNeighN>"
       << "<mo_climCompDepNeighA>"
       << "<mo_ccdnaVal species=\"Species_1\">0.1</mo_ccdnaVal>"
       << "<mo_ccdnaVal species=\"Species_2\">2</mo_ccdnaVal>"
       << "</mo_climCompDepNeighA>"
       << "<mo_climCompDepNeighB>"
       << "<mo_ccdnbVal species=\"Species_1\">0.1</mo_ccdnbVal>"
       << "<mo_ccdnbVal species=\"Species_2\">0.9</mo_ccdnbVal>"
       << "</mo_climCompDepNeighB>"
       << "<mo_climCompDepNeighC>"
       << "<mo_ccdncVal species=\"Species_1\">335</mo_ccdncVal>"
       << "<mo_ccdncVal species=\"Species_2\">278</mo_ccdncVal>"
       << "</mo_climCompDepNeighC>"
       << "<mo_climCompDepNeighD>"
       << "<mo_ccdndVal species=\"Species_1\">74</mo_ccdndVal>"
       << "<mo_ccdndVal species=\"Species_2\">0</mo_ccdndVal>"
       << "</mo_climCompDepNeighD>"
       << "<mo_climCompDepNeighRadius>10</mo_climCompDepNeighRadius>"
       << "</ClimateCompDepNeighborhoodSurvival1>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}
