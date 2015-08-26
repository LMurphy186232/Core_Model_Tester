//---------------------------------------------------------------------------
// TestLaggedPostHarvestGrowth.cpp
//---------------------------------------------------------------------------
#include "TestLaggedPostHarvestGrowth.h"
#include <gtest/gtest.h>
#include <fstream>
#include <math.h>
#include "TreePopulation.h"
#include "SimManager.h"
#include "BehaviorBase.h"

////////////////////////////////////////////////////////////////////////////
// TestLaggedPostHarvestGrowth()
// Tests pre- and post-harvest growth over 4 timesteps with a timestep length
// of 2 years. 10 identical trees are created and have growth applied to them.
// In the second timestep, 5 of these trees are harvested. The diameter of a
// representative tree is checked after each timestep to make sure it is
// correct.
////////////////////////////////////////////////////////////////////////////
TEST(LaggedPostHarvestGrowth, TestLaggedPostHarvestGrowth) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {

  clSimManager *p_oSimManager = new clSimManager(4, 2, "");
  clTreePopulation * p_oPop;
  clTreeSearch *p_oAllTrees;
  clTree *p_oTree;
  float fDiam;
  int i;

  //Load our test file and get our tree population pointers
  p_oSimManager->ReadFile( WriteLaggedPostHarvestGrowthXMLFile() );
  p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );

  //Create ten identical trees
  for (i=0;i<10;i++) {
  	p_oPop->CreateTree(1, 1, 0, clTreePopulation::adult, 20.0);
  }

  //Run first timestep
   p_oSimManager->RunSim(1);
  //Confirm sample tree after ts 1
  p_oAllTrees = p_oPop->Find("all");
  p_oTree = p_oAllTrees->NextTree();
  p_oTree->GetValue(p_oPop->GetDbhCode(0,clTreePopulation::adult), &fDiam);
  EXPECT_LT(fabs(fDiam - 20.0660), 0.001);

  //Run second timestep
   p_oSimManager->RunSim(1);
  //Confirm sample tree after ts 2
  p_oAllTrees = p_oPop->Find("all");
  p_oTree = p_oAllTrees->NextTree();
  p_oTree->GetValue(p_oPop->GetDbhCode(0,clTreePopulation::adult), &fDiam);
  EXPECT_LT(fabs(fDiam - 20.1319), 0.001);

  //Run third timestep
   p_oSimManager->RunSim(1);
  //Confirm sample tree after ts 3
  p_oAllTrees = p_oPop->Find("all");
  p_oTree = p_oAllTrees->NextTree();
  p_oTree->GetValue(p_oPop->GetDbhCode(0,clTreePopulation::adult), &fDiam);
  EXPECT_LT(fabs(fDiam - 20.2409), 0.001);

  //Run fourth timestep
   p_oSimManager->RunSim(1);
  //Confirm sample tree after ts 4
  p_oAllTrees = p_oPop->Find("all");
  p_oTree = p_oAllTrees->NextTree();
  p_oTree->GetValue(p_oPop->GetDbhCode(0,clTreePopulation::adult), &fDiam);
  EXPECT_LT(fabs(fDiam - 20.3691), 0.001);


  delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

////////////////////////////////////////////////////////////////////////////
// WriteLaggedPostHarvestGrowthXMLFile()
////////////////////////////////////////////////////////////////////////////
const char* WriteLaggedPostHarvestGrowthXMLFile() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  //Write file
  oOut << "<?xml version=\"1.0\" standalone=\"no\"?>"
       << "<paramFile fileCode=\"06080101\">"
       << "<plot>"
       << "<timesteps>4</timesteps>"
       << "<randomSeed>0</randomSeed>"
       << "<yearsPerTimestep>2.0</yearsPerTimestep>"
       << "<plot_lenX>8</plot_lenX>"
       << "<plot_lenY>8</plot_lenY>"
       << "<plot_latitude>40.0</plot_latitude>"
       << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
       << "<plot_temp_C>12.88171785</plot_temp_C>"
       << "</plot>"
       << "<trees>"
       << "<tr_speciesList>"
       << "<tr_species speciesName=\"sp1\"/>"
       << "</tr_speciesList>"
       << "<tr_seedDiam10Cm>1.0</tr_seedDiam10Cm>"
       << "<tr_minAdultDBH>"
       << "<tr_madVal species=\"sp1\">5.0</tr_madVal>"
       << "</tr_minAdultDBH>"
       << "<tr_maxSeedlingHeight>"
       << "<tr_mshVal species=\"sp1\">1.35</tr_mshVal>"
       << "</tr_maxSeedlingHeight>"
       << "</trees>"
       << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>Harvest</behaviorName>"
       << "<version>1.0</version>"
       << "<listPosition>1</listPosition>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>LaggedPostHarvestGrowth</behaviorName>"
       << "<version>1.0</version>"
       << "<listPosition>2</listPosition>"
       << "<applyTo species=\"sp1\" type=\"Adult\"/>"
       << "</behavior>"
       << "</behaviorList>"
       << "<allometry>"
       << "<tr_whatAdultHeightDiam>"
       << "<tr_wahdVal species=\"sp1\">0</tr_wahdVal>"
       << "</tr_whatAdultHeightDiam>"
       << "<tr_whatSaplingHeightDiam>"
       << "<tr_wsahdVal species=\"sp1\">0</tr_wsahdVal>"
       << "</tr_whatSaplingHeightDiam>"
       << "<tr_whatSeedlingHeightDiam>"
       << "<tr_wsehdVal species=\"sp1\">0</tr_wsehdVal>"
       << "</tr_whatSeedlingHeightDiam>"
       << "<tr_whatAdultCrownRadDiam>"
       << "<tr_wacrdVal species=\"sp1\">0</tr_wacrdVal>"
       << "</tr_whatAdultCrownRadDiam>"
       << "<tr_whatSaplingCrownRadDiam>"
       << "<tr_wscrdVal species=\"sp1\">0</tr_wscrdVal>"
       << "</tr_whatSaplingCrownRadDiam>"
       << "<tr_whatAdultCrownHeightHeight>"
       << "<tr_wachhVal species=\"sp1\">0</tr_wachhVal>"
       << "</tr_whatAdultCrownHeightHeight>"
       << "<tr_whatSaplingCrownHeightHeight>"
       << "<tr_wschhVal species=\"sp1\">0</tr_wschhVal>"
       << "</tr_whatSaplingCrownHeightHeight>"
       << "<tr_canopyHeight>"
       << "<tr_chVal species=\"sp1\">15.0</tr_chVal>"
       << "</tr_canopyHeight>"
       << "<tr_stdAsympCrownRad>"
       << "<tr_sacrVal species=\"sp1\">1.0</tr_sacrVal>"
       << "</tr_stdAsympCrownRad>"
       << "<tr_stdCrownRadExp>"
       << "<tr_screVal species=\"sp1\">1.0</tr_screVal>"
       << "</tr_stdCrownRadExp>"
       << "<tr_stdMaxCrownRad>"
       << "<tr_smcrVal species=\"sp1\">10</tr_smcrVal>"
       << "</tr_stdMaxCrownRad>"
       << "<tr_stdAsympCrownHt>"
       << "<tr_sachVal species=\"sp1\">1.0</tr_sachVal>"
       << "</tr_stdAsympCrownHt>"
       << "<tr_stdCrownHtExp>"
       << "<tr_scheVal species=\"sp1\">1.0</tr_scheVal>"
       << "</tr_stdCrownHtExp>"
       << "<tr_conversionDiam10ToDBH>"
       << "<tr_cdtdVal species=\"sp1\">1.0</tr_cdtdVal>"
       << "</tr_conversionDiam10ToDBH>"
       << "<tr_interceptDiam10ToDBH>"
       << "<tr_idtdVal species=\"sp1\">0.0</tr_idtdVal>"
       << "</tr_interceptDiam10ToDBH>"
       << "<tr_slopeOfAsymHeight>"
       << "<tr_soahVal species=\"sp1\">1.0</tr_soahVal>"
       << "</tr_slopeOfAsymHeight>"
       << "<tr_slopeOfHeight-Diam10>"
       << "<tr_sohdVal species=\"sp1\">1.0</tr_sohdVal>"
       << "</tr_slopeOfHeight-Diam10>"
       << "<tr_adultLinearSlope>"
       << "<tr_alsVal species=\"sp1\">1.0</tr_alsVal>"
       << "</tr_adultLinearSlope>"
       << "<tr_adultLinearIntercept>"
       << "<tr_aliVal species=\"sp1\">1.0</tr_aliVal>"
       << "</tr_adultLinearIntercept>"
       << "<tr_adultReverseLinearSlope>"
       << "<tr_arlsVal species=\"sp1\">1.0</tr_arlsVal>"
       << "</tr_adultReverseLinearSlope>"
       << "<tr_adultReverseLinearIntercept>"
       << "<tr_arliVal species=\"sp1\">1.0</tr_arliVal>"
       << "</tr_adultReverseLinearIntercept>"
       << "<tr_saplingLinearSlope>"
       << "<tr_salsVal species=\"sp1\">1.0</tr_salsVal>"
       << "</tr_saplingLinearSlope>"
       << "<tr_saplingLinearIntercept>"
       << "<tr_aliVal species=\"sp1\">1.0</tr_aliVal>"
       << "</tr_saplingLinearIntercept>"
       << "<tr_saplingReverseLinearSlope>"
       << "<tr_sarlsVal species=\"sp1\">1.0</tr_sarlsVal>"
       << "</tr_saplingReverseLinearSlope>"
       << "<tr_saplingReverseLinearIntercept>"
       << "<tr_sarliVal species=\"sp1\">1.0</tr_sarliVal>"
       << "</tr_saplingReverseLinearIntercept>"
       << "<tr_saplingPowerA>"
       << "<tr_sapaVal species=\"sp1\">1.0</tr_sapaVal>"
       << "</tr_saplingPowerA>"
       << "<tr_saplingPowerB>"
       << "<tr_sapbVal species=\"sp1\">1.0</tr_sapbVal>"
       << "</tr_saplingPowerB>"
       << "<tr_seedlingLinearSlope>"
       << "<tr_selsVal species=\"sp1\">1.0</tr_selsVal>"
       << "</tr_seedlingLinearSlope>"
       << "<tr_seedlingLinearIntercept>"
       << "<tr_seliVal species=\"sp1\">1.0</tr_seliVal>"
       << "</tr_seedlingLinearIntercept>"
       << "<tr_seedlingReverseLinearSlope>"
       << "<tr_serlsVal species=\"sp1\">1.0</tr_serlsVal>"
       << "</tr_seedlingReverseLinearSlope>"
       << "<tr_seedlingReverseLinearIntercept>"
       << "<tr_serliVal species=\"sp1\">1.0</tr_serliVal>"
       << "</tr_seedlingReverseLinearIntercept>"
       << "<tr_chRichCrownRadIntercept>"
       << "<tr_crcriVal species=\"sp1\">1.0</tr_crcriVal>"
       << "</tr_chRichCrownRadIntercept>"
       << "<tr_chRichCrownRadAsymp>"
       << "<tr_crcraVal species=\"sp1\">1.0</tr_crcraVal>"
       << "</tr_chRichCrownRadAsymp>"
       << "<tr_chRichCrownRadShape1b>"
       << "<tr_crcrs1bVal species=\"sp1\">1.0</tr_crcrs1bVal>"
       << "</tr_chRichCrownRadShape1b>"
       << "<tr_chRichCrownRadShape2c>"
       << "<tr_crcrs2cVal species=\"sp1\">1.0</tr_crcrs2cVal>"
       << "</tr_chRichCrownRadShape2c>"
       << "<tr_chRichCrownHtIntercept>"
       << "<tr_crchiVal species=\"sp1\">1.0</tr_crchiVal>"
       << "</tr_chRichCrownHtIntercept>"
       << "<tr_chRichCrownHtAsymp>"
       << "<tr_crchaVal species=\"sp1\">1.0</tr_crchaVal>"
       << "</tr_chRichCrownHtAsymp>"
       << "<tr_chRichCrownHtShape1b>"
       << "<tr_crchs1bVal species=\"sp1\">1.0</tr_crchs1bVal>"
       << "</tr_chRichCrownHtShape1b>"
       << "<tr_chRichCrownHtShape2c>"
       << "<tr_crchs2cVal species=\"sp1\">1.0</tr_crchs2cVal>"
       << "</tr_chRichCrownHtShape2c>"
       << "</allometry>"
       << "<Harvest1>"
       << "<ha_cutEvent>"
       << "<ha_applyToSpecies species=\"sp1\"/>"
       << "<ha_timestep>2</ha_timestep>"
       << "<ha_cutType>partial</ha_cutType>"
       << "<ha_cutAmountType>percent of basal area</ha_cutAmountType>"
       << "<ha_dbhRange>"
       << "<ha_low>10.0</ha_low>"
       << "<ha_high>21.0</ha_high>"
       << "<ha_amountToCut>51.0</ha_amountToCut>"
       << "</ha_dbhRange>"
       << "<ha_applyToCell x=\"0\" y=\"0\"/>"
       << "</ha_cutEvent>"
       << "</Harvest1>"
       << "<LaggedPostHarvestGrowth2>"
       << "<gr_lagMaxGrowthConstant>"
       << "<gr_lmgcVal species=\"sp1\">1.5</gr_lmgcVal>"
       << "</gr_lagMaxGrowthConstant>"
       << "<gr_lagMaxGrowthDbhEffect>"
       << "<gr_lmgdbheVal species=\"sp1\">0.04</gr_lmgdbheVal>"
       << "</gr_lagMaxGrowthDbhEffect>"
       << "<gr_lagNciConstant>"
       << "<gr_lncicVal species=\"sp1\">100</gr_lncicVal>"
       << "</gr_lagNciConstant>"
       << "<gr_lagNciDbhEffect>"
       << "<gr_lncidbheVal species=\"sp1\">0.15</gr_lncidbheVal>"
       << "</gr_lagNciDbhEffect>"
       << "<gr_lagTimeSinceHarvestRateParam>"
       << "<gr_ltshrpVal species=\"sp1\">0.4</gr_ltshrpVal>"
       << "</gr_lagTimeSinceHarvestRateParam>"
       << "<gr_lagNciDistanceRadius>5</gr_lagNciDistanceRadius>"
       << "</LaggedPostHarvestGrowth2>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

