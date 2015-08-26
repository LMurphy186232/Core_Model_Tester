//---------------------------------------------------------------------------
// TestMortalityOrg.cpp
//---------------------------------------------------------------------------
#include "TestMortalityOrg.h"
#include <gtest/gtest.h>
#include "SimManager.h"
#include "TreePopulation.h"
#include <fstream>

/////////////////////////////////////////////////////////////////////////////
// TestMortalityOrg()
// Tests the clMortalityOrg class. WriteXMLFile1() will create the parameter
// file for this run. In the file:
//
// -- Two species, Species 1 and Species 2.
// -- A stochastic mortality behavior that kills everything to which it is
// applied. It is applied to adults of Species 2. This behavior should
// be first, to make sure it's the hooked one.
// -- A stochastic mortality behavior that kills none of the trees to
// which it is applied. It is applied to saplings of Species 2.
// -- A self-thinning behavior that kills none of the trees to which it is
// applied. It is applied to saplings of species 2.
//
// This function will:
//
// -- Make sure that saplings and adults of species 2 each have one bool
// data member. It does this by making sure that "dead" has been registered
// for both. It will then attempt to register a bool data member on all
// types, all species, and will throw an error if it is successful (which
// means that the wrong bool data member count was passed to the tree
// population).
// -- Make sure that the behaviors are applied correctly. 10 trees of each
// of Species 1 saplings and adults and Species 2 saplings and adults
// are created. Then the model is run one timestep. All Species 2 adults
// should be gone and everything else should be left. (My concern is mainly
// to make sure that the hooked behavior works right.)
/////////////////////////////////////////////////////////////////////////////
TEST(MortalityOrg, TestMortalityOrg) {
  clTreePopulation * p_oPop;
  clTreeSearch *p_oAllTrees;
  clTree *p_oTree;
  int iDeadCode, i, j, iNumSpecies, iNumTypes;

  //Create the sim manager and load our file
  clSimManager *p_oSimManager = new clSimManager(3, 2, "");
  p_oSimManager->ReadFile( WriteMortalityOrgXMLFile1() );
  p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );
  iNumSpecies = p_oPop->GetNumberOfSpecies();
  iNumTypes = p_oPop->GetNumberOfTypes();

  //Verify that saplings and adults of species 2 have a "dead" data member
  //and no one else
  for (i = 0; i < iNumSpecies; i++) {
    for (j = 0; j < iNumTypes; j++) {
      iDeadCode = p_oPop->GetIntDataCode("dead", i, j);
      if (1 == i && (clTreePopulation::sapling == j || clTreePopulation::adult == j)) {
        EXPECT_GT(iDeadCode, -1);
      } else {
        EXPECT_EQ(iDeadCode, -1);
      }
    }
  }

  //Now make sure that no extra bools got thrown to the tree population
  //Try to register a bool with every species and type - we should get
  //an error every time
  for (i = 0; i < iNumSpecies; i++) {
    for (j = 0; j < iNumTypes; j++) {
      try {
        p_oPop->RegisterBool("test", i, j);
        FAIL() << "TestMortalityOrg failed - extra bool data members were given to clTreePopulation.";
      } catch (modelErr& err) {
        ;
      }
    }
  }

  //Put in 10 trees for saplings and adults of species 1 and 2
  for (i = 0; i < 10; i++) {
    p_oPop->CreateTree(i, i, 0, clTreePopulation::sapling, 9);
  }

  for (i = 0; i < 10; i++) {
    p_oPop->CreateTree(i, i, 0, clTreePopulation::adult, 19);
  }

  for (i = 0; i < 10; i++) {
    p_oPop->CreateTree(i, i, 1, clTreePopulation::sapling, 9);
  }

  for (i = 0; i < 10; i++) {
    p_oPop->CreateTree(i, i, 1, clTreePopulation::adult, 19);
  }

  //Run the model
  p_oSimManager->RunSim(1);

  //Count the trees that are left
  int ** p_iTreeCount = new int*[iNumSpecies];
  for (i = 0; i < iNumSpecies; i++) {
    p_iTreeCount[i] = new int[iNumTypes];
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

  //There should be 10 of species 1 saplings and adults, and species 2 saplings
  for (i = 0; i < iNumSpecies; i++) {
    for (j = 0; j < iNumTypes; j++) {
      if ((1 == i && clTreePopulation::sapling == j) ||
         (0 == i && (clTreePopulation::sapling == j || clTreePopulation::adult == j))) {
        EXPECT_EQ(10,  p_iTreeCount[i][j]);
      } else {
        EXPECT_EQ(0, p_iTreeCount[i][j]);
      }
    }
  }


  for (i = 0; i < iNumSpecies; i++) delete[] p_iTreeCount[i];
  delete[] p_iTreeCount;
  delete p_oSimManager;
}

/////////////////////////////////////////////////////////////////////////////
// WriteMortalityOrgXMLFile1()
/////////////////////////////////////////////////////////////////////////////
const char* WriteMortalityOrgXMLFile1() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06010101\">" << "<plot>"
       << "<timesteps>2</timesteps>"
       << "<yearsPerTimestep>1</yearsPerTimestep>"
       << "<randomSeed>1</randomSeed>"
       << "<plot_lenX>2000</plot_lenX>"
       << "<plot_lenY>200.0</plot_lenY>"
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
       << "</allometry>"
       << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>StochasticMortality</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>StochasticMortality</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>2</listPosition>"
       << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>SelfThinning</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>3</listPosition>"
       << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>RemoveDead</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>4</listPosition>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
       << "</behavior>"
       << "</behaviorList>"
       << "<StochasticMortality1>"
       << "<mo_stochasticMortRate>"
       << "<mo_smrVal species=\"Species_2\">1.0</mo_smrVal>"
       << "</mo_stochasticMortRate>"
       << "</StochasticMortality1>"
       << "<StochasticMortality2>"
       << "<mo_stochasticMortRate>"
       << "<mo_smrVal species=\"Species_2\">0.0</mo_smrVal>"
       << "</mo_stochasticMortRate>"
       << "</StochasticMortality2>"
       << "<SelfThinning3>"
       << "<mo_selfThinSlope>"
       << "<mo_stsVal species=\"Species_1\">0</mo_stsVal>"
       << "<mo_stsVal species=\"Species_2\">0</mo_stsVal>"
       << "</mo_selfThinSlope>"
       << "<mo_selfThinIntercept>"
       << "<mo_stiVal species=\"Species_1\">0</mo_stiVal>"
       << "<mo_stiVal species=\"Species_2\">0</mo_stiVal>"
       << "</mo_selfThinIntercept>"
       << "<mo_selfThinMaxDbh>"
       << "<mo_stmdVal species=\"Species_1\">100</mo_stmdVal>"
       << "<mo_stmdVal species=\"Species_2\">100</mo_stmdVal>"
       << "</mo_selfThinMaxDbh>"
       << "</SelfThinning3>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

