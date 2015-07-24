//---------------------------------------------------------------------------
// TestSuppressionDurationMort.cpp
//---------------------------------------------------------------------------
#include "TestSuppressionDurationMort.h"
#include <gtest/gtest.h>
#include "SimManager.h"
#include "TreePopulation.h"
#include "Grid.h"
#include "BehaviorBase.h"
#include <fstream>
#include <math.h>

/////////////////////////////////////////////////////////////////////////////
// NormalProcessingRun1()
// Tests normal processing run 1. WriteSuppressionDurationMortXMLFile1() does
// setup.
/////////////////////////////////////////////////////////////////////////////
TEST(SuppressionDurationMort, NormalProcessingRun1) {
  clTreePopulation * p_oPop;
  clTreeSearch *p_oAllTrees;
  clTree *p_oTree;
  float fDiam, fX, fY, fExpected;
  int *p_iNumTrees = new int[3];
  int i, iSpecies, iAge, iYr;

  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {

    p_oSimManager->ReadFile(WriteSuppressionDurationMortXMLFile1());
    p_oPop = (clTreePopulation *) p_oSimManager->GetPopulationObject("treepopulation");

    //Add 1000 trees to the plot of each kind
    fDiam = 20;
    for (i = 0; i < 1000; i++) {
      iAge = 0;
      for (iSpecies = 0; iSpecies < 3; iSpecies++) {
        fX = clModelMath::GetRand() * 100;
        fY = clModelMath::GetRand() * 100;
        p_oTree = p_oPop->CreateTree(fX, fY, iSpecies, clTreePopulation::adult, fDiam);
        p_oTree->SetValue(p_oPop->GetIntDataCode("Tree Age", p_oTree->GetSpecies(), p_oTree->GetType()), iAge);
      }

      iAge = 1;
      for (iSpecies = 0; iSpecies < 3; iSpecies++) {
        fX = clModelMath::GetRand() * 100;
        fY = clModelMath::GetRand() * 100;
        p_oTree = p_oPop->CreateTree(fX, fY, iSpecies, clTreePopulation::adult, fDiam);
        p_oTree->SetValue(p_oPop->GetIntDataCode("Tree Age", p_oTree->GetSpecies(), p_oTree->GetType()), iAge);
      }

      iAge = 5;
      for (iSpecies = 0; iSpecies < 3; iSpecies++) {
        fX = clModelMath::GetRand() * 100;
        fY = clModelMath::GetRand() * 100;
        p_oTree = p_oPop->CreateTree(fX, fY, iSpecies, clTreePopulation::adult, fDiam);
        p_oTree->SetValue(p_oPop->GetIntDataCode("Tree Age", p_oTree->GetSpecies(), p_oTree->GetType()), iAge);
      }

      iAge = 10;
      for (iSpecies = 0; iSpecies < 3; iSpecies++) {
        fX = clModelMath::GetRand() * 100;
        fY = clModelMath::GetRand() * 100;
        p_oTree = p_oPop->CreateTree(fX, fY, iSpecies, clTreePopulation::adult, fDiam);
        p_oTree->SetValue(p_oPop->GetIntDataCode("Tree Age", p_oTree->GetSpecies(), p_oTree->GetType()), iAge);
      }

      iAge = 20;
      for (iSpecies = 0; iSpecies < 3; iSpecies++) {
        fX = clModelMath::GetRand() * 100;
        fY = clModelMath::GetRand() * 100;
        p_oTree = p_oPop->CreateTree(fX, fY, iSpecies, clTreePopulation::adult, fDiam);
        p_oTree->SetValue(p_oPop->GetIntDataCode("Tree Age", p_oTree->GetSpecies(), p_oTree->GetType()), iAge);
      }

      iAge = 50;
      for (iSpecies = 0; iSpecies < 3; iSpecies++) {
        fX = clModelMath::GetRand() * 100;
        fY = clModelMath::GetRand() * 100;
        p_oTree = p_oPop->CreateTree(fX, fY, iSpecies, clTreePopulation::adult, fDiam);
        p_oTree->SetValue(p_oPop->GetIntDataCode("Tree Age", p_oTree->GetSpecies(), p_oTree->GetType()), iAge);
      }

      iAge = 10000;
      for (iSpecies = 0; iSpecies < 3; iSpecies++) {
        fX = clModelMath::GetRand() * 100;
        fY = clModelMath::GetRand() * 100;
        p_oTree = p_oPop->CreateTree(fX, fY, iSpecies, clTreePopulation::adult, fDiam);
        p_oTree->SetValue(p_oPop->GetIntDataCode("Tree Age", p_oTree->GetSpecies(), p_oTree->GetType()), iAge);
      }
    }


    //Run a timestep
    p_oSimManager->RunSim(1);

    //Count up the trees for each year
    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();

    iYr = 0;
    for (i = 0; i < 3; i++) p_iNumTrees[i] = 0;
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {
      p_oTree->GetValue(p_oPop->GetIntDataCode("Tree Age", p_oTree->GetSpecies(), p_oTree->GetType()), &iAge);
      if (iAge-1 == iYr)
        p_iNumTrees[p_oTree->GetSpecies()]++;

      p_oTree = p_oAllTrees->NextTree();
    }
    EXPECT_EQ(1000, p_iNumTrees[0]);
    EXPECT_EQ(1000, p_iNumTrees[1]);
    EXPECT_EQ(1000, p_iNumTrees[2]);




    p_oAllTrees->StartOver();
    iYr = 1;
    for (i = 0; i < 3; i++) p_iNumTrees[i] = 0;
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {
      p_oTree->GetValue(p_oPop->GetIntDataCode("Tree Age", p_oTree->GetSpecies(), p_oTree->GetType()), &iAge);
      if (iAge-1 == iYr)
        p_iNumTrees[p_oTree->GetSpecies()]++;

      p_oTree = p_oAllTrees->NextTree();
    }
    EXPECT_GT(p_iNumTrees[0], 990);
    EXPECT_EQ(1000, p_iNumTrees[1]);
    fExpected = 833.3333333;
    EXPECT_LT(fabs(p_iNumTrees[2] - fExpected)/fExpected, 0.05);



    p_oAllTrees->StartOver();
    iYr = 5;
    for (i = 0; i < 3; i++) p_iNumTrees[i] = 0;
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {
      p_oTree->GetValue(p_oPop->GetIntDataCode("Tree Age", p_oTree->GetSpecies(), p_oTree->GetType()), &iAge);
      if (iAge-1 == iYr)
        p_iNumTrees[p_oTree->GetSpecies()]++;

      p_oTree = p_oAllTrees->NextTree();
    }
    fExpected = 996.1538462;
    EXPECT_GT(p_iNumTrees[0], 980);
    EXPECT_EQ(1000, p_iNumTrees[1]);
    fExpected = 500;
    EXPECT_LT(fabs(p_iNumTrees[2] - fExpected)/fExpected, 0.10);



    p_oAllTrees->StartOver();
    iYr = 10;
    for (i = 0; i < 3; i++) p_iNumTrees[i] = 0;
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {
      p_oTree->GetValue(p_oPop->GetIntDataCode("Tree Age", p_oTree->GetSpecies(), p_oTree->GetType()), &iAge);
      if (iAge-1 == iYr)
        p_iNumTrees[p_oTree->GetSpecies()]++;

      p_oTree = p_oAllTrees->NextTree();
    }
    fExpected = 972.2222222;
    EXPECT_LT(fabs(p_iNumTrees[0] - fExpected)/fExpected, 0.05);
    EXPECT_EQ(1000, p_iNumTrees[1]);
    fExpected = 333.3333333;
    EXPECT_LT(fabs(p_iNumTrees[2] - fExpected)/fExpected, 0.05);



    p_oAllTrees->StartOver();
    iYr = 20;
    for (i = 0; i < 3; i++) p_iNumTrees[i] = 0;
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {
      p_oTree->GetValue(p_oPop->GetIntDataCode("Tree Age", p_oTree->GetSpecies(), p_oTree->GetType()), &iAge);
      if (iAge-1 == iYr)
        p_iNumTrees[p_oTree->GetSpecies()]++;

      p_oTree = p_oAllTrees->NextTree();
    }
    fExpected = 875;
    EXPECT_LT(fabs(p_iNumTrees[0] - fExpected)/fExpected, 0.05);
    EXPECT_EQ(1000, p_iNumTrees[1]);
    fExpected = 200;
    EXPECT_LT(fabs(p_iNumTrees[2] - fExpected)/fExpected, 0.05);


    p_oAllTrees->StartOver();
    iYr = 50;
    for (i = 0; i < 3; i++) p_iNumTrees[i] = 0;
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {
      p_oTree->GetValue(p_oPop->GetIntDataCode("Tree Age", p_oTree->GetSpecies(), p_oTree->GetType()), &iAge);
      if (iAge-1 == iYr)
        p_iNumTrees[p_oTree->GetSpecies()]++;

      p_oTree = p_oAllTrees->NextTree();
    }
    fExpected = 765.037594;
    EXPECT_LT(fabs(p_iNumTrees[0] - fExpected)/fExpected, 0.05);
    EXPECT_EQ(1000, p_iNumTrees[1]);
    fExpected = 90.90909091;
    EXPECT_LT(fabs(p_iNumTrees[2] - fExpected)/fExpected, 0.05);


    p_oAllTrees->StartOver();
    iYr = 10000;
    for (i = 0; i < 3; i++) p_iNumTrees[i] = 0;
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {
      p_oTree->GetValue(p_oPop->GetIntDataCode("Tree Age", p_oTree->GetSpecies(), p_oTree->GetType()), &iAge);
      if (iAge-1 == iYr)
        p_iNumTrees[p_oTree->GetSpecies()]++;

      p_oTree = p_oAllTrees->NextTree();
    }
    EXPECT_EQ(1000, p_iNumTrees[0]);
    EXPECT_EQ(1000, p_iNumTrees[1]);
    EXPECT_EQ(1000, p_iNumTrees[2]);


    delete[] p_iNumTrees;
    delete p_oSimManager;
  } catch (modelErr &e) {
    delete[] p_iNumTrees;
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}


////////////////////////////////////////////////////////////////////////////
// ErrorProcessing()
////////////////////////////////////////////////////////////////////////////
TEST(SuppressionDurationMort, ErrorProcessing)
{
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try
  {
    p_oSimManager->ReadFile( WriteSuppressionDurationMortXMLErrorFile1() );
    FAIL() << "TestSuppressionDurationMort error processing didn't catch error for WriteSuppressionDurationMortXMLErrorFile1.";
  }
  catch ( modelErr& err )
  {
    if ( err.sFunction.compare("clSuppressionDurationMort::DoShellSetup" ) != 0 )
    {
      FAIL() << "TestSuppressionDurationMort error processing caught wrong error for WriteSuppressionDurationMortXMLErrorFile1.";
    }
    ;
  }

  try
  {
    p_oSimManager->ReadFile( WriteSuppressionDurationMortXMLErrorFile2() );
    FAIL() << "TestSuppressionDurationMort error processing didn't catch error for WriteSuppressionDurationMortXMLErrorFile2.";
  }
  catch ( modelErr& err )
  {
    if ( err.sFunction.compare("clSuppressionDurationMort::DoShellSetup" ) != 0 )
    {
      FAIL() << "TestSuppressionDurationMort error processing caught wrong error for WriteSuppressionDurationMortXMLErrorFile2.";
    }
    ;
  }
  try
  {
    p_oSimManager->ReadFile( WriteSuppressionDurationMortXMLErrorFile3() );
    FAIL() << "TestSuppressionDurationMort error processing didn't catch error for WriteSuppressionDurationMortXMLErrorFile3.";
  }
  catch ( modelErr& err )
  {
    if ( err.sFunction.compare("clSuppressionDurationMort::DoShellSetup" ) != 0 )
    {
      FAIL() << "TestSuppressionDurationMort error processing caught wrong error for WriteSuppressionDurationMortXMLErrorFile3.";
    }
    ;
  }
  delete p_oSimManager;
}

////////////////////////////////////////////////////////////////////////////
// WriteSuppressionDurationMortXMLFile1()
////////////////////////////////////////////////////////////////////////////
const char* WriteSuppressionDurationMortXMLFile1() {
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

  oOut << "<randomSeed>1</randomSeed>"
       << "<plot_lenX>100</plot_lenX>"
       << "<plot_lenY>100</plot_lenY>"
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
       << "<tr_conversionDiam10ToDBH>"
       << "<tr_cdtdVal species=\"Species_1\">1</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_2\">1</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_3\">1</tr_cdtdVal>"
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
       << "</allometry>";

  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>SuppressionDurationMortality</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>RemoveDead</behaviorName>"
       << "<version>2</version>"
       << "<listPosition>2</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>TreeAgeCalculator</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>3</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
       << "</behavior>"
       << "</behaviorList>";

  oOut << "<SuppressionDurationMortality1>"
       << "<mo_suppDurMaxMort>"
       << "<mo_sdmmVal species=\"Species_1\">0.25</mo_sdmmVal>"
       << "<mo_sdmmVal species=\"Species_3\">1</mo_sdmmVal>"
       << "</mo_suppDurMaxMort>"
       << "<mo_suppDurMortX0>"
       << "<mo_sdmx0Val species=\"Species_1\">20</mo_sdmx0Val>"
       << "<mo_sdmx0Val species=\"Species_3\">5</mo_sdmx0Val>"
       << "</mo_suppDurMortX0>"
       << "<mo_suppDurMortXb>"
       << "<mo_sdmxbVal species=\"Species_1\">-3</mo_sdmxbVal>"
       << "<mo_sdmxbVal species=\"Species_3\">-1</mo_sdmxbVal>"
       << "</mo_suppDurMortXb>"
       << "</SuppressionDurationMortality1>";

  oOut << "</paramFile>";

  oOut.close();

  return cFileString;
}



////////////////////////////////////////////////////////////////////////////
// WriteSuppressionDurationMortXMLErrorFile1()
////////////////////////////////////////////////////////////////////////////
const char* WriteSuppressionDurationMortXMLErrorFile1() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  //Write file
  WriteSuppressionDurationMortErrorCommonStuff(oOut);

  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>SuppressionDurationMortality</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>RemoveDead</behaviorName>"
       << "<version>2</version>"
       << "<listPosition>2</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>TreeAgeCalculator</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>3</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "</behavior>"
       << "</behaviorList>";

  oOut << "<SuppressionDurationMortality1>"
       << "<mo_suppDurMaxMort>"
       << "<mo_sdmmVal species=\"Species_1\">1.25</mo_sdmmVal>"
       << "<mo_sdmmVal species=\"Species_2\">1</mo_sdmmVal>"
       << "</mo_suppDurMaxMort>"
       << "<mo_suppDurMortX0>"
       << "<mo_sdmx0Val species=\"Species_1\">20</mo_sdmx0Val>"
       << "<mo_sdmx0Val species=\"Species_2\">5</mo_sdmx0Val>"
       << "</mo_suppDurMortX0>"
       << "<mo_suppDurMortXb>"
       << "<mo_sdmxbVal species=\"Species_1\">-3</mo_sdmxbVal>"
       << "<mo_sdmxbVal species=\"Species_2\">-1</mo_sdmxbVal>"
       << "</mo_suppDurMortXb>"
       << "</SuppressionDurationMortality1>";

  oOut << "</paramFile>";

  oOut.close();

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteSuppressionDurationMortXMLErrorFile2()
////////////////////////////////////////////////////////////////////////////
const char* WriteSuppressionDurationMortXMLErrorFile2() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  //Write file
  WriteSuppressionDurationMortErrorCommonStuff(oOut);

  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>SuppressionDurationMortality</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>RemoveDead</behaviorName>"
       << "<version>2</version>"
       << "<listPosition>2</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "</behavior>"
       << "</behaviorList>";

  oOut << "<SuppressionDurationMortality1>"
       << "<mo_suppDurMaxMort>"
       << "<mo_sdmmVal species=\"Species_1\">0.25</mo_sdmmVal>"
       << "<mo_sdmmVal species=\"Species_2\">1</mo_sdmmVal>"
       << "</mo_suppDurMaxMort>"
       << "<mo_suppDurMortX0>"
       << "<mo_sdmx0Val species=\"Species_1\">20</mo_sdmx0Val>"
       << "<mo_sdmx0Val species=\"Species_2\">5</mo_sdmx0Val>"
       << "</mo_suppDurMortX0>"
       << "<mo_suppDurMortXb>"
       << "<mo_sdmxbVal species=\"Species_1\">-3</mo_sdmxbVal>"
       << "<mo_sdmxbVal species=\"Species_2\">-1</mo_sdmxbVal>"
       << "</mo_suppDurMortXb>"
       << "</SuppressionDurationMortality1>";

  oOut << "</paramFile>";

  oOut.close();

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteSuppressionDurationMortXMLErrorFile3()
////////////////////////////////////////////////////////////////////////////
const char* WriteSuppressionDurationMortXMLErrorFile3() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  //Write file
  WriteSuppressionDurationMortErrorCommonStuff(oOut);

  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>SuppressionDurationMortality</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>RemoveDead</behaviorName>"
       << "<version>2</version>"
       << "<listPosition>2</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>TreeAgeCalculator</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>3</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "</behavior>"
       << "</behaviorList>";

  oOut << "<SuppressionDurationMortality1>"
       << "<mo_suppDurMaxMort>"
       << "<mo_sdmmVal species=\"Species_1\">0.25</mo_sdmmVal>"
       << "<mo_sdmmVal species=\"Species_2\">1</mo_sdmmVal>"
       << "</mo_suppDurMaxMort>"
       << "<mo_suppDurMortX0>"
       << "<mo_sdmx0Val species=\"Species_1\">0</mo_sdmx0Val>"
       << "<mo_sdmx0Val species=\"Species_2\">5</mo_sdmx0Val>"
       << "</mo_suppDurMortX0>"
       << "<mo_suppDurMortXb>"
       << "<mo_sdmxbVal species=\"Species_1\">-3</mo_sdmxbVal>"
       << "<mo_sdmxbVal species=\"Species_2\">-1</mo_sdmxbVal>"
       << "</mo_suppDurMortXb>"
       << "</SuppressionDurationMortality1>";

  oOut << "</paramFile>";

  oOut.close();

  return cFileString;
}


/////////////////////////////////////////////////////////////////////////////
// WriteSuppressionDurationMortErrorCommonStuff()
/////////////////////////////////////////////////////////////////////////////
void WriteSuppressionDurationMortErrorCommonStuff(std::fstream &oOut) {
  using namespace std;
  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06010101\">"
       << "<plot>"
       << "<timesteps>1</timesteps>"
       << "<yearsPerTimestep>1</yearsPerTimestep>"
       << "<randomSeed>1</randomSeed>"
       << "<plot_lenX>100</plot_lenX>"
       << "<plot_lenY>100</plot_lenY>"
       << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
       << "<plot_temp_C>12.88171785</plot_temp_C>"
       << "<plot_latitude>55.37</plot_latitude>"
       << "</plot>"
       << "<trees>"
       << "<tr_speciesList>"
       << "<tr_species speciesName=\"Species_1\"/>"
       << "<tr_species speciesName=\"Species_2\"/>"
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
}
