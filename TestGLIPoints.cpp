//---------------------------------------------------------------------------
#include "TestGLIPoints.h"
#include <gtest/gtest.h>
#include <fstream>
#include <math.h>

#include "TreePopulation.h"
#include "TreeSearch.h"
#include "SimManager.h"
//---------------------------------------------------------------------------

/////////////////////////////////////////////////////////////////////////////
// TestNormalProcessing()
// Tests normal processing calculations. WriteGLIPointsXMLFile1() is used for
// setup. This only has one behavior, GLI points. It is run. Then this will read
// in the output file and test the values.
/////////////////////////////////////////////////////////////////////////////
TEST(GLIPoints, TestNormalProcessing) {
  using namespace std;
  float fX, fY, fExpectedX, fExpectedY, fDiam, fHeight, fExpectedHeight, fGLI, fExpectedGLI;
  char* m_sFileName = new char[20];
  strcpy(m_sFileName, "testout.txt");

  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {

    //Clean out that file
    fstream oFile;
    oFile.open(m_sFileName, ios::out | ios::trunc);
    oFile.close();

    //Feed our file to the sim manager
    p_oSimManager->ReadFile(WriteGLIPointsXMLFile1());
    clTreePopulation *p_oPop = (clTreePopulation*) p_oSimManager->GetPopulationObject("treepopulation");

    //Create our trees
    fX = 56.1;
    fY = 50;
    fDiam = 45;
    p_oPop->CreateTree (fX, fY, 0, clTreePopulation::adult, fDiam);

    fX = 187;
    fY = 190;
    fDiam = 140;
    p_oPop->CreateTree (fX, fY, 0, clTreePopulation::adult, fDiam);

    fX = 10;
    fY = 185;
    fDiam = 40;
    p_oPop->CreateTree (fX, fY, 0, clTreePopulation::adult, fDiam);

    fX = 11;
    fY = 11;
    fDiam = 45;
    p_oPop->CreateTree (fX, fY, 0, clTreePopulation::adult, fDiam);

    fX = 155;
    fY = 21.5;
    fDiam = 56;
    p_oPop->CreateTree (fX, fY, 0, clTreePopulation::adult, fDiam);

    fX = 147;
    fY = 8;
    fDiam = 62;
    p_oPop->CreateTree (fX, fY, 0, clTreePopulation::adult, fDiam);

    fX = 147;
    fY = 17;
    fDiam = 57;
    p_oPop->CreateTree (fX, fY, 0, clTreePopulation::adult, fDiam);

    fX = 9;
    fY = 4;
    fDiam = 61;
    p_oPop->CreateTree (fX, fY, 0, clTreePopulation::adult, fDiam);

    fX = 1;
    fY = 199;
    fDiam = 41;
    p_oPop->CreateTree (fX, fY, 0, clTreePopulation::adult, fDiam);

    fX = 51;
    fY = 57;
    fDiam = 15;
    p_oPop->CreateTree (fX, fY, 0, clTreePopulation::adult, fDiam);

    fX = 59;
    fY = 57;
    fDiam = 45;
    p_oPop->CreateTree (fX, fY, 0, clTreePopulation::adult, fDiam);

    //Run a timestep
    p_oSimManager->RunSim(1);

    //Read in the output file
    FILE *fp_in = fopen(m_sFileName, "rt");
    ASSERT_TRUE(fp_in != NULL);

    //First 4 lines - skip
    char testch = fgetc(fp_in);
    while(testch != '\n' && testch != EOF)
      testch = fgetc(fp_in);
    testch = fgetc(fp_in);
    while(testch != '\n' && testch != EOF)
      testch = fgetc(fp_in);
    testch = fgetc(fp_in);
    while(testch != '\n' && testch != EOF)
      testch = fgetc(fp_in);
    testch = fgetc(fp_in);
    while(testch != '\n' && testch != EOF)
      testch = fgetc(fp_in);

    //First point
    fExpectedX = 75;
    fExpectedY = 80;
    fExpectedHeight = 15.13074207;
    fExpectedGLI = 100;
    fscanf(fp_in, "%f", &fX);
    fscanf(fp_in, "%f", &fY);
    fscanf(fp_in, "%f", &fHeight);
    fscanf(fp_in, "%f", &fGLI);
    EXPECT_LT(fabs(fExpectedX - fX), 0.1);
    EXPECT_LT(fabs(fExpectedY - fY), 0.1);
    EXPECT_LT(fabs(fExpectedGLI - fGLI), 0.1);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.1);
    testch = fgetc(fp_in);
    while(testch != '\n' && testch != EOF)   //throw away extra tab characters
      testch = fgetc(fp_in);

    //Second point
    fExpectedX = 50;
    fExpectedY = 50;
    fExpectedHeight = 12.03726764;
    fExpectedGLI = 90.4544612;
    fscanf(fp_in, "%f", &fX);
    fscanf(fp_in, "%f", &fY);
    fscanf(fp_in, "%f", &fHeight);
    fscanf(fp_in, "%f", &fGLI);
    EXPECT_LT(fabs(fExpectedX - fX), 0.1);
    EXPECT_LT(fabs(fExpectedY - fY), 0.1);
    EXPECT_LT(fabs(fExpectedGLI - fGLI), 0.1);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.1);
    testch = fgetc(fp_in);
    while(testch != '\n' && testch != EOF)   //throw away extra tab characters
      testch = fgetc(fp_in);

    //Third point
    fExpectedX = 190;
    fExpectedY = 193;
    fExpectedHeight = 5.648193732;
    fExpectedGLI = 38.9158116;
    fscanf(fp_in, "%f", &fX);
    fscanf(fp_in, "%f", &fY);
    fscanf(fp_in, "%f", &fHeight);
    fscanf(fp_in, "%f", &fGLI);
    EXPECT_LT(fabs(fExpectedX - fX), 0.1);
    EXPECT_LT(fabs(fExpectedY - fY), 0.1);
    EXPECT_LT(fabs(fExpectedGLI - fGLI), 0.1);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.1);
    testch = fgetc(fp_in);
    while(testch != '\n' && testch != EOF)   //throw away extra tab characters
      testch = fgetc(fp_in);

    //Fourth point
    fExpectedX = 10;
    fExpectedY = 10;
    fExpectedHeight = 15.13074207;
    fExpectedGLI = 13.68761304;
    fscanf(fp_in, "%f", &fX);
    fscanf(fp_in, "%f", &fY);
    fscanf(fp_in, "%f", &fHeight);
    fscanf(fp_in, "%f", &fGLI);
    EXPECT_LT(fabs(fExpectedX - fX), 0.1);
    EXPECT_LT(fabs(fExpectedY - fY), 0.1);
    EXPECT_LT(fabs(fExpectedGLI - fGLI), 0.1);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.1);
    testch = fgetc(fp_in);
    while(testch != '\n' && testch != EOF)   //throw away extra tab characters
      testch = fgetc(fp_in);

    //Fifth point
    fExpectedX = 156;
    fExpectedY = 15;
    fExpectedHeight = 17.21977678;
    fExpectedGLI = 81.9849348;
    fscanf(fp_in, "%f", &fX);
    fscanf(fp_in, "%f", &fY);
    fscanf(fp_in, "%f", &fHeight);
    fscanf(fp_in, "%f", &fGLI);
    EXPECT_LT(fabs(fExpectedX - fX), 0.1);
    EXPECT_LT(fabs(fExpectedY - fY), 0.1);
    EXPECT_LT(fabs(fExpectedGLI - fGLI), 0.1);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.1);
    testch = fgetc(fp_in);
    while(testch != '\n' && testch != EOF)   //throw away extra tab characters
      testch = fgetc(fp_in);

    //Sixth point
    fExpectedX = 12;
    fExpectedY = 194;
    fExpectedHeight = 9.461874761;
    fExpectedGLI = 79.96579752;
    fscanf(fp_in, "%f", &fX);
    fscanf(fp_in, "%f", &fY);
    fscanf(fp_in, "%f", &fHeight);
    fscanf(fp_in, "%f", &fGLI);
    EXPECT_LT(fabs(fExpectedX - fX), 0.1);
    EXPECT_LT(fabs(fExpectedY - fY), 0.1);
    EXPECT_LT(fabs(fExpectedGLI - fGLI), 0.1);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.1);
    testch = fgetc(fp_in);
    while(testch != '\n' && testch != EOF)   //throw away extra tab characters
      testch = fgetc(fp_in);

    fclose(fp_in);
    delete[] m_sFileName;
    delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

/////////////////////////////////////////////////////////////////////////////
// TestRotatedSky()
// Tests normal processing calculations when the sky is rotated. We will have
// a line of points running north to south. In the first calculation, the
// azimuth of north is 0. In the second, it's 180. The GLI values running north
// to south will equal the points running south to north in the second calculation.
/////////////////////////////////////////////////////////////////////////////
TEST(GLIPoints, TestRotatedSky) {
  using namespace std;
  float fX, fY, fExpectedX, fExpectedY, fDiam, fHeight, fExpectedHeight,
  fPoint1_1, fPoint1_2,
  fPoint2_1, fPoint2_2,
  fPoint3_1, fPoint3_2,
  fPoint4_1, fPoint4_2,
  fPoint5_1, fPoint5_2;
  int i;

  char* m_sFileName = new char[20];
  strcpy(m_sFileName, "testout.txt");

  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {

    //Clean out that file
    fstream oFile;
    oFile.open(m_sFileName, ios::out | ios::trunc);
    oFile.close();

    //Feed our first file to the sim manager - the one where azimuth is north
    p_oSimManager->ReadFile(WriteGLIPointsXMLRotateFile1());
    clTreePopulation *p_oPop = (clTreePopulation*) p_oSimManager->GetPopulationObject("treepopulation");

    //Create our trees
    fX = 90;
    fY = 80;
    fDiam = 10;
//    for (i = 0; i < 5; i++) {
      p_oPop->CreateTree (fX, fY, 0, clTreePopulation::adult, fDiam);
      fY += 10;
//    }

    fX = 110;
    fY = 80;
    fDiam = 10;
//    for (i = 0; i < 5; i++) {
      p_oPop->CreateTree (fX, fY, 0, clTreePopulation::adult, fDiam);
      fY += 10;
//    }

    //Run a timestep
    p_oSimManager->RunSim(1);

    //Read in the output file
    FILE *fp_in = fopen(m_sFileName, "rt");
    ASSERT_TRUE(fp_in != NULL);

    //First 4 lines - skip
    char testch = fgetc(fp_in);
    while(testch != '\n' && testch != EOF)
      testch = fgetc(fp_in);
    testch = fgetc(fp_in);
    while(testch != '\n' && testch != EOF)
      testch = fgetc(fp_in);
    testch = fgetc(fp_in);
    while(testch != '\n' && testch != EOF)
      testch = fgetc(fp_in);
    testch = fgetc(fp_in);
    while(testch != '\n' && testch != EOF)
      testch = fgetc(fp_in);

    //First point
    fExpectedX = 100;
    fExpectedY = 80;
    fExpectedHeight = 2;
    fscanf(fp_in, "%f", &fX);
    fscanf(fp_in, "%f", &fY);
    fscanf(fp_in, "%f", &fHeight);
    fscanf(fp_in, "%f", &fPoint1_1);
    EXPECT_LT(fabs(fExpectedX - fX), 0.1);
    EXPECT_LT(fabs(fExpectedY - fY), 0.1);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.1);

    testch = fgetc(fp_in);
    while(testch != '\n' && testch != EOF)   //throw away extra tab characters
      testch = fgetc(fp_in);

    //Second point
    fExpectedX = 100;
    fExpectedY = 90;
    fExpectedHeight = 2;
    fscanf(fp_in, "%f", &fX);
    fscanf(fp_in, "%f", &fY);
    fscanf(fp_in, "%f", &fHeight);
    fscanf(fp_in, "%f", &fPoint2_1);
    EXPECT_LT(fabs(fExpectedX - fX), 0.1);
    EXPECT_LT(fabs(fExpectedY - fY), 0.1);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.1);
    testch = fgetc(fp_in);
    while(testch != '\n' && testch != EOF)   //throw away extra tab characters
      testch = fgetc(fp_in);

    //Third point
    fExpectedX = 100;
    fExpectedY = 100;
    fExpectedHeight = 2;
    fscanf(fp_in, "%f", &fX);
    fscanf(fp_in, "%f", &fY);
    fscanf(fp_in, "%f", &fHeight);
    fscanf(fp_in, "%f", &fPoint3_1);
    EXPECT_LT(fabs(fExpectedX - fX), 0.1);
    EXPECT_LT(fabs(fExpectedY - fY), 0.1);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.1);
    testch = fgetc(fp_in);
    while(testch != '\n' && testch != EOF)   //throw away extra tab characters
      testch = fgetc(fp_in);

    //Fourth point
    fExpectedX = 100;
    fExpectedY = 110;
    fExpectedHeight = 2;
    fscanf(fp_in, "%f", &fX);
    fscanf(fp_in, "%f", &fY);
    fscanf(fp_in, "%f", &fHeight);
    fscanf(fp_in, "%f", &fPoint4_1);
    EXPECT_LT(fabs(fExpectedX - fX), 0.1);
    EXPECT_LT(fabs(fExpectedY - fY), 0.1);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.1);
    testch = fgetc(fp_in);
    while(testch != '\n' && testch != EOF)   //throw away extra tab characters
      testch = fgetc(fp_in);

    //Fifth point
    fExpectedX = 100;
    fExpectedY = 120;
    fExpectedHeight = 2;
    fscanf(fp_in, "%f", &fX);
    fscanf(fp_in, "%f", &fY);
    fscanf(fp_in, "%f", &fHeight);
    fscanf(fp_in, "%f", &fPoint5_1);
    EXPECT_LT(fabs(fExpectedX - fX), 0.1);
    EXPECT_LT(fabs(fExpectedY - fY), 0.1);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.1);
    testch = fgetc(fp_in);
    while(testch != '\n' && testch != EOF)   //throw away extra tab characters
      testch = fgetc(fp_in);

    fclose(fp_in);

    //**************************************************
    //Do the second file
    //**************************************************

    //Clean out that file
    oFile.open(m_sFileName, ios::out | ios::trunc);
    oFile.close();

    p_oSimManager->ReadFile(WriteGLIPointsXMLRotateFile2());
    p_oPop = (clTreePopulation*) p_oSimManager->GetPopulationObject("treepopulation");

    //Create our trees
    fX = 40;
    fY = 30;
    fDiam = 10;
    for (i = 0; i < 5; i++) {
      p_oPop->CreateTree (fX, fY, 0, clTreePopulation::adult, fDiam);
      fY += 10;
    }

    fX = 60;
    fY = 30;
    fDiam = 10;
    for (i = 0; i < 5; i++) {
      p_oPop->CreateTree (fX, fY, 0, clTreePopulation::adult, fDiam);
      fY += 10;
    }

    //Run a timestep
    p_oSimManager->RunSim(1);

    //Read in the output file
    fp_in = fopen(m_sFileName, "rt");
    ASSERT_TRUE(fp_in != NULL);

    //First 4 lines - skip
    testch = fgetc(fp_in);
    while(testch != '\n' && testch != EOF)
      testch = fgetc(fp_in);
    testch = fgetc(fp_in);
    while(testch != '\n' && testch != EOF)
      testch = fgetc(fp_in);
    testch = fgetc(fp_in);
    while(testch != '\n' && testch != EOF)
      testch = fgetc(fp_in);
    testch = fgetc(fp_in);
    while(testch != '\n' && testch != EOF)
      testch = fgetc(fp_in);

    //First point
    fExpectedX = 100;
    fExpectedY = 80;
    fExpectedHeight = 2;
    fscanf(fp_in, "%f", &fX);
    fscanf(fp_in, "%f", &fY);
    fscanf(fp_in, "%f", &fHeight);
    fscanf(fp_in, "%f", &fPoint1_2);
    EXPECT_LT(fabs(fExpectedX - fX), 0.1);
    EXPECT_LT(fabs(fExpectedY - fY), 0.1);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.1);

    testch = fgetc(fp_in);
    while(testch != '\n' && testch != EOF)   //throw away extra tab characters
      testch = fgetc(fp_in);

    //Second point
    fExpectedX = 100;
    fExpectedY = 90;
    fExpectedHeight = 2;
    fscanf(fp_in, "%f", &fX);
    fscanf(fp_in, "%f", &fY);
    fscanf(fp_in, "%f", &fHeight);
    fscanf(fp_in, "%f", &fPoint2_2);
    EXPECT_LT(fabs(fExpectedX - fX), 0.1);
    EXPECT_LT(fabs(fExpectedY - fY), 0.1);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.1);
    testch = fgetc(fp_in);
    while(testch != '\n' && testch != EOF)   //throw away extra tab characters
      testch = fgetc(fp_in);

    //Third point
    fExpectedX = 100;
    fExpectedY = 100;
    fExpectedHeight = 2;
    fscanf(fp_in, "%f", &fX);
    fscanf(fp_in, "%f", &fY);
    fscanf(fp_in, "%f", &fHeight);
    fscanf(fp_in, "%f", &fPoint3_2);
    EXPECT_LT(fabs(fExpectedX - fX), 0.1);
    EXPECT_LT(fabs(fExpectedY - fY), 0.1);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.1);
    testch = fgetc(fp_in);
    while(testch != '\n' && testch != EOF)   //throw away extra tab characters
      testch = fgetc(fp_in);

    //Fourth point
    fExpectedX = 100;
    fExpectedY = 110;
    fExpectedHeight = 2;
    fscanf(fp_in, "%f", &fX);
    fscanf(fp_in, "%f", &fY);
    fscanf(fp_in, "%f", &fHeight);
    fscanf(fp_in, "%f", &fPoint4_2);
    EXPECT_LT(fabs(fExpectedX - fX), 0.1);
    EXPECT_LT(fabs(fExpectedY - fY), 0.1);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.1);
    testch = fgetc(fp_in);
    while(testch != '\n' && testch != EOF)   //throw away extra tab characters
      testch = fgetc(fp_in);

    //Fifth point
    fExpectedX = 100;
    fExpectedY = 120;
    fExpectedHeight = 2;
    fscanf(fp_in, "%f", &fX);
    fscanf(fp_in, "%f", &fY);
    fscanf(fp_in, "%f", &fHeight);
    fscanf(fp_in, "%f", &fPoint5_2);
    EXPECT_LT(fabs(fExpectedX - fX), 0.1);
    EXPECT_LT(fabs(fExpectedY - fY), 0.1);
    EXPECT_LT(fabs(fExpectedHeight - fHeight), 0.1);
    testch = fgetc(fp_in);
    while(testch != '\n' && testch != EOF)   //throw away extra tab characters
      testch = fgetc(fp_in);

    fclose(fp_in);

    // Check to see if the points values north to south for the first file are the
    // same as the values south to north in the second file
    EXPECT_LT(fabs(fPoint1_1 - fPoint1_2), 0.01);
    EXPECT_LT(fabs(fPoint2_1 - fPoint2_2), 0.01);
    EXPECT_LT(fabs(fPoint3_1 - fPoint3_2), 0.01);
    EXPECT_LT(fabs(fPoint4_1 - fPoint4_2), 0.01);
    EXPECT_LT(fabs(fPoint5_1 - fPoint5_2), 0.01);

    delete[] m_sFileName;
    delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}


////////////////////////////////////////////////////////////////////////////
// TestErrorProcessing()
////////////////////////////////////////////////////////////////////////////
TEST(GLIPoints, TestErrorProcessing) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  //Feed our error file to the sim manager
  try
  {
    p_oSimManager->ReadFile(WriteGLIPointsXMLErrorFile1());
    FAIL() << "TestGLIPoints error processing didn't catch error for WriteGLIPointsXMLErrorFile1.";
  }
  catch (modelErr& err)
  {
    if (err.sFunction.compare("clGLIPoints::ReadParameterFileData") != 0)
    {
      FAIL() << "TestGLIPoints error processing caught wrong error for WriteGLIPointsXMLErrorFile1.";
    }
    ;
  }

  try
  {
    p_oSimManager->ReadFile(WriteGLIPointsXMLErrorFile2());
    FAIL() << "TestGLIPoints error processing didn't catch error for WriteGLIPointsXMLErrorFile2.";
  }
  catch (modelErr& err)
  {
    if (err.sFunction.compare("clGLIPoints::ReadParameterFileData") != 0)
    {
      FAIL() << "TestGLIPoints error processing caught wrong error for WriteGLIPointsXMLErrorFile2.";
    }
    ;
  }

  try
  {
    p_oSimManager->ReadFile(WriteGLIPointsXMLErrorFile3());
    FAIL() << "TestGLIPoints error processing didn't catch error for WriteGLIPointsXMLErrorFile3.";
  }
  catch (modelErr& err)
  {
    if (err.sFunction.compare("clGLIPoints::ReadParameterFileData") != 0)
    {
      FAIL() << "TestGLIPoints error processing caught wrong error for WriteGLIPointsXMLErrorFile3.";
    }
    ;
  }

  try
  {
    p_oSimManager->ReadFile(WriteGLIPointsXMLErrorFile4());
    FAIL() << "TestGLIPoints error processing didn't catch error for WriteGLIPointsXMLErrorFile4.";
  }
  catch (modelErr& err)
  {
    if (err.sFunction.compare("clGLIPoints::ReadParameterFileData") != 0)
    {
      FAIL() << "TestGLIPoints error processing caught wrong error for WriteGLIPointsXMLErrorFile4.";
    }
    ;
  }

  try
  {
    p_oSimManager->ReadFile(WriteGLIPointsXMLErrorFile5());
    FAIL() << "TestGLIPoints error processing didn't catch error for WriteGLIPointsXMLErrorFile5.";
  }
  catch (modelErr& err)
  {
    if (err.sFunction.compare("clGLIPoints::ReadParameterFileData") != 0)
    {
      FAIL() << "TestGLIPoints error processing caught wrong error for WriteGLIPointsXMLErrorFile5.";
    }
    ;
  }
  delete p_oSimManager;
}

////////////////////////////////////////////////////////////////////////////
// WriteGLIPointsXMLFile1()
////////////////////////////////////////////////////////////////////////////
const char* WriteGLIPointsXMLFile1() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  //Write file
  WriteGLIPointsCommonStuff(oOut);

  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>GLIPointCreator</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "</behavior>"
       << "</behaviorList>"
       << "<GLIPointCreator1>"
       << "<li_beamFractGlobalRad>0.5</li_beamFractGlobalRad>"
       << "<li_clearSkyTransCoeff>0.65</li_clearSkyTransCoeff>"
       << "<li_julianDayGrowthStarts>105</li_julianDayGrowthStarts>"
       << "<li_julianDayGrowthEnds>258</li_julianDayGrowthEnds>"
       << "<li_minSunAngle>0.785</li_minSunAngle>"
       << "<li_numAltGrids>12</li_numAltGrids>"
       << "<li_numAziGrids>18</li_numAziGrids>"
       << "<li_lightExtinctionCoefficient>"
       << "<li_lecVal species=\"Species_1\">0.2</li_lecVal>"
       << "</li_lightExtinctionCoefficient>"
       << "<li_GLIPointsFilename>testout.txt</li_GLIPointsFilename>"
       << "<li_GLIPoint x=\"75\" y=\"80\" h=\"15.13074207\"/>"
       << "<li_GLIPoint x=\"50\" y=\"50\" h=\"12.03726764\"/>"
       << "<li_GLIPoint x=\"190\" y=\"193\" h=\"5.648193732\"/>"
       << "<li_GLIPoint x=\"10\" y=\"10\" h=\"15.13074207\"/>"
       << "<li_GLIPoint x=\"156\" y=\"15\" h=\"17.21977678\"/>"
       << "<li_GLIPoint x=\"12\" y=\"194\" h=\"9.461874761\"/>"
       << "</GLIPointCreator1>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteGLIPointsXMLRotateFile1()
////////////////////////////////////////////////////////////////////////////
const char* WriteGLIPointsXMLRotateFile1() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  //Write file
  WriteGLIPointsCommonStuff(oOut);

  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>GLIPointCreator</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "</behavior>"
       << "</behaviorList>"
       << "<GLIPointCreator1>"
       << "<li_beamFractGlobalRad>0.5</li_beamFractGlobalRad>"
       << "<li_clearSkyTransCoeff>0.65</li_clearSkyTransCoeff>"
       << "<li_julianDayGrowthStarts>105</li_julianDayGrowthStarts>"
       << "<li_julianDayGrowthEnds>258</li_julianDayGrowthEnds>"
       << "<li_minSunAngle>0.785</li_minSunAngle>"
       << "<li_numAltGrids>12</li_numAltGrids>"
       << "<li_numAziGrids>18</li_numAziGrids>"
       << "<li_AziOfNorth>0</li_AziOfNorth>"
       << "<li_lightExtinctionCoefficient>"
       << "<li_lecVal species=\"Species_1\">0.2</li_lecVal>"
       << "</li_lightExtinctionCoefficient>"
       << "<li_GLIPointsFilename>testout.txt</li_GLIPointsFilename>"
       << "<li_GLIPoint x=\"100\" y=\"80\" h=\"2\"/>"
       << "<li_GLIPoint x=\"100\" y=\"90\" h=\"2\"/>"
       << "<li_GLIPoint x=\"100\" y=\"100\" h=\"2\"/>"
       << "<li_GLIPoint x=\"100\" y=\"110\" h=\"2\"/>"
       << "<li_GLIPoint x=\"100\" y=\"120\" h=\"2\"/>"
       << "</GLIPointCreator1>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteGLIPointsXMLRotateFile2()
////////////////////////////////////////////////////////////////////////////
const char* WriteGLIPointsXMLRotateFile2() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  //Write file
  WriteGLIPointsCommonStuff(oOut);

  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>GLIPointCreator</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "</behavior>"
       << "</behaviorList>"
       << "<GLIPointCreator1>"
       << "<li_beamFractGlobalRad>0.5</li_beamFractGlobalRad>"
       << "<li_clearSkyTransCoeff>0.65</li_clearSkyTransCoeff>"
       << "<li_julianDayGrowthStarts>105</li_julianDayGrowthStarts>"
       << "<li_julianDayGrowthEnds>258</li_julianDayGrowthEnds>"
       << "<li_minSunAngle>0.785</li_minSunAngle>"
       << "<li_numAltGrids>12</li_numAltGrids>"
       << "<li_numAziGrids>18</li_numAziGrids>"
       << "<li_AziOfNorth>3.14159</li_AziOfNorth>"
       << "<li_lightExtinctionCoefficient>"
       << "<li_lecVal species=\"Species_1\">0.2</li_lecVal>"
       << "</li_lightExtinctionCoefficient>"
       << "<li_GLIPointsFilename>testout.txt</li_GLIPointsFilename>"
       << "<li_GLIPoint x=\"100\" y=\"80\" h=\"2\"/>"
       << "<li_GLIPoint x=\"100\" y=\"90\" h=\"2\"/>"
       << "<li_GLIPoint x=\"100\" y=\"100\" h=\"2\"/>"
       << "<li_GLIPoint x=\"100\" y=\"110\" h=\"2\"/>"
       << "<li_GLIPoint x=\"100\" y=\"120\" h=\"2\"/>"
       << "</GLIPointCreator1>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteGLIPointsXMLErrorFile2()
////////////////////////////////////////////////////////////////////////////
const char* WriteGLIPointsXMLErrorFile2() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  //Write file
  WriteGLIPointsCommonStuff(oOut);

  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>GLIPointCreator</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "</behavior>"
       << "</behaviorList>"
       << "<GLIPointCreator1>"
       << "<li_beamFractGlobalRad>0.5</li_beamFractGlobalRad>"
       << "<li_clearSkyTransCoeff>0.65</li_clearSkyTransCoeff>"
       << "<li_julianDayGrowthStarts>105</li_julianDayGrowthStarts>"
       << "<li_julianDayGrowthEnds>258</li_julianDayGrowthEnds>"
       << "<li_minSunAngle>0.785</li_minSunAngle>"
       << "<li_numAltGrids>12</li_numAltGrids>"
       << "<li_numAziGrids>-18</li_numAziGrids>"
       << "<li_lightExtinctionCoefficient>"
       << "<li_lecVal species=\"Species_1\">0.2</li_lecVal>"
       << "</li_lightExtinctionCoefficient>"
       << "<li_GLIPointsFilename>testout.txt</li_GLIPointsFilename>"
       << "<li_GLIPoint x=\"75\" y=\"80\" h=\"15.13074207\"/>"
       << "<li_GLIPoint x=\"50\" y=\"50\" h=\"12.03726764\"/>"
       << "<li_GLIPoint x=\"190\" y=\"193\" h=\"5.648193732\"/>"
       << "<li_GLIPoint x=\"10\" y=\"10\" h=\"15.13074207\"/>"
       << "<li_GLIPoint x=\"156\" y=\"15\" h=\"17.21977678\"/>"
       << "<li_GLIPoint x=\"12\" y=\"194\" h=\"9.461874761\"/>"
       << "</GLIPointCreator1>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteGLIPointsXMLErrorFile1()
////////////////////////////////////////////////////////////////////////////
const char* WriteGLIPointsXMLErrorFile1() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  //Write file
  WriteGLIPointsCommonStuff(oOut);

  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>GLIPointCreator</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "</behavior>"
       << "</behaviorList>"
       << "<GLIPointCreator1>"
       << "<li_beamFractGlobalRad>0.5</li_beamFractGlobalRad>"
       << "<li_clearSkyTransCoeff>0.65</li_clearSkyTransCoeff>"
       << "<li_julianDayGrowthStarts>105</li_julianDayGrowthStarts>"
       << "<li_julianDayGrowthEnds>258</li_julianDayGrowthEnds>"
       << "<li_minSunAngle>0.785</li_minSunAngle>"
       << "<li_numAltGrids>12</li_numAltGrids>"
       << "<li_numAziGrids>18</li_numAziGrids>"
       << "<li_lightExtinctionCoefficient>"
       << "<li_lecVal species=\"Species_1\">0.2</li_lecVal>"
       << "</li_lightExtinctionCoefficient>"
       << "<li_GLIPointsFilename>testout.txt</li_GLIPointsFilename>"
       << "</GLIPointCreator1>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteGLIPointsXMLErrorFile3()
////////////////////////////////////////////////////////////////////////////
const char* WriteGLIPointsXMLErrorFile3() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  //Write file
  WriteGLIPointsCommonStuff(oOut);

  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>GLIPointCreator</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "</behavior>"
       << "</behaviorList>"
       << "<GLIPointCreator1>"
       << "<li_beamFractGlobalRad>0.5</li_beamFractGlobalRad>"
       << "<li_clearSkyTransCoeff>0.65</li_clearSkyTransCoeff>"
       << "<li_julianDayGrowthStarts>105</li_julianDayGrowthStarts>"
       << "<li_julianDayGrowthEnds>258</li_julianDayGrowthEnds>"
       << "<li_minSunAngle>0.785</li_minSunAngle>"
       << "<li_numAltGrids>-12</li_numAltGrids>"
       << "<li_numAziGrids>18</li_numAziGrids>"
       << "<li_lightExtinctionCoefficient>"
       << "<li_lecVal species=\"Species_1\">0.2</li_lecVal>"
       << "</li_lightExtinctionCoefficient>"
       << "<li_GLIPointsFilename>testout.txt</li_GLIPointsFilename>"
       << "<li_GLIPoint x=\"75\" y=\"80\" h=\"15.13074207\"/>"
       << "<li_GLIPoint x=\"50\" y=\"50\" h=\"12.03726764\"/>"
       << "<li_GLIPoint x=\"190\" y=\"193\" h=\"5.648193732\"/>"
       << "<li_GLIPoint x=\"10\" y=\"10\" h=\"15.13074207\"/>"
       << "<li_GLIPoint x=\"156\" y=\"15\" h=\"17.21977678\"/>"
       << "<li_GLIPoint x=\"12\" y=\"194\" h=\"9.461874761\"/>"
       << "</GLIPointCreator1>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteGLIPointsXMLErrorFile4()
////////////////////////////////////////////////////////////////////////////
const char* WriteGLIPointsXMLErrorFile4() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  //Write file
  WriteGLIPointsCommonStuff(oOut);

  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>GLIPointCreator</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "</behavior>"
       << "</behaviorList>"
       << "<GLIPointCreator1>"
       << "<li_beamFractGlobalRad>0.5</li_beamFractGlobalRad>"
       << "<li_clearSkyTransCoeff>0.65</li_clearSkyTransCoeff>"
       << "<li_julianDayGrowthStarts>105</li_julianDayGrowthStarts>"
       << "<li_julianDayGrowthEnds>258</li_julianDayGrowthEnds>"
       << "<li_minSunAngle>0.785</li_minSunAngle>"
       << "<li_numAltGrids>12</li_numAltGrids>"
       << "<li_numAziGrids>18</li_numAziGrids>"
       << "<li_lightExtinctionCoefficient>"
       << "<li_lecVal species=\"Species_1\">0.2</li_lecVal>"
       << "</li_lightExtinctionCoefficient>"
       << "<li_GLIPointsFilename>testout.txt</li_GLIPointsFilename>"
       << "<li_GLIPoint x=\"75\" y=\"80\" h=\"15.13074207\"/>"
       << "<li_GLIPoint x=\"50\" y=\"-50\" h=\"12.03726764\"/>"
       << "<li_GLIPoint x=\"190\" y=\"193\" h=\"5.648193732\"/>"
       << "<li_GLIPoint x=\"10\" y=\"10\" h=\"15.13074207\"/>"
       << "<li_GLIPoint x=\"156\" y=\"15\" h=\"17.21977678\"/>"
       << "<li_GLIPoint x=\"12\" y=\"194\" h=\"9.461874761\"/>"
       << "</GLIPointCreator1>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteGLIPointsXMLErrorFile5()
////////////////////////////////////////////////////////////////////////////
const char* WriteGLIPointsXMLErrorFile5() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  //Write file
  WriteGLIPointsCommonStuff(oOut);

  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>GLIPointCreator</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "</behavior>"
       << "</behaviorList>"
       << "<GLIPointCreator1>"
       << "<li_beamFractGlobalRad>0.5</li_beamFractGlobalRad>"
       << "<li_clearSkyTransCoeff>0.65</li_clearSkyTransCoeff>"
       << "<li_julianDayGrowthStarts>105</li_julianDayGrowthStarts>"
       << "<li_julianDayGrowthEnds>258</li_julianDayGrowthEnds>"
       << "<li_minSunAngle>0.785</li_minSunAngle>"
       << "<li_numAltGrids>12</li_numAltGrids>"
       << "<li_numAziGrids>18</li_numAziGrids>"
       << "<li_lightExtinctionCoefficient>"
       << "<li_lecVal species=\"Species_1\">0.2</li_lecVal>"
       << "</li_lightExtinctionCoefficient>"
       << "<li_GLIPointsFilename>testout.txt</li_GLIPointsFilename>"
       << "<li_GLIPoint x=\"75\" y=\"80\" h=\"15.13074207\"/>"
       << "<li_GLIPoint x=\"50\" y=\"50\" h=\"12.03726764\"/>"
       << "<li_GLIPoint x=\"190\" y=\"193\" h=\"5.648193732\"/>"
       << "<li_GLIPoint x=\"10\" y=\"10\" h=\"-15.13074207\"/>"
       << "<li_GLIPoint x=\"156\" y=\"15\" h=\"17.21977678\"/>"
       << "<li_GLIPoint x=\"12\" y=\"194\" h=\"9.461874761\"/>"
       << "</GLIPointCreator1>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteGLIPointsCommonStuff()
////////////////////////////////////////////////////////////////////////////
void WriteGLIPointsCommonStuff(std::fstream &oOut) {
  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06010101\">"
       << "<plot>"
       << "<timesteps>1</timesteps>"
       << "<yearsPerTimestep>1</yearsPerTimestep>"
       << "<randomSeed>1</randomSeed>"
       << "<plot_lenX>200.0</plot_lenX>"
       << "<plot_lenY>200.0</plot_lenY>"
       << "<plot_latitude>55.37</plot_latitude>"
       << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
       << "<plot_temp_C>12</plot_temp_C>"
       << "</plot>"
       << "<trees>"
       << "<tr_speciesList>"
       << "<tr_species speciesName=\"Species_1\" />"
       << "</tr_speciesList>"
       << "<tr_maxSeedlingHeight>"
       << "<tr_mshVal species=\"Species_1\">1.35</tr_mshVal>"
       << "</tr_maxSeedlingHeight>"
       << "<tr_seedDiam10Cm>0.1</tr_seedDiam10Cm>"
       << "<tr_minAdultDBH>"
       << "<tr_madVal species=\"Species_1\">10.0</tr_madVal>"
       << "</tr_minAdultDBH>"
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
