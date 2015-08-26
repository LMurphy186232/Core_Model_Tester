//---------------------------------------------------------------------------
// TestConditOmegaCalculator.cpp
//---------------------------------------------------------------------------
#include "TestConditOmegaCalculator.h"
#include <gtest/gtest.h>
#include <fstream>
#include <math.h>
#include "TreePopulation.h"
#include "SimManager.h"
#include "Grid.h"
#include "BehaviorBase.h"
#include "Plot.h"
#include "ConditOmegaCalculator.h"

////////////////////////////////////////////////////////////////////////////
// TestNormalProcessingRun1()
// Tests normal processing, run 1. WriteConditOmegaCalculatorXMLFile1() does
// setup. Several trees are created and the Condit's Omega calculated.
////////////////////////////////////////////////////////////////////////////
TEST(ConditOmegaCalculator, TestNormalProcessingRun1) {
  clTreePopulation * p_oPop;
  clGrid *p_oGrid;
  std::stringstream sLabel;
  float fExpectedValue, fActualValue, fX, fY, fDBH;
  int iSp, i, j, iCode;

  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    //Load our test file and get our tree population pointers
    p_oSimManager->ReadFile( WriteConditOmegaCalculatorXMLFile1() );
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );
    p_oGrid = p_oSimManager->GetGridObject("Relative Neighborhood Density");
    ASSERT_TRUE(p_oGrid != NULL);
    EXPECT_EQ(p_oGrid->GetNumberXCells(), 1);
    EXPECT_EQ(p_oGrid->GetNumberYCells(), 1);
    fExpectedValue = 1;
    p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("inc"), &fActualValue);
    EXPECT_LT(fabs(fActualValue - fExpectedValue), 0.001);
    fExpectedValue = 50;
    p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("dist"), &fActualValue);
    EXPECT_LT(fabs(fActualValue - fExpectedValue), 0.001);

    //Check the initial conditions - all zeroes
    for (i = 0; i < 50; i++) {
      for (j = 0; j < 4; j++) {
        sLabel << i << "_" << j;
        iCode = p_oGrid->GetFloatDataCode(sLabel.str());
        ASSERT_TRUE(-1 != iCode);
        p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
        EXPECT_LT(fabs(fActualValue), 0.0001);
        sLabel.str("");
      }
    }

    fX = 31.7094184;
    fY = 69.2171281;
    fDBH = 6.70; iSp = 2;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::sapling, fDBH);

    fX = 63.0650021;
    fY = 58.5537260;
    fDBH = 15.58; iSp = 2;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

    fX = 34.6777252;
    fY = 42.6892403;
    fDBH = 19.13; iSp = 0;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

    fX = 60.2542323;
    fY = 43.3365898;
    fDBH = 47.91; iSp = 2;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

    fX = 57.7935430;
    fY = 31.8673210;
    fDBH = 41.56; iSp = 2;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

    fX = 58.5834899;
    fY = 38.0598394;
    fDBH = 25.92; iSp = 2;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

    fX = 61.0027385;
    fY = 69.1505016;
    fDBH = 47.12; iSp = 2;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

    fX = 58.1158336;
    fY = 30.6776078;
    fDBH = 45.25; iSp = 2;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

    fX = 36.6402414;
    fY = 36.9972270;
    fDBH = 23.00; iSp = 0;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

    fX = 68.1446909;
    fY = 61.9238429;
    fDBH = 20.35; iSp = 2;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

    fX = 62.3120718;
    fY = 52.4005773;
    fDBH = 17.07; iSp = 2;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

    fX = 44.6887800;
    fY = 41.9360127;
    fDBH = 22.02; iSp = 0;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

    fX = 52.5822889;
    fY = 31.2152253;
    fDBH = 7.31; iSp = 2;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::sapling, fDBH);

    fX = 56.4709828;
    fY = 37.1044565;
    fDBH = 10.76; iSp = 2;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

    fX = 61.7827570;
    fY = 66.6782430;
    fDBH = 2.53; iSp = 2;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::sapling, fDBH);

    fX = 40.7574851;
    fY = 51.9639395;
    fDBH = 10.81; iSp = 2;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

    fX = 60.7592505;
    fY = 30.0070687;
    fDBH = 22.23; iSp = 2;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

    fX = 38.3173005;
    fY = 59.1225341;
    fDBH = 4.73; iSp = 2;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::sapling, fDBH);

    fX = 54.3454495;
    fY = 39.1810222;
    fDBH = 35.74; iSp = 2;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

    fX = 52.6841327;
    fY = 42.9954431;
    fDBH = 43.69; iSp = 2;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

    fX = 44.7244036;
    fY = 31.3294605;
    fDBH = 4.96; iSp = 0;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::sapling, fDBH);

    fX = 42.2820773;
    fY = 56.6854570;
    fDBH = 1.07; iSp = 2;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::sapling, fDBH);

    fX = 37.3181167;
    fY = 31.1232073;
    fDBH = 24.51; iSp = 0;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

    fX = 59.6902360;
    fY = 31.0386153;
    fDBH = 42.43; iSp = 2;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

    fX = 65.7543677;
    fY = 68.9714840;
    fDBH = 17.64; iSp = 2;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

    fX = 64.0057333;
    fY = 37.9274886;
    fDBH = 39.64; iSp = 2;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

    fX = 42.8191345;
    fY = 54.1697617;
    fDBH = 10.30; iSp = 2;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

    fX = 63.6726781;
    fY = 37.3445726;
    fDBH = 6.88; iSp = 2;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::sapling, fDBH);

    fX = 48.0225822;
    fY = 67.0129890;
    fDBH = 24.28; iSp = 2;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

    fX = 30.0999843;
    fY = 48.0911072;
    fDBH = 13.84; iSp = 2;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

    fX = 67.0225125;
    fY = 46.4747131;
    fDBH = 14.23; iSp = 2;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

    fX = 64.2440628;
    fY = 37.2466892;
    fDBH = 49.45; iSp = 2;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

    fX = 32.5510550;
    fY = 53.7041606;
    fDBH = 35.07; iSp = 2;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

    fX = 64.3337019;
    fY = 55.2130771;
    fDBH = 1.48; iSp = 2;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::sapling, fDBH);

    fX = 69.9937888;
    fY = 59.4101570;
    fDBH = 11.55; iSp = 2;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

    fX = 61.5409042;
    fY = 66.1535237;
    fDBH = 3.25; iSp = 2;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::sapling, fDBH);

    fX = 55.7173425;
    fY = 68.4870485;
    fDBH = 34.48; iSp = 2;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

    fX = 59.5319442;
    fY = 34.7770076;
    fDBH = 7.40; iSp = 2;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::sapling, fDBH);

    fX = 38.7133121;
    fY = 36.8053197;
    fDBH = 44.46; iSp = 0;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

    fX = 66.3748061;
    fY = 67.9110779;
    fDBH = 37.60; iSp = 2;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

    fX = 68.4595765;
    fY = 34.0531134;
    fDBH = 19.03; iSp = 2;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

    fX = 52.5231057;
    fY = 45.6320188;
    fDBH = 10.55; iSp = 1;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

    fX = 35.5425861;
    fY = 66.8206196;
    fDBH = 42.47; iSp = 2;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

    fX = 31.4508971;
    fY = 64.1512154;
    fDBH = 19.47; iSp = 2;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

    fX = 33.0824643;
    fY = 35.3648909;
    fDBH = 41.03; iSp = 0;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

    fX = 66.0341443;
    fY = 59.9338286;
    fDBH = 22.97; iSp = 2;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

    fX = 55.0419430;
    fY = 54.2776736;
    fDBH = 26.11; iSp = 1;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

    fX = 69.4689362;
    fY = 47.0136816;
    fDBH = 5.76; iSp = 2;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

    fX = 66.2749605;
    fY = 30.3135251;
    fDBH = 30.60; iSp = 2;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

    fX = 66.9336249;
    fY = 67.8912659;
    fDBH = 39.27; iSp = 2;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

    fX = 32.0115274;
    fY = 69.6498619;
    fDBH = 28.48; iSp = 2;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

    fX = 35.5562352;
    fY = 32.7346060;
    fDBH = 15.04; iSp = 0;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

    fX = 30.4359842;
    fY = 50.7268044;
    fDBH = 24.25; iSp = 2;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

    fX = 43.0721663;
    fY = 55.4585224;
    fDBH = 8.42; iSp = 2;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

    fX = 58.0836270;
    fY = 37.4290565;
    fDBH = 38.32; iSp = 2;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

    fX = 30.9104683;
    fY = 52.5851442;
    fDBH = 13.62; iSp = 2;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

    fX = 66.6604773;
    fY = 46.9947606;
    fDBH = 4.09; iSp = 2;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

    fX = 46.9727741;
    fY = 48.1382869;
    fDBH = 29.92; iSp = 1;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

    fX = 63.2410097;
    fY = 41.5415066;
    fDBH = 32.91; iSp = 2;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

    fX = 66.2716582;
    fY = 67.5411284;
    fDBH = 46.33; iSp = 2;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

    fX = 50.2501481;
    fY = 58.4426534;
    fDBH = 11.15; iSp = 1;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

    fX = 64.0742451;
    fY = 62.0013591;
    fDBH = 22.10; iSp = 2;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

    fX = 55.1002950;
    fY = 48.0370165;
    fDBH = 33.19; iSp = 1;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

    fX = 41.7031183;
    fY = 53.8484351;
    fDBH = 36.70; iSp = 2;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

    fX = 39.4844218;
    fY = 30.8515324;
    fDBH = 36.48; iSp = 0;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

    fX = 66.0148319;
    fY = 32.0354012;
    fDBH = 44.62; iSp = 2;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

    fX = 57.9983750;
    fY = 50.8579588;
    fDBH = 11.08; iSp = 1;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

    fX = 41.3090853;
    fY = 55.3172117;
    fDBH = 21.98; iSp = 2;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

    fX = 68.0889239;
    fY = 67.8509960;
    fDBH = 49.27; iSp = 2;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

    fX = 59.2650277;
    fY = 30.2195109;
    fDBH = 13.32; iSp = 2;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

    fX = 48.0081818;
    fY = 33.5267253;
    fDBH = 3.70; iSp = 2;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

    fX = 67.3063727;
    fY = 50.6869068;
    fDBH = 1.68; iSp = 2;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

    fX = 62.7331277;
    fY = 36.1758086;
    fDBH = 31.45; iSp = 2;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

    fX = 68.6612698;
    fY = 66.1263193;
    fDBH = 39.46; iSp = 2;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

    fX = 36.3649443;
    fY = 57.7572972;
    fDBH = 21.49; iSp = 2;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

    fX = 40.5483717;
    fY = 57.2168482;
    fDBH = 37.01; iSp = 2;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

    fX = 54.2735002;
    fY = 60.7494505;
    fDBH = 37.65; iSp = 2;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

    fX = 39.9040256;
    fY = 57.0768941;
    fDBH = 31.72; iSp = 2;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

    fX = 56.3782721;
    fY = 59.2669709;
    fDBH = 11.80; iSp = 1;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

    fX = 50.6824674;
    fY = 58.6841613;
    fDBH = 28.86; iSp = 1;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

    fX = 40.1631905;
    fY = 53.7083696;
    fDBH = 29.45; iSp = 2;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

    fX = 39.9462708;
    fY = 57.2334618;
    fDBH = 19.69; iSp = 2;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

    fX = 64.3522870;
    fY = 37.1541965;
    fDBH = 16.45; iSp = 2;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

    fX = 58.4491902;
    fY = 47.5277952;
    fDBH = 32.77; iSp = 1;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

    fX = 66.0808891;
    fY = 48.4055297;
    fDBH = 10.57; iSp = 2;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

    fX = 69.1167040;
    fY = 38.2317015;
    fDBH = 8.51; iSp = 2;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::sapling, fDBH);

    fX = 65.0434486;
    fY = 39.9599933;
    fDBH = 41.08; iSp = 2;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

    fX = 69.8230852;
    fY = 34.3845812;
    fDBH = 20.35; iSp = 2;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

    fX = 42.7282420;
    fY = 30.2865289;
    fDBH = 41.26; iSp = 0;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

    fX = 57.6942266;
    fY = 64.8899863;
    fDBH = 19.07; iSp = 2;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

    fX = 31.2855571;
    fY = 49.1837897;
    fDBH = 3.94; iSp = 2;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::sapling, fDBH);

    fX = 50.5203479;
    fY = 38.9092183;
    fDBH = 34.21; iSp = 2;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

    fX = 56.0964522;
    fY = 55.6961520;
    fDBH = 24.56; iSp = 1;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

    fX = 44.1205560;
    fY = 63.2525782;
    fDBH = 49.64; iSp = 2;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

    fX = 52.1101118;
    fY = 66.2257349;
    fDBH = 4.49; iSp = 2;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

    fX = 34.8577627;
    fY = 55.8509844;
    fDBH = 7.58; iSp = 2;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

    fX = 51.5419791;
    fY = 42.5956021;
    fDBH = 27.52; iSp = 2;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

    fX = 46.1417305;
    fY = 30.7815262;
    fDBH = 47.63; iSp = 2;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

    fX = 30.1654434;
    fY = 65.1138069;
    fDBH = 11.93; iSp = 2;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

    fX = 54.8983830;
    fY = 66.2619967;
    fDBH = 1.96; iSp = 2;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);


    //Create some seedlings and snags to be skipped
    fX = 57.6942266;
    fY = 64.8899863;
    fDBH = 19.07; iSp = 2;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::snag, fDBH);

    fX = 31.2855571;
    fY = 49.1837897;
    fDBH = 0.94; iSp = 2;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::seedling, fDBH);

    fX = 50.5203479;
    fY = 38.9092183;
    fDBH = 34.21; iSp = 2;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::snag, fDBH);

    fX = 56.0964522;
    fY = 55.6961520;
    fDBH = 24.56; iSp = 1;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::snag, fDBH);

    fX = 44.1205560;
    fY = 63.2525782;
    fDBH = 49.64; iSp = 2;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::snag, fDBH);

    fX = 52.1101118;
    fY = 66.2257349;
    fDBH = 4.49; iSp = 2;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::snag, fDBH);

    fX = 34.8577627;
    fY = 55.8509844;
    fDBH = 7.58; iSp = 2;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::snag, fDBH);

    fX = 51.5419791;
    fY = 42.5956021;
    fDBH = 27.52; iSp = 2;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::snag, fDBH);

    fX = 46.1417305;
    fY = 30.7815262;
    fDBH = 47.63; iSp = 2;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::snag, fDBH);

    fX = 30.1654434;
    fY = 65.1138069;
    fDBH = 11.93; iSp = 2;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::snag, fDBH);

    fX = 54.8983830;
    fY = 66.2619967;
    fDBH = 1.96; iSp = 2;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::snag, fDBH);

    fX = 51.5419791;
    fY = 42.5956021;
    fDBH = 0.94; iSp = 3;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::seedling, fDBH);

    fX = 46.1417305;
    fY = 30.7815262;
    fDBH = 0.94; iSp = 3;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::seedling, fDBH);

    fX = 30.1654434;
    fY = 65.1138069;
    fDBH = 0.94; iSp = 3;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::seedling, fDBH);

    fX = 54.8983830;
    fY = 66.2619967;
    fDBH = 0.94; iSp = 3;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::seedling, fDBH);

    //Cell with only seedlings
    fX = 86.1417305;
    fY = 80.7815262;
    fDBH = 0.94; iSp = 3;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::seedling, fDBH);

    fX = 80.1654434;
    fY = 85.1138069;
    fDBH = 0.94; iSp = 3;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::seedling, fDBH);

    fX = 84.8983830;
    fY = 86.2619967;
    fDBH = 0.94; iSp = 3;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::seedling, fDBH);

    //Run one timestep
    p_oSimManager->RunSim(1);

    CheckConditOmegaCalculatorRun1Results(p_oGrid);

    p_oSimManager->RunSim(1);

    CheckConditOmegaCalculatorRun1Results(p_oGrid);
    delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

////////////////////////////////////////////////////////////////////////////
// TestNormalProcessingRun2()
// Tests normal processing, run 2. WriteConditOmegaCalculatorXMLFile2() does setup. Several
// trees are created and the Condit's Omega calculated.
////////////////////////////////////////////////////////////////////////////
TEST(ConditOmegaCalculator, TestNormalProcessingRun2) {
  clTreePopulation * p_oPop;
  clGrid *p_oGrid;
  std::stringstream sLabel;
  float fExpectedValue, fActualValue, fX, fY, fDBH;
  int iSp, i, j, iCode;

  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {


    //Load our test file and get our tree population pointers
    p_oSimManager->ReadFile( WriteConditOmegaCalculatorXMLFile2() );
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );
    p_oGrid = p_oSimManager->GetGridObject("Relative Neighborhood Density");
    ASSERT_TRUE(p_oGrid != NULL);
    EXPECT_EQ(p_oGrid->GetNumberXCells(), 1);
    EXPECT_EQ(p_oGrid->GetNumberYCells(), 1);
    fExpectedValue = 2;
    p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("inc"), &fActualValue);
    EXPECT_LT(fabs(fActualValue - fExpectedValue), 0.001);
    fExpectedValue = 20;
    p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("dist"), &fActualValue);
    EXPECT_LT(fabs(fActualValue - fExpectedValue), 0.001);

    //Check the initial conditions - all zeroes
    for (i = 0; i < 10; i++) {
      for (j = 0; j < 4; j++) {
        sLabel << i << "_" << j;
        iCode = p_oGrid->GetFloatDataCode(sLabel.str());
        ASSERT_TRUE(-1 != iCode);
        p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
        EXPECT_LT(fabs(fActualValue), 0.0001);
        sLabel.str("");
      }
    }

    iSp = 0;
    fX = 31.7094184;
    fY = 69.2171281;
    fDBH = 6.70;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::sapling, fDBH);

    fX = 63.0650021;
    fY = 58.5537260;
    fDBH = 15.58;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

    fX = 34.6777252;
    fY = 42.6892403;
    fDBH = 19.13;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

    fX = 60.2542323;
    fY = 43.3365898;
    fDBH = 47.91;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

    fX = 57.7935430;
    fY = 31.8673210;
    fDBH = 41.56;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

    fX = 58.5834899;
    fY = 38.0598394;
    fDBH = 25.92;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

    fX = 61.0027385;
    fY = 69.1505016;
    fDBH = 47.12;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

    fX = 58.1158336;
    fY = 30.6776078;
    fDBH = 45.25;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

    fX = 36.6402414;
    fY = 36.9972270;
    fDBH = 23.00;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

    fX = 68.1446909;
    fY = 61.9238429;
    fDBH = 20.35;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

    fX = 62.3120718;
    fY = 52.4005773;
    fDBH = 17.07;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

    fX = 44.6887800;
    fY = 41.9360127;
    fDBH = 22.02;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

    fX = 52.5822889;
    fY = 31.2152253;
    fDBH = 7.31;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::sapling, fDBH);

    fX = 56.4709828;
    fY = 37.1044565;
    fDBH = 10.76;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

    fX = 61.7827570;
    fY = 66.6782430;
    fDBH = 2.53;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::sapling, fDBH);

    fX = 40.7574851;
    fY = 51.9639395;
    fDBH = 10.81;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

    fX = 60.7592505;
    fY = 30.0070687;
    fDBH = 22.23;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

    fX = 38.3173005;
    fY = 59.1225341;
    fDBH = 4.73;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::sapling, fDBH);

    fX = 54.3454495;
    fY = 39.1810222;
    fDBH = 35.74;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

    fX = 52.6841327;
    fY = 42.9954431;
    fDBH = 43.69;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

    fX = 44.7244036;
    fY = 31.3294605;
    fDBH = 4.96;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::sapling, fDBH);

    fX = 42.2820773;
    fY = 56.6854570;
    fDBH = 1.07;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::sapling, fDBH);

    fX = 37.3181167;
    fY = 31.1232073;
    fDBH = 24.51;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

    fX = 59.6902360;
    fY = 31.0386153;
    fDBH = 42.43;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

    fX = 65.7543677;
    fY = 68.9714840;
    fDBH = 17.64;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

    fX = 64.0057333;
    fY = 37.9274886;
    fDBH = 39.64;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

    fX = 42.8191345;
    fY = 54.1697617;
    fDBH = 10.30;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

    fX = 63.6726781;
    fY = 37.3445726;
    fDBH = 6.88;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::sapling, fDBH);

    fX = 48.0225822;
    fY = 67.0129890;
    fDBH = 24.28;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

    fX = 30.0999843;
    fY = 48.0911072;
    fDBH = 13.84;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

    fX = 67.0225125;
    fY = 46.4747131;
    fDBH = 14.23;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

    fX = 64.2440628;
    fY = 37.2466892;
    fDBH = 49.45;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

    fX = 32.5510550;
    fY = 53.7041606;
    fDBH = 35.07;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

    fX = 64.3337019;
    fY = 55.2130771;
    fDBH = 1.48;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::sapling, fDBH);

    fX = 69.9937888;
    fY = 59.4101570;
    fDBH = 11.55;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

    fX = 61.5409042;
    fY = 66.1535237;
    fDBH = 3.25;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::sapling, fDBH);

    fX = 55.7173425;
    fY = 68.4870485;
    fDBH = 34.48;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

    fX = 59.5319442;
    fY = 34.7770076;
    fDBH = 7.40;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::sapling, fDBH);

    fX = 38.7133121;
    fY = 36.8053197;
    fDBH = 44.46;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

    fX = 66.3748061;
    fY = 67.9110779;
    fDBH = 37.60;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

    fX = 68.4595765;
    fY = 34.0531134;
    fDBH = 19.03;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

    fX = 52.5231057;
    fY = 45.6320188;
    fDBH = 10.55;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

    fX = 35.5425861;
    fY = 66.8206196;
    fDBH = 42.47;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

    fX = 31.4508971;
    fY = 64.1512154;
    fDBH = 19.47;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

    fX = 33.0824643;
    fY = 35.3648909;
    fDBH = 41.03;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

    fX = 66.0341443;
    fY = 59.9338286;
    fDBH = 22.97;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

    fX = 55.0419430;
    fY = 54.2776736;
    fDBH = 26.11;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

    fX = 69.4689362;
    fY = 47.0136816;
    fDBH = 5.76;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

    fX = 66.2749605;
    fY = 30.3135251;
    fDBH = 30.60;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

    fX = 66.9336249;
    fY = 67.8912659;
    fDBH = 39.27;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

    fX = 32.0115274;
    fY = 69.6498619;
    fDBH = 28.48;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

    fX = 35.5562352;
    fY = 32.7346060;
    fDBH = 15.04;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

    fX = 30.4359842;
    fY = 50.7268044;
    fDBH = 24.25;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

    fX = 43.0721663;
    fY = 55.4585224;
    fDBH = 8.42;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

    fX = 58.0836270;
    fY = 37.4290565;
    fDBH = 38.32;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

    fX = 30.9104683;
    fY = 52.5851442;
    fDBH = 13.62;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

    fX = 66.6604773;
    fY = 46.9947606;
    fDBH = 4.09;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

    fX = 46.9727741;
    fY = 48.1382869;
    fDBH = 29.92;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

    fX = 63.2410097;
    fY = 41.5415066;
    fDBH = 32.91;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

    fX = 66.2716582;
    fY = 67.5411284;
    fDBH = 46.33;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

    fX = 50.2501481;
    fY = 58.4426534;
    fDBH = 11.15;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

    fX = 64.0742451;
    fY = 62.0013591;
    fDBH = 22.10;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

    fX = 55.1002950;
    fY = 48.0370165;
    fDBH = 33.19;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

    fX = 41.7031183;
    fY = 53.8484351;
    fDBH = 36.70;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

    fX = 39.4844218;
    fY = 30.8515324;
    fDBH = 36.48;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

    fX = 66.0148319;
    fY = 32.0354012;
    fDBH = 44.62;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

    fX = 57.9983750;
    fY = 50.8579588;
    fDBH = 11.08;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

    fX = 41.3090853;
    fY = 55.3172117;
    fDBH = 21.98;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

    fX = 68.0889239;
    fY = 67.8509960;
    fDBH = 49.27;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

    fX = 59.2650277;
    fY = 30.2195109;
    fDBH = 13.32;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

    fX = 48.0081818;
    fY = 33.5267253;
    fDBH = 3.70;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

    fX = 67.3063727;
    fY = 50.6869068;
    fDBH = 1.68;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

    fX = 62.7331277;
    fY = 36.1758086;
    fDBH = 31.45;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

    fX = 68.6612698;
    fY = 66.1263193;
    fDBH = 39.46;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

    fX = 36.3649443;
    fY = 57.7572972;
    fDBH = 21.49;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

    fX = 40.5483717;
    fY = 57.2168482;
    fDBH = 37.01;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

    fX = 54.2735002;
    fY = 60.7494505;
    fDBH = 37.65;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

    fX = 39.9040256;
    fY = 57.0768941;
    fDBH = 31.72;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

    fX = 56.3782721;
    fY = 59.2669709;
    fDBH = 11.80;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

    fX = 50.6824674;
    fY = 58.6841613;
    fDBH = 28.86;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

    fX = 40.1631905;
    fY = 53.7083696;
    fDBH = 29.45;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

    fX = 39.9462708;
    fY = 57.2334618;
    fDBH = 19.69;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

    fX = 64.3522870;
    fY = 37.1541965;
    fDBH = 16.45;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

    fX = 58.4491902;
    fY = 47.5277952;
    fDBH = 32.77;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

    fX = 66.0808891;
    fY = 48.4055297;
    fDBH = 10.57;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

    fX = 69.1167040;
    fY = 38.2317015;
    fDBH = 8.51;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::sapling, fDBH);

    fX = 65.0434486;
    fY = 39.9599933;
    fDBH = 41.08;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

    fX = 69.8230852;
    fY = 34.3845812;
    fDBH = 20.35;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

    fX = 42.7282420;
    fY = 30.2865289;
    fDBH = 41.26;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

    fX = 57.6942266;
    fY = 64.8899863;
    fDBH = 19.07;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

    fX = 31.2855571;
    fY = 49.1837897;
    fDBH = 3.94;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::sapling, fDBH);

    fX = 50.5203479;
    fY = 38.9092183;
    fDBH = 34.21;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

    fX = 56.0964522;
    fY = 55.6961520;
    fDBH = 24.56;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

    fX = 44.1205560;
    fY = 63.2525782;
    fDBH = 49.64;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

    fX = 52.1101118;
    fY = 66.2257349;
    fDBH = 4.49;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

    fX = 34.8577627;
    fY = 55.8509844;
    fDBH = 7.58;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

    fX = 51.5419791;
    fY = 42.5956021;
    fDBH = 27.52;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

    fX = 46.1417305;
    fY = 30.7815262;
    fDBH = 47.63;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

    fX = 30.1654434;
    fY = 65.1138069;
    fDBH = 11.93;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);

    fX = 54.8983830;
    fY = 66.2619967;
    fDBH = 1.96;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::adult, fDBH);


    //Create some seedlings and snags to be skipped
    fX = 57.6942266;
    fY = 64.8899863;
    fDBH = 19.07;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::snag, fDBH);

    fX = 31.2855571;
    fY = 49.1837897;
    fDBH = 0.94;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::seedling, fDBH);

    fX = 50.5203479;
    fY = 38.9092183;
    fDBH = 34.21;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::snag, fDBH);

    fX = 56.0964522;
    fY = 55.6961520;
    fDBH = 24.56;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::snag, fDBH);

    fX = 44.1205560;
    fY = 63.2525782;
    fDBH = 49.64;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::snag, fDBH);

    fX = 52.1101118;
    fY = 66.2257349;
    fDBH = 4.49;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::snag, fDBH);

    fX = 34.8577627;
    fY = 55.8509844;
    fDBH = 7.58;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::snag, fDBH);

    fX = 51.5419791;
    fY = 42.5956021;
    fDBH = 27.52;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::snag, fDBH);

    fX = 46.1417305;
    fY = 30.7815262;
    fDBH = 47.63;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::snag, fDBH);

    fX = 30.1654434;
    fY = 65.1138069;
    fDBH = 11.93;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::snag, fDBH);

    fX = 54.8983830;
    fY = 66.2619967;
    fDBH = 1.96;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::snag, fDBH);

    fX = 51.5419791;
    fY = 42.5956021;
    fDBH = 0.94; iSp = 3;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::seedling, fDBH);

    fX = 46.1417305;
    fY = 30.7815262;
    fDBH = 0.94; iSp = 3;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::seedling, fDBH);

    fX = 30.1654434;
    fY = 65.1138069;
    fDBH = 0.94;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::seedling, fDBH);

    fX = 54.8983830;
    fY = 66.2619967;
    fDBH = 0.94;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::seedling, fDBH);

    //Cell with only seedlings
    fX = 86.1417305;
    fY = 80.7815262;
    fDBH = 0.94;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::seedling, fDBH);

    fX = 80.1654434;
    fY = 85.1138069;
    fDBH = 0.94;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::seedling, fDBH);

    fX = 84.8983830;
    fY = 86.2619967;
    fDBH = 0.94;
    p_oPop->CreateTree(fX, fY, iSp, clTreePopulation::seedling, fDBH);

    //Run one timestep
    p_oSimManager->RunSim(1);

    //Species 1
    iCode = p_oGrid->GetFloatDataCode("0_0");
    fExpectedValue = 8.91267681;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("1_0");
    fExpectedValue = 5.252113122;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("2_0");
    fExpectedValue = 4.520000384;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("3_0");
    fExpectedValue = 4.706439031;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("4_0");
    fExpectedValue = 3.625195926;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("5_0");
    fExpectedValue = 3.371191067;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("6_0");
    fExpectedValue = 3.464680684;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("7_0");
    fExpectedValue = 2.960281942;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("8_0");
    fExpectedValue = 2.471582646;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

    iCode = p_oGrid->GetFloatDataCode("9_0");
    fExpectedValue = 2.42083045;
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);
    delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

////////////////////////////////////////////////////////////////////////////
// TestErrorProcessing()
////////////////////////////////////////////////////////////////////////////
TEST(ConditOmegaCalculator, TestErrorProcessing) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try
  {
    p_oSimManager->ReadFile(WriteConditOmegaCalculatorXMLErrorFile1());
    FAIL() << "TestConditOmegaCalculator error processing didn't catch error for WriteConditOmegaCalculatorXMLErrorFile1.";
  }
  catch (modelErr& err)
  {
    if (err.sFunction.compare("clConditOmegaCalculator::GetParameterFileData") != 0 &&
        err.sMoreInfo.compare("The distance increment must be less than the max distance.") != 0)
    {
      FAIL() << "TestConditOmegaCalculator error processing caught wrong error for WriteConditOmegaCalculatorXMLErrorFile1.";
    }
    ;
  }

  try
  {
    p_oSimManager->ReadFile(WriteConditOmegaCalculatorXMLErrorFile2());
    FAIL() << "TestConditOmegaCalculator error processing didn't catch error for WriteConditOmegaCalculatorXMLErrorFile2.";
  }
  catch (modelErr& err)
  {
    if (err.sFunction.compare("clConditOmegaCalculator::GetParameterFileData") != 0 &&
        err.sMoreInfo.compare("The max distance must be greater than zero.") != 0)
    {
      FAIL() << "TestConditOmegaCalculator error processing caught wrong error for WriteConditOmegaCalculatorXMLErrorFile2.";
    }
    ;
  }

  try
  {
    p_oSimManager->ReadFile(WriteConditOmegaCalculatorXMLErrorFile3());
    FAIL() << "TestConditOmegaCalculator error processing didn't catch error for WriteConditOmegaCalculatorXMLErrorFile3.";
  }
  catch (modelErr& err)
  {
    if (err.sFunction.compare("clConditOmegaCalculator::GetParameterFileData") != 0 &&
        err.sMoreInfo.compare("The distance increment must be greater than zero.") != 0)
    {
      FAIL() << "TestConditOmegaCalculator error processing caught wrong error for WriteConditOmegaCalculatorXMLErrorFile3.";
    }
    ;
  }
  delete p_oSimManager;
}

////////////////////////////////////////////////////////////////////////////
// WriteConditOmegaCalculatorXMLFile1()
////////////////////////////////////////////////////////////////////////////
const char* WriteConditOmegaCalculatorXMLFile1() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
      << "<paramFile fileCode=\"06010101\">"
      << "<plot>"
      << "<timesteps>3</timesteps>"
      << "<yearsPerTimestep>1</yearsPerTimestep>"
      << "<randomSeed>1</randomSeed>"
      << "<plot_lenX>200.0</plot_lenX>"
      << "<plot_lenY>200.0</plot_lenY>"
      << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
      << "<plot_temp_C>12.88171785</plot_temp_C>"
      << "<plot_latitude>55.37</plot_latitude>"
      << "</plot>";

  WriteConditOmegaCalculatorCommonStuff(oOut);

  oOut << "<ConditsOmega1>"
      << "<an_ConditsOmegaMaxDistance>50</an_ConditsOmegaMaxDistance>"
      << "<an_ConditsOmegaDistanceInc>1</an_ConditsOmegaDistanceInc>"
      << "</ConditsOmega1>"
      << "</paramFile>";

  oOut.close();
  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteConditOmegaCalculatorXMLFile2()
////////////////////////////////////////////////////////////////////////////
const char* WriteConditOmegaCalculatorXMLFile2() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
      << "<paramFile fileCode=\"06010101\">"
      << "<plot>"
      << "<timesteps>3</timesteps>"
      << "<yearsPerTimestep>1</yearsPerTimestep>"
      << "<randomSeed>1</randomSeed>"
      << "<plot_lenX>100.0</plot_lenX>"
      << "<plot_lenY>100.0</plot_lenY>"
      << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
      << "<plot_temp_C>12.88171785</plot_temp_C>"
      << "<plot_latitude>55.37</plot_latitude>"
      << "</plot>";

  WriteConditOmegaCalculatorCommonStuff(oOut);

  oOut << "<ConditsOmega1>"
      << "<an_ConditsOmegaMaxDistance>20</an_ConditsOmegaMaxDistance>"
      << "<an_ConditsOmegaDistanceInc>2</an_ConditsOmegaDistanceInc>"
      << "</ConditsOmega1>"
      << "</paramFile>";

  oOut.close();
  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteConditOmegaCalculatorXMLErrorFile1()
////////////////////////////////////////////////////////////////////////////
const char* WriteConditOmegaCalculatorXMLErrorFile1() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
      << "<paramFile fileCode=\"06010101\">"
      << "<plot>"
      << "<timesteps>3</timesteps>"
      << "<yearsPerTimestep>1</yearsPerTimestep>"
      << "<randomSeed>1</randomSeed>"
      << "<plot_lenX>200.0</plot_lenX>"
      << "<plot_lenY>200.0</plot_lenY>"
      << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
      << "<plot_temp_C>12.88171785</plot_temp_C>"
      << "<plot_latitude>55.37</plot_latitude>"
      << "</plot>";

  WriteConditOmegaCalculatorCommonStuff(oOut);

  oOut << "<ConditsOmega1>"
      << "<an_ConditsOmegaMaxDistance>10</an_ConditsOmegaMaxDistance>"
      << "<an_ConditsOmegaDistanceInc>20</an_ConditsOmegaDistanceInc>"
      << "</ConditsOmega1>"
      << "</paramFile>";

  oOut.close();
  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteConditOmegaCalculatorXMLErrorFile2()
////////////////////////////////////////////////////////////////////////////
const char* WriteConditOmegaCalculatorXMLErrorFile2() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
      << "<paramFile fileCode=\"06010101\">"
      << "<plot>"
      << "<timesteps>3</timesteps>"
      << "<yearsPerTimestep>1</yearsPerTimestep>"
      << "<randomSeed>1</randomSeed>"
      << "<plot_lenX>200.0</plot_lenX>"
      << "<plot_lenY>200.0</plot_lenY>"
      << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
      << "<plot_temp_C>12.88171785</plot_temp_C>"
      << "<plot_latitude>55.37</plot_latitude>"
      << "</plot>";

  WriteConditOmegaCalculatorCommonStuff(oOut);

  oOut << "<ConditsOmega1>"
      << "<an_ConditsOmegaMaxDistance>-50</an_ConditsOmegaMaxDistance>"
      << "<an_ConditsOmegaDistanceInc>1</an_ConditsOmegaDistanceInc>"
      << "</ConditsOmega1>"
      << "</paramFile>";

  oOut.close();
  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteConditOmegaCalculatorXMLErrorFile3()
////////////////////////////////////////////////////////////////////////////
const char* WriteConditOmegaCalculatorXMLErrorFile3() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
      << "<paramFile fileCode=\"06010101\">"
      << "<plot>"
      << "<timesteps>3</timesteps>"
      << "<yearsPerTimestep>1</yearsPerTimestep>"
      << "<randomSeed>1</randomSeed>"
      << "<plot_lenX>200.0</plot_lenX>"
      << "<plot_lenY>200.0</plot_lenY>"
      << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
      << "<plot_temp_C>12.88171785</plot_temp_C>"
      << "<plot_latitude>55.37</plot_latitude>"
      << "</plot>";

  WriteConditOmegaCalculatorCommonStuff(oOut);

  oOut << "<ConditsOmega1>"
      << "<an_ConditsOmegaMaxDistance>50</an_ConditsOmegaMaxDistance>"
      << "<an_ConditsOmegaDistanceInc>-1</an_ConditsOmegaDistanceInc>"
      << "</ConditsOmega1>"
      << "</paramFile>";

  oOut.close();
  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteConditOmegaCalculatorCommonStuff()
////////////////////////////////////////////////////////////////////////////
void WriteConditOmegaCalculatorCommonStuff(std::fstream &oOut) {

  oOut << "<trees>"
      << "<tr_speciesList>"
      << "<tr_species speciesName=\"Species_1\" />"
      << "<tr_species speciesName=\"Species_2\" />"
      << "<tr_species speciesName=\"Species_3\" />"
      << "<tr_species speciesName=\"Species_4\" />"
      << "</tr_speciesList>"
      << "<tr_seedDiam10Cm>0.1</tr_seedDiam10Cm>"
      << "<tr_minAdultDBH>"
      << "<tr_madVal species=\"Species_1\">0.0</tr_madVal>"
      << "<tr_madVal species=\"Species_2\">0.0</tr_madVal>"
      << "<tr_madVal species=\"Species_3\">0.0</tr_madVal>"
      << "<tr_madVal species=\"Species_4\">0.0</tr_madVal>"
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
      << "<tr_stdMaxCrownRad>"
      << "<tr_smcrVal species=\"Species_1\">10</tr_smcrVal>"
      << "<tr_smcrVal species=\"Species_2\">10</tr_smcrVal>"
      << "<tr_smcrVal species=\"Species_3\">10</tr_smcrVal>"
      << "<tr_smcrVal species=\"Species_4\">10</tr_smcrVal>"
      << "</tr_stdMaxCrownRad>"
      << "<tr_stdCrownRadExp>"
      << "<tr_screVal species=\"Species_1\">1.0</tr_screVal>"
      << "<tr_screVal species=\"Species_2\">1.0</tr_screVal>"
      << "<tr_screVal species=\"Species_3\">1.0</tr_screVal>"
      << "<tr_screVal species=\"Species_4\">1.0</tr_screVal>"
      << "</tr_stdCrownRadExp>"
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
      << "<tr_soahVal species=\"Species_2\">0.0241</tr_soahVal>"
      << "<tr_soahVal species=\"Species_3\">0.0263</tr_soahVal>"
      << "<tr_soahVal species=\"Species_4\">0.0263</tr_soahVal>"
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
      << "</allometry>"
      << "<behaviorList>"
      << "<behavior>"
      << "<behaviorName>ConditsOmega</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>1</listPosition>"
      << "</behavior>"
      << "</behaviorList>";
}

////////////////////////////////////////////////////////////////////////////
// CheckRun1Results()
////////////////////////////////////////////////////////////////////////////
void CheckConditOmegaCalculatorRun1Results(clGrid *p_oGrid) {

  std::stringstream sLabel;
  float fActualValue, fExpectedValue;
  int iCode, i;

  //Species 1
  iCode = p_oGrid->GetFloatDataCode("0_0");
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("1_0");
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("2_0");
  fExpectedValue = 203.7183272;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("3_0");
  fExpectedValue = 109.1348181;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("4_0");
  fExpectedValue = 56.58842421;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("5_0");
  fExpectedValue = 162.0486693;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("6_0");
  fExpectedValue = 58.76490206;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("7_0");
  fExpectedValue = 118.8356908;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("8_0");
  fExpectedValue = 14.97928876;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("9_0");
  fExpectedValue = 67.01260762;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("10_0");
  fExpectedValue = 36.37827271;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("11_0");
  fExpectedValue = 22.14329643;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("12_0");
  fExpectedValue = 40.74366543;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("13_0");
  fExpectedValue = 18.86280807;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("14_0");
  fExpectedValue = 8.780962377;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("15_0");
  fExpectedValue = 8.214448676;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("16_0");
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("17_0");
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("18_0");
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("19_0");
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("20_0");
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("21_0");
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("22_0");
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("23_0");
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("24_0");
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("25_0");
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("26_0");
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("27_0");
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("28_0");
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("29_0");
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("30_0");
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("31_0");
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("32_0");
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("33_0");
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("34_0");
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("35_0");
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("36_0");
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("37_0");
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("38_0");
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("39_0");
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("40_0");
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("41_0");
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("42_0");
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("43_0");
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("44_0");
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("45_0");
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("46_0");
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("47_0");
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("48_0");
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("49_0");
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);


  //Species 2
  iCode = p_oGrid->GetFloatDataCode("0_1");
  fExpectedValue = 254.6479089;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("1_1");
  fExpectedValue = 84.88263632;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("2_1");
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("3_1");
  fExpectedValue = 145.5130908;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("4_1");
  fExpectedValue = 56.58842421;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("5_1");
  fExpectedValue = 69.44942971;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("6_1");
  fExpectedValue = 156.7064055;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("7_1");
  fExpectedValue = 50.92958179;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("8_1");
  fExpectedValue = 44.93786628;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("9_1");
  fExpectedValue = 13.40252152;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("10_1");
  fExpectedValue = 60.63045451;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("11_1");
  fExpectedValue = 88.57318572;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("12_1");
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("13_1");
  fExpectedValue = 37.72561614;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("14_1");
  fExpectedValue = 17.56192475;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("15_1");
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("16_1");
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("17_1");
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("18_1");
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("19_1");
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("20_1");
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("21_1");
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("22_1");
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("23_1");
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("24_1");
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("25_1");
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("26_1");
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("27_1");
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("28_1");
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("29_1");
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("30_1");
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("31_1");
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("32_1");
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("33_1");
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("34_1");
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("35_1");
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("36_1");
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("37_1");
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("38_1");
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("39_1");
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("40_1");
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("41_1");
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("42_1");
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("43_1");
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("44_1");
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("45_1");
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("46_1");
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("47_1");
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("48_1");
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("49_1");
  fExpectedValue = 0;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  //Species 3
  iCode = p_oGrid->GetFloatDataCode("0_2");
  fExpectedValue = 67.64085081;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("1_2");
  fExpectedValue = 47.74648293;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("2_2");
  fExpectedValue = 31.83098862;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("3_2");
  fExpectedValue = 24.44165197;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("4_2");
  fExpectedValue = 22.98904734;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("5_2");
  fExpectedValue = 24.9583888;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("6_2");
  fExpectedValue = 21.11863668;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("7_2");
  fExpectedValue = 22.28169203;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("8_2");
  fExpectedValue = 15.44739154;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("9_2");
  fExpectedValue = 14.24017912;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("10_2");
  fExpectedValue = 14.39973295;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("11_2");
  fExpectedValue = 12.97458775;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("12_2");
  fExpectedValue = 12.89155039;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("13_2");
  fExpectedValue = 13.26291192;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("14_2");
  fExpectedValue = 10.29019029;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("15_2");
  fExpectedValue = 7.187642591;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("16_2");
  fExpectedValue = 7.234315595;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("17_2");
  fExpectedValue = 7.389336644;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("18_2");
  fExpectedValue = 7.312524412;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("19_2");
  fExpectedValue = 6.121343965;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("20_2");
  fExpectedValue = 5.628650426;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("21_2");
  fExpectedValue = 7.310023549;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("22_2");
  fExpectedValue = 6.808294788;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("23_2");
  fExpectedValue = 7.449805847;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("24_2");
  fExpectedValue = 6.983329136;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("25_2");
  fExpectedValue = 6.709473091;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("26_2");
  fExpectedValue = 7.282089377;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("27_2");
  fExpectedValue = 7.089629283;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("28_2");
  fExpectedValue = 7.678527956;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("29_2");
  fExpectedValue = 8.767009577;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("30_2");
  fExpectedValue = 7.435927669;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("31_2");
  fExpectedValue = 6.757769409;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("32_2");
  fExpectedValue = 5.26435581;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("33_2");
  fExpectedValue = 5.463527897;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("34_2");
  fExpectedValue = 5.189835101;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("35_2");
  fExpectedValue = 5.660087765;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("36_2");
  fExpectedValue = 4.57842987;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("37_2");
  fExpectedValue = 2.970892271;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("38_2");
  fExpectedValue = 2.73870519;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("39_2");
  fExpectedValue = 2.669370881;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("40_2");
  fExpectedValue = 1.866632049;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("41_2");
  fExpectedValue = 1.917529435;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("42_2");
  fExpectedValue = 0.702154161;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("43_2");
  fExpectedValue = 0.686012686;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("44_2");
  fExpectedValue = 0.491770892;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("45_2");
  fExpectedValue = 0.612134397;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("46_2");
  fExpectedValue = 0.213917934;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("47_2");
  fExpectedValue = 0.376945918;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("48_2");
  fExpectedValue = 0.287135207;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  iCode = p_oGrid->GetFloatDataCode("49_2");
  fExpectedValue = 0.040190642;
  p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
  EXPECT_LT(fabs(fExpectedValue - fActualValue), 0.0001);

  //Species 4
  for (i = 0; i < 50; i++) {
    sLabel << i << "_3";
    iCode = p_oGrid->GetFloatDataCode(sLabel.str());
    ASSERT_TRUE(-1 != iCode);
    p_oGrid->GetValueOfCell(0, 0, iCode, &fActualValue);
    if (fabs(fActualValue) > 0.0001)
      fActualValue = 0;
    EXPECT_LT(fabs(fActualValue), 0.0001);
    sLabel.str("");
  }
}
