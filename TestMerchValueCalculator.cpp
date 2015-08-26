//---------------------------------------------------------------------------
// TestMerchValueCalculator.cpp
//---------------------------------------------------------------------------
#include "TestMerchValueCalculator.h"
#include <gtest/gtest.h>
#include <fstream>
#include <math.h>
#include "TreePopulation.h"
#include "SimManager.h"
#include "BehaviorBase.h"
#include "Grid.h"

////////////////////////////////////////////////////////////////////////////
// TestErrorProcessing()
////////////////////////////////////////////////////////////////////////////
TEST(MerchValueCalculator, TestErrorProcessing) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try
  {
    p_oSimManager->ReadFile(WriteMerchValueCalculatorXMLErrorFile1());
    FAIL() << "TestMerchValueCalculator error processing didn't catch error for WriteMerchValueCalculatorXMLErrorFile1.";
  }
  catch (modelErr& err)
  {
    if (err.sFunction.compare("clMerchValueCalculator::GetParameterFileData") != 0)
    {
      FAIL() << "TestMerchValueCalculator error processing caught wrong error for WriteMerchValueCalculatorXMLErrorFile1.";
    }
    ;
  }

  try
  {
    p_oSimManager->ReadFile(WriteMerchValueCalculatorXMLErrorFile2());
    FAIL() << "TestMerchValueCalculator error processing didn't catch error for WriteMerchValueCalculatorXMLErrorFile2.";
  }
  catch (modelErr& err)
  {
    if (err.sFunction.compare("clMerchValueCalculator::RegisterTreeDataMembers") != 0)
    {
      FAIL() << "TestMerchValueCalculator error processing caught wrong error for WriteMerchValueCalculatorXMLErrorFile2.";
    }
    ;
  }
  delete p_oSimManager;
}

////////////////////////////////////////////////////////////////////////////
// TestNormalProcessing()
// Tests normal processing. WriteMerchValueCalculatorXMLFile1() does setup. Then 33 trees of
// each of 6 species are created. A simulation is run for one timestep then
// the value checked for all those trees, as well as the species totals. Then
// all trees are killed, a second timestep is run, and the species total
// values are checked to make sure they equal 0.
////////////////////////////////////////////////////////////////////////////
TEST(MerchValueCalculator, TestNormalProcessing) {

  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  clTree ***p_oTrees; //array to hold our target trees
  int iNumTrees = 33, iNumSpecies = 7, iCount = 0, iSpecies, i;
  try {
    clTreePopulation * p_oPop;
    clTreeSearch *p_oAllTrees;
    clGrid *p_oValueGrid;
    clTree *p_oTree;
    char cLabel[] = "Merch Val";
    float fValue, fExpectedValue, fDiam;

    //Load our test file and get our tree population pointers
    p_oSimManager->ReadFile( WriteMerchValueCalculatorXMLFile1() );
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );

    //Create the array of target trees
    p_oTrees = new clTree**[iNumSpecies];
    for (i = 0; i < iNumSpecies; i++) {
      p_oTrees[i] = new clTree*[iNumTrees];
    }

    //Create our trees - there the same for each species
    for (iSpecies = 0; iSpecies < iNumSpecies; iSpecies++) {
      iCount = 0;

      fDiam = 13;
      p_oTrees[iSpecies][iCount] = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, fDiam);
      iCount++;

      fDiam = 26;
      p_oTrees[iSpecies][iCount] = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, fDiam);
      iCount++;

      fDiam = 30;
      p_oTrees[iSpecies][iCount] = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, fDiam);
      iCount++;

      fDiam = 32;
      p_oTrees[iSpecies][iCount] = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, fDiam);
      iCount++;

      fDiam = 35;
      p_oTrees[iSpecies][iCount] = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, fDiam);
      iCount++;

      fDiam = 37;
      p_oTrees[iSpecies][iCount] = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, fDiam);
      iCount++;

      fDiam = 39;
      p_oTrees[iSpecies][iCount] = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, fDiam);
      iCount++;

      fDiam = 41;
      p_oTrees[iSpecies][iCount] = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, fDiam);
      iCount++;

      fDiam = 44;
      p_oTrees[iSpecies][iCount] = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, fDiam);
      iCount++;

      fDiam = 46;
      p_oTrees[iSpecies][iCount] = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, fDiam);
      iCount++;

      fDiam = 49;
      p_oTrees[iSpecies][iCount] = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, fDiam);
      iCount++;

      fDiam = 51;
      p_oTrees[iSpecies][iCount] = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, fDiam);
      iCount++;

      fDiam = 54;
      p_oTrees[iSpecies][iCount] = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, fDiam);
      iCount++;

      fDiam = 56;
      p_oTrees[iSpecies][iCount] = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, fDiam);
      iCount++;

      fDiam = 59;
      p_oTrees[iSpecies][iCount] = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, fDiam);
      iCount++;

      fDiam = 61;
      p_oTrees[iSpecies][iCount] = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, fDiam);
      iCount++;

      fDiam = 64;
      p_oTrees[iSpecies][iCount] = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, fDiam);
      iCount++;

      fDiam = 66;
      p_oTrees[iSpecies][iCount] = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, fDiam);
      iCount++;

      fDiam = 69;
      p_oTrees[iSpecies][iCount] = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, fDiam);
      iCount++;

      fDiam = 72;
      p_oTrees[iSpecies][iCount] = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, fDiam);
      iCount++;

      fDiam = 74;
      p_oTrees[iSpecies][iCount] = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, fDiam);
      iCount++;

      fDiam = 77;
      p_oTrees[iSpecies][iCount] = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, fDiam);
      iCount++;

      fDiam = 79;
      p_oTrees[iSpecies][iCount] = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, fDiam);
      iCount++;

      fDiam = 82;
      p_oTrees[iSpecies][iCount] = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, fDiam);
      iCount++;

      fDiam = 84;
      p_oTrees[iSpecies][iCount] = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, fDiam);
      iCount++;

      fDiam = 87;
      p_oTrees[iSpecies][iCount] = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, fDiam);
      iCount++;

      fDiam = 89;
      p_oTrees[iSpecies][iCount] = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, fDiam);
      iCount++;

      fDiam = 92;
      p_oTrees[iSpecies][iCount] = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, fDiam);
      iCount++;

      fDiam = 94;
      p_oTrees[iSpecies][iCount] = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, fDiam);
      iCount++;

      fDiam = 97;
      p_oTrees[iSpecies][iCount] = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, fDiam);
      iCount++;

      fDiam = 99;
      p_oTrees[iSpecies][iCount] = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, fDiam);
      iCount++;

      fDiam = 102;
      p_oTrees[iSpecies][iCount] = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, fDiam);
      iCount++;

      fDiam = 110;
      p_oTrees[iSpecies][iCount] = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, fDiam);
      iCount++;
    }

    //Now do the run
    p_oSimManager->RunSim(1);

    //Check the value for each tree for each species
    //***************
    //Species 0 - no value
    //***************
    for (iCount = 0; iCount < iNumTrees; iCount++) {
      EXPECT_EQ(-1, p_oPop->GetFloatDataCode(cLabel, p_oTrees[0][iCount]->GetSpecies(), p_oTrees[0][iCount]->GetType()));
    }

    //***************
    //Species 1
    //***************
    iSpecies = 1;

    iCount = 0;
    fExpectedValue = 0;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 1;
    fExpectedValue = 0.07257;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 2;
    fExpectedValue = 0.09348;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 3;
    fExpectedValue = 0.11316;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 4;
    fExpectedValue = 0.13776;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 5;
    fExpectedValue = 0.16236;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 6;
    fExpectedValue = 0.19188;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 7;
    fExpectedValue = 0.2214;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 8;
    fExpectedValue = 0.25338;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 9;
    fExpectedValue = 0.28659;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 10;
    fExpectedValue = 0.44034;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 11;
    fExpectedValue = 0.49323;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 12;
    fExpectedValue = 0.5535;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 13;
    fExpectedValue = 0.615;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 14;
    fExpectedValue = 0.67896;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 15;
    fExpectedValue = 0.74415;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 16;
    fExpectedValue = 0.81795;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 17;
    fExpectedValue = 0.89175;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 18;
    fExpectedValue = 0.96924;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 19;
    fExpectedValue = 1.0455;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 20;
    fExpectedValue = 1.1316;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 21;
    fExpectedValue = 1.21893;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 22;
    fExpectedValue = 1.3161;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 23;
    fExpectedValue = 1.41327;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 24;
    fExpectedValue = 1.50798;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 25;
    fExpectedValue = 1.60392;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 26;
    fExpectedValue = 1.71462;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 27;
    fExpectedValue = 1.82655;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 28;
    fExpectedValue = 1.94094;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 29;
    fExpectedValue = 2.0541;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 30;
    fExpectedValue = 2.17587;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 31;
    fExpectedValue = 2.29764;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 32;
    fExpectedValue = 2.29764;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    //***************
    //Species 2
    //***************
    iSpecies = 2;

    iCount = 0;
    fExpectedValue = 0;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 1;
    fExpectedValue = 0.05429;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 2;
    fExpectedValue = 0.06942;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 3;
    fExpectedValue = 0.08544;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 4;
    fExpectedValue = 0.10413;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 5;
    fExpectedValue = 0.12282;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 6;
    fExpectedValue = 0.1424;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 7;
    fExpectedValue = 0.16287;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 8;
    fExpectedValue = 0.25454;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 9;
    fExpectedValue = 0.28925;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 10;
    fExpectedValue = 0.3293;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 11;
    fExpectedValue = 0.36846;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 12;
    fExpectedValue = 0.41296;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 13;
    fExpectedValue = 0.45746;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 14;
    fExpectedValue = 0.50819;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 15;
    fExpectedValue = 0.55892;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 16;
    fExpectedValue = 0.60965;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 17;
    fExpectedValue = 0.66038;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 18;
    fExpectedValue = 0.7209;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 19;
    fExpectedValue = 0.78053;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 20;
    fExpectedValue = 0.84372;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 21;
    fExpectedValue = 0.9078;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 22;
    fExpectedValue = 0.979;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 23;
    fExpectedValue = 1.05109;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 24;
    fExpectedValue = 1.12585;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 25;
    fExpectedValue = 1.20061;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 26;
    fExpectedValue = 1.27715;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 27;
    fExpectedValue = 1.35369;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 28;
    fExpectedValue = 1.4418;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 29;
    fExpectedValue = 1.5308;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 30;
    fExpectedValue = 1.62158;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 31;
    fExpectedValue = 1.71147;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 32;
    fExpectedValue = 2.10218;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    //***************
    //Species 3
    //***************
    iSpecies = 3;

    iCount = 0;
    fExpectedValue = 0;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 1;
    fExpectedValue = 0.61488;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 2;
    fExpectedValue = 0.7808;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 3;
    fExpectedValue = 0.95648;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 4;
    fExpectedValue = 1.1712;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 5;
    fExpectedValue = 1.37616;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 6;
    fExpectedValue = 2.15696;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 7;
    fExpectedValue = 2.49856;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 8;
    fExpectedValue = 2.88896;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 9;
    fExpectedValue = 3.27936;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 10;
    fExpectedValue = 3.72832;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 11;
    fExpectedValue = 4.16752;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 12;
    fExpectedValue = 4.66528;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 13;
    fExpectedValue = 5.15328;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 14;
    fExpectedValue = 5.71936;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 15;
    fExpectedValue = 6.28544;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 16;
    fExpectedValue = 6.89056;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 17;
    fExpectedValue = 7.48592;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 18;
    fExpectedValue = 8.15936;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 19;
    fExpectedValue = 8.82304;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 20;
    fExpectedValue = 9.53552;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 21;
    fExpectedValue = 10.248;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 22;
    fExpectedValue = 11.04832;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 23;
    fExpectedValue = 11.83888;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 24;
    fExpectedValue = 12.66848;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 25;
    fExpectedValue = 13.49808;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 26;
    fExpectedValue = 14.41552;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 27;
    fExpectedValue = 15.33296;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 28;
    fExpectedValue = 16.31872;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 29;
    fExpectedValue = 17.29472;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 30;
    fExpectedValue = 18.29024;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 31;
    fExpectedValue = 23.73632;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 32;
    fExpectedValue = 23.73632;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    //***************
    //Species 4
    //***************
    iSpecies = 4;

    iCount = 0;
    fExpectedValue = 0;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 1;
    fExpectedValue = 0.01495;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 2;
    fExpectedValue = 0.01886;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 3;
    fExpectedValue = 0.023;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 4;
    fExpectedValue = 0.0368;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 5;
    fExpectedValue = 0.0437;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 6;
    fExpectedValue = 0.05244;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 7;
    fExpectedValue = 0.06095;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 8;
    fExpectedValue = 0.07038;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 9;
    fExpectedValue = 0.07958;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 10;
    fExpectedValue = 0.09016;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 11;
    fExpectedValue = 0.10097;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 12;
    fExpectedValue = 0.11316;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 13;
    fExpectedValue = 0.12512;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 14;
    fExpectedValue = 0.13846;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 15;
    fExpectedValue = 0.15157;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 16;
    fExpectedValue = 0.16698;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 17;
    fExpectedValue = 0.18239;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 18;
    fExpectedValue = 0.19849;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 19;
    fExpectedValue = 0.21459;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 20;
    fExpectedValue = 0.23138;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 21;
    fExpectedValue = 0.2484;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 22;
    fExpectedValue = 0.26726;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 23;
    fExpectedValue = 0.28635;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 24;
    fExpectedValue = 0.30636;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 25;
    fExpectedValue = 0.32637;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 26;
    fExpectedValue = 0.34914;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 27;
    fExpectedValue = 0.37214;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 28;
    fExpectedValue = 0.39583;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 29;
    fExpectedValue = 0.51382;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 30;
    fExpectedValue = 0.54464;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 31;
    fExpectedValue = 0.57546;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 32;
    fExpectedValue = 0.57546;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    //***************
    //Species 5
    //***************
    iSpecies = 5;

    iCount = 0;
    fExpectedValue = 0;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 1;
    fExpectedValue = 0.32021;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 2;
    fExpectedValue = 0.53218;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 3;
    fExpectedValue = 0.65395;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 4;
    fExpectedValue = 0.80278;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 5;
    fExpectedValue = 0.95612;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 6;
    fExpectedValue = 1.12299;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 7;
    fExpectedValue = 1.28986;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 8;
    fExpectedValue = 1.49732;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 9;
    fExpectedValue = 1.70027;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 10;
    fExpectedValue = 1.93028;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 11;
    fExpectedValue = 2.16029;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 12;
    fExpectedValue = 2.42187;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 13;
    fExpectedValue = 2.68345;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 14;
    fExpectedValue = 2.9766;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 15;
    fExpectedValue = 3.26524;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 16;
    fExpectedValue = 3.5629;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 17;
    fExpectedValue = 3.85605;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 18;
    fExpectedValue = 5.12336;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 19;
    fExpectedValue = 5.5473;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 20;
    fExpectedValue = 5.9983;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 21;
    fExpectedValue = 6.44479;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 22;
    fExpectedValue = 6.97246;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 23;
    fExpectedValue = 7.50464;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 24;
    fExpectedValue = 8.03682;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 25;
    fExpectedValue = 8.57351;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 26;
    fExpectedValue = 9.12373;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 27;
    fExpectedValue = 9.67395;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 28;
    fExpectedValue = 10.30084;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 29;
    fExpectedValue = 10.92322;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 30;
    fExpectedValue = 11.5907;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 31;
    fExpectedValue = 12.26269;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 32;
    fExpectedValue = 12.26269;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    //***************
    //Species 6
    //***************
    iSpecies = 6;

    iCount = 0;
    fExpectedValue = 0;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 1;
    fExpectedValue = 0.08732;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 2;
    fExpectedValue = 0.14396;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 3;
    fExpectedValue = 0.177;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 4;
    fExpectedValue = 0.21712;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 5;
    fExpectedValue = 0.25606;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 6;
    fExpectedValue = 0.30326;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 7;
    fExpectedValue = 0.35046;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 8;
    fExpectedValue = 0.40356;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 9;
    fExpectedValue = 0.45784;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 10;
    fExpectedValue = 0.5192;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 11;
    fExpectedValue = 0.58056;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 12;
    fExpectedValue = 0.649;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 13;
    fExpectedValue = 0.71862;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 14;
    fExpectedValue = 0.7965;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 15;
    fExpectedValue = 0.87438;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 16;
    fExpectedValue = 1.16348;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 17;
    fExpectedValue = 1.26968;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 18;
    fExpectedValue = 1.38296;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 19;
    fExpectedValue = 1.49506;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 20;
    fExpectedValue = 1.61424;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 21;
    fExpectedValue = 1.73342;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 22;
    fExpectedValue = 1.87384;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 23;
    fExpectedValue = 2.01308;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 24;
    fExpectedValue = 2.15586;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 25;
    fExpectedValue = 2.29864;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 26;
    fExpectedValue = 2.4544;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 27;
    fExpectedValue = 2.61016;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 28;
    fExpectedValue = 2.77536;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 29;
    fExpectedValue = 2.94174;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 30;
    fExpectedValue = 3.11992;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 31;
    fExpectedValue = 3.2981;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    iCount = 32;
    fExpectedValue = 3.2981;
    p_oTrees[iSpecies][iCount]->GetValue(p_oPop->GetFloatDataCode(cLabel, p_oTrees[iSpecies][iCount]->GetSpecies(), p_oTrees[iSpecies][iCount]->GetType()), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.0001);

    //Check the total values for each species
    p_oValueGrid = p_oSimManager->GetGridObject("Merchantable Timber Value");
    EXPECT_EQ(1, p_oValueGrid->GetNumberXCells());
    EXPECT_EQ(1, p_oValueGrid->GetNumberYCells());

    //Species 0
    fExpectedValue = 0;
    p_oValueGrid->GetValueOfCell(0, 0, p_oValueGrid->GetFloatDataCode("value_0"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

    //Species 1
    fExpectedValue = 31.28136;
    p_oValueGrid->GetValueOfCell(0, 0, p_oValueGrid->GetFloatDataCode("value_1"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

    //Species 2
    fExpectedValue = 23.83865;
    p_oValueGrid->GetValueOfCell(0, 0, p_oValueGrid->GetFloatDataCode("value_2"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

    //Species 3
    fExpectedValue = 274.76352;
    p_oValueGrid->GetValueOfCell(0, 0, p_oValueGrid->GetFloatDataCode("value_3"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

    //Species 4
    fExpectedValue = 6.87516;
    p_oValueGrid->GetValueOfCell(0, 0, p_oValueGrid->GetFloatDataCode("value_4"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

    //Species 5
    fExpectedValue = 162.07136;
    p_oValueGrid->GetValueOfCell(0, 0, p_oValueGrid->GetFloatDataCode("value_5"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

    //Species 6
    fExpectedValue = 44.03288;
    p_oValueGrid->GetValueOfCell(0, 0, p_oValueGrid->GetFloatDataCode("value_6"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

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
    p_oValueGrid->GetValueOfCell(0, 0, p_oValueGrid->GetFloatDataCode("value_0"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    p_oValueGrid->GetValueOfCell(0, 0, p_oValueGrid->GetFloatDataCode("value_1"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    p_oValueGrid->GetValueOfCell(0, 0, p_oValueGrid->GetFloatDataCode("value_2"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    p_oValueGrid->GetValueOfCell(0, 0, p_oValueGrid->GetFloatDataCode("value_3"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    p_oValueGrid->GetValueOfCell(0, 0, p_oValueGrid->GetFloatDataCode("value_4"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    p_oValueGrid->GetValueOfCell(0, 0, p_oValueGrid->GetFloatDataCode("value_5"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);
    p_oValueGrid->GetValueOfCell(0, 0, p_oValueGrid->GetFloatDataCode("value_6"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

    //Delete our array
    for (i = 0; i < iNumSpecies; i++) {
      delete[] p_oTrees[i];
    }
    delete[] p_oTrees;

    delete p_oSimManager;
  } catch (modelErr &e) {
    for (int i = 0; i < iNumSpecies; i++) {
      delete[] p_oTrees[i];
    }
    delete[] p_oTrees;
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

////////////////////////////////////////////////////////////////////////////
// WriteMerchValueCalculatorXMLFile1()
////////////////////////////////////////////////////////////////////////////
const char* WriteMerchValueCalculatorXMLFile1() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  WriteMerchValueCalculatorCommonStuff(oOut);

  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>MerchValueCalculator</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_4\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_5\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_6\" type=\"Adult\"/>"
       << "</behavior>"
       << "</behaviorList>";

  oOut << "<MerchValueCalculator1>"
       << "<an_merchValueFormClasses>"
       << "<an_mvfcVal species=\"Species_1\">78</an_mvfcVal>"
       << "<an_mvfcVal species=\"Species_2\">79</an_mvfcVal>"
       << "<an_mvfcVal species=\"Species_3\">80</an_mvfcVal>"
       << "<an_mvfcVal species=\"Species_4\">81</an_mvfcVal>"
       << "<an_mvfcVal species=\"Species_5\">84</an_mvfcVal>"
       << "<an_mvfcVal species=\"Species_6\">85</an_mvfcVal>"
       << "</an_merchValueFormClasses>"
       << "<an_merchValuePricePer1KFeet>"
       << "<an_mvpp1kfVal species=\"Species_1\">1.23</an_mvpp1kfVal>"
       << "<an_mvpp1kfVal species=\"Species_2\">0.89</an_mvpp1kfVal>"
       << "<an_mvpp1kfVal species=\"Species_3\">9.76</an_mvpp1kfVal>"
       << "<an_mvpp1kfVal species=\"Species_4\">0.23</an_mvpp1kfVal>"
       << "<an_mvpp1kfVal species=\"Species_5\">4.51</an_mvpp1kfVal>"
       << "<an_mvpp1kfVal species=\"Species_6\">1.18</an_mvpp1kfVal>"
       << "</an_merchValuePricePer1KFeet>"
       << "</MerchValueCalculator1>"
       << "</paramFile>";

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteMerchValueCalculatorXMLErrorFile1()
////////////////////////////////////////////////////////////////////////////
const char* WriteMerchValueCalculatorXMLErrorFile1() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  WriteMerchValueCalculatorCommonStuff(oOut);

  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>MerchValueCalculator</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_4\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_5\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_6\" type=\"Adult\"/>"
       << "</behavior>"
       << "</behaviorList>";

  oOut << "<MerchValueCalculator1>"
       << "<an_merchValueFormClasses>"
       << "<an_mvfcVal species=\"Species_1\">68</an_mvfcVal>"
       << "<an_mvfcVal species=\"Species_2\">79</an_mvfcVal>"
       << "<an_mvfcVal species=\"Species_3\">80</an_mvfcVal>"
       << "<an_mvfcVal species=\"Species_4\">81</an_mvfcVal>"
       << "<an_mvfcVal species=\"Species_5\">84</an_mvfcVal>"
       << "<an_mvfcVal species=\"Species_6\">85</an_mvfcVal>"
       << "</an_merchValueFormClasses>"
       << "<an_merchValuePricePer1KFeet>"
       << "<an_mvpp1kfVal species=\"Species_1\">1.23</an_mvpp1kfVal>"
       << "<an_mvpp1kfVal species=\"Species_2\">0.89</an_mvpp1kfVal>"
       << "<an_mvpp1kfVal species=\"Species_3\">9.76</an_mvpp1kfVal>"
       << "<an_mvpp1kfVal species=\"Species_4\">0.23</an_mvpp1kfVal>"
       << "<an_mvpp1kfVal species=\"Species_5\">4.51</an_mvpp1kfVal>"
       << "<an_mvpp1kfVal species=\"Species_6\">1.18</an_mvpp1kfVal>"
       << "</an_merchValuePricePer1KFeet>"
       << "</MerchValueCalculator1>"
       << "</paramFile>";

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteMerchValueCalculatorXMLErrorFile2()
////////////////////////////////////////////////////////////////////////////
const char* WriteMerchValueCalculatorXMLErrorFile2() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  WriteMerchValueCalculatorCommonStuff(oOut);

  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>MerchValueCalculator</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Seedling\"/>"
       << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_4\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_5\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_6\" type=\"Adult\"/>"
       << "</behavior>"
       << "</behaviorList>";

  oOut << "<MerchValueCalculator1>"
       << "<an_merchValueFormClasses>"
       << "<an_mvfcVal species=\"Species_1\">78</an_mvfcVal>"
       << "<an_mvfcVal species=\"Species_2\">79</an_mvfcVal>"
       << "<an_mvfcVal species=\"Species_3\">80</an_mvfcVal>"
       << "<an_mvfcVal species=\"Species_4\">81</an_mvfcVal>"
       << "<an_mvfcVal species=\"Species_5\">84</an_mvfcVal>"
       << "<an_mvfcVal species=\"Species_6\">85</an_mvfcVal>"
       << "</an_merchValueFormClasses>"
       << "<an_merchValuePricePer1KFeet>"
       << "<an_mvpp1kfVal species=\"Species_1\">1.23</an_mvpp1kfVal>"
       << "<an_mvpp1kfVal species=\"Species_2\">0.89</an_mvpp1kfVal>"
       << "<an_mvpp1kfVal species=\"Species_3\">9.76</an_mvpp1kfVal>"
       << "<an_mvpp1kfVal species=\"Species_4\">0.23</an_mvpp1kfVal>"
       << "<an_mvpp1kfVal species=\"Species_5\">4.51</an_mvpp1kfVal>"
       << "<an_mvpp1kfVal species=\"Species_6\">1.18</an_mvpp1kfVal>"
       << "</an_merchValuePricePer1KFeet>"
       << "</MerchValueCalculator1>"
       << "</paramFile>";

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteMerchValueCalculatorCommonStuff()
/////////////////////////////////////////////////////////////////////////////
void WriteMerchValueCalculatorCommonStuff( std::fstream &oOut )
{
  using namespace std;
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
       << "<tr_species speciesName=\"Species_0\" />"
       << "<tr_species speciesName=\"Species_1\" />"
       << "<tr_species speciesName=\"Species_2\" />"
       << "<tr_species speciesName=\"Species_3\" />"
       << "<tr_species speciesName=\"Species_4\" />"
       << "<tr_species speciesName=\"Species_5\" />"
       << "<tr_species speciesName=\"Species_6\" />"
       << "</tr_speciesList>"
       << "<tr_seedDiam10Cm>0.1</tr_seedDiam10Cm>"
       << "<tr_minAdultDBH>"
       << "<tr_madVal species=\"Species_0\">0.0</tr_madVal>"
       << "<tr_madVal species=\"Species_1\">0.0</tr_madVal>"
       << "<tr_madVal species=\"Species_2\">0.0</tr_madVal>"
       << "<tr_madVal species=\"Species_3\">0.0</tr_madVal>"
       << "<tr_madVal species=\"Species_4\">0.0</tr_madVal>"
       << "<tr_madVal species=\"Species_5\">0.0</tr_madVal>"
       << "<tr_madVal species=\"Species_6\">0.0</tr_madVal>"
       << "</tr_minAdultDBH>"
       << "<tr_maxSeedlingHeight>"
       << "<tr_mshVal species=\"Species_0\">1.35</tr_mshVal>"
       << "<tr_mshVal species=\"Species_1\">1.35</tr_mshVal>"
       << "<tr_mshVal species=\"Species_2\">1.35</tr_mshVal>"
       << "<tr_mshVal species=\"Species_3\">1.35</tr_mshVal>"
       << "<tr_mshVal species=\"Species_4\">1.35</tr_mshVal>"
       << "<tr_mshVal species=\"Species_5\">1.35</tr_mshVal>"
       << "<tr_mshVal species=\"Species_6\">1.35</tr_mshVal>"
       << "</tr_maxSeedlingHeight>"
       << "</trees>"
       << "<allometry>"
       << "<tr_canopyHeight>"
       << "<tr_chVal species=\"Species_0\">39.48</tr_chVal>"
       << "<tr_chVal species=\"Species_1\">39.48</tr_chVal>"
       << "<tr_chVal species=\"Species_2\">39.48</tr_chVal>"
       << "<tr_chVal species=\"Species_3\">39.48</tr_chVal>"
       << "<tr_chVal species=\"Species_4\">39.48</tr_chVal>"
       << "<tr_chVal species=\"Species_5\">39.48</tr_chVal>"
       << "<tr_chVal species=\"Species_6\">39.48</tr_chVal>"
       << "</tr_canopyHeight>"
       << "<tr_stdAsympCrownRad>"
       << "<tr_sacrVal species=\"Species_0\">0.0549</tr_sacrVal>"
       << "<tr_sacrVal species=\"Species_1\">0.0549</tr_sacrVal>"
       << "<tr_sacrVal species=\"Species_2\">0.0549</tr_sacrVal>"
       << "<tr_sacrVal species=\"Species_3\">0.0549</tr_sacrVal>"
       << "<tr_sacrVal species=\"Species_4\">0.0549</tr_sacrVal>"
       << "<tr_sacrVal species=\"Species_5\">0.0549</tr_sacrVal>"
       << "<tr_sacrVal species=\"Species_6\">0.0549</tr_sacrVal>"
       << "</tr_stdAsympCrownRad>"
       << "<tr_stdCrownRadExp>"
       << "<tr_screVal species=\"Species_0\">1.0</tr_screVal>"
       << "<tr_screVal species=\"Species_1\">1.0</tr_screVal>"
       << "<tr_screVal species=\"Species_2\">1.0</tr_screVal>"
       << "<tr_screVal species=\"Species_3\">1.0</tr_screVal>"
       << "<tr_screVal species=\"Species_4\">1.0</tr_screVal>"
       << "<tr_screVal species=\"Species_5\">1.0</tr_screVal>"
       << "<tr_screVal species=\"Species_6\">1.0</tr_screVal>"
       << "</tr_stdCrownRadExp>"
       << "<tr_stdMaxCrownRad>"
       << "<tr_smcrVal species=\"Species_0\">10</tr_smcrVal>"
       << "<tr_smcrVal species=\"Species_1\">10</tr_smcrVal>"
       << "<tr_smcrVal species=\"Species_2\">10</tr_smcrVal>"
       << "<tr_smcrVal species=\"Species_3\">10</tr_smcrVal>"
       << "<tr_smcrVal species=\"Species_4\">10</tr_smcrVal>"
       << "<tr_smcrVal species=\"Species_5\">10</tr_smcrVal>"
       << "<tr_smcrVal species=\"Species_6\">10</tr_smcrVal>"
       << "</tr_stdMaxCrownRad>"
       << "<tr_conversionDiam10ToDBH>"
       << "<tr_cdtdVal species=\"Species_0\">0.8008</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_1\">0.8008</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_2\">0.8008</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_3\">0.8008</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_4\">0.8008</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_5\">0.8008</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_6\">0.8008</tr_cdtdVal>"
       << "</tr_conversionDiam10ToDBH>"
       << "<tr_interceptDiam10ToDBH>"
       << "<tr_idtdVal species=\"Species_0\">0</tr_idtdVal>"
       << "<tr_idtdVal species=\"Species_1\">0</tr_idtdVal>"
       << "<tr_idtdVal species=\"Species_2\">0</tr_idtdVal>"
       << "<tr_idtdVal species=\"Species_3\">0</tr_idtdVal>"
       << "<tr_idtdVal species=\"Species_4\">0</tr_idtdVal>"
       << "<tr_idtdVal species=\"Species_5\">0</tr_idtdVal>"
       << "<tr_idtdVal species=\"Species_6\">0</tr_idtdVal>"
       << "</tr_interceptDiam10ToDBH>"
       << "<tr_stdAsympCrownHt>"
       << "<tr_sachVal species=\"Species_0\">0.389</tr_sachVal>"
       << "<tr_sachVal species=\"Species_1\">0.389</tr_sachVal>"
       << "<tr_sachVal species=\"Species_2\">0.389</tr_sachVal>"
       << "<tr_sachVal species=\"Species_3\">0.389</tr_sachVal>"
       << "<tr_sachVal species=\"Species_4\">0.389</tr_sachVal>"
       << "<tr_sachVal species=\"Species_5\">0.389</tr_sachVal>"
       << "<tr_sachVal species=\"Species_6\">0.389</tr_sachVal>"
       << "</tr_stdAsympCrownHt>"
       << "<tr_stdCrownHtExp>"
       << "<tr_scheVal species=\"Species_0\">1.0</tr_scheVal>"
       << "<tr_scheVal species=\"Species_1\">1.0</tr_scheVal>"
       << "<tr_scheVal species=\"Species_2\">1.0</tr_scheVal>"
       << "<tr_scheVal species=\"Species_3\">1.0</tr_scheVal>"
       << "<tr_scheVal species=\"Species_4\">1.0</tr_scheVal>"
       << "<tr_scheVal species=\"Species_5\">1.0</tr_scheVal>"
       << "<tr_scheVal species=\"Species_6\">1.0</tr_scheVal>"
       << "</tr_stdCrownHtExp>"
       << "<tr_slopeOfHeight-Diam10>"
       << "<tr_sohdVal species=\"Species_0\">0.03418</tr_sohdVal>"
       << "<tr_sohdVal species=\"Species_1\">0.03418</tr_sohdVal>"
       << "<tr_sohdVal species=\"Species_2\">0.03418</tr_sohdVal>"
       << "<tr_sohdVal species=\"Species_3\">0.03418</tr_sohdVal>"
       << "<tr_sohdVal species=\"Species_4\">0.03418</tr_sohdVal>"
       << "<tr_sohdVal species=\"Species_5\">0.03418</tr_sohdVal>"
       << "<tr_sohdVal species=\"Species_6\">0.03418</tr_sohdVal>"
       << "</tr_slopeOfHeight-Diam10>"
       << "<tr_slopeOfAsymHeight>"
       << "<tr_soahVal species=\"Species_0\">0.0299</tr_soahVal>"
       << "<tr_soahVal species=\"Species_1\">0.0241</tr_soahVal>"
       << "<tr_soahVal species=\"Species_2\">0.0263</tr_soahVal>"
       << "<tr_soahVal species=\"Species_3\">0.0263</tr_soahVal>"
       << "<tr_soahVal species=\"Species_4\">0.0263</tr_soahVal>"
       << "<tr_soahVal species=\"Species_5\">0.0263</tr_soahVal>"
       << "<tr_soahVal species=\"Species_6\">0.0263</tr_soahVal>"
       << "</tr_slopeOfAsymHeight>"
       << "<tr_whatSeedlingHeightDiam>"
       << "<tr_wsehdVal species=\"Species_0\">0</tr_wsehdVal>"
       << "<tr_wsehdVal species=\"Species_1\">0</tr_wsehdVal>"
       << "<tr_wsehdVal species=\"Species_2\">0</tr_wsehdVal>"
       << "<tr_wsehdVal species=\"Species_3\">0</tr_wsehdVal>"
       << "<tr_wsehdVal species=\"Species_4\">0</tr_wsehdVal>"
       << "<tr_wsehdVal species=\"Species_5\">0</tr_wsehdVal>"
       << "<tr_wsehdVal species=\"Species_6\">0</tr_wsehdVal>"
       << "</tr_whatSeedlingHeightDiam>"
       << "<tr_whatSaplingHeightDiam>"
       << "<tr_wsahdVal species=\"Species_0\">0</tr_wsahdVal>"
       << "<tr_wsahdVal species=\"Species_1\">0</tr_wsahdVal>"
       << "<tr_wsahdVal species=\"Species_2\">0</tr_wsahdVal>"
       << "<tr_wsahdVal species=\"Species_3\">0</tr_wsahdVal>"
       << "<tr_wsahdVal species=\"Species_4\">0</tr_wsahdVal>"
       << "<tr_wsahdVal species=\"Species_5\">0</tr_wsahdVal>"
       << "<tr_wsahdVal species=\"Species_6\">0</tr_wsahdVal>"
       << "</tr_whatSaplingHeightDiam>"
       << "<tr_whatAdultHeightDiam>"
       << "<tr_wahdVal species=\"Species_0\">0</tr_wahdVal>"
       << "<tr_wahdVal species=\"Species_1\">0</tr_wahdVal>"
       << "<tr_wahdVal species=\"Species_2\">0</tr_wahdVal>"
       << "<tr_wahdVal species=\"Species_3\">0</tr_wahdVal>"
       << "<tr_wahdVal species=\"Species_4\">0</tr_wahdVal>"
       << "<tr_wahdVal species=\"Species_5\">0</tr_wahdVal>"
       << "<tr_wahdVal species=\"Species_6\">0</tr_wahdVal>"
       << "</tr_whatAdultHeightDiam>"
       << "<tr_whatAdultCrownRadDiam>"
       << "<tr_wacrdVal species=\"Species_0\">0</tr_wacrdVal>"
       << "<tr_wacrdVal species=\"Species_1\">0</tr_wacrdVal>"
       << "<tr_wacrdVal species=\"Species_2\">0</tr_wacrdVal>"
       << "<tr_wacrdVal species=\"Species_3\">0</tr_wacrdVal>"
       << "<tr_wacrdVal species=\"Species_4\">0</tr_wacrdVal>"
       << "<tr_wacrdVal species=\"Species_5\">0</tr_wacrdVal>"
       << "<tr_wacrdVal species=\"Species_6\">0</tr_wacrdVal>"
       << "</tr_whatAdultCrownRadDiam>"
       << "<tr_whatAdultCrownHeightHeight>"
       << "<tr_wachhVal species=\"Species_0\">0</tr_wachhVal>"
       << "<tr_wachhVal species=\"Species_1\">0</tr_wachhVal>"
       << "<tr_wachhVal species=\"Species_2\">0</tr_wachhVal>"
       << "<tr_wachhVal species=\"Species_3\">0</tr_wachhVal>"
       << "<tr_wachhVal species=\"Species_4\">0</tr_wachhVal>"
       << "<tr_wachhVal species=\"Species_5\">0</tr_wachhVal>"
       << "<tr_wachhVal species=\"Species_6\">0</tr_wachhVal>"
       << "</tr_whatAdultCrownHeightHeight>"
       << "<tr_whatSaplingCrownRadDiam>"
       << "<tr_wscrdVal species=\"Species_0\">0</tr_wscrdVal>"
       << "<tr_wscrdVal species=\"Species_1\">0</tr_wscrdVal>"
       << "<tr_wscrdVal species=\"Species_2\">0</tr_wscrdVal>"
       << "<tr_wscrdVal species=\"Species_3\">0</tr_wscrdVal>"
       << "<tr_wscrdVal species=\"Species_4\">0</tr_wscrdVal>"
       << "<tr_wscrdVal species=\"Species_5\">0</tr_wscrdVal>"
       << "<tr_wscrdVal species=\"Species_6\">0</tr_wscrdVal>"
       << "</tr_whatSaplingCrownRadDiam>"
       << "<tr_whatSaplingCrownHeightHeight>"
       << "<tr_wschhVal species=\"Species_0\">0</tr_wschhVal>"
       << "<tr_wschhVal species=\"Species_1\">0</tr_wschhVal>"
       << "<tr_wschhVal species=\"Species_2\">0</tr_wschhVal>"
       << "<tr_wschhVal species=\"Species_3\">0</tr_wschhVal>"
       << "<tr_wschhVal species=\"Species_4\">0</tr_wschhVal>"
       << "<tr_wschhVal species=\"Species_5\">0</tr_wschhVal>"
       << "<tr_wschhVal species=\"Species_6\">0</tr_wschhVal>"
       << "</tr_whatSaplingCrownHeightHeight>"
       << "</allometry>";
}
