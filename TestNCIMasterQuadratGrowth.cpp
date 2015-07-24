//---------------------------------------------------------------------------
// TestNCIMasterQuadratGrowth.cpp
//---------------------------------------------------------------------------
#include "TestNCIMasterQuadratGrowth.h"
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
TEST(NCIMasterQuadratGrowth, TestErrorProcessing) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );

  try {
    p_oSimManager->ReadFile(WriteNCIQuadratGrowthXMLErrorFile1());
    FAIL() << "TestNCIQuadratGrowth error processing didn't catch error for WriteNCIQuadratGrowthXMLErrorFile1.";
  } catch (modelErr& err) {
    if (err.sFunction.compare("clNCIMasterQuadratGrowth::ValidateData") != 0) {
      FAIL() << "TestNCIQuadratGrowth error processing caught wrong error for WriteNCIQuadratGrowthXMLErrorFile1.";
    };
  }

  delete p_oSimManager;
}

////////////////////////////////////////////////////////////////////////////
// TestRun1()
// Performs a test run of growth for a 1-year timestep.
////////////////////////////////////////////////////////////////////////////
TEST(NCIMasterQuadratGrowth, TestRun1) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    clTreePopulation * p_oPop;
    clTreeSearch *p_oAllTrees;
    clTree *p_oTargetTree1, *p_oTargetTree2, *p_oTargetTree3, *p_oTargetTree4,
    *p_oTargetTree5, *p_oTargetTree6, *p_oTargetTree7, *p_oTargetTree8,
    *p_oTargetTree9, *p_oTargetTree10, *p_oTargetTree;
    float fDiam, fExpectedDiam, fGrowth, fExpectedGrowth;
    int iSpecies;

    //Load our test file and get our tree population pointers
    p_oSimManager->ReadFile(WriteNCIQuadratGrowthXMLFile(1, 0));
    p_oPop = (clTreePopulation *) p_oSimManager->GetPopulationObject(
        "treepopulation");

    //Create our trees
    fDiam = 0.5;
    iSpecies = 1;
    p_oTargetTree1 = p_oPop->CreateTree(51, 53, iSpecies,
        clTreePopulation::seedling, fDiam);

    fDiam = 0.6;
    iSpecies = 1;
    p_oTargetTree2 = p_oPop->CreateTree(51.2, 54, iSpecies,
        clTreePopulation::seedling, fDiam);

    fDiam = 0.7;
    iSpecies = 2;
    p_oTargetTree3 = p_oPop->CreateTree(50.5, 61, iSpecies,
        clTreePopulation::seedling, fDiam);

    fDiam = 0.8;
    iSpecies = 3;
    p_oTargetTree4 = p_oPop->CreateTree(53, 51, iSpecies,
        clTreePopulation::seedling, fDiam);

    fDiam = 0.9;
    iSpecies = 1;
    p_oTargetTree5 = p_oPop->CreateTree(20.5, 20.5, iSpecies,
        clTreePopulation::seedling, fDiam);

    fDiam = 1;
    iSpecies = 2;
    p_oTargetTree6 = p_oPop->CreateTree(61, 50.5, iSpecies,
        clTreePopulation::seedling, fDiam);

    fDiam = 1.1;
    iSpecies = 3;
    p_oTargetTree7 = p_oPop->CreateTree(60, 50.5, iSpecies,
        clTreePopulation::seedling, fDiam);

    fDiam = 1.2;
    iSpecies = 1;
    p_oTargetTree8 = p_oPop->CreateTree(51, 53, iSpecies,
        clTreePopulation::seedling, fDiam);

    fDiam = 1.3;
    iSpecies = 2;
    p_oTargetTree9 = p_oPop->CreateTree(51.2, 54, iSpecies,
        clTreePopulation::seedling, fDiam);

    fDiam = 1.4;
    iSpecies = 3;
    p_oTargetTree10 = p_oPop->CreateTree(50.5, 61, iSpecies,
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

    //Now do the run
    p_oSimManager->RunSim(1);

    //Check the diameters and growth of the target trees
    fExpectedDiam = 1.333952493;
    fExpectedGrowth = 4.169762464;
    p_oTargetTree = p_oTargetTree1;
    p_oTargetTree->GetValue(p_oPop->GetDiam10Code(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    p_oTargetTree->GetValue(p_oPop->GetFloatDataCode("Growth",
        p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fGrowth);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);
    EXPECT_LT(fabs(fGrowth - fExpectedGrowth)/fGrowth, 0.001);

    fExpectedDiam = 1.433952493;
    fExpectedGrowth = 4.169762464;
    p_oTargetTree = p_oTargetTree2;
    p_oTargetTree->GetValue(p_oPop->GetDiam10Code(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    p_oTargetTree->GetValue(p_oPop->GetFloatDataCode("Growth",
        p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fGrowth);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);
    EXPECT_LT(fabs(fGrowth - fExpectedGrowth)/fGrowth, 0.001);

    fExpectedDiam = 0.788157234;
    fExpectedGrowth = 0.440786172;
    p_oTargetTree = p_oTargetTree3;
    p_oTargetTree->GetValue(p_oPop->GetDiam10Code(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    p_oTargetTree->GetValue(p_oPop->GetFloatDataCode("Growth",
        p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fGrowth);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);
    EXPECT_LT(fabs(fGrowth - fExpectedGrowth)/fGrowth, 0.001);

    fExpectedDiam = 1.540640151;
    fExpectedGrowth = 3.703200756;
    p_oTargetTree = p_oTargetTree4;
    p_oTargetTree->GetValue(p_oPop->GetDiam10Code(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    p_oTargetTree->GetValue(p_oPop->GetFloatDataCode("Growth",
        p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fGrowth);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);
    EXPECT_LT(fabs(fGrowth - fExpectedGrowth), 0.001);

    fExpectedDiam = 2.952572236;
    fExpectedGrowth = 10.26286118;
    p_oTargetTree = p_oTargetTree5;
    p_oTargetTree->GetValue(p_oPop->GetDiam10Code(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    p_oTargetTree->GetValue(p_oPop->GetFloatDataCode("Growth",
        p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fGrowth);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);
    EXPECT_LT(fabs(fGrowth - fExpectedGrowth)/fGrowth, 0.001);

    fExpectedDiam = 1.179024574;
    fExpectedGrowth = 0.89512287;
    p_oTargetTree = p_oTargetTree6;
    p_oTargetTree->GetValue(p_oPop->GetDiam10Code(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    p_oTargetTree->GetValue(p_oPop->GetFloatDataCode("Growth",
        p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fGrowth);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);
    EXPECT_LT(fabs(fGrowth - fExpectedGrowth)/fGrowth, 0.001);

    fExpectedDiam = 2.089921523;
    fExpectedGrowth = 4.949607615;
    p_oTargetTree = p_oTargetTree7;
    p_oTargetTree->GetValue(p_oPop->GetDiam10Code(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    p_oTargetTree->GetValue(p_oPop->GetFloatDataCode("Growth",
        p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fGrowth);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);
    EXPECT_LT(fabs(fGrowth - fExpectedGrowth), 0.001);

    fExpectedDiam = 2.033952493;
    fExpectedGrowth = 4.169762464;
    p_oTargetTree = p_oTargetTree8;
    p_oTargetTree->GetValue(p_oPop->GetDiam10Code(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    p_oTargetTree->GetValue(p_oPop->GetFloatDataCode("Growth",
        p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fGrowth);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);
    EXPECT_LT(fabs(fGrowth - fExpectedGrowth)/fGrowth, 0.001);

    fExpectedDiam = 1.342162069;
    fExpectedGrowth = 0.210810347;
    p_oTargetTree = p_oTargetTree9;
    p_oTargetTree->GetValue(p_oPop->GetDiam10Code(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    p_oTargetTree->GetValue(p_oPop->GetFloatDataCode("Growth",
        p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fGrowth);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);
    EXPECT_LT(fabs(fGrowth - fExpectedGrowth)/fGrowth, 0.001);

    fExpectedDiam = 2.251791411;
    fExpectedGrowth = 4.258957053;
    p_oTargetTree = p_oTargetTree10;
    p_oTargetTree->GetValue(p_oPop->GetDiam10Code(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    p_oTargetTree->GetValue(p_oPop->GetFloatDataCode("Growth",
        p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fGrowth);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);
    EXPECT_LT(fabs(fGrowth - fExpectedGrowth)/fGrowth, 0.001);

    //Kill all the adults
    p_oAllTrees = p_oPop->Find("all");
    p_oTargetTree = p_oAllTrees->NextTree();
    while (p_oTargetTree) {
      if (p_oTargetTree->GetType() == clTreePopulation::adult)
        p_oPop->KillTree(p_oTargetTree, remove_tree);
      p_oTargetTree = p_oAllTrees->NextTree();
    }

    p_oSimManager->RunSim(1);
    //Check the diameters and growth of the target trees
    fExpectedDiam = 3.386524729;
    p_oTargetTree = p_oTargetTree1;
    p_oTargetTree->GetValue(p_oPop->GetDiam10Code(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    p_oTargetTree->GetValue(p_oPop->GetFloatDataCode("Growth",
        p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fGrowth);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);

    fExpectedDiam = 3.486524729;
    p_oTargetTree = p_oTargetTree2;
    p_oTargetTree->GetValue(p_oPop->GetDiam10Code(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    p_oTargetTree->GetValue(p_oPop->GetFloatDataCode("Growth",
        p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fGrowth);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);

    fExpectedDiam = 1.858552291;
    p_oTargetTree = p_oTargetTree3;
    p_oTargetTree->GetValue(p_oPop->GetDiam10Code(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    p_oTargetTree->GetValue(p_oPop->GetFloatDataCode("Growth",
        p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fGrowth);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);

    fExpectedDiam = 3.452213299;
    p_oTargetTree = p_oTargetTree4;
    p_oTargetTree->GetValue(p_oPop->GetDiam10Code(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    p_oTargetTree->GetValue(p_oPop->GetFloatDataCode("Growth",
        p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fGrowth);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);

    fExpectedDiam = 5.005144473;
    p_oTargetTree = p_oTargetTree5;
    p_oTargetTree->GetValue(p_oPop->GetDiam10Code(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    p_oTargetTree->GetValue(p_oPop->GetFloatDataCode("Growth",
        p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fGrowth);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);

    fExpectedDiam = 2.249419631;
    p_oTargetTree = p_oTargetTree6;
    p_oTargetTree->GetValue(p_oPop->GetDiam10Code(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    p_oTargetTree->GetValue(p_oPop->GetFloatDataCode("Growth",
        p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fGrowth);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);

    fExpectedDiam = 4.001494671;
    p_oTargetTree = p_oTargetTree7;
    p_oTargetTree->GetValue(p_oPop->GetDiam10Code(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    p_oTargetTree->GetValue(p_oPop->GetFloatDataCode("Growth",
        p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fGrowth);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);

    fExpectedDiam = 4.086524729;
    p_oTargetTree = p_oTargetTree8;
    p_oTargetTree->GetValue(p_oPop->GetDiam10Code(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    p_oTargetTree->GetValue(p_oPop->GetFloatDataCode("Growth",
        p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fGrowth);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);

    fExpectedDiam = 2.412557126;
    p_oTargetTree = p_oTargetTree9;
    p_oTargetTree->GetValue(p_oPop->GetDiam10Code(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    p_oTargetTree->GetValue(p_oPop->GetFloatDataCode("Growth",
        p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fGrowth);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);

    fExpectedDiam = 4.163364558;
    p_oTargetTree = p_oTargetTree10;
    p_oTargetTree->GetValue(p_oPop->GetDiam10Code(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    p_oTargetTree->GetValue(p_oPop->GetFloatDataCode("Growth",
        p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fGrowth);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);
    delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

////////////////////////////////////////////////////////////////////////////
// TestRun2()
// Performs a test run of growth for a 3-year timestep.
////////////////////////////////////////////////////////////////////////////
TEST(NCIMasterQuadratGrowth, TestRun2) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    clTreePopulation * p_oPop;
    clTree *p_oTargetTree1, *p_oTargetTree2, *p_oTargetTree3, *p_oTargetTree4,
    *p_oTargetTree5, *p_oTargetTree6, *p_oTargetTree7, *p_oTargetTree8,
    *p_oTargetTree9, *p_oTargetTree10, *p_oTargetTree;
    float fDiam, fExpectedDiam, fGrowth, fExpectedGrowth;
    int iSpecies;

    //Load our test file and get our tree population pointers
    p_oSimManager->ReadFile(WriteNCIQuadratGrowthXMLFile(3, 0));
    p_oPop = (clTreePopulation *) p_oSimManager->GetPopulationObject(
        "treepopulation");

    //Create our trees
    fDiam = 0.5;
    iSpecies = 1;
    p_oTargetTree1 = p_oPop->CreateTree(51, 53, iSpecies,
        clTreePopulation::seedling, fDiam);

    fDiam = 0.6;
    iSpecies = 1;
    p_oTargetTree2 = p_oPop->CreateTree(51.2, 54, iSpecies,
        clTreePopulation::seedling, fDiam);

    fDiam = 0.7;
    iSpecies = 2;
    p_oTargetTree3 = p_oPop->CreateTree(50.5, 61, iSpecies,
        clTreePopulation::seedling, fDiam);

    fDiam = 0.8;
    iSpecies = 3;
    p_oTargetTree4 = p_oPop->CreateTree(53, 51, iSpecies,
        clTreePopulation::seedling, fDiam);

    fDiam = 0.9;
    iSpecies = 1;
    p_oTargetTree5 = p_oPop->CreateTree(20.5, 20.5, iSpecies,
        clTreePopulation::seedling, fDiam);

    fDiam = 1;
    iSpecies = 2;
    p_oTargetTree6 = p_oPop->CreateTree(61, 50.5, iSpecies,
        clTreePopulation::seedling, fDiam);

    fDiam = 1.1;
    iSpecies = 3;
    p_oTargetTree7 = p_oPop->CreateTree(60, 50.5, iSpecies,
        clTreePopulation::seedling, fDiam);

    fDiam = 1.2;
    iSpecies = 1;
    p_oTargetTree8 = p_oPop->CreateTree(51, 53, iSpecies,
        clTreePopulation::seedling, fDiam);

    fDiam = 1.3;
    iSpecies = 2;
    p_oTargetTree9 = p_oPop->CreateTree(51.2, 54, iSpecies,
        clTreePopulation::seedling, fDiam);

    fDiam = 1.4;
    iSpecies = 3;
    p_oTargetTree10 = p_oPop->CreateTree(50.5, 61, iSpecies,
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
        p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), insects);

    //Now do the run
    p_oSimManager->RunSim(1);

    //Check the diameters and growth of the target trees
    fExpectedDiam = 3.001857478;
    fExpectedGrowth = 4.169762464;
    p_oTargetTree = p_oTargetTree1;
    p_oTargetTree->GetValue(p_oPop->GetDiam10Code(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    p_oTargetTree->GetValue(p_oPop->GetFloatDataCode("Growth",
        p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fGrowth);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);
    EXPECT_LT(fabs(fGrowth - fExpectedGrowth)/fGrowth, 0.001);

    fExpectedDiam = 3.101857478;
    fExpectedGrowth = 4.169762464;
    p_oTargetTree = p_oTargetTree2;
    p_oTargetTree->GetValue(p_oPop->GetDiam10Code(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    p_oTargetTree->GetValue(p_oPop->GetFloatDataCode("Growth",
        p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fGrowth);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);
    EXPECT_LT(fabs(fGrowth - fExpectedGrowth)/fGrowth, 0.001);

    fExpectedDiam = 0.964471703;
    fExpectedGrowth = 0.440786172;
    p_oTargetTree = p_oTargetTree3;
    p_oTargetTree->GetValue(p_oPop->GetDiam10Code(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    p_oTargetTree->GetValue(p_oPop->GetFloatDataCode("Growth",
        p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fGrowth);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);
    EXPECT_LT(fabs(fGrowth - fExpectedGrowth)/fGrowth, 0.001);

    fExpectedDiam = 3.021920453;
    fExpectedGrowth = 3.703200756;
    p_oTargetTree = p_oTargetTree4;
    p_oTargetTree->GetValue(p_oPop->GetDiam10Code(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    p_oTargetTree->GetValue(p_oPop->GetFloatDataCode("Growth",
        p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fGrowth);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);
    EXPECT_LT(fabs(fGrowth - fExpectedGrowth), 0.001);

    fExpectedDiam = 7.057716709;
    fExpectedGrowth = 10.26286118;
    p_oTargetTree = p_oTargetTree5;
    p_oTargetTree->GetValue(p_oPop->GetDiam10Code(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    p_oTargetTree->GetValue(p_oPop->GetFloatDataCode("Growth",
        p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fGrowth);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);
    EXPECT_LT(fabs(fGrowth - fExpectedGrowth)/fGrowth, 0.001);

    fExpectedDiam = 1.537073722;
    fExpectedGrowth = 0.89512287;
    p_oTargetTree = p_oTargetTree6;
    p_oTargetTree->GetValue(p_oPop->GetDiam10Code(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    p_oTargetTree->GetValue(p_oPop->GetFloatDataCode("Growth",
        p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fGrowth);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);
    EXPECT_LT(fabs(fGrowth - fExpectedGrowth)/fGrowth, 0.001);

    fExpectedDiam = 4.069764569;
    fExpectedGrowth = 4.949607615;
    p_oTargetTree = p_oTargetTree7;
    p_oTargetTree->GetValue(p_oPop->GetDiam10Code(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    p_oTargetTree->GetValue(p_oPop->GetFloatDataCode("Growth",
        p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fGrowth);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);
    EXPECT_LT(fabs(fGrowth - fExpectedGrowth), 0.001);

    fExpectedDiam = 3.701857478;
    fExpectedGrowth = 4.169762464;
    p_oTargetTree = p_oTargetTree8;
    p_oTargetTree->GetValue(p_oPop->GetDiam10Code(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    p_oTargetTree->GetValue(p_oPop->GetFloatDataCode("Growth",
        p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fGrowth);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);
    EXPECT_LT(fabs(fGrowth - fExpectedGrowth)/fGrowth, 0.001);

    fExpectedDiam = 1.426486208;
    fExpectedGrowth = 0.210810347;
    p_oTargetTree = p_oTargetTree9;
    p_oTargetTree->GetValue(p_oPop->GetDiam10Code(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    p_oTargetTree->GetValue(p_oPop->GetFloatDataCode("Growth",
        p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fGrowth);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);
    EXPECT_LT(fabs(fGrowth - fExpectedGrowth)/fGrowth, 0.001);

    fExpectedDiam = 3.955374232;
    fExpectedGrowth = 4.258957053;
    p_oTargetTree = p_oTargetTree10;
    p_oTargetTree->GetValue(p_oPop->GetDiam10Code(p_oTargetTree->GetSpecies(),
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
// Performs a test run of growth for a run using water deficit.
////////////////////////////////////////////////////////////////////////////
TEST(NCIMasterQuadratGrowth, TestRun3) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    clTreePopulation * p_oPop;
    clTree *p_oTargetTree1, *p_oTargetTree2, *p_oTargetTree3, *p_oTargetTree4,
    *p_oTargetTree5, *p_oTargetTree6, *p_oTargetTree7, *p_oTargetTree8,
    *p_oTargetTree9, *p_oTargetTree10, *p_oTargetTree;
    float fDiam, fExpectedDiam;
    int iSpecies;

    //Load our test file and get our tree population pointers
    p_oSimManager->ReadFile(WriteNCIQuadratGrowthXMLFile(1, 2));
    p_oPop = (clTreePopulation *) p_oSimManager->GetPopulationObject(
        "treepopulation");

    //Create our trees
    fDiam = 0.5;
    iSpecies = 1;
    p_oTargetTree1 = p_oPop->CreateTree(51, 53, iSpecies,
        clTreePopulation::seedling, fDiam);

    fDiam = 0.6;
    iSpecies = 1;
    p_oTargetTree2 = p_oPop->CreateTree(51.2, 54, iSpecies,
        clTreePopulation::seedling, fDiam);

    fDiam = 0.7;
    iSpecies = 2;
    p_oTargetTree3 = p_oPop->CreateTree(50.5, 61, iSpecies,
        clTreePopulation::seedling, fDiam);

    fDiam = 0.8;
    iSpecies = 3;
    p_oTargetTree4 = p_oPop->CreateTree(53, 51, iSpecies,
        clTreePopulation::seedling, fDiam);

    fDiam = 0.9;
    iSpecies = 1;
    p_oTargetTree5 = p_oPop->CreateTree(20.5, 20.5, iSpecies,
        clTreePopulation::seedling, fDiam);

    fDiam = 1;
    iSpecies = 2;
    p_oTargetTree6 = p_oPop->CreateTree(61, 50.5, iSpecies,
        clTreePopulation::seedling, fDiam);

    fDiam = 1.1;
    iSpecies = 3;
    p_oTargetTree7 = p_oPop->CreateTree(60, 50.5, iSpecies,
        clTreePopulation::seedling, fDiam);

    fDiam = 1.2;
    iSpecies = 1;
    p_oTargetTree8 = p_oPop->CreateTree(51, 53, iSpecies,
        clTreePopulation::seedling, fDiam);

    fDiam = 1.3;
    iSpecies = 2;
    p_oTargetTree9 = p_oPop->CreateTree(51.2, 54, iSpecies,
        clTreePopulation::seedling, fDiam);

    fDiam = 1.4;
    iSpecies = 3;
    p_oTargetTree10 = p_oPop->CreateTree(50.5, 61, iSpecies,
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

    //Now do the run
    p_oSimManager->RunSim(1);

    //Check the diameters and growth of the target trees
    fExpectedDiam = 1.229484188;
    p_oTargetTree = p_oTargetTree1;
    p_oTargetTree->GetValue(p_oPop->GetDiam10Code(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);

    fExpectedDiam = 1.329484188;
    p_oTargetTree = p_oTargetTree2;
    p_oTargetTree->GetValue(p_oPop->GetDiam10Code(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);

    fExpectedDiam = 0.764772496;
    p_oTargetTree = p_oTargetTree3;
    p_oTargetTree->GetValue(p_oPop->GetDiam10Code(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);

    fExpectedDiam = 1.633677528;
    p_oTargetTree = p_oTargetTree4;
    p_oTargetTree->GetValue(p_oPop->GetDiam10Code(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);

    fExpectedDiam = 2.695448786;
    p_oTargetTree = p_oTargetTree5;
    p_oTargetTree->GetValue(p_oPop->GetDiam10Code(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);

    fExpectedDiam = 1.131536211;
    p_oTargetTree = p_oTargetTree6;
    p_oTargetTree->GetValue(p_oPop->GetDiam10Code(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);

    fExpectedDiam = 2.214273007;
    p_oTargetTree = p_oTargetTree7;
    p_oTargetTree->GetValue(p_oPop->GetDiam10Code(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);

    fExpectedDiam = 1.929484188;
    p_oTargetTree = p_oTargetTree8;
    p_oTargetTree->GetValue(p_oPop->GetDiam10Code(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);

    fExpectedDiam = 1.330978087;
    p_oTargetTree = p_oTargetTree9;
    p_oTargetTree->GetValue(p_oPop->GetDiam10Code(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);

    fExpectedDiam = 2.358791333;
    p_oTargetTree = p_oTargetTree10;
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
// TestRun4()
// Performs a test run of growth for a run using seasonal precipitation.
////////////////////////////////////////////////////////////////////////////
TEST(NCIMasterQuadratGrowth, TestRun4) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    clTreePopulation * p_oPop;
    clTree *p_oTree;
    float fDiam, fTotalDiam1 = 0, fTotalDiam2 = 0, fExpectedDiam;
    int iSpecies, i;

    //Load our test file and get our tree population pointers
    p_oSimManager->ReadFile(WriteNCIQuadratGrowthXMLFile2(1, 1));
    p_oPop = (clTreePopulation *) p_oSimManager->GetPopulationObject(
        "treepopulation");

    //Create our trees
    for (i = 0; i < 1000; i++) {
      fDiam = 0.5;
      iSpecies = 0;
      p_oPop->CreateTree(51, 53, iSpecies, clTreePopulation::seedling, fDiam);

      fDiam = 1;
      iSpecies = 1;
      p_oPop->CreateTree(51.2, 54, iSpecies, clTreePopulation::seedling, fDiam);
    }

    //Now do the run
    p_oSimManager->RunSim(1);

    //Check the mean diameter of the target trees
    clTreeSearch *p_oTrees = p_oPop->Find("all");
    p_oTree = p_oTrees->NextTree();
    while (p_oTree) {
      p_oTree->GetValue(p_oPop->GetDbhCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fDiam);
      if (0 == p_oTree->GetSpecies()) {
        fTotalDiam1 += fDiam;
      } else {
        fTotalDiam2 += fDiam;
      }

      p_oTree = p_oTrees->NextTree();
    }

    fTotalDiam1 /= 1000.0;
    fTotalDiam2 /= 1000.0;

    fExpectedDiam = 2.848440722;
    EXPECT_LT(fabs(fTotalDiam1 - fExpectedDiam), 0.01);
    fExpectedDiam = 2.565627148;
    EXPECT_LT(fabs(fTotalDiam2 - fExpectedDiam), 0.01);

    delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

////////////////////////////////////////////////////////////////////////////
// WriteNCIQuadratGrowthXMLFile()
////////////////////////////////////////////////////////////////////////////
const char* WriteNCIQuadratGrowthXMLFile(int iYearsPerTimestep, int iPrecip ) {
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
       << "<yearsPerTimestep>" << iYearsPerTimestep << "</yearsPerTimestep>";

  oOut << "<randomSeed>1</randomSeed>"
       << "<plot_lenX>200.0</plot_lenX>"
       << "<plot_lenY>200.0</plot_lenY>"
       << "<plot_latitude>55.37</plot_latitude>"
       << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
       << "<plot_temp_C>12.88171785</plot_temp_C>"
       << "<plot_seasonal_precipitation>500</plot_seasonal_precipitation>"
       << "<plot_water_deficit>600</plot_water_deficit>"
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
       << "</grid>"
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
       << "<behaviorName>NCIMasterQuadratGrowth</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_3\" type=\"Seedling\"/>"
       << "<applyTo species=\"Species_2\" type=\"Seedling\"/>"
       << "<applyTo species=\"Species_4\" type=\"Seedling\"/>"
       << "<applyTo species=\"Species_3\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_4\" type=\"Sapling\"/>"
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
       << "<nciWhichCrowdingEffect>" << crowding_effect_no_size << "</nciWhichCrowdingEffect>"
       << "<nciWhichNCITerm>" << larger_neighbors << "</nciWhichNCITerm>"
       << "<nciWhichSizeEffect>" << no_size_effect << "</nciWhichSizeEffect>"
       << "<nciWhichDamageEffect>" << no_damage_effect << "</nciWhichDamageEffect>"
       << "<nciWhichPrecipitationEffect>" << weibull_precip_effect << "</nciWhichPrecipitationEffect>"
       << "<nciWhichTemperatureEffect>" << weibull_temp_effect << "</nciWhichTemperatureEffect>"
       << "<nciWhichNitrogenEffect>" << no_nitrogen_effect << "</nciWhichNitrogenEffect>"
       << "<nciWhichInfectionEffect>" << no_infection_effect << "</nciWhichInfectionEffect>"
       << "<gr_stochGrowthMethod>" << deterministic_pdf << "</gr_stochGrowthMethod>"
       << "<gr_nciMaxPotentialGrowth>"
       << "<gr_nmpgVal species=\"Species_2\">3</gr_nmpgVal>"
       << "<gr_nmpgVal species=\"Species_3\">2</gr_nmpgVal>"
       << "<gr_nmpgVal species=\"Species_4\">5.4</gr_nmpgVal>"
       << "</gr_nciMaxPotentialGrowth>"
       << "<nciMaxCrowdingRadius>"
       << "<nmcrVal species=\"Species_2\">10</nmcrVal>"
       << "<nmcrVal species=\"Species_3\">10</nmcrVal>"
       << "<nmcrVal species=\"Species_4\">10</nmcrVal>"
       << "</nciMaxCrowdingRadius>"
       << "<nciCrowdingC>"
       << "<nccVal species=\"Species_2\">0.2</nccVal>"
       << "<nccVal species=\"Species_3\">0.5</nccVal>"
       << "<nccVal species=\"Species_4\">0.3</nccVal>"
       << "</nciCrowdingC>"
       << "<nciCrowdingD>"
       << "<ncdVal species=\"Species_2\">0.935</ncdVal>"
       << "<ncdVal species=\"Species_3\">1.16</ncdVal>"
       << "<ncdVal species=\"Species_4\">0.715</ncdVal>"
       << "</nciCrowdingD>"
       << "<nciWeibTempEffA>"
       << "<nwteaVal species=\"Species_2\">6.88</nwteaVal>"
       << "<nwteaVal species=\"Species_3\">139.57</nwteaVal>"
       << "<nwteaVal species=\"Species_4\">6.99</nwteaVal>"
       << "</nciWeibTempEffA>"
       << "<nciWeibTempEffB>"
       << "<nwtebVal species=\"Species_2\">0.301</nwtebVal>"
       << "<nwtebVal species=\"Species_3\">0</nwtebVal>"
       << "<nwtebVal species=\"Species_4\">3</nwtebVal>"
       << "</nciWeibTempEffB>"
       << "<nciWeibTempEffC>"
       << "<nwtecVal species=\"Species_2\">14.23</nwtecVal>"
       << "<nwtecVal species=\"Species_3\">28.61</nwtecVal>"
       << "<nwtecVal species=\"Species_4\">9.67</nwtecVal>"
       << "</nciWeibTempEffC>"
       << "<nciWeibPrecipEffA>"
       << "<nwpeaVal species=\"Species_2\">1296.2</nwpeaVal>"
       << "<nwpeaVal species=\"Species_3\">3306.15</nwpeaVal>"
       << "<nwpeaVal species=\"Species_4\">0.001</nwpeaVal>"
       << "</nciWeibPrecipEffA>"
       << "<nciWeibPrecipEffB>"
       << "<nwpebVal species=\"Species_2\">0.802</nwpebVal>"
       << "<nwpebVal species=\"Species_3\">6.66</nwpebVal>"
       << "<nwpebVal species=\"Species_4\">0.052</nwpebVal>"
       << "</nciWeibPrecipEffB>"
       << "<nciWeibPrecipEffC>"
       << "<nwpecVal species=\"Species_2\">1032.2</nwpecVal>"
       << "<nwpecVal species=\"Species_3\">3835.9</nwpecVal>"
       << "<nwpecVal species=\"Species_4\">643.82</nwpecVal>"
       << "</nciWeibPrecipEffC>"
       << "<nciWeibPrecipType>" << iPrecip << "</nciWeibPrecipType>"
       << "<nciMinNeighborDBH>"
       << "<nmndVal species=\"Species_1\">5</nmndVal>"
       << "<nmndVal species=\"Species_2\">5</nmndVal>"
       << "<nmndVal species=\"Species_3\">5</nmndVal>"
       << "<nmndVal species=\"Species_4\">5</nmndVal>"
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

////////////////////////////////////////////////////////////////////////////
// WriteNCIQuadratGrowthXMLFile2()
////////////////////////////////////////////////////////////////////////////
const char* WriteNCIQuadratGrowthXMLFile2(int iYearsPerTimestep, int iPrecip ) {
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
       << "<yearsPerTimestep>" << iYearsPerTimestep << "</yearsPerTimestep>";

  oOut << "<randomSeed>1</randomSeed>"
       << "<plot_lenX>200.0</plot_lenX>"
       << "<plot_lenY>200.0</plot_lenY>"
       << "<plot_latitude>55.37</plot_latitude>"
       << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
       << "<plot_temp_C>12.88171785</plot_temp_C>"
       << "<plot_seasonal_precipitation>500</plot_seasonal_precipitation>"
       << "<plot_water_deficit>600</plot_water_deficit>"
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
       << "<behaviorName>NCIMasterQuadratGrowth</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Seedling\"/>"
       << "<applyTo species=\"Species_2\" type=\"Seedling\"/>"
       << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
       << "</behavior>"
       << "</behaviorList>"
       << "<NCIMasterQuadratGrowth1>"
       << "<nciWhichShadingEffect>" << no_shading << "</nciWhichShadingEffect>"
       << "<nciWhichCrowdingEffect>" << no_crowding_effect << "</nciWhichCrowdingEffect>"
       << "<nciWhichNCITerm>" << no_nci_term << "</nciWhichNCITerm>"
       << "<nciWhichSizeEffect>" << no_size_effect << "</nciWhichSizeEffect>"
       << "<nciWhichDamageEffect>" << no_damage_effect << "</nciWhichDamageEffect>"
       << "<nciWhichPrecipitationEffect>" << weibull_precip_effect << "</nciWhichPrecipitationEffect>"
       << "<nciWhichTemperatureEffect>" << no_temp_effect << "</nciWhichTemperatureEffect>"
       << "<nciWhichNitrogenEffect>" << no_nitrogen_effect << "</nciWhichNitrogenEffect>"
       << "<nciWhichInfectionEffect>" << no_infection_effect << "</nciWhichInfectionEffect>"
       << "<gr_stochGrowthMethod>" << normal_pdf << "</gr_stochGrowthMethod>"
       << "<gr_nciMaxPotentialGrowth>"
       << "<gr_nmpgVal species=\"Species_1\">3</gr_nmpgVal>"
       << "<gr_nmpgVal species=\"Species_2\">2</gr_nmpgVal>"
       << "</gr_nciMaxPotentialGrowth>"
       << "<gr_standardDeviation>"
       << "<gr_sdVal species=\"Species_1\">0.2</gr_sdVal>"
       << "<gr_sdVal species=\"Species_2\">0.2</gr_sdVal>"
       << "</gr_standardDeviation>"
       << "<nciWeibPrecipEffA>"
       << "<nwpeaVal species=\"Species_1\">1296.2</nwpeaVal>"
       << "<nwpeaVal species=\"Species_2\">1296.2</nwpeaVal>"
       << "</nciWeibPrecipEffA>"
       << "<nciWeibPrecipEffB>"
       << "<nwpebVal species=\"Species_1\">0.802</nwpebVal>"
       << "<nwpebVal species=\"Species_2\">0.802</nwpebVal>"
       << "</nciWeibPrecipEffB>"
       << "<nciWeibPrecipEffC>"
       << "<nwpecVal species=\"Species_1\">1032.2</nwpecVal>"
       << "<nwpecVal species=\"Species_2\">1032.2</nwpecVal>"
       << "</nciWeibPrecipEffC>"
       << "<nciWeibPrecipType>" << iPrecip << "</nciWeibPrecipType>"
       << "</NCIMasterQuadratGrowth1>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteNCIQuadratGrowthXMLErrorFile1()
////////////////////////////////////////////////////////////////////////////
const char* WriteNCIQuadratGrowthXMLErrorFile1() {
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06010101\">"
       << "<plot>"
       << "<timesteps>1</timesteps>"
       << "<yearsPerTimestep>3</yearsPerTimestep>";

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
       << "<behaviorName>NCIMasterQuadratGrowth</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Seedling\"/>"
       << "<applyTo species=\"Species_2\" type=\"Seedling\"/>"
       << "</behavior>"
       << "</behaviorList>"
       << "<NCIMasterQuadratGrowth1>"
       << "<nciWhichShadingEffect>" << no_shading << "</nciWhichShadingEffect>"
       << "<nciWhichCrowdingEffect>" << crowding_effect_no_size << "</nciWhichCrowdingEffect>"
       << "<nciWhichNCITerm>" << larger_neighbors << "</nciWhichNCITerm>"
       << "<nciWhichSizeEffect>" << no_size_effect << "</nciWhichSizeEffect>"
       << "<nciWhichDamageEffect>" << no_damage_effect << "</nciWhichDamageEffect>"
       << "<nciWhichPrecipitationEffect>" << weibull_precip_effect << "</nciWhichPrecipitationEffect>"
       << "<nciWhichTemperatureEffect>" << weibull_temp_effect << "</nciWhichTemperatureEffect>"
       << "<nciWhichNitrogenEffect>" << no_nitrogen_effect << "</nciWhichNitrogenEffect>"
       << "<nciWhichInfectionEffect>" << no_infection_effect << "</nciWhichInfectionEffect>"
       << "<gr_stochGrowthMethod>" << deterministic_pdf << "</gr_stochGrowthMethod>"
       << "<nciCrowdingC>"
       << "<nccVal species=\"Species_1\">0.2</nccVal>"
       << "<nccVal species=\"Species_2\">0.5</nccVal>"
       << "</nciCrowdingC>"
       << "<nciCrowdingD>"
       << "<ncdVal species=\"Species_1\">0.935</ncdVal>"
       << "<ncdVal species=\"Species_2\">1.16</ncdVal>"
       << "</nciCrowdingD>"
       << "<nciWeibTempEffB>"
       << "<nwtebVal species=\"Species_1\">0.301</nwtebVal>"
       << "<nwtebVal species=\"Species_2\">0</nwtebVal>"
       << "</nciWeibTempEffB>"
       << "<nciWeibTempEffC>"
       << "<nwtecVal species=\"Species_1\">14.23</nwtecVal>"
       << "<nwtecVal species=\"Species_2\">28.61</nwtecVal>"
       << "</nciWeibTempEffC>"
       << "<nciWeibPrecipEffB>"
       << "<nwpebVal species=\"Species_1\">0.802</nwpebVal>"
       << "<nwpebVal species=\"Species_2\">6.66</nwpebVal>"
       << "</nciWeibPrecipEffB>"
       << "<nciWeibPrecipEffC>"
       << "<nwpecVal species=\"Species_1\">1032.2</nwpecVal>"
       << "<nwpecVal species=\"Species_2\">3835.9</nwpecVal>"
       << "</nciWeibPrecipEffC>"
       << "<nciWeibPrecipType>0</nciWeibPrecipType>"
       << "<nciMinNeighborDBH>"
       << "<nmndVal species=\"Species_1\">5</nmndVal>"
       << "<nmndVal species=\"Species_2\">5</nmndVal>"
       << "</nciMinNeighborDBH>";

  oOut << "<gr_nciMaxPotentialGrowth>"
       << "<gr_nmpgVal species=\"Species_1\">-3</gr_nmpgVal>"
       << "<gr_nmpgVal species=\"Species_2\">2</gr_nmpgVal>"
       << "</gr_nciMaxPotentialGrowth>"
       << "<nciMaxCrowdingRadius>"
       << "<nmcrVal species=\"Species_2\">10</nmcrVal>"
       << "<nmcrVal species=\"Species_3\">10</nmcrVal>"
       << "<nmcrVal species=\"Species_4\">10</nmcrVal>"
       << "</nciMaxCrowdingRadius>"
       << "<nciWeibTempEffA>"
       << "<nwteaVal species=\"Species_1\">6.88</nwteaVal>"
       << "<nwteaVal species=\"Species_2\">139.57</nwteaVal>"
       << "</nciWeibTempEffA>"
       << "<nciWeibPrecipEffA>"
       << "<nwpeaVal species=\"Species_1\">1296.2</nwpeaVal>"
       << "<nwpeaVal species=\"Species_2\">3306.15</nwpeaVal>"
       << "</nciWeibPrecipEffA>"
       << "</NCIMasterQuadratGrowth1>"
       << "</paramFile>";

  oOut.close();

  return cFileString;

}
