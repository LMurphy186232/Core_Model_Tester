//---------------------------------------------------------------------------

#include "TestGrowthOrg.h"
#include <gtest/gtest.h>
#include <fstream>
#include <math.h>
#include "TreePopulation.h"
#include "SimManager.h"

////////////////////////////////////////////////////////////////////////////
// TestNormalProcessingRun1()
// Tests normal processing. WriteGrowthOrgXMLFile1() is used to create the file
// for this run. Then six trees are added - a seedling, sapling, and species of
// each of Species 1 and Species 2. Both the diameter and height of each
// tree are set to known values. Then growth is run. The diameter and height
// for each tree are checked against expected values.
////////////////////////////////////////////////////////////////////////////
TEST(GrowthOrg, TestNormalProcessingRun1) {

  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    clTreePopulation * p_oPop;
    clTree *p_oTree1, *p_oTree2, *p_oTree3, *p_oTree4, *p_oTree5, *p_oTree6,
    *p_oTree7;
    float fDiam, fHeight, fExpectedDiam, fExpectedHeight, fGrowth, fExpectedGrowth;

    //Load our test file and get our tree population pointers
    p_oSimManager->ReadFile( WriteGrowthOrgXMLFile1() );
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );

    //Create our six trees and set diameter and height for each
    //Seedling, Species 1
    fDiam = 0.3;
    fHeight = 0.8;
    p_oTree1 = p_oPop->CreateTree(1, 1, 0, clTreePopulation::seedling, fDiam);
    p_oTree1->SetValue(p_oPop->GetHeightCode(p_oTree1->GetSpecies(), p_oTree1->GetType()), fHeight, false, false);

    //Sapling, Species 1
    fDiam = 5.52552;
    fHeight = 4;
    p_oTree2 = p_oPop->CreateTree(2, 2, 0, clTreePopulation::sapling, fDiam);
    p_oTree2->SetValue(p_oPop->GetHeightCode(p_oTree2->GetSpecies(), p_oTree2->GetType()), fHeight, false, false);

    //Adult, Species 1
    fDiam = 25;
    fHeight = 12;
    p_oTree3 = p_oPop->CreateTree(3, 3, 0, clTreePopulation::adult, fDiam);
    p_oTree3->SetValue(p_oPop->GetHeightCode(p_oTree3->GetSpecies(), p_oTree3->GetType()), fHeight, false, false);

    //Seedling, Species 2
    fDiam = 1.2;
    fHeight = 1;
    p_oTree4 = p_oPop->CreateTree(4, 4, 1, clTreePopulation::seedling, fDiam);
    p_oTree4->SetValue(p_oPop->GetHeightCode(p_oTree4->GetSpecies(), p_oTree4->GetType()), fHeight, false, false);

    //Sapling, Species 2
    fDiam = 2.91256;
    fHeight = 5;
    p_oTree5 = p_oPop->CreateTree(5, 5, 1, clTreePopulation::sapling, fDiam);
    p_oTree5->SetValue(p_oPop->GetHeightCode(p_oTree5->GetSpecies(), p_oTree5->GetType()), fHeight, false, false);

    //Adult, Species 2
    fDiam = 17.8;
    fHeight = 14;
    p_oTree6 = p_oPop->CreateTree(6, 6, 1, clTreePopulation::adult, fDiam);
    p_oTree6->SetValue(p_oPop->GetHeightCode(p_oTree6->GetSpecies(), p_oTree6->GetType()), fHeight, false, false);

    //Dead tree
    fDiam = 10;
    p_oTree7 = p_oPop->CreateTree(7, 7, 1, clTreePopulation::adult, fDiam);
    p_oTree7->SetValue(p_oPop->GetIntDataCode("dead", p_oTree7->GetSpecies(), p_oTree7->GetType()), natural);

    //Run our timestep
    p_oSimManager->RunSim(1);

    //Check our results for each tree

    //Seedling, Species 1
    fExpectedDiam = 1;
    fExpectedHeight = 1.108073877;
    fExpectedGrowth = 3.5;
    p_oTree1->GetValue(p_oPop->GetDiam10Code(p_oTree1->GetSpecies(), p_oTree1->GetType()), &fDiam);
    p_oTree1->GetValue(p_oPop->GetHeightCode(p_oTree1->GetSpecies(), p_oTree1->GetType()), &fHeight);
    p_oTree1->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree1->GetSpecies(), p_oTree1->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    //Sapling, Species 1
    fExpectedDiam = 9.798550725;
    fExpectedHeight = 9.323947201;
    fExpectedGrowth = 14.49275362;
    p_oTree2->GetValue(p_oPop->GetDiam10Code(p_oTree2->GetSpecies(), p_oTree2->GetType()), &fDiam);
    p_oTree2->GetValue(p_oPop->GetHeightCode(p_oTree2->GetSpecies(), p_oTree2->GetType()), &fHeight);
    p_oTree2->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree2->GetSpecies(), p_oTree2->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    //Adult, Species 1
    fExpectedDiam = 25.7;
    fExpectedHeight = 21.79757207;
    fExpectedGrowth = 3.5;
    p_oTree3->GetValue(p_oPop->GetDbhCode(p_oTree3->GetSpecies(), p_oTree3->GetType()), &fDiam);
    p_oTree3->GetValue(p_oPop->GetHeightCode(p_oTree3->GetSpecies(), p_oTree3->GetType()), &fHeight);
    p_oTree3->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree3->GetSpecies(), p_oTree3->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    //Seedling, Species 2
    fExpectedDiam = 1.49;
    fExpectedHeight = 1.225714595;
    fExpectedGrowth = 1.45;
    p_oTree4->GetValue(p_oPop->GetDiam10Code(p_oTree4->GetSpecies(), p_oTree4->GetType()), &fDiam);
    p_oTree4->GetValue(p_oPop->GetHeightCode(p_oTree4->GetSpecies(), p_oTree4->GetType()), &fHeight);
    p_oTree4->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree4->GetSpecies(), p_oTree4->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    //Sapling, Species 2
    fExpectedDiam = 7.553061224;
    fExpectedHeight = 6.327644755;
    fExpectedGrowth = 13.26530612;
    p_oTree5->GetValue(p_oPop->GetDiam10Code(p_oTree5->GetSpecies(), p_oTree5->GetType()), &fDiam);
    p_oTree5->GetValue(p_oPop->GetHeightCode(p_oTree5->GetSpecies(), p_oTree5->GetType()), &fHeight);
    p_oTree5->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree5->GetSpecies(), p_oTree5->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    //Adult, Species 2
    fExpectedDiam = 18.53033708;
    fExpectedHeight = 14.43388034;
    fExpectedGrowth = 3.651685393;
    p_oTree6->GetValue(p_oPop->GetDbhCode(p_oTree6->GetSpecies(), p_oTree6->GetType()), &fDiam);
    p_oTree6->GetValue(p_oPop->GetHeightCode(p_oTree6->GetSpecies(), p_oTree6->GetType()), &fHeight);
    p_oTree6->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree6->GetSpecies(), p_oTree6->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);

    //Dead tree - no growth
    fExpectedDiam = 10;
    fExpectedGrowth = 0;
    p_oTree7->GetValue(p_oPop->GetDbhCode(p_oTree6->GetSpecies(), p_oTree6->GetType()), &fDiam);
    p_oTree7->GetValue(p_oPop->GetFloatDataCode("Growth", p_oTree6->GetSpecies(), p_oTree6->GetType()), &fGrowth);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedGrowth - fGrowth), 0.001);
    delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

////////////////////////////////////////////////////////////////////////////
// TestNormalProcessingRun2()
// Tests to make sure that precedence requests are properly met when diameter
// and HeightIncrementers need to go in different orders.
// WriteGrowthOrgXMLFile2() creates the file. There are four species with each
// possible combination of possible precedence. One tree of each species is
// created; growth is run; and the results are checked.
////////////////////////////////////////////////////////////////////////////
TEST(GrowthOrg, TestNormalProcessingRun2) {

  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    clTreePopulation * p_oPop;
    clTree *p_oTree1, *p_oTree2, *p_oTree3, *p_oTree4;
    float fDiam, fHeight, fExpectedDiam, fExpectedHeight;

    //Load our test file and get our tree population pointers
    p_oSimManager->ReadFile( WriteGrowthOrgXMLFile2() );
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );

    //Create our four trees and set diameter and height for each
    fDiam = 15;
    fHeight = 4;
    p_oTree1 = p_oPop->CreateTree(1, 1, 0, clTreePopulation::adult, fDiam);
    p_oTree1->SetValue(p_oPop->GetHeightCode(p_oTree1->GetSpecies(), p_oTree1->GetType()), fHeight, false, false);

    fDiam = 16;
    fHeight = 5;
    p_oTree2 = p_oPop->CreateTree(2, 2, 1, clTreePopulation::adult, fDiam);
    p_oTree2->SetValue(p_oPop->GetHeightCode(p_oTree2->GetSpecies(), p_oTree2->GetType()), fHeight, false, false);

    fDiam = 17;
    fHeight = 6;
    p_oTree3 = p_oPop->CreateTree(2, 2, 2, clTreePopulation::adult, fDiam);
    p_oTree3->SetValue(p_oPop->GetHeightCode(p_oTree3->GetSpecies(), p_oTree3->GetType()), fHeight, false, false);

    fDiam = 18;
    fHeight = 7;
    p_oTree4 = p_oPop->CreateTree(2, 2, 3, clTreePopulation::adult, fDiam);
    p_oTree4->SetValue(p_oPop->GetHeightCode(p_oTree4->GetSpecies(), p_oTree4->GetType()), fHeight, false, false);

    //Run our timestep
    p_oSimManager->RunSim(1);

    //Check our results for each tree

    fExpectedDiam = 22.04635276;
    fExpectedHeight = 9.637082209;
    p_oTree1->GetValue(p_oPop->GetDbhCode(p_oTree1->GetSpecies(), p_oTree1->GetType()), &fDiam);
    p_oTree1->GetValue(p_oPop->GetHeightCode(p_oTree1->GetSpecies(), p_oTree1->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);

    fExpectedDiam = 19;
    fExpectedHeight = 7.7;
    p_oTree2->GetValue(p_oPop->GetDbhCode(p_oTree2->GetSpecies(), p_oTree2->GetType()), &fDiam);
    p_oTree2->GetValue(p_oPop->GetHeightCode(p_oTree2->GetSpecies(), p_oTree2->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);

    fExpectedDiam = 22.16012186;
    fExpectedHeight = 8.56;
    p_oTree3->GetValue(p_oPop->GetDbhCode(p_oTree3->GetSpecies(), p_oTree3->GetType()), &fDiam);
    p_oTree3->GetValue(p_oPop->GetHeightCode(p_oTree3->GetSpecies(), p_oTree3->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);

    fExpectedDiam = 23;
    fExpectedHeight = 10.71;
    p_oTree4->GetValue(p_oPop->GetDbhCode(p_oTree4->GetSpecies(), p_oTree4->GetType()), &fDiam);
    p_oTree4->GetValue(p_oPop->GetHeightCode(p_oTree4->GetSpecies(), p_oTree4->GetType()), &fHeight);
    EXPECT_LT(fabs(fExpectedDiam - fDiam), 0.001);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.001);

    delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

////////////////////////////////////////////////////////////////////////////
// TestErrorProcessing()
////////////////////////////////////////////////////////////////////////////
TEST(GrowthOrg, TestErrorProcessing) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try
  {
    p_oSimManager->ReadFile(WriteGrowthOrgXMLErrorFile1());
    modelErr stcErr;
    stcErr.sMoreInfo = "TestGrowthOrg didn't catch bad behavior setup.";
    throw(stcErr);
  }
  catch (modelErr& err)
  {
    if (err.sFunction.compare("clGrowthOrg::PopulateGrowthTables") != 0)
    {
      modelErr stcErr;
      stcErr.sMoreInfo = "TestGrowthOrg caught the wrong error.";
      throw(stcErr);
    }
  }

  try
  {
    p_oSimManager->ReadFile(WriteGrowthOrgXMLErrorFile2());
    modelErr stcErr;
    stcErr.sMoreInfo = "TestGrowthOrg didn't catch bad behavior setup.";
    throw(stcErr);
  }
  catch (modelErr& err)
  {
    if (err.sFunction.compare("clGrowthOrg::PopulateGrowthTables") != 0)
    {
      modelErr stcErr;
      stcErr.sMoreInfo = "TestGrowthOrg caught the wrong error.";
      throw(stcErr);
    }
  }
  delete p_oSimManager;
}

////////////////////////////////////////////////////////////////////////////
// WriteGrowthOrgXMLFile1()
////////////////////////////////////////////////////////////////////////////
const char* WriteGrowthOrgXMLFile1() {
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
      << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
      << "<plot_temp_C>12</plot_temp_C>"
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
      << "<tr_canopyHeight>"
      << "<tr_chVal species=\"Species_1\">39.48</tr_chVal>"
      << "<tr_chVal species=\"Species_2\">39.54</tr_chVal>"
      << "</tr_canopyHeight>"
      << "<tr_stdAsympCrownRad>"
      << "<tr_sacrVal species=\"Species_1\">0.0549</tr_sacrVal>"
      << "<tr_sacrVal species=\"Species_2\">0.0614</tr_sacrVal>"
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
      << "<tr_cdtdVal species=\"Species_2\">0.5944</tr_cdtdVal>"
      << "</tr_conversionDiam10ToDBH>"
      << "<tr_interceptDiam10ToDBH>"
      << "<tr_idtdVal species=\"Species_1\">0</tr_idtdVal>"
      << "<tr_idtdVal species=\"Species_2\">0</tr_idtdVal>"
      << "</tr_interceptDiam10ToDBH>"
      << "<tr_stdAsympCrownHt>"
      << "<tr_sachVal species=\"Species_1\">0.389</tr_sachVal>"
      << "<tr_sachVal species=\"Species_2\">0.368</tr_sachVal>"
      << "</tr_stdAsympCrownHt>"
      << "<tr_stdCrownHtExp>"
      << "<tr_scheVal species=\"Species_1\">1.0</tr_scheVal>"
      << "<tr_scheVal species=\"Species_2\">1.0</tr_scheVal>"
      << "</tr_stdCrownHtExp>"
      << "<tr_slopeOfHeight-Diam10>"
      << "<tr_sohdVal species=\"Species_1\">0.03418</tr_sohdVal>"
      << "<tr_sohdVal species=\"Species_2\">0.0269</tr_sohdVal>"
      << "</tr_slopeOfHeight-Diam10>"
      << "<tr_slopeOfAsymHeight>"
      << "<tr_soahVal species=\"Species_1\">0.0299</tr_soahVal>"
      << "<tr_soahVal species=\"Species_2\">0.0241</tr_soahVal>"
      << "</tr_slopeOfAsymHeight>"
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
      << "</allometry>";

  oOut << "<behaviorList>"
      << "<behavior>"
      //Leave in one light so that "Light" will be registerd
      << "<behaviorName>ConstantGLI</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>1</listPosition>"
      << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_1\" type=\"Seedling\"/>"
      << "<applyTo species=\"Species_2\" type=\"Seedling\"/>"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>ConstBAGrowth</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>2</listPosition>"
      << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>ConstRadialGrowth</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>3</listPosition>"
      << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_1\" type=\"Seedling\"/>"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>HeightIncrementer</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>4</listPosition>"
      << "<applyTo species=\"Species_1\" type=\"Seedling\"/>"
      << "<applyTo species=\"Species_2\" type=\"Seedling\"/>"
      << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>ConstBAGrowth diam only</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>5</listPosition>"
      << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>ConstRadialGrowth diam only</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>6</listPosition>"
      << "<applyTo species=\"Species_2\" type=\"Seedling\"/>"
      << "</behavior>"
      //Have one mortality on the list so we can test dead trees
      << "<behavior>"
      << "<behaviorName>StochasticMortality</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>7</listPosition>"
      << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_1\" type=\"Seedling\"/>"
      << "<applyTo species=\"Species_2\" type=\"Seedling\"/>"
      << "</behavior>"
      << "</behaviorList>"
      << "<ConstantGLI1>"
      << "<li_constGLI>100</li_constGLI>"
      << "</ConstantGLI1>"
      << "<ConstBAGrowth2>"
      << "<gr_adultConstAreaInc>"
      << "<gr_acaiVal species=\"Species_1\">0.2</gr_acaiVal>"
      << "</gr_adultConstAreaInc>"
      << "</ConstBAGrowth2>"
      << "<ConstBAGrowth5>"
      << "<gr_adultConstAreaInc>"
      << "<gr_acaiVal species=\"Species_2\">0.13</gr_acaiVal>"
      << "</gr_adultConstAreaInc>"
      << "</ConstBAGrowth5>"
      << "<ConstRadialGrowth3>"
      << "<gr_adultConstRadialInc>"
      << "<gr_acriVal species=\"Species_1\">3.5</gr_acriVal>"
      << "</gr_adultConstRadialInc>"
      << "</ConstRadialGrowth3>"
      << "<ConstRadialGrowth6>"
      << "<gr_adultConstRadialInc>"
      << "<gr_acriVal species=\"Species_2\">1.45</gr_acriVal>"
      << "</gr_adultConstRadialInc>"
      << "</ConstRadialGrowth6>"
      << "<StochasticMortality7>"
      << "<mo_stochasticMortRate>"
      << "<mo_smrVal species=\"Species_2\">0</mo_smrVal>"
      << "<mo_smrVal species=\"Species_1\">0</mo_smrVal>"
      << "</mo_stochasticMortRate>"
      << "</StochasticMortality7>"
      << "</paramFile>";

  oOut.close();

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteGrowthOrgXMLFile2()
////////////////////////////////////////////////////////////////////////////
const char* WriteGrowthOrgXMLFile2() {
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
      << "<plot_latitude>55.37</plot_latitude>"
      << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
      << "<plot_temp_C>12</plot_temp_C>"
      << "</plot>"
      << "<trees>"
      << "<tr_speciesList>"
      << "<tr_species speciesName=\"Species_1\"/>"
      << "<tr_species speciesName=\"Species_2\"/>"
      << "<tr_species speciesName=\"Species_3\"/>"
      << "<tr_species speciesName=\"Species_4\"/>"
      << "</tr_speciesList>"
      << "<tr_seedDiam10Cm>0.1</tr_seedDiam10Cm>"
      << "<tr_minAdultDBH>"
      << "<tr_madVal species=\"Species_1\">10.0</tr_madVal>"
      << "<tr_madVal species=\"Species_2\">10.0</tr_madVal>"
      << "<tr_madVal species=\"Species_3\">10.0</tr_madVal>"
      << "<tr_madVal species=\"Species_4\">10.0</tr_madVal>"
      << "</tr_minAdultDBH>"
      << "<tr_maxSeedlingHeight>"
      << "<tr_mshVal species=\"Species_1\">2</tr_mshVal>"
      << "<tr_mshVal species=\"Species_2\">2</tr_mshVal>"
      << "<tr_mshVal species=\"Species_3\">2</tr_mshVal>"
      << "<tr_mshVal species=\"Species_4\">2</tr_mshVal>"
      << "</tr_maxSeedlingHeight>"
      << "</trees>"
      << "<allometry>"
      << "<tr_canopyHeight>"
      << "<tr_chVal species=\"Species_1\">46</tr_chVal>"
      << "<tr_chVal species=\"Species_2\">39.48</tr_chVal>"
      << "<tr_chVal species=\"Species_3\">39.54</tr_chVal>"
      << "<tr_chVal species=\"Species_4\">39.54</tr_chVal>"
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
      << "<tr_cdtdVal species=\"Species_2\">0.5944</tr_cdtdVal>"
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
      << "<tr_whatSeedlingHeightDiam>"
      << "<tr_wsehdVal species=\"Species_1\">1</tr_wsehdVal>"
      << "<tr_wsehdVal species=\"Species_2\">1</tr_wsehdVal>"
      << "<tr_wsehdVal species=\"Species_3\">1</tr_wsehdVal>"
      << "<tr_wsehdVal species=\"Species_4\">1</tr_wsehdVal>"
      << "</tr_whatSeedlingHeightDiam>"
      << "<tr_whatSaplingHeightDiam>"
      << "<tr_wsahdVal species=\"Species_1\">1</tr_wsahdVal>"
      << "<tr_wsahdVal species=\"Species_2\">1</tr_wsahdVal>"
      << "<tr_wsahdVal species=\"Species_3\">1</tr_wsahdVal>"
      << "<tr_wsahdVal species=\"Species_4\">1</tr_wsahdVal>"
      << "</tr_whatSaplingHeightDiam>"
      << "<tr_whatAdultHeightDiam>"
      << "<tr_wahdVal species=\"Species_1\">1</tr_wahdVal>"
      << "<tr_wahdVal species=\"Species_2\">1</tr_wahdVal>"
      << "<tr_wahdVal species=\"Species_3\">1</tr_wahdVal>"
      << "<tr_wahdVal species=\"Species_4\">1</tr_wahdVal>"
      << "</tr_whatAdultHeightDiam>"
      << "<tr_seedlingLinearSlope>"
      << "<tr_selsVal species=\"Species_1\">0.8</tr_selsVal>"
      << "<tr_selsVal species=\"Species_2\">0.9</tr_selsVal>"
      << "<tr_selsVal species=\"Species_3\">1</tr_selsVal>"
      << "<tr_selsVal species=\"Species_4\">1.1</tr_selsVal>"
      << "</tr_seedlingLinearSlope>"
      << "<tr_seedlingLinearIntercept>"
      << "<tr_seliVal species=\"Species_1\">10</tr_seliVal>"
      << "<tr_seliVal species=\"Species_2\">11</tr_seliVal>"
      << "<tr_seliVal species=\"Species_3\">12</tr_seliVal>"
      << "<tr_seliVal species=\"Species_4\">13</tr_seliVal>"
      << "</tr_seedlingLinearIntercept>"
      << "<tr_saplingLinearSlope>"
      << "<tr_salsVal species=\"Species_1\">0.8</tr_salsVal>"
      << "<tr_salsVal species=\"Species_2\">0.9</tr_salsVal>"
      << "<tr_salsVal species=\"Species_3\">1</tr_salsVal>"
      << "<tr_salsVal species=\"Species_4\">1.1</tr_salsVal>"
      << "</tr_saplingLinearSlope>"
      << "<tr_saplingLinearIntercept>"
      << "<tr_saliVal species=\"Species_1\">10</tr_saliVal>"
      << "<tr_saliVal species=\"Species_2\">11</tr_saliVal>"
      << "<tr_saliVal species=\"Species_3\">12</tr_saliVal>"
      << "<tr_saliVal species=\"Species_4\">13</tr_saliVal>"
      << "</tr_saplingLinearIntercept>"
      << "<tr_adultLinearSlope>"
      << "<tr_alsVal species=\"Species_1\">0.8</tr_alsVal>"
      << "<tr_alsVal species=\"Species_2\">0.9</tr_alsVal>"
      << "<tr_alsVal species=\"Species_3\">1</tr_alsVal>"
      << "<tr_alsVal species=\"Species_4\">1.1</tr_alsVal>"
      << "</tr_adultLinearSlope>"
      << "<tr_adultLinearIntercept>"
      << "<tr_aliVal species=\"Species_1\">10</tr_aliVal>"
      << "<tr_aliVal species=\"Species_2\">11</tr_aliVal>"
      << "<tr_aliVal species=\"Species_3\">12</tr_aliVal>"
      << "<tr_aliVal species=\"Species_4\">13</tr_aliVal>"
      << "</tr_adultLinearIntercept>"
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

  oOut << "<behaviorList>"
      << "<behavior>"
      << "<behaviorName>ConstantGLI</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>1</listPosition>"
      << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_4\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>PRSemiStochastic diam only</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>2</listPosition>"
      << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>HeightIncrementer</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>3</listPosition>"
      << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>SimpleLinearGrowth height only</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>4</listPosition>"
      << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_4\" type=\"Adult\"/>"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>ConstRadialGrowth diam only</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>5</listPosition>"
      << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_4\" type=\"Adult\"/>"
      << "</behavior>"
      << "</behaviorList>";

  oOut << "<ConstantGLI1>"
      << "<li_constGLI>100</li_constGLI>"
      << "</ConstantGLI1>"
      << "<PRSemiStochastic2>"
      << "<gr_prStochHiteThreshold>"
      << "<gr_pshtVal species=\"Species_1\">20</gr_pshtVal>"
      << "<gr_pshtVal species=\"Species_3\">20</gr_pshtVal>"
      << "</gr_prStochHiteThreshold>"
      << "<gr_prStochDetermA>"
      << "<gr_psdaVal species=\"Species_1\">2</gr_psdaVal>"
      << "<gr_psdaVal species=\"Species_3\">4</gr_psdaVal>"
      << "</gr_prStochDetermA>"
      << "<gr_prStochDetermB>"
      << "<gr_psdbVal species=\"Species_1\">-0.006</gr_psdbVal>"
      << "<gr_psdbVal species=\"Species_3\">-0.002</gr_psdbVal>"
      << "</gr_prStochDetermB>"
      << "<gr_prStochMeanDBH>"
      << "<gr_psmdVal species=\"Species_1\">30</gr_psmdVal>"
      << "<gr_psmdVal species=\"Species_3\">35</gr_psmdVal>"
      << "</gr_prStochMeanDBH>"
      << "<gr_prStochStdDev>"
      << "<gr_pssdVal species=\"Species_1\">0.1</gr_pssdVal>"
      << "<gr_pssdVal species=\"Species_3\">0.2</gr_pssdVal>"
      << "</gr_prStochStdDev>"
      << "</PRSemiStochastic2>"
      << "<ConstRadialGrowth5>"
      << "<gr_adultConstRadialInc>"
      << "<gr_acriVal species=\"Species_2\">15</gr_acriVal>"
      << "<gr_acriVal species=\"Species_4\">25</gr_acriVal>"
      << "</gr_adultConstRadialInc>"
      << "</ConstRadialGrowth5>"
      << "<SimpleLinearGrowth4>"
      << "<gr_heightSimpleLinearIntercept>"
      << "<gr_hsliVal species=\"Species_3\">56</gr_hsliVal>"
      << "<gr_hsliVal species=\"Species_4\">71</gr_hsliVal>"
      << "</gr_heightSimpleLinearIntercept>"
      << "<gr_heightSimpleLinearSlope>"
      << "<gr_hslsVal species=\"Species_3\">2</gr_hslsVal>"
      << "<gr_hslsVal species=\"Species_4\">3</gr_hslsVal>"
      << "</gr_heightSimpleLinearSlope>"
      << "</SimpleLinearGrowth4>"
      << "</paramFile>";

  oOut.close();

  return cFileString;

}

////////////////////////////////////////////////////////////////////////////
// WriteGrowthOrgXMLErrorFile1()
////////////////////////////////////////////////////////////////////////////
const char* WriteGrowthOrgXMLErrorFile1() {
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
      << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
      << "<plot_temp_C>12</plot_temp_C>"
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
      << "<tr_canopyHeight>"
      << "<tr_chVal species=\"Species_1\">39.48</tr_chVal>"
      << "<tr_chVal species=\"Species_2\">39.54</tr_chVal>"
      << "</tr_canopyHeight>"
      << "<tr_stdAsympCrownRad>"
      << "<tr_sacrVal species=\"Species_1\">0.0549</tr_sacrVal>"
      << "<tr_sacrVal species=\"Species_2\">0.0614</tr_sacrVal>"
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
      << "<tr_cdtdVal species=\"Species_2\">0.5944</tr_cdtdVal>"
      << "</tr_conversionDiam10ToDBH>"
      << "<tr_interceptDiam10ToDBH>"
      << "<tr_idtdVal species=\"Species_1\">0</tr_idtdVal>"
      << "<tr_idtdVal species=\"Species_2\">0</tr_idtdVal>"
      << "</tr_interceptDiam10ToDBH>"
      << "<tr_stdAsympCrownHt>"
      << "<tr_sachVal species=\"Species_1\">0.389</tr_sachVal>"
      << "<tr_sachVal species=\"Species_2\">0.368</tr_sachVal>"
      << "</tr_stdAsympCrownHt>"
      << "<tr_stdCrownHtExp>"
      << "<tr_scheVal species=\"Species_1\">1.0</tr_scheVal>"
      << "<tr_scheVal species=\"Species_2\">1.0</tr_scheVal>"
      << "</tr_stdCrownHtExp>"
      << "<tr_slopeOfHeight-Diam10>"
      << "<tr_sohdVal species=\"Species_1\">0.03418</tr_sohdVal>"
      << "<tr_sohdVal species=\"Species_2\">0.0269</tr_sohdVal>"
      << "</tr_slopeOfHeight-Diam10>"
      << "<tr_slopeOfAsymHeight>"
      << "<tr_soahVal species=\"Species_1\">0.0299</tr_soahVal>"
      << "<tr_soahVal species=\"Species_2\">0.0241</tr_soahVal>"
      << "</tr_slopeOfAsymHeight>"
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
      //Leave in one light so that "Light" will be registerd
      << "<behaviorName>ConstantGLI</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>1</listPosition>"
      << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_1\" type=\"Seedling\"/>"
      << "<applyTo species=\"Species_2\" type=\"Seedling\"/>"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>ConstBAGrowth</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>2</listPosition>"
      << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>ConstRadialGrowth</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>3</listPosition>"
      << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_1\" type=\"Seedling\"/>"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>HeightIncrementer</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>4</listPosition>"
      << "<applyTo species=\"Species_1\" type=\"Seedling\"/>"
      << "<applyTo species=\"Species_2\" type=\"Seedling\"/>"
      << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>ConstBAGrowth diam only</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>5</listPosition>"
      << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>ConstRadialGrowth diam only</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>6</listPosition>"
      << "<applyTo species=\"Species_2\" type=\"Seedling\"/>"
      << "</behavior>"
      << "</behaviorList>"
      << "<ConstantGLI1>"
      << "<li_constGLI>100</li_constGLI>"
      << "</ConstantGLI1>"
      << "<ConstBAGrowth2>"
      << "<gr_adultConstAreaInc>"
      << "<gr_acaiVal species=\"Species_1\">0.2</gr_acaiVal>"
      << "</gr_adultConstAreaInc>"
      << "</ConstBAGrowth2>"
      << "<ConstBAGrowth5>"
      << "<gr_adultConstAreaInc>"
      << "<gr_acaiVal species=\"Species_2\">0.13</gr_acaiVal>"
      << "</gr_adultConstAreaInc>"
      << "</ConstBAGrowth5>"
      << "<ConstRadialGrowth6>"
      << "<gr_adultConstRadialInc>"
      << "<gr_acriVal species=\"Species_1\">3.5</gr_acriVal>"
      << "<gr_acriVal species=\"Species_2\">1.45</gr_acriVal>"
      << "</gr_adultConstRadialInc>"
      << "</ConstRadialGrowth6>"
      << "</paramFile>";

  oOut.close();

  return cFileString;
}


////////////////////////////////////////////////////////////////////////////
// WriteGrowthOrgXMLErrorFile2()
////////////////////////////////////////////////////////////////////////////
const char* WriteGrowthOrgXMLErrorFile2() {
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
      << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
      << "<plot_temp_C>12</plot_temp_C>"
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
      << "<tr_canopyHeight>"
      << "<tr_chVal species=\"Species_1\">39.48</tr_chVal>"
      << "<tr_chVal species=\"Species_2\">39.54</tr_chVal>"
      << "</tr_canopyHeight>"
      << "<tr_stdAsympCrownRad>"
      << "<tr_sacrVal species=\"Species_1\">0.0549</tr_sacrVal>"
      << "<tr_sacrVal species=\"Species_2\">0.0614</tr_sacrVal>"
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
      << "<tr_cdtdVal species=\"Species_2\">0.5944</tr_cdtdVal>"
      << "</tr_conversionDiam10ToDBH>"
      << "<tr_interceptDiam10ToDBH>"
      << "<tr_idtdVal species=\"Species_1\">0</tr_idtdVal>"
      << "<tr_idtdVal species=\"Species_2\">0</tr_idtdVal>"
      << "</tr_interceptDiam10ToDBH>"
      << "<tr_stdAsympCrownHt>"
      << "<tr_sachVal species=\"Species_1\">0.389</tr_sachVal>"
      << "<tr_sachVal species=\"Species_2\">0.368</tr_sachVal>"
      << "</tr_stdAsympCrownHt>"
      << "<tr_stdCrownHtExp>"
      << "<tr_scheVal species=\"Species_1\">1.0</tr_scheVal>"
      << "<tr_scheVal species=\"Species_2\">1.0</tr_scheVal>"
      << "</tr_stdCrownHtExp>"
      << "<tr_slopeOfHeight-Diam10>"
      << "<tr_sohdVal species=\"Species_1\">0.03418</tr_sohdVal>"
      << "<tr_sohdVal species=\"Species_2\">0.0269</tr_sohdVal>"
      << "</tr_slopeOfHeight-Diam10>"
      << "<tr_slopeOfAsymHeight>"
      << "<tr_soahVal species=\"Species_1\">0.0299</tr_soahVal>"
      << "<tr_soahVal species=\"Species_2\">0.0241</tr_soahVal>"
      << "</tr_slopeOfAsymHeight>"
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
      //Leave in one light so that "Light" will be registerd
      << "<behaviorName>ConstantGLI</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>1</listPosition>"
      << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_1\" type=\"Seedling\"/>"
      << "<applyTo species=\"Species_2\" type=\"Seedling\"/>"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>ConstBAGrowth</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>2</listPosition>"
      << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>ConstRadialGrowth</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>3</listPosition>"
      << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_1\" type=\"Seedling\"/>"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>HeightIncrementer</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>4</listPosition>"
      << "<applyTo species=\"Species_1\" type=\"Seedling\"/>"
      << "<applyTo species=\"Species_2\" type=\"Seedling\"/>"
      << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>ConstBAGrowth diam only</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>5</listPosition>"
      << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>ConstRadialGrowth diam only</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>6</listPosition>"
      << "<applyTo species=\"Species_2\" type=\"Seedling\"/>"
      << "</behavior>"
      << "</behaviorList>"
      << "<ConstantGLI1>"
      << "<li_constGLI>100</li_constGLI>"
      << "</ConstantGLI1>"
      << "<ConstBAGrowth2>"
      << "<gr_adultConstAreaInc>"
      << "<gr_acaiVal species=\"Species_1\">0.2</gr_acaiVal>"
      << "</gr_adultConstAreaInc>"
      << "</ConstBAGrowth2>"
      << "<ConstBAGrowth5>"
      << "<gr_adultConstAreaInc>"
      << "<gr_acaiVal species=\"Species_2\">0.13</gr_acaiVal>"
      << "</gr_adultConstAreaInc>"
      << "</ConstBAGrowth5>"
      << "<ConstRadialGrowth6>"
      << "<gr_adultConstRadialInc>"
      << "<gr_acriVal species=\"Species_1\">3.5</gr_acriVal>"
      << "<gr_acriVal species=\"Species_2\">1.45</gr_acriVal>"
      << "</gr_adultConstRadialInc>"
      << "</ConstRadialGrowth6>"
      << "</paramFile>";

  oOut.close();

  return cFileString;
}
