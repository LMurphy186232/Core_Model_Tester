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
// TestSubstrateRun2()
// Substrate normal processing, run 2. This run has harvest and has non-
// directional tree fall. This tests that new fresh log area and new
// tip-up area are added correctly when trees die, that cohorts are managed
// correctly, and that the final substrate numbers are calculated correctly.
// WriteSubstrateXMLFile1() is used to set up with tip-up probabilities of 1. This
// also has harvests occuring in three grid cells so harvest cohorts can be
// tested. This executes the timesteps and provides mortality (killing known
// trees at certain times), and then verifies grid values.
/////////////////////////////////////////////////////////////////////////////
TEST(Substrate, TestSubstrateRun2) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    clGrid * p_oSubstrateGrid, *p_oCalcsGrid;
    clPopulationBase *p_oTemp;
    clTreePopulation *p_oPop;
    clTree *p_oTree;
    int i, iDead = natural;

    //Create and feed in the file
    p_oSimManager->ReadFile(WriteSubstrateXMLFile1());
    //Grab our pointers
    p_oTemp = p_oSimManager->GetPopulationObject("treepopulation");
    p_oPop = (clTreePopulation*) p_oTemp;
    p_oSubstrateGrid = p_oSimManager->GetGridObject("Substrate");
    p_oCalcsGrid = p_oSimManager->GetGridObject("substratecalcs");

    //Create our trees for harvesting
    p_oTree = p_oPop->CreateTree(1, 1, 0, clTreePopulation::adult, 20);
    p_oTree = p_oPop->CreateTree(1, 9, 0, clTreePopulation::adult, 20);
    p_oTree = p_oPop->CreateTree(1, 17, 0, clTreePopulation::adult, 20);

    //********************************
    //Timestep 1:  Just run.
    //********************************
    p_oSimManager->RunSim(1);

    //Verify the freshlogs and declogs arrays
    VerifySubstrateRun2TS1SubstrateArrays(p_oCalcsGrid);

    //Verify the new tipups
    VerifySubstrateRun2TS1Tipup(p_oCalcsGrid);

    //Verify the cohorts
    VerifySubstrateRun2TS1Cohorts(p_oSubstrateGrid);

    //Verify the substrate proportions
    VerifySubstrateRun2TS1Proportions(p_oSubstrateGrid);

    //********************************
    //Timestep 2:
    //********************************

    //Set the timestep to 2
    p_oSimManager->SetCurrentTimestep(2);

    //Run the harvest behavior
    p_oSimManager->GetBehaviorObject(0)->Action();

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


    //Now run the substrate behavior and the tree killer
    for (i = 2; i < p_oSimManager->GetNumberOfBehaviors(); i++) {
      p_oSimManager->GetBehaviorObject(i)->Action();
    }
    //Now timestep cleanup
    for (i = 0; i < p_oSimManager->GetNumberOfBehaviors(); i++) {
      p_oSimManager->GetBehaviorObject(i)->TimestepCleanup();
    }

    //Verify the freshlogs and declogs arrays
    VerifySubstrateRun2TS2SubstrateArrays(p_oCalcsGrid);

    //Verify the new tipups
    VerifySubstrateRun2TS2Tipup(p_oCalcsGrid);

    //Verify the cohorts
    VerifySubstrateRun2TS2Cohorts(p_oSubstrateGrid);

    //Verify the substrate proportions
    VerifySubstrateRun2TS2Proportions(p_oSubstrateGrid);

    //********************************
    //Timestep 3:
    //********************************
    //We have to fake this timestep.  The light behavior will interfere with our
    //ability to kill trees, so we have to skip it.  Set the timestep to 3
    p_oSimManager->SetCurrentTimestep(3);

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
    p_oSimManager->GetBehaviorObject(0)->Action();
    for (i = 2; i < p_oSimManager->GetNumberOfBehaviors(); i++) {
      p_oSimManager->GetBehaviorObject(i)->Action();
    }
    //Now timestep cleanup
    for (i = 0; i < p_oSimManager->GetNumberOfBehaviors(); i++) {
      p_oSimManager->GetBehaviorObject(i)->TimestepCleanup();
    }

    //Verify the freshlogs and declogs arrays
    VerifySubstrateRun2TS3SubstrateArrays(p_oCalcsGrid);

    //Verify the new tipups
    VerifySubstrateRun2TS3Tipup(p_oCalcsGrid);

    //Verify the cohorts
    VerifySubstrateRun2TS3Cohorts(p_oSubstrateGrid);

    //Verify the substrate proportions
    VerifySubstrateRun2TS3Proportions(p_oSubstrateGrid);

    //********************************
    //Timestep 4:  Just run.
    //********************************
    p_oSimManager->RunSim(1);

    //Verify the freshlogs and declogs arrays
    VerifySubstrateRun2TS4SubstrateArrays(p_oCalcsGrid);

    //Verify the new tipups
    VerifySubstrateRun2TS4Tipup(p_oCalcsGrid);

    //Verify the cohorts
    VerifySubstrateRun2TS4Cohorts(p_oSubstrateGrid);

    //Verify the substrate proportions
    VerifySubstrateRun2TS4Proportions(p_oSubstrateGrid);
    delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

/////////////////////////////////////////////////////////////////////////////
// TestSubstrateRun3()
// Substrate normal processing run 3. Verifies substrate calculations. This
// run has no harvest and directional tree fall. This function tests that
// new fresh log area and new tip-up area are added correctly when trees die,
// that cohorts are managed correctly, and that the final substrate numbers
// are calculated correctly. WriteSubstrateXMLFile3() is used to set up with tip-up
// probabilities of 1. This executes the timesteps and provides mortality
// (killing known trees at certain times), and then verifies grid values.
/////////////////////////////////////////////////////////////////////////////
TEST(Substrate, TestSubstrateRun3) {

  clGrid * p_oSubstrateGrid, *p_oCalcsGrid;
  clTreePopulation *p_oPop;
  std::stringstream sLabel;
  int *p_iFreshLogCodes = new int[3];
  float fExpectedScarSoil = 0, fExpectedFFMoss, fExpectedFFLitter, fExpectedTipup,
  fExpectedDecLog, fExpectedFreshLog, fActual;
  int iX, iY, i, j, iCode;

  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    //Create and feed in the file
    p_oSimManager->ReadFile(WriteSubstrateXMLFile3());
    //Grab our pointers
    p_oPop = (clTreePopulation*) p_oSimManager->GetPopulationObject("treepopulation");
    p_oSubstrateGrid = p_oSimManager->GetGridObject("Substrate");
    p_oCalcsGrid = p_oSimManager->GetGridObject("substratecalcs");

    //********************************
    //Timestep 1:  Run.
    //********************************
    p_oSimManager->RunSim(1);

    //Verify the freshlogs and declogs arrays
    fExpectedFreshLog = 0.01; //all values are the same
    for ( i = 0; i < 3; i++ )
    {
      sLabel << "freshlog_" << i;
      p_iFreshLogCodes[i] = p_oCalcsGrid->GetFloatDataCode(sLabel.str());
      EXPECT_LT(-1, p_iFreshLogCodes[i]);
      sLabel.str("");
    }

    //Current timestep addition
    //Cell 1
    iX = 5; iY = 5;
    p_oCalcsGrid->GetValueOfCell(iX, iY, p_iFreshLogCodes[0], & fActual);
    EXPECT_LT(fabs(fActual - fExpectedFreshLog), 0.001);
    //Cell 2
    iX = 5; iY = 15;
    p_oCalcsGrid->GetValueOfCell(iX, iY, p_iFreshLogCodes[0], & fActual);
    EXPECT_LT(fabs(fActual - fExpectedFreshLog), 0.001);
    //Cell 3
    iX = 15; iY = 5;
    p_oCalcsGrid->GetValueOfCell(iX, iY, p_iFreshLogCodes[0], & fActual);
    EXPECT_LT(fabs(fActual - fExpectedFreshLog), 0.001);
    //Cell 4
    iX = 15; iY = 15;
    p_oCalcsGrid->GetValueOfCell(iX, iY, p_iFreshLogCodes[0], & fActual);
    EXPECT_LT(fabs(fActual - fExpectedFreshLog), 0.001);

    //Last timestep
    fExpectedFreshLog = 0.0;
    //Cell 1
    iX = 5; iY = 5;
    p_oCalcsGrid->GetValueOfCell(iX, iY, p_iFreshLogCodes[1], & fActual);
    EXPECT_LT(fabs(fActual - fExpectedFreshLog), 0.001);
    //Cell 2
    iX = 5; iY = 15;
    p_oCalcsGrid->GetValueOfCell(iX, iY, p_iFreshLogCodes[1], & fActual);
    EXPECT_LT(fabs(fActual - fExpectedFreshLog), 0.001);
    //Cell 3
    iX = 15; iY = 5;
    p_oCalcsGrid->GetValueOfCell(iX, iY, p_iFreshLogCodes[1], & fActual);
    EXPECT_LT(fabs(fActual - fExpectedFreshLog), 0.001);
    //Cell 4
    iX = 15; iY = 15;
    p_oCalcsGrid->GetValueOfCell(iX, iY, p_iFreshLogCodes[1], & fActual);
    EXPECT_LT(fabs(fActual - fExpectedFreshLog), 0.001);

    //Timestep - 2
    //Cell 1
    iX = 5; iY = 5;
    p_oCalcsGrid->GetValueOfCell(iX, iY, p_iFreshLogCodes[2], & fActual);
    EXPECT_LT(fabs(fActual - fExpectedFreshLog), 0.001);
    //Cell 2
    iX = 5; iY = 15;
    p_oCalcsGrid->GetValueOfCell(iX, iY, p_iFreshLogCodes[2], & fActual);
    EXPECT_LT(fabs(fActual - fExpectedFreshLog), 0.001);
    //Cell 3
    iX = 15; iY = 5;
    p_oCalcsGrid->GetValueOfCell(iX, iY, p_iFreshLogCodes[2], & fActual);
    EXPECT_LT(fabs(fActual - fExpectedFreshLog), 0.001);
    //Cell 4
    iX = 15; iY = 15;
    p_oCalcsGrid->GetValueOfCell(iX, iY, p_iFreshLogCodes[2], & fActual);
    EXPECT_LT(fabs(fActual - fExpectedFreshLog), 0.001);

    //Verify the new tipups
    //Cell 1
    fExpectedTipup = 0.2;
    iCode = p_oCalcsGrid->GetFloatDataCode("newtipup");
    iX = 5; iY = 5;
    p_oCalcsGrid->GetValueOfCell(iX, iY, iCode, & fActual);
    EXPECT_LT(fabs(fActual - fExpectedTipup), 0.001);
    //Cell 2
    iX = 5; iY = 15;
    p_oCalcsGrid->GetValueOfCell(iX, iY, iCode, & fActual);
    EXPECT_LT(fabs(fActual - fExpectedTipup), 0.001);
    //Cell 3
    iX = 15; iY = 5;
    p_oCalcsGrid->GetValueOfCell(iX, iY, iCode, & fActual);
    EXPECT_LT(fabs(fActual - fExpectedTipup), 0.001);
    //Cell 4
    iX = 15; iY = 15;
    p_oCalcsGrid->GetValueOfCell(iX, iY, iCode, & fActual);
    EXPECT_LT(fabs(fActual - fExpectedTipup), 0.001);

    //Verify the substrate proportions
    fExpectedFreshLog = 0.01;
    fExpectedDecLog = 0.11;
    fExpectedTipup = 0.2;
    fExpectedFFMoss = 0.238;
    fExpectedFFLitter = 0.442;
    iX = 5; iY = 5;
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
    iX = 5; iY = 15;
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
    iX = 15; iY = 5;
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
    iX = 15; iY = 15;
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

    //********************************
    //Timestep 2:
    //********************************
    //Create certain trees within each test grid cell - these should all get killed
    p_oPop->CreateTree(44, 44, 0, clTreePopulation::adult, 20);
    p_oPop->CreateTree(44, 124, 0, clTreePopulation::adult, 30);
    p_oPop->CreateTree(124, 44, 0, clTreePopulation::adult, 35);
    p_oPop->CreateTree(124, 124, 0, clTreePopulation::adult, 40);

    p_oSimManager->RunSim(1);

    //Current timestep addition - make sure these do NOT equal
    //Cell 1
    iX = 5; iY = 5;
    fExpectedFreshLog = 0.028924872;
    p_oCalcsGrid->GetValueOfCell(iX, iY, p_iFreshLogCodes[0], & fActual);
    EXPECT_GT(fabs(fActual - fExpectedFreshLog)/fExpectedFreshLog, 0.1);
    //Cell 2
    iX = 5; iY = 15;
    fExpectedFreshLog = 0.056088097;
    p_oCalcsGrid->GetValueOfCell(iX, iY, p_iFreshLogCodes[0], & fActual);
    EXPECT_GT(fabs(fActual - fExpectedFreshLog)/fExpectedFreshLog, 0.1);
    //Cell 3
    iX = 15; iY = 5;
    fExpectedFreshLog = 0.071340092;
    p_oCalcsGrid->GetValueOfCell(iX, iY, p_iFreshLogCodes[0], & fActual);
    EXPECT_GT(fabs(fActual - fExpectedFreshLog)/fExpectedFreshLog, 0.1);
    //Cell 4
    iX = 15; iY = 15;
    fExpectedFreshLog = 0.087341983;
    p_oCalcsGrid->GetValueOfCell(iX, iY, p_iFreshLogCodes[0], & fActual);
    EXPECT_GT(fabs(fActual - fExpectedFreshLog)/fExpectedFreshLog, 0.1);

    //Now add up each target grid cell and all surrounding cells - they should
    //total the amount in each tree trunk
    //Cell 1
    fActual = 0;
    fExpectedFreshLog = 0.028924872;
    iX = 5; iY = 5;
    for (i = iX - 3; i <= iX + 3; i++) {
      for (j = iY - 3; j <= iY + 3; j++) {
        //Dangerously co-opt this variable
        p_oCalcsGrid->GetValueOfCell(i, j, p_iFreshLogCodes[0], & fExpectedTipup);
        fActual += fExpectedTipup;
      }
    }
    EXPECT_LT(fabs(fActual - fExpectedFreshLog), 0.001);

    //Cell 2
    fActual = 0;
    fExpectedFreshLog = 0.056088097;
    iX = 5; iY = 15;
    for (i = iX - 3; i <= iX + 3; i++) {
      for (j = iY - 3; j <= iY + 3; j++) {
        //Dangerously co-opt this variable
        p_oCalcsGrid->GetValueOfCell(i, j, p_iFreshLogCodes[0], & fExpectedTipup);
        fActual += fExpectedTipup;
      }
    }
    EXPECT_LT(fabs(fActual - fExpectedFreshLog), 0.001);

    //Cell 3
    fActual = 0;
    fExpectedFreshLog = 0.071340092;
    iX = 15; iY = 5;
    for (i = iX - 3; i <= iX + 3; i++) {
      for (j = iY - 3; j <= iY + 3; j++) {
        //Dangerously co-opt this variable
        p_oCalcsGrid->GetValueOfCell(i, j, p_iFreshLogCodes[0], & fExpectedTipup);
        fActual += fExpectedTipup;
      }
    }
    EXPECT_LT(fabs(fActual - fExpectedFreshLog), 0.001);

    //Cell 4
    fActual = 0;
    fExpectedFreshLog = 0.087341983;
    iX = 15; iY = 15;
    for (i = iX - 3; i <= iX + 3; i++) {
      for (j = iY - 3; j <= iY + 3; j++) {
        //Dangerously co-opt this variable
        p_oCalcsGrid->GetValueOfCell(i, j, p_iFreshLogCodes[0], & fExpectedTipup);
        fActual += fExpectedTipup;
      }
    }
    EXPECT_LT(fabs(fActual - fExpectedFreshLog), 0.001);

    //Last timestep
    fExpectedFreshLog = 0.01;
    //Cell 1
    iX = 5; iY = 5;
    p_oCalcsGrid->GetValueOfCell(iX, iY, p_iFreshLogCodes[1], & fActual);
    EXPECT_LT(fabs(fActual - fExpectedFreshLog), 0.001);
    //Cell 2
    iX = 5; iY = 15;
    p_oCalcsGrid->GetValueOfCell(iX, iY, p_iFreshLogCodes[1], & fActual);
    EXPECT_LT(fabs(fActual - fExpectedFreshLog), 0.001);
    //Cell 3
    iX = 15; iY = 5;
    p_oCalcsGrid->GetValueOfCell(iX, iY, p_iFreshLogCodes[1], & fActual);
    EXPECT_LT(fabs(fActual - fExpectedFreshLog), 0.001);
    //Cell 4
    iX = 15; iY = 15;
    p_oCalcsGrid->GetValueOfCell(iX, iY, p_iFreshLogCodes[1], & fActual);
    EXPECT_LT(fabs(fActual - fExpectedFreshLog), 0.001);

    //Timestep - 2
    fExpectedFreshLog = 0.0;
    //Cell 1
    iX = 5; iY = 5;
    p_oCalcsGrid->GetValueOfCell(iX, iY, p_iFreshLogCodes[2], & fActual);
    EXPECT_LT(fabs(fActual - fExpectedFreshLog), 0.001);
    //Cell 2
    iX = 5; iY = 15;
    p_oCalcsGrid->GetValueOfCell(iX, iY, p_iFreshLogCodes[2], & fActual);
    EXPECT_LT(fabs(fActual - fExpectedFreshLog), 0.001);
    //Cell 3
    iX = 15; iY = 5;
    p_oCalcsGrid->GetValueOfCell(iX, iY, p_iFreshLogCodes[2], & fActual);
    EXPECT_LT(fabs(fActual - fExpectedFreshLog), 0.001);
    //Cell 4
    iX = 15; iY = 15;
    p_oCalcsGrid->GetValueOfCell(iX, iY, p_iFreshLogCodes[2], & fActual);
    EXPECT_LT(fabs(fActual - fExpectedFreshLog), 0.001);

    //Verify the new tipups
    //Cell 1
    fExpectedTipup = 0.004717298;
    iCode = p_oCalcsGrid->GetFloatDataCode("newtipup");
    iX = 5; iY = 5;
    p_oCalcsGrid->GetValueOfCell(iX, iY, iCode, & fActual);
    EXPECT_LT(fabs(fActual - fExpectedTipup), 0.001);
    //Cell 2
    fExpectedTipup = 0.01061392;
    iX = 5; iY = 15;
    p_oCalcsGrid->GetValueOfCell(iX, iY, iCode, & fActual);
    EXPECT_LT(fabs(fActual - fExpectedTipup), 0.001);
    //Cell 3
    fExpectedTipup = 0.014446724;
    iX = 15; iY = 5;
    p_oCalcsGrid->GetValueOfCell(iX, iY, iCode, & fActual);
    EXPECT_LT(fabs(fActual - fExpectedTipup), 0.001);
    //Cell 4
    fExpectedTipup = 0.018869191;
    iX = 15; iY = 15;
    p_oCalcsGrid->GetValueOfCell(iX, iY, iCode, & fActual);
    EXPECT_LT(fabs(fActual - fExpectedTipup), 0.001);

    //Don't verify the proportions - too complicated

    delete[] p_iFreshLogCodes;
    delete p_oSimManager;
  } catch (modelErr &e) {
    delete[] p_iFreshLogCodes;
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

/////////////////////////////////////////////////////////////////////////////
// VerifySubstrateRun2TS1Proportions()
/////////////////////////////////////////////////////////////////////////////
void VerifySubstrateRun2TS1Proportions(clGrid *p_oSubstrateGrid) {
  float fExpectedTipup, fExpectedFreshLog, fExpectedScarSoil,
        fExpectedDecLog, fExpectedFFMoss, fExpectedFFLitter, fActual;
  int iX, iY;

  //Cell 1
  iX = 0; iY = 0;
  fExpectedScarSoil = 0;
  fExpectedFreshLog = 0.01;
  fExpectedDecLog = 0.11;
  fExpectedTipup = 0.2;
  fExpectedFFMoss = 0.476;
  fExpectedFFLitter = 0.204;
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
// VerifySubstrateRun2TS2Proportions()
/////////////////////////////////////////////////////////////////////////////
void VerifySubstrateRun2TS2Proportions(clGrid *p_oSubstrateGrid) {
  float fExpectedTipup, fExpectedFreshLog, fExpectedScarSoil,
        fExpectedDecLog, fExpectedFFMoss, fExpectedFFLitter, fActual;
  int iX, iY;

  //Cell 1
  iX = 0; iY = 0;
  fExpectedScarSoil = 0.45;
  fExpectedFreshLog = 0.09;
  fExpectedDecLog = 0;
  fExpectedTipup = 0.34;
  fExpectedFFMoss = 0.084;
  fExpectedFFLitter = 0.036;
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
  fExpectedScarSoil = 0.36;
  fExpectedFreshLog = 0.17;
  fExpectedDecLog = 0.01;
  fExpectedTipup = 0.28;
  fExpectedFFMoss = 0.126;
  fExpectedFFLitter = 0.054;
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
  fExpectedScarSoil = 0.146224932;
  fExpectedFreshLog = 0.167875654;
  fExpectedDecLog = 0.04;
  fExpectedTipup = 0.152608487;
  fExpectedFFMoss = 0.345303649;
  fExpectedFFLitter = 0.147987278;
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
  fExpectedScarSoil = 0;
  fExpectedFreshLog = 0.169256747;
  fExpectedDecLog = 0.049988087;
  fExpectedTipup = 0.198221137;
  fExpectedFFMoss = 0.407773821;
  fExpectedFFLitter = 0.174760209;
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
  fExpectedScarSoil = 0;
  fExpectedFreshLog = 0.009512294;
  fExpectedDecLog = 0.049988087;
  fExpectedTipup = 0.199860049;
  fExpectedFFMoss = 0.518447699;
  fExpectedFFLitter = 0.222191871;
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
// VerifySubstrateRun2TS3Proportions()
/////////////////////////////////////////////////////////////////////////////
void VerifySubstrateRun2TS3Proportions(clGrid *p_oSubstrateGrid) {
  float fExpectedTipup, fExpectedFreshLog, fExpectedScarSoil,
        fExpectedDecLog, fExpectedFFMoss, fExpectedFFLitter, fActual;
  int iX, iY;

  //Cell 1
  iX = 0; iY = 0;
  fExpectedScarSoil = 0.349659363;
  fExpectedFreshLog = 0.239311544;
  fExpectedDecLog = 0.004389352;
  fExpectedTipup = 0.313963341;
  fExpectedFFMoss = 0.06487348;
  fExpectedFFLitter = 0.02780292;
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
  fExpectedScarSoil = 0.211791635;
  fExpectedFreshLog = 0.388640914;
  fExpectedDecLog = 0.012791032;
  fExpectedTipup = 0.282627975;
  fExpectedFFMoss = 0.07290391;
  fExpectedFFLitter = 0.031244533;
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
  fExpectedScarSoil = 0.1336126;
  fExpectedFreshLog = 0.217329207;
  fExpectedDecLog = 0.026596774;
  fExpectedTipup = 0.153865788;
  fExpectedFFMoss = 0.328016942;
  fExpectedFFLitter = 0.140578689;
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
  fExpectedScarSoil = 0;
  fExpectedFreshLog = 0.230107105;
  fExpectedDecLog = 0.037370059;
  fExpectedTipup = 0.194422339;
  fExpectedFFMoss = 0.376670348;
  fExpectedFFLitter = 0.161430149;
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
  fExpectedScarSoil = 0;
  fExpectedFreshLog = 0.000108295;
  fExpectedDecLog = 0.029486458;
  fExpectedTipup = 0.197261163;
  fExpectedFFMoss = 0.541200859;
  fExpectedFFLitter = 0.231943225;
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
// VerifySubstrateRun2TS4Proportions()
/////////////////////////////////////////////////////////////////////////////
void VerifySubstrateRun2TS4Proportions(clGrid *p_oSubstrateGrid) {
  float fExpectedTipup, fExpectedFreshLog, fExpectedScarSoil,
        fExpectedDecLog, fExpectedFFMoss, fExpectedFFLitter, fActual;
  int iX, iY;

  //Cell 1
  iX = 0; iY = 0;
  fExpectedScarSoil = 0.346091173;
  fExpectedFreshLog = 0.16508864;
  fExpectedDecLog = 0.095036646;
  fExpectedTipup = 0.310493762;
  fExpectedFFMoss = 0.058302845;
  fExpectedFFLitter = 0.024986934;
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
  fExpectedScarSoil = 0.209630353;
  fExpectedFreshLog = 0.280228899;
  fExpectedDecLog = 0.179716778;
  fExpectedTipup = 0.280403828;
  fExpectedFFMoss = 0.0350141;
  fExpectedFFLitter = 0.015006043;
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
  fExpectedScarSoil = 0.132249116;
  fExpectedFreshLog = 0.06952284;
  fExpectedDecLog = 0.180332059;
  fExpectedTipup = 0.152042738;
  fExpectedFFMoss = 0.326097273;
  fExpectedFFLitter = 0.139755974;
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
  fExpectedScarSoil = 0;
  fExpectedFreshLog = 0.090875207;
  fExpectedDecLog = 0.164459882;
  fExpectedTipup = 0.054255551;
  fExpectedFFMoss = 0.483286552;
  fExpectedFFLitter = 0.207122808;
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
  fExpectedScarSoil = 0;
  fExpectedFreshLog = 0.000108295;
  fExpectedDecLog = 0.004319899;
  fExpectedTipup = 0.197261163;
  fExpectedFFMoss = 0.558817451;
  fExpectedFFLitter = 0.239493193;
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
// VerifySubstrateRun2TS1Cohorts()
/////////////////////////////////////////////////////////////////////////////
void VerifySubstrateRun2TS1Cohorts(clGrid *p_oSubstrateGrid) {
  clPackage * p_oCohort;
  float fExpectedTipup = 0.2, fExpectedFreshLog = 0.01, fExpectedScarSoil = 0, fActual;
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
// VerifySubstrateRun2TS2Cohorts()
/////////////////////////////////////////////////////////////////////////////
void VerifySubstrateRun2TS2Cohorts(clGrid *p_oSubstrateGrid) {
  clPackage * p_oCohort;
  float fExpectedTipup, fExpectedFreshLog, fExpectedScarSoil, fActual;
  int iX, iY, iAge, iActual;

  //Cell 1
  iX = 0; iY = 0;
  fExpectedTipup = 0.34;
  fExpectedFreshLog = 0.09;
  fExpectedScarSoil = 0.45;
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

  //Cell 2
  iY = 1;
  fExpectedTipup = 0.28;
  fExpectedFreshLog = 0.17;
  fExpectedScarSoil = 0.36;
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

  //Cell 3
  iY = 2;
  fExpectedTipup = 0.152608487;
  fExpectedFreshLog = 0.167875654;
  fExpectedScarSoil = 0.146224932;
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

  //Cell 4, cohort 1
  iY = 3;
  fExpectedTipup = 0.160005057;
  fExpectedFreshLog = 0.008000253;
  fExpectedScarSoil = 0;
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
  fExpectedFreshLog = 0.161646671;
  fExpectedScarSoil = 0;
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
  fExpectedScarSoil = 0;
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
// VerifySubstrateRun2TS3Cohorts()
/////////////////////////////////////////////////////////////////////////////
void VerifySubstrateRun2TS3Cohorts(clGrid *p_oSubstrateGrid) {
  clPackage * p_oCohort;
  float fExpectedTipup, fExpectedFreshLog, fExpectedScarSoil, fActual;
  int iX, iY, iAge, iActual;

  //Cell 1, cohort 1
  iX = 0; iY = 0;
  fExpectedTipup = 0.264321844;
  fExpectedFreshLog = 0.069967547;
  fExpectedScarSoil = 0.349837735;
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

  //Cell 1, cohort 2
  fExpectedTipup = 0.049826457;
  fExpectedFreshLog = 0.172756354;
  fExpectedScarSoil = 0;
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

  //Cell 2, cohort 1
  iY = 1;
  fExpectedTipup = 0.16481086;
  fExpectedFreshLog = 0.100063736;
  fExpectedScarSoil = 0.211899677;
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

  //Cell 2, cohort 2
  fExpectedTipup = 0.117932443;
  fExpectedFreshLog = 0.293457344;
  fExpectedScarSoil = 0;
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


  //Cell 3, cohort 1
  iY = 2;
  fExpectedTipup = 0.139516691;
  fExpectedFreshLog = 0.153474136;
  fExpectedScarSoil = 0.13368076;
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
  fExpectedScarSoil = 0;
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
  fExpectedFreshLog = 0.143104415;
  fExpectedScarSoil = 0;
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
  fExpectedScarSoil = 0;
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
// VerifySubstrateRun2TS4Cohorts()
/////////////////////////////////////////////////////////////////////////////
void VerifySubstrateRun2TS4Cohorts(clGrid *p_oSubstrateGrid) {
  clPackage * p_oCohort;
  float fExpectedTipup, fExpectedFreshLog, fExpectedScarSoil, fActual;
  int iX, iY, iAge, iActual;

  //Cell 1, cohort 1
  iX = 0; iY = 0;
  fExpectedTipup = 0.049826457;
  fExpectedFreshLog = 0.172756354;
  fExpectedScarSoil = 0;
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
  fExpectedScarSoil = 0;
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
  fExpectedScarSoil = 0;
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
  fExpectedScarSoil = 0;
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
// VerifySubstrateRun2TS1Tipup()
/////////////////////////////////////////////////////////////////////////////
void VerifySubstrateRun2TS1Tipup(clGrid *p_oCalcsGrid) {

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
// VerifySubstrateRun2TS2Tipup()
/////////////////////////////////////////////////////////////////////////////
void VerifySubstrateRun2TS2Tipup(clGrid *p_oCalcsGrid) {

  float fExpectedTipup, fActual;
  int iCode = p_oCalcsGrid->GetFloatDataCode("newtipup"),
      iX, iY;

  //Cell 1
  iX = 0; iY = 0;
  fExpectedTipup = 0.34;
  p_oCalcsGrid->GetValueOfCell(iX, iY, iCode, & fActual);
  EXPECT_LT(fabs(fActual - fExpectedTipup), 0.001);
  //Cell 2
  iY = 1;
  fExpectedTipup = 0.28;
  p_oCalcsGrid->GetValueOfCell(iX, iY, iCode, & fActual);
  EXPECT_LT(fabs(fActual - fExpectedTipup), 0.001);
  //Cell 3
  iY = 2;
  fExpectedTipup = 0.173586489;
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
// VerifySubstrateRun2TS3Tipup()
/////////////////////////////////////////////////////////////////////////////
void VerifySubstrateRun2TS3Tipup(clGrid *p_oCalcsGrid) {

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
// VerifySubstrateRun2TS4Tipup()
/////////////////////////////////////////////////////////////////////////////
void VerifySubstrateRun2TS4Tipup(clGrid *p_oCalcsGrid) {

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
// VerifySubstrateRun2TS1SubstrateArrays()
/////////////////////////////////////////////////////////////////////////////
void VerifySubstrateRun2TS1SubstrateArrays(clGrid *p_oCalcsGrid) {
  std::stringstream sLabel;
  float fExpectedLog = 0.01, //all values are the same
        fActual;
  int *p_iLogCodes = new int[3],
       iX, iY, i;

  //Fresh logs
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

  //Decayed logs
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
// VerifySubstrateRun2TS2SubstrateArrays()
/////////////////////////////////////////////////////////////////////////////
void VerifySubstrateRun2TS2SubstrateArrays(clGrid *p_oCalcsGrid) {
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
  fExpectedLog = 0.09;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[0], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 2
  iY = 1;
  fExpectedLog = 0.17;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[0], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 3
  iY = 2;
  fExpectedLog = 0.176266855;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[0], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 4
  iY = 3;
  fExpectedLog = 0.161646671;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[0], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 5
  iY = 4;
  fExpectedLog = 0.0;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[0], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);

  //Last timestep
  //Cell 1
  iX = 0; iY = 0;
  fExpectedLog = 0.0;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[1], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 2
  iY = 1;
  fExpectedLog = 0.0;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[1], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 3
  iY = 2;
  fExpectedLog = 0.0;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[1], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 4
  iY = 3;
  fExpectedLog = 0.01;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[1], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 5
  iY = 4;
  fExpectedLog = 0.01;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[1], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);

  //Timestep - 2
  //Cell 1
  fExpectedLog = 0.0;
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

  //Decayed logs
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
  fExpectedLog = 0;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[0], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 2
  iY = 1;
  fExpectedLog = 0.01;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[0], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 3
  iY = 2;
  fExpectedLog = 0.04;
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
  fExpectedLog = 0;
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
// VerifySubstrateRun2TS3SubstrateArrays()
/////////////////////////////////////////////////////////////////////////////
void VerifySubstrateRun2TS3SubstrateArrays(clGrid *p_oCalcsGrid) {
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
  fExpectedLog = 0.0;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[0], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);

  //Last timestep
  //Cell 1
  iX = 0; iY = 0;
  fExpectedLog = 0.09;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[1], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 2
  iY = 1;
  fExpectedLog = 0.17;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[1], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 3
  iY = 2;
  fExpectedLog = 0.176266855;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[1], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 4
  iY = 3;
  fExpectedLog = 0.161646671;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[1], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 5
  iY = 4;
  fExpectedLog = 0.0;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[1], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);

  //Timestep - 2
  //Cell 1
  fExpectedLog = 0.0;
  iX = 0; iY = 0;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[2], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 2
  fExpectedLog = 0.0;
  iY = 1;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[2], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 3
  fExpectedLog = 0.0;
  iY = 2;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[2], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 4
  fExpectedLog = 0.01;
  iY = 3;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[2], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 5
  fExpectedLog = 0.01;
  iY = 4;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[2], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);

  //Decayed logs
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
  fExpectedLog = 0.004389352;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[0], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 2
  iY = 1;
  fExpectedLog = 0.008290998;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[0], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 3
  iY = 2;
  fExpectedLog = 0.008596636;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[0], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 4
  iY = 3;
  fExpectedLog = 0.017287601;
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
  fExpectedLog = 0;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[1], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 2
  iY = 1;
  fExpectedLog = 0.01;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[1], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 3
  iY = 2;
  fExpectedLog = 0.04;
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
// VerifySubstrateRun2TS4SubstrateArrays()
/////////////////////////////////////////////////////////////////////////////
void VerifySubstrateRun2TS4SubstrateArrays(clGrid *p_oCalcsGrid) {
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
  fExpectedLog = 0.0;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[1], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);

  //Timestep - 2
  //Cell 1
  iX = 0; iY = 0;
  fExpectedLog = 0.09;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[2], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 2
  iY = 1;
  fExpectedLog = 0.17;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[2], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 3
  iY = 2;
  fExpectedLog = 0.176266855;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[2], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 4
  iY = 3;
  fExpectedLog = 0.161646671;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[2], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 5
  iY = 4;
  fExpectedLog = 0.0;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[2], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);

  //Decayed logs
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
  fExpectedLog = 0.093061422;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[0], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 2
  iY = 1;
  fExpectedLog = 0.174180074;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[0], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 3
  iY = 2;
  fExpectedLog = 0.169240638;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[0], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 4
  iY = 3;
  fExpectedLog = 0.156592335;
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
  fExpectedLog = 0.004389352;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[1], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 2
  iY = 1;
  fExpectedLog = 0.008290998;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[1], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 3
  iY = 2;
  fExpectedLog = 0.008596636;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[1], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 4
  iY = 3;
  fExpectedLog = 0.017287601;
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
  fExpectedLog = 0;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[2], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 2
  iY = 1;
  fExpectedLog = 0.01;
  p_oCalcsGrid->GetValueOfCell(iX, iY, p_iLogCodes[2], & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog), 0.001);
  //Cell 3
  iY = 2;
  fExpectedLog = 0.04;
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
// WriteSubstrateXMLFile1()
/////////////////////////////////////////////////////////////////////////////
const char* WriteSubstrateXMLFile1()
{
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
       << "<plot_lenX>200.0</plot_lenX>"
       << "<plot_lenY>200.0</plot_lenY>"
       << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
       << "<plot_temp_C>12.88171785</plot_temp_C>"
       << "<plot_latitude>55.37</plot_latitude>"
       << "</plot>";

  WriteSubstrateCommonTreeStuff(oOut);

  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>Harvest</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "</behavior>"
       //Have to have a StochasticMortality behavior so dead is registered
       << "<behavior>"
       << "<behaviorName>StochasticMortality</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>2</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>Substrate</behaviorName>"
       << "<version>2.1</version>"
       << "<listPosition>3</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
       << "</behavior>"
       //Let the dead remover get rid of the trees we kill
       << "<behavior>"
       << "<behaviorName>RemoveDead</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>4</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\" />"
       << "<applyTo species=\"Species_1\" type=\"Sapling\" />"
       << "</behavior>"
       << "</behaviorList>"
       << "<Harvest1>"
       << "<ha_cutEvent>"
       << "<ha_applyToSpecies species=\"Species_1\" />"
       << "<ha_timestep>2</ha_timestep>"
       << "<ha_cutType>gap</ha_cutType>"
       << "<ha_cutAmountType>percent of density</ha_cutAmountType>"
       << "<ha_dbhRange>"
       << "<ha_low>0.0</ha_low>"
       << "<ha_high>25.0</ha_high>"
       << "<ha_amountToCut>100.0</ha_amountToCut>"
       << "</ha_dbhRange>"
       << "<ha_applyToCell x=\"0\" y=\"0\" />"
       << "</ha_cutEvent>"
       << "<ha_cutEvent>"
       << "<ha_applyToSpecies species=\"Species_1\" />"
       << "<ha_timestep>2</ha_timestep>"
       << "<ha_cutType>clear</ha_cutType>"
       << "<ha_cutAmountType>percent of density</ha_cutAmountType>"
       << "<ha_dbhRange>"
       << "<ha_low>0.0</ha_low>"
       << "<ha_high>25.0</ha_high>"
       << "<ha_amountToCut>100.0</ha_amountToCut>"
       << "</ha_dbhRange>"
       << "<ha_applyToCell x=\"0\" y=\"1\" />"
       << "</ha_cutEvent>"
       << "<ha_cutEvent>"
       << "<ha_applyToSpecies species=\"Species_1\" />"
       << "<ha_timestep>2</ha_timestep>"
       << "<ha_cutType>partial</ha_cutType>"
       << "<ha_cutAmountType>percent of density</ha_cutAmountType>"
       << "<ha_dbhRange>"
       << "<ha_low>0.0</ha_low>"
       << "<ha_high>15.0</ha_high>"
       << "<ha_amountToCut>100.0</ha_amountToCut>"
       << "</ha_dbhRange>"
       << "<ha_applyToCell x=\"0\" y=\"2\" />"
       << "</ha_cutEvent>"
       << "</Harvest1>"
       << "<StochasticMortality2>"
       << "<mo_stochasticMortRate>"
       << "<mo_smrVal species=\"Species_1\">0.0</mo_smrVal>"
       << "</mo_stochasticMortRate>"
       << "</StochasticMortality2>"
       << "<Substrate3>"
       << "<su_scarSoilDecayAlpha>-5.1E-4</su_scarSoilDecayAlpha>"
       << "<su_scarSoilDecayBeta>4.4</su_scarSoilDecayBeta>"
       << "<su_tipupDecayAlpha>-7.0E-4</su_tipupDecayAlpha>"
       << "<su_tipupDecayBeta>4.3</su_tipupDecayBeta>"
       << "<su_freshLogDecayAlpha>-0.05</su_freshLogDecayAlpha>"
       << "<su_freshLogDecayBeta>6.5</su_freshLogDecayBeta>"
       << "<su_decayedLogDecayAlpha>-0.7985</su_decayedLogDecayAlpha>"
       << "<su_decayedLogDecayBeta>1.1</su_decayedLogDecayBeta>"
       << "<su_maxNumberDecayYears>3</su_maxNumberDecayYears>"
       << "<su_initialScarSoil>0.0</su_initialScarSoil>"
       << "<su_initialTipup>0.2</su_initialTipup>"
       << "<su_initialFreshLog>0.01</su_initialFreshLog>"
       << "<su_initialDecayedLog>0.11</su_initialDecayedLog>"
       << "<su_partialCutScarSoil>0.17</su_partialCutScarSoil>"
       << "<su_partialCutTipup>0.15</su_partialCutTipup>"
       << "<su_partialCutFreshLog>0.06</su_partialCutFreshLog>"
       << "<su_partialCutDecayedLog>0.04</su_partialCutDecayedLog>"
       << "<su_gapCutScarSoil>0.45</su_gapCutScarSoil>"
       << "<su_gapCutTipup>0.34</su_gapCutTipup>"
       << "<su_gapCutFreshLog>0.09</su_gapCutFreshLog>"
       << "<su_gapCutDecayedLog>0.0</su_gapCutDecayedLog>"
       << "<su_clearCutScarSoil>0.36</su_clearCutScarSoil>"
       << "<su_clearCutTipup>0.28</su_clearCutTipup>"
       << "<su_clearCutFreshLog>0.17</su_clearCutFreshLog>"
       << "<su_clearCutDecayedLog>0.01</su_clearCutDecayedLog>"
       << "<su_propOfDeadFall>"
       << "<su_podfVal species=\"Species_1\">1</su_podfVal>"
       << "</su_propOfDeadFall>"
       << "<su_propOfFallUproot>"
       << "<su_pofuVal species=\"Species_1\">1</su_pofuVal>"
       << "</su_propOfFallUproot>"
       << "<su_propOfSnagsUproot>"
       << "<su_posuVal species=\"Species_1\">0</su_posuVal>"
       << "</su_propOfSnagsUproot>"
       << "<su_mossProportion>0.7</su_mossProportion>"
       << "<su_directionalTreeFall>0</su_directionalTreeFall>"
       << "<su_rootTipupFactor>3.1</su_rootTipupFactor>"
       << "</Substrate3>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteSubstrateXMLFile3()
/////////////////////////////////////////////////////////////////////////////
const char* WriteSubstrateXMLFile3()
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
       << "<yearsPerTimestep>1</yearsPerTimestep>"
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
       << "<mo_smrVal species=\"Species_1\">1.0</mo_smrVal>"
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
       << "<su_maxNumberDecayYears>10</su_maxNumberDecayYears>"
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
       << "<su_directionalTreeFall>1</su_directionalTreeFall>"
       << "<su_rootTipupFactor>3.1</su_rootTipupFactor>"
       << "</Substrate2>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}
