//---------------------------------------------------------------------------
// TestFuncResponseSeedPredation.cpp
//---------------------------------------------------------------------------
#include "TestFuncResponseSeedPredation.h"
#include <gtest/gtest.h>
#include "SimManager.h"
#include "Grid.h"
#include "FuncResponseSeedPredation.h"
#include <fstream>
#include <math.h>


/////////////////////////////////////////////////////////////////////////////
// TestDensities()
// This verifies that densities are correctly written each timestep. If the
// predator densities are to be preserved, the values in the predator grid
// will be different after a second timestep; if they are not, it will be
// the same (assuming the seed grid input is the same).
// WriteFunResponseSeedPredationXMLFile6() will create the file with two
// timesteps where the densities are to be preserved;
// WriteFunResponseSeedPredationXMLFile7() is the same but densities are not to
// be preserved.
/////////////////////////////////////////////////////////////////////////////
TEST(FuncResponseSeedPredation, TestDensities) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    clGrid *p_oPredatorGrid, *p_oSeedsGrid;
    float fPredNum1, //number of predators after timestep 1
    fPredNum2, //number of predators after timestep 2
    fNumSeeds = 51200000.0;

    //Read in the file with preservation of predator densities
    p_oSimManager->ReadFile(WriteFunResponseSeedPredationXMLFile6());
    p_oPredatorGrid = p_oSimManager->GetGridObject("Seed Predators");
    p_oSeedsGrid = p_oSimManager->GetGridObject("Dispersed Seeds");
    //Set the seeds
    p_oSeedsGrid->SetValueOfCell(0, 0, p_oSeedsGrid->GetFloatDataCode("seeds_0"), fNumSeeds);
    //Run one timestep
    p_oSimManager->RunSim(1);
    //Get the number of predators
    p_oPredatorGrid->GetValueOfCell(0, 0, p_oPredatorGrid->GetFloatDataCode("num preds"), &fPredNum1);
    //Reset the seeds
    p_oSeedsGrid->SetValueOfCell(0, 0, p_oSeedsGrid->GetFloatDataCode("seeds_0"), fNumSeeds);
    //Run one timestep
    p_oSimManager->RunSim(1);
    //Get the number of predators
    p_oPredatorGrid->GetValueOfCell(0, 0, p_oPredatorGrid->GetFloatDataCode("num preds"), &fPredNum2);
    //Assert that they are at least 20% different
    EXPECT_GT(fabs(fPredNum1 - fPredNum2)/fPredNum1, 0.2);


    //Now repeat with no preservation of predator densities
    p_oSimManager->ReadFile(WriteFunResponseSeedPredationXMLFile7());
    p_oSeedsGrid = p_oSimManager->GetGridObject("Dispersed Seeds");
    p_oPredatorGrid = p_oSimManager->GetGridObject("Seed Predators");
    //Set the seeds
    p_oSeedsGrid->SetValueOfCell(0, 0, p_oSeedsGrid->GetFloatDataCode("seeds_0"), fNumSeeds);
    //Run one timestep
    p_oSimManager->RunSim(1);
    //Get the number of predators
    p_oPredatorGrid->GetValueOfCell(0, 0, p_oPredatorGrid->GetFloatDataCode("num preds"), &fPredNum1);
    //Reset the seeds
    p_oSeedsGrid->SetValueOfCell(0, 0, p_oSeedsGrid->GetFloatDataCode("seeds_0"), fNumSeeds);
    //Run one timestep
    p_oSimManager->RunSim(1);
    //Get the number of predators
    p_oPredatorGrid->GetValueOfCell(0, 0, p_oPredatorGrid->GetFloatDataCode("num preds"), &fPredNum2);
    //Assert that they are within 1%
    EXPECT_LT(fabs(fPredNum1 - fPredNum2)/fPredNum1, 0.01);
    delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

/////////////////////////////////////////////////////////////////////////////
// TestSeedOfftake1()
// This verifies that the correct number of seeds is left in the seed grid
// after the model runs. This is based on Wendy's spreadsheet - how many
// should be left if you subtract all the offtake from the original number.
/////////////////////////////////////////////////////////////////////////////
TEST(FuncResponseSeedPredation, TestSeedOfftake1) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    clGrid *p_oSeedsGrid;
    float fNumExpectedSeeds = 46724929.24,
        fSeed1Proportion = 0.25, fSeed2Proportion = 0.75,
        fNumActualSeeds,
        fSpecies1Seeds,
        fSpecies2Seeds,
        fSpecies3Seeds;

    p_oSimManager->ReadFile(WriteFunResponseSeedPredationXMLFile8());
    p_oSimManager->RunSim(1);

    p_oSeedsGrid = p_oSimManager->GetGridObject("Dispersed Seeds");
    p_oSeedsGrid->GetValueOfCell(0, 0, p_oSeedsGrid->GetFloatDataCode("seeds_0"), &fSpecies1Seeds);
    p_oSeedsGrid->GetValueOfCell(0, 0, p_oSeedsGrid->GetFloatDataCode("seeds_1"), &fSpecies2Seeds);
    p_oSeedsGrid->GetValueOfCell(0, 0, p_oSeedsGrid->GetFloatDataCode("seeds_2"), &fSpecies3Seeds);

    //Make sure the total is right - only species 1 and 2
    fNumActualSeeds = fSpecies1Seeds + fSpecies2Seeds;

    EXPECT_LT(fabs(fNumExpectedSeeds - fNumActualSeeds)/fNumActualSeeds, 0.01);

    //Make sure that the species 3 level is right
    EXPECT_LT(fabs(100000 - fSpecies3Seeds), 1);

    //Make sure the proportions of species 1 and species 2 are right
    EXPECT_LT(fabs((fNumExpectedSeeds * fSeed1Proportion) - fSpecies1Seeds)/fSpecies1Seeds, 0.01);
    EXPECT_LT(fabs((fNumExpectedSeeds * fSeed2Proportion) - fSpecies2Seeds)/fSpecies2Seeds, 0.01);
    delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}


/////////////////////////////////////////////////////////////////////////////
// TestSeedOfftake2()
// This tests the combination of regular and linked seed predation. This will
// use WriteFunResponseSeedPredationXMLOfftakeFile2().
/////////////////////////////////////////////////////////////////////////////
TEST(FuncResponseSeedPredation, TestSeedOfftake2) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    clGrid *p_oSeedsGrid;
    clBehaviorBase *p_oTemp;
    clFuncResponseSeedPredation *p_oPred;
    float fNumSp1ExpectedSeeds = 47623086.43,
        fNumSp2ExpectedSeeds = 51200000,
        fNumSp3ExpectedSeeds = 36000000,
        fExpectedOfftake = 0.077311856,
        fSpecies1Seeds,
        fSpecies2Seeds,
        fSpecies3Seeds,
        fOfftake;

    p_oSimManager->ReadFile(WriteFunResponseSeedPredationXMLOfftakeTestFile2());
    p_oSimManager->RunSim(1);

    //Test seed totals
    p_oSeedsGrid = p_oSimManager->GetGridObject("Dispersed Seeds");
    p_oSeedsGrid->GetValueOfCell(0, 0, p_oSeedsGrid->GetFloatDataCode("seeds_0"), &fSpecies1Seeds);
    p_oSeedsGrid->GetValueOfCell(0, 0, p_oSeedsGrid->GetFloatDataCode("seeds_1"), &fSpecies2Seeds);
    p_oSeedsGrid->GetValueOfCell(0, 0, p_oSeedsGrid->GetFloatDataCode("seeds_2"), &fSpecies3Seeds);

    EXPECT_LT(fabs(fNumSp1ExpectedSeeds - fSpecies1Seeds), 100);
    EXPECT_LT(fabs(fNumSp2ExpectedSeeds - fSpecies2Seeds), 2);
    EXPECT_LT(fabs(fNumSp3ExpectedSeeds - fSpecies3Seeds), 2);

    //Test seed offtake rate
    p_oTemp = p_oSimManager->GetBehaviorObject("LinkedFunctionalResponseSeedPredation");
    ASSERT_TRUE(NULL != p_oTemp);
    p_oPred = dynamic_cast<clFuncResponseSeedPredation*>(p_oTemp);

    fOfftake = p_oPred->GetOfftakeRate();
    EXPECT_LT(fabs(fExpectedOfftake - fOfftake)/fExpectedOfftake, 0.001);
    delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}


/////////////////////////////////////////////////////////////////////////////
// TestSeedOfftake3()
// This tests seed pooling across cells and species for linked seed predation.
// This will use WriteFunResponseSeedPredationXMLOfftakeFile3().
/////////////////////////////////////////////////////////////////////////////
TEST(FuncResponseSeedPredation, TestSeedOfftake3) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    clGrid *p_oSeedsGrid;
    clBehaviorBase *p_oTemp;
    clFuncResponseSeedPredation *p_oPred;
    float fNumSp1ExpectedSeeds = 0,
        fNumSp2ExpectedSeeds = 100000,
        fNumSp3ExpectedSeeds = 100000,
        fExpectedOfftake = 0.596678234,
        fSpecies1Seeds,
        fSpecies2Seeds,
        fSpecies3Seeds,
        fOfftake;
    int iX, iY, iNumXCells, iNumYCells;

    p_oSimManager->ReadFile(WriteFunResponseSeedPredationXMLOfftakeTestFile3());
    p_oSimManager->RunSim(1);

    //Test seed totals
    p_oSeedsGrid = p_oSimManager->GetGridObject("Dispersed Seeds");
    iNumXCells = p_oSeedsGrid->GetNumberXCells();
    iNumYCells = p_oSeedsGrid->GetNumberYCells();
    EXPECT_EQ(iNumXCells, 16);
    EXPECT_EQ(iNumYCells, 16);
    for (iX = 0; iX < iNumXCells; iX++) {
      for (iY = 0; iY < iNumYCells; iY++) {
        p_oSeedsGrid->GetValueOfCell(iX, iY, p_oSeedsGrid->GetFloatDataCode("seeds_0"), &fSpecies1Seeds);
        p_oSeedsGrid->GetValueOfCell(iX, iY, p_oSeedsGrid->GetFloatDataCode("seeds_1"), &fSpecies2Seeds);
        p_oSeedsGrid->GetValueOfCell(iX, iY, p_oSeedsGrid->GetFloatDataCode("seeds_2"), &fSpecies3Seeds);

        EXPECT_EQ(fNumSp1ExpectedSeeds, fSpecies1Seeds);
        EXPECT_EQ(fNumSp2ExpectedSeeds, fSpecies2Seeds);
        EXPECT_EQ(fNumSp3ExpectedSeeds, fSpecies3Seeds);
      }
    }

    //Test seed offtake rate
    p_oTemp = p_oSimManager->GetBehaviorObject("LinkedFunctionalResponseSeedPredation");
    ASSERT_TRUE(NULL != p_oTemp);
    p_oPred = dynamic_cast<clFuncResponseSeedPredation*>(p_oTemp);

    fOfftake = p_oPred->GetOfftakeRate();
    EXPECT_LT(fabs(fExpectedOfftake - fOfftake)/fExpectedOfftake, 0.01);

    //Eliminate all seeds, run another timestep, and verify an updated offtake
    //rate
    fSpecies1Seeds = 0;
    for (iX = 0; iX < iNumXCells; iX++) {
      for (iY = 0; iY < iNumYCells; iY++) {
        p_oSeedsGrid->SetValueOfCell(iX, iY, p_oSeedsGrid->GetFloatDataCode("seeds_0"), fSpecies1Seeds);
        p_oSeedsGrid->SetValueOfCell(iX, iY, p_oSeedsGrid->GetFloatDataCode("seeds_1"), fSpecies1Seeds);
        p_oSeedsGrid->SetValueOfCell(iX, iY, p_oSeedsGrid->GetFloatDataCode("seeds_2"), fSpecies1Seeds);
      }
    }
    p_oSimManager->RunSim(1);

    fOfftake = p_oPred->GetOfftakeRate();
    EXPECT_LT(fOfftake >= 0 && fOfftake, 0.00001);
    delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

/////////////////////////////////////////////////////////////////////////////
// TestSeedOfftake4()
// This tests species- and season-specific parameters. This will use
// WriteFunResponseSeedPredationXMLOfftakeFile4().
/////////////////////////////////////////////////////////////////////////////
TEST(FuncResponseSeedPredation, TestSeedOfftake4) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    clGrid *p_oSeedsGrid;
    float fNumSp1ExpectedSeeds = 24901578.21,
        fNumSp2ExpectedSeeds = 33799935.73,
        fNumSp3ExpectedSeeds = 36000000,
        fNumSp4ExpectedSeeds = 36778314.44,
        fSpecies1Seeds,
        fSpecies2Seeds,
        fSpecies3Seeds,
        fSpecies4Seeds;

    p_oSimManager->ReadFile(WriteFunResponseSeedPredationXMLOfftakeTestFile4());
    p_oSimManager->RunSim(1);

    //Test seed totals
    p_oSeedsGrid = p_oSimManager->GetGridObject("Dispersed Seeds");
    p_oSeedsGrid->GetValueOfCell(0, 0, p_oSeedsGrid->GetFloatDataCode("seeds_0"), &fSpecies1Seeds);
    p_oSeedsGrid->GetValueOfCell(0, 0, p_oSeedsGrid->GetFloatDataCode("seeds_1"), &fSpecies2Seeds);
    p_oSeedsGrid->GetValueOfCell(0, 0, p_oSeedsGrid->GetFloatDataCode("seeds_2"), &fSpecies3Seeds);
    p_oSeedsGrid->GetValueOfCell(0, 0, p_oSeedsGrid->GetFloatDataCode("seeds_3"), &fSpecies4Seeds);

    EXPECT_LT(fabs(fNumSp1ExpectedSeeds - fSpecies1Seeds)/fNumSp1ExpectedSeeds, 0.001);
    EXPECT_LT(fabs(fNumSp2ExpectedSeeds - fSpecies2Seeds)/fNumSp2ExpectedSeeds, 0.001);
    EXPECT_LT(fabs(fNumSp3ExpectedSeeds - fSpecies3Seeds), 2);
    EXPECT_LT(fabs(fNumSp4ExpectedSeeds - fSpecies4Seeds)/fNumSp4ExpectedSeeds, 0.001);
    delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

/////////////////////////////////////////////////////////////////////////////
// TestSetup1()
/////////////////////////////////////////////////////////////////////////////
TEST(FuncResponseSeedPredation, TestSetup1) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    p_oSimManager->ReadFile(WriteFunResponseSeedPredationXMLFile2());

    clGrid *p_oPredatorGrid = p_oSimManager->GetGridObject("Seed Predators");

    //Make sure it has default resolution
    EXPECT_LT(fabs(8 - p_oPredatorGrid->GetLengthXCells()), 0.001);
    EXPECT_LT(fabs(8 - p_oPredatorGrid->GetLengthYCells()), 0.001);

    //Make sure the grid cells have the right value - should all be 30
    float fExpected = 30, fActual;
    int iNumX = p_oPredatorGrid->GetNumberXCells(),
        iNumY = p_oPredatorGrid->GetNumberYCells(),
        iNumCode = p_oPredatorGrid->GetFloatDataCode("num preds"),
        iX, iY;

    for (iX = 0; iX < iNumX; iX++) {
      for (iY = 0; iY < iNumY; iY++) {
        p_oPredatorGrid->GetValueOfCell(iX, iY, iNumCode, &fActual);
        EXPECT_LT(fabs(fActual - fExpected), 0.001);
      }
    }
    delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}


/////////////////////////////////////////////////////////////////////////////
// TestSetup2()
/////////////////////////////////////////////////////////////////////////////
TEST(FuncResponseSeedPredation, TestSetup2) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    p_oSimManager->ReadFile(WriteFunResponseSeedPredationXMLFile3());

    clGrid *p_oPredatorGrid = p_oSimManager->GetGridObject("Seed Predators");

    //Make sure it has default resolution
    EXPECT_LT(fabs(8 - p_oPredatorGrid->GetLengthXCells()), 0.001);
    EXPECT_LT(fabs(8 - p_oPredatorGrid->GetLengthYCells()), 0.001);

    //Make sure the grid cells have the right value - should all be 30
    float fExpected = 0, fActual;
    int iNumX = p_oPredatorGrid->GetNumberXCells(),
        iNumY = p_oPredatorGrid->GetNumberYCells(),
        iNumCode = p_oPredatorGrid->GetFloatDataCode("num preds"),
        iX, iY;

    for (iX = 0; iX < iNumX; iX++) {
      for (iY = 0; iY < iNumY; iY++) {
        p_oPredatorGrid->GetValueOfCell(iX, iY, iNumCode, &fActual);
        EXPECT_LT(fabs(fActual - fExpected), 0.001);
      }
    }
    delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}


/////////////////////////////////////////////////////////////////////////////
// TestSetup3()
/////////////////////////////////////////////////////////////////////////////
TEST(FuncResponseSeedPredation, TestSetup3) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    p_oSimManager->ReadFile(WriteFunResponseSeedPredationXMLFile4());

    clGrid *p_oPredatorGrid = p_oSimManager->GetGridObject("Seed Predators");

    //Make sure it has default resolution
    EXPECT_LT(fabs(2 - p_oPredatorGrid->GetLengthXCells()), 0.001);
    EXPECT_LT(fabs(4 - p_oPredatorGrid->GetLengthYCells()), 0.001);

    //Make sure the grid cells have the right value - should all be 30
    float fExpected, fActual;
    int iNumX = p_oPredatorGrid->GetNumberXCells(),
        iNumY = p_oPredatorGrid->GetNumberYCells(),
        iNumCode = p_oPredatorGrid->GetFloatDataCode("num preds"),
        iX, iY;

    for (iX = 0; iX < iNumX; iX++) {
      for (iY = 0; iY < iNumY; iY++) {
        fExpected = iX + iY;
        p_oPredatorGrid->GetValueOfCell(iX, iY, iNumCode, &fActual);
        EXPECT_LT(fabs(fActual - fExpected), 0.001);
      }
    }
    delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}


/////////////////////////////////////////////////////////////////////////////
// TestErrorProcessing()
/////////////////////////////////////////////////////////////////////////////
TEST(FuncResponseSeedPredation, TestErrorProcessing)
{
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try
  {
    p_oSimManager->ReadFile(WriteFunResponseSeedPredationXMLErrorFile1());
    FAIL() << "TestFuncResponseSeedPredation error processing didn't catch error for WriteFunResponseSeedPredationXMLErrorFile1.";
  }
  catch (modelErr& err)
  {
    if (err.sFunction.compare("clFuncResponseSeedPredation::GetParameterFileData") != 0)
    {
      FAIL() << "TestFuncResponseSeedPredation error processing caught wrong error for WriteFunResponseSeedPredationXMLErrorFile1.";
    }
    ;
  }

  try
  {
    p_oSimManager->ReadFile(WriteFunResponseSeedPredationXMLErrorFile2());
    FAIL() << "TestFuncResponseSeedPredation error processing didn't catch error for WriteFunResponseSeedPredationXMLErrorFile2.";
  }
  catch (modelErr& err)
  {
    if (err.sFunction.compare("clFuncResponseSeedPredation::GetData") != 0)
    {
      FAIL() << "TestFuncResponseSeedPredation error processing caught wrong error for WriteFunResponseSeedPredationXMLErrorFile2.";
    }
    ;
  }

  try
  {
    p_oSimManager->ReadFile(WriteFunResponseSeedPredationXMLErrorFile3());
    FAIL() << "TestFuncResponseSeedPredation error processing didn't catch error for WriteFunResponseSeedPredationXMLErrorFile3.";
  }
  catch (modelErr& err)
  {
    if (err.sFunction.compare("clFuncResponseSeedPredation::GetData") != 0)
    {
      FAIL() << "TestFuncResponseSeedPredation error processing caught wrong error for WriteFunResponseSeedPredationXMLErrorFile3.";
    }
    ;
  }

  try
  {
    p_oSimManager->ReadFile(WriteFunResponseSeedPredationXMLErrorFile4());
    FAIL() << "TestFuncResponseSeedPredation error processing didn't catch error for WriteFunResponseSeedPredationXMLErrorFile4.";
  }
  catch (modelErr& err)
  {
    if (err.sFunction.compare("clFuncResponseSeedPredation::GetParameterFileData") != 0)
    {
      FAIL() << "TestFuncResponseSeedPredation error processing caught wrong error for WriteFunResponseSeedPredationXMLErrorFile4.";
    }
    ;
  }

  try
  {
    p_oSimManager->ReadFile(WriteFunResponseSeedPredationXMLErrorFile5());
    FAIL() << "TestFuncResponseSeedPredation error processing didn't catch error for WriteFunResponseSeedPredationXMLErrorFile5.";
  }
  catch (modelErr& err)
  {
    if (err.sFunction.compare("clFuncResponseSeedPredation::GetParameterFileData") != 0)
    {
      FAIL() << "TestFuncResponseSeedPredation error processing caught wrong error for WriteFunResponseSeedPredationXMLErrorFile5.";
    }
    ;
  }

  try
  {
    p_oSimManager->ReadFile(WriteFunResponseSeedPredationXMLErrorFile6());
    FAIL() << "TestFuncResponseSeedPredation error processing didn't catch error for WriteFunResponseSeedPredationXMLErrorFile6.";
  }
  catch (modelErr& err)
  {
    if (err.sFunction.compare("clFuncResponseSeedPredation::GetData") != 0)
    {
      FAIL() << "TestFuncResponseSeedPredation error processing caught wrong error for WriteFunResponseSeedPredationXMLErrorFile6.";
    }
    ;
  }

  try
  {
    p_oSimManager->ReadFile(WriteFunResponseSeedPredationXMLErrorFile7());
    FAIL() << "TestFuncResponseSeedPredation error processing didn't catch error for WriteFunResponseSeedPredationXMLErrorFile7.";
  }
  catch (modelErr& err)
  {
    if (err.sFunction.compare("clFuncResponseSeedPredation::GetData") != 0)
    {
      FAIL() << "TestFuncResponseSeedPredation error processing caught wrong error for WriteFunResponseSeedPredationXMLErrorFile7.";
    }
    ;
  }

  try
  {
    p_oSimManager->ReadFile(WriteFunResponseSeedPredationXMLErrorFile8());
    FAIL() << "TestFuncResponseSeedPredation error processing didn't catch error for WriteFunResponseSeedPredationXMLErrorFile8.";
  }
  catch (modelErr& err)
  {
    if (err.sFunction.compare("clFuncResponseSeedPredation::GetParameterFileData") != 0)
    {
      FAIL() << "TestFuncResponseSeedPredation error processing caught wrong error for WriteFunResponseSeedPredationXMLErrorFile8.";
    }
    ;
  }

  try
  {
    p_oSimManager->ReadFile(WriteFunResponseSeedPredationXMLErrorFile9());
    FAIL() << "TestFuncResponseSeedPredation error processing didn't catch error for WriteFunResponseSeedPredationXMLErrorFile9.";
  }
  catch (modelErr& err)
  {
    if (err.sFunction.compare("clFuncResponseSeedPredation::GetParameterFileData") != 0)
    {
      FAIL() << "TestFuncResponseSeedPredation error processing caught wrong error for WriteFunResponseSeedPredationXMLErrorFile9.";
    }
    ;
  }

  try
  {
    p_oSimManager->ReadFile(WriteFunResponseSeedPredationXMLErrorFile10());
    FAIL() << "TestFuncResponseSeedPredation error processing didn't catch error for WriteFunResponseSeedPredationXMLErrorFile10.";
  }
  catch (modelErr& err)
  {
    if (err.sFunction.compare("clFuncResponseSeedPredation::GetParameterFileData") != 0)
    {
      FAIL() << "TestFuncResponseSeedPredation error processing caught wrong error for WriteFunResponseSeedPredationXMLErrorFile10.";
    }
    ;
  }

  try
  {
    p_oSimManager->ReadFile(WriteFunResponseSeedPredationXMLErrorFile11());
    FAIL() << "TestFuncResponseSeedPredation error processing didn't catch error for WriteFunResponseSeedPredationXMLErrorFile11.";
  }
  catch (modelErr& err)
  {
    if (err.sFunction.compare("clFuncResponseSeedPredation::GetParameterFileData") != 0)
    {
      FAIL() << "TestFuncResponseSeedPredation error processing caught wrong error for WriteFunResponseSeedPredationXMLErrorFile11.";
    }
    ;
  }
  delete p_oSimManager;
}


/////////////////////////////////////////////////////////////////////////////
// TestSeedPredationNormal()
/////////////////////////////////////////////////////////////////////////////
TEST(FuncResponseSeedPredation, TestSeedPredationNormal)
{
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    clGrid *p_oSeedsGrid;
    float fNumExpectedSeeds = 46724931.74,
        fNumActualSeeds;
    p_oSimManager->ReadFile(WriteFunResponseSeedPredationXMLFile1());
    p_oSimManager->RunSim(1);

    p_oSeedsGrid = p_oSimManager->GetGridObject("Dispersed Seeds");
    p_oSeedsGrid->GetValueOfCell(0, 0, p_oSeedsGrid->GetFloatDataCode("seeds_0"), &fNumActualSeeds);

    EXPECT_LT(fabs(fNumExpectedSeeds - fNumActualSeeds), 100);
    delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}


/////////////////////////////////////////////////////////////////////////////
// WriteFunResponseSeedPredationXMLFile1()
/////////////////////////////////////////////////////////////////////////////
const char* WriteFunResponseSeedPredationXMLFile1() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06010101\">"
       << "<plot>"
       << "<timesteps>1</timesteps>"
       << "<yearsPerTimestep>1</yearsPerTimestep>"
       << "<randomSeed>1</randomSeed>"
       << "<plot_lenX>160.0</plot_lenX>"
       << "<plot_lenY>160.0</plot_lenY>"
       << "<plot_latitude>55.37</plot_latitude>"
       << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
       << "<plot_temp_C>12.88171785</plot_temp_C>"
       << "</plot>"
       << "<trees>"
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
       << "<tr_slopeOfAsymHeight>"
       << "<tr_soahVal species=\"Species_1\">0.0299</tr_soahVal>"
       << "</tr_slopeOfAsymHeight>"
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
       << "</allometry>"
       << "<grid gridName=\"Dispersed Seeds\">"
       << "<ma_floatCodes>"
       << "<ma_floatCode label=\"seeds_0\">0</ma_floatCode>"
       << "</ma_floatCodes>"
       << "<ma_intCodes>"
       << "<ma_intCode label=\"count\">0</ma_intCode>"
       << "</ma_intCodes>"
       << "<ma_boolCodes>"
       << "<ma_boolCode label=\"Is Gap\">0</ma_boolCode>"
       << "</ma_boolCodes>"


       << "<ma_lengthXCells>160</ma_lengthXCells>"
       << "<ma_lengthYCells>160</ma_lengthYCells>"
       << "<ma_v x=\"0\" y=\"0\">"
       << "<fl c=\"0\">51200000</fl>"
       << "</ma_v>";

  oOut << "</grid>"
       << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>FunctionalResponseSeedPredation</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Seed\"/>"
       << "</behavior>"
       << "</behaviorList>"
       << "<FunctionalResponseSeedPredation1>"
       << "<pr_funcRespPredatorInitialDensity>0.00046875</pr_funcRespPredatorInitialDensity>"
       << "<pr_funcRespMaxInstDeclineRate1>-0.050622442</pr_funcRespMaxInstDeclineRate1>"
       << "<pr_funcRespMaxInstDeclineRate2>-0.050622442</pr_funcRespMaxInstDeclineRate2>"
       << "<pr_funcRespDemographicEfficiency1>0.000154258</pr_funcRespDemographicEfficiency1>"
       << "<pr_funcRespDemographicEfficiency2>0.000154258</pr_funcRespDemographicEfficiency2>"
       << "<pr_funcRespDensityDependentCoefficient1>-0.000718667</pr_funcRespDensityDependentCoefficient1>"
       << "<pr_funcRespDensityDependentCoefficient2>-0.000718667</pr_funcRespDensityDependentCoefficient2>"
       << "<pr_funcRespMaxIntakeRate>"
       << "<pr_frmirVal species=\"Species_1\">1042.2</pr_frmirVal>"
       << "</pr_funcRespMaxIntakeRate>"
       << "<pr_funcRespForagingEfficiency>"
       << "<pr_frfeVal species=\"Species_1\">0.001389</pr_frfeVal>"
       << "</pr_funcRespForagingEfficiency>"
       << "<pr_funcRespNumWeeksSeedFall>12</pr_funcRespNumWeeksSeedFall>"
       << "<pr_funcRespWeekSeason2Starts>52</pr_funcRespWeekSeason2Starts>"
       << "<pr_funcRespNumWeeksToModel>52</pr_funcRespNumWeeksToModel>"
       << "<pr_funcRespWeekGerminationStarts>32</pr_funcRespWeekGerminationStarts>"
       << "<pr_funcRespPreservePredatorDensities>0</pr_funcRespPreservePredatorDensities>"
       << "<pr_funcRespProportionGerminating>0.35</pr_funcRespProportionGerminating>"
       << "<pr_funcRespOutputFilename>TestSeeds.txt</pr_funcRespOutputFilename>"
       << "</FunctionalResponseSeedPredation1>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}


/////////////////////////////////////////////////////////////////////////////
// WriteFunResponseSeedPredationXMLFile2()
/////////////////////////////////////////////////////////////////////////////
const char* WriteFunResponseSeedPredationXMLFile2()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>" << "<paramFile fileCode=\"06010101\">" << "<plot>"
       << "<timesteps>1</timesteps>"
       << "<yearsPerTimestep>1</yearsPerTimestep>"
       << "<randomSeed>1</randomSeed>"
       << "<plot_lenX>160.0</plot_lenX>"
       << "<plot_lenY>160.0</plot_lenY>"
       << "<plot_latitude>55.37</plot_latitude>"
       << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
       << "<plot_temp_C>12.88171785</plot_temp_C>"
       << "</plot>"
       << "<trees>"
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
       << "<tr_slopeOfAsymHeight>"
       << "<tr_soahVal species=\"Species_1\">0.0299</tr_soahVal>"
       << "</tr_slopeOfAsymHeight>"
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
       << "</allometry>"
       << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>NonSpatialDisperse</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>FunctionalResponseSeedPredation</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>2</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Seed\"/>"
       << "</behavior>"
       << "</behaviorList>"
       << "<NonSpatialDisperse1>"
       << "<di_minDbhForReproduction>"
       << "<di_mdfrVal species=\"Species_1\">15.0</di_mdfrVal>"
       << "</di_minDbhForReproduction>"
       << "<di_nonSpatialSlopeOfLambda>"
       << "<di_nssolVal species=\"Species_1\">0</di_nssolVal>"
       << "</di_nonSpatialSlopeOfLambda>"
       << "<di_nonSpatialInterceptOfLambda>"
       << "<di_nsiolVal species=\"Species_1\">0.3</di_nsiolVal>"
       << "</di_nonSpatialInterceptOfLambda>"
       << "</NonSpatialDisperse1>"
       << "<GeneralDisperse>"
       << "<di_seedDistributionMethod>0</di_seedDistributionMethod>"
       << "</GeneralDisperse>"
       << "<FunctionalResponseSeedPredation2>"
       << "<pr_funcRespPredatorInitialDensity>0.46875</pr_funcRespPredatorInitialDensity>"
       << "<pr_funcRespMaxInstDeclineRate1>-0.050622442</pr_funcRespMaxInstDeclineRate1>"
       << "<pr_funcRespMaxInstDeclineRate2>-0.050622442</pr_funcRespMaxInstDeclineRate2>"
       << "<pr_funcRespDemographicEfficiency1>0.000154258</pr_funcRespDemographicEfficiency1>"
       << "<pr_funcRespDemographicEfficiency2>0.000154258</pr_funcRespDemographicEfficiency2>"
       << "<pr_funcRespDensityDependentCoefficient1>-0.000718667</pr_funcRespDensityDependentCoefficient1>"
       << "<pr_funcRespDensityDependentCoefficient2>-0.000718667</pr_funcRespDensityDependentCoefficient2>"
       << "<pr_funcRespMaxIntakeRate>"
       << "<pr_frmirVal species=\"Species_1\">7295.4</pr_frmirVal>"
       << "</pr_funcRespMaxIntakeRate>"
       << "<pr_funcRespForagingEfficiency>"
       << "<pr_frfeVal species=\"Species_1\">0.001389</pr_frfeVal>"
       << "</pr_funcRespForagingEfficiency>"
       << "<pr_funcRespWeekSeason2Starts>1</pr_funcRespWeekSeason2Starts>"
       << "<pr_funcRespNumWeeksSeedFall>12</pr_funcRespNumWeeksSeedFall>"
       << "<pr_funcRespNumWeeksToModel>52</pr_funcRespNumWeeksToModel>"
       << "<pr_funcRespWeekGerminationStarts>32</pr_funcRespWeekGerminationStarts>"
       << "<pr_funcRespPreservePredatorDensities>1</pr_funcRespPreservePredatorDensities>"
       << "<pr_funcRespProportionGerminating>0.35</pr_funcRespProportionGerminating>"
       << "</FunctionalResponseSeedPredation2>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}


/////////////////////////////////////////////////////////////////////////////
// WriteFunResponseSeedPredationXMLFile3()
/////////////////////////////////////////////////////////////////////////////
const char* WriteFunResponseSeedPredationXMLFile3()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06010101\">"
       << "<plot>"
       << "<timesteps>1</timesteps>"
       << "<yearsPerTimestep>1</yearsPerTimestep>"
       << "<randomSeed>1</randomSeed>"
       << "<plot_lenX>160.0</plot_lenX>"
       << "<plot_lenY>160.0</plot_lenY>"
       << "<plot_latitude>55.37</plot_latitude>"
       << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
       << "<plot_temp_C>12.88171785</plot_temp_C>"
       << "</plot>"
       << "<trees>"
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
       << "<tr_slopeOfAsymHeight>"
       << "<tr_soahVal species=\"Species_1\">0.0299</tr_soahVal>"
       << "</tr_slopeOfAsymHeight>"
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
       << "</allometry>"
       << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>NonSpatialDisperse</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>FunctionalResponseSeedPredation</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>2</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Seed\"/>"
       << "</behavior>"
       << "</behaviorList>"
       << "<NonSpatialDisperse1>"
       << "<di_minDbhForReproduction>"
       << "<di_mdfrVal species=\"Species_1\">15.0</di_mdfrVal>"
       << "</di_minDbhForReproduction>"
       << "<di_nonSpatialSlopeOfLambda>"
       << "<di_nssolVal species=\"Species_1\">0</di_nssolVal>"
       << "</di_nonSpatialSlopeOfLambda>"
       << "<di_nonSpatialInterceptOfLambda>"
       << "<di_nsiolVal species=\"Species_1\">0.3</di_nsiolVal>"
       << "</di_nonSpatialInterceptOfLambda>"
       << "</NonSpatialDisperse1>"
       << "<GeneralDisperse>"
       << "<di_seedDistributionMethod>0</di_seedDistributionMethod>"
       << "</GeneralDisperse>"
       << "<FunctionalResponseSeedPredation2>"
       << "<pr_funcRespPredatorInitialDensity>0.00046875</pr_funcRespPredatorInitialDensity>"
       << "<pr_funcRespMaxInstDeclineRate1>-0.050622442</pr_funcRespMaxInstDeclineRate1>"
       << "<pr_funcRespMaxInstDeclineRate2>-0.050622442</pr_funcRespMaxInstDeclineRate2>"
       << "<pr_funcRespDemographicEfficiency1>0.000154258</pr_funcRespDemographicEfficiency1>"
       << "<pr_funcRespDemographicEfficiency2>0.000154258</pr_funcRespDemographicEfficiency2>"
       << "<pr_funcRespDensityDependentCoefficient1>-0.000718667</pr_funcRespDensityDependentCoefficient1>"
       << "<pr_funcRespDensityDependentCoefficient2>-0.000718667</pr_funcRespDensityDependentCoefficient2>"
       << "<pr_funcRespMaxIntakeRate>"
       << "<pr_frmirVal species=\"Species_1\">7295.4</pr_frmirVal>"
       << "</pr_funcRespMaxIntakeRate>"
       << "<pr_funcRespForagingEfficiency>"
       << "<pr_frfeVal species=\"Species_1\">0.001389</pr_frfeVal>"
       << "</pr_funcRespForagingEfficiency>"
       << "<pr_funcRespWeekSeason2Starts>12</pr_funcRespWeekSeason2Starts>"
       << "<pr_funcRespNumWeeksSeedFall>12</pr_funcRespNumWeeksSeedFall>"
       << "<pr_funcRespNumWeeksToModel>52</pr_funcRespNumWeeksToModel>"
       << "<pr_funcRespWeekGerminationStarts>32</pr_funcRespWeekGerminationStarts>"
       << "<pr_funcRespPreservePredatorDensities>0</pr_funcRespPreservePredatorDensities>"
       << "<pr_funcRespProportionGerminating>0.35</pr_funcRespProportionGerminating>"
       << "</FunctionalResponseSeedPredation2>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}


/////////////////////////////////////////////////////////////////////////////
// WriteFunResponseSeedPredationXMLFile4()
/////////////////////////////////////////////////////////////////////////////
const char* WriteFunResponseSeedPredationXMLFile4()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  int iX, iY;
  oOut.open(cFileString, ios::out | ios::trunc);

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06010101\">"
       << "<plot>"
       << "<timesteps>1</timesteps>"
       << "<yearsPerTimestep>1</yearsPerTimestep>"
       << "<randomSeed>1</randomSeed>"
       << "<plot_lenX>160.0</plot_lenX>"
       << "<plot_lenY>160.0</plot_lenY>"
       << "<plot_latitude>55.37</plot_latitude>"
       << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
       << "<plot_temp_C>12.88171785</plot_temp_C>"
       << "</plot>"
       << "<trees>"
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
       << "<tr_slopeOfAsymHeight>"
       << "<tr_soahVal species=\"Species_1\">0.0299</tr_soahVal>"
       << "</tr_slopeOfAsymHeight>"
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
       << "</allometry>"
       << "<grid gridName=\"Dispersed Seeds\">"
       << "<ma_floatCodes>"
       << "<ma_floatCode label=\"seeds_0\">0</ma_floatCode>"
       << "</ma_floatCodes>"
       << "<ma_intCodes>"
       << "<ma_intCode label=\"count\">0</ma_intCode>"
       << "</ma_intCodes>"
       << "<ma_boolCodes>"
       << "<ma_boolCode label=\"Is Gap\">0</ma_boolCode>"
       << "</ma_boolCodes>"
       << "<ma_lengthXCells>2</ma_lengthXCells>"
       << "<ma_lengthYCells>4</ma_lengthYCells>"
       << "</grid>"
       << "<grid gridName=\"Seed Predators\">"
       << "<ma_floatCodes>"
       << "<ma_floatCode label=\"num preds\">0</ma_floatCode>"
       << "</ma_floatCodes>"
       << "<ma_lengthXCells>2</ma_lengthXCells>"
       << "<ma_lengthYCells>4</ma_lengthYCells>";
       for (iX = 0; iX < 80; iX++)
       {
         for (iY = 0; iY < 40; iY++)
         {
           oOut << "<ma_v x=\"" << iX << "\" y=\"" << iY << "\">"
           << "<fl c=\"0\">" << (float)(iX + iY) << "</fl>"
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
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>FunctionalResponseSeedPredation</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>2</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Seed\"/>"
       << "</behavior>"
       << "</behaviorList>"
       << "<NonSpatialDisperse1>"
       << "<di_minDbhForReproduction>"
       << "<di_mdfrVal species=\"Species_1\">15.0</di_mdfrVal>"
       << "</di_minDbhForReproduction>"
       << "<di_nonSpatialSlopeOfLambda>"
       << "<di_nssolVal species=\"Species_1\">0</di_nssolVal>"
       << "</di_nonSpatialSlopeOfLambda>"
       << "<di_nonSpatialInterceptOfLambda>"
       << "<di_nsiolVal species=\"Species_1\">0.3</di_nsiolVal>"
       << "</di_nonSpatialInterceptOfLambda>"
       << "</NonSpatialDisperse1>"
       << "<GeneralDisperse>"
       << "<di_seedDistributionMethod>0</di_seedDistributionMethod>"
       << "</GeneralDisperse>"
       << "<FunctionalResponseSeedPredation2>"
       << "<pr_funcRespPredatorInitialDensity>0.00046875</pr_funcRespPredatorInitialDensity>"
       << "<pr_funcRespMaxInstDeclineRate1>-0.050622442</pr_funcRespMaxInstDeclineRate1>"
       << "<pr_funcRespMaxInstDeclineRate2>-0.050622442</pr_funcRespMaxInstDeclineRate2>"
       << "<pr_funcRespDemographicEfficiency1>0.000154258</pr_funcRespDemographicEfficiency1>"
       << "<pr_funcRespDemographicEfficiency2>0.000154258</pr_funcRespDemographicEfficiency2>"
       << "<pr_funcRespDensityDependentCoefficient1>-0.000718667</pr_funcRespDensityDependentCoefficient1>"
       << "<pr_funcRespDensityDependentCoefficient2>-0.000718667</pr_funcRespDensityDependentCoefficient2>"
       << "<pr_funcRespMaxIntakeRate>"
       << "<pr_frmirVal species=\"Species_1\">7295.4</pr_frmirVal>"
       << "</pr_funcRespMaxIntakeRate>"
       << "<pr_funcRespForagingEfficiency>"
       << "<pr_frfeVal species=\"Species_1\">0.001389</pr_frfeVal>"
       << "</pr_funcRespForagingEfficiency>"
       << "<pr_funcRespWeekSeason2Starts>12</pr_funcRespWeekSeason2Starts>"
       << "<pr_funcRespNumWeeksSeedFall>12</pr_funcRespNumWeeksSeedFall>"
       << "<pr_funcRespNumWeeksToModel>52</pr_funcRespNumWeeksToModel>"
       << "<pr_funcRespWeekGerminationStarts>32</pr_funcRespWeekGerminationStarts>"
       << "<pr_funcRespPreservePredatorDensities>1</pr_funcRespPreservePredatorDensities>"
       << "<pr_funcRespProportionGerminating>0.35</pr_funcRespProportionGerminating>"
       << "</FunctionalResponseSeedPredation2>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}


/////////////////////////////////////////////////////////////////////////////
// WriteFunResponseSeedPredationXMLFile6()
/////////////////////////////////////////////////////////////////////////////
const char* WriteFunResponseSeedPredationXMLFile6()
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
       << "<plot_lenX>160.0</plot_lenX>"
       << "<plot_lenY>160.0</plot_lenY>"
       << "<plot_latitude>55.37</plot_latitude>"
       << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
       << "<plot_temp_C>12.88171785</plot_temp_C>"
       << "</plot>"
       << "<trees>"
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
       << "<tr_slopeOfAsymHeight>"
       << "<tr_soahVal species=\"Species_1\">0.0299</tr_soahVal>"
       << "</tr_slopeOfAsymHeight>"
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
       << "</allometry>"
       << "<grid gridName=\"Dispersed Seeds\">"
       << "<ma_floatCodes>"
       << "<ma_floatCode label=\"seeds_0\">0</ma_floatCode>"
       << "</ma_floatCodes>"
       << "<ma_intCodes>"
       << "<ma_intCode label=\"count\">0</ma_intCode>"
       << "</ma_intCodes>"
       << "<ma_boolCodes>"
       << "<ma_boolCode label=\"Is Gap\">0</ma_boolCode>"
       << "</ma_boolCodes>"
       << "<ma_lengthXCells>160</ma_lengthXCells>"
       << "<ma_lengthYCells>160</ma_lengthYCells>"
       << "</grid>"
       << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>FunctionalResponseSeedPredation</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Seed\"/>"
       << "</behavior>"
       << "</behaviorList>"
       << "<FunctionalResponseSeedPredation1>"
       << "<pr_funcRespPredatorInitialDensity>0.00046875</pr_funcRespPredatorInitialDensity>"
       << "<pr_funcRespMaxInstDeclineRate1>-0.050622442</pr_funcRespMaxInstDeclineRate1>"
       << "<pr_funcRespMaxInstDeclineRate2>-0.050622442</pr_funcRespMaxInstDeclineRate2>"
       << "<pr_funcRespDemographicEfficiency1>0.000154258</pr_funcRespDemographicEfficiency1>"
       << "<pr_funcRespDemographicEfficiency2>0.000154258</pr_funcRespDemographicEfficiency2>"
       << "<pr_funcRespDensityDependentCoefficient1>-0.000718667</pr_funcRespDensityDependentCoefficient1>"
       << "<pr_funcRespDensityDependentCoefficient2>-0.000718667</pr_funcRespDensityDependentCoefficient2>"
       << "<pr_funcRespMaxIntakeRate>"
       << "<pr_frmirVal species=\"Species_1\">1042.2</pr_frmirVal>"
       << "</pr_funcRespMaxIntakeRate>"
       << "<pr_funcRespForagingEfficiency>"
       << "<pr_frfeVal species=\"Species_1\">0.001389</pr_frfeVal>"
       << "</pr_funcRespForagingEfficiency>"
       << "<pr_funcRespWeekSeason2Starts>12</pr_funcRespWeekSeason2Starts>"
       << "<pr_funcRespNumWeeksSeedFall>12</pr_funcRespNumWeeksSeedFall>"
       << "<pr_funcRespNumWeeksToModel>32</pr_funcRespNumWeeksToModel>"
       << "<pr_funcRespWeekGerminationStarts>32</pr_funcRespWeekGerminationStarts>"
       << "<pr_funcRespPreservePredatorDensities>1</pr_funcRespPreservePredatorDensities>"
       << "<pr_funcRespProportionGerminating>0.35</pr_funcRespProportionGerminating>"
       << "</FunctionalResponseSeedPredation1>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}


/////////////////////////////////////////////////////////////////////////////
// WriteFunResponseSeedPredationXMLFile7()
/////////////////////////////////////////////////////////////////////////////
const char* WriteFunResponseSeedPredationXMLFile7()
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
       << "<plot_lenX>160.0</plot_lenX>"
       << "<plot_lenY>160.0</plot_lenY>"
       << "<plot_latitude>55.37</plot_latitude>"
       << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
       << "<plot_temp_C>12.88171785</plot_temp_C>"
       << "</plot>"
       << "<trees>"
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
       << "<tr_slopeOfAsymHeight>"
       << "<tr_soahVal species=\"Species_1\">0.0299</tr_soahVal>"
       << "</tr_slopeOfAsymHeight>"
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
       << "</allometry>"
       << "<grid gridName=\"Dispersed Seeds\">"
       << "<ma_floatCodes>"
       << "<ma_floatCode label=\"seeds_0\">0</ma_floatCode>"
       << "</ma_floatCodes>"
       << "<ma_intCodes>"
       << "<ma_intCode label=\"count\">0</ma_intCode>"
       << "</ma_intCodes>"
       << "<ma_boolCodes>"
       << "<ma_boolCode label=\"Is Gap\">0</ma_boolCode>"
       << "</ma_boolCodes>"
       << "<ma_lengthXCells>160</ma_lengthXCells>"
       << "<ma_lengthYCells>160</ma_lengthYCells>"
       << "</grid>"
       << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>FunctionalResponseSeedPredation</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Seed\"/>"
       << "</behavior>"
       << "</behaviorList>"
       << "<FunctionalResponseSeedPredation1>"
       << "<pr_funcRespPredatorInitialDensity>0.00046875</pr_funcRespPredatorInitialDensity>"
       << "<pr_funcRespMaxInstDeclineRate1>-0.050622442</pr_funcRespMaxInstDeclineRate1>"
       << "<pr_funcRespMaxInstDeclineRate2>-0.050622442</pr_funcRespMaxInstDeclineRate2>"
       << "<pr_funcRespDemographicEfficiency1>0.000154258</pr_funcRespDemographicEfficiency1>"
       << "<pr_funcRespDemographicEfficiency2>0.000154258</pr_funcRespDemographicEfficiency2>"
       << "<pr_funcRespDensityDependentCoefficient1>-0.000718667</pr_funcRespDensityDependentCoefficient1>"
       << "<pr_funcRespDensityDependentCoefficient2>-0.000718667</pr_funcRespDensityDependentCoefficient2>"
       << "<pr_funcRespMaxIntakeRate>"
       << "<pr_frmirVal species=\"Species_1\">1042.2</pr_frmirVal>"
       << "</pr_funcRespMaxIntakeRate>"
       << "<pr_funcRespForagingEfficiency>"
       << "<pr_frfeVal species=\"Species_1\">0.001389</pr_frfeVal>"
       << "</pr_funcRespForagingEfficiency>"
       << "<pr_funcRespWeekSeason2Starts>12</pr_funcRespWeekSeason2Starts>"
       << "<pr_funcRespNumWeeksSeedFall>12</pr_funcRespNumWeeksSeedFall>"
       << "<pr_funcRespNumWeeksToModel>32</pr_funcRespNumWeeksToModel>"
       << "<pr_funcRespWeekGerminationStarts>32</pr_funcRespWeekGerminationStarts>"
       << "<pr_funcRespPreservePredatorDensities>0</pr_funcRespPreservePredatorDensities>"
       << "<pr_funcRespProportionGerminating>0.35</pr_funcRespProportionGerminating>"
       << "</FunctionalResponseSeedPredation1>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}


/////////////////////////////////////////////////////////////////////////////
// WriteFunResponseSeedPredationXMLFile8()
/////////////////////////////////////////////////////////////////////////////
const char* WriteFunResponseSeedPredationXMLFile8()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  float fTotalSeeds = 51200000.0,
        fSeed1Proportion = 0.25, fSeed2Proportion = 0.75,
        fSpecieslSeeds = fTotalSeeds * fSeed1Proportion,
        fSpecies2Seeds = fTotalSeeds * fSeed2Proportion;

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06010101\">"
       << "<plot>"
       << "<timesteps>1</timesteps>"
       << "<yearsPerTimestep>1</yearsPerTimestep>"
       << "<randomSeed>1</randomSeed>"
       << "<plot_lenX>160.0</plot_lenX>"
       << "<plot_lenY>160.0</plot_lenY>"
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
       << "<tr_chVal species=\"Species_2\">39.48</tr_chVal>"
       << "<tr_chVal species=\"Species_3\">39.48</tr_chVal>"
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
       << "<tr_stdMaxCrownRad>"
       << "<tr_smcrVal species=\"Species_1\">10</tr_smcrVal>"
       << "<tr_smcrVal species=\"Species_2\">10</tr_smcrVal>"
       << "<tr_smcrVal species=\"Species_3\">10</tr_smcrVal>"
       << "</tr_stdMaxCrownRad>"
       << "<tr_conversionDiam10ToDBH>"
       << "<tr_cdtdVal species=\"Species_1\">0.8008</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_2\">0.8008</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_3\">0.8008</tr_cdtdVal>"
       << "</tr_conversionDiam10ToDBH>"
       << "<tr_interceptDiam10ToDBH>"
       << "<tr_idtdVal species=\"Species_1\">0</tr_idtdVal>"
       << "<tr_idtdVal species=\"Species_2\">0</tr_idtdVal>"
       << "<tr_idtdVal species=\"Species_3\">0</tr_idtdVal>"
       << "</tr_interceptDiam10ToDBH>"
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
       << "<tr_slopeOfAsymHeight>"
       << "<tr_soahVal species=\"Species_1\">0.0299</tr_soahVal>"
       << "<tr_soahVal species=\"Species_2\">0.0299</tr_soahVal>"
       << "<tr_soahVal species=\"Species_3\">0.0299</tr_soahVal>"
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
       << "<grid gridName=\"Dispersed Seeds\">"
       << "<ma_floatCodes>"
       << "<ma_floatCode label=\"seeds_0\">0</ma_floatCode>"
       << "<ma_floatCode label=\"seeds_1\">1</ma_floatCode>"
       << "<ma_floatCode label=\"seeds_2\">2</ma_floatCode>"
       << "</ma_floatCodes>"
       << "<ma_intCodes>"
       << "<ma_intCode label=\"count\">0</ma_intCode>"
       << "</ma_intCodes>"
       << "<ma_boolCodes>"
       << "<ma_boolCode label=\"Is Gap\">0</ma_boolCode>"
       << "</ma_boolCodes>"
       << "<ma_lengthXCells>160</ma_lengthXCells>"
       << "<ma_lengthYCells>160</ma_lengthYCells>"
       << "<ma_v x=\"0\" y=\"0\">"
       << "<fl c=\"0\">" << fSpecieslSeeds << "</fl>"
       << "<fl c=\"1\">" << fSpecies2Seeds << "</fl>"
       << "<fl c=\"2\">100000</fl>"
       << "</ma_v>"
       << "</grid>"
       << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>FunctionalResponseSeedPredation</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Seed\"/>"
       << "<applyTo species=\"Species_2\" type=\"Seed\"/>"
       << "</behavior>"
       << "</behaviorList>"
       << "<FunctionalResponseSeedPredation1>"
       << "<pr_funcRespPredatorInitialDensity>0.00046875</pr_funcRespPredatorInitialDensity>"
       << "<pr_funcRespMaxInstDeclineRate1>-0.050622442</pr_funcRespMaxInstDeclineRate1>"
       << "<pr_funcRespMaxInstDeclineRate2>-0.050622442</pr_funcRespMaxInstDeclineRate2>"
       << "<pr_funcRespDemographicEfficiency1>0.000154258</pr_funcRespDemographicEfficiency1>"
       << "<pr_funcRespDemographicEfficiency2>0.000154258</pr_funcRespDemographicEfficiency2>"
       << "<pr_funcRespDensityDependentCoefficient1>-0.000718667</pr_funcRespDensityDependentCoefficient1>"
       << "<pr_funcRespDensityDependentCoefficient2>-0.000718667</pr_funcRespDensityDependentCoefficient2>"
       << "<pr_funcRespMaxIntakeRate>"
       << "<pr_frmirVal species=\"Species_1\">1042.2</pr_frmirVal>"
       << "<pr_frmirVal species=\"Species_2\">1042.2</pr_frmirVal>"
       << "</pr_funcRespMaxIntakeRate>"
       << "<pr_funcRespForagingEfficiency>"
       << "<pr_frfeVal species=\"Species_1\">0.001389</pr_frfeVal>"
       << "<pr_frfeVal species=\"Species_2\">0.001389</pr_frfeVal>"
       << "</pr_funcRespForagingEfficiency>"
       << "<pr_funcRespWeekSeason2Starts>12</pr_funcRespWeekSeason2Starts>"
       << "<pr_funcRespNumWeeksSeedFall>12</pr_funcRespNumWeeksSeedFall>"
       << "<pr_funcRespNumWeeksToModel>52</pr_funcRespNumWeeksToModel>"
       << "<pr_funcRespWeekGerminationStarts>32</pr_funcRespWeekGerminationStarts>"
       << "<pr_funcRespPreservePredatorDensities>0</pr_funcRespPreservePredatorDensities>"
       << "<pr_funcRespProportionGerminating>0.35</pr_funcRespProportionGerminating>"
       << "<pr_funcRespOutputFilename>TestOfftake1.txt</pr_funcRespOutputFilename>"
       << "</FunctionalResponseSeedPredation1>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}


/////////////////////////////////////////////////////////////////////////////
// WriteFunResponseSeedPredationXMLOfftakeTestFile2()
/////////////////////////////////////////////////////////////////////////////
const char* WriteFunResponseSeedPredationXMLOfftakeTestFile2()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06010101\">"
       << "<plot>"
       << "<timesteps>1</timesteps>"
       << "<yearsPerTimestep>1</yearsPerTimestep>"
       << "<randomSeed>1</randomSeed>"
       << "<plot_lenX>160.0</plot_lenX>"
       << "<plot_lenY>160.0</plot_lenY>"
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
       << "<tr_chVal species=\"Species_2\">39.48</tr_chVal>"
       << "<tr_chVal species=\"Species_3\">39.48</tr_chVal>"
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
       << "<tr_stdMaxCrownRad>"
       << "<tr_smcrVal species=\"Species_1\">10</tr_smcrVal>"
       << "<tr_smcrVal species=\"Species_2\">10</tr_smcrVal>"
       << "<tr_smcrVal species=\"Species_3\">10</tr_smcrVal>"
       << "</tr_stdMaxCrownRad>"
       << "<tr_conversionDiam10ToDBH>"
       << "<tr_cdtdVal species=\"Species_1\">0.8008</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_2\">0.8008</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_3\">0.8008</tr_cdtdVal>"
       << "</tr_conversionDiam10ToDBH>"
       << "<tr_interceptDiam10ToDBH>"
       << "<tr_idtdVal species=\"Species_1\">0</tr_idtdVal>"
       << "<tr_idtdVal species=\"Species_2\">0</tr_idtdVal>"
       << "<tr_idtdVal species=\"Species_3\">0</tr_idtdVal>"
       << "</tr_interceptDiam10ToDBH>"
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
       << "<tr_slopeOfAsymHeight>"
       << "<tr_soahVal species=\"Species_1\">0.0299</tr_soahVal>"
       << "<tr_soahVal species=\"Species_2\">0.0299</tr_soahVal>"
       << "<tr_soahVal species=\"Species_3\">0.0299</tr_soahVal>"
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
       << "<grid gridName=\"Dispersed Seeds\">"
       << "<ma_floatCodes>"
       << "<ma_floatCode label=\"seeds_0\">0</ma_floatCode>"
       << "<ma_floatCode label=\"seeds_1\">1</ma_floatCode>"
       << "<ma_floatCode label=\"seeds_2\">2</ma_floatCode>"
       << "</ma_floatCodes>"
       << "<ma_intCodes>"
       << "<ma_intCode label=\"count\">0</ma_intCode>"
       << "</ma_intCodes>"
       << "<ma_boolCodes>"
       << "<ma_boolCode label=\"Is Gap\">0</ma_boolCode>"
       << "</ma_boolCodes>"

       << "<ma_lengthXCells>160</ma_lengthXCells>"
       << "<ma_lengthYCells>160</ma_lengthYCells>"
       << "<ma_v x=\"0\" y=\"0\">"
       << "<fl c=\"0\">51200000</fl>"
       << "<fl c=\"1\">51200000</fl>"
       << "<fl c=\"2\">36000000</fl>"
       << "</ma_v>";

  oOut << "</grid>"
       << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>LinkedFunctionalResponseSeedPredation</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_3\" type=\"Seed\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>FunctionalResponseSeedPredation</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>2</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Seed\"/>"
       << "</behavior>"
       << "</behaviorList>"
       << "<FunctionalResponseSeedPredation2>"
       << "<pr_funcRespPredatorInitialDensity>0.00046875</pr_funcRespPredatorInitialDensity>"
       << "<pr_funcRespMaxInstDeclineRate1>-0.050622442</pr_funcRespMaxInstDeclineRate1>"
       << "<pr_funcRespMaxInstDeclineRate2>-0.050622442</pr_funcRespMaxInstDeclineRate2>"
       << "<pr_funcRespDemographicEfficiency1>0.000154258</pr_funcRespDemographicEfficiency1>"
       << "<pr_funcRespDemographicEfficiency2>0.000154258</pr_funcRespDemographicEfficiency2>"
       << "<pr_funcRespDensityDependentCoefficient1>-0.000718667</pr_funcRespDensityDependentCoefficient1>"
       << "<pr_funcRespDensityDependentCoefficient2>-0.000718667</pr_funcRespDensityDependentCoefficient2>"
       << "<pr_funcRespMaxIntakeRate>"
       << "<pr_frmirVal species=\"Species_1\">1042.2</pr_frmirVal>"
       << "</pr_funcRespMaxIntakeRate>"
       << "<pr_funcRespForagingEfficiency>"
       << "<pr_frfeVal species=\"Species_1\">0.001389</pr_frfeVal>"
       << "</pr_funcRespForagingEfficiency>"
       << "<pr_funcRespWeekSeason2Starts>12</pr_funcRespWeekSeason2Starts>"
       << "<pr_funcRespNumWeeksSeedFall>12</pr_funcRespNumWeeksSeedFall>"
       << "<pr_funcRespNumWeeksToModel>35</pr_funcRespNumWeeksToModel>"
       << "<pr_funcRespWeekGerminationStarts>32</pr_funcRespWeekGerminationStarts>"
       << "<pr_funcRespPreservePredatorDensities>0</pr_funcRespPreservePredatorDensities>"
       << "<pr_funcRespProportionGerminating>0.35</pr_funcRespProportionGerminating>"
       << "</FunctionalResponseSeedPredation2>"
       << "<FunctionalResponseSeedPredation1>"
       << "<pr_funcRespPredatorInitialDensity>0.002</pr_funcRespPredatorInitialDensity>"
       << "<pr_funcRespMaxInstDeclineRate1>-0.04</pr_funcRespMaxInstDeclineRate1>"
       << "<pr_funcRespMaxInstDeclineRate2>-0.04</pr_funcRespMaxInstDeclineRate2>"
       << "<pr_funcRespDemographicEfficiency1>0.0002</pr_funcRespDemographicEfficiency1>"
       << "<pr_funcRespDemographicEfficiency2>0.0002</pr_funcRespDemographicEfficiency2>"
       << "<pr_funcRespDensityDependentCoefficient1>-0.008</pr_funcRespDensityDependentCoefficient1>"
       << "<pr_funcRespDensityDependentCoefficient2>-0.008</pr_funcRespDensityDependentCoefficient2>"
       << "<pr_funcRespMaxIntakeRate>"
       << "<pr_frmirVal species=\"Species_3\">300</pr_frmirVal>"
       << "</pr_funcRespMaxIntakeRate>"
       << "<pr_funcRespForagingEfficiency>"
       << "<pr_frfeVal species=\"Species_3\">0.002</pr_frfeVal>"
       << "</pr_funcRespForagingEfficiency>"
       << "<pr_funcRespNumWeeksSeedFall>7</pr_funcRespNumWeeksSeedFall>"
       << "<pr_funcRespNumWeeksToModel>30</pr_funcRespNumWeeksToModel>"
       << "<pr_funcRespWeekSeason2Starts>12</pr_funcRespWeekSeason2Starts>"
       << "<pr_funcRespWeekGerminationStarts>10</pr_funcRespWeekGerminationStarts>"
       << "<pr_funcRespPreservePredatorDensities>0</pr_funcRespPreservePredatorDensities>"
       << "<pr_funcRespProportionGerminating>0.1</pr_funcRespProportionGerminating>"
       << "</FunctionalResponseSeedPredation1>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}


/////////////////////////////////////////////////////////////////////////////
// WriteFunResponseSeedPredationXMLOfftakeTestFile3()
/////////////////////////////////////////////////////////////////////////////
const char* WriteFunResponseSeedPredationXMLOfftakeTestFile3()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  int iX, iY;
  oOut.open(cFileString, ios::out | ios::trunc);

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06010101\">"
       << "<plot>"
       << "<timesteps>3</timesteps>"
       << "<yearsPerTimestep>1</yearsPerTimestep>"
       << "<randomSeed>1</randomSeed>"
       << "<plot_lenX>160.0</plot_lenX>"
       << "<plot_lenY>160.0</plot_lenY>"
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
       << "<tr_chVal species=\"Species_2\">39.48</tr_chVal>"
       << "<tr_chVal species=\"Species_3\">39.48</tr_chVal>"
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
       << "<tr_stdMaxCrownRad>"
       << "<tr_smcrVal species=\"Species_1\">10</tr_smcrVal>"
       << "<tr_smcrVal species=\"Species_2\">10</tr_smcrVal>"
       << "<tr_smcrVal species=\"Species_3\">10</tr_smcrVal>"
       << "</tr_stdMaxCrownRad>"
       << "<tr_conversionDiam10ToDBH>"
       << "<tr_cdtdVal species=\"Species_1\">0.8008</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_2\">0.8008</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_3\">0.8008</tr_cdtdVal>"
       << "</tr_conversionDiam10ToDBH>"
       << "<tr_interceptDiam10ToDBH>"
       << "<tr_idtdVal species=\"Species_1\">0</tr_idtdVal>"
       << "<tr_idtdVal species=\"Species_2\">0</tr_idtdVal>"
       << "<tr_idtdVal species=\"Species_3\">0</tr_idtdVal>"
       << "</tr_interceptDiam10ToDBH>"
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
       << "<tr_slopeOfAsymHeight>"
       << "<tr_soahVal species=\"Species_1\">0.0299</tr_soahVal>"
       << "<tr_soahVal species=\"Species_2\">0.0299</tr_soahVal>"
       << "<tr_soahVal species=\"Species_3\">0.0299</tr_soahVal>"
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
       << "<grid gridName=\"Dispersed Seeds\">"
       << "<ma_floatCodes>"
       << "<ma_floatCode label=\"seeds_0\">0</ma_floatCode>"
       << "<ma_floatCode label=\"seeds_1\">1</ma_floatCode>"
       << "<ma_floatCode label=\"seeds_2\">2</ma_floatCode>"
       << "</ma_floatCodes>"
       << "<ma_intCodes>"
       << "<ma_intCode label=\"count\">0</ma_intCode>"
       << "</ma_intCodes>"
       << "<ma_boolCodes>"
       << "<ma_boolCode label=\"Is Gap\">0</ma_boolCode>"
       << "</ma_boolCodes>"
       << "<ma_lengthXCells>10</ma_lengthXCells>"
       << "<ma_lengthYCells>10</ma_lengthYCells>";
       for (iX = 0; iX < 16; iX++) {
         for (iY = 0; iY < 16; iY++) {
           oOut << "<ma_v x=\"" << iX << "\" y=\"" << iY << "\">"
                << "<fl c=\"1\">100000</fl>"
                << "<fl c=\"2\">100000</fl>"
                << "</ma_v>";
         }
       }

  oOut << "</grid>"
       << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>LinkedFunctionalResponseSeedPredation</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_2\" type=\"Seed\"/>"
       << "<applyTo species=\"Species_3\" type=\"Seed\"/>"
       << "</behavior>"
       << "</behaviorList>"
       << "<FunctionalResponseSeedPredation1>"
       << "<pr_funcRespPredatorInitialDensity>0.002</pr_funcRespPredatorInitialDensity>"
       << "<pr_funcRespMaxInstDeclineRate1>-0.04</pr_funcRespMaxInstDeclineRate1>"
       << "<pr_funcRespMaxInstDeclineRate2>-0.04</pr_funcRespMaxInstDeclineRate2>"
       << "<pr_funcRespDemographicEfficiency1>0.0002</pr_funcRespDemographicEfficiency1>"
       << "<pr_funcRespDemographicEfficiency2>0.0002</pr_funcRespDemographicEfficiency2>"
       << "<pr_funcRespDensityDependentCoefficient1>-0.008</pr_funcRespDensityDependentCoefficient1>"
       << "<pr_funcRespDensityDependentCoefficient2>-0.008</pr_funcRespDensityDependentCoefficient2>"
       << "<pr_funcRespMaxIntakeRate>"
       << "<pr_frmirVal species=\"Species_2\">2000</pr_frmirVal>"
       << "<pr_frmirVal species=\"Species_3\">2000</pr_frmirVal>"
       << "</pr_funcRespMaxIntakeRate>"
       << "<pr_funcRespForagingEfficiency>"
       << "<pr_frfeVal species=\"Species_2\">0.002</pr_frfeVal>"
       << "<pr_frfeVal species=\"Species_3\">0.002</pr_frfeVal>"
       << "</pr_funcRespForagingEfficiency>"
       << "<pr_funcRespNumWeeksSeedFall>12</pr_funcRespNumWeeksSeedFall>"
       << "<pr_funcRespNumWeeksToModel>45</pr_funcRespNumWeeksToModel>"
       << "<pr_funcRespWeekSeason2Starts>12</pr_funcRespWeekSeason2Starts>"
       << "<pr_funcRespWeekGerminationStarts>30</pr_funcRespWeekGerminationStarts>"
       << "<pr_funcRespPreservePredatorDensities>0</pr_funcRespPreservePredatorDensities>"
       << "<pr_funcRespProportionGerminating>0.4</pr_funcRespProportionGerminating>"
       << "</FunctionalResponseSeedPredation1>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}


/////////////////////////////////////////////////////////////////////////////
// WriteFunResponseSeedPredationXMLOfftakeTestFile4()
/////////////////////////////////////////////////////////////////////////////
const char* WriteFunResponseSeedPredationXMLOfftakeTestFile4()
{
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
       << "<plot_lenX>160.0</plot_lenX>"
       << "<plot_lenY>160.0</plot_lenY>"
       << "<plot_latitude>55.37</plot_latitude>"
       << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
       << "<plot_temp_C>12.88171785</plot_temp_C>"
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
       << "<tr_soahVal species=\"Species_2\">0.0299</tr_soahVal>"
       << "<tr_soahVal species=\"Species_3\">0.0299</tr_soahVal>"
       << "<tr_soahVal species=\"Species_4\">0.0299</tr_soahVal>"
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
       << "<grid gridName=\"Dispersed Seeds\">"
       << "<ma_floatCodes>"
       << "<ma_floatCode label=\"seeds_0\">0</ma_floatCode>"
       << "<ma_floatCode label=\"seeds_1\">1</ma_floatCode>"
       << "<ma_floatCode label=\"seeds_2\">2</ma_floatCode>"
       << "<ma_floatCode label=\"seeds_3\">3</ma_floatCode>"
       << "</ma_floatCodes>"
       << "<ma_intCodes>"
       << "<ma_intCode label=\"count\">0</ma_intCode>"
       << "</ma_intCodes>"
       << "<ma_boolCodes>"
       << "<ma_boolCode label=\"Is Gap\">0</ma_boolCode>"
       << "</ma_boolCodes>"
       << "<ma_lengthXCells>160</ma_lengthXCells>"
       << "<ma_lengthYCells>160</ma_lengthYCells>"
       << "<ma_v x=\"0\" y=\"0\">"
       << "<fl c=\"0\">51200000</fl>"
       << "<fl c=\"1\">102400000</fl>"
       << "<fl c=\"2\">36000000</fl>"
       << "<fl c=\"3\">153600000</fl>"
       << "</ma_v>";

  oOut << "</grid>"
       << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>FunctionalResponseSeedPredation</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Seed\"/>"
       << "<applyTo species=\"Species_2\" type=\"Seed\"/>"
       << "<applyTo species=\"Species_4\" type=\"Seed\"/>"
       << "</behavior>"
       << "</behaviorList>"
       << "<FunctionalResponseSeedPredation1>"
       << "<pr_funcRespPredatorInitialDensity>0.002</pr_funcRespPredatorInitialDensity>"
       << "<pr_funcRespMaxInstDeclineRate1>-0.1749</pr_funcRespMaxInstDeclineRate1>"
       << "<pr_funcRespMaxInstDeclineRate2>0.549</pr_funcRespMaxInstDeclineRate2>"
       << "<pr_funcRespDemographicEfficiency1>0.00179</pr_funcRespDemographicEfficiency1>"
       << "<pr_funcRespDemographicEfficiency2>0.024</pr_funcRespDemographicEfficiency2>"
       << "<pr_funcRespDensityDependentCoefficient1>-0.1566</pr_funcRespDensityDependentCoefficient1>"
       << "<pr_funcRespDensityDependentCoefficient2>-0.0258</pr_funcRespDensityDependentCoefficient2>"
       << "<pr_funcRespMaxIntakeRate>"
       << "<pr_frmirVal species=\"Species_1\">666.67</pr_frmirVal>"
       << "<pr_frmirVal species=\"Species_2\">1042</pr_frmirVal>"
       << "<pr_frmirVal species=\"Species_4\">1378</pr_frmirVal>"
       << "</pr_funcRespMaxIntakeRate>"
       << "<pr_funcRespForagingEfficiency>"
       << "<pr_frfeVal species=\"Species_1\">0.002</pr_frfeVal>"
       << "<pr_frfeVal species=\"Species_2\">0.00139</pr_frfeVal>"
       << "<pr_frfeVal species=\"Species_4\">0.00105</pr_frfeVal>"
       << "</pr_funcRespForagingEfficiency>"
       << "<pr_funcRespNumWeeksSeedFall>12</pr_funcRespNumWeeksSeedFall>"
       << "<pr_funcRespWeekSeason2Starts>20</pr_funcRespWeekSeason2Starts>"
       << "<pr_funcRespNumWeeksToModel>52</pr_funcRespNumWeeksToModel>"
       << "<pr_funcRespWeekGerminationStarts>30</pr_funcRespWeekGerminationStarts>"
       << "<pr_funcRespPreservePredatorDensities>0</pr_funcRespPreservePredatorDensities>"
       << "<pr_funcRespProportionGerminating>0.4</pr_funcRespProportionGerminating>"
       << "</FunctionalResponseSeedPredation1>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}


/////////////////////////////////////////////////////////////////////////////
// WriteFunResponseSeedPredationXMLErrorFile1()
/////////////////////////////////////////////////////////////////////////////
const char* WriteFunResponseSeedPredationXMLErrorFile1()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06010101\">"
       << "<plot>"
       << "<timesteps>1</timesteps>"
       << "<yearsPerTimestep>1</yearsPerTimestep>"
       << "<randomSeed>1</randomSeed>"
       << "<plot_lenX>160.0</plot_lenX>"
       << "<plot_lenY>160.0</plot_lenY>"
       << "<plot_latitude>55.37</plot_latitude>"
       << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
       << "<plot_temp_C>12.88171785</plot_temp_C>"
       << "</plot>"
       << "<trees>"
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
       << "<tr_slopeOfAsymHeight>"
       << "<tr_soahVal species=\"Species_1\">0.0299</tr_soahVal>"
       << "</tr_slopeOfAsymHeight>"
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
       << "</allometry>"
       << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>NonSpatialDisperse</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>FunctionalResponseSeedPredation</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>2</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Seed\"/>"
       << "</behavior>"
       << "</behaviorList>"
       << "<NonSpatialDisperse1>"
       << "<di_minDbhForReproduction>"
       << "<di_mdfrVal species=\"Species_1\">15.0</di_mdfrVal>"
       << "</di_minDbhForReproduction>"
       << "<di_nonSpatialSlopeOfLambda>"
       << "<di_nssolVal species=\"Species_1\">0</di_nssolVal>"
       << "</di_nonSpatialSlopeOfLambda>"
       << "<di_nonSpatialInterceptOfLambda>"
       << "<di_nsiolVal species=\"Species_1\">0.3</di_nsiolVal>"
       << "</di_nonSpatialInterceptOfLambda>"
       << "</NonSpatialDisperse1>"
       << "<GeneralDisperse>"
       << "<di_seedDistributionMethod>0</di_seedDistributionMethod>"
       << "</GeneralDisperse>"
       << "<FunctionalResponseSeedPredation2>"
       << "<pr_funcRespPredatorInitialDensity>0</pr_funcRespPredatorInitialDensity>"
       << "<pr_funcRespMaxInstDeclineRate1>-0.050622442</pr_funcRespMaxInstDeclineRate1>"
       << "<pr_funcRespMaxInstDeclineRate2>-0.050622442</pr_funcRespMaxInstDeclineRate2>"
       << "<pr_funcRespDemographicEfficiency1>0.000154258</pr_funcRespDemographicEfficiency1>"
       << "<pr_funcRespDemographicEfficiency2>0.000154258</pr_funcRespDemographicEfficiency2>"
       << "<pr_funcRespDensityDependentCoefficient1>-0.000718667</pr_funcRespDensityDependentCoefficient1>"
       << "<pr_funcRespDensityDependentCoefficient2>-0.000718667</pr_funcRespDensityDependentCoefficient2>"
       << "<pr_funcRespMaxIntakeRate>"
       << "<pr_frmirVal species=\"Species_1\">7295.4</pr_frmirVal>"
       << "</pr_funcRespMaxIntakeRate>"
       << "<pr_funcRespForagingEfficiency>"
       << "<pr_frfeVal species=\"Species_1\">0.001389</pr_frfeVal>"
       << "</pr_funcRespForagingEfficiency>"
       << "<pr_funcRespWeekSeason2Starts>12</pr_funcRespWeekSeason2Starts>"
       << "<pr_funcRespNumWeeksSeedFall>12</pr_funcRespNumWeeksSeedFall>"
       << "<pr_funcRespNumWeeksToModel>52</pr_funcRespNumWeeksToModel>"
       << "<pr_funcRespOutputFilename>TestSeeds.txt</pr_funcRespOutputFilename>"
       << "<pr_funcRespWeekGerminationStarts>32</pr_funcRespWeekGerminationStarts>"
       << "<pr_funcRespPreservePredatorDensities>0</pr_funcRespPreservePredatorDensities>"
       << "<pr_funcRespProportionGerminating>0.35</pr_funcRespProportionGerminating>"
       << "</FunctionalResponseSeedPredation2>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}


/////////////////////////////////////////////////////////////////////////////
// WriteFunResponseSeedPredationXMLErrorFile2()
/////////////////////////////////////////////////////////////////////////////
const char* WriteFunResponseSeedPredationXMLErrorFile2()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06010101\">"
       << "<plot>"
       << "<timesteps>1</timesteps>"
       << "<yearsPerTimestep>1</yearsPerTimestep>"
       << "<randomSeed>1</randomSeed>"
       << "<plot_lenX>160.0</plot_lenX>"
       << "<plot_lenY>160.0</plot_lenY>"
       << "<plot_latitude>55.37</plot_latitude>"
       << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
       << "<plot_temp_C>12.88171785</plot_temp_C>"
       << "</plot>"
       << "<trees>"
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
       << "<tr_stdMaxCrownRad>"
       << "<tr_smcrVal species=\"Species_1\">10</tr_smcrVal>"
       << "</tr_stdMaxCrownRad>"
       << "<tr_slopeOfHeight-Diam10>"
       << "<tr_sohdVal species=\"Species_1\">0.03418</tr_sohdVal>"
       << "</tr_slopeOfHeight-Diam10>"
       << "<tr_slopeOfAsymHeight>"
       << "<tr_soahVal species=\"Species_1\">0.0299</tr_soahVal>"
       << "</tr_slopeOfAsymHeight>"
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
       << "</allometry>"
       << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>FunctionalResponseSeedPredation</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Seed\"/>"
       << "</behavior>"
       << "</behaviorList>"
       << "<FunctionalResponseSeedPredation1>"
       << "<pr_funcRespPredatorInitialDensity>0.1</pr_funcRespPredatorInitialDensity>"
       << "<pr_funcRespMaxInstDeclineRate1>-0.050622442</pr_funcRespMaxInstDeclineRate1>"
       << "<pr_funcRespMaxInstDeclineRate2>-0.050622442</pr_funcRespMaxInstDeclineRate2>"
       << "<pr_funcRespDemographicEfficiency1>0.000154258</pr_funcRespDemographicEfficiency1>"
       << "<pr_funcRespDemographicEfficiency2>0.000154258</pr_funcRespDemographicEfficiency2>"
       << "<pr_funcRespDensityDependentCoefficient1>-0.000718667</pr_funcRespDensityDependentCoefficient1>"
       << "<pr_funcRespDensityDependentCoefficient2>-0.000718667</pr_funcRespDensityDependentCoefficient2>"
       << "<pr_funcRespMaxIntakeRate>"
       << "<pr_frmirVal species=\"Species_1\">7295.4</pr_frmirVal>"
       << "</pr_funcRespMaxIntakeRate>"
       << "<pr_funcRespForagingEfficiency>"
       << "<pr_frfeVal species=\"Species_1\">0.001389</pr_frfeVal>"
       << "</pr_funcRespForagingEfficiency>"
       << "<pr_funcRespWeekSeason2Starts>12</pr_funcRespWeekSeason2Starts>"
       << "<pr_funcRespNumWeeksSeedFall>12</pr_funcRespNumWeeksSeedFall>"
       << "<pr_funcRespNumWeeksToModel>52</pr_funcRespNumWeeksToModel>"
       << "<pr_funcRespOutputFilename>TestSeeds.txt</pr_funcRespOutputFilename>"
       << "<pr_funcRespWeekGerminationStarts>32</pr_funcRespWeekGerminationStarts>"
       << "<pr_funcRespPreservePredatorDensities>0</pr_funcRespPreservePredatorDensities>"
       << "<pr_funcRespProportionGerminating>0.35</pr_funcRespProportionGerminating>"
       << "</FunctionalResponseSeedPredation1>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}


/////////////////////////////////////////////////////////////////////////////
// WriteFunResponseSeedPredationXMLErrorFile3()
/////////////////////////////////////////////////////////////////////////////
const char* WriteFunResponseSeedPredationXMLErrorFile3()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  int iX, iY;
  oOut.open(cFileString, ios::out | ios::trunc);

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06010101\">"
       << "<plot>"
       << "<timesteps>1</timesteps>"
       << "<yearsPerTimestep>1</yearsPerTimestep>"
       << "<randomSeed>1</randomSeed>"
       << "<plot_lenX>160.0</plot_lenX>"
       << "<plot_lenY>160.0</plot_lenY>"
       << "<plot_latitude>55.37</plot_latitude>"
       << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
       << "<plot_temp_C>12.88171785</plot_temp_C>"
       << "</plot>"
       << "<trees>"
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
       << "<tr_slopeOfAsymHeight>"
       << "<tr_soahVal species=\"Species_1\">0.0299</tr_soahVal>"
       << "</tr_slopeOfAsymHeight>"
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
       << "</allometry>"
       << "<grid gridName=\"Dispersed Seeds\">"
       << "<ma_floatCodes>"
       << "<ma_floatCode label=\"seeds_0\">0</ma_floatCode>"
       << "</ma_floatCodes>"
       << "<ma_intCodes>"
       << "<ma_intCode label=\"count\">0</ma_intCode>"
       << "</ma_intCodes>"
       << "<ma_boolCodes>"
       << "<ma_boolCode label=\"Is Gap\">0</ma_boolCode>"
       << "</ma_boolCodes>"
       << "<ma_lengthXCells>2</ma_lengthXCells>"
       << "<ma_lengthYCells>4</ma_lengthYCells>"
       << "</grid>"
       << "<grid gridName=\"Seed Predators\">"
       << "<ma_floatCodes>"
       << "<ma_floatCode label=\"num preds\">0</ma_floatCode>"
       << "</ma_floatCodes>"
       << "<ma_lengthXCells>4</ma_lengthXCells>"
       << "<ma_lengthYCells>4</ma_lengthYCells>";
       for (iX = 0; iX < 40; iX++)
       {
         for (iY = 0; iY < 40; iY++)
         {
           oOut << "<ma_v x=\"" << iX << "\" y=\"" << iY << "\">"
           << "<fl c=\"0\">" << (float)(iX + iY) << "</fl>"
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
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>FunctionalResponseSeedPredation</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>2</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Seed\"/>"
       << "</behavior>"
       << "</behaviorList>"
       << "<NonSpatialDisperse1>"
       << "<di_minDbhForReproduction>"
       << "<di_mdfrVal species=\"Species_1\">15.0</di_mdfrVal>"
       << "</di_minDbhForReproduction>"
       << "<di_nonSpatialSlopeOfLambda>"
       << "<di_nssolVal species=\"Species_1\">0</di_nssolVal>"
       << "</di_nonSpatialSlopeOfLambda>"
       << "<di_nonSpatialInterceptOfLambda>"
       << "<di_nsiolVal species=\"Species_1\">0.3</di_nsiolVal>"
       << "</di_nonSpatialInterceptOfLambda>"
       << "</NonSpatialDisperse1>"
       << "<GeneralDisperse>"
       << "<di_seedDistributionMethod>0</di_seedDistributionMethod>"
       << "</GeneralDisperse>"
       << "<FunctionalResponseSeedPredation2>"
       << "<pr_funcRespPredatorInitialDensity>0.1</pr_funcRespPredatorInitialDensity>"
       << "<pr_funcRespMaxInstDeclineRate1>-0.050622442</pr_funcRespMaxInstDeclineRate1>"
       << "<pr_funcRespMaxInstDeclineRate2>-0.050622442</pr_funcRespMaxInstDeclineRate2>"
       << "<pr_funcRespDemographicEfficiency1>0.000154258</pr_funcRespDemographicEfficiency1>"
       << "<pr_funcRespDemographicEfficiency2>0.000154258</pr_funcRespDemographicEfficiency2>"
       << "<pr_funcRespDensityDependentCoefficient1>-0.000718667</pr_funcRespDensityDependentCoefficient1>"
       << "<pr_funcRespDensityDependentCoefficient2>-0.000718667</pr_funcRespDensityDependentCoefficient2>"
       << "<pr_funcRespMaxIntakeRate>"
       << "<pr_frmirVal species=\"Species_1\">7295.4</pr_frmirVal>"
       << "</pr_funcRespMaxIntakeRate>"
       << "<pr_funcRespForagingEfficiency>"
       << "<pr_frfeVal species=\"Species_1\">0.001389</pr_frfeVal>"
       << "</pr_funcRespForagingEfficiency>"
       << "<pr_funcRespWeekSeason2Starts>12</pr_funcRespWeekSeason2Starts>"
       << "<pr_funcRespNumWeeksSeedFall>12</pr_funcRespNumWeeksSeedFall>"
       << "<pr_funcRespNumWeeksToModel>52</pr_funcRespNumWeeksToModel>"
       << "<pr_funcRespOutputFilename>TestSeeds.txt</pr_funcRespOutputFilename>"
       << "<pr_funcRespWeekGerminationStarts>32</pr_funcRespWeekGerminationStarts>"
       << "<pr_funcRespPreservePredatorDensities>1</pr_funcRespPreservePredatorDensities>"
       << "<pr_funcRespProportionGerminating>0.35</pr_funcRespProportionGerminating>"
       << "</FunctionalResponseSeedPredation2>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}


/////////////////////////////////////////////////////////////////////////////
// WriteFunResponseSeedPredationXMLErrorFile4()
/////////////////////////////////////////////////////////////////////////////
const char* WriteFunResponseSeedPredationXMLErrorFile4()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06010101\">"
       << "<plot>"
       << "<timesteps>1</timesteps>"
       << "<yearsPerTimestep>1</yearsPerTimestep>"
       << "<randomSeed>1</randomSeed>"
       << "<plot_lenX>160.0</plot_lenX>"
       << "<plot_lenY>160.0</plot_lenY>"
       << "<plot_latitude>55.37</plot_latitude>"
       << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
       << "<plot_temp_C>12.88171785</plot_temp_C>"
       << "</plot>"
       << "<trees>"
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
       << "<tr_slopeOfAsymHeight>"
       << "<tr_soahVal species=\"Species_1\">0.0299</tr_soahVal>"
       << "</tr_slopeOfAsymHeight>"
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
       << "</allometry>"
       << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>NonSpatialDisperse</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>FunctionalResponseSeedPredation</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>2</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Seed\"/>"
       << "</behavior>"
       << "</behaviorList>"
       << "<NonSpatialDisperse1>"
       << "<di_minDbhForReproduction>"
       << "<di_mdfrVal species=\"Species_1\">15.0</di_mdfrVal>"
       << "</di_minDbhForReproduction>"
       << "<di_nonSpatialSlopeOfLambda>"
       << "<di_nssolVal species=\"Species_1\">0</di_nssolVal>"
       << "</di_nonSpatialSlopeOfLambda>"
       << "<di_nonSpatialInterceptOfLambda>"
       << "<di_nsiolVal species=\"Species_1\">0.3</di_nsiolVal>"
       << "</di_nonSpatialInterceptOfLambda>"
       << "</NonSpatialDisperse1>"
       << "<GeneralDisperse>"
       << "<di_seedDistributionMethod>0</di_seedDistributionMethod>"
       << "</GeneralDisperse>"
       << "<FunctionalResponseSeedPredation2>"
       << "<pr_funcRespPredatorInitialDensity>0.1</pr_funcRespPredatorInitialDensity>"
       << "<pr_funcRespMaxInstDeclineRate1>-0.050622442</pr_funcRespMaxInstDeclineRate1>"
       << "<pr_funcRespMaxInstDeclineRate2>-0.050622442</pr_funcRespMaxInstDeclineRate2>"
       << "<pr_funcRespDemographicEfficiency1>0.000154258</pr_funcRespDemographicEfficiency1>"
       << "<pr_funcRespDemographicEfficiency2>0.000154258</pr_funcRespDemographicEfficiency2>"
       << "<pr_funcRespDensityDependentCoefficient1>-0.000718667</pr_funcRespDensityDependentCoefficient1>"
       << "<pr_funcRespDensityDependentCoefficient2>-0.000718667</pr_funcRespDensityDependentCoefficient2>"
       << "<pr_funcRespMaxIntakeRate>"
       << "<pr_frmirVal species=\"Species_1\">7295.4</pr_frmirVal>"
       << "</pr_funcRespMaxIntakeRate>"
       << "<pr_funcRespForagingEfficiency>"
       << "<pr_frfeVal species=\"Species_1\">0.001389</pr_frfeVal>"
       << "</pr_funcRespForagingEfficiency>"
       << "<pr_funcRespWeekSeason2Starts>12</pr_funcRespWeekSeason2Starts>"
       << "<pr_funcRespNumWeeksSeedFall>0</pr_funcRespNumWeeksSeedFall>"
       << "<pr_funcRespNumWeeksToModel>52</pr_funcRespNumWeeksToModel>"
       << "<pr_funcRespOutputFilename>TestSeeds.txt</pr_funcRespOutputFilename>"
       << "<pr_funcRespWeekGerminationStarts>32</pr_funcRespWeekGerminationStarts>"
       << "<pr_funcRespPreservePredatorDensities>0</pr_funcRespPreservePredatorDensities>"
       << "<pr_funcRespProportionGerminating>0.35</pr_funcRespProportionGerminating>"
       << "</FunctionalResponseSeedPredation2>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}


/////////////////////////////////////////////////////////////////////////////
// WriteFunResponseSeedPredationXMLErrorFile5()
/////////////////////////////////////////////////////////////////////////////
const char* WriteFunResponseSeedPredationXMLErrorFile5()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06010101\">"
       << "<plot>"
       << "<timesteps>1</timesteps>"
       << "<yearsPerTimestep>1</yearsPerTimestep>"
       << "<randomSeed>1</randomSeed>"
       << "<plot_lenX>160.0</plot_lenX>"
       << "<plot_lenY>160.0</plot_lenY>"
       << "<plot_latitude>55.37</plot_latitude>"
       << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
       << "<plot_temp_C>12.88171785</plot_temp_C>"
       << "</plot>"
       << "<trees>"
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
       << "<tr_slopeOfAsymHeight>"
       << "<tr_soahVal species=\"Species_1\">0.0299</tr_soahVal>"
       << "</tr_slopeOfAsymHeight>"
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
       << "</allometry>"
       << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>NonSpatialDisperse</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>FunctionalResponseSeedPredation</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>2</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Seed\"/>"
       << "</behavior>"
       << "</behaviorList>"
       << "<NonSpatialDisperse1>"
       << "<di_minDbhForReproduction>"
       << "<di_mdfrVal species=\"Species_1\">15.0</di_mdfrVal>"
       << "</di_minDbhForReproduction>"
       << "<di_nonSpatialSlopeOfLambda>"
       << "<di_nssolVal species=\"Species_1\">0</di_nssolVal>"
       << "</di_nonSpatialSlopeOfLambda>"
       << "<di_nonSpatialInterceptOfLambda>"
       << "<di_nsiolVal species=\"Species_1\">0.3</di_nsiolVal>"
       << "</di_nonSpatialInterceptOfLambda>"
       << "</NonSpatialDisperse1>"
       << "<GeneralDisperse>"
       << "<di_seedDistributionMethod>0</di_seedDistributionMethod>"
       << "</GeneralDisperse>"
       << "<FunctionalResponseSeedPredation2>"
       << "<pr_funcRespPredatorInitialDensity>0.1</pr_funcRespPredatorInitialDensity>"
       << "<pr_funcRespMaxInstDeclineRate1>-0.050622442</pr_funcRespMaxInstDeclineRate1>"
       << "<pr_funcRespMaxInstDeclineRate2>-0.050622442</pr_funcRespMaxInstDeclineRate2>"
       << "<pr_funcRespDemographicEfficiency1>0.000154258</pr_funcRespDemographicEfficiency1>"
       << "<pr_funcRespDemographicEfficiency2>0.000154258</pr_funcRespDemographicEfficiency2>"
       << "<pr_funcRespDensityDependentCoefficient1>-0.000718667</pr_funcRespDensityDependentCoefficient1>"
       << "<pr_funcRespDensityDependentCoefficient2>-0.000718667</pr_funcRespDensityDependentCoefficient2>"
       << "<pr_funcRespMaxIntakeRate>"
       << "<pr_frmirVal species=\"Species_1\">7295.4</pr_frmirVal>"
       << "</pr_funcRespMaxIntakeRate>"
       << "<pr_funcRespForagingEfficiency>"
       << "<pr_frfeVal species=\"Species_1\">0.001389</pr_frfeVal>"
       << "</pr_funcRespForagingEfficiency>"
       << "<pr_funcRespWeekSeason2Starts>12</pr_funcRespWeekSeason2Starts>"
       << "<pr_funcRespNumWeeksSeedFall>12</pr_funcRespNumWeeksSeedFall>"
       << "<pr_funcRespNumWeeksToModel>0</pr_funcRespNumWeeksToModel>"
       << "<pr_funcRespOutputFilename>TestSeeds.txt</pr_funcRespOutputFilename>"
       << "<pr_funcRespWeekGerminationStarts>32</pr_funcRespWeekGerminationStarts>"
       << "<pr_funcRespPreservePredatorDensities>0</pr_funcRespPreservePredatorDensities>"
       << "<pr_funcRespProportionGerminating>0.35</pr_funcRespProportionGerminating>"
       << "</FunctionalResponseSeedPredation2>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}


/////////////////////////////////////////////////////////////////////////////
// WriteFunResponseSeedPredationXMLErrorFile6()
/////////////////////////////////////////////////////////////////////////////
const char* WriteFunResponseSeedPredationXMLErrorFile6()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  int iX, iY;
  oOut.open(cFileString, ios::out | ios::trunc);

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06010101\">"
       << "<plot>"
       << "<timesteps>1</timesteps>"
       << "<yearsPerTimestep>1</yearsPerTimestep>"
       << "<randomSeed>1</randomSeed>"
       << "<plot_lenX>160.0</plot_lenX>"
       << "<plot_lenY>160.0</plot_lenY>"
       << "<plot_latitude>55.37</plot_latitude>"
       << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
       << "<plot_temp_C>12.88171785</plot_temp_C>"
       << "</plot>"
       << "<trees>"
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
       << "<tr_slopeOfAsymHeight>"
       << "<tr_soahVal species=\"Species_1\">0.0299</tr_soahVal>"
       << "</tr_slopeOfAsymHeight>"
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
       << "</allometry>"
       << "<grid gridName=\"Dispersed Seeds\">"
       << "<ma_floatCodes>"
       << "<ma_floatCode label=\"seeds_0\">0</ma_floatCode>"
       << "</ma_floatCodes>"
       << "<ma_intCodes>"
       << "<ma_intCode label=\"count\">0</ma_intCode>"
       << "</ma_intCodes>"
       << "<ma_boolCodes>"
       << "<ma_boolCode label=\"Is Gap\">0</ma_boolCode>"
       << "</ma_boolCodes>"
       << "<ma_lengthXCells>2</ma_lengthXCells>"
       << "<ma_lengthYCells>4</ma_lengthYCells>"
       << "</grid>"
       << "<grid gridName=\"Seed Predators\">"
       << "<ma_floatCodes>"
       << "<ma_floatCode label=\"num preds\">0</ma_floatCode>"
       << "</ma_floatCodes>"
       << "<ma_lengthXCells>2</ma_lengthXCells>"
       << "<ma_lengthYCells>2</ma_lengthYCells>";
       for (iX = 0; iX < 80; iX++)
       {
         for (iY = 0; iY < 80; iY++)
         {
           oOut << "<ma_v x=\"" << iX << "\" y=\"" << iY << "\">"
           << "<fl c=\"0\">" << (float)(iX + iY) << "</fl>"
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
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>FunctionalResponseSeedPredation</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>2</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Seed\"/>"
       << "</behavior>"
       << "</behaviorList>"
       << "<NonSpatialDisperse1>"
       << "<di_minDbhForReproduction>"
       << "<di_mdfrVal species=\"Species_1\">15.0</di_mdfrVal>"
       << "</di_minDbhForReproduction>"
       << "<di_nonSpatialSlopeOfLambda>"
       << "<di_nssolVal species=\"Species_1\">0</di_nssolVal>"
       << "</di_nonSpatialSlopeOfLambda>"
       << "<di_nonSpatialInterceptOfLambda>"
       << "<di_nsiolVal species=\"Species_1\">0.3</di_nsiolVal>"
       << "</di_nonSpatialInterceptOfLambda>"
       << "</NonSpatialDisperse1>"
       << "<GeneralDisperse>"
       << "<di_seedDistributionMethod>0</di_seedDistributionMethod>"
       << "</GeneralDisperse>"
       << "<FunctionalResponseSeedPredation2>"
       << "<pr_funcRespPredatorInitialDensity>0.1</pr_funcRespPredatorInitialDensity>"
       << "<pr_funcRespMaxInstDeclineRate1>-0.050622442</pr_funcRespMaxInstDeclineRate1>"
       << "<pr_funcRespMaxInstDeclineRate2>-0.050622442</pr_funcRespMaxInstDeclineRate2>"
       << "<pr_funcRespDemographicEfficiency1>0.000154258</pr_funcRespDemographicEfficiency1>"
       << "<pr_funcRespDemographicEfficiency2>0.000154258</pr_funcRespDemographicEfficiency2>"
       << "<pr_funcRespDensityDependentCoefficient1>-0.000718667</pr_funcRespDensityDependentCoefficient1>"
       << "<pr_funcRespDensityDependentCoefficient2>-0.000718667</pr_funcRespDensityDependentCoefficient2>"
       << "<pr_funcRespMaxIntakeRate>"
       << "<pr_frmirVal species=\"Species_1\">7295.4</pr_frmirVal>"
       << "</pr_funcRespMaxIntakeRate>"
       << "<pr_funcRespForagingEfficiency>"
       << "<pr_frfeVal species=\"Species_1\">0.001389</pr_frfeVal>"
       << "</pr_funcRespForagingEfficiency>"
       << "<pr_funcRespWeekSeason2Starts>12</pr_funcRespWeekSeason2Starts>"
       << "<pr_funcRespNumWeeksSeedFall>12</pr_funcRespNumWeeksSeedFall>"
       << "<pr_funcRespNumWeeksToModel>52</pr_funcRespNumWeeksToModel>"
       << "<pr_funcRespOutputFilename>TestSeeds.txt</pr_funcRespOutputFilename>"
       << "<pr_funcRespWeekGerminationStarts>32</pr_funcRespWeekGerminationStarts>"
       << "<pr_funcRespPreservePredatorDensities>1</pr_funcRespPreservePredatorDensities>"
       << "<pr_funcRespProportionGerminating>0.35</pr_funcRespProportionGerminating>"
       << "</FunctionalResponseSeedPredation2>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}


/////////////////////////////////////////////////////////////////////////////
// WriteFunResponseSeedPredationXMLErrorFile7()
/////////////////////////////////////////////////////////////////////////////
const char* WriteFunResponseSeedPredationXMLErrorFile7()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06010101\">" << "<plot>"
       << "<timesteps>1</timesteps>"
       << "<yearsPerTimestep>1</yearsPerTimestep>"
       << "<randomSeed>1</randomSeed>"
       << "<plot_lenX>160.0</plot_lenX>"
       << "<plot_lenY>160.0</plot_lenY>"
       << "<plot_latitude>55.37</plot_latitude>"
       << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
       << "<plot_temp_C>12.88171785</plot_temp_C>"
       << "</plot>"
       << "<trees>"
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
       << "<tr_slopeOfAsymHeight>"
       << "<tr_soahVal species=\"Species_1\">0.0299</tr_soahVal>"
       << "</tr_slopeOfAsymHeight>"
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
       << "</allometry>"
       << "<grid gridName=\"Dispersed Seeds\">"
       << "<ma_floatCodes>"
       << "<ma_floatCode label=\"seeds_0\">0</ma_floatCode>"
       << "</ma_floatCodes>"
       << "<ma_intCodes>"
       << "<ma_intCode label=\"count\">0</ma_intCode>"
       << "</ma_intCodes>"
       << "<ma_boolCodes>"
       << "<ma_boolCode label=\"Is Gap\">0</ma_boolCode>"
       << "</ma_boolCodes>"
       << "<ma_lengthXCells>2</ma_lengthXCells>"
       << "<ma_lengthYCells>4</ma_lengthYCells>"
       << "</grid>"
       << "<grid gridName=\"Seed Predators\">"
       << "<ma_intCodes>"
       << "<ma_intCode label=\"num preds\">0</ma_intCode>"
       << "</ma_intCodes>"
       << "<ma_lengthXCells>2</ma_lengthXCells>"
       << "<ma_lengthYCells>4</ma_lengthYCells>"
       << "</grid>"
       << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>NonSpatialDisperse</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>FunctionalResponseSeedPredation</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>2</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Seed\"/>"
       << "</behavior>"
       << "</behaviorList>"
       << "<NonSpatialDisperse1>"
       << "<di_minDbhForReproduction>"
       << "<di_mdfrVal species=\"Species_1\">15.0</di_mdfrVal>"
       << "</di_minDbhForReproduction>"
       << "<di_nonSpatialSlopeOfLambda>"
       << "<di_nssolVal species=\"Species_1\">0</di_nssolVal>"
       << "</di_nonSpatialSlopeOfLambda>"
       << "<di_nonSpatialInterceptOfLambda>"
       << "<di_nsiolVal species=\"Species_1\">0.3</di_nsiolVal>"
       << "</di_nonSpatialInterceptOfLambda>"
       << "</NonSpatialDisperse1>"
       << "<GeneralDisperse>"
       << "<di_seedDistributionMethod>0</di_seedDistributionMethod>"
       << "</GeneralDisperse>"
       << "<FunctionalResponseSeedPredation2>"
       << "<pr_funcRespPredatorInitialDensity>0.1</pr_funcRespPredatorInitialDensity>"
       << "<pr_funcRespMaxInstDeclineRate1>-0.050622442</pr_funcRespMaxInstDeclineRate1>"
       << "<pr_funcRespMaxInstDeclineRate2>-0.050622442</pr_funcRespMaxInstDeclineRate2>"
       << "<pr_funcRespDemographicEfficiency1>0.000154258</pr_funcRespDemographicEfficiency1>"
       << "<pr_funcRespDemographicEfficiency2>0.000154258</pr_funcRespDemographicEfficiency2>"
       << "<pr_funcRespDensityDependentCoefficient1>-0.000718667</pr_funcRespDensityDependentCoefficient1>"
       << "<pr_funcRespDensityDependentCoefficient2>-0.000718667</pr_funcRespDensityDependentCoefficient2>"
       << "<pr_funcRespMaxIntakeRate>"
       << "<pr_frmirVal species=\"Species_1\">7295.4</pr_frmirVal>"
       << "</pr_funcRespMaxIntakeRate>"
       << "<pr_funcRespForagingEfficiency>"
       << "<pr_frfeVal species=\"Species_1\">0.001389</pr_frfeVal>"
       << "</pr_funcRespForagingEfficiency>"
       << "<pr_funcRespWeekSeason2Starts>12</pr_funcRespWeekSeason2Starts>"
       << "<pr_funcRespNumWeeksSeedFall>12</pr_funcRespNumWeeksSeedFall>"
       << "<pr_funcRespNumWeeksToModel>52</pr_funcRespNumWeeksToModel>"
       << "<pr_funcRespOutputFilename>TestSeeds.txt</pr_funcRespOutputFilename>"
       << "<pr_funcRespWeekGerminationStarts>32</pr_funcRespWeekGerminationStarts>"
       << "<pr_funcRespPreservePredatorDensities>1</pr_funcRespPreservePredatorDensities>"
       << "<pr_funcRespProportionGerminating>0.35</pr_funcRespProportionGerminating>"
       << "</FunctionalResponseSeedPredation2>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}


/////////////////////////////////////////////////////////////////////////////
// WriteFunResponseSeedPredationXMLErrorFile8()
/////////////////////////////////////////////////////////////////////////////
const char* WriteFunResponseSeedPredationXMLErrorFile8()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06010101\">"
       << "<plot>"
       << "<timesteps>1</timesteps>"
       << "<yearsPerTimestep>1</yearsPerTimestep>"
       << "<randomSeed>1</randomSeed>"
       << "<plot_lenX>160.0</plot_lenX>"
       << "<plot_lenY>160.0</plot_lenY>"
       << "<plot_latitude>55.37</plot_latitude>"
       << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
       << "<plot_temp_C>12.88171785</plot_temp_C>"
       << "</plot>"
       << "<trees>"
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
       << "<tr_slopeOfAsymHeight>"
       << "<tr_soahVal species=\"Species_1\">0.0299</tr_soahVal>"
       << "</tr_slopeOfAsymHeight>"
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
       << "</allometry>"
       << "<grid gridName=\"Dispersed Seeds\">"
       << "<ma_floatCodes>"
       << "<ma_floatCode label=\"seeds_0\">0</ma_floatCode>"
       << "</ma_floatCodes>"
       << "<ma_intCodes>"
       << "<ma_intCode label=\"count\">0</ma_intCode>"
       << "</ma_intCodes>"
       << "<ma_boolCodes>"
       << "<ma_boolCode label=\"Is Gap\">0</ma_boolCode>"
       << "</ma_boolCodes>"
       << "<ma_lengthXCells>160</ma_lengthXCells>"
       << "<ma_lengthYCells>160</ma_lengthYCells>"
       << "<ma_v x=\"0\" y=\"0\">"
       << "<fl c=\"0\">51200000</fl>"
       << "</ma_v>"
       << "</grid>"
       << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>FunctionalResponseSeedPredation</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Seed\"/>"
       << "</behavior>"
       << "</behaviorList>"
       << "<FunctionalResponseSeedPredation1>"
       << "<pr_funcRespPredatorInitialDensity>0.00046875</pr_funcRespPredatorInitialDensity>"
       << "<pr_funcRespMaxInstDeclineRate1>-0.050622442</pr_funcRespMaxInstDeclineRate1>"
       << "<pr_funcRespMaxInstDeclineRate2>-0.050622442</pr_funcRespMaxInstDeclineRate2>"
       << "<pr_funcRespDemographicEfficiency1>0.000154258</pr_funcRespDemographicEfficiency1>"
       << "<pr_funcRespDemographicEfficiency2>0.000154258</pr_funcRespDemographicEfficiency2>"
       << "<pr_funcRespDensityDependentCoefficient1>-0.000718667</pr_funcRespDensityDependentCoefficient1>"
       << "<pr_funcRespDensityDependentCoefficient2>-0.000718667</pr_funcRespDensityDependentCoefficient2>"
       << "<pr_funcRespMaxIntakeRate>"
       << "<pr_frmirVal species=\"Species_1\">1042.2</pr_frmirVal>"
       << "</pr_funcRespMaxIntakeRate>"
       << "<pr_funcRespForagingEfficiency>"
       << "<pr_frfeVal species=\"Species_1\">0.001389</pr_frfeVal>"
       << "</pr_funcRespForagingEfficiency>"
       << "<pr_funcRespWeekSeason2Starts>12</pr_funcRespWeekSeason2Starts>"
       << "<pr_funcRespNumWeeksSeedFall>12</pr_funcRespNumWeeksSeedFall>"
       << "<pr_funcRespNumWeeksToModel>52</pr_funcRespNumWeeksToModel>"
       << "<pr_funcRespWeekGerminationStarts>-32</pr_funcRespWeekGerminationStarts>"
       << "<pr_funcRespPreservePredatorDensities>0</pr_funcRespPreservePredatorDensities>"
       << "<pr_funcRespProportionGerminating>0.35</pr_funcRespProportionGerminating>"
       << "<pr_funcRespOutputFilename>TestSeeds.txt</pr_funcRespOutputFilename>"
       << "</FunctionalResponseSeedPredation1>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}


/////////////////////////////////////////////////////////////////////////////
// WriteFunResponseSeedPredationXMLErrorFile9()
/////////////////////////////////////////////////////////////////////////////
const char* WriteFunResponseSeedPredationXMLErrorFile9()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06010101\">"
       << "<plot>"
       << "<timesteps>1</timesteps>"
       << "<yearsPerTimestep>1</yearsPerTimestep>"
       << "<randomSeed>1</randomSeed>"
       << "<plot_lenX>160.0</plot_lenX>"
       << "<plot_lenY>160.0</plot_lenY>"
       << "<plot_latitude>55.37</plot_latitude>"
       << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
       << "<plot_temp_C>12.88171785</plot_temp_C>"
       << "</plot>"
       << "<trees>"
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
       << "<tr_slopeOfAsymHeight>"
       << "<tr_soahVal species=\"Species_1\">0.0299</tr_soahVal>"
       << "</tr_slopeOfAsymHeight>"
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
       << "</allometry>"
       << "<grid gridName=\"Dispersed Seeds\">"
       << "<ma_floatCodes>"
       << "<ma_floatCode label=\"seeds_0\">0</ma_floatCode>"
       << "</ma_floatCodes>"
       << "<ma_intCodes>"
       << "<ma_intCode label=\"count\">0</ma_intCode>"
       << "</ma_intCodes>"
       << "<ma_boolCodes>"
       << "<ma_boolCode label=\"Is Gap\">0</ma_boolCode>"
       << "</ma_boolCodes>"
       << "<ma_lengthXCells>160</ma_lengthXCells>"
       << "<ma_lengthYCells>160</ma_lengthYCells>"
       << "<ma_v x=\"0\" y=\"0\">"
       << "<fl c=\"0\">51200000</fl>"
       << "</ma_v>"
       << "</grid>"
       << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>FunctionalResponseSeedPredation</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Seed\"/>"
       << "</behavior>"
       << "</behaviorList>"
       << "<FunctionalResponseSeedPredation1>"
       << "<pr_funcRespPredatorInitialDensity>0.00046875</pr_funcRespPredatorInitialDensity>"
       << "<pr_funcRespMaxInstDeclineRate1>-0.050622442</pr_funcRespMaxInstDeclineRate1>"
       << "<pr_funcRespMaxInstDeclineRate2>-0.050622442</pr_funcRespMaxInstDeclineRate2>"
       << "<pr_funcRespDemographicEfficiency1>0.000154258</pr_funcRespDemographicEfficiency1>"
       << "<pr_funcRespDemographicEfficiency2>0.000154258</pr_funcRespDemographicEfficiency2>"
       << "<pr_funcRespDensityDependentCoefficient1>-0.000718667</pr_funcRespDensityDependentCoefficient1>"
       << "<pr_funcRespDensityDependentCoefficient2>-0.000718667</pr_funcRespDensityDependentCoefficient2>"
       << "<pr_funcRespMaxIntakeRate>"
       << "<pr_frmirVal species=\"Species_1\">1042.2</pr_frmirVal>"
       << "</pr_funcRespMaxIntakeRate>"
       << "<pr_funcRespForagingEfficiency>"
       << "<pr_frfeVal species=\"Species_1\">0.001389</pr_frfeVal>"
       << "</pr_funcRespForagingEfficiency>"
       << "<pr_funcRespWeekSeason2Starts>12</pr_funcRespWeekSeason2Starts>"
       << "<pr_funcRespNumWeeksSeedFall>12</pr_funcRespNumWeeksSeedFall>"
       << "<pr_funcRespNumWeeksToModel>52</pr_funcRespNumWeeksToModel>"
       << "<pr_funcRespWeekGerminationStarts>53</pr_funcRespWeekGerminationStarts>"
       << "<pr_funcRespPreservePredatorDensities>0</pr_funcRespPreservePredatorDensities>"
       << "<pr_funcRespProportionGerminating>0.35</pr_funcRespProportionGerminating>"
       << "<pr_funcRespOutputFilename>TestSeeds.txt</pr_funcRespOutputFilename>"
       << "</FunctionalResponseSeedPredation1>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}


/////////////////////////////////////////////////////////////////////////////
// WriteFunResponseSeedPredationXMLErrorFile10()
/////////////////////////////////////////////////////////////////////////////
const char* WriteFunResponseSeedPredationXMLErrorFile10()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06010101\">"
       << "<plot>"
       << "<timesteps>1</timesteps>"
       << "<yearsPerTimestep>1</yearsPerTimestep>"
       << "<randomSeed>1</randomSeed>"
       << "<plot_lenX>160.0</plot_lenX>"
       << "<plot_lenY>160.0</plot_lenY>"
       << "<plot_latitude>55.37</plot_latitude>"
       << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
       << "<plot_temp_C>12.88171785</plot_temp_C>"
       << "</plot>"
       << "<trees>"
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
       << "<tr_slopeOfAsymHeight>"
       << "<tr_soahVal species=\"Species_1\">0.0299</tr_soahVal>"
       << "</tr_slopeOfAsymHeight>"
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
       << "</allometry>"
       << "<grid gridName=\"Dispersed Seeds\">"
       << "<ma_floatCodes>"
       << "<ma_floatCode label=\"seeds_0\">0</ma_floatCode>"
       << "</ma_floatCodes>"
       << "<ma_intCodes>"
       << "<ma_intCode label=\"count\">0</ma_intCode>"
       << "</ma_intCodes>"
       << "<ma_boolCodes>"
       << "<ma_boolCode label=\"Is Gap\">0</ma_boolCode>"
       << "</ma_boolCodes>"
       << "<ma_lengthXCells>160</ma_lengthXCells>"
       << "<ma_lengthYCells>160</ma_lengthYCells>"
       << "<ma_v x=\"0\" y=\"0\">"
       << "<fl c=\"0\">51200000</fl>"
       << "</ma_v>"
       << "</grid>"
       << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>FunctionalResponseSeedPredation</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Seed\"/>"
       << "</behavior>"
       << "</behaviorList>"
       << "<FunctionalResponseSeedPredation1>"
       << "<pr_funcRespPredatorInitialDensity>0.00046875</pr_funcRespPredatorInitialDensity>"
       << "<pr_funcRespMaxInstDeclineRate1>-0.050622442</pr_funcRespMaxInstDeclineRate1>"
       << "<pr_funcRespMaxInstDeclineRate2>-0.050622442</pr_funcRespMaxInstDeclineRate2>"
       << "<pr_funcRespDemographicEfficiency1>0.000154258</pr_funcRespDemographicEfficiency1>"
       << "<pr_funcRespDemographicEfficiency2>0.000154258</pr_funcRespDemographicEfficiency2>"
       << "<pr_funcRespDensityDependentCoefficient1>-0.000718667</pr_funcRespDensityDependentCoefficient1>"
       << "<pr_funcRespDensityDependentCoefficient2>-0.000718667</pr_funcRespDensityDependentCoefficient2>"
       << "<pr_funcRespMaxIntakeRate>"
       << "<pr_frmirVal species=\"Species_1\">1042.2</pr_frmirVal>"
       << "</pr_funcRespMaxIntakeRate>"
       << "<pr_funcRespForagingEfficiency>"
       << "<pr_frfeVal species=\"Species_1\">0.001389</pr_frfeVal>"
       << "</pr_funcRespForagingEfficiency>"
       << "<pr_funcRespWeekSeason2Starts>12</pr_funcRespWeekSeason2Starts>"
       << "<pr_funcRespNumWeeksSeedFall>12</pr_funcRespNumWeeksSeedFall>"
       << "<pr_funcRespNumWeeksToModel>52</pr_funcRespNumWeeksToModel>"
       << "<pr_funcRespWeekGerminationStarts>32</pr_funcRespWeekGerminationStarts>"
       << "<pr_funcRespPreservePredatorDensities>0</pr_funcRespPreservePredatorDensities>"
       << "<pr_funcRespProportionGerminating>-0.35</pr_funcRespProportionGerminating>"
       << "<pr_funcRespOutputFilename>TestSeeds.txt</pr_funcRespOutputFilename>"
       << "</FunctionalResponseSeedPredation1>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}


/////////////////////////////////////////////////////////////////////////////
// WriteFunResponseSeedPredationXMLErrorFile11()
/////////////////////////////////////////////////////////////////////////////
const char* WriteFunResponseSeedPredationXMLErrorFile11()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06010101\">"
       << "<plot>"
       << "<timesteps>1</timesteps>"
       << "<yearsPerTimestep>1</yearsPerTimestep>"
       << "<randomSeed>1</randomSeed>"
       << "<plot_lenX>160.0</plot_lenX>"
       << "<plot_lenY>160.0</plot_lenY>"
       << "<plot_latitude>55.37</plot_latitude>"
       << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
       << "<plot_temp_C>12.88171785</plot_temp_C>"
       << "</plot>"
       << "<trees>"
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
       << "<tr_slopeOfAsymHeight>"
       << "<tr_soahVal species=\"Species_1\">0.0299</tr_soahVal>"
       << "</tr_slopeOfAsymHeight>"
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
       << "</allometry>"
       << "<grid gridName=\"Dispersed Seeds\">"
       << "<ma_floatCodes>"
       << "<ma_floatCode label=\"seeds_0\">0</ma_floatCode>"
       << "</ma_floatCodes>"
       << "<ma_intCodes>"
       << "<ma_intCode label=\"count\">0</ma_intCode>"
       << "</ma_intCodes>"
       << "<ma_boolCodes>"
       << "<ma_boolCode label=\"Is Gap\">0</ma_boolCode>"
       << "</ma_boolCodes>"
       << "<ma_lengthXCells>160</ma_lengthXCells>"
       << "<ma_lengthYCells>160</ma_lengthYCells>"
       << "<ma_v x=\"0\" y=\"0\">"
       << "<fl c=\"0\">51200000</fl>"
       << "</ma_v>"
       << "</grid>"
       << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>FunctionalResponseSeedPredation</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Seed\"/>"
       << "</behavior>"
       << "</behaviorList>"
       << "<FunctionalResponseSeedPredation1>"
       << "<pr_funcRespPredatorInitialDensity>0.00046875</pr_funcRespPredatorInitialDensity>"
       << "<pr_funcRespMaxInstDeclineRate1>-0.050622442</pr_funcRespMaxInstDeclineRate1>"
       << "<pr_funcRespMaxInstDeclineRate2>-0.050622442</pr_funcRespMaxInstDeclineRate2>"
       << "<pr_funcRespDemographicEfficiency1>0.000154258</pr_funcRespDemographicEfficiency1>"
       << "<pr_funcRespDemographicEfficiency2>0.000154258</pr_funcRespDemographicEfficiency2>"
       << "<pr_funcRespDensityDependentCoefficient1>-0.000718667</pr_funcRespDensityDependentCoefficient1>"
       << "<pr_funcRespDensityDependentCoefficient2>-0.000718667</pr_funcRespDensityDependentCoefficient2>"
       << "<pr_funcRespMaxIntakeRate>"
       << "<pr_frmirVal species=\"Species_1\">1042.2</pr_frmirVal>"
       << "</pr_funcRespMaxIntakeRate>"
       << "<pr_funcRespForagingEfficiency>"
       << "<pr_frfeVal species=\"Species_1\">0.001389</pr_frfeVal>"
       << "</pr_funcRespForagingEfficiency>"
       << "<pr_funcRespWeekSeason2Starts>12</pr_funcRespWeekSeason2Starts>"
       << "<pr_funcRespNumWeeksSeedFall>12</pr_funcRespNumWeeksSeedFall>"
       << "<pr_funcRespNumWeeksToModel>52</pr_funcRespNumWeeksToModel>"
       << "<pr_funcRespWeekGerminationStarts>32</pr_funcRespWeekGerminationStarts>"
       << "<pr_funcRespPreservePredatorDensities>0</pr_funcRespPreservePredatorDensities>"
       << "<pr_funcRespProportionGerminating>1.35</pr_funcRespProportionGerminating>"
       << "<pr_funcRespOutputFilename>TestSeeds.txt</pr_funcRespOutputFilename>"
       << "</FunctionalResponseSeedPredation1>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

