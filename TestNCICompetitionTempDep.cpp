//---------------------------------------------------------------------------
// TestNCICompetitionTempDep.cpp
//---------------------------------------------------------------------------
#include "TestNCICompetitionTempDep.h"
#include <gtest/gtest.h>
#include <fstream>
#include <math.h>
#include "TreePopulation.h"
#include "Plot.h"
#include "SimManager.h"
#include "BehaviorBase.h"
#include "DataTypes.h"
#include "NCIEffectsList.h"

using namespace std;

////////////////////////////////////////////////////////////////////////////
// TestRun1()
////////////////////////////////////////////////////////////////////////////
TEST(NCICompetitionTempDep, TestRun1) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    clTreePopulation * p_oPop;
    clTree *p_oTargetTree1, *p_oTargetTree2, *p_oTargetTree3, *p_oTargetTree4,
    *p_oTargetTree5, *p_oTargetTree6, *p_oTargetTree7, *p_oTargetTree8,
    *p_oTargetTree9, *p_oTargetTree;
    float fDiam, fExpectedDiam;
    int iSpecies;

    //Load our test file and get our tree population pointers
    p_oSimManager->ReadFile(WriteNCICompTempDepXMLFile1());
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

    //Now create all the neighbors that are too small to compete
    p_oPop->CreateTree(56, 56, 0, clTreePopulation::snag, 30);
    p_oPop->CreateTree(56, 56, 0, clTreePopulation::seedling, 0.2);

    //----------------------------------------------------------------
    // Timestep 1
    //----------------------------------------------------------------
    p_oSimManager->GetPlotObject()->SetMeanAnnualTemp(9.35);
    p_oSimManager->RunSim(1);

    //Check the diameters and growth of the target trees
    fExpectedDiam = 11.2574;
    p_oTargetTree = p_oTargetTree1;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);

    fExpectedDiam = 10.68898729;
    p_oTargetTree = p_oTargetTree2;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);

    fExpectedDiam = 20.51040035;
    p_oTargetTree = p_oTargetTree3;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);

    fExpectedDiam = 30.0190547;
    p_oTargetTree = p_oTargetTree4;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);

    fExpectedDiam = 30.19207463;
    p_oTargetTree = p_oTargetTree5;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);

    fExpectedDiam = 53.10804207;
    p_oTargetTree = p_oTargetTree6;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);

    fExpectedDiam = 19.77976478;
    p_oTargetTree = p_oTargetTree7;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);

    fExpectedDiam = 4.13279586;
    p_oTargetTree = p_oTargetTree8;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);

    fExpectedDiam = 6.862358178;
    p_oTargetTree = p_oTargetTree9;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);

    //----------------------------------------------------------------
    // Timestep 2
    //---------------------------------------------------------------
    p_oSimManager->GetPlotObject()->SetMeanAnnualTemp(12.15);
    p_oSimManager->RunSim(1);

    //Check the diameters and growth of the target trees
    fExpectedDiam = 11.5148;
    p_oTargetTree = p_oTargetTree1;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);

    fExpectedDiam = 10.87633864;
    p_oTargetTree = p_oTargetTree2;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);

    fExpectedDiam = 26.44387621;
    p_oTargetTree = p_oTargetTree3;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);

    fExpectedDiam = 35.20647673;
    p_oTargetTree = p_oTargetTree4;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);

    fExpectedDiam = 30.38111702;
    p_oTargetTree = p_oTargetTree5;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);

    fExpectedDiam = 61.20963803;
    p_oTargetTree = p_oTargetTree6;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);

    fExpectedDiam = 24.91697024;
    p_oTargetTree = p_oTargetTree7;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);

    fExpectedDiam = 4.257933687;
    p_oTargetTree = p_oTargetTree8;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);

    fExpectedDiam = 10.28521443;
    p_oTargetTree = p_oTargetTree9;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);




    delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

////////////////////////////////////////////////////////////////////////////
// TestRun2()
////////////////////////////////////////////////////////////////////////////
TEST(NCICompetitionTempDep, TestRun2) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    clTreePopulation * p_oPop;
    clTree *p_oTargetTree1, *p_oTargetTree2, *p_oTargetTree3, *p_oTargetTree4,
    *p_oTargetTree5, *p_oTargetTree6, *p_oTargetTree7, *p_oTargetTree8,
    *p_oTargetTree9, *p_oTargetTree;
    float fDiam, fExpectedDiam;
    int iSpecies;

    //Load our test file and get our tree population pointers
    p_oSimManager->ReadFile(WriteNCICompTempDepXMLFile2());
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

    //Now create all the neighbors that are too small to compete
    p_oPop->CreateTree(56, 56, 0, clTreePopulation::snag, 30);
    p_oPop->CreateTree(56, 56, 0, clTreePopulation::seedling, 0.2);

    //----------------------------------------------------------------
    // Timestep 1
    //----------------------------------------------------------------
    p_oSimManager->GetPlotObject()->SetMeanAnnualTemp(9.35);
    p_oSimManager->RunSim(1);

    //Check the diameters and growth of the target trees
    fExpectedDiam = 11.2574;
    p_oTargetTree = p_oTargetTree1;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);

    fExpectedDiam = 10.75218491;
    p_oTargetTree = p_oTargetTree2;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);

    fExpectedDiam = 15;
    p_oTargetTree = p_oTargetTree3;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);

    fExpectedDiam = 28.56506024;
    p_oTargetTree = p_oTargetTree4;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);

    fExpectedDiam = 30.25368376;
    p_oTargetTree = p_oTargetTree5;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);

    fExpectedDiam = 45.00000436;
    p_oTargetTree = p_oTargetTree6;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);

    fExpectedDiam = 17.66793764;
    p_oTargetTree = p_oTargetTree7;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);

    fExpectedDiam = 4.247901113;
    p_oTargetTree = p_oTargetTree8;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);

    fExpectedDiam = 4;
    p_oTargetTree = p_oTargetTree9;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);

    //----------------------------------------------------------------
    // Timestep 2
    //---------------------------------------------------------------
    p_oSimManager->GetPlotObject()->SetMeanAnnualTemp(12.15);
    p_oSimManager->RunSim(1);

    //Check the diameters and growth of the target trees
    fExpectedDiam = 11.5148;
    p_oTargetTree = p_oTargetTree1;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);

    fExpectedDiam = 10.92701295;
    p_oTargetTree = p_oTargetTree2;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);

    fExpectedDiam = 15;
    p_oTargetTree = p_oTargetTree3;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);

    fExpectedDiam = 32.30352563;
    p_oTargetTree = p_oTargetTree4;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);

    fExpectedDiam = 30.44944152;
    p_oTargetTree = p_oTargetTree5;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);

    fExpectedDiam = 45.00000604;
    p_oTargetTree = p_oTargetTree6;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);

    fExpectedDiam = 20.61286838;
    p_oTargetTree = p_oTargetTree7;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);

    fExpectedDiam = 4.373938084;
    p_oTargetTree = p_oTargetTree8;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);

    fExpectedDiam = 4;
    p_oTargetTree = p_oTargetTree9;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);




    delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

////////////////////////////////////////////////////////////////////////////
// TestRun3()
////////////////////////////////////////////////////////////////////////////
TEST(NCICompetitionTempDep, TestRun3) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    clTreePopulation * p_oPop;
    clTree *p_oTargetTree1, *p_oTargetTree2, *p_oTargetTree3, *p_oTargetTree4,
    *p_oTargetTree5, *p_oTargetTree6, *p_oTargetTree7, *p_oTargetTree8,
    *p_oTargetTree9, *p_oTargetTree;
    float fDiam, fExpectedDiam;
    int iSpecies;

    //Load our test file and get our tree population pointers
    p_oSimManager->ReadFile(WriteNCICompTempDepXMLFile3());
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

    //Now create all the neighbors that are too small to compete
    p_oPop->CreateTree(56, 56, 0, clTreePopulation::snag, 30);
    p_oPop->CreateTree(56, 56, 0, clTreePopulation::seedling, 0.2);

    //----------------------------------------------------------------
    // Timestep 1
    //----------------------------------------------------------------
    p_oSimManager->GetPlotObject()->SetMeanAnnualTemp(9.35);
    p_oSimManager->RunSim(1);

    //Check the diameters and growth of the target trees
    fExpectedDiam = 11.2574;
    p_oTargetTree = p_oTargetTree1;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);

    fExpectedDiam = 10.75535201;
    p_oTargetTree = p_oTargetTree2;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);

    fExpectedDiam = 15.03852772;
    p_oTargetTree = p_oTargetTree3;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);

    fExpectedDiam = 29.94628544;
    p_oTargetTree = p_oTargetTree4;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);

    fExpectedDiam = 30.25545902;
    p_oTargetTree = p_oTargetTree5;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);

    fExpectedDiam = 46.41375549;
    p_oTargetTree = p_oTargetTree6;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);

    fExpectedDiam = 19.66475077;
    p_oTargetTree = p_oTargetTree7;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);

    fExpectedDiam = 4.253032843;
    p_oTargetTree = p_oTargetTree8;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);

    fExpectedDiam = 4.000085577;
    p_oTargetTree = p_oTargetTree9;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);

    //----------------------------------------------------------------
    // Timestep 2
    //---------------------------------------------------------------
    p_oSimManager->GetPlotObject()->SetMeanAnnualTemp(12.15);
    p_oSimManager->RunSim(1);

    //Check the diameters and growth of the target trees
    fExpectedDiam = 11.5148;
    p_oTargetTree = p_oTargetTree1;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);

    fExpectedDiam = 10.9774505;
    p_oTargetTree = p_oTargetTree2;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);

    fExpectedDiam = 15.12491702;
    p_oTargetTree = p_oTargetTree3;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);

    fExpectedDiam = 35.12468711;
    p_oTargetTree = p_oTargetTree4;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);

    fExpectedDiam = 30.47759892;
    p_oTargetTree = p_oTargetTree5;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);

    fExpectedDiam = 48.0811222;
    p_oTargetTree = p_oTargetTree6;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);

    fExpectedDiam = 24.78759859;
    p_oTargetTree = p_oTargetTree7;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);

    fExpectedDiam = 4.437887633;
    p_oTargetTree = p_oTargetTree8;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);

    fExpectedDiam = 4.000744736;
    p_oTargetTree = p_oTargetTree9;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);




    delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

////////////////////////////////////////////////////////////////////////////
// TestRun4()
// Performs a test run of BA ratio with seedlings in NCI quadrat growth.
////////////////////////////////////////////////////////////////////////////
TEST(NCICompetitionTempDep, TestRun4) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    clTreePopulation * p_oPop;
    clTree *p_oTargetTree1, *p_oTargetTree2, *p_oTargetTree3, *p_oTargetTree4,
    *p_oTargetTree5, *p_oTargetTree6, *p_oTargetTree7, *p_oTargetTree8, *p_oTargetTree;
    float fDiam, fExpectedDiam;
    int iSpecies;

    //Load our test file and get our tree population pointers
    p_oSimManager->ReadFile(WriteNCICompTempDepXMLFile4());
    p_oPop = (clTreePopulation *) p_oSimManager->GetPopulationObject(
        "treepopulation");

    //Create our trees
    fDiam = 0.5;
    iSpecies = 1;
    p_oTargetTree1 = p_oPop->CreateTree(51, 53, iSpecies,
        clTreePopulation::seedling, fDiam);

    fDiam = 0.6;
    p_oTargetTree2 = p_oPop->CreateTree(51.2, 54, iSpecies,
        clTreePopulation::seedling, fDiam);

    fDiam = 0.7;
    p_oTargetTree3 = p_oPop->CreateTree(50.5, 61, iSpecies,
        clTreePopulation::seedling, fDiam);

    fDiam = 0.8;
    p_oTargetTree4 = p_oPop->CreateTree(53, 51, iSpecies,
        clTreePopulation::seedling, fDiam);

    fDiam = 0.9;
    p_oTargetTree5 = p_oPop->CreateTree(20.5, 20.5, iSpecies,
        clTreePopulation::seedling, fDiam);

    fDiam = 1.2;
    p_oTargetTree6 = p_oPop->CreateTree(51, 53, iSpecies,
        clTreePopulation::seedling, fDiam);

    fDiam = 1.3;
    p_oTargetTree7 = p_oPop->CreateTree(51.2, 54, iSpecies,
        clTreePopulation::seedling, fDiam);

    fDiam = 1.4;
    p_oTargetTree8 = p_oPop->CreateTree(50.5, 61, iSpecies,
        clTreePopulation::seedling, fDiam);

    //Create all neighbors
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

    //Now create all the neighbors that are too small or dead to compete
    p_oPop->CreateTree(56, 56, 0, clTreePopulation::snag, 30);
    p_oPop->CreateTree(56, 56, 0, clTreePopulation::seedling, 0.2);
    p_oTargetTree = p_oPop->CreateTree(54, 54, 1, clTreePopulation::adult, 20);
    p_oTargetTree->SetValue(p_oPop->GetIntDataCode("dead",
        p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), storm);

    //----------------------------------------------------------------
    // Timestep 1
    //----------------------------------------------------------------
    p_oSimManager->GetPlotObject()->SetMeanAnnualTemp(9.35);
    p_oSimManager->RunSim(1);

    //Check the diameters and growth of the target trees
    fExpectedDiam = 0.755093539;
    p_oTargetTree = p_oTargetTree1;
    p_oTargetTree->GetValue(p_oPop->GetDiam10Code(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);

    fExpectedDiam = 0.855607594;
    p_oTargetTree = p_oTargetTree2;
    p_oTargetTree->GetValue(p_oPop->GetDiam10Code(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);

    fExpectedDiam = 0.956252161;
    p_oTargetTree = p_oTargetTree3;
    p_oTargetTree->GetValue(p_oPop->GetDiam10Code(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);

    fExpectedDiam = 1.053990826;
    p_oTargetTree = p_oTargetTree4;
    p_oTargetTree->GetValue(p_oPop->GetDiam10Code(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);

    fExpectedDiam = 1.1574;
    p_oTargetTree = p_oTargetTree5;
    p_oTargetTree->GetValue(p_oPop->GetDiam10Code(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);

    fExpectedDiam = 1.455093539;
    p_oTargetTree = p_oTargetTree6;
    p_oTargetTree->GetValue(p_oPop->GetDiam10Code(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);

    fExpectedDiam = 1.554417338;
    p_oTargetTree = p_oTargetTree7;
    p_oTargetTree->GetValue(p_oPop->GetDiam10Code(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);

    fExpectedDiam = 1.655254609;
    p_oTargetTree = p_oTargetTree8;
    p_oTargetTree->GetValue(p_oPop->GetDiam10Code(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);

    //----------------------------------------------------------------
    // Timestep 2
    //---------------------------------------------------------------
    p_oSimManager->GetPlotObject()->SetMeanAnnualTemp(12.15);
    p_oSimManager->RunSim(1);

    //Check the diameters and growth of the target trees
    fExpectedDiam = 0.97617901;
    p_oTargetTree = p_oTargetTree1;
    p_oTargetTree->GetValue(p_oPop->GetDiam10Code(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);

    fExpectedDiam = 1.083786544;
    p_oTargetTree = p_oTargetTree2;
    p_oTargetTree->GetValue(p_oPop->GetDiam10Code(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);

    fExpectedDiam = 1.200179216;
    p_oTargetTree = p_oTargetTree3;
    p_oTargetTree->GetValue(p_oPop->GetDiam10Code(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);

    fExpectedDiam = 1.255059535;
    p_oTargetTree = p_oTargetTree4;
    p_oTargetTree->GetValue(p_oPop->GetDiam10Code(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);

    fExpectedDiam = 1.4148;
    p_oTargetTree = p_oTargetTree5;
    p_oTargetTree->GetValue(p_oPop->GetDiam10Code(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);

    fExpectedDiam = 1.67617901;
    p_oTargetTree = p_oTargetTree6;
    p_oTargetTree->GetValue(p_oPop->GetDiam10Code(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);

    fExpectedDiam = 1.782596288;
    p_oTargetTree = p_oTargetTree7;
    p_oTargetTree->GetValue(p_oPop->GetDiam10Code(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);

    fExpectedDiam = 1.899181664;
    p_oTargetTree = p_oTargetTree8;
    p_oTargetTree->GetValue(p_oPop->GetDiam10Code(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);

    delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

////////////////////////////////////////////////////////////////////////////
// WriteNCICompTempDepXMLFile1()
////////////////////////////////////////////////////////////////////////////
const char* WriteNCICompTempDepXMLFile1() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  //Write file
  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06010101\">"
       << "<plot>"
       << "<timesteps>3</timesteps>"
       << "<yearsPerTimestep>1</yearsPerTimestep>"
       << "<randomSeed>1</randomSeed>"
       << "<plot_lenX>200.0</plot_lenX>"
       << "<plot_lenY>200.0</plot_lenY>"
       << "<plot_latitude>55.37</plot_latitude>"
       << "<plot_precip_mm_yr>115</plot_precip_mm_yr>"
       << "<plot_temp_C>12.88</plot_temp_C>"
       << "<plot_n_dep>4.76</plot_n_dep>"
       << "<plot_seasonal_precipitation>1150.65</plot_seasonal_precipitation>"
       << "<plot_water_deficit>456.2</plot_water_deficit>"
       << "</plot>";

  WriteNCICompTempDepTreeStuff(oOut);

  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>NCIMasterGrowth</behaviorName>"
       << "<version>3</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_3\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_4\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_4\" type=\"Adult\"/>"
       << "</behavior>"
       << "</behaviorList>"
       << "<NCIMasterGrowth1>"
       << "<nciWhichShadingEffect>" << no_shading << "</nciWhichShadingEffect>"
       << "<nciWhichCrowdingEffect>" << default_crowding_effect << "</nciWhichCrowdingEffect>"
       << "<nciWhichNCITerm>" << nci_nci_temp_dep_ba_ratio << "</nciWhichNCITerm>"
       << "<nciWhichSizeEffect>" << no_size_effect << "</nciWhichSizeEffect>"
       << "<nciWhichDamageEffect>" << no_damage_effect << "</nciWhichDamageEffect>"
       << "<nciWhichPrecipitationEffect>" << no_precip_effect << "</nciWhichPrecipitationEffect>"
       << "<nciWhichTemperatureEffect>" << no_temp_effect << "</nciWhichTemperatureEffect>"
       << "<nciWhichNitrogenEffect>" << no_nitrogen_effect << "</nciWhichNitrogenEffect>"
       << "<nciWhichInfectionEffect>" << no_infection_effect << "</nciWhichInfectionEffect>"
       << "<gr_stochGrowthMethod>" << deterministic_pdf << "</gr_stochGrowthMethod>"
       << "<gr_nciMaxPotentialGrowth>"
       << "<gr_nmpgVal species=\"Species_2\">0.2574</gr_nmpgVal>"
       << "<gr_nmpgVal species=\"Species_3\">10</gr_nmpgVal>"
       << "<gr_nmpgVal species=\"Species_4\">5.4</gr_nmpgVal>"
       << "</gr_nciMaxPotentialGrowth>"
       << "<nciMaxAdultCrowdingRadius>10</nciMaxAdultCrowdingRadius>"
       << "<nciMaxSaplingCrowdingRadius>0</nciMaxSaplingCrowdingRadius>"
       << "<nciDbhAdjustor>0.1</nciDbhAdjustor>"
       << "<nciCrowdingC>"
       << "<nccVal species=\"Species_2\">0.953</nccVal>"
       << "<nccVal species=\"Species_3\">0.37</nccVal>"
       << "<nccVal species=\"Species_4\">0.321</nccVal>"
       << "</nciCrowdingC>"
       << "<nciCrowdingD>"
       << "<ncdVal species=\"Species_2\">0.62</ncdVal>"
       << "<ncdVal species=\"Species_3\">0.81</ncdVal>"
       << "<ncdVal species=\"Species_4\">0.4</ncdVal>"
       << "</nciCrowdingD>"
       << "<nciCrowdingGamma>"
       << "<ncgVal species=\"Species_2\">-0.15</ncgVal>"
       << "<ncgVal species=\"Species_3\">0.13</ncgVal>"
       << "<ncgVal species=\"Species_4\">0.461</ncgVal>"
       << "</nciCrowdingGamma>"
       << "<nciAlpha>"
       << "<naVal species=\"Species_2\">0.53</naVal>"
       << "<naVal species=\"Species_3\">1.2</naVal>"
       << "<naVal species=\"Species_4\">0.2</naVal>"
       << "</nciAlpha>"
       << "<nciBeta>"
       << "<nbVal species=\"Species_2\">1.63</nbVal>"
       << "<nbVal species=\"Species_3\">0.75</nbVal>"
       << "<nbVal species=\"Species_4\">0.6</nbVal>"
       << "</nciBeta>"
       << "<nciSpecies_1NeighborLambdaX0>"
       << "<nlX0Val species=\"Species_2\">279.46</nlX0Val>"
       << "<nlX0Val species=\"Species_3\">282.91</nlX0Val>"
       << "<nlX0Val species=\"Species_4\">272.4335</nlX0Val>"
       << "</nciSpecies_1NeighborLambdaX0>"
       << "<nciSpecies_2NeighborLambdaX0>"
       << "<nlX0Val species=\"Species_2\">279.46</nlX0Val>"
       << "<nlX0Val species=\"Species_3\">282.91</nlX0Val>"
       << "<nlX0Val species=\"Species_4\">272.4335</nlX0Val>"
       << "</nciSpecies_2NeighborLambdaX0>"
       << "<nciSpecies_3NeighborLambdaX0>"
       << "<nlX0Val species=\"Species_2\">285.34</nlX0Val>"
       << "<nlX0Val species=\"Species_3\">283.66</nlX0Val>"
       << "<nlX0Val species=\"Species_4\">277.8034</nlX0Val>"
       << "</nciSpecies_3NeighborLambdaX0>"
       << "<nciSpecies_4NeighborLambdaX0>"
       << "<nlX0Val species=\"Species_2\">282.48</nlX0Val>"
       << "<nlX0Val species=\"Species_3\">274.8733</nlX0Val>"
       << "<nlX0Val species=\"Species_4\">309.9974</nlX0Val>"
       << "</nciSpecies_4NeighborLambdaX0>"
       << "<nciSpecies_1NeighborLambdaXa>"
       << "<nlXaVal species=\"Species_2\">0.87</nlXaVal>"
       << "<nlXaVal species=\"Species_3\">0.3</nlXaVal>"
       << "<nlXaVal species=\"Species_4\">0.05103447</nlXaVal>"
       << "</nciSpecies_1NeighborLambdaXa>"
       << "<nciSpecies_2NeighborLambdaXa>"
       << "<nlXaVal species=\"Species_2\">0.87</nlXaVal>"
       << "<nlXaVal species=\"Species_3\">0.3</nlXaVal>"
       << "<nlXaVal species=\"Species_4\">0.05103447</nlXaVal>"
       << "</nciSpecies_2NeighborLambdaXa>"
       << "<nciSpecies_3NeighborLambdaXa>"
       << "<nlXaVal species=\"Species_2\">0.99</nlXaVal>"
       << "<nlXaVal species=\"Species_3\">0.65</nlXaVal>"
       << "<nlXaVal species=\"Species_4\">0.06603158</nlXaVal>"
       << "</nciSpecies_3NeighborLambdaXa>"
       << "<nciSpecies_4NeighborLambdaXa>"
       << "<nlXaVal species=\"Species_2\">0.9</nlXaVal>"
       << "<nlXaVal species=\"Species_3\">0.2580891</nlXaVal>"
       << "<nlXaVal species=\"Species_4\">0.07445122</nlXaVal>"
       << "</nciSpecies_4NeighborLambdaXa>"
       << "<nciSpecies_1NeighborLambdaXb>"
       << "<nlXbVal species=\"Species_2\">2.4</nlXbVal>"
       << "<nlXbVal species=\"Species_3\">17.34661</nlXbVal>"
       << "<nlXbVal species=\"Species_4\">6.790175</nlXbVal>"
       << "</nciSpecies_1NeighborLambdaXb>"
       << "<nciSpecies_2NeighborLambdaXb>"
       << "<nlXbVal species=\"Species_2\">2.4</nlXbVal>"
       << "<nlXbVal species=\"Species_3\">17.34661</nlXbVal>"
       << "<nlXbVal species=\"Species_4\">6.790175</nlXbVal>"
       << "</nciSpecies_2NeighborLambdaXb>"
       << "<nciSpecies_3NeighborLambdaXb>"
       << "<nlXbVal species=\"Species_2\">5.6</nlXbVal>"
       << "<nlXbVal species=\"Species_3\">1.4</nlXbVal>"
       << "<nlXbVal species=\"Species_4\">2.912006</nlXbVal>"
       << "</nciSpecies_3NeighborLambdaXb>"
       << "<nciSpecies_4NeighborLambdaXb>"
       << "<nlXbVal species=\"Species_2\">2.5</nlXbVal>"
       << "<nlXbVal species=\"Species_3\">2.25</nlXbVal>"
       << "<nlXbVal species=\"Species_4\">44.80562</nlXbVal>"
       << "</nciSpecies_4NeighborLambdaXb>"
       << "<nciMinNeighborDBH>"
       << "<nmndVal species=\"Species_1\">0</nmndVal>"
       << "<nmndVal species=\"Species_2\">0</nmndVal>"
       << "<nmndVal species=\"Species_3\">0</nmndVal>"
       << "<nmndVal species=\"Species_4\">0</nmndVal>"
       << "</nciMinNeighborDBH>"
       << "</NCIMasterGrowth1>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteNCICompTempDepXMLFile2()
////////////////////////////////////////////////////////////////////////////
const char* WriteNCICompTempDepXMLFile2() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  //Write file
  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06010101\">"
       << "<plot>"
       << "<timesteps>3</timesteps>"
       << "<yearsPerTimestep>1</yearsPerTimestep>"
       << "<randomSeed>1</randomSeed>"
       << "<plot_lenX>200.0</plot_lenX>"
       << "<plot_lenY>200.0</plot_lenY>"
       << "<plot_latitude>55.37</plot_latitude>"
       << "<plot_precip_mm_yr>115</plot_precip_mm_yr>"
       << "<plot_temp_C>12.88</plot_temp_C>"
       << "<plot_n_dep>4.76</plot_n_dep>"
       << "<plot_seasonal_precipitation>1150.65</plot_seasonal_precipitation>"
       << "<plot_water_deficit>456.2</plot_water_deficit>"
       << "</plot>";

  WriteNCICompTempDepTreeStuff(oOut);

  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>NCIMasterGrowth</behaviorName>"
       << "<version>3</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_3\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_4\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_4\" type=\"Adult\"/>"
       << "</behavior>"
       << "</behaviorList>"
       << "<NCIMasterGrowth1>"
       << "<nciWhichShadingEffect>" << no_shading << "</nciWhichShadingEffect>"
       << "<nciWhichCrowdingEffect>" << crowding_effect_temp_dep << "</nciWhichCrowdingEffect>"
       << "<nciWhichNCITerm>" << nci_nci_ba_ratio << "</nciWhichNCITerm>"
       << "<nciWhichSizeEffect>" << no_size_effect << "</nciWhichSizeEffect>"
       << "<nciWhichDamageEffect>" << no_damage_effect << "</nciWhichDamageEffect>"
       << "<nciWhichPrecipitationEffect>" << no_precip_effect << "</nciWhichPrecipitationEffect>"
       << "<nciWhichTemperatureEffect>" << no_temp_effect << "</nciWhichTemperatureEffect>"
       << "<nciWhichNitrogenEffect>" << no_nitrogen_effect << "</nciWhichNitrogenEffect>"
       << "<nciWhichInfectionEffect>" << no_infection_effect << "</nciWhichInfectionEffect>"
       << "<gr_stochGrowthMethod>" << deterministic_pdf << "</gr_stochGrowthMethod>"
       << "<gr_nciMaxPotentialGrowth>"
       << "<gr_nmpgVal species=\"Species_2\">0.2574</gr_nmpgVal>"
       << "<gr_nmpgVal species=\"Species_3\">10</gr_nmpgVal>"
       << "<gr_nmpgVal species=\"Species_4\">5.4</gr_nmpgVal>"
       << "</gr_nciMaxPotentialGrowth>"
       << "<nciMaxAdultCrowdingRadius>10</nciMaxAdultCrowdingRadius>"
       << "<nciMaxSaplingCrowdingRadius>5</nciMaxSaplingCrowdingRadius>"
       << "<nciDbhAdjustor>5</nciDbhAdjustor>"
       << "<nciCrowdingC>"
       << "<nccVal species=\"Species_2\">0.953</nccVal>"
       << "<nccVal species=\"Species_3\">0.37</nccVal>"
       << "<nccVal species=\"Species_4\">0.321</nccVal>"
       << "</nciCrowdingC>"
       << "<nciCrowdingCX0>"
       << "<nccx0Val species=\"Species_2\">283</nccx0Val>"
       << "<nccx0Val species=\"Species_3\">276</nccx0Val>"
       << "<nccx0Val species=\"Species_4\">235</nccx0Val>"
       << "</nciCrowdingCX0>"
       << "<nciCrowdingCXb>"
       << "<nccxbVal species=\"Species_2\">3.2</nccxbVal>"
       << "<nccxbVal species=\"Species_3\">2</nccxbVal>"
       << "<nccxbVal species=\"Species_4\">1</nccxbVal>"
       << "</nciCrowdingCXb>"
       << "<nciCrowdingD>"
       << "<ncdVal species=\"Species_2\">0.62</ncdVal>"
       << "<ncdVal species=\"Species_3\">0.81</ncdVal>"
       << "<ncdVal species=\"Species_4\">0.4</ncdVal>"
       << "</nciCrowdingD>"
       << "<nciCrowdingGamma>"
       << "<ncgVal species=\"Species_2\">-0.15</ncgVal>"
       << "<ncgVal species=\"Species_3\">0.13</ncgVal>"
       << "<ncgVal species=\"Species_4\">0.461</ncgVal>"
       << "</nciCrowdingGamma>"
       << "<nciAlpha>"
       << "<naVal species=\"Species_2\">0.53</naVal>"
       << "<naVal species=\"Species_3\">1.2</naVal>"
       << "<naVal species=\"Species_4\">0.2</naVal>"
       << "</nciAlpha>"
       << "<nciBeta>"
       << "<nbVal species=\"Species_2\">1.63</nbVal>"
       << "<nbVal species=\"Species_3\">0.75</nbVal>"
       << "<nbVal species=\"Species_4\">0.6</nbVal>"
       << "</nciBeta>"
       << "<nciSpecies_1NeighborLambda>"
       << "<nlVal species=\"Species_2\">0.87</nlVal>"
       << "<nlVal species=\"Species_3\">0.3</nlVal>"
       << "<nlVal species=\"Species_4\">0.5103447</nlVal>"
       << "</nciSpecies_1NeighborLambda>"
       << "<nciSpecies_2NeighborLambda>"
       << "<nlVal species=\"Species_2\">0.87</nlVal>"
       << "<nlVal species=\"Species_3\">0.3</nlVal>"
       << "<nlVal species=\"Species_4\">0.5103447</nlVal>"
       << "</nciSpecies_2NeighborLambda>"
       << "<nciSpecies_3NeighborLambda>"
       << "<nlVal species=\"Species_2\">0.99</nlVal>"
       << "<nlVal species=\"Species_3\">0.65</nlVal>"
       << "<nlVal species=\"Species_4\">0.6603158</nlVal>"
       << "</nciSpecies_3NeighborLambda>"
       << "<nciSpecies_4NeighborLambda>"
       << "<nlVal species=\"Species_2\">0.9</nlVal>"
       << "<nlVal species=\"Species_3\">0.2580891</nlVal>"
       << "<nlVal species=\"Species_4\">0.7445122</nlVal>"
       << "</nciSpecies_4NeighborLambda>"
       << "<nciMinNeighborDBH>"
       << "<nmndVal species=\"Species_1\">0</nmndVal>"
       << "<nmndVal species=\"Species_2\">0</nmndVal>"
       << "<nmndVal species=\"Species_3\">0</nmndVal>"
       << "<nmndVal species=\"Species_4\">0</nmndVal>"
       << "</nciMinNeighborDBH>"
       << "</NCIMasterGrowth1>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}


////////////////////////////////////////////////////////////////////////////
// WriteNCICompTempDepXMLFile3()
////////////////////////////////////////////////////////////////////////////
const char* WriteNCICompTempDepXMLFile3() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  //Write file
  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06010101\">"
       << "<plot>"
       << "<timesteps>3</timesteps>"
       << "<yearsPerTimestep>1</yearsPerTimestep>"
       << "<randomSeed>1</randomSeed>"
       << "<plot_lenX>200.0</plot_lenX>"
       << "<plot_lenY>200.0</plot_lenY>"
       << "<plot_latitude>55.37</plot_latitude>"
       << "<plot_precip_mm_yr>115</plot_precip_mm_yr>"
       << "<plot_temp_C>12.88</plot_temp_C>"
       << "<plot_n_dep>4.76</plot_n_dep>"
       << "<plot_seasonal_precipitation>1150.65</plot_seasonal_precipitation>"
       << "<plot_water_deficit>456.2</plot_water_deficit>"
       << "</plot>";

  WriteNCICompTempDepTreeStuff(oOut);

  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>NCIMasterGrowth</behaviorName>"
       << "<version>3</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_3\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_4\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_4\" type=\"Adult\"/>"
       << "</behavior>"
       << "</behaviorList>"
       << "<NCIMasterGrowth1>"
       << "<nciWhichShadingEffect>" << no_shading << "</nciWhichShadingEffect>"
       << "<nciWhichCrowdingEffect>" << crowding_effect_temp_dep << "</nciWhichCrowdingEffect>"
       << "<nciWhichNCITerm>" << nci_nci_temp_dep_ba_ratio << "</nciWhichNCITerm>"
       << "<nciWhichSizeEffect>" << no_size_effect << "</nciWhichSizeEffect>"
       << "<nciWhichDamageEffect>" << no_damage_effect << "</nciWhichDamageEffect>"
       << "<nciWhichPrecipitationEffect>" << no_precip_effect << "</nciWhichPrecipitationEffect>"
       << "<nciWhichTemperatureEffect>" << no_temp_effect << "</nciWhichTemperatureEffect>"
       << "<nciWhichNitrogenEffect>" << no_nitrogen_effect << "</nciWhichNitrogenEffect>"
       << "<nciWhichInfectionEffect>" << no_infection_effect << "</nciWhichInfectionEffect>"
       << "<gr_stochGrowthMethod>" << deterministic_pdf << "</gr_stochGrowthMethod>"
       << "<gr_nciMaxPotentialGrowth>"
       << "<gr_nmpgVal species=\"Species_2\">0.2574</gr_nmpgVal>"
       << "<gr_nmpgVal species=\"Species_3\">10</gr_nmpgVal>"
       << "<gr_nmpgVal species=\"Species_4\">5.4</gr_nmpgVal>"
       << "</gr_nciMaxPotentialGrowth>"
       << "<nciMaxAdultCrowdingRadius>10</nciMaxAdultCrowdingRadius>"
       << "<nciMaxSaplingCrowdingRadius>0</nciMaxSaplingCrowdingRadius>"
       << "<nciDbhAdjustor>1</nciDbhAdjustor>"
       << "<nciCrowdingC>"
       << "<nccVal species=\"Species_2\">0.953</nccVal>"
       << "<nccVal species=\"Species_3\">0.37</nccVal>"
       << "<nccVal species=\"Species_4\">0.321</nccVal>"
       << "</nciCrowdingC>"
       << "<nciCrowdingCX0>"
       << "<nccx0Val species=\"Species_2\">283</nccx0Val>"
       << "<nccx0Val species=\"Species_3\">276</nccx0Val>"
       << "<nccx0Val species=\"Species_4\">279</nccx0Val>"
       << "</nciCrowdingCX0>"
       << "<nciCrowdingCXb>"
       << "<nccxbVal species=\"Species_2\">3.2</nccxbVal>"
       << "<nccxbVal species=\"Species_3\">2</nccxbVal>"
       << "<nccxbVal species=\"Species_4\">1</nccxbVal>"
       << "</nciCrowdingCXb>"
       << "<nciCrowdingD>"
       << "<ncdVal species=\"Species_2\">0.62</ncdVal>"
       << "<ncdVal species=\"Species_3\">0.81</ncdVal>"
       << "<ncdVal species=\"Species_4\">0.4</ncdVal>"
       << "</nciCrowdingD>"
       << "<nciCrowdingGamma>"
       << "<ncgVal species=\"Species_2\">-0.15</ncgVal>"
       << "<ncgVal species=\"Species_3\">0.13</ncgVal>"
       << "<ncgVal species=\"Species_4\">0.461</ncgVal>"
       << "</nciCrowdingGamma>"
       << "<nciAlpha>"
       << "<naVal species=\"Species_2\">0.53</naVal>"
       << "<naVal species=\"Species_3\">1.2</naVal>"
       << "<naVal species=\"Species_4\">0.2</naVal>"
       << "</nciAlpha>"
       << "<nciBeta>"
       << "<nbVal species=\"Species_2\">1.63</nbVal>"
       << "<nbVal species=\"Species_3\">0.75</nbVal>"
       << "<nbVal species=\"Species_4\">0.6</nbVal>"
       << "</nciBeta>"
       << "<nciSpecies_1NeighborLambdaX0>"
       << "<nlX0Val species=\"Species_2\">279.46</nlX0Val>"
       << "<nlX0Val species=\"Species_3\">282.91</nlX0Val>"
       << "<nlX0Val species=\"Species_4\">272.4335</nlX0Val>"
       << "</nciSpecies_1NeighborLambdaX0>"
       << "<nciSpecies_2NeighborLambdaX0>"
       << "<nlX0Val species=\"Species_2\">279.46</nlX0Val>"
       << "<nlX0Val species=\"Species_3\">282.91</nlX0Val>"
       << "<nlX0Val species=\"Species_4\">272.4335</nlX0Val>"
       << "</nciSpecies_2NeighborLambdaX0>"
       << "<nciSpecies_3NeighborLambdaX0>"
       << "<nlX0Val species=\"Species_2\">285.34</nlX0Val>"
       << "<nlX0Val species=\"Species_3\">283.66</nlX0Val>"
       << "<nlX0Val species=\"Species_4\">277.8034</nlX0Val>"
       << "</nciSpecies_3NeighborLambdaX0>"
       << "<nciSpecies_4NeighborLambdaX0>"
       << "<nlX0Val species=\"Species_2\">282.48</nlX0Val>"
       << "<nlX0Val species=\"Species_3\">274.8733</nlX0Val>"
       << "<nlX0Val species=\"Species_4\">309.9974</nlX0Val>"
       << "</nciSpecies_4NeighborLambdaX0>"
       << "<nciSpecies_1NeighborLambdaXa>"
       << "<nlXaVal species=\"Species_2\">0.87</nlXaVal>"
       << "<nlXaVal species=\"Species_3\">0.3</nlXaVal>"
       << "<nlXaVal species=\"Species_4\">0.05103447</nlXaVal>"
       << "</nciSpecies_1NeighborLambdaXa>"
       << "<nciSpecies_2NeighborLambdaXa>"
       << "<nlXaVal species=\"Species_2\">0.87</nlXaVal>"
       << "<nlXaVal species=\"Species_3\">0.3</nlXaVal>"
       << "<nlXaVal species=\"Species_4\">0.05103447</nlXaVal>"
       << "</nciSpecies_2NeighborLambdaXa>"
       << "<nciSpecies_3NeighborLambdaXa>"
       << "<nlXaVal species=\"Species_2\">0.99</nlXaVal>"
       << "<nlXaVal species=\"Species_3\">0.65</nlXaVal>"
       << "<nlXaVal species=\"Species_4\">0.06603158</nlXaVal>"
       << "</nciSpecies_3NeighborLambdaXa>"
       << "<nciSpecies_4NeighborLambdaXa>"
       << "<nlXaVal species=\"Species_2\">0.9</nlXaVal>"
       << "<nlXaVal species=\"Species_3\">0.2580891</nlXaVal>"
       << "<nlXaVal species=\"Species_4\">0.07445122</nlXaVal>"
       << "</nciSpecies_4NeighborLambdaXa>"
       << "<nciSpecies_1NeighborLambdaXb>"
       << "<nlXbVal species=\"Species_2\">2.4</nlXbVal>"
       << "<nlXbVal species=\"Species_3\">17.34661</nlXbVal>"
       << "<nlXbVal species=\"Species_4\">6.790175</nlXbVal>"
       << "</nciSpecies_1NeighborLambdaXb>"
       << "<nciSpecies_2NeighborLambdaXb>"
       << "<nlXbVal species=\"Species_2\">2.4</nlXbVal>"
       << "<nlXbVal species=\"Species_3\">17.34661</nlXbVal>"
       << "<nlXbVal species=\"Species_4\">6.790175</nlXbVal>"
       << "</nciSpecies_2NeighborLambdaXb>"
       << "<nciSpecies_3NeighborLambdaXb>"
       << "<nlXbVal species=\"Species_2\">5.6</nlXbVal>"
       << "<nlXbVal species=\"Species_3\">1.4</nlXbVal>"
       << "<nlXbVal species=\"Species_4\">2.912006</nlXbVal>"
       << "</nciSpecies_3NeighborLambdaXb>"
       << "<nciSpecies_4NeighborLambdaXb>"
       << "<nlXbVal species=\"Species_2\">2.5</nlXbVal>"
       << "<nlXbVal species=\"Species_3\">2.25</nlXbVal>"
       << "<nlXbVal species=\"Species_4\">44.80562</nlXbVal>"
       << "</nciSpecies_4NeighborLambdaXb>"
       << "<nciMinNeighborDBH>"
       << "<nmndVal species=\"Species_1\">0</nmndVal>"
       << "<nmndVal species=\"Species_2\">0</nmndVal>"
       << "<nmndVal species=\"Species_3\">0</nmndVal>"
       << "<nmndVal species=\"Species_4\">0</nmndVal>"
       << "</nciMinNeighborDBH>"
       << "</NCIMasterGrowth1>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}


////////////////////////////////////////////////////////////////////////////
// WriteNCICompTempDepXMLFile4()
////////////////////////////////////////////////////////////////////////////
const char* WriteNCICompTempDepXMLFile4() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  //Write file
  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06010101\">"
       << "<plot>"
       << "<timesteps>3</timesteps>"
       << "<yearsPerTimestep>1</yearsPerTimestep>"
       << "<randomSeed>1</randomSeed>"
       << "<plot_lenX>200.0</plot_lenX>"
       << "<plot_lenY>200.0</plot_lenY>"
       << "<plot_latitude>55.37</plot_latitude>"
       << "<plot_precip_mm_yr>115</plot_precip_mm_yr>"
       << "<plot_temp_C>12.88</plot_temp_C>"
       << "<plot_n_dep>4.76</plot_n_dep>"
       << "<plot_seasonal_precipitation>1150.65</plot_seasonal_precipitation>"
       << "<plot_water_deficit>456.2</plot_water_deficit>"
       << "</plot>"
       << "<grid gridName=\"NCI Quadrat Growth\">"
       << "<ma_floatCodes>"
       << "<ma_floatCode label=\"growth_0\">0</ma_floatCode>"
       << "<ma_floatCode label=\"growth_1\">1</ma_floatCode>"
       << "<ma_floatCode label=\"growth_2\">2</ma_floatCode>"
       << "<ma_floatCode label=\"growth_3\">3</ma_floatCode>"
       << "</ma_floatCodes>"
       << "<ma_lengthXCells>2</ma_lengthXCells>"
       << "<ma_lengthYCells>2</ma_lengthYCells>"
       << "</grid>";

  WriteNCICompTempDepTreeStuff(oOut);

  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>NCIMasterQuadratGrowth</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_2\" type=\"Seedling\"/>"
       << "<applyTo species=\"Species_3\" type=\"Seedling\"/>"
       << "<applyTo species=\"Species_4\" type=\"Seedling\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>StochasticMortality</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>2</listPosition>"
       << "<applyTo species=\"Species_3\" type=\"Seedling\"/>"
       << "<applyTo species=\"Species_2\" type=\"Seedling\"/>"
       << "<applyTo species=\"Species_4\" type=\"Seedling\"/>"
       << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_4\" type=\"Adult\"/>"
       << "</behavior>"
       << "</behaviorList>"
       << "<NCIMasterQuadratGrowth1>"
       << "<nciWhichShadingEffect>" << no_shading << "</nciWhichShadingEffect>"
       << "<nciWhichCrowdingEffect>" << crowding_effect_temp_dep << "</nciWhichCrowdingEffect>"
       << "<nciWhichNCITerm>" << nci_nci_temp_dep_ba_ratio_ba_default << "</nciWhichNCITerm>"
       << "<nciWhichSizeEffect>" << no_size_effect << "</nciWhichSizeEffect>"
       << "<nciWhichDamageEffect>" << no_damage_effect << "</nciWhichDamageEffect>"
       << "<nciWhichPrecipitationEffect>" << no_precip_effect << "</nciWhichPrecipitationEffect>"
       << "<nciWhichTemperatureEffect>" << no_temp_effect << "</nciWhichTemperatureEffect>"
       << "<nciWhichNitrogenEffect>" << no_nitrogen_effect << "</nciWhichNitrogenEffect>"
       << "<nciWhichInfectionEffect>" << no_infection_effect << "</nciWhichInfectionEffect>"
       << "<gr_stochGrowthMethod>" << deterministic_pdf << "</gr_stochGrowthMethod>"
       << "<gr_nciMaxPotentialGrowth>"
       << "<gr_nmpgVal species=\"Species_2\">0.2574</gr_nmpgVal>"
       << "<gr_nmpgVal species=\"Species_3\">10</gr_nmpgVal>"
       << "<gr_nmpgVal species=\"Species_4\">5.4</gr_nmpgVal>"
       << "</gr_nciMaxPotentialGrowth>"
       << "<nciMaxAdultCrowdingRadius>10</nciMaxAdultCrowdingRadius>"
       << "<nciMaxSaplingCrowdingRadius>5</nciMaxSaplingCrowdingRadius>"
       << "<nciDbhAdjustor>1</nciDbhAdjustor>"
       << "<nciBADefaultDBH>1</nciBADefaultDBH>"
       << "<nciCrowdingC>"
       << "<nccVal species=\"Species_2\">0.953</nccVal>"
       << "<nccVal species=\"Species_3\">0.37</nccVal>"
       << "<nccVal species=\"Species_4\">0.321</nccVal>"
       << "</nciCrowdingC>"
       << "<nciCrowdingCX0>"
       << "<nccx0Val species=\"Species_2\">283</nccx0Val>"
       << "<nccx0Val species=\"Species_3\">276</nccx0Val>"
       << "<nccx0Val species=\"Species_4\">279</nccx0Val>"
       << "</nciCrowdingCX0>"
       << "<nciCrowdingCXb>"
       << "<nccxbVal species=\"Species_2\">3.2</nccxbVal>"
       << "<nccxbVal species=\"Species_3\">2</nccxbVal>"
       << "<nccxbVal species=\"Species_4\">1</nccxbVal>"
       << "</nciCrowdingCXb>"
       << "<nciCrowdingD>"
       << "<ncdVal species=\"Species_2\">0.62</ncdVal>"
       << "<ncdVal species=\"Species_3\">0.81</ncdVal>"
       << "<ncdVal species=\"Species_4\">0.4</ncdVal>"
       << "</nciCrowdingD>"
       << "<nciCrowdingGamma>"
       << "<ncgVal species=\"Species_2\">-0.15</ncgVal>"
       << "<ncgVal species=\"Species_3\">0.13</ncgVal>"
       << "<ncgVal species=\"Species_4\">0.461</ncgVal>"
       << "</nciCrowdingGamma>"
       << "<nciAlpha>"
       << "<naVal species=\"Species_2\">0.53</naVal>"
       << "<naVal species=\"Species_3\">1.2</naVal>"
       << "<naVal species=\"Species_4\">0.2</naVal>"
       << "</nciAlpha>"
       << "<nciBeta>"
       << "<nbVal species=\"Species_2\">1.63</nbVal>"
       << "<nbVal species=\"Species_3\">0.75</nbVal>"
       << "<nbVal species=\"Species_4\">0.6</nbVal>"
       << "</nciBeta>"
       << "<nciSpecies_1NeighborLambdaX0>"
       << "<nlX0Val species=\"Species_2\">279.46</nlX0Val>"
       << "<nlX0Val species=\"Species_3\">282.91</nlX0Val>"
       << "<nlX0Val species=\"Species_4\">272.4335</nlX0Val>"
       << "</nciSpecies_1NeighborLambdaX0>"
       << "<nciSpecies_2NeighborLambdaX0>"
       << "<nlX0Val species=\"Species_2\">279.46</nlX0Val>"
       << "<nlX0Val species=\"Species_3\">282.91</nlX0Val>"
       << "<nlX0Val species=\"Species_4\">272.4335</nlX0Val>"
       << "</nciSpecies_2NeighborLambdaX0>"
       << "<nciSpecies_3NeighborLambdaX0>"
       << "<nlX0Val species=\"Species_2\">285.34</nlX0Val>"
       << "<nlX0Val species=\"Species_3\">283.66</nlX0Val>"
       << "<nlX0Val species=\"Species_4\">277.8034</nlX0Val>"
       << "</nciSpecies_3NeighborLambdaX0>"
       << "<nciSpecies_4NeighborLambdaX0>"
       << "<nlX0Val species=\"Species_2\">282.48</nlX0Val>"
       << "<nlX0Val species=\"Species_3\">274.8733</nlX0Val>"
       << "<nlX0Val species=\"Species_4\">309.9974</nlX0Val>"
       << "</nciSpecies_4NeighborLambdaX0>"
       << "<nciSpecies_1NeighborLambdaXa>"
       << "<nlXaVal species=\"Species_2\">0.87</nlXaVal>"
       << "<nlXaVal species=\"Species_3\">0.3</nlXaVal>"
       << "<nlXaVal species=\"Species_4\">0.05103447</nlXaVal>"
       << "</nciSpecies_1NeighborLambdaXa>"
       << "<nciSpecies_2NeighborLambdaXa>"
       << "<nlXaVal species=\"Species_2\">0.87</nlXaVal>"
       << "<nlXaVal species=\"Species_3\">0.3</nlXaVal>"
       << "<nlXaVal species=\"Species_4\">0.05103447</nlXaVal>"
       << "</nciSpecies_2NeighborLambdaXa>"
       << "<nciSpecies_3NeighborLambdaXa>"
       << "<nlXaVal species=\"Species_2\">0.99</nlXaVal>"
       << "<nlXaVal species=\"Species_3\">0.65</nlXaVal>"
       << "<nlXaVal species=\"Species_4\">0.06603158</nlXaVal>"
       << "</nciSpecies_3NeighborLambdaXa>"
       << "<nciSpecies_4NeighborLambdaXa>"
       << "<nlXaVal species=\"Species_2\">0.9</nlXaVal>"
       << "<nlXaVal species=\"Species_3\">0.2580891</nlXaVal>"
       << "<nlXaVal species=\"Species_4\">0.07445122</nlXaVal>"
       << "</nciSpecies_4NeighborLambdaXa>"
       << "<nciSpecies_1NeighborLambdaXb>"
       << "<nlXbVal species=\"Species_2\">2.4</nlXbVal>"
       << "<nlXbVal species=\"Species_3\">17.34661</nlXbVal>"
       << "<nlXbVal species=\"Species_4\">6.790175</nlXbVal>"
       << "</nciSpecies_1NeighborLambdaXb>"
       << "<nciSpecies_2NeighborLambdaXb>"
       << "<nlXbVal species=\"Species_2\">2.4</nlXbVal>"
       << "<nlXbVal species=\"Species_3\">17.34661</nlXbVal>"
       << "<nlXbVal species=\"Species_4\">6.790175</nlXbVal>"
       << "</nciSpecies_2NeighborLambdaXb>"
       << "<nciSpecies_3NeighborLambdaXb>"
       << "<nlXbVal species=\"Species_2\">5.6</nlXbVal>"
       << "<nlXbVal species=\"Species_3\">1.4</nlXbVal>"
       << "<nlXbVal species=\"Species_4\">2.912006</nlXbVal>"
       << "</nciSpecies_3NeighborLambdaXb>"
       << "<nciSpecies_4NeighborLambdaXb>"
       << "<nlXbVal species=\"Species_2\">2.5</nlXbVal>"
       << "<nlXbVal species=\"Species_3\">2.25</nlXbVal>"
       << "<nlXbVal species=\"Species_4\">44.80562</nlXbVal>"
       << "</nciSpecies_4NeighborLambdaXb>"
       << "<nciMinNeighborDBH>"
       << "<nmndVal species=\"Species_1\">0</nmndVal>"
       << "<nmndVal species=\"Species_2\">0</nmndVal>"
       << "<nmndVal species=\"Species_3\">0</nmndVal>"
       << "<nmndVal species=\"Species_4\">0</nmndVal>"
       << "</nciMinNeighborDBH>"
       << "</NCIMasterQuadratGrowth1>"
       << "<StochasticMortality2>"
       << "<mo_stochasticMortRate>"
       << "<mo_smrVal species=\"Species_3\">0</mo_smrVal>"
       << "<mo_smrVal species=\"Species_1\">0</mo_smrVal>"
       << "<mo_smrVal species=\"Species_2\">0</mo_smrVal>"
       << "<mo_smrVal species=\"Species_4\">0</mo_smrVal>"
       << "</mo_stochasticMortRate>"
       << "</StochasticMortality2>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}


/////////////////////////////////////////////////////////////////////////////
// WriteNCICompTempDepTreeStuff()
/////////////////////////////////////////////////////////////////////////////
void WriteNCICompTempDepTreeStuff(std::fstream &oOut) {
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
       << "<tr_cdtdVal species=\"Species_1\">1.0</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_2\">1.0</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_3\">1.0</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_4\">1.0</tr_cdtdVal>"
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
       << "<tr_sohdVal species=\"Species_1\">0.02</tr_sohdVal>"
       << "<tr_sohdVal species=\"Species_2\">0.02</tr_sohdVal>"
       << "<tr_sohdVal species=\"Species_3\">0.02</tr_sohdVal>"
       << "<tr_sohdVal species=\"Species_4\">0.02</tr_sohdVal>"
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

