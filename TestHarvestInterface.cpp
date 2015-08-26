//---------------------------------------------------------------------------
// TestHarvestInterface.cpp
//---------------------------------------------------------------------------
#include "TestHarvestInterface.h"
#include <gtest/gtest.h>
#include <fstream>
#include <math.h>
#include <stdio.h>
#include <fstream>
#include "TreePopulation.h"
#include "Disturbance.h"
#include "Grid.h"
#include "SimManager.h"
#include "PlatformFuncs.h"

#ifdef linux
#define TESTPATH "/home/lora/SORTIE/Core_Model_Tester/"
#define TESTPATH2 "/home/lora/Documents/"
#define TESTPATH3 "/home/lora/SORTIE/"
#else
#define TESTPATH "c:\\Code\\current_development\\Core_Model_Tester\\"
#define TESTPATH2 "c:\\users\\lora\\my documents\\"
#define TESTPATH3 "c:\\Code\\current_development\\"
#endif

using namespace std;

////////////////////////////////////////////////////////////////////////////
// TestErrorProcessing()
////////////////////////////////////////////////////////////////////////////
TEST(HarvestInterface, TestErrorProcessing) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try
  {
    p_oSimManager->ReadFile(WriteHarvestInterfaceXMLErrorFile1());
    FAIL() << "Test error processing didn't catch error for WriteHarvestInterfaceXMLErrorFile1.";
  }
  catch (modelErr& err)
  {
    if (err.sFunction.compare("clHarvestInterface::GetData") != 0)
    {
      FAIL() << "Test error processing caught wrong error for WriteHarvestInterfaceXMLErrorFile1.";
    }
    ;
  }

  try
  {
    p_oSimManager->ReadFile(WriteHarvestInterfaceXMLErrorFile2());
    FAIL() << "Test error processing didn't catch error for WriteHarvestInterfaceXMLErrorFile2.";
  }
  catch (modelErr& err)
  {
    if (err.sFunction.compare("clHarvestInterface::GetData") != 0)
    {
      FAIL() << "Test error processing caught wrong error for WriteHarvestInterfaceXMLErrorFile2.";
    }
    ;
  }

  try
  {
    p_oSimManager->ReadFile(WriteHarvestInterfaceXMLErrorFile3());
    FAIL() << "Test error processing didn't catch error for WriteHarvestInterfaceXMLErrorFile3.";
  }
  catch (modelErr& err)
  {
    if (err.sFunction.compare("clHarvestInterface::GetData") != 0)
    {
      FAIL() << "Test error processing caught wrong error for WriteHarvestInterfaceXMLErrorFile3.";
    }
    ;
  }

  try
  {
    p_oSimManager->ReadFile(WriteHarvestInterfaceXMLErrorFile4());
    FAIL() << "Test error processing didn't catch error for WriteHarvestInterfaceXMLErrorFile4.";
  }
  catch (modelErr& err)
  {
    if (err.sFunction.compare("clHarvestInterface::GetData") != 0)
    {
      FAIL() << "Test error processing caught wrong error for WriteHarvestInterfaceXMLErrorFile4.";
    }
    ;
  }

  //Provoke an error with the batch parameters file
  //Prepare our files
  WriteHarvestInterfaceAllParamsFile();
  WriteHarvestInterfaceXMLFile5();

  try {
    //Run our batch - we can't directly catch the error, but there will
    //be a crash if it doesn't work
    p_oSimManager->RunBatch( WriteHarvestInterfaceXMLErrorBatch1() );
    //FAIL() << "Test error processing didn't catch error for batch parameters file too short.";
  }
  catch (modelErr& err)
  {
    if (err.sFunction.compare("clHarvestInterface::GetData") != 0)
    {
      FAIL() << "Test error processing caught wrong error for batch parameters file too short.";
    }
    ;
  }
  char cPath[500];
  sprintf(cPath, "%s%s", TESTPATH, "test5harvest.txt");
  DeleteThisFile(cPath);
  sprintf(cPath, "%s%s", TESTPATH, "cutfile5.txt");
  DeleteThisFile(cPath);
  sprintf(cPath, "%s%s", TESTPATH, "batch1.txt");
  DeleteThisFile(cPath);
  sprintf(cPath, "%s%s", TESTPATH, "batch2.txt");
  DeleteThisFile(cPath);
  sprintf(cPath, "%s%s", TESTPATH, "batch3.txt");
  DeleteThisFile(cPath);
  sprintf(cPath, "%s%s", TESTPATH, "allparams.txt");
  DeleteThisFile(cPath);
  sprintf(cPath, "%s%s", TESTPATH, "parameters5.txt");
  DeleteThisFile(cPath);
  sprintf(cPath, "%s%s", TESTPATH, "TestBatchFile1.xml");
  DeleteThisFile(cPath);

  //Provoke an error where the harvest return file doesn't exist
  try {
    p_oSimManager->ReadFile( WriteHarvestInterfaceXMLErrorFile5() );
    p_oSimManager->RunSim(1);
    FAIL() << "Test error processing didn't catch error for WriteHarvestInterfaceXMLErrorFile5.";
  }
  catch (modelErr& err)
  {
    if (err.sFunction.compare("clHarvestInterface::Action") != 0 ||
        err.sMoreInfo.find("can't find the harvested trees file") == string::npos)
    {
      FAIL() << "Test error processing caught wrong error for WriteHarvestInterfaceXMLErrorFile5.";
    }
    ;
  }
  sprintf(cPath, "%s%s", TESTPATH, "test1harvest.txt");
  DeleteThisFile(cPath);
  sprintf(cPath, "%s%s", TESTPATH, "cutfile.txt");
  DeleteThisFile(cPath);
  sprintf(cPath, "%s%s", TESTPATH, "Update File 3.txt");
  DeleteThisFile(cPath);



  //Provoke an error where the update return file doesn't exist
  try {
    p_oSimManager->ReadFile( WriteHarvestInterfaceXMLErrorFile6() );
    p_oSimManager->RunSim();
    FAIL() << "Test error processing didn't catch error for WriteHarvestInterfaceXMLErrorFile6.";
  }
  catch (modelErr& err)
  {
    if (err.sFunction.compare("clHarvestInterface::Action") != 0 ||
        err.sMoreInfo.find("can't find the updated trees file") == string::npos)
    {
      FAIL() << "Test error processing caught wrong error for WriteHarvestInterfaceXMLErrorFile6.";
    }
    ;
  }
  sprintf(cPath, "%s%s", TESTPATH, "test4harvest.txt");
  DeleteThisFile(cPath);
  sprintf(cPath, "%s%s", TESTPATH, "cutfile4.txt");
  DeleteThisFile(cPath);



  //Provoke an error where a tree to harvest doesn't exist
  try {
    p_oSimManager->ReadFile( WriteHarvestInterfaceXMLErrorFile7() );
    p_oSimManager->RunSim(1);
    FAIL() << "Test error processing didn't catch error for WriteHarvestInterfaceXMLErrorFile7.";
  }
  catch (modelErr& err)
  {
    if (err.sFunction.compare("clHarvestInterface::Action") != 0 ||
        err.sMoreInfo.find("Unrecognized tree in harvest file") == string::npos)
    {
      FAIL() << "Test error processing caught wrong error for WriteHarvestInterfaceXMLErrorFile7.";
    }
    ;
  }
  sprintf(cPath, "%s%s", TESTPATH, "test1harvest.txt");
  DeleteThisFile(cPath);
  sprintf(cPath, "%s%s", TESTPATH, "cutfile.txt");
  DeleteThisFile(cPath);
  sprintf(cPath, "%s%s", TESTPATH, "Update File 3.txt");
  DeleteThisFile(cPath);



  //Provoke an error where a tree to update doesn't exist
  try {
    p_oSimManager->ReadFile( WriteHarvestInterfaceXMLErrorFile8() );
    p_oSimManager->RunSim(1);
    FAIL() << "Test error processing didn't catch error for WriteHarvestInterfaceXMLErrorFile8.";
  }
  catch (modelErr& err)
  {
    if (err.sFunction.compare("clHarvestInterface::Action") != 0 ||
        err.sMoreInfo.find("Unrecognized tree in update file") == string::npos)
    {
      FAIL() << "Test error processing caught wrong error for WriteHarvestInterfaceXMLErrorFile8.";
    }
    ;
  }
  sprintf(cPath, "%s%s", TESTPATH2, "Test 3 SORTIE input.txt");
  DeleteThisFile(cPath);
  sprintf(cPath, "%s%s", TESTPATH, "cutfile.txt");
  DeleteThisFile(cPath);
  sprintf(cPath, "%s%s", TESTPATH, "Update File 3.txt");
  DeleteThisFile(cPath);



  //Provoke an error where the batch parameters file is missing
  WriteHarvestInterfaceXMLErrorFile9();

  try {
    //Run our batch - we can't catch the error but there will be a crash if
    //it doesn't work
    p_oSimManager->RunBatch( WriteHarvestInterfaceXMLErrorBatch1() );
    //FAIL() << "Test error processing didn't catch error for WriteHarvestInterfaceXMLErrorFile9.";
  }
  catch (modelErr& err)
  {
    if (err.sFunction.compare("clHarvestInterface::GetData") != 0)
    {
      FAIL() << "Test error processing caught wrong error for WriteHarvestInterfaceXMLErrorFile9.";
    }
    ;
  }
  sprintf(cPath, "%s%s", TESTPATH, "TestBatchFile1.xml");
  DeleteThisFile(cPath);
  delete p_oSimManager;
}

////////////////////////////////////////////////////////////////////////////
// TestNormalProcessingRun1()
// Tests normal processing, run 1.  WriteHarvestInterfaceXMLFile1() does setup. Then 55 trees
// are created. Two timesteps are run. In the first, the following trees
// should be dead:  2, 3, 9, 15, 19, 20, 21, 22, 34, 48, 50. In the second
// timestep, the following trees should be dead:  1,4, 30, 31.
////////////////////////////////////////////////////////////////////////////
TEST(HarvestInterface, TestNormalProcessingRun1) {

  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    clTreePopulation * p_oPop;
    clTreeSearch *p_oAllTrees;
    clTree *p_oTree;
    clGrid *p_oGrid;
    std::stringstream sLabel;
    std::string sPath;
    bool *p_bFound;
    float *p_fDiam, *p_fX, *p_fY, fX, fY, fDiam, fVal, *p_fBA;
    int  iNumTrees = 55, iCount = 0, *p_iSpecies, *p_iType,
        *p_iDensity,
        i, iNumSpecies = 3, iCode,
        iSp, iTp, iX, iY, iNumXCells, iNumYCells, iVal;

    p_bFound = new bool[iNumTrees];
    p_fX = new float[iNumTrees];
    p_fY = new float[iNumTrees];
    p_fDiam = new float[iNumTrees];
    p_iSpecies = new int[iNumTrees];
    p_iType = new int[iNumTrees];
    p_fBA = new float[iNumSpecies];
    p_iDensity = new int[iNumSpecies];

    //Load our test file and get our tree population pointers
    p_oSimManager->ReadFile( WriteHarvestInterfaceXMLFile1() );
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );

    //Create our trees
    //Tree 1
    p_iSpecies[iCount] = 1;
    p_iType[iCount] = clTreePopulation::adult;
    p_fX[iCount] = 42.0525;
    p_fY[iCount] = 2.21632;
    p_fDiam[iCount] = 20.5095;
    iCount++;

    //Tree 2
    p_iSpecies[iCount] = 1;
    p_iType[iCount] = clTreePopulation::adult;
    p_fX[iCount] = 74.4779;
    p_fY[iCount] = 2.86341;
    p_fDiam[iCount] = 26.2185;
    iCount++;

    //Tree 3
    p_iSpecies[iCount] = 2;
    p_iType[iCount] = clTreePopulation::adult;
    p_fX[iCount] = 36.3822;
    p_fY[iCount] = 2.95831;
    p_fDiam[iCount] = 21.2419;
    iCount++;

    //Tree 4
    p_iSpecies[iCount] = 1;
    p_iType[iCount] = clTreePopulation::adult;
    p_fX[iCount] = 26.7469;
    p_fY[iCount] = 3.75704;
    p_fDiam[iCount] = 13.6089;
    iCount++;

    //Tree 5
    p_iSpecies[iCount] = 0;
    p_iType[iCount] = clTreePopulation::sapling;
    p_fX[iCount] = 49.8263;
    p_fY[iCount] = 4.18441;
    p_fDiam[iCount] = 6.42101;
    iCount++;

    //Tree 6
    p_iSpecies[iCount] = 1;
    p_iType[iCount] = clTreePopulation::adult;
    p_fX[iCount] = 27.794;
    p_fY[iCount] = 8.64942;
    p_fDiam[iCount] = 28.5256;
    iCount++;

    //Tree 7
    p_iSpecies[iCount] = 1;
    p_iType[iCount] = clTreePopulation::adult;
    p_fX[iCount] = 78.0224;
    p_fY[iCount] = 12.6457;
    p_fDiam[iCount] = 26.3755;
    iCount++;

    //Tree 8
    p_iSpecies[iCount] = 0;
    p_iType[iCount] = clTreePopulation::sapling;
    p_fX[iCount] = 88.2882;
    p_fY[iCount] = 13.1436;
    p_fDiam[iCount] = 3.8165;
    iCount++;

    //Tree 9
    p_iSpecies[iCount] = 1;
    p_iType[iCount] = clTreePopulation::adult;
    p_fX[iCount] = 72.0387;
    p_fY[iCount] = 13.9719;
    p_fDiam[iCount] = 12.3629;
    iCount++;

    //Tree 10
    p_iSpecies[iCount] = 0;
    p_iType[iCount] = clTreePopulation::adult;
    p_fX[iCount] = 18.4304;
    p_fY[iCount] = 15.3092;
    p_fDiam[iCount] = 13.8248;
    iCount++;

    //Tree 11
    p_iSpecies[iCount] = 0;
    p_iType[iCount] = clTreePopulation::seedling;
    p_fX[iCount] = 39.366;
    p_fY[iCount] = 19.9556;
    p_fDiam[iCount] = 1.12;
    iCount++;

    //Tree 12
    p_iSpecies[iCount] = 1;
    p_iType[iCount] = clTreePopulation::seedling;
    p_fX[iCount] = 86.5371;
    p_fY[iCount] = 20.0087;
    p_fDiam[iCount] = 1.14;
    iCount++;

    //Tree 13
    p_iSpecies[iCount] = 2;
    p_iType[iCount] = clTreePopulation::seedling;
    p_fX[iCount] = 93.3186;
    p_fY[iCount] = 20.998;
    p_fDiam[iCount] = 1.2;
    iCount++;

    //Tree 14
    p_iSpecies[iCount] = 2;
    p_iType[iCount] = clTreePopulation::seedling;
    p_fX[iCount] = 30.1811;
    p_fY[iCount] = 21.9206;
    p_fDiam[iCount] = 1.12;
    iCount++;

    //Tree 15
    p_iSpecies[iCount] = 0;
    p_iType[iCount] = clTreePopulation::seedling;
    p_fX[iCount] = 28.4697;
    p_fY[iCount] = 22.4661;
    p_fDiam[iCount] = 1.14;
    iCount++;

    //Tree 16
    p_iSpecies[iCount] = 1;
    p_iType[iCount] = clTreePopulation::adult;
    p_fX[iCount] = 55.9178;
    p_fY[iCount] = 25.7332;
    p_fDiam[iCount] = 17.3983;
    iCount++;

    //Tree 17
    p_iSpecies[iCount] = 2;
    p_iType[iCount] = clTreePopulation::adult;
    p_fX[iCount] = 20.4647;
    p_fY[iCount] = 27.7396;
    p_fDiam[iCount] = 24.272;
    iCount++;

    //Tree 18
    p_iSpecies[iCount] = 0;
    p_iType[iCount] = clTreePopulation::sapling;
    p_fX[iCount] = 98.1614;
    p_fY[iCount] = 29.6613;
    p_fDiam[iCount] = 8.42262;
    iCount++;

    //Tree 19
    p_iSpecies[iCount] = 2;
    p_iType[iCount] = clTreePopulation::adult;
    p_fX[iCount] = 74.1404;
    p_fY[iCount] = 39.8158;
    p_fDiam[iCount] = 24.7286;
    iCount++;

    //Tree 20
    p_iSpecies[iCount] = 1;
    p_iType[iCount] = clTreePopulation::adult;
    p_fX[iCount] = 90.0865;
    p_fY[iCount] = 40.4886;
    p_fDiam[iCount] = 28.1205;
    iCount++;

    //Tree 21
    p_iSpecies[iCount] = 1;
    p_iType[iCount] = clTreePopulation::adult;
    p_fX[iCount] = 90.0865;
    p_fY[iCount] = 40.4886;
    p_fDiam[iCount] = 28.1206;
    iCount++;

    //Tree 22
    p_iSpecies[iCount] = 2;
    p_iType[iCount] = clTreePopulation::adult;
    p_fX[iCount] = 36.0762;
    p_fY[iCount] = 42.6468;
    p_fDiam[iCount] = 20.4855;
    iCount++;

    //Tree 23
    p_iSpecies[iCount] = 0;
    p_iType[iCount] = clTreePopulation::adult;
    p_fX[iCount] = 70.1652;
    p_fY[iCount] = 43.3971;
    p_fDiam[iCount] = 15.1196;
    iCount++;

    //Tree 24
    p_iSpecies[iCount] = 1;
    p_iType[iCount] = clTreePopulation::adult;
    p_fX[iCount] = 67.6349;
    p_fY[iCount] = 47.9413;
    p_fDiam[iCount] = 26.2077;
    iCount++;

    //Tree 25
    p_iSpecies[iCount] = 0;
    p_iType[iCount] = clTreePopulation::sapling;
    p_fX[iCount] = 69.7277;
    p_fY[iCount] = 48.6251;
    p_fDiam[iCount] = 7.98507;
    iCount++;

    //Tree 26
    p_iSpecies[iCount] = 2;
    p_iType[iCount] = clTreePopulation::adult;
    p_fX[iCount] = 86.0179;
    p_fY[iCount] = 49.4856;
    p_fDiam[iCount] = 17.5575;
    iCount++;

    //Tree 27
    p_iSpecies[iCount] = 2;
    p_iType[iCount] = clTreePopulation::adult;
    p_fX[iCount] = 68.888;
    p_fY[iCount] = 50.1366;
    p_fDiam[iCount] = 24.708;
    iCount++;

    //Tree 28
    p_iSpecies[iCount] = 1;
    p_iType[iCount] = clTreePopulation::adult;
    p_fX[iCount] = 84.6036;
    p_fY[iCount] = 50.93;
    p_fDiam[iCount] = 21.3454;
    iCount++;

    //Tree 29
    p_iSpecies[iCount] = 2;
    p_iType[iCount] = clTreePopulation::adult;
    p_fX[iCount] = 25.7016;
    p_fY[iCount] = 54.1108;
    p_fDiam[iCount] = 20.7396;
    iCount++;

    //Tree 30
    p_iSpecies[iCount] = 2;
    p_iType[iCount] = clTreePopulation::adult;
    p_fX[iCount] = 21.2453;
    p_fY[iCount] = 54.7161;
    p_fDiam[iCount] = 12.1276;
    iCount++;

    //Tree 31
    p_iSpecies[iCount] = 0;
    p_iType[iCount] = clTreePopulation::sapling;
    p_fX[iCount] = 14.3788;
    p_fY[iCount] = 55.4155;
    p_fDiam[iCount] = 5.12777;
    iCount++;

    //Tree 32
    p_iSpecies[iCount] = 0;
    p_iType[iCount] = clTreePopulation::adult;
    p_fX[iCount] = 60.6626;
    p_fY[iCount] = 55.657;
    p_fDiam[iCount] = 16.8162;
    iCount++;

    //Tree 33
    p_iSpecies[iCount] = 2;
    p_iType[iCount] = clTreePopulation::adult;
    p_fX[iCount] = 71.3062;
    p_fY[iCount] = 56.5974;
    p_fDiam[iCount] = 24.7457;
    iCount++;

    //Tree 34
    p_iSpecies[iCount] = 2;
    p_iType[iCount] = clTreePopulation::adult;
    p_fX[iCount] = 9.38922;
    p_fY[iCount] = 59.3884;
    p_fDiam[iCount] = 19.1746;
    iCount++;

    //Tree 35
    p_iSpecies[iCount] = 2;
    p_iType[iCount] = clTreePopulation::adult;
    p_fX[iCount] = 27.1944;
    p_fY[iCount] = 63.1713;
    p_fDiam[iCount] = 26.0429;
    iCount++;

    //Tree 36
    p_iSpecies[iCount] = 0;
    p_iType[iCount] = clTreePopulation::adult;
    p_fX[iCount] = 61.7164;
    p_fY[iCount] = 66.0961;
    p_fDiam[iCount] = 17.1742;
    iCount++;

    //Tree 37
    p_iSpecies[iCount] = 1;
    p_iType[iCount] = clTreePopulation::adult;
    p_fX[iCount] = 34.2957;
    p_fY[iCount] = 67.5466;
    p_fDiam[iCount] = 16.9941;
    iCount++;

    //Tree 38
    p_iSpecies[iCount] = 2;
    p_iType[iCount] = clTreePopulation::sapling;
    p_fX[iCount] = 41.5812;
    p_fY[iCount] = 71.8411;
    p_fDiam[iCount] = 7.14589;
    iCount++;

    //Tree 39
    p_iSpecies[iCount] = 1;
    p_iType[iCount] = clTreePopulation::adult;
    p_fX[iCount] = 28.2031;
    p_fY[iCount] = 72.6295;
    p_fDiam[iCount] = 23.4028;
    iCount++;

    //Tree 40
    p_iSpecies[iCount] = 2;
    p_iType[iCount] = clTreePopulation::sapling;
    p_fX[iCount] = 6.33182;
    p_fY[iCount] = 75.0587;
    p_fDiam[iCount] = 4.24863;
    iCount++;

    //Tree 41
    p_iSpecies[iCount] = 1;
    p_iType[iCount] = clTreePopulation::adult;
    p_fX[iCount] = 63.196;
    p_fY[iCount] = 77.6672;
    p_fDiam[iCount] = 24.5384;
    iCount++;

    //Tree 42
    p_iSpecies[iCount] = 1;
    p_iType[iCount] = clTreePopulation::adult;
    p_fX[iCount] = 47.198;
    p_fY[iCount] = 77.8982;
    p_fDiam[iCount] = 24.5211;
    iCount++;

    //Tree 43
    p_iSpecies[iCount] = 2;
    p_iType[iCount] = clTreePopulation::adult;
    p_fX[iCount] = 1.12617;
    p_fY[iCount] = 78.3586;
    p_fDiam[iCount] = 25.6215;
    iCount++;

    //Tree 44
    p_iSpecies[iCount] = 1;
    p_iType[iCount] = clTreePopulation::adult;
    p_fX[iCount] = 74.3191;
    p_fY[iCount] = 81.1496;
    p_fDiam[iCount] = 27.4837;
    iCount++;

    //Tree 45
    p_iSpecies[iCount] = 1;
    p_iType[iCount] = clTreePopulation::adult;
    p_fX[iCount] = 23.3972;
    p_fY[iCount] = 82.7297;
    p_fDiam[iCount] = 24.9638;
    iCount++;

    //Tree 46
    p_iSpecies[iCount] = 2;
    p_iType[iCount] = clTreePopulation::adult;
    p_fX[iCount] = 15.6913;
    p_fY[iCount] = 84.3219;
    p_fDiam[iCount] = 24.791;
    iCount++;

    //Tree 47
    p_iSpecies[iCount] = 2;
    p_iType[iCount] = clTreePopulation::adult;
    p_fX[iCount] = 38.6781;
    p_fY[iCount] = 84.8195;
    p_fDiam[iCount] = 25.1718;
    iCount++;

    //Tree 48
    p_iSpecies[iCount] = 2;
    p_iType[iCount] = clTreePopulation::sapling;
    p_fX[iCount] = 91.4707;
    p_fY[iCount] = 86.3797;
    p_fDiam[iCount] = 8.31;
    iCount++;

    //Tree 49
    p_iSpecies[iCount] = 2;
    p_iType[iCount] = clTreePopulation::adult;
    p_fX[iCount] = 37.5938;
    p_fY[iCount] = 87.2484;
    p_fDiam[iCount] = 15.9924;
    iCount++;

    //Tree 50
    p_iSpecies[iCount] = 2;
    p_iType[iCount] = clTreePopulation::sapling;
    p_fX[iCount] = 36.6376;
    p_fY[iCount] = 87.5301;
    p_fDiam[iCount] = 6.8901;
    iCount++;

    //Tree 51
    p_iSpecies[iCount] = 0;
    p_iType[iCount] = clTreePopulation::adult;
    p_fX[iCount] = 55.9163;
    p_fY[iCount] = 90.0189;
    p_fDiam[iCount] = 12.9417;
    iCount++;

    //Tree 52
    p_iSpecies[iCount] = 2;
    p_iType[iCount] = clTreePopulation::adult;
    p_fX[iCount] = 97.7476;
    p_fY[iCount] = 94.7417;
    p_fDiam[iCount] = 25.3651;
    iCount++;

    //Tree 53
    p_iSpecies[iCount] = 2;
    p_iType[iCount] = clTreePopulation::adult;
    p_fX[iCount] = 51.7177;
    p_fY[iCount] = 95.4606;
    p_fDiam[iCount] = 12.6799;
    iCount++;

    //Tree 54
    p_iSpecies[iCount] = 2;
    p_iType[iCount] = clTreePopulation::adult;
    p_fX[iCount] = 64.2286;
    p_fY[iCount] = 98.6715;
    p_fDiam[iCount] = 25.688;
    iCount++;

    //Tree 55
    p_iSpecies[iCount] = 0;
    p_iType[iCount] = clTreePopulation::adult;
    p_fX[iCount] = 96.6835;
    p_fY[iCount] = 98.7591;
    p_fDiam[iCount] = 17.3889;
    iCount++;

    for (i = 0; i < iNumTrees; i++) {
      p_oPop->CreateTree(p_fX[i], p_fY[i], p_iSpecies[i], p_iType[i], p_fDiam[i]);
    }

    //Now do the run
    p_oSimManager->RunSim(1);

    for (i = 0; i < iNumTrees; i++) {
      p_bFound[i] = false;
    }

    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {

      iSp = p_oTree->GetSpecies();
      iTp = p_oTree->GetType();
      if (clTreePopulation::seedling == iTp)
        p_oTree->GetValue(p_oPop->GetDiam10Code(iSp, iTp), & fDiam);
      else
        p_oTree->GetValue(p_oPop->GetDbhCode(iSp, iTp), & fDiam);
      p_oTree->GetValue(p_oPop->GetXCode(iSp, iTp), & fX);
      p_oTree->GetValue(p_oPop->GetYCode(iSp, iTp), & fY);

      for (i = 0; i < iNumTrees; i++) {
        if (iSp == p_iSpecies[i] &&
            iTp == p_iType[i] &&
            fabs(fDiam - p_fDiam[i]) < 0.0001 &&
            fabs(fX - p_fX[i]) < 0.0001 &&
            fabs(fY - p_fY[i]) < 0.0001 ) {

          p_bFound[i] = true;
          break;
        }
      }

      p_oTree = p_oAllTrees->NextTree();
    }

    //Verify that certain trees are dead
    for (i = 0; i < iNumTrees; i++) {
      if ( 1 == i ||
          2 == i ||
          8 == i ||
          14 == i ||
          18 == i ||
          19 == i ||
          20 == i ||
          21 == i ||
          33 == i ||
          47 == i ||
          49 == i ) {

        EXPECT_FALSE(p_bFound[i]);
      } else {
        EXPECT_TRUE(p_bFound[i]);
      }
    }

    //Check the Harvest Results grid
    p_oGrid = p_oSimManager->GetGridObject("Harvest Results");
    ASSERT_TRUE(NULL != p_oGrid);
    p_oGrid->GetValueAtPoint(p_fX[1], p_fY[1],
        p_oGrid->GetIntDataCode("Harvest Type"), &iVal);
    EXPECT_EQ(clDisturbance::partial, iVal);
    for (i = 0; i < iNumSpecies; i++) {
      p_fBA[i] = 0;
      p_iDensity[i] = 0;
    }
    iNumXCells = p_oGrid->GetNumberXCells();
    iNumYCells = p_oGrid->GetNumberYCells();
    for (iX = 0; iX < iNumXCells; iX++) {
      for (iY = 0; iY < iNumYCells; iY++) {
        for (i = 0; i < iNumSpecies; i++) {
          sLabel << "Cut Density_0_" << i;
          iCode = p_oGrid->GetIntDataCode(sLabel.str());
          EXPECT_GT(iCode, -1);
          p_oGrid->GetValueOfCell(iX, iY, iCode, &iVal);
          p_iDensity[i] += iVal;
          sLabel.str("");
          sLabel << "Cut Basal Area_0_" << i;
          iCode = p_oGrid->GetFloatDataCode(sLabel.str());
          EXPECT_GT(iCode, -1);
          p_oGrid->GetValueOfCell(iX, iY, iCode, &fVal);
          p_fBA[i] += fVal;
          sLabel.str("");
        }
      }
    }
    EXPECT_EQ(1, p_iDensity[0]);
    EXPECT_EQ(4, p_iDensity[1]);
    EXPECT_EQ(6, p_iDensity[2]);
    fVal = 0;
    EXPECT_LT(fabs(p_fBA[0] - fVal), 0.0001);
    fVal = 0.19020629;
    EXPECT_LT(fabs(p_fBA[1] - fVal), 0.0001);
    fVal = 0.154454247;
    EXPECT_LT(fabs(p_fBA[2] - fVal), 0.0001);

    //Do the second timestep
    p_oSimManager->RunSim(1);

    //Verify that certain trees die
    for (i = 0; i < iNumTrees; i++) {
      p_bFound[i] = false;
    }

    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {

      iSp = p_oTree->GetSpecies();
      iTp = p_oTree->GetType();
      if (clTreePopulation::seedling == iTp)
        p_oTree->GetValue(p_oPop->GetDiam10Code(iSp, iTp), & fDiam);
      else
        p_oTree->GetValue(p_oPop->GetDbhCode(iSp, iTp), & fDiam);
      p_oTree->GetValue(p_oPop->GetXCode(iSp, iTp), & fX);
      p_oTree->GetValue(p_oPop->GetYCode(iSp, iTp), & fY);

      for (i = 0; i < iNumTrees; i++) {
        if (iSp == p_iSpecies[i] &&
            iTp == p_iType[i] &&
            fabs(fDiam - p_fDiam[i]) < 0.0001 &&
            fabs(fX - p_fX[i]) < 0.0001 &&
            fabs(fY - p_fY[i]) < 0.0001 ) {

          p_bFound[i] = true;
          break;
        }
      }

      p_oTree = p_oAllTrees->NextTree();
    }

    for (i = 0; i < iNumTrees; i++) {
      if ( 0 == i ||
          1 == i ||
          2 == i ||
          3 == i ||
          8 == i ||
          14 == i ||
          18 == i ||
          19 == i ||
          20 == i ||
          21 == i ||
          29 == i ||
          30 == i ||
          33 == i ||
          47 == i ||
          49 == i ) {

        EXPECT_FALSE(p_bFound[i]);
      } else {
        EXPECT_TRUE(p_bFound[i]);
      }
    }

    p_oGrid->GetValueAtPoint(p_fX[0], p_fY[0],
        p_oGrid->GetIntDataCode("Harvest Type"), &iVal);
    EXPECT_EQ(clDisturbance::partial, iVal);
    for (i = 0; i < iNumSpecies; i++) {
      p_fBA[i] = 0;
      p_iDensity[i] = 0;
    }
    iNumXCells = p_oGrid->GetNumberXCells();
    iNumYCells = p_oGrid->GetNumberYCells();
    for (iX = 0; iX < iNumXCells; iX++) {
      for (iY = 0; iY < iNumYCells; iY++) {
        for (i = 0; i < iNumSpecies; i++) {
          sLabel << "Cut Density_0_" << i;
          p_oGrid->GetValueOfCell(iX, iY, p_oGrid->GetIntDataCode(sLabel.str()), &iVal);
          p_iDensity[i] += iVal;
          sLabel.str("");
          sLabel << "Cut Basal Area_0_" << i;
          p_oGrid->GetValueOfCell(iX, iY, p_oGrid->GetFloatDataCode(sLabel.str()), &fVal);
          p_fBA[i] += fVal;
          sLabel.str("");
        }
      }
    }
    EXPECT_EQ(1, p_iDensity[0]);
    EXPECT_EQ(2, p_iDensity[1]);
    EXPECT_EQ(1, p_iDensity[2]);
    fVal = 0.002065128;
    EXPECT_LT(fabs(p_fBA[0] - fVal), 0.0001);
    fVal = 0.0475827;
    EXPECT_LT(fabs(p_fBA[1] - fVal), 0.0001);
    fVal = 0.011551533;
    EXPECT_LT(fabs(p_fBA[2] - fVal), 0.0001);

    delete[] p_bFound;
    delete[] p_fX;
    delete[] p_fY;
    delete[] p_fDiam;
    delete[] p_iSpecies;
    delete[] p_iType;
    delete[] p_fBA;
    delete[] p_iDensity;

    sPath = TESTPATH; sPath += "test1harvest.txt";
    DeleteThisFile(sPath);
    sPath = TESTPATH; sPath += "cutfile.txt";
    DeleteThisFile(sPath);

    delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

////////////////////////////////////////////////////////////////////////////
// TestNormalProcessingRun2()
// Tests normal processing, run 2. This tests extra columns desired in the
// files. WriteHarvestInterfaceXMLFile2() does setup. Then 55 trees
// are created. Three timesteps are run. In the first, the following trees
// should be dead:  2, 3, 9, 15, 19, 20, 21, 22, 34, 48, 50. In the second
// timestep, all remaining trees are cut. The third timestep tests the
// situation when there are no trees.
////////////////////////////////////////////////////////////////////////////
TEST(HarvestInterface, TestNormalProcessingRun2) {
  using namespace std;

  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    clTreePopulation * p_oPop;
    clTreeSearch *p_oAllTrees;
    clTree *p_oTree;
    char cPath[500];
    bool *p_bFound;
    float *p_fDiam, *p_fX, *p_fY, fX, fY, fDiam;
    int  iNumTrees = 55, iCount = 0, *p_iSpecies, *p_iType, i,
        iSp, iTp;

    p_bFound = new bool[iNumTrees];
    p_fX = new float[iNumTrees];
    p_fY = new float[iNumTrees];
    p_fDiam = new float[iNumTrees];
    p_iSpecies = new int[iNumTrees];
    p_iType = new int[iNumTrees];

    //Load our test file and get our tree population pointers
    p_oSimManager->ReadFile( WriteHarvestInterfaceXMLFile2() );
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );

    //Create our trees
    //Tree 1
    p_iSpecies[iCount] = 1;
    p_iType[iCount] = clTreePopulation::adult;
    p_fX[iCount] = 42.0525;
    p_fY[iCount] = 2.21632;
    p_fDiam[iCount] = 20.5095;
    iCount++;

    //Tree 2
    p_iSpecies[iCount] = 1;
    p_iType[iCount] = clTreePopulation::adult;
    p_fX[iCount] = 74.4779;
    p_fY[iCount] = 2.86341;
    p_fDiam[iCount] = 26.2185;
    iCount++;

    //Tree 3
    p_iSpecies[iCount] = 2;
    p_iType[iCount] = clTreePopulation::adult;
    p_fX[iCount] = 36.3822;
    p_fY[iCount] = 2.95831;
    p_fDiam[iCount] = 21.2419;
    iCount++;

    //Tree 4
    p_iSpecies[iCount] = 1;
    p_iType[iCount] = clTreePopulation::adult;
    p_fX[iCount] = 26.7469;
    p_fY[iCount] = 3.75704;
    p_fDiam[iCount] = 13.6089;
    iCount++;

    //Tree 5
    p_iSpecies[iCount] = 0;
    p_iType[iCount] = clTreePopulation::sapling;
    p_fX[iCount] = 49.8263;
    p_fY[iCount] = 4.18441;
    p_fDiam[iCount] = 6.42101;
    iCount++;

    //Tree 6
    p_iSpecies[iCount] = 1;
    p_iType[iCount] = clTreePopulation::adult;
    p_fX[iCount] = 27.794;
    p_fY[iCount] = 8.64942;
    p_fDiam[iCount] = 28.5256;
    iCount++;

    //Tree 7
    p_iSpecies[iCount] = 1;
    p_iType[iCount] = clTreePopulation::adult;
    p_fX[iCount] = 78.0224;
    p_fY[iCount] = 12.6457;
    p_fDiam[iCount] = 26.3755;
    iCount++;

    //Tree 8
    p_iSpecies[iCount] = 0;
    p_iType[iCount] = clTreePopulation::sapling;
    p_fX[iCount] = 88.2882;
    p_fY[iCount] = 13.1436;
    p_fDiam[iCount] = 3.8165;
    iCount++;

    //Tree 9
    p_iSpecies[iCount] = 1;
    p_iType[iCount] = clTreePopulation::adult;
    p_fX[iCount] = 72.0387;
    p_fY[iCount] = 13.9719;
    p_fDiam[iCount] = 12.3629;
    iCount++;

    //Tree 10
    p_iSpecies[iCount] = 0;
    p_iType[iCount] = clTreePopulation::adult;
    p_fX[iCount] = 18.4304;
    p_fY[iCount] = 15.3092;
    p_fDiam[iCount] = 13.8248;
    iCount++;

    //Tree 11
    p_iSpecies[iCount] = 0;
    p_iType[iCount] = clTreePopulation::seedling;
    p_fX[iCount] = 39.366;
    p_fY[iCount] = 19.9556;
    p_fDiam[iCount] = 1.12;
    iCount++;

    //Tree 12
    p_iSpecies[iCount] = 1;
    p_iType[iCount] = clTreePopulation::seedling;
    p_fX[iCount] = 86.5371;
    p_fY[iCount] = 20.0087;
    p_fDiam[iCount] = 1.14;
    iCount++;

    //Tree 13
    p_iSpecies[iCount] = 2;
    p_iType[iCount] = clTreePopulation::seedling;
    p_fX[iCount] = 93.3186;
    p_fY[iCount] = 20.998;
    p_fDiam[iCount] = 1.2;
    iCount++;

    //Tree 14
    p_iSpecies[iCount] = 2;
    p_iType[iCount] = clTreePopulation::seedling;
    p_fX[iCount] = 30.1811;
    p_fY[iCount] = 21.9206;
    p_fDiam[iCount] = 1.12;
    iCount++;

    //Tree 15
    p_iSpecies[iCount] = 0;
    p_iType[iCount] = clTreePopulation::seedling;
    p_fX[iCount] = 28.4697;
    p_fY[iCount] = 22.4661;
    p_fDiam[iCount] = 1.14;
    iCount++;

    //Tree 16
    p_iSpecies[iCount] = 1;
    p_iType[iCount] = clTreePopulation::adult;
    p_fX[iCount] = 55.9178;
    p_fY[iCount] = 25.7332;
    p_fDiam[iCount] = 17.3983;
    iCount++;

    //Tree 17
    p_iSpecies[iCount] = 2;
    p_iType[iCount] = clTreePopulation::adult;
    p_fX[iCount] = 20.4647;
    p_fY[iCount] = 27.7396;
    p_fDiam[iCount] = 24.272;
    iCount++;

    //Tree 18
    p_iSpecies[iCount] = 0;
    p_iType[iCount] = clTreePopulation::sapling;
    p_fX[iCount] = 98.1614;
    p_fY[iCount] = 29.6613;
    p_fDiam[iCount] = 8.42262;
    iCount++;

    //Tree 19
    p_iSpecies[iCount] = 2;
    p_iType[iCount] = clTreePopulation::adult;
    p_fX[iCount] = 74.1404;
    p_fY[iCount] = 39.8158;
    p_fDiam[iCount] = 24.7286;
    iCount++;

    //Tree 20
    p_iSpecies[iCount] = 1;
    p_iType[iCount] = clTreePopulation::adult;
    p_fX[iCount] = 90.0865;
    p_fY[iCount] = 40.4886;
    p_fDiam[iCount] = 28.1205;
    iCount++;

    //Tree 21
    p_iSpecies[iCount] = 2;
    p_iType[iCount] = clTreePopulation::adult;
    p_fX[iCount] = 94.9792;
    p_fY[iCount] = 40.9522;
    p_fDiam[iCount] = 24.5678;
    iCount++;

    //Tree 22
    p_iSpecies[iCount] = 2;
    p_iType[iCount] = clTreePopulation::adult;
    p_fX[iCount] = 36.0762;
    p_fY[iCount] = 42.6468;
    p_fDiam[iCount] = 20.4855;
    iCount++;

    //Tree 23
    p_iSpecies[iCount] = 0;
    p_iType[iCount] = clTreePopulation::adult;
    p_fX[iCount] = 70.1652;
    p_fY[iCount] = 43.3971;
    p_fDiam[iCount] = 15.1196;
    iCount++;

    //Tree 24
    p_iSpecies[iCount] = 1;
    p_iType[iCount] = clTreePopulation::adult;
    p_fX[iCount] = 67.6349;
    p_fY[iCount] = 47.9413;
    p_fDiam[iCount] = 26.2077;
    iCount++;

    //Tree 25
    p_iSpecies[iCount] = 0;
    p_iType[iCount] = clTreePopulation::sapling;
    p_fX[iCount] = 69.7277;
    p_fY[iCount] = 48.6251;
    p_fDiam[iCount] = 7.98507;
    iCount++;

    //Tree 26
    p_iSpecies[iCount] = 2;
    p_iType[iCount] = clTreePopulation::adult;
    p_fX[iCount] = 86.0179;
    p_fY[iCount] = 49.4856;
    p_fDiam[iCount] = 17.5575;
    iCount++;

    //Tree 27
    p_iSpecies[iCount] = 2;
    p_iType[iCount] = clTreePopulation::adult;
    p_fX[iCount] = 68.888;
    p_fY[iCount] = 50.1366;
    p_fDiam[iCount] = 24.708;
    iCount++;

    //Tree 28
    p_iSpecies[iCount] = 1;
    p_iType[iCount] = clTreePopulation::adult;
    p_fX[iCount] = 84.6036;
    p_fY[iCount] = 50.93;
    p_fDiam[iCount] = 21.3454;
    iCount++;

    //Tree 29
    p_iSpecies[iCount] = 2;
    p_iType[iCount] = clTreePopulation::adult;
    p_fX[iCount] = 25.7016;
    p_fY[iCount] = 54.1108;
    p_fDiam[iCount] = 20.7396;
    iCount++;

    //Tree 30
    p_iSpecies[iCount] = 2;
    p_iType[iCount] = clTreePopulation::adult;
    p_fX[iCount] = 21.2453;
    p_fY[iCount] = 54.7161;
    p_fDiam[iCount] = 12.1276;
    iCount++;

    //Tree 31
    p_iSpecies[iCount] = 0;
    p_iType[iCount] = clTreePopulation::sapling;
    p_fX[iCount] = 14.3788;
    p_fY[iCount] = 55.4155;
    p_fDiam[iCount] = 5.12777;
    iCount++;

    //Tree 32
    p_iSpecies[iCount] = 0;
    p_iType[iCount] = clTreePopulation::adult;
    p_fX[iCount] = 60.6626;
    p_fY[iCount] = 55.657;
    p_fDiam[iCount] = 16.8162;
    iCount++;

    //Tree 33
    p_iSpecies[iCount] = 2;
    p_iType[iCount] = clTreePopulation::adult;
    p_fX[iCount] = 71.3062;
    p_fY[iCount] = 56.5974;
    p_fDiam[iCount] = 24.7457;
    iCount++;

    //Tree 34
    p_iSpecies[iCount] = 2;
    p_iType[iCount] = clTreePopulation::adult;
    p_fX[iCount] = 9.38922;
    p_fY[iCount] = 59.3884;
    p_fDiam[iCount] = 19.1746;
    iCount++;

    //Tree 35
    p_iSpecies[iCount] = 2;
    p_iType[iCount] = clTreePopulation::adult;
    p_fX[iCount] = 27.1944;
    p_fY[iCount] = 63.1713;
    p_fDiam[iCount] = 26.0429;
    iCount++;

    //Tree 36
    p_iSpecies[iCount] = 0;
    p_iType[iCount] = clTreePopulation::adult;
    p_fX[iCount] = 61.7164;
    p_fY[iCount] = 66.0961;
    p_fDiam[iCount] = 17.1742;
    iCount++;

    //Tree 37
    p_iSpecies[iCount] = 1;
    p_iType[iCount] = clTreePopulation::adult;
    p_fX[iCount] = 34.2957;
    p_fY[iCount] = 67.5466;
    p_fDiam[iCount] = 16.9941;
    iCount++;

    //Tree 38
    p_iSpecies[iCount] = 2;
    p_iType[iCount] = clTreePopulation::sapling;
    p_fX[iCount] = 41.5812;
    p_fY[iCount] = 71.8411;
    p_fDiam[iCount] = 7.14589;
    iCount++;

    //Tree 39
    p_iSpecies[iCount] = 1;
    p_iType[iCount] = clTreePopulation::adult;
    p_fX[iCount] = 28.2031;
    p_fY[iCount] = 72.6295;
    p_fDiam[iCount] = 23.4028;
    iCount++;

    //Tree 40
    p_iSpecies[iCount] = 2;
    p_iType[iCount] = clTreePopulation::sapling;
    p_fX[iCount] = 6.33182;
    p_fY[iCount] = 75.0587;
    p_fDiam[iCount] = 4.24863;
    iCount++;

    //Tree 41
    p_iSpecies[iCount] = 1;
    p_iType[iCount] = clTreePopulation::adult;
    p_fX[iCount] = 63.196;
    p_fY[iCount] = 77.6672;
    p_fDiam[iCount] = 24.5384;
    iCount++;

    //Tree 42
    p_iSpecies[iCount] = 1;
    p_iType[iCount] = clTreePopulation::adult;
    p_fX[iCount] = 47.198;
    p_fY[iCount] = 77.8982;
    p_fDiam[iCount] = 24.5211;
    iCount++;

    //Tree 43
    p_iSpecies[iCount] = 2;
    p_iType[iCount] = clTreePopulation::adult;
    p_fX[iCount] = 1.12617;
    p_fY[iCount] = 78.3586;
    p_fDiam[iCount] = 25.6215;
    iCount++;

    //Tree 44
    p_iSpecies[iCount] = 1;
    p_iType[iCount] = clTreePopulation::adult;
    p_fX[iCount] = 74.3191;
    p_fY[iCount] = 81.1496;
    p_fDiam[iCount] = 27.4837;
    iCount++;

    //Tree 45
    p_iSpecies[iCount] = 1;
    p_iType[iCount] = clTreePopulation::adult;
    p_fX[iCount] = 23.3972;
    p_fY[iCount] = 82.7297;
    p_fDiam[iCount] = 24.9638;
    iCount++;

    //Tree 46
    p_iSpecies[iCount] = 2;
    p_iType[iCount] = clTreePopulation::adult;
    p_fX[iCount] = 15.6913;
    p_fY[iCount] = 84.3219;
    p_fDiam[iCount] = 24.791;
    iCount++;

    //Tree 47
    p_iSpecies[iCount] = 2;
    p_iType[iCount] = clTreePopulation::adult;
    p_fX[iCount] = 38.6781;
    p_fY[iCount] = 84.8195;
    p_fDiam[iCount] = 25.1718;
    iCount++;

    //Tree 48
    p_iSpecies[iCount] = 2;
    p_iType[iCount] = clTreePopulation::sapling;
    p_fX[iCount] = 91.4707;
    p_fY[iCount] = 86.3797;
    p_fDiam[iCount] = 8.31;
    iCount++;

    //Tree 49
    p_iSpecies[iCount] = 2;
    p_iType[iCount] = clTreePopulation::adult;
    p_fX[iCount] = 37.5938;
    p_fY[iCount] = 87.2484;
    p_fDiam[iCount] = 15.9924;
    iCount++;

    //Tree 50
    p_iSpecies[iCount] = 2;
    p_iType[iCount] = clTreePopulation::sapling;
    p_fX[iCount] = 36.6376;
    p_fY[iCount] = 87.5301;
    p_fDiam[iCount] = 6.8901;
    iCount++;

    //Tree 51
    p_iSpecies[iCount] = 0;
    p_iType[iCount] = clTreePopulation::adult;
    p_fX[iCount] = 55.9163;
    p_fY[iCount] = 90.0189;
    p_fDiam[iCount] = 12.9417;
    iCount++;

    //Tree 52
    p_iSpecies[iCount] = 2;
    p_iType[iCount] = clTreePopulation::adult;
    p_fX[iCount] = 97.7476;
    p_fY[iCount] = 94.7417;
    p_fDiam[iCount] = 25.3651;
    iCount++;

    //Tree 53
    p_iSpecies[iCount] = 2;
    p_iType[iCount] = clTreePopulation::adult;
    p_fX[iCount] = 51.7177;
    p_fY[iCount] = 95.4606;
    p_fDiam[iCount] = 12.6799;
    iCount++;

    //Tree 54
    p_iSpecies[iCount] = 2;
    p_iType[iCount] = clTreePopulation::adult;
    p_fX[iCount] = 64.2286;
    p_fY[iCount] = 98.6715;
    p_fDiam[iCount] = 25.688;
    iCount++;

    //Tree 55
    p_iSpecies[iCount] = 0;
    p_iType[iCount] = clTreePopulation::adult;
    p_fX[iCount] = 96.6835;
    p_fY[iCount] = 98.7591;
    p_fDiam[iCount] = 17.3889;
    iCount++;

    for (i = 0; i < iNumTrees; i++) {
      p_oPop->CreateTree(p_fX[i], p_fY[i], p_iSpecies[i], p_iType[i], p_fDiam[i]);
    }

    //Now do the run
    p_oSimManager->RunSim(1);

    //Update the diameters for species 3 saplings - because they will have grown
    //Tree 38
    p_fDiam[37] = 8.04589;
    //Tree 40
    p_fDiam[39] = 5.14863;
    //Tree 48
    p_fDiam[47] = 9.21;
    //Tree 50
    p_fDiam[49] = 7.7901;

    for (i = 0; i < iNumTrees; i++) {
      p_bFound[i] = false;
    }

    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {

      iSp = p_oTree->GetSpecies();
      iTp = p_oTree->GetType();
      if (clTreePopulation::seedling == iTp)
        p_oTree->GetValue(p_oPop->GetDiam10Code(iSp, iTp), & fDiam);
      else
        p_oTree->GetValue(p_oPop->GetDbhCode(iSp, iTp), & fDiam);
      p_oTree->GetValue(p_oPop->GetXCode(iSp, iTp), & fX);
      p_oTree->GetValue(p_oPop->GetYCode(iSp, iTp), & fY);

      for (i = 0; i < iNumTrees; i++) {
        if (iSp == p_iSpecies[i] &&
            iTp == p_iType[i] &&
            fabs(fDiam - p_fDiam[i]) < 0.0001 &&
            fabs(fX - p_fX[i]) < 0.0001 &&
            fabs(fY - p_fY[i]) < 0.0001 ) {

          p_bFound[i] = true;
          break;
        }
      }

      p_oTree = p_oAllTrees->NextTree();
    }

    //Verify that certain trees are dead
    for (i = 0; i < iNumTrees; i++) {
      if ( 1 == i ||
          2 == i ||
          8 == i ||
          14 == i ||
          18 == i ||
          19 == i ||
          20 == i ||
          21 == i ||
          33 == i ||
          47 == i ||
          49 == i ) {

        EXPECT_FALSE(p_bFound[i]);
      } else {
        EXPECT_TRUE(p_bFound[i]);
      }
    }

    //Do the second timestep
    p_oSimManager->RunSim(1);

    //Verify that all trees die
    p_oAllTrees = p_oPop->Find("all");
    EXPECT_EQ(NULL, p_oAllTrees->NextTree());

    //Do the third timestep
    p_oSimManager->RunSim(1);

    //Verify that all trees are still dead
    p_oAllTrees = p_oPop->Find("all");
    EXPECT_EQ(NULL, p_oAllTrees->NextTree());

    delete[] p_bFound;
    delete[] p_fX;
    delete[] p_fY;
    delete[] p_fDiam;
    delete[] p_iSpecies;
    delete[] p_iType;

    sprintf(cPath, "%s%s", TESTPATH, "Test 2 Harvest.txt");
    DeleteThisFile(cPath);
    sprintf(cPath, "%s%s", TESTPATH, "Cut File 2.txt");
    DeleteThisFile(cPath);

    delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

////////////////////////////////////////////////////////////////////////////
// TestNormalProcessingRun3()
// Tests normal processing, run 3. This tests extra columns desired in the
// files, and new tree members to be added and updated. WriteHarvestInterfaceXMLFile3() does
// setup.
////////////////////////////////////////////////////////////////////////////
TEST(HarvestInterface, TestNormalProcessingRun3) {
  using namespace std;

  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    clTreePopulation * p_oPop;
    clTreeSearch *p_oAllTrees;
    clTree *p_oTree;
    char cPath[500];
    bool *p_bFound;
    float *p_fDiam, *p_fX, *p_fY, fX, fY, fDiam, fVal;
    int  iNumTrees = 55, iCount = 0, *p_iSpecies, *p_iType, i, iVal,
        iSp, iTp;

    p_bFound = new bool[iNumTrees];
    p_fX = new float[iNumTrees];
    p_fY = new float[iNumTrees];
    p_fDiam = new float[iNumTrees];
    p_iSpecies = new int[iNumTrees];
    p_iType = new int[iNumTrees];

    //Load our test file and get our tree population pointers
    p_oSimManager->ReadFile( WriteHarvestInterfaceXMLFile3() );
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );

    //Create our trees
    //Tree 1
    p_iSpecies[iCount] = 1;
    p_iType[iCount] = clTreePopulation::adult;
    p_fX[iCount] = 42.0525;
    p_fY[iCount] = 2.21632;
    p_fDiam[iCount] = 20.5095;
    iCount++;

    //Tree 2
    p_iSpecies[iCount] = 1;
    p_iType[iCount] = clTreePopulation::adult;
    p_fX[iCount] = 74.4779;
    p_fY[iCount] = 2.86341;
    p_fDiam[iCount] = 26.2185;
    iCount++;

    //Tree 3
    p_iSpecies[iCount] = 2;
    p_iType[iCount] = clTreePopulation::adult;
    p_fX[iCount] = 36.3822;
    p_fY[iCount] = 2.95831;
    p_fDiam[iCount] = 21.2419;
    iCount++;

    //Tree 4
    p_iSpecies[iCount] = 1;
    p_iType[iCount] = clTreePopulation::adult;
    p_fX[iCount] = 26.7469;
    p_fY[iCount] = 3.75704;
    p_fDiam[iCount] = 13.6089;
    iCount++;

    //Tree 5
    p_iSpecies[iCount] = 0;
    p_iType[iCount] = clTreePopulation::sapling;
    p_fX[iCount] = 49.8263;
    p_fY[iCount] = 4.18441;
    p_fDiam[iCount] = 6.42101;
    iCount++;

    //Tree 6
    p_iSpecies[iCount] = 1;
    p_iType[iCount] = clTreePopulation::adult;
    p_fX[iCount] = 27.794;
    p_fY[iCount] = 8.64942;
    p_fDiam[iCount] = 28.5256;
    iCount++;

    //Tree 7
    p_iSpecies[iCount] = 1;
    p_iType[iCount] = clTreePopulation::adult;
    p_fX[iCount] = 78.0224;
    p_fY[iCount] = 12.6457;
    p_fDiam[iCount] = 26.3755;
    iCount++;

    //Tree 8
    p_iSpecies[iCount] = 0;
    p_iType[iCount] = clTreePopulation::sapling;
    p_fX[iCount] = 88.2882;
    p_fY[iCount] = 13.1436;
    p_fDiam[iCount] = 3.8165;
    iCount++;

    //Tree 9
    p_iSpecies[iCount] = 1;
    p_iType[iCount] = clTreePopulation::adult;
    p_fX[iCount] = 72.0387;
    p_fY[iCount] = 13.9719;
    p_fDiam[iCount] = 12.3629;
    iCount++;

    //Tree 10
    p_iSpecies[iCount] = 0;
    p_iType[iCount] = clTreePopulation::adult;
    p_fX[iCount] = 18.4304;
    p_fY[iCount] = 15.3092;
    p_fDiam[iCount] = 13.8248;
    iCount++;

    //Tree 11
    p_iSpecies[iCount] = 0;
    p_iType[iCount] = clTreePopulation::seedling;
    p_fX[iCount] = 39.366;
    p_fY[iCount] = 19.9556;
    p_fDiam[iCount] = 1.12;
    iCount++;

    //Tree 12
    p_iSpecies[iCount] = 1;
    p_iType[iCount] = clTreePopulation::seedling;
    p_fX[iCount] = 86.5371;
    p_fY[iCount] = 20.0087;
    p_fDiam[iCount] = 1.14;
    iCount++;

    //Tree 13
    p_iSpecies[iCount] = 2;
    p_iType[iCount] = clTreePopulation::seedling;
    p_fX[iCount] = 93.3186;
    p_fY[iCount] = 20.998;
    p_fDiam[iCount] = 1.2;
    iCount++;

    //Tree 14
    p_iSpecies[iCount] = 2;
    p_iType[iCount] = clTreePopulation::seedling;
    p_fX[iCount] = 30.1811;
    p_fY[iCount] = 21.9206;
    p_fDiam[iCount] = 1.12;
    iCount++;

    //Tree 15
    p_iSpecies[iCount] = 0;
    p_iType[iCount] = clTreePopulation::seedling;
    p_fX[iCount] = 28.4697;
    p_fY[iCount] = 22.4661;
    p_fDiam[iCount] = 1.14;
    iCount++;

    //Tree 16
    p_iSpecies[iCount] = 1;
    p_iType[iCount] = clTreePopulation::adult;
    p_fX[iCount] = 55.9178;
    p_fY[iCount] = 25.7332;
    p_fDiam[iCount] = 17.3983;
    iCount++;

    //Tree 17
    p_iSpecies[iCount] = 2;
    p_iType[iCount] = clTreePopulation::adult;
    p_fX[iCount] = 20.4647;
    p_fY[iCount] = 27.7396;
    p_fDiam[iCount] = 24.272;
    iCount++;

    //Tree 18
    p_iSpecies[iCount] = 0;
    p_iType[iCount] = clTreePopulation::sapling;
    p_fX[iCount] = 98.1614;
    p_fY[iCount] = 29.6613;
    p_fDiam[iCount] = 8.42262;
    iCount++;

    //Tree 19
    p_iSpecies[iCount] = 2;
    p_iType[iCount] = clTreePopulation::adult;
    p_fX[iCount] = 74.1404;
    p_fY[iCount] = 39.8158;
    p_fDiam[iCount] = 24.7286;
    iCount++;

    //Tree 20
    p_iSpecies[iCount] = 1;
    p_iType[iCount] = clTreePopulation::adult;
    p_fX[iCount] = 90.0865;
    p_fY[iCount] = 40.4886;
    p_fDiam[iCount] = 28.1205;
    iCount++;

    //Tree 21
    p_iSpecies[iCount] = 2;
    p_iType[iCount] = clTreePopulation::adult;
    p_fX[iCount] = 94.9792;
    p_fY[iCount] = 40.9522;
    p_fDiam[iCount] = 24.5678;
    iCount++;

    //Tree 22
    p_iSpecies[iCount] = 2;
    p_iType[iCount] = clTreePopulation::adult;
    p_fX[iCount] = 36.0762;
    p_fY[iCount] = 42.6468;
    p_fDiam[iCount] = 20.4855;
    iCount++;

    //Tree 23
    p_iSpecies[iCount] = 0;
    p_iType[iCount] = clTreePopulation::adult;
    p_fX[iCount] = 70.1652;
    p_fY[iCount] = 43.3971;
    p_fDiam[iCount] = 15.1196;
    iCount++;

    //Tree 24
    p_iSpecies[iCount] = 1;
    p_iType[iCount] = clTreePopulation::adult;
    p_fX[iCount] = 67.6349;
    p_fY[iCount] = 47.9413;
    p_fDiam[iCount] = 26.2077;
    iCount++;

    //Tree 25
    p_iSpecies[iCount] = 0;
    p_iType[iCount] = clTreePopulation::sapling;
    p_fX[iCount] = 69.7277;
    p_fY[iCount] = 48.6251;
    p_fDiam[iCount] = 7.98507;
    iCount++;

    //Tree 26
    p_iSpecies[iCount] = 2;
    p_iType[iCount] = clTreePopulation::adult;
    p_fX[iCount] = 86.0179;
    p_fY[iCount] = 49.4856;
    p_fDiam[iCount] = 17.5575;
    iCount++;

    //Tree 27
    p_iSpecies[iCount] = 2;
    p_iType[iCount] = clTreePopulation::adult;
    p_fX[iCount] = 68.888;
    p_fY[iCount] = 50.1366;
    p_fDiam[iCount] = 24.708;
    iCount++;

    //Tree 28
    p_iSpecies[iCount] = 1;
    p_iType[iCount] = clTreePopulation::adult;
    p_fX[iCount] = 84.6036;
    p_fY[iCount] = 50.93;
    p_fDiam[iCount] = 21.3454;
    iCount++;

    //Tree 29
    p_iSpecies[iCount] = 2;
    p_iType[iCount] = clTreePopulation::adult;
    p_fX[iCount] = 25.7016;
    p_fY[iCount] = 54.1108;
    p_fDiam[iCount] = 20.7396;
    iCount++;

    //Tree 30
    p_iSpecies[iCount] = 2;
    p_iType[iCount] = clTreePopulation::adult;
    p_fX[iCount] = 21.2453;
    p_fY[iCount] = 54.7161;
    p_fDiam[iCount] = 12.1276;
    iCount++;

    //Tree 31
    p_iSpecies[iCount] = 0;
    p_iType[iCount] = clTreePopulation::sapling;
    p_fX[iCount] = 14.3788;
    p_fY[iCount] = 55.4155;
    p_fDiam[iCount] = 5.12777;
    iCount++;

    //Tree 32
    p_iSpecies[iCount] = 0;
    p_iType[iCount] = clTreePopulation::adult;
    p_fX[iCount] = 60.6626;
    p_fY[iCount] = 55.657;
    p_fDiam[iCount] = 16.8162;
    iCount++;

    //Tree 33
    p_iSpecies[iCount] = 2;
    p_iType[iCount] = clTreePopulation::adult;
    p_fX[iCount] = 71.3062;
    p_fY[iCount] = 56.5974;
    p_fDiam[iCount] = 24.7457;
    iCount++;

    //Tree 34
    p_iSpecies[iCount] = 2;
    p_iType[iCount] = clTreePopulation::adult;
    p_fX[iCount] = 9.38922;
    p_fY[iCount] = 59.3884;
    p_fDiam[iCount] = 19.1746;
    iCount++;

    //Tree 35
    p_iSpecies[iCount] = 2;
    p_iType[iCount] = clTreePopulation::adult;
    p_fX[iCount] = 27.1944;
    p_fY[iCount] = 63.1713;
    p_fDiam[iCount] = 26.0429;
    iCount++;

    //Tree 36
    p_iSpecies[iCount] = 0;
    p_iType[iCount] = clTreePopulation::adult;
    p_fX[iCount] = 61.7164;
    p_fY[iCount] = 66.0961;
    p_fDiam[iCount] = 17.1742;
    iCount++;

    //Tree 37
    p_iSpecies[iCount] = 1;
    p_iType[iCount] = clTreePopulation::adult;
    p_fX[iCount] = 34.2957;
    p_fY[iCount] = 67.5466;
    p_fDiam[iCount] = 16.9941;
    iCount++;

    //Tree 38
    p_iSpecies[iCount] = 2;
    p_iType[iCount] = clTreePopulation::sapling;
    p_fX[iCount] = 41.5812;
    p_fY[iCount] = 71.8411;
    p_fDiam[iCount] = 7.14589;
    iCount++;

    //Tree 39
    p_iSpecies[iCount] = 1;
    p_iType[iCount] = clTreePopulation::adult;
    p_fX[iCount] = 28.2031;
    p_fY[iCount] = 72.6295;
    p_fDiam[iCount] = 23.4028;
    iCount++;

    //Tree 40
    p_iSpecies[iCount] = 2;
    p_iType[iCount] = clTreePopulation::sapling;
    p_fX[iCount] = 6.33182;
    p_fY[iCount] = 75.0587;
    p_fDiam[iCount] = 4.24863;
    iCount++;

    //Tree 41
    p_iSpecies[iCount] = 1;
    p_iType[iCount] = clTreePopulation::adult;
    p_fX[iCount] = 63.196;
    p_fY[iCount] = 77.6672;
    p_fDiam[iCount] = 24.5384;
    iCount++;

    //Tree 42
    p_iSpecies[iCount] = 1;
    p_iType[iCount] = clTreePopulation::adult;
    p_fX[iCount] = 47.198;
    p_fY[iCount] = 77.8982;
    p_fDiam[iCount] = 24.5211;
    iCount++;

    //Tree 43
    p_iSpecies[iCount] = 2;
    p_iType[iCount] = clTreePopulation::adult;
    p_fX[iCount] = 1.12617;
    p_fY[iCount] = 78.3586;
    p_fDiam[iCount] = 25.6215;
    iCount++;

    //Tree 44
    p_iSpecies[iCount] = 1;
    p_iType[iCount] = clTreePopulation::adult;
    p_fX[iCount] = 74.3191;
    p_fY[iCount] = 81.1496;
    p_fDiam[iCount] = 27.4837;
    iCount++;

    //Tree 45
    p_iSpecies[iCount] = 1;
    p_iType[iCount] = clTreePopulation::adult;
    p_fX[iCount] = 23.3972;
    p_fY[iCount] = 82.7297;
    p_fDiam[iCount] = 24.9638;
    iCount++;

    //Tree 46
    p_iSpecies[iCount] = 2;
    p_iType[iCount] = clTreePopulation::adult;
    p_fX[iCount] = 15.6913;
    p_fY[iCount] = 84.3219;
    p_fDiam[iCount] = 24.791;
    iCount++;

    //Tree 47
    p_iSpecies[iCount] = 2;
    p_iType[iCount] = clTreePopulation::adult;
    p_fX[iCount] = 38.6781;
    p_fY[iCount] = 84.8195;
    p_fDiam[iCount] = 25.1718;
    iCount++;

    //Tree 48
    p_iSpecies[iCount] = 2;
    p_iType[iCount] = clTreePopulation::sapling;
    p_fX[iCount] = 91.4707;
    p_fY[iCount] = 86.3797;
    p_fDiam[iCount] = 8.31;
    iCount++;

    //Tree 49
    p_iSpecies[iCount] = 2;
    p_iType[iCount] = clTreePopulation::adult;
    p_fX[iCount] = 37.5938;
    p_fY[iCount] = 87.2484;
    p_fDiam[iCount] = 15.9924;
    iCount++;

    //Tree 50
    p_iSpecies[iCount] = 2;
    p_iType[iCount] = clTreePopulation::sapling;
    p_fX[iCount] = 36.6376;
    p_fY[iCount] = 87.5301;
    p_fDiam[iCount] = 6.8901;
    iCount++;

    //Tree 51
    p_iSpecies[iCount] = 0;
    p_iType[iCount] = clTreePopulation::adult;
    p_fX[iCount] = 55.9163;
    p_fY[iCount] = 90.0189;
    p_fDiam[iCount] = 12.9417;
    iCount++;

    //Tree 52
    p_iSpecies[iCount] = 2;
    p_iType[iCount] = clTreePopulation::adult;
    p_fX[iCount] = 97.7476;
    p_fY[iCount] = 94.7417;
    p_fDiam[iCount] = 25.3651;
    iCount++;

    //Tree 53
    p_iSpecies[iCount] = 2;
    p_iType[iCount] = clTreePopulation::adult;
    p_fX[iCount] = 51.7177;
    p_fY[iCount] = 95.4606;
    p_fDiam[iCount] = 12.6799;
    iCount++;

    //Tree 54
    p_iSpecies[iCount] = 2;
    p_iType[iCount] = clTreePopulation::adult;
    p_fX[iCount] = 64.2286;
    p_fY[iCount] = 98.6715;
    p_fDiam[iCount] = 25.688;
    iCount++;

    //Tree 55
    p_iSpecies[iCount] = 0;
    p_iType[iCount] = clTreePopulation::adult;
    p_fX[iCount] = 96.6835;
    p_fY[iCount] = 98.7591;
    p_fDiam[iCount] = 17.3889;
    iCount++;

    for (i = 0; i < iNumTrees; i++) {
      p_oPop->CreateTree(p_fX[i], p_fY[i], p_iSpecies[i], p_iType[i], p_fDiam[i]);
    }

    //***********************************************************
    // Timestep 1
    //***********************************************************
    p_oSimManager->RunSim(1);

    for (i = 0; i < iNumTrees; i++) {
      p_bFound[i] = false;
    }

    //There should be no harvests or updates
    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {

      iSp = p_oTree->GetSpecies();
      iTp = p_oTree->GetType();
      if (clTreePopulation::seedling == iTp)
        p_oTree->GetValue(p_oPop->GetDiam10Code(iSp, iTp), & fDiam);
      else
        p_oTree->GetValue(p_oPop->GetDbhCode(iSp, iTp), & fDiam);
      p_oTree->GetValue(p_oPop->GetXCode(iSp, iTp), & fX);
      p_oTree->GetValue(p_oPop->GetYCode(iSp, iTp), & fY);

      //Verify test values are still all 0
      p_oTree->GetValue(p_oPop->GetFloatDataCode("test 1", iSp, iTp), &fVal);
      EXPECT_LT(fabs(fVal), 0.0001);
      p_oTree->GetValue(p_oPop->GetFloatDataCode("test 2", iSp, iTp), &fVal);
      EXPECT_LT(fabs(fVal), 0.0001);
      p_oTree->GetValue(p_oPop->GetFloatDataCode("test 3", iSp, iTp), &fVal);
      EXPECT_LT(fabs(fVal), 0.0001);

      //Verify that the "dead" and "Tree Age" values are un-messed-with
      p_oTree->GetValue(p_oPop->GetIntDataCode("Tree Age", iSp, iTp), &iVal);
      EXPECT_EQ(2, iVal);
      p_oTree->GetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), &iVal);
      EXPECT_EQ(notdead, iVal);

      for (i = 0; i < iNumTrees; i++) {
        if (iSp == p_iSpecies[i] &&
            iTp == p_iType[i] &&
            fabs(fDiam - p_fDiam[i]) < 0.0001 &&
            fabs(fX - p_fX[i]) < 0.0001 &&
            fabs(fY - p_fY[i]) < 0.0001 ) {

          p_bFound[i] = true;
          break;
        }
      }

      p_oTree = p_oAllTrees->NextTree();
    }

    //Verify that no trees have been harvested
    for (i = 0; i < iNumTrees; i++) {
      EXPECT_EQ(true, p_bFound[i]);
    }


    //***********************************************************
    // Timestep 2
    //***********************************************************
    p_oSimManager->RunSim(1);

    for (i = 0; i < iNumTrees; i++) {
      p_bFound[i] = false;
    }

    //There should be no harvests, only updates
    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {

      iSp = p_oTree->GetSpecies();
      iTp = p_oTree->GetType();
      if (clTreePopulation::seedling == iTp)
        p_oTree->GetValue(p_oPop->GetDiam10Code(iSp, iTp), & fDiam);
      else
        p_oTree->GetValue(p_oPop->GetDbhCode(iSp, iTp), & fDiam);
      p_oTree->GetValue(p_oPop->GetXCode(iSp, iTp), & fX);
      p_oTree->GetValue(p_oPop->GetYCode(iSp, iTp), & fY);

      //Verify test values are changed for some trees, not others

      //Tree 6
      if (fabs(fX - 27.794) < 0.001 && fabs(fY - 8.64942) < 0.001) {
        p_oTree->GetValue(p_oPop->GetFloatDataCode("test 1", iSp, iTp), &fVal);
        EXPECT_LT(fabs(fVal - 0.491), 0.0001);
        p_oTree->GetValue(p_oPop->GetFloatDataCode("test 2", iSp, iTp), &fVal);
        EXPECT_LT(fabs(fVal - 0.54), 0.0001);
        p_oTree->GetValue(p_oPop->GetFloatDataCode("test 3", iSp, iTp), &fVal);
        EXPECT_LT(fabs(fVal - 0.483), 0.0001);
      }

      //Tree 10
      else if (fabs(fX - 18.4304) < 0.001 && fabs(fY - 15.3092) < 0.001) {
        p_oTree->GetValue(p_oPop->GetFloatDataCode("test 1", iSp, iTp), &fVal);
        EXPECT_LT(fabs(fVal - 0.373), 0.0001);
        p_oTree->GetValue(p_oPop->GetFloatDataCode("test 2", iSp, iTp), &fVal);
        EXPECT_LT(fabs(fVal - 0.36), 0.0001);
        p_oTree->GetValue(p_oPop->GetFloatDataCode("test 3", iSp, iTp), &fVal);
        EXPECT_LT(fabs(fVal - 0.44), 0.0001);
      }

      //Tree 28
      else if (fabs(fX - 84.6036) < 0.001 && fabs(fY - 50.93) < 0.001) {
        p_oTree->GetValue(p_oPop->GetFloatDataCode("test 1", iSp, iTp), &fVal);
        EXPECT_LT(fabs(fVal - 23), 0.0001);
        p_oTree->GetValue(p_oPop->GetFloatDataCode("test 2", iSp, iTp), &fVal);
        EXPECT_LT(fabs(fVal - 23), 0.0001);
        p_oTree->GetValue(p_oPop->GetFloatDataCode("test 3", iSp, iTp), &fVal);
        EXPECT_LT(fabs(fVal - 23), 0.0001);
      }

      //Tree 34
      else if (fabs(fX - 9.38922) < 0.001 && fabs(fY - 59.3884) < 0.001) {
        p_oTree->GetValue(p_oPop->GetFloatDataCode("test 1", iSp, iTp), &fVal);
        EXPECT_LT(fabs(fVal - 33.352), 0.0001);
        p_oTree->GetValue(p_oPop->GetFloatDataCode("test 2", iSp, iTp), &fVal);
        EXPECT_LT(fabs(fVal - 23.81), 0.0001);
        p_oTree->GetValue(p_oPop->GetFloatDataCode("test 3", iSp, iTp), &fVal);
        EXPECT_LT(fabs(fVal - 19.76), 0.0001);
      }

      //Tree 40
      else if (fabs(fX - 6.33182) < 0.001 && fabs(fY - 75.0587) < 0.001) {
        p_oTree->GetValue(p_oPop->GetFloatDataCode("test 1", iSp, iTp), &fVal);
        EXPECT_LT(fabs(fVal - -0.23), 0.0001);
        p_oTree->GetValue(p_oPop->GetFloatDataCode("test 2", iSp, iTp), &fVal);
        EXPECT_LT(fabs(fVal - 0), 0.0001);
        p_oTree->GetValue(p_oPop->GetFloatDataCode("test 3", iSp, iTp), &fVal);
        EXPECT_LT(fabs(fVal - 15.66), 0.0001);
      }

      //Tree 50
      else if (fabs(fX - 36.6376) < 0.001 && fabs(fY - 87.5301) < 0.001) {
        p_oTree->GetValue(p_oPop->GetFloatDataCode("test 1", iSp, iTp), &fVal);
        EXPECT_LT(fabs(fVal - 0.011), 0.0001);
        p_oTree->GetValue(p_oPop->GetFloatDataCode("test 2", iSp, iTp), &fVal);
        EXPECT_LT(fabs(fVal - 0.075), 0.0001);
        p_oTree->GetValue(p_oPop->GetFloatDataCode("test 3", iSp, iTp), &fVal);
        EXPECT_LT(fabs(fVal - 0.086), 0.0001);
      }

      else {
        p_oTree->GetValue(p_oPop->GetFloatDataCode("test 1", iSp, iTp), &fVal);
        EXPECT_LT(fabs(fVal), 0.0001);
        p_oTree->GetValue(p_oPop->GetFloatDataCode("test 2", iSp, iTp), &fVal);
        EXPECT_LT(fabs(fVal), 0.0001);
        p_oTree->GetValue(p_oPop->GetFloatDataCode("test 3", iSp, iTp), &fVal);
        EXPECT_LT(fabs(fVal), 0.0001);
      }

      //Verify that the "dead" and "Tree Age" values are un-messed-with
      p_oTree->GetValue(p_oPop->GetIntDataCode("Tree Age", iSp, iTp), &iVal);
      EXPECT_EQ(4, iVal);
      p_oTree->GetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), &iVal);
      EXPECT_EQ(notdead, iVal);

      for (i = 0; i < iNumTrees; i++) {
        if (iSp == p_iSpecies[i] &&
            iTp == p_iType[i] &&
            fabs(fDiam - p_fDiam[i]) < 0.0001 &&
            fabs(fX - p_fX[i]) < 0.0001 &&
            fabs(fY - p_fY[i]) < 0.0001 ) {

          p_bFound[i] = true;
          break;
        }
      }

      p_oTree = p_oAllTrees->NextTree();
    }

    //Verify that no trees have been harvested
    for (i = 0; i < iNumTrees; i++) {
      EXPECT_EQ(true, p_bFound[i]);
    }

    //***********************************************************
    // Timestep 3
    //***********************************************************
    p_oSimManager->RunSim(1);

    for (i = 0; i < iNumTrees; i++) {
      p_bFound[i] = false;
    }

    //There should be no harvests or updates
    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {

      iSp = p_oTree->GetSpecies();
      iTp = p_oTree->GetType();
      if (clTreePopulation::seedling == iTp)
        p_oTree->GetValue(p_oPop->GetDiam10Code(iSp, iTp), & fDiam);
      else
        p_oTree->GetValue(p_oPop->GetDbhCode(iSp, iTp), & fDiam);
      p_oTree->GetValue(p_oPop->GetXCode(iSp, iTp), & fX);
      p_oTree->GetValue(p_oPop->GetYCode(iSp, iTp), & fY);

      //Verify that last timesteps' were the only updates

      //Tree 6
      if (fabs(fX - 27.794) < 0.001 && fabs(fY - 8.64942) < 0.001) {
        p_oTree->GetValue(p_oPop->GetFloatDataCode("test 1", iSp, iTp), &fVal);
        EXPECT_LT(fabs(fVal - 0.491), 0.0001);
        p_oTree->GetValue(p_oPop->GetFloatDataCode("test 2", iSp, iTp), &fVal);
        EXPECT_LT(fabs(fVal - 0.54), 0.0001);
        p_oTree->GetValue(p_oPop->GetFloatDataCode("test 3", iSp, iTp), &fVal);
        EXPECT_LT(fabs(fVal - 0.483), 0.0001);
      }

      //Tree 10
      else if (fabs(fX - 18.4304) < 0.001 && fabs(fY - 15.3092) < 0.001) {
        p_oTree->GetValue(p_oPop->GetFloatDataCode("test 1", iSp, iTp), &fVal);
        EXPECT_LT(fabs(fVal - 0.373), 0.0001);
        p_oTree->GetValue(p_oPop->GetFloatDataCode("test 2", iSp, iTp), &fVal);
        EXPECT_LT(fabs(fVal - 0.36), 0.0001);
        p_oTree->GetValue(p_oPop->GetFloatDataCode("test 3", iSp, iTp), &fVal);
        EXPECT_LT(fabs(fVal - 0.44), 0.0001);
      }

      //Tree 28
      else if (fabs(fX - 84.6036) < 0.001 && fabs(fY - 50.93) < 0.001) {
        p_oTree->GetValue(p_oPop->GetFloatDataCode("test 1", iSp, iTp), &fVal);
        EXPECT_LT(fabs(fVal - 23), 0.0001);
        p_oTree->GetValue(p_oPop->GetFloatDataCode("test 2", iSp, iTp), &fVal);
        EXPECT_LT(fabs(fVal - 23), 0.0001);
        p_oTree->GetValue(p_oPop->GetFloatDataCode("test 3", iSp, iTp), &fVal);
        EXPECT_LT(fabs(fVal - 23), 0.0001);
      }

      //Tree 34
      else if (fabs(fX - 9.38922) < 0.001 && fabs(fY - 59.3884) < 0.001) {
        p_oTree->GetValue(p_oPop->GetFloatDataCode("test 1", iSp, iTp), &fVal);
        EXPECT_LT(fabs(fVal - 33.352), 0.0001);
        p_oTree->GetValue(p_oPop->GetFloatDataCode("test 2", iSp, iTp), &fVal);
        EXPECT_LT(fabs(fVal - 23.81), 0.0001);
        p_oTree->GetValue(p_oPop->GetFloatDataCode("test 3", iSp, iTp), &fVal);
        EXPECT_LT(fabs(fVal - 19.76), 0.0001);
      }

      //Tree 40
      else if (fabs(fX - 6.33182) < 0.001 && fabs(fY - 75.0587) < 0.001) {
        p_oTree->GetValue(p_oPop->GetFloatDataCode("test 1", iSp, iTp), &fVal);
        EXPECT_LT(fabs(fVal - -0.23), 0.0001);
        p_oTree->GetValue(p_oPop->GetFloatDataCode("test 2", iSp, iTp), &fVal);
        EXPECT_LT(fabs(fVal - 0), 0.0001);
        p_oTree->GetValue(p_oPop->GetFloatDataCode("test 3", iSp, iTp), &fVal);
        EXPECT_LT(fabs(fVal - 15.66), 0.0001);
      }

      //Tree 50
      else if (fabs(fX - 36.6376) < 0.001 && fabs(fY - 87.5301) < 0.001) {
        p_oTree->GetValue(p_oPop->GetFloatDataCode("test 1", iSp, iTp), &fVal);
        EXPECT_LT(fabs(fVal - 0.011), 0.0001);
        p_oTree->GetValue(p_oPop->GetFloatDataCode("test 2", iSp, iTp), &fVal);
        EXPECT_LT(fabs(fVal - 0.075), 0.0001);
        p_oTree->GetValue(p_oPop->GetFloatDataCode("test 3", iSp, iTp), &fVal);
        EXPECT_LT(fabs(fVal - 0.086), 0.0001);
      }

      else {
        p_oTree->GetValue(p_oPop->GetFloatDataCode("test 1", iSp, iTp), &fVal);
        EXPECT_LT(fabs(fVal), 0.0001);
        p_oTree->GetValue(p_oPop->GetFloatDataCode("test 2", iSp, iTp), &fVal);
        EXPECT_LT(fabs(fVal), 0.0001);
        p_oTree->GetValue(p_oPop->GetFloatDataCode("test 3", iSp, iTp), &fVal);
        EXPECT_LT(fabs(fVal), 0.0001);
      }

      //Verify that the "dead" and "Tree Age" values are un-messed-with
      p_oTree->GetValue(p_oPop->GetIntDataCode("Tree Age", iSp, iTp), &iVal);
      EXPECT_EQ(6, iVal);
      p_oTree->GetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), &iVal);
      EXPECT_EQ(notdead, iVal);

      for (i = 0; i < iNumTrees; i++) {
        if (iSp == p_iSpecies[i] &&
            iTp == p_iType[i] &&
            fabs(fDiam - p_fDiam[i]) < 0.0001 &&
            fabs(fX - p_fX[i]) < 0.0001 &&
            fabs(fY - p_fY[i]) < 0.0001 ) {

          p_bFound[i] = true;
          break;
        }
      }

      p_oTree = p_oAllTrees->NextTree();
    }

    //Verify that no trees have been harvested
    for (i = 0; i < iNumTrees; i++) {
      EXPECT_EQ(true, p_bFound[i]);
    }

    //***********************************************************
    // Timestep 4
    //***********************************************************
    p_oSimManager->RunSim(1);

    for (i = 0; i < iNumTrees; i++) {
      p_bFound[i] = false;
    }

    //There should be one harvest, and no new updates
    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {

      iSp = p_oTree->GetSpecies();
      iTp = p_oTree->GetType();
      if (clTreePopulation::seedling == iTp)
        p_oTree->GetValue(p_oPop->GetDiam10Code(iSp, iTp), & fDiam);
      else
        p_oTree->GetValue(p_oPop->GetDbhCode(iSp, iTp), & fDiam);
      p_oTree->GetValue(p_oPop->GetXCode(iSp, iTp), & fX);
      p_oTree->GetValue(p_oPop->GetYCode(iSp, iTp), & fY);

      //Verify test values are changed for some trees, not others

      //Tree 6
      if (fabs(fX - 27.794) < 0.001 && fabs(fY - 8.64942) < 0.001) {
        p_oTree->GetValue(p_oPop->GetFloatDataCode("test 1", iSp, iTp), &fVal);
        EXPECT_LT(fabs(fVal - 0.491), 0.0001);
        p_oTree->GetValue(p_oPop->GetFloatDataCode("test 2", iSp, iTp), &fVal);
        EXPECT_LT(fabs(fVal - 0.54), 0.0001);
        p_oTree->GetValue(p_oPop->GetFloatDataCode("test 3", iSp, iTp), &fVal);
        EXPECT_LT(fabs(fVal - 0.483), 0.0001);
      }

      //Tree 10
      else if (fabs(fX - 18.4304) < 0.001 && fabs(fY - 15.3092) < 0.001) {
        p_oTree->GetValue(p_oPop->GetFloatDataCode("test 1", iSp, iTp), &fVal);
        EXPECT_LT(fabs(fVal - 0.373), 0.0001);
        p_oTree->GetValue(p_oPop->GetFloatDataCode("test 2", iSp, iTp), &fVal);
        EXPECT_LT(fabs(fVal - 0.36), 0.0001);
        p_oTree->GetValue(p_oPop->GetFloatDataCode("test 3", iSp, iTp), &fVal);
        EXPECT_LT(fabs(fVal - 0.44), 0.0001);
      }

      //Tree 28
      else if (fabs(fX - 84.6036) < 0.001 && fabs(fY - 50.93) < 0.001) {
        p_oTree->GetValue(p_oPop->GetFloatDataCode("test 1", iSp, iTp), &fVal);
        EXPECT_LT(fabs(fVal - 23), 0.0001);
        p_oTree->GetValue(p_oPop->GetFloatDataCode("test 2", iSp, iTp), &fVal);
        EXPECT_LT(fabs(fVal - 23), 0.0001);
        p_oTree->GetValue(p_oPop->GetFloatDataCode("test 3", iSp, iTp), &fVal);
        EXPECT_LT(fabs(fVal - 23), 0.0001);
      }

      //Tree 34
      else if (fabs(fX - 9.38922) < 0.001 && fabs(fY - 59.3884) < 0.001) {
        p_oTree->GetValue(p_oPop->GetFloatDataCode("test 1", iSp, iTp), &fVal);
        EXPECT_LT(fabs(fVal - 33.352), 0.0001);
        p_oTree->GetValue(p_oPop->GetFloatDataCode("test 2", iSp, iTp), &fVal);
        EXPECT_LT(fabs(fVal - 23.81), 0.0001);
        p_oTree->GetValue(p_oPop->GetFloatDataCode("test 3", iSp, iTp), &fVal);
        EXPECT_LT(fabs(fVal - 19.76), 0.0001);
      }

      //Tree 40
      else if (fabs(fX - 6.33182) < 0.001 && fabs(fY - 75.0587) < 0.001) {
        p_oTree->GetValue(p_oPop->GetFloatDataCode("test 1", iSp, iTp), &fVal);
        EXPECT_LT(fabs(fVal - -0.23), 0.0001);
        p_oTree->GetValue(p_oPop->GetFloatDataCode("test 2", iSp, iTp), &fVal);
        EXPECT_LT(fabs(fVal - 0), 0.0001);
        p_oTree->GetValue(p_oPop->GetFloatDataCode("test 3", iSp, iTp), &fVal);
        EXPECT_LT(fabs(fVal - 15.66), 0.0001);
      }

      //Tree 50
      else if (fabs(fX - 36.6376) < 0.001 && fabs(fY - 87.5301) < 0.001) {
        p_oTree->GetValue(p_oPop->GetFloatDataCode("test 1", iSp, iTp), &fVal);
        EXPECT_LT(fabs(fVal - 0.011), 0.0001);
        p_oTree->GetValue(p_oPop->GetFloatDataCode("test 2", iSp, iTp), &fVal);
        EXPECT_LT(fabs(fVal - 0.075), 0.0001);
        p_oTree->GetValue(p_oPop->GetFloatDataCode("test 3", iSp, iTp), &fVal);
        EXPECT_LT(fabs(fVal - 0.086), 0.0001);
      }

      else {
        p_oTree->GetValue(p_oPop->GetFloatDataCode("test 1", iSp, iTp), &fVal);
        EXPECT_LT(fabs(fVal), 0.0001);
        p_oTree->GetValue(p_oPop->GetFloatDataCode("test 2", iSp, iTp), &fVal);
        EXPECT_LT(fabs(fVal), 0.0001);
        p_oTree->GetValue(p_oPop->GetFloatDataCode("test 3", iSp, iTp), &fVal);
        EXPECT_LT(fabs(fVal), 0.0001);
      }

      //Verify that the "dead" and "Tree Age" values are un-messed-with
      p_oTree->GetValue(p_oPop->GetIntDataCode("Tree Age", iSp, iTp), &iVal);
      EXPECT_EQ(8, iVal);
      p_oTree->GetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), &iVal);
      EXPECT_EQ(notdead, iVal);

      for (i = 0; i < iNumTrees; i++) {
        if (iSp == p_iSpecies[i] &&
            iTp == p_iType[i] &&
            fabs(fDiam - p_fDiam[i]) < 0.0001 &&
            fabs(fX - p_fX[i]) < 0.0001 &&
            fabs(fY - p_fY[i]) < 0.0001 ) {

          p_bFound[i] = true;
          break;
        }
      }

      p_oTree = p_oAllTrees->NextTree();
    }

    //Verify that the right trees have been harvested
    for (i = 0; i < iNumTrees; i++) {
      if (1 == i) {
        EXPECT_FALSE(p_bFound[i]);
      } else {
        EXPECT_TRUE(p_bFound[i]);
      }
    }

    //***********************************************************
    // Timestep 5 - exactly like timestep 4
    //***********************************************************
    p_oSimManager->RunSim(1);

    for (i = 0; i < iNumTrees; i++) {
      p_bFound[i] = false;
    }

    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {

      iSp = p_oTree->GetSpecies();
      iTp = p_oTree->GetType();
      if (clTreePopulation::seedling == iTp)
        p_oTree->GetValue(p_oPop->GetDiam10Code(iSp, iTp), & fDiam);
      else
        p_oTree->GetValue(p_oPop->GetDbhCode(iSp, iTp), & fDiam);
      p_oTree->GetValue(p_oPop->GetXCode(iSp, iTp), & fX);
      p_oTree->GetValue(p_oPop->GetYCode(iSp, iTp), & fY);

      //Verify test values are changed for some trees, not others

      //Tree 6
      if (fabs(fX - 27.794) < 0.001 && fabs(fY - 8.64942) < 0.001) {
        p_oTree->GetValue(p_oPop->GetFloatDataCode("test 1", iSp, iTp), &fVal);
        EXPECT_LT(fabs(fVal - 0.491), 0.0001);
        p_oTree->GetValue(p_oPop->GetFloatDataCode("test 2", iSp, iTp), &fVal);
        EXPECT_LT(fabs(fVal - 0.54), 0.0001);
        p_oTree->GetValue(p_oPop->GetFloatDataCode("test 3", iSp, iTp), &fVal);
        EXPECT_LT(fabs(fVal - 0.483), 0.0001);
      }

      //Tree 10
      else if (fabs(fX - 18.4304) < 0.001 && fabs(fY - 15.3092) < 0.001) {
        p_oTree->GetValue(p_oPop->GetFloatDataCode("test 1", iSp, iTp), &fVal);
        EXPECT_LT(fabs(fVal - 0.373), 0.0001);
        p_oTree->GetValue(p_oPop->GetFloatDataCode("test 2", iSp, iTp), &fVal);
        EXPECT_LT(fabs(fVal - 0.36), 0.0001);
        p_oTree->GetValue(p_oPop->GetFloatDataCode("test 3", iSp, iTp), &fVal);
        EXPECT_LT(fabs(fVal - 0.44), 0.0001);
      }

      //Tree 28
      else if (fabs(fX - 84.6036) < 0.001 && fabs(fY - 50.93) < 0.001) {
        p_oTree->GetValue(p_oPop->GetFloatDataCode("test 1", iSp, iTp), &fVal);
        EXPECT_LT(fabs(fVal - 23), 0.0001);
        p_oTree->GetValue(p_oPop->GetFloatDataCode("test 2", iSp, iTp), &fVal);
        EXPECT_LT(fabs(fVal - 23), 0.0001);
        p_oTree->GetValue(p_oPop->GetFloatDataCode("test 3", iSp, iTp), &fVal);
        EXPECT_LT(fabs(fVal - 23), 0.0001);
      }

      //Tree 34
      else if (fabs(fX - 9.38922) < 0.001 && fabs(fY - 59.3884) < 0.001) {
        p_oTree->GetValue(p_oPop->GetFloatDataCode("test 1", iSp, iTp), &fVal);
        EXPECT_LT(fabs(fVal - 33.352), 0.0001);
        p_oTree->GetValue(p_oPop->GetFloatDataCode("test 2", iSp, iTp), &fVal);
        EXPECT_LT(fabs(fVal - 23.81), 0.0001);
        p_oTree->GetValue(p_oPop->GetFloatDataCode("test 3", iSp, iTp), &fVal);
        EXPECT_LT(fabs(fVal - 19.76), 0.0001);
      }

      //Tree 40
      else if (fabs(fX - 6.33182) < 0.001 && fabs(fY - 75.0587) < 0.001) {
        p_oTree->GetValue(p_oPop->GetFloatDataCode("test 1", iSp, iTp), &fVal);
        EXPECT_LT(fabs(fVal - -0.23), 0.0001);
        p_oTree->GetValue(p_oPop->GetFloatDataCode("test 2", iSp, iTp), &fVal);
        EXPECT_LT(fabs(fVal - 0), 0.0001);
        p_oTree->GetValue(p_oPop->GetFloatDataCode("test 3", iSp, iTp), &fVal);
        EXPECT_LT(fabs(fVal - 15.66), 0.0001);
      }

      //Tree 50
      else if (fabs(fX - 36.6376) < 0.001 && fabs(fY - 87.5301) < 0.001) {
        p_oTree->GetValue(p_oPop->GetFloatDataCode("test 1", iSp, iTp), &fVal);
        EXPECT_LT(fabs(fVal - 0.011), 0.0001);
        p_oTree->GetValue(p_oPop->GetFloatDataCode("test 2", iSp, iTp), &fVal);
        EXPECT_LT(fabs(fVal - 0.075), 0.0001);
        p_oTree->GetValue(p_oPop->GetFloatDataCode("test 3", iSp, iTp), &fVal);
        EXPECT_LT(fabs(fVal - 0.086), 0.0001);
      }

      else {
        p_oTree->GetValue(p_oPop->GetFloatDataCode("test 1", iSp, iTp), &fVal);
        EXPECT_LT(fabs(fVal), 0.0001);
        p_oTree->GetValue(p_oPop->GetFloatDataCode("test 2", iSp, iTp), &fVal);
        EXPECT_LT(fabs(fVal), 0.0001);
        p_oTree->GetValue(p_oPop->GetFloatDataCode("test 3", iSp, iTp), &fVal);
        EXPECT_LT(fabs(fVal), 0.0001);
      }

      //Verify that the "dead" and "Tree Age" values are un-messed-with
      p_oTree->GetValue(p_oPop->GetIntDataCode("Tree Age", iSp, iTp), &iVal);
      EXPECT_EQ(10, iVal);
      p_oTree->GetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), &iVal);
      EXPECT_EQ(notdead, iVal);

      for (i = 0; i < iNumTrees; i++) {
        if (iSp == p_iSpecies[i] &&
            iTp == p_iType[i] &&
            fabs(fDiam - p_fDiam[i]) < 0.0001 &&
            fabs(fX - p_fX[i]) < 0.0001 &&
            fabs(fY - p_fY[i]) < 0.0001 ) {

          p_bFound[i] = true;
          break;
        }
      }

      p_oTree = p_oAllTrees->NextTree();
    }

    //Verify that the right trees have been harvested
    for (i = 0; i < iNumTrees; i++) {
      if (1 == i) {
        EXPECT_FALSE(p_bFound[i]);
      } else {
        EXPECT_TRUE(p_bFound[i]);
      }
    }

    //***********************************************************
    // Timestep 6
    //***********************************************************
    p_oSimManager->RunSim(1);

    for (i = 0; i < iNumTrees; i++) {
      p_bFound[i] = false;
    }

    //There should be harvests and updates
    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {

      iSp = p_oTree->GetSpecies();
      iTp = p_oTree->GetType();
      if (clTreePopulation::seedling == iTp)
        p_oTree->GetValue(p_oPop->GetDiam10Code(iSp, iTp), & fDiam);
      else
        p_oTree->GetValue(p_oPop->GetDbhCode(iSp, iTp), & fDiam);
      p_oTree->GetValue(p_oPop->GetXCode(iSp, iTp), & fX);
      p_oTree->GetValue(p_oPop->GetYCode(iSp, iTp), & fY);

      //Verify test values are changed for some trees, not others

      //Tree 6
      if (fabs(fX - 27.794) < 0.001 && fabs(fY - 8.64942) < 0.001) {
        p_oTree->GetValue(p_oPop->GetFloatDataCode("test 1", iSp, iTp), &fVal);
        EXPECT_LT(fabs(fVal - 0.491), 0.0001);
        p_oTree->GetValue(p_oPop->GetFloatDataCode("test 2", iSp, iTp), &fVal);
        EXPECT_LT(fabs(fVal - 0.54), 0.0001);
        p_oTree->GetValue(p_oPop->GetFloatDataCode("test 3", iSp, iTp), &fVal);
        EXPECT_LT(fabs(fVal - 0.483), 0.0001);
      }

      //Tree 10
      else if (fabs(fX - 18.4304) < 0.001 && fabs(fY - 15.3092) < 0.001) {
        p_oTree->GetValue(p_oPop->GetFloatDataCode("test 1", iSp, iTp), &fVal);
        EXPECT_LT(fabs(fVal - 0.373), 0.0001);
        p_oTree->GetValue(p_oPop->GetFloatDataCode("test 2", iSp, iTp), &fVal);
        EXPECT_LT(fabs(fVal - 0.36), 0.0001);
        p_oTree->GetValue(p_oPop->GetFloatDataCode("test 3", iSp, iTp), &fVal);
        EXPECT_LT(fabs(fVal - 0.44), 0.0001);
      }

      //Tree 28
      else if (fabs(fX - 84.6036) < 0.001 && fabs(fY - 50.93) < 0.001) {
        p_oTree->GetValue(p_oPop->GetFloatDataCode("test 1", iSp, iTp), &fVal);
        EXPECT_LT(fabs(fVal - 23), 0.0001);
        p_oTree->GetValue(p_oPop->GetFloatDataCode("test 2", iSp, iTp), &fVal);
        EXPECT_LT(fabs(fVal - 23), 0.0001);
        p_oTree->GetValue(p_oPop->GetFloatDataCode("test 3", iSp, iTp), &fVal);
        EXPECT_LT(fabs(fVal - 23), 0.0001);
      }

      //Tree 34
      else if (fabs(fX - 9.38922) < 0.001 && fabs(fY - 59.3884) < 0.001) {
        p_oTree->GetValue(p_oPop->GetFloatDataCode("test 1", iSp, iTp), &fVal);
        EXPECT_LT(fabs(fVal - 1.239), 0.0001);
        p_oTree->GetValue(p_oPop->GetFloatDataCode("test 2", iSp, iTp), &fVal);
        EXPECT_LT(fabs(fVal - 0.033), 0.0001);
        p_oTree->GetValue(p_oPop->GetFloatDataCode("test 3", iSp, iTp), &fVal);
        EXPECT_LT(fabs(fVal - 2.447), 0.0001);
      }

      //Tree 35
      else if (fabs(fX - 27.1944) < 0.001 && fabs(fY - 63.1713) < 0.001) {
        p_oTree->GetValue(p_oPop->GetFloatDataCode("test 1", iSp, iTp), &fVal);
        EXPECT_LT(fabs(fVal - 46.485), 0.0001);
        p_oTree->GetValue(p_oPop->GetFloatDataCode("test 2", iSp, iTp), &fVal);
        EXPECT_LT(fabs(fVal - 16.391), 0.0001);
        p_oTree->GetValue(p_oPop->GetFloatDataCode("test 3", iSp, iTp), &fVal);
        EXPECT_LT(fabs(fVal - -0.369), 0.0001);
      }

      //Tree 36
      else if (fabs(fX - 61.7164) < 0.001 && fabs(fY - 66.0961) < 0.001) {
        p_oTree->GetValue(p_oPop->GetFloatDataCode("test 1", iSp, iTp), &fVal);
        EXPECT_LT(fabs(fVal - 0), 0.0001);
        p_oTree->GetValue(p_oPop->GetFloatDataCode("test 2", iSp, iTp), &fVal);
        EXPECT_LT(fabs(fVal - 0), 0.0001);
        p_oTree->GetValue(p_oPop->GetFloatDataCode("test 3", iSp, iTp), &fVal);
        EXPECT_LT(fabs(fVal - 0.657), 0.0001);
      }

      //Tree 40
      else if (fabs(fX - 6.33182) < 0.001 && fabs(fY - 75.0587) < 0.001) {
        p_oTree->GetValue(p_oPop->GetFloatDataCode("test 1", iSp, iTp), &fVal);
        EXPECT_LT(fabs(fVal - -0.23), 0.0001);
        p_oTree->GetValue(p_oPop->GetFloatDataCode("test 2", iSp, iTp), &fVal);
        EXPECT_LT(fabs(fVal - 0), 0.0001);
        p_oTree->GetValue(p_oPop->GetFloatDataCode("test 3", iSp, iTp), &fVal);
        EXPECT_LT(fabs(fVal - 15.66), 0.0001);
      }

      //Tree 47
      else if (fabs(fX - 38.6781) < 0.001 && fabs(fY - 84.8195) < 0.001) {
        p_oTree->GetValue(p_oPop->GetFloatDataCode("test 1", iSp, iTp), &fVal);
        EXPECT_LT(fabs(fVal - 10), 0.0001);
        p_oTree->GetValue(p_oPop->GetFloatDataCode("test 2", iSp, iTp), &fVal);
        EXPECT_LT(fabs(fVal - 0.0084), 0.0001);
        p_oTree->GetValue(p_oPop->GetFloatDataCode("test 3", iSp, iTp), &fVal);
        EXPECT_LT(fabs(fVal - -0.254), 0.0001);
      }

      //Tree 49
      else if (fabs(fX - 37.5938) < 0.001 && fabs(fY - 87.2484) < 0.001) {
        p_oTree->GetValue(p_oPop->GetFloatDataCode("test 1", iSp, iTp), &fVal);
        EXPECT_LT(fabs(fVal - 0), 0.0001);
        p_oTree->GetValue(p_oPop->GetFloatDataCode("test 2", iSp, iTp), &fVal);
        EXPECT_LT(fabs(fVal - 0.01), 0.0001);
        p_oTree->GetValue(p_oPop->GetFloatDataCode("test 3", iSp, iTp), &fVal);
        EXPECT_LT(fabs(fVal - 0.828), 0.0001);
      }

      //Tree 50
      else if (fabs(fX - 36.6376) < 0.001 && fabs(fY - 87.5301) < 0.001) {
        p_oTree->GetValue(p_oPop->GetFloatDataCode("test 1", iSp, iTp), &fVal);
        EXPECT_LT(fabs(fVal - 2.883), 0.0001);
        p_oTree->GetValue(p_oPop->GetFloatDataCode("test 2", iSp, iTp), &fVal);
        EXPECT_LT(fabs(fVal - 0), 0.0001);
        p_oTree->GetValue(p_oPop->GetFloatDataCode("test 3", iSp, iTp), &fVal);
        EXPECT_LT(fabs(fVal - -3.976), 0.0001);
      }

      //Tree 52
      else if (fabs(fX - 97.7476) < 0.001 && fabs(fY - 94.7417) < 0.001) {
        p_oTree->GetValue(p_oPop->GetFloatDataCode("test 1", iSp, iTp), &fVal);
        EXPECT_LT(fabs(fVal - 0.109), 0.0001);
        p_oTree->GetValue(p_oPop->GetFloatDataCode("test 2", iSp, iTp), &fVal);
        EXPECT_LT(fabs(fVal - 10), 0.0001);
        p_oTree->GetValue(p_oPop->GetFloatDataCode("test 3", iSp, iTp), &fVal);
        EXPECT_LT(fabs(fVal - 2.132), 0.0001);
      }

      else {
        p_oTree->GetValue(p_oPop->GetFloatDataCode("test 1", iSp, iTp), &fVal);
        EXPECT_LT(fabs(fVal), 0.0001);
        p_oTree->GetValue(p_oPop->GetFloatDataCode("test 2", iSp, iTp), &fVal);
        EXPECT_LT(fabs(fVal), 0.0001);
        p_oTree->GetValue(p_oPop->GetFloatDataCode("test 3", iSp, iTp), &fVal);
        EXPECT_LT(fabs(fVal), 0.0001);
      }

      //Verify that the "dead" and "Tree Age" values are un-messed-with
      p_oTree->GetValue(p_oPop->GetIntDataCode("Tree Age", iSp, iTp), &iVal);
      EXPECT_EQ(12, iVal);
      p_oTree->GetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), &iVal);
      EXPECT_EQ(notdead, iVal);

      for (i = 0; i < iNumTrees; i++) {
        if (iSp == p_iSpecies[i] &&
            iTp == p_iType[i] &&
            fabs(fDiam - p_fDiam[i]) < 0.0001 &&
            fabs(fX - p_fX[i]) < 0.0001 &&
            fabs(fY - p_fY[i]) < 0.0001 ) {

          p_bFound[i] = true;
          break;
        }
      }

      p_oTree = p_oAllTrees->NextTree();
    }

    //Verify that the right trees have been harvested
    for (i = 0; i < iNumTrees; i++) {
      if (0 == i ||
          1 == i ||
          2 == i ||
          8 == i ||
          14 == i ||
          18 == i ||
          19 == i ||
          27 == i) {
        EXPECT_FALSE(p_bFound[i]);
      } else {
        EXPECT_TRUE(p_bFound[i]);
      }
    }

    delete[] p_bFound;
    delete[] p_fX;
    delete[] p_fY;
    delete[] p_fDiam;
    delete[] p_iSpecies;
    delete[] p_iType;

    sprintf(cPath, "%s%s", TESTPATH2, "Test 3 SORTIE input.txt");
    DeleteThisFile(cPath);
    sprintf(cPath, "%s%s", TESTPATH2, "Cut File 3.txt");
    DeleteThisFile(cPath);
    sprintf(cPath, "%s%s", TESTPATH2, "Update File 3.txt");
    DeleteThisFile(cPath);

    delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

////////////////////////////////////////////////////////////////////////////
// TestNormalProcessingRun4()
// Tests normal processing, run 4. This tests applying the behavior to only
// a subset of trees. WriteHarvestInterfaceXMLFile4() does setup.
////////////////////////////////////////////////////////////////////////////
TEST(HarvestInterface, TestNormalProcessingRun4) {
  clTreePopulation * p_oPop;
  clTreeSearch *p_oAllTrees;
  clTree *p_oTree;
  char cPath[500];
  int **p_iCount, iNumSpecies, iNumTypes, i, j;

  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    //Load our test file and get our tree population pointers
    p_oSimManager->ReadFile( WriteHarvestInterfaceXMLFile4() );
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );
    iNumSpecies = p_oPop->GetNumberOfSpecies();
    iNumTypes = p_oPop->GetNumberOfTypes();
    p_iCount = new int*[iNumSpecies];
    for (i = 0; i < iNumSpecies; i++) {
      p_iCount[i] = new int[iNumTypes];
      for (j = 0; j < iNumTypes; j++) {
        p_iCount[i][j] = 0;
      }
    }

    //Count up all existing trees and make sure there are 80 of each species
    //for each of seedlings, saplings, and adults
    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {
      p_iCount[p_oTree->GetSpecies()][p_oTree->GetType()]++;
      p_oTree = p_oAllTrees->NextTree();
    }

    for (i = 0; i < iNumSpecies; i++)
      for (j = 0; j < iNumTypes; j++)
        if (clTreePopulation::seedling == j ||
            clTreePopulation::sapling == j ||
            clTreePopulation::adult == j)
          EXPECT_EQ(80, p_iCount[i][j]);
        else
          EXPECT_EQ(0, p_iCount[i][j]);

    //Run 1 timestep - no trees killed
    p_oSimManager->RunSim(1);
    for (i = 0; i < iNumSpecies; i++) {
      for (j = 0; j < iNumTypes; j++) {
        p_iCount[i][j] = 0;
      }
    }

    //Count up all existing trees and make sure there are 80 of each species
    //for each of seedlings, saplings, and adults
    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {
      p_iCount[p_oTree->GetSpecies()][p_oTree->GetType()]++;
      p_oTree = p_oAllTrees->NextTree();
    }

    for (i = 0; i < iNumSpecies; i++)
      for (j = 0; j < iNumTypes; j++)
        if (clTreePopulation::seedling == j ||
            clTreePopulation::sapling == j ||
            clTreePopulation::adult == j)
          EXPECT_EQ(80, p_iCount[i][j]);
        else
          EXPECT_EQ(0, p_iCount[i][j]);

    //Run 2 timestep - no trees killed
    p_oSimManager->RunSim(1);
    for (i = 0; i < iNumSpecies; i++) {
      for (j = 0; j < iNumTypes; j++) {
        p_iCount[i][j] = 0;
      }
    }

    //Count up all existing trees and make sure there are 80 of each species
    //for each of seedlings, saplings, and adults
    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {
      p_iCount[p_oTree->GetSpecies()][p_oTree->GetType()]++;
      p_oTree = p_oAllTrees->NextTree();
    }

    for (i = 0; i < iNumSpecies; i++)
      for (j = 0; j < iNumTypes; j++)
        if (clTreePopulation::seedling == j ||
            clTreePopulation::sapling == j ||
            clTreePopulation::adult == j)
          EXPECT_EQ(80, p_iCount[i][j]);
        else
          EXPECT_EQ(0, p_iCount[i][j]);

    //Run 3 timestep - all trees killed to which the behavior applies
    p_oSimManager->RunSim(1);
    for (i = 0; i < iNumSpecies; i++) {
      for (j = 0; j < iNumTypes; j++) {
        p_iCount[i][j] = 0;
      }
    }

    //Count up all existing trees and make sure there are 80 of each species
    //for each of seedlings, saplings, and adults
    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {
      p_iCount[p_oTree->GetSpecies()][p_oTree->GetType()]++;
      p_oTree = p_oAllTrees->NextTree();
    }

    for (i = 0; i < iNumSpecies; i++)
      for (j = 0; j < iNumTypes; j++)
        if ((clTreePopulation::seedling == j && i == 0) ||
            (clTreePopulation::sapling == j && 1 == i) ||
            (clTreePopulation::adult == j && 2 == i) ||
            clTreePopulation::seed == j ||
            clTreePopulation::snag == j ||
            clTreePopulation::woody_debris == j ||
            clTreePopulation::stump == j)
          EXPECT_EQ(0, p_iCount[i][j]);
        else
          EXPECT_EQ(80, p_iCount[i][j]);

    for (i = 0; i < iNumSpecies; i++)
      delete[] p_iCount[i];

    delete[] p_iCount;

    sprintf(cPath, "%s%s", TESTPATH, "test4harvest.txt");
    DeleteThisFile(cPath);
    sprintf(cPath, "%s%s", TESTPATH, "cutfile4.txt");
    DeleteThisFile(cPath);

    delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

////////////////////////////////////////////////////////////////////////////
// TestNormalProcessingRun5()
// Tests normal processing, run 5. This tests batch running. WriteHarvestInterfaceXMLBatch1()
// runs WriteHarvestInterfaceXMLFile5() for setup.
////////////////////////////////////////////////////////////////////////////
TEST(HarvestInterface, TestNormalProcessingRun5) {

  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    char cPath[500];

    //Prepare our files
    WriteHarvestInterfaceAllParamsFile();
    WriteHarvestInterfaceXMLFile5();

    //Run our batch
    p_oSimManager->RunBatch( WriteHarvestInterfaceXMLBatch1() );

    //Check for the existence of files written by our executable for each
    //run
    sprintf(cPath, "%s%s", TESTPATH, "batch1.txt");
    ASSERT_TRUE(DoesFileExist(cPath));
    sprintf(cPath, "%s%s", TESTPATH, "batch2.txt");
    ASSERT_TRUE(DoesFileExist(cPath));
    sprintf(cPath, "%s%s", TESTPATH, "batch3.txt");
    ASSERT_TRUE(DoesFileExist(cPath));

    sprintf(cPath, "%s%s", TESTPATH, "test5harvest.txt");
    DeleteThisFile(cPath);
    sprintf(cPath, "%s%s", TESTPATH, "cutfile5.txt");
    DeleteThisFile(cPath);
    sprintf(cPath, "%s%s", TESTPATH, "batch1.txt");
    DeleteThisFile(cPath);
    sprintf(cPath, "%s%s", TESTPATH, "batch2.txt");
    DeleteThisFile(cPath);
    sprintf(cPath, "%s%s", TESTPATH, "batch3.txt");
    DeleteThisFile(cPath);
    sprintf(cPath, "%s%s", TESTPATH, "allparams.txt");
    DeleteThisFile(cPath);
    sprintf(cPath, "%s%s", TESTPATH, "parameters5.txt");
    DeleteThisFile(cPath);
    sprintf(cPath, "%s%s", TESTPATH, "TestBatchFile1.xml");
    DeleteThisFile(cPath);

    delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

////////////////////////////////////////////////////////////////////////////
// TestNormalProcessingRun6()
// Tests normal processing, run 6. This tests batch running with no extra
// parameters file. WriteHarvestInterfaceXMLBatch1() runs WriteHarvestInterfaceXMLFile6() for setup.
////////////////////////////////////////////////////////////////////////////
TEST(HarvestInterface, TestNormalProcessingRun6) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    char cPath[500];

    //Prepare our files
    WriteHarvestInterfaceXMLFile6();

    //Run our batch
    p_oSimManager->RunBatch( WriteHarvestInterfaceXMLBatch1() );

    //Check for the existence of files written by our executable for each
    //run
    sprintf(cPath, "%s%s", TESTPATH, "batch1.txt");
    ASSERT_TRUE(!DoesFileExist(cPath));
    sprintf(cPath, "%s%s", TESTPATH, "batch2.txt");
    ASSERT_TRUE(!DoesFileExist(cPath));
    sprintf(cPath, "%s%s", TESTPATH, "batch3.txt");
    ASSERT_TRUE(!DoesFileExist(cPath));
    sprintf(cPath, "%s%s", TESTPATH, "batch.txt");
    ASSERT_TRUE(DoesFileExist(cPath));

    sprintf(cPath, "%s%s", TESTPATH, "test5harvest.txt");
    DeleteThisFile(cPath);
    sprintf(cPath, "%s%s", TESTPATH, "cutfile5.txt");
    DeleteThisFile(cPath);
    sprintf(cPath, "%s%s", TESTPATH, "batch.txt");
    DeleteThisFile(cPath);
    sprintf(cPath, "%s%s", TESTPATH, "TestBatchFile1.xml");
    DeleteThisFile(cPath);
    delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

////////////////////////////////////////////////////////////////////////////
// WriteHarvestInterfaceXMLFile1()
////////////////////////////////////////////////////////////////////////////
const char* WriteHarvestInterfaceXMLFile1() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
      << "<paramFile fileCode=\"06060101\">"
      << "<plot>"
      << "<timesteps>10</timesteps>"
      << "<rt_timestep>0</rt_timestep>"
      << "<randomSeed>0</randomSeed>"
      << "<yearsPerTimestep>5.0</yearsPerTimestep>"
      << "<plot_lenX>500.0</plot_lenX>"
      << "<plot_lenY>500.0</plot_lenY>"
      << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
      << "<plot_temp_C>12.88171785</plot_temp_C>"
      << "<plot_latitude>41.92</plot_latitude>"
      << "<plot_title>Default parameter file-use for testing only</plot_title>"
      << "</plot>";

  WriteHarvestInterfaceTrees(oOut);

  oOut << "<behaviorList>"
      << "<behavior>"
      << "<behaviorName>HarvestInterface</behaviorName>"
      << "<version>1.0</version>"
      << "<listPosition>1</listPosition>"
      << "<applyTo species=\"Species_3\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_3\" type=\"Seedling\"/>"
      << "<applyTo species=\"Species_1\" type=\"Seedling\"/>"
      << "<applyTo species=\"Species_2\" type=\"Seedling\"/>"
      << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>NonSpatialDisperse</behaviorName>"
      << "<version>1.0</version>"
      << "<listPosition>2</listPosition>"
      << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
      << "</behavior>"
      << "</behaviorList>";

  WriteHarvestInterfaceAllometry(oOut);

  oOut << "<HarvestInterface1>"
      << "<hi_executable>" << TESTPATH << "trees1.exe</hi_executable>"
      << "<hi_harvestableTreesFile>" << TESTPATH << "test1harvest.txt</hi_harvestableTreesFile>"
      << "<hi_treesToHarvestFile>" << TESTPATH << "cutfile.txt</hi_treesToHarvestFile>"
      << "<hi_harvestPeriod>1</hi_harvestPeriod>"
      << "</HarvestInterface1>";

  oOut << "<GeneralDisperse>"
      << "<di_seedDistributionMethod>0</di_seedDistributionMethod>"
      << "</GeneralDisperse>"
      << "<NonSpatialDisperse2>"
      << "<di_minDbhForReproduction>"
      << "<di_mdfrVal species=\"Species_3\">0.0</di_mdfrVal>"
      << "<di_mdfrVal species=\"Species_1\">0.0</di_mdfrVal>"
      << "<di_mdfrVal species=\"Species_2\">0.0</di_mdfrVal>"
      << "</di_minDbhForReproduction>"
      << "<di_nonSpatialSlopeOfLambda>"
      << "<di_nssolVal species=\"Species_3\">0.0</di_nssolVal>"
      << "<di_nssolVal species=\"Species_1\">0.0</di_nssolVal>"
      << "<di_nssolVal species=\"Species_2\">0.0</di_nssolVal>"
      << "</di_nonSpatialSlopeOfLambda>"
      << "<di_nonSpatialInterceptOfLambda>"
      << "<di_nsiolVal species=\"Species_3\">0</di_nsiolVal>"
      << "<di_nsiolVal species=\"Species_1\">0</di_nsiolVal>"
      << "<di_nsiolVal species=\"Species_2\">0</di_nsiolVal>"
      << "</di_nonSpatialInterceptOfLambda>"
      << "</NonSpatialDisperse2>"
      << "</paramFile>";

  oOut.close();
  return cFileString;
}


////////////////////////////////////////////////////////////////////////////
// WriteHarvestInterfaceXMLFile2()
////////////////////////////////////////////////////////////////////////////
const char* WriteHarvestInterfaceXMLFile2() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
      << "<paramFile fileCode=\"06060101\">"
      << "<plot>"
      << "<timesteps>10</timesteps>"
      << "<rt_timestep>0</rt_timestep>"
      << "<randomSeed>0</randomSeed>"
      << "<yearsPerTimestep>1.0</yearsPerTimestep>"
      << "<plot_lenX>500.0</plot_lenX>"
      << "<plot_lenY>500.0</plot_lenY>"
      << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
      << "<plot_temp_C>12.88171785</plot_temp_C>"
      << "<plot_latitude>41.92</plot_latitude>"
      << "<plot_title>Default parameter file-use for testing only</plot_title>"
      << "</plot>";

  WriteHarvestInterfaceTrees(oOut);

  oOut << "<behaviorList>"
      << "<behavior>"
      << "<behaviorName>HarvestInterface</behaviorName>"
      << "<version>1.0</version>"
      << "<listPosition>1</listPosition>"
      << "<applyTo species=\"Species_3\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_3\" type=\"Seedling\"/>"
      << "<applyTo species=\"Species_1\" type=\"Seedling\"/>"
      << "<applyTo species=\"Species_2\" type=\"Seedling\"/>"
      << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>ConstantGLI</behaviorName>"
      << "<version>1.0</version>"
      << "<listPosition>2</listPosition>"
      << "<applyTo species=\"Species_3\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_3\" type=\"Seedling\"/>"
      << "<applyTo species=\"Species_1\" type=\"Seedling\"/>"
      << "<applyTo species=\"Species_2\" type=\"Seedling\"/>"
      << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>ConstRadialGrowth</behaviorName>"
      << "<version>1.0</version>"
      << "<applyTo species=\"Species_3\" type=\"Sapling\"/>"
      << "<listPosition>3</listPosition>"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>SimpleLinearGrowth</behaviorName>"
      << "<version>1.0</version>"
      << "<listPosition>4</listPosition>"
      << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_3\" type=\"Seedling\"/>"
      << "<applyTo species=\"Species_1\" type=\"Seedling\"/>"
      << "<applyTo species=\"Species_2\" type=\"Seedling\"/>"
      << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>NonSpatialDisperse</behaviorName>"
      << "<version>1.0</version>"
      << "<listPosition>5</listPosition>"
      << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
      << "</behavior>"
      << "</behaviorList>";

  WriteHarvestInterfaceAllometry(oOut);

  oOut << "<HarvestInterface1>"
      << "<hi_executable>" << TESTPATH << "trees2.exe</hi_executable>"
      << "<hi_harvestableTreesFile>" << TESTPATH << "Test 2 Harvest.txt</hi_harvestableTreesFile>"
      << "<hi_treesToHarvestFile>" << TESTPATH << "Cut File 2.txt</hi_treesToHarvestFile>"
      << "<hi_executableArguments>Some arguments!</hi_executableArguments>"
      << "<hi_harvestPeriod>1</hi_harvestPeriod>"
      << "<hi_dataMembers>"
      << "<hi_dataMember>Growth</hi_dataMember>"
      << "<hi_dataMember>Light</hi_dataMember>"
      << "</hi_dataMembers>"
      << "</HarvestInterface1>";

  oOut << "<ConstantGLI2>"
      << "<li_constGLI>100.0</li_constGLI>"
      << "</ConstantGLI2>"
      << "<ConstRadialGrowth3>"
      << "<gr_adultConstRadialInc>"
      << "<gr_acriVal species=\"Species_3\">6.0</gr_acriVal>"
      << "</gr_adultConstRadialInc>"
      << "</ConstRadialGrowth3>"
      << "<SimpleLinearGrowth4>"
      << "<gr_diamSimpleLinearIntercept>"
      << "<gr_dsliVal species=\"Species_3\">0.0</gr_dsliVal>"
      << "<gr_dsliVal species=\"Species_1\">0.0</gr_dsliVal>"
      << "<gr_dsliVal species=\"Species_2\">0.0</gr_dsliVal>"
      << "</gr_diamSimpleLinearIntercept>"
      << "<gr_diamSimpleLinearSlope>"
      << "<gr_dslsVal species=\"Species_3\">0.0</gr_dslsVal>"
      << "<gr_dslsVal species=\"Species_1\">0.0</gr_dslsVal>"
      << "<gr_dslsVal species=\"Species_2\">0.0</gr_dslsVal>"
      << "</gr_diamSimpleLinearSlope>"
      << "</SimpleLinearGrowth4>"
      << "<GeneralDisperse>"
      << "<di_seedDistributionMethod>0</di_seedDistributionMethod>"
      << "</GeneralDisperse>"
      << "<NonSpatialDisperse5>"
      << "<di_minDbhForReproduction>"
      << "<di_mdfrVal species=\"Species_3\">0.0</di_mdfrVal>"
      << "<di_mdfrVal species=\"Species_1\">0.0</di_mdfrVal>"
      << "<di_mdfrVal species=\"Species_2\">0.0</di_mdfrVal>"
      << "</di_minDbhForReproduction>"
      << "<di_nonSpatialSlopeOfLambda>"
      << "<di_nssolVal species=\"Species_3\">0.0</di_nssolVal>"
      << "<di_nssolVal species=\"Species_1\">0.0</di_nssolVal>"
      << "<di_nssolVal species=\"Species_2\">0.0</di_nssolVal>"
      << "</di_nonSpatialSlopeOfLambda>"
      << "<di_nonSpatialInterceptOfLambda>"
      << "<di_nsiolVal species=\"Species_3\">0</di_nsiolVal>"
      << "<di_nsiolVal species=\"Species_1\">0</di_nsiolVal>"
      << "<di_nsiolVal species=\"Species_2\">0</di_nsiolVal>"
      << "</di_nonSpatialInterceptOfLambda>"
      << "</NonSpatialDisperse5>"
      << "</paramFile>";

  oOut.close();
  return cFileString;
}


////////////////////////////////////////////////////////////////////////////
// WriteHarvestInterfaceXMLFile3()
////////////////////////////////////////////////////////////////////////////
const char* WriteHarvestInterfaceXMLFile3() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
      << "<paramFile fileCode=\"06060101\">"
      << "<plot>"
      << "<timesteps>10</timesteps>"
      << "<rt_timestep>0</rt_timestep>"
      << "<randomSeed>0</randomSeed>"
      << "<yearsPerTimestep>2.0</yearsPerTimestep>"
      << "<plot_lenX>500.0</plot_lenX>"
      << "<plot_lenY>500.0</plot_lenY>"
      << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
      << "<plot_temp_C>12.88171785</plot_temp_C>"
      << "<plot_latitude>41.92</plot_latitude>"
      << "<plot_title>Default parameter file-use for testing only</plot_title>"
      << "</plot>";

  WriteHarvestInterfaceTrees(oOut);

  oOut << "<behaviorList>"
      << "<behavior>"
      << "<behaviorName>HarvestInterface (test 1) (test 2) (test 3)</behaviorName>"
      << "<version>1.0</version>"
      << "<listPosition>1</listPosition>"
      << "<applyTo species=\"Species_3\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_3\" type=\"Seedling\"/>"
      << "<applyTo species=\"Species_1\" type=\"Seedling\"/>"
      << "<applyTo species=\"Species_2\" type=\"Seedling\"/>"
      << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>StochasticMortality</behaviorName>"
      << "<version>1.0</version>"
      << "<listPosition>2</listPosition>"
      << "<applyTo species=\"Species_3\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_3\" type=\"Seedling\"/>"
      << "<applyTo species=\"Species_1\" type=\"Seedling\"/>"
      << "<applyTo species=\"Species_2\" type=\"Seedling\"/>"
      << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>TreeAgeCalculator</behaviorName>"
      << "<version>1.0</version>"
      << "<listPosition>3</listPosition>"
      << "<applyTo species=\"Species_3\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_3\" type=\"Seedling\"/>"
      << "<applyTo species=\"Species_1\" type=\"Seedling\"/>"
      << "<applyTo species=\"Species_2\" type=\"Seedling\"/>"
      << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
      << "</behavior>"
      << "</behaviorList>";

  WriteHarvestInterfaceAllometry(oOut);

  oOut << "<HarvestInterface1>"
      << "<hi_executable>" << TESTPATH << "trees3.exe</hi_executable>"
      << "<hi_harvestableTreesFile>" << TESTPATH2 << "Test 3 SORTIE input.txt</hi_harvestableTreesFile>"
      << "<hi_treesToHarvestFile>" << TESTPATH2 << "Cut File 3.txt</hi_treesToHarvestFile>"
      << "<hi_treesToUpdateFile>" << TESTPATH2 << "Update File 3.txt</hi_treesToUpdateFile>"
      << "<hi_harvestPeriod>4</hi_harvestPeriod>"
      << "<hi_dataMembers>"
      << "<hi_dataMember>test 2</hi_dataMember>"
      << "<hi_dataMember>Tree Age</hi_dataMember>"
      << "<hi_dataMember>test 1</hi_dataMember>"
      << "<hi_dataMember>dead</hi_dataMember>"
      << "<hi_dataMember>test 3</hi_dataMember>"
      << "</hi_dataMembers>"
      << "</HarvestInterface1>";

  oOut << "<StochasticMortality2>"
      << "<mo_stochasticMortRate>"
      << "<mo_smrVal species=\"Species_1\">0.0</mo_smrVal>"
      << "<mo_smrVal species=\"Species_2\">0.0</mo_smrVal>"
      << "<mo_smrVal species=\"Species_3\">0.0</mo_smrVal>"
      << "</mo_stochasticMortRate>"
      << "</StochasticMortality2>"
      << "</paramFile>";

  oOut.close();
  return cFileString;
}


////////////////////////////////////////////////////////////////////////////
// WriteHarvestInterfaceXMLFile4()
////////////////////////////////////////////////////////////////////////////
const char* WriteHarvestInterfaceXMLFile4() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
      << "<paramFile fileCode=\"06060101\">"
      << "<plot>"
      << "<timesteps>3</timesteps>"
      << "<rt_timestep>0</rt_timestep>"
      << "<randomSeed>0</randomSeed>"
      << "<yearsPerTimestep>2.0</yearsPerTimestep>"
      << "<plot_lenX>200.0</plot_lenX>"
      << "<plot_lenY>200.0</plot_lenY>"
      << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
      << "<plot_temp_C>12.88171785</plot_temp_C>"
      << "<plot_latitude>41.92</plot_latitude>"
      << "<plot_title>Default parameter file-use for testing only</plot_title>"
      << "</plot>"
      << "<trees>"
      << "<tr_speciesList>"
      << "<tr_species speciesName=\"Species_1\"/>"
      << "<tr_species speciesName=\"Species_2\"/>"
      << "<tr_species speciesName=\"Species_3\"/>"
      << "</tr_speciesList>"
      << "<tr_sizeClasses>"
      << "<tr_sizeClass sizeKey=\"Seedling\"/>"
      << "<tr_sizeClass sizeKey=\"s2.5\"/>"
      << "<tr_sizeClass sizeKey=\"s5.0\"/>"
      << "<tr_sizeClass sizeKey=\"s20.0\"/>"
      << "<tr_sizeClass sizeKey=\"s30.0\"/>"
      << "</tr_sizeClasses>"
      << "<tr_initialDensities>"
      << "<tr_idVals whatSpecies=\"Species_1\">"
      << "<tr_initialDensity sizeClass=\"Seedling\">20.0</tr_initialDensity>"
      << "<tr_initialDensity sizeClass=\"s5.0\">20.0</tr_initialDensity>"
      << "<tr_initialDensity sizeClass=\"s30.0\">20.0</tr_initialDensity>"
      << "</tr_idVals>"
      << "<tr_idVals whatSpecies=\"Species_2\">"
      << "<tr_initialDensity sizeClass=\"Seedling\">20.0</tr_initialDensity>"
      << "<tr_initialDensity sizeClass=\"s5.0\">20.0</tr_initialDensity>"
      << "<tr_initialDensity sizeClass=\"s30.0\">20.0</tr_initialDensity>"
      << "</tr_idVals>"
      << "<tr_idVals whatSpecies=\"Species_3\">"
      << "<tr_initialDensity sizeClass=\"Seedling\">20.0</tr_initialDensity>"
      << "<tr_initialDensity sizeClass=\"s5.0\">20.0</tr_initialDensity>"
      << "<tr_initialDensity sizeClass=\"s30.0\">20.0</tr_initialDensity>"
      << "</tr_idVals>"
      << "</tr_initialDensities>"
      << "<tr_seedDiam10Cm>0.2</tr_seedDiam10Cm>"
      << "<tr_minAdultDBH>"
      << "<tr_madVal species=\"Species_3\">10.0</tr_madVal>"
      << "<tr_madVal species=\"Species_1\">10.0</tr_madVal>"
      << "<tr_madVal species=\"Species_2\">10.0</tr_madVal>"
      << "</tr_minAdultDBH>"
      << "<tr_maxSeedlingHeight>"
      << "<tr_mshVal species=\"Species_3\">1.35</tr_mshVal>"
      << "<tr_mshVal species=\"Species_1\">1.35</tr_mshVal>"
      << "<tr_mshVal species=\"Species_2\">1.35</tr_mshVal>"
      << "</tr_maxSeedlingHeight>"
      << "</trees>"
      << "<behaviorList>"
      << "<behavior>"
      << "<behaviorName>HarvestInterface</behaviorName>"
      << "<version>1.0</version>"
      << "<listPosition>1</listPosition>"
      << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_1\" type=\"Seedling\"/>"
      << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>NonSpatialDisperse</behaviorName>"
      << "<version>1.0</version>"
      << "<listPosition>2</listPosition>"
      << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
      << "</behavior>"
      << "</behaviorList>";

  WriteHarvestInterfaceAllometry(oOut);

  oOut << "<HarvestInterface1>"
      << "<hi_executable>" << TESTPATH << "trees4.exe</hi_executable>"
      << "<hi_harvestableTreesFile>" << TESTPATH << "test4harvest.txt</hi_harvestableTreesFile>"
      << "<hi_treesToHarvestFile>" << TESTPATH << "cutfile4.txt</hi_treesToHarvestFile>"
      << "<hi_harvestPeriod>6</hi_harvestPeriod>"
      << "</HarvestInterface1>";

  oOut << "<GeneralDisperse>"
      << "<di_seedDistributionMethod>0</di_seedDistributionMethod>"
      << "</GeneralDisperse>"
      << "<NonSpatialDisperse2>"
      << "<di_minDbhForReproduction>"
      << "<di_mdfrVal species=\"Species_3\">0.0</di_mdfrVal>"
      << "<di_mdfrVal species=\"Species_1\">0.0</di_mdfrVal>"
      << "<di_mdfrVal species=\"Species_2\">0.0</di_mdfrVal>"
      << "</di_minDbhForReproduction>"
      << "<di_nonSpatialSlopeOfLambda>"
      << "<di_nssolVal species=\"Species_3\">0.0</di_nssolVal>"
      << "<di_nssolVal species=\"Species_1\">0.0</di_nssolVal>"
      << "<di_nssolVal species=\"Species_2\">0.0</di_nssolVal>"
      << "</di_nonSpatialSlopeOfLambda>"
      << "<di_nonSpatialInterceptOfLambda>"
      << "<di_nsiolVal species=\"Species_3\">0</di_nsiolVal>"
      << "<di_nsiolVal species=\"Species_1\">0</di_nsiolVal>"
      << "<di_nsiolVal species=\"Species_2\">0</di_nsiolVal>"
      << "</di_nonSpatialInterceptOfLambda>"
      << "</NonSpatialDisperse2>"
      << "</paramFile>";

  oOut.close();
  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteHarvestInterfaceXMLFile5()
////////////////////////////////////////////////////////////////////////////
const char* WriteHarvestInterfaceXMLFile5() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
      << "<paramFile fileCode=\"06060101\">"
      << "<plot>"
      << "<timesteps>3</timesteps>"
      << "<rt_timestep>0</rt_timestep>"
      << "<randomSeed>0</randomSeed>"
      << "<yearsPerTimestep>1.0</yearsPerTimestep>"
      << "<plot_lenX>200.0</plot_lenX>"
      << "<plot_lenY>200.0</plot_lenY>"
      << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
      << "<plot_temp_C>12.88171785</plot_temp_C>"
      << "<plot_latitude>41.92</plot_latitude>"
      << "<plot_title>Default parameter file-use for testing only</plot_title>"
      << "</plot>"
      << "<trees>"
      << "<tr_speciesList>"
      << "<tr_species speciesName=\"Species_1\"/>"
      << "<tr_species speciesName=\"Species_2\"/>"
      << "<tr_species speciesName=\"Species_3\"/>"
      << "</tr_speciesList>"
      << "<tr_sizeClasses>"
      << "<tr_sizeClass sizeKey=\"Seedling\"/>"
      << "<tr_sizeClass sizeKey=\"s2.5\"/>"
      << "<tr_sizeClass sizeKey=\"s5.0\"/>"
      << "<tr_sizeClass sizeKey=\"s20.0\"/>"
      << "<tr_sizeClass sizeKey=\"s30.0\"/>"
      << "</tr_sizeClasses>"
      << "<tr_initialDensities>"
      << "<tr_idVals whatSpecies=\"Species_1\">"
      << "<tr_initialDensity sizeClass=\"Seedling\">20.0</tr_initialDensity>"
      << "<tr_initialDensity sizeClass=\"s5.0\">20.0</tr_initialDensity>"
      << "<tr_initialDensity sizeClass=\"s30.0\">20.0</tr_initialDensity>"
      << "</tr_idVals>"
      << "<tr_idVals whatSpecies=\"Species_2\">"
      << "<tr_initialDensity sizeClass=\"Seedling\">20.0</tr_initialDensity>"
      << "<tr_initialDensity sizeClass=\"s5.0\">20.0</tr_initialDensity>"
      << "<tr_initialDensity sizeClass=\"s30.0\">20.0</tr_initialDensity>"
      << "</tr_idVals>"
      << "<tr_idVals whatSpecies=\"Species_3\">"
      << "<tr_initialDensity sizeClass=\"Seedling\">20.0</tr_initialDensity>"
      << "<tr_initialDensity sizeClass=\"s5.0\">20.0</tr_initialDensity>"
      << "<tr_initialDensity sizeClass=\"s30.0\">20.0</tr_initialDensity>"
      << "</tr_idVals>"
      << "</tr_initialDensities>"
      << "<tr_seedDiam10Cm>0.2</tr_seedDiam10Cm>"
      << "<tr_minAdultDBH>"
      << "<tr_madVal species=\"Species_3\">10.0</tr_madVal>"
      << "<tr_madVal species=\"Species_1\">10.0</tr_madVal>"
      << "<tr_madVal species=\"Species_2\">10.0</tr_madVal>"
      << "</tr_minAdultDBH>"
      << "<tr_maxSeedlingHeight>"
      << "<tr_mshVal species=\"Species_3\">1.35</tr_mshVal>"
      << "<tr_mshVal species=\"Species_1\">1.35</tr_mshVal>"
      << "<tr_mshVal species=\"Species_2\">1.35</tr_mshVal>"
      << "</tr_maxSeedlingHeight>"
      << "</trees>"
      << "<behaviorList>"
      << "<behavior>"
      << "<behaviorName>HarvestInterface</behaviorName>"
      << "<version>1.0</version>"
      << "<listPosition>1</listPosition>"
      << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_1\" type=\"Seedling\"/>"
      << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>NonSpatialDisperse</behaviorName>"
      << "<version>1.0</version>"
      << "<listPosition>2</listPosition>"
      << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
      << "</behavior>"
      << "</behaviorList>";

  WriteHarvestInterfaceAllometry(oOut);

  oOut << "<HarvestInterface1>"
      << "<hi_executable>" << TESTPATH << "trees5.exe</hi_executable>"
      << "<hi_harvestableTreesFile>" << TESTPATH << "test5harvest.txt</hi_harvestableTreesFile>"
      << "<hi_treesToHarvestFile>" << TESTPATH << "cutfile5.txt</hi_treesToHarvestFile>"
      << "<hi_batchParamsFile>" << TESTPATH << "allparams.txt</hi_batchParamsFile>"
      << "<hi_batchSingleRunParamsFile>" << TESTPATH << "parameters5.txt</hi_batchSingleRunParamsFile>"
      << "<hi_executableArguments>yes</hi_executableArguments>"
      << "<hi_harvestPeriod>1</hi_harvestPeriod>"
      << "</HarvestInterface1>";

  oOut << "<GeneralDisperse>"
      << "<di_seedDistributionMethod>0</di_seedDistributionMethod>"
      << "</GeneralDisperse>"
      << "<NonSpatialDisperse2>"
      << "<di_minDbhForReproduction>"
      << "<di_mdfrVal species=\"Species_3\">0.0</di_mdfrVal>"
      << "<di_mdfrVal species=\"Species_1\">0.0</di_mdfrVal>"
      << "<di_mdfrVal species=\"Species_2\">0.0</di_mdfrVal>"
      << "</di_minDbhForReproduction>"
      << "<di_nonSpatialSlopeOfLambda>"
      << "<di_nssolVal species=\"Species_3\">0.0</di_nssolVal>"
      << "<di_nssolVal species=\"Species_1\">0.0</di_nssolVal>"
      << "<di_nssolVal species=\"Species_2\">0.0</di_nssolVal>"
      << "</di_nonSpatialSlopeOfLambda>"
      << "<di_nonSpatialInterceptOfLambda>"
      << "<di_nsiolVal species=\"Species_3\">0</di_nsiolVal>"
      << "<di_nsiolVal species=\"Species_1\">0</di_nsiolVal>"
      << "<di_nsiolVal species=\"Species_2\">0</di_nsiolVal>"
      << "</di_nonSpatialInterceptOfLambda>"
      << "</NonSpatialDisperse2>"
      << "</paramFile>";

  oOut.close();
  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteHarvestInterfaceXMLFile6()
////////////////////////////////////////////////////////////////////////////
const char* WriteHarvestInterfaceXMLFile6() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
      << "<paramFile fileCode=\"06060101\">"
      << "<plot>"
      << "<timesteps>3</timesteps>"
      << "<rt_timestep>0</rt_timestep>"
      << "<randomSeed>0</randomSeed>"
      << "<yearsPerTimestep>1.0</yearsPerTimestep>"
      << "<plot_lenX>200.0</plot_lenX>"
      << "<plot_lenY>200.0</plot_lenY>"
      << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
      << "<plot_temp_C>12.88171785</plot_temp_C>"
      << "<plot_latitude>41.92</plot_latitude>"
      << "<plot_title>Default parameter file-use for testing only</plot_title>"
      << "</plot>"
      << "<trees>"
      << "<tr_speciesList>"
      << "<tr_species speciesName=\"Species_1\"/>"
      << "<tr_species speciesName=\"Species_2\"/>"
      << "<tr_species speciesName=\"Species_3\"/>"
      << "</tr_speciesList>"
      << "<tr_sizeClasses>"
      << "<tr_sizeClass sizeKey=\"Seedling\"/>"
      << "<tr_sizeClass sizeKey=\"s2.5\"/>"
      << "<tr_sizeClass sizeKey=\"s5.0\"/>"
      << "<tr_sizeClass sizeKey=\"s20.0\"/>"
      << "<tr_sizeClass sizeKey=\"s30.0\"/>"
      << "</tr_sizeClasses>"
      << "<tr_initialDensities>"
      << "<tr_idVals whatSpecies=\"Species_1\">"
      << "<tr_initialDensity sizeClass=\"Seedling\">20.0</tr_initialDensity>"
      << "<tr_initialDensity sizeClass=\"s5.0\">20.0</tr_initialDensity>"
      << "<tr_initialDensity sizeClass=\"s30.0\">20.0</tr_initialDensity>"
      << "</tr_idVals>"
      << "<tr_idVals whatSpecies=\"Species_2\">"
      << "<tr_initialDensity sizeClass=\"Seedling\">20.0</tr_initialDensity>"
      << "<tr_initialDensity sizeClass=\"s5.0\">20.0</tr_initialDensity>"
      << "<tr_initialDensity sizeClass=\"s30.0\">20.0</tr_initialDensity>"
      << "</tr_idVals>"
      << "<tr_idVals whatSpecies=\"Species_3\">"
      << "<tr_initialDensity sizeClass=\"Seedling\">20.0</tr_initialDensity>"
      << "<tr_initialDensity sizeClass=\"s5.0\">20.0</tr_initialDensity>"
      << "<tr_initialDensity sizeClass=\"s30.0\">20.0</tr_initialDensity>"
      << "</tr_idVals>"
      << "</tr_initialDensities>"
      << "<tr_seedDiam10Cm>0.2</tr_seedDiam10Cm>"
      << "<tr_minAdultDBH>"
      << "<tr_madVal species=\"Species_3\">10.0</tr_madVal>"
      << "<tr_madVal species=\"Species_1\">10.0</tr_madVal>"
      << "<tr_madVal species=\"Species_2\">10.0</tr_madVal>"
      << "</tr_minAdultDBH>"
      << "<tr_maxSeedlingHeight>"
      << "<tr_mshVal species=\"Species_3\">1.35</tr_mshVal>"
      << "<tr_mshVal species=\"Species_1\">1.35</tr_mshVal>"
      << "<tr_mshVal species=\"Species_2\">1.35</tr_mshVal>"
      << "</tr_maxSeedlingHeight>"
      << "</trees>"
      << "<behaviorList>"
      << "<behavior>"
      << "<behaviorName>HarvestInterface</behaviorName>"
      << "<version>1.0</version>"
      << "<listPosition>1</listPosition>"
      << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_1\" type=\"Seedling\"/>"
      << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>NonSpatialDisperse</behaviorName>"
      << "<version>1.0</version>"
      << "<listPosition>2</listPosition>"
      << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
      << "</behavior>"
      << "</behaviorList>";

  WriteHarvestInterfaceAllometry(oOut);

  oOut << "<HarvestInterface1>"
      << "<hi_executable>" << TESTPATH << "trees5.exe</hi_executable>"
      << "<hi_harvestableTreesFile>" << TESTPATH << "test5harvest.txt</hi_harvestableTreesFile>"
      << "<hi_treesToHarvestFile>" << TESTPATH << "cutfile5.txt</hi_treesToHarvestFile>"
      << "<hi_executableArguments>no</hi_executableArguments>"
      << "<hi_batchParamsFile></hi_batchParamsFile>"
      << "<hi_batchSingleRunParamsFile></hi_batchSingleRunParamsFile>"
      << "<hi_harvestPeriod>1</hi_harvestPeriod>"
      << "</HarvestInterface1>";

  oOut << "<GeneralDisperse>"
      << "<di_seedDistributionMethod>0</di_seedDistributionMethod>"
      << "</GeneralDisperse>"
      << "<NonSpatialDisperse2>"
      << "<di_minDbhForReproduction>"
      << "<di_mdfrVal species=\"Species_3\">0.0</di_mdfrVal>"
      << "<di_mdfrVal species=\"Species_1\">0.0</di_mdfrVal>"
      << "<di_mdfrVal species=\"Species_2\">0.0</di_mdfrVal>"
      << "</di_minDbhForReproduction>"
      << "<di_nonSpatialSlopeOfLambda>"
      << "<di_nssolVal species=\"Species_3\">0.0</di_nssolVal>"
      << "<di_nssolVal species=\"Species_1\">0.0</di_nssolVal>"
      << "<di_nssolVal species=\"Species_2\">0.0</di_nssolVal>"
      << "</di_nonSpatialSlopeOfLambda>"
      << "<di_nonSpatialInterceptOfLambda>"
      << "<di_nsiolVal species=\"Species_3\">0</di_nsiolVal>"
      << "<di_nsiolVal species=\"Species_1\">0</di_nsiolVal>"
      << "<di_nsiolVal species=\"Species_2\">0</di_nsiolVal>"
      << "</di_nonSpatialInterceptOfLambda>"
      << "</NonSpatialDisperse2>"
      << "</paramFile>";

  oOut.close();
  return cFileString;
}


////////////////////////////////////////////////////////////////////////////
// WriteHarvestInterfaceXMLErrorFile1()
////////////////////////////////////////////////////////////////////////////
const char* WriteHarvestInterfaceXMLErrorFile1() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
      << "<paramFile fileCode=\"06060101\">"
      << "<plot>"
      << "<timesteps>10</timesteps>"
      << "<rt_timestep>0</rt_timestep>"
      << "<randomSeed>0</randomSeed>"
      << "<yearsPerTimestep>5.0</yearsPerTimestep>"
      << "<plot_lenX>500.0</plot_lenX>"
      << "<plot_lenY>500.0</plot_lenY>"
      << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
      << "<plot_temp_C>12.88171785</plot_temp_C>"
      << "<plot_latitude>41.92</plot_latitude>"
      << "<plot_title>Default parameter file-use for testing only</plot_title>"
      << "</plot>";

  WriteHarvestInterfaceTrees(oOut);

  oOut << "<behaviorList>"
      << "<behavior>"
      << "<behaviorName>HarvestInterface</behaviorName>"
      << "<version>1.0</version>"
      << "<listPosition>1</listPosition>"
      << "<applyTo species=\"Species_3\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_3\" type=\"Seedling\"/>"
      << "<applyTo species=\"Species_1\" type=\"Seedling\"/>"
      << "<applyTo species=\"Species_2\" type=\"Seedling\"/>"
      << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>NonSpatialDisperse</behaviorName>"
      << "<version>1.0</version>"
      << "<listPosition>2</listPosition>"
      << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
      << "</behavior>"
      << "</behaviorList>";

  WriteHarvestInterfaceAllometry(oOut);

  oOut << "<HarvestInterface1>"
      << "<hi_executable>" << TESTPATH3 << "trees1.exe</hi_executable>"
      << "<hi_harvestableTreesFile>" << TESTPATH << "test1harvest.txt</hi_harvestableTreesFile>"
      << "<hi_treesToHarvestFile>" << TESTPATH << "cutfile.txt</hi_treesToHarvestFile>"
      << "<hi_harvestPeriod>1</hi_harvestPeriod>"
      << "</HarvestInterface1>";

  oOut << "<GeneralDisperse>"
      << "<di_seedDistributionMethod>0</di_seedDistributionMethod>"
      << "</GeneralDisperse>"
      << "<NonSpatialDisperse2>"
      << "<di_minDbhForReproduction>"
      << "<di_mdfrVal species=\"Species_3\">0.0</di_mdfrVal>"
      << "<di_mdfrVal species=\"Species_1\">0.0</di_mdfrVal>"
      << "<di_mdfrVal species=\"Species_2\">0.0</di_mdfrVal>"
      << "</di_minDbhForReproduction>"
      << "<di_nonSpatialSlopeOfLambda>"
      << "<di_nssolVal species=\"Species_3\">0.0</di_nssolVal>"
      << "<di_nssolVal species=\"Species_1\">0.0</di_nssolVal>"
      << "<di_nssolVal species=\"Species_2\">0.0</di_nssolVal>"
      << "</di_nonSpatialSlopeOfLambda>"
      << "<di_nonSpatialInterceptOfLambda>"
      << "<di_nsiolVal species=\"Species_3\">0</di_nsiolVal>"
      << "<di_nsiolVal species=\"Species_1\">0</di_nsiolVal>"
      << "<di_nsiolVal species=\"Species_2\">0</di_nsiolVal>"
      << "</di_nonSpatialInterceptOfLambda>"
      << "</NonSpatialDisperse2>"
      << "</paramFile>";

  oOut.close();
  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteHarvestInterfaceXMLErrorFile2()
////////////////////////////////////////////////////////////////////////////
const char* WriteHarvestInterfaceXMLErrorFile2() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
      << "<paramFile fileCode=\"06060101\">"
      << "<plot>"
      << "<timesteps>10</timesteps>"
      << "<rt_timestep>0</rt_timestep>"
      << "<randomSeed>0</randomSeed>"
      << "<yearsPerTimestep>5.0</yearsPerTimestep>"
      << "<plot_lenX>500.0</plot_lenX>"
      << "<plot_lenY>500.0</plot_lenY>"
      << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
      << "<plot_temp_C>12.88171785</plot_temp_C>"
      << "<plot_latitude>41.92</plot_latitude>"
      << "<plot_title>Default parameter file-use for testing only</plot_title>"
      << "</plot>";

  WriteHarvestInterfaceTrees(oOut);

  oOut << "<behaviorList>"
      << "<behavior>"
      << "<behaviorName>HarvestInterface</behaviorName>"
      << "<version>1.0</version>"
      << "<listPosition>1</listPosition>"
      << "<applyTo species=\"Species_3\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_3\" type=\"Seedling\"/>"
      << "<applyTo species=\"Species_1\" type=\"Seedling\"/>"
      << "<applyTo species=\"Species_2\" type=\"Seedling\"/>"
      << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>NonSpatialDisperse</behaviorName>"
      << "<version>1.0</version>"
      << "<listPosition>2</listPosition>"
      << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
      << "</behavior>"
      << "</behaviorList>";

  WriteHarvestInterfaceAllometry(oOut);

  oOut << "<HarvestInterface1>"
      << "<hi_executable>" << TESTPATH << "trees1.exe</hi_executable>"
      << "<hi_harvestableTreesFile>" << TESTPATH << "test1harvest.txt</hi_harvestableTreesFile>"
      << "<hi_treesToHarvestFile>" << TESTPATH << "cutfile.txt</hi_treesToHarvestFile>"
      << "<hi_harvestPeriod>-1</hi_harvestPeriod>"
      << "</HarvestInterface1>";

  oOut << "<GeneralDisperse>"
      << "<di_seedDistributionMethod>0</di_seedDistributionMethod>"
      << "</GeneralDisperse>"
      << "<NonSpatialDisperse2>"
      << "<di_minDbhForReproduction>"
      << "<di_mdfrVal species=\"Species_3\">0.0</di_mdfrVal>"
      << "<di_mdfrVal species=\"Species_1\">0.0</di_mdfrVal>"
      << "<di_mdfrVal species=\"Species_2\">0.0</di_mdfrVal>"
      << "</di_minDbhForReproduction>"
      << "<di_nonSpatialSlopeOfLambda>"
      << "<di_nssolVal species=\"Species_3\">0.0</di_nssolVal>"
      << "<di_nssolVal species=\"Species_1\">0.0</di_nssolVal>"
      << "<di_nssolVal species=\"Species_2\">0.0</di_nssolVal>"
      << "</di_nonSpatialSlopeOfLambda>"
      << "<di_nonSpatialInterceptOfLambda>"
      << "<di_nsiolVal species=\"Species_3\">0</di_nsiolVal>"
      << "<di_nsiolVal species=\"Species_1\">0</di_nsiolVal>"
      << "<di_nsiolVal species=\"Species_2\">0</di_nsiolVal>"
      << "</di_nonSpatialInterceptOfLambda>"
      << "</NonSpatialDisperse2>"
      << "</paramFile>";

  oOut.close();
  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteHarvestInterfaceXMLErrorFile3()
////////////////////////////////////////////////////////////////////////////
const char* WriteHarvestInterfaceXMLErrorFile3() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
      << "<paramFile fileCode=\"06060101\">"
      << "<plot>"
      << "<timesteps>10</timesteps>"
      << "<rt_timestep>0</rt_timestep>"
      << "<randomSeed>0</randomSeed>"
      << "<yearsPerTimestep>1.0</yearsPerTimestep>"
      << "<plot_lenX>500.0</plot_lenX>"
      << "<plot_lenY>500.0</plot_lenY>"
      << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
      << "<plot_temp_C>12.88171785</plot_temp_C>"
      << "<plot_latitude>41.92</plot_latitude>"
      << "<plot_title>Default parameter file-use for testing only</plot_title>"
      << "</plot>";

  WriteHarvestInterfaceTrees(oOut);

  oOut << "<behaviorList>"
      << "<behavior>"
      << "<behaviorName>HarvestInterface</behaviorName>"
      << "<version>1.0</version>"
      << "<listPosition>1</listPosition>"
      << "<applyTo species=\"Species_3\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_3\" type=\"Seedling\"/>"
      << "<applyTo species=\"Species_1\" type=\"Seedling\"/>"
      << "<applyTo species=\"Species_2\" type=\"Seedling\"/>"
      << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>ConstantGLI</behaviorName>"
      << "<version>1.0</version>"
      << "<listPosition>2</listPosition>"
      << "<applyTo species=\"Species_3\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_3\" type=\"Seedling\"/>"
      << "<applyTo species=\"Species_1\" type=\"Seedling\"/>"
      << "<applyTo species=\"Species_2\" type=\"Seedling\"/>"
      << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>ConstRadialGrowth</behaviorName>"
      << "<version>1.0</version>"
      << "<listPosition>3</listPosition>"
      << "<applyTo species=\"Species_3\" type=\"Sapling\"/>"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>SimpleLinearGrowth</behaviorName>"
      << "<version>1.0</version>"
      << "<listPosition>4</listPosition>"
      << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_3\" type=\"Seedling\"/>"
      << "<applyTo species=\"Species_1\" type=\"Seedling\"/>"
      << "<applyTo species=\"Species_2\" type=\"Seedling\"/>"
      << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>NonSpatialDisperse</behaviorName>"
      << "<version>1.0</version>"
      << "<listPosition>5</listPosition>"
      << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
      << "</behavior>"
      << "</behaviorList>";

  WriteHarvestInterfaceAllometry(oOut);

  oOut << "<HarvestInterface1>"
      << "<hi_executable>" << TESTPATH << "trees2.exe</hi_executable>"
      << "<hi_harvestableTreesFile>" << TESTPATH << "Test 2 Harvest.txt</hi_harvestableTreesFile>"
      << "<hi_treesToHarvestFile>" << TESTPATH << "Cut File 2.txt</hi_treesToHarvestFile>"
      << "<hi_executableArguments>Some arguments!</hi_executableArguments>"
      << "<hi_harvestPeriod>1</hi_harvestPeriod>"
      << "<hi_dataMembers>"
      << "<hi_dataMember>Growth1</hi_dataMember>"
      << "<hi_dataMember>Light</hi_dataMember>"
      << "</hi_dataMembers>"
      << "</HarvestInterface1>";

  oOut << "<ConstantGLI2>"
      << "<li_constGLI>100.0</li_constGLI>"
      << "</ConstantGLI2>"
      << "<ConstRadialGrowth3>"
      << "<gr_adultConstRadialInc>"
      << "<gr_acriVal species=\"Species_3\">6.0</gr_acriVal>"
      << "</gr_adultConstRadialInc>"
      << "</ConstRadialGrowth3>"
      << "<SimpleLinearGrowth4>"
      << "<gr_diamSimpleLinearIntercept>"
      << "<gr_dsliVal species=\"Species_3\">0.0</gr_dsliVal>"
      << "<gr_dsliVal species=\"Species_1\">0.0</gr_dsliVal>"
      << "<gr_dsliVal species=\"Species_2\">0.0</gr_dsliVal>"
      << "</gr_diamSimpleLinearIntercept>"
      << "<gr_diamSimpleLinearSlope>"
      << "<gr_dslsVal species=\"Species_3\">0.0</gr_dslsVal>"
      << "<gr_dslsVal species=\"Species_1\">0.0</gr_dslsVal>"
      << "<gr_dslsVal species=\"Species_2\">0.0</gr_dslsVal>"
      << "</gr_diamSimpleLinearSlope>"
      << "</SimpleLinearGrowth4>"
      << "<GeneralDisperse>"
      << "<di_seedDistributionMethod>0</di_seedDistributionMethod>"
      << "</GeneralDisperse>"
      << "<NonSpatialDisperse5>"
      << "<di_minDbhForReproduction>"
      << "<di_mdfrVal species=\"Species_3\">0.0</di_mdfrVal>"
      << "<di_mdfrVal species=\"Species_1\">0.0</di_mdfrVal>"
      << "<di_mdfrVal species=\"Species_2\">0.0</di_mdfrVal>"
      << "</di_minDbhForReproduction>"
      << "<di_nonSpatialSlopeOfLambda>"
      << "<di_nssolVal species=\"Species_3\">0.0</di_nssolVal>"
      << "<di_nssolVal species=\"Species_1\">0.0</di_nssolVal>"
      << "<di_nssolVal species=\"Species_2\">0.0</di_nssolVal>"
      << "</di_nonSpatialSlopeOfLambda>"
      << "<di_nonSpatialInterceptOfLambda>"
      << "<di_nsiolVal species=\"Species_3\">0</di_nsiolVal>"
      << "<di_nsiolVal species=\"Species_1\">0</di_nsiolVal>"
      << "<di_nsiolVal species=\"Species_2\">0</di_nsiolVal>"
      << "</di_nonSpatialInterceptOfLambda>"
      << "</NonSpatialDisperse5>"
      << "</paramFile>";

  oOut.close();
  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteHarvestInterfaceXMLErrorFile4()
////////////////////////////////////////////////////////////////////////////
const char* WriteHarvestInterfaceXMLErrorFile4() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
      << "<paramFile fileCode=\"06060101\">"
      << "<plot>"
      << "<timesteps>10</timesteps>"
      << "<rt_timestep>0</rt_timestep>"
      << "<randomSeed>0</randomSeed>"
      << "<yearsPerTimestep>1.0</yearsPerTimestep>"
      << "<plot_lenX>500.0</plot_lenX>"
      << "<plot_lenY>500.0</plot_lenY>"
      << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
      << "<plot_temp_C>12.88171785</plot_temp_C>"
      << "<plot_latitude>41.92</plot_latitude>"
      << "<plot_title>Default parameter file-use for testing only</plot_title>"
      << "</plot>";

  WriteHarvestInterfaceTrees(oOut);

  oOut << "<behaviorList>"
      << "<behavior>"
      << "<behaviorName>HarvestInterface</behaviorName>"
      << "<version>1.0</version>"
      << "<listPosition>1</listPosition>"
      << "<applyTo species=\"Species_3\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_3\" type=\"Seedling\"/>"
      << "<applyTo species=\"Species_1\" type=\"Seedling\"/>"
      << "<applyTo species=\"Species_2\" type=\"Seedling\"/>"
      << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>ConstantGLI</behaviorName>"
      << "<version>1.0</version>"
      << "<listPosition>2</listPosition>"
      << "<applyTo species=\"Species_3\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_3\" type=\"Seedling\"/>"
      << "<applyTo species=\"Species_1\" type=\"Seedling\"/>"
      << "<applyTo species=\"Species_2\" type=\"Seedling\"/>"
      << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>SimpleLinearGrowth</behaviorName>"
      << "<version>1.0</version>"
      << "<listPosition>3</listPosition>"
      << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_3\" type=\"Seedling\"/>"
      << "<applyTo species=\"Species_1\" type=\"Seedling\"/>"
      << "<applyTo species=\"Species_2\" type=\"Seedling\"/>"
      << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>NonSpatialDisperse</behaviorName>"
      << "<version>1.0</version>"
      << "<listPosition>4</listPosition>"
      << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
      << "</behavior>"
      << "</behaviorList>";

  WriteHarvestInterfaceAllometry(oOut);

  oOut << "<HarvestInterface1>"
      << "<hi_executable>" << TESTPATH << "trees2.exe</hi_executable>"
      << "<hi_harvestableTreesFile>" << TESTPATH << "Test 2 Harvest.txt</hi_harvestableTreesFile>"
      << "<hi_treesToHarvestFile>" << TESTPATH << "Cut File 2.txt</hi_treesToHarvestFile>"
      << "<hi_executableArguments>Some arguments!</hi_executableArguments>"
      << "<hi_harvestPeriod>1</hi_harvestPeriod>"
      << "<hi_dataMembers>"
      << "<hi_dataMember>Growth</hi_dataMember>"
      << "<hi_dataMember>Light</hi_dataMember>"
      << "</hi_dataMembers>"
      << "</HarvestInterface1>";

  oOut << "<ConstantGLI2>"
      << "<li_constGLI>100.0</li_constGLI>"
      << "</ConstantGLI2>"
      << "<SimpleLinearGrowth3>"
      << "<gr_diamSimpleLinearIntercept>"
      << "<gr_dsliVal species=\"Species_3\">0.0</gr_dsliVal>"
      << "<gr_dsliVal species=\"Species_1\">0.0</gr_dsliVal>"
      << "<gr_dsliVal species=\"Species_2\">0.0</gr_dsliVal>"
      << "</gr_diamSimpleLinearIntercept>"
      << "<gr_diamSimpleLinearSlope>"
      << "<gr_dslsVal species=\"Species_3\">0.0</gr_dslsVal>"
      << "<gr_dslsVal species=\"Species_1\">0.0</gr_dslsVal>"
      << "<gr_dslsVal species=\"Species_2\">0.0</gr_dslsVal>"
      << "</gr_diamSimpleLinearSlope>"
      << "</SimpleLinearGrowth3>"
      << "<GeneralDisperse>"
      << "<di_seedDistributionMethod>0</di_seedDistributionMethod>"
      << "</GeneralDisperse>"
      << "<NonSpatialDisperse4>"
      << "<di_minDbhForReproduction>"
      << "<di_mdfrVal species=\"Species_3\">0.0</di_mdfrVal>"
      << "<di_mdfrVal species=\"Species_1\">0.0</di_mdfrVal>"
      << "<di_mdfrVal species=\"Species_2\">0.0</di_mdfrVal>"
      << "</di_minDbhForReproduction>"
      << "<di_nonSpatialSlopeOfLambda>"
      << "<di_nssolVal species=\"Species_3\">0.0</di_nssolVal>"
      << "<di_nssolVal species=\"Species_1\">0.0</di_nssolVal>"
      << "<di_nssolVal species=\"Species_2\">0.0</di_nssolVal>"
      << "</di_nonSpatialSlopeOfLambda>"
      << "<di_nonSpatialInterceptOfLambda>"
      << "<di_nsiolVal species=\"Species_3\">0</di_nsiolVal>"
      << "<di_nsiolVal species=\"Species_1\">0</di_nsiolVal>"
      << "<di_nsiolVal species=\"Species_2\">0</di_nsiolVal>"
      << "</di_nonSpatialInterceptOfLambda>"
      << "</NonSpatialDisperse4>"
      << "</paramFile>";

  oOut.close();
  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteHarvestInterfaceXMLErrorFile5()
////////////////////////////////////////////////////////////////////////////
const char* WriteHarvestInterfaceXMLErrorFile5() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
      << "<paramFile fileCode=\"06060101\">"
      << "<plot>"
      << "<timesteps>10</timesteps>"
      << "<rt_timestep>0</rt_timestep>"
      << "<randomSeed>0</randomSeed>"
      << "<yearsPerTimestep>5.0</yearsPerTimestep>"
      << "<plot_lenX>500.0</plot_lenX>"
      << "<plot_lenY>500.0</plot_lenY>"
      << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
      << "<plot_temp_C>12.88171785</plot_temp_C>"
      << "<plot_latitude>41.92</plot_latitude>"
      << "<plot_title>Default parameter file-use for testing only</plot_title>"
      << "</plot>";

  WriteHarvestInterfaceTrees(oOut);

  oOut << "<behaviorList>"
      << "<behavior>"
      << "<behaviorName>HarvestInterface</behaviorName>"
      << "<version>1.0</version>"
      << "<listPosition>1</listPosition>"
      << "<applyTo species=\"Species_3\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_3\" type=\"Seedling\"/>"
      << "<applyTo species=\"Species_1\" type=\"Seedling\"/>"
      << "<applyTo species=\"Species_2\" type=\"Seedling\"/>"
      << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>NonSpatialDisperse</behaviorName>"
      << "<version>1.0</version>"
      << "<listPosition>2</listPosition>"
      << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
      << "</behavior>"
      << "</behaviorList>";

  WriteHarvestInterfaceAllometry(oOut);

  oOut << "<HarvestInterface1>"
      << "<hi_executable>" << TESTPATH << "trees6.exe</hi_executable>"
      << "<hi_harvestableTreesFile>" << TESTPATH << "test1harvest.txt</hi_harvestableTreesFile>"
      << "<hi_treesToHarvestFile>" << TESTPATH << "cutfilefake.txt</hi_treesToHarvestFile>"
      << "<hi_executableArguments>1</hi_executableArguments>"
      << "<hi_harvestPeriod>1</hi_harvestPeriod>"
      << "</HarvestInterface1>";

  oOut << "<GeneralDisperse>"
      << "<di_seedDistributionMethod>0</di_seedDistributionMethod>"
      << "</GeneralDisperse>"
      << "<NonSpatialDisperse2>"
      << "<di_minDbhForReproduction>"
      << "<di_mdfrVal species=\"Species_3\">0.0</di_mdfrVal>"
      << "<di_mdfrVal species=\"Species_1\">0.0</di_mdfrVal>"
      << "<di_mdfrVal species=\"Species_2\">0.0</di_mdfrVal>"
      << "</di_minDbhForReproduction>"
      << "<di_nonSpatialSlopeOfLambda>"
      << "<di_nssolVal species=\"Species_3\">0.0</di_nssolVal>"
      << "<di_nssolVal species=\"Species_1\">0.0</di_nssolVal>"
      << "<di_nssolVal species=\"Species_2\">0.0</di_nssolVal>"
      << "</di_nonSpatialSlopeOfLambda>"
      << "<di_nonSpatialInterceptOfLambda>"
      << "<di_nsiolVal species=\"Species_3\">0</di_nsiolVal>"
      << "<di_nsiolVal species=\"Species_1\">0</di_nsiolVal>"
      << "<di_nsiolVal species=\"Species_2\">0</di_nsiolVal>"
      << "</di_nonSpatialInterceptOfLambda>"
      << "</NonSpatialDisperse2>"
      << "</paramFile>";

  oOut.close();
  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteHarvestInterfaceXMLErrorFile6()
////////////////////////////////////////////////////////////////////////////
const char* WriteHarvestInterfaceXMLErrorFile6() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
      << "<paramFile fileCode=\"06060101\">"
      << "<plot>"
      << "<timesteps>3</timesteps>"
      << "<rt_timestep>0</rt_timestep>"
      << "<randomSeed>0</randomSeed>"
      << "<yearsPerTimestep>2</yearsPerTimestep>"
      << "<plot_lenX>500.0</plot_lenX>"
      << "<plot_lenY>500.0</plot_lenY>"
      << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
      << "<plot_temp_C>12.88171785</plot_temp_C>"
      << "<plot_latitude>41.92</plot_latitude>"
      << "<plot_title>Default parameter file-use for testing only</plot_title>"
      << "</plot>";

  WriteHarvestInterfaceTrees(oOut);

  oOut << "<behaviorList>"
      << "<behavior>"
      << "<behaviorName>HarvestInterface (test 1) (test 2) (test 3)</behaviorName>"
      << "<version>1.0</version>"
      << "<listPosition>1</listPosition>"
      << "<applyTo species=\"Species_3\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_3\" type=\"Seedling\"/>"
      << "<applyTo species=\"Species_1\" type=\"Seedling\"/>"
      << "<applyTo species=\"Species_2\" type=\"Seedling\"/>"
      << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>StochasticMortality</behaviorName>"
      << "<version>1.0</version>"
      << "<listPosition>2</listPosition>"
      << "<applyTo species=\"Species_3\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_3\" type=\"Seedling\"/>"
      << "<applyTo species=\"Species_1\" type=\"Seedling\"/>"
      << "<applyTo species=\"Species_2\" type=\"Seedling\"/>"
      << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>TreeAgeCalculator</behaviorName>"
      << "<version>1.0</version>"
      << "<listPosition>3</listPosition>"
      << "<applyTo species=\"Species_3\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_3\" type=\"Seedling\"/>"
      << "<applyTo species=\"Species_1\" type=\"Seedling\"/>"
      << "<applyTo species=\"Species_2\" type=\"Seedling\"/>"
      << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
      << "</behavior>"
      << "</behaviorList>";

  WriteHarvestInterfaceAllometry(oOut);

  oOut << "<HarvestInterface1>"
      << "<hi_executable>" << TESTPATH << "trees4.exe</hi_executable>"
      << "<hi_harvestableTreesFile>" << TESTPATH << "test4harvest.txt</hi_harvestableTreesFile>"
      << "<hi_treesToHarvestFile>" << TESTPATH << "cutfile4.txt</hi_treesToHarvestFile>"
      << "<hi_treesToUpdateFile>" << TESTPATH2 << "Update File Fake.txt</hi_treesToUpdateFile>"
      << "<hi_harvestPeriod>6</hi_harvestPeriod>"
      << "<hi_dataMembers>"
      << "<hi_dataMember>test 2</hi_dataMember>"
      << "<hi_dataMember>Tree Age</hi_dataMember>"
      << "<hi_dataMember>test 1</hi_dataMember>"
      << "<hi_dataMember>dead</hi_dataMember>"
      << "<hi_dataMember>test 3</hi_dataMember>"
      << "</hi_dataMembers>"
      << "</HarvestInterface1>";

  oOut << "<StochasticMortality2>"
      << "<mo_stochasticMortRate>"
      << "<mo_smrVal species=\"Species_1\">0.0</mo_smrVal>"
      << "<mo_smrVal species=\"Species_2\">0.0</mo_smrVal>"
      << "<mo_smrVal species=\"Species_3\">0.0</mo_smrVal>"
      << "</mo_stochasticMortRate>"
      << "</StochasticMortality2>"
      << "</paramFile>";

  oOut.close();
  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteHarvestInterfaceXMLErrorFile7()
////////////////////////////////////////////////////////////////////////////
const char* WriteHarvestInterfaceXMLErrorFile7() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
      << "<paramFile fileCode=\"06060101\">"
      << "<plot>"
      << "<timesteps>3</timesteps>"
      << "<rt_timestep>0</rt_timestep>"
      << "<randomSeed>0</randomSeed>"
      << "<yearsPerTimestep>1</yearsPerTimestep>"
      << "<plot_lenX>200.0</plot_lenX>"
      << "<plot_lenY>200.0</plot_lenY>"
      << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
      << "<plot_temp_C>12.88171785</plot_temp_C>"
      << "<plot_latitude>41.92</plot_latitude>"
      << "<plot_title>Default parameter file-use for testing only</plot_title>"
      << "</plot>"
      << "<trees>"
      << "<tr_speciesList>"
      << "<tr_species speciesName=\"Species_1\"/>"
      << "<tr_species speciesName=\"Species_2\"/>"
      << "<tr_species speciesName=\"Species_3\"/>"
      << "</tr_speciesList>"
      << "<tr_sizeClasses>"
      << "<tr_sizeClass sizeKey=\"Seedling\"/>"
      << "<tr_sizeClass sizeKey=\"s2.5\"/>"
      << "<tr_sizeClass sizeKey=\"s5.0\"/>"
      << "<tr_sizeClass sizeKey=\"s20.0\"/>"
      << "<tr_sizeClass sizeKey=\"s30.0\"/>"
      << "</tr_sizeClasses>"
      << "<tr_initialDensities>"
      << "<tr_idVals whatSpecies=\"Species_1\">"
      << "<tr_initialDensity sizeClass=\"Seedling\">20.0</tr_initialDensity>"
      << "<tr_initialDensity sizeClass=\"s5.0\">20.0</tr_initialDensity>"
      << "<tr_initialDensity sizeClass=\"s30.0\">20.0</tr_initialDensity>"
      << "</tr_idVals>"
      << "<tr_idVals whatSpecies=\"Species_2\">"
      << "<tr_initialDensity sizeClass=\"Seedling\">20.0</tr_initialDensity>"
      << "<tr_initialDensity sizeClass=\"s5.0\">20.0</tr_initialDensity>"
      << "<tr_initialDensity sizeClass=\"s30.0\">20.0</tr_initialDensity>"
      << "</tr_idVals>"
      << "<tr_idVals whatSpecies=\"Species_3\">"
      << "<tr_initialDensity sizeClass=\"Seedling\">20.0</tr_initialDensity>"
      << "<tr_initialDensity sizeClass=\"s5.0\">20.0</tr_initialDensity>"
      << "<tr_initialDensity sizeClass=\"s30.0\">20.0</tr_initialDensity>"
      << "</tr_idVals>"
      << "</tr_initialDensities>"
      << "<tr_seedDiam10Cm>0.2</tr_seedDiam10Cm>"
      << "<tr_minAdultDBH>"
      << "<tr_madVal species=\"Species_3\">10.0</tr_madVal>"
      << "<tr_madVal species=\"Species_1\">10.0</tr_madVal>"
      << "<tr_madVal species=\"Species_2\">10.0</tr_madVal>"
      << "</tr_minAdultDBH>"
      << "<tr_maxSeedlingHeight>"
      << "<tr_mshVal species=\"Species_3\">1.35</tr_mshVal>"
      << "<tr_mshVal species=\"Species_1\">1.35</tr_mshVal>"
      << "<tr_mshVal species=\"Species_2\">1.35</tr_mshVal>"
      << "</tr_maxSeedlingHeight>"
      << "</trees>"
      << "<behaviorList>"
      << "<behavior>"
      << "<behaviorName>HarvestInterface</behaviorName>"
      << "<version>1.0</version>"
      << "<listPosition>1</listPosition>"
      << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_1\" type=\"Seedling\"/>"
      << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>NonSpatialDisperse</behaviorName>"
      << "<version>1.0</version>"
      << "<listPosition>2</listPosition>"
      << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
      << "</behavior>"
      << "</behaviorList>";

  WriteHarvestInterfaceAllometry(oOut);

  oOut << "<HarvestInterface1>"
      << "<hi_executable>" << TESTPATH << "trees6.exe</hi_executable>"
      << "<hi_harvestableTreesFile>" << TESTPATH << "test1harvest.txt</hi_harvestableTreesFile>"
      << "<hi_treesToHarvestFile>" << TESTPATH << "cutfile.txt</hi_treesToHarvestFile>"
      << "<hi_executableArguments>1</hi_executableArguments>"
      << "<hi_harvestPeriod>1</hi_harvestPeriod>"
      << "</HarvestInterface1>";

  oOut << "<GeneralDisperse>"
      << "<di_seedDistributionMethod>0</di_seedDistributionMethod>"
      << "</GeneralDisperse>"
      << "<NonSpatialDisperse2>"
      << "<di_minDbhForReproduction>"
      << "<di_mdfrVal species=\"Species_3\">0.0</di_mdfrVal>"
      << "<di_mdfrVal species=\"Species_1\">0.0</di_mdfrVal>"
      << "<di_mdfrVal species=\"Species_2\">0.0</di_mdfrVal>"
      << "</di_minDbhForReproduction>"
      << "<di_nonSpatialSlopeOfLambda>"
      << "<di_nssolVal species=\"Species_3\">0.0</di_nssolVal>"
      << "<di_nssolVal species=\"Species_1\">0.0</di_nssolVal>"
      << "<di_nssolVal species=\"Species_2\">0.0</di_nssolVal>"
      << "</di_nonSpatialSlopeOfLambda>"
      << "<di_nonSpatialInterceptOfLambda>"
      << "<di_nsiolVal species=\"Species_3\">0</di_nsiolVal>"
      << "<di_nsiolVal species=\"Species_1\">0</di_nsiolVal>"
      << "<di_nsiolVal species=\"Species_2\">0</di_nsiolVal>"
      << "</di_nonSpatialInterceptOfLambda>"
      << "</NonSpatialDisperse2>"
      << "</paramFile>";

  oOut.close();
  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteHarvestInterfaceXMLErrorFile8()
////////////////////////////////////////////////////////////////////////////
const char* WriteHarvestInterfaceXMLErrorFile8() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
      << "<paramFile fileCode=\"06060101\">"
      << "<plot>"
      << "<timesteps>3</timesteps>"
      << "<rt_timestep>0</rt_timestep>"
      << "<randomSeed>0</randomSeed>"
      << "<yearsPerTimestep>1.0</yearsPerTimestep>"
      << "<plot_lenX>500.0</plot_lenX>"
      << "<plot_lenY>500.0</plot_lenY>"
      << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
      << "<plot_temp_C>12.88171785</plot_temp_C>"
      << "<plot_latitude>41.92</plot_latitude>"
      << "<plot_title>Default parameter file-use for testing only</plot_title>"
      << "</plot>"
      << "<trees>"
      << "<tr_speciesList>"
      << "<tr_species speciesName=\"Species_1\"/>"
      << "<tr_species speciesName=\"Species_2\"/>"
      << "<tr_species speciesName=\"Species_3\"/>"
      << "</tr_speciesList>"
      << "<tr_sizeClasses>"
      << "<tr_sizeClass sizeKey=\"Seedling\"/>"
      << "<tr_sizeClass sizeKey=\"s2.5\"/>"
      << "<tr_sizeClass sizeKey=\"s5.0\"/>"
      << "<tr_sizeClass sizeKey=\"s20.0\"/>"
      << "<tr_sizeClass sizeKey=\"s30.0\"/>"
      << "</tr_sizeClasses>"
      << "<tr_initialDensities>"
      << "<tr_idVals whatSpecies=\"Species_1\">"
      << "<tr_initialDensity sizeClass=\"Seedling\">20.0</tr_initialDensity>"
      << "<tr_initialDensity sizeClass=\"s5.0\">20.0</tr_initialDensity>"
      << "<tr_initialDensity sizeClass=\"s30.0\">20.0</tr_initialDensity>"
      << "</tr_idVals>"
      << "<tr_idVals whatSpecies=\"Species_2\">"
      << "<tr_initialDensity sizeClass=\"Seedling\">20.0</tr_initialDensity>"
      << "<tr_initialDensity sizeClass=\"s5.0\">20.0</tr_initialDensity>"
      << "<tr_initialDensity sizeClass=\"s30.0\">20.0</tr_initialDensity>"
      << "</tr_idVals>"
      << "<tr_idVals whatSpecies=\"Species_3\">"
      << "<tr_initialDensity sizeClass=\"Seedling\">20.0</tr_initialDensity>"
      << "<tr_initialDensity sizeClass=\"s5.0\">20.0</tr_initialDensity>"
      << "<tr_initialDensity sizeClass=\"s30.0\">20.0</tr_initialDensity>"
      << "</tr_idVals>"
      << "</tr_initialDensities>"
      << "<tr_seedDiam10Cm>0.2</tr_seedDiam10Cm>"
      << "<tr_minAdultDBH>"
      << "<tr_madVal species=\"Species_3\">10.0</tr_madVal>"
      << "<tr_madVal species=\"Species_1\">10.0</tr_madVal>"
      << "<tr_madVal species=\"Species_2\">10.0</tr_madVal>"
      << "</tr_minAdultDBH>"
      << "<tr_maxSeedlingHeight>"
      << "<tr_mshVal species=\"Species_3\">1.35</tr_mshVal>"
      << "<tr_mshVal species=\"Species_1\">1.35</tr_mshVal>"
      << "<tr_mshVal species=\"Species_2\">1.35</tr_mshVal>"
      << "</tr_maxSeedlingHeight>"
      << "</trees>";

  oOut << "<behaviorList>"
      << "<behavior>"
      << "<behaviorName>HarvestInterface (test 1) (test 2) (test 3)</behaviorName>"
      << "<version>1.0</version>"
      << "<listPosition>1</listPosition>"
      << "<applyTo species=\"Species_3\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_3\" type=\"Seedling\"/>"
      << "<applyTo species=\"Species_1\" type=\"Seedling\"/>"
      << "<applyTo species=\"Species_2\" type=\"Seedling\"/>"
      << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>StochasticMortality</behaviorName>"
      << "<version>1.0</version>"
      << "<listPosition>2</listPosition>"
      << "<applyTo species=\"Species_3\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_3\" type=\"Seedling\"/>"
      << "<applyTo species=\"Species_1\" type=\"Seedling\"/>"
      << "<applyTo species=\"Species_2\" type=\"Seedling\"/>"
      << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>TreeAgeCalculator</behaviorName>"
      << "<version>1.0</version>"
      << "<listPosition>3</listPosition>"
      << "<applyTo species=\"Species_3\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_3\" type=\"Seedling\"/>"
      << "<applyTo species=\"Species_1\" type=\"Seedling\"/>"
      << "<applyTo species=\"Species_2\" type=\"Seedling\"/>"
      << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
      << "</behavior>"
      << "</behaviorList>";

  WriteHarvestInterfaceAllometry(oOut);

  oOut << "<HarvestInterface1>"
      << "<hi_executable>" << TESTPATH << "trees6.exe</hi_executable>"
      << "<hi_harvestableTreesFile>" << TESTPATH2 << "Test 3 SORTIE input.txt</hi_harvestableTreesFile>"
      << "<hi_treesToHarvestFile>" << TESTPATH << "cutfile.txt</hi_treesToHarvestFile>"
      << "<hi_treesToUpdateFile>" << TESTPATH << "Update File 3.txt</hi_treesToUpdateFile>"
      << "<hi_executableArguments>2</hi_executableArguments>"
      << "<hi_harvestPeriod>1</hi_harvestPeriod>"
      << "<hi_dataMembers>"
      << "<hi_dataMember>test 2</hi_dataMember>"
      << "<hi_dataMember>Tree Age</hi_dataMember>"
      << "<hi_dataMember>test 1</hi_dataMember>"
      << "<hi_dataMember>dead</hi_dataMember>"
      << "<hi_dataMember>test 3</hi_dataMember>"
      << "</hi_dataMembers>"
      << "</HarvestInterface1>";

  oOut << "<StochasticMortality2>"
      << "<mo_stochasticMortRate>"
      << "<mo_smrVal species=\"Species_1\">0.0</mo_smrVal>"
      << "<mo_smrVal species=\"Species_2\">0.0</mo_smrVal>"
      << "<mo_smrVal species=\"Species_3\">0.0</mo_smrVal>"
      << "</mo_stochasticMortRate>"
      << "</StochasticMortality2>"
      << "</paramFile>";

  oOut.close();
  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteHarvestInterfaceXMLErrorFile9()
////////////////////////////////////////////////////////////////////////////
const char* WriteHarvestInterfaceXMLErrorFile9() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
      << "<paramFile fileCode=\"06060101\">"
      << "<plot>"
      << "<timesteps>3</timesteps>"
      << "<rt_timestep>0</rt_timestep>"
      << "<randomSeed>0</randomSeed>"
      << "<yearsPerTimestep>1.0</yearsPerTimestep>"
      << "<plot_lenX>200.0</plot_lenX>"
      << "<plot_lenY>200.0</plot_lenY>"
      << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
      << "<plot_temp_C>12.88171785</plot_temp_C>"
      << "<plot_latitude>41.92</plot_latitude>"
      << "<plot_title>Default parameter file-use for testing only</plot_title>"
      << "</plot>"
      << "<trees>"
      << "<tr_speciesList>"
      << "<tr_species speciesName=\"Species_1\"/>"
      << "<tr_species speciesName=\"Species_2\"/>"
      << "<tr_species speciesName=\"Species_3\"/>"
      << "</tr_speciesList>"
      << "<tr_sizeClasses>"
      << "<tr_sizeClass sizeKey=\"Seedling\"/>"
      << "<tr_sizeClass sizeKey=\"s2.5\"/>"
      << "<tr_sizeClass sizeKey=\"s5.0\"/>"
      << "<tr_sizeClass sizeKey=\"s20.0\"/>"
      << "<tr_sizeClass sizeKey=\"s30.0\"/>"
      << "</tr_sizeClasses>"
      << "<tr_initialDensities>"
      << "<tr_idVals whatSpecies=\"Species_1\">"
      << "<tr_initialDensity sizeClass=\"Seedling\">20.0</tr_initialDensity>"
      << "<tr_initialDensity sizeClass=\"s5.0\">20.0</tr_initialDensity>"
      << "<tr_initialDensity sizeClass=\"s30.0\">20.0</tr_initialDensity>"
      << "</tr_idVals>"
      << "<tr_idVals whatSpecies=\"Species_2\">"
      << "<tr_initialDensity sizeClass=\"Seedling\">20.0</tr_initialDensity>"
      << "<tr_initialDensity sizeClass=\"s5.0\">20.0</tr_initialDensity>"
      << "<tr_initialDensity sizeClass=\"s30.0\">20.0</tr_initialDensity>"
      << "</tr_idVals>"
      << "<tr_idVals whatSpecies=\"Species_3\">"
      << "<tr_initialDensity sizeClass=\"Seedling\">20.0</tr_initialDensity>"
      << "<tr_initialDensity sizeClass=\"s5.0\">20.0</tr_initialDensity>"
      << "<tr_initialDensity sizeClass=\"s30.0\">20.0</tr_initialDensity>"
      << "</tr_idVals>"
      << "</tr_initialDensities>"
      << "<tr_seedDiam10Cm>0.2</tr_seedDiam10Cm>"
      << "<tr_minAdultDBH>"
      << "<tr_madVal species=\"Species_3\">10.0</tr_madVal>"
      << "<tr_madVal species=\"Species_1\">10.0</tr_madVal>"
      << "<tr_madVal species=\"Species_2\">10.0</tr_madVal>"
      << "</tr_minAdultDBH>"
      << "<tr_maxSeedlingHeight>"
      << "<tr_mshVal species=\"Species_3\">1.35</tr_mshVal>"
      << "<tr_mshVal species=\"Species_1\">1.35</tr_mshVal>"
      << "<tr_mshVal species=\"Species_2\">1.35</tr_mshVal>"
      << "</tr_maxSeedlingHeight>"
      << "</trees>"
      << "<behaviorList>"
      << "<behavior>"
      << "<behaviorName>HarvestInterface</behaviorName>"
      << "<version>1.0</version>"
      << "<listPosition>1</listPosition>"
      << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_1\" type=\"Seedling\"/>"
      << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>NonSpatialDisperse</behaviorName>"
      << "<version>1.0</version>"
      << "<listPosition>2</listPosition>"
      << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
      << "</behavior>"
      << "</behaviorList>";

  WriteHarvestInterfaceAllometry(oOut);

  oOut << "<HarvestInterface1>"
      << "<hi_executable>" << TESTPATH << "trees5.exe</hi_executable>"
      << "<hi_harvestableTreesFile>" << TESTPATH << "test5harvest.txt</hi_harvestableTreesFile>"
      << "<hi_treesToHarvestFile>" << TESTPATH << "cutfile5.txt</hi_treesToHarvestFile>"
      << "<hi_batchParamsFile>" << TESTPATH << "allparamserror.txt</hi_batchParamsFile>"
      << "<hi_batchSingleRunParamsFile>" << TESTPATH << "parameters5.txt</hi_batchSingleRunParamsFile>"
      << "<hi_executableArguments>yes</hi_executableArguments>"
      << "<hi_harvestPeriod>1</hi_harvestPeriod>"
      << "</HarvestInterface1>";

  oOut << "<GeneralDisperse>"
      << "<di_seedDistributionMethod>0</di_seedDistributionMethod>"
      << "</GeneralDisperse>"
      << "<NonSpatialDisperse2>"
      << "<di_minDbhForReproduction>"
      << "<di_mdfrVal species=\"Species_3\">0.0</di_mdfrVal>"
      << "<di_mdfrVal species=\"Species_1\">0.0</di_mdfrVal>"
      << "<di_mdfrVal species=\"Species_2\">0.0</di_mdfrVal>"
      << "</di_minDbhForReproduction>"
      << "<di_nonSpatialSlopeOfLambda>"
      << "<di_nssolVal species=\"Species_3\">0.0</di_nssolVal>"
      << "<di_nssolVal species=\"Species_1\">0.0</di_nssolVal>"
      << "<di_nssolVal species=\"Species_2\">0.0</di_nssolVal>"
      << "</di_nonSpatialSlopeOfLambda>"
      << "<di_nonSpatialInterceptOfLambda>"
      << "<di_nsiolVal species=\"Species_3\">0</di_nsiolVal>"
      << "<di_nsiolVal species=\"Species_1\">0</di_nsiolVal>"
      << "<di_nsiolVal species=\"Species_2\">0</di_nsiolVal>"
      << "</di_nonSpatialInterceptOfLambda>"
      << "</NonSpatialDisperse2>"
      << "</paramFile>";

  oOut.close();
  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteHarvestInterfaceXMLBatch1()
////////////////////////////////////////////////////////////////////////////
const char* WriteHarvestInterfaceXMLBatch1() {
  using namespace std;
  const char *cFileString = "TestBatchFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
      << "<batchFile fileCode=\"06010401\">"
      << "<ba_parFile>"
      << "<ba_fileName>" << TESTPATH << "TestFile1.xml</ba_fileName>"
      << "<ba_numTimesToRun>3</ba_numTimesToRun>"
      << "</ba_parFile>"
      << "</batchFile>";

  oOut.close();
  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteHarvestInterfaceXMLErrorBatch1()
////////////////////////////////////////////////////////////////////////////
const char* WriteHarvestInterfaceXMLErrorBatch1() {
  using namespace std;
  const char *cFileString = "TestBatchFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
      << "<batchFile fileCode=\"06010401\">"
      << "<ba_parFile>"
      << "<ba_fileName>" << TESTPATH << "TestFile1.xml</ba_fileName>"
      << "<ba_numTimesToRun>4</ba_numTimesToRun>"
      << "</ba_parFile>"
      << "</batchFile>";

  oOut.close();
  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteHarvestInterfaceAllParamsFile()
////////////////////////////////////////////////////////////////////////////
const char* WriteHarvestInterfaceAllParamsFile() {
  using namespace std;
  const char *cFileString = "allparams.txt";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  oOut << 1 << "\t" << 30 << "\t" <<  32.676 << endl
      << 2 << "\t" << 86 << "\t" <<  65.333 << endl
      << 3 << "\t" << 0 << "\t" << -0.34 << endl;

  oOut.close();
  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteHarvestInterfaceTrees()
////////////////////////////////////////////////////////////////////////////
void WriteHarvestInterfaceTrees(std::fstream &oOut) {
  oOut << "<trees>"
      << "<tr_speciesList>"
      << "<tr_species speciesName=\"Species_1\"/>"
      << "<tr_species speciesName=\"Species_2\"/>"
      << "<tr_species speciesName=\"Species_3\"/>"
      << "</tr_speciesList>"
      << "<tr_seedDiam10Cm>0.2</tr_seedDiam10Cm>"
      << "<tr_minAdultDBH>"
      << "<tr_madVal species=\"Species_3\">10.0</tr_madVal>"
      << "<tr_madVal species=\"Species_1\">10.0</tr_madVal>"
      << "<tr_madVal species=\"Species_2\">10.0</tr_madVal>"
      << "</tr_minAdultDBH>"
      << "<tr_maxSeedlingHeight>"
      << "<tr_mshVal species=\"Species_3\">1.35</tr_mshVal>"
      << "<tr_mshVal species=\"Species_1\">1.35</tr_mshVal>"
      << "<tr_mshVal species=\"Species_2\">1.35</tr_mshVal>"
      << "</tr_maxSeedlingHeight>"
      << "</trees>";
}

////////////////////////////////////////////////////////////////////////////
// WriteHarvestInterfaceAllometry()
////////////////////////////////////////////////////////////////////////////
void WriteHarvestInterfaceAllometry(std::fstream &oOut) {
  oOut << "<allometry>"
      << "<tr_whatAdultHeightDiam>"
      << "<tr_wahdVal species=\"Species_3\">0</tr_wahdVal>"
      << "<tr_wahdVal species=\"Species_1\">0</tr_wahdVal>"
      << "<tr_wahdVal species=\"Species_2\">0</tr_wahdVal>"
      << "</tr_whatAdultHeightDiam>"
      << "<tr_whatSaplingHeightDiam>"
      << "<tr_wsahdVal species=\"Species_3\">0</tr_wsahdVal>"
      << "<tr_wsahdVal species=\"Species_1\">0</tr_wsahdVal>"
      << "<tr_wsahdVal species=\"Species_2\">0</tr_wsahdVal>"
      << "</tr_whatSaplingHeightDiam>"
      << "<tr_whatSeedlingHeightDiam>"
      << "<tr_wsehdVal species=\"Species_3\">0</tr_wsehdVal>"
      << "<tr_wsehdVal species=\"Species_1\">0</tr_wsehdVal>"
      << "<tr_wsehdVal species=\"Species_2\">0</tr_wsehdVal>"
      << "</tr_whatSeedlingHeightDiam>"
      << "<tr_whatAdultCrownRadDiam>"
      << "<tr_wacrdVal species=\"Species_3\">0</tr_wacrdVal>"
      << "<tr_wacrdVal species=\"Species_1\">0</tr_wacrdVal>"
      << "<tr_wacrdVal species=\"Species_2\">0</tr_wacrdVal>"
      << "</tr_whatAdultCrownRadDiam>"
      << "<tr_whatSaplingCrownRadDiam>"
      << "<tr_wscrdVal species=\"Species_3\">0</tr_wscrdVal>"
      << "<tr_wscrdVal species=\"Species_1\">0</tr_wscrdVal>"
      << "<tr_wscrdVal species=\"Species_2\">0</tr_wscrdVal>"
      << "</tr_whatSaplingCrownRadDiam>"
      << "<tr_whatAdultCrownHeightHeight>"
      << "<tr_wachhVal species=\"Species_3\">0</tr_wachhVal>"
      << "<tr_wachhVal species=\"Species_1\">0</tr_wachhVal>"
      << "<tr_wachhVal species=\"Species_2\">0</tr_wachhVal>"
      << "</tr_whatAdultCrownHeightHeight>"
      << "<tr_whatSaplingCrownHeightHeight>"
      << "<tr_wschhVal species=\"Species_3\">0</tr_wschhVal>"
      << "<tr_wschhVal species=\"Species_1\">0</tr_wschhVal>"
      << "<tr_wschhVal species=\"Species_2\">0</tr_wschhVal>"
      << "</tr_whatSaplingCrownHeightHeight>"
      << "<tr_canopyHeight>"
      << "<tr_chVal species=\"Species_3\">30.0</tr_chVal>"
      << "<tr_chVal species=\"Species_1\">30.0</tr_chVal>"
      << "<tr_chVal species=\"Species_2\">30.0</tr_chVal>"
      << "</tr_canopyHeight>"
      << "<tr_stdAsympCrownRad>"
      << "<tr_sacrVal species=\"Species_3\">0.108</tr_sacrVal>"
      << "<tr_sacrVal species=\"Species_1\">0.107</tr_sacrVal>"
      << "<tr_sacrVal species=\"Species_2\">0.109</tr_sacrVal>"
      << "</tr_stdAsympCrownRad>"
      << "<tr_stdCrownRadExp>"
      << "<tr_screVal species=\"Species_3\">1.0</tr_screVal>"
      << "<tr_screVal species=\"Species_1\">1.0</tr_screVal>"
      << "<tr_screVal species=\"Species_2\">1.0</tr_screVal>"
      << "</tr_stdCrownRadExp>"
      << "<tr_stdMaxCrownRad>"
      << "<tr_smcrVal species=\"Species_1\">10</tr_smcrVal>"
      << "<tr_smcrVal species=\"Species_2\">10</tr_smcrVal>"
      << "<tr_smcrVal species=\"Species_3\">10</tr_smcrVal>"
      << "</tr_stdMaxCrownRad>"
      << "<tr_stdAsympCrownHt>"
      << "<tr_sachVal species=\"Species_3\">0.49</tr_sachVal>"
      << "<tr_sachVal species=\"Species_1\">0.58</tr_sachVal>"
      << "<tr_sachVal species=\"Species_2\">0.54</tr_sachVal>"
      << "</tr_stdAsympCrownHt>"
      << "<tr_stdCrownHtExp>"
      << "<tr_scheVal species=\"Species_3\">1.0</tr_scheVal>"
      << "<tr_scheVal species=\"Species_1\">1.0</tr_scheVal>"
      << "<tr_scheVal species=\"Species_2\">1.0</tr_scheVal>"
      << "</tr_stdCrownHtExp>"
      << "<tr_conversionDiam10ToDBH>"
      << "<tr_cdtdVal species=\"Species_3\">0.75</tr_cdtdVal>"
      << "<tr_cdtdVal species=\"Species_1\">0.75</tr_cdtdVal>"
      << "<tr_cdtdVal species=\"Species_2\">0.75</tr_cdtdVal>"
      << "</tr_conversionDiam10ToDBH>"
      << "<tr_interceptDiam10ToDBH>"
      << "<tr_idtdVal species=\"Species_3\">0.0</tr_idtdVal>"
      << "<tr_idtdVal species=\"Species_1\">0.0</tr_idtdVal>"
      << "<tr_idtdVal species=\"Species_2\">0.0</tr_idtdVal>"
      << "</tr_interceptDiam10ToDBH>"
      << "<tr_slopeOfAsymHeight>"
      << "<tr_soahVal species=\"Species_3\">0.063</tr_soahVal>"
      << "<tr_soahVal species=\"Species_1\">0.062333334</tr_soahVal>"
      << "<tr_soahVal species=\"Species_2\">0.063</tr_soahVal>"
      << "</tr_slopeOfAsymHeight>"
      << "<tr_slopeOfHeight-Diam10>"
      << "<tr_sohdVal species=\"Species_3\">0.03</tr_sohdVal>"
      << "<tr_sohdVal species=\"Species_1\">0.03</tr_sohdVal>"
      << "<tr_sohdVal species=\"Species_2\">0.03</tr_sohdVal>"
      << "</tr_slopeOfHeight-Diam10>"
      << "</allometry>";
}
