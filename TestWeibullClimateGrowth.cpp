//---------------------------------------------------------------------------
// TestWeibullClimateGrowth.cpp
//---------------------------------------------------------------------------
#include "TestWeibullClimateGrowth.h"
#include <gtest/gtest.h>
#include <fstream>
#include <math.h>
#include "TreePopulation.h"
#include "SimManager.h"
#include "BehaviorBase.h"
#include "NCIEffectsList.h"

using namespace std;

////////////////////////////////////////////////////////////////////////////
// TestRun1()
// Performs a test run of growth. WriteWeibullClimateGrowthXMLFile1() performs setup for a
// 1-year timestep. There are 9 target trees whose values will be tested
// according to the testing spreadsheet prepared.
////////////////////////////////////////////////////////////////////////////
TEST(WeibullClimateGrowth, TestRun1) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    clTreePopulation * p_oPop;
    clTree *p_oTargetTree1, *p_oTargetTree2, *p_oTargetTree3, *p_oTargetTree4,
    *p_oTargetTree5, *p_oTargetTree6, *p_oTargetTree7, *p_oTargetTree8,
    *p_oTargetTree9, *p_oTargetTree;
    float fDiam, fExpectedDiam, fGrowth, fExpectedGrowth;
    int iSpecies;

    //Load our test file and get our tree population pointers
    p_oSimManager->ReadFile(WriteWeibullClimateGrowthXMLFile1());
    p_oPop = (clTreePopulation *) p_oSimManager->GetPopulationObject(
        "treepopulation");

    //Create our trees
    fDiam = 11;
    iSpecies = 1;
    p_oTargetTree1 = p_oPop->CreateTree(10, 10, iSpecies,
        clTreePopulation::adult, fDiam);

    fDiam = 10.5;
    iSpecies = 1;
    p_oTargetTree2 = p_oPop->CreateTree(50, 50, iSpecies,
        clTreePopulation::adult, fDiam);

    fDiam = 15;
    iSpecies = 2;
    p_oTargetTree3 = p_oPop->CreateTree(53, 52, iSpecies,
        clTreePopulation::adult, fDiam);

    fDiam = 25;
    iSpecies = 3;
    p_oTargetTree4 = p_oPop->CreateTree(59, 50, iSpecies,
        clTreePopulation::adult, fDiam);

    fDiam = 30;
    iSpecies = 1;
    p_oTargetTree5 = p_oPop->CreateTree(50, 59, iSpecies,
        clTreePopulation::adult, fDiam);

    fDiam = 45;
    iSpecies = 2;
    p_oTargetTree6 = p_oPop->CreateTree(55, 55, iSpecies,
        clTreePopulation::adult, fDiam);

    fDiam = 15;
    iSpecies = 3;
    p_oTargetTree7 = p_oPop->CreateTree(60, 61, iSpecies,
        clTreePopulation::adult, fDiam);

    fDiam = 4;
    iSpecies = 1;
    p_oTargetTree8 = p_oPop->CreateTree(52, 52, iSpecies,
        clTreePopulation::sapling, fDiam);

    fDiam = 4;
    iSpecies = 2;
    p_oTargetTree9 = p_oPop->CreateTree(53, 53, iSpecies,
        clTreePopulation::sapling, fDiam);

    //Now create all the neighbors that are too small or dead to compete
    p_oPop->CreateTree(56, 56, 0, clTreePopulation::snag, 30);
    p_oPop->CreateTree(56, 56, 0, clTreePopulation::seedling, 0.2);
    p_oTargetTree = p_oPop->CreateTree(54, 54, 1, clTreePopulation::adult, 20);
    p_oTargetTree->SetValue(p_oPop->GetIntDataCode("dead",
        p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), disease);

    //Now do the run
    p_oSimManager->RunSim(1);

    //Check the diameters and growth of the target trees
    fExpectedDiam = 11.08373955;
    fExpectedGrowth = 0.418697729;
    p_oTargetTree = p_oTargetTree1;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    p_oTargetTree->GetValue(p_oPop->GetFloatDataCode("Growth",
        p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fGrowth);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);
    EXPECT_LT(fabs(fGrowth - fExpectedGrowth)/fGrowth, 0.001);

    fExpectedDiam = 10.51201261;
    fExpectedGrowth = 0.060063058;
    p_oTargetTree = p_oTargetTree2;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    p_oTargetTree->GetValue(p_oPop->GetFloatDataCode("Growth",
        p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fGrowth);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);
    EXPECT_LT(fabs(fGrowth - fExpectedGrowth)/fGrowth, 0.001);

    fExpectedDiam = 20.0912634;
    fExpectedGrowth = 25.45631698;
    p_oTargetTree = p_oTargetTree3;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    p_oTargetTree->GetValue(p_oPop->GetFloatDataCode("Growth",
        p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fGrowth);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);
    EXPECT_LT(fabs(fGrowth - fExpectedGrowth)/fGrowth, 0.001);

    fExpectedDiam = 25.37568211;
    fExpectedGrowth = 1.878410547;
    p_oTargetTree = p_oTargetTree4;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    p_oTargetTree->GetValue(p_oPop->GetFloatDataCode("Growth",
        p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fGrowth);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);
    EXPECT_LT(fabs(fGrowth - fExpectedGrowth), 0.001);

    fExpectedDiam = 30.08664016;
    fExpectedGrowth = 0.433200788;
    p_oTargetTree = p_oTargetTree5;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    p_oTargetTree->GetValue(p_oPop->GetFloatDataCode("Growth",
        p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fGrowth);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);
    EXPECT_LT(fabs(fGrowth - fExpectedGrowth)/fGrowth, 0.001);

    fExpectedDiam = 48.11810814;
    fExpectedGrowth = 15.59054069;
    p_oTargetTree = p_oTargetTree6;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    p_oTargetTree->GetValue(p_oPop->GetFloatDataCode("Growth",
        p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fGrowth);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);
    EXPECT_LT(fabs(fGrowth - fExpectedGrowth)/fGrowth, 0.001);

    fExpectedDiam = 15.23503434;
    fExpectedGrowth = 1.17517172;
    p_oTargetTree = p_oTargetTree7;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    p_oTargetTree->GetValue(p_oPop->GetFloatDataCode("Growth",
        p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fGrowth);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);
    EXPECT_LT(fabs(fGrowth - fExpectedGrowth), 0.001);

    fExpectedDiam = 4.03513154;
    fExpectedGrowth = 0.219352775;
    p_oTargetTree = p_oTargetTree8;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    p_oTargetTree->GetValue(p_oPop->GetFloatDataCode("Growth",
        p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fGrowth);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);
    EXPECT_LT(fabs(fGrowth - fExpectedGrowth)/fGrowth, 0.001);

    fExpectedDiam = 4.24614164;
    fExpectedGrowth = 1.536848403;
    p_oTargetTree = p_oTargetTree9;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    p_oTargetTree->GetValue(p_oPop->GetFloatDataCode("Growth",
        p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fGrowth);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);
    EXPECT_LT(fabs(fGrowth - fExpectedGrowth)/fGrowth, 0.001);
    delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

////////////////////////////////////////////////////////////////////////////
// TestRun2()
// Performs a test run of growth. WriteWeibullClimateGrowthXMLFile2() performs setup for a
// 3-year timestep. There are 9 target trees whose values will be tested
// according to the testing spreadsheet prepared.
////////////////////////////////////////////////////////////////////////////
TEST(WeibullClimateGrowth, TestRun2) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    clTreePopulation * p_oPop;
    clTree *p_oTargetTree1, *p_oTargetTree2, *p_oTargetTree3, *p_oTargetTree4,
    *p_oTargetTree5, *p_oTargetTree6, *p_oTargetTree7, *p_oTargetTree8,
    *p_oTargetTree9, *p_oTargetTree;
    float fDiam, fExpectedDiam, fGrowth, fExpectedGrowth;
    int iSpecies;

    //Load our test file and get our tree population pointers
    p_oSimManager->ReadFile(WriteWeibullClimateGrowthXMLFile2());
    p_oPop = (clTreePopulation *) p_oSimManager->GetPopulationObject(
        "treepopulation");

    //Create our trees
    fDiam = 11;
    iSpecies = 1;
    p_oTargetTree1 = p_oPop->CreateTree(10, 10, iSpecies,
        clTreePopulation::adult, fDiam);

    fDiam = 10.5;
    iSpecies = 1;
    p_oTargetTree2 = p_oPop->CreateTree(50, 50, iSpecies,
        clTreePopulation::adult, fDiam);

    fDiam = 15;
    iSpecies = 2;
    p_oTargetTree3 = p_oPop->CreateTree(53, 52, iSpecies,
        clTreePopulation::adult, fDiam);

    fDiam = 25;
    iSpecies = 3;
    p_oTargetTree4 = p_oPop->CreateTree(59, 50, iSpecies,
        clTreePopulation::adult, fDiam);

    fDiam = 30;
    iSpecies = 1;
    p_oTargetTree5 = p_oPop->CreateTree(50, 59, iSpecies,
        clTreePopulation::adult, fDiam);

    fDiam = 45;
    iSpecies = 2;
    p_oTargetTree6 = p_oPop->CreateTree(55, 55, iSpecies,
        clTreePopulation::adult, fDiam);

    fDiam = 15;
    iSpecies = 3;
    p_oTargetTree7 = p_oPop->CreateTree(60, 61, iSpecies,
        clTreePopulation::adult, fDiam);

    fDiam = 4;
    iSpecies = 1;
    p_oTargetTree8 = p_oPop->CreateTree(52, 52, iSpecies,
        clTreePopulation::sapling, fDiam);

    fDiam = 4;
    iSpecies = 2;
    p_oTargetTree9 = p_oPop->CreateTree(53, 53, iSpecies,
        clTreePopulation::sapling, fDiam);

    //Now create all the neighbors that are too small or dead to compete
    p_oPop->CreateTree(56, 56, 0, clTreePopulation::snag, 30);
    p_oPop->CreateTree(56, 56, 0, clTreePopulation::seedling, 0.2);
    p_oTargetTree = p_oPop->CreateTree(54, 54, 1, clTreePopulation::adult, 20);
    p_oTargetTree->SetValue(p_oPop->GetIntDataCode("dead",
        p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), disease);

    //Now do the run
    p_oSimManager->RunSim(1);

    //Check the diameters and growth of the target trees
    fExpectedDiam = 11.25159786;
    fExpectedGrowth = 0.419329775;
    p_oTargetTree = p_oTargetTree1;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    p_oTargetTree->GetValue(p_oPop->GetFloatDataCode("Growth",
        p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fGrowth);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);
    EXPECT_LT(fabs(fGrowth - fExpectedGrowth)/fGrowth, 0.001);

    fExpectedDiam = 10.53614256;
    fExpectedGrowth = 0.060237607;
    p_oTargetTree = p_oTargetTree2;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    p_oTargetTree->GetValue(p_oPop->GetFloatDataCode("Growth",
        p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fGrowth);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);
    EXPECT_LT(fabs(fGrowth - fExpectedGrowth)/fGrowth, 0.001);

    fExpectedDiam = 30.11101459;
    fExpectedGrowth = 25.18502432;
    p_oTargetTree = p_oTargetTree3;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    p_oTargetTree->GetValue(p_oPop->GetFloatDataCode("Growth",
        p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fGrowth);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);
    EXPECT_LT(fabs(fGrowth - fExpectedGrowth)/fGrowth, 0.001);

    fExpectedDiam = 26.12030572;
    fExpectedGrowth = 1.867176201;
    p_oTargetTree = p_oTargetTree4;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    p_oTargetTree->GetValue(p_oPop->GetFloatDataCode("Growth",
        p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fGrowth);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);
    EXPECT_LT(fabs(fGrowth - fExpectedGrowth), 0.001);

    fExpectedDiam = 30.26014701;
    fExpectedGrowth = 0.433578346;
    p_oTargetTree = p_oTargetTree5;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    p_oTargetTree->GetValue(p_oPop->GetFloatDataCode("Growth",
        p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fGrowth);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);
    EXPECT_LT(fabs(fGrowth - fExpectedGrowth)/fGrowth, 0.001);

    fExpectedDiam = 53.68619667;
    fExpectedGrowth = 14.47699446;
    p_oTargetTree = p_oTargetTree6;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    p_oTargetTree->GetValue(p_oPop->GetFloatDataCode("Growth",
        p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fGrowth);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);
    EXPECT_LT(fabs(fGrowth - fExpectedGrowth)/fGrowth, 0.001);

    fExpectedDiam = 15.69994406;
    fExpectedGrowth = 1.166573431;
    p_oTargetTree = p_oTargetTree7;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    p_oTargetTree->GetValue(p_oPop->GetFloatDataCode("Growth",
        p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fGrowth);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);
    EXPECT_LT(fabs(fGrowth - fExpectedGrowth), 0.001);

    fExpectedDiam = 4.105681673;
    fExpectedGrowth = 0.219950202;
    p_oTargetTree = p_oTargetTree8;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    p_oTargetTree->GetValue(p_oPop->GetFloatDataCode("Growth",
        p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fGrowth);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);
    EXPECT_LT(fabs(fGrowth - fExpectedGrowth)/fGrowth, 0.001);

    fExpectedDiam = 4.78060567;
    fExpectedGrowth = 1.624637176;
    p_oTargetTree = p_oTargetTree9;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    p_oTargetTree->GetValue(p_oPop->GetFloatDataCode("Growth",
        p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fGrowth);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);
    EXPECT_LT(fabs(fGrowth - fExpectedGrowth)/fGrowth, 0.001);
    delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

////////////////////////////////////////////////////////////////////////////
// TestRun3()
// Performs a test run of growth. WriteWeibullClimateGrowthXMLFile3() performs
// setup for a 1-year timestep. There are 9 target trees whose values will be
// tested according to the testing spreadsheet prepared.
////////////////////////////////////////////////////////////////////////////
TEST(WeibullClimateGrowth, TestRun3) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    clTreePopulation * p_oPop;
    clTree *p_oTargetTree1, *p_oTargetTree2, *p_oTargetTree3, *p_oTargetTree4,
    *p_oTargetTree5, *p_oTargetTree6, *p_oTargetTree7, *p_oTargetTree8,
    *p_oTargetTree9, *p_oTargetTree;
    float fDiam, fExpectedDiam, fGrowth, fExpectedGrowth;
    int iSpecies;

    //Load our test file and get our tree population pointers
    p_oSimManager->ReadFile(WriteWeibullClimateGrowthXMLFile3());
    p_oPop = (clTreePopulation *) p_oSimManager->GetPopulationObject(
        "treepopulation");

    //Create our trees
    fDiam = 11;
    iSpecies = 1;
    p_oTargetTree1 = p_oPop->CreateTree(10, 10, iSpecies,
        clTreePopulation::adult, fDiam);

    fDiam = 10.5;
    iSpecies = 1;
    p_oTargetTree2 = p_oPop->CreateTree(50, 50, iSpecies,
        clTreePopulation::adult, fDiam);

    fDiam = 15;
    iSpecies = 2;
    p_oTargetTree3 = p_oPop->CreateTree(53, 52, iSpecies,
        clTreePopulation::adult, fDiam);

    fDiam = 25;
    iSpecies = 3;
    p_oTargetTree4 = p_oPop->CreateTree(59, 50, iSpecies,
        clTreePopulation::adult, fDiam);

    fDiam = 30;
    iSpecies = 1;
    p_oTargetTree5 = p_oPop->CreateTree(50, 59, iSpecies,
        clTreePopulation::adult, fDiam);

    fDiam = 45;
    iSpecies = 2;
    p_oTargetTree6 = p_oPop->CreateTree(55, 55, iSpecies,
        clTreePopulation::adult, fDiam);

    fDiam = 15;
    iSpecies = 3;
    p_oTargetTree7 = p_oPop->CreateTree(60, 61, iSpecies,
        clTreePopulation::adult, fDiam);

    fDiam = 4;
    iSpecies = 1;
    p_oTargetTree8 = p_oPop->CreateTree(52, 52, iSpecies,
        clTreePopulation::sapling, fDiam);

    fDiam = 4;
    iSpecies = 2;
    p_oTargetTree9 = p_oPop->CreateTree(53, 53, iSpecies,
        clTreePopulation::sapling, fDiam);

    //Now create all the neighbors that are too small or dead to compete
    p_oPop->CreateTree(56, 56, 0, clTreePopulation::snag, 30);
    p_oPop->CreateTree(56, 56, 0, clTreePopulation::seedling, 0.2);
    p_oTargetTree = p_oPop->CreateTree(54, 54, 1, clTreePopulation::adult, 20);
    p_oTargetTree->SetValue(p_oPop->GetIntDataCode("dead",
        p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), disease);

    //Now do the run
    p_oSimManager->RunSim(1);

    //Check the diameters and growth of the target trees
    fExpectedDiam = 11.14960547;
    fExpectedGrowth = 0.748027333;
    p_oTargetTree = p_oTargetTree1;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    p_oTargetTree->GetValue(p_oPop->GetFloatDataCode("Growth",
        p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fGrowth);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);
    EXPECT_LT(fabs(fGrowth - fExpectedGrowth)/fGrowth, 0.001);

    fExpectedDiam = 10.52146121;
    fExpectedGrowth = 0.107306073;
    p_oTargetTree = p_oTargetTree2;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    p_oTargetTree->GetValue(p_oPop->GetFloatDataCode("Growth",
        p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fGrowth);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);
    EXPECT_LT(fabs(fGrowth - fExpectedGrowth)/fGrowth, 0.001);

    fExpectedDiam = 23.74713846;
    fExpectedGrowth = 43.73569228;
    p_oTargetTree = p_oTargetTree3;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    p_oTargetTree->GetValue(p_oPop->GetFloatDataCode("Growth",
        p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fGrowth);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);
    EXPECT_LT(fabs(fGrowth - fExpectedGrowth)/fGrowth, 0.001);

    fExpectedDiam = 25.29082338;
    fExpectedGrowth = 1.454116891;
    p_oTargetTree = p_oTargetTree4;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    p_oTargetTree->GetValue(p_oPop->GetFloatDataCode("Growth",
        p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fGrowth);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);
    EXPECT_LT(fabs(fGrowth - fExpectedGrowth), 0.001);

    fExpectedDiam = 30.15478757;
    fExpectedGrowth = 0.773937873;
    p_oTargetTree = p_oTargetTree5;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    p_oTargetTree->GetValue(p_oPop->GetFloatDataCode("Growth",
        p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fGrowth);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);
    EXPECT_LT(fabs(fGrowth - fExpectedGrowth)/fGrowth, 0.001);

    fExpectedDiam = 50.35712288;
    fExpectedGrowth = 26.78561438;
    p_oTargetTree = p_oTargetTree6;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    p_oTargetTree->GetValue(p_oPop->GetFloatDataCode("Growth",
        p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fGrowth);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);
    EXPECT_LT(fabs(fGrowth - fExpectedGrowth)/fGrowth, 0.001);

    fExpectedDiam = 15.181945;
    fExpectedGrowth = 0.909725007;
    p_oTargetTree = p_oTargetTree7;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    p_oTargetTree->GetValue(p_oPop->GetFloatDataCode("Growth",
        p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fGrowth);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);
    EXPECT_LT(fabs(fGrowth - fExpectedGrowth), 0.001);

    fExpectedDiam = 4.046565946;
    fExpectedGrowth = 0.290746418;
    p_oTargetTree = p_oTargetTree8;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    p_oTargetTree->GetValue(p_oPop->GetFloatDataCode("Growth",
        p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fGrowth);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);
    EXPECT_LT(fabs(fGrowth - fExpectedGrowth)/fGrowth, 0.001);

    fExpectedDiam = 4.335006202;
    fExpectedGrowth = 2.091697066;
    p_oTargetTree = p_oTargetTree9;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    p_oTargetTree->GetValue(p_oPop->GetFloatDataCode("Growth",
        p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fGrowth);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);
    EXPECT_LT(fabs(fGrowth - fExpectedGrowth)/fGrowth, 0.001);
    delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

////////////////////////////////////////////////////////////////////////////
// TestErrorProcessing()
////////////////////////////////////////////////////////////////////////////
TEST(WeibullClimateGrowth, TestErrorProcessing) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    p_oSimManager->ReadFile(WriteWeibullClimateGrowthXMLErrorFile1());
    FAIL() << "TestWeibullClimateGrowth error processing didn't catch error for WriteWeibullClimateGrowthXMLErrorFile1.";
  } catch (modelErr& err) {
    if (err.sFunction.compare("clNCILargerNeighbors::DoSetup") != 0) {
      FAIL() << "TestWeibullClimateGrowth error processing caught wrong error for WriteWeibullClimateGrowthXMLErrorFile1.";
    };
  }

  try {
    p_oSimManager->ReadFile(WriteWeibullClimateGrowthXMLErrorFile2());
    FAIL() << "TestWeibullClimateGrowth error processing didn't catch error for WriteWeibullClimateGrowthXMLErrorFile2.";
  } catch (modelErr& err) {
    if (err.sFunction.compare("clNCIMasterGrowth::ValidateData") != 0) {
      FAIL() << "TestWeibullClimateGrowth error processing caught wrong error for WriteWeibullClimateGrowthXMLErrorFile2.";
    };
  }

  try {
    p_oSimManager->ReadFile(WriteWeibullClimateGrowthXMLErrorFile3());
    FAIL() << "TestWeibullClimateGrowth error processing didn't catch error for WriteWeibullClimateGrowthXMLErrorFile3.";
  } catch (modelErr& err) {
    if (err.sFunction.compare("clSizeEffectLowerBounded::DoSetup") != 0) {
      FAIL() << "TestWeibullClimateGrowth error processing caught wrong error for WriteWeibullClimateGrowthXMLErrorFile3.";
    };
  }

  try {
    p_oSimManager->ReadFile(WriteWeibullClimateGrowthXMLErrorFile4());
    FAIL() << "TestWeibullClimateGrowth error processing didn't catch error for WriteWeibullClimateGrowthXMLErrorFile4.";
  } catch (modelErr& err) {
    if (err.sFunction.compare("clSizeEffectLowerBounded::DoSetup") != 0) {
      FAIL() << "TestWeibullClimateGrowth error processing caught wrong error for WriteWeibullClimateGrowthXMLErrorFile4.";
    };
  }

  try {
    p_oSimManager->ReadFile(WriteWeibullClimateGrowthXMLErrorFile5());
    FAIL() << "TestWeibullClimateGrowth error processing didn't catch error for WriteWeibullClimateGrowthXMLErrorFile5.";
  } catch (modelErr& err) {
    if (err.sFunction.compare("clPrecipitationEffectWeibull::DoSetup") != 0) {
      FAIL() << "TestWeibullClimateGrowth error processing caught wrong error for WriteWeibullClimateGrowthXMLErrorFile5.";
    };
  }

  try {
    p_oSimManager->ReadFile(WriteWeibullClimateGrowthXMLErrorFile6());
    FAIL() << "TestWeibullClimateGrowth error processing didn't catch error for WriteWeibullClimateGrowthXMLErrorFile6.";
  } catch (modelErr& err) {
    if (err.sFunction.compare("clTemperatureEffectWeibull::DoSetup") != 0) {
      FAIL() << "TestWeibullClimateGrowth error processing caught wrong error for WriteWeibullClimateGrowthXMLErrorFile6.";
    };
  }

  try {
      p_oSimManager->ReadFile(WriteWeibullClimateGrowthXMLErrorFile7());
      FAIL() << "TestWeibullClimateGrowth error processing didn't catch error for WriteWeibullClimateGrowthXMLErrorFile7.";
    } catch (modelErr& err) {
      if (err.sFunction.compare("clGaussianNitrogenEffect::DoSetup") != 0) {
        FAIL() << "TestWeibullClimateGrowth error processing caught wrong error for WriteWeibullClimateGrowthXMLErrorFile7.";
      };
    }
  delete p_oSimManager;
}

////////////////////////////////////////////////////////////////////////////
// WriteWeibullClimateGrowthXMLFile1()
////////////////////////////////////////////////////////////////////////////
const char* WriteWeibullClimateGrowthXMLFile1() {
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
       << "<yearsPerTimestep>1</yearsPerTimestep>"
       << "<randomSeed>1</randomSeed>"
       << "<plot_lenX>200.0</plot_lenX>"
       << "<plot_lenY>200.0</plot_lenY>"
       << "<plot_latitude>55.37</plot_latitude>"
       << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
       << "<plot_temp_C>12.88171785</plot_temp_C>"
       << "<plot_n_dep>3.58</plot_n_dep>"
       << "<plot_seasonal_precipitation>34</plot_seasonal_precipitation>"
       << "<plot_water_deficit>456.2</plot_water_deficit>"
       << "</plot>";

  WriteWeibullClimateGrowthTreeStuff(oOut);
  WriteWeibullClimateGrowthCommonStuff(oOut, 0);

  oOut.close();

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteWeibullClimateGrowthXMLFile2()
////////////////////////////////////////////////////////////////////////////
const char* WriteWeibullClimateGrowthXMLFile2() {
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
       << "<yearsPerTimestep>3</yearsPerTimestep>"
       << "<randomSeed>1</randomSeed>"
       << "<plot_lenX>200.0</plot_lenX>"
       << "<plot_lenY>200.0</plot_lenY>"
       << "<plot_latitude>55.37</plot_latitude>"
       << "<plot_precip_mm_yr>665.5</plot_precip_mm_yr>"
       << "<plot_temp_C>12.88171785</plot_temp_C>"
       << "<plot_n_dep>3.58</plot_n_dep>"
       << "<plot_seasonal_precipitation>34</plot_seasonal_precipitation>"
       << "<plot_water_deficit>1150.645781</plot_water_deficit>"
       << "</plot>";

  WriteWeibullClimateGrowthTreeStuff(oOut);
  WriteWeibullClimateGrowthCommonStuff(oOut, 2);

  oOut.close();

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteWeibullClimateGrowthXMLFile3()
////////////////////////////////////////////////////////////////////////////
const char* WriteWeibullClimateGrowthXMLFile3() {
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
       << "<yearsPerTimestep>1</yearsPerTimestep>"
       << "<randomSeed>1</randomSeed>"
       << "<plot_lenX>200.0</plot_lenX>"
       << "<plot_lenY>200.0</plot_lenY>"
       << "<plot_latitude>55.37</plot_latitude>"
       << "<plot_precip_mm_yr>10.68</plot_precip_mm_yr>"
       << "<plot_temp_C>12.88171785</plot_temp_C>"
       << "<plot_n_dep>3.58</plot_n_dep>"
       << "<plot_seasonal_precipitation>1150.645781</plot_seasonal_precipitation>"
       << "<plot_water_deficit>6457</plot_water_deficit>"
       << "</plot>";

  WriteWeibullClimateGrowthTreeStuff(oOut);

  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>NCIMasterGrowth</behaviorName>"
       << "<version>3</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_3\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_4\" type=\"Sapling\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>NCIMasterGrowth</behaviorName>"
       << "<version>3</version>"
       << "<listPosition>2</listPosition>"
       << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_4\" type=\"Adult\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>StochasticMortality</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>3</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_3\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_4\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_4\" type=\"Sapling\"/>"
       << "</behavior>"
       << "</behaviorList>"
       << "<NCIMasterGrowth1>"
       << "<nciWhichShadingEffect>0</nciWhichShadingEffect>"
       << "<nciWhichCrowdingEffect>1</nciWhichCrowdingEffect>"
       << "<nciWhichNCITerm>3</nciWhichNCITerm>"
       << "<nciWhichSizeEffect>2</nciWhichSizeEffect>"
       << "<nciWhichDamageEffect>0</nciWhichDamageEffect>"
       << "<nciWhichPrecipitationEffect>1</nciWhichPrecipitationEffect>"
       << "<nciWhichTemperatureEffect>1</nciWhichTemperatureEffect>"
       << "<nciWhichNitrogenEffect>1</nciWhichNitrogenEffect>"
       << "<nciWhichInfectionEffect>" << no_infection_effect << "</nciWhichInfectionEffect>"
       << "<gr_stochGrowthMethod>" << deterministic_pdf << "</gr_stochGrowthMethod>"
       << "<nciMaxCrowdingRadius>"
       << "<nmcrVal species=\"Species_2\">10</nmcrVal>"
       << "<nmcrVal species=\"Species_3\">11</nmcrVal>"
       << "<nmcrVal species=\"Species_4\">12</nmcrVal>"
       << "</nciMaxCrowdingRadius>"
       << "<gr_nciMaxPotentialGrowth>"
       << "<gr_nmpgVal species=\"Species_2\">0.2574</gr_nmpgVal>"
       << "<gr_nmpgVal species=\"Species_3\">10</gr_nmpgVal>"
       << "<gr_nmpgVal species=\"Species_4\">5.4</gr_nmpgVal>"
       << "</gr_nciMaxPotentialGrowth>"
       << "<nciSizeEffectX0>"
       << "<nsex0Val species=\"Species_2\">297.615</nsex0Val>"
       << "<nsex0Val species=\"Species_3\">18.07</nsex0Val>"
       << "<nsex0Val species=\"Species_4\">132.1</nsex0Val>"
       << "</nciSizeEffectX0>"
       << "<nciSizeEffectXb>"
       << "<nsexbVal species=\"Species_2\">4.065</nsexbVal>"
       << "<nsexbVal species=\"Species_3\">0.902</nsexbVal>"
       << "<nsexbVal species=\"Species_4\">2.568</nsexbVal>"
       << "</nciSizeEffectXb>"
       << "<nciSizeEffectLowerBound>"
       << "<nselbVal species=\"Species_2\">2.54</nselbVal>"
       << "<nselbVal species=\"Species_3\">7</nselbVal>"
       << "<nselbVal species=\"Species_4\">10</nselbVal>"
       << "</nciSizeEffectLowerBound>"
       << "<nciCrowdingC>"
       << "<nccVal species=\"Species_2\">0.2</nccVal>"
       << "<nccVal species=\"Species_3\">0.5</nccVal>"
       << "<nccVal species=\"Species_4\">6.068213</nccVal>"
       << "</nciCrowdingC>"
       << "<nciCrowdingD>"
       << "<ncdVal species=\"Species_2\">0.9358206</ncdVal>"
       << "<ncdVal species=\"Species_3\">1.16629</ncdVal>"
       << "<ncdVal species=\"Species_4\">0.7153209</ncdVal>"
       << "</nciCrowdingD>"
       << "<nciCrowdingGamma>"
       << "<ncgVal species=\"Species_2\">-0.06164447</ncgVal>"
       << "<ncgVal species=\"Species_3\">-0.4051102</ncgVal>"
       << "<ncgVal species=\"Species_4\">0.391744</ncgVal>"
       << "</nciCrowdingGamma>"
       << "<nciWeibPrecipEffA>"
       << "<nwpeaVal species=\"Species_2\">1296.22</nwpeaVal>"
       << "<nwpeaVal species=\"Species_3\">1296.22</nwpeaVal>"
       << "<nwpeaVal species=\"Species_4\">1296.22</nwpeaVal>"
       << "</nciWeibPrecipEffA>"
       << "<nciWeibPrecipEffB>"
       << "<nwpebVal species=\"Species_2\">0.8</nwpebVal>"
       << "<nwpebVal species=\"Species_3\">0.8</nwpebVal>"
       << "<nwpebVal species=\"Species_4\">0.8</nwpebVal>"
       << "</nciWeibPrecipEffB>"
       << "<nciWeibPrecipEffC>"
       << "<nwpecVal species=\"Species_2\">1032.2</nwpecVal>"
       << "<nwpecVal species=\"Species_3\">1032.2</nwpecVal>"
       << "<nwpecVal species=\"Species_4\">1032.2</nwpecVal>"
       << "</nciWeibPrecipEffC>"
       << "<nciWeibPrecipType>1</nciWeibPrecipType>"
       << "<nciWeibTempEffA>"
       << "<nwteaVal species=\"Species_2\">8.89</nwteaVal>"
       << "<nwteaVal species=\"Species_3\">8.89</nwteaVal>"
       << "<nwteaVal species=\"Species_4\">8.89</nwteaVal>"
       << "</nciWeibTempEffA>"
       << "<nciWeibTempEffB>"
       << "<nwtebVal species=\"Species_2\">1.2</nwtebVal>"
       << "<nwtebVal species=\"Species_3\">1.2</nwtebVal>"
       << "<nwtebVal species=\"Species_4\">1.2</nwtebVal>"
       << "</nciWeibTempEffB>"
       << "<nciWeibTempEffC>"
       << "<nwtecVal species=\"Species_2\">13.26</nwtecVal>"
       << "<nwtecVal species=\"Species_3\">13.26</nwtecVal>"
       << "<nwtecVal species=\"Species_4\">13.26</nwtecVal>"
       << "</nciWeibTempEffC>"
       << "<nciMinNeighborDBH>"
       << "<nmndVal species=\"Species_1\">5</nmndVal>"
       << "<nmndVal species=\"Species_2\">5</nmndVal>"
       << "<nmndVal species=\"Species_3\">5</nmndVal>"
       << "<nmndVal species=\"Species_4\">5</nmndVal>"
       << "</nciMinNeighborDBH>"
       << "<nciNitrogenX0>"
       << "<nnx0Val species=\"Species_2\">3.41</nnx0Val>"
       << "<nnx0Val species=\"Species_3\">1.13</nnx0Val>"
       << "<nnx0Val species=\"Species_4\">10.9</nnx0Val>"
       << "</nciNitrogenX0>"
       << "<nciNitrogenXb>"
       << "<nnxbVal species=\"Species_2\">1.07</nnxbVal>"
       << "<nnxbVal species=\"Species_3\">3.6</nnxbVal>"
       << "<nnxbVal species=\"Species_4\">14.44</nnxbVal>"
       << "</nciNitrogenXb>"

       << "</NCIMasterGrowth1>"
       << "<NCIMasterGrowth2>"
       << "<nciWhichShadingEffect>0</nciWhichShadingEffect>"
       << "<nciWhichCrowdingEffect>1</nciWhichCrowdingEffect>"
       << "<nciWhichNCITerm>3</nciWhichNCITerm>"
       << "<nciWhichSizeEffect>2</nciWhichSizeEffect>"
       << "<nciWhichDamageEffect>0</nciWhichDamageEffect>"
       << "<nciWhichPrecipitationEffect>1</nciWhichPrecipitationEffect>"
       << "<nciWhichTemperatureEffect>1</nciWhichTemperatureEffect>"
       << "<nciWhichNitrogenEffect>1</nciWhichNitrogenEffect>"
       << "<nciWhichInfectionEffect>" << no_infection_effect << "</nciWhichInfectionEffect>"
       << "<gr_stochGrowthMethod>" << deterministic_pdf << "</gr_stochGrowthMethod>"
       << "<nciMaxCrowdingRadius>"
       << "<nmcrVal species=\"Species_2\">10</nmcrVal>"
       << "<nmcrVal species=\"Species_3\">11</nmcrVal>"
       << "<nmcrVal species=\"Species_4\">12</nmcrVal>"
       << "</nciMaxCrowdingRadius>"
       << "<gr_nciMaxPotentialGrowth>"
       << "<gr_nmpgVal species=\"Species_2\">0.2574</gr_nmpgVal>"
       << "<gr_nmpgVal species=\"Species_3\">10</gr_nmpgVal>"
       << "<gr_nmpgVal species=\"Species_4\">5.4</gr_nmpgVal>"
       << "</gr_nciMaxPotentialGrowth>"
       << "<nciSizeEffectX0>"
       << "<nsex0Val species=\"Species_2\">297.615</nsex0Val>"
       << "<nsex0Val species=\"Species_3\">18.07</nsex0Val>"
       << "<nsex0Val species=\"Species_4\">132.1</nsex0Val>"
       << "</nciSizeEffectX0>"
       << "<nciSizeEffectXb>"
       << "<nsexbVal species=\"Species_2\">4.065</nsexbVal>"
       << "<nsexbVal species=\"Species_3\">0.902</nsexbVal>"
       << "<nsexbVal species=\"Species_4\">2.568</nsexbVal>"
       << "</nciSizeEffectXb>"
       << "<nciSizeEffectLowerBound>"
       << "<nselbVal species=\"Species_2\">2.54</nselbVal>"
       << "<nselbVal species=\"Species_3\">7</nselbVal>"
       << "<nselbVal species=\"Species_4\">10</nselbVal>"
       << "</nciSizeEffectLowerBound>"
       << "<nciCrowdingC>"
       << "<nccVal species=\"Species_2\">8.261</nccVal>"
       << "<nccVal species=\"Species_3\">0</nccVal>"
       << "<nccVal species=\"Species_4\">0.321</nccVal>"
       << "</nciCrowdingC>"
       << "<nciCrowdingD>"
       << "<ncdVal species=\"Species_2\">1.001</ncdVal>"
       << "<ncdVal species=\"Species_3\">2.914</ncdVal>"
       << "<ncdVal species=\"Species_4\">0.4</ncdVal>"
       << "</nciCrowdingD>"
       << "<nciCrowdingGamma>"
       << "<ncgVal species=\"Species_2\">-1.208</ncgVal>"
       << "<ncgVal species=\"Species_3\">1.976</ncgVal>"
       << "<ncgVal species=\"Species_4\">0.461</ncgVal>"
       << "</nciCrowdingGamma>"
       << "<nciWeibTempEffA>"
       << "<nwteaVal species=\"Species_2\">8.89</nwteaVal>"
       << "<nwteaVal species=\"Species_3\">8.89</nwteaVal>"
       << "<nwteaVal species=\"Species_4\">8.89</nwteaVal>"
       << "</nciWeibTempEffA>"
       << "<nciWeibTempEffB>"
       << "<nwtebVal species=\"Species_2\">1.2</nwtebVal>"
       << "<nwtebVal species=\"Species_3\">1.2</nwtebVal>"
       << "<nwtebVal species=\"Species_4\">1.2</nwtebVal>"
       << "</nciWeibTempEffB>"
       << "<nciWeibTempEffC>"
       << "<nwtecVal species=\"Species_2\">13.26</nwtecVal>"
       << "<nwtecVal species=\"Species_3\">13.26</nwtecVal>"
       << "<nwtecVal species=\"Species_4\">13.26</nwtecVal>"
       << "</nciWeibTempEffC>"
       << "<nciWeibPrecipEffA>"
       << "<nwpeaVal species=\"Species_2\">1296.22</nwpeaVal>"
       << "<nwpeaVal species=\"Species_3\">1296.22</nwpeaVal>"
       << "<nwpeaVal species=\"Species_4\">1296.22</nwpeaVal>"
       << "</nciWeibPrecipEffA>"
       << "<nciWeibPrecipEffB>"
       << "<nwpebVal species=\"Species_2\">0.8</nwpebVal>"
       << "<nwpebVal species=\"Species_3\">0.8</nwpebVal>"
       << "<nwpebVal species=\"Species_4\">0.8</nwpebVal>"
       << "</nciWeibPrecipEffB>"
       << "<nciWeibPrecipEffC>"
       << "<nwpecVal species=\"Species_2\">1032.2</nwpecVal>"
       << "<nwpecVal species=\"Species_3\">1032.2</nwpecVal>"
       << "<nwpecVal species=\"Species_4\">1032.2</nwpecVal>"
       << "</nciWeibPrecipEffC>"
       << "<nciWeibPrecipType>1</nciWeibPrecipType>"
       << "<nciMinNeighborDBH>"
       << "<nmndVal species=\"Species_1\">5</nmndVal>"
       << "<nmndVal species=\"Species_2\">5</nmndVal>"
       << "<nmndVal species=\"Species_3\">5</nmndVal>"
       << "<nmndVal species=\"Species_4\">5</nmndVal>"
       << "</nciMinNeighborDBH>"
       << "<nciNitrogenX0>"
       << "<nnx0Val species=\"Species_2\">10.9</nnx0Val>"
       << "<nnx0Val species=\"Species_3\">22.59</nnx0Val>"
       << "<nnx0Val species=\"Species_4\">31.9</nnx0Val>"
       << "</nciNitrogenX0>"
       << "<nciNitrogenXb>"
       << "<nnxbVal species=\"Species_2\">14.44</nnxbVal>"
       << "<nnxbVal species=\"Species_3\">81.05</nnxbVal>"
       << "<nnxbVal species=\"Species_4\">18.2</nnxbVal>"
       << "</nciNitrogenXb>"
       << "</NCIMasterGrowth2>"
       << "<StochasticMortality3>"
       << "<mo_stochasticMortRate>"
       << "<mo_smrVal species=\"Species_3\">0</mo_smrVal>"
       << "<mo_smrVal species=\"Species_1\">0</mo_smrVal>"
       << "<mo_smrVal species=\"Species_2\">0</mo_smrVal>"
       << "<mo_smrVal species=\"Species_4\">0</mo_smrVal>"
       << "</mo_stochasticMortRate>"
       << "</StochasticMortality3>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteWeibullClimateGrowthTreeStuff()
/////////////////////////////////////////////////////////////////////////////
void WriteWeibullClimateGrowthTreeStuff(std::fstream &oOut) {
  oOut << "<trees>"
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
// WriteWeibullClimateGrowthCommonStuff()
/////////////////////////////////////////////////////////////////////////////
void WriteWeibullClimateGrowthCommonStuff(std::fstream &oOut, int iPrecipType) {
  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>NCIMasterGrowth</behaviorName>"
       << "<version>3</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_3\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_4\" type=\"Sapling\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>NCIMasterGrowth</behaviorName>"
       << "<version>3</version>"
       << "<listPosition>2</listPosition>"
       << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_4\" type=\"Adult\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>StochasticMortality</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>3</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_3\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_4\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_4\" type=\"Sapling\"/>"
       << "</behavior>"
       << "</behaviorList>"
       << "<NCIMasterGrowth1>"
       << "<nciWhichShadingEffect>0</nciWhichShadingEffect>"
       << "<nciWhichCrowdingEffect>1</nciWhichCrowdingEffect>"
       << "<nciWhichNCITerm>3</nciWhichNCITerm>"
       << "<nciWhichSizeEffect>2</nciWhichSizeEffect>"
       << "<nciWhichDamageEffect>0</nciWhichDamageEffect>"
       << "<nciWhichPrecipitationEffect>1</nciWhichPrecipitationEffect>"
       << "<nciWhichTemperatureEffect>1</nciWhichTemperatureEffect>"
       << "<nciWhichNitrogenEffect>0</nciWhichNitrogenEffect>"
       << "<nciWhichInfectionEffect>" << no_infection_effect << "</nciWhichInfectionEffect>"
       << "<gr_stochGrowthMethod>" << deterministic_pdf << "</gr_stochGrowthMethod>"
       << "<nciMaxCrowdingRadius>"
       << "<nmcrVal species=\"Species_2\">10</nmcrVal>"
       << "<nmcrVal species=\"Species_3\">11</nmcrVal>"
       << "<nmcrVal species=\"Species_4\">12</nmcrVal>"
       << "</nciMaxCrowdingRadius>"
       << "<gr_nciMaxPotentialGrowth>"
       << "<gr_nmpgVal species=\"Species_2\">0.2574</gr_nmpgVal>"
       << "<gr_nmpgVal species=\"Species_3\">10</gr_nmpgVal>"
       << "<gr_nmpgVal species=\"Species_4\">5.4</gr_nmpgVal>"
       << "</gr_nciMaxPotentialGrowth>"
       << "<nciSizeEffectX0>"
       << "<nsex0Val species=\"Species_2\">297.615</nsex0Val>"
       << "<nsex0Val species=\"Species_3\">18.07</nsex0Val>"
       << "<nsex0Val species=\"Species_4\">132.1</nsex0Val>"
       << "</nciSizeEffectX0>"
       << "<nciSizeEffectXb>"
       << "<nsexbVal species=\"Species_2\">4.065</nsexbVal>"
       << "<nsexbVal species=\"Species_3\">0.902</nsexbVal>"
       << "<nsexbVal species=\"Species_4\">2.568</nsexbVal>"
       << "</nciSizeEffectXb>"
       << "<nciSizeEffectLowerBound>"
       << "<nselbVal species=\"Species_2\">2.54</nselbVal>"
       << "<nselbVal species=\"Species_3\">7</nselbVal>"
       << "<nselbVal species=\"Species_4\">10</nselbVal>"
       << "</nciSizeEffectLowerBound>"
       << "<nciCrowdingC>"
       << "<nccVal species=\"Species_2\">0.2</nccVal>"
       << "<nccVal species=\"Species_3\">0.5</nccVal>"
       << "<nccVal species=\"Species_4\">6.068213</nccVal>"
       << "</nciCrowdingC>"
       << "<nciCrowdingD>"
       << "<ncdVal species=\"Species_2\">0.9358206</ncdVal>"
       << "<ncdVal species=\"Species_3\">1.16629</ncdVal>"
       << "<ncdVal species=\"Species_4\">0.7153209</ncdVal>"
       << "</nciCrowdingD>"
       << "<nciCrowdingGamma>"
       << "<ncgVal species=\"Species_2\">-0.06164447</ncgVal>"
       << "<ncgVal species=\"Species_3\">-0.4051102</ncgVal>"
       << "<ncgVal species=\"Species_4\">0.391744</ncgVal>"
       << "</nciCrowdingGamma>"
       << "<nciWeibPrecipEffA>"
       << "<nwpeaVal species=\"Species_2\">1296.228</nwpeaVal>"
       << "<nwpeaVal species=\"Species_3\">3306.159</nwpeaVal>"
       << "<nwpeaVal species=\"Species_4\">0.001</nwpeaVal>"
       << "</nciWeibPrecipEffA>"
       << "<nciWeibPrecipEffB>"
       << "<nwpebVal species=\"Species_2\">0.8027915</nwpebVal>"
       << "<nwpebVal species=\"Species_3\">6.669916</nwpebVal>"
       << "<nwpebVal species=\"Species_4\">0.05211167</nwpebVal>"
       << "</nciWeibPrecipEffB>"
       << "<nciWeibPrecipEffC>"
       << "<nwpecVal species=\"Species_2\">1032.264</nwpecVal>"
       << "<nwpecVal species=\"Species_3\">3835.918</nwpecVal>"
       << "<nwpecVal species=\"Species_4\">643.8208</nwpecVal>"
       << "</nciWeibPrecipEffC>"
       << "<nciWeibPrecipType>" << iPrecipType << "</nciWeibPrecipType>"
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
       << "</NCIMasterGrowth1>"
       << "<NCIMasterGrowth2>"
       << "<nciWhichShadingEffect>0</nciWhichShadingEffect>"
       << "<nciWhichCrowdingEffect>1</nciWhichCrowdingEffect>"
       << "<nciWhichNCITerm>3</nciWhichNCITerm>"
       << "<nciWhichSizeEffect>2</nciWhichSizeEffect>"
       << "<nciWhichDamageEffect>0</nciWhichDamageEffect>"
       << "<nciWhichPrecipitationEffect>1</nciWhichPrecipitationEffect>"
       << "<nciWhichTemperatureEffect>1</nciWhichTemperatureEffect>"
       << "<nciWhichNitrogenEffect>0</nciWhichNitrogenEffect>"
       << "<nciWhichInfectionEffect>" << no_infection_effect << "</nciWhichInfectionEffect>"
       << "<gr_stochGrowthMethod>" << deterministic_pdf << "</gr_stochGrowthMethod>"
       << "<nciMaxCrowdingRadius>"
       << "<nmcrVal species=\"Species_2\">10</nmcrVal>"
       << "<nmcrVal species=\"Species_3\">11</nmcrVal>"
       << "<nmcrVal species=\"Species_4\">12</nmcrVal>"
       << "</nciMaxCrowdingRadius>"
       << "<gr_nciMaxPotentialGrowth>"
       << "<gr_nmpgVal species=\"Species_2\">0.2574</gr_nmpgVal>"
       << "<gr_nmpgVal species=\"Species_3\">10</gr_nmpgVal>"
       << "<gr_nmpgVal species=\"Species_4\">5.4</gr_nmpgVal>"
       << "</gr_nciMaxPotentialGrowth>"
       << "<nciSizeEffectX0>"
       << "<nsex0Val species=\"Species_2\">297.615</nsex0Val>"
       << "<nsex0Val species=\"Species_3\">18.07</nsex0Val>"
       << "<nsex0Val species=\"Species_4\">132.1</nsex0Val>"
       << "</nciSizeEffectX0>"
       << "<nciSizeEffectXb>"
       << "<nsexbVal species=\"Species_2\">4.065</nsexbVal>"
       << "<nsexbVal species=\"Species_3\">0.902</nsexbVal>"
       << "<nsexbVal species=\"Species_4\">2.568</nsexbVal>"
       << "</nciSizeEffectXb>"
       << "<nciSizeEffectLowerBound>"
       << "<nselbVal species=\"Species_2\">2.54</nselbVal>"
       << "<nselbVal species=\"Species_3\">7</nselbVal>"
       << "<nselbVal species=\"Species_4\">10</nselbVal>"
       << "</nciSizeEffectLowerBound>"
       << "<nciCrowdingC>"
       << "<nccVal species=\"Species_2\">8.261</nccVal>"
       << "<nccVal species=\"Species_3\">0</nccVal>"
       << "<nccVal species=\"Species_4\">0.321</nccVal>"
       << "</nciCrowdingC>"
       << "<nciCrowdingD>"
       << "<ncdVal species=\"Species_2\">1.001</ncdVal>"
       << "<ncdVal species=\"Species_3\">2.914</ncdVal>"
       << "<ncdVal species=\"Species_4\">0.4</ncdVal>"
       << "</nciCrowdingD>"
       << "<nciCrowdingGamma>"
       << "<ncgVal species=\"Species_2\">-1.208</ncgVal>"
       << "<ncgVal species=\"Species_3\">1.976</ncgVal>"
       << "<ncgVal species=\"Species_4\">0.461</ncgVal>"
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
       << "<nwpeaVal species=\"Species_2\">420.2115</nwpeaVal>"
       << "<nwpeaVal species=\"Species_3\">3.753555</nwpeaVal>"
       << "<nwpeaVal species=\"Species_4\">0.001</nwpeaVal>"
       << "</nciWeibPrecipEffA>"
       << "<nciWeibPrecipEffB>"
       << "<nwpebVal species=\"Species_2\">0.4447052</nwpebVal>"
       << "<nwpebVal species=\"Species_3\">0.07809054</nwpebVal>"
       << "<nwpebVal species=\"Species_4\">0.05211167</nwpebVal>"
       << "</nciWeibPrecipEffB>"
       << "<nciWeibPrecipEffC>"
       << "<nwpecVal species=\"Species_2\">0.000319117</nwpecVal>"
       << "<nwpecVal species=\"Species_3\">1048.734</nwpecVal>"
       << "<nwpecVal species=\"Species_4\">643.8208</nwpecVal>"
       << "</nciWeibPrecipEffC>"
       << "<nciWeibPrecipType>" << iPrecipType << "</nciWeibPrecipType>"
       << "<nciMinNeighborDBH>"
       << "<nmndVal species=\"Species_1\">5</nmndVal>"
       << "<nmndVal species=\"Species_2\">5</nmndVal>"
       << "<nmndVal species=\"Species_3\">5</nmndVal>"
       << "<nmndVal species=\"Species_4\">5</nmndVal>"
       << "</nciMinNeighborDBH>"
       << "</NCIMasterGrowth2>"
       << "<StochasticMortality3>"
       << "<mo_stochasticMortRate>"
       << "<mo_smrVal species=\"Species_3\">0</mo_smrVal>"
       << "<mo_smrVal species=\"Species_1\">0</mo_smrVal>"
       << "<mo_smrVal species=\"Species_2\">0</mo_smrVal>"
       << "<mo_smrVal species=\"Species_4\">0</mo_smrVal>"
       << "</mo_stochasticMortRate>"
       << "</StochasticMortality3>"
       << "</paramFile>";

}

/////////////////////////////////////////////////////////////////////////////
// WriteWeibullClimateGrowthErrorFileCommonStuff()
/////////////////////////////////////////////////////////////////////////////
void WriteWeibullClimateGrowthErrorFileCommonStuff(std::fstream &oOut) {
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
       << "<behaviorName>NCIMasterGrowth</behaviorName>"
       << "<version>3</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>StochasticMortality</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>2</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
       << "</behavior>"
       << "</behaviorList>"
       << "<NCIMasterGrowth1>"
       << "<nciWhichShadingEffect>0</nciWhichShadingEffect>"
       << "<nciWhichCrowdingEffect>1</nciWhichCrowdingEffect>"
       << "<nciWhichNCITerm>3</nciWhichNCITerm>"
       << "<nciWhichSizeEffect>2</nciWhichSizeEffect>"
       << "<nciWhichDamageEffect>0</nciWhichDamageEffect>"
       << "<nciWhichPrecipitationEffect>1</nciWhichPrecipitationEffect>"
       << "<nciWhichTemperatureEffect>1</nciWhichTemperatureEffect>"
       << "<nciWhichNitrogenEffect>1</nciWhichNitrogenEffect>"
       << "<nciWhichInfectionEffect>" << no_infection_effect << "</nciWhichInfectionEffect>"
       << "<gr_stochGrowthMethod>" << deterministic_pdf << "</gr_stochGrowthMethod>"
       << "<nciCrowdingC>"
       << "<nccVal species=\"Species_1\">8.261</nccVal>"
       << "<nccVal species=\"Species_2\">0</nccVal>"
       << "</nciCrowdingC>"
       << "<nciCrowdingD>"
       << "<ncdVal species=\"Species_1\">1.001</ncdVal>"
       << "<ncdVal species=\"Species_2\">2.914</ncdVal>"
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
       << "<nwpebVal species=\"Species_1\">0.4447052</nwpebVal>"
       << "<nwpebVal species=\"Species_2\">0.07809054</nwpebVal>"
       << "</nciWeibPrecipEffB>"
       << "<nciWeibPrecipEffC>"
       << "<nwpecVal species=\"Species_1\">0.000319117</nwpecVal>"
       << "<nwpecVal species=\"Species_2\">1048.734</nwpecVal>"
       << "</nciWeibPrecipEffC>"
       << "<nciSizeEffectLowerBound>"
       << "<nselbVal species=\"Species_1\">0</nselbVal>"
       << "<nselbVal species=\"Species_2\">0.5</nselbVal>"
       << "</nciSizeEffectLowerBound>"
       << "<nciMinNeighborDBH>"
       << "<nmndVal species=\"Species_1\">5</nmndVal>"
       << "<nmndVal species=\"Species_2\">5</nmndVal>"
       << "</nciMinNeighborDBH>"
       << "<nciNitrogenX0>"
       << "<nnx0Val species=\"Species_1\">5</nnx0Val>"
       << "<nnx0Val species=\"Species_2\">5</nnx0Val>"
       << "</nciNitrogenX0>";

}

////////////////////////////////////////////////////////////////////////////
// WriteWeibullClimateGrowthXMLErrorFile1()
////////////////////////////////////////////////////////////////////////////
const char* WriteWeibullClimateGrowthXMLErrorFile1() {
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  WriteWeibullClimateGrowthErrorFileCommonStuff(oOut);

  //Write file
  oOut << "<nciMaxCrowdingRadius>"
       << "<nmcrVal species=\"Species_1\">-10</nmcrVal>"
       << "<nmcrVal species=\"Species_2\">11</nmcrVal>"
       << "</nciMaxCrowdingRadius>"
       << "<gr_nciMaxPotentialGrowth>"
       << "<gr_nmpgVal species=\"Species_1\">0.2574</gr_nmpgVal>"
       << "<gr_nmpgVal species=\"Species_2\">10</gr_nmpgVal>"
       << "</gr_nciMaxPotentialGrowth>"
       << "<nciSizeEffectX0>"
       << "<nsex0Val species=\"Species_1\">297.615</nsex0Val>"
       << "<nsex0Val species=\"Species_2\">18.07</nsex0Val>"
       << "</nciSizeEffectX0>"
       << "<nciSizeEffectXb>"
       << "<nsexbVal species=\"Species_1\">4.065</nsexbVal>"
       << "<nsexbVal species=\"Species_2\">0.902</nsexbVal>"
       << "</nciSizeEffectXb>"
       << "<nciWeibTempEffA>"
       << "<nwteaVal species=\"Species_1\">8.897617</nwteaVal>"
       << "<nwteaVal species=\"Species_2\">8.91133</nwteaVal>"
       << "</nciWeibTempEffA>"
       << "<nciWeibPrecipEffA>"
       << "<nwpeaVal species=\"Species_1\">420.2115</nwpeaVal>"
       << "<nwpeaVal species=\"Species_2\">3.753555</nwpeaVal>"
       << "</nciWeibPrecipEffA>"
       << "<nciNitrogenXb>"
       << "<nnxbVal species=\"Species_1\">4.2</nnxbVal>"
       << "<nnxbVal species=\"Species_2\">3.5</nnxbVal>"
       << "</nciNitrogenXb>"
       << "</NCIMasterGrowth1>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteWeibullClimateGrowthXMLErrorFile2()
////////////////////////////////////////////////////////////////////////////
const char* WriteWeibullClimateGrowthXMLErrorFile2() {
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  WriteWeibullClimateGrowthErrorFileCommonStuff(oOut);

  //Write file
  oOut << "<nciMaxCrowdingRadius>"
       << "<nmcrVal species=\"Species_1\">10</nmcrVal>"
       << "<nmcrVal species=\"Species_2\">11</nmcrVal>"
       << "</nciMaxCrowdingRadius>"
       << "<gr_nciMaxPotentialGrowth>"
       << "<gr_nmpgVal species=\"Species_1\">-0.2574</gr_nmpgVal>"
       << "<gr_nmpgVal species=\"Species_2\">10</gr_nmpgVal>"
       << "</gr_nciMaxPotentialGrowth>"
       << "<nciSizeEffectX0>"
       << "<nsex0Val species=\"Species_1\">297.615</nsex0Val>"
       << "<nsex0Val species=\"Species_2\">18.07</nsex0Val>"
       << "</nciSizeEffectX0>"
       << "<nciSizeEffectXb>"
       << "<nsexbVal species=\"Species_1\">4.065</nsexbVal>"
       << "<nsexbVal species=\"Species_2\">0.902</nsexbVal>"
       << "</nciSizeEffectXb>"
       << "<nciWeibTempEffA>"
       << "<nwteaVal species=\"Species_1\">8.897617</nwteaVal>"
       << "<nwteaVal species=\"Species_2\">8.91133</nwteaVal>"
       << "</nciWeibTempEffA>"
       << "<nciWeibPrecipEffA>"
       << "<nwpeaVal species=\"Species_1\">420.2115</nwpeaVal>"
       << "<nwpeaVal species=\"Species_2\">3.753555</nwpeaVal>"
       << "</nciWeibPrecipEffA>"
       << "<nciNitrogenXb>"
       << "<nnxbVal species=\"Species_1\">4.2</nnxbVal>"
       << "<nnxbVal species=\"Species_2\">3.5</nnxbVal>"
       << "</nciNitrogenXb>"
       << "</NCIMasterGrowth1>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteWeibullClimateGrowthXMLErrorFile3()
////////////////////////////////////////////////////////////////////////////
const char* WriteWeibullClimateGrowthXMLErrorFile3() {
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  WriteWeibullClimateGrowthErrorFileCommonStuff(oOut);

  //Write file
  oOut << "<nciMaxCrowdingRadius>"
       << "<nmcrVal species=\"Species_1\">10</nmcrVal>"
       << "<nmcrVal species=\"Species_2\">11</nmcrVal>"
       << "</nciMaxCrowdingRadius>"
       << "<gr_nciMaxPotentialGrowth>"
       << "<gr_nmpgVal species=\"Species_1\">0.2574</gr_nmpgVal>"
       << "<gr_nmpgVal species=\"Species_2\">10</gr_nmpgVal>"
       << "</gr_nciMaxPotentialGrowth>"
       << "<nciSizeEffectX0>"
       << "<nsex0Val species=\"Species_1\">297.615</nsex0Val>"
       << "<nsex0Val species=\"Species_2\">18.07</nsex0Val>"
       << "</nciSizeEffectX0>"
       << "<nciSizeEffectXb>"
       << "<nsexbVal species=\"Species_1\">0</nsexbVal>"
       << "<nsexbVal species=\"Species_2\">0.902</nsexbVal>"
       << "</nciSizeEffectXb>"
       << "<nciWeibTempEffA>"
       << "<nwteaVal species=\"Species_1\">8.897617</nwteaVal>"
       << "<nwteaVal species=\"Species_2\">8.91133</nwteaVal>"
       << "</nciWeibTempEffA>"
       << "<nciWeibPrecipEffA>"
       << "<nwpeaVal species=\"Species_1\">420.2115</nwpeaVal>"
       << "<nwpeaVal species=\"Species_2\">3.753555</nwpeaVal>"
       << "</nciWeibPrecipEffA>"
       << "<nciNitrogenXb>"
       << "<nnxbVal species=\"Species_1\">4.2</nnxbVal>"
       << "<nnxbVal species=\"Species_2\">3.5</nnxbVal>"
       << "</nciNitrogenXb>"
       << "</NCIMasterGrowth1>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteWeibullClimateGrowthXMLErrorFile4()
////////////////////////////////////////////////////////////////////////////
const char* WriteWeibullClimateGrowthXMLErrorFile4() {
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  WriteWeibullClimateGrowthErrorFileCommonStuff(oOut);

  //Write file
  oOut << "<nciMaxCrowdingRadius>"
       << "<nmcrVal species=\"Species_1\">10</nmcrVal>"
       << "<nmcrVal species=\"Species_2\">11</nmcrVal>"
       << "</nciMaxCrowdingRadius>"
       << "<gr_nciMaxPotentialGrowth>"
       << "<gr_nmpgVal species=\"Species_1\">0.2574</gr_nmpgVal>"
       << "<gr_nmpgVal species=\"Species_2\">10</gr_nmpgVal>"
       << "</gr_nciMaxPotentialGrowth>"
       << "<nciSizeEffectX0>"
       << "<nsex0Val species=\"Species_1\">0</nsex0Val>"
       << "<nsex0Val species=\"Species_2\">18.07</nsex0Val>"
       << "</nciSizeEffectX0>"
       << "<nciSizeEffectXb>"
       << "<nsexbVal species=\"Species_1\">4.065</nsexbVal>"
       << "<nsexbVal species=\"Species_2\">0.902</nsexbVal>"
       << "</nciSizeEffectXb>"
       << "<nciWeibTempEffA>"
       << "<nwteaVal species=\"Species_1\">8.897617</nwteaVal>"
       << "<nwteaVal species=\"Species_2\">8.91133</nwteaVal>"
       << "</nciWeibTempEffA>"
       << "<nciWeibPrecipEffA>"
       << "<nwpeaVal species=\"Species_1\">420.2115</nwpeaVal>"
       << "<nwpeaVal species=\"Species_2\">3.753555</nwpeaVal>"
       << "</nciWeibPrecipEffA>"
       << "<nciNitrogenXb>"
       << "<nnxbVal species=\"Species_1\">4.2</nnxbVal>"
       << "<nnxbVal species=\"Species_2\">3.5</nnxbVal>"
       << "</nciNitrogenXb>"
       << "</NCIMasterGrowth1>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteWeibullClimateGrowthXMLErrorFile5()
////////////////////////////////////////////////////////////////////////////
const char* WriteWeibullClimateGrowthXMLErrorFile5() {
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  WriteWeibullClimateGrowthErrorFileCommonStuff(oOut);

  //Write file
  oOut << "<nciMaxCrowdingRadius>"
       << "<nmcrVal species=\"Species_1\">10</nmcrVal>"
       << "<nmcrVal species=\"Species_2\">11</nmcrVal>"
       << "</nciMaxCrowdingRadius>"
       << "<gr_nciMaxPotentialGrowth>"
       << "<gr_nmpgVal species=\"Species_1\">0.2574</gr_nmpgVal>"
       << "<gr_nmpgVal species=\"Species_2\">10</gr_nmpgVal>"
       << "</gr_nciMaxPotentialGrowth>"
       << "<nciSizeEffectX0>"
       << "<nsex0Val species=\"Species_1\">297.615</nsex0Val>"
       << "<nsex0Val species=\"Species_2\">18.07</nsex0Val>"
       << "</nciSizeEffectX0>"
       << "<nciSizeEffectXb>"
       << "<nsexbVal species=\"Species_1\">4.065</nsexbVal>"
       << "<nsexbVal species=\"Species_2\">0.902</nsexbVal>"
       << "</nciSizeEffectXb>"
       << "<nciWeibTempEffA>"
       << "<nwteaVal species=\"Species_1\">8.897617</nwteaVal>"
       << "<nwteaVal species=\"Species_2\">8.91133</nwteaVal>"
       << "</nciWeibTempEffA>"
       << "<nciWeibPrecipEffA>"
       << "<nwpeaVal species=\"Species_1\">0</nwpeaVal>"
       << "<nwpeaVal species=\"Species_2\">3.753555</nwpeaVal>"
       << "</nciWeibPrecipEffA>"
       << "<nciNitrogenXb>"
       << "<nnxbVal species=\"Species_1\">4.2</nnxbVal>"
       << "<nnxbVal species=\"Species_2\">3.5</nnxbVal>"
       << "</nciNitrogenXb>"
       << "</NCIMasterGrowth1>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteWeibullClimateGrowthXMLErrorFile6()
////////////////////////////////////////////////////////////////////////////
const char* WriteWeibullClimateGrowthXMLErrorFile6() {
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  WriteWeibullClimateGrowthErrorFileCommonStuff(oOut);

  //Write file
  oOut << "<nciMaxCrowdingRadius>"
       << "<nmcrVal species=\"Species_1\">10</nmcrVal>"
       << "<nmcrVal species=\"Species_2\">11</nmcrVal>"
       << "</nciMaxCrowdingRadius>"
       << "<gr_nciMaxPotentialGrowth>"
       << "<gr_nmpgVal species=\"Species_1\">0.2574</gr_nmpgVal>"
       << "<gr_nmpgVal species=\"Species_2\">10</gr_nmpgVal>"
       << "</gr_nciMaxPotentialGrowth>"
       << "<nciSizeEffectX0>"
       << "<nsex0Val species=\"Species_1\">297.615</nsex0Val>"
       << "<nsex0Val species=\"Species_2\">18.07</nsex0Val>"
       << "</nciSizeEffectX0>"
       << "<nciSizeEffectXb>"
       << "<nsexbVal species=\"Species_1\">4.065</nsexbVal>"
       << "<nsexbVal species=\"Species_2\">0.902</nsexbVal>"
       << "</nciSizeEffectXb>"
       << "<nciWeibTempEffA>"
       << "<nwteaVal species=\"Species_1\">0</nwteaVal>"
       << "<nwteaVal species=\"Species_2\">8.91133</nwteaVal>"
       << "</nciWeibTempEffA>"
       << "<nciWeibPrecipEffA>"
       << "<nwpeaVal species=\"Species_1\">7.6</nwpeaVal>"
       << "<nwpeaVal species=\"Species_2\">3.753555</nwpeaVal>"
       << "</nciWeibPrecipEffA>"
       << "<nciNitrogenXb>"
       << "<nnxbVal species=\"Species_1\">4.2</nnxbVal>"
       << "<nnxbVal species=\"Species_2\">3.0</nnxbVal>"
       << "</nciNitrogenXb>"
       << "</NCIMasterGrowth1>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteWeibullClimateGrowthXMLErrorFile7()
////////////////////////////////////////////////////////////////////////////
const char* WriteWeibullClimateGrowthXMLErrorFile7() {
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  WriteWeibullClimateGrowthErrorFileCommonStuff(oOut);

  //Write file
  oOut << "<nciMaxCrowdingRadius>"
       << "<nmcrVal species=\"Species_1\">10</nmcrVal>"
       << "<nmcrVal species=\"Species_2\">11</nmcrVal>"
       << "</nciMaxCrowdingRadius>"
       << "<gr_nciMaxPotentialGrowth>"
       << "<gr_nmpgVal species=\"Species_1\">0.2574</gr_nmpgVal>"
       << "<gr_nmpgVal species=\"Species_2\">10</gr_nmpgVal>"
       << "</gr_nciMaxPotentialGrowth>"
       << "<nciSizeEffectX0>"
       << "<nsex0Val species=\"Species_1\">297.615</nsex0Val>"
       << "<nsex0Val species=\"Species_2\">18.07</nsex0Val>"
       << "</nciSizeEffectX0>"
       << "<nciSizeEffectXb>"
       << "<nsexbVal species=\"Species_1\">4.065</nsexbVal>"
       << "<nsexbVal species=\"Species_2\">0.902</nsexbVal>"
       << "</nciSizeEffectXb>"
       << "<nciWeibTempEffA>"
       << "<nwteaVal species=\"Species_1\">420.2115</nwteaVal>"
       << "<nwteaVal species=\"Species_2\">8.91133</nwteaVal>"
       << "</nciWeibTempEffA>"
       << "<nciWeibPrecipEffA>"
       << "<nwpeaVal species=\"Species_1\">420.2115</nwpeaVal>"
       << "<nwpeaVal species=\"Species_2\">3.753555</nwpeaVal>"
       << "</nciWeibPrecipEffA>"
       << "<nciNitrogenXb>"
       << "<nnxbVal species=\"Species_1\">4.2</nnxbVal>"
       << "<nnxbVal species=\"Species_2\">0</nnxbVal>"
       << "</nciNitrogenXb>"
       << "</NCIMasterGrowth1>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}
