//---------------------------------------------------------------------------
// TestWeibullClimateSurvival.cpp
//---------------------------------------------------------------------------
#include "TestWeibullClimateSurvival.h"
#include <gtest/gtest.h>
#include <fstream>
#include <math.h>
#include "TreePopulation.h"
#include "SimManager.h"
#include "BehaviorBase.h"
#include "NCIEffectsList.h"

using namespace std;

////////////////////////////////////////////////////////////////////////////
// TestErrorProcessing()
////////////////////////////////////////////////////////////////////////////
TEST(WeibullClimateSurvival, TestErrorProcessing) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    p_oSimManager->ReadFile(WriteWeibullClimateSurvivalXMLErrorFile1());
    FAIL() << "TestWeibullClimateSurvival error processing didn't catch error for WriteWeibullClimateSurvivalXMLErrorFile1.";
  } catch (modelErr& err) {
    if (err.sFunction.compare("clNCILargerNeighbors::DoSetup") != 0) {
      FAIL() << "TestWeibullClimateSurvival error processing caught wrong error for WriteWeibullClimateSurvivalXMLErrorFile1.";
    };
  }

  try {
    p_oSimManager->ReadFile(WriteWeibullClimateSurvivalXMLErrorFile2());
    FAIL() << "TestWeibullClimateSurvival error processing didn't catch error for WriteWeibullClimateSurvivalXMLErrorFile2.";
  } catch (modelErr& err) {
    if (err.sFunction.compare("clNCIMasterMortality::DoShellSetup") != 0) {
      FAIL() << "TestWeibullClimateSurvival error processing caught wrong error for WriteWeibullClimateSurvivalXMLErrorFile2.";
    };
  }

  try {
    p_oSimManager->ReadFile(WriteWeibullClimateSurvivalXMLErrorFile3());
    FAIL() << "TestWeibullClimateSurvival error processing didn't catch error for WriteWeibullClimateSurvivalXMLErrorFile3.";
  } catch (modelErr& err) {
    if (err.sFunction.compare("clSizeEffectLowerBounded::DoSetup") != 0) {
      FAIL() << "TestWeibullClimateSurvival error processing caught wrong error for WriteWeibullClimateSurvivalXMLErrorFile3.";
    };
  }

  try {
    p_oSimManager->ReadFile(WriteWeibullClimateSurvivalXMLErrorFile4());
    FAIL() << "TestWeibullClimateSurvival error processing didn't catch error for WriteWeibullClimateSurvivalXMLErrorFile4.";
  } catch (modelErr& err) {
    if (err.sFunction.compare("clSizeEffectLowerBounded::DoSetup") != 0) {
      FAIL() << "TestWeibullClimateSurvival error processing caught wrong error for WriteWeibullClimateSurvivalXMLErrorFile4.";
    };
  }

  try {
    p_oSimManager->ReadFile(WriteWeibullClimateSurvivalXMLErrorFile5());
    FAIL() << "TestWeibullClimateSurvival error processing didn't catch error for WriteWeibullClimateSurvivalXMLErrorFile5.";
  } catch (modelErr& err) {
    if (err.sFunction.compare("clPrecipitationEffectWeibull::DoSetup") != 0) {
      FAIL() << "TestWeibullClimateSurvival error processing caught wrong error for WriteWeibullClimateSurvivalXMLErrorFile5.";
    };
  }

  try {
    p_oSimManager->ReadFile(WriteWeibullClimateSurvivalXMLErrorFile6());
    FAIL() << "TestWeibullClimateSurvival error processing didn't catch error for WriteWeibullClimateSurvivalXMLErrorFile5.";
  } catch (modelErr& err) {
    if (err.sFunction.compare("clTemperatureEffectWeibull::DoSetup") != 0) {
      FAIL() << "TestWeibullClimateSurvival error processing caught wrong error for WriteWeibullClimateSurvivalXMLErrorFile5.";
    };
  }
  delete p_oSimManager;
}

////////////////////////////////////////////////////////////////////////////
// TestRun1()
// Performs a test run of survival. WriteWeibullClimateSurvivalXMLFile1() performs setup for a
// 1-year timestep.
////////////////////////////////////////////////////////////////////////////
TEST(WeibullClimateSurvival, TestRun1) {

  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    clTreePopulation * p_oPop;
    clTreeSearch *p_oAllTrees;
    clTree *p_oTree;
    float fDiam, fTestDiam, fExpected;
    int iSpecies, i, iCount;

    /////////////////////////////////////
    // # 1
    p_oSimManager->ReadFile(WriteWeibullClimateSurvivalXMLFile(1));
    p_oPop = (clTreePopulation *) p_oSimManager->GetPopulationObject(
        "treepopulation");

    CreateWeibullClimateSurvivalTrees(p_oPop);
    //Create 999 more of our target
    fDiam = 11;
    iSpecies = 1;
    for (i = 0; i < 999; i++) {
      p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, fDiam);
    }

    //Now do the run and count the targets
    p_oSimManager->RunSim(1);
    iCount = 0;
    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {
      if (p_oTree->GetType() == clTreePopulation::adult &&
          p_oTree->GetSpecies() == iSpecies) {
        p_oTree->GetValue(p_oPop->GetDbhCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTestDiam);
        if (fabs(fDiam - fTestDiam) < 0.001) iCount++;
      }
      p_oTree = p_oAllTrees->NextTree();
    }
    fExpected = 861.26;
    EXPECT_LT(fabs(iCount - fExpected)/fExpected, 0.1);

    /////////////////////////////////////
    // # 2
    p_oSimManager->ReadFile(WriteWeibullClimateSurvivalXMLFile(1));
    p_oPop = (clTreePopulation *) p_oSimManager->GetPopulationObject(
        "treepopulation");

    CreateWeibullClimateSurvivalTrees(p_oPop);
    //Create 999 more of our target
    fDiam = 10.5;
    iSpecies = 1;
    for (i = 0; i < 999; i++) {
      p_oPop->CreateTree(50, 50, iSpecies, clTreePopulation::adult, fDiam);
    }

    //Now do the run and count the targets
    p_oSimManager->RunSim(1);
    iCount = 0;
    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {
      if (p_oTree->GetType() == clTreePopulation::adult &&
          p_oTree->GetSpecies() == iSpecies) {
        p_oTree->GetValue(p_oPop->GetDbhCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTestDiam);
        if (fabs(fDiam - fTestDiam) < 0.001) iCount++;
      }
      p_oTree = p_oAllTrees->NextTree();
    }
    fExpected = 562.82;
    EXPECT_LT(fabs(iCount - fExpected)/fExpected, 0.1);

    /////////////////////////////////////
    // # 3
    p_oSimManager->ReadFile(WriteWeibullClimateSurvivalXMLFile(1));
    p_oPop = (clTreePopulation *) p_oSimManager->GetPopulationObject(
        "treepopulation");

    CreateWeibullClimateSurvivalTrees(p_oPop);
    //Create 999 more of our target
    fDiam = 15;
    iSpecies = 2;
    for (i = 0; i < 999; i++) {
      p_oPop->CreateTree(53, 52, iSpecies, clTreePopulation::adult, fDiam);
    }

    //Now do the run and count the targets
    p_oSimManager->RunSim(1);
    iCount = 0;
    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {
      if (p_oTree->GetType() == clTreePopulation::adult &&
          p_oTree->GetSpecies() == iSpecies) {
        p_oTree->GetValue(p_oPop->GetDbhCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTestDiam);
        if (fabs(fDiam - fTestDiam) < 0.001) iCount++;
      }
      p_oTree = p_oAllTrees->NextTree();
    }
    EXPECT_EQ(iCount, 0);

    /////////////////////////////////////
    // # 4
    p_oSimManager->ReadFile(WriteWeibullClimateSurvivalXMLFile(1));
    p_oPop = (clTreePopulation *) p_oSimManager->GetPopulationObject(
        "treepopulation");

    CreateWeibullClimateSurvivalTrees(p_oPop);
    //Create 999 more of our target
    fDiam = 25;
    iSpecies = 3;
    for (i = 0; i < 999; i++) {
      p_oPop->CreateTree(59, 50, iSpecies, clTreePopulation::adult, fDiam);
    }

    //Now do the run and count the targets
    p_oSimManager->RunSim(1);
    iCount = 0;
    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {
      if (p_oTree->GetType() == clTreePopulation::adult &&
          p_oTree->GetSpecies() == iSpecies) {
        p_oTree->GetValue(p_oPop->GetDbhCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTestDiam);
        if (fabs(fDiam - fTestDiam) < 0.001) iCount++;
      }
      p_oTree = p_oAllTrees->NextTree();
    }
    fExpected = 913.85;
    EXPECT_LT(fabs(iCount - fExpected)/fExpected, 0.1);

    /////////////////////////////////////
    // # 5
    p_oSimManager->ReadFile(WriteWeibullClimateSurvivalXMLFile(1));
    p_oPop = (clTreePopulation *) p_oSimManager->GetPopulationObject(
        "treepopulation");

    CreateWeibullClimateSurvivalTrees(p_oPop);
    //Create 999 more of our target
    fDiam = 30;
    iSpecies = 1;
    for (i = 0; i < 999; i++) {
      p_oPop->CreateTree(50, 59, iSpecies, clTreePopulation::adult, fDiam);
    }

    //Now do the run and count the targets
    p_oSimManager->RunSim(1);
    iCount = 0;
    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {
      if (p_oTree->GetType() == clTreePopulation::adult &&
          p_oTree->GetSpecies() == iSpecies) {
        p_oTree->GetValue(p_oPop->GetDbhCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTestDiam);
        if (fabs(fDiam - fTestDiam) < 0.001) iCount++;
      }
      p_oTree = p_oAllTrees->NextTree();
    }
    fExpected = 921.62;
    EXPECT_LT(fabs(iCount - fExpected)/fExpected, 0.1);

    /////////////////////////////////////
    // # 6
    p_oSimManager->ReadFile(WriteWeibullClimateSurvivalXMLFile(1));
    p_oPop = (clTreePopulation *) p_oSimManager->GetPopulationObject(
        "treepopulation");

    CreateWeibullClimateSurvivalTrees(p_oPop);
    //Create 999 more of our target
    fDiam = 45;
    iSpecies = 2;
    for (i = 0; i < 999; i++) {
      p_oPop->CreateTree(55, 55, iSpecies, clTreePopulation::adult, fDiam);
    }

    //Now do the run and count the targets
    p_oSimManager->RunSim(1);
    iCount = 0;
    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {
      if (p_oTree->GetType() == clTreePopulation::adult &&
          p_oTree->GetSpecies() == iSpecies) {
        p_oTree->GetValue(p_oPop->GetDbhCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTestDiam);
        if (fabs(fDiam - fTestDiam) < 0.001) iCount++;
      }
      p_oTree = p_oAllTrees->NextTree();
    }
    fExpected = 956.61;
    EXPECT_LT(fabs(iCount - fExpected)/fExpected, 0.1);

    /////////////////////////////////////
    // # 7
    p_oSimManager->ReadFile(WriteWeibullClimateSurvivalXMLFile(1));
    p_oPop = (clTreePopulation *) p_oSimManager->GetPopulationObject(
        "treepopulation");

    CreateWeibullClimateSurvivalTrees(p_oPop);
    //Create 999 more of our target
    fDiam = 15;
    iSpecies = 3;
    for (i = 0; i < 999; i++) {
      p_oPop->CreateTree(60, 61, iSpecies, clTreePopulation::adult, fDiam);
    }

    //Now do the run and count the targets
    p_oSimManager->RunSim(1);
    iCount = 0;
    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {
      if (p_oTree->GetType() == clTreePopulation::adult &&
          p_oTree->GetSpecies() == iSpecies) {
        p_oTree->GetValue(p_oPop->GetDbhCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTestDiam);
        if (fabs(fDiam - fTestDiam) < 0.001) iCount++;
      }
      p_oTree = p_oAllTrees->NextTree();
    }
    fExpected = 702.52;
    EXPECT_LT(fabs(iCount - fExpected)/fExpected, 0.1);

    /////////////////////////////////////
    // # 8
    p_oSimManager->ReadFile(WriteWeibullClimateSurvivalXMLFile(1));
    p_oPop = (clTreePopulation *) p_oSimManager->GetPopulationObject(
        "treepopulation");

    CreateWeibullClimateSurvivalTrees(p_oPop);
    //Create 999 more of our target
    fDiam = 4;
    iSpecies = 1;
    for (i = 0; i < 999; i++) {
      p_oPop->CreateTree(52, 52, iSpecies, clTreePopulation::sapling, fDiam);
    }

    //Now do the run and count the targets
    p_oSimManager->RunSim(1);
    iCount = 0;
    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {
      if (p_oTree->GetType() == clTreePopulation::sapling &&
          p_oTree->GetSpecies() == iSpecies) {
        p_oTree->GetValue(p_oPop->GetDbhCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTestDiam);
        if (fabs(fDiam - fTestDiam) < 0.001) iCount++;
      }
      p_oTree = p_oAllTrees->NextTree();
    }
    fExpected = 187.49;
    EXPECT_LT(fabs(iCount - fExpected)/fExpected, 0.1);

    /////////////////////////////////////
    // # 9
    p_oSimManager->ReadFile(WriteWeibullClimateSurvivalXMLFile(1));
    p_oPop = (clTreePopulation *) p_oSimManager->GetPopulationObject(
        "treepopulation");

    CreateWeibullClimateSurvivalTrees(p_oPop);
    //Create 999 more of our target
    fDiam = 4;
    iSpecies = 2;
    for (i = 0; i < 999; i++) {
      p_oPop->CreateTree(53, 53, iSpecies, clTreePopulation::sapling, fDiam);
    }

    //Now do the run and count the targets
    p_oSimManager->RunSim(1);
    iCount = 0;
    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {
      if (p_oTree->GetType() == clTreePopulation::sapling &&
          p_oTree->GetSpecies() == iSpecies) {
        p_oTree->GetValue(p_oPop->GetDbhCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTestDiam);
        if (fabs(fDiam - fTestDiam) < 0.001) iCount++;
      }
      p_oTree = p_oAllTrees->NextTree();
    }
    fExpected = 200.45;
    EXPECT_LT(fabs(iCount - fExpected)/fExpected, 0.1);

    /////////////////////////////////////
    // # 10
    p_oSimManager->ReadFile(WriteWeibullClimateSurvivalXMLFile(1));
    p_oPop = (clTreePopulation *) p_oSimManager->GetPopulationObject(
        "treepopulation");

    CreateWeibullClimateSurvivalTrees(p_oPop);
    //Create 999 more of our target
    fDiam = 11;
    iSpecies = 1;
    for (i = 0; i < 999; i++) {
      p_oPop->CreateTree(20, 20, iSpecies, clTreePopulation::adult, fDiam);
    }

    //Now do the run and count the targets
    p_oSimManager->RunSim(1);
    iCount = 0;
    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {
      if (p_oTree->GetType() == clTreePopulation::adult &&
          p_oTree->GetSpecies() == iSpecies) {
        p_oTree->GetValue(p_oPop->GetDbhCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTestDiam);
        if (fabs(fDiam - fTestDiam) < 0.001) iCount++;
      }
      p_oTree = p_oAllTrees->NextTree();
    }
    fExpected = 861.26;
    EXPECT_LT(fabs(iCount - fExpected)/fExpected, 0.1);

    /////////////////////////////////////
    // # 11
    p_oSimManager->ReadFile(WriteWeibullClimateSurvivalXMLFile(1));
    p_oPop = (clTreePopulation *) p_oSimManager->GetPopulationObject(
        "treepopulation");

    CreateWeibullClimateSurvivalTrees(p_oPop);
    //Create 999 more of our target
    fDiam = 2;
    iSpecies = 1;
    for (i = 0; i < 999; i++) {
      p_oPop->CreateTree(50.1, 50.1, iSpecies, clTreePopulation::sapling, fDiam);
    }

    //Now do the run and count the targets
    p_oSimManager->RunSim(1);
    iCount = 0;
    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {
      if (p_oTree->GetType() == clTreePopulation::sapling &&
          p_oTree->GetSpecies() == iSpecies) {
        p_oTree->GetValue(p_oPop->GetDbhCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTestDiam);
        if (fabs(fDiam - fTestDiam) < 0.001) iCount++;
      }
      p_oTree = p_oAllTrees->NextTree();
    }
    fExpected = 149.38;
    EXPECT_LT(fabs(iCount - fExpected)/fExpected, 0.1);

    /////////////////////////////////////
    // # 12
    p_oSimManager->ReadFile(WriteWeibullClimateSurvivalXMLFile(1));
    p_oPop = (clTreePopulation *) p_oSimManager->GetPopulationObject(
        "treepopulation");

    CreateWeibullClimateSurvivalTrees(p_oPop);
    //Create 999 more of our target
    fDiam = 3;
    iSpecies = 2;
    for (i = 0; i < 999; i++) {
      p_oPop->CreateTree(53.1, 52.1, iSpecies, clTreePopulation::sapling, fDiam);
    }

    //Now do the run and count the targets
    p_oSimManager->RunSim(1);
    iCount = 0;
    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {
      if (p_oTree->GetType() == clTreePopulation::sapling &&
          p_oTree->GetSpecies() == iSpecies) {
        p_oTree->GetValue(p_oPop->GetDbhCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTestDiam);
        if (fabs(fDiam - fTestDiam) < 0.001) iCount++;
      }
      p_oTree = p_oAllTrees->NextTree();
    }
    fExpected = 170.61;
    EXPECT_LT(fabs(iCount - fExpected)/fExpected, 0.1);

    /////////////////////////////////////
    // # 13
    p_oSimManager->ReadFile(WriteWeibullClimateSurvivalXMLFile(1));
    p_oPop = (clTreePopulation *) p_oSimManager->GetPopulationObject(
        "treepopulation");

    CreateWeibullClimateSurvivalTrees(p_oPop);
    //Create 999 more of our target
    fDiam = 6;
    iSpecies = 3;
    for (i = 0; i < 999; i++) {
      p_oPop->CreateTree(59.1, 50.1, iSpecies, clTreePopulation::sapling, fDiam);
    }

    //Now do the run and count the targets
    p_oSimManager->RunSim(1);
    iCount = 0;
    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {
      if (p_oTree->GetType() == clTreePopulation::sapling &&
          p_oTree->GetSpecies() == iSpecies) {
        p_oTree->GetValue(p_oPop->GetDbhCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTestDiam);
        if (fabs(fDiam - fTestDiam) < 0.001) iCount++;
      }
      p_oTree = p_oAllTrees->NextTree();
    }
    fExpected = 196.95;
    EXPECT_LT(fabs(iCount - fExpected)/fExpected, 0.1);

    /////////////////////////////////////
    // # 14
    p_oSimManager->ReadFile(WriteWeibullClimateSurvivalXMLFile(1));
    p_oPop = (clTreePopulation *) p_oSimManager->GetPopulationObject(
        "treepopulation");

    CreateWeibullClimateSurvivalTrees(p_oPop);
    //Create 999 more of our target
    fDiam = 7;
    iSpecies = 1;
    for (i = 0; i < 999; i++) {
      p_oPop->CreateTree(50.1, 59.1, iSpecies, clTreePopulation::sapling, fDiam);
    }

    //Now do the run and count the targets
    p_oSimManager->RunSim(1);
    iCount = 0;
    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {
      if (p_oTree->GetType() == clTreePopulation::sapling &&
          p_oTree->GetSpecies() == iSpecies) {
        p_oTree->GetValue(p_oPop->GetDbhCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTestDiam);
        if (fabs(fDiam - fTestDiam) < 0.001) iCount++;
      }
      p_oTree = p_oAllTrees->NextTree();
    }
    fExpected = 331.16;
    EXPECT_LT(fabs(iCount - fExpected)/fExpected, 0.1);

    /////////////////////////////////////
    // # 15
    p_oSimManager->ReadFile(WriteWeibullClimateSurvivalXMLFile(1));
    p_oPop = (clTreePopulation *) p_oSimManager->GetPopulationObject(
        "treepopulation");

    CreateWeibullClimateSurvivalTrees(p_oPop);
    //Create 999 more of our target
    fDiam = 8;
    iSpecies = 2;
    for (i = 0; i < 999; i++) {
      p_oPop->CreateTree(50.1, 59.1, iSpecies, clTreePopulation::sapling, fDiam);
    }

    //Now do the run and count the targets
    p_oSimManager->RunSim(1);
    iCount = 0;
    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {
      if (p_oTree->GetType() == clTreePopulation::sapling &&
          p_oTree->GetSpecies() == iSpecies) {
        p_oTree->GetValue(p_oPop->GetDbhCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTestDiam);
        if (fabs(fDiam - fTestDiam) < 0.001) iCount++;
      }
      p_oTree = p_oAllTrees->NextTree();
    }
    fExpected = 438.88;
    EXPECT_LT(fabs(iCount - fExpected)/fExpected, 0.1);

    /////////////////////////////////////
    // # 16
    p_oSimManager->ReadFile(WriteWeibullClimateSurvivalXMLFile(1));
    p_oPop = (clTreePopulation *) p_oSimManager->GetPopulationObject(
        "treepopulation");

    CreateWeibullClimateSurvivalTrees(p_oPop);
    //Create 999 more of our target
    fDiam = 9;
    iSpecies = 3;
    for (i = 0; i < 999; i++) {
      p_oPop->CreateTree(60.1, 61.1, iSpecies, clTreePopulation::sapling, fDiam);
    }

    //Now do the run and count the targets
    p_oSimManager->RunSim(1);
    iCount = 0;
    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {
      if (p_oTree->GetType() == clTreePopulation::sapling &&
          p_oTree->GetSpecies() == iSpecies) {
        p_oTree->GetValue(p_oPop->GetDbhCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTestDiam);
        if (fabs(fDiam - fTestDiam) < 0.001) iCount++;
      }
      p_oTree = p_oAllTrees->NextTree();
    }
    fExpected = 161.42;
    EXPECT_LT(fabs(iCount - fExpected)/fExpected, 0.1);
    delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

////////////////////////////////////////////////////////////////////////////
// TestRun2()
// Performs a test run of survival. WriteWeibullClimateSurvivalXMLFile2() performs setup for a
// 3-year timestep.
////////////////////////////////////////////////////////////////////////////
TEST(WeibullClimateSurvival, TestRun2) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    clTreePopulation * p_oPop;
    clTreeSearch *p_oAllTrees;
    clTree *p_oTree;
    float fDiam, fTestDiam, fExpected;
    int iSpecies, i, iCount;

    /////////////////////////////////////
    // # 1
    p_oSimManager->ReadFile(WriteWeibullClimateSurvivalXMLFile(3));
    p_oPop = (clTreePopulation *) p_oSimManager->GetPopulationObject(
        "treepopulation");

    CreateWeibullClimateSurvivalTrees(p_oPop);
    //Create 999 more of our target
    fDiam = 11;
    iSpecies = 1;
    for (i = 0; i < 999; i++) {
      p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, fDiam);
    }

    //Now do the run and count the targets
    p_oSimManager->RunSim(1);
    iCount = 0;
    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {
      if (p_oTree->GetType() == clTreePopulation::adult &&
          p_oTree->GetSpecies() == iSpecies) {
        p_oTree->GetValue(p_oPop->GetDbhCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTestDiam);
        if (fabs(fDiam - fTestDiam) < 0.001) iCount++;
      }
      p_oTree = p_oAllTrees->NextTree();
    }
    fExpected = 638.87;
    EXPECT_LT(fabs(iCount - fExpected)/fExpected, 0.1);

    /////////////////////////////////////
    // # 2
    p_oSimManager->ReadFile(WriteWeibullClimateSurvivalXMLFile(3));
    p_oPop = (clTreePopulation *) p_oSimManager->GetPopulationObject(
        "treepopulation");

    CreateWeibullClimateSurvivalTrees(p_oPop);
    //Create 999 more of our target
    fDiam = 10.5;
    iSpecies = 1;
    for (i = 0; i < 999; i++) {
      p_oPop->CreateTree(50, 50, iSpecies, clTreePopulation::adult, fDiam);
    }

    //Now do the run and count the targets
    p_oSimManager->RunSim(1);
    iCount = 0;
    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {
      if (p_oTree->GetType() == clTreePopulation::adult &&
          p_oTree->GetSpecies() == iSpecies) {
        p_oTree->GetValue(p_oPop->GetDbhCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTestDiam);
        if (fabs(fDiam - fTestDiam) < 0.001) iCount++;
      }
      p_oTree = p_oAllTrees->NextTree();
    }
    fExpected = 178.28;
    EXPECT_LT(fabs(iCount - fExpected)/fExpected, 0.1);

    /////////////////////////////////////
    // # 3
    p_oSimManager->ReadFile(WriteWeibullClimateSurvivalXMLFile(3));
    p_oPop = (clTreePopulation *) p_oSimManager->GetPopulationObject(
        "treepopulation");

    CreateWeibullClimateSurvivalTrees(p_oPop);
    //Create 999 more of our target
    fDiam = 15;
    iSpecies = 2;
    for (i = 0; i < 999; i++) {
      p_oPop->CreateTree(53, 52, iSpecies, clTreePopulation::adult, fDiam);
    }

    //Now do the run and count the targets
    p_oSimManager->RunSim(1);
    iCount = 0;
    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {
      if (p_oTree->GetType() == clTreePopulation::adult &&
          p_oTree->GetSpecies() == iSpecies) {
        p_oTree->GetValue(p_oPop->GetDbhCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTestDiam);
        if (fabs(fDiam - fTestDiam) < 0.001) iCount++;
      }
      p_oTree = p_oAllTrees->NextTree();
    }
    EXPECT_EQ(iCount, 0);

    /////////////////////////////////////
    // # 4
    p_oSimManager->ReadFile(WriteWeibullClimateSurvivalXMLFile(3));
    p_oPop = (clTreePopulation *) p_oSimManager->GetPopulationObject(
        "treepopulation");

    CreateWeibullClimateSurvivalTrees(p_oPop);
    //Create 999 more of our target
    fDiam = 25;
    iSpecies = 3;
    for (i = 0; i < 999; i++) {
      p_oPop->CreateTree(59, 50, iSpecies, clTreePopulation::adult, fDiam);
    }

    //Now do the run and count the targets
    p_oSimManager->RunSim(1);
    iCount = 0;
    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {
      if (p_oTree->GetType() == clTreePopulation::adult &&
          p_oTree->GetSpecies() == iSpecies) {
        p_oTree->GetValue(p_oPop->GetDbhCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTestDiam);
        if (fabs(fDiam - fTestDiam) < 0.001) iCount++;
      }
      p_oTree = p_oAllTrees->NextTree();
    }
    fExpected = 763.1;
    EXPECT_LT(fabs(iCount - fExpected)/fExpected, 0.1);

    /////////////////////////////////////
    // # 5
    p_oSimManager->ReadFile(WriteWeibullClimateSurvivalXMLFile(3));
    p_oPop = (clTreePopulation *) p_oSimManager->GetPopulationObject(
        "treepopulation");

    CreateWeibullClimateSurvivalTrees(p_oPop);
    //Create 999 more of our target
    fDiam = 30;
    iSpecies = 1;
    for (i = 0; i < 999; i++) {
      p_oPop->CreateTree(50, 59, iSpecies, clTreePopulation::adult, fDiam);
    }

    //Now do the run and count the targets
    p_oSimManager->RunSim(1);
    iCount = 0;
    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {
      if (p_oTree->GetType() == clTreePopulation::adult &&
          p_oTree->GetSpecies() == iSpecies) {
        p_oTree->GetValue(p_oPop->GetDbhCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTestDiam);
        if (fabs(fDiam - fTestDiam) < 0.001) iCount++;
      }
      p_oTree = p_oAllTrees->NextTree();
    }
    fExpected = 782.81;
    EXPECT_LT(fabs(iCount - fExpected)/fExpected, 0.1);

    /////////////////////////////////////
    // # 6
    p_oSimManager->ReadFile(WriteWeibullClimateSurvivalXMLFile(3));
    p_oPop = (clTreePopulation *) p_oSimManager->GetPopulationObject(
        "treepopulation");

    CreateWeibullClimateSurvivalTrees(p_oPop);
    //Create 999 more of our target
    fDiam = 45;
    iSpecies = 2;
    for (i = 0; i < 999; i++) {
      p_oPop->CreateTree(55, 55, iSpecies, clTreePopulation::adult, fDiam);
    }

    //Now do the run and count the targets
    p_oSimManager->RunSim(1);
    iCount = 0;
    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {
      if (p_oTree->GetType() == clTreePopulation::adult &&
          p_oTree->GetSpecies() == iSpecies) {
        p_oTree->GetValue(p_oPop->GetDbhCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTestDiam);
        if (fabs(fDiam - fTestDiam) < 0.001) iCount++;
      }
      p_oTree = p_oAllTrees->NextTree();
    }
    fExpected = 875.4;
    EXPECT_LT(fabs(iCount - fExpected)/fExpected, 0.1);

    /////////////////////////////////////
    // # 7
    p_oSimManager->ReadFile(WriteWeibullClimateSurvivalXMLFile(3));
    p_oPop = (clTreePopulation *) p_oSimManager->GetPopulationObject(
        "treepopulation");

    CreateWeibullClimateSurvivalTrees(p_oPop);
    //Create 999 more of our target
    fDiam = 15;
    iSpecies = 3;
    for (i = 0; i < 999; i++) {
      p_oPop->CreateTree(60, 61, iSpecies, clTreePopulation::adult, fDiam);
    }

    //Now do the run and count the targets
    p_oSimManager->RunSim(1);
    iCount = 0;
    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {
      if (p_oTree->GetType() == clTreePopulation::adult &&
          p_oTree->GetSpecies() == iSpecies) {
        p_oTree->GetValue(p_oPop->GetDbhCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTestDiam);
        if (fabs(fDiam - fTestDiam) < 0.001) iCount++;
      }
      p_oTree = p_oAllTrees->NextTree();
    }
    fExpected = 346.73;
    EXPECT_LT(fabs(iCount - fExpected)/fExpected, 0.1);

    /////////////////////////////////////
    // # 8
    p_oSimManager->ReadFile(WriteWeibullClimateSurvivalXMLFile(3));
    p_oPop = (clTreePopulation *) p_oSimManager->GetPopulationObject(
        "treepopulation");

    CreateWeibullClimateSurvivalTrees(p_oPop);
    //Create 999 more of our target
    fDiam = 4;
    iSpecies = 1;
    for (i = 0; i < 999; i++) {
      p_oPop->CreateTree(52, 52, iSpecies, clTreePopulation::sapling, fDiam);
    }

    //Now do the run and count the targets
    p_oSimManager->RunSim(1);
    iCount = 0;
    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {
      if (p_oTree->GetType() == clTreePopulation::sapling &&
          p_oTree->GetSpecies() == iSpecies) {
        p_oTree->GetValue(p_oPop->GetDbhCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTestDiam);
        if (fabs(fDiam - fTestDiam) < 0.001) iCount++;
      }
      p_oTree = p_oAllTrees->NextTree();
    }
    fExpected = 6.59;
    EXPECT_LT(iCount, 20);

    /////////////////////////////////////
    // # 9
    p_oSimManager->ReadFile(WriteWeibullClimateSurvivalXMLFile(3));
    p_oPop = (clTreePopulation *) p_oSimManager->GetPopulationObject(
        "treepopulation");

    CreateWeibullClimateSurvivalTrees(p_oPop);
    //Create 999 more of our target
    fDiam = 4;
    iSpecies = 2;
    for (i = 0; i < 999; i++) {
      p_oPop->CreateTree(53, 53, iSpecies, clTreePopulation::sapling, fDiam);
    }

    //Now do the run and count the targets
    p_oSimManager->RunSim(1);
    iCount = 0;
    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {
      if (p_oTree->GetType() == clTreePopulation::sapling &&
          p_oTree->GetSpecies() == iSpecies) {
        p_oTree->GetValue(p_oPop->GetDbhCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTestDiam);
        if (fabs(fDiam - fTestDiam) < 0.001) iCount++;
      }
      p_oTree = p_oAllTrees->NextTree();
    }
    fExpected = 8.0;
    EXPECT_LT(iCount, 15);

    /////////////////////////////////////
    // # 10
    p_oSimManager->ReadFile(WriteWeibullClimateSurvivalXMLFile(3));
    p_oPop = (clTreePopulation *) p_oSimManager->GetPopulationObject(
        "treepopulation");

    CreateWeibullClimateSurvivalTrees(p_oPop);
    //Create 999 more of our target
    fDiam = 11;
    iSpecies = 1;
    for (i = 0; i < 999; i++) {
      p_oPop->CreateTree(20, 20, iSpecies, clTreePopulation::adult, fDiam);
    }

    //Now do the run and count the targets
    p_oSimManager->RunSim(1);
    iCount = 0;
    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {
      if (p_oTree->GetType() == clTreePopulation::adult &&
          p_oTree->GetSpecies() == iSpecies) {
        p_oTree->GetValue(p_oPop->GetDbhCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTestDiam);
        if (fabs(fDiam - fTestDiam) < 0.001) iCount++;
      }
      p_oTree = p_oAllTrees->NextTree();
    }
    fExpected = 638.87;
    EXPECT_LT(fabs(iCount - fExpected)/fExpected, 0.1);

    /////////////////////////////////////
    // # 11
    p_oSimManager->ReadFile(WriteWeibullClimateSurvivalXMLFile(3));
    p_oPop = (clTreePopulation *) p_oSimManager->GetPopulationObject(
        "treepopulation");

    CreateWeibullClimateSurvivalTrees(p_oPop);
    //Create 999 more of our target
    fDiam = 2;
    iSpecies = 1;
    for (i = 0; i < 999; i++) {
      p_oPop->CreateTree(50.1, 50.1, iSpecies, clTreePopulation::sapling, fDiam);
    }

    //Now do the run and count the targets
    p_oSimManager->RunSim(1);
    iCount = 0;
    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {
      if (p_oTree->GetType() == clTreePopulation::sapling &&
          p_oTree->GetSpecies() == iSpecies) {
        p_oTree->GetValue(p_oPop->GetDbhCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTestDiam);
        if (fabs(fDiam - fTestDiam) < 0.001) iCount++;
      }
      p_oTree = p_oAllTrees->NextTree();
    }
    fExpected = 3.33;
    EXPECT_LT(iCount, 10);

    /////////////////////////////////////
    // # 12
    p_oSimManager->ReadFile(WriteWeibullClimateSurvivalXMLFile(3));
    p_oPop = (clTreePopulation *) p_oSimManager->GetPopulationObject(
        "treepopulation");

    CreateWeibullClimateSurvivalTrees(p_oPop);
    //Create 999 more of our target
    fDiam = 3;
    iSpecies = 2;
    for (i = 0; i < 999; i++) {
      p_oPop->CreateTree(53.1, 52.1, iSpecies, clTreePopulation::sapling, fDiam);
    }

    //Now do the run and count the targets
    p_oSimManager->RunSim(1);
    iCount = 0;
    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {
      if (p_oTree->GetType() == clTreePopulation::sapling &&
          p_oTree->GetSpecies() == iSpecies) {
        p_oTree->GetValue(p_oPop->GetDbhCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTestDiam);
        if (fabs(fDiam - fTestDiam) < 0.001) iCount++;
      }
      p_oTree = p_oAllTrees->NextTree();
    }
    fExpected = 4.96;
    EXPECT_LT(iCount, 10);

    /////////////////////////////////////
    // # 13
    p_oSimManager->ReadFile(WriteWeibullClimateSurvivalXMLFile(3));
    p_oPop = (clTreePopulation *) p_oSimManager->GetPopulationObject(
        "treepopulation");

    CreateWeibullClimateSurvivalTrees(p_oPop);
    //Create 999 more of our target
    fDiam = 6;
    iSpecies = 3;
    for (i = 0; i < 999; i++) {
      p_oPop->CreateTree(59.1, 50.1, iSpecies, clTreePopulation::sapling, fDiam);
    }

    //Now do the run and count the targets
    p_oSimManager->RunSim(1);
    iCount = 0;
    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {
      if (p_oTree->GetType() == clTreePopulation::sapling &&
          p_oTree->GetSpecies() == iSpecies) {
        p_oTree->GetValue(p_oPop->GetDbhCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTestDiam);
        if (fabs(fDiam - fTestDiam) < 0.001) iCount++;
      }
      p_oTree = p_oAllTrees->NextTree();
    }
    fExpected = 7.63;
    EXPECT_LT(iCount, 15);

    /////////////////////////////////////
    // # 14
    p_oSimManager->ReadFile(WriteWeibullClimateSurvivalXMLFile(3));
    p_oPop = (clTreePopulation *) p_oSimManager->GetPopulationObject(
        "treepopulation");

    CreateWeibullClimateSurvivalTrees(p_oPop);
    //Create 999 more of our target
    fDiam = 7;
    iSpecies = 1;
    for (i = 0; i < 999; i++) {
      p_oPop->CreateTree(50.1, 59.1, iSpecies, clTreePopulation::sapling, fDiam);
    }

    //Now do the run and count the targets
    p_oSimManager->RunSim(1);
    iCount = 0;
    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {
      if (p_oTree->GetType() == clTreePopulation::sapling &&
          p_oTree->GetSpecies() == iSpecies) {
        p_oTree->GetValue(p_oPop->GetDbhCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTestDiam);
        if (fabs(fDiam - fTestDiam) < 0.001) iCount++;
      }
      p_oTree = p_oAllTrees->NextTree();
    }
    fExpected = 36.31;
    EXPECT_LT(iCount > 25 && iCount, 50);

    /////////////////////////////////////
    // # 15
    p_oSimManager->ReadFile(WriteWeibullClimateSurvivalXMLFile(3));
    p_oPop = (clTreePopulation *) p_oSimManager->GetPopulationObject(
        "treepopulation");

    CreateWeibullClimateSurvivalTrees(p_oPop);
    //Create 999 more of our target
    fDiam = 8;
    iSpecies = 2;
    for (i = 0; i < 999; i++) {
      p_oPop->CreateTree(50.1, 59.1, iSpecies, clTreePopulation::sapling, fDiam);
    }

    //Now do the run and count the targets
    p_oSimManager->RunSim(1);
    iCount = 0;
    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {
      if (p_oTree->GetType() == clTreePopulation::sapling &&
          p_oTree->GetSpecies() == iSpecies) {
        p_oTree->GetValue(p_oPop->GetDbhCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTestDiam);
        if (fabs(fDiam - fTestDiam) < 0.001) iCount++;
      }
      p_oTree = p_oAllTrees->NextTree();
    }
    fExpected = 84.53;
    EXPECT_LT(fabs(iCount - fExpected)/fExpected, 0.1);

    /////////////////////////////////////
    // # 16
    p_oSimManager->ReadFile(WriteWeibullClimateSurvivalXMLFile(3));
    p_oPop = (clTreePopulation *) p_oSimManager->GetPopulationObject(
        "treepopulation");

    CreateWeibullClimateSurvivalTrees(p_oPop);
    //Create 999 more of our target
    fDiam = 9;
    iSpecies = 3;
    for (i = 0; i < 999; i++) {
      p_oPop->CreateTree(60.1, 61.1, iSpecies, clTreePopulation::sapling, fDiam);
    }

    //Now do the run and count the targets
    p_oSimManager->RunSim(1);
    iCount = 0;
    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {
      if (p_oTree->GetType() == clTreePopulation::sapling &&
          p_oTree->GetSpecies() == iSpecies) {
        p_oTree->GetValue(p_oPop->GetDbhCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTestDiam);
        if (fabs(fDiam - fTestDiam) < 0.001) iCount++;
      }
      p_oTree = p_oAllTrees->NextTree();
    }
    fExpected = 4.20;
    EXPECT_LT(iCount, 10);
    delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

////////////////////////////////////////////////////////////////////////////
// CreateWeibullClimateSurvivalTrees()
////////////////////////////////////////////////////////////////////////////
void CreateWeibullClimateSurvivalTrees(clTreePopulation *p_oPop) {

  clTree *p_oTargetTree;
  float fDiam;
  int iSpecies;

  fDiam = 11;
  iSpecies = 1;
  p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, fDiam);

  fDiam = 10.5;
  iSpecies = 1;
  p_oPop->CreateTree(50, 50, iSpecies, clTreePopulation::adult, fDiam);

  fDiam = 15;
  iSpecies = 2;
  p_oPop->CreateTree(53, 52, iSpecies, clTreePopulation::adult, fDiam);

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

  fDiam = 4;
  iSpecies = 1;
  p_oPop->CreateTree(52, 52, iSpecies, clTreePopulation::sapling, fDiam);

  fDiam = 4;
  iSpecies = 2;
  p_oPop->CreateTree(53, 53, iSpecies, clTreePopulation::sapling, fDiam);

  fDiam = 11;
  iSpecies = 1;
  p_oPop->CreateTree(20, 20, iSpecies, clTreePopulation::adult, fDiam);

  fDiam = 2;
  iSpecies = 1;
  p_oPop->CreateTree(50.1, 50.1, iSpecies, clTreePopulation::sapling, fDiam);

  fDiam = 3;
  iSpecies = 2;
  p_oPop->CreateTree(53.1, 52.1, iSpecies, clTreePopulation::sapling, fDiam);

  fDiam = 6;
  iSpecies = 3;
  p_oPop->CreateTree(59.1, 50.1, iSpecies, clTreePopulation::sapling, fDiam);

  fDiam = 7;
  iSpecies = 1;
  p_oPop->CreateTree(50.1, 59.1, iSpecies, clTreePopulation::sapling, fDiam);

  fDiam = 8;
  iSpecies = 2;
  p_oPop->CreateTree(55.1, 55.1, iSpecies, clTreePopulation::sapling, fDiam);

  fDiam = 9;
  iSpecies = 3;
  p_oPop->CreateTree(60.1, 61.1, iSpecies, clTreePopulation::sapling, fDiam);

  //Now create all the neighbors that are too small or dead to compete
  p_oPop->CreateTree(56, 56, 0, clTreePopulation::snag, 30);
  p_oPop->CreateTree(56, 56, 0, clTreePopulation::seedling, 0.2);
  p_oTargetTree = p_oPop->CreateTree(54, 54, 1, clTreePopulation::adult, 20);
  p_oTargetTree->SetValue(p_oPop->GetIntDataCode("dead",
      p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), storm);

}

////////////////////////////////////////////////////////////////////////////
// WriteWeibullClimateSurvivalXMLFile()
////////////////////////////////////////////////////////////////////////////
const char* WriteWeibullClimateSurvivalXMLFile(int iYearsPerTimestep) {
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
       << "<yearsPerTimestep>" << iYearsPerTimestep << "</yearsPerTimestep>";

  oOut << "<randomSeed>1</randomSeed>"
       << "<plot_lenX>200.0</plot_lenX>"
       << "<plot_lenY>200.0</plot_lenY>"
       << "<plot_latitude>55.37</plot_latitude>"
       << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
       << "<plot_temp_C>12.88171785</plot_temp_C>"
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

  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>NCIMasterMortality</behaviorName>"
       << "<version>3</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_3\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_4\" type=\"Sapling\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>NCIMasterMortality</behaviorName>"
       << "<version>3</version>"
       << "<listPosition>2</listPosition>"
       << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_4\" type=\"Adult\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>RemoveDead</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>2</listPosition>"
       << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_3\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_4\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_4\" type=\"Sapling\"/>"
       << "</behavior>"
       << "</behaviorList>"
       << "<NCIMasterMortality1>"
       << "<nciWhichShadingEffect>0</nciWhichShadingEffect>"
       << "<nciWhichCrowdingEffect>1</nciWhichCrowdingEffect>"
       << "<nciWhichNCITerm>3</nciWhichNCITerm>"
       << "<nciWhichSizeEffect>2</nciWhichSizeEffect>"
       << "<nciWhichDamageEffect>0</nciWhichDamageEffect>"
       << "<nciWhichPrecipitationEffect>1</nciWhichPrecipitationEffect>"
       << "<nciWhichTemperatureEffect>1</nciWhichTemperatureEffect>"
       << "<nciWhichNitrogenEffect>0</nciWhichNitrogenEffect>"
       << "<nciWhichInfectionEffect>" << no_infection_effect << "</nciWhichInfectionEffect>"
       << "<mo_nciMortSurvPeriod>1</mo_nciMortSurvPeriod>"
       << "<mo_nciMaxPotentialSurvival>"
       << "<mo_nmpsVal species=\"Species_2\">1</mo_nmpsVal>"
       << "<mo_nmpsVal species=\"Species_3\">0.974</mo_nmpsVal>"
       << "<mo_nmpsVal species=\"Species_4\">0.85</mo_nmpsVal>"
       << "</mo_nciMaxPotentialSurvival>"
       << "<nciMaxCrowdingRadius>"
       << "<nmcrVal species=\"Species_2\">10</nmcrVal>"
       << "<nmcrVal species=\"Species_3\">11</nmcrVal>"
       << "<nmcrVal species=\"Species_4\">12</nmcrVal>"
       << "</nciMaxCrowdingRadius>"
       << "<nciSizeEffectX0>"
       << "<nsex0Val species=\"Species_2\">7.75</nsex0Val>"
       << "<nsex0Val species=\"Species_3\">12.8</nsex0Val>"
       << "<nsex0Val species=\"Species_4\">8.53</nsex0Val>"
       << "</nciSizeEffectX0>"
       << "<nciSizeEffectXb>"
       << "<nsexbVal species=\"Species_2\">1.53</nsexbVal>"
       << "<nsexbVal species=\"Species_3\">2.63</nsexbVal>"
       << "<nsexbVal species=\"Species_4\">0.84</nsexbVal>"
       << "</nciSizeEffectXb>"
       << "<nciSizeEffectLowerBound>"
       << "<nselbVal species=\"Species_2\">2.54</nselbVal>"
       << "<nselbVal species=\"Species_3\">7</nselbVal>"
       << "<nselbVal species=\"Species_4\">10</nselbVal>"
       << "</nciSizeEffectLowerBound>"
       << "<nciCrowdingC>"
       << "<nccVal species=\"Species_2\">0.2</nccVal>"
       << "<nccVal species=\"Species_3\">0.5</nccVal>"
       << "<nccVal species=\"Species_4\">0.6</nccVal>"
       << "</nciCrowdingC>"
       << "<nciCrowdingD>"
       << "<ncdVal species=\"Species_2\">0.93</ncdVal>"
       << "<ncdVal species=\"Species_3\">1.16</ncdVal>"
       << "<ncdVal species=\"Species_4\">0.072</ncdVal>"
       << "</nciCrowdingD>"
       << "<nciCrowdingGamma>"
       << "<ncgVal species=\"Species_2\">-0.061</ncgVal>"
       << "<ncgVal species=\"Species_3\">-1.405</ncgVal>"
       << "<ncgVal species=\"Species_4\">0.39</ncgVal>"
       << "</nciCrowdingGamma>"
       << "<nciWeibPrecipEffA>"
       << "<nwpeaVal species=\"Species_2\">2362.133</nwpeaVal>"
       << "<nwpeaVal species=\"Species_3\">9853.651</nwpeaVal>"
       << "<nwpeaVal species=\"Species_4\">2089.756</nwpeaVal>"
       << "</nciWeibPrecipEffA>"
       << "<nciWeibPrecipEffB>"
       << "<nwpebVal species=\"Species_2\">1.320871</nwpebVal>"
       << "<nwpebVal species=\"Species_3\">0.9795493</nwpebVal>"
       << "<nwpebVal species=\"Species_4\">2.626266</nwpebVal>"
       << "</nciWeibPrecipEffB>"
       << "<nciWeibPrecipEffC>"
       << "<nwpecVal species=\"Species_2\">1099.235</nwpecVal>"
       << "<nwpecVal species=\"Species_3\">708.4292</nwpecVal>"
       << "<nwpecVal species=\"Species_4\">1580.326</nwpecVal>"
       << "</nciWeibPrecipEffC>"
       << "<nciWeibTempEffA>"
       << "<nwteaVal species=\"Species_2\">6.884225</nwteaVal>"
       << "<nwteaVal species=\"Species_3\">139.5745</nwteaVal>"
       << "<nwteaVal species=\"Species_4\">6.996252</nwteaVal>"
       << "</nciWeibTempEffA>"
       << "<nciWeibTempEffB>"
       << "<nwtebVal species=\"Species_2\">0.3014869</nwtebVal>"
       << "<nwtebVal species=\"Species_3\">0</nwtebVal>"
       << "<nwtebVal species=\"Species_4\">3.000519</nwtebVal>"
       << "</nciWeibTempEffB>"
       << "<nciWeibTempEffC>"
       << "<nwtecVal species=\"Species_2\">14.2357</nwtecVal>"
       << "<nwtecVal species=\"Species_3\">28.6192</nwtecVal>"
       << "<nwtecVal species=\"Species_4\">9.6727</nwtecVal>"
       << "</nciWeibTempEffC>"
       << "<nciMinNeighborDBH>"
       << "<nmndVal species=\"Species_1\">5</nmndVal>"
       << "<nmndVal species=\"Species_2\">5</nmndVal>"
       << "<nmndVal species=\"Species_3\">5</nmndVal>"
       << "<nmndVal species=\"Species_4\">5</nmndVal>"
       << "</nciMinNeighborDBH>"
       << "</NCIMasterMortality1>"
       << "<NCIMasterMortality2>"
       << "<nciWhichShadingEffect>0</nciWhichShadingEffect>"
       << "<nciWhichCrowdingEffect>1</nciWhichCrowdingEffect>"
       << "<nciWhichNCITerm>3</nciWhichNCITerm>"
       << "<nciWhichSizeEffect>2</nciWhichSizeEffect>"
       << "<nciWhichDamageEffect>0</nciWhichDamageEffect>"
       << "<nciWhichPrecipitationEffect>1</nciWhichPrecipitationEffect>"
       << "<nciWhichTemperatureEffect>1</nciWhichTemperatureEffect>"
       << "<nciWhichNitrogenEffect>0</nciWhichNitrogenEffect>"
       << "<nciWhichInfectionEffect>" << no_infection_effect << "</nciWhichInfectionEffect>"
       << "<mo_nciMortSurvPeriod>1</mo_nciMortSurvPeriod>"
       << "<mo_nciMaxPotentialSurvival>"
       << "<mo_nmpsVal species=\"Species_2\">0.95</mo_nmpsVal>"
       << "<mo_nmpsVal species=\"Species_3\">1</mo_nmpsVal>"
       << "<mo_nmpsVal species=\"Species_4\">0.98</mo_nmpsVal>"
       << "</mo_nciMaxPotentialSurvival>"
       << "<nciMaxCrowdingRadius>"
       << "<nmcrVal species=\"Species_2\">10</nmcrVal>"
       << "<nmcrVal species=\"Species_3\">11</nmcrVal>"
       << "<nmcrVal species=\"Species_4\">12</nmcrVal>"
       << "</nciMaxCrowdingRadius>"
       << "<nciSizeEffectX0>"
       << "<nsex0Val species=\"Species_2\">30.48</nsex0Val>"
       << "<nsex0Val species=\"Species_3\">29.6</nsex0Val>"
       << "<nsex0Val species=\"Species_4\">26.6</nsex0Val>"
       << "</nciSizeEffectX0>"
       << "<nciSizeEffectXb>"
       << "<nsexbVal species=\"Species_2\">2.46</nsexbVal>"
       << "<nsexbVal species=\"Species_3\">2.85</nsexbVal>"
       << "<nsexbVal species=\"Species_4\">1.19</nsexbVal>"
       << "</nciSizeEffectXb>"
       << "<nciSizeEffectLowerBound>"
       << "<nselbVal species=\"Species_2\">2.54</nselbVal>"
       << "<nselbVal species=\"Species_3\">7</nselbVal>"
       << "<nselbVal species=\"Species_4\">10</nselbVal>"
       << "</nciSizeEffectLowerBound>"
       << "<nciCrowdingC>"
       << "<nccVal species=\"Species_2\">1.1</nccVal>"
       << "<nccVal species=\"Species_3\">6.7</nccVal>"
       << "<nccVal species=\"Species_4\">0.25</nccVal>"
       << "</nciCrowdingC>"
       << "<nciCrowdingD>"
       << "<ncdVal species=\"Species_2\">1.35</ncdVal>"
       << "<ncdVal species=\"Species_3\">0.874</ncdVal>"
       << "<ncdVal species=\"Species_4\">2.05</ncdVal>"
       << "</nciCrowdingD>"
       << "<nciCrowdingGamma>"
       << "<ncgVal species=\"Species_2\">-1.208</ncgVal>"
       << "<ncgVal species=\"Species_3\">1.976</ncgVal>"
       << "<ncgVal species=\"Species_4\">-1</ncgVal>"
       << "</nciCrowdingGamma>"
       << "<nciWeibTempEffA>"
       << "<nwteaVal species=\"Species_2\">8.897617</nwteaVal>"
       << "<nwteaVal species=\"Species_3\">8.91133</nwteaVal>"
       << "<nwteaVal species=\"Species_4\">6.996252</nwteaVal>"
       << "</nciWeibTempEffA>"
       << "<nciWeibTempEffB>"
       << "<nwtebVal species=\"Species_2\">1.205544</nwtebVal>"
       << "<nwtebVal species=\"Species_3\">1.475192</nwtebVal>"
       << "<nwtebVal species=\"Species_4\">3.000519</nwtebVal>"
       << "</nciWeibTempEffB>"
       << "<nciWeibTempEffC>"
       << "<nwtecVal species=\"Species_2\">13.2644</nwtecVal>"
       << "<nwtecVal species=\"Species_3\">12.4024</nwtecVal>"
       << "<nwtecVal species=\"Species_4\">9.6727</nwtecVal>"
       << "</nciWeibTempEffC>"
       << "<nciWeibPrecipEffA>"
       << "<nwpeaVal species=\"Species_2\">2593.648</nwpeaVal>"
       << "<nwpeaVal species=\"Species_3\">4777.299</nwpeaVal>"
       << "<nwpeaVal species=\"Species_4\">1636.351</nwpeaVal>"
       << "</nciWeibPrecipEffA>"
       << "<nciWeibPrecipEffB>"
       << "<nwpebVal species=\"Species_2\">2.890661</nwpebVal>"
       << "<nwpebVal species=\"Species_3\">1.29611</nwpebVal>"
       << "<nwpebVal species=\"Species_4\">1.692687</nwpebVal>"
       << "</nciWeibPrecipEffB>"
       << "<nciWeibPrecipEffC>"
       << "<nwpecVal species=\"Species_2\">1449.694</nwpecVal>"
       << "<nwpecVal species=\"Species_3\">1650.96</nwpecVal>"
       << "<nwpecVal species=\"Species_4\">1315.7</nwpecVal>"
       << "</nciWeibPrecipEffC>"
       << "<nciMinNeighborDBH>"
       << "<nmndVal species=\"Species_1\">5</nmndVal>"
       << "<nmndVal species=\"Species_2\">5</nmndVal>"
       << "<nmndVal species=\"Species_3\">5</nmndVal>"
       << "<nmndVal species=\"Species_4\">5</nmndVal>"
       << "</nciMinNeighborDBH>"
       << "</NCIMasterMortality2>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteWeibullClimateSurvivalErrorFileCommonStuff()
/////////////////////////////////////////////////////////////////////////////
void WriteWeibullClimateSurvivalErrorFileCommonStuff(std::fstream &oOut) {
  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06010101\">"
       << "<plot>"
       << "<timesteps>1</timesteps>"
       << "<yearsPerTimestep>1</yearsPerTimestep>"
       << "<randomSeed>1</randomSeed>"
       << "<plot_lenX>200.0</plot_lenX>"
       << "<plot_lenY>200.0</plot_lenY>"
       << "<plot_latitude>55.37</plot_latitude>"
       << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
       << "<plot_temp_C>12.88171785</plot_temp_C>"
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
       << "<behaviorName>NCIMasterMortality</behaviorName>"
       << "<version>3</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "</behavior>"
       << "</behaviorList>"
       << "<NCIMasterMortality1>"
       << "<nciWhichShadingEffect>0</nciWhichShadingEffect>"
       << "<nciWhichCrowdingEffect>1</nciWhichCrowdingEffect>"
       << "<nciWhichNCITerm>3</nciWhichNCITerm>"
       << "<nciWhichSizeEffect>2</nciWhichSizeEffect>"
       << "<nciWhichDamageEffect>0</nciWhichDamageEffect>"
       << "<nciWhichPrecipitationEffect>1</nciWhichPrecipitationEffect>"
       << "<nciWhichTemperatureEffect>1</nciWhichTemperatureEffect>"
       << "<nciWhichNitrogenEffect>0</nciWhichNitrogenEffect>"
       << "<nciWhichInfectionEffect>" << no_infection_effect << "</nciWhichInfectionEffect>"
       << "<mo_nciMortSurvPeriod>1</mo_nciMortSurvPeriod>"
       << "<nciSizeEffectLowerBound>"
       << "<nselbVal species=\"Species_1\">2.54</nselbVal>"
       << "<nselbVal species=\"Species_2\">7</nselbVal>"
       << "</nciSizeEffectLowerBound>"
       << "<nciCrowdingC>"
       << "<nccVal species=\"Species_1\">1.1</nccVal>"
       << "<nccVal species=\"Species_2\">6.7</nccVal>"
       << "</nciCrowdingC>"
       << "<nciCrowdingD>"
       << "<ncdVal species=\"Species_1\">1.35</ncdVal>"
       << "<ncdVal species=\"Species_2\">0.874</ncdVal>"
       << "</nciCrowdingD>"
       << "<nciCrowdingGamma>"
       << "<ncgVal species=\"Species_1\">-1.208</ncgVal>"
       << "<ncgVal species=\"Species_2\">1.976</ncgVal>"
       << "</nciCrowdingGamma>"
       << "<nciWeibTempEffB>"
       << "<nwtebVal species=\"Species_1\">1.205544</nwtebVal>"
       << "<nwtebVal species=\"Species_2\">1.475192</nwtebVal>"
       << "</nciWeibTempEffB>"
       << "<nciWeibTempEffC>"
       << "<nwtecVal species=\"Species_1\">13.2644</nwtecVal>"
       << "<nwtecVal species=\"Species_2\">12.4024</nwtecVal>"
       << "</nciWeibTempEffC>"
       << "<nciWeibPrecipEffB>"
       << "<nwpebVal species=\"Species_1\">2.890661</nwpebVal>"
       << "<nwpebVal species=\"Species_2\">1.29611</nwpebVal>"
       << "</nciWeibPrecipEffB>"
       << "<nciWeibPrecipEffC>"
       << "<nwpecVal species=\"Species_1\">1449.694</nwpecVal>"
       << "<nwpecVal species=\"Species_2\">1650.96</nwpecVal>"
       << "</nciWeibPrecipEffC>"
       << "<nciMinNeighborDBH>"
       << "<nmndVal species=\"Species_1\">5</nmndVal>"
       << "<nmndVal species=\"Species_2\">5</nmndVal>"
       << "</nciMinNeighborDBH>";

}

////////////////////////////////////////////////////////////////////////////
// WriteWeibullClimateSurvivalXMLErrorFile1()
////////////////////////////////////////////////////////////////////////////
const char* WriteWeibullClimateSurvivalXMLErrorFile1() {
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  WriteWeibullClimateSurvivalErrorFileCommonStuff(oOut);

  //Write file
  oOut << "<nciMaxCrowdingRadius>"
       << "<nmcrVal species=\"Species_1\">-10</nmcrVal>"
       << "<nmcrVal species=\"Species_2\">11</nmcrVal>"
       << "</nciMaxCrowdingRadius>"
       << "<nciSizeEffectX0>"
       << "<nsex0Val species=\"Species_1\">30.48</nsex0Val>"
       << "<nsex0Val species=\"Species_2\">29.6</nsex0Val>"
       << "</nciSizeEffectX0>"
       << "<mo_nciMaxPotentialSurvival>"
       << "<mo_nmpsVal species=\"Species_1\">0.95</mo_nmpsVal>"
       << "<mo_nmpsVal species=\"Species_2\">1</mo_nmpsVal>"
       << "</mo_nciMaxPotentialSurvival>"
       << "<nciSizeEffectXb>"
       << "<nsexbVal species=\"Species_1\">2.46</nsexbVal>"
       << "<nsexbVal species=\"Species_2\">2.85</nsexbVal>"
       << "</nciSizeEffectXb>"
       << "<nciWeibTempEffA>"
       << "<nwteaVal species=\"Species_1\">8.897617</nwteaVal>"
       << "<nwteaVal species=\"Species_2\">8.91133</nwteaVal>"
       << "</nciWeibTempEffA>"
       << "<nciWeibPrecipEffA>"
       << "<nwpeaVal species=\"Species_1\">2593.648</nwpeaVal>"
       << "<nwpeaVal species=\"Species_2\">4777.299</nwpeaVal>"
       << "</nciWeibPrecipEffA>"
       << "</NCIMasterMortality1>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteWeibullClimateSurvivalXMLErrorFile2()
////////////////////////////////////////////////////////////////////////////
const char* WriteWeibullClimateSurvivalXMLErrorFile2() {
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  WriteWeibullClimateSurvivalErrorFileCommonStuff(oOut);

  oOut << "<nciMaxCrowdingRadius>"
       << "<nmcrVal species=\"Species_1\">10</nmcrVal>"
       << "<nmcrVal species=\"Species_2\">11</nmcrVal>"
       << "</nciMaxCrowdingRadius>"
       << "<nciSizeEffectX0>"
       << "<nsex0Val species=\"Species_1\">30.48</nsex0Val>"
       << "<nsex0Val species=\"Species_2\">29.6</nsex0Val>"
       << "</nciSizeEffectX0>"
       << "<mo_nciMaxPotentialSurvival>"
       << "<mo_nmpsVal species=\"Species_1\">-0.95</mo_nmpsVal>"
       << "<mo_nmpsVal species=\"Species_2\">1</mo_nmpsVal>"
       << "</mo_nciMaxPotentialSurvival>"
       << "<nciSizeEffectXb>"
       << "<nsexbVal species=\"Species_1\">2.46</nsexbVal>"
       << "<nsexbVal species=\"Species_2\">2.85</nsexbVal>"
       << "</nciSizeEffectXb>"
       << "<nciWeibTempEffA>"
       << "<nwteaVal species=\"Species_1\">8.897617</nwteaVal>"
       << "<nwteaVal species=\"Species_2\">8.91133</nwteaVal>"
       << "</nciWeibTempEffA>"
       << "<nciWeibPrecipEffA>"
       << "<nwpeaVal species=\"Species_1\">2593.648</nwpeaVal>"
       << "<nwpeaVal species=\"Species_2\">4777.299</nwpeaVal>"
       << "</nciWeibPrecipEffA>"
       << "</NCIMasterMortality1>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteWeibullClimateSurvivalXMLErrorFile3()
////////////////////////////////////////////////////////////////////////////
const char* WriteWeibullClimateSurvivalXMLErrorFile3() {
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  WriteWeibullClimateSurvivalErrorFileCommonStuff(oOut);

  oOut << "<nciMaxCrowdingRadius>"
       << "<nmcrVal species=\"Species_1\">10</nmcrVal>"
       << "<nmcrVal species=\"Species_2\">11</nmcrVal>"
       << "</nciMaxCrowdingRadius>"
       << "<nciSizeEffectX0>"
       << "<nsex0Val species=\"Species_1\">30.48</nsex0Val>"
       << "<nsex0Val species=\"Species_2\">29.6</nsex0Val>"
       << "</nciSizeEffectX0>"
       << "<mo_nciMaxPotentialSurvival>"
       << "<mo_nmpsVal species=\"Species_1\">0.95</mo_nmpsVal>"
       << "<mo_nmpsVal species=\"Species_2\">1</mo_nmpsVal>"
       << "</mo_nciMaxPotentialSurvival>"
       << "<nciSizeEffectXb>"
       << "<nsexbVal species=\"Species_1\">0</nsexbVal>"
       << "<nsexbVal species=\"Species_2\">2.85</nsexbVal>"
       << "</nciSizeEffectXb>"
       << "<nciWeibTempEffA>"
       << "<nwteaVal species=\"Species_1\">8.897617</nwteaVal>"
       << "<nwteaVal species=\"Species_2\">8.91133</nwteaVal>"
       << "</nciWeibTempEffA>"
       << "<nciWeibPrecipEffA>"
       << "<nwpeaVal species=\"Species_1\">2593.648</nwpeaVal>"
       << "<nwpeaVal species=\"Species_2\">4777.299</nwpeaVal>"
       << "</nciWeibPrecipEffA>"
       << "</NCIMasterMortality1>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteWeibullClimateSurvivalXMLErrorFile4()
////////////////////////////////////////////////////////////////////////////
const char* WriteWeibullClimateSurvivalXMLErrorFile4() {
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  WriteWeibullClimateSurvivalErrorFileCommonStuff(oOut);

  oOut << "<nciMaxCrowdingRadius>"
       << "<nmcrVal species=\"Species_1\">10</nmcrVal>"
       << "<nmcrVal species=\"Species_2\">11</nmcrVal>"
       << "</nciMaxCrowdingRadius>"
       << "<nciSizeEffectX0>"
       << "<nsex0Val species=\"Species_1\">0</nsex0Val>"
       << "<nsex0Val species=\"Species_2\">29.6</nsex0Val>"
       << "</nciSizeEffectX0>"
       << "<mo_nciMaxPotentialSurvival>"
       << "<mo_nmpsVal species=\"Species_1\">0.95</mo_nmpsVal>"
       << "<mo_nmpsVal species=\"Species_2\">1</mo_nmpsVal>"
       << "</mo_nciMaxPotentialSurvival>"
       << "<nciSizeEffectXb>"
       << "<nsexbVal species=\"Species_1\">2.46</nsexbVal>"
       << "<nsexbVal species=\"Species_2\">2.85</nsexbVal>"
       << "</nciSizeEffectXb>"
       << "<nciWeibTempEffA>"
       << "<nwteaVal species=\"Species_1\">8.897617</nwteaVal>"
       << "<nwteaVal species=\"Species_2\">8.91133</nwteaVal>"
       << "</nciWeibTempEffA>"
       << "<nciWeibPrecipEffA>"
       << "<nwpeaVal species=\"Species_1\">2593.648</nwpeaVal>"
       << "<nwpeaVal species=\"Species_2\">4777.299</nwpeaVal>"
       << "</nciWeibPrecipEffA>"
       << "</NCIMasterMortality1>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteWeibullClimateSurvivalXMLErrorFile5()
////////////////////////////////////////////////////////////////////////////
const char* WriteWeibullClimateSurvivalXMLErrorFile5() {
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  WriteWeibullClimateSurvivalErrorFileCommonStuff(oOut);

  oOut << "<nciMaxCrowdingRadius>"
       << "<nmcrVal species=\"Species_1\">10</nmcrVal>"
       << "<nmcrVal species=\"Species_2\">11</nmcrVal>"
       << "</nciMaxCrowdingRadius>"
       << "<nciSizeEffectX0>"
       << "<nsex0Val species=\"Species_1\">30.48</nsex0Val>"
       << "<nsex0Val species=\"Species_2\">29.6</nsex0Val>"
       << "</nciSizeEffectX0>"
       << "<mo_nciMaxPotentialSurvival>"
       << "<mo_nmpsVal species=\"Species_1\">0.95</mo_nmpsVal>"
       << "<mo_nmpsVal species=\"Species_2\">1</mo_nmpsVal>"
       << "</mo_nciMaxPotentialSurvival>"
       << "<nciSizeEffectXb>"
       << "<nsexbVal species=\"Species_1\">2.46</nsexbVal>"
       << "<nsexbVal species=\"Species_2\">2.85</nsexbVal>"
       << "</nciSizeEffectXb>"
       << "<nciWeibTempEffA>"
       << "<nwteaVal species=\"Species_1\">8.897617</nwteaVal>"
       << "<nwteaVal species=\"Species_2\">8.91133</nwteaVal>"
       << "</nciWeibTempEffA>"
       << "<nciWeibPrecipEffA>"
       << "<nwpeaVal species=\"Species_1\">0</nwpeaVal>"
       << "<nwpeaVal species=\"Species_2\">4777.299</nwpeaVal>"
       << "</nciWeibPrecipEffA>"
       << "</NCIMasterMortality1>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}


////////////////////////////////////////////////////////////////////////////
// WriteWeibullClimateSurvivalXMLErrorFile6()
////////////////////////////////////////////////////////////////////////////
const char* WriteWeibullClimateSurvivalXMLErrorFile6() {
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  WriteWeibullClimateSurvivalErrorFileCommonStuff(oOut);

  oOut << "<nciMaxCrowdingRadius>"
       << "<nmcrVal species=\"Species_1\">10</nmcrVal>"
       << "<nmcrVal species=\"Species_2\">11</nmcrVal>"
       << "</nciMaxCrowdingRadius>"
       << "<nciSizeEffectX0>"
       << "<nsex0Val species=\"Species_1\">30.48</nsex0Val>"
       << "<nsex0Val species=\"Species_2\">29.6</nsex0Val>"
       << "</nciSizeEffectX0>"
       << "<mo_nciMaxPotentialSurvival>"
       << "<mo_nmpsVal species=\"Species_1\">0.95</mo_nmpsVal>"
       << "<mo_nmpsVal species=\"Species_2\">1</mo_nmpsVal>"
       << "</mo_nciMaxPotentialSurvival>"
       << "<nciSizeEffectXb>"
       << "<nsexbVal species=\"Species_1\">2.46</nsexbVal>"
       << "<nsexbVal species=\"Species_2\">2.85</nsexbVal>"
       << "</nciSizeEffectXb>"
       << "<nciWeibTempEffA>"
       << "<nwteaVal species=\"Species_1\">0</nwteaVal>"
       << "<nwteaVal species=\"Species_2\">8.91133</nwteaVal>"
       << "</nciWeibTempEffA>"
       << "<nciWeibPrecipEffA>"
       << "<nwpeaVal species=\"Species_1\">2593.648</nwpeaVal>"
       << "<nwpeaVal species=\"Species_2\">4777.299</nwpeaVal>"
       << "</nciWeibPrecipEffA>"
       << "</NCIMasterMortality1>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}
