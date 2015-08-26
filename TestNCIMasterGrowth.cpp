//---------------------------------------------------------------------------
// TestNciGrowth.cpp
//---------------------------------------------------------------------------
#include "TestNCIMasterGrowth.h"
#include <gtest/gtest.h>
#include <fstream>
#include <math.h>
#include "TreePopulation.h"
#include "SimManager.h"
#include "BehaviorBase.h"
#include "NCIEffectsList.h"

////////////////////////////////////////////////////////////////////////////
// TestAutoHeightVsDiamOnly()
// Tests to make sure that the two NCI growth behaviors, diam only and auto
// height, work correctly. WriteNCIGrowthXMLFile1() is used to do setup. Then,
// this will create two trees, one of each species. Species 1 and Species 2 are
// identical in every way. Species 1 is assigned NCI growth as a
// diameter-auto, and Species 2 is assigned NCI growth as diameter-only.
// The two trees are assigned identical diameters and heights (heights that
// do not match the diameters, allometrically-speaking). The same shade will
// be assigned to each (0.5). Growth will be allowed to occur, and then
// this makes sure that the new diameters are identical but the heights
// are not.
////////////////////////////////////////////////////////////////////////////
TEST(NCIMasterGrowth, TestAutoHeightVsDiamOnly) {

  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    clTreePopulation * p_oPop;
    clTree *p_oTree1, *p_oTree2;
    float fDiam, fHeight, fDiam2, fHeight2, fShade, fGrowth;

    //Load our test file and get our tree population pointers
    p_oSimManager->ReadFile( WriteNCIGrowthXMLFile1() );
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );

    //Create our two trees and set diameter, height, and shade for each
    //Adult, Species 1
    fDiam = 22;
    fHeight = 10;
    fShade = 0.5;
    p_oTree1 = p_oPop->CreateTree(1, 1, 0, clTreePopulation::adult, fDiam);
    p_oTree1->SetValue(p_oPop->GetHeightCode(p_oTree1->GetSpecies(), p_oTree1->GetType()), fHeight, false, false);
    p_oTree1->SetValue(p_oPop->GetFloatDataCode("Light", p_oTree1->GetSpecies(), p_oTree1->GetType()), fShade, false, false);

    p_oTree2 = p_oPop->CreateTree(10, 10, 1, clTreePopulation::adult, fDiam);
    p_oTree2->SetValue(p_oPop->GetHeightCode(p_oTree2->GetSpecies(), p_oTree2->GetType()), fHeight, false, false);
    p_oTree2->SetValue(p_oPop->GetFloatDataCode("Light", p_oTree2->GetSpecies(), p_oTree2->GetType()), fShade, false, false);

    //Now run growth, but skip light
    int i;
    for (i = 1; i < p_oSimManager->GetNumberOfBehaviors(); i++) {
      clBehaviorBase *p_oBase = p_oSimManager->GetBehaviorObject(i);
      p_oBase->Action();
    }

    //Diameters should be the same
    p_oTree1->GetValue(p_oPop->GetDbhCode(p_oTree1->GetSpecies(), p_oTree1->GetType()), &fDiam);
    p_oTree2->GetValue(p_oPop->GetDbhCode(p_oTree2->GetSpecies(), p_oTree2->GetType()), &fDiam2);
    EXPECT_LT(fabs(fDiam - fDiam2), 0.001);

    //Heights should be different
    p_oTree1->GetValue(p_oPop->GetHeightCode(p_oTree1->GetSpecies(), p_oTree1->GetType()), &fHeight);
    p_oTree2->GetValue(p_oPop->GetHeightCode(p_oTree2->GetSpecies(), p_oTree2->GetType()), &fHeight2);
    EXPECT_GT(fabs(fHeight - fHeight2), 1);

    //Lgm should be different from shade for each
    p_oTree1->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree1->GetSpecies(), p_oTree1->GetType()), &fGrowth);
    EXPECT_GT(fabs(fGrowth - fShade), 0.1);

    p_oTree2->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree2->GetSpecies(), p_oTree2->GetType()), &fGrowth);
    EXPECT_GT(fabs(fGrowth - fShade), 0.1);
    delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

////////////////////////////////////////////////////////////////////////////
// TestBoundaryProcessing()
// Tests boundary conditions for NCI growth.
//
// Condition: The case in which two trees are at 0 distance. In this test,
// we don't really care what the outcome is, we just want to make sure that
// there isn't a divide-by-zero condition. WriteNCIGrowthXMLFile4() is used to
// do setup. Then some trees are created, two of which have the exact same
// coordinates.
////////////////////////////////////////////////////////////////////////////
TEST(NCIMasterGrowth, TestBoundaryProcessing) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    clTreePopulation * p_oPop;
    clTree *p_oTargetTree1,
    *p_oTargetTree2,
    *p_oTargetTree3;
    float fDiam;
    int iSpecies, iDamage;

    //Load our test file and get our tree population pointers
    p_oSimManager->ReadFile( WriteNCIGrowthXMLFile4() );
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );

    //Create our trees and set the damage level for each
    fDiam = 11;
    iSpecies = 0;
    iDamage = 0;
    p_oTargetTree1 = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, fDiam);
    p_oTargetTree1->SetValue(p_oPop->GetIntDataCode("stm_dmg",
        p_oTargetTree1->GetSpecies(),
        p_oTargetTree1->GetType()),
        iDamage);

    fDiam = 8;
    iSpecies = 1;
    iDamage = 1010;
    p_oTargetTree2 = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::sapling, fDiam);
    p_oTargetTree2->SetValue(p_oPop->GetIntDataCode("stm_dmg",
        p_oTargetTree2->GetSpecies(),
        p_oTargetTree2->GetType()),
        iDamage);

    fDiam = 15;
    iSpecies = 3;
    iDamage = 2010;
    p_oTargetTree3 = p_oPop->CreateTree(12, 12, iSpecies, clTreePopulation::adult, fDiam);
    p_oTargetTree3->SetValue(p_oPop->GetIntDataCode("stm_dmg",
        p_oTargetTree3->GetSpecies(),
        p_oTargetTree3->GetType()),
        iDamage);

    //Now do the run
    p_oSimManager->RunSim(1);
    delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

////////////////////////////////////////////////////////////////////////////
// TestErrorProcessing()
// Tests error processing for input files.
////////////////////////////////////////////////////////////////////////////
TEST(NCIMasterGrowth, TestErrorProcessing) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );

  //Max. radius of neighbor effects must be > 0
  try
  {
    p_oSimManager->ReadFile(WriteNCIGrowthXMLErrorFile1(true));
    FAIL() << "TestNCIMasterGrowth error processing didn't catch error for WriteNCIGrowthXMLErrorFile1A.";
  }
  catch (modelErr& err)
  {
    if (err.sFunction.compare("clNCITermDefault::DoSetup") != 0)
    {
      FAIL() << "TestNCIMasterGrowth error processing caught wrong error for WriteNCIGrowthXMLErrorFile1A.";
    }
    ;
  }

  //Max. radius of neighbor effects must be > 0
    try
    {
      p_oSimManager->ReadFile(WriteNCIGrowthXMLErrorFile1(false));
      FAIL() << "TestNCIMasterGrowth error processing didn't catch error for WriteNCIGrowthXMLErrorFile1B.";
    }
    catch (modelErr& err)
    {
      if (err.sFunction.compare("clNCITermWithNeighborDamage::DoSetup") != 0)
      {
        FAIL() << "TestNCIMasterGrowth error processing caught wrong error for WriteNCIGrowthXMLErrorFile1B.";
      }
      ;
    }

  try
  {
    p_oSimManager->ReadFile(WriteNCIGrowthXMLErrorFile2());
    FAIL() << "TestNCIMasterGrowth error processing didn't catch error for WriteNCIGrowthXMLErrorFile2.";
  }
  catch (modelErr& err)
  {
    if (err.sFunction.compare("clNCIMasterGrowth::ValidateData") != 0)
    {
      FAIL() << "TestNCIMasterGrowth error processing caught wrong error for WriteNCIGrowthXMLErrorFile2.";
    }
    ;
  }

  try
  {
    p_oSimManager->ReadFile(WriteNCIGrowthXMLErrorFile3());
    FAIL() << "TestNCIMasterGrowth error processing didn't catch error for WriteNCIGrowthXMLErrorFile3.";
  }
  catch (modelErr& err)
  {
    if (err.sFunction.compare("clSizeEffectDefault::DoSetup") != 0)
    {
      FAIL() << "TestNCIMasterGrowth error processing caught wrong error for WriteNCIGrowthXMLErrorFile3.";
    }
    ;
  }

  try
  {
    p_oSimManager->ReadFile(WriteNCIGrowthXMLErrorFile4());
    FAIL() << "TestNCIMasterGrowth error processing didn't catch error for WriteNCIGrowthXMLErrorFile4.";
  }
  catch (modelErr& err)
  {
    if (err.sFunction.compare("clSizeEffectDefault::DoSetup") != 0)
    {
      FAIL() << "TestNCIMasterGrowth error processing caught wrong error for WriteNCIGrowthXMLErrorFile4.";
    }
    ;
  }

  try
  {
    p_oSimManager->ReadFile(WriteNCIGrowthXMLErrorFile5());
    FAIL() << "TestNCIMasterGrowth error processing didn't catch error for WriteNCIGrowthXMLErrorFile5.";
  }
  catch (modelErr& err)
  {
    if (err.sFunction.compare("clNCITermWithNeighborDamage::DoSetup") != 0)
    {
      FAIL() << "TestNCIMasterGrowth error processing caught wrong error for WriteNCIGrowthXMLErrorFile5.";
    }
    ;
  }

  try
  {
    p_oSimManager->ReadFile(WriteNCIGrowthXMLErrorFile6());
    FAIL() << "TestNCIMasterGrowth error processing didn't catch error for WriteNCIGrowthXMLErrorFile6.";
  }
  catch (modelErr& err)
  {
    if (err.sFunction.compare("clNCITermWithNeighborDamage::DoSetup") != 0)
    {
      FAIL() << "TestNCIMasterGrowth error processing caught wrong error for WriteNCIGrowthXMLErrorFile6.";
    }
    ;
  }

  try
  {
    p_oSimManager->ReadFile(WriteNCIGrowthXMLErrorFile7());
    FAIL() << "TestNCIMasterGrowth error processing didn't catch error for WriteNCIGrowthXMLErrorFile7.";
  }
  catch (modelErr& err)
  {
    if (err.sFunction.compare("clNCITermWithNeighborDamage::DoSetup") != 0)
    {
      FAIL() << "TestNCIMasterGrowth error processing caught wrong error for WriteNCIGrowthXMLErrorFile7.";
    }
    ;
  }

  try
  {
    p_oSimManager->ReadFile(WriteNCIGrowthXMLErrorFile8());
    FAIL() << "TestNCIMasterGrowth error processing didn't catch error for WriteNCIGrowthXMLErrorFile8.";
  }
  catch (modelErr& err)
  {
    if (err.sFunction.compare("clNCITermWithNeighborDamage::DoSetup") != 0)
    {
      FAIL() << "TestNCIMasterGrowth error processing caught wrong error for WriteNCIGrowthXMLErrorFile8.";
    }
    ;
  }

  try
  {
    p_oSimManager->ReadFile(WriteNCIGrowthXMLErrorFile9());
    FAIL() << "TestNCIMasterGrowth error processing didn't catch error for WriteNCIGrowthXMLErrorFile9.";
  }
  catch (modelErr& err)
  {
    if (err.sFunction.compare("clDamageEffectDefault::DoSetup") != 0)
    {
      FAIL() << "TestNCIMasterGrowth error processing caught wrong error for WriteNCIGrowthXMLErrorFile9.";
    }
    ;
  }

  try
  {
    p_oSimManager->ReadFile(WriteNCIGrowthXMLErrorFile10());
    FAIL() << "TestNCIMasterGrowth error processing didn't catch error for WriteNCIGrowthXMLErrorFile10.";
  }
  catch (modelErr& err)
  {
    if (err.sFunction.compare("clDamageEffectDefault::DoSetup") != 0)
    {
      FAIL() << "TestNCIMasterGrowth error processing caught wrong error for WriteNCIGrowthXMLErrorFile10.";
    }
    ;
  }

  try
  {
    p_oSimManager->ReadFile(WriteNCIGrowthXMLErrorFile11());
    FAIL() << "TestNCIMasterGrowth error processing didn't catch error for WriteNCIGrowthXMLErrorFile11.";
  }
  catch (modelErr& err)
  {
    if (err.sFunction.compare("clDamageEffectDefault::DoSetup") != 0)
    {
      FAIL() << "TestNCIMasterGrowth error processing caught wrong error for WriteNCIGrowthXMLErrorFile11.";
    }
    ;
  }

  try
  {
    p_oSimManager->ReadFile(WriteNCIGrowthXMLErrorFile12());
    FAIL() << "TestNCIMasterGrowth error processing didn't catch error for WriteNCIGrowthXMLErrorFile12.";
  }
  catch (modelErr& err)
  {
    if (err.sFunction.compare("clDamageEffectDefault::DoSetup") != 0)
    {
      FAIL() << "TestNCIMasterGrowth error processing caught wrong error for WriteNCIGrowthXMLErrorFile12.";
    }
    ;
  }

  try
 {
   p_oSimManager->ReadFile(WriteNCIGrowthXMLErrorFile13());
   FAIL() << "TestNCIMasterGrowth error processing didn't catch error for WriteNCIGrowthXMLErrorFile13.";
 }
 catch (modelErr& err)
 {
   if (err.sFunction.compare("clShadingEffectDefault::DoSetup") != 0)
   {
     FAIL() << "TestNCIMasterGrowth error processing caught wrong error for WriteNCIGrowthXMLErrorFile13.";
   }
   ;
 }

 try
 {
   p_oSimManager->ReadFile(WriteNCIGrowthXMLErrorFile14(true));
   FAIL() << "TestNCIMasterGrowth error processing didn't catch error for WriteNCIGrowthXMLErrorFile14.";
 }
 catch (modelErr& err)
 {
   if (err.sFunction.compare("clNCITermDefault::DoSetup") != 0)
   {
     FAIL() << "TestNCIMasterGrowth error processing caught wrong error for WriteNCIGrowthXMLErrorFile14.";
   }
   ;
 }

 try
  {
    p_oSimManager->ReadFile(WriteNCIGrowthXMLErrorFile14(false));
    FAIL() << "TestNCIMasterGrowth error processing didn't catch error for WriteNCIGrowthXMLErrorFile14.";
  }
  catch (modelErr& err)
  {
    if (err.sFunction.compare("clNCITermWithNeighborDamage::DoSetup") != 0)
    {
      FAIL() << "TestNCIMasterGrowth error processing caught wrong error for WriteNCIGrowthXMLErrorFile14.";
    }
    ;
  }

 delete p_oSimManager;
}

////////////////////////////////////////////////////////////////////////////
// TestRun1()
// Performs a test run of NCI growth - a Puerto-Rico-like situation. This
// run has no shading effect and uses damage effect.
// WriteNCIGrowthXMLFile4() performs setup for a 1-year timestep; then WriteNCIGrowthXMLFile5()
// performs setup for an otherwise identical 3-year timestep.
//
// There are 8 target trees whose values will be tested according to the
// testing spreadsheet prepared.
////////////////////////////////////////////////////////////////////////////
TEST(NCIMasterGrowth, TestRun1) {

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
    float fDiam, fExpectedDiam;
    int iSpecies, iDamage;

    //***********************************
    // Run 1 - 1 year timestep
    //***********************************
    //Load our test file and get our tree population pointers
    p_oSimManager->ReadFile( WriteNCIGrowthXMLFile4() );
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );

    //Create our trees and set the damage level for each
    fDiam = 11;
    iSpecies = 0;
    iDamage = 0;
    p_oTargetTree1 = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, fDiam);
    p_oTargetTree1->SetValue(p_oPop->GetIntDataCode("stm_dmg",
        p_oTargetTree1->GetSpecies(),
        p_oTargetTree1->GetType()),
        iDamage);

    fDiam = 8;
    iSpecies = 1;
    iDamage = 1000;
    p_oTargetTree2 = p_oPop->CreateTree(20, 20, iSpecies, clTreePopulation::sapling, fDiam);
    p_oTargetTree2->SetValue(p_oPop->GetIntDataCode("stm_dmg",
        p_oTargetTree2->GetSpecies(),
        p_oTargetTree2->GetType()),
        iDamage);

    fDiam = 15;
    iSpecies = 3;
    iDamage = 2000;
    p_oTargetTree3 = p_oPop->CreateTree(30, 30, iSpecies, clTreePopulation::adult, fDiam);
    p_oTargetTree3->SetValue(p_oPop->GetIntDataCode("stm_dmg",
        p_oTargetTree3->GetSpecies(),
        p_oTargetTree3->GetType()),
        iDamage);

    fDiam = 10.5;
    iSpecies = 0;
    iDamage = 0;
    p_oTargetTree4 = p_oPop->CreateTree(50, 50, iSpecies, clTreePopulation::adult, fDiam);
    p_oTargetTree4->SetValue(p_oPop->GetIntDataCode("stm_dmg",
        p_oTargetTree4->GetSpecies(),
        p_oTargetTree4->GetType()),
        iDamage);

    fDiam = 15;
    iSpecies = 1;
    iDamage = 1000;
    p_oTargetTree5 = p_oPop->CreateTree(53, 52, iSpecies, clTreePopulation::adult, fDiam);
    p_oTargetTree5->SetValue(p_oPop->GetIntDataCode("stm_dmg",
        p_oTargetTree5->GetSpecies(),
        p_oTargetTree5->GetType()),
        iDamage);

    fDiam = 25;
    iSpecies = 3;
    iDamage = 2000;
    p_oTargetTree6 = p_oPop->CreateTree(59, 50, iSpecies, clTreePopulation::adult, fDiam);
    p_oTargetTree6->SetValue(p_oPop->GetIntDataCode("stm_dmg",
        p_oTargetTree6->GetSpecies(),
        p_oTargetTree6->GetType()),
        iDamage);

    fDiam = 30;
    iSpecies = 0;
    iDamage = 2000;
    p_oTargetTree7 = p_oPop->CreateTree(50, 59, iSpecies, clTreePopulation::adult, fDiam);
    p_oTargetTree7->SetValue(p_oPop->GetIntDataCode("stm_dmg",
        p_oTargetTree7->GetSpecies(),
        p_oTargetTree7->GetType()),
        iDamage);

    fDiam = 45;
    iSpecies = 1;
    iDamage = 0;
    p_oTargetTree8 = p_oPop->CreateTree(55, 55, iSpecies, clTreePopulation::adult, fDiam);
    p_oTargetTree8->SetValue(p_oPop->GetIntDataCode("stm_dmg",
        p_oTargetTree8->GetSpecies(),
        p_oTargetTree8->GetType()),
        iDamage);

    fDiam = 1;
    iSpecies = 3;
    iDamage = 0;
    p_oTargetTree9 = p_oPop->CreateTree(30, 10, iSpecies, clTreePopulation::sapling, fDiam);


    //Now create all the neighbors that are too small or dead to compete
    p_oPop->CreateTree(56, 56, 0, clTreePopulation::snag, 30);
    p_oPop->CreateTree(56, 56, 0, clTreePopulation::seedling, 0.2);
    p_oPop->CreateTree(52, 52, 0, clTreePopulation::sapling, 4);
    p_oPop->CreateTree(53, 53, 1, clTreePopulation::sapling, 4);
    p_oPop->CreateTree(54, 54, 2, clTreePopulation::sapling, 4);
    p_oPop->CreateTree(57, 57, 3, clTreePopulation::sapling, 4);
    p_oTargetTree = p_oPop->CreateTree(58, 58, 1, clTreePopulation::adult, 20);
    p_oTargetTree->SetValue(p_oPop->GetIntDataCode("dead", p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), storm);

    //Now do the run
    p_oSimManager->RunSim(1);

    //Check the diameters and growth of the target trees
    fExpectedDiam = 12.02578252;
    p_oTargetTree = p_oTargetTree1;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam), 0.01);

    fExpectedDiam = 8.566136279;
    p_oTargetTree = p_oTargetTree2;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam), 0.01);

    fExpectedDiam = 15.62491548;
    p_oTargetTree = p_oTargetTree3;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam), 0.01);

    fExpectedDiam = 11.2924378;
    p_oTargetTree = p_oTargetTree4;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam), 0.01);

    fExpectedDiam = 15.78042057;
    p_oTargetTree = p_oTargetTree5;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam), 0.01);

    fExpectedDiam = 25.52586497;
    p_oTargetTree = p_oTargetTree6;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam), 0.01);

    fExpectedDiam = 30.37529052;
    p_oTargetTree = p_oTargetTree7;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam), 0.01);

    fExpectedDiam = 46.24530477;
    p_oTargetTree = p_oTargetTree8;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam), 0.01);

    fExpectedDiam = 2.6016;
    p_oTargetTree = p_oTargetTree9;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam), 0.01);

    //***********************************
    // Run 2 - 3 year timestep
    //***********************************
    //Load our test file and get our tree population pointers
    p_oSimManager->ReadFile( WriteNCIGrowthXMLFile5() );
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );

    //Create our trees and set the damage level for each
    fDiam = 11;
    iSpecies = 0;
    iDamage = 0;
    p_oTargetTree1 = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, fDiam);
    p_oTargetTree1->SetValue(p_oPop->GetIntDataCode("stm_dmg",
        p_oTargetTree1->GetSpecies(),
        p_oTargetTree1->GetType()),
        iDamage);

    fDiam = 8;
    iSpecies = 1;
    iDamage = 1000;
    p_oTargetTree2 = p_oPop->CreateTree(20, 20, iSpecies, clTreePopulation::sapling, fDiam);
    p_oTargetTree2->SetValue(p_oPop->GetIntDataCode("stm_dmg",
        p_oTargetTree2->GetSpecies(),
        p_oTargetTree2->GetType()),
        iDamage);

    fDiam = 15;
    iSpecies = 3;
    iDamage = 2000;
    p_oTargetTree3 = p_oPop->CreateTree(30, 30, iSpecies, clTreePopulation::adult, fDiam);
    p_oTargetTree3->SetValue(p_oPop->GetIntDataCode("stm_dmg",
        p_oTargetTree3->GetSpecies(),
        p_oTargetTree3->GetType()),
        iDamage);

    fDiam = 10.5;
    iSpecies = 0;
    iDamage = 0;
    p_oTargetTree4 = p_oPop->CreateTree(50, 50, iSpecies, clTreePopulation::adult, fDiam);
    p_oTargetTree4->SetValue(p_oPop->GetIntDataCode("stm_dmg",
        p_oTargetTree4->GetSpecies(),
        p_oTargetTree4->GetType()),
        iDamage);

    fDiam = 15;
    iSpecies = 1;
    iDamage = 1000;
    p_oTargetTree5 = p_oPop->CreateTree(53, 52, iSpecies, clTreePopulation::adult, fDiam);
    p_oTargetTree5->SetValue(p_oPop->GetIntDataCode("stm_dmg",
        p_oTargetTree5->GetSpecies(),
        p_oTargetTree5->GetType()),
        iDamage);

    fDiam = 25;
    iSpecies = 3;
    iDamage = 2000;
    p_oTargetTree6 = p_oPop->CreateTree(59, 50, iSpecies, clTreePopulation::adult, fDiam);
    p_oTargetTree6->SetValue(p_oPop->GetIntDataCode("stm_dmg",
        p_oTargetTree6->GetSpecies(),
        p_oTargetTree6->GetType()),
        iDamage);

    fDiam = 30;
    iSpecies = 0;
    iDamage = 2000;
    p_oTargetTree7 = p_oPop->CreateTree(50, 59, iSpecies, clTreePopulation::adult, fDiam);
    p_oTargetTree7->SetValue(p_oPop->GetIntDataCode("stm_dmg",
        p_oTargetTree7->GetSpecies(),
        p_oTargetTree7->GetType()),
        iDamage);

    fDiam = 45;
    iSpecies = 1;
    iDamage = 0;
    p_oTargetTree8 = p_oPop->CreateTree(55, 55, iSpecies, clTreePopulation::adult, fDiam);
    p_oTargetTree8->SetValue(p_oPop->GetIntDataCode("stm_dmg",
        p_oTargetTree8->GetSpecies(),
        p_oTargetTree8->GetType()),
        iDamage);

    fDiam = 1;
    iSpecies = 3;
    iDamage = 0;
    p_oTargetTree9 = p_oPop->CreateTree(30, 10, iSpecies, clTreePopulation::sapling, fDiam);

    //Now create all the neighbors that are too small to compete
    p_oPop->CreateTree(56, 56, 0, clTreePopulation::seedling, 0.2);
    p_oPop->CreateTree(52, 52, 0, clTreePopulation::sapling, 4);
    p_oPop->CreateTree(53, 53, 1, clTreePopulation::sapling, 4);
    p_oPop->CreateTree(54, 54, 2, clTreePopulation::sapling, 4);
    p_oPop->CreateTree(57, 57, 3, clTreePopulation::sapling, 4);
    p_oPop->CreateTree(57, 57, 3, clTreePopulation::sapling, 4);
    p_oTargetTree = p_oPop->CreateTree(58, 58, 1, clTreePopulation::adult, 20);
    p_oTargetTree->SetValue(p_oPop->GetIntDataCode("dead", p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), storm);

    //Now do the run
    p_oSimManager->RunSim(1);

    //Check the diameters and growth of the target trees
    fExpectedDiam = 14.08875462;
    p_oTargetTree = p_oTargetTree1;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam), 0.01);

    fExpectedDiam = 9.754968806;
    p_oTargetTree = p_oTargetTree2;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam), 0.01);

    fExpectedDiam = 16.8769391;
    p_oTargetTree = p_oTargetTree3;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam), 0.01);

    fExpectedDiam = 12.90645617;
    p_oTargetTree = p_oTargetTree4;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam), 0.01);

    fExpectedDiam = 17.39443379;
    p_oTargetTree = p_oTargetTree5;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam), 0.01);

    fExpectedDiam = 26.57309113;
    p_oTargetTree = p_oTargetTree6;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam), 0.01);

    fExpectedDiam = 31.12786623;
    p_oTargetTree = p_oTargetTree7;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam), 0.01);

    fExpectedDiam = 48.75968063;
    p_oTargetTree = p_oTargetTree8;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam), 0.01);

    fExpectedDiam = 5.8048;
    p_oTargetTree = p_oTargetTree9;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam), 0.01);

    delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

////////////////////////////////////////////////////////////////////////////
// TestRun2()
// Tests the growth calculations at two timestep lengths in a BC-like
// situation. It uses no storm damage and simplified crowding -
// no size sensitivity to NCI (g = 0, d = 1). It does use Shading.
// WriteNCIGrowthXMLFile2() is used to do setup in the first case, for a 1 year
// timestep. Growth is checked for two target trees. Then WriteNCIGrowthXMLFile3()
// does setup for a 3 year timestep and the growth is checked for the same two
// trees.
//
// The first target tree is too far away from the other trees to be affected.
// It has the lowest possible value of shade and a zero NCI. The second
// target tree is surrounded by 4 trees affecting shade and NCI and two which
// do not.
////////////////////////////////////////////////////////////////////////////
TEST(NCIMasterGrowth, TestRun2) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    clTreePopulation * p_oPop;
    clTree *p_oTargetTree1, *p_oTargetTree2, *p_oTree;
    float fDiam, fExpectedDiam, fGrowth, fExpectedGrowth;

    //***********************************
    // Run 1 - 1 year timestep
    //***********************************
    //Load our test file and get our tree population pointers
    p_oSimManager->ReadFile( WriteNCIGrowthXMLFile2() );
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );

    //Create our two target trees
    fDiam = 11;
    p_oTargetTree1 = p_oPop->CreateTree(10, 10, 0, clTreePopulation::adult, fDiam);

    fDiam = 10.5;
    p_oTargetTree2 = p_oPop->CreateTree(50, 50, 0, clTreePopulation::adult, fDiam);

    //Now create all the neighbors
    p_oPop->CreateTree(53, 52, 1, clTreePopulation::adult, 15);
    p_oPop->CreateTree(59, 50, 2, clTreePopulation::adult, 25);
    p_oPop->CreateTree(50, 59, 0, clTreePopulation::adult, 30);
    p_oPop->CreateTree(55, 55, 1, clTreePopulation::adult, 45);
    p_oPop->CreateTree(60, 61, 2, clTreePopulation::adult, 15);
    p_oPop->CreateTree(56, 56, 0, clTreePopulation::seedling, 0.2);
    p_oPop->CreateTree(52, 52, 0, clTreePopulation::sapling, 4);
    p_oPop->CreateTree(53, 53, 1, clTreePopulation::sapling, 4);
    p_oPop->CreateTree(57, 57, 3, clTreePopulation::sapling, 4);
    p_oPop->CreateTree(56, 56, 0, clTreePopulation::snag, 30);
    p_oTree = p_oPop->CreateTree(54, 54, 0, clTreePopulation::adult, 20);
    p_oTree->SetValue(p_oPop->GetIntDataCode("dead", p_oTree->GetSpecies(), p_oTree->GetType()), storm);

    //Now do the run
    p_oSimManager->RunSim(1);

    //Check the diameters and growth of the target trees
    fExpectedDiam = 11.94022982;
    fExpectedGrowth = 4.70114909;
    p_oTargetTree1->GetValue(p_oPop->GetDbhCode(p_oTargetTree1->GetSpecies(), p_oTargetTree1->GetType()), &fDiam);
    p_oTargetTree1->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTargetTree1->GetSpecies(), p_oTargetTree1->GetType()), &fGrowth);
    EXPECT_LT(fabs(fDiam - fExpectedDiam), 0.01);
    EXPECT_LT(fabs(fGrowth - fExpectedGrowth), 0.01);

    fExpectedDiam = 11.39981688;
    fExpectedGrowth = 4.49908438;
    p_oTargetTree2->GetValue(p_oPop->GetDbhCode(p_oTargetTree2->GetSpecies(), p_oTargetTree2->GetType()), &fDiam);
    p_oTargetTree2->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTargetTree2->GetSpecies(), p_oTargetTree2->GetType()), &fGrowth);
    EXPECT_LT(fabs(fDiam - fExpectedDiam), 0.01);
    EXPECT_LT(fabs(fGrowth - fExpectedGrowth), 0.01);

    //***********************************
    // Run 2 - 3 year timestep
    //***********************************
    //Load our test file and get our tree population pointers
    p_oSimManager->ReadFile( WriteNCIGrowthXMLFile3() );
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );

    //Create our two target trees
    fDiam = 11;
    p_oTargetTree1 = p_oPop->CreateTree(10, 10, 0, clTreePopulation::adult, fDiam);

    fDiam = 10.5;
    p_oTargetTree2 = p_oPop->CreateTree(50, 50, 0, clTreePopulation::adult, fDiam);

    //Now create all the neighbors
    p_oPop->CreateTree(53, 52, 1, clTreePopulation::adult, 15);
    p_oPop->CreateTree(59, 50, 2, clTreePopulation::adult, 25);
    p_oPop->CreateTree(50, 59, 0, clTreePopulation::adult, 30);
    p_oPop->CreateTree(55, 55, 1, clTreePopulation::adult, 45);
    p_oPop->CreateTree(60, 61, 2, clTreePopulation::adult, 15);
    p_oPop->CreateTree(56, 56, 0, clTreePopulation::seedling, 0.2);
    p_oPop->CreateTree(52, 52, 0, clTreePopulation::sapling, 4);
    p_oPop->CreateTree(53, 53, 1, clTreePopulation::sapling, 4);
    p_oTree = p_oPop->CreateTree(54, 54, 0, clTreePopulation::adult, 20);
    p_oTree->SetValue(p_oPop->GetIntDataCode("dead", p_oTree->GetSpecies(), p_oTree->GetType()), storm);

    //Now do the run
    p_oSimManager->RunSim(1);

    //Check the diameters and growth of the target trees
    fExpectedDiam = 13.83037522;
    fExpectedGrowth = 4.71729204;
    p_oTargetTree1->GetValue(p_oPop->GetDbhCode(p_oTargetTree1->GetSpecies(), p_oTargetTree1->GetType()), &fDiam);
    p_oTargetTree1->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTargetTree1->GetSpecies(), p_oTargetTree1->GetType()), &fGrowth);
    EXPECT_LT(fabs(fDiam - fExpectedDiam), 0.01);
    EXPECT_LT(fabs(fGrowth - fExpectedGrowth), 0.01);

    fExpectedDiam = 13.20914701;
    fExpectedGrowth = 4.515245025;
    p_oTargetTree2->GetValue(p_oPop->GetDbhCode(p_oTargetTree2->GetSpecies(), p_oTargetTree2->GetType()), &fDiam);
    p_oTargetTree2->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTargetTree2->GetSpecies(), p_oTargetTree2->GetType()), &fGrowth);
    EXPECT_LT(fabs(fDiam - fExpectedDiam), 0.01);
    EXPECT_LT(fabs(fGrowth - fExpectedGrowth), 0.01);
    delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

////////////////////////////////////////////////////////////////////////////
// TestRun3()
// Performs Test Run 3. This run has no storm damage, has variability in
// functions between species, doesn't use NCImax, and doesn't use the DBH
// divisor.
//
// WriteNCIGrowthXMLFile6() is used to do setup for the first run, for a 1 year
// timestep. Growth is checked for five target trees. Then WriteNCIGrowthXMLFile7()
// does setup for a 3 year timestep and the growth is checked for the same
// five trees.
////////////////////////////////////////////////////////////////////////////
TEST(NCIMasterGrowth, TestRun3) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    clTreePopulation * p_oPop;
    clTree *p_oTargetTree1,
    *p_oTargetTree2,
    *p_oTargetTree3,
    *p_oTargetTree4,
    *p_oTargetTree5,
    *p_oTargetTree;
    float fDiam, fExpectedDiam, fShade, fGrowth, fExpectedGrowth;
    int iSpecies;

    //***********************************
    // Run 1 - 1 year timestep
    //***********************************

    //Load our test file and get our tree population pointers
    p_oSimManager->ReadFile( WriteNCIGrowthXMLFile6() );
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );

    //Create our trees and set their light levels
    fDiam = 15;
    iSpecies = 1;
    fShade = 1;
    p_oTargetTree1 = p_oPop->CreateTree(53, 52, iSpecies, clTreePopulation::adult, fDiam);
    p_oTargetTree1->SetValue(p_oPop->GetFloatDataCode("Light",
        p_oTargetTree1->GetSpecies(),
        p_oTargetTree1->GetType()),
        fShade);


    fDiam = 25;
    iSpecies = 3;
    fShade = 0.2;
    p_oTargetTree2 = p_oPop->CreateTree(59, 50, iSpecies, clTreePopulation::adult, fDiam);
    p_oTargetTree2->SetValue(p_oPop->GetFloatDataCode("Light",
        p_oTargetTree2->GetSpecies(),
        p_oTargetTree2->GetType()),
        fShade);

    fDiam = 30;
    iSpecies = 0;
    fShade = 0.4;
    p_oTargetTree3 = p_oPop->CreateTree(50, 59, iSpecies, clTreePopulation::adult, fDiam);
    p_oTargetTree3->SetValue(p_oPop->GetFloatDataCode("Light",
        p_oTargetTree3->GetSpecies(),
        p_oTargetTree3->GetType()),
        fShade);

    fDiam = 45;
    iSpecies = 1;
    fShade = 0.8;
    p_oTargetTree4 = p_oPop->CreateTree(55, 55, iSpecies, clTreePopulation::adult, fDiam);
    p_oTargetTree4->SetValue(p_oPop->GetFloatDataCode("Light",
        p_oTargetTree4->GetSpecies(),
        p_oTargetTree4->GetType()),
        fShade);

    fDiam = 10.5;
    iSpecies = 0;
    fShade = 0;
    p_oTargetTree5 = p_oPop->CreateTree(50, 50, iSpecies, clTreePopulation::adult, fDiam);
    p_oTargetTree5->SetValue(p_oPop->GetFloatDataCode("Light",
        p_oTargetTree5->GetSpecies(),
        p_oTargetTree5->GetType()),
        fShade);

    //Now create all the neighbors that are too small or dead to compete
    p_oPop->CreateTree(52, 52, 0, clTreePopulation::sapling, 9);
    p_oPop->CreateTree(53, 53, 1, clTreePopulation::adult, 11);
    p_oPop->CreateTree(54, 54, 3, clTreePopulation::adult, 13);
    p_oPop->CreateTree(56, 56, 2, clTreePopulation::adult, 15);
    p_oPop->CreateTree(56, 56, 0, clTreePopulation::snag, 30);
    p_oTargetTree = p_oPop->CreateTree(58, 58, 1, clTreePopulation::adult, 20);
    p_oTargetTree->SetValue(p_oPop->GetIntDataCode("dead", p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), storm);

    //Now do the run - but don't let SailLight go, or it will mess up the
    //shading values we've assigned
    for (int i = 0; i < p_oSimManager->GetNumberOfBehaviors(); i++) {
      if (p_oSimManager->GetBehaviorObject(i)->GetName().compare("ncigrowthshell") == 0) {
        p_oSimManager->GetBehaviorObject(i)->Action();
        break;
      }
    }

    //Check the diameters and growth of the target trees
    fExpectedDiam = 15.91129062;
    fExpectedGrowth = 4.556453117;
    p_oTargetTree = p_oTargetTree1;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fDiam);
    p_oTargetTree->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fGrowth);
    EXPECT_LT(fabs(fDiam - fExpectedDiam), 0.01);
    EXPECT_LT(fabs(fGrowth - fExpectedGrowth), 0.01);

    fExpectedDiam = 27.30600165;
    fExpectedGrowth = 11.53000827;
    p_oTargetTree = p_oTargetTree2;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fDiam);
    p_oTargetTree->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fGrowth);
    EXPECT_LT(fabs(fDiam - fExpectedDiam), 0.01);
    EXPECT_LT(fabs(fGrowth - fExpectedGrowth), 0.01);

    fExpectedDiam = 31.01554876;
    fExpectedGrowth = 5.077743794;
    p_oTargetTree = p_oTargetTree3;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fDiam);
    p_oTargetTree->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fGrowth);
    EXPECT_LT(fabs(fDiam - fExpectedDiam), 0.01);
    EXPECT_LT(fabs(fGrowth - fExpectedGrowth), 0.01);

    fExpectedDiam = 46.44982526;
    fExpectedGrowth = 7.249126321;
    p_oTargetTree = p_oTargetTree4;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fDiam);
    p_oTargetTree->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fGrowth);
    EXPECT_LT(fabs(fDiam - fExpectedDiam), 0.01);
    EXPECT_LT(fabs(fGrowth - fExpectedGrowth), 0.01);

    fExpectedDiam = 11.53806956;
    fExpectedGrowth = 5.190347813;
    p_oTargetTree = p_oTargetTree5;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fDiam);
    p_oTargetTree->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fGrowth);
    EXPECT_LT(fabs(fDiam - fExpectedDiam), 0.01);
    EXPECT_LT(fabs(fGrowth - fExpectedGrowth), 0.01);

    //***********************************
    // Run 2 - 3 year timestep
    //***********************************
    //Load our test file and get our tree population pointers
    p_oSimManager->ReadFile( WriteNCIGrowthXMLFile7() );
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );

    //Create our trees and set their light levels
    fDiam = 15;
    iSpecies = 1;
    fShade = 1;
    p_oTargetTree1 = p_oPop->CreateTree(53, 52, iSpecies, clTreePopulation::adult, fDiam);
    p_oTargetTree1->SetValue(p_oPop->GetFloatDataCode("Light",
        p_oTargetTree1->GetSpecies(),
        p_oTargetTree1->GetType()),
        fShade);


    fDiam = 25;
    iSpecies = 3;
    fShade = 0.2;
    p_oTargetTree2 = p_oPop->CreateTree(59, 50, iSpecies, clTreePopulation::adult, fDiam);
    p_oTargetTree2->SetValue(p_oPop->GetFloatDataCode("Light",
        p_oTargetTree2->GetSpecies(),
        p_oTargetTree2->GetType()),
        fShade);

    fDiam = 30;
    iSpecies = 0;
    fShade = 0.4;
    p_oTargetTree3 = p_oPop->CreateTree(50, 59, iSpecies, clTreePopulation::adult, fDiam);
    p_oTargetTree3->SetValue(p_oPop->GetFloatDataCode("Light",
        p_oTargetTree3->GetSpecies(),
        p_oTargetTree3->GetType()),
        fShade);

    fDiam = 45;
    iSpecies = 1;
    fShade = 0.8;
    p_oTargetTree4 = p_oPop->CreateTree(55, 55, iSpecies, clTreePopulation::adult, fDiam);
    p_oTargetTree4->SetValue(p_oPop->GetFloatDataCode("Light",
        p_oTargetTree4->GetSpecies(),
        p_oTargetTree4->GetType()),
        fShade);

    fDiam = 10.5;
    iSpecies = 0;
    fShade = 0;
    p_oTargetTree5 = p_oPop->CreateTree(50, 50, iSpecies, clTreePopulation::adult, fDiam);
    p_oTargetTree5->SetValue(p_oPop->GetFloatDataCode("Light",
        p_oTargetTree5->GetSpecies(),
        p_oTargetTree5->GetType()),
        fShade);

    //Now create all the neighbors that are too small to compete
    p_oPop->CreateTree(52, 52, 0, clTreePopulation::sapling, 9);
    p_oPop->CreateTree(53, 53, 1, clTreePopulation::adult, 11);
    p_oPop->CreateTree(54, 54, 3, clTreePopulation::adult, 13);
    p_oPop->CreateTree(56, 56, 2, clTreePopulation::adult, 15);
    p_oTargetTree = p_oPop->CreateTree(58, 58, 1, clTreePopulation::adult, 20);
    p_oTargetTree->SetValue(p_oPop->GetIntDataCode("dead", p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), storm);

    //Now do the run - but don't let SailLight go, or it will mess up the
    //shading values we've assigned
    for (int i = 0; i < p_oSimManager->GetNumberOfBehaviors(); i++) {
      if (p_oSimManager->GetBehaviorObject(i)->GetName().compare("ncigrowthshell") == 0) {
        p_oSimManager->GetBehaviorObject(i)->Action();
        break;
      }
    }

    //Check the diameters and growth of the target trees
    fExpectedDiam = 17.80779863;
    fExpectedGrowth = 4.679664378;
    p_oTargetTree = p_oTargetTree1;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fDiam);
    p_oTargetTree->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fGrowth);
    EXPECT_LT(fabs(fDiam - fExpectedDiam), 0.01);
    EXPECT_LT(fabs(fGrowth - fExpectedGrowth), 0.01);

    fExpectedDiam = 31.82738854;
    fExpectedGrowth = 11.37898089;
    p_oTargetTree = p_oTargetTree2;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fDiam);
    p_oTargetTree->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fGrowth);
    EXPECT_LT(fabs(fDiam - fExpectedDiam), 0.01);
    EXPECT_LT(fabs(fGrowth - fExpectedGrowth), 0.01);

    fExpectedDiam = 33.04706798;
    fExpectedGrowth = 5.078446636;
    p_oTargetTree = p_oTargetTree3;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fDiam);
    p_oTargetTree->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fGrowth);
    EXPECT_LT(fabs(fDiam - fExpectedDiam), 0.01);
    EXPECT_LT(fabs(fGrowth - fExpectedGrowth), 0.01);

    fExpectedDiam = 49.38354469;
    fExpectedGrowth = 7.305907813;
    p_oTargetTree = p_oTargetTree4;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fDiam);
    p_oTargetTree->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fGrowth);
    EXPECT_LT(fabs(fDiam - fExpectedDiam), 0.01);
    EXPECT_LT(fabs(fGrowth - fExpectedGrowth), 0.01);

    fExpectedDiam = 13.62688973;
    fExpectedGrowth = 5.211482877;
    p_oTargetTree = p_oTargetTree5;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fDiam);
    p_oTargetTree->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fGrowth);
    EXPECT_LT(fabs(fDiam - fExpectedDiam), 0.01);
    EXPECT_LT(fabs(fGrowth - fExpectedGrowth), 0.01);
    delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

////////////////////////////////////////////////////////////////////////////
// TestRun4()
// Performs Test Run 4. This run tests variability in light behavior
// requirements, but is otherwise almost exactly like TestRun3.
//
// WriteNCIGrowthXMLFile8() is used to do setup for the first run, for a 1 year
// timestep. Growth is checked for five target trees. Then WriteNCIGrowthXMLFile9()
// does setup for a 3 year timestep and the growth is checked for the same
// five trees.
////////////////////////////////////////////////////////////////////////////
TEST(NCIMasterGrowth, TestRun4) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    clTreePopulation * p_oPop;
    clTree *p_oTargetTree1,
    *p_oTargetTree2,
    *p_oTargetTree3,
    *p_oTargetTree4,
    *p_oTargetTree5,
    *p_oTargetTree;
    float fDiam, fExpectedDiam, fShade, fGrowth, fExpectedGrowth;
    int iSpecies;

    //***********************************
    // Run 1 - 1 year timestep
    //***********************************

    //Load our test file and get our tree population pointers
    p_oSimManager->ReadFile( WriteNCIGrowthXMLFile8() );
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );

    //Create our trees and set their light levels
    fDiam = 15;
    iSpecies = 1;
    p_oTargetTree1 = p_oPop->CreateTree(53, 52, iSpecies, clTreePopulation::adult, fDiam);


    fDiam = 25;
    iSpecies = 3;
    fShade = 0.2;
    p_oTargetTree2 = p_oPop->CreateTree(59, 50, iSpecies, clTreePopulation::adult, fDiam);
    p_oTargetTree2->SetValue(p_oPop->GetFloatDataCode("Light",
        p_oTargetTree2->GetSpecies(),
        p_oTargetTree2->GetType()),
        fShade);

    fDiam = 30;
    iSpecies = 0;
    fShade = 0.4;
    p_oTargetTree3 = p_oPop->CreateTree(50, 59, iSpecies, clTreePopulation::adult, fDiam);
    p_oTargetTree3->SetValue(p_oPop->GetFloatDataCode("Light",
        p_oTargetTree3->GetSpecies(),
        p_oTargetTree3->GetType()),
        fShade);

    fDiam = 45;
    iSpecies = 1;
    p_oTargetTree4 = p_oPop->CreateTree(55, 55, iSpecies, clTreePopulation::adult, fDiam);

    fDiam = 10.5;
    iSpecies = 0;
    fShade = 0;
    p_oTargetTree5 = p_oPop->CreateTree(50, 50, iSpecies, clTreePopulation::adult, fDiam);
    p_oTargetTree5->SetValue(p_oPop->GetFloatDataCode("Light",
        p_oTargetTree5->GetSpecies(),
        p_oTargetTree5->GetType()),
        fShade);

    //Now create all the neighbors that are too small or dead to compete
    p_oPop->CreateTree(52, 52, 0, clTreePopulation::sapling, 9);
    p_oPop->CreateTree(53, 53, 1, clTreePopulation::adult, 11);
    p_oPop->CreateTree(54, 54, 3, clTreePopulation::adult, 13);
    p_oPop->CreateTree(56, 56, 2, clTreePopulation::adult, 15);
    p_oPop->CreateTree(56, 56, 0, clTreePopulation::snag, 30);
    p_oTargetTree = p_oPop->CreateTree(58, 58, 1, clTreePopulation::adult, 20);
    p_oTargetTree->SetValue(p_oPop->GetIntDataCode("dead", p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), storm);

    //Now do the run - but don't let SailLight go, or it will mess up the
    //shading values we've assigned
    for (int i = 0; i < p_oSimManager->GetNumberOfBehaviors(); i++) {
      if (p_oSimManager->GetBehaviorObject(i)->GetName().compare("ncigrowthshell") == 0) {
        p_oSimManager->GetBehaviorObject(i)->Action();
        break;
      }
    }

    //Check the diameters and growth of the target trees
    fExpectedDiam = 16.23011367;
    fExpectedGrowth = 6.150568371;
    p_oTargetTree = p_oTargetTree1;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fDiam);
    p_oTargetTree->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fGrowth);
    EXPECT_LT(fabs(fDiam - fExpectedDiam), 0.01);
    EXPECT_LT(fabs(fGrowth - fExpectedGrowth), 0.01);

    fExpectedDiam = 27.30600165;
    fExpectedGrowth = 11.53000827;
    p_oTargetTree = p_oTargetTree2;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fDiam);
    p_oTargetTree->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fGrowth);
    EXPECT_LT(fabs(fDiam - fExpectedDiam), 0.01);
    EXPECT_LT(fabs(fGrowth - fExpectedGrowth), 0.01);

    fExpectedDiam = 31.01554876;
    fExpectedGrowth = 5.077743794;
    p_oTargetTree = p_oTargetTree3;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fDiam);
    p_oTargetTree->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fGrowth);
    EXPECT_LT(fabs(fDiam - fExpectedDiam), 0.01);
    EXPECT_LT(fabs(fGrowth - fExpectedGrowth), 0.01);

    fExpectedDiam = 46.84308914;
    fExpectedGrowth = 9.215445676;
    p_oTargetTree = p_oTargetTree4;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fDiam);
    p_oTargetTree->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fGrowth);
    EXPECT_LT(fabs(fDiam - fExpectedDiam), 0.01);
    EXPECT_LT(fabs(fGrowth - fExpectedGrowth), 0.01);

    fExpectedDiam = 11.53806956;
    fExpectedGrowth = 5.190347813;
    p_oTargetTree = p_oTargetTree5;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fDiam);
    p_oTargetTree->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fGrowth);
    EXPECT_LT(fabs(fDiam - fExpectedDiam), 0.01);
    EXPECT_LT(fabs(fGrowth - fExpectedGrowth), 0.01);

    //***********************************
    // Run 2 - 3 year timestep
    //***********************************
    //Load our test file and get our tree population pointers
    p_oSimManager->ReadFile( WriteNCIGrowthXMLFile9() );
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );

    //Create our trees and set their light levels
    fDiam = 15;
    iSpecies = 1;
    p_oTargetTree1 = p_oPop->CreateTree(53, 52, iSpecies, clTreePopulation::adult, fDiam);


    fDiam = 25;
    iSpecies = 3;
    fShade = 0.2;
    p_oTargetTree2 = p_oPop->CreateTree(59, 50, iSpecies, clTreePopulation::adult, fDiam);
    p_oTargetTree2->SetValue(p_oPop->GetFloatDataCode("Light",
        p_oTargetTree2->GetSpecies(),
        p_oTargetTree2->GetType()),
        fShade);

    fDiam = 30;
    iSpecies = 0;
    fShade = 0.4;
    p_oTargetTree3 = p_oPop->CreateTree(50, 59, iSpecies, clTreePopulation::adult, fDiam);
    p_oTargetTree3->SetValue(p_oPop->GetFloatDataCode("Light",
        p_oTargetTree3->GetSpecies(),
        p_oTargetTree3->GetType()),
        fShade);

    fDiam = 45;
    iSpecies = 1;
    p_oTargetTree4 = p_oPop->CreateTree(55, 55, iSpecies, clTreePopulation::adult, fDiam);

    fDiam = 10.5;
    iSpecies = 0;
    fShade = 0;
    p_oTargetTree5 = p_oPop->CreateTree(50, 50, iSpecies, clTreePopulation::adult, fDiam);
    p_oTargetTree5->SetValue(p_oPop->GetFloatDataCode("Light",
        p_oTargetTree5->GetSpecies(),
        p_oTargetTree5->GetType()),
        fShade);

    //Now create all the neighbors that are too small to compete
    p_oPop->CreateTree(52, 52, 0, clTreePopulation::sapling, 9);
    p_oPop->CreateTree(53, 53, 1, clTreePopulation::adult, 11);
    p_oPop->CreateTree(54, 54, 3, clTreePopulation::adult, 13);
    p_oPop->CreateTree(56, 56, 2, clTreePopulation::adult, 15);
    p_oTargetTree = p_oPop->CreateTree(58, 58, 1, clTreePopulation::adult, 20);
    p_oTargetTree->SetValue(p_oPop->GetIntDataCode("dead", p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), storm);

    //Now do the run - but don't let SailLight go, or it will mess up the
    //shading values we've assigned
    for (int i = 0; i < p_oSimManager->GetNumberOfBehaviors(); i++) {
      if (p_oSimManager->GetBehaviorObject(i)->GetName().compare("ncigrowthshell") == 0) {
        p_oSimManager->GetBehaviorObject(i)->Action();
        break;
      }
    }

    //Check the diameters and growth of the target trees
    fExpectedDiam = 18.8233003;
    fExpectedGrowth = 6.372167173;
    p_oTargetTree = p_oTargetTree1;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fDiam);
    p_oTargetTree->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fGrowth);
    EXPECT_LT(fabs(fDiam - fExpectedDiam), 0.01);
    EXPECT_LT(fabs(fGrowth - fExpectedGrowth), 0.01);

    fExpectedDiam = 31.82738854;
    fExpectedGrowth = 11.37898089;
    p_oTargetTree = p_oTargetTree2;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fDiam);
    p_oTargetTree->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fGrowth);
    EXPECT_LT(fabs(fDiam - fExpectedDiam), 0.01);
    EXPECT_LT(fabs(fGrowth - fExpectedGrowth), 0.01);

    fExpectedDiam = 33.04706798;
    fExpectedGrowth = 5.078446636;
    p_oTargetTree = p_oTargetTree3;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fDiam);
    p_oTargetTree->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fGrowth);
    EXPECT_LT(fabs(fDiam - fExpectedDiam), 0.01);
    EXPECT_LT(fabs(fGrowth - fExpectedGrowth), 0.01);

    fExpectedDiam = 50.5837852;
    fExpectedGrowth = 9.306308666;
    p_oTargetTree = p_oTargetTree4;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fDiam);
    p_oTargetTree->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fGrowth);
    EXPECT_LT(fabs(fDiam - fExpectedDiam), 0.01);
    EXPECT_LT(fabs(fGrowth - fExpectedGrowth), 0.01);

    fExpectedDiam = 13.62688973;
    fExpectedGrowth = 5.211482877;
    p_oTargetTree = p_oTargetTree5;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fDiam);
    p_oTargetTree->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fGrowth);
    EXPECT_LT(fabs(fDiam - fExpectedDiam), 0.01);
    EXPECT_LT(fabs(fGrowth - fExpectedGrowth), 0.01);
    delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

////////////////////////////////////////////////////////////////////////////
// TestRun5()
// Performs a test run of NCI growth - a Puerto-Rico-like situation. This
// run has no shading effect and uses damage effect. The damage applier is
// not applied to all species.
// WriteNCIGrowthXMLFile10() performs setup for a 1-year timestep; then WriteNCIGrowthXMLFile11()
// performs setup for an otherwise identical 3-year timestep.
////////////////////////////////////////////////////////////////////////////
TEST(NCIMasterGrowth, TestRun5) {
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
    *p_oTargetTree;
    float fDiam, fExpectedDiam;
    int iSpecies, iDamage;

    //***********************************
    // Run 1 - 1 year timestep
    //***********************************
    //Load our test file and get our tree population pointers
    p_oSimManager->ReadFile( WriteNCIGrowthXMLFile10() );
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );

    //Create our trees and set the damage level for each
    fDiam = 11;
    iSpecies = 0;
    iDamage = 0;
    p_oTargetTree1 = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, fDiam);
    p_oTargetTree1->SetValue(p_oPop->GetIntDataCode("stm_dmg",
        p_oTargetTree1->GetSpecies(),
        p_oTargetTree1->GetType()),
        iDamage);

    fDiam = 8;
    iSpecies = 1;
    p_oTargetTree2 = p_oPop->CreateTree(20, 20, iSpecies, clTreePopulation::sapling, fDiam);

    fDiam = 15;
    iSpecies = 3;
    iDamage = 2000;
    p_oTargetTree3 = p_oPop->CreateTree(30, 30, iSpecies, clTreePopulation::adult, fDiam);
    p_oTargetTree3->SetValue(p_oPop->GetIntDataCode("stm_dmg",
        p_oTargetTree3->GetSpecies(),
        p_oTargetTree3->GetType()),
        iDamage);

    fDiam = 10.5;
    iSpecies = 0;
    iDamage = 0;
    p_oTargetTree4 = p_oPop->CreateTree(50, 50, iSpecies, clTreePopulation::adult, fDiam);
    p_oTargetTree4->SetValue(p_oPop->GetIntDataCode("stm_dmg",
        p_oTargetTree4->GetSpecies(),
        p_oTargetTree4->GetType()),
        iDamage);

    fDiam = 15;
    iSpecies = 1;
    p_oTargetTree5 = p_oPop->CreateTree(53, 52, iSpecies, clTreePopulation::adult, fDiam);

    fDiam = 25;
    iSpecies = 3;
    iDamage = 2000;
    p_oTargetTree6 = p_oPop->CreateTree(59, 50, iSpecies, clTreePopulation::adult, fDiam);
    p_oTargetTree6->SetValue(p_oPop->GetIntDataCode("stm_dmg",
        p_oTargetTree6->GetSpecies(),
        p_oTargetTree6->GetType()),
        iDamage);

    fDiam = 30;
    iSpecies = 0;
    iDamage = 2000;
    p_oTargetTree7 = p_oPop->CreateTree(50, 59, iSpecies, clTreePopulation::adult, fDiam);
    p_oTargetTree7->SetValue(p_oPop->GetIntDataCode("stm_dmg",
        p_oTargetTree7->GetSpecies(),
        p_oTargetTree7->GetType()),
        iDamage);

    fDiam = 45;
    iSpecies = 1;
    p_oTargetTree8 = p_oPop->CreateTree(55, 55, iSpecies, clTreePopulation::adult, fDiam);

    //Competing neighbor snag
    fDiam = 11;
    iSpecies = 0;
    iDamage = 2000;
    p_oTargetTree = p_oPop->CreateTree(57, 57, iSpecies, clTreePopulation::snag, fDiam);
    p_oTargetTree->SetValue(p_oPop->GetIntDataCode("stm_dmg",
        p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()),
        iDamage);


    //Now create all the neighbors that are too small to compete
    p_oPop->CreateTree(56, 56, 0, clTreePopulation::seedling, 0.2);
    p_oPop->CreateTree(52, 52, 0, clTreePopulation::sapling, 4);
    p_oPop->CreateTree(53, 53, 1, clTreePopulation::sapling, 4);
    p_oPop->CreateTree(54, 54, 2, clTreePopulation::sapling, 4);
    p_oPop->CreateTree(57, 57, 3, clTreePopulation::sapling, 4);
    p_oTargetTree = p_oPop->CreateTree(58, 58, 1, clTreePopulation::adult, 20);
    p_oTargetTree->SetValue(p_oPop->GetIntDataCode("dead", p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), storm);

    //Now do the run
    p_oSimManager->RunSim(1);

    //Check the diameters and growth of the target trees
    fExpectedDiam = 12.02578252;
    p_oTargetTree = p_oTargetTree1;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam), 0.01);

    fExpectedDiam = 8.62904031;
    p_oTargetTree = p_oTargetTree2;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam), 0.01);

    fExpectedDiam = 15.62491548;
    p_oTargetTree = p_oTargetTree3;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam), 0.01);

    fExpectedDiam = 11.2924611;
    p_oTargetTree = p_oTargetTree4;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam), 0.01);

    fExpectedDiam = 15.8671366;
    p_oTargetTree = p_oTargetTree5;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam), 0.01);

    fExpectedDiam = 25.52597706;
    p_oTargetTree = p_oTargetTree6;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam), 0.01);

    fExpectedDiam = 30.37533594;
    p_oTargetTree = p_oTargetTree7;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam), 0.01);

    fExpectedDiam = 46.2453247;
    p_oTargetTree = p_oTargetTree8;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam), 0.01);

    //***********************************
    // Run 2 - 3 year timestep
    //***********************************
    //Load our test file and get our tree population pointers
    p_oSimManager->ReadFile( WriteNCIGrowthXMLFile11() );
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );

    //Create our trees and set the damage level for each
    fDiam = 11;
    iSpecies = 0;
    iDamage = 0;
    p_oTargetTree1 = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, fDiam);
    p_oTargetTree1->SetValue(p_oPop->GetIntDataCode("stm_dmg",
        p_oTargetTree1->GetSpecies(),
        p_oTargetTree1->GetType()),
        iDamage);

    fDiam = 8;
    iSpecies = 1;
    p_oTargetTree2 = p_oPop->CreateTree(20, 20, iSpecies, clTreePopulation::sapling, fDiam);

    fDiam = 15;
    iSpecies = 3;
    iDamage = 2000;
    p_oTargetTree3 = p_oPop->CreateTree(30, 30, iSpecies, clTreePopulation::adult, fDiam);
    p_oTargetTree3->SetValue(p_oPop->GetIntDataCode("stm_dmg",
        p_oTargetTree3->GetSpecies(),
        p_oTargetTree3->GetType()),
        iDamage);

    fDiam = 10.5;
    iSpecies = 0;
    iDamage = 0;
    p_oTargetTree4 = p_oPop->CreateTree(50, 50, iSpecies, clTreePopulation::adult, fDiam);
    p_oTargetTree4->SetValue(p_oPop->GetIntDataCode("stm_dmg",
        p_oTargetTree4->GetSpecies(),
        p_oTargetTree4->GetType()),
        iDamage);

    fDiam = 15;
    iSpecies = 1;
    p_oTargetTree5 = p_oPop->CreateTree(53, 52, iSpecies, clTreePopulation::adult, fDiam);

    fDiam = 25;
    iSpecies = 3;
    iDamage = 2000;
    p_oTargetTree6 = p_oPop->CreateTree(59, 50, iSpecies, clTreePopulation::adult, fDiam);
    p_oTargetTree6->SetValue(p_oPop->GetIntDataCode("stm_dmg",
        p_oTargetTree6->GetSpecies(),
        p_oTargetTree6->GetType()),
        iDamage);

    fDiam = 30;
    iSpecies = 0;
    iDamage = 2000;
    p_oTargetTree7 = p_oPop->CreateTree(50, 59, iSpecies, clTreePopulation::adult, fDiam);
    p_oTargetTree7->SetValue(p_oPop->GetIntDataCode("stm_dmg",
        p_oTargetTree7->GetSpecies(),
        p_oTargetTree7->GetType()),
        iDamage);

    fDiam = 45;
    iSpecies = 1;
    p_oTargetTree8 = p_oPop->CreateTree(55, 55, iSpecies, clTreePopulation::adult, fDiam);

    //Competing neighbor snag
    fDiam = 11;
    iSpecies = 0;
    iDamage = 2000;
    p_oTargetTree = p_oPop->CreateTree(57, 57, iSpecies, clTreePopulation::snag, fDiam);
    p_oTargetTree->SetValue(p_oPop->GetIntDataCode("stm_dmg",
        p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()),
        iDamage);

    //Now create all the neighbors that are too small to compete
    p_oPop->CreateTree(56, 56, 0, clTreePopulation::seedling, 0.2);
    p_oPop->CreateTree(52, 52, 0, clTreePopulation::sapling, 4);
    p_oPop->CreateTree(53, 53, 1, clTreePopulation::sapling, 4);
    p_oPop->CreateTree(54, 54, 2, clTreePopulation::sapling, 4);
    p_oPop->CreateTree(57, 57, 3, clTreePopulation::sapling, 4);
    p_oTargetTree = p_oPop->CreateTree(58, 58, 1, clTreePopulation::adult, 20);
    p_oTargetTree->SetValue(p_oPop->GetIntDataCode("dead", p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), storm);

    //Now do the run
    p_oSimManager->RunSim(1);

    //Check the diameters and growth of the target trees
    fExpectedDiam = 14.08875462;
    p_oTargetTree = p_oTargetTree1;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam), 0.01);

    fExpectedDiam = 9.956648552;
    p_oTargetTree = p_oTargetTree2;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam), 0.01);

    fExpectedDiam = 16.8769391;
    p_oTargetTree = p_oTargetTree3;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam), 0.01);

    fExpectedDiam = 12.90647995;
    p_oTargetTree = p_oTargetTree4;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam), 0.01);

    fExpectedDiam = 17.6666058;
    p_oTargetTree = p_oTargetTree5;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam), 0.01);

    fExpectedDiam = 26.57320243;
    p_oTargetTree = p_oTargetTree6;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam), 0.01);

    fExpectedDiam = 31.12798751;
    p_oTargetTree = p_oTargetTree7;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam), 0.01);

    fExpectedDiam = 48.75973525;
    p_oTargetTree = p_oTargetTree8;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam), 0.01);
    delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

////////////////////////////////////////////////////////////////////////////
// TestRun6()
// Performs a test run of NCI growth with no crowding effect (also no
// shading or damage - size effect only).
// WriteNCIGrowthXMLFile12() performs setup for a 1-year timestep; then
// WriteNCIGrowthXMLFile13() performs setup for an otherwise identical 3-year timestep.
////////////////////////////////////////////////////////////////////////////
TEST(NCIMasterGrowth, TestRun6) {
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
    *p_oTargetTree;
    float fDiam, fExpectedDiam;
    int iSpecies;

    //***********************************
    // Run 1 - 1 year timestep
    //***********************************
    //Load our test file and get our tree population pointers
    p_oSimManager->ReadFile( WriteNCIGrowthXMLFile12() );
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );

    //Create our trees
    fDiam = 11;
    iSpecies = 0;
    p_oTargetTree1 = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, fDiam);

    fDiam = 8;
    iSpecies = 1;
    p_oTargetTree2 = p_oPop->CreateTree(20, 20, iSpecies, clTreePopulation::sapling, fDiam);

    fDiam = 15;
    iSpecies = 3;
    p_oTargetTree3 = p_oPop->CreateTree(30, 30, iSpecies, clTreePopulation::adult, fDiam);

    fDiam = 10.5;
    iSpecies = 0;
    p_oTargetTree4 = p_oPop->CreateTree(50, 50, iSpecies, clTreePopulation::adult, fDiam);

    fDiam = 15;
    iSpecies = 1;
    p_oTargetTree5 = p_oPop->CreateTree(53, 52, iSpecies, clTreePopulation::adult, fDiam);

    fDiam = 25;
    iSpecies = 3;
    p_oTargetTree6 = p_oPop->CreateTree(59, 50, iSpecies, clTreePopulation::adult, fDiam);

    fDiam = 30;
    iSpecies = 0;
    p_oTargetTree7 = p_oPop->CreateTree(50, 59, iSpecies, clTreePopulation::adult, fDiam);

    fDiam = 45;
    iSpecies = 1;
    p_oTargetTree8 = p_oPop->CreateTree(55, 55, iSpecies, clTreePopulation::adult, fDiam);

    //Neighbors
    fDiam = 11;
    iSpecies = 0;
    p_oTargetTree = p_oPop->CreateTree(57, 57, iSpecies, clTreePopulation::snag, fDiam);
    p_oPop->CreateTree(56, 56, 0, clTreePopulation::seedling, 0.2);
    p_oPop->CreateTree(52, 52, 0, clTreePopulation::sapling, 4);
    p_oPop->CreateTree(53, 53, 1, clTreePopulation::sapling, 4);
    p_oPop->CreateTree(54, 54, 2, clTreePopulation::sapling, 4);
    p_oPop->CreateTree(57, 57, 3, clTreePopulation::sapling, 4);
    p_oTargetTree = p_oPop->CreateTree(58, 58, 1, clTreePopulation::adult, 20);
    p_oTargetTree->SetValue(p_oPop->GetIntDataCode("dead", p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), storm);

    //Now do the run
    p_oSimManager->RunSim(1);

    //Check the diameters and growth of the target trees
    fExpectedDiam = 12.02578252;
    p_oTargetTree = p_oTargetTree1;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam), 0.01);

    fExpectedDiam = 8.62904031;
    p_oTargetTree = p_oTargetTree2;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam), 0.01);

    fExpectedDiam = 15.99192934;
    p_oTargetTree = p_oTargetTree3;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam), 0.01);

    fExpectedDiam = 11.52357274;
    p_oTargetTree = p_oTargetTree4;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam), 0.01);

    fExpectedDiam = 16.03131074;
    p_oTargetTree = p_oTargetTree5;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam), 0.01);

    fExpectedDiam = 25.9509129;
    p_oTargetTree = p_oTargetTree6;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam), 0.01);

    fExpectedDiam = 31.05221861;
    p_oTargetTree = p_oTargetTree7;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam), 0.01);

    fExpectedDiam = 46.39973664;
    p_oTargetTree = p_oTargetTree8;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam), 0.01);

    //***********************************
    // Run 2 - 3 year timestep
    //***********************************
    //Load our test file and get our tree population pointers
    p_oSimManager->ReadFile( WriteNCIGrowthXMLFile13() );
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );

    //Create our trees and set the damage level for each
    fDiam = 11;
    iSpecies = 0;
    p_oTargetTree1 = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, fDiam);

    fDiam = 8;
    iSpecies = 1;
    p_oTargetTree2 = p_oPop->CreateTree(20, 20, iSpecies, clTreePopulation::sapling, fDiam);

    fDiam = 15;
    iSpecies = 3;
    p_oTargetTree3 = p_oPop->CreateTree(30, 30, iSpecies, clTreePopulation::adult, fDiam);

    fDiam = 10.5;
    iSpecies = 0;
    p_oTargetTree4 = p_oPop->CreateTree(50, 50, iSpecies, clTreePopulation::adult, fDiam);

    fDiam = 15;
    iSpecies = 1;
    p_oTargetTree5 = p_oPop->CreateTree(53, 52, iSpecies, clTreePopulation::adult, fDiam);

    fDiam = 25;
    iSpecies = 3;
    p_oTargetTree6 = p_oPop->CreateTree(59, 50, iSpecies, clTreePopulation::adult, fDiam);

    fDiam = 30;
    iSpecies = 0;
    p_oTargetTree7 = p_oPop->CreateTree(50, 59, iSpecies, clTreePopulation::adult, fDiam);

    fDiam = 45;
    iSpecies = 1;
    p_oTargetTree8 = p_oPop->CreateTree(55, 55, iSpecies, clTreePopulation::adult, fDiam);

    //Neighbors
    fDiam = 11;
    iSpecies = 0;
    p_oTargetTree = p_oPop->CreateTree(57, 57, iSpecies, clTreePopulation::snag, fDiam);
    p_oPop->CreateTree(56, 56, 0, clTreePopulation::seedling, 0.2);
    p_oPop->CreateTree(52, 52, 0, clTreePopulation::sapling, 4);
    p_oPop->CreateTree(53, 53, 1, clTreePopulation::sapling, 4);
    p_oPop->CreateTree(54, 54, 2, clTreePopulation::sapling, 4);
    p_oPop->CreateTree(57, 57, 3, clTreePopulation::sapling, 4);
    p_oTargetTree = p_oPop->CreateTree(58, 58, 1, clTreePopulation::adult, 20);
    p_oTargetTree->SetValue(p_oPop->GetIntDataCode("dead", p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), storm);

    //Now do the run
    p_oSimManager->RunSim(1);

    //Check the diameters and growth of the target trees
    fExpectedDiam = 14.0887546;
    p_oTargetTree = p_oTargetTree1;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam), 0.01);

    fExpectedDiam = 9.95664855;
    p_oTargetTree = p_oTargetTree2;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam), 0.01);

    fExpectedDiam = 17.97947018;
    p_oTargetTree = p_oTargetTree3;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam), 0.01);

    fExpectedDiam = 13.58307004;
    p_oTargetTree = p_oTargetTree4;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam), 0.01);

    fExpectedDiam = 18.1699152;
    p_oTargetTree = p_oTargetTree5;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam), 0.01);

    fExpectedDiam = 27.82913748;
    p_oTargetTree = p_oTargetTree6;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam), 0.01);

    fExpectedDiam = 33.15710399;
    p_oTargetTree = p_oTargetTree7;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam), 0.01);

    fExpectedDiam = 49.22161854;
    p_oTargetTree = p_oTargetTree8;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam), 0.01);
    delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

////////////////////////////////////////////////////////////////////////////
// WriteNCIGrowthXMLFile1()
////////////////////////////////////////////////////////////////////////////
const char* WriteNCIGrowthXMLFile1() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  WriteNCIGrowthErrorFileCommonStuff(oOut);

  //Write file
  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>ConstantGLI</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\" />"
       << "<applyTo species=\"Species_2\" type=\"Adult\" />"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>NCIMasterGrowth</behaviorName>"
       << "<version>3</version>"
       << "<listPosition>2</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\" />"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>NCIMasterGrowth diam only</behaviorName>"
       << "<version>3</version>"
       << "<listPosition>3</listPosition>"
       << "<applyTo species=\"Species_2\" type=\"Adult\" />"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>HeightIncrementer</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>4</listPosition>"
       << "<applyTo species=\"Species_2\" type=\"Adult\" />"
       << "</behavior>"
       << "</behaviorList>"
       << "<ConstantGLI1>"
       << "<li_constGLI>100</li_constGLI>"
       << "</ConstantGLI1>"
       << "<NCIMasterGrowth2>"
       << "<nciWhichShadingEffect>" << no_shading << "</nciWhichShadingEffect>"
       << "<nciWhichCrowdingEffect>1</nciWhichCrowdingEffect>"
       << "<nciWhichNCITerm>1</nciWhichNCITerm>"
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
       << "<nciAlpha>"
       << "<naVal species=\"Species_1\">2.17031683</naVal>"
       << "<naVal species=\"Species_2\">2.17031683</naVal>"
       << "</nciAlpha>"
       << "<nciBeta>"
       << "<nbVal species=\"Species_1\">0.5</nbVal>"
       << "<nbVal species=\"Species_2\">0.5</nbVal>"
       << "</nciBeta>"
       << "<gr_nciMaxPotentialGrowth>"
       << "<gr_nmpgVal species=\"Species_1\">1.531</gr_nmpgVal>"
       << "<gr_nmpgVal species=\"Species_2\">1.531</gr_nmpgVal>"
       << "</gr_nciMaxPotentialGrowth>"
       << "<nciCrowdingGamma>"
       << "<ncgVal species=\"Species_1\">0.36</ncgVal>"
       << "<ncgVal species=\"Species_2\">0.36</ncgVal>"
       << "</nciCrowdingGamma>"
       << "<nciSizeEffectX0>"
       << "<nsex0Val species=\"Species_1\">122.23</nsex0Val>"
       << "<nsex0Val species=\"Species_2\">122.23</nsex0Val>"
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
       << "<nciShadingCoefficient>"
       << "<nscVal species=\"Species_1\">0</nscVal>"
       << "<nscVal species=\"Species_2\">0</nscVal>"
       << "</nciShadingCoefficient>"
       << "<nciShadingExponent>"
       << "<nseVal species=\"Species_1\">1</nseVal>"
       << "<nseVal species=\"Species_2\">1</nseVal>"
       << "</nciShadingExponent>"
       << "<nciStormEffMedDmg>"
       << "<nsemdVal species=\"Species_1\">1</nsemdVal>"
       << "<nsemdVal species=\"Species_2\">1</nsemdVal>"
       << "</nciStormEffMedDmg>"
       << "<nciStormEffFullDmg>"
       << "<nsefdVal species=\"Species_1\">1</nsefdVal>"
       << "<nsefdVal species=\"Species_2\">1</nsefdVal>"
       << "</nciStormEffFullDmg>"
       << "<nciNeighStormEffMedDmg>"
       << "<nnsemdVal species=\"Species_1\">1</nnsemdVal>"
       << "<nnsemdVal species=\"Species_2\">1</nnsemdVal>"
       << "</nciNeighStormEffMedDmg>"
       << "<nciNeighStormEffFullDmg>"
       << "<nnsefdVal species=\"Species_1\">1</nnsefdVal>"
       << "<nnsefdVal species=\"Species_2\">1</nnsefdVal>"
       << "</nciNeighStormEffFullDmg>"
       << "<nciSpecies_1NeighborLambda>"
       << "<nlVal species=\"Species_1\">0.71</nlVal>"
       << "<nlVal species=\"Species_2\">0.71</nlVal>"
       << "</nciSpecies_1NeighborLambda>"
       << "<nciSpecies_2NeighborLambda>"
       << "<nlVal species=\"Species_1\">0.12</nlVal>"
       << "<nlVal species=\"Species_2\">0.12</nlVal>"
       << "</nciSpecies_2NeighborLambda>"
       << "<nciMinNeighborDBH>"
       << "<nmndVal species=\"Species_1\">0</nmndVal>"
       << "<nmndVal species=\"Species_2\">0</nmndVal>"
       << "</nciMinNeighborDBH>"
       << "<nciDbhDivisor>100</nciDbhDivisor>"
       << "<nciIncludeSnagsInNCI>0</nciIncludeSnagsInNCI>"
       << "</NCIMasterGrowth2>"
       << "<NCIMasterGrowth3>"
       << "<nciWhichShadingEffect>" << no_shading << "</nciWhichShadingEffect>"
       << "<nciWhichCrowdingEffect>1</nciWhichCrowdingEffect>"
       << "<nciWhichNCITerm>1</nciWhichNCITerm>"
       << "<nciWhichSizeEffect>1</nciWhichSizeEffect>"
       << "<nciWhichDamageEffect>0</nciWhichDamageEffect>"
       << "<nciWhichPrecipitationEffect>" << no_precip_effect << "</nciWhichPrecipitationEffect>"
       << "<nciWhichTemperatureEffect>" << no_temp_effect << "</nciWhichTemperatureEffect>"
       << "<nciWhichNitrogenEffect>" << no_nitrogen_effect << "</nciWhichNitrogenEffect>"
       << "<nciWhichInfectionEffect>" << no_infection_effect << "</nciWhichInfectionEffect>"
       << "<gr_stochGrowthMethod>" << deterministic_pdf << "</gr_stochGrowthMethod>"
       << "<nciMaxCrowdingRadius>"
       << "<nmcrVal species=\"Species_1\">10</nmcrVal>"
       << "<nmcrVal species=\"Species_2\">10</nmcrVal>"
       << "</nciMaxCrowdingRadius>"
       << "<nciAlpha>"
       << "<naVal species=\"Species_1\">2.17031683</naVal>"
       << "<naVal species=\"Species_2\">2.17031683</naVal>"
       << "</nciAlpha>"
       << "<nciBeta>"
       << "<nbVal species=\"Species_1\">0.5</nbVal>"
       << "<nbVal species=\"Species_2\">0.5</nbVal>"
       << "</nciBeta>"
       << "<gr_nciMaxPotentialGrowth>"
       << "<gr_nmpgVal species=\"Species_1\">1.531</gr_nmpgVal>"
       << "<gr_nmpgVal species=\"Species_2\">1.531</gr_nmpgVal>"
       << "</gr_nciMaxPotentialGrowth>"
       << "<nciCrowdingGamma>"
       << "<ncgVal species=\"Species_1\">0.36</ncgVal>"
       << "<ncgVal species=\"Species_2\">0.36</ncgVal>"
       << "</nciCrowdingGamma>"
       << "<nciSizeEffectX0>"
       << "<nsex0Val species=\"Species_1\">122.23</nsex0Val>"
       << "<nsex0Val species=\"Species_2\">122.23</nsex0Val>"
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
       << "<nciShadingCoefficient>"
       << "<nscVal species=\"Species_1\">0</nscVal>"
       << "<nscVal species=\"Species_2\">0</nscVal>"
       << "</nciShadingCoefficient>"
       << "<nciShadingExponent>"
       << "<nseVal species=\"Species_1\">1</nseVal>"
       << "<nseVal species=\"Species_2\">1</nseVal>"
       << "</nciShadingExponent>"
       << "<nciStormEffMedDmg>"
       << "<nsemdVal species=\"Species_1\">1</nsemdVal>"
       << "<nsemdVal species=\"Species_2\">1</nsemdVal>"
       << "</nciStormEffMedDmg>"
       << "<nciStormEffFullDmg>"
       << "<nsefdVal species=\"Species_1\">1</nsefdVal>"
       << "<nsefdVal species=\"Species_2\">1</nsefdVal>"
       << "</nciStormEffFullDmg>"
       << "<nciNeighStormEffMedDmg>"
       << "<nnsemdVal species=\"Species_1\">1</nnsemdVal>"
       << "<nnsemdVal species=\"Species_2\">1</nnsemdVal>"
       << "</nciNeighStormEffMedDmg>"
       << "<nciNeighStormEffFullDmg>"
       << "<nnsefdVal species=\"Species_1\">1</nnsefdVal>"
       << "<nnsefdVal species=\"Species_2\">1</nnsefdVal>"
       << "</nciNeighStormEffFullDmg>"
       << "<nciSpecies_1NeighborLambda>"
       << "<nlVal species=\"Species_1\">0.71</nlVal>"
       << "<nlVal species=\"Species_2\">0.71</nlVal>"
       << "</nciSpecies_1NeighborLambda>"
       << "<nciSpecies_2NeighborLambda>"
       << "<nlVal species=\"Species_1\">0.12</nlVal>"
       << "<nlVal species=\"Species_2\">0.12</nlVal>"
       << "</nciSpecies_2NeighborLambda>"
       << "<nciMinNeighborDBH>"
       << "<nmndVal species=\"Species_1\">0</nmndVal>"
       << "<nmndVal species=\"Species_2\">0</nmndVal>"
       << "</nciMinNeighborDBH>"
       << "<nciDbhDivisor>100</nciDbhDivisor>"
       << "<nciIncludeSnagsInNCI>0</nciIncludeSnagsInNCI>"
       << "</NCIMasterGrowth3>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteNCIGrowthXMLFile2()
////////////////////////////////////////////////////////////////////////////
const char* WriteNCIGrowthXMLFile2() {
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
  WriteNCIGrowthCommonStuff(oOut);
  WriteNCIGrowthRun2CommonStuff(oOut);

  oOut.close();

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteNCIGrowthXMLFile3()
////////////////////////////////////////////////////////////////////////////
const char* WriteNCIGrowthXMLFile3() {
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
  WriteNCIGrowthCommonStuff(oOut);
  WriteNCIGrowthRun2CommonStuff(oOut);

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteNCIGrowthCommonStuff()
/////////////////////////////////////////////////////////////////////////////
void WriteNCIGrowthCommonStuff( std::fstream &oOut )
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

////////////////////////////////////////////////////////////////////////////
// WriteNCIGrowthXMLFile4()
////////////////////////////////////////////////////////////////////////////
const char* WriteNCIGrowthXMLFile4() {
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

  WriteNCIGrowthCommonStuff(oOut);
  WriteNCIGrowthRun1CommonStuff(oOut);

  oOut.close();

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteNCIGrowthXMLFile5()
////////////////////////////////////////////////////////////////////////////
const char* WriteNCIGrowthXMLFile5() {
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

  WriteNCIGrowthCommonStuff(oOut);
  WriteNCIGrowthRun1CommonStuff(oOut);

  oOut.close();

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteNCIGrowthXMLFile6()
////////////////////////////////////////////////////////////////////////////
const char* WriteNCIGrowthXMLFile6() {
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

  WriteNCIGrowthCommonStuff(oOut);
  WriteNCIGrowthRun3CommonStuff(oOut);

  oOut.close();

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteNCIGrowthXMLFile7()
////////////////////////////////////////////////////////////////////////////
const char* WriteNCIGrowthXMLFile7() {
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

  WriteNCIGrowthCommonStuff(oOut);
  WriteNCIGrowthRun3CommonStuff(oOut);

  oOut.close();

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteNCIGrowthXMLFile8()
////////////////////////////////////////////////////////////////////////////
const char* WriteNCIGrowthXMLFile8() {
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

  WriteNCIGrowthCommonStuff(oOut);
  WriteNCIGrowthRun4CommonStuff(oOut);

  oOut.close();

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteNCIGrowthXMLFile9()
////////////////////////////////////////////////////////////////////////////
const char* WriteNCIGrowthXMLFile9() {
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

  WriteNCIGrowthCommonStuff(oOut);
  WriteNCIGrowthRun4CommonStuff(oOut);

  oOut.close();

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteNCIGrowthXMLFile10()
////////////////////////////////////////////////////////////////////////////
const char* WriteNCIGrowthXMLFile10() {
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

  WriteNCIGrowthCommonStuff(oOut);
  WriteNCIGrowthRun5CommonStuff(oOut);

  oOut.close();

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteNCIGrowthXMLFile11()
////////////////////////////////////////////////////////////////////////////
const char* WriteNCIGrowthXMLFile11() {
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

  WriteNCIGrowthCommonStuff(oOut);
  WriteNCIGrowthRun5CommonStuff(oOut);

  oOut.close();

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteNCIGrowthXMLFile12()
////////////////////////////////////////////////////////////////////////////
const char* WriteNCIGrowthXMLFile12() {
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

  WriteNCIGrowthCommonStuff(oOut);
  WriteNCIGrowthRun6CommonStuff(oOut);

  oOut.close();

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteNCIGrowthXMLFile13()
////////////////////////////////////////////////////////////////////////////
const char* WriteNCIGrowthXMLFile13() {
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

  WriteNCIGrowthCommonStuff(oOut);
  WriteNCIGrowthRun6CommonStuff(oOut);

  oOut.close();

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteNCIGrowthRun1CommonStuff()
////////////////////////////////////////////////////////////////////////////
void WriteNCIGrowthRun1CommonStuff( std::fstream &oOut ) {

  using namespace std;
  //Write file
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
       << "<behaviorName>NCIMasterGrowth</behaviorName>"
       << "<version>3</version>"
       << "<listPosition>3</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_4\" type=\"Adult\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>ConstRadialGrowth</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>4</listPosition>"
       << "<applyTo species=\"Species_4\" type=\"Sapling\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>StochasticMortality</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>5</listPosition>"
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
       << "<Storm1>"
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
       << "</StormDamageApplier2>"
       << "<ConstRadialGrowth4>"
       << "<gr_adultConstRadialInc>"
       << "<gr_acriVal species=\"Species_4\">10</gr_acriVal>"
       << "</gr_adultConstRadialInc>"
       << "</ConstRadialGrowth4>"
       << "<NCIMasterGrowth3>"
       << "<nciWhichShadingEffect>" << no_shading << "</nciWhichShadingEffect>"
       << "<nciWhichCrowdingEffect>1</nciWhichCrowdingEffect>"
       << "<nciWhichNCITerm>2</nciWhichNCITerm>"
       << "<nciWhichSizeEffect>1</nciWhichSizeEffect>"
       << "<nciWhichDamageEffect>1</nciWhichDamageEffect>"
       << "<nciWhichPrecipitationEffect>" << no_precip_effect << "</nciWhichPrecipitationEffect>"
       << "<nciWhichTemperatureEffect>" << no_temp_effect << "</nciWhichTemperatureEffect>"
       << "<nciWhichNitrogenEffect>" << no_nitrogen_effect << "</nciWhichNitrogenEffect>"
       << "<nciWhichInfectionEffect>" << no_infection_effect << "</nciWhichInfectionEffect>"
       << "<gr_stochGrowthMethod>" << deterministic_pdf << "</gr_stochGrowthMethod>"
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
       << "<gr_nciMaxPotentialGrowth>"
       << "<gr_nmpgVal species=\"Species_1\">1.05258749</gr_nmpgVal>"
       << "<gr_nmpgVal species=\"Species_2\">1.531</gr_nmpgVal>"
       << "<gr_nmpgVal species=\"Species_4\">0.994</gr_nmpgVal>"
       << "</gr_nciMaxPotentialGrowth>"
       << "<nciCrowdingGamma>"
       << "<ncgVal species=\"Species_1\">-0.43</ncgVal>"
       << "<ncgVal species=\"Species_2\">-0.36</ncgVal>"
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
       << "<nccVal species=\"Species_1\">0.698</nccVal>"
       << "<nccVal species=\"Species_2\">0.457</nccVal>"
       << "<nccVal species=\"Species_4\">0.469</nccVal>"
       << "</nciCrowdingC>"
       << "<nciCrowdingD>"
       << "<ncdVal species=\"Species_1\">-0.00163</ncdVal>"
       << "<ncdVal species=\"Species_2\">-0.00126</ncdVal>"
       << "<ncdVal species=\"Species_4\">-0.00163</ncdVal>"
       << "</nciCrowdingD>"
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
       << "<nciMinNeighborDBH>"
       << "<nmndVal species=\"Species_1\">5</nmndVal>"
       << "<nmndVal species=\"Species_2\">5</nmndVal>"
       << "<nmndVal species=\"Species_3\">5</nmndVal>"
       << "<nmndVal species=\"Species_4\">5</nmndVal>"
       << "</nciMinNeighborDBH>"
       << "<nciDbhDivisor>100</nciDbhDivisor>"
       << "<nciIncludeSnagsInNCI>0</nciIncludeSnagsInNCI>"
       << "</NCIMasterGrowth3>"
       << "<StochasticMortality5>"
       << "<mo_stochasticMortRate>"
       << "<mo_smrVal species=\"Species_3\">0</mo_smrVal>"
       << "<mo_smrVal species=\"Species_1\">0</mo_smrVal>"
       << "<mo_smrVal species=\"Species_2\">0</mo_smrVal>"
       << "<mo_smrVal species=\"Species_4\">0</mo_smrVal>"
       << "</mo_stochasticMortRate>"
       << "</StochasticMortality5>"
       << "</paramFile>";
}

////////////////////////////////////////////////////////////////////////////
// WriteNCIGrowthRun2CommonStuff()
////////////////////////////////////////////////////////////////////////////
void WriteNCIGrowthRun2CommonStuff( std::fstream &oOut ) {
  using namespace std;

  //Write file
  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>SailLight</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>NCIMasterGrowth</behaviorName>"
       << "<version>3</version>"
       << "<listPosition>2</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\" />"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>StochasticMortality</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>3</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_4\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_4\" type=\"Sapling\"/>"
       << "</behavior>"
       << "</behaviorList>"
       << "<SailLight1>"
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
       << "</SailLight1>"
       << "<NCIMasterGrowth2>"
       << "<nciWhichShadingEffect>1</nciWhichShadingEffect>"
       << "<nciWhichCrowdingEffect>1</nciWhichCrowdingEffect>"
       << "<nciWhichNCITerm>1</nciWhichNCITerm>"
       << "<nciWhichSizeEffect>1</nciWhichSizeEffect>"
       << "<nciWhichDamageEffect>0</nciWhichDamageEffect>"
       << "<nciWhichPrecipitationEffect>" << no_precip_effect << "</nciWhichPrecipitationEffect>"
       << "<nciWhichTemperatureEffect>" << no_temp_effect << "</nciWhichTemperatureEffect>"
       << "<nciWhichNitrogenEffect>" << no_nitrogen_effect << "</nciWhichNitrogenEffect>"
       << "<nciWhichInfectionEffect>" << no_infection_effect << "</nciWhichInfectionEffect>"
       << "<gr_stochGrowthMethod>" << deterministic_pdf << "</gr_stochGrowthMethod>"
       << "<nciMaxCrowdingRadius>"
       << "<nmcrVal species=\"Species_1\">10</nmcrVal>"
       << "</nciMaxCrowdingRadius>"
       << "<nciAlpha>"
       << "<naVal species=\"Species_1\">2.170317</naVal>"
       << "</nciAlpha>"
       << "<nciBeta>"
       << "<nbVal species=\"Species_1\">0.699942</nbVal>"
       << "</nciBeta>"
       << "<gr_nciMaxPotentialGrowth>"
       << "<gr_nmpgVal species=\"Species_1\">1.052587488</gr_nmpgVal>"
       << "</gr_nciMaxPotentialGrowth>"
       << "<nciSizeEffectX0>"
       << "<nsex0Val species=\"Species_1\">34.24639</nsex0Val>"
       << "</nciSizeEffectX0>"
       << "<nciSizeEffectXb>"
       << "<nsexbVal species=\"Species_1\">5.0</nsexbVal>"
       << "</nciSizeEffectXb>"
       << "<nciShadingCoefficient>"
       << "<nscVal species=\"Species_1\">0.2</nscVal>"
       << "</nciShadingCoefficient>"
       << "<nciShadingExponent>"
       << "<nseVal species=\"Species_1\">0.5</nseVal>"
       << "</nciShadingExponent>"
       << "<nciCrowdingC>"
       << "<nccVal species=\"Species_1\">1.98</nccVal>"
       << "</nciCrowdingC>"
       << "<nciCrowdingD>"
       << "<ncdVal species=\"Species_1\">1</ncdVal>"
       << "</nciCrowdingD>"
       << "<nciCrowdingGamma>"
       << "<ncgVal species=\"Species_1\">0</ncgVal>"
       << "</nciCrowdingGamma>"
       << "<nciSpecies_1NeighborLambda>"
       << "<nlVal species=\"Species_1\">0.6640108</nlVal>"
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
       << "<nciMinNeighborDBH>"
       << "<nmndVal species=\"Species_1\">5</nmndVal>"
       << "<nmndVal species=\"Species_2\">5</nmndVal>"
       << "<nmndVal species=\"Species_3\">5</nmndVal>"
       << "<nmndVal species=\"Species_4\">5</nmndVal>"
       << "</nciMinNeighborDBH>"
       << "<nciDbhDivisor>100</nciDbhDivisor>"
       << "<nciIncludeSnagsInNCI>0</nciIncludeSnagsInNCI>"
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

////////////////////////////////////////////////////////////////////////////
// WriteNCIGrowthRun3CommonStuff()
////////////////////////////////////////////////////////////////////////////
void WriteNCIGrowthRun3CommonStuff( std::fstream &oOut ) {
  using namespace std;

  //Write file
  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>ConstantGLI</behaviorName>"
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
       << "<behaviorName>NCIMasterGrowth</behaviorName>"
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
       << "<behaviorName>StochasticMortality</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>3</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_4\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_4\" type=\"Sapling\"/>"
       << "</behavior>"
       << "</behaviorList>"
       << "<ConstantGLI1>"
       << "<li_constGLI>100</li_constGLI>"
       << "</ConstantGLI1>"
       << "<NCIMasterGrowth2>"
       << "<nciWhichShadingEffect>1</nciWhichShadingEffect>"
       << "<nciWhichCrowdingEffect>1</nciWhichCrowdingEffect>"
       << "<nciWhichNCITerm>1</nciWhichNCITerm>"
       << "<nciWhichSizeEffect>1</nciWhichSizeEffect>"
       << "<nciWhichDamageEffect>0</nciWhichDamageEffect>"
       << "<nciWhichPrecipitationEffect>" << no_precip_effect << "</nciWhichPrecipitationEffect>"
       << "<nciWhichTemperatureEffect>" << no_temp_effect << "</nciWhichTemperatureEffect>"
       << "<nciWhichNitrogenEffect>" << no_nitrogen_effect << "</nciWhichNitrogenEffect>"
       << "<nciWhichInfectionEffect>" << no_infection_effect << "</nciWhichInfectionEffect>"
       << "<gr_stochGrowthMethod>" << deterministic_pdf << "</gr_stochGrowthMethod>"
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
       << "<gr_nciMaxPotentialGrowth>"
       << "<gr_nmpgVal species=\"Species_1\">3.052587488</gr_nmpgVal>"
       << "<gr_nmpgVal species=\"Species_2\">3.531</gr_nmpgVal>"
       << "<gr_nmpgVal species=\"Species_4\">3.994</gr_nmpgVal>"
       << "</gr_nciMaxPotentialGrowth>"
       << "<nciCrowdingGamma>"
       << "<ncgVal species=\"Species_1\">0</ncgVal>"
       << "<ncgVal species=\"Species_2\">-0.13</ncgVal>"
       << "<ncgVal species=\"Species_4\">-0.23</ncgVal>"
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
       << "<nccVal species=\"Species_1\">0.98</nccVal>"
       << "<nccVal species=\"Species_2\">0.57</nccVal>"
       << "<nccVal species=\"Species_4\">0.069</nccVal>"
       << "</nciCrowdingC>"
       << "<nciCrowdingD>"
       << "<ncdVal species=\"Species_1\">0.012</ncdVal>"
       << "<ncdVal species=\"Species_2\">0.056</ncdVal>"
       << "<ncdVal species=\"Species_4\">1</ncdVal>"
       << "</nciCrowdingD>"
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
       << "<nmndVal species=\"Species_1\">10</nmndVal>"
       << "<nmndVal species=\"Species_2\">12</nmndVal>"
       << "<nmndVal species=\"Species_3\">16</nmndVal>"
       << "<nmndVal species=\"Species_4\">14</nmndVal>"
       << "</nciMinNeighborDBH>"
       << "<nciDbhDivisor>1</nciDbhDivisor>"
       << "<nciIncludeSnagsInNCI>0</nciIncludeSnagsInNCI>"
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

////////////////////////////////////////////////////////////////////////////
// WriteNCIGrowthRun4CommonStuff()
////////////////////////////////////////////////////////////////////////////
void WriteNCIGrowthRun4CommonStuff( std::fstream &oOut ) {

  using namespace std;
  //Write file
  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>ConstantGLI</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_4\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_4\" type=\"Sapling\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>NCIMasterGrowth</behaviorName>"
       << "<version>3</version>"
       << "<listPosition>2</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_4\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_4\" type=\"Sapling\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>NCIMasterGrowth</behaviorName>"
       << "<version>3</version>"
       << "<listPosition>3</listPosition>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>StochasticMortality</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>4</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_4\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_4\" type=\"Sapling\"/>"
       << "</behavior>"
       << "</behaviorList>"
       << "<ConstantGLI1>"
       << "<li_constGLI>100</li_constGLI>"
       << "</ConstantGLI1>"
       << "<NCIMasterGrowth2>"
       << "<nciWhichShadingEffect>1</nciWhichShadingEffect>"
       << "<nciWhichCrowdingEffect>1</nciWhichCrowdingEffect>"
       << "<nciWhichNCITerm>1</nciWhichNCITerm>"
       << "<nciWhichSizeEffect>1</nciWhichSizeEffect>"
       << "<nciWhichDamageEffect>0</nciWhichDamageEffect>"
       << "<nciWhichPrecipitationEffect>" << no_precip_effect << "</nciWhichPrecipitationEffect>"
       << "<nciWhichTemperatureEffect>" << no_temp_effect << "</nciWhichTemperatureEffect>"
       << "<nciWhichNitrogenEffect>" << no_nitrogen_effect << "</nciWhichNitrogenEffect>"
       << "<nciWhichInfectionEffect>" << no_infection_effect << "</nciWhichInfectionEffect>"
       << "<gr_stochGrowthMethod>" << deterministic_pdf << "</gr_stochGrowthMethod>"
       << "<nciMaxCrowdingRadius>"
       << "<nmcrVal species=\"Species_1\">10</nmcrVal>"
       << "<nmcrVal species=\"Species_4\">15</nmcrVal>"
       << "</nciMaxCrowdingRadius>"
       << "<nciAlpha>"
       << "<naVal species=\"Species_1\">2.17031683</naVal>"
       << "<naVal species=\"Species_4\">1.33</naVal>"
       << "</nciAlpha>"
       << "<nciBeta>"
       << "<nbVal species=\"Species_1\">0.699942</nbVal>"
       << "<nbVal species=\"Species_4\">0.09</nbVal>"
       << "</nciBeta>"
       << "<gr_nciMaxPotentialGrowth>"
       << "<gr_nmpgVal species=\"Species_1\">3.052587488</gr_nmpgVal>"
       << "<gr_nmpgVal species=\"Species_4\">3.994</gr_nmpgVal>"
       << "</gr_nciMaxPotentialGrowth>"
       << "<nciCrowdingGamma>"
       << "<ncgVal species=\"Species_1\">0</ncgVal>"
       << "<ncgVal species=\"Species_4\">-0.23</ncgVal>"
       << "</nciCrowdingGamma>"
       << "<nciSizeEffectX0>"
       << "<nsex0Val species=\"Species_1\">34.24638994</nsex0Val>"
       << "<nsex0Val species=\"Species_4\">16.43</nsex0Val>"
       << "</nciSizeEffectX0>"
       << "<nciSizeEffectXb>"
       << "<nsexbVal species=\"Species_1\">5</nsexbVal>"
       << "<nsexbVal species=\"Species_4\">1.41</nsexbVal>"
       << "</nciSizeEffectXb>"
       << "<nciCrowdingC>"
       << "<nccVal species=\"Species_1\">0.98</nccVal>"
       << "<nccVal species=\"Species_4\">0.069</nccVal>"
       << "</nciCrowdingC>"
       << "<nciCrowdingD>"
       << "<ncdVal species=\"Species_1\">0.012</ncdVal>"
       << "<ncdVal species=\"Species_4\">1</ncdVal>"
       << "</nciCrowdingD>"
       << "<nciShadingCoefficient>"
       << "<nscVal species=\"Species_1\">0.2</nscVal>"
       << "<nscVal species=\"Species_4\">0.5</nscVal>"
       << "</nciShadingCoefficient>"
       << "<nciShadingExponent>"
       << "<nseVal species=\"Species_1\">1</nseVal>"
       << "<nseVal species=\"Species_4\">1</nseVal>"
       << "</nciShadingExponent>"
       << "<nciSpecies_1NeighborLambda>"
       << "<nlVal species=\"Species_1\">0.66401082</nlVal>"
       << "<nlVal species=\"Species_4\">0.08</nlVal>"
       << "</nciSpecies_1NeighborLambda>"
       << "<nciSpecies_2NeighborLambda>"
       << "<nlVal species=\"Species_1\">0.00442797</nlVal>"
       << "<nlVal species=\"Species_4\">0.03</nlVal>"
       << "</nciSpecies_2NeighborLambda>"
       << "<nciSpecies_3NeighborLambda>"
       << "<nlVal species=\"Species_1\">0.41812471</nlVal>"
       << "<nlVal species=\"Species_4\">0.05</nlVal>"
       << "</nciSpecies_3NeighborLambda>"
       << "<nciSpecies_4NeighborLambda>"
       << "<nlVal species=\"Species_1\">0.41812471</nlVal>"
       << "<nlVal species=\"Species_4\">0.05</nlVal>"
       << "</nciSpecies_4NeighborLambda>"
       << "<nciMinNeighborDBH>"
       << "<nmndVal species=\"Species_1\">10</nmndVal>"
       << "<nmndVal species=\"Species_2\">12</nmndVal>"
       << "<nmndVal species=\"Species_3\">16</nmndVal>"
       << "<nmndVal species=\"Species_4\">14</nmndVal>"
       << "</nciMinNeighborDBH>"
       << "<nciDbhDivisor>1</nciDbhDivisor>"
       << "<nciIncludeSnagsInNCI>0</nciIncludeSnagsInNCI>"
       << "</NCIMasterGrowth2>"
       << "<NCIMasterGrowth3>"
       << "<nciWhichShadingEffect>0</nciWhichShadingEffect>"
       << "<nciWhichCrowdingEffect>1</nciWhichCrowdingEffect>"
       << "<nciWhichNCITerm>1</nciWhichNCITerm>"
       << "<nciWhichSizeEffect>1</nciWhichSizeEffect>"
       << "<nciWhichDamageEffect>0</nciWhichDamageEffect>"
       << "<nciWhichPrecipitationEffect>" << no_precip_effect << "</nciWhichPrecipitationEffect>"
       << "<nciWhichTemperatureEffect>" << no_temp_effect << "</nciWhichTemperatureEffect>"
       << "<nciWhichNitrogenEffect>" << no_nitrogen_effect << "</nciWhichNitrogenEffect>"
       << "<nciWhichInfectionEffect>" << no_infection_effect << "</nciWhichInfectionEffect>"
       << "<gr_stochGrowthMethod>" << deterministic_pdf << "</gr_stochGrowthMethod>"
       << "<nciMaxCrowdingRadius>"
       << "<nmcrVal species=\"Species_2\">10</nmcrVal>"
       << "</nciMaxCrowdingRadius>"
       << "<nciAlpha>"
       << "<naVal species=\"Species_2\">2.81</naVal>"
       << "</nciAlpha>"
       << "<nciBeta>"
       << "<nbVal species=\"Species_2\">0.5</nbVal>"
       << "</nciBeta>"
       << "<gr_nciMaxPotentialGrowth>"
       << "<gr_nmpgVal species=\"Species_2\">3.531</gr_nmpgVal>"
       << "</gr_nciMaxPotentialGrowth>"
       << "<nciCrowdingGamma>"
       << "<ncgVal species=\"Species_2\">-0.13</ncgVal>"
       << "</nciCrowdingGamma>"
       << "<nciSizeEffectX0>"
       << "<nsex0Val species=\"Species_2\">122.23</nsex0Val>"
       << "</nciSizeEffectX0>"
       << "<nciSizeEffectXb>"
       << "<nsexbVal species=\"Species_2\">2.36</nsexbVal>"
       << "</nciSizeEffectXb>"
       << "<nciCrowdingC>"
       << "<nccVal species=\"Species_2\">0.57</nccVal>"
       << "</nciCrowdingC>"
       << "<nciCrowdingD>"
       << "<ncdVal species=\"Species_2\">0.056</ncdVal>"
       << "</nciCrowdingD>"
       << "<nciSpecies_1NeighborLambda>"
       << "<nlVal species=\"Species_2\">0.71</nlVal>"
       << "</nciSpecies_1NeighborLambda>"
       << "<nciSpecies_2NeighborLambda>"
       << "<nlVal species=\"Species_2\">0.12</nlVal>"
       << "</nciSpecies_2NeighborLambda>"
       << "<nciSpecies_3NeighborLambda>"
       << "<nlVal species=\"Species_2\">0.24</nlVal>"
       << "</nciSpecies_3NeighborLambda>"
       << "<nciSpecies_4NeighborLambda>"
       << "<nlVal species=\"Species_2\">0.24</nlVal>"
       << "</nciSpecies_4NeighborLambda>"
       << "<nciMinNeighborDBH>"
       << "<nmndVal species=\"Species_1\">10</nmndVal>"
       << "<nmndVal species=\"Species_2\">12</nmndVal>"
       << "<nmndVal species=\"Species_3\">16</nmndVal>"
       << "<nmndVal species=\"Species_4\">14</nmndVal>"
       << "</nciMinNeighborDBH>"
       << "<nciDbhDivisor>1</nciDbhDivisor>"
       << "<nciIncludeSnagsInNCI>0</nciIncludeSnagsInNCI>"
       << "</NCIMasterGrowth3>"
       << "<StochasticMortality4>"
       << "<mo_stochasticMortRate>"
       << "<mo_smrVal species=\"Species_3\">0</mo_smrVal>"
       << "<mo_smrVal species=\"Species_1\">0</mo_smrVal>"
       << "<mo_smrVal species=\"Species_2\">0</mo_smrVal>"
       << "<mo_smrVal species=\"Species_4\">0</mo_smrVal>"
       << "</mo_stochasticMortRate>"
       << "</StochasticMortality4>"
       << "</paramFile>";
}

////////////////////////////////////////////////////////////////////////////
// WriteNCIGrowthRun5CommonStuff()
////////////////////////////////////////////////////////////////////////////
void WriteNCIGrowthRun5CommonStuff( std::fstream &oOut ) {

  using namespace std;
  //Write file
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
       << "<applyTo species=\"Species_1\" type=\"Snag\"/>"
       << "<applyTo species=\"Species_4\" type=\"Adult\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>NCIMasterGrowth</behaviorName>"
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
       << "<applyTo species=\"Species_1\" type=\"Snag\"/>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_4\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_4\" type=\"Sapling\"/>"
       << "</behavior>"
       << "</behaviorList>"
       << "<Storm1>"
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
       << "</StormDamageApplier2>"
       << "<NCIMasterGrowth3>"
       << "<nciWhichShadingEffect>0</nciWhichShadingEffect>"
       << "<nciWhichCrowdingEffect>1</nciWhichCrowdingEffect>"
       << "<nciWhichNCITerm>2</nciWhichNCITerm>"
       << "<nciWhichSizeEffect>1</nciWhichSizeEffect>"
       << "<nciWhichDamageEffect>1</nciWhichDamageEffect>"
       << "<nciWhichPrecipitationEffect>" << no_precip_effect << "</nciWhichPrecipitationEffect>"
       << "<nciWhichTemperatureEffect>" << no_temp_effect << "</nciWhichTemperatureEffect>"
       << "<nciWhichNitrogenEffect>" << no_nitrogen_effect << "</nciWhichNitrogenEffect>"
       << "<nciWhichInfectionEffect>" << no_infection_effect << "</nciWhichInfectionEffect>"
       << "<gr_stochGrowthMethod>" << deterministic_pdf << "</gr_stochGrowthMethod>"
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
       << "<gr_nciMaxPotentialGrowth>"
       << "<gr_nmpgVal species=\"Species_1\">1.05258749</gr_nmpgVal>"
       << "<gr_nmpgVal species=\"Species_2\">1.531</gr_nmpgVal>"
       << "<gr_nmpgVal species=\"Species_4\">0.994</gr_nmpgVal>"
       << "</gr_nciMaxPotentialGrowth>"
       << "<nciCrowdingGamma>"
       << "<ncgVal species=\"Species_1\">-0.43</ncgVal>"
       << "<ncgVal species=\"Species_2\">-0.36</ncgVal>"
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
       << "<nccVal species=\"Species_1\">0.698</nccVal>"
       << "<nccVal species=\"Species_2\">0.457</nccVal>"
       << "<nccVal species=\"Species_4\">0.469</nccVal>"
       << "</nciCrowdingC>"
       << "<nciCrowdingD>"
       << "<ncdVal species=\"Species_1\">-0.00163</ncdVal>"
       << "<ncdVal species=\"Species_2\">-0.00126</ncdVal>"
       << "<ncdVal species=\"Species_4\">-0.00163</ncdVal>"
       << "</nciCrowdingD>"
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
       << "<nmndVal species=\"Species_1\">5</nmndVal>"
       << "<nmndVal species=\"Species_2\">5</nmndVal>"
       << "<nmndVal species=\"Species_3\">5</nmndVal>"
       << "<nmndVal species=\"Species_4\">5</nmndVal>"
       << "</nciMinNeighborDBH>"
       << "<nciDbhDivisor>100</nciDbhDivisor>"
       << "<nciIncludeSnagsInNCI>1</nciIncludeSnagsInNCI>"
       << "</NCIMasterGrowth3>"
       << "<StochasticMortality4>"
       << "<mo_stochasticMortRate>"
       << "<mo_smrVal species=\"Species_3\">0</mo_smrVal>"
       << "<mo_smrVal species=\"Species_1\">0</mo_smrVal>"
       << "<mo_smrVal species=\"Species_2\">0</mo_smrVal>"
       << "<mo_smrVal species=\"Species_4\">0</mo_smrVal>"
       << "</mo_stochasticMortRate>"
       << "</StochasticMortality4>"
       << "</paramFile>";
}

////////////////////////////////////////////////////////////////////////////
// WriteNCIGrowthRun6CommonStuff()
////////////////////////////////////////////////////////////////////////////
void WriteNCIGrowthRun6CommonStuff( std::fstream &oOut ) {

  using namespace std;
  //Write file
  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>NCIMasterGrowth</behaviorName>"
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
       << "<behaviorName>StochasticMortality</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>2</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Snag\"/>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_4\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_4\" type=\"Sapling\"/>"
       << "</behavior>"
       << "</behaviorList>"
       << "<NCIMasterGrowth1>"
       << "<nciWhichShadingEffect>0</nciWhichShadingEffect>"
       << "<nciWhichCrowdingEffect>0</nciWhichCrowdingEffect>"
       << "<nciWhichNCITerm>0</nciWhichNCITerm>"
       << "<nciWhichSizeEffect>1</nciWhichSizeEffect>"
       << "<nciWhichDamageEffect>0</nciWhichDamageEffect>"
       << "<nciWhichPrecipitationEffect>" << no_precip_effect << "</nciWhichPrecipitationEffect>"
       << "<nciWhichTemperatureEffect>" << no_temp_effect << "</nciWhichTemperatureEffect>"
       << "<nciWhichNitrogenEffect>" << no_nitrogen_effect << "</nciWhichNitrogenEffect>"
       << "<nciWhichInfectionEffect>" << no_infection_effect << "</nciWhichInfectionEffect>"
       << "<gr_stochGrowthMethod>" << deterministic_pdf << "</gr_stochGrowthMethod>"
       << "<gr_nciMaxPotentialGrowth>"
       << "<gr_nmpgVal species=\"Species_1\">1.05258749</gr_nmpgVal>"
       << "<gr_nmpgVal species=\"Species_2\">1.531</gr_nmpgVal>"
       << "<gr_nmpgVal species=\"Species_4\">0.994</gr_nmpgVal>"
       << "</gr_nciMaxPotentialGrowth>"
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
// WriteNCIGrowthErrorFileCommonStuff()
/////////////////////////////////////////////////////////////////////////////
void WriteNCIGrowthErrorFileCommonStuff( std::fstream &oOut )
{
  using namespace std;
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
       << "</allometry>";
}

/////////////////////////////////////////////////////////////////////////////
// WriteNCIGrowthStormErrorFileCommonStuff()
/////////////////////////////////////////////////////////////////////////////
void WriteNCIGrowthStormErrorFileCommonStuff( std::fstream &oOut )
{
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
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>NCIMasterGrowth</behaviorName>"
       << "<version>3</version>"
       << "<listPosition>3</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "</behavior>"
       << "</behaviorList>"
       << "<Storm1>"
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
       << "</st_minDBH>"
       << "<st_stmDmgInterceptMed>"
       << "<st_sdimVal species=\"Species_1\">2.1789601</st_sdimVal>"
       << "<st_sdimVal species=\"Species_2\">2.475987</st_sdimVal>"
       << "</st_stmDmgInterceptMed>"
       << "<st_stmDmgInterceptFull>"
       << "<st_sdifVal species=\"Species_1\">3.6334169</st_sdifVal>"
       << "<st_sdifVal species=\"Species_2\">3.6331242</st_sdifVal>"
       << "</st_stmDmgInterceptFull>"
       << "<st_stmIntensityCoeff>"
       << "<st_sicVal species=\"Species_1\">-0.3545352</st_sicVal>"
       << "<st_sicVal species=\"Species_2\">-1.2289105</st_sicVal>"
       << "</st_stmIntensityCoeff>"
       << "<st_stmDBHCoeff>"
       << "<st_sdcVal species=\"Species_1\">0.8280319</st_sdcVal>"
       << "<st_sdcVal species=\"Species_2\">0.3282479</st_sdcVal>"
       << "</st_stmDBHCoeff>"
       << "<st_stmPropDieMedDmg>"
       << "<st_spdmdVal species=\"Species_1\">0</st_spdmdVal>"
       << "<st_spdmdVal species=\"Species_2\">0</st_spdmdVal>"
       << "</st_stmPropDieMedDmg>"
       << "<st_stmPropDieFullDmg>"
       << "<st_spdfdVal species=\"Species_1\">0</st_spdfdVal>"
       << "<st_spdfdVal species=\"Species_2\">0</st_spdfdVal>"
       << "</st_stmPropDieFullDmg>"
       << "<st_stmPropTipUpFullDmg>"
       << "<st_sptufdVal species=\"Species_1\">0</st_sptufdVal>"
       << "<st_sptufdVal species=\"Species_2\">0</st_sptufdVal>"
       << "</st_stmPropTipUpFullDmg>"
       << "<st_numYearsStormSnags>0</st_numYearsStormSnags>"
       << "<st_numYearsToHeal>4</st_numYearsToHeal>"
       << "</StormDamageApplier2>"
       << "<NCIMasterGrowth3>"
       << "<nciWhichShadingEffect>0</nciWhichShadingEffect>"
       << "<nciWhichCrowdingEffect>1</nciWhichCrowdingEffect>"
       << "<nciWhichNCITerm>2</nciWhichNCITerm>"
       << "<nciWhichSizeEffect>1</nciWhichSizeEffect>"
       << "<nciWhichDamageEffect>1</nciWhichDamageEffect>"
       << "<nciWhichPrecipitationEffect>" << no_precip_effect << "</nciWhichPrecipitationEffect>"
       << "<nciWhichTemperatureEffect>" << no_temp_effect << "</nciWhichTemperatureEffect>"
       << "<nciWhichNitrogenEffect>" << no_nitrogen_effect << "</nciWhichNitrogenEffect>"
       << "<nciWhichInfectionEffect>" << no_infection_effect << "</nciWhichInfectionEffect>"
       << "<gr_stochGrowthMethod>" << deterministic_pdf << "</gr_stochGrowthMethod>"
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
       << "</nciCrowdingD>";
}

////////////////////////////////////////////////////////////////////////////
// WriteNCIGrowthXMLErrorFile1()
////////////////////////////////////////////////////////////////////////////
const char* WriteNCIGrowthXMLErrorFile1(bool bDefault) {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  WriteNCIGrowthErrorFileCommonStuff(oOut);

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
       << "<nciWhichShadingEffect>0</nciWhichShadingEffect>"
       << "<nciWhichCrowdingEffect>0</nciWhichCrowdingEffect>";

  if (bDefault) {
    oOut << "<nciWhichNCITerm>1</nciWhichNCITerm>";
  } else {
    oOut << "<nciWhichNCITerm>2</nciWhichNCITerm>";
  }
  oOut << "<nciWhichSizeEffect>0</nciWhichSizeEffect>"
       << "<nciWhichDamageEffect>0</nciWhichDamageEffect>"
       << "<nciWhichPrecipitationEffect>" << no_precip_effect << "</nciWhichPrecipitationEffect>"
       << "<nciWhichTemperatureEffect>" << no_temp_effect << "</nciWhichTemperatureEffect>"
       << "<nciWhichNitrogenEffect>" << no_nitrogen_effect << "</nciWhichNitrogenEffect>"
       << "<nciWhichInfectionEffect>" << no_infection_effect << "</nciWhichInfectionEffect>"
       << "<gr_stochGrowthMethod>" << deterministic_pdf << "</gr_stochGrowthMethod>"
       << "<nciMaxCrowdingRadius>"
       << "<nmcrVal species=\"Species_1\">10</nmcrVal>"
       << "<nmcrVal species=\"Species_2\">-10</nmcrVal>"
       << "</nciMaxCrowdingRadius>";

  if (!bDefault) {
    oOut << "<nciNeighStormEffMedDmg>"
         << "<nnsemdVal species=\"Species_1\">0.33</nnsemdVal>"
         << "<nnsemdVal species=\"Species_2\">0.33</nnsemdVal>"
         << "</nciNeighStormEffMedDmg>"
         << "<nciNeighStormEffFullDmg>"
         << "<nnsefdVal species=\"Species_1\">0.54</nnsefdVal>"
         << "<nnsefdVal species=\"Species_2\">0.54</nnsefdVal>"
         << "</nciNeighStormEffFullDmg>";
  }
  oOut << "<nciAlpha>"
       << "<naVal species=\"Species_1\">2.81</naVal>"
       << "<naVal species=\"Species_2\">2.81</naVal>"
       << "</nciAlpha>"
       << "<nciBeta>"
       << "<nbVal species=\"Species_1\">0.5</nbVal>"
       << "<nbVal species=\"Species_2\">0.5</nbVal>"
       << "</nciBeta>"
       << "<gr_nciMaxPotentialGrowth>"
       << "<gr_nmpgVal species=\"Species_1\">15.31</gr_nmpgVal>"
       << "<gr_nmpgVal species=\"Species_2\">15.31</gr_nmpgVal>"
       << "</gr_nciMaxPotentialGrowth>"
       << "<nciSpecies_1NeighborLambda>"
       << "<nlVal species=\"Species_1\">0.66</nlVal>"
       << "<nlVal species=\"Species_2\">0.66</nlVal>"
       << "</nciSpecies_1NeighborLambda>"
       << "<nciSpecies_2NeighborLambda>"
       << "<nlVal species=\"Species_1\">0.66</nlVal>"
       << "<nlVal species=\"Species_2\">0.66</nlVal>"
       << "</nciSpecies_2NeighborLambda>"
       << "<nciMinNeighborDBH>"
       << "<nmndVal species=\"Species_1\">0</nmndVal>"
       << "<nmndVal species=\"Species_2\">0</nmndVal>"
       << "</nciMinNeighborDBH>"
       << "<nciDbhDivisor>100</nciDbhDivisor>"
       << "<nciIncludeSnagsInNCI>0</nciIncludeSnagsInNCI>"
       << "</NCIMasterGrowth1>"
       << "</paramFile>";


  oOut.close();

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteNCIGrowthXMLErrorFile2()
////////////////////////////////////////////////////////////////////////////
const char* WriteNCIGrowthXMLErrorFile2() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  WriteNCIGrowthErrorFileCommonStuff(oOut);

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
       << "<nciWhichShadingEffect>0</nciWhichShadingEffect>"
       << "<nciWhichCrowdingEffect>1</nciWhichCrowdingEffect>"
       << "<nciWhichNCITerm>1</nciWhichNCITerm>"
       << "<nciWhichSizeEffect>1</nciWhichSizeEffect>"
       << "<nciWhichDamageEffect>0</nciWhichDamageEffect>"
       << "<nciWhichPrecipitationEffect>" << no_precip_effect << "</nciWhichPrecipitationEffect>"
       << "<nciWhichTemperatureEffect>" << no_temp_effect << "</nciWhichTemperatureEffect>"
       << "<nciWhichNitrogenEffect>" << no_nitrogen_effect << "</nciWhichNitrogenEffect>"
       << "<nciWhichInfectionEffect>" << no_infection_effect << "</nciWhichInfectionEffect>"
       << "<gr_stochGrowthMethod>" << deterministic_pdf << "</gr_stochGrowthMethod>"
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
       << "<gr_nciMaxPotentialGrowth>"
       << "<gr_nmpgVal species=\"Species_1\">15.31</gr_nmpgVal>"
       << "<gr_nmpgVal species=\"Species_2\">-15.31</gr_nmpgVal>"
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
       << "<nciSpecies_1NeighborLambda>"
       << "<nlVal species=\"Species_1\">0.66</nlVal>"
       << "<nlVal species=\"Species_2\">0.66</nlVal>"
       << "</nciSpecies_1NeighborLambda>"
       << "<nciSpecies_2NeighborLambda>"
       << "<nlVal species=\"Species_1\">0.66</nlVal>"
       << "<nlVal species=\"Species_2\">0.66</nlVal>"
       << "</nciSpecies_2NeighborLambda>"
       << "<nciMinNeighborDBH>"
       << "<nmndVal species=\"Species_1\">0</nmndVal>"
       << "<nmndVal species=\"Species_2\">0</nmndVal>"
       << "</nciMinNeighborDBH>"
       << "<nciDbhDivisor>100</nciDbhDivisor>"
       << "<nciIncludeSnagsInNCI>0</nciIncludeSnagsInNCI>"
       << "</NCIMasterGrowth1>"
       << "</paramFile>";


  oOut.close();

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteNCIGrowthXMLErrorFile3()
////////////////////////////////////////////////////////////////////////////
const char* WriteNCIGrowthXMLErrorFile3() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  WriteNCIGrowthErrorFileCommonStuff(oOut);

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
       << "<nciWhichShadingEffect>0</nciWhichShadingEffect>"
       << "<nciWhichCrowdingEffect>1</nciWhichCrowdingEffect>"
       << "<nciWhichNCITerm>1</nciWhichNCITerm>"
       << "<nciWhichSizeEffect>1</nciWhichSizeEffect>"
       << "<nciWhichDamageEffect>0</nciWhichDamageEffect>"
       << "<nciWhichPrecipitationEffect>" << no_precip_effect << "</nciWhichPrecipitationEffect>"
       << "<nciWhichTemperatureEffect>" << no_temp_effect << "</nciWhichTemperatureEffect>"
       << "<nciWhichNitrogenEffect>" << no_nitrogen_effect << "</nciWhichNitrogenEffect>"
       << "<nciWhichInfectionEffect>" << no_infection_effect << "</nciWhichInfectionEffect>"
       << "<gr_stochGrowthMethod>" << deterministic_pdf << "</gr_stochGrowthMethod>"
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
       << "<nciSpecies_1NeighborLambda>"
       << "<nlVal species=\"Species_1\">0.66</nlVal>"
       << "<nlVal species=\"Species_2\">0.66</nlVal>"
       << "</nciSpecies_1NeighborLambda>"
       << "<nciSpecies_2NeighborLambda>"
       << "<nlVal species=\"Species_1\">0.66</nlVal>"
       << "<nlVal species=\"Species_2\">0.66</nlVal>"
       << "</nciSpecies_2NeighborLambda>"
       << "<nciMinNeighborDBH>"
       << "<nmndVal species=\"Species_1\">0</nmndVal>"
       << "<nmndVal species=\"Species_2\">0</nmndVal>"
       << "</nciMinNeighborDBH>"
       << "<nciDbhDivisor>100</nciDbhDivisor>"
       << "<nciIncludeSnagsInNCI>0</nciIncludeSnagsInNCI>"
       << "</NCIMasterGrowth1>"
       << "</paramFile>";


  oOut.close();

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteNCIGrowthXMLErrorFile4()
////////////////////////////////////////////////////////////////////////////
const char* WriteNCIGrowthXMLErrorFile4() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  WriteNCIGrowthErrorFileCommonStuff(oOut);

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
       << "<nciWhichShadingEffect>0</nciWhichShadingEffect>"
       << "<nciWhichCrowdingEffect>1</nciWhichCrowdingEffect>"
       << "<nciWhichNCITerm>1</nciWhichNCITerm>"
       << "<nciWhichSizeEffect>1</nciWhichSizeEffect>"
       << "<nciWhichDamageEffect>0</nciWhichDamageEffect>"
       << "<nciWhichPrecipitationEffect>" << no_precip_effect << "</nciWhichPrecipitationEffect>"
       << "<nciWhichTemperatureEffect>" << no_temp_effect << "</nciWhichTemperatureEffect>"
       << "<nciWhichNitrogenEffect>" << no_nitrogen_effect << "</nciWhichNitrogenEffect>"
       << "<nciWhichInfectionEffect>" << no_infection_effect << "</nciWhichInfectionEffect>"
       << "<gr_stochGrowthMethod>" << deterministic_pdf << "</gr_stochGrowthMethod>"
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
       << "<gr_nciMaxPotentialGrowth>"
       << "<gr_nmpgVal species=\"Species_1\">15.31</gr_nmpgVal>"
       << "<gr_nmpgVal species=\"Species_2\">15.31</gr_nmpgVal>"
       << "</gr_nciMaxPotentialGrowth>"
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
       << "<nciSpecies_1NeighborLambda>"
       << "<nlVal species=\"Species_1\">0.66</nlVal>"
       << "<nlVal species=\"Species_2\">0.66</nlVal>"
       << "</nciSpecies_1NeighborLambda>"
       << "<nciSpecies_2NeighborLambda>"
       << "<nlVal species=\"Species_1\">0.66</nlVal>"
       << "<nlVal species=\"Species_2\">0.66</nlVal>"
       << "</nciSpecies_2NeighborLambda>"
       << "<nciMinNeighborDBH>"
       << "<nmndVal species=\"Species_1\">0</nmndVal>"
       << "<nmndVal species=\"Species_2\">0</nmndVal>"
       << "</nciMinNeighborDBH>"
       << "<nciDbhDivisor>100</nciDbhDivisor>"
       << "<nciIncludeSnagsInNCI>0</nciIncludeSnagsInNCI>"
       << "</NCIMasterGrowth1>"
       << "</paramFile>";


  oOut.close();

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteNCIGrowthXMLErrorFile5()
////////////////////////////////////////////////////////////////////////////
const char* WriteNCIGrowthXMLErrorFile5() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  WriteNCIGrowthErrorFileCommonStuff(oOut);
  WriteNCIGrowthStormErrorFileCommonStuff(oOut);

  //Write file
  oOut << "<nciStormEffMedDmg>"
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
       << "<nlVal species=\"Species_1\">0.66</nlVal>"
       << "<nlVal species=\"Species_2\">0.66</nlVal>"
       << "</nciSpecies_1NeighborLambda>"
       << "<nciSpecies_2NeighborLambda>"
       << "<nlVal species=\"Species_1\">0.66</nlVal>"
       << "<nlVal species=\"Species_2\">0.66</nlVal>"
       << "</nciSpecies_2NeighborLambda>"
       << "<nciMinNeighborDBH>"
       << "<nmndVal species=\"Species_1\">0</nmndVal>"
       << "<nmndVal species=\"Species_2\">0</nmndVal>"
       << "</nciMinNeighborDBH>"
       << "<nciDbhDivisor>100</nciDbhDivisor>"
       << "<nciIncludeSnagsInNCI>0</nciIncludeSnagsInNCI>"
       << "</NCIMasterGrowth3>"
       << "</paramFile>";


  oOut.close();

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteNCIGrowthXMLErrorFile6()
////////////////////////////////////////////////////////////////////////////
const char* WriteNCIGrowthXMLErrorFile6() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  WriteNCIGrowthErrorFileCommonStuff(oOut);
  WriteNCIGrowthStormErrorFileCommonStuff(oOut);

  //Write file
  oOut << "<nciStormEffMedDmg>"
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
       << "<nlVal species=\"Species_1\">0.66</nlVal>"
       << "<nlVal species=\"Species_2\">0.66</nlVal>"
       << "</nciSpecies_1NeighborLambda>"
       << "<nciSpecies_2NeighborLambda>"
       << "<nlVal species=\"Species_1\">0.66</nlVal>"
       << "<nlVal species=\"Species_2\">0.66</nlVal>"
       << "</nciSpecies_2NeighborLambda>"
       << "<nciMinNeighborDBH>"
       << "<nmndVal species=\"Species_1\">0</nmndVal>"
       << "<nmndVal species=\"Species_2\">0</nmndVal>"
       << "</nciMinNeighborDBH>"
       << "<nciDbhDivisor>100</nciDbhDivisor>"
       << "<nciIncludeSnagsInNCI>0</nciIncludeSnagsInNCI>"
       << "</NCIMasterGrowth3>"
       << "</paramFile>";


  oOut.close();

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteNCIGrowthXMLErrorFile7()
////////////////////////////////////////////////////////////////////////////
const char* WriteNCIGrowthXMLErrorFile7() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  WriteNCIGrowthErrorFileCommonStuff(oOut);
  WriteNCIGrowthStormErrorFileCommonStuff(oOut);

  //Write file
  oOut << "<nciStormEffMedDmg>"
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
       << "<nlVal species=\"Species_1\">0.66</nlVal>"
       << "<nlVal species=\"Species_2\">0.66</nlVal>"
       << "</nciSpecies_1NeighborLambda>"
       << "<nciSpecies_2NeighborLambda>"
       << "<nlVal species=\"Species_1\">0.66</nlVal>"
       << "<nlVal species=\"Species_2\">0.66</nlVal>"
       << "</nciSpecies_2NeighborLambda>"
       << "<nciMinNeighborDBH>"
       << "<nmndVal species=\"Species_1\">0</nmndVal>"
       << "<nmndVal species=\"Species_2\">0</nmndVal>"
       << "</nciMinNeighborDBH>"
       << "<nciDbhDivisor>100</nciDbhDivisor>"
       << "<nciIncludeSnagsInNCI>0</nciIncludeSnagsInNCI>"
       << "</NCIMasterGrowth3>"
       << "</paramFile>";


  oOut.close();

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteNCIGrowthXMLErrorFile8()
////////////////////////////////////////////////////////////////////////////
const char* WriteNCIGrowthXMLErrorFile8() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  WriteNCIGrowthErrorFileCommonStuff(oOut);
  WriteNCIGrowthStormErrorFileCommonStuff(oOut);

  //Write file
  oOut << "<nciStormEffMedDmg>"
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
       << "<nlVal species=\"Species_1\">0.66</nlVal>"
       << "<nlVal species=\"Species_2\">0.66</nlVal>"
       << "</nciSpecies_1NeighborLambda>"
       << "<nciSpecies_2NeighborLambda>"
       << "<nlVal species=\"Species_1\">0.66</nlVal>"
       << "<nlVal species=\"Species_2\">0.66</nlVal>"
       << "</nciSpecies_2NeighborLambda>"
       << "<nciMinNeighborDBH>"
       << "<nmndVal species=\"Species_1\">0</nmndVal>"
       << "<nmndVal species=\"Species_2\">0</nmndVal>"
       << "</nciMinNeighborDBH>"
       << "<nciDbhDivisor>100</nciDbhDivisor>"
       << "<nciIncludeSnagsInNCI>0</nciIncludeSnagsInNCI>"
       << "</NCIMasterGrowth3>"
       << "</paramFile>";


  oOut.close();

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteNCIGrowthXMLErrorFile9()
////////////////////////////////////////////////////////////////////////////
const char* WriteNCIGrowthXMLErrorFile9() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  WriteNCIGrowthErrorFileCommonStuff(oOut);
  WriteNCIGrowthStormErrorFileCommonStuff(oOut);

  //Write file
  oOut << "<nciStormEffMedDmg>"
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
       << "<nlVal species=\"Species_1\">0.66</nlVal>"
       << "<nlVal species=\"Species_2\">0.66</nlVal>"
       << "</nciSpecies_1NeighborLambda>"
       << "<nciSpecies_2NeighborLambda>"
       << "<nlVal species=\"Species_1\">0.66</nlVal>"
       << "<nlVal species=\"Species_2\">0.66</nlVal>"
       << "</nciSpecies_2NeighborLambda>"
       << "<nciMinNeighborDBH>"
       << "<nmndVal species=\"Species_1\">0</nmndVal>"
       << "<nmndVal species=\"Species_2\">0</nmndVal>"
       << "</nciMinNeighborDBH>"
       << "<nciDbhDivisor>100</nciDbhDivisor>"
       << "<nciIncludeSnagsInNCI>0</nciIncludeSnagsInNCI>"
       << "</NCIMasterGrowth3>"
       << "</paramFile>";


  oOut.close();

  return cFileString;
}


////////////////////////////////////////////////////////////////////////////
// WriteNCIGrowthXMLErrorFile10()
////////////////////////////////////////////////////////////////////////////
const char* WriteNCIGrowthXMLErrorFile10() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  WriteNCIGrowthErrorFileCommonStuff(oOut);
  WriteNCIGrowthStormErrorFileCommonStuff(oOut);

  //Write file
  oOut << "<nciStormEffMedDmg>"
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
       << "<nlVal species=\"Species_1\">0.66</nlVal>"
       << "<nlVal species=\"Species_2\">0.66</nlVal>"
       << "</nciSpecies_1NeighborLambda>"
       << "<nciSpecies_2NeighborLambda>"
       << "<nlVal species=\"Species_1\">0.66</nlVal>"
       << "<nlVal species=\"Species_2\">0.66</nlVal>"
       << "</nciSpecies_2NeighborLambda>"
       << "<nciMinNeighborDBH>"
       << "<nmndVal species=\"Species_1\">0</nmndVal>"
       << "<nmndVal species=\"Species_2\">0</nmndVal>"
       << "</nciMinNeighborDBH>"
       << "<nciDbhDivisor>100</nciDbhDivisor>"
       << "<nciIncludeSnagsInNCI>0</nciIncludeSnagsInNCI>"
       << "</NCIMasterGrowth3>"
       << "</paramFile>";


  oOut.close();

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteNCIGrowthXMLErrorFile11()
////////////////////////////////////////////////////////////////////////////
const char* WriteNCIGrowthXMLErrorFile11() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  WriteNCIGrowthErrorFileCommonStuff(oOut);
  WriteNCIGrowthStormErrorFileCommonStuff(oOut);

  //Write file
  oOut << "<nciStormEffMedDmg>"
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
       << "<nlVal species=\"Species_1\">0.66</nlVal>"
       << "<nlVal species=\"Species_2\">0.66</nlVal>"
       << "</nciSpecies_1NeighborLambda>"
       << "<nciSpecies_2NeighborLambda>"
       << "<nlVal species=\"Species_1\">0.66</nlVal>"
       << "<nlVal species=\"Species_2\">0.66</nlVal>"
       << "</nciSpecies_2NeighborLambda>"
       << "<nciMinNeighborDBH>"
       << "<nmndVal species=\"Species_1\">0</nmndVal>"
       << "<nmndVal species=\"Species_2\">0</nmndVal>"
       << "</nciMinNeighborDBH>"
       << "<nciDbhDivisor>100</nciDbhDivisor>"
       << "<nciIncludeSnagsInNCI>0</nciIncludeSnagsInNCI>"
       << "</NCIMasterGrowth3>"
       << "</paramFile>";


  oOut.close();

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteNCIGrowthXMLErrorFile12()
////////////////////////////////////////////////////////////////////////////
const char* WriteNCIGrowthXMLErrorFile12() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  WriteNCIGrowthErrorFileCommonStuff(oOut);

  //Write file
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
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>NCIMasterGrowth</behaviorName>"
       << "<version>3</version>"
       << "<listPosition>3</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "</behavior>"
       << "</behaviorList>"
       << "<Storm1>"
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
       << "</st_minDBH>"
       << "<st_stmDmgInterceptMed>"
       << "<st_sdimVal species=\"Species_1\">2.1789601</st_sdimVal>"
       << "<st_sdimVal species=\"Species_2\">2.475987</st_sdimVal>"
       << "</st_stmDmgInterceptMed>"
       << "<st_stmDmgInterceptFull>"
       << "<st_sdifVal species=\"Species_1\">3.6334169</st_sdifVal>"
       << "<st_sdifVal species=\"Species_2\">3.6331242</st_sdifVal>"
       << "</st_stmDmgInterceptFull>"
       << "<st_stmIntensityCoeff>"
       << "<st_sicVal species=\"Species_1\">-0.3545352</st_sicVal>"
       << "<st_sicVal species=\"Species_2\">-1.2289105</st_sicVal>"
       << "</st_stmIntensityCoeff>"
       << "<st_stmDBHCoeff>"
       << "<st_sdcVal species=\"Species_1\">0.8280319</st_sdcVal>"
       << "<st_sdcVal species=\"Species_2\">0.3282479</st_sdcVal>"
       << "</st_stmDBHCoeff>"
       << "<st_stmPropDieMedDmg>"
       << "<st_spdmdVal species=\"Species_1\">0</st_spdmdVal>"
       << "<st_spdmdVal species=\"Species_2\">0</st_spdmdVal>"
       << "</st_stmPropDieMedDmg>"
       << "<st_stmPropDieFullDmg>"
       << "<st_spdfdVal species=\"Species_1\">0</st_spdfdVal>"
       << "<st_spdfdVal species=\"Species_2\">0</st_spdfdVal>"
       << "</st_stmPropDieFullDmg>"
       << "<st_stmPropTipUpFullDmg>"
       << "<st_sptufdVal species=\"Species_1\">0</st_sptufdVal>"
       << "<st_sptufdVal species=\"Species_2\">0</st_sptufdVal>"
       << "</st_stmPropTipUpFullDmg>"
       << "<st_numYearsStormSnags>0</st_numYearsStormSnags>"
       << "<st_numYearsToHeal>4</st_numYearsToHeal>"
       << "</StormDamageApplier2>"
       << "<NCIMasterGrowth3>"
       << "<nciWhichShadingEffect>0</nciWhichShadingEffect>"
       << "<nciWhichCrowdingEffect>1</nciWhichCrowdingEffect>"
       << "<nciWhichNCITerm>2</nciWhichNCITerm>"
       << "<nciWhichSizeEffect>1</nciWhichSizeEffect>"
       << "<nciWhichDamageEffect>1</nciWhichDamageEffect>"
       << "<nciWhichPrecipitationEffect>" << no_precip_effect << "</nciWhichPrecipitationEffect>"
       << "<nciWhichTemperatureEffect>" << no_temp_effect << "</nciWhichTemperatureEffect>"
       << "<nciWhichNitrogenEffect>" << no_nitrogen_effect << "</nciWhichNitrogenEffect>"
       << "<nciWhichInfectionEffect>" << no_infection_effect << "</nciWhichInfectionEffect>"
       << "<gr_stochGrowthMethod>" << deterministic_pdf << "</gr_stochGrowthMethod>"
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
       << "<nlVal species=\"Species_1\">0.66</nlVal>"
       << "<nlVal species=\"Species_2\">0.66</nlVal>"
       << "</nciSpecies_1NeighborLambda>"
       << "<nciSpecies_2NeighborLambda>"
       << "<nlVal species=\"Species_1\">0.66</nlVal>"
       << "<nlVal species=\"Species_2\">0.66</nlVal>"
       << "</nciSpecies_2NeighborLambda>"
       << "<nciMinNeighborDBH>"
       << "<nmndVal species=\"Species_1\">0</nmndVal>"
       << "<nmndVal species=\"Species_2\">0</nmndVal>"
       << "</nciMinNeighborDBH>"
       << "<nciDbhDivisor>100</nciDbhDivisor>"
       << "<nciIncludeSnagsInNCI>0</nciIncludeSnagsInNCI>"
       << "</NCIMasterGrowth3>"
       << "</paramFile>";


  oOut.close();

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteNCIGrowthXMLErrorFile13()
////////////////////////////////////////////////////////////////////////////
const char* WriteNCIGrowthXMLErrorFile13() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  WriteNCIGrowthErrorFileCommonStuff(oOut);

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
       << "<nciWhichShadingEffect>1</nciWhichShadingEffect>"
       << "<nciWhichCrowdingEffect>0</nciWhichCrowdingEffect>"
       << "<nciWhichNCITerm>0</nciWhichNCITerm>"
       << "<nciWhichSizeEffect>1</nciWhichSizeEffect>"
       << "<nciWhichDamageEffect>0</nciWhichDamageEffect>"
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
       << "<nciShadingCoefficient>"
       << "<nscVal species=\"Species_1\">0.2</nscVal>"
       << "<nscVal species=\"Species_2\">0.2</nscVal>"
       << "</nciShadingCoefficient>"
       << "<nciShadingExponent>"
       << "<nseVal species=\"Species_1\">0.5</nseVal>"
       << "<nseVal species=\"Species_2\">0.5</nseVal>"
       << "</nciShadingExponent>"
       << "</NCIMasterGrowth1>"
       << "</paramFile>";


  oOut.close();

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteNCIGrowthXMLErrorFile14()
////////////////////////////////////////////////////////////////////////////
const char* WriteNCIGrowthXMLErrorFile14(bool bDefault) {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  WriteNCIGrowthErrorFileCommonStuff(oOut);

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
       << "<nciWhichShadingEffect>0</nciWhichShadingEffect>"
       << "<nciWhichCrowdingEffect>0</nciWhichCrowdingEffect>";

  if (bDefault) {
    oOut << "<nciWhichNCITerm>1</nciWhichNCITerm>";
  } else {
    oOut << "<nciWhichNCITerm>2</nciWhichNCITerm>";
  }

  oOut << "<nciWhichSizeEffect>0</nciWhichSizeEffect>"
       << "<nciWhichDamageEffect>0</nciWhichDamageEffect>"
       << "<nciWhichPrecipitationEffect>" << no_precip_effect << "</nciWhichPrecipitationEffect>"
       << "<nciWhichTemperatureEffect>" << no_temp_effect << "</nciWhichTemperatureEffect>"
       << "<nciWhichNitrogenEffect>" << no_nitrogen_effect << "</nciWhichNitrogenEffect>"
       << "<nciWhichInfectionEffect>" << no_infection_effect << "</nciWhichInfectionEffect>"
       << "<gr_stochGrowthMethod>" << deterministic_pdf << "</gr_stochGrowthMethod>"
       << "<nciMaxCrowdingRadius>"
       << "<nmcrVal species=\"Species_1\">10</nmcrVal>"
       << "<nmcrVal species=\"Species_2\">10</nmcrVal>"
       << "</nciMaxCrowdingRadius>";

  if (!bDefault) {
    oOut << "<nciNeighStormEffMedDmg>"
         << "<nnsemdVal species=\"Species_1\">0.33</nnsemdVal>"
         << "<nnsemdVal species=\"Species_2\">0.33</nnsemdVal>"
         << "</nciNeighStormEffMedDmg>"
         << "<nciNeighStormEffFullDmg>"
         << "<nnsefdVal species=\"Species_1\">0.54</nnsefdVal>"
         << "<nnsefdVal species=\"Species_2\">0.54</nnsefdVal>"
         << "</nciNeighStormEffFullDmg>";
  }
  oOut << "<nciAlpha>"
       << "<naVal species=\"Species_1\">2.81</naVal>"
       << "<naVal species=\"Species_2\">2.81</naVal>"
       << "</nciAlpha>"
       << "<nciBeta>"
       << "<nbVal species=\"Species_1\">0.5</nbVal>"
       << "<nbVal species=\"Species_2\">0.5</nbVal>"
       << "</nciBeta>"
       << "<gr_nciMaxPotentialGrowth>"
       << "<gr_nmpgVal species=\"Species_1\">15.31</gr_nmpgVal>"
       << "<gr_nmpgVal species=\"Species_2\">15.31</gr_nmpgVal>"
       << "</gr_nciMaxPotentialGrowth>"
       << "<nciSpecies_1NeighborLambda>"
       << "<nlVal species=\"Species_1\">0.66</nlVal>"
       << "<nlVal species=\"Species_2\">0.66</nlVal>"
       << "</nciSpecies_1NeighborLambda>"
       << "<nciSpecies_2NeighborLambda>"
       << "<nlVal species=\"Species_1\">0.66</nlVal>"
       << "<nlVal species=\"Species_2\">0.66</nlVal>"
       << "</nciSpecies_2NeighborLambda>"
       << "<nciShadingCoefficient>"
       << "<nscVal species=\"Species_1\">0.2</nscVal>"
       << "<nscVal species=\"Species_2\">0.2</nscVal>"
       << "</nciShadingCoefficient>"
       << "<nciShadingExponent>"
       << "<nseVal species=\"Species_1\">0.5</nseVal>"
       << "<nseVal species=\"Species_2\">0.5</nseVal>"
       << "</nciShadingExponent>"
       << "<nciMinNeighborDBH>"
       << "<nmndVal species=\"Species_1\">-10</nmndVal>"
       << "<nmndVal species=\"Species_2\">0</nmndVal>"
       << "</nciMinNeighborDBH>"
       << "<nciDbhDivisor>100</nciDbhDivisor>"
       << "<nciIncludeSnagsInNCI>0</nciIncludeSnagsInNCI>"
       << "</NCIMasterGrowth1>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}
