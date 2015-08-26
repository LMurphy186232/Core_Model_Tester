//---------------------------------------------------------------------------
// TestBoleVolumeCalculator.cpp
//---------------------------------------------------------------------------
#include "TestBoleVolumeCalculator.h"
#include <gtest/gtest.h>
#include <fstream>
#include <math.h>
#include "TreePopulation.h"
#include "SimManager.h"
#include "BehaviorBase.h"


////////////////////////////////////////////////////////////////////////////
// TestErrorProcessing()
////////////////////////////////////////////////////////////////////////////
TEST(BoleVolumeCalculator, TestErrorProcessing) {

  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try
  {
    p_oSimManager->ReadFile(WriteBoleVolumeCalculatorXMLErrorFile1());
    FAIL() << "TestBoleVolumeCalculator error processing didn't catch error for WriteBoleVolumeCalculatorXMLErrorFile1.";
  }
  catch (modelErr& err)
  {
    if (err.sFunction.compare("clBoleVolumeCalculator::GetParameterFileData") != 0)
    {
      FAIL() << "TestBoleVolumeCalculator error processing caught wrong error for WriteBoleVolumeCalculatorXMLErrorFile1.";
    }
    ;
  }

  try
  {
    p_oSimManager->ReadFile(WriteBoleVolumeCalculatorXMLErrorFile2());
    FAIL() << "TestBoleVolumeCalculator error processing didn't catch error for WriteBoleVolumeCalculatorXMLErrorFile2.";
  }
  catch (modelErr& err)
  {
    if (err.sFunction.compare("clBoleVolumeCalculator::GetParameterFileData") != 0)
    {
      FAIL() << "TestBoleVolumeCalculator error processing caught wrong error for WriteBoleVolumeCalculatorXMLErrorFile2.";
    }
    ;
  }

  try
  {
    p_oSimManager->ReadFile(WriteBoleVolumeCalculatorXMLErrorFile3());
    FAIL() << "TestBoleVolumeCalculator error processing didn't catch error for WriteBoleVolumeCalculatorXMLErrorFile3.";
  }
  catch (modelErr& err)
  {
    if (err.sFunction.compare("clBoleVolumeCalculator::RegisterTreeDataMembers") != 0)
    {
      FAIL() << "TestBoleVolumeCalculator error processing caught wrong error for WriteBoleVolumeCalculatorXMLErrorFile3.";
    }
    ;
  }
  delete p_oSimManager;
}

////////////////////////////////////////////////////////////////////////////
// TestNormalProcessing()
// Tests normal processing. WriteBoleVolumeCalculatorXMLFile1() does setup.
// Then 87 trees are created. A simulation is run for one timestep then the
// volume checked for all those trees.
////////////////////////////////////////////////////////////////////////////
TEST(BoleVolumeCalculator, TestNormalProcessing) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  clTree **p_oTrees; //array to hold our target trees
  try {
    clTreePopulation * p_oPop;
    float fVolume, fExpectedVolume, fDiam;
    int iNumTrees = 87, iCount = 0, iSpecies;

    //Load our test file and get our tree population pointers
    p_oSimManager->ReadFile( WriteBoleVolumeCalculatorXMLFile1() );
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );

    //Create the array of target trees
    p_oTrees = new clTree*[iNumTrees];

    //Create our trees

    iSpecies = 4;
    fDiam = 13;
    p_oTrees[iCount] = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, fDiam);
    iCount++;

    iSpecies = 1;
    fDiam = 30;
    p_oTrees[iCount] = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, fDiam);
    iCount++;

    iSpecies = 5;
    fDiam = 32;
    p_oTrees[iCount] = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, fDiam);
    iCount++;

    iSpecies = 1;
    fDiam = 69;
    p_oTrees[iCount] = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, fDiam);
    iCount++;

    iSpecies = 1;
    fDiam = 74;
    p_oTrees[iCount] = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, fDiam);
    iCount++;

    iSpecies = 1;
    fDiam = 79;
    p_oTrees[iCount] = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, fDiam);
    iCount++;

    iSpecies = 1;
    fDiam = 84;
    p_oTrees[iCount] = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, fDiam);
    iCount++;

    iSpecies = 1;
    fDiam = 89;
    p_oTrees[iCount] = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, fDiam);
    iCount++;

    iSpecies = 1;
    fDiam = 94;
    p_oTrees[iCount] = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, fDiam);
    iCount++;

    iSpecies = 1;
    fDiam = 99;
    p_oTrees[iCount] = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, fDiam);
    iCount++;

    iSpecies = 1;
    fDiam = 110;
    p_oTrees[iCount] = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, fDiam);
    iCount++;

    iSpecies = 2;
    fDiam = 107;
    p_oTrees[iCount] = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, fDiam);
    iCount++;

    iSpecies = 2;
    fDiam = 29;
    p_oTrees[iCount] = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, fDiam);
    iCount++;

    iSpecies = 2;
    fDiam = 35;
    p_oTrees[iCount] = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, fDiam);
    iCount++;

    iSpecies = 2;
    fDiam = 39;
    p_oTrees[iCount] = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, fDiam);
    iCount++;

    iSpecies = 2;
    fDiam = 45;
    p_oTrees[iCount] = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, fDiam);
    iCount++;

    iSpecies = 2;
    fDiam = 49;
    p_oTrees[iCount] = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, fDiam);
    iCount++;

    iSpecies = 2;
    fDiam = 55;
    p_oTrees[iCount] = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, fDiam);
    iCount++;

    iSpecies = 2;
    fDiam = 60;
    p_oTrees[iCount] = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, fDiam);
    iCount++;

    iSpecies = 2;
    fDiam = 65;
    p_oTrees[iCount] = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, fDiam);
    iCount++;

    iSpecies = 2;
    fDiam = 71;
    p_oTrees[iCount] = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, fDiam);
    iCount++;

    iSpecies = 2;
    fDiam = 76;
    p_oTrees[iCount] = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, fDiam);
    iCount++;

    iSpecies = 2;
    fDiam = 112;
    p_oTrees[iCount] = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, fDiam);
    iCount++;

    iSpecies = 2;
    fDiam = 80.5;
    p_oTrees[iCount] = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, fDiam);
    iCount++;

    iSpecies = 2;
    fDiam = 85.5;
    p_oTrees[iCount] = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, fDiam);
    iCount++;

    iSpecies = 2;
    fDiam = 90.5;
    p_oTrees[iCount] = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, fDiam);
    iCount++;

    iSpecies = 2;
    fDiam = 95.5;
    p_oTrees[iCount] = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, fDiam);
    iCount++;

    iSpecies = 2;
    fDiam = 100.5;
    p_oTrees[iCount] = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, fDiam);
    iCount++;

    iSpecies = 2;
    fDiam = 105.5;
    p_oTrees[iCount] = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, fDiam);
    iCount++;

    iSpecies = 3;
    fDiam = 31;
    p_oTrees[iCount] = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, fDiam);
    iCount++;

    iSpecies = 3;
    fDiam = 37;
    p_oTrees[iCount] = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, fDiam);
    iCount++;

    iSpecies = 3;
    fDiam = 43;
    p_oTrees[iCount] = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, fDiam);
    iCount++;

    iSpecies = 3;
    fDiam = 47;
    p_oTrees[iCount] = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, fDiam);
    iCount++;

    iSpecies = 3;
    fDiam = 52;
    p_oTrees[iCount] = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, fDiam);
    iCount++;

    iSpecies = 3;
    fDiam = 57;
    p_oTrees[iCount] = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, fDiam);
    iCount++;

    iSpecies = 3;
    fDiam = 62;
    p_oTrees[iCount] = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, fDiam);
    iCount++;

    iSpecies = 3;
    fDiam = 68;
    p_oTrees[iCount] = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, fDiam);
    iCount++;

    iSpecies = 3;
    fDiam = 73;
    p_oTrees[iCount] = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, fDiam);
    iCount++;

    iSpecies = 3;
    fDiam = 77;
    p_oTrees[iCount] = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, fDiam);
    iCount++;

    iSpecies = 3;
    fDiam = 109;
    p_oTrees[iCount] = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, fDiam);
    iCount++;

    iSpecies = 3;
    fDiam = 104;
    p_oTrees[iCount] = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, fDiam);
    iCount++;

    iSpecies = 4;
    fDiam = 29.5;
    p_oTrees[iCount] = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, fDiam);
    iCount++;

    iSpecies = 4;
    fDiam = 30.457;
    p_oTrees[iCount] = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, fDiam);
    iCount++;

    iSpecies = 4;
    fDiam = 36;
    p_oTrees[iCount] = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, fDiam);
    iCount++;

    iSpecies = 4;
    fDiam = 42;
    p_oTrees[iCount] = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, fDiam);
    iCount++;

    iSpecies = 4;
    fDiam = 46;
    p_oTrees[iCount] = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, fDiam);
    iCount++;

    iSpecies = 4;
    fDiam = 51;
    p_oTrees[iCount] = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, fDiam);
    iCount++;

    iSpecies = 4;
    fDiam = 56;
    p_oTrees[iCount] = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, fDiam);
    iCount++;

    iSpecies = 4;
    fDiam = 61;
    p_oTrees[iCount] = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, fDiam);
    iCount++;

    iSpecies = 4;
    fDiam = 67;
    p_oTrees[iCount] = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, fDiam);
    iCount++;

    iSpecies = 4;
    fDiam = 72;
    p_oTrees[iCount] = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, fDiam);
    iCount++;

    iSpecies = 4;
    fDiam = 77;
    p_oTrees[iCount] = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, fDiam);
    iCount++;

    iSpecies = 4;
    fDiam = 82;
    p_oTrees[iCount] = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, fDiam);
    iCount++;

    iSpecies = 4;
    fDiam = 87;
    p_oTrees[iCount] = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, fDiam);
    iCount++;

    iSpecies = 4;
    fDiam = 92;
    p_oTrees[iCount] = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, fDiam);
    iCount++;

    iSpecies = 4;
    fDiam = 97;
    p_oTrees[iCount] = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, fDiam);
    iCount++;

    iSpecies = 4;
    fDiam = 102;
    p_oTrees[iCount] = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, fDiam);
    iCount++;

    iSpecies = 4;
    fDiam = 108;
    p_oTrees[iCount] = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, fDiam);
    iCount++;

    iSpecies = 5;
    fDiam = 38;
    p_oTrees[iCount] = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, fDiam);
    iCount++;

    iSpecies = 5;
    fDiam = 44;
    p_oTrees[iCount] = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, fDiam);
    iCount++;

    iSpecies = 5;
    fDiam = 48;
    p_oTrees[iCount] = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, fDiam);
    iCount++;

    iSpecies = 5;
    fDiam = 53;
    p_oTrees[iCount] = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, fDiam);
    iCount++;

    iSpecies = 5;
    fDiam = 58;
    p_oTrees[iCount] = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, fDiam);
    iCount++;

    iSpecies = 5;
    fDiam = 63;
    p_oTrees[iCount] = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, fDiam);
    iCount++;

    iSpecies = 5;
    fDiam = 80;
    p_oTrees[iCount] = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, fDiam);
    iCount++;

    iSpecies = 5;
    fDiam = 85;
    p_oTrees[iCount] = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, fDiam);
    iCount++;

    iSpecies = 5;
    fDiam = 90;
    p_oTrees[iCount] = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, fDiam);
    iCount++;

    iSpecies = 5;
    fDiam = 95;
    p_oTrees[iCount] = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, fDiam);
    iCount++;

    iSpecies = 5;
    fDiam = 100;
    p_oTrees[iCount] = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, fDiam);
    iCount++;

    iSpecies = 5;
    fDiam = 105;
    p_oTrees[iCount] = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, fDiam);
    iCount++;

    iSpecies = 6;
    fDiam = 82;
    p_oTrees[iCount] = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, fDiam);
    iCount++;

    iSpecies = 6;
    fDiam = 88;
    p_oTrees[iCount] = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, fDiam);
    iCount++;

    iSpecies = 6;
    fDiam = 93;
    p_oTrees[iCount] = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, fDiam);
    iCount++;

    iSpecies = 6;
    fDiam = 98;
    p_oTrees[iCount] = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, fDiam);
    iCount++;

    iSpecies = 6;
    fDiam = 103;
    p_oTrees[iCount] = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, fDiam);
    iCount++;

    iSpecies = 7;
    fDiam = 54;
    p_oTrees[iCount] = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, fDiam);
    iCount++;

    iSpecies = 7;
    fDiam = 59;
    p_oTrees[iCount] = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, fDiam);
    iCount++;

    iSpecies = 7;
    fDiam = 64;
    p_oTrees[iCount] = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, fDiam);
    iCount++;

    iSpecies = 7;
    fDiam = 70;
    p_oTrees[iCount] = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, fDiam);
    iCount++;

    iSpecies = 7;
    fDiam = 75;
    p_oTrees[iCount] = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, fDiam);
    iCount++;

    iSpecies = 7;
    fDiam = 111;
    p_oTrees[iCount] = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, fDiam);
    iCount++;

    iSpecies = 7;
    fDiam = 81;
    p_oTrees[iCount] = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, fDiam);
    iCount++;

    iSpecies = 7;
    fDiam = 86;
    p_oTrees[iCount] = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, fDiam);
    iCount++;

    iSpecies = 7;
    fDiam = 91;
    p_oTrees[iCount] = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, fDiam);
    iCount++;

    iSpecies = 7;
    fDiam = 96;
    p_oTrees[iCount] = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, fDiam);
    iCount++;

    iSpecies = 7;
    fDiam = 101;
    p_oTrees[iCount] = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, fDiam);
    iCount++;

    iSpecies = 7;
    fDiam = 106;
    p_oTrees[iCount] = p_oPop->CreateTree(10, 10, iSpecies, clTreePopulation::adult, fDiam);
    iCount++;

    //Now do the run
    p_oSimManager->RunSim(1);

    //Check the volume for each tree
    iCount = 0;
    p_oTrees[0]->GetValue(p_oPop->GetFloatDataCode("Bole Vol", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fVolume);
    fExpectedVolume = 0;
    EXPECT_EQ(fExpectedVolume, fVolume);
    iCount++;

    p_oTrees[1]->GetValue(p_oPop->GetFloatDataCode("Bole Vol", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fVolume);
    fExpectedVolume = 14.89783996;
    EXPECT_LT(fabs(fExpectedVolume - fVolume)/fExpectedVolume, 0.1);
    iCount++;

    p_oTrees[2]->GetValue(p_oPop->GetFloatDataCode("Bole Vol", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fVolume);
    fExpectedVolume = 23.83248686;
    EXPECT_LT(fabs(fExpectedVolume - fVolume)/fExpectedVolume, 0.1);
    iCount++;

    p_oTrees[3]->GetValue(p_oPop->GetFloatDataCode("Bole Vol", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fVolume);
    fExpectedVolume = 98.02871302;
    EXPECT_LT(fabs(fExpectedVolume - fVolume)/fExpectedVolume, 0.1);
    iCount++;

    p_oTrees[4]->GetValue(p_oPop->GetFloatDataCode("Bole Vol", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fVolume);
    fExpectedVolume = 112.764109;
    EXPECT_LT(fabs(fExpectedVolume - fVolume)/fExpectedVolume, 0.1);
    iCount++;

    p_oTrees[5]->GetValue(p_oPop->GetFloatDataCode("Bole Vol", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fVolume);
    fExpectedVolume = 128.5336044;
    EXPECT_LT(fabs(fExpectedVolume - fVolume)/fExpectedVolume, 0.1);
    iCount++;

    p_oTrees[6]->GetValue(p_oPop->GetFloatDataCode("Bole Vol", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fVolume);
    fExpectedVolume = 145.3373783;
    EXPECT_LT(fabs(fExpectedVolume - fVolume)/fExpectedVolume, 0.1);
    iCount++;

    p_oTrees[7]->GetValue(p_oPop->GetFloatDataCode("Bole Vol", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fVolume);
    fExpectedVolume = 163.1755954;
    EXPECT_LT(fabs(fExpectedVolume - fVolume)/fExpectedVolume, 0.1);
    iCount++;

    p_oTrees[8]->GetValue(p_oPop->GetFloatDataCode("Bole Vol", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fVolume);
    fExpectedVolume = 182.048408;
    EXPECT_LT(fabs(fExpectedVolume - fVolume)/fExpectedVolume, 0.1);
    iCount++;

    p_oTrees[9]->GetValue(p_oPop->GetFloatDataCode("Bole Vol", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fVolume);
    fExpectedVolume = 201.9559575;
    EXPECT_LT(fabs(fExpectedVolume - fVolume)/fExpectedVolume, 0.1);
    iCount++;

    p_oTrees[10]->GetValue(p_oPop->GetFloatDataCode("Bole Vol", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fVolume);
    fExpectedVolume = 289.7598581;
    EXPECT_LT(fabs(fExpectedVolume - fVolume)/fExpectedVolume, 0.1);
    iCount++;

    p_oTrees[11]->GetValue(p_oPop->GetFloatDataCode("Bole Vol", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fVolume);
    fExpectedVolume = 316.0673632;
    EXPECT_LT(fabs(fExpectedVolume - fVolume)/fExpectedVolume, 0.1);
    iCount++;

    p_oTrees[12]->GetValue(p_oPop->GetFloatDataCode("Bole Vol", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fVolume);
    fExpectedVolume = 16.62186809;
    EXPECT_LT(fabs(fExpectedVolume - fVolume)/fExpectedVolume, 0.1);
    iCount++;

    p_oTrees[13]->GetValue(p_oPop->GetFloatDataCode("Bole Vol", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fVolume);
    fExpectedVolume = 27.81814671;
    EXPECT_LT(fabs(fExpectedVolume - fVolume)/fExpectedVolume, 0.1);
    iCount++;

    p_oTrees[14]->GetValue(p_oPop->GetFloatDataCode("Bole Vol", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fVolume);
    fExpectedVolume = 34.51415961;
    EXPECT_LT(fabs(fExpectedVolume - fVolume)/fExpectedVolume, 0.1);
    iCount++;

    p_oTrees[15]->GetValue(p_oPop->GetFloatDataCode("Bole Vol", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fVolume);
    fExpectedVolume = 45.92789431;
    EXPECT_LT(fabs(fExpectedVolume - fVolume)/fExpectedVolume, 0.1);
    iCount++;

    p_oTrees[16]->GetValue(p_oPop->GetFloatDataCode("Bole Vol", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fVolume);
    fExpectedVolume = 54.45104078;
    EXPECT_LT(fabs(fExpectedVolume - fVolume)/fExpectedVolume, 0.1);
    iCount++;

    p_oTrees[17]->GetValue(p_oPop->GetFloatDataCode("Bole Vol", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fVolume);
    fExpectedVolume = 76.35456819;
    EXPECT_LT(fabs(fExpectedVolume - fVolume)/fExpectedVolume, 0.1);
    iCount++;

    p_oTrees[18]->GetValue(p_oPop->GetFloatDataCode("Bole Vol", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fVolume);
    fExpectedVolume = 90.8972732;
    EXPECT_LT(fabs(fExpectedVolume - fVolume)/fExpectedVolume, 0.1);
    iCount++;

    p_oTrees[19]->GetValue(p_oPop->GetFloatDataCode("Bole Vol", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fVolume);
    fExpectedVolume = 106.7168893;
    EXPECT_LT(fabs(fExpectedVolume - fVolume)/fExpectedVolume, 0.1);
    iCount++;

    p_oTrees[20]->GetValue(p_oPop->GetFloatDataCode("Bole Vol", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fVolume);
    fExpectedVolume = 127.387263;
    EXPECT_LT(fabs(fExpectedVolume - fVolume)/fExpectedVolume, 0.1);
    iCount++;

    p_oTrees[21]->GetValue(p_oPop->GetFloatDataCode("Bole Vol", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fVolume);
    fExpectedVolume = 146.0192772;
    EXPECT_LT(fabs(fExpectedVolume - fVolume)/fExpectedVolume, 0.1);
    iCount++;

    p_oTrees[22]->GetValue(p_oPop->GetFloatDataCode("Bole Vol", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fVolume);
    fExpectedVolume = 346.4313084;
    EXPECT_LT(fabs(fExpectedVolume - fVolume)/fExpectedVolume, 0.1);
    iCount++;

    p_oTrees[23]->GetValue(p_oPop->GetFloatDataCode("Bole Vol", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fVolume);
    fExpectedVolume = 178.4930169;
    EXPECT_LT(fabs(fExpectedVolume - fVolume)/fExpectedVolume, 0.1);
    iCount++;

    p_oTrees[24]->GetValue(p_oPop->GetFloatDataCode("Bole Vol", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fVolume);
    fExpectedVolume = 201.4455077;
    EXPECT_LT(fabs(fExpectedVolume - fVolume)/fExpectedVolume, 0.1);
    iCount++;

    p_oTrees[25]->GetValue(p_oPop->GetFloatDataCode("Bole Vol", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fVolume);
    fExpectedVolume = 225.7948166;
    EXPECT_LT(fabs(fExpectedVolume - fVolume)/fExpectedVolume, 0.1);
    iCount++;

    p_oTrees[26]->GetValue(p_oPop->GetFloatDataCode("Bole Vol", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fVolume);
    fExpectedVolume = 251.5417175;
    EXPECT_LT(fabs(fExpectedVolume - fVolume)/fExpectedVolume, 0.1);
    iCount++;

    p_oTrees[27]->GetValue(p_oPop->GetFloatDataCode("Bole Vol", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fVolume);
    fExpectedVolume = 278.6869417;
    EXPECT_LT(fabs(fExpectedVolume - fVolume)/fExpectedVolume, 0.1);
    iCount++;

    p_oTrees[28]->GetValue(p_oPop->GetFloatDataCode("Bole Vol", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fVolume);
    fExpectedVolume = 307.231183;
    EXPECT_LT(fabs(fExpectedVolume - fVolume)/fExpectedVolume, 0.1);
    iCount++;

    p_oTrees[29]->GetValue(p_oPop->GetFloatDataCode("Bole Vol", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fVolume);
    fExpectedVolume = 14.53547469;
    EXPECT_LT(fabs(fExpectedVolume - fVolume)/fExpectedVolume, 0.1);
    iCount++;

    p_oTrees[30]->GetValue(p_oPop->GetFloatDataCode("Bole Vol", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fVolume);
    fExpectedVolume = 20.65580939;
    EXPECT_LT(fabs(fExpectedVolume - fVolume)/fExpectedVolume, 0.1);
    iCount++;

    p_oTrees[31]->GetValue(p_oPop->GetFloatDataCode("Bole Vol", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fVolume);
    fExpectedVolume = 27.8657867;
    EXPECT_LT(fabs(fExpectedVolume - fVolume)/fExpectedVolume, 0.1);
    iCount++;

    p_oTrees[32]->GetValue(p_oPop->GetFloatDataCode("Bole Vol", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fVolume);
    fExpectedVolume = 33.27846225;
    EXPECT_LT(fabs(fExpectedVolume - fVolume)/fExpectedVolume, 0.1);
    iCount++;

    p_oTrees[33]->GetValue(p_oPop->GetFloatDataCode("Bole Vol", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fVolume);
    fExpectedVolume = 40.72670343;
    EXPECT_LT(fabs(fExpectedVolume - fVolume)/fExpectedVolume, 0.1);
    iCount++;

    p_oTrees[34]->GetValue(p_oPop->GetFloatDataCode("Bole Vol", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fVolume);
    fExpectedVolume = 48.93374073;
    EXPECT_LT(fabs(fExpectedVolume - fVolume)/fExpectedVolume, 0.1);
    iCount++;

    p_oTrees[35]->GetValue(p_oPop->GetFloatDataCode("Bole Vol", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fVolume);
    fExpectedVolume = 57.90013884;
    EXPECT_LT(fabs(fExpectedVolume - fVolume)/fExpectedVolume, 0.1);
    iCount++;

    p_oTrees[36]->GetValue(p_oPop->GetFloatDataCode("Bole Vol", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fVolume);
    fExpectedVolume = 69.66289787;
    EXPECT_LT(fabs(fExpectedVolume - fVolume)/fExpectedVolume, 0.1);
    iCount++;

    p_oTrees[37]->GetValue(p_oPop->GetFloatDataCode("Bole Vol", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fVolume);
    fExpectedVolume = 80.30165329;
    EXPECT_LT(fabs(fExpectedVolume - fVolume)/fExpectedVolume, 0.1);
    iCount++;

    p_oTrees[38]->GetValue(p_oPop->GetFloatDataCode("Bole Vol", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fVolume);
    fExpectedVolume = 89.36047242;
    EXPECT_LT(fabs(fExpectedVolume - fVolume)/fExpectedVolume, 0.1);
    iCount++;

    p_oTrees[39]->GetValue(p_oPop->GetFloatDataCode("Bole Vol", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fVolume);
    fExpectedVolume = 219.4867298;
    EXPECT_LT(fabs(fExpectedVolume - fVolume)/fExpectedVolume, 0.1);
    iCount++;

    p_oTrees[40]->GetValue(p_oPop->GetFloatDataCode("Bole Vol", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fVolume);
    fExpectedVolume = 199.7621041;
    EXPECT_LT(fabs(fExpectedVolume - fVolume)/fExpectedVolume, 0.1);
    iCount++;

    p_oTrees[41]->GetValue(p_oPop->GetFloatDataCode("Bole Vol", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fVolume);
    fExpectedVolume = 9.284435074;
    EXPECT_LT(fabs(fExpectedVolume - fVolume)/fExpectedVolume, 0.1);
    iCount++;

    p_oTrees[42]->GetValue(p_oPop->GetFloatDataCode("Bole Vol", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fVolume);
    fExpectedVolume = 9.910864368;
    EXPECT_LT(fabs(fExpectedVolume - fVolume)/fExpectedVolume, 0.1);
    iCount++;

    p_oTrees[43]->GetValue(p_oPop->GetFloatDataCode("Bole Vol", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fVolume);
    fExpectedVolume = 13.93446788;
    EXPECT_LT(fabs(fExpectedVolume - fVolume)/fExpectedVolume, 0.1);
    iCount++;

    p_oTrees[44]->GetValue(p_oPop->GetFloatDataCode("Bole Vol", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fVolume);
    fExpectedVolume = 19.04994956;
    EXPECT_LT(fabs(fExpectedVolume - fVolume)/fExpectedVolume, 0.1);
    iCount++;

    p_oTrees[45]->GetValue(p_oPop->GetFloatDataCode("Bole Vol", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fVolume);
    fExpectedVolume = 22.89947942;
    EXPECT_LT(fabs(fExpectedVolume - fVolume)/fExpectedVolume, 0.1);
    iCount++;

    p_oTrees[46]->GetValue(p_oPop->GetFloatDataCode("Bole Vol", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fVolume);
    fExpectedVolume = 28.20567109;
    EXPECT_LT(fabs(fExpectedVolume - fVolume)/fExpectedVolume, 0.1);
    iCount++;

    p_oTrees[47]->GetValue(p_oPop->GetFloatDataCode("Bole Vol", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fVolume);
    fExpectedVolume = 34.0612134;
    EXPECT_LT(fabs(fExpectedVolume - fVolume)/fExpectedVolume, 0.1);
    iCount++;

    p_oTrees[48]->GetValue(p_oPop->GetFloatDataCode("Bole Vol", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fVolume);
    fExpectedVolume = 40.46624897;
    EXPECT_LT(fabs(fExpectedVolume - fVolume)/fExpectedVolume, 0.1);
    iCount++;

    p_oTrees[49]->GetValue(p_oPop->GetFloatDataCode("Bole Vol", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fVolume);
    fExpectedVolume = 48.87779897;
    EXPECT_LT(fabs(fExpectedVolume - fVolume)/fExpectedVolume, 0.1);
    iCount++;

    p_oTrees[50]->GetValue(p_oPop->GetFloatDataCode("Bole Vol", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fVolume);
    fExpectedVolume = 56.49214364;
    EXPECT_LT(fabs(fExpectedVolume - fVolume)/fExpectedVolume, 0.1);
    iCount++;

    p_oTrees[51]->GetValue(p_oPop->GetFloatDataCode("Bole Vol", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fVolume);
    fExpectedVolume = 64.65633933;
    EXPECT_LT(fabs(fExpectedVolume - fVolume)/fExpectedVolume, 0.1);
    iCount++;

    p_oTrees[52]->GetValue(p_oPop->GetFloatDataCode("Bole Vol", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fVolume);
    fExpectedVolume = 73.37047547;
    EXPECT_LT(fabs(fExpectedVolume - fVolume)/fExpectedVolume, 0.1);
    iCount++;

    p_oTrees[53]->GetValue(p_oPop->GetFloatDataCode("Bole Vol", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fVolume);
    fExpectedVolume = 82.63463351;
    EXPECT_LT(fabs(fExpectedVolume - fVolume)/fExpectedVolume, 0.1);
    iCount++;

    p_oTrees[54]->GetValue(p_oPop->GetFloatDataCode("Bole Vol", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fVolume);
    fExpectedVolume = 92.44888808;
    EXPECT_LT(fabs(fExpectedVolume - fVolume)/fExpectedVolume, 0.1);
    iCount++;

    p_oTrees[55]->GetValue(p_oPop->GetFloatDataCode("Bole Vol", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fVolume);
    fExpectedVolume = 102.8133078;
    EXPECT_LT(fabs(fExpectedVolume - fVolume)/fExpectedVolume, 0.1);
    iCount++;

    p_oTrees[56]->GetValue(p_oPop->GetFloatDataCode("Bole Vol", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fVolume);
    fExpectedVolume = 113.7279562;
    EXPECT_LT(fabs(fExpectedVolume - fVolume)/fExpectedVolume, 0.1);
    iCount++;

    p_oTrees[57]->GetValue(p_oPop->GetFloatDataCode("Bole Vol", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fVolume);
    fExpectedVolume = 127.5519184;
    EXPECT_LT(fabs(fExpectedVolume - fVolume)/fExpectedVolume, 0.1);
    iCount++;

    p_oTrees[58]->GetValue(p_oPop->GetFloatDataCode("Bole Vol", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fVolume);
    fExpectedVolume = 33.76422112;
    EXPECT_LT(fabs(fExpectedVolume - fVolume)/fExpectedVolume, 0.1);
    iCount++;

    p_oTrees[59]->GetValue(p_oPop->GetFloatDataCode("Bole Vol", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fVolume);
    fExpectedVolume = 45.38620367;
    EXPECT_LT(fabs(fExpectedVolume - fVolume)/fExpectedVolume, 0.1);
    iCount++;

    p_oTrees[60]->GetValue(p_oPop->GetFloatDataCode("Bole Vol", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fVolume);
    fExpectedVolume = 54.07186943;
    EXPECT_LT(fabs(fExpectedVolume - fVolume)/fExpectedVolume, 0.1);
    iCount++;

    p_oTrees[61]->GetValue(p_oPop->GetFloatDataCode("Bole Vol", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fVolume);
    fExpectedVolume = 65.98251108;
    EXPECT_LT(fabs(fExpectedVolume - fVolume)/fExpectedVolume, 0.1);
    iCount++;

    p_oTrees[62]->GetValue(p_oPop->GetFloatDataCode("Bole Vol", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fVolume);
    fExpectedVolume = 79.06247759;
    EXPECT_LT(fabs(fExpectedVolume - fVolume)/fExpectedVolume, 0.1);
    iCount++;

    p_oTrees[63]->GetValue(p_oPop->GetFloatDataCode("Bole Vol", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fVolume);
    fExpectedVolume = 93.31045018;
    EXPECT_LT(fabs(fExpectedVolume - fVolume)/fExpectedVolume, 0.1);
    iCount++;

    p_oTrees[64]->GetValue(p_oPop->GetFloatDataCode("Bole Vol", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fVolume);
    fExpectedVolume = 183.2354969;
    EXPECT_LT(fabs(fExpectedVolume - fVolume)/fExpectedVolume, 0.1);
    iCount++;

    p_oTrees[65]->GetValue(p_oPop->GetFloatDataCode("Bole Vol", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fVolume);
    fExpectedVolume = 206.8525818;
    EXPECT_LT(fabs(fExpectedVolume - fVolume)/fExpectedVolume, 0.1);
    iCount++;

    p_oTrees[66]->GetValue(p_oPop->GetFloatDataCode("Bole Vol", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fVolume);
    fExpectedVolume = 231.8911946;
    EXPECT_LT(fabs(fExpectedVolume - fVolume)/fExpectedVolume, 0.1);
    iCount++;

    p_oTrees[67]->GetValue(p_oPop->GetFloatDataCode("Bole Vol", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fVolume);
    fExpectedVolume = 258.3504711;
    EXPECT_LT(fabs(fExpectedVolume - fVolume)/fExpectedVolume, 0.1);
    iCount++;

    p_oTrees[68]->GetValue(p_oPop->GetFloatDataCode("Bole Vol", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fVolume);
    fExpectedVolume = 286.2295733;
    EXPECT_LT(fabs(fExpectedVolume - fVolume)/fExpectedVolume, 0.1);
    iCount++;

    p_oTrees[69]->GetValue(p_oPop->GetFloatDataCode("Bole Vol", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fVolume);
    fExpectedVolume = 315.5276876;
    EXPECT_LT(fabs(fExpectedVolume - fVolume)/fExpectedVolume, 0.1);
    iCount++;

    p_oTrees[70]->GetValue(p_oPop->GetFloatDataCode("Bole Vol", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fVolume);
    fExpectedVolume = 116.823018;
    EXPECT_LT(fabs(fExpectedVolume - fVolume)/fExpectedVolume, 0.1);
    iCount++;

    p_oTrees[71]->GetValue(p_oPop->GetFloatDataCode("Bole Vol", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fVolume);
    fExpectedVolume = 134.6112163;
    EXPECT_LT(fabs(fExpectedVolume - fVolume)/fExpectedVolume, 0.1);
    iCount++;

    p_oTrees[72]->GetValue(p_oPop->GetFloatDataCode("Bole Vol", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fVolume);
    fExpectedVolume = 150.3970906;
    EXPECT_LT(fabs(fExpectedVolume - fVolume)/fExpectedVolume, 0.1);
    iCount++;

    p_oTrees[73]->GetValue(p_oPop->GetFloatDataCode("Bole Vol", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fVolume);
    fExpectedVolume = 167.0576637;
    EXPECT_LT(fabs(fExpectedVolume - fVolume)/fExpectedVolume, 0.1);
    iCount++;

    p_oTrees[74]->GetValue(p_oPop->GetFloatDataCode("Bole Vol", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fVolume);
    fExpectedVolume = 184.5927597;
    EXPECT_LT(fabs(fExpectedVolume - fVolume)/fExpectedVolume, 0.1);
    iCount++;

    p_oTrees[75]->GetValue(p_oPop->GetFloatDataCode("Bole Vol", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fVolume);
    fExpectedVolume = 86.56138632;
    EXPECT_LT(fabs(fExpectedVolume - fVolume)/fExpectedVolume, 0.1);
    iCount++;

    p_oTrees[76]->GetValue(p_oPop->GetFloatDataCode("Bole Vol", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fVolume);
    fExpectedVolume = 103.3394141;
    EXPECT_LT(fabs(fExpectedVolume - fVolume)/fExpectedVolume, 0.1);
    iCount++;

    p_oTrees[77]->GetValue(p_oPop->GetFloatDataCode("Bole Vol", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fVolume);
    fExpectedVolume = 121.6004638;
    EXPECT_LT(fabs(fExpectedVolume - fVolume)/fExpectedVolume, 0.1);
    iCount++;

    p_oTrees[78]->GetValue(p_oPop->GetFloatDataCode("Bole Vol", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fVolume);
    fExpectedVolume = 145.4708439;
    EXPECT_LT(fabs(fExpectedVolume - fVolume)/fExpectedVolume, 0.1);
    iCount++;

    p_oTrees[79]->GetValue(p_oPop->GetFloatDataCode("Bole Vol", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fVolume);
    fExpectedVolume = 166.9933882;
    EXPECT_LT(fabs(fExpectedVolume - fVolume)/fExpectedVolume, 0.1);
    iCount++;

    p_oTrees[80]->GetValue(p_oPop->GetFloatDataCode("Bole Vol", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fVolume);
    fExpectedVolume = 425.9024018;
    EXPECT_LT(fabs(fExpectedVolume - fVolume)/fExpectedVolume, 0.1);
    iCount++;

    p_oTrees[81]->GetValue(p_oPop->GetFloatDataCode("Bole Vol", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fVolume);
    fExpectedVolume = 226.9375528;
    EXPECT_LT(fabs(fExpectedVolume - fVolume)/fExpectedVolume, 0.1);
    iCount++;

    p_oTrees[82]->GetValue(p_oPop->GetFloatDataCode("Bole Vol", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fVolume);
    fExpectedVolume = 255.7925236;
    EXPECT_LT(fabs(fExpectedVolume - fVolume)/fExpectedVolume, 0.1);
    iCount++;

    p_oTrees[83]->GetValue(p_oPop->GetFloatDataCode("Bole Vol", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fVolume);
    fExpectedVolume = 286.3703443;
    EXPECT_LT(fabs(fExpectedVolume - fVolume)/fExpectedVolume, 0.1);
    iCount++;

    p_oTrees[84]->GetValue(p_oPop->GetFloatDataCode("Bole Vol", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fVolume);
    fExpectedVolume = 318.6706168;
    EXPECT_LT(fabs(fExpectedVolume - fVolume)/fExpectedVolume, 0.1);
    iCount++;

    p_oTrees[85]->GetValue(p_oPop->GetFloatDataCode("Bole Vol", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fVolume);
    fExpectedVolume = 352.6929594;
    EXPECT_LT(fabs(fExpectedVolume - fVolume)/fExpectedVolume, 0.1);
    iCount++;

    p_oTrees[86]->GetValue(p_oPop->GetFloatDataCode("Bole Vol", p_oTrees[iCount]->GetSpecies(), p_oTrees[iCount]->GetType()), &fVolume);
    fExpectedVolume = 388.4370054;
    EXPECT_LT(fabs(fExpectedVolume - fVolume)/fExpectedVolume, 0.1);

    delete[] p_oTrees;
    delete p_oSimManager;
  } catch (modelErr &e) {
    delete[] p_oTrees;
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}


////////////////////////////////////////////////////////////////////////////
// WriteBoleVolumeCalculatorXMLFile1()
////////////////////////////////////////////////////////////////////////////
const char* WriteBoleVolumeCalculatorXMLFile1() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  WriteBoleVolumeCalculatorCommonStuff(oOut);

  oOut << "<behaviorList>"
      << "<behavior>"
      << "<behaviorName>TreeBoleVolumeCalculator</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>1</listPosition>"
      << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_4\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_5\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_6\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_7\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_8\" type=\"Adult\"/>"
      << "</behavior>"
      << "</behaviorList>";

  oOut << "<TreeBoleVolumeCalculator1>"
      << "<an_boleB0>"
      << "<an_bb0Val species=\"Species_2\">0.11</an_bb0Val>"
      << "<an_bb0Val species=\"Species_3\">0.24</an_bb0Val>"
      << "<an_bb0Val species=\"Species_4\">0.19</an_bb0Val>"
      << "<an_bb0Val species=\"Species_5\">-0.19</an_bb0Val>"
      << "<an_bb0Val species=\"Species_6\">-0.45</an_bb0Val>"
      << "<an_bb0Val species=\"Species_7\">0.06</an_bb0Val>"
      << "<an_bb0Val species=\"Species_8\">-0.04</an_bb0Val>"
      << "</an_boleB0>"
      << "<an_boleB1>"
      << "<an_bb1Val species=\"Species_2\">-0.05977</an_bb1Val>"
      << "<an_bb1Val species=\"Species_3\">-0.05895</an_bb1Val>"
      << "<an_bb1Val species=\"Species_4\">-0.05904</an_bb1Val>"
      << "<an_bb1Val species=\"Species_5\">-0.01171</an_bb1Val>"
      << "<an_bb1Val species=\"Species_6\">-0.00523</an_bb1Val>"
      << "<an_bb1Val species=\"Species_7\">-0.02437</an_bb1Val>"
      << "<an_bb1Val species=\"Species_8\">-0.01783</an_bb1Val>"
      << "</an_boleB1>"
      << "<an_boleB2>"
      << "<an_bb2Val species=\"Species_2\">2.0498</an_bb2Val>"
      << "<an_bb2Val species=\"Species_3\">2.0362</an_bb2Val>"
      << "<an_bb2Val species=\"Species_4\">1.9935</an_bb2Val>"
      << "<an_bb2Val species=\"Species_5\">1.8949</an_bb2Val>"
      << "<an_bb2Val species=\"Species_6\">2.2323</an_bb2Val>"
      << "<an_bb2Val species=\"Species_7\">1.5419</an_bb2Val>"
      << "<an_bb2Val species=\"Species_8\">1.8109</an_bb2Val>"
      << "</an_boleB2>"
      << "<an_boleB3>"
      << "<an_bb3Val species=\"Species_2\">0.04965</an_bb3Val>"
      << "<an_bb3Val species=\"Species_3\">0.04947</an_bb3Val>"
      << "<an_bb3Val species=\"Species_4\">0.04981</an_bb3Val>"
      << "<an_bb3Val species=\"Species_5\">0.0134</an_bb3Val>"
      << "<an_bb3Val species=\"Species_6\">0.01338</an_bb3Val>"
      << "<an_bb3Val species=\"Species_7\">0.01299</an_bb3Val>"
      << "<an_bb3Val species=\"Species_8\">0.01358</an_bb3Val>"
      << "</an_boleB3>"
      << "<an_boleB4>"
      << "<an_bb4Val species=\"Species_2\">2.0198</an_bb4Val>"
      << "<an_bb4Val species=\"Species_3\">2.0172</an_bb4Val>"
      << "<an_bb4Val species=\"Species_4\">2.0027</an_bb4Val>"
      << "<an_bb4Val species=\"Species_5\">1.9928</an_bb4Val>"
      << "<an_bb4Val species=\"Species_6\">2.0093</an_bb4Val>"
      << "<an_bb4Val species=\"Species_7\">1.9885</an_bb4Val>"
      << "<an_bb4Val species=\"Species_8\">1.9905</an_bb4Val>"
      << "</an_boleB4>"
      << "<an_boleB5>"
      << "<an_bb5Val species=\"Species_2\">0.3468</an_bb5Val>"
      << "<an_bb5Val species=\"Species_3\">0.3366</an_bb5Val>"
      << "<an_bb5Val species=\"Species_4\">0.3242</an_bb5Val>"
      << "<an_bb5Val species=\"Species_5\">0.6471</an_bb5Val>"
      << "<an_bb5Val species=\"Species_6\">0.6384</an_bb5Val>"
      << "<an_bb5Val species=\"Species_7\">0.6453</an_bb5Val>"
      << "<an_bb5Val species=\"Species_8\">0.6553</an_bb5Val>"
      << "</an_boleB5>"
      << "<an_boleFormClasses>"
      << "<an_bfcVal species=\"Species_2\">80</an_bfcVal>"
      << "<an_bfcVal species=\"Species_3\">99</an_bfcVal>"
      << "<an_bfcVal species=\"Species_4\">75</an_bfcVal>"
      << "<an_bfcVal species=\"Species_5\">61</an_bfcVal>"
      << "<an_bfcVal species=\"Species_6\">85</an_bfcVal>"
      << "<an_bfcVal species=\"Species_7\">70</an_bfcVal>"
      << "<an_bfcVal species=\"Species_8\">90</an_bfcVal>"
      << "</an_boleFormClasses>"
      << "</TreeBoleVolumeCalculator1>"
      << "</paramFile>";

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteBoleVolumeCalculatorXMLErrorFile1()
////////////////////////////////////////////////////////////////////////////
const char* WriteBoleVolumeCalculatorXMLErrorFile1() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  WriteBoleVolumeCalculatorCommonStuff(oOut);

  oOut << "<behaviorList>"
      << "<behavior>"
      << "<behaviorName>TreeBoleVolumeCalculator</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>1</listPosition>"
      << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_4\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_5\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_6\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_7\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_8\" type=\"Adult\"/>"
      << "</behavior>"
      << "</behaviorList>";

  oOut << "<TreeBoleVolumeCalculator1>"
      << "<an_boleB0>"
      << "<an_bb0Val species=\"Species_2\">0.11</an_bb0Val>"
      << "<an_bb0Val species=\"Species_3\">0.24</an_bb0Val>"
      << "<an_bb0Val species=\"Species_4\">0.19</an_bb0Val>"
      << "<an_bb0Val species=\"Species_5\">-0.19</an_bb0Val>"
      << "<an_bb0Val species=\"Species_6\">-0.45</an_bb0Val>"
      << "<an_bb0Val species=\"Species_7\">0.06</an_bb0Val>"
      << "<an_bb0Val species=\"Species_8\">-0.04</an_bb0Val>"
      << "</an_boleB0>"
      << "<an_boleB1>"
      << "<an_bb1Val species=\"Species_2\">-0.05977</an_bb1Val>"
      << "<an_bb1Val species=\"Species_3\">-0.05895</an_bb1Val>"
      << "<an_bb1Val species=\"Species_4\">-0.05904</an_bb1Val>"
      << "<an_bb1Val species=\"Species_5\">-0.01171</an_bb1Val>"
      << "<an_bb1Val species=\"Species_6\">-0.00523</an_bb1Val>"
      << "<an_bb1Val species=\"Species_7\">-0.02437</an_bb1Val>"
      << "<an_bb1Val species=\"Species_8\">-0.01783</an_bb1Val>"
      << "</an_boleB1>"
      << "<an_boleB2>"
      << "<an_bb2Val species=\"Species_2\">2.0498</an_bb2Val>"
      << "<an_bb2Val species=\"Species_3\">2.0362</an_bb2Val>"
      << "<an_bb2Val species=\"Species_4\">1.9935</an_bb2Val>"
      << "<an_bb2Val species=\"Species_5\">1.8949</an_bb2Val>"
      << "<an_bb2Val species=\"Species_6\">2.2323</an_bb2Val>"
      << "<an_bb2Val species=\"Species_7\">1.5419</an_bb2Val>"
      << "<an_bb2Val species=\"Species_8\">1.8109</an_bb2Val>"
      << "</an_boleB2>"
      << "<an_boleB3>"
      << "<an_bb3Val species=\"Species_2\">0.04965</an_bb3Val>"
      << "<an_bb3Val species=\"Species_3\">0.04947</an_bb3Val>"
      << "<an_bb3Val species=\"Species_4\">0.04981</an_bb3Val>"
      << "<an_bb3Val species=\"Species_5\">0.0134</an_bb3Val>"
      << "<an_bb3Val species=\"Species_6\">0.01338</an_bb3Val>"
      << "<an_bb3Val species=\"Species_7\">0.01299</an_bb3Val>"
      << "<an_bb3Val species=\"Species_8\">0.01358</an_bb3Val>"
      << "</an_boleB3>"
      << "<an_boleB4>"
      << "<an_bb4Val species=\"Species_2\">2.0198</an_bb4Val>"
      << "<an_bb4Val species=\"Species_3\">2.0172</an_bb4Val>"
      << "<an_bb4Val species=\"Species_4\">2.0027</an_bb4Val>"
      << "<an_bb4Val species=\"Species_5\">1.9928</an_bb4Val>"
      << "<an_bb4Val species=\"Species_6\">2.0093</an_bb4Val>"
      << "<an_bb4Val species=\"Species_7\">1.9885</an_bb4Val>"
      << "<an_bb4Val species=\"Species_8\">1.9905</an_bb4Val>"
      << "</an_boleB4>"
      << "<an_boleB5>"
      << "<an_bb5Val species=\"Species_2\">0.3468</an_bb5Val>"
      << "<an_bb5Val species=\"Species_3\">0.3366</an_bb5Val>"
      << "<an_bb5Val species=\"Species_4\">0.3242</an_bb5Val>"
      << "<an_bb5Val species=\"Species_5\">0.6471</an_bb5Val>"
      << "<an_bb5Val species=\"Species_6\">0.6384</an_bb5Val>"
      << "<an_bb5Val species=\"Species_7\">0.6453</an_bb5Val>"
      << "<an_bb5Val species=\"Species_8\">0.6553</an_bb5Val>"
      << "</an_boleB5>"
      << "<an_boleFormClasses>"
      << "<an_bfcVal species=\"Species_2\">80</an_bfcVal>"
      << "<an_bfcVal species=\"Species_3\">49</an_bfcVal>"
      << "<an_bfcVal species=\"Species_4\">75</an_bfcVal>"
      << "<an_bfcVal species=\"Species_5\">61</an_bfcVal>"
      << "<an_bfcVal species=\"Species_6\">85</an_bfcVal>"
      << "<an_bfcVal species=\"Species_7\">70</an_bfcVal>"
      << "<an_bfcVal species=\"Species_8\">90</an_bfcVal>"
      << "</an_boleFormClasses>"
      << "</TreeBoleVolumeCalculator1>"
      << "</paramFile>";

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteBoleVolumeCalculatorXMLErrorFile2()
////////////////////////////////////////////////////////////////////////////
const char* WriteBoleVolumeCalculatorXMLErrorFile2() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  WriteBoleVolumeCalculatorCommonStuff(oOut);

  oOut << "<behaviorList>"
      << "<behavior>"
      << "<behaviorName>TreeBoleVolumeCalculator</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>1</listPosition>"
      << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_4\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_5\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_6\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_7\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_8\" type=\"Adult\"/>"
      << "</behavior>"
      << "</behaviorList>";

  oOut << "<TreeBoleVolumeCalculator1>"
      << "<an_boleB0>"
      << "<an_bb0Val species=\"Species_2\">0.11</an_bb0Val>"
      << "<an_bb0Val species=\"Species_3\">0.24</an_bb0Val>"
      << "<an_bb0Val species=\"Species_4\">0.19</an_bb0Val>"
      << "<an_bb0Val species=\"Species_5\">-0.19</an_bb0Val>"
      << "<an_bb0Val species=\"Species_6\">-0.45</an_bb0Val>"
      << "<an_bb0Val species=\"Species_7\">0.06</an_bb0Val>"
      << "<an_bb0Val species=\"Species_8\">-0.04</an_bb0Val>"
      << "</an_boleB0>"
      << "<an_boleB1>"
      << "<an_bb1Val species=\"Species_2\">-0.05977</an_bb1Val>"
      << "<an_bb1Val species=\"Species_3\">-0.05895</an_bb1Val>"
      << "<an_bb1Val species=\"Species_4\">-0.05904</an_bb1Val>"
      << "<an_bb1Val species=\"Species_5\">-0.01171</an_bb1Val>"
      << "<an_bb1Val species=\"Species_6\">-0.00523</an_bb1Val>"
      << "<an_bb1Val species=\"Species_7\">-0.02437</an_bb1Val>"
      << "<an_bb1Val species=\"Species_8\">-0.01783</an_bb1Val>"
      << "</an_boleB1>"
      << "<an_boleB2>"
      << "<an_bb2Val species=\"Species_2\">2.0498</an_bb2Val>"
      << "<an_bb2Val species=\"Species_3\">2.0362</an_bb2Val>"
      << "<an_bb2Val species=\"Species_4\">1.9935</an_bb2Val>"
      << "<an_bb2Val species=\"Species_5\">1.8949</an_bb2Val>"
      << "<an_bb2Val species=\"Species_6\">2.2323</an_bb2Val>"
      << "<an_bb2Val species=\"Species_7\">1.5419</an_bb2Val>"
      << "<an_bb2Val species=\"Species_8\">1.8109</an_bb2Val>"
      << "</an_boleB2>"
      << "<an_boleB3>"
      << "<an_bb3Val species=\"Species_2\">0.04965</an_bb3Val>"
      << "<an_bb3Val species=\"Species_3\">0.04947</an_bb3Val>"
      << "<an_bb3Val species=\"Species_4\">0.04981</an_bb3Val>"
      << "<an_bb3Val species=\"Species_5\">0.0134</an_bb3Val>"
      << "<an_bb3Val species=\"Species_6\">0.01338</an_bb3Val>"
      << "<an_bb3Val species=\"Species_7\">0.01299</an_bb3Val>"
      << "<an_bb3Val species=\"Species_8\">0.01358</an_bb3Val>"
      << "</an_boleB3>"
      << "<an_boleB4>"
      << "<an_bb4Val species=\"Species_2\">2.0198</an_bb4Val>"
      << "<an_bb4Val species=\"Species_3\">2.0172</an_bb4Val>"
      << "<an_bb4Val species=\"Species_4\">2.0027</an_bb4Val>"
      << "<an_bb4Val species=\"Species_5\">1.9928</an_bb4Val>"
      << "<an_bb4Val species=\"Species_6\">2.0093</an_bb4Val>"
      << "<an_bb4Val species=\"Species_7\">1.9885</an_bb4Val>"
      << "<an_bb4Val species=\"Species_8\">1.9905</an_bb4Val>"
      << "</an_boleB4>"
      << "<an_boleB5>"
      << "<an_bb5Val species=\"Species_2\">0.3468</an_bb5Val>"
      << "<an_bb5Val species=\"Species_3\">0.3366</an_bb5Val>"
      << "<an_bb5Val species=\"Species_4\">0.3242</an_bb5Val>"
      << "<an_bb5Val species=\"Species_5\">0.6471</an_bb5Val>"
      << "<an_bb5Val species=\"Species_6\">0.6384</an_bb5Val>"
      << "<an_bb5Val species=\"Species_7\">0.6453</an_bb5Val>"
      << "<an_bb5Val species=\"Species_8\">0.6553</an_bb5Val>"
      << "</an_boleB5>"
      << "<an_boleFormClasses>"
      << "<an_bfcVal species=\"Species_2\">80</an_bfcVal>"
      << "<an_bfcVal species=\"Species_3\">99</an_bfcVal>"
      << "<an_bfcVal species=\"Species_4\">75</an_bfcVal>"
      << "<an_bfcVal species=\"Species_5\">61</an_bfcVal>"
      << "<an_bfcVal species=\"Species_6\">85</an_bfcVal>"
      << "<an_bfcVal species=\"Species_7\">170</an_bfcVal>"
      << "<an_bfcVal species=\"Species_8\">90</an_bfcVal>"
      << "</an_boleFormClasses>"
      << "</TreeBoleVolumeCalculator1>"
      << "</paramFile>";

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteBoleVolumeCalculatorXMLErrorFile3()
////////////////////////////////////////////////////////////////////////////
const char* WriteBoleVolumeCalculatorXMLErrorFile3() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  WriteBoleVolumeCalculatorCommonStuff(oOut);

  oOut << "<behaviorList>"
      << "<behavior>"
      << "<behaviorName>TreeBoleVolumeCalculator</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>1</listPosition>"
      << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_3\" type=\"Seedling\"/>"
      << "<applyTo species=\"Species_4\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_5\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_6\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_7\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_8\" type=\"Adult\"/>"
      << "</behavior>"
      << "</behaviorList>";

  oOut << "<TreeBoleVolumeCalculator1>"
      << "<an_boleB0>"
      << "<an_bb0Val species=\"Species_2\">0.11</an_bb0Val>"
      << "<an_bb0Val species=\"Species_3\">0.24</an_bb0Val>"
      << "<an_bb0Val species=\"Species_4\">0.19</an_bb0Val>"
      << "<an_bb0Val species=\"Species_5\">-0.19</an_bb0Val>"
      << "<an_bb0Val species=\"Species_6\">-0.45</an_bb0Val>"
      << "<an_bb0Val species=\"Species_7\">0.06</an_bb0Val>"
      << "<an_bb0Val species=\"Species_8\">-0.04</an_bb0Val>"
      << "</an_boleB0>"
      << "<an_boleB1>"
      << "<an_bb1Val species=\"Species_2\">-0.05977</an_bb1Val>"
      << "<an_bb1Val species=\"Species_3\">-0.05895</an_bb1Val>"
      << "<an_bb1Val species=\"Species_4\">-0.05904</an_bb1Val>"
      << "<an_bb1Val species=\"Species_5\">-0.01171</an_bb1Val>"
      << "<an_bb1Val species=\"Species_6\">-0.00523</an_bb1Val>"
      << "<an_bb1Val species=\"Species_7\">-0.02437</an_bb1Val>"
      << "<an_bb1Val species=\"Species_8\">-0.01783</an_bb1Val>"
      << "</an_boleB1>"
      << "<an_boleB2>"
      << "<an_bb2Val species=\"Species_2\">2.0498</an_bb2Val>"
      << "<an_bb2Val species=\"Species_3\">2.0362</an_bb2Val>"
      << "<an_bb2Val species=\"Species_4\">1.9935</an_bb2Val>"
      << "<an_bb2Val species=\"Species_5\">1.8949</an_bb2Val>"
      << "<an_bb2Val species=\"Species_6\">2.2323</an_bb2Val>"
      << "<an_bb2Val species=\"Species_7\">1.5419</an_bb2Val>"
      << "<an_bb2Val species=\"Species_8\">1.8109</an_bb2Val>"
      << "</an_boleB2>"
      << "<an_boleB3>"
      << "<an_bb3Val species=\"Species_2\">0.04965</an_bb3Val>"
      << "<an_bb3Val species=\"Species_3\">0.04947</an_bb3Val>"
      << "<an_bb3Val species=\"Species_4\">0.04981</an_bb3Val>"
      << "<an_bb3Val species=\"Species_5\">0.0134</an_bb3Val>"
      << "<an_bb3Val species=\"Species_6\">0.01338</an_bb3Val>"
      << "<an_bb3Val species=\"Species_7\">0.01299</an_bb3Val>"
      << "<an_bb3Val species=\"Species_8\">0.01358</an_bb3Val>"
      << "</an_boleB3>"
      << "<an_boleB4>"
      << "<an_bb4Val species=\"Species_2\">2.0198</an_bb4Val>"
      << "<an_bb4Val species=\"Species_3\">2.0172</an_bb4Val>"
      << "<an_bb4Val species=\"Species_4\">2.0027</an_bb4Val>"
      << "<an_bb4Val species=\"Species_5\">1.9928</an_bb4Val>"
      << "<an_bb4Val species=\"Species_6\">2.0093</an_bb4Val>"
      << "<an_bb4Val species=\"Species_7\">1.9885</an_bb4Val>"
      << "<an_bb4Val species=\"Species_8\">1.9905</an_bb4Val>"
      << "</an_boleB4>"
      << "<an_boleB5>"
      << "<an_bb5Val species=\"Species_2\">0.3468</an_bb5Val>"
      << "<an_bb5Val species=\"Species_3\">0.3366</an_bb5Val>"
      << "<an_bb5Val species=\"Species_4\">0.3242</an_bb5Val>"
      << "<an_bb5Val species=\"Species_5\">0.6471</an_bb5Val>"
      << "<an_bb5Val species=\"Species_6\">0.6384</an_bb5Val>"
      << "<an_bb5Val species=\"Species_7\">0.6453</an_bb5Val>"
      << "<an_bb5Val species=\"Species_8\">0.6553</an_bb5Val>"
      << "</an_boleB5>"
      << "<an_boleFormClasses>"
      << "<an_bfcVal species=\"Species_2\">80</an_bfcVal>"
      << "<an_bfcVal species=\"Species_3\">99</an_bfcVal>"
      << "<an_bfcVal species=\"Species_4\">75</an_bfcVal>"
      << "<an_bfcVal species=\"Species_5\">61</an_bfcVal>"
      << "<an_bfcVal species=\"Species_6\">85</an_bfcVal>"
      << "<an_bfcVal species=\"Species_7\">70</an_bfcVal>"
      << "<an_bfcVal species=\"Species_8\">90</an_bfcVal>"
      << "</an_boleFormClasses>"
      << "</TreeBoleVolumeCalculator1>"
      << "</paramFile>";

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteBoleVolumeCalculatorCommonStuff()
/////////////////////////////////////////////////////////////////////////////
void WriteBoleVolumeCalculatorCommonStuff( std::fstream &oOut )
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
      << "<tr_species speciesName=\"Species_4\" />"
      << "<tr_species speciesName=\"Species_5\" />"
      << "<tr_species speciesName=\"Species_6\" />"
      << "<tr_species speciesName=\"Species_7\" />"
      << "<tr_species speciesName=\"Species_8\" />"
      << "</tr_speciesList>"
      << "<tr_seedDiam10Cm>0.1</tr_seedDiam10Cm>"
      << "<tr_minAdultDBH>"
      << "<tr_madVal species=\"Species_1\">0.0</tr_madVal>"
      << "<tr_madVal species=\"Species_2\">0.0</tr_madVal>"
      << "<tr_madVal species=\"Species_3\">0.0</tr_madVal>"
      << "<tr_madVal species=\"Species_4\">0.0</tr_madVal>"
      << "<tr_madVal species=\"Species_5\">0.0</tr_madVal>"
      << "<tr_madVal species=\"Species_6\">0.0</tr_madVal>"
      << "<tr_madVal species=\"Species_7\">0.0</tr_madVal>"
      << "<tr_madVal species=\"Species_8\">0.0</tr_madVal>"
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
      << "</tr_slopeOfHeight-Diam10>"
      << "<tr_slopeOfAsymHeight>"
      << "<tr_soahVal species=\"Species_1\">0.0299</tr_soahVal>"
      << "<tr_soahVal species=\"Species_2\">0.0241</tr_soahVal>"
      << "<tr_soahVal species=\"Species_3\">0.0263</tr_soahVal>"
      << "<tr_soahVal species=\"Species_4\">0.0263</tr_soahVal>"
      << "<tr_soahVal species=\"Species_5\">0.0263</tr_soahVal>"
      << "<tr_soahVal species=\"Species_6\">0.0263</tr_soahVal>"
      << "<tr_soahVal species=\"Species_7\">0.0263</tr_soahVal>"
      << "<tr_soahVal species=\"Species_8\">0.0263</tr_soahVal>"
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
      << "</tr_whatSaplingCrownHeightHeight>"
      << "</allometry>";
}
