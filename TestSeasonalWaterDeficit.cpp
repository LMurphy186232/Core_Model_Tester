//---------------------------------------------------------------------------
// TestSeasonalWaterDeficit.cpp
//---------------------------------------------------------------------------
#include "TestSeasonalWaterDeficit.h"
#include <gtest/gtest.h>
#include "SimManager.h"
#include "TreePopulation.h"
#include "Plot.h"
#include "ModelMath.h"
#include "Grid.h"
#include <math.h>
#include <fstream>

/////////////////////////////////////////////////////////////////////////////
// TestNormalProcessingRun1()
// Tests normal processing for a 1-year timestep.
// WriteSeasonalWaterDeficitXMLFile1() does setup.
/////////////////////////////////////////////////////////////////////////////
TEST(SeasonalWaterDeficit, TestNormalProcessingRun1) {

  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    clPlot *p_oPlot;
    clGrid *p_oClimateGrid;
    float fActualTemp, fExpectedTemp, fActualPrecip, fExpectedPrecip,
          fActualWaterDeficit, fExpectedWaterDeficit;
    int iTempCode, iPrecipCode, iWDCode;

    //Feed our file to the sim manager
    p_oSimManager->ReadFile(WriteSeasonalWaterDeficitXMLFile1());
    p_oPlot = p_oSimManager->GetPlotObject();
    p_oClimateGrid = p_oSimManager->GetGridObject("State Variables");
    iTempCode = p_oClimateGrid->GetFloatDataCode("Temp.C");
    iPrecipCode = p_oClimateGrid->GetFloatDataCode("Precip.mm");
    iWDCode = p_oClimateGrid->GetFloatDataCode("WaterDeficit");

    //Initial conditions
    fExpectedPrecip = 1383.79729;
    fExpectedTemp = 6.273638083;
    fExpectedWaterDeficit = 220.1067155;
    fActualPrecip = p_oPlot->GetMeanAnnualPrecip();
    fActualTemp = p_oPlot->GetMeanAnnualTemp();
    fActualWaterDeficit = p_oPlot->GetWaterDeficit();
    EXPECT_LT(fabs(fExpectedPrecip - fActualPrecip), 0.000001);
    EXPECT_LT(fabs(fExpectedTemp - fActualTemp), 0.000001);
    EXPECT_LT(fabs(fExpectedWaterDeficit - fActualWaterDeficit), 0.001);

    p_oClimateGrid->GetValueOfCell(0, 0, iTempCode, &fActualTemp);
    p_oClimateGrid->GetValueOfCell(0, 0, iPrecipCode, &fActualPrecip);
    p_oClimateGrid->GetValueOfCell(0, 0, iWDCode, &fActualWaterDeficit);
    EXPECT_LT(fabs(fExpectedPrecip - fActualPrecip), 0.000001);
    EXPECT_LT(fabs(fExpectedTemp - fActualTemp), 0.000001);
    EXPECT_LT(fabs(fExpectedWaterDeficit - fActualWaterDeficit), 0.001);

    //Timestep 1
    p_oSimManager->RunSim(1);
    fExpectedPrecip = 1383.79729;
    fExpectedTemp = 6.273638083;
    fExpectedWaterDeficit = 220.1067155;
    fActualPrecip = p_oPlot->GetMeanAnnualPrecip();
    fActualTemp = p_oPlot->GetMeanAnnualTemp();
    fActualWaterDeficit = p_oPlot->GetWaterDeficit();
    EXPECT_LT(fabs(fExpectedPrecip - fActualPrecip), 0.000001);
    EXPECT_LT(fabs(fExpectedTemp - fActualTemp), 0.000001);
    EXPECT_LT(fabs(fExpectedWaterDeficit - fActualWaterDeficit), 0.001);

    p_oClimateGrid->GetValueOfCell(0, 0, iTempCode, &fActualTemp);
    p_oClimateGrid->GetValueOfCell(0, 0, iPrecipCode, &fActualPrecip);
    p_oClimateGrid->GetValueOfCell(0, 0, iWDCode, &fActualWaterDeficit);
    EXPECT_LT(fabs(fExpectedPrecip - fActualPrecip), 0.000001);
    EXPECT_LT(fabs(fExpectedTemp - fActualTemp), 0.000001);
    EXPECT_LT(fabs(fExpectedWaterDeficit - fActualWaterDeficit), 0.001);

    //Timestep 2
    p_oSimManager->RunSim(1);
    fExpectedPrecip = 1385.79729;
    fExpectedTemp = 6.473638083;
    fExpectedWaterDeficit = 232.3369145;
    fActualPrecip = p_oPlot->GetMeanAnnualPrecip();
    fActualTemp = p_oPlot->GetMeanAnnualTemp();
    fActualWaterDeficit = p_oPlot->GetWaterDeficit();
    EXPECT_LT(fabs(fExpectedPrecip - fActualPrecip), 0.000001);
    EXPECT_LT(fabs(fExpectedTemp - fActualTemp), 0.000001);
    EXPECT_LT(fabs(fExpectedWaterDeficit - fActualWaterDeficit), 0.001);

    p_oClimateGrid->GetValueOfCell(0, 0, iTempCode, &fActualTemp);
    p_oClimateGrid->GetValueOfCell(0, 0, iPrecipCode, &fActualPrecip);
    p_oClimateGrid->GetValueOfCell(0, 0, iWDCode, &fActualWaterDeficit);
    EXPECT_LT(fabs(fExpectedPrecip - fActualPrecip), 0.000001);
    EXPECT_LT(fabs(fExpectedTemp - fActualTemp), 0.000001);
    EXPECT_LT(fabs(fExpectedWaterDeficit - fActualWaterDeficit), 0.001);

    //Timestep 3
    p_oSimManager->RunSim(1);
    fExpectedPrecip = 1391.79729;
    fExpectedTemp = 6.673638083;
    fExpectedWaterDeficit = 242.4269619;
    fActualPrecip = p_oPlot->GetMeanAnnualPrecip();
    fActualTemp = p_oPlot->GetMeanAnnualTemp();
    fActualWaterDeficit = p_oPlot->GetWaterDeficit();
    EXPECT_LT(fabs(fExpectedPrecip - fActualPrecip), 0.000001);
    EXPECT_LT(fabs(fExpectedTemp - fActualTemp), 0.000001);
    EXPECT_LT(fabs(fExpectedWaterDeficit - fActualWaterDeficit), 0.001);

    p_oClimateGrid->GetValueOfCell(0, 0, iTempCode, &fActualTemp);
    p_oClimateGrid->GetValueOfCell(0, 0, iPrecipCode, &fActualPrecip);
    p_oClimateGrid->GetValueOfCell(0, 0, iWDCode, &fActualWaterDeficit);
    EXPECT_LT(fabs(fExpectedPrecip - fActualPrecip), 0.000001);
    EXPECT_LT(fabs(fExpectedTemp - fActualTemp), 0.000001);
    EXPECT_LT(fabs(fExpectedWaterDeficit - fActualWaterDeficit), 0.001);

    //Timestep 4
    p_oSimManager->RunSim(1);
    fExpectedPrecip = 1401.79729;
    fExpectedTemp = 6.873638083;
    fExpectedWaterDeficit = 250.3968329;
    fActualPrecip = p_oPlot->GetMeanAnnualPrecip();
    fActualTemp = p_oPlot->GetMeanAnnualTemp();
    fActualWaterDeficit = p_oPlot->GetWaterDeficit();
    EXPECT_LT(fabs(fExpectedPrecip - fActualPrecip), 0.000001);
    EXPECT_LT(fabs(fExpectedTemp - fActualTemp), 0.000001);
    EXPECT_LT(fabs(fExpectedWaterDeficit - fActualWaterDeficit), 0.001);

    p_oClimateGrid->GetValueOfCell(0, 0, iTempCode, &fActualTemp);
    p_oClimateGrid->GetValueOfCell(0, 0, iPrecipCode, &fActualPrecip);
    p_oClimateGrid->GetValueOfCell(0, 0, iWDCode, &fActualWaterDeficit);
    EXPECT_LT(fabs(fExpectedPrecip - fActualPrecip), 0.000001);
    EXPECT_LT(fabs(fExpectedTemp - fActualTemp), 0.000001);
    EXPECT_LT(fabs(fExpectedWaterDeficit - fActualWaterDeficit), 0.001);

    //Timestep 5
    p_oSimManager->RunSim(1);
    fExpectedPrecip = 1415.79729;
    fExpectedTemp = 7.073638083;
    fExpectedWaterDeficit = 256.2652437;
    fActualPrecip = p_oPlot->GetMeanAnnualPrecip();
    fActualTemp = p_oPlot->GetMeanAnnualTemp();
    fActualWaterDeficit = p_oPlot->GetWaterDeficit();
    EXPECT_LT(fabs(fExpectedPrecip - fActualPrecip), 0.000001);
    EXPECT_LT(fabs(fExpectedTemp - fActualTemp), 0.000001);
    EXPECT_LT(fabs(fExpectedWaterDeficit - fActualWaterDeficit), 0.001);

    p_oClimateGrid->GetValueOfCell(0, 0, iTempCode, &fActualTemp);
    p_oClimateGrid->GetValueOfCell(0, 0, iPrecipCode, &fActualPrecip);
    p_oClimateGrid->GetValueOfCell(0, 0, iWDCode, &fActualWaterDeficit);
    EXPECT_LT(fabs(fExpectedPrecip - fActualPrecip), 0.000001);
    EXPECT_LT(fabs(fExpectedTemp - fActualTemp), 0.000001);
    EXPECT_LT(fabs(fExpectedWaterDeficit - fActualWaterDeficit), 0.001);

    delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

////////////////////////////////////////////////////////////////////////////
// TestErrorProcessing()
////////////////////////////////////////////////////////////////////////////
TEST(SeasonalWaterDeficit, TestErrorProcessing) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try
  {
    p_oSimManager->ReadFile(WriteSeasonalWaterDeficitXMLErrorFile1());
    FAIL() << "TestNCIMasterMortality error processing didn't catch error for WriteSeasonalWaterDeficitXMLErrorFile1.";
  }
  catch (modelErr& err)
  {
    if (err.sFunction.compare("clSeasonalWaterDeficit::GetData") != 0)
    {
      FAIL() << "TestSeasonalWaterDeficit error processing caught wrong error for WriteSeasonalWaterDeficitXMLErrorFile1.";
    }
    ;
  }

  try
  {
    p_oSimManager->ReadFile(WriteSeasonalWaterDeficitXMLErrorFile2());
    FAIL() << "TestNCIMasterMortality error processing didn't catch error for WriteSeasonalWaterDeficitXMLErrorFile2.";
  }
  catch (modelErr& err)
  {
    if (err.sFunction.compare("clSeasonalWaterDeficit::GetData") != 0)
    {
      FAIL() << "TestSeasonalWaterDeficit error processing caught wrong error for WriteSeasonalWaterDeficitXMLErrorFile2.";
    }
    ;
  }

  delete p_oSimManager;
}



/////////////////////////////////////////////////////////////////////////////
// WriteSeasonalWaterDeficitXMLFile1()
/////////////////////////////////////////////////////////////////////////////
const char* WriteSeasonalWaterDeficitXMLFile1()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  std::fstream oOut;
  oOut.open( cFileString, ios::out | ios::trunc );

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06010101\">"
       << "<plot>"
       << "<timesteps>10</timesteps>"
       << "<yearsPerTimestep>1</yearsPerTimestep>"
       << "<randomSeed>0</randomSeed>"
       << "<plot_lenX>100</plot_lenX>"
       << "<plot_lenY>100</plot_lenY>"
       << "<plot_precip_mm_yr>1383.79729</plot_precip_mm_yr>"
       << "<plot_temp_C>6.27363808</plot_temp_C>"
       << "<plot_latitude>55.37</plot_latitude>"
       << "<plot_seasonal_precipitation>600</plot_seasonal_precipitation>"
       << "<plot_water_deficit>500</plot_water_deficit>"
       << "</plot>";

  oOut << "<trees>"
       << "<tr_speciesList>"
       << "<tr_species speciesName=\"Species_1\"/>"
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
       << "<tr_slopeOfAsymHeight>"
       << "<tr_soahVal species=\"Species_1\">0.0299</tr_soahVal>"
       << "</tr_slopeOfAsymHeight>"
       << "<tr_canopyHeight>"
       << "<tr_chVal species=\"Species_1\">39.48</tr_chVal>"
       << "</tr_canopyHeight>"
       << "<tr_stdAsympCrownRad>"
       << "<tr_sacrVal species=\"Species_1\">0.0549</tr_sacrVal>"
       << "</tr_stdAsympCrownRad>"
       << "<tr_stdCrownRadExp>"
       << "<tr_screVal species=\"Species_1\">1.0</tr_screVal>"
       << "</tr_stdCrownRadExp>"
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
       << "</allometry>";

  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>TemperatureClimateChange</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>PrecipitationClimateChange</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>2</listPosition>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>SeasonalWaterDeficit</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>3</listPosition>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>StateReporter</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>4</listPosition>"
       << "</behavior>"
       << "</behaviorList>"
       << "<ClimateChange2>"
       << "<sc_climateChangePrecipB>2</sc_climateChangePrecipB>"
       << "<sc_climateChangePrecipC>2</sc_climateChangePrecipC>"
       << "<sc_climateChangeMinPrecip>0</sc_climateChangeMinPrecip>"
       << "<sc_climateChangeMaxPrecip>2000</sc_climateChangeMaxPrecip>"
       << "<sc_climateChangeOtherPrecip>0</sc_climateChangeOtherPrecip>"
       << "</ClimateChange2>"
       << "<ClimateChange1>"
       << "<sc_climateChangeTempB>0.2</sc_climateChangeTempB>"
       << "<sc_climateChangeTempC>1</sc_climateChangeTempC>"
       << "<sc_climateChangeMinTemp>0</sc_climateChangeMinTemp>"
       << "<sc_climateChangeMaxTemp>20</sc_climateChangeMaxTemp>"
       << "</ClimateChange1>"
       << "<SeasonalWaterDeficit3>"
       << "<sc_wdJanPptProp>0.070974839</sc_wdJanPptProp>"
       << "<sc_wdFebPptProp>0.054794073</sc_wdFebPptProp>"
       << "<sc_wdMarPptProp>0.061593711</sc_wdMarPptProp>"
       << "<sc_wdAprPptProp>0.079008971</sc_wdAprPptProp>"
       << "<sc_wdMayPptProp>0.086810403</sc_wdMayPptProp>"
       << "<sc_wdJunPptProp>0.087226865</sc_wdJunPptProp>"
       << "<sc_wdJulPptProp>0.088887802</sc_wdJulPptProp>"
       << "<sc_wdAugPptProp>0.082232203</sc_wdAugPptProp>"
       << "<sc_wdSepPptProp>0.085111165</sc_wdSepPptProp>"
       << "<sc_wdOctPptProp>0.123076914</sc_wdOctPptProp>"
       << "<sc_wdNovPptProp>0.090123894</sc_wdNovPptProp>"
       << "<sc_wdDecPptProp>0.090159159</sc_wdDecPptProp>"

       << "<sc_wdJanRad>7468.475</sc_wdJanRad>"
       << "<sc_wdFebRad>10353.32</sc_wdFebRad>"
       << "<sc_wdMarRad>17453.07</sc_wdMarRad>"
       << "<sc_wdAprRad>22721.85</sc_wdAprRad>"
       << "<sc_wdMayRad>27901.37</sc_wdMayRad>"
       << "<sc_wdJunRad>28677.54</sc_wdJunRad>"
       << "<sc_wdJulRad>28764.65</sc_wdJulRad>"
       << "<sc_wdAugRad>25075.4</sc_wdAugRad>"
       << "<sc_wdSepRad>19259.27</sc_wdSepRad>"
       << "<sc_wdOctRad>12609.6</sc_wdOctRad>"
       << "<sc_wdNovRad>7988.013</sc_wdNovRad>"
       << "<sc_wdDecRad>6307.151</sc_wdDecRad>"

       << "<sc_wdJanTempRatio>-1.284748003</sc_wdJanTempRatio>"
       << "<sc_wdFebTempRatio>-1.212893683</sc_wdFebTempRatio>"
       << "<sc_wdMarTempRatio>-0.365839082</sc_wdMarTempRatio>"
       << "<sc_wdAprTempRatio>0.83247295</sc_wdAprTempRatio>"
       << "<sc_wdMayTempRatio>1.812082535</sc_wdMayTempRatio>"
       << "<sc_wdJunTempRatio>2.727519467</sc_wdJunTempRatio>"
       << "<sc_wdJulTempRatio>3.113137822</sc_wdJulTempRatio>"
       << "<sc_wdAugTempRatio>3.018141906</sc_wdAugTempRatio>"
       << "<sc_wdSepTempRatio>2.43367083</sc_wdSepTempRatio>"
       << "<sc_wdOctTempRatio>1.263996726</sc_wdOctTempRatio>"
       << "<sc_wdNovTempRatio>0.396456724</sc_wdNovTempRatio>"
       << "<sc_wdDecTempRatio>-0.73399819</sc_wdDecTempRatio>"

       << "<sc_wdAWS>60.9</sc_wdAWS>"
       << "</SeasonalWaterDeficit3>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteSeasonalWaterDeficitXMLErrorFile1()
/////////////////////////////////////////////////////////////////////////////
const char* WriteSeasonalWaterDeficitXMLErrorFile1()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  std::fstream oOut;
  oOut.open( cFileString, ios::out | ios::trunc );

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06010101\">"
       << "<plot>"
       << "<timesteps>10</timesteps>"
       << "<yearsPerTimestep>1</yearsPerTimestep>"
       << "<randomSeed>0</randomSeed>"
       << "<plot_lenX>100</plot_lenX>"
       << "<plot_lenY>100</plot_lenY>"
       << "<plot_precip_mm_yr>1383.79729</plot_precip_mm_yr>"
       << "<plot_temp_C>6.27363808</plot_temp_C>"
       << "<plot_latitude>55.37</plot_latitude>"
       << "<plot_seasonal_precipitation>600</plot_seasonal_precipitation>"
       << "<plot_water_deficit>500</plot_water_deficit>"
       << "</plot>";

  oOut << "<trees>"
       << "<tr_speciesList>"
       << "<tr_species speciesName=\"Species_1\"/>"
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
       << "<tr_slopeOfAsymHeight>"
       << "<tr_soahVal species=\"Species_1\">0.0299</tr_soahVal>"
       << "</tr_slopeOfAsymHeight>"
       << "<tr_canopyHeight>"
       << "<tr_chVal species=\"Species_1\">39.48</tr_chVal>"
       << "</tr_canopyHeight>"
       << "<tr_stdAsympCrownRad>"
       << "<tr_sacrVal species=\"Species_1\">0.0549</tr_sacrVal>"
       << "</tr_stdAsympCrownRad>"
       << "<tr_stdCrownRadExp>"
       << "<tr_screVal species=\"Species_1\">1.0</tr_screVal>"
       << "</tr_stdCrownRadExp>"
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
       << "</allometry>";

  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>TemperatureClimateChange</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>PrecipitationClimateChange</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>2</listPosition>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>SeasonalWaterDeficit</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>3</listPosition>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>StateReporter</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>4</listPosition>"
       << "</behavior>"
       << "</behaviorList>"
       << "<ClimateChange2>"
       << "<sc_climateChangePrecipB>2</sc_climateChangePrecipB>"
       << "<sc_climateChangePrecipC>2</sc_climateChangePrecipC>"
       << "<sc_climateChangeMinPrecip>0</sc_climateChangeMinPrecip>"
       << "<sc_climateChangeMaxPrecip>2000</sc_climateChangeMaxPrecip>"
       << "<sc_climateChangeOtherPrecip>0</sc_climateChangeOtherPrecip>"
       << "</ClimateChange2>"
       << "<ClimateChange1>"
       << "<sc_climateChangeTempB>0.2</sc_climateChangeTempB>"
       << "<sc_climateChangeTempC>1</sc_climateChangeTempC>"
       << "<sc_climateChangeMinTemp>0</sc_climateChangeMinTemp>"
       << "<sc_climateChangeMaxTemp>20</sc_climateChangeMaxTemp>"
       << "</ClimateChange1>"
       << "<SeasonalWaterDeficit3>"
       << "<sc_wdJanPptProp>1.070974839</sc_wdJanPptProp>"
       << "<sc_wdFebPptProp>0.054794073</sc_wdFebPptProp>"
       << "<sc_wdMarPptProp>0.061593711</sc_wdMarPptProp>"
       << "<sc_wdAprPptProp>0.079008971</sc_wdAprPptProp>"
       << "<sc_wdMayPptProp>0.086810403</sc_wdMayPptProp>"
       << "<sc_wdJunPptProp>0.087226865</sc_wdJunPptProp>"
       << "<sc_wdJulPptProp>0.088887802</sc_wdJulPptProp>"
       << "<sc_wdAugPptProp>0.082232203</sc_wdAugPptProp>"
       << "<sc_wdSepPptProp>0.085111165</sc_wdSepPptProp>"
       << "<sc_wdOctPptProp>0.123076914</sc_wdOctPptProp>"
       << "<sc_wdNovPptProp>0.090123894</sc_wdNovPptProp>"
       << "<sc_wdDecPptProp>0.090159159</sc_wdDecPptProp>"

       << "<sc_wdJanRad>7468.475</sc_wdJanRad>"
       << "<sc_wdFebRad>10353.32</sc_wdFebRad>"
       << "<sc_wdMarRad>17453.07</sc_wdMarRad>"
       << "<sc_wdAprRad>22721.85</sc_wdAprRad>"
       << "<sc_wdMayRad>27901.37</sc_wdMayRad>"
       << "<sc_wdJunRad>28677.54</sc_wdJunRad>"
       << "<sc_wdJulRad>28764.65</sc_wdJulRad>"
       << "<sc_wdAugRad>25075.4</sc_wdAugRad>"
       << "<sc_wdSepRad>19259.27</sc_wdSepRad>"
       << "<sc_wdOctRad>12609.6</sc_wdOctRad>"
       << "<sc_wdNovRad>7988.013</sc_wdNovRad>"
       << "<sc_wdDecRad>6307.151</sc_wdDecRad>"

       << "<sc_wdJanTempRatio>-1.284748003</sc_wdJanTempRatio>"
       << "<sc_wdFebTempRatio>-1.212893683</sc_wdFebTempRatio>"
       << "<sc_wdMarTempRatio>-0.365839082</sc_wdMarTempRatio>"
       << "<sc_wdAprTempRatio>0.83247295</sc_wdAprTempRatio>"
       << "<sc_wdMayTempRatio>1.812082535</sc_wdMayTempRatio>"
       << "<sc_wdJunTempRatio>2.727519467</sc_wdJunTempRatio>"
       << "<sc_wdJulTempRatio>3.113137822</sc_wdJulTempRatio>"
       << "<sc_wdAugTempRatio>3.018141906</sc_wdAugTempRatio>"
       << "<sc_wdSepTempRatio>2.43367083</sc_wdSepTempRatio>"
       << "<sc_wdOctTempRatio>1.263996726</sc_wdOctTempRatio>"
       << "<sc_wdNovTempRatio>0.396456724</sc_wdNovTempRatio>"
       << "<sc_wdDecTempRatio>-0.73399819</sc_wdDecTempRatio>"

       << "<sc_wdAWS>60.9</sc_wdAWS>"
       << "</SeasonalWaterDeficit3>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteSeasonalWaterDeficitXMLErrorFile2()
/////////////////////////////////////////////////////////////////////////////
const char* WriteSeasonalWaterDeficitXMLErrorFile2()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  std::fstream oOut;
  oOut.open( cFileString, ios::out | ios::trunc );

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06010101\">"
       << "<plot>"
       << "<timesteps>10</timesteps>"
       << "<yearsPerTimestep>1</yearsPerTimestep>"
       << "<randomSeed>0</randomSeed>"
       << "<plot_lenX>100</plot_lenX>"
       << "<plot_lenY>100</plot_lenY>"
       << "<plot_precip_mm_yr>1383.79729</plot_precip_mm_yr>"
       << "<plot_temp_C>6.27363808</plot_temp_C>"
       << "<plot_latitude>55.37</plot_latitude>"
       << "<plot_seasonal_precipitation>600</plot_seasonal_precipitation>"
       << "<plot_water_deficit>500</plot_water_deficit>"
       << "</plot>";

  oOut << "<trees>"
       << "<tr_speciesList>"
       << "<tr_species speciesName=\"Species_1\"/>"
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
       << "<tr_slopeOfAsymHeight>"
       << "<tr_soahVal species=\"Species_1\">0.0299</tr_soahVal>"
       << "</tr_slopeOfAsymHeight>"
       << "<tr_canopyHeight>"
       << "<tr_chVal species=\"Species_1\">39.48</tr_chVal>"
       << "</tr_canopyHeight>"
       << "<tr_stdAsympCrownRad>"
       << "<tr_sacrVal species=\"Species_1\">0.0549</tr_sacrVal>"
       << "</tr_stdAsympCrownRad>"
       << "<tr_stdCrownRadExp>"
       << "<tr_screVal species=\"Species_1\">1.0</tr_screVal>"
       << "</tr_stdCrownRadExp>"
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
       << "</allometry>";

  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>TemperatureClimateChange</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>PrecipitationClimateChange</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>2</listPosition>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>SeasonalWaterDeficit</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>3</listPosition>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>StateReporter</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>4</listPosition>"
       << "</behavior>"
       << "</behaviorList>"
       << "<ClimateChange2>"
       << "<sc_climateChangePrecipB>2</sc_climateChangePrecipB>"
       << "<sc_climateChangePrecipC>2</sc_climateChangePrecipC>"
       << "<sc_climateChangeMinPrecip>0</sc_climateChangeMinPrecip>"
       << "<sc_climateChangeMaxPrecip>2000</sc_climateChangeMaxPrecip>"
       << "<sc_climateChangeOtherPrecip>0</sc_climateChangeOtherPrecip>"
       << "</ClimateChange2>"
       << "<ClimateChange1>"
       << "<sc_climateChangeTempB>0.2</sc_climateChangeTempB>"
       << "<sc_climateChangeTempC>1</sc_climateChangeTempC>"
       << "<sc_climateChangeMinTemp>0</sc_climateChangeMinTemp>"
       << "<sc_climateChangeMaxTemp>20</sc_climateChangeMaxTemp>"
       << "</ClimateChange1>"
       << "<SeasonalWaterDeficit3>"
       << "<sc_wdJanPptProp>0.70974839</sc_wdJanPptProp>"
       << "<sc_wdFebPptProp>0.54794073</sc_wdFebPptProp>"
       << "<sc_wdMarPptProp>0.061593711</sc_wdMarPptProp>"
       << "<sc_wdAprPptProp>0.079008971</sc_wdAprPptProp>"
       << "<sc_wdMayPptProp>0.086810403</sc_wdMayPptProp>"
       << "<sc_wdJunPptProp>0.087226865</sc_wdJunPptProp>"
       << "<sc_wdJulPptProp>0.088887802</sc_wdJulPptProp>"
       << "<sc_wdAugPptProp>0.082232203</sc_wdAugPptProp>"
       << "<sc_wdSepPptProp>0.085111165</sc_wdSepPptProp>"
       << "<sc_wdOctPptProp>0.123076914</sc_wdOctPptProp>"
       << "<sc_wdNovPptProp>0.090123894</sc_wdNovPptProp>"
       << "<sc_wdDecPptProp>0.090159159</sc_wdDecPptProp>"

       << "<sc_wdJanRad>7468.475</sc_wdJanRad>"
       << "<sc_wdFebRad>10353.32</sc_wdFebRad>"
       << "<sc_wdMarRad>17453.07</sc_wdMarRad>"
       << "<sc_wdAprRad>22721.85</sc_wdAprRad>"
       << "<sc_wdMayRad>27901.37</sc_wdMayRad>"
       << "<sc_wdJunRad>28677.54</sc_wdJunRad>"
       << "<sc_wdJulRad>28764.65</sc_wdJulRad>"
       << "<sc_wdAugRad>25075.4</sc_wdAugRad>"
       << "<sc_wdSepRad>19259.27</sc_wdSepRad>"
       << "<sc_wdOctRad>12609.6</sc_wdOctRad>"
       << "<sc_wdNovRad>7988.013</sc_wdNovRad>"
       << "<sc_wdDecRad>6307.151</sc_wdDecRad>"

       << "<sc_wdJanTempRatio>-1.284748003</sc_wdJanTempRatio>"
       << "<sc_wdFebTempRatio>-1.212893683</sc_wdFebTempRatio>"
       << "<sc_wdMarTempRatio>-0.365839082</sc_wdMarTempRatio>"
       << "<sc_wdAprTempRatio>0.83247295</sc_wdAprTempRatio>"
       << "<sc_wdMayTempRatio>1.812082535</sc_wdMayTempRatio>"
       << "<sc_wdJunTempRatio>2.727519467</sc_wdJunTempRatio>"
       << "<sc_wdJulTempRatio>3.113137822</sc_wdJulTempRatio>"
       << "<sc_wdAugTempRatio>3.018141906</sc_wdAugTempRatio>"
       << "<sc_wdSepTempRatio>2.43367083</sc_wdSepTempRatio>"
       << "<sc_wdOctTempRatio>1.263996726</sc_wdOctTempRatio>"
       << "<sc_wdNovTempRatio>0.396456724</sc_wdNovTempRatio>"
       << "<sc_wdDecTempRatio>-0.73399819</sc_wdDecTempRatio>"

       << "<sc_wdAWS>60.9</sc_wdAWS>"
       << "</SeasonalWaterDeficit3>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}
