//---------------------------------------------------------------------------
// TestNeighbhorhoodSeedPredation.cpp
//---------------------------------------------------------------------------
#include "TestDensDepRodentSeedPredation.h"
#include <gtest/gtest.h>
#include "SimManager.h"
#include "TreePopulation.h"
#include "Grid.h"
#include <fstream>
#include <math.h>

/////////////////////////////////////////////////////////////////////////////
// TestNormalProcessingRun1()
// First normal processing run. WriteDensDepRodentSeedPredationXMLFile1()
// does setup. Seed predation is applied to species 1, 2, and 4. This run
// tests normal processing and capturing masting timeseries from different
// copies of Masting Disperse with Autocorrelation.
/////////////////////////////////////////////////////////////////////////////
TEST(DensDepRodentSeedPredation, TestNormalProcessingRun1)
{
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    //Feed our file to the sim manager
    p_oSimManager->ReadFile(WriteDensDepRodentSeedPredationXMLFile1());
    clTreePopulation *p_oPop = (clTreePopulation *) p_oSimManager->GetPopulationObject("treepopulation");
    clTreeSearch *p_oAllTrees;
    clTree *p_oTree;

    int iNumSp1, iNumSp2, iNumSp3, iNumSp4;

    //-----------------------------------------------------------------------//
    //Timestep 1: the number of seeds will be fed in by non-spatial disperse.
    //There are no parents, and that's on purpose. They can't mess with our
    //seed inputs
    //-----------------------------------------------------------------------//
    p_oSimManager->RunSim(1);

    //Count the number of seedlings of each type
    iNumSp1 = 0;
    iNumSp2 = 0;
    iNumSp3 = 0;
    iNumSp4 = 0;
    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {
      if (p_oTree->GetType() == clTreePopulation::seedling) {
        if (p_oTree->GetSpecies() == 0) iNumSp1++;
        else if (p_oTree->GetSpecies() == 1) iNumSp2++;
        else if (p_oTree->GetSpecies() == 2) iNumSp3++;
        else if (p_oTree->GetSpecies() == 3) iNumSp4++;
        else FAIL() << "DensDepRodentSeedPredation doesn't know what this seedling is";
      }
      p_oTree = p_oAllTrees->NextTree();
    }

    //Check the counts
    EXPECT_TRUE(iNumSp1 == 109 || iNumSp1 == 110);
    EXPECT_TRUE(iNumSp2 == 219 || iNumSp2 == 220);
    EXPECT_TRUE(iNumSp3 == 27648);
    EXPECT_TRUE(iNumSp4 == 439 || iNumSp4 == 440);

    // Kill all the seedlings in preparation for the next timestep
    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {
      p_oPop->KillTree(p_oTree, remove_tree);
      p_oTree = p_oAllTrees->NextTree();
    }

    //-----------------------------------------------------------------------//
    // Timestep 2
    //-----------------------------------------------------------------------//
    p_oSimManager->RunSim(1);

    //Count the number of seedlings of each type
    iNumSp1 = 0;
    iNumSp2 = 0;
    iNumSp3 = 0;
    iNumSp4 = 0;
    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {
      if (p_oTree->GetType() == clTreePopulation::seedling) {
        if (p_oTree->GetSpecies() == 0) iNumSp1++;
        else if (p_oTree->GetSpecies() == 1) iNumSp2++;
        else if (p_oTree->GetSpecies() == 2) iNumSp3++;
        else if (p_oTree->GetSpecies() == 3) iNumSp4++;
        else FAIL() << "DensDepRodentSeedPredation doesn't know what this seedling is";
      }
      p_oTree = p_oAllTrees->NextTree();
    }

    //Check the counts
    EXPECT_TRUE(iNumSp1 == 8120  || iNumSp1 == 8121 );
    EXPECT_TRUE(iNumSp2 == 16241 || iNumSp2 == 16242);
    EXPECT_TRUE(iNumSp3 == 27648);
    EXPECT_TRUE(iNumSp4 == 32482 || iNumSp4 == 32483);

    // Kill all the seedlings in preparation for the next timestep
    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {
      p_oPop->KillTree(p_oTree, remove_tree);
      p_oTree = p_oAllTrees->NextTree();
    }

    //-----------------------------------------------------------------------//
    // Timestep 3
    //-----------------------------------------------------------------------//
    p_oSimManager->RunSim(1);

    //Count the number of seedlings of each type
    iNumSp1 = 0;
    iNumSp2 = 0;
    iNumSp3 = 0;
    iNumSp4 = 0;
    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {
      if (p_oTree->GetType() == clTreePopulation::seedling) {
        if (p_oTree->GetSpecies() == 0) iNumSp1++;
        else if (p_oTree->GetSpecies() == 1) iNumSp2++;
        else if (p_oTree->GetSpecies() == 2) iNumSp3++;
        else if (p_oTree->GetSpecies() == 3) iNumSp4++;
        else FAIL() << "DensDepRodentSeedPredation doesn't know what this seedling is";
      }
      p_oTree = p_oAllTrees->NextTree();
    }

    //Check the counts
    EXPECT_TRUE(iNumSp1 == 379   || iNumSp1 == 380  );
    EXPECT_TRUE(iNumSp2 == 758   || iNumSp2 == 759  );
    EXPECT_TRUE(iNumSp3 == 27648);
    EXPECT_TRUE(iNumSp4 == 1517  || iNumSp4 == 1518 );

    // Kill all the seedlings in preparation for the next timestep
    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {
      p_oPop->KillTree(p_oTree, remove_tree);
      p_oTree = p_oAllTrees->NextTree();
    }

    //-----------------------------------------------------------------------//
    // Timestep 4
    //-----------------------------------------------------------------------//
    p_oSimManager->RunSim(1);

    //Count the number of seedlings of each type
    iNumSp1 = 0;
    iNumSp2 = 0;
    iNumSp3 = 0;
    iNumSp4 = 0;
    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {
      if (p_oTree->GetType() == clTreePopulation::seedling) {
        if (p_oTree->GetSpecies() == 0) iNumSp1++;
        else if (p_oTree->GetSpecies() == 1) iNumSp2++;
        else if (p_oTree->GetSpecies() == 2) iNumSp3++;
        else if (p_oTree->GetSpecies() == 3) iNumSp4++;
        else FAIL() << "DensDepRodentSeedPredation doesn't know what this seedling is";
      }
      p_oTree = p_oAllTrees->NextTree();
    }

    //Check the counts
    EXPECT_TRUE(iNumSp1 == 5942  || iNumSp1 == 5943 );
    EXPECT_TRUE(iNumSp2 == 11885 || iNumSp2 == 11886);
    EXPECT_TRUE(iNumSp3 == 27648);
    EXPECT_TRUE(iNumSp4 == 23771 || iNumSp4 == 23772);

    // Kill all the seedlings in preparation for the next timestep
    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {
      p_oPop->KillTree(p_oTree, remove_tree);
      p_oTree = p_oAllTrees->NextTree();
    }


    delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}


/////////////////////////////////////////////////////////////////////////////
// TestNormalProcessingRun2()
// Tests bounding for lambda.
/////////////////////////////////////////////////////////////////////////////
TEST(DensDepRodentSeedPredation, TestNormalProcessingRun2)
{
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    //Feed our file to the sim manager
    p_oSimManager->ReadFile(WriteDensDepRodentSeedPredationXMLFile2());
    clTreePopulation *p_oPop = (clTreePopulation *) p_oSimManager->GetPopulationObject("treepopulation");
    clTreeSearch *p_oAllTrees;
    clTree *p_oTree;
    clGrid *p_oGrid;
    float fExpectedValue, fValue;

    int iNumSp1;

    p_oGrid = p_oSimManager->GetGridObject("Rodent Lambda");
    ASSERT_TRUE(NULL != p_oGrid);

    //-----------------------------------------------------------------------//
    //Timestep 1: the number of seeds will be fed in by non-spatial disperse.
    //There are no parents, and that's on purpose. They can't mess with our
    //seed inputs
    //-----------------------------------------------------------------------//
    p_oSimManager->RunSim(1);

    fExpectedValue = 1;
    p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("rodent_lambda"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

    //Count the number of seedlings of each type
    iNumSp1 = 0;
    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {
      if (p_oTree->GetType() == clTreePopulation::seedling) {
        if (p_oTree->GetSpecies() == 0) iNumSp1++;
        else FAIL() << "DensDepRodentSeedPredation doesn't know what this seedling is";
      }
      p_oTree = p_oAllTrees->NextTree();
    }

    //Check the counts
    EXPECT_TRUE(iNumSp1 == 0 || iNumSp1 == 1);

    // Kill all the seedlings in preparation for the next timestep
    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {
      p_oPop->KillTree(p_oTree, remove_tree);
      p_oTree = p_oAllTrees->NextTree();
    }

    //-----------------------------------------------------------------------//
    // Timestep 2
    //-----------------------------------------------------------------------//
    p_oSimManager->RunSim(1);

    fExpectedValue = 0.0001;
    p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("rodent_lambda"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

    //Count the number of seedlings of each type
    iNumSp1 = 0;
    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {
      if (p_oTree->GetType() == clTreePopulation::seedling) {
        if (p_oTree->GetSpecies() == 0) iNumSp1++;
        else FAIL() << "DensDepRodentSeedPredation doesn't know what this seedling is";
      }
      p_oTree = p_oAllTrees->NextTree();
    }

    //Check the counts
    EXPECT_TRUE(iNumSp1 == 9215  || iNumSp1 == 9216 );

    // Kill all the seedlings in preparation for the next timestep
    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {
      p_oPop->KillTree(p_oTree, remove_tree);
      p_oTree = p_oAllTrees->NextTree();
    }

    //-----------------------------------------------------------------------//
    // Timestep 3
    //-----------------------------------------------------------------------//
    p_oSimManager->RunSim(1);

    fExpectedValue = 1;
    p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("rodent_lambda"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

    //Count the number of seedlings of each type
    iNumSp1 = 0;
    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {
      if (p_oTree->GetType() == clTreePopulation::seedling) {
        if (p_oTree->GetSpecies() == 0) iNumSp1++;
        else FAIL() << "DensDepRodentSeedPredation doesn't know what this seedling is";
      }
      p_oTree = p_oAllTrees->NextTree();
    }

    //Check the counts
    EXPECT_TRUE(iNumSp1 == 0 || iNumSp1 == 1);

    // Kill all the seedlings in preparation for the next timestep
    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {
      p_oPop->KillTree(p_oTree, remove_tree);
      p_oTree = p_oAllTrees->NextTree();
    }

    //-----------------------------------------------------------------------//
    // Timestep 4
    //-----------------------------------------------------------------------//
    p_oSimManager->RunSim(1);

    fExpectedValue = 0.0001;
    p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("rodent_lambda"), &fValue);
    EXPECT_LT(fabs(fExpectedValue - fValue), 0.001);

    //Count the number of seedlings of each type
    iNumSp1 = 0;
    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {
      if (p_oTree->GetType() == clTreePopulation::seedling) {
        if (p_oTree->GetSpecies() == 0) iNumSp1++;
        else FAIL() << "DensDepRodentSeedPredation doesn't know what this seedling is";
      }
      p_oTree = p_oAllTrees->NextTree();
    }

    //Check the counts
    EXPECT_TRUE(iNumSp1 == 9215  || iNumSp1 == 9216 );

    // Kill all the seedlings in preparation for the next timestep
    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {
      p_oPop->KillTree(p_oTree, remove_tree);
      p_oTree = p_oAllTrees->NextTree();
    }

    delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}



/////////////////////////////////////////////////////////////////////////////
// TestNormalProcessingRun3()
// Species share the same copy of Masting Disperse with Autocorrelation.
/////////////////////////////////////////////////////////////////////////////
TEST(DensDepRodentSeedPredation, TestNormalProcessingRun3)
{
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    //Feed our file to the sim manager
    p_oSimManager->ReadFile(WriteDensDepRodentSeedPredationXMLFile3());
    clTreePopulation *p_oPop = (clTreePopulation *) p_oSimManager->GetPopulationObject("treepopulation");
    clTreeSearch *p_oAllTrees;
    clTree *p_oTree;

    int iNumSp1, iNumSp2, iNumSp3, iNumSp4;

    //-----------------------------------------------------------------------//
    //Timestep 1: the number of seeds will be fed in by non-spatial disperse.
    //There are no parents, and that's on purpose. They can't mess with our
    //seed inputs
    //-----------------------------------------------------------------------//
    p_oSimManager->RunSim(1);

    //Count the number of seedlings of each type
    iNumSp1 = 0;
    iNumSp2 = 0;
    iNumSp3 = 0;
    iNumSp4 = 0;
    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {
      if (p_oTree->GetType() == clTreePopulation::seedling) {
        if (p_oTree->GetSpecies() == 0) iNumSp1++;
        else if (p_oTree->GetSpecies() == 1) iNumSp2++;
        else if (p_oTree->GetSpecies() == 2) iNumSp3++;
        else if (p_oTree->GetSpecies() == 3) iNumSp4++;
        else FAIL() << "DensDepRodentSeedPredation doesn't know what this seedling is";
      }
      p_oTree = p_oAllTrees->NextTree();
    }

    //Check the counts
    EXPECT_TRUE(iNumSp1 == 126 || iNumSp1 == 127);
    EXPECT_TRUE(iNumSp2 == 252 || iNumSp2 == 253);
    EXPECT_TRUE(iNumSp3 == 27648);
    EXPECT_TRUE(iNumSp4 == 504 || iNumSp4 == 505);

    // Kill all the seedlings in preparation for the next timestep
    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {
      p_oPop->KillTree(p_oTree, remove_tree);
      p_oTree = p_oAllTrees->NextTree();
    }

    //-----------------------------------------------------------------------//
    // Timestep 2
    //-----------------------------------------------------------------------//
    p_oSimManager->RunSim(1);

    //Count the number of seedlings of each type
    iNumSp1 = 0;
    iNumSp2 = 0;
    iNumSp3 = 0;
    iNumSp4 = 0;
    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {
      if (p_oTree->GetType() == clTreePopulation::seedling) {
        if (p_oTree->GetSpecies() == 0) iNumSp1++;
        else if (p_oTree->GetSpecies() == 1) iNumSp2++;
        else if (p_oTree->GetSpecies() == 2) iNumSp3++;
        else if (p_oTree->GetSpecies() == 3) iNumSp4++;
        else FAIL() << "DensDepRodentSeedPredation doesn't know what this seedling is";
      }
      p_oTree = p_oAllTrees->NextTree();
    }

    //Check the counts
    EXPECT_TRUE(iNumSp1 == 7955  || iNumSp1 == 7956 );
    EXPECT_TRUE(iNumSp2 == 15911 || iNumSp2 == 15912);
    EXPECT_TRUE(iNumSp3 == 27648);
    EXPECT_TRUE(iNumSp4 == 31822 || iNumSp4 == 31823);

    // Kill all the seedlings in preparation for the next timestep
    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {
      p_oPop->KillTree(p_oTree, remove_tree);
      p_oTree = p_oAllTrees->NextTree();
    }

    //-----------------------------------------------------------------------//
    // Timestep 3
    //-----------------------------------------------------------------------//
    p_oSimManager->RunSim(1);

    //Count the number of seedlings of each type
    iNumSp1 = 0;
    iNumSp2 = 0;
    iNumSp3 = 0;
    iNumSp4 = 0;
    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {
      if (p_oTree->GetType() == clTreePopulation::seedling) {
        if (p_oTree->GetSpecies() == 0) iNumSp1++;
        else if (p_oTree->GetSpecies() == 1) iNumSp2++;
        else if (p_oTree->GetSpecies() == 2) iNumSp3++;
        else if (p_oTree->GetSpecies() == 3) iNumSp4++;
        else FAIL() << "DensDepRodentSeedPredation doesn't know what this seedling is";
      }
      p_oTree = p_oAllTrees->NextTree();
    }

    //Check the counts
    EXPECT_TRUE(iNumSp1 == 339   || iNumSp1 == 340  );
    EXPECT_TRUE(iNumSp2 == 679   || iNumSp2 == 680  );
    EXPECT_TRUE(iNumSp3 == 27648);
    EXPECT_TRUE(iNumSp4 == 1359  || iNumSp4 == 1360 );

    // Kill all the seedlings in preparation for the next timestep
    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {
      p_oPop->KillTree(p_oTree, remove_tree);
      p_oTree = p_oAllTrees->NextTree();
    }

    //-----------------------------------------------------------------------//
    // Timestep 4
    //-----------------------------------------------------------------------//
    p_oSimManager->RunSim(1);

    //Count the number of seedlings of each type
    iNumSp1 = 0;
    iNumSp2 = 0;
    iNumSp3 = 0;
    iNumSp4 = 0;
    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {
      if (p_oTree->GetType() == clTreePopulation::seedling) {
        if (p_oTree->GetSpecies() == 0) iNumSp1++;
        else if (p_oTree->GetSpecies() == 1) iNumSp2++;
        else if (p_oTree->GetSpecies() == 2) iNumSp3++;
        else if (p_oTree->GetSpecies() == 3) iNumSp4++;
        else FAIL() << "DensDepRodentSeedPredation doesn't know what this seedling is";
      }
      p_oTree = p_oAllTrees->NextTree();
    }

    //Check the counts
    EXPECT_TRUE(iNumSp1 == 6188  || iNumSp1 == 6189 );
    EXPECT_TRUE(iNumSp2 == 12376 || iNumSp2 == 12377);
    EXPECT_TRUE(iNumSp3 == 27648);
    EXPECT_TRUE(iNumSp4 == 24752 || iNumSp4 == 24753);

    // Kill all the seedlings in preparation for the next timestep
    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {
      p_oPop->KillTree(p_oTree, remove_tree);
      p_oTree = p_oAllTrees->NextTree();
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
TEST(DensDepRodentSeedPredation, TestErrorProcessing)
{
  using namespace std;
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try
  {
    p_oSimManager->ReadFile(WriteDensDepRodentSeedPredationErrorFile1());
    FAIL() << "TestDensDepRodentSeedPredation error processing didn't catch error for WriteDensDepRodentSeedPredationErrorFile1.";
  }
  catch (modelErr& err)
  {
    if (err.sFunction.compare("clDensDepRodentSeedPredation::GetMastingIndexes") != 0)
    {
      FAIL() << "TestDensDepRodentSeedPredation error processing caught wrong error for WriteDensDepRodentSeedPredationXMLErrorFile1.";
    }
    ;
  }

  delete p_oSimManager;
}

/////////////////////////////////////////////////////////////////////////////
// WriteDensDepRodentSeedPredationXMLFile1()
/////////////////////////////////////////////////////////////////////////////
const char* WriteDensDepRodentSeedPredationXMLFile1()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06010101\">" << "<plot>"
       << "<timesteps>4</timesteps>"
       << "<yearsPerTimestep>1</yearsPerTimestep>"
       << "<randomSeed>1</randomSeed>"
       << "<plot_lenX>96</plot_lenX>"
       << "<plot_lenY>96</plot_lenY>"
       << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
       << "<plot_temp_C>12.88171785</plot_temp_C>"
       << "<plot_latitude>55.37</plot_latitude>"
       << "</plot>";

  WriteDensDepRodentSeedPredationTreesAllometry(oOut);

  oOut << "<grid gridName=\"Dispersed Seeds\">"
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
       << "<ma_lengthXCells>96</ma_lengthXCells>"
       << "<ma_lengthYCells>96</ma_lengthYCells>"
       << "</grid>"
       << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>NonSpatialDisperse</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_4\" type=\"Adult\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>MastingDisperseAutocorrelation</behaviorName>"
       << "<version>1.0</version>"
       << "<listPosition>2</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>MastingDisperseAutocorrelation</behaviorName>"
       << "<version>1.0</version>"
       << "<listPosition>3</listPosition>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>MastingDisperseAutocorrelation</behaviorName>"
       << "<version>1.0</version>"
       << "<listPosition>4</listPosition>"
       << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>MastingDisperseAutocorrelation</behaviorName>"
       << "<version>1.0</version>"
       << "<listPosition>5</listPosition>"
       << "<applyTo species=\"Species_4\" type=\"Adult\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>DensDepRodentSeedPredation</behaviorName>"
       << "<version>1.0</version>"
       << "<listPosition>6</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Seed\"/>"
       << "<applyTo species=\"Species_2\" type=\"Seed\"/>"
       << "<applyTo species=\"Species_4\" type=\"Seed\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>Establishment</behaviorName>"
       << "<version>1.0</version>"
       << "<listPosition>7</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Seed\"/>"
       << "<applyTo species=\"Species_2\" type=\"Seed\"/>"
       << "<applyTo species=\"Species_3\" type=\"Seed\"/>"
       << "<applyTo species=\"Species_4\" type=\"Seed\"/>"
       << "</behavior>"
       << "</behaviorList>"
       << "<GeneralDisperse>"
       << "<di_seedDistributionMethod>0</di_seedDistributionMethod>"
       << "</GeneralDisperse>"
       << "<NonSpatialDisperse1>"
       << "<di_minDbhForReproduction>"
       << "<di_mdfrVal species=\"Species_1\">15.0</di_mdfrVal>"
       << "<di_mdfrVal species=\"Species_2\">15.0</di_mdfrVal>"
       << "<di_mdfrVal species=\"Species_3\">15.0</di_mdfrVal>"
       << "<di_mdfrVal species=\"Species_4\">15.0</di_mdfrVal>"
       << "</di_minDbhForReproduction>"
       << "<di_nonSpatialSlopeOfLambda>"
       << "<di_nssolVal species=\"Species_4\">0</di_nssolVal>"
       << "<di_nssolVal species=\"Species_2\">0</di_nssolVal>"
       << "<di_nssolVal species=\"Species_3\">0</di_nssolVal>"
       << "<di_nssolVal species=\"Species_1\">0</di_nssolVal>"
       << "</di_nonSpatialSlopeOfLambda>"
       << "<di_nonSpatialInterceptOfLambda>"
       << "<di_nsiolVal species=\"Species_1\">1</di_nsiolVal>"
       << "<di_nsiolVal species=\"Species_2\">2</di_nsiolVal>"
       << "<di_nsiolVal species=\"Species_3\">3</di_nsiolVal>"
       << "<di_nsiolVal species=\"Species_4\">4</di_nsiolVal>"
       << "</di_nonSpatialInterceptOfLambda>"
       << "</NonSpatialDisperse1>"
       << "<MastingDisperseAutocorrelation2>"
       << "<di_minDbhForReproduction>"
       << "<di_mdfrVal species=\"Species_1\">15.0</di_mdfrVal>"
       << "</di_minDbhForReproduction>"
       //Mast timeseries
       << "<di_mdaMastTS>"
       << "<di_mdaMTS ts=\"1\">0.49</di_mdaMTS>"
       << "<di_mdaMTS ts=\"2\">0.04</di_mdaMTS>"
       << "<di_mdaMTS ts=\"3\">0.89</di_mdaMTS>"
       << "<di_mdaMTS ts=\"4\">0.29</di_mdaMTS>"
       << "</di_mdaMastTS>"
       << "<di_maxDbhForSizeEffect>"
       << "<di_mdfseVal species=\"Species_1\">100</di_mdfseVal>"
       << "</di_maxDbhForSizeEffect>"
       << "<di_weibullCanopyBeta>"
       << "<di_wcbVal species=\"Species_1\">1</di_wcbVal>"
       << "</di_weibullCanopyBeta>"
       << "<di_weibullCanopySTR>"
       << "<di_wcsVal species=\"Species_1\">1000</di_wcsVal>"
       << "</di_weibullCanopySTR>"
       << "<di_mdaReproFracA>"
       << "<di_mdarfaVal species=\"Species_1\">1</di_mdarfaVal>"
       << "</di_mdaReproFracA>"
       << "<di_mdaReproFracB>"
       << "<di_mdarfbVal species=\"Species_1\">1</di_mdarfbVal>"
       << "</di_mdaReproFracB>"
       << "<di_mdaReproFracC>"
       << "<di_mdarfcVal species=\"Species_1\">0</di_mdarfcVal>"
       << "</di_mdaReproFracC>"
       << "<di_mdaRhoACF>"
       << "<di_mdaraVal species=\"Species_1\">1</di_mdaraVal>"
       << "</di_mdaRhoACF>"
       << "<di_mdaRhoNoiseSD>"
       << "<di_mdarnsdVal species=\"Species_1\">0</di_mdarnsdVal>"
       << "</di_mdaRhoNoiseSD>"
       << "<di_mdaPRA>"
       << "<di_mdapraVal species=\"Species_1\">0.75</di_mdapraVal>"
       << "</di_mdaPRA>"
       << "<di_mdaPRB>"
       << "<di_mdaprbVal species=\"Species_1\">0.004</di_mdaprbVal>"
       << "</di_mdaPRB>"
       << "<di_mdaSPSSD>"
       << "<di_mdaspssdVal species=\"Species_1\">0.1</di_mdaspssdVal>"
       << "</di_mdaSPSSD>"
       << "<di_canopyFunction>"
       << "<di_cfVal species=\"Species_1\">0</di_cfVal>"
       << "</di_canopyFunction>"
       << "<di_weibullCanopyDispersal>"
       << "<di_wcdVal species=\"Species_1\">1.76E-04</di_wcdVal>"
       << "</di_weibullCanopyDispersal>"
       << "<di_weibullCanopyTheta>"
       << "<di_wctVal species=\"Species_1\">3</di_wctVal>"
       << "</di_weibullCanopyTheta>"
       << "</MastingDisperseAutocorrelation2>"

       << "<MastingDisperseAutocorrelation3>"
       << "<di_minDbhForReproduction>"
       << "<di_mdfrVal species=\"Species_2\">15.0</di_mdfrVal>"
       << "</di_minDbhForReproduction>"
       //Mast timeseries
       << "<di_mdaMastTS>"
       << "<di_mdaMTS ts=\"1\">0.5</di_mdaMTS>"
       << "<di_mdaMTS ts=\"2\">0.29</di_mdaMTS>"
       << "<di_mdaMTS ts=\"3\">0.05</di_mdaMTS>"
       << "<di_mdaMTS ts=\"4\">0.63</di_mdaMTS>"
       << "</di_mdaMastTS>"
       << "<di_maxDbhForSizeEffect>"
       << "<di_mdfseVal species=\"Species_2\">100</di_mdfseVal>"
       << "</di_maxDbhForSizeEffect>"
       << "<di_weibullCanopyBeta>"
       << "<di_wcbVal species=\"Species_2\">1</di_wcbVal>"
       << "</di_weibullCanopyBeta>"
       << "<di_weibullCanopySTR>"
       << "<di_wcsVal species=\"Species_2\">1000</di_wcsVal>"
       << "</di_weibullCanopySTR>"
       << "<di_mdaReproFracA>"
       << "<di_mdarfaVal species=\"Species_2\">10000</di_mdarfaVal>"
       << "</di_mdaReproFracA>"
       << "<di_mdaReproFracB>"
       << "<di_mdarfbVal species=\"Species_2\">1</di_mdarfbVal>"
       << "</di_mdaReproFracB>"
       << "<di_mdaReproFracC>"
       << "<di_mdarfcVal species=\"Species_2\">1</di_mdarfcVal>"
       << "</di_mdaReproFracC>"
       << "<di_mdaRhoACF>"
       << "<di_mdaraVal species=\"Species_2\">1</di_mdaraVal>"
       << "</di_mdaRhoACF>"
       << "<di_mdaRhoNoiseSD>"
       << "<di_mdarnsdVal species=\"Species_2\">0</di_mdarnsdVal>"
       << "</di_mdaRhoNoiseSD>"
       << "<di_mdaPRA>"
       << "<di_mdapraVal species=\"Species_2\">100</di_mdapraVal>"
       << "</di_mdaPRA>"
       << "<di_mdaPRB>"
       << "<di_mdaprbVal species=\"Species_2\">0.004</di_mdaprbVal>"
       << "</di_mdaPRB>"
       << "<di_mdaSPSSD>"
       << "<di_mdaspssdVal species=\"Species_2\">0.1</di_mdaspssdVal>"
       << "</di_mdaSPSSD>"
       << "<di_canopyFunction>"
       << "<di_cfVal species=\"Species_2\">0</di_cfVal>"
       << "</di_canopyFunction>"
       << "<di_weibullCanopyDispersal>"
       << "<di_wcdVal species=\"Species_2\">1.82E-04</di_wcdVal>"
       << "</di_weibullCanopyDispersal>"
       << "<di_weibullCanopyTheta>"
       << "<di_wctVal species=\"Species_2\">3</di_wctVal>"
       << "</di_weibullCanopyTheta>"
       << "</MastingDisperseAutocorrelation3>"
       << "<MastingDisperseAutocorrelation4>"
       << "<di_minDbhForReproduction>"
       << "<di_mdfrVal species=\"Species_3\">15.0</di_mdfrVal>"
       << "</di_minDbhForReproduction>"
       //Mast timeseries
       << "<di_mdaMastTS>"
       << "<di_mdaMTS ts=\"1\">0.71</di_mdaMTS>"
       << "<di_mdaMTS ts=\"2\">0.76</di_mdaMTS>"
       << "<di_mdaMTS ts=\"3\">0.16</di_mdaMTS>"
       << "<di_mdaMTS ts=\"4\">0.33</di_mdaMTS>"
       << "</di_mdaMastTS>"
       << "<di_maxDbhForSizeEffect>"
       << "<di_mdfseVal species=\"Species_3\">100</di_mdfseVal>"
       << "</di_maxDbhForSizeEffect>"
       << "<di_weibullCanopyBeta>"
       << "<di_wcbVal species=\"Species_3\">1</di_wcbVal>"
       << "</di_weibullCanopyBeta>"
       << "<di_weibullCanopySTR>"
       << "<di_wcsVal species=\"Species_3\">1</di_wcsVal>"
       << "</di_weibullCanopySTR>"
       << "<di_mdaReproFracA>"
       << "<di_mdarfaVal species=\"Species_3\">10000</di_mdarfaVal>"
       << "</di_mdaReproFracA>"
       << "<di_mdaReproFracB>"
       << "<di_mdarfbVal species=\"Species_3\">1</di_mdarfbVal>"
       << "</di_mdaReproFracB>"
       << "<di_mdaReproFracC>"
       << "<di_mdarfcVal species=\"Species_3\">1</di_mdarfcVal>"
       << "</di_mdaReproFracC>"
       << "<di_mdaRhoACF>"
       << "<di_mdaraVal species=\"Species_3\">1</di_mdaraVal>"
       << "</di_mdaRhoACF>"
       << "<di_mdaRhoNoiseSD>"
       << "<di_mdarnsdVal species=\"Species_3\">0</di_mdarnsdVal>"
       << "</di_mdaRhoNoiseSD>"
       << "<di_mdaPRA>"
       << "<di_mdapraVal species=\"Species_3\">100</di_mdapraVal>"
       << "</di_mdaPRA>"
       << "<di_mdaPRB>"
       << "<di_mdaprbVal species=\"Species_3\">0.004</di_mdaprbVal>"
       << "</di_mdaPRB>"
       << "<di_mdaSPSSD>"
       << "<di_mdaspssdVal species=\"Species_3\">0</di_mdaspssdVal>"
       << "</di_mdaSPSSD>"
       << "<di_canopyFunction>"
       << "<di_cfVal species=\"Species_3\">0</di_cfVal>"
       << "</di_canopyFunction>"
       << "<di_weibullCanopyDispersal>"
       << "<di_wcdVal species=\"Species_3\">1.82E-04</di_wcdVal>"
       << "</di_weibullCanopyDispersal>"
       << "<di_weibullCanopyTheta>"
       << "<di_wctVal species=\"Species_3\">3</di_wctVal>"
       << "</di_weibullCanopyTheta>"
       << "</MastingDisperseAutocorrelation4>"

       << "<MastingDisperseAutocorrelation5>"
       << "<di_minDbhForReproduction>"
       << "<di_mdfrVal species=\"Species_4\">15.0</di_mdfrVal>"
       << "</di_minDbhForReproduction>"
       << "<di_mdaMastTS>"
       << "<di_mdaMTS ts=\"1\">0.71</di_mdaMTS>"
       << "<di_mdaMTS ts=\"2\">0.76</di_mdaMTS>"
       << "<di_mdaMTS ts=\"3\">0.16</di_mdaMTS>"
       << "<di_mdaMTS ts=\"4\">0.33</di_mdaMTS>"
       << "</di_mdaMastTS>"
       << "<di_maxDbhForSizeEffect>"
       << "<di_mdfseVal species=\"Species_4\">100</di_mdfseVal>"
       << "</di_maxDbhForSizeEffect>"
       << "<di_weibullCanopyBeta>"
       << "<di_wcbVal species=\"Species_4\">1</di_wcbVal>"
       << "</di_weibullCanopyBeta>"
       << "<di_weibullCanopySTR>"
       << "<di_wcsVal species=\"Species_4\">1000</di_wcsVal>"
       << "</di_weibullCanopySTR>"
       << "<di_mdaReproFracA>"
       << "<di_mdarfaVal species=\"Species_4\">10000</di_mdarfaVal>"
       << "</di_mdaReproFracA>"
       << "<di_mdaReproFracB>"
       << "<di_mdarfbVal species=\"Species_4\">1</di_mdarfbVal>"
       << "</di_mdaReproFracB>"
       << "<di_mdaReproFracC>"
       << "<di_mdarfcVal species=\"Species_4\">1</di_mdarfcVal>"
       << "</di_mdaReproFracC>"
       << "<di_mdaRhoACF>"
       << "<di_mdaraVal species=\"Species_4\">1</di_mdaraVal>"
       << "</di_mdaRhoACF>"
       << "<di_mdaRhoNoiseSD>"
       << "<di_mdarnsdVal species=\"Species_4\">0</di_mdarnsdVal>"
       << "</di_mdaRhoNoiseSD>"
       << "<di_mdaPRA>"
       << "<di_mdapraVal species=\"Species_4\">100</di_mdapraVal>"
       << "</di_mdaPRA>"
       << "<di_mdaPRB>"
       << "<di_mdaprbVal species=\"Species_4\">0.004</di_mdaprbVal>"
       << "</di_mdaPRB>"
       << "<di_mdaSPSSD>"
       << "<di_mdaspssdVal species=\"Species_4\">0.1</di_mdaspssdVal>"
       << "</di_mdaSPSSD>"
       << "<di_canopyFunction>"
       << "<di_cfVal species=\"Species_4\">0</di_cfVal>"
       << "</di_canopyFunction>"
       << "<di_weibullCanopyDispersal>"
       << "<di_wcdVal species=\"Species_4\">9.61E-05</di_wcdVal>"
       << "</di_weibullCanopyDispersal>"
       << "<di_weibullCanopyTheta>"
       << "<di_wctVal species=\"Species_4\">3</di_wctVal>"
       << "</di_weibullCanopyTheta>"
       << "</MastingDisperseAutocorrelation5>"

       << "<DensDepRodentSeedPredation6>"
       << "<pr_densDepFuncRespSlope>"
       << "<pr_ddfrsVal species=\"Species_1\">0.9</pr_ddfrsVal>"
       << "<pr_ddfrsVal species=\"Species_2\">0.05</pr_ddfrsVal>"
       << "<pr_ddfrsVal species=\"Species_4\">0.4</pr_ddfrsVal>"
       << "</pr_densDepFuncRespSlope>"
       << "<pr_densDepFuncRespA>0.02</pr_densDepFuncRespA>"
       << "<pr_densDepDensCoeff>0.07</pr_densDepDensCoeff>"
       << "</DensDepRodentSeedPredation6>"

       << "</paramFile>";

  oOut.close();

  return cFileString;
}


/////////////////////////////////////////////////////////////////////////////
// WriteDensDepRodentSeedPredationXMLFile2()
/////////////////////////////////////////////////////////////////////////////
const char* WriteDensDepRodentSeedPredationXMLFile2()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06010101\">" << "<plot>"
       << "<timesteps>4</timesteps>"
       << "<yearsPerTimestep>1</yearsPerTimestep>"
       << "<randomSeed>1</randomSeed>"
       << "<plot_lenX>96</plot_lenX>"
       << "<plot_lenY>96</plot_lenY>"
       << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
       << "<plot_temp_C>12.88171785</plot_temp_C>"
       << "<plot_latitude>55.37</plot_latitude>"
       << "</plot>";

  WriteDensDepRodentSeedPredationTreesAllometry(oOut);

  oOut << "<grid gridName=\"Dispersed Seeds\">"
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
       << "<ma_lengthXCells>96</ma_lengthXCells>"
       << "<ma_lengthYCells>96</ma_lengthYCells>"
       << "</grid>"
       << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>NonSpatialDisperse</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>MastingDisperseAutocorrelation</behaviorName>"
       << "<version>1.0</version>"
       << "<listPosition>2</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>DensDepRodentSeedPredation</behaviorName>"
       << "<version>1.0</version>"
       << "<listPosition>3</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Seed\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>Establishment</behaviorName>"
       << "<version>1.0</version>"
       << "<listPosition>4</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Seed\"/>"
       << "</behavior>"
       << "</behaviorList>"
       << "<GeneralDisperse>"
       << "<di_seedDistributionMethod>0</di_seedDistributionMethod>"
       << "</GeneralDisperse>"
       << "<NonSpatialDisperse1>"
       << "<di_minDbhForReproduction>"
       << "<di_mdfrVal species=\"Species_1\">15.0</di_mdfrVal>"
       << "</di_minDbhForReproduction>"
       << "<di_nonSpatialSlopeOfLambda>"
       << "<di_nssolVal species=\"Species_1\">0</di_nssolVal>"
       << "</di_nonSpatialSlopeOfLambda>"
       << "<di_nonSpatialInterceptOfLambda>"
       << "<di_nsiolVal species=\"Species_1\">1</di_nsiolVal>"
       << "</di_nonSpatialInterceptOfLambda>"
       << "</NonSpatialDisperse1>"
       << "<MastingDisperseAutocorrelation2>"
       << "<di_minDbhForReproduction>"
       << "<di_mdfrVal species=\"Species_1\">15.0</di_mdfrVal>"
       << "</di_minDbhForReproduction>"
       //Mast timeseries
       << "<di_mdaMastTS>"
       << "<di_mdaMTS ts=\"1\">0.49</di_mdaMTS>"
       << "<di_mdaMTS ts=\"2\">0.04</di_mdaMTS>"
       << "<di_mdaMTS ts=\"3\">0.89</di_mdaMTS>"
       << "<di_mdaMTS ts=\"4\">0.29</di_mdaMTS>"
       << "</di_mdaMastTS>"
       << "<di_maxDbhForSizeEffect>"
       << "<di_mdfseVal species=\"Species_1\">100</di_mdfseVal>"
       << "</di_maxDbhForSizeEffect>"
       << "<di_weibullCanopyBeta>"
       << "<di_wcbVal species=\"Species_1\">1</di_wcbVal>"
       << "</di_weibullCanopyBeta>"
       << "<di_weibullCanopySTR>"
       << "<di_wcsVal species=\"Species_1\">1000</di_wcsVal>"
       << "</di_weibullCanopySTR>"
       << "<di_mdaReproFracA>"
       << "<di_mdarfaVal species=\"Species_1\">1</di_mdarfaVal>"
       << "</di_mdaReproFracA>"
       << "<di_mdaReproFracB>"
       << "<di_mdarfbVal species=\"Species_1\">1</di_mdarfbVal>"
       << "</di_mdaReproFracB>"
       << "<di_mdaReproFracC>"
       << "<di_mdarfcVal species=\"Species_1\">0</di_mdarfcVal>"
       << "</di_mdaReproFracC>"
       << "<di_mdaRhoACF>"
       << "<di_mdaraVal species=\"Species_1\">1</di_mdaraVal>"
       << "</di_mdaRhoACF>"
       << "<di_mdaRhoNoiseSD>"
       << "<di_mdarnsdVal species=\"Species_1\">0</di_mdarnsdVal>"
       << "</di_mdaRhoNoiseSD>"
       << "<di_mdaPRA>"
       << "<di_mdapraVal species=\"Species_1\">0.75</di_mdapraVal>"
       << "</di_mdaPRA>"
       << "<di_mdaPRB>"
       << "<di_mdaprbVal species=\"Species_1\">0.004</di_mdaprbVal>"
       << "</di_mdaPRB>"
       << "<di_mdaSPSSD>"
       << "<di_mdaspssdVal species=\"Species_1\">0.1</di_mdaspssdVal>"
       << "</di_mdaSPSSD>"
       << "<di_canopyFunction>"
       << "<di_cfVal species=\"Species_1\">0</di_cfVal>"
       << "</di_canopyFunction>"
       << "<di_weibullCanopyDispersal>"
       << "<di_wcdVal species=\"Species_1\">1.76E-04</di_wcdVal>"
       << "</di_weibullCanopyDispersal>"
       << "<di_weibullCanopyTheta>"
       << "<di_wctVal species=\"Species_1\">3</di_wctVal>"
       << "</di_weibullCanopyTheta>"
       << "</MastingDisperseAutocorrelation2>"


       << "<DensDepRodentSeedPredation3>"
       << "<pr_densDepFuncRespSlope>"
       << "<pr_ddfrsVal species=\"Species_1\">3</pr_ddfrsVal>"
       << "</pr_densDepFuncRespSlope>"
       << "<pr_densDepFuncRespA>-1</pr_densDepFuncRespA>"
       << "<pr_densDepDensCoeff>0.07</pr_densDepDensCoeff>"
       << "</DensDepRodentSeedPredation3>"

       << "</paramFile>";

  oOut.close();

  return cFileString;
}


/////////////////////////////////////////////////////////////////////////////
// WriteDensDepRodentSeedPredationXMLFile3()
/////////////////////////////////////////////////////////////////////////////
const char* WriteDensDepRodentSeedPredationXMLFile3()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06010101\">" << "<plot>"
       << "<timesteps>4</timesteps>"
       << "<yearsPerTimestep>1</yearsPerTimestep>"
       << "<randomSeed>1</randomSeed>"
       << "<plot_lenX>96</plot_lenX>"
       << "<plot_lenY>96</plot_lenY>"
       << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
       << "<plot_temp_C>12.88171785</plot_temp_C>"
       << "<plot_latitude>55.37</plot_latitude>"
       << "</plot>";

  WriteDensDepRodentSeedPredationTreesAllometry(oOut);

  oOut << "<grid gridName=\"Dispersed Seeds\">"
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
       << "<ma_lengthXCells>96</ma_lengthXCells>"
       << "<ma_lengthYCells>96</ma_lengthYCells>"
       << "</grid>"
       << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>NonSpatialDisperse</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_4\" type=\"Adult\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>MastingDisperseAutocorrelation</behaviorName>"
       << "<version>1.0</version>"
       << "<listPosition>2</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_4\" type=\"Adult\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>DensDepRodentSeedPredation</behaviorName>"
       << "<version>1.0</version>"
       << "<listPosition>3</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Seed\"/>"
       << "<applyTo species=\"Species_2\" type=\"Seed\"/>"
       << "<applyTo species=\"Species_4\" type=\"Seed\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>Establishment</behaviorName>"
       << "<version>1.0</version>"
       << "<listPosition>4</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Seed\"/>"
       << "<applyTo species=\"Species_2\" type=\"Seed\"/>"
       << "<applyTo species=\"Species_3\" type=\"Seed\"/>"
       << "<applyTo species=\"Species_4\" type=\"Seed\"/>"
       << "</behavior>"
       << "</behaviorList>"
       << "<GeneralDisperse>"
       << "<di_seedDistributionMethod>0</di_seedDistributionMethod>"
       << "</GeneralDisperse>"
       << "<NonSpatialDisperse1>"
       << "<di_minDbhForReproduction>"
       << "<di_mdfrVal species=\"Species_1\">15.0</di_mdfrVal>"
       << "<di_mdfrVal species=\"Species_2\">15.0</di_mdfrVal>"
       << "<di_mdfrVal species=\"Species_3\">15.0</di_mdfrVal>"
       << "<di_mdfrVal species=\"Species_4\">15.0</di_mdfrVal>"
       << "</di_minDbhForReproduction>"
       << "<di_nonSpatialSlopeOfLambda>"
       << "<di_nssolVal species=\"Species_4\">0</di_nssolVal>"
       << "<di_nssolVal species=\"Species_2\">0</di_nssolVal>"
       << "<di_nssolVal species=\"Species_3\">0</di_nssolVal>"
       << "<di_nssolVal species=\"Species_1\">0</di_nssolVal>"
       << "</di_nonSpatialSlopeOfLambda>"
       << "<di_nonSpatialInterceptOfLambda>"
       << "<di_nsiolVal species=\"Species_1\">1</di_nsiolVal>"
       << "<di_nsiolVal species=\"Species_2\">2</di_nsiolVal>"
       << "<di_nsiolVal species=\"Species_3\">3</di_nsiolVal>"
       << "<di_nsiolVal species=\"Species_4\">4</di_nsiolVal>"
       << "</di_nonSpatialInterceptOfLambda>"
       << "</NonSpatialDisperse1>"
       << "<MastingDisperseAutocorrelation2>"
       << "<di_minDbhForReproduction>"
       << "<di_mdfrVal species=\"Species_1\">15.0</di_mdfrVal>"
       << "<di_mdfrVal species=\"Species_2\">15.0</di_mdfrVal>"
       << "<di_mdfrVal species=\"Species_3\">15.0</di_mdfrVal>"
       << "<di_mdfrVal species=\"Species_4\">15.0</di_mdfrVal>"
       << "</di_minDbhForReproduction>"
       //Mast timeseries
       << "<di_mdaMastTS>"
       << "<di_mdaMTS ts=\"1\">0.49</di_mdaMTS>"
       << "<di_mdaMTS ts=\"2\">0.04</di_mdaMTS>"
       << "<di_mdaMTS ts=\"3\">0.89</di_mdaMTS>"
       << "<di_mdaMTS ts=\"4\">0.29</di_mdaMTS>"
       << "</di_mdaMastTS>"
       << "<di_maxDbhForSizeEffect>"
       << "<di_mdfseVal species=\"Species_1\">100</di_mdfseVal>"
       << "<di_mdfseVal species=\"Species_2\">100</di_mdfseVal>"
       << "<di_mdfseVal species=\"Species_3\">100</di_mdfseVal>"
       << "<di_mdfseVal species=\"Species_4\">100</di_mdfseVal>"
       << "</di_maxDbhForSizeEffect>"
       << "<di_weibullCanopyBeta>"
       << "<di_wcbVal species=\"Species_1\">1</di_wcbVal>"
       << "<di_wcbVal species=\"Species_2\">1</di_wcbVal>"
       << "<di_wcbVal species=\"Species_3\">1</di_wcbVal>"
       << "<di_wcbVal species=\"Species_4\">1</di_wcbVal>"
       << "</di_weibullCanopyBeta>"
       << "<di_weibullCanopySTR>"
       << "<di_wcsVal species=\"Species_1\">1000</di_wcsVal>"
       << "<di_wcsVal species=\"Species_2\">1000</di_wcsVal>"
       << "<di_wcsVal species=\"Species_3\">1000</di_wcsVal>"
       << "<di_wcsVal species=\"Species_4\">1000</di_wcsVal>"
       << "</di_weibullCanopySTR>"
       << "<di_mdaReproFracA>"
       << "<di_mdarfaVal species=\"Species_1\">1</di_mdarfaVal>"
       << "<di_mdarfaVal species=\"Species_2\">1</di_mdarfaVal>"
       << "<di_mdarfaVal species=\"Species_3\">1</di_mdarfaVal>"
       << "<di_mdarfaVal species=\"Species_4\">1</di_mdarfaVal>"
       << "</di_mdaReproFracA>"
       << "<di_mdaReproFracB>"
       << "<di_mdarfbVal species=\"Species_1\">1</di_mdarfbVal>"
       << "<di_mdarfbVal species=\"Species_2\">1</di_mdarfbVal>"
       << "<di_mdarfbVal species=\"Species_3\">1</di_mdarfbVal>"
       << "<di_mdarfbVal species=\"Species_4\">1</di_mdarfbVal>"
       << "</di_mdaReproFracB>"
       << "<di_mdaReproFracC>"
       << "<di_mdarfcVal species=\"Species_1\">0</di_mdarfcVal>"
       << "<di_mdarfcVal species=\"Species_2\">0</di_mdarfcVal>"
       << "<di_mdarfcVal species=\"Species_3\">0</di_mdarfcVal>"
       << "<di_mdarfcVal species=\"Species_4\">0</di_mdarfcVal>"
       << "</di_mdaReproFracC>"
       << "<di_mdaRhoACF>"
       << "<di_mdaraVal species=\"Species_1\">1</di_mdaraVal>"
       << "<di_mdaraVal species=\"Species_2\">1</di_mdaraVal>"
       << "<di_mdaraVal species=\"Species_3\">1</di_mdaraVal>"
       << "<di_mdaraVal species=\"Species_4\">1</di_mdaraVal>"
       << "</di_mdaRhoACF>"
       << "<di_mdaRhoNoiseSD>"
       << "<di_mdarnsdVal species=\"Species_1\">0</di_mdarnsdVal>"
       << "<di_mdarnsdVal species=\"Species_2\">0</di_mdarnsdVal>"
       << "<di_mdarnsdVal species=\"Species_3\">0</di_mdarnsdVal>"
       << "<di_mdarnsdVal species=\"Species_4\">0</di_mdarnsdVal>"
       << "</di_mdaRhoNoiseSD>"
       << "<di_mdaPRA>"
       << "<di_mdapraVal species=\"Species_1\">0.75</di_mdapraVal>"
       << "<di_mdapraVal species=\"Species_2\">0.75</di_mdapraVal>"
       << "<di_mdapraVal species=\"Species_3\">0.75</di_mdapraVal>"
       << "<di_mdapraVal species=\"Species_4\">0.75</di_mdapraVal>"
       << "</di_mdaPRA>"
       << "<di_mdaPRB>"
       << "<di_mdaprbVal species=\"Species_1\">0.004</di_mdaprbVal>"
       << "<di_mdaprbVal species=\"Species_2\">0.004</di_mdaprbVal>"
       << "<di_mdaprbVal species=\"Species_3\">0.004</di_mdaprbVal>"
       << "<di_mdaprbVal species=\"Species_4\">0.004</di_mdaprbVal>"
       << "</di_mdaPRB>"
       << "<di_mdaSPSSD>"
       << "<di_mdaspssdVal species=\"Species_1\">0.1</di_mdaspssdVal>"
       << "<di_mdaspssdVal species=\"Species_2\">0.1</di_mdaspssdVal>"
       << "<di_mdaspssdVal species=\"Species_4\">0.1</di_mdaspssdVal>"
       << "<di_mdaspssdVal species=\"Species_3\">0.1</di_mdaspssdVal>"
       << "</di_mdaSPSSD>"
       << "<di_canopyFunction>"
       << "<di_cfVal species=\"Species_1\">0</di_cfVal>"
       << "<di_cfVal species=\"Species_2\">0</di_cfVal>"
       << "<di_cfVal species=\"Species_4\">0</di_cfVal>"
       << "<di_cfVal species=\"Species_3\">0</di_cfVal>"
       << "</di_canopyFunction>"
       << "<di_weibullCanopyDispersal>"
       << "<di_wcdVal species=\"Species_1\">1.76E-04</di_wcdVal>"
       << "<di_wcdVal species=\"Species_2\">1.76E-04</di_wcdVal>"
       << "<di_wcdVal species=\"Species_3\">1.76E-04</di_wcdVal>"
       << "<di_wcdVal species=\"Species_4\">1.76E-04</di_wcdVal>"
       << "</di_weibullCanopyDispersal>"
       << "<di_weibullCanopyTheta>"
       << "<di_wctVal species=\"Species_1\">3</di_wctVal>"
       << "<di_wctVal species=\"Species_2\">3</di_wctVal>"
       << "<di_wctVal species=\"Species_3\">3</di_wctVal>"
       << "<di_wctVal species=\"Species_4\">3</di_wctVal>"
       << "</di_weibullCanopyTheta>"
       << "</MastingDisperseAutocorrelation2>"

       << "<DensDepRodentSeedPredation3>"
       << "<pr_densDepFuncRespSlope>"
       << "<pr_ddfrsVal species=\"Species_1\">0.9</pr_ddfrsVal>"
       << "<pr_ddfrsVal species=\"Species_2\">0.05</pr_ddfrsVal>"
       << "<pr_ddfrsVal species=\"Species_4\">0.4</pr_ddfrsVal>"
       << "</pr_densDepFuncRespSlope>"
       << "<pr_densDepFuncRespA>0.02</pr_densDepFuncRespA>"
       << "<pr_densDepDensCoeff>0.07</pr_densDepDensCoeff>"
       << "</DensDepRodentSeedPredation3>"

       << "</paramFile>";

  oOut.close();

  return cFileString;
}



/////////////////////////////////////////////////////////////////////////////
// WriteDensDepRodentSeedPredationTreesAllometry()
/////////////////////////////////////////////////////////////////////////////
void WriteDensDepRodentSeedPredationTreesAllometry(std::fstream &oOut)
{
  oOut << "<trees>"
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
       << "<tr_chVal species=\"Species_2\">39.54</tr_chVal>"
       << "<tr_chVal species=\"Species_3\">40.0</tr_chVal>"
       << "<tr_chVal species=\"Species_4\">40.0</tr_chVal>"
       << "</tr_canopyHeight>"
       << "<tr_stdAsympCrownRad>"
       << "<tr_sacrVal species=\"Species_1\">0.0549</tr_sacrVal>"
       << "<tr_sacrVal species=\"Species_2\">0.0614</tr_sacrVal>"
       << "<tr_sacrVal species=\"Species_3\">0.0242</tr_sacrVal>"
       << "<tr_sacrVal species=\"Species_4\">0.0242</tr_sacrVal>"
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
       << "<tr_cdtdVal species=\"Species_2\">0.5944</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_3\">0.7059</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_4\">0.7059</tr_cdtdVal>"
       << "</tr_conversionDiam10ToDBH>"
       << "<tr_interceptDiam10ToDBH>"
       << "<tr_idtdVal species=\"Species_1\">0</tr_idtdVal>"
       << "<tr_idtdVal species=\"Species_2\">0</tr_idtdVal>"
       << "<tr_idtdVal species=\"Species_3\">0</tr_idtdVal>"
       << "<tr_idtdVal species=\"Species_4\">0</tr_idtdVal>"
       << "</tr_interceptDiam10ToDBH>"
       << "<tr_stdAsympCrownHt>"
       << "<tr_sachVal species=\"Species_1\">0.389</tr_sachVal>"
       << "<tr_sachVal species=\"Species_2\">0.368</tr_sachVal>"
       << "<tr_sachVal species=\"Species_3\">0.464</tr_sachVal>"
       << "<tr_sachVal species=\"Species_4\">0.464</tr_sachVal>"
       << "</tr_stdAsympCrownHt>"
       << "<tr_stdCrownHtExp>"
       << "<tr_scheVal species=\"Species_1\">1.0</tr_scheVal>"
       << "<tr_scheVal species=\"Species_2\">1.0</tr_scheVal>"
       << "<tr_scheVal species=\"Species_3\">1.0</tr_scheVal>"
       << "<tr_scheVal species=\"Species_4\">1.0</tr_scheVal>"
       << "</tr_stdCrownHtExp>"
       << "<tr_slopeOfHeight-Diam10>"
       << "<tr_sohdVal species=\"Species_1\">0.03418</tr_sohdVal>"
       << "<tr_sohdVal species=\"Species_2\">0.0269</tr_sohdVal>"
       << "<tr_sohdVal species=\"Species_3\">0.02871</tr_sohdVal>"
       << "<tr_sohdVal species=\"Species_4\">0.02871</tr_sohdVal>"
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
}

/////////////////////////////////////////////////////////////////////////////
// WriteDensDepRodentSeedPredationErrorFile1()
/////////////////////////////////////////////////////////////////////////////
const char* WriteDensDepRodentSeedPredationErrorFile1()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06010101\">" << "<plot>"
       << "<timesteps>4</timesteps>"
       << "<yearsPerTimestep>1</yearsPerTimestep>"
       << "<randomSeed>1</randomSeed>"
       << "<plot_lenX>96</plot_lenX>"
       << "<plot_lenY>96</plot_lenY>"
       << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
       << "<plot_temp_C>12.88171785</plot_temp_C>"
       << "<plot_latitude>55.37</plot_latitude>"
       << "</plot>"<< "<trees>"
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
       << "</allometry>";

  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>NonSpatialDisperse</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>DensDepRodentSeedPredation</behaviorName>"
       << "<version>1.0</version>"
       << "<listPosition>2</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Seed\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>Establishment</behaviorName>"
       << "<version>1.0</version>"
       << "<listPosition>3</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Seed\"/>"
       << "</behavior>"
       << "</behaviorList>"
       << "<GeneralDisperse>"
       << "<di_seedDistributionMethod>0</di_seedDistributionMethod>"
       << "</GeneralDisperse>"
       << "<NonSpatialDisperse1>"
       << "<di_minDbhForReproduction>"
       << "<di_mdfrVal species=\"Species_1\">15.0</di_mdfrVal>"
       << "</di_minDbhForReproduction>"
       << "<di_nonSpatialSlopeOfLambda>"
       << "<di_nssolVal species=\"Species_1\">0</di_nssolVal>"
       << "</di_nonSpatialSlopeOfLambda>"
       << "<di_nonSpatialInterceptOfLambda>"
       << "<di_nsiolVal species=\"Species_1\">1</di_nsiolVal>"
       << "</di_nonSpatialInterceptOfLambda>"
       << "</NonSpatialDisperse1>"

       << "<DensDepRodentSeedPredation2>"
       << "<pr_densDepFuncRespSlope>"
       << "<pr_ddfrsVal species=\"Species_1\">0.9</pr_ddfrsVal>"
       << "</pr_densDepFuncRespSlope>"
       << "<pr_densDepFuncRespA>0.02</pr_densDepFuncRespA>"
       << "<pr_densDepDensCoeff>0.07</pr_densDepDensCoeff>"
       << "</DensDepRodentSeedPredation2>"

       << "</paramFile>";

  oOut.close();

  return cFileString;
}
