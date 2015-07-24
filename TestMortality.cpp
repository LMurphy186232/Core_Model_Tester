//---------------------------------------------------------------------------
// TestMortality.cpp
//---------------------------------------------------------------------------
#include "TestMortality.h"
#include <gtest/gtest.h>
#include "SimManager.h"
#include "TreePopulation.h"
#include "BehaviorBase.h"
#include <fstream>
#include <math.h>

/////////////////////////////////////////////////////////////////////////////
// TestMortality()
// Tests the mortality classes.
// First run: WriteMortalityXMLFile1() creates the parameter file. The file has the
// following characteristics:
//
// -- Timestep length of 1 year.
// -- 5 species: Species 1, Species 2, Species 3, Species 4, Species 5.
// -- BC mortality behavior, applied to seedlings, saplings, and adults of
// Species 1.
// -- Juvenile stochastic mortality behavior, applied to seedlings of
// Species 3 and Species 4.
// -- Adult stochastic mortality behavior, applied to adults of Species 3.
// -- Senescence mortality behavior, applied to adults of Species 4.
// -- Adult self-thinning behavior, applied to adults of Species 5.
// -- Juvenile self-thinning behavior, applied to saplings of Species 4.
//
// The function does the following:
//
// -- 1000 trees are created of each tree species/type combination that has
// been applied to a behavior.
//
// -- Seedlings of species 1 all get a value of 0 in their "Growth" data
// member.
// -- Saplings of Species 1 all get a value of 0.1 in their "Growth" data
// member.
// -- Adults of Species 1 all get a value of 5 in their "Growth" data member.
// -- Adults of Species 4 all get a DBH of 100.
// -- Adults of Species 5 all get a DBH 20.
// -- Saplings of Species 4 all get a DBH of 8.
// </ul>
// -- The model is run for 1 timestep.
// -- The remaining trees of each tree type and species are counted.
// -- The counts are compared to expected results, give or take 5%.
//
// Second run:
// WriteMortalityXMLFile2() creates the parameter file. The file has the following
// characteristics:
//
// -- Timestep length of 5 years.
// -- BC mortality behavior, applied to seedlings, saplings, and adults of
// Species 1.
// -- GMF mortality behavior, applied to seedlings, saplings, and adults of
// Species 2.
// -- Juvenile stochastic mortality behavior, applied to seedlings and
// saplings of Species 3.
// -- Adult stochastic mortality behavior, applied to adults of Species 3.
// -- Senescence mortality behavior, applied to adults of Species 4.
// -- Adult self-thinning behavior, applied to adults of Species 5.
// -- Juvenile self-thinning behavior, applied to saplings of Species 4.
//
// The function does the following:
//
// -- 1000 trees are created of each tree species/type combination that has
// been applied to a behavior.
//   -- Seedlings of species 1 all get a value of 0 in their "Growth" data member.
//   -- Saplings of Species 1 all get a value of 0.5 in their "Growth" data member.
//   -- Adults of Species 1 all get a value of 5 in their "Growth" data member.
//   -- Seedlings of species 2 all get a value of 0 in their "Growth" data member.
//   -- Saplings of Species 2 all get a value of 0.1 in their "Growth" data member.
//   -- Adults of Species 2 all get a value of 5 in their "Growth" data member.
//   -- Adults of Species 4 all get a DBH of 100.
//   -- Adults of Species 5 all get a DBH 20.
//   -- Saplings of Species 4 all get a DBH of 8.
//
// -- The model is run for 1 timestep.
// -- The remaining trees of each tree type and species are counted.
// -- The counts are compared to expected results, give or take 5%.
//
/////////////////////////////////////////////////////////////////////////////
TEST(Mortality, TestMortality) {
  clTreePopulation * p_oPop;
  clTreeSearch *p_oAllTrees;
  clTree *p_oTree;
  float fVal;
  int **p_iTreeCount;
  int i, j, iNumSpecies, iNumTypes;

  //******************************************
  // Run 1
  //******************************************

  //Create the sim manager and load our file
  clSimManager *p_oSimManager = new clSimManager(3, 2, "");
  p_oSimManager->ReadFile( WriteMortalityXMLFile1() );
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

  //Create 100 of each kind of tree affected by mortality
  //Seedlings of Species 1
  fVal = 0;
  for (i = 0; i < 1000; i++) {
    p_oTree = p_oPop->CreateTree(1, 1, 0, clTreePopulation::seedling, 0);
    //Put a value of 0 in the "Growth" data member
    p_oTree->SetValue(p_oPop->GetFloatDataCode("Growth", p_oTree->GetSpecies(), p_oTree->GetType()), fVal);
  }

  //Saplings of Species 1
  fVal = 0.1;
  for (i = 0; i < 1000; i++) {
    p_oTree = p_oPop->CreateTree(1, 1, 0, clTreePopulation::sapling, 7);
    //Put a value of 0 in the "Growth" data member
    p_oTree->SetValue(p_oPop->GetFloatDataCode("Growth", p_oTree->GetSpecies(), p_oTree->GetType()), fVal);
  }

  //Adults of Species 1
  fVal = 5;
  for (i = 0; i < 1000; i++) {
    p_oTree = p_oPop->CreateTree(1, 1, 0, clTreePopulation::adult, 17);
    //Put a value of 0 in the "Growth" data member
    p_oTree->SetValue(p_oPop->GetFloatDataCode("Growth", p_oTree->GetSpecies(), p_oTree->GetType()), fVal);
  }

  //Seedlings of Species 3
  for (i = 0; i < 1000; i++) {
    p_oTree = p_oPop->CreateTree(1, 1, 2, clTreePopulation::seedling, 0);
  }

  //Adults of Species 3
  for (i = 0; i < 1000; i++) {
    p_oTree = p_oPop->CreateTree(1, 1, 2, clTreePopulation::adult, 17);
  }

  //Seedlings of Species 4
  for (i = 0; i < 1000; i++) {
    p_oTree = p_oPop->CreateTree(1, 1, 3, clTreePopulation::seedling, 0);
  }

  //Saplings of Species 4
  for (i = 0; i < 1000; i++) {
    p_oTree = p_oPop->CreateTree(1, 1, 3, clTreePopulation::sapling, 8);
  }

  //Adults of Species 4
  for (i = 0; i < 1000; i++) {
    p_oTree = p_oPop->CreateTree(1, 1, 3, clTreePopulation::adult, 100);
  }

  //Adults of Species 5
  for (i = 0; i < 1000; i++) {
    p_oTree = p_oPop->CreateTree(1, 1, 4, clTreePopulation::adult, 20);
  }

  //Initial conditions count
  p_oAllTrees = p_oPop->Find("all");
  p_oTree = p_oAllTrees->NextTree();
  while (p_oTree) {
    p_iTreeCount[p_oTree->GetSpecies()][p_oTree->GetType()]++;
    p_oTree = p_oAllTrees->NextTree();
  }
  EXPECT_EQ(p_iTreeCount[0][clTreePopulation::seedling], 1000);
  EXPECT_EQ(p_iTreeCount[0][clTreePopulation::sapling], 1000);
  EXPECT_EQ(p_iTreeCount[0][clTreePopulation::adult], 1000);
  EXPECT_EQ(p_iTreeCount[2][clTreePopulation::seedling], 1000);
  EXPECT_EQ(p_iTreeCount[2][clTreePopulation::adult], 1000);
  EXPECT_EQ(p_iTreeCount[3][clTreePopulation::seedling], 1000);
  EXPECT_EQ(p_iTreeCount[3][clTreePopulation::sapling], 1000);
  EXPECT_EQ(p_iTreeCount[3][clTreePopulation::adult], 1000);
  EXPECT_EQ(p_iTreeCount[4][clTreePopulation::adult], 1000);

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
  //Seedlings of Species 1
  EXPECT_LT(fabs(p_iTreeCount[0][clTreePopulation::seedling] - 367.8)/367.8, 0.05);

  //Saplings of Species 1
  EXPECT_LT(fabs(p_iTreeCount[0][clTreePopulation::sapling] - 551.8)/551.8, 0.05);

  //Adults of Species 1
  EXPECT_LT(fabs(p_iTreeCount[0][clTreePopulation::adult] - 1000)/1000, 0.05);

  //Seedlings of Species 3
  EXPECT_LT(fabs(p_iTreeCount[2][clTreePopulation::seedling] - 700)/700, 0.05);

  //Adults of Species 3
  EXPECT_EQ(p_iTreeCount[2][clTreePopulation::adult], 0);

  //Seedlings of Species 4
  EXPECT_LT(fabs(p_iTreeCount[3][clTreePopulation::seedling] - 1000)/1000, 0.05);

  //Saplings of Species 4
  EXPECT_LT(fabs(p_iTreeCount[3][clTreePopulation::sapling] - 830)/830, 0.05);

  //Adults of Species 4
  EXPECT_LT(fabs(p_iTreeCount[3][clTreePopulation::adult] - 777.2)/777.2, 0.05);

  //Adults of Species 5
  EXPECT_EQ(p_iTreeCount[4][clTreePopulation::adult], 1000);




  //******************************************
  // Run 2
  //******************************************
  //Load our second file
  p_oSimManager->ReadFile( WriteMortalityXMLFile2() );
  p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );
  iNumSpecies = p_oPop->GetNumberOfSpecies();
  iNumTypes = p_oPop->GetNumberOfTypes();

  //Set up our tree count array
  for (i = 0; i < iNumSpecies; i++) {
    for (j = 0; j < iNumTypes; j++) {
      p_iTreeCount[i][j] = 0;
    }
  }

  //Create 100 of each kind of tree affected by mortality
  //Seedlings of Species 1
  fVal = 0;
  for (i = 0; i < 1000; i++) {
    p_oTree = p_oPop->CreateTree(1, 1, 0, clTreePopulation::seedling, 0);
    //Put a value of 0 in the "Growth" data member
    p_oTree->SetValue(p_oPop->GetFloatDataCode("Growth", p_oTree->GetSpecies(), p_oTree->GetType()), fVal);
  }

  //Saplings of Species 1
  fVal = 0.5;
  for (i = 0; i < 1000; i++) {
    p_oTree = p_oPop->CreateTree(1, 1, 0, clTreePopulation::sapling, 7);
    //Put a value of 0 in the "Growth" data member
    p_oTree->SetValue(p_oPop->GetFloatDataCode("Growth", p_oTree->GetSpecies(), p_oTree->GetType()), fVal);
  }

  //Adults of Species 1
  fVal = 5;
  for (i = 0; i < 1000; i++) {
    p_oTree = p_oPop->CreateTree(1, 1, 0, clTreePopulation::adult, 17);
    //Put a value of 0 in the "Growth" data member
    p_oTree->SetValue(p_oPop->GetFloatDataCode("Growth", p_oTree->GetSpecies(), p_oTree->GetType()), fVal);
  }

  //Seedlings of Species 2
  fVal = 0;
  for (i = 0; i < 1000; i++) {
    p_oTree = p_oPop->CreateTree(1, 1, 1, clTreePopulation::seedling, 0);
    //Put a value of 0 in the "Growth" data member
    p_oTree->SetValue(p_oPop->GetFloatDataCode("Growth", p_oTree->GetSpecies(), p_oTree->GetType()), fVal);
  }

  //Saplings of Species 2
  fVal = 0.1;
  for (i = 0; i < 1000; i++) {
    p_oTree = p_oPop->CreateTree(1, 1, 1, clTreePopulation::sapling, 7);
    //Put a value of 0 in the "Growth" data member
    p_oTree->SetValue(p_oPop->GetFloatDataCode("Growth", p_oTree->GetSpecies(), p_oTree->GetType()), fVal);
  }

  //Adults of Species 2
  fVal = 5;
  for (i = 0; i < 1000; i++) {
    p_oTree = p_oPop->CreateTree(1, 1, 1, clTreePopulation::adult, 17);
    //Put a value of 0 in the "Growth" data member
    p_oTree->SetValue(p_oPop->GetFloatDataCode("Growth", p_oTree->GetSpecies(), p_oTree->GetType()), fVal);
  }

  //Seedlings of Species 3
  for (i = 0; i < 1000; i++) {
    p_oTree = p_oPop->CreateTree(1, 1, 2, clTreePopulation::seedling, 0);
  }

  //Adults of Species 3
  for (i = 0; i < 1000; i++) {
    p_oTree = p_oPop->CreateTree(1, 1, 2, clTreePopulation::adult, 17);
  }

  //Seedlings of Species 4
  for (i = 0; i < 1000; i++) {
    p_oTree = p_oPop->CreateTree(1, 1, 3, clTreePopulation::seedling, 0);
  }

  //Saplings of Species 4
  for (i = 0; i < 1000; i++) {
    p_oTree = p_oPop->CreateTree(1, 1, 3, clTreePopulation::sapling, 8);
  }

  //Adults of Species 4
  for (i = 0; i < 1000; i++) {
    p_oTree = p_oPop->CreateTree(1, 1, 3, clTreePopulation::adult, 100);
  }

  //Adults of Species 5
  for (i = 0; i < 1000; i++) {
    p_oTree = p_oPop->CreateTree(1, 1, 4, clTreePopulation::adult, 20);
  }

  //Run for one timestep - everything except the light behavior
  for (i = 1; i < p_oSimManager->GetNumberOfBehaviors(); i++)
    p_oSimManager->GetBehaviorObject(i)->Action();

  //Count the remaining trees
  p_oAllTrees = p_oPop->Find("all");
  p_oTree = p_oAllTrees->NextTree();
  while (p_oTree) {
    p_iTreeCount[p_oTree->GetSpecies()][p_oTree->GetType()]++;
    p_oTree = p_oAllTrees->NextTree();
  }

  //Make sure they are as expected
  //Seedlings of Species 1
  EXPECT_LT(fabs(p_iTreeCount[0][clTreePopulation::seedling] - 6.73), 10);

  //Saplings of Species 1
  EXPECT_LT(fabs(p_iTreeCount[0][clTreePopulation::sapling] - 689.7)/689.7, 0.05);

  //Adults of Species 1
  EXPECT_LT(fabs(p_iTreeCount[0][clTreePopulation::adult] - 1000)/1000, 0.05);

  //Seedlings of Species 2
  EXPECT_EQ(p_iTreeCount[1][clTreePopulation::seedling], 0);

  //Saplings of Species 2
  EXPECT_LT(fabs(p_iTreeCount[1][clTreePopulation::sapling] - 240.45)/240.45, 0.1);

  //Adults of Species 3
  EXPECT_LT(fabs(p_iTreeCount[1][clTreePopulation::adult] - 1000)/1000, 0.05);

  //Seedlings of Species 3 - get more leeway because the number's small
  EXPECT_LT(fabs(p_iTreeCount[2][clTreePopulation::seedling] - 168.07)/168.07, 0.2);

  //Adults of Species 3
  EXPECT_EQ(p_iTreeCount[2][clTreePopulation::adult], 0);

  //Seedlings of Species 4
  EXPECT_LT(fabs(p_iTreeCount[3][clTreePopulation::seedling] - 1000)/1000, 0.05);

  //Saplings of Species 4
  EXPECT_LT(fabs(p_iTreeCount[3][clTreePopulation::sapling] - 393.9)/393.9, 0.07);

  //Adults of Species 4
  EXPECT_LT(fabs(p_iTreeCount[3][clTreePopulation::adult] - 283.7)/283.7, 0.08);

  //Adults of Species 5
  EXPECT_EQ(p_iTreeCount[4][clTreePopulation::adult], 1000);



  //Cleanup
  for (i = 0; i < iNumSpecies; i++) delete[] p_iTreeCount[i];
    delete[] p_iTreeCount;

  delete p_oSimManager;
}

/////////////////////////////////////////////////////////////////////////////
// WriteMortalityXMLFile1()
/////////////////////////////////////////////////////////////////////////////
const char* WriteMortalityXMLFile1() {
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
       << "<randomSeed>-1</randomSeed>"
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
       << "<tr_species speciesName=\"Species_4\" />"
       << "<tr_species speciesName=\"Species_5\" />"
       << "</tr_speciesList>"
       << "<tr_seedDiam10Cm>0.1</tr_seedDiam10Cm>"
       << "<tr_minAdultDBH>"
       << "<tr_madVal species=\"Species_1\">10.0</tr_madVal>"
       << "<tr_madVal species=\"Species_2\">10.0</tr_madVal>"
       << "<tr_madVal species=\"Species_3\">10.0</tr_madVal>"
       << "<tr_madVal species=\"Species_4\">10.0</tr_madVal>"
       << "<tr_madVal species=\"Species_5\">10.0</tr_madVal>"
       << "</tr_minAdultDBH>"
       << "<tr_maxSeedlingHeight>"
       << "<tr_mshVal species=\"Species_1\">1.35</tr_mshVal>"
       << "<tr_mshVal species=\"Species_2\">1.35</tr_mshVal>"
       << "<tr_mshVal species=\"Species_3\">1.35</tr_mshVal>"
       << "<tr_mshVal species=\"Species_4\">1.35</tr_mshVal>"
       << "<tr_mshVal species=\"Species_5\">1.35</tr_mshVal>"
       << "</tr_maxSeedlingHeight>"
       << "</trees>"
       << "<allometry>"
       << "<tr_canopyHeight>"
       << "<tr_chVal species=\"Species_1\">40.0</tr_chVal>"
       << "<tr_chVal species=\"Species_2\">40.0</tr_chVal>"
       << "<tr_chVal species=\"Species_3\">40.0</tr_chVal>"
       << "<tr_chVal species=\"Species_4\">40.0</tr_chVal>"
       << "<tr_chVal species=\"Species_5\">40.0</tr_chVal>"
       << "</tr_canopyHeight>"
       << "<tr_stdAsympCrownRad>"
       << "<tr_sacrVal species=\"Species_1\">0.7</tr_sacrVal>"
       << "<tr_sacrVal species=\"Species_2\">0.7</tr_sacrVal>"
       << "<tr_sacrVal species=\"Species_3\">0.7</tr_sacrVal>"
       << "<tr_sacrVal species=\"Species_4\">0.7</tr_sacrVal>"
       << "<tr_sacrVal species=\"Species_5\">0.7</tr_sacrVal>"
       << "</tr_stdAsympCrownRad>"
       << "<tr_stdCrownRadExp>"
       << "<tr_screVal species=\"Species_1\">1.0</tr_screVal>"
       << "<tr_screVal species=\"Species_2\">1.0</tr_screVal>"
       << "<tr_screVal species=\"Species_3\">1.0</tr_screVal>"
       << "<tr_screVal species=\"Species_4\">1.0</tr_screVal>"
       << "<tr_screVal species=\"Species_5\">1.0</tr_screVal>"
       << "</tr_stdCrownRadExp>"
       << "<tr_conversionDiam10ToDBH>"
       << "<tr_cdtdVal species=\"Species_1\">0.7</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_2\">0.7</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_3\">0.7</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_4\">0.7</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_5\">0.7</tr_cdtdVal>"
       << "</tr_conversionDiam10ToDBH>"
       << "<tr_interceptDiam10ToDBH>"
       << "<tr_idtdVal species=\"Species_1\">0</tr_idtdVal>"
       << "<tr_idtdVal species=\"Species_2\">0</tr_idtdVal>"
       << "<tr_idtdVal species=\"Species_3\">0</tr_idtdVal>"
       << "<tr_idtdVal species=\"Species_4\">0</tr_idtdVal>"
       << "<tr_idtdVal species=\"Species_5\">0</tr_idtdVal>"
       << "</tr_interceptDiam10ToDBH>"
       << "<tr_stdAsympCrownHt>"
       << "<tr_sachVal species=\"Species_1\">0.7</tr_sachVal>"
       << "<tr_sachVal species=\"Species_2\">0.7</tr_sachVal>"
       << "<tr_sachVal species=\"Species_3\">0.7</tr_sachVal>"
       << "<tr_sachVal species=\"Species_4\">0.7</tr_sachVal>"
       << "<tr_sachVal species=\"Species_5\">0.7</tr_sachVal>"
       << "</tr_stdAsympCrownHt>"
       << "<tr_stdCrownHtExp>"
       << "<tr_scheVal species=\"Species_1\">1.0</tr_scheVal>"
       << "<tr_scheVal species=\"Species_2\">1.0</tr_scheVal>"
       << "<tr_scheVal species=\"Species_3\">1.0</tr_scheVal>"
       << "<tr_scheVal species=\"Species_4\">1.0</tr_scheVal>"
       << "<tr_scheVal species=\"Species_5\">1.0</tr_scheVal>"
       << "</tr_stdCrownHtExp>"
       << "<tr_slopeOfHeight-Diam10>"
       << "<tr_sohdVal species=\"Species_1\">0.03</tr_sohdVal>"
       << "<tr_sohdVal species=\"Species_2\">0.03</tr_sohdVal>"
       << "<tr_sohdVal species=\"Species_3\">0.03</tr_sohdVal>"
       << "<tr_sohdVal species=\"Species_4\">0.03</tr_sohdVal>"
       << "<tr_sohdVal species=\"Species_5\">0.03</tr_sohdVal>"
       << "</tr_slopeOfHeight-Diam10>"
       << "<tr_slopeOfAsymHeight>"
       << "<tr_soahVal species=\"Species_1\">0.7</tr_soahVal>"
       << "<tr_soahVal species=\"Species_2\">0.7</tr_soahVal>"
       << "<tr_soahVal species=\"Species_3\">0.7</tr_soahVal>"
       << "<tr_soahVal species=\"Species_4\">0.7</tr_soahVal>"
       << "<tr_soahVal species=\"Species_5\">0.7</tr_soahVal>"
       << "</tr_slopeOfAsymHeight>"
       << "<tr_whatSeedlingHeightDiam>"
       << "<tr_wsehdVal species=\"Species_1\">0</tr_wsehdVal>"
       << "<tr_wsehdVal species=\"Species_2\">0</tr_wsehdVal>"
       << "<tr_wsehdVal species=\"Species_3\">0</tr_wsehdVal>"
       << "<tr_wsehdVal species=\"Species_4\">0</tr_wsehdVal>"
       << "<tr_wsehdVal species=\"Species_5\">0</tr_wsehdVal>"
       << "</tr_whatSeedlingHeightDiam>"
       << "<tr_whatSaplingHeightDiam>"
       << "<tr_wsahdVal species=\"Species_1\">0</tr_wsahdVal>"
       << "<tr_wsahdVal species=\"Species_2\">0</tr_wsahdVal>"
       << "<tr_wsahdVal species=\"Species_3\">0</tr_wsahdVal>"
       << "<tr_wsahdVal species=\"Species_4\">0</tr_wsahdVal>"
       << "<tr_wsahdVal species=\"Species_5\">0</tr_wsahdVal>"
       << "</tr_whatSaplingHeightDiam>"
       << "<tr_whatAdultHeightDiam>"
       << "<tr_wahdVal species=\"Species_1\">0</tr_wahdVal>"
       << "<tr_wahdVal species=\"Species_2\">0</tr_wahdVal>"
       << "<tr_wahdVal species=\"Species_3\">0</tr_wahdVal>"
       << "<tr_wahdVal species=\"Species_4\">0</tr_wahdVal>"
       << "<tr_wahdVal species=\"Species_5\">0</tr_wahdVal>"
       << "</tr_whatAdultHeightDiam>"
       << "<tr_whatAdultCrownRadDiam>"
       << "<tr_wacrdVal species=\"Species_1\">0</tr_wacrdVal>"
       << "<tr_wacrdVal species=\"Species_2\">0</tr_wacrdVal>"
       << "<tr_wacrdVal species=\"Species_3\">0</tr_wacrdVal>"
       << "<tr_wacrdVal species=\"Species_4\">0</tr_wacrdVal>"
       << "<tr_wacrdVal species=\"Species_5\">0</tr_wacrdVal>"
       << "</tr_whatAdultCrownRadDiam>"
       << "<tr_whatAdultCrownHeightHeight>"
       << "<tr_wachhVal species=\"Species_1\">0</tr_wachhVal>"
       << "<tr_wachhVal species=\"Species_2\">0</tr_wachhVal>"
       << "<tr_wachhVal species=\"Species_3\">0</tr_wachhVal>"
       << "<tr_wachhVal species=\"Species_4\">0</tr_wachhVal>"
       << "<tr_wachhVal species=\"Species_5\">0</tr_wachhVal>"
       << "</tr_whatAdultCrownHeightHeight>"
       << "<tr_whatSaplingCrownRadDiam>"
       << "<tr_wscrdVal species=\"Species_1\">0</tr_wscrdVal>"
       << "<tr_wscrdVal species=\"Species_2\">0</tr_wscrdVal>"
       << "<tr_wscrdVal species=\"Species_3\">0</tr_wscrdVal>"
       << "<tr_wscrdVal species=\"Species_4\">0</tr_wscrdVal>"
       << "<tr_wscrdVal species=\"Species_5\">0</tr_wscrdVal>"
       << "</tr_whatSaplingCrownRadDiam>"
       << "<tr_whatSaplingCrownHeightHeight>"
       << "<tr_wschhVal species=\"Species_1\">0</tr_wschhVal>"
       << "<tr_wschhVal species=\"Species_2\">0</tr_wschhVal>"
       << "<tr_wschhVal species=\"Species_3\">0</tr_wschhVal>"
       << "<tr_wschhVal species=\"Species_4\">0</tr_wschhVal>"
       << "<tr_wschhVal species=\"Species_5\">0</tr_wschhVal>"
       << "</tr_whatSaplingCrownHeightHeight>"
       << "</allometry>"
       << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>ConstRadialGrowth</behaviorName>"
       << "<version>1.0</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Seedling\" />"
       << "<applyTo species=\"Species_2\" type=\"Seedling\" />"
       << "<applyTo species=\"Species_3\" type=\"Seedling\" />"
       << "<applyTo species=\"Species_4\" type=\"Seedling\" />"
       << "<applyTo species=\"Species_5\" type=\"Seedling\" />"
       << "<applyTo species=\"Species_1\" type=\"Sapling\" />"
       << "<applyTo species=\"Species_2\" type=\"Sapling\" />"
       << "<applyTo species=\"Species_3\" type=\"Sapling\" />"
       << "<applyTo species=\"Species_4\" type=\"Sapling\" />"
       << "<applyTo species=\"Species_5\" type=\"Sapling\" />"
       << "<applyTo species=\"Species_1\" type=\"Adult\" />"
       << "<applyTo species=\"Species_2\" type=\"Adult\" />"
       << "<applyTo species=\"Species_3\" type=\"Adult\" />"
       << "<applyTo species=\"Species_4\" type=\"Adult\" />"
       << "<applyTo species=\"Species_5\" type=\"Adult\" />"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>BCMortality</behaviorName>"
       << "<version>1.0</version>"
       << "<listPosition>2</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Seedling\" />"
       << "<applyTo species=\"Species_1\" type=\"Sapling\" />"
       << "<applyTo species=\"Species_1\" type=\"Adult\" />"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>SelfThinning</behaviorName>"
       << "<version>1.0</version>"
       << "<listPosition>3</listPosition>"
       << "<applyTo species=\"Species_5\" type=\"Adult\" />"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>SelfThinning</behaviorName>"
       << "<version>1.0</version>"
       << "<listPosition>4</listPosition>"
       << "<applyTo species=\"Species_4\" type=\"Sapling\" />"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>Senescence</behaviorName>"
       << "<version>1.0</version>"
       << "<listPosition>5</listPosition>"
       << "<applyTo species=\"Species_4\" type=\"Adult\" />"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>StochasticMortality</behaviorName>"
       << "<version>1.0</version>"
       << "<listPosition>6</listPosition>"
       << "<applyTo species=\"Species_3\" type=\"Adult\" />"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>StochasticMortality</behaviorName>"
       << "<version>1.0</version>"
       << "<listPosition>7</listPosition>"
       << "<applyTo species=\"Species_3\" type=\"Seedling\" />"
       << "<applyTo species=\"Species_4\" type=\"Seedling\" />"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>RemoveDead</behaviorName>"
       << "<version>2.0</version>"
       << "<listPosition>8</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Seedling\" />"
       << "<applyTo species=\"Species_1\" type=\"Sapling\" />"
       << "<applyTo species=\"Species_1\" type=\"Adult\" />"
       << "<applyTo species=\"Species_3\" type=\"Seedling\" />"
       << "<applyTo species=\"Species_4\" type=\"Seedling\" />"
       << "<applyTo species=\"Species_3\" type=\"Adult\" />"
       << "<applyTo species=\"Species_4\" type=\"Adult\" />"
       << "<applyTo species=\"Species_4\" type=\"Sapling\" />"
       << "<applyTo species=\"Species_5\" type=\"Adult\" />"
       << "</behavior>"
       << "</behaviorList>"
       << "<ConstRadialGrowth1>"
       << "<gr_adultConstRadialInc>"
       << "<gr_acriVal species=\"Species_3\">0.0</gr_acriVal>"
       << "<gr_acriVal species=\"Species_4\">0.0</gr_acriVal>"
       << "<gr_acriVal species=\"Species_1\">0.0</gr_acriVal>"
       << "<gr_acriVal species=\"Species_2\">0.0</gr_acriVal>"
       << "<gr_acriVal species=\"Species_5\">0.0</gr_acriVal>"
       << "</gr_adultConstRadialInc>"
       << "</ConstRadialGrowth1>"
       << "<StochasticMortality7>"
       << "<mo_stochasticMortRate>"
       << "<mo_smrVal species=\"Species_3\">0.3</mo_smrVal>"
       << "<mo_smrVal species=\"Species_4\">0.0</mo_smrVal>"
       << "</mo_stochasticMortRate>"
       << "</StochasticMortality7>"
       << "<StochasticMortality6>"
       << "<mo_stochasticMortRate>"
       << "<mo_smrVal species=\"Species_3\">1.0</mo_smrVal>"
       << "</mo_stochasticMortRate>"
       << "</StochasticMortality6>"
       << "<BCMortality2>"
       << "<mo_mortAtZeroGrowth>"
       << "<mo_mazgVal species=\"Species_1\">1.0</mo_mazgVal>"
       << "</mo_mortAtZeroGrowth>"
       << "<mo_lightDependentMortality>"
       << "<mo_ldmVal species=\"Species_1\">5.2</mo_ldmVal>"
       << "</mo_lightDependentMortality>"
       << "</BCMortality2>"
       << "<SelfThinning4>"
       << "<mo_selfThinSlope>"
       << "<mo_stsVal species=\"Species_4\">0.02</mo_stsVal>"
       << "</mo_selfThinSlope>"
       << "<mo_selfThinIntercept>"
       << "<mo_stiVal species=\"Species_4\">0.01</mo_stiVal>"
       << "</mo_selfThinIntercept>"
       << "<mo_selfThinMaxDbh>"
       << "<mo_stmdVal species=\"Species_4\">15.0</mo_stmdVal>"
       << "</mo_selfThinMaxDbh>"
       << "</SelfThinning4>"
       << "<SelfThinning3>"
       << "<mo_selfThinSlope>"
       << "<mo_stsVal species=\"Species_5\">0.02</mo_stsVal>"
       << "</mo_selfThinSlope>"
       << "<mo_selfThinIntercept>"
       << "<mo_stiVal species=\"Species_5\">0.01</mo_stiVal>"
       << "</mo_selfThinIntercept>"
       << "<mo_selfThinMaxDbh>"
       << "<mo_stmdVal species=\"Species_5\">15.0</mo_stmdVal>"
       << "</mo_selfThinMaxDbh>"
       << "</SelfThinning3>"
       << "<Senescence5>"
       << "<mo_senescenceAlpha>"
       << "<mo_saVal species=\"Species_4\">-8.0</mo_saVal>"
       << "</mo_senescenceAlpha>"
       << "<mo_senescenceBeta>"
       << "<mo_sbVal species=\"Species_4\">0.135</mo_sbVal>"
       << "</mo_senescenceBeta>"
       << "<mo_dbhAtOnsetOfSenescence>"
       << "<mo_daoosVal species=\"Species_4\">50.0</mo_daoosVal>"
       << "</mo_dbhAtOnsetOfSenescence>"
       << "<mo_dbhAtAsympMaxMort>110</mo_dbhAtAsympMaxMort>"
       << "</Senescence5>"
       << "</paramFile>";
  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteMortalityXMLFile2()
/////////////////////////////////////////////////////////////////////////////
const char* WriteMortalityXMLFile2()
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
       << "<randomSeed>-1</randomSeed>"
       << "<yearsPerTimestep>5.0</yearsPerTimestep>"
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
       << "<tr_species speciesName=\"Species_4\" />"
       << "<tr_species speciesName=\"Species_5\" />"
       << "</tr_speciesList>"
       << "<tr_seedDiam10Cm>0.1</tr_seedDiam10Cm>"
       << "<tr_minAdultDBH>"
       << "<tr_madVal species=\"Species_1\">10.0</tr_madVal>"
       << "<tr_madVal species=\"Species_2\">10.0</tr_madVal>"
       << "<tr_madVal species=\"Species_3\">10.0</tr_madVal>"
       << "<tr_madVal species=\"Species_4\">10.0</tr_madVal>"
       << "<tr_madVal species=\"Species_5\">10.0</tr_madVal>"
       << "</tr_minAdultDBH>"
       << "<tr_maxSeedlingHeight>"
       << "<tr_mshVal species=\"Species_1\">1.35</tr_mshVal>"
       << "<tr_mshVal species=\"Species_2\">1.35</tr_mshVal>"
       << "<tr_mshVal species=\"Species_3\">1.35</tr_mshVal>"
       << "<tr_mshVal species=\"Species_4\">1.35</tr_mshVal>"
       << "<tr_mshVal species=\"Species_5\">1.35</tr_mshVal>"
       << "</tr_maxSeedlingHeight>"
       << "</trees>"
       << "<allometry>"
       << "<tr_canopyHeight>"
       << "<tr_chVal species=\"Species_1\">40.0</tr_chVal>"
       << "<tr_chVal species=\"Species_2\">40.0</tr_chVal>"
       << "<tr_chVal species=\"Species_3\">40.0</tr_chVal>"
       << "<tr_chVal species=\"Species_4\">40.0</tr_chVal>"
       << "<tr_chVal species=\"Species_5\">40.0</tr_chVal>"
       << "</tr_canopyHeight>"
       << "<tr_stdAsympCrownRad>"
       << "<tr_sacrVal species=\"Species_1\">0.7</tr_sacrVal>"
       << "<tr_sacrVal species=\"Species_2\">0.7</tr_sacrVal>"
       << "<tr_sacrVal species=\"Species_3\">0.7</tr_sacrVal>"
       << "<tr_sacrVal species=\"Species_4\">0.7</tr_sacrVal>"
       << "<tr_sacrVal species=\"Species_5\">0.7</tr_sacrVal>"
       << "</tr_stdAsympCrownRad>"
       << "<tr_stdCrownRadExp>"
       << "<tr_screVal species=\"Species_1\">1.0</tr_screVal>"
       << "<tr_screVal species=\"Species_2\">1.0</tr_screVal>"
       << "<tr_screVal species=\"Species_3\">1.0</tr_screVal>"
       << "<tr_screVal species=\"Species_4\">1.0</tr_screVal>"
       << "<tr_screVal species=\"Species_5\">1.0</tr_screVal>"
       << "</tr_stdCrownRadExp>"
       << "<tr_conversionDiam10ToDBH>"
       << "<tr_cdtdVal species=\"Species_1\">0.7</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_2\">0.7</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_3\">0.7</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_4\">0.7</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_5\">0.7</tr_cdtdVal>"
       << "</tr_conversionDiam10ToDBH>"
       << "<tr_interceptDiam10ToDBH>"
       << "<tr_idtdVal species=\"Species_1\">0</tr_idtdVal>"
       << "<tr_idtdVal species=\"Species_2\">0</tr_idtdVal>"
       << "<tr_idtdVal species=\"Species_3\">0</tr_idtdVal>"
       << "<tr_idtdVal species=\"Species_4\">0</tr_idtdVal>"
       << "<tr_idtdVal species=\"Species_5\">0</tr_idtdVal>"
       << "</tr_interceptDiam10ToDBH>"
       << "<tr_stdAsympCrownHt>"
       << "<tr_sachVal species=\"Species_1\">0.7</tr_sachVal>"
       << "<tr_sachVal species=\"Species_2\">0.7</tr_sachVal>"
       << "<tr_sachVal species=\"Species_3\">0.7</tr_sachVal>"
       << "<tr_sachVal species=\"Species_4\">0.7</tr_sachVal>"
       << "<tr_sachVal species=\"Species_5\">0.7</tr_sachVal>"
       << "</tr_stdAsympCrownHt>"
       << "<tr_stdCrownHtExp>"
       << "<tr_scheVal species=\"Species_1\">1.0</tr_scheVal>"
       << "<tr_scheVal species=\"Species_2\">1.0</tr_scheVal>"
       << "<tr_scheVal species=\"Species_3\">1.0</tr_scheVal>"
       << "<tr_scheVal species=\"Species_4\">1.0</tr_scheVal>"
       << "<tr_scheVal species=\"Species_5\">1.0</tr_scheVal>"
       << "</tr_stdCrownHtExp>"
       << "<tr_slopeOfHeight-Diam10>"
       << "<tr_sohdVal species=\"Species_1\">0.03</tr_sohdVal>"
       << "<tr_sohdVal species=\"Species_2\">0.03</tr_sohdVal>"
       << "<tr_sohdVal species=\"Species_3\">0.03</tr_sohdVal>"
       << "<tr_sohdVal species=\"Species_4\">0.03</tr_sohdVal>"
       << "<tr_sohdVal species=\"Species_5\">0.03</tr_sohdVal>"
       << "</tr_slopeOfHeight-Diam10>"
       << "<tr_slopeOfAsymHeight>"
       << "<tr_soahVal species=\"Species_1\">0.7</tr_soahVal>"
       << "<tr_soahVal species=\"Species_2\">0.7</tr_soahVal>"
       << "<tr_soahVal species=\"Species_3\">0.7</tr_soahVal>"
       << "<tr_soahVal species=\"Species_4\">0.7</tr_soahVal>"
       << "<tr_soahVal species=\"Species_5\">0.7</tr_soahVal>"
       << "</tr_slopeOfAsymHeight>"
       << "<tr_whatSeedlingHeightDiam>"
       << "<tr_wsehdVal species=\"Species_1\">0</tr_wsehdVal>"
       << "<tr_wsehdVal species=\"Species_2\">0</tr_wsehdVal>"
       << "<tr_wsehdVal species=\"Species_3\">0</tr_wsehdVal>"
       << "<tr_wsehdVal species=\"Species_4\">0</tr_wsehdVal>"
       << "<tr_wsehdVal species=\"Species_5\">0</tr_wsehdVal>"
       << "</tr_whatSeedlingHeightDiam>"
       << "<tr_whatSaplingHeightDiam>"
       << "<tr_wsahdVal species=\"Species_1\">0</tr_wsahdVal>"
       << "<tr_wsahdVal species=\"Species_2\">0</tr_wsahdVal>"
       << "<tr_wsahdVal species=\"Species_3\">0</tr_wsahdVal>"
       << "<tr_wsahdVal species=\"Species_4\">0</tr_wsahdVal>"
       << "<tr_wsahdVal species=\"Species_5\">0</tr_wsahdVal>"
       << "</tr_whatSaplingHeightDiam>"
       << "<tr_whatAdultHeightDiam>"
       << "<tr_wahdVal species=\"Species_1\">0</tr_wahdVal>"
       << "<tr_wahdVal species=\"Species_2\">0</tr_wahdVal>"
       << "<tr_wahdVal species=\"Species_3\">0</tr_wahdVal>"
       << "<tr_wahdVal species=\"Species_4\">0</tr_wahdVal>"
       << "<tr_wahdVal species=\"Species_5\">0</tr_wahdVal>"
       << "</tr_whatAdultHeightDiam>"
       << "<tr_whatAdultCrownRadDiam>"
       << "<tr_wacrdVal species=\"Species_1\">0</tr_wacrdVal>"
       << "<tr_wacrdVal species=\"Species_2\">0</tr_wacrdVal>"
       << "<tr_wacrdVal species=\"Species_3\">0</tr_wacrdVal>"
       << "<tr_wacrdVal species=\"Species_4\">0</tr_wacrdVal>"
       << "<tr_wacrdVal species=\"Species_5\">0</tr_wacrdVal>"
       << "</tr_whatAdultCrownRadDiam>"
       << "<tr_whatAdultCrownHeightHeight>"
       << "<tr_wachhVal species=\"Species_1\">0</tr_wachhVal>"
       << "<tr_wachhVal species=\"Species_2\">0</tr_wachhVal>"
       << "<tr_wachhVal species=\"Species_3\">0</tr_wachhVal>"
       << "<tr_wachhVal species=\"Species_4\">0</tr_wachhVal>"
       << "<tr_wachhVal species=\"Species_5\">0</tr_wachhVal>"
       << "</tr_whatAdultCrownHeightHeight>"
       << "<tr_whatSaplingCrownRadDiam>"
       << "<tr_wscrdVal species=\"Species_1\">0</tr_wscrdVal>"
       << "<tr_wscrdVal species=\"Species_2\">0</tr_wscrdVal>"
       << "<tr_wscrdVal species=\"Species_3\">0</tr_wscrdVal>"
       << "<tr_wscrdVal species=\"Species_4\">0</tr_wscrdVal>"
       << "<tr_wscrdVal species=\"Species_5\">0</tr_wscrdVal>"
       << "</tr_whatSaplingCrownRadDiam>"
       << "<tr_whatSaplingCrownHeightHeight>"
       << "<tr_wschhVal species=\"Species_1\">0</tr_wschhVal>"
       << "<tr_wschhVal species=\"Species_2\">0</tr_wschhVal>"
       << "<tr_wschhVal species=\"Species_3\">0</tr_wschhVal>"
       << "<tr_wschhVal species=\"Species_4\">0</tr_wschhVal>"
       << "<tr_wschhVal species=\"Species_5\">0</tr_wschhVal>"
       << "</tr_whatSaplingCrownHeightHeight>"
       << "</allometry>"
       << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>ConstRadialGrowth</behaviorName>"
       << "<version>1.0</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Seedling\" />"
       << "<applyTo species=\"Species_2\" type=\"Seedling\" />"
       << "<applyTo species=\"Species_3\" type=\"Seedling\" />"
       << "<applyTo species=\"Species_4\" type=\"Seedling\" />"
       << "<applyTo species=\"Species_5\" type=\"Seedling\" />"
       << "<applyTo species=\"Species_1\" type=\"Sapling\" />"
       << "<applyTo species=\"Species_2\" type=\"Sapling\" />"
       << "<applyTo species=\"Species_3\" type=\"Sapling\" />"
       << "<applyTo species=\"Species_4\" type=\"Sapling\" />"
       << "<applyTo species=\"Species_5\" type=\"Sapling\" />"
       << "<applyTo species=\"Species_1\" type=\"Adult\" />"
       << "<applyTo species=\"Species_2\" type=\"Adult\" />"
       << "<applyTo species=\"Species_3\" type=\"Adult\" />"
       << "<applyTo species=\"Species_4\" type=\"Adult\" />"
       << "<applyTo species=\"Species_5\" type=\"Adult\" />"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>BCMortality</behaviorName>"
       << "<version>1.0</version>"
       << "<listPosition>2</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Seedling\" />"
       << "<applyTo species=\"Species_1\" type=\"Sapling\" />"
       << "<applyTo species=\"Species_1\" type=\"Adult\" />"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>GMFMortality</behaviorName>"
       << "<version>1.0</version>"
       << "<listPosition>3</listPosition>"
       << "<applyTo species=\"Species_2\" type=\"Seedling\" />"
       << "<applyTo species=\"Species_2\" type=\"Sapling\" />"
       << "<applyTo species=\"Species_2\" type=\"Adult\" />"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>SelfThinning</behaviorName>"
       << "<version>1.0</version>"
       << "<listPosition>4</listPosition>"
       << "<applyTo species=\"Species_5\" type=\"Adult\" />"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>SelfThinning</behaviorName>"
       << "<version>1.0</version>"
       << "<listPosition>5</listPosition>"
       << "<applyTo species=\"Species_4\" type=\"Sapling\" />"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>Senescence</behaviorName>"
       << "<version>1.0</version>"
       << "<listPosition>6</listPosition>"
       << "<applyTo species=\"Species_4\" type=\"Adult\" />"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>StochasticMortality</behaviorName>"
       << "<version>1.0</version>"
       << "<listPosition>7</listPosition>"
       << "<applyTo species=\"Species_3\" type=\"Adult\" />"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>StochasticMortality</behaviorName>"
       << "<version>1.0</version>"
       << "<listPosition>8</listPosition>"
       << "<applyTo species=\"Species_3\" type=\"Seedling\" />"
       << "<applyTo species=\"Species_4\" type=\"Seedling\" />"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>RemoveDead</behaviorName>"
       << "<version>2.0</version>"
       << "<listPosition>9</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Seedling\" />"
       << "<applyTo species=\"Species_1\" type=\"Sapling\" />"
       << "<applyTo species=\"Species_1\" type=\"Adult\" />"
       << "<applyTo species=\"Species_2\" type=\"Seedling\" />"
       << "<applyTo species=\"Species_2\" type=\"Sapling\" />"
       << "<applyTo species=\"Species_2\" type=\"Adult\" />"
       << "<applyTo species=\"Species_3\" type=\"Seedling\" />"
       << "<applyTo species=\"Species_4\" type=\"Seedling\" />"
       << "<applyTo species=\"Species_3\" type=\"Adult\" />"
       << "<applyTo species=\"Species_4\" type=\"Adult\" />"
       << "<applyTo species=\"Species_4\" type=\"Sapling\" />"
       << "<applyTo species=\"Species_5\" type=\"Adult\" />"
       << "</behavior>"
       << "</behaviorList>"
       << "<ConstRadialGrowth1>"
       << "<gr_adultConstRadialInc>"
       << "<gr_acriVal species=\"Species_3\">0.0</gr_acriVal>"
       << "<gr_acriVal species=\"Species_4\">0.0</gr_acriVal>"
       << "<gr_acriVal species=\"Species_1\">0.0</gr_acriVal>"
       << "<gr_acriVal species=\"Species_2\">0.0</gr_acriVal>"
       << "<gr_acriVal species=\"Species_5\">0.0</gr_acriVal>"
       << "</gr_adultConstRadialInc>"
       << "</ConstRadialGrowth1>"
       << "<SelfThinning5>"
       << "<mo_selfThinSlope>"
       << "<mo_stsVal species=\"Species_4\">0.02</mo_stsVal>"
       << "</mo_selfThinSlope>"
       << "<mo_selfThinIntercept>"
       << "<mo_stiVal species=\"Species_4\">0.01</mo_stiVal>"
       << "</mo_selfThinIntercept>"
       << "<mo_selfThinMaxDbh>"
       << "<mo_stmdVal species=\"Species_4\">15.0</mo_stmdVal>"
       << "</mo_selfThinMaxDbh>"
       << "</SelfThinning5>"
       << "<SelfThinning4>"
       << "<mo_selfThinSlope>"
       << "<mo_stsVal species=\"Species_5\">0.02</mo_stsVal>"
       << "</mo_selfThinSlope>"
       << "<mo_selfThinIntercept>"
       << "<mo_stiVal species=\"Species_5\">0.01</mo_stiVal>"
       << "</mo_selfThinIntercept>"
       << "<mo_selfThinMaxDbh>"
       << "<mo_stmdVal species=\"Species_5\">15.0</mo_stmdVal>"
       << "</mo_selfThinMaxDbh>"
       << "</SelfThinning4>"
       << "<BCMortality2>"
       << "<mo_mortAtZeroGrowth>"
       << "<mo_mazgVal species=\"Species_1\">1.0</mo_mazgVal>"
       << "</mo_mortAtZeroGrowth>"
       << "<mo_lightDependentMortality>"
       << "<mo_ldmVal species=\"Species_1\">5.2</mo_ldmVal>"
       << "</mo_lightDependentMortality>"
       << "</BCMortality2>"
       << "<GMFMortality3>"
       << "<mo_mortAtZeroGrowth>"
       << "<mo_mazgVal species=\"Species_2\">0.99</mo_mazgVal>"
       << "</mo_mortAtZeroGrowth>"
       << "<mo_lightDependentMortality>"
       << "<mo_ldmVal species=\"Species_2\">6.64</mo_ldmVal>"
       << "</mo_lightDependentMortality>"
       << "</GMFMortality3>"
       << "<SelfThinning4>"
       << "<mo_selfThinSlope>"
       << "<mo_stsVal species=\"Species_4\">0.02</mo_stsVal>"
       << "</mo_selfThinSlope>"
       << "<mo_selfThinIntercept>"
       << "<mo_stiVal species=\"Species_4\">0.01</mo_stiVal>"
       << "</mo_selfThinIntercept>"
       << "<mo_selfThinMaxDbh>"
       << "<mo_stmdVal species=\"Species_5\">15.0</mo_stmdVal>"
       << "</mo_selfThinMaxDbh>"
       << "</SelfThinning4>"
       << "<SelfThinning3>"
       << "<mo_selfThinSlope>"
       << "<mo_stsVal species=\"Species_5\">0.02</mo_stsVal>"
       << "</mo_selfThinSlope>"
       << "<mo_selfThinIntercept>"
       << "<mo_stiVal species=\"Species_5\">0.01</mo_stiVal>"
       << "</mo_selfThinIntercept>"
       << "<mo_selfThinMaxDbh>"
       << "<mo_stmdVal species=\"Species_5\">15.0</mo_stmdVal>"
       << "</mo_selfThinMaxDbh>"
       << "</SelfThinning3>"
       << "<Senescence6>"
       << "<mo_senescenceAlpha>"
       << "<mo_saVal species=\"Species_4\">-8.0</mo_saVal>"
       << "</mo_senescenceAlpha>"
       << "<mo_senescenceBeta>"
       << "<mo_sbVal species=\"Species_4\">0.135</mo_sbVal>"
       << "</mo_senescenceBeta>"
       << "<mo_dbhAtOnsetOfSenescence>"
       << "<mo_daoosVal species=\"Species_4\">50.0</mo_daoosVal>"
       << "</mo_dbhAtOnsetOfSenescence>"
       << "<mo_dbhAtAsympMaxMort>110</mo_dbhAtAsympMaxMort>"
       << "</Senescence6>"
       << "<StochasticMortality8>"
       << "<mo_stochasticMortRate>"
       << "<mo_smrVal species=\"Species_3\">0.3</mo_smrVal>"
       << "<mo_smrVal species=\"Species_4\">0.0</mo_smrVal>"
       << "</mo_stochasticMortRate>"
       << "</StochasticMortality8>"
       << "<StochasticMortality7>"
       << "<mo_stochasticMortRate>"
       << "<mo_smrVal species=\"Species_3\">1.0</mo_smrVal>"
       << "</mo_stochasticMortRate>"
       << "</StochasticMortality7>"
       << "</paramFile>";
oOut.close();

  return cFileString;
}
