//---------------------------------------------------------------------------
// TestClimateImporter.cpp
//---------------------------------------------------------------------------
#include "TestClimateImporter.h"
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
TEST(ClimateImporter, TestNormalProcessingRun1) {

  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    clPlot *p_oPlot;
    clGrid *p_oClimateGrid;
    float fActualTemp, fExpectedTemp, fActualPrecip, fExpectedPrecip,
          fActualWaterDeficit, fExpectedWaterDeficit,
		  fActualSeasonal, fExpectedSeasonal;
    int iTempCode, iPrecipCode, iWDCode, iSeasonalCode;

    //Feed our file to the sim manager
    p_oSimManager->ReadFile(WriteClimateImporterXMLFile1());
    p_oPlot = p_oSimManager->GetPlotObject();
    p_oClimateGrid = p_oSimManager->GetGridObject("State Variables");
    iTempCode = p_oClimateGrid->GetFloatDataCode("Temp.C");
    iPrecipCode = p_oClimateGrid->GetFloatDataCode("Precip.mm");
    iWDCode = p_oClimateGrid->GetFloatDataCode("WaterDeficit");
    iSeasonalCode = p_oClimateGrid->GetFloatDataCode("SeasonalPrecip");

    //Initial conditions
    fExpectedPrecip = 1630.33;
    fExpectedTemp = 6.855;
    fExpectedWaterDeficit = 91.08509587;
    fExpectedSeasonal = 881.900839;
    fActualPrecip = p_oPlot->GetMeanAnnualPrecip();
    fActualTemp = p_oPlot->GetMeanAnnualTemp();
    fActualWaterDeficit = p_oPlot->GetWaterDeficit();
    fActualSeasonal = p_oPlot->GetSeasonalPrecipitation();
    EXPECT_LT(fabs(fExpectedPrecip - fActualPrecip), 0.000001);
    EXPECT_LT(fabs(fExpectedTemp - fActualTemp), 0.000001);
    EXPECT_LT(fabs(fExpectedWaterDeficit - fActualWaterDeficit), 0.001);
    EXPECT_LT(fabs(fExpectedSeasonal - fActualSeasonal), 0.001);

    p_oClimateGrid->GetValueOfCell(0, 0, iTempCode, &fActualTemp);
    p_oClimateGrid->GetValueOfCell(0, 0, iPrecipCode, &fActualPrecip);
    p_oClimateGrid->GetValueOfCell(0, 0, iWDCode, &fActualWaterDeficit);
    p_oClimateGrid->GetValueOfCell(0, 0, iSeasonalCode, &fActualSeasonal);
    EXPECT_LT(fabs(fExpectedPrecip - fActualPrecip), 0.000001);
    EXPECT_LT(fabs(fExpectedTemp - fActualTemp), 0.000001);
    EXPECT_LT(fabs(fExpectedWaterDeficit - fActualWaterDeficit), 0.001);
    EXPECT_LT(fabs(fExpectedSeasonal - fActualSeasonal), 0.001);

    //Timestep 1
    p_oSimManager->RunSim(1);
    fExpectedPrecip = 1630.33;
    fExpectedTemp = 6.855;
    fExpectedWaterDeficit = 91.08509587;
    fExpectedSeasonal = 881.900839;
    fActualPrecip = p_oPlot->GetMeanAnnualPrecip();
    fActualTemp = p_oPlot->GetMeanAnnualTemp();
    fActualWaterDeficit = p_oPlot->GetWaterDeficit();
    fActualSeasonal = p_oPlot->GetSeasonalPrecipitation();
    EXPECT_LT(fabs(fExpectedPrecip - fActualPrecip), 0.000001);
    EXPECT_LT(fabs(fExpectedTemp - fActualTemp), 0.000001);
    EXPECT_LT(fabs(fExpectedWaterDeficit - fActualWaterDeficit), 0.001);
    EXPECT_LT(fabs(fExpectedSeasonal - fActualSeasonal), 0.001);

    EXPECT_LT(fabs(0 - p_oPlot->GetLTMAnnualPrecip()), 0.000001);
    EXPECT_LT(fabs(0 - p_oPlot->GetLTMAnnualTemp()), 0.000001);
    EXPECT_LT(fabs(0 - p_oPlot->GetLTMSeasonalPrecipitation()), 0.000001);
    EXPECT_LT(fabs(0 - p_oPlot->GetLTMWaterDeficit()), 0.000001);

    p_oClimateGrid->GetValueOfCell(0, 0, iTempCode, &fActualTemp);
    p_oClimateGrid->GetValueOfCell(0, 0, iPrecipCode, &fActualPrecip);
    p_oClimateGrid->GetValueOfCell(0, 0, iWDCode, &fActualWaterDeficit);
    p_oClimateGrid->GetValueOfCell(0, 0, iSeasonalCode, &fActualSeasonal);
    EXPECT_LT(fabs(fExpectedPrecip - fActualPrecip), 0.000001);
    EXPECT_LT(fabs(fExpectedTemp - fActualTemp), 0.000001);
    EXPECT_LT(fabs(fExpectedWaterDeficit - fActualWaterDeficit), 0.001);
    EXPECT_LT(fabs(fExpectedSeasonal - fActualSeasonal), 0.001);

    //Timestep 2
    p_oSimManager->RunSim(1);
    fExpectedPrecip = 1642.67;
    fExpectedTemp = 6.801666667;
    fExpectedWaterDeficit = 160.0181253;
    fExpectedSeasonal = 859.9102243;
    fActualPrecip = p_oPlot->GetMeanAnnualPrecip();
    fActualTemp = p_oPlot->GetMeanAnnualTemp();
    fActualWaterDeficit = p_oPlot->GetWaterDeficit();
    fActualSeasonal = p_oPlot->GetSeasonalPrecipitation();
    EXPECT_LT(fabs(fExpectedPrecip - fActualPrecip), 0.000001);
    EXPECT_LT(fabs(fExpectedTemp - fActualTemp), 0.000001);
    EXPECT_LT(fabs(fExpectedWaterDeficit - fActualWaterDeficit), 0.001);
    EXPECT_LT(fabs(fExpectedSeasonal - fActualSeasonal), 0.001);

    EXPECT_LT(fabs(0 - p_oPlot->GetLTMAnnualPrecip()), 0.000001);
    EXPECT_LT(fabs(0 - p_oPlot->GetLTMAnnualTemp()), 0.000001);
    EXPECT_LT(fabs(0 - p_oPlot->GetLTMSeasonalPrecipitation()), 0.000001);
    EXPECT_LT(fabs(0 - p_oPlot->GetLTMWaterDeficit()), 0.000001);

    p_oClimateGrid->GetValueOfCell(0, 0, iTempCode, &fActualTemp);
    p_oClimateGrid->GetValueOfCell(0, 0, iPrecipCode, &fActualPrecip);
    p_oClimateGrid->GetValueOfCell(0, 0, iWDCode, &fActualWaterDeficit);
    p_oClimateGrid->GetValueOfCell(0, 0, iSeasonalCode, &fActualSeasonal);
    EXPECT_LT(fabs(fExpectedPrecip - fActualPrecip), 0.000001);
    EXPECT_LT(fabs(fExpectedTemp - fActualTemp), 0.000001);
    EXPECT_LT(fabs(fExpectedWaterDeficit - fActualWaterDeficit), 0.001);
    EXPECT_LT(fabs(fExpectedSeasonal - fActualSeasonal), 0.001);

    //Timestep 3
    p_oSimManager->RunSim(1);
    fExpectedPrecip = 1892.37;
    fExpectedTemp = 6.618333333;
    fExpectedWaterDeficit = 11.9990999;
    fExpectedSeasonal = 989.3014842;
    fActualPrecip = p_oPlot->GetMeanAnnualPrecip();
    fActualTemp = p_oPlot->GetMeanAnnualTemp();
    fActualWaterDeficit = p_oPlot->GetWaterDeficit();
    fActualSeasonal = p_oPlot->GetSeasonalPrecipitation();
    EXPECT_LT(fabs(fExpectedPrecip - fActualPrecip), 0.000001);
    EXPECT_LT(fabs(fExpectedTemp - fActualTemp), 0.000001);
    EXPECT_LT(fabs(fExpectedWaterDeficit - fActualWaterDeficit), 0.001);
    EXPECT_LT(fabs(fExpectedSeasonal - fActualSeasonal), 0.001);

    EXPECT_LT(fabs(0 - p_oPlot->GetLTMAnnualPrecip()), 0.000001);
    EXPECT_LT(fabs(0 - p_oPlot->GetLTMAnnualTemp()), 0.000001);
    EXPECT_LT(fabs(0 - p_oPlot->GetLTMSeasonalPrecipitation()), 0.000001);
    EXPECT_LT(fabs(0 - p_oPlot->GetLTMWaterDeficit()), 0.000001);

    p_oClimateGrid->GetValueOfCell(0, 0, iTempCode, &fActualTemp);
    p_oClimateGrid->GetValueOfCell(0, 0, iPrecipCode, &fActualPrecip);
    p_oClimateGrid->GetValueOfCell(0, 0, iWDCode, &fActualWaterDeficit);
    p_oClimateGrid->GetValueOfCell(0, 0, iSeasonalCode, &fActualSeasonal);
    EXPECT_LT(fabs(fExpectedPrecip - fActualPrecip), 0.000001);
    EXPECT_LT(fabs(fExpectedTemp - fActualTemp), 0.000001);
    EXPECT_LT(fabs(fExpectedWaterDeficit - fActualWaterDeficit), 0.001);
    EXPECT_LT(fabs(fExpectedSeasonal - fActualSeasonal), 0.001);

    //Timestep 4
    p_oSimManager->RunSim(1);
    fExpectedPrecip = 1722.77;
    fExpectedTemp = 7.395;
    fExpectedWaterDeficit = 130.4596051;
    fExpectedSeasonal = 946.4096629;
    fActualPrecip = p_oPlot->GetMeanAnnualPrecip();
    fActualTemp = p_oPlot->GetMeanAnnualTemp();
    fActualWaterDeficit = p_oPlot->GetWaterDeficit();
    fActualSeasonal = p_oPlot->GetSeasonalPrecipitation();
    EXPECT_LT(fabs(fExpectedPrecip - fActualPrecip), 0.000001);
    EXPECT_LT(fabs(fExpectedTemp - fActualTemp), 0.000001);
    EXPECT_LT(fabs(fExpectedWaterDeficit - fActualWaterDeficit), 0.001);
    EXPECT_LT(fabs(fExpectedSeasonal - fActualSeasonal), 0.001);

    EXPECT_LT(fabs(0 - p_oPlot->GetLTMAnnualPrecip()), 0.000001);
    EXPECT_LT(fabs(0 - p_oPlot->GetLTMAnnualTemp()), 0.000001);
    EXPECT_LT(fabs(0 - p_oPlot->GetLTMSeasonalPrecipitation()), 0.000001);
    EXPECT_LT(fabs(0 - p_oPlot->GetLTMWaterDeficit()), 0.000001);

    p_oClimateGrid->GetValueOfCell(0, 0, iTempCode, &fActualTemp);
    p_oClimateGrid->GetValueOfCell(0, 0, iPrecipCode, &fActualPrecip);
    p_oClimateGrid->GetValueOfCell(0, 0, iWDCode, &fActualWaterDeficit);
    p_oClimateGrid->GetValueOfCell(0, 0, iSeasonalCode, &fActualSeasonal);
    EXPECT_LT(fabs(fExpectedPrecip - fActualPrecip), 0.000001);
    EXPECT_LT(fabs(fExpectedTemp - fActualTemp), 0.000001);
    EXPECT_LT(fabs(fExpectedWaterDeficit - fActualWaterDeficit), 0.001);
    EXPECT_LT(fabs(fExpectedSeasonal - fActualSeasonal), 0.001);

    //Timestep 5
    p_oSimManager->RunSim(1);
    fExpectedPrecip = 1527.74;
    fExpectedTemp = 7.99;
    fExpectedWaterDeficit = 129.3160883;
    fExpectedSeasonal = 902.2940183;
    fActualPrecip = p_oPlot->GetMeanAnnualPrecip();
    fActualTemp = p_oPlot->GetMeanAnnualTemp();
    fActualWaterDeficit = p_oPlot->GetWaterDeficit();
    fActualSeasonal = p_oPlot->GetSeasonalPrecipitation();
    EXPECT_LT(fabs(fExpectedPrecip - fActualPrecip), 0.000001);
    EXPECT_LT(fabs(fExpectedTemp - fActualTemp), 0.000001);
    EXPECT_LT(fabs(fExpectedWaterDeficit - fActualWaterDeficit), 0.001);
    EXPECT_LT(fabs(fExpectedSeasonal - fActualSeasonal), 0.001);

    EXPECT_LT(fabs(0 - p_oPlot->GetLTMAnnualPrecip()), 0.000001);
    EXPECT_LT(fabs(0 - p_oPlot->GetLTMAnnualTemp()), 0.000001);
    EXPECT_LT(fabs(0 - p_oPlot->GetLTMSeasonalPrecipitation()), 0.000001);
    EXPECT_LT(fabs(0 - p_oPlot->GetLTMWaterDeficit()), 0.000001);

    p_oClimateGrid->GetValueOfCell(0, 0, iTempCode, &fActualTemp);
    p_oClimateGrid->GetValueOfCell(0, 0, iPrecipCode, &fActualPrecip);
    p_oClimateGrid->GetValueOfCell(0, 0, iWDCode, &fActualWaterDeficit);
    p_oClimateGrid->GetValueOfCell(0, 0, iSeasonalCode, &fActualSeasonal);
    EXPECT_LT(fabs(fExpectedPrecip - fActualPrecip), 0.000001);
    EXPECT_LT(fabs(fExpectedTemp - fActualTemp), 0.000001);
    EXPECT_LT(fabs(fExpectedWaterDeficit - fActualWaterDeficit), 0.001);
    EXPECT_LT(fabs(fExpectedSeasonal - fActualSeasonal), 0.001);

    //Timestep 6
    p_oSimManager->RunSim(1);
    fExpectedPrecip = 1628.82;
    fExpectedTemp = 7.334166667;
    fExpectedWaterDeficit = 152.2639151;
    fExpectedSeasonal = 862.5541861;
    fActualPrecip = p_oPlot->GetMeanAnnualPrecip();
    fActualTemp = p_oPlot->GetMeanAnnualTemp();
    fActualWaterDeficit = p_oPlot->GetWaterDeficit();
    fActualSeasonal = p_oPlot->GetSeasonalPrecipitation();
    EXPECT_LT(fabs(fExpectedPrecip - fActualPrecip), 0.000001);
    EXPECT_LT(fabs(fExpectedTemp - fActualTemp), 0.000001);
    EXPECT_LT(fabs(fExpectedWaterDeficit - fActualWaterDeficit), 0.001);
    EXPECT_LT(fabs(fExpectedSeasonal - fActualSeasonal), 0.001);

    EXPECT_LT(fabs(0 - p_oPlot->GetLTMAnnualPrecip()), 0.000001);
    EXPECT_LT(fabs(0 - p_oPlot->GetLTMAnnualTemp()), 0.000001);
    EXPECT_LT(fabs(0 - p_oPlot->GetLTMSeasonalPrecipitation()), 0.000001);
    EXPECT_LT(fabs(0 - p_oPlot->GetLTMWaterDeficit()), 0.000001);

    p_oClimateGrid->GetValueOfCell(0, 0, iTempCode, &fActualTemp);
    p_oClimateGrid->GetValueOfCell(0, 0, iPrecipCode, &fActualPrecip);
    p_oClimateGrid->GetValueOfCell(0, 0, iWDCode, &fActualWaterDeficit);
    p_oClimateGrid->GetValueOfCell(0, 0, iSeasonalCode, &fActualSeasonal);
    EXPECT_LT(fabs(fExpectedPrecip - fActualPrecip), 0.000001);
    EXPECT_LT(fabs(fExpectedTemp - fActualTemp), 0.000001);
    EXPECT_LT(fabs(fExpectedWaterDeficit - fActualWaterDeficit), 0.001);
    EXPECT_LT(fabs(fExpectedSeasonal - fActualSeasonal), 0.001);

    delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}



/////////////////////////////////////////////////////////////////////////////
// TestNormalProcessingRun2()
// Tests normal processing for a 1-year timestep.
// WriteSeasonalWaterDeficitXMLFile2() does setup.
/////////////////////////////////////////////////////////////////////////////
TEST(ClimateImporter, TestNormalProcessingRun2) {

  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    clPlot *p_oPlot;
    clGrid *p_oClimateGrid;
    float fActualTemp, fExpectedTemp, fActualPrecip, fExpectedPrecip,
          fActualWaterDeficit, fExpectedWaterDeficit,
      fActualSeasonal, fExpectedSeasonal;
    int iTempCode, iPrecipCode, iWDCode, iSeasonalCode;

    //Feed our file to the sim manager
    p_oSimManager->ReadFile(WriteClimateImporterXMLFile2());
    p_oPlot = p_oSimManager->GetPlotObject();
    p_oClimateGrid = p_oSimManager->GetGridObject("State Variables");
    iTempCode = p_oClimateGrid->GetFloatDataCode("Temp.C");
    iPrecipCode = p_oClimateGrid->GetFloatDataCode("Precip.mm");
    iWDCode = p_oClimateGrid->GetFloatDataCode("WaterDeficit");
    iSeasonalCode = p_oClimateGrid->GetFloatDataCode("SeasonalPrecip");

    //-----------------------------------------------------------------------//
    //Initial conditions
    //-----------------------------------------------------------------------//
    fExpectedPrecip = 1651.56;
    fExpectedTemp = 7.361666667;
    fExpectedWaterDeficit = 91.08509587;
    fExpectedSeasonal = 881.900839;
    fActualPrecip = p_oPlot->GetMeanAnnualPrecip();
    fActualTemp = p_oPlot->GetMeanAnnualTemp();
    fActualWaterDeficit = p_oPlot->GetWaterDeficit();
    fActualSeasonal = p_oPlot->GetSeasonalPrecipitation();
    EXPECT_LT(fabs(fExpectedPrecip - fActualPrecip), 0.000001);
    EXPECT_LT(fabs(fExpectedTemp - fActualTemp), 0.000001);
    EXPECT_LT(fabs(fExpectedWaterDeficit - fActualWaterDeficit), 0.001);
    EXPECT_LT(fabs(fExpectedSeasonal - fActualSeasonal), 0.001);

    //----- Grid values -----------------------------------------------------//
    p_oClimateGrid->GetValueOfCell(0, 0, iTempCode, &fActualTemp);
    p_oClimateGrid->GetValueOfCell(0, 0, iPrecipCode, &fActualPrecip);
    p_oClimateGrid->GetValueOfCell(0, 0, iWDCode, &fActualWaterDeficit);
    p_oClimateGrid->GetValueOfCell(0, 0, iSeasonalCode, &fActualSeasonal);

    //----- Long term means -------------------------------------------------//
    fExpectedPrecip = 1745.36;
    fExpectedTemp = 7.553833333;
    fExpectedWaterDeficit = 100.5264293;
    fExpectedSeasonal = 921.4657412;
    fActualPrecip = p_oPlot->GetLTMAnnualPrecip();
    fActualTemp = p_oPlot->GetLTMAnnualTemp();
    fActualWaterDeficit = p_oPlot->GetLTMWaterDeficit();
    fActualSeasonal = p_oPlot->GetLTMSeasonalPrecipitation();
    EXPECT_LT(fabs(fExpectedPrecip - fActualPrecip), 0.000001);
    EXPECT_LT(fabs(fExpectedTemp - fActualTemp), 0.000001);
    EXPECT_LT(fabs(fExpectedWaterDeficit - fActualWaterDeficit), 0.001);
    EXPECT_LT(fabs(fExpectedSeasonal - fActualSeasonal), 0.001);
    //-----------------------------------------------------------------------//




    //-----------------------------------------------------------------------//
    //Timestep 1
    //-----------------------------------------------------------------------//
    p_oSimManager->RunSim(1);
    fExpectedPrecip = 1651.56;
    fExpectedTemp = 7.361666667;
    fExpectedWaterDeficit = 91.08509587;
    fExpectedSeasonal = 881.900839;
    fActualPrecip = p_oPlot->GetMeanAnnualPrecip();
    fActualTemp = p_oPlot->GetMeanAnnualTemp();
    fActualWaterDeficit = p_oPlot->GetWaterDeficit();
    fActualSeasonal = p_oPlot->GetSeasonalPrecipitation();
    EXPECT_LT(fabs(fExpectedPrecip - fActualPrecip), 0.000001);
    EXPECT_LT(fabs(fExpectedTemp - fActualTemp), 0.000001);
    EXPECT_LT(fabs(fExpectedWaterDeficit - fActualWaterDeficit), 0.001);
    EXPECT_LT(fabs(fExpectedSeasonal - fActualSeasonal), 0.001);

    //----- Grid values -----------------------------------------------------//
    p_oClimateGrid->GetValueOfCell(0, 0, iTempCode, &fActualTemp);
    p_oClimateGrid->GetValueOfCell(0, 0, iPrecipCode, &fActualPrecip);
    p_oClimateGrid->GetValueOfCell(0, 0, iWDCode, &fActualWaterDeficit);
    p_oClimateGrid->GetValueOfCell(0, 0, iSeasonalCode, &fActualSeasonal);
    EXPECT_LT(fabs(fExpectedPrecip - fActualPrecip), 0.000001);
    EXPECT_LT(fabs(fExpectedTemp - fActualTemp), 0.000001);
    EXPECT_LT(fabs(fExpectedWaterDeficit - fActualWaterDeficit), 0.001);
    EXPECT_LT(fabs(fExpectedSeasonal - fActualSeasonal), 0.001);

    //----- Long term means -------------------------------------------------//
    fExpectedPrecip = 1745.36;
    fExpectedTemp = 7.553833333;
    fExpectedWaterDeficit = 100.5264293;
    fExpectedSeasonal = 921.4657412;
    fActualPrecip = p_oPlot->GetLTMAnnualPrecip();
    fActualTemp = p_oPlot->GetLTMAnnualTemp();
    fActualWaterDeficit = p_oPlot->GetLTMWaterDeficit();
    fActualSeasonal = p_oPlot->GetLTMSeasonalPrecipitation();
    EXPECT_LT(fabs(fExpectedPrecip - fActualPrecip), 0.000001);
    EXPECT_LT(fabs(fExpectedTemp - fActualTemp), 0.000001);
    EXPECT_LT(fabs(fExpectedWaterDeficit - fActualWaterDeficit), 0.001);
    EXPECT_LT(fabs(fExpectedSeasonal - fActualSeasonal), 0.001);
    //-----------------------------------------------------------------------//


    //-----------------------------------------------------------------------//
    //Timestep 2
    //-----------------------------------------------------------------------//
    p_oSimManager->RunSim(1);
    fExpectedPrecip = 1521.78;
    fExpectedTemp = 6.551666667;
    fExpectedWaterDeficit = 160.0181253;
    fExpectedSeasonal = 859.9102243;
    fActualPrecip = p_oPlot->GetMeanAnnualPrecip();
    fActualTemp = p_oPlot->GetMeanAnnualTemp();
    fActualWaterDeficit = p_oPlot->GetWaterDeficit();
    fActualSeasonal = p_oPlot->GetSeasonalPrecipitation();
    EXPECT_LT(fabs(fExpectedPrecip - fActualPrecip), 0.000001);
    EXPECT_LT(fabs(fExpectedTemp - fActualTemp), 0.000001);
    EXPECT_LT(fabs(fExpectedWaterDeficit - fActualWaterDeficit), 0.001);
    EXPECT_LT(fabs(fExpectedSeasonal - fActualSeasonal), 0.001);

    //----- Grid values -----------------------------------------------------//
    p_oClimateGrid->GetValueOfCell(0, 0, iTempCode, &fActualTemp);
    p_oClimateGrid->GetValueOfCell(0, 0, iPrecipCode, &fActualPrecip);
    p_oClimateGrid->GetValueOfCell(0, 0, iWDCode, &fActualWaterDeficit);
    p_oClimateGrid->GetValueOfCell(0, 0, iSeasonalCode, &fActualSeasonal);
    EXPECT_LT(fabs(fExpectedPrecip - fActualPrecip), 0.000001);
    EXPECT_LT(fabs(fExpectedTemp - fActualTemp), 0.000001);
    EXPECT_LT(fabs(fExpectedWaterDeficit - fActualWaterDeficit), 0.001);
    EXPECT_LT(fabs(fExpectedSeasonal - fActualSeasonal), 0.001);

    //----- Long term means -------------------------------------------------//
    fExpectedPrecip = 1634.906;
    fExpectedTemp = 7.5565;
    fExpectedWaterDeficit = 132.5300544;
    fExpectedSeasonal = 891.2020291;
    fActualPrecip = p_oPlot->GetLTMAnnualPrecip();
    fActualTemp = p_oPlot->GetLTMAnnualTemp();
    fActualWaterDeficit = p_oPlot->GetLTMWaterDeficit();
    fActualSeasonal = p_oPlot->GetLTMSeasonalPrecipitation();
    EXPECT_LT(fabs(fExpectedPrecip - fActualPrecip), 0.000001);
    EXPECT_LT(fabs(fExpectedTemp - fActualTemp), 0.000001);
    EXPECT_LT(fabs(fExpectedWaterDeficit - fActualWaterDeficit), 0.001);
    EXPECT_LT(fabs(fExpectedSeasonal - fActualSeasonal), 0.001);
    //-----------------------------------------------------------------------//


    //-----------------------------------------------------------------------//
    //Timestep 3
    //-----------------------------------------------------------------------//
    p_oSimManager->RunSim(1);
    fExpectedPrecip = 1958.15;
    fExpectedTemp = 6.555;
    fExpectedWaterDeficit = 11.9990999;
    fExpectedSeasonal = 989.3014842;
    fActualPrecip = p_oPlot->GetMeanAnnualPrecip();
    fActualTemp = p_oPlot->GetMeanAnnualTemp();
    fActualWaterDeficit = p_oPlot->GetWaterDeficit();
    fActualSeasonal = p_oPlot->GetSeasonalPrecipitation();
    EXPECT_LT(fabs(fExpectedPrecip - fActualPrecip), 0.000001);
    EXPECT_LT(fabs(fExpectedTemp - fActualTemp), 0.000001);
    EXPECT_LT(fabs(fExpectedWaterDeficit - fActualWaterDeficit), 0.001);
    EXPECT_LT(fabs(fExpectedSeasonal - fActualSeasonal), 0.001);

    //----- Grid values -----------------------------------------------------//
    p_oClimateGrid->GetValueOfCell(0, 0, iTempCode, &fActualTemp);
    p_oClimateGrid->GetValueOfCell(0, 0, iPrecipCode, &fActualPrecip);
    p_oClimateGrid->GetValueOfCell(0, 0, iWDCode, &fActualWaterDeficit);
    p_oClimateGrid->GetValueOfCell(0, 0, iSeasonalCode, &fActualSeasonal);
    EXPECT_LT(fabs(fExpectedPrecip - fActualPrecip), 0.000001);
    EXPECT_LT(fabs(fExpectedTemp - fActualTemp), 0.000001);
    EXPECT_LT(fabs(fExpectedWaterDeficit - fActualWaterDeficit), 0.001);
    EXPECT_LT(fabs(fExpectedSeasonal - fActualSeasonal), 0.001);

    //----- Long term means -------------------------------------------------//
    fExpectedPrecip = 1713.402;
    fExpectedTemp = 7.424833333;
    fExpectedWaterDeficit = 108.2844741;
    fExpectedSeasonal = 912.0563317;
    fActualPrecip = p_oPlot->GetLTMAnnualPrecip();
    fActualTemp = p_oPlot->GetLTMAnnualTemp();
    fActualWaterDeficit = p_oPlot->GetLTMWaterDeficit();
    fActualSeasonal = p_oPlot->GetLTMSeasonalPrecipitation();
    EXPECT_LT(fabs(fExpectedPrecip - fActualPrecip), 0.000001);
    EXPECT_LT(fabs(fExpectedTemp - fActualTemp), 0.000001);
    EXPECT_LT(fabs(fExpectedWaterDeficit - fActualWaterDeficit), 0.001);
    EXPECT_LT(fabs(fExpectedSeasonal - fActualSeasonal), 0.001);
    //-----------------------------------------------------------------------//


    //-----------------------------------------------------------------------//
    //Timestep 4
    //-----------------------------------------------------------------------//
    p_oSimManager->RunSim(1);
    fExpectedPrecip = 1677.63;
    fExpectedTemp = 6.9575;
    fExpectedWaterDeficit = 130.4596051;
    fExpectedSeasonal = 946.4096629;
    fActualPrecip = p_oPlot->GetMeanAnnualPrecip();
    fActualTemp = p_oPlot->GetMeanAnnualTemp();
    fActualWaterDeficit = p_oPlot->GetWaterDeficit();
    fActualSeasonal = p_oPlot->GetSeasonalPrecipitation();
    EXPECT_LT(fabs(fExpectedPrecip - fActualPrecip), 0.000001);
    EXPECT_LT(fabs(fExpectedTemp - fActualTemp), 0.000001);
    EXPECT_LT(fabs(fExpectedWaterDeficit - fActualWaterDeficit), 0.001);
    EXPECT_LT(fabs(fExpectedSeasonal - fActualSeasonal), 0.001);

    //----- Grid values -----------------------------------------------------//
    p_oClimateGrid->GetValueOfCell(0, 0, iTempCode, &fActualTemp);
    p_oClimateGrid->GetValueOfCell(0, 0, iPrecipCode, &fActualPrecip);
    p_oClimateGrid->GetValueOfCell(0, 0, iWDCode, &fActualWaterDeficit);
    p_oClimateGrid->GetValueOfCell(0, 0, iSeasonalCode, &fActualSeasonal);
    EXPECT_LT(fabs(fExpectedPrecip - fActualPrecip), 0.000001);
    EXPECT_LT(fabs(fExpectedTemp - fActualTemp), 0.000001);
    EXPECT_LT(fabs(fExpectedWaterDeficit - fActualWaterDeficit), 0.001);
    EXPECT_LT(fabs(fExpectedSeasonal - fActualSeasonal), 0.001);

    //----- Long term means -------------------------------------------------//
    fExpectedPrecip = 1680.038;
    fExpectedTemp = 6.7655;
    fExpectedWaterDeficit = 102.847204;
    fExpectedSeasonal = 902.7790948;
    fActualPrecip = p_oPlot->GetLTMAnnualPrecip();
    fActualTemp = p_oPlot->GetLTMAnnualTemp();
    fActualWaterDeficit = p_oPlot->GetLTMWaterDeficit();
    fActualSeasonal = p_oPlot->GetLTMSeasonalPrecipitation();
    EXPECT_LT(fabs(fExpectedPrecip - fActualPrecip), 0.000001);
    EXPECT_LT(fabs(fExpectedTemp - fActualTemp), 0.000001);
    EXPECT_LT(fabs(fExpectedWaterDeficit - fActualWaterDeficit), 0.001);
    EXPECT_LT(fabs(fExpectedSeasonal - fActualSeasonal), 0.001);
    //-----------------------------------------------------------------------//


    //-----------------------------------------------------------------------//
    //Timestep 5
    //-----------------------------------------------------------------------//
    p_oSimManager->RunSim(1);
    fExpectedPrecip = 1594.67;
    fExpectedTemp = 7.813333333;
    fExpectedWaterDeficit = 129.3160883;
    fExpectedSeasonal = 902.2940183;
    fActualPrecip = p_oPlot->GetMeanAnnualPrecip();
    fActualTemp = p_oPlot->GetMeanAnnualTemp();
    fActualWaterDeficit = p_oPlot->GetWaterDeficit();
    fActualSeasonal = p_oPlot->GetSeasonalPrecipitation();
    EXPECT_LT(fabs(fExpectedPrecip - fActualPrecip), 0.000001);
    EXPECT_LT(fabs(fExpectedTemp - fActualTemp), 0.000001);
    EXPECT_LT(fabs(fExpectedWaterDeficit - fActualWaterDeficit), 0.001);
    EXPECT_LT(fabs(fExpectedSeasonal - fActualSeasonal), 0.001);

    //----- Grid values -----------------------------------------------------//
    p_oClimateGrid->GetValueOfCell(0, 0, iTempCode, &fActualTemp);
    p_oClimateGrid->GetValueOfCell(0, 0, iPrecipCode, &fActualPrecip);
    p_oClimateGrid->GetValueOfCell(0, 0, iWDCode, &fActualWaterDeficit);
    p_oClimateGrid->GetValueOfCell(0, 0, iSeasonalCode, &fActualSeasonal);
    EXPECT_LT(fabs(fExpectedPrecip - fActualPrecip), 0.000001);
    EXPECT_LT(fabs(fExpectedTemp - fActualTemp), 0.000001);
    EXPECT_LT(fabs(fExpectedWaterDeficit - fActualWaterDeficit), 0.001);
    EXPECT_LT(fabs(fExpectedSeasonal - fActualSeasonal), 0.001);

    //----- Long term means -------------------------------------------------//
    fExpectedPrecip = 1680.758;
    fExpectedTemp = 7.047833333;
    fExpectedWaterDeficit = 104.5756029;
    fExpectedSeasonal = 915.9632457;
    fActualPrecip = p_oPlot->GetLTMAnnualPrecip();
    fActualTemp = p_oPlot->GetLTMAnnualTemp();
    fActualWaterDeficit = p_oPlot->GetLTMWaterDeficit();
    fActualSeasonal = p_oPlot->GetLTMSeasonalPrecipitation();
    EXPECT_LT(fabs(fExpectedPrecip - fActualPrecip), 0.000001);
    EXPECT_LT(fabs(fExpectedTemp - fActualTemp), 0.000001);
    EXPECT_LT(fabs(fExpectedWaterDeficit - fActualWaterDeficit), 0.001);
    EXPECT_LT(fabs(fExpectedSeasonal - fActualSeasonal), 0.001);
    //-----------------------------------------------------------------------//


    //-----------------------------------------------------------------------//
    //Timestep 6
    //-----------------------------------------------------------------------//
    p_oSimManager->RunSim(1);
    fExpectedPrecip = 1534.99;
    fExpectedTemp = 7.115;
    fExpectedWaterDeficit = 152.2639151;
    fExpectedSeasonal = 862.5541861;
    fActualPrecip = p_oPlot->GetMeanAnnualPrecip();
    fActualTemp = p_oPlot->GetMeanAnnualTemp();
    fActualWaterDeficit = p_oPlot->GetWaterDeficit();
    fActualSeasonal = p_oPlot->GetSeasonalPrecipitation();
    EXPECT_LT(fabs(fExpectedPrecip - fActualPrecip), 0.000001);
    EXPECT_LT(fabs(fExpectedTemp - fActualTemp), 0.000001);
    EXPECT_LT(fabs(fExpectedWaterDeficit - fActualWaterDeficit), 0.001);
    EXPECT_LT(fabs(fExpectedSeasonal - fActualSeasonal), 0.001);

    //----- Grid values -----------------------------------------------------//
    p_oClimateGrid->GetValueOfCell(0, 0, iTempCode, &fActualTemp);
    p_oClimateGrid->GetValueOfCell(0, 0, iPrecipCode, &fActualPrecip);
    p_oClimateGrid->GetValueOfCell(0, 0, iWDCode, &fActualWaterDeficit);
    p_oClimateGrid->GetValueOfCell(0, 0, iSeasonalCode, &fActualSeasonal);
    EXPECT_LT(fabs(fExpectedPrecip - fActualPrecip), 0.000001);
    EXPECT_LT(fabs(fExpectedTemp - fActualTemp), 0.000001);
    EXPECT_LT(fabs(fExpectedWaterDeficit - fActualWaterDeficit), 0.001);
    EXPECT_LT(fabs(fExpectedSeasonal - fActualSeasonal), 0.001);

    //----- Long term means -------------------------------------------------//
    fExpectedPrecip = 1657.444;
    fExpectedTemp = 6.9985;
    fExpectedWaterDeficit = 116.8113667;
    fExpectedSeasonal = 912.0939152;
    fActualPrecip = p_oPlot->GetLTMAnnualPrecip();
    fActualTemp = p_oPlot->GetLTMAnnualTemp();
    fActualWaterDeficit = p_oPlot->GetLTMWaterDeficit();
    fActualSeasonal = p_oPlot->GetLTMSeasonalPrecipitation();
    EXPECT_LT(fabs(fExpectedPrecip - fActualPrecip), 0.000001);
    EXPECT_LT(fabs(fExpectedTemp - fActualTemp), 0.000001);
    EXPECT_LT(fabs(fExpectedWaterDeficit - fActualWaterDeficit), 0.001);
    EXPECT_LT(fabs(fExpectedSeasonal - fActualSeasonal), 0.001);
    //-----------------------------------------------------------------------//

    delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}


/////////////////////////////////////////////////////////////////////////////
// TestNormalProcessingRun3()
// Tests normal processing for a 1-year timestep.
// WriteSeasonalWaterDeficitXMLFile3() does setup.
/////////////////////////////////////////////////////////////////////////////
TEST(ClimateImporter, TestNormalProcessingRun3) {

  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    clPlot *p_oPlot;
    clGrid *p_oClimateGrid;
    float fActualTemp, fExpectedTemp, fActualPrecip, fExpectedPrecip,
          fActualWaterDeficit, fExpectedWaterDeficit,
      fActualSeasonal, fExpectedSeasonal;
    int iTempCode, iPrecipCode, iWDCode, iSeasonalCode;

    //Feed our file to the sim manager
    p_oSimManager->ReadFile(WriteClimateImporterXMLFile3());
    p_oPlot = p_oSimManager->GetPlotObject();
    p_oClimateGrid = p_oSimManager->GetGridObject("State Variables");
    iTempCode = p_oClimateGrid->GetFloatDataCode("Temp.C");
    iPrecipCode = p_oClimateGrid->GetFloatDataCode("Precip.mm");
    iWDCode = p_oClimateGrid->GetFloatDataCode("WaterDeficit");
    iSeasonalCode = p_oClimateGrid->GetFloatDataCode("SeasonalPrecip");

    //-----------------------------------------------------------------------//
    //Initial conditions
    //-----------------------------------------------------------------------//
    fExpectedPrecip = 1630.33;
    fExpectedTemp = 6.855;
    fExpectedWaterDeficit = 91.08509587;
    fExpectedSeasonal = 881.900839;
    fActualPrecip = p_oPlot->GetMeanAnnualPrecip();
    fActualTemp = p_oPlot->GetMeanAnnualTemp();
    fActualWaterDeficit = p_oPlot->GetWaterDeficit();
    fActualSeasonal = p_oPlot->GetSeasonalPrecipitation();
    EXPECT_LT(fabs(fExpectedPrecip - fActualPrecip), 0.000001);
    EXPECT_LT(fabs(fExpectedTemp - fActualTemp), 0.000001);
    EXPECT_LT(fabs(fExpectedWaterDeficit - fActualWaterDeficit), 0.001);
    EXPECT_LT(fabs(fExpectedSeasonal - fActualSeasonal), 0.001);

    //----- Grid values -----------------------------------------------------//
    p_oClimateGrid->GetValueOfCell(0, 0, iTempCode, &fActualTemp);
    p_oClimateGrid->GetValueOfCell(0, 0, iPrecipCode, &fActualPrecip);
    p_oClimateGrid->GetValueOfCell(0, 0, iWDCode, &fActualWaterDeficit);
    p_oClimateGrid->GetValueOfCell(0, 0, iSeasonalCode, &fActualSeasonal);

    //----- Long term means -------------------------------------------------//
    fExpectedPrecip = 1675.6225;
    fExpectedTemp = 7.564583333;
    fExpectedWaterDeficit = 125.6580366;
    fExpectedSeasonal = 899.0249803;
    fActualPrecip = p_oPlot->GetLTMAnnualPrecip();
    fActualTemp = p_oPlot->GetLTMAnnualTemp();
    fActualWaterDeficit = p_oPlot->GetLTMWaterDeficit();
    fActualSeasonal = p_oPlot->GetLTMSeasonalPrecipitation();
    EXPECT_LT(fabs(fExpectedPrecip - fActualPrecip), 0.000001);
    EXPECT_LT(fabs(fExpectedTemp - fActualTemp), 0.000001);
    EXPECT_LT(fabs(fExpectedWaterDeficit - fActualWaterDeficit), 0.001);
    EXPECT_LT(fabs(fExpectedSeasonal - fActualSeasonal), 0.001);
    //-----------------------------------------------------------------------//




    //-----------------------------------------------------------------------//
    //Timestep 1
    //-----------------------------------------------------------------------//
    p_oSimManager->RunSim(1);
    fExpectedPrecip = 1630.33;
    fExpectedTemp = 6.855;
    fExpectedWaterDeficit = 91.08509587;
    fExpectedSeasonal = 881.900839;
    fActualPrecip = p_oPlot->GetMeanAnnualPrecip();
    fActualTemp = p_oPlot->GetMeanAnnualTemp();
    fActualWaterDeficit = p_oPlot->GetWaterDeficit();
    fActualSeasonal = p_oPlot->GetSeasonalPrecipitation();
    EXPECT_LT(fabs(fExpectedPrecip - fActualPrecip), 0.000001);
    EXPECT_LT(fabs(fExpectedTemp - fActualTemp), 0.000001);
    EXPECT_LT(fabs(fExpectedWaterDeficit - fActualWaterDeficit), 0.001);
    EXPECT_LT(fabs(fExpectedSeasonal - fActualSeasonal), 0.001);

    //----- Grid values -----------------------------------------------------//
    p_oClimateGrid->GetValueOfCell(0, 0, iTempCode, &fActualTemp);
    p_oClimateGrid->GetValueOfCell(0, 0, iPrecipCode, &fActualPrecip);
    p_oClimateGrid->GetValueOfCell(0, 0, iWDCode, &fActualWaterDeficit);
    p_oClimateGrid->GetValueOfCell(0, 0, iSeasonalCode, &fActualSeasonal);
    EXPECT_LT(fabs(fExpectedPrecip - fActualPrecip), 0.000001);
    EXPECT_LT(fabs(fExpectedTemp - fActualTemp), 0.000001);
    EXPECT_LT(fabs(fExpectedWaterDeficit - fActualWaterDeficit), 0.001);
    EXPECT_LT(fabs(fExpectedSeasonal - fActualSeasonal), 0.001);

    //----- Long term means -------------------------------------------------//
    fExpectedPrecip = 1675.6225;
    fExpectedTemp = 7.564583333;
    fExpectedWaterDeficit = 125.6580366;
    fExpectedSeasonal = 899.0249803;
    fActualPrecip = p_oPlot->GetLTMAnnualPrecip();
    fActualTemp = p_oPlot->GetLTMAnnualTemp();
    fActualWaterDeficit = p_oPlot->GetLTMWaterDeficit();
    fActualSeasonal = p_oPlot->GetLTMSeasonalPrecipitation();
    EXPECT_LT(fabs(fExpectedPrecip - fActualPrecip), 0.000001);
    EXPECT_LT(fabs(fExpectedTemp - fActualTemp), 0.000001);
    EXPECT_LT(fabs(fExpectedWaterDeficit - fActualWaterDeficit), 0.001);
    EXPECT_LT(fabs(fExpectedSeasonal - fActualSeasonal), 0.001);
    //-----------------------------------------------------------------------//


    //-----------------------------------------------------------------------//
    //Timestep 2
    //-----------------------------------------------------------------------//
    p_oSimManager->RunSim(1);
    fExpectedPrecip = 1642.67;
    fExpectedTemp = 6.801666667;
    fExpectedWaterDeficit = 160.0181253;
    fExpectedSeasonal = 859.9102243;
    fActualPrecip = p_oPlot->GetMeanAnnualPrecip();
    fActualTemp = p_oPlot->GetMeanAnnualTemp();
    fActualWaterDeficit = p_oPlot->GetWaterDeficit();
    fActualSeasonal = p_oPlot->GetSeasonalPrecipitation();
    EXPECT_LT(fabs(fExpectedPrecip - fActualPrecip), 0.000001);
    EXPECT_LT(fabs(fExpectedTemp - fActualTemp), 0.000001);
    EXPECT_LT(fabs(fExpectedWaterDeficit - fActualWaterDeficit), 0.001);
    EXPECT_LT(fabs(fExpectedSeasonal - fActualSeasonal), 0.001);

    //----- Grid values -----------------------------------------------------//
    p_oClimateGrid->GetValueOfCell(0, 0, iTempCode, &fActualTemp);
    p_oClimateGrid->GetValueOfCell(0, 0, iPrecipCode, &fActualPrecip);
    p_oClimateGrid->GetValueOfCell(0, 0, iWDCode, &fActualWaterDeficit);
    p_oClimateGrid->GetValueOfCell(0, 0, iSeasonalCode, &fActualSeasonal);
    EXPECT_LT(fabs(fExpectedPrecip - fActualPrecip), 0.000001);
    EXPECT_LT(fabs(fExpectedTemp - fActualTemp), 0.000001);
    EXPECT_LT(fabs(fExpectedWaterDeficit - fActualWaterDeficit), 0.001);
    EXPECT_LT(fabs(fExpectedSeasonal - fActualSeasonal), 0.001);

    //----- Long term means -------------------------------------------------//
    fExpectedPrecip = 1692.06;
    fExpectedTemp = 7.355833333;
    fExpectedWaterDeficit = 132.3558176;
    fExpectedSeasonal = 892.7450435;
    fActualPrecip = p_oPlot->GetLTMAnnualPrecip();
    fActualTemp = p_oPlot->GetLTMAnnualTemp();
    fActualWaterDeficit = p_oPlot->GetLTMWaterDeficit();
    fActualSeasonal = p_oPlot->GetLTMSeasonalPrecipitation();
    EXPECT_LT(fabs(fExpectedPrecip - fActualPrecip), 0.000001);
    EXPECT_LT(fabs(fExpectedTemp - fActualTemp), 0.000001);
    EXPECT_LT(fabs(fExpectedWaterDeficit - fActualWaterDeficit), 0.001);
    EXPECT_LT(fabs(fExpectedSeasonal - fActualSeasonal), 0.001);
    //-----------------------------------------------------------------------//


    //-----------------------------------------------------------------------//
    //Timestep 3
    //-----------------------------------------------------------------------//
    p_oSimManager->RunSim(1);
    fExpectedPrecip = 1892.37;
    fExpectedTemp = 6.618333333;
    fExpectedWaterDeficit = 11.9990999;
    fExpectedSeasonal = 989.3014842;
    fActualPrecip = p_oPlot->GetMeanAnnualPrecip();
    fActualTemp = p_oPlot->GetMeanAnnualTemp();
    fActualWaterDeficit = p_oPlot->GetWaterDeficit();
    fActualSeasonal = p_oPlot->GetSeasonalPrecipitation();
    EXPECT_LT(fabs(fExpectedPrecip - fActualPrecip), 0.000001);
    EXPECT_LT(fabs(fExpectedTemp - fActualTemp), 0.000001);
    EXPECT_LT(fabs(fExpectedWaterDeficit - fActualWaterDeficit), 0.001);
    EXPECT_LT(fabs(fExpectedSeasonal - fActualSeasonal), 0.001);

    //----- Grid values -----------------------------------------------------//
    p_oClimateGrid->GetValueOfCell(0, 0, iTempCode, &fActualTemp);
    p_oClimateGrid->GetValueOfCell(0, 0, iPrecipCode, &fActualPrecip);
    p_oClimateGrid->GetValueOfCell(0, 0, iWDCode, &fActualWaterDeficit);
    p_oClimateGrid->GetValueOfCell(0, 0, iSeasonalCode, &fActualSeasonal);
    EXPECT_LT(fabs(fExpectedPrecip - fActualPrecip), 0.000001);
    EXPECT_LT(fabs(fExpectedTemp - fActualTemp), 0.000001);
    EXPECT_LT(fabs(fExpectedWaterDeficit - fActualWaterDeficit), 0.001);
    EXPECT_LT(fabs(fExpectedSeasonal - fActualSeasonal), 0.001);

    //----- Long term means -------------------------------------------------//
    fExpectedPrecip = 1668.585;
    fExpectedTemp = 6.698125;
    fExpectedWaterDeficit = 95.94410372;
    fExpectedSeasonal = 891.8714528;
    fActualPrecip = p_oPlot->GetLTMAnnualPrecip();
    fActualTemp = p_oPlot->GetLTMAnnualTemp();
    fActualWaterDeficit = p_oPlot->GetLTMWaterDeficit();
    fActualSeasonal = p_oPlot->GetLTMSeasonalPrecipitation();
    EXPECT_LT(fabs(fExpectedPrecip - fActualPrecip), 0.000001);
    EXPECT_LT(fabs(fExpectedTemp - fActualTemp), 0.000001);
    EXPECT_LT(fabs(fExpectedWaterDeficit - fActualWaterDeficit), 0.001);
    EXPECT_LT(fabs(fExpectedSeasonal - fActualSeasonal), 0.001);
    //-----------------------------------------------------------------------//


    //-----------------------------------------------------------------------//
    //Timestep 4
    //-----------------------------------------------------------------------//
    p_oSimManager->RunSim(1);
    fExpectedPrecip = 1722.77;
    fExpectedTemp = 7.395;
    fExpectedWaterDeficit = 130.4596051;
    fExpectedSeasonal = 946.4096629;
    fActualPrecip = p_oPlot->GetMeanAnnualPrecip();
    fActualTemp = p_oPlot->GetMeanAnnualTemp();
    fActualWaterDeficit = p_oPlot->GetWaterDeficit();
    fActualSeasonal = p_oPlot->GetSeasonalPrecipitation();
    EXPECT_LT(fabs(fExpectedPrecip - fActualPrecip), 0.000001);
    EXPECT_LT(fabs(fExpectedTemp - fActualTemp), 0.000001);
    EXPECT_LT(fabs(fExpectedWaterDeficit - fActualWaterDeficit), 0.001);
    EXPECT_LT(fabs(fExpectedSeasonal - fActualSeasonal), 0.001);

    //----- Grid values -----------------------------------------------------//
    p_oClimateGrid->GetValueOfCell(0, 0, iTempCode, &fActualTemp);
    p_oClimateGrid->GetValueOfCell(0, 0, iPrecipCode, &fActualPrecip);
    p_oClimateGrid->GetValueOfCell(0, 0, iWDCode, &fActualWaterDeficit);
    p_oClimateGrid->GetValueOfCell(0, 0, iSeasonalCode, &fActualSeasonal);
    EXPECT_LT(fabs(fExpectedPrecip - fActualPrecip), 0.000001);
    EXPECT_LT(fabs(fExpectedTemp - fActualTemp), 0.000001);
    EXPECT_LT(fabs(fExpectedWaterDeficit - fActualWaterDeficit), 0.001);
    EXPECT_LT(fabs(fExpectedSeasonal - fActualSeasonal), 0.001);

    //----- Long term means -------------------------------------------------//
    fExpectedPrecip = 1722.035;
    fExpectedTemp = 6.9175;
    fExpectedWaterDeficit = 98.39048156;
    fExpectedSeasonal = 919.3805526;
    fActualPrecip = p_oPlot->GetLTMAnnualPrecip();
    fActualTemp = p_oPlot->GetLTMAnnualTemp();
    fActualWaterDeficit = p_oPlot->GetLTMWaterDeficit();
    fActualSeasonal = p_oPlot->GetLTMSeasonalPrecipitation();
    EXPECT_LT(fabs(fExpectedPrecip - fActualPrecip), 0.000001);
    EXPECT_LT(fabs(fExpectedTemp - fActualTemp), 0.000001);
    EXPECT_LT(fabs(fExpectedWaterDeficit - fActualWaterDeficit), 0.001);
    EXPECT_LT(fabs(fExpectedSeasonal - fActualSeasonal), 0.001);
    //-----------------------------------------------------------------------//


    //-----------------------------------------------------------------------//
    //Timestep 5
    //-----------------------------------------------------------------------//
    p_oSimManager->RunSim(1);
    fExpectedPrecip = 1527.74;
    fExpectedTemp = 7.99;
    fExpectedWaterDeficit = 129.3160883;
    fExpectedSeasonal = 902.2940183;
    fActualPrecip = p_oPlot->GetMeanAnnualPrecip();
    fActualTemp = p_oPlot->GetMeanAnnualTemp();
    fActualWaterDeficit = p_oPlot->GetWaterDeficit();
    fActualSeasonal = p_oPlot->GetSeasonalPrecipitation();
    EXPECT_LT(fabs(fExpectedPrecip - fActualPrecip), 0.000001);
    EXPECT_LT(fabs(fExpectedTemp - fActualTemp), 0.000001);
    EXPECT_LT(fabs(fExpectedWaterDeficit - fActualWaterDeficit), 0.001);
    EXPECT_LT(fabs(fExpectedSeasonal - fActualSeasonal), 0.001);

    //----- Grid values -----------------------------------------------------//
    p_oClimateGrid->GetValueOfCell(0, 0, iTempCode, &fActualTemp);
    p_oClimateGrid->GetValueOfCell(0, 0, iPrecipCode, &fActualPrecip);
    p_oClimateGrid->GetValueOfCell(0, 0, iWDCode, &fActualWaterDeficit);
    p_oClimateGrid->GetValueOfCell(0, 0, iSeasonalCode, &fActualSeasonal);
    EXPECT_LT(fabs(fExpectedPrecip - fActualPrecip), 0.000001);
    EXPECT_LT(fabs(fExpectedTemp - fActualTemp), 0.000001);
    EXPECT_LT(fabs(fExpectedWaterDeficit - fActualWaterDeficit), 0.001);
    EXPECT_LT(fabs(fExpectedSeasonal - fActualSeasonal), 0.001);

    //----- Long term means -------------------------------------------------//
    fExpectedPrecip = 1696.3875;
    fExpectedTemp = 7.20125;
    fExpectedWaterDeficit = 107.9482297;
    fExpectedSeasonal = 924.4788474;
    fActualPrecip = p_oPlot->GetLTMAnnualPrecip();
    fActualTemp = p_oPlot->GetLTMAnnualTemp();
    fActualWaterDeficit = p_oPlot->GetLTMWaterDeficit();
    fActualSeasonal = p_oPlot->GetLTMSeasonalPrecipitation();
    EXPECT_LT(fabs(fExpectedPrecip - fActualPrecip), 0.000001);
    EXPECT_LT(fabs(fExpectedTemp - fActualTemp), 0.000001);
    EXPECT_LT(fabs(fExpectedWaterDeficit - fActualWaterDeficit), 0.001);
    EXPECT_LT(fabs(fExpectedSeasonal - fActualSeasonal), 0.001);
    //-----------------------------------------------------------------------//


    //-----------------------------------------------------------------------//
    //Timestep 6
    //-----------------------------------------------------------------------//
    p_oSimManager->RunSim(1);
    fExpectedPrecip = 1628.82;
    fExpectedTemp = 7.334166667;
    fExpectedWaterDeficit = 152.2639151;
    fExpectedSeasonal = 862.5541861;
    fActualPrecip = p_oPlot->GetMeanAnnualPrecip();
    fActualTemp = p_oPlot->GetMeanAnnualTemp();
    fActualWaterDeficit = p_oPlot->GetWaterDeficit();
    fActualSeasonal = p_oPlot->GetSeasonalPrecipitation();
    EXPECT_LT(fabs(fExpectedPrecip - fActualPrecip), 0.000001);
    EXPECT_LT(fabs(fExpectedTemp - fActualTemp), 0.000001);
    EXPECT_LT(fabs(fExpectedWaterDeficit - fActualWaterDeficit), 0.001);
    EXPECT_LT(fabs(fExpectedSeasonal - fActualSeasonal), 0.001);

    //----- Grid values -----------------------------------------------------//
    p_oClimateGrid->GetValueOfCell(0, 0, iTempCode, &fActualTemp);
    p_oClimateGrid->GetValueOfCell(0, 0, iPrecipCode, &fActualPrecip);
    p_oClimateGrid->GetValueOfCell(0, 0, iWDCode, &fActualWaterDeficit);
    p_oClimateGrid->GetValueOfCell(0, 0, iSeasonalCode, &fActualSeasonal);
    EXPECT_LT(fabs(fExpectedPrecip - fActualPrecip), 0.000001);
    EXPECT_LT(fabs(fExpectedTemp - fActualTemp), 0.000001);
    EXPECT_LT(fabs(fExpectedWaterDeficit - fActualWaterDeficit), 0.001);
    EXPECT_LT(fabs(fExpectedSeasonal - fActualSeasonal), 0.001);

    //----- Long term means -------------------------------------------------//
    fExpectedPrecip = 1692.925;
    fExpectedTemp = 7.334375;
    fExpectedWaterDeficit = 106.0096771;
    fExpectedSeasonal = 925.1398379;
    fActualPrecip = p_oPlot->GetLTMAnnualPrecip();
    fActualTemp = p_oPlot->GetLTMAnnualTemp();
    fActualWaterDeficit = p_oPlot->GetLTMWaterDeficit();
    fActualSeasonal = p_oPlot->GetLTMSeasonalPrecipitation();
    EXPECT_LT(fabs(fExpectedPrecip - fActualPrecip), 0.000001);
    EXPECT_LT(fabs(fExpectedTemp - fActualTemp), 0.000001);
    EXPECT_LT(fabs(fExpectedWaterDeficit - fActualWaterDeficit), 0.001);
    EXPECT_LT(fabs(fExpectedSeasonal - fActualSeasonal), 0.001);
    //-----------------------------------------------------------------------//

    delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}


////////////////////////////////////////////////////////////////////////////
// TestErrorProcessing()
////////////////////////////////////////////////////////////////////////////
TEST(ClimateImporter, TestErrorProcessing) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try
  {
    p_oSimManager->ReadFile(WriteClimateImporterXMLErrorFile1());
    FAIL() << "TestClimateImporter error processing didn't catch error for WriteSeasonalWaterDeficitXMLErrorFile1.";
  }
  catch (modelErr& err)
  {
    if (err.sFunction.compare("clClimateImporter::ReadParameterFileData") != 0)
    {
      std::stringstream msg;
      msg << "TestClimateImporter error processing caught wrong error for WriteClimateImporterXMLErrorFile1:"
             << err.sFunction << err.sMoreInfo;
      FAIL() << msg.str();
    }
    ;
  }

  try
  {
    p_oSimManager->ReadFile(WriteClimateImporterXMLErrorFile2());
    FAIL() << "TestClimateImporter error processing didn't catch error for WriteClimateImporterXMLErrorFile2.";
  }
  catch (modelErr& err)
  {
    if (err.sFunction.compare("clClimateImporter::ReadParameterFileData") != 0)
    {
      std::stringstream msg;
      msg << "TestClimateImporter error processing caught wrong error for WriteClimateImporterXMLErrorFile2:"
             << err.sFunction << err.sMoreInfo;
      FAIL() << msg.str();
    }
    ;
  }

  try
  {
    p_oSimManager->ReadFile(WriteClimateImporterXMLErrorFile3());
    FAIL() << "TestClimateImporter error processing didn't catch error for WriteClimateImporterXMLErrorFile3.";
  }
  catch (modelErr& err)
  {
    if (err.sFunction.compare("clClimateImporter::ReadParameterFileData") != 0)
    {
      FAIL() << "TestClimateImporter error processing caught wrong error for WriteClimateImporterXMLErrorFile3.";
    }
    ;
  }

  delete p_oSimManager;
}



/////////////////////////////////////////////////////////////////////////////
// WriteClimateImporterXMLFile1()
/////////////////////////////////////////////////////////////////////////////
const char* WriteClimateImporterXMLFile1()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  std::fstream oOut;
  oOut.open( cFileString, ios::out | ios::trunc );

  WriteClimateImporterCommonStuff(oOut);

  oOut << "<ClimateImporter1>"
	   << "<sc_ciAWS>60.9</sc_ciAWS>"

	   << "<sc_ciMonthlyTempJan>"
	   << "<sc_cimtjanVal ts=\"1\">-2.57</sc_cimtjanVal>"
	   << "<sc_cimtjanVal ts=\"2\">-3.46</sc_cimtjanVal>"
	   << "<sc_cimtjanVal ts=\"3\">-6.93</sc_cimtjanVal>"
	   << "<sc_cimtjanVal ts=\"4\">-7.76</sc_cimtjanVal>"
	   << "<sc_cimtjanVal ts=\"5\">-0.72</sc_cimtjanVal>"
	   << "<sc_cimtjanVal ts=\"6\">1.3</sc_cimtjanVal>"
	   << "</sc_ciMonthlyTempJan>"

	   << "<sc_ciMonthlyTempFeb>"
	   << "<sc_cimtfebVal ts=\"1\">2.75</sc_cimtfebVal>"
	   << "<sc_cimtfebVal ts=\"2\">-8.57</sc_cimtfebVal>"
	   << "<sc_cimtfebVal ts=\"3\">1.98</sc_cimtfebVal>"
	   << "<sc_cimtfebVal ts=\"4\">-7.5</sc_cimtfebVal>"
	   << "<sc_cimtfebVal ts=\"5\">-2.44</sc_cimtfebVal>"
	   << "<sc_cimtfebVal ts=\"6\">-9.36</sc_cimtfebVal>"
	   << "</sc_ciMonthlyTempFeb>"

	   << "<sc_ciMonthlyTempMar>"
	   << "<sc_cimtmarVal ts=\"1\">2.94</sc_cimtmarVal>"
	   << "<sc_cimtmarVal ts=\"2\">0.28</sc_cimtmarVal>"
	   << "<sc_cimtmarVal ts=\"3\">0.3</sc_cimtmarVal>"
	   << "<sc_cimtmarVal ts=\"4\">-0.78</sc_cimtmarVal>"
	   << "<sc_cimtmarVal ts=\"5\">4.85</sc_cimtmarVal>"
	   << "<sc_cimtmarVal ts=\"6\">3.78</sc_cimtmarVal>"
	   << "</sc_ciMonthlyTempMar>"

	   << "<sc_ciMonthlyTempApr>"
	   << "<sc_cimtaprVal ts=\"1\">2.17</sc_cimtaprVal>"
	   << "<sc_cimtaprVal ts=\"2\">5.9</sc_cimtaprVal>"
	   << "<sc_cimtaprVal ts=\"3\">7.17</sc_cimtaprVal>"
	   << "<sc_cimtaprVal ts=\"4\">8.67</sc_cimtaprVal>"
	   << "<sc_cimtaprVal ts=\"5\">5.61</sc_cimtaprVal>"
	   << "<sc_cimtaprVal ts=\"6\">4.56</sc_cimtaprVal>"
	   << "</sc_ciMonthlyTempApr>"

	   << "<sc_ciMonthlyTempMay>"
	   << "<sc_cimtmayVal ts=\"1\">7.25</sc_cimtmayVal>"
	   << "<sc_cimtmayVal ts=\"2\">7.6</sc_cimtmayVal>"
	   << "<sc_cimtmayVal ts=\"3\">9.46</sc_cimtmayVal>"
	   << "<sc_cimtmayVal ts=\"4\">11.26</sc_cimtmayVal>"
	   << "<sc_cimtmayVal ts=\"5\">7.6</sc_cimtmayVal>"
	   << "<sc_cimtmayVal ts=\"6\">6.9</sc_cimtmayVal>"
	   << "</sc_ciMonthlyTempMay>"

	   << "<sc_ciMonthlyTempJun>"
	   << "<sc_cimtjunVal ts=\"1\">11.05</sc_cimtjunVal>"
	   << "<sc_cimtjunVal ts=\"2\">17.16</sc_cimtjunVal>"
	   << "<sc_cimtjunVal ts=\"3\">11.06</sc_cimtjunVal>"
	   << "<sc_cimtjunVal ts=\"4\">17.72</sc_cimtjunVal>"
	   << "<sc_cimtjunVal ts=\"5\">14.05</sc_cimtjunVal>"
	   << "<sc_cimtjunVal ts=\"6\">13.52</sc_cimtjunVal>"
	   << "</sc_ciMonthlyTempJun>"

	   << "<sc_ciMonthlyTempJul>"
	   << "<sc_cimtjulVal ts=\"1\">16.82</sc_cimtjulVal>"
	   << "<sc_cimtjulVal ts=\"2\">22</sc_cimtjulVal>"
	   << "<sc_cimtjulVal ts=\"3\">18.34</sc_cimtjulVal>"
	   << "<sc_cimtjulVal ts=\"4\">20.99</sc_cimtjulVal>"
	   << "<sc_cimtjulVal ts=\"5\">15.46</sc_cimtjulVal>"
	   << "<sc_cimtjulVal ts=\"6\">15.74</sc_cimtjulVal>"
	   << "</sc_ciMonthlyTempJul>"

	   << "<sc_ciMonthlyTempAug>"
	   << "<sc_cimtaugVal ts=\"1\">18.32</sc_cimtaugVal>"
	   << "<sc_cimtaugVal ts=\"2\">15.97</sc_cimtaugVal>"
	   << "<sc_cimtaugVal ts=\"3\">17.54</sc_cimtaugVal>"
	   << "<sc_cimtaugVal ts=\"4\">17.46</sc_cimtaugVal>"
	   << "<sc_cimtaugVal ts=\"5\">16.69</sc_cimtaugVal>"
	   << "<sc_cimtaugVal ts=\"6\">17.48</sc_cimtaugVal>"
	   << "</sc_ciMonthlyTempAug>"

	   << "<sc_ciMonthlyTempSep>"
	   << "<sc_cimtsepVal ts=\"1\">22.73</sc_cimtsepVal>"
	   << "<sc_cimtsepVal ts=\"2\">20.94</sc_cimtsepVal>"
	   << "<sc_cimtsepVal ts=\"3\">15.94</sc_cimtsepVal>"
	   << "<sc_cimtsepVal ts=\"4\">18.87</sc_cimtsepVal>"
	   << "<sc_cimtsepVal ts=\"5\">22.85</sc_cimtsepVal>"
	   << "<sc_cimtsepVal ts=\"6\">19.53</sc_cimtsepVal>"
	   << "</sc_ciMonthlyTempSep>"

	   << "<sc_ciMonthlyTempOct>"
	   << "<sc_cimtoctVal ts=\"1\">7.92</sc_cimtoctVal>"
	   << "<sc_cimtoctVal ts=\"2\">8.18</sc_cimtoctVal>"
	   << "<sc_cimtoctVal ts=\"3\">8.43</sc_cimtoctVal>"
	   << "<sc_cimtoctVal ts=\"4\">8.68</sc_cimtoctVal>"
	   << "<sc_cimtoctVal ts=\"5\">8.94</sc_cimtoctVal>"
	   << "<sc_cimtoctVal ts=\"6\">9.19</sc_cimtoctVal>"
	   << "</sc_ciMonthlyTempOct>"

	   << "<sc_ciMonthlyTempNov>"
	   << "<sc_cimtnovVal ts=\"1\">2.48</sc_cimtnovVal>"
	   << "<sc_cimtnovVal ts=\"2\">2.56</sc_cimtnovVal>"
	   << "<sc_cimtnovVal ts=\"3\">2.64</sc_cimtnovVal>"
	   << "<sc_cimtnovVal ts=\"4\">2.72</sc_cimtnovVal>"
	   << "<sc_cimtnovVal ts=\"5\">2.8</sc_cimtnovVal>"
	   << "<sc_cimtnovVal ts=\"6\">2.88</sc_cimtnovVal>"
	   << "</sc_ciMonthlyTempNov>"

	   << "<sc_ciMonthlyTempDec>"
	   << "<sc_cimtdecVal ts=\"1\">-9.6</sc_cimtdecVal>"
	   << "<sc_cimtdecVal ts=\"2\">-6.94</sc_cimtdecVal>"
	   << "<sc_cimtdecVal ts=\"3\">-6.51</sc_cimtdecVal>"
	   << "<sc_cimtdecVal ts=\"4\">-1.59</sc_cimtdecVal>"
	   << "<sc_cimtdecVal ts=\"5\">0.19</sc_cimtdecVal>"
	   << "<sc_cimtdecVal ts=\"6\">2.49</sc_cimtdecVal>"
	   << "</sc_ciMonthlyTempDec>"

	   << "<sc_ciMonthlyPptJan>"
	   << "<sc_cimpjanVal ts=\"1\">161.48</sc_cimpjanVal>"
	   << "<sc_cimpjanVal ts=\"2\">152.09</sc_cimpjanVal>"
	   << "<sc_cimpjanVal ts=\"3\">152.5</sc_cimpjanVal>"
	   << "<sc_cimpjanVal ts=\"4\">152.71</sc_cimpjanVal>"
	   << "<sc_cimpjanVal ts=\"5\">78.44</sc_cimpjanVal>"
	   << "<sc_cimpjanVal ts=\"6\">123.19</sc_cimpjanVal>"
	   << "</sc_ciMonthlyPptJan>"

	   << "<sc_ciMonthlyPptFeb>"
	   << "<sc_cimpfebVal ts=\"1\">199.32</sc_cimpfebVal>"
	   << "<sc_cimpfebVal ts=\"2\">192.94</sc_cimpfebVal>"
	   << "<sc_cimpfebVal ts=\"3\">188.1</sc_cimpfebVal>"
	   << "<sc_cimpfebVal ts=\"4\">153.95</sc_cimpfebVal>"
	   << "<sc_cimpfebVal ts=\"5\">89.79</sc_cimpfebVal>"
	   << "<sc_cimpfebVal ts=\"6\">189.67</sc_cimpfebVal>"
	   << "</sc_ciMonthlyPptFeb>"

	   << "<sc_ciMonthlyPptMar>"
	   << "<sc_cimpmarVal ts=\"1\">169.99</sc_cimpmarVal>"
	   << "<sc_cimpmarVal ts=\"2\">105.49</sc_cimpmarVal>"
	   << "<sc_cimpmarVal ts=\"3\">141.34</sc_cimpmarVal>"
	   << "<sc_cimpmarVal ts=\"4\">84.71</sc_cimpmarVal>"
	   << "<sc_cimpmarVal ts=\"5\">188.92</sc_cimpmarVal>"
	   << "<sc_cimpmarVal ts=\"6\">93.47</sc_cimpmarVal>"
	   << "</sc_ciMonthlyPptMar>"

	   << "<sc_ciMonthlyPptApr>"
	   << "<sc_cimpaprVal ts=\"1\">82.02</sc_cimpaprVal>"
	   << "<sc_cimpaprVal ts=\"2\">77.49</sc_cimpaprVal>"
	   << "<sc_cimpaprVal ts=\"3\">186.32</sc_cimpaprVal>"
	   << "<sc_cimpaprVal ts=\"4\">174.4</sc_cimpaprVal>"
	   << "<sc_cimpaprVal ts=\"5\">161.25</sc_cimpaprVal>"
	   << "<sc_cimpaprVal ts=\"6\">99.76</sc_cimpaprVal>"
	   << "</sc_ciMonthlyPptApr>"

	   << "<sc_ciMonthlyPptMay>"
	   << "<sc_cimpmayVal ts=\"1\">132.54</sc_cimpmayVal>"
	   << "<sc_cimpmayVal ts=\"2\">121.74</sc_cimpmayVal>"
	   << "<sc_cimpmayVal ts=\"3\">178.18</sc_cimpmayVal>"
	   << "<sc_cimpmayVal ts=\"4\">102.86</sc_cimpmayVal>"
	   << "<sc_cimpmayVal ts=\"5\">102.84</sc_cimpmayVal>"
	   << "<sc_cimpmayVal ts=\"6\">172.41</sc_cimpmayVal>"
	   << "</sc_ciMonthlyPptMay>"

	   << "<sc_ciMonthlyPptJun>"
	   << "<sc_cimpjunVal ts=\"1\">157.67</sc_cimpjunVal>"
	   << "<sc_cimpjunVal ts=\"2\">133.89</sc_cimpjunVal>"
	   << "<sc_cimpjunVal ts=\"3\">147.29</sc_cimpjunVal>"
	   << "<sc_cimpjunVal ts=\"4\">123.74</sc_cimpjunVal>"
	   << "<sc_cimpjunVal ts=\"5\">126.66</sc_cimpjunVal>"
	   << "<sc_cimpjunVal ts=\"6\">134.35</sc_cimpjunVal>"
	   << "</sc_ciMonthlyPptJun>"

	   << "<sc_ciMonthlyPptJul>"
	   << "<sc_cimpjulVal ts=\"1\">97.63</sc_cimpjulVal>"
	   << "<sc_cimpjulVal ts=\"2\">141.94</sc_cimpjulVal>"
	   << "<sc_cimpjulVal ts=\"3\">173.88</sc_cimpjulVal>"
	   << "<sc_cimpjulVal ts=\"4\">166.53</sc_cimpjulVal>"
	   << "<sc_cimpjulVal ts=\"5\">140.41</sc_cimpjulVal>"
	   << "<sc_cimpjulVal ts=\"6\">128.89</sc_cimpjulVal>"
	   << "</sc_ciMonthlyPptJul>"

	   << "<sc_ciMonthlyPptAug>"
	   << "<sc_cimpaugVal ts=\"1\">145.57</sc_cimpaugVal>"
	   << "<sc_cimpaugVal ts=\"2\">156.69</sc_cimpaugVal>"
	   << "<sc_cimpaugVal ts=\"3\">146.55</sc_cimpaugVal>"
	   << "<sc_cimpaugVal ts=\"4\">167.73</sc_cimpaugVal>"
	   << "<sc_cimpaugVal ts=\"5\">147.67</sc_cimpaugVal>"
	   << "<sc_cimpaugVal ts=\"6\">119.52</sc_cimpaugVal>"
	   << "</sc_ciMonthlyPptAug>"

	   << "<sc_ciMonthlyPptSep>"
	   << "<sc_cimpsepVal ts=\"1\">134.38</sc_cimpsepVal>"
	   << "<sc_cimpsepVal ts=\"2\">89.78</sc_cimpsepVal>"
	   << "<sc_cimpsepVal ts=\"3\">173.37</sc_cimpsepVal>"
	   << "<sc_cimpsepVal ts=\"4\">146.16</sc_cimpsepVal>"
	   << "<sc_cimpsepVal ts=\"5\">108.71</sc_cimpsepVal>"
	   << "<sc_cimpsepVal ts=\"6\">90.68</sc_cimpsepVal>"
	   << "</sc_ciMonthlyPptSep>"

	   << "<sc_ciMonthlyPptOct>"
	   << "<sc_cimpoctVal ts=\"1\">100.17</sc_cimpoctVal>"
	   << "<sc_cimpoctVal ts=\"2\">178.11</sc_cimpoctVal>"
	   << "<sc_cimpoctVal ts=\"3\">120.16</sc_cimpoctVal>"
	   << "<sc_cimpoctVal ts=\"4\">198.43</sc_cimpoctVal>"
	   << "<sc_cimpoctVal ts=\"5\">75.22</sc_cimpoctVal>"
	   << "<sc_cimpoctVal ts=\"6\">198.3</sc_cimpoctVal>"
	   << "</sc_ciMonthlyPptOct>"

	   << "<sc_ciMonthlyPptNov>"
	   << "<sc_cimpnovVal ts=\"1\">112.34</sc_cimpnovVal>"
	   << "<sc_cimpnovVal ts=\"2\">191.22</sc_cimpnovVal>"
	   << "<sc_cimpnovVal ts=\"3\">125.47</sc_cimpnovVal>"
	   << "<sc_cimpnovVal ts=\"4\">79.8</sc_cimpnovVal>"
	   << "<sc_cimpnovVal ts=\"5\">116.29</sc_cimpnovVal>"
	   << "<sc_cimpnovVal ts=\"6\">146.75</sc_cimpnovVal>"
	   << "</sc_ciMonthlyPptNov>"

	   << "<sc_ciMonthlyPptDec>"
	   << "<sc_cimpdecVal ts=\"1\">137.22</sc_cimpdecVal>"
	   << "<sc_cimpdecVal ts=\"2\">101.29</sc_cimpdecVal>"
	   << "<sc_cimpdecVal ts=\"3\">159.21</sc_cimpdecVal>"
	   << "<sc_cimpdecVal ts=\"4\">171.75</sc_cimpdecVal>"
	   << "<sc_cimpdecVal ts=\"5\">191.54</sc_cimpdecVal>"
	   << "<sc_cimpdecVal ts=\"6\">131.83</sc_cimpdecVal>"
	   << "</sc_ciMonthlyPptDec>"

       << "<sc_ciJanRad>7468.475</sc_ciJanRad>"
       << "<sc_ciFebRad>10353.32</sc_ciFebRad>"
       << "<sc_ciMarRad>17453.07</sc_ciMarRad>"
       << "<sc_ciAprRad>22721.85</sc_ciAprRad>"
       << "<sc_ciMayRad>27901.37</sc_ciMayRad>"
       << "<sc_ciJunRad>28677.54</sc_ciJunRad>"
       << "<sc_ciJulRad>28764.65</sc_ciJulRad>"
       << "<sc_ciAugRad>25075.4</sc_ciAugRad>"
       << "<sc_ciSepRad>19259.27</sc_ciSepRad>"
       << "<sc_ciOctRad>12609.6</sc_ciOctRad>"
       << "<sc_ciNovRad>7988.013</sc_ciNovRad>"
       << "<sc_ciDecRad>6307.151</sc_ciDecRad>"

       << "</ClimateImporter1>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteClimateImporterXMLFile2()
/////////////////////////////////////////////////////////////////////////////
const char* WriteClimateImporterXMLFile2()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  std::fstream oOut;
  oOut.open( cFileString, ios::out | ios::trunc );

  WriteClimateImporterCommonStuff(oOut);

  oOut << "<ClimateImporter1>"
     << "<sc_ciAWS>60.9</sc_ciAWS>"
     << "<sc_ciCalendarMean>0</sc_ciCalendarMean>"
     << "<sc_ciLTM>5</sc_ciLTM>"

     << "<sc_ciMonthlyTempJan>"
     << "<sc_cimtjanVal ts=\"-5\">-3.86</sc_cimtjanVal>"
     << "<sc_cimtjanVal ts=\"-4\">0.56</sc_cimtjanVal>"
     << "<sc_cimtjanVal ts=\"-3\">-1.51</sc_cimtjanVal>"
     << "<sc_cimtjanVal ts=\"-2\">5.03</sc_cimtjanVal>"
     << "<sc_cimtjanVal ts=\"-1\">-5.5</sc_cimtjanVal>"
     << "<sc_cimtjanVal ts=\"1\">-2.57</sc_cimtjanVal>"
     << "<sc_cimtjanVal ts=\"2\">-3.46</sc_cimtjanVal>"
     << "<sc_cimtjanVal ts=\"3\">-6.93</sc_cimtjanVal>"
     << "<sc_cimtjanVal ts=\"4\">-7.76</sc_cimtjanVal>"
     << "<sc_cimtjanVal ts=\"5\">-0.72</sc_cimtjanVal>"
     << "<sc_cimtjanVal ts=\"6\">1.3</sc_cimtjanVal>"
     << "</sc_ciMonthlyTempJan>"

     << "<sc_ciMonthlyTempFeb>"
     << "<sc_cimtfebVal ts=\"-5\">-1.56</sc_cimtfebVal>"
     << "<sc_cimtfebVal ts=\"-4\">-0.03</sc_cimtfebVal>"
     << "<sc_cimtfebVal ts=\"-3\">2.16</sc_cimtfebVal>"
     << "<sc_cimtfebVal ts=\"-2\">4.5</sc_cimtfebVal>"
     << "<sc_cimtfebVal ts=\"-1\">-0.6</sc_cimtfebVal>"
     << "<sc_cimtfebVal ts=\"1\">2.75</sc_cimtfebVal>"
     << "<sc_cimtfebVal ts=\"2\">-8.57</sc_cimtfebVal>"
     << "<sc_cimtfebVal ts=\"3\">1.98</sc_cimtfebVal>"
     << "<sc_cimtfebVal ts=\"4\">-7.5</sc_cimtfebVal>"
     << "<sc_cimtfebVal ts=\"5\">-2.44</sc_cimtfebVal>"
     << "<sc_cimtfebVal ts=\"6\">-9.36</sc_cimtfebVal>"
     << "</sc_ciMonthlyTempFeb>"

     << "<sc_ciMonthlyTempMar>"
     << "<sc_cimtmarVal ts=\"-5\">1.93</sc_cimtmarVal>"
     << "<sc_cimtmarVal ts=\"-4\">1.57</sc_cimtmarVal>"
     << "<sc_cimtmarVal ts=\"-3\">7.49</sc_cimtmarVal>"
     << "<sc_cimtmarVal ts=\"-2\">6.95</sc_cimtmarVal>"
     << "<sc_cimtmarVal ts=\"-1\">1.54</sc_cimtmarVal>"
     << "<sc_cimtmarVal ts=\"1\">2.94</sc_cimtmarVal>"
     << "<sc_cimtmarVal ts=\"2\">0.28</sc_cimtmarVal>"
     << "<sc_cimtmarVal ts=\"3\">0.3</sc_cimtmarVal>"
     << "<sc_cimtmarVal ts=\"4\">-0.78</sc_cimtmarVal>"
     << "<sc_cimtmarVal ts=\"5\">4.85</sc_cimtmarVal>"
     << "<sc_cimtmarVal ts=\"6\">3.78</sc_cimtmarVal>"
     << "</sc_ciMonthlyTempMar>"

     << "<sc_ciMonthlyTempApr>"
     << "<sc_cimtaprVal ts=\"-5\">5.53</sc_cimtaprVal>"
     << "<sc_cimtaprVal ts=\"-4\">11.17</sc_cimtaprVal>"
     << "<sc_cimtaprVal ts=\"-3\">6.21</sc_cimtaprVal>"
     << "<sc_cimtaprVal ts=\"-2\">11.68</sc_cimtaprVal>"
     << "<sc_cimtaprVal ts=\"-1\">8.66</sc_cimtaprVal>"
     << "<sc_cimtaprVal ts=\"1\">2.17</sc_cimtaprVal>"
     << "<sc_cimtaprVal ts=\"2\">5.9</sc_cimtaprVal>"
     << "<sc_cimtaprVal ts=\"3\">7.17</sc_cimtaprVal>"
     << "<sc_cimtaprVal ts=\"4\">8.67</sc_cimtaprVal>"
     << "<sc_cimtaprVal ts=\"5\">5.61</sc_cimtaprVal>"
     << "<sc_cimtaprVal ts=\"6\">4.56</sc_cimtaprVal>"
     << "</sc_ciMonthlyTempApr>"

     << "<sc_ciMonthlyTempMay>"
     << "<sc_cimtmayVal ts=\"-5\">10.59</sc_cimtmayVal>"
     << "<sc_cimtmayVal ts=\"-4\">7.49</sc_cimtmayVal>"
     << "<sc_cimtmayVal ts=\"-3\">7.66</sc_cimtmayVal>"
     << "<sc_cimtmayVal ts=\"-2\">12.52</sc_cimtmayVal>"
     << "<sc_cimtmayVal ts=\"-1\">10.68</sc_cimtmayVal>"
     << "<sc_cimtmayVal ts=\"1\">7.25</sc_cimtmayVal>"
     << "<sc_cimtmayVal ts=\"2\">7.6</sc_cimtmayVal>"
     << "<sc_cimtmayVal ts=\"3\">9.46</sc_cimtmayVal>"
     << "<sc_cimtmayVal ts=\"4\">11.26</sc_cimtmayVal>"
     << "<sc_cimtmayVal ts=\"5\">7.6</sc_cimtmayVal>"
     << "<sc_cimtmayVal ts=\"6\">6.9</sc_cimtmayVal>"
     << "</sc_ciMonthlyTempMay>"

     << "<sc_ciMonthlyTempJun>"
     << "<sc_cimtjunVal ts=\"-5\">14.99</sc_cimtjunVal>"
     << "<sc_cimtjunVal ts=\"-4\">7.67</sc_cimtjunVal>"
     << "<sc_cimtjunVal ts=\"-3\">10.1</sc_cimtjunVal>"
     << "<sc_cimtjunVal ts=\"-2\">14.33</sc_cimtjunVal>"
     << "<sc_cimtjunVal ts=\"-1\">16.65</sc_cimtjunVal>"
     << "<sc_cimtjunVal ts=\"1\">11.05</sc_cimtjunVal>"
     << "<sc_cimtjunVal ts=\"2\">17.16</sc_cimtjunVal>"
     << "<sc_cimtjunVal ts=\"3\">11.06</sc_cimtjunVal>"
     << "<sc_cimtjunVal ts=\"4\">17.72</sc_cimtjunVal>"
     << "<sc_cimtjunVal ts=\"5\">14.05</sc_cimtjunVal>"
     << "<sc_cimtjunVal ts=\"6\">13.52</sc_cimtjunVal>"
     << "</sc_ciMonthlyTempJun>"

     << "<sc_ciMonthlyTempJul>"
     << "<sc_cimtjulVal ts=\"-5\">13.42</sc_cimtjulVal>"
     << "<sc_cimtjulVal ts=\"-4\">15.48</sc_cimtjulVal>"
     << "<sc_cimtjulVal ts=\"-3\">15.24</sc_cimtjulVal>"
     << "<sc_cimtjulVal ts=\"-2\">17.87</sc_cimtjulVal>"
     << "<sc_cimtjulVal ts=\"-1\">14.13</sc_cimtjulVal>"
     << "<sc_cimtjulVal ts=\"1\">16.82</sc_cimtjulVal>"
     << "<sc_cimtjulVal ts=\"2\">22</sc_cimtjulVal>"
     << "<sc_cimtjulVal ts=\"3\">18.34</sc_cimtjulVal>"
     << "<sc_cimtjulVal ts=\"4\">20.99</sc_cimtjulVal>"
     << "<sc_cimtjulVal ts=\"5\">15.46</sc_cimtjulVal>"
     << "<sc_cimtjulVal ts=\"6\">15.74</sc_cimtjulVal>"
     << "</sc_ciMonthlyTempJul>"

     << "<sc_ciMonthlyTempAug>"
     << "<sc_cimtaugVal ts=\"-5\">7.55</sc_cimtaugVal>"
     << "<sc_cimtaugVal ts=\"-4\">12.01</sc_cimtaugVal>"
     << "<sc_cimtaugVal ts=\"-3\">15.55</sc_cimtaugVal>"
     << "<sc_cimtaugVal ts=\"-2\">16.23</sc_cimtaugVal>"
     << "<sc_cimtaugVal ts=\"-1\">19.9</sc_cimtaugVal>"
     << "<sc_cimtaugVal ts=\"1\">18.32</sc_cimtaugVal>"
     << "<sc_cimtaugVal ts=\"2\">15.97</sc_cimtaugVal>"
     << "<sc_cimtaugVal ts=\"3\">17.54</sc_cimtaugVal>"
     << "<sc_cimtaugVal ts=\"4\">17.46</sc_cimtaugVal>"
     << "<sc_cimtaugVal ts=\"5\">16.69</sc_cimtaugVal>"
     << "<sc_cimtaugVal ts=\"6\">17.48</sc_cimtaugVal>"
     << "</sc_ciMonthlyTempAug>"

     << "<sc_ciMonthlyTempSep>"
     << "<sc_cimtsepVal ts=\"-5\">13.72</sc_cimtsepVal>"
     << "<sc_cimtsepVal ts=\"-4\">17.95</sc_cimtsepVal>"
     << "<sc_cimtsepVal ts=\"-3\">11.19</sc_cimtsepVal>"
     << "<sc_cimtsepVal ts=\"-2\">16.39</sc_cimtsepVal>"
     << "<sc_cimtsepVal ts=\"-1\">5.87</sc_cimtsepVal>"
     << "<sc_cimtsepVal ts=\"1\">22.73</sc_cimtsepVal>"
     << "<sc_cimtsepVal ts=\"2\">20.94</sc_cimtsepVal>"
     << "<sc_cimtsepVal ts=\"3\">15.94</sc_cimtsepVal>"
     << "<sc_cimtsepVal ts=\"4\">18.87</sc_cimtsepVal>"
     << "<sc_cimtsepVal ts=\"5\">22.85</sc_cimtsepVal>"
     << "<sc_cimtsepVal ts=\"6\">19.53</sc_cimtsepVal>"
     << "</sc_ciMonthlyTempSep>"

     << "<sc_ciMonthlyTempOct>"
     << "<sc_cimtoctVal ts=\"-5\">2.83</sc_cimtoctVal>"
     << "<sc_cimtoctVal ts=\"-4\">7.09</sc_cimtoctVal>"
     << "<sc_cimtoctVal ts=\"-3\">10.7</sc_cimtoctVal>"
     << "<sc_cimtoctVal ts=\"-2\">2.84</sc_cimtoctVal>"
     << "<sc_cimtoctVal ts=\"-1\">4.3</sc_cimtoctVal>"
     << "<sc_cimtoctVal ts=\"1\">7.92</sc_cimtoctVal>"
     << "<sc_cimtoctVal ts=\"2\">8.18</sc_cimtoctVal>"
     << "<sc_cimtoctVal ts=\"3\">8.43</sc_cimtoctVal>"
     << "<sc_cimtoctVal ts=\"4\">8.68</sc_cimtoctVal>"
     << "<sc_cimtoctVal ts=\"5\">8.94</sc_cimtoctVal>"
     << "<sc_cimtoctVal ts=\"6\">9.19</sc_cimtoctVal>"
     << "</sc_ciMonthlyTempOct>"

     << "<sc_ciMonthlyTempNov>"
     << "<sc_cimtnovVal ts=\"-5\">-0.58</sc_cimtnovVal>"
     << "<sc_cimtnovVal ts=\"-4\">8.71</sc_cimtnovVal>"
     << "<sc_cimtnovVal ts=\"-3\">7.51</sc_cimtnovVal>"
     << "<sc_cimtnovVal ts=\"-2\">-0.57</sc_cimtnovVal>"
     << "<sc_cimtnovVal ts=\"-1\">1.98</sc_cimtnovVal>"
     << "<sc_cimtnovVal ts=\"1\">2.48</sc_cimtnovVal>"
     << "<sc_cimtnovVal ts=\"2\">2.56</sc_cimtnovVal>"
     << "<sc_cimtnovVal ts=\"3\">2.64</sc_cimtnovVal>"
     << "<sc_cimtnovVal ts=\"4\">2.72</sc_cimtnovVal>"
     << "<sc_cimtnovVal ts=\"5\">2.8</sc_cimtnovVal>"
     << "<sc_cimtnovVal ts=\"6\">2.88</sc_cimtnovVal>"
     << "</sc_ciMonthlyTempNov>"

     << "<sc_ciMonthlyTempDec>"
     << "<sc_cimtdecVal ts=\"-5\">2.34</sc_cimtdecVal>"
     << "<sc_cimtdecVal ts=\"-4\">-3.33</sc_cimtdecVal>"
     << "<sc_cimtdecVal ts=\"-3\">-0.66</sc_cimtdecVal>"
     << "<sc_cimtdecVal ts=\"-2\">3.22</sc_cimtdecVal>"
     << "<sc_cimtdecVal ts=\"-1\">0.6</sc_cimtdecVal>"
     << "<sc_cimtdecVal ts=\"1\">-9.6</sc_cimtdecVal>"
     << "<sc_cimtdecVal ts=\"2\">-6.94</sc_cimtdecVal>"
     << "<sc_cimtdecVal ts=\"3\">-6.51</sc_cimtdecVal>"
     << "<sc_cimtdecVal ts=\"4\">-1.59</sc_cimtdecVal>"
     << "<sc_cimtdecVal ts=\"5\">0.19</sc_cimtdecVal>"
     << "<sc_cimtdecVal ts=\"6\">2.49</sc_cimtdecVal>"
     << "</sc_ciMonthlyTempDec>"

     << "<sc_ciMonthlyPptJan>"
     << "<sc_cimpjanVal ts=\"-5\">156.75</sc_cimpjanVal>"
     << "<sc_cimpjanVal ts=\"-4\">200.8</sc_cimpjanVal>"
     << "<sc_cimpjanVal ts=\"-3\">76.15</sc_cimpjanVal>"
     << "<sc_cimpjanVal ts=\"-2\">144.61</sc_cimpjanVal>"
     << "<sc_cimpjanVal ts=\"-1\">81.05</sc_cimpjanVal>"
     << "<sc_cimpjanVal ts=\"1\">161.48</sc_cimpjanVal>"
     << "<sc_cimpjanVal ts=\"2\">152.09</sc_cimpjanVal>"
     << "<sc_cimpjanVal ts=\"3\">152.5</sc_cimpjanVal>"
     << "<sc_cimpjanVal ts=\"4\">152.71</sc_cimpjanVal>"
     << "<sc_cimpjanVal ts=\"5\">78.44</sc_cimpjanVal>"
     << "<sc_cimpjanVal ts=\"6\">123.19</sc_cimpjanVal>"
     << "</sc_ciMonthlyPptJan>"

     << "<sc_ciMonthlyPptFeb>"
     << "<sc_cimpfebVal ts=\"-5\">187.85</sc_cimpfebVal>"
     << "<sc_cimpfebVal ts=\"-4\">124.88</sc_cimpfebVal>"
     << "<sc_cimpfebVal ts=\"-3\">63.49</sc_cimpfebVal>"
     << "<sc_cimpfebVal ts=\"-2\">192.17</sc_cimpfebVal>"
     << "<sc_cimpfebVal ts=\"-1\">182.35</sc_cimpfebVal>"
     << "<sc_cimpfebVal ts=\"1\">199.32</sc_cimpfebVal>"
     << "<sc_cimpfebVal ts=\"2\">192.94</sc_cimpfebVal>"
     << "<sc_cimpfebVal ts=\"3\">188.1</sc_cimpfebVal>"
     << "<sc_cimpfebVal ts=\"4\">153.95</sc_cimpfebVal>"
     << "<sc_cimpfebVal ts=\"5\">89.79</sc_cimpfebVal>"
     << "<sc_cimpfebVal ts=\"6\">189.67</sc_cimpfebVal>"
     << "</sc_ciMonthlyPptFeb>"

     << "<sc_ciMonthlyPptMar>"
     << "<sc_cimpmarVal ts=\"-5\">208.64</sc_cimpmarVal>"
     << "<sc_cimpmarVal ts=\"-4\">233.06</sc_cimpmarVal>"
     << "<sc_cimpmarVal ts=\"-3\">246.05</sc_cimpmarVal>"
     << "<sc_cimpmarVal ts=\"-2\">183.98</sc_cimpmarVal>"
     << "<sc_cimpmarVal ts=\"-1\">144.42</sc_cimpmarVal>"
     << "<sc_cimpmarVal ts=\"1\">169.99</sc_cimpmarVal>"
     << "<sc_cimpmarVal ts=\"2\">105.49</sc_cimpmarVal>"
     << "<sc_cimpmarVal ts=\"3\">141.34</sc_cimpmarVal>"
     << "<sc_cimpmarVal ts=\"4\">84.71</sc_cimpmarVal>"
     << "<sc_cimpmarVal ts=\"5\">188.92</sc_cimpmarVal>"
     << "<sc_cimpmarVal ts=\"6\">93.47</sc_cimpmarVal>"
     << "</sc_ciMonthlyPptMar>"

     << "<sc_ciMonthlyPptApr>"
     << "<sc_cimpaprVal ts=\"-5\">61.72</sc_cimpaprVal>"
     << "<sc_cimpaprVal ts=\"-4\">197.01</sc_cimpaprVal>"
     << "<sc_cimpaprVal ts=\"-3\">146.71</sc_cimpaprVal>"
     << "<sc_cimpaprVal ts=\"-2\">173.62</sc_cimpaprVal>"
     << "<sc_cimpaprVal ts=\"-1\">50.19</sc_cimpaprVal>"
     << "<sc_cimpaprVal ts=\"1\">82.02</sc_cimpaprVal>"
     << "<sc_cimpaprVal ts=\"2\">77.49</sc_cimpaprVal>"
     << "<sc_cimpaprVal ts=\"3\">186.32</sc_cimpaprVal>"
     << "<sc_cimpaprVal ts=\"4\">174.4</sc_cimpaprVal>"
     << "<sc_cimpaprVal ts=\"5\">161.25</sc_cimpaprVal>"
     << "<sc_cimpaprVal ts=\"6\">99.76</sc_cimpaprVal>"
     << "</sc_ciMonthlyPptApr>"

     << "<sc_ciMonthlyPptMay>"
     << "<sc_cimpmayVal ts=\"-5\">98.88</sc_cimpmayVal>"
     << "<sc_cimpmayVal ts=\"-4\">221.62</sc_cimpmayVal>"
     << "<sc_cimpmayVal ts=\"-3\">245.51</sc_cimpmayVal>"
     << "<sc_cimpmayVal ts=\"-2\">227.17</sc_cimpmayVal>"
     << "<sc_cimpmayVal ts=\"-1\">157.19</sc_cimpmayVal>"
     << "<sc_cimpmayVal ts=\"1\">132.54</sc_cimpmayVal>"
     << "<sc_cimpmayVal ts=\"2\">121.74</sc_cimpmayVal>"
     << "<sc_cimpmayVal ts=\"3\">178.18</sc_cimpmayVal>"
     << "<sc_cimpmayVal ts=\"4\">102.86</sc_cimpmayVal>"
     << "<sc_cimpmayVal ts=\"5\">102.84</sc_cimpmayVal>"
     << "<sc_cimpmayVal ts=\"6\">172.41</sc_cimpmayVal>"
     << "</sc_ciMonthlyPptMay>"

     << "<sc_ciMonthlyPptJun>"
     << "<sc_cimpjunVal ts=\"-5\">144.55</sc_cimpjunVal>"
     << "<sc_cimpjunVal ts=\"-4\">142.87</sc_cimpjunVal>"
     << "<sc_cimpjunVal ts=\"-3\">184.78</sc_cimpjunVal>"
     << "<sc_cimpjunVal ts=\"-2\">249.3</sc_cimpjunVal>"
     << "<sc_cimpjunVal ts=\"-1\">201.05</sc_cimpjunVal>"
     << "<sc_cimpjunVal ts=\"1\">157.67</sc_cimpjunVal>"
     << "<sc_cimpjunVal ts=\"2\">133.89</sc_cimpjunVal>"
     << "<sc_cimpjunVal ts=\"3\">147.29</sc_cimpjunVal>"
     << "<sc_cimpjunVal ts=\"4\">123.74</sc_cimpjunVal>"
     << "<sc_cimpjunVal ts=\"5\">126.66</sc_cimpjunVal>"
     << "<sc_cimpjunVal ts=\"6\">134.35</sc_cimpjunVal>"
     << "</sc_ciMonthlyPptJun>"

     << "<sc_ciMonthlyPptJul>"
     << "<sc_cimpjulVal ts=\"-5\">96.74</sc_cimpjulVal>"
     << "<sc_cimpjulVal ts=\"-4\">198.29</sc_cimpjulVal>"
     << "<sc_cimpjulVal ts=\"-3\">56.77</sc_cimpjulVal>"
     << "<sc_cimpjulVal ts=\"-2\">55.16</sc_cimpjulVal>"
     << "<sc_cimpjulVal ts=\"-1\">174.6</sc_cimpjulVal>"
     << "<sc_cimpjulVal ts=\"1\">97.63</sc_cimpjulVal>"
     << "<sc_cimpjulVal ts=\"2\">141.94</sc_cimpjulVal>"
     << "<sc_cimpjulVal ts=\"3\">173.88</sc_cimpjulVal>"
     << "<sc_cimpjulVal ts=\"4\">166.53</sc_cimpjulVal>"
     << "<sc_cimpjulVal ts=\"5\">140.41</sc_cimpjulVal>"
     << "<sc_cimpjulVal ts=\"6\">128.89</sc_cimpjulVal>"
     << "</sc_ciMonthlyPptJul>"

     << "<sc_ciMonthlyPptAug>"
     << "<sc_cimpaugVal ts=\"-5\">250.84</sc_cimpaugVal>"
     << "<sc_cimpaugVal ts=\"-4\">145.97</sc_cimpaugVal>"
     << "<sc_cimpaugVal ts=\"-3\">104.14</sc_cimpaugVal>"
     << "<sc_cimpaugVal ts=\"-2\">99.69</sc_cimpaugVal>"
     << "<sc_cimpaugVal ts=\"-1\">59.28</sc_cimpaugVal>"
     << "<sc_cimpaugVal ts=\"1\">145.57</sc_cimpaugVal>"
     << "<sc_cimpaugVal ts=\"2\">156.69</sc_cimpaugVal>"
     << "<sc_cimpaugVal ts=\"3\">146.55</sc_cimpaugVal>"
     << "<sc_cimpaugVal ts=\"4\">167.73</sc_cimpaugVal>"
     << "<sc_cimpaugVal ts=\"5\">147.67</sc_cimpaugVal>"
     << "<sc_cimpaugVal ts=\"6\">119.52</sc_cimpaugVal>"
     << "</sc_ciMonthlyPptAug>"

     << "<sc_ciMonthlyPptSep>"
     << "<sc_cimpsepVal ts=\"-5\">154.02</sc_cimpsepVal>"
     << "<sc_cimpsepVal ts=\"-4\">124.84</sc_cimpsepVal>"
     << "<sc_cimpsepVal ts=\"-3\">142.08</sc_cimpsepVal>"
     << "<sc_cimpsepVal ts=\"-2\">207.51</sc_cimpsepVal>"
     << "<sc_cimpsepVal ts=\"-1\">87.88</sc_cimpsepVal>"
     << "<sc_cimpsepVal ts=\"1\">134.38</sc_cimpsepVal>"
     << "<sc_cimpsepVal ts=\"2\">89.78</sc_cimpsepVal>"
     << "<sc_cimpsepVal ts=\"3\">173.37</sc_cimpsepVal>"
     << "<sc_cimpsepVal ts=\"4\">146.16</sc_cimpsepVal>"
     << "<sc_cimpsepVal ts=\"5\">108.71</sc_cimpsepVal>"
     << "<sc_cimpsepVal ts=\"6\">90.68</sc_cimpsepVal>"
     << "</sc_ciMonthlyPptSep>"

     << "<sc_ciMonthlyPptOct>"
     << "<sc_cimpoctVal ts=\"-5\">129.54</sc_cimpoctVal>"
     << "<sc_cimpoctVal ts=\"-4\">72.4</sc_cimpoctVal>"
     << "<sc_cimpoctVal ts=\"-3\">162.74</sc_cimpoctVal>"
     << "<sc_cimpoctVal ts=\"-2\">51.89</sc_cimpoctVal>"
     << "<sc_cimpoctVal ts=\"-1\">98.17</sc_cimpoctVal>"
     << "<sc_cimpoctVal ts=\"1\">100.17</sc_cimpoctVal>"
     << "<sc_cimpoctVal ts=\"2\">178.11</sc_cimpoctVal>"
     << "<sc_cimpoctVal ts=\"3\">120.16</sc_cimpoctVal>"
     << "<sc_cimpoctVal ts=\"4\">198.43</sc_cimpoctVal>"
     << "<sc_cimpoctVal ts=\"5\">75.22</sc_cimpoctVal>"
     << "<sc_cimpoctVal ts=\"6\">198.3</sc_cimpoctVal>"
     << "</sc_ciMonthlyPptOct>"

     << "<sc_ciMonthlyPptNov>"
     << "<sc_cimpnovVal ts=\"-5\">186.31</sc_cimpnovVal>"
     << "<sc_cimpnovVal ts=\"-4\">74.2</sc_cimpnovVal>"
     << "<sc_cimpnovVal ts=\"-3\">68.19</sc_cimpnovVal>"
     << "<sc_cimpnovVal ts=\"-2\">197.74</sc_cimpnovVal>"
     << "<sc_cimpnovVal ts=\"-1\">222.2</sc_cimpnovVal>"
     << "<sc_cimpnovVal ts=\"1\">112.34</sc_cimpnovVal>"
     << "<sc_cimpnovVal ts=\"2\">191.22</sc_cimpnovVal>"
     << "<sc_cimpnovVal ts=\"3\">125.47</sc_cimpnovVal>"
     << "<sc_cimpnovVal ts=\"4\">79.8</sc_cimpnovVal>"
     << "<sc_cimpnovVal ts=\"5\">116.29</sc_cimpnovVal>"
     << "<sc_cimpnovVal ts=\"6\">146.75</sc_cimpnovVal>"
     << "</sc_ciMonthlyPptNov>"

     << "<sc_ciMonthlyPptDec>"
     << "<sc_cimpdecVal ts=\"-5\">168.86</sc_cimpdecVal>"
     << "<sc_cimpdecVal ts=\"-4\">153.39</sc_cimpdecVal>"
     << "<sc_cimpdecVal ts=\"-3\">80.31</sc_cimpdecVal>"
     << "<sc_cimpdecVal ts=\"-2\">203.43</sc_cimpdecVal>"
     << "<sc_cimpdecVal ts=\"-1\">50.59</sc_cimpdecVal>"
     << "<sc_cimpdecVal ts=\"1\">137.22</sc_cimpdecVal>"
     << "<sc_cimpdecVal ts=\"2\">101.29</sc_cimpdecVal>"
     << "<sc_cimpdecVal ts=\"3\">159.21</sc_cimpdecVal>"
     << "<sc_cimpdecVal ts=\"4\">171.75</sc_cimpdecVal>"
     << "<sc_cimpdecVal ts=\"5\">191.54</sc_cimpdecVal>"
     << "<sc_cimpdecVal ts=\"6\">131.83</sc_cimpdecVal>"
     << "</sc_ciMonthlyPptDec>"

     << "<sc_ciJanRad>7468.475</sc_ciJanRad>"
     << "<sc_ciFebRad>10353.32</sc_ciFebRad>"
     << "<sc_ciMarRad>17453.07</sc_ciMarRad>"
     << "<sc_ciAprRad>22721.85</sc_ciAprRad>"
     << "<sc_ciMayRad>27901.37</sc_ciMayRad>"
     << "<sc_ciJunRad>28677.54</sc_ciJunRad>"
     << "<sc_ciJulRad>28764.65</sc_ciJulRad>"
     << "<sc_ciAugRad>25075.4</sc_ciAugRad>"
     << "<sc_ciSepRad>19259.27</sc_ciSepRad>"
     << "<sc_ciOctRad>12609.6</sc_ciOctRad>"
     << "<sc_ciNovRad>7988.013</sc_ciNovRad>"
     << "<sc_ciDecRad>6307.151</sc_ciDecRad>"

     << "</ClimateImporter1>"
     << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteClimateImporterXMLFile3()
/////////////////////////////////////////////////////////////////////////////
const char* WriteClimateImporterXMLFile3()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  std::fstream oOut;
  oOut.open( cFileString, ios::out | ios::trunc );

  WriteClimateImporterCommonStuff(oOut);

  oOut << "<ClimateImporter1>"
     << "<sc_ciAWS>60.9</sc_ciAWS>"
     << "<sc_ciCalendarMean>1</sc_ciCalendarMean>"
     << "<sc_ciLTM>4</sc_ciLTM>"

     << "<sc_ciMonthlyTempJan>"
     << "<sc_cimtjanVal ts=\"-3\">-1.51</sc_cimtjanVal>"
     << "<sc_cimtjanVal ts=\"-2\">5.03</sc_cimtjanVal>"
     << "<sc_cimtjanVal ts=\"-1\">-5.5</sc_cimtjanVal>"
     << "<sc_cimtjanVal ts=\"1\">-2.57</sc_cimtjanVal>"
     << "<sc_cimtjanVal ts=\"2\">-3.46</sc_cimtjanVal>"
     << "<sc_cimtjanVal ts=\"3\">-6.93</sc_cimtjanVal>"
     << "<sc_cimtjanVal ts=\"4\">-7.76</sc_cimtjanVal>"
     << "<sc_cimtjanVal ts=\"5\">-0.72</sc_cimtjanVal>"
     << "<sc_cimtjanVal ts=\"6\">1.3</sc_cimtjanVal>"
     << "</sc_ciMonthlyTempJan>"

     << "<sc_ciMonthlyTempFeb>"
     << "<sc_cimtfebVal ts=\"-3\">2.16</sc_cimtfebVal>"
     << "<sc_cimtfebVal ts=\"-2\">4.5</sc_cimtfebVal>"
     << "<sc_cimtfebVal ts=\"-1\">-0.6</sc_cimtfebVal>"
     << "<sc_cimtfebVal ts=\"1\">2.75</sc_cimtfebVal>"
     << "<sc_cimtfebVal ts=\"2\">-8.57</sc_cimtfebVal>"
     << "<sc_cimtfebVal ts=\"3\">1.98</sc_cimtfebVal>"
     << "<sc_cimtfebVal ts=\"4\">-7.5</sc_cimtfebVal>"
     << "<sc_cimtfebVal ts=\"5\">-2.44</sc_cimtfebVal>"
     << "<sc_cimtfebVal ts=\"6\">-9.36</sc_cimtfebVal>"
     << "</sc_ciMonthlyTempFeb>"

     << "<sc_ciMonthlyTempMar>"
     << "<sc_cimtmarVal ts=\"-3\">7.49</sc_cimtmarVal>"
     << "<sc_cimtmarVal ts=\"-2\">6.95</sc_cimtmarVal>"
     << "<sc_cimtmarVal ts=\"-1\">1.54</sc_cimtmarVal>"
     << "<sc_cimtmarVal ts=\"1\">2.94</sc_cimtmarVal>"
     << "<sc_cimtmarVal ts=\"2\">0.28</sc_cimtmarVal>"
     << "<sc_cimtmarVal ts=\"3\">0.3</sc_cimtmarVal>"
     << "<sc_cimtmarVal ts=\"4\">-0.78</sc_cimtmarVal>"
     << "<sc_cimtmarVal ts=\"5\">4.85</sc_cimtmarVal>"
     << "<sc_cimtmarVal ts=\"6\">3.78</sc_cimtmarVal>"
     << "</sc_ciMonthlyTempMar>"

     << "<sc_ciMonthlyTempApr>"
     << "<sc_cimtaprVal ts=\"-3\">6.21</sc_cimtaprVal>"
     << "<sc_cimtaprVal ts=\"-2\">11.68</sc_cimtaprVal>"
     << "<sc_cimtaprVal ts=\"-1\">8.66</sc_cimtaprVal>"
     << "<sc_cimtaprVal ts=\"1\">2.17</sc_cimtaprVal>"
     << "<sc_cimtaprVal ts=\"2\">5.9</sc_cimtaprVal>"
     << "<sc_cimtaprVal ts=\"3\">7.17</sc_cimtaprVal>"
     << "<sc_cimtaprVal ts=\"4\">8.67</sc_cimtaprVal>"
     << "<sc_cimtaprVal ts=\"5\">5.61</sc_cimtaprVal>"
     << "<sc_cimtaprVal ts=\"6\">4.56</sc_cimtaprVal>"
     << "</sc_ciMonthlyTempApr>"

     << "<sc_ciMonthlyTempMay>"
     << "<sc_cimtmayVal ts=\"-3\">7.66</sc_cimtmayVal>"
     << "<sc_cimtmayVal ts=\"-2\">12.52</sc_cimtmayVal>"
     << "<sc_cimtmayVal ts=\"-1\">10.68</sc_cimtmayVal>"
     << "<sc_cimtmayVal ts=\"1\">7.25</sc_cimtmayVal>"
     << "<sc_cimtmayVal ts=\"2\">7.6</sc_cimtmayVal>"
     << "<sc_cimtmayVal ts=\"3\">9.46</sc_cimtmayVal>"
     << "<sc_cimtmayVal ts=\"4\">11.26</sc_cimtmayVal>"
     << "<sc_cimtmayVal ts=\"5\">7.6</sc_cimtmayVal>"
     << "<sc_cimtmayVal ts=\"6\">6.9</sc_cimtmayVal>"
     << "</sc_ciMonthlyTempMay>"

     << "<sc_ciMonthlyTempJun>"
     << "<sc_cimtjunVal ts=\"-3\">10.1</sc_cimtjunVal>"
     << "<sc_cimtjunVal ts=\"-2\">14.33</sc_cimtjunVal>"
     << "<sc_cimtjunVal ts=\"-1\">16.65</sc_cimtjunVal>"
     << "<sc_cimtjunVal ts=\"1\">11.05</sc_cimtjunVal>"
     << "<sc_cimtjunVal ts=\"2\">17.16</sc_cimtjunVal>"
     << "<sc_cimtjunVal ts=\"3\">11.06</sc_cimtjunVal>"
     << "<sc_cimtjunVal ts=\"4\">17.72</sc_cimtjunVal>"
     << "<sc_cimtjunVal ts=\"5\">14.05</sc_cimtjunVal>"
     << "<sc_cimtjunVal ts=\"6\">13.52</sc_cimtjunVal>"
     << "</sc_ciMonthlyTempJun>"

     << "<sc_ciMonthlyTempJul>"
     << "<sc_cimtjulVal ts=\"-3\">15.24</sc_cimtjulVal>"
     << "<sc_cimtjulVal ts=\"-2\">17.87</sc_cimtjulVal>"
     << "<sc_cimtjulVal ts=\"-1\">14.13</sc_cimtjulVal>"
     << "<sc_cimtjulVal ts=\"1\">16.82</sc_cimtjulVal>"
     << "<sc_cimtjulVal ts=\"2\">22</sc_cimtjulVal>"
     << "<sc_cimtjulVal ts=\"3\">18.34</sc_cimtjulVal>"
     << "<sc_cimtjulVal ts=\"4\">20.99</sc_cimtjulVal>"
     << "<sc_cimtjulVal ts=\"5\">15.46</sc_cimtjulVal>"
     << "<sc_cimtjulVal ts=\"6\">15.74</sc_cimtjulVal>"
     << "</sc_ciMonthlyTempJul>"

     << "<sc_ciMonthlyTempAug>"
     << "<sc_cimtaugVal ts=\"-3\">15.55</sc_cimtaugVal>"
     << "<sc_cimtaugVal ts=\"-2\">16.23</sc_cimtaugVal>"
     << "<sc_cimtaugVal ts=\"-1\">19.9</sc_cimtaugVal>"
     << "<sc_cimtaugVal ts=\"1\">18.32</sc_cimtaugVal>"
     << "<sc_cimtaugVal ts=\"2\">15.97</sc_cimtaugVal>"
     << "<sc_cimtaugVal ts=\"3\">17.54</sc_cimtaugVal>"
     << "<sc_cimtaugVal ts=\"4\">17.46</sc_cimtaugVal>"
     << "<sc_cimtaugVal ts=\"5\">16.69</sc_cimtaugVal>"
     << "<sc_cimtaugVal ts=\"6\">17.48</sc_cimtaugVal>"
     << "</sc_ciMonthlyTempAug>"

     << "<sc_ciMonthlyTempSep>"
     << "<sc_cimtsepVal ts=\"-3\">11.19</sc_cimtsepVal>"
     << "<sc_cimtsepVal ts=\"-2\">16.39</sc_cimtsepVal>"
     << "<sc_cimtsepVal ts=\"-1\">5.87</sc_cimtsepVal>"
     << "<sc_cimtsepVal ts=\"1\">22.73</sc_cimtsepVal>"
     << "<sc_cimtsepVal ts=\"2\">20.94</sc_cimtsepVal>"
     << "<sc_cimtsepVal ts=\"3\">15.94</sc_cimtsepVal>"
     << "<sc_cimtsepVal ts=\"4\">18.87</sc_cimtsepVal>"
     << "<sc_cimtsepVal ts=\"5\">22.85</sc_cimtsepVal>"
     << "<sc_cimtsepVal ts=\"6\">19.53</sc_cimtsepVal>"
     << "</sc_ciMonthlyTempSep>"

     << "<sc_ciMonthlyTempOct>"
     << "<sc_cimtoctVal ts=\"-3\">10.7</sc_cimtoctVal>"
     << "<sc_cimtoctVal ts=\"-2\">2.84</sc_cimtoctVal>"
     << "<sc_cimtoctVal ts=\"-1\">4.3</sc_cimtoctVal>"
     << "<sc_cimtoctVal ts=\"1\">7.92</sc_cimtoctVal>"
     << "<sc_cimtoctVal ts=\"2\">8.18</sc_cimtoctVal>"
     << "<sc_cimtoctVal ts=\"3\">8.43</sc_cimtoctVal>"
     << "<sc_cimtoctVal ts=\"4\">8.68</sc_cimtoctVal>"
     << "<sc_cimtoctVal ts=\"5\">8.94</sc_cimtoctVal>"
     << "<sc_cimtoctVal ts=\"6\">9.19</sc_cimtoctVal>"
     << "</sc_ciMonthlyTempOct>"

     << "<sc_ciMonthlyTempNov>"
     << "<sc_cimtnovVal ts=\"-3\">7.51</sc_cimtnovVal>"
     << "<sc_cimtnovVal ts=\"-2\">-0.57</sc_cimtnovVal>"
     << "<sc_cimtnovVal ts=\"-1\">1.98</sc_cimtnovVal>"
     << "<sc_cimtnovVal ts=\"1\">2.48</sc_cimtnovVal>"
     << "<sc_cimtnovVal ts=\"2\">2.56</sc_cimtnovVal>"
     << "<sc_cimtnovVal ts=\"3\">2.64</sc_cimtnovVal>"
     << "<sc_cimtnovVal ts=\"4\">2.72</sc_cimtnovVal>"
     << "<sc_cimtnovVal ts=\"5\">2.8</sc_cimtnovVal>"
     << "<sc_cimtnovVal ts=\"6\">2.88</sc_cimtnovVal>"
     << "</sc_ciMonthlyTempNov>"

     << "<sc_ciMonthlyTempDec>"
     << "<sc_cimtdecVal ts=\"-3\">-0.66</sc_cimtdecVal>"
     << "<sc_cimtdecVal ts=\"-2\">3.22</sc_cimtdecVal>"
     << "<sc_cimtdecVal ts=\"-1\">0.6</sc_cimtdecVal>"
     << "<sc_cimtdecVal ts=\"1\">-9.6</sc_cimtdecVal>"
     << "<sc_cimtdecVal ts=\"2\">-6.94</sc_cimtdecVal>"
     << "<sc_cimtdecVal ts=\"3\">-6.51</sc_cimtdecVal>"
     << "<sc_cimtdecVal ts=\"4\">-1.59</sc_cimtdecVal>"
     << "<sc_cimtdecVal ts=\"5\">0.19</sc_cimtdecVal>"
     << "<sc_cimtdecVal ts=\"6\">2.49</sc_cimtdecVal>"
     << "</sc_ciMonthlyTempDec>"

     << "<sc_ciMonthlyPptJan>"
     << "<sc_cimpjanVal ts=\"-3\">76.15</sc_cimpjanVal>"
     << "<sc_cimpjanVal ts=\"-2\">144.61</sc_cimpjanVal>"
     << "<sc_cimpjanVal ts=\"-1\">81.05</sc_cimpjanVal>"
     << "<sc_cimpjanVal ts=\"1\">161.48</sc_cimpjanVal>"
     << "<sc_cimpjanVal ts=\"2\">152.09</sc_cimpjanVal>"
     << "<sc_cimpjanVal ts=\"3\">152.5</sc_cimpjanVal>"
     << "<sc_cimpjanVal ts=\"4\">152.71</sc_cimpjanVal>"
     << "<sc_cimpjanVal ts=\"5\">78.44</sc_cimpjanVal>"
     << "<sc_cimpjanVal ts=\"6\">123.19</sc_cimpjanVal>"
     << "</sc_ciMonthlyPptJan>"

     << "<sc_ciMonthlyPptFeb>"
     << "<sc_cimpfebVal ts=\"-3\">63.49</sc_cimpfebVal>"
     << "<sc_cimpfebVal ts=\"-2\">192.17</sc_cimpfebVal>"
     << "<sc_cimpfebVal ts=\"-1\">182.35</sc_cimpfebVal>"
     << "<sc_cimpfebVal ts=\"1\">199.32</sc_cimpfebVal>"
     << "<sc_cimpfebVal ts=\"2\">192.94</sc_cimpfebVal>"
     << "<sc_cimpfebVal ts=\"3\">188.1</sc_cimpfebVal>"
     << "<sc_cimpfebVal ts=\"4\">153.95</sc_cimpfebVal>"
     << "<sc_cimpfebVal ts=\"5\">89.79</sc_cimpfebVal>"
     << "<sc_cimpfebVal ts=\"6\">189.67</sc_cimpfebVal>"
     << "</sc_ciMonthlyPptFeb>"

     << "<sc_ciMonthlyPptMar>"
     << "<sc_cimpmarVal ts=\"-3\">246.05</sc_cimpmarVal>"
     << "<sc_cimpmarVal ts=\"-2\">183.98</sc_cimpmarVal>"
     << "<sc_cimpmarVal ts=\"-1\">144.42</sc_cimpmarVal>"
     << "<sc_cimpmarVal ts=\"1\">169.99</sc_cimpmarVal>"
     << "<sc_cimpmarVal ts=\"2\">105.49</sc_cimpmarVal>"
     << "<sc_cimpmarVal ts=\"3\">141.34</sc_cimpmarVal>"
     << "<sc_cimpmarVal ts=\"4\">84.71</sc_cimpmarVal>"
     << "<sc_cimpmarVal ts=\"5\">188.92</sc_cimpmarVal>"
     << "<sc_cimpmarVal ts=\"6\">93.47</sc_cimpmarVal>"
     << "</sc_ciMonthlyPptMar>"

     << "<sc_ciMonthlyPptApr>"
     << "<sc_cimpaprVal ts=\"-3\">146.71</sc_cimpaprVal>"
     << "<sc_cimpaprVal ts=\"-2\">173.62</sc_cimpaprVal>"
     << "<sc_cimpaprVal ts=\"-1\">50.19</sc_cimpaprVal>"
     << "<sc_cimpaprVal ts=\"1\">82.02</sc_cimpaprVal>"
     << "<sc_cimpaprVal ts=\"2\">77.49</sc_cimpaprVal>"
     << "<sc_cimpaprVal ts=\"3\">186.32</sc_cimpaprVal>"
     << "<sc_cimpaprVal ts=\"4\">174.4</sc_cimpaprVal>"
     << "<sc_cimpaprVal ts=\"5\">161.25</sc_cimpaprVal>"
     << "<sc_cimpaprVal ts=\"6\">99.76</sc_cimpaprVal>"
     << "</sc_ciMonthlyPptApr>"

     << "<sc_ciMonthlyPptMay>"
     << "<sc_cimpmayVal ts=\"-3\">245.51</sc_cimpmayVal>"
     << "<sc_cimpmayVal ts=\"-2\">227.17</sc_cimpmayVal>"
     << "<sc_cimpmayVal ts=\"-1\">157.19</sc_cimpmayVal>"
     << "<sc_cimpmayVal ts=\"1\">132.54</sc_cimpmayVal>"
     << "<sc_cimpmayVal ts=\"2\">121.74</sc_cimpmayVal>"
     << "<sc_cimpmayVal ts=\"3\">178.18</sc_cimpmayVal>"
     << "<sc_cimpmayVal ts=\"4\">102.86</sc_cimpmayVal>"
     << "<sc_cimpmayVal ts=\"5\">102.84</sc_cimpmayVal>"
     << "<sc_cimpmayVal ts=\"6\">172.41</sc_cimpmayVal>"
     << "</sc_ciMonthlyPptMay>"

     << "<sc_ciMonthlyPptJun>"
     << "<sc_cimpjunVal ts=\"-3\">184.78</sc_cimpjunVal>"
     << "<sc_cimpjunVal ts=\"-2\">249.3</sc_cimpjunVal>"
     << "<sc_cimpjunVal ts=\"-1\">201.05</sc_cimpjunVal>"
     << "<sc_cimpjunVal ts=\"1\">157.67</sc_cimpjunVal>"
     << "<sc_cimpjunVal ts=\"2\">133.89</sc_cimpjunVal>"
     << "<sc_cimpjunVal ts=\"3\">147.29</sc_cimpjunVal>"
     << "<sc_cimpjunVal ts=\"4\">123.74</sc_cimpjunVal>"
     << "<sc_cimpjunVal ts=\"5\">126.66</sc_cimpjunVal>"
     << "<sc_cimpjunVal ts=\"6\">134.35</sc_cimpjunVal>"
     << "</sc_ciMonthlyPptJun>"

     << "<sc_ciMonthlyPptJul>"
     << "<sc_cimpjulVal ts=\"-3\">56.77</sc_cimpjulVal>"
     << "<sc_cimpjulVal ts=\"-2\">55.16</sc_cimpjulVal>"
     << "<sc_cimpjulVal ts=\"-1\">174.6</sc_cimpjulVal>"
     << "<sc_cimpjulVal ts=\"1\">97.63</sc_cimpjulVal>"
     << "<sc_cimpjulVal ts=\"2\">141.94</sc_cimpjulVal>"
     << "<sc_cimpjulVal ts=\"3\">173.88</sc_cimpjulVal>"
     << "<sc_cimpjulVal ts=\"4\">166.53</sc_cimpjulVal>"
     << "<sc_cimpjulVal ts=\"5\">140.41</sc_cimpjulVal>"
     << "<sc_cimpjulVal ts=\"6\">128.89</sc_cimpjulVal>"
     << "</sc_ciMonthlyPptJul>"

     << "<sc_ciMonthlyPptAug>"
     << "<sc_cimpaugVal ts=\"-3\">104.14</sc_cimpaugVal>"
     << "<sc_cimpaugVal ts=\"-2\">99.69</sc_cimpaugVal>"
     << "<sc_cimpaugVal ts=\"-1\">59.28</sc_cimpaugVal>"
     << "<sc_cimpaugVal ts=\"1\">145.57</sc_cimpaugVal>"
     << "<sc_cimpaugVal ts=\"2\">156.69</sc_cimpaugVal>"
     << "<sc_cimpaugVal ts=\"3\">146.55</sc_cimpaugVal>"
     << "<sc_cimpaugVal ts=\"4\">167.73</sc_cimpaugVal>"
     << "<sc_cimpaugVal ts=\"5\">147.67</sc_cimpaugVal>"
     << "<sc_cimpaugVal ts=\"6\">119.52</sc_cimpaugVal>"
     << "</sc_ciMonthlyPptAug>"

     << "<sc_ciMonthlyPptSep>"
     << "<sc_cimpsepVal ts=\"-3\">142.08</sc_cimpsepVal>"
     << "<sc_cimpsepVal ts=\"-2\">207.51</sc_cimpsepVal>"
     << "<sc_cimpsepVal ts=\"-1\">87.88</sc_cimpsepVal>"
     << "<sc_cimpsepVal ts=\"1\">134.38</sc_cimpsepVal>"
     << "<sc_cimpsepVal ts=\"2\">89.78</sc_cimpsepVal>"
     << "<sc_cimpsepVal ts=\"3\">173.37</sc_cimpsepVal>"
     << "<sc_cimpsepVal ts=\"4\">146.16</sc_cimpsepVal>"
     << "<sc_cimpsepVal ts=\"5\">108.71</sc_cimpsepVal>"
     << "<sc_cimpsepVal ts=\"6\">90.68</sc_cimpsepVal>"
     << "</sc_ciMonthlyPptSep>"

     << "<sc_ciMonthlyPptOct>"
     << "<sc_cimpoctVal ts=\"-3\">162.74</sc_cimpoctVal>"
     << "<sc_cimpoctVal ts=\"-2\">51.89</sc_cimpoctVal>"
     << "<sc_cimpoctVal ts=\"-1\">98.17</sc_cimpoctVal>"
     << "<sc_cimpoctVal ts=\"1\">100.17</sc_cimpoctVal>"
     << "<sc_cimpoctVal ts=\"2\">178.11</sc_cimpoctVal>"
     << "<sc_cimpoctVal ts=\"3\">120.16</sc_cimpoctVal>"
     << "<sc_cimpoctVal ts=\"4\">198.43</sc_cimpoctVal>"
     << "<sc_cimpoctVal ts=\"5\">75.22</sc_cimpoctVal>"
     << "<sc_cimpoctVal ts=\"6\">198.3</sc_cimpoctVal>"
     << "</sc_ciMonthlyPptOct>"

     << "<sc_ciMonthlyPptNov>"
     << "<sc_cimpnovVal ts=\"-3\">68.19</sc_cimpnovVal>"
     << "<sc_cimpnovVal ts=\"-2\">197.74</sc_cimpnovVal>"
     << "<sc_cimpnovVal ts=\"-1\">222.2</sc_cimpnovVal>"
     << "<sc_cimpnovVal ts=\"1\">112.34</sc_cimpnovVal>"
     << "<sc_cimpnovVal ts=\"2\">191.22</sc_cimpnovVal>"
     << "<sc_cimpnovVal ts=\"3\">125.47</sc_cimpnovVal>"
     << "<sc_cimpnovVal ts=\"4\">79.8</sc_cimpnovVal>"
     << "<sc_cimpnovVal ts=\"5\">116.29</sc_cimpnovVal>"
     << "<sc_cimpnovVal ts=\"6\">146.75</sc_cimpnovVal>"
     << "</sc_ciMonthlyPptNov>"

     << "<sc_ciMonthlyPptDec>"
     << "<sc_cimpdecVal ts=\"-3\">80.31</sc_cimpdecVal>"
     << "<sc_cimpdecVal ts=\"-2\">203.43</sc_cimpdecVal>"
     << "<sc_cimpdecVal ts=\"-1\">50.59</sc_cimpdecVal>"
     << "<sc_cimpdecVal ts=\"1\">137.22</sc_cimpdecVal>"
     << "<sc_cimpdecVal ts=\"2\">101.29</sc_cimpdecVal>"
     << "<sc_cimpdecVal ts=\"3\">159.21</sc_cimpdecVal>"
     << "<sc_cimpdecVal ts=\"4\">171.75</sc_cimpdecVal>"
     << "<sc_cimpdecVal ts=\"5\">191.54</sc_cimpdecVal>"
     << "<sc_cimpdecVal ts=\"6\">131.83</sc_cimpdecVal>"
     << "</sc_ciMonthlyPptDec>"

     << "<sc_ciJanRad>7468.475</sc_ciJanRad>"
     << "<sc_ciFebRad>10353.32</sc_ciFebRad>"
     << "<sc_ciMarRad>17453.07</sc_ciMarRad>"
     << "<sc_ciAprRad>22721.85</sc_ciAprRad>"
     << "<sc_ciMayRad>27901.37</sc_ciMayRad>"
     << "<sc_ciJunRad>28677.54</sc_ciJunRad>"
     << "<sc_ciJulRad>28764.65</sc_ciJulRad>"
     << "<sc_ciAugRad>25075.4</sc_ciAugRad>"
     << "<sc_ciSepRad>19259.27</sc_ciSepRad>"
     << "<sc_ciOctRad>12609.6</sc_ciOctRad>"
     << "<sc_ciNovRad>7988.013</sc_ciNovRad>"
     << "<sc_ciDecRad>6307.151</sc_ciDecRad>"

     << "</ClimateImporter1>"
     << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteClimateImporterXMLErrorFile1()
/////////////////////////////////////////////////////////////////////////////
const char* WriteClimateImporterXMLErrorFile1()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
	std::fstream oOut;
	oOut.open( cFileString, ios::out | ios::trunc );

	WriteClimateImporterCommonStuff(oOut);

  oOut << "<ClimateImporter1>"
	     << "<sc_ciAWS>60.9</sc_ciAWS>"

  		 << "<sc_ciMonthlyTempJan>"
	  	 << "<sc_cimtjanVal ts=\"1\">-2.57</sc_cimtjanVal>"
		   << "<sc_cimtjanVal ts=\"2\">-3.46</sc_cimtjanVal>"
  		 << "<sc_cimtjanVal ts=\"3\">-6.93</sc_cimtjanVal>"
		   << "<sc_cimtjanVal ts=\"4\">-7.76</sc_cimtjanVal>"
       << "<sc_cimtjanVal ts=\"5\">-0.72</sc_cimtjanVal>"
       << "<sc_cimtjanVal ts=\"6\">1.3</sc_cimtjanVal>"
    	 << "</sc_ciMonthlyTempJan>"

		 << "<sc_ciMonthlyTempFeb>"
		 << "<sc_cimtfebVal ts=\"1\">2.75</sc_cimtfebVal>"
		 << "<sc_cimtfebVal ts=\"2\">-8.57</sc_cimtfebVal>"
		 << "<sc_cimtfebVal ts=\"3\">1.98</sc_cimtfebVal>"
		 << "<sc_cimtfebVal ts=\"4\">-7.5</sc_cimtfebVal>"
		 << "<sc_cimtfebVal ts=\"5\">-2.44</sc_cimtfebVal>"
		 << "<sc_cimtfebVal ts=\"6\">-9.36</sc_cimtfebVal>"
		 << "</sc_ciMonthlyTempFeb>"

		 << "<sc_ciMonthlyTempMar>"
		 << "<sc_cimtmarVal ts=\"1\">2.94</sc_cimtmarVal>"
		 << "<sc_cimtmarVal ts=\"2\">0.28</sc_cimtmarVal>"
		 << "<sc_cimtmarVal ts=\"3\">0.3</sc_cimtmarVal>"
		 << "<sc_cimtmarVal ts=\"4\">-0.78</sc_cimtmarVal>"
		 << "<sc_cimtmarVal ts=\"5\">4.85</sc_cimtmarVal>"
		 << "<sc_cimtmarVal ts=\"6\">3.78</sc_cimtmarVal>"
		 << "</sc_ciMonthlyTempMar>"

		 << "<sc_ciMonthlyTempApr>"
		 << "<sc_cimtaprVal ts=\"1\">2.17</sc_cimtaprVal>"
		 << "<sc_cimtaprVal ts=\"2\">5.9</sc_cimtaprVal>"
		 << "<sc_cimtaprVal ts=\"3\">7.17</sc_cimtaprVal>"
		 << "<sc_cimtaprVal ts=\"4\">8.67</sc_cimtaprVal>"
		 << "<sc_cimtaprVal ts=\"5\">5.61</sc_cimtaprVal>"
		 << "<sc_cimtaprVal ts=\"6\">4.56</sc_cimtaprVal>"
		 << "</sc_ciMonthlyTempApr>"

		 << "<sc_ciMonthlyTempMay>"
		 << "<sc_cimtmayVal ts=\"1\">7.25</sc_cimtmayVal>"
		 << "<sc_cimtmayVal ts=\"2\">7.6</sc_cimtmayVal>"
		 << "<sc_cimtmayVal ts=\"3\">9.46</sc_cimtmayVal>"
		 << "<sc_cimtmayVal ts=\"4\">11.26</sc_cimtmayVal>"
		 << "<sc_cimtmayVal ts=\"5\">7.6</sc_cimtmayVal>"
		 << "<sc_cimtmayVal ts=\"6\">6.9</sc_cimtmayVal>"
		 << "</sc_ciMonthlyTempMay>"

		 << "<sc_ciMonthlyTempJun>"
		 << "<sc_cimtjunVal ts=\"1\">11.05</sc_cimtjunVal>"
		 << "<sc_cimtjunVal ts=\"2\">17.16</sc_cimtjunVal>"
		 << "<sc_cimtjunVal ts=\"3\">11.06</sc_cimtjunVal>"
		 << "<sc_cimtjunVal ts=\"4\">17.72</sc_cimtjunVal>"
		 << "<sc_cimtjunVal ts=\"5\">14.05</sc_cimtjunVal>"
		 << "<sc_cimtjunVal ts=\"6\">13.52</sc_cimtjunVal>"
		 << "</sc_ciMonthlyTempJun>"

		 << "<sc_ciMonthlyTempJul>"
		 << "<sc_cimtjulVal ts=\"1\">16.82</sc_cimtjulVal>"
		 << "<sc_cimtjulVal ts=\"2\">22</sc_cimtjulVal>"
		 << "<sc_cimtjulVal ts=\"3\">18.34</sc_cimtjulVal>"
		 << "<sc_cimtjulVal ts=\"4\">20.99</sc_cimtjulVal>"
		 << "<sc_cimtjulVal ts=\"5\">15.46</sc_cimtjulVal>"
		 << "<sc_cimtjulVal ts=\"6\">15.74</sc_cimtjulVal>"
		 << "</sc_ciMonthlyTempJul>"

		 << "<sc_ciMonthlyTempAug>"
		 << "<sc_cimtaugVal ts=\"1\">18.32</sc_cimtaugVal>"
		 << "<sc_cimtaugVal ts=\"2\">15.97</sc_cimtaugVal>"
		 << "<sc_cimtaugVal ts=\"3\">17.54</sc_cimtaugVal>"
		 << "<sc_cimtaugVal ts=\"4\">17.46</sc_cimtaugVal>"
		 << "<sc_cimtaugVal ts=\"5\">16.69</sc_cimtaugVal>"
		 << "<sc_cimtaugVal ts=\"6\">17.48</sc_cimtaugVal>"
		 << "</sc_ciMonthlyTempAug>"

		 << "<sc_ciMonthlyTempSep>"
		 << "<sc_cimtsepVal ts=\"1\">22.73</sc_cimtsepVal>"
		 << "<sc_cimtsepVal ts=\"2\">20.94</sc_cimtsepVal>"
		 << "<sc_cimtsepVal ts=\"3\">15.94</sc_cimtsepVal>"
		 << "<sc_cimtsepVal ts=\"4\">18.87</sc_cimtsepVal>"
		 << "<sc_cimtsepVal ts=\"5\">22.85</sc_cimtsepVal>"
		 << "<sc_cimtsepVal ts=\"6\">19.53</sc_cimtsepVal>"
		 << "</sc_ciMonthlyTempSep>"

		 << "<sc_ciMonthlyTempOct>"
		 << "<sc_cimtoctVal ts=\"1\">7.92</sc_cimtoctVal>"
		 << "<sc_cimtoctVal ts=\"2\">8.18</sc_cimtoctVal>"
		 << "<sc_cimtoctVal ts=\"3\">8.43</sc_cimtoctVal>"
		 << "<sc_cimtoctVal ts=\"4\">8.68</sc_cimtoctVal>"
		 << "<sc_cimtoctVal ts=\"5\">8.94</sc_cimtoctVal>"
		 << "<sc_cimtoctVal ts=\"6\">9.19</sc_cimtoctVal>"
		 << "</sc_ciMonthlyTempOct>"

		 << "<sc_ciMonthlyTempNov>"
		 << "<sc_cimtnovVal ts=\"1\">2.48</sc_cimtnovVal>"
		 << "<sc_cimtnovVal ts=\"2\">2.56</sc_cimtnovVal>"
		 << "<sc_cimtnovVal ts=\"3\">2.64</sc_cimtnovVal>"
		 << "<sc_cimtnovVal ts=\"4\">2.72</sc_cimtnovVal>"
		 << "<sc_cimtnovVal ts=\"5\">2.8</sc_cimtnovVal>"
		 << "<sc_cimtnovVal ts=\"6\">2.88</sc_cimtnovVal>"
		 << "</sc_ciMonthlyTempNov>"

		 << "<sc_ciMonthlyTempDec>"
		 << "<sc_cimtdecVal ts=\"1\">-9.6</sc_cimtdecVal>"
		 << "<sc_cimtdecVal ts=\"2\">-6.94</sc_cimtdecVal>"
		 << "<sc_cimtdecVal ts=\"3\">-6.51</sc_cimtdecVal>"
		 << "<sc_cimtdecVal ts=\"4\">-1.59</sc_cimtdecVal>"
		 << "<sc_cimtdecVal ts=\"5\">0.19</sc_cimtdecVal>"
		 << "<sc_cimtdecVal ts=\"6\">2.49</sc_cimtdecVal>"
		 << "</sc_ciMonthlyTempDec>"

		 << "<sc_ciMonthlyPptJan>"
		 << "<sc_cimpjanVal ts=\"1\">161.48</sc_cimpjanVal>"
		 << "<sc_cimpjanVal ts=\"2\">152.09</sc_cimpjanVal>"
		 << "<sc_cimpjanVal ts=\"3\">152.5</sc_cimpjanVal>"
		 << "<sc_cimpjanVal ts=\"4\">152.71</sc_cimpjanVal>"
		 << "<sc_cimpjanVal ts=\"5\">78.44</sc_cimpjanVal>"
		 << "<sc_cimpjanVal ts=\"6\">123.19</sc_cimpjanVal>"
		 << "</sc_ciMonthlyPptJan>"

		 << "<sc_ciMonthlyPptFeb>"
		 << "<sc_cimpfebVal ts=\"1\">199.32</sc_cimpfebVal>"
		 << "<sc_cimpfebVal ts=\"2\">192.94</sc_cimpfebVal>"
		 << "<sc_cimpfebVal ts=\"3\">188.1</sc_cimpfebVal>"
		 << "<sc_cimpfebVal ts=\"4\">153.95</sc_cimpfebVal>"
		 << "<sc_cimpfebVal ts=\"5\">89.79</sc_cimpfebVal>"
		 << "<sc_cimpfebVal ts=\"6\">189.67</sc_cimpfebVal>"
		 << "</sc_ciMonthlyPptFeb>"

		 << "<sc_ciMonthlyPptMar>"
		 << "<sc_cimpmarVal ts=\"1\">169.99</sc_cimpmarVal>"
		 << "<sc_cimpmarVal ts=\"2\">105.49</sc_cimpmarVal>"
		 << "<sc_cimpmarVal ts=\"3\">141.34</sc_cimpmarVal>"
		 << "<sc_cimpmarVal ts=\"4\">84.71</sc_cimpmarVal>"
		 << "<sc_cimpmarVal ts=\"5\">188.92</sc_cimpmarVal>"
		 << "<sc_cimpmarVal ts=\"6\">93.47</sc_cimpmarVal>"
		 << "</sc_ciMonthlyPptMar>"

		 << "<sc_ciMonthlyPptApr>"
		 << "<sc_cimpaprVal ts=\"1\">82.02</sc_cimpaprVal>"
		 << "<sc_cimpaprVal ts=\"2\">77.49</sc_cimpaprVal>"
		 << "<sc_cimpaprVal ts=\"3\">186.32</sc_cimpaprVal>"
		 << "<sc_cimpaprVal ts=\"4\">174.4</sc_cimpaprVal>"
		 << "<sc_cimpaprVal ts=\"5\">161.25</sc_cimpaprVal>"
		 << "<sc_cimpaprVal ts=\"6\">99.76</sc_cimpaprVal>"
		 << "</sc_ciMonthlyPptApr>"

		 << "<sc_ciMonthlyPptMay>"
		 << "<sc_cimpmayVal ts=\"1\">132.54</sc_cimpmayVal>"
		 << "<sc_cimpmayVal ts=\"2\">121.74</sc_cimpmayVal>"
		 << "<sc_cimpmayVal ts=\"3\">178.18</sc_cimpmayVal>"
		 << "<sc_cimpmayVal ts=\"4\">102.86</sc_cimpmayVal>"
		 << "<sc_cimpmayVal ts=\"5\">102.84</sc_cimpmayVal>"
		 << "<sc_cimpmayVal ts=\"6\">172.41</sc_cimpmayVal>"
		 << "</sc_ciMonthlyPptMay>"
         << "<sc_ciMonthlyPptJun>"
		 << "<sc_cimpjunVal ts=\"1\">157.67</sc_cimpjunVal>"
		 << "<sc_cimpjunVal ts=\"2\">133.89</sc_cimpjunVal>"
		 << "<sc_cimpjunVal ts=\"3\">147.29</sc_cimpjunVal>"
		 << "<sc_cimpjunVal ts=\"4\">123.74</sc_cimpjunVal>"
		 << "<sc_cimpjunVal ts=\"5\">126.66</sc_cimpjunVal>"
		 << "<sc_cimpjunVal ts=\"6\">134.35</sc_cimpjunVal>"
		 << "</sc_ciMonthlyPptJun>"

		 << "<sc_ciMonthlyPptJul>"
		 << "<sc_cimpjulVal ts=\"1\">97.63</sc_cimpjulVal>"
		 << "<sc_cimpjulVal ts=\"2\">141.94</sc_cimpjulVal>"
		 << "<sc_cimpjulVal ts=\"3\">173.88</sc_cimpjulVal>"
		 << "<sc_cimpjulVal ts=\"4\">166.53</sc_cimpjulVal>"
		 << "<sc_cimpjulVal ts=\"5\">140.41</sc_cimpjulVal>"
		 << "<sc_cimpjulVal ts=\"6\">128.89</sc_cimpjulVal>"
		 << "</sc_ciMonthlyPptJul>"

		 << "<sc_ciMonthlyPptAug>"
		 << "<sc_cimpaugVal ts=\"1\">145.57</sc_cimpaugVal>"
		 << "<sc_cimpaugVal ts=\"2\">156.69</sc_cimpaugVal>"
		 << "<sc_cimpaugVal ts=\"3\">146.55</sc_cimpaugVal>"
		 << "<sc_cimpaugVal ts=\"4\">167.73</sc_cimpaugVal>"
		 << "<sc_cimpaugVal ts=\"5\">147.67</sc_cimpaugVal>"
		 << "<sc_cimpaugVal ts=\"6\">119.52</sc_cimpaugVal>"
		 << "</sc_ciMonthlyPptAug>"

		 << "<sc_ciMonthlyPptSep>"
		 << "<sc_cimpsepVal ts=\"1\">134.38</sc_cimpsepVal>"
		 << "<sc_cimpsepVal ts=\"2\">89.78</sc_cimpsepVal>"
		 << "<sc_cimpsepVal ts=\"3\">173.37</sc_cimpsepVal>"
		 << "<sc_cimpsepVal ts=\"4\">146.16</sc_cimpsepVal>"
		 << "<sc_cimpsepVal ts=\"5\">108.71</sc_cimpsepVal>"
		 << "<sc_cimpsepVal ts=\"6\">90.68</sc_cimpsepVal>"
		 << "</sc_ciMonthlyPptSep>"

		 << "<sc_ciMonthlyPptOct>"
		 << "<sc_cimpoctVal ts=\"1\">100.17</sc_cimpoctVal>"
		 << "<sc_cimpoctVal ts=\"2\">178.11</sc_cimpoctVal>"
		 << "<sc_cimpoctVal ts=\"3\">120.16</sc_cimpoctVal>"
		 << "<sc_cimpoctVal ts=\"4\">198.43</sc_cimpoctVal>"
		 << "<sc_cimpoctVal ts=\"5\">75.22</sc_cimpoctVal>"
		 << "<sc_cimpoctVal ts=\"6\">198.3</sc_cimpoctVal>"
		 << "</sc_ciMonthlyPptOct>"

		 << "<sc_ciMonthlyPptNov>"
		 << "<sc_cimpnovVal ts=\"1\">112.34</sc_cimpnovVal>"
		 << "<sc_cimpnovVal ts=\"2\">191.22</sc_cimpnovVal>"
		 << "<sc_cimpnovVal ts=\"3\">-125.47</sc_cimpnovVal>"
		 << "<sc_cimpnovVal ts=\"4\">79.8</sc_cimpnovVal>"
		 << "<sc_cimpnovVal ts=\"5\">116.29</sc_cimpnovVal>"
		 << "<sc_cimpnovVal ts=\"6\">146.75</sc_cimpnovVal>"
		 << "</sc_ciMonthlyPptNov>"

		 << "<sc_ciMonthlyPptDec>"
		 << "<sc_cimpdecVal ts=\"1\">137.22</sc_cimpdecVal>"
		 << "<sc_cimpdecVal ts=\"2\">101.29</sc_cimpdecVal>"
		 << "<sc_cimpdecVal ts=\"3\">159.21</sc_cimpdecVal>"
		 << "<sc_cimpdecVal ts=\"4\">171.75</sc_cimpdecVal>"
		 << "<sc_cimpdecVal ts=\"5\">191.54</sc_cimpdecVal>"
		 << "<sc_cimpdecVal ts=\"6\">131.83</sc_cimpdecVal>"
		 << "</sc_ciMonthlyPptDec>"

	     << "<sc_ciJanRad>7468.475</sc_ciJanRad>"
	     << "<sc_ciFebRad>10353.32</sc_ciFebRad>"
	     << "<sc_ciMarRad>17453.07</sc_ciMarRad>"
	     << "<sc_ciAprRad>22721.85</sc_ciAprRad>"
	     << "<sc_ciMayRad>27901.37</sc_ciMayRad>"
	     << "<sc_ciJunRad>28677.54</sc_ciJunRad>"
	     << "<sc_ciJulRad>28764.65</sc_ciJulRad>"
	     << "<sc_ciAugRad>25075.4</sc_ciAugRad>"
	     << "<sc_ciSepRad>19259.27</sc_ciSepRad>"
	     << "<sc_ciOctRad>12609.6</sc_ciOctRad>"
	     << "<sc_ciNovRad>7988.013</sc_ciNovRad>"
	     << "<sc_ciDecRad>6307.151</sc_ciDecRad>"

	     << "</ClimateImporter1>"
	     << "</paramFile>";

	oOut.close();

	return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteClimateImporterXMLErrorFile2()
/////////////////////////////////////////////////////////////////////////////
const char* WriteClimateImporterXMLErrorFile2()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  std::fstream oOut;
  oOut.open( cFileString, ios::out | ios::trunc );

  WriteClimateImporterCommonStuff(oOut);

  oOut << "<ClimateImporter1>"
       << "<sc_ciAWS>-60.9</sc_ciAWS>"

  	   << "<sc_ciMonthlyTempJan>"
  	   << "<sc_cimtjanVal ts=\"1\">-2.57</sc_cimtjanVal>"
  	   << "<sc_cimtjanVal ts=\"2\">-3.46</sc_cimtjanVal>"
  	   << "<sc_cimtjanVal ts=\"3\">-6.93</sc_cimtjanVal>"
  	   << "<sc_cimtjanVal ts=\"4\">-7.76</sc_cimtjanVal>"
  	   << "<sc_cimtjanVal ts=\"5\">-0.72</sc_cimtjanVal>"
  	   << "<sc_cimtjanVal ts=\"6\">1.3</sc_cimtjanVal>"
  	   << "</sc_ciMonthlyTempJan>"

  	   << "<sc_ciMonthlyTempFeb>"
  	   << "<sc_cimtfebVal ts=\"1\">2.75</sc_cimtfebVal>"
  	   << "<sc_cimtfebVal ts=\"2\">-8.57</sc_cimtfebVal>"
  	   << "<sc_cimtfebVal ts=\"3\">1.98</sc_cimtfebVal>"
  	   << "<sc_cimtfebVal ts=\"4\">-7.5</sc_cimtfebVal>"
  	   << "<sc_cimtfebVal ts=\"5\">-2.44</sc_cimtfebVal>"
  	   << "<sc_cimtfebVal ts=\"6\">-9.36</sc_cimtfebVal>"
  	   << "</sc_ciMonthlyTempFeb>"

  	   << "<sc_ciMonthlyTempMar>"
  	   << "<sc_cimtmarVal ts=\"1\">2.94</sc_cimtmarVal>"
  	   << "<sc_cimtmarVal ts=\"2\">0.28</sc_cimtmarVal>"
  	   << "<sc_cimtmarVal ts=\"3\">0.3</sc_cimtmarVal>"
  	   << "<sc_cimtmarVal ts=\"4\">-0.78</sc_cimtmarVal>"
  	   << "<sc_cimtmarVal ts=\"5\">4.85</sc_cimtmarVal>"
  	   << "<sc_cimtmarVal ts=\"6\">3.78</sc_cimtmarVal>"
  	   << "</sc_ciMonthlyTempMar>"

  	   << "<sc_ciMonthlyTempApr>"
  	   << "<sc_cimtaprVal ts=\"1\">2.17</sc_cimtaprVal>"
  	   << "<sc_cimtaprVal ts=\"2\">5.9</sc_cimtaprVal>"
  	   << "<sc_cimtaprVal ts=\"3\">7.17</sc_cimtaprVal>"
  	   << "<sc_cimtaprVal ts=\"4\">8.67</sc_cimtaprVal>"
  	   << "<sc_cimtaprVal ts=\"5\">5.61</sc_cimtaprVal>"
  	   << "<sc_cimtaprVal ts=\"6\">4.56</sc_cimtaprVal>"
  	   << "</sc_ciMonthlyTempApr>"

  	   << "<sc_ciMonthlyTempMay>"
  	   << "<sc_cimtmayVal ts=\"1\">7.25</sc_cimtmayVal>"
  	   << "<sc_cimtmayVal ts=\"2\">7.6</sc_cimtmayVal>"
  	   << "<sc_cimtmayVal ts=\"3\">9.46</sc_cimtmayVal>"
  	   << "<sc_cimtmayVal ts=\"4\">11.26</sc_cimtmayVal>"
  	   << "<sc_cimtmayVal ts=\"5\">7.6</sc_cimtmayVal>"
  	   << "<sc_cimtmayVal ts=\"6\">6.9</sc_cimtmayVal>"
  	   << "</sc_ciMonthlyTempMay>"

  	   << "<sc_ciMonthlyTempJun>"
  	   << "<sc_cimtjunVal ts=\"1\">11.05</sc_cimtjunVal>"
  	   << "<sc_cimtjunVal ts=\"2\">17.16</sc_cimtjunVal>"
  	   << "<sc_cimtjunVal ts=\"3\">11.06</sc_cimtjunVal>"
  	   << "<sc_cimtjunVal ts=\"4\">17.72</sc_cimtjunVal>"
  	   << "<sc_cimtjunVal ts=\"5\">14.05</sc_cimtjunVal>"
  	   << "<sc_cimtjunVal ts=\"6\">13.52</sc_cimtjunVal>"
  	   << "</sc_ciMonthlyTempJun>"

  	   << "<sc_ciMonthlyTempJul>"
  	   << "<sc_cimtjulVal ts=\"1\">16.82</sc_cimtjulVal>"
  	   << "<sc_cimtjulVal ts=\"2\">22</sc_cimtjulVal>"
  	   << "<sc_cimtjulVal ts=\"3\">18.34</sc_cimtjulVal>"
  	   << "<sc_cimtjulVal ts=\"4\">20.99</sc_cimtjulVal>"
  	   << "<sc_cimtjulVal ts=\"5\">15.46</sc_cimtjulVal>"
  	   << "<sc_cimtjulVal ts=\"6\">15.74</sc_cimtjulVal>"
  	   << "</sc_ciMonthlyTempJul>"

  	   << "<sc_ciMonthlyTempAug>"
  	   << "<sc_cimtaugVal ts=\"1\">18.32</sc_cimtaugVal>"
  	   << "<sc_cimtaugVal ts=\"2\">15.97</sc_cimtaugVal>"
  	   << "<sc_cimtaugVal ts=\"3\">17.54</sc_cimtaugVal>"
  	   << "<sc_cimtaugVal ts=\"4\">17.46</sc_cimtaugVal>"
  	   << "<sc_cimtaugVal ts=\"5\">16.69</sc_cimtaugVal>"
  	   << "<sc_cimtaugVal ts=\"6\">17.48</sc_cimtaugVal>"
  	   << "</sc_ciMonthlyTempAug>"

  	   << "<sc_ciMonthlyTempSep>"
  	   << "<sc_cimtsepVal ts=\"1\">22.73</sc_cimtsepVal>"
  	   << "<sc_cimtsepVal ts=\"2\">20.94</sc_cimtsepVal>"
  	   << "<sc_cimtsepVal ts=\"3\">15.94</sc_cimtsepVal>"
  	   << "<sc_cimtsepVal ts=\"4\">18.87</sc_cimtsepVal>"
  	   << "<sc_cimtsepVal ts=\"5\">22.85</sc_cimtsepVal>"
  	   << "<sc_cimtsepVal ts=\"6\">19.53</sc_cimtsepVal>"
  	   << "</sc_ciMonthlyTempSep>"

  	   << "<sc_ciMonthlyTempOct>"
  	   << "<sc_cimtoctVal ts=\"1\">7.92</sc_cimtoctVal>"
  	   << "<sc_cimtoctVal ts=\"2\">8.18</sc_cimtoctVal>"
  	   << "<sc_cimtoctVal ts=\"3\">8.43</sc_cimtoctVal>"
  	   << "<sc_cimtoctVal ts=\"4\">8.68</sc_cimtoctVal>"
  	   << "<sc_cimtoctVal ts=\"5\">8.94</sc_cimtoctVal>"
  	   << "<sc_cimtoctVal ts=\"6\">9.19</sc_cimtoctVal>"
  	   << "</sc_ciMonthlyTempOct>"

  	   << "<sc_ciMonthlyTempNov>"
  	   << "<sc_cimtnovVal ts=\"1\">2.48</sc_cimtnovVal>"
  	   << "<sc_cimtnovVal ts=\"2\">2.56</sc_cimtnovVal>"
  	   << "<sc_cimtnovVal ts=\"3\">2.64</sc_cimtnovVal>"
  	   << "<sc_cimtnovVal ts=\"4\">2.72</sc_cimtnovVal>"
  	   << "<sc_cimtnovVal ts=\"5\">2.8</sc_cimtnovVal>"
  	   << "<sc_cimtnovVal ts=\"6\">2.88</sc_cimtnovVal>"
  	   << "</sc_ciMonthlyTempNov>"

  	   << "<sc_ciMonthlyTempDec>"
  	   << "<sc_cimtdecVal ts=\"1\">-9.6</sc_cimtdecVal>"
  	   << "<sc_cimtdecVal ts=\"2\">-6.94</sc_cimtdecVal>"
  	   << "<sc_cimtdecVal ts=\"3\">-6.51</sc_cimtdecVal>"
  	   << "<sc_cimtdecVal ts=\"4\">-1.59</sc_cimtdecVal>"
  	   << "<sc_cimtdecVal ts=\"5\">0.19</sc_cimtdecVal>"
  	   << "<sc_cimtdecVal ts=\"6\">2.49</sc_cimtdecVal>"
  	   << "</sc_ciMonthlyTempDec>"

  	   << "<sc_ciMonthlyPptJan>"
  	   << "<sc_cimpjanVal ts=\"1\">161.48</sc_cimpjanVal>"
  	   << "<sc_cimpjanVal ts=\"2\">152.09</sc_cimpjanVal>"
  	   << "<sc_cimpjanVal ts=\"3\">152.5</sc_cimpjanVal>"
  	   << "<sc_cimpjanVal ts=\"4\">152.71</sc_cimpjanVal>"
  	   << "<sc_cimpjanVal ts=\"5\">78.44</sc_cimpjanVal>"
  	   << "<sc_cimpjanVal ts=\"6\">123.19</sc_cimpjanVal>"
  	   << "</sc_ciMonthlyPptJan>"

  	   << "<sc_ciMonthlyPptFeb>"
  	   << "<sc_cimpfebVal ts=\"1\">199.32</sc_cimpfebVal>"
  	   << "<sc_cimpfebVal ts=\"2\">192.94</sc_cimpfebVal>"
  	   << "<sc_cimpfebVal ts=\"3\">188.1</sc_cimpfebVal>"
  	   << "<sc_cimpfebVal ts=\"4\">153.95</sc_cimpfebVal>"
  	   << "<sc_cimpfebVal ts=\"5\">89.79</sc_cimpfebVal>"
  	   << "<sc_cimpfebVal ts=\"6\">189.67</sc_cimpfebVal>"
  	   << "</sc_ciMonthlyPptFeb>"

  	   << "<sc_ciMonthlyPptMar>"
  	   << "<sc_cimpmarVal ts=\"1\">169.99</sc_cimpmarVal>"
  	   << "<sc_cimpmarVal ts=\"2\">105.49</sc_cimpmarVal>"
  	   << "<sc_cimpmarVal ts=\"3\">141.34</sc_cimpmarVal>"
  	   << "<sc_cimpmarVal ts=\"4\">84.71</sc_cimpmarVal>"
  	   << "<sc_cimpmarVal ts=\"5\">188.92</sc_cimpmarVal>"
  	   << "<sc_cimpmarVal ts=\"6\">93.47</sc_cimpmarVal>"
  	   << "</sc_ciMonthlyPptMar>"

  	   << "<sc_ciMonthlyPptApr>"
  	   << "<sc_cimpaprVal ts=\"1\">82.02</sc_cimpaprVal>"
  	   << "<sc_cimpaprVal ts=\"2\">77.49</sc_cimpaprVal>"
  	   << "<sc_cimpaprVal ts=\"3\">186.32</sc_cimpaprVal>"
  	   << "<sc_cimpaprVal ts=\"4\">174.4</sc_cimpaprVal>"
  	   << "<sc_cimpaprVal ts=\"5\">161.25</sc_cimpaprVal>"
  	   << "<sc_cimpaprVal ts=\"6\">99.76</sc_cimpaprVal>"
  	   << "</sc_ciMonthlyPptApr>"

  	   << "<sc_ciMonthlyPptMay>"
  	   << "<sc_cimpmayVal ts=\"1\">132.54</sc_cimpmayVal>"
  	   << "<sc_cimpmayVal ts=\"2\">121.74</sc_cimpmayVal>"
  	   << "<sc_cimpmayVal ts=\"3\">178.18</sc_cimpmayVal>"
  	   << "<sc_cimpmayVal ts=\"4\">102.86</sc_cimpmayVal>"
  	   << "<sc_cimpmayVal ts=\"5\">102.84</sc_cimpmayVal>"
  	   << "<sc_cimpmayVal ts=\"6\">172.41</sc_cimpmayVal>"
  	   << "</sc_ciMonthlyPptMay>"

  	   << "<sc_ciMonthlyPptJun>"
  	   << "<sc_cimpjunVal ts=\"1\">157.67</sc_cimpjunVal>"
  	   << "<sc_cimpjunVal ts=\"2\">133.89</sc_cimpjunVal>"
  	   << "<sc_cimpjunVal ts=\"3\">147.29</sc_cimpjunVal>"
  	   << "<sc_cimpjunVal ts=\"4\">123.74</sc_cimpjunVal>"
  	   << "<sc_cimpjunVal ts=\"5\">126.66</sc_cimpjunVal>"
  	   << "<sc_cimpjunVal ts=\"6\">134.35</sc_cimpjunVal>"
  	   << "</sc_ciMonthlyPptJun>"

  	   << "<sc_ciMonthlyPptJul>"
  	   << "<sc_cimpjulVal ts=\"1\">97.63</sc_cimpjulVal>"
  	   << "<sc_cimpjulVal ts=\"2\">141.94</sc_cimpjulVal>"
  	   << "<sc_cimpjulVal ts=\"3\">173.88</sc_cimpjulVal>"
  	   << "<sc_cimpjulVal ts=\"4\">166.53</sc_cimpjulVal>"
  	   << "<sc_cimpjulVal ts=\"5\">140.41</sc_cimpjulVal>"
  	   << "<sc_cimpjulVal ts=\"6\">128.89</sc_cimpjulVal>"
  	   << "</sc_ciMonthlyPptJul>"

  	   << "<sc_ciMonthlyPptAug>"
  	   << "<sc_cimpaugVal ts=\"1\">145.57</sc_cimpaugVal>"
  	   << "<sc_cimpaugVal ts=\"2\">156.69</sc_cimpaugVal>"
  	   << "<sc_cimpaugVal ts=\"3\">146.55</sc_cimpaugVal>"
  	   << "<sc_cimpaugVal ts=\"4\">167.73</sc_cimpaugVal>"
  	   << "<sc_cimpaugVal ts=\"5\">147.67</sc_cimpaugVal>"
  	   << "<sc_cimpaugVal ts=\"6\">119.52</sc_cimpaugVal>"
  	   << "</sc_ciMonthlyPptAug>"

  	   << "<sc_ciMonthlyPptSep>"
  	   << "<sc_cimpsepVal ts=\"1\">134.38</sc_cimpsepVal>"
  	   << "<sc_cimpsepVal ts=\"2\">89.78</sc_cimpsepVal>"
  	   << "<sc_cimpsepVal ts=\"3\">173.37</sc_cimpsepVal>"
  	   << "<sc_cimpsepVal ts=\"4\">146.16</sc_cimpsepVal>"
  	   << "<sc_cimpsepVal ts=\"5\">108.71</sc_cimpsepVal>"
  	   << "<sc_cimpsepVal ts=\"6\">90.68</sc_cimpsepVal>"
  	   << "</sc_ciMonthlyPptSep>"

  	   << "<sc_ciMonthlyPptOct>"
  	   << "<sc_cimpoctVal ts=\"1\">100.17</sc_cimpoctVal>"
  	   << "<sc_cimpoctVal ts=\"2\">178.11</sc_cimpoctVal>"
  	   << "<sc_cimpoctVal ts=\"3\">120.16</sc_cimpoctVal>"
  	   << "<sc_cimpoctVal ts=\"4\">198.43</sc_cimpoctVal>"
  	   << "<sc_cimpoctVal ts=\"5\">75.22</sc_cimpoctVal>"
  	   << "<sc_cimpoctVal ts=\"6\">198.3</sc_cimpoctVal>"
  	   << "</sc_ciMonthlyPptOct>"

  	   << "<sc_ciMonthlyPptNov>"
  	   << "<sc_cimpnovVal ts=\"1\">112.34</sc_cimpnovVal>"
  	   << "<sc_cimpnovVal ts=\"2\">191.22</sc_cimpnovVal>"
  	   << "<sc_cimpnovVal ts=\"3\">125.47</sc_cimpnovVal>"
  	   << "<sc_cimpnovVal ts=\"4\">79.8</sc_cimpnovVal>"
  	   << "<sc_cimpnovVal ts=\"5\">116.29</sc_cimpnovVal>"
  	   << "<sc_cimpnovVal ts=\"6\">146.75</sc_cimpnovVal>"
  	   << "</sc_ciMonthlyPptNov>"

  	   << "<sc_ciMonthlyPptDec>"
  	   << "<sc_cimpdecVal ts=\"1\">137.22</sc_cimpdecVal>"
  	   << "<sc_cimpdecVal ts=\"2\">101.29</sc_cimpdecVal>"
  	   << "<sc_cimpdecVal ts=\"3\">159.21</sc_cimpdecVal>"
  	   << "<sc_cimpdecVal ts=\"4\">171.75</sc_cimpdecVal>"
  	   << "<sc_cimpdecVal ts=\"5\">191.54</sc_cimpdecVal>"
  	   << "<sc_cimpdecVal ts=\"6\">131.83</sc_cimpdecVal>"
  	   << "</sc_ciMonthlyPptDec>"

	   << "<sc_ciJanRad>7468.475</sc_ciJanRad>"
       << "<sc_ciFebRad>10353.32</sc_ciFebRad>"
       << "<sc_ciMarRad>17453.07</sc_ciMarRad>"
       << "<sc_ciAprRad>22721.85</sc_ciAprRad>"
       << "<sc_ciMayRad>27901.37</sc_ciMayRad>"
       << "<sc_ciJunRad>28677.54</sc_ciJunRad>"
       << "<sc_ciJulRad>28764.65</sc_ciJulRad>"
       << "<sc_ciAugRad>25075.4</sc_ciAugRad>"
       << "<sc_ciSepRad>19259.27</sc_ciSepRad>"
       << "<sc_ciOctRad>12609.6</sc_ciOctRad>"
       << "<sc_ciNovRad>7988.013</sc_ciNovRad>"
       << "<sc_ciDecRad>6307.151</sc_ciDecRad>"

	   << "</ClimateImporter1>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteClimateImporterXMLErrorFile3()
/////////////////////////////////////////////////////////////////////////////
const char* WriteClimateImporterXMLErrorFile3()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  std::fstream oOut;
  oOut.open( cFileString, ios::out | ios::trunc );

  WriteClimateImporterCommonStuff(oOut);

  oOut << "<ClimateImporter1>"
  	   << "<sc_ciAWS>60.9</sc_ciAWS>"

  	   << "<sc_ciMonthlyTempJan>"
  	   << "<sc_cimtjanVal ts=\"1\">-2.57</sc_cimtjanVal>"
  	   << "<sc_cimtjanVal ts=\"2\">-3.46</sc_cimtjanVal>"
  	   << "<sc_cimtjanVal ts=\"3\">-6.93</sc_cimtjanVal>"
  	   << "<sc_cimtjanVal ts=\"4\">-7.76</sc_cimtjanVal>"
  	   << "<sc_cimtjanVal ts=\"5\">-0.72</sc_cimtjanVal>"
  	   << "<sc_cimtjanVal ts=\"6\">1.3</sc_cimtjanVal>"
  	   << "</sc_ciMonthlyTempJan>"

  	   << "<sc_ciMonthlyTempFeb>"
  	   << "<sc_cimtfebVal ts=\"1\">2.75</sc_cimtfebVal>"
  	   << "<sc_cimtfebVal ts=\"2\">-8.57</sc_cimtfebVal>"
  	   << "<sc_cimtfebVal ts=\"3\">1.98</sc_cimtfebVal>"
  	   << "<sc_cimtfebVal ts=\"4\">-7.5</sc_cimtfebVal>"
  	   << "<sc_cimtfebVal ts=\"5\">-2.44</sc_cimtfebVal>"
  	   << "<sc_cimtfebVal ts=\"6\">-9.36</sc_cimtfebVal>"
  	   << "</sc_ciMonthlyTempFeb>"

  	   << "<sc_ciMonthlyTempMar>"
  	   << "<sc_cimtmarVal ts=\"1\">2.94</sc_cimtmarVal>"
  	   << "<sc_cimtmarVal ts=\"2\">0.28</sc_cimtmarVal>"
  	   << "<sc_cimtmarVal ts=\"3\">0.3</sc_cimtmarVal>"
  	   << "<sc_cimtmarVal ts=\"4\">-0.78</sc_cimtmarVal>"
  	   << "<sc_cimtmarVal ts=\"5\">4.85</sc_cimtmarVal>"
  	   << "<sc_cimtmarVal ts=\"6\">3.78</sc_cimtmarVal>"
  	   << "</sc_ciMonthlyTempMar>"

  	   << "<sc_ciMonthlyTempApr>"
  	   << "<sc_cimtaprVal ts=\"1\">2.17</sc_cimtaprVal>"
  	   << "<sc_cimtaprVal ts=\"2\">5.9</sc_cimtaprVal>"
  	   << "<sc_cimtaprVal ts=\"3\">7.17</sc_cimtaprVal>"
  	   << "<sc_cimtaprVal ts=\"4\">8.67</sc_cimtaprVal>"
  	   << "<sc_cimtaprVal ts=\"5\">5.61</sc_cimtaprVal>"
  	   << "<sc_cimtaprVal ts=\"6\">4.56</sc_cimtaprVal>"
  	   << "</sc_ciMonthlyTempApr>"

  	   << "<sc_ciMonthlyTempMay>"
  	   << "<sc_cimtmayVal ts=\"1\">7.25</sc_cimtmayVal>"
  	   << "<sc_cimtmayVal ts=\"2\">7.6</sc_cimtmayVal>"
  	   << "<sc_cimtmayVal ts=\"3\">9.46</sc_cimtmayVal>"
  	   << "<sc_cimtmayVal ts=\"4\">11.26</sc_cimtmayVal>"
  	   << "<sc_cimtmayVal ts=\"5\">7.6</sc_cimtmayVal>"
  	   << "<sc_cimtmayVal ts=\"6\">6.9</sc_cimtmayVal>"
  	   << "</sc_ciMonthlyTempMay>"

  	   << "<sc_ciMonthlyTempJun>"
  	   << "<sc_cimtjunVal ts=\"1\">11.05</sc_cimtjunVal>"
  	   << "<sc_cimtjunVal ts=\"2\">17.16</sc_cimtjunVal>"
  	   << "<sc_cimtjunVal ts=\"3\">11.06</sc_cimtjunVal>"
  	   << "<sc_cimtjunVal ts=\"4\">17.72</sc_cimtjunVal>"
  	   << "<sc_cimtjunVal ts=\"5\">14.05</sc_cimtjunVal>"
  	   << "<sc_cimtjunVal ts=\"6\">13.52</sc_cimtjunVal>"
  	   << "</sc_ciMonthlyTempJun>"

  	   << "<sc_ciMonthlyTempJul>"
  	   << "<sc_cimtjulVal ts=\"1\">16.82</sc_cimtjulVal>"
  	   << "<sc_cimtjulVal ts=\"2\">22</sc_cimtjulVal>"
  	   << "<sc_cimtjulVal ts=\"3\">18.34</sc_cimtjulVal>"
  	   << "<sc_cimtjulVal ts=\"4\">20.99</sc_cimtjulVal>"
  	   << "<sc_cimtjulVal ts=\"5\">15.46</sc_cimtjulVal>"
  	   << "<sc_cimtjulVal ts=\"6\">15.74</sc_cimtjulVal>"
  	   << "</sc_ciMonthlyTempJul>"

  	   << "<sc_ciMonthlyTempAug>"
  	   << "<sc_cimtaugVal ts=\"1\">18.32</sc_cimtaugVal>"
  	   << "<sc_cimtaugVal ts=\"2\">15.97</sc_cimtaugVal>"
  	   << "<sc_cimtaugVal ts=\"3\">17.54</sc_cimtaugVal>"
  	   << "<sc_cimtaugVal ts=\"4\">17.46</sc_cimtaugVal>"
  	   << "<sc_cimtaugVal ts=\"5\">16.69</sc_cimtaugVal>"
  	   << "<sc_cimtaugVal ts=\"6\">17.48</sc_cimtaugVal>"
  	   << "</sc_ciMonthlyTempAug>"

  	   << "<sc_ciMonthlyTempSep>"
  	   << "<sc_cimtsepVal ts=\"1\">22.73</sc_cimtsepVal>"
  	   << "<sc_cimtsepVal ts=\"2\">20.94</sc_cimtsepVal>"
  	   << "<sc_cimtsepVal ts=\"3\">15.94</sc_cimtsepVal>"
  	   << "<sc_cimtsepVal ts=\"4\">18.87</sc_cimtsepVal>"
  	   << "<sc_cimtsepVal ts=\"5\">22.85</sc_cimtsepVal>"
  	   << "<sc_cimtsepVal ts=\"6\">19.53</sc_cimtsepVal>"
  	   << "</sc_ciMonthlyTempSep>"

  	   << "<sc_ciMonthlyTempOct>"
  	   << "<sc_cimtoctVal ts=\"1\">7.92</sc_cimtoctVal>"
  	   << "<sc_cimtoctVal ts=\"2\">8.18</sc_cimtoctVal>"
  	   << "<sc_cimtoctVal ts=\"3\">8.43</sc_cimtoctVal>"
  	   << "<sc_cimtoctVal ts=\"4\">8.68</sc_cimtoctVal>"
  	   << "<sc_cimtoctVal ts=\"5\">8.94</sc_cimtoctVal>"
  	   << "<sc_cimtoctVal ts=\"6\">9.19</sc_cimtoctVal>"
  	   << "</sc_ciMonthlyTempOct>"

  	   << "<sc_ciMonthlyTempNov>"
  	   << "<sc_cimtnovVal ts=\"1\">2.48</sc_cimtnovVal>"
  	   << "<sc_cimtnovVal ts=\"2\">2.56</sc_cimtnovVal>"
  	   << "<sc_cimtnovVal ts=\"3\">2.64</sc_cimtnovVal>"
  	   << "<sc_cimtnovVal ts=\"4\">2.72</sc_cimtnovVal>"
  	   << "<sc_cimtnovVal ts=\"5\">2.8</sc_cimtnovVal>"
  	   << "<sc_cimtnovVal ts=\"6\">2.88</sc_cimtnovVal>"
  	   << "</sc_ciMonthlyTempNov>"

  	   << "<sc_ciMonthlyTempDec>"
  	   << "<sc_cimtdecVal ts=\"1\">-9.6</sc_cimtdecVal>"
  	   << "<sc_cimtdecVal ts=\"2\">-6.94</sc_cimtdecVal>"
  	   << "<sc_cimtdecVal ts=\"3\">-6.51</sc_cimtdecVal>"
  	   << "<sc_cimtdecVal ts=\"4\">-1.59</sc_cimtdecVal>"
  	   << "<sc_cimtdecVal ts=\"5\">0.19</sc_cimtdecVal>"
  	   << "<sc_cimtdecVal ts=\"6\">2.49</sc_cimtdecVal>"
  	   << "</sc_ciMonthlyTempDec>"

  	   << "<sc_ciMonthlyPptJan>"
  	   << "<sc_cimpjanVal ts=\"1\">161.48</sc_cimpjanVal>"
  	   << "<sc_cimpjanVal ts=\"2\">152.09</sc_cimpjanVal>"
  	   << "<sc_cimpjanVal ts=\"3\">152.5</sc_cimpjanVal>"
  	   << "<sc_cimpjanVal ts=\"4\">152.71</sc_cimpjanVal>"
  	   << "<sc_cimpjanVal ts=\"5\">78.44</sc_cimpjanVal>"
  	   << "<sc_cimpjanVal ts=\"6\">123.19</sc_cimpjanVal>"
  	   << "</sc_ciMonthlyPptJan>"

  	   << "<sc_ciMonthlyPptFeb>"
  	   << "<sc_cimpfebVal ts=\"1\">199.32</sc_cimpfebVal>"
  	   << "<sc_cimpfebVal ts=\"2\">192.94</sc_cimpfebVal>"
  	   << "<sc_cimpfebVal ts=\"3\">188.1</sc_cimpfebVal>"
  	   << "<sc_cimpfebVal ts=\"4\">153.95</sc_cimpfebVal>"
  	   << "<sc_cimpfebVal ts=\"5\">89.79</sc_cimpfebVal>"
  	   << "<sc_cimpfebVal ts=\"6\">189.67</sc_cimpfebVal>"
  	   << "</sc_ciMonthlyPptFeb>"

  	   << "<sc_ciMonthlyPptMar>"
  	   << "<sc_cimpmarVal ts=\"1\">169.99</sc_cimpmarVal>"
  	   << "<sc_cimpmarVal ts=\"2\">105.49</sc_cimpmarVal>"
  	   << "<sc_cimpmarVal ts=\"3\">141.34</sc_cimpmarVal>"
  	   << "<sc_cimpmarVal ts=\"4\">84.71</sc_cimpmarVal>"
  	   << "<sc_cimpmarVal ts=\"5\">188.92</sc_cimpmarVal>"
  	   << "<sc_cimpmarVal ts=\"6\">93.47</sc_cimpmarVal>"
  	   << "</sc_ciMonthlyPptMar>"

  	   << "<sc_ciMonthlyPptApr>"
  	   << "<sc_cimpaprVal ts=\"1\">82.02</sc_cimpaprVal>"
  	   << "<sc_cimpaprVal ts=\"2\">77.49</sc_cimpaprVal>"
  	   << "<sc_cimpaprVal ts=\"3\">186.32</sc_cimpaprVal>"
  	   << "<sc_cimpaprVal ts=\"4\">174.4</sc_cimpaprVal>"
  	   << "<sc_cimpaprVal ts=\"5\">161.25</sc_cimpaprVal>"
  	   << "<sc_cimpaprVal ts=\"6\">99.76</sc_cimpaprVal>"
  	   << "</sc_ciMonthlyPptApr>"

  	   << "<sc_ciMonthlyPptMay>"
  	   << "<sc_cimpmayVal ts=\"1\">132.54</sc_cimpmayVal>"
  	   << "<sc_cimpmayVal ts=\"2\">121.74</sc_cimpmayVal>"
  	   << "<sc_cimpmayVal ts=\"3\">178.18</sc_cimpmayVal>"
  	   << "<sc_cimpmayVal ts=\"4\">102.86</sc_cimpmayVal>"
  	   << "<sc_cimpmayVal ts=\"5\">102.84</sc_cimpmayVal>"
  	   << "<sc_cimpmayVal ts=\"6\">172.41</sc_cimpmayVal>"
  	   << "</sc_ciMonthlyPptMay>"

  	   << "<sc_ciMonthlyPptJun>"
  	   << "<sc_cimpjunVal ts=\"1\">157.67</sc_cimpjunVal>"
  	   << "<sc_cimpjunVal ts=\"2\">133.89</sc_cimpjunVal>"
  	   << "<sc_cimpjunVal ts=\"3\">147.29</sc_cimpjunVal>"
  	   << "<sc_cimpjunVal ts=\"4\">123.74</sc_cimpjunVal>"
  	   << "<sc_cimpjunVal ts=\"5\">126.66</sc_cimpjunVal>"
  	   << "<sc_cimpjunVal ts=\"6\">134.35</sc_cimpjunVal>"
  	   << "</sc_ciMonthlyPptJun>"

  	   << "<sc_ciMonthlyPptJul>"
  	   << "<sc_cimpjulVal ts=\"1\">97.63</sc_cimpjulVal>"
  	   << "<sc_cimpjulVal ts=\"2\">141.94</sc_cimpjulVal>"
  	   << "<sc_cimpjulVal ts=\"3\">173.88</sc_cimpjulVal>"
  	   << "<sc_cimpjulVal ts=\"4\">166.53</sc_cimpjulVal>"
  	   << "<sc_cimpjulVal ts=\"5\">140.41</sc_cimpjulVal>"
  	   << "<sc_cimpjulVal ts=\"6\">128.89</sc_cimpjulVal>"
  	   << "</sc_ciMonthlyPptJul>"

  	   << "<sc_ciMonthlyPptAug>"
  	   << "<sc_cimpaugVal ts=\"1\">145.57</sc_cimpaugVal>"
  	   << "<sc_cimpaugVal ts=\"2\">156.69</sc_cimpaugVal>"
  	   << "<sc_cimpaugVal ts=\"3\">146.55</sc_cimpaugVal>"
  	   << "<sc_cimpaugVal ts=\"4\">167.73</sc_cimpaugVal>"
  	   << "<sc_cimpaugVal ts=\"5\">147.67</sc_cimpaugVal>"
  	   << "<sc_cimpaugVal ts=\"6\">119.52</sc_cimpaugVal>"
  	   << "</sc_ciMonthlyPptAug>"

  	   << "<sc_ciMonthlyPptSep>"
  	   << "<sc_cimpsepVal ts=\"1\">134.38</sc_cimpsepVal>"
  	   << "<sc_cimpsepVal ts=\"2\">89.78</sc_cimpsepVal>"
  	   << "<sc_cimpsepVal ts=\"3\">173.37</sc_cimpsepVal>"
  	   << "<sc_cimpsepVal ts=\"4\">146.16</sc_cimpsepVal>"
  	   << "<sc_cimpsepVal ts=\"5\">108.71</sc_cimpsepVal>"
  	   << "<sc_cimpsepVal ts=\"6\">90.68</sc_cimpsepVal>"
  	   << "</sc_ciMonthlyPptSep>"

  	   << "<sc_ciMonthlyPptOct>"
  	   << "<sc_cimpoctVal ts=\"1\">100.17</sc_cimpoctVal>"
  	   << "<sc_cimpoctVal ts=\"2\">178.11</sc_cimpoctVal>"
  	   << "<sc_cimpoctVal ts=\"3\">120.16</sc_cimpoctVal>"
  	   << "<sc_cimpoctVal ts=\"4\">198.43</sc_cimpoctVal>"
  	   << "<sc_cimpoctVal ts=\"5\">75.22</sc_cimpoctVal>"
  	   << "<sc_cimpoctVal ts=\"6\">198.3</sc_cimpoctVal>"
  	   << "</sc_ciMonthlyPptOct>"

  	   << "<sc_ciMonthlyPptNov>"
  	   << "<sc_cimpnovVal ts=\"1\">112.34</sc_cimpnovVal>"
  	   << "<sc_cimpnovVal ts=\"2\">191.22</sc_cimpnovVal>"
  	   << "<sc_cimpnovVal ts=\"3\">125.47</sc_cimpnovVal>"
  	   << "<sc_cimpnovVal ts=\"4\">79.8</sc_cimpnovVal>"
  	   << "<sc_cimpnovVal ts=\"5\">116.29</sc_cimpnovVal>"
  	   << "<sc_cimpnovVal ts=\"6\">146.75</sc_cimpnovVal>"
  	   << "</sc_ciMonthlyPptNov>"

  	   << "<sc_ciMonthlyPptDec>"
  	   << "<sc_cimpdecVal ts=\"1\">137.22</sc_cimpdecVal>"
  	   << "<sc_cimpdecVal ts=\"2\">101.29</sc_cimpdecVal>"
  	   << "<sc_cimpdecVal ts=\"3\">159.21</sc_cimpdecVal>"
  	   << "<sc_cimpdecVal ts=\"4\">171.75</sc_cimpdecVal>"
  	   << "<sc_cimpdecVal ts=\"5\">191.54</sc_cimpdecVal>"
  	   << "<sc_cimpdecVal ts=\"6\">131.83</sc_cimpdecVal>"
  	   << "</sc_ciMonthlyPptDec>"

       << "<sc_ciJanRad>7468.475</sc_ciJanRad>"
       << "<sc_ciFebRad>10353.32</sc_ciFebRad>"
       << "<sc_ciMarRad>17453.07</sc_ciMarRad>"
       << "<sc_ciAprRad>22721.85</sc_ciAprRad>"
       << "<sc_ciMayRad>27901.37</sc_ciMayRad>"
       << "<sc_ciJunRad>-28677.54</sc_ciJunRad>"
       << "<sc_ciJulRad>28764.65</sc_ciJulRad>"
       << "<sc_ciAugRad>25075.4</sc_ciAugRad>"
       << "<sc_ciSepRad>19259.27</sc_ciSepRad>"
       << "<sc_ciOctRad>12609.6</sc_ciOctRad>"
       << "<sc_ciNovRad>7988.013</sc_ciNovRad>"
       << "<sc_ciDecRad>6307.151</sc_ciDecRad>"

       << "</ClimateImporter1>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

void WriteClimateImporterCommonStuff( std::fstream &oOut ) {

  using namespace std;
  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"07010101\">"
       << "<plot>"
       << "<timesteps>6</timesteps>"
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
       << "<behaviorName>ClimateImporter</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>StateReporter</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>2</listPosition>"
       << "</behavior>"
       << "</behaviorList>";
}
