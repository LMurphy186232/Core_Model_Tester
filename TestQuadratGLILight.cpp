//---------------------------------------------------------------------------
// TestQuadratGLILight.cpp
//---------------------------------------------------------------------------
#include "TestQuadratGLILight.h"
#include <gtest/gtest.h>

#include <fstream>
#include <math.h>
#include "SimManager.h"
#include "Grid.h"
#include "QuadratGLILight.h"
#include "TreePopulation.h"


/////////////////////////////////////////////////////////////////////////////
// TestNormalProcessingRun1()
// Makes sure Quadrat GLI processing is performed correctly.
// WriteQuadratGLILightXMLFile2() does setup. Two "Quadrat GLI" grid cells,
// (0, 0) and (5, 5), have their GLIs tested according to expected values from a
// spreadsheet. This verifies that GLI is being correctly calculated. All other
// cell values should be -1.
/////////////////////////////////////////////////////////////////////////////
TEST(QuadratGLILight, TestNormalProcessingRun1) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    clTreePopulation *p_oPop;
    clGrid *p_oQuadratGLIGrid;
    float fX, fY, fDiam, fExpectedGLI, fActualGLI;
    int iNumXCells, iNumYCells, iX, iY, iQuadratGLICode, i;

    //Run 1: WriteQuadratGLILightXMLFile2() does setup.
    p_oSimManager->ReadFile(WriteQuadratGLILightXMLFile2());

    //Place a seedling in cells 0, 0 and 5, 5 of the GLI quadrat grid.
    p_oPop = (clTreePopulation*) p_oSimManager->GetPopulationObject("treepopulation");
    ASSERT_TRUE(NULL != p_oPop);

    fX = 1; fY = 1;
    p_oPop->CreateTree (fX, fY, 0, clTreePopulation::seedling, 0);
    fX = 51; fY = 51;
    p_oPop->CreateTree (fX, fY, 0, clTreePopulation::seedling, 0);
    //Another seedling - this one should be ignored (wrong species)
    fX = 1; fY = 51;
    p_oPop->CreateTree (fX, fY, 1, clTreePopulation::seedling, 0);

    //Add the list of known neighbors
    fX = 65; fY = 66; fDiam = 25;
    p_oPop->CreateTree (fX, fY, 0, clTreePopulation::adult, fDiam);
    fX = 50; fY = 50; fDiam = 11;
    p_oPop->CreateTree (fX, fY, 0, clTreePopulation::adult, fDiam);
    fX = 56.1; fY = 50; fDiam = 45;
    p_oPop->CreateTree (fX, fY, 0, clTreePopulation::adult, fDiam);
    fX = 56; fY = 56; fDiam = 61;
    p_oPop->CreateTree (fX, fY, 0, clTreePopulation::adult, fDiam);
    fX = 51; fY = 57; fDiam = 15;
    p_oPop->CreateTree (fX, fY, 0, clTreePopulation::adult, fDiam);
    fX = 59; fY = 57; fDiam = 45;
    p_oPop->CreateTree (fX, fY, 0, clTreePopulation::adult, fDiam);

    //Run a timestep - don't let the whole timestep run because
    //clQuadratGLILight::TimestepCleanup will erase the values in the quadrat
    //grid cell
    for (i = 0; i < p_oSimManager->GetNumberOfBehaviors(); i++) {
      p_oSimManager->GetBehaviorObject(i)->Action();
    }

    //Test the GLIs of two "Quadrat GLI" grid cells, (0, 0) and (5, 5). This
    //verifies that GLI is being calculated.
    p_oQuadratGLIGrid = p_oSimManager->GetGridObject("Quadrat GLI");
    ASSERT_TRUE(p_oQuadratGLIGrid != NULL);
    iQuadratGLICode = p_oQuadratGLIGrid->GetFloatDataCode("GLI");
    ASSERT_TRUE(-1 != iQuadratGLICode);

    //0, 0
    fExpectedGLI = 100;
    p_oQuadratGLIGrid->GetValueOfCell(0, 0, iQuadratGLICode, &fActualGLI);
    EXPECT_LT(fabs(fExpectedGLI - fActualGLI), 0.1);

    //5, 5
    fExpectedGLI = 62.6762;
    p_oQuadratGLIGrid->GetValueOfCell(5, 5, iQuadratGLICode, &fActualGLI);
    EXPECT_LT(fabs(fExpectedGLI - fActualGLI), 0.01);

    //Make sure all other values are -1.
    iNumXCells = p_oQuadratGLIGrid->GetNumberXCells();
    iNumYCells = p_oQuadratGLIGrid->GetNumberYCells();
    for (iX = 0; iX < iNumXCells; iX++) {
      for (iY = 0; iY < iNumYCells; iY++) {
        if (!((iX==0 && iY==0) || (iX==5 && iY==5))) {
          p_oQuadratGLIGrid->GetValueOfCell(iX, iY, iQuadratGLICode, &fExpectedGLI);
          EXPECT_LT(fExpectedGLI, 0);
        }
      }
    }
    delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

/////////////////////////////////////////////////////////////////////////////
// TestNormalProcessingRun2()
// Makes sure Quadrat GLI processing is performed correctly.
// WriteQuadratGLILightXMLFile5() does setup. This makes sure that every cell
// gets a GLI value when that flag is set.
/////////////////////////////////////////////////////////////////////////////
TEST(QuadratGLILight, TestNormalProcessingRun2) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    clGrid *p_oQuadratGLIGrid;
    float fGLI;
    int iNumXCells, iNumYCells, iX, iY, iQuadratGLICode, i;

    p_oSimManager->ReadFile(WriteQuadratGLILightXMLFile5());

    //Run a timestep - don't let the whole timestep run because
    //clQuadratGLILight::TimestepCleanup will erase the values in the quadrat
    //grid cell
    for (i = 0; i < p_oSimManager->GetNumberOfBehaviors(); i++) {
      p_oSimManager->GetBehaviorObject(i)->Action();
    }

    //Verify that all GLI values are greater than 0
    p_oQuadratGLIGrid = p_oSimManager->GetGridObject("Quadrat GLI");
    ASSERT_TRUE(p_oQuadratGLIGrid != NULL);
    iQuadratGLICode = p_oQuadratGLIGrid->GetFloatDataCode("GLI");
    ASSERT_TRUE(-1 != iQuadratGLICode);
    iNumXCells = p_oQuadratGLIGrid->GetNumberXCells();
    iNumYCells = p_oQuadratGLIGrid->GetNumberYCells();
    for (iX = 0; iX < iNumXCells; iX++) {
      for (iY = 0; iY < iNumYCells; iY++) {
        p_oQuadratGLIGrid->GetValueOfCell(iX, iY, iQuadratGLICode, &fGLI);
        EXPECT_GT(fGLI, 0);
      }
    }
  delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

/////////////////////////////////////////////////////////////////////////////
// TestGridSetup()
// Tests the setup for the "Quadrat GLI" grid.  Tests the following conditions:
//
// -- The "Quadrat GLI" grid is correctly set up when there is no grid setup
//    information in the parameter file. WriteQuadratGLILightXMLFile1() is used to create the
//    parameter file in question. "Quadrat GLI" should have an 8m X 8m
//    resolution.
// -- The "Quadrat GLI" grid is correctly set up when there is grid setup
//    information in the parameter file.  WriteQuadratGLILightXMLFile2() is used to create the
//    parameter file in question. "Quadrat GLI" should have a 10m X 10m
//    resolution with no map values.
/////////////////////////////////////////////////////////////////////////////
TEST(QuadratGLILight, TestGridSetup) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    clGrid *p_oMapGrid;
    float fGLI;
    int iNumXCells, iNumYCells, iX, iY, iGLICode;

    //Feed in the first parameter file
    p_oSimManager->ReadFile(WriteQuadratGLILightXMLFile1());

    //Get the grid map
    p_oMapGrid = p_oSimManager->GetGridObject("Quadrat GLI");
    ASSERT_TRUE(NULL != p_oMapGrid);

    //Make sure that the grid resolution is 8 X 8 m
    EXPECT_LT(fabs(QUADRAT_CELL_SIZE - p_oMapGrid->GetLengthXCells()), 0.01);
    EXPECT_LT(fabs(QUADRAT_CELL_SIZE - p_oMapGrid->GetLengthYCells()), 0.01);

    //Make sure that all the grid values are -1
    iNumXCells = p_oMapGrid->GetNumberXCells();
    iNumYCells = p_oMapGrid->GetNumberYCells();
    iGLICode = p_oMapGrid->GetFloatDataCode("GLI");
    ASSERT_TRUE(-1 != iGLICode);

    for (iX = 0; iX < iNumXCells; iX++) {
      for (iY = 0; iY < iNumYCells; iY++) {
        p_oMapGrid->GetValueOfCell(iX, iY, iGLICode, &fGLI);
        EXPECT_LT(fGLI, 0);
      }
    }

    //Try the second parameter file
    p_oSimManager->ReadFile(WriteQuadratGLILightXMLFile2());

    //Get the grid map
    p_oMapGrid = p_oSimManager->GetGridObject("Quadrat GLI");
    ASSERT_TRUE(NULL != p_oMapGrid);

    //Make sure that the grid resolution is 10 X 10 m
    EXPECT_LT(fabs(10 - p_oMapGrid->GetLengthXCells()), 0.01);
    EXPECT_LT(fabs(10 - p_oMapGrid->GetLengthYCells()), 0.01);

    //Make sure that all the grid values are -1
    iNumXCells = p_oMapGrid->GetNumberXCells();
    iNumYCells = p_oMapGrid->GetNumberYCells();
    iGLICode = p_oMapGrid->GetFloatDataCode("GLI");
    ASSERT_TRUE(-1 != iGLICode);

    for (iX = 0; iX < iNumXCells; iX++) {
      for (iY = 0; iY < iNumYCells; iY++) {
        p_oMapGrid->GetValueOfCell(iX, iY, iGLICode, &fGLI);
        EXPECT_LT(fGLI, 0);
      }
    }
    delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

/////////////////////////////////////////////////////////////////////////////
// TestParameterSetup()
// Tests the setup for the parameters.  Tests the following conditions:
//
// -- The Quadrat GLI behavior is the only light behavior in the list.
// WriteQuadratGLILightXMLFile1() creates the parameter file.  The brightness array is
// checked to make sure it has non-zero values.
// -- The Quadrat GLI behavior and the GLI Light behavior are both in the
// list, and the GLI Light behavior comes first (meaning the Quadrat GLI
// behavior can borrow brightness array information from it).  WriteQuadratGLILightXMLFile2()
// creates the parameter file.  The brightness array has non-zero values.
// The Quadrat GLI has its correct settings for sky grids.
// -- The GLI light behavior and the Quadrat GLI Light behavior are both in
// the list, and the GLI Light behavior comes second (meaning the Quadrat GLI
// behavior cannot borrow brightness array information from it).
// WriteQuadratGLILightXMLFile3() creates the parameter file.  The brightness array has non-
// zero values. The Quadrat GLI has its correct settings for sky grids.
// -- The Quadrat GLI behavior and the GLI light behavior are both in the
// list, the Quadrat GLI behavior comes second, and the light settings are
// different. WriteQuadratGLILightXMLFile6() creates the parameter file.  The Quadrat GLI
// grid is of the right size for its sky grids and contains non-zero
// values.
/////////////////////////////////////////////////////////////////////////////
TEST(QuadratGLILight, TestParameterSetup) {

  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    clBehaviorBase *p_oTemp;
    clQuadratGLILight *p_oQuadrat;
    int i, j;

    //Test the following condition: The GLI Map behavior is the only light
    //behavior in the list. WriteQuadratGLILightXMLFile1() creates the parameter file.  The
    //brightness array is checked to make sure it has non-zero values.
    p_oSimManager->ReadFile(WriteQuadratGLILightXMLFile1());
    p_oTemp = p_oSimManager->GetBehaviorObject("quadratglilightshell");
    ASSERT_TRUE(NULL != p_oTemp);
    p_oQuadrat = dynamic_cast<clQuadratGLILight *>(p_oTemp);

    EXPECT_LT(fabs(p_oQuadrat->GetLightHeight() - 2), 0.01);
    EXPECT_LT(fabs(p_oQuadrat->GetSinMinSunAng() - 0.7068), 0.01);
    EXPECT_LT(fabs(p_oQuadrat->GetAziChunkConverter() - 0.05), 0.01);
    EXPECT_LT(fabs(p_oQuadrat->GetRcpTanMinAng() - 1.00079), 0.01);
    EXPECT_LT(fabs(p_oQuadrat->GetMinSunAngle() - 0.785), 0.01);
    EXPECT_EQ(p_oQuadrat->GetNumAziAng(), 18);
    EXPECT_EQ(p_oQuadrat->GetNumAltAng(), 12);
    EXPECT_EQ(p_oQuadrat->GetMinAngRow(), 8);
    EXPECT_LT(fabs(p_oQuadrat->GetMaxSearchRad() - 47.509), 0.01);
    for (i = p_oQuadrat->GetMinAngRow(); i < p_oQuadrat->GetNumAltAng(); i++) {
      for (j = 0; j < p_oQuadrat->GetNumAziAng(); j++) {
        EXPECT_GT( p_oQuadrat->GetBrightness(i, j), 0);
      }
    }

    //Test the following condition:  The Quadrat GLI and GLI Light behaviors are
    //both in the list, and the GLI Light behavior comes first (meaning the
    //Quadrat GLI behavior can borrow brightness array information from it).
    //WriteQuadratGLILightXMLFile2() creates the parameter file.  The brightness array has
    //non-zero values. The Quadrat GLI has its correct settings
    //for sky grids.
    p_oSimManager->ReadFile(WriteQuadratGLILightXMLFile2());
    p_oTemp = p_oSimManager->GetBehaviorObject("quadratglilightshell");
    ASSERT_TRUE(NULL != p_oTemp);
    p_oQuadrat = dynamic_cast<clQuadratGLILight *>(p_oTemp);

    EXPECT_LT(fabs(p_oQuadrat->GetLightHeight() - 2), 0.01);
    EXPECT_LT(fabs(p_oQuadrat->GetSinMinSunAng() - 0.7068), 0.01);
    EXPECT_LT(fabs(p_oQuadrat->GetAziChunkConverter() - 0.05), 0.01);
    EXPECT_LT(fabs(p_oQuadrat->GetRcpTanMinAng() - 1.00079), 0.01);
    EXPECT_LT(fabs(p_oQuadrat->GetMinSunAngle() - 0.785), 0.01);
    EXPECT_EQ(p_oQuadrat->GetNumAziAng(), 18);
    EXPECT_EQ(p_oQuadrat->GetNumAltAng(), 12);
    EXPECT_EQ(p_oQuadrat->GetMinAngRow(), 8);
    EXPECT_LT(fabs(p_oQuadrat->GetMaxSearchRad() - 47.509), 0.01);
    for (i = p_oQuadrat->GetMinAngRow(); i < p_oQuadrat->GetNumAltAng(); i++) {
      for (j = 0; j < p_oQuadrat->GetNumAziAng(); j++) {
        EXPECT_GT( p_oQuadrat->GetBrightness(i, j), 0);
      }
    }

    //The GLI light behavior and the Quadrat GLI Light behavior are both in
    // the list, and the GLI Light behavior comes second (meaning the Quadrat GLI
    // behavior cannot borrow brightness array information from it).
    // WriteQuadratGLILightXMLFile3() creates the parameter file.  The brightness array has non-
    // zero values. The Quadrat GLI has its correct settings for sky grids.
    p_oSimManager->ReadFile(WriteQuadratGLILightXMLFile3());
    p_oTemp = p_oSimManager->GetBehaviorObject("quadratglilightshell");
    ASSERT_TRUE(NULL != p_oTemp);
    p_oQuadrat = dynamic_cast<clQuadratGLILight *>(p_oTemp);

    EXPECT_LT(fabs(p_oQuadrat->GetLightHeight() - 2), 0.01);
    EXPECT_LT(fabs(p_oQuadrat->GetSinMinSunAng() - 0.7068), 0.01);
    EXPECT_LT(fabs(p_oQuadrat->GetAziChunkConverter() - 0.05), 0.01);
    EXPECT_LT(fabs(p_oQuadrat->GetRcpTanMinAng() - 1.00079), 0.01);
    EXPECT_LT(fabs(p_oQuadrat->GetMinSunAngle() - 0.785), 0.01);
    EXPECT_EQ(p_oQuadrat->GetNumAziAng(), 18);
    EXPECT_EQ(p_oQuadrat->GetNumAltAng(), 12);
    EXPECT_EQ(p_oQuadrat->GetMinAngRow(), 8);
    EXPECT_LT(fabs(p_oQuadrat->GetMaxSearchRad() - 47.509), 0.01);
    for (i = p_oQuadrat->GetMinAngRow(); i < p_oQuadrat->GetNumAltAng(); i++) {
      for (j = 0; j < p_oQuadrat->GetNumAziAng(); j++) {
        EXPECT_GT( p_oQuadrat->GetBrightness(i, j), 0);
      }
    }

    //The Quadrat GLI behavior and the GLI light behavior are both in the
    // list, the Quadrat GLI behavior comes second, and the light settings are
    // different. WriteQuadratGLILightXMLFile6() creates the parameter file.  The Quadrat GLI
    // grid is of the right size for its sky grids and contains non-zero
    // values.
    p_oSimManager->ReadFile(WriteQuadratGLILightXMLFile4());
    p_oTemp = p_oSimManager->GetBehaviorObject("quadratglilightshell");
    ASSERT_TRUE(NULL != p_oTemp);
    p_oQuadrat = dynamic_cast<clQuadratGLILight *>(p_oTemp);

    EXPECT_LT(fabs(p_oQuadrat->GetLightHeight() - 1), 0.01);
    EXPECT_LT(fabs(p_oQuadrat->GetSinMinSunAng() - 0.7068), 0.01);
    EXPECT_LT(fabs(p_oQuadrat->GetAziChunkConverter() - 0.0555), 0.01);
    EXPECT_LT(fabs(p_oQuadrat->GetRcpTanMinAng() - 1.00079), 0.01);
    EXPECT_LT(fabs(p_oQuadrat->GetMinSunAngle() - 0.785), 0.01);
    EXPECT_EQ(p_oQuadrat->GetNumAziAng(), 20);
    EXPECT_EQ(p_oQuadrat->GetNumAltAng(), 10);
    EXPECT_EQ(p_oQuadrat->GetMinAngRow(), 7);
    EXPECT_LT(fabs(p_oQuadrat->GetMaxSearchRad() - 48.511), 0.01);
    for (i = p_oQuadrat->GetMinAngRow(); i < p_oQuadrat->GetNumAltAng(); i++) {
      for (j = 0; j < p_oQuadrat->GetNumAziAng(); j++) {
        EXPECT_GT( p_oQuadrat->GetBrightness(i, j), 0);
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
TEST(QuadratGLILight, TestErrorProcessing) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try
  {
    p_oSimManager->ReadFile(WriteQuadratGLILightXMLErrorFile1());
    FAIL() << "TestQuadratGLILight error processing didn't catch error for WriteQuadratGLILightXMLErrorFile1.";
  }
  catch (modelErr& err)
  {
    if (err.sFunction.compare("clQuadratGLILight::DoShellSetup") != 0)
    {
      FAIL() << "TestQuadratGLILight error processing caught wrong error for WriteQuadratGLILightXMLErrorFile1.";
    }
    ;
  }

  try
  {
    p_oSimManager->ReadFile(WriteQuadratGLILightXMLErrorFile2());
    FAIL() << "TestQuadratGLILight error processing didn't catch error for WriteQuadratGLILightXMLErrorFile2.";
  }
  catch (modelErr& err)
  {
    if (err.sFunction.compare("clQuadratGLILight::DoShellSetup") != 0)
    {
      FAIL() << "TestQuadratGLILight error processing caught wrong error for WriteQuadratGLILightXMLErrorFile2.";
    }
    ;
  }

  try
  {
    p_oSimManager->ReadFile(WriteQuadratGLILightXMLErrorFile3());
    FAIL() << "TestQuadratGLILight error processing didn't catch error for WriteQuadratGLILightXMLErrorFile3.";
  }
  catch (modelErr& err)
  {
    if (err.sFunction.compare("clQuadratGLILight::DoShellSetup") != 0)
    {
      FAIL() << "TestQuadratGLILight error processing caught wrong error for WriteQuadratGLILightXMLErrorFile3.";
    }
    ;
  }
  delete p_oSimManager;
}

////////////////////////////////////////////////////////////////////////////
// WriteQuadratGLILightXMLFile1()
////////////////////////////////////////////////////////////////////////////
const char* WriteQuadratGLILightXMLFile1() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  WriteQuadratGLILightCommonStuff(oOut);

  //Write file
  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>QuadratLight</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Seedling\"/>"
       << "</behavior>"
       << "</behaviorList>"
       << "<GeneralLight>"
       << "<li_beamFractGlobalRad>0.5</li_beamFractGlobalRad>"
       << "<li_clearSkyTransCoeff>0.65</li_clearSkyTransCoeff>"
       << "<li_julianDayGrowthStarts>105</li_julianDayGrowthStarts>"
       << "<li_julianDayGrowthEnds>258</li_julianDayGrowthEnds>"
       << "<li_lightExtinctionCoefficient>"
       << "<li_lecVal species=\"Species_1\">0.2</li_lecVal>"
       << "<li_lecVal species=\"Species_2\">0.2</li_lecVal>"
       << "</li_lightExtinctionCoefficient>"
       << "</GeneralLight>"
       << "<QuadratLight1>"
       << "<li_minSunAngle>0.785</li_minSunAngle>"
       << "<li_numAltGrids>12</li_numAltGrids>"
       << "<li_numAziGrids>18</li_numAziGrids>"
       << "<li_quadratLightHeight>2</li_quadratLightHeight>"
       << "<li_quadratAllGLIs>0</li_quadratAllGLIs>"
       << "</QuadratLight1>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteQuadratGLILightXMLFile2()
////////////////////////////////////////////////////////////////////////////
const char* WriteQuadratGLILightXMLFile2() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  WriteQuadratGLILightCommonStuff(oOut);

  oOut << "<grid gridName=\"Quadrat GLI\">"
       << "<ma_floatCodes>"
       << "<ma_floatCode label=\"GLI\">0</ma_floatCode>"
       << "</ma_floatCodes>"
       << "<ma_lengthXCells>10</ma_lengthXCells>"
       << "<ma_lengthYCells>10</ma_lengthYCells>";
  oOut << "</grid>"
       << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>GLILight</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>QuadratLight</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>2</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Seedling\"/>"
       << "</behavior>"
       << "</behaviorList>"
       << "<GeneralLight>"
       << "<li_beamFractGlobalRad>0.5</li_beamFractGlobalRad>"
       << "<li_clearSkyTransCoeff>0.65</li_clearSkyTransCoeff>"
       << "<li_julianDayGrowthStarts>105</li_julianDayGrowthStarts>"
       << "<li_julianDayGrowthEnds>258</li_julianDayGrowthEnds>"
       << "<li_lightExtinctionCoefficient>"
       << "<li_lecVal species=\"Species_1\">0.2</li_lecVal>"
       << "<li_lecVal species=\"Species_2\">0.2</li_lecVal>"
       << "</li_lightExtinctionCoefficient>"
       << "</GeneralLight>"
       << "<GLILight1>"
       << "<li_minSunAngle>0.785</li_minSunAngle>"
       << "<li_numAltGrids>12</li_numAltGrids>"
       << "<li_numAziGrids>18</li_numAziGrids>"
       << "</GLILight1>"
       << "<QuadratLight2>"
       << "<li_minSunAngle>0.785</li_minSunAngle>"
       << "<li_numAltGrids>12</li_numAltGrids>"
       << "<li_numAziGrids>18</li_numAziGrids>"
       << "<li_quadratLightHeight>2</li_quadratLightHeight>"
       << "<li_quadratAllGLIs>0</li_quadratAllGLIs>"
       << "</QuadratLight2>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteQuadratGLILightXMLFile3()
////////////////////////////////////////////////////////////////////////////
const char* WriteQuadratGLILightXMLFile3() {
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
       << "<plot_lenX>100.0</plot_lenX>"
       << "<plot_lenY>100.0</plot_lenY>"
       << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
       << "<plot_temp_C>12.88171785</plot_temp_C>"
       << "<plot_latitude>55.37</plot_latitude>"
       << "</plot>"
       << "<trees>"
       << "<tr_speciesList>"
       << "<tr_species speciesName=\"Species_1\" />"
       << "</tr_speciesList>"
       << "<tr_minAdultDBH>"
       << "<tr_madVal species=\"Species_1\">10.0</tr_madVal>"
       << "</tr_minAdultDBH>"
       << "<tr_maxSeedlingHeight>"
       << "<tr_mshVal species=\"Species_1\">1.35</tr_mshVal>"
       << "</tr_maxSeedlingHeight>";

  oOut << "<tr_sizeClasses>"
       << "<tr_sizeClass sizeKey=\"s15.0\" />"
       << "<tr_sizeClass sizeKey=\"s20.0\" />"
       << "<tr_sizeClass sizeKey=\"s30.0\" />"
       << "</tr_sizeClasses>"
       << "<tr_initialDensities>"
       << "<tr_idVals whatSpecies=\"Species_1\">"
       << "<tr_initialDensity sizeClass=\"s20.0\">50.0</tr_initialDensity>"
       << "</tr_idVals>"
       << "</tr_initialDensities>"
       << "<tr_seedDiam10Cm>0.1</tr_seedDiam10Cm>"
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
       << "<tr_sachVal species=\"Species_1\">0.589</tr_sachVal>"
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
       << "</tr_whatAdultHeightDiam>"
       << "</allometry>";

  oOut << "<grid gridName=\"Quadrat GLI\">"
       << "<ma_floatCodes>"
       << "<ma_floatCode label=\"GLI\">0</ma_floatCode>"
       << "</ma_floatCodes>"
       << "<ma_lengthXCells>8</ma_lengthXCells>"
       << "<ma_lengthYCells>8</ma_lengthYCells>"
       << "</grid>"
       << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>QuadratLight</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Seedling\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>GLILight</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>2</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "</behavior>"
       << "</behaviorList>"
       << "<GeneralLight>"
       << "<li_beamFractGlobalRad>0.5</li_beamFractGlobalRad>"
       << "<li_clearSkyTransCoeff>0.65</li_clearSkyTransCoeff>"
       << "<li_julianDayGrowthStarts>105</li_julianDayGrowthStarts>"
       << "<li_julianDayGrowthEnds>258</li_julianDayGrowthEnds>"
       << "<li_lightExtinctionCoefficient>"
       << "<li_lecVal species=\"Species_1\">0.2</li_lecVal>"
       << "</li_lightExtinctionCoefficient>"
       << "</GeneralLight>"
       << "<GLILight2>"
       << "<li_minSunAngle>0.785</li_minSunAngle>"
       << "<li_numAltGrids>12</li_numAltGrids>"
       << "<li_numAziGrids>18</li_numAziGrids>"
       << "</GLILight2>"
       << "<QuadratLight1>"
       << "<li_minSunAngle>0.785</li_minSunAngle>"
       << "<li_numAltGrids>12</li_numAltGrids>"
       << "<li_numAziGrids>18</li_numAziGrids>"
       << "<li_quadratLightHeight>2</li_quadratLightHeight>"
       << "<li_quadratAllGLIs>0</li_quadratAllGLIs>"
       << "</QuadratLight1>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteQuadratGLILightXMLFile4()
////////////////////////////////////////////////////////////////////////////
const char* WriteQuadratGLILightXMLFile4() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  WriteQuadratGLILightCommonStuff(oOut);

  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>GLILight</behaviorName>"
       << "<listPosition>1</listPosition>"
       << "<version>1</version>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>QuadratLight</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>2</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Seedling\"/>"
       << "</behavior>"
       << "</behaviorList>"
       << "<GeneralLight>"
       << "<li_beamFractGlobalRad>0.5</li_beamFractGlobalRad>"
       << "<li_clearSkyTransCoeff>0.65</li_clearSkyTransCoeff>"
       << "<li_julianDayGrowthStarts>105</li_julianDayGrowthStarts>"
       << "<li_julianDayGrowthEnds>258</li_julianDayGrowthEnds>"
       << "<li_lightExtinctionCoefficient>"
       << "<li_lecVal species=\"Species_1\">0.2</li_lecVal>"
       << "<li_lecVal species=\"Species_2\">0.2</li_lecVal>"
       << "</li_lightExtinctionCoefficient>"
       << "</GeneralLight>"
       << "<GLILight1>"
       << "<li_minSunAngle>0.785</li_minSunAngle>"
       << "<li_numAltGrids>12</li_numAltGrids>"
       << "<li_numAziGrids>18</li_numAziGrids>"
       << "</GLILight1>"
       << "<QuadratLight2>"
       << "<li_minSunAngle>0.785</li_minSunAngle>"
       << "<li_numAltGrids>10</li_numAltGrids>"
       << "<li_numAziGrids>20</li_numAziGrids>"
       << "<li_quadratLightHeight>1</li_quadratLightHeight>"
       << "<li_quadratAllGLIs>0</li_quadratAllGLIs>"
       << "</QuadratLight2>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteQuadratGLILightXMLFile5()
////////////////////////////////////////////////////////////////////////////
const char* WriteQuadratGLILightXMLFile5() {
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
       << "<plot_lenX>100.0</plot_lenX>"
       << "<plot_lenY>100.0</plot_lenY>"
       << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
       << "<plot_temp_C>12.88171785</plot_temp_C>"
       << "<plot_latitude>55.37</plot_latitude>"
       << "</plot>"
       << "<trees>"
       << "<tr_speciesList>"
       << "<tr_species speciesName=\"Species_1\" />"
       << "</tr_speciesList>"
       << "<tr_minAdultDBH>"
       << "<tr_madVal species=\"Species_1\">10.0</tr_madVal>"
       << "</tr_minAdultDBH>"
       << "<tr_maxSeedlingHeight>"
       << "<tr_mshVal species=\"Species_1\">1.35</tr_mshVal>"
       << "</tr_maxSeedlingHeight>";

  oOut << "<tr_sizeClasses>"
       << "<tr_sizeClass sizeKey=\"s15.0\" />"
       << "<tr_sizeClass sizeKey=\"s20.0\" />"
       << "<tr_sizeClass sizeKey=\"s30.0\" />"
       << "</tr_sizeClasses>"
       << "<tr_initialDensities>"
       << "<tr_idVals whatSpecies=\"Species_1\">"
       << "<tr_initialDensity sizeClass=\"s20.0\">50.0</tr_initialDensity>"
       << "</tr_idVals>"
       << "</tr_initialDensities>"
       << "<tr_seedDiam10Cm>0.1</tr_seedDiam10Cm>"
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
       << "<tr_sachVal species=\"Species_1\">0.589</tr_sachVal>"
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
       << "</tr_whatAdultHeightDiam>"
       << "</allometry>";

  //Write file
  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>QuadratLight</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Seedling\"/>"
       << "</behavior>"
       << "</behaviorList>"
       << "<GeneralLight>"
       << "<li_beamFractGlobalRad>0.5</li_beamFractGlobalRad>"
       << "<li_clearSkyTransCoeff>0.65</li_clearSkyTransCoeff>"
       << "<li_julianDayGrowthStarts>105</li_julianDayGrowthStarts>"
       << "<li_julianDayGrowthEnds>258</li_julianDayGrowthEnds>"
       << "<li_lightExtinctionCoefficient>"
       << "<li_lecVal species=\"Species_1\">0.2</li_lecVal>"
       << "</li_lightExtinctionCoefficient>"
       << "</GeneralLight>"
       << "<QuadratLight1>"
       << "<li_minSunAngle>0.785</li_minSunAngle>"
       << "<li_numAltGrids>12</li_numAltGrids>"
       << "<li_numAziGrids>18</li_numAziGrids>"
       << "<li_quadratLightHeight>2</li_quadratLightHeight>"
       << "<li_quadratAllGLIs>1</li_quadratAllGLIs>"
       << "</QuadratLight1>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}


////////////////////////////////////////////////////////////////////////////
// WriteQuadratGLILightXMLErrorFile1()
////////////////////////////////////////////////////////////////////////////
const char* WriteQuadratGLILightXMLErrorFile1() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  WriteQuadratGLILightCommonStuff(oOut);

  //Write file
  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>QuadratLight</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "</behavior>"
       << "</behaviorList>"
       << "<GeneralLight>"
       << "<li_beamFractGlobalRad>0.5</li_beamFractGlobalRad>"
       << "<li_clearSkyTransCoeff>0.65</li_clearSkyTransCoeff>"
       << "<li_julianDayGrowthStarts>105</li_julianDayGrowthStarts>"
       << "<li_julianDayGrowthEnds>258</li_julianDayGrowthEnds>"
       << "<li_lightExtinctionCoefficient>"
       << "<li_lecVal species=\"Species_1\">0.2</li_lecVal>"
       << "<li_lecVal species=\"Species_2\">0.2</li_lecVal>"
       << "</li_lightExtinctionCoefficient>"
       << "</GeneralLight>"
       << "<QuadratLight1>"
       << "<li_minSunAngle>0.785</li_minSunAngle>"
       << "<li_numAltGrids>12</li_numAltGrids>"
       << "<li_numAziGrids>-18</li_numAziGrids>"
       << "<li_quadratLightHeight>2</li_quadratLightHeight>"
       << "<li_quadratAllGLIs>0</li_quadratAllGLIs>"
       << "</QuadratLight1>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteQuadratGLILightXMLErrorFile2()
////////////////////////////////////////////////////////////////////////////
const char* WriteQuadratGLILightXMLErrorFile2() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  WriteQuadratGLILightCommonStuff(oOut);

  //Write file
  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>QuadratLight</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "</behavior>"
       << "</behaviorList>"
       << "<GeneralLight>"
       << "<li_beamFractGlobalRad>0.5</li_beamFractGlobalRad>"
       << "<li_clearSkyTransCoeff>0.65</li_clearSkyTransCoeff>"
       << "<li_julianDayGrowthStarts>105</li_julianDayGrowthStarts>"
       << "<li_julianDayGrowthEnds>258</li_julianDayGrowthEnds>"
       << "<li_lightExtinctionCoefficient>"
       << "<li_lecVal species=\"Species_1\">0.2</li_lecVal>"
       << "<li_lecVal species=\"Species_2\">0.2</li_lecVal>"
       << "</li_lightExtinctionCoefficient>"
       << "</GeneralLight>"
       << "<QuadratLight1>"
       << "<li_minSunAngle>0.785</li_minSunAngle>"
       << "<li_numAltGrids>0</li_numAltGrids>"
       << "<li_numAziGrids>18</li_numAziGrids>"
       << "<li_quadratLightHeight>2</li_quadratLightHeight>"
       << "<li_quadratAllGLIs>0</li_quadratAllGLIs>"
       << "</QuadratLight1>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteQuadratGLILightXMLErrorFile3()
////////////////////////////////////////////////////////////////////////////
const char* WriteQuadratGLILightXMLErrorFile3() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  WriteQuadratGLILightCommonStuff(oOut);

  //Write file
  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>QuadratLight</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "</behavior>"
       << "</behaviorList>"
       << "<GeneralLight>"
       << "<li_beamFractGlobalRad>0.5</li_beamFractGlobalRad>"
       << "<li_clearSkyTransCoeff>0.65</li_clearSkyTransCoeff>"
       << "<li_julianDayGrowthStarts>105</li_julianDayGrowthStarts>"
       << "<li_julianDayGrowthEnds>258</li_julianDayGrowthEnds>"
       << "<li_lightExtinctionCoefficient>"
       << "<li_lecVal species=\"Species_1\">0.2</li_lecVal>"
       << "<li_lecVal species=\"Species_2\">0.2</li_lecVal>"
       << "</li_lightExtinctionCoefficient>"
       << "</GeneralLight>"
       << "<QuadratLight1>"
       << "<li_minSunAngle>0.785</li_minSunAngle>"
       << "<li_numAltGrids>12</li_numAltGrids>"
       << "<li_numAziGrids>18</li_numAziGrids>"
       << "<li_quadratLightHeight>-1</li_quadratLightHeight>"
       << "<li_quadratAllGLIs>0</li_quadratAllGLIs>"
       << "</QuadratLight1>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteQuadratGLILightCommonStuff()
/////////////////////////////////////////////////////////////////////////////
void WriteQuadratGLILightCommonStuff( std::fstream &oOut )
{
  using namespace std;
  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06010101\">"
       << "<plot>"
       << "<timesteps>1</timesteps>"
       << "<yearsPerTimestep>1</yearsPerTimestep>"
       << "<randomSeed>1</randomSeed>"
       << "<plot_lenX>100.0</plot_lenX>"
       << "<plot_lenY>100.0</plot_lenY>"
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
        << "<tr_interceptDiam10ToDBH>"
       << "<tr_idtdVal species=\"Species_1\">0</tr_idtdVal>"
       << "<tr_idtdVal species=\"Species_2\">0</tr_idtdVal>"
       << "</tr_interceptDiam10ToDBH>"
       << "<tr_stdAsympCrownHt>"
       << "<tr_sachVal species=\"Species_1\">0.589</tr_sachVal>"
       << "<tr_sachVal species=\"Species_2\">0.589</tr_sachVal>"
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
       << "</allometry>";
}

