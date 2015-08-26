//---------------------------------------------------------------------------
// TestNCISizeEffectCompoundExponential.cpp
//---------------------------------------------------------------------------
#include "TestNCISizeEffectCompoundExponential.h"
#include <gtest/gtest.h>
#include <fstream>
#include <math.h>
#include "TreePopulation.h"
#include "SimManager.h"
#include "BehaviorBase.h"
#include "DataTypes.h"
#include "NCIEffectsList.h"
#include "NCI/PrecipitationEffectBase.h"

using namespace std;

////////////////////////////////////////////////////////////////////////////
// TestRun1()
////////////////////////////////////////////////////////////////////////////
TEST(NCISizeEffectCompoundExponential, TestRun1) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    clTreePopulation * p_oPop;
    clTree *p_oTargetTree1, *p_oTargetTree2, *p_oTargetTree3, *p_oTargetTree4,
    *p_oTargetTree5, *p_oTargetTree6, *p_oTargetTree7, *p_oTargetTree8,
    *p_oTargetTree9, *p_oTargetTree;
    float fDiam, fExpectedDiam;
    int iSpecies;

    //Load our test file and get our tree population pointers
    p_oSimManager->ReadFile(WriteNCISizeEffectXMLFile1());
    p_oPop = (clTreePopulation *) p_oSimManager->GetPopulationObject(
        "treepopulation");

    //Create our trees
    fDiam = 11;
    iSpecies = 1;
    p_oTargetTree1 = p_oPop->CreateTree(10, 10, iSpecies,
        clTreePopulation::adult, fDiam);

    fDiam = 10.5;
    iSpecies = 1;
    p_oTargetTree2 = p_oPop->CreateTree(50, 50, iSpecies,
        clTreePopulation::adult, fDiam);

    fDiam = 15;
    iSpecies = 2;
    p_oTargetTree3 = p_oPop->CreateTree(53, 52, iSpecies,
        clTreePopulation::adult, fDiam);

    fDiam = 25;
    iSpecies = 3;
    p_oTargetTree4 = p_oPop->CreateTree(59, 50, iSpecies,
        clTreePopulation::adult, fDiam);

    fDiam = 30;
    iSpecies = 1;
    p_oTargetTree5 = p_oPop->CreateTree(50, 59, iSpecies,
        clTreePopulation::adult, fDiam);

    fDiam = 45;
    iSpecies = 2;
    p_oTargetTree6 = p_oPop->CreateTree(55, 55, iSpecies,
        clTreePopulation::adult, fDiam);

    fDiam = 15;
    iSpecies = 3;
    p_oTargetTree7 = p_oPop->CreateTree(60, 61, iSpecies,
        clTreePopulation::adult, fDiam);

    fDiam = 4;
    iSpecies = 1;
    p_oTargetTree8 = p_oPop->CreateTree(52, 52, iSpecies,
        clTreePopulation::sapling, fDiam);

    fDiam = 4;
    iSpecies = 2;
    p_oTargetTree9 = p_oPop->CreateTree(53, 53, iSpecies,
        clTreePopulation::sapling, fDiam);

    //Now do the run
    p_oSimManager->RunSim(1);

    //Check the diameters and growth of the target trees
    fExpectedDiam = 11.2445478;
    p_oTargetTree = p_oTargetTree1;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);

    fExpectedDiam = 10.74388887;
    p_oTargetTree = p_oTargetTree2;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);

    fExpectedDiam = 24.92516866;
    p_oTargetTree = p_oTargetTree3;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);

    fExpectedDiam = 30.16767373;
    p_oTargetTree = p_oTargetTree4;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);

    fExpectedDiam = 30.2554591;
    p_oTargetTree = p_oTargetTree5;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);

    fExpectedDiam = 54.9875208;
    p_oTargetTree = p_oTargetTree6;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);

    fExpectedDiam = 20.01736366;
    p_oTargetTree = p_oTargetTree7;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);

    fExpectedDiam = 4.185400369;
    p_oTargetTree = p_oTargetTree8;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);

    fExpectedDiam = 11.46826547;
    p_oTargetTree = p_oTargetTree9;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);
    delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

////////////////////////////////////////////////////////////////////////////
// TestRun2()
////////////////////////////////////////////////////////////////////////////
TEST(NCISizeEffectCompoundExponential, TestRun2) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    clTreePopulation * p_oPop;
    clTree *p_oTargetTree1, *p_oTargetTree2, *p_oTargetTree3, *p_oTargetTree4,
    *p_oTargetTree5, *p_oTargetTree6, *p_oTargetTree7, *p_oTargetTree8,
    *p_oTargetTree9, *p_oTargetTree;
    float fDiam, fExpectedDiam;
    int iSpecies;

    //Load our test file and get our tree population pointers
    p_oSimManager->ReadFile(WriteNCISizeEffectXMLFile2());
    p_oPop = (clTreePopulation *) p_oSimManager->GetPopulationObject(
        "treepopulation");

    //Create our trees
    fDiam = 11;
    iSpecies = 1;
    p_oTargetTree1 = p_oPop->CreateTree(10, 10, iSpecies,
        clTreePopulation::adult, fDiam);

    fDiam = 10.5;
    iSpecies = 1;
    p_oTargetTree2 = p_oPop->CreateTree(50, 50, iSpecies,
        clTreePopulation::adult, fDiam);

    fDiam = 15;
    iSpecies = 2;
    p_oTargetTree3 = p_oPop->CreateTree(53, 52, iSpecies,
        clTreePopulation::adult, fDiam);

    fDiam = 25;
    iSpecies = 3;
    p_oTargetTree4 = p_oPop->CreateTree(59, 50, iSpecies,
        clTreePopulation::adult, fDiam);

    fDiam = 30;
    iSpecies = 1;
    p_oTargetTree5 = p_oPop->CreateTree(50, 59, iSpecies,
        clTreePopulation::adult, fDiam);

    fDiam = 45;
    iSpecies = 2;
    p_oTargetTree6 = p_oPop->CreateTree(55, 55, iSpecies,
        clTreePopulation::adult, fDiam);

    fDiam = 15;
    iSpecies = 3;
    p_oTargetTree7 = p_oPop->CreateTree(60, 61, iSpecies,
        clTreePopulation::adult, fDiam);

    fDiam = 4;
    iSpecies = 1;
    p_oTargetTree8 = p_oPop->CreateTree(52, 52, iSpecies,
        clTreePopulation::sapling, fDiam);

    fDiam = 4;
    iSpecies = 2;
    p_oTargetTree9 = p_oPop->CreateTree(53, 53, iSpecies,
        clTreePopulation::sapling, fDiam);

    //Now do the run
    p_oSimManager->RunSim(1);

    //Check the diameters and growth of the target trees
    fExpectedDiam = 11.73456773;
    p_oTargetTree = p_oTargetTree1;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);

    fExpectedDiam = 11.23263578;
    p_oTargetTree = p_oTargetTree2;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);

    fExpectedDiam = 44.90790501;
    p_oTargetTree = p_oTargetTree3;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);

    fExpectedDiam = 40.64823882;
    p_oTargetTree = p_oTargetTree4;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);

    fExpectedDiam = 30.76651856;
    p_oTargetTree = p_oTargetTree5;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);

    fExpectedDiam = 74.90682487;
    p_oTargetTree = p_oTargetTree6;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);

    fExpectedDiam = 30.28860685;
    p_oTargetTree = p_oTargetTree7;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);

    fExpectedDiam = 4.557337012;
    p_oTargetTree = p_oTargetTree8;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);

    fExpectedDiam = 27.33766085;
    p_oTargetTree = p_oTargetTree9;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);
    delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

////////////////////////////////////////////////////////////////////////////
// WriteNCIXMLFile1()
////////////////////////////////////////////////////////////////////////////
const char* WriteNCISizeEffectXMLFile1() {
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
       << "<plot_latitude>55.37</plot_latitude>"
       << "<plot_precip_mm_yr>115</plot_precip_mm_yr>"
       << "<plot_temp_C>12.88</plot_temp_C>"
       << "<plot_n_dep>4.76</plot_n_dep>"
       << "<plot_seasonal_precipitation>1150.65</plot_seasonal_precipitation>"
       << "<plot_water_deficit>456.2</plot_water_deficit>"
       << "</plot>";

  WriteNCISizeEffectTreeStuff(oOut);
  WriteNCISizeEffectCommonStuff(oOut);

  oOut.close();

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteNCIXMLFile2()
////////////////////////////////////////////////////////////////////////////
const char* WriteNCISizeEffectXMLFile2() {
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
       << "<yearsPerTimestep>3</yearsPerTimestep>"
       << "<randomSeed>1</randomSeed>"
       << "<plot_lenX>200.0</plot_lenX>"
       << "<plot_lenY>200.0</plot_lenY>"
       << "<plot_latitude>55.37</plot_latitude>"
       << "<plot_precip_mm_yr>115</plot_precip_mm_yr>"
       << "<plot_temp_C>12.88</plot_temp_C>"
       << "<plot_n_dep>4.76</plot_n_dep>"
       << "<plot_seasonal_precipitation>1150.65</plot_seasonal_precipitation>"
       << "<plot_water_deficit>456.2</plot_water_deficit>"
       << "</plot>";

  WriteNCISizeEffectTreeStuff(oOut);
  WriteNCISizeEffectCommonStuff(oOut);

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteNCISizeEffectNCITreeStuff()
/////////////////////////////////////////////////////////////////////////////
void WriteNCISizeEffectTreeStuff(std::fstream &oOut) {
  oOut << "<trees>"
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
       << "<tr_stdMaxCrownRad>"
       << "<tr_smcrVal species=\"Species_1\">10</tr_smcrVal>"
       << "<tr_smcrVal species=\"Species_2\">10</tr_smcrVal>"
       << "<tr_smcrVal species=\"Species_3\">10</tr_smcrVal>"
       << "<tr_smcrVal species=\"Species_4\">10</tr_smcrVal>"
       << "</tr_stdMaxCrownRad>"
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
       << "</allometry>";
}

/////////////////////////////////////////////////////////////////////////////
// WriteNCISizeEffectCommonStuff()
/////////////////////////////////////////////////////////////////////////////
void WriteNCISizeEffectCommonStuff(std::fstream &oOut) {
  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>NCIMasterGrowth</behaviorName>"
       << "<version>3</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_3\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_4\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_4\" type=\"Adult\"/>"
       << "</behavior>"
       << "</behaviorList>"
       << "<NCIMasterGrowth1>"
       << "<nciWhichShadingEffect>" << no_shading << "</nciWhichShadingEffect>"
       << "<nciWhichCrowdingEffect>" << no_crowding_effect << "</nciWhichCrowdingEffect>"
       << "<nciWhichNCITerm>" << no_nci_term << "</nciWhichNCITerm>"
       << "<nciWhichSizeEffect>" << size_effect_compound_exp << "</nciWhichSizeEffect>"
       << "<nciWhichDamageEffect>" << no_damage_effect << "</nciWhichDamageEffect>"
       << "<nciWhichPrecipitationEffect>" << no_precip_effect << "</nciWhichPrecipitationEffect>"
       << "<nciWhichTemperatureEffect>" << no_temp_effect << "</nciWhichTemperatureEffect>"
       << "<nciWhichNitrogenEffect>" << no_nitrogen_effect << "</nciWhichNitrogenEffect>"
       << "<nciWhichInfectionEffect>" << no_infection_effect << "</nciWhichInfectionEffect>"
       << "<gr_stochGrowthMethod>" << deterministic_pdf << "</gr_stochGrowthMethod>"
       << "<gr_nciMaxPotentialGrowth>"
       << "<gr_nmpgVal species=\"Species_2\">0.2574</gr_nmpgVal>"
       << "<gr_nmpgVal species=\"Species_3\">10</gr_nmpgVal>"
       << "<gr_nmpgVal species=\"Species_4\">5.4</gr_nmpgVal>"
       << "</gr_nciMaxPotentialGrowth>"
       << "<nciSizeEffectA>"
       << "<nseaVal species=\"Species_2\">0.15</nseaVal>"
       << "<nseaVal species=\"Species_3\">0.15</nseaVal>"
       << "<nseaVal species=\"Species_4\">0.15</nseaVal>"
       << "</nciSizeEffectA>"
       << "<nciSizeEffectB>"
       << "<nsebVal species=\"Species_2\">-10</nsebVal>"
       << "<nsebVal species=\"Species_3\">-20</nsebVal>"
       << "<nsebVal species=\"Species_4\">-5</nsebVal>"
       << "</nciSizeEffectB>"
       << "<nciSizeEffectC>"
       << "<nsecVal species=\"Species_2\">-0.1</nsecVal>"
       << "<nsecVal species=\"Species_3\">-0.03</nsecVal>"
       << "<nsecVal species=\"Species_4\">-0.051</nsecVal>"
       << "</nciSizeEffectC>"
       << "<nciSizeEffectD>"
       << "<nsedVal species=\"Species_2\">6</nsedVal>"
       << "<nsedVal species=\"Species_3\">4</nsedVal>"
       << "<nsedVal species=\"Species_4\">5</nsedVal>"
       << "</nciSizeEffectD>"
       << "</NCIMasterGrowth1>"
       << "</paramFile>";

}
