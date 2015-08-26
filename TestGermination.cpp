//---------------------------------------------------------------------------
// TestGermination.cpp
//---------------------------------------------------------------------------
#include "TestGermination.h"
#include <gtest/gtest.h>
#include "SimManager.h"
#include "Grid.h"
#include "BehaviorBase.h"
#include <fstream>
#include <math.h>

/////////////////////////////////////////////////////////////////////////////
// TestGerminationNormalProcessing()
/////////////////////////////////////////////////////////////////////////////
TEST(Germination, TestGerminationNormalProcessing)
{
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    //Feed our file to the sim manager
    p_oSimManager->ReadFile(WriteGerminationXMLFile1());

    //Run the germination behavior
    p_oSimManager->GetBehaviorObject(p_oSimManager->GetNumberOfBehaviors() - 1)->Action();

    //Verify file 1
    VerifyXMLFile1(p_oSimManager->GetGridObject("Dispersed Seeds"));
    delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

/////////////////////////////////////////////////////////////////////////////
// TestGerminationErrorProcessing()
/////////////////////////////////////////////////////////////////////////////
TEST(Germination, TestGerminationErrorProcessing) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try
    {
      p_oSimManager->ReadFile(WriteGerminationXMLErrorFile1());
      FAIL() << "TestGermination didn't catch bad parameter.";
    }
    catch (modelErr& err)
    {
      if (err.sFunction.compare("clGermination::GetData") != 0)
      {
        FAIL() << "TestGermination caught the wrong error.";
      }
    }

  try
  {
    p_oSimManager->ReadFile(WriteGerminationXMLErrorFile2());
    FAIL() << "TestGermination didn't catch bad parameter.";
  }
  catch (modelErr& err)
  {
    if (err.sFunction.compare("clGermination::GetData") != 0)
    {
      FAIL() << "TestGermination caught the wrong error.";
    }
  }
  delete p_oSimManager;
}


/////////////////////////////////////////////////////////////////////////////
// VerifyXMLFile1
/////////////////////////////////////////////////////////////////////////////
void VerifyXMLFile1(clGrid * p_oSeedGrid) {

  float fNumExpectedSeeds, fNumActualSeeds;
  int iNumXCells = p_oSeedGrid->GetNumberXCells(), iNumYCells = p_oSeedGrid->GetNumberYCells(), iX, iY, //loop counters
       iSpecies1Code = p_oSeedGrid->GetFloatDataCode("seeds_0"),
       iSpecies2Code = p_oSeedGrid->GetFloatDataCode("seeds_1"),
       iSpecies3Code = p_oSeedGrid->GetFloatDataCode("seeds_2");

  //Make sure we got the codes
  EXPECT_GT(iSpecies1Code, -1);
  EXPECT_GT(iSpecies2Code, -1);
  EXPECT_GT(iSpecies3Code, -1);

  for (iX = 0; iX < iNumXCells; iX++) {
    for (iY = 0; iY < iNumYCells; iY++) {

      //Species 1
      fNumExpectedSeeds = (iX + iY) * 0.3;
      p_oSeedGrid->GetValueOfCell(iX, iY, iSpecies1Code, & fNumActualSeeds);
      EXPECT_LT(fabs(fNumExpectedSeeds - fNumActualSeeds), 2);

      //Species 2
      fNumExpectedSeeds = 2 * (iX + iY) * 0.7;
      p_oSeedGrid->GetValueOfCell(iX, iY, iSpecies2Code, & fNumActualSeeds);
      EXPECT_LT(fabs(fNumExpectedSeeds - fNumActualSeeds), 2);

      //Species 3
      fNumExpectedSeeds = (iX + iY) * 3;
      p_oSeedGrid->GetValueOfCell(iX, iY, iSpecies3Code, & fNumActualSeeds);
      EXPECT_LT(fabs(fNumExpectedSeeds - fNumActualSeeds), 2);
    }
  }
}



/////////////////////////////////////////////////////////////////////////////
// WriteGerminationXMLFile1()
/////////////////////////////////////////////////////////////////////////////
const char* WriteGerminationXMLFile1() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";
  int iX, iY, iNumX = 20, iNumY = 20;

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06010101\">"
       << "<plot>"
       << "<timesteps>1</timesteps>"
       << "<yearsPerTimestep>5</yearsPerTimestep>"
       << "<randomSeed>1</randomSeed>"
       << "<plot_lenX>100.0</plot_lenX>"
       << "<plot_lenY>100.0</plot_lenY>"
       << "<plot_latitude>55.37</plot_latitude>"
       << "<plot_precip_mm_yr>1150.64</plot_precip_mm_yr>"
       << "<plot_temp_C>12.8</plot_temp_C>"
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
       << "<tr_mshVal species=\"Species_1\">1.35</tr_mshVal>"
       << "<tr_mshVal species=\"Species_2\">1.35</tr_mshVal>"
       << "<tr_mshVal species=\"Species_3\">1.35</tr_mshVal>"
       << "</tr_maxSeedlingHeight>"
       << "</trees>"
       << "<allometry>"
       << "<tr_canopyHeight>"
       << "<tr_chVal species=\"Species_1\">39.48</tr_chVal>"
       << "<tr_chVal species=\"Species_2\">39.54</tr_chVal>"
       << "<tr_chVal species=\"Species_3\">40.0</tr_chVal>"
       << "</tr_canopyHeight>"
       << "<tr_stdAsympCrownRad>"
       << "<tr_sacrVal species=\"Species_1\">0.0549</tr_sacrVal>"
       << "<tr_sacrVal species=\"Species_2\">0.0614</tr_sacrVal>"
       << "<tr_sacrVal species=\"Species_3\">0.0242</tr_sacrVal>"
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
       << "<tr_cdtdVal species=\"Species_3\">0.7059</tr_cdtdVal>"
       << "</tr_conversionDiam10ToDBH>"
       << "<tr_interceptDiam10ToDBH>"
       << "<tr_idtdVal species=\"Species_1\">0</tr_idtdVal>"
       << "<tr_idtdVal species=\"Species_2\">0</tr_idtdVal>"
       << "<tr_idtdVal species=\"Species_3\">0</tr_idtdVal>"
       << "</tr_interceptDiam10ToDBH>"
       << "<tr_stdAsympCrownHt>"
       << "<tr_sachVal species=\"Species_1\">0.389</tr_sachVal>"
       << "<tr_sachVal species=\"Species_2\">0.368</tr_sachVal>"
       << "<tr_sachVal species=\"Species_3\">0.464</tr_sachVal>"
       << "</tr_stdAsympCrownHt>"
       << "<tr_stdCrownHtExp>"
       << "<tr_scheVal species=\"Species_1\">1.0</tr_scheVal>"
       << "<tr_scheVal species=\"Species_2\">1.0</tr_scheVal>"
       << "<tr_scheVal species=\"Species_3\">1.0</tr_scheVal>"
       << "</tr_stdCrownHtExp>"
       << "<tr_slopeOfHeight-Diam10>"
       << "<tr_sohdVal species=\"Species_1\">0.03418</tr_sohdVal>"
       << "<tr_sohdVal species=\"Species_2\">0.0269</tr_sohdVal>"
       << "<tr_sohdVal species=\"Species_3\">0.02871</tr_sohdVal>"
       << "</tr_slopeOfHeight-Diam10>"
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
       << "</allometry>";

  //Auto-generate seed grid values
  oOut << "<grid gridName=\"Dispersed Seeds\">"
       << "<ma_floatCodes>"
       << "<ma_floatCode label=\"seeds_0\">0</ma_floatCode>"
       << "<ma_floatCode label=\"seeds_1\">1</ma_floatCode>"
       << "<ma_floatCode label=\"seeds_2\">2</ma_floatCode>"
       << "</ma_floatCodes>"
       << "<ma_intCodes>"
       << "<ma_intCode label=\"count\">4</ma_intCode>"
       << "</ma_intCodes>"
       << "<ma_boolCodes>"
       << "<ma_boolCode label=\"Is Gap\">0</ma_boolCode>"
       << "</ma_boolCodes>"
       << "<ma_lengthXCells>5</ma_lengthXCells>"
       << "<ma_lengthYCells>5</ma_lengthYCells>";

  for (iX = 0; iX < iNumX; iX++)
  {
    for (iY = 0; iY < iNumY; iY++)
    {
      oOut << "<ma_v x=\"" << iX << "\" y=\"" << iY << "\">"
           << "<fl c=\"0\">" << (iX + iY) << "</fl>"
           << "<fl c=\"1\">" << 2 * (iX + iY) << "</fl>"
           << "<fl c=\"2\">" << 3 * (iX + iY) << "</fl>"
           << "</ma_v>";
    }
  }
  oOut << "</grid>"
       << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>NonSpatialDisperse</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>Germination</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>2</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Seed\"/>"
       << "<applyTo species=\"Species_2\" type=\"Seed\"/>"
       << "</behavior>"
       << "</behaviorList>"
       << "<NonSpatialDisperse1>"
       << "<di_minDbhForReproduction>"
       << "<di_mdfrVal species=\"Species_1\">15.0</di_mdfrVal>"
       << "<di_mdfrVal species=\"Species_2\">15.0</di_mdfrVal>"
       << "<di_mdfrVal species=\"Species_3\">15.0</di_mdfrVal>"
       << "</di_minDbhForReproduction>"
       << "<di_nonSpatialSlopeOfLambda>"
       << "<di_nssolVal species=\"Species_1\">1</di_nssolVal>"
       << "<di_nssolVal species=\"Species_2\">1</di_nssolVal>"
       << "<di_nssolVal species=\"Species_3\">1</di_nssolVal>"
       << "</di_nonSpatialSlopeOfLambda>"
       << "<di_nonSpatialInterceptOfLambda>"
       << "<di_nsiolVal species=\"Species_1\">1</di_nsiolVal>"
       << "<di_nsiolVal species=\"Species_2\">1</di_nsiolVal>"
       << "<di_nsiolVal species=\"Species_3\">1</di_nsiolVal>"
       << "</di_nonSpatialInterceptOfLambda>"
       << "</NonSpatialDisperse1>"
       << "<GeneralDisperse>"
       << "<di_seedDistributionMethod>0</di_seedDistributionMethod>"
       << "</GeneralDisperse>"
       << "<Germination2>"
       << "<ge_proportionGerminating>"
       << "<ge_pgVal species=\"Species_1\">0.3</ge_pgVal>"
       << "<ge_pgVal species=\"Species_2\">0.7</ge_pgVal>"
       << "</ge_proportionGerminating>"
       << "</Germination2>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}



/////////////////////////////////////////////////////////////////////////////
// WriteGerminationXMLErrorFile1()
/////////////////////////////////////////////////////////////////////////////
const char* WriteGerminationXMLErrorFile1() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";
  int iX, iY, iNumX = 20, iNumY = 20;

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06010101\">"
       << "<plot>"
       << "<timesteps>1</timesteps>"
       << "<yearsPerTimestep>5</yearsPerTimestep>"
       << "<randomSeed>1</randomSeed>"
       << "<plot_lenX>100.0</plot_lenX>"
       << "<plot_lenY>100.0</plot_lenY>"
       << "<plot_latitude>55.37</plot_latitude>"
       << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
       << "<plot_temp_C>12.88171785</plot_temp_C>"
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
       << "<tr_mshVal species=\"Species_1\">1.35</tr_mshVal>"
       << "<tr_mshVal species=\"Species_2\">1.35</tr_mshVal>"
       << "<tr_mshVal species=\"Species_3\">1.35</tr_mshVal>"
       << "</tr_maxSeedlingHeight>"
       << "</trees>"
       << "<allometry>"
       << "<tr_canopyHeight>"
       << "<tr_chVal species=\"Species_1\">39.48</tr_chVal>"
       << "<tr_chVal species=\"Species_2\">39.54</tr_chVal>"
       << "<tr_chVal species=\"Species_3\">40.0</tr_chVal>"
       << "</tr_canopyHeight>"
       << "<tr_stdAsympCrownRad>"
       << "<tr_sacrVal species=\"Species_1\">0.0549</tr_sacrVal>"
       << "<tr_sacrVal species=\"Species_2\">0.0614</tr_sacrVal>"
       << "<tr_sacrVal species=\"Species_3\">0.0242</tr_sacrVal>"
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
       << "<tr_cdtdVal species=\"Species_3\">0.7059</tr_cdtdVal>"
       << "</tr_conversionDiam10ToDBH>"
       << "<tr_interceptDiam10ToDBH>"
       << "<tr_idtdVal species=\"Species_1\">0</tr_idtdVal>"
       << "<tr_idtdVal species=\"Species_2\">0</tr_idtdVal>"
       << "<tr_idtdVal species=\"Species_3\">0</tr_idtdVal>"
       << "</tr_interceptDiam10ToDBH>"
       << "<tr_stdAsympCrownHt>"
       << "<tr_sachVal species=\"Species_1\">0.389</tr_sachVal>"
       << "<tr_sachVal species=\"Species_2\">0.368</tr_sachVal>"
       << "<tr_sachVal species=\"Species_3\">0.464</tr_sachVal>"
       << "</tr_stdAsympCrownHt>"
       << "<tr_stdCrownHtExp>"
       << "<tr_scheVal species=\"Species_1\">1.0</tr_scheVal>"
       << "<tr_scheVal species=\"Species_2\">1.0</tr_scheVal>"
       << "<tr_scheVal species=\"Species_3\">1.0</tr_scheVal>"
       << "</tr_stdCrownHtExp>"
       << "<tr_slopeOfHeight-Diam10>"
       << "<tr_sohdVal species=\"Species_1\">0.03418</tr_sohdVal>"
       << "<tr_sohdVal species=\"Species_2\">0.0269</tr_sohdVal>"
       << "<tr_sohdVal species=\"Species_3\">0.02871</tr_sohdVal>"
       << "</tr_slopeOfHeight-Diam10>"
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
       << "</allometry>";

  //Auto-generate seed grid values
  oOut << "<grid gridName=\"Dispersed Seeds\">"
       << "<ma_floatCodes>"
       << "<ma_floatCode label=\"seeds_0\">0</ma_floatCode>"
       << "<ma_floatCode label=\"seeds_1\">1</ma_floatCode>"
       << "<ma_floatCode label=\"seeds_2\">2</ma_floatCode>"
       << "</ma_floatCodes>"
       << "<ma_intCodes>"
       << "<ma_intCode label=\"count\">4</ma_intCode>"
       << "</ma_intCodes>"
       << "<ma_boolCodes>"
       << "<ma_boolCode label=\"Is Gap\">0</ma_boolCode>"
       << "</ma_boolCodes>"
       << "<ma_lengthXCells>5</ma_lengthXCells>"
       << "<ma_lengthYCells>5</ma_lengthYCells>";

  for (iX = 0; iX < iNumX; iX++) {
    for (iY = 0; iY < iNumY; iY++) {
      oOut << "<ma_v x=\"" << iX << "\" y=\"" << iY << "\">"
           << "<fl c=\"0\">" << (iX + iY) << "</fl>"
           << "<fl c=\"1\">" << 2 * (iX + iY) << "</fl>"
           << "<fl c=\"2\">" << 3 * (iX + iY) << "</fl>"
           << "</ma_v>";
    }
  }
  oOut << "</grid>"
       << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>NonSpatialDisperse</behaviorName>"
       << "<listPosition>1</listPosition>"
       << "<version>1</version>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>Germination</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>2</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Seed\"/>"
       << "<applyTo species=\"Species_2\" type=\"Seed\"/>"
       << "</behavior>"
       << "</behaviorList>"
       << "<NonSpatialDisperse1>"
       << "<di_minDbhForReproduction>"
       << "<di_mdfrVal species=\"Species_1\">15.0</di_mdfrVal>"
       << "<di_mdfrVal species=\"Species_2\">15.0</di_mdfrVal>"
       << "<di_mdfrVal species=\"Species_3\">15.0</di_mdfrVal>"
       << "</di_minDbhForReproduction>"
       << "<di_nonSpatialSlopeOfLambda>"
       << "<di_nssolVal species=\"Species_1\">1</di_nssolVal>"
       << "<di_nssolVal species=\"Species_2\">1</di_nssolVal>"
       << "<di_nssolVal species=\"Species_3\">1</di_nssolVal>"
       << "</di_nonSpatialSlopeOfLambda>"
       << "<di_nonSpatialInterceptOfLambda>"
       << "<di_nsiolVal species=\"Species_1\">1</di_nsiolVal>"
       << "<di_nsiolVal species=\"Species_2\">1</di_nsiolVal>"
       << "<di_nsiolVal species=\"Species_3\">1</di_nsiolVal>"
       << "</di_nonSpatialInterceptOfLambda>"
       << "</NonSpatialDisperse1>"
       << "<GeneralDisperse>"
       << "<di_seedDistributionMethod>0</di_seedDistributionMethod>"
       << "</GeneralDisperse>"
       << "<Germination2>"
       << "<ge_proportionGerminating>"
       << "<ge_pgVal species=\"Species_1\">-3</ge_pgVal>"
       << "<ge_pgVal species=\"Species_2\">0.7</ge_pgVal>"
       << "</ge_proportionGerminating>"
       << "</Germination2>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteGerminationXMLErrorFile2()
/////////////////////////////////////////////////////////////////////////////
const char* WriteGerminationXMLErrorFile2() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";
  int iX, iY, iNumX = 20, iNumY = 20;

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06010101\">"
       << "<plot>"
       << "<timesteps>1</timesteps>"
       << "<yearsPerTimestep>5</yearsPerTimestep>"
       << "<randomSeed>1</randomSeed>"
       << "<plot_lenX>100.0</plot_lenX>"
       << "<plot_lenY>100.0</plot_lenY>"
       << "<plot_latitude>55.37</plot_latitude>"
       << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
       << "<plot_temp_C>12.88171785</plot_temp_C>"
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
       << "<tr_mshVal species=\"Species_1\">1.35</tr_mshVal>"
       << "<tr_mshVal species=\"Species_2\">1.35</tr_mshVal>"
       << "<tr_mshVal species=\"Species_3\">1.35</tr_mshVal>"
       << "</tr_maxSeedlingHeight>"
       << "</trees>"
       << "<allometry>"
       << "<tr_canopyHeight>"
       << "<tr_chVal species=\"Species_1\">39.48</tr_chVal>"
       << "<tr_chVal species=\"Species_2\">39.54</tr_chVal>"
       << "<tr_chVal species=\"Species_3\">40.0</tr_chVal>"
       << "</tr_canopyHeight>"
       << "<tr_stdAsympCrownRad>"
       << "<tr_sacrVal species=\"Species_1\">0.0549</tr_sacrVal>"
       << "<tr_sacrVal species=\"Species_2\">0.0614</tr_sacrVal>"
       << "<tr_sacrVal species=\"Species_3\">0.0242</tr_sacrVal>"
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
       << "<tr_cdtdVal species=\"Species_3\">0.7059</tr_cdtdVal>"
       << "</tr_conversionDiam10ToDBH>"
       << "<tr_interceptDiam10ToDBH>"
       << "<tr_idtdVal species=\"Species_1\">0</tr_idtdVal>"
       << "<tr_idtdVal species=\"Species_2\">0</tr_idtdVal>"
       << "<tr_idtdVal species=\"Species_3\">0</tr_idtdVal>"
       << "</tr_interceptDiam10ToDBH>"
       << "<tr_stdAsympCrownHt>"
       << "<tr_sachVal species=\"Species_1\">0.389</tr_sachVal>"
       << "<tr_sachVal species=\"Species_2\">0.368</tr_sachVal>"
       << "<tr_sachVal species=\"Species_3\">0.464</tr_sachVal>"
       << "</tr_stdAsympCrownHt>"
       << "<tr_stdCrownHtExp>"
       << "<tr_scheVal species=\"Species_1\">1.0</tr_scheVal>"
       << "<tr_scheVal species=\"Species_2\">1.0</tr_scheVal>"
       << "<tr_scheVal species=\"Species_3\">1.0</tr_scheVal>"
       << "</tr_stdCrownHtExp>"
       << "<tr_slopeOfHeight-Diam10>"
       << "<tr_sohdVal species=\"Species_1\">0.03418</tr_sohdVal>"
       << "<tr_sohdVal species=\"Species_2\">0.0269</tr_sohdVal>"
       << "<tr_sohdVal species=\"Species_3\">0.02871</tr_sohdVal>"
       << "</tr_slopeOfHeight-Diam10>"
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
       << "</allometry>";

  //Auto-generate seed grid values
  oOut << "<grid gridName=\"Dispersed Seeds\">" << "<ma_floatCodes>"
       << "<ma_floatCode label=\"seeds_0\">0</ma_floatCode>"
       << "<ma_floatCode label=\"seeds_1\">1</ma_floatCode>"
       << "<ma_floatCode label=\"seeds_2\">2</ma_floatCode>"
       << "</ma_floatCodes>"
       << "<ma_intCodes>"
       << "<ma_intCode label=\"count\">4</ma_intCode>" << "</ma_intCodes>" << "<ma_boolCodes>"
       << "<ma_boolCode label=\"Is Gap\">0</ma_boolCode>" << "</ma_boolCodes>" << "<ma_lengthXCells>5</ma_lengthXCells>"
       << "<ma_lengthYCells>5</ma_lengthYCells>";

  for (iX = 0; iX < iNumX; iX++) {
    for (iY = 0; iY < iNumY; iY++) {
      oOut << "<ma_v x=\"" << iX << "\" y=\"" << iY << "\">"
           << "<fl c=\"0\">" << (iX + iY) << "</fl>"
           << "<fl c=\"1\">" << 2 * (iX + iY) << "</fl>"
           << "<fl c=\"2\">" << 3 * (iX + iY) << "</fl>"
           << "</ma_v>";
    }
  }
  oOut << "</grid>"
       << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>NonSpatialDisperse</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>Germination</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>2</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Seed\"/>"
       << "<applyTo species=\"Species_2\" type=\"Seed\"/>"
       << "</behavior>"
       << "</behaviorList>"
       << "<NonSpatialDisperse1>"
       << "<di_minDbhForReproduction>"
       << "<di_mdfrVal species=\"Species_1\">15.0</di_mdfrVal>"
       << "<di_mdfrVal species=\"Species_2\">15.0</di_mdfrVal>"
       << "<di_mdfrVal species=\"Species_3\">15.0</di_mdfrVal>"
       << "</di_minDbhForReproduction>"
       << "<di_nonSpatialSlopeOfLambda>"
       << "<di_nssolVal species=\"Species_1\">1</di_nssolVal>"
       << "<di_nssolVal species=\"Species_2\">1</di_nssolVal>"
       << "<di_nssolVal species=\"Species_3\">1</di_nssolVal>"
       << "</di_nonSpatialSlopeOfLambda>"
       << "<di_nonSpatialInterceptOfLambda>"
       << "<di_nsiolVal species=\"Species_1\">1</di_nsiolVal>"
       << "<di_nsiolVal species=\"Species_2\">1</di_nsiolVal>"
       << "<di_nsiolVal species=\"Species_3\">1</di_nsiolVal>"
       << "</di_nonSpatialInterceptOfLambda>"
       << "</NonSpatialDisperse1>"
       << "<GeneralDisperse>"
       << "<di_seedDistributionMethod>0</di_seedDistributionMethod>"
       << "</GeneralDisperse>"
       << "<Germination2>"
       << "<ge_proportionGerminating>"
       << "<ge_pgVal species=\"Species_1\">0.3</ge_pgVal>"
       << "<ge_pgVal species=\"Species_2\">1.45</ge_pgVal>"
       << "</ge_proportionGerminating>"
       << "</Germination2>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}
