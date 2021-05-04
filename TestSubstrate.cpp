//---------------------------------------------------------------------------
// TestSubstrate.cpp
//---------------------------------------------------------------------------
#include "TestSubstrate.h"
#include <gtest/gtest.h>
#include "Grid.h"
#include "SimManager.h"
#include "BehaviorBase.h"
#include "TreePopulation.h"
#include <math.h>
#include <fstream>
#include <sstream>

/////////////////////////////////////////////////////////////////////////////
// TestTreeFall()
// Tests tree fall. This makes sure that fallen trees are removed, and
// standing trees have the opportunity to become snags; and that all snags
// fall. This uses WriteSubstrateXMLFile5() to do setup. It has three
// species. For live trees:  for species 1, 20% of dead trees fall; for
// species 2, 50%; and for species 3, 0%. There is a behavior which is
// applied to snags, to ensure standing dead trees produce snags. 1000 trees
// and 1000 snags are created for each species, and all are set to dead. Then
// one timestep is run, and the snags counted to make sure there is the
// proper proportion of each. Then another timestep is run to make sure the
// snags created from dead adults aren't "disappeared". This process is
// repeated for WriteSubstrateXMLFile4(), but this time we're concentrating on
// tipup area. In this case, the whole plot is divided into six grid cells. In
// each one go either 1000 live trees or 1000 snags of a species. We check
// to make sure the right amount of organic matter is in both.
/////////////////////////////////////////////////////////////////////////////
TEST(Substrate, TestTreeFall) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    clTreePopulation *p_oPop;
    clTreeSearch *p_oAllTrees;
    clTree *p_oTree;
    int iNumSp1Snags = 0, iNumSp2Snags = 0, iNumSp3Snags = 0,
        iDead = natural,
        iSpecies, i;

    //Create and feed in the file
    p_oSimManager->ReadFile(WriteSubstrateXMLFile5());
    //Grab our pointers
    p_oPop = (clTreePopulation*) p_oSimManager->GetPopulationObject("treepopulation");

    // There should not be packages from our initial conditions - this tests
    // that the substrate map flag was triggered
    clGrid *p_oSubstrateGrid = p_oSimManager->GetGridObject("Substrate");
    clPackage *p_oCohort = p_oSubstrateGrid->GetFirstPackageOfCell(0, 0);
    ASSERT_TRUE(NULL == p_oCohort);

    //Create 1000 of each species of tree, all adults
    for (i = 0; i < 1000; i++) {
      p_oTree = p_oPop->CreateTree(1, 1, 0, clTreePopulation::adult, 17);
    }
    for (i = 0; i < 1000; i++) {
      p_oTree = p_oPop->CreateTree(1, 1, 1, clTreePopulation::adult, 17);
    }
    for (i = 0; i < 1000; i++) {
      p_oTree = p_oPop->CreateTree(1, 1, 2, clTreePopulation::adult, 17);
    }
    //Create 1000 of each species of tree, all snags
    for (i = 0; i < 1000; i++) {
      p_oTree = p_oPop->CreateTree(2, 1, 0, clTreePopulation::snag, 17);
      p_oTree->SetValue(p_oPop->GetIntDataCode("dead", p_oTree->GetSpecies(), p_oTree->GetType()), iDead);
    }
    for (i = 0; i < 1000; i++) {
      p_oTree = p_oPop->CreateTree(2, 1, 1, clTreePopulation::snag, 17);
      p_oTree->SetValue(p_oPop->GetIntDataCode("dead", p_oTree->GetSpecies(), p_oTree->GetType()), iDead);
    }
    for (i = 0; i < 1000; i++) {
      p_oTree = p_oPop->CreateTree(2, 1, 2, clTreePopulation::snag, 17);
      p_oTree->SetValue(p_oPop->GetIntDataCode("dead", p_oTree->GetSpecies(), p_oTree->GetType()), iDead);
    }

    //Run for 1 timestep and make sure all the snags have fallen
    p_oSimManager->RunSim(1);

    //Count up the snags and make sure there's the right number of each
    iNumSp1Snags = 0;
    iNumSp2Snags = 0;
    iNumSp3Snags = 0;
    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {

      //Make sure it's not alive
      EXPECT_EQ(clTreePopulation::snag, p_oTree->GetType());

      //Count it
      iSpecies = p_oTree->GetSpecies();
      if (0 == iSpecies) iNumSp1Snags++;
      else if (1 == iSpecies) iNumSp2Snags++;
      else if (2 == iSpecies) iNumSp3Snags++;

      p_oTree = p_oAllTrees->NextTree();
    }

    //Now make sure we have the number we expect left standing
    EXPECT_LT(fabs(iNumSp1Snags - 800)/800, 0.1);
    EXPECT_LT(fabs(iNumSp2Snags - 500)/500, 0.1);
    EXPECT_EQ(iNumSp3Snags, 1000);

    //Run another timestep and count them again
    iNumSp1Snags = 0;
    iNumSp2Snags = 0;
    iNumSp3Snags = 0;
    p_oSimManager->RunSim(1);
    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {

      //Make sure it's not alive
      EXPECT_EQ(clTreePopulation::snag, p_oTree->GetType());

      //Count it
      iSpecies = p_oTree->GetSpecies();
      if (0 == iSpecies) iNumSp1Snags++;
      else if (1 == iSpecies) iNumSp2Snags++;
      else if (2 == iSpecies) iNumSp3Snags++;

      p_oTree = p_oAllTrees->NextTree();
    }

    //Now make sure we have the number we expect left standing
    EXPECT_LT(fabs(iNumSp1Snags - 800)/800, 0.1);
    EXPECT_LT(fabs(iNumSp2Snags - 500)/500, 0.1);
    EXPECT_EQ(iNumSp3Snags, 1000);

    //***************************
    // Test the tipup
    //***************************
    p_oSimManager->ReadFile(WriteSubstrateXMLFile4());
    //Grab our pointers
    clGrid *p_oCalcsGrid = p_oSimManager->GetGridObject("substratecalcs");
    p_oPop = (clTreePopulation*) p_oSimManager->GetPopulationObject("treepopulation");

    //Run for 1 timestep
    p_oSimManager->RunSim(1);

    // There should be packages from our initial conditions - this tests
    // that the substrate map flag was not triggered
    p_oSubstrateGrid = p_oSimManager->GetGridObject("Substrate");
    p_oCohort = p_oSubstrateGrid->GetFirstPackageOfCell(0, 0);
    ASSERT_TRUE(NULL != p_oCohort);

    //Create 1000 of each species of tree, all adults
    for (i = 0; i < 1000; i++) {
      p_oTree = p_oPop->CreateTree(1, 1, 0, clTreePopulation::adult, 20);
    }
    for (i = 0; i < 1000; i++) {
      p_oTree = p_oPop->CreateTree(1, 46, 1, clTreePopulation::adult, 40);
    }
    for (i = 0; i < 1000; i++) {
      p_oTree = p_oPop->CreateTree(1, 91, 2, clTreePopulation::adult, 55);
    }
    //Create 1000 of each species of tree, all snags
    for (i = 0; i < 1000; i++) {
      p_oTree = p_oPop->CreateTree(1, 135, 0, clTreePopulation::snag, 25);
    }
    for (i = 0; i < 1000; i++) {
      p_oTree = p_oPop->CreateTree(1, 181, 1, clTreePopulation::snag, 30);
    }
    for (i = 0; i < 1000; i++) {
      p_oTree = p_oPop->CreateTree(1, 226, 2, clTreePopulation::snag, 65);
    }

    //Run for 1 timestep
    p_oSimManager->RunSim(1);

    float fExpectedTipup, fActual;
    int iCode = p_oCalcsGrid->GetFloatDataCode("newtipup"),
        iX, iY;

    //Cell 1
    iX = 0; iY = 0;
    fExpectedTipup = 0.149089903;
    p_oCalcsGrid->GetValueOfCell(iX, iY, iCode, & fActual);
    EXPECT_LT(fabs(fActual - fExpectedTipup)/fExpectedTipup, 0.1);
    //Cell 2
    iY = 1;
    fExpectedTipup = 0.097488417;
    p_oCalcsGrid->GetValueOfCell(iX, iY, iCode, & fActual);
    EXPECT_LT(fabs(fActual - fExpectedTipup)/fExpectedTipup, 0.1);
    //Cell 3
    iY = 2;
    fExpectedTipup = 0.049159992;
    p_oCalcsGrid->GetValueOfCell(iX, iY, iCode, & fActual);
    EXPECT_LT(fabs(fActual - fExpectedTipup)/fExpectedTipup, 0.2);
    //Cell 4
    iY = 3;
    fExpectedTipup = 0.123516502;
    p_oCalcsGrid->GetValueOfCell(iX, iY, iCode, & fActual);
    EXPECT_LT(fabs(fActual - fExpectedTipup)/fExpectedTipup, 0.1);
    //Cell 5
    iY = 4;
    fExpectedTipup = 0;
    p_oCalcsGrid->GetValueOfCell(iX, iY, iCode, & fActual);
    EXPECT_EQ(fActual, fExpectedTipup);
    //Cell 6
    iY = 5;
    fExpectedTipup = 0.147523047;
    p_oCalcsGrid->GetValueOfCell(iX, iY, iCode, & fActual);
    EXPECT_LT(fabs(fActual - fExpectedTipup)/fExpectedTipup, 0.1);

    delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

/////////////////////////////////////////////////////////////////////////////
// TestSubstrateRun1()
// Substrate normal processing run 1. Verifies substrate calculations. This
// run has no harvest and non-directional tree fall. This function tests that
// new fresh log area and new tip-up area are added correctly when trees die,
// that cohorts are managed correctly, and that the final substrate numbers
// are calculated correctly. WriteSubstrateXMLFile2() is used to set up with
// tip-up probabilities of 1. This executes the timesteps and provides mortality
// (killing known trees at certain times), and then verifies grid values.
/////////////////////////////////////////////////////////////////////////////
TEST(Substrate, TestSubstrateRun1) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    clGrid * p_oSubstrateGrid, *p_oCalcsGrid;
    clTreePopulation *p_oPop;
    clTree *p_oTree;
    int iDead = natural;

    //Create and feed in the file
    p_oSimManager->ReadFile(WriteSubstrateXMLFile2());
    //Grab our pointers
    p_oPop = (clTreePopulation*) p_oSimManager->GetPopulationObject("treepopulation");
    p_oSubstrateGrid = p_oSimManager->GetGridObject("Substrate");
    p_oCalcsGrid = p_oSimManager->GetGridObject("substratecalcs");

    //********************************
    //Timestep 1:  Just run.
    //********************************
    p_oSimManager->RunSim(1);

    //Verify the freshlogs and declogs arrays
    VerifySubstrateRun1TS1SubstrateArrays(p_oCalcsGrid);

    //Verify the new tipups
    VerifySubstrateRun1TS1Tipup(p_oCalcsGrid);

    //Verify the cohorts
    VerifySubstrateRun1TS1Cohorts(p_oSubstrateGrid);

    //Verify the substrate proportions
    VerifySubstrateRun1TS1Proportions(p_oSubstrateGrid);

    //********************************
    //Timestep 2:
    //********************************
    //Create and then kill certain trees within cell 0, 2
    //Tree where y = 18
    p_oTree = p_oPop->CreateTree(1, 18, 0, 3, 20);
    p_oTree->SetValue(p_oPop->GetIntDataCode("dead", p_oTree->GetSpecies(), p_oTree->GetType()), iDead);

    //Tree where y = 19
    p_oTree = p_oPop->CreateTree(1, 19, 0, 3, 40);
    p_oTree->SetValue(p_oPop->GetIntDataCode("dead", p_oTree->GetSpecies(), p_oTree->GetType()), iDead);


    //Now create and then kill certain trees within cell 0, 3
    //Tree where y = 25
    p_oTree = p_oPop->CreateTree(1, 25, 0, 3, 55);
    p_oTree->SetValue(p_oPop->GetIntDataCode("dead", p_oTree->GetSpecies(), p_oTree->GetType()), iDead);

    //Tree where y = 26
    p_oTree = p_oPop->CreateTree(1, 26, 0, 3, 15);
    p_oTree->SetValue(p_oPop->GetIntDataCode("dead", p_oTree->GetSpecies(), p_oTree->GetType()), iDead);

    //Tree where y = 27
    p_oTree = p_oPop->CreateTree(1, 27, 0, 2, 8);
    p_oTree->SetValue(p_oPop->GetIntDataCode("dead", p_oTree->GetSpecies(), p_oTree->GetType()), iDead);

    p_oSimManager->RunSim(1);


    //Verify the freshlogs and declogs arrays
    VerifySubstrateRun1TS2SubstrateArrays(p_oCalcsGrid);

    //Verify the new tipups
    VerifySubstrateRun1TS2Tipup(p_oCalcsGrid);

    //Verify the cohorts
    VerifySubstrateRun1TS2Cohorts(p_oSubstrateGrid);

    //Verify the substrate proportions
    VerifySubstrateRun1TS2Proportions(p_oSubstrateGrid);

    //********************************
    //Timestep 3:
    //********************************
    //Create and kill a tree in cell 0, 0 where y = 2
    p_oTree = p_oPop->CreateTree(1, 2, 0, 2, 65);
    p_oTree->SetValue(p_oPop->GetIntDataCode("dead", p_oTree->GetSpecies(), p_oTree->GetType()), iDead);

    //Create and kill a tree in cell 0, 1 where y = 10
    p_oTree = p_oPop->CreateTree(1, 10, 0, 2, 100);
    p_oTree->SetValue(p_oPop->GetIntDataCode("dead", p_oTree->GetSpecies(), p_oTree->GetType()), iDead);

    //Create and kill a tree in cell 0, 2 where y = 20
    p_oTree = p_oPop->CreateTree(1, 20, 0, 2, 35);
    p_oTree->SetValue(p_oPop->GetIntDataCode("dead", p_oTree->GetSpecies(), p_oTree->GetType()), iDead);

    //Create and kill a tree in cell 0, 3 where y = 28
    p_oTree = p_oPop->CreateTree(1, 28, 0, 2, 42);
    p_oTree->SetValue(p_oPop->GetIntDataCode("dead", p_oTree->GetSpecies(), p_oTree->GetType()), iDead);

    //Now run the harvest behavior, substrate behavior and the tree killer
    p_oSimManager->RunSim(1);

    //Verify the freshlogs and declogs arrays
    VerifySubstrateRun1TS3SubstrateArrays(p_oCalcsGrid);

    //Verify the new tipups
    VerifySubstrateRun1TS3Tipup(p_oCalcsGrid);

    //Verify the cohorts
    VerifySubstrateRun1TS3Cohorts(p_oSubstrateGrid);

    //Verify the substrate proportions
    VerifySubstrateRun1TS3Proportions(p_oSubstrateGrid);

    //********************************
    //Timestep 4:  Just run.
    //********************************
    p_oSimManager->RunSim(1);

    //Verify the freshlogs and declogs arrays
    VerifySubstrateRun1TS4SubstrateArrays(p_oCalcsGrid);

    //Verify the new tipups
    VerifySubstrateRun1TS4Tipup(p_oCalcsGrid);

    //Verify the cohorts
    VerifySubstrateRun1TS4Cohorts(p_oSubstrateGrid);

    //Verify the substrate proportions
    VerifySubstrateRun1TS4Proportions(p_oSubstrateGrid);
    delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}


/////////////////////////////////////////////////////////////////////////////
// TestSubstrateRun4()
// Substrate normal processing run 4. Verifies substrate calculations with
// a multi-year timestep. This run has no harvest and non-directional tree
// fall. WriteSubstrateXMLFile6() is used to set up with tip-up probabilities of 1.
// This executes the timesteps and provides mortality (killing known trees at
// certain times), and then verifies grid values.
/////////////////////////////////////////////////////////////////////////////
TEST(Substrate, TestSubstrateRun4) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    clGrid * p_oSubstrateGrid, *p_oCalcsGrid;
    clPopulationBase *p_oTemp;
    clTreePopulation *p_oPop;
    clTree *p_oTree;
    int iDead = natural;

    //Create and feed in the file
    p_oSimManager->ReadFile(WriteSubstrateXMLFile6());
    //Grab our pointers
    p_oTemp = p_oSimManager->GetPopulationObject("treepopulation");
    p_oPop = (clTreePopulation*) p_oTemp;
    p_oSubstrateGrid = p_oSimManager->GetGridObject("Substrate");
    p_oCalcsGrid = p_oSimManager->GetGridObject("substratecalcs");

    //********************************
    //Timestep 1:  Just run.
    //********************************
    p_oSimManager->RunSim(1);

    //Verify the freshlogs and declogs arrays
    VerifySubstrateRun4TS1SubstrateArrays(p_oCalcsGrid);

    //Verify the new tipups
    VerifySubstrateRun1TS1Tipup(p_oCalcsGrid);

    //Verify the cohorts
    VerifySubstrateRun1TS1Cohorts(p_oSubstrateGrid);

    //Verify the substrate proportions
    VerifySubstrateRun4TS1Proportions(p_oSubstrateGrid);

    //********************************
    //Timestep 2:
    //********************************
    //Create and then kill certain trees within cell 0, 2
    //Tree where y = 18
    p_oTree = p_oPop->CreateTree(1, 18, 0, 3, 20);
    p_oTree->SetValue(p_oPop->GetIntDataCode("dead", p_oTree->GetSpecies(), p_oTree->GetType()), iDead);

    //Tree where y = 19
    p_oTree = p_oPop->CreateTree(1, 19, 0, 3, 40);
    p_oTree->SetValue(p_oPop->GetIntDataCode("dead", p_oTree->GetSpecies(), p_oTree->GetType()), iDead);


    //Now create and then kill certain trees within cell 0, 3
    //Tree where y = 25
    p_oTree = p_oPop->CreateTree(1, 25, 0, 3, 55);
    p_oTree->SetValue(p_oPop->GetIntDataCode("dead", p_oTree->GetSpecies(), p_oTree->GetType()), iDead);

    //Tree where y = 26
    p_oTree = p_oPop->CreateTree(1, 26, 0, 3, 15);
    p_oTree->SetValue(p_oPop->GetIntDataCode("dead", p_oTree->GetSpecies(), p_oTree->GetType()), iDead);

    //Tree where y = 27
    p_oTree = p_oPop->CreateTree(1, 27, 0, 2, 8);
    p_oTree->SetValue(p_oPop->GetIntDataCode("dead", p_oTree->GetSpecies(), p_oTree->GetType()), iDead);

    p_oSimManager->RunSim(1);


    //Verify the freshlogs and declogs arrays
    VerifySubstrateRun4TS2SubstrateArrays(p_oCalcsGrid);

    //Verify the new tipups
    VerifySubstrateRun1TS2Tipup(p_oCalcsGrid);

    //Verify the cohorts
    VerifySubstrateRun1TS2Cohorts(p_oSubstrateGrid);

    //Verify the substrate proportions
    VerifySubstrateRun4TS2Proportions(p_oSubstrateGrid);

    //********************************
    //Timestep 3:
    //********************************
    //Create and kill a tree in cell 0, 0 where y = 2
    p_oTree = p_oPop->CreateTree(1, 2, 0, 2, 65);
    p_oTree->SetValue(p_oPop->GetIntDataCode("dead", p_oTree->GetSpecies(), p_oTree->GetType()), iDead);

    //Create and kill a tree in cell 0, 1 where y = 10
    p_oTree = p_oPop->CreateTree(1, 10, 0, 2, 100);
    p_oTree->SetValue(p_oPop->GetIntDataCode("dead", p_oTree->GetSpecies(), p_oTree->GetType()), iDead);

    //Create and kill a tree in cell 0, 2 where y = 20
    p_oTree = p_oPop->CreateTree(1, 20, 0, 2, 35);
    p_oTree->SetValue(p_oPop->GetIntDataCode("dead", p_oTree->GetSpecies(), p_oTree->GetType()), iDead);

    //Create and kill a tree in cell 0, 3 where y = 28
    p_oTree = p_oPop->CreateTree(1, 28, 0, 2, 42);
    p_oTree->SetValue(p_oPop->GetIntDataCode("dead", p_oTree->GetSpecies(), p_oTree->GetType()), iDead);

    //Now run the harvest behavior, substrate behavior and the tree killer
    p_oSimManager->RunSim(1);

    //Verify the freshlogs and declogs arrays
    VerifySubstrateRun4TS3SubstrateArrays(p_oCalcsGrid);

    //Verify the new tipups
    VerifySubstrateRun1TS3Tipup(p_oCalcsGrid);

    //Verify the cohorts
    VerifySubstrateRun1TS3Cohorts(p_oSubstrateGrid);

    //Verify the substrate proportions
    VerifySubstrateRun4TS3Proportions(p_oSubstrateGrid);

    //********************************
    //Timestep 4:  Just run.
    //********************************
    p_oSimManager->RunSim(1);

    //Verify the freshlogs and declogs arrays
    VerifySubstrateRun4TS4SubstrateArrays(p_oCalcsGrid);

    //Verify the new tipups
    VerifySubstrateRun1TS4Tipup(p_oCalcsGrid);

    //Verify the cohorts
    VerifySubstrateRun1TS4Cohorts(p_oSubstrateGrid);

    //Verify the substrate proportions
    VerifySubstrateRun4TS4Proportions(p_oSubstrateGrid);
    delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}



/////////////////////////////////////////////////////////////////////////////
// VerifySubstrateRun1TS1Proportions()
/////////////////////////////////////////////////////////////////////////////
void VerifySubstrateRun1TS1Proportions(clGrid *p_oSubstrateGrid) {
  float fExpectedTipup, fExpectedFreshLog, fExpectedScarSoil,
        fExpectedDecLog, fExpectedFFMoss, fExpectedFFLitter, fActual;
  int iX, iY;

  //Cell 1
  iX = 0; iY = 0;
  fExpectedScarSoil = 0;
  fExpectedFreshLog = 0.01;
  fExpectedDecLog = 0.11;
  fExpectedTipup = 0.2;
  fExpectedFFMoss = 0.238;
  fExpectedFFLitter = 0.442;
  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("scarsoil"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedScarSoil), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("tipup"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedTipup), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("freshlog"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedFreshLog), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("declog"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedDecLog), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("ffmoss"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedFFMoss), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("fflitter"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedFFLitter), 0.001);

  //Cell 2
  iY = 1;
  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("scarsoil"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedScarSoil), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("tipup"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedTipup), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("freshlog"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedFreshLog), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("ffmoss"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedFFMoss), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("declog"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedDecLog), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("fflitter"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedFFLitter), 0.001);

  //Cell 3
  iY = 2;
  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("scarsoil"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedScarSoil), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("tipup"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedTipup), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("freshlog"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedFreshLog), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("ffmoss"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedFFMoss), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("declog"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedDecLog), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("fflitter"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedFFLitter), 0.001);

  //Cell 4
  iY = 3;
  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("scarsoil"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedScarSoil), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("tipup"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedTipup), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("freshlog"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedFreshLog), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("ffmoss"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedFFMoss), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("declog"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedDecLog), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("fflitter"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedFFLitter), 0.001);

  //Cell 5
  iY = 4;
  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("scarsoil"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedScarSoil), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("tipup"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedTipup), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("freshlog"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedFreshLog), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("ffmoss"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedFFMoss), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("declog"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedDecLog), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("fflitter"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedFFLitter), 0.001);
}

/////////////////////////////////////////////////////////////////////////////
// VerifySubstrateRun1TS2Proportions()
/////////////////////////////////////////////////////////////////////////////
void VerifySubstrateRun1TS2Proportions(clGrid *p_oSubstrateGrid) {
  float fExpectedTipup, fExpectedFreshLog, fExpectedScarSoil = 0,
        fExpectedDecLog, fExpectedFFMoss, fExpectedFFLitter, fActual;
  int iX, iY;

  //Cell 1
  iX = 0; iY = 0;
  fExpectedFreshLog = 0.009512294;
  fExpectedDecLog = 0.049988087;
  fExpectedTipup = 0.199860049;
  fExpectedFFMoss = 0.25922385;
  fExpectedFFLitter = 0.481415721;
  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("scarsoil"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedScarSoil), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("tipup"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedTipup), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("freshlog"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedFreshLog), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("ffmoss"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedFFMoss), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("declog"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedDecLog), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("fflitter"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedFFLitter), 0.001);

  //Cell 2
  iY = 1;
  fExpectedFreshLog = 0.009512294;
  fExpectedDecLog = 0.049988087;
  fExpectedTipup = 0.199860049;
  fExpectedFFLitter = 0.481415721;
  fExpectedFFMoss = 0.25922385;
  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("scarsoil"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedScarSoil), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("tipup"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedTipup), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("freshlog"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedFreshLog), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("declog"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedDecLog), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("ffmoss"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedFFMoss), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("fflitter"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedFFLitter), 0.001);

  //Cell 3
  iY = 2;
  fExpectedFreshLog = 0.124448823;
  fExpectedDecLog = 0.049988087;
  fExpectedTipup = 0.195495441;
  fExpectedFFMoss = 0.220523677;
  fExpectedFFLitter = 0.409543972;
  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("scarsoil"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedScarSoil), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("tipup"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedTipup), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("freshlog"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedFreshLog), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("ffmoss"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedFFMoss), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("declog"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedDecLog), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("fflitter"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedFFLitter), 0.001);

  //Cell 4
  iY = 3;
  fExpectedFreshLog = 0.163399328;
  fExpectedDecLog = 0.049988087;
  fExpectedTipup = 0.199403043;
  fExpectedFFMoss = 0.20552334;
  fExpectedFFLitter = 0.381686202;
  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("scarsoil"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedScarSoil), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("tipup"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedTipup), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("freshlog"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedFreshLog), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("ffmoss"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedFFMoss), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("declog"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedDecLog), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("fflitter"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedFFLitter), 0.001);

  //Cell 5
  iY = 4;
  fExpectedFreshLog = 0.009512294;
  fExpectedDecLog = 0.049988087;
  fExpectedTipup = 0.199860049;
  fExpectedFFMoss = 0.25922385;
  fExpectedFFLitter = 0.481415721;
  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("scarsoil"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedScarSoil), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("tipup"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedTipup), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("freshlog"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedFreshLog), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("ffmoss"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedFFMoss), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("declog"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedDecLog), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("fflitter"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedFFLitter), 0.001);
}

/////////////////////////////////////////////////////////////////////////////
// VerifySubstrateRun1TS3Proportions()
/////////////////////////////////////////////////////////////////////////////
void VerifySubstrateRun1TS3Proportions(clGrid *p_oSubstrateGrid) {
  float fExpectedTipup, fExpectedFreshLog, fExpectedScarSoil = 0,
        fExpectedDecLog, fExpectedFFMoss, fExpectedFFLitter, fActual;
  int iX, iY;

  //Cell 1
  iX = 0; iY = 0;
  fExpectedFreshLog = 0.172840545;
  fExpectedDecLog = 0.031898812;
  fExpectedTipup = 0.203180676;
  fExpectedFFMoss = 0.207227989;
  fExpectedFFLitter = 0.384851979;
  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("scarsoil"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedScarSoil), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("tipup"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedTipup), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("freshlog"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedFreshLog), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("ffmoss"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedFFMoss), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("declog"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedDecLog), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("fflitter"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedFFLitter), 0.001);

  //Cell 2
  iY = 1;
  fExpectedFreshLog = 0.293521087;
  fExpectedDecLog = 0.031898812;
  fExpectedTipup = 0.234042378;
  fExpectedFFMoss = 0.154188203;
  fExpectedFFLitter = 0.28634952;
  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("scarsoil"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedScarSoil), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("tipup"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedTipup), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("freshlog"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedFreshLog), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("ffmoss"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedFFMoss), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("declog"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedDecLog), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("fflitter"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedFFLitter), 0.001);

  //Cell 3
  iY = 2;
  fExpectedFreshLog = 0.172533986;
  fExpectedDecLog = 0.037569213;
  fExpectedTipup = 0.191112492;
  fExpectedFFMoss = 0.209574508;
  fExpectedFFLitter = 0.389209801;
  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("scarsoil"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedScarSoil), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("tipup"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedTipup), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("freshlog"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedFreshLog), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("ffmoss"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedFFMoss), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("declog"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedDecLog), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("fflitter"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedFFLitter), 0.001);

  //Cell 4
  iY = 3;
  fExpectedFreshLog = 0.225127679;
  fExpectedDecLog = 0.039494;
  fExpectedTipup = 0.195455065;
  fExpectedFFMoss = 0.18897314;
  fExpectedFFLitter = 0.350950116;
  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("scarsoil"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedScarSoil), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("tipup"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedTipup), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("freshlog"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedFreshLog), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("ffmoss"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedFFMoss), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("declog"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedDecLog), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("fflitter"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedFFLitter), 0.001);

  //Cell 5
  iY = 4;
  fExpectedFreshLog = 0.000108295;
  fExpectedDecLog = 0.031898812;
  fExpectedTipup = 0.197261163;
  fExpectedFFMoss = 0.269756106;
  fExpectedFFLitter = 0.500975625;
  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("scarsoil"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedScarSoil), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("tipup"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedTipup), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("freshlog"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedFreshLog), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("ffmoss"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedFFMoss), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("declog"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedDecLog), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("fflitter"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedFFLitter), 0.001);
}

/////////////////////////////////////////////////////////////////////////////
// VerifySubstrateRun1TS4Proportions()
/////////////////////////////////////////////////////////////////////////////
void VerifySubstrateRun1TS4Proportions(clGrid *p_oSubstrateGrid) {
  float fExpectedTipup, fExpectedFreshLog, fExpectedScarSoil,
        fExpectedDecLog, fExpectedFFMoss, fExpectedFFLitter, fActual;
  int iX, iY;

  fExpectedScarSoil = 0;

  //Cell 1
  iX = 0; iY = 0;
  fExpectedFreshLog = 0.164330928;
  fExpectedDecLog = 0.012756021;
  fExpectedTipup = 0.049791591;
  fExpectedFFMoss = 0.270592511;
  fExpectedFFLitter = 0.502528949;
  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("scarsoil"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedScarSoil), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("tipup"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedTipup), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("freshlog"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedFreshLog), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("ffmoss"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedFFMoss), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("declog"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedDecLog), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("fflitter"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedFFLitter), 0.001);

  //Cell 2
  iY = 1;
  fExpectedFreshLog = 0.27914526;
  fExpectedDecLog = 0.018642678;
  fExpectedTipup = 0.117849919;
  fExpectedFFMoss = 0.20452675;
  fExpectedFFLitter = 0.379835393;
  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("scarsoil"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedScarSoil), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("tipup"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedTipup), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("freshlog"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedFreshLog), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("ffmoss"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedFFMoss), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("declog"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedDecLog), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("fflitter"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedFFLitter), 0.001);

  //Cell 3
  iY = 2;
  fExpectedFreshLog = 0.069011889;
  fExpectedDecLog = 0.119698936;
  fExpectedTipup = 0.035704405;
  fExpectedFFMoss = 0.271454669;
  fExpectedFFLitter = 0.5041301;
  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("scarsoil"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedScarSoil), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("tipup"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedTipup), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("freshlog"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedFreshLog), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("ffmoss"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedFFMoss), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("declog"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedDecLog), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("fflitter"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedFFLitter), 0.001);

  //Cell 4
  iY = 3;
  fExpectedFreshLog = 0.090818511;
  fExpectedDecLog = 0.158779574;
  fExpectedTipup = 0.054255551;
  fExpectedFFMoss = 0.243651228;
  fExpectedFFLitter = 0.452495137;
  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("scarsoil"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedScarSoil), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("tipup"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedTipup), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("freshlog"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedFreshLog), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("ffmoss"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedFFMoss), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("declog"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedDecLog), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("fflitter"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedFFLitter), 0.001);

  //Cell 5
  iY = 4;
  fExpectedFreshLog = 0.000108295;
  fExpectedDecLog = 0.004330594;
  fExpectedTipup = 0.197261163;
  fExpectedFFMoss = 0.279404982;
  fExpectedFFLitter = 0.518894966;
  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("scarsoil"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedScarSoil), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("tipup"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedTipup), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("freshlog"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedFreshLog), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("declog"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedDecLog), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("ffmoss"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedFFMoss), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("fflitter"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedFFLitter), 0.001);
}

/////////////////////////////////////////////////////////////////////////////
// VerifySubstrateRun1TS1Cohorts()
/////////////////////////////////////////////////////////////////////////////
void VerifySubstrateRun1TS1Cohorts(clGrid *p_oSubstrateGrid) {
  clPackage * p_oCohort;
  float fExpectedTipup = 0.2, fExpectedFreshLog = 0.01, fExpectedScarSoil = 0.0, fActual;
  int iX, iY, iAge = 1, iActual;

  //Cell 1
  iX = 0; iY = 0;
  p_oCohort = p_oSubstrateGrid->GetFirstPackageOfCell(iX, iY);
  ASSERT_TRUE(NULL != p_oCohort);

  p_oCohort->GetValue(p_oSubstrateGrid->GetPackageFloatDataCode("scarsoil"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedScarSoil), 0.001);

  p_oCohort->GetValue(p_oSubstrateGrid->GetPackageFloatDataCode("tipup"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedTipup), 0.001);

  p_oCohort->GetValue(p_oSubstrateGrid->GetPackageFloatDataCode("freshlog"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedFreshLog), 0.001);

  p_oCohort->GetValue(p_oSubstrateGrid->GetPackageIntDataCode("age"), & iActual);
  EXPECT_EQ(iActual, iAge);

  EXPECT_EQ(NULL, p_oCohort->GetNextPackage());

  //Cell 2
  iY = 1;
  p_oCohort = p_oSubstrateGrid->GetFirstPackageOfCell(iX, iY);
  ASSERT_TRUE(NULL != p_oCohort);

  p_oCohort->GetValue(p_oSubstrateGrid->GetPackageFloatDataCode("scarsoil"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedScarSoil), 0.001);

  p_oCohort->GetValue(p_oSubstrateGrid->GetPackageFloatDataCode("tipup"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedTipup), 0.001);

  p_oCohort->GetValue(p_oSubstrateGrid->GetPackageFloatDataCode("freshlog"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedFreshLog), 0.001);

  p_oCohort->GetValue(p_oSubstrateGrid->GetPackageIntDataCode("age"), & iActual);
  EXPECT_EQ(iActual, iAge);

  EXPECT_EQ(NULL, p_oCohort->GetNextPackage());

  //Cell 3
  iY = 2;
  p_oCohort = p_oSubstrateGrid->GetFirstPackageOfCell(iX, iY);
  ASSERT_TRUE(NULL != p_oCohort);

  p_oCohort->GetValue(p_oSubstrateGrid->GetPackageFloatDataCode("scarsoil"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedScarSoil), 0.001);

  p_oCohort->GetValue(p_oSubstrateGrid->GetPackageFloatDataCode("tipup"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedTipup), 0.001);

  p_oCohort->GetValue(p_oSubstrateGrid->GetPackageFloatDataCode("freshlog"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedFreshLog), 0.001);

  p_oCohort->GetValue(p_oSubstrateGrid->GetPackageIntDataCode("age"), & iActual);
  EXPECT_EQ(iActual, iAge);

  EXPECT_EQ(NULL, p_oCohort->GetNextPackage());

  //Cell 4
  iY = 3;
  p_oCohort = p_oSubstrateGrid->GetFirstPackageOfCell(iX, iY);
  ASSERT_TRUE(NULL != p_oCohort);

  p_oCohort->GetValue(p_oSubstrateGrid->GetPackageFloatDataCode("scarsoil"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedScarSoil), 0.001);

  p_oCohort->GetValue(p_oSubstrateGrid->GetPackageFloatDataCode("tipup"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedTipup), 0.001);

  p_oCohort->GetValue(p_oSubstrateGrid->GetPackageFloatDataCode("freshlog"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedFreshLog), 0.001);

  p_oCohort->GetValue(p_oSubstrateGrid->GetPackageIntDataCode("age"), & iActual);
  EXPECT_EQ(iActual, iAge);

  EXPECT_EQ(NULL, p_oCohort->GetNextPackage());

  //Cell 5
  iY = 4;
  p_oCohort = p_oSubstrateGrid->GetFirstPackageOfCell(iX, iY);
  ASSERT_TRUE(NULL != p_oCohort);

  p_oCohort->GetValue(p_oSubstrateGrid->GetPackageFloatDataCode("scarsoil"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedScarSoil), 0.001);

  p_oCohort->GetValue(p_oSubstrateGrid->GetPackageFloatDataCode("tipup"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedTipup), 0.001);

  p_oCohort->GetValue(p_oSubstrateGrid->GetPackageFloatDataCode("freshlog"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedFreshLog), 0.001);

  p_oCohort->GetValue(p_oSubstrateGrid->GetPackageIntDataCode("age"), & iActual);
  EXPECT_EQ(iActual, iAge);

  EXPECT_EQ(NULL, p_oCohort->GetNextPackage());
}

/////////////////////////////////////////////////////////////////////////////
// VerifySubstrateRun1TS2Cohorts()
/////////////////////////////////////////////////////////////////////////////
void VerifySubstrateRun1TS2Cohorts(clGrid *p_oSubstrateGrid) {
  clPackage * p_oCohort;
  float fExpectedTipup, fExpectedFreshLog, fExpectedScarSoil = 0, fActual;
  int iX, iY, iAge, iActual;

  //Cell 1
  iX = 0; iY = 0;
  fExpectedTipup = 0.2;
  fExpectedFreshLog = 0.01;
  iAge = 2;
  p_oCohort = p_oSubstrateGrid->GetFirstPackageOfCell(iX, iY);
  ASSERT_TRUE(NULL != p_oCohort);

  p_oCohort->GetValue(p_oSubstrateGrid->GetPackageFloatDataCode("scarsoil"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedScarSoil), 0.001);

  p_oCohort->GetValue(p_oSubstrateGrid->GetPackageFloatDataCode("tipup"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedTipup), 0.001);

  p_oCohort->GetValue(p_oSubstrateGrid->GetPackageFloatDataCode("freshlog"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedFreshLog), 0.001);

  p_oCohort->GetValue(p_oSubstrateGrid->GetPackageIntDataCode("age"), & iActual);
  EXPECT_EQ(iActual, iAge);

  EXPECT_EQ(NULL, p_oCohort->GetNextPackage());

  //Cell 2
  iY = 1;
  fExpectedTipup = 0.2;
  fExpectedFreshLog = 0.01;
  iAge = 2;
  p_oCohort = p_oSubstrateGrid->GetFirstPackageOfCell(iX, iY);
  ASSERT_TRUE(NULL != p_oCohort);

  p_oCohort->GetValue(p_oSubstrateGrid->GetPackageFloatDataCode("scarsoil"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedScarSoil), 0.001);

  p_oCohort->GetValue(p_oSubstrateGrid->GetPackageFloatDataCode("tipup"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedTipup), 0.001);

  p_oCohort->GetValue(p_oSubstrateGrid->GetPackageFloatDataCode("freshlog"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedFreshLog), 0.001);

  p_oCohort->GetValue(p_oSubstrateGrid->GetPackageIntDataCode("age"), & iActual);
  EXPECT_EQ(iActual, iAge);

  EXPECT_EQ(NULL, p_oCohort->GetNextPackage());

  //Cell 3 cohort 1
  iY = 2;
  fExpectedTipup = 0.172029331;
  fExpectedFreshLog = 0.008601467;
  iAge = 2;
  p_oCohort = p_oSubstrateGrid->GetFirstPackageOfCell(iX, iY);
  ASSERT_TRUE(NULL != p_oCohort);

  p_oCohort->GetValue(p_oSubstrateGrid->GetPackageFloatDataCode("scarsoil"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedScarSoil), 0.001);

  p_oCohort->GetValue(p_oSubstrateGrid->GetPackageFloatDataCode("tipup"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedTipup), 0.001);

  p_oCohort->GetValue(p_oSubstrateGrid->GetPackageFloatDataCode("freshlog"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedFreshLog), 0.001);

  p_oCohort->GetValue(p_oSubstrateGrid->GetPackageIntDataCode("age"), & iActual);
  EXPECT_EQ(iActual, iAge);

  //Cell 3 cohort 2
  fExpectedTipup = 0.023586489;
  fExpectedFreshLog = 0.116266855;
  iAge = 1;
  p_oCohort = p_oCohort->GetNextPackage();
  ASSERT_TRUE(NULL != p_oCohort);

  p_oCohort->GetValue(p_oSubstrateGrid->GetPackageFloatDataCode("scarsoil"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedScarSoil), 0.001);

  p_oCohort->GetValue(p_oSubstrateGrid->GetPackageFloatDataCode("tipup"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedTipup), 0.001);

  p_oCohort->GetValue(p_oSubstrateGrid->GetPackageFloatDataCode("freshlog"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedFreshLog), 0.001);

  p_oCohort->GetValue(p_oSubstrateGrid->GetPackageIntDataCode("age"), & iActual);
  EXPECT_EQ(iActual, iAge);

  EXPECT_EQ(NULL, p_oCohort->GetNextPackage());


  //Cell 4, cohort 1
  iY = 3;
  fExpectedTipup = 0.161187791;
  fExpectedFreshLog = 0.00805939;
  iAge = 2;
  p_oCohort = p_oSubstrateGrid->GetFirstPackageOfCell(iX, iY);
  ASSERT_TRUE(NULL != p_oCohort);

  p_oCohort->GetValue(p_oSubstrateGrid->GetPackageFloatDataCode("scarsoil"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedScarSoil), 0.001);

  p_oCohort->GetValue(p_oSubstrateGrid->GetPackageFloatDataCode("tipup"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedTipup), 0.001);

  p_oCohort->GetValue(p_oSubstrateGrid->GetPackageFloatDataCode("freshlog"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedFreshLog), 0.001);

  p_oCohort->GetValue(p_oSubstrateGrid->GetPackageIntDataCode("age"), & iActual);
  EXPECT_EQ(iActual, iAge);

  //Cell 4, cohort 2
  fExpectedTipup = 0.038328044;
  fExpectedFreshLog = 0.155733;
  iAge = 1;
  p_oCohort = p_oCohort->GetNextPackage();
  ASSERT_TRUE(NULL != p_oCohort);

  p_oCohort->GetValue(p_oSubstrateGrid->GetPackageFloatDataCode("scarsoil"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedScarSoil), 0.001);

  p_oCohort->GetValue(p_oSubstrateGrid->GetPackageFloatDataCode("tipup"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedTipup), 0.001);

  p_oCohort->GetValue(p_oSubstrateGrid->GetPackageFloatDataCode("freshlog"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedFreshLog), 0.001);

  p_oCohort->GetValue(p_oSubstrateGrid->GetPackageIntDataCode("age"), & iActual);
  EXPECT_EQ(iActual, iAge);

  EXPECT_EQ(NULL, p_oCohort->GetNextPackage());

  //Cell 5
  iY = 4;
  fExpectedTipup = 0.2;
  fExpectedFreshLog = 0.01;
  iAge = 2;
  p_oCohort = p_oSubstrateGrid->GetFirstPackageOfCell(iX, iY);
  ASSERT_TRUE(NULL != p_oCohort);

  p_oCohort->GetValue(p_oSubstrateGrid->GetPackageFloatDataCode("scarsoil"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedScarSoil), 0.001);

  p_oCohort->GetValue(p_oSubstrateGrid->GetPackageFloatDataCode("tipup"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedTipup), 0.001);

  p_oCohort->GetValue(p_oSubstrateGrid->GetPackageFloatDataCode("freshlog"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedFreshLog), 0.001);

  p_oCohort->GetValue(p_oSubstrateGrid->GetPackageIntDataCode("age"), & iActual);
  EXPECT_EQ(iActual, iAge);

  EXPECT_EQ(NULL, p_oCohort->GetNextPackage());
}

/////////////////////////////////////////////////////////////////////////////
// VerifySubstrateRun1TS3Cohorts()
/////////////////////////////////////////////////////////////////////////////
void VerifySubstrateRun1TS3Cohorts(clGrid *p_oSubstrateGrid) {
  clPackage * p_oCohort;
  float fExpectedTipup, fExpectedFreshLog, fExpectedScarSoil = 0, fActual;
  int iX, iY, iAge, iActual;

  //Cell 1, cohort 1
  iX = 0; iY = 0;
  fExpectedTipup = 0.049826457;
  fExpectedFreshLog = 0.172756354;
  iAge = 1;
  p_oCohort = p_oSubstrateGrid->GetFirstPackageOfCell(iX, iY);
  ASSERT_TRUE(NULL != p_oCohort);

  p_oCohort->GetValue(p_oSubstrateGrid->GetPackageFloatDataCode("scarsoil"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedScarSoil), 0.001);

  p_oCohort->GetValue(p_oSubstrateGrid->GetPackageFloatDataCode("tipup"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedTipup), 0.001);

  p_oCohort->GetValue(p_oSubstrateGrid->GetPackageFloatDataCode("freshlog"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedFreshLog), 0.001);

  p_oCohort->GetValue(p_oSubstrateGrid->GetPackageIntDataCode("age"), & iActual);
  EXPECT_EQ(iActual, iAge);

  EXPECT_EQ(NULL, p_oCohort->GetNextPackage());

  //Cell 2, cohort 1
  iY = 1;
  fExpectedTipup = 0.117932443;
  fExpectedFreshLog = 0.293457344;
  iAge = 1;
  p_oCohort = p_oSubstrateGrid->GetFirstPackageOfCell(iX, iY);
  ASSERT_TRUE(NULL != p_oCohort);

  p_oCohort->GetValue(p_oSubstrateGrid->GetPackageFloatDataCode("scarsoil"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedScarSoil), 0.001);

  p_oCohort->GetValue(p_oSubstrateGrid->GetPackageFloatDataCode("tipup"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedTipup), 0.001);

  p_oCohort->GetValue(p_oSubstrateGrid->GetPackageFloatDataCode("freshlog"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedFreshLog), 0.001);

  p_oCohort->GetValue(p_oSubstrateGrid->GetPackageIntDataCode("age"), & iActual);
  EXPECT_EQ(iActual, iAge);

  EXPECT_EQ(NULL, p_oCohort->GetNextPackage());


  //Cell 3, cohort 1
  iY = 2;
  fExpectedTipup = 0.021563079;
  fExpectedFreshLog = 0.106292692;
  iAge = 2;
  p_oCohort = p_oSubstrateGrid->GetFirstPackageOfCell(iX, iY);
  ASSERT_TRUE(NULL != p_oCohort);

  p_oCohort->GetValue(p_oSubstrateGrid->GetPackageFloatDataCode("scarsoil"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedScarSoil), 0.001);

  p_oCohort->GetValue(p_oSubstrateGrid->GetPackageFloatDataCode("tipup"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedTipup), 0.001);

  p_oCohort->GetValue(p_oSubstrateGrid->GetPackageFloatDataCode("freshlog"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedFreshLog), 0.001);

  p_oCohort->GetValue(p_oSubstrateGrid->GetPackageIntDataCode("age"), & iActual);
  EXPECT_EQ(iActual, iAge);

  //Cell 3, cohort 2
  fExpectedTipup = 0.014446724;
  fExpectedFreshLog = 0.071340092;
  iAge = 1;
  p_oCohort = p_oCohort->GetNextPackage();
  ASSERT_TRUE(NULL != p_oCohort);

  p_oCohort->GetValue(p_oSubstrateGrid->GetPackageFloatDataCode("scarsoil"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedScarSoil), 0.001);

  p_oCohort->GetValue(p_oSubstrateGrid->GetPackageFloatDataCode("tipup"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedTipup), 0.001);

  p_oCohort->GetValue(p_oSubstrateGrid->GetPackageFloatDataCode("freshlog"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedFreshLog), 0.001);

  p_oCohort->GetValue(p_oSubstrateGrid->GetPackageIntDataCode("age"), & iActual);
  EXPECT_EQ(iActual, iAge);

  EXPECT_EQ(NULL, p_oCohort->GetNextPackage());

  //Cell 4, cohort 1
  iY = 3;
  fExpectedTipup = 0.033931489;
  fExpectedFreshLog = 0.137869092;
  iAge = 2;
  p_oCohort = p_oSubstrateGrid->GetFirstPackageOfCell(iX, iY);
  ASSERT_TRUE(NULL != p_oCohort);

  p_oCohort->GetValue(p_oSubstrateGrid->GetPackageFloatDataCode("scarsoil"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedScarSoil), 0.001);

  p_oCohort->GetValue(p_oSubstrateGrid->GetPackageFloatDataCode("tipup"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedTipup), 0.001);

  p_oCohort->GetValue(p_oSubstrateGrid->GetPackageFloatDataCode("freshlog"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedFreshLog), 0.001);

  p_oCohort->GetValue(p_oSubstrateGrid->GetPackageIntDataCode("age"), & iActual);
  EXPECT_EQ(iActual, iAge);

  //Cell 4, cohort 2
  fExpectedTipup = 0.020803283;
  fExpectedFreshLog = 0.093905275;
  iAge = 1;
  p_oCohort = p_oCohort->GetNextPackage();
  ASSERT_TRUE(NULL != p_oCohort);

  p_oCohort->GetValue(p_oSubstrateGrid->GetPackageFloatDataCode("scarsoil"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedScarSoil), 0.001);

  p_oCohort->GetValue(p_oSubstrateGrid->GetPackageFloatDataCode("tipup"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedTipup), 0.001);

  p_oCohort->GetValue(p_oSubstrateGrid->GetPackageFloatDataCode("freshlog"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedFreshLog), 0.001);

  p_oCohort->GetValue(p_oSubstrateGrid->GetPackageIntDataCode("age"), & iActual);
  EXPECT_EQ(iActual, iAge);

  EXPECT_EQ(NULL, p_oCohort->GetNextPackage());

  //Cell 5
  iY = 4;
  p_oCohort = p_oSubstrateGrid->GetFirstPackageOfCell(iX, iY);
  EXPECT_EQ(NULL, p_oCohort);
}

/////////////////////////////////////////////////////////////////////////////
// VerifySubstrateRun1TS4Cohorts()
/////////////////////////////////////////////////////////////////////////////
void VerifySubstrateRun1TS4Cohorts(clGrid *p_oSubstrateGrid) {
  clPackage * p_oCohort;
  float fExpectedTipup, fExpectedFreshLog, fExpectedScarSoil = 0, fActual;
  int iX, iY, iAge, iActual;

  //Cell 1, cohort 1
  iX = 0; iY = 0;
  fExpectedTipup = 0.049826457;
  fExpectedFreshLog = 0.172756354;
  iAge = 2;

  p_oCohort = p_oSubstrateGrid->GetFirstPackageOfCell(iX, iY);
  ASSERT_TRUE(NULL != p_oCohort);

  p_oCohort->GetValue(p_oSubstrateGrid->GetPackageFloatDataCode("scarsoil"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedScarSoil), 0.001);

  p_oCohort->GetValue(p_oSubstrateGrid->GetPackageFloatDataCode("tipup"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedTipup), 0.001);

  p_oCohort->GetValue(p_oSubstrateGrid->GetPackageFloatDataCode("freshlog"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedFreshLog), 0.001);

  p_oCohort->GetValue(p_oSubstrateGrid->GetPackageIntDataCode("age"), & iActual);
  EXPECT_EQ(iActual, iAge);
  EXPECT_EQ(NULL, p_oCohort->GetNextPackage());

  //Cell 2, cohort 1
  iY = 1;
  fExpectedTipup = 0.117932443;
  fExpectedFreshLog = 0.293457344;
  iAge = 2;
  p_oCohort = p_oSubstrateGrid->GetFirstPackageOfCell(iX, iY);
  ASSERT_TRUE(NULL != p_oCohort);

  p_oCohort->GetValue(p_oSubstrateGrid->GetPackageFloatDataCode("scarsoil"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedScarSoil), 0.001);

  p_oCohort->GetValue(p_oSubstrateGrid->GetPackageFloatDataCode("tipup"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedTipup), 0.001);

  p_oCohort->GetValue(p_oSubstrateGrid->GetPackageFloatDataCode("freshlog"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedFreshLog), 0.001);

  p_oCohort->GetValue(p_oSubstrateGrid->GetPackageIntDataCode("age"), & iActual);
  EXPECT_EQ(iActual, iAge);

  EXPECT_EQ(NULL, p_oCohort->GetNextPackage());

  //Cell 3, cohort 1
  iY = 2;
  fExpectedTipup = 0.014446724;
  fExpectedFreshLog = 0.071340092;
  iAge = 2;
  p_oCohort = p_oSubstrateGrid->GetFirstPackageOfCell(iX, iY);
  ASSERT_TRUE(NULL != p_oCohort);

  p_oCohort->GetValue(p_oSubstrateGrid->GetPackageFloatDataCode("scarsoil"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedScarSoil), 0.001);

  p_oCohort->GetValue(p_oSubstrateGrid->GetPackageFloatDataCode("tipup"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedTipup), 0.001);

  p_oCohort->GetValue(p_oSubstrateGrid->GetPackageFloatDataCode("freshlog"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedFreshLog), 0.001);

  p_oCohort->GetValue(p_oSubstrateGrid->GetPackageIntDataCode("age"), & iActual);
  EXPECT_EQ(iActual, iAge);

  EXPECT_EQ(NULL, p_oCohort->GetNextPackage());

  //Cell 4, cohort 1
  iY = 3;
  fExpectedTipup = 0.020803283;
  fExpectedFreshLog = 0.093905275;
  iAge = 2;

  p_oCohort = p_oSubstrateGrid->GetFirstPackageOfCell(iX, iY);
  ASSERT_TRUE(NULL != p_oCohort);

  p_oCohort->GetValue(p_oSubstrateGrid->GetPackageFloatDataCode("scarsoil"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedScarSoil), 0.001);

  p_oCohort->GetValue(p_oSubstrateGrid->GetPackageFloatDataCode("tipup"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedTipup), 0.001);

  p_oCohort->GetValue(p_oSubstrateGrid->GetPackageFloatDataCode("freshlog"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedFreshLog), 0.001);

  p_oCohort->GetValue(p_oSubstrateGrid->GetPackageIntDataCode("age"), & iActual);
  EXPECT_EQ(iActual, iAge);

  EXPECT_EQ(NULL, p_oCohort->GetNextPackage());

  //Cell 5
  iY = 4;
  p_oCohort = p_oSubstrateGrid->GetFirstPackageOfCell(iX, iY);
  EXPECT_EQ(NULL, p_oCohort);
}

/////////////////////////////////////////////////////////////////////////////
// VerifySubstrateRun1TS1Tipup()
/////////////////////////////////////////////////////////////////////////////
void VerifySubstrateRun1TS1Tipup(clGrid *p_oCalcsGrid) {

  float fExpectedTipup = 0.2, fActual;
  int iCode = p_oCalcsGrid->GetFloatDataCode("newtipup"),
      iX, iY;

  //Cell 1
  iX = 0; iY = 0;
  p_oCalcsGrid->GetValueOfCell(iX, iY, iCode, & fActual);
  EXPECT_LT(fabs(fActual - fExpectedTipup), 0.001);
  //Cell 2
  iY = 1;
  p_oCalcsGrid->GetValueOfCell(iX, iY, iCode, & fActual);
  EXPECT_LT(fabs(fActual - fExpectedTipup), 0.001);
  //Cell 3
  iY = 2;
  p_oCalcsGrid->GetValueOfCell(iX, iY, iCode, & fActual);
  EXPECT_LT(fabs(fActual - fExpectedTipup), 0.001);
  //Cell 4
  iY = 3;
  p_oCalcsGrid->GetValueOfCell(iX, iY, iCode, & fActual);
  EXPECT_LT(fabs(fActual - fExpectedTipup), 0.001);
  //Cell 5
  iY = 4;
  p_oCalcsGrid->GetValueOfCell(iX, iY, iCode, & fActual);
  EXPECT_LT(fabs(fActual - fExpectedTipup), 0.001);
}

/////////////////////////////////////////////////////////////////////////////
// VerifySubstrateRun1TS2Tipup()
/////////////////////////////////////////////////////////////////////////////
void VerifySubstrateRun1TS2Tipup(clGrid *p_oCalcsGrid) {

  float fExpectedTipup, fActual;
  int iCode = p_oCalcsGrid->GetFloatDataCode("newtipup"),
      iX, iY;

  //Cell 1
  iX = 0; iY = 0;
  fExpectedTipup = 0;
  p_oCalcsGrid->GetValueOfCell(iX, iY, iCode, & fActual);
  EXPECT_LT(fabs(fActual - fExpectedTipup), 0.001);
  //Cell 2
  iY = 1;
  fExpectedTipup = 0;
  p_oCalcsGrid->GetValueOfCell(iX, iY, iCode, & fActual);
  EXPECT_LT(fabs(fActual - fExpectedTipup), 0.001);
  //Cell 3
  iY = 2;
  fExpectedTipup = 0.023586489;
  p_oCalcsGrid->GetValueOfCell(iX, iY, iCode, & fActual);
  EXPECT_LT(fabs(fActual - fExpectedTipup), 0.001);
  //Cell 4
  iY = 3;
  fExpectedTipup = 0.038328044;
  p_oCalcsGrid->GetValueOfCell(iX, iY, iCode, & fActual);
  EXPECT_LT(fabs(fActual - fExpectedTipup), 0.001);
  //Cell 5
  iY = 4;
  fExpectedTipup = 0;
  p_oCalcsGrid->GetValueOfCell(iX, iY, iCode, & fActual);
  EXPECT_LT(fabs(fActual - fExpectedTipup), 0.001);
}

/////////////////////////////////////////////////////////////////////////////
// VerifySubstrateRun1TS3Tipup()
/////////////////////////////////////////////////////////////////////////////
void VerifySubstrateRun1TS3Tipup(clGrid *p_oCalcsGrid) {

  float fExpectedTipup, fActual;
  int iCode = p_oCalcsGrid->GetFloatDataCode("newtipup"),
      iX, iY;

  //Cell 1
  iX = 0; iY = 0;
  fExpectedTipup = 0.049826457;
  p_oCalcsGrid->GetValueOfCell(iX, iY, iCode, & fActual);
  EXPECT_LT(fabs(fActual - fExpectedTipup), 0.001);
  //Cell 2
  iY = 1;
  fExpectedTipup = 0.117932443;
  p_oCalcsGrid->GetValueOfCell(iX, iY, iCode, & fActual);
  EXPECT_LT(fabs(fActual - fExpectedTipup), 0.001);
  //Cell 3
  iY = 2;
  fExpectedTipup = 0.014446724;
  p_oCalcsGrid->GetValueOfCell(iX, iY, iCode, & fActual);
  EXPECT_LT(fabs(fActual - fExpectedTipup), 0.001);
  //Cell 4
  iY = 3;
  fExpectedTipup = 0.020803283;
  p_oCalcsGrid->GetValueOfCell(iX, iY, iCode, & fActual);
  EXPECT_LT(fabs(fActual - fExpectedTipup), 0.001);
  //Cell 5
  iY = 4;
  fExpectedTipup = 0;
  p_oCalcsGrid->GetValueOfCell(iX, iY, iCode, & fActual);
  EXPECT_LT(fabs(fActual - fExpectedTipup), 0.001);
}

/////////////////////////////////////////////////////////////////////////////
// VerifySubstrateRun1TS4Tipup()
/////////////////////////////////////////////////////////////////////////////
void VerifySubstrateRun1TS4Tipup(clGrid *p_oCalcsGrid) {

  float fExpectedTipup = 0.0, fActual;
  int iCode = p_oCalcsGrid->GetFloatDataCode("newtipup"),
      iX, iY;

  //Cell 1
  iX = 0; iY = 0;
  p_oCalcsGrid->GetValueOfCell(iX, iY, iCode, & fActual);
  EXPECT_LT(fabs(fActual - fExpectedTipup), 0.001);
  //Cell 2
  iY = 1;
  p_oCalcsGrid->GetValueOfCell(iX, iY, iCode, & fActual);
  EXPECT_LT(fabs(fActual - fExpectedTipup), 0.001);
  //Cell 3
  iY = 2;
  p_oCalcsGrid->GetValueOfCell(iX, iY, iCode, & fActual);
  EXPECT_LT(fabs(fActual - fExpectedTipup), 0.001);
  //Cell 4
  iY = 3;
  p_oCalcsGrid->GetValueOfCell(iX, iY, iCode, & fActual);
  EXPECT_LT(fabs(fActual - fExpectedTipup), 0.001);
  //Cell 5
  iY = 4;
  p_oCalcsGrid->GetValueOfCell(iX, iY, iCode, & fActual);
  EXPECT_LT(fabs(fActual - fExpectedTipup), 0.001);
}

/////////////////////////////////////////////////////////////////////////////
// VerifySubstrateRun1TS1SubstrateArrays()
/////////////////////////////////////////////////////////////////////////////
void VerifySubstrateRun1TS1SubstrateArrays(clGrid *p_oCalcsGrid) {
  std::stringstream sLabel;
  float fExpectedLog = 0.01, //all values are the same
        fActual;
  int *p_iLogCodes = new int[3],
       iX, iY, i;

  //Fresh log arrays
  for ( i = 0; i < 3; i++ )
  {
    sLabel << "freshlog_" << i;
    p_iLogCodes[i] = p_oCalcsGrid->GetFloatDataCode(sLabel.str());
    EXPECT_LT(-1, p_iLogCodes[i]);
    sLabel.str("");
  }

  //Current timestep addition
  //Cell 1
  iX = 0; iY = 0;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[0], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 2
  iY = 1;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[0], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 3
  iY = 2;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[0], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 4
  iY = 3;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[0], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 5
  iY = 4;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[0], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);

  //Last timestep
  fExpectedLog = 0.0;
  //Cell 1
  iX = 0; iY = 0;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[1], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 2
  iY = 1;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[1], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 3
  iY = 2;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[1], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 4
  iY = 3;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[1], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 5
  iY = 4;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[1], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);

  //Timestep - 2
  //Cell 1
  iX = 0; iY = 0;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[2], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 2
  iY = 1;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[2], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 3
  iY = 2;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[2], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 4
  iY = 3;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[2], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 5
  iY = 4;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[2], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);

  //Decayed log arrays
  fExpectedLog = 0.11;
  for ( i = 0; i < 3; i++ )
  {
    sLabel << "declog_" << i;
    p_iLogCodes[i] = p_oCalcsGrid->GetFloatDataCode(sLabel.str());
    EXPECT_LT(-1, p_iLogCodes[i]);
    sLabel.str("");
  }

  //Current timestep addition
  //Cell 1
  iX = 0; iY = 0;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[0], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 2
  iY = 1;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[0], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 3
  iY = 2;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[0], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 4
  iY = 3;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[0], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 5
  iY = 4;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[0], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);

  //Last timestep
  fExpectedLog = 0.0;
  //Cell 1
  iX = 0; iY = 0;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[1], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 2
  iY = 1;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[1], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 3
  iY = 2;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[1], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 4
  iY = 3;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[1], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 5
  iY = 4;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[1], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);

  //Timestep - 2
  //Cell 1
  iX = 0; iY = 0;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[2], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 2
  iY = 1;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[2], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 3
  iY = 2;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[2], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 4
  iY = 3;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[2], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 5
  iY = 4;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[2], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);

  delete[] p_iLogCodes;
}

/////////////////////////////////////////////////////////////////////////////
// VerifySubstrateRun1TS2SubstrateArrays()
/////////////////////////////////////////////////////////////////////////////
void VerifySubstrateRun1TS2SubstrateArrays(clGrid *p_oCalcsGrid) {
  std::stringstream sLabel;
  float fExpectedLog, //all values are the same
        fActual;
  int *p_iLogCodes = new int[3],
       iX, iY, i;

  for ( i = 0; i < 3; i++ )
  {
    sLabel << "freshlog_" << i;
    p_iLogCodes[i] = p_oCalcsGrid->GetFloatDataCode(sLabel.str());
    EXPECT_LT(-1, p_iLogCodes[i]);
    sLabel.str("");
  }

  //Current timestep addition
  //Cell 1
  iX = 0; iY = 0;
  fExpectedLog = 0;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[0], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 2
  iY = 1;
  fExpectedLog = 0;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[0], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 3
  iY = 2;
  fExpectedLog = 0.116266855;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[0], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 4
  iY = 3;
  fExpectedLog = 0.155733;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[0], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 5
  iY = 4;
  fExpectedLog = 0;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[0], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);

  //Last timestep
  //Cell 1
  iX = 0; iY = 0;
  fExpectedLog = 0.01;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[1], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 2
  iY = 1;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[1], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 3
  iY = 2;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[1], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 4
  iY = 3;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[1], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 5
  iY = 4;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[1], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);

  //Timestep - 2
  //Cell 1
  fExpectedLog = 0;
  iX = 0; iY = 0;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[2], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 2
  iY = 1;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[2], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 3
  iY = 2;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[2], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 4
  iY = 3;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[2], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 5
  iY = 4;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[2], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);

  //Decayed log arrays
  for ( i = 0; i < 3; i++ )
  {
    sLabel << "declog_" << i;
    p_iLogCodes[i] = p_oCalcsGrid->GetFloatDataCode(sLabel.str());
    EXPECT_LT(-1, p_iLogCodes[i]);
    sLabel.str("");
  }

  //Current timestep addition
  //Cell 1
  iX = 0; iY = 0;
  fExpectedLog = 0.000487706;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[0], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 2
  iY = 1;
  fExpectedLog = 0.000487706;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[0], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 3
  iY = 2;
  fExpectedLog = 0.000487706;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[0], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 4
  iY = 3;
  fExpectedLog = 0.000487706;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[0], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 5
  iY = 4;
  fExpectedLog = 0.000487706;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[0], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);

  //Last timestep
  //Cell 1
  iX = 0; iY = 0;
  fExpectedLog = 0.11;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[1], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 2
  iY = 1;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[1], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 3
  iY = 2;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[1], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 4
  iY = 3;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[1], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 5
  iY = 4;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[1], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);

  //Timestep - 2
  //Cell 1
  fExpectedLog = 0;
  iX = 0; iY = 0;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[2], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 2
  iY = 1;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[2], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 3
  iY = 2;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[2], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 4
  iY = 3;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[2], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 5
  iY = 4;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[2], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);

  delete[] p_iLogCodes;
}

/////////////////////////////////////////////////////////////////////////////
// VerifySubstrateRun1TS3SubstrateArrays()
/////////////////////////////////////////////////////////////////////////////
void VerifySubstrateRun1TS3SubstrateArrays(clGrid *p_oCalcsGrid) {
  std::stringstream sLabel;
  float fExpectedLog, //all values are the same
        fActual;
  int *p_iLogCodes = new int[3],
       iX, iY, i;

  for ( i = 0; i < 3; i++ )
  {
    sLabel << "freshlog_" << i;
    p_iLogCodes[i] = p_oCalcsGrid->GetFloatDataCode(sLabel.str());
    EXPECT_LT(-1, p_iLogCodes[i]);
    sLabel.str("");
  }

  //Current timestep addition
  //Cell 1
  iX = 0; iY = 0;
  fExpectedLog = 0.172756354;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[0], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 2
  iY = 1;
  fExpectedLog = 0.293457344;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[0], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 3
  iY = 2;
  fExpectedLog = 0.071340092;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[0], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 4
  iY = 3;
  fExpectedLog = 0.093905275;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[0], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 5
  iY = 4;
  fExpectedLog = 0;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[0], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);

  //Last timestep
  //Cell 1
  iX = 0; iY = 0;
  fExpectedLog = 0;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[1], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 2
  iY = 1;
  fExpectedLog = 0;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[1], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 3
  iY = 2;
  fExpectedLog = 0.116266855;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[1], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 4
  iY = 3;
  fExpectedLog = 0.155733;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[1], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 5
  iY = 4;
  fExpectedLog = 0;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[1], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);

  //Timestep - 2
  //Cell 1
  fExpectedLog = 0.01;
  iX = 0; iY = 0;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[2], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 2
  iY = 1;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[2], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 3
  iY = 2;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[2], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 4
  iY = 3;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[2], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 5
  iY = 4;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[2], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);

  //Decayed log arrays
  for ( i = 0; i < 3; i++ )
  {
    sLabel << "declog_" << i;
    p_iLogCodes[i] = p_oCalcsGrid->GetFloatDataCode(sLabel.str());
    EXPECT_LT(-1, p_iLogCodes[i]);
    sLabel.str("");
  }

  //Current timestep addition
  //Cell 1
  iX = 0; iY = 0;
  fExpectedLog = 0.00940399;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[0], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 2
  iY = 1;
  fExpectedLog = 0.009403999;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[0], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 3
  iY = 2;
  fExpectedLog = 0.015074401;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[0], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 4
  iY = 3;
  fExpectedLog = 0.016999187;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[0], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 5
  iY = 4;
  fExpectedLog = 0.009403999;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[0], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);

  //Last timestep
  //Cell 1
  iX = 0; iY = 0;
  fExpectedLog = 0.000487706;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[1], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 2
  iY = 1;
  fExpectedLog = 0.000487706;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[1], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 3
  iY = 2;
  fExpectedLog = 0.000487706;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[1], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 4
  iY = 3;
  fExpectedLog = 0.000487706;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[1], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 5
  iY = 4;
  fExpectedLog = 0.000487706;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[1], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);

  //Timestep - 2
  //Cell 1
  fExpectedLog = 0.11;
  iX = 0; iY = 0;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[2], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 2
  iY = 1;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[2], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 3
  iY = 2;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[2], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 4
  iY = 3;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[2], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 5
  iY = 4;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[2], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);

  delete[] p_iLogCodes;
}

/////////////////////////////////////////////////////////////////////////////
// VerifySubstrateRun1TS4SubstrateArrays()
/////////////////////////////////////////////////////////////////////////////
void VerifySubstrateRun1TS4SubstrateArrays(clGrid *p_oCalcsGrid) {
  std::stringstream sLabel;
  float fExpectedLog, //all values are the same
        fActual;
  int *p_iLogCodes = new int[3],
       iX, iY, i;

  for ( i = 0; i < 3; i++ )
  {
    sLabel << "freshlog_" << i;
    p_iLogCodes[i] = p_oCalcsGrid->GetFloatDataCode(sLabel.str());
    EXPECT_LT(-1, p_iLogCodes[i]);
    sLabel.str("");
  }

  //Current timestep addition
  //Cell 1
  fExpectedLog = 0.0;
  iX = 0; iY = 0;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[0], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 2
  iY = 1;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[0], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 3
  iY = 2;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[0], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 4
  iY = 3;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[0], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 5
  iY = 4;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[0], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);

  //Last timestep
  iX = 0; iY = 0;
  fExpectedLog = 0.172756354;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[1], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 2
  iY = 1;
  fExpectedLog = 0.293457344;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[1], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 3
  iY = 2;
  fExpectedLog = 0.071340092;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[1], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 4
  iY = 3;
  fExpectedLog = 0.093905275;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[1], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 5
  iY = 4;
  fExpectedLog = 0;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[1], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);

  //Timestep - 2
  //Cell 1
  iX = 0; iY = 0;
  fExpectedLog = 0;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[2], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 2
  iY = 1;
  fExpectedLog = 0;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[2], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 3
  iY = 2;
  fExpectedLog = 0.116266855;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[2], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 4
  iY = 3;
  fExpectedLog = 0.155733;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[2], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 5
  iY = 4;
  fExpectedLog = 0;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[2], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);

  //Decayed log arrays
  for ( i = 0; i < 3; i++ )
  {
    sLabel << "declog_" << i;
    p_iLogCodes[i] = p_oCalcsGrid->GetFloatDataCode(sLabel.str());
    EXPECT_LT(-1, p_iLogCodes[i]);
    sLabel.str("");
  }

  //Current timestep addition
  //Cell 1
  fExpectedLog = 0.008425427;
  iX = 0; iY = 0;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[0], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 2
  fExpectedLog = 0.014312084;
  iY = 1;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[0], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 3
  fExpectedLog = 0.112816642;
  iY = 2;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[0], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 4
  fExpectedLog = 0.151031119;
  iY = 3;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[0], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 5
  fExpectedLog = 0;
  iY = 4;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[0], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);

  //Last timestep
  iX = 0; iY = 0;
  fExpectedLog = 0.009403999;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[1], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 2
  iY = 1;
  fExpectedLog = 0.009403999;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[1], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 3
  iY = 2;
  fExpectedLog = 0.015074401;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[1], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 4
  iY = 3;
  fExpectedLog = 0.016999187;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[1], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 5
  iY = 4;
  fExpectedLog = 0.009403999;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[1], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);

  //Timestep - 2
  //Cell 1
  iX = 0; iY = 0;
  fExpectedLog = 0.000487706;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[2], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 2
  iY = 1;
  fExpectedLog = 0.000487706;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[2], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 3
  iY = 2;
  fExpectedLog = 0.000487706;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[2], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 4
  iY = 3;
  fExpectedLog = 0.000487706;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[2], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 5
  iY = 4;
  fExpectedLog = 0.000487706;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[2], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);

  delete[] p_iLogCodes;
}

/////////////////////////////////////////////////////////////////////////////
// VerifySubstrateRun4TS1Proportions()
/////////////////////////////////////////////////////////////////////////////
void VerifySubstrateRun4TS1Proportions(clGrid *p_oSubstrateGrid) {
  float fExpectedTipup, fExpectedFreshLog, fExpectedScarSoil,
        fExpectedDecLog, fExpectedFFMoss, fExpectedFFLitter, fActual;
  int iX, iY;

  //Cell 1
  iX = 0; iY = 0;
  fExpectedScarSoil = 0;
  fExpectedFreshLog = 0.01;
  fExpectedDecLog = 0.11;
  fExpectedTipup = 0.2;
  fExpectedFFMoss = 0.238;
  fExpectedFFLitter = 0.442;
  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("scarsoil"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedScarSoil), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("tipup"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedTipup), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("freshlog"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedFreshLog), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("declog"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedDecLog), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("ffmoss"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedFFMoss), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("fflitter"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedFFLitter), 0.001);

  //Cell 2
  iY = 1;
  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("scarsoil"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedScarSoil), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("tipup"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedTipup), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("freshlog"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedFreshLog), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("ffmoss"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedFFMoss), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("declog"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedDecLog), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("fflitter"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedFFLitter), 0.001);

  //Cell 3
  iY = 2;
  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("scarsoil"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedScarSoil), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("tipup"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedTipup), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("freshlog"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedFreshLog), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("ffmoss"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedFFMoss), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("declog"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedDecLog), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("fflitter"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedFFLitter), 0.001);

  //Cell 4
  iY = 3;
  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("scarsoil"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedScarSoil), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("tipup"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedTipup), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("freshlog"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedFreshLog), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("ffmoss"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedFFMoss), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("declog"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedDecLog), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("fflitter"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedFFLitter), 0.001);

  //Cell 5
  iY = 4;
  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("scarsoil"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedScarSoil), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("tipup"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedTipup), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("freshlog"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedFreshLog), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("ffmoss"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedFFMoss), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("declog"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedDecLog), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("fflitter"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedFFLitter), 0.001);
}

/////////////////////////////////////////////////////////////////////////////
// VerifySubstrateRun4TS2Proportions()
/////////////////////////////////////////////////////////////////////////////
void VerifySubstrateRun4TS2Proportions(clGrid *p_oSubstrateGrid) {
  float fExpectedTipup, fExpectedFreshLog, fExpectedScarSoil = 0,
        fExpectedDecLog, fExpectedFFMoss, fExpectedFFLitter, fActual;
  int iX, iY;

  //Cell 1
  iX = 0; iY = 0;
  fExpectedFreshLog = 0.000964946;
  fExpectedDecLog = 0.019059036;
  fExpectedTipup = 0.199416888;
  fExpectedFFMoss = 0.273195696;
  fExpectedFFLitter = 0.507363435;
  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("scarsoil"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedScarSoil), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("tipup"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedTipup), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("freshlog"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedFreshLog), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("ffmoss"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedFFMoss), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("declog"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedDecLog), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("fflitter"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedFFLitter), 0.001);

  //Cell 2
  iY = 1;
  fExpectedFreshLog = 0.000964946;
  fExpectedDecLog = 0.019059036;
  fExpectedTipup = 0.199416888;
  fExpectedFFLitter = 0.507363435;
  fExpectedFFMoss = 0.273195696;
  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("scarsoil"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedScarSoil), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("tipup"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedTipup), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("freshlog"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedFreshLog), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("declog"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedDecLog), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("ffmoss"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedFFMoss), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("fflitter"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedFFLitter), 0.001);

  //Cell 3
  iY = 2;
  fExpectedFreshLog = 0.11709685;
  fExpectedDecLog = 0.019059036;
  fExpectedTipup = 0.195114258;
  fExpectedFFMoss = 0.23405545;
  fExpectedFFLitter = 0.434674407;
  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("scarsoil"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedScarSoil), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("tipup"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedTipup), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("freshlog"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedFreshLog), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("ffmoss"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedFFMoss), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("declog"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedDecLog), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("fflitter"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedFFLitter), 0.001);

  //Cell 4
  iY = 3;
  fExpectedFreshLog = 0.156510687;
  fExpectedDecLog = 0.019059036;
  fExpectedTipup = 0.199045883;
  fExpectedFFMoss = 0.218884538;
  fExpectedFFLitter = 0.406499856;
  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("scarsoil"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedScarSoil), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("tipup"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedTipup), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("freshlog"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedFreshLog), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("ffmoss"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedFFMoss), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("declog"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedDecLog), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("fflitter"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedFFLitter), 0.001);

  //Cell 5
  iY = 4;
  fExpectedFreshLog = 8.52217E-09;
  fExpectedDecLog = 0.019059036;
  fExpectedTipup = 0.199416888;
  fExpectedFFMoss = 0.273533424;
  fExpectedFFLitter = 0.507990644;
  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("scarsoil"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedScarSoil), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("tipup"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedTipup), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("freshlog"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedFreshLog), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("ffmoss"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedFFMoss), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("declog"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedDecLog), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("fflitter"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedFFLitter), 0.001);
}

/////////////////////////////////////////////////////////////////////////////
// VerifySubstrateRun4TS3Proportions()
/////////////////////////////////////////////////////////////////////////////
void VerifySubstrateRun4TS3Proportions(clGrid *p_oSubstrateGrid) {
  float fExpectedTipup, fExpectedFreshLog, fExpectedScarSoil = 0,
        fExpectedDecLog, fExpectedFFMoss, fExpectedFFLitter, fActual;
  int iX, iY;

  //Cell 1
  iX = 0; iY = 0;
  fExpectedFreshLog = 0.172756354;
  fExpectedDecLog = 0.00270174;
  fExpectedTipup = 0.204196066;
  fExpectedFFMoss = 0.217121044;
  fExpectedFFLitter = 0.403224796;
  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("scarsoil"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedScarSoil), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("tipup"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedTipup), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("freshlog"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedFreshLog), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("ffmoss"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedFFMoss), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("declog"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedDecLog), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("fflitter"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedFFLitter), 0.001);

  //Cell 2
  iY = 1;
  fExpectedFreshLog = 0.293457344;
  fExpectedDecLog = 0.00270174;
  fExpectedTipup = 0.234811166;
  fExpectedFFMoss = 0.164160412;
  fExpectedFFLitter = 0.304869337;
  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("scarsoil"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedScarSoil), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("tipup"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedTipup), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("freshlog"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedFreshLog), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("ffmoss"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedFFMoss), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("declog"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedDecLog), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("fflitter"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedFFLitter), 0.001);

  //Cell 3
  iY = 2;
  fExpectedFreshLog = 0.081596759;
  fExpectedDecLog = 0.107749476;
  fExpectedTipup = 0.192091779;
  fExpectedFFMoss = 0.216496695;
  fExpectedFFLitter = 0.402065291;
  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("scarsoil"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedScarSoil), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("tipup"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedTipup), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("freshlog"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedFreshLog), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("ffmoss"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedFFMoss), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("declog"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedDecLog), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("fflitter"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedFFLitter), 0.001);

  //Cell 4
  iY = 3;
  fExpectedFreshLog = 0.107208893;
  fExpectedDecLog = 0.143407352;
  fExpectedTipup = 0.196311775;
  fExpectedFFMoss = 0.193575193;
  fExpectedFFLitter = 0.359496787;
  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("scarsoil"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedScarSoil), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("tipup"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedTipup), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("freshlog"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedFreshLog), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("ffmoss"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedFFMoss), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("declog"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedDecLog), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("fflitter"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedFFLitter), 0.001);

  //Cell 5
  iY = 4;
  fExpectedFreshLog = 3.24311E-14;
  fExpectedDecLog = 0.00270174;
  fExpectedTipup = 0.19856727;
  fExpectedFFMoss = 0.279555846;
  fExpectedFFLitter = 0.519175143;
  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("scarsoil"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedScarSoil), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("tipup"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedTipup), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("freshlog"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedFreshLog), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("ffmoss"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedFFMoss), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("declog"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedDecLog), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("fflitter"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedFFLitter), 0.001);
}

/////////////////////////////////////////////////////////////////////////////
// VerifySubstrateRun4TS4Proportions()
/////////////////////////////////////////////////////////////////////////////
void VerifySubstrateRun4TS4Proportions(clGrid *p_oSubstrateGrid) {
  float fExpectedTipup, fExpectedFreshLog, fExpectedScarSoil,
        fExpectedDecLog, fExpectedFFMoss, fExpectedFFLitter, fActual;
  int iX, iY;

  fExpectedScarSoil = 0;

  //Cell 1
  iX = 0; iY = 0;
  fExpectedFreshLog = 0.016670049;
  fExpectedDecLog = 0.156249266;
  fExpectedTipup = 0.049681185;
  fExpectedFFMoss = 0.272089825;
  fExpectedFFLitter = 0.505309674;
  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("scarsoil"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedScarSoil), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("tipup"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedTipup), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("freshlog"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedFreshLog), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("ffmoss"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedFFMoss), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("declog"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedDecLog), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("fflitter"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedFFLitter), 0.001);

  //Cell 2
  iY = 1;
  fExpectedFreshLog = 0.028317039;
  fExpectedDecLog = 0.265303266;
  fExpectedTipup = 0.117588604;
  fExpectedFFMoss = 0.206076882;
  fExpectedFFLitter = 0.382714209;
  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("scarsoil"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedScarSoil), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("tipup"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedTipup), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("freshlog"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedFreshLog), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("ffmoss"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedFFMoss), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("declog"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedDecLog), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("fflitter"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedFFLitter), 0.001);

  //Cell 3
  iY = 2;
  fExpectedFreshLog = 0.006883931;
  fExpectedDecLog = 0.085410938;
  fExpectedTipup = 0.035813212;
  fExpectedFFMoss = 0.305162172;
  fExpectedFFLitter = 0.566729747;
  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("scarsoil"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedScarSoil), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("tipup"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedTipup), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("freshlog"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedFreshLog), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("ffmoss"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedFFMoss), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("declog"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedDecLog), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("fflitter"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedFFLitter), 0.001);

  //Cell 4
  iY = 3;
  fExpectedFreshLog = 0.009061349;
  fExpectedDecLog = 0.11285637;
  fExpectedTipup = 0.054431046;
  fExpectedFFMoss = 0.288277932;
  fExpectedFFLitter = 0.535373303;
  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("scarsoil"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedScarSoil), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("tipup"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedTipup), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("freshlog"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedFreshLog), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("ffmoss"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedFFMoss), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("declog"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedDecLog), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("fflitter"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedFFLitter), 0.001);

  //Cell 5
  iY = 4;
  fExpectedFreshLog = 3.24311E-14;
  fExpectedDecLog = 0.000162961;
  fExpectedTipup = 0.19856727;
  fExpectedFFMoss = 0.280444419;
  fExpectedFFLitter = 0.52082535;
  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("scarsoil"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedScarSoil), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("tipup"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedTipup), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("freshlog"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedFreshLog), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("declog"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedDecLog), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("ffmoss"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedFFMoss), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("fflitter"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedFFLitter), 0.001);
}

/////////////////////////////////////////////////////////////////////////////
// VerifySubstrateRun4TS1SubstrateArrays()
/////////////////////////////////////////////////////////////////////////////
void VerifySubstrateRun4TS1SubstrateArrays(clGrid *p_oCalcsGrid) {
  std::stringstream sLabel;
  float fExpectedLog = 0.01, //all values are the same
        fActual;
  int *p_iLogCodes = new int[3],
       iX, iY, i;

  //Fresh log arrays
  for ( i = 0; i < 3; i++ )
  {
    sLabel << "freshlog_" << i;
    p_iLogCodes[i] = p_oCalcsGrid->GetFloatDataCode(sLabel.str());
    EXPECT_LT(-1, p_iLogCodes[i]);
    sLabel.str("");
  }

  //Current timestep addition
  //Cell 1
  iX = 0; iY = 0;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[0], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 2
  iY = 1;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[0], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 3
  iY = 2;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[0], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 4
  iY = 3;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[0], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 5
  iY = 4;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[0], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);

  //Last timestep
  fExpectedLog = 0.0;
  //Cell 1
  iX = 0; iY = 0;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[1], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 2
  iY = 1;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[1], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 3
  iY = 2;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[1], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 4
  iY = 3;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[1], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 5
  iY = 4;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[1], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);

  //Timestep - 2
  //Cell 1
  iX = 0; iY = 0;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[2], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 2
  iY = 1;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[2], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 3
  iY = 2;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[2], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 4
  iY = 3;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[2], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 5
  iY = 4;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[2], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);

  //Decayed log arrays
  fExpectedLog = 0.11;
  for ( i = 0; i < 3; i++ )
  {
    sLabel << "declog_" << i;
    p_iLogCodes[i] = p_oCalcsGrid->GetFloatDataCode(sLabel.str());
    EXPECT_LT(-1, p_iLogCodes[i]);
    sLabel.str("");
  }

  //Current timestep addition
  //Cell 1
  iX = 0; iY = 0;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[0], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 2
  iY = 1;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[0], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 3
  iY = 2;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[0], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 4
  iY = 3;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[0], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 5
  iY = 4;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[0], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);

  //Last timestep
  fExpectedLog = 0;
  //Cell 1
  iX = 0; iY = 0;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[1], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 2
  iY = 1;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[1], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 3
  iY = 2;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[1], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 4
  iY = 3;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[1], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 5
  iY = 4;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[1], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);

  //Timestep - 2
  //Cell 1
  iX = 0; iY = 0;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[2], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 2
  iY = 1;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[2], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 3
  iY = 2;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[2], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 4
  iY = 3;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[2], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 5
  iY = 4;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[2], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);

  delete[] p_iLogCodes;
}

/////////////////////////////////////////////////////////////////////////////
// VerifySubstrateRun4TS2SubstrateArrays()
/////////////////////////////////////////////////////////////////////////////
void VerifySubstrateRun4TS2SubstrateArrays(clGrid *p_oCalcsGrid) {
  std::stringstream sLabel;
  float fExpectedLog, //all values are the same
        fActual;
  int *p_iLogCodes = new int[3],
       iX, iY, i;

  for ( i = 0; i < 3; i++ )
  {
    sLabel << "freshlog_" << i;
    p_iLogCodes[i] = p_oCalcsGrid->GetFloatDataCode(sLabel.str());
    EXPECT_LT(-1, p_iLogCodes[i]);
    sLabel.str("");
  }

  //Current timestep addition
  //Cell 1
  iX = 0; iY = 0;
  fExpectedLog = 0;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[0], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 2
  iY = 1;
  fExpectedLog = 0;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[0], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 3
  iY = 2;
  fExpectedLog = 0.116266855;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[0], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 4
  iY = 3;
  fExpectedLog = 0.155733;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[0], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 5
  iY = 4;
  fExpectedLog = 0;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[0], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);

  //Last timestep
  //Cell 1
  iX = 0; iY = 0;
  fExpectedLog = 0.01;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[1], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 2
  iY = 1;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[1], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 3
  iY = 2;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[1], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 4
  iY = 3;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[1], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 5
  iY = 4;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[1], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);

  //Timestep - 2
  //Cell 1
  fExpectedLog = 0;
  iX = 0; iY = 0;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[2], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 2
  iY = 1;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[2], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 3
  iY = 2;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[2], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 4
  iY = 3;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[2], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 5
  iY = 4;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[2], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);

  //Decayed log arrays
  for ( i = 0; i < 3; i++ )
  {
    sLabel << "declog_" << i;
    p_iLogCodes[i] = p_oCalcsGrid->GetFloatDataCode(sLabel.str());
    EXPECT_LT(-1, p_iLogCodes[i]);
    sLabel.str("");
  }

  //Current timestep addition
  //Cell 1
  iX = 0; iY = 0;
  fExpectedLog = 0.009035054;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[0], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 2
  iY = 1;
  fExpectedLog = 0.009035054;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[0], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 3
  iY = 2;
  fExpectedLog = 0.009035054;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[0], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 4
  iY = 3;
  fExpectedLog = 0.009035054;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[0], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 5
  iY = 4;
  fExpectedLog = 0.009035054;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[0], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);

  //Last timestep
  //Cell 1
  iX = 0; iY = 0;
  fExpectedLog = 0.11;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[1], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 2
  iY = 1;
  fExpectedLog = 0.11;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[1], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 3
  iY = 2;
  fExpectedLog = 0.11;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[1], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 4
  iY = 3;
  fExpectedLog = 0.11;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[1], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 5
  iY = 4;
  fExpectedLog = 0.11;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[1], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);

  //Timestep - 2
  //Cell 1
  iX = 0; iY = 0;
  fExpectedLog = 0;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[2], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 2
  iY = 1;
  fExpectedLog = 0;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[2], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 3
  iY = 2;
  fExpectedLog = 0;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[2], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 4
  iY = 3;
  fExpectedLog = 0;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[2], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 5
  iY = 4;
  fExpectedLog = 0;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[2], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);

  delete[] p_iLogCodes;
}

/////////////////////////////////////////////////////////////////////////////
// VerifySubstrateRun4TS3SubstrateArrays()
/////////////////////////////////////////////////////////////////////////////
void VerifySubstrateRun4TS3SubstrateArrays(clGrid *p_oCalcsGrid) {
  std::stringstream sLabel;
  float fExpectedLog, //all values are the same
        fActual;
  int *p_iLogCodes = new int[3],
       iX, iY, i;

  for ( i = 0; i < 3; i++ )
  {
    sLabel << "freshlog_" << i;
    p_iLogCodes[i] = p_oCalcsGrid->GetFloatDataCode(sLabel.str());
    EXPECT_LT(-1, p_iLogCodes[i]);
    sLabel.str("");
  }

  //Current timestep addition
  //Cell 1
  iX = 0; iY = 0;
  fExpectedLog = 0.172756354;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[0], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 2
  iY = 1;
  fExpectedLog = 0.293457344;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[0], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 3
  iY = 2;
  fExpectedLog = 0.071340092;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[0], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 4
  iY = 3;
  fExpectedLog = 0.093905275;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[0], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 5
  iY = 4;
  fExpectedLog = 0;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[0], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);

  //Last timestep
  //Cell 1
  iX = 0; iY = 0;
  fExpectedLog = 0;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[1], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 2
  iY = 1;
  fExpectedLog = 0;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[1], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 3
  iY = 2;
  fExpectedLog = 0.116266855;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[1], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 4
  iY = 3;
  fExpectedLog = 0.155733;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[1], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 5
  iY = 4;
  fExpectedLog = 0;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[1], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);

  //Timestep - 2
  //Cell 1
  fExpectedLog = 0.01;
  iX = 0; iY = 0;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[2], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 2
  iY = 1;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[2], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 3
  iY = 2;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[2], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 4
  iY = 3;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[2], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 5
  iY = 4;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[2], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);

  //Decayed log arrays
  for ( i = 0; i < 3; i++ )
  {
    sLabel << "declog_" << i;
    p_iLogCodes[i] = p_oCalcsGrid->GetFloatDataCode(sLabel.str());
    EXPECT_LT(-1, p_iLogCodes[i]);
    sLabel.str("");
  }

  //Current timestep addition
  //Cell 1
  iX = 0; iY = 0;
  fExpectedLog = 0.000964946;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[0], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 2
  iY = 1;
  fExpectedLog = 0.000964946;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[0], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 3
  iY = 2;
  fExpectedLog = 0.106012681;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[0], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 4
  iY = 3;
  fExpectedLog = 0.141670557;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[0], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 5
  iY = 4;
  fExpectedLog = 0.000964946;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[0], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);

  //Last timestep
  //Cell 1
  iX = 0; iY = 0;
  fExpectedLog = 0.009035054;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[1], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 2
  iY = 1;
  fExpectedLog = 0.009035054;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[1], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 3
  iY = 2;
  fExpectedLog = 0.009035054;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[1], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 4
  iY = 3;
  fExpectedLog = 0.009035054;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[1], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 5
  iY = 4;
  fExpectedLog = 0.009035054;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[1], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);

  //Timestep - 2
  //Cell 1
  iX = 0; iY = 0;
  fExpectedLog = 0.11;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[2], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 2
  iY = 1;
  fExpectedLog = 0.11;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[2], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 3
  iY = 2;
  fExpectedLog = 0.11;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[2], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 4
  iY = 3;
  fExpectedLog = 0.11;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[2], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 5
  iY = 4;
  fExpectedLog = 0.11;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[2], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);

  delete[] p_iLogCodes;
}

/////////////////////////////////////////////////////////////////////////////
// VerifySubstrateRun4TS4SubstrateArrays()
/////////////////////////////////////////////////////////////////////////////
void VerifySubstrateRun4TS4SubstrateArrays(clGrid *p_oCalcsGrid) {
  std::stringstream sLabel;
  float fExpectedLog, //all values are the same
        fActual;
  int *p_iLogCodes = new int[3],
       iX, iY, i;

  for ( i = 0; i < 3; i++ )
  {
    sLabel << "freshlog_" << i;
    p_iLogCodes[i] = p_oCalcsGrid->GetFloatDataCode(sLabel.str());
    EXPECT_LT(-1, p_iLogCodes[i]);
    sLabel.str("");
  }

  //Current timestep addition
  //Cell 1
  fExpectedLog = 0.0;
  iX = 0; iY = 0;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[0], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 2
  iY = 1;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[0], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 3
  iY = 2;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[0], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 4
  iY = 3;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[0], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 5
  iY = 4;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[0], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);

  //Last timestep
  iX = 0; iY = 0;
  fExpectedLog = 0.172756354;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[1], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 2
  iY = 1;
  fExpectedLog = 0.293457344;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[1], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 3
  iY = 2;
  fExpectedLog = 0.071340092;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[1], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 4
  iY = 3;
  fExpectedLog = 0.093905275;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[1], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 5
  iY = 4;
  fExpectedLog = 0;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[1], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);

  //Timestep - 2
  //Cell 1
  iX = 0; iY = 0;
  fExpectedLog = 0;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[2], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 2
  iY = 1;
  fExpectedLog = 0;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[2], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 3
  iY = 2;
  fExpectedLog = 0.116266855;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[2], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 4
  iY = 3;
  fExpectedLog = 0.155733;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[2], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 5
  iY = 4;
  fExpectedLog = 0;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[2], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);

  //Decayed log arrays
  for ( i = 0; i < 3; i++ )
  {
    sLabel << "declog_" << i;
    p_iLogCodes[i] = p_oCalcsGrid->GetFloatDataCode(sLabel.str());
    EXPECT_LT(-1, p_iLogCodes[i]);
    sLabel.str("");
  }

  //Current timestep addition
  //Cell 1
  iX = 0; iY = 0;
  fExpectedLog = 0.156086305;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[0], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 2
  iY = 1;
  fExpectedLog = 0.265140305;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[0], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 3
  iY = 2;
  fExpectedLog = 0.075675281;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[0], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 4
  iY = 3;
  fExpectedLog = 0.099871314;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[0], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 5
  iY = 4;
  fExpectedLog = 0;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[0], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);

  //Last timestep
  //Cell 1
  iX = 0; iY = 0;
  fExpectedLog = 0.000964946;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[1], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 2
  iY = 1;
  fExpectedLog = 0.000964946;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[1], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 3
  iY = 2;
  fExpectedLog = 0.106012681;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[1], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 4
  iY = 3;
  fExpectedLog = 0.141670557;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[1], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 5
  iY = 4;
  fExpectedLog = 0.000964946;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[1], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);

  //Timestep - 2
  //Cell 1
  iX = 0; iY = 0;
  fExpectedLog = 0.009035054;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[2], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 2
  iY = 1;
  fExpectedLog = 0.009035054;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[2], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 3
  iY = 2;
  fExpectedLog = 0.009035054;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[2], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 4
  iY = 3;
  fExpectedLog = 0.009035054;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[2], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 5
  iY = 4;
  fExpectedLog = 0.009035054;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[2], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);

  delete[] p_iLogCodes;
}


/////////////////////////////////////////////////////////////////////////////
// TestHarvestSubstrate()
// Verifies that harvest substrate is calculated correctly. WriteSubstrateXMLFile1()
// produces all cut types in various grid cells; in those cells, the substrate
// proportions should match the harvest conditions, and there should be only
// one cohort with the harvest's conditions.
/////////////////////////////////////////////////////////////////////////////
TEST(Substrate, TestHarvestSubstrate) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    clTreePopulation *p_oPop;
    clGrid * p_oSubstrateGrid;
    clPackage * p_oCohort;
    float fExpectedScarSoil, fExpectedFFMoss, fExpectedFFLitter, fExpectedTipup, fExpectedDecLog, fExpectedFreshLog, fActual;
    int iX, iY;

    //Feed file # 1 and run it
    p_oSimManager->ReadFile(WriteSubstrateXMLFile1());
    p_oPop = (clTreePopulation*) p_oSimManager->GetPopulationObject("treepopulation");
    p_oSimManager->RunSim(1);
    p_oPop->CreateTree(1, 1, 0, clTreePopulation::adult, 12);
    p_oPop->CreateTree(1, 9, 0, clTreePopulation::adult, 12);
    p_oPop->CreateTree(1, 17, 0, clTreePopulation::adult, 12);

    p_oSimManager->RunSim(1);

    p_oSubstrateGrid = p_oSimManager->GetGridObject("Substrate");

    //Verify the substrates of the clear cut cell
    fExpectedScarSoil = 0.36;
    fExpectedFFMoss = 0.126;
    fExpectedFFLitter = 0.054;
    fExpectedTipup = 0.28;
    fExpectedDecLog = 0.01;
    fExpectedFreshLog = 0.17;
    iX = 0; iY = 1;

    p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("scarsoil"), & fActual);
    EXPECT_LT(fabs(fActual - fExpectedScarSoil), 0.001);

    p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("ffmoss"), & fActual);
    EXPECT_LT(fabs(fActual - fExpectedFFMoss), 0.001);

    p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("fflitter"), & fActual);
    EXPECT_LT(fabs(fActual - fExpectedFFLitter), 0.001);

    p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("tipup"), & fActual);
    EXPECT_LT(fabs(fActual - fExpectedTipup), 0.001);

    p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("freshlog"), & fActual);
    EXPECT_LT(fabs(fActual - fExpectedFreshLog), 0.001);

    p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("declog"), & fActual);
    EXPECT_LT(fabs(fActual - fExpectedDecLog), 0.001);

    //There should be one cohort per cell which also matches the clear cut conditions
    p_oCohort = p_oSubstrateGrid->GetFirstPackageOfCell(iX, iY);
    ASSERT_TRUE(NULL != p_oCohort);

    p_oCohort->GetValue(p_oSubstrateGrid->GetPackageFloatDataCode("scarsoil"), & fActual);
    EXPECT_LT(fabs(fActual - fExpectedScarSoil), 0.001);

    p_oCohort->GetValue(p_oSubstrateGrid->GetPackageFloatDataCode("tipup"), & fActual);
    EXPECT_LT(fabs(fActual - fExpectedTipup), 0.001);

    p_oCohort->GetValue(p_oSubstrateGrid->GetPackageFloatDataCode("freshlog"), & fActual);
    EXPECT_LT(fabs(fActual - fExpectedFreshLog), 0.001);

    EXPECT_EQ(NULL, p_oCohort->GetNextPackage());

    //Verify the substrates of the gap cut cell
    fExpectedScarSoil = 0.45;
    fExpectedFFMoss = 0.084;
    fExpectedFFLitter = 0.036;
    fExpectedTipup = 0.34;
    fExpectedDecLog = 0.0;
    fExpectedFreshLog = 0.09;
    iX = 0; iY = 0;

    p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("scarsoil"), & fActual);
    EXPECT_LT(fabs(fActual - fExpectedScarSoil), 0.001);

    p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("ffmoss"), & fActual);
    EXPECT_LT(fabs(fActual - fExpectedFFMoss), 0.001);

    p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("fflitter"), & fActual);
    EXPECT_LT(fabs(fActual - fExpectedFFLitter), 0.001);

    p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("tipup"), & fActual);
    EXPECT_LT(fabs(fActual - fExpectedTipup), 0.001);

    p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("freshlog"), & fActual);
    EXPECT_LT(fabs(fActual - fExpectedFreshLog), 0.001);

    p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("declog"), & fActual);
    EXPECT_LT(fabs(fActual - fExpectedDecLog), 0.001);

    //There should be one cohort per cell which also matches the clear cut conditions
    p_oCohort = p_oSubstrateGrid->GetFirstPackageOfCell(iX, iY);

    p_oCohort->GetValue(p_oSubstrateGrid->GetPackageFloatDataCode("scarsoil"), & fActual);
    EXPECT_LT(fabs(fActual - fExpectedScarSoil), 0.001);

    p_oCohort->GetValue(p_oSubstrateGrid->GetPackageFloatDataCode("tipup"), & fActual);
    EXPECT_LT(fabs(fActual - fExpectedTipup), 0.001);

    p_oCohort->GetValue(p_oSubstrateGrid->GetPackageFloatDataCode("freshlog"), & fActual);
    EXPECT_LT(fabs(fActual - fExpectedFreshLog), 0.001);

    EXPECT_EQ(NULL, p_oCohort->GetNextPackage());

    //Verify the substrates of the partial cut cell
    fExpectedScarSoil = 0.17;
    fExpectedFFMoss = 0.406;
    fExpectedFFLitter = 0.174;
    fExpectedTipup = 0.15;
    fExpectedDecLog = 0.04;
    fExpectedFreshLog = 0.06;
    iX = 0; iY = 2;

    p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("scarsoil"), & fActual);
    EXPECT_LT(fabs(fActual - fExpectedScarSoil), 0.001);

    p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("ffmoss"), & fActual);
    EXPECT_LT(fabs(fActual - fExpectedFFMoss), 0.001);

    p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("fflitter"), & fActual);
    EXPECT_LT(fabs(fActual - fExpectedFFLitter), 0.001);

    p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("tipup"), & fActual);
    EXPECT_LT(fabs(fActual - fExpectedTipup), 0.001);

    p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("freshlog"), & fActual);
    EXPECT_LT(fabs(fActual - fExpectedFreshLog), 0.001);

    p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("declog"), & fActual);
    EXPECT_LT(fabs(fActual - fExpectedDecLog), 0.001);

    //There should be one cohort per cell which also matches the clear cut conditions
    p_oCohort = p_oSubstrateGrid->GetFirstPackageOfCell(iX, iY);

    p_oCohort->GetValue(p_oSubstrateGrid->GetPackageFloatDataCode("scarsoil"), & fActual);
    EXPECT_LT(fabs(fActual - fExpectedScarSoil), 0.001);

    p_oCohort->GetValue(p_oSubstrateGrid->GetPackageFloatDataCode("tipup"), & fActual);
    EXPECT_LT(fabs(fActual - fExpectedTipup), 0.001);

    p_oCohort->GetValue(p_oSubstrateGrid->GetPackageFloatDataCode("freshlog"), & fActual);
    EXPECT_LT(fabs(fActual - fExpectedFreshLog), 0.001);

    EXPECT_EQ(NULL, p_oCohort->GetNextPackage());
    delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

/////////////////////////////////////////////////////////////////////////////
// TestSubstrateGridSetup()
// Tests aspects of substrate grid setup. This will enter three parameter
// files:
// -- With harvest
// -- With no harvest and Substrate and substratecalcs grid maps
// -- With neither
//
// In the first case, grid cell resolution should match harvest;
// in the second, it should be what was specified in the map; in the third,
// it should match the plot. This will also make sure that initial conditions
// have been correctly populated.
/////////////////////////////////////////////////////////////////////////////
TEST(Substrate, TestSubstrateGridSetup) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    clGrid * p_oSubstrateGrid, *p_oSubstrateCalcsGrid;
    float fVal;

    //Feed file # 1 and make sure grid resolutions are right
    p_oSimManager->ReadFile(WriteSubstrateXMLFile1());
    p_oSubstrateGrid = p_oSimManager->GetGridObject("Substrate");
    EXPECT_LT(fabs(p_oSubstrateGrid->GetLengthXCells() - 8), 0.001);
    EXPECT_LT(fabs(p_oSubstrateGrid->GetLengthYCells() - 8), 0.001);

    //Feed file # 2 and make sure grid resolutions are right
    p_oSimManager->ReadFile(WriteSubstrateXMLFile5());
    p_oSubstrateGrid = p_oSimManager->GetGridObject("Substrate");
    EXPECT_LT(fabs(p_oSubstrateGrid->GetLengthXCells() - 3), 0.001);
    EXPECT_LT(fabs(p_oSubstrateGrid->GetLengthYCells() - 2), 0.001);
    //Make sure the substrate calcs resolutions are right and the values got read
    p_oSubstrateCalcsGrid = p_oSimManager->GetGridObject("substratecalcs");
    EXPECT_LT(fabs(p_oSubstrateCalcsGrid->GetLengthXCells() - 3), 0.001);
    EXPECT_LT(fabs(p_oSubstrateCalcsGrid->GetLengthYCells() - 2), 0.001);
    p_oSubstrateCalcsGrid->GetValueOfCell(0, 0, p_oSubstrateCalcsGrid->GetFloatDataCode("newtipup"), &fVal);
    EXPECT_LT(fabs(fVal - 0.1), 0.001);
    p_oSubstrateCalcsGrid->GetValueOfCell(0, 0, p_oSubstrateCalcsGrid->GetFloatDataCode("freshlog_0"), &fVal);
    EXPECT_LT(fabs(fVal - 0.01), 0.001);
    p_oSubstrateCalcsGrid->GetValueOfCell(0, 0, p_oSubstrateCalcsGrid->GetFloatDataCode("freshlog_1"), &fVal);
    EXPECT_LT(fabs(fVal - 0.02), 0.001);
    p_oSubstrateCalcsGrid->GetValueOfCell(0, 0, p_oSubstrateCalcsGrid->GetFloatDataCode("freshlog_2"), &fVal);
    EXPECT_LT(fabs(fVal - 0.03), 0.001);
    p_oSubstrateCalcsGrid->GetValueOfCell(0, 0, p_oSubstrateCalcsGrid->GetFloatDataCode("freshlog_3"), &fVal);
    EXPECT_LT(fabs(fVal - 0.04), 0.001);
    p_oSubstrateCalcsGrid->GetValueOfCell(0, 0, p_oSubstrateCalcsGrid->GetFloatDataCode("freshlog_4"), &fVal);
    EXPECT_LT(fabs(fVal - 0.05), 0.001);
    p_oSubstrateCalcsGrid->GetValueOfCell(0, 0, p_oSubstrateCalcsGrid->GetFloatDataCode("freshlog_5"), &fVal);
    EXPECT_LT(fabs(fVal - 0.06), 0.001);
    p_oSubstrateCalcsGrid->GetValueOfCell(0, 0, p_oSubstrateCalcsGrid->GetFloatDataCode("freshlog_6"), &fVal);
    EXPECT_LT(fabs(fVal - 0.07), 0.001);
    p_oSubstrateCalcsGrid->GetValueOfCell(0, 0, p_oSubstrateCalcsGrid->GetFloatDataCode("freshlog_7"), &fVal);
    EXPECT_LT(fabs(fVal - 0.08), 0.001);
    p_oSubstrateCalcsGrid->GetValueOfCell(0, 0, p_oSubstrateCalcsGrid->GetFloatDataCode("freshlog_8"), &fVal);
    EXPECT_LT(fabs(fVal - 0.09), 0.001);
    p_oSubstrateCalcsGrid->GetValueOfCell(0, 0, p_oSubstrateCalcsGrid->GetFloatDataCode("freshlog_9"), &fVal);
    EXPECT_LT(fabs(fVal - 0.11), 0.001);
    p_oSubstrateCalcsGrid->GetValueOfCell(0, 0, p_oSubstrateCalcsGrid->GetFloatDataCode("declog_0"), &fVal);
    EXPECT_LT(fabs(fVal - 0.11), 0.001);
    p_oSubstrateCalcsGrid->GetValueOfCell(0, 0, p_oSubstrateCalcsGrid->GetFloatDataCode("declog_1"), &fVal);
    EXPECT_LT(fabs(fVal - 0.12), 0.001);
    p_oSubstrateCalcsGrid->GetValueOfCell(0, 0, p_oSubstrateCalcsGrid->GetFloatDataCode("declog_2"), &fVal);
    EXPECT_LT(fabs(fVal - 0.13), 0.001);
    p_oSubstrateCalcsGrid->GetValueOfCell(0, 0, p_oSubstrateCalcsGrid->GetFloatDataCode("declog_3"), &fVal);
    EXPECT_LT(fabs(fVal - 0.14), 0.001);
    p_oSubstrateCalcsGrid->GetValueOfCell(0, 0, p_oSubstrateCalcsGrid->GetFloatDataCode("declog_4"), &fVal);
    EXPECT_LT(fabs(fVal - 0.15), 0.001);
    p_oSubstrateCalcsGrid->GetValueOfCell(0, 0, p_oSubstrateCalcsGrid->GetFloatDataCode("declog_5"), &fVal);
    EXPECT_LT(fabs(fVal - 0.16), 0.001);
    p_oSubstrateCalcsGrid->GetValueOfCell(0, 0, p_oSubstrateCalcsGrid->GetFloatDataCode("declog_6"), &fVal);
    EXPECT_LT(fabs(fVal - 0.17), 0.001);
    p_oSubstrateCalcsGrid->GetValueOfCell(0, 0, p_oSubstrateCalcsGrid->GetFloatDataCode("declog_7"), &fVal);
    EXPECT_LT(fabs(fVal - 0.18), 0.001);
    p_oSubstrateCalcsGrid->GetValueOfCell(0, 0, p_oSubstrateCalcsGrid->GetFloatDataCode("declog_8"), &fVal);
    EXPECT_LT(fabs(fVal - 0.19), 0.001);
    p_oSubstrateCalcsGrid->GetValueOfCell(0, 0, p_oSubstrateCalcsGrid->GetFloatDataCode("declog_9"), &fVal);
    EXPECT_LT(fabs(fVal - 0.20), 0.001);

    //Feed file # 3 and make sure grid resolutions are right
    p_oSimManager->ReadFile(WriteSubstrateXMLFile2());
    p_oSubstrateGrid = p_oSimManager->GetGridObject("Substrate");
    EXPECT_LT(fabs(p_oSubstrateGrid->GetLengthXCells() - 8), 0.001);
    EXPECT_LT(fabs(p_oSubstrateGrid->GetLengthYCells() - 8), 0.001);

    //Now check that initial conditions were correctly populated
    clPackage * p_oCohort;
    float fExpectedScarSoil = 0, fExpectedFFMoss = 0.238, fExpectedFFLitter = 0.442,
        fExpectedTipup = 0.2, fExpectedDecLog = 0.11,
        fExpectedFreshLog = 0.01, fActual;
    int iNumXCells = p_oSubstrateGrid->GetNumberXCells(), iNumYCells = p_oSubstrateGrid->GetNumberYCells(), iX, iY;

    for (iX = 0; iX < iNumXCells; iX++)
    {
      for (iY = 0; iY < iNumYCells; iY++)
      {

        //The values all should match the parameter file initial conditions
        p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("scarsoil"), & fActual);
        EXPECT_LT(fabs(fActual - fExpectedScarSoil), 0.001);

        p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("ffmoss"), & fActual);
        EXPECT_LT(fabs(fActual - fExpectedFFMoss), 0.001);

        p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("fflitter"), & fActual);
        EXPECT_LT(fabs(fActual - fExpectedFFLitter), 0.001);

        p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("tipup"), & fActual);
        EXPECT_LT(fabs(fActual - fExpectedTipup), 0.001);

        p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("freshlog"), & fActual);
        EXPECT_LT(fabs(fActual - fExpectedFreshLog), 0.001);

        p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("declog"), & fActual);
        EXPECT_LT(fabs(fActual - fExpectedDecLog), 0.001);

        //There should be one cohort per cell which also matches the initial conditions
        p_oCohort = p_oSubstrateGrid->GetFirstPackageOfCell(iX, iY);

        p_oCohort->GetValue(p_oSubstrateGrid->GetPackageFloatDataCode("scarsoil"), & fActual);
        EXPECT_LT(fabs(fActual - fExpectedScarSoil), 0.001);

        p_oCohort->GetValue(p_oSubstrateGrid->GetPackageFloatDataCode("tipup"), & fActual);
        EXPECT_LT(fabs(fActual - fExpectedTipup), 0.001);

        p_oCohort->GetValue(p_oSubstrateGrid->GetPackageFloatDataCode("freshlog"), & fActual);
        EXPECT_LT(fabs(fActual - fExpectedFreshLog), 0.001);

        EXPECT_EQ(NULL, p_oCohort->GetNextPackage());
      }
    }
    delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

/////////////////////////////////////////////////////////////////////////////
// WriteSubstrateXMLFile2()
/////////////////////////////////////////////////////////////////////////////
const char* WriteSubstrateXMLFile2()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06010101\">"
       << "<plot>"
       << "<timesteps>5</timesteps>"
       << "<yearsPerTimestep>1</yearsPerTimestep>" << "<randomSeed>1</randomSeed>"
       << "<plot_lenX>200.0</plot_lenX>"
       << "<plot_lenY>200.0</plot_lenY>"
       << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
       << "<plot_temp_C>12.88171785</plot_temp_C>"
       << "<plot_latitude>55.37</plot_latitude>"
       << "</plot>";

  WriteSubstrateCommonTreeStuff(oOut);

  oOut << "<behaviorList>"
       //Have to have a StochasticMortality behavior so dead is registered
       << "<behavior>"
       << "<behaviorName>StochasticMortality</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>Substrate</behaviorName>"
       << "<version>2.1</version>"
       << "<listPosition>2</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "</behavior>"
       << "</behaviorList>"
       << "<StochasticMortality1>"
       << "<mo_stochasticMortRate>"
       << "<mo_smrVal species=\"Species_1\">0.0</mo_smrVal>"
       << "</mo_stochasticMortRate>"
       << "</StochasticMortality1>"
       << "<Substrate2>"
       << "<su_scarSoilDecayAlpha>-5.1E-4</su_scarSoilDecayAlpha>"
       << "<su_scarSoilDecayBeta>4.4</su_scarSoilDecayBeta>"
       << "<su_tipupDecayAlpha>-7.0E-4</su_tipupDecayAlpha>"
       << "<su_tipupDecayBeta>4.3</su_tipupDecayBeta>"
       << "<su_freshLogDecayAlpha>-0.05</su_freshLogDecayAlpha>"
       << "<su_freshLogDecayBeta>6.5</su_freshLogDecayBeta>"
       << "<su_decayedLogDecayAlpha>-0.7985</su_decayedLogDecayAlpha>"
       << "<su_decayedLogDecayBeta>1</su_decayedLogDecayBeta>"
       << "<su_maxNumberDecayYears>3</su_maxNumberDecayYears>"
       << "<su_initialScarSoil>0.0</su_initialScarSoil>"
       << "<su_initialTipup>0.2</su_initialTipup>"
       << "<su_initialFreshLog>0.01</su_initialFreshLog>"
       << "<su_initialDecayedLog>0.11</su_initialDecayedLog>"
       << "<su_propOfDeadFall>"
       << "<su_podfVal species=\"Species_1\">1</su_podfVal>"
       << "</su_propOfDeadFall>"
       << "<su_propOfFallUproot>"
       << "<su_pofuVal species=\"Species_1\">1</su_pofuVal>"
       << "</su_propOfFallUproot>"
       << "<su_propOfSnagsUproot>"
       << "<su_posuVal species=\"Species_1\">1</su_posuVal>"
       << "</su_propOfSnagsUproot>"
       << "<su_mossProportion>0.35</su_mossProportion>"
       << "<su_directionalTreeFall>0</su_directionalTreeFall>"
       << "<su_rootTipupFactor>3.1</su_rootTipupFactor>"
       << "</Substrate2>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteSubstrateXMLFile4()
/////////////////////////////////////////////////////////////////////////////
const char* WriteSubstrateXMLFile4()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06010101\">"
       << "<plot>"
       << "<timesteps>10</timesteps>"
       << "<yearsPerTimestep>3</yearsPerTimestep>"
       << "<randomSeed>1</randomSeed>"
       << "<plot_lenX>270.0</plot_lenX>"
       << "<plot_lenY>270.0</plot_lenY>"
       << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
       << "<plot_temp_C>12.88171785</plot_temp_C>"
       << "<plot_latitude>55.37</plot_latitude>"
       << "</plot>"
       << "<trees>"
       << "<tr_speciesList>"
       << "<tr_species speciesName=\"Species_1\"/>"
       << "<tr_species speciesName=\"Species_2\"/>"
       << "<tr_species speciesName=\"Species_3\"/>"
       << "</tr_speciesList>"
       << "<tr_seedDiam10Cm>0.1</tr_seedDiam10Cm>"
       << "<tr_minAdultDBH>"
       << "<tr_madVal species=\"Species_1\">10.0</tr_madVal>"
       << "<tr_madVal species=\"Species_2\">10.0</tr_madVal>"
       << "<tr_madVal species=\"Species_3\">10.0</tr_madVal>"
       << "</tr_minAdultDBH>"
       << "<tr_maxSeedlingHeight>"
       << "<tr_mshVal species=\"Species_1\">1.35</tr_mshVal>"
       << "<tr_mshVal species=\"Species_2\">1.35</tr_mshVal>"
       << "<tr_mshVal species=\"Species_3\">1.35</tr_mshVal>"
       << "</tr_maxSeedlingHeight>"
       << "</trees>"
       << "<allometry>"
       << "<tr_canopyHeight>"
       << "<tr_chVal species=\"Species_1\">39.48</tr_chVal>"
       << "<tr_chVal species=\"Species_2\">39.48</tr_chVal>"
       << "<tr_chVal species=\"Species_3\">39.48</tr_chVal>"
       << "</tr_canopyHeight>"
       << "<tr_stdAsympCrownRad>"
       << "<tr_sacrVal species=\"Species_1\">0.0549</tr_sacrVal>"
       << "<tr_sacrVal species=\"Species_2\">0.0549</tr_sacrVal>"
       << "<tr_sacrVal species=\"Species_3\">0.0549</tr_sacrVal>"
       << "</tr_stdAsympCrownRad>"
       << "<tr_stdCrownRadExp>"
       << "<tr_screVal species=\"Species_1\">1.0</tr_screVal>"
       << "<tr_screVal species=\"Species_2\">1.0</tr_screVal>"
       << "<tr_screVal species=\"Species_3\">1.0</tr_screVal>"
       << "</tr_stdCrownRadExp>"
       << "<tr_stdMaxCrownRad>"
       << "<tr_smcrVal species=\"Species_1\">10</tr_smcrVal>"
       << "<tr_smcrVal species=\"Species_2\">10</tr_smcrVal>"
       << "<tr_smcrVal species=\"Species_3\">10</tr_smcrVal>"
       << "</tr_stdMaxCrownRad>"
       << "<tr_conversionDiam10ToDBH>"
       << "<tr_cdtdVal species=\"Species_1\">0.8008</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_2\">0.8008</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_3\">0.8008</tr_cdtdVal>"
       << "</tr_conversionDiam10ToDBH>"
       << "<tr_interceptDiam10ToDBH>"
       << "<tr_idtdVal species=\"Species_1\">0</tr_idtdVal>"
       << "<tr_idtdVal species=\"Species_2\">0</tr_idtdVal>"
       << "<tr_idtdVal species=\"Species_3\">0</tr_idtdVal>"
       << "</tr_interceptDiam10ToDBH>"
       << "<tr_stdAsympCrownHt>"
       << "<tr_sachVal species=\"Species_1\">0.389</tr_sachVal>"
       << "<tr_sachVal species=\"Species_2\">0.389</tr_sachVal>"
       << "<tr_sachVal species=\"Species_3\">0.389</tr_sachVal>"
       << "</tr_stdAsympCrownHt>"
       << "<tr_stdCrownHtExp>"
       << "<tr_scheVal species=\"Species_1\">1.0</tr_scheVal>"
       << "<tr_scheVal species=\"Species_2\">1.0</tr_scheVal>"
       << "<tr_scheVal species=\"Species_3\">1.0</tr_scheVal>"
       << "</tr_stdCrownHtExp>"
       << "<tr_slopeOfHeight-Diam10>"
       << "<tr_sohdVal species=\"Species_1\">0.03418</tr_sohdVal>"
       << "<tr_sohdVal species=\"Species_2\">0.03418</tr_sohdVal>"
       << "<tr_sohdVal species=\"Species_3\">0.03418</tr_sohdVal>"
       << "</tr_slopeOfHeight-Diam10>"
       << "<tr_slopeOfAsymHeight>"
       << "<tr_soahVal species=\"Species_1\">0.0299</tr_soahVal>"
       << "<tr_soahVal species=\"Species_2\">0.0299</tr_soahVal>"
       << "<tr_soahVal species=\"Species_3\">0.0299</tr_soahVal>"
       << "</tr_slopeOfAsymHeight>"
       << "<tr_whatSeedlingHeightDiam>"
       << "<tr_wsehdVal species=\"Species_1\">0</tr_wsehdVal>"
       << "<tr_wsehdVal species=\"Species_2\">0</tr_wsehdVal>"
       << "<tr_wsehdVal species=\"Species_3\">0</tr_wsehdVal>"
       << "</tr_whatSeedlingHeightDiam>"
       << "<tr_whatSaplingHeightDiam>"
       << "<tr_wsahdVal species=\"Species_1\">0</tr_wsahdVal>"
       << "<tr_wsahdVal species=\"Species_2\">0</tr_wsahdVal>"
       << "<tr_wsahdVal species=\"Species_3\">0</tr_wsahdVal>"
       << "</tr_whatSaplingHeightDiam>"
       << "<tr_whatAdultHeightDiam>"
       << "<tr_wahdVal species=\"Species_1\">0</tr_wahdVal>"
       << "<tr_wahdVal species=\"Species_2\">0</tr_wahdVal>"
       << "<tr_wahdVal species=\"Species_3\">0</tr_wahdVal>"
       << "</tr_whatAdultHeightDiam>"
       << "<tr_whatAdultCrownRadDiam>"
       << "<tr_wacrdVal species=\"Species_1\">0</tr_wacrdVal>"
       << "<tr_wacrdVal species=\"Species_2\">0</tr_wacrdVal>"
       << "<tr_wacrdVal species=\"Species_3\">0</tr_wacrdVal>"
       << "</tr_whatAdultCrownRadDiam>"
       << "<tr_whatAdultCrownHeightHeight>"
       << "<tr_wachhVal species=\"Species_1\">0</tr_wachhVal>"
       << "<tr_wachhVal species=\"Species_2\">0</tr_wachhVal>"
       << "<tr_wachhVal species=\"Species_3\">0</tr_wachhVal>"
       << "</tr_whatAdultCrownHeightHeight>"
       << "<tr_whatSaplingCrownRadDiam>"
       << "<tr_wscrdVal species=\"Species_1\">0</tr_wscrdVal>"
       << "<tr_wscrdVal species=\"Species_2\">0</tr_wscrdVal>"
       << "<tr_wscrdVal species=\"Species_3\">0</tr_wscrdVal>"
       << "</tr_whatSaplingCrownRadDiam>"
       << "<tr_whatSaplingCrownHeightHeight>"
       << "<tr_wschhVal species=\"Species_1\">0</tr_wschhVal>"
       << "<tr_wschhVal species=\"Species_2\">0</tr_wschhVal>"
       << "<tr_wschhVal species=\"Species_3\">0</tr_wschhVal>"
       << "</tr_whatSaplingCrownHeightHeight>"
       << "</allometry>"
       << "<grid gridName=\"Substrate\">"
       << "<ma_floatCodes>"
       << "<ma_floatCode label=\"scarsoil\">0</ma_floatCode>"
       << "<ma_floatCode label=\"ffmoss\">1</ma_floatCode>"
       << "<ma_floatCode label=\"tipup\">2</ma_floatCode>"
       << "<ma_floatCode label=\"freshlog\">3</ma_floatCode>"
       << "<ma_floatCode label=\"declog\">4</ma_floatCode>"
       << "<ma_floatCode label=\"fflitter\">5</ma_floatCode>"
       << "</ma_floatCodes>"
       << "<ma_lengthXCells>45</ma_lengthXCells>"
       << "<ma_lengthYCells>45</ma_lengthYCells>"
       << "</grid>"
       << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>StochasticMortality</behaviorName>"
       << "<version>1.0</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_1\" type=\"Snag\"/>"
       << "<applyTo species=\"Species_2\" type=\"Snag\"/>"
       << "<applyTo species=\"Species_3\" type=\"Snag\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>Substrate</behaviorName>"
       << "<version>2.1</version>"
       << "<listPosition>2</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_1\" type=\"Snag\"/>"
       << "<applyTo species=\"Species_2\" type=\"Snag\"/>"
       << "<applyTo species=\"Species_3\" type=\"Snag\"/>"
       << "</behavior>"
       //Let the dead remover get rid of the trees we kill
       << "<behavior>"
       << "<behaviorName>RemoveDead</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>3</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\" />"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_1\" type=\"Snag\"/>"
       << "<applyTo species=\"Species_2\" type=\"Snag\"/>"
       << "<applyTo species=\"Species_3\" type=\"Snag\"/>"
       << "</behavior>"
       << "</behaviorList>"
       << "<StochasticMortality1>"
       << "<mo_stochasticMortRate>"
       << "<mo_smrVal species=\"Species_1\">1.0</mo_smrVal>"
       << "<mo_smrVal species=\"Species_2\">1.0</mo_smrVal>"
       << "<mo_smrVal species=\"Species_3\">1.0</mo_smrVal>"
       << "</mo_stochasticMortRate>"
       << "</StochasticMortality1>"
       << "<Substrate2>"
       << "<su_scarSoilDecayAlpha>-5.1E-4</su_scarSoilDecayAlpha>"
       << "<su_scarSoilDecayBeta>4.4</su_scarSoilDecayBeta>"
       << "<su_tipupDecayAlpha>-7.0E-4</su_tipupDecayAlpha>"
       << "<su_tipupDecayBeta>4.3</su_tipupDecayBeta>"
       << "<su_freshLogDecayAlpha>-0.05</su_freshLogDecayAlpha>"
       << "<su_freshLogDecayBeta>4.4</su_freshLogDecayBeta>"
       << "<su_decayedLogDecayAlpha>-0.7985</su_decayedLogDecayAlpha>"
       << "<su_decayedLogDecayBeta>1</su_decayedLogDecayBeta>"
       << "<su_maxNumberDecayYears>50</su_maxNumberDecayYears>"
       << "<su_initialScarSoil>0.0</su_initialScarSoil>"
       << "<su_initialTipup>0.2</su_initialTipup>"
       << "<su_initialFreshLog>0.01</su_initialFreshLog>"
       << "<su_initialDecayedLog>0.01</su_initialDecayedLog>"
       << "<su_partialCutScarSoil>0.17</su_partialCutScarSoil>"
       << "<su_partialCutTipup>0.15</su_partialCutTipup>"
       << "<su_partialCutFreshLog>0.06</su_partialCutFreshLog>"
       << "<su_partialCutDecayedLog>0.04</su_partialCutDecayedLog>"
       << "<su_gapCutScarSoil>0.45</su_gapCutScarSoil>"
       << "<su_gapCutTipup>0.34</su_gapCutTipup>"
       << "<su_gapCutFreshLog>0.09</su_gapCutFreshLog>"
       << "<su_gapCutDecayedLog>0.0</su_gapCutDecayedLog>"
       << "<su_clearCutScarSoil>0.36</su_clearCutScarSoil>"
       << "<su_clearCutTipup>0.34</su_clearCutTipup>"
       << "<su_clearCutFreshLog>0.17</su_clearCutFreshLog>"
       << "<su_clearCutDecayedLog>0.01</su_clearCutDecayedLog>"
       << "<su_propOfDeadFall>"
       << "<su_podfVal species=\"Species_1\">1</su_podfVal>"
       << "<su_podfVal species=\"Species_2\">1</su_podfVal>"
       << "<su_podfVal species=\"Species_3\">1</su_podfVal>"
       << "</su_propOfDeadFall>"
       << "<su_propOfFallUproot>"
       << "<su_pofuVal species=\"Species_1\">1</su_pofuVal>"
       << "<su_pofuVal species=\"Species_2\">0.5</su_pofuVal>"
       << "<su_pofuVal species=\"Species_3\">0.2</su_pofuVal>"
       << "</su_propOfFallUproot>"
       << "<su_propOfSnagsUproot>"
       << "<su_posuVal species=\"Species_1\">0.8</su_posuVal>"
       << "<su_posuVal species=\"Species_2\">0</su_posuVal>"
       << "<su_posuVal species=\"Species_3\">0.6</su_posuVal>"
       << "</su_propOfSnagsUproot>"
       << "<su_rootTipupFactor>3.1</su_rootTipupFactor>"
       << "<su_mossProportion>0</su_mossProportion>"
       << "<su_directionalTreeFall>0</su_directionalTreeFall>"
       << "</Substrate2>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteSubstrateXMLFile5()
/////////////////////////////////////////////////////////////////////////////
const char* WriteSubstrateXMLFile5()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06010101\">"
       << "<plot>"
       << "<timesteps>10</timesteps>"
       << "<yearsPerTimestep>1</yearsPerTimestep>"
       << "<randomSeed>1</randomSeed>"
       << "<plot_lenX>200.0</plot_lenX>"
       << "<plot_lenY>200.0</plot_lenY>"
       << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
       << "<plot_temp_C>12.88171785</plot_temp_C>"
       << "<plot_latitude>55.37</plot_latitude>"
       << "</plot>"
       << "<trees>"
       << "<tr_speciesList>"
       << "<tr_species speciesName=\"Species_1\"/>"
       << "<tr_species speciesName=\"Species_2\"/>"
       << "<tr_species speciesName=\"Species_3\"/>"
       << "</tr_speciesList>"
       << "<tr_seedDiam10Cm>0.1</tr_seedDiam10Cm>"
       << "<tr_minAdultDBH>"
       << "<tr_madVal species=\"Species_1\">10.0</tr_madVal>"
       << "<tr_madVal species=\"Species_2\">10.0</tr_madVal>"
       << "<tr_madVal species=\"Species_3\">10.0</tr_madVal>"
       << "</tr_minAdultDBH>"
       << "<tr_maxSeedlingHeight>"
       << "<tr_mshVal species=\"Species_1\">1.35</tr_mshVal>"
       << "<tr_mshVal species=\"Species_2\">1.35</tr_mshVal>"
       << "<tr_mshVal species=\"Species_3\">1.35</tr_mshVal>"
       << "</tr_maxSeedlingHeight>"
       << "</trees>"
       << "<allometry>"
       << "<tr_canopyHeight>"
       << "<tr_chVal species=\"Species_1\">39.48</tr_chVal>"
       << "<tr_chVal species=\"Species_2\">39.48</tr_chVal>"
       << "<tr_chVal species=\"Species_3\">39.48</tr_chVal>"
       << "</tr_canopyHeight>"
       << "<tr_stdAsympCrownRad>"
       << "<tr_sacrVal species=\"Species_1\">0.0549</tr_sacrVal>"
       << "<tr_sacrVal species=\"Species_2\">0.0549</tr_sacrVal>"
       << "<tr_sacrVal species=\"Species_3\">0.0549</tr_sacrVal>"
       << "</tr_stdAsympCrownRad>"
       << "<tr_stdCrownRadExp>"
       << "<tr_screVal species=\"Species_1\">1.0</tr_screVal>"
       << "<tr_screVal species=\"Species_2\">1.0</tr_screVal>"
       << "<tr_screVal species=\"Species_3\">1.0</tr_screVal>"
       << "</tr_stdCrownRadExp>"
       << "<tr_stdMaxCrownRad>"
       << "<tr_smcrVal species=\"Species_1\">10</tr_smcrVal>"
       << "<tr_smcrVal species=\"Species_2\">10</tr_smcrVal>"
       << "<tr_smcrVal species=\"Species_3\">10</tr_smcrVal>"
       << "</tr_stdMaxCrownRad>"
       << "<tr_conversionDiam10ToDBH>"
       << "<tr_cdtdVal species=\"Species_1\">0.8008</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_2\">0.8008</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_3\">0.8008</tr_cdtdVal>"
       << "</tr_conversionDiam10ToDBH>"
       << "<tr_interceptDiam10ToDBH>"
       << "<tr_idtdVal species=\"Species_1\">0</tr_idtdVal>"
       << "<tr_idtdVal species=\"Species_2\">0</tr_idtdVal>"
       << "<tr_idtdVal species=\"Species_3\">0</tr_idtdVal>"
       << "</tr_interceptDiam10ToDBH>"
       << "<tr_stdAsympCrownHt>"
       << "<tr_sachVal species=\"Species_1\">0.389</tr_sachVal>"
       << "<tr_sachVal species=\"Species_2\">0.389</tr_sachVal>"
       << "<tr_sachVal species=\"Species_3\">0.389</tr_sachVal>"
       << "</tr_stdAsympCrownHt>"
       << "<tr_stdCrownHtExp>"
       << "<tr_scheVal species=\"Species_1\">1.0</tr_scheVal>"
       << "<tr_scheVal species=\"Species_2\">1.0</tr_scheVal>"
       << "<tr_scheVal species=\"Species_3\">1.0</tr_scheVal>"
       << "</tr_stdCrownHtExp>"
       << "<tr_slopeOfHeight-Diam10>"
       << "<tr_sohdVal species=\"Species_1\">0.03418</tr_sohdVal>"
       << "<tr_sohdVal species=\"Species_2\">0.03418</tr_sohdVal>"
       << "<tr_sohdVal species=\"Species_3\">0.03418</tr_sohdVal>"
       << "</tr_slopeOfHeight-Diam10>"
       << "<tr_slopeOfAsymHeight>"
       << "<tr_soahVal species=\"Species_1\">0.0299</tr_soahVal>"
       << "<tr_soahVal species=\"Species_2\">0.0299</tr_soahVal>"
       << "<tr_soahVal species=\"Species_3\">0.0299</tr_soahVal>"
       << "</tr_slopeOfAsymHeight>"
       << "<tr_whatSeedlingHeightDiam>"
       << "<tr_wsehdVal species=\"Species_1\">0</tr_wsehdVal>"
       << "<tr_wsehdVal species=\"Species_2\">0</tr_wsehdVal>"
       << "<tr_wsehdVal species=\"Species_3\">0</tr_wsehdVal>"
       << "</tr_whatSeedlingHeightDiam>"
       << "<tr_whatSaplingHeightDiam>"
       << "<tr_wsahdVal species=\"Species_1\">0</tr_wsahdVal>"
       << "<tr_wsahdVal species=\"Species_2\">0</tr_wsahdVal>"
       << "<tr_wsahdVal species=\"Species_3\">0</tr_wsahdVal>"
       << "</tr_whatSaplingHeightDiam>"
       << "<tr_whatAdultHeightDiam>"
       << "<tr_wahdVal species=\"Species_1\">0</tr_wahdVal>"
       << "<tr_wahdVal species=\"Species_2\">0</tr_wahdVal>"
       << "<tr_wahdVal species=\"Species_3\">0</tr_wahdVal>"
       << "</tr_whatAdultHeightDiam>"
       << "<tr_whatAdultCrownRadDiam>"
       << "<tr_wacrdVal species=\"Species_1\">0</tr_wacrdVal>"
       << "<tr_wacrdVal species=\"Species_2\">0</tr_wacrdVal>"
       << "<tr_wacrdVal species=\"Species_3\">0</tr_wacrdVal>"
       << "</tr_whatAdultCrownRadDiam>"
       << "<tr_whatAdultCrownHeightHeight>"
       << "<tr_wachhVal species=\"Species_1\">0</tr_wachhVal>"
       << "<tr_wachhVal species=\"Species_2\">0</tr_wachhVal>"
       << "<tr_wachhVal species=\"Species_3\">0</tr_wachhVal>"
       << "</tr_whatAdultCrownHeightHeight>"
       << "<tr_whatSaplingCrownRadDiam>"
       << "<tr_wscrdVal species=\"Species_1\">0</tr_wscrdVal>"
       << "<tr_wscrdVal species=\"Species_2\">0</tr_wscrdVal>"
       << "<tr_wscrdVal species=\"Species_3\">0</tr_wscrdVal>"
       << "</tr_whatSaplingCrownRadDiam>"
       << "<tr_whatSaplingCrownHeightHeight>"
       << "<tr_wschhVal species=\"Species_1\">0</tr_wschhVal>"
       << "<tr_wschhVal species=\"Species_2\">0</tr_wschhVal>"
       << "<tr_wschhVal species=\"Species_3\">0</tr_wschhVal>"
       << "</tr_whatSaplingCrownHeightHeight>"
       << "</allometry>"
       << "<grid gridName=\"Substrate\">"
       << "<ma_floatCodes>"
       << "<ma_floatCode label=\"scarsoil\">0</ma_floatCode>"
       << "<ma_floatCode label=\"ffmoss\">1</ma_floatCode>"
       << "<ma_floatCode label=\"tipup\">2</ma_floatCode>"
       << "<ma_floatCode label=\"freshlog\">3</ma_floatCode>"
       << "<ma_floatCode label=\"declog\">4</ma_floatCode>"
       << "<ma_floatCode label=\"fflitter\">5</ma_floatCode>"
       << "</ma_floatCodes>"
       << "<ma_lengthXCells>3</ma_lengthXCells>"
       << "<ma_lengthYCells>2</ma_lengthYCells>"
       << "<ma_v y=\"0\" x=\"0\">"
       << "<fl c=\"0\">0</fl>"
       << "<fl c=\"1\">0</fl>"
       << "<fl c=\"2\">0</fl>"
       << "<fl c=\"3\">0.00289823</fl>"
       << "<fl c=\"4\">0</fl>"
       << "<fl c=\"5\">0.997102</fl>"
       << "</ma_v>"
       << "</grid>"
       << "<grid gridName=\"substratecalcs\">"
       << "<ma_floatCodes>"
       << "<ma_floatCode label=\"newtipup\">0</ma_floatCode>"
       << "<ma_floatCode label=\"freshlog_0\">1</ma_floatCode>"
       << "<ma_floatCode label=\"freshlog_1\">2</ma_floatCode>"
       << "<ma_floatCode label=\"freshlog_2\">3</ma_floatCode>"
       << "<ma_floatCode label=\"freshlog_3\">4</ma_floatCode>"
       << "<ma_floatCode label=\"freshlog_4\">5</ma_floatCode>"
       << "<ma_floatCode label=\"freshlog_5\">6</ma_floatCode>"
       << "<ma_floatCode label=\"freshlog_6\">7</ma_floatCode>"
       << "<ma_floatCode label=\"freshlog_7\">8</ma_floatCode>"
       << "<ma_floatCode label=\"freshlog_8\">9</ma_floatCode>"
       << "<ma_floatCode label=\"freshlog_9\">10</ma_floatCode>"
       << "<ma_floatCode label=\"declog_0\">11</ma_floatCode>"
       << "<ma_floatCode label=\"declog_1\">12</ma_floatCode>"
       << "<ma_floatCode label=\"declog_2\">13</ma_floatCode>"
       << "<ma_floatCode label=\"declog_3\">14</ma_floatCode>"
       << "<ma_floatCode label=\"declog_4\">15</ma_floatCode>"
       << "<ma_floatCode label=\"declog_5\">16</ma_floatCode>"
       << "<ma_floatCode label=\"declog_6\">17</ma_floatCode>"
       << "<ma_floatCode label=\"declog_7\">18</ma_floatCode>"
       << "<ma_floatCode label=\"declog_8\">19</ma_floatCode>"
       << "<ma_floatCode label=\"declog_9\">20</ma_floatCode>"
       << "</ma_floatCodes>"
       << "<ma_lengthXCells>3</ma_lengthXCells>"
       << "<ma_lengthYCells>2</ma_lengthYCells>"
       << "<ma_v x=\"0\" y=\"0\">"
       << "<fl c=\"0\">0.1</fl>"
       << "<fl c=\"1\">0.01</fl>"
       << "<fl c=\"2\">0.02</fl>"
       << "<fl c=\"3\">0.03</fl>"
       << "<fl c=\"4\">0.04</fl>"
       << "<fl c=\"5\">0.05</fl>"
       << "<fl c=\"6\">0.06</fl>"
       << "<fl c=\"7\">0.07</fl>"
       << "<fl c=\"8\">0.08</fl>"
       << "<fl c=\"9\">0.09</fl>"
       << "<fl c=\"10\">0.11</fl>"
       << "<fl c=\"11\">0.11</fl>"
       << "<fl c=\"12\">0.12</fl>"
       << "<fl c=\"13\">0.13</fl>"
       << "<fl c=\"14\">0.14</fl>"
       << "<fl c=\"15\">0.15</fl>"
       << "<fl c=\"16\">0.16</fl>"
       << "<fl c=\"17\">0.17</fl>"
       << "<fl c=\"18\">0.18</fl>"
       << "<fl c=\"19\">0.19</fl>"
       << "<fl c=\"20\">0.20</fl>"
       << "</ma_v>"
       << "</grid>"
       << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>StochasticMortality</behaviorName>"
       << "<version>1.0</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>StochasticMortality</behaviorName>"
       << "<version>1.0</version>"
       << "<listPosition>2</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Snag\"/>"
       << "<applyTo species=\"Species_2\" type=\"Snag\"/>"
       << "<applyTo species=\"Species_3\" type=\"Snag\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>Substrate</behaviorName>"
       << "<version>2.1</version>"
       << "<listPosition>3</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_1\" type=\"Snag\"/>"
       << "<applyTo species=\"Species_2\" type=\"Snag\"/>"
       << "<applyTo species=\"Species_3\" type=\"Snag\"/>"
       << "</behavior>"
       //Let the dead remover get rid of the trees we kill
       << "<behavior>"
       << "<behaviorName>RemoveDead</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>4</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\" />"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_1\" type=\"Snag\"/>"
       << "<applyTo species=\"Species_2\" type=\"Snag\"/>"
       << "<applyTo species=\"Species_3\" type=\"Snag\"/>"
       << "</behavior>"
       << "</behaviorList>"
       << "<StochasticMortality1>"
       << "<mo_stochasticMortRate>"
       << "<mo_smrVal species=\"Species_1\">1.0</mo_smrVal>"
       << "<mo_smrVal species=\"Species_2\">1.0</mo_smrVal>"
       << "<mo_smrVal species=\"Species_3\">1.0</mo_smrVal>"
       << "</mo_stochasticMortRate>"
       << "</StochasticMortality1>"
       << "<StochasticMortality2>"
       << "<mo_stochasticMortRate>"
       << "<mo_smrVal species=\"Species_1\">0.0</mo_smrVal>"
       << "<mo_smrVal species=\"Species_2\">0.0</mo_smrVal>"
       << "<mo_smrVal species=\"Species_3\">0.0</mo_smrVal>"
       << "</mo_stochasticMortRate>"
       << "</StochasticMortality2>"
       << "<Substrate3>"
       << "<su_scarSoilDecayAlpha>-5.1E-4</su_scarSoilDecayAlpha>"
       << "<su_scarSoilDecayBeta>4.4</su_scarSoilDecayBeta>"
       << "<su_tipupDecayAlpha>-7.0E-4</su_tipupDecayAlpha>"
       << "<su_tipupDecayBeta>4.3</su_tipupDecayBeta>"
       << "<su_freshLogDecayAlpha>-0.05</su_freshLogDecayAlpha>"
       << "<su_freshLogDecayBeta>4.4</su_freshLogDecayBeta>"
       << "<su_decayedLogDecayAlpha>-0.7985</su_decayedLogDecayAlpha>"
       << "<su_decayedLogDecayBeta>1.1</su_decayedLogDecayBeta>"
       << "<su_maxNumberDecayYears>10</su_maxNumberDecayYears>"
       << "<su_initialScarSoil>0.0</su_initialScarSoil>"
       << "<su_initialTipup>0.2</su_initialTipup>"
       << "<su_initialFreshLog>0.01</su_initialFreshLog>"
       << "<su_initialDecayedLog>0.01</su_initialDecayedLog>"
       << "<su_partialCutScarSoil>0.17</su_partialCutScarSoil>"
       << "<su_partialCutTipup>0.15</su_partialCutTipup>"
       << "<su_partialCutFreshLog>0.06</su_partialCutFreshLog>"
       << "<su_partialCutDecayedLog>0.04</su_partialCutDecayedLog>"
       << "<su_gapCutScarSoil>0.45</su_gapCutScarSoil>"
       << "<su_gapCutTipup>0.34</su_gapCutTipup>"
       << "<su_gapCutFreshLog>0.09</su_gapCutFreshLog>"
       << "<su_gapCutDecayedLog>0.0</su_gapCutDecayedLog>"
       << "<su_clearCutScarSoil>0.36</su_clearCutScarSoil>"
       << "<su_clearCutTipup>0.34</su_clearCutTipup>"
       << "<su_clearCutFreshLog>0.17</su_clearCutFreshLog>"
       << "<su_clearCutDecayedLog>0.01</su_clearCutDecayedLog>"
       << "<su_propOfDeadFall>"
       << "<su_podfVal species=\"Species_1\">0.2</su_podfVal>"
       << "<su_podfVal species=\"Species_2\">0.5</su_podfVal>"
       << "<su_podfVal species=\"Species_3\">0.0</su_podfVal>"
       << "</su_propOfDeadFall>"
       << "<su_propOfFallUproot>"
       //<< "<su_pofuVal species=\"Species_1\">1</su_pofuVal>"
       //<< "<su_pofuVal species=\"Species_2\">1</su_pofuVal>"
       //<< "<su_pofuVal species=\"Species_3\">1</su_pofuVal>"
       << "<su_pofuVal species=\"Species_1\">1</su_pofuVal>"
       << "<su_pofuVal species=\"Species_2\">1</su_pofuVal>"
       << "<su_pofuVal species=\"Species_3\">1</su_pofuVal>"
       << "</su_propOfFallUproot>"
       << "<su_propOfSnagsUproot>"
       << "<su_posuVal species=\"Species_1\">1</su_posuVal>"
       << "<su_posuVal species=\"Species_2\">0.7</su_posuVal>"
       << "<su_posuVal species=\"Species_3\">0.15</su_posuVal>"
       << "</su_propOfSnagsUproot>"
       << "<su_rootTipupFactor>3.1</su_rootTipupFactor>"
       << "<su_mossProportion>0</su_mossProportion>"
       << "<su_directionalTreeFall>0</su_directionalTreeFall>"
       << "</Substrate3>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteSubstrateXMLFile6()
/////////////////////////////////////////////////////////////////////////////
const char* WriteSubstrateXMLFile6()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06010101\">"
       << "<plot>"
       << "<timesteps>5</timesteps>"
       << "<yearsPerTimestep>3</yearsPerTimestep>"
       << "<randomSeed>1</randomSeed>"
       << "<plot_lenX>200.0</plot_lenX>"
       << "<plot_lenY>200.0</plot_lenY>"
       << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
       << "<plot_temp_C>12.88171785</plot_temp_C>"
       << "<plot_latitude>55.37</plot_latitude>"
       << "</plot>";

  WriteSubstrateCommonTreeStuff(oOut);

  oOut << "<behaviorList>"
       //Have to have a StochasticMortality behavior so dead is registered
       << "<behavior>"
       << "<behaviorName>StochasticMortality</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>Substrate</behaviorName>"
       << "<version>2.1</version>"
       << "<listPosition>2</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "</behavior>"
       << "</behaviorList>"
       << "<StochasticMortality1>"
       << "<mo_stochasticMortRate>"
       << "<mo_smrVal species=\"Species_1\">0.0</mo_smrVal>"
       << "</mo_stochasticMortRate>"
       << "</StochasticMortality1>"
       << "<Substrate2>"
       << "<su_scarSoilDecayAlpha>-5.1E-4</su_scarSoilDecayAlpha>"
       << "<su_scarSoilDecayBeta>4.1</su_scarSoilDecayBeta>"
       << "<su_tipupDecayAlpha>-7.0E-4</su_tipupDecayAlpha>"
       << "<su_tipupDecayBeta>1.3</su_tipupDecayBeta>"
       << "<su_freshLogDecayAlpha>-0.05</su_freshLogDecayAlpha>"
       << "<su_freshLogDecayBeta>3.5</su_freshLogDecayBeta>"
       << "<su_decayedLogDecayAlpha>-0.7985</su_decayedLogDecayAlpha>"
       << "<su_decayedLogDecayBeta>1</su_decayedLogDecayBeta>"
       << "<su_maxNumberDecayYears>9</su_maxNumberDecayYears>"
       << "<su_initialScarSoil>0.0</su_initialScarSoil>"
       << "<su_initialTipup>0.2</su_initialTipup>"
       << "<su_initialFreshLog>0.01</su_initialFreshLog>"
       << "<su_initialDecayedLog>0.11</su_initialDecayedLog>"
       << "<su_propOfDeadFall>"
       << "<su_podfVal species=\"Species_1\">1</su_podfVal>"
       << "</su_propOfDeadFall>"
       << "<su_propOfFallUproot>"
       << "<su_pofuVal species=\"Species_1\">1</su_pofuVal>"
       << "</su_propOfFallUproot>"
       << "<su_propOfSnagsUproot>"
       << "<su_posuVal species=\"Species_1\">1</su_posuVal>"
       << "</su_propOfSnagsUproot>"
       << "<su_mossProportion>0.35</su_mossProportion>"
       << "<su_directionalTreeFall>0</su_directionalTreeFall>"
       << "<su_rootTipupFactor>3.1</su_rootTipupFactor>"
       << "</Substrate2>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteSubstrateCommonTreeStuff()
/////////////////////////////////////////////////////////////////////////////
void WriteSubstrateCommonTreeStuff( std::fstream &oOut ) {
  using namespace std;
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
       << "<tr_stdMaxCrownRad>"
       << "<tr_smcrVal species=\"Species_1\">10</tr_smcrVal>"
       << "</tr_stdMaxCrownRad>"
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
}
