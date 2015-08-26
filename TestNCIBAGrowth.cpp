//---------------------------------------------------------------------------
// TestNCIBAGrowth.cpp
//---------------------------------------------------------------------------
#include "TestNCIBAGrowth.h"
#include <gtest/gtest.h>
#include <fstream>
#include <math.h>
#include "TreePopulation.h"
#include "NCIEffectsList.h"
#include "SimManager.h"
#include "BehaviorBase.h"

using namespace std;

// This tests the functionality of an old behavior, BA NCI growth, that got
// folded into NCI.

////////////////////////////////////////////////////////////////////////////
// TestAutoHeightVsDiamOnly()
// Tests to make sure that the two NCI growth behaviors, diam only and auto
// height, work correctly. WriteNCIBAGrowthXMLFile1() is used to do setup. Then,
// this will create two trees, one of each species. Species 1 and Species 2 are
// identical in every way. Species 1 is assigned NCI growth as a
// diameter-auto, and Species 2 is assigned NCI growth as diameter-only.
// The two trees are assigned identical diameters and heights (heights that
// do not match the diameters, allometrically-speaking). The same shade will
// be assigned to each (0.5). Growth will be allowed to occur, and then
// this makes sure that the new diameters are identical but the heights
// are not.
////////////////////////////////////////////////////////////////////////////
TEST(NCIBAGrowth, TestAutoHeightVsDiamOnly) {

  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    clTreePopulation * p_oPop;
    clTree *p_oTree1, *p_oTree2;
    float fDiam, fHeight, fDiam2, fHeight2;

    //Load our test file and get our tree population pointers
    p_oSimManager->ReadFile( WriteNCIBAGrowthXMLFile1() );
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );

    //Create our two trees and set diameter and height for each
    //Adult, Species 1
    fDiam = 22;
    fHeight = 10;
    p_oTree1 = p_oPop->CreateTree(1, 1, 0, clTreePopulation::adult, fDiam);
    p_oTree1->SetValue(p_oPop->GetHeightCode(p_oTree1->GetSpecies(), p_oTree1->GetType()), fHeight, false, false);

    p_oTree2 = p_oPop->CreateTree(10, 10, 1, clTreePopulation::adult, fDiam);
    p_oTree2->SetValue(p_oPop->GetHeightCode(p_oTree2->GetSpecies(), p_oTree2->GetType()), fHeight, false, false);

    //Now run growth
    p_oSimManager->RunSim(1);

    //Diameters should be the same
    p_oTree1->GetValue(p_oPop->GetDbhCode(p_oTree1->GetSpecies(), p_oTree1->GetType()), &fDiam);
    p_oTree2->GetValue(p_oPop->GetDbhCode(p_oTree2->GetSpecies(), p_oTree2->GetType()), &fDiam2);
    EXPECT_LT(fabs(fDiam - fDiam2), 0.001);

    //Heights should be different
    p_oTree1->GetValue(p_oPop->GetHeightCode(p_oTree1->GetSpecies(), p_oTree1->GetType()), &fHeight);
    p_oTree2->GetValue(p_oPop->GetHeightCode(p_oTree2->GetSpecies(), p_oTree2->GetType()), &fHeight2);
    EXPECT_GT(fabs(fHeight - fHeight2), 1);
    delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

////////////////////////////////////////////////////////////////////////////
// TestErrorProcessing()
////////////////////////////////////////////////////////////////////////////
TEST(NCIBAGrowth, TestErrorProcessing) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try
  {
    p_oSimManager->ReadFile(WriteNCIBAGrowthXMLErrorFile1());
    FAIL() << "TestNCIBAGrowth error processing didn't catch error for WriteNCIBAGrowthXMLErrorFile1.";
  }
  catch (modelErr& err)
  {
    if (err.sFunction.compare("clNCINeighborBA::DoSetup") != 0)
    {
      FAIL() << "TestNCIBAGrowth error processing caught wrong error for WriteNCIBAGrowthXMLErrorFile1.";
    }
    ;
  }

  try
  {
    p_oSimManager->ReadFile(WriteNCIBAGrowthXMLErrorFile2());
    FAIL() << "TestNCIBAGrowth error processing didn't catch error for WriteNCIBAGrowthXMLErrorFile5.";
  }
  catch (modelErr& err)
  {
    if (err.sFunction.compare("clNCINeighborBA::DoSetup") != 0)
    {
      FAIL() << "TestNCIBAGrowth error processing caught wrong error for WriteNCIBAGrowthXMLErrorFile5.";
    }
    ;
  }
  delete p_oSimManager;
}

////////////////////////////////////////////////////////////////////////////
// TestRun1()
// Performs a test run of NCI growth. WriteNCIBAGrowthXMLFile2() performs setup for a
// 1-year timestep. There are 9 target trees whose values will be tested
// according to the testing spreadsheet prepared.
////////////////////////////////////////////////////////////////////////////
TEST(NCIBAGrowth, TestRun1) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    clTreePopulation * p_oPop;
    clTree *p_oTargetTree1,
    *p_oTargetTree2,
    *p_oTargetTree3,
    *p_oTargetTree4,
    *p_oTargetTree5,
    *p_oTargetTree6,
    *p_oTargetTree7,
    *p_oTargetTree8,
    *p_oTargetTree9,
    *p_oTargetTree;
    float fDiam, fExpectedDiam, fGrowth, fExpectedGrowth;
    int iSpecies;

    //Load our test file and get our tree population pointers
    p_oSimManager->ReadFile( WriteNCIBAGrowthXMLFile2() );
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );

    //Create our trees
    fDiam = 11;
    iSpecies = 1;
    p_oTargetTree1 = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, fDiam);

    fDiam = 10.5;
    iSpecies = 1;
    p_oTargetTree2 = p_oPop->CreateTree(50, 50, iSpecies, clTreePopulation::adult, fDiam);

    fDiam = 15;
    iSpecies = 2;
    p_oTargetTree3 = p_oPop->CreateTree(53, 52, iSpecies, clTreePopulation::adult, fDiam);

    fDiam = 25;
    iSpecies = 3;
    p_oTargetTree4 = p_oPop->CreateTree(59, 50, iSpecies, clTreePopulation::adult, fDiam);

    fDiam = 30;
    iSpecies = 1;
    p_oTargetTree5 = p_oPop->CreateTree(50, 59, iSpecies, clTreePopulation::adult, fDiam);

    fDiam = 45;
    iSpecies = 2;
    p_oTargetTree6 = p_oPop->CreateTree(55, 55, iSpecies, clTreePopulation::adult, fDiam);

    fDiam = 15;
    iSpecies = 3;
    p_oTargetTree7 = p_oPop->CreateTree(60, 61, iSpecies, clTreePopulation::adult, fDiam);

    fDiam = 4;
    iSpecies = 1;
    p_oTargetTree8 = p_oPop->CreateTree(52, 52, iSpecies, clTreePopulation::sapling, fDiam);

    fDiam = 4;
    iSpecies = 2;
    p_oTargetTree9 = p_oPop->CreateTree(53, 53, iSpecies, clTreePopulation::sapling, fDiam);

    //Now create all the neighbors that are too small or dead to compete
    p_oPop->CreateTree(56, 56, 0, clTreePopulation::snag, 30);
    p_oPop->CreateTree(56, 56, 0, clTreePopulation::seedling, 0.2);
    p_oTargetTree = p_oPop->CreateTree(54, 54, 1, clTreePopulation::adult, 20);
    p_oTargetTree->SetValue(p_oPop->GetIntDataCode("dead", p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), natural);

    //Now do the run
    p_oSimManager->RunSim(1);

    //Check the diameters and growth of the target trees
    fExpectedDiam = 11.18521795;
    fExpectedGrowth = 0.926089761;
    p_oTargetTree = p_oTargetTree1;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fDiam);
    p_oTargetTree->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fGrowth);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);
    EXPECT_LT(fabs(fGrowth - fExpectedGrowth)/fGrowth, 0.001);

    fExpectedDiam = 10.54400652;
    fExpectedGrowth = 0.220032614;
    p_oTargetTree = p_oTargetTree2;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fDiam);
    p_oTargetTree->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fGrowth);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);
    EXPECT_LT(fabs(fGrowth - fExpectedGrowth)/fGrowth, 0.001);

    fExpectedDiam = 24.78918029;
    fExpectedGrowth = 48.94590146;
    p_oTargetTree = p_oTargetTree3;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fDiam);
    p_oTargetTree->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fGrowth);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);
    EXPECT_LT(fabs(fGrowth - fExpectedGrowth)/fGrowth, 0.001);

    fExpectedDiam = 25;
    fExpectedGrowth = 0;
    p_oTargetTree = p_oTargetTree4;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fDiam);
    p_oTargetTree->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fGrowth);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);
    EXPECT_LT(fabs(fGrowth - fExpectedGrowth), 0.001);

    fExpectedDiam = 30.17701465;
    fExpectedGrowth = 0.885073229;
    p_oTargetTree = p_oTargetTree5;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fDiam);
    p_oTargetTree->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fGrowth);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);
    EXPECT_LT(fabs(fGrowth - fExpectedGrowth)/fGrowth, 0.001);

    fExpectedDiam = 50.99531401;
    fExpectedGrowth = 29.97657003;
    p_oTargetTree = p_oTargetTree6;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fDiam);
    p_oTargetTree->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fGrowth);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);
    EXPECT_LT(fabs(fGrowth - fExpectedGrowth)/fGrowth, 0.001);

    fExpectedDiam = 15;
    fExpectedGrowth = 0;
    p_oTargetTree = p_oTargetTree7;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fDiam);
    p_oTargetTree->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fGrowth);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);
    EXPECT_LT(fabs(fGrowth - fExpectedGrowth), 0.001);

    fExpectedDiam = 4.001046852;
    fExpectedGrowth = 0.006536289;
    p_oTargetTree = p_oTargetTree8;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fDiam);
    p_oTargetTree->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fGrowth);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);
    EXPECT_LT(fabs(fGrowth - fExpectedGrowth)/fGrowth, 0.001);

    fExpectedDiam = 5.979793256;
    fExpectedGrowth = 12.36134651;
    p_oTargetTree = p_oTargetTree9;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fDiam);
    p_oTargetTree->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fGrowth);
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
// Performs a test run of NCI growth. WriteNCIBAGrowthXMLFile3() performs setup for a
// 3-year timestep. There are 9 target trees whose values will be tested
// according to the testing spreadsheet prepared.
////////////////////////////////////////////////////////////////////////////
TEST(NCIBAGrowth, TestRun2) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    clTreePopulation * p_oPop;
    clTree *p_oTargetTree1,
    *p_oTargetTree2,
    *p_oTargetTree3,
    *p_oTargetTree4,
    *p_oTargetTree5,
    *p_oTargetTree6,
    *p_oTargetTree7,
    *p_oTargetTree8,
    *p_oTargetTree9,
    *p_oTargetTree;
    float fDiam, fExpectedDiam, fGrowth, fExpectedGrowth;
    int iSpecies;

    //Load our test file and get our tree population pointers
    p_oSimManager->ReadFile( WriteNCIBAGrowthXMLFile3() );
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );

    //Create our trees
    fDiam = 11;
    iSpecies = 1;
    p_oTargetTree1 = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, fDiam);

    fDiam = 10.5;
    iSpecies = 1;
    p_oTargetTree2 = p_oPop->CreateTree(50, 50, iSpecies, clTreePopulation::adult, fDiam);

    fDiam = 15;
    iSpecies = 2;
    p_oTargetTree3 = p_oPop->CreateTree(53, 52, iSpecies, clTreePopulation::adult, fDiam);

    fDiam = 25;
    iSpecies = 3;
    p_oTargetTree4 = p_oPop->CreateTree(59, 50, iSpecies, clTreePopulation::adult, fDiam);

    fDiam = 30;
    iSpecies = 1;
    p_oTargetTree5 = p_oPop->CreateTree(50, 59, iSpecies, clTreePopulation::adult, fDiam);

    fDiam = 45;
    iSpecies = 2;
    p_oTargetTree6 = p_oPop->CreateTree(55, 55, iSpecies, clTreePopulation::adult, fDiam);

    fDiam = 15;
    iSpecies = 3;
    p_oTargetTree7 = p_oPop->CreateTree(60, 61, iSpecies, clTreePopulation::adult, fDiam);

    fDiam = 4;
    iSpecies = 1;
    p_oTargetTree8 = p_oPop->CreateTree(52, 52, iSpecies, clTreePopulation::sapling, fDiam);

    fDiam = 4;
    iSpecies = 2;
    p_oTargetTree9 = p_oPop->CreateTree(53, 53, iSpecies, clTreePopulation::sapling, fDiam);

    //Now create all the neighbors that are too small or dead to compete
    p_oPop->CreateTree(56, 56, 0, clTreePopulation::snag, 30);
    p_oPop->CreateTree(56, 56, 0, clTreePopulation::seedling, 0.2);
    p_oTargetTree = p_oPop->CreateTree(54, 54, 1, clTreePopulation::adult, 20);
    p_oTargetTree->SetValue(p_oPop->GetIntDataCode("dead", p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), natural);

    //Now do the run
    p_oSimManager->RunSim(1);

    //Check the diameters and growth of the target trees
    fExpectedDiam = 11.55749479;
    fExpectedGrowth = 0.929157982;
    p_oTargetTree = p_oTargetTree1;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fDiam);
    p_oTargetTree->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fGrowth);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);
    EXPECT_LT(fabs(fGrowth - fExpectedGrowth)/fGrowth, 0.001);

    fExpectedDiam = 10.63308904;
    fExpectedGrowth = 0.221815064;
    p_oTargetTree = p_oTargetTree2;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fDiam);
    p_oTargetTree->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fGrowth);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);
    EXPECT_LT(fabs(fGrowth - fExpectedGrowth)/fGrowth, 0.001);

    fExpectedDiam = 41.9815976;
    fExpectedGrowth = 44.96932933;
    p_oTargetTree = p_oTargetTree3;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fDiam);
    p_oTargetTree->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fGrowth);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);
    EXPECT_LT(fabs(fGrowth - fExpectedGrowth)/fGrowth, 0.001);

    fExpectedDiam = 25;
    fExpectedGrowth = 0;
    p_oTargetTree = p_oTargetTree4;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fDiam);
    p_oTargetTree->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fGrowth);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);
    EXPECT_LT(fabs(fGrowth - fExpectedGrowth), 0.001);

    fExpectedDiam = 30.53228555;
    fExpectedGrowth = 0.887142584;
    p_oTargetTree = p_oTargetTree5;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fDiam);
    p_oTargetTree->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fGrowth);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);
    EXPECT_LT(fabs(fGrowth - fExpectedGrowth)/fGrowth, 0.001);

    fExpectedDiam = 60.69407808;
    fExpectedGrowth = 26.15679679;
    p_oTargetTree = p_oTargetTree6;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fDiam);
    p_oTargetTree->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fGrowth);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);
    EXPECT_LT(fabs(fGrowth - fExpectedGrowth)/fGrowth, 0.001);

    fExpectedDiam = 15;
    fExpectedGrowth = 0;
    p_oTargetTree = p_oTargetTree7;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fDiam);
    p_oTargetTree->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fGrowth);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);
    EXPECT_LT(fabs(fGrowth - fExpectedGrowth), 0.001);

    fExpectedDiam = 4.003145469;
    fExpectedGrowth = 0.006546514;
    p_oTargetTree = p_oTargetTree8;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fDiam);
    p_oTargetTree->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fGrowth);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);
    EXPECT_LT(fabs(fGrowth - fExpectedGrowth)/fGrowth, 0.001);

    fExpectedDiam = 16.09746779;
    fExpectedGrowth = 25.17788002;
    p_oTargetTree = p_oTargetTree9;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fDiam);
    p_oTargetTree->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fGrowth);
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
// Performs a test run of NCI growth. WriteNCIBAGrowthXMLFile4() performs setup for a
// 1-year timestep. There are 9 target trees whose values will be tested
// according to the testing spreadsheet prepared.
////////////////////////////////////////////////////////////////////////////
TEST(NCIBAGrowth, TestRun3) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    clTreePopulation * p_oPop;
    clTree *p_oTargetTree1,
    *p_oTargetTree2,
    *p_oTargetTree3,
    *p_oTargetTree4,
    *p_oTargetTree5,
    *p_oTargetTree6,
    *p_oTargetTree7,
    *p_oTargetTree8,
    *p_oTargetTree9,
    *p_oTargetTree;
    float fDiam, fExpectedDiam, fGrowth, fExpectedGrowth;
    int iSpecies;

    //Load our test file and get our tree population pointers
    p_oSimManager->ReadFile( WriteNCIBAGrowthXMLFile4() );
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );

    //Create our trees
    fDiam = 11;
    iSpecies = 1;
    p_oTargetTree1 = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, fDiam);

    fDiam = 10.5;
    iSpecies = 1;
    p_oTargetTree2 = p_oPop->CreateTree(50, 50, iSpecies, clTreePopulation::adult, fDiam);

    fDiam = 15;
    iSpecies = 2;
    p_oTargetTree3 = p_oPop->CreateTree(53, 52, iSpecies, clTreePopulation::adult, fDiam);

    fDiam = 25;
    iSpecies = 3;
    p_oTargetTree4 = p_oPop->CreateTree(59, 50, iSpecies, clTreePopulation::adult, fDiam);

    fDiam = 30;
    iSpecies = 1;
    p_oTargetTree5 = p_oPop->CreateTree(50, 59, iSpecies, clTreePopulation::adult, fDiam);

    fDiam = 45;
    iSpecies = 2;
    p_oTargetTree6 = p_oPop->CreateTree(55, 55, iSpecies, clTreePopulation::adult, fDiam);

    fDiam = 15;
    iSpecies = 3;
    p_oTargetTree7 = p_oPop->CreateTree(60, 61, iSpecies, clTreePopulation::adult, fDiam);

    fDiam = 4;
    iSpecies = 1;
    p_oTargetTree8 = p_oPop->CreateTree(52, 52, iSpecies, clTreePopulation::sapling, fDiam);

    fDiam = 4;
    iSpecies = 2;
    p_oTargetTree9 = p_oPop->CreateTree(53, 53, iSpecies, clTreePopulation::sapling, fDiam);

    //Now create all the neighbors that are too small or dead to compete
    p_oPop->CreateTree(56, 56, 0, clTreePopulation::snag, 30);
    p_oPop->CreateTree(56, 56, 0, clTreePopulation::seedling, 0.2);
    p_oTargetTree = p_oPop->CreateTree(54, 54, 1, clTreePopulation::adult, 20);
    p_oTargetTree->SetValue(p_oPop->GetIntDataCode("dead", p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), natural);

    //Now do the run
    p_oSimManager->RunSim(1);

    //Check the diameters and growth of the target trees
    fExpectedDiam = 11.18521795;
    fExpectedGrowth = 0.926089761;
    p_oTargetTree = p_oTargetTree1;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fDiam);
    p_oTargetTree->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fGrowth);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);
    EXPECT_LT(fabs(fGrowth - fExpectedGrowth)/fGrowth, 0.001);

    fExpectedDiam = 10.51053299;
    fExpectedGrowth = 0.052664955;
    p_oTargetTree = p_oTargetTree2;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fDiam);
    p_oTargetTree->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fGrowth);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);
    EXPECT_LT(fabs(fGrowth - fExpectedGrowth)/fGrowth, 0.001);

    fExpectedDiam = 16.01009627;
    fExpectedGrowth = 5.050481328;
    p_oTargetTree = p_oTargetTree3;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fDiam);
    p_oTargetTree->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fGrowth);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);
    EXPECT_LT(fabs(fGrowth - fExpectedGrowth)/fGrowth, 0.001);

    fExpectedDiam = 28.08412233;
    fExpectedGrowth = 15.42061165;
    p_oTargetTree = p_oTargetTree4;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fDiam);
    p_oTargetTree->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fGrowth);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);
    EXPECT_LT(fabs(fGrowth - fExpectedGrowth), 0.001);

    fExpectedDiam = 30.13288859;
    fExpectedGrowth = 0.664442972;
    p_oTargetTree = p_oTargetTree5;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fDiam);
    p_oTargetTree->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fGrowth);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);
    EXPECT_LT(fabs(fGrowth - fExpectedGrowth)/fGrowth, 0.001);

    fExpectedDiam = 45.53407396;
    fExpectedGrowth = 2.670369789;
    p_oTargetTree = p_oTargetTree6;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fDiam);
    p_oTargetTree->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fGrowth);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);
    EXPECT_LT(fabs(fGrowth - fExpectedGrowth)/fGrowth, 0.001);

    fExpectedDiam = 17.65389656;
    fExpectedGrowth = 13.26948278;
    p_oTargetTree = p_oTargetTree7;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fDiam);
    p_oTargetTree->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fGrowth);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);
    EXPECT_LT(fabs(fGrowth - fExpectedGrowth), 0.001);

    fExpectedDiam = 4.000009265;
    fExpectedGrowth = 5.7849E-05;
    p_oTargetTree = p_oTargetTree8;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fDiam);
    p_oTargetTree->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fGrowth);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);
    EXPECT_LT(fabs(fGrowth - fExpectedGrowth)/fGrowth, 0.001);

    fExpectedDiam = 4.34733014;
    fExpectedGrowth = 2.168644728;
    p_oTargetTree = p_oTargetTree9;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fDiam);
    p_oTargetTree->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fGrowth);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);
    EXPECT_LT(fabs(fGrowth - fExpectedGrowth)/fGrowth, 0.001);
    delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

////////////////////////////////////////////////////////////////////////////
// WriteNCIBAGrowthXMLFile1()
////////////////////////////////////////////////////////////////////////////
const char* WriteNCIBAGrowthXMLFile1() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  WriteNCIBAGrowthErrorFileCommonStuff(oOut);

  //Write file
  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>NCIMasterGrowth</behaviorName>"
       << "<version>3</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\" />"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>NCIMasterGrowth diam only</behaviorName>"
       << "<version>3</version>"
       << "<listPosition>2</listPosition>"
       << "<applyTo species=\"Species_2\" type=\"Adult\" />"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>HeightIncrementer</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>3</listPosition>"
       << "<applyTo species=\"Species_2\" type=\"Adult\" />"
       << "</behavior>"
       << "</behaviorList>"
       << "<NCIMasterGrowth1>"
       << "<nciWhichShadingEffect>" << no_shading << "</nciWhichShadingEffect>"
       << "<nciWhichCrowdingEffect>" << crowding_effect_two << "</nciWhichCrowdingEffect>"
       << "<nciWhichNCITerm>" << neighbor_ba << "</nciWhichNCITerm>"
       << "<nciWhichSizeEffect>" << default_size_effect << "</nciWhichSizeEffect>"
       << "<nciWhichDamageEffect>" << no_damage_effect << "</nciWhichDamageEffect>"
       << "<nciWhichPrecipitationEffect>" << no_precip_effect << "</nciWhichPrecipitationEffect>"
       << "<nciWhichTemperatureEffect>" << no_temp_effect << "</nciWhichTemperatureEffect>"
       << "<nciWhichNitrogenEffect>" << no_nitrogen_effect << "</nciWhichNitrogenEffect>"
       << "<nciWhichInfectionEffect>" << no_infection_effect << "</nciWhichInfectionEffect>"
       << "<gr_stochGrowthMethod>" << deterministic_pdf << "</gr_stochGrowthMethod>"
       << "<nciMaxCrowdingRadius>"
       << "<nmcrVal species=\"Species_1\">10</nmcrVal>"
       << "</nciMaxCrowdingRadius>"
       << "<gr_nciMaxPotentialGrowth>"
       << "<gr_nmpgVal species=\"Species_1\">1.531</gr_nmpgVal>"
       << "</gr_nciMaxPotentialGrowth>"
       << "<nciCrowdingGamma>"
       << "<ncgVal species=\"Species_1\">0.36</ncgVal>"
       << "</nciCrowdingGamma>"
       << "<nciSizeEffectX0>"
       << "<nsex0Val species=\"Species_1\">122.23</nsex0Val>"
       << "</nciSizeEffectX0>"
       << "<nciSizeEffectXb>"
       << "<nsexbVal species=\"Species_1\">5</nsexbVal>"
       << "</nciSizeEffectXb>"
       << "<nciCrowdingC>"
       << "<nccVal species=\"Species_1\">1.98</nccVal>"
       << "</nciCrowdingC>"
       << "<nciCrowdingD>"
       << "<ncdVal species=\"Species_1\">1.63</ncdVal>"
       << "</nciCrowdingD>"
       << "<nciMinNeighborDBH>"
       << "<nmndVal species=\"Species_1\">0</nmndVal>"
       << "<nmndVal species=\"Species_2\">0</nmndVal>"
       << "</nciMinNeighborDBH>"
       << "<nciBAOnlyLargerNeighbors>1</nciBAOnlyLargerNeighbors>"
       << "<nciBADivisor>1000</nciBADivisor>"
       << "</NCIMasterGrowth1>"
       << "<NCIMasterGrowth2>"
       << "<nciWhichShadingEffect>" << no_shading << "</nciWhichShadingEffect>"
       << "<nciWhichCrowdingEffect>" << crowding_effect_two << "</nciWhichCrowdingEffect>"
       << "<nciWhichNCITerm>4</nciWhichNCITerm>"
       << "<nciWhichSizeEffect>1</nciWhichSizeEffect>"
       << "<nciWhichDamageEffect>" << no_damage_effect << "</nciWhichDamageEffect>"
       << "<nciWhichPrecipitationEffect>" << no_precip_effect << "</nciWhichPrecipitationEffect>"
       << "<nciWhichTemperatureEffect>" << no_temp_effect << "</nciWhichTemperatureEffect>"
       << "<nciWhichNitrogenEffect>" << no_nitrogen_effect << "</nciWhichNitrogenEffect>"
       << "<nciWhichInfectionEffect>" << no_infection_effect << "</nciWhichInfectionEffect>"
       << "<gr_stochGrowthMethod>" << deterministic_pdf << "</gr_stochGrowthMethod>"
       << "<nciMaxCrowdingRadius>"
       << "<nmcrVal species=\"Species_2\">10</nmcrVal>"
       << "</nciMaxCrowdingRadius>"
       << "<gr_nciMaxPotentialGrowth>"
       << "<gr_nmpgVal species=\"Species_2\">1.531</gr_nmpgVal>"
       << "</gr_nciMaxPotentialGrowth>"
       << "<nciCrowdingGamma>"
       << "<ncgVal species=\"Species_2\">0.36</ncgVal>"
       << "</nciCrowdingGamma>"
       << "<nciSizeEffectX0>"
       << "<nsex0Val species=\"Species_2\">122.23</nsex0Val>"
       << "</nciSizeEffectX0>"
       << "<nciSizeEffectXb>"
       << "<nsexbVal species=\"Species_2\">5</nsexbVal>"
       << "</nciSizeEffectXb>"
       << "<nciCrowdingC>"
       << "<nccVal species=\"Species_2\">1.98</nccVal>"
       << "</nciCrowdingC>"
       << "<nciCrowdingD>"
       << "<ncdVal species=\"Species_2\">1.63</ncdVal>"
       << "</nciCrowdingD>"
       << "<nciMinNeighborDBH>"
       << "<nmndVal species=\"Species_1\">0</nmndVal>"
       << "<nmndVal species=\"Species_2\">0</nmndVal>"
       << "</nciMinNeighborDBH>"
       << "<nciBAOnlyLargerNeighbors>1</nciBAOnlyLargerNeighbors>"
       << "<nciBADivisor>1000</nciBADivisor>"
       << "</NCIMasterGrowth2>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteNCIBAGrowthXMLFile2()
////////////////////////////////////////////////////////////////////////////
const char* WriteNCIBAGrowthXMLFile2() {
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

  WriteNCIBAGrowthTreeStuff(oOut);
  WriteNCIBAGrowthCommonStuff(oOut);

  oOut.close();

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteNCIBAGrowthXMLFile3()
////////////////////////////////////////////////////////////////////////////
const char* WriteNCIBAGrowthXMLFile3() {
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

  WriteNCIBAGrowthTreeStuff(oOut);
  WriteNCIBAGrowthCommonStuff(oOut);

  oOut.close();

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteNCIBAGrowthXMLFile4()
////////////////////////////////////////////////////////////////////////////
const char* WriteNCIBAGrowthXMLFile4() {
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

  WriteNCIBAGrowthTreeStuff(oOut);

  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>NCIMasterGrowth</behaviorName>"
       << "<version>3</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_3\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_4\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_4\" type=\"Sapling\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>StochasticMortality</behaviorName>"
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
       << "</behaviorList>"
       << "<NCIMasterGrowth1>"
       << "<nciWhichShadingEffect>0</nciWhichShadingEffect>"
       << "<nciWhichCrowdingEffect>" << crowding_effect_two << "</nciWhichCrowdingEffect>"
       << "<nciWhichNCITerm>4</nciWhichNCITerm>"
       << "<nciWhichSizeEffect>1</nciWhichSizeEffect>"
       << "<nciWhichDamageEffect>" << no_damage_effect << "</nciWhichDamageEffect>"
       << "<nciWhichPrecipitationEffect>" << no_precip_effect << "</nciWhichPrecipitationEffect>"
       << "<nciWhichTemperatureEffect>" << no_temp_effect << "</nciWhichTemperatureEffect>"
       << "<nciWhichNitrogenEffect>" << no_nitrogen_effect << "</nciWhichNitrogenEffect>"
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
       << "<nciCrowdingGamma>"
       << "<ncgVal species=\"Species_2\">-1.208</ncgVal>"
       << "<ncgVal species=\"Species_3\">0.68</ncgVal>"
       << "<ncgVal species=\"Species_4\">0.461</ncgVal>"
       << "</nciCrowdingGamma>"
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
       << "<nciCrowdingC>"
       << "<nccVal species=\"Species_2\">8.261</nccVal>"
       << "<nccVal species=\"Species_3\">0.67</nccVal>"
       << "<nccVal species=\"Species_4\">0.321</nccVal>"
       << "</nciCrowdingC>"
       << "<nciCrowdingD>"
       << "<ncdVal species=\"Species_2\">1.001</ncdVal>"
       << "<ncdVal species=\"Species_3\">0.34</ncdVal>"
       << "<ncdVal species=\"Species_4\">0.03</ncdVal>"
       << "</nciCrowdingD>"
       << "<nciMinNeighborDBH>"
       << "<nmndVal species=\"Species_1\">5</nmndVal>"
       << "<nmndVal species=\"Species_2\">5</nmndVal>"
       << "<nmndVal species=\"Species_3\">5</nmndVal>"
       << "<nmndVal species=\"Species_4\">5</nmndVal>"
       << "</nciMinNeighborDBH>"
       << "<nciBAOnlyLargerNeighbors>0</nciBAOnlyLargerNeighbors>"
       << "<nciBADivisor>500</nciBADivisor>"
       << "</NCIMasterGrowth1>"
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
// WriteNCIBAGrowthTreeStuff()
/////////////////////////////////////////////////////////////////////////////
void WriteNCIBAGrowthTreeStuff( std::fstream &oOut )
{
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
       << "<tr_stdMaxCrownRad>"
       << "<tr_smcrVal species=\"Species_1\">10</tr_smcrVal>"
       << "<tr_smcrVal species=\"Species_2\">10</tr_smcrVal>"
       << "<tr_smcrVal species=\"Species_3\">10</tr_smcrVal>"
       << "<tr_smcrVal species=\"Species_4\">10</tr_smcrVal>"
       << "</tr_stdMaxCrownRad>"
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
// WriteNCIBAGrowthCommonStuff()
/////////////////////////////////////////////////////////////////////////////
void WriteNCIBAGrowthCommonStuff( std::fstream &oOut )
{
  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>NCIMasterGrowth</behaviorName>"
       << "<version>3</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_3\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_4\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_4\" type=\"Sapling\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>StochasticMortality</behaviorName>"
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
       << "</behaviorList>"
       << "<NCIMasterGrowth1>"
       << "<nciWhichShadingEffect>" << no_shading << "</nciWhichShadingEffect>"
       << "<nciWhichCrowdingEffect>" << crowding_effect_two << "</nciWhichCrowdingEffect>"
       << "<nciWhichNCITerm>4</nciWhichNCITerm>"
       << "<nciWhichSizeEffect>1</nciWhichSizeEffect>"
       << "<nciWhichDamageEffect>" << no_damage_effect << "</nciWhichDamageEffect>"
       << "<nciWhichPrecipitationEffect>" << no_precip_effect << "</nciWhichPrecipitationEffect>"
       << "<nciWhichTemperatureEffect>" << no_temp_effect << "</nciWhichTemperatureEffect>"
       << "<nciWhichNitrogenEffect>" << no_nitrogen_effect << "</nciWhichNitrogenEffect>"
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
       << "<nciCrowdingGamma>"
       << "<ncgVal species=\"Species_2\">-1.208</ncgVal>"
       << "<ncgVal species=\"Species_3\">1.976</ncgVal>"
       << "<ncgVal species=\"Species_4\">0.461</ncgVal>"
       << "</nciCrowdingGamma>"
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
       << "<nciCrowdingC>"
       << "<nccVal species=\"Species_2\">8.261</nccVal>"
       << "<nccVal species=\"Species_3\">0</nccVal>"
       << "<nccVal species=\"Species_4\">0.321</nccVal>"
       << "</nciCrowdingC>"
       << "<nciCrowdingD>"
       << "<ncdVal species=\"Species_2\">1.001</ncdVal>"
       << "<ncdVal species=\"Species_3\">2.914</ncdVal>"
       << "<ncdVal species=\"Species_4\">4.975</ncdVal>"
       << "</nciCrowdingD>"
       << "<nciMinNeighborDBH>"
       << "<nmndVal species=\"Species_1\">5</nmndVal>"
       << "<nmndVal species=\"Species_2\">5</nmndVal>"
       << "<nmndVal species=\"Species_3\">5</nmndVal>"
       << "<nmndVal species=\"Species_4\">5</nmndVal>"
       << "</nciMinNeighborDBH>"
       << "<nciBAOnlyLargerNeighbors>1</nciBAOnlyLargerNeighbors>"
       << "<nciBADivisor>1000</nciBADivisor>"
       << "</NCIMasterGrowth1>"
       << "<StochasticMortality2>"
       << "<mo_stochasticMortRate>"
       << "<mo_smrVal species=\"Species_3\">0</mo_smrVal>"
       << "<mo_smrVal species=\"Species_1\">0</mo_smrVal>"
       << "<mo_smrVal species=\"Species_2\">0</mo_smrVal>"
       << "<mo_smrVal species=\"Species_4\">0</mo_smrVal>"
       << "</mo_stochasticMortRate>"
       << "</StochasticMortality2>"
       << "</paramFile>";

}

/////////////////////////////////////////////////////////////////////////////
// WriteNCIBAGrowthErrorFileCommonStuff()
/////////////////////////////////////////////////////////////////////////////
void WriteNCIBAGrowthErrorFileCommonStuff( std::fstream &oOut )
{
  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06010101\">"
       << "<plot>"
       << "<timesteps>1</timesteps>"
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
       << "<tr_stdMaxCrownRad>"
       << "<tr_smcrVal species=\"Species_1\">10</tr_smcrVal>"
       << "<tr_smcrVal species=\"Species_2\">10</tr_smcrVal>"
       << "</tr_stdMaxCrownRad>"
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
}

////////////////////////////////////////////////////////////////////////////
// WriteNCIBAGrowthXMLErrorFile1()
////////////////////////////////////////////////////////////////////////////
const char* WriteNCIBAGrowthXMLErrorFile1() {
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  WriteNCIBAGrowthErrorFileCommonStuff(oOut);

  //Write file
  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>NCIMasterGrowth</behaviorName>"
       << "<version>3</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "</behavior>"
       << "</behaviorList>"
       << "<NCIMasterGrowth1>"
       << "<nciWhichShadingEffect>" << no_shading << "</nciWhichShadingEffect>"
       << "<nciWhichCrowdingEffect>" << crowding_effect_two << "</nciWhichCrowdingEffect>"
       << "<nciWhichNCITerm>4</nciWhichNCITerm>"
       << "<nciWhichSizeEffect>1</nciWhichSizeEffect>"
       << "<nciWhichDamageEffect>" << no_damage_effect << "</nciWhichDamageEffect>"
       << "<nciWhichPrecipitationEffect>" << no_precip_effect << "</nciWhichPrecipitationEffect>"
       << "<nciWhichTemperatureEffect>" << no_temp_effect << "</nciWhichTemperatureEffect>"
       << "<nciWhichNitrogenEffect>" << no_nitrogen_effect << "</nciWhichNitrogenEffect>"
       << "<nciWhichInfectionEffect>" << no_infection_effect << "</nciWhichInfectionEffect>"
       << "<gr_stochGrowthMethod>" << deterministic_pdf << "</gr_stochGrowthMethod>"
       << "<nciMaxCrowdingRadius>"
       << "<nmcrVal species=\"Species_1\">10</nmcrVal>"
       << "<nmcrVal species=\"Species_2\">-10</nmcrVal>"
       << "</nciMaxCrowdingRadius>"
       << "<gr_nciMaxPotentialGrowth>"
       << "<gr_nmpgVal species=\"Species_1\">15.31</gr_nmpgVal>"
       << "<gr_nmpgVal species=\"Species_2\">15.31</gr_nmpgVal>"
       << "</gr_nciMaxPotentialGrowth>"
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
       << "<nciMinNeighborDBH>"
       << "<nmndVal species=\"Species_1\">0</nmndVal>"
       << "<nmndVal species=\"Species_2\">0</nmndVal>"
       << "</nciMinNeighborDBH>"
       << "<nciBAOnlyLargerNeighbors>1</nciBAOnlyLargerNeighbors>"
       << "<nciBADivisor>1000</nciBADivisor>"
       << "</NCIMasterGrowth1>"
       << "</paramFile>";


  oOut.close();

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteNCIBAGrowthXMLErrorFile5()
////////////////////////////////////////////////////////////////////////////
const char* WriteNCIBAGrowthXMLErrorFile2() {
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  WriteNCIBAGrowthErrorFileCommonStuff(oOut);

  //Write file
  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>NCIMasterGrowth</behaviorName>"
       << "<version>3</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "</behavior>"
       << "</behaviorList>"
       << "<NCIMasterGrowth1>"
       << "<nciWhichShadingEffect>" << no_shading << "</nciWhichShadingEffect>"
       << "<nciWhichCrowdingEffect>" << crowding_effect_two << "</nciWhichCrowdingEffect>"
       << "<nciWhichNCITerm>4</nciWhichNCITerm>"
       << "<nciWhichSizeEffect>1</nciWhichSizeEffect>"
       << "<nciWhichDamageEffect>" << no_damage_effect << "</nciWhichDamageEffect>"
       << "<nciWhichPrecipitationEffect>" << no_precip_effect << "</nciWhichPrecipitationEffect>"
       << "<nciWhichTemperatureEffect>" << no_temp_effect << "</nciWhichTemperatureEffect>"
       << "<nciWhichNitrogenEffect>" << no_nitrogen_effect << "</nciWhichNitrogenEffect>"
       << "<nciWhichInfectionEffect>" << no_infection_effect << "</nciWhichInfectionEffect>"
       << "<gr_stochGrowthMethod>" << deterministic_pdf << "</gr_stochGrowthMethod>"
       << "<nciMaxCrowdingRadius>"
       << "<nmcrVal species=\"Species_1\">10</nmcrVal>"
       << "<nmcrVal species=\"Species_2\">10</nmcrVal>"
       << "</nciMaxCrowdingRadius>"
       << "<gr_nciMaxPotentialGrowth>"
       << "<gr_nmpgVal species=\"Species_1\">15.31</gr_nmpgVal>"
       << "<gr_nmpgVal species=\"Species_2\">15.31</gr_nmpgVal>"
       << "</gr_nciMaxPotentialGrowth>"
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
       << "<nciCrowdingGamma>"
       << "<ncgVal species=\"Species_1\">0.43</ncgVal>"
       << "<ncgVal species=\"Species_2\">0.43</ncgVal>"
       << "</nciCrowdingGamma>"
       << "<nciMinNeighborDBH>"
       << "<nmndVal species=\"Species_1\">-10</nmndVal>"
       << "<nmndVal species=\"Species_2\">0</nmndVal>"
       << "</nciMinNeighborDBH>"
       << "<nciBAOnlyLargerNeighbors>1</nciBAOnlyLargerNeighbors>"
       << "<nciBADivisor>1000</nciBADivisor>"
       << "</NCIMasterGrowth1>"
       << "</paramFile>";


  oOut.close();

  return cFileString;
}
