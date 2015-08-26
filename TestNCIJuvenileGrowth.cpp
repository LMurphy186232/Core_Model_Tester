//---------------------------------------------------------------------------
// TestNCIJuvenileGrowth.cpp
//---------------------------------------------------------------------------
#include "TestNCIJuvenileGrowth.h"
#include <gtest/gtest.h>
#include <fstream>
#include <math.h>
#include "TreePopulation.h"
#include "NCIEffectsList.h"
#include "SimManager.h"
#include "BehaviorBase.h"

////////////////////////////////////////////////////////////////////////////
// TestErrorProcessing()
////////////////////////////////////////////////////////////////////////////
TEST(NCIJuvenileGrowth, TestErrorProcessing) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try
  {
    p_oSimManager->ReadFile(WriteNCIJuvenileGrowthXMLErrorFile1());
    FAIL() << "TestNCIGrowth error processing didn't catch error for WriteNCIJuvenileGrowthXMLErrorFile1.";
  }
  catch (modelErr& err)
  {
    if (err.sFunction.compare("clNCIWithSeedlings::DoSetup") != 0)
    {
      FAIL() << "TestNCIJuvenileGrowth error processing caught wrong error for WriteNCIJuvenileGrowthXMLErrorFile1.";
    }
    ;
  }

  try
  {
    p_oSimManager->ReadFile(WriteNCIJuvenileGrowthXMLErrorFile2());
    FAIL() << "TestNCIGrowth error processing didn't catch error for WriteNCIJuvenileGrowthXMLErrorFile3.";
  }
  catch (modelErr& err)
  {
    if (err.sFunction.compare("clNCIWithSeedlings::DoSetup") != 0)
    {
      FAIL() << "TestNCIJuvenileGrowth error processing caught wrong error for WriteNCIJuvenileGrowthXMLErrorFile3.";
    }
    ;
  }
  delete p_oSimManager;
}

////////////////////////////////////////////////////////////////////////////
// TestRun1()
// Performs a test run of NCI growth. WriteNCIJuvenileGrowthXMLFile1() performs setup for a
// 1-year timestep; then WriteNCIJuvenileGrowthXMLFile2() performs setup for an otherwise
// identical 3-year timestep.
////////////////////////////////////////////////////////////////////////////
TEST(NCIJuvenileGrowth, TestRun1) {

  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    clTreePopulation * p_oPop;
    clTree *p_oTargetTree1, *p_oTargetTree2, *p_oTree;
    float fDiam, fExpectedDiam, fGrowth, fExpectedGrowth;

    //***********************************
    // Run 1 - 1 year timestep
    //***********************************
    //Load our test file and get our tree population pointers
    p_oSimManager->ReadFile( WriteNCIJuvenileGrowthXMLFile1() );
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );

    //Create our two target trees
    fDiam = 8;
    p_oTargetTree1 = p_oPop->CreateTree(10, 10, 0, clTreePopulation::sapling, fDiam);

    fDiam = 8;
    p_oTargetTree2 = p_oPop->CreateTree(50, 50, 0, clTreePopulation::sapling, fDiam);

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
    fExpectedDiam = 10.38998007;
    fExpectedGrowth = 1.999850378;
    p_oTargetTree1->GetValue(p_oPop->GetDiam10Code(p_oTargetTree1->GetSpecies(), p_oTargetTree1->GetType()), &fDiam);
    p_oTargetTree1->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTargetTree1->GetSpecies(), p_oTargetTree1->GetType()), &fGrowth);
    EXPECT_LT(fabs(fDiam - fExpectedDiam), 0.01);
    EXPECT_LT(fabs(fGrowth - fExpectedGrowth), 0.01);

    fExpectedDiam = 10.18807678;
    fExpectedGrowth = 0.990333932;
    p_oTargetTree2->GetValue(p_oPop->GetDiam10Code(p_oTargetTree2->GetSpecies(), p_oTargetTree2->GetType()), &fDiam);
    p_oTargetTree2->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTargetTree2->GetSpecies(), p_oTargetTree2->GetType()), &fGrowth);
    EXPECT_LT(fabs(fDiam - fExpectedDiam), 0.01);
    EXPECT_LT(fabs(fGrowth - fExpectedGrowth), 0.01);

    //***********************************
    // Run 2 - 3 year timestep
    //***********************************
    //Load our test file and get our tree population pointers
    p_oSimManager->ReadFile( WriteNCIJuvenileGrowthXMLFile2() );
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );

    //Create our two target trees
    fDiam = 8;
    p_oTargetTree1 = p_oPop->CreateTree(10, 10, 0, clTreePopulation::sapling, fDiam);

    fDiam = 8;
    p_oTargetTree2 = p_oPop->CreateTree(50, 50, 0, clTreePopulation::sapling, fDiam);

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
    fExpectedDiam = 11.19225096;
    fExpectedGrowth = 2.003734955;
    p_oTargetTree1->GetValue(p_oPop->GetDiam10Code(p_oTargetTree1->GetSpecies(), p_oTargetTree1->GetType()), &fDiam);
    p_oTargetTree1->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTargetTree1->GetSpecies(), p_oTargetTree1->GetType()), &fGrowth);
    EXPECT_LT(fabs(fDiam - fExpectedDiam), 0.01);
    EXPECT_LT(fabs(fGrowth - fExpectedGrowth), 0.01);

    fExpectedDiam = 10.58479054;
    fExpectedGrowth = 0.991300923;
    p_oTargetTree2->GetValue(p_oPop->GetDiam10Code(p_oTargetTree2->GetSpecies(), p_oTargetTree2->GetType()), &fDiam);
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
// TestRun2()
// Tests the growth calculations at two timestep lengths. WriteNCIJuvenileGrowthXMLFile3() is
// used to do setup in the first case, for a 1 year timestep. WriteNCIJuvenileGrowthXMLFile4()
// does setup for a 3 year timestep and the growth is checked for the same
// trees.
////////////////////////////////////////////////////////////////////////////
TEST(NCIJuvenileGrowth, TestRun2) {
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
    int iSpecies, i;

    //***********************************
    // Run 1 - 1 year timestep
    //***********************************
    //Load our test file and get our tree population pointers
    p_oSimManager->ReadFile( WriteNCIJuvenileGrowthXMLFile3() );
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );

    //Create our trees
    fDiam = 7;
    iSpecies = 0;
    p_oTargetTree1 = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::sapling, fDiam);

    fDiam = 8;
    iSpecies = 1;
    p_oTargetTree2 = p_oPop->CreateTree(20, 20, iSpecies, clTreePopulation::sapling, fDiam);

    fDiam = 9;
    iSpecies = 3;
    p_oTargetTree3 = p_oPop->CreateTree(30, 30, iSpecies, clTreePopulation::sapling, fDiam);

    fDiam = 9.5;
    iSpecies = 0;
    p_oTargetTree4 = p_oPop->CreateTree(50, 50, iSpecies, clTreePopulation::sapling, fDiam);

    fDiam = 0.2;
    iSpecies = 0;
    p_oTargetTree5 = p_oPop->CreateTree(56, 56, iSpecies, clTreePopulation::seedling, fDiam);

    fDiam = 1.1;
    iSpecies = 0;
    p_oTargetTree6 = p_oPop->CreateTree(52, 52, iSpecies, clTreePopulation::seedling, fDiam);

    fDiam = 1.1;
    iSpecies = 1;
    p_oTargetTree7 = p_oPop->CreateTree(53, 53, iSpecies, clTreePopulation::seedling, fDiam);

    fDiam = 4;
    iSpecies = 3;
    p_oTargetTree8 = p_oPop->CreateTree(54, 54, iSpecies, clTreePopulation::sapling, fDiam);

    fDiam = 4;
    iSpecies = 3;
    p_oTargetTree9 = p_oPop->CreateTree(57, 57, iSpecies, clTreePopulation::sapling, fDiam);

    //Neighbors
    fDiam = 15;
    iSpecies = 1;
    p_oPop->CreateTree(53, 52, iSpecies, clTreePopulation::adult, fDiam);
    fDiam = 25;
    iSpecies = 3;
    p_oPop->CreateTree(59, 50, iSpecies, clTreePopulation::adult, fDiam);
    fDiam = 30;
    iSpecies = 0;
    p_oPop->CreateTree(50, 59, iSpecies, clTreePopulation::adult, fDiam);
    fDiam = 45;
    iSpecies = 1;
    p_oPop->CreateTree(55, 55, iSpecies, clTreePopulation::adult, fDiam);
    fDiam = 11;
    iSpecies = 0;
    p_oPop->CreateTree(57, 58, iSpecies, clTreePopulation::snag, fDiam);

    for (i = 0; i < 100; i++) {
      p_oTargetTree = p_oPop->CreateTree(58, 58, 1, clTreePopulation::adult, 20);
      p_oTargetTree->SetValue(p_oPop->GetIntDataCode("dead", p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), storm);
    }

    //Now do the run
    p_oSimManager->RunSim(1);

    //Check the diameters and growth of the target trees
    fExpectedDiam = 9.138567284;
    p_oTargetTree = p_oTargetTree1;
    p_oTargetTree->GetValue(p_oPop->GetDiam10Code(p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam), 0.01);

    fExpectedDiam = 11.3568165;
    p_oTargetTree = p_oTargetTree2;
    p_oTargetTree->GetValue(p_oPop->GetDiam10Code(p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam), 0.01);

    fExpectedDiam = 12.02238043;
    p_oTargetTree = p_oTargetTree3;
    p_oTargetTree->GetValue(p_oPop->GetDiam10Code(p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam), 0.01);

    fExpectedDiam = 12.06304149;
    p_oTargetTree = p_oTargetTree4;
    p_oTargetTree->GetValue(p_oPop->GetDiam10Code(p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam), 0.01);

    fExpectedDiam = 0.36481175;
    p_oTargetTree = p_oTargetTree5;
    p_oTargetTree->GetValue(p_oPop->GetDiam10Code(p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam), 0.01);

    fExpectedDiam = 1.279475968;
    p_oTargetTree = p_oTargetTree6;
    p_oTargetTree->GetValue(p_oPop->GetDiam10Code(p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam), 0.01);

    fExpectedDiam = 1.924116554;
    p_oTargetTree = p_oTargetTree7;
    p_oTargetTree->GetValue(p_oPop->GetDiam10Code(p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam), 0.01);

    fExpectedDiam = 5.478338098;
    p_oTargetTree = p_oTargetTree8;
    p_oTargetTree->GetValue(p_oPop->GetDiam10Code(p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam), 0.01);

    fExpectedDiam = 5.478338098;
    p_oTargetTree = p_oTargetTree9;
    p_oTargetTree->GetValue(p_oPop->GetDiam10Code(p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam), 0.01);

    //***********************************
    // Run 2 - 3 year timestep
    //***********************************
    //Load our test file and get our tree population pointers
    p_oSimManager->ReadFile( WriteNCIJuvenileGrowthXMLFile4() );
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );

    //Create our trees
    fDiam = 7;
    iSpecies = 0;
    p_oTargetTree1 = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::sapling, fDiam);

    fDiam = 8;
    iSpecies = 1;
    p_oTargetTree2 = p_oPop->CreateTree(20, 20, iSpecies, clTreePopulation::sapling, fDiam);

    fDiam = 9;
    iSpecies = 3;
    p_oTargetTree3 = p_oPop->CreateTree(30, 30, iSpecies, clTreePopulation::sapling, fDiam);

    fDiam = 9.5;
    iSpecies = 0;
    p_oTargetTree4 = p_oPop->CreateTree(50, 50, iSpecies, clTreePopulation::sapling, fDiam);

    fDiam = 0.2;
    iSpecies = 0;
    p_oTargetTree5 = p_oPop->CreateTree(56, 56, iSpecies, clTreePopulation::seedling, fDiam);

    fDiam = 1.1;
    iSpecies = 0;
    p_oTargetTree6 = p_oPop->CreateTree(52, 52, iSpecies, clTreePopulation::seedling, fDiam);

    fDiam = 1.1;
    iSpecies = 1;
    p_oTargetTree7 = p_oPop->CreateTree(53, 53, iSpecies, clTreePopulation::seedling, fDiam);

    fDiam = 4;
    iSpecies = 3;
    p_oTargetTree8 = p_oPop->CreateTree(54, 54, iSpecies, clTreePopulation::sapling, fDiam);

    fDiam = 4;
    iSpecies = 3;
    p_oTargetTree9 = p_oPop->CreateTree(57, 57, iSpecies, clTreePopulation::sapling, fDiam);

    //Neighbors
    fDiam = 15;
    iSpecies = 1;
    p_oPop->CreateTree(53, 52, iSpecies, clTreePopulation::adult, fDiam);
    fDiam = 25;
    iSpecies = 3;
    p_oPop->CreateTree(59, 50, iSpecies, clTreePopulation::adult, fDiam);
    fDiam = 30;
    iSpecies = 0;
    p_oPop->CreateTree(50, 59, iSpecies, clTreePopulation::adult, fDiam);
    fDiam = 45;
    iSpecies = 1;
    p_oPop->CreateTree(55, 55, iSpecies, clTreePopulation::adult, fDiam);
    fDiam = 11;
    iSpecies = 0;
    p_oPop->CreateTree(57, 58, iSpecies, clTreePopulation::snag, fDiam);

    for (i = 0; i < 100; i++) {
      p_oTargetTree = p_oPop->CreateTree(58, 58, 1, clTreePopulation::adult, 20);
      p_oTargetTree->SetValue(p_oPop->GetIntDataCode("dead", p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), storm);
    }

    //Now do the run
    p_oSimManager->RunSim(1);

    //Check the diameters and growth of the target trees
    fExpectedDiam = 9.9358024;
    p_oTargetTree = p_oTargetTree1;
    p_oTargetTree->GetValue(p_oPop->GetDiam10Code(p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam), 0.01);

    fExpectedDiam = 11.29320759; //note DBH
    p_oTargetTree = p_oTargetTree2;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam), 0.01);

    fExpectedDiam = 10.88432005; //note DBH
    p_oTargetTree = p_oTargetTree3;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam), 0.01);

    fExpectedDiam = 12.46334956;
    p_oTargetTree = p_oTargetTree4;
    p_oTargetTree->GetValue(p_oPop->GetDiam10Code(p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam), 0.01);

    fExpectedDiam = 0.707769002;
    p_oTargetTree = p_oTargetTree5;
    p_oTargetTree->GetValue(p_oPop->GetDiam10Code(p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam), 0.01);

    fExpectedDiam = 1.642350086;
    p_oTargetTree = p_oTargetTree6;
    p_oTargetTree->GetValue(p_oPop->GetDiam10Code(p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam), 0.01);

    fExpectedDiam = 3.601378255;
    p_oTargetTree = p_oTargetTree7;
    p_oTargetTree->GetValue(p_oPop->GetDiam10Code(p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam), 0.01);

    fExpectedDiam = 6.446842055;
    p_oTargetTree = p_oTargetTree8;
    p_oTargetTree->GetValue(p_oPop->GetDiam10Code(p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam), 0.01);

    fExpectedDiam = 6.446842055;
    p_oTargetTree = p_oTargetTree9;
    p_oTargetTree->GetValue(p_oPop->GetDiam10Code(p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam), 0.01);
    delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

////////////////////////////////////////////////////////////////////////////
// WriteNCIJuvenileGrowthXMLFile1()
////////////////////////////////////////////////////////////////////////////
const char* WriteNCIJuvenileGrowthXMLFile1() {
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

  WriteNCIJuvenileGrowthCommonStuff(oOut);
  WriteNCIJuvenileGrowthRunCommonStuff(oOut);

  oOut << "<nciMinNeighborDBH>"
       << "<nmndVal species=\"Species_1\">5</nmndVal>"
       << "<nmndVal species=\"Species_2\">5</nmndVal>"
       << "<nmndVal species=\"Species_3\">5</nmndVal>"
       << "<nmndVal species=\"Species_4\">5</nmndVal>"
       << "</nciMinNeighborDBH>"
       << "<nciDbhDivisor>100</nciDbhDivisor>"
       << "<nciIncludeSnagsInNCI>0</nciIncludeSnagsInNCI>"
       << "</NCIMasterGrowth1>"
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

////////////////////////////////////////////////////////////////////////////
// WriteNCIJuvenileGrowthXMLFile2()
////////////////////////////////////////////////////////////////////////////
const char* WriteNCIJuvenileGrowthXMLFile2() {
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

  WriteNCIJuvenileGrowthCommonStuff(oOut);
  WriteNCIJuvenileGrowthRunCommonStuff(oOut);

  oOut << "<nciMinNeighborDBH>"
       << "<nmndVal species=\"Species_1\">5</nmndVal>"
       << "<nmndVal species=\"Species_2\">5</nmndVal>"
       << "<nmndVal species=\"Species_3\">5</nmndVal>"
       << "<nmndVal species=\"Species_4\">5</nmndVal>"
       << "</nciMinNeighborDBH>"
       << "<nciDbhDivisor>100</nciDbhDivisor>"
       << "<nciIncludeSnagsInNCI>0</nciIncludeSnagsInNCI>"
       << "</NCIMasterGrowth1>"
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

////////////////////////////////////////////////////////////////////////////
// WriteNCIJuvenileGrowthXMLFile3()
////////////////////////////////////////////////////////////////////////////
const char* WriteNCIJuvenileGrowthXMLFile3() {
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

  WriteNCIJuvenileGrowthCommonStuff(oOut);
  WriteNCIJuvenileGrowthRunCommonStuff(oOut);

  oOut << "<nciMinNeighborDBH>"
       << "<nmndVal species=\"Species_1\">0</nmndVal>"
       << "<nmndVal species=\"Species_2\">0</nmndVal>"
       << "<nmndVal species=\"Species_3\">0</nmndVal>"
       << "<nmndVal species=\"Species_4\">0</nmndVal>"
       << "</nciMinNeighborDBH>"
       << "<nciDbhDivisor>100</nciDbhDivisor>"
       << "<nciIncludeSnagsInNCI>1</nciIncludeSnagsInNCI>"
       << "</NCIMasterGrowth1>"
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

////////////////////////////////////////////////////////////////////////////
// WriteNCIJuvenileGrowthXMLFile4()
////////////////////////////////////////////////////////////////////////////
const char* WriteNCIJuvenileGrowthXMLFile4() {
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

  WriteNCIJuvenileGrowthCommonStuff(oOut);
  WriteNCIJuvenileGrowthRunCommonStuff(oOut);

  oOut << "<nciMinNeighborDBH>"
       << "<nmndVal species=\"Species_1\">0</nmndVal>"
       << "<nmndVal species=\"Species_2\">0</nmndVal>"
       << "<nmndVal species=\"Species_3\">0</nmndVal>"
       << "<nmndVal species=\"Species_4\">0</nmndVal>"
       << "</nciMinNeighborDBH>"
       << "<nciDbhDivisor>100</nciDbhDivisor>"
       << "<nciIncludeSnagsInNCI>1</nciIncludeSnagsInNCI>"
       << "</NCIMasterGrowth1>"
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
// WriteNCIJuvenileGrowthCommonStuff()
/////////////////////////////////////////////////////////////////////////////
void WriteNCIJuvenileGrowthCommonStuff( std::fstream &oOut )
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
// WriteNCIJuvenileGrowthRunCommonStuff()
////////////////////////////////////////////////////////////////////////////
void WriteNCIJuvenileGrowthRunCommonStuff( std::fstream &oOut ) {

  using namespace std;
  //Write file
  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>NCIMasterGrowth</behaviorName>"
       << "<version>3</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Seedling\"/>"
       << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_2\" type=\"Seedling\"/>"
       << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_4\" type=\"Sapling\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>ConstRadialGrowth</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>2</listPosition>"
       << "<applyTo species=\"Species_4\" type=\"Seedling\"/>"
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
       << "<ConstRadialGrowth2>"
       << "<gr_adultConstRadialInc>"
       << "<gr_acriVal species=\"Species_4\">10</gr_acriVal>"
       << "</gr_adultConstRadialInc>"
       << "</ConstRadialGrowth2>"
       << "<NCIMasterGrowth1>"
       << "<nciWhichShadingEffect>" << no_shading << "</nciWhichShadingEffect>"
       << "<nciWhichCrowdingEffect>" << crowding_effect_no_size << "</nciWhichCrowdingEffect>"
       << "<nciWhichNCITerm>" << nci_with_seedlings << "</nciWhichNCITerm>"
       << "<nciWhichSizeEffect>" << size_effect_power_function << "</nciWhichSizeEffect>"
       << "<nciWhichDamageEffect>" << no_damage_effect << "</nciWhichDamageEffect>"
       << "<nciWhichPrecipitationEffect>" << no_precip_effect << "</nciWhichPrecipitationEffect>"
       << "<nciWhichTemperatureEffect>" << no_temp_effect << "</nciWhichTemperatureEffect>"
       << "<nciWhichNitrogenEffect>" << no_nitrogen_effect << "</nciWhichNitrogenEffect>"
       << "<nciWhichInfectionEffect>" << no_infection_effect << "</nciWhichInfectionEffect>"
       << "<gr_stochGrowthMethod>" << deterministic_pdf << "</gr_stochGrowthMethod>"
       << "<nciMaxCrowdingRadius>"
       << "<nmcrVal species=\"Species_1\">12</nmcrVal>"
       << "<nmcrVal species=\"Species_4\">12</nmcrVal>"
       << "<nmcrVal species=\"Species_2\">12</nmcrVal>"
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
       << "<nciSizeEffectA>"
       << "<nseaVal species=\"Species_1\">0.342463899</nseaVal>"
       << "<nseaVal species=\"Species_2\">0.85</nseaVal>"
       << "<nseaVal species=\"Species_4\">0.7643</nseaVal>"
       << "</nciSizeEffectA>"
       << "<nciSizeEffectB>"
       << "<nsebVal species=\"Species_1\">0.05</nsebVal>"
       << "<nsebVal species=\"Species_2\">0.0236</nsebVal>"
       << "<nsebVal species=\"Species_4\">0.0141</nsebVal>"
       << "</nciSizeEffectB>"
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
       << "</nciSpecies_4NeighborLambda>";

}

/////////////////////////////////////////////////////////////////////////////
// WriteNCIJuvenileGrowthErrorFileCommonStuff()
/////////////////////////////////////////////////////////////////////////////
void WriteNCIJuvenileGrowthErrorFileCommonStuff( std::fstream &oOut )
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

////////////////////////////////////////////////////////////////////////////
// WriteNCIJuvenileGrowthXMLErrorFile1()
////////////////////////////////////////////////////////////////////////////
const char* WriteNCIJuvenileGrowthXMLErrorFile1() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  WriteNCIJuvenileGrowthErrorFileCommonStuff(oOut);

  //Write file
  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>NCIMasterGrowth</behaviorName>"
       << "<version>3</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Seedling\"/>"
       << "<applyTo species=\"Species_2\" type=\"Seedling\"/>"
       << "</behavior>"
       << "</behaviorList>"
       << "<NCIMasterGrowth1>"
       << "<nciWhichShadingEffect>" << no_shading << "</nciWhichShadingEffect>"
       << "<nciWhichCrowdingEffect>" << crowding_effect_no_size << "</nciWhichCrowdingEffect>"
       << "<nciWhichNCITerm>" << nci_with_seedlings << "</nciWhichNCITerm>"
       << "<nciWhichSizeEffect>" << size_effect_power_function << "</nciWhichSizeEffect>"
       << "<nciWhichDamageEffect>" << no_damage_effect << "</nciWhichDamageEffect>"
       << "<nciWhichPrecipitationEffect>" << no_precip_effect << "</nciWhichPrecipitationEffect>"
       << "<nciWhichTemperatureEffect>" << no_temp_effect << "</nciWhichTemperatureEffect>"
       << "<nciWhichNitrogenEffect>" << no_nitrogen_effect << "</nciWhichNitrogenEffect>"
       << "<nciWhichInfectionEffect>" << no_infection_effect << "</nciWhichInfectionEffect>"
       << "<gr_stochGrowthMethod>" << deterministic_pdf << "</gr_stochGrowthMethod>"
       << "<nciMaxCrowdingRadius>"
       << "<nmcrVal species=\"Species_1\">-12</nmcrVal>"
       << "<nmcrVal species=\"Species_2\">12</nmcrVal>"
       << "</nciMaxCrowdingRadius>"
       << "<nciAlpha>"
       << "<naVal species=\"Species_1\">2.17031683</naVal>"
       << "<naVal species=\"Species_2\">2.81</naVal>"
       << "</nciAlpha>"
       << "<nciBeta>"
       << "<nbVal species=\"Species_1\">0.699942</nbVal>"
       << "<nbVal species=\"Species_2\">0.5</nbVal>"
       << "</nciBeta>"
       << "<gr_nciMaxPotentialGrowth>"
       << "<gr_nmpgVal species=\"Species_1\">1.05258749</gr_nmpgVal>"
       << "<gr_nmpgVal species=\"Species_2\">1.531</gr_nmpgVal>"
       << "</gr_nciMaxPotentialGrowth>"
       << "<nciSizeEffectA>"
       << "<nseaVal species=\"Species_1\">0.342463899</nseaVal>"
       << "<nseaVal species=\"Species_2\">0.85</nseaVal>"
       << "</nciSizeEffectA>"
       << "<nciSizeEffectB>"
       << "<nsebVal species=\"Species_1\">0.05</nsebVal>"
       << "<nsebVal species=\"Species_2\">0.0236</nsebVal>"
       << "</nciSizeEffectB>"
       << "<nciCrowdingC>"
       << "<nccVal species=\"Species_1\">0.698</nccVal>"
       << "<nccVal species=\"Species_2\">0.457</nccVal>"
       << "</nciCrowdingC>"
       << "<nciCrowdingD>"
       << "<ncdVal species=\"Species_1\">-0.00163</ncdVal>"
       << "<ncdVal species=\"Species_2\">-0.00126</ncdVal>"
       << "</nciCrowdingD>"
       << "<nciSpecies_1NeighborLambda>"
       << "<nlVal species=\"Species_1\">0.66401082</nlVal>"
       << "<nlVal species=\"Species_2\">0.71</nlVal>"
       << "</nciSpecies_1NeighborLambda>"
       << "<nciSpecies_2NeighborLambda>"
       << "<nlVal species=\"Species_1\">0.00442797</nlVal>"
       << "<nlVal species=\"Species_2\">0.12</nlVal>"
       << "</nciSpecies_2NeighborLambda>"
       << "<nciMinNeighborDBH>"
       << "<nmndVal species=\"Species_1\">5</nmndVal>"
       << "<nmndVal species=\"Species_2\">5</nmndVal>"
       << "</nciMinNeighborDBH>"
       << "<nciDbhDivisor>100</nciDbhDivisor>"
       << "<nciIncludeSnagsInNCI>0</nciIncludeSnagsInNCI>"
       << "</NCIMasterGrowth1>"
       << "</paramFile>";


  oOut.close();

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteNCIJuvenileGrowthXMLErrorFile2()
////////////////////////////////////////////////////////////////////////////
const char* WriteNCIJuvenileGrowthXMLErrorFile2() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  WriteNCIJuvenileGrowthErrorFileCommonStuff(oOut);

  //Write file
  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>NCIMasterGrowth</behaviorName>"
       << "<version>3</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Seedling\"/>"
       << "<applyTo species=\"Species_2\" type=\"Seedling\"/>"
       << "</behavior>"
       << "</behaviorList>"
       << "<NCIMasterGrowth1>"
       << "<nciWhichShadingEffect>" << no_shading << "</nciWhichShadingEffect>"
       << "<nciWhichCrowdingEffect>" << crowding_effect_no_size << "</nciWhichCrowdingEffect>"
       << "<nciWhichNCITerm>" << nci_with_seedlings << "</nciWhichNCITerm>"
       << "<nciWhichSizeEffect>" << size_effect_power_function << "</nciWhichSizeEffect>"
       << "<nciWhichDamageEffect>" << no_damage_effect << "</nciWhichDamageEffect>"
       << "<nciWhichPrecipitationEffect>" << no_precip_effect << "</nciWhichPrecipitationEffect>"
       << "<nciWhichTemperatureEffect>" << no_temp_effect << "</nciWhichTemperatureEffect>"
       << "<nciWhichNitrogenEffect>" << no_nitrogen_effect << "</nciWhichNitrogenEffect>"
       << "<nciWhichInfectionEffect>" << no_infection_effect << "</nciWhichInfectionEffect>"
       << "<gr_stochGrowthMethod>" << deterministic_pdf << "</gr_stochGrowthMethod>"
       << "<nciMaxCrowdingRadius>"
       << "<nmcrVal species=\"Species_1\">12</nmcrVal>"
       << "<nmcrVal species=\"Species_2\">12</nmcrVal>"
       << "</nciMaxCrowdingRadius>"
       << "<nciAlpha>"
       << "<naVal species=\"Species_1\">2.17031683</naVal>"
       << "<naVal species=\"Species_2\">2.81</naVal>"
       << "</nciAlpha>"
       << "<nciBeta>"
       << "<nbVal species=\"Species_1\">0.699942</nbVal>"
       << "<nbVal species=\"Species_2\">0.5</nbVal>"
       << "</nciBeta>"
       << "<gr_nciMaxPotentialGrowth>"
       << "<gr_nmpgVal species=\"Species_1\">1.05258749</gr_nmpgVal>"
       << "<gr_nmpgVal species=\"Species_2\">1.531</gr_nmpgVal>"
       << "</gr_nciMaxPotentialGrowth>"
       << "<nciSizeEffectA>"
       << "<nseaVal species=\"Species_1\">0.342463899</nseaVal>"
       << "<nseaVal species=\"Species_2\">0.85</nseaVal>"
       << "</nciSizeEffectA>"
       << "<nciSizeEffectB>"
       << "<nsebVal species=\"Species_1\">0.05</nsebVal>"
       << "<nsebVal species=\"Species_2\">0.0236</nsebVal>"
       << "</nciSizeEffectB>"
       << "<nciCrowdingC>"
       << "<nccVal species=\"Species_1\">0.698</nccVal>"
       << "<nccVal species=\"Species_2\">0.457</nccVal>"
       << "</nciCrowdingC>"
       << "<nciCrowdingD>"
       << "<ncdVal species=\"Species_1\">-0.00163</ncdVal>"
       << "<ncdVal species=\"Species_2\">-0.00126</ncdVal>"
       << "</nciCrowdingD>"
       << "<nciSpecies_1NeighborLambda>"
       << "<nlVal species=\"Species_1\">0.66401082</nlVal>"
       << "<nlVal species=\"Species_2\">0.71</nlVal>"
       << "</nciSpecies_1NeighborLambda>"
       << "<nciSpecies_2NeighborLambda>"
       << "<nlVal species=\"Species_1\">0.00442797</nlVal>"
       << "<nlVal species=\"Species_2\">0.12</nlVal>"
       << "</nciSpecies_2NeighborLambda>"
       << "<nciMinNeighborDBH>"
       << "<nmndVal species=\"Species_1\">-5</nmndVal>"
       << "<nmndVal species=\"Species_2\">5</nmndVal>"
       << "</nciMinNeighborDBH>"
       << "<nciDbhDivisor>100</nciDbhDivisor>"
       << "<nciIncludeSnagsInNCI>0</nciIncludeSnagsInNCI>"
       << "</NCIMasterGrowth1>"
       << "</paramFile>";


  oOut.close();

  return cFileString;
}
