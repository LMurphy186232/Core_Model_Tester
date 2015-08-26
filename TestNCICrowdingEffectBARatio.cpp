//---------------------------------------------------------------------------
// TestNCICrowdingEffectBARatio.cpp
//---------------------------------------------------------------------------
#include "TestNCICrowdingEffectBARatio.h"
#include <gtest/gtest.h>
#include <fstream>
#include <math.h>
#include "TreePopulation.h"
#include "SimManager.h"
#include "BehaviorBase.h"
#include "DataTypes.h"
#include "NCIEffectsList.h"
#include "NCI/PrecipitationEffectBase.h"

using namespace std;

////////////////////////////////////////////////////////////////////////////
// TestRun1()
////////////////////////////////////////////////////////////////////////////
TEST(NCICrowdingEffectBARatio, TestRun1) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    clTreePopulation * p_oPop;
    clTree *p_oTargetTree1, *p_oTargetTree2, *p_oTargetTree3, *p_oTargetTree4,
    *p_oTargetTree5, *p_oTargetTree6, *p_oTargetTree7, *p_oTargetTree8,
    *p_oTargetTree9, *p_oTargetTree;
    float fDiam, fExpectedDiam;
    int iSpecies;

    //Load our test file and get our tree population pointers
    p_oSimManager->ReadFile(WriteNCIXMLFile1());
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

    //Now do the run
    p_oSimManager->RunSim(1);

    //Check the diameters and growth of the target trees
    fExpectedDiam = 11.2574;
    p_oTargetTree = p_oTargetTree1;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);

    fExpectedDiam = 10.68381213;
    p_oTargetTree = p_oTargetTree2;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);

    fExpectedDiam = 23.56658574;
    p_oTargetTree = p_oTargetTree3;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);

    fExpectedDiam = 29.54537773;
    p_oTargetTree = p_oTargetTree4;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);

    fExpectedDiam = 30.18284113;
    p_oTargetTree = p_oTargetTree5;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);

    fExpectedDiam = 54.33842326;
    p_oTargetTree = p_oTargetTree6;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);

    fExpectedDiam = 18.68450925;
    p_oTargetTree = p_oTargetTree7;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);

    fExpectedDiam = 4.197958073;
    p_oTargetTree = p_oTargetTree8;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);

    fExpectedDiam = 11.8868969;
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
TEST(NCICrowdingEffectBARatio, TestRun2) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    clTreePopulation * p_oPop;
    clTree *p_oTargetTree1, *p_oTargetTree2, *p_oTargetTree3, *p_oTargetTree4,
    *p_oTargetTree5, *p_oTargetTree6, *p_oTargetTree7, *p_oTargetTree8,
    *p_oTargetTree9, *p_oTargetTree;
    float fDiam, fExpectedDiam;
    int iSpecies;

    //Load our test file and get our tree population pointers
    p_oSimManager->ReadFile(WriteNCIXMLFile2());
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

    //Now do the run
    p_oSimManager->RunSim(1);

    //Check the diameters and growth of the target trees
    fExpectedDiam = 11.7722;
    p_oTargetTree = p_oTargetTree1;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);

    fExpectedDiam = 11.05143638;
    p_oTargetTree = p_oTargetTree2;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);

    fExpectedDiam = 40.69975721;
    p_oTargetTree = p_oTargetTree3;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);

    fExpectedDiam = 38.63613319;
    p_oTargetTree = p_oTargetTree4;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);

    fExpectedDiam = 30.54852339;
    p_oTargetTree = p_oTargetTree5;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);

    fExpectedDiam = 73.01526978;
    p_oTargetTree = p_oTargetTree6;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);

    fExpectedDiam = 26.05352775;
    p_oTargetTree = p_oTargetTree7;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);

    fExpectedDiam = 4.59387422;
    p_oTargetTree = p_oTargetTree8;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);

    fExpectedDiam = 27.6606907;
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
// Performs a test run of BA ratio with seedlings in NCI quadrat growth.
////////////////////////////////////////////////////////////////////////////
TEST(NCICrowdingEffectBARatio, TestRun3) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    clTreePopulation * p_oPop;
    clTree *p_oTargetTree1, *p_oTargetTree2, *p_oTargetTree3, *p_oTargetTree4,
    *p_oTargetTree5, *p_oTargetTree6, *p_oTargetTree7, *p_oTargetTree8, *p_oTargetTree;
    float fDiam, fExpectedDiam;
    int iSpecies;

    //Load our test file and get our tree population pointers
    p_oSimManager->ReadFile(WriteNCIXMLFile3());
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

    fDiam = 1.2;
    iSpecies = 1;
    p_oTargetTree6 = p_oPop->CreateTree(51, 53, iSpecies,
        clTreePopulation::seedling, fDiam);

    fDiam = 1.3;
    iSpecies = 2;
    p_oTargetTree7 = p_oPop->CreateTree(51.2, 54, iSpecies,
        clTreePopulation::seedling, fDiam);

    fDiam = 1.4;
    iSpecies = 3;
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

    //Now do the run
    p_oSimManager->RunSim(1);

    //Check the diameters and growth of the target trees
    fExpectedDiam = 3.011758274;
    p_oTargetTree = p_oTargetTree1;
    p_oTargetTree->GetValue(p_oPop->GetDiam10Code(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);

    fExpectedDiam = 3.111758274;
    p_oTargetTree = p_oTargetTree2;
    p_oTargetTree->GetValue(p_oPop->GetDiam10Code(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);

    fExpectedDiam = 2.177103935;
    p_oTargetTree = p_oTargetTree3;
    p_oTargetTree->GetValue(p_oPop->GetDiam10Code(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);

    fExpectedDiam = 6.119786145;
    p_oTargetTree = p_oTargetTree4;
    p_oTargetTree->GetValue(p_oPop->GetDiam10Code(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);

    fExpectedDiam = 3.9;
    p_oTargetTree = p_oTargetTree5;
    p_oTargetTree->GetValue(p_oPop->GetDiam10Code(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);

    fExpectedDiam = 3.711758274;
    p_oTargetTree = p_oTargetTree6;
    p_oTargetTree->GetValue(p_oPop->GetDiam10Code(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);

    fExpectedDiam = 2.746263913;
    p_oTargetTree = p_oTargetTree7;
    p_oTargetTree->GetValue(p_oPop->GetDiam10Code(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);

    fExpectedDiam = 6.736039506;
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
// WriteNCIXMLFile1()
////////////////////////////////////////////////////////////////////////////
const char* WriteNCIXMLFile1() {
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
       << "<plot_precip_mm_yr>115</plot_precip_mm_yr>"
       << "<plot_temp_C>12.88</plot_temp_C>"
       << "<plot_n_dep>4.76</plot_n_dep>"
       << "<plot_seasonal_precipitation>1150.65</plot_seasonal_precipitation>"
       << "<plot_water_deficit>456.2</plot_water_deficit>"
       << "</plot>";

  WriteNCITreeStuff(oOut);
  WriteNCICommonStuff(oOut);

  oOut.close();

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteNCIXMLFile2()
////////////////////////////////////////////////////////////////////////////
const char* WriteNCIXMLFile2() {
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
       << "<plot_precip_mm_yr>115</plot_precip_mm_yr>"
       << "<plot_temp_C>12.88</plot_temp_C>"
       << "<plot_n_dep>4.76</plot_n_dep>"
       << "<plot_seasonal_precipitation>1150.65</plot_seasonal_precipitation>"
       << "<plot_water_deficit>456.2</plot_water_deficit>"
       << "</plot>";

  WriteNCITreeStuff(oOut);
  WriteNCICommonStuff(oOut);

  oOut.close();

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteNCIXMLFile3()
////////////////////////////////////////////////////////////////////////////
const char* WriteNCIXMLFile3() {
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

  WriteNCITreeStuff(oOut);

  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>NCIMasterQuadratGrowth</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_3\" type=\"Seedling\"/>"
       << "<applyTo species=\"Species_2\" type=\"Seedling\"/>"
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
       << "<nciWhichCrowdingEffect>" << default_crowding_effect << "</nciWhichCrowdingEffect>"
       << "<nciWhichNCITerm>" << nci_ba_ratio_dbh_default << "</nciWhichNCITerm>"
       << "<nciWhichSizeEffect>" << no_size_effect << "</nciWhichSizeEffect>"
       << "<nciWhichDamageEffect>" << no_damage_effect << "</nciWhichDamageEffect>"
       << "<nciWhichPrecipitationEffect>" << no_precip_effect << "</nciWhichPrecipitationEffect>"
       << "<nciWhichTemperatureEffect>" << no_temp_effect << "</nciWhichTemperatureEffect>"
       << "<nciWhichNitrogenEffect>" << no_nitrogen_effect << "</nciWhichNitrogenEffect>"
       << "<nciWhichInfectionEffect>" << no_infection_effect << "</nciWhichInfectionEffect>"
       << "<gr_stochGrowthMethod>" << deterministic_pdf << "</gr_stochGrowthMethod>"
       << "<gr_nciMaxPotentialGrowth>"
       << "<gr_nmpgVal species=\"Species_2\">3</gr_nmpgVal>"
       << "<gr_nmpgVal species=\"Species_3\">2</gr_nmpgVal>"
       << "<gr_nmpgVal species=\"Species_4\">5.4</gr_nmpgVal>"
       << "</gr_nciMaxPotentialGrowth>"
       << "<nciMaxAdultCrowdingRadius>10</nciMaxAdultCrowdingRadius>"
       << "<nciMaxSaplingCrowdingRadius>5</nciMaxSaplingCrowdingRadius>"
       << "<nciBADefaultDBH>1</nciBADefaultDBH>"
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
       << "<ncgVal species=\"Species_4\">-0.41</ncgVal>"
       << "</nciCrowdingGamma>"
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
// WriteNCITreeStuff()
/////////////////////////////////////////////////////////////////////////////
void WriteNCITreeStuff(std::fstream &oOut) {
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

/////////////////////////////////////////////////////////////////////////////
// WriteNCICommonStuff()
/////////////////////////////////////////////////////////////////////////////
void WriteNCICommonStuff(std::fstream &oOut) {
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
       << "<nciWhichNCITerm>" << nci_ba_ratio << "</nciWhichNCITerm>"
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
       << "<nciMaxAdultCrowdingRadius>"
       << "<nmacrVal species=\"Species_2\">10</nmacrVal>"
       << "<nmacrVal species=\"Species_3\">11</nmacrVal>"
       << "<nmacrVal species=\"Species_4\">12</nmacrVal>"
       << "</nciMaxAdultCrowdingRadius>"
       << "<nciMaxSaplingCrowdingRadius>"
       << "<nmscrVal species=\"Species_2\">4</nmscrVal>"
       << "<nmscrVal species=\"Species_3\">4</nmscrVal>"
       << "<nmscrVal species=\"Species_4\">4</nmscrVal>"
       << "</nciMaxSaplingCrowdingRadius>"
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
       << "</NCIMasterGrowth1>"
       << "</paramFile>";

}
