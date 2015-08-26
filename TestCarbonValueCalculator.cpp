//---------------------------------------------------------------------------
// TestCarbonValueCalculator.cpp
//---------------------------------------------------------------------------
#include "TestCarbonValueCalculator.h"
#include <gtest/gtest.h>
#include <fstream>
#include <math.h>
#include "TreePopulation.h"
#include "SimManager.h"
#include "BehaviorBase.h"
#include "Grid.h"


////////////////////////////////////////////////////////////////////////////
// TestNormalProcessing()
// Tests normal processing. WriteCarbonValueCalculatorXMLFile1() does setup.
// This function creates three trees for each species, of varying sizes. The run
// goes for a timestep and then the function checks the carbon and carbon value
// for each species. Then this kills all trees and runs another timestep to
// check grid reset.
////////////////////////////////////////////////////////////////////////////
TEST(CarbonValueCalculator, TestNormalProcessing) {
  clTreePopulation * p_oPop;
  clTreeSearch *p_oAllTrees;
  clTree ***p_oTrees; //array to hold our target trees
  clTree *p_oTree; //array to hold our target trees
  clGrid *p_oValueGrid;
  char cLabel[] = "Carbon";
  float fValue, fExpectedValue, fDiam;
  int iNumTrees = 3, iNumSpecies = 19, iCount = 0, iSpecies, iCode, i;

  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {

    //Load our test file and get our tree population pointers
    p_oSimManager->ReadFile( WriteCarbonValueCalculatorXMLFile1() );
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );

    //Create the array of target trees
    p_oTrees = new clTree**[iNumSpecies];
    for (i = 0; i < iNumSpecies; i++) {
      p_oTrees[i] = new clTree*[iNumTrees];
    }

    //Create our trees
    //Create our trees - there the same for each species
    for (iSpecies = 0; iSpecies < iNumSpecies; iSpecies++) {
      iCount = 0;

      fDiam = 5;
      p_oTrees[iSpecies][iCount] = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::sapling, fDiam);
      iCount++;

      fDiam = 50;
      p_oTrees[iSpecies][iCount] = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, fDiam);
      iCount++;

      fDiam = 100;
      p_oTrees[iSpecies][iCount] = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, fDiam);
      iCount++;
    }

    //Now do the run
    p_oSimManager->RunSim(1);

    //***************
    //Species 1
    //***************
    iSpecies = 0;

    iCount = 0;
    fExpectedValue = 0;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 1;
    fExpectedValue = 0;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 2;
    fExpectedValue = 0;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    //***************
    //Species 2
    //***************
    iSpecies = 1;

    iCount = 0;
    fExpectedValue = 0.005293412;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 1;
    fExpectedValue = 1.360616499;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 2;
    fExpectedValue = 7.231327365;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    //***************
    //Species 3
    //***************
    iSpecies = 2;

    iCount = 0;
    fExpectedValue = 5.47159E-05;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 1;
    fExpectedValue = 0.023448418;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 2;
    fExpectedValue = 0.145353167;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    //***************
    //Species 4
    //***************
    iSpecies = 3;

    iCount = 0;
    fExpectedValue = 1.80765E-05;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 1;
    fExpectedValue = 2.79715E-05;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 2;
    fExpectedValue = 3.19E-05;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    //***************
    //Species 5
    //***************
    iSpecies = 4;

    iCount = 0;
    fExpectedValue = 0.002528839;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 1;
    fExpectedValue = 3.646877636;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 2;
    fExpectedValue = 32.57428921;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    //***************
    //Species 6
    //***************
    iSpecies = 5;

    iCount = 0;
    fExpectedValue = 9.37157E-05;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 1;
    fExpectedValue = 0.032569607;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 2;
    fExpectedValue = 0.189552594;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    //***************
    //Species 7
    //***************
    iSpecies = 6;

    iCount = 0;
    fExpectedValue = 0.005217663;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 1;
    fExpectedValue = 3.261940224;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 2;
    fExpectedValue = 22.65457223;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    //***************
    //Species 8
    //***************
    iSpecies = 7;

    iCount = 0;
    fExpectedValue = 6.96675E-06;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 1;
    fExpectedValue = 0.004195948;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 2;
    fExpectedValue = 0.028815971;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    //***************
    //Species 9
    //***************
    iSpecies = 8;

    iCount = 0;
    fExpectedValue = 9.30608E-07;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 1;
    fExpectedValue = 0.00104416;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 2;
    fExpectedValue = 0.008647857;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    //***************
    //Species 10
    //***************
    iSpecies = 9;

    iCount = 0;
    fExpectedValue = 0.189256409;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 1;
    fExpectedValue = 18.07384675;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 2;
    fExpectedValue = 71.30007505;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    //***************
    //Species 11
    //***************
    iSpecies = 10;

    iCount = 0;
    fExpectedValue = 0.004253635;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 1;
    fExpectedValue = 1.093352544;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 2;
    fExpectedValue = 5.810888061;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    //***************
    //Species 12
    //***************
    iSpecies = 11;

    iCount = 0;
    fExpectedValue = 9.68423E-06;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 1;
    fExpectedValue = 0.004150163;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 2;
    fExpectedValue = 0.025726224;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    //***************
    //Species 13
    //***************
    iSpecies = 12;

    iCount = 0;
    EXPECT_EQ(-1, p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()));

    iCount = 1;
    EXPECT_EQ(-1, p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()));

    iCount = 2;
    EXPECT_EQ(-1, p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()));

    //***************
    //Species 14
    //***************
    iSpecies = 13;

    iCount = 0;
    fExpectedValue = 7.76974E-05;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 1;
    fExpectedValue = 0.000120228;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 2;
    fExpectedValue = 0.000137114;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    //***************
    //Species 15
    //***************
    iSpecies = 14;

    iCount = 0;
    fExpectedValue = 0.000366498;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 1;
    fExpectedValue = 0.528532991;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 2;
    fExpectedValue = 4.72091148;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    //***************
    //Species 16
    //***************
    iSpecies = 15;

    iCount = 0;
    fExpectedValue = 3.0296E-05;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 1;
    fExpectedValue = 0.010528968;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 2;
    fExpectedValue = 0.061277778;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    //***************
    //Species 17
    //***************
    iSpecies = 16;

    iCount = 0;
    fExpectedValue = 0.00222977;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 1;
    fExpectedValue = 1.393991549;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 2;
    fExpectedValue = 9.681441123;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    //***************
    //Species 18
    //***************
    iSpecies = 17;

    iCount = 0;
    fExpectedValue = 3.44401E-06;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 1;
    fExpectedValue = 0.002074268;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 2;
    fExpectedValue = 0.014245183;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    //***************
    //Species 19
    //***************
    iSpecies = 18;

    iCount = 0;
    fExpectedValue = 5.0273E-07;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 1;
    fExpectedValue = 0.000564072;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 2;
    fExpectedValue = 0.004671711;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    //***************
    //Check the total values for each species
    //***************
    p_oValueGrid = p_oSimManager->GetGridObject("Carbon Value");
    ASSERT_TRUE(p_oValueGrid != NULL);
    EXPECT_EQ(1, p_oValueGrid->GetNumberXCells());
    EXPECT_EQ(1, p_oValueGrid->GetNumberYCells());

    //Species 1
    fExpectedValue = 0;
    iCode = p_oValueGrid->GetFloatDataCode("carbon_0");
    EXPECT_GT(iCode, -1);
    p_oValueGrid->GetValueOfCell(0, 0, iCode, &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

    //Species 2
    fExpectedValue = 8.597237277;
    iCode = p_oValueGrid->GetFloatDataCode("carbon_1");
    EXPECT_GT(iCode, -1);
    p_oValueGrid->GetValueOfCell(0, 0, iCode, &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue)/fExpectedValue, 0.001);

    //Species 3
    fExpectedValue = 0.168856301;
    iCode = p_oValueGrid->GetFloatDataCode("carbon_2");
    EXPECT_GT(iCode, -1);
    p_oValueGrid->GetValueOfCell(0, 0, iCode, &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue)/fExpectedValue, 0.001);

    //Species 4
    fExpectedValue = 7.7948E-05;
    iCode = p_oValueGrid->GetFloatDataCode("carbon_3");
    EXPECT_GT(iCode, -1);
    p_oValueGrid->GetValueOfCell(0, 0, iCode, &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue)/fExpectedValue, 0.001);

    //Species 5
    fExpectedValue = 36.22369569;
    iCode = p_oValueGrid->GetFloatDataCode("carbon_4");
    EXPECT_GT(iCode, -1);
    p_oValueGrid->GetValueOfCell(0, 0, iCode, &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue)/fExpectedValue, 0.001);

    //Species 6
    fExpectedValue = 0.222215917;
    iCode = p_oValueGrid->GetFloatDataCode("carbon_5");
    EXPECT_GT(iCode, -1);
    p_oValueGrid->GetValueOfCell(0, 0, iCode, &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue)/fExpectedValue, 0.001);

    //Species 7
    fExpectedValue = 25.92173011;
    iCode = p_oValueGrid->GetFloatDataCode("carbon_6");
    EXPECT_GT(iCode, -1);
    p_oValueGrid->GetValueOfCell(0, 0, iCode, &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue)/fExpectedValue, 0.001);

    //Species 8
    fExpectedValue = 0.033018885;
    iCode = p_oValueGrid->GetFloatDataCode("carbon_7");
    EXPECT_GT(iCode, -1);
    p_oValueGrid->GetValueOfCell(0, 0, iCode, &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue)/fExpectedValue, 0.001);

    //Species 9
    fExpectedValue = 0.009692947;
    iCode = p_oValueGrid->GetFloatDataCode("carbon_8");
    EXPECT_GT(iCode, -1);
    p_oValueGrid->GetValueOfCell(0, 0, iCode, &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue)/fExpectedValue, 0.001);

    //Species 10
    fExpectedValue = 89.56317821;
    iCode = p_oValueGrid->GetFloatDataCode("carbon_9");
    EXPECT_GT(iCode, -1);
    p_oValueGrid->GetValueOfCell(0, 0, iCode, &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue)/fExpectedValue, 0.001);

    //Species 11
    fExpectedValue = 6.908494241;
    iCode = p_oValueGrid->GetFloatDataCode("carbon_10");
    EXPECT_GT(iCode, -1);
    p_oValueGrid->GetValueOfCell(0, 0, iCode, &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue)/fExpectedValue, 0.001);

    //Species 12
    fExpectedValue = 0.029886071;
    iCode = p_oValueGrid->GetFloatDataCode("carbon_11");
    EXPECT_GT(iCode, -1);
    p_oValueGrid->GetValueOfCell(0, 0, iCode, &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue)/fExpectedValue, 0.001);

    //Species 13
    fExpectedValue = 0;
    iCode = p_oValueGrid->GetFloatDataCode("carbon_12");
    EXPECT_GT(iCode, -1);
    p_oValueGrid->GetValueOfCell(0, 0, iCode, &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

    //Species 14
    fExpectedValue = 0.00033504;
    iCode = p_oValueGrid->GetFloatDataCode("carbon_13");
    EXPECT_GT(iCode, -1);
    p_oValueGrid->GetValueOfCell(0, 0, iCode, &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue)/fExpectedValue, 0.001);

    //Species 15
    fExpectedValue = 5.249810969;
    iCode = p_oValueGrid->GetFloatDataCode("carbon_14");
    EXPECT_GT(iCode, -1);
    p_oValueGrid->GetValueOfCell(0, 0, iCode, &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue)/fExpectedValue, 0.001);

    //Species 16
    fExpectedValue = 0.071837042;
    iCode = p_oValueGrid->GetFloatDataCode("carbon_15");
    EXPECT_GT(iCode, -1);
    p_oValueGrid->GetValueOfCell(0, 0, iCode, &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue)/fExpectedValue, 0.001);

    //Species 17
    fExpectedValue = 11.07766244;
    iCode = p_oValueGrid->GetFloatDataCode("carbon_16");
    EXPECT_GT(iCode, -1);
    p_oValueGrid->GetValueOfCell(0, 0, iCode, &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue)/fExpectedValue, 0.001);

    //Species 18
    fExpectedValue = 0.016322895;
    iCode = p_oValueGrid->GetFloatDataCode("carbon_17");
    EXPECT_GT(iCode, -1);
    p_oValueGrid->GetValueOfCell(0, 0, iCode, &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue)/fExpectedValue, 0.001);

    //Species 19
    fExpectedValue = 0.005236286;
    iCode = p_oValueGrid->GetFloatDataCode("carbon_18");
    EXPECT_GT(iCode, -1);
    p_oValueGrid->GetValueOfCell(0, 0, iCode, &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue)/fExpectedValue, 0.001);



    //Species 1
    fExpectedValue = 0;
    iCode = p_oValueGrid->GetFloatDataCode("value_0");
    EXPECT_GT(iCode, -1);
    p_oValueGrid->GetValueOfCell(0, 0, iCode, &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

    //Species 2
    fExpectedValue = 94.56961005;
    iCode = p_oValueGrid->GetFloatDataCode("value_1");
    EXPECT_GT(iCode, -1);
    p_oValueGrid->GetValueOfCell(0, 0, iCode, &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue)/fExpectedValue, 0.001);

    //Species 3
    fExpectedValue = 1.857419314;
    iCode = p_oValueGrid->GetFloatDataCode("value_2");
    EXPECT_GT(iCode, -1);
    p_oValueGrid->GetValueOfCell(0, 0, iCode, &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue)/fExpectedValue, 0.001);

    //Species 4
    fExpectedValue = 0.000857428;
    iCode = p_oValueGrid->GetFloatDataCode("value_3");
    EXPECT_GT(iCode, -1);
    p_oValueGrid->GetValueOfCell(0, 0, iCode, &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue)/fExpectedValue, 0.001);

    //Species 5
    fExpectedValue = 398.4606525;
    iCode = p_oValueGrid->GetFloatDataCode("value_4");
    EXPECT_GT(iCode, -1);
    p_oValueGrid->GetValueOfCell(0, 0, iCode, &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue)/fExpectedValue, 0.001);

    //Species 6
    fExpectedValue = 2.444375086;
    iCode = p_oValueGrid->GetFloatDataCode("value_5");
    EXPECT_GT(iCode, -1);
    p_oValueGrid->GetValueOfCell(0, 0, iCode, &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue)/fExpectedValue, 0.001);

    //Species 7
    fExpectedValue = 285.1390313;
    iCode = p_oValueGrid->GetFloatDataCode("value_6");
    EXPECT_GT(iCode, -1);
    p_oValueGrid->GetValueOfCell(0, 0, iCode, &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue)/fExpectedValue, 0.001);

    //Species 8
    fExpectedValue = 0.36320774;
    iCode = p_oValueGrid->GetFloatDataCode("value_7");
    EXPECT_GT(iCode, -1);
    p_oValueGrid->GetValueOfCell(0, 0, iCode, &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue)/fExpectedValue, 0.001);

    //Species 9
    fExpectedValue = 0.106622417;
    iCode = p_oValueGrid->GetFloatDataCode("value_8");
    EXPECT_GT(iCode, -1);
    p_oValueGrid->GetValueOfCell(0, 0, iCode, &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue)/fExpectedValue, 0.001);

    //Species 10
    fExpectedValue = 985.1949603;
    iCode = p_oValueGrid->GetFloatDataCode("value_9");
    EXPECT_GT(iCode, -1);
    p_oValueGrid->GetValueOfCell(0, 0, iCode, &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue)/fExpectedValue, 0.001);

    //Species 11
    fExpectedValue = 75.99343665;
    iCode = p_oValueGrid->GetFloatDataCode("value_10");
    EXPECT_GT(iCode, -1);
    p_oValueGrid->GetValueOfCell(0, 0, iCode, &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue)/fExpectedValue, 0.001);

    //Species 12
    fExpectedValue = 0.328746781;
    iCode = p_oValueGrid->GetFloatDataCode("value_11");
    EXPECT_GT(iCode, -1);
    p_oValueGrid->GetValueOfCell(0, 0, iCode, &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue)/fExpectedValue, 0.001);

    //Species 13
    fExpectedValue = 0;
    iCode = p_oValueGrid->GetFloatDataCode("value_12");
    EXPECT_GT(iCode, -1);
    p_oValueGrid->GetValueOfCell(0, 0, iCode, &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

    //Species 14
    fExpectedValue = 0.003685437;
    iCode = p_oValueGrid->GetFloatDataCode("value_13");
    EXPECT_GT(iCode, -1);
    p_oValueGrid->GetValueOfCell(0, 0, iCode, &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue)/fExpectedValue, 0.001);

    //Species 15
    fExpectedValue = 57.74792066;
    iCode = p_oValueGrid->GetFloatDataCode("value_14");
    EXPECT_GT(iCode, -1);
    p_oValueGrid->GetValueOfCell(0, 0, iCode, &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue)/fExpectedValue, 0.001);

    //Species 16
    fExpectedValue = 0.790207463;
    iCode = p_oValueGrid->GetFloatDataCode("value_15");
    EXPECT_GT(iCode, -1);
    p_oValueGrid->GetValueOfCell(0, 0, iCode, &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue)/fExpectedValue, 0.001);

    //Species 17
    fExpectedValue = 121.8542869;
    iCode = p_oValueGrid->GetFloatDataCode("value_16");
    EXPECT_GT(iCode, -1);
    p_oValueGrid->GetValueOfCell(0, 0, iCode, &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue)/fExpectedValue, 0.001);

    //Species 18
    fExpectedValue = 0.179551849;
    iCode = p_oValueGrid->GetFloatDataCode("value_17");
    EXPECT_GT(iCode, -1);
    p_oValueGrid->GetValueOfCell(0, 0, iCode, &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue)/fExpectedValue, 0.001);

    //Species 19
    fExpectedValue = 0.057599145;
    iCode = p_oValueGrid->GetFloatDataCode("value_18");
    EXPECT_GT(iCode, -1);
    p_oValueGrid->GetValueOfCell(0, 0, iCode, &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue)/fExpectedValue, 0.001);

    //Kill all the trees
    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {
      p_oPop->KillTree(p_oTree, remove_tree);
      p_oTree = p_oAllTrees->NextTree();
    }

    //Run another timestep
    p_oSimManager->RunSim(1);

    //Make sure the grid totals are zero
    fExpectedValue = 0;

    iCode = p_oValueGrid->GetFloatDataCode("value_0");
    EXPECT_GT(iCode, -1);
    p_oValueGrid->GetValueOfCell(0, 0, iCode, &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

    iCode = p_oValueGrid->GetFloatDataCode("value_1");
    EXPECT_GT(iCode, -1);
    p_oValueGrid->GetValueOfCell(0, 0, iCode, &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

    iCode = p_oValueGrid->GetFloatDataCode("value_2");
    EXPECT_GT(iCode, -1);
    p_oValueGrid->GetValueOfCell(0, 0, iCode, &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

    iCode = p_oValueGrid->GetFloatDataCode("value_3");
    EXPECT_GT(iCode, -1);
    p_oValueGrid->GetValueOfCell(0, 0, iCode, &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

    iCode = p_oValueGrid->GetFloatDataCode("value_4");
    EXPECT_GT(iCode, -1);
    p_oValueGrid->GetValueOfCell(0, 0, iCode, &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

    iCode = p_oValueGrid->GetFloatDataCode("value_5");
    EXPECT_GT(iCode, -1);
    p_oValueGrid->GetValueOfCell(0, 0, iCode, &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

    iCode = p_oValueGrid->GetFloatDataCode("value_6");
    EXPECT_GT(iCode, -1);
    p_oValueGrid->GetValueOfCell(0, 0, iCode, &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

    iCode = p_oValueGrid->GetFloatDataCode("value_7");
    EXPECT_GT(iCode, -1);
    p_oValueGrid->GetValueOfCell(0, 0, iCode, &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

    iCode = p_oValueGrid->GetFloatDataCode("value_8");
    EXPECT_GT(iCode, -1);
    p_oValueGrid->GetValueOfCell(0, 0, iCode, &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

    iCode = p_oValueGrid->GetFloatDataCode("value_9");
    EXPECT_GT(iCode, -1);
    p_oValueGrid->GetValueOfCell(0, 0, iCode, &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

    iCode = p_oValueGrid->GetFloatDataCode("value_10");
    EXPECT_GT(iCode, -1);
    p_oValueGrid->GetValueOfCell(0, 0, iCode, &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

    iCode = p_oValueGrid->GetFloatDataCode("value_11");
    EXPECT_GT(iCode, -1);
    p_oValueGrid->GetValueOfCell(0, 0, iCode, &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

    iCode = p_oValueGrid->GetFloatDataCode("value_12");
    EXPECT_GT(iCode, -1);
    p_oValueGrid->GetValueOfCell(0, 0, iCode, &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

    iCode = p_oValueGrid->GetFloatDataCode("value_13");
    EXPECT_GT(iCode, -1);
    p_oValueGrid->GetValueOfCell(0, 0, iCode, &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

    iCode = p_oValueGrid->GetFloatDataCode("value_14");
    EXPECT_GT(iCode, -1);
    p_oValueGrid->GetValueOfCell(0, 0, iCode, &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

    iCode = p_oValueGrid->GetFloatDataCode("value_15");
    EXPECT_GT(iCode, -1);
    p_oValueGrid->GetValueOfCell(0, 0, iCode, &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

    iCode = p_oValueGrid->GetFloatDataCode("value_16");
    EXPECT_GT(iCode, -1);
    p_oValueGrid->GetValueOfCell(0, 0, iCode, &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

    iCode = p_oValueGrid->GetFloatDataCode("value_17");
    EXPECT_GT(iCode, -1);
    p_oValueGrid->GetValueOfCell(0, 0, iCode, &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

    iCode = p_oValueGrid->GetFloatDataCode("value_18");
    EXPECT_GT(iCode, -1);
    p_oValueGrid->GetValueOfCell(0, 0, iCode, &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);



    iCode = p_oValueGrid->GetFloatDataCode("carbon_0");
    EXPECT_GT(iCode, -1);
    p_oValueGrid->GetValueOfCell(0, 0, iCode, &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

    iCode = p_oValueGrid->GetFloatDataCode("carbon_1");
    EXPECT_GT(iCode, -1);
    p_oValueGrid->GetValueOfCell(0, 0, iCode, &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

    iCode = p_oValueGrid->GetFloatDataCode("carbon_2");
    EXPECT_GT(iCode, -1);
    p_oValueGrid->GetValueOfCell(0, 0, iCode, &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

    iCode = p_oValueGrid->GetFloatDataCode("carbon_3");
    EXPECT_GT(iCode, -1);
    p_oValueGrid->GetValueOfCell(0, 0, iCode, &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

    iCode = p_oValueGrid->GetFloatDataCode("carbon_4");
    EXPECT_GT(iCode, -1);
    p_oValueGrid->GetValueOfCell(0, 0, iCode, &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

    iCode = p_oValueGrid->GetFloatDataCode("carbon_5");
    EXPECT_GT(iCode, -1);
    p_oValueGrid->GetValueOfCell(0, 0, iCode, &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

    iCode = p_oValueGrid->GetFloatDataCode("carbon_6");
    EXPECT_GT(iCode, -1);
    p_oValueGrid->GetValueOfCell(0, 0, iCode, &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

    iCode = p_oValueGrid->GetFloatDataCode("carbon_7");
    EXPECT_GT(iCode, -1);
    p_oValueGrid->GetValueOfCell(0, 0, iCode, &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

    iCode = p_oValueGrid->GetFloatDataCode("carbon_8");
    EXPECT_GT(iCode, -1);
    p_oValueGrid->GetValueOfCell(0, 0, iCode, &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

    iCode = p_oValueGrid->GetFloatDataCode("carbon_9");
    EXPECT_GT(iCode, -1);
    p_oValueGrid->GetValueOfCell(0, 0, iCode, &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

    iCode = p_oValueGrid->GetFloatDataCode("carbon_10");
    EXPECT_GT(iCode, -1);
    p_oValueGrid->GetValueOfCell(0, 0, iCode, &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

    iCode = p_oValueGrid->GetFloatDataCode("carbon_11");
    EXPECT_GT(iCode, -1);
    p_oValueGrid->GetValueOfCell(0, 0, iCode, &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

    iCode = p_oValueGrid->GetFloatDataCode("carbon_12");
    EXPECT_GT(iCode, -1);
    p_oValueGrid->GetValueOfCell(0, 0, iCode, &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

    iCode = p_oValueGrid->GetFloatDataCode("carbon_13");
    EXPECT_GT(iCode, -1);
    p_oValueGrid->GetValueOfCell(0, 0, iCode, &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

    iCode = p_oValueGrid->GetFloatDataCode("carbon_14");
    EXPECT_GT(iCode, -1);
    p_oValueGrid->GetValueOfCell(0, 0, iCode, &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

    iCode = p_oValueGrid->GetFloatDataCode("carbon_15");
    EXPECT_GT(iCode, -1);
    p_oValueGrid->GetValueOfCell(0, 0, iCode, &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

    iCode = p_oValueGrid->GetFloatDataCode("carbon_16");
    EXPECT_GT(iCode, -1);
    p_oValueGrid->GetValueOfCell(0, 0, iCode, &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

    iCode = p_oValueGrid->GetFloatDataCode("carbon_17");
    EXPECT_GT(iCode, -1);
    p_oValueGrid->GetValueOfCell(0, 0, iCode, &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

    iCode = p_oValueGrid->GetFloatDataCode("carbon_18");
    EXPECT_GT(iCode, -1);
    p_oValueGrid->GetValueOfCell(0, 0, iCode, &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

    //Delete our array
    for (i = 0; i < iNumSpecies; i++) {
      delete[] p_oTrees[i];
    }
    delete[] p_oTrees;
    delete p_oSimManager;
  } catch (modelErr &e) {
    delete[] p_oTrees;
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

////////////////////////////////////////////////////////////////////////////
// TestErrorProcessing()
////////////////////////////////////////////////////////////////////////////
TEST(CarbonValueCalculator, TestErrorProcessing) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try
  {
    p_oSimManager->ReadFile(WriteCarbonValueCalculatorXMLErrorFile1());
    FAIL() << "TestCarbonValueCalculator error processing didn't catch error for WriteCarbonValueCalculatorXMLErrorFile1.";
  }
  catch (modelErr& err)
  {
    if (err.sFunction.compare("clCarbonValueCalculator::GetBiomassCodes") != 0)
    {
      FAIL() << "TestCarbonValueCalculator error processing caught wrong error for WriteCarbonValueCalculatorXMLErrorFile1.";
    }
    ;
  }

  try
  {
    p_oSimManager->ReadFile(WriteCarbonValueCalculatorXMLErrorFile2());
    FAIL() << "TestCarbonValueCalculator error processing didn't catch error for WriteCarbonValueCalculatorXMLErrorFile2.";
  }
  catch (modelErr& err)
  {
    if (err.sFunction.compare("clCarbonValueCalculator::GetParameterFileData") != 0)
    {
      FAIL() << "TestCarbonValueCalculator error processing caught wrong error for WriteCarbonValueCalculatorXMLErrorFile2.";
    }
    ;
  }

  try
  {
    p_oSimManager->ReadFile(WriteCarbonValueCalculatorXMLErrorFile3());
    FAIL() << "TestCarbonValueCalculator error processing didn't catch error for WriteCarbonValueCalculatorXMLErrorFile3.";
  }
  catch (modelErr& err)
  {
    if (err.sFunction.compare("clCarbonValueCalculator::GetParameterFileData") != 0)
    {
      FAIL() << "TestCarbonValueCalculator error processing caught wrong error for WriteCarbonValueCalculatorXMLErrorFile3.";
    }
    ;
  }
  delete p_oSimManager;
}

////////////////////////////////////////////////////////////////////////////
// WriteCarbonValueCalculatorXMLFile1()
////////////////////////////////////////////////////////////////////////////
const char* WriteCarbonValueCalculatorXMLFile1() {
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
      << "</plot>"
      << "<trees>"
      << "<tr_speciesList>"
      << "<tr_species speciesName=\"Species_1\" />"
      << "<tr_species speciesName=\"Species_2\" />"
      << "<tr_species speciesName=\"Species_3\" />"
      << "<tr_species speciesName=\"Species_4\" />"
      << "<tr_species speciesName=\"Species_5\" />"
      << "<tr_species speciesName=\"Species_6\" />"
      << "<tr_species speciesName=\"Species_7\" />"
      << "<tr_species speciesName=\"Species_8\" />"
      << "<tr_species speciesName=\"Species_9\" />"
      << "<tr_species speciesName=\"Species_10\" />"
      << "<tr_species speciesName=\"Species_11\" />"
      << "<tr_species speciesName=\"Species_12\" />"
      << "<tr_species speciesName=\"Species_13\" />"
      << "<tr_species speciesName=\"Species_14\" />"
      << "<tr_species speciesName=\"Species_15\" />"
      << "<tr_species speciesName=\"Species_16\" />"
      << "<tr_species speciesName=\"Species_17\" />"
      << "<tr_species speciesName=\"Species_18\" />"
      << "<tr_species speciesName=\"Species_19\" />"
      << "</tr_speciesList>"
      << "<tr_seedDiam10Cm>0.1</tr_seedDiam10Cm>"
      << "<tr_minAdultDBH>"
      << "<tr_madVal species=\"Species_1\">10.0</tr_madVal>"
      << "<tr_madVal species=\"Species_2\">10.0</tr_madVal>"
      << "<tr_madVal species=\"Species_3\">10.0</tr_madVal>"
      << "<tr_madVal species=\"Species_4\">10.0</tr_madVal>"
      << "<tr_madVal species=\"Species_5\">10.0</tr_madVal>"
      << "<tr_madVal species=\"Species_6\">10.0</tr_madVal>"
      << "<tr_madVal species=\"Species_7\">10.0</tr_madVal>"
      << "<tr_madVal species=\"Species_8\">10.0</tr_madVal>"
      << "<tr_madVal species=\"Species_9\">10.0</tr_madVal>"
      << "<tr_madVal species=\"Species_10\">10.0</tr_madVal>"
      << "<tr_madVal species=\"Species_11\">10.0</tr_madVal>"
      << "<tr_madVal species=\"Species_12\">10.0</tr_madVal>"
      << "<tr_madVal species=\"Species_13\">10.0</tr_madVal>"
      << "<tr_madVal species=\"Species_14\">10.0</tr_madVal>"
      << "<tr_madVal species=\"Species_15\">10.0</tr_madVal>"
      << "<tr_madVal species=\"Species_16\">10.0</tr_madVal>"
      << "<tr_madVal species=\"Species_17\">10.0</tr_madVal>"
      << "<tr_madVal species=\"Species_18\">10.0</tr_madVal>"
      << "<tr_madVal species=\"Species_19\">10.0</tr_madVal>"
      << "</tr_minAdultDBH>"
      << "<tr_maxSeedlingHeight>"
      << "<tr_mshVal species=\"Species_1\">1.35</tr_mshVal>"
      << "<tr_mshVal species=\"Species_2\">1.35</tr_mshVal>"
      << "<tr_mshVal species=\"Species_3\">1.35</tr_mshVal>"
      << "<tr_mshVal species=\"Species_4\">1.35</tr_mshVal>"
      << "<tr_mshVal species=\"Species_5\">1.35</tr_mshVal>"
      << "<tr_mshVal species=\"Species_6\">1.35</tr_mshVal>"
      << "<tr_mshVal species=\"Species_7\">1.35</tr_mshVal>"
      << "<tr_mshVal species=\"Species_8\">1.35</tr_mshVal>"
      << "<tr_mshVal species=\"Species_9\">1.35</tr_mshVal>"
      << "<tr_mshVal species=\"Species_10\">1.35</tr_mshVal>"
      << "<tr_mshVal species=\"Species_11\">1.35</tr_mshVal>"
      << "<tr_mshVal species=\"Species_12\">1.35</tr_mshVal>"
      << "<tr_mshVal species=\"Species_13\">1.35</tr_mshVal>"
      << "<tr_mshVal species=\"Species_14\">1.35</tr_mshVal>"
      << "<tr_mshVal species=\"Species_15\">1.35</tr_mshVal>"
      << "<tr_mshVal species=\"Species_16\">1.35</tr_mshVal>"
      << "<tr_mshVal species=\"Species_17\">1.35</tr_mshVal>"
      << "<tr_mshVal species=\"Species_18\">1.35</tr_mshVal>"
      << "<tr_mshVal species=\"Species_19\">1.35</tr_mshVal>"
      << "</tr_maxSeedlingHeight>"
      << "</trees>"
      << "<allometry>"
      << "<tr_canopyHeight>"
      << "<tr_chVal species=\"Species_1\">39.48</tr_chVal>"
      << "<tr_chVal species=\"Species_2\">39.48</tr_chVal>"
      << "<tr_chVal species=\"Species_3\">39.48</tr_chVal>"
      << "<tr_chVal species=\"Species_4\">39.48</tr_chVal>"
      << "<tr_chVal species=\"Species_5\">39.48</tr_chVal>"
      << "<tr_chVal species=\"Species_6\">39.48</tr_chVal>"
      << "<tr_chVal species=\"Species_7\">39.48</tr_chVal>"
      << "<tr_chVal species=\"Species_8\">39.48</tr_chVal>"
      << "<tr_chVal species=\"Species_9\">39.48</tr_chVal>"
      << "<tr_chVal species=\"Species_10\">39.48</tr_chVal>"
      << "<tr_chVal species=\"Species_11\">39.48</tr_chVal>"
      << "<tr_chVal species=\"Species_12\">39.48</tr_chVal>"
      << "<tr_chVal species=\"Species_13\">39.48</tr_chVal>"
      << "<tr_chVal species=\"Species_14\">39.48</tr_chVal>"
      << "<tr_chVal species=\"Species_15\">39.48</tr_chVal>"
      << "<tr_chVal species=\"Species_16\">39.48</tr_chVal>"
      << "<tr_chVal species=\"Species_17\">39.48</tr_chVal>"
      << "<tr_chVal species=\"Species_18\">39.48</tr_chVal>"
      << "<tr_chVal species=\"Species_19\">39.48</tr_chVal>"
      << "</tr_canopyHeight>"
      << "<tr_stdAsympCrownRad>"
      << "<tr_sacrVal species=\"Species_1\">0.0549</tr_sacrVal>"
      << "<tr_sacrVal species=\"Species_2\">0.0549</tr_sacrVal>"
      << "<tr_sacrVal species=\"Species_3\">0.0549</tr_sacrVal>"
      << "<tr_sacrVal species=\"Species_4\">0.0549</tr_sacrVal>"
      << "<tr_sacrVal species=\"Species_5\">0.0549</tr_sacrVal>"
      << "<tr_sacrVal species=\"Species_6\">0.0549</tr_sacrVal>"
      << "<tr_sacrVal species=\"Species_7\">0.0549</tr_sacrVal>"
      << "<tr_sacrVal species=\"Species_8\">0.0549</tr_sacrVal>"
      << "<tr_sacrVal species=\"Species_9\">0.0549</tr_sacrVal>"
      << "<tr_sacrVal species=\"Species_10\">0.0549</tr_sacrVal>"
      << "<tr_sacrVal species=\"Species_11\">0.0549</tr_sacrVal>"
      << "<tr_sacrVal species=\"Species_12\">0.0549</tr_sacrVal>"
      << "<tr_sacrVal species=\"Species_13\">0.0549</tr_sacrVal>"
      << "<tr_sacrVal species=\"Species_14\">0.0549</tr_sacrVal>"
      << "<tr_sacrVal species=\"Species_15\">0.0549</tr_sacrVal>"
      << "<tr_sacrVal species=\"Species_16\">0.0549</tr_sacrVal>"
      << "<tr_sacrVal species=\"Species_17\">0.0549</tr_sacrVal>"
      << "<tr_sacrVal species=\"Species_18\">0.0549</tr_sacrVal>"
      << "<tr_sacrVal species=\"Species_19\">0.0549</tr_sacrVal>"
      << "</tr_stdAsympCrownRad>"
      << "<tr_stdCrownRadExp>"
      << "<tr_screVal species=\"Species_1\">1.0</tr_screVal>"
      << "<tr_screVal species=\"Species_2\">1.0</tr_screVal>"
      << "<tr_screVal species=\"Species_3\">1.0</tr_screVal>"
      << "<tr_screVal species=\"Species_4\">1.0</tr_screVal>"
      << "<tr_screVal species=\"Species_5\">1.0</tr_screVal>"
      << "<tr_screVal species=\"Species_6\">1.0</tr_screVal>"
      << "<tr_screVal species=\"Species_7\">1.0</tr_screVal>"
      << "<tr_screVal species=\"Species_8\">1.0</tr_screVal>"
      << "<tr_screVal species=\"Species_9\">1.0</tr_screVal>"
      << "<tr_screVal species=\"Species_10\">1.0</tr_screVal>"
      << "<tr_screVal species=\"Species_11\">1.0</tr_screVal>"
      << "<tr_screVal species=\"Species_12\">1.0</tr_screVal>"
      << "<tr_screVal species=\"Species_13\">1.0</tr_screVal>"
      << "<tr_screVal species=\"Species_14\">1.0</tr_screVal>"
      << "<tr_screVal species=\"Species_15\">1.0</tr_screVal>"
      << "<tr_screVal species=\"Species_16\">1.0</tr_screVal>"
      << "<tr_screVal species=\"Species_17\">1.0</tr_screVal>"
      << "<tr_screVal species=\"Species_18\">1.0</tr_screVal>"
      << "<tr_screVal species=\"Species_19\">1.0</tr_screVal>"
      << "</tr_stdCrownRadExp>"
      << "<tr_stdMaxCrownRad>"
      << "<tr_smcrVal species=\"Species_1\">10</tr_smcrVal>"
      << "<tr_smcrVal species=\"Species_2\">10</tr_smcrVal>"
      << "<tr_smcrVal species=\"Species_3\">10</tr_smcrVal>"
      << "<tr_smcrVal species=\"Species_4\">10</tr_smcrVal>"
      << "<tr_smcrVal species=\"Species_5\">10</tr_smcrVal>"
      << "<tr_smcrVal species=\"Species_6\">10</tr_smcrVal>"
      << "<tr_smcrVal species=\"Species_7\">10</tr_smcrVal>"
      << "<tr_smcrVal species=\"Species_8\">10</tr_smcrVal>"
      << "<tr_smcrVal species=\"Species_9\">10</tr_smcrVal>"
      << "<tr_smcrVal species=\"Species_10\">10</tr_smcrVal>"
      << "<tr_smcrVal species=\"Species_11\">10</tr_smcrVal>"
      << "<tr_smcrVal species=\"Species_12\">10</tr_smcrVal>"
      << "<tr_smcrVal species=\"Species_13\">10</tr_smcrVal>"
      << "<tr_smcrVal species=\"Species_14\">10</tr_smcrVal>"
      << "<tr_smcrVal species=\"Species_15\">10</tr_smcrVal>"
      << "<tr_smcrVal species=\"Species_16\">10</tr_smcrVal>"
      << "<tr_smcrVal species=\"Species_17\">10</tr_smcrVal>"
      << "<tr_smcrVal species=\"Species_18\">10</tr_smcrVal>"
      << "<tr_smcrVal species=\"Species_19\">10</tr_smcrVal>"
      << "</tr_stdMaxCrownRad>"
      << "<tr_conversionDiam10ToDBH>"
      << "<tr_cdtdVal species=\"Species_1\">0.8008</tr_cdtdVal>"
      << "<tr_cdtdVal species=\"Species_2\">0.8008</tr_cdtdVal>"
      << "<tr_cdtdVal species=\"Species_3\">0.8008</tr_cdtdVal>"
      << "<tr_cdtdVal species=\"Species_4\">0.8008</tr_cdtdVal>"
      << "<tr_cdtdVal species=\"Species_5\">0.8008</tr_cdtdVal>"
      << "<tr_cdtdVal species=\"Species_6\">0.8008</tr_cdtdVal>"
      << "<tr_cdtdVal species=\"Species_7\">0.8008</tr_cdtdVal>"
      << "<tr_cdtdVal species=\"Species_8\">0.8008</tr_cdtdVal>"
      << "<tr_cdtdVal species=\"Species_9\">0.8008</tr_cdtdVal>"
      << "<tr_cdtdVal species=\"Species_10\">0.8008</tr_cdtdVal>"
      << "<tr_cdtdVal species=\"Species_11\">0.8008</tr_cdtdVal>"
      << "<tr_cdtdVal species=\"Species_12\">0.8008</tr_cdtdVal>"
      << "<tr_cdtdVal species=\"Species_13\">0.8008</tr_cdtdVal>"
      << "<tr_cdtdVal species=\"Species_14\">0.8008</tr_cdtdVal>"
      << "<tr_cdtdVal species=\"Species_15\">0.8008</tr_cdtdVal>"
      << "<tr_cdtdVal species=\"Species_16\">0.8008</tr_cdtdVal>"
      << "<tr_cdtdVal species=\"Species_17\">0.8008</tr_cdtdVal>"
      << "<tr_cdtdVal species=\"Species_18\">0.8008</tr_cdtdVal>"
      << "<tr_cdtdVal species=\"Species_19\">0.8008</tr_cdtdVal>"
      << "</tr_conversionDiam10ToDBH>"
      << "<tr_interceptDiam10ToDBH>"
      << "<tr_idtdVal species=\"Species_1\">0</tr_idtdVal>"
      << "<tr_idtdVal species=\"Species_2\">0</tr_idtdVal>"
      << "<tr_idtdVal species=\"Species_3\">0</tr_idtdVal>"
      << "<tr_idtdVal species=\"Species_4\">0</tr_idtdVal>"
      << "<tr_idtdVal species=\"Species_5\">0</tr_idtdVal>"
      << "<tr_idtdVal species=\"Species_6\">0</tr_idtdVal>"
      << "<tr_idtdVal species=\"Species_7\">0</tr_idtdVal>"
      << "<tr_idtdVal species=\"Species_8\">0</tr_idtdVal>"
      << "<tr_idtdVal species=\"Species_9\">0</tr_idtdVal>"
      << "<tr_idtdVal species=\"Species_10\">0</tr_idtdVal>"
      << "<tr_idtdVal species=\"Species_11\">0</tr_idtdVal>"
      << "<tr_idtdVal species=\"Species_12\">0</tr_idtdVal>"
      << "<tr_idtdVal species=\"Species_13\">0</tr_idtdVal>"
      << "<tr_idtdVal species=\"Species_14\">0</tr_idtdVal>"
      << "<tr_idtdVal species=\"Species_15\">0</tr_idtdVal>"
      << "<tr_idtdVal species=\"Species_16\">0</tr_idtdVal>"
      << "<tr_idtdVal species=\"Species_17\">0</tr_idtdVal>"
      << "<tr_idtdVal species=\"Species_18\">0</tr_idtdVal>"
      << "<tr_idtdVal species=\"Species_19\">0</tr_idtdVal>"
      << "</tr_interceptDiam10ToDBH>"
      << "<tr_stdAsympCrownHt>"
      << "<tr_sachVal species=\"Species_1\">0.389</tr_sachVal>"
      << "<tr_sachVal species=\"Species_2\">0.389</tr_sachVal>"
      << "<tr_sachVal species=\"Species_3\">0.389</tr_sachVal>"
      << "<tr_sachVal species=\"Species_4\">0.389</tr_sachVal>"
      << "<tr_sachVal species=\"Species_5\">0.389</tr_sachVal>"
      << "<tr_sachVal species=\"Species_6\">0.389</tr_sachVal>"
      << "<tr_sachVal species=\"Species_7\">0.389</tr_sachVal>"
      << "<tr_sachVal species=\"Species_8\">0.389</tr_sachVal>"
      << "<tr_sachVal species=\"Species_9\">0.389</tr_sachVal>"
      << "<tr_sachVal species=\"Species_10\">0.389</tr_sachVal>"
      << "<tr_sachVal species=\"Species_12\">0.389</tr_sachVal>"
      << "<tr_sachVal species=\"Species_13\">0.389</tr_sachVal>"
      << "<tr_sachVal species=\"Species_14\">0.389</tr_sachVal>"
      << "<tr_sachVal species=\"Species_15\">0.389</tr_sachVal>"
      << "<tr_sachVal species=\"Species_16\">0.389</tr_sachVal>"
      << "<tr_sachVal species=\"Species_17\">0.389</tr_sachVal>"
      << "<tr_sachVal species=\"Species_18\">0.389</tr_sachVal>"
      << "<tr_sachVal species=\"Species_11\">0.389</tr_sachVal>"
      << "<tr_sachVal species=\"Species_19\">0.389</tr_sachVal>"
      << "</tr_stdAsympCrownHt>"
      << "<tr_stdCrownHtExp>"
      << "<tr_scheVal species=\"Species_1\">1.0</tr_scheVal>"
      << "<tr_scheVal species=\"Species_2\">1.0</tr_scheVal>"
      << "<tr_scheVal species=\"Species_3\">1.0</tr_scheVal>"
      << "<tr_scheVal species=\"Species_4\">1.0</tr_scheVal>"
      << "<tr_scheVal species=\"Species_5\">1.0</tr_scheVal>"
      << "<tr_scheVal species=\"Species_6\">1.0</tr_scheVal>"
      << "<tr_scheVal species=\"Species_7\">1.0</tr_scheVal>"
      << "<tr_scheVal species=\"Species_8\">1.0</tr_scheVal>"
      << "<tr_scheVal species=\"Species_9\">1.0</tr_scheVal>"
      << "<tr_scheVal species=\"Species_10\">1.0</tr_scheVal>"
      << "<tr_scheVal species=\"Species_11\">1.0</tr_scheVal>"
      << "<tr_scheVal species=\"Species_12\">1.0</tr_scheVal>"
      << "<tr_scheVal species=\"Species_13\">1.0</tr_scheVal>"
      << "<tr_scheVal species=\"Species_14\">1.0</tr_scheVal>"
      << "<tr_scheVal species=\"Species_15\">1.0</tr_scheVal>"
      << "<tr_scheVal species=\"Species_16\">1.0</tr_scheVal>"
      << "<tr_scheVal species=\"Species_17\">1.0</tr_scheVal>"
      << "<tr_scheVal species=\"Species_18\">1.0</tr_scheVal>"
      << "<tr_scheVal species=\"Species_19\">1.0</tr_scheVal>"
      << "</tr_stdCrownHtExp>"
      << "<tr_slopeOfHeight-Diam10>"
      << "<tr_sohdVal species=\"Species_1\">0.03418</tr_sohdVal>"
      << "<tr_sohdVal species=\"Species_2\">0.03418</tr_sohdVal>"
      << "<tr_sohdVal species=\"Species_3\">0.03418</tr_sohdVal>"
      << "<tr_sohdVal species=\"Species_4\">0.03418</tr_sohdVal>"
      << "<tr_sohdVal species=\"Species_5\">0.03418</tr_sohdVal>"
      << "<tr_sohdVal species=\"Species_6\">0.03418</tr_sohdVal>"
      << "<tr_sohdVal species=\"Species_7\">0.03418</tr_sohdVal>"
      << "<tr_sohdVal species=\"Species_8\">0.03418</tr_sohdVal>"
      << "<tr_sohdVal species=\"Species_9\">0.03418</tr_sohdVal>"
      << "<tr_sohdVal species=\"Species_10\">0.03418</tr_sohdVal>"
      << "<tr_sohdVal species=\"Species_11\">0.03418</tr_sohdVal>"
      << "<tr_sohdVal species=\"Species_12\">0.03418</tr_sohdVal>"
      << "<tr_sohdVal species=\"Species_13\">0.03418</tr_sohdVal>"
      << "<tr_sohdVal species=\"Species_14\">0.03418</tr_sohdVal>"
      << "<tr_sohdVal species=\"Species_15\">0.03418</tr_sohdVal>"
      << "<tr_sohdVal species=\"Species_16\">0.03418</tr_sohdVal>"
      << "<tr_sohdVal species=\"Species_17\">0.03418</tr_sohdVal>"
      << "<tr_sohdVal species=\"Species_18\">0.03418</tr_sohdVal>"
      << "<tr_sohdVal species=\"Species_19\">0.03418</tr_sohdVal>"
      << "</tr_slopeOfHeight-Diam10>"
      << "<tr_slopeOfAsymHeight>"
      << "<tr_soahVal species=\"Species_1\">0.0299</tr_soahVal>"
      << "<tr_soahVal species=\"Species_2\">0.0299</tr_soahVal>"
      << "<tr_soahVal species=\"Species_3\">0.0299</tr_soahVal>"
      << "<tr_soahVal species=\"Species_4\">0.0299</tr_soahVal>"
      << "<tr_soahVal species=\"Species_5\">0.0299</tr_soahVal>"
      << "<tr_soahVal species=\"Species_6\">0.0299</tr_soahVal>"
      << "<tr_soahVal species=\"Species_7\">0.0299</tr_soahVal>"
      << "<tr_soahVal species=\"Species_8\">0.0299</tr_soahVal>"
      << "<tr_soahVal species=\"Species_9\">0.0299</tr_soahVal>"
      << "<tr_soahVal species=\"Species_10\">0.0299</tr_soahVal>"
      << "<tr_soahVal species=\"Species_11\">0.0299</tr_soahVal>"
      << "<tr_soahVal species=\"Species_12\">0.0299</tr_soahVal>"
      << "<tr_soahVal species=\"Species_13\">0.0299</tr_soahVal>"
      << "<tr_soahVal species=\"Species_14\">0.0299</tr_soahVal>"
      << "<tr_soahVal species=\"Species_15\">0.0299</tr_soahVal>"
      << "<tr_soahVal species=\"Species_16\">0.0299</tr_soahVal>"
      << "<tr_soahVal species=\"Species_17\">0.0299</tr_soahVal>"
      << "<tr_soahVal species=\"Species_18\">0.0299</tr_soahVal>"
      << "<tr_soahVal species=\"Species_19\">0.0299</tr_soahVal>"
      << "</tr_slopeOfAsymHeight>"
      << "<tr_whatSeedlingHeightDiam>"
      << "<tr_wsehdVal species=\"Species_1\">0</tr_wsehdVal>"
      << "<tr_wsehdVal species=\"Species_2\">0</tr_wsehdVal>"
      << "<tr_wsehdVal species=\"Species_3\">0</tr_wsehdVal>"
      << "<tr_wsehdVal species=\"Species_4\">0</tr_wsehdVal>"
      << "<tr_wsehdVal species=\"Species_5\">0</tr_wsehdVal>"
      << "<tr_wsehdVal species=\"Species_6\">0</tr_wsehdVal>"
      << "<tr_wsehdVal species=\"Species_7\">0</tr_wsehdVal>"
      << "<tr_wsehdVal species=\"Species_8\">0</tr_wsehdVal>"
      << "<tr_wsehdVal species=\"Species_9\">0</tr_wsehdVal>"
      << "<tr_wsehdVal species=\"Species_10\">0</tr_wsehdVal>"
      << "<tr_wsehdVal species=\"Species_11\">0</tr_wsehdVal>"
      << "<tr_wsehdVal species=\"Species_12\">0</tr_wsehdVal>"
      << "<tr_wsehdVal species=\"Species_13\">0</tr_wsehdVal>"
      << "<tr_wsehdVal species=\"Species_14\">0</tr_wsehdVal>"
      << "<tr_wsehdVal species=\"Species_15\">0</tr_wsehdVal>"
      << "<tr_wsehdVal species=\"Species_16\">0</tr_wsehdVal>"
      << "<tr_wsehdVal species=\"Species_17\">0</tr_wsehdVal>"
      << "<tr_wsehdVal species=\"Species_18\">0</tr_wsehdVal>"
      << "<tr_wsehdVal species=\"Species_19\">0</tr_wsehdVal>"
      << "</tr_whatSeedlingHeightDiam>"
      << "<tr_whatSaplingHeightDiam>"
      << "<tr_wsahdVal species=\"Species_1\">0</tr_wsahdVal>"
      << "<tr_wsahdVal species=\"Species_2\">0</tr_wsahdVal>"
      << "<tr_wsahdVal species=\"Species_3\">0</tr_wsahdVal>"
      << "<tr_wsahdVal species=\"Species_4\">0</tr_wsahdVal>"
      << "<tr_wsahdVal species=\"Species_5\">0</tr_wsahdVal>"
      << "<tr_wsahdVal species=\"Species_6\">0</tr_wsahdVal>"
      << "<tr_wsahdVal species=\"Species_7\">0</tr_wsahdVal>"
      << "<tr_wsahdVal species=\"Species_8\">0</tr_wsahdVal>"
      << "<tr_wsahdVal species=\"Species_9\">0</tr_wsahdVal>"
      << "<tr_wsahdVal species=\"Species_10\">0</tr_wsahdVal>"
      << "<tr_wsahdVal species=\"Species_11\">0</tr_wsahdVal>"
      << "<tr_wsahdVal species=\"Species_12\">0</tr_wsahdVal>"
      << "<tr_wsahdVal species=\"Species_13\">0</tr_wsahdVal>"
      << "<tr_wsahdVal species=\"Species_14\">0</tr_wsahdVal>"
      << "<tr_wsahdVal species=\"Species_15\">0</tr_wsahdVal>"
      << "<tr_wsahdVal species=\"Species_16\">0</tr_wsahdVal>"
      << "<tr_wsahdVal species=\"Species_17\">0</tr_wsahdVal>"
      << "<tr_wsahdVal species=\"Species_18\">0</tr_wsahdVal>"
      << "<tr_wsahdVal species=\"Species_19\">0</tr_wsahdVal>"
      << "</tr_whatSaplingHeightDiam>"
      << "<tr_whatAdultHeightDiam>"
      << "<tr_wahdVal species=\"Species_1\">0</tr_wahdVal>"
      << "<tr_wahdVal species=\"Species_2\">0</tr_wahdVal>"
      << "<tr_wahdVal species=\"Species_3\">0</tr_wahdVal>"
      << "<tr_wahdVal species=\"Species_4\">0</tr_wahdVal>"
      << "<tr_wahdVal species=\"Species_5\">0</tr_wahdVal>"
      << "<tr_wahdVal species=\"Species_6\">0</tr_wahdVal>"
      << "<tr_wahdVal species=\"Species_7\">0</tr_wahdVal>"
      << "<tr_wahdVal species=\"Species_8\">0</tr_wahdVal>"
      << "<tr_wahdVal species=\"Species_9\">0</tr_wahdVal>"
      << "<tr_wahdVal species=\"Species_10\">0</tr_wahdVal>"
      << "<tr_wahdVal species=\"Species_11\">0</tr_wahdVal>"
      << "<tr_wahdVal species=\"Species_12\">0</tr_wahdVal>"
      << "<tr_wahdVal species=\"Species_13\">0</tr_wahdVal>"
      << "<tr_wahdVal species=\"Species_14\">0</tr_wahdVal>"
      << "<tr_wahdVal species=\"Species_15\">0</tr_wahdVal>"
      << "<tr_wahdVal species=\"Species_16\">0</tr_wahdVal>"
      << "<tr_wahdVal species=\"Species_17\">0</tr_wahdVal>"
      << "<tr_wahdVal species=\"Species_18\">0</tr_wahdVal>"
      << "<tr_wahdVal species=\"Species_19\">0</tr_wahdVal>"
      << "</tr_whatAdultHeightDiam>"
      << "<tr_whatAdultCrownRadDiam>"
      << "<tr_wacrdVal species=\"Species_1\">0</tr_wacrdVal>"
      << "<tr_wacrdVal species=\"Species_2\">0</tr_wacrdVal>"
      << "<tr_wacrdVal species=\"Species_3\">0</tr_wacrdVal>"
      << "<tr_wacrdVal species=\"Species_4\">0</tr_wacrdVal>"
      << "<tr_wacrdVal species=\"Species_5\">0</tr_wacrdVal>"
      << "<tr_wacrdVal species=\"Species_6\">0</tr_wacrdVal>"
      << "<tr_wacrdVal species=\"Species_7\">0</tr_wacrdVal>"
      << "<tr_wacrdVal species=\"Species_8\">0</tr_wacrdVal>"
      << "<tr_wacrdVal species=\"Species_9\">0</tr_wacrdVal>"
      << "<tr_wacrdVal species=\"Species_10\">0</tr_wacrdVal>"
      << "<tr_wacrdVal species=\"Species_11\">0</tr_wacrdVal>"
      << "<tr_wacrdVal species=\"Species_12\">0</tr_wacrdVal>"
      << "<tr_wacrdVal species=\"Species_13\">0</tr_wacrdVal>"
      << "<tr_wacrdVal species=\"Species_14\">0</tr_wacrdVal>"
      << "<tr_wacrdVal species=\"Species_15\">0</tr_wacrdVal>"
      << "<tr_wacrdVal species=\"Species_16\">0</tr_wacrdVal>"
      << "<tr_wacrdVal species=\"Species_17\">0</tr_wacrdVal>"
      << "<tr_wacrdVal species=\"Species_18\">0</tr_wacrdVal>"
      << "<tr_wacrdVal species=\"Species_19\">0</tr_wacrdVal>"
      << "</tr_whatAdultCrownRadDiam>"
      << "<tr_whatAdultCrownHeightHeight>"
      << "<tr_wachhVal species=\"Species_1\">0</tr_wachhVal>"
      << "<tr_wachhVal species=\"Species_2\">0</tr_wachhVal>"
      << "<tr_wachhVal species=\"Species_3\">0</tr_wachhVal>"
      << "<tr_wachhVal species=\"Species_4\">0</tr_wachhVal>"
      << "<tr_wachhVal species=\"Species_5\">0</tr_wachhVal>"
      << "<tr_wachhVal species=\"Species_6\">0</tr_wachhVal>"
      << "<tr_wachhVal species=\"Species_7\">0</tr_wachhVal>"
      << "<tr_wachhVal species=\"Species_8\">0</tr_wachhVal>"
      << "<tr_wachhVal species=\"Species_9\">0</tr_wachhVal>"
      << "<tr_wachhVal species=\"Species_10\">0</tr_wachhVal>"
      << "<tr_wachhVal species=\"Species_11\">0</tr_wachhVal>"
      << "<tr_wachhVal species=\"Species_12\">0</tr_wachhVal>"
      << "<tr_wachhVal species=\"Species_13\">0</tr_wachhVal>"
      << "<tr_wachhVal species=\"Species_14\">0</tr_wachhVal>"
      << "<tr_wachhVal species=\"Species_15\">0</tr_wachhVal>"
      << "<tr_wachhVal species=\"Species_16\">0</tr_wachhVal>"
      << "<tr_wachhVal species=\"Species_17\">0</tr_wachhVal>"
      << "<tr_wachhVal species=\"Species_18\">0</tr_wachhVal>"
      << "<tr_wachhVal species=\"Species_19\">0</tr_wachhVal>"
      << "</tr_whatAdultCrownHeightHeight>"
      << "<tr_whatSaplingCrownRadDiam>"
      << "<tr_wscrdVal species=\"Species_1\">0</tr_wscrdVal>"
      << "<tr_wscrdVal species=\"Species_2\">0</tr_wscrdVal>"
      << "<tr_wscrdVal species=\"Species_3\">0</tr_wscrdVal>"
      << "<tr_wscrdVal species=\"Species_4\">0</tr_wscrdVal>"
      << "<tr_wscrdVal species=\"Species_5\">0</tr_wscrdVal>"
      << "<tr_wscrdVal species=\"Species_6\">0</tr_wscrdVal>"
      << "<tr_wscrdVal species=\"Species_7\">0</tr_wscrdVal>"
      << "<tr_wscrdVal species=\"Species_8\">0</tr_wscrdVal>"
      << "<tr_wscrdVal species=\"Species_9\">0</tr_wscrdVal>"
      << "<tr_wscrdVal species=\"Species_10\">0</tr_wscrdVal>"
      << "<tr_wscrdVal species=\"Species_11\">0</tr_wscrdVal>"
      << "<tr_wscrdVal species=\"Species_12\">0</tr_wscrdVal>"
      << "<tr_wscrdVal species=\"Species_13\">0</tr_wscrdVal>"
      << "<tr_wscrdVal species=\"Species_14\">0</tr_wscrdVal>"
      << "<tr_wscrdVal species=\"Species_15\">0</tr_wscrdVal>"
      << "<tr_wscrdVal species=\"Species_16\">0</tr_wscrdVal>"
      << "<tr_wscrdVal species=\"Species_17\">0</tr_wscrdVal>"
      << "<tr_wscrdVal species=\"Species_18\">0</tr_wscrdVal>"
      << "<tr_wscrdVal species=\"Species_19\">0</tr_wscrdVal>"
      << "</tr_whatSaplingCrownRadDiam>"
      << "<tr_whatSaplingCrownHeightHeight>"
      << "<tr_wschhVal species=\"Species_1\">0</tr_wschhVal>"
      << "<tr_wschhVal species=\"Species_2\">0</tr_wschhVal>"
      << "<tr_wschhVal species=\"Species_3\">0</tr_wschhVal>"
      << "<tr_wschhVal species=\"Species_4\">0</tr_wschhVal>"
      << "<tr_wschhVal species=\"Species_5\">0</tr_wschhVal>"
      << "<tr_wschhVal species=\"Species_6\">0</tr_wschhVal>"
      << "<tr_wschhVal species=\"Species_7\">0</tr_wschhVal>"
      << "<tr_wschhVal species=\"Species_8\">0</tr_wschhVal>"
      << "<tr_wschhVal species=\"Species_9\">0</tr_wschhVal>"
      << "<tr_wschhVal species=\"Species_10\">0</tr_wschhVal>"
      << "<tr_wschhVal species=\"Species_11\">0</tr_wschhVal>"
      << "<tr_wschhVal species=\"Species_12\">0</tr_wschhVal>"
      << "<tr_wschhVal species=\"Species_13\">0</tr_wschhVal>"
      << "<tr_wschhVal species=\"Species_14\">0</tr_wschhVal>"
      << "<tr_wschhVal species=\"Species_15\">0</tr_wschhVal>"
      << "<tr_wschhVal species=\"Species_16\">0</tr_wschhVal>"
      << "<tr_wschhVal species=\"Species_17\">0</tr_wschhVal>"
      << "<tr_wschhVal species=\"Species_18\">0</tr_wschhVal>"
      << "<tr_wschhVal species=\"Species_19\">0</tr_wschhVal>"
      << "</tr_whatSaplingCrownHeightHeight>"
      << "</allometry>"
      << "<behaviorList>"
      << "<behavior>"
      << "<behaviorName>DimensionAnalysis</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>1</listPosition>"
      << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_4\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_5\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_6\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_7\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_8\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_9\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_10\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_11\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_12\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_14\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_15\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_16\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_17\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_18\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_19\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_3\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_4\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_5\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_6\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_7\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_8\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_9\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_10\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_11\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_12\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_14\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_15\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_16\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_17\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_18\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_19\" type=\"Sapling\"/>"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>CarbonValueCalculator</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>2</listPosition>"
      << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_4\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_5\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_6\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_7\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_8\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_9\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_10\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_11\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_12\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_14\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_15\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_16\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_17\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_18\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_19\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_3\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_4\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_5\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_6\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_7\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_8\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_9\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_10\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_11\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_12\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_14\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_15\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_16\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_17\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_18\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_19\" type=\"Sapling\"/>"
      << "</behavior>"
      << "</behaviorList>";

  oOut << "<DimensionAnalysis1>"
      << "<bi_a>"
      << "<bi_aVal species=\"Species_1\">-0.99</bi_aVal>"
      << "<bi_aVal species=\"Species_2\">-1.01</bi_aVal>"
      << "<bi_aVal species=\"Species_3\">-1.09</bi_aVal>"
      << "<bi_aVal species=\"Species_4\">-1.08</bi_aVal>"
      << "<bi_aVal species=\"Species_5\">-1</bi_aVal>"
      << "<bi_aVal species=\"Species_6\">-1.1</bi_aVal>"
      << "<bi_aVal species=\"Species_7\">-0.8</bi_aVal>"
      << "<bi_aVal species=\"Species_8\">-0.95</bi_aVal>"
      << "<bi_aVal species=\"Species_9\">-0.85</bi_aVal>"
      << "<bi_aVal species=\"Species_10\">-0.99</bi_aVal>"
      << "<bi_aVal species=\"Species_11\">-1.01</bi_aVal>"
      << "<bi_aVal species=\"Species_12\">-1.09</bi_aVal>"
      << "<bi_aVal species=\"Species_14\">-1.08</bi_aVal>"
      << "<bi_aVal species=\"Species_15\">-1</bi_aVal>"
      << "<bi_aVal species=\"Species_16\">-1.1</bi_aVal>"
      << "<bi_aVal species=\"Species_17\">-0.8</bi_aVal>"
      << "<bi_aVal species=\"Species_18\">-0.95</bi_aVal>"
      << "<bi_aVal species=\"Species_19\">-0.85</bi_aVal>"
      << "</bi_a>"
      << "<bi_b>"
      << "<bi_bVal species=\"Species_1\">2.2</bi_bVal>"
      << "<bi_bVal species=\"Species_2\">2.41</bi_bVal>"
      << "<bi_bVal species=\"Species_3\">2.35</bi_bVal>"
      << "<bi_bVal species=\"Species_4\">2.37</bi_bVal>"
      << "<bi_bVal species=\"Species_5\">2.43</bi_bVal>"
      << "<bi_bVal species=\"Species_6\">2.31</bi_bVal>"
      << "<bi_bVal species=\"Species_7\">2.33</bi_bVal>"
      << "<bi_bVal species=\"Species_8\">2.46</bi_bVal>"
      << "<bi_bVal species=\"Species_9\">2.44</bi_bVal>"
      << "<bi_bVal species=\"Species_10\">2.2</bi_bVal>"
      << "<bi_bVal species=\"Species_11\">2.41</bi_bVal>"
      << "<bi_bVal species=\"Species_12\">2.35</bi_bVal>"
      << "<bi_bVal species=\"Species_14\">2.37</bi_bVal>"
      << "<bi_bVal species=\"Species_15\">2.43</bi_bVal>"
      << "<bi_bVal species=\"Species_16\">2.31</bi_bVal>"
      << "<bi_bVal species=\"Species_17\">2.33</bi_bVal>"
      << "<bi_bVal species=\"Species_18\">2.46</bi_bVal>"
      << "<bi_bVal species=\"Species_19\">2.44</bi_bVal>"
      << "</bi_b>"
      << "<bi_c>"
      << "<bi_cVal species=\"Species_1\">0.9</bi_cVal>"
      << "<bi_cVal species=\"Species_2\">1</bi_cVal>"
      << "<bi_cVal species=\"Species_3\">1.12</bi_cVal>"
      << "<bi_cVal species=\"Species_4\">0.08</bi_cVal>"
      << "<bi_cVal species=\"Species_5\">1.3</bi_cVal>"
      << "<bi_cVal species=\"Species_6\">1.1</bi_cVal>"
      << "<bi_cVal species=\"Species_7\">1.2</bi_cVal>"
      << "<bi_cVal species=\"Species_8\">1.13</bi_cVal>"
      << "<bi_cVal species=\"Species_9\">1.25</bi_cVal>"
      << "<bi_cVal species=\"Species_10\">0.9</bi_cVal>"
      << "<bi_cVal species=\"Species_11\">1</bi_cVal>"
      << "<bi_cVal species=\"Species_12\">1.12</bi_cVal>"
      << "<bi_cVal species=\"Species_14\">0.08</bi_cVal>"
      << "<bi_cVal species=\"Species_15\">1.3</bi_cVal>"
      << "<bi_cVal species=\"Species_16\">1.1</bi_cVal>"
      << "<bi_cVal species=\"Species_17\">1.2</bi_cVal>"
      << "<bi_cVal species=\"Species_18\">1.13</bi_cVal>"
      << "<bi_cVal species=\"Species_19\">1.25</bi_cVal>"
      << "</bi_c>"
      << "<bi_d>"
      << "<bi_dVal species=\"Species_1\">1</bi_dVal>"
      << "<bi_dVal species=\"Species_2\">1</bi_dVal>"
      << "<bi_dVal species=\"Species_3\">1</bi_dVal>"
      << "<bi_dVal species=\"Species_4\">1</bi_dVal>"
      << "<bi_dVal species=\"Species_5\">1</bi_dVal>"
      << "<bi_dVal species=\"Species_6\">1</bi_dVal>"
      << "<bi_dVal species=\"Species_7\">1</bi_dVal>"
      << "<bi_dVal species=\"Species_8\">1</bi_dVal>"
      << "<bi_dVal species=\"Species_9\">1</bi_dVal>"
      << "<bi_dVal species=\"Species_10\">1</bi_dVal>"
      << "<bi_dVal species=\"Species_11\">1</bi_dVal>"
      << "<bi_dVal species=\"Species_12\">1</bi_dVal>"
      << "<bi_dVal species=\"Species_14\">1</bi_dVal>"
      << "<bi_dVal species=\"Species_15\">1</bi_dVal>"
      << "<bi_dVal species=\"Species_16\">1</bi_dVal>"
      << "<bi_dVal species=\"Species_17\">1</bi_dVal>"
      << "<bi_dVal species=\"Species_18\">1</bi_dVal>"
      << "<bi_dVal species=\"Species_19\">1</bi_dVal>"
      << "</bi_d>"
      << "<bi_e>"
      << "<bi_eVal species=\"Species_1\">0</bi_eVal>"
      << "<bi_eVal species=\"Species_2\">0</bi_eVal>"
      << "<bi_eVal species=\"Species_3\">0</bi_eVal>"
      << "<bi_eVal species=\"Species_4\">0</bi_eVal>"
      << "<bi_eVal species=\"Species_5\">0</bi_eVal>"
      << "<bi_eVal species=\"Species_6\">0</bi_eVal>"
      << "<bi_eVal species=\"Species_7\">0</bi_eVal>"
      << "<bi_eVal species=\"Species_8\">0</bi_eVal>"
      << "<bi_eVal species=\"Species_9\">0</bi_eVal>"
      << "<bi_eVal species=\"Species_10\">0</bi_eVal>"
      << "<bi_eVal species=\"Species_11\">0</bi_eVal>"
      << "<bi_eVal species=\"Species_12\">0</bi_eVal>"
      << "<bi_eVal species=\"Species_14\">0</bi_eVal>"
      << "<bi_eVal species=\"Species_15\">0</bi_eVal>"
      << "<bi_eVal species=\"Species_16\">0</bi_eVal>"
      << "<bi_eVal species=\"Species_17\">0</bi_eVal>"
      << "<bi_eVal species=\"Species_18\">0</bi_eVal>"
      << "<bi_eVal species=\"Species_19\">0</bi_eVal>"
      << "</bi_e>"
      << "<bi_eqID>"
      << "<bi_eiVal species=\"Species_1\">1</bi_eiVal>"
      << "<bi_eiVal species=\"Species_2\">1</bi_eiVal>"
      << "<bi_eiVal species=\"Species_3\">1</bi_eiVal>"
      << "<bi_eiVal species=\"Species_4\">1</bi_eiVal>"
      << "<bi_eiVal species=\"Species_5\">1</bi_eiVal>"
      << "<bi_eiVal species=\"Species_6\">1</bi_eiVal>"
      << "<bi_eiVal species=\"Species_7\">1</bi_eiVal>"
      << "<bi_eiVal species=\"Species_8\">1</bi_eiVal>"
      << "<bi_eiVal species=\"Species_9\">1</bi_eiVal>"
      << "<bi_eiVal species=\"Species_10\">1</bi_eiVal>"
      << "<bi_eiVal species=\"Species_11\">1</bi_eiVal>"
      << "<bi_eiVal species=\"Species_12\">1</bi_eiVal>"
      << "<bi_eiVal species=\"Species_14\">1</bi_eiVal>"
      << "<bi_eiVal species=\"Species_15\">1</bi_eiVal>"
      << "<bi_eiVal species=\"Species_16\">1</bi_eiVal>"
      << "<bi_eiVal species=\"Species_17\">1</bi_eiVal>"
      << "<bi_eiVal species=\"Species_18\">1</bi_eiVal>"
      << "<bi_eiVal species=\"Species_19\">1</bi_eiVal>"
      << "</bi_eqID>"
      << "<bi_dbhUnits>"
      << "<bi_duVal species=\"Species_1\">0</bi_duVal>"
      << "<bi_duVal species=\"Species_2\">1</bi_duVal>"
      << "<bi_duVal species=\"Species_3\">2</bi_duVal>"
      << "<bi_duVal species=\"Species_4\">0</bi_duVal>"
      << "<bi_duVal species=\"Species_5\">1</bi_duVal>"
      << "<bi_duVal species=\"Species_6\">2</bi_duVal>"
      << "<bi_duVal species=\"Species_7\">0</bi_duVal>"
      << "<bi_duVal species=\"Species_8\">1</bi_duVal>"
      << "<bi_duVal species=\"Species_9\">2</bi_duVal>"
      << "<bi_duVal species=\"Species_10\">0</bi_duVal>"
      << "<bi_duVal species=\"Species_11\">1</bi_duVal>"
      << "<bi_duVal species=\"Species_12\">2</bi_duVal>"
      << "<bi_duVal species=\"Species_14\">0</bi_duVal>"
      << "<bi_duVal species=\"Species_15\">1</bi_duVal>"
      << "<bi_duVal species=\"Species_16\">2</bi_duVal>"
      << "<bi_duVal species=\"Species_17\">0</bi_duVal>"
      << "<bi_duVal species=\"Species_18\">1</bi_duVal>"
      << "<bi_duVal species=\"Species_19\">2</bi_duVal>"
      << "</bi_dbhUnits>"
      << "<bi_biomassUnits>"
      << "<bi_buVal species=\"Species_1\">1</bi_buVal>"
      << "<bi_buVal species=\"Species_2\">1</bi_buVal>"
      << "<bi_buVal species=\"Species_3\">1</bi_buVal>"
      << "<bi_buVal species=\"Species_4\">2</bi_buVal>"
      << "<bi_buVal species=\"Species_5\">2</bi_buVal>"
      << "<bi_buVal species=\"Species_6\">2</bi_buVal>"
      << "<bi_buVal species=\"Species_7\">0</bi_buVal>"
      << "<bi_buVal species=\"Species_8\">0</bi_buVal>"
      << "<bi_buVal species=\"Species_9\">0</bi_buVal>"
      << "<bi_buVal species=\"Species_10\">1</bi_buVal>"
      << "<bi_buVal species=\"Species_11\">1</bi_buVal>"
      << "<bi_buVal species=\"Species_12\">1</bi_buVal>"
      << "<bi_buVal species=\"Species_14\">2</bi_buVal>"
      << "<bi_buVal species=\"Species_15\">2</bi_buVal>"
      << "<bi_buVal species=\"Species_16\">2</bi_buVal>"
      << "<bi_buVal species=\"Species_17\">0</bi_buVal>"
      << "<bi_buVal species=\"Species_18\">0</bi_buVal>"
      << "<bi_buVal species=\"Species_19\">0</bi_buVal>"
      << "</bi_biomassUnits>"
      << "<bi_useCorrectionFactor>"
      << "<bi_ucfVal species=\"Species_1\">1</bi_ucfVal>"
      << "<bi_ucfVal species=\"Species_2\">1</bi_ucfVal>"
      << "<bi_ucfVal species=\"Species_3\">1</bi_ucfVal>"
      << "<bi_ucfVal species=\"Species_4\">1</bi_ucfVal>"
      << "<bi_ucfVal species=\"Species_5\">1</bi_ucfVal>"
      << "<bi_ucfVal species=\"Species_6\">1</bi_ucfVal>"
      << "<bi_ucfVal species=\"Species_7\">1</bi_ucfVal>"
      << "<bi_ucfVal species=\"Species_8\">1</bi_ucfVal>"
      << "<bi_ucfVal species=\"Species_9\">1</bi_ucfVal>"
      << "<bi_ucfVal species=\"Species_10\">0</bi_ucfVal>"
      << "<bi_ucfVal species=\"Species_11\">0</bi_ucfVal>"
      << "<bi_ucfVal species=\"Species_12\">0</bi_ucfVal>"
      << "<bi_ucfVal species=\"Species_14\">0</bi_ucfVal>"
      << "<bi_ucfVal species=\"Species_15\">0</bi_ucfVal>"
      << "<bi_ucfVal species=\"Species_16\">0</bi_ucfVal>"
      << "<bi_ucfVal species=\"Species_17\">0</bi_ucfVal>"
      << "<bi_ucfVal species=\"Species_18\">0</bi_ucfVal>"
      << "<bi_ucfVal species=\"Species_19\">0</bi_ucfVal>"
      << "</bi_useCorrectionFactor>"
      << "<bi_correctionFactorValue>"
      << "<bi_cfvVal species=\"Species_1\">1.11</bi_cfvVal>"
      << "<bi_cfvVal species=\"Species_2\">1.12</bi_cfvVal>"
      << "<bi_cfvVal species=\"Species_3\">1.13</bi_cfvVal>"
      << "<bi_cfvVal species=\"Species_4\">1.14</bi_cfvVal>"
      << "<bi_cfvVal species=\"Species_5\">1.15</bi_cfvVal>"
      << "<bi_cfvVal species=\"Species_6\">1.16</bi_cfvVal>"
      << "<bi_cfvVal species=\"Species_7\">1.17</bi_cfvVal>"
      << "<bi_cfvVal species=\"Species_8\">1.18</bi_cfvVal>"
      << "<bi_cfvVal species=\"Species_9\">1.19</bi_cfvVal>"
      << "<bi_cfvVal species=\"Species_10\">1</bi_cfvVal>"
      << "<bi_cfvVal species=\"Species_11\">1</bi_cfvVal>"
      << "<bi_cfvVal species=\"Species_12\">1</bi_cfvVal>"
      << "<bi_cfvVal species=\"Species_14\">1</bi_cfvVal>"
      << "<bi_cfvVal species=\"Species_15\">1</bi_cfvVal>"
      << "<bi_cfvVal species=\"Species_16\">1</bi_cfvVal>"
      << "<bi_cfvVal species=\"Species_17\">1</bi_cfvVal>"
      << "<bi_cfvVal species=\"Species_18\">1</bi_cfvVal>"
      << "<bi_cfvVal species=\"Species_19\">1</bi_cfvVal>"
      << "</bi_correctionFactorValue>"
      << "<bi_whatDia>"
      << "<bi_wdVal species=\"Species_1\">0</bi_wdVal>"
      << "<bi_wdVal species=\"Species_2\">0</bi_wdVal>"
      << "<bi_wdVal species=\"Species_3\">0</bi_wdVal>"
      << "<bi_wdVal species=\"Species_4\">0</bi_wdVal>"
      << "<bi_wdVal species=\"Species_5\">0</bi_wdVal>"
      << "<bi_wdVal species=\"Species_6\">0</bi_wdVal>"
      << "<bi_wdVal species=\"Species_7\">0</bi_wdVal>"
      << "<bi_wdVal species=\"Species_8\">0</bi_wdVal>"
      << "<bi_wdVal species=\"Species_9\">0</bi_wdVal>"
      << "<bi_wdVal species=\"Species_10\">0</bi_wdVal>"
      << "<bi_wdVal species=\"Species_11\">0</bi_wdVal>"
      << "<bi_wdVal species=\"Species_12\">0</bi_wdVal>"
      << "<bi_wdVal species=\"Species_14\">0</bi_wdVal>"
      << "<bi_wdVal species=\"Species_15\">0</bi_wdVal>"
      << "<bi_wdVal species=\"Species_16\">0</bi_wdVal>"
      << "<bi_wdVal species=\"Species_17\">0</bi_wdVal>"
      << "<bi_wdVal species=\"Species_18\">0</bi_wdVal>"
      << "<bi_wdVal species=\"Species_19\">0</bi_wdVal>"
      << "</bi_whatDia>"
      << "</DimensionAnalysis1>"
      << "<CarbonValueCalculator2>"
      << "<an_carbonPercentBiomassCarbon>"
      << "<an_cpbcVal species=\"Species_1\">0</an_cpbcVal>"
      << "<an_cpbcVal species=\"Species_2\">100</an_cpbcVal>"
      << "<an_cpbcVal species=\"Species_3\">10</an_cpbcVal>"
      << "<an_cpbcVal species=\"Species_4\">20</an_cpbcVal>"
      << "<an_cpbcVal species=\"Species_5\">30</an_cpbcVal>"
      << "<an_cpbcVal species=\"Species_6\">40</an_cpbcVal>"
      << "<an_cpbcVal species=\"Species_7\">50</an_cpbcVal>"
      << "<an_cpbcVal species=\"Species_8\">60</an_cpbcVal>"
      << "<an_cpbcVal species=\"Species_9\">70</an_cpbcVal>"
      << "<an_cpbcVal species=\"Species_10\">80</an_cpbcVal>"
      << "<an_cpbcVal species=\"Species_11\">90</an_cpbcVal>"
      << "<an_cpbcVal species=\"Species_12\">2</an_cpbcVal>"
      << "<an_cpbcVal species=\"Species_14\">98</an_cpbcVal>"
      << "<an_cpbcVal species=\"Species_15\">5</an_cpbcVal>"
      << "<an_cpbcVal species=\"Species_16\">15</an_cpbcVal>"
      << "<an_cpbcVal species=\"Species_17\">25</an_cpbcVal>"
      << "<an_cpbcVal species=\"Species_18\">35</an_cpbcVal>"
      << "<an_cpbcVal species=\"Species_19\">45</an_cpbcVal>"
      << "</an_carbonPercentBiomassCarbon>"
      << "<an_carbonPricePerMetricTonCarbon>11</an_carbonPricePerMetricTonCarbon>"
      << "</CarbonValueCalculator2>"
      << "</paramFile>";

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteCarbonValueCalculatorXMLErrorFile1()
////////////////////////////////////////////////////////////////////////////
const char* WriteCarbonValueCalculatorXMLErrorFile1() {
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
      << "<tr_conversionDiam10ToDBH>"
      << "<tr_cdtdVal species=\"Species_1\">0.8008</tr_cdtdVal>"
      << "<tr_cdtdVal species=\"Species_2\">0.8008</tr_cdtdVal>"
      << "</tr_conversionDiam10ToDBH>"
      << "<tr_stdMaxCrownRad>"
      << "<tr_smcrVal species=\"Species_1\">10</tr_smcrVal>"
      << "<tr_smcrVal species=\"Species_2\">10</tr_smcrVal>"
      << "</tr_stdMaxCrownRad>"
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
      << "<tr_wacrdVal species=\"Species_3\">0</tr_wacrdVal>"
      << "<tr_wacrdVal species=\"Species_4\">0</tr_wacrdVal>"
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
      << "<behaviorName>DimensionAnalysis</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>1</listPosition>"
      << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>CarbonValueCalculator</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>2</listPosition>"
      << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
      << "</behavior>"
      << "</behaviorList>"
      << "<DimensionAnalysis1>"
      << "<bi_a>"
      << "<bi_aVal species=\"Species_1\">-0.99</bi_aVal>"
      << "</bi_a>"
      << "<bi_b>"
      << "<bi_bVal species=\"Species_1\">2.2</bi_bVal>"
      << "</bi_b>"
      << "<bi_c>"
      << "<bi_cVal species=\"Species_1\">0.9</bi_cVal>"
      << "</bi_c>"
      << "<bi_d>"
      << "<bi_dVal species=\"Species_1\">1</bi_dVal>"
      << "</bi_d>"
      << "<bi_e>"
      << "<bi_eVal species=\"Species_1\">0</bi_eVal>"
      << "</bi_e>"
      << "<bi_eqID>"
      << "<bi_eiVal species=\"Species_1\">1</bi_eiVal>"
      << "</bi_eqID>"
      << "<bi_dbhUnits>"
      << "<bi_duVal species=\"Species_1\">0</bi_duVal>"
      << "</bi_dbhUnits>"
      << "<bi_biomassUnits>"
      << "<bi_buVal species=\"Species_1\">1</bi_buVal>"
      << "</bi_biomassUnits>"
      << "<bi_useCorrectionFactor>"
      << "<bi_ucfVal species=\"Species_1\">1</bi_ucfVal>"
      << "</bi_useCorrectionFactor>"
      << "<bi_correctionFactorValue>"
      << "<bi_cfvVal species=\"Species_1\">1.11</bi_cfvVal>"
      << "</bi_correctionFactorValue>"
      << "<bi_whatDia>"
      << "<bi_wdVal species=\"Species_1\">0</bi_wdVal>"
      << "</bi_whatDia>"
      << "</DimensionAnalysis1>";

  oOut << "<CarbonValueCalculator2>"
      << "<an_carbonPercentBiomassCarbon>"
      << "<an_cpbcVal species=\"Species_1\">0</an_cpbcVal>"
      << "<an_cpbcVal species=\"Species_2\">100</an_cpbcVal>"
      << "</an_carbonPercentBiomassCarbon>"
      << "<an_carbonPricePerMetricTonCarbon>10</an_carbonPricePerMetricTonCarbon>"
      << "</CarbonValueCalculator2>"
      << "</paramFile>";

  return cFileString;

}

////////////////////////////////////////////////////////////////////////////
// WriteCarbonValueCalculatorXMLErrorFile2()
////////////////////////////////////////////////////////////////////////////
const char* WriteCarbonValueCalculatorXMLErrorFile2() {
  using namespace std;

  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  WriteCarbonValueCalculatorCommonErrorStuff(oOut);

  oOut << "<CarbonValueCalculator2>"
      << "<an_carbonPercentBiomassCarbon>"
      << "<an_cpbcVal species=\"Species_1\">0</an_cpbcVal>"
      << "<an_cpbcVal species=\"Species_2\">-100</an_cpbcVal>"
      << "</an_carbonPercentBiomassCarbon>"
      << "<an_carbonPricePerMetricTonCarbon>10</an_carbonPricePerMetricTonCarbon>"
      << "</CarbonValueCalculator2>"
      << "</paramFile>";

  return cFileString;

}

////////////////////////////////////////////////////////////////////////////
// WriteCarbonValueCalculatorXMLErrorFile3()
////////////////////////////////////////////////////////////////////////////
const char* WriteCarbonValueCalculatorXMLErrorFile3() {
  using namespace std;

  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  WriteCarbonValueCalculatorCommonErrorStuff(oOut);

  oOut << "<CarbonValueCalculator2>"
      << "<an_carbonPercentBiomassCarbon>"
      << "<an_cpbcVal species=\"Species_1\">0</an_cpbcVal>"
      << "<an_cpbcVal species=\"Species_2\">102</an_cpbcVal>"
      << "</an_carbonPercentBiomassCarbon>"
      << "<an_carbonPricePerMetricTonCarbon>10</an_carbonPricePerMetricTonCarbon>"
      << "</CarbonValueCalculator2>"
      << "</paramFile>";

  return cFileString;

}

/////////////////////////////////////////////////////////////////////////////
// WriteCarbonValueCalculatorCommonErrorStuff()
/////////////////////////////////////////////////////////////////////////////
void WriteCarbonValueCalculatorCommonErrorStuff( std::fstream &oOut ) {
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
      << "<tr_wacrdVal species=\"Species_3\">0</tr_wacrdVal>"
      << "<tr_wacrdVal species=\"Species_4\">0</tr_wacrdVal>"
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
      << "<behaviorName>DimensionAnalysis</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>1</listPosition>"
      << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>CarbonValueCalculator</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>2</listPosition>"
      << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
      << "</behavior>"
      << "</behaviorList>"
      << "<DimensionAnalysis1>"
      << "<bi_a>"
      << "<bi_aVal species=\"Species_1\">-0.99</bi_aVal>"
      << "<bi_aVal species=\"Species_2\">-1.01</bi_aVal>"
      << "</bi_a>"
      << "<bi_b>"
      << "<bi_bVal species=\"Species_1\">2.2</bi_bVal>"
      << "<bi_bVal species=\"Species_2\">2.41</bi_bVal>"
      << "</bi_b>"
      << "<bi_c>"
      << "<bi_cVal species=\"Species_1\">0.9</bi_cVal>"
      << "<bi_cVal species=\"Species_2\">1</bi_cVal>"
      << "</bi_c>"
      << "<bi_d>"
      << "<bi_dVal species=\"Species_1\">1</bi_dVal>"
      << "<bi_dVal species=\"Species_2\">1</bi_dVal>"
      << "</bi_d>"
      << "<bi_e>"
      << "<bi_eVal species=\"Species_1\">0</bi_eVal>"
      << "<bi_eVal species=\"Species_2\">0</bi_eVal>"
      << "</bi_e>"
      << "<bi_eqID>"
      << "<bi_eiVal species=\"Species_1\">1</bi_eiVal>"
      << "<bi_eiVal species=\"Species_2\">1</bi_eiVal>"
      << "</bi_eqID>"
      << "<bi_dbhUnits>"
      << "<bi_duVal species=\"Species_1\">0</bi_duVal>"
      << "<bi_duVal species=\"Species_2\">1</bi_duVal>"
      << "</bi_dbhUnits>"
      << "<bi_biomassUnits>"
      << "<bi_buVal species=\"Species_1\">1</bi_buVal>"
      << "<bi_buVal species=\"Species_2\">1</bi_buVal>"
      << "</bi_biomassUnits>"
      << "<bi_useCorrectionFactor>"
      << "<bi_ucfVal species=\"Species_1\">1</bi_ucfVal>"
      << "<bi_ucfVal species=\"Species_2\">1</bi_ucfVal>"
      << "</bi_useCorrectionFactor>"
      << "<bi_correctionFactorValue>"
      << "<bi_cfvVal species=\"Species_1\">1.11</bi_cfvVal>"
      << "<bi_cfvVal species=\"Species_2\">1.12</bi_cfvVal>"
      << "</bi_correctionFactorValue>"
      << "<bi_whatDia>"
      << "<bi_wdVal species=\"Species_1\">0</bi_wdVal>"
      << "<bi_wdVal species=\"Species_2\">0</bi_wdVal>"
      << "</bi_whatDia>"
      << "</DimensionAnalysis1>";
}

