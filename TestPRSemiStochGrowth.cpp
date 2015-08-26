//---------------------------------------------------------------------------
// TestPRSemiStochGrowth.cpp
//---------------------------------------------------------------------------
#include "TestPRSemiStochGrowth.h"
#include <gtest/gtest.h>
#include <fstream>
#include <math.h>
#include "TreePopulation.h"
#include "SimManager.h"

////////////////////////////////////////////////////////////////////////////
// NormalProcessingRun1()
// Tests normal processing run 1. WriteXMLFile1() does setup. Timestep
// length is 1 year. 8 trees are created of 2 species. Then growth is run.
// Their diameters and heights are checked to make sure they are correct.
////////////////////////////////////////////////////////////////////////////
TEST(PRSemiStochGrowth, NormalProcessingRun1) {

  clTreePopulation * p_oPop;
  clTree **p_oTrees = new clTree*[8];
  float fDiam, fHeight, fExpectedDiam, fExpectedHeight;
  int iIndex, iSpecies, iType;
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {

    //Load our test file and get our tree population
    p_oSimManager->ReadFile( WritePRSemiStochGrowthXMLFile1() );
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );

    //Create our trees, verifying starting heights
    iIndex = 0;

    fDiam = 0.1;
    fExpectedHeight = 0.09629;
    iSpecies = 1;
    iType = clTreePopulation::seedling;
    p_oTrees[iIndex] = p_oPop->CreateTree(1, 1, iSpecies, iType, fDiam);
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(iSpecies, iType), &fHeight);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fDiam = 0.3;
    fExpectedHeight = 0.26991;
    iSpecies = 2;
    iType = clTreePopulation::seedling;
    p_oTrees[iIndex] = p_oPop->CreateTree(1, 1, iSpecies, iType, fDiam);
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(iSpecies, iType), &fHeight);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fDiam = 0.5;
    fExpectedHeight = 0.48145;
    iSpecies = 1;
    iType = clTreePopulation::seedling;
    p_oTrees[iIndex] = p_oPop->CreateTree(1, 1, iSpecies, iType, fDiam);
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(iSpecies, iType), &fHeight);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fDiam = 0.7;
    fExpectedHeight = 0.62979;
    iSpecies = 2;
    iType = clTreePopulation::seedling;
    p_oTrees[iIndex] = p_oPop->CreateTree(1, 1, iSpecies, iType, fDiam);
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(iSpecies, iType), &fHeight);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fDiam = 1.3;
    fExpectedHeight = 1.25177;
    iSpecies = 1;
    iType = clTreePopulation::seedling;
    p_oTrees[iIndex] = p_oPop->CreateTree(1, 1, iSpecies, iType, fDiam);
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(iSpecies, iType), &fHeight);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fDiam = 2.2;
    fExpectedHeight = 1.97934;
    iSpecies = 2;
    iType = clTreePopulation::seedling;
    p_oTrees[iIndex] = p_oPop->CreateTree(1, 1, iSpecies, iType, fDiam);
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(iSpecies, iType), &fHeight);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fDiam = 15;
    fExpectedHeight = 15.13074207;
    iSpecies = 1;
    iType = clTreePopulation::adult;
    p_oTrees[iIndex] = p_oPop->CreateTree(1, 1, iSpecies, iType, fDiam);
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(iSpecies, iType), &fHeight);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    fDiam = 15;
    fExpectedHeight = 12.93567754;
    iSpecies = 2;
    iType = clTreePopulation::adult;
    p_oTrees[iIndex] = p_oPop->CreateTree(1, 1, iSpecies, iType, fDiam);
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(iSpecies, iType), &fHeight);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    iIndex++;

    //Now run
    p_oSimManager->RunSim(1);

    //Confirm all trees
    iIndex = 0;
    fExpectedDiam = 2.20027873;
    fExpectedHeight = 0.159061445;
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    p_oTrees[iIndex]->GetValue(p_oPop->GetDiam10Code(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fDiam);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    iIndex++;

    fExpectedDiam = 5.129761185;
    fExpectedHeight = 0.31095593;
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    p_oTrees[iIndex]->GetValue(p_oPop->GetDiam10Code(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fDiam);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    iIndex++;

    fExpectedDiam = 2.803325544;
    fExpectedHeight = 0.562765377;
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    p_oTrees[iIndex]->GetValue(p_oPop->GetDiam10Code(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fDiam);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    iIndex++;

    fExpectedDiam = 7.017817577;
    fExpectedHeight = 0.702697403;
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    p_oTrees[iIndex]->GetValue(p_oPop->GetDiam10Code(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fDiam);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    iIndex++;

    fExpectedDiam = 30;
    fExpectedHeight = 1.342056389;
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    p_oTrees[iIndex]->GetValue(p_oPop->GetDiam10Code(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fDiam);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedDiam - fDiam)/fDiam, 0.2);
    iIndex++;

    fExpectedDiam = 35;
    fExpectedHeight = 2.108468147;
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    p_oTrees[iIndex]->GetValue(p_oPop->GetDiam10Code(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fDiam);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedDiam - fDiam)/fDiam, 0.2);
    iIndex++;

    fExpectedDiam = 30;
    fExpectedHeight = 15.23063465;
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    p_oTrees[iIndex]->GetValue(p_oPop->GetDbhCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fDiam);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedDiam - fDiam)/fDiam, 0.2);
    iIndex++;

    fExpectedDiam = 35;
    fExpectedHeight = 13.13372731;
    p_oTrees[iIndex]->GetValue(p_oPop->GetHeightCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fHeight);
    p_oTrees[iIndex]->GetValue(p_oPop->GetDbhCode(p_oTrees[iIndex]->GetSpecies(), p_oTrees[iIndex]->GetType()), &fDiam);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedDiam - fDiam)/fDiam, 0.2);
    iIndex++;

    delete[] p_oTrees;
    delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

////////////////////////////////////////////////////////////////////////////
// WritePRSemiStochGrowthXMLFile1()
////////////////////////////////////////////////////////////////////////////
const char* WritePRSemiStochGrowthXMLFile1() {
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
       << "<yearsPerTimestep>1</yearsPerTimestep>";

  oOut << "<randomSeed>1</randomSeed>"
       << "<plot_lenX>100</plot_lenX>"
       << "<plot_lenY>100</plot_lenY>"
       << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
       << "<plot_temp_C>12.88171785</plot_temp_C>"
       << "<plot_latitude>55.37</plot_latitude>"
       << "</plot>"
       << "<trees>"
       << "<tr_speciesList>"
       << "<tr_species speciesName=\"Species_1\"/>"
       << "<tr_species speciesName=\"Species_2\"/>"
       << "<tr_species speciesName=\"Species_3\"/>"
       << "</tr_speciesList>"
       << "<tr_seedDiam10Cm>0.1</tr_seedDiam10Cm>"
       << "<tr_minAdultDBH>"
       << "<tr_madVal species=\"Species_1\">10.0</tr_madVal>"
       << "<tr_madVal species=\"Species_2\">10.0</tr_madVal>"
       << "<tr_madVal species=\"Species_3\">10.0</tr_madVal>"
       << "</tr_minAdultDBH>"
       << "<tr_maxSeedlingHeight>"
       << "<tr_mshVal species=\"Species_1\">2</tr_mshVal>"
       << "<tr_mshVal species=\"Species_2\">2</tr_mshVal>"
       << "<tr_mshVal species=\"Species_3\">2</tr_mshVal>"
       << "</tr_maxSeedlingHeight>"
       << "</trees>"
       << "<allometry>"
       << "<tr_slopeOfAsymHeight>"
       << "<tr_soahVal species=\"Species_2\">0.0299</tr_soahVal>"
       << "<tr_soahVal species=\"Species_3\">0.0241</tr_soahVal>"
       << "<tr_soahVal species=\"Species_1\">0.0241</tr_soahVal>"
       << "</tr_slopeOfAsymHeight>"
       << "<tr_canopyHeight>"
       << "<tr_chVal species=\"Species_1\">46</tr_chVal>"
       << "<tr_chVal species=\"Species_2\">39.48</tr_chVal>"
       << "<tr_chVal species=\"Species_3\">39.54</tr_chVal>"
       << "</tr_canopyHeight>"
       << "<tr_stdAsympCrownRad>"
       << "<tr_sacrVal species=\"Species_1\">0.0549</tr_sacrVal>"
       << "<tr_sacrVal species=\"Species_2\">0.0549</tr_sacrVal>"
       << "<tr_sacrVal species=\"Species_3\">0.0549</tr_sacrVal>"
       << "</tr_stdAsympCrownRad>"
       << "<tr_stdCrownRadExp>"
       << "<tr_screVal species=\"Species_1\">1.0</tr_screVal>"
       << "<tr_screVal species=\"Species_2\">1.0</tr_screVal>"
       << "<tr_screVal species=\"Species_3\">1.0</tr_screVal>"
       << "</tr_stdCrownRadExp>"
       << "<tr_stdMaxCrownRad>"
       << "<tr_smcrVal species=\"Species_1\">10</tr_smcrVal>"
       << "<tr_smcrVal species=\"Species_2\">10</tr_smcrVal>"
       << "<tr_smcrVal species=\"Species_3\">10</tr_smcrVal>"
       << "</tr_stdMaxCrownRad>"
       << "<tr_conversionDiam10ToDBH>"
       << "<tr_cdtdVal species=\"Species_1\">0.8008</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_2\">0.5944</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_3\">0.8008</tr_cdtdVal>"
       << "</tr_conversionDiam10ToDBH>"
       << "<tr_interceptDiam10ToDBH>"
       << "<tr_idtdVal species=\"Species_1\">0</tr_idtdVal>"
       << "<tr_idtdVal species=\"Species_2\">0</tr_idtdVal>"
       << "<tr_idtdVal species=\"Species_3\">0</tr_idtdVal>"
       << "</tr_interceptDiam10ToDBH>"
       << "<tr_stdAsympCrownHt>"
       << "<tr_sachVal species=\"Species_1\">0.389</tr_sachVal>"
       << "<tr_sachVal species=\"Species_2\">0.389</tr_sachVal>"
       << "<tr_sachVal species=\"Species_3\">0.389</tr_sachVal>"
       << "</tr_stdAsympCrownHt>"
       << "<tr_stdCrownHtExp>"
       << "<tr_scheVal species=\"Species_1\">1.0</tr_scheVal>"
       << "<tr_scheVal species=\"Species_2\">1.0</tr_scheVal>"
       << "<tr_scheVal species=\"Species_3\">1.0</tr_scheVal>"
       << "</tr_stdCrownHtExp>"
       << "<tr_whatSeedlingHeightDiam>"
       << "<tr_wsehdVal species=\"Species_1\">1</tr_wsehdVal>"
       << "<tr_wsehdVal species=\"Species_2\">1</tr_wsehdVal>"
       << "<tr_wsehdVal species=\"Species_3\">1</tr_wsehdVal>"
       << "</tr_whatSeedlingHeightDiam>"
       << "<tr_whatSaplingHeightDiam>"
       << "<tr_wsahdVal species=\"Species_1\">1</tr_wsahdVal>"
       << "<tr_wsahdVal species=\"Species_2\">1</tr_wsahdVal>"
       << "<tr_wsahdVal species=\"Species_3\">1</tr_wsahdVal>"
       << "</tr_whatSaplingHeightDiam>"
       << "<tr_whatAdultHeightDiam>"
       << "<tr_wahdVal species=\"Species_1\">0</tr_wahdVal>"
       << "<tr_wahdVal species=\"Species_2\">0</tr_wahdVal>"
       << "<tr_wahdVal species=\"Species_3\">0</tr_wahdVal>"
       << "</tr_whatAdultHeightDiam>"
       << "<tr_seedlingLinearSlope>"
       << "<tr_selsVal species=\"Species_2\">0.9629</tr_selsVal>"
       << "<tr_selsVal species=\"Species_3\">0.8997</tr_selsVal>"
       << "<tr_selsVal species=\"Species_1\">0.8997</tr_selsVal>"
       << "</tr_seedlingLinearSlope>"
       << "<tr_seedlingLinearIntercept>"
       << "<tr_seliVal species=\"Species_1\">0</tr_seliVal>"
       << "<tr_seliVal species=\"Species_2\">0</tr_seliVal>"
       << "<tr_seliVal species=\"Species_3\">0</tr_seliVal>"
       << "</tr_seedlingLinearIntercept>"
       << "<tr_saplingLinearSlope>"
       << "<tr_salsVal species=\"Species_2\">0.9629</tr_salsVal>"
       << "<tr_salsVal species=\"Species_3\">0.8997</tr_salsVal>"
       << "<tr_salsVal species=\"Species_1\">0.8997</tr_salsVal>"
       << "</tr_saplingLinearSlope>"
       << "<tr_saplingLinearIntercept>"
       << "<tr_saliVal species=\"Species_1\">0</tr_saliVal>"
       << "<tr_saliVal species=\"Species_2\">0</tr_saliVal>"
       << "<tr_saliVal species=\"Species_3\">0</tr_saliVal>"
       << "</tr_saplingLinearIntercept>"
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
       << "</allometry>";

  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>PRSemiStochastic diam only</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_2\" type=\"Seedling\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_3\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_3\" type=\"Seedling\"/>"
       << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>LogBilevelGrowth height only</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>2</listPosition>"
       << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_2\" type=\"Seedling\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_3\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_3\" type=\"Seedling\"/>"
       << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
       << "</behavior>"
       << "</behaviorList>";

  oOut << "<LogBilevelGrowth2>"
       << "<gr_lognormalBilevLoLiteX0>"
       << "<gr_lbllx0Val species=\"Species_2\">12</gr_lbllx0Val>"
       << "<gr_lbllx0Val species=\"Species_3\">18</gr_lbllx0Val>"
       << "</gr_lognormalBilevLoLiteX0>"
       << "<gr_lognormalBilevLoLiteXb>"
       << "<gr_lbllxbVal species=\"Species_2\">5</gr_lbllxbVal>"
       << "<gr_lbllxbVal species=\"Species_3\">2.36</gr_lbllxbVal>"
       << "</gr_lognormalBilevLoLiteXb>"
       << "<gr_lognormalBilevLoLiteMaxGrowth>"
       << "<gr_lbllmgVal species=\"Species_2\">0.1</gr_lbllmgVal>"
       << "<gr_lbllmgVal species=\"Species_3\">0.2</gr_lbllmgVal>"
       << "</gr_lognormalBilevLoLiteMaxGrowth>"
       << "</LogBilevelGrowth2>"
       << "<PRSemiStochastic1>"
       << "<gr_prStochHiteThreshold>"
       << "<gr_pshtVal species=\"Species_2\">1.3</gr_pshtVal>"
       << "<gr_pshtVal species=\"Species_3\">2.1</gr_pshtVal>"
       << "</gr_prStochHiteThreshold>"
       << "<gr_prStochDetermA>"
       << "<gr_psdaVal species=\"Species_2\">2</gr_psdaVal>"
       << "<gr_psdaVal species=\"Species_3\">4</gr_psdaVal>"
       << "</gr_prStochDetermA>"
       << "<gr_prStochDetermB>"
       << "<gr_psdbVal species=\"Species_2\">-0.006</gr_psdbVal>"
       << "<gr_psdbVal species=\"Species_3\">-0.008</gr_psdbVal>"
       << "</gr_prStochDetermB>"
       << "<gr_prStochMeanDBH>"
       << "<gr_psmdVal species=\"Species_2\">30</gr_psmdVal>"
       << "<gr_psmdVal species=\"Species_3\">35</gr_psmdVal>"
       << "</gr_prStochMeanDBH>"
       << "<gr_prStochStdDev>"
       << "<gr_pssdVal species=\"Species_2\">0.1</gr_pssdVal>"
       << "<gr_pssdVal species=\"Species_3\">0.2</gr_pssdVal>"
       << "</gr_prStochStdDev>"
       << "</PRSemiStochastic1>"
       << "</paramFile>";

  oOut.close();

  return cFileString;

}
