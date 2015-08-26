//---------------------------------------------------------------------------
// TestNCIDoubleLogisticClimateGrowth.cpp
//---------------------------------------------------------------------------
#include "TestNCIDoubleLogisticClimateGrowth.h"
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
TEST(NCIDoubleLogisticClimateGrowth, TestRun1) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    clTreePopulation * p_oPop;
    clTree *p_oTargetTree1, *p_oTargetTree2, *p_oTargetTree3, *p_oTargetTree4,
    *p_oTargetTree5, *p_oTargetTree6, *p_oTargetTree7, *p_oTargetTree8,
    *p_oTargetTree9, *p_oTargetTree;
    float fDiam, fExpectedDiam;
    int iSpecies;

    //Load our test file and get our tree population pointers
    p_oSimManager->ReadFile(WriteNCIDoubleLogisticClimateGrowthXMLFile1());
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

    //Now create all the neighbors that are too small to compete
    p_oPop->CreateTree(56, 56, 0, clTreePopulation::snag, 30);
    p_oPop->CreateTree(56, 56, 0, clTreePopulation::seedling, 0.2);

    //Now do the run
    p_oSimManager->RunSim(1);

    //Check the diameters and growth of the target trees
    fExpectedDiam = 11.0630943;
    p_oTargetTree = p_oTargetTree1;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);

    fExpectedDiam = 10.50905202;
    p_oTargetTree = p_oTargetTree2;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);

    fExpectedDiam = 17.11183279;
    p_oTargetTree = p_oTargetTree3;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);

    fExpectedDiam = 25.49413651;
    p_oTargetTree = p_oTargetTree4;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);

    fExpectedDiam = 30.06519225;
    p_oTargetTree = p_oTargetTree5;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);

    fExpectedDiam = 46.28318837;
    p_oTargetTree = p_oTargetTree6;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);

    fExpectedDiam = 15.31022653;
    p_oTargetTree = p_oTargetTree7;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);

    fExpectedDiam = 4.000017288;
    p_oTargetTree = p_oTargetTree8;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);

    fExpectedDiam = 4.663861902;
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
TEST(NCIDoubleLogisticClimateGrowth, TestRun2) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    clTreePopulation * p_oPop;
    clTree *p_oTargetTree1, *p_oTargetTree2, *p_oTargetTree3, *p_oTargetTree4,
    *p_oTargetTree5, *p_oTargetTree6, *p_oTargetTree7, *p_oTargetTree8,
    *p_oTargetTree9, *p_oTargetTree;
    float fDiam, fExpectedDiam;
    int iSpecies;

    //Load our test file and get our tree population pointers
    p_oSimManager->ReadFile(WriteNCIDoubleLogisticClimateGrowthXMLFile2());
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

    //Now create all the neighbors that are too small to compete
    p_oPop->CreateTree(56, 56, 0, clTreePopulation::snag, 30);
    p_oPop->CreateTree(56, 56, 0, clTreePopulation::seedling, 0.2);

    //Now do the run
    p_oSimManager->RunSim(1);

    //Check the diameters and growth of the target trees
    fExpectedDiam = 11.18949601;
    p_oTargetTree = p_oTargetTree1;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);

    fExpectedDiam = 10.52721546;
    p_oTargetTree = p_oTargetTree2;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);

    fExpectedDiam = 21.4041846;
    p_oTargetTree = p_oTargetTree3;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);

    fExpectedDiam = 26.47063636;
    p_oTargetTree = p_oTargetTree4;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);

    fExpectedDiam = 30.19570484;
    p_oTargetTree = p_oTargetTree5;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);

    fExpectedDiam = 48.7306575;
    p_oTargetTree = p_oTargetTree6;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);

    fExpectedDiam = 15.9215426;
    p_oTargetTree = p_oTargetTree7;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);

    fExpectedDiam = 4.000051866;
    p_oTargetTree = p_oTargetTree8;
    p_oTargetTree->GetValue(p_oPop->GetDbhCode(p_oTargetTree->GetSpecies(),
        p_oTargetTree->GetType()), &fDiam);
    EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);

    fExpectedDiam = 6.055029576;
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
// TestRun3()
////////////////////////////////////////////////////////////////////////////
TEST(NCIDoubleLogisticClimateGrowth, TestRun3) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    clTreePopulation * p_oPop;
    clTree *p_oTree;
    float fDiam, fTotalDiam1 = 0, fTotalDiam2 = 0, fExpectedDiam;
    int iSpecies, i;

    //Load our test file and get our tree population pointers
    p_oSimManager->ReadFile(WriteNCIDoubleLogisticClimateGrowthXMLFile3());
    p_oPop = (clTreePopulation *) p_oSimManager->GetPopulationObject(
        "treepopulation");

    //Create our trees
    for (i = 0; i < 1000; i++) {
      fDiam = 11;
      iSpecies = 1;
      p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, fDiam);

      fDiam = 10.5;
      iSpecies = 2;
      p_oPop->CreateTree(50, 50, iSpecies, clTreePopulation::adult, fDiam);
    }

    //Now do the run
    p_oSimManager->RunSim(1);

    //Check the mean diameter of the target trees
    clTreeSearch *p_oTrees = p_oPop->Find("all");
    p_oTree = p_oTrees->NextTree();
    while (p_oTree) {
      p_oTree->GetValue(p_oPop->GetDbhCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fDiam);
      if (1 == p_oTree->GetSpecies()) {
        fTotalDiam1 += fDiam;
      } else {
        fTotalDiam2 += fDiam;
      }

      p_oTree = p_oTrees->NextTree();
    }

    fTotalDiam1 /= 1000.0;
    fTotalDiam2 /= 1000.0;

    fExpectedDiam = 14.14855481;
    EXPECT_LT(fabs(fTotalDiam1 - fExpectedDiam), 0.01);
    fExpectedDiam = 13.6196027;
    EXPECT_LT(fabs(fTotalDiam2 - fExpectedDiam), 0.01);

    delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

////////////////////////////////////////////////////////////////////////////
// TestErrorProcessing()
////////////////////////////////////////////////////////////////////////////
TEST(NCIDoubleLogisticClimateGrowth, TestErrorProcessing) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    p_oSimManager->ReadFile(WriteNCIDoubleLogisticClimateGrowthXMLErrorFile1());
    FAIL() << "TestNCIDoubleLogisticClimateGrowth error processing didn't catch error for WriteNCIDoubleLogisticClimateGrowthXMLErrorFile1.";
  } catch (modelErr& err) {
    if (err.sFunction.compare("clSizeEffectShiftedLognormal::DoSetup") != 0) {
      FAIL() << "TestNCIDoubleLogisticClimateGrowth error processing caught wrong error for WriteNCIDoubleLogisticClimateGrowthXMLErrorFile1.";
    };
  }

  try {
    p_oSimManager->ReadFile(WriteNCIDoubleLogisticClimateGrowthXMLErrorFile2());
    FAIL() << "TestNCIDoubleLogisticClimateGrowth error processing didn't catch error for WriteNCIDoubleLogisticClimateGrowthXMLErrorFile2.";
  } catch (modelErr& err) {
    if (err.sFunction.compare("clSizeEffectShiftedLognormal::DoSetup") != 0) {
      FAIL() << "TestNCIDoubleLogisticClimateGrowth error processing caught wrong error for WriteNCIDoubleLogisticClimateGrowthXMLErrorFile2.";
    };
  }

  delete p_oSimManager;
}

////////////////////////////////////////////////////////////////////////////
// WriteNCIDoubleLogisticClimateGrowthXMLFile1()
////////////////////////////////////////////////////////////////////////////
const char* WriteNCIDoubleLogisticClimateGrowthXMLFile1() {
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

  WriteNCIDoubleLogisticClimateGrowthTreeStuff(oOut);
  WriteNCIDoubleLogisticClimateGrowthCommonStuff(oOut);

  oOut.close();

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteNCIDoubleLogisticClimateGrowthXMLFile2()
////////////////////////////////////////////////////////////////////////////
const char* WriteNCIDoubleLogisticClimateGrowthXMLFile2() {
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

  WriteNCIDoubleLogisticClimateGrowthTreeStuff(oOut);
  WriteNCIDoubleLogisticClimateGrowthCommonStuff(oOut);

  oOut.close();

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteNCIDoubleLogisticClimateGrowthXMLFile3()
////////////////////////////////////////////////////////////////////////////
const char* WriteNCIDoubleLogisticClimateGrowthXMLFile3() {
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
       << "<randomSeed>2</randomSeed>"
       << "<plot_lenX>200.0</plot_lenX>"
       << "<plot_lenY>200.0</plot_lenY>"
       << "<plot_latitude>55.37</plot_latitude>"
       << "<plot_precip_mm_yr>10.68</plot_precip_mm_yr>"
       << "<plot_temp_C>12.88171785</plot_temp_C>"
       << "<plot_n_dep>4.76</plot_n_dep>"
       << "<plot_seasonal_precipitation>1150.645781</plot_seasonal_precipitation>"
       << "<plot_water_deficit>6457</plot_water_deficit>"
       << "</plot>";

  WriteNCIDoubleLogisticClimateGrowthTreeStuff(oOut);

  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>NCIMasterGrowth</behaviorName>"
       << "<version>3</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_3\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "</behavior>"
       << "</behaviorList>"
       << "<NCIMasterGrowth1>"
       << "<nciWhichShadingEffect>" << no_shading << "</nciWhichShadingEffect>"
       << "<nciWhichCrowdingEffect>" << no_crowding_effect << "</nciWhichCrowdingEffect>"
       << "<nciWhichNCITerm>" << no_nci_term << "</nciWhichNCITerm>"
       << "<nciWhichSizeEffect>" << size_effect_shifted_lognormal << "</nciWhichSizeEffect>"
       << "<nciWhichDamageEffect>" << no_damage_effect << "</nciWhichDamageEffect>"
       << "<nciWhichPrecipitationEffect>" << no_precip_effect << "</nciWhichPrecipitationEffect>"
       << "<nciWhichTemperatureEffect>" << no_temp_effect << "</nciWhichTemperatureEffect>"
       << "<nciWhichNitrogenEffect>" << gauss_nitrogen_effect << "</nciWhichNitrogenEffect>"
       << "<nciWhichInfectionEffect>" << no_infection_effect << "</nciWhichInfectionEffect>"
       << "<gr_stochGrowthMethod>" << normal_pdf << "</gr_stochGrowthMethod>"
       << "<gr_standardDeviation>"
       << "<gr_sdVal species=\"Species_2\">0.2</gr_sdVal>"
       << "<gr_sdVal species=\"Species_3\">0.2</gr_sdVal>"
       << "</gr_standardDeviation>"
       << "<gr_nciMaxPotentialGrowth>"
       << "<gr_nmpgVal species=\"Species_2\">5</gr_nmpgVal>"
       << "<gr_nmpgVal species=\"Species_3\">5</gr_nmpgVal>"
       << "</gr_nciMaxPotentialGrowth>"
       << "<nciSizeEffectX0>"
       << "<nsex0Val species=\"Species_2\">297.615</nsex0Val>"
       << "<nsex0Val species=\"Species_3\">297.615</nsex0Val>"
       << "</nciSizeEffectX0>"
       << "<nciSizeEffectXb>"
       << "<nsexbVal species=\"Species_2\">4.065</nsexbVal>"
       << "<nsexbVal species=\"Species_3\">4.065</nsexbVal>"
       << "</nciSizeEffectXb>"
       << "<nciSizeEffectXp>"
       << "<nsexpVal species=\"Species_2\">0.1</nsexpVal>"
       << "<nsexpVal species=\"Species_3\">0.1</nsexpVal>"
       << "</nciSizeEffectXp>"
       << "<nciSizeEffectLowerBound>"
       << "<nselbVal species=\"Species_2\">0</nselbVal>"
       << "<nselbVal species=\"Species_3\">0</nselbVal>"
       << "</nciSizeEffectLowerBound>"
       << "<nciNitrogenX0>"
       << "<nnx0Val species=\"Species_2\">4.5</nnx0Val>"
       << "<nnx0Val species=\"Species_3\">4.5</nnx0Val>"
       << "</nciNitrogenX0>"
       << "<nciNitrogenXb>"
       << "<nnxbVal species=\"Species_2\">0.5</nnxbVal>"
       << "<nnxbVal species=\"Species_3\">0.5</nnxbVal>"
       << "</nciNitrogenXb>"
       << "</NCIMasterGrowth1>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteNCIDoubleLogisticClimateGrowthTreeStuff()
/////////////////////////////////////////////////////////////////////////////
void WriteNCIDoubleLogisticClimateGrowthTreeStuff(std::fstream &oOut) {
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
// WriteNCIDoubleLogisticClimateGrowthCommonStuff()
/////////////////////////////////////////////////////////////////////////////
void WriteNCIDoubleLogisticClimateGrowthCommonStuff(std::fstream &oOut) {
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
       << "<nciWhichCrowdingEffect>" << default_crowding_effect << "</nciWhichCrowdingEffect>"
       << "<nciWhichNCITerm>" << larger_neighbors << "</nciWhichNCITerm>"
       << "<nciWhichSizeEffect>" << size_effect_shifted_lognormal << "</nciWhichSizeEffect>"
       << "<nciWhichDamageEffect>" << no_damage_effect << "</nciWhichDamageEffect>"
       << "<nciWhichPrecipitationEffect>" << double_logistic_precip_effect << "</nciWhichPrecipitationEffect>"
       << "<nciWhichTemperatureEffect>" << double_logistic_temp_effect << "</nciWhichTemperatureEffect>"
       << "<nciWhichNitrogenEffect>" << gauss_nitrogen_effect << "</nciWhichNitrogenEffect>"
       << "<nciWhichInfectionEffect>" << no_infection_effect << "</nciWhichInfectionEffect>"
       << "<gr_stochGrowthMethod>" << deterministic_pdf << "</gr_stochGrowthMethod>"
       << "<gr_nciMaxPotentialGrowth>"
       << "<gr_nmpgVal species=\"Species_2\">0.2574</gr_nmpgVal>"
       << "<gr_nmpgVal species=\"Species_3\">10</gr_nmpgVal>"
       << "<gr_nmpgVal species=\"Species_4\">5.4</gr_nmpgVal>"
       << "</gr_nciMaxPotentialGrowth>"
       << "<nciSizeEffectX0>"
       << "<nsex0Val species=\"Species_2\">297.615</nsex0Val>"
       << "<nsex0Val species=\"Species_3\">18.07</nsex0Val>"
       << "<nsex0Val species=\"Species_4\">132.1</nsex0Val>"
       << "</nciSizeEffectX0>"
       << "<nciSizeEffectXb>"
       << "<nsexbVal species=\"Species_2\">4.065</nsexbVal>"
       << "<nsexbVal species=\"Species_3\">0.902</nsexbVal>"
       << "<nsexbVal species=\"Species_4\">2.568</nsexbVal>"
       << "</nciSizeEffectXb>"
       << "<nciSizeEffectXp>"
       << "<nsexpVal species=\"Species_2\">0.1</nsexpVal>"
       << "<nsexpVal species=\"Species_3\">0.2</nsexpVal>"
       << "<nsexpVal species=\"Species_4\">0.3</nsexpVal>"
       << "</nciSizeEffectXp>"
       << "<nciSizeEffectLowerBound>"
       << "<nselbVal species=\"Species_2\">0</nselbVal>"
       << "<nselbVal species=\"Species_3\">5</nselbVal>"
       << "<nselbVal species=\"Species_4\">0</nselbVal>"
       << "</nciSizeEffectLowerBound>"
       << "<nciMaxCrowdingRadius>"
       << "<nmcrVal species=\"Species_2\">10</nmcrVal>"
       << "<nmcrVal species=\"Species_3\">11</nmcrVal>"
       << "<nmcrVal species=\"Species_4\">12</nmcrVal>"
       << "</nciMaxCrowdingRadius>"
       << "<nciCrowdingC>"
       << "<nccVal species=\"Species_2\">8.261</nccVal>"
       << "<nccVal species=\"Species_3\">0</nccVal>"
       << "<nccVal species=\"Species_4\">0.321</nccVal>"
       << "</nciCrowdingC>"
       << "<nciCrowdingD>"
       << "<ncdVal species=\"Species_2\">1.001</ncdVal>"
       << "<ncdVal species=\"Species_3\">2.914</ncdVal>"
       << "<ncdVal species=\"Species_4\">0.4</ncdVal>"
       << "</nciCrowdingD>"
       << "<nciCrowdingGamma>"
       << "<ncgVal species=\"Species_2\">-1.208</ncgVal>"
       << "<ncgVal species=\"Species_3\">1.976</ncgVal>"
       << "<ncgVal species=\"Species_4\">0.461</ncgVal>"
       << "</nciCrowdingGamma>"
       << "<nciDoubLogPrecipEffAl>"
       << "<ndlpealVal species=\"Species_2\">0.35</ndlpealVal>"
       << "<ndlpealVal species=\"Species_3\">0.4</ndlpealVal>"
       << "<ndlpealVal species=\"Species_4\">0.8</ndlpealVal>"
       << "</nciDoubLogPrecipEffAl>"
       << "<nciDoubLogPrecipEffBl>"
       << "<ndlpeblVal species=\"Species_2\">700</ndlpeblVal>"
       << "<ndlpeblVal species=\"Species_3\">600</ndlpeblVal>"
       << "<ndlpeblVal species=\"Species_4\">600</ndlpeblVal>"
       << "</nciDoubLogPrecipEffBl>"
       << "<nciDoubLogPrecipEffCl>"
       << "<ndlpeclVal species=\"Species_2\">4</ndlpeclVal>"
       << "<ndlpeclVal species=\"Species_3\">3</ndlpeclVal>"
       << "<ndlpeclVal species=\"Species_4\">6</ndlpeclVal>"
       << "</nciDoubLogPrecipEffCl>"
       << "<nciDoubLogPrecipEffAh>"
       << "<ndlpeahVal species=\"Species_2\">0.6</ndlpeahVal>"
       << "<ndlpeahVal species=\"Species_3\">0.66</ndlpeahVal>"
       << "<ndlpeahVal species=\"Species_4\">0.9</ndlpeahVal>"
       << "</nciDoubLogPrecipEffAh>"
       << "<nciDoubLogPrecipEffBh>"
       << "<ndlpebhVal species=\"Species_2\">475</ndlpebhVal>"
       << "<ndlpebhVal species=\"Species_3\">542</ndlpebhVal>"
       << "<ndlpebhVal species=\"Species_4\">1200</ndlpebhVal>"
       << "</nciDoubLogPrecipEffBh>"
       << "<nciDoubLogPrecipEffCh>"
       << "<ndlpechVal species=\"Species_2\">7</ndlpechVal>"
       << "<ndlpechVal species=\"Species_3\">0.2</ndlpechVal>"
       << "<ndlpechVal species=\"Species_4\">3</ndlpechVal>"
       << "</nciDoubLogPrecipEffCh>"
       << "<nciDoubleLogisticPrecipType>" << clPrecipitationEffectBase::seasonal_precip << "</nciDoubleLogisticPrecipType>"
       << "<nciDoubLogTempEffAl>"
       << "<ndltealVal species=\"Species_2\">0.8</ndltealVal>"
       << "<ndltealVal species=\"Species_3\">0.89</ndltealVal>"
       << "<ndltealVal species=\"Species_4\">0.3</ndltealVal>"
       << "</nciDoubLogTempEffAl>"
       << "<nciDoubLogTempEffBl>"
       << "<ndlteblVal species=\"Species_2\">286.85</ndlteblVal>"
       << "<ndlteblVal species=\"Species_3\">290</ndlteblVal>"
       << "<ndlteblVal species=\"Species_4\">273</ndlteblVal>"
       << "</nciDoubLogTempEffBl>"
       << "<nciDoubLogTempEffCl>"
       << "<ndlteclVal species=\"Species_2\">3</ndlteclVal>"
       << "<ndlteclVal species=\"Species_3\">1</ndlteclVal>"
       << "<ndlteclVal species=\"Species_4\">25</ndlteclVal>"
       << "</nciDoubLogTempEffCl>"
       << "<nciDoubLogTempEffAh>"
       << "<ndlteahVal species=\"Species_2\">0.5</ndlteahVal>"
       << "<ndlteahVal species=\"Species_3\">0.4</ndlteahVal>"
       << "<ndlteahVal species=\"Species_4\">0.2</ndlteahVal>"
       << "</nciDoubLogTempEffAh>"
       << "<nciDoubLogTempEffBh>"
       << "<ndltebhVal species=\"Species_2\">300.85</ndltebhVal>"
       << "<ndltebhVal species=\"Species_3\">310</ndltebhVal>"
       << "<ndltebhVal species=\"Species_4\">315</ndltebhVal>"
       << "</nciDoubLogTempEffBh>"
       << "<nciDoubLogTempEffCh>"
       << "<ndltechVal species=\"Species_2\">5</ndltechVal>"
       << "<ndltechVal species=\"Species_3\">6</ndltechVal>"
       << "<ndltechVal species=\"Species_4\">0.01</ndltechVal>"
       << "</nciDoubLogTempEffCh>"
       << "<nciNitrogenX0>"
       << "<nnx0Val species=\"Species_2\">4.5</nnx0Val>"
       << "<nnx0Val species=\"Species_3\">3.8</nnx0Val>"
       << "<nnx0Val species=\"Species_4\">6.3</nnx0Val>"
       << "</nciNitrogenX0>"
       << "<nciNitrogenXb>"
       << "<nnxbVal species=\"Species_2\">0.5</nnxbVal>"
       << "<nnxbVal species=\"Species_3\">0.7</nnxbVal>"
       << "<nnxbVal species=\"Species_4\">7</nnxbVal>"
       << "</nciNitrogenXb>"
       << "<nciMinNeighborDBH>"
       << "<nmndVal species=\"Species_1\">5</nmndVal>"
       << "<nmndVal species=\"Species_2\">5</nmndVal>"
       << "<nmndVal species=\"Species_3\">5</nmndVal>"
       << "<nmndVal species=\"Species_4\">5</nmndVal>"
       << "</nciMinNeighborDBH>"
       << "</NCIMasterGrowth1>"
       << "</paramFile>";

}

/////////////////////////////////////////////////////////////////////////////
// WriteNCIDoubleLogisticClimateGrowthErrorFileCommonStuff()
/////////////////////////////////////////////////////////////////////////////
void WriteNCIDoubleLogisticClimateGrowthErrorFileCommonStuff(std::fstream &oOut) {
  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06010101\">"
       << "<plot>"
       << "<timesteps>1</timesteps>"
       << "<yearsPerTimestep>1</yearsPerTimestep>"
       << "<randomSeed>1</randomSeed>"
       << "<plot_lenX>200.0</plot_lenX>"
       << "<plot_lenY>200.0</plot_lenY>"
       << "<plot_latitude>55.37</plot_latitude>"
       << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
       << "<plot_temp_C>12.88171785</plot_temp_C>"
       << "</plot>"
       << "<trees>"
       << "<tr_speciesList>"
       << "<tr_species speciesName=\"Species_1\" />"
       << "<tr_species speciesName=\"Species_2\" />"
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
       << "<behaviorName>NCIMasterGrowth</behaviorName>"
       << "<version>3</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "</behavior>"
       << "</behaviorList>"
       << "<NCIMasterGrowth1>"
       << "<nciWhichShadingEffect>" << no_shading << "</nciWhichShadingEffect>"
       << "<nciWhichCrowdingEffect>" << no_crowding_effect << "</nciWhichCrowdingEffect>"
       << "<nciWhichNCITerm>" << no_nci_term << "</nciWhichNCITerm>"
       << "<nciWhichSizeEffect>" << size_effect_shifted_lognormal << "</nciWhichSizeEffect>"
       << "<nciWhichDamageEffect>" << no_damage_effect << "</nciWhichDamageEffect>"
       << "<nciWhichPrecipitationEffect>" << no_precip_effect << "</nciWhichPrecipitationEffect>"
       << "<nciWhichTemperatureEffect>" << no_temp_effect << "</nciWhichTemperatureEffect>"
       << "<nciWhichNitrogenEffect>" << no_nitrogen_effect << "</nciWhichNitrogenEffect>"
       << "<nciWhichInfectionEffect>" << no_infection_effect << "</nciWhichInfectionEffect>"
       << "<gr_stochGrowthMethod>" << deterministic_pdf << "</gr_stochGrowthMethod>"
       << "<nciMaxCrowdingRadius>"
       << "<nmcrVal species=\"Species_1\">10</nmcrVal>"
       << "<nmcrVal species=\"Species_2\">11</nmcrVal>"
       << "</nciMaxCrowdingRadius>"
       << "<gr_nciMaxPotentialGrowth>"
       << "<gr_nmpgVal species=\"Species_1\">0.2574</gr_nmpgVal>"
       << "<gr_nmpgVal species=\"Species_2\">10</gr_nmpgVal>"
       << "</gr_nciMaxPotentialGrowth>"
       << "<nciSizeEffectXp>"
       << "<nsexpVal species=\"Species_1\">0.1</nsexpVal>"
       << "<nsexpVal species=\"Species_2\">0.2</nsexpVal>"
       << "</nciSizeEffectXp>"
       << "<nciSizeEffectLowerBound>"
       << "<nselbVal species=\"Species_1\">0</nselbVal>"
       << "<nselbVal species=\"Species_2\">5</nselbVal>"
       << "</nciSizeEffectLowerBound>";
}

////////////////////////////////////////////////////////////////////////////
// WriteNCIDoubleLogisticClimateGrowthXMLErrorFile1()
////////////////////////////////////////////////////////////////////////////
const char* WriteNCIDoubleLogisticClimateGrowthXMLErrorFile1() {
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  WriteNCIDoubleLogisticClimateGrowthErrorFileCommonStuff(oOut);

  //Write file
  oOut << "<nciSizeEffectX0>"
       << "<nsex0Val species=\"Species_1\">297.615</nsex0Val>"
       << "<nsex0Val species=\"Species_2\">18.07</nsex0Val>"
       << "</nciSizeEffectX0>"
       << "<nciSizeEffectXb>"
       << "<nsexbVal species=\"Species_1\">0</nsexbVal>"
       << "<nsexbVal species=\"Species_2\">0.902</nsexbVal>"
       << "</nciSizeEffectXb>"
       << "</NCIMasterGrowth1>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteNCIDoubleLogisticClimateGrowthXMLErrorFile2()
////////////////////////////////////////////////////////////////////////////
const char* WriteNCIDoubleLogisticClimateGrowthXMLErrorFile2() {
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  WriteNCIDoubleLogisticClimateGrowthErrorFileCommonStuff(oOut);

  //Write file
  oOut << "<nciSizeEffectX0>"
       << "<nsex0Val species=\"Species_1\">297.615</nsex0Val>"
       << "<nsex0Val species=\"Species_2\">0</nsex0Val>"
       << "</nciSizeEffectX0>"
       << "<nciSizeEffectXb>"
       << "<nsexbVal species=\"Species_1\">4.065</nsexbVal>"
       << "<nsexbVal species=\"Species_2\">0.902</nsexbVal>"
       << "</nciSizeEffectXb>"
       << "</NCIMasterGrowth1>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}
