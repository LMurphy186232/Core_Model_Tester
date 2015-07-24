//---------------------------------------------------------------------------
// TestResourceMortality.cpp
//---------------------------------------------------------------------------
#include "TestResourceMortality.h"
#include <gtest/gtest.h>
#include "SimManager.h"
#include "TreePopulation.h"
#include "BehaviorBase.h"
#include <fstream>
#include <math.h>

/////////////////////////////////////////////////////////////////////////////
// TestResourceMortality()
// Tests the growth-and-resource mortality class.
//
// First run: WriteResourceMortalityXMLFile1() creates the parameter file. The file has the
// following characteristics:
//
// -- Timestep length of 1 year.
// -- 3 species: Species 1, Species 2, Species 3 (Species 2 isn't used).
// -- Growth and resource mortality applied to saplings and adults of both
// species.
// -- The resource grid has specified values for 4 cells.
//
// The function does the following:
//
// -- 1000 trees are created of each species for both saplings and
// adults.
//
// -- Saplings of species 1 all get a value of 0 in their "growth" data member
// and 0 for their resource level.
// -- Saplings of Species 3 all get a value of 0 in their "growth" data member
// and 1.2 for their resource level.
// -- Adults of Species 1 all get a value of 4 in their "growth" data member
// and 0 for their resource level.
// -- Adults of Species 3 all get a value of 25.1 in their "growth" data member
// and 0.01 for their resource level.
//
// --  The model is run for 1 timestep.
// --  The remaining trees of each tree type and species are counted.
// --  The counts are compared to expected results, give or take 5% (or
// greater tolerance at lower numbers).
/////////////////////////////////////////////////////////////////////////////
TEST(ResourceMortality, NormalProcessingRun1) {

  clTreePopulation * p_oPop;
  clTreeSearch *p_oAllTrees;
  clTree *p_oTree;
  float fVal;
  int **p_iTreeCount;
  int i, j, iNumSpecies, iNumTypes;

  //Create the sim manager and load our file
  clSimManager *p_oSimManager = new clSimManager(7, 1, "");
  p_oSimManager->ReadFile( WriteResourceMortalityXMLFile1() );
  p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );
  iNumSpecies = p_oPop->GetNumberOfSpecies();
  iNumTypes = p_oPop->GetNumberOfTypes();

  //Set up our tree count array
  p_iTreeCount = new int*[iNumSpecies];
  for (i = 0; i < iNumSpecies; i++) {
    p_iTreeCount[i] = new int[iNumTypes];
    for (j = 0; j < iNumTypes; j++) {
      p_iTreeCount[i][j] = 0;
    }
  }

  //Create 1000 of each kind of tree affected by mortality

  //Saplings of Species 1
  fVal = 0.0;
  for (i = 0; i < 1000; i++) {
    p_oTree = p_oPop->CreateTree(1, 1, 0, clTreePopulation::sapling, 7);
    //Put the correct value in the "Growth" data member
    p_oTree->SetValue(p_oPop->GetFloatDataCode("Growth", p_oTree->GetSpecies(), p_oTree->GetType()), fVal);
  }

  //Saplings of Species 3
  fVal = 0.0;
  for (i = 0; i < 1000; i++) {
    p_oTree = p_oPop->CreateTree(9, 9, 2, clTreePopulation::sapling, 7);
    //Put the correct value in the "Growth" data member
    p_oTree->SetValue(p_oPop->GetFloatDataCode("Growth", p_oTree->GetSpecies(), p_oTree->GetType()), fVal);
  }

  //Adults of Species 1
  fVal = 4;
  for (i = 0; i < 1000; i++) {
    p_oTree = p_oPop->CreateTree(17, 17, 0, clTreePopulation::adult, 17);
    //Put the correct value in the "Growth" data member
    p_oTree->SetValue(p_oPop->GetFloatDataCode("Growth", p_oTree->GetSpecies(), p_oTree->GetType()), fVal);
  }

  //Adults of Species 3
  fVal = 25.1;
  for (i = 0; i < 1000; i++) {
    p_oTree = p_oPop->CreateTree(25, 25, 2, clTreePopulation::adult, 17);
    //Put the correct value in the "Growth" data member
    p_oTree->SetValue(p_oPop->GetFloatDataCode("Growth", p_oTree->GetSpecies(), p_oTree->GetType()), fVal);
  }

  //Initial conditions count
  p_oAllTrees = p_oPop->Find("all");
  p_oTree = p_oAllTrees->NextTree();
  while (p_oTree) {
    p_iTreeCount[p_oTree->GetSpecies()][p_oTree->GetType()]++;
    p_oTree = p_oAllTrees->NextTree();
  }
  EXPECT_EQ(p_iTreeCount[0][clTreePopulation::sapling], 1000);
  EXPECT_EQ(p_iTreeCount[0][clTreePopulation::adult], 1000);
  EXPECT_EQ(p_iTreeCount[2][clTreePopulation::sapling], 1000);
  EXPECT_EQ(p_iTreeCount[2][clTreePopulation::adult], 1000);

  //Run for one timestep - everything except the light behavior
  for (i = 1; i < p_oSimManager->GetNumberOfBehaviors(); i++)
    p_oSimManager->GetBehaviorObject(i)->Action();

  //Count the remaining trees
  for (i = 0; i < iNumSpecies; i++) {
    for (j = 0; j < iNumTypes; j++) {
      p_iTreeCount[i][j] = 0;
    }
  }
  p_oAllTrees = p_oPop->Find("all");
  p_oTree = p_oAllTrees->NextTree();
  while (p_oTree) {
    p_iTreeCount[p_oTree->GetSpecies()][p_oTree->GetType()]++;
    p_oTree = p_oAllTrees->NextTree();
  }

  //Make sure they are as expected

  //Saplings of Species 1
  EXPECT_LT(fabs(p_iTreeCount[0][clTreePopulation::sapling] - 640.5)/640.5, 0.05);

  //Saplings of Species 3
  EXPECT_LT(fabs(p_iTreeCount[2][clTreePopulation::sapling] - 242.6)/242.6, 0.1);

  //Adults of Species 1
  EXPECT_LT(fabs(p_iTreeCount[0][clTreePopulation::adult] - 795.5)/795.5, 0.05);

  //Adults of Species 3
  EXPECT_LT(fabs(p_iTreeCount[2][clTreePopulation::adult] - 397.7)/397.7, 0.1);

  for (i = 0; i < iNumSpecies; i++) delete[] p_iTreeCount[i];
    delete[] p_iTreeCount;

  delete p_oSimManager;
}

/////////////////////////////////////////////////////////////////////////////
// TestResourceMortality()
// Tests the growth-and-resource mortality class.
//
// Second run:
// WriteResourceMortalityXMLFile2() creates the parameter file. The file has the following
// characteristics:
//
// -- Timestep length of 5 years.
// -- 3 species: Species 1, Species 2, Species 3 (Species 2 isn't used).
// -- Growth and resource mortality applied to saplings and adults of both
// species.
// -- The resource grid has specified values for 4 cells.
//
// The function does the following:
//
// -- 1000 trees are created of each species for both saplings and
//adults.
//
// -- Saplings of species 1 all get a value of 0 in their "growth" data member
// and 0 for their resource level.
// -- Saplings of Species 3 all get a value of 0 in their "growth" data member
// and 1.2 for their resource level.
// -- Adults of Species 1 all get a value of 4 in their "growth" data member
// and 0 for their resource level.
// -- Adults of Species 3 all get a value of 25.1 in their "growth" data member
// and 0.01 for their resource level.
//
// --  The model is run for 1 timestep.
// --  The remaining trees of each tree type and species are counted.
// --  The counts are compared to expected results, give or take 5% (or
// greater tolerance at lower numbers).
/////////////////////////////////////////////////////////////////////////////
TEST(ResourceMortality, NormalProcessingRun2) {
  clTreePopulation * p_oPop;
  clTreeSearch *p_oAllTrees;
  clTree *p_oTree;
  float fVal;
  int **p_iTreeCount;
  int i, j, iNumSpecies, iNumTypes;

  clSimManager *p_oSimManager = new clSimManager(7, 1, "");
  //Load our second file
  p_oSimManager->ReadFile( WriteResourceMortalityXMLFile2() );
  p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );
  iNumSpecies = p_oPop->GetNumberOfSpecies();
  iNumTypes = p_oPop->GetNumberOfTypes();

  //Set up our tree count array
  p_iTreeCount = new int*[iNumSpecies];
  for (i = 0; i < iNumSpecies; i++) {
    p_iTreeCount[i] = new int[iNumTypes];
    for (j = 0; j < iNumTypes; j++) {
      p_iTreeCount[i][j] = 0;
    }
  }

  //Create 1000 of each kind of tree affected by mortality

  //Saplings of Species 1
  fVal = 0.0;
  for (i = 0; i < 1000; i++) {
    p_oTree = p_oPop->CreateTree(1, 1, 0, clTreePopulation::sapling, 7);
    //Put the correct value in the "Growth" data member
    p_oTree->SetValue(p_oPop->GetFloatDataCode("Growth", p_oTree->GetSpecies(), p_oTree->GetType()), fVal);
  }

  //Saplings of Species 3
  fVal = 0.0;
  for (i = 0; i < 1000; i++) {
    p_oTree = p_oPop->CreateTree(9, 9, 2, clTreePopulation::sapling, 7);
    //Put the correct value in the "Growth" data member
    p_oTree->SetValue(p_oPop->GetFloatDataCode("Growth", p_oTree->GetSpecies(), p_oTree->GetType()), fVal);
  }

  //Adults of Species 1
  fVal = 4;
  for (i = 0; i < 1000; i++) {
    p_oTree = p_oPop->CreateTree(17, 17, 0, clTreePopulation::adult, 17);
    //Put the correct value in the "Growth" data member
    p_oTree->SetValue(p_oPop->GetFloatDataCode("Growth", p_oTree->GetSpecies(), p_oTree->GetType()), fVal);
  }

  //Adults of Species 3
  fVal = 25.1;
  for (i = 0; i < 1000; i++) {
    p_oTree = p_oPop->CreateTree(25, 25, 2, clTreePopulation::adult, 17);
    //Put the correct value in the "Growth" data member
    p_oTree->SetValue(p_oPop->GetFloatDataCode("Growth", p_oTree->GetSpecies(), p_oTree->GetType()), fVal);
  }

  //Initial conditions count
  p_oAllTrees = p_oPop->Find("all");
  p_oTree = p_oAllTrees->NextTree();
  while (p_oTree) {
    p_iTreeCount[p_oTree->GetSpecies()][p_oTree->GetType()]++;
    p_oTree = p_oAllTrees->NextTree();
  }
  EXPECT_EQ(p_iTreeCount[0][clTreePopulation::sapling], 1000);
  EXPECT_EQ(p_iTreeCount[0][clTreePopulation::adult], 1000);
  EXPECT_EQ(p_iTreeCount[2][clTreePopulation::sapling], 1000);
  EXPECT_EQ(p_iTreeCount[2][clTreePopulation::adult], 1000);

  //Run for one timestep - everything except the light behavior
  for (i = 1; i < p_oSimManager->GetNumberOfBehaviors(); i++)
    p_oSimManager->GetBehaviorObject(i)->Action();

  //Count the remaining trees
  for (i = 0; i < iNumSpecies; i++) {
    for (j = 0; j < iNumTypes; j++) {
      p_iTreeCount[i][j] = 0;
    }
  }
  p_oAllTrees = p_oPop->Find("all");
  p_oTree = p_oAllTrees->NextTree();
  while (p_oTree) {
    p_iTreeCount[p_oTree->GetSpecies()][p_oTree->GetType()]++;
    p_oTree = p_oAllTrees->NextTree();
  }

  //Make sure they are as expected

  //Saplings of Species 1
  EXPECT_LT(fabs(p_iTreeCount[0][clTreePopulation::sapling] - 262.8)/262.8, 0.1);

  //Saplings of Species 3
  EXPECT_LT(p_iTreeCount[2][clTreePopulation::sapling], 30);

  //Adults of Species 1
  EXPECT_LT(fabs(p_iTreeCount[0][clTreePopulation::adult] - 503.5)/503.5, 0.05);

  //Adults of Species 3
  EXPECT_GT(p_iTreeCount[2][clTreePopulation::adult], 30);
  EXPECT_LT(p_iTreeCount[2][clTreePopulation::adult], 90);

  //Cleanup
  for (i = 0; i < iNumSpecies; i++) delete[] p_iTreeCount[i];
    delete[] p_iTreeCount;

  delete p_oSimManager;
}

/////////////////////////////////////////////////////////////////////////////
// WriteResourceMortalityXMLFile1()
/////////////////////////////////////////////////////////////////////////////
const char* WriteResourceMortalityXMLFile1()
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
       << "<rt_timestep>0</rt_timestep>"
       << "<randomSeed>1</randomSeed>"
       << "<yearsPerTimestep>1.0</yearsPerTimestep>"
       << "<plot_lenX>200.0</plot_lenX>"
       << "<plot_lenY>200.0</plot_lenY>"
       << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
       << "<plot_temp_C>12.88171785</plot_temp_C>"
       << "<plot_latitude>0.0</plot_latitude>"
       << "</plot>"
       << "<trees>"
       << "<tr_speciesList>"
       << "<tr_species speciesName=\"Species_1\" />"
       << "<tr_species speciesName=\"Species_2\" />"
       << "<tr_species speciesName=\"Species_3\" />"
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
       << "<tr_chVal species=\"Species_1\">40.0</tr_chVal>"
       << "<tr_chVal species=\"Species_2\">40.0</tr_chVal>"
       << "<tr_chVal species=\"Species_3\">40.0</tr_chVal>"
       << "</tr_canopyHeight>"
       << "<tr_stdAsympCrownRad>"
       << "<tr_sacrVal species=\"Species_1\">0.7</tr_sacrVal>"
       << "<tr_sacrVal species=\"Species_2\">0.7</tr_sacrVal>"
       << "<tr_sacrVal species=\"Species_3\">0.7</tr_sacrVal>"
       << "</tr_stdAsympCrownRad>"
       << "<tr_stdCrownRadExp>"
       << "<tr_screVal species=\"Species_1\">1.0</tr_screVal>"
       << "<tr_screVal species=\"Species_2\">1.0</tr_screVal>"
       << "<tr_screVal species=\"Species_3\">1.0</tr_screVal>"
       << "</tr_stdCrownRadExp>"
       << "<tr_conversionDiam10ToDBH>"
       << "<tr_cdtdVal species=\"Species_1\">0.7</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_2\">0.7</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_3\">0.7</tr_cdtdVal>"
       << "</tr_conversionDiam10ToDBH>"
        << "<tr_interceptDiam10ToDBH>"
       << "<tr_idtdVal species=\"Species_1\">0</tr_idtdVal>"
       << "<tr_idtdVal species=\"Species_2\">0</tr_idtdVal>"
       << "<tr_idtdVal species=\"Species_3\">0</tr_idtdVal>"
       << "</tr_interceptDiam10ToDBH>"
       << "<tr_stdAsympCrownHt>"
       << "<tr_sachVal species=\"Species_1\">0.7</tr_sachVal>"
       << "<tr_sachVal species=\"Species_2\">0.7</tr_sachVal>"
       << "<tr_sachVal species=\"Species_3\">0.7</tr_sachVal>"
       << "</tr_stdAsympCrownHt>"
       << "<tr_stdCrownHtExp>"
       << "<tr_scheVal species=\"Species_1\">1.0</tr_scheVal>"
       << "<tr_scheVal species=\"Species_2\">1.0</tr_scheVal>"
       << "<tr_scheVal species=\"Species_3\">1.0</tr_scheVal>"
       << "</tr_stdCrownHtExp>"
       << "<tr_slopeOfHeight-Diam10>"
       << "<tr_sohdVal species=\"Species_1\">0.03</tr_sohdVal>"
       << "<tr_sohdVal species=\"Species_2\">0.03</tr_sohdVal>"
       << "<tr_sohdVal species=\"Species_3\">0.03</tr_sohdVal>"
       << "</tr_slopeOfHeight-Diam10>"
       << "<tr_slopeOfAsymHeight>"
       << "<tr_soahVal species=\"Species_1\">0.7</tr_soahVal>"
       << "<tr_soahVal species=\"Species_2\">0.7</tr_soahVal>"
       << "<tr_soahVal species=\"Species_3\">0.7</tr_soahVal>"
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
       << "</allometry>"
       << "<grid gridName=\"Resource\">"
       << "<ma_floatCodes>"
       << "<ma_floatCode label=\"Resource\">0</ma_floatCode>"
       << "</ma_floatCodes>"
       << "<ma_lengthXCells>8</ma_lengthXCells>"
       << "<ma_lengthYCells>8</ma_lengthYCells>"
       << "<ma_v x=\"0\" y=\"0\">"
       << "<fl c=\"0\">0</fl>"
       << "</ma_v>"
       << "<ma_v x=\"1\" y=\"1\">"
       << "<fl c=\"0\">0.5</fl>"
       << "</ma_v>"
       << "<ma_v x=\"2\" y=\"2\">"
       << "<fl c=\"0\">0</fl>"
       << "</ma_v>"
       << "<ma_v x=\"3\" y=\"3\">"
       << "<fl c=\"0\">0.01</fl>"
       << "</ma_v>"
       << "</grid>"
       << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>ConstBAGrowth</behaviorName>"
       << "<version>1.0</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Sapling\" />"
       << "<applyTo species=\"Species_3\" type=\"Sapling\" />"
       << "<applyTo species=\"Species_1\" type=\"Adult\" />"
       << "<applyTo species=\"Species_3\" type=\"Adult\" />"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>GrowthResourceMortality</behaviorName>"
       << "<version>1.0</version>"
       << "<listPosition>2</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Sapling\" />"
       << "<applyTo species=\"Species_3\" type=\"Sapling\" />"
       << "<applyTo species=\"Species_1\" type=\"Adult\" />"
       << "<applyTo species=\"Species_3\" type=\"Adult\" />"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>RemoveDead</behaviorName>"
       << "<version>2.0</version>"
       << "<listPosition>3</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Sapling\" />"
       << "<applyTo species=\"Species_3\" type=\"Sapling\" />"
       << "<applyTo species=\"Species_1\" type=\"Adult\" />"
       << "<applyTo species=\"Species_3\" type=\"Adult\" />"
       << "</behavior>"
       << "</behaviorList>"
       << "<ConstBAGrowth1>"
       << "<gr_adultConstAreaInc>"
       << "<gr_acaiVal species=\"Species_1\">0.3</gr_acaiVal>"
       << "<gr_acaiVal species=\"Species_3\">0.3</gr_acaiVal>"
       << "</gr_adultConstAreaInc>"
       << "</ConstBAGrowth1>"
       << "<GrowthResourceMortality2>"
       << "<mo_resMortScalingFactor>"
       << "<mo_rmsfVal species=\"Species_1\">0.8</mo_rmsfVal>"
       << "<mo_rmsfVal species=\"Species_3\">0.4</mo_rmsfVal>"
       << "</mo_resMortScalingFactor>"
       << "<mo_resMortMode>"
       << "<mo_rmmVal species=\"Species_1\">0.2</mo_rmmVal>"
       << "<mo_rmmVal species=\"Species_3\">0.3</mo_rmmVal>"
       << "</mo_resMortMode>"
       << "<mo_resMortGrowthIncSurv>"
       << "<mo_rmgisVal species=\"Species_1\">0.4</mo_rmgisVal>"
       << "<mo_rmgisVal species=\"Species_3\">0.1</mo_rmgisVal>"
       << "</mo_resMortGrowthIncSurv>"
       << "<mo_resMortLoGrowthShape>"
       << "<mo_rmlgsVal species=\"Species_1\">0.3</mo_rmlgsVal>"
       << "<mo_rmlgsVal species=\"Species_3\">0.2</mo_rmlgsVal>"
       << "</mo_resMortLoGrowthShape>"
       << "</GrowthResourceMortality2>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteResourceMortalityXMLFile2()
/////////////////////////////////////////////////////////////////////////////
const char* WriteResourceMortalityXMLFile2() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06010101\">"
       << "<plot>"
       << "<timesteps>2</timesteps>"
       << "<rt_timestep>0</rt_timestep>"
       << "<randomSeed>1</randomSeed>"
       << "<yearsPerTimestep>3.0</yearsPerTimestep>"
       << "<plot_lenX>200.0</plot_lenX>"
       << "<plot_lenY>200.0</plot_lenY>"
       << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
       << "<plot_temp_C>12.88171785</plot_temp_C>"
       << "<plot_latitude>0.0</plot_latitude>"
       << "</plot>"
       << "<trees>"
       << "<tr_speciesList>"
       << "<tr_species speciesName=\"Species_1\" />"
       << "<tr_species speciesName=\"Species_2\" />"
       << "<tr_species speciesName=\"Species_3\" />"
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
       << "<tr_chVal species=\"Species_1\">40.0</tr_chVal>"
       << "<tr_chVal species=\"Species_2\">40.0</tr_chVal>"
       << "<tr_chVal species=\"Species_3\">40.0</tr_chVal>"
       << "</tr_canopyHeight>"
       << "<tr_stdAsympCrownRad>"
       << "<tr_sacrVal species=\"Species_1\">0.7</tr_sacrVal>"
       << "<tr_sacrVal species=\"Species_2\">0.7</tr_sacrVal>"
       << "<tr_sacrVal species=\"Species_3\">0.7</tr_sacrVal>"
       << "</tr_stdAsympCrownRad>"
       << "<tr_stdCrownRadExp>"
       << "<tr_screVal species=\"Species_1\">1.0</tr_screVal>"
       << "<tr_screVal species=\"Species_2\">1.0</tr_screVal>"
       << "<tr_screVal species=\"Species_3\">1.0</tr_screVal>"
       << "</tr_stdCrownRadExp>"
       << "<tr_conversionDiam10ToDBH>"
       << "<tr_cdtdVal species=\"Species_1\">0.7</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_2\">0.7</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_3\">0.7</tr_cdtdVal>"
       << "</tr_conversionDiam10ToDBH>"
        << "<tr_interceptDiam10ToDBH>"
       << "<tr_idtdVal species=\"Species_1\">0</tr_idtdVal>"
       << "<tr_idtdVal species=\"Species_2\">0</tr_idtdVal>"
       << "<tr_idtdVal species=\"Species_3\">0</tr_idtdVal>"
       << "</tr_interceptDiam10ToDBH>"
       << "<tr_stdAsympCrownHt>"
       << "<tr_sachVal species=\"Species_1\">0.7</tr_sachVal>"
       << "<tr_sachVal species=\"Species_2\">0.7</tr_sachVal>"
       << "<tr_sachVal species=\"Species_3\">0.7</tr_sachVal>"
       << "</tr_stdAsympCrownHt>"
       << "<tr_stdCrownHtExp>"
       << "<tr_scheVal species=\"Species_1\">1.0</tr_scheVal>"
       << "<tr_scheVal species=\"Species_2\">1.0</tr_scheVal>"
       << "<tr_scheVal species=\"Species_3\">1.0</tr_scheVal>"
       << "</tr_stdCrownHtExp>"
       << "<tr_slopeOfHeight-Diam10>"
       << "<tr_sohdVal species=\"Species_1\">0.03</tr_sohdVal>"
       << "<tr_sohdVal species=\"Species_2\">0.03</tr_sohdVal>"
       << "<tr_sohdVal species=\"Species_3\">0.03</tr_sohdVal>"
       << "</tr_slopeOfHeight-Diam10>"
       << "<tr_slopeOfAsymHeight>"
       << "<tr_soahVal species=\"Species_1\">0.7</tr_soahVal>"
       << "<tr_soahVal species=\"Species_2\">0.7</tr_soahVal>"
       << "<tr_soahVal species=\"Species_3\">0.7</tr_soahVal>"
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
       << "</allometry>"
       << "<grid gridName=\"Resource\">"
       << "<ma_floatCodes>"
       << "<ma_floatCode label=\"Resource\">0</ma_floatCode>"
       << "</ma_floatCodes>"
       << "<ma_lengthXCells>8</ma_lengthXCells>"
       << "<ma_lengthYCells>8</ma_lengthYCells>"
       << "<ma_v x=\"0\" y=\"0\">"
       << "<fl c=\"0\">0</fl>"
       << "</ma_v>"
       << "<ma_v x=\"1\" y=\"1\">"
       << "<fl c=\"0\">0.5</fl>"
       << "</ma_v>"
       << "<ma_v x=\"2\" y=\"2\">"
       << "<fl c=\"0\">0</fl>"
       << "</ma_v>"
       << "<ma_v x=\"3\" y=\"3\">"
       << "<fl c=\"0\">0.01</fl>"
       << "</ma_v>"
       << "</grid>"
       << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>ConstBAGrowth</behaviorName>"
       << "<version>1.0</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Sapling\" />"
       << "<applyTo species=\"Species_3\" type=\"Sapling\" />"
       << "<applyTo species=\"Species_1\" type=\"Adult\" />"
       << "<applyTo species=\"Species_3\" type=\"Adult\" />"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>GrowthResourceMortality</behaviorName>"
       << "<version>1.0</version>"
       << "<listPosition>2</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Sapling\" />"
       << "<applyTo species=\"Species_3\" type=\"Sapling\" />"
       << "<applyTo species=\"Species_1\" type=\"Adult\" />"
       << "<applyTo species=\"Species_3\" type=\"Adult\" />"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>RemoveDead</behaviorName>"
       << "<version>2.0</version>"
       << "<listPosition>3</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Sapling\" />"
       << "<applyTo species=\"Species_3\" type=\"Sapling\" />"
       << "<applyTo species=\"Species_1\" type=\"Adult\" />"
       << "<applyTo species=\"Species_3\" type=\"Adult\" />"
       << "</behavior>"
       << "</behaviorList>"
       << "<ConstBAGrowth1>"
       << "<gr_adultConstAreaInc>"
       << "<gr_acaiVal species=\"Species_1\">0.3</gr_acaiVal>"
       << "<gr_acaiVal species=\"Species_3\">0.3</gr_acaiVal>"
       << "</gr_adultConstAreaInc>"
       << "</ConstBAGrowth1>"
       << "<GrowthResourceMortality2>"
       << "<mo_resMortScalingFactor>"
       << "<mo_rmsfVal species=\"Species_1\">0.8</mo_rmsfVal>"
       << "<mo_rmsfVal species=\"Species_3\">0.4</mo_rmsfVal>"
       << "</mo_resMortScalingFactor>"
       << "<mo_resMortMode>"
       << "<mo_rmmVal species=\"Species_1\">0.2</mo_rmmVal>"
       << "<mo_rmmVal species=\"Species_3\">0.3</mo_rmmVal>"
       << "</mo_resMortMode>"
       << "<mo_resMortGrowthIncSurv>"
       << "<mo_rmgisVal species=\"Species_1\">0.4</mo_rmgisVal>"
       << "<mo_rmgisVal species=\"Species_3\">0.1</mo_rmgisVal>"
       << "</mo_resMortGrowthIncSurv>"
       << "<mo_resMortLoGrowthShape>"
       << "<mo_rmlgsVal species=\"Species_1\">0.3</mo_rmlgsVal>"
       << "<mo_rmlgsVal species=\"Species_3\">0.2</mo_rmlgsVal>"
       << "</mo_resMortLoGrowthShape>"
       << "</GrowthResourceMortality2>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

