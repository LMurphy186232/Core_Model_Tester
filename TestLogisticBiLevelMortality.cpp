//---------------------------------------------------------------------------
// TestLogisticBiLevelMortality.cpp
//---------------------------------------------------------------------------
#include "TestLogisticBiLevelMortality.h"
#include <gtest/gtest.h>
#include "SimManager.h"
#include "TreePopulation.h"
#include "Grid.h"
#include "BehaviorBase.h"
#include <fstream>
#include <math.h>

/////////////////////////////////////////////////////////////////////////////
// NormalProcessingRun1()
// Tests normal processing run 1. WriteLogisticBiLevelMortalityXMLFile1() does
// setup. Timestep length is 1 year and there is a light grid present. 1000
// copies of each of 27 trees is created of 3 species and assigned to a mix of
// light levels. Then mortality is run. We check the number left of each tree
// type to see if it is approximately the right number.
/////////////////////////////////////////////////////////////////////////////
TEST(LogisticBiLevelMortality, NormalProcessingRun1) {
  clTreePopulation * p_oPop;
  clGrid *p_oStormLight;
  clTreeSearch *p_oAllTrees;
  clTree *p_oTree;
  float fDiam, fY, fExpected;
  int *p_iNumTrees = new int[27], i, iSpecies, iType;

  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    for (i = 0; i < 27; i++) {
      p_iNumTrees[i] = 0;
    }

    p_oSimManager->ReadFile(WriteLogisticBiLevelMortalityXMLFile1());
    p_oPop = (clTreePopulation *) p_oSimManager->GetPopulationObject("treepopulation");
    p_oStormLight = p_oSimManager->GetGridObject("Storm Light");

    //Set our grid values
    fDiam = 15;
    p_oStormLight->SetValueOfCell(0, 0, p_oStormLight->GetFloatDataCode("Light"),
        fDiam);
    fDiam = 35;
    p_oStormLight->SetValueOfCell(0, 1, p_oStormLight->GetFloatDataCode("Light"),
        fDiam);
    fDiam = 80;
    p_oStormLight->SetValueOfCell(0, 2, p_oStormLight->GetFloatDataCode("Light"),
        fDiam);

    //Add 1000 trees to the plot of each kind
    for (i = 0; i < 1000; i++) {
      fDiam = 0.1;
      iSpecies = 0;
      iType = clTreePopulation::seedling;
      p_oTree = p_oPop->CreateTree(1, 1, iSpecies, iType, fDiam);

      fDiam = 0.2;
      iSpecies = 1;
      iType = clTreePopulation::seedling;
      p_oTree = p_oPop->CreateTree(1, 1, iSpecies, iType, fDiam);

      fDiam = 0.3;
      iSpecies = 3;
      iType = clTreePopulation::seedling;
      p_oTree = p_oPop->CreateTree(1, 1, iSpecies, iType, fDiam);

      fDiam = 2.5;
      iSpecies = 0;
      iType = clTreePopulation::sapling;
      p_oTree = p_oPop->CreateTree(1, 1, iSpecies, iType, fDiam);

      fDiam = 3.4;
      iSpecies = 1;
      iType = clTreePopulation::sapling;
      p_oTree = p_oPop->CreateTree(1, 1, iSpecies, iType, fDiam);

      fDiam = 5.4;
      iSpecies = 3;
      iType = clTreePopulation::sapling;
      p_oTree = p_oPop->CreateTree(1, 1, iSpecies, iType, fDiam);

      fDiam = 12.6;
      iSpecies = 0;
      iType = clTreePopulation::adult;
      p_oTree = p_oPop->CreateTree(1, 1, iSpecies, iType, fDiam);

      fDiam = 30;
      iSpecies = 1;
      iType = clTreePopulation::adult;
      p_oTree = p_oPop->CreateTree(1, 1, iSpecies, iType, fDiam);

      fDiam = 23.3;
      iSpecies = 3;
      iType = clTreePopulation::adult;
      p_oTree = p_oPop->CreateTree(1, 1, iSpecies, iType, fDiam);

      fDiam = 0.1;
      iSpecies = 0;
      iType = clTreePopulation::seedling;
      p_oTree = p_oPop->CreateTree(1, 9, iSpecies, iType, fDiam);

      fDiam = 0.2;
      iSpecies = 1;
      iType = clTreePopulation::seedling;
      p_oTree = p_oPop->CreateTree(1, 9, iSpecies, iType, fDiam);

      fDiam = 0.3;
      iSpecies = 3;
      iType = clTreePopulation::seedling;
      p_oTree = p_oPop->CreateTree(1, 9, iSpecies, iType, fDiam);

      fDiam = 2.5;
      iSpecies = 0;
      iType = clTreePopulation::sapling;
      p_oTree = p_oPop->CreateTree(1, 9, iSpecies, iType, fDiam);

      fDiam = 3.4;
      iSpecies = 1;
      iType = clTreePopulation::sapling;
      p_oTree = p_oPop->CreateTree(1, 9, iSpecies, iType, fDiam);

      fDiam = 5.4;
      iSpecies = 3;
      iType = clTreePopulation::sapling;
      p_oTree = p_oPop->CreateTree(1, 9, iSpecies, iType, fDiam);

      fDiam = 12.6;
      iSpecies = 0;
      iType = clTreePopulation::adult;
      p_oTree = p_oPop->CreateTree(1, 9, iSpecies, iType, fDiam);

      fDiam = 30;
      iSpecies = 1;
      iType = clTreePopulation::adult;
      p_oTree = p_oPop->CreateTree(1, 9, iSpecies, iType, fDiam);

      fDiam = 23.3;
      iSpecies = 3;
      iType = clTreePopulation::adult;
      p_oTree = p_oPop->CreateTree(1, 9, iSpecies, iType, fDiam);

      fDiam = 0.1;
      iSpecies = 0;
      iType = clTreePopulation::seedling;
      p_oTree = p_oPop->CreateTree(1, 17, iSpecies, iType, fDiam);

      fDiam = 0.2;
      iSpecies = 1;
      iType = clTreePopulation::seedling;
      p_oTree = p_oPop->CreateTree(1, 17, iSpecies, iType, fDiam);

      fDiam = 0.3;
      iSpecies = 3;
      iType = clTreePopulation::seedling;
      p_oTree = p_oPop->CreateTree(1, 17, iSpecies, iType, fDiam);

      fDiam = 2.5;
      iSpecies = 0;
      iType = clTreePopulation::sapling;
      p_oTree = p_oPop->CreateTree(1, 17, iSpecies, iType, fDiam);

      fDiam = 3.4;
      iSpecies = 1;
      iType = clTreePopulation::sapling;
      p_oTree = p_oPop->CreateTree(1, 17, iSpecies, iType, fDiam);

      fDiam = 5.4;
      iSpecies = 3;
      iType = clTreePopulation::sapling;
      p_oTree = p_oPop->CreateTree(1, 17, iSpecies, iType, fDiam);

      fDiam = 12.6;
      iSpecies = 0;
      iType = clTreePopulation::adult;
      p_oTree = p_oPop->CreateTree(1, 17, iSpecies, iType, fDiam);

      fDiam = 30;
      iSpecies = 1;
      iType = clTreePopulation::adult;
      p_oTree = p_oPop->CreateTree(1, 17, iSpecies, iType, fDiam);

      fDiam = 23.3;
      iSpecies = 3;
      iType = clTreePopulation::adult;
      p_oTree = p_oPop->CreateTree(1, 17, iSpecies, iType, fDiam);
    }

    //Now run mortality, but skip storm light
    for (i = 1; i < p_oSimManager->GetNumberOfBehaviors(); i++) {
      clBehaviorBase *p_oBase = p_oSimManager->GetBehaviorObject(i);
      p_oBase->Action();
    }

    //Count up the trees
    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {

      iSpecies = p_oTree->GetSpecies();
      iType = p_oTree->GetType();

      //Get the Y coordinate
      p_oTree->GetValue(p_oPop->GetYCode(iSpecies, iType), &fY);

      //Do the count based on species, type, and Y
      if (iSpecies == 0 && iType == clTreePopulation::seedling && fY == 1)
        p_iNumTrees[0]++;
      else if (iSpecies == 1 && iType == clTreePopulation::seedling && fY == 1)
        p_iNumTrees[1]++;
      else if (iSpecies == 3 && iType == clTreePopulation::seedling && fY == 1)
        p_iNumTrees[2]++;
      else if (iSpecies == 0 && iType == clTreePopulation::sapling && fY == 1)
        p_iNumTrees[3]++;
      else if (iSpecies == 1 && iType == clTreePopulation::sapling && fY == 1)
        p_iNumTrees[4]++;
      else if (iSpecies == 3 && iType == clTreePopulation::sapling && fY == 1)
        p_iNumTrees[5]++;
      else if (iSpecies == 0 && iType == clTreePopulation::adult && fY == 1)
        p_iNumTrees[6]++;
      else if (iSpecies == 1 && iType == clTreePopulation::adult && fY == 1)
        p_iNumTrees[7]++;
      else if (iSpecies == 3 && iType == clTreePopulation::adult && fY == 1)
        p_iNumTrees[8]++;
      else if (iSpecies == 0 && iType == clTreePopulation::seedling && fY == 9)
        p_iNumTrees[9]++;
      else if (iSpecies == 1 && iType == clTreePopulation::seedling && fY == 9)
        p_iNumTrees[10]++;
      else if (iSpecies == 3 && iType == clTreePopulation::seedling && fY == 9)
        p_iNumTrees[11]++;
      else if (iSpecies == 0 && iType == clTreePopulation::sapling && fY == 9)
        p_iNumTrees[12]++;
      else if (iSpecies == 1 && iType == clTreePopulation::sapling && fY == 9)
        p_iNumTrees[13]++;
      else if (iSpecies == 3 && iType == clTreePopulation::sapling && fY == 9)
        p_iNumTrees[14]++;
      else if (iSpecies == 0 && iType == clTreePopulation::adult && fY == 9)
        p_iNumTrees[15]++;
      else if (iSpecies == 1 && iType == clTreePopulation::adult && fY == 9)
        p_iNumTrees[16]++;
      else if (iSpecies == 3 && iType == clTreePopulation::adult && fY == 9)
        p_iNumTrees[17]++;
      else if (iSpecies == 0 && iType == clTreePopulation::seedling && fY == 17)
        p_iNumTrees[18]++;
      else if (iSpecies == 1 && iType == clTreePopulation::seedling && fY == 17)
        p_iNumTrees[19]++;
      else if (iSpecies == 3 && iType == clTreePopulation::seedling && fY == 17)
        p_iNumTrees[20]++;
      else if (iSpecies == 0 && iType == clTreePopulation::sapling && fY == 17)
        p_iNumTrees[21]++;
      else if (iSpecies == 1 && iType == clTreePopulation::sapling && fY == 17)
        p_iNumTrees[22]++;
      else if (iSpecies == 3 && iType == clTreePopulation::sapling && fY == 17)
        p_iNumTrees[23]++;
      else if (iSpecies == 0 && iType == clTreePopulation::adult && fY == 17)
        p_iNumTrees[24]++;
      else if (iSpecies == 1 && iType == clTreePopulation::adult && fY == 17)
        p_iNumTrees[25]++;
      else if (iSpecies == 3 && iType == clTreePopulation::adult && fY == 17)
        p_iNumTrees[26]++;

      p_oTree = p_oAllTrees->NextTree();
    }

    //Compare to expected results
    //fExpected = 19.68532853;
    EXPECT_LT(p_iNumTrees[0], 40);
    fExpected = 501.4999955;
    EXPECT_LT(fabs(p_iNumTrees[1] - fExpected) / fExpected, 0.1);
    fExpected = 551.6154697;
    EXPECT_LT(fabs(p_iNumTrees[2] - fExpected) / fExpected, 0.1);
    fExpected = 995.9298623;
    EXPECT_LT(fabs(p_iNumTrees[3] - fExpected) / fExpected, 0.1);
    fExpected = 525.4779145;
    EXPECT_LT(fabs(p_iNumTrees[4] - fExpected) / fExpected, 0.1);
    fExpected = 581.6620475;
    EXPECT_LT(fabs(p_iNumTrees[5] - fExpected) / fExpected, 0.1);
    fExpected = 1000;
    EXPECT_LT(fabs(p_iNumTrees[6] - fExpected) / fExpected, 0.1);
    fExpected = 710.9495026;
    EXPECT_LT(fabs(p_iNumTrees[7] - fExpected) / fExpected, 0.1);
    fExpected = 681.1800199;
    EXPECT_LT(fabs(p_iNumTrees[8] - fExpected) / fExpected, 0.1);
    fExpected = 575.542209;
    EXPECT_LT(fabs(p_iNumTrees[9] - fExpected) / fExpected, 0.1);
    fExpected = 501.4999955;
    EXPECT_LT(fabs(p_iNumTrees[10] - fExpected) / fExpected, 0.1);
    fExpected = 551.6154697;
    EXPECT_LT(fabs(p_iNumTrees[11] - fExpected) / fExpected, 0.1);
    fExpected = 601.6871802;
    EXPECT_LT(fabs(p_iNumTrees[12] - fExpected) / fExpected, 0.1);
    fExpected = 525.4779145;
    EXPECT_LT(fabs(p_iNumTrees[13] - fExpected) / fExpected, 0.1);
    fExpected = 581.6620475;
    EXPECT_LT(fabs(p_iNumTrees[14] - fExpected) / fExpected, 0.1);
    fExpected = 704.1210772;
    EXPECT_LT(fabs(p_iNumTrees[15] - fExpected) / fExpected, 0.1);
    fExpected = 710.9495026;
    EXPECT_LT(fabs(p_iNumTrees[16] - fExpected) / fExpected, 0.1);
    fExpected = 681.1800199;
    EXPECT_LT(fabs(p_iNumTrees[17] - fExpected) / fExpected, 0.1);
    fExpected = 575.542209;
    EXPECT_LT(fabs(p_iNumTrees[18] - fExpected) / fExpected, 0.1);
    fExpected = 54.05000866;
    EXPECT_LT(fabs(p_iNumTrees[19] - fExpected) / fExpected, 0.1);
    fExpected = 627.1711494;
    EXPECT_LT(fabs(p_iNumTrees[20] - fExpected) / fExpected, 0.1);
    fExpected = 601.6871802;
    EXPECT_LT(fabs(p_iNumTrees[21] - fExpected) / fExpected, 0.1);
    fExpected = 70.51796365;
    EXPECT_LT(fabs(p_iNumTrees[22] - fExpected) / fExpected, 0.1);
    fExpected = 703.0365887;
    EXPECT_LT(fabs(p_iNumTrees[23] - fExpected) / fExpected, 0.1);
    fExpected = 704.1210772;
    EXPECT_LT(fabs(p_iNumTrees[24] - fExpected) / fExpected, 0.1);
    fExpected = 444.7268207;
    EXPECT_LT(fabs(p_iNumTrees[25] - fExpected) / fExpected, 0.1);
    fExpected = 887.0644161;
    EXPECT_LT(fabs(p_iNumTrees[26] - fExpected) / fExpected, 0.1);

    delete[] p_iNumTrees;
    delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

/////////////////////////////////////////////////////////////////////////////
// NormalProcessingRun2()
// Tests normal processing run 2. WriteLogisticBiLevelMortalityXMLFile2() does
// setup. Timestep length is 3 years and there is a light grid present. 1000
// copies of each of 27 trees is created of 3 species and assigned to a mix of
// light levels. Then mortality is run. We check the number left of each tree
// type to see if it is approximately the right number.
/////////////////////////////////////////////////////////////////////////////
TEST(LogisticBiLevelMortality, NormalProcessingRun2) {
  clTreePopulation * p_oPop;
  clGrid *p_oStormLight;
  clTreeSearch *p_oAllTrees;
  clTree *p_oTree;
  float fDiam, fY, fExpected;
  int *p_iNumTrees = new int[27], i, iSpecies, iType;

  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    for (i = 0; i < 27; i++) {
      p_iNumTrees[i] = 0;
    }

    p_oSimManager->ReadFile(WriteLogisticBiLevelMortalityXMLFile2());
    p_oPop = (clTreePopulation *) p_oSimManager->GetPopulationObject(
        "treepopulation");
    p_oStormLight = p_oSimManager->GetGridObject("Storm Light");

    //Set our grid values
    fDiam = 15;
    p_oStormLight->SetValueOfCell(0, 0, p_oStormLight->GetFloatDataCode("Light"),
        fDiam);
    fDiam = 35;
    p_oStormLight->SetValueOfCell(0, 1, p_oStormLight->GetFloatDataCode("Light"),
        fDiam);
    fDiam = 80;
    p_oStormLight->SetValueOfCell(0, 2, p_oStormLight->GetFloatDataCode("Light"),
        fDiam);

    //Add 1000 trees to the plot of each kind
    for (i = 0; i < 1000; i++) {
      fDiam = 0.1;
      iSpecies = 0;
      iType = clTreePopulation::seedling;
      p_oTree = p_oPop->CreateTree(1, 1, iSpecies, iType, fDiam);

      fDiam = 0.2;
      iSpecies = 1;
      iType = clTreePopulation::seedling;
      p_oTree = p_oPop->CreateTree(1, 1, iSpecies, iType, fDiam);

      fDiam = 0.3;
      iSpecies = 3;
      iType = clTreePopulation::seedling;
      p_oTree = p_oPop->CreateTree(1, 1, iSpecies, iType, fDiam);

      fDiam = 2.5;
      iSpecies = 0;
      iType = clTreePopulation::sapling;
      p_oTree = p_oPop->CreateTree(1, 1, iSpecies, iType, fDiam);

      fDiam = 3.4;
      iSpecies = 1;
      iType = clTreePopulation::sapling;
      p_oTree = p_oPop->CreateTree(1, 1, iSpecies, iType, fDiam);

      fDiam = 5.4;
      iSpecies = 3;
      iType = clTreePopulation::sapling;
      p_oTree = p_oPop->CreateTree(1, 1, iSpecies, iType, fDiam);

      fDiam = 12.6;
      iSpecies = 0;
      iType = clTreePopulation::adult;
      p_oTree = p_oPop->CreateTree(1, 1, iSpecies, iType, fDiam);

      fDiam = 30;
      iSpecies = 1;
      iType = clTreePopulation::adult;
      p_oTree = p_oPop->CreateTree(1, 1, iSpecies, iType, fDiam);

      fDiam = 23.3;
      iSpecies = 3;
      iType = clTreePopulation::adult;
      p_oTree = p_oPop->CreateTree(1, 1, iSpecies, iType, fDiam);

      fDiam = 0.1;
      iSpecies = 0;
      iType = clTreePopulation::seedling;
      p_oTree = p_oPop->CreateTree(1, 9, iSpecies, iType, fDiam);

      fDiam = 0.2;
      iSpecies = 1;
      iType = clTreePopulation::seedling;
      p_oTree = p_oPop->CreateTree(1, 9, iSpecies, iType, fDiam);

      fDiam = 0.3;
      iSpecies = 3;
      iType = clTreePopulation::seedling;
      p_oTree = p_oPop->CreateTree(1, 9, iSpecies, iType, fDiam);

      fDiam = 2.5;
      iSpecies = 0;
      iType = clTreePopulation::sapling;
      p_oTree = p_oPop->CreateTree(1, 9, iSpecies, iType, fDiam);

      fDiam = 3.4;
      iSpecies = 1;
      iType = clTreePopulation::sapling;
      p_oTree = p_oPop->CreateTree(1, 9, iSpecies, iType, fDiam);

      fDiam = 5.4;
      iSpecies = 3;
      iType = clTreePopulation::sapling;
      p_oTree = p_oPop->CreateTree(1, 9, iSpecies, iType, fDiam);

      fDiam = 12.6;
      iSpecies = 0;
      iType = clTreePopulation::adult;
      p_oTree = p_oPop->CreateTree(1, 9, iSpecies, iType, fDiam);

      fDiam = 30;
      iSpecies = 1;
      iType = clTreePopulation::adult;
      p_oTree = p_oPop->CreateTree(1, 9, iSpecies, iType, fDiam);

      fDiam = 23.3;
      iSpecies = 3;
      iType = clTreePopulation::adult;
      p_oTree = p_oPop->CreateTree(1, 9, iSpecies, iType, fDiam);

      fDiam = 0.1;
      iSpecies = 0;
      iType = clTreePopulation::seedling;
      p_oTree = p_oPop->CreateTree(1, 17, iSpecies, iType, fDiam);

      fDiam = 0.2;
      iSpecies = 1;
      iType = clTreePopulation::seedling;
      p_oTree = p_oPop->CreateTree(1, 17, iSpecies, iType, fDiam);

      fDiam = 0.3;
      iSpecies = 3;
      iType = clTreePopulation::seedling;
      p_oTree = p_oPop->CreateTree(1, 17, iSpecies, iType, fDiam);

      fDiam = 2.5;
      iSpecies = 0;
      iType = clTreePopulation::sapling;
      p_oTree = p_oPop->CreateTree(1, 17, iSpecies, iType, fDiam);

      fDiam = 3.4;
      iSpecies = 1;
      iType = clTreePopulation::sapling;
      p_oTree = p_oPop->CreateTree(1, 17, iSpecies, iType, fDiam);

      fDiam = 5.4;
      iSpecies = 3;
      iType = clTreePopulation::sapling;
      p_oTree = p_oPop->CreateTree(1, 17, iSpecies, iType, fDiam);

      fDiam = 12.6;
      iSpecies = 0;
      iType = clTreePopulation::adult;
      p_oTree = p_oPop->CreateTree(1, 17, iSpecies, iType, fDiam);

      fDiam = 30;
      iSpecies = 1;
      iType = clTreePopulation::adult;
      p_oTree = p_oPop->CreateTree(1, 17, iSpecies, iType, fDiam);

      fDiam = 23.3;
      iSpecies = 3;
      iType = clTreePopulation::adult;
      p_oTree = p_oPop->CreateTree(1, 17, iSpecies, iType, fDiam);
    }

    //Now run mortality, but skip storm light
    for (i = 1; i < p_oSimManager->GetNumberOfBehaviors(); i++) {
      clBehaviorBase *p_oBase = p_oSimManager->GetBehaviorObject(i);
      p_oBase->Action();
    }

    //Count up the trees
    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {

      iSpecies = p_oTree->GetSpecies();
      iType = p_oTree->GetType();

      //Get the Y coordinate
      p_oTree->GetValue(p_oPop->GetYCode(iSpecies, iType), &fY);

      //Do the count based on species, type, and Y
      if (iSpecies == 0 && iType == clTreePopulation::seedling && fY == 1)
        p_iNumTrees[0]++;
      else if (iSpecies == 1 && iType == clTreePopulation::seedling && fY == 1)
        p_iNumTrees[1]++;
      else if (iSpecies == 3 && iType == clTreePopulation::seedling && fY == 1)
        p_iNumTrees[2]++;
      else if (iSpecies == 0 && iType == clTreePopulation::sapling && fY == 1)
        p_iNumTrees[3]++;
      else if (iSpecies == 1 && iType == clTreePopulation::sapling && fY == 1)
        p_iNumTrees[4]++;
      else if (iSpecies == 3 && iType == clTreePopulation::sapling && fY == 1)
        p_iNumTrees[5]++;
      else if (iSpecies == 0 && iType == clTreePopulation::adult && fY == 1)
        p_iNumTrees[6]++;
      else if (iSpecies == 1 && iType == clTreePopulation::adult && fY == 1)
        p_iNumTrees[7]++;
      else if (iSpecies == 3 && iType == clTreePopulation::adult && fY == 1)
        p_iNumTrees[8]++;
      else if (iSpecies == 0 && iType == clTreePopulation::seedling && fY == 9)
        p_iNumTrees[9]++;
      else if (iSpecies == 1 && iType == clTreePopulation::seedling && fY == 9)
        p_iNumTrees[10]++;
      else if (iSpecies == 3 && iType == clTreePopulation::seedling && fY == 9)
        p_iNumTrees[11]++;
      else if (iSpecies == 0 && iType == clTreePopulation::sapling && fY == 9)
        p_iNumTrees[12]++;
      else if (iSpecies == 1 && iType == clTreePopulation::sapling && fY == 9)
        p_iNumTrees[13]++;
      else if (iSpecies == 3 && iType == clTreePopulation::sapling && fY == 9)
        p_iNumTrees[14]++;
      else if (iSpecies == 0 && iType == clTreePopulation::adult && fY == 9)
        p_iNumTrees[15]++;
      else if (iSpecies == 1 && iType == clTreePopulation::adult && fY == 9)
        p_iNumTrees[16]++;
      else if (iSpecies == 3 && iType == clTreePopulation::adult && fY == 9)
        p_iNumTrees[17]++;
      else if (iSpecies == 0 && iType == clTreePopulation::seedling && fY == 17)
        p_iNumTrees[18]++;
      else if (iSpecies == 1 && iType == clTreePopulation::seedling && fY == 17)
        p_iNumTrees[19]++;
      else if (iSpecies == 3 && iType == clTreePopulation::seedling && fY == 17)
        p_iNumTrees[20]++;
      else if (iSpecies == 0 && iType == clTreePopulation::sapling && fY == 17)
        p_iNumTrees[21]++;
      else if (iSpecies == 1 && iType == clTreePopulation::sapling && fY == 17)
        p_iNumTrees[22]++;
      else if (iSpecies == 3 && iType == clTreePopulation::sapling && fY == 17)
        p_iNumTrees[23]++;
      else if (iSpecies == 0 && iType == clTreePopulation::adult && fY == 17)
        p_iNumTrees[24]++;
      else if (iSpecies == 1 && iType == clTreePopulation::adult && fY == 17)
        p_iNumTrees[25]++;
      else if (iSpecies == 3 && iType == clTreePopulation::adult && fY == 17)
        p_iNumTrees[26]++;

      p_oTree = p_oAllTrees->NextTree();
    }

    //Compare to expected results
    //fExpected = 0.007628304;
    EXPECT_LT(p_iNumTrees[0], 10);
    fExpected = 126.128375;
    EXPECT_LT(fabs(p_iNumTrees[1] - fExpected) / fExpected, 0.2);
    fExpected = 167.8453491;
    EXPECT_LT(fabs(p_iNumTrees[2] - fExpected) / fExpected, 0.2);
    fExpected = 987.8392175;
    EXPECT_LT(fabs(p_iNumTrees[3] - fExpected) / fExpected, 0.1);
    fExpected = 145.0986604;
    EXPECT_LT(fabs(p_iNumTrees[4] - fExpected) / fExpected, 0.2);
    fExpected = 196.7941495;
    EXPECT_LT(fabs(p_iNumTrees[5] - fExpected) / fExpected, 0.2);
    fExpected = 1000;
    EXPECT_LT(fabs(p_iNumTrees[6] - fExpected) / fExpected, 0.1);
    fExpected = 359.348854;
    EXPECT_LT(fabs(p_iNumTrees[7] - fExpected) / fExpected, 0.1);
    fExpected = 316.0717659;
    EXPECT_LT(fabs(p_iNumTrees[8] - fExpected) / fExpected, 0.1);
    fExpected = 190.6476858;
    EXPECT_LT(fabs(p_iNumTrees[9] - fExpected) / fExpected, 0.1);
    fExpected = 126.128375;
    EXPECT_LT(fabs(p_iNumTrees[10] - fExpected) / fExpected, 0.2);
    fExpected = 167.8453491;
    EXPECT_LT(fabs(p_iNumTrees[11] - fExpected) / fExpected, 0.1);
    fExpected = 217.8272832;
    EXPECT_LT(fabs(p_iNumTrees[12] - fExpected) / fExpected, 0.1);
    fExpected = 145.0986604;
    EXPECT_LT(fabs(p_iNumTrees[13] - fExpected) / fExpected, 0.2);
    fExpected = 196.7941495;
    EXPECT_LT(fabs(p_iNumTrees[14] - fExpected) / fExpected, 0.1);
    fExpected = 349.0937184;
    EXPECT_LT(fabs(p_iNumTrees[15] - fExpected) / fExpected, 0.1);
    fExpected = 359.348854;
    EXPECT_LT(fabs(p_iNumTrees[16] - fExpected) / fExpected, 0.1);
    fExpected = 316.0717659;
    EXPECT_LT(fabs(p_iNumTrees[17] - fExpected) / fExpected, 0.1);
    fExpected = 190.6476858;
    EXPECT_LT(fabs(p_iNumTrees[18] - fExpected) / fExpected, 0.1);
    fExpected = 15.29804584;
    EXPECT_LT(p_iNumTrees[19], 30);
    fExpected = 246.6937894;
    EXPECT_LT(fabs(p_iNumTrees[20] - fExpected) / fExpected, 0.1);
    fExpected = 217.8272832;
    EXPECT_LT(fabs(p_iNumTrees[21] - fExpected) / fExpected, 0.1);
    //fExpected = 0.350670545;
    EXPECT_LT(p_iNumTrees[22], 10);
    fExpected = 347.4831772;
    EXPECT_LT(fabs(p_iNumTrees[23] - fExpected) / fExpected, 0.1);
    fExpected = 349.0937184;
    EXPECT_LT(fabs(p_iNumTrees[24] - fExpected) / fExpected, 0.1);
    fExpected = 87.95893562;
    EXPECT_LT(p_iNumTrees[25] >= 60 && p_iNumTrees[25], 110);
    fExpected = 698.0161558;
    EXPECT_LT(fabs(p_iNumTrees[26] - fExpected) / fExpected, 0.1);

    delete[] p_iNumTrees;
    delete p_oSimManager;
  } catch (modelErr &e) {
    delete[] p_iNumTrees;
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

/////////////////////////////////////////////////////////////////////////////
// NormalProcessingRun3()
// Tests normal processing run 3. WriteLogisticBiLevelMortalityXMLFile3() does setup. Timestep
// length is 1 year and there is no light grid present. 1000 copies of each
// of 27 trees is created of 3 species and assigned to a mix of light levels.
// Then mortality is run. We check the number left of each tree type to see
// if it is approximately the right number.
/////////////////////////////////////////////////////////////////////////////
TEST(LogisticBiLevelMortality, NormalProcessingRun3) {
  clTreePopulation * p_oPop;
  clTreeSearch *p_oAllTrees;
  clTree *p_oTree;
  float fDiam, fY, fExpected;
  int *p_iNumTrees = new int[27], i, iSpecies, iType;

  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    for (i = 0; i < 27; i++) {
      p_iNumTrees[i] = 0;
    }

    p_oSimManager->ReadFile(WriteLogisticBiLevelMortalityXMLFile3());
    p_oPop = (clTreePopulation *) p_oSimManager->GetPopulationObject(
        "treepopulation");

    //Add 1000 trees to the plot of each kind
    for (i = 0; i < 1000; i++) {
      fDiam = 0.1;
      iSpecies = 0;
      iType = clTreePopulation::seedling;
      p_oTree = p_oPop->CreateTree(1, 1, iSpecies, iType, fDiam);

      fDiam = 0.2;
      iSpecies = 1;
      iType = clTreePopulation::seedling;
      p_oTree = p_oPop->CreateTree(1, 1, iSpecies, iType, fDiam);

      fDiam = 0.3;
      iSpecies = 3;
      iType = clTreePopulation::seedling;
      p_oTree = p_oPop->CreateTree(1, 1, iSpecies, iType, fDiam);

      fDiam = 2.5;
      iSpecies = 0;
      iType = clTreePopulation::sapling;
      p_oTree = p_oPop->CreateTree(1, 1, iSpecies, iType, fDiam);

      fDiam = 3.4;
      iSpecies = 1;
      iType = clTreePopulation::sapling;
      p_oTree = p_oPop->CreateTree(1, 1, iSpecies, iType, fDiam);

      fDiam = 5.4;
      iSpecies = 3;
      iType = clTreePopulation::sapling;
      p_oTree = p_oPop->CreateTree(1, 1, iSpecies, iType, fDiam);

      fDiam = 12.6;
      iSpecies = 0;
      iType = clTreePopulation::adult;
      p_oTree = p_oPop->CreateTree(1, 1, iSpecies, iType, fDiam);

      fDiam = 30;
      iSpecies = 1;
      iType = clTreePopulation::adult;
      p_oTree = p_oPop->CreateTree(1, 1, iSpecies, iType, fDiam);

      fDiam = 23.3;
      iSpecies = 3;
      iType = clTreePopulation::adult;
      p_oTree = p_oPop->CreateTree(1, 1, iSpecies, iType, fDiam);

      fDiam = 0.1;
      iSpecies = 0;
      iType = clTreePopulation::seedling;
      p_oTree = p_oPop->CreateTree(1, 9, iSpecies, iType, fDiam);

      fDiam = 0.2;
      iSpecies = 1;
      iType = clTreePopulation::seedling;
      p_oTree = p_oPop->CreateTree(1, 9, iSpecies, iType, fDiam);

      fDiam = 0.3;
      iSpecies = 3;
      iType = clTreePopulation::seedling;
      p_oTree = p_oPop->CreateTree(1, 9, iSpecies, iType, fDiam);

      fDiam = 2.5;
      iSpecies = 0;
      iType = clTreePopulation::sapling;
      p_oTree = p_oPop->CreateTree(1, 9, iSpecies, iType, fDiam);

      fDiam = 3.4;
      iSpecies = 1;
      iType = clTreePopulation::sapling;
      p_oTree = p_oPop->CreateTree(1, 9, iSpecies, iType, fDiam);

      fDiam = 5.4;
      iSpecies = 3;
      iType = clTreePopulation::sapling;
      p_oTree = p_oPop->CreateTree(1, 9, iSpecies, iType, fDiam);

      fDiam = 12.6;
      iSpecies = 0;
      iType = clTreePopulation::adult;
      p_oTree = p_oPop->CreateTree(1, 9, iSpecies, iType, fDiam);

      fDiam = 30;
      iSpecies = 1;
      iType = clTreePopulation::adult;
      p_oTree = p_oPop->CreateTree(1, 9, iSpecies, iType, fDiam);

      fDiam = 23.3;
      iSpecies = 3;
      iType = clTreePopulation::adult;
      p_oTree = p_oPop->CreateTree(1, 9, iSpecies, iType, fDiam);

      fDiam = 0.1;
      iSpecies = 0;
      iType = clTreePopulation::seedling;
      p_oTree = p_oPop->CreateTree(1, 17, iSpecies, iType, fDiam);

      fDiam = 0.2;
      iSpecies = 1;
      iType = clTreePopulation::seedling;
      p_oTree = p_oPop->CreateTree(1, 17, iSpecies, iType, fDiam);

      fDiam = 0.3;
      iSpecies = 3;
      iType = clTreePopulation::seedling;
      p_oTree = p_oPop->CreateTree(1, 17, iSpecies, iType, fDiam);

      fDiam = 2.5;
      iSpecies = 0;
      iType = clTreePopulation::sapling;
      p_oTree = p_oPop->CreateTree(1, 17, iSpecies, iType, fDiam);

      fDiam = 3.4;
      iSpecies = 1;
      iType = clTreePopulation::sapling;
      p_oTree = p_oPop->CreateTree(1, 17, iSpecies, iType, fDiam);

      fDiam = 5.4;
      iSpecies = 3;
      iType = clTreePopulation::sapling;
      p_oTree = p_oPop->CreateTree(1, 17, iSpecies, iType, fDiam);

      fDiam = 12.6;
      iSpecies = 0;
      iType = clTreePopulation::adult;
      p_oTree = p_oPop->CreateTree(1, 17, iSpecies, iType, fDiam);

      fDiam = 30;
      iSpecies = 1;
      iType = clTreePopulation::adult;
      p_oTree = p_oPop->CreateTree(1, 17, iSpecies, iType, fDiam);

      fDiam = 23.3;
      iSpecies = 3;
      iType = clTreePopulation::adult;
      p_oTree = p_oPop->CreateTree(1, 17, iSpecies, iType, fDiam);
    }

    //Now run
    p_oSimManager->RunSim(1);

    //Count up the trees
    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {

      iSpecies = p_oTree->GetSpecies();
      iType = p_oTree->GetType();

      //Get the Y coordinate
      p_oTree->GetValue(p_oPop->GetYCode(iSpecies, iType), &fY);

      //Do the count based on species, type, and Y
      if (iSpecies == 0 && iType == clTreePopulation::seedling && fY == 1)
        p_iNumTrees[0]++;
      else if (iSpecies == 1 && iType == clTreePopulation::seedling && fY == 1)
        p_iNumTrees[1]++;
      else if (iSpecies == 3 && iType == clTreePopulation::seedling && fY == 1)
        p_iNumTrees[2]++;
      else if (iSpecies == 0 && iType == clTreePopulation::sapling && fY == 1)
        p_iNumTrees[3]++;
      else if (iSpecies == 1 && iType == clTreePopulation::sapling && fY == 1)
        p_iNumTrees[4]++;
      else if (iSpecies == 3 && iType == clTreePopulation::sapling && fY == 1)
        p_iNumTrees[5]++;
      else if (iSpecies == 0 && iType == clTreePopulation::adult && fY == 1)
        p_iNumTrees[6]++;
      else if (iSpecies == 1 && iType == clTreePopulation::adult && fY == 1)
        p_iNumTrees[7]++;
      else if (iSpecies == 3 && iType == clTreePopulation::adult && fY == 1)
        p_iNumTrees[8]++;
      else if (iSpecies == 0 && iType == clTreePopulation::seedling && fY == 9)
        p_iNumTrees[9]++;
      else if (iSpecies == 1 && iType == clTreePopulation::seedling && fY == 9)
        p_iNumTrees[10]++;
      else if (iSpecies == 3 && iType == clTreePopulation::seedling && fY == 9)
        p_iNumTrees[11]++;
      else if (iSpecies == 0 && iType == clTreePopulation::sapling && fY == 9)
        p_iNumTrees[12]++;
      else if (iSpecies == 1 && iType == clTreePopulation::sapling && fY == 9)
        p_iNumTrees[13]++;
      else if (iSpecies == 3 && iType == clTreePopulation::sapling && fY == 9)
        p_iNumTrees[14]++;
      else if (iSpecies == 0 && iType == clTreePopulation::adult && fY == 9)
        p_iNumTrees[15]++;
      else if (iSpecies == 1 && iType == clTreePopulation::adult && fY == 9)
        p_iNumTrees[16]++;
      else if (iSpecies == 3 && iType == clTreePopulation::adult && fY == 9)
        p_iNumTrees[17]++;
      else if (iSpecies == 0 && iType == clTreePopulation::seedling && fY == 17)
        p_iNumTrees[18]++;
      else if (iSpecies == 1 && iType == clTreePopulation::seedling && fY == 17)
        p_iNumTrees[19]++;
      else if (iSpecies == 3 && iType == clTreePopulation::seedling && fY == 17)
        p_iNumTrees[20]++;
      else if (iSpecies == 0 && iType == clTreePopulation::sapling && fY == 17)
        p_iNumTrees[21]++;
      else if (iSpecies == 1 && iType == clTreePopulation::sapling && fY == 17)
        p_iNumTrees[22]++;
      else if (iSpecies == 3 && iType == clTreePopulation::sapling && fY == 17)
        p_iNumTrees[23]++;
      else if (iSpecies == 0 && iType == clTreePopulation::adult && fY == 17)
        p_iNumTrees[24]++;
      else if (iSpecies == 1 && iType == clTreePopulation::adult && fY == 17)
        p_iNumTrees[25]++;
      else if (iSpecies == 3 && iType == clTreePopulation::adult && fY == 17)
        p_iNumTrees[26]++;

      p_oTree = p_oAllTrees->NextTree();
    }

    //Compare to expected results
    //fExpected = 19.68532853;
    EXPECT_LT(p_iNumTrees[0], 40);
    fExpected = 501.4999955;
    EXPECT_LT(fabs(p_iNumTrees[1] - fExpected) / fExpected, 0.1);
    fExpected = 551.6154697;
    EXPECT_LT(fabs(p_iNumTrees[2] - fExpected) / fExpected, 0.1);
    fExpected = 995.9298623;
    EXPECT_LT(fabs(p_iNumTrees[3] - fExpected) / fExpected, 0.1);
    fExpected = 525.4779145;
    EXPECT_LT(fabs(p_iNumTrees[4] - fExpected) / fExpected, 0.1);
    fExpected = 581.6620475;
    EXPECT_LT(fabs(p_iNumTrees[5] - fExpected) / fExpected, 0.1);
    fExpected = 1000;
    EXPECT_LT(fabs(p_iNumTrees[6] - fExpected) / fExpected, 0.1);
    fExpected = 710.9495026;
    EXPECT_LT(fabs(p_iNumTrees[7] - fExpected) / fExpected, 0.1);
    fExpected = 681.1800199;
    EXPECT_LT(fabs(p_iNumTrees[8] - fExpected) / fExpected, 0.1);
    //fExpected = 19.68532853;
    EXPECT_LT(p_iNumTrees[9], 40);
    fExpected = 501.4999955;
    EXPECT_LT(fabs(p_iNumTrees[10] - fExpected) / fExpected, 0.1);
    fExpected = 551.6154697;
    EXPECT_LT(fabs(p_iNumTrees[11] - fExpected) / fExpected, 0.1);
    fExpected = 995.9298623;
    EXPECT_LT(fabs(p_iNumTrees[12] - fExpected) / fExpected, 0.1);
    fExpected = 525.4779145;
    EXPECT_LT(fabs(p_iNumTrees[13] - fExpected) / fExpected, 0.1);
    fExpected = 581.6620475;
    EXPECT_LT(fabs(p_iNumTrees[14] - fExpected) / fExpected, 0.1);
    fExpected = 1000;
    EXPECT_LT(fabs(p_iNumTrees[15] - fExpected) / fExpected, 0.1);
    fExpected = 710.9495026;
    EXPECT_LT(fabs(p_iNumTrees[16] - fExpected) / fExpected, 0.1);
    fExpected = 681.1800199;
    EXPECT_LT(fabs(p_iNumTrees[17] - fExpected) / fExpected, 0.1);
    //fExpected = 19.68532853;
    EXPECT_LT(p_iNumTrees[18], 40);
    fExpected = 501.4999955;
    EXPECT_LT(fabs(p_iNumTrees[19] - fExpected) / fExpected, 0.1);
    fExpected = 551.6154697;
    EXPECT_LT(fabs(p_iNumTrees[20] - fExpected) / fExpected, 0.1);
    fExpected = 995.9298623;
    EXPECT_LT(fabs(p_iNumTrees[21] - fExpected) / fExpected, 0.1);
    fExpected = 525.4779145;
    EXPECT_LT(fabs(p_iNumTrees[22] - fExpected) / fExpected, 0.1);
    fExpected = 581.6620475;
    EXPECT_LT(fabs(p_iNumTrees[23] - fExpected) / fExpected, 0.1);
    fExpected = 1000;
    EXPECT_LT(fabs(p_iNumTrees[24] - fExpected) / fExpected, 0.1);
    fExpected = 710.9495026;
    EXPECT_LT(fabs(p_iNumTrees[25] - fExpected) / fExpected, 0.1);
    fExpected = 681.1800199;
    EXPECT_LT(fabs(p_iNumTrees[26] - fExpected) / fExpected, 0.1);

    delete[] p_iNumTrees;
    delete p_oSimManager;
  } catch (modelErr &e) {
    delete[] p_iNumTrees;
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

////////////////////////////////////////////////////////////////////////////
// ErrorProcessing()
////////////////////////////////////////////////////////////////////////////
TEST(LogisticBiLevelMortality, ErrorProcessing) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    p_oSimManager->ReadFile(WriteLogisticBiLevelMortalityXMLErrorFile1());
    FAIL() << "TestLogisticBiLevelMortality error processing didn't catch error for WriteLogisticBiLevelMortalityXMLErrorFile1.";
  } catch (modelErr& err) {
    if (err.sFunction.compare("clLogisticBiLevelMortality::DoShellSetup") != 0) {
      FAIL() << "TestLogisticBiLevelMortality error processing caught wrong error for WriteLogisticBiLevelMortalityXMLErrorFile1.";
    };
  }
  delete p_oSimManager;
}

////////////////////////////////////////////////////////////////////////////
// WriteLogisticBiLevelMortalityXMLFile1()
////////////////////////////////////////////////////////////////////////////
const char* WriteLogisticBiLevelMortalityXMLFile1() {
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

  WriteLogisticBiLevelMortalityCommonStuff(oOut);

  oOut << "<behaviorList>"
      << "<behavior>"
      << "<behaviorName>StormLight</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>1</listPosition>"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>LogisticBiLevelMortality</behaviorName>"
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
      << "<behaviorName>RemoveDead</behaviorName>"
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
      << "<li_stormLightStoch>0</li_stormLightStoch>"
      << "<li_stormLightSnagMaxDmgTime>2</li_stormLightSnagMaxDmgTime>"
      << "<li_stormLightMinFullCanopy>9</li_stormLightMinFullCanopy>"
      << "</StormLight1>";

  WriteLogisticBiLevelMortalityMortParameters(oOut);
  oOut << "</paramFile>";

  oOut.close();

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteLogisticBiLevelMortalityXMLFile2()
////////////////////////////////////////////////////////////////////////////
const char* WriteLogisticBiLevelMortalityXMLFile2() {
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

  WriteLogisticBiLevelMortalityCommonStuff(oOut);

  oOut << "<behaviorList>"
      << "<behavior>"
      << "<behaviorName>StormLight</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>1</listPosition>"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>LogisticBiLevelMortality</behaviorName>"
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
      << "<behaviorName>RemoveDead</behaviorName>"
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
      << "<li_stormLightStoch>0</li_stormLightStoch>"
      << "<li_stormLightSnagMaxDmgTime>2</li_stormLightSnagMaxDmgTime>"
      << "<li_stormLightMinFullCanopy>9</li_stormLightMinFullCanopy>"
      << "</StormLight1>";

  WriteLogisticBiLevelMortalityMortParameters(oOut);
  oOut << "</paramFile>";

  oOut.close();

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteLogisticBiLevelMortalityXMLFile3()
////////////////////////////////////////////////////////////////////////////
const char* WriteLogisticBiLevelMortalityXMLFile3() {
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

  WriteLogisticBiLevelMortalityCommonStuff(oOut);

  oOut << "<behaviorList>"
      << "<behavior>"
      << "<behaviorName>LogisticBiLevelMortality</behaviorName>"
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
      << "<behaviorName>RemoveDead</behaviorName>"
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
      << "</behaviorList>";

  oOut << "<LogisticBiLevelMortality1>"
      << "<mo_logBilevLoLiteA>"
      << "<mo_lbllaVal species=\"Species_1\">-4.3</mo_lbllaVal>"
      << "<mo_lbllaVal species=\"Species_2\">0</mo_lbllaVal>"
      << "<mo_lbllaVal species=\"Species_4\">0.2</mo_lbllaVal>"
      << "</mo_logBilevLoLiteA>"
      << "<mo_logBilevLoLiteB>"
      << "<mo_lbllbVal species=\"Species_1\">3.92</mo_lbllbVal>"
      << "<mo_lbllbVal species=\"Species_2\">0.03</mo_lbllbVal>"
      << "<mo_lbllbVal species=\"Species_4\">0.024</mo_lbllbVal>"
      << "</mo_logBilevLoLiteB>"
      << "<mo_logBilevHiLiteThreshold>"
      << "<mo_lbhltVal species=\"Species_1\">20</mo_lbhltVal>"
      << "<mo_lbhltVal species=\"Species_2\">50</mo_lbhltVal>"
      << "<mo_lbhltVal species=\"Species_4\">70</mo_lbhltVal>"
      << "</mo_logBilevHiLiteThreshold>"
      << "</LogisticBiLevelMortality1>";
  oOut << "</paramFile>";

  oOut.close();

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteLogisticBiLevelMortalityXMLErrorFile1()
////////////////////////////////////////////////////////////////////////////
const char* WriteLogisticBiLevelMortalityXMLErrorFile1() {
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

  WriteLogisticBiLevelMortalityCommonStuff(oOut);

  oOut << "<behaviorList>"
      << "<behavior>"
      << "<behaviorName>StormLight</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>1</listPosition>"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>LogisticBiLevelMortality</behaviorName>"
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

  oOut << "<LogisticBiLevelMortality2>"
      << "<mo_logBilevLoLiteA>"
      << "<mo_lbllaVal species=\"Species_1\">-4.3</mo_lbllaVal>"
      << "<mo_lbllaVal species=\"Species_2\">0</mo_lbllaVal>"
      << "<mo_lbllaVal species=\"Species_4\">0.2</mo_lbllaVal>"
      << "</mo_logBilevLoLiteA>"
      << "<mo_logBilevHiLiteA>"
      << "<mo_lbhlaVal species=\"Species_1\">0.3</mo_lbhlaVal>"
      << "<mo_lbhlaVal species=\"Species_2\">-2.88</mo_lbhlaVal>"
      << "<mo_lbhlaVal species=\"Species_4\">0.5</mo_lbhlaVal>"
      << "</mo_logBilevHiLiteA>"
      << "<mo_logBilevLoLiteB>"
      << "<mo_lbllbVal species=\"Species_1\">3.92</mo_lbllbVal>"
      << "<mo_lbllbVal species=\"Species_2\">0.03</mo_lbllbVal>"
      << "<mo_lbllbVal species=\"Species_4\">0.024</mo_lbllbVal>"
      << "</mo_logBilevLoLiteB>"
      << "<mo_logBilevHiLiteB>"
      << "<mo_lbhlbVal species=\"Species_1\">0.045</mo_lbhlbVal>"
      << "<mo_lbhlbVal species=\"Species_2\">8.86</mo_lbhlbVal>"
      << "<mo_lbhlbVal species=\"Species_4\">0.067</mo_lbhlbVal>"
      << "</mo_logBilevHiLiteB>"
      << "<mo_logBilevHiLiteThreshold>"
      << "<mo_lbhltVal species=\"Species_1\">120</mo_lbhltVal>"
      << "<mo_lbhltVal species=\"Species_2\">50</mo_lbhltVal>"
      << "<mo_lbhltVal species=\"Species_4\">70</mo_lbhltVal>"
      << "</mo_logBilevHiLiteThreshold>"
      << "</LogisticBiLevelMortality2>"
      << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteLogisticBiLevelMortalityCommonStuff()
/////////////////////////////////////////////////////////////////////////////
void WriteLogisticBiLevelMortalityCommonStuff(std::fstream &oOut) {
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
// WriteLogisticBiLevelMortalityMortParameters()
/////////////////////////////////////////////////////////////////////////////
void WriteLogisticBiLevelMortalityMortParameters(std::fstream &oOut) {
  using namespace std;
  oOut << "<LogisticBiLevelMortality2>"
      << "<mo_logBilevLoLiteA>"
      << "<mo_lbllaVal species=\"Species_1\">-4.3</mo_lbllaVal>"
      << "<mo_lbllaVal species=\"Species_2\">0</mo_lbllaVal>"
      << "<mo_lbllaVal species=\"Species_4\">0.2</mo_lbllaVal>"
      << "</mo_logBilevLoLiteA>"
      << "<mo_logBilevHiLiteA>"
      << "<mo_lbhlaVal species=\"Species_1\">0.3</mo_lbhlaVal>"
      << "<mo_lbhlaVal species=\"Species_2\">-2.88</mo_lbhlaVal>"
      << "<mo_lbhlaVal species=\"Species_4\">0.5</mo_lbhlaVal>"
      << "</mo_logBilevHiLiteA>"
      << "<mo_logBilevLoLiteB>"
      << "<mo_lbllbVal species=\"Species_1\">3.92</mo_lbllbVal>"
      << "<mo_lbllbVal species=\"Species_2\">0.03</mo_lbllbVal>"
      << "<mo_lbllbVal species=\"Species_4\">0.024</mo_lbllbVal>"
      << "</mo_logBilevLoLiteB>"
      << "<mo_logBilevHiLiteB>"
      << "<mo_lbhlbVal species=\"Species_1\">0.045</mo_lbhlbVal>"
      << "<mo_lbhlbVal species=\"Species_2\">0.0886</mo_lbhlbVal>"
      << "<mo_lbhlbVal species=\"Species_4\">0.067</mo_lbhlbVal>"
      << "</mo_logBilevHiLiteB>"
      << "<mo_logBilevHiLiteThreshold>"
      << "<mo_lbhltVal species=\"Species_1\">20</mo_lbhltVal>"
      << "<mo_lbhltVal species=\"Species_2\">50</mo_lbhltVal>"
      << "<mo_lbhltVal species=\"Species_4\">70</mo_lbhltVal>"
      << "</mo_logBilevHiLiteThreshold>"
      << "</LogisticBiLevelMortality2>";
}
