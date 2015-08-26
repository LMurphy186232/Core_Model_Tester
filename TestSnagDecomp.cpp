//---------------------------------------------------------------------------
// TestSnagDecomp.cpp
//---------------------------------------------------------------------------
#include "TestSnagDecomp.h"
#include <gtest/gtest.h>
#include "SimManager.h"
#include "TreePopulation.h"
#include "BehaviorBase.h"
#include <fstream>
#include <math.h>

/////////////////////////////////////////////////////////////////////////////
// TestSnagDecomp()
// Tests the Snag Decay Class Dynamics class.
// WriteSnagDecompXMLFile1() and WriteSnagDecompXMLFile2() create separate
// parameter file. The files have the following common characteristics:
//
// -- Timestep length of 5 years.
// -- 1 species used: ACSA
//
// WriteSnagDecompXMLFile1() tests the snag fall function under harvesting, as follows:
// -- 22500 live trees and 5600 decay class 1 snags are created.
// -- The model is run for 1 timestep.
// -- 5 m2/ha is cut roughly evenly across grid cells. The dead tree remover
// behavior is not invoked so they do not become snags.
// -- The number of snags in each decay class is counted and compared to expected
// results. Individual decay classes are +/- 10%, and total snags are +/- 2%.
//
// WriteSnagDecompXMLFile2() tests the tree fall function, as follows:
// -- 11200 live trees are created.
// -- The model is run for 1 timestep.
// -- 100% mortality kills all these trees.
// -- The number of snags in each decay class is counted and compared to expected
// results. Individual decay classes are +/- 10%, and total snags are +/- 2%.
//
// Error condition 1: WriteSnagDecompXMLErrorFile1() creates the paramter file. The
// behavior finds a negative parameter value and correctly throws an error.
//
// Error condition 2: WriteSnagDecompXMLErrorFile2() creates the parameter file. The
// behaviour finds that the sum of transition probabilities does not add up to
// 1 and correctly throws an error.
/////////////////////////////////////////////////////////////////////////////
TEST(SnagDecomp, TestSnagDecomp) {
  clTreePopulation * p_oPop;
  clTreeSearch *p_oAllTrees;
  clTree *p_oTree;
  int p_iTreeCount[6]; //snag count indexed by decay class
  int i, j, DecayClass;

  //******************************************
  // Run 1
  //******************************************

  //Create the sim manager and load our file
  clSimManager *p_oSimManager = new clSimManager(3, 2, "");
  p_oSimManager->ReadFile(WriteSnagDecompXMLFile1() );
  p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject("treepopulation");

  //Zero out our tree count array
  for (i = 0; i < 6; i++) {
    p_iTreeCount[i] = 0;
  }

  //Create 5600 live trees and 22500 dc1 snags
  for (i = 0; i < 5600; i++)
    p_oTree = p_oPop->CreateTree(8+16*20.0*((i/14)/20)/20.0, 8+16*20.0*((i/14)
        %20)/20.0, 0, clTreePopulation::adult, 25.0-(i%14)/14.0/1000.0);

  for (i=0; i<22500; i++) {
    p_oTree = p_oPop->CreateTree(1+298.0*(i/150)/150.0, 1+298.0*(i%150)/150.0,
        0, clTreePopulation::snag, 25);
    //Assign decay class
    p_oTree->SetValue(p_oPop->GetIntDataCode("SnagDecayClass",
        p_oTree->GetSpecies(), p_oTree->GetType()), 1);
  }

  //Initial conditions count
  p_oAllTrees = p_oPop->Find("all");
  p_oTree = p_oAllTrees->NextTree();
  while (p_oTree) {
    if (p_oTree->GetType()==clTreePopulation::adult)
      DecayClass=0;
    else if (p_oTree->GetType()==clTreePopulation::snag)
      p_oTree->GetValue(p_oPop->GetIntDataCode("SnagDecayClass",
          p_oTree->GetSpecies(), p_oTree->GetType()), &DecayClass);

    p_iTreeCount[DecayClass]++;
    p_oTree = p_oAllTrees->NextTree();
  }

  EXPECT_EQ(p_iTreeCount[0], 5600);
  EXPECT_EQ(p_iTreeCount[1], 22500);
  for (i = 2; i <= 5; i++)
    EXPECT_EQ(p_iTreeCount[i], 0);

  //Run for one timestep
  p_oSimManager->RunSim(1);

  //Count the remaining trees
  for (j = 0; j < 6; j++)
    p_iTreeCount[j] = 0;

  p_oAllTrees = p_oPop->Find("all");
  p_oTree = p_oAllTrees->NextTree();

  while (p_oTree) {
    if (p_oTree->GetType()==clTreePopulation::adult)
      DecayClass=0;
    else if (p_oTree->GetType()==clTreePopulation::snag)
      p_oTree->GetValue(p_oPop->GetIntDataCode("SnagDecayClass",
          p_oTree->GetSpecies(), p_oTree->GetType()), &DecayClass);

    p_iTreeCount[DecayClass]++;
    p_oTree = p_oAllTrees->NextTree();
  }

  //Make sure they are as expected

  //All decay classes
  EXPECT_LT(fabs( (p_iTreeCount[1] + p_iTreeCount[2] + p_iTreeCount[3]
      + p_iTreeCount[4] + p_iTreeCount[5]) - 11598)/11598, 0.02);

  //Decay Class 1
  EXPECT_LT(fabs(p_iTreeCount[1] - 522)/522, 0.1);
  //Decay Class 2
  EXPECT_LT(fabs(p_iTreeCount[2] - 2157)/2157, 0.1);
  //Decay Class 3
  EXPECT_LT(fabs(p_iTreeCount[3] - 3816)/3816, 0.1);
  //Decay Class 4
  EXPECT_LT(fabs(p_iTreeCount[4] - 1925)/1925, 0.1);
  //Decay Class 5
  EXPECT_LT(fabs(p_iTreeCount[5] - 3178)/3178, 0.1);

  //******************************************
  // Run 2
  //******************************************

  p_oSimManager->ReadFile(WriteSnagDecompXMLFile2() );
  p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject("treepopulation");

  //Zero out our tree count array
  for (j = 0; j < 6; j++) {
    p_iTreeCount[j] = 0;
  }

  //Create 11200 live trees
  for (i = 0; i < 11200; i++) {
    p_oTree = p_oPop->CreateTree(8+16*20.0*((i/28)/20)/20.0, 8+16*20.0*((i/28)
        %20)/20.0, 0, clTreePopulation::adult, 10.0);

  }

  //Initial conditions count
  p_oAllTrees = p_oPop->Find("all");
  p_oTree = p_oAllTrees->NextTree();
  while (p_oTree) {
    if (p_oTree->GetType()==clTreePopulation::adult) {
      p_iTreeCount[0]++;
    }
    p_oTree = p_oAllTrees->NextTree();
  }

  EXPECT_EQ(p_iTreeCount[0], 11200);

  p_oSimManager->RunSim(1);

  //Count the remaining trees
  for (j = 0; j < 6; j++)
    p_iTreeCount[j] = 0;

  p_oAllTrees = p_oPop->Find("all");
  p_oTree = p_oAllTrees->NextTree();

  while (p_oTree) {
    if (p_oTree->GetType()==clTreePopulation::adult)
      DecayClass=0;
    else if (p_oTree->GetType()==clTreePopulation::snag)
      p_oTree->GetValue(p_oPop->GetIntDataCode("SnagDecayClass",
          p_oTree->GetSpecies(), p_oTree->GetType()), &DecayClass);

    p_iTreeCount[DecayClass]++;
    p_oTree = p_oAllTrees->NextTree();
  }

  //Make sure they are as expected

  //Live trees
  EXPECT_EQ(p_iTreeCount[0], 0);

  //All decay classes
  EXPECT_LT(fabs( (p_iTreeCount[1] + p_iTreeCount[2] + p_iTreeCount[3]
      + p_iTreeCount[4] + p_iTreeCount[5]) - 8645)/8645, 0.02);

  //Decay Class 1
  EXPECT_LT(fabs(p_iTreeCount[1] - 2507)/2507, 0.1);
  //Decay Class 2
  EXPECT_LT(fabs(p_iTreeCount[2] - 1980)/1980, 0.1);
  //Decay Class 3
  EXPECT_LT(fabs(p_iTreeCount[3] - 1694)/1694, 0.1);
  //Decay Class 4
  EXPECT_LT(fabs(p_iTreeCount[4] - 1072)/1072, 0.1);
  //Decay Class 5
  EXPECT_LT(fabs(p_iTreeCount[5] - 1392)/1392, 0.1);

  delete p_oSimManager;
}

////////////////////////////////////////////////////////////////////////////
// TestErrorProcessing()
////////////////////////////////////////////////////////////////////////////
TEST(SnagDecomp, TestErrorProcessing) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try
  {
    //Identify negative parameter value.
    p_oSimManager->ReadFile(WriteSnagDecompXMLErrorFile1());
    FAIL() << "TestSnagDecomp error processing didn't catch error for WriteSnagDecompXMLErrorFile1.";
  }
  catch (modelErr& err)
  {
    if (err.sMoreInfo.compare("Values for transition probabilites cannot be less than 0.") != 0)
    {
      FAIL() << "TestSnagDecomp error processing caught wrong error for WriteSnagDecompXMLErrorFile1.";
    }
    ;
  }

  try
  {
    //Identify that transition probabilities don't sum up to 1.
    p_oSimManager->ReadFile(WriteSnagDecompXMLErrorFile2());
    FAIL() << "TestSnagDecomp error processing didn't catch error for WriteSnagDecompXMLErrorFile2.";
  }
  catch (modelErr& err)
  {
    if (err.sMoreInfo.compare("Sum of transition probabilities must add up to 1 within each column.") != 0)
    {
      FAIL() << "TestSnagDecomp error processing caught wrong error for WriteSnagDecompXMLErrorFile2.";
    }
    ;
  }
  delete p_oSimManager;
}

/////////////////////////////////////////////////////////////////////////////
// WriteSnagDecompXMLFile1()
/////////////////////////////////////////////////////////////////////////////
const char* WriteSnagDecompXMLFile1() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  std::fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06050101\">"
       << "<plot>"
       << "<timesteps>1</timesteps>"
       << "<rt_timestep>0</rt_timestep><randomSeed>0</randomSeed>"
       << "<yearsPerTimestep>5.0</yearsPerTimestep>"
       << "<plot_lenX>320.0</plot_lenX>"
       << "<plot_lenY>320.0</plot_lenY>"
       << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
       << "<plot_temp_C>12.88171785</plot_temp_C>"
       << "<plot_latitude>41.92</plot_latitude>"
       << "<plot_title>Default parameter file-use for testing only</plot_title>"
       << "</plot>"
       << "<trees>"
       << "<tr_speciesList>"
       << "<tr_species speciesName=\"ACSA\"/>"
       << "</tr_speciesList>"
       << "<tr_seedDiam10Cm>0.2</tr_seedDiam10Cm>"
       << "<tr_minAdultDBH>"
       << "<tr_madVal species=\"ACSA\">10.0</tr_madVal>"
       << "</tr_minAdultDBH>"
       << "<tr_maxSeedlingHeight>"
       << "<tr_mshVal species=\"ACSA\">1.35</tr_mshVal>"
       << "</tr_maxSeedlingHeight>"
       << "</trees>"
       << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>Harvest</behaviorName>"
       << "<version>1.0</version>"
       << "<listPosition>1</listPosition>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>StochasticMortality</behaviorName>"
       << "<version>1</version>"
       << "<applyTo species=\"ACSA\" type=\"Adult\" />"
       << "<listPosition>2</listPosition>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>SnagDecayClassDynamics</behaviorName>"
       << "<version>2.0</version>"
       << "<listPosition>3</listPosition>"
       << "<applyTo species=\"ACSA\" type=\"Adult\" />"
       << "<applyTo species=\"ACSA\" type=\"Snag\" />"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>RemoveDead</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>4</listPosition>"
       << "<applyTo species=\"ACSA\" type=\"Snag\" />"
       << "</behavior>"
       << "</behaviorList>"
       << "<Harvest1>"
       << "<ha_cutEvent>"
       << "<ha_applyToSpecies species=\"ACSA\" />"
       << "<ha_timestep>1</ha_timestep>"
       << "<ha_cutType>partial</ha_cutType>"
       << "<ha_cutAmountType>absolute density</ha_cutAmountType>"
       << "<ha_dbhRange>"
       << "<ha_low>1.0</ha_low>"
       << "<ha_high>100.0</ha_high>"
       << "<ha_amountToCut>117.1875</ha_amountToCut>"
       << "</ha_dbhRange>";

  for (int iX = 0; iX < 40; iX++)
    for (int iY = 0; iY < 40; iY++)
      oOut << "<ha_applyToCell x=\"" << iX << "\" y=\"" << iY << "\" />";

  oOut << "</ha_cutEvent>"
       << "</Harvest1>"
       << "<allometry>"
       << "<tr_whatAdultHeightDiam>"
       << "<tr_wahdVal species=\"ACSA\">0</tr_wahdVal>"
       << "</tr_whatAdultHeightDiam>"
       << "<tr_whatSaplingHeightDiam>"
       << "<tr_wsahdVal species=\"ACSA\">0</tr_wsahdVal>"
       << "</tr_whatSaplingHeightDiam>"
       << "<tr_whatSeedlingHeightDiam>"
       << "<tr_wsehdVal species=\"ACSA\">0</tr_wsehdVal>"
       << "</tr_whatSeedlingHeightDiam>"
       << "<tr_whatAdultCrownRadDiam>"
       << "<tr_wacrdVal species=\"ACSA\">0</tr_wacrdVal>"
       << "</tr_whatAdultCrownRadDiam>"
       << "<tr_whatSaplingCrownRadDiam>"
       << "<tr_wscrdVal species=\"ACSA\">0</tr_wscrdVal>"
       << "</tr_whatSaplingCrownRadDiam>"
       << "<tr_whatAdultCrownHeightHeight>"
       << "<tr_wachhVal species=\"ACSA\">0</tr_wachhVal>"
       << "</tr_whatAdultCrownHeightHeight>"
       << "<tr_whatSaplingCrownHeightHeight>"
       << "<tr_wschhVal species=\"ACSA\">0</tr_wschhVal>"
       << "</tr_whatSaplingCrownHeightHeight>"
       << "<tr_canopyHeight>"
       << "<tr_chVal species=\"ACSA\">24.8</tr_chVal>"
       << "</tr_canopyHeight>"
       << "<tr_stdAsympCrownRad>"
       << "<tr_sacrVal species=\"ACSA\">0.107</tr_sacrVal>"
       << "</tr_stdAsympCrownRad>"
       << "<tr_stdCrownRadExp>"
       << "<tr_screVal species=\"ACSA\">1.0</tr_screVal>"
       << "</tr_stdCrownRadExp>"
       << "<tr_stdMaxCrownRad>"
       << "<tr_smcrVal species=\"ACSA\">10</tr_smcrVal>"
       << "</tr_stdMaxCrownRad>"
       << "<tr_stdAsympCrownHt>"
       << "<tr_sachVal species=\"ACSA\">0.58</tr_sachVal>"
       << "</tr_stdAsympCrownHt>"
       << "<tr_stdCrownHtExp>"
       << "<tr_scheVal species=\"ACSA\">1.0</tr_scheVal>"
       << "</tr_stdCrownHtExp>"
       << "<tr_conversionDiam10ToDBH>"
       << "<tr_cdtdVal species=\"ACSA\">0.75</tr_cdtdVal>"
       << "</tr_conversionDiam10ToDBH>"
       << "<tr_interceptDiam10ToDBH>"
       << "<tr_idtdVal species=\"ACSA\">0.0</tr_idtdVal>"
       << "</tr_interceptDiam10ToDBH>"
       << "<tr_slopeOfAsymHeight>"
       << "<tr_soahVal species=\"ACSA\">0.062333334</tr_soahVal>"
       << "</tr_slopeOfAsymHeight>"
       << "<tr_slopeOfHeight-Diam10>"
       << "<tr_sohdVal species=\"ACSA\">0.03</tr_sohdVal>"
       << "</tr_slopeOfHeight-Diam10>"
       << "</allometry>"
       << "<StochasticMortality2>"
       << "<mo_stochasticMortRate>"
       << "<mo_smrVal species=\"ACSA\">0.0</mo_smrVal>"
       << "</mo_stochasticMortRate>"
       << "</StochasticMortality2>"
       << "<SnagDecayClassDynamics3>"
       << "<sd_snagDecompTreefallAlpha>-0.805</sd_snagDecompTreefallAlpha>"
       << "<sd_snagDecompTreefallBeta>"
       << "<sd_sdtbVal species=\"ACSA\">0.000</sd_sdtbVal>"
       << "</sd_snagDecompTreefallBeta>"
       << "<sd_snagDecompTreefallDelta>-0.016</sd_snagDecompTreefallDelta>"
       << "<sd_snagDecompTreefallTheta>-0.026</sd_snagDecompTreefallTheta>"
       << "<sd_snagDecompTreefallIota>3.389</sd_snagDecompTreefallIota>"
       << "<sd_snagDecompTreefallLambda>-0.084</sd_snagDecompTreefallLambda>"
       << "<sd_snagDecompSnagfallAlpha>5.691</sd_snagDecompSnagfallAlpha>"
       << "<sd_snagDecompSnagfallBeta>"
       << "<sd_sdsbVal species=\"ACSA\">0.000</sd_sdsbVal>"
       << "</sd_snagDecompSnagfallBeta>"
       << "<sd_snagDecompSnagfallGamma2>0.177</sd_snagDecompSnagfallGamma2>"
       << "<sd_snagDecompSnagfallGamma3>0.542</sd_snagDecompSnagfallGamma3>"
       << "<sd_snagDecompSnagfallGamma4>0.702</sd_snagDecompSnagfallGamma4>"
       << "<sd_snagDecompSnagfallGamma5>0.528</sd_snagDecompSnagfallGamma5>"
       << "<sd_snagDecompSnagfallZeta>-3.777</sd_snagDecompSnagfallZeta>"
       << "<sd_snagDecompSnagfallEta>0.531</sd_snagDecompSnagfallEta>"
       << "<sd_snagDecompSnagfallKappa>0.157</sd_snagDecompSnagfallKappa>"
       << "<sd_snagDecompLiveTo1Prob>0.290</sd_snagDecompLiveTo1Prob>"
       << "<sd_snagDecompLiveTo2Prob>0.229</sd_snagDecompLiveTo2Prob>"
       << "<sd_snagDecompLiveTo3Prob>0.196</sd_snagDecompLiveTo3Prob>"
       << "<sd_snagDecompLiveTo4Prob>0.124</sd_snagDecompLiveTo4Prob>"
       << "<sd_snagDecompLiveTo5Prob>0.161</sd_snagDecompLiveTo5Prob>"
       << "<sd_snagDecomp1To1Prob>0.045</sd_snagDecomp1To1Prob>"
       << "<sd_snagDecomp1To2Prob>0.186</sd_snagDecomp1To2Prob>"
       << "<sd_snagDecomp1To3Prob>0.329</sd_snagDecomp1To3Prob>"
       << "<sd_snagDecomp1To4Prob>0.166</sd_snagDecomp1To4Prob>"
       << "<sd_snagDecomp1To5Prob>0.274</sd_snagDecomp1To5Prob>"
       << "<sd_snagDecomp2To2Prob>0.165</sd_snagDecomp2To2Prob>"
       << "<sd_snagDecomp2To3Prob>0.379</sd_snagDecomp2To3Prob>"
       << "<sd_snagDecomp2To4Prob>0.204</sd_snagDecomp2To4Prob>"
       << "<sd_snagDecomp2To5Prob>0.252</sd_snagDecomp2To5Prob>"
       << "<sd_snagDecomp3To3Prob>0.351</sd_snagDecomp3To3Prob>"
       << "<sd_snagDecomp3To4Prob>0.346</sd_snagDecomp3To4Prob>"
       << "<sd_snagDecomp3To5Prob>0.303</sd_snagDecomp3To5Prob>"
       << "<sd_snagDecomp4To4Prob>0.527</sd_snagDecomp4To4Prob>"
       << "<sd_snagDecomp4To5Prob>0.473</sd_snagDecomp4To5Prob>"
       << "<sd_snagDecomp5To5Prob>1.000</sd_snagDecomp5To5Prob>"
       << "<sd_minSnagBreakHeight>6</sd_minSnagBreakHeight>"
       << "<sd_maxSnagBreakHeight>6</sd_maxSnagBreakHeight>"
       << "</SnagDecayClassDynamics3>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteSnagDecompXMLFile2()
/////////////////////////////////////////////////////////////////////////////
const char* WriteSnagDecompXMLFile2() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  std::fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?><paramFile fileCode=\"06050101\">"
       << "<plot>"
       << "<timesteps>1</timesteps>"
       << "<randomSeed>0</randomSeed>"
       << "<yearsPerTimestep>5.0</yearsPerTimestep>"
       << "<plot_lenX>320.0</plot_lenX>"
       << "<plot_lenY>320.0</plot_lenY>"
       << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
       << "<plot_temp_C>12.88171785</plot_temp_C>"
       << "<plot_latitude>41.92</plot_latitude>"
       << "<plot_title>Default parameter file-use for testing only</plot_title>"
       << "</plot>"
       << "<trees>"
       << "<tr_speciesList>"
       << "<tr_species speciesName=\"ACSA\"/>"
       << "</tr_speciesList>"
       << "<tr_seedDiam10Cm>0.2</tr_seedDiam10Cm>"
       << "<tr_minAdultDBH>"
       << "<tr_madVal species=\"ACSA\">10.0</tr_madVal>"
       << "</tr_minAdultDBH>"
       << "<tr_maxSeedlingHeight>"
       << "<tr_mshVal species=\"ACSA\">1.35</tr_mshVal>"
       << "</tr_maxSeedlingHeight>"
       << "</trees>"
       << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>StochasticMortality</behaviorName>"
       << "<version>1.0</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"ACSA\" type=\"Adult\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>SnagDecayClassDynamics</behaviorName>"
       << "<version>2.0</version>"
       << "<listPosition>2</listPosition>"
       << "<applyTo species=\"ACSA\" type=\"Adult\" />"
       << "<applyTo species=\"ACSA\" type=\"Snag\" />"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>RemoveDead</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>3</listPosition>"
       << "<applyTo species=\"ACSA\" type=\"Adult\" />"
       << "<applyTo species=\"ACSA\" type=\"Snag\" />"
       << "</behavior>"
       << "</behaviorList>"
       << "<allometry>"
       << "<tr_whatAdultHeightDiam>"
       << "<tr_wahdVal species=\"ACSA\">0</tr_wahdVal>"
       << "</tr_whatAdultHeightDiam>"
       << "<tr_whatSaplingHeightDiam>"
       << "<tr_wsahdVal species=\"ACSA\">0</tr_wsahdVal>"
       << "</tr_whatSaplingHeightDiam>"
       << "<tr_whatSeedlingHeightDiam>"
       << "<tr_wsehdVal species=\"ACSA\">0</tr_wsehdVal>"
       << "</tr_whatSeedlingHeightDiam>"
       << "<tr_whatAdultCrownRadDiam>"
       << "<tr_wacrdVal species=\"ACSA\">0</tr_wacrdVal>"
       << "</tr_whatAdultCrownRadDiam>"
       << "<tr_whatSaplingCrownRadDiam>"
       << "<tr_wscrdVal species=\"ACSA\">0</tr_wscrdVal>"
       << "</tr_whatSaplingCrownRadDiam>"
       << "<tr_whatAdultCrownHeightHeight>"
       << "<tr_wachhVal species=\"ACSA\">0</tr_wachhVal>"
       << "</tr_whatAdultCrownHeightHeight>"
       << "<tr_whatSaplingCrownHeightHeight>"
       << "<tr_wschhVal species=\"ACSA\">0</tr_wschhVal>"
       << "</tr_whatSaplingCrownHeightHeight>"
       << "<tr_canopyHeight>"
       << "<tr_chVal species=\"ACSA\">24.8</tr_chVal>"
       << "</tr_canopyHeight>"
       << "<tr_stdAsympCrownRad>"
       << "<tr_sacrVal species=\"ACSA\">0.107</tr_sacrVal>"
       << "</tr_stdAsympCrownRad>"
       << "<tr_stdCrownRadExp>"
       << "<tr_screVal species=\"ACSA\">1.0</tr_screVal>"
       << "</tr_stdCrownRadExp>"
       << "<tr_stdMaxCrownRad>"
       << "<tr_smcrVal species=\"ACSA\">10</tr_smcrVal>"
       << "</tr_stdMaxCrownRad>"
       << "<tr_stdAsympCrownHt>"
       << "<tr_sachVal species=\"ACSA\">0.58</tr_sachVal>"
       << "</tr_stdAsympCrownHt>"
       << "<tr_stdCrownHtExp>"
       << "<tr_scheVal species=\"ACSA\">1.0</tr_scheVal>"
       << "</tr_stdCrownHtExp>"
       << "<tr_conversionDiam10ToDBH>"
       << "<tr_cdtdVal species=\"ACSA\">0.75</tr_cdtdVal>"
       << "</tr_conversionDiam10ToDBH>"
       << "<tr_interceptDiam10ToDBH>"
       << "<tr_idtdVal species=\"ACSA\">0.0</tr_idtdVal>"
       << "</tr_interceptDiam10ToDBH>"
       << "<tr_slopeOfAsymHeight>"
       << "<tr_soahVal species=\"ACSA\">0.062333334</tr_soahVal>"
       << "</tr_slopeOfAsymHeight><tr_slopeOfHeight-Diam10>"
       << "<tr_sohdVal species=\"ACSA\">0.03</tr_sohdVal>"
       << "</tr_slopeOfHeight-Diam10>"
       << "</allometry>"
       << "<StochasticMortality1>"
       << "<mo_stochasticMortRate>"
       << "<mo_smrVal species=\"ACSA\">1.0</mo_smrVal>"
       << "</mo_stochasticMortRate>"
       << "</StochasticMortality1>"
       << "<SnagDecayClassDynamics2>"
       << "<sd_snagDecompTreefallAlpha>-0.805</sd_snagDecompTreefallAlpha>"
       << "<sd_snagDecompTreefallBeta>"
       << "<sd_sdtbVal species=\"ACSA\">0.000</sd_sdtbVal>"
       << "</sd_snagDecompTreefallBeta>"
       << "<sd_snagDecompTreefallDelta>-0.016</sd_snagDecompTreefallDelta>"
       << "<sd_snagDecompTreefallTheta>-0.026</sd_snagDecompTreefallTheta>"
       << "<sd_snagDecompTreefallIota>3.389</sd_snagDecompTreefallIota>"
       << "<sd_snagDecompTreefallLambda>-0.084</sd_snagDecompTreefallLambda>"
       << "<sd_snagDecompSnagfallAlpha>5.691</sd_snagDecompSnagfallAlpha>"
       << "<sd_snagDecompSnagfallBeta>"
       << "<sd_sdsbVal species=\"ACSA\">0.000</sd_sdsbVal>"
       << "</sd_snagDecompSnagfallBeta>"
       << "<sd_snagDecompSnagfallGamma2>0.177</sd_snagDecompSnagfallGamma2>"
       << "<sd_snagDecompSnagfallGamma3>0.542</sd_snagDecompSnagfallGamma3>"
       << "<sd_snagDecompSnagfallGamma4>0.702</sd_snagDecompSnagfallGamma4>"
       << "<sd_snagDecompSnagfallGamma5>0.528</sd_snagDecompSnagfallGamma5>"
       << "<sd_snagDecompSnagfallZeta>-3.777</sd_snagDecompSnagfallZeta>"
       << "<sd_snagDecompSnagfallEta>0.531</sd_snagDecompSnagfallEta>"
       << "<sd_snagDecompSnagfallKappa>0.157</sd_snagDecompSnagfallKappa>"
       << "<sd_snagDecompLiveTo1Prob>0.290</sd_snagDecompLiveTo1Prob>"
       << "<sd_snagDecompLiveTo2Prob>0.229</sd_snagDecompLiveTo2Prob>"
       << "<sd_snagDecompLiveTo3Prob>0.196</sd_snagDecompLiveTo3Prob>"
       << "<sd_snagDecompLiveTo4Prob>0.124</sd_snagDecompLiveTo4Prob>"
       << "<sd_snagDecompLiveTo5Prob>0.161</sd_snagDecompLiveTo5Prob>"
       << "<sd_snagDecomp1To1Prob>0.045</sd_snagDecomp1To1Prob>"
       << "<sd_snagDecomp1To2Prob>0.186</sd_snagDecomp1To2Prob>"
       << "<sd_snagDecomp1To3Prob>0.329</sd_snagDecomp1To3Prob>"
       << "<sd_snagDecomp1To4Prob>0.166</sd_snagDecomp1To4Prob>"
       << "<sd_snagDecomp1To5Prob>0.274</sd_snagDecomp1To5Prob>"
       << "<sd_snagDecomp2To2Prob>0.165</sd_snagDecomp2To2Prob>"
       << "<sd_snagDecomp2To3Prob>0.379</sd_snagDecomp2To3Prob>"
       << "<sd_snagDecomp2To4Prob>0.204</sd_snagDecomp2To4Prob>"
       << "<sd_snagDecomp2To5Prob>0.252</sd_snagDecomp2To5Prob>"
       << "<sd_snagDecomp3To3Prob>0.351</sd_snagDecomp3To3Prob>"
       << "<sd_snagDecomp3To4Prob>0.346</sd_snagDecomp3To4Prob>"
       << "<sd_snagDecomp3To5Prob>0.303</sd_snagDecomp3To5Prob>"
       << "<sd_snagDecomp4To4Prob>0.527</sd_snagDecomp4To4Prob>"
       << "<sd_snagDecomp4To5Prob>0.473</sd_snagDecomp4To5Prob>"
       << "<sd_snagDecomp5To5Prob>1.000</sd_snagDecomp5To5Prob>"
       << "<sd_minSnagBreakHeight>6</sd_minSnagBreakHeight>"
       << "<sd_maxSnagBreakHeight>6</sd_maxSnagBreakHeight>"
       << "</SnagDecayClassDynamics2>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteSnagDecompXMLErrorFile()
/////////////////////////////////////////////////////////////////////////////
const char* WriteSnagDecompXMLErrorFile1() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  std::fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  oOut
       << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?><paramFile fileCode=\"06050101\">"
       << "<plot>"
       << "<timesteps>1</timesteps>"
       << "<randomSeed>0</randomSeed>"
       << "<yearsPerTimestep>5.0</yearsPerTimestep>"
       << "<plot_lenX>320.0</plot_lenX>"
       << "<plot_lenY>320.0</plot_lenY>"
       << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
       << "<plot_temp_C>12.88171785</plot_temp_C>"
       << "<plot_latitude>41.92</plot_latitude>"
       << "<plot_title>Default parameter file-use for testing only</plot_title>"
       << "</plot>"
       << "<trees>"
       << "<tr_speciesList>"
       << "<tr_species speciesName=\"ACSA\"/>"
       << "</tr_speciesList>"
       << "<tr_seedDiam10Cm>0.2</tr_seedDiam10Cm><tr_minAdultDBH><tr_madVal species=\"ACRU\">10.0</tr_madVal><tr_madVal species=\"ACSA\">10.0</tr_madVal><tr_madVal species=\"BEAL\">10.0</tr_madVal><tr_madVal species=\"FAGR\">10.0</tr_madVal><tr_madVal species=\"TSCA\">10.0</tr_madVal><tr_madVal species=\"FRAM\">10.0</tr_madVal><tr_madVal species=\"PIST\">10.0</tr_madVal><tr_madVal species=\"PRSE\">10.0</tr_madVal><tr_madVal species=\"QURU\">10.0</tr_madVal></tr_minAdultDBH><tr_maxSeedlingHeight><tr_mshVal species=\"ACRU\">1.35</tr_mshVal><tr_mshVal species=\"ACSA\">1.35</tr_mshVal><tr_mshVal species=\"BEAL\">1.35</tr_mshVal><tr_mshVal species=\"FAGR\">1.35</tr_mshVal><tr_mshVal species=\"TSCA\">1.35</tr_mshVal><tr_mshVal species=\"FRAM\">1.35</tr_mshVal><tr_mshVal species=\"PIST\">1.35</tr_mshVal><tr_mshVal species=\"PRSE\">1.35</tr_mshVal><tr_mshVal species=\"QURU\">1.35</tr_mshVal></tr_maxSeedlingHeight>"
       << "</trees>"
       << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>StochasticMortality</behaviorName>"
       << "<version>1.0</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"ACSA\" type=\"Adult\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>SnagDecayClassDynamics</behaviorName>"
       << "<version>2.0</version>"
       << "<listPosition>2</listPosition>"
       << "<applyTo species=\"ACSA\" type=\"Snag\" />"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>RemoveDead</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>3</listPosition>"
       << "<applyTo species=\"ACSA\" type=\"Adult\"/>"
       << "</behavior>"
       << "</behaviorList>"
       << "<allometry>"
       << "<tr_whatAdultHeightDiam>"
       << "<tr_wahdVal species=\"ACSA\">0</tr_wahdVal>"
       << "</tr_whatAdultHeightDiam>"
       << "<tr_whatSaplingHeightDiam>"
       << "<tr_wsahdVal species=\"ACSA\">0</tr_wsahdVal>"
       << "</tr_whatSaplingHeightDiam>"
       << "<tr_whatSeedlingHeightDiam>"
       << "<tr_wsehdVal species=\"ACSA\">0</tr_wsehdVal>"
       << "</tr_whatSeedlingHeightDiam>"
       << "<tr_whatAdultCrownRadDiam>"
       << "<tr_wacrdVal species=\"ACSA\">0</tr_wacrdVal>"
       << "</tr_whatAdultCrownRadDiam>"
       << "<tr_whatSaplingCrownRadDiam>"
       << "<tr_wscrdVal species=\"ACSA\">0</tr_wscrdVal>"
       << "</tr_whatSaplingCrownRadDiam>"
       << "<tr_whatAdultCrownHeightHeight>"
       << "<tr_wachhVal species=\"ACSA\">0</tr_wachhVal>"
       << "</tr_whatAdultCrownHeightHeight>"
       << "<tr_whatSaplingCrownHeightHeight>"
       << "<tr_wschhVal species=\"ACSA\">0</tr_wschhVal>"
       << "</tr_whatSaplingCrownHeightHeight>"
       << "<tr_canopyHeight>"
       << "<tr_chVal species=\"ACSA\">24.8</tr_chVal>"
       << "</tr_canopyHeight>"
       << "<tr_stdAsympCrownRad>"
       << "<tr_sacrVal species=\"ACSA\">0.107</tr_sacrVal>"
       << "</tr_stdAsympCrownRad>"
       << "<tr_stdCrownRadExp>"
       << "<tr_screVal species=\"ACSA\">1.0</tr_screVal>"
       << "</tr_stdCrownRadExp>"
       << "<tr_stdMaxCrownRad>"
       << "<tr_smcrVal species=\"ACSA\">10</tr_smcrVal>"
       << "</tr_stdMaxCrownRad>"
       << "<tr_stdAsympCrownHt>"
       << "<tr_sachVal species=\"ACSA\">0.58</tr_sachVal>"
       << "</tr_stdAsympCrownHt>"
       << "<tr_stdCrownHtExp>"
       << "<tr_scheVal species=\"ACSA\">1.0</tr_scheVal>"
       << "</tr_stdCrownHtExp>"
       << "<tr_conversionDiam10ToDBH>"
       << "<tr_cdtdVal species=\"ACSA\">0.75</tr_cdtdVal>"
       << "</tr_conversionDiam10ToDBH>"
       << "<tr_interceptDiam10ToDBH>"
       << "<tr_idtdVal species=\"ACSA\">0.0</tr_idtdVal>"
       << "</tr_interceptDiam10ToDBH>"
       << "<tr_slopeOfAsymHeight>"
       << "<tr_soahVal species=\"ACSA\">0.062333334</tr_soahVal>"
       << "</tr_slopeOfAsymHeight>"
       << "<tr_slopeOfHeight-Diam10>"
       << "<tr_sohdVal species=\"ACSA\">0.03</tr_sohdVal>"
       << "</tr_slopeOfHeight-Diam10>"
       << "</allometry>"
       << "<StochasticMortality1>"
       << "<mo_stochasticMortRate>"
       << "<mo_smrVal species=\"ACSA\">1.0</mo_smrVal></mo_stochasticMortRate>"
       << "</StochasticMortality1>"
       << "<SnagDecayClassDynamics2>"
       << "<sd_snagDecompTreefallAlpha>-0.805</sd_snagDecompTreefallAlpha>"
       << "<sd_snagDecompTreefallBeta>"
       << "<sd_sdtbVal species=\"ACSA\">0.000</sd_sdtbVal>"
       << "</sd_snagDecompTreefallBeta>"
       << "<sd_snagDecompTreefallDelta>-0.016</sd_snagDecompTreefallDelta>"
       << "<sd_snagDecompTreefallTheta>-0.026</sd_snagDecompTreefallTheta>"
       << "<sd_snagDecompTreefallIota>3.389</sd_snagDecompTreefallIota>"
       << "<sd_snagDecompTreefallLambda>-0.084</sd_snagDecompTreefallLambda>"
       << "<sd_snagDecompSnagfallAlpha>5.691</sd_snagDecompSnagfallAlpha>"
       << "<sd_snagDecompSnagfallBeta>"
       << "<sd_sdsbVal species=\"ACSA\">0.000</sd_sdsbVal>"
       << "</sd_snagDecompSnagfallBeta>"
       << "<sd_snagDecompSnagfallGamma2>0.177</sd_snagDecompSnagfallGamma2>"
       << "<sd_snagDecompSnagfallGamma3>0.542</sd_snagDecompSnagfallGamma3>"
       << "<sd_snagDecompSnagfallGamma4>0.702</sd_snagDecompSnagfallGamma4>"
       << "<sd_snagDecompSnagfallGamma5>0.528</sd_snagDecompSnagfallGamma5>"
       << "<sd_snagDecompSnagfallZeta>-3.777</sd_snagDecompSnagfallZeta>"
       << "<sd_snagDecompSnagfallEta>0.531</sd_snagDecompSnagfallEta>"
       << "<sd_snagDecompSnagfallKappa>0.157</sd_snagDecompSnagfallKappa>"
       << "<sd_snagDecompLiveTo1Prob>0.290</sd_snagDecompLiveTo1Prob>"
       << "<sd_snagDecompLiveTo2Prob>0.229</sd_snagDecompLiveTo2Prob>"
       << "<sd_snagDecompLiveTo3Prob>0.196</sd_snagDecompLiveTo3Prob>"
       << "<sd_snagDecompLiveTo4Prob>0.124</sd_snagDecompLiveTo4Prob>"
       << "<sd_snagDecompLiveTo5Prob>0.161</sd_snagDecompLiveTo5Prob>"
       << "<sd_snagDecomp1To1Prob>-0.045</sd_snagDecomp1To1Prob>"
       << "<sd_snagDecomp1To2Prob>0.186</sd_snagDecomp1To2Prob>"
       << "<sd_snagDecomp1To3Prob>0.329</sd_snagDecomp1To3Prob>"
       << "<sd_snagDecomp1To4Prob>0.166</sd_snagDecomp1To4Prob>"
       << "<sd_snagDecomp1To5Prob>0.274</sd_snagDecomp1To5Prob>"
       << "<sd_snagDecomp2To2Prob>0.165</sd_snagDecomp2To2Prob>"
       << "<sd_snagDecomp2To3Prob>0.379</sd_snagDecomp2To3Prob>"
       << "<sd_snagDecomp2To4Prob>0.204</sd_snagDecomp2To4Prob>"
       << "<sd_snagDecomp2To5Prob>0.252</sd_snagDecomp2To5Prob>"
       << "<sd_snagDecomp3To3Prob>0.351</sd_snagDecomp3To3Prob>"
       << "<sd_snagDecomp3To4Prob>0.346</sd_snagDecomp3To4Prob>"
       << "<sd_snagDecomp3To5Prob>0.303</sd_snagDecomp3To5Prob>"
       << "<sd_snagDecomp4To4Prob>0.527</sd_snagDecomp4To4Prob>"
       << "<sd_snagDecomp4To5Prob>0.473</sd_snagDecomp4To5Prob>"
       << "<sd_snagDecomp5To5Prob>1.000</sd_snagDecomp5To5Prob>"
       << "<sd_minSnagBreakHeight>6</sd_minSnagBreakHeight>"
       << "<sd_maxSnagBreakHeight>6</sd_maxSnagBreakHeight>"
       << "</SnagDecayClassDynamics2>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteSnagDecompXMLErrorFile2()
/////////////////////////////////////////////////////////////////////////////
const char* WriteSnagDecompXMLErrorFile2() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  std::fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  oOut
       << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?><paramFile fileCode=\"06050101\">"
       << "<plot>"
       << "<timesteps>1</timesteps>"
       << "<randomSeed>0</randomSeed>"
       << "<yearsPerTimestep>5.0</yearsPerTimestep>"
       << "<plot_lenX>320.0</plot_lenX>"
       << "<plot_lenY>320.0</plot_lenY>"
       << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
       << "<plot_temp_C>12.88171785</plot_temp_C>"
       << "<plot_latitude>41.92</plot_latitude><plot_title>Default parameter file-use for testing only</plot_title>"
       << "</plot>"
       << "<trees>"
       << "<tr_speciesList>"
       << "<tr_species speciesName=\"ACSA\"/>"
       << "</tr_speciesList>"
       << "<tr_seedDiam10Cm>0.2</tr_seedDiam10Cm>"
       << "<tr_minAdultDBH>"
       << "<tr_madVal species=\"ACSA\">10.0</tr_madVal>"
       << "</tr_minAdultDBH>"
       << "<tr_maxSeedlingHeight>"
       << "<tr_mshVal species=\"ACSA\">1.35</tr_mshVal>"
       << "</tr_maxSeedlingHeight>"
       << "</trees>"
       << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>StochasticMortality</behaviorName>"
       << "<version>1.0</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"ACSA\" type=\"Adult\" />"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>SnagDecayClassDynamics</behaviorName>"
       << "<version>2.0</version>"
       << "<listPosition>2</listPosition>"
       << "<applyTo species=\"ACSA\" type=\"Adult\" />"
       << "<applyTo species=\"ACSA\" type=\"Snag\" />"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>RemoveDead</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>3</listPosition>"
       << "<applyTo species=\"ACSA\" type=\"Adult\" />"
       << "<applyTo species=\"ACSA\" type=\"Snag\" />"
       << "</behavior>"
       << "</behaviorList>"
       << "<allometry>"
       << "<tr_whatAdultHeightDiam>"
       << "<tr_wahdVal species=\"ACSA\">0</tr_wahdVal>"
       << "</tr_whatAdultHeightDiam>"
       << "<tr_whatSaplingHeightDiam>"
       << "<tr_wsahdVal species=\"ACSA\">0</tr_wsahdVal>"
       << "</tr_whatSaplingHeightDiam>"
       << "<tr_whatSeedlingHeightDiam>"
       << "<tr_wsehdVal species=\"ACSA\">0</tr_wsehdVal>"
       << "</tr_whatSeedlingHeightDiam>"
       << "<tr_whatAdultCrownRadDiam>"
       << "<tr_wacrdVal species=\"ACSA\">0</tr_wacrdVal>"
       << "</tr_whatAdultCrownRadDiam>"
       << "<tr_whatSaplingCrownRadDiam>"
       << "<tr_wscrdVal species=\"ACSA\">0</tr_wscrdVal>"
       << "</tr_whatSaplingCrownRadDiam>"
       << "<tr_whatAdultCrownHeightHeight>"
       << "<tr_wachhVal species=\"ACSA\">0</tr_wachhVal>"
       << "</tr_whatAdultCrownHeightHeight>"
       << "<tr_whatSaplingCrownHeightHeight>"
       << "<tr_wschhVal species=\"ACSA\">0</tr_wschhVal>"
       << "</tr_whatSaplingCrownHeightHeight>"
       << "<tr_canopyHeight>"
       << "<tr_chVal species=\"ACSA\">24.8</tr_chVal>"
       << "</tr_canopyHeight>"
       << "<tr_stdAsympCrownRad>"
       << "<tr_sacrVal species=\"ACSA\">0.107</tr_sacrVal>"
       << "</tr_stdAsympCrownRad>"
       << "<tr_stdCrownRadExp>"
       << "<tr_screVal species=\"ACSA\">1.0</tr_screVal>"
       << "</tr_stdCrownRadExp>"
       << "<tr_stdMaxCrownRad>"
       << "<tr_smcrVal species=\"ACSA\">10</tr_smcrVal>"
       << "</tr_stdMaxCrownRad>"
       << "<tr_stdAsympCrownHt>"
       << "<tr_sachVal species=\"ACSA\">0.58</tr_sachVal>"
       << "</tr_stdAsympCrownHt>"
       << "<tr_stdCrownHtExp>"
       << "<tr_scheVal species=\"ACSA\">1.0</tr_scheVal>"
       << "</tr_stdCrownHtExp>"
       << "<tr_conversionDiam10ToDBH>"
       << "<tr_cdtdVal species=\"ACSA\">0.75</tr_cdtdVal>"
       << "</tr_conversionDiam10ToDBH>"
       << "<tr_interceptDiam10ToDBH>"
       << "<tr_idtdVal species=\"ACSA\">0.0</tr_idtdVal>"
       << "</tr_interceptDiam10ToDBH>"
       << "<tr_slopeOfAsymHeight>"
       << "<tr_soahVal species=\"ACSA\">0.062333334</tr_soahVal>"
       << "</tr_slopeOfAsymHeight>"
       << "<tr_slopeOfHeight-Diam10>"
       << "<tr_sohdVal species=\"ACSA\">0.03</tr_sohdVal>"
       << "</tr_slopeOfHeight-Diam10>"
       << "</allometry>"
       << "<StochasticMortality1>"
       << "<mo_stochasticMortRate>"
       << "<mo_smrVal species=\"ACSA\">1.0</mo_smrVal>"
       << "</mo_stochasticMortRate>"
       << "</StochasticMortality1>"
       << "<SnagDecayClassDynamics2>"
       << "<sd_snagDecompTreefallAlpha>-0.805</sd_snagDecompTreefallAlpha>"
       << "<sd_snagDecompTreefallBeta>"
       << "<sd_sdtbVal species=\"ACSA\">0.000</sd_sdtbVal>"
       << "</sd_snagDecompTreefallBeta>"
       << "<sd_snagDecompTreefallDelta>-0.016</sd_snagDecompTreefallDelta>"
       << "<sd_snagDecompTreefallTheta>-0.026</sd_snagDecompTreefallTheta>"
       << "<sd_snagDecompTreefallIota>3.389</sd_snagDecompTreefallIota>"
       << "<sd_snagDecompTreefallLambda>-0.084</sd_snagDecompTreefallLambda>"
       << "<sd_snagDecompSnagfallAlpha>5.691</sd_snagDecompSnagfallAlpha>"
       << "<sd_snagDecompSnagfallBeta>"
       << "<sd_sdsbVal species=\"ACSA\">0.000</sd_sdsbVal>"
       << "</sd_snagDecompSnagfallBeta>"
       << "<sd_snagDecompSnagfallGamma2>0.177</sd_snagDecompSnagfallGamma2>"
       << "<sd_snagDecompSnagfallGamma3>0.542</sd_snagDecompSnagfallGamma3>"
       << "<sd_snagDecompSnagfallGamma4>0.702</sd_snagDecompSnagfallGamma4>"
       << "<sd_snagDecompSnagfallGamma5>0.528</sd_snagDecompSnagfallGamma5>"
       << "<sd_snagDecompSnagfallZeta>-3.777</sd_snagDecompSnagfallZeta>"
       << "<sd_snagDecompSnagfallEta>0.531</sd_snagDecompSnagfallEta>"
       << "<sd_snagDecompSnagfallKappa>0.157</sd_snagDecompSnagfallKappa>"
       << "<sd_snagDecompLiveTo1Prob>0.290</sd_snagDecompLiveTo1Prob>"
       << "<sd_snagDecompLiveTo2Prob>0.229</sd_snagDecompLiveTo2Prob>"
       << "<sd_snagDecompLiveTo3Prob>0.196</sd_snagDecompLiveTo3Prob>"
       << "<sd_snagDecompLiveTo4Prob>0.124</sd_snagDecompLiveTo4Prob>"
       << "<sd_snagDecompLiveTo5Prob>0.161</sd_snagDecompLiveTo5Prob>"
       << "<sd_snagDecomp1To1Prob>0.045</sd_snagDecomp1To1Prob>"
       << "<sd_snagDecomp1To2Prob>0.186</sd_snagDecomp1To2Prob>"
       << "<sd_snagDecomp1To3Prob>0.329</sd_snagDecomp1To3Prob>"
       << "<sd_snagDecomp1To4Prob>0.166</sd_snagDecomp1To4Prob>"
       << "<sd_snagDecomp1To5Prob>0.274</sd_snagDecomp1To5Prob>"
       << "<sd_snagDecomp2To2Prob>0.165</sd_snagDecomp2To2Prob>"
       << "<sd_snagDecomp2To3Prob>0.279</sd_snagDecomp2To3Prob>"
       << "<sd_snagDecomp2To4Prob>0.204</sd_snagDecomp2To4Prob>"
       << "<sd_snagDecomp2To5Prob>0.252</sd_snagDecomp2To5Prob>"
       << "<sd_snagDecomp3To3Prob>0.351</sd_snagDecomp3To3Prob>"
       << "<sd_snagDecomp3To4Prob>0.346</sd_snagDecomp3To4Prob>"
       << "<sd_snagDecomp3To5Prob>0.303</sd_snagDecomp3To5Prob>"
       << "<sd_snagDecomp4To4Prob>0.527</sd_snagDecomp4To4Prob>"
       << "<sd_snagDecomp4To5Prob>0.473</sd_snagDecomp4To5Prob>"
       << "<sd_snagDecomp5To5Prob>1.000</sd_snagDecomp5To5Prob>"
       << "<sd_minSnagBreakHeight>6</sd_minSnagBreakHeight>"
       << "<sd_maxSnagBreakHeight>6</sd_maxSnagBreakHeight>"
       << "</SnagDecayClassDynamics2>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

