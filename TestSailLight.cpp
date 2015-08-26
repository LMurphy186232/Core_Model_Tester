//---------------------------------------------------------------------------
// TestSailLight.cpp
//---------------------------------------------------------------------------
#include "TestSailLight.h"
#include <gtest/gtest.h>
#include <fstream>
#include <math.h>
#include "TreePopulation.h"
#include "SimManager.h"

////////////////////////////////////////////////////////////////////////////
// Run1()
// Tests light extinction coefficient management by taking a target tree and
// surrounding it with both live and snag neighbors to see if the amount of
// shade calculated by sail light comes out right. WriteSailLightXMLFile1() is
// used to set up the run. A single sapling of species 1 is created, along with
// four neighbors. Then sail light is run and the resulting shade is compared
// to expected.
//
// This run uses top-of-crown fisheye.
////////////////////////////////////////////////////////////////////////////
TEST(SailLight, Run1) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    clTreePopulation * p_oPop;
    clTree *p_oTargetTree, *p_oDeadTree, *p_oTree;
    float fLight, fExpectedLight, fDiam;

    //Load our test file and get our tree population pointers
    p_oSimManager->ReadFile( WriteSailLightXMLFile1() );
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );

    //Create our target, Species 1
    fDiam = 8;
    p_oTargetTree = p_oPop->CreateTree(50, 50, 0, clTreePopulation::sapling, fDiam);

    //Neighbors - and set the snag ages
    p_oPop->CreateTree(53, 52, 0, clTreePopulation::adult, 15.0);
    p_oTree = p_oPop->CreateTree(59, 50, 0, clTreePopulation::snag, 15.0);
    p_oTree->SetValue(p_oPop->GetAgeCode(0), 2);
    p_oTree = p_oPop->CreateTree(50, 59, 0, clTreePopulation::snag, 15.0);
    p_oTree->SetValue(p_oPop->GetAgeCode(0), 6);
    p_oTree = p_oPop->CreateTree(55, 55, 0, clTreePopulation::snag, 15.0);
    p_oTree->SetValue(p_oPop->GetAgeCode(0), 11);
    //Dead neighbor
    p_oDeadTree = p_oPop->CreateTree(52, 52, 0, clTreePopulation::adult, 20.0);
    p_oDeadTree->SetValue(p_oPop->GetIntDataCode("dead", p_oDeadTree->GetSpecies(), p_oDeadTree->GetType()), natural);

    //Run the behavior
    p_oSimManager->RunSim(1);

    //See if our target tree's shade value is right
    fExpectedLight = 0.207024788;
    p_oTargetTree->GetValue(p_oPop->GetFloatDataCode("Light", p_oTargetTree->GetSpecies(), p_oTargetTree->GetType()), &fLight);
    EXPECT_LT(fabs(fExpectedLight - fLight), 0.001);

    //Make sure that our dead tree did not get light calculated
    p_oDeadTree->GetValue(p_oPop->GetFloatDataCode("Light", p_oDeadTree->GetSpecies(), p_oDeadTree->GetType()), &fLight);
    EXPECT_EQ(0, fLight);
    delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

////////////////////////////////////////////////////////////////////////////
// Run2()
// Tests light extinction coefficient management by taking 2 target trees and
// surrounding them with neighbors to see if the amount of shade calculated by
// sail light comes out right. WriteSailLightXMLFile2() is used to set up the
// run.
//
// This run uses mid-crown fisheye (with a seedling to make sure it still gets
// top-of-crown), and differing crown radius equations for saplings and
// adults.
////////////////////////////////////////////////////////////////////////////
TEST(SailLight, Run2) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    clTreePopulation * p_oPop;
    clTree *p_oTargetTree1, *p_oTargetTree2, *p_oTargetTree3;
    float fLight, fExpectedLight, fDiam;

    //Load our test file and get our tree population pointers
    p_oSimManager->ReadFile( WriteSailLightXMLFile2() );
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );

    //Create our target # 1
    fDiam = 8;
    p_oTargetTree1 = p_oPop->CreateTree(50, 50, 0, clTreePopulation::sapling, fDiam);

    //Create our target # 2
    fDiam = 1;
    p_oTargetTree2 = p_oPop->CreateTree(52, 52, 0, clTreePopulation::seedling, fDiam);

    //Create our target # 3
    fDiam = 15;
    p_oTargetTree3 = p_oPop->CreateTree(53, 52, 0, clTreePopulation::adult, fDiam);

    //Neighbors
    p_oPop->CreateTree(59, 50, 0, clTreePopulation::adult, 45.0);
    p_oPop->CreateTree(50, 59, 0, clTreePopulation::adult, 15.0);
    p_oPop->CreateTree(55, 55, 0, clTreePopulation::sapling, 9.0);

    //Run the behavior
    p_oSimManager->RunSim(1);

    //See if our target trees' shade value is right
    fExpectedLight = 0.20391627;
    p_oTargetTree1->GetValue(p_oPop->GetFloatDataCode("Light", p_oTargetTree1->GetSpecies(), p_oTargetTree1->GetType()), &fLight);
    EXPECT_LT(fabs(fExpectedLight - fLight), 0.001);

    fExpectedLight = 0.244686637;
    p_oTargetTree2->GetValue(p_oPop->GetFloatDataCode("Light", p_oTargetTree2->GetSpecies(), p_oTargetTree2->GetType()), &fLight);
    EXPECT_LT(fabs(fExpectedLight - fLight), 0.001);

    fExpectedLight = 0.19391829;
    p_oTargetTree3->GetValue(p_oPop->GetFloatDataCode("Light", p_oTargetTree3->GetSpecies(), p_oTargetTree3->GetType()), &fLight);
    EXPECT_LT(fabs(fExpectedLight - fLight), 0.001);
    delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

////////////////////////////////////////////////////////////////////////////
// WriteSailLightXMLFile1()
////////////////////////////////////////////////////////////////////////////
const char* WriteSailLightXMLFile1() {
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
      << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
      << "<plot_temp_C>12.88171785</plot_temp_C>"
      << "<plot_latitude>55.37</plot_latitude>"
      << "</plot>"
      << "<trees>"
      << "<tr_speciesList>"
      << "<tr_species speciesName=\"Species_1\" />"
      << "</tr_speciesList>"
      << "<tr_seedDiam10Cm>0.1</tr_seedDiam10Cm>"
      << "<tr_minAdultDBH>"
      << "<tr_madVal species=\"Species_1\">10.0</tr_madVal>"
      << "</tr_minAdultDBH>"
      << "<tr_maxSeedlingHeight>"
      << "<tr_mshVal species=\"Species_1\">1.35</tr_mshVal>"
      << "</tr_maxSeedlingHeight>"
      << "</trees>"
      << "<allometry>"
      << "<tr_canopyHeight>"
      << "<tr_chVal species=\"Species_1\">39.48</tr_chVal>"
      << "</tr_canopyHeight>"
      << "<tr_stdAsympCrownRad>"
      << "<tr_sacrVal species=\"Species_1\">0.0549</tr_sacrVal>"
      << "</tr_stdAsympCrownRad>"
      << "<tr_stdCrownRadExp>"
      << "<tr_screVal species=\"Species_1\">1.0</tr_screVal>"
      << "</tr_stdCrownRadExp>"
      << "<tr_stdMaxCrownRad>"
      << "<tr_smcrVal species=\"Species_1\">10</tr_smcrVal>"
      << "</tr_stdMaxCrownRad>"
      << "<tr_conversionDiam10ToDBH>"
      << "<tr_cdtdVal species=\"Species_1\">0.8008</tr_cdtdVal>"
      << "</tr_conversionDiam10ToDBH>"
      << "<tr_interceptDiam10ToDBH>"
      << "<tr_idtdVal species=\"Species_1\">0</tr_idtdVal>"
      << "</tr_interceptDiam10ToDBH>"
      << "<tr_stdAsympCrownHt>"
      << "<tr_sachVal species=\"Species_1\">0.389</tr_sachVal>"
      << "</tr_stdAsympCrownHt>"
      << "<tr_stdCrownHtExp>"
      << "<tr_scheVal species=\"Species_1\">1.0</tr_scheVal>"
      << "</tr_stdCrownHtExp>"
      << "<tr_slopeOfHeight-Diam10>"
      << "<tr_sohdVal species=\"Species_1\">0.03418</tr_sohdVal>"
      << "</tr_slopeOfHeight-Diam10>"
      << "<tr_slopeOfAsymHeight>"
      << "<tr_soahVal species=\"Species_1\">0.0299</tr_soahVal>"
      << "</tr_slopeOfAsymHeight>"
      << "<tr_whatSeedlingHeightDiam>"
      << "<tr_wsehdVal species=\"Species_1\">0</tr_wsehdVal>"
      << "</tr_whatSeedlingHeightDiam>"
      << "<tr_whatSaplingHeightDiam>"
      << "<tr_wsahdVal species=\"Species_1\">0</tr_wsahdVal>"
      << "</tr_whatSaplingHeightDiam>"
      << "<tr_whatAdultHeightDiam>"
      << "<tr_wahdVal species=\"Species_1\">0</tr_wahdVal>"
      << "</tr_whatAdultHeightDiam>"
      << "<tr_whatAdultCrownRadDiam>"
      << "<tr_wacrdVal species=\"Species_1\">0</tr_wacrdVal>"
      << "</tr_whatAdultCrownRadDiam>"
      << "<tr_whatAdultCrownHeightHeight>"
      << "<tr_wachhVal species=\"Species_1\">0</tr_wachhVal>"
      << "</tr_whatAdultCrownHeightHeight>"
      << "<tr_whatSaplingCrownRadDiam>"
      << "<tr_wscrdVal species=\"Species_1\">0</tr_wscrdVal>"
      << "</tr_whatSaplingCrownRadDiam>"
      << "<tr_whatSaplingCrownHeightHeight>"
      << "<tr_wschhVal species=\"Species_1\">0</tr_wschhVal>"
      << "</tr_whatSaplingCrownHeightHeight>"
      << "</allometry>"
      << "<behaviorList>"
      << "<behavior>"
      << "<behaviorName>SailLight</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>1</listPosition>"
      << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>ConstantGLI</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>2</listPosition>"
      << "<applyTo species=\"Species_1\" type=\"Snag\"/>"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>ConstRadialGrowth</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>3</listPosition>"
      << "<applyTo species=\"Species_1\" type=\"Snag\"/>"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>StochasticMortality</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>4</listPosition>"
      << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
      << "</behavior>"
      << "</behaviorList>"
      << "<ConstantGLI2>"
      << "<li_constGLI>100</li_constGLI>"
      << "</ConstantGLI2>"
      << "<SailLight1>"
      << "<li_maxShadingRadius>15.0</li_maxShadingRadius>"
      << "<li_skyMaskAngle>30.0</li_skyMaskAngle>"
      << "<li_crownFracOfHeight>0</li_crownFracOfHeight>"
      << "<li_heightOfFishEyePhoto>1</li_heightOfFishEyePhoto>"
      << "<li_beamFractGlobalRad>0.5</li_beamFractGlobalRad>"
      << "<li_clearSkyTransCoeff>0.65</li_clearSkyTransCoeff>"
      << "<li_julianDayGrowthStarts>120</li_julianDayGrowthStarts>"
      << "<li_julianDayGrowthEnds>270</li_julianDayGrowthEnds>"
      << "<li_minSunAngle>0.785</li_minSunAngle>"
      << "<li_lightExtinctionCoefficient>"
      << "<li_lecVal species=\"Species_1\">0.1</li_lecVal>"
      << "</li_lightExtinctionCoefficient>"
      << "<li_snag1LightExtinctionCoefficient>"
      << "<li_s1lecVal species=\"Species_1\">0.3</li_s1lecVal>"
      << "</li_snag1LightExtinctionCoefficient>"
      << "<li_snag2LightExtinctionCoefficient>"
      << "<li_s2lecVal species=\"Species_1\">0.5</li_s2lecVal>"
      << "</li_snag2LightExtinctionCoefficient>"
      << "<li_snag3LightExtinctionCoefficient>"
      << "<li_s3lecVal species=\"Species_1\">0.7</li_s3lecVal>"
      << "</li_snag3LightExtinctionCoefficient>"
      << "<li_snagAgeClass1>3</li_snagAgeClass1>"
      << "<li_snagAgeClass2>10</li_snagAgeClass2>"
      << "</SailLight1>"
      << "<ConstRadialGrowth3>"
      << "<gr_adultConstRadialInc>"
      << "<gr_acriVal species=\"Species_1\">1.14</gr_acriVal>"
      << "</gr_adultConstRadialInc>"
      << "</ConstRadialGrowth3>"
      << "<StochasticMortality4>"
      << "<mo_stochasticMortRate>"
      << "<mo_smrVal species=\"Species_1\">0</mo_smrVal>"
      << "</mo_stochasticMortRate>"
      << "</StochasticMortality4>"
      << "</paramFile>";

  oOut.close();

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteSailLightXMLFile2()
////////////////////////////////////////////////////////////////////////////
const char* WriteSailLightXMLFile2() {
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
      << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
      << "<plot_temp_C>12.88171785</plot_temp_C>"
      << "<plot_latitude>55.37</plot_latitude>"
      << "</plot>"
      << "<trees>"
      << "<tr_speciesList>"
      << "<tr_species speciesName=\"Species_1\" />"
      << "</tr_speciesList>"
      << "<tr_seedDiam10Cm>0.1</tr_seedDiam10Cm>"
      << "<tr_minAdultDBH>"
      << "<tr_madVal species=\"Species_1\">10.0</tr_madVal>"
      << "</tr_minAdultDBH>"
      << "<tr_maxSeedlingHeight>"
      << "<tr_mshVal species=\"Species_1\">1.35</tr_mshVal>"
      << "</tr_maxSeedlingHeight>"
      << "</trees>"
      << "<allometry>"
      << "<tr_canopyHeight>"
      << "<tr_chVal species=\"Species_1\">39.48</tr_chVal>"
      << "</tr_canopyHeight>"
      << "<tr_stdAsympCrownRad>"
      << "<tr_sacrVal species=\"Species_1\">0.0549</tr_sacrVal>"
      << "</tr_stdAsympCrownRad>"
      << "<tr_stdCrownRadExp>"
      << "<tr_screVal species=\"Species_1\">1.0</tr_screVal>"
      << "</tr_stdCrownRadExp>"
      << "<tr_stdMaxCrownRad>"
      << "<tr_smcrVal species=\"Species_1\">10</tr_smcrVal>"
      << "</tr_stdMaxCrownRad>"
      << "<tr_conversionDiam10ToDBH>"
      << "<tr_cdtdVal species=\"Species_1\">0.8008</tr_cdtdVal>"
      << "</tr_conversionDiam10ToDBH>"
      << "<tr_interceptDiam10ToDBH>"
      << "<tr_idtdVal species=\"Species_1\">0</tr_idtdVal>"
      << "</tr_interceptDiam10ToDBH>"
      << "<tr_stdAsympCrownHt>"
      << "<tr_sachVal species=\"Species_1\">0.389</tr_sachVal>"
      << "</tr_stdAsympCrownHt>"
      << "<tr_stdCrownHtExp>"
      << "<tr_scheVal species=\"Species_1\">1.0</tr_scheVal>"
      << "</tr_stdCrownHtExp>"
      << "<tr_slopeOfHeight-Diam10>"
      << "<tr_sohdVal species=\"Species_1\">0.03418</tr_sohdVal>"
      << "</tr_slopeOfHeight-Diam10>"
      << "<tr_slopeOfAsymHeight>"
      << "<tr_soahVal species=\"Species_1\">0.0299</tr_soahVal>"
      << "</tr_slopeOfAsymHeight>"
      << "<tr_whatSeedlingHeightDiam>"
      << "<tr_wsehdVal species=\"Species_1\">0</tr_wsehdVal>"
      << "</tr_whatSeedlingHeightDiam>"
      << "<tr_whatSaplingHeightDiam>"
      << "<tr_wsahdVal species=\"Species_1\">0</tr_wsahdVal>"
      << "</tr_whatSaplingHeightDiam>"
      << "<tr_whatAdultHeightDiam>"
      << "<tr_wahdVal species=\"Species_1\">0</tr_wahdVal>"
      << "</tr_whatAdultHeightDiam>"
      << "<tr_whatAdultCrownRadDiam>"
      << "<tr_wacrdVal species=\"Species_1\">0</tr_wacrdVal>"
      << "</tr_whatAdultCrownRadDiam>"
      << "<tr_whatAdultCrownHeightHeight>"
      << "<tr_wachhVal species=\"Species_1\">1</tr_wachhVal>"
      << "</tr_whatAdultCrownHeightHeight>"
      << "<tr_whatSaplingCrownRadDiam>"
      << "<tr_wscrdVal species=\"Species_1\">1</tr_wscrdVal>"
      << "</tr_whatSaplingCrownRadDiam>"
      << "<tr_whatSaplingCrownHeightHeight>"
      << "<tr_wschhVal species=\"Species_1\">0</tr_wschhVal>"
      << "</tr_whatSaplingCrownHeightHeight>"
      << "<tr_chRichCrownRadIntercept>"
      << "<tr_crcriVal species=\"Species_1\">0.3</tr_crcriVal>"
      << "</tr_chRichCrownRadIntercept>"
      << "<tr_chRichCrownRadAsymp>"
      << "<tr_crcraVal species=\"Species_1\">8</tr_crcraVal>"
      << "</tr_chRichCrownRadAsymp>"
      << "<tr_chRichCrownRadShape1b>"
      << "<tr_crcrs1bVal species=\"Species_1\">0.09</tr_crcrs1bVal>"
      << "</tr_chRichCrownRadShape1b>"
      << "<tr_chRichCrownRadShape2c>"
      << "<tr_crcrs2cVal species=\"Species_1\">1.5</tr_crcrs2cVal>"
      << "</tr_chRichCrownRadShape2c>"
      << "<tr_chRichCrownHtIntercept>"
      << "<tr_crchiVal species=\"Species_1\">0.6</tr_crchiVal>"
      << "</tr_chRichCrownHtIntercept>"
      << "<tr_chRichCrownHtAsymp>"
      << "<tr_crchaVal species=\"Species_1\">3</tr_crchaVal>"
      << "</tr_chRichCrownHtAsymp>"
      << "<tr_chRichCrownHtShape1b>"
      << "<tr_crchs1bVal species=\"Species_1\">0.3</tr_crchs1bVal>"
      << "</tr_chRichCrownHtShape1b>"
      << "<tr_chRichCrownHtShape2c>"
      << "<tr_crchs2cVal species=\"Species_1\">5.6</tr_crchs2cVal>"
      << "</tr_chRichCrownHtShape2c>"
      << "</allometry>"
      << "<behaviorList>"
      << "<behavior>"
      << "<behaviorName>SailLight</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>1</listPosition>"
      << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_1\" type=\"Seedling\"/>"
      << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
      << "</behavior>"
      << "</behaviorList>"
      << "<SailLight1>"
      << "<li_heightOfFishEyePhoto>0</li_heightOfFishEyePhoto>"
      << "<li_beamFractGlobalRad>0.5</li_beamFractGlobalRad>"
      << "<li_clearSkyTransCoeff>0.65</li_clearSkyTransCoeff>"
      << "<li_julianDayGrowthStarts>120</li_julianDayGrowthStarts>"
      << "<li_julianDayGrowthEnds>270</li_julianDayGrowthEnds>"
      << "<li_lightExtinctionCoefficient>"
      << "<li_lecVal species=\"Species_1\">0.1</li_lecVal>"
      << "</li_lightExtinctionCoefficient>"
      << "<li_maxShadingRadius>15.0</li_maxShadingRadius>"
      << "<li_skyMaskAngle>30.0</li_skyMaskAngle>"
      << "<li_crownFracOfHeight>1</li_crownFracOfHeight>"
      << "</SailLight1>"
      << "</paramFile>";

  oOut.close();

  return cFileString;
}
