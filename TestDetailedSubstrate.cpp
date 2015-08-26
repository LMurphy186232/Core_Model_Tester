//---------------------------------------------------------------------------
// TestDetailedSubstrate.cpp
//---------------------------------------------------------------------------
#include "TestDetailedSubstrate.h"
#include <gtest/gtest.h>
#include "Grid.h"
#include "SimManager.h"
#include "BehaviorBase.h"
#include "TreePopulation.h"
#include <math.h>
#include <fstream>

/////////////////////////////////////////////////////////////////////////////
// TestSubstrateGridSetup()
// Tests aspects of substrate grid setup.  This will enter two parameter
// files:
// -- With no grid maps defined
// -- With Substrate and substratecalcs grid maps
//
// In the first case, grid cell resolution should match harvest and the plot;
// in the second, it should be what was specified in the map. The second case
// also tests that a value is correctly read in from the map.
/////////////////////////////////////////////////////////////////////////////
TEST(DetailedSubstrate, TestSubstrateGridSetup) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    clGrid * p_oSubstrateGrid, *p_oSubstrateCalcsGrid;
    float fVal;

    //Feed file # 1 and make sure grid resolutions are right
    p_oSimManager->ReadFile(WriteDetailedSubstrateXMLFile1(1));
    p_oSubstrateGrid = p_oSimManager->GetGridObject("DetailedSubstrate");
    EXPECT_LT(fabs(p_oSubstrateGrid->GetLengthXCells() - 8), 0.001);
    EXPECT_LT(fabs(p_oSubstrateGrid->GetLengthYCells() - 8), 0.001);

    //Feed file # 2 and make sure grid resolutions are right
    p_oSimManager->ReadFile(WriteDetailedSubstrateXMLFile2());
    p_oSubstrateGrid = p_oSimManager->GetGridObject("DetailedSubstrate");
    EXPECT_LT(fabs(p_oSubstrateGrid->GetLengthXCells() - 3), 0.001);
    EXPECT_LT(fabs(p_oSubstrateGrid->GetLengthYCells() - 2), 0.001);

    //Make sure the substrate calcs resolutions are right and a value got read
    p_oSubstrateCalcsGrid = p_oSimManager->GetGridObject("detailedsubstratecalcs");
    EXPECT_LT(fabs(p_oSubstrateCalcsGrid->GetLengthXCells() - 3), 0.001);
    EXPECT_LT(fabs(p_oSubstrateCalcsGrid->GetLengthYCells() - 2), 0.001);

    p_oSubstrateCalcsGrid->GetValueOfCell(0, 0, p_oSubstrateCalcsGrid->GetFloatDataCode("newtipup"), &fVal);
    EXPECT_LT(fabs(fVal - 0.1), 0.001);
    delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

/////////////////////////////////////////////////////////////////////////////
// TestNewInputs()
// Tests new inputs to substrate. A single tree is entered into each of 8
// separate grid cells. The trees are different combinations of adult/snag,
// standing/fallen, intact/newly broken/previously broken. We check to make sure
// the correct amount of new log and tipup is added to the cells after one
// timestep.
/////////////////////////////////////////////////////////////////////////////
TEST(DetailedSubstrate, TestNewInputs)
{
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    clTreePopulation *p_oPop;
    clTree *p_oTree;
    clGrid * p_oSubstrateGrid;

    float fExpectedLog, fExpectedTipup, fActual;
    int 	iLogCode, iTipupCode,
    iX, iY;

    //***************************
    // Test log and tipup inputs
    //***************************

    p_oSimManager->ReadFile(WriteDetailedSubstrateXMLFile3());
    //Grab our pointers
    p_oPop = (clTreePopulation*) p_oSimManager->GetPopulationObject("treepopulation");

    p_oSubstrateGrid = p_oSimManager->GetGridObject("DetailedSubstrate");

    iLogCode = p_oSubstrateGrid->GetFloatDataCode("totallog");
    iTipupCode = p_oSubstrateGrid->GetFloatDataCode("tipup");


    int iAdultDeadCode, iSnagDeadCode, iAdultFallCode, iAdultBreakCode, iSnagNewBreakCode, iSnagOldBreakCode;

    //Run for 1 timestep
    p_oSimManager->RunSim(1);

    iAdultDeadCode = p_oPop->GetIntDataCode("dead",0,clTreePopulation::adult);
    iSnagDeadCode  = p_oPop->GetIntDataCode("dead",0,clTreePopulation::snag);
    iAdultFallCode = p_oPop->GetBoolDataCode("Fall",0,clTreePopulation::adult);
    iAdultBreakCode = p_oPop->GetFloatDataCode("NewBreakHeight",0,clTreePopulation::adult);
    iSnagNewBreakCode = p_oPop->GetFloatDataCode("NewBreakHeight",0,clTreePopulation::snag);
    iSnagOldBreakCode = p_oPop->GetFloatDataCode("SnagOldBreakHeight",0,clTreePopulation::snag);


    //Cell 0,0; dead tree intact standing
    p_oTree = p_oPop->CreateTree(1, 1, 0, clTreePopulation::adult, 35);
    p_oTree->SetValue(iAdultDeadCode, natural);
    p_oTree->SetValue(iAdultFallCode, false);
    p_oTree->SetValue(iAdultBreakCode,(float) -1.0);

    //Cell 0,1; dead tree intact fallen
    p_oTree = p_oPop->CreateTree(1, 9, 0, clTreePopulation::adult, 35);
    p_oTree->SetValue(iAdultDeadCode, natural);
    p_oTree->SetValue(iAdultFallCode, true);
    p_oTree->SetValue(iAdultBreakCode,(float) -1.0);

    //Cell 0,2; dead tree broken standing
    p_oTree = p_oPop->CreateTree(1, 17, 0, clTreePopulation::adult, 35);
    p_oTree->SetValue(iAdultDeadCode, natural);
    p_oTree->SetValue(iAdultFallCode, false);
    p_oTree->SetValue(iAdultBreakCode, (float) 5.0);

    //Cell 0,3; snag intact standing
    p_oTree = p_oPop->CreateTree(1, 25, 0, clTreePopulation::snag, 35);
    p_oTree->SetValue(iSnagDeadCode, notdead);
    p_oTree->SetValue(iSnagNewBreakCode, (float) -1.0);
    p_oTree->SetValue(iSnagOldBreakCode,(float) -1.0);

    //Cell 0,4; snag intact fallen
    p_oTree = p_oPop->CreateTree(1, 33, 0, clTreePopulation::snag, 35);
    p_oTree->SetValue(iSnagDeadCode, natural);
    p_oTree->SetValue(iSnagNewBreakCode, (float) -1.0);
    p_oTree->SetValue(iSnagOldBreakCode,(float) -1.0);

    //Cell 0,5; snag previously broken standing
    p_oTree = p_oPop->CreateTree(1, 41, 0, clTreePopulation::snag, 35);
    p_oTree->SetValue(iSnagDeadCode, notdead);
    p_oTree->SetValue(iSnagNewBreakCode, (float) -1.0);
    p_oTree->SetValue(iSnagOldBreakCode, (float) 5.0);

    //Cell 0,6; snag newly broken standing
    p_oTree = p_oPop->CreateTree(1, 49, 0, clTreePopulation::snag, 35);
    p_oTree->SetValue(iSnagDeadCode, notdead);
    p_oTree->SetValue(iSnagNewBreakCode, (float) 5.0);
    p_oTree->SetValue(iSnagOldBreakCode, (float) -1.0);

    //Cell 0,7; snag previously broken fallen
    p_oTree = p_oPop->CreateTree(1, 57, 0, clTreePopulation::snag, 35);
    p_oTree->SetValue(iSnagDeadCode, natural);
    p_oTree->SetValue(iSnagNewBreakCode, (float) -1.0);
    p_oTree->SetValue(iSnagOldBreakCode, (float) 5.0);


    //Run detailedsubstrate and removedead only for 1 timestep
    p_oSimManager->GetBehaviorObject("DetailedSubstrate")->Action();
    p_oSimManager->GetBehaviorObject("removedead")->Action();

    //Cell 1
    iX = 0; iY = 0;
    fExpectedLog = 0;
    fExpectedTipup = 0;

    p_oSubstrateGrid->GetValueOfCell(iX, iY, iLogCode, & fActual);
    ASSERT_TRUE(fabs(fActual)< 0.001);

    p_oSubstrateGrid->GetValueOfCell(iX, iY, iTipupCode, & fActual);
    ASSERT_TRUE(fabs(fActual)< 0.001);


    //Cell 2
    iY = 1;
    fExpectedLog = 0.075081213526109;
    fExpectedTipup = 0.0135297105491514;

    p_oSubstrateGrid->GetValueOfCell(iX, iY, iLogCode, & fActual);
    EXPECT_LT(fabs(fActual - fExpectedLog)/fExpectedLog, 0.001);

    p_oSubstrateGrid->GetValueOfCell(iX, iY, iTipupCode, & fActual);
    EXPECT_LT(fabs(fActual - fExpectedTipup)/fExpectedTipup, 0.001);

    //Cell 3
    iY = 2;
    fExpectedLog = 0.0490610765813205;
    fExpectedTipup = 0;

    p_oSubstrateGrid->GetValueOfCell(iX, iY, iLogCode, & fActual);
    EXPECT_LT(fabs(fActual - fExpectedLog)/fExpectedLog, 0.001);

    p_oSubstrateGrid->GetValueOfCell(iX, iY, iTipupCode, & fActual);
    ASSERT_TRUE(fabs(fActual)< 0.001);

    //Cell 4
    iY = 3;
    fExpectedLog = 0;
    fExpectedTipup = 0;

    p_oSubstrateGrid->GetValueOfCell(iX, iY, iLogCode, & fActual);
    ASSERT_TRUE(fabs(fActual)< 0.001);

    p_oSubstrateGrid->GetValueOfCell(iX, iY, iTipupCode, & fActual);
    ASSERT_TRUE(fabs(fActual)< 0.001);

    //Cell 5
    iY = 4;
    fExpectedLog = 0.075081213526109;
    fExpectedTipup = 0.0135297105491514;

    p_oSubstrateGrid->GetValueOfCell(iX, iY, iLogCode, & fActual);
    EXPECT_LT(fabs(fActual - fExpectedLog)/fExpectedLog, 0.001);

    p_oSubstrateGrid->GetValueOfCell(iX, iY, iTipupCode, & fActual);
    EXPECT_LT(fabs(fActual - fExpectedTipup)/fExpectedTipup, 0.001);

    //Cell 6
    iY = 5;
    fExpectedLog = 0;
    fExpectedTipup = 0;

    p_oSubstrateGrid->GetValueOfCell(iX, iY, iLogCode, & fActual);
    ASSERT_TRUE(fabs(fActual)< 0.001);

    p_oSubstrateGrid->GetValueOfCell(iX, iY, iTipupCode, & fActual);
    ASSERT_TRUE(fabs(fActual)< 0.001);

    //Cell 7
    iY = 6;
    fExpectedLog = 0.0490610765813205;
    fExpectedTipup = 0;

    p_oSubstrateGrid->GetValueOfCell(iX, iY, iLogCode, & fActual);
    EXPECT_LT(fabs(fActual - fExpectedLog)/fExpectedLog, 0.001);

    p_oSubstrateGrid->GetValueOfCell(iX, iY, iTipupCode, & fActual);
    ASSERT_TRUE(fabs(fActual)< 0.001);

    //Cell 8
    iY = 7;
    fExpectedLog = 0.0260201369447884;
    fExpectedTipup = 0.0135297105491514;

    p_oSubstrateGrid->GetValueOfCell(iX, iY, iLogCode, & fActual);
    EXPECT_LT(fabs(fActual - fExpectedLog)/fExpectedLog, 0.001);

    p_oSubstrateGrid->GetValueOfCell(iX, iY, iTipupCode, & fActual);
    EXPECT_LT(fabs(fActual - fExpectedTipup)/fExpectedTipup, 0.001);
    delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

/////////////////////////////////////////////////////////////////////////////
// TestSubstrateRun1()
// Substrate normal processing run 1. Verifies substrate decay calculations over
// 4 timesteps with a 1-year timestep length.  This run has 5 cells with
// different harvest and mortality regimes. Non-directional tree fall and 100%
// decay class and tipup probabilities are used to avoid having to average over
// large numbers of trees. This function tests that the substrate numbers are
// calculated correctly for all types of logs, tipup, scarified soil, moss, and
// litter after each timestep.
/////////////////////////////////////////////////////////////////////////////
TEST(DetailedSubstrate, TestSubstrateRun1)
{
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    clGrid * p_oSubstrateGrid;
    clTreePopulation *p_oPop;
    clTree *p_oTree;
    int i, iDead = natural;

    //Create and feed in the file
    p_oSimManager->ReadFile(WriteDetailedSubstrateXMLFile1(1));
    //Grab our pointers
    p_oPop = (clTreePopulation*) p_oSimManager->GetPopulationObject("treepopulation");
    p_oSubstrateGrid = p_oSimManager->GetGridObject("DetailedSubstrate");

    //Create our trees for harvesting
    p_oTree = p_oPop->CreateTree(1, 17, 0, clTreePopulation::adult, 20);
    p_oTree = p_oPop->CreateTree(1, 25, 0, clTreePopulation::adult, 20);
    p_oTree = p_oPop->CreateTree(1, 33, 0, clTreePopulation::adult, 12);

    //********************************
    //Timestep 1:  Just run.
    //********************************
    p_oSimManager->RunSim(1);

    //Verify the substrate proportions
    VerifyDetailedSubstrateRun1TS1Proportions(p_oSubstrateGrid);

    //********************************
    //Timestep 2:
    //********************************

    //Set the timestep to 2
    p_oSimManager->SetCurrentTimestep(2);

    //Run the harvest behavior
    p_oSimManager->GetBehaviorObject(0)->Action();

    //Create and then kill certain trees within cell 0, 1
    //Tree where y = 10
    p_oTree = p_oPop->CreateTree(1, 10, 0, clTreePopulation::adult, 12);
    p_oTree->SetValue(p_oPop->GetIntDataCode("dead", p_oTree->GetSpecies(), p_oTree->GetType()), iDead);

    //Tree where y = 11
    p_oTree = p_oPop->CreateTree(1, 11, 0, clTreePopulation::adult, 15);
    p_oTree->SetValue(p_oPop->GetIntDataCode("dead", p_oTree->GetSpecies(), p_oTree->GetType()), iDead);

    //Tree where y = 12
    p_oTree = p_oPop->CreateTree(1, 12, 0, clTreePopulation::sapling, 8);
    p_oTree->SetValue(p_oPop->GetIntDataCode("dead", p_oTree->GetSpecies(), p_oTree->GetType()), iDead);

    //Now create and then kill certain trees within cell 0, 4
    //Tree where y = 34
    p_oTree = p_oPop->CreateTree(1, 34, 0, clTreePopulation::adult, 20);
    p_oTree->SetValue(p_oPop->GetIntDataCode("dead", p_oTree->GetSpecies(), p_oTree->GetType()), iDead);

    //Tree where y = 35
    p_oTree = p_oPop->CreateTree(1, 35, 0, clTreePopulation::adult, 25);
    p_oTree->SetValue(p_oPop->GetIntDataCode("dead", p_oTree->GetSpecies(), p_oTree->GetType()), iDead);


    //Now run the substrate behavior and the tree killer
    for (i = 2; i < p_oSimManager->GetNumberOfBehaviors(); i++) {
      p_oSimManager->GetBehaviorObject(i)->Action();
    }
    //Now timestep cleanup
    for (i = 0; i < p_oSimManager->GetNumberOfBehaviors(); i++) {
      p_oSimManager->GetBehaviorObject(i)->TimestepCleanup();
    }

    //Verify the substrate proportions
    VerifyDetailedSubstrateRun1TS2Proportions(p_oSubstrateGrid);

    //********************************
    //Timestep 3:
    //********************************
    //We have to fake this timestep.  The light behavior will interfere with our
    //ability to kill trees, so we have to skip it.  Set the timestep to 3
    p_oSimManager->SetCurrentTimestep(3);

    //Create and kill a tree in cell 0, 1 where y = 13
    p_oTree = p_oPop->CreateTree(1, 13, 0, clTreePopulation::adult, 28);
    p_oTree->SetValue(p_oPop->GetIntDataCode("dead", p_oTree->GetSpecies(), p_oTree->GetType()), iDead);

    //Create and kill a tree in cell 0, 3 where y = 26
    p_oTree = p_oPop->CreateTree(1, 26, 0, clTreePopulation::adult, 100);
    p_oTree->SetValue(p_oPop->GetIntDataCode("dead", p_oTree->GetSpecies(), p_oTree->GetType()), iDead);

    //Create and kill a tree in cell 0, 4 where y = 36
    p_oTree = p_oPop->CreateTree(1, 36, 0, clTreePopulation::adult, 35);
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

    //Verify the substrate proportions
    VerifyDetailedSubstrateRun1TS3Proportions(p_oSubstrateGrid);

    //********************************
    //Timestep 4:  Just run.
    //********************************
    p_oSimManager->RunSim(1);


    //Verify the substrate proportions
    VerifyDetailedSubstrateRun1TS4Proportions(p_oSubstrateGrid);

    delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

/////////////////////////////////////////////////////////////////////////////
// TestSubstrateRun2()
// Substrate normal processing, run 2. This tests substrate calculations in
// Cell 1 from run 1 (no harvest or mortality) with a 2-year timestep length
// this time. Model is run for 1 timestep and final proportions are checked to
// match those after 2 timesteps in run 1. The numbers would not match for more
// complicated scenarios where mortality and harvest occur at different times,
// or where cohorts are removed over longer runs.
/////////////////////////////////////////////////////////////////////////////
TEST(DetailedSubstrate, TestSubstrateRun2)
{
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    clGrid * p_oSubstrateGrid;

    //Create and feed in the file
    p_oSimManager->ReadFile(WriteDetailedSubstrateXMLFile1(2));
    //Grab our pointers
    p_oSubstrateGrid = p_oSimManager->GetGridObject("DetailedSubstrate");

    //********************************
    //Timestep 1:  Just run.
    //********************************
    p_oSimManager->RunSim(1);

    //Verify the substrate proportions
    VerifyDetailedSubstrateRun2TS1Proportions(p_oSubstrateGrid);
    delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

/////////////////////////////////////////////////////////////////////////////
// VerifyDetailedSubstrateRun1TS1Proportions()
/////////////////////////////////////////////////////////////////////////////
void VerifyDetailedSubstrateRun1TS1Proportions(clGrid *p_oSubstrateGrid) {
  float fExpectedTipup, fExpectedLog1, fExpectedLog2, fExpectedLog3,
  fExpectedLog4, fExpectedLog5, fExpectedScarSoil,
  fExpectedFFMoss, fExpectedFFLitter, fActual;
  int iX, iY;

  //Cell 1
  iX = 0; iY = 0;
  fExpectedLog1 = 0.183939720585721;
  fExpectedLog2 = 0.316060279414279;
  fExpectedLog3 = 0;
  fExpectedLog4 = 0.121306131942527;
  fExpectedLog5 = 0.0786938680574733;
  fExpectedTipup = 0.0606530659712633;
  fExpectedScarSoil = 0;
  fExpectedFFMoss = 0.0957387736114947;
  fExpectedFFLitter = 0.143608160417242;

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("scarsoil"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedScarSoil), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("tipup"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedTipup), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("loggroup1smalldecay1"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog1), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("loggroup1smalldecay2"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog2), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("loggroup1smalldecay3"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog3), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("loggroup1smalldecay4"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog4), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("loggroup1smalldecay5"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog5), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("ffmoss"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedFFMoss), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("fflitter"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedFFLitter), 0.001);

  //Cell 2
  iY = 1;
  fExpectedLog1 = 0.183939720585721;
  fExpectedLog2 = 0.316060279414279;
  fExpectedLog3 = 0;
  fExpectedLog4 = 0.121306131942527;
  fExpectedLog5 = 0.0786938680574733;
  fExpectedTipup = 0.0606530659712633;
  fExpectedScarSoil = 0;
  fExpectedFFMoss = 0.0957387736114947;
  fExpectedFFLitter = 0.143608160417242;

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("scarsoil"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedScarSoil), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("tipup"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedTipup), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("loggroup1smalldecay1"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog1), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("loggroup1smalldecay2"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog2), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("loggroup1smalldecay3"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog3), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("loggroup1smalldecay4"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog4), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("loggroup1smalldecay5"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog5), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("ffmoss"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedFFMoss), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("fflitter"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedFFLitter), 0.001);

  //Cell 3
  iY = 2;
  fExpectedLog1 = 0.183939720585721;
  fExpectedLog2 = 0.316060279414279;
  fExpectedLog3 = 0;
  fExpectedLog4 = 0.121306131942527;
  fExpectedLog5 = 0.0786938680574733;
  fExpectedTipup = 0.0606530659712633;
  fExpectedScarSoil = 0;
  fExpectedFFMoss = 0.0957387736114947;
  fExpectedFFLitter = 0.143608160417242;

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("scarsoil"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedScarSoil), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("tipup"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedTipup), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("loggroup1smalldecay1"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog1), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("loggroup1smalldecay2"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog2), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("loggroup1smalldecay3"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog3), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("loggroup1smalldecay4"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog4), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("loggroup1smalldecay5"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog5), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("ffmoss"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedFFMoss), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("fflitter"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedFFLitter), 0.001);

  //Cell 4
  iY = 3;
  fExpectedLog1 = 0;
  fExpectedLog2 = 0;
  fExpectedLog3 = 0;
  fExpectedLog4 = 0;
  fExpectedLog5 = 0;
  fExpectedTipup = 0.0606530659712633;
  fExpectedScarSoil = 0;
  fExpectedFFMoss = 0.0957387736114947;
  fExpectedFFLitter = 0.143608160417242;

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("scarsoil"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedScarSoil), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("tipup"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedTipup), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("loggroup1largedecay1"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog1), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("loggroup1largedecay2"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog2), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("loggroup1largedecay3"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog3), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("loggroup1largedecay4"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog4), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("loggroup1largedecay5"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog5), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("ffmoss"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedFFMoss), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("fflitter"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedFFLitter), 0.001);

  //Cell 5
  iY = 4;
  fExpectedLog1 = 0.183939720585721;
  fExpectedLog2 = 0.316060279414279;
  fExpectedLog3 = 0;
  fExpectedLog4 = 0.121306131942527;
  fExpectedLog5 = 0.0786938680574733;
  fExpectedTipup = 0.0606530659712633;
  fExpectedScarSoil = 0;
  fExpectedFFMoss = 0.0957387736114947;
  fExpectedFFLitter = 0.143608160417242;

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("scarsoil"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedScarSoil), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("tipup"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedTipup), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("loggroup1smalldecay1"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog1), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("loggroup1smalldecay2"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog2), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("loggroup1smalldecay3"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog3), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("loggroup1smalldecay4"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog4), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("loggroup1smalldecay5"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog5), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("ffmoss"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedFFMoss), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("fflitter"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedFFLitter), 0.001);
}

/////////////////////////////////////////////////////////////////////////////
// VerifyDetailedSubstrateRun1TS2Proportions()
/////////////////////////////////////////////////////////////////////////////
void VerifyDetailedSubstrateRun1TS2Proportions(clGrid *p_oSubstrateGrid) {
  float fExpectedTipup, fExpectedLog1, fExpectedLog2, fExpectedLog3,
  fExpectedLog4, fExpectedLog5, fExpectedScarSoil,
  fExpectedFFMoss, fExpectedFFLitter, fActual;
  int iX, iY;

  //Cell 1
  iX = 0; iY = 0;
  fExpectedLog1 = 0.0676676416183064;
  fExpectedLog2 = 0.258287116915232;
  fExpectedLog3 = 0.174045241466461;
  fExpectedLog4 = 0.0270670566473225;
  fExpectedLog5 = 0.123188931499807;
  fExpectedTipup = 0.0243116734434214;
  fExpectedScarSoil = 0;
  fExpectedFFMoss = 0.13017293536378;
  fExpectedFFLitter = 0.19525940304567;

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("scarsoil"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedScarSoil), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("tipup"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedTipup), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("loggroup1smalldecay1"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog1), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("loggroup1smalldecay2"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog2), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("loggroup1smalldecay3"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog3), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("loggroup1smalldecay4"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog4), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("loggroup1smalldecay5"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog5), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("ffmoss"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedFFMoss), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("fflitter"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedFFLitter), 0.001);

  //Cell 2
  iY = 1;
  fExpectedLog1 = 0.064708683143705;
  fExpectedLog2 = 0.286645124443337;
  fExpectedLog3 = 0.166434622418939;
  fExpectedLog4 = 0.025883473257482;
  fExpectedLog5 = 0.117802148036973;
  fExpectedTipup = 0.0273240571125062;
  fExpectedScarSoil = 0;
  fExpectedFFMoss = 0.124480756634823;
  fExpectedFFLitter = 0.186721134952235;

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("scarsoil"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedScarSoil), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("tipup"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedTipup), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("loggroup1smalldecay1"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog1), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("loggroup1smalldecay2"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog2), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("loggroup1smalldecay3"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog3), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("loggroup1smalldecay4"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog4), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("loggroup1smalldecay5"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog5), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("ffmoss"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedFFMoss), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("fflitter"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedFFLitter), 0.001);

  //Cell 3
  iY = 2;
  fExpectedLog1 = 0.147151776468577;
  fExpectedLog2 = 0.252848223531423;
  fExpectedLog3 = 0.150597105956101;
  fExpectedLog4 = 0.349402894043899;
  fExpectedLog5 = 0;
  fExpectedTipup = 0.0606530659712633;
  fExpectedScarSoil = 0;
  fExpectedFFMoss = 0.0157387736114947;
  fExpectedFFLitter = 0.023608160417242;

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("scarsoil"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedScarSoil), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("tipup"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedTipup), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("loggroup1smalldecay1"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog1), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("loggroup1smalldecay2"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog2), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("loggroup1smalldecay3"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog3), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("loggroup1smalldecay4"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog4), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("loggroup1smalldecay5"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog5), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("ffmoss"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedFFMoss), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("fflitter"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedFFLitter), 0.001);

  //Cell 4
  iY = 3;
  fExpectedLog1 = 0;
  fExpectedLog2 = 0;
  fExpectedLog3 = 0;
  fExpectedLog4 = 0;
  fExpectedLog5 = 0;
  fExpectedTipup = 0;
  fExpectedScarSoil = 0.606530659712633;
  fExpectedFFMoss = 0.157387736114947;
  fExpectedFFLitter = 0.23608160417242;

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("scarsoil"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedScarSoil), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("tipup"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedTipup), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("loggroup1largedecay1"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog1), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("loggroup1largedecay2"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog2), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("loggroup1largedecay3"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog3), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("loggroup1largedecay4"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog4), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("loggroup1largedecay5"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog5), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("ffmoss"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedFFMoss), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("fflitter"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedFFLitter), 0.001);

  //Cell 5
  iY = 4;
  fExpectedLog1 = 0.0459446945839262;
  fExpectedLog2 = 0.221558917723531;
  fExpectedLog3 = 0.109558796450915;
  fExpectedLog4 = 0.12412287776123;
  fExpectedLog5 = 0.0920078261982308;
  fExpectedTipup = 0.0711378886420719;
  fExpectedScarSoil = 0.110755367697417;
  fExpectedFFMoss = 0.0899654523770713;
  fExpectedFFLitter = 0.134948178565607;

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("scarsoil"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedScarSoil), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("tipup"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedTipup), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("loggroup1smalldecay1"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog1), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("loggroup1smalldecay2"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog2), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("loggroup1smalldecay3"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog3), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("loggroup1smalldecay4"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog4), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("loggroup1smalldecay5"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog5), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("ffmoss"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedFFMoss), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("fflitter"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedFFLitter), 0.001);
}

/////////////////////////////////////////////////////////////////////////////
// VerifyDetailedSubstrateRun1TS3Proportions()
/////////////////////////////////////////////////////////////////////////////
void VerifyDetailedSubstrateRun1TS3Proportions(clGrid *p_oSubstrateGrid) {
  float fExpectedTipup, fExpectedLog1, fExpectedLog2, fExpectedLog3,
  fExpectedLog4, fExpectedLog5, fExpectedScarSoil,
  fExpectedFFMoss, fExpectedFFLitter, fActual;
  int iX, iY;

  //Cell 1
  iX = 0; iY = 0;
  fExpectedLog1 = 0;
  fExpectedLog2 = 0.183723524306651;
  fExpectedLog3 = 0.194652653567447;
  fExpectedLog4 = 0.121623822125902;
  fExpectedLog5 = 0.0723857319259785;
  fExpectedTipup = 0;
  fExpectedScarSoil = 0;
  fExpectedFFMoss = 0.171045707229609;
  fExpectedFFLitter = 0.256568560844413;

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("scarsoil"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedScarSoil), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("tipup"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedTipup), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("loggroup1smalldecay1"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog1), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("loggroup1smalldecay2"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog2), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("loggroup1smalldecay3"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog3), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("loggroup1smalldecay4"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog4), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("loggroup1smalldecay5"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog5), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("ffmoss"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedFFMoss), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("fflitter"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedFFLitter), 0.001);

  //Cell 2
  iY = 1;
  fExpectedLog1 = 0;
  fExpectedLog2 = 0.234790632643971;
  fExpectedLog3 = 0.195097145726312;
  fExpectedLog4 = 0.109103130121872;
  fExpectedLog5 = 0.0649339067893435;
  fExpectedTipup = 0.0109778430080258;
  fExpectedScarSoil = 0;
  fExpectedFFMoss = 0.15403893668419;
  fExpectedFFLitter = 0.231058405026285;

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("scarsoil"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedScarSoil), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("tipup"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedTipup), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("loggroup1smalldecay1"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog1), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("loggroup1smalldecay2"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog2), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("loggroup1smalldecay3"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog3), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("loggroup1smalldecay4"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog4), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("loggroup1smalldecay5"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog5), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("ffmoss"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedFFMoss), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("fflitter"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedFFLitter), 0.001);

  //Cell 3
  iY = 2;
  fExpectedLog1 = 0.0541341132946451;
  fExpectedLog2 = 0.206629693532186;
  fExpectedLog3 = 0.156021359652572;
  fExpectedLog4 = 0.345735507306647;
  fExpectedLog5 = 0.13747932621395;
  fExpectedTipup = 0.0243116734434214;
  fExpectedScarSoil = 0;
  fExpectedFFMoss = 0.0302753306226315;
  fExpectedFFLitter = 0.0454129959339472;

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("scarsoil"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedScarSoil), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("tipup"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedTipup), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("loggroup1smalldecay1"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog1), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("loggroup1smalldecay2"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog2), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("loggroup1smalldecay3"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog3), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("loggroup1smalldecay4"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog4), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("loggroup1smalldecay5"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog5), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("ffmoss"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedFFMoss), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("fflitter"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedFFLitter), 0.001);

  //Cell 4
  iY = 3;
  fExpectedLog1 = 0;
  fExpectedLog2 = 0.25868049945062;
  fExpectedLog3 = 0;
  fExpectedLog4 = 0;
  fExpectedLog5 = 0;
  fExpectedTipup = 0.110446616727766;
  fExpectedScarSoil = 0.215421372907273;
  fExpectedFFMoss = 0.148061852211307;
  fExpectedFFLitter = 0.22209277831696;

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("scarsoil"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedScarSoil), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("tipup"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedTipup), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("loggroup1largedecay1"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog1), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("loggroup1largedecay2"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog2), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("loggroup1largedecay3"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog3), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("loggroup1largedecay4"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog4), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("loggroup1largedecay5"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog5), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("ffmoss"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedFFMoss), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("fflitter"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedFFLitter), 0.001);

  //Cell 5
  iY = 4;
  fExpectedLog1 = 0.0112615166553532;
  fExpectedLog2 = 0.196424559545526;
  fExpectedLog3 = 0.136514090769146;
  fExpectedLog4 = 0.121062282161521;
  fExpectedLog5 = 0.0974420634832544;
  fExpectedTipup = 0.0400178960969479;
  fExpectedScarSoil = 0.0612239521702712;
  fExpectedFFMoss = 0.134421455647192;
  fExpectedFFLitter = 0.201632183470788;

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("scarsoil"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedScarSoil), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("tipup"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedTipup), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("loggroup1smalldecay1"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog1), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("loggroup1smalldecay2"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog2), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("loggroup1smalldecay3"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog3), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("loggroup1smalldecay4"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog4), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("loggroup1smalldecay5"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog5), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("ffmoss"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedFFMoss), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("fflitter"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedFFLitter), 0.001);
}

/////////////////////////////////////////////////////////////////////////////
// VerifyDetailedSubstrateRun1TS4Proportions()
/////////////////////////////////////////////////////////////////////////////
void VerifyDetailedSubstrateRun1TS4Proportions(clGrid *p_oSubstrateGrid) {
  float fExpectedTipup, fExpectedLog1, fExpectedLog2, fExpectedLog3,
  fExpectedLog4, fExpectedLog5, fExpectedScarSoil,
  fExpectedFFMoss, fExpectedFFLitter, fActual;
  int iX, iY;

  //Cell 1
  iX = 0; iY = 0;
  fExpectedLog1 = 0;
  fExpectedLog2 = 0.0538799591961296;
  fExpectedLog3 = 0.178525546318714;
  fExpectedLog4 = 0.21973924943005;
  fExpectedLog5 = 0.0705665306757122;
  fExpectedTipup = 0;
  fExpectedScarSoil = 0;
  fExpectedFFMoss = 0.190915485751758;
  fExpectedFFLitter = 0.286373228627637;

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("scarsoil"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedScarSoil), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("tipup"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedTipup), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("loggroup1smalldecay1"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog1), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("loggroup1smalldecay2"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog2), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("loggroup1smalldecay3"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog3), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("loggroup1smalldecay4"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog4), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("loggroup1smalldecay5"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog5), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("ffmoss"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedFFMoss), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("fflitter"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedFFLitter), 0.001);

  //Cell 2
  iY = 1;
  fExpectedLog1 = 0;
  fExpectedLog2 = 0.079777594387975;
  fExpectedLog3 = 0.204852827274742;
  fExpectedLog4 = 0.211431750197099;
  fExpectedLog5 = 0.0633019851209041;
  fExpectedTipup = 0.00618141787438806;
  fExpectedScarSoil = 0;
  fExpectedFFMoss = 0.173781770057957;
  fExpectedFFLitter = 0.260672655086935;

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("scarsoil"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedScarSoil), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("tipup"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedTipup), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("loggroup1smalldecay1"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog1), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("loggroup1smalldecay2"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog2), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("loggroup1smalldecay3"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog3), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("loggroup1smalldecay4"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog4), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("loggroup1smalldecay5"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog5), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("ffmoss"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedFFMoss), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("fflitter"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedFFLitter), 0.001);

  //Cell 3
  iY = 2;
  fExpectedLog1 = 0;
  fExpectedLog2 = 0.146978819445321;
  fExpectedLog3 = 0.155722122853958;
  fExpectedLog4 = 0.242531807737476;
  fExpectedLog5 = 0.26786374144951;
  fExpectedTipup = 0;
  fExpectedScarSoil = 0;
  fExpectedFFMoss = 0.0747614034054941;
  fExpectedFFLitter = 0.112142105108241;

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("scarsoil"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedScarSoil), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("tipup"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedTipup), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("loggroup1smalldecay1"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog1), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("loggroup1smalldecay2"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog2), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("loggroup1smalldecay3"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog3), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("loggroup1smalldecay4"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog4), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("loggroup1smalldecay5"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog5), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("ffmoss"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedFFMoss), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("fflitter"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedFFLitter), 0.001);

  //Cell 4
  iY = 3;
  fExpectedLog1 = 0;
  fExpectedLog2 = 0.156897653986578;
  fExpectedLog3 = 0.101782845464042;
  fExpectedLog4 = 0;
  fExpectedLog5 = 0;
  fExpectedTipup = 0.0669892593069204;
  fExpectedScarSoil = 0;
  fExpectedFFMoss = 0.251613344342554;
  fExpectedFFLitter = 0.377420016513831;

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("scarsoil"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedScarSoil), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("tipup"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedTipup), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("loggroup1largedecay1"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog1), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("loggroup1largedecay2"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog2), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("loggroup1largedecay3"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog3), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("loggroup1largedecay4"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog4), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("loggroup1largedecay5"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog5), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("ffmoss"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedFFMoss), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("fflitter"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedFFLitter), 0.001);

  //Cell 5
  iY = 4;
  fExpectedLog1 = 0;
  fExpectedLog2 = 0.0872001756140189;
  fExpectedLog3 = 0.156487841991712;
  fExpectedLog4 = 0.153587467052012;
  fExpectedLog5 = 0.099038977305064;
  fExpectedTipup = 0.0107145736519851;
  fExpectedScarSoil = 0;
  fExpectedFFMoss = 0.197188385754083;
  fExpectedFFLitter = 0.295782578631125;

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("scarsoil"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedScarSoil), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("tipup"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedTipup), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("loggroup1smalldecay1"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog1), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("loggroup1smalldecay2"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog2), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("loggroup1smalldecay3"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog3), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("loggroup1smalldecay4"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog4), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("loggroup1smalldecay5"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog5), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("ffmoss"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedFFMoss), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("fflitter"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedFFLitter), 0.001);
}


/////////////////////////////////////////////////////////////////////////////
// VerifyDetailedSubstrateRun2TS1Proportions()
/////////////////////////////////////////////////////////////////////////////
void VerifyDetailedSubstrateRun2TS1Proportions(clGrid *p_oSubstrateGrid) {
  float fExpectedTipup, fExpectedLog1, fExpectedLog2, fExpectedLog3,
  fExpectedLog4, fExpectedLog5, fExpectedScarSoil,
  fExpectedFFMoss, fExpectedFFLitter, fActual;
  int iX, iY;

  //Cell 1
  iX = 0; iY = 0;

  //These are the same values as Cell 1, TS 2 in Run1
  fExpectedLog1 = 0.0676676416183064;
  fExpectedLog2 = 0.258287116915232;
  fExpectedLog3 = 0.174045241466461;
  fExpectedLog4 = 0.0270670566473225;
  fExpectedLog5 = 0.123188931499807;
  fExpectedTipup = 0.0243116734434214;
  fExpectedScarSoil = 0;
  fExpectedFFMoss = 0.13017293536378;
  fExpectedFFLitter = 0.19525940304567;

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("scarsoil"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedScarSoil), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("tipup"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedTipup), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("loggroup1smalldecay1"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog1), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("loggroup1smalldecay2"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog2), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("loggroup1smalldecay3"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog3), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("loggroup1smalldecay4"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog4), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("loggroup1smalldecay5"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedLog5), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("ffmoss"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedFFMoss), 0.001);

  p_oSubstrateGrid->GetValueOfCell(iX, iY, p_oSubstrateGrid->GetFloatDataCode("fflitter"), & fActual);
  EXPECT_LT(fabs(fActual - fExpectedFFLitter), 0.001);

}

/////////////////////////////////////////////////////////////////////////////
// WriteDetailedSubstrateXMLFile1()
/////////////////////////////////////////////////////////////////////////////
const char* WriteDetailedSubstrateXMLFile1(int iYearsPerTS)
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
      << "<yearsPerTimestep>" << iYearsPerTS << "</yearsPerTimestep>"
      << "<randomSeed>1</randomSeed>"
      << "<plot_lenX>8.0</plot_lenX>"
      << "<plot_lenY>40.0</plot_lenY>"
      << "<plot_latitude>55.37</plot_latitude>"
      << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
      << "<plot_temp_C>12</plot_temp_C>"
      << "</plot>"
      << "<trees>"
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
      << "</allometry>"
      << "<behaviorList>"
      << "<behavior>"
      << "<behaviorName>Harvest</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>1</listPosition>"
      << "</behavior>"
      //Have to have a mortality behavior so dead is registered
      << "<behavior>"
      << "<behaviorName>StochasticMortality</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>2</listPosition>"
      << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
      << "</behavior>"
      //Have to have a snag dynamics behavior to register
      //appropriate data members
      << "<behavior>"
      << "<behaviorName>SnagDecayClassDynamics</behaviorName>"
      << "<listPosition>3</listPosition>"
      << "<version>2.0</version>"
      << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>DetailedSubstrate</behaviorName>"
      << "<version>1.0</version>"
      << "<listPosition>4</listPosition>"
      << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
      << "</behavior>"
      //Let the dead remover get rid of the trees we kill
      << "<behavior>"
      << "<behaviorName>RemoveDead</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>5</listPosition>"
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
      << "<ha_applyToCell x=\"0\" y=\"2\" />"
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
      << "<ha_applyToCell x=\"0\" y=\"3\" />"
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
      << "<ha_applyToCell x=\"0\" y=\"4\" />"
      << "</ha_cutEvent>"
      << "</Harvest1>"
      << "<StochasticMortality2>"
      << "<mo_stochasticMortRate>"
      << "<mo_smrVal species=\"Species_1\">0.0</mo_smrVal>"
      << "</mo_stochasticMortRate>"
      << "</StochasticMortality2>"
      << "<SnagDecayClassDynamics3>"
      << "<sd_snagDecompTreefallAlpha>9999</sd_snagDecompTreefallAlpha>"
      << "<sd_snagDecompTreefallBeta>"
      << "<sd_sdtbVal species=\"Species_1\">0.000</sd_sdtbVal>"
      << "</sd_snagDecompTreefallBeta>"
      << "<sd_snagDecompTreefallDelta>0</sd_snagDecompTreefallDelta>"
      << "<sd_snagDecompTreefallTheta>0</sd_snagDecompTreefallTheta>"
      << "<sd_snagDecompTreefallIota>0</sd_snagDecompTreefallIota>"
      << "<sd_snagDecompTreefallLambda>0</sd_snagDecompTreefallLambda>"
      << "<sd_snagDecompSnagfallAlpha>0</sd_snagDecompSnagfallAlpha>"
      << "<sd_snagDecompSnagfallBeta>"
      << "<sd_sdsbVal species=\"Species_1\">0.000</sd_sdsbVal>"
      << "</sd_snagDecompSnagfallBeta>"
      << "<sd_snagDecompSnagfallGamma2>0</sd_snagDecompSnagfallGamma2>"
      << "<sd_snagDecompSnagfallGamma3>0</sd_snagDecompSnagfallGamma3>"
      << "<sd_snagDecompSnagfallGamma4>0</sd_snagDecompSnagfallGamma4>"
      << "<sd_snagDecompSnagfallGamma5>0</sd_snagDecompSnagfallGamma5>"
      << "<sd_snagDecompSnagfallZeta>0</sd_snagDecompSnagfallZeta>"
      << "<sd_snagDecompSnagfallEta>0</sd_snagDecompSnagfallEta>"
      << "<sd_snagDecompSnagfallKappa>0</sd_snagDecompSnagfallKappa>"
      << "<sd_snagDecompLiveTo1Prob>1</sd_snagDecompLiveTo1Prob>"
      << "<sd_snagDecompLiveTo2Prob>0</sd_snagDecompLiveTo2Prob>"
      << "<sd_snagDecompLiveTo3Prob>0</sd_snagDecompLiveTo3Prob>"
      << "<sd_snagDecompLiveTo4Prob>0</sd_snagDecompLiveTo4Prob>"
      << "<sd_snagDecompLiveTo5Prob>0</sd_snagDecompLiveTo5Prob>"
      << "<sd_snagDecomp1To1Prob>1</sd_snagDecomp1To1Prob>"
      << "<sd_snagDecomp1To2Prob>0</sd_snagDecomp1To2Prob>"
      << "<sd_snagDecomp1To3Prob>0</sd_snagDecomp1To3Prob>"
      << "<sd_snagDecomp1To4Prob>0</sd_snagDecomp1To4Prob>"
      << "<sd_snagDecomp1To5Prob>0</sd_snagDecomp1To5Prob>"
      << "<sd_snagDecomp2To2Prob>1</sd_snagDecomp2To2Prob>"
      << "<sd_snagDecomp2To3Prob>0</sd_snagDecomp2To3Prob>"
      << "<sd_snagDecomp2To4Prob>0</sd_snagDecomp2To4Prob>"
      << "<sd_snagDecomp2To5Prob>0</sd_snagDecomp2To5Prob>"
      << "<sd_snagDecomp3To3Prob>1</sd_snagDecomp3To3Prob>"
      << "<sd_snagDecomp3To4Prob>0</sd_snagDecomp3To4Prob>"
      << "<sd_snagDecomp3To5Prob>0</sd_snagDecomp3To5Prob>"
      << "<sd_snagDecomp4To4Prob>1</sd_snagDecomp4To4Prob>"
      << "<sd_snagDecomp4To5Prob>0</sd_snagDecomp4To5Prob>"
      << "<sd_snagDecomp5To5Prob>1</sd_snagDecomp5To5Prob>"
      << "<sd_minSnagBreakHeight>0.1</sd_minSnagBreakHeight>"
      << "<sd_maxSnagBreakHeight>0.1</sd_maxSnagBreakHeight>"
      << "</SnagDecayClassDynamics3>"
      << "<substrate>"
      << "<su_logSizeClassBoundary>40</su_logSizeClassBoundary>"
      << "<su_logSpGroupAssignment>"
      << "<su_lsgaVal species=\"Species_1\">1</su_lsgaVal>"
      << "</su_logSpGroupAssignment>"
      << "<su_propFallenTreesLogDecayClass1>0.0</su_propFallenTreesLogDecayClass1>"
      << "<su_propFallenTreesLogDecayClass2>1.0</su_propFallenTreesLogDecayClass2>"
      << "<su_propFallenTreesLogDecayClass3>0.0</su_propFallenTreesLogDecayClass3>"
      << "<su_propFallenTreesLogDecayClass4>0.0</su_propFallenTreesLogDecayClass4>"
      << "<su_propFallenTreesLogDecayClass5>0.0</su_propFallenTreesLogDecayClass5>"
      << "<su_propFallenSnagsLogDecayClass1>0.0</su_propFallenSnagsLogDecayClass1>"
      << "<su_propFallenSnagsLogDecayClass2>1.0</su_propFallenSnagsLogDecayClass2>"
      << "<su_propFallenSnagsLogDecayClass3>0.0</su_propFallenSnagsLogDecayClass3>"
      << "<su_propFallenSnagsLogDecayClass4>0.0</su_propFallenSnagsLogDecayClass4>"
      << "<su_propFallenSnagsLogDecayClass5>0.0</su_propFallenSnagsLogDecayClass5>"
      << "<su_logSpGroup1SmallDecayClass1DecayAlpha>-1</su_logSpGroup1SmallDecayClass1DecayAlpha>"
      << "<su_logSpGroup1SmallDecayClass2DecayAlpha>-0.8</su_logSpGroup1SmallDecayClass2DecayAlpha>"
      << "<su_logSpGroup1SmallDecayClass3DecayAlpha>-1.2</su_logSpGroup1SmallDecayClass3DecayAlpha>"
      << "<su_logSpGroup1SmallDecayClass4DecayAlpha>-0.5</su_logSpGroup1SmallDecayClass4DecayAlpha>"
      << "<su_logSpGroup1SmallDecayClass5DecayAlpha>-1</su_logSpGroup1SmallDecayClass5DecayAlpha>"
      << "<su_logSpGroup1LargeDecayClass1DecayAlpha>-1.2</su_logSpGroup1LargeDecayClass1DecayAlpha>"
      << "<su_logSpGroup1LargeDecayClass2DecayAlpha>-0.5</su_logSpGroup1LargeDecayClass2DecayAlpha>"
      << "<su_logSpGroup1LargeDecayClass3DecayAlpha>-1</su_logSpGroup1LargeDecayClass3DecayAlpha>"
      << "<su_logSpGroup1LargeDecayClass4DecayAlpha>-1</su_logSpGroup1LargeDecayClass4DecayAlpha>"
      << "<su_logSpGroup1LargeDecayClass5DecayAlpha>-0.8</su_logSpGroup1LargeDecayClass5DecayAlpha>"
      << "<su_logSpGroup1SmallDecayClass1DecayBeta>1</su_logSpGroup1SmallDecayClass1DecayBeta>"
      << "<su_logSpGroup1SmallDecayClass2DecayBeta>1</su_logSpGroup1SmallDecayClass2DecayBeta>"
      << "<su_logSpGroup1SmallDecayClass3DecayBeta>1.5</su_logSpGroup1SmallDecayClass3DecayBeta>"
      << "<su_logSpGroup1SmallDecayClass4DecayBeta>2</su_logSpGroup1SmallDecayClass4DecayBeta>"
      << "<su_logSpGroup1SmallDecayClass5DecayBeta>1</su_logSpGroup1SmallDecayClass5DecayBeta>"
      << "<su_logSpGroup1LargeDecayClass1DecayBeta>1.5</su_logSpGroup1LargeDecayClass1DecayBeta>"
      << "<su_logSpGroup1LargeDecayClass2DecayBeta>2</su_logSpGroup1LargeDecayClass2DecayBeta>"
      << "<su_logSpGroup1LargeDecayClass3DecayBeta>1</su_logSpGroup1LargeDecayClass3DecayBeta>"
      << "<su_logSpGroup1LargeDecayClass4DecayBeta>1</su_logSpGroup1LargeDecayClass4DecayBeta>"
      << "<su_logSpGroup1LargeDecayClass5DecayBeta>1</su_logSpGroup1LargeDecayClass5DecayBeta>"
      << "<su_initialLogSpGroup1SmallDecayClass1>0.5</su_initialLogSpGroup1SmallDecayClass1>"
      << "<su_initialLogSpGroup1SmallDecayClass2>0.0</su_initialLogSpGroup1SmallDecayClass2>"
      << "<su_initialLogSpGroup1SmallDecayClass3>0.0</su_initialLogSpGroup1SmallDecayClass3>"
      << "<su_initialLogSpGroup1SmallDecayClass4>0.2</su_initialLogSpGroup1SmallDecayClass4>"
      << "<su_initialLogSpGroup1SmallDecayClass5>0.0</su_initialLogSpGroup1SmallDecayClass5>"
      << "<su_initialLogSpGroup1LargeDecayClass1>0</su_initialLogSpGroup1LargeDecayClass1>"
      << "<su_initialLogSpGroup1LargeDecayClass2>0</su_initialLogSpGroup1LargeDecayClass2>"
      << "<su_initialLogSpGroup1LargeDecayClass3>0</su_initialLogSpGroup1LargeDecayClass3>"
      << "<su_initialLogSpGroup1LargeDecayClass4>0</su_initialLogSpGroup1LargeDecayClass4>"
      << "<su_initialLogSpGroup1LargeDecayClass5>0</su_initialLogSpGroup1LargeDecayClass5>"
      << "<su_initialScarSoil>0.0</su_initialScarSoil>"
      << "<su_initialTipup>0.1</su_initialTipup>"
      << "<su_partialCutLogSpGroup1SmallDecayClass1>0.1</su_partialCutLogSpGroup1SmallDecayClass1>"
      << "<su_partialCutLogSpGroup1SmallDecayClass2>0.1</su_partialCutLogSpGroup1SmallDecayClass2>"
      << "<su_partialCutLogSpGroup1SmallDecayClass3>0.1</su_partialCutLogSpGroup1SmallDecayClass3>"
      << "<su_partialCutLogSpGroup1SmallDecayClass4>0.1</su_partialCutLogSpGroup1SmallDecayClass4>"
      << "<su_partialCutLogSpGroup1SmallDecayClass5>0.1</su_partialCutLogSpGroup1SmallDecayClass5>"
      << "<su_partialCutLogSpGroup1LargeDecayClass1>0.0</su_partialCutLogSpGroup1LargeDecayClass1>"
      << "<su_partialCutLogSpGroup1LargeDecayClass2>0.0</su_partialCutLogSpGroup1LargeDecayClass2>"
      << "<su_partialCutLogSpGroup1LargeDecayClass3>0.0</su_partialCutLogSpGroup1LargeDecayClass3>"
      << "<su_partialCutLogSpGroup1LargeDecayClass4>0.0</su_partialCutLogSpGroup1LargeDecayClass4>"
      << "<su_partialCutLogSpGroup1LargeDecayClass5>0.0</su_partialCutLogSpGroup1LargeDecayClass5>"
      << "<su_partialCutScarSoil>0.2</su_partialCutScarSoil>"
      << "<su_partialCutTipup>0.1</su_partialCutTipup>"
      << "<su_gapCutLogSpGroup1SmallDecayClass1>0.4</su_gapCutLogSpGroup1SmallDecayClass1>"
      << "<su_gapCutLogSpGroup1SmallDecayClass2>0.0</su_gapCutLogSpGroup1SmallDecayClass2>"
      << "<su_gapCutLogSpGroup1SmallDecayClass3>0.5</su_gapCutLogSpGroup1SmallDecayClass3>"
      << "<su_gapCutLogSpGroup1SmallDecayClass4>0.0</su_gapCutLogSpGroup1SmallDecayClass4>"
      << "<su_gapCutLogSpGroup1SmallDecayClass5>0.0</su_gapCutLogSpGroup1SmallDecayClass5>"
      << "<su_gapCutLogSpGroup1LargeDecayClass1>0.0</su_gapCutLogSpGroup1LargeDecayClass1>"
      << "<su_gapCutLogSpGroup1LargeDecayClass2>0.0</su_gapCutLogSpGroup1LargeDecayClass2>"
      << "<su_gapCutLogSpGroup1LargeDecayClass3>0.0</su_gapCutLogSpGroup1LargeDecayClass3>"
      << "<su_gapCutLogSpGroup1LargeDecayClass4>0.0</su_gapCutLogSpGroup1LargeDecayClass4>"
      << "<su_gapCutLogSpGroup1LargeDecayClass5>0.0</su_gapCutLogSpGroup1LargeDecayClass5>"
      << "<su_gapCutScarSoil>0.0</su_gapCutScarSoil>"
      << "<su_gapCutTipup>0.1</su_gapCutTipup>"
      << "<su_clearCutLogSpGroup1SmallDecayClass1>0.0</su_clearCutLogSpGroup1SmallDecayClass1>"
      << "<su_clearCutLogSpGroup1SmallDecayClass2>0.0</su_clearCutLogSpGroup1SmallDecayClass2>"
      << "<su_clearCutLogSpGroup1SmallDecayClass3>0.0</su_clearCutLogSpGroup1SmallDecayClass3>"
      << "<su_clearCutLogSpGroup1SmallDecayClass4>0.0</su_clearCutLogSpGroup1SmallDecayClass4>"
      << "<su_clearCutLogSpGroup1SmallDecayClass5>0.0</su_clearCutLogSpGroup1SmallDecayClass5>"
      << "<su_clearCutLogSpGroup1LargeDecayClass1>0.0</su_clearCutLogSpGroup1LargeDecayClass1>"
      << "<su_clearCutLogSpGroup1LargeDecayClass2>0.0</su_clearCutLogSpGroup1LargeDecayClass2>"
      << "<su_clearCutLogSpGroup1LargeDecayClass3>0.0</su_clearCutLogSpGroup1LargeDecayClass3>"
      << "<su_clearCutLogSpGroup1LargeDecayClass4>0.0</su_clearCutLogSpGroup1LargeDecayClass4>"
      << "<su_clearCutLogSpGroup1LargeDecayClass5>0.0</su_clearCutLogSpGroup1LargeDecayClass5>"
      << "<su_clearCutScarSoil>1.0</su_clearCutScarSoil>"
      << "<su_clearCutTipup>0.0</su_clearCutTipup>"
      << "<su_scarSoilDecayAlpha>-0.5</su_scarSoilDecayAlpha>"
      << "<su_scarSoilDecayBeta>1</su_scarSoilDecayBeta>"
      << "<su_tipupDecayAlpha>-0.5</su_tipupDecayAlpha>"
      << "<su_tipupDecayBeta>1.5</su_tipupDecayBeta>"
      << "<su_maxNumberDecayYears>2</su_maxNumberDecayYears>"
      << "<su_propOfFallUproot>"
      << "<su_pofuVal species=\"Species_1\">1</su_pofuVal>"
      << "</su_propOfFallUproot>"
      << "<su_propOfSnagsUproot>"
      << "<su_posuVal species=\"Species_1\">0</su_posuVal>"
      << "</su_propOfSnagsUproot>"
      << "<su_rootTipupFactor>3</su_rootTipupFactor>"
      << "<su_mossProportion>0.4</su_mossProportion>"
      << "<su_directionalTreeFall>0</su_directionalTreeFall>"
      << "<su_initialSmallLogMeanDiameter>20</su_initialSmallLogMeanDiameter>"
      << "<su_initialLargeLogMeanDiameter>50</su_initialLargeLogMeanDiameter>"
      << "<su_partialCutSmallLogMeanDiameter>20</su_partialCutSmallLogMeanDiameter>"
      << "<su_partialCutLargeLogMeanDiameter>50</su_partialCutLargeLogMeanDiameter>"
      << "</substrate>"
      << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteDetailedSubstrateXMLFile2()
/////////////////////////////////////////////////////////////////////////////
const char* WriteDetailedSubstrateXMLFile2()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";
  int i,j,k,t,c;
  string sSizes[]  = {"", "small","large"};

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
      << "<plot_latitude>55.37</plot_latitude>"
      << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
      << "<plot_temp_C>12</plot_temp_C>"
      << "</plot>"
      << "<trees>"
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
      << "</allometry>"
      << "<grid gridName=\"DetailedSubstrate\">"
      << "<ma_floatCodes>"
      << "<ma_floatCode label=\"scarsoil\">0</ma_floatCode>"
      << "<ma_floatCode label=\"ffmoss\">1</ma_floatCode>"
      << "<ma_floatCode label=\"tipup\">2</ma_floatCode>"
      << "<ma_floatCode label=\"fflitter\">3</ma_floatCode>";
  c = 4;
  for (i = 1; i <= 3; i++) {
    for (j=1;j<=2;j++) {
      for (k=1;k<=5;k++) {
        oOut << "<ma_floatCode label=\"loggroup" << i << sSizes[j] << "decay" << k << "\">" << c << "</ma_floatCode>";
        c++;
        oOut << "<ma_floatCode label=\"vloggroup" << i << sSizes[j] << "decay" << k << "\">" << c << "</ma_floatCode>";
        c++;
      }
    }
  }

  oOut << "<ma_floatCode label=\"totallog\">64</ma_floatCode>"
      << "<ma_floatCode label=\"totallogvol\">65</ma_floatCode>"
      << "</ma_floatCodes>"
      << "<ma_lengthXCells>3</ma_lengthXCells>"
      << "<ma_lengthYCells>2</ma_lengthYCells>"
      << "</grid>"
      << "<grid gridName=\"detailedsubstratecalcs\">"
      << "<ma_floatCodes>"
      << "<ma_floatCode label=\"newtipup\">0</ma_floatCode>";

  c = 1;
  for (i = 1; i <= 3; i++) {
    for (j=1;j<=2;j++) {
      for (k=1;k<=5;k++) {
        oOut << "<ma_floatCode label=\"newloggroup" << i << sSizes[j] << "decay" << k << "\">" << (j+k-1) << "</ma_floatCode>";
        c++;
        for (t=0;t<=2;t++) {
          oOut << "<ma_floatCode label=\"loggroup" << i << sSizes[j] << "decay" << k << "_" << t << "\">" << (8+j+k+t) << "</ma_floatCode>";
          c++;
        }
      }
    }
  }

  oOut << "</ma_floatCodes>"
      << "<ma_lengthXCells>3</ma_lengthXCells>"
      << "<ma_lengthYCells>2</ma_lengthYCells>"
      << "<ma_v x=\"0\" y=\"0\">"
      << "<fl c=\"0\">0.1</fl>"
      << "</ma_v>"
      << "</grid>"
      << "<behaviorList>"
      << "<behavior>"
      << "<behaviorName>StochasticMortality</behaviorName>"
      << "<version>1.0</version>"
      << "<listPosition>1</listPosition>"
      << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>StochasticMortality</behaviorName>"
      << "<version>1.0</version>"
      << "<applyTo species=\"Species_1\" type=\"Snag\"/>"
      << "<listPosition>2</listPosition>"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>SnagDecayClassDynamics</behaviorName>"
      << "<version>2.0</version>"
      << "<listPosition>3</listPosition>"
      << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_1\" type=\"Snag\"/>"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>DetailedSubstrate</behaviorName>"
      << "<version>1.0</version>"
      << "<listPosition>4</listPosition>"
      << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_1\" type=\"Snag\"/>"
      << "</behavior>"
      //Let the dead remover get rid of the trees we kill
      << "<behavior>"
      << "<behaviorName>RemoveDead</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>5</listPosition>"
      << "<applyTo species=\"Species_1\" type=\"Adult\" />"
      << "<applyTo species=\"Species_1\" type=\"Snag\"/>"
      << "</behavior>"
      << "</behaviorList>"
      << "<StochasticMortality1>"
      << "<mo_stochasticMortRate>"
      << "<mo_smrVal species=\"Species_1\">1.0</mo_smrVal>"
      << "</mo_stochasticMortRate>"
      << "</StochasticMortality1>"
      << "<StochasticMortality2>"
      << "<mo_stochasticMortRate>"
      << "<mo_smrVal species=\"Species_1\">0.0</mo_smrVal>"
      << "</mo_stochasticMortRate>"
      << "</StochasticMortality2>"
      << "<SnagDecayClassDynamics3>"
      << "<sd_snagDecompTreefallAlpha>9999</sd_snagDecompTreefallAlpha>"
      << "<sd_snagDecompTreefallBeta>"
      << "<sd_sdtbVal species=\"Species_1\">0.000</sd_sdtbVal>"
      << "</sd_snagDecompTreefallBeta>"
      << "<sd_snagDecompTreefallDelta>0</sd_snagDecompTreefallDelta>"
      << "<sd_snagDecompTreefallTheta>0</sd_snagDecompTreefallTheta>"
      << "<sd_snagDecompTreefallIota>0</sd_snagDecompTreefallIota>"
      << "<sd_snagDecompTreefallLambda>0</sd_snagDecompTreefallLambda>"
      << "<sd_snagDecompSnagfallAlpha>0</sd_snagDecompSnagfallAlpha>"
      << "<sd_snagDecompSnagfallBeta>"
      << "<sd_sdsbVal species=\"Species_1\">0.000</sd_sdsbVal>"
      << "</sd_snagDecompSnagfallBeta>"
      << "<sd_snagDecompSnagfallGamma2>0</sd_snagDecompSnagfallGamma2>"
      << "<sd_snagDecompSnagfallGamma3>0</sd_snagDecompSnagfallGamma3>"
      << "<sd_snagDecompSnagfallGamma4>0</sd_snagDecompSnagfallGamma4>"
      << "<sd_snagDecompSnagfallGamma5>0</sd_snagDecompSnagfallGamma5>"
      << "<sd_snagDecompSnagfallZeta>0</sd_snagDecompSnagfallZeta>"
      << "<sd_snagDecompSnagfallEta>0</sd_snagDecompSnagfallEta>"
      << "<sd_snagDecompSnagfallKappa>0</sd_snagDecompSnagfallKappa>"
      << "<sd_snagDecompLiveTo1Prob>1</sd_snagDecompLiveTo1Prob>"
      << "<sd_snagDecompLiveTo2Prob>0</sd_snagDecompLiveTo2Prob>"
      << "<sd_snagDecompLiveTo3Prob>0</sd_snagDecompLiveTo3Prob>"
      << "<sd_snagDecompLiveTo4Prob>0</sd_snagDecompLiveTo4Prob>"
      << "<sd_snagDecompLiveTo5Prob>0</sd_snagDecompLiveTo5Prob>"
      << "<sd_snagDecomp1To1Prob>1</sd_snagDecomp1To1Prob>"
      << "<sd_snagDecomp1To2Prob>0</sd_snagDecomp1To2Prob>"
      << "<sd_snagDecomp1To3Prob>0</sd_snagDecomp1To3Prob>"
      << "<sd_snagDecomp1To4Prob>0</sd_snagDecomp1To4Prob>"
      << "<sd_snagDecomp1To5Prob>0</sd_snagDecomp1To5Prob>"
      << "<sd_snagDecomp2To2Prob>1</sd_snagDecomp2To2Prob>"
      << "<sd_snagDecomp2To3Prob>0</sd_snagDecomp2To3Prob>"
      << "<sd_snagDecomp2To4Prob>0</sd_snagDecomp2To4Prob>"
      << "<sd_snagDecomp2To5Prob>0</sd_snagDecomp2To5Prob>"
      << "<sd_snagDecomp3To3Prob>1</sd_snagDecomp3To3Prob>"
      << "<sd_snagDecomp3To4Prob>0</sd_snagDecomp3To4Prob>"
      << "<sd_snagDecomp3To5Prob>0</sd_snagDecomp3To5Prob>"
      << "<sd_snagDecomp4To4Prob>1</sd_snagDecomp4To4Prob>"
      << "<sd_snagDecomp4To5Prob>0</sd_snagDecomp4To5Prob>"
      << "<sd_snagDecomp5To5Prob>1</sd_snagDecomp5To5Prob>"
      << "<sd_minSnagBreakHeight>0.1</sd_minSnagBreakHeight>"
      << "<sd_maxSnagBreakHeight>0.1</sd_maxSnagBreakHeight>"
      << "</SnagDecayClassDynamics3>"
      << "<substrate>"
      << "<su_logSizeClassBoundary>40</su_logSizeClassBoundary>"
      << "<su_logSpGroupAssignment>"
      << "<su_lsgaVal species=\"Species_1\">1</su_lsgaVal>"
      << "</su_logSpGroupAssignment>"
      << "<su_propFallenTreesLogDecayClass1>0.0</su_propFallenTreesLogDecayClass1>"
      << "<su_propFallenTreesLogDecayClass2>1.0</su_propFallenTreesLogDecayClass2>"
      << "<su_propFallenTreesLogDecayClass3>0.0</su_propFallenTreesLogDecayClass3>"
      << "<su_propFallenTreesLogDecayClass4>0.0</su_propFallenTreesLogDecayClass4>"
      << "<su_propFallenTreesLogDecayClass5>0.0</su_propFallenTreesLogDecayClass5>"
      << "<su_propFallenSnagsLogDecayClass1>0.0</su_propFallenSnagsLogDecayClass1>"
      << "<su_propFallenSnagsLogDecayClass2>1.0</su_propFallenSnagsLogDecayClass2>"
      << "<su_propFallenSnagsLogDecayClass3>0.0</su_propFallenSnagsLogDecayClass3>"
      << "<su_propFallenSnagsLogDecayClass4>0.0</su_propFallenSnagsLogDecayClass4>"
      << "<su_propFallenSnagsLogDecayClass5>0.0</su_propFallenSnagsLogDecayClass5>"
      << "<su_logSpGroup1SmallDecayClass1DecayAlpha>-1</su_logSpGroup1SmallDecayClass1DecayAlpha>"
      << "<su_logSpGroup1SmallDecayClass2DecayAlpha>-0.8</su_logSpGroup1SmallDecayClass2DecayAlpha>"
      << "<su_logSpGroup1SmallDecayClass3DecayAlpha>-1.2</su_logSpGroup1SmallDecayClass3DecayAlpha>"
      << "<su_logSpGroup1SmallDecayClass4DecayAlpha>-0.5</su_logSpGroup1SmallDecayClass4DecayAlpha>"
      << "<su_logSpGroup1SmallDecayClass5DecayAlpha>-1</su_logSpGroup1SmallDecayClass5DecayAlpha>"
      << "<su_logSpGroup1LargeDecayClass1DecayAlpha>-1.2</su_logSpGroup1LargeDecayClass1DecayAlpha>"
      << "<su_logSpGroup1LargeDecayClass2DecayAlpha>-0.5</su_logSpGroup1LargeDecayClass2DecayAlpha>"
      << "<su_logSpGroup1LargeDecayClass3DecayAlpha>-1</su_logSpGroup1LargeDecayClass3DecayAlpha>"
      << "<su_logSpGroup1LargeDecayClass4DecayAlpha>-1</su_logSpGroup1LargeDecayClass4DecayAlpha>"
      << "<su_logSpGroup1LargeDecayClass5DecayAlpha>-0.8</su_logSpGroup1LargeDecayClass5DecayAlpha>"
      << "<su_logSpGroup1SmallDecayClass1DecayBeta>1</su_logSpGroup1SmallDecayClass1DecayBeta>"
      << "<su_logSpGroup1SmallDecayClass2DecayBeta>1</su_logSpGroup1SmallDecayClass2DecayBeta>"
      << "<su_logSpGroup1SmallDecayClass3DecayBeta>1.5</su_logSpGroup1SmallDecayClass3DecayBeta>"
      << "<su_logSpGroup1SmallDecayClass4DecayBeta>2</su_logSpGroup1SmallDecayClass4DecayBeta>"
      << "<su_logSpGroup1SmallDecayClass5DecayBeta>1</su_logSpGroup1SmallDecayClass5DecayBeta>"
      << "<su_logSpGroup1LargeDecayClass1DecayBeta>1.5</su_logSpGroup1LargeDecayClass1DecayBeta>"
      << "<su_logSpGroup1LargeDecayClass2DecayBeta>2</su_logSpGroup1LargeDecayClass2DecayBeta>"
      << "<su_logSpGroup1LargeDecayClass3DecayBeta>1</su_logSpGroup1LargeDecayClass3DecayBeta>"
      << "<su_logSpGroup1LargeDecayClass4DecayBeta>1</su_logSpGroup1LargeDecayClass4DecayBeta>"
      << "<su_logSpGroup1LargeDecayClass5DecayBeta>1</su_logSpGroup1LargeDecayClass5DecayBeta>"
      << "<su_initialLogSpGroup1SmallDecayClass1>0.0</su_initialLogSpGroup1SmallDecayClass1>"
      << "<su_initialLogSpGroup1SmallDecayClass2>0.0</su_initialLogSpGroup1SmallDecayClass2>"
      << "<su_initialLogSpGroup1SmallDecayClass3>0.0</su_initialLogSpGroup1SmallDecayClass3>"
      << "<su_initialLogSpGroup1SmallDecayClass4>0.0</su_initialLogSpGroup1SmallDecayClass4>"
      << "<su_initialLogSpGroup1SmallDecayClass5>0.0</su_initialLogSpGroup1SmallDecayClass5>"
      << "<su_initialLogSpGroup1LargeDecayClass1>0</su_initialLogSpGroup1LargeDecayClass1>"
      << "<su_initialLogSpGroup1LargeDecayClass2>0</su_initialLogSpGroup1LargeDecayClass2>"
      << "<su_initialLogSpGroup1LargeDecayClass3>0</su_initialLogSpGroup1LargeDecayClass3>"
      << "<su_initialLogSpGroup1LargeDecayClass4>0</su_initialLogSpGroup1LargeDecayClass4>"
      << "<su_initialLogSpGroup1LargeDecayClass5>0</su_initialLogSpGroup1LargeDecayClass5>"
      << "<su_initialScarSoil>0.0</su_initialScarSoil>"
      << "<su_initialTipup>0.0</su_initialTipup>"
      << "<su_scarSoilDecayAlpha>-0.5</su_scarSoilDecayAlpha>"
      << "<su_scarSoilDecayBeta>1</su_scarSoilDecayBeta>"
      << "<su_tipupDecayAlpha>-0.5</su_tipupDecayAlpha>"
      << "<su_tipupDecayBeta>1.5</su_tipupDecayBeta>"
      << "<su_maxNumberDecayYears>2</su_maxNumberDecayYears>"
      << "<su_propOfFallUproot>"
      << "<su_pofuVal species=\"Species_1\">1</su_pofuVal>"
      << "</su_propOfFallUproot>"
      << "<su_propOfSnagsUproot>"
      << "<su_posuVal species=\"Species_1\">1</su_posuVal>"
      << "</su_propOfSnagsUproot>"
      << "<su_rootTipupFactor>3</su_rootTipupFactor>"
      << "<su_mossProportion>0.4</su_mossProportion>"
      << "<su_directionalTreeFall>0</su_directionalTreeFall>"
      << "<su_initialSmallLogMeanDiameter>20</su_initialSmallLogMeanDiameter>"
      << "<su_initialLargeLogMeanDiameter>50</su_initialLargeLogMeanDiameter>"
      << "</substrate>"
      << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteDetailedSubstrateXMLFile3()
/////////////////////////////////////////////////////////////////////////////
const char* WriteDetailedSubstrateXMLFile3()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
      << "<paramFile fileCode=\"06010101\">"
      << "<plot>"
      << "<timesteps>2</timesteps>"
      << "<yearsPerTimestep>3</yearsPerTimestep>"
      << "<randomSeed>1</randomSeed>"
      << "<plot_lenX>270.0</plot_lenX>"
      << "<plot_lenY>270.0</plot_lenY>"
      << "<plot_latitude>55.37</plot_latitude>"
      << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
      << "<plot_temp_C>12</plot_temp_C>"
      << "</plot>"
      << "<trees>"
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
      << "<applyTo species=\"Species_1\" type=\"Snag\"/>"
      << "</behavior>"
      //Have to have a snag dynamics behavior to register
      //appropriate data members
      << "<behavior>"
      << "<behaviorName>SnagDecayClassDynamics</behaviorName>"
      << "<version>2.0</version>"
      << "<listPosition>2</listPosition>"
      << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_1\" type=\"Snag\"/>"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>DetailedSubstrate</behaviorName>"
      << "<version>1.0</version>"
      << "<listPosition>3</listPosition>"
      << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_1\" type=\"Snag\"/>"
      << "</behavior>"
      //Let the dead remover get rid of the trees we kill
      << "<behavior>"
      << "<behaviorName>RemoveDead</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>4</listPosition>"
      << "<applyTo species=\"Species_1\" type=\"Adult\" />"
      << "<applyTo species=\"Species_1\" type=\"Snag\"/>"
      << "</behavior>"
      << "</behaviorList>"
      << "<StochasticMortality1>"
      << "<mo_stochasticMortRate>"
      << "<mo_smrVal species=\"Species_1\">0.0</mo_smrVal>"
      << "</mo_stochasticMortRate>"
      << "</StochasticMortality1>"
      << "<SnagDecayClassDynamics2>"
      << "<sd_snagDecompTreefallAlpha>9999</sd_snagDecompTreefallAlpha>"
      << "<sd_snagDecompTreefallBeta>"
      << "<sd_sdtbVal species=\"Species_1\">0.000</sd_sdtbVal>"
      << "</sd_snagDecompTreefallBeta>"
      << "<sd_snagDecompTreefallDelta>0</sd_snagDecompTreefallDelta>"
      << "<sd_snagDecompTreefallTheta>0</sd_snagDecompTreefallTheta>"
      << "<sd_snagDecompTreefallIota>0</sd_snagDecompTreefallIota>"
      << "<sd_snagDecompTreefallLambda>0</sd_snagDecompTreefallLambda>"
      << "<sd_snagDecompSnagfallAlpha>0</sd_snagDecompSnagfallAlpha>"
      << "<sd_snagDecompSnagfallBeta>"
      << "<sd_sdsbVal species=\"Species_1\">0.000</sd_sdsbVal>"
      << "</sd_snagDecompSnagfallBeta>"
      << "<sd_snagDecompSnagfallGamma2>0</sd_snagDecompSnagfallGamma2>"
      << "<sd_snagDecompSnagfallGamma3>0</sd_snagDecompSnagfallGamma3>"
      << "<sd_snagDecompSnagfallGamma4>0</sd_snagDecompSnagfallGamma4>"
      << "<sd_snagDecompSnagfallGamma5>0</sd_snagDecompSnagfallGamma5>"
      << "<sd_snagDecompSnagfallZeta>0</sd_snagDecompSnagfallZeta>"
      << "<sd_snagDecompSnagfallEta>0</sd_snagDecompSnagfallEta>"
      << "<sd_snagDecompSnagfallKappa>0</sd_snagDecompSnagfallKappa>"
      << "<sd_snagDecompLiveTo1Prob>1</sd_snagDecompLiveTo1Prob>"
      << "<sd_snagDecompLiveTo2Prob>0</sd_snagDecompLiveTo2Prob>"
      << "<sd_snagDecompLiveTo3Prob>0</sd_snagDecompLiveTo3Prob>"
      << "<sd_snagDecompLiveTo4Prob>0</sd_snagDecompLiveTo4Prob>"
      << "<sd_snagDecompLiveTo5Prob>0</sd_snagDecompLiveTo5Prob>"
      << "<sd_snagDecomp1To1Prob>1</sd_snagDecomp1To1Prob>"
      << "<sd_snagDecomp1To2Prob>0</sd_snagDecomp1To2Prob>"
      << "<sd_snagDecomp1To3Prob>0</sd_snagDecomp1To3Prob>"
      << "<sd_snagDecomp1To4Prob>0</sd_snagDecomp1To4Prob>"
      << "<sd_snagDecomp1To5Prob>0</sd_snagDecomp1To5Prob>"
      << "<sd_snagDecomp2To2Prob>1</sd_snagDecomp2To2Prob>"
      << "<sd_snagDecomp2To3Prob>0</sd_snagDecomp2To3Prob>"
      << "<sd_snagDecomp2To4Prob>0</sd_snagDecomp2To4Prob>"
      << "<sd_snagDecomp2To5Prob>0</sd_snagDecomp2To5Prob>"
      << "<sd_snagDecomp3To3Prob>1</sd_snagDecomp3To3Prob>"
      << "<sd_snagDecomp3To4Prob>0</sd_snagDecomp3To4Prob>"
      << "<sd_snagDecomp3To5Prob>0</sd_snagDecomp3To5Prob>"
      << "<sd_snagDecomp4To4Prob>1</sd_snagDecomp4To4Prob>"
      << "<sd_snagDecomp4To5Prob>0</sd_snagDecomp4To5Prob>"
      << "<sd_snagDecomp5To5Prob>1</sd_snagDecomp5To5Prob>"
      << "<sd_minSnagBreakHeight>0.1</sd_minSnagBreakHeight>"
      << "<sd_maxSnagBreakHeight>0.1</sd_maxSnagBreakHeight>"
      << "</SnagDecayClassDynamics2>"
      << "<substrate>"
      << "<su_logSizeClassBoundary>40</su_logSizeClassBoundary>"
      << "<su_logSpGroupAssignment>"
      << "<su_lsgaVal species=\"Species_1\">1</su_lsgaVal>"
      << "</su_logSpGroupAssignment>"
      << "<su_propFallenTreesLogDecayClass1>0.0</su_propFallenTreesLogDecayClass1>"
      << "<su_propFallenTreesLogDecayClass2>1.0</su_propFallenTreesLogDecayClass2>"
      << "<su_propFallenTreesLogDecayClass3>0.0</su_propFallenTreesLogDecayClass3>"
      << "<su_propFallenTreesLogDecayClass4>0.0</su_propFallenTreesLogDecayClass4>"
      << "<su_propFallenTreesLogDecayClass5>0.0</su_propFallenTreesLogDecayClass5>"
      << "<su_propFallenSnagsLogDecayClass1>0.0</su_propFallenSnagsLogDecayClass1>"
      << "<su_propFallenSnagsLogDecayClass2>1.0</su_propFallenSnagsLogDecayClass2>"
      << "<su_propFallenSnagsLogDecayClass3>0.0</su_propFallenSnagsLogDecayClass3>"
      << "<su_propFallenSnagsLogDecayClass4>0.0</su_propFallenSnagsLogDecayClass4>"
      << "<su_propFallenSnagsLogDecayClass5>0.0</su_propFallenSnagsLogDecayClass5>"
      << "<su_logSpGroup1SmallDecayClass1DecayAlpha>-1</su_logSpGroup1SmallDecayClass1DecayAlpha>"
      << "<su_logSpGroup1SmallDecayClass2DecayAlpha>-0.8</su_logSpGroup1SmallDecayClass2DecayAlpha>"
      << "<su_logSpGroup1SmallDecayClass3DecayAlpha>-1.2</su_logSpGroup1SmallDecayClass3DecayAlpha>"
      << "<su_logSpGroup1SmallDecayClass4DecayAlpha>-0.5</su_logSpGroup1SmallDecayClass4DecayAlpha>"
      << "<su_logSpGroup1SmallDecayClass5DecayAlpha>-1</su_logSpGroup1SmallDecayClass5DecayAlpha>"
      << "<su_logSpGroup1LargeDecayClass1DecayAlpha>-1.2</su_logSpGroup1LargeDecayClass1DecayAlpha>"
      << "<su_logSpGroup1LargeDecayClass2DecayAlpha>-0.5</su_logSpGroup1LargeDecayClass2DecayAlpha>"
      << "<su_logSpGroup1LargeDecayClass3DecayAlpha>-1</su_logSpGroup1LargeDecayClass3DecayAlpha>"
      << "<su_logSpGroup1LargeDecayClass4DecayAlpha>-1</su_logSpGroup1LargeDecayClass4DecayAlpha>"
      << "<su_logSpGroup1LargeDecayClass5DecayAlpha>-0.8</su_logSpGroup1LargeDecayClass5DecayAlpha>"
      << "<su_logSpGroup1SmallDecayClass1DecayBeta>1</su_logSpGroup1SmallDecayClass1DecayBeta>"
      << "<su_logSpGroup1SmallDecayClass2DecayBeta>1</su_logSpGroup1SmallDecayClass2DecayBeta>"
      << "<su_logSpGroup1SmallDecayClass3DecayBeta>1.5</su_logSpGroup1SmallDecayClass3DecayBeta>"
      << "<su_logSpGroup1SmallDecayClass4DecayBeta>2</su_logSpGroup1SmallDecayClass4DecayBeta>"
      << "<su_logSpGroup1SmallDecayClass5DecayBeta>1</su_logSpGroup1SmallDecayClass5DecayBeta>"
      << "<su_logSpGroup1LargeDecayClass1DecayBeta>1.5</su_logSpGroup1LargeDecayClass1DecayBeta>"
      << "<su_logSpGroup1LargeDecayClass2DecayBeta>2</su_logSpGroup1LargeDecayClass2DecayBeta>"
      << "<su_logSpGroup1LargeDecayClass3DecayBeta>1</su_logSpGroup1LargeDecayClass3DecayBeta>"
      << "<su_logSpGroup1LargeDecayClass4DecayBeta>1</su_logSpGroup1LargeDecayClass4DecayBeta>"
      << "<su_logSpGroup1LargeDecayClass5DecayBeta>1</su_logSpGroup1LargeDecayClass5DecayBeta>"
      << "<su_initialLogSpGroup1SmallDecayClass1>0.0</su_initialLogSpGroup1SmallDecayClass1>"
      << "<su_initialLogSpGroup1SmallDecayClass2>0.0</su_initialLogSpGroup1SmallDecayClass2>"
      << "<su_initialLogSpGroup1SmallDecayClass3>0.0</su_initialLogSpGroup1SmallDecayClass3>"
      << "<su_initialLogSpGroup1SmallDecayClass4>0.0</su_initialLogSpGroup1SmallDecayClass4>"
      << "<su_initialLogSpGroup1SmallDecayClass5>0.0</su_initialLogSpGroup1SmallDecayClass5>"
      << "<su_initialLogSpGroup1LargeDecayClass1>0</su_initialLogSpGroup1LargeDecayClass1>"
      << "<su_initialLogSpGroup1LargeDecayClass2>0</su_initialLogSpGroup1LargeDecayClass2>"
      << "<su_initialLogSpGroup1LargeDecayClass3>0</su_initialLogSpGroup1LargeDecayClass3>"
      << "<su_initialLogSpGroup1LargeDecayClass4>0</su_initialLogSpGroup1LargeDecayClass4>"
      << "<su_initialLogSpGroup1LargeDecayClass5>0</su_initialLogSpGroup1LargeDecayClass5>"
      << "<su_initialScarSoil>0.0</su_initialScarSoil>"
      << "<su_initialTipup>0.0</su_initialTipup>"
      << "<su_scarSoilDecayAlpha>-0.5</su_scarSoilDecayAlpha>"
      << "<su_scarSoilDecayBeta>1</su_scarSoilDecayBeta>"
      << "<su_tipupDecayAlpha>-0.5</su_tipupDecayAlpha>"
      << "<su_tipupDecayBeta>1.5</su_tipupDecayBeta>"
      << "<su_maxNumberDecayYears>2</su_maxNumberDecayYears>"
      << "<su_propOfFallUproot>"
      << "<su_pofuVal species=\"Species_1\">1</su_pofuVal>"
      << "</su_propOfFallUproot>"
      << "<su_propOfSnagsUproot>"
      << "<su_posuVal species=\"Species_1\">1</su_posuVal>"
      << "</su_propOfSnagsUproot>"
      << "<su_rootTipupFactor>3</su_rootTipupFactor>"
      << "<su_mossProportion>0.4</su_mossProportion>"
      << "<su_directionalTreeFall>0</su_directionalTreeFall>"
      << "<su_initialSmallLogMeanDiameter>20</su_initialSmallLogMeanDiameter>"
      << "<su_initialLargeLogMeanDiameter>50</su_initialLargeLogMeanDiameter>"
      << "</substrate>"
      << "</paramFile>";

  oOut.close();

  return cFileString;
}


