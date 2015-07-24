//---------------------------------------------------------------------------
// TestHeightGLIWeibullMortality.cpp
//---------------------------------------------------------------------------
#include "TestHeightGLIWeibullMortality.h"
#include <gtest/gtest.h>
#include "SimManager.h"
#include "TreePopulation.h"
#include "BehaviorBase.h"
#include <fstream>
#include <math.h>

/////////////////////////////////////////////////////////////////////////////
// NormalProcessingRun1()
// Tests normal processing run 1. WriteHeightGLIWeibullMortalityXMLFile1() does
// setup. Timestep length is 1 year and there is a light grid present. 1000
// copies of each of 27 trees is created of 3 species and assigned to a mix of
// light levels. Then mortality is run.  We check the number left of each tree
// type to see if it is approximately the right number.
/////////////////////////////////////////////////////////////////////////////
TEST(HeightGLIWeibullMortality, NormalProcessingRun1) {
  clTreePopulation * p_oPop;
  clTreeSearch *p_oAllTrees;
  clTree *p_oTree;
  float fDiam, fLight, fY, fExpected;
  int iNumTrees = 39,
      *p_iNumTrees = new int[iNumTrees], i,
      iSpecies, iType, iIndex;
  bool bBrowsed;

  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    for (i = 0; i < iNumTrees; i++) {
      p_iNumTrees[i] = 0;
    }

    p_oSimManager->ReadFile(WriteHeightGLIWeibullMortalityXMLFile1());
    p_oPop = (clTreePopulation *) p_oSimManager->GetPopulationObject("treepopulation");

    //Add 1000 trees to the plot of each kind
    //Each tree's diameter is also its height
    for (i = 0; i < 1000; i++) {
      fDiam = 0.1;
      iSpecies = 0;
      fLight = 15;
      iType = clTreePopulation::seedling;
      bBrowsed = false;
      p_oTree = p_oPop->CreateTree(1, 0, iSpecies, iType, fDiam);
      p_oTree->SetValue(p_oPop->GetHeightCode(iSpecies, iType), fDiam);
      p_oTree->SetValue(p_oPop->GetFloatDataCode("Light", iSpecies, iType), fLight);
      p_oTree->SetValue(p_oPop->GetBoolDataCode("Browsed", iSpecies, iType), bBrowsed);

      fDiam = 0.1;
      iSpecies = 0;
      fLight = 15;
      iType = clTreePopulation::seedling;
      bBrowsed = true;
      p_oTree = p_oPop->CreateTree(1, 1, iSpecies, iType, fDiam);
      p_oTree->SetValue(p_oPop->GetHeightCode(iSpecies, iType), fDiam);
      p_oTree->SetValue(p_oPop->GetFloatDataCode("Light", iSpecies, iType), fLight);
      p_oTree->SetValue(p_oPop->GetBoolDataCode("Browsed", iSpecies, iType), bBrowsed);

      fDiam = 0.2;
      iSpecies = 1;
      fLight = 15;
      iType = clTreePopulation::seedling;
      bBrowsed = false;
      p_oTree = p_oPop->CreateTree(1, 2, iSpecies, iType, fDiam);
      p_oTree->SetValue(p_oPop->GetHeightCode(iSpecies, iType), fDiam);
      p_oTree->SetValue(p_oPop->GetFloatDataCode("Light", iSpecies, iType), fLight);
      p_oTree->SetValue(p_oPop->GetBoolDataCode("Browsed", iSpecies, iType), bBrowsed);

      fDiam = 0.2;
      iSpecies = 1;
      fLight = 15;
      iType = clTreePopulation::seedling;
      bBrowsed = true;
      p_oTree = p_oPop->CreateTree(1, 3, iSpecies, iType, fDiam);
      p_oTree->SetValue(p_oPop->GetHeightCode(iSpecies, iType), fDiam);
      p_oTree->SetValue(p_oPop->GetFloatDataCode("Light", iSpecies, iType), fLight);
      p_oTree->SetValue(p_oPop->GetBoolDataCode("Browsed", iSpecies, iType), bBrowsed);

      fDiam = 0.3;
      iSpecies = 3;
      fLight = 15;
      iType = clTreePopulation::seedling;
      p_oTree = p_oPop->CreateTree(1, 4, iSpecies, iType, fDiam);
      p_oTree->SetValue(p_oPop->GetHeightCode(iSpecies, iType), fDiam);
      p_oTree->SetValue(p_oPop->GetFloatDataCode("Light", iSpecies, iType), fLight);

      fDiam = 2.5;
      iSpecies = 0;
      fLight = 15;
      iType = clTreePopulation::sapling;
      bBrowsed = false;
      p_oTree = p_oPop->CreateTree(1, 5, iSpecies, iType, fDiam);
      p_oTree->SetValue(p_oPop->GetHeightCode(iSpecies, iType), fDiam);
      p_oTree->SetValue(p_oPop->GetFloatDataCode("Light", iSpecies, iType), fLight);
      p_oTree->SetValue(p_oPop->GetBoolDataCode("Browsed", iSpecies, iType), bBrowsed);

      fDiam = 2.5;
      iSpecies = 0;
      fLight = 15;
      iType = clTreePopulation::sapling;
      bBrowsed = true;
      p_oTree = p_oPop->CreateTree(1, 6, iSpecies, iType, fDiam);
      p_oTree->SetValue(p_oPop->GetHeightCode(iSpecies, iType), fDiam);
      p_oTree->SetValue(p_oPop->GetFloatDataCode("Light", iSpecies, iType), fLight);
      p_oTree->SetValue(p_oPop->GetBoolDataCode("Browsed", iSpecies, iType), bBrowsed);

      fDiam = 3.4;
      iSpecies = 1;
      fLight = 15;
      bBrowsed = false;
      iType = clTreePopulation::sapling;
      p_oTree = p_oPop->CreateTree(1, 7, iSpecies, iType, fDiam);
      p_oTree->SetValue(p_oPop->GetHeightCode(iSpecies, iType), fDiam);
      p_oTree->SetValue(p_oPop->GetFloatDataCode("Light", iSpecies, iType), fLight);
      p_oTree->SetValue(p_oPop->GetBoolDataCode("Browsed", iSpecies, iType), bBrowsed);

      fDiam = 3.4;
      iSpecies = 1;
      fLight = 15;
      bBrowsed = true;
      iType = clTreePopulation::sapling;
      p_oTree = p_oPop->CreateTree(1, 8, iSpecies, iType, fDiam);
      p_oTree->SetValue(p_oPop->GetHeightCode(iSpecies, iType), fDiam);
      p_oTree->SetValue(p_oPop->GetFloatDataCode("Light", iSpecies, iType), fLight);
      p_oTree->SetValue(p_oPop->GetBoolDataCode("Browsed", iSpecies, iType), bBrowsed);

      fDiam = 5.4;
      iSpecies = 3;
      fLight = 15;
      iType = clTreePopulation::sapling;
      p_oTree = p_oPop->CreateTree(1, 9, iSpecies, iType, fDiam);
      p_oTree->SetValue(p_oPop->GetHeightCode(iSpecies, iType), fDiam);
      p_oTree->SetValue(p_oPop->GetFloatDataCode("Light", iSpecies, iType), fLight);

      fDiam = 12.6;
      iSpecies = 0;
      fLight = 15;
      iType = clTreePopulation::adult;
      p_oTree = p_oPop->CreateTree(1, 10, iSpecies, iType, fDiam);
      p_oTree->SetValue(p_oPop->GetHeightCode(iSpecies, iType), fDiam);
      p_oTree->SetValue(p_oPop->GetFloatDataCode("Light", iSpecies, iType), fLight);

      fDiam = 30;
      iSpecies = 1;
      fLight = 15;
      iType = clTreePopulation::adult;
      p_oTree = p_oPop->CreateTree(1, 11, iSpecies, iType, fDiam);
      p_oTree->SetValue(p_oPop->GetHeightCode(iSpecies, iType), fDiam);
      p_oTree->SetValue(p_oPop->GetFloatDataCode("Light", iSpecies, iType), fLight);

      fDiam = 23.3;
      iSpecies = 3;
      fLight = 15;
      iType = clTreePopulation::adult;
      p_oTree = p_oPop->CreateTree(1, 12, iSpecies, iType, fDiam);
      p_oTree->SetValue(p_oPop->GetHeightCode(iSpecies, iType), fDiam);
      p_oTree->SetValue(p_oPop->GetFloatDataCode("Light", iSpecies, iType), fLight);

      fDiam = 0.1;
      iSpecies = 0;
      fLight = 35;
      iType = clTreePopulation::seedling;
      bBrowsed = false;
      p_oTree = p_oPop->CreateTree(1, 13, iSpecies, iType, fDiam);
      p_oTree->SetValue(p_oPop->GetHeightCode(iSpecies, iType), fDiam);
      p_oTree->SetValue(p_oPop->GetFloatDataCode("Light", iSpecies, iType), fLight);
      p_oTree->SetValue(p_oPop->GetBoolDataCode("Browsed", iSpecies, iType), bBrowsed);

      fDiam = 0.1;
      iSpecies = 0;
      fLight = 35;
      iType = clTreePopulation::seedling;
      bBrowsed = true;
      p_oTree = p_oPop->CreateTree(1, 14, iSpecies, iType, fDiam);
      p_oTree->SetValue(p_oPop->GetHeightCode(iSpecies, iType), fDiam);
      p_oTree->SetValue(p_oPop->GetFloatDataCode("Light", iSpecies, iType), fLight);
      p_oTree->SetValue(p_oPop->GetBoolDataCode("Browsed", iSpecies, iType), bBrowsed);

      fDiam = 0.2;
      iSpecies = 1;
      fLight = 35;
      iType = clTreePopulation::seedling;
      bBrowsed = false;
      p_oTree = p_oPop->CreateTree(1, 15, iSpecies, iType, fDiam);
      p_oTree->SetValue(p_oPop->GetHeightCode(iSpecies, iType), fDiam);
      p_oTree->SetValue(p_oPop->GetFloatDataCode("Light", iSpecies, iType), fLight);
      p_oTree->SetValue(p_oPop->GetBoolDataCode("Browsed", iSpecies, iType), bBrowsed);

      fDiam = 0.2;
      iSpecies = 1;
      fLight = 35;
      iType = clTreePopulation::seedling;
      bBrowsed = true;
      p_oTree = p_oPop->CreateTree(1, 16, iSpecies, iType, fDiam);
      p_oTree->SetValue(p_oPop->GetHeightCode(iSpecies, iType), fDiam);
      p_oTree->SetValue(p_oPop->GetFloatDataCode("Light", iSpecies, iType), fLight);
      p_oTree->SetValue(p_oPop->GetBoolDataCode("Browsed", iSpecies, iType), bBrowsed);

      fDiam = 0.3;
      iSpecies = 3;
      fLight = 35;
      iType = clTreePopulation::seedling;
      p_oTree = p_oPop->CreateTree(1, 17, iSpecies, iType, fDiam);
      p_oTree->SetValue(p_oPop->GetHeightCode(iSpecies, iType), fDiam);
      p_oTree->SetValue(p_oPop->GetFloatDataCode("Light", iSpecies, iType), fLight);

      fDiam = 2.5;
      iSpecies = 0;
      fLight = 35;
      iType = clTreePopulation::sapling;
      bBrowsed = false;
      p_oTree = p_oPop->CreateTree(1, 18, iSpecies, iType, fDiam);
      p_oTree->SetValue(p_oPop->GetHeightCode(iSpecies, iType), fDiam);
      p_oTree->SetValue(p_oPop->GetFloatDataCode("Light", iSpecies, iType), fLight);
      p_oTree->SetValue(p_oPop->GetBoolDataCode("Browsed", iSpecies, iType), bBrowsed);

      fDiam = 2.5;
      iSpecies = 0;
      fLight = 35;
      iType = clTreePopulation::sapling;
      bBrowsed = true;
      p_oTree = p_oPop->CreateTree(1, 19, iSpecies, iType, fDiam);
      p_oTree->SetValue(p_oPop->GetHeightCode(iSpecies, iType), fDiam);
      p_oTree->SetValue(p_oPop->GetFloatDataCode("Light", iSpecies, iType), fLight);
      p_oTree->SetValue(p_oPop->GetBoolDataCode("Browsed", iSpecies, iType), bBrowsed);

      fDiam = 3.4;
      iSpecies = 1;
      fLight = 35;
      iType = clTreePopulation::sapling;
      bBrowsed = false;
      p_oTree = p_oPop->CreateTree(1, 20, iSpecies, iType, fDiam);
      p_oTree->SetValue(p_oPop->GetHeightCode(iSpecies, iType), fDiam);
      p_oTree->SetValue(p_oPop->GetFloatDataCode("Light", iSpecies, iType), fLight);
      p_oTree->SetValue(p_oPop->GetBoolDataCode("Browsed", iSpecies, iType), bBrowsed);

      fDiam = 3.4;
      iSpecies = 1;
      fLight = 35;
      iType = clTreePopulation::sapling;
      bBrowsed = true;
      p_oTree = p_oPop->CreateTree(1, 21, iSpecies, iType, fDiam);
      p_oTree->SetValue(p_oPop->GetHeightCode(iSpecies, iType), fDiam);
      p_oTree->SetValue(p_oPop->GetFloatDataCode("Light", iSpecies, iType), fLight);
      p_oTree->SetValue(p_oPop->GetBoolDataCode("Browsed", iSpecies, iType), bBrowsed);

      fDiam = 5.4;
      iSpecies = 3;
      fLight = 35;
      iType = clTreePopulation::sapling;
      p_oTree = p_oPop->CreateTree(1, 22, iSpecies, iType, fDiam);
      p_oTree->SetValue(p_oPop->GetHeightCode(iSpecies, iType), fDiam);
      p_oTree->SetValue(p_oPop->GetFloatDataCode("Light", iSpecies, iType), fLight);

      fDiam = 12.6;
      iSpecies = 0;
      fLight = 35;
      iType = clTreePopulation::adult;
      p_oTree = p_oPop->CreateTree(1, 23, iSpecies, iType, fDiam);
      p_oTree->SetValue(p_oPop->GetHeightCode(iSpecies, iType), fDiam);
      p_oTree->SetValue(p_oPop->GetFloatDataCode("Light", iSpecies, iType), fLight);

      fDiam = 30;
      iSpecies = 1;
      fLight = 35;
      iType = clTreePopulation::adult;
      p_oTree = p_oPop->CreateTree(1, 24, iSpecies, iType, fDiam);
      p_oTree->SetValue(p_oPop->GetHeightCode(iSpecies, iType), fDiam);
      p_oTree->SetValue(p_oPop->GetFloatDataCode("Light", iSpecies, iType), fLight);

      fDiam = 23.3;
      iSpecies = 3;
      iType = clTreePopulation::adult;
      p_oTree = p_oPop->CreateTree(1, 25, iSpecies, iType, fDiam);
      p_oTree->SetValue(p_oPop->GetHeightCode(iSpecies, iType), fDiam);
      p_oTree->SetValue(p_oPop->GetFloatDataCode("Light", iSpecies, iType), fLight);

      fDiam = 0.1;
      iSpecies = 0;
      fLight = 80;
      iType = clTreePopulation::seedling;
      bBrowsed = false;
      p_oTree = p_oPop->CreateTree(1, 26, iSpecies, iType, fDiam);
      p_oTree->SetValue(p_oPop->GetHeightCode(iSpecies, iType), fDiam);
      p_oTree->SetValue(p_oPop->GetFloatDataCode("Light", iSpecies, iType), fLight);
      p_oTree->SetValue(p_oPop->GetBoolDataCode("Browsed", iSpecies, iType), bBrowsed);

      fDiam = 0.1;
      iSpecies = 0;
      fLight = 80;
      iType = clTreePopulation::seedling;
      bBrowsed = true;
      p_oTree = p_oPop->CreateTree(1, 27, iSpecies, iType, fDiam);
      p_oTree->SetValue(p_oPop->GetHeightCode(iSpecies, iType), fDiam);
      p_oTree->SetValue(p_oPop->GetFloatDataCode("Light", iSpecies, iType), fLight);
      p_oTree->SetValue(p_oPop->GetBoolDataCode("Browsed", iSpecies, iType), bBrowsed);

      fDiam = 0.2;
      iSpecies = 1;
      fLight = 80;
      iType = clTreePopulation::seedling;
      bBrowsed = false;
      p_oTree = p_oPop->CreateTree(1, 28, iSpecies, iType, fDiam);
      p_oTree->SetValue(p_oPop->GetHeightCode(iSpecies, iType), fDiam);
      p_oTree->SetValue(p_oPop->GetFloatDataCode("Light", iSpecies, iType), fLight);
      p_oTree->SetValue(p_oPop->GetBoolDataCode("Browsed", iSpecies, iType), bBrowsed);

      fDiam = 0.2;
      iSpecies = 1;
      fLight = 80;
      iType = clTreePopulation::seedling;
      bBrowsed = true;
      p_oTree = p_oPop->CreateTree(1, 29, iSpecies, iType, fDiam);
      p_oTree->SetValue(p_oPop->GetHeightCode(iSpecies, iType), fDiam);
      p_oTree->SetValue(p_oPop->GetFloatDataCode("Light", iSpecies, iType), fLight);
      p_oTree->SetValue(p_oPop->GetBoolDataCode("Browsed", iSpecies, iType), bBrowsed);

      fDiam = 0.3;
      iSpecies = 3;
      fLight = 80;
      iType = clTreePopulation::seedling;
      p_oTree = p_oPop->CreateTree(1, 30, iSpecies, iType, fDiam);
      p_oTree->SetValue(p_oPop->GetHeightCode(iSpecies, iType), fDiam);
      p_oTree->SetValue(p_oPop->GetFloatDataCode("Light", iSpecies, iType), fLight);

      fDiam = 2.5;
      iSpecies = 0;
      fLight = 80;
      iType = clTreePopulation::sapling;
      bBrowsed = false;
      p_oTree = p_oPop->CreateTree(1, 31, iSpecies, iType, fDiam);
      p_oTree->SetValue(p_oPop->GetHeightCode(iSpecies, iType), fDiam);
      p_oTree->SetValue(p_oPop->GetFloatDataCode("Light", iSpecies, iType), fLight);
      p_oTree->SetValue(p_oPop->GetBoolDataCode("Browsed", iSpecies, iType), bBrowsed);

      fDiam = 2.5;
      iSpecies = 0;
      fLight = 80;
      iType = clTreePopulation::sapling;
      bBrowsed = true;
      p_oTree = p_oPop->CreateTree(1, 32, iSpecies, iType, fDiam);
      p_oTree->SetValue(p_oPop->GetHeightCode(iSpecies, iType), fDiam);
      p_oTree->SetValue(p_oPop->GetFloatDataCode("Light", iSpecies, iType), fLight);
      p_oTree->SetValue(p_oPop->GetBoolDataCode("Browsed", iSpecies, iType), bBrowsed);

      fDiam = 3.4;
      iSpecies = 1;
      fLight = 80;
      iType = clTreePopulation::sapling;
      bBrowsed = false;
      p_oTree = p_oPop->CreateTree(1, 33, iSpecies, iType, fDiam);
      p_oTree->SetValue(p_oPop->GetHeightCode(iSpecies, iType), fDiam);
      p_oTree->SetValue(p_oPop->GetFloatDataCode("Light", iSpecies, iType), fLight);
      p_oTree->SetValue(p_oPop->GetBoolDataCode("Browsed", iSpecies, iType), bBrowsed);

      fDiam = 3.4;
      iSpecies = 1;
      fLight = 80;
      iType = clTreePopulation::sapling;
      bBrowsed = true;
      p_oTree = p_oPop->CreateTree(1, 34, iSpecies, iType, fDiam);
      p_oTree->SetValue(p_oPop->GetHeightCode(iSpecies, iType), fDiam);
      p_oTree->SetValue(p_oPop->GetFloatDataCode("Light", iSpecies, iType), fLight);
      p_oTree->SetValue(p_oPop->GetBoolDataCode("Browsed", iSpecies, iType), bBrowsed);

      fDiam = 5.4;
      iSpecies = 3;
      fLight = 80;
      iType = clTreePopulation::sapling;
      p_oTree = p_oPop->CreateTree(1, 35, iSpecies, iType, fDiam);
      p_oTree->SetValue(p_oPop->GetHeightCode(iSpecies, iType), fDiam);
      p_oTree->SetValue(p_oPop->GetFloatDataCode("Light", iSpecies, iType), fLight);

      fDiam = 12.6;
      iSpecies = 0;
      fLight = 80;
      iType = clTreePopulation::adult;
      p_oTree = p_oPop->CreateTree(1, 36, iSpecies, iType, fDiam);
      p_oTree->SetValue(p_oPop->GetHeightCode(iSpecies, iType), fDiam);
      p_oTree->SetValue(p_oPop->GetFloatDataCode("Light", iSpecies, iType), fLight);

      fDiam = 30;
      iSpecies = 1;
      fLight = 80;
      iType = clTreePopulation::adult;
      p_oTree = p_oPop->CreateTree(1, 37, iSpecies, iType, fDiam);
      p_oTree->SetValue(p_oPop->GetHeightCode(iSpecies, iType), fDiam);
      p_oTree->SetValue(p_oPop->GetFloatDataCode("Light", iSpecies, iType), fLight);

      fDiam = 23.3;
      iSpecies = 3;
      fLight = 80;
      iType = clTreePopulation::adult;
      p_oTree = p_oPop->CreateTree(1, 38, iSpecies, iType, fDiam);
      p_oTree->SetValue(p_oPop->GetHeightCode(iSpecies, iType), fDiam);
      p_oTree->SetValue(p_oPop->GetFloatDataCode("Light", iSpecies, iType), fLight);
    }

    //Now run mortality, but skip light and browse
    for (i = 2; i < p_oSimManager->GetNumberOfBehaviors(); i++) {
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
      iIndex = (int)fY;
      p_iNumTrees[iIndex]++;
      p_oTree = p_oAllTrees->NextTree();
    }

    //Compare to expected results
    fExpected = 601.8042022;
    EXPECT_LT(fabs(p_iNumTrees[0] - fExpected)/fExpected, 0.1);
    fExpected = 680.5827985;
    EXPECT_LT(fabs(p_iNumTrees[1] - fExpected)/fExpected, 0.1);
    fExpected = 929.354059;
    EXPECT_LT(fabs(p_iNumTrees[2] - fExpected)/fExpected, 0.1);
    fExpected = 733.9152996;
    EXPECT_LT(fabs(p_iNumTrees[3] - fExpected)/fExpected, 0.1);
    fExpected = 822.4304053;
    EXPECT_LT(fabs(p_iNumTrees[4] - fExpected)/fExpected, 0.1);
    fExpected = 958.6121059;
    EXPECT_LT(fabs(p_iNumTrees[5] - fExpected)/fExpected, 0.1);
    fExpected = 950.8686124;
    EXPECT_LT(fabs(p_iNumTrees[6] - fExpected)/fExpected, 0.1);
    fExpected = 999.9820105;
    EXPECT_LT(fabs(p_iNumTrees[7] - fExpected)/fExpected, 0.1);
    fExpected = 899.9041754;
    EXPECT_LT(fabs(p_iNumTrees[8] - fExpected)/fExpected, 0.1);
    fExpected = 1000;
    EXPECT_LT(fabs(p_iNumTrees[9] - fExpected)/fExpected, 0.1);
    fExpected = 997.8084568;
    EXPECT_LT(fabs(p_iNumTrees[10] - fExpected)/fExpected, 0.1);
    fExpected = 1000;
    EXPECT_LT(fabs(p_iNumTrees[11] - fExpected)/fExpected, 0.1);
    fExpected = 1000;
    EXPECT_LT(fabs(p_iNumTrees[12] - fExpected)/fExpected, 0.1);
    fExpected = 601.8042022;
    EXPECT_LT(fabs(p_iNumTrees[13] - fExpected)/fExpected, 0.1);
    fExpected = 994.1496699;
    EXPECT_LT(fabs(p_iNumTrees[14] - fExpected)/fExpected, 0.1);
    fExpected = 929.354059;
    EXPECT_LT(fabs(p_iNumTrees[15] - fExpected)/fExpected, 0.1);
    fExpected = 734.8269147;
    EXPECT_LT(fabs(p_iNumTrees[16] - fExpected)/fExpected, 0.1);
    fExpected = 822.4410514;
    EXPECT_LT(fabs(p_iNumTrees[17] - fExpected)/fExpected, 0.1);
    fExpected = 958.6121059;
    EXPECT_LT(fabs(p_iNumTrees[18] - fExpected)/fExpected, 0.1);
    fExpected = 999.1001272;
    EXPECT_LT(fabs(p_iNumTrees[19] - fExpected)/fExpected, 0.1);
    fExpected = 999.9820105;
    EXPECT_LT(fabs(p_iNumTrees[20] - fExpected)/fExpected, 0.1);
    fExpected = 900.24710;
    EXPECT_LT(fabs(p_iNumTrees[21] - fExpected)/fExpected, 0.1);
    fExpected = 1000;
    EXPECT_LT(fabs(p_iNumTrees[22] - fExpected)/fExpected, 0.1);
    fExpected = 997.8084568;
    EXPECT_LT(fabs(p_iNumTrees[23] - fExpected)/fExpected, 0.1);
    fExpected = 1000;
    EXPECT_LT(fabs(p_iNumTrees[24] - fExpected)/fExpected, 0.1);
    fExpected = 1000;
    EXPECT_LT(fabs(p_iNumTrees[25] - fExpected)/fExpected, 0.1);
    fExpected = 601.8042022;
    EXPECT_LT(fabs(p_iNumTrees[26] - fExpected)/fExpected, 0.1);
    fExpected = 1000;
    EXPECT_LT(fabs(p_iNumTrees[27] - fExpected)/fExpected, 0.1);
    fExpected = 929.354059;
    EXPECT_LT(fabs(p_iNumTrees[28] - fExpected)/fExpected, 0.1);
    fExpected = 735.7163028;
    EXPECT_LT(fabs(p_iNumTrees[29] - fExpected)/fExpected, 0.1);
    fExpected = 822.4650028;
    EXPECT_LT(fabs(p_iNumTrees[30] - fExpected)/fExpected, 0.1);
    fExpected = 958.6121059;
    EXPECT_LT(fabs(p_iNumTrees[31] - fExpected)/fExpected, 0.1);
    fExpected = 1000;
    EXPECT_LT(fabs(p_iNumTrees[32] - fExpected)/fExpected, 0.1);
    fExpected = 999.9820105;
    EXPECT_LT(fabs(p_iNumTrees[33] - fExpected)/fExpected, 0.1);
    fExpected = 900.5816773;
    EXPECT_LT(fabs(p_iNumTrees[34] - fExpected)/fExpected, 0.1);
    fExpected = 1000;
    EXPECT_LT(fabs(p_iNumTrees[35] - fExpected)/fExpected, 0.1);
    fExpected = 997.8084568;
    EXPECT_LT(fabs(p_iNumTrees[36] - fExpected)/fExpected, 0.1);
    fExpected = 1000;
    EXPECT_LT(fabs(p_iNumTrees[37] - fExpected)/fExpected, 0.1);
    fExpected = 1000;
    EXPECT_LT(fabs(p_iNumTrees[38] - fExpected)/fExpected, 0.1);

    delete[] p_iNumTrees;
    delete p_oSimManager;
  } catch (modelErr &e) {
    delete[] p_iNumTrees;
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

/////////////////////////////////////////////////////////////////////////////
// NormalProcessingRun2()
// Tests normal processing run 2. WriteHeightGLIWeibullMortalityXMLFile2() does
// setup. Timestep length is 3 years and there is a light grid present. 1000
// copies of each of 27 trees is created of 3 species and assigned to a mix of
// light levels. Then mortality is run. We check the number left of each tree
// type to see if it is approximately the right number.
/////////////////////////////////////////////////////////////////////////////
TEST(HeightGLIWeibullMortality, NormalProcessingRun2) {
  clTreePopulation * p_oPop;
  clTreeSearch *p_oAllTrees;
  clTree *p_oTree;
  float fDiam, fLight, fY, fExpected;
  int *p_iNumTrees = new int[27], i,
      iSpecies, iType;

  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {

    for (i = 0; i < 27; i++) {
      p_iNumTrees[i] = 0;
    }

    p_oSimManager->ReadFile(WriteHeightGLIWeibullMortalityXMLFile2());
    p_oPop = (clTreePopulation *) p_oSimManager->GetPopulationObject("treepopulation");

    //Add 1000 trees to the plot of each kind
    //Each tree's diameter is also its height
    for (i = 0; i < 1000; i++) {
      fDiam = 0.1;
      iSpecies = 0;
      fLight = 15;
      iType = clTreePopulation::seedling;
      p_oTree = p_oPop->CreateTree(1, 1, iSpecies, iType, fDiam);
      p_oTree->SetValue(p_oPop->GetHeightCode(iSpecies, iType), fDiam);
      p_oTree->SetValue(p_oPop->GetFloatDataCode("Light", iSpecies, iType), fLight);

      fDiam = 0.2;
      iSpecies = 1;
      fLight = 15;
      iType = clTreePopulation::seedling;
      p_oTree = p_oPop->CreateTree(1, 1, iSpecies, iType, fDiam);
      p_oTree->SetValue(p_oPop->GetHeightCode(iSpecies, iType), fDiam);
      p_oTree->SetValue(p_oPop->GetFloatDataCode("Light", iSpecies, iType), fLight);

      fDiam = 0.3;
      iSpecies = 3;
      fLight = 15;
      iType = clTreePopulation::seedling;
      p_oTree = p_oPop->CreateTree(1, 1, iSpecies, iType, fDiam);
      p_oTree->SetValue(p_oPop->GetHeightCode(iSpecies, iType), fDiam);
      p_oTree->SetValue(p_oPop->GetFloatDataCode("Light", iSpecies, iType), fLight);

      fDiam = 2.5;
      iSpecies = 0;
      fLight = 15;
      iType = clTreePopulation::sapling;
      p_oTree = p_oPop->CreateTree(1, 1, iSpecies, iType, fDiam);
      p_oTree->SetValue(p_oPop->GetHeightCode(iSpecies, iType), fDiam);
      p_oTree->SetValue(p_oPop->GetFloatDataCode("Light", iSpecies, iType), fLight);

      fDiam = 3.4;
      iSpecies = 1;
      fLight = 15;
      iType = clTreePopulation::sapling;
      p_oTree = p_oPop->CreateTree(1, 1, iSpecies, iType, fDiam);
      p_oTree->SetValue(p_oPop->GetHeightCode(iSpecies, iType), fDiam);
      p_oTree->SetValue(p_oPop->GetFloatDataCode("Light", iSpecies, iType), fLight);

      fDiam = 5.4;
      iSpecies = 3;
      fLight = 15;
      iType = clTreePopulation::sapling;
      p_oTree = p_oPop->CreateTree(1, 1, iSpecies, iType, fDiam);
      p_oTree->SetValue(p_oPop->GetHeightCode(iSpecies, iType), fDiam);
      p_oTree->SetValue(p_oPop->GetFloatDataCode("Light", iSpecies, iType), fLight);

      fDiam = 12.6;
      iSpecies = 0;
      fLight = 15;
      iType = clTreePopulation::adult;
      p_oTree = p_oPop->CreateTree(1, 1, iSpecies, iType, fDiam);
      p_oTree->SetValue(p_oPop->GetHeightCode(iSpecies, iType), fDiam);
      p_oTree->SetValue(p_oPop->GetFloatDataCode("Light", iSpecies, iType), fLight);

      fDiam = 30;
      iSpecies = 1;
      fLight = 15;
      iType = clTreePopulation::adult;
      p_oTree = p_oPop->CreateTree(1, 1, iSpecies, iType, fDiam);
      p_oTree->SetValue(p_oPop->GetHeightCode(iSpecies, iType), fDiam);
      p_oTree->SetValue(p_oPop->GetFloatDataCode("Light", iSpecies, iType), fLight);

      fDiam = 23.3;
      iSpecies = 3;
      fLight = 15;
      iType = clTreePopulation::adult;
      p_oTree = p_oPop->CreateTree(1, 1, iSpecies, iType, fDiam);
      p_oTree->SetValue(p_oPop->GetHeightCode(iSpecies, iType), fDiam);
      p_oTree->SetValue(p_oPop->GetFloatDataCode("Light", iSpecies, iType), fLight);

      fDiam = 0.1;
      iSpecies = 0;
      fLight = 35;
      iType = clTreePopulation::seedling;
      p_oTree = p_oPop->CreateTree(1, 9, iSpecies, iType, fDiam);
      p_oTree->SetValue(p_oPop->GetHeightCode(iSpecies, iType), fDiam);
      p_oTree->SetValue(p_oPop->GetFloatDataCode("Light", iSpecies, iType), fLight);

      fDiam = 0.2;
      iSpecies = 1;
      fLight = 35;
      iType = clTreePopulation::seedling;
      p_oTree = p_oPop->CreateTree(1, 9, iSpecies, iType, fDiam);
      p_oTree->SetValue(p_oPop->GetHeightCode(iSpecies, iType), fDiam);
      p_oTree->SetValue(p_oPop->GetFloatDataCode("Light", iSpecies, iType), fLight);

      fDiam = 0.3;
      iSpecies = 3;
      fLight = 35;
      iType = clTreePopulation::seedling;
      p_oTree = p_oPop->CreateTree(1, 9, iSpecies, iType, fDiam);
      p_oTree->SetValue(p_oPop->GetHeightCode(iSpecies, iType), fDiam);
      p_oTree->SetValue(p_oPop->GetFloatDataCode("Light", iSpecies, iType), fLight);

      fDiam = 2.5;
      iSpecies = 0;
      fLight = 35;
      iType = clTreePopulation::sapling;
      p_oTree = p_oPop->CreateTree(1, 9, iSpecies, iType, fDiam);
      p_oTree->SetValue(p_oPop->GetHeightCode(iSpecies, iType), fDiam);
      p_oTree->SetValue(p_oPop->GetFloatDataCode("Light", iSpecies, iType), fLight);

      fDiam = 3.4;
      iSpecies = 1;
      fLight = 35;
      iType = clTreePopulation::sapling;
      p_oTree = p_oPop->CreateTree(1, 9, iSpecies, iType, fDiam);
      p_oTree->SetValue(p_oPop->GetHeightCode(iSpecies, iType), fDiam);
      p_oTree->SetValue(p_oPop->GetFloatDataCode("Light", iSpecies, iType), fLight);

      fDiam = 5.4;
      iSpecies = 3;
      fLight = 35;
      iType = clTreePopulation::sapling;
      p_oTree = p_oPop->CreateTree(1, 9, iSpecies, iType, fDiam);
      p_oTree->SetValue(p_oPop->GetHeightCode(iSpecies, iType), fDiam);
      p_oTree->SetValue(p_oPop->GetFloatDataCode("Light", iSpecies, iType), fLight);

      fDiam = 12.6;
      iSpecies = 0;
      fLight = 35;
      iType = clTreePopulation::adult;
      p_oTree = p_oPop->CreateTree(1, 9, iSpecies, iType, fDiam);
      p_oTree->SetValue(p_oPop->GetHeightCode(iSpecies, iType), fDiam);
      p_oTree->SetValue(p_oPop->GetFloatDataCode("Light", iSpecies, iType), fLight);

      fDiam = 30;
      iSpecies = 1;
      fLight = 35;
      iType = clTreePopulation::adult;
      p_oTree = p_oPop->CreateTree(1, 9, iSpecies, iType, fDiam);
      p_oTree->SetValue(p_oPop->GetHeightCode(iSpecies, iType), fDiam);
      p_oTree->SetValue(p_oPop->GetFloatDataCode("Light", iSpecies, iType), fLight);

      fDiam = 23.3;
      iSpecies = 3;
      iType = clTreePopulation::adult;
      p_oTree = p_oPop->CreateTree(1, 9, iSpecies, iType, fDiam);
      p_oTree->SetValue(p_oPop->GetHeightCode(iSpecies, iType), fDiam);
      p_oTree->SetValue(p_oPop->GetFloatDataCode("Light", iSpecies, iType), fLight);

      fDiam = 0.1;
      iSpecies = 0;
      fLight = 80;
      iType = clTreePopulation::seedling;
      p_oTree = p_oPop->CreateTree(1, 17, iSpecies, iType, fDiam);
      p_oTree->SetValue(p_oPop->GetHeightCode(iSpecies, iType), fDiam);
      p_oTree->SetValue(p_oPop->GetFloatDataCode("Light", iSpecies, iType), fLight);

      fDiam = 0.2;
      iSpecies = 1;
      fLight = 80;
      iType = clTreePopulation::seedling;
      p_oTree = p_oPop->CreateTree(1, 17, iSpecies, iType, fDiam);
      p_oTree->SetValue(p_oPop->GetHeightCode(iSpecies, iType), fDiam);
      p_oTree->SetValue(p_oPop->GetFloatDataCode("Light", iSpecies, iType), fLight);

      fDiam = 0.3;
      iSpecies = 3;
      fLight = 80;
      iType = clTreePopulation::seedling;
      p_oTree = p_oPop->CreateTree(1, 17, iSpecies, iType, fDiam);
      p_oTree->SetValue(p_oPop->GetHeightCode(iSpecies, iType), fDiam);
      p_oTree->SetValue(p_oPop->GetFloatDataCode("Light", iSpecies, iType), fLight);

      fDiam = 2.5;
      iSpecies = 0;
      fLight = 80;
      iType = clTreePopulation::sapling;
      p_oTree = p_oPop->CreateTree(1, 17, iSpecies, iType, fDiam);
      p_oTree->SetValue(p_oPop->GetHeightCode(iSpecies, iType), fDiam);
      p_oTree->SetValue(p_oPop->GetFloatDataCode("Light", iSpecies, iType), fLight);

      fDiam = 3.4;
      iSpecies = 1;
      fLight = 80;
      iType = clTreePopulation::sapling;
      p_oTree = p_oPop->CreateTree(1, 17, iSpecies, iType, fDiam);
      p_oTree->SetValue(p_oPop->GetHeightCode(iSpecies, iType), fDiam);
      p_oTree->SetValue(p_oPop->GetFloatDataCode("Light", iSpecies, iType), fLight);

      fDiam = 5.4;
      iSpecies = 3;
      fLight = 80;
      iType = clTreePopulation::sapling;
      p_oTree = p_oPop->CreateTree(1, 17, iSpecies, iType, fDiam);
      p_oTree->SetValue(p_oPop->GetHeightCode(iSpecies, iType), fDiam);
      p_oTree->SetValue(p_oPop->GetFloatDataCode("Light", iSpecies, iType), fLight);

      fDiam = 12.6;
      iSpecies = 0;
      fLight = 80;
      iType = clTreePopulation::adult;
      p_oTree = p_oPop->CreateTree(1, 17, iSpecies, iType, fDiam);
      p_oTree->SetValue(p_oPop->GetHeightCode(iSpecies, iType), fDiam);
      p_oTree->SetValue(p_oPop->GetFloatDataCode("Light", iSpecies, iType), fLight);

      fDiam = 30;
      iSpecies = 1;
      fLight = 80;
      iType = clTreePopulation::adult;
      p_oTree = p_oPop->CreateTree(1, 17, iSpecies, iType, fDiam);
      p_oTree->SetValue(p_oPop->GetHeightCode(iSpecies, iType), fDiam);
      p_oTree->SetValue(p_oPop->GetFloatDataCode("Light", iSpecies, iType), fLight);

      fDiam = 23.3;
      iSpecies = 3;
      fLight = 80;
      iType = clTreePopulation::adult;
      p_oTree = p_oPop->CreateTree(1, 17, iSpecies, iType, fDiam);
      p_oTree->SetValue(p_oPop->GetHeightCode(iSpecies, iType), fDiam);
      p_oTree->SetValue(p_oPop->GetFloatDataCode("Light", iSpecies, iType), fLight);
    }

    //Now run mortality, but skip light
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
    fExpected = 217.9544035;
    EXPECT_LT(fabs(p_iNumTrees[0] - fExpected)/fExpected, 0.1);
    fExpected = 802.6821408;
    EXPECT_LT(fabs(p_iNumTrees[1] - fExpected)/fExpected, 0.1);
    fExpected = 556.2851589;
    EXPECT_LT(fabs(p_iNumTrees[2] - fExpected)/fExpected, 0.1);
    fExpected = 880.9042954;
    EXPECT_LT(fabs(p_iNumTrees[3] - fExpected)/fExpected, 0.1);
    fExpected = 999.9460325;
    EXPECT_LT(fabs(p_iNumTrees[4] - fExpected)/fExpected, 0.1);
    fExpected = 1000;
    EXPECT_LT(fabs(p_iNumTrees[5] - fExpected)/fExpected, 0.1);
    fExpected = 993.4397684;
    EXPECT_LT(fabs(p_iNumTrees[6] - fExpected)/fExpected, 0.1);
    fExpected = 1000;
    EXPECT_LT(fabs(p_iNumTrees[7] - fExpected)/fExpected, 0.1);
    fExpected = 1000;
    EXPECT_LT(fabs(p_iNumTrees[8] - fExpected)/fExpected, 0.1);
    fExpected = 217.9544035;
    EXPECT_LT(fabs(p_iNumTrees[9] - fExpected)/fExpected, 0.1);
    fExpected = 802.6821408;
    EXPECT_LT(fabs(p_iNumTrees[10] - fExpected)/fExpected, 0.1);
    fExpected = 556.3067619;
    EXPECT_LT(fabs(p_iNumTrees[11] - fExpected)/fExpected, 0.1);
    fExpected = 880.9042954;
    EXPECT_LT(fabs(p_iNumTrees[12] - fExpected)/fExpected, 0.1);
    fExpected = 999.9460325;
    EXPECT_LT(fabs(p_iNumTrees[13] - fExpected)/fExpected, 0.1);
    fExpected = 1000;
    EXPECT_LT(fabs(p_iNumTrees[14] - fExpected)/fExpected, 0.1);
    fExpected = 993.4397684;
    EXPECT_LT(fabs(p_iNumTrees[15] - fExpected)/fExpected, 0.1);
    fExpected = 1000;
    EXPECT_LT(fabs(p_iNumTrees[16] - fExpected)/fExpected, 0.1);
    fExpected = 1000;
    EXPECT_LT(fabs(p_iNumTrees[17] - fExpected)/fExpected, 0.1);
    fExpected = 217.9544035;
    EXPECT_LT(fabs(p_iNumTrees[18] - fExpected)/fExpected, 0.15);
    fExpected = 802.6821408;
    EXPECT_LT(fabs(p_iNumTrees[19] - fExpected)/fExpected, 0.1);
    fExpected = 556.3553661;
    EXPECT_LT(fabs(p_iNumTrees[20] - fExpected)/fExpected, 0.1);
    fExpected = 880.9042954;
    EXPECT_LT(fabs(p_iNumTrees[21] - fExpected)/fExpected, 0.1);
    fExpected = 999.9460325;
    EXPECT_LT(fabs(p_iNumTrees[22] - fExpected)/fExpected, 0.1);
    fExpected = 1000;
    EXPECT_LT(fabs(p_iNumTrees[23] - fExpected)/fExpected, 0.1);
    fExpected = 993.4397684;
    EXPECT_LT(fabs(p_iNumTrees[24] - fExpected)/fExpected, 0.1);
    fExpected = 1000;
    EXPECT_LT(fabs(p_iNumTrees[25] - fExpected)/fExpected, 0.1);
    fExpected = 1000;
    EXPECT_LT(fabs(p_iNumTrees[26] - fExpected)/fExpected, 0.1);

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
TEST(HeightGLIWeibullMortality, ErrorProcessing)
{
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try
  {
    p_oSimManager->ReadFile( WriteHeightGLIWeibullMortalityXMLErrorFile1() );
    FAIL() << "TestHeightGLIWeibullMortality error processing didn't catch error for WriteHeightGLIWeibullMortalityXMLErrorFile1.";
  }
  catch ( modelErr& err )
  {
    if ( err.sFunction.compare("clHeightGLIWeibullMortality::ReadParameterFileData" ) != 0 )
    {
      FAIL() << "TestHeightGLIWeibullMortality error processing caught wrong error for WriteHeightGLIWeibullMortalityXMLErrorFile1.";
    }
    ;
  }

  try
  {
    p_oSimManager->ReadFile( WriteHeightGLIWeibullMortalityXMLErrorFile2() );
    FAIL() << "TestHeightGLIWeibullMortality error processing didn't catch error for WriteHeightGLIWeibullMortalityXMLErrorFile2.";
  }
  catch ( modelErr& err )
  {
    if ( err.sFunction.compare("clHeightGLIWeibullMortality::GetTreeDataMemberCodes" ) != 0 )
    {
      FAIL() << "TestHeightGLIWeibullMortality error processing caught wrong error for WriteHeightGLIWeibullMortalityXMLErrorFile2.";
    }
    ;
  }

  try
  {
    p_oSimManager->ReadFile( WriteHeightGLIWeibullMortalityXMLErrorFile3() );
    FAIL() << "TestHeightGLIWeibullMortality error processing didn't catch error for WriteHeightGLIWeibullMortalityXMLErrorFile3.";
  }
  catch ( modelErr& err )
  {
    if ( err.sFunction.compare("clHeightGLIWeibullMortality::ReadParameterFileData" ) != 0 )
    {
      FAIL() << "TestHeightGLIWeibullMortality error processing caught wrong error for WriteHeightGLIWeibullMortalityXMLErrorFile3.";
    }
    ;
  }
  delete p_oSimManager;
}

////////////////////////////////////////////////////////////////////////////
// WriteHeightGLIWeibullMortalityXMLFile1()
////////////////////////////////////////////////////////////////////////////
const char* WriteHeightGLIWeibullMortalityXMLFile1() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  //WriteHeightGLIWeibullMortality file
  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
      << "<paramFile fileCode=\"06010101\">"
      << "<plot>"
      << "<timesteps>1</timesteps>"
      << "<yearsPerTimestep>1</yearsPerTimestep>";

  WriteHeightGLIWeibullMortalityCommonStuff(oOut);

  oOut << "<behaviorList>"
      << "<behavior>"
      << "<behaviorName>RandomBrowse</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>1</listPosition>"
      << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_1\" type=\"Seedling\"/>"
      << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_2\" type=\"Seedling\"/>"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>BasalAreaLight</behaviorName>"
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
      << "<behaviorName>HeightGLIWeibullMortality</behaviorName>"
      << "<version>2</version>"
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
      << "<behaviorName>RemoveDead</behaviorName>"
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
      << "<RandomBrowse1>"
      << "<di_randBrowsePDF>0</di_randBrowsePDF>"
      << "<di_randBrowseProb>"
      << "<di_rbpVal species=\"Species_1\">0.33</di_rbpVal>"
      << "<di_rbpVal species=\"Species_2\">1</di_rbpVal>"
      << "</di_randBrowseProb>"
      << "</RandomBrowse1>"
      << "<BasalAreaLight2>"
      << "<li_baLightSearchRadius>15</li_baLightSearchRadius>"
      << "<li_baLightA>12.4</li_baLightA>"
      << "<li_baConiferLightB>1.8</li_baConiferLightB>"
      << "<li_baConiferLightC>2.1</li_baConiferLightC>"
      << "<li_baAngiospermLightB>3.83</li_baAngiospermLightB>"
      << "<li_baAngiospermLightC>3.04</li_baAngiospermLightC>"
      << "<li_baLightSigma>0.82</li_baLightSigma>"
      << "<li_baLightChangeThreshold>0.05</li_baLightChangeThreshold>"
      << "<li_baLightMinDBH>10</li_baLightMinDBH>"
      << "<li_baTreeType>"
      << "<li_bttVal species=\"Species_1\">1</li_bttVal>"
      << "<li_bttVal species=\"Species_2\">0</li_bttVal>"
      << "<li_bttVal species=\"Species_3\">1</li_bttVal>"
      << "<li_bttVal species=\"Species_4\">0</li_bttVal>"
      << "</li_baTreeType>"
      << "</BasalAreaLight2>";

  oOut << "<HeightGLIWeibullMortality3>"
      << "<mo_heightGLIWeibA>"
      << "<mo_hgwaVal species=\"Species_1\">2.1</mo_hgwaVal>"
      << "<mo_hgwaVal species=\"Species_2\">4.37</mo_hgwaVal>"
      << "<mo_hgwaVal species=\"Species_4\">3.564</mo_hgwaVal>"
      << "</mo_heightGLIWeibA>"
      << "<mo_heightGLIWeibB>"
      << "<mo_hgwbVal species=\"Species_1\">0.415</mo_hgwbVal>"
      << "<mo_hgwbVal species=\"Species_2\">0.659</mo_hgwbVal>"
      << "<mo_hgwbVal species=\"Species_4\">1.449</mo_hgwbVal>"
      << "</mo_heightGLIWeibB>"
      << "<mo_heightGLIWeibC>"
      << "<mo_hgwcVal species=\"Species_1\">0</mo_hgwcVal>"
      << "<mo_hgwcVal species=\"Species_2\">1.136</mo_hgwcVal>"
      << "<mo_hgwcVal species=\"Species_4\">2.99781E-06</mo_hgwcVal>"
      << "</mo_heightGLIWeibC>"
      << "<mo_heightGLIWeibD>"
      << "<mo_hgwdVal species=\"Species_1\">3.838</mo_hgwdVal>"
      << "<mo_hgwdVal species=\"Species_2\">0</mo_hgwdVal>"
      << "<mo_hgwdVal species=\"Species_4\">1</mo_hgwdVal>"
      << "</mo_heightGLIWeibD>"
      << "<mo_heightGLIWeibMaxMort>"
      << "<mo_hgwmmVal species=\"Species_1\">0.893</mo_hgwmmVal>"
      << "<mo_hgwmmVal species=\"Species_2\">0.999</mo_hgwmmVal>"
      << "<mo_hgwmmVal species=\"Species_4\">0.331</mo_hgwmmVal>"
      << "</mo_heightGLIWeibMaxMort>"
      << "<mo_heightGLIWeibBrowsedA>"
      << "<mo_hgwbaVal species=\"Species_1\">0.3</mo_hgwbaVal>"
      << "<mo_hgwbaVal species=\"Species_2\">0.7</mo_hgwbaVal>"
      << "<mo_hgwbaVal species=\"Species_4\">0.5</mo_hgwbaVal>"
      << "</mo_heightGLIWeibBrowsedA>"
      << "<mo_heightGLIWeibBrowsedB>"
      << "<mo_hgwbbVal species=\"Species_1\">2</mo_hgwbbVal>"
      << "<mo_hgwbbVal species=\"Species_2\">0.5</mo_hgwbbVal>"
      << "<mo_hgwbbVal species=\"Species_4\">0.7</mo_hgwbbVal>"
      << "</mo_heightGLIWeibBrowsedB>"
      << "<mo_heightGLIWeibBrowsedC>"
      << "<mo_hgwbcVal species=\"Species_1\">0.004</mo_hgwbcVal>"
      << "<mo_hgwbcVal species=\"Species_2\">1</mo_hgwbcVal>"
      << "<mo_hgwbcVal species=\"Species_4\">0.0035</mo_hgwbcVal>"
      << "</mo_heightGLIWeibBrowsedC>"
      << "<mo_heightGLIWeibBrowsedD>"
      << "<mo_hgwbdVal species=\"Species_1\">2</mo_hgwbdVal>"
      << "<mo_hgwbdVal species=\"Species_2\">0.004</mo_hgwbdVal>"
      << "<mo_hgwbdVal species=\"Species_4\">1</mo_hgwbdVal>"
      << "</mo_heightGLIWeibBrowsedD>"
      << "<mo_heightGLIWeibBrowsedMaxMort>"
      << "<mo_hgwbmmVal species=\"Species_1\">0.788</mo_hgwbmmVal>"
      << "<mo_hgwbmmVal species=\"Species_2\">1</mo_hgwbmmVal>"
      << "<mo_hgwbmmVal species=\"Species_4\">0.977</mo_hgwbmmVal>"
      << "</mo_heightGLIWeibBrowsedMaxMort>"
      << "</HeightGLIWeibullMortality3>";

  oOut << "</paramFile>";

  oOut.close();

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteHeightGLIWeibullMortalityXMLFile2()
////////////////////////////////////////////////////////////////////////////
const char* WriteHeightGLIWeibullMortalityXMLFile2() {
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

  WriteHeightGLIWeibullMortalityCommonStuff(oOut);

  oOut << "<behaviorList>"
      << "<behavior>"
      << "<behaviorName>BasalAreaLight</behaviorName>"
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
      << "<behaviorName>HeightGLIWeibullMortality</behaviorName>"
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
      << "<BasalAreaLight1>"
      << "<li_baLightSearchRadius>15</li_baLightSearchRadius>"
      << "<li_baLightA>12.4</li_baLightA>"
      << "<li_baConiferLightB>1.8</li_baConiferLightB>"
      << "<li_baConiferLightC>2.1</li_baConiferLightC>"
      << "<li_baAngiospermLightB>3.83</li_baAngiospermLightB>"
      << "<li_baAngiospermLightC>3.04</li_baAngiospermLightC>"
      << "<li_baLightSigma>0.82</li_baLightSigma>"
      << "<li_baLightChangeThreshold>0.05</li_baLightChangeThreshold>"
      << "<li_baLightMinDBH>10</li_baLightMinDBH>"
      << "<li_baTreeType>"
      << "<li_bttVal species=\"Species_1\">1</li_bttVal>"
      << "<li_bttVal species=\"Species_2\">0</li_bttVal>"
      << "<li_bttVal species=\"Species_3\">1</li_bttVal>"
      << "<li_bttVal species=\"Species_4\">0</li_bttVal>"
      << "</li_baTreeType>"
      << "</BasalAreaLight1>"
      << "<HeightGLIWeibullMortality2>"
      << "<mo_heightGLIWeibA>"
      << "<mo_hgwaVal species=\"Species_1\">2.1</mo_hgwaVal>"
      << "<mo_hgwaVal species=\"Species_2\">4.37</mo_hgwaVal>"
      << "<mo_hgwaVal species=\"Species_4\">3.564</mo_hgwaVal>"
      << "</mo_heightGLIWeibA>"
      << "<mo_heightGLIWeibB>"
      << "<mo_hgwbVal species=\"Species_1\">0.415</mo_hgwbVal>"
      << "<mo_hgwbVal species=\"Species_2\">0.659</mo_hgwbVal>"
      << "<mo_hgwbVal species=\"Species_4\">1.449</mo_hgwbVal>"
      << "</mo_heightGLIWeibB>"
      << "<mo_heightGLIWeibC>"
      << "<mo_hgwcVal species=\"Species_1\">0</mo_hgwcVal>"
      << "<mo_hgwcVal species=\"Species_2\">1.136</mo_hgwcVal>"
      << "<mo_hgwcVal species=\"Species_4\">2.99781E-06</mo_hgwcVal>"
      << "</mo_heightGLIWeibC>"
      << "<mo_heightGLIWeibD>"
      << "<mo_hgwdVal species=\"Species_1\">3.838</mo_hgwdVal>"
      << "<mo_hgwdVal species=\"Species_2\">0</mo_hgwdVal>"
      << "<mo_hgwdVal species=\"Species_4\">1</mo_hgwdVal>"
      << "</mo_heightGLIWeibD>"
      << "<mo_heightGLIWeibMaxMort>"
      << "<mo_hgwmmVal species=\"Species_1\">0.893</mo_hgwmmVal>"
      << "<mo_hgwmmVal species=\"Species_2\">0.999</mo_hgwmmVal>"
      << "<mo_hgwmmVal species=\"Species_4\">0.331</mo_hgwmmVal>"
      << "</mo_heightGLIWeibMaxMort>"
      << "</HeightGLIWeibullMortality2>";

  oOut << "</paramFile>";

  oOut.close();

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteHeightGLIWeibullMortalityXMLErrorFile1()
////////////////////////////////////////////////////////////////////////////
const char* WriteHeightGLIWeibullMortalityXMLErrorFile1() {
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

  WriteHeightGLIWeibullMortalityCommonStuff(oOut);

  oOut << "<behaviorList>"
      << "<behavior>"
      << "<behaviorName>BasalAreaLight</behaviorName>"
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
      << "<behaviorName>HeightGLIWeibullMortality</behaviorName>"
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
      << "<BasalAreaLight1>"
      << "<li_baLightSearchRadius>15</li_baLightSearchRadius>"
      << "<li_baLightA>12.4</li_baLightA>"
      << "<li_baConiferLightB>1.8</li_baConiferLightB>"
      << "<li_baConiferLightC>2.1</li_baConiferLightC>"
      << "<li_baAngiospermLightB>3.83</li_baAngiospermLightB>"
      << "<li_baAngiospermLightC>3.04</li_baAngiospermLightC>"
      << "<li_baLightSigma>0.82</li_baLightSigma>"
      << "<li_baLightChangeThreshold>0.05</li_baLightChangeThreshold>"
      << "<li_baLightMinDBH>10</li_baLightMinDBH>"
      << "<li_baTreeType>"
      << "<li_bttVal species=\"Species_1\">1</li_bttVal>"
      << "<li_bttVal species=\"Species_2\">0</li_bttVal>"
      << "<li_bttVal species=\"Species_3\">1</li_bttVal>"
      << "<li_bttVal species=\"Species_4\">0</li_bttVal>"
      << "</li_baTreeType>"
      << "</BasalAreaLight1>";

  oOut << "<HeightGLIWeibullMortality2>"
      << "<mo_heightGLIWeibA>"
      << "<mo_hgwaVal species=\"Species_1\">2.1</mo_hgwaVal>"
      << "<mo_hgwaVal species=\"Species_2\">4.37</mo_hgwaVal>"
      << "<mo_hgwaVal species=\"Species_4\">3.564</mo_hgwaVal>"
      << "</mo_heightGLIWeibA>"
      << "<mo_heightGLIWeibB>"
      << "<mo_hgwbVal species=\"Species_1\">0.415</mo_hgwbVal>"
      << "<mo_hgwbVal species=\"Species_2\">0.659</mo_hgwbVal>"
      << "<mo_hgwbVal species=\"Species_4\">1.449</mo_hgwbVal>"
      << "</mo_heightGLIWeibB>"
      << "<mo_heightGLIWeibC>"
      << "<mo_hgwcVal species=\"Species_1\">0</mo_hgwcVal>"
      << "<mo_hgwcVal species=\"Species_2\">1.136</mo_hgwcVal>"
      << "<mo_hgwcVal species=\"Species_4\">2.99781E-06</mo_hgwcVal>"
      << "</mo_heightGLIWeibC>"
      << "<mo_heightGLIWeibD>"
      << "<mo_hgwdVal species=\"Species_1\">3.838</mo_hgwdVal>"
      << "<mo_hgwdVal species=\"Species_2\">0</mo_hgwdVal>"
      << "<mo_hgwdVal species=\"Species_4\">1</mo_hgwdVal>"
      << "</mo_heightGLIWeibD>"
      << "<mo_heightGLIWeibMaxMort>"
      << "<mo_hgwmmVal species=\"Species_1\">1.893</mo_hgwmmVal>"
      << "<mo_hgwmmVal species=\"Species_2\">0.999</mo_hgwmmVal>"
      << "<mo_hgwmmVal species=\"Species_4\">0.331</mo_hgwmmVal>"
      << "</mo_heightGLIWeibMaxMort>"
      << "</HeightGLIWeibullMortality2>";

  oOut << "</paramFile>";

  oOut.close();

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteHeightGLIWeibullMortalityXMLErrorFile2()
////////////////////////////////////////////////////////////////////////////
const char* WriteHeightGLIWeibullMortalityXMLErrorFile2() {
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

  WriteHeightGLIWeibullMortalityCommonStuff(oOut);

  oOut << "<behaviorList>"
      << "<behavior>"
      << "<behaviorName>HeightGLIWeibullMortality</behaviorName>"
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

  oOut << "<HeightGLIWeibullMortality1>"
      << "<mo_heightGLIWeibA>"
      << "<mo_hgwaVal species=\"Species_1\">2.1</mo_hgwaVal>"
      << "<mo_hgwaVal species=\"Species_2\">4.37</mo_hgwaVal>"
      << "<mo_hgwaVal species=\"Species_4\">3.564</mo_hgwaVal>"
      << "</mo_heightGLIWeibA>"
      << "<mo_heightGLIWeibB>"
      << "<mo_hgwbVal species=\"Species_1\">0.415</mo_hgwbVal>"
      << "<mo_hgwbVal species=\"Species_2\">0.659</mo_hgwbVal>"
      << "<mo_hgwbVal species=\"Species_4\">1.449</mo_hgwbVal>"
      << "</mo_heightGLIWeibB>"
      << "<mo_heightGLIWeibC>"
      << "<mo_hgwcVal species=\"Species_1\">0</mo_hgwcVal>"
      << "<mo_hgwcVal species=\"Species_2\">1.136</mo_hgwcVal>"
      << "<mo_hgwcVal species=\"Species_4\">2.99781E-06</mo_hgwcVal>"
      << "</mo_heightGLIWeibC>"
      << "<mo_heightGLIWeibD>"
      << "<mo_hgwdVal species=\"Species_1\">3.838</mo_hgwdVal>"
      << "<mo_hgwdVal species=\"Species_2\">0</mo_hgwdVal>"
      << "<mo_hgwdVal species=\"Species_4\">1</mo_hgwdVal>"
      << "</mo_heightGLIWeibD>"
      << "<mo_heightGLIWeibMaxMort>"
      << "<mo_hgwmmVal species=\"Species_1\">0.893</mo_hgwmmVal>"
      << "<mo_hgwmmVal species=\"Species_2\">0.999</mo_hgwmmVal>"
      << "<mo_hgwmmVal species=\"Species_4\">0.331</mo_hgwmmVal>"
      << "</mo_heightGLIWeibMaxMort>"
      << "<mo_heightGLIWeibBrowsedA>"
      << "<mo_hgwbaVal species=\"Species_1\">0.3</mo_hgwbaVal>"
      << "<mo_hgwbaVal species=\"Species_2\">0.7</mo_hgwbaVal>"
      << "<mo_hgwbaVal species=\"Species_4\">0.5</mo_hgwbaVal>"
      << "</mo_heightGLIWeibBrowsedA>"
      << "<mo_heightGLIWeibBrowsedB>"
      << "<mo_hgwbbVal species=\"Species_1\">2</mo_hgwbbVal>"
      << "<mo_hgwbbVal species=\"Species_2\">0.5</mo_hgwbbVal>"
      << "<mo_hgwbbVal species=\"Species_4\">0.7</mo_hgwbbVal>"
      << "</mo_heightGLIWeibBrowsedB>"
      << "<mo_heightGLIWeibBrowsedC>"
      << "<mo_hgwbcVal species=\"Species_1\">0.004</mo_hgwbcVal>"
      << "<mo_hgwbcVal species=\"Species_2\">1</mo_hgwbcVal>"
      << "<mo_hgwbcVal species=\"Species_4\">0.0035</mo_hgwbcVal>"
      << "</mo_heightGLIWeibBrowsedC>"
      << "<mo_heightGLIWeibBrowsedD>"
      << "<mo_hgwbdVal species=\"Species_1\">2</mo_hgwbdVal>"
      << "<mo_hgwbdVal species=\"Species_2\">0.004</mo_hgwbdVal>"
      << "<mo_hgwbdVal species=\"Species_4\">1</mo_hgwbdVal>"
      << "</mo_heightGLIWeibBrowsedD>"
      << "<mo_heightGLIWeibBrowsedMaxMort>"
      << "<mo_hgwbmmVal species=\"Species_1\">0.788</mo_hgwbmmVal>"
      << "<mo_hgwbmmVal species=\"Species_2\">1</mo_hgwbmmVal>"
      << "<mo_hgwbmmVal species=\"Species_4\">0.977</mo_hgwbmmVal>"
      << "</mo_heightGLIWeibBrowsedMaxMort>"
      << "</HeightGLIWeibullMortality1>";

  oOut << "</paramFile>";

  oOut.close();

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteHeightGLIWeibullMortalityXMLErrorFile3()
////////////////////////////////////////////////////////////////////////////
const char* WriteHeightGLIWeibullMortalityXMLErrorFile3() {
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

  WriteHeightGLIWeibullMortalityCommonStuff(oOut);

  oOut << "<behaviorList>"
      << "<behavior>"
      << "<behaviorName>RandomBrowse</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>1</listPosition>"
      << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_1\" type=\"Seedling\"/>"
      << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_2\" type=\"Seedling\"/>"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>BasalAreaLight</behaviorName>"
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
      << "<behaviorName>HeightGLIWeibullMortality</behaviorName>"
      << "<version>2</version>"
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
      << "<behaviorName>RemoveDead</behaviorName>"
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
      << "<RandomBrowse1>"
      << "<di_randBrowsePDF>0</di_randBrowsePDF>"
      << "<di_randBrowseProb>"
      << "<di_rbpVal species=\"Species_1\">0.33</di_rbpVal>"
      << "<di_rbpVal species=\"Species_2\">1</di_rbpVal>"
      << "</di_randBrowseProb>"
      << "</RandomBrowse1>"
      << "<BasalAreaLight2>"
      << "<li_baLightSearchRadius>15</li_baLightSearchRadius>"
      << "<li_baLightA>12.4</li_baLightA>"
      << "<li_baConiferLightB>1.8</li_baConiferLightB>"
      << "<li_baConiferLightC>2.1</li_baConiferLightC>"
      << "<li_baAngiospermLightB>3.83</li_baAngiospermLightB>"
      << "<li_baAngiospermLightC>3.04</li_baAngiospermLightC>"
      << "<li_baLightSigma>0.82</li_baLightSigma>"
      << "<li_baLightChangeThreshold>0.05</li_baLightChangeThreshold>"
      << "<li_baLightMinDBH>10</li_baLightMinDBH>"
      << "<li_baTreeType>"
      << "<li_bttVal species=\"Species_1\">1</li_bttVal>"
      << "<li_bttVal species=\"Species_2\">0</li_bttVal>"
      << "<li_bttVal species=\"Species_3\">1</li_bttVal>"
      << "<li_bttVal species=\"Species_4\">0</li_bttVal>"
      << "</li_baTreeType>"
      << "</BasalAreaLight2>"
      << "<HeightGLIWeibullMortality3>"
      << "<mo_heightGLIWeibA>"
      << "<mo_hgwaVal species=\"Species_1\">2.1</mo_hgwaVal>"
      << "<mo_hgwaVal species=\"Species_2\">4.37</mo_hgwaVal>"
      << "<mo_hgwaVal species=\"Species_4\">3.564</mo_hgwaVal>"
      << "</mo_heightGLIWeibA>"
      << "<mo_heightGLIWeibB>"
      << "<mo_hgwbVal species=\"Species_1\">0.415</mo_hgwbVal>"
      << "<mo_hgwbVal species=\"Species_2\">0.659</mo_hgwbVal>"
      << "<mo_hgwbVal species=\"Species_4\">1.449</mo_hgwbVal>"
      << "</mo_heightGLIWeibB>"
      << "<mo_heightGLIWeibC>"
      << "<mo_hgwcVal species=\"Species_1\">0</mo_hgwcVal>"
      << "<mo_hgwcVal species=\"Species_2\">1.136</mo_hgwcVal>"
      << "<mo_hgwcVal species=\"Species_4\">2.99781E-06</mo_hgwcVal>"
      << "</mo_heightGLIWeibC>"
      << "<mo_heightGLIWeibD>"
      << "<mo_hgwdVal species=\"Species_1\">3.838</mo_hgwdVal>"
      << "<mo_hgwdVal species=\"Species_2\">0</mo_hgwdVal>"
      << "<mo_hgwdVal species=\"Species_4\">1</mo_hgwdVal>"
      << "</mo_heightGLIWeibD>"
      << "<mo_heightGLIWeibMaxMort>"
      << "<mo_hgwmmVal species=\"Species_1\">0.893</mo_hgwmmVal>"
      << "<mo_hgwmmVal species=\"Species_2\">0.999</mo_hgwmmVal>"
      << "<mo_hgwmmVal species=\"Species_4\">0.331</mo_hgwmmVal>"
      << "</mo_heightGLIWeibMaxMort>"
      << "<mo_heightGLIWeibBrowsedA>"
      << "<mo_hgwbaVal species=\"Species_1\">0.3</mo_hgwbaVal>"
      << "<mo_hgwbaVal species=\"Species_2\">0.7</mo_hgwbaVal>"
      << "<mo_hgwbaVal species=\"Species_4\">0.5</mo_hgwbaVal>"
      << "</mo_heightGLIWeibBrowsedA>"
      << "<mo_heightGLIWeibBrowsedB>"
      << "<mo_hgwbbVal species=\"Species_1\">2</mo_hgwbbVal>"
      << "<mo_hgwbbVal species=\"Species_2\">0.5</mo_hgwbbVal>"
      << "<mo_hgwbbVal species=\"Species_4\">0.7</mo_hgwbbVal>"
      << "</mo_heightGLIWeibBrowsedB>"
      << "<mo_heightGLIWeibBrowsedC>"
      << "<mo_hgwbcVal species=\"Species_1\">0.004</mo_hgwbcVal>"
      << "<mo_hgwbcVal species=\"Species_2\">1</mo_hgwbcVal>"
      << "<mo_hgwbcVal species=\"Species_4\">0.0035</mo_hgwbcVal>"
      << "</mo_heightGLIWeibBrowsedC>"
      << "<mo_heightGLIWeibBrowsedD>"
      << "<mo_hgwbdVal species=\"Species_1\">2</mo_hgwbdVal>"
      << "<mo_hgwbdVal species=\"Species_2\">0.004</mo_hgwbdVal>"
      << "<mo_hgwbdVal species=\"Species_4\">1</mo_hgwbdVal>"
      << "</mo_heightGLIWeibBrowsedD>"
      << "<mo_heightGLIWeibBrowsedMaxMort>"
      << "<mo_hgwbmmVal species=\"Species_1\">4.788</mo_hgwbmmVal>"
      << "<mo_hgwbmmVal species=\"Species_2\">1</mo_hgwbmmVal>"
      << "<mo_hgwbmmVal species=\"Species_4\">0.977</mo_hgwbmmVal>"
      << "</mo_heightGLIWeibBrowsedMaxMort>"
      << "</HeightGLIWeibullMortality3>";

  oOut << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteHeightGLIWeibullMortalityCommonStuff()
/////////////////////////////////////////////////////////////////////////////
void WriteHeightGLIWeibullMortalityCommonStuff(std::fstream &oOut)
{
  using namespace std;
  oOut << "<randomSeed>1</randomSeed>"
      << "<plot_lenX>104</plot_lenX>"
      << "<plot_lenY>104</plot_lenY>"
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
