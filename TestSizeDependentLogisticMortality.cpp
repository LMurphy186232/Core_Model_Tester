//---------------------------------------------------------------------------
// TestSizeDependentLogisticMortality.cpp
//---------------------------------------------------------------------------
#include "TestSizeDependentLogisticMortality.h"
#include <gtest/gtest.h>
#include "SimManager.h"
#include "TreePopulation.h"
#include "BehaviorBase.h"
#include "ModelMath.h"
#include <fstream>
#include <math.h>

/////////////////////////////////////////////////////////////////////////////
// Run1()
/////////////////////////////////////////////////////////////////////////////
TEST(SizeDependentLogisticMortality, Run1) {
  clTreePopulation * p_oPop;
  clTreeSearch *p_oAllTrees;
  clTree *p_oTree;
  float fDBH;
  int *p_iNumTrees = new int[4], i, j;

  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {

    p_oSimManager->ReadFile(WriteSizeDepLogMortXMLFile1());
    p_oPop = (clTreePopulation *) p_oSimManager->GetPopulationObject("treepopulation");

    //Add 1000 trees to the plot of each tree
    for (i = 0; i < 1000; i++) {

      for (j = 0; j < 4; j++) {
        p_oPop->CreateTree(
          (200.0*clModelMath::GetRand()), //X
          (200.0*clModelMath::GetRand()), //Y
          j, //species
          clTreePopulation::sapling, //type
          8.0); //diameter
      }
      for (j = 0; j < 4; j++) {
        p_oPop->CreateTree(
          (200.0*clModelMath::GetRand()), //X
          (200.0*clModelMath::GetRand()), //Y
          j, //species
          clTreePopulation::adult, //type
          20.0); //diameter
      }
      for (j = 0; j < 4; j++) {
        p_oPop->CreateTree(
          (200.0*clModelMath::GetRand()), //X
          (200.0*clModelMath::GetRand()), //Y
          j, //species
          clTreePopulation::adult, //type
          60.0); //diameter
      }
      for (j = 0; j < 4; j++) {
        p_oPop->CreateTree(
          (200.0*clModelMath::GetRand()), //X
          (200.0*clModelMath::GetRand()), //Y
          j, //species
          clTreePopulation::adult, //type
          100.0); //diameter
      }
    }

    //Run the model
    p_oSimManager->RunSim(1);

    //Count up the 8 cm trees
    for (i = 0; i < 4; i++) {
      p_iNumTrees[i] = 0;
    }
    p_oAllTrees = p_oPop->Find("type=2");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {
      p_iNumTrees[p_oTree->GetSpecies()]++;
      p_oTree = p_oAllTrees->NextTree();
    }

    //Compare to expected results
    EXPECT_EQ(p_iNumTrees[0], 1000);
    EXPECT_LT(fabs(p_iNumTrees[1] - 763)/763, 0.05);
    EXPECT_GT(p_iNumTrees[2], 990);
    EXPECT_GT(p_iNumTrees[3], 990);

    //Count up the 20 cm trees
    for (i = 0; i < 4; i++) {
      p_iNumTrees[i] = 0;
    }
    p_oAllTrees = p_oPop->Find("type=3");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {
      p_oTree->GetValue(p_oPop->GetDbhCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fDBH);
      if (fabs(fDBH - 20.0) < 0.01) p_iNumTrees[p_oTree->GetSpecies()]++;
      p_oTree = p_oAllTrees->NextTree();
    }

    //Compare to expected results
    EXPECT_EQ(p_iNumTrees[0], 1000);
    EXPECT_LT(fabs(p_iNumTrees[1] - 707)/707, 0.05);
    EXPECT_LT(fabs(p_iNumTrees[2] - 992)/992, 0.05);
    EXPECT_GT(p_iNumTrees[3], 990);

    //Count up the 60 cm trees
    for (i = 0; i < 4; i++) {
      p_iNumTrees[i] = 0;
    }
    p_oAllTrees = p_oPop->Find("type=3");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {
      p_oTree->GetValue(p_oPop->GetDbhCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fDBH);
      if (fabs(fDBH - 60.0) < 0.01) p_iNumTrees[p_oTree->GetSpecies()]++;
      p_oTree = p_oAllTrees->NextTree();
    }

    //Compare to expected results
    EXPECT_EQ(p_iNumTrees[0], 1000);
    EXPECT_LT(fabs(p_iNumTrees[1] - 644)/644, 0.06);
    EXPECT_LT(fabs(p_iNumTrees[2] - 500)/500, 0.07);
    EXPECT_LT(fabs(p_iNumTrees[3] - 958)/958, 0.06);

    //Count up the 100 cm trees
    for (i = 0; i < 4; i++) {
      p_iNumTrees[i] = 0;
    }
    p_oAllTrees = p_oPop->Find("type=3");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {
      p_oTree->GetValue(p_oPop->GetDbhCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fDBH);
      if (fabs(fDBH - 100.0) < 0.01) p_iNumTrees[p_oTree->GetSpecies()]++;
      p_oTree = p_oAllTrees->NextTree();
    }

    //Compare to expected results
    EXPECT_EQ(p_iNumTrees[0], 1000);
    EXPECT_LT(fabs(p_iNumTrees[1] - 620)/620, 0.06);
    EXPECT_LT(fabs(p_iNumTrees[2] - 321)/321, 0.06);
    EXPECT_LT(fabs(p_iNumTrees[3] - 830)/830, 0.06);

    delete[] p_iNumTrees;
    delete p_oSimManager;
  } catch (modelErr &e) {
    delete[] p_iNumTrees;
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

/////////////////////////////////////////////////////////////////////////////
// Run2()
// This performs a test of stochastic mortality. An XML file is written with
// different species getting different mortality levels. This will add 1000
// trees of each species, run mortality, and then count the remaining trees
// to make sure the correct number were killed.
/////////////////////////////////////////////////////////////////////////////
TEST(SizeDependentLogisticMortality, Run2) {
  clTreePopulation * p_oPop;
  clTreeSearch *p_oAllTrees;
  clTree *p_oTree;
  float fDBH;
  int *p_iNumTrees = new int[4], i, j;

  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {

    p_oSimManager->ReadFile(WriteSizeDepLogMortXMLFile2());
    p_oPop = (clTreePopulation *) p_oSimManager->GetPopulationObject("treepopulation");

    //Add 1000 trees to the plot of each tree
    for (i = 0; i < 1000; i++) {

      for (j = 0; j < 4; j++) {
        p_oPop->CreateTree(
          (200.0*clModelMath::GetRand()), //X
          (200.0*clModelMath::GetRand()), //Y
          j, //species
          clTreePopulation::sapling, //type
          8.0); //diameter
      }
      for (j = 0; j < 4; j++) {
        p_oPop->CreateTree(
          (200.0*clModelMath::GetRand()), //X
          (200.0*clModelMath::GetRand()), //Y
          j, //species
          clTreePopulation::adult, //type
          20.0); //diameter
      }
      for (j = 0; j < 4; j++) {
        p_oPop->CreateTree(
          (200.0*clModelMath::GetRand()), //X
          (200.0*clModelMath::GetRand()), //Y
          j, //species
          clTreePopulation::adult, //type
          60.0); //diameter
      }
      for (j = 0; j < 4; j++) {
        p_oPop->CreateTree(
          (200.0*clModelMath::GetRand()), //X
          (200.0*clModelMath::GetRand()), //Y
          j, //species
          clTreePopulation::adult, //type
          100.0); //diameter
      }
    }

    //Run the model
    p_oSimManager->RunSim(1);

    //Count up the 8 cm trees
    for (i = 0; i < 4; i++) {
      p_iNumTrees[i] = 0;
    }
    p_oAllTrees = p_oPop->Find("type=2");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {
      p_iNumTrees[p_oTree->GetSpecies()]++;
      p_oTree = p_oAllTrees->NextTree();
    }

    //Compare to expected results
    EXPECT_EQ(p_iNumTrees[0], 1000);
    EXPECT_LT(fabs(p_iNumTrees[1] - 445)/445, 0.06);
    EXPECT_GT(p_iNumTrees[2], 990);
    EXPECT_GT(p_iNumTrees[3], 990);

    //Count up the 20 cm trees
    for (i = 0; i < 4; i++) {
      p_iNumTrees[i] = 0;
    }
    p_oAllTrees = p_oPop->Find("type=3");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {
      p_oTree->GetValue(p_oPop->GetDbhCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fDBH);
      if (fabs(fDBH - 20.0) < 0.01) p_iNumTrees[p_oTree->GetSpecies()]++;
      p_oTree = p_oAllTrees->NextTree();
    }

    //Compare to expected results
    EXPECT_EQ(p_iNumTrees[0], 1000);
    EXPECT_LT(fabs(p_iNumTrees[1] - 353)/353, 0.06);
    EXPECT_LT(fabs(p_iNumTrees[2] - 978)/978, 0.06);
    EXPECT_GT(p_iNumTrees[3], 990);

    //Count up the 60 cm trees
    for (i = 0; i < 4; i++) {
      p_iNumTrees[i] = 0;
    }
    p_oAllTrees = p_oPop->Find("type=3");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {
      p_oTree->GetValue(p_oPop->GetDbhCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fDBH);
      if (fabs(fDBH - 60.0) < 0.01) p_iNumTrees[p_oTree->GetSpecies()]++;
      p_oTree = p_oAllTrees->NextTree();
    }

    //Compare to expected results
    EXPECT_EQ(p_iNumTrees[0], 1000);
    EXPECT_LT(fabs(p_iNumTrees[1] - 268)/268, 0.12);
    EXPECT_LT(fabs(p_iNumTrees[2] - 125)/125, 0.12);
    EXPECT_LT(fabs(p_iNumTrees[3] - 880)/880, 0.06);

    //Count up the 100 cm trees
    for (i = 0; i < 4; i++) {
      p_iNumTrees[i] = 0;
    }
    p_oAllTrees = p_oPop->Find("type=3");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {
      p_oTree->GetValue(p_oPop->GetDbhCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fDBH);
      if (fabs(fDBH - 100.0) < 0.01) p_iNumTrees[p_oTree->GetSpecies()]++;
      p_oTree = p_oAllTrees->NextTree();
    }

    //Compare to expected results
    EXPECT_EQ(p_iNumTrees[0], 1000);
    EXPECT_LT(fabs(p_iNumTrees[1] - 238)/238, 0.10);
    EXPECT_LT(p_iNumTrees[2], 50);
    EXPECT_LT(fabs(p_iNumTrees[3] - 572)/572, 0.06);

    delete[] p_iNumTrees;
    delete p_oSimManager;
  } catch (modelErr &e) {
    delete[] p_iNumTrees;
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}



/////////////////////////////////////////////////////////////////////////////
// WriteSizeDepLogMortXMLFile1()
/////////////////////////////////////////////////////////////////////////////
const char* WriteSizeDepLogMortXMLFile1()
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
      << "<yearsPerTimestep>1</yearsPerTimestep>"
      << "<randomSeed>1</randomSeed>"
      << "<plot_lenX>200.0</plot_lenX>"
      << "<plot_lenY>200.0</plot_lenY>"
      << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
      << "<plot_temp_C>12.88171785</plot_temp_C>"
      << "<plot_latitude>55.37</plot_latitude>"
      << "<plot_title>Test Plot 2</plot_title>"
      << "</plot>"
      << "<trees>"
      << "<tr_speciesList>"
      << "<tr_species speciesName=\"Species_1\"/>"
      << "<tr_species speciesName=\"Species_2\"/>"
      << "<tr_species speciesName=\"Species_3\"/>"
      << "<tr_species speciesName=\"Species_4\"/>"
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
      << "</allometry>"
      << "<behaviorList>"
      << "<behavior>"
      << "<behaviorName>SizeDependentLogisticMortality</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>1</listPosition>"
      << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_3\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_4\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_4\" type=\"Adult\"/>"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>RemoveDead</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>2</listPosition>"
      << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_3\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_4\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_4\" type=\"Adult\"/>"
      << "</behavior>"
      << "</behaviorList>"
      << "<SizeDependentLogisticMortality1>"
      << "<mo_sizeDepLogMax>"
      << "<mo_sdlmVal species=\"Species_2\">0.5</mo_sdlmVal>"
      << "<mo_sdlmVal species=\"Species_3\">0.7</mo_sdlmVal>"
      << "<mo_sdlmVal species=\"Species_4\">0.2</mo_sdlmVal>"
      << "</mo_sizeDepLogMax>"
      << "<mo_sizeDepLogX0>"
      << "<mo_sdlx0Val species=\"Species_2\">10</mo_sdlx0Val>"
      << "<mo_sdlx0Val species=\"Species_3\">50</mo_sdlx0Val>"
      << "<mo_sdlx0Val species=\"Species_4\">75</mo_sdlx0Val>"
      << "</mo_sizeDepLogX0>"
      << "<mo_sizeDepLogXb>"
      << "<mo_sdlxbVal species=\"Species_2\">-0.5</mo_sdlxbVal>"
      << "<mo_sdlxbVal species=\"Species_3\">-5</mo_sdlxbVal>"
      << "<mo_sdlxbVal species=\"Species_4\">-6</mo_sdlxbVal>"
      << "</mo_sizeDepLogXb>"
      << "</SizeDependentLogisticMortality1>"
      << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteSizeDepLogMortXMLFile2()
/////////////////////////////////////////////////////////////////////////////
const char* WriteSizeDepLogMortXMLFile2()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
      << "<paramFile fileCode=\"06010101\">" << "<plot>"
      << "<timesteps>2</timesteps>"
      << "<yearsPerTimestep>3</yearsPerTimestep>"
      << "<randomSeed>1</randomSeed>"
      << "<plot_lenX>200.0</plot_lenX>"
      << "<plot_lenY>200.0</plot_lenY>"
      << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
      << "<plot_temp_C>12.88171785</plot_temp_C>"
      << "<plot_latitude>55.37</plot_latitude>"
      << "<plot_title>Test Plot 2</plot_title>"
      << "</plot>"
      << "<trees>"
      << "<tr_speciesList>"
      << "<tr_species speciesName=\"Species_1\"/>"
      << "<tr_species speciesName=\"Species_2\"/>"
      << "<tr_species speciesName=\"Species_3\"/>"
      << "<tr_species speciesName=\"Species_4\"/>"
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
      << "</allometry>"
      << "<behaviorList>"
      << "<behavior>"
      << "<behaviorName>SizeDependentLogisticMortality</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>1</listPosition>"
      << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_3\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_4\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_4\" type=\"Adult\"/>"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>RemoveDead</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>2</listPosition>"
      << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_3\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_4\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_4\" type=\"Adult\"/>"
      << "</behavior>"
      << "</behaviorList>"
      << "<SizeDependentLogisticMortality1>"
      << "<mo_sizeDepLogMax>"
      << "<mo_sdlmVal species=\"Species_2\">0.5</mo_sdlmVal>"
      << "<mo_sdlmVal species=\"Species_3\">0.7</mo_sdlmVal>"
      << "<mo_sdlmVal species=\"Species_4\">0.2</mo_sdlmVal>"
      << "</mo_sizeDepLogMax>"
      << "<mo_sizeDepLogX0>"
      << "<mo_sdlx0Val species=\"Species_2\">10</mo_sdlx0Val>"
      << "<mo_sdlx0Val species=\"Species_3\">50</mo_sdlx0Val>"
      << "<mo_sdlx0Val species=\"Species_4\">75</mo_sdlx0Val>"
      << "</mo_sizeDepLogX0>"
      << "<mo_sizeDepLogXb>"
      << "<mo_sdlxbVal species=\"Species_2\">-0.5</mo_sdlxbVal>"
      << "<mo_sdlxbVal species=\"Species_3\">-5</mo_sdlxbVal>"
      << "<mo_sdlxbVal species=\"Species_4\">-6</mo_sdlxbVal>"
      << "</mo_sizeDepLogXb>"
      << "</SizeDependentLogisticMortality1>"
      << "</paramFile>";

  oOut.close();

  return cFileString;
}


