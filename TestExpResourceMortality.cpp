//---------------------------------------------------------------------------
// TestExpResourceMortality.cpp
//---------------------------------------------------------------------------
#include "TestExpResourceMortality.h"
#include <gtest/gtest.h>
#include "SimManager.h"
#include "TreePopulation.h"
#include "BehaviorBase.h"
#include <fstream>
#include <math.h>

/////////////////////////////////////////////////////////////////////////////
// TestExpResourceMortality()
// Tests the growth-and-resource mortality class.
//
// First run: WriteExpResourceMortalityXMLFile1() creates the parameter file.
// The file has the following characteristics:
// -- Timestep length of 1 year.
// -- 4 species: Species 1, Species 2, Species 3, Species 4 (Species 2 isn't
//    used).
// -- Growth and resource mortality applied to saplings of species 1 and 3,
//    and adults of species 1 and 4.
// -- The resource grid has specified values for 5 cells.
//
// The function does the following:
// -- Grid 1:  Resource = 0, 1000 saplings of species 1 all with a value of 0
//    in their "Growth" data member; 1000 each of saplings and adults of
//    species 2.
// -- Grid 2: Resource = 0.5, 1000 adults of Species 1 all with a value of
//    0 in their "Growth" data member.
// -- Grid 3: Resource = 0, 1000 saplings of Species 3 all with a value of 4
//    in their "Growth" data member.
// -- Grid 4: Resource = 1, 1000 saplings of Species 1 all with a value of 0
//    in their "Growth" data member.
// -- Grid 5: Resource = 0.6, 1000 adults of Species 4 all with a value of
//    25.1 in their "Growth" data member.
// -- Grid 6: Resource = 3, 1000 saplings of Species 4 all with a value of
//    10 in their "Growth" data member.
// -- Grid 7: Resource = 5, 1000 adults of Species 3 all with a value of 14
//    in their "Growth" data member.
// --  The model is run for 1 timestep.
// --  The remaining trees of each tree type and species are counted.
// --  The counts are compared to expected results, give or take 5% (or
// greater tolerance at lower numbers).
/////////////////////////////////////////////////////////////////////////////
TEST(ExpResourceMortality, TestExpResourceMortality1) {
  clTreePopulation * p_oPop;
  clTreeSearch *p_oAllTrees;
  clTree *p_oTree;
  int **p_iTreeCount;
  float fVal;
  int i, j, iNumSpecies, iNumTypes;

  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {

    //Create the sim manager and load our file
    clSimManager *p_oSimManager = new clSimManager(3, 2, "");
    p_oSimManager->ReadFile( WriteExpResourceMortalityXMLFile1() );
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

    //Grid 1:  1000 each of saplings of Species 1, Species 2 saplings, Species
    //2 adults
    for (i = 0; i < 1000; i++) {
      p_oTree = p_oPop->CreateTree(1, 1, 0, clTreePopulation::sapling, 7);
      p_oTree = p_oPop->CreateTree(1, 1, 1, clTreePopulation::sapling, 7);
      p_oTree = p_oPop->CreateTree(1, 1, 1, clTreePopulation::adult, 17);
    }

    //Grid 2:  1000 adults of Species 1
    for (i = 0; i < 1000; i++) {
      p_oTree = p_oPop->CreateTree(9, 9, 0, clTreePopulation::adult, 17);
    }

    //Grid 3:  1000 saplings of Species 3
    for (i = 0; i < 1000; i++) {
      p_oTree = p_oPop->CreateTree(17, 17, 2, clTreePopulation::sapling, 7);
    }

    //Grid 4:  1000 saplings of Species 1
    for (i = 0; i < 1000; i++) {
      p_oTree = p_oPop->CreateTree(25, 25, 0, clTreePopulation::sapling, 7);
    }

    //Grid 5:  1000 adults of Species 4
    for (i = 0; i < 1000; i++) {
      p_oTree = p_oPop->CreateTree(33, 33, 3, clTreePopulation::adult, 17);
    }

    //Grid 6:  1000 saplings of Species 4
    for (i = 0; i < 1000; i++) {
      p_oTree = p_oPop->CreateTree(41, 41, 3, clTreePopulation::sapling, 7);
    }

    //Grid 7:  1000 adults of Species 3
    for (i = 0; i < 1000; i++) {
      p_oTree = p_oPop->CreateTree(49, 49, 2, clTreePopulation::adult, 17);
    }

    //Verify initial conditions
    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {
      p_iTreeCount[p_oTree->GetSpecies()][p_oTree->GetType()]++;
      p_oTree = p_oAllTrees->NextTree();
    }
    EXPECT_EQ(p_iTreeCount[0][clTreePopulation::sapling], 2000);
    EXPECT_EQ(p_iTreeCount[0][clTreePopulation::adult], 1000);
    EXPECT_EQ(p_iTreeCount[1][clTreePopulation::sapling], 1000);
    EXPECT_EQ(p_iTreeCount[1][clTreePopulation::adult], 1000);
    EXPECT_EQ(p_iTreeCount[2][clTreePopulation::sapling], 1000);
    EXPECT_EQ(p_iTreeCount[2][clTreePopulation::adult], 1000);
    EXPECT_EQ(p_iTreeCount[3][clTreePopulation::sapling], 1000);
    EXPECT_EQ(p_iTreeCount[3][clTreePopulation::adult], 1000);

    //Run for one timestep
    p_oSimManager->RunSim(1);

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
    fVal = 1200;
    EXPECT_LT(fabs(p_iTreeCount[0][clTreePopulation::sapling] - fVal)/fVal, 0.1);

    //Adults of Species 1
    fVal = 600;
    EXPECT_LT(fabs(p_iTreeCount[0][clTreePopulation::adult] - fVal)/fVal, 0.1);

    //Saplings of Species 2
    EXPECT_EQ(p_iTreeCount[1][clTreePopulation::sapling], 1000);

    //Adults of Species 2
    EXPECT_EQ(p_iTreeCount[1][clTreePopulation::adult], 1000);

    //Saplings of Species 3
    fVal = 847;
    EXPECT_LT(fabs(p_iTreeCount[2][clTreePopulation::sapling] - fVal)/fVal, 0.1);

    //Adults of Species 3
    EXPECT_EQ(p_iTreeCount[2][clTreePopulation::adult], 1000);

    //Saplings of Species 4
    EXPECT_EQ(p_iTreeCount[3][clTreePopulation::sapling], 1000);

    //Adults of Species 4
    fVal = 208;
    EXPECT_LT(fabs(p_iTreeCount[3][clTreePopulation::adult] - fVal)/fVal, 0.1);

    for (i = 0; i < iNumSpecies; i++) delete[] p_iTreeCount[i];
    delete[] p_iTreeCount; p_iTreeCount = NULL;
    delete p_oSimManager;
  } catch (modelErr &e) {
    for (i = 0; i < iNumSpecies; i++) delete[] p_iTreeCount[i];
    delete[] p_iTreeCount; p_iTreeCount = NULL;
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

/////////////////////////////////////////////////////////////////////////////
// TestExpResourceMortality()
// Tests the growth-and-resource mortality class.
//
// Second run:
// WriteExpResourceMortalityXMLFile2() creates the parameter file.  Everything is exactly as it
// is in the first run except the timestep length is 3 years.
/////////////////////////////////////////////////////////////////////////////
TEST(ExpResourceMortality, TestExpResourceMortality2) {

  clTreePopulation * p_oPop;
  clTreeSearch *p_oAllTrees;
  clTree *p_oTree;
  int **p_iTreeCount;
  float fVal;
  int i, j, iNumSpecies, iNumTypes;

  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {

    //Load our second file
    p_oSimManager->ReadFile( WriteExpResourceMortalityXMLFile2() );
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

    //Grid 1:  1000 each of saplings of Species 1, Species 2 saplings, Species
    //2 adults
    for (i = 0; i < 1000; i++) {
      p_oTree = p_oPop->CreateTree(1, 1, 0, clTreePopulation::sapling, 7);
      p_oTree = p_oPop->CreateTree(1, 1, 1, clTreePopulation::sapling, 7);
      p_oTree = p_oPop->CreateTree(1, 1, 1, clTreePopulation::adult, 17);
    }

    //Grid 2:  1000 adults of Species 1
    for (i = 0; i < 1000; i++) {
      p_oTree = p_oPop->CreateTree(9, 9, 0, clTreePopulation::adult, 17);
    }

    //Grid 3:  1000 saplings of Species 3
    for (i = 0; i < 1000; i++) {
      p_oTree = p_oPop->CreateTree(17, 17, 2, clTreePopulation::sapling, 7);
    }

    //Grid 4:  1000 saplings of Species 1
    for (i = 0; i < 1000; i++) {
      p_oTree = p_oPop->CreateTree(25, 25, 0, clTreePopulation::sapling, 7);
    }

    //Grid 5:  1000 adults of Species 4
    for (i = 0; i < 1000; i++) {
      p_oTree = p_oPop->CreateTree(33, 33, 3, clTreePopulation::adult, 17);
    }

    //Grid 6:  1000 saplings of Species 4
    for (i = 0; i < 1000; i++) {
      p_oTree = p_oPop->CreateTree(41, 41, 3, clTreePopulation::sapling, 7);
    }

    //Grid 7:  1000 adults of Species 3
    for (i = 0; i < 1000; i++) {
      p_oTree = p_oPop->CreateTree(49, 49, 2, clTreePopulation::adult, 17);
    }

    //Verify initial conditions
    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {
      p_iTreeCount[p_oTree->GetSpecies()][p_oTree->GetType()]++;
      p_oTree = p_oAllTrees->NextTree();
    }
    EXPECT_EQ(p_iTreeCount[0][clTreePopulation::sapling], 2000);
    EXPECT_EQ(p_iTreeCount[0][clTreePopulation::adult], 1000);
    EXPECT_EQ(p_iTreeCount[1][clTreePopulation::sapling], 1000);
    EXPECT_EQ(p_iTreeCount[1][clTreePopulation::adult], 1000);
    EXPECT_EQ(p_iTreeCount[2][clTreePopulation::sapling], 1000);
    EXPECT_EQ(p_iTreeCount[2][clTreePopulation::adult], 1000);
    EXPECT_EQ(p_iTreeCount[3][clTreePopulation::sapling], 1000);
    EXPECT_EQ(p_iTreeCount[3][clTreePopulation::adult], 1000);

    //Run for one timestep
    p_oSimManager->RunSim(1);

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
    fVal = 1008;
    EXPECT_LT(fabs(p_iTreeCount[0][clTreePopulation::sapling] - fVal)/fVal, 0.1);

    //Adults of Species 1
    fVal = 216;
    EXPECT_LT(fabs(p_iTreeCount[0][clTreePopulation::adult] - fVal)/fVal, 0.1);

    //Saplings of Species 2
    EXPECT_EQ(p_iTreeCount[1][clTreePopulation::sapling], 1000);

    //Adults of Species 2
    EXPECT_EQ(p_iTreeCount[1][clTreePopulation::adult], 1000);

    //Saplings of Species 3
    fVal = 609;
    EXPECT_LT(fabs(p_iTreeCount[2][clTreePopulation::sapling] - fVal)/fVal, 0.1);

    //Adults of Species 3
    EXPECT_EQ(p_iTreeCount[2][clTreePopulation::adult], 1000);

    //Saplings of Species 4
    EXPECT_EQ(p_iTreeCount[3][clTreePopulation::sapling], 1000);

    //Adults of Species 4
    EXPECT_LT(p_iTreeCount[3][clTreePopulation::adult], 20);



    //Cleanup
    for (i = 0; i < iNumSpecies; i++) delete[] p_iTreeCount[i];
    delete[] p_iTreeCount;
    delete p_oSimManager;
  } catch (modelErr &e) {
    for (i = 0; i < iNumSpecies; i++) delete[] p_iTreeCount[i];
    delete[] p_iTreeCount; p_iTreeCount = NULL;
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

/////////////////////////////////////////////////////////////////////////////
// WriteExpResourceMortalityXMLFile1()
/////////////////////////////////////////////////////////////////////////////
const char* WriteExpResourceMortalityXMLFile1() {
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
      << "<plot_latitude>55.37</plot_latitude>"
      << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
      << "<plot_temp_C>12</plot_temp_C>"
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
      << "<tr_chVal species=\"Species_1\">40.0</tr_chVal>"
      << "<tr_chVal species=\"Species_2\">40.0</tr_chVal>"
      << "<tr_chVal species=\"Species_3\">40.0</tr_chVal>"
      << "<tr_chVal species=\"Species_4\">40.0</tr_chVal>"
      << "</tr_canopyHeight>"
      << "<tr_stdAsympCrownRad>"
      << "<tr_sacrVal species=\"Species_1\">0.7</tr_sacrVal>"
      << "<tr_sacrVal species=\"Species_2\">0.7</tr_sacrVal>"
      << "<tr_sacrVal species=\"Species_3\">0.7</tr_sacrVal>"
      << "<tr_sacrVal species=\"Species_4\">0.7</tr_sacrVal>"
      << "</tr_stdAsympCrownRad>"
      << "<tr_stdCrownRadExp>"
      << "<tr_screVal species=\"Species_1\">1.0</tr_screVal>"
      << "<tr_screVal species=\"Species_2\">1.0</tr_screVal>"
      << "<tr_screVal species=\"Species_3\">1.0</tr_screVal>"
      << "<tr_screVal species=\"Species_4\">1.0</tr_screVal>"
      << "</tr_stdCrownRadExp>"
      << "<tr_conversionDiam10ToDBH>"
      << "<tr_cdtdVal species=\"Species_1\">0.7</tr_cdtdVal>"
      << "<tr_cdtdVal species=\"Species_2\">0.7</tr_cdtdVal>"
      << "<tr_cdtdVal species=\"Species_3\">0.7</tr_cdtdVal>"
      << "<tr_cdtdVal species=\"Species_4\">0.7</tr_cdtdVal>"
      << "</tr_conversionDiam10ToDBH>"
      << "<tr_interceptDiam10ToDBH>"
      << "<tr_idtdVal species=\"Species_1\">0</tr_idtdVal>"
      << "<tr_idtdVal species=\"Species_2\">0</tr_idtdVal>"
      << "<tr_idtdVal species=\"Species_3\">0</tr_idtdVal>"
      << "<tr_idtdVal species=\"Species_4\">0</tr_idtdVal>"
      << "</tr_interceptDiam10ToDBH>"
      << "<tr_stdAsympCrownHt>"
      << "<tr_sachVal species=\"Species_1\">0.7</tr_sachVal>"
      << "<tr_sachVal species=\"Species_2\">0.7</tr_sachVal>"
      << "<tr_sachVal species=\"Species_3\">0.7</tr_sachVal>"
      << "<tr_sachVal species=\"Species_4\">0.7</tr_sachVal>"
      << "</tr_stdAsympCrownHt>"
      << "<tr_stdCrownHtExp>"
      << "<tr_scheVal species=\"Species_1\">1.0</tr_scheVal>"
      << "<tr_scheVal species=\"Species_2\">1.0</tr_scheVal>"
      << "<tr_scheVal species=\"Species_3\">1.0</tr_scheVal>"
      << "<tr_scheVal species=\"Species_4\">1.0</tr_scheVal>"
      << "</tr_stdCrownHtExp>"
      << "<tr_slopeOfHeight-Diam10>"
      << "<tr_sohdVal species=\"Species_1\">0.03</tr_sohdVal>"
      << "<tr_sohdVal species=\"Species_2\">0.03</tr_sohdVal>"
      << "<tr_sohdVal species=\"Species_3\">0.03</tr_sohdVal>"
      << "<tr_sohdVal species=\"Species_4\">0.03</tr_sohdVal>"
      << "</tr_slopeOfHeight-Diam10>"
      << "<tr_slopeOfAsymHeight>"
      << "<tr_soahVal species=\"Species_1\">0.7</tr_soahVal>"
      << "<tr_soahVal species=\"Species_2\">0.7</tr_soahVal>"
      << "<tr_soahVal species=\"Species_3\">0.7</tr_soahVal>"
      << "<tr_soahVal species=\"Species_4\">0.7</tr_soahVal>"
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
      << "<fl c=\"0\">1</fl>"
      << "</ma_v>"
      << "<ma_v x=\"4\" y=\"4\">"
      << "<fl c=\"0\">0.6</fl>"
      << "</ma_v>"
      << "<ma_v x=\"5\" y=\"5\">"
      << "<fl c=\"0\">10</fl>"
      << "</ma_v>"
      << "<ma_v x=\"6\" y=\"6\">"
      << "<fl c=\"0\">14</fl>"
      << "</ma_v>"
      << "</grid>"
      << "<behaviorList>"
      << "<behavior>"
      << "<behaviorName>ConstRadialGrowth</behaviorName>"
      << "<version>1.0</version>"
      << "<listPosition>1</listPosition>"
      << "<applyTo species=\"Species_1\" type=\"Sapling\" />"
      << "<applyTo species=\"Species_3\" type=\"Sapling\" />"
      << "<applyTo species=\"Species_1\" type=\"Adult\" />"
      << "<applyTo species=\"Species_4\" type=\"Adult\" />"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>ExponentialGrowthResourceMortality</behaviorName>"
      << "<version>1.0</version>"
      << "<listPosition>2</listPosition>"
      << "<applyTo species=\"Species_1\" type=\"Sapling\" />"
      << "<applyTo species=\"Species_3\" type=\"Sapling\" />"
      << "<applyTo species=\"Species_1\" type=\"Adult\" />"
      << "<applyTo species=\"Species_4\" type=\"Adult\" />"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>StochasticMortality</behaviorName>"
      << "<version>1.0</version>"
      << "<listPosition>3</listPosition>"
      << "<applyTo species=\"Species_1\" type=\"Sapling\" />"
      << "<applyTo species=\"Species_2\" type=\"Sapling\" />"
      << "<applyTo species=\"Species_3\" type=\"Sapling\" />"
      << "<applyTo species=\"Species_4\" type=\"Sapling\" />"
      << "<applyTo species=\"Species_1\" type=\"Adult\" />"
      << "<applyTo species=\"Species_2\" type=\"Adult\" />"
      << "<applyTo species=\"Species_3\" type=\"Adult\" />"
      << "<applyTo species=\"Species_4\" type=\"Adult\" />"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>RemoveDead</behaviorName>"
      << "<version>2.0</version>"
      << "<listPosition>4</listPosition>"
      << "<applyTo species=\"Species_1\" type=\"Sapling\" />"
      << "<applyTo species=\"Species_2\" type=\"Sapling\" />"
      << "<applyTo species=\"Species_3\" type=\"Sapling\" />"
      << "<applyTo species=\"Species_4\" type=\"Sapling\" />"
      << "<applyTo species=\"Species_1\" type=\"Adult\" />"
      << "<applyTo species=\"Species_2\" type=\"Adult\" />"
      << "<applyTo species=\"Species_3\" type=\"Adult\" />"
      << "<applyTo species=\"Species_4\" type=\"Adult\" />"
      << "</behavior>"
      << "</behaviorList>"
      << "<ConstRadialGrowth1>"
      << "<gr_adultConstRadialInc>"
      << "<gr_acriVal species=\"Species_1\">0</gr_acriVal>"
      << "<gr_acriVal species=\"Species_3\">4</gr_acriVal>"
      << "<gr_acriVal species=\"Species_4\">25.1</gr_acriVal>"
      << "</gr_adultConstRadialInc>"
      << "</ConstRadialGrowth1>"
      << "<StochasticMortality3>"
      << "<mo_stochasticMortRate>"
      << "<mo_smrVal species=\"Species_1\">0</mo_smrVal>"
      << "<mo_smrVal species=\"Species_3\">0</mo_smrVal>"
      << "<mo_smrVal species=\"Species_2\">0</mo_smrVal>"
      << "<mo_smrVal species=\"Species_4\">0</mo_smrVal>"
      << "</mo_stochasticMortRate>"
      << "</StochasticMortality3>"
      << "<ExponentialGrowthResourceMortality2>"
      << "<mo_expResMortA>"
      << "<mo_ermaVal species=\"Species_1\">0.8</mo_ermaVal>"
      << "<mo_ermaVal species=\"Species_3\">0.9</mo_ermaVal>"
      << "<mo_ermaVal species=\"Species_4\">1.2</mo_ermaVal>"
      << "</mo_expResMortA>"
      << "<mo_expResMortB>"
      << "<mo_ermbVal species=\"Species_1\">1.6</mo_ermbVal>"
      << "<mo_ermbVal species=\"Species_3\">0.7</mo_ermbVal>"
      << "<mo_ermbVal species=\"Species_4\">-0.3</mo_ermbVal>"
      << "</mo_expResMortB>"
      << "<mo_expResMortC>"
      << "<mo_ermcVal species=\"Species_1\">0.2</mo_ermcVal>"
      << "<mo_ermcVal species=\"Species_3\">1.3</mo_ermcVal>"
      << "<mo_ermcVal species=\"Species_4\">0.51</mo_ermcVal>"
      << "</mo_expResMortC>"
      << "<mo_expResMortD>"
      << "<mo_ermdVal species=\"Species_1\">0</mo_ermdVal>"
      << "<mo_ermdVal species=\"Species_3\">2.5</mo_ermdVal>"
      << "<mo_ermdVal species=\"Species_4\">0.2</mo_ermdVal>"
      << "</mo_expResMortD>"
      << "</ExponentialGrowthResourceMortality2>"
      << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteExpResourceMortalityXMLFile2()
/////////////////////////////////////////////////////////////////////////////
const char* WriteExpResourceMortalityXMLFile2() {
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
      << "<plot_latitude>55.37</plot_latitude>"
      << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
      << "<plot_temp_C>12</plot_temp_C>"
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
      << "<tr_chVal species=\"Species_1\">40.0</tr_chVal>"
      << "<tr_chVal species=\"Species_2\">40.0</tr_chVal>"
      << "<tr_chVal species=\"Species_3\">40.0</tr_chVal>"
      << "<tr_chVal species=\"Species_4\">40.0</tr_chVal>"
      << "</tr_canopyHeight>"
      << "<tr_stdAsympCrownRad>"
      << "<tr_sacrVal species=\"Species_1\">0.7</tr_sacrVal>"
      << "<tr_sacrVal species=\"Species_2\">0.7</tr_sacrVal>"
      << "<tr_sacrVal species=\"Species_3\">0.7</tr_sacrVal>"
      << "<tr_sacrVal species=\"Species_4\">0.7</tr_sacrVal>"
      << "</tr_stdAsympCrownRad>"
      << "<tr_stdCrownRadExp>"
      << "<tr_screVal species=\"Species_1\">1.0</tr_screVal>"
      << "<tr_screVal species=\"Species_2\">1.0</tr_screVal>"
      << "<tr_screVal species=\"Species_3\">1.0</tr_screVal>"
      << "<tr_screVal species=\"Species_4\">1.0</tr_screVal>"
      << "</tr_stdCrownRadExp>"
      << "<tr_conversionDiam10ToDBH>"
      << "<tr_cdtdVal species=\"Species_1\">0.7</tr_cdtdVal>"
      << "<tr_cdtdVal species=\"Species_2\">0.7</tr_cdtdVal>"
      << "<tr_cdtdVal species=\"Species_3\">0.7</tr_cdtdVal>"
      << "<tr_cdtdVal species=\"Species_4\">0.7</tr_cdtdVal>"
      << "</tr_conversionDiam10ToDBH>"
      << "<tr_interceptDiam10ToDBH>"
      << "<tr_idtdVal species=\"Species_1\">0</tr_idtdVal>"
      << "<tr_idtdVal species=\"Species_2\">0</tr_idtdVal>"
      << "<tr_idtdVal species=\"Species_3\">0</tr_idtdVal>"
      << "<tr_idtdVal species=\"Species_4\">0</tr_idtdVal>"
      << "</tr_interceptDiam10ToDBH>"
      << "<tr_stdAsympCrownHt>"
      << "<tr_sachVal species=\"Species_1\">0.7</tr_sachVal>"
      << "<tr_sachVal species=\"Species_2\">0.7</tr_sachVal>"
      << "<tr_sachVal species=\"Species_3\">0.7</tr_sachVal>"
      << "<tr_sachVal species=\"Species_4\">0.7</tr_sachVal>"
      << "</tr_stdAsympCrownHt>"
      << "<tr_stdCrownHtExp>"
      << "<tr_scheVal species=\"Species_1\">1.0</tr_scheVal>"
      << "<tr_scheVal species=\"Species_2\">1.0</tr_scheVal>"
      << "<tr_scheVal species=\"Species_3\">1.0</tr_scheVal>"
      << "<tr_scheVal species=\"Species_4\">1.0</tr_scheVal>"
      << "</tr_stdCrownHtExp>"
      << "<tr_slopeOfHeight-Diam10>"
      << "<tr_sohdVal species=\"Species_1\">0.03</tr_sohdVal>"
      << "<tr_sohdVal species=\"Species_2\">0.03</tr_sohdVal>"
      << "<tr_sohdVal species=\"Species_3\">0.03</tr_sohdVal>"
      << "<tr_sohdVal species=\"Species_4\">0.03</tr_sohdVal>"
      << "</tr_slopeOfHeight-Diam10>"
      << "<tr_slopeOfAsymHeight>"
      << "<tr_soahVal species=\"Species_1\">0.7</tr_soahVal>"
      << "<tr_soahVal species=\"Species_2\">0.7</tr_soahVal>"
      << "<tr_soahVal species=\"Species_3\">0.7</tr_soahVal>"
      << "<tr_soahVal species=\"Species_4\">0.7</tr_soahVal>"
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
      << "<fl c=\"0\">1</fl>"
      << "</ma_v>"
      << "<ma_v x=\"4\" y=\"4\">"
      << "<fl c=\"0\">0.6</fl>"
      << "</ma_v>"
      << "<ma_v x=\"5\" y=\"5\">"
      << "<fl c=\"0\">10</fl>"
      << "</ma_v>"
      << "<ma_v x=\"6\" y=\"6\">"
      << "<fl c=\"0\">14</fl>"
      << "</ma_v>"
      << "</grid>"
      << "<behaviorList>"
      << "<behavior>"
      << "<behaviorName>ConstRadialGrowth</behaviorName>"
      << "<version>1.0</version>"
      << "<listPosition>1</listPosition>"
      << "<applyTo species=\"Species_1\" type=\"Sapling\" />"
      << "<applyTo species=\"Species_3\" type=\"Sapling\" />"
      << "<applyTo species=\"Species_1\" type=\"Adult\" />"
      << "<applyTo species=\"Species_4\" type=\"Adult\" />"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>ExponentialGrowthResourceMortality</behaviorName>"
      << "<version>1.0</version>"
      << "<listPosition>2</listPosition>"
      << "<applyTo species=\"Species_1\" type=\"Sapling\" />"
      << "<applyTo species=\"Species_3\" type=\"Sapling\" />"
      << "<applyTo species=\"Species_1\" type=\"Adult\" />"
      << "<applyTo species=\"Species_4\" type=\"Adult\" />"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>StochasticMortality</behaviorName>"
      << "<version>1.0</version>"
      << "<listPosition>3</listPosition>"
      << "<applyTo species=\"Species_1\" type=\"Sapling\" />"
      << "<applyTo species=\"Species_2\" type=\"Sapling\" />"
      << "<applyTo species=\"Species_3\" type=\"Sapling\" />"
      << "<applyTo species=\"Species_4\" type=\"Sapling\" />"
      << "<applyTo species=\"Species_1\" type=\"Adult\" />"
      << "<applyTo species=\"Species_2\" type=\"Adult\" />"
      << "<applyTo species=\"Species_3\" type=\"Adult\" />"
      << "<applyTo species=\"Species_4\" type=\"Adult\" />"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>RemoveDead</behaviorName>"
      << "<version>2.0</version>"
      << "<listPosition>4</listPosition>"
      << "<applyTo species=\"Species_1\" type=\"Sapling\" />"
      << "<applyTo species=\"Species_2\" type=\"Sapling\" />"
      << "<applyTo species=\"Species_3\" type=\"Sapling\" />"
      << "<applyTo species=\"Species_4\" type=\"Sapling\" />"
      << "<applyTo species=\"Species_1\" type=\"Adult\" />"
      << "<applyTo species=\"Species_2\" type=\"Adult\" />"
      << "<applyTo species=\"Species_3\" type=\"Adult\" />"
      << "<applyTo species=\"Species_4\" type=\"Adult\" />"
      << "</behavior>"
      << "</behaviorList>"
      << "<ConstRadialGrowth1>"
      << "<gr_adultConstRadialInc>"
      << "<gr_acriVal species=\"Species_1\">0</gr_acriVal>"
      << "<gr_acriVal species=\"Species_3\">4</gr_acriVal>"
      << "<gr_acriVal species=\"Species_4\">25.1</gr_acriVal>"
      << "</gr_adultConstRadialInc>"
      << "</ConstRadialGrowth1>"
      << "<StochasticMortality3>"
      << "<mo_stochasticMortRate>"
      << "<mo_smrVal species=\"Species_1\">0</mo_smrVal>"
      << "<mo_smrVal species=\"Species_3\">0</mo_smrVal>"
      << "<mo_smrVal species=\"Species_2\">0</mo_smrVal>"
      << "<mo_smrVal species=\"Species_4\">0</mo_smrVal>"
      << "</mo_stochasticMortRate>"
      << "</StochasticMortality3>"
      << "<ExponentialGrowthResourceMortality2>"
      << "<mo_expResMortA>"
      << "<mo_ermaVal species=\"Species_1\">0.8</mo_ermaVal>"
      << "<mo_ermaVal species=\"Species_3\">0.9</mo_ermaVal>"
      << "<mo_ermaVal species=\"Species_4\">1.2</mo_ermaVal>"
      << "</mo_expResMortA>"
      << "<mo_expResMortB>"
      << "<mo_ermbVal species=\"Species_1\">1.6</mo_ermbVal>"
      << "<mo_ermbVal species=\"Species_3\">0.7</mo_ermbVal>"
      << "<mo_ermbVal species=\"Species_4\">-0.3</mo_ermbVal>"
      << "</mo_expResMortB>"
      << "<mo_expResMortC>"
      << "<mo_ermcVal species=\"Species_1\">0.2</mo_ermcVal>"
      << "<mo_ermcVal species=\"Species_3\">1.3</mo_ermcVal>"
      << "<mo_ermcVal species=\"Species_4\">0.51</mo_ermcVal>"
      << "</mo_expResMortC>"
      << "<mo_expResMortD>"
      << "<mo_ermdVal species=\"Species_1\">0</mo_ermdVal>"
      << "<mo_ermdVal species=\"Species_3\">2.5</mo_ermdVal>"
      << "<mo_ermdVal species=\"Species_4\">0.2</mo_ermdVal>"
      << "</mo_expResMortD>"
      << "</ExponentialGrowthResourceMortality2>"
      << "</paramFile>";

  oOut.close();

  return cFileString;
}

