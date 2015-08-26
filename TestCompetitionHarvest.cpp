//---------------------------------------------------------------------------
// TestCompetitionHarvest.cpp
//---------------------------------------------------------------------------
#include "TestCompetitionHarvest.h"
#include <gtest/gtest.h>
#include "TreePopulation.h"
#include "SimManager.h"
#include "ModelMath.h"
#include "Grid.h"
#include "PlatformFuncs.h"
#include <fstream>
#include <math.h>

#define MAX_FILE_LINE_LENGTH 1000

/////////////////////////////////////////////////////////////////////////////
// TestErrorProcessing()
/////////////////////////////////////////////////////////////////////////////
TEST(CompetitionHarvest, DoErrorProcessing) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try
  {
    p_oSimManager->ReadFile(WriteCompetitionHarvestXMLErrorFile1());
    FAIL() << "TestCompetitionHarvest error processing didn't catch error for WriteCompetitionHarvestXMLErrorFile1.";
  }
  catch (modelErr& err)
  {
    if (err.sFunction.compare("clCompetitionHarvest::RegisterTreeDataMembers") != 0)
    {
      FAIL() << "TestCompetitionHarvest error processing caught wrong error for WriteCompetitionHarvestXMLErrorFile1.";
    }
    ;
  }

  try
  {
    p_oSimManager->ReadFile(WriteCompetitionHarvestXMLErrorFile2());
    FAIL() << "TestCompetitionHarvest error processing didn't catch error for WriteCompetitionHarvestXMLErrorFile2.";
  }
  catch (modelErr& err)
  {
    if (err.sFunction.compare("clCompetitionHarvest::ReadParameterFileData") != 0)
    {
      FAIL() << "TestCompetitionHarvest error processing caught wrong error for WriteCompetitionHarvestXMLErrorFile2.";
    }
    ;
  }

  try
  {
    p_oSimManager->ReadFile(WriteCompetitionHarvestXMLErrorFile3());
    FAIL() << "TestCompetitionHarvest error processing didn't catch error for WriteCompetitionHarvestXMLErrorFile3.";
  }
  catch (modelErr& err)
  {
    if (err.sFunction.compare("clCompetitionHarvest::ReadParameterFileData") != 0)
    {
      FAIL() << "TestCompetitionHarvest error processing caught wrong error for WriteCompetitionHarvestXMLErrorFile3.";
    }
    ;
  }

  try
  {
    p_oSimManager->ReadFile(WriteCompetitionHarvestXMLErrorFile4());
    FAIL() << "TestCompetitionHarvest error processing didn't catch error for WriteCompetitionHarvestXMLErrorFile4.";
  }
  catch (modelErr& err)
  {
    if (err.sFunction.compare("clCompetitionHarvest::ReadParameterFileData") != 0)
    {
      FAIL() << "TestCompetitionHarvest error processing caught wrong error for WriteCompetitionHarvestXMLErrorFile4.";
    }
    ;
  }

  try
  {
    p_oSimManager->ReadFile(WriteCompetitionHarvestXMLErrorFile5());
    FAIL() << "TestCompetitionHarvest error processing didn't catch error for WriteCompetitionHarvestXMLErrorFile5.";
  }
  catch (modelErr& err)
  {
    if (err.sFunction.compare("clCompetitionHarvest::ReadParameterFileData") != 0)
    {
      FAIL() << "TestCompetitionHarvest error processing caught wrong error for WriteCompetitionHarvestXMLErrorFile5.";
    }
    ;
  }

  try
  {
    p_oSimManager->ReadFile(WriteCompetitionHarvestXMLErrorFile6());
    FAIL() << "TestCompetitionHarvest error processing didn't catch error for WriteCompetitionHarvestXMLErrorFile6.";
  }
  catch (modelErr& err)
  {
    if (err.sFunction.compare("clCompetitionHarvest::ReadParameterFileData") != 0)
    {
      FAIL() << "TestCompetitionHarvest error processing caught wrong error for WriteCompetitionHarvestXMLErrorFile6.";
    }
    ;
  }
  delete p_oSimManager;
}

/////////////////////////////////////////////////////////////////////////////
// DoHarvestRun1()
// Performs the first harvest run.
/////////////////////////////////////////////////////////////////////////////
TEST(CompetitionHarvest, DoHarvestRun1) {

  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    clTreePopulation * p_oPop;
    clTreeSearch *p_oAllTrees;
    clGrid *p_oResultsGrid;
    clTree *p_oTree;
    ifstream outfile;
    string sHarvestFile = "core_model_tester1.txt";
    char cTemp[MAX_FILE_LINE_LENGTH], c;
    float fTemp, fX, fY, fDbh;
    int i, iTemp, iSp, iTs,
    iDead;

    p_oSimManager->ReadFile( WriteCompetitionHarvestXMLFile1() );
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );

    //Get the results grid and verify that it's set up correctly
    p_oResultsGrid = p_oSimManager->GetGridObject("Competition Harvest Results");
    EXPECT_EQ(1, p_oResultsGrid->GetNumberXCells());
    EXPECT_EQ(1, p_oResultsGrid->GetNumberYCells());

    //Find the harvesting output file and make sure it's been set up
    ASSERT_TRUE(DoesFileExist(sHarvestFile));

    p_oPop->CreateTree(10, 10, 0, clTreePopulation::adult, 11);
    p_oPop->CreateTree(20, 20, 1, clTreePopulation::sapling, 8);
    p_oPop->CreateTree(30, 30, 2, clTreePopulation::adult, 15);
    p_oPop->CreateTree(50, 50, 0, clTreePopulation::adult, 10.5);
    p_oPop->CreateTree(53, 52, 1, clTreePopulation::adult, 15);
    p_oPop->CreateTree(59, 50, 2, clTreePopulation::adult, 25);
    p_oPop->CreateTree(50, 59, 0, clTreePopulation::adult, 30);
    p_oPop->CreateTree(55, 55, 1, clTreePopulation::adult, 45);
    p_oPop->CreateTree(30, 10, 2, clTreePopulation::sapling, 3);
    p_oPop->CreateTree(56, 56, 0, clTreePopulation::snag, 30);
    p_oPop->CreateTree(56, 56, 0, clTreePopulation::seedling, 0.2);
    p_oPop->CreateTree(52, 52, 0, clTreePopulation::sapling, 4);
    p_oPop->CreateTree(53, 53, 1, clTreePopulation::sapling, 4);
    p_oPop->CreateTree(54, 54, 2, clTreePopulation::sapling, 4);
    p_oPop->CreateTree(57, 57, 2, clTreePopulation::sapling, 4);
    p_oTree = p_oPop->CreateTree(58, 58, 1, clTreePopulation::adult, 20);
    //This tree's dead
    iDead = natural;
    p_oTree->SetValue(p_oPop->GetIntDataCode("dead",
        p_oTree->GetSpecies(), p_oTree->GetType()), iDead);

    //*********************************************
    // Timestep 1
    //*********************************************
    //Harvest
    p_oSimManager->RunSim(1);

    //Check the harvest results grid
    p_oResultsGrid->GetValueOfCell(0, 0, p_oResultsGrid->GetIntDataCode("Cut Density_0"), &iTemp);
    EXPECT_EQ(1, iTemp);
    p_oResultsGrid->GetValueOfCell(0, 0, p_oResultsGrid->GetIntDataCode("Cut Density_1"), &iTemp);
    EXPECT_EQ(3, iTemp);
    p_oResultsGrid->GetValueOfCell(0, 0, p_oResultsGrid->GetIntDataCode("Cut Density_2"), &iTemp);
    EXPECT_EQ(0, iTemp);
    p_oResultsGrid->GetValueOfCell(0, 0, p_oResultsGrid->GetFloatDataCode("Cut Basal Area_0"), &fTemp);
    EXPECT_LT(fabs(fTemp - 0.001256637), 0.0001);
    p_oResultsGrid->GetValueOfCell(0, 0, p_oResultsGrid->GetFloatDataCode("Cut Basal Area_1"), &fTemp);
    EXPECT_LT(fabs(fTemp - 0.177971224), 0.0001);
    p_oResultsGrid->GetValueOfCell(0, 0, p_oResultsGrid->GetFloatDataCode("Cut Basal Area_2"), &fTemp);
    EXPECT_EQ(0, fTemp);

    //Verify that the correct trees have been written to the harvest output file
    outfile.open( sHarvestFile.c_str() );
    //Discard the header line
    outfile.getline(cTemp, MAX_FILE_LINE_LENGTH);
    ASSERT_TRUE(!outfile.eof());
    //Tree 13
    ASSERT_TRUE(!outfile.eof());
    outfile >> fX >> fY >> iSp >> fDbh >> iTs;
    EXPECT_EQ(53.0, fX);
    EXPECT_EQ(53.0, fY);
    EXPECT_EQ(1, iSp);
    EXPECT_EQ(4.0, fDbh);
    EXPECT_EQ(1, iTs);
    //Tree 5
    outfile >> fX >> fY >> iSp >> fDbh >> iTs;
    EXPECT_EQ(53.0, fX);
    EXPECT_EQ(52.0, fY);
    EXPECT_EQ(1, iSp);
    EXPECT_EQ(15.0, fDbh);
    EXPECT_EQ(1, iTs);
    //Tree 8
    ASSERT_TRUE(!outfile.eof());
    outfile >> fX >> fY >> iSp >> fDbh >> iTs;
    EXPECT_EQ(55.0, fX);
    EXPECT_EQ(55.0, fY);
    EXPECT_EQ(1, iSp);
    EXPECT_EQ(45.0, fDbh);
    EXPECT_EQ(1, iTs);
    //Tree 12
    ASSERT_TRUE(!outfile.eof());
    outfile >> fX >> fY >> iSp >> fDbh >> iTs;
    EXPECT_EQ(52.0, fX);
    EXPECT_EQ(52.0, fY);
    EXPECT_EQ(0, iSp);
    EXPECT_EQ(4.0, fDbh);
    EXPECT_EQ(1, iTs);

    outfile >> c;
    ASSERT_TRUE(outfile.eof());
    outfile.close();

    //*********************************************
    // Timestep 2
    //*********************************************
    //No harvest. But we're adding some trees.
    //First - some snags.
    for (i = 0; i < 10; i++) {
      p_oPop->CreateTree(30.5, 30.5, 0, clTreePopulation::snag, 11);
      p_oPop->CreateTree(30.5, 30.5, 1, clTreePopulation::snag, 11);
      p_oPop->CreateTree(30.5, 30.5, 2, clTreePopulation::snag, 11);
    }
    p_oPop->CreateTree(48, 48, 0, clTreePopulation::adult, 20);
    p_oPop->CreateTree(53, 53, 1, clTreePopulation::adult, 30);
    p_oPop->CreateTree(51, 53, 2, clTreePopulation::adult, 40);
    p_oPop->CreateTree(54, 51, 0, clTreePopulation::adult, 50);

    p_oSimManager->RunSim(1);

    //Make sure we have 31 total snags
    p_oAllTrees = p_oPop->Find("all");
    iTemp = 0;
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {
      if (clTreePopulation::snag == p_oTree->GetType()) iTemp++;
      p_oTree = p_oAllTrees->NextTree();
    }
    EXPECT_EQ(31, iTemp);

    //Check the harvest results grid - should be all zeroes
    p_oResultsGrid->GetValueOfCell(0, 0, p_oResultsGrid->GetIntDataCode("Cut Density_0"), &iTemp);
    EXPECT_EQ(0, iTemp);
    p_oResultsGrid->GetValueOfCell(0, 0, p_oResultsGrid->GetIntDataCode("Cut Density_1"), &iTemp);
    EXPECT_EQ(0, iTemp);
    p_oResultsGrid->GetValueOfCell(0, 0, p_oResultsGrid->GetIntDataCode("Cut Density_2"), &iTemp);
    EXPECT_EQ(0, iTemp);
    p_oResultsGrid->GetValueOfCell(0, 0, p_oResultsGrid->GetFloatDataCode("Cut Basal Area_0"), &fTemp);
    EXPECT_EQ(0, fTemp);
    p_oResultsGrid->GetValueOfCell(0, 0, p_oResultsGrid->GetFloatDataCode("Cut Basal Area_1"), &fTemp);
    EXPECT_EQ(0, fTemp);
    p_oResultsGrid->GetValueOfCell(0, 0, p_oResultsGrid->GetFloatDataCode("Cut Basal Area_2"), &fTemp);
    EXPECT_EQ(0, fTemp);

    //Verify that nothing new has been written to the harvest file - that it's
    //still only 5 lines long (4 trees plus header)
    ifstream outfile2( sHarvestFile.c_str() );
    iTemp = 0;
    while (!outfile2.eof()) {
      outfile2.getline(cTemp, MAX_FILE_LINE_LENGTH);
      if (strlen(cTemp) > 1) iTemp++;
    }
    outfile2.close();
    EXPECT_EQ(5, iTemp);

    //*********************************************
    // Timestep 3
    //*********************************************
    p_oSimManager->RunSim(1);

    //Check the harvest results grid
    p_oResultsGrid->GetValueOfCell(0, 0, p_oResultsGrid->GetIntDataCode("Cut Density_0"), &iTemp);
    EXPECT_EQ(2, iTemp);
    p_oResultsGrid->GetValueOfCell(0, 0, p_oResultsGrid->GetIntDataCode("Cut Density_1"), &iTemp);
    EXPECT_EQ(1, iTemp);
    p_oResultsGrid->GetValueOfCell(0, 0, p_oResultsGrid->GetIntDataCode("Cut Density_2"), &iTemp);
    EXPECT_EQ(3, iTemp);
    p_oResultsGrid->GetValueOfCell(0, 0, p_oResultsGrid->GetFloatDataCode("Cut Basal Area_0"), &fTemp);
    EXPECT_LT(fabs(fTemp - 0.205008556), 0.0001);
    p_oResultsGrid->GetValueOfCell(0, 0, p_oResultsGrid->GetFloatDataCode("Cut Basal Area_1"), &fTemp);
    EXPECT_LT(fabs(fTemp - 0.070685835), 0.0001);
    p_oResultsGrid->GetValueOfCell(0, 0, p_oResultsGrid->GetFloatDataCode("Cut Basal Area_2"), &fTemp);
    EXPECT_LT(fabs(fTemp - 0.12817698), 0.0001);

    //Verify that the correct trees have been written to the harvest output file
    ifstream outfile3( sHarvestFile.c_str() );
    //Skip the header line and the first 4 trees
    outfile3.getline(cTemp, MAX_FILE_LINE_LENGTH);
    outfile3.getline(cTemp, MAX_FILE_LINE_LENGTH);
    outfile3.getline(cTemp, MAX_FILE_LINE_LENGTH);
    outfile3.getline(cTemp, MAX_FILE_LINE_LENGTH);
    outfile3.getline(cTemp, MAX_FILE_LINE_LENGTH);
    ASSERT_TRUE(!outfile3.eof());
    //Tree 21
    outfile3 >> fX >> fY >> iSp >> fDbh >> iTs;
    EXPECT_EQ(53.0, fX);
    EXPECT_EQ(53.0, fY);
    EXPECT_EQ(1, iSp);
    EXPECT_EQ(30.0, fDbh);
    EXPECT_EQ(3, iTs);
    //Tree 14
    ASSERT_TRUE(!outfile3.eof());
    outfile3 >> fX >> fY >> iSp >> fDbh >> iTs;
    EXPECT_EQ(54.0, fX);
    EXPECT_EQ(54.0, fY);
    EXPECT_EQ(2, iSp);
    EXPECT_EQ(4.0, fDbh);
    EXPECT_EQ(3, iTs);
    //Tree 22
    ASSERT_TRUE(!outfile3.eof());
    outfile3 >> fX >> fY >> iSp >> fDbh >> iTs;
    EXPECT_EQ(51.0, fX);
    EXPECT_EQ(53.0, fY);
    EXPECT_EQ(2, iSp);
    EXPECT_EQ(40.0, fDbh);
    EXPECT_EQ(3, iTs);
    //Tree 4
    ASSERT_TRUE(!outfile3.eof());
    outfile3 >> fX >> fY >> iSp >> fDbh >> iTs;
    EXPECT_EQ(50.0, fX);
    EXPECT_EQ(50.0, fY);
    EXPECT_EQ(0, iSp);
    EXPECT_EQ(10.5, fDbh);
    EXPECT_EQ(3, iTs);
    //Tree 23
    ASSERT_TRUE(!outfile3.eof());
    outfile3 >> fX >> fY >> iSp >> fDbh >> iTs;
    EXPECT_EQ(54.0, fX);
    EXPECT_EQ(51.0, fY);
    EXPECT_EQ(0, iSp);
    EXPECT_EQ(50.0, fDbh);
    EXPECT_EQ(3, iTs);
    //Tree 15
    ASSERT_TRUE(!outfile3.eof());
    outfile3 >> fX >> fY >> iSp >> fDbh >> iTs;
    EXPECT_EQ(57.0, fX);
    EXPECT_EQ(57.0, fY);
    EXPECT_EQ(2, iSp);
    EXPECT_EQ(4.0, fDbh);
    EXPECT_EQ(3, iTs);

    outfile3 >> c;
    ASSERT_TRUE(outfile3.eof());
    outfile3.close();

    //*********************************************
    // Timestep 4
    //*********************************************
    //No harvest.
    p_oSimManager->RunSim(1);

    //Check the harvest results grid - should be all zeroes
    p_oResultsGrid->GetValueOfCell(0, 0, p_oResultsGrid->GetIntDataCode("Cut Density_0"), &iTemp);
    EXPECT_EQ(0, iTemp);
    p_oResultsGrid->GetValueOfCell(0, 0, p_oResultsGrid->GetIntDataCode("Cut Density_1"), &iTemp);
    EXPECT_EQ(0, iTemp);
    p_oResultsGrid->GetValueOfCell(0, 0, p_oResultsGrid->GetIntDataCode("Cut Density_2"), &iTemp);
    EXPECT_EQ(0, iTemp);
    p_oResultsGrid->GetValueOfCell(0, 0, p_oResultsGrid->GetFloatDataCode("Cut Basal Area_0"), &fTemp);
    EXPECT_EQ(0, fTemp);
    p_oResultsGrid->GetValueOfCell(0, 0, p_oResultsGrid->GetFloatDataCode("Cut Basal Area_1"), &fTemp);
    EXPECT_EQ(0, fTemp);
    p_oResultsGrid->GetValueOfCell(0, 0, p_oResultsGrid->GetFloatDataCode("Cut Basal Area_2"), &fTemp);
    EXPECT_EQ(0, fTemp);

    //Verify that nothing new has been written to the harvest file - that it's
    //still only 11 lines long (10 trees plus header)
    ifstream outfile4( sHarvestFile.c_str() );
    iTemp = 0;
    while (!outfile4.eof()) {
      outfile4.getline(cTemp, MAX_FILE_LINE_LENGTH);
      if (strlen(cTemp) > 1) iTemp++;
    }
    outfile4.close();
    EXPECT_EQ(11, iTemp);

    //*********************************************
    // Timestep 5
    //*********************************************
    //No harvest due to insufficient basal area.
    p_oSimManager->RunSim(1);

    //Check the harvest results grid - should be all zeroes
    p_oResultsGrid->GetValueOfCell(0, 0, p_oResultsGrid->GetIntDataCode("Cut Density_0"), &iTemp);
    EXPECT_EQ(0, iTemp);
    p_oResultsGrid->GetValueOfCell(0, 0, p_oResultsGrid->GetIntDataCode("Cut Density_1"), &iTemp);
    EXPECT_EQ(0, iTemp);
    p_oResultsGrid->GetValueOfCell(0, 0, p_oResultsGrid->GetIntDataCode("Cut Density_2"), &iTemp);
    EXPECT_EQ(0, iTemp);
    p_oResultsGrid->GetValueOfCell(0, 0, p_oResultsGrid->GetFloatDataCode("Cut Basal Area_0"), &fTemp);
    EXPECT_EQ(0, fTemp);
    p_oResultsGrid->GetValueOfCell(0, 0, p_oResultsGrid->GetFloatDataCode("Cut Basal Area_1"), &fTemp);
    EXPECT_EQ(0, fTemp);
    p_oResultsGrid->GetValueOfCell(0, 0, p_oResultsGrid->GetFloatDataCode("Cut Basal Area_2"), &fTemp);
    EXPECT_EQ(0, fTemp);

    //Verify that nothing new has been written to the harvest file - that it's
    //still only 11 lines long (10 trees plus header)
    ifstream outfile5 ( sHarvestFile.c_str() );
    iTemp = 0;
    while (!outfile5.eof()) {
      outfile5.getline(cTemp, MAX_FILE_LINE_LENGTH);
      if (strlen(cTemp) > 1) iTemp++;
    }
    outfile5.close();
    EXPECT_EQ(11, iTemp);

    DeleteThisFile(sHarvestFile);





    //*****************************************************
    //Again, with no harvest file
    //*****************************************************
    p_oSimManager->ReadFile( WriteCompetitionHarvestXMLFile1a() );
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );

    //Get the results grid and verify that it's set up correctly
    p_oResultsGrid = p_oSimManager->GetGridObject("Competition Harvest Results");
    EXPECT_EQ(1, p_oResultsGrid->GetNumberXCells());
    EXPECT_EQ(1, p_oResultsGrid->GetNumberYCells());

    //Find the harvesting output file and make sure it's been set up
    ASSERT_FALSE(DoesFileExist(sHarvestFile));

    p_oPop->CreateTree(10, 10, 0, clTreePopulation::adult, 11);
    p_oPop->CreateTree(20, 20, 1, clTreePopulation::sapling, 8);
    p_oPop->CreateTree(30, 30, 2, clTreePopulation::adult, 15);
    p_oPop->CreateTree(50, 50, 0, clTreePopulation::adult, 10.5);
    p_oPop->CreateTree(53, 52, 1, clTreePopulation::adult, 15);
    p_oPop->CreateTree(59, 50, 2, clTreePopulation::adult, 25);
    p_oPop->CreateTree(50, 59, 0, clTreePopulation::adult, 30);
    p_oPop->CreateTree(55, 55, 1, clTreePopulation::adult, 45);
    p_oPop->CreateTree(30, 10, 2, clTreePopulation::sapling, 3);
    p_oPop->CreateTree(56, 56, 0, clTreePopulation::snag, 30);
    p_oPop->CreateTree(56, 56, 0, clTreePopulation::seedling, 0.2);
    p_oPop->CreateTree(52, 52, 0, clTreePopulation::sapling, 4);
    p_oPop->CreateTree(53, 53, 1, clTreePopulation::sapling, 4);
    p_oPop->CreateTree(54, 54, 2, clTreePopulation::sapling, 4);
    p_oPop->CreateTree(57, 57, 2, clTreePopulation::sapling, 4);
    p_oTree = p_oPop->CreateTree(58, 58, 1, clTreePopulation::adult, 20);
    //This tree's dead
    iDead = natural;
    p_oTree->SetValue(p_oPop->GetIntDataCode("dead",
        p_oTree->GetSpecies(), p_oTree->GetType()), iDead);

    // Timestep 1
    //Harvest
    p_oSimManager->RunSim(1);

    //Check the harvest results grid
    p_oResultsGrid->GetValueOfCell(0, 0, p_oResultsGrid->GetIntDataCode("Cut Density_0"), &iTemp);
    EXPECT_EQ(1, iTemp);
    p_oResultsGrid->GetValueOfCell(0, 0, p_oResultsGrid->GetIntDataCode("Cut Density_1"), &iTemp);
    EXPECT_EQ(3, iTemp);
    p_oResultsGrid->GetValueOfCell(0, 0, p_oResultsGrid->GetIntDataCode("Cut Density_2"), &iTemp);
    EXPECT_EQ(0, iTemp);
    p_oResultsGrid->GetValueOfCell(0, 0, p_oResultsGrid->GetFloatDataCode("Cut Basal Area_0"), &fTemp);
    EXPECT_LT(fabs(fTemp - 0.001256637), 0.0001);
    p_oResultsGrid->GetValueOfCell(0, 0, p_oResultsGrid->GetFloatDataCode("Cut Basal Area_1"), &fTemp);
    EXPECT_LT(fabs(fTemp - 0.177971224), 0.0001);
    p_oResultsGrid->GetValueOfCell(0, 0, p_oResultsGrid->GetFloatDataCode("Cut Basal Area_2"), &fTemp);
    EXPECT_EQ(0, fTemp);

    ASSERT_FALSE(DoesFileExist(sHarvestFile));

    // Timestep 2
    //No harvest. But we're adding some trees.
    //First - some snags.
    for (i = 0; i < 10; i++) {
      p_oPop->CreateTree(30.5, 30.5, 0, clTreePopulation::snag, 11);
      p_oPop->CreateTree(30.5, 30.5, 1, clTreePopulation::snag, 11);
      p_oPop->CreateTree(30.5, 30.5, 2, clTreePopulation::snag, 11);
    }
    p_oPop->CreateTree(48, 48, 0, clTreePopulation::adult, 20);
    p_oPop->CreateTree(53, 53, 1, clTreePopulation::adult, 30);
    p_oPop->CreateTree(51, 53, 2, clTreePopulation::adult, 40);
    p_oPop->CreateTree(54, 51, 0, clTreePopulation::adult, 50);

    p_oSimManager->RunSim(1);

    //Make sure we have 31 total snags
    p_oAllTrees = p_oPop->Find("all");
    iTemp = 0;
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {
      if (clTreePopulation::snag == p_oTree->GetType()) iTemp++;
      p_oTree = p_oAllTrees->NextTree();
    }
    EXPECT_EQ(31, iTemp);

    //Check the harvest results grid - should be all zeroes
    p_oResultsGrid->GetValueOfCell(0, 0, p_oResultsGrid->GetIntDataCode("Cut Density_0"), &iTemp);
    EXPECT_EQ(0, iTemp);
    p_oResultsGrid->GetValueOfCell(0, 0, p_oResultsGrid->GetIntDataCode("Cut Density_1"), &iTemp);
    EXPECT_EQ(0, iTemp);
    p_oResultsGrid->GetValueOfCell(0, 0, p_oResultsGrid->GetIntDataCode("Cut Density_2"), &iTemp);
    EXPECT_EQ(0, iTemp);
    p_oResultsGrid->GetValueOfCell(0, 0, p_oResultsGrid->GetFloatDataCode("Cut Basal Area_0"), &fTemp);
    EXPECT_EQ(0, fTemp);
    p_oResultsGrid->GetValueOfCell(0, 0, p_oResultsGrid->GetFloatDataCode("Cut Basal Area_1"), &fTemp);
    EXPECT_EQ(0, fTemp);
    p_oResultsGrid->GetValueOfCell(0, 0, p_oResultsGrid->GetFloatDataCode("Cut Basal Area_2"), &fTemp);
    EXPECT_EQ(0, fTemp);

    ASSERT_FALSE(DoesFileExist(sHarvestFile));

    // Timestep 3
    p_oSimManager->RunSim(1);

    //Check the harvest results grid
    p_oResultsGrid->GetValueOfCell(0, 0, p_oResultsGrid->GetIntDataCode("Cut Density_0"), &iTemp);
    EXPECT_EQ(2, iTemp);
    p_oResultsGrid->GetValueOfCell(0, 0, p_oResultsGrid->GetIntDataCode("Cut Density_1"), &iTemp);
    EXPECT_EQ(1, iTemp);
    p_oResultsGrid->GetValueOfCell(0, 0, p_oResultsGrid->GetIntDataCode("Cut Density_2"), &iTemp);
    EXPECT_EQ(3, iTemp);
    p_oResultsGrid->GetValueOfCell(0, 0, p_oResultsGrid->GetFloatDataCode("Cut Basal Area_0"), &fTemp);
    EXPECT_LT(fabs(fTemp - 0.205008556), 0.0001);
    p_oResultsGrid->GetValueOfCell(0, 0, p_oResultsGrid->GetFloatDataCode("Cut Basal Area_1"), &fTemp);
    EXPECT_LT(fabs(fTemp - 0.070685835), 0.0001);
    p_oResultsGrid->GetValueOfCell(0, 0, p_oResultsGrid->GetFloatDataCode("Cut Basal Area_2"), &fTemp);
    EXPECT_LT(fabs(fTemp - 0.12817698), 0.0001);

    ASSERT_FALSE(DoesFileExist(sHarvestFile));

    // Timestep 4
    //No harvest.
    p_oSimManager->RunSim(1);

    //Check the harvest results grid - should be all zeroes
    p_oResultsGrid->GetValueOfCell(0, 0, p_oResultsGrid->GetIntDataCode("Cut Density_0"), &iTemp);
    EXPECT_EQ(0, iTemp);
    p_oResultsGrid->GetValueOfCell(0, 0, p_oResultsGrid->GetIntDataCode("Cut Density_1"), &iTemp);
    EXPECT_EQ(0, iTemp);
    p_oResultsGrid->GetValueOfCell(0, 0, p_oResultsGrid->GetIntDataCode("Cut Density_2"), &iTemp);
    EXPECT_EQ(0, iTemp);
    p_oResultsGrid->GetValueOfCell(0, 0, p_oResultsGrid->GetFloatDataCode("Cut Basal Area_0"), &fTemp);
    EXPECT_EQ(0, fTemp);
    p_oResultsGrid->GetValueOfCell(0, 0, p_oResultsGrid->GetFloatDataCode("Cut Basal Area_1"), &fTemp);
    EXPECT_EQ(0, fTemp);
    p_oResultsGrid->GetValueOfCell(0, 0, p_oResultsGrid->GetFloatDataCode("Cut Basal Area_2"), &fTemp);
    EXPECT_EQ(0, fTemp);

    ASSERT_FALSE(DoesFileExist(sHarvestFile));

    // Timestep 5
    //No harvest due to insufficient basal area.
    p_oSimManager->RunSim(1);

    //Check the harvest results grid - should be all zeroes
    p_oResultsGrid->GetValueOfCell(0, 0, p_oResultsGrid->GetIntDataCode("Cut Density_0"), &iTemp);
    EXPECT_EQ(0, iTemp);
    p_oResultsGrid->GetValueOfCell(0, 0, p_oResultsGrid->GetIntDataCode("Cut Density_1"), &iTemp);
    EXPECT_EQ(0, iTemp);
    p_oResultsGrid->GetValueOfCell(0, 0, p_oResultsGrid->GetIntDataCode("Cut Density_2"), &iTemp);
    EXPECT_EQ(0, iTemp);
    p_oResultsGrid->GetValueOfCell(0, 0, p_oResultsGrid->GetFloatDataCode("Cut Basal Area_0"), &fTemp);
    EXPECT_EQ(0, fTemp);
    p_oResultsGrid->GetValueOfCell(0, 0, p_oResultsGrid->GetFloatDataCode("Cut Basal Area_1"), &fTemp);
    EXPECT_EQ(0, fTemp);
    p_oResultsGrid->GetValueOfCell(0, 0, p_oResultsGrid->GetFloatDataCode("Cut Basal Area_2"), &fTemp);
    EXPECT_EQ(0, fTemp);

    ASSERT_FALSE(DoesFileExist(sHarvestFile));

    delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

/////////////////////////////////////////////////////////////////////////////
// DoHarvestRun2()
// Performs the second harvest run.
/////////////////////////////////////////////////////////////////////////////
TEST(CompetitionHarvest, DoHarvestRun2) {

  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    clTreePopulation * p_oPop;
    clGrid *p_oResultsGrid;
    string sHarvestFile = "core_model_tester2.txt";
    char cTemp[MAX_FILE_LINE_LENGTH], c;
    float fTemp, fX, fY, fDbh;
    int i, iTemp, iSp, iTs;

    p_oSimManager->ReadFile( WriteCompetitionHarvestXMLFile2() );
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );

    //Get the results grid and verify that it's set up correctly
    p_oResultsGrid = p_oSimManager->GetGridObject("Competition Harvest Results");
    EXPECT_EQ(1, p_oResultsGrid->GetNumberXCells());
    EXPECT_EQ(1, p_oResultsGrid->GetNumberYCells());

    //Find the harvesting output file and make sure it's been set up
    ASSERT_TRUE(DoesFileExist(sHarvestFile));

    //*********************************************
    // Timestep 1
    //*********************************************
    //No trees - no harvest.
    p_oSimManager->RunSim(1);

    //Check the harvest results grid - should be all zeroes
    p_oResultsGrid->GetValueOfCell(0, 0, p_oResultsGrid->GetIntDataCode("Cut Density_0"), &iTemp);
    EXPECT_EQ(0, iTemp);
    p_oResultsGrid->GetValueOfCell(0, 0, p_oResultsGrid->GetIntDataCode("Cut Density_1"), &iTemp);
    EXPECT_EQ(0, iTemp);
    p_oResultsGrid->GetValueOfCell(0, 0, p_oResultsGrid->GetIntDataCode("Cut Density_2"), &iTemp);
    EXPECT_EQ(0, iTemp);
    p_oResultsGrid->GetValueOfCell(0, 0, p_oResultsGrid->GetIntDataCode("Cut Density_3"), &iTemp);
    EXPECT_EQ(0, iTemp);
    p_oResultsGrid->GetValueOfCell(0, 0, p_oResultsGrid->GetFloatDataCode("Cut Basal Area_0"), &fTemp);
    EXPECT_EQ(0, fTemp);
    p_oResultsGrid->GetValueOfCell(0, 0, p_oResultsGrid->GetFloatDataCode("Cut Basal Area_1"), &fTemp);
    EXPECT_EQ(0, fTemp);
    p_oResultsGrid->GetValueOfCell(0, 0, p_oResultsGrid->GetFloatDataCode("Cut Basal Area_2"), &fTemp);
    EXPECT_EQ(0, fTemp);
    p_oResultsGrid->GetValueOfCell(0, 0, p_oResultsGrid->GetFloatDataCode("Cut Basal Area_3"), &fTemp);
    EXPECT_EQ(0, fTemp);

    //*********************************************
    // Timestep 2
    //*********************************************
    //No harvest because of insufficient basal area by participating species. Add
    //some trees.
    p_oPop->CreateTree(195, 195, 0, clTreePopulation::adult, 10.5);
    p_oPop->CreateTree(198, 197, 1, clTreePopulation::adult, 15);
    p_oPop->CreateTree(4, 195, 2, clTreePopulation::adult, 25);
    p_oPop->CreateTree(195, 4, 3, clTreePopulation::adult, 30);
    p_oPop->CreateTree(0, 0, 2, clTreePopulation::adult, 45);
    p_oPop->CreateTree(197, 197, 2, clTreePopulation::adult, 33);
    p_oPop->CreateTree(198, 198, 2, clTreePopulation::adult, 21);
    p_oPop->CreateTree(199, 199, 2, clTreePopulation::sapling, 7);
    p_oPop->CreateTree(2, 2, 3, clTreePopulation::sapling, 4);
    p_oPop->CreateTree(196, 197, 0, clTreePopulation::adult, 100);

    p_oSimManager->RunSim(1);

    //Check the harvest results grid - should be all zeroes
    p_oResultsGrid->GetValueOfCell(0, 0, p_oResultsGrid->GetIntDataCode("Cut Density_0"), &iTemp);
    EXPECT_EQ(0, iTemp);
    p_oResultsGrid->GetValueOfCell(0, 0, p_oResultsGrid->GetIntDataCode("Cut Density_1"), &iTemp);
    EXPECT_EQ(0, iTemp);
    p_oResultsGrid->GetValueOfCell(0, 0, p_oResultsGrid->GetIntDataCode("Cut Density_2"), &iTemp);
    EXPECT_EQ(0, iTemp);
    p_oResultsGrid->GetValueOfCell(0, 0, p_oResultsGrid->GetIntDataCode("Cut Density_3"), &iTemp);
    EXPECT_EQ(0, iTemp);
    p_oResultsGrid->GetValueOfCell(0, 0, p_oResultsGrid->GetFloatDataCode("Cut Basal Area_0"), &fTemp);
    EXPECT_EQ(0, fTemp);
    p_oResultsGrid->GetValueOfCell(0, 0, p_oResultsGrid->GetFloatDataCode("Cut Basal Area_1"), &fTemp);
    EXPECT_EQ(0, fTemp);
    p_oResultsGrid->GetValueOfCell(0, 0, p_oResultsGrid->GetFloatDataCode("Cut Basal Area_2"), &fTemp);
    EXPECT_EQ(0, fTemp);
    p_oResultsGrid->GetValueOfCell(0, 0, p_oResultsGrid->GetFloatDataCode("Cut Basal Area_3"), &fTemp);
    EXPECT_EQ(0, fTemp);

    //*********************************************
    // Timestep 3
    //*********************************************
    //Harvest. Add some trees.
    p_oPop->CreateTree(196.5, 195.4, 0, clTreePopulation::adult, 41);
    p_oPop->CreateTree(4, 197, 1, clTreePopulation::adult, 42);
    p_oPop->CreateTree(0, 195, 3, clTreePopulation::adult, 43);
    p_oPop->CreateTree(195, 3, 0, clTreePopulation::adult, 44);
    p_oPop->CreateTree(0, 197, 1, clTreePopulation::adult, 45);
    p_oPop->CreateTree(198, 199, 3, clTreePopulation::adult, 49);

    p_oSimManager->RunSim(1);

    //Check the harvest results grid
    p_oResultsGrid->GetValueOfCell(0, 0, p_oResultsGrid->GetIntDataCode("Cut Density_0"), &iTemp);
    EXPECT_EQ(0, iTemp);
    p_oResultsGrid->GetValueOfCell(0, 0, p_oResultsGrid->GetIntDataCode("Cut Density_1"), &iTemp);
    EXPECT_EQ(1, iTemp);
    p_oResultsGrid->GetValueOfCell(0, 0, p_oResultsGrid->GetIntDataCode("Cut Density_2"), &iTemp);
    EXPECT_EQ(0, iTemp);
    p_oResultsGrid->GetValueOfCell(0, 0, p_oResultsGrid->GetIntDataCode("Cut Density_3"), &iTemp);
    EXPECT_EQ(1, iTemp);
    p_oResultsGrid->GetValueOfCell(0, 0, p_oResultsGrid->GetFloatDataCode("Cut Basal Area_0"), &fTemp);
    EXPECT_EQ(0, fTemp);
    p_oResultsGrid->GetValueOfCell(0, 0, p_oResultsGrid->GetFloatDataCode("Cut Basal Area_1"), &fTemp);
    EXPECT_LT(fabs(fTemp - 0.159043128), 0.0001);
    p_oResultsGrid->GetValueOfCell(0, 0, p_oResultsGrid->GetFloatDataCode("Cut Basal Area_2"), &fTemp);
    EXPECT_EQ(0, fTemp);
    p_oResultsGrid->GetValueOfCell(0, 0, p_oResultsGrid->GetFloatDataCode("Cut Basal Area_3"), &fTemp);
    EXPECT_LT(fabs(fTemp - 0.188574099), 0.0001);

    //Verify that the correct trees have been written to the harvest output file
    ifstream outfile( sHarvestFile.c_str() );
    //Discard the header line
    outfile.getline(cTemp, MAX_FILE_LINE_LENGTH);
    ASSERT_TRUE(!outfile.eof());
    //Tree 15
    outfile >> fX >> fY >> iSp >> fDbh >> iTs;
    EXPECT_EQ(0, fX);
    EXPECT_EQ(197, fY);
    EXPECT_EQ(1, iSp);
    EXPECT_EQ(45.0, fDbh);
    EXPECT_EQ(3, iTs);
    //Tree 16
    ASSERT_TRUE(!outfile.eof());
    outfile >> fX >> fY >> iSp >> fDbh >> iTs;
    EXPECT_EQ(198, fX);
    EXPECT_EQ(199, fY);
    EXPECT_EQ(3, iSp);
    EXPECT_EQ(49.0, fDbh);
    EXPECT_EQ(3, iTs);

    outfile >> c;
    ASSERT_TRUE(outfile.eof());
    outfile.close();

    //*********************************************
    // Timestep 4
    //*********************************************
    //Sufficient basal area for harvest but no harvest because the minimum
    //interval has not yet passed. Add some trees.
    for (i = 0; i < 10; i++) {
      p_oPop->CreateTree(4, 197, 1, clTreePopulation::adult, 42);
      p_oPop->CreateTree(0, 197, 1, clTreePopulation::adult, 45);
    }

    p_oSimManager->RunSim(1);

    //Check the harvest results grid
    p_oResultsGrid->GetValueOfCell(0, 0, p_oResultsGrid->GetIntDataCode("Cut Density_0"), &iTemp);
    EXPECT_EQ(0, iTemp);
    p_oResultsGrid->GetValueOfCell(0, 0, p_oResultsGrid->GetIntDataCode("Cut Density_1"), &iTemp);
    EXPECT_EQ(0, iTemp);
    p_oResultsGrid->GetValueOfCell(0, 0, p_oResultsGrid->GetIntDataCode("Cut Density_2"), &iTemp);
    EXPECT_EQ(0, iTemp);
    p_oResultsGrid->GetValueOfCell(0, 0, p_oResultsGrid->GetIntDataCode("Cut Density_3"), &iTemp);
    EXPECT_EQ(0, iTemp);
    p_oResultsGrid->GetValueOfCell(0, 0, p_oResultsGrid->GetFloatDataCode("Cut Basal Area_0"), &fTemp);
    EXPECT_EQ(0, fTemp);
    p_oResultsGrid->GetValueOfCell(0, 0, p_oResultsGrid->GetFloatDataCode("Cut Basal Area_1"), &fTemp);
    EXPECT_EQ(0, fTemp);
    p_oResultsGrid->GetValueOfCell(0, 0, p_oResultsGrid->GetFloatDataCode("Cut Basal Area_2"), &fTemp);
    EXPECT_EQ(0, fTemp);
    p_oResultsGrid->GetValueOfCell(0, 0, p_oResultsGrid->GetFloatDataCode("Cut Basal Area_3"), &fTemp);
    EXPECT_EQ(0, fTemp);

    //Verify that nothing new has been written to the harvest file - that it's
    //still only 3 lines long (2 trees plus header)
    ifstream outfile2( sHarvestFile.c_str() );
    iTemp = 0;
    while (!outfile2.eof()) {
      outfile2.getline(cTemp, MAX_FILE_LINE_LENGTH);
      if (strlen(cTemp) > 1) iTemp++;
    }
    outfile2.close();
    EXPECT_EQ(3, iTemp);

    DeleteThisFile(sHarvestFile);

    delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

/////////////////////////////////////////////////////////////////////////////
// DoHarvestRun3()
// Performs the third harvest run.
/////////////////////////////////////////////////////////////////////////////
TEST(CompetitionHarvest, DoHarvestRun3) {

  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    clTreePopulation * p_oPop;
    clGrid *p_oResultsGrid;
    ifstream outfile;
    string sHarvestFile = "core_model_tester3.txt";
    char cTemp[MAX_FILE_LINE_LENGTH], c;
    float fTemp, fX, fY, fDbh;
    int iTemp, iSp, iTs;

    p_oSimManager->ReadFile( WriteCompetitionHarvestXMLFile3() );
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );

    //Get the results grid and verify that it's set up correctly
    p_oResultsGrid = p_oSimManager->GetGridObject("Competition Harvest Results");
    EXPECT_EQ(1, p_oResultsGrid->GetNumberXCells());
    EXPECT_EQ(1, p_oResultsGrid->GetNumberYCells());

    //Find the harvesting output file and make sure it's been set up
    ASSERT_TRUE(DoesFileExist(sHarvestFile));

    //Create trees
    p_oPop->CreateTree(95, 95, 0, clTreePopulation::adult, 10.5);
    p_oPop->CreateTree(98, 97, 1, clTreePopulation::adult, 15);
    p_oPop->CreateTree(4, 95, 2, clTreePopulation::adult, 25);
    p_oPop->CreateTree(95, 4, 3, clTreePopulation::adult, 30);
    p_oPop->CreateTree(0, 0, 2, clTreePopulation::adult, 45);
    p_oPop->CreateTree(97, 98, 2, clTreePopulation::adult, 33);
    p_oPop->CreateTree(98, 99, 2, clTreePopulation::adult, 21);
    p_oPop->CreateTree(99, 98, 2, clTreePopulation::sapling, 7);
    p_oPop->CreateTree(97, 97, 0, clTreePopulation::sapling, 4);
    p_oPop->CreateTree(98, 98, 1, clTreePopulation::sapling, 4);
    p_oPop->CreateTree(99, 99, 0, clTreePopulation::sapling, 4);
    p_oPop->CreateTree(2, 2, 3, clTreePopulation::sapling, 4);
    p_oPop->CreateTree(96, 97, 0, clTreePopulation::adult, 100);
    p_oPop->CreateTree(96.5, 95.4, 0, clTreePopulation::adult, 41);
    p_oPop->CreateTree(4, 97, 1, clTreePopulation::adult, 42);
    p_oPop->CreateTree(0, 95, 3, clTreePopulation::adult, 43);
    p_oPop->CreateTree(95, 3, 0, clTreePopulation::adult, 44);
    p_oPop->CreateTree(0, 97, 1, clTreePopulation::adult, 45);
    p_oPop->CreateTree(98, 99, 3, clTreePopulation::adult, 49);

    //*********************************************
    // Timestep 1
    //*********************************************
    //Harvest
    p_oSimManager->RunSim(1);

    //Check the harvest results grid
    p_oResultsGrid->GetValueOfCell(0, 0, p_oResultsGrid->GetIntDataCode("Cut Density_0"), &iTemp);
    EXPECT_EQ(5, iTemp);
    p_oResultsGrid->GetValueOfCell(0, 0, p_oResultsGrid->GetIntDataCode("Cut Density_1"), &iTemp);
    EXPECT_EQ(4, iTemp);
    p_oResultsGrid->GetValueOfCell(0, 0, p_oResultsGrid->GetIntDataCode("Cut Density_2"), &iTemp);
    EXPECT_EQ(0, iTemp);
    p_oResultsGrid->GetValueOfCell(0, 0, p_oResultsGrid->GetIntDataCode("Cut Density_3"), &iTemp);
    EXPECT_EQ(0, iTemp);
    p_oResultsGrid->GetValueOfCell(0, 0, p_oResultsGrid->GetFloatDataCode("Cut Basal Area_0"), &fTemp);
    EXPECT_LT(fabs(fTemp - 0.928595884), 0.0001);
    p_oResultsGrid->GetValueOfCell(0, 0, p_oResultsGrid->GetFloatDataCode("Cut Basal Area_1"), &fTemp);
    EXPECT_LT(fabs(fTemp - 0.31651546), 0.0001);
    p_oResultsGrid->GetValueOfCell(0, 0, p_oResultsGrid->GetFloatDataCode("Cut Basal Area_2"), &fTemp);
    EXPECT_EQ(0, fTemp);
    p_oResultsGrid->GetValueOfCell(0, 0, p_oResultsGrid->GetFloatDataCode("Cut Basal Area_3"), &fTemp);
    EXPECT_EQ(0, fTemp);

    //Verify that the correct trees have been written to the harvest output file
    outfile.open( sHarvestFile.c_str() );
    //Discard the header line
    outfile.getline(cTemp, MAX_FILE_LINE_LENGTH);
    ASSERT_TRUE(!outfile.eof());
    //Tree 10
    outfile >> fX >> fY >> iSp >> fDbh >> iTs;
    EXPECT_EQ(98.0, fX);
    EXPECT_EQ(98.0, fY);
    EXPECT_EQ(1, iSp);
    EXPECT_EQ(4.0, fDbh);
    EXPECT_EQ(1, iTs);
    //Tree 2
    ASSERT_TRUE(!outfile.eof());
    outfile >> fX >> fY >> iSp >> fDbh >> iTs;
    EXPECT_EQ(98.0, fX);
    EXPECT_EQ(97.0, fY);
    EXPECT_EQ(1, iSp);
    EXPECT_EQ(15, fDbh);
    EXPECT_EQ(1, iTs);
    //Tree 18
    ASSERT_TRUE(!outfile.eof());
    outfile >> fX >> fY >> iSp >> fDbh >> iTs;
    EXPECT_EQ(0, fX);
    EXPECT_EQ(97, fY);
    EXPECT_EQ(1, iSp);
    EXPECT_EQ(45, fDbh);
    EXPECT_EQ(1, iTs);
    //Tree 9
    ASSERT_TRUE(!outfile.eof());
    outfile >> fX >> fY >> iSp >> fDbh >> iTs;
    EXPECT_EQ(97.0, fX);
    EXPECT_EQ(97.0, fY);
    EXPECT_EQ(0, iSp);
    EXPECT_EQ(4, fDbh);
    EXPECT_EQ(1, iTs);
    //Tree 11
    ASSERT_TRUE(!outfile.eof());
    outfile >> fX >> fY >> iSp >> fDbh >> iTs;
    EXPECT_EQ(99.0, fX);
    EXPECT_EQ(99.0, fY);
    EXPECT_EQ(0, iSp);
    EXPECT_EQ(4, fDbh);
    EXPECT_EQ(1, iTs);
    //Tree 1
    ASSERT_TRUE(!outfile.eof());
    outfile >> fX >> fY >> iSp >> fDbh >> iTs;
    EXPECT_EQ(95.0, fX);
    EXPECT_EQ(95.0, fY);
    EXPECT_EQ(0, iSp);
    EXPECT_EQ(10.5, fDbh);
    EXPECT_EQ(1, iTs);
    //Tree 14
    ASSERT_TRUE(!outfile.eof());
    outfile >> fX >> fY >> iSp >> fDbh >> iTs;
    EXPECT_EQ(96.5, fX);
    EXPECT_LT(fabs(95.4 - fY), 0.00001);
    EXPECT_EQ(0, iSp);
    EXPECT_EQ(41, fDbh);
    EXPECT_EQ(1, iTs);
    //Tree 13
    ASSERT_TRUE(!outfile.eof());
    outfile >> fX >> fY >> iSp >> fDbh >> iTs;
    EXPECT_EQ(96.0, fX);
    EXPECT_EQ(97.0, fY);
    EXPECT_EQ(0, iSp);
    EXPECT_EQ(100, fDbh);
    EXPECT_EQ(1, iTs);
    //Tree 15
    ASSERT_TRUE(!outfile.eof());
    outfile >> fX >> fY >> iSp >> fDbh >> iTs;
    EXPECT_EQ(4, fX);
    EXPECT_EQ(97, fY);
    EXPECT_EQ(1, iSp);
    EXPECT_EQ(42, fDbh);
    EXPECT_EQ(1, iTs);

    outfile >> c;
    ASSERT_TRUE(outfile.eof());
    outfile.close();

    DeleteThisFile(sHarvestFile);

    delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

/////////////////////////////////////////////////////////////////////////////
// WriteCompetitionHarvestXMLFile1()
/////////////////////////////////////////////////////////////////////////////
const char* WriteCompetitionHarvestXMLFile1()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  std::fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
      << "<paramFile fileCode=\"06010101\">"
      << "<plot>"
      << "<timesteps>8</timesteps>"
      << "<yearsPerTimestep>1</yearsPerTimestep>"
      << "<randomSeed>10</randomSeed>"
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
      << "</tr_speciesList>"
      << "<tr_seedDiam10Cm>0.1</tr_seedDiam10Cm>"
      << "<tr_minAdultDBH>"
      << "<tr_madVal species=\"Species_1\">0.0</tr_madVal>"
      << "<tr_madVal species=\"Species_2\">0.0</tr_madVal>"
      << "<tr_madVal species=\"Species_3\">0.0</tr_madVal>"
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
      << "<tr_soahVal species=\"Species_2\">0.0241</tr_soahVal>"
      << "<tr_soahVal species=\"Species_3\">0.0263</tr_soahVal>"
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
      << "</allometry>";

  oOut << "<behaviorList>"
      << "<behavior>"
      << "<behaviorName>CompetitionHarvest</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>1</listPosition>"
      << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_3\" type=\"Sapling\"/>"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>StochasticMortality</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>2</listPosition>"
      << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_3\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_1\" type=\"Snag\"/>"
      << "<applyTo species=\"Species_2\" type=\"Snag\"/>"
      << "<applyTo species=\"Species_3\" type=\"Snag\"/>"
      << "</behavior>"
      << "</behaviorList>";

  oOut << "<CompetitionHarvest1>"
      << "<di_compHarvMaxCrowdingRadius>"
      << "<di_chmcrVal species=\"Species_1\">10</di_chmcrVal>"
      << "<di_chmcrVal species=\"Species_2\">10</di_chmcrVal>"
      << "<di_chmcrVal species=\"Species_3\">10</di_chmcrVal>"
      << "</di_compHarvMaxCrowdingRadius>"
      << "<di_compHarvAlpha>"
      << "<di_chaVal species=\"Species_1\">2.17031683</di_chaVal>"
      << "<di_chaVal species=\"Species_2\">2.81</di_chaVal>"
      << "<di_chaVal species=\"Species_3\">1.33</di_chaVal>"
      << "</di_compHarvAlpha>"
      << "<di_compHarvBeta>"
      << "<di_chbVal species=\"Species_1\">0.69994199</di_chbVal>"
      << "<di_chbVal species=\"Species_2\">0.5</di_chbVal>"
      << "<di_chbVal species=\"Species_3\">0.09</di_chbVal>"
      << "</di_compHarvBeta>"
      << "<di_compHarvGamma>"
      << "<di_chgVal species=\"Species_1\">-0.43</di_chgVal>"
      << "<di_chgVal species=\"Species_2\">-0.36</di_chgVal>"
      << "<di_chgVal species=\"Species_3\">-0.4</di_chgVal>"
      << "</di_compHarvGamma>"
      << "<di_compHarvSpecies_1NeighborLambda>"
      << "<di_nlVal species=\"Species_1\">0.66401082</di_nlVal>"
      << "<di_nlVal species=\"Species_2\">0.71</di_nlVal>"
      << "<di_nlVal species=\"Species_3\">0.08</di_nlVal>"
      << "</di_compHarvSpecies_1NeighborLambda>"
      << "<di_compHarvSpecies_2NeighborLambda>"
      << "<di_nlVal species=\"Species_1\">0.00442797</di_nlVal>"
      << "<di_nlVal species=\"Species_2\">0.12</di_nlVal>"
      << "<di_nlVal species=\"Species_3\">0.03</di_nlVal>"
      << "</di_compHarvSpecies_2NeighborLambda>"
      << "<di_compHarvSpecies_3NeighborLambda>"
      << "<di_nlVal species=\"Species_1\">0.41812471</di_nlVal>"
      << "<di_nlVal species=\"Species_2\">0.24</di_nlVal>"
      << "<di_nlVal species=\"Species_3\">0.05</di_nlVal>"
      << "</di_compHarvSpecies_3NeighborLambda>"
      << "<di_compHarvCrowdingSlope>"
      << "<di_chcsVal species=\"Species_1\">0.698</di_chcsVal>"
      << "<di_chcsVal species=\"Species_2\">0.457</di_chcsVal>"
      << "<di_chcsVal species=\"Species_3\">0.469</di_chcsVal>"
      << "</di_compHarvCrowdingSlope>"
      << "<di_compHarvCrowdingSteepness>"
      << "<di_chcstVal species=\"Species_1\">-0.00163</di_chcstVal>"
      << "<di_chcstVal species=\"Species_2\">-0.00126</di_chcstVal>"
      << "<di_chcstVal species=\"Species_3\">-0.00163</di_chcstVal>"
      << "</di_compHarvCrowdingSteepness>"
      << "<di_compHarvProportion>"
      << "<di_chpVal species=\"Species_1\">1</di_chpVal>"
      << "<di_chpVal species=\"Species_2\">1</di_chpVal>"
      << "<di_chpVal species=\"Species_3\">1</di_chpVal>"
      << "</di_compHarvProportion>"
      << "<di_compHarvDbhDivisor>100</di_compHarvDbhDivisor>"
      << "<di_compHarvMinHarvDBH>0</di_compHarvMinHarvDBH>"
      << "<di_compHarvMaxHarvDBH>100</di_compHarvMaxHarvDBH>"
      << "<di_compHarvTypeHarvest>0</di_compHarvTypeHarvest>"
      << "<di_compHarvCutAmount>0.0406</di_compHarvCutAmount>"
      << "<di_compHarvInterval>2</di_compHarvInterval>"
      << "<di_compHarvHarvestedListFile>core_model_tester1.txt</di_compHarvHarvestedListFile>"
      << "</CompetitionHarvest1>"
      << "<StochasticMortality2>"
      << "<mo_stochasticMortRate>"
      << "<mo_smrVal species=\"Species_1\">0</mo_smrVal>"
      << "<mo_smrVal species=\"Species_2\">0</mo_smrVal>"
      << "<mo_smrVal species=\"Species_3\">0</mo_smrVal>"
      << "</mo_stochasticMortRate>"
      << "</StochasticMortality2>"
      << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteCompetitionHarvestXMLFile1a()
/////////////////////////////////////////////////////////////////////////////
const char* WriteCompetitionHarvestXMLFile1a()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  std::fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
      << "<paramFile fileCode=\"06010101\">"
      << "<plot>"
      << "<timesteps>8</timesteps>"
      << "<yearsPerTimestep>1</yearsPerTimestep>"
      << "<randomSeed>10</randomSeed>"
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
      << "</tr_speciesList>"
      << "<tr_seedDiam10Cm>0.1</tr_seedDiam10Cm>"
      << "<tr_minAdultDBH>"
      << "<tr_madVal species=\"Species_1\">0.0</tr_madVal>"
      << "<tr_madVal species=\"Species_2\">0.0</tr_madVal>"
      << "<tr_madVal species=\"Species_3\">0.0</tr_madVal>"
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
      << "<tr_soahVal species=\"Species_2\">0.0241</tr_soahVal>"
      << "<tr_soahVal species=\"Species_3\">0.0263</tr_soahVal>"
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
      << "</allometry>";

  oOut << "<behaviorList>"
      << "<behavior>"
      << "<behaviorName>CompetitionHarvest</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>1</listPosition>"
      << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_3\" type=\"Sapling\"/>"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>StochasticMortality</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>2</listPosition>"
      << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_3\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_1\" type=\"Snag\"/>"
      << "<applyTo species=\"Species_2\" type=\"Snag\"/>"
      << "<applyTo species=\"Species_3\" type=\"Snag\"/>"
      << "</behavior>"
      << "</behaviorList>";

  oOut << "<CompetitionHarvest1>"
      << "<di_compHarvMaxCrowdingRadius>"
      << "<di_chmcrVal species=\"Species_1\">10</di_chmcrVal>"
      << "<di_chmcrVal species=\"Species_2\">10</di_chmcrVal>"
      << "<di_chmcrVal species=\"Species_3\">10</di_chmcrVal>"
      << "</di_compHarvMaxCrowdingRadius>"
      << "<di_compHarvAlpha>"
      << "<di_chaVal species=\"Species_1\">2.17031683</di_chaVal>"
      << "<di_chaVal species=\"Species_2\">2.81</di_chaVal>"
      << "<di_chaVal species=\"Species_3\">1.33</di_chaVal>"
      << "</di_compHarvAlpha>"
      << "<di_compHarvBeta>"
      << "<di_chbVal species=\"Species_1\">0.69994199</di_chbVal>"
      << "<di_chbVal species=\"Species_2\">0.5</di_chbVal>"
      << "<di_chbVal species=\"Species_3\">0.09</di_chbVal>"
      << "</di_compHarvBeta>"
      << "<di_compHarvGamma>"
      << "<di_chgVal species=\"Species_1\">-0.43</di_chgVal>"
      << "<di_chgVal species=\"Species_2\">-0.36</di_chgVal>"
      << "<di_chgVal species=\"Species_3\">-0.4</di_chgVal>"
      << "</di_compHarvGamma>"
      << "<di_compHarvSpecies_1NeighborLambda>"
      << "<di_nlVal species=\"Species_1\">0.66401082</di_nlVal>"
      << "<di_nlVal species=\"Species_2\">0.71</di_nlVal>"
      << "<di_nlVal species=\"Species_3\">0.08</di_nlVal>"
      << "</di_compHarvSpecies_1NeighborLambda>"
      << "<di_compHarvSpecies_2NeighborLambda>"
      << "<di_nlVal species=\"Species_1\">0.00442797</di_nlVal>"
      << "<di_nlVal species=\"Species_2\">0.12</di_nlVal>"
      << "<di_nlVal species=\"Species_3\">0.03</di_nlVal>"
      << "</di_compHarvSpecies_2NeighborLambda>"
      << "<di_compHarvSpecies_3NeighborLambda>"
      << "<di_nlVal species=\"Species_1\">0.41812471</di_nlVal>"
      << "<di_nlVal species=\"Species_2\">0.24</di_nlVal>"
      << "<di_nlVal species=\"Species_3\">0.05</di_nlVal>"
      << "</di_compHarvSpecies_3NeighborLambda>"
      << "<di_compHarvCrowdingSlope>"
      << "<di_chcsVal species=\"Species_1\">0.698</di_chcsVal>"
      << "<di_chcsVal species=\"Species_2\">0.457</di_chcsVal>"
      << "<di_chcsVal species=\"Species_3\">0.469</di_chcsVal>"
      << "</di_compHarvCrowdingSlope>"
      << "<di_compHarvCrowdingSteepness>"
      << "<di_chcstVal species=\"Species_1\">-0.00163</di_chcstVal>"
      << "<di_chcstVal species=\"Species_2\">-0.00126</di_chcstVal>"
      << "<di_chcstVal species=\"Species_3\">-0.00163</di_chcstVal>"
      << "</di_compHarvCrowdingSteepness>"
      << "<di_compHarvProportion>"
      << "<di_chpVal species=\"Species_1\">1</di_chpVal>"
      << "<di_chpVal species=\"Species_2\">1</di_chpVal>"
      << "<di_chpVal species=\"Species_3\">1</di_chpVal>"
      << "</di_compHarvProportion>"
      << "<di_compHarvDbhDivisor>100</di_compHarvDbhDivisor>"
      << "<di_compHarvMinHarvDBH>0</di_compHarvMinHarvDBH>"
      << "<di_compHarvMaxHarvDBH>100</di_compHarvMaxHarvDBH>"
      << "<di_compHarvTypeHarvest>0</di_compHarvTypeHarvest>"
      << "<di_compHarvCutAmount>0.0406</di_compHarvCutAmount>"
      << "<di_compHarvInterval>2</di_compHarvInterval>"
      << "</CompetitionHarvest1>"
      << "<StochasticMortality2>"
      << "<mo_stochasticMortRate>"
      << "<mo_smrVal species=\"Species_1\">0</mo_smrVal>"
      << "<mo_smrVal species=\"Species_2\">0</mo_smrVal>"
      << "<mo_smrVal species=\"Species_3\">0</mo_smrVal>"
      << "</mo_stochasticMortRate>"
      << "</StochasticMortality2>"
      << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteCompetitionHarvestXMLFile2()
/////////////////////////////////////////////////////////////////////////////
const char* WriteCompetitionHarvestXMLFile2()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  std::fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
      << "<paramFile fileCode=\"06010101\">"
      << "<plot>"
      << "<timesteps>8</timesteps>"
      << "<yearsPerTimestep>1</yearsPerTimestep>"
      << "<randomSeed>10</randomSeed>"
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
      << "</allometry>";

  oOut << "<behaviorList>"
      << "<behavior>"
      << "<behaviorName>CompetitionHarvest</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>1</listPosition>"
      << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_4\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_4\" type=\"Sapling\"/>"
      << "</behavior>"
      << "</behaviorList>";

  oOut << "<CompetitionHarvest1>"
      << "<di_compHarvMaxCrowdingRadius>"
      << "<di_chmcrVal species=\"Species_1\">10</di_chmcrVal>"
      << "<di_chmcrVal species=\"Species_2\">10</di_chmcrVal>"
      << "<di_chmcrVal species=\"Species_4\">10</di_chmcrVal>"
      << "</di_compHarvMaxCrowdingRadius>"
      << "<di_compHarvAlpha>"
      << "<di_chaVal species=\"Species_1\">2.17031683</di_chaVal>"
      << "<di_chaVal species=\"Species_2\">2.81</di_chaVal>"
      << "<di_chaVal species=\"Species_3\">1.33</di_chaVal>"
      << "<di_chaVal species=\"Species_4\">2.5373318</di_chaVal>"
      << "</di_compHarvAlpha>"
      << "<di_compHarvBeta>"
      << "<di_chbVal species=\"Species_1\">0.69994199</di_chbVal>"
      << "<di_chbVal species=\"Species_2\">0.5</di_chbVal>"
      << "<di_chbVal species=\"Species_3\">0.09</di_chbVal>"
      << "<di_chbVal species=\"Species_4\">2.3097172</di_chbVal>"
      << "</di_compHarvBeta>"
      << "<di_compHarvGamma>"
      << "<di_chgVal species=\"Species_1\">-0.43</di_chgVal>"
      << "<di_chgVal species=\"Species_2\">-0.36</di_chgVal>"
      << "<di_chgVal species=\"Species_3\">-0.4</di_chgVal>"
      << "<di_chgVal species=\"Species_4\">2.3097172</di_chgVal>"
      << "</di_compHarvGamma>"
      << "<di_compHarvSpecies_1NeighborLambda>"
      << "<di_nlVal species=\"Species_1\">0.66401082</di_nlVal>"
      << "<di_nlVal species=\"Species_2\">0.71</di_nlVal>"
      << "<di_nlVal species=\"Species_3\">0.08</di_nlVal>"
      << "<di_nlVal species=\"Species_4\">0.7796396</di_nlVal>"
      << "</di_compHarvSpecies_1NeighborLambda>"
      << "<di_compHarvSpecies_2NeighborLambda>"
      << "<di_nlVal species=\"Species_1\">0.00442797</di_nlVal>"
      << "<di_nlVal species=\"Species_2\">0.12</di_nlVal>"
      << "<di_nlVal species=\"Species_3\">0.03</di_nlVal>"
      << "<di_nlVal species=\"Species_4\">0.44910568</di_nlVal>"
      << "</di_compHarvSpecies_2NeighborLambda>"
      << "<di_compHarvSpecies_4NeighborLambda>"
      << "<di_nlVal species=\"Species_1\">0.41812471</di_nlVal>"
      << "<di_nlVal species=\"Species_2\">0.24</di_nlVal>"
      << "<di_nlVal species=\"Species_3\">0.05</di_nlVal>"
      << "<di_nlVal species=\"Species_4\">0.89732885</di_nlVal>"
      << "</di_compHarvSpecies_4NeighborLambda>"
      << "<di_compHarvCrowdingSlope>"
      << "<di_chcsVal species=\"Species_1\">0.698</di_chcsVal>"
      << "<di_chcsVal species=\"Species_2\">0.457</di_chcsVal>"
      << "<di_chcsVal species=\"Species_3\">0.469</di_chcsVal>"
      << "<di_chcsVal species=\"Species_4\">0.19291385</di_chcsVal>"
      << "</di_compHarvCrowdingSlope>"
      << "<di_compHarvCrowdingSteepness>"
      << "<di_chcstVal species=\"Species_1\">-0.00163</di_chcstVal>"
      << "<di_chcstVal species=\"Species_2\">-0.00126</di_chcstVal>"
      << "<di_chcstVal species=\"Species_3\">-0.00163</di_chcstVal>"
      << "<di_chcstVal species=\"Species_4\">3.533081</di_chcstVal>"
      << "</di_compHarvCrowdingSteepness>"
      << "<di_compHarvProportion>"
      << "<di_chpVal species=\"Species_1\">1</di_chpVal>"
      << "<di_chpVal species=\"Species_2\">1</di_chpVal>"
      << "<di_chpVal species=\"Species_4\">1</di_chpVal>"
      << "</di_compHarvProportion>"
      << "<di_compHarvDbhDivisor>100</di_compHarvDbhDivisor>"
      << "<di_compHarvMinHarvDBH>20</di_compHarvMinHarvDBH>"
      << "<di_compHarvMaxHarvDBH>50</di_compHarvMaxHarvDBH>"
      << "<di_compHarvTypeHarvest>1</di_compHarvTypeHarvest>"
      << "<di_compHarvCutAmount>0.1</di_compHarvCutAmount>"
      << "<di_compHarvBAThreshold>0.2</di_compHarvBAThreshold>"
      << "<di_compHarvMinInterval>2</di_compHarvMinInterval>"
      << "<di_compHarvHarvestedListFile>core_model_tester2.txt</di_compHarvHarvestedListFile>"
      << "</CompetitionHarvest1>"
      << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteCompetitionHarvestXMLFile3()
/////////////////////////////////////////////////////////////////////////////
const char* WriteCompetitionHarvestXMLFile3()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  std::fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
      << "<paramFile fileCode=\"06010101\">"
      << "<plot>"
      << "<timesteps>8</timesteps>"
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
      << "</allometry>";

  oOut << "<behaviorList>"
      << "<behavior>"
      << "<behaviorName>CompetitionHarvest</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>1</listPosition>"
      << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_3\" type=\"Sapling\"/>"
      << "</behavior>"
      << "</behaviorList>";

  oOut << "<CompetitionHarvest1>"
      << "<di_compHarvMaxCrowdingRadius>"
      << "<di_chmcrVal species=\"Species_1\">10</di_chmcrVal>"
      << "<di_chmcrVal species=\"Species_2\">10</di_chmcrVal>"
      << "<di_chmcrVal species=\"Species_3\">10</di_chmcrVal>"
      << "</di_compHarvMaxCrowdingRadius>"
      << "<di_compHarvAlpha>"
      << "<di_chaVal species=\"Species_1\">2.17031683</di_chaVal>"
      << "<di_chaVal species=\"Species_2\">2.81</di_chaVal>"
      << "<di_chaVal species=\"Species_3\">1.33</di_chaVal>"
      << "<di_chaVal species=\"Species_4\">2.5373318</di_chaVal>"
      << "</di_compHarvAlpha>"
      << "<di_compHarvBeta>"
      << "<di_chbVal species=\"Species_1\">0.69994199</di_chbVal>"
      << "<di_chbVal species=\"Species_2\">0.5</di_chbVal>"
      << "<di_chbVal species=\"Species_3\">0.09</di_chbVal>"
      << "<di_chbVal species=\"Species_4\">2.3097172</di_chbVal>"
      << "</di_compHarvBeta>"
      << "<di_compHarvGamma>"
      << "<di_chgVal species=\"Species_1\">-0.43</di_chgVal>"
      << "<di_chgVal species=\"Species_2\">-0.36</di_chgVal>"
      << "<di_chgVal species=\"Species_3\">-0.4</di_chgVal>"
      << "<di_chgVal species=\"Species_4\">2.3097172</di_chgVal>"
      << "</di_compHarvGamma>"
      << "<di_compHarvSpecies_1NeighborLambda>"
      << "<di_nlVal species=\"Species_1\">0.66401082</di_nlVal>"
      << "<di_nlVal species=\"Species_2\">0.71</di_nlVal>"
      << "<di_nlVal species=\"Species_3\">0.08</di_nlVal>"
      << "<di_nlVal species=\"Species_4\">0.7796396</di_nlVal>"
      << "</di_compHarvSpecies_1NeighborLambda>"
      << "<di_compHarvSpecies_2NeighborLambda>"
      << "<di_nlVal species=\"Species_1\">0.00442797</di_nlVal>"
      << "<di_nlVal species=\"Species_2\">0.12</di_nlVal>"
      << "<di_nlVal species=\"Species_3\">0.03</di_nlVal>"
      << "<di_nlVal species=\"Species_4\">0.44910568</di_nlVal>"
      << "</di_compHarvSpecies_2NeighborLambda>"
      << "<di_compHarvSpecies_3NeighborLambda>"
      << "<di_nlVal species=\"Species_1\">0.41812471</di_nlVal>"
      << "<di_nlVal species=\"Species_2\">0.24</di_nlVal>"
      << "<di_nlVal species=\"Species_3\">0.05</di_nlVal>"
      << "<di_nlVal species=\"Species_4\">0.89732885</di_nlVal>"
      << "</di_compHarvSpecies_3NeighborLambda>"
      << "<di_compHarvCrowdingSlope>"
      << "<di_chcsVal species=\"Species_1\">0.698</di_chcsVal>"
      << "<di_chcsVal species=\"Species_2\">0.457</di_chcsVal>"
      << "<di_chcsVal species=\"Species_3\">0.469</di_chcsVal>"
      << "<di_chcsVal species=\"Species_4\">0.19291385</di_chcsVal>"
      << "</di_compHarvCrowdingSlope>"
      << "<di_compHarvCrowdingSteepness>"
      << "<di_chcstVal species=\"Species_1\">-0.00163</di_chcstVal>"
      << "<di_chcstVal species=\"Species_2\">-0.00126</di_chcstVal>"
      << "<di_chcstVal species=\"Species_3\">-0.00163</di_chcstVal>"
      << "<di_chcstVal species=\"Species_4\">3.533081</di_chcstVal>"
      << "</di_compHarvCrowdingSteepness>"
      << "<di_compHarvProportion>"
      << "<di_chpVal species=\"Species_1\">0.75</di_chpVal>"
      << "<di_chpVal species=\"Species_2\">0.25</di_chpVal>"
      << "<di_chpVal species=\"Species_3\">0</di_chpVal>"
      << "</di_compHarvProportion>"
      << "<di_compHarvDbhDivisor>100</di_compHarvDbhDivisor>"
      << "<di_compHarvMinHarvDBH>0</di_compHarvMinHarvDBH>"
      << "<di_compHarvMaxHarvDBH>200</di_compHarvMaxHarvDBH>"
      << "<di_compHarvTypeHarvest>2</di_compHarvTypeHarvest>"
      << "<di_compHarvCutAmount>0.5</di_compHarvCutAmount>"
      << "<di_compHarvBAThreshold>0.5</di_compHarvBAThreshold>"
      << "<di_compHarvMinInterval>1</di_compHarvMinInterval>"
      << "<di_compHarvHarvestedListFile>core_model_tester3.txt</di_compHarvHarvestedListFile>"
      << "</CompetitionHarvest1>"
      << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteCompetitionHarvestXMLErrorFile1()
/////////////////////////////////////////////////////////////////////////////
const char* WriteCompetitionHarvestXMLErrorFile1()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  std::fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  WriteCompetitionHarvestCommonErrorStuff(oOut);

  oOut << "<behaviorList>"
      << "<behavior>"
      << "<behaviorName>CompetitionHarvest</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>1</listPosition>"
      << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_1\" type=\"Seedling\"/>"
      << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
      << "</behavior>"
      << "</behaviorList>";

  oOut << "<CompetitionHarvest1>"
      << "<di_compHarvMaxCrowdingRadius>"
      << "<di_chmcrVal species=\"Species_1\">10</di_chmcrVal>"
      << "<di_chmcrVal species=\"Species_2\">10</di_chmcrVal>"
      << "</di_compHarvMaxCrowdingRadius>"
      << "<di_compHarvAlpha>"
      << "<di_chaVal species=\"Species_1\">2.17031683</di_chaVal>"
      << "<di_chaVal species=\"Species_2\">2.81</di_chaVal>"
      << "</di_compHarvAlpha>"
      << "<di_compHarvBeta>"
      << "<di_chbVal species=\"Species_1\">0.69994199</di_chbVal>"
      << "<di_chbVal species=\"Species_2\">0.5</di_chbVal>"
      << "</di_compHarvBeta>"
      << "<di_compHarvGamma>"
      << "<di_chgVal species=\"Species_1\">-0.43</di_chgVal>"
      << "<di_chgVal species=\"Species_2\">-0.36</di_chgVal>"
      << "</di_compHarvGamma>"
      << "<di_compHarvSpecies_1NeighborLambda>"
      << "<di_nlVal species=\"Species_1\">0.66401082</di_nlVal>"
      << "<di_nlVal species=\"Species_2\">0.71</di_nlVal>"
      << "</di_compHarvSpecies_1NeighborLambda>"
      << "<di_compHarvSpecies_2NeighborLambda>"
      << "<di_nlVal species=\"Species_1\">0.00442797</di_nlVal>"
      << "<di_nlVal species=\"Species_2\">0.12</di_nlVal>"
      << "</di_compHarvSpecies_2NeighborLambda>"
      << "<di_compHarvSpecies_3NeighborLambda>"
      << "<di_nlVal species=\"Species_1\">0.41812471</di_nlVal>"
      << "<di_nlVal species=\"Species_2\">0.24</di_nlVal>"
      << "</di_compHarvSpecies_3NeighborLambda>"
      << "<di_compHarvCrowdingSlope>"
      << "<di_chcsVal species=\"Species_1\">0.698</di_chcsVal>"
      << "<di_chcsVal species=\"Species_2\">0.457</di_chcsVal>"
      << "</di_compHarvCrowdingSlope>"
      << "<di_compHarvCrowdingSteepness>"
      << "<di_chcstVal species=\"Species_1\">-0.00163</di_chcstVal>"
      << "<di_chcstVal species=\"Species_2\">-0.00126</di_chcstVal>"
      << "</di_compHarvCrowdingSteepness>"
      << "<di_compHarvProportion>"
      << "<di_chpVal species=\"Species_1\">1</di_chpVal>"
      << "<di_chpVal species=\"Species_2\">1</di_chpVal>"
      << "</di_compHarvProportion>"
      << "<di_compHarvDbhDivisor>100</di_compHarvDbhDivisor>"
      << "<di_compHarvMinHarvDBH>0</di_compHarvMinHarvDBH>"
      << "<di_compHarvMaxHarvDBH>100</di_compHarvMaxHarvDBH>"
      << "<di_compHarvTypeHarvest>0</di_compHarvTypeHarvest>"
      << "<di_compHarvCutAmount>0.1625</di_compHarvCutAmount>"
      << "<di_compHarvInterval>2</di_compHarvInterval>"
      << "</CompetitionHarvest1>"
      << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteCompetitionHarvestXMLErrorFile2()
/////////////////////////////////////////////////////////////////////////////
const char* WriteCompetitionHarvestXMLErrorFile2()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  std::fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  WriteCompetitionHarvestCommonErrorStuff(oOut);

  oOut << "<behaviorList>"
      << "<behavior>"
      << "<behaviorName>CompetitionHarvest</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>1</listPosition>"
      << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
      << "</behavior>"
      << "</behaviorList>";

  oOut << "<CompetitionHarvest1>"
      << "<di_compHarvMaxCrowdingRadius>"
      << "<di_chmcrVal species=\"Species_1\">10</di_chmcrVal>"
      << "<di_chmcrVal species=\"Species_2\">10</di_chmcrVal>"
      << "</di_compHarvMaxCrowdingRadius>"
      << "<di_compHarvAlpha>"
      << "<di_chaVal species=\"Species_1\">2.17031683</di_chaVal>"
      << "<di_chaVal species=\"Species_2\">2.81</di_chaVal>"
      << "</di_compHarvAlpha>"
      << "<di_compHarvBeta>"
      << "<di_chbVal species=\"Species_1\">0.69994199</di_chbVal>"
      << "<di_chbVal species=\"Species_2\">0.5</di_chbVal>"
      << "</di_compHarvBeta>"
      << "<di_compHarvGamma>"
      << "<di_chgVal species=\"Species_1\">-0.43</di_chgVal>"
      << "<di_chgVal species=\"Species_2\">-0.36</di_chgVal>"
      << "</di_compHarvGamma>"
      << "<di_compHarvSpecies_1NeighborLambda>"
      << "<di_nlVal species=\"Species_1\">0.66401082</di_nlVal>"
      << "<di_nlVal species=\"Species_2\">0.71</di_nlVal>"
      << "</di_compHarvSpecies_1NeighborLambda>"
      << "<di_compHarvSpecies_2NeighborLambda>"
      << "<di_nlVal species=\"Species_1\">0.00442797</di_nlVal>"
      << "<di_nlVal species=\"Species_2\">0.12</di_nlVal>"
      << "</di_compHarvSpecies_2NeighborLambda>"
      << "<di_compHarvSpecies_3NeighborLambda>"
      << "<di_nlVal species=\"Species_1\">0.41812471</di_nlVal>"
      << "<di_nlVal species=\"Species_2\">0.24</di_nlVal>"
      << "</di_compHarvSpecies_3NeighborLambda>"
      << "<di_compHarvCrowdingSlope>"
      << "<di_chcsVal species=\"Species_1\">0.698</di_chcsVal>"
      << "<di_chcsVal species=\"Species_2\">0.457</di_chcsVal>"
      << "</di_compHarvCrowdingSlope>"
      << "<di_compHarvCrowdingSteepness>"
      << "<di_chcstVal species=\"Species_1\">-0.00163</di_chcstVal>"
      << "<di_chcstVal species=\"Species_2\">-0.00126</di_chcstVal>"
      << "</di_compHarvCrowdingSteepness>"
      << "<di_compHarvProportion>"
      << "<di_chpVal species=\"Species_1\">1</di_chpVal>"
      << "<di_chpVal species=\"Species_2\">1</di_chpVal>"
      << "</di_compHarvProportion>"
      << "<di_compHarvDbhDivisor>100</di_compHarvDbhDivisor>"
      << "<di_compHarvMinHarvDBH>0</di_compHarvMinHarvDBH>"
      << "<di_compHarvMaxHarvDBH>100</di_compHarvMaxHarvDBH>"
      << "<di_compHarvTypeHarvest>0</di_compHarvTypeHarvest>"
      << "<di_compHarvCutAmount>0.1625</di_compHarvCutAmount>"
      << "<di_compHarvInterval>-2</di_compHarvInterval>"
      << "</CompetitionHarvest1>"
      << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteCompetitionHarvestXMLErrorFile3()
/////////////////////////////////////////////////////////////////////////////
const char* WriteCompetitionHarvestXMLErrorFile3()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  std::fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  WriteCompetitionHarvestCommonErrorStuff(oOut);

  oOut << "<behaviorList>"
      << "<behavior>"
      << "<behaviorName>CompetitionHarvest</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>1</listPosition>"
      << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
      << "</behavior>"
      << "</behaviorList>";

  oOut << "<CompetitionHarvest1>"
      << "<di_compHarvMaxCrowdingRadius>"
      << "<di_chmcrVal species=\"Species_1\">10</di_chmcrVal>"
      << "<di_chmcrVal species=\"Species_2\">10</di_chmcrVal>"
      << "</di_compHarvMaxCrowdingRadius>"
      << "<di_compHarvAlpha>"
      << "<di_chaVal species=\"Species_1\">2.17031683</di_chaVal>"
      << "<di_chaVal species=\"Species_2\">2.81</di_chaVal>"
      << "</di_compHarvAlpha>"
      << "<di_compHarvBeta>"
      << "<di_chbVal species=\"Species_1\">0.69994199</di_chbVal>"
      << "<di_chbVal species=\"Species_2\">0.5</di_chbVal>"
      << "</di_compHarvBeta>"
      << "<di_compHarvGamma>"
      << "<di_chgVal species=\"Species_1\">-0.43</di_chgVal>"
      << "<di_chgVal species=\"Species_2\">-0.36</di_chgVal>"
      << "</di_compHarvGamma>"
      << "<di_compHarvSpecies_1NeighborLambda>"
      << "<di_nlVal species=\"Species_1\">0.66401082</di_nlVal>"
      << "<di_nlVal species=\"Species_2\">0.71</di_nlVal>"
      << "</di_compHarvSpecies_1NeighborLambda>"
      << "<di_compHarvSpecies_2NeighborLambda>"
      << "<di_nlVal species=\"Species_1\">0.00442797</di_nlVal>"
      << "<di_nlVal species=\"Species_2\">0.12</di_nlVal>"
      << "</di_compHarvSpecies_2NeighborLambda>"
      << "<di_compHarvSpecies_3NeighborLambda>"
      << "<di_nlVal species=\"Species_1\">0.41812471</di_nlVal>"
      << "<di_nlVal species=\"Species_2\">0.24</di_nlVal>"
      << "</di_compHarvSpecies_3NeighborLambda>"
      << "<di_compHarvCrowdingSlope>"
      << "<di_chcsVal species=\"Species_1\">0.698</di_chcsVal>"
      << "<di_chcsVal species=\"Species_2\">0.457</di_chcsVal>"
      << "</di_compHarvCrowdingSlope>"
      << "<di_compHarvCrowdingSteepness>"
      << "<di_chcstVal species=\"Species_1\">-0.00163</di_chcstVal>"
      << "<di_chcstVal species=\"Species_2\">-0.00126</di_chcstVal>"
      << "</di_compHarvCrowdingSteepness>"
      << "<di_compHarvProportion>"
      << "<di_chpVal species=\"Species_1\">1</di_chpVal>"
      << "<di_chpVal species=\"Species_2\">1</di_chpVal>"
      << "</di_compHarvProportion>"
      << "<di_compHarvDbhDivisor>100</di_compHarvDbhDivisor>"
      << "<di_compHarvMinHarvDBH>0</di_compHarvMinHarvDBH>"
      << "<di_compHarvMaxHarvDBH>200</di_compHarvMaxHarvDBH>"
      << "<di_compHarvTypeHarvest>2</di_compHarvTypeHarvest>"
      << "<di_compHarvCutAmount>50</di_compHarvCutAmount>"
      << "<di_compHarvBAThreshold>0.5</di_compHarvBAThreshold>"
      << "<di_compHarvMinInterval>1</di_compHarvMinInterval>"
      << "</CompetitionHarvest1>"
      << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteCompetitionHarvestXMLErrorFile4()
/////////////////////////////////////////////////////////////////////////////
const char* WriteCompetitionHarvestXMLErrorFile4()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  std::fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  WriteCompetitionHarvestCommonErrorStuff(oOut);

  oOut << "<behaviorList>"
      << "<behavior>"
      << "<behaviorName>CompetitionHarvest</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>1</listPosition>"
      << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
      << "</behavior>"
      << "</behaviorList>";

  oOut << "<CompetitionHarvest1>"
      << "<di_compHarvMaxCrowdingRadius>"
      << "<di_chmcrVal species=\"Species_1\">10</di_chmcrVal>"
      << "<di_chmcrVal species=\"Species_2\">10</di_chmcrVal>"
      << "</di_compHarvMaxCrowdingRadius>"
      << "<di_compHarvAlpha>"
      << "<di_chaVal species=\"Species_1\">2.17031683</di_chaVal>"
      << "<di_chaVal species=\"Species_2\">2.81</di_chaVal>"
      << "</di_compHarvAlpha>"
      << "<di_compHarvBeta>"
      << "<di_chbVal species=\"Species_1\">0.69994199</di_chbVal>"
      << "<di_chbVal species=\"Species_2\">0.5</di_chbVal>"
      << "</di_compHarvBeta>"
      << "<di_compHarvGamma>"
      << "<di_chgVal species=\"Species_1\">-0.43</di_chgVal>"
      << "<di_chgVal species=\"Species_2\">-0.36</di_chgVal>"
      << "</di_compHarvGamma>"
      << "<di_compHarvSpecies_1NeighborLambda>"
      << "<di_nlVal species=\"Species_1\">0.66401082</di_nlVal>"
      << "<di_nlVal species=\"Species_2\">0.71</di_nlVal>"
      << "</di_compHarvSpecies_1NeighborLambda>"
      << "<di_compHarvSpecies_2NeighborLambda>"
      << "<di_nlVal species=\"Species_1\">0.00442797</di_nlVal>"
      << "<di_nlVal species=\"Species_2\">0.12</di_nlVal>"
      << "</di_compHarvSpecies_2NeighborLambda>"
      << "<di_compHarvSpecies_3NeighborLambda>"
      << "<di_nlVal species=\"Species_1\">0.41812471</di_nlVal>"
      << "<di_nlVal species=\"Species_2\">0.24</di_nlVal>"
      << "</di_compHarvSpecies_3NeighborLambda>"
      << "<di_compHarvCrowdingSlope>"
      << "<di_chcsVal species=\"Species_1\">0.698</di_chcsVal>"
      << "<di_chcsVal species=\"Species_2\">0.457</di_chcsVal>"
      << "</di_compHarvCrowdingSlope>"
      << "<di_compHarvCrowdingSteepness>"
      << "<di_chcstVal species=\"Species_1\">-0.00163</di_chcstVal>"
      << "<di_chcstVal species=\"Species_2\">-0.00126</di_chcstVal>"
      << "</di_compHarvCrowdingSteepness>"
      << "<di_compHarvProportion>"
      << "<di_chpVal species=\"Species_1\">0.6</di_chpVal>"
      << "<di_chpVal species=\"Species_2\">0.5</di_chpVal>"
      << "</di_compHarvProportion>"
      << "<di_compHarvDbhDivisor>100</di_compHarvDbhDivisor>"
      << "<di_compHarvMinHarvDBH>0</di_compHarvMinHarvDBH>"
      << "<di_compHarvMaxHarvDBH>100</di_compHarvMaxHarvDBH>"
      << "<di_compHarvTypeHarvest>0</di_compHarvTypeHarvest>"
      << "<di_compHarvCutAmount>0.1625</di_compHarvCutAmount>"
      << "<di_compHarvInterval>2</di_compHarvInterval>"
      << "</CompetitionHarvest1>"
      << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteCompetitionHarvestXMLErrorFile5()
/////////////////////////////////////////////////////////////////////////////
const char* WriteCompetitionHarvestXMLErrorFile5()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  std::fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  WriteCompetitionHarvestCommonErrorStuff(oOut);

  oOut << "<behaviorList>"
      << "<behavior>"
      << "<behaviorName>CompetitionHarvest</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>1</listPosition>"
      << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
      << "</behavior>"
      << "</behaviorList>";

  oOut << "<CompetitionHarvest1>"
      << "<di_compHarvMaxCrowdingRadius>"
      << "<di_chmcrVal species=\"Species_1\">10</di_chmcrVal>"
      << "<di_chmcrVal species=\"Species_2\">10</di_chmcrVal>"
      << "</di_compHarvMaxCrowdingRadius>"
      << "<di_compHarvAlpha>"
      << "<di_chaVal species=\"Species_1\">2.17031683</di_chaVal>"
      << "<di_chaVal species=\"Species_2\">2.81</di_chaVal>"
      << "</di_compHarvAlpha>"
      << "<di_compHarvBeta>"
      << "<di_chbVal species=\"Species_1\">0.69994199</di_chbVal>"
      << "<di_chbVal species=\"Species_2\">0.5</di_chbVal>"
      << "</di_compHarvBeta>"
      << "<di_compHarvGamma>"
      << "<di_chgVal species=\"Species_1\">-0.43</di_chgVal>"
      << "<di_chgVal species=\"Species_2\">-0.36</di_chgVal>"
      << "</di_compHarvGamma>"
      << "<di_compHarvSpecies_1NeighborLambda>"
      << "<di_nlVal species=\"Species_1\">0.66401082</di_nlVal>"
      << "<di_nlVal species=\"Species_2\">0.71</di_nlVal>"
      << "</di_compHarvSpecies_1NeighborLambda>"
      << "<di_compHarvSpecies_2NeighborLambda>"
      << "<di_nlVal species=\"Species_1\">0.00442797</di_nlVal>"
      << "<di_nlVal species=\"Species_2\">0.12</di_nlVal>"
      << "</di_compHarvSpecies_2NeighborLambda>"
      << "<di_compHarvSpecies_3NeighborLambda>"
      << "<di_nlVal species=\"Species_1\">0.41812471</di_nlVal>"
      << "<di_nlVal species=\"Species_2\">0.24</di_nlVal>"
      << "</di_compHarvSpecies_3NeighborLambda>"
      << "<di_compHarvCrowdingSlope>"
      << "<di_chcsVal species=\"Species_1\">0.698</di_chcsVal>"
      << "<di_chcsVal species=\"Species_2\">0.457</di_chcsVal>"
      << "</di_compHarvCrowdingSlope>"
      << "<di_compHarvCrowdingSteepness>"
      << "<di_chcstVal species=\"Species_1\">-0.00163</di_chcstVal>"
      << "<di_chcstVal species=\"Species_2\">-0.00126</di_chcstVal>"
      << "</di_compHarvCrowdingSteepness>"
      << "<di_compHarvProportion>"
      << "<di_chpVal species=\"Species_1\">1</di_chpVal>"
      << "<di_chpVal species=\"Species_2\">1</di_chpVal>"
      << "</di_compHarvProportion>"
      << "<di_compHarvDbhDivisor>100</di_compHarvDbhDivisor>"
      << "<di_compHarvMinHarvDBH>0</di_compHarvMinHarvDBH>"
      << "<di_compHarvMaxHarvDBH>100</di_compHarvMaxHarvDBH>"
      << "<di_compHarvTypeHarvest>1</di_compHarvTypeHarvest>"
      << "<di_compHarvCutAmount>0.1625</di_compHarvCutAmount>"
      << "<di_compHarvBAThreshold>0.2</di_compHarvBAThreshold>"
      << "<di_compHarvMinInterval>0</di_compHarvMinInterval>"
      << "</CompetitionHarvest1>"
      << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteCompetitionHarvestXMLErrorFile6()
/////////////////////////////////////////////////////////////////////////////
const char* WriteCompetitionHarvestXMLErrorFile6()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  std::fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  WriteCompetitionHarvestCommonErrorStuff(oOut);

  oOut << "<behaviorList>"
      << "<behavior>"
      << "<behaviorName>CompetitionHarvest</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>1</listPosition>"
      << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
      << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
      << "</behavior>"
      << "</behaviorList>";

  oOut << "<CompetitionHarvest1>"
      << "<di_compHarvMaxCrowdingRadius>"
      << "<di_chmcrVal species=\"Species_1\">-10</di_chmcrVal>"
      << "<di_chmcrVal species=\"Species_2\">10</di_chmcrVal>"
      << "</di_compHarvMaxCrowdingRadius>"
      << "<di_compHarvAlpha>"
      << "<di_chaVal species=\"Species_1\">2.17031683</di_chaVal>"
      << "<di_chaVal species=\"Species_2\">2.81</di_chaVal>"
      << "</di_compHarvAlpha>"
      << "<di_compHarvBeta>"
      << "<di_chbVal species=\"Species_1\">0.69994199</di_chbVal>"
      << "<di_chbVal species=\"Species_2\">0.5</di_chbVal>"
      << "</di_compHarvBeta>"
      << "<di_compHarvGamma>"
      << "<di_chgVal species=\"Species_1\">-0.43</di_chgVal>"
      << "<di_chgVal species=\"Species_2\">-0.36</di_chgVal>"
      << "</di_compHarvGamma>"
      << "<di_compHarvSpecies_1NeighborLambda>"
      << "<di_nlVal species=\"Species_1\">0.66401082</di_nlVal>"
      << "<di_nlVal species=\"Species_2\">0.71</di_nlVal>"
      << "</di_compHarvSpecies_1NeighborLambda>"
      << "<di_compHarvSpecies_2NeighborLambda>"
      << "<di_nlVal species=\"Species_1\">0.00442797</di_nlVal>"
      << "<di_nlVal species=\"Species_2\">0.12</di_nlVal>"
      << "</di_compHarvSpecies_2NeighborLambda>"
      << "<di_compHarvSpecies_3NeighborLambda>"
      << "<di_nlVal species=\"Species_1\">0.41812471</di_nlVal>"
      << "<di_nlVal species=\"Species_2\">0.24</di_nlVal>"
      << "</di_compHarvSpecies_3NeighborLambda>"
      << "<di_compHarvCrowdingSlope>"
      << "<di_chcsVal species=\"Species_1\">0.698</di_chcsVal>"
      << "<di_chcsVal species=\"Species_2\">0.457</di_chcsVal>"
      << "</di_compHarvCrowdingSlope>"
      << "<di_compHarvCrowdingSteepness>"
      << "<di_chcstVal species=\"Species_1\">-0.00163</di_chcstVal>"
      << "<di_chcstVal species=\"Species_2\">-0.00126</di_chcstVal>"
      << "</di_compHarvCrowdingSteepness>"
      << "<di_compHarvProportion>"
      << "<di_chpVal species=\"Species_1\">1</di_chpVal>"
      << "<di_chpVal species=\"Species_2\">1</di_chpVal>"
      << "</di_compHarvProportion>"
      << "<di_compHarvDbhDivisor>100</di_compHarvDbhDivisor>"
      << "<di_compHarvMinHarvDBH>0</di_compHarvMinHarvDBH>"
      << "<di_compHarvMaxHarvDBH>100</di_compHarvMaxHarvDBH>"
      << "<di_compHarvTypeHarvest>0</di_compHarvTypeHarvest>"
      << "<di_compHarvCutAmount>0.1625</di_compHarvCutAmount>"
      << "<di_compHarvInterval>2</di_compHarvInterval>"
      << "</CompetitionHarvest1>"
      << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteCompetitionHarvestCommonErrorStuff()
/////////////////////////////////////////////////////////////////////////////
void WriteCompetitionHarvestCommonErrorStuff(std::fstream &oOut) {

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
      << "<paramFile fileCode=\"06010101\">"
      << "<plot>"
      << "<timesteps>8</timesteps>"
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
      << "<tr_madVal species=\"Species_1\">0.0</tr_madVal>"
      << "<tr_madVal species=\"Species_2\">0.0</tr_madVal>"
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
      << "<tr_soahVal species=\"Species_2\">0.0241</tr_soahVal>"
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
