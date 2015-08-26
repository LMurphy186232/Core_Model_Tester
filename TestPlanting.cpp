//---------------------------------------------------------------------------
// TestPlanting.cpp
//---------------------------------------------------------------------------
#include "TestPlanting.h"
#include <gtest/gtest.h>
#include "TreePopulation.h"
#include "SimManager.h"
#include <fstream>
#include <math.h>

/////////////////////////////////////////////////////////////////////////////
// DoPlantingRun1()
// Do the first planting run. WritePlantingXMLFile1() is used to do the run. The
// characteristics of this run are:
//
// -- Timestep 1
// -- Species 3, 4, 5
// -- Spacing Type - Random
// -- Density - 200/ha
// -- Grids - whole plot
// -- Amount - 33.3% for each species
// -- Seedling diam10 - default
/////////////////////////////////////////////////////////////////////////////
TEST(Planting, DoPlantingRun1) {
  clTreePopulation * p_oPop;
  clTreeSearch *p_oAllTrees;
  clTree *p_oTree;
  float fTemp;
  int iNumSpecies, i, iTemp;
  int *p_iTreeCount;
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    p_oSimManager->ReadFile( WritePlantingXMLFile1() );
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );
    iNumSpecies = p_oPop->GetNumberOfSpecies();
    p_iTreeCount = new int[iNumSpecies];

    //Make sure there are no existing trees
    p_oAllTrees = p_oPop->Find("all");
    EXPECT_EQ(NULL, p_oAllTrees->NextTree());

    //*********************************************
    // Timestep 1
    //*********************************************
    //Run the first timestep
    p_oSimManager->RunSim(1);

    for (i = 0; i < iNumSpecies; i++)
      p_iTreeCount[i] = 0;

    //Count the trees
    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {

      EXPECT_EQ(clTreePopulation::seedling, p_oTree->GetType());

      //Make sure the tree is of the right species
      iTemp = p_oTree->GetSpecies();
      EXPECT_TRUE(3 == iTemp || 4 == iTemp || 5 == iTemp);

      //Verify that the diameter is close to 0.1
      p_oTree->GetValue(p_oPop->GetDiam10Code(p_oTree->GetSpecies(), p_oTree->GetType()), &fTemp);

      ASSERT_TRUE(fabs(fTemp - 0.1)/0.1 <= 0.05);

      p_iTreeCount[p_oTree->GetSpecies()]++;

      p_oTree = p_oAllTrees->NextTree();
    }

    //Total up all the trees and verify that it's 800
    iTemp = 0;
    for (i = 0; i < iNumSpecies; i++)
      iTemp += p_iTreeCount[i];

    EXPECT_EQ(800, iTemp);

    //Verify that there are approximately 267 trees of each species
    EXPECT_LT(fabs(267 - p_iTreeCount[3])/267, 0.1);
    EXPECT_LT(fabs(267 - p_iTreeCount[4])/267, 0.1);
    EXPECT_LT(fabs(267 - p_iTreeCount[5])/267, 0.1);

    //*********************************************
    // Timestep 2
    //*********************************************
    p_oSimManager->RunSim(1);

    //Verify that there are still the same number of trees
    iTemp = 0;
    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {

      iTemp++;

      p_oTree = p_oAllTrees->NextTree();
    }
    EXPECT_EQ(800, iTemp);
    delete[] p_iTreeCount;
    delete p_oSimManager;
  } catch (modelErr &e) {
    delete[] p_iTreeCount;
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

/////////////////////////////////////////////////////////////////////////////
// DoPlantingRun2()
// Do the second planting run. WritePlantingXMLFile2() is used to do the run. The
// characteristics of this run are:
//
// -- Timestep 2
// -- Species All
// -- Spacing Type - Gridded
// -- Density - 2 m
// -- Grids - whole plot
// -- Amount
//
// -- Sp 0 - 5%
// -- Sp 1 - 10%
// -- Sp 2 - 15%
// -- Sp 3 - 30%
// -- Sp 4 - 1%
// -- Sp 5 - 10%
// -- Sp 6 - 7%
// -- Sp 7 - 8%
// -- Sp 8 - 4%
//
// -- Seedling diam10
//
// -- Sp 0 - 0.1
// -- Sp 1 - 0.2
// -- Sp 2 - 0.3
// -- Sp 3 - 0.4
// -- Sp 4 - 0.5
// -- Sp 5 - 0.6
// -- Sp 6 - 0.7
// -- Sp 7 - 0.8
// -- Sp 8 - 0.9
/////////////////////////////////////////////////////////////////////////////
TEST(Planting, DoPlantingRun2) {
  clTreePopulation * p_oPop;
  clTreeSearch *p_oAllTrees;
  clTree *p_oTree;
  float fTemp, fDiam10, fX, fY;
  int iNumSpecies, i, iTemp;
  int *p_iTreeCount;
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {

    p_oSimManager->ReadFile( WritePlantingXMLFile2() );
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );
    iNumSpecies = p_oPop->GetNumberOfSpecies();
    p_iTreeCount = new int[iNumSpecies];

    //Make sure there are no existing trees
    p_oAllTrees = p_oPop->Find("all");
    EXPECT_EQ(NULL, p_oAllTrees->NextTree());

    //*********************************************
    // Timestep 1
    //*********************************************
    //Run the first timestep
    p_oSimManager->RunSim(1);

    //Make sure there are no trees
    p_oAllTrees = p_oPop->Find("all");
    EXPECT_EQ(NULL, p_oAllTrees->NextTree());

    //*********************************************
    // Timestep 2
    //*********************************************
    //Run the next timestep
    p_oSimManager->RunSim(1);

    for (i = 0; i < iNumSpecies; i++)
      p_iTreeCount[i] = 0;

    //Count the trees
    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {

      EXPECT_EQ(clTreePopulation::seedling, p_oTree->GetType());

      //Verify that the diameter is close to 0.x for each species
      p_oTree->GetValue(p_oPop->GetDiam10Code(p_oTree->GetSpecies(), p_oTree->GetType()), &fDiam10);
      iTemp = p_oTree->GetSpecies();
      fTemp = (iTemp * 0.1) + 0.1;
      EXPECT_LT(fabs(fTemp - fDiam10)/fTemp, 0.02);

      //Verify the gridded nature
      p_oTree->GetValue(p_oPop->GetXCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fX);
      p_oTree->GetValue(p_oPop->GetYCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fY);
      EXPECT_LT(((fX-1) / 2) - (floor((fX-1) / 2)), 0.01);
      EXPECT_LT(((fY-1) / 2) - (floor((fY-1) / 2)), 0.01);

      p_iTreeCount[p_oTree->GetSpecies()]++;

      p_oTree = p_oAllTrees->NextTree();
    }

    //Total up all the trees and verify that it's 10000
    iTemp = 0;
    for (i = 0; i < iNumSpecies; i++)
      iTemp += p_iTreeCount[i];

    EXPECT_EQ(10000, iTemp);

    //Verify that there are approximately the right number of trees of each species
    EXPECT_LT(fabs(500 - p_iTreeCount[0])/500, 0.1);
    EXPECT_LT(fabs(1000 - p_iTreeCount[1])/1000, 0.1);
    EXPECT_LT(fabs(1500 - p_iTreeCount[2])/1500, 0.1);
    EXPECT_LT(fabs(3000 - p_iTreeCount[3])/3000, 0.1);
    EXPECT_LT(fabs(100 - p_iTreeCount[4])/100, 0.25); //more latitute - smaller number
    EXPECT_LT(fabs(1000 - p_iTreeCount[5])/1000, 0.1);
    EXPECT_LT(fabs(700 - p_iTreeCount[6])/700, 0.1);
    EXPECT_LT(fabs(800 - p_iTreeCount[7])/800, 0.1);
    EXPECT_LT(fabs(1400 - p_iTreeCount[8])/1400, 0.1);

    //*********************************************
    // Timestep 3
    //*********************************************
    p_oSimManager->RunSim(1);

    //Verify that there are still the same number of trees
    iTemp = 0;
    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {

      iTemp++;

      p_oTree = p_oAllTrees->NextTree();
    }
    EXPECT_EQ(10000, iTemp);

    delete[] p_iTreeCount;
    delete p_oSimManager;
  } catch (modelErr &e) {
    delete[] p_iTreeCount;
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

/////////////////////////////////////////////////////////////////////////////
// DoPlantingRun3()
// Do the third planting run. WritePlantingXMLFile3() is used to do the run. The
// characteristics of this run are:
// Planting event 1:
//
// -- Timestep 1
// -- Species 0, 1, 2
// -- Spacing Type - Random
// -- Density - 150/ha
// -- Grids - 0,0-2-24; 5,0-5,24
// -- Amount
//
// -- Sp 0 - 25%
// -- Sp 1 - 35%
// -- Sp 2 - 40%
//
// -- Seedling diam10
//
// -- Sp 0 - 0.1
// -- Sp 1 - 0.2
// -- Sp 2 - 0.3
//
//
// Planting event 2:
//
// -- Timestep 1
// -- Species 7, 8
// -- Spacing Type - Gridded
// -- Spacing - 3 m
// -- Grids - 0,0 - 24,2; 6,5-11,10
// -- Amount
//
// -- Sp 7 - 40%
// -- Sp 8 - 60%
//
// -- Seedling diam10
//
// -- Sp 7 - 0.7
// -- Sp 8 - 0.8
/////////////////////////////////////////////////////////////////////////////
TEST(Planting, DoPlantingRun3) {
  clTreePopulation * p_oPop;
  clTreeSearch *p_oAllTrees;
  clTree *p_oTree;
  float fTemp, fDiam10, fX, fY;
  int iNumSpecies, i, iTemp;
  int *p_iTreeCount;
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {

    p_oSimManager->ReadFile( WritePlantingXMLFile3() );
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );
    iNumSpecies = p_oPop->GetNumberOfSpecies();
    p_iTreeCount = new int[iNumSpecies];

    //Make sure there are no existing trees
    p_oAllTrees = p_oPop->Find("all");
    EXPECT_EQ(NULL, p_oAllTrees->NextTree());

    //*********************************************
    // Timestep 1
    //*********************************************
    //Run the first timestep
    p_oSimManager->RunSim(1);

    for (i = 0; i < iNumSpecies; i++)
      p_iTreeCount[i] = 0;

    //Count the trees
    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {

      EXPECT_EQ(clTreePopulation::seedling, p_oTree->GetType());

      //Verify the species
      iTemp = p_oTree->GetSpecies();
      EXPECT_TRUE(0 == iTemp || 1 == iTemp || 2 == iTemp || 7 == iTemp || 8 == iTemp);

      //Verify that the diameter is close to 0.x for each species
      p_oTree->GetValue(p_oPop->GetDiam10Code(p_oTree->GetSpecies(), p_oTree->GetType()), &fDiam10);
      fTemp = (iTemp * 0.1) + 0.1;
      EXPECT_LT(fabs(fTemp - fDiam10)/fTemp, 0.02);

      //Verify that the trees are in the proper grids
      if (0 == iTemp || 1 == iTemp || 2 == iTemp) {
        p_oTree->GetValue(p_oPop->GetXCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fX);
        p_oTree->GetValue(p_oPop->GetYCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fY);
        EXPECT_TRUE(fX < 24 || (fX >= 40 && fX < 48));
      } else if (7 == iTemp || 8 == iTemp) {
        p_oTree->GetValue(p_oPop->GetXCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fX);
        p_oTree->GetValue(p_oPop->GetYCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fY);
        EXPECT_TRUE(fY < 24 || (fX >= 48 && fX < 96 && fY >= 40 && fY < 88));
        if (fY < 24) {
          EXPECT_LT(((fX-floor(fX/8))-1 / 3) - (floor((fX-floor(fX/8))-1 / 3)), 0.01);
          EXPECT_LT(((fY-floor(fY/8))-1 / 3) - (floor((fY-floor(fY/8))-1 / 3)), 0.01);
        }
      } else {
        FAIL() << "Test set up wrong.";
      }

      p_iTreeCount[p_oTree->GetSpecies()]++;

      p_oTree = p_oAllTrees->NextTree();
    }

    //Verify that the number of trees is right
    EXPECT_LT(fabs(24 - p_iTreeCount[0])/24, 0.38); //more leeway 'cause the numbers are smaller
    EXPECT_LT(fabs(33.6 - p_iTreeCount[1])/33.6, 0.35); //more leeway 'cause the numbers are smaller
    EXPECT_LT(fabs(38.4 - p_iTreeCount[2])/38.4, 0.25); //more leeway 'cause the numbers are smaller
    EXPECT_LT(fabs(400 - p_iTreeCount[7])/400, 0.1);
    EXPECT_LT(fabs(599 - p_iTreeCount[8])/599, 0.1);

    //*********************************************
    // Timestep 2 & 3
    //*********************************************
    p_oSimManager->RunSim(2);

    //Verify that there are still the same number of trees
    iTemp = 0;
    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {

      iTemp++;

      p_oTree = p_oAllTrees->NextTree();
    }
    EXPECT_LT(fabs(1095 - iTemp)/1095, 0.05);
    delete[] p_iTreeCount;
    delete p_oSimManager;
  } catch (modelErr &e) {
    delete[] p_iTreeCount;
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

/////////////////////////////////////////////////////////////////////////////
// DoPlantingRun4()
// Do the fourth planting run. WritePlantingXMLFile4() is used to do the run. The
// characteristics of this run are:
// Planting event 1:
//
// -- Timestep 2
// -- Species - All
// -- Spacing Type - Random
// -- Density - 156.25/ha
// -- Grids - 24, 24
// -- Amount - 11.1% for each species
// -- Seedling diam10 - default
//
// Planting event 2:
//
// -- Timestep 3
// -- Species - All
// -- Spacing Type - Gridded
// -- Spacing - 2 m
// -- Grids - 23, 23
// -- Amount - 11.1% for each species
// -- Seedling diam10 - default
/////////////////////////////////////////////////////////////////////////////
TEST(Planting, DoPlantingRun4) {

  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    clTreePopulation * p_oPop;
    clTreeSearch *p_oAllTrees;
    clTree *p_oTree;
    float fX, fY;
    int iNumTrees;

    p_oSimManager->ReadFile( WritePlantingXMLFile4() );
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );

    //Make sure there are no existing trees
    p_oAllTrees = p_oPop->Find("all");
    EXPECT_EQ(NULL, p_oAllTrees->NextTree());

    //*********************************************
    // Timestep 1
    //*********************************************
    //Run the first timestep
    p_oSimManager->RunSim(1);

    p_oAllTrees = p_oPop->Find("all");
    EXPECT_EQ(NULL, p_oAllTrees->NextTree());

    //*********************************************
    // Timestep 2
    //*********************************************
    //Run the next timestep
    p_oSimManager->RunSim(1);

    //Count the trees
    iNumTrees = 0;
    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {

      EXPECT_EQ(clTreePopulation::seedling, p_oTree->GetType());

      //Verify that the new trees are in the proper grid
      p_oTree->GetValue(p_oPop->GetXCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fX);
      p_oTree->GetValue(p_oPop->GetYCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fY);
      EXPECT_GT(fX, 192); EXPECT_GT(fY, 192);

      iNumTrees++;

      p_oTree = p_oAllTrees->NextTree();
    }

    //Verify that the number of trees is right
    EXPECT_EQ(9, iNumTrees);

    //*********************************************
    // Timestep 3
    //*********************************************
    p_oSimManager->RunSim(1);

    //Verify the new trees
    iNumTrees = 0;
    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {

      //Verify that the new trees are in the proper grid
      p_oTree->GetValue(p_oPop->GetXCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fX);
      p_oTree->GetValue(p_oPop->GetYCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fY);
      if (fX >= 184 && fX < 192 && fY >= 184 && fY < 192) {
        iNumTrees++;
        EXPECT_LT(((fX-185) / 2) - (floor((fX-185) / 2)), 0.01);
        EXPECT_LT(((fY-185) / 2) - (floor((fY-185) / 2)), 0.01);
      }

      p_oTree = p_oAllTrees->NextTree();
    }
    //Verify that the number of trees is right
    EXPECT_EQ(16, iNumTrees);
    delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

/////////////////////////////////////////////////////////////////////////////
// DoPlantingRun5()
// Do the fifth planting run. This makes sure that random plantings happen
// correctly when grid cells do not divide evenly into the plot.
/////////////////////////////////////////////////////////////////////////////
TEST(Planting, DoPlantingRun5) {

  clTreePopulation * p_oPop;
  clTreeSearch *p_oAllTrees;
  clTree *p_oTree;
  float fTemp;
  int iNumSpecies, i, iTemp;
  int *p_iTreeCount;

  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    p_oSimManager->ReadFile( WritePlantingXMLFile5() );
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );
    iNumSpecies = p_oPop->GetNumberOfSpecies();
    p_iTreeCount = new int[iNumSpecies];

    //Make sure there are no existing trees
    p_oAllTrees = p_oPop->Find("all");
    EXPECT_EQ(NULL, p_oAllTrees->NextTree());

    //*********************************************
    // Timestep 1
    //*********************************************
    //Run the first timestep
    p_oSimManager->RunSim(1);

    for (i = 0; i < iNumSpecies; i++)
      p_iTreeCount[i] = 0;

    //Count the trees
    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {

      EXPECT_EQ(clTreePopulation::seedling, p_oTree->GetType());

      //Make sure the tree is of the right species
      iTemp = p_oTree->GetSpecies();
      EXPECT_TRUE(3 == iTemp || 4 == iTemp || 5 == iTemp);

      //Verify that the diameter is close to 0.1
      p_oTree->GetValue(p_oPop->GetDiam10Code(p_oTree->GetSpecies(), p_oTree->GetType()), &fTemp);

      EXPECT_LT(fabs(fTemp - 0.1)/0.1, 0.05);

      p_iTreeCount[p_oTree->GetSpecies()]++;

      p_oTree = p_oAllTrees->NextTree();
    }

    //Total up all the trees and verify that it's 200
    iTemp = 0;
    for (i = 0; i < iNumSpecies; i++)
      iTemp += p_iTreeCount[i];

    EXPECT_EQ(200, iTemp);
    delete[] p_iTreeCount;
    delete p_oSimManager;
  } catch (modelErr &e) {
    delete[] p_iTreeCount;
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

/////////////////////////////////////////////////////////////////////////////
// DoPlantingRun6()
// Do the sixth planting run. This makes sure that gridded plantings happen
// correctly when grid cells do not divide evenly into the plot.
/////////////////////////////////////////////////////////////////////////////
TEST(Planting, DoPlantingRun6) {
  clTreePopulation * p_oPop;
  clTreeSearch *p_oAllTrees;
  clTree *p_oTree;
  float fTemp, fDiam10, fX, fY;
  int iNumSpecies, i, iTemp;
  int *p_iTreeCount;

  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {

    p_oSimManager->ReadFile( WritePlantingXMLFile6() );
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );
    iNumSpecies = p_oPop->GetNumberOfSpecies();
    p_iTreeCount = new int[iNumSpecies];

    //Make sure there are no existing trees
    p_oAllTrees = p_oPop->Find("all");
    EXPECT_EQ(NULL, p_oAllTrees->NextTree());

    //*********************************************
    // Timestep 1
    //*********************************************
    //Run the first timestep
    p_oSimManager->RunSim(1);

    //Make sure there are no trees
    p_oAllTrees = p_oPop->Find("all");
    EXPECT_EQ(NULL, p_oAllTrees->NextTree());

    //*********************************************
    // Timestep 2
    //*********************************************
    //Run the next timestep
    p_oSimManager->RunSim(1);

    for (i = 0; i < iNumSpecies; i++)
      p_iTreeCount[i] = 0;

    //Count the trees
    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {

      EXPECT_EQ(clTreePopulation::seedling, p_oTree->GetType());

      //Verify that the diameter is close to 0.x for each species
      p_oTree->GetValue(p_oPop->GetDiam10Code(p_oTree->GetSpecies(), p_oTree->GetType()), &fDiam10);
      iTemp = p_oTree->GetSpecies();
      fTemp = (iTemp * 0.1) + 0.1;
      EXPECT_LT(fabs(fTemp - fDiam10)/fTemp, 0.02);

      //Verify the gridded nature
      p_oTree->GetValue(p_oPop->GetXCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fX);
      p_oTree->GetValue(p_oPop->GetYCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fY);
      EXPECT_LT(((fX-1) / 2) - (floor((fX-1) / 2)), 0.01);
      EXPECT_LT(((fY-1) / 2) - (floor((fY-1) / 2)), 0.01);

      p_iTreeCount[p_oTree->GetSpecies()]++;

      p_oTree = p_oAllTrees->NextTree();
    }

    //Total up all the trees and verify that it's 10000
    iTemp = 0;
    for (i = 0; i < iNumSpecies; i++)
      iTemp += p_iTreeCount[i];

    EXPECT_EQ(2500, iTemp);
    delete[] p_iTreeCount;
    delete p_oSimManager;
  } catch (modelErr &e) {
    delete[] p_iTreeCount;
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

/////////////////////////////////////////////////////////////////////////////
// WritePlantingXMLFile1()
/////////////////////////////////////////////////////////////////////////////
const char* WritePlantingXMLFile1()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  std::fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
      << "<paramFile fileCode=\"06010101\">" << "<plot>"
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
      << "<tr_species speciesName=\"Western_Hemlock\"/>"
      << "<tr_species speciesName=\"Western_Redcedar\"/>"
      << "<tr_species speciesName=\"Amabilis_Fir\"/>"
      << "<tr_species speciesName=\"Subalpine_Fir\"/>"
      << "<tr_species speciesName=\"Hybrid_Spruce\"/>"
      << "<tr_species speciesName=\"Lodgepole_Pine\"/>"
      << "<tr_species speciesName=\"Trembling_Aspen\"/>"
      << "<tr_species speciesName=\"Black_Cottonwood\"/>"
      << "<tr_species speciesName=\"Paper_Birch\"/>"
      << "</tr_speciesList>"
      << "<tr_seedDiam10Cm>0.1</tr_seedDiam10Cm>"
      << "<tr_minAdultDBH>"
      << "<tr_madVal species=\"Western_Hemlock\">10</tr_madVal>"
      << "<tr_madVal species=\"Western_Redcedar\">10</tr_madVal>"
      << "<tr_madVal species=\"Amabilis_Fir\">10</tr_madVal>"
      << "<tr_madVal species=\"Subalpine_Fir\">10</tr_madVal>"
      << "<tr_madVal species=\"Hybrid_Spruce\">10</tr_madVal>"
      << "<tr_madVal species=\"Lodgepole_Pine\">10</tr_madVal>"
      << "<tr_madVal species=\"Trembling_Aspen\">10</tr_madVal>"
      << "<tr_madVal species=\"Black_Cottonwood\">10</tr_madVal>"
      << "<tr_madVal species=\"Paper_Birch\">10</tr_madVal>"
      << "</tr_minAdultDBH>"
      << "<tr_maxSeedlingHeight>"
      << "<tr_mshVal species=\"Western_Hemlock\">1.35</tr_mshVal>"
      << "<tr_mshVal species=\"Western_Redcedar\">1.35</tr_mshVal>"
      << "<tr_mshVal species=\"Amabilis_Fir\">1.35</tr_mshVal>"
      << "<tr_mshVal species=\"Subalpine_Fir\">1.35</tr_mshVal>"
      << "<tr_mshVal species=\"Hybrid_Spruce\">1.35</tr_mshVal>"
      << "<tr_mshVal species=\"Lodgepole_Pine\">1.35</tr_mshVal>"
      << "<tr_mshVal species=\"Trembling_Aspen\">1.35</tr_mshVal>"
      << "<tr_mshVal species=\"Black_Cottonwood\">1.35</tr_mshVal>"
      << "<tr_mshVal species=\"Paper_Birch\">1.35</tr_mshVal>"
      << "</tr_maxSeedlingHeight>"
      << "</trees>"
      << "<allometry>"
      << "<tr_canopyHeight>"
      << "<tr_chVal species=\"Western_Hemlock\">39.48</tr_chVal>"
      << "<tr_chVal species=\"Western_Redcedar\">39.54</tr_chVal>"
      << "<tr_chVal species=\"Amabilis_Fir\">40</tr_chVal>"
      << "<tr_chVal species=\"Subalpine_Fir\">40</tr_chVal>"
      << "<tr_chVal species=\"Hybrid_Spruce\">45</tr_chVal>"
      << "<tr_chVal species=\"Lodgepole_Pine\">40</tr_chVal>"
      << "<tr_chVal species=\"Trembling_Aspen\">39.14</tr_chVal>"
      << "<tr_chVal species=\"Black_Cottonwood\">39.47</tr_chVal>"
      << "<tr_chVal species=\"Paper_Birch\">33.18</tr_chVal>"
      << "</tr_canopyHeight>"
      << "<tr_stdAsympCrownRad>"
      << "<tr_sacrVal species=\"Western_Hemlock\">0.0549</tr_sacrVal>"
      << "<tr_sacrVal species=\"Western_Redcedar\">0.0614</tr_sacrVal>"
      << "<tr_sacrVal species=\"Amabilis_Fir\">0.0242</tr_sacrVal>"
      << "<tr_sacrVal species=\"Subalpine_Fir\">0.0251</tr_sacrVal>"
      << "<tr_sacrVal species=\"Hybrid_Spruce\">0.0239</tr_sacrVal>"
      << "<tr_sacrVal species=\"Lodgepole_Pine\">0.0303</tr_sacrVal>"
      << "<tr_sacrVal species=\"Trembling_Aspen\">0.0328</tr_sacrVal>"
      << "<tr_sacrVal species=\"Black_Cottonwood\">0.0247</tr_sacrVal>"
      << "<tr_sacrVal species=\"Paper_Birch\">0.0484</tr_sacrVal>"
      << "</tr_stdAsympCrownRad>"
      << "<tr_stdCrownRadExp>"
      << "<tr_screVal species=\"Western_Hemlock\">1.0</tr_screVal>"
      << "<tr_screVal species=\"Western_Redcedar\">1.0</tr_screVal>"
      << "<tr_screVal species=\"Amabilis_Fir\">1.0</tr_screVal>"
      << "<tr_screVal species=\"Subalpine_Fir\">1.0</tr_screVal>"
      << "<tr_screVal species=\"Hybrid_Spruce\">1.0</tr_screVal>"
      << "<tr_screVal species=\"Lodgepole_Pine\">1.0</tr_screVal>"
      << "<tr_screVal species=\"Trembling_Aspen\">1.0</tr_screVal>"
      << "<tr_screVal species=\"Black_Cottonwood\">1.0</tr_screVal>"
      << "<tr_screVal species=\"Paper_Birch\">1.0</tr_screVal>"
      << "</tr_stdCrownRadExp>"
      << "<tr_stdMaxCrownRad>"
      << "<tr_smcrVal species=\"Western_Hemlock\">10</tr_smcrVal>"
      << "<tr_smcrVal species=\"Western_Redcedar\">10</tr_smcrVal>"
      << "<tr_smcrVal species=\"Amabilis_Fir\">10</tr_smcrVal>"
      << "<tr_smcrVal species=\"Subalpine_Fir\">10</tr_smcrVal>"
      << "<tr_smcrVal species=\"Hybrid_Spruce\">10</tr_smcrVal>"
      << "<tr_smcrVal species=\"Lodgepole_Pine\">10</tr_smcrVal>"
      << "<tr_smcrVal species=\"Trembling_Aspen\">10</tr_smcrVal>"
      << "<tr_smcrVal species=\"Black_Cottonwood\">10</tr_smcrVal>"
      << "<tr_smcrVal species=\"Paper_Birch\">10</tr_smcrVal>"
      << "</tr_stdMaxCrownRad>"
      << "<tr_conversionDiam10ToDBH>"
      << "<tr_cdtdVal species=\"Western_Hemlock\">0.8008</tr_cdtdVal>"
      << "<tr_cdtdVal species=\"Western_Redcedar\">0.5944</tr_cdtdVal>"
      << "<tr_cdtdVal species=\"Amabilis_Fir\">0.7059</tr_cdtdVal>"
      << "<tr_cdtdVal species=\"Subalpine_Fir\">0.7776</tr_cdtdVal>"
      << "<tr_cdtdVal species=\"Hybrid_Spruce\">0.6933</tr_cdtdVal>"
      << "<tr_cdtdVal species=\"Lodgepole_Pine\">0.8014</tr_cdtdVal>"
      << "<tr_cdtdVal species=\"Trembling_Aspen\">0.7992</tr_cdtdVal>"
      << "<tr_cdtdVal species=\"Black_Cottonwood\">0.7926</tr_cdtdVal>"
      << "<tr_cdtdVal species=\"Paper_Birch\">0.7803</tr_cdtdVal>"
      << "</tr_conversionDiam10ToDBH>"
      << "<tr_interceptDiam10ToDBH>"
      << "<tr_idtdVal species=\"Western_Hemlock\">0</tr_idtdVal>"
      << "<tr_idtdVal species=\"Western_Redcedar\">0</tr_idtdVal>"
      << "<tr_idtdVal species=\"Amabilis_Fir\">0</tr_idtdVal>"
      << "<tr_idtdVal species=\"Subalpine_Fir\">0</tr_idtdVal>"
      << "<tr_idtdVal species=\"Hybrid_Spruce\">0</tr_idtdVal>"
      << "<tr_idtdVal species=\"Lodgepole_Pine\">0</tr_idtdVal>"
      << "<tr_idtdVal species=\"Trembling_Aspen\">0</tr_idtdVal>"
      << "<tr_idtdVal species=\"Black_Cottonwood\">0</tr_idtdVal>"
      << "<tr_idtdVal species=\"Paper_Birch\">0</tr_idtdVal>"
      << "</tr_interceptDiam10ToDBH>"
      << "<tr_stdAsympCrownHt>"
      << "<tr_sachVal species=\"Western_Hemlock\">0.389</tr_sachVal>"
      << "<tr_sachVal species=\"Western_Redcedar\">0.368</tr_sachVal>"
      << "<tr_sachVal species=\"Amabilis_Fir\">0.464</tr_sachVal>"
      << "<tr_sachVal species=\"Subalpine_Fir\">0.454</tr_sachVal>"
      << "<tr_sachVal species=\"Hybrid_Spruce\">0.405</tr_sachVal>"
      << "<tr_sachVal species=\"Lodgepole_Pine\">0.201</tr_sachVal>"
      << "<tr_sachVal species=\"Trembling_Aspen\">0.301</tr_sachVal>"
      << "<tr_sachVal species=\"Black_Cottonwood\">0.42</tr_sachVal>"
      << "<tr_sachVal species=\"Paper_Birch\">0.315</tr_sachVal>"
      << "</tr_stdAsympCrownHt>"
      << "<tr_stdCrownHtExp>"
      << "<tr_scheVal species=\"Western_Hemlock\">1.0</tr_scheVal>"
      << "<tr_scheVal species=\"Western_Redcedar\">1.0</tr_scheVal>"
      << "<tr_scheVal species=\"Amabilis_Fir\">1.0</tr_scheVal>"
      << "<tr_scheVal species=\"Subalpine_Fir\">1.0</tr_scheVal>"
      << "<tr_scheVal species=\"Hybrid_Spruce\">1.0</tr_scheVal>"
      << "<tr_scheVal species=\"Lodgepole_Pine\">1.0</tr_scheVal>"
      << "<tr_scheVal species=\"Trembling_Aspen\">1.0</tr_scheVal>"
      << "<tr_scheVal species=\"Black_Cottonwood\">1.0</tr_scheVal>"
      << "<tr_scheVal species=\"Paper_Birch\">1.0</tr_scheVal>"
      << "</tr_stdCrownHtExp>"
      << "<tr_slopeOfHeight-Diam10>"
      << "<tr_sohdVal species=\"Western_Hemlock\">0.03418</tr_sohdVal>"
      << "<tr_sohdVal species=\"Western_Redcedar\">0.0269</tr_sohdVal>"
      << "<tr_sohdVal species=\"Amabilis_Fir\">0.02871</tr_sohdVal>"
      << "<tr_sohdVal species=\"Subalpine_Fir\">0.02815</tr_sohdVal>"
      << "<tr_sohdVal species=\"Hybrid_Spruce\">0.02871</tr_sohdVal>"
      << "<tr_sohdVal species=\"Lodgepole_Pine\">0.03224</tr_sohdVal>"
      << "<tr_sohdVal species=\"Trembling_Aspen\">0.04796</tr_sohdVal>"
      << "<tr_sohdVal species=\"Black_Cottonwood\">0.04681</tr_sohdVal>"
      << "<tr_sohdVal species=\"Paper_Birch\">0.04101</tr_sohdVal>"
      << "</tr_slopeOfHeight-Diam10>"
      << "<tr_slopeOfAsymHeight>"
      << "<tr_soahVal species=\"Western_Hemlock\">0.0299</tr_soahVal>"
      << "<tr_soahVal species=\"Western_Redcedar\">0.0241</tr_soahVal>"
      << "<tr_soahVal species=\"Amabilis_Fir\">0.0263</tr_soahVal>"
      << "<tr_soahVal species=\"Subalpine_Fir\">0.0264</tr_soahVal>"
      << "<tr_soahVal species=\"Hybrid_Spruce\">0.0264</tr_soahVal>"
      << "<tr_soahVal species=\"Lodgepole_Pine\">0.0333</tr_soahVal>"
      << "<tr_soahVal species=\"Trembling_Aspen\">0.0352</tr_soahVal>"
      << "<tr_soahVal species=\"Black_Cottonwood\">0.0347</tr_soahVal>"
      << "<tr_soahVal species=\"Paper_Birch\">0.0454</tr_soahVal>"
      << "</tr_slopeOfAsymHeight>"
      << "<tr_whatSeedlingHeightDiam>"
      << "<tr_wsehdVal species=\"Western_Hemlock\">0</tr_wsehdVal>"
      << "<tr_wsehdVal species=\"Western_Redcedar\">0</tr_wsehdVal>"
      << "<tr_wsehdVal species=\"Amabilis_Fir\">0</tr_wsehdVal>"
      << "<tr_wsehdVal species=\"Subalpine_Fir\">0</tr_wsehdVal>"
      << "<tr_wsehdVal species=\"Hybrid_Spruce\">0</tr_wsehdVal>"
      << "<tr_wsehdVal species=\"Lodgepole_Pine\">0</tr_wsehdVal>"
      << "<tr_wsehdVal species=\"Trembling_Aspen\">0</tr_wsehdVal>"
      << "<tr_wsehdVal species=\"Black_Cottonwood\">0</tr_wsehdVal>"
      << "<tr_wsehdVal species=\"Paper_Birch\">0</tr_wsehdVal>"
      << "</tr_whatSeedlingHeightDiam>"
      << "<tr_whatSaplingHeightDiam>"
      << "<tr_wsahdVal species=\"Western_Hemlock\">0</tr_wsahdVal>"
      << "<tr_wsahdVal species=\"Western_Redcedar\">0</tr_wsahdVal>"
      << "<tr_wsahdVal species=\"Amabilis_Fir\">0</tr_wsahdVal>"
      << "<tr_wsahdVal species=\"Subalpine_Fir\">0</tr_wsahdVal>"
      << "<tr_wsahdVal species=\"Hybrid_Spruce\">0</tr_wsahdVal>"
      << "<tr_wsahdVal species=\"Lodgepole_Pine\">0</tr_wsahdVal>"
      << "<tr_wsahdVal species=\"Trembling_Aspen\">0</tr_wsahdVal>"
      << "<tr_wsahdVal species=\"Black_Cottonwood\">0</tr_wsahdVal>"
      << "<tr_wsahdVal species=\"Paper_Birch\">0</tr_wsahdVal>"
      << "</tr_whatSaplingHeightDiam>"
      << "<tr_whatAdultHeightDiam>"
      << "<tr_wahdVal species=\"Western_Hemlock\">0</tr_wahdVal>"
      << "<tr_wahdVal species=\"Western_Redcedar\">0</tr_wahdVal>"
      << "<tr_wahdVal species=\"Amabilis_Fir\">0</tr_wahdVal>"
      << "<tr_wahdVal species=\"Subalpine_Fir\">0</tr_wahdVal>"
      << "<tr_wahdVal species=\"Hybrid_Spruce\">0</tr_wahdVal>"
      << "<tr_wahdVal species=\"Lodgepole_Pine\">0</tr_wahdVal>"
      << "<tr_wahdVal species=\"Trembling_Aspen\">0</tr_wahdVal>"
      << "<tr_wahdVal species=\"Black_Cottonwood\">0</tr_wahdVal>"
      << "<tr_wahdVal species=\"Paper_Birch\">0</tr_wahdVal>"
      << "</tr_whatAdultHeightDiam>"
      << "<tr_whatAdultCrownRadDiam>"
      << "<tr_wacrdVal species=\"Western_Hemlock\">0</tr_wacrdVal>"
      << "<tr_wacrdVal species=\"Western_Redcedar\">0</tr_wacrdVal>"
      << "<tr_wacrdVal species=\"Amabilis_Fir\">0</tr_wacrdVal>"
      << "<tr_wacrdVal species=\"Subalpine_Fir\">0</tr_wacrdVal>"
      << "<tr_wacrdVal species=\"Hybrid_Spruce\">0</tr_wacrdVal>"
      << "<tr_wacrdVal species=\"Lodgepole_Pine\">0</tr_wacrdVal>"
      << "<tr_wacrdVal species=\"Trembling_Aspen\">0</tr_wacrdVal>"
      << "<tr_wacrdVal species=\"Black_Cottonwood\">0</tr_wacrdVal>"
      << "<tr_wacrdVal species=\"Paper_Birch\">0</tr_wacrdVal>"
      << "</tr_whatAdultCrownRadDiam>"
      << "<tr_whatAdultCrownHeightHeight>"
      << "<tr_wachhVal species=\"Western_Hemlock\">0</tr_wachhVal>"
      << "<tr_wachhVal species=\"Western_Redcedar\">0</tr_wachhVal>"
      << "<tr_wachhVal species=\"Amabilis_Fir\">0</tr_wachhVal>"
      << "<tr_wachhVal species=\"Subalpine_Fir\">0</tr_wachhVal>"
      << "<tr_wachhVal species=\"Hybrid_Spruce\">0</tr_wachhVal>"
      << "<tr_wachhVal species=\"Lodgepole_Pine\">0</tr_wachhVal>"
      << "<tr_wachhVal species=\"Trembling_Aspen\">0</tr_wachhVal>"
      << "<tr_wachhVal species=\"Black_Cottonwood\">0</tr_wachhVal>"
      << "<tr_wachhVal species=\"Paper_Birch\">0</tr_wachhVal>"
      << "</tr_whatAdultCrownHeightHeight>"
      << "<tr_whatSaplingCrownRadDiam>"
      << "<tr_wscrdVal species=\"Western_Hemlock\">0</tr_wscrdVal>"
      << "<tr_wscrdVal species=\"Western_Redcedar\">0</tr_wscrdVal>"
      << "<tr_wscrdVal species=\"Amabilis_Fir\">0</tr_wscrdVal>"
      << "<tr_wscrdVal species=\"Subalpine_Fir\">0</tr_wscrdVal>"
      << "<tr_wscrdVal species=\"Hybrid_Spruce\">0</tr_wscrdVal>"
      << "<tr_wscrdVal species=\"Lodgepole_Pine\">0</tr_wscrdVal>"
      << "<tr_wscrdVal species=\"Trembling_Aspen\">0</tr_wscrdVal>"
      << "<tr_wscrdVal species=\"Black_Cottonwood\">0</tr_wscrdVal>"
      << "<tr_wscrdVal species=\"Paper_Birch\">0</tr_wscrdVal>"
      << "</tr_whatSaplingCrownRadDiam>"
      << "<tr_whatSaplingCrownHeightHeight>"
      << "<tr_wschhVal species=\"Western_Hemlock\">0</tr_wschhVal>"
      << "<tr_wschhVal species=\"Western_Redcedar\">0</tr_wschhVal>"
      << "<tr_wschhVal species=\"Amabilis_Fir\">0</tr_wschhVal>"
      << "<tr_wschhVal species=\"Subalpine_Fir\">0</tr_wschhVal>"
      << "<tr_wschhVal species=\"Hybrid_Spruce\">0</tr_wschhVal>"
      << "<tr_wschhVal species=\"Lodgepole_Pine\">0</tr_wschhVal>"
      << "<tr_wschhVal species=\"Trembling_Aspen\">0</tr_wschhVal>"
      << "<tr_wschhVal species=\"Black_Cottonwood\">0</tr_wschhVal>"
      << "<tr_wschhVal species=\"Paper_Birch\">0</tr_wschhVal>"
      << "</tr_whatSaplingCrownHeightHeight>"
      << "</allometry>";
  oOut  << "<behaviorList>"
      << "<behavior>"
      << "<behaviorName>Plant</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>1</listPosition>"
      << "</behavior>"
      << "</behaviorList>"
      << "<Plant1>"
      << "<pl_plantEvent>"
      << "<pl_applyToSpecies species=\"Lodgepole_Pine\" />"
      << "<pl_applyToSpecies species=\"Subalpine_Fir\" />"
      << "<pl_applyToSpecies species=\"Hybrid_Spruce\" />"
      << "<pl_timestep>1</pl_timestep>"
      << "<pl_spaceType>random</pl_spaceType>"
      << "<pl_distanceOrDensity>200</pl_distanceOrDensity>"
      << "<pl_amountToPlant>"
      << "<pl_atpVal species=\"Subalpine_Fir\">33.3</pl_atpVal>"
      << "<pl_atpVal species=\"Hybrid_Spruce\">33.3</pl_atpVal>"
      << "<pl_atpVal species=\"Lodgepole_Pine\">33.4</pl_atpVal>"
      << "</pl_amountToPlant>";
  for (int i = 0; i < 25; i++) {
    for (int j = 0; j < 25; j++) {
      oOut << "<pl_applyToCell x=\"" << i << "\" y=\"" << j << "\" /> ";
    }
  }
  oOut << "</pl_plantEvent>"
      << "</Plant1>"
      << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WritePlantingXMLFile2()
/////////////////////////////////////////////////////////////////////////////
const char* WritePlantingXMLFile2()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  std::fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
      << "<paramFile fileCode=\"06010101\">" << "<plot>"
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
      << "<tr_species speciesName=\"Western_Hemlock\"/>"
      << "<tr_species speciesName=\"Western_Redcedar\"/>"
      << "<tr_species speciesName=\"Amabilis_Fir\"/>"
      << "<tr_species speciesName=\"Subalpine_Fir\"/>"
      << "<tr_species speciesName=\"Hybrid_Spruce\"/>"
      << "<tr_species speciesName=\"Lodgepole_Pine\"/>"
      << "<tr_species speciesName=\"Trembling_Aspen\"/>"
      << "<tr_species speciesName=\"Black_Cottonwood\"/>"
      << "<tr_species speciesName=\"Paper_Birch\"/>"
      << "</tr_speciesList>"
      << "<tr_seedDiam10Cm>0.1</tr_seedDiam10Cm>"
      << "<tr_minAdultDBH>"
      << "<tr_madVal species=\"Western_Hemlock\">10</tr_madVal>"
      << "<tr_madVal species=\"Western_Redcedar\">10</tr_madVal>"
      << "<tr_madVal species=\"Amabilis_Fir\">10</tr_madVal>"
      << "<tr_madVal species=\"Subalpine_Fir\">10</tr_madVal>"
      << "<tr_madVal species=\"Hybrid_Spruce\">10</tr_madVal>"
      << "<tr_madVal species=\"Lodgepole_Pine\">10</tr_madVal>"
      << "<tr_madVal species=\"Trembling_Aspen\">10</tr_madVal>"
      << "<tr_madVal species=\"Black_Cottonwood\">10</tr_madVal>"
      << "<tr_madVal species=\"Paper_Birch\">10</tr_madVal>"
      << "</tr_minAdultDBH>"
      << "<tr_maxSeedlingHeight>"
      << "<tr_mshVal species=\"Western_Hemlock\">1.35</tr_mshVal>"
      << "<tr_mshVal species=\"Western_Redcedar\">1.35</tr_mshVal>"
      << "<tr_mshVal species=\"Amabilis_Fir\">1.35</tr_mshVal>"
      << "<tr_mshVal species=\"Subalpine_Fir\">1.35</tr_mshVal>"
      << "<tr_mshVal species=\"Hybrid_Spruce\">1.35</tr_mshVal>"
      << "<tr_mshVal species=\"Lodgepole_Pine\">1.35</tr_mshVal>"
      << "<tr_mshVal species=\"Trembling_Aspen\">1.35</tr_mshVal>"
      << "<tr_mshVal species=\"Black_Cottonwood\">1.35</tr_mshVal>"
      << "<tr_mshVal species=\"Paper_Birch\">1.35</tr_mshVal>"
      << "</tr_maxSeedlingHeight>"
      << "</trees>"
      << "<allometry>"
      << "<tr_canopyHeight>"
      << "<tr_chVal species=\"Western_Hemlock\">39.48</tr_chVal>"
      << "<tr_chVal species=\"Western_Redcedar\">39.54</tr_chVal>"
      << "<tr_chVal species=\"Amabilis_Fir\">40</tr_chVal>"
      << "<tr_chVal species=\"Subalpine_Fir\">40</tr_chVal>"
      << "<tr_chVal species=\"Hybrid_Spruce\">45</tr_chVal>"
      << "<tr_chVal species=\"Lodgepole_Pine\">40</tr_chVal>"
      << "<tr_chVal species=\"Trembling_Aspen\">39.14</tr_chVal>"
      << "<tr_chVal species=\"Black_Cottonwood\">39.47</tr_chVal>"
      << "<tr_chVal species=\"Paper_Birch\">33.18</tr_chVal>"
      << "</tr_canopyHeight>"
      << "<tr_stdAsympCrownRad>"
      << "<tr_sacrVal species=\"Western_Hemlock\">0.0549</tr_sacrVal>"
      << "<tr_sacrVal species=\"Western_Redcedar\">0.0614</tr_sacrVal>"
      << "<tr_sacrVal species=\"Amabilis_Fir\">0.0242</tr_sacrVal>"
      << "<tr_sacrVal species=\"Subalpine_Fir\">0.0251</tr_sacrVal>"
      << "<tr_sacrVal species=\"Hybrid_Spruce\">0.0239</tr_sacrVal>"
      << "<tr_sacrVal species=\"Lodgepole_Pine\">0.0303</tr_sacrVal>"
      << "<tr_sacrVal species=\"Trembling_Aspen\">0.0328</tr_sacrVal>"
      << "<tr_sacrVal species=\"Black_Cottonwood\">0.0247</tr_sacrVal>"
      << "<tr_sacrVal species=\"Paper_Birch\">0.0484</tr_sacrVal>"
      << "</tr_stdAsympCrownRad>"
      << "<tr_stdCrownRadExp>"
      << "<tr_screVal species=\"Western_Hemlock\">1.0</tr_screVal>"
      << "<tr_screVal species=\"Western_Redcedar\">1.0</tr_screVal>"
      << "<tr_screVal species=\"Amabilis_Fir\">1.0</tr_screVal>"
      << "<tr_screVal species=\"Subalpine_Fir\">1.0</tr_screVal>"
      << "<tr_screVal species=\"Hybrid_Spruce\">1.0</tr_screVal>"
      << "<tr_screVal species=\"Lodgepole_Pine\">1.0</tr_screVal>"
      << "<tr_screVal species=\"Trembling_Aspen\">1.0</tr_screVal>"
      << "<tr_screVal species=\"Black_Cottonwood\">1.0</tr_screVal>"
      << "<tr_screVal species=\"Paper_Birch\">1.0</tr_screVal>"
      << "</tr_stdCrownRadExp>"
      << "<tr_stdMaxCrownRad>"
      << "<tr_smcrVal species=\"Western_Hemlock\">10</tr_smcrVal>"
      << "<tr_smcrVal species=\"Western_Redcedar\">10</tr_smcrVal>"
      << "<tr_smcrVal species=\"Amabilis_Fir\">10</tr_smcrVal>"
      << "<tr_smcrVal species=\"Subalpine_Fir\">10</tr_smcrVal>"
      << "<tr_smcrVal species=\"Hybrid_Spruce\">10</tr_smcrVal>"
      << "<tr_smcrVal species=\"Lodgepole_Pine\">10</tr_smcrVal>"
      << "<tr_smcrVal species=\"Trembling_Aspen\">10</tr_smcrVal>"
      << "<tr_smcrVal species=\"Black_Cottonwood\">10</tr_smcrVal>"
      << "<tr_smcrVal species=\"Paper_Birch\">10</tr_smcrVal>"
      << "</tr_stdMaxCrownRad>"
      << "<tr_conversionDiam10ToDBH>"
      << "<tr_cdtdVal species=\"Western_Hemlock\">0.8008</tr_cdtdVal>"
      << "<tr_cdtdVal species=\"Western_Redcedar\">0.5944</tr_cdtdVal>"
      << "<tr_cdtdVal species=\"Amabilis_Fir\">0.7059</tr_cdtdVal>"
      << "<tr_cdtdVal species=\"Subalpine_Fir\">0.7776</tr_cdtdVal>"
      << "<tr_cdtdVal species=\"Hybrid_Spruce\">0.6933</tr_cdtdVal>"
      << "<tr_cdtdVal species=\"Lodgepole_Pine\">0.8014</tr_cdtdVal>"
      << "<tr_cdtdVal species=\"Trembling_Aspen\">0.7992</tr_cdtdVal>"
      << "<tr_cdtdVal species=\"Black_Cottonwood\">0.7926</tr_cdtdVal>"
      << "<tr_cdtdVal species=\"Paper_Birch\">0.7803</tr_cdtdVal>"
      << "</tr_conversionDiam10ToDBH>"
      << "<tr_interceptDiam10ToDBH>"
      << "<tr_idtdVal species=\"Western_Hemlock\">0</tr_idtdVal>"
      << "<tr_idtdVal species=\"Western_Redcedar\">0</tr_idtdVal>"
      << "<tr_idtdVal species=\"Amabilis_Fir\">0</tr_idtdVal>"
      << "<tr_idtdVal species=\"Subalpine_Fir\">0</tr_idtdVal>"
      << "<tr_idtdVal species=\"Hybrid_Spruce\">0</tr_idtdVal>"
      << "<tr_idtdVal species=\"Lodgepole_Pine\">0</tr_idtdVal>"
      << "<tr_idtdVal species=\"Trembling_Aspen\">0</tr_idtdVal>"
      << "<tr_idtdVal species=\"Black_Cottonwood\">0</tr_idtdVal>"
      << "<tr_idtdVal species=\"Paper_Birch\">0</tr_idtdVal>"
      << "</tr_interceptDiam10ToDBH>"
      << "<tr_stdAsympCrownHt>"
      << "<tr_sachVal species=\"Western_Hemlock\">0.389</tr_sachVal>"
      << "<tr_sachVal species=\"Western_Redcedar\">0.368</tr_sachVal>"
      << "<tr_sachVal species=\"Amabilis_Fir\">0.464</tr_sachVal>"
      << "<tr_sachVal species=\"Subalpine_Fir\">0.454</tr_sachVal>"
      << "<tr_sachVal species=\"Hybrid_Spruce\">0.405</tr_sachVal>"
      << "<tr_sachVal species=\"Lodgepole_Pine\">0.201</tr_sachVal>"
      << "<tr_sachVal species=\"Trembling_Aspen\">0.301</tr_sachVal>"
      << "<tr_sachVal species=\"Black_Cottonwood\">0.42</tr_sachVal>"
      << "<tr_sachVal species=\"Paper_Birch\">0.315</tr_sachVal>"
      << "</tr_stdAsympCrownHt>"
      << "<tr_stdCrownHtExp>"
      << "<tr_scheVal species=\"Western_Hemlock\">1.0</tr_scheVal>"
      << "<tr_scheVal species=\"Western_Redcedar\">1.0</tr_scheVal>"
      << "<tr_scheVal species=\"Amabilis_Fir\">1.0</tr_scheVal>"
      << "<tr_scheVal species=\"Subalpine_Fir\">1.0</tr_scheVal>"
      << "<tr_scheVal species=\"Hybrid_Spruce\">1.0</tr_scheVal>"
      << "<tr_scheVal species=\"Lodgepole_Pine\">1.0</tr_scheVal>"
      << "<tr_scheVal species=\"Trembling_Aspen\">1.0</tr_scheVal>"
      << "<tr_scheVal species=\"Black_Cottonwood\">1.0</tr_scheVal>"
      << "<tr_scheVal species=\"Paper_Birch\">1.0</tr_scheVal>"
      << "</tr_stdCrownHtExp>"
      << "<tr_slopeOfHeight-Diam10>"
      << "<tr_sohdVal species=\"Western_Hemlock\">0.03418</tr_sohdVal>"
      << "<tr_sohdVal species=\"Western_Redcedar\">0.0269</tr_sohdVal>"
      << "<tr_sohdVal species=\"Amabilis_Fir\">0.02871</tr_sohdVal>"
      << "<tr_sohdVal species=\"Subalpine_Fir\">0.02815</tr_sohdVal>"
      << "<tr_sohdVal species=\"Hybrid_Spruce\">0.02871</tr_sohdVal>"
      << "<tr_sohdVal species=\"Lodgepole_Pine\">0.03224</tr_sohdVal>"
      << "<tr_sohdVal species=\"Trembling_Aspen\">0.04796</tr_sohdVal>"
      << "<tr_sohdVal species=\"Black_Cottonwood\">0.04681</tr_sohdVal>"
      << "<tr_sohdVal species=\"Paper_Birch\">0.04101</tr_sohdVal>"
      << "</tr_slopeOfHeight-Diam10>"
      << "<tr_slopeOfAsymHeight>"
      << "<tr_soahVal species=\"Western_Hemlock\">0.0299</tr_soahVal>"
      << "<tr_soahVal species=\"Western_Redcedar\">0.0241</tr_soahVal>"
      << "<tr_soahVal species=\"Amabilis_Fir\">0.0263</tr_soahVal>"
      << "<tr_soahVal species=\"Subalpine_Fir\">0.0264</tr_soahVal>"
      << "<tr_soahVal species=\"Hybrid_Spruce\">0.0264</tr_soahVal>"
      << "<tr_soahVal species=\"Lodgepole_Pine\">0.0333</tr_soahVal>"
      << "<tr_soahVal species=\"Trembling_Aspen\">0.0352</tr_soahVal>"
      << "<tr_soahVal species=\"Black_Cottonwood\">0.0347</tr_soahVal>"
      << "<tr_soahVal species=\"Paper_Birch\">0.0454</tr_soahVal>"
      << "</tr_slopeOfAsymHeight>"
      << "<tr_whatSeedlingHeightDiam>"
      << "<tr_wsehdVal species=\"Western_Hemlock\">0</tr_wsehdVal>"
      << "<tr_wsehdVal species=\"Western_Redcedar\">0</tr_wsehdVal>"
      << "<tr_wsehdVal species=\"Amabilis_Fir\">0</tr_wsehdVal>"
      << "<tr_wsehdVal species=\"Subalpine_Fir\">0</tr_wsehdVal>"
      << "<tr_wsehdVal species=\"Hybrid_Spruce\">0</tr_wsehdVal>"
      << "<tr_wsehdVal species=\"Lodgepole_Pine\">0</tr_wsehdVal>"
      << "<tr_wsehdVal species=\"Trembling_Aspen\">0</tr_wsehdVal>"
      << "<tr_wsehdVal species=\"Black_Cottonwood\">0</tr_wsehdVal>"
      << "<tr_wsehdVal species=\"Paper_Birch\">0</tr_wsehdVal>"
      << "</tr_whatSeedlingHeightDiam>"
      << "<tr_whatSaplingHeightDiam>"
      << "<tr_wsahdVal species=\"Western_Hemlock\">0</tr_wsahdVal>"
      << "<tr_wsahdVal species=\"Western_Redcedar\">0</tr_wsahdVal>"
      << "<tr_wsahdVal species=\"Amabilis_Fir\">0</tr_wsahdVal>"
      << "<tr_wsahdVal species=\"Subalpine_Fir\">0</tr_wsahdVal>"
      << "<tr_wsahdVal species=\"Hybrid_Spruce\">0</tr_wsahdVal>"
      << "<tr_wsahdVal species=\"Lodgepole_Pine\">0</tr_wsahdVal>"
      << "<tr_wsahdVal species=\"Trembling_Aspen\">0</tr_wsahdVal>"
      << "<tr_wsahdVal species=\"Black_Cottonwood\">0</tr_wsahdVal>"
      << "<tr_wsahdVal species=\"Paper_Birch\">0</tr_wsahdVal>"
      << "</tr_whatSaplingHeightDiam>"
      << "<tr_whatAdultHeightDiam>"
      << "<tr_wahdVal species=\"Western_Hemlock\">0</tr_wahdVal>"
      << "<tr_wahdVal species=\"Western_Redcedar\">0</tr_wahdVal>"
      << "<tr_wahdVal species=\"Amabilis_Fir\">0</tr_wahdVal>"
      << "<tr_wahdVal species=\"Subalpine_Fir\">0</tr_wahdVal>"
      << "<tr_wahdVal species=\"Hybrid_Spruce\">0</tr_wahdVal>"
      << "<tr_wahdVal species=\"Lodgepole_Pine\">0</tr_wahdVal>"
      << "<tr_wahdVal species=\"Trembling_Aspen\">0</tr_wahdVal>"
      << "<tr_wahdVal species=\"Black_Cottonwood\">0</tr_wahdVal>"
      << "<tr_wahdVal species=\"Paper_Birch\">0</tr_wahdVal>"
      << "</tr_whatAdultHeightDiam>"
      << "<tr_whatAdultCrownRadDiam>"
      << "<tr_wacrdVal species=\"Western_Hemlock\">0</tr_wacrdVal>"
      << "<tr_wacrdVal species=\"Western_Redcedar\">0</tr_wacrdVal>"
      << "<tr_wacrdVal species=\"Amabilis_Fir\">0</tr_wacrdVal>"
      << "<tr_wacrdVal species=\"Subalpine_Fir\">0</tr_wacrdVal>"
      << "<tr_wacrdVal species=\"Hybrid_Spruce\">0</tr_wacrdVal>"
      << "<tr_wacrdVal species=\"Lodgepole_Pine\">0</tr_wacrdVal>"
      << "<tr_wacrdVal species=\"Trembling_Aspen\">0</tr_wacrdVal>"
      << "<tr_wacrdVal species=\"Black_Cottonwood\">0</tr_wacrdVal>"
      << "<tr_wacrdVal species=\"Paper_Birch\">0</tr_wacrdVal>"
      << "</tr_whatAdultCrownRadDiam>"
      << "<tr_whatAdultCrownHeightHeight>"
      << "<tr_wachhVal species=\"Western_Hemlock\">0</tr_wachhVal>"
      << "<tr_wachhVal species=\"Western_Redcedar\">0</tr_wachhVal>"
      << "<tr_wachhVal species=\"Amabilis_Fir\">0</tr_wachhVal>"
      << "<tr_wachhVal species=\"Subalpine_Fir\">0</tr_wachhVal>"
      << "<tr_wachhVal species=\"Hybrid_Spruce\">0</tr_wachhVal>"
      << "<tr_wachhVal species=\"Lodgepole_Pine\">0</tr_wachhVal>"
      << "<tr_wachhVal species=\"Trembling_Aspen\">0</tr_wachhVal>"
      << "<tr_wachhVal species=\"Black_Cottonwood\">0</tr_wachhVal>"
      << "<tr_wachhVal species=\"Paper_Birch\">0</tr_wachhVal>"
      << "</tr_whatAdultCrownHeightHeight>"
      << "<tr_whatSaplingCrownRadDiam>"
      << "<tr_wscrdVal species=\"Western_Hemlock\">0</tr_wscrdVal>"
      << "<tr_wscrdVal species=\"Western_Redcedar\">0</tr_wscrdVal>"
      << "<tr_wscrdVal species=\"Amabilis_Fir\">0</tr_wscrdVal>"
      << "<tr_wscrdVal species=\"Subalpine_Fir\">0</tr_wscrdVal>"
      << "<tr_wscrdVal species=\"Hybrid_Spruce\">0</tr_wscrdVal>"
      << "<tr_wscrdVal species=\"Lodgepole_Pine\">0</tr_wscrdVal>"
      << "<tr_wscrdVal species=\"Trembling_Aspen\">0</tr_wscrdVal>"
      << "<tr_wscrdVal species=\"Black_Cottonwood\">0</tr_wscrdVal>"
      << "<tr_wscrdVal species=\"Paper_Birch\">0</tr_wscrdVal>"
      << "</tr_whatSaplingCrownRadDiam>"
      << "<tr_whatSaplingCrownHeightHeight>"
      << "<tr_wschhVal species=\"Western_Hemlock\">0</tr_wschhVal>"
      << "<tr_wschhVal species=\"Western_Redcedar\">0</tr_wschhVal>"
      << "<tr_wschhVal species=\"Amabilis_Fir\">0</tr_wschhVal>"
      << "<tr_wschhVal species=\"Subalpine_Fir\">0</tr_wschhVal>"
      << "<tr_wschhVal species=\"Hybrid_Spruce\">0</tr_wschhVal>"
      << "<tr_wschhVal species=\"Lodgepole_Pine\">0</tr_wschhVal>"
      << "<tr_wschhVal species=\"Trembling_Aspen\">0</tr_wschhVal>"
      << "<tr_wschhVal species=\"Black_Cottonwood\">0</tr_wschhVal>"
      << "<tr_wschhVal species=\"Paper_Birch\">0</tr_wschhVal>"
      << "</tr_whatSaplingCrownHeightHeight>"
      << "</allometry>"
      << "<behaviorList>"
      << "<behavior>"
      << "<behaviorName>Plant</behaviorName>"
      << "<listPosition>1</listPosition>"
      << "<version>1</version>"
      << "</behavior>"
      << "</behaviorList>"
      << "<Plant1>"
      << "<pl_initialDiam10>"
      << "<pl_idVal species=\"Hybrid_Spruce\">0.5</pl_idVal>"
      << "<pl_idVal species=\"Lodgepole_Pine\">0.6</pl_idVal>"
      << "<pl_idVal species=\"Trembling_Aspen\">0.7</pl_idVal>"
      << "<pl_idVal species=\"Black_Cottonwood\">0.8</pl_idVal>"
      << "<pl_idVal species=\"Western_Hemlock\">0.1</pl_idVal>"
      << "<pl_idVal species=\"Western_Redcedar\">0.2</pl_idVal>"
      << "<pl_idVal species=\"Amabilis_Fir\">0.3</pl_idVal>"
      << "<pl_idVal species=\"Subalpine_Fir\">0.4</pl_idVal>"
      << "<pl_idVal species=\"Paper_Birch\">0.9</pl_idVal>"
      << "</pl_initialDiam10>"
      << "<pl_plantEvent>"
      << "<pl_applyToSpecies species=\"Lodgepole_Pine\" />"
      << "<pl_applyToSpecies species=\"Subalpine_Fir\" />"
      << "<pl_applyToSpecies species=\"Hybrid_Spruce\" />"
      << "<pl_applyToSpecies species=\"Trembling_Aspen\" />"
      << "<pl_applyToSpecies species=\"Black_Cottonwood\" />"
      << "<pl_applyToSpecies species=\"Western_Hemlock\" />"
      << "<pl_applyToSpecies species=\"Western_Redcedar\" />"
      << "<pl_applyToSpecies species=\"Amabilis_Fir\" />"
      << "<pl_applyToSpecies species=\"Paper_Birch\" />"
      << "<pl_timestep>2</pl_timestep>"
      << "<pl_spaceType>gridded</pl_spaceType>"
      << "<pl_distanceOrDensity>2</pl_distanceOrDensity>"
      << "<pl_amountToPlant>"
      << "<pl_atpVal species=\"Western_Hemlock\">5</pl_atpVal>"
      << "<pl_atpVal species=\"Western_Redcedar\">10</pl_atpVal>"
      << "<pl_atpVal species=\"Amabilis_Fir\">15</pl_atpVal>"
      << "<pl_atpVal species=\"Subalpine_Fir\">30</pl_atpVal>"
      << "<pl_atpVal species=\"Hybrid_Spruce\">1</pl_atpVal>"
      << "<pl_atpVal species=\"Lodgepole_Pine\">10</pl_atpVal>"
      << "<pl_atpVal species=\"Trembling_Aspen\">7</pl_atpVal>"
      << "<pl_atpVal species=\"Black_Cottonwood\">8</pl_atpVal>"
      << "<pl_atpVal species=\"Paper_Birch\">14</pl_atpVal>"
      << "</pl_amountToPlant>";
  for (int i = 0; i < 25; i++) {
    for (int j = 0; j < 25; j++) {
      oOut << "<pl_applyToCell x=\"" << i << "\" y=\"" << j << "\" /> ";
    }
  }
  oOut << "</pl_plantEvent>"
      << "</Plant1>"
      << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WritePlantingXMLFile3()
/////////////////////////////////////////////////////////////////////////////
const char* WritePlantingXMLFile3()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";
  int i, j;

  //Open file to write to
  std::fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
      << "<paramFile fileCode=\"06010101\">" << "<plot>"
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
      << "<tr_species speciesName=\"Western_Hemlock\"/>"
      << "<tr_species speciesName=\"Western_Redcedar\"/>"
      << "<tr_species speciesName=\"Amabilis_Fir\"/>"
      << "<tr_species speciesName=\"Subalpine_Fir\"/>"
      << "<tr_species speciesName=\"Hybrid_Spruce\"/>"
      << "<tr_species speciesName=\"Lodgepole_Pine\"/>"
      << "<tr_species speciesName=\"Trembling_Aspen\"/>"
      << "<tr_species speciesName=\"Black_Cottonwood\"/>"
      << "<tr_species speciesName=\"Paper_Birch\"/>"
      << "</tr_speciesList>"
      << "<tr_seedDiam10Cm>0.1</tr_seedDiam10Cm>"
      << "<tr_minAdultDBH>"
      << "<tr_madVal species=\"Western_Hemlock\">10</tr_madVal>"
      << "<tr_madVal species=\"Western_Redcedar\">10</tr_madVal>"
      << "<tr_madVal species=\"Amabilis_Fir\">10</tr_madVal>"
      << "<tr_madVal species=\"Subalpine_Fir\">10</tr_madVal>"
      << "<tr_madVal species=\"Hybrid_Spruce\">10</tr_madVal>"
      << "<tr_madVal species=\"Lodgepole_Pine\">10</tr_madVal>"
      << "<tr_madVal species=\"Trembling_Aspen\">10</tr_madVal>"
      << "<tr_madVal species=\"Black_Cottonwood\">10</tr_madVal>"
      << "<tr_madVal species=\"Paper_Birch\">10</tr_madVal>"
      << "</tr_minAdultDBH>"
      << "<tr_maxSeedlingHeight>"
      << "<tr_mshVal species=\"Western_Hemlock\">1.35</tr_mshVal>"
      << "<tr_mshVal species=\"Western_Redcedar\">1.35</tr_mshVal>"
      << "<tr_mshVal species=\"Amabilis_Fir\">1.35</tr_mshVal>"
      << "<tr_mshVal species=\"Subalpine_Fir\">1.35</tr_mshVal>"
      << "<tr_mshVal species=\"Hybrid_Spruce\">1.35</tr_mshVal>"
      << "<tr_mshVal species=\"Lodgepole_Pine\">1.35</tr_mshVal>"
      << "<tr_mshVal species=\"Trembling_Aspen\">1.35</tr_mshVal>"
      << "<tr_mshVal species=\"Black_Cottonwood\">1.35</tr_mshVal>"
      << "<tr_mshVal species=\"Paper_Birch\">1.35</tr_mshVal>"
      << "</tr_maxSeedlingHeight>"
      << "</trees>"
      << "<allometry>"
      << "<tr_canopyHeight>"
      << "<tr_chVal species=\"Western_Hemlock\">39.48</tr_chVal>"
      << "<tr_chVal species=\"Western_Redcedar\">39.54</tr_chVal>"
      << "<tr_chVal species=\"Amabilis_Fir\">40</tr_chVal>"
      << "<tr_chVal species=\"Subalpine_Fir\">40</tr_chVal>"
      << "<tr_chVal species=\"Hybrid_Spruce\">45</tr_chVal>"
      << "<tr_chVal species=\"Lodgepole_Pine\">40</tr_chVal>"
      << "<tr_chVal species=\"Trembling_Aspen\">39.14</tr_chVal>"
      << "<tr_chVal species=\"Black_Cottonwood\">39.47</tr_chVal>"
      << "<tr_chVal species=\"Paper_Birch\">33.18</tr_chVal>"
      << "</tr_canopyHeight>"
      << "<tr_stdAsympCrownRad>"
      << "<tr_sacrVal species=\"Western_Hemlock\">0.0549</tr_sacrVal>"
      << "<tr_sacrVal species=\"Western_Redcedar\">0.0614</tr_sacrVal>"
      << "<tr_sacrVal species=\"Amabilis_Fir\">0.0242</tr_sacrVal>"
      << "<tr_sacrVal species=\"Subalpine_Fir\">0.0251</tr_sacrVal>"
      << "<tr_sacrVal species=\"Hybrid_Spruce\">0.0239</tr_sacrVal>"
      << "<tr_sacrVal species=\"Lodgepole_Pine\">0.0303</tr_sacrVal>"
      << "<tr_sacrVal species=\"Trembling_Aspen\">0.0328</tr_sacrVal>"
      << "<tr_sacrVal species=\"Black_Cottonwood\">0.0247</tr_sacrVal>"
      << "<tr_sacrVal species=\"Paper_Birch\">0.0484</tr_sacrVal>"
      << "</tr_stdAsympCrownRad>"
      << "<tr_stdCrownRadExp>"
      << "<tr_screVal species=\"Western_Hemlock\">1.0</tr_screVal>"
      << "<tr_screVal species=\"Western_Redcedar\">1.0</tr_screVal>"
      << "<tr_screVal species=\"Amabilis_Fir\">1.0</tr_screVal>"
      << "<tr_screVal species=\"Subalpine_Fir\">1.0</tr_screVal>"
      << "<tr_screVal species=\"Hybrid_Spruce\">1.0</tr_screVal>"
      << "<tr_screVal species=\"Lodgepole_Pine\">1.0</tr_screVal>"
      << "<tr_screVal species=\"Trembling_Aspen\">1.0</tr_screVal>"
      << "<tr_screVal species=\"Black_Cottonwood\">1.0</tr_screVal>"
      << "<tr_screVal species=\"Paper_Birch\">1.0</tr_screVal>"
      << "</tr_stdCrownRadExp>"
      << "<tr_stdMaxCrownRad>"
      << "<tr_smcrVal species=\"Western_Hemlock\">10</tr_smcrVal>"
      << "<tr_smcrVal species=\"Western_Redcedar\">10</tr_smcrVal>"
      << "<tr_smcrVal species=\"Amabilis_Fir\">10</tr_smcrVal>"
      << "<tr_smcrVal species=\"Subalpine_Fir\">10</tr_smcrVal>"
      << "<tr_smcrVal species=\"Hybrid_Spruce\">10</tr_smcrVal>"
      << "<tr_smcrVal species=\"Lodgepole_Pine\">10</tr_smcrVal>"
      << "<tr_smcrVal species=\"Trembling_Aspen\">10</tr_smcrVal>"
      << "<tr_smcrVal species=\"Black_Cottonwood\">10</tr_smcrVal>"
      << "<tr_smcrVal species=\"Paper_Birch\">10</tr_smcrVal>"
      << "</tr_stdMaxCrownRad>"
      << "<tr_conversionDiam10ToDBH>"
      << "<tr_cdtdVal species=\"Western_Hemlock\">0.8008</tr_cdtdVal>"
      << "<tr_cdtdVal species=\"Western_Redcedar\">0.5944</tr_cdtdVal>"
      << "<tr_cdtdVal species=\"Amabilis_Fir\">0.7059</tr_cdtdVal>"
      << "<tr_cdtdVal species=\"Subalpine_Fir\">0.7776</tr_cdtdVal>"
      << "<tr_cdtdVal species=\"Hybrid_Spruce\">0.6933</tr_cdtdVal>"
      << "<tr_cdtdVal species=\"Lodgepole_Pine\">0.8014</tr_cdtdVal>"
      << "<tr_cdtdVal species=\"Trembling_Aspen\">0.7992</tr_cdtdVal>"
      << "<tr_cdtdVal species=\"Black_Cottonwood\">0.7926</tr_cdtdVal>"
      << "<tr_cdtdVal species=\"Paper_Birch\">0.7803</tr_cdtdVal>"
      << "</tr_conversionDiam10ToDBH>"
      << "<tr_interceptDiam10ToDBH>"
      << "<tr_idtdVal species=\"Western_Hemlock\">0</tr_idtdVal>"
      << "<tr_idtdVal species=\"Western_Redcedar\">0</tr_idtdVal>"
      << "<tr_idtdVal species=\"Amabilis_Fir\">0</tr_idtdVal>"
      << "<tr_idtdVal species=\"Subalpine_Fir\">0</tr_idtdVal>"
      << "<tr_idtdVal species=\"Hybrid_Spruce\">0</tr_idtdVal>"
      << "<tr_idtdVal species=\"Lodgepole_Pine\">0</tr_idtdVal>"
      << "<tr_idtdVal species=\"Trembling_Aspen\">0</tr_idtdVal>"
      << "<tr_idtdVal species=\"Black_Cottonwood\">0</tr_idtdVal>"
      << "<tr_idtdVal species=\"Paper_Birch\">0</tr_idtdVal>"
      << "</tr_interceptDiam10ToDBH>"
      << "<tr_stdAsympCrownHt>"
      << "<tr_sachVal species=\"Western_Hemlock\">0.389</tr_sachVal>"
      << "<tr_sachVal species=\"Western_Redcedar\">0.368</tr_sachVal>"
      << "<tr_sachVal species=\"Amabilis_Fir\">0.464</tr_sachVal>"
      << "<tr_sachVal species=\"Subalpine_Fir\">0.454</tr_sachVal>"
      << "<tr_sachVal species=\"Hybrid_Spruce\">0.405</tr_sachVal>"
      << "<tr_sachVal species=\"Lodgepole_Pine\">0.201</tr_sachVal>"
      << "<tr_sachVal species=\"Trembling_Aspen\">0.301</tr_sachVal>"
      << "<tr_sachVal species=\"Black_Cottonwood\">0.42</tr_sachVal>"
      << "<tr_sachVal species=\"Paper_Birch\">0.315</tr_sachVal>"
      << "</tr_stdAsympCrownHt>"
      << "<tr_stdCrownHtExp>"
      << "<tr_scheVal species=\"Western_Hemlock\">1.0</tr_scheVal>"
      << "<tr_scheVal species=\"Western_Redcedar\">1.0</tr_scheVal>"
      << "<tr_scheVal species=\"Amabilis_Fir\">1.0</tr_scheVal>"
      << "<tr_scheVal species=\"Subalpine_Fir\">1.0</tr_scheVal>"
      << "<tr_scheVal species=\"Hybrid_Spruce\">1.0</tr_scheVal>"
      << "<tr_scheVal species=\"Lodgepole_Pine\">1.0</tr_scheVal>"
      << "<tr_scheVal species=\"Trembling_Aspen\">1.0</tr_scheVal>"
      << "<tr_scheVal species=\"Black_Cottonwood\">1.0</tr_scheVal>"
      << "<tr_scheVal species=\"Paper_Birch\">1.0</tr_scheVal>"
      << "</tr_stdCrownHtExp>"
      << "<tr_slopeOfHeight-Diam10>"
      << "<tr_sohdVal species=\"Western_Hemlock\">0.03418</tr_sohdVal>"
      << "<tr_sohdVal species=\"Western_Redcedar\">0.0269</tr_sohdVal>"
      << "<tr_sohdVal species=\"Amabilis_Fir\">0.02871</tr_sohdVal>"
      << "<tr_sohdVal species=\"Subalpine_Fir\">0.02815</tr_sohdVal>"
      << "<tr_sohdVal species=\"Hybrid_Spruce\">0.02871</tr_sohdVal>"
      << "<tr_sohdVal species=\"Lodgepole_Pine\">0.03224</tr_sohdVal>"
      << "<tr_sohdVal species=\"Trembling_Aspen\">0.04796</tr_sohdVal>"
      << "<tr_sohdVal species=\"Black_Cottonwood\">0.04681</tr_sohdVal>"
      << "<tr_sohdVal species=\"Paper_Birch\">0.04101</tr_sohdVal>"
      << "</tr_slopeOfHeight-Diam10>"
      << "<tr_slopeOfAsymHeight>"
      << "<tr_soahVal species=\"Western_Hemlock\">0.0299</tr_soahVal>"
      << "<tr_soahVal species=\"Western_Redcedar\">0.0241</tr_soahVal>"
      << "<tr_soahVal species=\"Amabilis_Fir\">0.0263</tr_soahVal>"
      << "<tr_soahVal species=\"Subalpine_Fir\">0.0264</tr_soahVal>"
      << "<tr_soahVal species=\"Hybrid_Spruce\">0.0264</tr_soahVal>"
      << "<tr_soahVal species=\"Lodgepole_Pine\">0.0333</tr_soahVal>"
      << "<tr_soahVal species=\"Trembling_Aspen\">0.0352</tr_soahVal>"
      << "<tr_soahVal species=\"Black_Cottonwood\">0.0347</tr_soahVal>"
      << "<tr_soahVal species=\"Paper_Birch\">0.0454</tr_soahVal>"
      << "</tr_slopeOfAsymHeight>"
      << "<tr_whatSeedlingHeightDiam>"
      << "<tr_wsehdVal species=\"Western_Hemlock\">0</tr_wsehdVal>"
      << "<tr_wsehdVal species=\"Western_Redcedar\">0</tr_wsehdVal>"
      << "<tr_wsehdVal species=\"Amabilis_Fir\">0</tr_wsehdVal>"
      << "<tr_wsehdVal species=\"Subalpine_Fir\">0</tr_wsehdVal>"
      << "<tr_wsehdVal species=\"Hybrid_Spruce\">0</tr_wsehdVal>"
      << "<tr_wsehdVal species=\"Lodgepole_Pine\">0</tr_wsehdVal>"
      << "<tr_wsehdVal species=\"Trembling_Aspen\">0</tr_wsehdVal>"
      << "<tr_wsehdVal species=\"Black_Cottonwood\">0</tr_wsehdVal>"
      << "<tr_wsehdVal species=\"Paper_Birch\">0</tr_wsehdVal>"
      << "</tr_whatSeedlingHeightDiam>"
      << "<tr_whatSaplingHeightDiam>"
      << "<tr_wsahdVal species=\"Western_Hemlock\">0</tr_wsahdVal>"
      << "<tr_wsahdVal species=\"Western_Redcedar\">0</tr_wsahdVal>"
      << "<tr_wsahdVal species=\"Amabilis_Fir\">0</tr_wsahdVal>"
      << "<tr_wsahdVal species=\"Subalpine_Fir\">0</tr_wsahdVal>"
      << "<tr_wsahdVal species=\"Hybrid_Spruce\">0</tr_wsahdVal>"
      << "<tr_wsahdVal species=\"Lodgepole_Pine\">0</tr_wsahdVal>"
      << "<tr_wsahdVal species=\"Trembling_Aspen\">0</tr_wsahdVal>"
      << "<tr_wsahdVal species=\"Black_Cottonwood\">0</tr_wsahdVal>"
      << "<tr_wsahdVal species=\"Paper_Birch\">0</tr_wsahdVal>"
      << "</tr_whatSaplingHeightDiam>"
      << "<tr_whatAdultHeightDiam>"
      << "<tr_wahdVal species=\"Western_Hemlock\">0</tr_wahdVal>"
      << "<tr_wahdVal species=\"Western_Redcedar\">0</tr_wahdVal>"
      << "<tr_wahdVal species=\"Amabilis_Fir\">0</tr_wahdVal>"
      << "<tr_wahdVal species=\"Subalpine_Fir\">0</tr_wahdVal>"
      << "<tr_wahdVal species=\"Hybrid_Spruce\">0</tr_wahdVal>"
      << "<tr_wahdVal species=\"Lodgepole_Pine\">0</tr_wahdVal>"
      << "<tr_wahdVal species=\"Trembling_Aspen\">0</tr_wahdVal>"
      << "<tr_wahdVal species=\"Black_Cottonwood\">0</tr_wahdVal>"
      << "<tr_wahdVal species=\"Paper_Birch\">0</tr_wahdVal>"
      << "</tr_whatAdultHeightDiam>"
      << "<tr_whatAdultCrownRadDiam>"
      << "<tr_wacrdVal species=\"Western_Hemlock\">0</tr_wacrdVal>"
      << "<tr_wacrdVal species=\"Western_Redcedar\">0</tr_wacrdVal>"
      << "<tr_wacrdVal species=\"Amabilis_Fir\">0</tr_wacrdVal>"
      << "<tr_wacrdVal species=\"Subalpine_Fir\">0</tr_wacrdVal>"
      << "<tr_wacrdVal species=\"Hybrid_Spruce\">0</tr_wacrdVal>"
      << "<tr_wacrdVal species=\"Lodgepole_Pine\">0</tr_wacrdVal>"
      << "<tr_wacrdVal species=\"Trembling_Aspen\">0</tr_wacrdVal>"
      << "<tr_wacrdVal species=\"Black_Cottonwood\">0</tr_wacrdVal>"
      << "<tr_wacrdVal species=\"Paper_Birch\">0</tr_wacrdVal>"
      << "</tr_whatAdultCrownRadDiam>"
      << "<tr_whatAdultCrownHeightHeight>"
      << "<tr_wachhVal species=\"Western_Hemlock\">0</tr_wachhVal>"
      << "<tr_wachhVal species=\"Western_Redcedar\">0</tr_wachhVal>"
      << "<tr_wachhVal species=\"Amabilis_Fir\">0</tr_wachhVal>"
      << "<tr_wachhVal species=\"Subalpine_Fir\">0</tr_wachhVal>"
      << "<tr_wachhVal species=\"Hybrid_Spruce\">0</tr_wachhVal>"
      << "<tr_wachhVal species=\"Lodgepole_Pine\">0</tr_wachhVal>"
      << "<tr_wachhVal species=\"Trembling_Aspen\">0</tr_wachhVal>"
      << "<tr_wachhVal species=\"Black_Cottonwood\">0</tr_wachhVal>"
      << "<tr_wachhVal species=\"Paper_Birch\">0</tr_wachhVal>"
      << "</tr_whatAdultCrownHeightHeight>"
      << "<tr_whatSaplingCrownRadDiam>"
      << "<tr_wscrdVal species=\"Western_Hemlock\">0</tr_wscrdVal>"
      << "<tr_wscrdVal species=\"Western_Redcedar\">0</tr_wscrdVal>"
      << "<tr_wscrdVal species=\"Amabilis_Fir\">0</tr_wscrdVal>"
      << "<tr_wscrdVal species=\"Subalpine_Fir\">0</tr_wscrdVal>"
      << "<tr_wscrdVal species=\"Hybrid_Spruce\">0</tr_wscrdVal>"
      << "<tr_wscrdVal species=\"Lodgepole_Pine\">0</tr_wscrdVal>"
      << "<tr_wscrdVal species=\"Trembling_Aspen\">0</tr_wscrdVal>"
      << "<tr_wscrdVal species=\"Black_Cottonwood\">0</tr_wscrdVal>"
      << "<tr_wscrdVal species=\"Paper_Birch\">0</tr_wscrdVal>"
      << "</tr_whatSaplingCrownRadDiam>"
      << "<tr_whatSaplingCrownHeightHeight>"
      << "<tr_wschhVal species=\"Western_Hemlock\">0</tr_wschhVal>"
      << "<tr_wschhVal species=\"Western_Redcedar\">0</tr_wschhVal>"
      << "<tr_wschhVal species=\"Amabilis_Fir\">0</tr_wschhVal>"
      << "<tr_wschhVal species=\"Subalpine_Fir\">0</tr_wschhVal>"
      << "<tr_wschhVal species=\"Hybrid_Spruce\">0</tr_wschhVal>"
      << "<tr_wschhVal species=\"Lodgepole_Pine\">0</tr_wschhVal>"
      << "<tr_wschhVal species=\"Trembling_Aspen\">0</tr_wschhVal>"
      << "<tr_wschhVal species=\"Black_Cottonwood\">0</tr_wschhVal>"
      << "<tr_wschhVal species=\"Paper_Birch\">0</tr_wschhVal>"
      << "</tr_whatSaplingCrownHeightHeight>"
      << "</allometry>"
      << "<behaviorList>"
      << "<behavior>"
      << "<behaviorName>Plant</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>1</listPosition>"
      << "</behavior>"
      << "</behaviorList>"
      << "<Plant1>"
      << "<pl_initialDiam10>"
      << "<pl_idVal species=\"Hybrid_Spruce\">0.5</pl_idVal>"
      << "<pl_idVal species=\"Lodgepole_Pine\">0.6</pl_idVal>"
      << "<pl_idVal species=\"Trembling_Aspen\">0.7</pl_idVal>"
      << "<pl_idVal species=\"Black_Cottonwood\">0.8</pl_idVal>"
      << "<pl_idVal species=\"Western_Hemlock\">0.1</pl_idVal>"
      << "<pl_idVal species=\"Western_Redcedar\">0.2</pl_idVal>"
      << "<pl_idVal species=\"Amabilis_Fir\">0.3</pl_idVal>"
      << "<pl_idVal species=\"Subalpine_Fir\">0.4</pl_idVal>"
      << "<pl_idVal species=\"Paper_Birch\">0.9</pl_idVal>"
      << "</pl_initialDiam10>"
      << "<pl_plantEvent>"
      << "<pl_applyToSpecies species=\"Western_Redcedar\" />"
      << "<pl_applyToSpecies species=\"Western_Hemlock\" />"
      << "<pl_applyToSpecies species=\"Amabilis_Fir\" />"
      << "<pl_timestep>1</pl_timestep>"
      << "<pl_spaceType>random</pl_spaceType>"
      << "<pl_distanceOrDensity>150</pl_distanceOrDensity>"
      << "<pl_amountToPlant>"
      << "<pl_atpVal species=\"Western_Hemlock\">25</pl_atpVal>"
      << "<pl_atpVal species=\"Western_Redcedar\">35</pl_atpVal>"
      << "<pl_atpVal species=\"Amabilis_Fir\">40</pl_atpVal>"
      << "</pl_amountToPlant>";
  for (i = 0; i < 3; i++) {
    for (int j = 0; j < 25; j++) {
      oOut << "<pl_applyToCell x=\"" << i << "\" y=\"" << j << "\" /> ";
    }
  }
  i = 5;
  for (j = 0; j < 25; j++) {
    oOut << "<pl_applyToCell x=\"" << i << "\" y=\"" << j << "\" /> ";
  }

  oOut << "</pl_plantEvent>"
      << "<pl_plantEvent>"
      << "<pl_applyToSpecies species=\"Black_Cottonwood\" />"
      << "<pl_applyToSpecies species=\"Paper_Birch\" />"
      << "<pl_timestep>1</pl_timestep>"
      << "<pl_spaceType>gridded</pl_spaceType>"
      << "<pl_distanceOrDensity>3</pl_distanceOrDensity>"
      << "<pl_amountToPlant>"
      << "<pl_atpVal species=\"Black_Cottonwood\">40</pl_atpVal>"
      << "<pl_atpVal species=\"Paper_Birch\">60</pl_atpVal>"
      << "</pl_amountToPlant>";
  for (int i = 0; i < 25; i++) {
    for (int j = 0; j < 3; j++) {
      oOut << "<pl_applyToCell x=\"" << i << "\" y=\"" << j << "\" /> ";
    }
  }
  for (int i = 6; i < 12; i++) {
    for (int j = 5; j < 11; j++) {
      oOut << "<pl_applyToCell x=\"" << i << "\" y=\"" << j << "\" /> ";
    }
  }
  oOut << "</pl_plantEvent>"
      << "</Plant1>"
      << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WritePlantingXMLFile4()
/////////////////////////////////////////////////////////////////////////////
const char* WritePlantingXMLFile4()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  std::fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
      << "<paramFile fileCode=\"06010101\">" << "<plot>"
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
      << "<tr_species speciesName=\"Western_Hemlock\"/>"
      << "<tr_species speciesName=\"Western_Redcedar\"/>"
      << "<tr_species speciesName=\"Amabilis_Fir\"/>"
      << "<tr_species speciesName=\"Subalpine_Fir\"/>"
      << "<tr_species speciesName=\"Hybrid_Spruce\"/>"
      << "<tr_species speciesName=\"Lodgepole_Pine\"/>"
      << "<tr_species speciesName=\"Trembling_Aspen\"/>"
      << "<tr_species speciesName=\"Black_Cottonwood\"/>"
      << "<tr_species speciesName=\"Paper_Birch\"/>"
      << "</tr_speciesList>"
      << "<tr_seedDiam10Cm>0.1</tr_seedDiam10Cm>"
      << "<tr_minAdultDBH>"
      << "<tr_madVal species=\"Western_Hemlock\">10</tr_madVal>"
      << "<tr_madVal species=\"Western_Redcedar\">10</tr_madVal>"
      << "<tr_madVal species=\"Amabilis_Fir\">10</tr_madVal>"
      << "<tr_madVal species=\"Subalpine_Fir\">10</tr_madVal>"
      << "<tr_madVal species=\"Hybrid_Spruce\">10</tr_madVal>"
      << "<tr_madVal species=\"Lodgepole_Pine\">10</tr_madVal>"
      << "<tr_madVal species=\"Trembling_Aspen\">10</tr_madVal>"
      << "<tr_madVal species=\"Black_Cottonwood\">10</tr_madVal>"
      << "<tr_madVal species=\"Paper_Birch\">10</tr_madVal>"
      << "</tr_minAdultDBH>"
      << "<tr_maxSeedlingHeight>"
      << "<tr_mshVal species=\"Western_Hemlock\">1.35</tr_mshVal>"
      << "<tr_mshVal species=\"Western_Redcedar\">1.35</tr_mshVal>"
      << "<tr_mshVal species=\"Amabilis_Fir\">1.35</tr_mshVal>"
      << "<tr_mshVal species=\"Subalpine_Fir\">1.35</tr_mshVal>"
      << "<tr_mshVal species=\"Hybrid_Spruce\">1.35</tr_mshVal>"
      << "<tr_mshVal species=\"Lodgepole_Pine\">1.35</tr_mshVal>"
      << "<tr_mshVal species=\"Trembling_Aspen\">1.35</tr_mshVal>"
      << "<tr_mshVal species=\"Black_Cottonwood\">1.35</tr_mshVal>"
      << "<tr_mshVal species=\"Paper_Birch\">1.35</tr_mshVal>"
      << "</tr_maxSeedlingHeight>"
      << "</trees>"
      << "<allometry>"
      << "<tr_canopyHeight>"
      << "<tr_chVal species=\"Western_Hemlock\">39.48</tr_chVal>"
      << "<tr_chVal species=\"Western_Redcedar\">39.54</tr_chVal>"
      << "<tr_chVal species=\"Amabilis_Fir\">40</tr_chVal>"
      << "<tr_chVal species=\"Subalpine_Fir\">40</tr_chVal>"
      << "<tr_chVal species=\"Hybrid_Spruce\">45</tr_chVal>"
      << "<tr_chVal species=\"Lodgepole_Pine\">40</tr_chVal>"
      << "<tr_chVal species=\"Trembling_Aspen\">39.14</tr_chVal>"
      << "<tr_chVal species=\"Black_Cottonwood\">39.47</tr_chVal>"
      << "<tr_chVal species=\"Paper_Birch\">33.18</tr_chVal>"
      << "</tr_canopyHeight>"
      << "<tr_stdAsympCrownRad>"
      << "<tr_sacrVal species=\"Western_Hemlock\">0.0549</tr_sacrVal>"
      << "<tr_sacrVal species=\"Western_Redcedar\">0.0614</tr_sacrVal>"
      << "<tr_sacrVal species=\"Amabilis_Fir\">0.0242</tr_sacrVal>"
      << "<tr_sacrVal species=\"Subalpine_Fir\">0.0251</tr_sacrVal>"
      << "<tr_sacrVal species=\"Hybrid_Spruce\">0.0239</tr_sacrVal>"
      << "<tr_sacrVal species=\"Lodgepole_Pine\">0.0303</tr_sacrVal>"
      << "<tr_sacrVal species=\"Trembling_Aspen\">0.0328</tr_sacrVal>"
      << "<tr_sacrVal species=\"Black_Cottonwood\">0.0247</tr_sacrVal>"
      << "<tr_sacrVal species=\"Paper_Birch\">0.0484</tr_sacrVal>"
      << "</tr_stdAsympCrownRad>"
      << "<tr_stdCrownRadExp>"
      << "<tr_screVal species=\"Western_Hemlock\">1.0</tr_screVal>"
      << "<tr_screVal species=\"Western_Redcedar\">1.0</tr_screVal>"
      << "<tr_screVal species=\"Amabilis_Fir\">1.0</tr_screVal>"
      << "<tr_screVal species=\"Subalpine_Fir\">1.0</tr_screVal>"
      << "<tr_screVal species=\"Hybrid_Spruce\">1.0</tr_screVal>"
      << "<tr_screVal species=\"Lodgepole_Pine\">1.0</tr_screVal>"
      << "<tr_screVal species=\"Trembling_Aspen\">1.0</tr_screVal>"
      << "<tr_screVal species=\"Black_Cottonwood\">1.0</tr_screVal>"
      << "<tr_screVal species=\"Paper_Birch\">1.0</tr_screVal>"
      << "</tr_stdCrownRadExp>"
      << "<tr_stdMaxCrownRad>"
      << "<tr_smcrVal species=\"Western_Hemlock\">10</tr_smcrVal>"
      << "<tr_smcrVal species=\"Western_Redcedar\">10</tr_smcrVal>"
      << "<tr_smcrVal species=\"Amabilis_Fir\">10</tr_smcrVal>"
      << "<tr_smcrVal species=\"Subalpine_Fir\">10</tr_smcrVal>"
      << "<tr_smcrVal species=\"Hybrid_Spruce\">10</tr_smcrVal>"
      << "<tr_smcrVal species=\"Lodgepole_Pine\">10</tr_smcrVal>"
      << "<tr_smcrVal species=\"Trembling_Aspen\">10</tr_smcrVal>"
      << "<tr_smcrVal species=\"Black_Cottonwood\">10</tr_smcrVal>"
      << "<tr_smcrVal species=\"Paper_Birch\">10</tr_smcrVal>"
      << "</tr_stdMaxCrownRad>"
      << "<tr_conversionDiam10ToDBH>"
      << "<tr_cdtdVal species=\"Western_Hemlock\">0.8008</tr_cdtdVal>"
      << "<tr_cdtdVal species=\"Western_Redcedar\">0.5944</tr_cdtdVal>"
      << "<tr_cdtdVal species=\"Amabilis_Fir\">0.7059</tr_cdtdVal>"
      << "<tr_cdtdVal species=\"Subalpine_Fir\">0.7776</tr_cdtdVal>"
      << "<tr_cdtdVal species=\"Hybrid_Spruce\">0.6933</tr_cdtdVal>"
      << "<tr_cdtdVal species=\"Lodgepole_Pine\">0.8014</tr_cdtdVal>"
      << "<tr_cdtdVal species=\"Trembling_Aspen\">0.7992</tr_cdtdVal>"
      << "<tr_cdtdVal species=\"Black_Cottonwood\">0.7926</tr_cdtdVal>"
      << "<tr_cdtdVal species=\"Paper_Birch\">0.7803</tr_cdtdVal>"
      << "</tr_conversionDiam10ToDBH>"
      << "<tr_interceptDiam10ToDBH>"
      << "<tr_idtdVal species=\"Western_Hemlock\">0</tr_idtdVal>"
      << "<tr_idtdVal species=\"Western_Redcedar\">0</tr_idtdVal>"
      << "<tr_idtdVal species=\"Amabilis_Fir\">0</tr_idtdVal>"
      << "<tr_idtdVal species=\"Subalpine_Fir\">0</tr_idtdVal>"
      << "<tr_idtdVal species=\"Hybrid_Spruce\">0</tr_idtdVal>"
      << "<tr_idtdVal species=\"Lodgepole_Pine\">0</tr_idtdVal>"
      << "<tr_idtdVal species=\"Trembling_Aspen\">0</tr_idtdVal>"
      << "<tr_idtdVal species=\"Black_Cottonwood\">0</tr_idtdVal>"
      << "<tr_idtdVal species=\"Paper_Birch\">0</tr_idtdVal>"
      << "</tr_interceptDiam10ToDBH>"
      << "<tr_stdAsympCrownHt>"
      << "<tr_sachVal species=\"Western_Hemlock\">0.389</tr_sachVal>"
      << "<tr_sachVal species=\"Western_Redcedar\">0.368</tr_sachVal>"
      << "<tr_sachVal species=\"Amabilis_Fir\">0.464</tr_sachVal>"
      << "<tr_sachVal species=\"Subalpine_Fir\">0.454</tr_sachVal>"
      << "<tr_sachVal species=\"Hybrid_Spruce\">0.405</tr_sachVal>"
      << "<tr_sachVal species=\"Lodgepole_Pine\">0.201</tr_sachVal>"
      << "<tr_sachVal species=\"Trembling_Aspen\">0.301</tr_sachVal>"
      << "<tr_sachVal species=\"Black_Cottonwood\">0.42</tr_sachVal>"
      << "<tr_sachVal species=\"Paper_Birch\">0.315</tr_sachVal>"
      << "</tr_stdAsympCrownHt>"
      << "<tr_stdCrownHtExp>"
      << "<tr_scheVal species=\"Western_Hemlock\">1.0</tr_scheVal>"
      << "<tr_scheVal species=\"Western_Redcedar\">1.0</tr_scheVal>"
      << "<tr_scheVal species=\"Amabilis_Fir\">1.0</tr_scheVal>"
      << "<tr_scheVal species=\"Subalpine_Fir\">1.0</tr_scheVal>"
      << "<tr_scheVal species=\"Hybrid_Spruce\">1.0</tr_scheVal>"
      << "<tr_scheVal species=\"Lodgepole_Pine\">1.0</tr_scheVal>"
      << "<tr_scheVal species=\"Trembling_Aspen\">1.0</tr_scheVal>"
      << "<tr_scheVal species=\"Black_Cottonwood\">1.0</tr_scheVal>"
      << "<tr_scheVal species=\"Paper_Birch\">1.0</tr_scheVal>"
      << "</tr_stdCrownHtExp>"
      << "<tr_slopeOfHeight-Diam10>"
      << "<tr_sohdVal species=\"Western_Hemlock\">0.03418</tr_sohdVal>"
      << "<tr_sohdVal species=\"Western_Redcedar\">0.0269</tr_sohdVal>"
      << "<tr_sohdVal species=\"Amabilis_Fir\">0.02871</tr_sohdVal>"
      << "<tr_sohdVal species=\"Subalpine_Fir\">0.02815</tr_sohdVal>"
      << "<tr_sohdVal species=\"Hybrid_Spruce\">0.02871</tr_sohdVal>"
      << "<tr_sohdVal species=\"Lodgepole_Pine\">0.03224</tr_sohdVal>"
      << "<tr_sohdVal species=\"Trembling_Aspen\">0.04796</tr_sohdVal>"
      << "<tr_sohdVal species=\"Black_Cottonwood\">0.04681</tr_sohdVal>"
      << "<tr_sohdVal species=\"Paper_Birch\">0.04101</tr_sohdVal>"
      << "</tr_slopeOfHeight-Diam10>"
      << "<tr_slopeOfAsymHeight>"
      << "<tr_soahVal species=\"Western_Hemlock\">0.0299</tr_soahVal>"
      << "<tr_soahVal species=\"Western_Redcedar\">0.0241</tr_soahVal>"
      << "<tr_soahVal species=\"Amabilis_Fir\">0.0263</tr_soahVal>"
      << "<tr_soahVal species=\"Subalpine_Fir\">0.0264</tr_soahVal>"
      << "<tr_soahVal species=\"Hybrid_Spruce\">0.0264</tr_soahVal>"
      << "<tr_soahVal species=\"Lodgepole_Pine\">0.0333</tr_soahVal>"
      << "<tr_soahVal species=\"Trembling_Aspen\">0.0352</tr_soahVal>"
      << "<tr_soahVal species=\"Black_Cottonwood\">0.0347</tr_soahVal>"
      << "<tr_soahVal species=\"Paper_Birch\">0.0454</tr_soahVal>"
      << "</tr_slopeOfAsymHeight>"
      << "<tr_whatSeedlingHeightDiam>"
      << "<tr_wsehdVal species=\"Western_Hemlock\">0</tr_wsehdVal>"
      << "<tr_wsehdVal species=\"Western_Redcedar\">0</tr_wsehdVal>"
      << "<tr_wsehdVal species=\"Amabilis_Fir\">0</tr_wsehdVal>"
      << "<tr_wsehdVal species=\"Subalpine_Fir\">0</tr_wsehdVal>"
      << "<tr_wsehdVal species=\"Hybrid_Spruce\">0</tr_wsehdVal>"
      << "<tr_wsehdVal species=\"Lodgepole_Pine\">0</tr_wsehdVal>"
      << "<tr_wsehdVal species=\"Trembling_Aspen\">0</tr_wsehdVal>"
      << "<tr_wsehdVal species=\"Black_Cottonwood\">0</tr_wsehdVal>"
      << "<tr_wsehdVal species=\"Paper_Birch\">0</tr_wsehdVal>"
      << "</tr_whatSeedlingHeightDiam>"
      << "<tr_whatSaplingHeightDiam>"
      << "<tr_wsahdVal species=\"Western_Hemlock\">0</tr_wsahdVal>"
      << "<tr_wsahdVal species=\"Western_Redcedar\">0</tr_wsahdVal>"
      << "<tr_wsahdVal species=\"Amabilis_Fir\">0</tr_wsahdVal>"
      << "<tr_wsahdVal species=\"Subalpine_Fir\">0</tr_wsahdVal>"
      << "<tr_wsahdVal species=\"Hybrid_Spruce\">0</tr_wsahdVal>"
      << "<tr_wsahdVal species=\"Lodgepole_Pine\">0</tr_wsahdVal>"
      << "<tr_wsahdVal species=\"Trembling_Aspen\">0</tr_wsahdVal>"
      << "<tr_wsahdVal species=\"Black_Cottonwood\">0</tr_wsahdVal>"
      << "<tr_wsahdVal species=\"Paper_Birch\">0</tr_wsahdVal>"
      << "</tr_whatSaplingHeightDiam>"
      << "<tr_whatAdultHeightDiam>"
      << "<tr_wahdVal species=\"Western_Hemlock\">0</tr_wahdVal>"
      << "<tr_wahdVal species=\"Western_Redcedar\">0</tr_wahdVal>"
      << "<tr_wahdVal species=\"Amabilis_Fir\">0</tr_wahdVal>"
      << "<tr_wahdVal species=\"Subalpine_Fir\">0</tr_wahdVal>"
      << "<tr_wahdVal species=\"Hybrid_Spruce\">0</tr_wahdVal>"
      << "<tr_wahdVal species=\"Lodgepole_Pine\">0</tr_wahdVal>"
      << "<tr_wahdVal species=\"Trembling_Aspen\">0</tr_wahdVal>"
      << "<tr_wahdVal species=\"Black_Cottonwood\">0</tr_wahdVal>"
      << "<tr_wahdVal species=\"Paper_Birch\">0</tr_wahdVal>"
      << "</tr_whatAdultHeightDiam>"
      << "<tr_whatAdultCrownRadDiam>"
      << "<tr_wacrdVal species=\"Western_Hemlock\">0</tr_wacrdVal>"
      << "<tr_wacrdVal species=\"Western_Redcedar\">0</tr_wacrdVal>"
      << "<tr_wacrdVal species=\"Amabilis_Fir\">0</tr_wacrdVal>"
      << "<tr_wacrdVal species=\"Subalpine_Fir\">0</tr_wacrdVal>"
      << "<tr_wacrdVal species=\"Hybrid_Spruce\">0</tr_wacrdVal>"
      << "<tr_wacrdVal species=\"Lodgepole_Pine\">0</tr_wacrdVal>"
      << "<tr_wacrdVal species=\"Trembling_Aspen\">0</tr_wacrdVal>"
      << "<tr_wacrdVal species=\"Black_Cottonwood\">0</tr_wacrdVal>"
      << "<tr_wacrdVal species=\"Paper_Birch\">0</tr_wacrdVal>"
      << "</tr_whatAdultCrownRadDiam>"
      << "<tr_whatAdultCrownHeightHeight>"
      << "<tr_wachhVal species=\"Western_Hemlock\">0</tr_wachhVal>"
      << "<tr_wachhVal species=\"Western_Redcedar\">0</tr_wachhVal>"
      << "<tr_wachhVal species=\"Amabilis_Fir\">0</tr_wachhVal>"
      << "<tr_wachhVal species=\"Subalpine_Fir\">0</tr_wachhVal>"
      << "<tr_wachhVal species=\"Hybrid_Spruce\">0</tr_wachhVal>"
      << "<tr_wachhVal species=\"Lodgepole_Pine\">0</tr_wachhVal>"
      << "<tr_wachhVal species=\"Trembling_Aspen\">0</tr_wachhVal>"
      << "<tr_wachhVal species=\"Black_Cottonwood\">0</tr_wachhVal>"
      << "<tr_wachhVal species=\"Paper_Birch\">0</tr_wachhVal>"
      << "</tr_whatAdultCrownHeightHeight>"
      << "<tr_whatSaplingCrownRadDiam>"
      << "<tr_wscrdVal species=\"Western_Hemlock\">0</tr_wscrdVal>"
      << "<tr_wscrdVal species=\"Western_Redcedar\">0</tr_wscrdVal>"
      << "<tr_wscrdVal species=\"Amabilis_Fir\">0</tr_wscrdVal>"
      << "<tr_wscrdVal species=\"Subalpine_Fir\">0</tr_wscrdVal>"
      << "<tr_wscrdVal species=\"Hybrid_Spruce\">0</tr_wscrdVal>"
      << "<tr_wscrdVal species=\"Lodgepole_Pine\">0</tr_wscrdVal>"
      << "<tr_wscrdVal species=\"Trembling_Aspen\">0</tr_wscrdVal>"
      << "<tr_wscrdVal species=\"Black_Cottonwood\">0</tr_wscrdVal>"
      << "<tr_wscrdVal species=\"Paper_Birch\">0</tr_wscrdVal>"
      << "</tr_whatSaplingCrownRadDiam>"
      << "<tr_whatSaplingCrownHeightHeight>"
      << "<tr_wschhVal species=\"Western_Hemlock\">0</tr_wschhVal>"
      << "<tr_wschhVal species=\"Western_Redcedar\">0</tr_wschhVal>"
      << "<tr_wschhVal species=\"Amabilis_Fir\">0</tr_wschhVal>"
      << "<tr_wschhVal species=\"Subalpine_Fir\">0</tr_wschhVal>"
      << "<tr_wschhVal species=\"Hybrid_Spruce\">0</tr_wschhVal>"
      << "<tr_wschhVal species=\"Lodgepole_Pine\">0</tr_wschhVal>"
      << "<tr_wschhVal species=\"Trembling_Aspen\">0</tr_wschhVal>"
      << "<tr_wschhVal species=\"Black_Cottonwood\">0</tr_wschhVal>"
      << "<tr_wschhVal species=\"Paper_Birch\">0</tr_wschhVal>"
      << "</tr_whatSaplingCrownHeightHeight>"
      << "</allometry>"
      << "<behaviorList>"
      << "<behavior>"
      << "<behaviorName>Plant</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>1</listPosition>"
      << "</behavior>"
      << "</behaviorList>"
      << "<Plant1>"
      << "<pl_plantEvent>"
      << "<pl_applyToSpecies species=\"Lodgepole_Pine\" />"
      << "<pl_applyToSpecies species=\"Subalpine_Fir\" />"
      << "<pl_applyToSpecies species=\"Hybrid_Spruce\" />"
      << "<pl_applyToSpecies species=\"Trembling_Aspen\" />"
      << "<pl_applyToSpecies species=\"Black_Cottonwood\" />"
      << "<pl_applyToSpecies species=\"Western_Hemlock\" />"
      << "<pl_applyToSpecies species=\"Western_Redcedar\" />"
      << "<pl_applyToSpecies species=\"Amabilis_Fir\" />"
      << "<pl_applyToSpecies species=\"Paper_Birch\" />"
      << "<pl_timestep>2</pl_timestep>"
      << "<pl_spaceType>random</pl_spaceType>"
      << "<pl_distanceOrDensity>1406.25</pl_distanceOrDensity>"
      << "<pl_amountToPlant>"
      << "<pl_atpVal species=\"Western_Hemlock\">11.11</pl_atpVal>"
      << "<pl_atpVal species=\"Western_Redcedar\">11.11</pl_atpVal>"
      << "<pl_atpVal species=\"Amabilis_Fir\">11.11</pl_atpVal>"
      << "<pl_atpVal species=\"Subalpine_Fir\">11.11</pl_atpVal>"
      << "<pl_atpVal species=\"Hybrid_Spruce\">11.11</pl_atpVal>"
      << "<pl_atpVal species=\"Lodgepole_Pine\">11.11</pl_atpVal>"
      << "<pl_atpVal species=\"Trembling_Aspen\">11.11</pl_atpVal>"
      << "<pl_atpVal species=\"Black_Cottonwood\">11.11</pl_atpVal>"
      << "<pl_atpVal species=\"Paper_Birch\">11.12</pl_atpVal>"
      << "</pl_amountToPlant>"
      << "<pl_applyToCell x=\"24\" y=\"24\" /> ";
  oOut << "</pl_plantEvent>"
      << "<pl_plantEvent>"
      << "<pl_applyToSpecies species=\"Lodgepole_Pine\" />"
      << "<pl_applyToSpecies species=\"Subalpine_Fir\" />"
      << "<pl_applyToSpecies species=\"Hybrid_Spruce\" />"
      << "<pl_applyToSpecies species=\"Trembling_Aspen\" />"
      << "<pl_applyToSpecies species=\"Black_Cottonwood\" />"
      << "<pl_applyToSpecies species=\"Western_Hemlock\" />"
      << "<pl_applyToSpecies species=\"Western_Redcedar\" />"
      << "<pl_applyToSpecies species=\"Amabilis_Fir\" />"
      << "<pl_applyToSpecies species=\"Paper_Birch\" />"
      << "<pl_timestep>3</pl_timestep>"
      << "<pl_spaceType>gridded</pl_spaceType>"
      << "<pl_distanceOrDensity>2</pl_distanceOrDensity>"
      << "<pl_amountToPlant>"
      << "<pl_atpVal species=\"Western_Hemlock\">11.11</pl_atpVal>"
      << "<pl_atpVal species=\"Western_Redcedar\">11.11</pl_atpVal>"
      << "<pl_atpVal species=\"Amabilis_Fir\">11.11</pl_atpVal>"
      << "<pl_atpVal species=\"Subalpine_Fir\">11.11</pl_atpVal>"
      << "<pl_atpVal species=\"Hybrid_Spruce\">11.11</pl_atpVal>"
      << "<pl_atpVal species=\"Lodgepole_Pine\">11.11</pl_atpVal>"
      << "<pl_atpVal species=\"Trembling_Aspen\">11.11</pl_atpVal>"
      << "<pl_atpVal species=\"Black_Cottonwood\">11.11</pl_atpVal>"
      << "<pl_atpVal species=\"Paper_Birch\">11.12</pl_atpVal>"
      << "</pl_amountToPlant>"
      << "<pl_applyToCell x=\"23\" y=\"23\" /> ";
  oOut << "</pl_plantEvent>"
      << "</Plant1>"
      << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WritePlantingXMLFile5()
/////////////////////////////////////////////////////////////////////////////
const char* WritePlantingXMLFile5()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  std::fstream oOut;
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
      << "</plot>"
      << "<trees>"
      << "<tr_speciesList>"
      << "<tr_species speciesName=\"Western_Hemlock\"/>"
      << "<tr_species speciesName=\"Western_Redcedar\"/>"
      << "<tr_species speciesName=\"Amabilis_Fir\"/>"
      << "<tr_species speciesName=\"Subalpine_Fir\"/>"
      << "<tr_species speciesName=\"Hybrid_Spruce\"/>"
      << "<tr_species speciesName=\"Lodgepole_Pine\"/>"
      << "<tr_species speciesName=\"Trembling_Aspen\"/>"
      << "<tr_species speciesName=\"Black_Cottonwood\"/>"
      << "<tr_species speciesName=\"Paper_Birch\"/>"
      << "</tr_speciesList>"
      << "<tr_seedDiam10Cm>0.1</tr_seedDiam10Cm>"
      << "<tr_minAdultDBH>"
      << "<tr_madVal species=\"Western_Hemlock\">10</tr_madVal>"
      << "<tr_madVal species=\"Western_Redcedar\">10</tr_madVal>"
      << "<tr_madVal species=\"Amabilis_Fir\">10</tr_madVal>"
      << "<tr_madVal species=\"Subalpine_Fir\">10</tr_madVal>"
      << "<tr_madVal species=\"Hybrid_Spruce\">10</tr_madVal>"
      << "<tr_madVal species=\"Lodgepole_Pine\">10</tr_madVal>"
      << "<tr_madVal species=\"Trembling_Aspen\">10</tr_madVal>"
      << "<tr_madVal species=\"Black_Cottonwood\">10</tr_madVal>"
      << "<tr_madVal species=\"Paper_Birch\">10</tr_madVal>"
      << "</tr_minAdultDBH>"
      << "<tr_maxSeedlingHeight>"
      << "<tr_mshVal species=\"Western_Hemlock\">1.35</tr_mshVal>"
      << "<tr_mshVal species=\"Western_Redcedar\">1.35</tr_mshVal>"
      << "<tr_mshVal species=\"Amabilis_Fir\">1.35</tr_mshVal>"
      << "<tr_mshVal species=\"Subalpine_Fir\">1.35</tr_mshVal>"
      << "<tr_mshVal species=\"Hybrid_Spruce\">1.35</tr_mshVal>"
      << "<tr_mshVal species=\"Lodgepole_Pine\">1.35</tr_mshVal>"
      << "<tr_mshVal species=\"Trembling_Aspen\">1.35</tr_mshVal>"
      << "<tr_mshVal species=\"Black_Cottonwood\">1.35</tr_mshVal>"
      << "<tr_mshVal species=\"Paper_Birch\">1.35</tr_mshVal>"
      << "</tr_maxSeedlingHeight>"
      << "</trees>"
      << "<allometry>"
      << "<tr_canopyHeight>"
      << "<tr_chVal species=\"Western_Hemlock\">39.48</tr_chVal>"
      << "<tr_chVal species=\"Western_Redcedar\">39.54</tr_chVal>"
      << "<tr_chVal species=\"Amabilis_Fir\">40</tr_chVal>"
      << "<tr_chVal species=\"Subalpine_Fir\">40</tr_chVal>"
      << "<tr_chVal species=\"Hybrid_Spruce\">45</tr_chVal>"
      << "<tr_chVal species=\"Lodgepole_Pine\">40</tr_chVal>"
      << "<tr_chVal species=\"Trembling_Aspen\">39.14</tr_chVal>"
      << "<tr_chVal species=\"Black_Cottonwood\">39.47</tr_chVal>"
      << "<tr_chVal species=\"Paper_Birch\">33.18</tr_chVal>"
      << "</tr_canopyHeight>"
      << "<tr_stdAsympCrownRad>"
      << "<tr_sacrVal species=\"Western_Hemlock\">0.0549</tr_sacrVal>"
      << "<tr_sacrVal species=\"Western_Redcedar\">0.0614</tr_sacrVal>"
      << "<tr_sacrVal species=\"Amabilis_Fir\">0.0242</tr_sacrVal>"
      << "<tr_sacrVal species=\"Subalpine_Fir\">0.0251</tr_sacrVal>"
      << "<tr_sacrVal species=\"Hybrid_Spruce\">0.0239</tr_sacrVal>"
      << "<tr_sacrVal species=\"Lodgepole_Pine\">0.0303</tr_sacrVal>"
      << "<tr_sacrVal species=\"Trembling_Aspen\">0.0328</tr_sacrVal>"
      << "<tr_sacrVal species=\"Black_Cottonwood\">0.0247</tr_sacrVal>"
      << "<tr_sacrVal species=\"Paper_Birch\">0.0484</tr_sacrVal>"
      << "</tr_stdAsympCrownRad>"
      << "<tr_stdCrownRadExp>"
      << "<tr_screVal species=\"Western_Hemlock\">1.0</tr_screVal>"
      << "<tr_screVal species=\"Western_Redcedar\">1.0</tr_screVal>"
      << "<tr_screVal species=\"Amabilis_Fir\">1.0</tr_screVal>"
      << "<tr_screVal species=\"Subalpine_Fir\">1.0</tr_screVal>"
      << "<tr_screVal species=\"Hybrid_Spruce\">1.0</tr_screVal>"
      << "<tr_screVal species=\"Lodgepole_Pine\">1.0</tr_screVal>"
      << "<tr_screVal species=\"Trembling_Aspen\">1.0</tr_screVal>"
      << "<tr_screVal species=\"Black_Cottonwood\">1.0</tr_screVal>"
      << "<tr_screVal species=\"Paper_Birch\">1.0</tr_screVal>"
      << "</tr_stdCrownRadExp>"
      << "<tr_stdMaxCrownRad>"
      << "<tr_smcrVal species=\"Western_Hemlock\">10</tr_smcrVal>"
      << "<tr_smcrVal species=\"Western_Redcedar\">10</tr_smcrVal>"
      << "<tr_smcrVal species=\"Amabilis_Fir\">10</tr_smcrVal>"
      << "<tr_smcrVal species=\"Subalpine_Fir\">10</tr_smcrVal>"
      << "<tr_smcrVal species=\"Hybrid_Spruce\">10</tr_smcrVal>"
      << "<tr_smcrVal species=\"Lodgepole_Pine\">10</tr_smcrVal>"
      << "<tr_smcrVal species=\"Trembling_Aspen\">10</tr_smcrVal>"
      << "<tr_smcrVal species=\"Black_Cottonwood\">10</tr_smcrVal>"
      << "<tr_smcrVal species=\"Paper_Birch\">10</tr_smcrVal>"
      << "</tr_stdMaxCrownRad>"
      << "<tr_conversionDiam10ToDBH>"
      << "<tr_cdtdVal species=\"Western_Hemlock\">0.8008</tr_cdtdVal>"
      << "<tr_cdtdVal species=\"Western_Redcedar\">0.5944</tr_cdtdVal>"
      << "<tr_cdtdVal species=\"Amabilis_Fir\">0.7059</tr_cdtdVal>"
      << "<tr_cdtdVal species=\"Subalpine_Fir\">0.7776</tr_cdtdVal>"
      << "<tr_cdtdVal species=\"Hybrid_Spruce\">0.6933</tr_cdtdVal>"
      << "<tr_cdtdVal species=\"Lodgepole_Pine\">0.8014</tr_cdtdVal>"
      << "<tr_cdtdVal species=\"Trembling_Aspen\">0.7992</tr_cdtdVal>"
      << "<tr_cdtdVal species=\"Black_Cottonwood\">0.7926</tr_cdtdVal>"
      << "<tr_cdtdVal species=\"Paper_Birch\">0.7803</tr_cdtdVal>"
      << "</tr_conversionDiam10ToDBH>"
      << "<tr_interceptDiam10ToDBH>"
      << "<tr_idtdVal species=\"Western_Hemlock\">0</tr_idtdVal>"
      << "<tr_idtdVal species=\"Western_Redcedar\">0</tr_idtdVal>"
      << "<tr_idtdVal species=\"Amabilis_Fir\">0</tr_idtdVal>"
      << "<tr_idtdVal species=\"Subalpine_Fir\">0</tr_idtdVal>"
      << "<tr_idtdVal species=\"Hybrid_Spruce\">0</tr_idtdVal>"
      << "<tr_idtdVal species=\"Lodgepole_Pine\">0</tr_idtdVal>"
      << "<tr_idtdVal species=\"Trembling_Aspen\">0</tr_idtdVal>"
      << "<tr_idtdVal species=\"Black_Cottonwood\">0</tr_idtdVal>"
      << "<tr_idtdVal species=\"Paper_Birch\">0</tr_idtdVal>"
      << "</tr_interceptDiam10ToDBH>"
      << "<tr_stdAsympCrownHt>"
      << "<tr_sachVal species=\"Western_Hemlock\">0.389</tr_sachVal>"
      << "<tr_sachVal species=\"Western_Redcedar\">0.368</tr_sachVal>"
      << "<tr_sachVal species=\"Amabilis_Fir\">0.464</tr_sachVal>"
      << "<tr_sachVal species=\"Subalpine_Fir\">0.454</tr_sachVal>"
      << "<tr_sachVal species=\"Hybrid_Spruce\">0.405</tr_sachVal>"
      << "<tr_sachVal species=\"Lodgepole_Pine\">0.201</tr_sachVal>"
      << "<tr_sachVal species=\"Trembling_Aspen\">0.301</tr_sachVal>"
      << "<tr_sachVal species=\"Black_Cottonwood\">0.42</tr_sachVal>"
      << "<tr_sachVal species=\"Paper_Birch\">0.315</tr_sachVal>"
      << "</tr_stdAsympCrownHt>"
      << "<tr_stdCrownHtExp>"
      << "<tr_scheVal species=\"Western_Hemlock\">1.0</tr_scheVal>"
      << "<tr_scheVal species=\"Western_Redcedar\">1.0</tr_scheVal>"
      << "<tr_scheVal species=\"Amabilis_Fir\">1.0</tr_scheVal>"
      << "<tr_scheVal species=\"Subalpine_Fir\">1.0</tr_scheVal>"
      << "<tr_scheVal species=\"Hybrid_Spruce\">1.0</tr_scheVal>"
      << "<tr_scheVal species=\"Lodgepole_Pine\">1.0</tr_scheVal>"
      << "<tr_scheVal species=\"Trembling_Aspen\">1.0</tr_scheVal>"
      << "<tr_scheVal species=\"Black_Cottonwood\">1.0</tr_scheVal>"
      << "<tr_scheVal species=\"Paper_Birch\">1.0</tr_scheVal>"
      << "</tr_stdCrownHtExp>"
      << "<tr_slopeOfHeight-Diam10>"
      << "<tr_sohdVal species=\"Western_Hemlock\">0.03418</tr_sohdVal>"
      << "<tr_sohdVal species=\"Western_Redcedar\">0.0269</tr_sohdVal>"
      << "<tr_sohdVal species=\"Amabilis_Fir\">0.02871</tr_sohdVal>"
      << "<tr_sohdVal species=\"Subalpine_Fir\">0.02815</tr_sohdVal>"
      << "<tr_sohdVal species=\"Hybrid_Spruce\">0.02871</tr_sohdVal>"
      << "<tr_sohdVal species=\"Lodgepole_Pine\">0.03224</tr_sohdVal>"
      << "<tr_sohdVal species=\"Trembling_Aspen\">0.04796</tr_sohdVal>"
      << "<tr_sohdVal species=\"Black_Cottonwood\">0.04681</tr_sohdVal>"
      << "<tr_sohdVal species=\"Paper_Birch\">0.04101</tr_sohdVal>"
      << "</tr_slopeOfHeight-Diam10>"
      << "<tr_slopeOfAsymHeight>"
      << "<tr_soahVal species=\"Western_Hemlock\">0.0299</tr_soahVal>"
      << "<tr_soahVal species=\"Western_Redcedar\">0.0241</tr_soahVal>"
      << "<tr_soahVal species=\"Amabilis_Fir\">0.0263</tr_soahVal>"
      << "<tr_soahVal species=\"Subalpine_Fir\">0.0264</tr_soahVal>"
      << "<tr_soahVal species=\"Hybrid_Spruce\">0.0264</tr_soahVal>"
      << "<tr_soahVal species=\"Lodgepole_Pine\">0.0333</tr_soahVal>"
      << "<tr_soahVal species=\"Trembling_Aspen\">0.0352</tr_soahVal>"
      << "<tr_soahVal species=\"Black_Cottonwood\">0.0347</tr_soahVal>"
      << "<tr_soahVal species=\"Paper_Birch\">0.0454</tr_soahVal>"
      << "</tr_slopeOfAsymHeight>"
      << "<tr_whatSeedlingHeightDiam>"
      << "<tr_wsehdVal species=\"Western_Hemlock\">0</tr_wsehdVal>"
      << "<tr_wsehdVal species=\"Western_Redcedar\">0</tr_wsehdVal>"
      << "<tr_wsehdVal species=\"Amabilis_Fir\">0</tr_wsehdVal>"
      << "<tr_wsehdVal species=\"Subalpine_Fir\">0</tr_wsehdVal>"
      << "<tr_wsehdVal species=\"Hybrid_Spruce\">0</tr_wsehdVal>"
      << "<tr_wsehdVal species=\"Lodgepole_Pine\">0</tr_wsehdVal>"
      << "<tr_wsehdVal species=\"Trembling_Aspen\">0</tr_wsehdVal>"
      << "<tr_wsehdVal species=\"Black_Cottonwood\">0</tr_wsehdVal>"
      << "<tr_wsehdVal species=\"Paper_Birch\">0</tr_wsehdVal>"
      << "</tr_whatSeedlingHeightDiam>"
      << "<tr_whatSaplingHeightDiam>"
      << "<tr_wsahdVal species=\"Western_Hemlock\">0</tr_wsahdVal>"
      << "<tr_wsahdVal species=\"Western_Redcedar\">0</tr_wsahdVal>"
      << "<tr_wsahdVal species=\"Amabilis_Fir\">0</tr_wsahdVal>"
      << "<tr_wsahdVal species=\"Subalpine_Fir\">0</tr_wsahdVal>"
      << "<tr_wsahdVal species=\"Hybrid_Spruce\">0</tr_wsahdVal>"
      << "<tr_wsahdVal species=\"Lodgepole_Pine\">0</tr_wsahdVal>"
      << "<tr_wsahdVal species=\"Trembling_Aspen\">0</tr_wsahdVal>"
      << "<tr_wsahdVal species=\"Black_Cottonwood\">0</tr_wsahdVal>"
      << "<tr_wsahdVal species=\"Paper_Birch\">0</tr_wsahdVal>"
      << "</tr_whatSaplingHeightDiam>"
      << "<tr_whatAdultHeightDiam>"
      << "<tr_wahdVal species=\"Western_Hemlock\">0</tr_wahdVal>"
      << "<tr_wahdVal species=\"Western_Redcedar\">0</tr_wahdVal>"
      << "<tr_wahdVal species=\"Amabilis_Fir\">0</tr_wahdVal>"
      << "<tr_wahdVal species=\"Subalpine_Fir\">0</tr_wahdVal>"
      << "<tr_wahdVal species=\"Hybrid_Spruce\">0</tr_wahdVal>"
      << "<tr_wahdVal species=\"Lodgepole_Pine\">0</tr_wahdVal>"
      << "<tr_wahdVal species=\"Trembling_Aspen\">0</tr_wahdVal>"
      << "<tr_wahdVal species=\"Black_Cottonwood\">0</tr_wahdVal>"
      << "<tr_wahdVal species=\"Paper_Birch\">0</tr_wahdVal>"
      << "</tr_whatAdultHeightDiam>"
      << "<tr_whatAdultCrownRadDiam>"
      << "<tr_wacrdVal species=\"Western_Hemlock\">0</tr_wacrdVal>"
      << "<tr_wacrdVal species=\"Western_Redcedar\">0</tr_wacrdVal>"
      << "<tr_wacrdVal species=\"Amabilis_Fir\">0</tr_wacrdVal>"
      << "<tr_wacrdVal species=\"Subalpine_Fir\">0</tr_wacrdVal>"
      << "<tr_wacrdVal species=\"Hybrid_Spruce\">0</tr_wacrdVal>"
      << "<tr_wacrdVal species=\"Lodgepole_Pine\">0</tr_wacrdVal>"
      << "<tr_wacrdVal species=\"Trembling_Aspen\">0</tr_wacrdVal>"
      << "<tr_wacrdVal species=\"Black_Cottonwood\">0</tr_wacrdVal>"
      << "<tr_wacrdVal species=\"Paper_Birch\">0</tr_wacrdVal>"
      << "</tr_whatAdultCrownRadDiam>"
      << "<tr_whatAdultCrownHeightHeight>"
      << "<tr_wachhVal species=\"Western_Hemlock\">0</tr_wachhVal>"
      << "<tr_wachhVal species=\"Western_Redcedar\">0</tr_wachhVal>"
      << "<tr_wachhVal species=\"Amabilis_Fir\">0</tr_wachhVal>"
      << "<tr_wachhVal species=\"Subalpine_Fir\">0</tr_wachhVal>"
      << "<tr_wachhVal species=\"Hybrid_Spruce\">0</tr_wachhVal>"
      << "<tr_wachhVal species=\"Lodgepole_Pine\">0</tr_wachhVal>"
      << "<tr_wachhVal species=\"Trembling_Aspen\">0</tr_wachhVal>"
      << "<tr_wachhVal species=\"Black_Cottonwood\">0</tr_wachhVal>"
      << "<tr_wachhVal species=\"Paper_Birch\">0</tr_wachhVal>"
      << "</tr_whatAdultCrownHeightHeight>"
      << "<tr_whatSaplingCrownRadDiam>"
      << "<tr_wscrdVal species=\"Western_Hemlock\">0</tr_wscrdVal>"
      << "<tr_wscrdVal species=\"Western_Redcedar\">0</tr_wscrdVal>"
      << "<tr_wscrdVal species=\"Amabilis_Fir\">0</tr_wscrdVal>"
      << "<tr_wscrdVal species=\"Subalpine_Fir\">0</tr_wscrdVal>"
      << "<tr_wscrdVal species=\"Hybrid_Spruce\">0</tr_wscrdVal>"
      << "<tr_wscrdVal species=\"Lodgepole_Pine\">0</tr_wscrdVal>"
      << "<tr_wscrdVal species=\"Trembling_Aspen\">0</tr_wscrdVal>"
      << "<tr_wscrdVal species=\"Black_Cottonwood\">0</tr_wscrdVal>"
      << "<tr_wscrdVal species=\"Paper_Birch\">0</tr_wscrdVal>"
      << "</tr_whatSaplingCrownRadDiam>"
      << "<tr_whatSaplingCrownHeightHeight>"
      << "<tr_wschhVal species=\"Western_Hemlock\">0</tr_wschhVal>"
      << "<tr_wschhVal species=\"Western_Redcedar\">0</tr_wschhVal>"
      << "<tr_wschhVal species=\"Amabilis_Fir\">0</tr_wschhVal>"
      << "<tr_wschhVal species=\"Subalpine_Fir\">0</tr_wschhVal>"
      << "<tr_wschhVal species=\"Hybrid_Spruce\">0</tr_wschhVal>"
      << "<tr_wschhVal species=\"Lodgepole_Pine\">0</tr_wschhVal>"
      << "<tr_wschhVal species=\"Trembling_Aspen\">0</tr_wschhVal>"
      << "<tr_wschhVal species=\"Black_Cottonwood\">0</tr_wschhVal>"
      << "<tr_wschhVal species=\"Paper_Birch\">0</tr_wschhVal>"
      << "</tr_whatSaplingCrownHeightHeight>"
      << "</allometry>";
  oOut  << "<behaviorList>"
      << "<behavior>"
      << "<behaviorName>Plant</behaviorName>"
      << "<listPosition>1</listPosition>"
      << "<version>1</version>"
      << "</behavior>"
      << "</behaviorList>"
      << "<Plant1>"
      << "<pl_plantEvent>"
      << "<pl_applyToSpecies species=\"Lodgepole_Pine\" />"
      << "<pl_applyToSpecies species=\"Subalpine_Fir\" />"
      << "<pl_applyToSpecies species=\"Hybrid_Spruce\" />"
      << "<pl_timestep>1</pl_timestep>"
      << "<pl_spaceType>random</pl_spaceType>"
      << "<pl_distanceOrDensity>200</pl_distanceOrDensity>"
      << "<pl_amountToPlant>"
      << "<pl_atpVal species=\"Subalpine_Fir\">33.3</pl_atpVal>"
      << "<pl_atpVal species=\"Hybrid_Spruce\">33.3</pl_atpVal>"
      << "<pl_atpVal species=\"Lodgepole_Pine\">33.4</pl_atpVal>"
      << "</pl_amountToPlant>";
  for (int i = 0; i < 13; i++) {
    for (int j = 0; j < 13; j++) {
      oOut << "<pl_applyToCell x=\"" << i << "\" y=\"" << j << "\" /> ";
    }
  }
  oOut << "</pl_plantEvent>"
      << "</Plant1>"
      << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WritePlantingXMLFile6()
/////////////////////////////////////////////////////////////////////////////
const char* WritePlantingXMLFile6() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  std::fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
      << "<paramFile fileCode=\"06010101\">" << "<plot>"
      << "<timesteps>3</timesteps>"
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
      << "<tr_species speciesName=\"Western_Hemlock\"/>"
      << "<tr_species speciesName=\"Western_Redcedar\"/>"
      << "<tr_species speciesName=\"Amabilis_Fir\"/>"
      << "<tr_species speciesName=\"Subalpine_Fir\"/>"
      << "<tr_species speciesName=\"Hybrid_Spruce\"/>"
      << "<tr_species speciesName=\"Lodgepole_Pine\"/>"
      << "<tr_species speciesName=\"Trembling_Aspen\"/>"
      << "<tr_species speciesName=\"Black_Cottonwood\"/>"
      << "<tr_species speciesName=\"Paper_Birch\"/>"
      << "</tr_speciesList>"
      << "<tr_seedDiam10Cm>0.1</tr_seedDiam10Cm>"
      << "<tr_minAdultDBH>"
      << "<tr_madVal species=\"Western_Hemlock\">10</tr_madVal>"
      << "<tr_madVal species=\"Western_Redcedar\">10</tr_madVal>"
      << "<tr_madVal species=\"Amabilis_Fir\">10</tr_madVal>"
      << "<tr_madVal species=\"Subalpine_Fir\">10</tr_madVal>"
      << "<tr_madVal species=\"Hybrid_Spruce\">10</tr_madVal>"
      << "<tr_madVal species=\"Lodgepole_Pine\">10</tr_madVal>"
      << "<tr_madVal species=\"Trembling_Aspen\">10</tr_madVal>"
      << "<tr_madVal species=\"Black_Cottonwood\">10</tr_madVal>"
      << "<tr_madVal species=\"Paper_Birch\">10</tr_madVal>"
      << "</tr_minAdultDBH>"
      << "<tr_maxSeedlingHeight>"
      << "<tr_mshVal species=\"Western_Hemlock\">1.35</tr_mshVal>"
      << "<tr_mshVal species=\"Western_Redcedar\">1.35</tr_mshVal>"
      << "<tr_mshVal species=\"Amabilis_Fir\">1.35</tr_mshVal>"
      << "<tr_mshVal species=\"Subalpine_Fir\">1.35</tr_mshVal>"
      << "<tr_mshVal species=\"Hybrid_Spruce\">1.35</tr_mshVal>"
      << "<tr_mshVal species=\"Lodgepole_Pine\">1.35</tr_mshVal>"
      << "<tr_mshVal species=\"Trembling_Aspen\">1.35</tr_mshVal>"
      << "<tr_mshVal species=\"Black_Cottonwood\">1.35</tr_mshVal>"
      << "<tr_mshVal species=\"Paper_Birch\">1.35</tr_mshVal>"
      << "</tr_maxSeedlingHeight>"
      << "</trees>"
      << "<allometry>"
      << "<tr_canopyHeight>"
      << "<tr_chVal species=\"Western_Hemlock\">39.48</tr_chVal>"
      << "<tr_chVal species=\"Western_Redcedar\">39.54</tr_chVal>"
      << "<tr_chVal species=\"Amabilis_Fir\">40</tr_chVal>"
      << "<tr_chVal species=\"Subalpine_Fir\">40</tr_chVal>"
      << "<tr_chVal species=\"Hybrid_Spruce\">45</tr_chVal>"
      << "<tr_chVal species=\"Lodgepole_Pine\">40</tr_chVal>"
      << "<tr_chVal species=\"Trembling_Aspen\">39.14</tr_chVal>"
      << "<tr_chVal species=\"Black_Cottonwood\">39.47</tr_chVal>"
      << "<tr_chVal species=\"Paper_Birch\">33.18</tr_chVal>"
      << "</tr_canopyHeight>"
      << "<tr_stdAsympCrownRad>"
      << "<tr_sacrVal species=\"Western_Hemlock\">0.0549</tr_sacrVal>"
      << "<tr_sacrVal species=\"Western_Redcedar\">0.0614</tr_sacrVal>"
      << "<tr_sacrVal species=\"Amabilis_Fir\">0.0242</tr_sacrVal>"
      << "<tr_sacrVal species=\"Subalpine_Fir\">0.0251</tr_sacrVal>"
      << "<tr_sacrVal species=\"Hybrid_Spruce\">0.0239</tr_sacrVal>"
      << "<tr_sacrVal species=\"Lodgepole_Pine\">0.0303</tr_sacrVal>"
      << "<tr_sacrVal species=\"Trembling_Aspen\">0.0328</tr_sacrVal>"
      << "<tr_sacrVal species=\"Black_Cottonwood\">0.0247</tr_sacrVal>"
      << "<tr_sacrVal species=\"Paper_Birch\">0.0484</tr_sacrVal>"
      << "</tr_stdAsympCrownRad>"
      << "<tr_stdCrownRadExp>"
      << "<tr_screVal species=\"Western_Hemlock\">1.0</tr_screVal>"
      << "<tr_screVal species=\"Western_Redcedar\">1.0</tr_screVal>"
      << "<tr_screVal species=\"Amabilis_Fir\">1.0</tr_screVal>"
      << "<tr_screVal species=\"Subalpine_Fir\">1.0</tr_screVal>"
      << "<tr_screVal species=\"Hybrid_Spruce\">1.0</tr_screVal>"
      << "<tr_screVal species=\"Lodgepole_Pine\">1.0</tr_screVal>"
      << "<tr_screVal species=\"Trembling_Aspen\">1.0</tr_screVal>"
      << "<tr_screVal species=\"Black_Cottonwood\">1.0</tr_screVal>"
      << "<tr_screVal species=\"Paper_Birch\">1.0</tr_screVal>"
      << "</tr_stdCrownRadExp>"
      << "<tr_stdMaxCrownRad>"
      << "<tr_smcrVal species=\"Western_Hemlock\">10</tr_smcrVal>"
      << "<tr_smcrVal species=\"Western_Redcedar\">10</tr_smcrVal>"
      << "<tr_smcrVal species=\"Amabilis_Fir\">10</tr_smcrVal>"
      << "<tr_smcrVal species=\"Subalpine_Fir\">10</tr_smcrVal>"
      << "<tr_smcrVal species=\"Hybrid_Spruce\">10</tr_smcrVal>"
      << "<tr_smcrVal species=\"Lodgepole_Pine\">10</tr_smcrVal>"
      << "<tr_smcrVal species=\"Trembling_Aspen\">10</tr_smcrVal>"
      << "<tr_smcrVal species=\"Black_Cottonwood\">10</tr_smcrVal>"
      << "<tr_smcrVal species=\"Paper_Birch\">10</tr_smcrVal>"
      << "</tr_stdMaxCrownRad>"
      << "<tr_conversionDiam10ToDBH>"
      << "<tr_cdtdVal species=\"Western_Hemlock\">0.8008</tr_cdtdVal>"
      << "<tr_cdtdVal species=\"Western_Redcedar\">0.5944</tr_cdtdVal>"
      << "<tr_cdtdVal species=\"Amabilis_Fir\">0.7059</tr_cdtdVal>"
      << "<tr_cdtdVal species=\"Subalpine_Fir\">0.7776</tr_cdtdVal>"
      << "<tr_cdtdVal species=\"Hybrid_Spruce\">0.6933</tr_cdtdVal>"
      << "<tr_cdtdVal species=\"Lodgepole_Pine\">0.8014</tr_cdtdVal>"
      << "<tr_cdtdVal species=\"Trembling_Aspen\">0.7992</tr_cdtdVal>"
      << "<tr_cdtdVal species=\"Black_Cottonwood\">0.7926</tr_cdtdVal>"
      << "<tr_cdtdVal species=\"Paper_Birch\">0.7803</tr_cdtdVal>"
      << "</tr_conversionDiam10ToDBH>"
      << "<tr_interceptDiam10ToDBH>"
      << "<tr_idtdVal species=\"Western_Hemlock\">0</tr_idtdVal>"
      << "<tr_idtdVal species=\"Western_Redcedar\">0</tr_idtdVal>"
      << "<tr_idtdVal species=\"Amabilis_Fir\">0</tr_idtdVal>"
      << "<tr_idtdVal species=\"Subalpine_Fir\">0</tr_idtdVal>"
      << "<tr_idtdVal species=\"Hybrid_Spruce\">0</tr_idtdVal>"
      << "<tr_idtdVal species=\"Lodgepole_Pine\">0</tr_idtdVal>"
      << "<tr_idtdVal species=\"Trembling_Aspen\">0</tr_idtdVal>"
      << "<tr_idtdVal species=\"Black_Cottonwood\">0</tr_idtdVal>"
      << "<tr_idtdVal species=\"Paper_Birch\">0</tr_idtdVal>"
      << "</tr_interceptDiam10ToDBH>"
      << "<tr_stdAsympCrownHt>"
      << "<tr_sachVal species=\"Western_Hemlock\">0.389</tr_sachVal>"
      << "<tr_sachVal species=\"Western_Redcedar\">0.368</tr_sachVal>"
      << "<tr_sachVal species=\"Amabilis_Fir\">0.464</tr_sachVal>"
      << "<tr_sachVal species=\"Subalpine_Fir\">0.454</tr_sachVal>"
      << "<tr_sachVal species=\"Hybrid_Spruce\">0.405</tr_sachVal>"
      << "<tr_sachVal species=\"Lodgepole_Pine\">0.201</tr_sachVal>"
      << "<tr_sachVal species=\"Trembling_Aspen\">0.301</tr_sachVal>"
      << "<tr_sachVal species=\"Black_Cottonwood\">0.42</tr_sachVal>"
      << "<tr_sachVal species=\"Paper_Birch\">0.315</tr_sachVal>"
      << "</tr_stdAsympCrownHt>"
      << "<tr_stdCrownHtExp>"
      << "<tr_scheVal species=\"Western_Hemlock\">1.0</tr_scheVal>"
      << "<tr_scheVal species=\"Western_Redcedar\">1.0</tr_scheVal>"
      << "<tr_scheVal species=\"Amabilis_Fir\">1.0</tr_scheVal>"
      << "<tr_scheVal species=\"Subalpine_Fir\">1.0</tr_scheVal>"
      << "<tr_scheVal species=\"Hybrid_Spruce\">1.0</tr_scheVal>"
      << "<tr_scheVal species=\"Lodgepole_Pine\">1.0</tr_scheVal>"
      << "<tr_scheVal species=\"Trembling_Aspen\">1.0</tr_scheVal>"
      << "<tr_scheVal species=\"Black_Cottonwood\">1.0</tr_scheVal>"
      << "<tr_scheVal species=\"Paper_Birch\">1.0</tr_scheVal>"
      << "</tr_stdCrownHtExp>"
      << "<tr_slopeOfHeight-Diam10>"
      << "<tr_sohdVal species=\"Western_Hemlock\">0.03418</tr_sohdVal>"
      << "<tr_sohdVal species=\"Western_Redcedar\">0.0269</tr_sohdVal>"
      << "<tr_sohdVal species=\"Amabilis_Fir\">0.02871</tr_sohdVal>"
      << "<tr_sohdVal species=\"Subalpine_Fir\">0.02815</tr_sohdVal>"
      << "<tr_sohdVal species=\"Hybrid_Spruce\">0.02871</tr_sohdVal>"
      << "<tr_sohdVal species=\"Lodgepole_Pine\">0.03224</tr_sohdVal>"
      << "<tr_sohdVal species=\"Trembling_Aspen\">0.04796</tr_sohdVal>"
      << "<tr_sohdVal species=\"Black_Cottonwood\">0.04681</tr_sohdVal>"
      << "<tr_sohdVal species=\"Paper_Birch\">0.04101</tr_sohdVal>"
      << "</tr_slopeOfHeight-Diam10>"
      << "<tr_slopeOfAsymHeight>"
      << "<tr_soahVal species=\"Western_Hemlock\">0.0299</tr_soahVal>"
      << "<tr_soahVal species=\"Western_Redcedar\">0.0241</tr_soahVal>"
      << "<tr_soahVal species=\"Amabilis_Fir\">0.0263</tr_soahVal>"
      << "<tr_soahVal species=\"Subalpine_Fir\">0.0264</tr_soahVal>"
      << "<tr_soahVal species=\"Hybrid_Spruce\">0.0264</tr_soahVal>"
      << "<tr_soahVal species=\"Lodgepole_Pine\">0.0333</tr_soahVal>"
      << "<tr_soahVal species=\"Trembling_Aspen\">0.0352</tr_soahVal>"
      << "<tr_soahVal species=\"Black_Cottonwood\">0.0347</tr_soahVal>"
      << "<tr_soahVal species=\"Paper_Birch\">0.0454</tr_soahVal>"
      << "</tr_slopeOfAsymHeight>"
      << "<tr_whatSeedlingHeightDiam>"
      << "<tr_wsehdVal species=\"Western_Hemlock\">0</tr_wsehdVal>"
      << "<tr_wsehdVal species=\"Western_Redcedar\">0</tr_wsehdVal>"
      << "<tr_wsehdVal species=\"Amabilis_Fir\">0</tr_wsehdVal>"
      << "<tr_wsehdVal species=\"Subalpine_Fir\">0</tr_wsehdVal>"
      << "<tr_wsehdVal species=\"Hybrid_Spruce\">0</tr_wsehdVal>"
      << "<tr_wsehdVal species=\"Lodgepole_Pine\">0</tr_wsehdVal>"
      << "<tr_wsehdVal species=\"Trembling_Aspen\">0</tr_wsehdVal>"
      << "<tr_wsehdVal species=\"Black_Cottonwood\">0</tr_wsehdVal>"
      << "<tr_wsehdVal species=\"Paper_Birch\">0</tr_wsehdVal>"
      << "</tr_whatSeedlingHeightDiam>"
      << "<tr_whatSaplingHeightDiam>"
      << "<tr_wsahdVal species=\"Western_Hemlock\">0</tr_wsahdVal>"
      << "<tr_wsahdVal species=\"Western_Redcedar\">0</tr_wsahdVal>"
      << "<tr_wsahdVal species=\"Amabilis_Fir\">0</tr_wsahdVal>"
      << "<tr_wsahdVal species=\"Subalpine_Fir\">0</tr_wsahdVal>"
      << "<tr_wsahdVal species=\"Hybrid_Spruce\">0</tr_wsahdVal>"
      << "<tr_wsahdVal species=\"Lodgepole_Pine\">0</tr_wsahdVal>"
      << "<tr_wsahdVal species=\"Trembling_Aspen\">0</tr_wsahdVal>"
      << "<tr_wsahdVal species=\"Black_Cottonwood\">0</tr_wsahdVal>"
      << "<tr_wsahdVal species=\"Paper_Birch\">0</tr_wsahdVal>"
      << "</tr_whatSaplingHeightDiam>"
      << "<tr_whatAdultHeightDiam>"
      << "<tr_wahdVal species=\"Western_Hemlock\">0</tr_wahdVal>"
      << "<tr_wahdVal species=\"Western_Redcedar\">0</tr_wahdVal>"
      << "<tr_wahdVal species=\"Amabilis_Fir\">0</tr_wahdVal>"
      << "<tr_wahdVal species=\"Subalpine_Fir\">0</tr_wahdVal>"
      << "<tr_wahdVal species=\"Hybrid_Spruce\">0</tr_wahdVal>"
      << "<tr_wahdVal species=\"Lodgepole_Pine\">0</tr_wahdVal>"
      << "<tr_wahdVal species=\"Trembling_Aspen\">0</tr_wahdVal>"
      << "<tr_wahdVal species=\"Black_Cottonwood\">0</tr_wahdVal>"
      << "<tr_wahdVal species=\"Paper_Birch\">0</tr_wahdVal>"
      << "</tr_whatAdultHeightDiam>"
      << "<tr_whatAdultCrownRadDiam>"
      << "<tr_wacrdVal species=\"Western_Hemlock\">0</tr_wacrdVal>"
      << "<tr_wacrdVal species=\"Western_Redcedar\">0</tr_wacrdVal>"
      << "<tr_wacrdVal species=\"Amabilis_Fir\">0</tr_wacrdVal>"
      << "<tr_wacrdVal species=\"Subalpine_Fir\">0</tr_wacrdVal>"
      << "<tr_wacrdVal species=\"Hybrid_Spruce\">0</tr_wacrdVal>"
      << "<tr_wacrdVal species=\"Lodgepole_Pine\">0</tr_wacrdVal>"
      << "<tr_wacrdVal species=\"Trembling_Aspen\">0</tr_wacrdVal>"
      << "<tr_wacrdVal species=\"Black_Cottonwood\">0</tr_wacrdVal>"
      << "<tr_wacrdVal species=\"Paper_Birch\">0</tr_wacrdVal>"
      << "</tr_whatAdultCrownRadDiam>"
      << "<tr_whatAdultCrownHeightHeight>"
      << "<tr_wachhVal species=\"Western_Hemlock\">0</tr_wachhVal>"
      << "<tr_wachhVal species=\"Western_Redcedar\">0</tr_wachhVal>"
      << "<tr_wachhVal species=\"Amabilis_Fir\">0</tr_wachhVal>"
      << "<tr_wachhVal species=\"Subalpine_Fir\">0</tr_wachhVal>"
      << "<tr_wachhVal species=\"Hybrid_Spruce\">0</tr_wachhVal>"
      << "<tr_wachhVal species=\"Lodgepole_Pine\">0</tr_wachhVal>"
      << "<tr_wachhVal species=\"Trembling_Aspen\">0</tr_wachhVal>"
      << "<tr_wachhVal species=\"Black_Cottonwood\">0</tr_wachhVal>"
      << "<tr_wachhVal species=\"Paper_Birch\">0</tr_wachhVal>"
      << "</tr_whatAdultCrownHeightHeight>"
      << "<tr_whatSaplingCrownRadDiam>"
      << "<tr_wscrdVal species=\"Western_Hemlock\">0</tr_wscrdVal>"
      << "<tr_wscrdVal species=\"Western_Redcedar\">0</tr_wscrdVal>"
      << "<tr_wscrdVal species=\"Amabilis_Fir\">0</tr_wscrdVal>"
      << "<tr_wscrdVal species=\"Subalpine_Fir\">0</tr_wscrdVal>"
      << "<tr_wscrdVal species=\"Hybrid_Spruce\">0</tr_wscrdVal>"
      << "<tr_wscrdVal species=\"Lodgepole_Pine\">0</tr_wscrdVal>"
      << "<tr_wscrdVal species=\"Trembling_Aspen\">0</tr_wscrdVal>"
      << "<tr_wscrdVal species=\"Black_Cottonwood\">0</tr_wscrdVal>"
      << "<tr_wscrdVal species=\"Paper_Birch\">0</tr_wscrdVal>"
      << "</tr_whatSaplingCrownRadDiam>"
      << "<tr_whatSaplingCrownHeightHeight>"
      << "<tr_wschhVal species=\"Western_Hemlock\">0</tr_wschhVal>"
      << "<tr_wschhVal species=\"Western_Redcedar\">0</tr_wschhVal>"
      << "<tr_wschhVal species=\"Amabilis_Fir\">0</tr_wschhVal>"
      << "<tr_wschhVal species=\"Subalpine_Fir\">0</tr_wschhVal>"
      << "<tr_wschhVal species=\"Hybrid_Spruce\">0</tr_wschhVal>"
      << "<tr_wschhVal species=\"Lodgepole_Pine\">0</tr_wschhVal>"
      << "<tr_wschhVal species=\"Trembling_Aspen\">0</tr_wschhVal>"
      << "<tr_wschhVal species=\"Black_Cottonwood\">0</tr_wschhVal>"
      << "<tr_wschhVal species=\"Paper_Birch\">0</tr_wschhVal>"
      << "</tr_whatSaplingCrownHeightHeight>"
      << "</allometry>"
      << "<behaviorList>"
      << "<behavior>"
      << "<behaviorName>Plant</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>1</listPosition>"
      << "</behavior>"
      << "</behaviorList>"
      << "<Plant1>"
      << "<pl_initialDiam10>"
      << "<pl_idVal species=\"Hybrid_Spruce\">0.5</pl_idVal>"
      << "<pl_idVal species=\"Lodgepole_Pine\">0.6</pl_idVal>"
      << "<pl_idVal species=\"Trembling_Aspen\">0.7</pl_idVal>"
      << "<pl_idVal species=\"Black_Cottonwood\">0.8</pl_idVal>"
      << "<pl_idVal species=\"Western_Hemlock\">0.1</pl_idVal>"
      << "<pl_idVal species=\"Western_Redcedar\">0.2</pl_idVal>"
      << "<pl_idVal species=\"Amabilis_Fir\">0.3</pl_idVal>"
      << "<pl_idVal species=\"Subalpine_Fir\">0.4</pl_idVal>"
      << "<pl_idVal species=\"Paper_Birch\">0.9</pl_idVal>"
      << "</pl_initialDiam10>"
      << "<pl_plantEvent>"
      << "<pl_applyToSpecies species=\"Lodgepole_Pine\" />"
      << "<pl_applyToSpecies species=\"Subalpine_Fir\" />"
      << "<pl_applyToSpecies species=\"Hybrid_Spruce\" />"
      << "<pl_applyToSpecies species=\"Trembling_Aspen\" />"
      << "<pl_applyToSpecies species=\"Black_Cottonwood\" />"
      << "<pl_applyToSpecies species=\"Western_Hemlock\" />"
      << "<pl_applyToSpecies species=\"Western_Redcedar\" />"
      << "<pl_applyToSpecies species=\"Amabilis_Fir\" />"
      << "<pl_applyToSpecies species=\"Paper_Birch\" />"
      << "<pl_timestep>2</pl_timestep>"
      << "<pl_spaceType>gridded</pl_spaceType>"
      << "<pl_distanceOrDensity>2</pl_distanceOrDensity>"
      << "<pl_amountToPlant>"
      << "<pl_atpVal species=\"Western_Hemlock\">5</pl_atpVal>"
      << "<pl_atpVal species=\"Western_Redcedar\">10</pl_atpVal>"
      << "<pl_atpVal species=\"Amabilis_Fir\">15</pl_atpVal>"
      << "<pl_atpVal species=\"Subalpine_Fir\">30</pl_atpVal>"
      << "<pl_atpVal species=\"Hybrid_Spruce\">1</pl_atpVal>"
      << "<pl_atpVal species=\"Lodgepole_Pine\">10</pl_atpVal>"
      << "<pl_atpVal species=\"Trembling_Aspen\">7</pl_atpVal>"
      << "<pl_atpVal species=\"Black_Cottonwood\">8</pl_atpVal>"
      << "<pl_atpVal species=\"Paper_Birch\">14</pl_atpVal>"
      << "</pl_amountToPlant>";
  for (int i = 0; i < 13; i++) {
    for (int j = 0; j < 13; j++) {
      oOut << "<pl_applyToCell x=\"" << i << "\" y=\"" << j << "\" /> ";
    }
  }
  oOut << "</pl_plantEvent>"
      << "</Plant1>"
      << "</paramFile>";

  oOut.close();

  return cFileString;
}
