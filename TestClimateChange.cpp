//---------------------------------------------------------------------------
// TestClimateChange.cpp
//---------------------------------------------------------------------------
#include "TestClimateChange.h"
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
// WriteClimateChangeXMLFile1() does setup.
/////////////////////////////////////////////////////////////////////////////
TEST(ClimateChange, TestNormalProcessingRun1) {

  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    clPlot *p_oPlot;
    clGrid *p_oClimateGrid;
    float fActualTemp, fExpectedTemp, fActualPrecip, fExpectedPrecip,
          fActualWaterDeficit, fExpectedWaterDeficit,
          fActualSeasonalPrecip, fExpectedSeasonalPrecip;
    int iTempCode, iPrecipCode;

    //Feed our file to the sim manager
    p_oSimManager->ReadFile(WriteClimateChangeXMLFile1());
    p_oPlot = p_oSimManager->GetPlotObject();
    p_oClimateGrid = p_oSimManager->GetGridObject("State Variables");
    iTempCode = p_oClimateGrid->GetFloatDataCode("Temp.C");
    iPrecipCode = p_oClimateGrid->GetFloatDataCode("Precip.mm");

    //Initial conditions
    fExpectedPrecip = 1000;
    fExpectedTemp = 8;
    fExpectedWaterDeficit = 500;
    fExpectedSeasonalPrecip = 600;
    fActualPrecip = p_oPlot->GetMeanAnnualPrecip();
    fActualTemp = p_oPlot->GetMeanAnnualTemp();
    fActualWaterDeficit = p_oPlot->GetWaterDeficit();
    fActualSeasonalPrecip = p_oPlot->GetSeasonalPrecipitation();
    EXPECT_LT(fabs(fExpectedPrecip - fActualPrecip), 0.000001);
    EXPECT_LT(fabs(fExpectedTemp - fActualTemp), 0.000001);
    EXPECT_LT(fabs(fExpectedWaterDeficit - fActualWaterDeficit), 0.000001);
    EXPECT_LT(fabs(fExpectedSeasonalPrecip - fActualSeasonalPrecip), 0.000001);

    p_oClimateGrid->GetValueOfCell(0, 0, iTempCode, &fActualTemp);
    p_oClimateGrid->GetValueOfCell(0, 0, iPrecipCode, &fActualPrecip);
    EXPECT_LT(fabs(fExpectedPrecip - fActualPrecip), 0.000001);
    EXPECT_LT(fabs(fExpectedTemp - fActualTemp), 0.000001);

    //Timestep 1
    p_oSimManager->RunSim(1);
    fExpectedPrecip = 1000;
    fExpectedTemp = 8;
    fActualPrecip = p_oPlot->GetMeanAnnualPrecip();
    fActualTemp = p_oPlot->GetMeanAnnualTemp();
    fActualWaterDeficit = p_oPlot->GetWaterDeficit();
    fActualSeasonalPrecip = p_oPlot->GetSeasonalPrecipitation();

    EXPECT_LT(fabs(fExpectedPrecip - fActualPrecip), 0.000001);
    EXPECT_LT(fabs(fExpectedTemp - fActualTemp), 0.000001);
    EXPECT_LT(fabs(fExpectedWaterDeficit - fActualWaterDeficit), 0.000001);
    EXPECT_LT(fabs(fExpectedSeasonalPrecip - fActualSeasonalPrecip), 0.000001);

    p_oClimateGrid->GetValueOfCell(0, 0, iTempCode, &fActualTemp);
    p_oClimateGrid->GetValueOfCell(0, 0, iPrecipCode, &fActualPrecip);
    EXPECT_LT(fabs(fExpectedPrecip - fActualPrecip), 0.000001);
    EXPECT_LT(fabs(fExpectedTemp - fActualTemp), 0.000001);

    //Timestep 2
    p_oSimManager->RunSim(1);
    fExpectedPrecip = 1000.01;
    fExpectedTemp = 8.02;
    fActualPrecip = p_oPlot->GetMeanAnnualPrecip();
    fActualTemp = p_oPlot->GetMeanAnnualTemp();
    fActualWaterDeficit = p_oPlot->GetWaterDeficit();
    fActualSeasonalPrecip = p_oPlot->GetSeasonalPrecipitation();

    EXPECT_LT(fabs(fExpectedPrecip - fActualPrecip), 0.000001);
    EXPECT_LT(fabs(fExpectedTemp - fActualTemp), 0.000001);
    EXPECT_LT(fabs(fExpectedWaterDeficit - fActualWaterDeficit), 0.000001);
    EXPECT_LT(fabs(fExpectedSeasonalPrecip - fActualSeasonalPrecip), 0.000001);

    p_oClimateGrid->GetValueOfCell(0, 0, iTempCode, &fActualTemp);
    p_oClimateGrid->GetValueOfCell(0, 0, iPrecipCode, &fActualPrecip);
    EXPECT_LT(fabs(fExpectedPrecip - fActualPrecip), 0.000001);
    EXPECT_LT(fabs(fExpectedTemp - fActualTemp), 0.000001);

    //Timestep 3
    p_oSimManager->RunSim(1);
    fExpectedPrecip = 1000.04;
    fExpectedTemp = 8.04;
    fActualPrecip = p_oPlot->GetMeanAnnualPrecip();
    fActualTemp = p_oPlot->GetMeanAnnualTemp();
    fActualWaterDeficit = p_oPlot->GetWaterDeficit();
    fActualSeasonalPrecip = p_oPlot->GetSeasonalPrecipitation();

    EXPECT_LT(fabs(fExpectedPrecip - fActualPrecip), 0.000001);
    EXPECT_LT(fabs(fExpectedTemp - fActualTemp), 0.000001);
    EXPECT_LT(fabs(fExpectedWaterDeficit - fActualWaterDeficit), 0.000001);
    EXPECT_LT(fabs(fExpectedSeasonalPrecip - fActualSeasonalPrecip), 0.000001);

    p_oClimateGrid->GetValueOfCell(0, 0, iTempCode, &fActualTemp);
    p_oClimateGrid->GetValueOfCell(0, 0, iPrecipCode, &fActualPrecip);
    EXPECT_LT(fabs(fExpectedPrecip - fActualPrecip), 0.000001);
    EXPECT_LT(fabs(fExpectedTemp - fActualTemp), 0.000001);

    //Timestep 4
    p_oSimManager->RunSim(1);
    fExpectedPrecip = 1000.09;
    fExpectedTemp = 8.06;
    fActualPrecip = p_oPlot->GetMeanAnnualPrecip();
    fActualTemp = p_oPlot->GetMeanAnnualTemp();
    fActualWaterDeficit = p_oPlot->GetWaterDeficit();
    fActualSeasonalPrecip = p_oPlot->GetSeasonalPrecipitation();

    EXPECT_LT(fabs(fExpectedPrecip - fActualPrecip), 0.000001);
    EXPECT_LT(fabs(fExpectedTemp - fActualTemp), 0.000001);
    EXPECT_LT(fabs(fExpectedWaterDeficit - fActualWaterDeficit), 0.000001);
    EXPECT_LT(fabs(fExpectedSeasonalPrecip - fActualSeasonalPrecip), 0.000001);

    p_oClimateGrid->GetValueOfCell(0, 0, iTempCode, &fActualTemp);
    p_oClimateGrid->GetValueOfCell(0, 0, iPrecipCode, &fActualPrecip);
    EXPECT_LT(fabs(fExpectedPrecip - fActualPrecip), 0.000001);
    EXPECT_LT(fabs(fExpectedTemp - fActualTemp), 0.000001);

    //Timestep 5
    p_oSimManager->RunSim(1);
    fExpectedPrecip = 1000.16;
    fExpectedTemp = 8.08;
    fActualPrecip = p_oPlot->GetMeanAnnualPrecip();
    fActualTemp = p_oPlot->GetMeanAnnualTemp();
    fActualWaterDeficit = p_oPlot->GetWaterDeficit();
    fActualSeasonalPrecip = p_oPlot->GetSeasonalPrecipitation();

    EXPECT_LT(fabs(fExpectedPrecip - fActualPrecip), 0.000001);
    EXPECT_LT(fabs(fExpectedTemp - fActualTemp), 0.000001);
    EXPECT_LT(fabs(fExpectedWaterDeficit - fActualWaterDeficit), 0.000001);
    EXPECT_LT(fabs(fExpectedSeasonalPrecip - fActualSeasonalPrecip), 0.000001);

    p_oClimateGrid->GetValueOfCell(0, 0, iTempCode, &fActualTemp);
    p_oClimateGrid->GetValueOfCell(0, 0, iPrecipCode, &fActualPrecip);
    EXPECT_LT(fabs(fExpectedPrecip - fActualPrecip), 0.000001);
    EXPECT_LT(fabs(fExpectedTemp - fActualTemp), 0.000001);
    delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

/////////////////////////////////////////////////////////////////////////////
// TestNormalProcessingRun2()
// Tests normal processing for a 3-year timestep.
// WriteClimateChangeXMLFile2() does setup.
/////////////////////////////////////////////////////////////////////////////
TEST(ClimateChange, TestNormalProcessingRun2) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    clPlot *p_oPlot;
    clGrid *p_oClimateGrid;
    float fActualTemp, fExpectedTemp, fActualPrecip, fExpectedPrecip,
          fActualWaterDeficit, fExpectedWaterDeficit,
          fActualSeasonalPrecip, fExpectedSeasonalPrecip;
    int iTempCode, iPrecipCode;

    //Feed our file to the sim manager
    p_oSimManager->ReadFile(WriteClimateChangeXMLFile2());
    p_oPlot = p_oSimManager->GetPlotObject();
    p_oClimateGrid = p_oSimManager->GetGridObject("State Variables");
    iTempCode = p_oClimateGrid->GetFloatDataCode("Temp.C");
    iPrecipCode = p_oClimateGrid->GetFloatDataCode("Precip.mm");

    //Initial conditions
    fExpectedPrecip = 1000;
    fExpectedTemp = 8;
    fExpectedWaterDeficit = 500;
    fExpectedSeasonalPrecip = 600;

    fActualPrecip = p_oPlot->GetMeanAnnualPrecip();
    fActualTemp = p_oPlot->GetMeanAnnualTemp();
    fActualWaterDeficit = p_oPlot->GetWaterDeficit();
    fActualSeasonalPrecip = p_oPlot->GetSeasonalPrecipitation();

    EXPECT_LT(fabs(fExpectedPrecip - fActualPrecip), 0.000001);
    EXPECT_LT(fabs(fExpectedTemp - fActualTemp), 0.000001);
    EXPECT_LT(fabs(fExpectedWaterDeficit - fActualWaterDeficit), 0.000001);
    EXPECT_LT(fabs(fExpectedSeasonalPrecip - fActualSeasonalPrecip), 0.000001);

    p_oClimateGrid->GetValueOfCell(0, 0, iTempCode, &fActualTemp);
    p_oClimateGrid->GetValueOfCell(0, 0, iPrecipCode, &fActualPrecip);
    EXPECT_LT(fabs(fExpectedPrecip - fActualPrecip), 0.000001);
    EXPECT_LT(fabs(fExpectedTemp - fActualTemp), 0.000001);

    //Timestep 1
    p_oSimManager->RunSim(1);
    fExpectedPrecip = 1000;
    fExpectedTemp = 8;
    fActualPrecip = p_oPlot->GetMeanAnnualPrecip();
    fActualTemp = p_oPlot->GetMeanAnnualTemp();
    fActualWaterDeficit = p_oPlot->GetWaterDeficit();
    fActualSeasonalPrecip = p_oPlot->GetSeasonalPrecipitation();

    EXPECT_LT(fabs(fExpectedPrecip - fActualPrecip), 0.000001);
    EXPECT_LT(fabs(fExpectedTemp - fActualTemp), 0.000001);
    EXPECT_LT(fabs(fExpectedWaterDeficit - fActualWaterDeficit), 0.000001);
    EXPECT_LT(fabs(fExpectedSeasonalPrecip - fActualSeasonalPrecip), 0.000001);

    p_oClimateGrid->GetValueOfCell(0, 0, iTempCode, &fActualTemp);
    p_oClimateGrid->GetValueOfCell(0, 0, iPrecipCode, &fActualPrecip);
    EXPECT_LT(fabs(fExpectedPrecip - fActualPrecip), 0.000001);
    EXPECT_LT(fabs(fExpectedTemp - fActualTemp), 0.000001);

    //Timestep 2
    p_oSimManager->RunSim(1);
    fExpectedPrecip = 1000.09;
    fExpectedTemp = 8.06;
    fActualPrecip = p_oPlot->GetMeanAnnualPrecip();
    fActualTemp = p_oPlot->GetMeanAnnualTemp();
    fActualWaterDeficit = p_oPlot->GetWaterDeficit();
    fActualSeasonalPrecip = p_oPlot->GetSeasonalPrecipitation();

    EXPECT_LT(fabs(fExpectedPrecip - fActualPrecip), 0.000001);
    EXPECT_LT(fabs(fExpectedTemp - fActualTemp), 0.000001);
    EXPECT_LT(fabs(fExpectedWaterDeficit - fActualWaterDeficit), 0.000001);
    EXPECT_LT(fabs(fExpectedSeasonalPrecip - fActualSeasonalPrecip), 0.000001);

    p_oClimateGrid->GetValueOfCell(0, 0, iTempCode, &fActualTemp);
    p_oClimateGrid->GetValueOfCell(0, 0, iPrecipCode, &fActualPrecip);
    EXPECT_LT(fabs(fExpectedPrecip - fActualPrecip), 0.000001);
    EXPECT_LT(fabs(fExpectedTemp - fActualTemp), 0.000001);

    //Timestep 3
    p_oSimManager->RunSim(1);
    fExpectedPrecip = 1000.36;
    fExpectedTemp = 8.12;
    fActualPrecip = p_oPlot->GetMeanAnnualPrecip();
    fActualTemp = p_oPlot->GetMeanAnnualTemp();
    fActualWaterDeficit = p_oPlot->GetWaterDeficit();
    fActualSeasonalPrecip = p_oPlot->GetSeasonalPrecipitation();

    EXPECT_LT(fabs(fExpectedPrecip - fActualPrecip), 0.000001);
    EXPECT_LT(fabs(fExpectedTemp - fActualTemp), 0.000001);
    EXPECT_LT(fabs(fExpectedWaterDeficit - fActualWaterDeficit), 0.000001);
    EXPECT_LT(fabs(fExpectedSeasonalPrecip - fActualSeasonalPrecip), 0.000001);

    p_oClimateGrid->GetValueOfCell(0, 0, iTempCode, &fActualTemp);
    p_oClimateGrid->GetValueOfCell(0, 0, iPrecipCode, &fActualPrecip);
    EXPECT_LT(fabs(fExpectedPrecip - fActualPrecip), 0.000001);
    EXPECT_LT(fabs(fExpectedTemp - fActualTemp), 0.000001);

    //Timestep 4
    p_oSimManager->RunSim(1);
    fExpectedPrecip = 1000.81;
    fExpectedTemp = 8.18;
    fActualPrecip = p_oPlot->GetMeanAnnualPrecip();
    fActualTemp = p_oPlot->GetMeanAnnualTemp();
    fActualWaterDeficit = p_oPlot->GetWaterDeficit();
    fActualSeasonalPrecip = p_oPlot->GetSeasonalPrecipitation();

    EXPECT_LT(fabs(fExpectedPrecip - fActualPrecip), 0.000001);
    EXPECT_LT(fabs(fExpectedTemp - fActualTemp), 0.000001);
    EXPECT_LT(fabs(fExpectedWaterDeficit - fActualWaterDeficit), 0.000001);
    EXPECT_LT(fabs(fExpectedSeasonalPrecip - fActualSeasonalPrecip), 0.000001);

    p_oClimateGrid->GetValueOfCell(0, 0, iTempCode, &fActualTemp);
    p_oClimateGrid->GetValueOfCell(0, 0, iPrecipCode, &fActualPrecip);
    EXPECT_LT(fabs(fExpectedPrecip - fActualPrecip), 0.000001);
    EXPECT_LT(fabs(fExpectedTemp - fActualTemp), 0.000001);

    //Timestep 5
    p_oSimManager->RunSim(1);
    fExpectedPrecip = 1001.44;
    fExpectedTemp = 8.24;
    fActualPrecip = p_oPlot->GetMeanAnnualPrecip();
    fActualTemp = p_oPlot->GetMeanAnnualTemp();
    fActualWaterDeficit = p_oPlot->GetWaterDeficit();
    fActualSeasonalPrecip = p_oPlot->GetSeasonalPrecipitation();

    EXPECT_LT(fabs(fExpectedPrecip - fActualPrecip), 0.000001);
    EXPECT_LT(fabs(fExpectedTemp - fActualTemp), 0.000001);
    EXPECT_LT(fabs(fExpectedWaterDeficit - fActualWaterDeficit), 0.000001);
    EXPECT_LT(fabs(fExpectedSeasonalPrecip - fActualSeasonalPrecip), 0.000001);

    p_oClimateGrid->GetValueOfCell(0, 0, iTempCode, &fActualTemp);
    p_oClimateGrid->GetValueOfCell(0, 0, iPrecipCode, &fActualPrecip);
    EXPECT_LT(fabs(fExpectedPrecip - fActualPrecip), 0.000001);
    EXPECT_LT(fabs(fExpectedTemp - fActualTemp), 0.000001);
    delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

/////////////////////////////////////////////////////////////////////////////
// TestNormalProcessingRun3()
// Tests normal processing for a 1-year timestep, only temperature.
// WriteClimateChangeXMLFile3() does setup.
/////////////////////////////////////////////////////////////////////////////
TEST(ClimateChange, TestNormalProcessingRun3) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    clPlot *p_oPlot;
    clGrid *p_oClimateGrid;
    float fActualTemp, fExpectedTemp, fActualPrecip, fExpectedPrecip,
          fActualWaterDeficit, fExpectedWaterDeficit,
          fActualSeasonalPrecip, fExpectedSeasonalPrecip;
    int iTempCode, iPrecipCode;

    //Feed our file to the sim manager
    p_oSimManager->ReadFile(WriteClimateChangeXMLFile3());
    p_oPlot = p_oSimManager->GetPlotObject();
    p_oClimateGrid = p_oSimManager->GetGridObject("State Variables");
    iTempCode = p_oClimateGrid->GetFloatDataCode("Temp.C");
    iPrecipCode = p_oClimateGrid->GetFloatDataCode("Precip.mm");

    //Initial conditions
    fExpectedPrecip = 1000;
    fExpectedTemp = 8;
    fExpectedWaterDeficit = 500;
    fExpectedSeasonalPrecip = 600;

    fActualPrecip = p_oPlot->GetMeanAnnualPrecip();
    fActualTemp = p_oPlot->GetMeanAnnualTemp();
    fActualWaterDeficit = p_oPlot->GetWaterDeficit();
    fActualSeasonalPrecip = p_oPlot->GetSeasonalPrecipitation();

    EXPECT_LT(fabs(fExpectedPrecip - fActualPrecip), 0.000001);
    EXPECT_LT(fabs(fExpectedTemp - fActualTemp), 0.000001);
    EXPECT_LT(fabs(fExpectedWaterDeficit - fActualWaterDeficit), 0.000001);
    EXPECT_LT(fabs(fExpectedSeasonalPrecip - fActualSeasonalPrecip), 0.000001);

    p_oClimateGrid->GetValueOfCell(0, 0, iTempCode, &fActualTemp);
    p_oClimateGrid->GetValueOfCell(0, 0, iPrecipCode, &fActualPrecip);
    EXPECT_LT(fabs(fExpectedPrecip - fActualPrecip), 0.000001);
    EXPECT_LT(fabs(fExpectedTemp - fActualTemp), 0.000001);

    //Timestep 1
    p_oSimManager->RunSim(1);
    fExpectedTemp = 8;
    fActualPrecip = p_oPlot->GetMeanAnnualPrecip();
    fActualTemp = p_oPlot->GetMeanAnnualTemp();
    fActualWaterDeficit = p_oPlot->GetWaterDeficit();
    fActualSeasonalPrecip = p_oPlot->GetSeasonalPrecipitation();

    EXPECT_LT(fabs(fExpectedPrecip - fActualPrecip), 0.000001);
    EXPECT_LT(fabs(fExpectedTemp - fActualTemp), 0.000001);
    EXPECT_LT(fabs(fExpectedWaterDeficit - fActualWaterDeficit), 0.000001);
    EXPECT_LT(fabs(fExpectedSeasonalPrecip - fActualSeasonalPrecip), 0.000001);

    p_oClimateGrid->GetValueOfCell(0, 0, iTempCode, &fActualTemp);
    p_oClimateGrid->GetValueOfCell(0, 0, iPrecipCode, &fActualPrecip);
    EXPECT_LT(fabs(fExpectedPrecip - fActualPrecip), 0.000001);
    EXPECT_LT(fabs(fExpectedTemp - fActualTemp), 0.000001);

    //Timestep 2
    p_oSimManager->RunSim(1);
    fExpectedTemp = 8.02;
    fActualPrecip = p_oPlot->GetMeanAnnualPrecip();
    fActualTemp = p_oPlot->GetMeanAnnualTemp();
    fActualWaterDeficit = p_oPlot->GetWaterDeficit();
    fActualSeasonalPrecip = p_oPlot->GetSeasonalPrecipitation();

    EXPECT_LT(fabs(fExpectedPrecip - fActualPrecip), 0.000001);
    EXPECT_LT(fabs(fExpectedTemp - fActualTemp), 0.000001);
    EXPECT_LT(fabs(fExpectedWaterDeficit - fActualWaterDeficit), 0.000001);
    EXPECT_LT(fabs(fExpectedSeasonalPrecip - fActualSeasonalPrecip), 0.000001);

    p_oClimateGrid->GetValueOfCell(0, 0, iTempCode, &fActualTemp);
    p_oClimateGrid->GetValueOfCell(0, 0, iPrecipCode, &fActualPrecip);
    EXPECT_LT(fabs(fExpectedPrecip - fActualPrecip), 0.000001);
    EXPECT_LT(fabs(fExpectedTemp - fActualTemp), 0.000001);

    //Timestep 3
    p_oSimManager->RunSim(1);
    fExpectedTemp = 8.04;
    fActualPrecip = p_oPlot->GetMeanAnnualPrecip();
    fActualTemp = p_oPlot->GetMeanAnnualTemp();
    fActualWaterDeficit = p_oPlot->GetWaterDeficit();
    fActualSeasonalPrecip = p_oPlot->GetSeasonalPrecipitation();

    EXPECT_LT(fabs(fExpectedPrecip - fActualPrecip), 0.000001);
    EXPECT_LT(fabs(fExpectedTemp - fActualTemp), 0.000001);
    EXPECT_LT(fabs(fExpectedWaterDeficit - fActualWaterDeficit), 0.000001);
    EXPECT_LT(fabs(fExpectedSeasonalPrecip - fActualSeasonalPrecip), 0.000001);

    p_oClimateGrid->GetValueOfCell(0, 0, iTempCode, &fActualTemp);
    p_oClimateGrid->GetValueOfCell(0, 0, iPrecipCode, &fActualPrecip);
    EXPECT_LT(fabs(fExpectedPrecip - fActualPrecip), 0.000001);
    EXPECT_LT(fabs(fExpectedTemp - fActualTemp), 0.000001);

    //Timestep 4
    p_oSimManager->RunSim(1);
    fExpectedTemp = 8.06;
    fActualPrecip = p_oPlot->GetMeanAnnualPrecip();
    fActualTemp = p_oPlot->GetMeanAnnualTemp();
    fActualWaterDeficit = p_oPlot->GetWaterDeficit();
    fActualSeasonalPrecip = p_oPlot->GetSeasonalPrecipitation();

    EXPECT_LT(fabs(fExpectedPrecip - fActualPrecip), 0.000001);
    EXPECT_LT(fabs(fExpectedTemp - fActualTemp), 0.000001);
    EXPECT_LT(fabs(fExpectedWaterDeficit - fActualWaterDeficit), 0.000001);
    EXPECT_LT(fabs(fExpectedSeasonalPrecip - fActualSeasonalPrecip), 0.000001);

    p_oClimateGrid->GetValueOfCell(0, 0, iTempCode, &fActualTemp);
    p_oClimateGrid->GetValueOfCell(0, 0, iPrecipCode, &fActualPrecip);
    EXPECT_LT(fabs(fExpectedPrecip - fActualPrecip), 0.000001);
    EXPECT_LT(fabs(fExpectedTemp - fActualTemp), 0.000001);

    //Timestep 5
    p_oSimManager->RunSim(1);
    fExpectedTemp = 8.08;
    fActualPrecip = p_oPlot->GetMeanAnnualPrecip();
    fActualTemp = p_oPlot->GetMeanAnnualTemp();
    fActualWaterDeficit = p_oPlot->GetWaterDeficit();
    fActualSeasonalPrecip = p_oPlot->GetSeasonalPrecipitation();

    EXPECT_LT(fabs(fExpectedPrecip - fActualPrecip), 0.000001);
    EXPECT_LT(fabs(fExpectedTemp - fActualTemp), 0.000001);
    EXPECT_LT(fabs(fExpectedWaterDeficit - fActualWaterDeficit), 0.000001);
    EXPECT_LT(fabs(fExpectedSeasonalPrecip - fActualSeasonalPrecip), 0.000001);

    p_oClimateGrid->GetValueOfCell(0, 0, iTempCode, &fActualTemp);
    p_oClimateGrid->GetValueOfCell(0, 0, iPrecipCode, &fActualPrecip);
    EXPECT_LT(fabs(fExpectedPrecip - fActualPrecip), 0.000001);
    EXPECT_LT(fabs(fExpectedTemp - fActualTemp), 0.000001);
    delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

/////////////////////////////////////////////////////////////////////////////
// TestNormalProcessingRun4()
// Tests normal processing for a 1-year timestep, only precipitation.
// WriteClimateChangeXMLFile4() does setup.
/////////////////////////////////////////////////////////////////////////////
TEST(ClimateChange, TestNormalProcessingRun4) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    clPlot *p_oPlot;
    clGrid *p_oClimateGrid;
    float fActualTemp, fExpectedTemp, fActualPrecip, fExpectedPrecip,
          fActualWaterDeficit, fExpectedWaterDeficit,
          fActualSeasonalPrecip, fExpectedSeasonalPrecip;
    int iTempCode, iPrecipCode;

    //Feed our file to the sim manager
    p_oSimManager->ReadFile(WriteClimateChangeXMLFile4());
    p_oPlot = p_oSimManager->GetPlotObject();
    p_oClimateGrid = p_oSimManager->GetGridObject("State Variables");
    iTempCode = p_oClimateGrid->GetFloatDataCode("Temp.C");
    iPrecipCode = p_oClimateGrid->GetFloatDataCode("Precip.mm");

    //Initial conditions
    fExpectedPrecip = 1000;
    fExpectedTemp = 8;
    fExpectedWaterDeficit = 500;
    fExpectedSeasonalPrecip = 600;

    fActualPrecip = p_oPlot->GetMeanAnnualPrecip();
    fActualTemp = p_oPlot->GetMeanAnnualTemp();
    fActualWaterDeficit = p_oPlot->GetWaterDeficit();
    fActualSeasonalPrecip = p_oPlot->GetSeasonalPrecipitation();

    EXPECT_LT(fabs(fExpectedPrecip - fActualPrecip), 0.000001);
    EXPECT_LT(fabs(fExpectedTemp - fActualTemp), 0.000001);
    EXPECT_LT(fabs(fExpectedWaterDeficit - fActualWaterDeficit), 0.000001);
    EXPECT_LT(fabs(fExpectedSeasonalPrecip - fActualSeasonalPrecip), 0.000001);

    p_oClimateGrid->GetValueOfCell(0, 0, iTempCode, &fActualTemp);
    p_oClimateGrid->GetValueOfCell(0, 0, iPrecipCode, &fActualPrecip);
    EXPECT_LT(fabs(fExpectedPrecip - fActualPrecip), 0.000001);
    EXPECT_LT(fabs(fExpectedTemp - fActualTemp), 0.000001);

    //Timestep 1
    p_oSimManager->RunSim(1);
    fExpectedPrecip = 1000;
    fActualPrecip = p_oPlot->GetMeanAnnualPrecip();
    fActualTemp = p_oPlot->GetMeanAnnualTemp();
    fActualWaterDeficit = p_oPlot->GetWaterDeficit();
    fActualSeasonalPrecip = p_oPlot->GetSeasonalPrecipitation();

    EXPECT_LT(fabs(fExpectedPrecip - fActualPrecip), 0.000001);
    EXPECT_LT(fabs(fExpectedTemp - fActualTemp), 0.000001);
    EXPECT_LT(fabs(fExpectedWaterDeficit - fActualWaterDeficit), 0.000001);
    EXPECT_LT(fabs(fExpectedSeasonalPrecip - fActualSeasonalPrecip), 0.000001);

    p_oClimateGrid->GetValueOfCell(0, 0, iTempCode, &fActualTemp);
    p_oClimateGrid->GetValueOfCell(0, 0, iPrecipCode, &fActualPrecip);
    EXPECT_LT(fabs(fExpectedPrecip - fActualPrecip), 0.000001);
    EXPECT_LT(fabs(fExpectedTemp - fActualTemp), 0.000001);

    //Timestep 2
    p_oSimManager->RunSim(1);
    fExpectedPrecip = 1000.01;
    fActualPrecip = p_oPlot->GetMeanAnnualPrecip();
    fActualTemp = p_oPlot->GetMeanAnnualTemp();
    fActualWaterDeficit = p_oPlot->GetWaterDeficit();
    fActualSeasonalPrecip = p_oPlot->GetSeasonalPrecipitation();

    EXPECT_LT(fabs(fExpectedPrecip - fActualPrecip), 0.000001);
    EXPECT_LT(fabs(fExpectedTemp - fActualTemp), 0.000001);
    EXPECT_LT(fabs(fExpectedWaterDeficit - fActualWaterDeficit), 0.000001);
    EXPECT_LT(fabs(fExpectedSeasonalPrecip - fActualSeasonalPrecip), 0.000001);

    p_oClimateGrid->GetValueOfCell(0, 0, iTempCode, &fActualTemp);
    p_oClimateGrid->GetValueOfCell(0, 0, iPrecipCode, &fActualPrecip);
    EXPECT_LT(fabs(fExpectedPrecip - fActualPrecip), 0.000001);
    EXPECT_LT(fabs(fExpectedTemp - fActualTemp), 0.000001);

    //Timestep 3
    p_oSimManager->RunSim(1);
    fExpectedPrecip = 1000.04;
    fActualPrecip = p_oPlot->GetMeanAnnualPrecip();
    fActualTemp = p_oPlot->GetMeanAnnualTemp();
    fActualWaterDeficit = p_oPlot->GetWaterDeficit();
    fActualSeasonalPrecip = p_oPlot->GetSeasonalPrecipitation();

    EXPECT_LT(fabs(fExpectedPrecip - fActualPrecip), 0.000001);
    EXPECT_LT(fabs(fExpectedTemp - fActualTemp), 0.000001);
    EXPECT_LT(fabs(fExpectedWaterDeficit - fActualWaterDeficit), 0.000001);
    EXPECT_LT(fabs(fExpectedSeasonalPrecip - fActualSeasonalPrecip), 0.000001);

    p_oClimateGrid->GetValueOfCell(0, 0, iTempCode, &fActualTemp);
    p_oClimateGrid->GetValueOfCell(0, 0, iPrecipCode, &fActualPrecip);
    EXPECT_LT(fabs(fExpectedPrecip - fActualPrecip), 0.000001);
    EXPECT_LT(fabs(fExpectedTemp - fActualTemp), 0.000001);

    //Timestep 4
    p_oSimManager->RunSim(1);
    fExpectedPrecip = 1000.09;
    fActualPrecip = p_oPlot->GetMeanAnnualPrecip();
    fActualTemp = p_oPlot->GetMeanAnnualTemp();
    fActualWaterDeficit = p_oPlot->GetWaterDeficit();
    fActualSeasonalPrecip = p_oPlot->GetSeasonalPrecipitation();

    EXPECT_LT(fabs(fExpectedPrecip - fActualPrecip), 0.000001);
    EXPECT_LT(fabs(fExpectedTemp - fActualTemp), 0.000001);
    EXPECT_LT(fabs(fExpectedWaterDeficit - fActualWaterDeficit), 0.000001);
    EXPECT_LT(fabs(fExpectedSeasonalPrecip - fActualSeasonalPrecip), 0.000001);

    p_oClimateGrid->GetValueOfCell(0, 0, iTempCode, &fActualTemp);
    p_oClimateGrid->GetValueOfCell(0, 0, iPrecipCode, &fActualPrecip);
    EXPECT_LT(fabs(fExpectedPrecip - fActualPrecip), 0.000001);
    EXPECT_LT(fabs(fExpectedTemp - fActualTemp), 0.000001);

    //Timestep 5
    p_oSimManager->RunSim(1);
    fExpectedPrecip = 1000.16;
    fActualPrecip = p_oPlot->GetMeanAnnualPrecip();
    fActualTemp = p_oPlot->GetMeanAnnualTemp();
    fActualWaterDeficit = p_oPlot->GetWaterDeficit();
    fActualSeasonalPrecip = p_oPlot->GetSeasonalPrecipitation();

    EXPECT_LT(fabs(fExpectedPrecip - fActualPrecip), 0.000001);
    EXPECT_LT(fabs(fExpectedTemp - fActualTemp), 0.000001);
    EXPECT_LT(fabs(fExpectedWaterDeficit - fActualWaterDeficit), 0.000001);
    EXPECT_LT(fabs(fExpectedSeasonalPrecip - fActualSeasonalPrecip), 0.000001);

    p_oClimateGrid->GetValueOfCell(0, 0, iTempCode, &fActualTemp);
    p_oClimateGrid->GetValueOfCell(0, 0, iPrecipCode, &fActualPrecip);
    EXPECT_LT(fabs(fExpectedPrecip - fActualPrecip), 0.000001);
    EXPECT_LT(fabs(fExpectedTemp - fActualTemp), 0.000001);
    delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

/////////////////////////////////////////////////////////////////////////////
// TestNormalProcessingRun5()
// Tests normal processing for a 1-year timestep.
// WriteClimateChangeXMLFile5() does setup.
/////////////////////////////////////////////////////////////////////////////
TEST(ClimateChange, TestNormalProcessingRun5) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    clPlot *p_oPlot;
    clGrid *p_oClimateGrid;
    float fActualTemp, fExpectedTemp, fActualPrecip, fExpectedPrecip,
          fActualWaterDeficit, fExpectedWaterDeficit,
          fActualSeasonalPrecip, fExpectedSeasonalPrecip;
    int iTempCode, iPrecipCode;

    //Feed our file to the sim manager
    p_oSimManager->ReadFile(WriteClimateChangeXMLFile5());
    p_oPlot = p_oSimManager->GetPlotObject();
    p_oClimateGrid = p_oSimManager->GetGridObject("State Variables");
    iTempCode = p_oClimateGrid->GetFloatDataCode("Temp.C");
    iPrecipCode = p_oClimateGrid->GetFloatDataCode("Precip.mm");

    //Initial conditions
    fExpectedPrecip = 1000;
    fExpectedTemp = 8;
    fExpectedWaterDeficit = 500;
    fExpectedSeasonalPrecip = 600;

    fActualPrecip = p_oPlot->GetMeanAnnualPrecip();
    fActualTemp = p_oPlot->GetMeanAnnualTemp();
    fActualWaterDeficit = p_oPlot->GetWaterDeficit();
    fActualSeasonalPrecip = p_oPlot->GetSeasonalPrecipitation();

    EXPECT_LT(fabs(fExpectedPrecip - fActualPrecip), 0.000001);
    EXPECT_LT(fabs(fExpectedTemp - fActualTemp), 0.000001);
    EXPECT_LT(fabs(fExpectedWaterDeficit - fActualWaterDeficit), 0.000001);
    EXPECT_LT(fabs(fExpectedSeasonalPrecip - fActualSeasonalPrecip), 0.000001);

    p_oClimateGrid->GetValueOfCell(0, 0, iTempCode, &fActualTemp);
    p_oClimateGrid->GetValueOfCell(0, 0, iPrecipCode, &fActualPrecip);
    EXPECT_LT(fabs(fExpectedPrecip - fActualPrecip), 0.000001);
    EXPECT_LT(fabs(fExpectedTemp - fActualTemp), 0.000001);

    //Timestep 1
    p_oSimManager->RunSim(1);
    fExpectedPrecip = 1000;
    fExpectedTemp = 8;
    fExpectedWaterDeficit = 500;
    fExpectedSeasonalPrecip = 600;

    fActualPrecip = p_oPlot->GetMeanAnnualPrecip();
    fActualTemp = p_oPlot->GetMeanAnnualTemp();
    fActualWaterDeficit = p_oPlot->GetWaterDeficit();
    fActualSeasonalPrecip = p_oPlot->GetSeasonalPrecipitation();

    EXPECT_LT(fabs(fExpectedPrecip - fActualPrecip), 0.000001);
    EXPECT_LT(fabs(fExpectedTemp - fActualTemp), 0.000001);
    EXPECT_LT(fabs(fExpectedWaterDeficit - fActualWaterDeficit), 0.000001);
    EXPECT_LT(fabs(fExpectedSeasonalPrecip - fActualSeasonalPrecip), 0.000001);

    p_oClimateGrid->GetValueOfCell(0, 0, iTempCode, &fActualTemp);
    p_oClimateGrid->GetValueOfCell(0, 0, iPrecipCode, &fActualPrecip);
    EXPECT_LT(fabs(fExpectedPrecip - fActualPrecip), 0.000001);
    EXPECT_LT(fabs(fExpectedTemp - fActualTemp), 0.000001);

    //Timestep 2
    p_oSimManager->RunSim(1);
    fExpectedPrecip = 1010;
    fExpectedTemp = 8.4;
    fExpectedSeasonalPrecip = 606;

    fActualPrecip = p_oPlot->GetMeanAnnualPrecip();
    fActualTemp = p_oPlot->GetMeanAnnualTemp();
    fActualWaterDeficit = p_oPlot->GetWaterDeficit();
    fActualSeasonalPrecip = p_oPlot->GetSeasonalPrecipitation();

    EXPECT_LT(fabs(fExpectedPrecip - fActualPrecip), 0.000001);
    EXPECT_LT(fabs(fExpectedTemp - fActualTemp), 0.000001);
    EXPECT_LT(fabs(fExpectedWaterDeficit - fActualWaterDeficit), 0.000001);
    EXPECT_LT(fabs(fExpectedSeasonalPrecip - fActualSeasonalPrecip), 0.000001);

    p_oClimateGrid->GetValueOfCell(0, 0, iTempCode, &fActualTemp);
    p_oClimateGrid->GetValueOfCell(0, 0, iPrecipCode, &fActualPrecip);
    EXPECT_LT(fabs(fExpectedPrecip - fActualPrecip), 0.000001);
    EXPECT_LT(fabs(fExpectedTemp - fActualTemp), 0.000001);

    //Timestep 3
    p_oSimManager->RunSim(1);
    fExpectedPrecip = 1040;
    fExpectedTemp = 9.13137085;
    fExpectedSeasonalPrecip = 624;

    fActualPrecip = p_oPlot->GetMeanAnnualPrecip();
    fActualTemp = p_oPlot->GetMeanAnnualTemp();
    fActualWaterDeficit = p_oPlot->GetWaterDeficit();
    fActualSeasonalPrecip = p_oPlot->GetSeasonalPrecipitation();

    EXPECT_LT(fabs(fExpectedPrecip - fActualPrecip), 0.000001);
    EXPECT_LT(fabs(fExpectedTemp - fActualTemp), 0.000001);
    EXPECT_LT(fabs(fExpectedWaterDeficit - fActualWaterDeficit), 0.000001);
    EXPECT_LT(fabs(fExpectedSeasonalPrecip - fActualSeasonalPrecip), 0.000001);

    p_oClimateGrid->GetValueOfCell(0, 0, iTempCode, &fActualTemp);
    p_oClimateGrid->GetValueOfCell(0, 0, iPrecipCode, &fActualPrecip);
    EXPECT_LT(fabs(fExpectedPrecip - fActualPrecip), 0.000001);
    EXPECT_LT(fabs(fExpectedTemp - fActualTemp), 0.000001);

    //Timestep 4
    p_oSimManager->RunSim(1);
    fExpectedPrecip = 1090;
    fExpectedTemp = 10.07846097;
    fExpectedSeasonalPrecip = 654;

    fActualPrecip = p_oPlot->GetMeanAnnualPrecip();
    fActualTemp = p_oPlot->GetMeanAnnualTemp();
    fActualWaterDeficit = p_oPlot->GetWaterDeficit();
    fActualSeasonalPrecip = p_oPlot->GetSeasonalPrecipitation();

    EXPECT_LT(fabs(fExpectedPrecip - fActualPrecip), 0.000001);
    EXPECT_LT(fabs(fExpectedTemp - fActualTemp), 0.000001);
    EXPECT_LT(fabs(fExpectedWaterDeficit - fActualWaterDeficit), 0.000001);
    EXPECT_LT(fabs(fExpectedSeasonalPrecip - fActualSeasonalPrecip), 0.000001);

    p_oClimateGrid->GetValueOfCell(0, 0, iTempCode, &fActualTemp);
    p_oClimateGrid->GetValueOfCell(0, 0, iPrecipCode, &fActualPrecip);
    EXPECT_LT(fabs(fExpectedPrecip - fActualPrecip), 0.000001);
    EXPECT_LT(fabs(fExpectedTemp - fActualTemp), 0.000001);

    //Timestep 5
    p_oSimManager->RunSim(1);
    fExpectedPrecip = 1160;
    fExpectedTemp = 11.2;
    fExpectedSeasonalPrecip = 696;

    fActualPrecip = p_oPlot->GetMeanAnnualPrecip();
    fActualTemp = p_oPlot->GetMeanAnnualTemp();
    fActualWaterDeficit = p_oPlot->GetWaterDeficit();
    fActualSeasonalPrecip = p_oPlot->GetSeasonalPrecipitation();

    EXPECT_LT(fabs(fExpectedPrecip - fActualPrecip), 0.000001);
    EXPECT_LT(fabs(fExpectedTemp - fActualTemp), 0.000001);
    EXPECT_LT(fabs(fExpectedWaterDeficit - fActualWaterDeficit), 0.000001);
    EXPECT_LT(fabs(fExpectedSeasonalPrecip - fActualSeasonalPrecip), 0.000001);

    p_oClimateGrid->GetValueOfCell(0, 0, iTempCode, &fActualTemp);
    p_oClimateGrid->GetValueOfCell(0, 0, iPrecipCode, &fActualPrecip);
    EXPECT_LT(fabs(fExpectedPrecip - fActualPrecip), 0.000001);
    EXPECT_LT(fabs(fExpectedTemp - fActualTemp), 0.000001);

    //Timestep 6
    p_oSimManager->RunSim(1);
    fExpectedPrecip = 1210;
    fExpectedTemp = 12;
    fExpectedSeasonalPrecip = 726;

    fActualPrecip = p_oPlot->GetMeanAnnualPrecip();
    fActualTemp = p_oPlot->GetMeanAnnualTemp();
    fActualWaterDeficit = p_oPlot->GetWaterDeficit();
    fActualSeasonalPrecip = p_oPlot->GetSeasonalPrecipitation();

    EXPECT_LT(fabs(fExpectedPrecip - fActualPrecip), 0.000001);
    EXPECT_LT(fabs(fExpectedTemp - fActualTemp), 0.000001);
    EXPECT_LT(fabs(fExpectedWaterDeficit - fActualWaterDeficit), 0.000001);
    EXPECT_LT(fabs(fExpectedSeasonalPrecip - fActualSeasonalPrecip), 0.000001);

    p_oClimateGrid->GetValueOfCell(0, 0, iTempCode, &fActualTemp);
    p_oClimateGrid->GetValueOfCell(0, 0, iPrecipCode, &fActualPrecip);
    EXPECT_LT(fabs(fExpectedPrecip - fActualPrecip), 0.000001);
    EXPECT_LT(fabs(fExpectedTemp - fActualTemp), 0.000001);

    //Timestep 7
    p_oSimManager->RunSim(1);
    fExpectedPrecip = 1210;
    fExpectedTemp = 12;
    fExpectedSeasonalPrecip = 726;

    fActualPrecip = p_oPlot->GetMeanAnnualPrecip();
    fActualTemp = p_oPlot->GetMeanAnnualTemp();
    fActualWaterDeficit = p_oPlot->GetWaterDeficit();
    fActualSeasonalPrecip = p_oPlot->GetSeasonalPrecipitation();

    EXPECT_LT(fabs(fExpectedPrecip - fActualPrecip), 0.000001);
    EXPECT_LT(fabs(fExpectedTemp - fActualTemp), 0.000001);
    EXPECT_LT(fabs(fExpectedWaterDeficit - fActualWaterDeficit), 0.000001);
    EXPECT_LT(fabs(fExpectedSeasonalPrecip - fActualSeasonalPrecip), 0.000001);

    p_oClimateGrid->GetValueOfCell(0, 0, iTempCode, &fActualTemp);
    p_oClimateGrid->GetValueOfCell(0, 0, iPrecipCode, &fActualPrecip);
    EXPECT_LT(fabs(fExpectedPrecip - fActualPrecip), 0.000001);
    EXPECT_LT(fabs(fExpectedTemp - fActualTemp), 0.000001);

    //Timestep 8
    p_oSimManager->RunSim(1);
    fExpectedPrecip = 1210;
    fExpectedTemp = 12;
    fExpectedSeasonalPrecip = 726;

    fActualPrecip = p_oPlot->GetMeanAnnualPrecip();
    fActualTemp = p_oPlot->GetMeanAnnualTemp();
    fActualWaterDeficit = p_oPlot->GetWaterDeficit();
    fActualSeasonalPrecip = p_oPlot->GetSeasonalPrecipitation();

    EXPECT_LT(fabs(fExpectedPrecip - fActualPrecip), 0.000001);
    EXPECT_LT(fabs(fExpectedTemp - fActualTemp), 0.000001);
    EXPECT_LT(fabs(fExpectedWaterDeficit - fActualWaterDeficit), 0.000001);
    EXPECT_LT(fabs(fExpectedSeasonalPrecip - fActualSeasonalPrecip), 0.000001);

    p_oClimateGrid->GetValueOfCell(0, 0, iTempCode, &fActualTemp);
    p_oClimateGrid->GetValueOfCell(0, 0, iPrecipCode, &fActualPrecip);
    EXPECT_LT(fabs(fExpectedPrecip - fActualPrecip), 0.000001);
    EXPECT_LT(fabs(fExpectedTemp - fActualTemp), 0.000001);

    //Timestep 9
    p_oSimManager->RunSim(1);
    fExpectedPrecip = 1210;
    fExpectedTemp = 12;
    fExpectedSeasonalPrecip = 726;

    fActualPrecip = p_oPlot->GetMeanAnnualPrecip();
    fActualTemp = p_oPlot->GetMeanAnnualTemp();
    fActualWaterDeficit = p_oPlot->GetWaterDeficit();
    fActualSeasonalPrecip = p_oPlot->GetSeasonalPrecipitation();

    EXPECT_LT(fabs(fExpectedPrecip - fActualPrecip), 0.000001);
    EXPECT_LT(fabs(fExpectedTemp - fActualTemp), 0.000001);
    EXPECT_LT(fabs(fExpectedWaterDeficit - fActualWaterDeficit), 0.000001);
    EXPECT_LT(fabs(fExpectedSeasonalPrecip - fActualSeasonalPrecip), 0.000001);

    p_oClimateGrid->GetValueOfCell(0, 0, iTempCode, &fActualTemp);
    p_oClimateGrid->GetValueOfCell(0, 0, iPrecipCode, &fActualPrecip);
    EXPECT_LT(fabs(fExpectedPrecip - fActualPrecip), 0.000001);
    EXPECT_LT(fabs(fExpectedTemp - fActualTemp), 0.000001);
    delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

/////////////////////////////////////////////////////////////////////////////
// TestNormalProcessingRun6()
// Tests normal processing for a 1-year timestep.
// WriteClimateChangeXMLFile6() does setup.
/////////////////////////////////////////////////////////////////////////////
TEST(ClimateChange, TestNormalProcessingRun6) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    clPlot *p_oPlot;
    clGrid *p_oClimateGrid;
    float fActualTemp, fExpectedTemp, fActualPrecip, fExpectedPrecip,
          fActualWaterDeficit, fExpectedWaterDeficit,
          fActualSeasonalPrecip, fExpectedSeasonalPrecip;
    int iTempCode, iPrecipCode;

    //Feed our file to the sim manager
    p_oSimManager->ReadFile(WriteClimateChangeXMLFile6());
    p_oPlot = p_oSimManager->GetPlotObject();
    p_oClimateGrid = p_oSimManager->GetGridObject("State Variables");
    iTempCode = p_oClimateGrid->GetFloatDataCode("Temp.C");
    iPrecipCode = p_oClimateGrid->GetFloatDataCode("Precip.mm");

    //Initial conditions
    fExpectedPrecip = 1000;
    fExpectedTemp = 8;
    fExpectedWaterDeficit = 500;
    fExpectedSeasonalPrecip = 600;

    fActualPrecip = p_oPlot->GetMeanAnnualPrecip();
    fActualTemp = p_oPlot->GetMeanAnnualTemp();
    fActualWaterDeficit = p_oPlot->GetWaterDeficit();
    fActualSeasonalPrecip = p_oPlot->GetSeasonalPrecipitation();

    EXPECT_LT(fabs(fExpectedPrecip - fActualPrecip), 0.000001);
    EXPECT_LT(fabs(fExpectedTemp - fActualTemp), 0.000001);
    EXPECT_LT(fabs(fExpectedWaterDeficit - fActualWaterDeficit), 0.000001);
    EXPECT_LT(fabs(fExpectedSeasonalPrecip - fActualSeasonalPrecip), 0.000001);

    p_oClimateGrid->GetValueOfCell(0, 0, iTempCode, &fActualTemp);
    p_oClimateGrid->GetValueOfCell(0, 0, iPrecipCode, &fActualPrecip);
    EXPECT_LT(fabs(fExpectedPrecip - fActualPrecip), 0.000001);
    EXPECT_LT(fabs(fExpectedTemp - fActualTemp), 0.000001);

    //Timestep 1
    p_oSimManager->RunSim(1);
    fExpectedPrecip = 1000;
    fExpectedTemp = 8;
    fExpectedSeasonalPrecip = 600;

    fActualPrecip = p_oPlot->GetMeanAnnualPrecip();
    fActualTemp = p_oPlot->GetMeanAnnualTemp();
    fActualWaterDeficit = p_oPlot->GetWaterDeficit();
    fActualSeasonalPrecip = p_oPlot->GetSeasonalPrecipitation();

    EXPECT_LT(fabs(fExpectedPrecip - fActualPrecip), 0.000001);
    EXPECT_LT(fabs(fExpectedTemp - fActualTemp), 0.000001);
    EXPECT_LT(fabs(fExpectedWaterDeficit - fActualWaterDeficit), 0.000001);
    EXPECT_LT(fabs(fExpectedSeasonalPrecip - fActualSeasonalPrecip), 0.000001);

    p_oClimateGrid->GetValueOfCell(0, 0, iTempCode, &fActualTemp);
    p_oClimateGrid->GetValueOfCell(0, 0, iPrecipCode, &fActualPrecip);
    EXPECT_LT(fabs(fExpectedPrecip - fActualPrecip), 0.000001);
    EXPECT_LT(fabs(fExpectedTemp - fActualTemp), 0.000001);

    //Timestep 2
    p_oSimManager->RunSim(1);
    fExpectedPrecip = 990;
    fExpectedTemp = 7.8;
    fExpectedSeasonalPrecip = 594;

    fActualPrecip = p_oPlot->GetMeanAnnualPrecip();
    fActualTemp = p_oPlot->GetMeanAnnualTemp();
    fActualWaterDeficit = p_oPlot->GetWaterDeficit();
    fActualSeasonalPrecip = p_oPlot->GetSeasonalPrecipitation();

    EXPECT_LT(fabs(fExpectedPrecip - fActualPrecip), 0.000001);
    EXPECT_LT(fabs(fExpectedTemp - fActualTemp), 0.000001);
    EXPECT_LT(fabs(fExpectedWaterDeficit - fActualWaterDeficit), 0.000001);
    EXPECT_LT(fabs(fExpectedSeasonalPrecip - fActualSeasonalPrecip), 0.000001);

    p_oClimateGrid->GetValueOfCell(0, 0, iTempCode, &fActualTemp);
    p_oClimateGrid->GetValueOfCell(0, 0, iPrecipCode, &fActualPrecip);
    EXPECT_LT(fabs(fExpectedPrecip - fActualPrecip), 0.000001);
    EXPECT_LT(fabs(fExpectedTemp - fActualTemp), 0.000001);

    //Timestep 3
    p_oSimManager->RunSim(1);
    fExpectedPrecip = 960;
    fExpectedTemp = 7.434315;
    fExpectedSeasonalPrecip = 576;

    fActualPrecip = p_oPlot->GetMeanAnnualPrecip();
    fActualTemp = p_oPlot->GetMeanAnnualTemp();
    fActualWaterDeficit = p_oPlot->GetWaterDeficit();
    fActualSeasonalPrecip = p_oPlot->GetSeasonalPrecipitation();

    EXPECT_LT(fabs(fExpectedPrecip - fActualPrecip), 0.000001);
    EXPECT_LT(fabs(fExpectedTemp - fActualTemp), 0.000001);
    EXPECT_LT(fabs(fExpectedWaterDeficit - fActualWaterDeficit), 0.000001);
    EXPECT_LT(fabs(fExpectedSeasonalPrecip - fActualSeasonalPrecip), 0.000001);

    p_oClimateGrid->GetValueOfCell(0, 0, iTempCode, &fActualTemp);
    p_oClimateGrid->GetValueOfCell(0, 0, iPrecipCode, &fActualPrecip);
    EXPECT_LT(fabs(fExpectedPrecip - fActualPrecip), 0.000001);
    EXPECT_LT(fabs(fExpectedTemp - fActualTemp), 0.000001);

    //Timestep 4
    p_oSimManager->RunSim(1);
    fExpectedPrecip = 910;
    fExpectedTemp = 7;
    fExpectedSeasonalPrecip = 546;

    fActualPrecip = p_oPlot->GetMeanAnnualPrecip();
    fActualTemp = p_oPlot->GetMeanAnnualTemp();
    fActualWaterDeficit = p_oPlot->GetWaterDeficit();
    fActualSeasonalPrecip = p_oPlot->GetSeasonalPrecipitation();

    EXPECT_LT(fabs(fExpectedPrecip - fActualPrecip), 0.000001);
    EXPECT_LT(fabs(fExpectedTemp - fActualTemp), 0.000001);
    EXPECT_LT(fabs(fExpectedWaterDeficit - fActualWaterDeficit), 0.000001);
    EXPECT_LT(fabs(fExpectedSeasonalPrecip - fActualSeasonalPrecip), 0.000001);

    p_oClimateGrid->GetValueOfCell(0, 0, iTempCode, &fActualTemp);
    p_oClimateGrid->GetValueOfCell(0, 0, iPrecipCode, &fActualPrecip);
    EXPECT_LT(fabs(fExpectedPrecip - fActualPrecip), 0.000001);
    EXPECT_LT(fabs(fExpectedTemp - fActualTemp), 0.000001);

    //Timestep 5
    p_oSimManager->RunSim(1);
    fExpectedPrecip = 900;
    fExpectedTemp = 7;
    fExpectedSeasonalPrecip = 540;

    fActualPrecip = p_oPlot->GetMeanAnnualPrecip();
    fActualTemp = p_oPlot->GetMeanAnnualTemp();
    fActualWaterDeficit = p_oPlot->GetWaterDeficit();
    fActualSeasonalPrecip = p_oPlot->GetSeasonalPrecipitation();

    EXPECT_LT(fabs(fExpectedPrecip - fActualPrecip), 0.000001);
    EXPECT_LT(fabs(fExpectedTemp - fActualTemp), 0.000001);
    EXPECT_LT(fabs(fExpectedWaterDeficit - fActualWaterDeficit), 0.000001);
    EXPECT_LT(fabs(fExpectedSeasonalPrecip - fActualSeasonalPrecip), 0.000001);

    p_oClimateGrid->GetValueOfCell(0, 0, iTempCode, &fActualTemp);
    p_oClimateGrid->GetValueOfCell(0, 0, iPrecipCode, &fActualPrecip);
    EXPECT_LT(fabs(fExpectedPrecip - fActualPrecip), 0.000001);
    EXPECT_LT(fabs(fExpectedTemp - fActualTemp), 0.000001);

    //Timestep 6
    p_oSimManager->RunSim(1);
    fExpectedPrecip = 900;
    fExpectedTemp = 7;
    fExpectedSeasonalPrecip = 540;

    fActualPrecip = p_oPlot->GetMeanAnnualPrecip();
    fActualTemp = p_oPlot->GetMeanAnnualTemp();
    fActualWaterDeficit = p_oPlot->GetWaterDeficit();
    fActualSeasonalPrecip = p_oPlot->GetSeasonalPrecipitation();

    EXPECT_LT(fabs(fExpectedPrecip - fActualPrecip), 0.000001);
    EXPECT_LT(fabs(fExpectedTemp - fActualTemp), 0.000001);
    EXPECT_LT(fabs(fExpectedWaterDeficit - fActualWaterDeficit), 0.000001);
    EXPECT_LT(fabs(fExpectedSeasonalPrecip - fActualSeasonalPrecip), 0.000001);

    p_oClimateGrid->GetValueOfCell(0, 0, iTempCode, &fActualTemp);
    p_oClimateGrid->GetValueOfCell(0, 0, iPrecipCode, &fActualPrecip);
    EXPECT_LT(fabs(fExpectedPrecip - fActualPrecip), 0.000001);
    EXPECT_LT(fabs(fExpectedTemp - fActualTemp), 0.000001);
    delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

/////////////////////////////////////////////////////////////////////////////
// WriteClimateChangeXMLFile1()
/////////////////////////////////////////////////////////////////////////////
const char* WriteClimateChangeXMLFile1()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  std::fstream oOut;
  oOut.open( cFileString, ios::out | ios::trunc );

  WriteClimateChangeCommonStuff(oOut, 1);

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
       << "<behaviorName>StateReporter</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>3</listPosition>"
       << "</behavior>"
       << "</behaviorList>"
       << "<ClimateChange2>"
       << "<sc_climateChangePrecipB>0.01</sc_climateChangePrecipB>"
       << "<sc_climateChangePrecipC>2</sc_climateChangePrecipC>"
       << "<sc_climateChangeMinPrecip>900</sc_climateChangeMinPrecip>"
       << "<sc_climateChangeMaxPrecip>2000</sc_climateChangeMaxPrecip>"
       << "<sc_climateChangeOtherPrecip>0</sc_climateChangeOtherPrecip>"
       << "</ClimateChange2>"
       << "<ClimateChange1>"
       << "<sc_climateChangeTempB>0.02</sc_climateChangeTempB>"
       << "<sc_climateChangeTempC>1</sc_climateChangeTempC>"
       << "<sc_climateChangeMinTemp>0</sc_climateChangeMinTemp>"
       << "<sc_climateChangeMaxTemp>10</sc_climateChangeMaxTemp>"
       << "</ClimateChange1>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteClimateChangeXMLFile2()
/////////////////////////////////////////////////////////////////////////////
const char* WriteClimateChangeXMLFile2()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  std::fstream oOut;
  oOut.open( cFileString, ios::out | ios::trunc );

  WriteClimateChangeCommonStuff(oOut, 3);

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
       << "<behaviorName>StateReporter</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>3</listPosition>"
       << "</behavior>"
       << "</behaviorList>"
       << "<ClimateChange2>"
       << "<sc_climateChangePrecipB>0.01</sc_climateChangePrecipB>"
       << "<sc_climateChangePrecipC>2</sc_climateChangePrecipC>"
       << "<sc_climateChangeMinPrecip>900</sc_climateChangeMinPrecip>"
       << "<sc_climateChangeMaxPrecip>2000</sc_climateChangeMaxPrecip>"
       << "<sc_climateChangeOtherPrecip>0</sc_climateChangeOtherPrecip>"
       << "</ClimateChange2>"
       << "<ClimateChange1>"
       << "<sc_climateChangeTempB>0.02</sc_climateChangeTempB>"
       << "<sc_climateChangeTempC>1</sc_climateChangeTempC>"
       << "<sc_climateChangeMinTemp>0</sc_climateChangeMinTemp>"
       << "<sc_climateChangeMaxTemp>10</sc_climateChangeMaxTemp>"
       << "</ClimateChange1>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteClimateChangeXMLFile3()
/////////////////////////////////////////////////////////////////////////////
const char* WriteClimateChangeXMLFile3()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  std::fstream oOut;
  oOut.open( cFileString, ios::out | ios::trunc );

  WriteClimateChangeCommonStuff(oOut, 1);

  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>TemperatureClimateChange</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>StateReporter</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>2</listPosition>"
       << "</behavior>"
       << "</behaviorList>"
       << "<ClimateChange1>"
       << "<sc_climateChangeTempB>0.02</sc_climateChangeTempB>"
       << "<sc_climateChangeTempC>1</sc_climateChangeTempC>"
       << "<sc_climateChangeMinTemp>0</sc_climateChangeMinTemp>"
       << "<sc_climateChangeMaxTemp>10</sc_climateChangeMaxTemp>"
       << "</ClimateChange1>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteClimateChangeXMLFile4()
/////////////////////////////////////////////////////////////////////////////
const char* WriteClimateChangeXMLFile4()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  std::fstream oOut;
  oOut.open( cFileString, ios::out | ios::trunc );

  WriteClimateChangeCommonStuff(oOut, 1);

  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>PrecipitationClimateChange</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>StateReporter</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>2</listPosition>"
       << "</behavior>"
       << "</behaviorList>"
       << "<ClimateChange1>"
       << "<sc_climateChangePrecipB>0.01</sc_climateChangePrecipB>"
       << "<sc_climateChangePrecipC>2</sc_climateChangePrecipC>"
       << "<sc_climateChangeMinPrecip>900</sc_climateChangeMinPrecip>"
       << "<sc_climateChangeMaxPrecip>2000</sc_climateChangeMaxPrecip>"
       << "<sc_climateChangeOtherPrecip>0</sc_climateChangeOtherPrecip>"
       << "</ClimateChange1>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteClimateChangeXMLFile5()
/////////////////////////////////////////////////////////////////////////////
const char* WriteClimateChangeXMLFile5()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  std::fstream oOut;
  oOut.open( cFileString, ios::out | ios::trunc );

  WriteClimateChangeCommonStuff(oOut, 1);

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
       << "<behaviorName>StateReporter</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>3</listPosition>"
       << "</behavior>"
       << "</behaviorList>"
       << "<ClimateChange2>"
       << "<sc_climateChangePrecipB>10</sc_climateChangePrecipB>"
       << "<sc_climateChangePrecipC>2</sc_climateChangePrecipC>"
       << "<sc_climateChangeMinPrecip>900</sc_climateChangeMinPrecip>"
       << "<sc_climateChangeMaxPrecip>1210</sc_climateChangeMaxPrecip>"
       << "<sc_climateChangeOtherPrecip>1</sc_climateChangeOtherPrecip>"
       << "</ClimateChange2>"
       << "<ClimateChange1>"
       << "<sc_climateChangeTempB>0.4</sc_climateChangeTempB>"
       << "<sc_climateChangeTempC>1.5</sc_climateChangeTempC>"
       << "<sc_climateChangeMinTemp>5</sc_climateChangeMinTemp>"
       << "<sc_climateChangeMaxTemp>12</sc_climateChangeMaxTemp>"
       << "</ClimateChange1>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteClimateChangeXMLFile6()
/////////////////////////////////////////////////////////////////////////////
const char* WriteClimateChangeXMLFile6()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  std::fstream oOut;
  oOut.open( cFileString, ios::out | ios::trunc );

  WriteClimateChangeCommonStuff(oOut, 1);

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
       << "<behaviorName>StateReporter</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>3</listPosition>"
       << "</behavior>"
       << "</behaviorList>"
       << "<ClimateChange2>"
       << "<sc_climateChangePrecipB>-10</sc_climateChangePrecipB>"
       << "<sc_climateChangePrecipC>2</sc_climateChangePrecipC>"
       << "<sc_climateChangeMinPrecip>900</sc_climateChangeMinPrecip>"
       << "<sc_climateChangeMaxPrecip>1200</sc_climateChangeMaxPrecip>"
       << "<sc_climateChangeOtherPrecip>1</sc_climateChangeOtherPrecip>"
       << "</ClimateChange2>"
       << "<ClimateChange1>"
       << "<sc_climateChangeTempB>-0.2</sc_climateChangeTempB>"
       << "<sc_climateChangeTempC>1.5</sc_climateChangeTempC>"
       << "<sc_climateChangeMinTemp>7</sc_climateChangeMinTemp>"
       << "<sc_climateChangeMaxTemp>10</sc_climateChangeMaxTemp>"
       << "</ClimateChange1>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteClimateChangeCommonStuff()
/////////////////////////////////////////////////////////////////////////////
void WriteClimateChangeCommonStuff( std::fstream &oOut, int iNumYrsPerTS )
{
  using namespace std;
  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06010101\">"
       << "<plot>"
       << "<timesteps>10</timesteps>"
       << "<yearsPerTimestep>" << iNumYrsPerTS << "</yearsPerTimestep>"
       << "<randomSeed>0</randomSeed>"
       << "<plot_lenX>100</plot_lenX>"
       << "<plot_lenY>100</plot_lenY>"
       << "<plot_precip_mm_yr>1000</plot_precip_mm_yr>"
       << "<plot_temp_C>8</plot_temp_C>"
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
}
