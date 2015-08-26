//---------------------------------------------------------------------------
// TestSeedStochasticity.cpp
//---------------------------------------------------------------------------
#include "TestSeedStochasticity.h"
#include <gtest/gtest.h>
#include "SimManager.h"
#include "Grid.h"
#include "BehaviorBase.h"
#include <fstream>
#include <sstream>

/////////////////////////////////////////////////////////////////////////////
// TestGotAllDisperseObjects()
// This makes sure that all disperse objects are found. WriteXMLFile1() is
// used to create the test file, with five species assigned to each of the
// five different disperse object types. After the behaviors have run, this
// verifies that there are seeds of each species present.
/////////////////////////////////////////////////////////////////////////////
TEST(SeedStochasticity, TestGotAllDisperseObjects) {

  clSimManager * p_oSimManager = new clSimManager(7, 1, "");
  clGrid *p_oSeeds;
  std::stringstream sLabel;
  float fTotal, fSeeds;
  int i, iNumXCells, iNumYCells, iX, iY, iCode;

  //Feed our file to the sim manager
  p_oSimManager->ReadFile(WriteSeedStochasticityXMLFile1());

  //Run all the behaviors
  for (i = 0; i < p_oSimManager->GetNumberOfBehaviors(); i++) {
    p_oSimManager->GetBehaviorObject(i)->Action();
  }

  //Verify that there are seeds for each species
  p_oSeeds = p_oSimManager->GetGridObject("Dispersed Seeds");
  iNumXCells = p_oSeeds->GetNumberXCells();
  iNumYCells = p_oSeeds->GetNumberYCells();

  for (i = 0; i < 3; i++) {
    sLabel << "seeds_" << i;
    fTotal = 0;
    iCode = p_oSeeds->GetFloatDataCode(sLabel.str());
    for (iX = 0; iX < iNumXCells; iX++) {
      for (iY = 0; iY < iNumYCells; iY++) {
        p_oSeeds->GetValueOfCell(iX, iY, iCode, &fSeeds);
        fTotal += fSeeds;
      }
    }
    EXPECT_GT(fTotal, 0);
    sLabel.str("");
  }

  //Clean up
  delete p_oSimManager;
}


/////////////////////////////////////////////////////////////////////////////
// WriteSeedStochasticityXMLFile1()
/////////////////////////////////////////////////////////////////////////////
const char* WriteSeedStochasticityXMLFile1() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

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
       << "<tr_species speciesName=\"Species_1\"/>"
       << "<tr_species speciesName=\"Species_2\"/>"
       << "<tr_species speciesName=\"Species_3\"/>"
       << "<tr_species speciesName=\"Species_4\"/>"
       << "<tr_species speciesName=\"Species_5\"/>"
       << "</tr_speciesList>"
       << "<tr_sizeClasses>"
       << "<tr_sizeClass sizeKey=\"s50.0\" />"
       << "<tr_sizeClass sizeKey=\"s60.0\" />"
       << "</tr_sizeClasses>"
       << "<tr_initialDensities>"
       << "<tr_idVals whatSpecies=\"Species_1\">"
       << "<tr_initialDensity sizeClass=\"s60.0\">25.0</tr_initialDensity>"
       << "</tr_idVals>"
       << "<tr_idVals whatSpecies=\"Species_2\">"
       << "<tr_initialDensity sizeClass=\"s60.0\">25.0</tr_initialDensity>"
       << "</tr_idVals>"
       << "<tr_idVals whatSpecies=\"Species_3\">"
       << "<tr_initialDensity sizeClass=\"s60.0\">25.0</tr_initialDensity>"
       << "</tr_idVals>"
       << "<tr_idVals whatSpecies=\"Species_4\">"
       << "<tr_initialDensity sizeClass=\"s60.0\">25.0</tr_initialDensity>"
       << "</tr_idVals>"
       << "<tr_idVals whatSpecies=\"Species_5\">"
       << "<tr_initialDensity sizeClass=\"s60.0\">25.0</tr_initialDensity>"
       << "</tr_idVals>"
       << "</tr_initialDensities>"
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
       << "<tr_chVal species=\"Species_1\">39.48</tr_chVal>"
       << "<tr_chVal species=\"Species_2\">39.54</tr_chVal>"
       << "<tr_chVal species=\"Species_3\">40.0</tr_chVal>"
       << "<tr_chVal species=\"Species_4\">40.0</tr_chVal>"
       << "<tr_chVal species=\"Species_5\">40.0</tr_chVal>"
       << "</tr_canopyHeight>"
       << "<tr_stdAsympCrownRad>"
       << "<tr_sacrVal species=\"Species_1\">0.0549</tr_sacrVal>"
       << "<tr_sacrVal species=\"Species_2\">0.0614</tr_sacrVal>"
       << "<tr_sacrVal species=\"Species_3\">0.0242</tr_sacrVal>"
       << "<tr_sacrVal species=\"Species_4\">0.0242</tr_sacrVal>"
       << "<tr_sacrVal species=\"Species_5\">0.0242</tr_sacrVal>"
       << "</tr_stdAsympCrownRad>"
       << "<tr_stdCrownRadExp>"
       << "<tr_screVal species=\"Species_1\">1.0</tr_screVal>"
       << "<tr_screVal species=\"Species_2\">1.0</tr_screVal>"
       << "<tr_screVal species=\"Species_3\">1.0</tr_screVal>"
       << "<tr_screVal species=\"Species_4\">1.0</tr_screVal>"
       << "<tr_screVal species=\"Species_5\">1.0</tr_screVal>"
       << "</tr_stdCrownRadExp>"
       << "<tr_stdMaxCrownRad>"
       << "<tr_smcrVal species=\"Species_1\">10</tr_smcrVal>"
       << "<tr_smcrVal species=\"Species_2\">10</tr_smcrVal>"
       << "<tr_smcrVal species=\"Species_3\">10</tr_smcrVal>"
       << "<tr_smcrVal species=\"Species_4\">10</tr_smcrVal>"
       << "<tr_smcrVal species=\"Species_5\">10</tr_smcrVal>"
       << "</tr_stdMaxCrownRad>"
       << "<tr_conversionDiam10ToDBH>"
       << "<tr_cdtdVal species=\"Species_1\">0.8008</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_2\">0.5944</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_3\">0.7059</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_4\">0.7059</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_5\">0.7059</tr_cdtdVal>"
       << "</tr_conversionDiam10ToDBH>"
       << "<tr_interceptDiam10ToDBH>"
       << "<tr_idtdVal species=\"Species_1\">0</tr_idtdVal>"
       << "<tr_idtdVal species=\"Species_2\">0</tr_idtdVal>"
       << "<tr_idtdVal species=\"Species_3\">0</tr_idtdVal>"
       << "<tr_idtdVal species=\"Species_4\">0</tr_idtdVal>"
       << "<tr_idtdVal species=\"Species_5\">0</tr_idtdVal>"
       << "</tr_interceptDiam10ToDBH>"
       << "<tr_stdAsympCrownHt>"
       << "<tr_sachVal species=\"Species_1\">0.389</tr_sachVal>"
       << "<tr_sachVal species=\"Species_2\">0.368</tr_sachVal>"
       << "<tr_sachVal species=\"Species_3\">0.464</tr_sachVal>"
       << "<tr_sachVal species=\"Species_4\">0.464</tr_sachVal>"
       << "<tr_sachVal species=\"Species_5\">0.464</tr_sachVal>"
       << "</tr_stdAsympCrownHt>"
       << "<tr_stdCrownHtExp>"
       << "<tr_scheVal species=\"Species_1\">1.0</tr_scheVal>"
       << "<tr_scheVal species=\"Species_2\">1.0</tr_scheVal>"
       << "<tr_scheVal species=\"Species_3\">1.0</tr_scheVal>"
       << "<tr_scheVal species=\"Species_4\">1.0</tr_scheVal>"
       << "<tr_scheVal species=\"Species_5\">1.0</tr_scheVal>"
       << "</tr_stdCrownHtExp>"
       << "<tr_slopeOfHeight-Diam10>"
       << "<tr_sohdVal species=\"Species_1\">0.03418</tr_sohdVal>"
       << "<tr_sohdVal species=\"Species_2\">0.0269</tr_sohdVal>"
       << "<tr_sohdVal species=\"Species_3\">0.02871</tr_sohdVal>"
       << "<tr_sohdVal species=\"Species_4\">0.02871</tr_sohdVal>"
       << "<tr_sohdVal species=\"Species_5\">0.02871</tr_sohdVal>"
       << "</tr_slopeOfHeight-Diam10>"
       << "<tr_slopeOfAsymHeight>"
       << "<tr_soahVal species=\"Species_1\">0.0299</tr_soahVal>"
       << "<tr_soahVal species=\"Species_2\">0.0241</tr_soahVal>"
       << "<tr_soahVal species=\"Species_3\">0.0263</tr_soahVal>"
       << "<tr_soahVal species=\"Species_4\">0.0263</tr_soahVal>"
       << "<tr_soahVal species=\"Species_5\">0.0263</tr_soahVal>"
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
       << "<behaviorName>NonSpatialDisperse</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>GapDisperse</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>2</listPosition>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>NonGapDisperse</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>3</listPosition>"
       << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
       << "</behavior>"
       << "</behaviorList>"
       << "<GapDisperse2>"
       << "<di_weibullCanopySTR>"
       << "<di_wcsVal species=\"Species_2\">19.325</di_wcsVal>"
       << "</di_weibullCanopySTR>"
       << "<di_weibullCanopyBeta>"
       << "<di_wcbVal species=\"Species_2\">2.0</di_wcbVal>"
       << "</di_weibullCanopyBeta>"
       << "<di_weibullCanopyDispersal>"
       << "<di_wcdVal species=\"Species_2\">1.76E-4</di_wcdVal>"
       << "</di_weibullCanopyDispersal>"
       << "<di_weibullCanopyTheta>"
       << "<di_wctVal species=\"Species_2\">3.0</di_wctVal>"
       << "</di_weibullCanopyTheta>"
       << "<di_weibullGapSTR>"
       << "<di_wgsVal species=\"Species_2\">14.894</di_wgsVal>"
       << "</di_weibullGapSTR>"
       << "<di_weibullGapBeta>"
       << "<di_wgbVal species=\"Species_2\">2.3</di_wgbVal>"
       << "</di_weibullGapBeta>"
       << "<di_weibullGapDispersal>"
       << "<di_wgdVal species=\"Species_2\">1.32E-4</di_wgdVal>"
       << "</di_weibullGapDispersal>"
       << "<di_weibullGapTheta>"
       << "<di_wgtVal species=\"Species_2\">3.0</di_wgtVal>"
       << "</di_weibullGapTheta>"
       << "<di_maxGapDensity>0</di_maxGapDensity>"
       << "<di_gapFunction>"
       << "<di_gfVal species=\"Species_2\">0</di_gfVal>"
       << "</di_gapFunction>"
       << "<di_canopyFunction>"
       << "<di_cfVal species=\"Species_2\">0</di_cfVal>"
       << "</di_canopyFunction>"
       << "<di_minDbhForReproduction>"
       << "<di_mdfrVal species=\"Species_2\">15.0</di_mdfrVal>"
       << "</di_minDbhForReproduction>"
       << "</GapDisperse2>"
       << "<NonGapDisperse3>"
       << "<di_weibullCanopySTR>"
       << "<di_wcsVal species=\"Species_3\">19.325</di_wcsVal>"
       << "</di_weibullCanopySTR>"
       << "<di_weibullCanopyBeta>"
       << "<di_wcbVal species=\"Species_3\">2.0</di_wcbVal>"
       << "</di_weibullCanopyBeta>"
       << "<di_weibullCanopyDispersal>"
       << "<di_wcdVal species=\"Species_3\">1.76E-4</di_wcdVal>"
       << "</di_weibullCanopyDispersal>"
       << "<di_weibullCanopyTheta>"
       << "<di_wctVal species=\"Species_3\">3.0</di_wctVal>"
       << "</di_weibullCanopyTheta>"
       << "<di_canopyFunction>"
       << "<di_cfVal species=\"Species_3\">0</di_cfVal>"
       << "</di_canopyFunction>"
       << "<di_minDbhForReproduction>"
       << "<di_mdfrVal species=\"Species_3\">15.0</di_mdfrVal>"
       << "</di_minDbhForReproduction>"
       << "</NonGapDisperse3>"
       << "<NonSpatialDisperse1>"
       << "<di_nonSpatialSlopeOfLambda>"
       << "<di_nssolVal species=\"Species_1\">0</di_nssolVal>"
       << "</di_nonSpatialSlopeOfLambda>"
       << "<di_nonSpatialInterceptOfLambda>"
       << "<di_nsiolVal species=\"Species_1\">0.3</di_nsiolVal>"
       << "</di_nonSpatialInterceptOfLambda>"
       << "<di_minDbhForReproduction>"
       << "<di_mdfrVal species=\"Species_1\">15.0</di_mdfrVal>"
       << "</di_minDbhForReproduction>"
       << "</NonSpatialDisperse1>"
       << "<GeneralDisperse>"
       << "<di_seedDistributionMethod>0</di_seedDistributionMethod>"
       << "</GeneralDisperse>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}
