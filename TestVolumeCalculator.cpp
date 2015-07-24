//---------------------------------------------------------------------------
// TestVolumeCalculator.cpp
//---------------------------------------------------------------------------
#include "TestVolumeCalculator.h"
#include <gtest/gtest.h>
#include <fstream>
#include <math.h>
#include "TreePopulation.h"
#include "SimManager.h"
#include "BehaviorBase.h"

////////////////////////////////////////////////////////////////////////////
// TestErrorProcessing()
////////////////////////////////////////////////////////////////////////////
TEST(VolumeCalculator, TestErrorProcessing) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try
  {
    p_oSimManager->ReadFile(WriteVolumeCalculatorXMLErrorFile1());
    FAIL() << "TestVolumeCalculator error processing didn't catch error for WriteVolumeCalculatorXMLErrorFile1.";
  }
  catch (modelErr& err)
  {
    if (err.sFunction.compare("clVolumeCalculator::GetData") != 0)
    {
      FAIL() << "TestVolumeCalculator error processing caught wrong error for WriteVolumeCalculatorXMLErrorFile1.";
    }
    ;
  }

  try
  {
    p_oSimManager->ReadFile(WriteVolumeCalculatorXMLErrorFile2());
    FAIL() << "TestVolumeCalculator error processing didn't catch error for WriteVolumeCalculatorXMLErrorFile2.";
  }
  catch (modelErr& err)
  {
    if (err.sFunction.compare("clVolumeCalculator::GetData") != 0)
    {
      FAIL() << "TestVolumeCalculator error processing caught wrong error for WriteVolumeCalculatorXMLErrorFile2.";
    }
    ;
  }

  try
  {
    p_oSimManager->ReadFile(WriteVolumeCalculatorXMLErrorFile3());
    FAIL() << "TestVolumeCalculator error processing didn't catch error for WriteVolumeCalculatorXMLErrorFile3.";
  }
  catch (modelErr& err)
  {
    if (err.sFunction.compare("clVolumeCalculator::GetData") != 0)
    {
      FAIL() << "TestVolumeCalculator error processing caught wrong error for WriteVolumeCalculatorXMLErrorFile3.";
    }
    ;
  }

  try
  {
    p_oSimManager->ReadFile(WriteVolumeCalculatorXMLErrorFile4());
    FAIL() << "TestVolumeCalculator error processing didn't catch error for WriteVolumeCalculatorXMLErrorFile4.";
  }
  catch (modelErr& err)
  {
    if (err.sFunction.compare("clVolumeCalculator::RegisterTreeDataMembers") != 0)
    {
      FAIL() << "TestVolumeCalculator error processing caught wrong error for WriteVolumeCalculatorXMLErrorFile4.";
    }
    ;
  }
  delete p_oSimManager;
}

////////////////////////////////////////////////////////////////////////////
// NormalRun1()
// Tests normal processing. It does this by calling NormalRun1(),
// NormalRun2(), NormalRun3(), NormalRun4(), and NormalRun5().
////////////////////////////////////////////////////////////////////////////
TEST(VolumeCalculator, NormalRun1) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    clTreePopulation * p_oPop;
    clTree *p_oTargetTree1,
    *p_oTargetTree2,
    *p_oTargetTree3,
    *p_oTargetTree4,
    *p_oTargetTree5;
    float fDiam, fVolume, fExpectedVolume;
    int iSpecies;

    //Load our test file and get our tree population pointers
    p_oSimManager->ReadFile( WriteVolumeCalculatorXMLFile1() );
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );

    //Create our trees
    fDiam = 15.552;
    iSpecies = 2;
    p_oTargetTree1 = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, fDiam);

    fDiam = 25.7345;
    iSpecies = 1;
    p_oTargetTree2 = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, fDiam);

    fDiam = 4;
    iSpecies = 2;
    p_oTargetTree3 = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, fDiam);

    fDiam = 8;
    iSpecies = 1;
    p_oTargetTree4 = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, fDiam);

    fDiam = 75;
    iSpecies = 2;
    p_oTargetTree5 = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, fDiam);

    //Now do the run
    p_oSimManager->RunSim(1);

    //Check the volumes
    p_oTargetTree1->GetValue(
        p_oPop->GetFloatDataCode("Volume",
            p_oTargetTree1->GetSpecies(),
            p_oTargetTree1->GetType()), &fVolume);
    fExpectedVolume = 0.064271476;
    EXPECT_LT(fabs(fExpectedVolume - fVolume), 0.001);

    p_oTargetTree2->GetValue(
        p_oPop->GetFloatDataCode("Volume",
            p_oTargetTree2->GetSpecies(),
            p_oTargetTree2->GetType()), &fVolume);
    fExpectedVolume = 0.469870084;
    EXPECT_LT(fabs(fExpectedVolume - fVolume), 0.001);

    p_oTargetTree3->GetValue(
        p_oPop->GetFloatDataCode("Volume",
            p_oTargetTree3->GetSpecies(),
            p_oTargetTree3->GetType()), &fVolume);
    fExpectedVolume = 0;
    EXPECT_LT(fabs(fExpectedVolume - fVolume), 0.001);

    p_oTargetTree4->GetValue(
        p_oPop->GetFloatDataCode("Volume",
            p_oTargetTree4->GetSpecies(),
            p_oTargetTree4->GetType()), &fVolume);
    fExpectedVolume = 0.010241452;
    EXPECT_LT(fabs(fExpectedVolume - fVolume), 0.001);

    p_oTargetTree5->GetValue(
        p_oPop->GetFloatDataCode("Volume",
            p_oTargetTree5->GetSpecies(),
            p_oTargetTree5->GetType()), &fVolume);
    fExpectedVolume = 2.594042442;
    EXPECT_LT(fabs(fExpectedVolume - fVolume), 0.001);
    delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

////////////////////////////////////////////////////////////////////////////
// NormalRun2()
// Performs the second normal processing run. WriteVolumeCalculatorXMLFile2() does setup.
// Two trees are created of two species. Then the run is allowed to proceed
// and their volumes are checked.
////////////////////////////////////////////////////////////////////////////
TEST(VolumeCalculator, NormalRun2) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    clTreePopulation * p_oPop;
    clTree *p_oTargetTree1,
    *p_oTargetTree2;
    float fDiam, fVolume, fExpectedVolume;
    int iSpecies;

    //Load our test file and get our tree population pointers
    p_oSimManager->ReadFile( WriteVolumeCalculatorXMLFile2() );
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );

    //Create our trees
    fDiam = 0.5;
    iSpecies = 2;
    p_oTargetTree1 = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, fDiam);

    fDiam = 0.7125;
    iSpecies = 1;
    p_oTargetTree2 = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, fDiam);

    //Now do the run
    p_oSimManager->RunSim(1);

    //Check the volumes
    p_oTargetTree1->GetValue(
        p_oPop->GetFloatDataCode("Volume",
            p_oTargetTree1->GetSpecies(),
            p_oTargetTree1->GetType()), &fVolume);
    fExpectedVolume = 7.18624E-05;
    EXPECT_LT(fabs(fExpectedVolume - fVolume), 0.0001);

    p_oTargetTree2->GetValue(
        p_oPop->GetFloatDataCode("Volume",
            p_oTargetTree2->GetSpecies(),
            p_oTargetTree2->GetType()), &fVolume);
    fExpectedVolume = 2.04402E-05;
    EXPECT_LT(fabs(fExpectedVolume - fVolume), 0.0001);
    delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

////////////////////////////////////////////////////////////////////////////
// NormalRun3()
// Performs the third normal processing run. WriteVolumeCalculatorXMLFile3() does setup.
// One tree is created. Then the run is allowed to proceed and its volume
// is checked.
////////////////////////////////////////////////////////////////////////////
TEST(VolumeCalculator, NormalRun3) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    clTreePopulation * p_oPop;
    clTree *p_oTargetTree1;
    float fDiam, fVolume, fExpectedVolume;
    int iSpecies;

    //Load our test file and get our tree population pointers
    p_oSimManager->ReadFile( WriteVolumeCalculatorXMLFile3() );
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );

    //Create our trees
    fDiam = 0.5;
    iSpecies = 2;
    p_oTargetTree1 = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, fDiam);

    //Now do the run
    p_oSimManager->RunSim(1);

    //Check the volumes
    p_oTargetTree1->GetValue(
        p_oPop->GetFloatDataCode("Volume",
            p_oTargetTree1->GetSpecies(),
            p_oTargetTree1->GetType()), &fVolume);
    fExpectedVolume = 0;
    EXPECT_LT(fabs(fExpectedVolume - fVolume), 0.001);
    delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

////////////////////////////////////////////////////////////////////////////
// NormalRun4()
// Performs the fourth normal processing run. WriteVolumeCalculatorXMLFile4() does setup.
// Four trees are created of two species. Then the run is allowed to proceed
// and their volumes are checked.
////////////////////////////////////////////////////////////////////////////
TEST(VolumeCalculator, NormalRun4) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    clTreePopulation * p_oPop;
    clTree *p_oTargetTree1,
    *p_oTargetTree2,
    *p_oTargetTree3,
    *p_oTargetTree4;
    float fDiam, fVolume, fExpectedVolume;
    int iSpecies;

    //Load our test file and get our tree population pointers
    p_oSimManager->ReadFile( WriteVolumeCalculatorXMLFile4() );
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );

    //Create our trees
    fDiam = 15.552;
    iSpecies = 2;
    p_oTargetTree1 = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, fDiam);

    fDiam = 25.7345;
    iSpecies = 1;
    p_oTargetTree2 = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, fDiam);

    fDiam = 8;
    iSpecies = 1;
    p_oTargetTree3 = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, fDiam);

    fDiam = 75;
    iSpecies = 2;
    p_oTargetTree4 = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, fDiam);

    //Now do the run
    p_oSimManager->RunSim(1);

    //Check the volumes
    p_oTargetTree1->GetValue(
        p_oPop->GetFloatDataCode("Volume",
            p_oTargetTree1->GetSpecies(),
            p_oTargetTree1->GetType()), &fVolume);
    fExpectedVolume = 0.066022717;
    EXPECT_LT(fabs(fExpectedVolume - fVolume), 0.001);

    p_oTargetTree2->GetValue(
        p_oPop->GetFloatDataCode("Volume",
            p_oTargetTree2->GetSpecies(),
            p_oTargetTree2->GetType()), &fVolume);
    fExpectedVolume = 0.452522026;
    EXPECT_LT(fabs(fExpectedVolume - fVolume), 0.001);

    p_oTargetTree3->GetValue(
        p_oPop->GetFloatDataCode("Volume",
            p_oTargetTree3->GetSpecies(),
            p_oTargetTree3->GetType()), &fVolume);
    fExpectedVolume = 0.014693001;
    EXPECT_LT(fabs(fExpectedVolume - fVolume), 0.0001);

    p_oTargetTree4->GetValue(
        p_oPop->GetFloatDataCode("Volume",
            p_oTargetTree4->GetSpecies(),
            p_oTargetTree4->GetType()), &fVolume);
    fExpectedVolume = 2.499628902;
    EXPECT_LT(fabs(fExpectedVolume - fVolume), 10);
    delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

////////////////////////////////////////////////////////////////////////////
// NormalRun5()
// Performs the fifth normal processing run. WriteVolumeCalculatorXMLFile5() does setup.
// Two trees are created of two species. Then the run is allowed to proceed
// and their volumes are checked.
////////////////////////////////////////////////////////////////////////////
TEST(VolumeCalculator, NormalRun5) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    clTreePopulation * p_oPop;
    clTree *p_oTargetTree1,
    *p_oTargetTree2;
    float fDiam, fVolume, fExpectedVolume;
    int iSpecies;

    //Load our test file and get our tree population pointers
    p_oSimManager->ReadFile( WriteVolumeCalculatorXMLFile5() );
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );

    //Create our trees
    fDiam = 0.5;
    iSpecies = 2;
    p_oTargetTree1 = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, fDiam);

    fDiam = 0.7125;
    iSpecies = 1;
    p_oTargetTree2 = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, fDiam);

    //Now do the run
    p_oSimManager->RunSim(1);

    //Check the volumes
    p_oTargetTree1->GetValue(
        p_oPop->GetFloatDataCode("Volume",
            p_oTargetTree1->GetSpecies(),
            p_oTargetTree1->GetType()), &fVolume);
    fExpectedVolume = 0;
    EXPECT_LT(fabs(fExpectedVolume - fVolume), 0.001);

    p_oTargetTree2->GetValue(
        p_oPop->GetFloatDataCode("Volume",
            p_oTargetTree2->GetSpecies(),
            p_oTargetTree2->GetType()), &fVolume);
    fExpectedVolume = 0;
    EXPECT_LT(fabs(fExpectedVolume - fVolume), 0.001);
    delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

////////////////////////////////////////////////////////////////////////////
// WriteVolumeCalculatorXMLFile1()
////////////////////////////////////////////////////////////////////////////
const char* WriteVolumeCalculatorXMLFile1() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  WriteVolumeCalculatorCommonStuff(oOut);

  oOut << "<vo_stumpHeight>0</vo_stumpHeight>"
       << "<vo_minUsableDiam>5</vo_minUsableDiam>"
       << "<vo_segmentLength>1</vo_segmentLength>"
       << "</TreeVolumeCalculator1>"
       << "</paramFile>";

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteVolumeCalculatorXMLFile2()
////////////////////////////////////////////////////////////////////////////
const char* WriteVolumeCalculatorXMLFile2() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  WriteVolumeCalculatorCommonStuff(oOut);

  oOut << "<vo_stumpHeight>0</vo_stumpHeight>"
       << "<vo_minUsableDiam>0</vo_minUsableDiam>"
       << "<vo_segmentLength>2</vo_segmentLength>"
       << "</TreeVolumeCalculator1>"
       << "</paramFile>";

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteVolumeCalculatorXMLFile3()
////////////////////////////////////////////////////////////////////////////
const char* WriteVolumeCalculatorXMLFile3() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  WriteVolumeCalculatorCommonStuff(oOut);

  oOut << "<vo_stumpHeight>200</vo_stumpHeight>"
       << "<vo_minUsableDiam>0</vo_minUsableDiam>"
       << "<vo_segmentLength>3</vo_segmentLength>"
       << "</TreeVolumeCalculator1>"
       << "</paramFile>";

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteVolumeCalculatorXMLFile4()
////////////////////////////////////////////////////////////////////////////
const char* WriteVolumeCalculatorXMLFile4() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  WriteVolumeCalculatorCommonStuff(oOut);

  oOut << "<vo_stumpHeight>13</vo_stumpHeight>"
       << "<vo_minUsableDiam>0</vo_minUsableDiam>"
       << "<vo_segmentLength>0.75</vo_segmentLength>"
       << "</TreeVolumeCalculator1>"
       << "</paramFile>";

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteVolumeCalculatorXMLFile5()
////////////////////////////////////////////////////////////////////////////
const char* WriteVolumeCalculatorXMLFile5() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  WriteVolumeCalculatorCommonStuff(oOut);

  oOut << "<vo_stumpHeight>0</vo_stumpHeight>"
       << "<vo_minUsableDiam>3</vo_minUsableDiam>"
       << "<vo_segmentLength>2</vo_segmentLength>"
       << "</TreeVolumeCalculator1>"
       << "</paramFile>";

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteVolumeCalculatorXMLErrorFile1()
////////////////////////////////////////////////////////////////////////////
const char* WriteVolumeCalculatorXMLErrorFile1() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  WriteVolumeCalculatorCommonStuff(oOut);

  oOut << "<vo_stumpHeight>-10</vo_stumpHeight>"
       << "<vo_minUsableDiam>5</vo_minUsableDiam>"
       << "<vo_segmentLength>1</vo_segmentLength>"
       << "</TreeVolumeCalculator1>"
       << "</paramFile>";

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteVolumeCalculatorXMLErrorFile2()
////////////////////////////////////////////////////////////////////////////
const char* WriteVolumeCalculatorXMLErrorFile2() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  WriteVolumeCalculatorCommonStuff(oOut);

  oOut << "<vo_stumpHeight>0</vo_stumpHeight>"
       << "<vo_minUsableDiam>-5</vo_minUsableDiam>"
       << "<vo_segmentLength>1</vo_segmentLength>"
       << "</TreeVolumeCalculator1>"
       << "</paramFile>";

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteVolumeCalculatorXMLErrorFile3()
////////////////////////////////////////////////////////////////////////////
const char* WriteVolumeCalculatorXMLErrorFile3() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  WriteVolumeCalculatorCommonStuff(oOut);

  oOut << "<vo_stumpHeight>0</vo_stumpHeight>"
       << "<vo_minUsableDiam>5</vo_minUsableDiam>"
       << "<vo_segmentLength>-1</vo_segmentLength>"
       << "</TreeVolumeCalculator1>"
       << "</paramFile>";

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteVolumeCalculatorXMLErrorFile4()
/////////////////////////////////////////////////////////////////////////////
const char* WriteVolumeCalculatorXMLErrorFile4()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06010101\">"
       << "<plot>"
       << "<timesteps>2</timesteps>"
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
       << "<tr_species speciesName=\"Species_2\" />"
       << "</tr_speciesList>"
       << "<tr_seedDiam10Cm>0.1</tr_seedDiam10Cm>"
       << "<tr_minAdultDBH>"
       << "<tr_madVal species=\"Species_1\">0.0</tr_madVal>"
       << "<tr_madVal species=\"Species_2\">0.0</tr_madVal>"
       << "</tr_minAdultDBH>"
       << "<tr_maxSeedlingHeight>"
       << "<tr_mshVal species=\"Species_1\">1.35</tr_mshVal>"
       << "<tr_mshVal species=\"Species_2\">1.35</tr_mshVal>"
       << "</tr_maxSeedlingHeight>"
       << "</trees>"
       << "<allometry>"
       << "<tr_canopyHeight>"
       << "<tr_chVal species=\"Species_1\">39.48</tr_chVal>"
       << "<tr_chVal species=\"Species_2\">39.54</tr_chVal>"
       << "</tr_canopyHeight>"
       << "<tr_stdAsympCrownRad>"
       << "<tr_sacrVal species=\"Species_1\">0.0549</tr_sacrVal>"
       << "<tr_sacrVal species=\"Species_2\">0.0549</tr_sacrVal>"
       << "</tr_stdAsympCrownRad>"
       << "<tr_stdCrownRadExp>"
       << "<tr_screVal species=\"Species_1\">1.0</tr_screVal>"
       << "<tr_screVal species=\"Species_2\">1.0</tr_screVal>"
       << "</tr_stdCrownRadExp>"
       << "<tr_conversionDiam10ToDBH>"
       << "<tr_cdtdVal species=\"Species_1\">0.8008</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_2\">0.8008</tr_cdtdVal>"
       << "</tr_conversionDiam10ToDBH>"
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
        << "<tr_interceptDiam10ToDBH>"
       << "<tr_idtdVal species=\"Species_1\">0</tr_idtdVal>"
       << "<tr_idtdVal species=\"Species_2\">0</tr_idtdVal>"
       << "</tr_interceptDiam10ToDBH>"
       << "<tr_slopeOfAsymHeight>"
       << "<tr_soahVal species=\"Species_1\">0.0299</tr_soahVal>"
       << "<tr_soahVal species=\"Species_2\">0.0241</tr_soahVal>"
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
       << "<behaviorName>TreeVolumeCalculator</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_1\" type=\"Seedling\"/>"
       << "</behavior>"
       << "</behaviorList>";

  oOut << "<TreeVolumeCalculator1>"
       << "<vo_taperA>"
       << "<vo_taVal species=\"Species_2\">0.843142</vo_taVal>"
       << "<vo_taVal species=\"Species_3\">0.8</vo_taVal>"
       << "</vo_taperA>"
       << "<vo_taperB>"
       << "<vo_tbVal species=\"Species_2\">1.00813</vo_tbVal>"
       << "<vo_tbVal species=\"Species_3\">0.9</vo_tbVal>"
       << "</vo_taperB>"
       << "<vo_taperC>"
       << "<vo_tcVal species=\"Species_2\">0.031402</vo_tcVal>"
       << "<vo_tcVal species=\"Species_3\">0.032</vo_tcVal>"
       << "</vo_taperC>"
       << "<vo_taperD>"
       << "<vo_tdVal species=\"Species_2\">0.319773</vo_tdVal>"
       << "<vo_tdVal species=\"Species_3\">0.321</vo_tdVal>"
       << "</vo_taperD>"
       << "<vo_taperF>"
       << "<vo_tfVal species=\"Species_2\">-0.532732</vo_tfVal>"
       << "<vo_tfVal species=\"Species_3\">-0.51</vo_tfVal>"
       << "</vo_taperF>"
       << "<vo_taperG>"
       << "<vo_tgVal species=\"Species_2\">0.585361</vo_tgVal>"
       << "<vo_tgVal species=\"Species_3\">0.59</vo_tgVal>"
       << "</vo_taperG>"
       << "<vo_taperI>"
       << "<vo_tiVal species=\"Species_2\">1.0315</vo_tiVal>"
       << "<vo_tiVal species=\"Species_3\">1.04</vo_tiVal>"
       << "</vo_taperI>"
       << "<vo_taperJ>"
       << "<vo_tjVal species=\"Species_2\">0.018622</vo_tjVal>"
       << "<vo_tjVal species=\"Species_3\">0.02</vo_tjVal>"
       << "</vo_taperJ>"
       << "<vo_taperK>"
       << "<vo_tkVal species=\"Species_2\">-0.225146</vo_tkVal>"
       << "<vo_tkVal species=\"Species_3\">-0.23</vo_tkVal>"
       << "</vo_taperK>"
       << "<vo_barkA>"
       << "<vo_baVal species=\"Species_2\">0.03</vo_baVal>"
       << "<vo_baVal species=\"Species_3\">0.01</vo_baVal>"
       << "</vo_barkA>"
       << "<vo_barkB>"
       << "<vo_bbVal species=\"Species_2\">0.04</vo_bbVal>"
       << "<vo_bbVal species=\"Species_3\">1</vo_bbVal>"
       << "</vo_barkB>"
       << "<vo_barkC>"
       << "<vo_bcVal species=\"Species_2\">-0.0005</vo_bcVal>"
       << "<vo_bcVal species=\"Species_3\">0.001</vo_bcVal>"
       << "</vo_barkC>";
  oOut << "<vo_stumpHeight>0</vo_stumpHeight>"
       << "<vo_minUsableDiam>5</vo_minUsableDiam>"
       << "<vo_segmentLength>1</vo_segmentLength>"
       << "</TreeVolumeCalculator1>"
       << "</paramFile>";

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteVolumeCalculatorCommonStuff()
/////////////////////////////////////////////////////////////////////////////
void WriteVolumeCalculatorCommonStuff( std::fstream &oOut )
{
  using namespace std;
  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06010101\">"
       << "<plot>"
       << "<timesteps>2</timesteps>"
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
       << "<tr_species speciesName=\"Species_2\" />"
       << "<tr_species speciesName=\"Species_3\" />"
       << "</tr_speciesList>"
       << "<tr_seedDiam10Cm>0.1</tr_seedDiam10Cm>"
       << "<tr_minAdultDBH>"
       << "<tr_madVal species=\"Species_1\">0.0</tr_madVal>"
       << "<tr_madVal species=\"Species_2\">0.0</tr_madVal>"
       << "<tr_madVal species=\"Species_3\">0.0</tr_madVal>"
       << "</tr_minAdultDBH>"
       << "<tr_maxSeedlingHeight>"
       << "<tr_mshVal species=\"Species_1\">1.35</tr_mshVal>"
       << "<tr_mshVal species=\"Species_2\">1.35</tr_mshVal>"
       << "<tr_mshVal species=\"Species_3\">1.35</tr_mshVal>"
       << "</tr_maxSeedlingHeight>"
       << "</trees>"
       << "<allometry>"
       << "<tr_canopyHeight>"
       << "<tr_chVal species=\"Species_1\">39.48</tr_chVal>"
       << "<tr_chVal species=\"Species_2\">39.54</tr_chVal>"
       << "<tr_chVal species=\"Species_3\">45</tr_chVal>"
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
       << "<tr_conversionDiam10ToDBH>"
       << "<tr_cdtdVal species=\"Species_1\">0.8008</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_2\">0.8008</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_3\">0.8008</tr_cdtdVal>"
       << "</tr_conversionDiam10ToDBH>"
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
       << "<tr_slopeOfHeight-Diam10>"
       << "<tr_sohdVal species=\"Species_1\">0.03418</tr_sohdVal>"
       << "<tr_sohdVal species=\"Species_2\">0.03418</tr_sohdVal>"
       << "<tr_sohdVal species=\"Species_3\">0.03418</tr_sohdVal>"
       << "</tr_slopeOfHeight-Diam10>"
        << "<tr_interceptDiam10ToDBH>"
       << "<tr_idtdVal species=\"Species_1\">0</tr_idtdVal>"
       << "<tr_idtdVal species=\"Species_2\">0</tr_idtdVal>"
       << "<tr_idtdVal species=\"Species_3\">0</tr_idtdVal>"
       << "</tr_interceptDiam10ToDBH>"
       << "<tr_slopeOfAsymHeight>"
       << "<tr_soahVal species=\"Species_1\">0.0299</tr_soahVal>"
       << "<tr_soahVal species=\"Species_2\">0.0241</tr_soahVal>"
       << "<tr_soahVal species=\"Species_3\">0.0263</tr_soahVal>"
       << "</tr_slopeOfAsymHeight>"
       << "<tr_whatSeedlingHeightDiam>"
       << "<tr_wsehdVal species=\"Species_1\">0</tr_wsehdVal>"
       << "<tr_wsehdVal species=\"Species_2\">0</tr_wsehdVal>"
       << "<tr_wsehdVal species=\"Species_3\">0</tr_wsehdVal>"
       << "</tr_whatSeedlingHeightDiam>"
       << "<tr_whatSaplingHeightDiam>"
       << "<tr_wsahdVal species=\"Species_1\">0</tr_wsahdVal>"
       << "<tr_wsahdVal species=\"Species_2\">0</tr_wsahdVal>"
       << "<tr_wsahdVal species=\"Species_3\">0</tr_wsahdVal>"
       << "</tr_whatSaplingHeightDiam>"
       << "<tr_whatAdultHeightDiam>"
       << "<tr_wahdVal species=\"Species_1\">0</tr_wahdVal>"
       << "<tr_wahdVal species=\"Species_2\">0</tr_wahdVal>"
       << "<tr_wahdVal species=\"Species_3\">0</tr_wahdVal>"
       << "</tr_whatAdultHeightDiam>"
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
       << "</allometry>"
       << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>TreeVolumeCalculator</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_3\" type=\"Sapling\"/>"
       << "</behavior>"
       << "</behaviorList>";

  oOut << "<TreeVolumeCalculator1>"
       << "<vo_taperA>"
       << "<vo_taVal species=\"Species_2\">0.843142</vo_taVal>"
       << "<vo_taVal species=\"Species_3\">0.8</vo_taVal>"
       << "</vo_taperA>"
       << "<vo_taperB>"
       << "<vo_tbVal species=\"Species_2\">1.00813</vo_tbVal>"
       << "<vo_tbVal species=\"Species_3\">0.9</vo_tbVal>"
       << "</vo_taperB>"
       << "<vo_taperC>"
       << "<vo_tcVal species=\"Species_2\">0.031402</vo_tcVal>"
       << "<vo_tcVal species=\"Species_3\">0.032</vo_tcVal>"
       << "</vo_taperC>"
       << "<vo_taperD>"
       << "<vo_tdVal species=\"Species_2\">0.319773</vo_tdVal>"
       << "<vo_tdVal species=\"Species_3\">0.321</vo_tdVal>"
       << "</vo_taperD>"
       << "<vo_taperF>"
       << "<vo_tfVal species=\"Species_2\">-0.532732</vo_tfVal>"
       << "<vo_tfVal species=\"Species_3\">-0.51</vo_tfVal>"
       << "</vo_taperF>"
       << "<vo_taperG>"
       << "<vo_tgVal species=\"Species_2\">0.585361</vo_tgVal>"
       << "<vo_tgVal species=\"Species_3\">0.59</vo_tgVal>"
       << "</vo_taperG>"
       << "<vo_taperI>"
       << "<vo_tiVal species=\"Species_2\">1.0315</vo_tiVal>"
       << "<vo_tiVal species=\"Species_3\">1.04</vo_tiVal>"
       << "</vo_taperI>"
       << "<vo_taperJ>"
       << "<vo_tjVal species=\"Species_2\">0.018622</vo_tjVal>"
       << "<vo_tjVal species=\"Species_3\">0.02</vo_tjVal>"
       << "</vo_taperJ>"
       << "<vo_taperK>"
       << "<vo_tkVal species=\"Species_2\">-0.225146</vo_tkVal>"
       << "<vo_tkVal species=\"Species_3\">-0.23</vo_tkVal>"
       << "</vo_taperK>"
       << "<vo_barkA>"
       << "<vo_baVal species=\"Species_2\">0.2</vo_baVal>"
       << "<vo_baVal species=\"Species_3\">0.01</vo_baVal>"
       << "</vo_barkA>"
       << "<vo_barkB>"
       << "<vo_bbVal species=\"Species_2\">0.8</vo_bbVal>"
       << "<vo_bbVal species=\"Species_3\">1</vo_bbVal>"
       << "</vo_barkB>"
       << "<vo_barkC>"
       << "<vo_bcVal species=\"Species_2\">0.01</vo_bcVal>"
       << "<vo_bcVal species=\"Species_3\">0.001</vo_bcVal>"
       << "</vo_barkC>";
}
