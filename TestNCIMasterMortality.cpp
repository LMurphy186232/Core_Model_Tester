//---------------------------------------------------------------------------
// TestNCIMort.cpp
//---------------------------------------------------------------------------
#include "TestNCIMasterMortality.h"
#include <gtest/gtest.h>
#include <fstream>
#include <math.h>
#include "TreePopulation.h"
#include "SimManager.h"
#include "BehaviorBase.h"
#include <iostream>
#include "NCIEffectsList.h"

////////////////////////////////////////////////////////////////////////////
// TestRun1()
// Performs a test run of NCI mortality - a Puerto-Rico-like situation. This
// run has no shading effect and uses damage effect.
// WriteNCIMortXMLFile1() performs setup for a 1-year timestep; then
// WriteNCIMortXMLFile2() performs setup for an otherwise identical 3-year
// timestep.
//
// There are 8 target trees, for which 1000 copies of each will be created.
// Then the remainder left after a timestep will be checked against the
// testing spreadsheet expected results.
////////////////////////////////////////////////////////////////////////////
TEST(NCIMasterMortality, TestRun1) {

  int *p_iCount; //for counting target trees
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    clTreePopulation * p_oPop;
    clTreeSearch *p_oAllTrees;
    clTree *p_oTree;
    float fDiam, fX, fY,
    fTarget1X = 10, fTarget1Y = 10, //coords of target 1 trees
    fTarget2X = 20, fTarget2Y = 20, //coords of target 2 trees
    fTarget3X = 30, fTarget3Y = 30, //coords of target 3 trees
    fTarget4X = 50, fTarget4Y = 50, //coords of target 4 trees
    fTarget5X = 53, fTarget5Y = 52, //coords of target 5 trees
    fTarget6X = 59, fTarget6Y = 50, //coords of target 6 trees
    fTarget7X = 50, fTarget7Y = 59, //coords of target 7 trees
    fTarget8X = 55, fTarget8Y = 55; //coords of target 8 trees
    int iSpecies, iDamage, i, iNumTargets = 8;
    p_iCount = new int[iNumTargets];

    //***********************************
    // Run 1 - 1 year timestep
    //***********************************
    //Load our test file and get our tree population pointers
    p_oSimManager->ReadFile( WriteNCIMortXMLFile1() );
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );

    //Create our trees and set the damage level for each
    fDiam = 11; iSpecies = 0; iDamage = 0;
    for (i = 0; i < 1000; i++) {
      p_oTree = p_oPop->CreateTree(fTarget1X, fTarget1Y, iSpecies, clTreePopulation::adult, fDiam);
      p_oTree->SetValue(p_oPop->GetIntDataCode("stm_dmg",
          p_oTree->GetSpecies(),
          p_oTree->GetType()),
          iDamage);
    }

    fDiam = 8;  iSpecies = 1;  iDamage = 1000;
    for (i = 0; i < 1000; i++) {
      p_oTree = p_oPop->CreateTree(fTarget2X, fTarget2Y, iSpecies, clTreePopulation::sapling, fDiam);
      p_oTree->SetValue(p_oPop->GetIntDataCode("stm_dmg",
          p_oTree->GetSpecies(),
          p_oTree->GetType()),
          iDamage);
    }

    fDiam = 15;  iSpecies = 3;  iDamage = 2000;
    for (i = 0; i < 1000; i++) {
      p_oTree = p_oPop->CreateTree(fTarget3X, fTarget3Y, iSpecies, clTreePopulation::adult, fDiam);
      p_oTree->SetValue(p_oPop->GetIntDataCode("stm_dmg",
          p_oTree->GetSpecies(),
          p_oTree->GetType()),
          iDamage);
    }

    fDiam = 10.5;  iSpecies = 0;  iDamage = 0;
    for (i = 0; i < 1000; i++) {
      p_oTree = p_oPop->CreateTree(fTarget4X, fTarget4Y, iSpecies, clTreePopulation::adult, fDiam);
      p_oTree->SetValue(p_oPop->GetIntDataCode("stm_dmg",
          p_oTree->GetSpecies(),
          p_oTree->GetType()),
          iDamage);
    }

    fDiam = 15;  iSpecies = 1;  iDamage = 1000;
    for (i = 0; i < 1000; i++) {
      p_oTree = p_oPop->CreateTree(fTarget5X, fTarget5Y, iSpecies, clTreePopulation::adult, fDiam);
      p_oTree->SetValue(p_oPop->GetIntDataCode("stm_dmg",
          p_oTree->GetSpecies(),
          p_oTree->GetType()),
          iDamage);
    }

    fDiam = 25;  iSpecies = 3;  iDamage = 2000;
    for (i = 0; i < 1000; i++) {
      p_oTree = p_oPop->CreateTree(fTarget6X, fTarget6Y, iSpecies, clTreePopulation::adult, fDiam);
      p_oTree->SetValue(p_oPop->GetIntDataCode("stm_dmg",
          p_oTree->GetSpecies(),
          p_oTree->GetType()),
          iDamage);
    }

    fDiam = 30;  iSpecies = 0;  iDamage = 2000;
    for (i = 0; i < 1000; i++) {
      p_oTree = p_oPop->CreateTree(fTarget7X, fTarget7Y, iSpecies, clTreePopulation::adult, fDiam);
      p_oTree->SetValue(p_oPop->GetIntDataCode("stm_dmg",
          p_oTree->GetSpecies(),
          p_oTree->GetType()),
          iDamage);
    }

    fDiam = 45;  iSpecies = 1;  iDamage = 0;
    for (i = 0; i < 1000; i++) {
      p_oTree = p_oPop->CreateTree(fTarget8X, fTarget8Y, iSpecies, clTreePopulation::adult, fDiam);
      p_oTree->SetValue(p_oPop->GetIntDataCode("stm_dmg",
          p_oTree->GetSpecies(),
          p_oTree->GetType()),
          iDamage);
    }

    //These trees won't compete
    p_oPop->CreateTree(56, 56, 0, clTreePopulation::snag, 30);
    p_oPop->CreateTree(56, 56, 0, clTreePopulation::seedling, 0.2);

    //Now do the run
    p_oSimManager->RunSim(1);

    //Count the target trees that are left
    for (i = 0; i < iNumTargets; i++) {
      p_iCount[i] = 0;
    }

    p_oAllTrees = p_oPop->Find("all");

    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {

      //Get the X and Y
      p_oTree->GetValue(p_oPop->GetXCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fX);
      p_oTree->GetValue(p_oPop->GetYCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fY);

      //Find out if it's a target tree
      if (fabs(fX - fTarget1X) < 0.001 && fabs(fY - fTarget1Y) < 0.001) {
        p_iCount[0]++;
      } else if (fabs(fX - fTarget2X) < 0.001 && fabs(fY - fTarget2Y) < 0.001) {
        p_iCount[1]++;
      } else if (fabs(fX - fTarget3X) < 0.001 && fabs(fY - fTarget3Y) < 0.001) {
        p_iCount[2]++;
      } else if (fabs(fX - fTarget4X) < 0.001 && fabs(fY - fTarget4Y) < 0.001) {
        p_iCount[3]++;
      } else if (fabs(fX - fTarget5X) < 0.001 && fabs(fY - fTarget5Y) < 0.001) {
        p_iCount[4]++;
      } else if (fabs(fX - fTarget6X) < 0.001 && fabs(fY - fTarget6Y) < 0.001) {
        p_iCount[5]++;
      } else if (fabs(fX - fTarget7X) < 0.001 && fabs(fY - fTarget7Y) < 0.001) {
        p_iCount[6]++;
      } else if (fabs(fX - fTarget8X) < 0.001 && fabs(fY - fTarget8Y) < 0.001) {
        p_iCount[7]++;
      }

      p_oTree = p_oAllTrees->NextTree();
    }

    //Check our counts
    //Make sure there are no divide by zero errors
    for (i = 0; i < iNumTargets; i++) {
      EXPECT_GT(p_iCount[i], 0);
    }
    EXPECT_LT(fabs(p_iCount[0] - 955.0435325)/p_iCount[0], 0.1);
    EXPECT_LT(fabs(p_iCount[1] - 457.1481071)/p_iCount[1], 0.1);
    EXPECT_LT(fabs(p_iCount[2] - 609.8269821)/p_iCount[2], 0.1);
    EXPECT_LT(fabs(p_iCount[3] - 405.6166509)/p_iCount[3], 0.1);
    EXPECT_LT(fabs(p_iCount[4] - 320.1246725)/p_iCount[4], 0.1);
    EXPECT_LT(fabs(p_iCount[5] - 543.6505973)/p_iCount[5], 0.1);
    EXPECT_LT(fabs(p_iCount[6] - 107.8864714)/p_iCount[6], 0.2);
    EXPECT_LT(fabs(p_iCount[7] - 356.5684946)/p_iCount[7], 0.1);

    //***********************************
    // Run 2 - 3 year timestep
    //***********************************
    //Load our test file and get our tree population pointers
    p_oSimManager->ReadFile( WriteNCIMortXMLFile2() );
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );

    //Create our trees and set the damage level for each
    fDiam = 11; iSpecies = 0; iDamage = 0;
    for (i = 0; i < 1000; i++) {
      p_oTree = p_oPop->CreateTree(fTarget1X, fTarget1Y, iSpecies, clTreePopulation::adult, fDiam);
      p_oTree->SetValue(p_oPop->GetIntDataCode("stm_dmg",
          p_oTree->GetSpecies(),
          p_oTree->GetType()),
          iDamage);
    }

    fDiam = 8;  iSpecies = 1;  iDamage = 1000;
    for (i = 0; i < 1000; i++) {
      p_oTree = p_oPop->CreateTree(fTarget2X, fTarget2Y, iSpecies, clTreePopulation::sapling, fDiam);
      p_oTree->SetValue(p_oPop->GetIntDataCode("stm_dmg",
          p_oTree->GetSpecies(),
          p_oTree->GetType()),
          iDamage);
    }

    fDiam = 15;  iSpecies = 3;  iDamage = 2000;
    for (i = 0; i < 1000; i++) {
      p_oTree = p_oPop->CreateTree(fTarget3X, fTarget3Y, iSpecies, clTreePopulation::adult, fDiam);
      p_oTree->SetValue(p_oPop->GetIntDataCode("stm_dmg",
          p_oTree->GetSpecies(),
          p_oTree->GetType()),
          iDamage);
    }

    fDiam = 10.5;  iSpecies = 0;  iDamage = 0;
    for (i = 0; i < 1000; i++) {
      p_oTree = p_oPop->CreateTree(fTarget4X, fTarget4Y, iSpecies, clTreePopulation::adult, fDiam);
      p_oTree->SetValue(p_oPop->GetIntDataCode("stm_dmg",
          p_oTree->GetSpecies(),
          p_oTree->GetType()),
          iDamage);
    }

    fDiam = 15;  iSpecies = 1;  iDamage = 1000;
    for (i = 0; i < 1000; i++) {
      p_oTree = p_oPop->CreateTree(fTarget5X, fTarget5Y, iSpecies, clTreePopulation::adult, fDiam);
      p_oTree->SetValue(p_oPop->GetIntDataCode("stm_dmg",
          p_oTree->GetSpecies(),
          p_oTree->GetType()),
          iDamage);
    }

    fDiam = 25;  iSpecies = 3;  iDamage = 2000;
    for (i = 0; i < 1000; i++) {
      p_oTree = p_oPop->CreateTree(fTarget6X, fTarget6Y, iSpecies, clTreePopulation::adult, fDiam);
      p_oTree->SetValue(p_oPop->GetIntDataCode("stm_dmg",
          p_oTree->GetSpecies(),
          p_oTree->GetType()),
          iDamage);
    }

    fDiam = 30;  iSpecies = 0;  iDamage = 2000;
    for (i = 0; i < 1000; i++) {
      p_oTree = p_oPop->CreateTree(fTarget7X, fTarget7Y, iSpecies, clTreePopulation::adult, fDiam);
      p_oTree->SetValue(p_oPop->GetIntDataCode("stm_dmg",
          p_oTree->GetSpecies(),
          p_oTree->GetType()),
          iDamage);
    }

    fDiam = 45;  iSpecies = 1;  iDamage = 0;
    for (i = 0; i < 1000; i++) {
      p_oTree = p_oPop->CreateTree(fTarget8X, fTarget8Y, iSpecies, clTreePopulation::adult, fDiam);
      p_oTree->SetValue(p_oPop->GetIntDataCode("stm_dmg",
          p_oTree->GetSpecies(),
          p_oTree->GetType()),
          iDamage);
    }

    p_oPop->CreateTree(56, 56, 0, clTreePopulation::seedling, 0.2);

    //Now do the run
    p_oSimManager->RunSim(1);

    //Count the target trees that are left
    for (i = 0; i < iNumTargets; i++) {
      p_iCount[i] = 0;
    }

    p_oAllTrees = p_oPop->Find("all");

    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {

      //Get the X and Y
      p_oTree->GetValue(p_oPop->GetXCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fX);
      p_oTree->GetValue(p_oPop->GetYCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fY);

      //Find out if it's a target tree
      if (fabs(fX - fTarget1X) < 0.001 && fabs(fY - fTarget1Y) < 0.001) {
        p_iCount[0]++;
      } else if (fabs(fX - fTarget2X) < 0.001 && fabs(fY - fTarget2Y) < 0.001) {
        p_iCount[1]++;
      } else if (fabs(fX - fTarget3X) < 0.001 && fabs(fY - fTarget3Y) < 0.001) {
        p_iCount[2]++;
      } else if (fabs(fX - fTarget4X) < 0.001 && fabs(fY - fTarget4Y) < 0.001) {
        p_iCount[3]++;
      } else if (fabs(fX - fTarget5X) < 0.001 && fabs(fY - fTarget5Y) < 0.001) {
        p_iCount[4]++;
      } else if (fabs(fX - fTarget6X) < 0.001 && fabs(fY - fTarget6Y) < 0.001) {
        p_iCount[5]++;
      } else if (fabs(fX - fTarget7X) < 0.001 && fabs(fY - fTarget7Y) < 0.001) {
        p_iCount[6]++;
      } else if (fabs(fX - fTarget8X) < 0.001 && fabs(fY - fTarget8Y) < 0.001) {
        p_iCount[7]++;
      }

      p_oTree = p_oAllTrees->NextTree();
    }

    //Check our counts
    //Make sure there are no divide by zero errors
    for (i = 0; i < iNumTargets; i++) {
      if (i != 6) {  //this one could indeed be 0
        EXPECT_GT(p_iCount[i], 0);
      }
    }
    EXPECT_LT(fabs(p_iCount[0] - 871.1029885)/p_iCount[0], 0.1);
    EXPECT_LT(fabs(p_iCount[1] - 95.53681915)/p_iCount[1], 0.25);
    EXPECT_LT(fabs(p_iCount[2] - 226.7879149)/p_iCount[2], 0.15);
    EXPECT_LT(fabs(p_iCount[3] - 66.73402572)/p_iCount[3], 0.3);
    EXPECT_LT(fabs(p_iCount[4] - 32.80631433)/p_iCount[4], 0.3);
    EXPECT_LT(fabs(p_iCount[5] - 160.6791807)/p_iCount[5], 0.5);
    EXPECT_LT(p_iCount[6], 10);
    //EXPECT_LT(fabs(p_iCount[7] - 45.33450756)/p_iCount[7], 0.3);
    EXPECT_LT(p_iCount[7] > 30 && p_iCount[7], 60);

    delete[] p_iCount;
    delete p_oSimManager;
  } catch (modelErr &e) {
    delete[] p_iCount;
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

////////////////////////////////////////////////////////////////////////////
// TestRun2()
// Tests the mortality calculations at two timestep lengths in a BC-like
// situation. It uses no storm damage and simplified crowding -
// no size sensitivity to NCI (g = 0, d = 1). It does use Shading.
// WriteNCIMortXMLFile3() is used to do setup in the first case, for a 1 year
// timestep. Mortality is checked for two target trees. Then WriteNCIMortXMLFile4()
// does setup for a 3 year timestep.
//
// The first target tree is too far away from the other trees to be affected.
// It has the lowest possible value of shade and a zero NCI. The second
// target tree is surrounded by 4 trees affecting shade and NCI and two which
// do not. 1000 copies of each are created. Then the remainder left after a
// timestep will be checked against the testing spreadsheet expected results.
////////////////////////////////////////////////////////////////////////////
TEST(NCIMasterMortality, TestRun2) {

  int *p_iCount; //for counting target trees
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    clTreePopulation * p_oPop;
    clTreeSearch *p_oAllTrees;
    clTree *p_oTree;
    float fDiam, fX, fY,
    fTarget1X = 10, fTarget1Y = 10, //coords of target 1 trees
    fTarget2X = 50, fTarget2Y = 50; //coords of target 2 trees;
    int iSpecies, iNumTargets = 2, i;
    p_iCount = new int[iNumTargets];

    //***********************************
    // Run 1 - 1 year timestep
    //***********************************
    //Load our test file and get our tree population pointers
    p_oSimManager->ReadFile( WriteNCIMortXMLFile3() );
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );

    //Create our two target trees
    fDiam = 11; iSpecies = 0;
    for (i = 0; i < 1000; i++) {
      p_oTree = p_oPop->CreateTree(fTarget1X, fTarget1Y, iSpecies, clTreePopulation::adult, fDiam);
    }

    fDiam = 10.5; iSpecies = 0;
    for (i = 0; i < 1000; i++) {
      p_oPop->CreateTree(fTarget2X, fTarget2Y, iSpecies, clTreePopulation::adult, fDiam);
    }

    //Now create all the neighbors
    p_oPop->CreateTree(53, 52, 1, clTreePopulation::adult, 15);
    p_oPop->CreateTree(59, 50, 2, clTreePopulation::adult, 25);
    p_oPop->CreateTree(50, 59, 0, clTreePopulation::adult, 30);
    p_oPop->CreateTree(55, 55, 1, clTreePopulation::adult, 45);
    p_oPop->CreateTree(60, 61, 2, clTreePopulation::adult, 15);
    p_oPop->CreateTree(56, 56, 0, clTreePopulation::seedling, 0.2);

    //Now do the run
    p_oSimManager->RunSim(1);

    //Count the target trees that are left
    for (i = 0; i < iNumTargets; i++) {
      p_iCount[i] = 0;
    }

    p_oAllTrees = p_oPop->Find("all");

    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {

      //Get the X and Y
      p_oTree->GetValue(p_oPop->GetXCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fX);
      p_oTree->GetValue(p_oPop->GetYCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fY);

      //Find out if it's a target tree
      if (fabs(fX - fTarget1X) < 0.001 && fabs(fY - fTarget1Y) < 0.001) {
        p_iCount[0]++;
      } else if (fabs(fX - fTarget2X) < 0.001 && fabs(fY - fTarget2Y) < 0.001) {
        p_iCount[1]++;
      }

      p_oTree = p_oAllTrees->NextTree();
    }

    //Check our counts
    //Make sure there are no divide by zero errors
    for (i = 0; i < iNumTargets; i++) {
      EXPECT_GT(p_iCount[i], 0);
    }
    EXPECT_LT(fabs(p_iCount[0] - 875.3906276)/p_iCount[0], 0.1);
    EXPECT_LT(fabs(p_iCount[1] - 837.7646025)/p_iCount[1], 0.1);

    //***********************************
    // Run 2 - 3 year timestep
    //***********************************
    //Load our test file and get our tree population pointers
    p_oSimManager->ReadFile( WriteNCIMortXMLFile4() );
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );

    //Create our two target trees
    fDiam = 11; iSpecies = 0;
    for (i = 0; i < 1000; i++) {
      p_oTree = p_oPop->CreateTree(fTarget1X, fTarget1Y, iSpecies, clTreePopulation::adult, fDiam);
    }

    fDiam = 10.5; iSpecies = 0;
    for (i = 0; i < 1000; i++) {
      p_oPop->CreateTree(fTarget2X, fTarget2Y, iSpecies, clTreePopulation::adult, fDiam);
    }

    //Now create all the neighbors
    p_oPop->CreateTree(53, 52, 1, clTreePopulation::adult, 15);
    p_oPop->CreateTree(59, 50, 2, clTreePopulation::adult, 25);
    p_oPop->CreateTree(50, 59, 0, clTreePopulation::adult, 30);
    p_oPop->CreateTree(55, 55, 1, clTreePopulation::adult, 45);
    p_oPop->CreateTree(60, 61, 2, clTreePopulation::adult, 15);
    p_oPop->CreateTree(56, 56, 0, clTreePopulation::seedling, 0.2);

    //Now do the run
    p_oSimManager->RunSim(1);

    //Count the target trees that are left
    for (i = 0; i < iNumTargets; i++) {
      p_iCount[i] = 0;
    }

    p_oAllTrees = p_oPop->Find("all");

    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {

      //Get the X and Y
      p_oTree->GetValue(p_oPop->GetXCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fX);
      p_oTree->GetValue(p_oPop->GetYCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fY);

      //Find out if it's a target tree
      if (fabs(fX - fTarget1X) < 0.001 && fabs(fY - fTarget1Y) < 0.001) {
        p_iCount[0]++;
      } else if (fabs(fX - fTarget2X) < 0.001 && fabs(fY - fTarget2Y) < 0.001) {
        p_iCount[1]++;
      }

      p_oTree = p_oAllTrees->NextTree();
    }

    //Check our counts
    //Make sure there are no divide by zero errors
    for (i = 0; i < iNumTargets; i++) {
      EXPECT_GT(p_iCount[i], 0);
    }
    EXPECT_LT(fabs(p_iCount[0] - 670.8194984)/p_iCount[0], 0.1);
    EXPECT_LT(fabs(p_iCount[1] - 587.9846918)/p_iCount[1], 0.1);

    delete[] p_iCount;
    delete p_oSimManager;
  } catch (modelErr &e) {
    delete[] p_iCount;
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

////////////////////////////////////////////////////////////////////////////
// TestRun3()
// Performs Test Run 3. This run has no storm damage, has variability in
// functions between species, has neighbors below the minimum neighbor DBH,
// and doesn't use the DBH divisor.
//
// WriteNCIMortXMLFile5() is used to do setup for the first run, for a 1 year
// timestep. 1000 copies are created for each of 5 target trees and the
// number left checked after 1 timestep. Then WriteNCIMortXMLFile6()
// does setup for a 3 year timestep and the process is repeated.
////////////////////////////////////////////////////////////////////////////
TEST(NCIMasterMortality, TestRun3) {

  int *p_iCount; //for counting target trees
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    clTreePopulation * p_oPop;
    clTreeSearch *p_oAllTrees;
    clTree *p_oTree;
    float fDiam, fX, fY, fShade,
    fTarget1X = 53, fTarget1Y = 52, //coords of target 1 trees
    fTarget2X = 59, fTarget2Y = 50, //coords of target 2 trees
    fTarget3X = 50, fTarget3Y = 59, //coords of target 3 trees
    fTarget4X = 55, fTarget4Y = 55, //coords of target 4 trees
    fTarget5X = 50, fTarget5Y = 50; //coords of target 5 trees
    int iSpecies, i, iNumTargets = 5;
    p_iCount = new int[iNumTargets];

    //***********************************
    // Run 1 - 1 year timestep
    //***********************************

    //Load our test file and get our tree population pointers
    p_oSimManager->ReadFile( WriteNCIMortXMLFile5() );
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );

    //Create our trees and set their light levels
    fDiam = 15; iSpecies = 1; fShade = 1;
    for (i = 0; i < 1000; i++) {
      p_oTree = p_oPop->CreateTree(fTarget1X, fTarget1Y, iSpecies, clTreePopulation::adult, fDiam);
      p_oTree->SetValue(p_oPop->GetFloatDataCode("Light",
          p_oTree->GetSpecies(),
          p_oTree->GetType()),
          fShade);
    }

    fDiam = 25;  iSpecies = 3;  fShade = 0.2;
    for (i = 0; i < 1000; i++) {
      p_oTree = p_oPop->CreateTree(fTarget2X, fTarget2Y, iSpecies, clTreePopulation::adult, fDiam);
      p_oTree->SetValue(p_oPop->GetFloatDataCode("Light",
          p_oTree->GetSpecies(),
          p_oTree->GetType()),
          fShade);
    }

    fDiam = 30;  iSpecies = 0;  fShade = 0.4;
    for (i = 0; i < 1000; i++) {
      p_oTree = p_oPop->CreateTree(fTarget3X, fTarget3Y, iSpecies, clTreePopulation::adult, fDiam);
      p_oTree->SetValue(p_oPop->GetFloatDataCode("Light",
          p_oTree->GetSpecies(),
          p_oTree->GetType()),
          fShade);
    }

    fDiam = 45;  iSpecies = 1;  fShade = 0.8;
    for (i = 0; i < 1000; i++) {
      p_oTree = p_oPop->CreateTree(fTarget4X, fTarget4Y, iSpecies, clTreePopulation::adult, fDiam);
      p_oTree->SetValue(p_oPop->GetFloatDataCode("Light",
          p_oTree->GetSpecies(),
          p_oTree->GetType()),
          fShade);
    }

    fDiam = 10.5;  iSpecies = 0;  fShade = 0;
    for (i = 0; i < 1000; i++) {
      p_oTree = p_oPop->CreateTree(fTarget5X, fTarget5Y, iSpecies, clTreePopulation::adult, fDiam);
      p_oTree->SetValue(p_oPop->GetFloatDataCode("Light",
          p_oTree->GetSpecies(),
          p_oTree->GetType()),
          fShade);
    }

    //Now create all the neighbors that are too small to compete
    p_oPop->CreateTree(52, 52, 0, clTreePopulation::sapling, 9);
    p_oPop->CreateTree(53, 53, 1, clTreePopulation::adult, 11);
    p_oPop->CreateTree(54, 54, 3, clTreePopulation::adult, 13);
    p_oPop->CreateTree(56, 56, 2, clTreePopulation::adult, 15);


    //Now do the run - but don't let SailLight go, or it will mess up the
    //shading values we've assigned
    for (int i = 1; i < p_oSimManager->GetNumberOfBehaviors(); i++) {
      p_oSimManager->GetBehaviorObject(i)->Action();
    }

    //Count the target trees that are left
    for (i = 0; i < iNumTargets; i++) {
      p_iCount[i] = 0;
    }

    p_oAllTrees = p_oPop->Find("all");

    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {

      //Get the X and Y
      p_oTree->GetValue(p_oPop->GetXCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fX);
      p_oTree->GetValue(p_oPop->GetYCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fY);

      //Find out if it's a target tree
      if (fabs(fX - fTarget1X) < 0.001 && fabs(fY - fTarget1Y) < 0.001) {
        p_iCount[0]++;
      } else if (fabs(fX - fTarget2X) < 0.001 && fabs(fY - fTarget2Y) < 0.001) {
        p_iCount[1]++;
      } else if (fabs(fX - fTarget3X) < 0.001 && fabs(fY - fTarget3Y) < 0.001) {
        p_iCount[2]++;
      } else if (fabs(fX - fTarget4X) < 0.001 && fabs(fY - fTarget4Y) < 0.001) {
        p_iCount[3]++;
      } else if (fabs(fX - fTarget5X) < 0.001 && fabs(fY - fTarget5Y) < 0.001) {
        p_iCount[4]++;
      }

      p_oTree = p_oAllTrees->NextTree();
    }

    //Check our counts
    //Make sure there are no divide by zero errors
    for (i = 0; i < iNumTargets; i++) {
      EXPECT_GT(p_iCount[i], 0);
    }
    EXPECT_LT(fabs(p_iCount[0] - 329.7033838)/p_iCount[0], 0.1);
    EXPECT_LT(fabs(p_iCount[1] - 153.080115)/p_iCount[1], 0.1);
    EXPECT_LT(fabs(p_iCount[2] - 338.9982341)/p_iCount[2], 0.1);
    EXPECT_LT(fabs(p_iCount[3] - 501.471828)/p_iCount[3], 0.1);
    EXPECT_LT(fabs(p_iCount[4] - 357.131635)/p_iCount[4], 0.1);

    //***********************************
    // Run 2 - 3 year timestep
    //***********************************

    //Load our test file and get our tree population pointers
    p_oSimManager->ReadFile( WriteNCIMortXMLFile6() );
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );

    //Create our trees and set their light levels
    fDiam = 15; iSpecies = 1; fShade = 1;
    for (i = 0; i < 1000; i++) {
      p_oTree = p_oPop->CreateTree(fTarget1X, fTarget1Y, iSpecies, clTreePopulation::adult, fDiam);
      p_oTree->SetValue(p_oPop->GetFloatDataCode("Light",
          p_oTree->GetSpecies(),
          p_oTree->GetType()),
          fShade);
    }

    fDiam = 25;  iSpecies = 3;  fShade = 0.2;
    for (i = 0; i < 1000; i++) {
      p_oTree = p_oPop->CreateTree(fTarget2X, fTarget2Y, iSpecies, clTreePopulation::adult, fDiam);
      p_oTree->SetValue(p_oPop->GetFloatDataCode("Light",
          p_oTree->GetSpecies(),
          p_oTree->GetType()),
          fShade);
    }

    fDiam = 30;  iSpecies = 0;  fShade = 0.4;
    for (i = 0; i < 1000; i++) {
      p_oTree = p_oPop->CreateTree(fTarget3X, fTarget3Y, iSpecies, clTreePopulation::adult, fDiam);
      p_oTree->SetValue(p_oPop->GetFloatDataCode("Light",
          p_oTree->GetSpecies(),
          p_oTree->GetType()),
          fShade);
    }

    fDiam = 45;  iSpecies = 1;  fShade = 0.8;
    for (i = 0; i < 1000; i++) {
      p_oTree = p_oPop->CreateTree(fTarget4X, fTarget4Y, iSpecies, clTreePopulation::adult, fDiam);
      p_oTree->SetValue(p_oPop->GetFloatDataCode("Light",
          p_oTree->GetSpecies(),
          p_oTree->GetType()),
          fShade);
    }

    fDiam = 10.5;  iSpecies = 0;  fShade = 0;
    for (i = 0; i < 1000; i++) {
      p_oTree = p_oPop->CreateTree(fTarget5X, fTarget5Y, iSpecies, clTreePopulation::adult, fDiam);
      p_oTree->SetValue(p_oPop->GetFloatDataCode("Light",
          p_oTree->GetSpecies(),
          p_oTree->GetType()),
          fShade);
    }

    //Now create all the neighbors
    p_oPop->CreateTree(52, 52, 0, clTreePopulation::sapling, 9);
    p_oPop->CreateTree(53, 53, 1, clTreePopulation::adult, 11);
    p_oPop->CreateTree(54, 54, 3, clTreePopulation::adult, 13);
    p_oPop->CreateTree(56, 56, 2, clTreePopulation::adult, 15);


    //Now do the run - but don't let SailLight go, or it will mess up the
    //shading values we've assigned
    for (int i = 1; i < p_oSimManager->GetNumberOfBehaviors(); i++) {
      p_oSimManager->GetBehaviorObject(i)->Action();
    }

    //Count the target trees that are left
    for (i = 0; i < iNumTargets; i++) {
      p_iCount[i] = 0;
    }

    p_oAllTrees = p_oPop->Find("all");

    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {

      //Get the X and Y
      p_oTree->GetValue(p_oPop->GetXCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fX);
      p_oTree->GetValue(p_oPop->GetYCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fY);

      //Find out if it's a target tree
      if (fabs(fX - fTarget1X) < 0.001 && fabs(fY - fTarget1Y) < 0.001) {
        p_iCount[0]++;
      } else if (fabs(fX - fTarget2X) < 0.001 && fabs(fY - fTarget2Y) < 0.001) {
        p_iCount[1]++;
      } else if (fabs(fX - fTarget3X) < 0.001 && fabs(fY - fTarget3Y) < 0.001) {
        p_iCount[2]++;
      } else if (fabs(fX - fTarget4X) < 0.001 && fabs(fY - fTarget4Y) < 0.001) {
        p_iCount[3]++;
      } else if (fabs(fX - fTarget5X) < 0.001 && fabs(fY - fTarget5Y) < 0.001) {
        p_iCount[4]++;
      }

      p_oTree = p_oAllTrees->NextTree();
    }

    //Check our counts
    //Make sure there are no divide by zero errors
    for (i = 0; i < iNumTargets; i++) {
      if (i != 1) { //this one could indeed be 0
        EXPECT_GT(p_iCount[i], 0);
      }
    }
    //EXPECT_LT(fabs(p_iCount[0] - 35.84018256)/p_iCount[0], 0.3);
    EXPECT_LT(p_iCount[0] > 20 && p_iCount[0], 50);
    EXPECT_LT(p_iCount[1], 10);
    //EXPECT_LT(fabs(p_iCount[2] - 38.95761017)/p_iCount[2], 0.3);
    EXPECT_LT(p_iCount[2] > 20 && p_iCount[2], 50);
    EXPECT_LT(fabs(p_iCount[3] - 126.1071236)/p_iCount[3], 0.3);
    //EXPECT_LT(fabs(p_iCount[4] - 45.54964179)/p_iCount[4], 0.3);
    EXPECT_LT(p_iCount[4] > 30 && p_iCount[4], 60);

    delete[] p_iCount;
    delete p_oSimManager;
  } catch (modelErr &e) {
    delete[] p_iCount;
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

////////////////////////////////////////////////////////////////////////////
// TestRun4()
// Performs Test Run 4. This run tests variability in light behavior
// requirements, but is otherwise almost exactly like TestRun3.
//
// WriteNCIMortXMLFile7() is used to do setup for the first run, for a 1 year
// timestep. 1000 copies are created for each of 5 target trees and the
// number left checked after 1 timestep. Then WriteNCIMortXMLFile8() does setup for
// a 3 year timestep and the process is repeated.
////////////////////////////////////////////////////////////////////////////
TEST(NCIMasterMortality, TestRun4) {

  int *p_iCount; //for counting target trees
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    clTreePopulation * p_oPop;
    clTreeSearch *p_oAllTrees;
    clTree *p_oTree;
    float fDiam, fX, fY, fShade,
    fTarget1X = 53, fTarget1Y = 52, //coords of target 1 trees
    fTarget2X = 59, fTarget2Y = 50, //coords of target 2 trees
    fTarget3X = 50, fTarget3Y = 59, //coords of target 3 trees
    fTarget4X = 55, fTarget4Y = 55, //coords of target 4 trees
    fTarget5X = 50, fTarget5Y = 50; //coords of target 5 trees
    int iSpecies, i, iNumTargets = 5;
    p_iCount = new int[iNumTargets];

    //***********************************
    // Run 1 - 1 year timestep
    //***********************************

    //Load our test file and get our tree population pointers
    p_oSimManager->ReadFile( WriteNCIMortXMLFile7() );
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );

    //Create our trees and set their light levels
    fDiam = 15; iSpecies = 1;
    for (i = 0; i < 1000; i++) {
      p_oTree = p_oPop->CreateTree(fTarget1X, fTarget1Y, iSpecies, clTreePopulation::adult, fDiam);
    }

    fDiam = 25;  iSpecies = 3;  fShade = 0.2;
    for (i = 0; i < 1000; i++) {
      p_oTree = p_oPop->CreateTree(fTarget2X, fTarget2Y, iSpecies, clTreePopulation::adult, fDiam);
      p_oTree->SetValue(p_oPop->GetFloatDataCode("Light",
          p_oTree->GetSpecies(),
          p_oTree->GetType()),
          fShade);
    }

    fDiam = 30;  iSpecies = 0;  fShade = 0.4;
    for (i = 0; i < 1000; i++) {
      p_oTree = p_oPop->CreateTree(fTarget3X, fTarget3Y, iSpecies, clTreePopulation::adult, fDiam);
      p_oTree->SetValue(p_oPop->GetFloatDataCode("Light",
          p_oTree->GetSpecies(),
          p_oTree->GetType()),
          fShade);
    }

    fDiam = 45;  iSpecies = 1;
    for (i = 0; i < 1000; i++) {
      p_oTree = p_oPop->CreateTree(fTarget4X, fTarget4Y, iSpecies, clTreePopulation::adult, fDiam);
    }

    fDiam = 10.5;  iSpecies = 0;  fShade = 0;
    for (i = 0; i < 1000; i++) {
      p_oTree = p_oPop->CreateTree(fTarget5X, fTarget5Y, iSpecies, clTreePopulation::adult, fDiam);
      p_oTree->SetValue(p_oPop->GetFloatDataCode("Light",
          p_oTree->GetSpecies(),
          p_oTree->GetType()),
          fShade);
    }

    //Now do the run - but don't let SailLight go, or it will mess up the
    //shading values we've assigned
    for (int i = 1; i < p_oSimManager->GetNumberOfBehaviors(); i++) {
      p_oSimManager->GetBehaviorObject(i)->Action();
    }

    //Count the target trees that are left
    for (i = 0; i < iNumTargets; i++) {
      p_iCount[i] = 0;
    }

    p_oAllTrees = p_oPop->Find("all");

    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {

      //Get the X and Y
      p_oTree->GetValue(p_oPop->GetXCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fX);
      p_oTree->GetValue(p_oPop->GetYCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fY);

      //Find out if it's a target tree
      if (fabs(fX - fTarget1X) < 0.001 && fabs(fY - fTarget1Y) < 0.001) {
        p_iCount[0]++;
      } else if (fabs(fX - fTarget2X) < 0.001 && fabs(fY - fTarget2Y) < 0.001) {
        p_iCount[1]++;
      } else if (fabs(fX - fTarget3X) < 0.001 && fabs(fY - fTarget3Y) < 0.001) {
        p_iCount[2]++;
      } else if (fabs(fX - fTarget4X) < 0.001 && fabs(fY - fTarget4Y) < 0.001) {
        p_iCount[3]++;
      } else if (fabs(fX - fTarget5X) < 0.001 && fabs(fY - fTarget5Y) < 0.001) {
        p_iCount[4]++;
      }

      p_oTree = p_oAllTrees->NextTree();
    }

    //Check our counts
    //Make sure there are no divide by zero errors
    for (i = 0; i < iNumTargets; i++) {
      EXPECT_GT(p_iCount[i], 0);
    }
    EXPECT_LT(fabs(p_iCount[0] - 416.2467224)/p_iCount[0], 0.1);
    EXPECT_LT(fabs(p_iCount[1] - 346.2004823)/p_iCount[1], 0.1);
    EXPECT_LT(fabs(p_iCount[2] - 338.3539099)/p_iCount[2], 0.1);
    EXPECT_LT(fabs(p_iCount[3] - 606.8340522)/p_iCount[3], 0.1);
    EXPECT_LT(fabs(p_iCount[4] - 346.2406171)/p_iCount[4], 0.1);

    //***********************************
    // Run 2 - 3 year timestep
    //***********************************

    //Load our test file and get our tree population pointers
    p_oSimManager->ReadFile( WriteNCIMortXMLFile8() );
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );

    //Create our trees and set their light levels
    fDiam = 15; iSpecies = 1;
    for (i = 0; i < 1000; i++) {
      p_oTree = p_oPop->CreateTree(fTarget1X, fTarget1Y, iSpecies, clTreePopulation::adult, fDiam);
    }

    fDiam = 25;  iSpecies = 3;  fShade = 0.2;
    for (i = 0; i < 1000; i++) {
      p_oTree = p_oPop->CreateTree(fTarget2X, fTarget2Y, iSpecies, clTreePopulation::adult, fDiam);
      p_oTree->SetValue(p_oPop->GetFloatDataCode("Light",
          p_oTree->GetSpecies(),
          p_oTree->GetType()),
          fShade);
    }

    fDiam = 30;  iSpecies = 0;  fShade = 0.4;
    for (i = 0; i < 1000; i++) {
      p_oTree = p_oPop->CreateTree(fTarget3X, fTarget3Y, iSpecies, clTreePopulation::adult, fDiam);
      p_oTree->SetValue(p_oPop->GetFloatDataCode("Light",
          p_oTree->GetSpecies(),
          p_oTree->GetType()),
          fShade);
    }

    fDiam = 45;  iSpecies = 1;
    for (i = 0; i < 1000; i++) {
      p_oTree = p_oPop->CreateTree(fTarget4X, fTarget4Y, iSpecies, clTreePopulation::adult, fDiam);
    }

    fDiam = 10.5;  iSpecies = 0;  fShade = 0;
    for (i = 0; i < 1000; i++) {
      p_oTree = p_oPop->CreateTree(fTarget5X, fTarget5Y, iSpecies, clTreePopulation::adult, fDiam);
      p_oTree->SetValue(p_oPop->GetFloatDataCode("Light",
          p_oTree->GetSpecies(),
          p_oTree->GetType()),
          fShade);
    }


    //Now do the run - but don't let SailLight go, or it will mess up the
    //shading values we've assigned
    for (int i = 1; i < p_oSimManager->GetNumberOfBehaviors(); i++) {
      p_oSimManager->GetBehaviorObject(i)->Action();
    }

    //Count the target trees that are left
    for (i = 0; i < iNumTargets; i++) {
      p_iCount[i] = 0;
    }

    p_oAllTrees = p_oPop->Find("all");

    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {

      //Get the X and Y
      p_oTree->GetValue(p_oPop->GetXCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fX);
      p_oTree->GetValue(p_oPop->GetYCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fY);

      //Find out if it's a target tree
      if (fabs(fX - fTarget1X) < 0.001 && fabs(fY - fTarget1Y) < 0.001) {
        p_iCount[0]++;
      } else if (fabs(fX - fTarget2X) < 0.001 && fabs(fY - fTarget2Y) < 0.001) {
        p_iCount[1]++;
      } else if (fabs(fX - fTarget3X) < 0.001 && fabs(fY - fTarget3Y) < 0.001) {
        p_iCount[2]++;
      } else if (fabs(fX - fTarget4X) < 0.001 && fabs(fY - fTarget4Y) < 0.001) {
        p_iCount[3]++;
      } else if (fabs(fX - fTarget5X) < 0.001 && fabs(fY - fTarget5Y) < 0.001) {
        p_iCount[4]++;
      }

      p_oTree = p_oAllTrees->NextTree();
    }

    //Check our counts
    //Make sure there are no divide by zero errors
    for (i = 0; i < iNumTargets; i++) {
      EXPECT_GT(p_iCount[i], 0);
    }
    /*EXPECT_LT(fabs(p_iCount[0] - 72.11946237)/p_iCount[0], 0.25);
  EXPECT_LT(fabs(p_iCount[1] - 41.49378055)/p_iCount[1], 0.4);
  EXPECT_LT(fabs(p_iCount[2] - 38.73589528)/p_iCount[2], 0.3);
  EXPECT_LT(fabs(p_iCount[3] - 223.4651633)/p_iCount[3], 0.1);
  EXPECT_LT(fabs(p_iCount[4] - 41.50821325)/p_iCount[4], 0.3);*/
    EXPECT_LT(p_iCount[0] > 60 && p_iCount[0], 90);
    EXPECT_LT(p_iCount[1] > 20 && p_iCount[1], 50);
    EXPECT_LT(p_iCount[2] > 20 && p_iCount[2], 50);
    EXPECT_LT(fabs(p_iCount[3] - 223.4651633)/p_iCount[3], 0.3);
    EXPECT_LT(p_iCount[4] > 30 && p_iCount[4], 60);

    delete[] p_iCount;
    delete p_oSimManager;
  } catch (modelErr &e) {
    delete[] p_iCount;
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

////////////////////////////////////////////////////////////////////////////
// TestRun5()
// Performs a test run of NCI mortality - a Puerto-Rico-like situation. This
// run has no shading effect and uses damage effect. The damage applier is
// not applied to all species.
// WriteNCIMortXMLFile9() performs setup for a 1-year timestep; then WriteNCIMortXMLFile10()
// performs setup for an otherwise identical 3-year timestep.
//
// There are 8 target trees, for which 1000 copies of each will be created.
// Then the remainder left after a timestep will be checked against the
// testing spreadsheet expected results.
////////////////////////////////////////////////////////////////////////////
TEST(NCIMasterMortality, TestRun5) {

  int *p_iCount; //for counting target trees
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    clTreePopulation * p_oPop;
    clTreeSearch *p_oAllTrees;
    clTree *p_oTree;
    float fDiam, fX, fY,
    fTarget1X = 10, fTarget1Y = 10, //coords of target 1 trees
    fTarget2X = 20, fTarget2Y = 20, //coords of target 2 trees
    fTarget3X = 30, fTarget3Y = 30, //coords of target 3 trees
    fTarget4X = 50, fTarget4Y = 50, //coords of target 4 trees
    fTarget5X = 53, fTarget5Y = 52, //coords of target 5 trees
    fTarget6X = 59, fTarget6Y = 50, //coords of target 6 trees
    fTarget7X = 50, fTarget7Y = 59, //coords of target 7 trees
    fTarget8X = 55, fTarget8Y = 55; //coords of target 8 trees
    int iSpecies, iDamage, i, iNumTargets = 8;
    p_iCount = new int[iNumTargets];

    //***********************************
    // Run 1 - 1 year timestep
    //***********************************
    //Load our test file and get our tree population pointers
    p_oSimManager->ReadFile( WriteNCIMortXMLFile9() );
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );

    //Create our trees and set the damage level for each
    fDiam = 11; iSpecies = 0; iDamage = 0;
    for (i = 0; i < 1000; i++) {
      p_oTree = p_oPop->CreateTree(fTarget1X, fTarget1Y, iSpecies, clTreePopulation::adult, fDiam);
      p_oTree->SetValue(p_oPop->GetIntDataCode("stm_dmg",
          p_oTree->GetSpecies(),
          p_oTree->GetType()),
          iDamage);
    }

    fDiam = 8;  iSpecies = 1;
    for (i = 0; i < 1000; i++) {
      p_oTree = p_oPop->CreateTree(fTarget2X, fTarget2Y, iSpecies, clTreePopulation::sapling, fDiam);
    }

    fDiam = 15;  iSpecies = 3;  iDamage = 2000;
    for (i = 0; i < 1000; i++) {
      p_oTree = p_oPop->CreateTree(fTarget3X, fTarget3Y, iSpecies, clTreePopulation::adult, fDiam);
      p_oTree->SetValue(p_oPop->GetIntDataCode("stm_dmg",
          p_oTree->GetSpecies(),
          p_oTree->GetType()),
          iDamage);
    }

    fDiam = 10.5;  iSpecies = 0;  iDamage = 0;
    for (i = 0; i < 1000; i++) {
      p_oTree = p_oPop->CreateTree(fTarget4X, fTarget4Y, iSpecies, clTreePopulation::adult, fDiam);
      p_oTree->SetValue(p_oPop->GetIntDataCode("stm_dmg",
          p_oTree->GetSpecies(),
          p_oTree->GetType()),
          iDamage);
    }

    fDiam = 15;  iSpecies = 1;
    for (i = 0; i < 1000; i++) {
      p_oTree = p_oPop->CreateTree(fTarget5X, fTarget5Y, iSpecies, clTreePopulation::adult, fDiam);
    }

    fDiam = 25;  iSpecies = 3;  iDamage = 2000;
    for (i = 0; i < 1000; i++) {
      p_oTree = p_oPop->CreateTree(fTarget6X, fTarget6Y, iSpecies, clTreePopulation::adult, fDiam);
      p_oTree->SetValue(p_oPop->GetIntDataCode("stm_dmg",
          p_oTree->GetSpecies(),
          p_oTree->GetType()),
          iDamage);
    }

    fDiam = 30;  iSpecies = 0;  iDamage = 2000;
    for (i = 0; i < 1000; i++) {
      p_oTree = p_oPop->CreateTree(fTarget7X, fTarget7Y, iSpecies, clTreePopulation::adult, fDiam);
      p_oTree->SetValue(p_oPop->GetIntDataCode("stm_dmg",
          p_oTree->GetSpecies(),
          p_oTree->GetType()),
          iDamage);
    }

    fDiam = 45;  iSpecies = 1;
    for (i = 0; i < 1000; i++) {
      p_oTree = p_oPop->CreateTree(fTarget8X, fTarget8Y, iSpecies, clTreePopulation::adult, fDiam);
    }

    p_oPop->CreateTree(56, 56, 0, clTreePopulation::seedling, 0.2);

    //Now do the run
    p_oSimManager->RunSim(1);

    //Count the target trees that are left
    for (i = 0; i < iNumTargets; i++) {
      p_iCount[i] = 0;
    }

    p_oAllTrees = p_oPop->Find("all");

    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {

      //Get the X and Y
      p_oTree->GetValue(p_oPop->GetXCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fX);
      p_oTree->GetValue(p_oPop->GetYCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fY);

      //Find out if it's a target tree
      if (fabs(fX - fTarget1X) < 0.001 && fabs(fY - fTarget1Y) < 0.001) {
        p_iCount[0]++;
      } else if (fabs(fX - fTarget2X) < 0.001 && fabs(fY - fTarget2Y) < 0.001) {
        p_iCount[1]++;
      } else if (fabs(fX - fTarget3X) < 0.001 && fabs(fY - fTarget3Y) < 0.001) {
        p_iCount[2]++;
      } else if (fabs(fX - fTarget4X) < 0.001 && fabs(fY - fTarget4Y) < 0.001) {
        p_iCount[3]++;
      } else if (fabs(fX - fTarget5X) < 0.001 && fabs(fY - fTarget5Y) < 0.001) {
        p_iCount[4]++;
      } else if (fabs(fX - fTarget6X) < 0.001 && fabs(fY - fTarget6Y) < 0.001) {
        p_iCount[5]++;
      } else if (fabs(fX - fTarget7X) < 0.001 && fabs(fY - fTarget7Y) < 0.001) {
        p_iCount[6]++;
      } else if (fabs(fX - fTarget8X) < 0.001 && fabs(fY - fTarget8Y) < 0.001) {
        p_iCount[7]++;
      }

      p_oTree = p_oAllTrees->NextTree();
    }

    //Check our counts
    //Make sure there are no divide by zero errors
    for (i = 0; i < iNumTargets; i++) {
      EXPECT_GT(p_iCount[i], 0);
    }
    EXPECT_LT(fabs(p_iCount[0] - 955.0435325)/p_iCount[0], 0.1);
    EXPECT_LT(fabs(p_iCount[1] - 507.9423412)/p_iCount[1], 0.1);
    EXPECT_LT(fabs(p_iCount[2] - 609.8269821)/p_iCount[2], 0.1);
    EXPECT_LT(fabs(p_iCount[3] - 405.5827587)/p_iCount[3], 0.1);
    EXPECT_LT(fabs(p_iCount[4] - 320.0150515)/p_iCount[4], 0.15);
    EXPECT_LT(fabs(p_iCount[5] - 543.6439835)/p_iCount[5], 0.1);
    EXPECT_LT(fabs(p_iCount[6] - 107.8860835)/p_iCount[6], 0.2);
    EXPECT_LT(fabs(p_iCount[7] - 356.111574)/p_iCount[7], 0.1);

    //***********************************
    // Run 2 - 3 year timestep
    //***********************************
    //Load our test file and get our tree population pointers
    p_oSimManager->ReadFile( WriteNCIMortXMLFile10() );
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );

    //Create our trees and set the damage level for each
    fDiam = 11; iSpecies = 0; iDamage = 0;
    for (i = 0; i < 1000; i++) {
      p_oTree = p_oPop->CreateTree(fTarget1X, fTarget1Y, iSpecies, clTreePopulation::adult, fDiam);
      p_oTree->SetValue(p_oPop->GetIntDataCode("stm_dmg",
          p_oTree->GetSpecies(),
          p_oTree->GetType()),
          iDamage);
    }

    fDiam = 8;  iSpecies = 1;
    for (i = 0; i < 1000; i++) {
      p_oTree = p_oPop->CreateTree(fTarget2X, fTarget2Y, iSpecies, clTreePopulation::sapling, fDiam);
    }

    fDiam = 15;  iSpecies = 3;  iDamage = 2000;
    for (i = 0; i < 1000; i++) {
      p_oTree = p_oPop->CreateTree(fTarget3X, fTarget3Y, iSpecies, clTreePopulation::adult, fDiam);
      p_oTree->SetValue(p_oPop->GetIntDataCode("stm_dmg",
          p_oTree->GetSpecies(),
          p_oTree->GetType()),
          iDamage);
    }

    fDiam = 10.5;  iSpecies = 0;  iDamage = 0;
    for (i = 0; i < 1000; i++) {
      p_oTree = p_oPop->CreateTree(fTarget4X, fTarget4Y, iSpecies, clTreePopulation::adult, fDiam);
      p_oTree->SetValue(p_oPop->GetIntDataCode("stm_dmg",
          p_oTree->GetSpecies(),
          p_oTree->GetType()),
          iDamage);
    }

    fDiam = 15;  iSpecies = 1;
    for (i = 0; i < 1000; i++) {
      p_oTree = p_oPop->CreateTree(fTarget5X, fTarget5Y, iSpecies, clTreePopulation::adult, fDiam);
    }

    fDiam = 25;  iSpecies = 3;  iDamage = 2000;
    for (i = 0; i < 1000; i++) {
      p_oTree = p_oPop->CreateTree(fTarget6X, fTarget6Y, iSpecies, clTreePopulation::adult, fDiam);
      p_oTree->SetValue(p_oPop->GetIntDataCode("stm_dmg",
          p_oTree->GetSpecies(),
          p_oTree->GetType()),
          iDamage);
    }

    fDiam = 30;  iSpecies = 0;  iDamage = 2000;
    for (i = 0; i < 1000; i++) {
      p_oTree = p_oPop->CreateTree(fTarget7X, fTarget7Y, iSpecies, clTreePopulation::adult, fDiam);
      p_oTree->SetValue(p_oPop->GetIntDataCode("stm_dmg",
          p_oTree->GetSpecies(),
          p_oTree->GetType()),
          iDamage);
    }

    fDiam = 45;  iSpecies = 1;
    for (i = 0; i < 1000; i++) {
      p_oTree = p_oPop->CreateTree(fTarget8X, fTarget8Y, iSpecies, clTreePopulation::adult, fDiam);
    }

    p_oPop->CreateTree(56, 56, 0, clTreePopulation::seedling, 0.2);

    //Now do the run
    p_oSimManager->RunSim(1);

    //Count the target trees that are left
    for (i = 0; i < iNumTargets; i++) {
      p_iCount[i] = 0;
    }

    p_oAllTrees = p_oPop->Find("all");

    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {

      //Get the X and Y
      p_oTree->GetValue(p_oPop->GetXCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fX);
      p_oTree->GetValue(p_oPop->GetYCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fY);

      //Find out if it's a target tree
      if (fabs(fX - fTarget1X) < 0.001 && fabs(fY - fTarget1Y) < 0.001) {
        p_iCount[0]++;
      } else if (fabs(fX - fTarget2X) < 0.001 && fabs(fY - fTarget2Y) < 0.001) {
        p_iCount[1]++;
      } else if (fabs(fX - fTarget3X) < 0.001 && fabs(fY - fTarget3Y) < 0.001) {
        p_iCount[2]++;
      } else if (fabs(fX - fTarget4X) < 0.001 && fabs(fY - fTarget4Y) < 0.001) {
        p_iCount[3]++;
      } else if (fabs(fX - fTarget5X) < 0.001 && fabs(fY - fTarget5Y) < 0.001) {
        p_iCount[4]++;
      } else if (fabs(fX - fTarget6X) < 0.001 && fabs(fY - fTarget6Y) < 0.001) {
        p_iCount[5]++;
      } else if (fabs(fX - fTarget7X) < 0.001 && fabs(fY - fTarget7Y) < 0.001) {
        p_iCount[6]++;
      } else if (fabs(fX - fTarget8X) < 0.001 && fabs(fY - fTarget8Y) < 0.001) {
        p_iCount[7]++;
      }

      p_oTree = p_oAllTrees->NextTree();
    }

    //Check our counts
    //Make sure there are no divide by zero errors
    for (i = 0; i < iNumTargets; i++) {
      if (i != 6) {
        EXPECT_GT(p_iCount[i], 0);
      }
    }
    EXPECT_LT(fabs(p_iCount[0] - 871.1029885)/p_iCount[0], 0.1);
    EXPECT_LT(fabs(p_iCount[1] - 131.0518781)/p_iCount[1], 0.2);
    EXPECT_LT(fabs(p_iCount[2] - 226.7879149)/p_iCount[2], 0.15);
    //EXPECT_LT(fabs(p_iCount[3] - 66.71729881)/p_iCount[3], 0.3);
    EXPECT_LT(p_iCount[3] > 50 && p_iCount[3], 85);
    //EXPECT_LT(fabs(p_iCount[4] - 32.77262402)/p_iCount[4], 0.4);
    EXPECT_LT(p_iCount[4] > 20 && p_iCount[4], 55);
    EXPECT_LT(fabs(p_iCount[5] - 160.6733165)/p_iCount[5], 0.2);
    EXPECT_LT(p_iCount[6], 10);
    //EXPECT_LT(fabs(p_iCount[7] - 45.16045061)/p_iCount[7], 0.3);
    EXPECT_LT(p_iCount[7] > 30 && p_iCount[7], 65);

    delete[] p_iCount;
    delete p_oSimManager;
  } catch (modelErr &e) {
    delete[] p_iCount;
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

////////////////////////////////////////////////////////////////////////////
// TestRun6()
// This run has only size effect, and a non-1 value for max survival time period
// length.
////////////////////////////////////////////////////////////////////////////
TEST(NCIMasterMortality, TestRun6) {

  int *p_iCount; //for counting target trees
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    clTreePopulation * p_oPop;
    clTreeSearch *p_oAllTrees;
    clTree *p_oTree;
    float fDiam, fX, fY,
    fTarget1X = 10, fTarget1Y = 10, //coords of target 1 trees
    fTarget2X = 20, fTarget2Y = 20, //coords of target 2 trees
    fTarget3X = 30, fTarget3Y = 30, //coords of target 3 trees
    fTarget4X = 50, fTarget4Y = 50, //coords of target 4 trees
    fTarget5X = 53, fTarget5Y = 52, //coords of target 5 trees
    fTarget6X = 59, fTarget6Y = 50, //coords of target 6 trees
    fTarget7X = 50, fTarget7Y = 59, //coords of target 7 trees
    fTarget8X = 55, fTarget8Y = 55; //coords of target 8 trees
    int iSpecies, i, iNumTargets = 8;
    p_iCount = new int[iNumTargets];

    //***********************************
    // Run 1 - 1 year timestep
    //***********************************
    //Load our test file and get our tree population pointers
    p_oSimManager->ReadFile( WriteNCIMortXMLFile11() );
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );

    //Create our trees and set the damage level for each
    fDiam = 11; iSpecies = 0;
    for (i = 0; i < 1000; i++) {
      p_oTree = p_oPop->CreateTree(fTarget1X, fTarget1Y, iSpecies, clTreePopulation::adult, fDiam);
    }

    fDiam = 8;  iSpecies = 1;
    for (i = 0; i < 1000; i++) {
      p_oTree = p_oPop->CreateTree(fTarget2X, fTarget2Y, iSpecies, clTreePopulation::sapling, fDiam);
    }

    fDiam = 15;  iSpecies = 3;
    for (i = 0; i < 1000; i++) {
      p_oTree = p_oPop->CreateTree(fTarget3X, fTarget3Y, iSpecies, clTreePopulation::adult, fDiam);
    }

    fDiam = 10.5;  iSpecies = 0;
    for (i = 0; i < 1000; i++) {
      p_oTree = p_oPop->CreateTree(fTarget4X, fTarget4Y, iSpecies, clTreePopulation::adult, fDiam);
    }

    fDiam = 15;  iSpecies = 1;
    for (i = 0; i < 1000; i++) {
      p_oTree = p_oPop->CreateTree(fTarget5X, fTarget5Y, iSpecies, clTreePopulation::adult, fDiam);
    }

    fDiam = 25;  iSpecies = 3;
    for (i = 0; i < 1000; i++) {
      p_oTree = p_oPop->CreateTree(fTarget6X, fTarget6Y, iSpecies, clTreePopulation::adult, fDiam);
    }

    fDiam = 30;  iSpecies = 0;
    for (i = 0; i < 1000; i++) {
      p_oTree = p_oPop->CreateTree(fTarget7X, fTarget7Y, iSpecies, clTreePopulation::adult, fDiam);
    }

    fDiam = 45;  iSpecies = 1;
    for (i = 0; i < 1000; i++) {
      p_oTree = p_oPop->CreateTree(fTarget8X, fTarget8Y, iSpecies, clTreePopulation::adult, fDiam);
    }

    p_oPop->CreateTree(56, 56, 0, clTreePopulation::seedling, 0.2);

    //Now do the run
    p_oSimManager->RunSim(1);

    //Count the target trees that are left
    for (i = 0; i < iNumTargets; i++) {
      p_iCount[i] = 0;
    }

    p_oAllTrees = p_oPop->Find("all");

    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {

      //Get the X and Y
      p_oTree->GetValue(p_oPop->GetXCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fX);
      p_oTree->GetValue(p_oPop->GetYCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fY);

      //Find out if it's a target tree
      if (fabs(fX - fTarget1X) < 0.001 && fabs(fY - fTarget1Y) < 0.001) {
        p_iCount[0]++;
      } else if (fabs(fX - fTarget2X) < 0.001 && fabs(fY - fTarget2Y) < 0.001) {
        p_iCount[1]++;
      } else if (fabs(fX - fTarget3X) < 0.001 && fabs(fY - fTarget3Y) < 0.001) {
        p_iCount[2]++;
      } else if (fabs(fX - fTarget4X) < 0.001 && fabs(fY - fTarget4Y) < 0.001) {
        p_iCount[3]++;
      } else if (fabs(fX - fTarget5X) < 0.001 && fabs(fY - fTarget5Y) < 0.001) {
        p_iCount[4]++;
      } else if (fabs(fX - fTarget6X) < 0.001 && fabs(fY - fTarget6Y) < 0.001) {
        p_iCount[5]++;
      } else if (fabs(fX - fTarget7X) < 0.001 && fabs(fY - fTarget7Y) < 0.001) {
        p_iCount[6]++;
      } else if (fabs(fX - fTarget8X) < 0.001 && fabs(fY - fTarget8Y) < 0.001) {
        p_iCount[7]++;
      }

      p_oTree = p_oAllTrees->NextTree();
    }

    //Check our counts
    //Make sure there are no divide by zero errors
    for (i = 0; i < iNumTargets; i++) {
      EXPECT_GT(p_iCount[i], 0);
    }
    EXPECT_LT(fabs(p_iCount[0] - 984.78)/p_iCount[0], 0.1);
    EXPECT_LT(fabs(p_iCount[1] - 797.88)/p_iCount[1], 0.1);
    EXPECT_LT(fabs(p_iCount[2] - 989.21)/p_iCount[2], 0.1);
    EXPECT_LT(fabs(p_iCount[3] - 984.07)/p_iCount[3], 0.1);
    EXPECT_LT(fabs(p_iCount[4] - 873.67)/p_iCount[4], 0.1);
    EXPECT_LT(fabs(p_iCount[5] - 975.38)/p_iCount[5], 0.5);
    EXPECT_LT(fabs(p_iCount[6] - 993.17)/p_iCount[6], 0.1);
    EXPECT_LT(fabs(p_iCount[7] - 967.31)/p_iCount[7], 0.1);

    //***********************************
    // Run 2 - 5 year timestep
    //***********************************
    //Load our test file and get our tree population pointers
    p_oSimManager->ReadFile( WriteNCIMortXMLFile12() );
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );

    //Create our trees and set the damage level for each
    fDiam = 11; iSpecies = 0;
    for (i = 0; i < 1000; i++) {
      p_oTree = p_oPop->CreateTree(fTarget1X, fTarget1Y, iSpecies, clTreePopulation::adult, fDiam);
    }

    fDiam = 8;  iSpecies = 1;
    for (i = 0; i < 1000; i++) {
      p_oTree = p_oPop->CreateTree(fTarget2X, fTarget2Y, iSpecies, clTreePopulation::sapling, fDiam);
    }

    fDiam = 15;  iSpecies = 3;
    for (i = 0; i < 1000; i++) {
      p_oTree = p_oPop->CreateTree(fTarget3X, fTarget3Y, iSpecies, clTreePopulation::adult, fDiam);
    }

    fDiam = 10.5;  iSpecies = 0;
    for (i = 0; i < 1000; i++) {
      p_oTree = p_oPop->CreateTree(fTarget4X, fTarget4Y, iSpecies, clTreePopulation::adult, fDiam);
    }

    fDiam = 15;  iSpecies = 1;
    for (i = 0; i < 1000; i++) {
      p_oTree = p_oPop->CreateTree(fTarget5X, fTarget5Y, iSpecies, clTreePopulation::adult, fDiam);
    }

    fDiam = 25;  iSpecies = 3;
    for (i = 0; i < 1000; i++) {
      p_oTree = p_oPop->CreateTree(fTarget6X, fTarget6Y, iSpecies, clTreePopulation::adult, fDiam);
    }

    fDiam = 30;  iSpecies = 0;
    for (i = 0; i < 1000; i++) {
      p_oTree = p_oPop->CreateTree(fTarget7X, fTarget7Y, iSpecies, clTreePopulation::adult, fDiam);
    }

    fDiam = 45;  iSpecies = 1;
    for (i = 0; i < 1000; i++) {
      p_oTree = p_oPop->CreateTree(fTarget8X, fTarget8Y, iSpecies, clTreePopulation::adult, fDiam);
    }

    p_oPop->CreateTree(56, 56, 0, clTreePopulation::seedling, 0.2);

    //Now do the run
    p_oSimManager->RunSim(1);

    //Count the target trees that are left
    for (i = 0; i < iNumTargets; i++) {
      p_iCount[i] = 0;
    }

    p_oAllTrees = p_oPop->Find("all");

    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {

      //Get the X and Y
      p_oTree->GetValue(p_oPop->GetXCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fX);
      p_oTree->GetValue(p_oPop->GetYCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fY);

      //Find out if it's a target tree
      if (fabs(fX - fTarget1X) < 0.001 && fabs(fY - fTarget1Y) < 0.001) {
        p_iCount[0]++;
      } else if (fabs(fX - fTarget2X) < 0.001 && fabs(fY - fTarget2Y) < 0.001) {
        p_iCount[1]++;
      } else if (fabs(fX - fTarget3X) < 0.001 && fabs(fY - fTarget3Y) < 0.001) {
        p_iCount[2]++;
      } else if (fabs(fX - fTarget4X) < 0.001 && fabs(fY - fTarget4Y) < 0.001) {
        p_iCount[3]++;
      } else if (fabs(fX - fTarget5X) < 0.001 && fabs(fY - fTarget5Y) < 0.001) {
        p_iCount[4]++;
      } else if (fabs(fX - fTarget6X) < 0.001 && fabs(fY - fTarget6Y) < 0.001) {
        p_iCount[5]++;
      } else if (fabs(fX - fTarget7X) < 0.001 && fabs(fY - fTarget7Y) < 0.001) {
        p_iCount[6]++;
      } else if (fabs(fX - fTarget8X) < 0.001 && fabs(fY - fTarget8Y) < 0.001) {
        p_iCount[7]++;
      }

      p_oTree = p_oAllTrees->NextTree();
    }

    //Check our counts
    //Make sure there are no divide by zero errors
    for (i = 0; i < iNumTargets; i++) {
      if (i != 6) {
        EXPECT_GT(p_iCount[i], 0);
      }
    }
    EXPECT_LT(fabs(p_iCount[0] - 926.21)/p_iCount[0], 0.1);
    EXPECT_LT(fabs(p_iCount[1] - 323.36)/p_iCount[1], 0.1);
    EXPECT_LT(fabs(p_iCount[2] - 947.20)/p_iCount[2], 0.1);
    EXPECT_LT(fabs(p_iCount[3] - 922.89)/p_iCount[3], 0.3);
    EXPECT_LT(fabs(p_iCount[4] - 509.03)/p_iCount[4], 0.4);
    EXPECT_LT(fabs(p_iCount[5] - 882.82)/p_iCount[5], 0.1);
    EXPECT_LT(fabs(p_iCount[6] - 966.32)/p_iCount[6], 0.1);
    EXPECT_LT(fabs(p_iCount[7] - 846.92)/p_iCount[7], 0.3);

    delete[] p_iCount;
    delete p_oSimManager;
  } catch (modelErr &e) {
    delete[] p_iCount;
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

////////////////////////////////////////////////////////////////////////////
// TestErrorProcessing()
// Tests error processing for input files. Tests:
//
// -- Max. radius of neighbor effects must be > 0
// -- Max probability of survival for each species must be 0-1
// -- X0  (Size effect mode) for each species must not = 0
// -- Xb (Size effect variance) for each species must not = 0
// -- Eta for each species for each damage category beyond undamaged must be
// between 0 and 1
// -- Storm Effect parameters for each species for each damage category beyond
// undamaged must be between 0 and 1
//
// WriteNCIMortXMLErrorFileX (where X = 1-12) is written and checked to make sure that
// each produces an error.
////////////////////////////////////////////////////////////////////////////
TEST(NCIMasterMortality, TestErrorProcessing) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try
  {
    p_oSimManager->ReadFile(WriteNCIMortXMLErrorFile1());
    FAIL() << "TestNCIMasterMortality error processing didn't catch error for WriteNCIMortXMLErrorFile1.";
  }
  catch (modelErr& err)
  {
    if (err.sFunction.compare("clNCITermWithNeighborDamage::DoSetup") != 0)
    {
      FAIL() << "TestNCIMasterMortality error processing caught wrong error for WriteNCIMortXMLErrorFile1.";
    }
    ;
  }

  try
  {
    p_oSimManager->ReadFile(WriteNCIMortXMLErrorFile2());
    FAIL() << "TestNCIMasterMortality error processing didn't catch error for WriteNCIMortXMLErrorFile2.";
  }
  catch (modelErr& err)
  {
    if (err.sFunction.compare("clNCIMasterMortality::DoShellSetup") != 0)
    {
      FAIL() << "TestNCIMasterMortality error processing caught wrong error for WriteNCIMortXMLErrorFile2.";
    }
    ;
  }

  try
  {
    p_oSimManager->ReadFile(WriteNCIMortXMLErrorFile3());
    FAIL() << "TestNCIMasterMortality error processing didn't catch error for WriteNCIMortXMLErrorFile3.";
  }
  catch (modelErr& err)
  {
    if (err.sFunction.compare("clSizeEffectDefault::DoSetup") != 0)
    {
      FAIL() << "TestNCIMasterMortality error processing caught wrong error for WriteNCIMortXMLErrorFile3.";
    }
    ;
  }

  try
  {
    p_oSimManager->ReadFile(WriteNCIMortXMLErrorFile4());
    FAIL() << "TestNCIMasterMortality error processing didn't catch error for WriteNCIMortXMLErrorFile4.";
  }
  catch (modelErr& err)
  {
    if (err.sFunction.compare("clSizeEffectDefault::DoSetup") != 0)
    {
      FAIL() << "TestNCIMasterMortality error processing caught wrong error for WriteNCIMortXMLErrorFile4.";
    }
    ;
  }

  try
  {
    p_oSimManager->ReadFile(WriteNCIMortXMLErrorFile5());
    FAIL() << "TestNCIMasterMortality error processing didn't catch error for WriteNCIMortXMLErrorFile5.";
  }
  catch (modelErr& err)
  {
    if (err.sFunction.compare("clNCITermWithNeighborDamage::DoSetup") != 0)
    {
      FAIL() << "TestNCIMasterMortality error processing caught wrong error for WriteNCIMortXMLErrorFile5.";
    }
    ;
  }

  try
  {
    p_oSimManager->ReadFile(WriteNCIMortXMLErrorFile6());
    FAIL() << "TestNCIMasterMortality error processing didn't catch error for WriteNCIMortXMLErrorFile6.";
  }
  catch (modelErr& err)
  {
    if (err.sFunction.compare("clNCITermWithNeighborDamage::DoSetup") != 0)
    {
      FAIL() << "TestNCIMasterMortality error processing caught wrong error for WriteNCIMortXMLErrorFile6.";
    }
    ;
  }

  try
  {
    p_oSimManager->ReadFile(WriteNCIMortXMLErrorFile7());
    FAIL() << "TestNCIMasterMortality error processing didn't catch error for WriteNCIMortXMLErrorFile7.";
  }
  catch (modelErr& err)
  {
    if (err.sFunction.compare("clNCITermWithNeighborDamage::DoSetup") != 0)
    {
      FAIL() << "TestNCIMasterMortality error processing caught wrong error for WriteNCIMortXMLErrorFile7.";
    }
    ;
  }

  try
  {
    p_oSimManager->ReadFile(WriteNCIMortXMLErrorFile8());
    FAIL() << "TestNCIMasterMortality error processing didn't catch error for WriteNCIMortXMLErrorFile8.";
  }
  catch (modelErr& err)
  {
    if (err.sFunction.compare("clNCITermWithNeighborDamage::DoSetup") != 0)
    {
      FAIL() << "TestNCIMasterMortality error processing caught wrong error for WriteNCIMortXMLErrorFile8.";
    }
    ;
  }

  try
  {
    p_oSimManager->ReadFile(WriteNCIMortXMLErrorFile9());
    FAIL() << "TestNCIMasterMortality error processing didn't catch error for WriteNCIMortXMLErrorFile9.";
  }
  catch (modelErr& err)
  {
    if (err.sFunction.compare("clDamageEffectDefault::DoSetup") != 0)
    {
      FAIL() << "TestNCIMasterMortality error processing caught wrong error for WriteNCIMortXMLErrorFile9.";
    }
    ;
  }

  try
  {
    p_oSimManager->ReadFile(WriteNCIMortXMLErrorFile10());
    FAIL() << "TestNCIMasterMortality error processing didn't catch error for WriteNCIMortXMLErrorFile10.";
  }
  catch (modelErr& err)
  {
    if (err.sFunction.compare("clDamageEffectDefault::DoSetup") != 0)
    {
      FAIL() << "TestNCIMasterMortality error processing caught wrong error for WriteNCIMortXMLErrorFile10.";
    }
    ;
  }

  try
  {
    p_oSimManager->ReadFile(WriteNCIMortXMLErrorFile11());
    FAIL() << "TestNCIMasterMortality error processing didn't catch error for WriteNCIMortXMLErrorFile11.";
  }
  catch (modelErr& err)
  {
    if (err.sFunction.compare("clDamageEffectDefault::DoSetup") != 0)
    {
      FAIL() << "TestNCIMasterMortality error processing caught wrong error for WriteNCIMortXMLErrorFile11.";
    }
    ;
  }

  try
  {
    p_oSimManager->ReadFile(WriteNCIMortXMLErrorFile12());
    FAIL() << "TestNCIMasterMortality error processing didn't catch error for WriteNCIMortXMLErrorFile12.";
  }
  catch (modelErr& err)
  {
    if (err.sFunction.compare("clDamageEffectDefault::DoSetup") != 0)
    {
      FAIL() << "TestNCIMasterMortality error processing caught wrong error for WriteNCIMortXMLErrorFile12.";
    }
    ;
  }

  try
  {
    p_oSimManager->ReadFile(WriteNCIMortXMLErrorFile13());
    FAIL() << "TestNCIMasterMortality error processing didn't catch error for WriteNCIMortXMLErrorFile13.";
  }
  catch (modelErr& err)
  {
    if (err.sFunction.compare("clShadingEffectDefault::DoSetup") != 0)
    {
      FAIL() << "TestNCIMasterMortality error processing caught wrong error for WriteNCIMortXMLErrorFile13.";
    }
    ;
  }
  delete p_oSimManager;
}



////////////////////////////////////////////////////////////////////////////
// WriteNCIMortXMLFile1()
////////////////////////////////////////////////////////////////////////////
const char* WriteNCIMortXMLFile1() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  //Write file
  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06010101\">"
       << "<plot>"
       << "<timesteps>2</timesteps>"
       << "<yearsPerTimestep>1</yearsPerTimestep>";

  WriteNCIMortRun1CommonStuff(oOut);

  oOut.close();

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteNCIMortXMLFile2()
////////////////////////////////////////////////////////////////////////////
const char* WriteNCIMortXMLFile2() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  //Write file
  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06010101\">"
       << "<plot>"
       << "<timesteps>2</timesteps>"
       << "<yearsPerTimestep>3</yearsPerTimestep>";

  WriteNCIMortRun1CommonStuff(oOut);

  oOut.close();

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteNCIMortXMLFile3()
////////////////////////////////////////////////////////////////////////////
const char* WriteNCIMortXMLFile3() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  //Write file
  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06010101\">"
       << "<plot>"
       << "<timesteps>2</timesteps>"
       << "<yearsPerTimestep>1</yearsPerTimestep>";

  WriteNCIMortRun2CommonStuff(oOut);

  oOut.close();

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteXMLFile4()
////////////////////////////////////////////////////////////////////////////
const char* WriteNCIMortXMLFile4() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  //Write file
  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06010101\">"
       << "<plot>"
       << "<timesteps>2</timesteps>"
       << "<yearsPerTimestep>3</yearsPerTimestep>";

  WriteNCIMortRun2CommonStuff(oOut);

  oOut.close();

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteNCIMortXMLFile5()
////////////////////////////////////////////////////////////////////////////
const char* WriteNCIMortXMLFile5() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  //Write file
  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06010101\">"
       << "<plot>"
       << "<timesteps>2</timesteps>"
       << "<yearsPerTimestep>1</yearsPerTimestep>";

  WriteNCIMortRun3CommonStuff(oOut);

  oOut.close();

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteNCIMortXMLFile6()
////////////////////////////////////////////////////////////////////////////
const char* WriteNCIMortXMLFile6() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  //Write file
  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06010101\">"
       << "<plot>"
       << "<timesteps>2</timesteps>"
       << "<yearsPerTimestep>3</yearsPerTimestep>";

  WriteNCIMortRun3CommonStuff(oOut);

  oOut.close();

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteNCIMortXMLFile7()
////////////////////////////////////////////////////////////////////////////
const char* WriteNCIMortXMLFile7() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  //Write file
  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06010101\">"
       << "<plot>"
       << "<timesteps>2</timesteps>"
       << "<yearsPerTimestep>1</yearsPerTimestep>";

  WriteNCIMortRun4CommonStuff(oOut);

  oOut.close();

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteNCIMortXMLFile8()
////////////////////////////////////////////////////////////////////////////
const char* WriteNCIMortXMLFile8() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  //Write file
  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06010101\">"
       << "<plot>"
       << "<timesteps>2</timesteps>"
       << "<yearsPerTimestep>3</yearsPerTimestep>";

  WriteNCIMortRun4CommonStuff(oOut);

  oOut.close();

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteNCIMortXMLFile9()
////////////////////////////////////////////////////////////////////////////
const char* WriteNCIMortXMLFile9() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  //Write file
  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06010101\">"
       << "<plot>"
       << "<timesteps>2</timesteps>"
       << "<yearsPerTimestep>1</yearsPerTimestep>";

  WriteNCIMortRun5CommonStuff(oOut);

  oOut.close();

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteNCIMortXMLFile10()
////////////////////////////////////////////////////////////////////////////
const char* WriteNCIMortXMLFile10() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  //Write file
  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06010101\">"
       << "<plot>"
       << "<timesteps>2</timesteps>"
       << "<yearsPerTimestep>3</yearsPerTimestep>";

  WriteNCIMortRun5CommonStuff(oOut);

  oOut.close();

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteNCIMortXMLFile11()
////////////////////////////////////////////////////////////////////////////
const char* WriteNCIMortXMLFile11() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  //Write file
  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06010101\">"
       << "<plot>"
       << "<timesteps>2</timesteps>"
       << "<yearsPerTimestep>1</yearsPerTimestep>";

  WriteNCIMortRun6CommonStuff(oOut);

  oOut.close();

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteNCIMortXMLFile12()
////////////////////////////////////////////////////////////////////////////
const char* WriteNCIMortXMLFile12() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  //Write file
  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06010101\">"
       << "<plot>"
       << "<timesteps>2</timesteps>"
       << "<yearsPerTimestep>5</yearsPerTimestep>";

  WriteNCIMortRun6CommonStuff(oOut);

  oOut.close();

  return cFileString;
}


////////////////////////////////////////////////////////////////////////////
// WriteNCIMortXMLErrorFile1()
////////////////////////////////////////////////////////////////////////////
const char* WriteNCIMortXMLErrorFile1() {
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

  WriteNCIMortCommonErrorStuff(oOut);

  oOut << "<NCIMasterMortality3>"
       << "<nciWhichShadingEffect>" << no_shading << "</nciWhichShadingEffect>"
       << "<nciWhichCrowdingEffect>" << default_crowding_effect << "</nciWhichCrowdingEffect>"
       << "<nciWhichNCITerm>" << nci_with_neighbor_damage << "</nciWhichNCITerm>"
       << "<nciWhichSizeEffect>" << default_size_effect << "</nciWhichSizeEffect>"
       << "<nciWhichDamageEffect>" << default_damage_effect << "</nciWhichDamageEffect>"
       << "<nciWhichPrecipitationEffect>" << no_precip_effect << "</nciWhichPrecipitationEffect>"
       << "<nciWhichTemperatureEffect>" << no_temp_effect << "</nciWhichTemperatureEffect>"
       << "<nciWhichNitrogenEffect>" << no_nitrogen_effect << "</nciWhichNitrogenEffect>"
       << "<nciWhichInfectionEffect>" << no_infection_effect << "</nciWhichInfectionEffect>"
       << "<mo_nciMortSurvPeriod>1</mo_nciMortSurvPeriod>"
       << "<nciMaxCrowdingRadius>"
       << "<nmcrVal species=\"Species_1\">10</nmcrVal>"
       << "<nmcrVal species=\"Species_2\">-10</nmcrVal>"
       << "</nciMaxCrowdingRadius>"
       << "<nciAlpha>"
       << "<naVal species=\"Species_1\">2.81</naVal>"
       << "<naVal species=\"Species_2\">2.81</naVal>"
       << "</nciAlpha>"
       << "<nciBeta>"
       << "<nbVal species=\"Species_1\">0.5</nbVal>"
       << "<nbVal species=\"Species_2\">0.5</nbVal>"
       << "</nciBeta>"
       << "<mo_nciMaxPotentialSurvival>"
       << "<mo_nmpsVal species=\"Species_1\">0.99</mo_nmpsVal>"
       << "<mo_nmpsVal species=\"Species_2\">0.99</mo_nmpsVal>"
       << "</mo_nciMaxPotentialSurvival>"
       << "<nciCrowdingGamma>"
       << "<ncgVal species=\"Species_1\">0.43</ncgVal>"
       << "<ncgVal species=\"Species_2\">0.43</ncgVal>"
       << "</nciCrowdingGamma>"
       << "<nciSizeEffectX0>"
       << "<nsex0Val species=\"Species_1\">34.2</nsex0Val>"
       << "<nsex0Val species=\"Species_2\">34.2</nsex0Val>"
       << "</nciSizeEffectX0>"
       << "<nciSizeEffectXb>"
       << "<nsexbVal species=\"Species_1\">5</nsexbVal>"
       << "<nsexbVal species=\"Species_2\">5</nsexbVal>"
       << "</nciSizeEffectXb>"
       << "<nciCrowdingC>"
       << "<nccVal species=\"Species_1\">1.98</nccVal>"
       << "<nccVal species=\"Species_2\">1.98</nccVal>"
       << "</nciCrowdingC>"
       << "<nciCrowdingD>"
       << "<ncdVal species=\"Species_1\">1.63</ncdVal>"
       << "<ncdVal species=\"Species_2\">1.63</ncdVal>"
       << "</nciCrowdingD>"
       << "<nciStormEffMedDmg>"
       << "<nsemdVal species=\"Species_1\">0.9</nsemdVal>"
       << "<nsemdVal species=\"Species_2\">0.9</nsemdVal>"
       << "</nciStormEffMedDmg>"
       << "<nciStormEffFullDmg>"
       << "<nsefdVal species=\"Species_1\">0.42</nsefdVal>"
       << "<nsefdVal species=\"Species_2\">0.42</nsefdVal>"
       << "</nciStormEffFullDmg>"
       << "<nciNeighStormEffMedDmg>"
       << "<nnsemdVal species=\"Species_1\">0.33</nnsemdVal>"
       << "<nnsemdVal species=\"Species_2\">0.33</nnsemdVal>"
       << "</nciNeighStormEffMedDmg>"
       << "<nciNeighStormEffFullDmg>"
       << "<nnsefdVal species=\"Species_1\">0.54</nnsefdVal>"
       << "<nnsefdVal species=\"Species_2\">0.54</nnsefdVal>"
       << "</nciNeighStormEffFullDmg>"
       << "<nciSpecies_1NeighborLambda>"
       << "<nlVal species=\"Species_1\">0.66401082</nlVal>"
       << "<nlVal species=\"Species_2\">0.71</nlVal>"
       << "</nciSpecies_1NeighborLambda>"
       << "<nciSpecies_2NeighborLambda>"
       << "<nlVal species=\"Species_1\">0.00442797</nlVal>"
       << "<nlVal species=\"Species_2\">0.12</nlVal>"
       << "</nciSpecies_2NeighborLambda>"
       << "<nciShadingCoefficient>"
       << "<nscVal species=\"Species_1\">0</nscVal>"
       << "<nscVal species=\"Species_2\">0</nscVal>"
       << "</nciShadingCoefficient>"
       << "<nciShadingExponent>"
       << "<nseVal species=\"Species_1\">1</nseVal>"
       << "<nseVal species=\"Species_2\">1</nseVal>"
       << "</nciShadingExponent>"
       << "<nciMinNeighborDBH>"
       << "<nmndVal species=\"Species_1\">0</nmndVal>"
       << "<nmndVal species=\"Species_2\">0</nmndVal>"
       << "</nciMinNeighborDBH>"
       << "<nciDbhDivisor>100</nciDbhDivisor>"
       << "<nciIncludeSnagsInNCI>0</nciIncludeSnagsInNCI>"
       << "</NCIMasterMortality3>"
       << "</paramFile>";


  oOut.close();

  return cFileString;
}



////////////////////////////////////////////////////////////////////////////
// WriteNCIMortXMLErrorFile2()
////////////////////////////////////////////////////////////////////////////
const char* WriteNCIMortXMLErrorFile2() {
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

  WriteNCIMortCommonErrorStuff(oOut);

  oOut << "<NCIMasterMortality3>"
       << "<nciWhichShadingEffect>0</nciWhichShadingEffect>"
       << "<nciWhichCrowdingEffect>" << default_crowding_effect << "</nciWhichCrowdingEffect>"
       << "<nciWhichNCITerm>2</nciWhichNCITerm>"
       << "<nciWhichSizeEffect>" << default_size_effect << "</nciWhichSizeEffect>"
       << "<nciWhichDamageEffect>" << default_damage_effect << "</nciWhichDamageEffect>"
       << "<nciWhichPrecipitationEffect>" << no_precip_effect << "</nciWhichPrecipitationEffect>"
       << "<nciWhichTemperatureEffect>" << no_temp_effect << "</nciWhichTemperatureEffect>"
       << "<nciWhichNitrogenEffect>" << no_nitrogen_effect << "</nciWhichNitrogenEffect>"
       << "<nciWhichInfectionEffect>" << no_infection_effect << "</nciWhichInfectionEffect>"
       << "<mo_nciMortSurvPeriod>1</mo_nciMortSurvPeriod>"
       << "<nciMaxCrowdingRadius>"
       << "<nmcrVal species=\"Species_1\">10</nmcrVal>"
       << "<nmcrVal species=\"Species_2\">10</nmcrVal>"
       << "</nciMaxCrowdingRadius>"
       << "<nciAlpha>"
       << "<naVal species=\"Species_1\">2.81</naVal>"
       << "<naVal species=\"Species_2\">2.81</naVal>"
       << "</nciAlpha>"
       << "<nciBeta>"
       << "<nbVal species=\"Species_1\">0.5</nbVal>"
       << "<nbVal species=\"Species_2\">0.5</nbVal>"
       << "</nciBeta>"
       << "<mo_nciMaxPotentialSurvival>"
       << "<mo_nmpsVal species=\"Species_1\">0.99</mo_nmpsVal>"
       << "<mo_nmpsVal species=\"Species_2\">-0.99</mo_nmpsVal>"
       << "</mo_nciMaxPotentialSurvival>"
       << "<nciCrowdingGamma>"
       << "<ncgVal species=\"Species_1\">0.43</ncgVal>"
       << "<ncgVal species=\"Species_2\">0.43</ncgVal>"
       << "</nciCrowdingGamma>"
       << "<nciSizeEffectX0>"
       << "<nsex0Val species=\"Species_1\">34.2</nsex0Val>"
       << "<nsex0Val species=\"Species_2\">34.2</nsex0Val>"
       << "</nciSizeEffectX0>"
       << "<nciSizeEffectXb>"
       << "<nsexbVal species=\"Species_1\">5</nsexbVal>"
       << "<nsexbVal species=\"Species_2\">5</nsexbVal>"
       << "</nciSizeEffectXb>"
       << "<nciCrowdingC>"
       << "<nccVal species=\"Species_1\">1.98</nccVal>"
       << "<nccVal species=\"Species_2\">1.98</nccVal>"
       << "</nciCrowdingC>"
       << "<nciCrowdingD>"
       << "<ncdVal species=\"Species_1\">1.63</ncdVal>"
       << "<ncdVal species=\"Species_2\">1.63</ncdVal>"
       << "</nciCrowdingD>"
       << "<nciStormEffMedDmg>"
       << "<nsemdVal species=\"Species_1\">0.9</nsemdVal>"
       << "<nsemdVal species=\"Species_2\">0.9</nsemdVal>"
       << "</nciStormEffMedDmg>"
       << "<nciStormEffFullDmg>"
       << "<nsefdVal species=\"Species_1\">0.42</nsefdVal>"
       << "<nsefdVal species=\"Species_2\">0.42</nsefdVal>"
       << "</nciStormEffFullDmg>"
       << "<nciNeighStormEffMedDmg>"
       << "<nnsemdVal species=\"Species_1\">0.33</nnsemdVal>"
       << "<nnsemdVal species=\"Species_2\">0.33</nnsemdVal>"
       << "</nciNeighStormEffMedDmg>"
       << "<nciNeighStormEffFullDmg>"
       << "<nnsefdVal species=\"Species_1\">0.54</nnsefdVal>"
       << "<nnsefdVal species=\"Species_2\">0.54</nnsefdVal>"
       << "</nciNeighStormEffFullDmg>"
       << "<nciSpecies_1NeighborLambda>"
       << "<nlVal species=\"Species_1\">0.66401082</nlVal>"
       << "<nlVal species=\"Species_2\">0.71</nlVal>"
       << "</nciSpecies_1NeighborLambda>"
       << "<nciSpecies_2NeighborLambda>"
       << "<nlVal species=\"Species_1\">0.00442797</nlVal>"
       << "<nlVal species=\"Species_2\">0.12</nlVal>"
       << "</nciSpecies_2NeighborLambda>"
       << "<nciShadingCoefficient>"
       << "<nscVal species=\"Species_1\">0</nscVal>"
       << "<nscVal species=\"Species_2\">0</nscVal>"
       << "</nciShadingCoefficient>"
       << "<nciShadingExponent>"
       << "<nseVal species=\"Species_1\">1</nseVal>"
       << "<nseVal species=\"Species_2\">1</nseVal>"
       << "</nciShadingExponent>"
       << "<nciMinNeighborDBH>"
       << "<nmndVal species=\"Species_1\">0</nmndVal>"
       << "<nmndVal species=\"Species_2\">0</nmndVal>"
       << "</nciMinNeighborDBH>"
       << "<nciDbhDivisor>100</nciDbhDivisor>"
       << "<nciIncludeSnagsInNCI>0</nciIncludeSnagsInNCI>"
       << "</NCIMasterMortality3>"
       << "</paramFile>";


  oOut.close();

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteNCIMortXMLErrorFile3()
////////////////////////////////////////////////////////////////////////////
const char* WriteNCIMortXMLErrorFile3() {
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

  WriteNCIMortCommonErrorStuff(oOut);

  oOut << "<NCIMasterMortality3>"
       << "<nciWhichShadingEffect>0</nciWhichShadingEffect>"
       << "<nciWhichCrowdingEffect>" << default_crowding_effect << "</nciWhichCrowdingEffect>"
       << "<nciWhichNCITerm>2</nciWhichNCITerm>"
       << "<nciWhichSizeEffect>" << default_size_effect << "</nciWhichSizeEffect>"
       << "<nciWhichDamageEffect>" << default_damage_effect << "</nciWhichDamageEffect>"
       << "<nciWhichPrecipitationEffect>" << no_precip_effect << "</nciWhichPrecipitationEffect>"
       << "<nciWhichTemperatureEffect>" << no_temp_effect << "</nciWhichTemperatureEffect>"
       << "<nciWhichNitrogenEffect>" << no_nitrogen_effect << "</nciWhichNitrogenEffect>"
       << "<nciWhichInfectionEffect>" << no_infection_effect << "</nciWhichInfectionEffect>"
       << "<mo_nciMortSurvPeriod>1</mo_nciMortSurvPeriod>"
       << "<nciMaxCrowdingRadius>"
       << "<nmcrVal species=\"Species_1\">10</nmcrVal>"
       << "<nmcrVal species=\"Species_2\">10</nmcrVal>"
       << "</nciMaxCrowdingRadius>"
       << "<nciAlpha>"
       << "<naVal species=\"Species_1\">2.81</naVal>"
       << "<naVal species=\"Species_2\">2.81</naVal>"
       << "</nciAlpha>"
       << "<nciBeta>"
       << "<nbVal species=\"Species_1\">0.5</nbVal>"
       << "<nbVal species=\"Species_2\">0.5</nbVal>"
       << "</nciBeta>"
       << "<mo_nciMaxPotentialSurvival>"
       << "<mo_nmpsVal species=\"Species_1\">0.99</mo_nmpsVal>"
       << "<mo_nmpsVal species=\"Species_2\">0.99</mo_nmpsVal>"
       << "</mo_nciMaxPotentialSurvival>"
       << "<nciCrowdingGamma>"
       << "<ncgVal species=\"Species_1\">0.43</ncgVal>"
       << "<ncgVal species=\"Species_2\">0.43</ncgVal>"
       << "</nciCrowdingGamma>"
       << "<nciSizeEffectX0>"
       << "<nsex0Val species=\"Species_1\">34.2</nsex0Val>"
       << "<nsex0Val species=\"Species_2\">34.2</nsex0Val>"
       << "</nciSizeEffectX0>"
       << "<nciSizeEffectXb>"
       << "<nsexbVal species=\"Species_1\">0</nsexbVal>"
       << "<nsexbVal species=\"Species_2\">5</nsexbVal>"
       << "</nciSizeEffectXb>"
       << "<nciCrowdingC>"
       << "<nccVal species=\"Species_1\">1.98</nccVal>"
       << "<nccVal species=\"Species_2\">1.98</nccVal>"
       << "</nciCrowdingC>"
       << "<nciCrowdingD>"
       << "<ncdVal species=\"Species_1\">1.63</ncdVal>"
       << "<ncdVal species=\"Species_2\">1.63</ncdVal>"
       << "</nciCrowdingD>"
       << "<nciStormEffMedDmg>"
       << "<nsemdVal species=\"Species_1\">0.9</nsemdVal>"
       << "<nsemdVal species=\"Species_2\">0.9</nsemdVal>"
       << "</nciStormEffMedDmg>"
       << "<nciStormEffFullDmg>"
       << "<nsefdVal species=\"Species_1\">0.42</nsefdVal>"
       << "<nsefdVal species=\"Species_2\">0.42</nsefdVal>"
       << "</nciStormEffFullDmg>"
       << "<nciNeighStormEffMedDmg>"
       << "<nnsemdVal species=\"Species_1\">0.33</nnsemdVal>"
       << "<nnsemdVal species=\"Species_2\">0.33</nnsemdVal>"
       << "</nciNeighStormEffMedDmg>"
       << "<nciNeighStormEffFullDmg>"
       << "<nnsefdVal species=\"Species_1\">0.54</nnsefdVal>"
       << "<nnsefdVal species=\"Species_2\">0.54</nnsefdVal>"
       << "</nciNeighStormEffFullDmg>"
       << "<nciSpecies_1NeighborLambda>"
       << "<nlVal species=\"Species_1\">0.66401082</nlVal>"
       << "<nlVal species=\"Species_2\">0.71</nlVal>"
       << "</nciSpecies_1NeighborLambda>"
       << "<nciSpecies_2NeighborLambda>"
       << "<nlVal species=\"Species_1\">0.00442797</nlVal>"
       << "<nlVal species=\"Species_2\">0.12</nlVal>"
       << "</nciSpecies_2NeighborLambda>"
       << "<nciShadingCoefficient>"
       << "<nscVal species=\"Species_1\">0</nscVal>"
       << "<nscVal species=\"Species_2\">0</nscVal>"
       << "</nciShadingCoefficient>"
       << "<nciShadingExponent>"
       << "<nseVal species=\"Species_1\">1</nseVal>"
       << "<nseVal species=\"Species_2\">1</nseVal>"
       << "</nciShadingExponent>"
       << "<nciMinNeighborDBH>"
       << "<nmndVal species=\"Species_1\">0</nmndVal>"
       << "<nmndVal species=\"Species_2\">0</nmndVal>"
       << "</nciMinNeighborDBH>"
       << "<nciDbhDivisor>100</nciDbhDivisor>"
       << "<nciIncludeSnagsInNCI>0</nciIncludeSnagsInNCI>"
       << "</NCIMasterMortality3>"
       << "</paramFile>";


  oOut.close();

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteNCIMortXMLErrorFile4()
////////////////////////////////////////////////////////////////////////////
const char* WriteNCIMortXMLErrorFile4() {
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

  WriteNCIMortCommonErrorStuff(oOut);

  oOut << "<NCIMasterMortality3>"
       << "<nciWhichShadingEffect>0</nciWhichShadingEffect>"
       << "<nciWhichCrowdingEffect>" << default_crowding_effect << "</nciWhichCrowdingEffect>"
       << "<nciWhichNCITerm>2</nciWhichNCITerm>"
       << "<nciWhichSizeEffect>" << default_size_effect << "</nciWhichSizeEffect>"
       << "<nciWhichDamageEffect>" << default_damage_effect << "</nciWhichDamageEffect>"
       << "<nciWhichPrecipitationEffect>" << no_precip_effect << "</nciWhichPrecipitationEffect>"
       << "<nciWhichTemperatureEffect>" << no_temp_effect << "</nciWhichTemperatureEffect>"
       << "<nciWhichNitrogenEffect>" << no_nitrogen_effect << "</nciWhichNitrogenEffect>"
       << "<nciWhichInfectionEffect>" << no_infection_effect << "</nciWhichInfectionEffect>"
       << "<mo_nciMortSurvPeriod>1</mo_nciMortSurvPeriod>"
       << "<nciMaxCrowdingRadius>"
       << "<nmcrVal species=\"Species_1\">10</nmcrVal>"
       << "<nmcrVal species=\"Species_2\">10</nmcrVal>"
       << "</nciMaxCrowdingRadius>"
       << "<nciAlpha>"
       << "<naVal species=\"Species_1\">2.81</naVal>"
       << "<naVal species=\"Species_2\">2.81</naVal>"
       << "</nciAlpha>"
       << "<nciBeta>"
       << "<nbVal species=\"Species_1\">0.5</nbVal>"
       << "<nbVal species=\"Species_2\">0.5</nbVal>"
       << "</nciBeta>"
       << "<mo_nciMaxPotentialSurvival>"
       << "<mo_nmpsVal species=\"Species_1\">0.99</mo_nmpsVal>"
       << "<mo_nmpsVal species=\"Species_2\">0.99</mo_nmpsVal>"
       << "</mo_nciMaxPotentialSurvival>"
       << "<nciCrowdingGamma>"
       << "<ncgVal species=\"Species_1\">0.43</ncgVal>"
       << "<ncgVal species=\"Species_2\">0.43</ncgVal>"
       << "</nciCrowdingGamma>"
       << "<nciSizeEffectX0>"
       << "<nsex0Val species=\"Species_1\">0</nsex0Val>"
       << "<nsex0Val species=\"Species_2\">34.2</nsex0Val>"
       << "</nciSizeEffectX0>"
       << "<nciSizeEffectXb>"
       << "<nsexbVal species=\"Species_1\">5</nsexbVal>"
       << "<nsexbVal species=\"Species_2\">5</nsexbVal>"
       << "</nciSizeEffectXb>"
       << "<nciCrowdingC>"
       << "<nccVal species=\"Species_1\">1.98</nccVal>"
       << "<nccVal species=\"Species_2\">1.98</nccVal>"
       << "</nciCrowdingC>"
       << "<nciCrowdingD>"
       << "<ncdVal species=\"Species_1\">1.63</ncdVal>"
       << "<ncdVal species=\"Species_2\">1.63</ncdVal>"
       << "</nciCrowdingD>"
       << "<nciStormEffMedDmg>"
       << "<nsemdVal species=\"Species_1\">0.9</nsemdVal>"
       << "<nsemdVal species=\"Species_2\">0.9</nsemdVal>"
       << "</nciStormEffMedDmg>"
       << "<nciStormEffFullDmg>"
       << "<nsefdVal species=\"Species_1\">0.42</nsefdVal>"
       << "<nsefdVal species=\"Species_2\">0.42</nsefdVal>"
       << "</nciStormEffFullDmg>"
       << "<nciNeighStormEffMedDmg>"
       << "<nnsemdVal species=\"Species_1\">0.33</nnsemdVal>"
       << "<nnsemdVal species=\"Species_2\">0.33</nnsemdVal>"
       << "</nciNeighStormEffMedDmg>"
       << "<nciNeighStormEffFullDmg>"
       << "<nnsefdVal species=\"Species_1\">0.54</nnsefdVal>"
       << "<nnsefdVal species=\"Species_2\">0.54</nnsefdVal>"
       << "</nciNeighStormEffFullDmg>"
       << "<nciSpecies_1NeighborLambda>"
       << "<nlVal species=\"Species_1\">0.66401082</nlVal>"
       << "<nlVal species=\"Species_2\">0.71</nlVal>"
       << "</nciSpecies_1NeighborLambda>"
       << "<nciSpecies_2NeighborLambda>"
       << "<nlVal species=\"Species_1\">0.00442797</nlVal>"
       << "<nlVal species=\"Species_2\">0.12</nlVal>"
       << "</nciSpecies_2NeighborLambda>"
       << "<nciShadingCoefficient>"
       << "<nscVal species=\"Species_1\">0</nscVal>"
       << "<nscVal species=\"Species_2\">0</nscVal>"
       << "</nciShadingCoefficient>"
       << "<nciShadingExponent>"
       << "<nseVal species=\"Species_1\">1</nseVal>"
       << "<nseVal species=\"Species_2\">1</nseVal>"
       << "</nciShadingExponent>"
       << "<nciMinNeighborDBH>"
       << "<nmndVal species=\"Species_1\">0</nmndVal>"
       << "<nmndVal species=\"Species_2\">0</nmndVal>"
       << "</nciMinNeighborDBH>"
       << "<nciDbhDivisor>100</nciDbhDivisor>"
       << "<nciIncludeSnagsInNCI>0</nciIncludeSnagsInNCI>"
       << "</NCIMasterMortality3>"
       << "</paramFile>";


  oOut.close();

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteNCIMortXMLErrorFile5()
////////////////////////////////////////////////////////////////////////////
const char* WriteNCIMortXMLErrorFile5() {
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

  WriteNCIMortCommonErrorStuff(oOut);

  oOut << "<NCIMasterMortality3>"
       << "<nciWhichShadingEffect>0</nciWhichShadingEffect>"
       << "<nciWhichCrowdingEffect>" << default_crowding_effect << "</nciWhichCrowdingEffect>"
       << "<nciWhichNCITerm>2</nciWhichNCITerm>"
       << "<nciWhichSizeEffect>" << default_size_effect << "</nciWhichSizeEffect>"
       << "<nciWhichDamageEffect>" << default_damage_effect << "</nciWhichDamageEffect>"
       << "<nciWhichPrecipitationEffect>" << no_precip_effect << "</nciWhichPrecipitationEffect>"
       << "<nciWhichTemperatureEffect>" << no_temp_effect << "</nciWhichTemperatureEffect>"
       << "<nciWhichNitrogenEffect>" << no_nitrogen_effect << "</nciWhichNitrogenEffect>"
       << "<nciWhichInfectionEffect>" << no_infection_effect << "</nciWhichInfectionEffect>"
       << "<mo_nciMortSurvPeriod>1</mo_nciMortSurvPeriod>"
       << "<nciMaxCrowdingRadius>"
       << "<nmcrVal species=\"Species_1\">10</nmcrVal>"
       << "<nmcrVal species=\"Species_2\">10</nmcrVal>"
       << "</nciMaxCrowdingRadius>"
       << "<nciAlpha>"
       << "<naVal species=\"Species_1\">2.81</naVal>"
       << "<naVal species=\"Species_2\">2.81</naVal>"
       << "</nciAlpha>"
       << "<nciBeta>"
       << "<nbVal species=\"Species_1\">0.5</nbVal>"
       << "<nbVal species=\"Species_2\">0.5</nbVal>"
       << "</nciBeta>"
       << "<mo_nciMaxPotentialSurvival>"
       << "<mo_nmpsVal species=\"Species_1\">0.99</mo_nmpsVal>"
       << "<mo_nmpsVal species=\"Species_2\">0.99</mo_nmpsVal>"
       << "</mo_nciMaxPotentialSurvival>"
       << "<nciCrowdingGamma>"
       << "<ncgVal species=\"Species_1\">0.43</ncgVal>"
       << "<ncgVal species=\"Species_2\">0.43</ncgVal>"
       << "</nciCrowdingGamma>"
       << "<nciSizeEffectX0>"
       << "<nsex0Val species=\"Species_1\">34.2</nsex0Val>"
       << "<nsex0Val species=\"Species_2\">34.2</nsex0Val>"
       << "</nciSizeEffectX0>"
       << "<nciSizeEffectXb>"
       << "<nsexbVal species=\"Species_1\">5</nsexbVal>"
       << "<nsexbVal species=\"Species_2\">5</nsexbVal>"
       << "</nciSizeEffectXb>"
       << "<nciCrowdingC>"
       << "<nccVal species=\"Species_1\">1.98</nccVal>"
       << "<nccVal species=\"Species_2\">1.98</nccVal>"
       << "</nciCrowdingC>"
       << "<nciCrowdingD>"
       << "<ncdVal species=\"Species_1\">1.63</ncdVal>"
       << "<ncdVal species=\"Species_2\">1.63</ncdVal>"
       << "</nciCrowdingD>"
       << "<nciStormEffMedDmg>"
       << "<nsemdVal species=\"Species_1\">0.9</nsemdVal>"
       << "<nsemdVal species=\"Species_2\">0.9</nsemdVal>"
       << "</nciStormEffMedDmg>"
       << "<nciStormEffFullDmg>"
       << "<nsefdVal species=\"Species_1\">0.42</nsefdVal>"
       << "<nsefdVal species=\"Species_2\">0.42</nsefdVal>"
       << "</nciStormEffFullDmg>"
       << "<nciNeighStormEffMedDmg>"
       << "<nnsemdVal species=\"Species_1\">-0.33</nnsemdVal>"
       << "<nnsemdVal species=\"Species_2\">0.33</nnsemdVal>"
       << "</nciNeighStormEffMedDmg>"
       << "<nciNeighStormEffFullDmg>"
       << "<nnsefdVal species=\"Species_1\">0.54</nnsefdVal>"
       << "<nnsefdVal species=\"Species_2\">0.54</nnsefdVal>"
       << "</nciNeighStormEffFullDmg>"
       << "<nciSpecies_1NeighborLambda>"
       << "<nlVal species=\"Species_1\">0.66401082</nlVal>"
       << "<nlVal species=\"Species_2\">0.71</nlVal>"
       << "</nciSpecies_1NeighborLambda>"
       << "<nciSpecies_2NeighborLambda>"
       << "<nlVal species=\"Species_1\">0.00442797</nlVal>"
       << "<nlVal species=\"Species_2\">0.12</nlVal>"
       << "</nciSpecies_2NeighborLambda>"
       << "<nciShadingCoefficient>"
       << "<nscVal species=\"Species_1\">0</nscVal>"
       << "<nscVal species=\"Species_2\">0</nscVal>"
       << "</nciShadingCoefficient>"
       << "<nciShadingExponent>"
       << "<nseVal species=\"Species_1\">1</nseVal>"
       << "<nseVal species=\"Species_2\">1</nseVal>"
       << "</nciShadingExponent>"
       << "<nciMinNeighborDBH>"
       << "<nmndVal species=\"Species_1\">0</nmndVal>"
       << "<nmndVal species=\"Species_2\">0</nmndVal>"
       << "</nciMinNeighborDBH>"
       << "<nciDbhDivisor>100</nciDbhDivisor>"
       << "<nciIncludeSnagsInNCI>0</nciIncludeSnagsInNCI>"
       << "</NCIMasterMortality3>"
       << "</paramFile>";


  oOut.close();

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteNCIMortXMLErrorFile6()
////////////////////////////////////////////////////////////////////////////
const char* WriteNCIMortXMLErrorFile6() {
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

  WriteNCIMortCommonErrorStuff(oOut);

  oOut << "<NCIMasterMortality3>"
       << "<nciWhichShadingEffect>0</nciWhichShadingEffect>"
       << "<nciWhichCrowdingEffect>" << default_crowding_effect << "</nciWhichCrowdingEffect>"
       << "<nciWhichNCITerm>2</nciWhichNCITerm>"
       << "<nciWhichSizeEffect>" << default_size_effect << "</nciWhichSizeEffect>"
       << "<nciWhichDamageEffect>" << default_damage_effect << "</nciWhichDamageEffect>"
       << "<nciWhichPrecipitationEffect>" << no_precip_effect << "</nciWhichPrecipitationEffect>"
       << "<nciWhichTemperatureEffect>" << no_temp_effect << "</nciWhichTemperatureEffect>"
       << "<nciWhichNitrogenEffect>" << no_nitrogen_effect << "</nciWhichNitrogenEffect>"
       << "<nciWhichInfectionEffect>" << no_infection_effect << "</nciWhichInfectionEffect>"
       << "<mo_nciMortSurvPeriod>1</mo_nciMortSurvPeriod>"
       << "<nciMaxCrowdingRadius>"
       << "<nmcrVal species=\"Species_1\">10</nmcrVal>"
       << "<nmcrVal species=\"Species_2\">10</nmcrVal>"
       << "</nciMaxCrowdingRadius>"
       << "<nciAlpha>"
       << "<naVal species=\"Species_1\">2.81</naVal>"
       << "<naVal species=\"Species_2\">2.81</naVal>"
       << "</nciAlpha>"
       << "<nciBeta>"
       << "<nbVal species=\"Species_1\">0.5</nbVal>"
       << "<nbVal species=\"Species_2\">0.5</nbVal>"
       << "</nciBeta>"
       << "<mo_nciMaxPotentialSurvival>"
       << "<mo_nmpsVal species=\"Species_1\">0.99</mo_nmpsVal>"
       << "<mo_nmpsVal species=\"Species_2\">0.99</mo_nmpsVal>"
       << "</mo_nciMaxPotentialSurvival>"
       << "<nciCrowdingGamma>"
       << "<ncgVal species=\"Species_1\">0.43</ncgVal>"
       << "<ncgVal species=\"Species_2\">0.43</ncgVal>"
       << "</nciCrowdingGamma>"
       << "<nciSizeEffectX0>"
       << "<nsex0Val species=\"Species_1\">34.2</nsex0Val>"
       << "<nsex0Val species=\"Species_2\">34.2</nsex0Val>"
       << "</nciSizeEffectX0>"
       << "<nciSizeEffectXb>"
       << "<nsexbVal species=\"Species_1\">5</nsexbVal>"
       << "<nsexbVal species=\"Species_2\">5</nsexbVal>"
       << "</nciSizeEffectXb>"
       << "<nciCrowdingC>"
       << "<nccVal species=\"Species_1\">1.98</nccVal>"
       << "<nccVal species=\"Species_2\">1.98</nccVal>"
       << "</nciCrowdingC>"
       << "<nciCrowdingD>"
       << "<ncdVal species=\"Species_1\">1.63</ncdVal>"
       << "<ncdVal species=\"Species_2\">1.63</ncdVal>"
       << "</nciCrowdingD>"
       << "<nciStormEffMedDmg>"
       << "<nsemdVal species=\"Species_1\">0.9</nsemdVal>"
       << "<nsemdVal species=\"Species_2\">0.9</nsemdVal>"
       << "</nciStormEffMedDmg>"
       << "<nciStormEffFullDmg>"
       << "<nsefdVal species=\"Species_1\">0.42</nsefdVal>"
       << "<nsefdVal species=\"Species_2\">0.42</nsefdVal>"
       << "</nciStormEffFullDmg>"
       << "<nciNeighStormEffMedDmg>"
       << "<nnsemdVal species=\"Species_1\">0.33</nnsemdVal>"
       << "<nnsemdVal species=\"Species_2\">1.33</nnsemdVal>"
       << "</nciNeighStormEffMedDmg>"
       << "<nciNeighStormEffFullDmg>"
       << "<nnsefdVal species=\"Species_1\">0.54</nnsefdVal>"
       << "<nnsefdVal species=\"Species_2\">0.54</nnsefdVal>"
       << "</nciNeighStormEffFullDmg>"
       << "<nciSpecies_1NeighborLambda>"
       << "<nlVal species=\"Species_1\">0.66401082</nlVal>"
       << "<nlVal species=\"Species_2\">0.71</nlVal>"
       << "</nciSpecies_1NeighborLambda>"
       << "<nciSpecies_2NeighborLambda>"
       << "<nlVal species=\"Species_1\">0.00442797</nlVal>"
       << "<nlVal species=\"Species_2\">0.12</nlVal>"
       << "</nciSpecies_2NeighborLambda>"
       << "<nciShadingCoefficient>"
       << "<nscVal species=\"Species_1\">0</nscVal>"
       << "<nscVal species=\"Species_2\">0</nscVal>"
       << "</nciShadingCoefficient>"
       << "<nciShadingExponent>"
       << "<nseVal species=\"Species_1\">1</nseVal>"
       << "<nseVal species=\"Species_2\">1</nseVal>"
       << "</nciShadingExponent>"
       << "<nciMinNeighborDBH>"
       << "<nmndVal species=\"Species_1\">0</nmndVal>"
       << "<nmndVal species=\"Species_2\">0</nmndVal>"
       << "</nciMinNeighborDBH>"
       << "<nciDbhDivisor>100</nciDbhDivisor>"
       << "<nciIncludeSnagsInNCI>0</nciIncludeSnagsInNCI>"
       << "</NCIMasterMortality3>"
       << "</paramFile>";


  oOut.close();

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteNCIMortXMLErrorFile7()
////////////////////////////////////////////////////////////////////////////
const char* WriteNCIMortXMLErrorFile7() {
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

  WriteNCIMortCommonErrorStuff(oOut);

  oOut << "<NCIMasterMortality3>"
       << "<nciWhichShadingEffect>0</nciWhichShadingEffect>"
       << "<nciWhichCrowdingEffect>" << default_crowding_effect << "</nciWhichCrowdingEffect>"
       << "<nciWhichNCITerm>2</nciWhichNCITerm>"
       << "<nciWhichSizeEffect>" << default_size_effect << "</nciWhichSizeEffect>"
       << "<nciWhichDamageEffect>" << default_damage_effect << "</nciWhichDamageEffect>"
       << "<nciWhichPrecipitationEffect>" << no_precip_effect << "</nciWhichPrecipitationEffect>"
       << "<nciWhichTemperatureEffect>" << no_temp_effect << "</nciWhichTemperatureEffect>"
       << "<nciWhichNitrogenEffect>" << no_nitrogen_effect << "</nciWhichNitrogenEffect>"
       << "<nciWhichInfectionEffect>" << no_infection_effect << "</nciWhichInfectionEffect>"
       << "<mo_nciMortSurvPeriod>1</mo_nciMortSurvPeriod>"
       << "<nciMaxCrowdingRadius>"
       << "<nmcrVal species=\"Species_1\">10</nmcrVal>"
       << "<nmcrVal species=\"Species_2\">10</nmcrVal>"
       << "</nciMaxCrowdingRadius>"
       << "<nciAlpha>"
       << "<naVal species=\"Species_1\">2.81</naVal>"
       << "<naVal species=\"Species_2\">2.81</naVal>"
       << "</nciAlpha>"
       << "<nciBeta>"
       << "<nbVal species=\"Species_1\">0.5</nbVal>"
       << "<nbVal species=\"Species_2\">0.5</nbVal>"
       << "</nciBeta>"
       << "<mo_nciMaxPotentialSurvival>"
       << "<mo_nmpsVal species=\"Species_1\">0.99</mo_nmpsVal>"
       << "<mo_nmpsVal species=\"Species_2\">0.99</mo_nmpsVal>"
       << "</mo_nciMaxPotentialSurvival>"
       << "<nciCrowdingGamma>"
       << "<ncgVal species=\"Species_1\">0.43</ncgVal>"
       << "<ncgVal species=\"Species_2\">0.43</ncgVal>"
       << "</nciCrowdingGamma>"
       << "<nciSizeEffectX0>"
       << "<nsex0Val species=\"Species_1\">34.2</nsex0Val>"
       << "<nsex0Val species=\"Species_2\">34.2</nsex0Val>"
       << "</nciSizeEffectX0>"
       << "<nciSizeEffectXb>"
       << "<nsexbVal species=\"Species_1\">5</nsexbVal>"
       << "<nsexbVal species=\"Species_2\">5</nsexbVal>"
       << "</nciSizeEffectXb>"
       << "<nciCrowdingC>"
       << "<nccVal species=\"Species_1\">1.98</nccVal>"
       << "<nccVal species=\"Species_2\">1.98</nccVal>"
       << "</nciCrowdingC>"
       << "<nciCrowdingD>"
       << "<ncdVal species=\"Species_1\">1.63</ncdVal>"
       << "<ncdVal species=\"Species_2\">1.63</ncdVal>"
       << "</nciCrowdingD>"
       << "<nciStormEffMedDmg>"
       << "<nsemdVal species=\"Species_1\">0.9</nsemdVal>"
       << "<nsemdVal species=\"Species_2\">0.9</nsemdVal>"
       << "</nciStormEffMedDmg>"
       << "<nciStormEffFullDmg>"
       << "<nsefdVal species=\"Species_1\">0.42</nsefdVal>"
       << "<nsefdVal species=\"Species_2\">0.42</nsefdVal>"
       << "</nciStormEffFullDmg>"
       << "<nciNeighStormEffMedDmg>"
       << "<nnsemdVal species=\"Species_1\">0.33</nnsemdVal>"
       << "<nnsemdVal species=\"Species_2\">0.33</nnsemdVal>"
       << "</nciNeighStormEffMedDmg>"
       << "<nciNeighStormEffFullDmg>"
       << "<nnsefdVal species=\"Species_1\">-0.54</nnsefdVal>"
       << "<nnsefdVal species=\"Species_2\">0.54</nnsefdVal>"
       << "</nciNeighStormEffFullDmg>"
       << "<nciSpecies_1NeighborLambda>"
       << "<nlVal species=\"Species_1\">0.66401082</nlVal>"
       << "<nlVal species=\"Species_2\">0.71</nlVal>"
       << "</nciSpecies_1NeighborLambda>"
       << "<nciSpecies_2NeighborLambda>"
       << "<nlVal species=\"Species_1\">0.00442797</nlVal>"
       << "<nlVal species=\"Species_2\">0.12</nlVal>"
       << "</nciSpecies_2NeighborLambda>"
       << "<nciShadingCoefficient>"
       << "<nscVal species=\"Species_1\">0</nscVal>"
       << "<nscVal species=\"Species_2\">0</nscVal>"
       << "</nciShadingCoefficient>"
       << "<nciShadingExponent>"
       << "<nseVal species=\"Species_1\">1</nseVal>"
       << "<nseVal species=\"Species_2\">1</nseVal>"
       << "</nciShadingExponent>"
       << "<nciMinNeighborDBH>"
       << "<nmndVal species=\"Species_1\">0</nmndVal>"
       << "<nmndVal species=\"Species_2\">0</nmndVal>"
       << "</nciMinNeighborDBH>"
       << "<nciDbhDivisor>100</nciDbhDivisor>"
       << "<nciIncludeSnagsInNCI>0</nciIncludeSnagsInNCI>"
       << "</NCIMasterMortality3>"
       << "</paramFile>";


  oOut.close();

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteNCIMortXMLErrorFile8()
////////////////////////////////////////////////////////////////////////////
const char* WriteNCIMortXMLErrorFile8() {
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

  WriteNCIMortCommonErrorStuff(oOut);

  oOut << "<NCIMasterMortality3>"
       << "<nciWhichShadingEffect>0</nciWhichShadingEffect>"
       << "<nciWhichCrowdingEffect>" << default_crowding_effect << "</nciWhichCrowdingEffect>"
       << "<nciWhichNCITerm>2</nciWhichNCITerm>"
       << "<nciWhichSizeEffect>" << default_size_effect << "</nciWhichSizeEffect>"
       << "<nciWhichDamageEffect>" << default_damage_effect << "</nciWhichDamageEffect>"
       << "<nciWhichPrecipitationEffect>" << no_precip_effect << "</nciWhichPrecipitationEffect>"
       << "<nciWhichTemperatureEffect>" << no_temp_effect << "</nciWhichTemperatureEffect>"
       << "<nciWhichNitrogenEffect>" << no_nitrogen_effect << "</nciWhichNitrogenEffect>"
       << "<nciWhichInfectionEffect>" << no_infection_effect << "</nciWhichInfectionEffect>"
       << "<mo_nciMortSurvPeriod>1</mo_nciMortSurvPeriod>"
       << "<nciMaxCrowdingRadius>"
       << "<nmcrVal species=\"Species_1\">10</nmcrVal>"
       << "<nmcrVal species=\"Species_2\">10</nmcrVal>"
       << "</nciMaxCrowdingRadius>"
       << "<nciAlpha>"
       << "<naVal species=\"Species_1\">2.81</naVal>"
       << "<naVal species=\"Species_2\">2.81</naVal>"
       << "</nciAlpha>"
       << "<nciBeta>"
       << "<nbVal species=\"Species_1\">0.5</nbVal>"
       << "<nbVal species=\"Species_2\">0.5</nbVal>"
       << "</nciBeta>"
       << "<mo_nciMaxPotentialSurvival>"
       << "<mo_nmpsVal species=\"Species_1\">0.99</mo_nmpsVal>"
       << "<mo_nmpsVal species=\"Species_2\">0.99</mo_nmpsVal>"
       << "</mo_nciMaxPotentialSurvival>"
       << "<nciCrowdingGamma>"
       << "<ncgVal species=\"Species_1\">0.43</ncgVal>"
       << "<ncgVal species=\"Species_2\">0.43</ncgVal>"
       << "</nciCrowdingGamma>"
       << "<nciSizeEffectX0>"
       << "<nsex0Val species=\"Species_1\">34.2</nsex0Val>"
       << "<nsex0Val species=\"Species_2\">34.2</nsex0Val>"
       << "</nciSizeEffectX0>"
       << "<nciSizeEffectXb>"
       << "<nsexbVal species=\"Species_1\">5</nsexbVal>"
       << "<nsexbVal species=\"Species_2\">5</nsexbVal>"
       << "</nciSizeEffectXb>"
       << "<nciCrowdingC>"
       << "<nccVal species=\"Species_1\">1.98</nccVal>"
       << "<nccVal species=\"Species_2\">1.98</nccVal>"
       << "</nciCrowdingC>"
       << "<nciCrowdingD>"
       << "<ncdVal species=\"Species_1\">1.63</ncdVal>"
       << "<ncdVal species=\"Species_2\">1.63</ncdVal>"
       << "</nciCrowdingD>"
       << "<nciStormEffMedDmg>"
       << "<nsemdVal species=\"Species_1\">0.9</nsemdVal>"
       << "<nsemdVal species=\"Species_2\">0.9</nsemdVal>"
       << "</nciStormEffMedDmg>"
       << "<nciStormEffFullDmg>"
       << "<nsefdVal species=\"Species_1\">0.42</nsefdVal>"
       << "<nsefdVal species=\"Species_2\">0.42</nsefdVal>"
       << "</nciStormEffFullDmg>"
       << "<nciNeighStormEffMedDmg>"
       << "<nnsemdVal species=\"Species_1\">0.33</nnsemdVal>"
       << "<nnsemdVal species=\"Species_2\">0.33</nnsemdVal>"
       << "</nciNeighStormEffMedDmg>"
       << "<nciNeighStormEffFullDmg>"
       << "<nnsefdVal species=\"Species_1\">0.54</nnsefdVal>"
       << "<nnsefdVal species=\"Species_2\">1.54</nnsefdVal>"
       << "</nciNeighStormEffFullDmg>"
       << "<nciSpecies_1NeighborLambda>"
       << "<nlVal species=\"Species_1\">0.66401082</nlVal>"
       << "<nlVal species=\"Species_2\">0.71</nlVal>"
       << "</nciSpecies_1NeighborLambda>"
       << "<nciSpecies_2NeighborLambda>"
       << "<nlVal species=\"Species_1\">0.00442797</nlVal>"
       << "<nlVal species=\"Species_2\">0.12</nlVal>"
       << "</nciSpecies_2NeighborLambda>"
       << "<nciShadingCoefficient>"
       << "<nscVal species=\"Species_1\">0</nscVal>"
       << "<nscVal species=\"Species_2\">0</nscVal>"
       << "</nciShadingCoefficient>"
       << "<nciShadingExponent>"
       << "<nseVal species=\"Species_1\">1</nseVal>"
       << "<nseVal species=\"Species_2\">1</nseVal>"
       << "</nciShadingExponent>"
       << "<nciMinNeighborDBH>"
       << "<nmndVal species=\"Species_1\">0</nmndVal>"
       << "<nmndVal species=\"Species_2\">0</nmndVal>"
       << "</nciMinNeighborDBH>"
       << "<nciDbhDivisor>100</nciDbhDivisor>"
       << "<nciIncludeSnagsInNCI>0</nciIncludeSnagsInNCI>"
       << "</NCIMasterMortality3>"
       << "</paramFile>";


  oOut.close();

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteNCIMortXMLErrorFile10()
////////////////////////////////////////////////////////////////////////////
const char* WriteNCIMortXMLErrorFile10() {
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

  WriteNCIMortCommonErrorStuff(oOut);

  oOut << "<NCIMasterMortality3>"
       << "<nciWhichShadingEffect>0</nciWhichShadingEffect>"
       << "<nciWhichCrowdingEffect>" << default_crowding_effect << "</nciWhichCrowdingEffect>"
       << "<nciWhichNCITerm>2</nciWhichNCITerm>"
       << "<nciWhichSizeEffect>" << default_size_effect << "</nciWhichSizeEffect>"
       << "<nciWhichDamageEffect>" << default_damage_effect << "</nciWhichDamageEffect>"
       << "<nciWhichPrecipitationEffect>" << no_precip_effect << "</nciWhichPrecipitationEffect>"
       << "<nciWhichTemperatureEffect>" << no_temp_effect << "</nciWhichTemperatureEffect>"
       << "<nciWhichNitrogenEffect>" << no_nitrogen_effect << "</nciWhichNitrogenEffect>"
       << "<nciWhichInfectionEffect>" << no_infection_effect << "</nciWhichInfectionEffect>"
       << "<mo_nciMortSurvPeriod>1</mo_nciMortSurvPeriod>"
       << "<nciMaxCrowdingRadius>"
       << "<nmcrVal species=\"Species_1\">10</nmcrVal>"
       << "<nmcrVal species=\"Species_2\">10</nmcrVal>"
       << "</nciMaxCrowdingRadius>"
       << "<nciAlpha>"
       << "<naVal species=\"Species_1\">2.81</naVal>"
       << "<naVal species=\"Species_2\">2.81</naVal>"
       << "</nciAlpha>"
       << "<nciBeta>"
       << "<nbVal species=\"Species_1\">0.5</nbVal>"
       << "<nbVal species=\"Species_2\">0.5</nbVal>"
       << "</nciBeta>"
       << "<mo_nciMaxPotentialSurvival>"
       << "<mo_nmpsVal species=\"Species_1\">0.99</mo_nmpsVal>"
       << "<mo_nmpsVal species=\"Species_2\">0.99</mo_nmpsVal>"
       << "</mo_nciMaxPotentialSurvival>"
       << "<nciCrowdingGamma>"
       << "<ncgVal species=\"Species_1\">0.43</ncgVal>"
       << "<ncgVal species=\"Species_2\">0.43</ncgVal>"
       << "</nciCrowdingGamma>"
       << "<nciSizeEffectX0>"
       << "<nsex0Val species=\"Species_1\">34.2</nsex0Val>"
       << "<nsex0Val species=\"Species_2\">34.2</nsex0Val>"
       << "</nciSizeEffectX0>"
       << "<nciSizeEffectXb>"
       << "<nsexbVal species=\"Species_1\">5</nsexbVal>"
       << "<nsexbVal species=\"Species_2\">5</nsexbVal>"
       << "</nciSizeEffectXb>"
       << "<nciCrowdingC>"
       << "<nccVal species=\"Species_1\">1.98</nccVal>"
       << "<nccVal species=\"Species_2\">1.98</nccVal>"
       << "</nciCrowdingC>"
       << "<nciCrowdingD>"
       << "<ncdVal species=\"Species_1\">1.63</ncdVal>"
       << "<ncdVal species=\"Species_2\">1.63</ncdVal>"
       << "</nciCrowdingD>"
       << "<nciStormEffMedDmg>"
       << "<nsemdVal species=\"Species_1\">0.9</nsemdVal>"
       << "<nsemdVal species=\"Species_2\">1.9</nsemdVal>"
       << "</nciStormEffMedDmg>"
       << "<nciStormEffFullDmg>"
       << "<nsefdVal species=\"Species_1\">0.42</nsefdVal>"
       << "<nsefdVal species=\"Species_2\">0.42</nsefdVal>"
       << "</nciStormEffFullDmg>"
       << "<nciNeighStormEffMedDmg>"
       << "<nnsemdVal species=\"Species_1\">0.33</nnsemdVal>"
       << "<nnsemdVal species=\"Species_2\">0.33</nnsemdVal>"
       << "</nciNeighStormEffMedDmg>"
       << "<nciNeighStormEffFullDmg>"
       << "<nnsefdVal species=\"Species_1\">0.54</nnsefdVal>"
       << "<nnsefdVal species=\"Species_2\">0.54</nnsefdVal>"
       << "</nciNeighStormEffFullDmg>"
       << "<nciSpecies_1NeighborLambda>"
       << "<nlVal species=\"Species_1\">0.66401082</nlVal>"
       << "<nlVal species=\"Species_2\">0.71</nlVal>"
       << "</nciSpecies_1NeighborLambda>"
       << "<nciSpecies_2NeighborLambda>"
       << "<nlVal species=\"Species_1\">0.00442797</nlVal>"
       << "<nlVal species=\"Species_2\">0.12</nlVal>"
       << "</nciSpecies_2NeighborLambda>"
       << "<nciShadingCoefficient>"
       << "<nscVal species=\"Species_1\">0</nscVal>"
       << "<nscVal species=\"Species_2\">0</nscVal>"
       << "</nciShadingCoefficient>"
       << "<nciShadingExponent>"
       << "<nseVal species=\"Species_1\">1</nseVal>"
       << "<nseVal species=\"Species_2\">1</nseVal>"
       << "</nciShadingExponent>"
       << "<nciMinNeighborDBH>"
       << "<nmndVal species=\"Species_1\">0</nmndVal>"
       << "<nmndVal species=\"Species_2\">0</nmndVal>"
       << "</nciMinNeighborDBH>"
       << "<nciDbhDivisor>100</nciDbhDivisor>"
       << "<nciIncludeSnagsInNCI>0</nciIncludeSnagsInNCI>"
       << "</NCIMasterMortality3>"
       << "</paramFile>";


  oOut.close();

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteNCIMortXMLErrorFile11()
////////////////////////////////////////////////////////////////////////////
const char* WriteNCIMortXMLErrorFile11() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  //WriteNCIMort file
  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06010101\">"
       << "<plot>"
       << "<timesteps>1</timesteps>"
       << "<yearsPerTimestep>1</yearsPerTimestep>";

  WriteNCIMortCommonErrorStuff(oOut);

  oOut << "<NCIMasterMortality3>"
       << "<nciWhichShadingEffect>0</nciWhichShadingEffect>"
       << "<nciWhichCrowdingEffect>" << default_crowding_effect << "</nciWhichCrowdingEffect>"
       << "<nciWhichNCITerm>2</nciWhichNCITerm>"
       << "<nciWhichSizeEffect>" << default_size_effect << "</nciWhichSizeEffect>"
       << "<nciWhichDamageEffect>" << default_damage_effect << "</nciWhichDamageEffect>"
       << "<nciWhichPrecipitationEffect>" << no_precip_effect << "</nciWhichPrecipitationEffect>"
       << "<nciWhichTemperatureEffect>" << no_temp_effect << "</nciWhichTemperatureEffect>"
       << "<nciWhichNitrogenEffect>" << no_nitrogen_effect << "</nciWhichNitrogenEffect>"
       << "<nciWhichInfectionEffect>" << no_infection_effect << "</nciWhichInfectionEffect>"
       << "<mo_nciMortSurvPeriod>1</mo_nciMortSurvPeriod>"
       << "<nciMaxCrowdingRadius>"
       << "<nmcrVal species=\"Species_1\">10</nmcrVal>"
       << "<nmcrVal species=\"Species_2\">10</nmcrVal>"
       << "</nciMaxCrowdingRadius>"
       << "<nciAlpha>"
       << "<naVal species=\"Species_1\">2.81</naVal>"
       << "<naVal species=\"Species_2\">2.81</naVal>"
       << "</nciAlpha>"
       << "<nciBeta>"
       << "<nbVal species=\"Species_1\">0.5</nbVal>"
       << "<nbVal species=\"Species_2\">0.5</nbVal>"
       << "</nciBeta>"
       << "<mo_nciMaxPotentialSurvival>"
       << "<mo_nmpsVal species=\"Species_1\">0.99</mo_nmpsVal>"
       << "<mo_nmpsVal species=\"Species_2\">0.99</mo_nmpsVal>"
       << "</mo_nciMaxPotentialSurvival>"
       << "<nciCrowdingGamma>"
       << "<ncgVal species=\"Species_1\">0.43</ncgVal>"
       << "<ncgVal species=\"Species_2\">0.43</ncgVal>"
       << "</nciCrowdingGamma>"
       << "<nciSizeEffectX0>"
       << "<nsex0Val species=\"Species_1\">34.2</nsex0Val>"
       << "<nsex0Val species=\"Species_2\">34.2</nsex0Val>"
       << "</nciSizeEffectX0>"
       << "<nciSizeEffectXb>"
       << "<nsexbVal species=\"Species_1\">5</nsexbVal>"
       << "<nsexbVal species=\"Species_2\">5</nsexbVal>"
       << "</nciSizeEffectXb>"
       << "<nciCrowdingC>"
       << "<nccVal species=\"Species_1\">1.98</nccVal>"
       << "<nccVal species=\"Species_2\">1.98</nccVal>"
       << "</nciCrowdingC>"
       << "<nciCrowdingD>"
       << "<ncdVal species=\"Species_1\">1.63</ncdVal>"
       << "<ncdVal species=\"Species_2\">1.63</ncdVal>"
       << "</nciCrowdingD>"
       << "<nciStormEffMedDmg>"
       << "<nsemdVal species=\"Species_1\">0.9</nsemdVal>"
       << "<nsemdVal species=\"Species_2\">0.9</nsemdVal>"
       << "</nciStormEffMedDmg>"
       << "<nciStormEffFullDmg>"
       << "<nsefdVal species=\"Species_1\">-0.42</nsefdVal>"
       << "<nsefdVal species=\"Species_2\">0.42</nsefdVal>"
       << "</nciStormEffFullDmg>"
       << "<nciNeighStormEffMedDmg>"
       << "<nnsemdVal species=\"Species_1\">0.33</nnsemdVal>"
       << "<nnsemdVal species=\"Species_2\">0.33</nnsemdVal>"
       << "</nciNeighStormEffMedDmg>"
       << "<nciNeighStormEffFullDmg>"
       << "<nnsefdVal species=\"Species_1\">0.54</nnsefdVal>"
       << "<nnsefdVal species=\"Species_2\">0.54</nnsefdVal>"
       << "</nciNeighStormEffFullDmg>"
       << "<nciSpecies_1NeighborLambda>"
       << "<nlVal species=\"Species_1\">0.66401082</nlVal>"
       << "<nlVal species=\"Species_2\">0.71</nlVal>"
       << "</nciSpecies_1NeighborLambda>"
       << "<nciSpecies_2NeighborLambda>"
       << "<nlVal species=\"Species_1\">0.00442797</nlVal>"
       << "<nlVal species=\"Species_2\">0.12</nlVal>"
       << "</nciSpecies_2NeighborLambda>"
       << "<nciShadingCoefficient>"
       << "<nscVal species=\"Species_1\">0</nscVal>"
       << "<nscVal species=\"Species_2\">0</nscVal>"
       << "</nciShadingCoefficient>"
       << "<nciShadingExponent>"
       << "<nseVal species=\"Species_1\">1</nseVal>"
       << "<nseVal species=\"Species_2\">1</nseVal>"
       << "</nciShadingExponent>"
       << "<nciMinNeighborDBH>"
       << "<nmndVal species=\"Species_1\">0</nmndVal>"
       << "<nmndVal species=\"Species_2\">0</nmndVal>"
       << "</nciMinNeighborDBH>"
       << "<nciDbhDivisor>100</nciDbhDivisor>"
       << "<nciIncludeSnagsInNCI>0</nciIncludeSnagsInNCI>"
       << "</NCIMasterMortality3>"
       << "</paramFile>";


  oOut.close();

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteNCIMortXMLErrorFile12()
////////////////////////////////////////////////////////////////////////////
const char* WriteNCIMortXMLErrorFile12() {
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

  WriteNCIMortCommonErrorStuff(oOut);

  oOut << "<NCIMasterMortality3>"
       << "<nciWhichShadingEffect>0</nciWhichShadingEffect>"
       << "<nciWhichCrowdingEffect>" << default_crowding_effect << "</nciWhichCrowdingEffect>"
       << "<nciWhichNCITerm>2</nciWhichNCITerm>"
       << "<nciWhichSizeEffect>" << default_size_effect << "</nciWhichSizeEffect>"
       << "<nciWhichDamageEffect>" << default_damage_effect << "</nciWhichDamageEffect>"
       << "<nciWhichPrecipitationEffect>" << no_precip_effect << "</nciWhichPrecipitationEffect>"
       << "<nciWhichTemperatureEffect>" << no_temp_effect << "</nciWhichTemperatureEffect>"
       << "<nciWhichNitrogenEffect>" << no_nitrogen_effect << "</nciWhichNitrogenEffect>"
       << "<nciWhichInfectionEffect>" << no_infection_effect << "</nciWhichInfectionEffect>"
       << "<mo_nciMortSurvPeriod>1</mo_nciMortSurvPeriod>"
       << "<nciMaxCrowdingRadius>"
       << "<nmcrVal species=\"Species_1\">10</nmcrVal>"
       << "<nmcrVal species=\"Species_2\">10</nmcrVal>"
       << "</nciMaxCrowdingRadius>"
       << "<nciAlpha>"
       << "<naVal species=\"Species_1\">2.81</naVal>"
       << "<naVal species=\"Species_2\">2.81</naVal>"
       << "</nciAlpha>"
       << "<nciBeta>"
       << "<nbVal species=\"Species_1\">0.5</nbVal>"
       << "<nbVal species=\"Species_2\">0.5</nbVal>"
       << "</nciBeta>"
       << "<mo_nciMaxPotentialSurvival>"
       << "<mo_nmpsVal species=\"Species_1\">0.99</mo_nmpsVal>"
       << "<mo_nmpsVal species=\"Species_2\">0.99</mo_nmpsVal>"
       << "</mo_nciMaxPotentialSurvival>"
       << "<nciCrowdingGamma>"
       << "<ncgVal species=\"Species_1\">0.43</ncgVal>"
       << "<ncgVal species=\"Species_2\">0.43</ncgVal>"
       << "</nciCrowdingGamma>"
       << "<nciSizeEffectX0>"
       << "<nsex0Val species=\"Species_1\">34.2</nsex0Val>"
       << "<nsex0Val species=\"Species_2\">34.2</nsex0Val>"
       << "</nciSizeEffectX0>"
       << "<nciSizeEffectXb>"
       << "<nsexbVal species=\"Species_1\">5</nsexbVal>"
       << "<nsexbVal species=\"Species_2\">5</nsexbVal>"
       << "</nciSizeEffectXb>"
       << "<nciCrowdingC>"
       << "<nccVal species=\"Species_1\">1.98</nccVal>"
       << "<nccVal species=\"Species_2\">1.98</nccVal>"
       << "</nciCrowdingC>"
       << "<nciCrowdingD>"
       << "<ncdVal species=\"Species_1\">1.63</ncdVal>"
       << "<ncdVal species=\"Species_2\">1.63</ncdVal>"
       << "</nciCrowdingD>"
       << "<nciStormEffMedDmg>"
       << "<nsemdVal species=\"Species_1\">0.9</nsemdVal>"
       << "<nsemdVal species=\"Species_2\">0.9</nsemdVal>"
       << "</nciStormEffMedDmg>"
       << "<nciStormEffFullDmg>"
       << "<nsefdVal species=\"Species_1\">0.42</nsefdVal>"
       << "<nsefdVal species=\"Species_2\">1.42</nsefdVal>"
       << "</nciStormEffFullDmg>"
       << "<nciNeighStormEffMedDmg>"
       << "<nnsemdVal species=\"Species_1\">0.33</nnsemdVal>"
       << "<nnsemdVal species=\"Species_2\">0.33</nnsemdVal>"
       << "</nciNeighStormEffMedDmg>"
       << "<nciNeighStormEffFullDmg>"
       << "<nnsefdVal species=\"Species_1\">0.54</nnsefdVal>"
       << "<nnsefdVal species=\"Species_2\">0.54</nnsefdVal>"
       << "</nciNeighStormEffFullDmg>"
       << "<nciSpecies_1NeighborLambda>"
       << "<nlVal species=\"Species_1\">0.66401082</nlVal>"
       << "<nlVal species=\"Species_2\">0.71</nlVal>"
       << "</nciSpecies_1NeighborLambda>"
       << "<nciSpecies_2NeighborLambda>"
       << "<nlVal species=\"Species_1\">0.00442797</nlVal>"
       << "<nlVal species=\"Species_2\">0.12</nlVal>"
       << "</nciSpecies_2NeighborLambda>"
       << "<nciShadingCoefficient>"
       << "<nscVal species=\"Species_1\">0</nscVal>"
       << "<nscVal species=\"Species_2\">0</nscVal>"
       << "</nciShadingCoefficient>"
       << "<nciShadingExponent>"
       << "<nseVal species=\"Species_1\">1</nseVal>"
       << "<nseVal species=\"Species_2\">1</nseVal>"
       << "</nciShadingExponent>"
       << "<nciMinNeighborDBH>"
       << "<nmndVal species=\"Species_1\">0</nmndVal>"
       << "<nmndVal species=\"Species_2\">0</nmndVal>"
       << "</nciMinNeighborDBH>"
       << "<nciDbhDivisor>100</nciDbhDivisor>"
       << "<nciIncludeSnagsInNCI>0</nciIncludeSnagsInNCI>"
       << "</NCIMasterMortality3>"
       << "</paramFile>";


  oOut.close();

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteNCIMortXMLFile9()
////////////////////////////////////////////////////////////////////////////
const char* WriteNCIMortXMLErrorFile9() {
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

  WriteNCIMortCommonErrorStuff(oOut);

  oOut << "<NCIMasterMortality3>"
       << "<nciWhichShadingEffect>0</nciWhichShadingEffect>"
       << "<nciWhichCrowdingEffect>" << default_crowding_effect << "</nciWhichCrowdingEffect>"
       << "<nciWhichNCITerm>2</nciWhichNCITerm>"
       << "<nciWhichSizeEffect>" << default_size_effect << "</nciWhichSizeEffect>"
       << "<nciWhichDamageEffect>" << default_damage_effect << "</nciWhichDamageEffect>"
       << "<nciWhichPrecipitationEffect>" << no_precip_effect << "</nciWhichPrecipitationEffect>"
       << "<nciWhichTemperatureEffect>" << no_temp_effect << "</nciWhichTemperatureEffect>"
       << "<nciWhichNitrogenEffect>" << no_nitrogen_effect << "</nciWhichNitrogenEffect>"
       << "<nciWhichInfectionEffect>" << no_infection_effect << "</nciWhichInfectionEffect>"
       << "<mo_nciMortSurvPeriod>1</mo_nciMortSurvPeriod>"
       << "<nciMaxCrowdingRadius>"
       << "<nmcrVal species=\"Species_1\">10</nmcrVal>"
       << "<nmcrVal species=\"Species_2\">10</nmcrVal>"
       << "</nciMaxCrowdingRadius>"
       << "<nciAlpha>"
       << "<naVal species=\"Species_1\">2.81</naVal>"
       << "<naVal species=\"Species_2\">2.81</naVal>"
       << "</nciAlpha>"
       << "<nciBeta>"
       << "<nbVal species=\"Species_1\">0.5</nbVal>"
       << "<nbVal species=\"Species_2\">0.5</nbVal>"
       << "</nciBeta>"
       << "<mo_nciMaxPotentialSurvival>"
       << "<mo_nmpsVal species=\"Species_1\">0.99</mo_nmpsVal>"
       << "<mo_nmpsVal species=\"Species_2\">0.99</mo_nmpsVal>"
       << "</mo_nciMaxPotentialSurvival>"
       << "<nciCrowdingGamma>"
       << "<ncgVal species=\"Species_1\">0.43</ncgVal>"
       << "<ncgVal species=\"Species_2\">0.43</ncgVal>"
       << "</nciCrowdingGamma>"
       << "<nciSizeEffectX0>"
       << "<nsex0Val species=\"Species_1\">34.2</nsex0Val>"
       << "<nsex0Val species=\"Species_2\">34.2</nsex0Val>"
       << "</nciSizeEffectX0>"
       << "<nciSizeEffectXb>"
       << "<nsexbVal species=\"Species_1\">5</nsexbVal>"
       << "<nsexbVal species=\"Species_2\">5</nsexbVal>"
       << "</nciSizeEffectXb>"
       << "<nciCrowdingC>"
       << "<nccVal species=\"Species_1\">1.98</nccVal>"
       << "<nccVal species=\"Species_2\">1.98</nccVal>"
       << "</nciCrowdingC>"
       << "<nciCrowdingD>"
       << "<ncdVal species=\"Species_1\">1.63</ncdVal>"
       << "<ncdVal species=\"Species_2\">1.63</ncdVal>"
       << "</nciCrowdingD>"
       << "<nciStormEffMedDmg>"
       << "<nsemdVal species=\"Species_1\">-0.9</nsemdVal>"
       << "<nsemdVal species=\"Species_2\">0.9</nsemdVal>"
       << "</nciStormEffMedDmg>"
       << "<nciStormEffFullDmg>"
       << "<nsefdVal species=\"Species_1\">0.42</nsefdVal>"
       << "<nsefdVal species=\"Species_2\">0.42</nsefdVal>"
       << "</nciStormEffFullDmg>"
       << "<nciNeighStormEffMedDmg>"
       << "<nnsemdVal species=\"Species_1\">0.33</nnsemdVal>"
       << "<nnsemdVal species=\"Species_2\">0.33</nnsemdVal>"
       << "</nciNeighStormEffMedDmg>"
       << "<nciNeighStormEffFullDmg>"
       << "<nnsefdVal species=\"Species_1\">0.54</nnsefdVal>"
       << "<nnsefdVal species=\"Species_2\">0.54</nnsefdVal>"
       << "</nciNeighStormEffFullDmg>"
       << "<nciSpecies_1NeighborLambda>"
        << "<nlVal species=\"Species_1\">0.66401082</nlVal>"
        << "<nlVal species=\"Species_2\">0.71</nlVal>"
        << "</nciSpecies_1NeighborLambda>"
        << "<nciSpecies_2NeighborLambda>"
        << "<nlVal species=\"Species_1\">0.00442797</nlVal>"
        << "<nlVal species=\"Species_2\">0.12</nlVal>"
        << "</nciSpecies_2NeighborLambda>"
        << "<nciShadingCoefficient>"
       << "<nscVal species=\"Species_1\">0</nscVal>"
       << "<nscVal species=\"Species_2\">0</nscVal>"
       << "</nciShadingCoefficient>"
       << "<nciShadingExponent>"
       << "<nseVal species=\"Species_1\">1</nseVal>"
       << "<nseVal species=\"Species_2\">1</nseVal>"
       << "</nciShadingExponent>"
       << "<nciMinNeighborDBH>"
       << "<nmndVal species=\"Species_1\">0</nmndVal>"
       << "<nmndVal species=\"Species_2\">0</nmndVal>"
       << "</nciMinNeighborDBH>"
       << "<nciDbhDivisor>100</nciDbhDivisor>"
       << "<nciIncludeSnagsInNCI>0</nciIncludeSnagsInNCI>"
       << "</NCIMasterMortality3>"
       << "</paramFile>";


  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteNCIMortPlotAndTrees()
/////////////////////////////////////////////////////////////////////////////
void WriteNCIMortPlotAndTrees( std::fstream &oOut )
{
  using namespace std;
  oOut << "<randomSeed>1</randomSeed>"
       << "<plot_lenX>200.0</plot_lenX>"
       << "<plot_lenY>200.0</plot_lenY>"
       << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
       << "<plot_temp_C>12.88171785</plot_temp_C>"
       << "<plot_latitude>55.37</plot_latitude>"
       << "</plot>"
       << "<trees>"
       << "<tr_speciesList>"
       << "<tr_species speciesName=\"Species_1\" />"
       << "<tr_species speciesName=\"Species_2\" />"
       << "<tr_species speciesName=\"Species_3\" />"
       << "<tr_species speciesName=\"Species_4\" />"
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
       << "<tr_stdMaxCrownRad>"
       << "<tr_smcrVal species=\"Species_1\">10</tr_smcrVal>"
       << "<tr_smcrVal species=\"Species_2\">10</tr_smcrVal>"
       << "<tr_smcrVal species=\"Species_3\">10</tr_smcrVal>"
       << "<tr_smcrVal species=\"Species_4\">10</tr_smcrVal>"
       << "</tr_stdMaxCrownRad>"
       << "<tr_conversionDiam10ToDBH>"
       << "<tr_cdtdVal species=\"Species_1\">0.8008</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_2\">0.8008</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_3\">0.8008</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_4\">0.8008</tr_cdtdVal>"
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
}

/////////////////////////////////////////////////////////////////////////////
// WriteNCIMortStormParameters()
/////////////////////////////////////////////////////////////////////////////
void WriteNCIMortStormParameters( std::fstream &oOut )
{
  using namespace std;
  oOut << "<Storm1>"
       << "<st_s1ReturnInterval>1000</st_s1ReturnInterval>"
       << "<st_s2ReturnInterval>1000</st_s2ReturnInterval>"
       << "<st_s3ReturnInterval>1000</st_s3ReturnInterval>"
       << "<st_s4ReturnInterval>1000</st_s4ReturnInterval>"
       << "<st_s5ReturnInterval>1000</st_s5ReturnInterval>"
       << "<st_s6ReturnInterval>1000</st_s6ReturnInterval>"
       << "<st_s7ReturnInterval>1000</st_s7ReturnInterval>"
       << "<st_s8ReturnInterval>1000</st_s8ReturnInterval>"
       << "<st_s9ReturnInterval>1000</st_s9ReturnInterval>"
       << "<st_s10ReturnInterval>1000</st_s10ReturnInterval>"
       << "<st_susceptibility>1</st_susceptibility>"
       << "<st_stochasticity>0</st_stochasticity>"
       << "<st_stmSSTPeriod>1</st_stmSSTPeriod>"
       << "<st_stmSineD>0</st_stmSineD>"
       << "<st_stmSineF>1</st_stmSineF>"
       << "<st_stmSineG>1</st_stmSineG>"
       << "<st_stmTrendSlopeM>0</st_stmTrendSlopeM>"
       << "<st_stmTrendInterceptI>1</st_stmTrendInterceptI>"
       << "</Storm1>"
       << "<StormDamageApplier2>"
       << "<st_minDBH>"
       << "<st_mdVal species=\"Species_1\">5</st_mdVal>"
       << "<st_mdVal species=\"Species_2\">6</st_mdVal>"
       << "<st_mdVal species=\"Species_3\">5</st_mdVal>"
       << "<st_mdVal species=\"Species_4\">6</st_mdVal>"
       << "</st_minDBH>"
       << "<st_stmDmgInterceptMed>"
       << "<st_sdimVal species=\"Species_1\">2.1789601</st_sdimVal>"
       << "<st_sdimVal species=\"Species_2\">2.475987</st_sdimVal>"
       << "<st_sdimVal species=\"Species_3\">2.1789601</st_sdimVal>"
       << "<st_sdimVal species=\"Species_4\">2.475987</st_sdimVal>"
       << "</st_stmDmgInterceptMed>"
       << "<st_stmDmgInterceptFull>"
       << "<st_sdifVal species=\"Species_1\">3.6334169</st_sdifVal>"
       << "<st_sdifVal species=\"Species_2\">3.6331242</st_sdifVal>"
       << "<st_sdifVal species=\"Species_3\">3.6334169</st_sdifVal>"
       << "<st_sdifVal species=\"Species_4\">3.6331242</st_sdifVal>"
       << "</st_stmDmgInterceptFull>"
       << "<st_stmIntensityCoeff>"
       << "<st_sicVal species=\"Species_1\">-0.3545352</st_sicVal>"
       << "<st_sicVal species=\"Species_2\">-1.2289105</st_sicVal>"
       << "<st_sicVal species=\"Species_3\">-0.3545352</st_sicVal>"
       << "<st_sicVal species=\"Species_4\">-1.2289105</st_sicVal>"
       << "</st_stmIntensityCoeff>"
       << "<st_stmDBHCoeff>"
       << "<st_sdcVal species=\"Species_1\">0.8280319</st_sdcVal>"
       << "<st_sdcVal species=\"Species_2\">0.3282479</st_sdcVal>"
       << "<st_sdcVal species=\"Species_3\">0.8280319</st_sdcVal>"
       << "<st_sdcVal species=\"Species_4\">0.3282479</st_sdcVal>"
       << "</st_stmDBHCoeff>"
       << "<st_stmPropDieMedDmg>"
       << "<st_spdmdVal species=\"Species_1\">0</st_spdmdVal>"
       << "<st_spdmdVal species=\"Species_2\">0</st_spdmdVal>"
       << "<st_spdmdVal species=\"Species_3\">0</st_spdmdVal>"
       << "<st_spdmdVal species=\"Species_4\">0</st_spdmdVal>"
       << "</st_stmPropDieMedDmg>"
       << "<st_stmPropDieFullDmg>"
       << "<st_spdfdVal species=\"Species_1\">0</st_spdfdVal>"
       << "<st_spdfdVal species=\"Species_2\">0</st_spdfdVal>"
       << "<st_spdfdVal species=\"Species_3\">0</st_spdfdVal>"
       << "<st_spdfdVal species=\"Species_4\">0</st_spdfdVal>"
       << "</st_stmPropDieFullDmg>"
       << "<st_stmPropTipUpFullDmg>"
       << "<st_sptufdVal species=\"Species_1\">0</st_sptufdVal>"
       << "<st_sptufdVal species=\"Species_2\">0</st_sptufdVal>"
       << "<st_sptufdVal species=\"Species_3\">0</st_sptufdVal>"
       << "<st_sptufdVal species=\"Species_4\">0</st_sptufdVal>"
       << "</st_stmPropTipUpFullDmg>"
       << "<st_numYearsStormSnags>0</st_numYearsStormSnags>"
       << "<st_numYearsToHeal>4</st_numYearsToHeal>"
       << "</StormDamageApplier2>";
}

/////////////////////////////////////////////////////////////////////////////
// WriteNCIMortRun1CommonStuff()
/////////////////////////////////////////////////////////////////////////////
void WriteNCIMortRun1CommonStuff( std::fstream &oOut )
{
  WriteNCIMortPlotAndTrees(oOut);
  using namespace std;
  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>Storm</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>StormDamageApplier</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>2</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_3\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_4\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_4\" type=\"Sapling\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>NCIMasterMortality</behaviorName>"
       << "<version>3</version>"
       << "<listPosition>3</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_4\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_4\" type=\"Sapling\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>StochasticMortality</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>4</listPosition>"
       << "<applyTo species=\"Species_3\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>RemoveDead</behaviorName>"
       << "<version>2</version>"
       << "<listPosition>5</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_4\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_4\" type=\"Sapling\"/>"
       << "</behavior>"
       << "</behaviorList>";

  WriteNCIMortStormParameters(oOut);

  oOut << "<StochasticMortality4>"
       << "<mo_stochasticMortRate>"
       << "<mo_smrVal species=\"Species_3\">0.0</mo_smrVal>"
       << "</mo_stochasticMortRate>"
       << "</StochasticMortality4>"
       << "<NCIMasterMortality3>"
       << "<nciWhichShadingEffect>" << no_shading << "</nciWhichShadingEffect>"
       << "<nciWhichCrowdingEffect>" << default_crowding_effect << "</nciWhichCrowdingEffect>"
       << "<nciWhichNCITerm>" << nci_with_neighbor_damage << "</nciWhichNCITerm>"
       << "<nciWhichSizeEffect>" << default_size_effect << "</nciWhichSizeEffect>"
       << "<nciWhichDamageEffect>" << default_damage_effect << "</nciWhichDamageEffect>"
       << "<nciWhichPrecipitationEffect>" << no_precip_effect << "</nciWhichPrecipitationEffect>"
       << "<nciWhichTemperatureEffect>" << no_temp_effect << "</nciWhichTemperatureEffect>"
       << "<nciWhichNitrogenEffect>" << no_nitrogen_effect << "</nciWhichNitrogenEffect>"
       << "<nciWhichInfectionEffect>" << no_infection_effect << "</nciWhichInfectionEffect>"
       << "<mo_nciMortSurvPeriod>1</mo_nciMortSurvPeriod>"
       << "<nciMaxCrowdingRadius>"
       << "<nmcrVal species=\"Species_1\">10</nmcrVal>"
       << "<nmcrVal species=\"Species_4\">10</nmcrVal>"
       << "<nmcrVal species=\"Species_2\">10</nmcrVal>"
       << "</nciMaxCrowdingRadius>"
       << "<nciAlpha>"
       << "<naVal species=\"Species_1\">2.17031683</naVal>"
       << "<naVal species=\"Species_2\">2.81</naVal>"
       << "<naVal species=\"Species_4\">1.33</naVal>"
       << "</nciAlpha>"
       << "<nciBeta>"
       << "<nbVal species=\"Species_1\">0.699942</nbVal>"
       << "<nbVal species=\"Species_2\">0.5</nbVal>"
       << "<nbVal species=\"Species_4\">0.09</nbVal>"
       << "</nciBeta>"
       << "<mo_nciMaxPotentialSurvival>"
       << "<mo_nmpsVal species=\"Species_1\">0.98</mo_nmpsVal>"
       << "<mo_nmpsVal species=\"Species_2\">0.99</mo_nmpsVal>"
       << "<mo_nmpsVal species=\"Species_4\">0.97</mo_nmpsVal>"
       << "</mo_nciMaxPotentialSurvival>"
       << "<nciCrowdingGamma>"
       << "<ncgVal species=\"Species_1\">0.43</ncgVal>"
       << "<ncgVal species=\"Species_2\">0.36</ncgVal>"
       << "<ncgVal species=\"Species_4\">-0.4</ncgVal>"
       << "</nciCrowdingGamma>"
       << "<nciSizeEffectX0>"
       << "<nsex0Val species=\"Species_1\">34.24638994</nsex0Val>"
       << "<nsex0Val species=\"Species_2\">122.23</nsex0Val>"
       << "<nsex0Val species=\"Species_4\">16.43</nsex0Val>"
       << "</nciSizeEffectX0>"
       << "<nciSizeEffectXb>"
       << "<nsexbVal species=\"Species_1\">5</nsexbVal>"
       << "<nsexbVal species=\"Species_2\">2.36</nsexbVal>"
       << "<nsexbVal species=\"Species_4\">1.41</nsexbVal>"
       << "</nciSizeEffectXb>"
       << "<nciCrowdingC>"
       << "<nccVal species=\"Species_1\">0.31</nccVal>"
       << "<nccVal species=\"Species_2\">0.236</nccVal>"
       << "<nccVal species=\"Species_4\">0.26</nccVal>"
       << "</nciCrowdingC>"
       << "<nciCrowdingD>"
       << "<ncdVal species=\"Species_1\">0.00118</ncdVal>"
       << "<ncdVal species=\"Species_2\">0.002009</ncdVal>"
       << "<ncdVal species=\"Species_4\">0.00474</ncdVal>"
       << "</nciCrowdingD>"
       << "<nciStormEffMedDmg>"
       << "<nsemdVal species=\"Species_1\">0.89</nsemdVal>"
       << "<nsemdVal species=\"Species_2\">0.9</nsemdVal>"
       << "<nsemdVal species=\"Species_4\">0.78</nsemdVal>"
       << "</nciStormEffMedDmg>"
       << "<nciStormEffFullDmg>"
       << "<nsefdVal species=\"Species_1\">0.42</nsefdVal>"
       << "<nsefdVal species=\"Species_2\">0.34</nsefdVal>"
       << "<nsefdVal species=\"Species_4\">0.63</nsefdVal>"
       << "</nciStormEffFullDmg>"
       << "<nciNeighStormEffMedDmg>"
       << "<nnsemdVal species=\"Species_1\">0.83</nnsemdVal>"
       << "<nnsemdVal species=\"Species_2\">0.33</nnsemdVal>"
       << "<nnsemdVal species=\"Species_4\">0.76</nnsemdVal>"
       << "</nciNeighStormEffMedDmg>"
       << "<nciNeighStormEffFullDmg>"
       << "<nnsefdVal species=\"Species_1\">0.54</nnsefdVal>"
       << "<nnsefdVal species=\"Species_2\">0.27</nnsefdVal>"
       << "<nnsefdVal species=\"Species_4\">0.7</nnsefdVal>"
       << "</nciNeighStormEffFullDmg>"
       << "<nciSpecies_1NeighborLambda>"
       << "<nlVal species=\"Species_1\">0.66401082</nlVal>"
       << "<nlVal species=\"Species_2\">0.71</nlVal>"
       << "<nlVal species=\"Species_4\">0.08</nlVal>"
       << "</nciSpecies_1NeighborLambda>"
       << "<nciSpecies_2NeighborLambda>"
       << "<nlVal species=\"Species_1\">0.00442797</nlVal>"
       << "<nlVal species=\"Species_2\">0.12</nlVal>"
       << "<nlVal species=\"Species_4\">0.03</nlVal>"
       << "</nciSpecies_2NeighborLambda>"
       << "<nciSpecies_3NeighborLambda>"
       << "<nlVal species=\"Species_1\">0.41812471</nlVal>"
       << "<nlVal species=\"Species_2\">0.24</nlVal>"
       << "<nlVal species=\"Species_4\">0.05</nlVal>"
       << "</nciSpecies_3NeighborLambda>"
       << "<nciSpecies_4NeighborLambda>"
       << "<nlVal species=\"Species_1\">0.41812471</nlVal>"
       << "<nlVal species=\"Species_2\">0.24</nlVal>"
       << "<nlVal species=\"Species_4\">0.05</nlVal>"
       << "</nciSpecies_4NeighborLambda>"
       << "<nciMinNeighborDBH>"
       << "<nmndVal species=\"Species_1\">0</nmndVal>"
       << "<nmndVal species=\"Species_2\">0</nmndVal>"
       << "<nmndVal species=\"Species_3\">0</nmndVal>"
       << "<nmndVal species=\"Species_4\">0</nmndVal>"
       << "</nciMinNeighborDBH>"
       << "<nciDbhDivisor>100</nciDbhDivisor>"
       << "<nciIncludeSnagsInNCI>0</nciIncludeSnagsInNCI>"
       << "</NCIMasterMortality3>"
       << "</paramFile>";
}

/////////////////////////////////////////////////////////////////////////////
// WriteNCIMortRun2CommonStuff()
/////////////////////////////////////////////////////////////////////////////
void WriteNCIMortRun2CommonStuff( std::fstream &oOut )
{
  using namespace std;
  WriteNCIMortPlotAndTrees(oOut);

  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>SailLight</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>NCIMasterMortality</behaviorName>"
       << "<version>3</version>"
       << "<listPosition>2</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>StochasticMortality</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>3</listPosition>"
       << "<applyTo species=\"Species_3\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>RemoveDead</behaviorName>"
       << "<version>2</version>"
       << "<listPosition>4</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "</behavior>"
       << "</behaviorList>";

  oOut << "<SailLight1>"
       << "<li_heightOfFishEyePhoto>1</li_heightOfFishEyePhoto>"
       << "<li_beamFractGlobalRad>0.5</li_beamFractGlobalRad>"
       << "<li_clearSkyTransCoeff>0.65</li_clearSkyTransCoeff>"
       << "<li_julianDayGrowthStarts>120</li_julianDayGrowthStarts>"
       << "<li_julianDayGrowthEnds>270</li_julianDayGrowthEnds>"
       << "<li_minSunAngle>0.785</li_minSunAngle>"
       << "<li_lightExtinctionCoefficient>"
       << "<li_lecVal species=\"Species_1\">0.08</li_lecVal>"
       << "<li_lecVal species=\"Species_2\">0.091</li_lecVal>"
       << "<li_lecVal species=\"Species_3\">0.059</li_lecVal>"
       << "<li_lecVal species=\"Species_4\">0.059</li_lecVal>"
       << "</li_lightExtinctionCoefficient>"
       << "<li_maxShadingRadius>15.0</li_maxShadingRadius>"
       << "<li_skyMaskAngle>30.0</li_skyMaskAngle>"
       << "<li_crownFracOfHeight>0</li_crownFracOfHeight>"
       << "</SailLight1>";

  oOut << "<StochasticMortality3>"
       << "<mo_stochasticMortRate>"
       << "<mo_smrVal species=\"Species_3\">0.0</mo_smrVal>"
       << "</mo_stochasticMortRate>"
       << "</StochasticMortality3>"
       << "<NCIMasterMortality2>"
       << "<nciWhichShadingEffect>" << default_shading << "</nciWhichShadingEffect>"
       << "<nciWhichCrowdingEffect>" << no_crowding_effect << "</nciWhichCrowdingEffect>"
       << "<nciWhichNCITerm>" << default_nci_term << "</nciWhichNCITerm>"
       << "<nciWhichSizeEffect>" << default_size_effect << "</nciWhichSizeEffect>"
       << "<nciWhichDamageEffect>" << no_damage_effect << "</nciWhichDamageEffect>"
       << "<nciWhichPrecipitationEffect>" << no_precip_effect << "</nciWhichPrecipitationEffect>"
       << "<nciWhichTemperatureEffect>" << no_temp_effect << "</nciWhichTemperatureEffect>"
       << "<nciWhichNitrogenEffect>" << no_nitrogen_effect << "</nciWhichNitrogenEffect>"
       << "<nciWhichInfectionEffect>" << no_infection_effect << "</nciWhichInfectionEffect>"
       << "<mo_nciMortSurvPeriod>1</mo_nciMortSurvPeriod>"
       << "<nciMaxCrowdingRadius>"
       << "<nmcrVal species=\"Species_1\">10</nmcrVal>"
       << "</nciMaxCrowdingRadius>"
       << "<nciAlpha>"
       << "<naVal species=\"Species_1\">2.17031683</naVal>"
       << "</nciAlpha>"
       << "<nciBeta>"
       << "<nbVal species=\"Species_1\">0.699942</nbVal>"
       << "</nciBeta>"
       << "<mo_nciMaxPotentialSurvival>"
       << "<mo_nmpsVal species=\"Species_1\">0.98</mo_nmpsVal>"
       << "</mo_nciMaxPotentialSurvival>"
       << "<nciCrowdingGamma>"
       << "<ncgVal species=\"Species_1\">0</ncgVal>"
       << "</nciCrowdingGamma>"
       << "<nciSizeEffectX0>"
       << "<nsex0Val species=\"Species_1\">34.24638994</nsex0Val>"
       << "</nciSizeEffectX0>"
       << "<nciSizeEffectXb>"
       << "<nsexbVal species=\"Species_1\">5</nsexbVal>"
       << "</nciSizeEffectXb>"
       << "<nciCrowdingC>"
       << "<nccVal species=\"Species_1\">1.63</nccVal>"
       << "</nciCrowdingC>"
       << "<nciCrowdingD>"
       << "<ncdVal species=\"Species_1\">1</ncdVal>"
       << "</nciCrowdingD>"
       << "<nciSpecies_1NeighborLambda>"
       << "<nlVal species=\"Species_1\">0.66401082</nlVal>"
       << "</nciSpecies_1NeighborLambda>"
       << "<nciSpecies_2NeighborLambda>"
       << "<nlVal species=\"Species_1\">0.00442797</nlVal>"
       << "</nciSpecies_2NeighborLambda>"
       << "<nciSpecies_3NeighborLambda>"
       << "<nlVal species=\"Species_1\">0.41812471</nlVal>"
       << "</nciSpecies_3NeighborLambda>"
       << "<nciSpecies_4NeighborLambda>"
       << "<nlVal species=\"Species_1\">0.41812471</nlVal>"
       << "</nciSpecies_4NeighborLambda>"
       << "<nciShadingCoefficient>"
       << "<nscVal species=\"Species_1\">0.2</nscVal>"
       << "</nciShadingCoefficient>"
       << "<nciShadingExponent>"
       << "<nseVal species=\"Species_1\">0.5</nseVal>"
       << "</nciShadingExponent>"
       << "<nciMinNeighborDBH>"
       << "<nmndVal species=\"Species_1\">0</nmndVal>"
       << "<nmndVal species=\"Species_2\">0</nmndVal>"
       << "<nmndVal species=\"Species_3\">0</nmndVal>"
       << "<nmndVal species=\"Species_4\">0</nmndVal>"
       << "</nciMinNeighborDBH>"
       << "<nciDbhDivisor>100</nciDbhDivisor>"
       << "<nciIncludeSnagsInNCI>0</nciIncludeSnagsInNCI>"
       << "</NCIMasterMortality2>"
       << "</paramFile>";
}

/////////////////////////////////////////////////////////////////////////////
// WriteNCIMortRun3CommonStuff()
/////////////////////////////////////////////////////////////////////////////
void WriteNCIMortRun3CommonStuff( std::fstream &oOut )
{
  using namespace std;
  WriteNCIMortPlotAndTrees(oOut);

  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>SailLight</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_4\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_4\" type=\"Sapling\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>NCIMasterMortality</behaviorName>"
       << "<version>3</version>"
       << "<listPosition>2</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_4\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_4\" type=\"Sapling\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>RemoveDead</behaviorName>"
       << "<version>2</version>"
       << "<listPosition>3</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_4\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_4\" type=\"Sapling\"/>"
       << "</behavior>"
       << "</behaviorList>";

  oOut << "<SailLight1>"
       << "<li_heightOfFishEyePhoto>1</li_heightOfFishEyePhoto>"
       << "<li_beamFractGlobalRad>0.5</li_beamFractGlobalRad>"
       << "<li_clearSkyTransCoeff>0.65</li_clearSkyTransCoeff>"
       << "<li_julianDayGrowthStarts>120</li_julianDayGrowthStarts>"
       << "<li_julianDayGrowthEnds>270</li_julianDayGrowthEnds>"
       << "<li_minSunAngle>0.785</li_minSunAngle>"
       << "<li_lightExtinctionCoefficient>"
       << "<li_lecVal species=\"Species_1\">0.08</li_lecVal>"
       << "<li_lecVal species=\"Species_2\">0.091</li_lecVal>"
       << "<li_lecVal species=\"Species_3\">0.059</li_lecVal>"
       << "<li_lecVal species=\"Species_4\">0.059</li_lecVal>"
       << "</li_lightExtinctionCoefficient>"
       << "<li_maxShadingRadius>15.0</li_maxShadingRadius>"
       << "<li_skyMaskAngle>30.0</li_skyMaskAngle>"
       << "<li_crownFracOfHeight>0</li_crownFracOfHeight>"
       << "</SailLight1>";

  oOut << "<NCIMasterMortality2>"
       << "<nciWhichShadingEffect>" << default_shading << "</nciWhichShadingEffect>"
       << "<nciWhichCrowdingEffect>" << default_crowding_effect << "</nciWhichCrowdingEffect>"
       << "<nciWhichNCITerm>" << default_nci_term << "</nciWhichNCITerm>"
       << "<nciWhichSizeEffect>" << default_size_effect << "</nciWhichSizeEffect>"
       << "<nciWhichDamageEffect>" << no_damage_effect << "</nciWhichDamageEffect>"
       << "<nciWhichPrecipitationEffect>" << no_precip_effect << "</nciWhichPrecipitationEffect>"
       << "<nciWhichTemperatureEffect>" << no_temp_effect << "</nciWhichTemperatureEffect>"
       << "<nciWhichNitrogenEffect>" << no_nitrogen_effect << "</nciWhichNitrogenEffect>"
       << "<nciWhichInfectionEffect>" << no_infection_effect << "</nciWhichInfectionEffect>"
       << "<mo_nciMortSurvPeriod>1</mo_nciMortSurvPeriod>"
       << "<nciMaxCrowdingRadius>"
       << "<nmcrVal species=\"Species_1\">10</nmcrVal>"
       << "<nmcrVal species=\"Species_4\">15</nmcrVal>"
       << "<nmcrVal species=\"Species_2\">10</nmcrVal>"
       << "</nciMaxCrowdingRadius>"
       << "<nciAlpha>"
       << "<naVal species=\"Species_1\">2.17031683</naVal>"
       << "<naVal species=\"Species_2\">2.81</naVal>"
       << "<naVal species=\"Species_4\">1.33</naVal>"
       << "</nciAlpha>"
       << "<nciBeta>"
       << "<nbVal species=\"Species_1\">0.699942</nbVal>"
       << "<nbVal species=\"Species_2\">0.5</nbVal>"
       << "<nbVal species=\"Species_4\">0.09</nbVal>"
       << "</nciBeta>"
       << "<mo_nciMaxPotentialSurvival>"
       << "<mo_nmpsVal species=\"Species_1\">0.98</mo_nmpsVal>"
       << "<mo_nmpsVal species=\"Species_2\">0.99</mo_nmpsVal>"
       << "<mo_nmpsVal species=\"Species_4\">0.97</mo_nmpsVal>"
       << "</mo_nciMaxPotentialSurvival>"
       << "<nciCrowdingGamma>"
       << "<ncgVal species=\"Species_1\">0</ncgVal>"
       << "<ncgVal species=\"Species_2\">-0.13</ncgVal>"
       << "<ncgVal species=\"Species_4\">-0.23</ncgVal>"
       << "</nciCrowdingGamma>"
       << "<nciSizeEffectX0>"
       << "<nsex0Val species=\"Species_1\">34.246</nsex0Val>"
       << "<nsex0Val species=\"Species_2\">122.23</nsex0Val>"
       << "<nsex0Val species=\"Species_4\">16.43</nsex0Val>"
       << "</nciSizeEffectX0>"
       << "<nciSizeEffectXb>"
       << "<nsexbVal species=\"Species_1\">5</nsexbVal>"
       << "<nsexbVal species=\"Species_2\">2.36</nsexbVal>"
       << "<nsexbVal species=\"Species_4\">1.41</nsexbVal>"
       << "</nciSizeEffectXb>"
       << "<nciCrowdingC>"
       << "<nccVal species=\"Species_1\">0.98</nccVal>"
       << "<nccVal species=\"Species_2\">0.57</nccVal>"
       << "<nccVal species=\"Species_4\">0.00029</nccVal>"
       << "</nciCrowdingC>"
       << "<nciCrowdingD>"
       << "<ncdVal species=\"Species_1\">0.00012</ncdVal>"
       << "<ncdVal species=\"Species_2\">0.00056</ncdVal>"
       << "<ncdVal species=\"Species_4\">1</ncdVal>"
       << "</nciCrowdingD>"
       << "<nciStormEffMedDmg>"
       << "<nsemdVal species=\"Species_1\">1</nsemdVal>"
       << "<nsemdVal species=\"Species_2\">1</nsemdVal>"
       << "<nsemdVal species=\"Species_4\">1</nsemdVal>"
       << "</nciStormEffMedDmg>"
       << "<nciStormEffFullDmg>"
       << "<nsefdVal species=\"Species_1\">1</nsefdVal>"
       << "<nsefdVal species=\"Species_2\">1</nsefdVal>"
       << "<nsefdVal species=\"Species_4\">1</nsefdVal>"
       << "</nciStormEffFullDmg>"
       << "<nciNeighStormEffMedDmg>"
       << "<nnsemdVal species=\"Species_1\">1</nnsemdVal>"
       << "<nnsemdVal species=\"Species_2\">1</nnsemdVal>"
       << "<nnsemdVal species=\"Species_4\">1</nnsemdVal>"
       << "</nciNeighStormEffMedDmg>"
       << "<nciNeighStormEffFullDmg>"
       << "<nnsefdVal species=\"Species_1\">1</nnsefdVal>"
       << "<nnsefdVal species=\"Species_2\">1</nnsefdVal>"
       << "<nnsefdVal species=\"Species_4\">1</nnsefdVal>"
       << "</nciNeighStormEffFullDmg>"
       << "<nciSpecies_1NeighborLambda>"
       << "<nlVal species=\"Species_1\">0.664</nlVal>"
       << "<nlVal species=\"Species_2\">0.71</nlVal>"
       << "<nlVal species=\"Species_4\">0.08</nlVal>"
       << "</nciSpecies_1NeighborLambda>"
       << "<nciSpecies_2NeighborLambda>"
       << "<nlVal species=\"Species_1\">0.0044</nlVal>"
       << "<nlVal species=\"Species_2\">0.12</nlVal>"
       << "<nlVal species=\"Species_4\">0.03</nlVal>"
       << "</nciSpecies_2NeighborLambda>"
       << "<nciSpecies_3NeighborLambda>"
       << "<nlVal species=\"Species_1\">0.4181</nlVal>"
       << "<nlVal species=\"Species_2\">0.24</nlVal>"
       << "<nlVal species=\"Species_4\">0.05</nlVal>"
       << "</nciSpecies_3NeighborLambda>"
       << "<nciSpecies_4NeighborLambda>"
       << "<nlVal species=\"Species_1\">0.41812471</nlVal>"
       << "<nlVal species=\"Species_2\">0.24</nlVal>"
       << "<nlVal species=\"Species_4\">0.05</nlVal>"
       << "</nciSpecies_4NeighborLambda>"
       << "<nciShadingCoefficient>"
       << "<nscVal species=\"Species_1\">0.2</nscVal>"
       << "<nscVal species=\"Species_2\">0.3</nscVal>"
       << "<nscVal species=\"Species_4\">0.5</nscVal>"
       << "</nciShadingCoefficient>"
       << "<nciShadingExponent>"
       << "<nseVal species=\"Species_1\">1</nseVal>"
       << "<nseVal species=\"Species_2\">1</nseVal>"
       << "<nseVal species=\"Species_4\">1</nseVal>"
       << "</nciShadingExponent>"
       << "<nciMinNeighborDBH>"
       << "<nmndVal species=\"Species_1\">10</nmndVal>"
       << "<nmndVal species=\"Species_2\">12</nmndVal>"
       << "<nmndVal species=\"Species_3\">16</nmndVal>"
       << "<nmndVal species=\"Species_4\">14</nmndVal>"
       << "</nciMinNeighborDBH>"
       << "<nciDbhDivisor>1</nciDbhDivisor>"
       << "<nciIncludeSnagsInNCI>0</nciIncludeSnagsInNCI>"
       << "</NCIMasterMortality2>"
       << "</paramFile>";
}

/////////////////////////////////////////////////////////////////////////////
// WriteNCIMortRun4CommonStuff()
/////////////////////////////////////////////////////////////////////////////
void WriteNCIMortRun4CommonStuff( std::fstream &oOut )
{
  using namespace std;
  WriteNCIMortPlotAndTrees(oOut);

  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>SailLight</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_4\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_4\" type=\"Sapling\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>NCIMasterMortality</behaviorName>"
       << "<version>3</version>"
       << "<listPosition>2</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_4\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_4\" type=\"Sapling\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>RemoveDead</behaviorName>"
       << "<version>2</version>"
       << "<listPosition>3</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_4\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_4\" type=\"Sapling\"/>"
       << "</behavior>"
       << "</behaviorList>";

  oOut << "<SailLight1>"
       << "<li_heightOfFishEyePhoto>1</li_heightOfFishEyePhoto>"
       << "<li_beamFractGlobalRad>0.5</li_beamFractGlobalRad>"
       << "<li_clearSkyTransCoeff>0.65</li_clearSkyTransCoeff>"
       << "<li_julianDayGrowthStarts>120</li_julianDayGrowthStarts>"
       << "<li_julianDayGrowthEnds>270</li_julianDayGrowthEnds>"
       << "<li_minSunAngle>0.785</li_minSunAngle>"
       << "<li_lightExtinctionCoefficient>"
       << "<li_lecVal species=\"Species_1\">0.08</li_lecVal>"
       << "<li_lecVal species=\"Species_2\">0.091</li_lecVal>"
       << "<li_lecVal species=\"Species_3\">0.059</li_lecVal>"
       << "<li_lecVal species=\"Species_4\">0.059</li_lecVal>"
       << "</li_lightExtinctionCoefficient>"
       << "<li_maxShadingRadius>15.0</li_maxShadingRadius>"
       << "<li_skyMaskAngle>30.0</li_skyMaskAngle>"
       << "<li_crownFracOfHeight>0</li_crownFracOfHeight>"
       << "</SailLight1>";

  oOut << "<NCIMasterMortality2>"
       << "<nciWhichShadingEffect>" << default_shading << "</nciWhichShadingEffect>"
       << "<nciWhichCrowdingEffect>" << default_crowding_effect << "</nciWhichCrowdingEffect>"
       << "<nciWhichNCITerm>" << default_nci_term << "</nciWhichNCITerm>"
       << "<nciWhichSizeEffect>" << default_size_effect << "</nciWhichSizeEffect>"
       << "<nciWhichDamageEffect>" << no_damage_effect << "</nciWhichDamageEffect>"
       << "<nciWhichPrecipitationEffect>" << no_precip_effect << "</nciWhichPrecipitationEffect>"
       << "<nciWhichTemperatureEffect>" << no_temp_effect << "</nciWhichTemperatureEffect>"
       << "<nciWhichNitrogenEffect>" << no_nitrogen_effect << "</nciWhichNitrogenEffect>"
       << "<nciWhichInfectionEffect>" << no_infection_effect << "</nciWhichInfectionEffect>"
       << "<mo_nciMortSurvPeriod>1</mo_nciMortSurvPeriod>"
       << "<nciMaxCrowdingRadius>"
       << "<nmcrVal species=\"Species_1\">10</nmcrVal>"
       << "<nmcrVal species=\"Species_4\">15</nmcrVal>"
       << "<nmcrVal species=\"Species_2\">10</nmcrVal>"
       << "</nciMaxCrowdingRadius>"
       << "<nciAlpha>"
       << "<naVal species=\"Species_1\">2.17031683</naVal>"
       << "<naVal species=\"Species_2\">2.81</naVal>"
       << "<naVal species=\"Species_4\">1.33</naVal>"
       << "</nciAlpha>"
       << "<nciBeta>"
       << "<nbVal species=\"Species_1\">0.699942</nbVal>"
       << "<nbVal species=\"Species_2\">0.5</nbVal>"
       << "<nbVal species=\"Species_4\">0.09</nbVal>"
       << "</nciBeta>"
       << "<mo_nciMaxPotentialSurvival>"
       << "<mo_nmpsVal species=\"Species_1\">0.98</mo_nmpsVal>"
       << "<mo_nmpsVal species=\"Species_2\">0.99</mo_nmpsVal>"
       << "<mo_nmpsVal species=\"Species_4\">0.97</mo_nmpsVal>"
       << "</mo_nciMaxPotentialSurvival>"
       << "<nciCrowdingGamma>"
       << "<ncgVal species=\"Species_1\">0</ncgVal>"
       << "<ncgVal species=\"Species_2\">-0.13</ncgVal>"
       << "<ncgVal species=\"Species_4\">-0.23</ncgVal>"
       << "</nciCrowdingGamma>"
       << "<nciSizeEffectX0>"
       << "<nsex0Val species=\"Species_1\">34.246</nsex0Val>"
       << "<nsex0Val species=\"Species_2\">122.23</nsex0Val>"
       << "<nsex0Val species=\"Species_4\">16.43</nsex0Val>"
       << "</nciSizeEffectX0>"
       << "<nciSizeEffectXb>"
       << "<nsexbVal species=\"Species_1\">5</nsexbVal>"
       << "<nsexbVal species=\"Species_2\">2.36</nsexbVal>"
       << "<nsexbVal species=\"Species_4\">1.41</nsexbVal>"
       << "</nciSizeEffectXb>"
       << "<nciCrowdingC>"
       << "<nccVal species=\"Species_1\">0.98</nccVal>"
       << "<nccVal species=\"Species_2\">0.57</nccVal>"
       << "<nccVal species=\"Species_4\">0.069</nccVal>"
       << "</nciCrowdingC>"
       << "<nciCrowdingD>"
       << "<ncdVal species=\"Species_1\">0.012</ncdVal>"
       << "<ncdVal species=\"Species_2\">0.056</ncdVal>"
       << "<ncdVal species=\"Species_4\">1</ncdVal>"
       << "</nciCrowdingD>"
       << "<nciStormEffMedDmg>"
       << "<nsemdVal species=\"Species_1\">1</nsemdVal>"
       << "<nsemdVal species=\"Species_2\">1</nsemdVal>"
       << "<nsemdVal species=\"Species_4\">1</nsemdVal>"
       << "</nciStormEffMedDmg>"
       << "<nciStormEffFullDmg>"
       << "<nsefdVal species=\"Species_1\">1</nsefdVal>"
       << "<nsefdVal species=\"Species_2\">1</nsefdVal>"
       << "<nsefdVal species=\"Species_4\">1</nsefdVal>"
       << "</nciStormEffFullDmg>"
       << "<nciNeighStormEffMedDmg>"
       << "<nnsemdVal species=\"Species_1\">1</nnsemdVal>"
       << "<nnsemdVal species=\"Species_2\">1</nnsemdVal>"
       << "<nnsemdVal species=\"Species_4\">1</nnsemdVal>"
       << "</nciNeighStormEffMedDmg>"
       << "<nciNeighStormEffFullDmg>"
       << "<nnsefdVal species=\"Species_1\">1</nnsefdVal>"
       << "<nnsefdVal species=\"Species_2\">1</nnsefdVal>"
       << "<nnsefdVal species=\"Species_4\">1</nnsefdVal>"
       << "</nciNeighStormEffFullDmg>"
       << "<nciSpecies_1NeighborLambda>"
       << "<nlVal species=\"Species_1\">0.664</nlVal>"
       << "<nlVal species=\"Species_2\">0.71</nlVal>"
       << "<nlVal species=\"Species_4\">0.08</nlVal>"
       << "</nciSpecies_1NeighborLambda>"
       << "<nciSpecies_2NeighborLambda>"
       << "<nlVal species=\"Species_1\">0.0044</nlVal>"
       << "<nlVal species=\"Species_2\">0.12</nlVal>"
       << "<nlVal species=\"Species_4\">0.03</nlVal>"
       << "</nciSpecies_2NeighborLambda>"
       << "<nciSpecies_3NeighborLambda>"
       << "<nlVal species=\"Species_1\">0.4181</nlVal>"
       << "<nlVal species=\"Species_2\">0.24</nlVal>"
       << "<nlVal species=\"Species_4\">0.05</nlVal>"
       << "</nciSpecies_3NeighborLambda>"
       << "<nciSpecies_4NeighborLambda>"
       << "<nlVal species=\"Species_1\">0.41812471</nlVal>"
       << "<nlVal species=\"Species_2\">0.24</nlVal>"
       << "<nlVal species=\"Species_4\">0.05</nlVal>"
       << "</nciSpecies_4NeighborLambda>"
       << "<nciShadingCoefficient>"
       << "<nscVal species=\"Species_1\">0.2</nscVal>"
       << "<nscVal species=\"Species_2\">0</nscVal>"
       << "<nscVal species=\"Species_4\">0.5</nscVal>"
       << "</nciShadingCoefficient>"
       << "<nciShadingExponent>"
       << "<nseVal species=\"Species_1\">1</nseVal>"
       << "<nseVal species=\"Species_2\">1</nseVal>"
       << "<nseVal species=\"Species_4\">1</nseVal>"
       << "</nciShadingExponent>"
       << "<nciMinNeighborDBH>"
       << "<nmndVal species=\"Species_1\">10</nmndVal>"
       << "<nmndVal species=\"Species_2\">12</nmndVal>"
       << "<nmndVal species=\"Species_3\">16</nmndVal>"
       << "<nmndVal species=\"Species_4\">14</nmndVal>"
       << "</nciMinNeighborDBH>"
       << "<nciDbhDivisor>100</nciDbhDivisor>"
       << "<nciIncludeSnagsInNCI>0</nciIncludeSnagsInNCI>"
       << "</NCIMasterMortality2>"
       << "</paramFile>";
}

/////////////////////////////////////////////////////////////////////////////
// WriteNCIMortRun5CommonStuff()
/////////////////////////////////////////////////////////////////////////////
void WriteNCIMortRun5CommonStuff( std::fstream &oOut )
{
  using namespace std;
  WriteNCIMortPlotAndTrees(oOut);

  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>Storm</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>StormDamageApplier</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>2</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_4\" type=\"Adult\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>NCIMasterMortality</behaviorName>"
       << "<version>3</version>"
       << "<listPosition>3</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_4\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_4\" type=\"Sapling\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>RemoveDead</behaviorName>"
       << "<version>2</version>"
       << "<listPosition>4</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_4\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_4\" type=\"Sapling\"/>"
       << "</behavior>"
       << "</behaviorList>";

  WriteNCIMortStormParameters(oOut);

  oOut << "<NCIMasterMortality3>"
       << "<nciWhichShadingEffect>" << no_shading << "</nciWhichShadingEffect>"
       << "<nciWhichCrowdingEffect>" << default_crowding_effect << "</nciWhichCrowdingEffect>"
       << "<nciWhichNCITerm>" << nci_with_neighbor_damage << "</nciWhichNCITerm>"
       << "<nciWhichSizeEffect>" << default_size_effect << "</nciWhichSizeEffect>"
       << "<nciWhichDamageEffect>" << default_damage_effect << "</nciWhichDamageEffect>"
       << "<nciWhichPrecipitationEffect>" << no_precip_effect << "</nciWhichPrecipitationEffect>"
       << "<nciWhichTemperatureEffect>" << no_temp_effect << "</nciWhichTemperatureEffect>"
       << "<nciWhichNitrogenEffect>" << no_nitrogen_effect << "</nciWhichNitrogenEffect>"
       << "<nciWhichInfectionEffect>" << no_infection_effect << "</nciWhichInfectionEffect>"
       << "<mo_nciMortSurvPeriod>1</mo_nciMortSurvPeriod>"
       << "<nciMaxCrowdingRadius>"
       << "<nmcrVal species=\"Species_1\">10</nmcrVal>"
       << "<nmcrVal species=\"Species_4\">10</nmcrVal>"
       << "<nmcrVal species=\"Species_2\">10</nmcrVal>"
       << "</nciMaxCrowdingRadius>"
       << "<nciAlpha>"
       << "<naVal species=\"Species_1\">2.17031683</naVal>"
       << "<naVal species=\"Species_2\">2.81</naVal>"
       << "<naVal species=\"Species_4\">1.33</naVal>"
       << "</nciAlpha>"
       << "<nciBeta>"
       << "<nbVal species=\"Species_1\">0.699942</nbVal>"
       << "<nbVal species=\"Species_2\">0.5</nbVal>"
       << "<nbVal species=\"Species_4\">0.09</nbVal>"
       << "</nciBeta>"
       << "<mo_nciMaxPotentialSurvival>"
       << "<mo_nmpsVal species=\"Species_1\">0.98</mo_nmpsVal>"
       << "<mo_nmpsVal species=\"Species_2\">0.99</mo_nmpsVal>"
       << "<mo_nmpsVal species=\"Species_4\">0.97</mo_nmpsVal>"
       << "</mo_nciMaxPotentialSurvival>"
       << "<nciCrowdingGamma>"
       << "<ncgVal species=\"Species_1\">0.43</ncgVal>"
       << "<ncgVal species=\"Species_2\">0.36</ncgVal>"
       << "<ncgVal species=\"Species_4\">-0.4</ncgVal>"
       << "</nciCrowdingGamma>"
       << "<nciSizeEffectX0>"
       << "<nsex0Val species=\"Species_1\">34.24638994</nsex0Val>"
       << "<nsex0Val species=\"Species_2\">122.23</nsex0Val>"
       << "<nsex0Val species=\"Species_4\">16.43</nsex0Val>"
       << "</nciSizeEffectX0>"
       << "<nciSizeEffectXb>"
       << "<nsexbVal species=\"Species_1\">5</nsexbVal>"
       << "<nsexbVal species=\"Species_2\">2.36</nsexbVal>"
       << "<nsexbVal species=\"Species_4\">1.41</nsexbVal>"
       << "</nciSizeEffectXb>"
       << "<nciCrowdingC>"
       << "<nccVal species=\"Species_1\">0.31</nccVal>"
       << "<nccVal species=\"Species_2\">0.236</nccVal>"
       << "<nccVal species=\"Species_4\">0.26</nccVal>"
       << "</nciCrowdingC>"
       << "<nciCrowdingD>"
       << "<ncdVal species=\"Species_1\">0.00118</ncdVal>"
       << "<ncdVal species=\"Species_2\">0.002009</ncdVal>"
       << "<ncdVal species=\"Species_4\">0.00474</ncdVal>"
       << "</nciCrowdingD>"
       << "<nciStormEffMedDmg>"
       << "<nsemdVal species=\"Species_1\">0.89</nsemdVal>"
       << "<nsemdVal species=\"Species_2\">0.9</nsemdVal>"
       << "<nsemdVal species=\"Species_4\">0.78</nsemdVal>"
       << "</nciStormEffMedDmg>"
       << "<nciStormEffFullDmg>"
       << "<nsefdVal species=\"Species_1\">0.42</nsefdVal>"
       << "<nsefdVal species=\"Species_2\">0.34</nsefdVal>"
       << "<nsefdVal species=\"Species_4\">0.63</nsefdVal>"
       << "</nciStormEffFullDmg>"
       << "<nciNeighStormEffMedDmg>"
       << "<nnsemdVal species=\"Species_1\">0.83</nnsemdVal>"
       << "<nnsemdVal species=\"Species_2\">0.33</nnsemdVal>"
       << "<nnsemdVal species=\"Species_4\">0.76</nnsemdVal>"
       << "</nciNeighStormEffMedDmg>"
       << "<nciNeighStormEffFullDmg>"
       << "<nnsefdVal species=\"Species_1\">0.54</nnsefdVal>"
       << "<nnsefdVal species=\"Species_2\">0.27</nnsefdVal>"
       << "<nnsefdVal species=\"Species_4\">0.7</nnsefdVal>"
       << "</nciNeighStormEffFullDmg>"
       << "<nciSpecies_1NeighborLambda>"
       << "<nlVal species=\"Species_1\">0.66401082</nlVal>"
       << "<nlVal species=\"Species_2\">0.71</nlVal>"
       << "<nlVal species=\"Species_4\">0.08</nlVal>"
       << "</nciSpecies_1NeighborLambda>"
       << "<nciSpecies_2NeighborLambda>"
       << "<nlVal species=\"Species_1\">0.00442797</nlVal>"
       << "<nlVal species=\"Species_2\">0.12</nlVal>"
       << "<nlVal species=\"Species_4\">0.03</nlVal>"
       << "</nciSpecies_2NeighborLambda>"
       << "<nciSpecies_3NeighborLambda>"
       << "<nlVal species=\"Species_1\">0.41812471</nlVal>"
       << "<nlVal species=\"Species_2\">0.24</nlVal>"
       << "<nlVal species=\"Species_4\">0.05</nlVal>"
       << "</nciSpecies_3NeighborLambda>"
       << "<nciSpecies_4NeighborLambda>"
       << "<nlVal species=\"Species_1\">0.41812471</nlVal>"
       << "<nlVal species=\"Species_2\">0.24</nlVal>"
       << "<nlVal species=\"Species_4\">0.05</nlVal>"
       << "</nciSpecies_4NeighborLambda>"
       << "<nciShadingCoefficient>"
       << "<nscVal species=\"Species_1\">0</nscVal>"
       << "<nscVal species=\"Species_2\">0</nscVal>"
       << "<nscVal species=\"Species_4\">0</nscVal>"
       << "</nciShadingCoefficient>"
       << "<nciShadingExponent>"
       << "<nseVal species=\"Species_1\">1</nseVal>"
       << "<nseVal species=\"Species_2\">1</nseVal>"
       << "<nseVal species=\"Species_4\">1</nseVal>"
       << "</nciShadingExponent>"
       << "<nciMinNeighborDBH>"
       << "<nmndVal species=\"Species_1\">0</nmndVal>"
       << "<nmndVal species=\"Species_2\">0</nmndVal>"
       << "<nmndVal species=\"Species_3\">0</nmndVal>"
       << "<nmndVal species=\"Species_4\">0</nmndVal>"
       << "</nciMinNeighborDBH>"
       << "<nciDbhDivisor>100</nciDbhDivisor>"
       << "<nciIncludeSnagsInNCI>0</nciIncludeSnagsInNCI>"
       << "</NCIMasterMortality3>"
       << "</paramFile>";
}

/////////////////////////////////////////////////////////////////////////////
// WriteNCIMortRun6CommonStuff()
/////////////////////////////////////////////////////////////////////////////
void WriteNCIMortRun6CommonStuff( std::fstream &oOut )
{
  using namespace std;
  WriteNCIMortPlotAndTrees(oOut);

  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>NCIMasterMortality</behaviorName>"
       << "<version>3</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_4\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_4\" type=\"Sapling\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>RemoveDead</behaviorName>"
       << "<version>2</version>"
       << "<listPosition>2</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_4\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_4\" type=\"Sapling\"/>"
       << "</behavior>"
       << "</behaviorList>";

  oOut << "<NCIMasterMortality1>"
       << "<nciWhichShadingEffect>" << no_shading << "</nciWhichShadingEffect>"
       << "<nciWhichCrowdingEffect>" << no_crowding_effect << "</nciWhichCrowdingEffect>"
       << "<nciWhichNCITerm>" << no_nci_term << "</nciWhichNCITerm>"
       << "<nciWhichSizeEffect>" << default_size_effect << "</nciWhichSizeEffect>"
       << "<nciWhichDamageEffect>" << no_damage_effect << "</nciWhichDamageEffect>"
       << "<nciWhichPrecipitationEffect>" << no_precip_effect << "</nciWhichPrecipitationEffect>"
       << "<nciWhichTemperatureEffect>" << no_temp_effect << "</nciWhichTemperatureEffect>"
       << "<nciWhichNitrogenEffect>" << no_nitrogen_effect << "</nciWhichNitrogenEffect>"
       << "<nciWhichInfectionEffect>" << no_infection_effect << "</nciWhichInfectionEffect>"
       << "<mo_nciMortSurvPeriod>3</mo_nciMortSurvPeriod>"
       << "<mo_nciMaxPotentialSurvival>"
       << "<mo_nmpsVal species=\"Species_1\">0.98</mo_nmpsVal>"
       << "<mo_nmpsVal species=\"Species_2\">0.99</mo_nmpsVal>"
       << "<mo_nmpsVal species=\"Species_4\">0.97</mo_nmpsVal>"
       << "</mo_nciMaxPotentialSurvival>"
       << "<nciSizeEffectX0>"
       << "<nsex0Val species=\"Species_1\">34.24</nsex0Val>"
       << "<nsex0Val species=\"Species_2\">122.23</nsex0Val>"
       << "<nsex0Val species=\"Species_4\">16.43</nsex0Val>"
       << "</nciSizeEffectX0>"
       << "<nciSizeEffectXb>"
       << "<nsexbVal species=\"Species_1\">5</nsexbVal>"
       << "<nsexbVal species=\"Species_2\">2.36</nsexbVal>"
       << "<nsexbVal species=\"Species_4\">1.41</nsexbVal>"
       << "</nciSizeEffectXb>"
       << "</NCIMasterMortality1>"
       << "</paramFile>";
}

/////////////////////////////////////////////////////////////////////////////
// WriteNCIMortCommonErrorStuff()
/////////////////////////////////////////////////////////////////////////////
void WriteNCIMortCommonErrorStuff( std::fstream &oOut )
{
  using namespace std;
  oOut << "<randomSeed>1</randomSeed>"
       << "<plot_lenX>200.0</plot_lenX>"
       << "<plot_lenY>200.0</plot_lenY>"
       << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
       << "<plot_temp_C>12.88171785</plot_temp_C>"
       << "<plot_latitude>55.37</plot_latitude>"
       << "</plot>"
       << "<trees>"
       << "<tr_speciesList>"
       << "<tr_species speciesName=\"Species_1\" />"
       << "<tr_species speciesName=\"Species_2\" />"
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
       << "<tr_stdMaxCrownRad>"
       << "<tr_smcrVal species=\"Species_1\">10</tr_smcrVal>"
       << "<tr_smcrVal species=\"Species_2\">10</tr_smcrVal>"
       << "</tr_stdMaxCrownRad>"
       << "<tr_conversionDiam10ToDBH>"
       << "<tr_cdtdVal species=\"Species_1\">0.8008</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_2\">0.8008</tr_cdtdVal>"
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
       << "</allometry>"
       << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>Storm</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>StormDamageApplier</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>2</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>NCIMasterMortality</behaviorName>"
       << "<version>3</version>"
       << "<listPosition>3</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>RemoveDead</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>5</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
       << "</behavior>"
       << "</behaviorList>";

  WriteNCIMortStormParameters(oOut);
}

////////////////////////////////////////////////////////////////////////////
// WriteNCIMortXMLErrorFile13()
////////////////////////////////////////////////////////////////////////////
const char* WriteNCIMortXMLErrorFile13() {
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

  WriteNCIMortCommonErrorStuff(oOut);

  oOut << "<NCIMasterMortality3>"
       << "<nciWhichShadingEffect>" << default_shading << "</nciWhichShadingEffect>"
       << "<nciWhichCrowdingEffect>" << default_crowding_effect << "</nciWhichCrowdingEffect>"
       << "<nciWhichNCITerm>2</nciWhichNCITerm>"
       << "<nciWhichSizeEffect>" << default_size_effect << "</nciWhichSizeEffect>"
       << "<nciWhichDamageEffect>" << default_damage_effect << "</nciWhichDamageEffect>"
       << "<nciWhichPrecipitationEffect>" << no_precip_effect << "</nciWhichPrecipitationEffect>"
       << "<nciWhichTemperatureEffect>" << no_temp_effect << "</nciWhichTemperatureEffect>"
       << "<nciWhichNitrogenEffect>" << no_nitrogen_effect << "</nciWhichNitrogenEffect>"
       << "<nciWhichInfectionEffect>" << no_infection_effect << "</nciWhichInfectionEffect>"
       << "<mo_nciMortSurvPeriod>1</mo_nciMortSurvPeriod>"
       << "<nciMaxCrowdingRadius>"
       << "<nmcrVal species=\"Species_1\">10</nmcrVal>"
       << "<nmcrVal species=\"Species_4\">10</nmcrVal>"
       << "<nmcrVal species=\"Species_2\">10</nmcrVal>"
       << "</nciMaxCrowdingRadius>"
       << "<nciAlpha>"
       << "<naVal species=\"Species_1\">2.17031683</naVal>"
       << "<naVal species=\"Species_2\">2.81</naVal>"
       << "<naVal species=\"Species_4\">1.33</naVal>"
       << "</nciAlpha>"
       << "<nciBeta>"
       << "<nbVal species=\"Species_1\">0.699942</nbVal>"
       << "<nbVal species=\"Species_2\">0.5</nbVal>"
       << "<nbVal species=\"Species_4\">0.09</nbVal>"
       << "</nciBeta>"
       << "<mo_nciMaxPotentialSurvival>"
       << "<mo_nmpsVal species=\"Species_1\">0.98</mo_nmpsVal>"
       << "<mo_nmpsVal species=\"Species_2\">0.99</mo_nmpsVal>"
       << "<mo_nmpsVal species=\"Species_4\">0.97</mo_nmpsVal>"
       << "</mo_nciMaxPotentialSurvival>"
       << "<nciCrowdingGamma>"
       << "<ncgVal species=\"Species_1\">0.43</ncgVal>"
       << "<ncgVal species=\"Species_2\">0.36</ncgVal>"
       << "<ncgVal species=\"Species_4\">-0.4</ncgVal>"
       << "</nciCrowdingGamma>"
       << "<nciSizeEffectX0>"
       << "<nsex0Val species=\"Species_1\">34.24638994</nsex0Val>"
       << "<nsex0Val species=\"Species_2\">122.23</nsex0Val>"
       << "<nsex0Val species=\"Species_4\">16.43</nsex0Val>"
       << "</nciSizeEffectX0>"
       << "<nciSizeEffectXb>"
       << "<nsexbVal species=\"Species_1\">5</nsexbVal>"
       << "<nsexbVal species=\"Species_2\">2.36</nsexbVal>"
       << "<nsexbVal species=\"Species_4\">1.41</nsexbVal>"
       << "</nciSizeEffectXb>"
       << "<nciCrowdingC>"
       << "<nccVal species=\"Species_1\">1.63</nccVal>"
       << "<nccVal species=\"Species_2\">1.26</nccVal>"
       << "<nccVal species=\"Species_4\">1.63</nccVal>"
       << "</nciCrowdingC>"
       << "<nciCrowdingD>"
       << "<ncdVal species=\"Species_1\">0.9</ncdVal>"
       << "<ncdVal species=\"Species_2\">0.78</ncdVal>"
       << "<ncdVal species=\"Species_4\">0.84</ncdVal>"
       << "</nciCrowdingD>"
       << "<nciStormEffMedDmg>"
       << "<nsemdVal species=\"Species_1\">0.89</nsemdVal>"
       << "<nsemdVal species=\"Species_2\">0.9</nsemdVal>"
       << "<nsemdVal species=\"Species_4\">0.78</nsemdVal>"
       << "</nciStormEffMedDmg>"
       << "<nciStormEffFullDmg>"
       << "<nsefdVal species=\"Species_1\">0.42</nsefdVal>"
       << "<nsefdVal species=\"Species_2\">0.34</nsefdVal>"
       << "<nsefdVal species=\"Species_4\">0.63</nsefdVal>"
       << "</nciStormEffFullDmg>"
       << "<nciNeighStormEffMedDmg>"
       << "<nnsemdVal species=\"Species_1\">0.83</nnsemdVal>"
       << "<nnsemdVal species=\"Species_2\">0.33</nnsemdVal>"
       << "<nnsemdVal species=\"Species_4\">0.76</nnsemdVal>"
       << "<nnsemdVal species=\"Species_3\">0.76</nnsemdVal>"
       << "</nciNeighStormEffMedDmg>"
       << "<nciNeighStormEffFullDmg>"
       << "<nnsefdVal species=\"Species_1\">0.54</nnsefdVal>"
       << "<nnsefdVal species=\"Species_2\">0.27</nnsefdVal>"
       << "<nnsefdVal species=\"Species_4\">0.7</nnsefdVal>"
       << "<nnsefdVal species=\"Species_3\">0.7</nnsefdVal>"
       << "</nciNeighStormEffFullDmg>"
       << "<nciSpecies_1NeighborLambda>"
       << "<nlVal species=\"Species_1\">0.66401082</nlVal>"
       << "<nlVal species=\"Species_2\">0.71</nlVal>"
       << "<nlVal species=\"Species_4\">0.08</nlVal>"
       << "</nciSpecies_1NeighborLambda>"
       << "<nciSpecies_2NeighborLambda>"
       << "<nlVal species=\"Species_1\">0.00442797</nlVal>"
       << "<nlVal species=\"Species_2\">0.12</nlVal>"
       << "<nlVal species=\"Species_4\">0.03</nlVal>"
       << "</nciSpecies_2NeighborLambda>"
       << "<nciSpecies_3NeighborLambda>"
       << "<nlVal species=\"Species_1\">0.41812471</nlVal>"
       << "<nlVal species=\"Species_2\">0.24</nlVal>"
       << "<nlVal species=\"Species_4\">0.05</nlVal>"
       << "</nciSpecies_3NeighborLambda>"
       << "<nciSpecies_4NeighborLambda>"
       << "<nlVal species=\"Species_1\">0.41812471</nlVal>"
       << "<nlVal species=\"Species_2\">0.24</nlVal>"
       << "<nlVal species=\"Species_4\">0.05</nlVal>"
       << "</nciSpecies_4NeighborLambda>"
       << "<nciShadingCoefficient>"
       << "<nscVal species=\"Species_1\">0.8</nscVal>"
       << "<nscVal species=\"Species_2\">0</nscVal>"
       << "<nscVal species=\"Species_4\">0</nscVal>"
       << "</nciShadingCoefficient>"
       << "<nciShadingExponent>"
       << "<nseVal species=\"Species_1\">1</nseVal>"
       << "<nseVal species=\"Species_2\">1</nseVal>"
       << "<nseVal species=\"Species_4\">1</nseVal>"
       << "</nciShadingExponent>"
       << "<nciMinNeighborDBH>"
       << "<nmndVal species=\"Species_1\">0</nmndVal>"
       << "<nmndVal species=\"Species_2\">0</nmndVal>"
       << "<nmndVal species=\"Species_3\">0</nmndVal>"
       << "<nmndVal species=\"Species_4\">0</nmndVal>"
       << "</nciMinNeighborDBH>"
       << "<nciDbhDivisor>100</nciDbhDivisor>"
       << "<nciIncludeSnagsInNCI>0</nciIncludeSnagsInNCI>"
       << "</NCIMasterMortality3>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}
