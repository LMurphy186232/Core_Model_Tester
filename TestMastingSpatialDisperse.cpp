//---------------------------------------------------------------------------
// TestMastingSpatialDisperse.cpp
//---------------------------------------------------------------------------
#include "TestMastingSpatialDisperse.h"
#include <gtest/gtest.h>
#include "TreePopulation.h"
#include "SimManager.h"
#include "MastingSpatialDisperse.h"
#include <stdio.h>
#include <fstream>
#include <math.h>
#include <iostream>

/////////////////////////////////////////////////////////////////////////////
// NormalProcessingRun1()
// Tests first normal processing run. WriteMastingSpatialDisperseXMLFile1() does
// setup. Three trees are created for the plot. The file is run for one timestep
// and the seedlings are counted. A certain number of each species is expected.
// This tests masting and mast grouping.
/////////////////////////////////////////////////////////////////////////////
TEST(MastingSpatialDisperse, NormalProcessingRun1) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    //Feed our file to the sim manager
    p_oSimManager->ReadFile(WriteMastingSpatialDisperseXMLFile1());

    clTreePopulation *p_oPop = (clTreePopulation *) p_oSimManager->GetPopulationObject("treepopulation");
    clTreeSearch *p_oAllTrees;
    clBehaviorBase *p_oTemp = p_oSimManager->GetBehaviorObject("MastingSpatialDisperse");
    clMastingSpatialDisperse *p_oDisp = dynamic_cast<clMastingSpatialDisperse*>(p_oTemp);
    clTree *p_oTree;
    int iNumSp1, iNumSp2, iNumSp4;

    //Create three trees
    p_oPop->CreateTree(1, 1, 0, clTreePopulation::adult, 20.0);
    p_oPop->CreateTree(1, 1, 1, clTreePopulation::adult, 30.0);
    p_oPop->CreateTree(1, 1, 3, clTreePopulation::adult, 40.0);

    //Run one timestep
    p_oSimManager->RunSim(1);

    //Count the number of seedlings of each type
    iNumSp1 = 0;
    iNumSp2 = 0;
    iNumSp4 = 0;
    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {
      if (p_oTree->GetType() == clTreePopulation::seedling) {
        if (p_oTree->GetSpecies() == 0) iNumSp1++;
        else if (p_oTree->GetSpecies() == 1) iNumSp2++;
        else iNumSp4++;
      }
      p_oTree = p_oAllTrees->NextTree();
    }

    //Check that the masting flags were correctly set
    EXPECT_EQ(mast, p_oDisp->GetMastEvent(0));
    EXPECT_EQ(nonmast, p_oDisp->GetMastEvent(1));
    EXPECT_EQ(nonmast, p_oDisp->GetMastEvent(2));
    EXPECT_EQ(mast, p_oDisp->GetMastEvent(3));

    //Check the counts
    EXPECT_TRUE(171 == iNumSp1 || 172 == iNumSp1);
    EXPECT_EQ(35, iNumSp2);
    EXPECT_EQ(168, iNumSp4);

    //Check the time since last mast counters
    EXPECT_EQ(1, p_oDisp->GetTimestepsSinceLastMast(0));
    EXPECT_EQ(2, p_oDisp->GetTimestepsSinceLastMast(1));
    EXPECT_EQ(1, p_oDisp->GetTimestepsSinceLastMast(2));
    delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

/////////////////////////////////////////////////////////////////////////////
// NormalProcessingRun2()
// Tests second normal processing run. WriteMastingSpatialDisperseXMLFile2()
// does setup. This is the same as run 1 except it's three years per timestep.
/////////////////////////////////////////////////////////////////////////////
TEST(MastingSpatialDisperse, NormalProcessingRun2) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    //Feed our file to the sim manager
    p_oSimManager->ReadFile(WriteMastingSpatialDisperseXMLFile2());

    clTreePopulation *p_oPop = (clTreePopulation *) p_oSimManager->GetPopulationObject("treepopulation");
    clTreeSearch *p_oAllTrees;
    clBehaviorBase *p_oTemp = p_oSimManager->GetBehaviorObject("MastingSpatialDisperse");
    clMastingSpatialDisperse *p_oDisp = dynamic_cast<clMastingSpatialDisperse*>(p_oTemp);
    clTree *p_oTree;
    int iNumSp1, iNumSp2, iNumSp4;

    //Create three trees
    p_oPop->CreateTree(1, 1, 0, clTreePopulation::adult, 20.0);
    p_oPop->CreateTree(1, 1, 1, clTreePopulation::adult, 30.0);
    p_oPop->CreateTree(1, 1, 3, clTreePopulation::adult, 40.0);

    //Run one timestep
    p_oSimManager->RunSim(1);

    //Count the number of seedlings of each type
    iNumSp1 = 0;
    iNumSp2 = 0;
    iNumSp4 = 0;
    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {
      if (p_oTree->GetType() == clTreePopulation::seedling) {
        if (p_oTree->GetSpecies() == 0) iNumSp1++;
        else if (p_oTree->GetSpecies() == 1) iNumSp2++;
        else iNumSp4++;
      }
      p_oTree = p_oAllTrees->NextTree();
    }

    //Check the counts
    //EXPECT_EQ(513, iNumSp1 || 514 == iNumSp1);
    //EXPECT_EQ(105, iNumSp2);
    //EXPECT_EQ(504, iNumSp4);

    //Check that the masting flags were correctly set
    EXPECT_EQ(mast, p_oDisp->GetMastEvent(0));
    EXPECT_EQ(nonmast, p_oDisp->GetMastEvent(1));
    EXPECT_EQ(nonmast, p_oDisp->GetMastEvent(2));
    EXPECT_EQ(mast, p_oDisp->GetMastEvent(3));

    //Check the time since last mast counters
    EXPECT_EQ(1, p_oDisp->GetTimestepsSinceLastMast(0));
    EXPECT_EQ(2, p_oDisp->GetTimestepsSinceLastMast(1));
    EXPECT_EQ(1, p_oDisp->GetTimestepsSinceLastMast(2));
    delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

/////////////////////////////////////////////////////////////////////////////
// NormalProcessingRun3()
// Tests third normal processing run. WriteMastingSpatialDisperseXMLFile3() does setup. This tests
// fraction participating. It is just like run 1 except 100 trees are created
// for each species and the final seedling counts should reflect the
// number of parents that participated.
/////////////////////////////////////////////////////////////////////////////
TEST(MastingSpatialDisperse, NormalProcessingRun3) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    //Feed our file to the sim manager
    p_oSimManager->ReadFile(WriteMastingSpatialDisperseXMLFile3());

    clTreePopulation *p_oPop = (clTreePopulation *) p_oSimManager->GetPopulationObject("treepopulation");
    clTreeSearch *p_oAllTrees;
    clBehaviorBase *p_oTemp = p_oSimManager->GetBehaviorObject("MastingSpatialDisperse");
    clMastingSpatialDisperse *p_oDisp = dynamic_cast<clMastingSpatialDisperse*>(p_oTemp);
    clTree *p_oTree;
    int iNumSp1, iNumSp2, iNumSp4, i;

    //Create three hundred trees
    for (i = 0; i < 100; i++) {
      p_oPop->CreateTree(1, 1, 0, clTreePopulation::adult, 20.0);
      p_oPop->CreateTree(1, 1, 1, clTreePopulation::adult, 30.0);
      p_oPop->CreateTree(1, 1, 3, clTreePopulation::adult, 40.0);
    }

    //Run one timestep
    p_oSimManager->RunSim(1);

    //Count the number of seedlings of each type
    iNumSp1 = 0;
    iNumSp2 = 0;
    iNumSp4 = 0;
    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {
      if (p_oTree->GetType() == clTreePopulation::seedling) {
        if (p_oTree->GetSpecies() == 0) iNumSp1++;
        else if (p_oTree->GetSpecies() == 1) iNumSp2++;
        else iNumSp4++;
      }
      p_oTree = p_oAllTrees->NextTree();
    }

    //Check that the masting flags were correctly set
    EXPECT_EQ(mast, p_oDisp->GetMastEvent(0));
    EXPECT_EQ(nonmast, p_oDisp->GetMastEvent(1));
    EXPECT_EQ(nonmast, p_oDisp->GetMastEvent(2));
    EXPECT_EQ(mast, p_oDisp->GetMastEvent(3));

    //Check the counts
    EXPECT_LT(fabs(iNumSp1 - 4277.778)/iNumSp1, 0.25);
    EXPECT_LT(fabs(iNumSp2 - 875.0)/iNumSp2, 0.26);
    EXPECT_LT(fabs(iNumSp4 - 12600.0)/iNumSp4, 0.25);
    delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

/////////////////////////////////////////////////////////////////////////////
// NormalProcessingRun4()
// Tests fourth normal processing run. WriteMastingSpatialDisperseXMLFile4() does setup. This tests
// STR draws per species vs. draws per tree. Four trees are used, 2 of each
// of 2 species. Species 1 is a draw per species, Species 2 is draw per tree.
// The two trees of species 1 should produce the same number of seedlings,
// and the two trees of species 2 should produce different seedlings.
/////////////////////////////////////////////////////////////////////////////
TEST(MastingSpatialDisperse, NormalProcessingRun4) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    //Feed our file to the sim manager
    p_oSimManager->ReadFile(WriteMastingSpatialDisperseXMLFile4());

    clTreePopulation *p_oPop = (clTreePopulation *) p_oSimManager->GetPopulationObject("treepopulation");
    clTreeSearch *p_oAllTrees;
    clTree *p_oTree;
    float fX;
    int iNumSp1Tree1, iNumSp1Tree2, iNumSp2Tree1, iNumSp2Tree2;

    //Create the trees
    p_oPop->CreateTree(50, 50, 0, clTreePopulation::adult, 20.0);
    p_oPop->CreateTree(150, 150, 0, clTreePopulation::adult, 20.0);
    p_oPop->CreateTree(50, 50, 1, clTreePopulation::adult, 20.0);
    p_oPop->CreateTree(150, 150, 1, clTreePopulation::adult, 20.0);

    //Run one timestep
    p_oSimManager->RunSim(1);

    //Count the number of seedlings of each type in each area
    iNumSp1Tree1 = 0;
    iNumSp1Tree2 = 0;
    iNumSp2Tree1 = 0;
    iNumSp2Tree2 = 0;
    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {
      if (p_oTree->GetType() == clTreePopulation::seedling) {
        p_oTree->GetValue(p_oPop->GetXCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fX);
        if (p_oTree->GetSpecies() == 0)
          if (fX < 100) iNumSp1Tree1++;
          else iNumSp1Tree2++;

        else
          if (fX < 100) iNumSp2Tree1++;
          else iNumSp2Tree2++;
      }
      p_oTree = p_oAllTrees->NextTree();
    }

    //The species 1 counts should be equal, the species 2 counts different
    ASSERT_TRUE(iNumSp1Tree1 == iNumSp1Tree2 ||
        iNumSp1Tree1 == iNumSp1Tree2 - 1 ||
        iNumSp1Tree1 == iNumSp1Tree2 + 1);
    EXPECT_GT(fabs(iNumSp2Tree1 - iNumSp2Tree2), 1);
    delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

/////////////////////////////////////////////////////////////////////////////
// NormalProcessingRun5()
// Tests fifth normal processing run. WriteMastingSpatialDisperseXMLFile5() does setup. This tests
// normal draws. 100 runs are done, and the mean and std deviation of the
// number of seedlings is calculated to see if it matches the requested.
/////////////////////////////////////////////////////////////////////////////
TEST(MastingSpatialDisperse, NormalProcessingRun5) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  int iNumRuns = 100,
        *p_iCounts = new int[iNumRuns],
        i;
  try {
    clTreePopulation *p_oPop;
    clTreeSearch *p_oAllTrees;
    clTree *p_oTree;
    float fMean, fStdDev;

    //Do 100 runs
    for (i = 0; i < iNumRuns; i++) {
      p_oSimManager->ReadFile(WriteMastingSpatialDisperseXMLFile5(i));
      p_oPop = (clTreePopulation *) p_oSimManager->GetPopulationObject("treepopulation");

      //Create a parent tree
      p_oPop->CreateTree(1, 1, 0, clTreePopulation::adult, 30.0);

      //Run one timestep
      p_oSimManager->RunSim(1);

      //Count the number of seedlings of each type
      p_iCounts[i] = 0;
      p_oAllTrees = p_oPop->Find("all");
      p_oTree = p_oAllTrees->NextTree();
      while (p_oTree) {
        if (p_oTree->GetType() == clTreePopulation::seedling) {
          p_iCounts[i]++;
        }
        p_oTree = p_oAllTrees->NextTree();
      }
    }

    //Calculate the mean
    fMean = 0;
    for (i = 0; i < iNumRuns; i++) {
      fMean += p_iCounts[i];
    }
    fMean /= iNumRuns;

    //Calculate the standard deviation
    fStdDev = 0;
    for (i = 0; i < iNumRuns; i++) {
      fStdDev += pow((float)p_iCounts[i] - fMean, 2);
    }
    fStdDev /= iNumRuns;
    fStdDev = sqrt(fStdDev);

    EXPECT_LT(fabs(200 - fMean)/fMean, 0.1);
    EXPECT_LT(fabs(20 - fStdDev), 5);

    delete[] p_iCounts;
    delete p_oSimManager;
  } catch (modelErr &e) {
    delete[] p_iCounts;
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

/////////////////////////////////////////////////////////////////////////////
// CheckMastingSetup()
// Tests masting CDF setup. This uses WriteMastingSpatialDisperseXMLCheckFile1() and
// WriteMastingSpatialDisperseXMLCheckFile2() for setup. The first gives a CDF where the max time
// until mast is before the end of the run. The second gives a CDF where the
// max time until mast is the length of the run.
/////////////////////////////////////////////////////////////////////////////
TEST(MastingSpatialDisperse, CheckMastingSetup) {
  using namespace std;
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    //Feed our first check file to the sim manager
    p_oSimManager->ReadFile(WriteMastingSpatialDisperseXMLCheckFile1());
    clBehaviorBase *p_oTemp = p_oSimManager->GetBehaviorObject("MastingSpatialDisperse");
    ASSERT_TRUE(NULL != p_oTemp);
    clMastingSpatialDisperse *p_oDisp = dynamic_cast<clMastingSpatialDisperse*>(p_oTemp);

    EXPECT_EQ(13, p_oDisp->GetMaxTimesteps());

    //Check the masting CDF array
    EXPECT_LT(fabs(p_oDisp->GetMastCDF(0, 0) - 0), 0.0001);
    EXPECT_LT(fabs(p_oDisp->GetMastCDF(0, 1) - 0.03030303), 0.0001);
    EXPECT_LT(fabs(p_oDisp->GetMastCDF(0, 2) - 0.5), 0.0001);
    EXPECT_LT(fabs(p_oDisp->GetMastCDF(0, 3) - 0.883636364), 0.0001);
    EXPECT_LT(fabs(p_oDisp->GetMastCDF(0, 4) - 0.96969697), 0.0001);
    EXPECT_LT(fabs(p_oDisp->GetMastCDF(0, 5) - 0.989863795), 0.0001);
    EXPECT_LT(fabs(p_oDisp->GetMastCDF(0, 6) - 0.995901639), 0.0001);
    EXPECT_LT(fabs(p_oDisp->GetMastCDF(0, 7) - 0.99809965), 0.0001);
    EXPECT_LT(fabs(p_oDisp->GetMastCDF(0, 8) - 0.99902439), 0.0001);
    EXPECT_LT(fabs(p_oDisp->GetMastCDF(0, 9) - 0.999458371), 0.0001);
    EXPECT_LT(fabs(p_oDisp->GetMastCDF(0, 10) - 0.999680102), 0.0001);
    EXPECT_LT(fabs(p_oDisp->GetMastCDF(0, 11) - 0.999801345), 0.0001);
    EXPECT_LT(fabs(p_oDisp->GetMastCDF(0, 12) - 1), 0.0001);

    EXPECT_LT(fabs(p_oDisp->GetMastCDF(1, 0) - 0), 0.0001);
    EXPECT_LT(fabs(p_oDisp->GetMastCDF(1, 1) - 0.5), 0.0001);
    EXPECT_LT(fabs(p_oDisp->GetMastCDF(1, 2) - 0.941176471), 0.0001);
    EXPECT_LT(fabs(p_oDisp->GetMastCDF(1, 3) - 0.987804878), 0.0001);
    EXPECT_LT(fabs(p_oDisp->GetMastCDF(1, 4) - 0.996108949), 0.0001);
    EXPECT_LT(fabs(p_oDisp->GetMastCDF(1, 5) - 0.998402556), 0.0001);
    EXPECT_LT(fabs(p_oDisp->GetMastCDF(1, 6) - 0.99922899), 0.0001);
    EXPECT_LT(fabs(p_oDisp->GetMastCDF(1, 7) - 0.99958368), 0.0001);
    EXPECT_LT(fabs(p_oDisp->GetMastCDF(1, 8) - 0.999755919), 0.0001);
    EXPECT_LT(fabs(p_oDisp->GetMastCDF(1, 9) - 0.999847607), 0.0001);
    EXPECT_LT(fabs(p_oDisp->GetMastCDF(1, 10) - 0.99990001), 0.0001);
    EXPECT_LT(fabs(p_oDisp->GetMastCDF(1, 11) - 0.999931703), 0.0001);
    EXPECT_LT(fabs(p_oDisp->GetMastCDF(1, 12) - 1), 0.0001);

    EXPECT_LT(fabs(p_oDisp->GetMastCDF(2, 0) - 0), 0.0001);
    EXPECT_LT(fabs(p_oDisp->GetMastCDF(2, 1) - 0.080706179), 0.0001);
    EXPECT_LT(fabs(p_oDisp->GetMastCDF(2, 2) - 0.848911917), 0.0001);
    EXPECT_LT(fabs(p_oDisp->GetMastCDF(2, 3) - 0.984615385), 0.0001);
    EXPECT_LT(fabs(p_oDisp->GetMastCDF(2, 4) - 0.997226798), 0.0001);
    EXPECT_LT(fabs(p_oDisp->GetMastCDF(2, 5) - 0.999271531), 0.0001);
    EXPECT_LT(fabs(p_oDisp->GetMastCDF(2, 6) - 0.999755919), 0.0001);
    EXPECT_LT(fabs(p_oDisp->GetMastCDF(2, 7) - 0.999903191), 0.0001);
    EXPECT_LT(fabs(p_oDisp->GetMastCDF(2, 8) - 0.99995655), 0.0001);
    EXPECT_LT(fabs(p_oDisp->GetMastCDF(2, 9) - 0.999978567), 0.0001);
    EXPECT_LT(fabs(p_oDisp->GetMastCDF(2, 10) - 0.99998861), 0.0001);
    EXPECT_LT(fabs(p_oDisp->GetMastCDF(2, 11) - 0.99999357), 0.0001);
    EXPECT_LT(fabs(p_oDisp->GetMastCDF(2, 12) - 1), 0.0001);

    //Feed our second check file to the sim manager
    p_oSimManager->ReadFile(WriteMastingSpatialDisperseXMLCheckFile2());
    p_oTemp = p_oSimManager->GetBehaviorObject("MastingSpatialDisperse");
    p_oDisp = dynamic_cast<clMastingSpatialDisperse*>(p_oTemp);

    EXPECT_EQ(5, p_oDisp->GetMaxTimesteps());

    //Check the masting CDF array
    EXPECT_LT(fabs(p_oDisp->GetMastCDF(0, 0) - 0), 0.0001);
    EXPECT_LT(fabs(p_oDisp->GetMastCDF(0, 1) - 0.116363636), 0.0001);
    EXPECT_LT(fabs(p_oDisp->GetMastCDF(0, 2) - 0.808208366), 0.0001);
    EXPECT_LT(fabs(p_oDisp->GetMastCDF(0, 3) - 0.96969697), 0.0001);
    EXPECT_LT(fabs(p_oDisp->GetMastCDF(0, 4) - 1), 0.0001);

    EXPECT_LT(fabs(p_oDisp->GetMastCDF(1, 0) - 0), 0.0001);
    EXPECT_LT(fabs(p_oDisp->GetMastCDF(1, 1) - 0.03030303), 0.0001);
    EXPECT_LT(fabs(p_oDisp->GetMastCDF(1, 2) - 0.5), 0.0001);
    EXPECT_LT(fabs(p_oDisp->GetMastCDF(1, 3) - 0.883636364), 0.0001);
    EXPECT_LT(fabs(p_oDisp->GetMastCDF(1, 4) - 1), 0.0001);

    EXPECT_LT(fabs(p_oDisp->GetMastCDF(2, 0) - 0), 0.0001);
    EXPECT_LT(fabs(p_oDisp->GetMastCDF(2, 1) - 0.010136205), 0.0001);
    EXPECT_LT(fabs(p_oDisp->GetMastCDF(2, 2) - 0.246806459), 0.0001);
    EXPECT_LT(fabs(p_oDisp->GetMastCDF(2, 3) - 0.713329052), 0.0001);
    EXPECT_LT(fabs(p_oDisp->GetMastCDF(2, 4) - 1), 0.0001);
    delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

////////////////////////////////////////////////////////////////////////////
// TestErrorProcessing()
////////////////////////////////////////////////////////////////////////////
TEST(MastingSpatialDisperse, TestErrorProcessing) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try
  {
    p_oSimManager->ReadFile(WriteMastingSpatialDisperseXMLErrorFile1());
    FAIL() << "TestMastingSpatialDisperse error processing didn't catch error for WriteMastingSpatialDisperseXMLErrorFile1.";
  }
  catch (modelErr& err)
  {
    if (err.sFunction.compare("clMastingSpatialDisperse::CalcMastCDF") != 0)
    {
      FAIL() << "TestMastingSpatialDisperse error processing caught wrong error for WriteMastingSpatialDisperseXMLErrorFile1.";
    }
    ;
  }

  try
  {
    p_oSimManager->ReadFile(WriteMastingSpatialDisperseXMLErrorFile2());
    FAIL() << "TestMastingSpatialDisperse error processing didn't catch error for WriteMastingSpatialDisperseXMLErrorFile2.";
  }
  catch (modelErr& err)
  {
    if (err.sFunction.compare("clMastingSpatialDisperse::GetParameterFileData") != 0)
    {
      FAIL() << "TestMastingSpatialDisperse error processing caught wrong error for WriteMastingSpatialDisperseXMLErrorFile2.";
    }
    ;
  }

  try
  {
    p_oSimManager->ReadFile(WriteMastingSpatialDisperseXMLErrorFile3());
    FAIL() << "TestMastingSpatialDisperse error processing didn't catch error for WriteMastingSpatialDisperseXMLErrorFile3.";
  }
  catch (modelErr& err)
  {
    if (err.sFunction.compare("clMastingSpatialDisperse::GetParameterFileData") != 0)
    {
      FAIL() << "TestMastingSpatialDisperse error processing caught wrong error for WriteMastingSpatialDisperseXMLErrorFile3.";
    }
    ;
  }

  try
  {
    p_oSimManager->ReadFile(WriteMastingSpatialDisperseXMLErrorFile4());
    FAIL() << "TestMastingSpatialDisperse error processing didn't catch error for WriteMastingSpatialDisperseXMLErrorFile4.";
  }
  catch (modelErr& err)
  {
    if (err.sFunction.compare("clMastingSpatialDisperse::GetParameterFileData") != 0)
    {
      FAIL() << "TestMastingSpatialDisperse error processing caught wrong error for WriteMastingSpatialDisperseXMLErrorFile4.";
    }
    ;
  }

  try
  {
    p_oSimManager->ReadFile(WriteMastingSpatialDisperseXMLErrorFile5());
    FAIL() << "TestMastingSpatialDisperse error processing didn't catch error for WriteMastingSpatialDisperseXMLErrorFile5.";
  }
  catch (modelErr& err)
  {
    if (err.sFunction.compare("clMastingSpatialDisperse::GetParameterFileData") != 0)
    {
      FAIL() << "TestMastingSpatialDisperse error processing caught wrong error for WriteMastingSpatialDisperseXMLErrorFile5.";
    }
    ;
  }

  try
  {
    p_oSimManager->ReadFile(WriteMastingSpatialDisperseXMLErrorFile6());
    FAIL() << "TestMastingSpatialDisperse error processing didn't catch error for WriteMastingSpatialDisperseXMLErrorFile6.";
  }
  catch (modelErr& err)
  {
    if (err.sFunction.compare("clMastingSpatialDisperse::CalcSeedCDF") != 0)
    {
      FAIL() << "TestMastingSpatialDisperse error processing caught wrong error for WriteMastingSpatialDisperseXMLErrorFile6.";
    }
    ;
  }

  try
  {
    p_oSimManager->ReadFile(WriteMastingSpatialDisperseXMLErrorFile7());
    FAIL() << "TestMastingSpatialDisperse error processing didn't catch error for WriteMastingSpatialDisperseXMLErrorFile7.";
  }
  catch (modelErr& err)
  {
    if (err.sFunction.compare("clMastingSpatialDisperse::CalcSeedCDF") != 0)
    {
      FAIL() << "TestMastingSpatialDisperse error processing caught wrong error for WriteMastingSpatialDisperseXMLErrorFile7.";
    }
    ;
  }
  delete p_oSimManager;
}

/////////////////////////////////////////////////////////////////////////////
// WriteMastingSpatialDisperseXMLFile1()
/////////////////////////////////////////////////////////////////////////////
const char* WriteMastingSpatialDisperseXMLFile1()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06070101\">"
       << "<plot>"
       << "<timesteps>100</timesteps>"
       << "<randomSeed>0</randomSeed>"
       << "<yearsPerTimestep>1</yearsPerTimestep>"
       << "<plot_lenX>200.0</plot_lenX>"
       << "<plot_lenY>200.0</plot_lenY>"
       << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
       << "<plot_temp_C>12.88171785</plot_temp_C>"
       << "<plot_latitude>55.37</plot_latitude>"
       << "</plot>";

  WriteMastingSpatialDisperseTrees(oOut);

  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>MastingSpatialDisperse</behaviorName>"
       << "<version>1.0</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_4\" type=\"Adult\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>Establishment</behaviorName>"
       << "<version>1.0</version>"
       << "<listPosition>2</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Seed\"/>"
       << "<applyTo species=\"Species_2\" type=\"Seed\"/>"
       << "<applyTo species=\"Species_4\" type=\"Seed\"/>"
       << "</behavior>"
       << "</behaviorList>";

  WriteMastingSpatialDisperseAllometry(oOut);

  oOut << "<GeneralDisperse>"
       << "<di_seedDistributionMethod>0</di_seedDistributionMethod>"
       << "</GeneralDisperse>"
       << "<MastingSpatialDisperse1>"
       << "<di_minDbhForReproduction>"
       << "<di_mdfrVal species=\"Species_1\">10.0</di_mdfrVal>"
       << "<di_mdfrVal species=\"Species_2\">10.0</di_mdfrVal>"
       << "<di_mdfrVal species=\"Species_3\">10.0</di_mdfrVal>"
       << "<di_mdfrVal species=\"Species_4\">10.0</di_mdfrVal>"
       << "</di_minDbhForReproduction>"
       << "<di_mastCDFA>"
       << "<di_mcdfaVal species=\"Species_1\">0.00001</di_mcdfaVal>"
       << "<di_mcdfaVal species=\"Species_2\">1000</di_mcdfaVal>"
       << "<di_mcdfaVal species=\"Species_4\">1000</di_mcdfaVal>"
       << "</di_mastCDFA>"
       << "<di_mastCDFB>"
       << "<di_mcdfbVal species=\"Species_1\">-5</di_mcdfbVal>"
       << "<di_mcdfbVal species=\"Species_2\">-5</di_mcdfbVal>"
       << "<di_mcdfbVal species=\"Species_4\">-5</di_mcdfbVal>"
       << "</di_mastCDFB>"
       << "<di_mastSTRPDF>"
       << "<di_mstrpdfVal species=\"Species_1\">0</di_mstrpdfVal>"
       << "<di_mstrpdfVal species=\"Species_2\">0</di_mstrpdfVal>"
       << "<di_mstrpdfVal species=\"Species_4\">0</di_mstrpdfVal>"
       << "</di_mastSTRPDF>"
       << "<di_spatialSTR>"
       << "<di_sstrVal species=\"Species_1\">550</di_sstrVal>"
       << "<di_sstrVal species=\"Species_2\">35</di_sstrVal>"
       << "<di_sstrVal species=\"Species_4\">10001</di_sstrVal>"
       << "</di_spatialSTR>"
       << "<di_spatialSTRStdDev>"
       << "<di_sstrsdVal species=\"Species_1\">0</di_sstrsdVal>"
       << "<di_sstrsdVal species=\"Species_2\">0</di_sstrsdVal>"
       << "<di_sstrsdVal species=\"Species_4\">0</di_sstrsdVal>"
       << "</di_spatialSTRStdDev>"
       << "<di_mastingSTR>"
       << "<di_mstrVal species=\"Species_1\">385</di_mstrVal>"
       << "<di_mstrVal species=\"Species_2\">214</di_mstrVal>"
       << "<di_mstrVal species=\"Species_4\">126</di_mstrVal>"
       << "</di_mastingSTR>"
       << "<di_mastingSTRStdDev>"
       << "<di_mstrsdVal species=\"Species_1\">0</di_mstrsdVal>"
       << "<di_mstrsdVal species=\"Species_2\">0</di_mstrsdVal>"
       << "<di_mstrsdVal species=\"Species_4\">0</di_mstrsdVal>"
       << "</di_mastingSTRStdDev>"
       << "<di_spatialBeta>"
       << "<di_sbVal species=\"Species_1\">1</di_sbVal>"
       << "<di_sbVal species=\"Species_2\">3.5</di_sbVal>"
       << "<di_sbVal species=\"Species_4\">2</di_sbVal>"
       << "</di_spatialBeta>"
       << "<di_mastingBeta>"
       << "<di_mbVal species=\"Species_1\">2</di_mbVal>"
       << "<di_mbVal species=\"Species_2\">2.5</di_mbVal>"
       << "<di_mbVal species=\"Species_4\">1</di_mbVal>"
       << "</di_mastingBeta>"
       << "<di_canopyFunction>"
       << "<di_cfVal species=\"Species_1\">0</di_cfVal>"
       << "<di_cfVal species=\"Species_2\">0</di_cfVal>"
       << "<di_cfVal species=\"Species_4\">0</di_cfVal>"
       << "</di_canopyFunction>"
       << "<di_weibullCanopyDispersal>"
       << "<di_wcdVal species=\"Species_1\">1.76E-04</di_wcdVal>"
       << "<di_wcdVal species=\"Species_2\">1.82E-04</di_wcdVal>"
       << "<di_wcdVal species=\"Species_4\">9.61E-05</di_wcdVal>"
       << "</di_weibullCanopyDispersal>"
       << "<di_weibullCanopyTheta>"
       << "<di_wctVal species=\"Species_1\">3</di_wctVal>"
       << "<di_wctVal species=\"Species_2\">3</di_wctVal>"
       << "<di_wctVal species=\"Species_4\">3</di_wctVal>"
       << "</di_weibullCanopyTheta>"
       << "<di_weibullMastingDispersal>"
       << "<di_wmdVal species=\"Species_1\">1.76E-04</di_wmdVal>"
       << "<di_wmdVal species=\"Species_2\">1.82E-04</di_wmdVal>"
       << "<di_wmdVal species=\"Species_4\">9.61E-05</di_wmdVal>"
       << "</di_weibullMastingDispersal>"
       << "<di_weibullMastingTheta>"
       << "<di_wmtVal species=\"Species_1\">3</di_wmtVal>"
       << "<di_wmtVal species=\"Species_2\">3</di_wmtVal>"
       << "<di_wmtVal species=\"Species_4\">3</di_wmtVal>"
       << "</di_weibullMastingTheta>"
       << "<di_mastGroup>"
       << "<di_mgVal species=\"Species_1\">1</di_mgVal>"
       << "<di_mgVal species=\"Species_2\">2</di_mgVal>"
       << "<di_mgVal species=\"Species_4\">1</di_mgVal>"
       << "</di_mastGroup>"
       << "<di_mastDrawPerSpecies>"
       << "<di_mdpsVal species=\"Species_1\">0</di_mdpsVal>"
       << "<di_mdpsVal species=\"Species_2\">0</di_mdpsVal>"
       << "<di_mdpsVal species=\"Species_4\">0</di_mdpsVal>"
       << "</di_mastDrawPerSpecies>"
       << "<di_mastPropParticipating>"
       << "<di_mppVal species=\"Species_1\">1</di_mppVal>"
       << "<di_mppVal species=\"Species_2\">1</di_mppVal>"
       << "<di_mppVal species=\"Species_4\">1</di_mppVal>"
       << "</di_mastPropParticipating>"
       << "<di_spatialPropParticipating>"
       << "<di_sppVal species=\"Species_1\">1</di_sppVal>"
       << "<di_sppVal species=\"Species_2\">1</di_sppVal>"
       << "<di_sppVal species=\"Species_4\">1</di_sppVal>"
       << "</di_spatialPropParticipating>"
       << "</MastingSpatialDisperse1>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteMastingSpatialDisperseXMLFile2()
/////////////////////////////////////////////////////////////////////////////
const char* WriteMastingSpatialDisperseXMLFile2()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06070101\">"
       << "<plot>"
       << "<timesteps>100</timesteps>"
       << "<randomSeed>0</randomSeed>"
       << "<yearsPerTimestep>3</yearsPerTimestep>"
       << "<plot_lenX>200.0</plot_lenX>"
       << "<plot_lenY>200.0</plot_lenY>"
       << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
       << "<plot_temp_C>12.88171785</plot_temp_C>"
       << "<plot_latitude>55.37</plot_latitude>"
       << "</plot>";

  WriteMastingSpatialDisperseTrees(oOut);

  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>MastingSpatialDisperse</behaviorName>"
       << "<version>1.0</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_4\" type=\"Adult\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>Establishment</behaviorName>"
       << "<version>1.0</version>"
       << "<listPosition>2</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Seed\"/>"
       << "<applyTo species=\"Species_2\" type=\"Seed\"/>"
       << "<applyTo species=\"Species_4\" type=\"Seed\"/>"
       << "</behavior>"
       << "</behaviorList>";

  WriteMastingSpatialDisperseAllometry(oOut);

  oOut << "<GeneralDisperse>"
       << "<di_seedDistributionMethod>0</di_seedDistributionMethod>"
       << "</GeneralDisperse>"
       << "<MastingSpatialDisperse1>"
       << "<di_minDbhForReproduction>"
       << "<di_mdfrVal species=\"Species_1\">10.0</di_mdfrVal>"
       << "<di_mdfrVal species=\"Species_2\">10.0</di_mdfrVal>"
       << "<di_mdfrVal species=\"Species_3\">10.0</di_mdfrVal>"
       << "<di_mdfrVal species=\"Species_4\">10.0</di_mdfrVal>"
       << "</di_minDbhForReproduction>"
       << "<di_mastCDFA>"
       << "<di_mcdfaVal species=\"Species_1\">0.00001</di_mcdfaVal>"
       << "<di_mcdfaVal species=\"Species_2\">1000</di_mcdfaVal>"
       << "<di_mcdfaVal species=\"Species_4\">1000</di_mcdfaVal>"
       << "</di_mastCDFA>"
       << "<di_mastCDFB>"
       << "<di_mcdfbVal species=\"Species_1\">-5</di_mcdfbVal>"
       << "<di_mcdfbVal species=\"Species_2\">-5</di_mcdfbVal>"
       << "<di_mcdfbVal species=\"Species_4\">-5</di_mcdfbVal>"
       << "</di_mastCDFB>"
       << "<di_mastSTRPDF>"
       << "<di_mstrpdfVal species=\"Species_1\">0</di_mstrpdfVal>"
       << "<di_mstrpdfVal species=\"Species_2\">0</di_mstrpdfVal>"
       << "<di_mstrpdfVal species=\"Species_4\">0</di_mstrpdfVal>"
       << "</di_mastSTRPDF>"
       << "<di_spatialSTR>"
       << "<di_sstrVal species=\"Species_1\">550</di_sstrVal>"
       << "<di_sstrVal species=\"Species_2\">35</di_sstrVal>"
       << "<di_sstrVal species=\"Species_4\">10001</di_sstrVal>"
       << "</di_spatialSTR>"
       << "<di_spatialSTRStdDev>"
       << "<di_sstrsdVal species=\"Species_1\">0</di_sstrsdVal>"
       << "<di_sstrsdVal species=\"Species_2\">0</di_sstrsdVal>"
       << "<di_sstrsdVal species=\"Species_4\">0</di_sstrsdVal>"
       << "</di_spatialSTRStdDev>"
       << "<di_mastingSTR>"
       << "<di_mstrVal species=\"Species_1\">385</di_mstrVal>"
       << "<di_mstrVal species=\"Species_2\">214</di_mstrVal>"
       << "<di_mstrVal species=\"Species_4\">126</di_mstrVal>"
       << "</di_mastingSTR>"
       << "<di_mastingSTRStdDev>"
       << "<di_mstrsdVal species=\"Species_1\">0</di_mstrsdVal>"
       << "<di_mstrsdVal species=\"Species_2\">0</di_mstrsdVal>"
       << "<di_mstrsdVal species=\"Species_4\">0</di_mstrsdVal>"
       << "</di_mastingSTRStdDev>"
       << "<di_canopyFunction>"
       << "<di_cfVal species=\"Species_1\">0</di_cfVal>"
       << "<di_cfVal species=\"Species_2\">0</di_cfVal>"
       << "<di_cfVal species=\"Species_4\">0</di_cfVal>"
       << "</di_canopyFunction>"
       << "<di_spatialBeta>"
       << "<di_sbVal species=\"Species_1\">1</di_sbVal>"
       << "<di_sbVal species=\"Species_2\">3.5</di_sbVal>"
       << "<di_sbVal species=\"Species_4\">2</di_sbVal>"
       << "</di_spatialBeta>"
       << "<di_mastingBeta>"
       << "<di_mbVal species=\"Species_1\">2</di_mbVal>"
       << "<di_mbVal species=\"Species_2\">2.5</di_mbVal>"
       << "<di_mbVal species=\"Species_4\">1</di_mbVal>"
       << "</di_mastingBeta>"
       << "<di_weibullCanopyDispersal>"
       << "<di_wcdVal species=\"Species_1\">1.76E-04</di_wcdVal>"
       << "<di_wcdVal species=\"Species_2\">1.82E-04</di_wcdVal>"
       << "<di_wcdVal species=\"Species_4\">9.61E-05</di_wcdVal>"
       << "</di_weibullCanopyDispersal>"
       << "<di_weibullCanopyTheta>"
       << "<di_wctVal species=\"Species_1\">3</di_wctVal>"
       << "<di_wctVal species=\"Species_2\">3</di_wctVal>"
       << "<di_wctVal species=\"Species_4\">3</di_wctVal>"
       << "</di_weibullCanopyTheta>"
       << "<di_weibullMastingDispersal>"
       << "<di_wmdVal species=\"Species_1\">1.76E-04</di_wmdVal>"
       << "<di_wmdVal species=\"Species_2\">1.82E-04</di_wmdVal>"
       << "<di_wmdVal species=\"Species_4\">9.61E-05</di_wmdVal>"
       << "</di_weibullMastingDispersal>"
       << "<di_weibullMastingTheta>"
       << "<di_wmtVal species=\"Species_1\">3</di_wmtVal>"
       << "<di_wmtVal species=\"Species_2\">3</di_wmtVal>"
       << "<di_wmtVal species=\"Species_4\">3</di_wmtVal>"
       << "</di_weibullMastingTheta>"
       << "<di_mastGroup>"
       << "<di_mgVal species=\"Species_1\">1</di_mgVal>"
       << "<di_mgVal species=\"Species_2\">2</di_mgVal>"
       << "<di_mgVal species=\"Species_4\">1</di_mgVal>"
       << "</di_mastGroup>"
       << "<di_mastDrawPerSpecies>"
       << "<di_mdpsVal species=\"Species_1\">0</di_mdpsVal>"
       << "<di_mdpsVal species=\"Species_2\">0</di_mdpsVal>"
       << "<di_mdpsVal species=\"Species_4\">0</di_mdpsVal>"
       << "</di_mastDrawPerSpecies>"
       << "<di_mastPropParticipating>"
       << "<di_mppVal species=\"Species_1\">1</di_mppVal>"
       << "<di_mppVal species=\"Species_2\">1</di_mppVal>"
       << "<di_mppVal species=\"Species_4\">1</di_mppVal>"
       << "</di_mastPropParticipating>"
       << "<di_spatialPropParticipating>"
       << "<di_sppVal species=\"Species_1\">1</di_sppVal>"
       << "<di_sppVal species=\"Species_2\">1</di_sppVal>"
       << "<di_sppVal species=\"Species_4\">1</di_sppVal>"
       << "</di_spatialPropParticipating>"
       << "</MastingSpatialDisperse1>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteMastingSpatialDisperseXMLFile3()
/////////////////////////////////////////////////////////////////////////////
const char* WriteMastingSpatialDisperseXMLFile3()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06070101\">"
       << "<plot>"
       << "<timesteps>100</timesteps>"
       << "<randomSeed>1</randomSeed>"
       << "<yearsPerTimestep>1</yearsPerTimestep>"
       << "<plot_lenX>200.0</plot_lenX>"
       << "<plot_lenY>200.0</plot_lenY>"
       << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
       << "<plot_temp_C>12.88171785</plot_temp_C>"
       << "<plot_latitude>55.37</plot_latitude>"
       << "</plot>";

  WriteMastingSpatialDisperseTrees(oOut);

  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>MastingSpatialDisperse</behaviorName>"
       << "<version>1.0</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_4\" type=\"Adult\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>Establishment</behaviorName>"
       << "<version>1.0</version>"
       << "<listPosition>2</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Seed\"/>"
       << "<applyTo species=\"Species_2\" type=\"Seed\"/>"
       << "<applyTo species=\"Species_4\" type=\"Seed\"/>"
       << "</behavior>"
       << "</behaviorList>";

  WriteMastingSpatialDisperseAllometry(oOut);

  oOut << "<GeneralDisperse>"
       << "<di_seedDistributionMethod>0</di_seedDistributionMethod>"
       << "</GeneralDisperse>"
       << "<MastingSpatialDisperse1>"
       << "<di_minDbhForReproduction>"
       << "<di_mdfrVal species=\"Species_1\">10.0</di_mdfrVal>"
       << "<di_mdfrVal species=\"Species_2\">10.0</di_mdfrVal>"
       << "<di_mdfrVal species=\"Species_3\">10.0</di_mdfrVal>"
       << "<di_mdfrVal species=\"Species_4\">10.0</di_mdfrVal>"
       << "</di_minDbhForReproduction>"
       << "<di_mastCDFA>"
       << "<di_mcdfaVal species=\"Species_1\">0.00001</di_mcdfaVal>"
       << "<di_mcdfaVal species=\"Species_2\">1000</di_mcdfaVal>"
       << "<di_mcdfaVal species=\"Species_4\">1000</di_mcdfaVal>"
       << "</di_mastCDFA>"
       << "<di_mastCDFB>"
       << "<di_mcdfbVal species=\"Species_1\">-5</di_mcdfbVal>"
       << "<di_mcdfbVal species=\"Species_2\">-5</di_mcdfbVal>"
       << "<di_mcdfbVal species=\"Species_4\">-5</di_mcdfbVal>"
       << "</di_mastCDFB>"
       << "<di_mastSTRPDF>"
       << "<di_mstrpdfVal species=\"Species_1\">0</di_mstrpdfVal>"
       << "<di_mstrpdfVal species=\"Species_2\">0</di_mstrpdfVal>"
       << "<di_mstrpdfVal species=\"Species_4\">0</di_mstrpdfVal>"
       << "</di_mastSTRPDF>"
       << "<di_canopyFunction>"
       << "<di_cfVal species=\"Species_1\">0</di_cfVal>"
       << "<di_cfVal species=\"Species_2\">0</di_cfVal>"
       << "<di_cfVal species=\"Species_4\">0</di_cfVal>"
       << "</di_canopyFunction>"
       << "<di_spatialSTR>"
       << "<di_sstrVal species=\"Species_1\">550</di_sstrVal>"
       << "<di_sstrVal species=\"Species_2\">35</di_sstrVal>"
       << "<di_sstrVal species=\"Species_4\">10001</di_sstrVal>"
       << "</di_spatialSTR>"
       << "<di_spatialSTRStdDev>"
       << "<di_sstrsdVal species=\"Species_1\">0</di_sstrsdVal>"
       << "<di_sstrsdVal species=\"Species_2\">0</di_sstrsdVal>"
       << "<di_sstrsdVal species=\"Species_4\">0</di_sstrsdVal>"
       << "</di_spatialSTRStdDev>"
       << "<di_mastingSTR>"
       << "<di_mstrVal species=\"Species_1\">385</di_mstrVal>"
       << "<di_mstrVal species=\"Species_2\">214</di_mstrVal>"
       << "<di_mstrVal species=\"Species_4\">126</di_mstrVal>"
       << "</di_mastingSTR>"
       << "<di_mastingSTRStdDev>"
       << "<di_mstrsdVal species=\"Species_1\">0</di_mstrsdVal>"
       << "<di_mstrsdVal species=\"Species_2\">0</di_mstrsdVal>"
       << "<di_mstrsdVal species=\"Species_4\">0</di_mstrsdVal>"
       << "</di_mastingSTRStdDev>"
       << "<di_spatialBeta>"
       << "<di_sbVal species=\"Species_1\">1</di_sbVal>"
       << "<di_sbVal species=\"Species_2\">3.5</di_sbVal>"
       << "<di_sbVal species=\"Species_4\">2</di_sbVal>"
       << "</di_spatialBeta>"
       << "<di_mastingBeta>"
       << "<di_mbVal species=\"Species_1\">2</di_mbVal>"
       << "<di_mbVal species=\"Species_2\">2.5</di_mbVal>"
       << "<di_mbVal species=\"Species_4\">1</di_mbVal>"
       << "</di_mastingBeta>"
       << "<di_weibullCanopyDispersal>"
       << "<di_wcdVal species=\"Species_1\">1.76E-04</di_wcdVal>"
       << "<di_wcdVal species=\"Species_2\">1.82E-04</di_wcdVal>"
       << "<di_wcdVal species=\"Species_4\">9.61E-05</di_wcdVal>"
       << "</di_weibullCanopyDispersal>"
       << "<di_weibullCanopyTheta>"
       << "<di_wctVal species=\"Species_1\">3</di_wctVal>"
       << "<di_wctVal species=\"Species_2\">3</di_wctVal>"
       << "<di_wctVal species=\"Species_4\">3</di_wctVal>"
       << "</di_weibullCanopyTheta>"
       << "<di_weibullMastingDispersal>"
       << "<di_wmdVal species=\"Species_1\">1.76E-04</di_wmdVal>"
       << "<di_wmdVal species=\"Species_2\">1.82E-04</di_wmdVal>"
       << "<di_wmdVal species=\"Species_4\">9.61E-05</di_wmdVal>"
       << "</di_weibullMastingDispersal>"
       << "<di_weibullMastingTheta>"
       << "<di_wmtVal species=\"Species_1\">3</di_wmtVal>"
       << "<di_wmtVal species=\"Species_2\">3</di_wmtVal>"
       << "<di_wmtVal species=\"Species_4\">3</di_wmtVal>"
       << "</di_weibullMastingTheta>"
       << "<di_mastGroup>"
       << "<di_mgVal species=\"Species_1\">1</di_mgVal>"
       << "<di_mgVal species=\"Species_2\">2</di_mgVal>"
       << "<di_mgVal species=\"Species_4\">1</di_mgVal>"
       << "</di_mastGroup>"
       << "<di_mastDrawPerSpecies>"
       << "<di_mdpsVal species=\"Species_1\">0</di_mdpsVal>"
       << "<di_mdpsVal species=\"Species_2\">0</di_mdpsVal>"
       << "<di_mdpsVal species=\"Species_4\">0</di_mdpsVal>"
       << "</di_mastDrawPerSpecies>"
       << "<di_mastPropParticipating>"
       << "<di_mppVal species=\"Species_1\">0.25</di_mppVal>"
       << "<di_mppVal species=\"Species_2\">0.5</di_mppVal>"
       << "<di_mppVal species=\"Species_4\">0.75</di_mppVal>"
       << "</di_mastPropParticipating>"
       << "<di_spatialPropParticipating>"
       << "<di_sppVal species=\"Species_1\">0.33</di_sppVal>"
       << "<di_sppVal species=\"Species_2\">0.25</di_sppVal>"
       << "<di_sppVal species=\"Species_4\">0</di_sppVal>"
       << "</di_spatialPropParticipating>"
       << "</MastingSpatialDisperse1>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteMastingSpatialDisperseXMLFile4()
/////////////////////////////////////////////////////////////////////////////
const char* WriteMastingSpatialDisperseXMLFile4()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06070101\">"
       << "<plot>"
       << "<timesteps>100</timesteps>"
       << "<randomSeed>10</randomSeed>"
       << "<yearsPerTimestep>1</yearsPerTimestep>"
       << "<plot_lenX>200.0</plot_lenX>"
       << "<plot_lenY>200.0</plot_lenY>"
       << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
       << "<plot_temp_C>12.88171785</plot_temp_C>"
       << "<plot_latitude>55.37</plot_latitude>"
       << "</plot>";

  WriteMastingSpatialDisperseTrees(oOut);

  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>MastingSpatialDisperse</behaviorName>"
       << "<version>1.0</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>Establishment</behaviorName>"
       << "<version>1.0</version>"
       << "<listPosition>2</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Seed\"/>"
       << "<applyTo species=\"Species_2\" type=\"Seed\"/>"
       << "</behavior>"
       << "</behaviorList>";

  WriteMastingSpatialDisperseAllometry(oOut);

  oOut << "<GeneralDisperse>"
       << "<di_seedDistributionMethod>0</di_seedDistributionMethod>"
       << "</GeneralDisperse>"
       << "<MastingSpatialDisperse1>"
       << "<di_minDbhForReproduction>"
       << "<di_mdfrVal species=\"Species_1\">10.0</di_mdfrVal>"
       << "<di_mdfrVal species=\"Species_2\">10.0</di_mdfrVal>"
       << "<di_mdfrVal species=\"Species_3\">10.0</di_mdfrVal>"
       << "<di_mdfrVal species=\"Species_4\">10.0</di_mdfrVal>"
       << "</di_minDbhForReproduction>"
       << "<di_mastCDFA>"
       << "<di_mcdfaVal species=\"Species_1\">3</di_mcdfaVal>"
       << "<di_mcdfaVal species=\"Species_2\">3</di_mcdfaVal>"
       << "</di_mastCDFA>"
       << "<di_mastCDFB>"
       << "<di_mcdfbVal species=\"Species_1\">-5</di_mcdfbVal>"
       << "<di_mcdfbVal species=\"Species_2\">-5</di_mcdfbVal>"
       << "</di_mastCDFB>"
       << "<di_mastSTRPDF>"
       << "<di_mstrpdfVal species=\"Species_1\">3</di_mstrpdfVal>"
       << "<di_mstrpdfVal species=\"Species_2\">3</di_mstrpdfVal>"
       << "</di_mastSTRPDF>"
       << "<di_spatialSTR>"
       << "<di_sstrVal species=\"Species_1\">385</di_sstrVal>"
       << "<di_sstrVal species=\"Species_2\">214</di_sstrVal>"
       << "</di_spatialSTR>"
       << "<di_spatialSTRStdDev>"
       << "<di_sstrsdVal species=\"Species_1\">100</di_sstrsdVal>"
       << "<di_sstrsdVal species=\"Species_2\">100</di_sstrsdVal>"
       << "</di_spatialSTRStdDev>"
       << "<di_mastingSTR>"
       << "<di_mstrVal species=\"Species_1\">385</di_mstrVal>"
       << "<di_mstrVal species=\"Species_2\">214</di_mstrVal>"
       << "</di_mastingSTR>"
       << "<di_mastingSTRStdDev>"
       << "<di_mstrsdVal species=\"Species_1\">50</di_mstrsdVal>"
       << "<di_mstrsdVal species=\"Species_2\">50</di_mstrsdVal>"
       << "</di_mastingSTRStdDev>"
       << "<di_canopyFunction>"
       << "<di_cfVal species=\"Species_1\">1</di_cfVal>"
       << "<di_cfVal species=\"Species_2\">1</di_cfVal>"
       << "</di_canopyFunction>"
       << "<di_spatialBeta>"
       << "<di_sbVal species=\"Species_1\">2</di_sbVal>"
       << "<di_sbVal species=\"Species_2\">2.5</di_sbVal>"
       << "</di_spatialBeta>"
       << "<di_mastingBeta>"
       << "<di_mbVal species=\"Species_1\">2</di_mbVal>"
       << "<di_mbVal species=\"Species_2\">2.5</di_mbVal>"
       << "</di_mastingBeta>"
       << "<di_lognormalCanopyX0>"
       << "<di_lcx0Val species=\"Species_1\">10.92</di_lcx0Val>"
       << "<di_lcx0Val species=\"Species_2\">10.92</di_lcx0Val>"
       << "</di_lognormalCanopyX0>"
       << "<di_lognormalCanopyXb>"
       << "<di_lcxbVal species=\"Species_1\">0.181</di_lcxbVal>"
       << "<di_lcxbVal species=\"Species_2\">0.181</di_lcxbVal>"
       << "</di_lognormalCanopyXb>"
       << "<di_lognormalMastingX0>"
       << "<di_lmx0Val species=\"Species_1\">10.92</di_lmx0Val>"
       << "<di_lmx0Val species=\"Species_2\">10.92</di_lmx0Val>"
       << "</di_lognormalMastingX0>"
       << "<di_lognormalMastingXb>"
       << "<di_lmxbVal species=\"Species_1\">0.181</di_lmxbVal>"
       << "<di_lmxbVal species=\"Species_2\">0.181</di_lmxbVal>"
       << "</di_lognormalMastingXb>"
       << "<di_mastGroup>"
       << "<di_mgVal species=\"Species_1\">1</di_mgVal>"
       << "<di_mgVal species=\"Species_2\">2</di_mgVal>"
       << "</di_mastGroup>"
       << "<di_mastDrawPerSpecies>"
       << "<di_mdpsVal species=\"Species_1\">1</di_mdpsVal>"
       << "<di_mdpsVal species=\"Species_2\">0</di_mdpsVal>"
       << "</di_mastDrawPerSpecies>"
       << "<di_mastPropParticipating>"
       << "<di_mppVal species=\"Species_1\">1</di_mppVal>"
       << "<di_mppVal species=\"Species_2\">1</di_mppVal>"
       << "</di_mastPropParticipating>"
       << "<di_spatialPropParticipating>"
       << "<di_sppVal species=\"Species_1\">1</di_sppVal>"
       << "<di_sppVal species=\"Species_2\">1</di_sppVal>"
       << "</di_spatialPropParticipating>"
       << "</MastingSpatialDisperse1>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteMastingSpatialDisperseXMLFile5()
/////////////////////////////////////////////////////////////////////////////
const char* WriteMastingSpatialDisperseXMLFile5(int iRandomSeed)
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06070101\">"
       << "<plot>"
       << "<timesteps>100</timesteps>"
       << "<randomSeed>" << iRandomSeed << "</randomSeed>"
       << "<yearsPerTimestep>2</yearsPerTimestep>"
       << "<plot_lenX>200.0</plot_lenX>"
       << "<plot_lenY>200.0</plot_lenY>"
       << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
       << "<plot_temp_C>12.88171785</plot_temp_C>"
       << "<plot_latitude>55.37</plot_latitude>"
       << "</plot>";

  WriteMastingSpatialDisperseTrees(oOut);

  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>MastingSpatialDisperse</behaviorName>"
       << "<version>1.0</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>Establishment</behaviorName>"
       << "<version>1.0</version>"
       << "<listPosition>2</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Seed\"/>"
       << "</behavior>"
       << "</behaviorList>";

  WriteMastingSpatialDisperseAllometry(oOut);

  oOut << "<GeneralDisperse>"
       << "<di_seedDistributionMethod>0</di_seedDistributionMethod>"
       << "</GeneralDisperse>"
       << "<MastingSpatialDisperse1>"
       << "<di_minDbhForReproduction>"
       << "<di_mdfrVal species=\"Species_1\">10.0</di_mdfrVal>"
       << "<di_mdfrVal species=\"Species_2\">10.0</di_mdfrVal>"
       << "<di_mdfrVal species=\"Species_3\">10.0</di_mdfrVal>"
       << "<di_mdfrVal species=\"Species_4\">10.0</di_mdfrVal>"
       << "</di_minDbhForReproduction>"
       << "<di_mastCDFA>"
       << "<di_mcdfaVal species=\"Species_1\">3</di_mcdfaVal>"
       << "</di_mastCDFA>"
       << "<di_mastCDFB>"
       << "<di_mcdfbVal species=\"Species_1\">-5</di_mcdfbVal>"
       << "</di_mastCDFB>"
       << "<di_mastSTRPDF>"
       << "<di_mstrpdfVal species=\"Species_1\">3</di_mstrpdfVal>"
       << "</di_mastSTRPDF>"
       << "<di_spatialSTR>"
       << "<di_sstrVal species=\"Species_1\">100</di_sstrVal>"
       << "</di_spatialSTR>"
       << "<di_spatialSTRStdDev>"
       << "<di_sstrsdVal species=\"Species_1\">10</di_sstrsdVal>"
       << "</di_spatialSTRStdDev>"
       << "<di_mastingSTR>"
       << "<di_mstrVal species=\"Species_1\">100</di_mstrVal>"
       << "</di_mastingSTR>"
       << "<di_canopyFunction>"
       << "<di_cfVal species=\"Species_1\">0</di_cfVal>"
       << "</di_canopyFunction>"
       << "<di_mastingSTRStdDev>"
       << "<di_mstrsdVal species=\"Species_1\">10</di_mstrsdVal>"
       << "</di_mastingSTRStdDev>"
       << "<di_spatialBeta>"
       << "<di_sbVal species=\"Species_1\">1</di_sbVal>"
       << "</di_spatialBeta>"
       << "<di_mastingBeta>"
       << "<di_mbVal species=\"Species_1\">1</di_mbVal>"
       << "</di_mastingBeta>"
       << "<di_weibullCanopyDispersal>"
       << "<di_wcdVal species=\"Species_1\">1.76E-04</di_wcdVal>"
       << "</di_weibullCanopyDispersal>"
       << "<di_weibullCanopyTheta>"
       << "<di_wctVal species=\"Species_1\">3</di_wctVal>"
       << "</di_weibullCanopyTheta>"
       << "<di_weibullMastingDispersal>"
       << "<di_wmdVal species=\"Species_1\">1.76E-04</di_wmdVal>"
       << "</di_weibullMastingDispersal>"
       << "<di_weibullMastingTheta>"
       << "<di_wmtVal species=\"Species_1\">3</di_wmtVal>"
       << "</di_weibullMastingTheta>"
       << "<di_mastGroup>"
       << "<di_mgVal species=\"Species_1\">1</di_mgVal>"
       << "</di_mastGroup>"
       << "<di_mastDrawPerSpecies>"
       << "<di_mdpsVal species=\"Species_1\">0</di_mdpsVal>"
       << "</di_mastDrawPerSpecies>"
       << "<di_mastPropParticipating>"
       << "<di_mppVal species=\"Species_1\">1</di_mppVal>"
       << "</di_mastPropParticipating>"
       << "<di_spatialPropParticipating>"
       << "<di_sppVal species=\"Species_1\">1</di_sppVal>"
       << "</di_spatialPropParticipating>"
       << "</MastingSpatialDisperse1>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteMastingSpatialDisperseXMLCheckFile1()
/////////////////////////////////////////////////////////////////////////////
const char* WriteMastingSpatialDisperseXMLCheckFile1()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06070101\">"
       << "<plot>"
       << "<timesteps>20</timesteps>"
       << "<randomSeed>0</randomSeed>"
       << "<yearsPerTimestep>1</yearsPerTimestep>"
       << "<plot_lenX>200.0</plot_lenX>"
       << "<plot_lenY>200.0</plot_lenY>"
       << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
       << "<plot_temp_C>12.88171785</plot_temp_C>"
       << "<plot_latitude>55.37</plot_latitude>"
       << "</plot>";

  WriteMastingSpatialDisperseTrees(oOut);

  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>MastingSpatialDisperse</behaviorName>"
       << "<version>1.0</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_4\" type=\"Adult\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>Establishment</behaviorName>"
       << "<version>1.0</version>"
       << "<listPosition>2</listPosition>"
       << "<applyTo species=\"Species_3\" type=\"Seed\"/>"
       << "<applyTo species=\"Species_2\" type=\"Seed\"/>"
       << "<applyTo species=\"Species_4\" type=\"Seed\"/>"
       << "</behavior>"
       << "</behaviorList>";

  WriteMastingSpatialDisperseAllometry(oOut);

  oOut << "<GeneralDisperse>"
       << "<di_seedDistributionMethod>0</di_seedDistributionMethod>"
       << "</GeneralDisperse>"
       << "<MastingSpatialDisperse1>"
       << "<di_minDbhForReproduction>"
       << "<di_mdfrVal species=\"Species_1\">10.0</di_mdfrVal>"
       << "<di_mdfrVal species=\"Species_2\">10.0</di_mdfrVal>"
       << "<di_mdfrVal species=\"Species_3\">10.0</di_mdfrVal>"
       << "<di_mdfrVal species=\"Species_4\">10.0</di_mdfrVal>"
       << "</di_minDbhForReproduction>"
       << "<di_mastCDFA>"
       << "<di_mcdfaVal species=\"Species_3\">1</di_mcdfaVal>"
       << "<di_mcdfaVal species=\"Species_2\">2</di_mcdfaVal>"
       << "<di_mcdfaVal species=\"Species_4\">1.5</di_mcdfaVal>"
       << "</di_mastCDFA>"
       << "<di_mastCDFB>"
       << "<di_mcdfbVal species=\"Species_3\">-4</di_mcdfbVal>"
       << "<di_mcdfbVal species=\"Species_2\">-5</di_mcdfbVal>"
       << "<di_mcdfbVal species=\"Species_4\">-6</di_mcdfbVal>"
       << "</di_mastCDFB>"
       << "<di_mastSTRPDF>"
       << "<di_mstrpdfVal species=\"Species_3\">0</di_mstrpdfVal>"
       << "<di_mstrpdfVal species=\"Species_2\">0</di_mstrpdfVal>"
       << "<di_mstrpdfVal species=\"Species_4\">0</di_mstrpdfVal>"
       << "</di_mastSTRPDF>"
       << "<di_spatialSTR>"
       << "<di_sstrVal species=\"Species_3\">550</di_sstrVal>"
       << "<di_sstrVal species=\"Species_2\">35</di_sstrVal>"
       << "<di_sstrVal species=\"Species_4\">10001</di_sstrVal>"
       << "</di_spatialSTR>"
       << "<di_spatialSTRStdDev>"
       << "<di_sstrsdVal species=\"Species_3\">0</di_sstrsdVal>"
       << "<di_sstrsdVal species=\"Species_2\">0</di_sstrsdVal>"
       << "<di_sstrsdVal species=\"Species_4\">0</di_sstrsdVal>"
       << "</di_spatialSTRStdDev>"
       << "<di_mastingSTR>"
       << "<di_mstrVal species=\"Species_3\">385</di_mstrVal>"
       << "<di_mstrVal species=\"Species_2\">214</di_mstrVal>"
       << "<di_mstrVal species=\"Species_4\">126</di_mstrVal>"
       << "</di_mastingSTR>"
       << "<di_mastingSTRStdDev>"
       << "<di_mstrsdVal species=\"Species_3\">0</di_mstrsdVal>"
       << "<di_mstrsdVal species=\"Species_2\">0</di_mstrsdVal>"
       << "<di_mstrsdVal species=\"Species_4\">0</di_mstrsdVal>"
       << "</di_mastingSTRStdDev>"
       << "<di_canopyFunction>"
       << "<di_cfVal species=\"Species_3\">0</di_cfVal>"
       << "<di_cfVal species=\"Species_2\">0</di_cfVal>"
       << "<di_cfVal species=\"Species_4\">0</di_cfVal>"
       << "</di_canopyFunction>"
       << "<di_spatialBeta>"
       << "<di_sbVal species=\"Species_3\">1</di_sbVal>"
       << "<di_sbVal species=\"Species_2\">3.5</di_sbVal>"
       << "<di_sbVal species=\"Species_4\">2</di_sbVal>"
       << "</di_spatialBeta>"
       << "<di_mastingBeta>"
       << "<di_mbVal species=\"Species_3\">2</di_mbVal>"
       << "<di_mbVal species=\"Species_2\">2.5</di_mbVal>"
       << "<di_mbVal species=\"Species_4\">1</di_mbVal>"
       << "</di_mastingBeta>"
       << "<di_weibullCanopyDispersal>"
       << "<di_wcdVal species=\"Species_3\">1.76E-04</di_wcdVal>"
       << "<di_wcdVal species=\"Species_2\">1.82E-04</di_wcdVal>"
       << "<di_wcdVal species=\"Species_4\">9.61E-05</di_wcdVal>"
       << "</di_weibullCanopyDispersal>"
       << "<di_weibullCanopyTheta>"
       << "<di_wctVal species=\"Species_3\">3</di_wctVal>"
       << "<di_wctVal species=\"Species_2\">3</di_wctVal>"
       << "<di_wctVal species=\"Species_4\">3</di_wctVal>"
       << "</di_weibullCanopyTheta>"
       << "<di_weibullMastingDispersal>"
       << "<di_wmdVal species=\"Species_3\">1.76E-04</di_wmdVal>"
       << "<di_wmdVal species=\"Species_2\">1.82E-04</di_wmdVal>"
       << "<di_wmdVal species=\"Species_4\">9.61E-05</di_wmdVal>"
       << "</di_weibullMastingDispersal>"
       << "<di_weibullMastingTheta>"
       << "<di_wmtVal species=\"Species_3\">3</di_wmtVal>"
       << "<di_wmtVal species=\"Species_2\">3</di_wmtVal>"
       << "<di_wmtVal species=\"Species_4\">3</di_wmtVal>"
       << "</di_weibullMastingTheta>"
       << "<di_mastGroup>"
       << "<di_mgVal species=\"Species_3\">1</di_mgVal>"
       << "<di_mgVal species=\"Species_2\">2</di_mgVal>"
       << "<di_mgVal species=\"Species_4\">1</di_mgVal>"
       << "</di_mastGroup>"
       << "<di_mastDrawPerSpecies>"
       << "<di_mdpsVal species=\"Species_3\">0</di_mdpsVal>"
       << "<di_mdpsVal species=\"Species_2\">0</di_mdpsVal>"
       << "<di_mdpsVal species=\"Species_4\">0</di_mdpsVal>"
       << "</di_mastDrawPerSpecies>"
       << "<di_mastPropParticipating>"
       << "<di_mppVal species=\"Species_3\">1</di_mppVal>"
       << "<di_mppVal species=\"Species_2\">1</di_mppVal>"
       << "<di_mppVal species=\"Species_4\">1</di_mppVal>"
       << "</di_mastPropParticipating>"
       << "<di_spatialPropParticipating>"
       << "<di_sppVal species=\"Species_3\">1</di_sppVal>"
       << "<di_sppVal species=\"Species_2\">1</di_sppVal>"
       << "<di_sppVal species=\"Species_4\">1</di_sppVal>"
       << "</di_spatialPropParticipating>"
       << "</MastingSpatialDisperse1>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteMastingSpatialDisperseXMLCheckFile2()
/////////////////////////////////////////////////////////////////////////////
const char* WriteMastingSpatialDisperseXMLCheckFile2()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06070101\">"
       << "<plot>"
       << "<timesteps>5</timesteps>"
       << "<randomSeed>0</randomSeed>"
       << "<yearsPerTimestep>2</yearsPerTimestep>"
       << "<plot_lenX>200.0</plot_lenX>"
       << "<plot_lenY>200.0</plot_lenY>"
       << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
       << "<plot_temp_C>12.88171785</plot_temp_C>"
       << "<plot_latitude>55.37</plot_latitude>"
       << "</plot>";

  WriteMastingSpatialDisperseTrees(oOut);

  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>MastingSpatialDisperse</behaviorName>"
       << "<version>1.0</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>Establishment</behaviorName>"
       << "<version>1.0</version>"
       << "<listPosition>2</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Seed\"/>"
       << "<applyTo species=\"Species_2\" type=\"Seed\"/>"
       << "<applyTo species=\"Species_3\" type=\"Seed\"/>"
       << "</behavior>"
       << "</behaviorList>";

  WriteMastingSpatialDisperseAllometry(oOut);

  oOut << "<GeneralDisperse>"
       << "<di_seedDistributionMethod>0</di_seedDistributionMethod>"
       << "</GeneralDisperse>"
       << "<MastingSpatialDisperse1>"
       << "<di_minDbhForReproduction>"
       << "<di_mdfrVal species=\"Species_1\">10.0</di_mdfrVal>"
       << "<di_mdfrVal species=\"Species_2\">10.0</di_mdfrVal>"
       << "<di_mdfrVal species=\"Species_3\">10.0</di_mdfrVal>"
       << "<di_mdfrVal species=\"Species_4\">10.0</di_mdfrVal>"
       << "</di_minDbhForReproduction>"
       << "<di_mastCDFA>"
       << "<di_mcdfaVal species=\"Species_1\">3</di_mcdfaVal>"
       << "<di_mcdfaVal species=\"Species_2\">4</di_mcdfaVal>"
       << "<di_mcdfaVal species=\"Species_3\">5</di_mcdfaVal>"
       << "</di_mastCDFA>"
       << "<di_mastCDFB>"
       << "<di_mcdfbVal species=\"Species_1\">-5</di_mcdfbVal>"
       << "<di_mcdfbVal species=\"Species_2\">-5</di_mcdfbVal>"
       << "<di_mcdfbVal species=\"Species_3\">-5</di_mcdfbVal>"
       << "</di_mastCDFB>"
       << "<di_mastSTRPDF>"
       << "<di_mstrpdfVal species=\"Species_1\">0</di_mstrpdfVal>"
       << "<di_mstrpdfVal species=\"Species_2\">0</di_mstrpdfVal>"
       << "<di_mstrpdfVal species=\"Species_3\">0</di_mstrpdfVal>"
       << "</di_mastSTRPDF>"
       << "<di_canopyFunction>"
       << "<di_cfVal species=\"Species_1\">0</di_cfVal>"
       << "<di_cfVal species=\"Species_2\">0</di_cfVal>"
       << "<di_cfVal species=\"Species_3\">0</di_cfVal>"
       << "</di_canopyFunction>"
       << "<di_spatialSTR>"
       << "<di_sstrVal species=\"Species_1\">550</di_sstrVal>"
       << "<di_sstrVal species=\"Species_2\">35</di_sstrVal>"
       << "<di_sstrVal species=\"Species_3\">10001</di_sstrVal>"
       << "</di_spatialSTR>"
       << "<di_spatialSTRStdDev>"
       << "<di_sstrsdVal species=\"Species_1\">0</di_sstrsdVal>"
       << "<di_sstrsdVal species=\"Species_2\">0</di_sstrsdVal>"
       << "<di_sstrsdVal species=\"Species_3\">0</di_sstrsdVal>"
       << "</di_spatialSTRStdDev>"
       << "<di_mastingSTR>"
       << "<di_mstrVal species=\"Species_1\">385</di_mstrVal>"
       << "<di_mstrVal species=\"Species_2\">214</di_mstrVal>"
       << "<di_mstrVal species=\"Species_3\">126</di_mstrVal>"
       << "</di_mastingSTR>"
       << "<di_mastingSTRStdDev>"
       << "<di_mstrsdVal species=\"Species_1\">0</di_mstrsdVal>"
       << "<di_mstrsdVal species=\"Species_2\">0</di_mstrsdVal>"
       << "<di_mstrsdVal species=\"Species_3\">0</di_mstrsdVal>"
       << "</di_mastingSTRStdDev>"
       << "<di_spatialBeta>"
       << "<di_sbVal species=\"Species_1\">1</di_sbVal>"
       << "<di_sbVal species=\"Species_2\">3.5</di_sbVal>"
       << "<di_sbVal species=\"Species_3\">2</di_sbVal>"
       << "</di_spatialBeta>"
       << "<di_mastingBeta>"
       << "<di_mbVal species=\"Species_1\">2</di_mbVal>"
       << "<di_mbVal species=\"Species_2\">2.5</di_mbVal>"
       << "<di_mbVal species=\"Species_3\">1</di_mbVal>"
       << "</di_mastingBeta>"
       << "<di_weibullCanopyDispersal>"
       << "<di_wcdVal species=\"Species_1\">1.76E-04</di_wcdVal>"
       << "<di_wcdVal species=\"Species_2\">1.82E-04</di_wcdVal>"
       << "<di_wcdVal species=\"Species_3\">9.61E-05</di_wcdVal>"
       << "</di_weibullCanopyDispersal>"
       << "<di_weibullCanopyTheta>"
       << "<di_wctVal species=\"Species_1\">3</di_wctVal>"
       << "<di_wctVal species=\"Species_2\">3</di_wctVal>"
       << "<di_wctVal species=\"Species_3\">3</di_wctVal>"
       << "</di_weibullCanopyTheta>"
       << "<di_weibullMastingDispersal>"
       << "<di_wmdVal species=\"Species_1\">1.76E-04</di_wmdVal>"
       << "<di_wmdVal species=\"Species_2\">1.82E-04</di_wmdVal>"
       << "<di_wmdVal species=\"Species_3\">9.61E-05</di_wmdVal>"
       << "</di_weibullMastingDispersal>"
       << "<di_weibullMastingTheta>"
       << "<di_wmtVal species=\"Species_1\">3</di_wmtVal>"
       << "<di_wmtVal species=\"Species_2\">3</di_wmtVal>"
       << "<di_wmtVal species=\"Species_3\">3</di_wmtVal>"
       << "</di_weibullMastingTheta>"
       << "<di_mastGroup>"
       << "<di_mgVal species=\"Species_1\">1</di_mgVal>"
       << "<di_mgVal species=\"Species_2\">2</di_mgVal>"
       << "<di_mgVal species=\"Species_3\">1</di_mgVal>"
       << "</di_mastGroup>"
       << "<di_mastDrawPerSpecies>"
       << "<di_mdpsVal species=\"Species_1\">0</di_mdpsVal>"
       << "<di_mdpsVal species=\"Species_2\">0</di_mdpsVal>"
       << "<di_mdpsVal species=\"Species_3\">0</di_mdpsVal>"
       << "</di_mastDrawPerSpecies>"
       << "<di_mastPropParticipating>"
       << "<di_mppVal species=\"Species_1\">1</di_mppVal>"
       << "<di_mppVal species=\"Species_2\">1</di_mppVal>"
       << "<di_mppVal species=\"Species_3\">1</di_mppVal>"
       << "</di_mastPropParticipating>"
       << "<di_spatialPropParticipating>"
       << "<di_sppVal species=\"Species_1\">1</di_sppVal>"
       << "<di_sppVal species=\"Species_2\">1</di_sppVal>"
       << "<di_sppVal species=\"Species_3\">1</di_sppVal>"
       << "</di_spatialPropParticipating>"
       << "</MastingSpatialDisperse1>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteMastingSpatialDisperseTrees()
/////////////////////////////////////////////////////////////////////////////
void WriteMastingSpatialDisperseTrees(std::fstream &oOut) {

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
       << "</trees>";
}

/////////////////////////////////////////////////////////////////////////////
// WriteMastingSpatialDisperseAllometry()
/////////////////////////////////////////////////////////////////////////////
void WriteMastingSpatialDisperseAllometry(std::fstream &oOut) {

  oOut << "<allometry>"
       << "<tr_whatAdultHeightDiam>"
       << "<tr_wahdVal species=\"Species_1\">0</tr_wahdVal>"
       << "<tr_wahdVal species=\"Species_2\">0</tr_wahdVal>"
       << "<tr_wahdVal species=\"Species_3\">0</tr_wahdVal>"
       << "<tr_wahdVal species=\"Species_4\">0</tr_wahdVal>"
       << "</tr_whatAdultHeightDiam>"
       << "<tr_whatSaplingHeightDiam>"
       << "<tr_wsahdVal species=\"Species_1\">0</tr_wsahdVal>"
       << "<tr_wsahdVal species=\"Species_2\">0</tr_wsahdVal>"
       << "<tr_wsahdVal species=\"Species_3\">0</tr_wsahdVal>"
       << "<tr_wsahdVal species=\"Species_4\">0</tr_wsahdVal>"
       << "</tr_whatSaplingHeightDiam>"
       << "<tr_whatSeedlingHeightDiam>"
       << "<tr_wsehdVal species=\"Species_1\">0</tr_wsehdVal>"
       << "<tr_wsehdVal species=\"Species_2\">0</tr_wsehdVal>"
       << "<tr_wsehdVal species=\"Species_3\">0</tr_wsehdVal>"
       << "<tr_wsehdVal species=\"Species_4\">0</tr_wsehdVal>"
       << "</tr_whatSeedlingHeightDiam>"
       << "<tr_whatAdultCrownRadDiam>"
       << "<tr_wacrdVal species=\"Species_1\">0</tr_wacrdVal>"
       << "<tr_wacrdVal species=\"Species_2\">0</tr_wacrdVal>"
       << "<tr_wacrdVal species=\"Species_3\">0</tr_wacrdVal>"
       << "<tr_wacrdVal species=\"Species_4\">0</tr_wacrdVal>"
       << "</tr_whatAdultCrownRadDiam>"
       << "<tr_whatSaplingCrownRadDiam>"
       << "<tr_wscrdVal species=\"Species_1\">0</tr_wscrdVal>"
       << "<tr_wscrdVal species=\"Species_2\">0</tr_wscrdVal>"
       << "<tr_wscrdVal species=\"Species_3\">0</tr_wscrdVal>"
       << "<tr_wscrdVal species=\"Species_4\">0</tr_wscrdVal>"
       << "</tr_whatSaplingCrownRadDiam>"
       << "<tr_whatAdultCrownHeightHeight>"
       << "<tr_wachhVal species=\"Species_1\">0</tr_wachhVal>"
       << "<tr_wachhVal species=\"Species_2\">0</tr_wachhVal>"
       << "<tr_wachhVal species=\"Species_3\">0</tr_wachhVal>"
       << "<tr_wachhVal species=\"Species_4\">0</tr_wachhVal>"
       << "</tr_whatAdultCrownHeightHeight>"
       << "<tr_whatSaplingCrownHeightHeight>"
       << "<tr_wschhVal species=\"Species_1\">0</tr_wschhVal>"
       << "<tr_wschhVal species=\"Species_2\">0</tr_wschhVal>"
       << "<tr_wschhVal species=\"Species_3\">0</tr_wschhVal>"
       << "<tr_wschhVal species=\"Species_4\">0</tr_wschhVal>"
       << "</tr_whatSaplingCrownHeightHeight>"
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
       << "<tr_sacrVal species=\"Species_4\">0.0251</tr_sacrVal>"
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
       << "<tr_stdAsympCrownHt>"
       << "<tr_sachVal species=\"Species_1\">0.389</tr_sachVal>"
       << "<tr_sachVal species=\"Species_2\">0.368</tr_sachVal>"
       << "<tr_sachVal species=\"Species_3\">0.464</tr_sachVal>"
       << "<tr_sachVal species=\"Species_4\">0.454</tr_sachVal>"
       << "</tr_stdAsympCrownHt>"
       << "<tr_stdCrownHtExp>"
       << "<tr_scheVal species=\"Species_1\">1.0</tr_scheVal>"
       << "<tr_scheVal species=\"Species_2\">1.0</tr_scheVal>"
       << "<tr_scheVal species=\"Species_3\">1.0</tr_scheVal>"
       << "<tr_scheVal species=\"Species_4\">1.0</tr_scheVal>"
       << "</tr_stdCrownHtExp>"
       << "<tr_conversionDiam10ToDBH>"
       << "<tr_cdtdVal species=\"Species_1\">0.8008</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_2\">0.5944</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_3\">0.7059</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_4\">0.7776</tr_cdtdVal>"
       << "</tr_conversionDiam10ToDBH>"
       << "<tr_interceptDiam10ToDBH>"
       << "<tr_idtdVal species=\"Species_1\">0.0</tr_idtdVal>"
       << "<tr_idtdVal species=\"Species_2\">0.0</tr_idtdVal>"
       << "<tr_idtdVal species=\"Species_3\">0.0</tr_idtdVal>"
       << "<tr_idtdVal species=\"Species_4\">0.0</tr_idtdVal>"
       << "</tr_interceptDiam10ToDBH>"
       << "<tr_slopeOfAsymHeight>"
       << "<tr_soahVal species=\"Species_1\">0.0299</tr_soahVal>"
       << "<tr_soahVal species=\"Species_2\">0.0241</tr_soahVal>"
       << "<tr_soahVal species=\"Species_3\">0.0263</tr_soahVal>"
       << "<tr_soahVal species=\"Species_4\">0.0264</tr_soahVal>"
       << "</tr_slopeOfAsymHeight>"
       << "<tr_slopeOfHeight-Diam10>"
       << "<tr_sohdVal species=\"Species_1\">0.03418</tr_sohdVal>"
       << "<tr_sohdVal species=\"Species_2\">0.0269</tr_sohdVal>"
       << "<tr_sohdVal species=\"Species_3\">0.02871</tr_sohdVal>"
       << "<tr_sohdVal species=\"Species_4\">0.02815</tr_sohdVal>"
       << "</tr_slopeOfHeight-Diam10>"
       << "</allometry>";
}

/////////////////////////////////////////////////////////////////////////////
// WriteMastingSpatialDisperseXMLErrorFile1()
/////////////////////////////////////////////////////////////////////////////
const char* WriteMastingSpatialDisperseXMLErrorFile1()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06070101\">"
       << "<plot>"
       << "<timesteps>100</timesteps>"
       << "<randomSeed>0</randomSeed>"
       << "<yearsPerTimestep>1</yearsPerTimestep>"
       << "<plot_lenX>200.0</plot_lenX>"
       << "<plot_lenY>200.0</plot_lenY>"
       << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
       << "<plot_temp_C>12.88171785</plot_temp_C>"
       << "<plot_latitude>55.37</plot_latitude>"
       << "</plot>";

  WriteMastingSpatialDisperseTrees(oOut);

  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>MastingSpatialDisperse</behaviorName>"
       << "<version>1.0</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_4\" type=\"Adult\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>Establishment</behaviorName>"
       << "<version>1.0</version>"
       << "<listPosition>2</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Seed\"/>"
       << "<applyTo species=\"Species_2\" type=\"Seed\"/>"
       << "<applyTo species=\"Species_4\" type=\"Seed\"/>"
       << "</behavior>"
       << "</behaviorList>";

  WriteMastingSpatialDisperseAllometry(oOut);

  oOut << "<GeneralDisperse>"
       << "<di_seedDistributionMethod>0</di_seedDistributionMethod>"
       << "</GeneralDisperse>"
       << "<MastingSpatialDisperse1>"
       << "<di_minDbhForReproduction>"
       << "<di_mdfrVal species=\"Species_1\">10.0</di_mdfrVal>"
       << "<di_mdfrVal species=\"Species_2\">10.0</di_mdfrVal>"
       << "<di_mdfrVal species=\"Species_3\">10.0</di_mdfrVal>"
       << "<di_mdfrVal species=\"Species_4\">10.0</di_mdfrVal>"
       << "</di_minDbhForReproduction>"
       << "<di_mastCDFA>"
       << "<di_mcdfaVal species=\"Species_1\">0.00001</di_mcdfaVal>"
       << "<di_mcdfaVal species=\"Species_2\">0</di_mcdfaVal>"
       << "<di_mcdfaVal species=\"Species_4\">1000</di_mcdfaVal>"
       << "</di_mastCDFA>"
       << "<di_mastCDFB>"
       << "<di_mcdfbVal species=\"Species_1\">-5</di_mcdfbVal>"
       << "<di_mcdfbVal species=\"Species_2\">-5</di_mcdfbVal>"
       << "<di_mcdfbVal species=\"Species_4\">-5</di_mcdfbVal>"
       << "</di_mastCDFB>"
       << "<di_mastSTRPDF>"
       << "<di_mstrpdfVal species=\"Species_1\">0</di_mstrpdfVal>"
       << "<di_mstrpdfVal species=\"Species_2\">0</di_mstrpdfVal>"
       << "<di_mstrpdfVal species=\"Species_4\">0</di_mstrpdfVal>"
       << "</di_mastSTRPDF>"
       << "<di_spatialSTR>"
       << "<di_sstrVal species=\"Species_1\">550</di_sstrVal>"
       << "<di_sstrVal species=\"Species_2\">35</di_sstrVal>"
       << "<di_sstrVal species=\"Species_4\">10001</di_sstrVal>"
       << "</di_spatialSTR>"
       << "<di_spatialSTRStdDev>"
       << "<di_sstrsdVal species=\"Species_1\">0</di_sstrsdVal>"
       << "<di_sstrsdVal species=\"Species_2\">0</di_sstrsdVal>"
       << "<di_sstrsdVal species=\"Species_4\">0</di_sstrsdVal>"
       << "</di_spatialSTRStdDev>"
       << "<di_mastingSTR>"
       << "<di_mstrVal species=\"Species_1\">385</di_mstrVal>"
       << "<di_mstrVal species=\"Species_2\">214</di_mstrVal>"
       << "<di_mstrVal species=\"Species_4\">126</di_mstrVal>"
       << "</di_mastingSTR>"
       << "<di_mastingSTRStdDev>"
       << "<di_mstrsdVal species=\"Species_1\">0</di_mstrsdVal>"
       << "<di_mstrsdVal species=\"Species_2\">0</di_mstrsdVal>"
       << "<di_mstrsdVal species=\"Species_4\">0</di_mstrsdVal>"
       << "</di_mastingSTRStdDev>"
       << "<di_canopyFunction>"
       << "<di_cfVal species=\"Species_1\">0</di_cfVal>"
       << "<di_cfVal species=\"Species_2\">0</di_cfVal>"
       << "<di_cfVal species=\"Species_4\">0</di_cfVal>"
       << "</di_canopyFunction>"
       << "<di_spatialBeta>"
       << "<di_sbVal species=\"Species_1\">1</di_sbVal>"
       << "<di_sbVal species=\"Species_2\">3.5</di_sbVal>"
       << "<di_sbVal species=\"Species_4\">2</di_sbVal>"
       << "</di_spatialBeta>"
       << "<di_mastingBeta>"
       << "<di_mbVal species=\"Species_1\">2</di_mbVal>"
       << "<di_mbVal species=\"Species_2\">2.5</di_mbVal>"
       << "<di_mbVal species=\"Species_4\">1</di_mbVal>"
       << "</di_mastingBeta>"
       << "<di_weibullCanopyDispersal>"
       << "<di_wcdVal species=\"Species_1\">1.76E-04</di_wcdVal>"
       << "<di_wcdVal species=\"Species_2\">1.82E-04</di_wcdVal>"
       << "<di_wcdVal species=\"Species_4\">9.61E-05</di_wcdVal>"
       << "</di_weibullCanopyDispersal>"
       << "<di_weibullCanopyTheta>"
       << "<di_wctVal species=\"Species_1\">3</di_wctVal>"
       << "<di_wctVal species=\"Species_2\">3</di_wctVal>"
       << "<di_wctVal species=\"Species_4\">3</di_wctVal>"
       << "</di_weibullCanopyTheta>"
       << "<di_weibullMastingDispersal>"
       << "<di_wmdVal species=\"Species_1\">1.76E-04</di_wmdVal>"
       << "<di_wmdVal species=\"Species_2\">1.82E-04</di_wmdVal>"
       << "<di_wmdVal species=\"Species_4\">9.61E-05</di_wmdVal>"
       << "</di_weibullMastingDispersal>"
       << "<di_weibullMastingTheta>"
       << "<di_wmtVal species=\"Species_1\">3</di_wmtVal>"
       << "<di_wmtVal species=\"Species_2\">3</di_wmtVal>"
       << "<di_wmtVal species=\"Species_4\">3</di_wmtVal>"
       << "</di_weibullMastingTheta>"
       << "<di_mastGroup>"
       << "<di_mgVal species=\"Species_1\">1</di_mgVal>"
       << "<di_mgVal species=\"Species_2\">2</di_mgVal>"
       << "<di_mgVal species=\"Species_4\">1</di_mgVal>"
       << "</di_mastGroup>"
       << "<di_mastDrawPerSpecies>"
       << "<di_mdpsVal species=\"Species_1\">0</di_mdpsVal>"
       << "<di_mdpsVal species=\"Species_2\">0</di_mdpsVal>"
       << "<di_mdpsVal species=\"Species_4\">0</di_mdpsVal>"
       << "</di_mastDrawPerSpecies>"
       << "<di_mastPropParticipating>"
       << "<di_mppVal species=\"Species_1\">1</di_mppVal>"
       << "<di_mppVal species=\"Species_2\">1</di_mppVal>"
       << "<di_mppVal species=\"Species_4\">1</di_mppVal>"
       << "</di_mastPropParticipating>"
       << "<di_spatialPropParticipating>"
       << "<di_sppVal species=\"Species_1\">1</di_sppVal>"
       << "<di_sppVal species=\"Species_2\">1</di_sppVal>"
       << "<di_sppVal species=\"Species_4\">1</di_sppVal>"
       << "</di_spatialPropParticipating>"
       << "</MastingSpatialDisperse1>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteMastingSpatialDisperseXMLErrorFile2()
/////////////////////////////////////////////////////////////////////////////
const char* WriteMastingSpatialDisperseXMLErrorFile2()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06070101\">"
       << "<plot>"
       << "<timesteps>100</timesteps>"
       << "<randomSeed>0</randomSeed>"
       << "<yearsPerTimestep>1</yearsPerTimestep>"
       << "<plot_lenX>200.0</plot_lenX>"
       << "<plot_lenY>200.0</plot_lenY>"
       << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
       << "<plot_temp_C>12.88171785</plot_temp_C>"
       << "<plot_latitude>55.37</plot_latitude>"
       << "</plot>";

  WriteMastingSpatialDisperseTrees(oOut);

  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>MastingSpatialDisperse</behaviorName>"
       << "<version>1.0</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_4\" type=\"Adult\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>Establishment</behaviorName>"
       << "<version>1.0</version>"
       << "<listPosition>2</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Seed\"/>"
       << "<applyTo species=\"Species_2\" type=\"Seed\"/>"
       << "<applyTo species=\"Species_4\" type=\"Seed\"/>"
       << "</behavior>"
       << "</behaviorList>";

  WriteMastingSpatialDisperseAllometry(oOut);

  oOut << "<GeneralDisperse>"
       << "<di_seedDistributionMethod>0</di_seedDistributionMethod>"
       << "</GeneralDisperse>"
       << "<MastingSpatialDisperse1>"
       << "<di_minDbhForReproduction>"
       << "<di_mdfrVal species=\"Species_1\">10.0</di_mdfrVal>"
       << "<di_mdfrVal species=\"Species_2\">10.0</di_mdfrVal>"
       << "<di_mdfrVal species=\"Species_3\">10.0</di_mdfrVal>"
       << "<di_mdfrVal species=\"Species_4\">10.0</di_mdfrVal>"
       << "</di_minDbhForReproduction>"
       << "<di_mastCDFA>"
       << "<di_mcdfaVal species=\"Species_1\">0.00001</di_mcdfaVal>"
       << "<di_mcdfaVal species=\"Species_2\">1000</di_mcdfaVal>"
       << "<di_mcdfaVal species=\"Species_4\">1000</di_mcdfaVal>"
       << "</di_mastCDFA>"
       << "<di_mastCDFB>"
       << "<di_mcdfbVal species=\"Species_1\">-5</di_mcdfbVal>"
       << "<di_mcdfbVal species=\"Species_2\">-5</di_mcdfbVal>"
       << "<di_mcdfbVal species=\"Species_4\">-5</di_mcdfbVal>"
       << "</di_mastCDFB>"
       << "<di_mastSTRPDF>"
       << "<di_mstrpdfVal species=\"Species_1\">0</di_mstrpdfVal>"
       << "<di_mstrpdfVal species=\"Species_2\">0</di_mstrpdfVal>"
       << "<di_mstrpdfVal species=\"Species_4\">0</di_mstrpdfVal>"
       << "</di_mastSTRPDF>"
       << "<di_canopyFunction>"
       << "<di_cfVal species=\"Species_1\">0</di_cfVal>"
       << "<di_cfVal species=\"Species_2\">0</di_cfVal>"
       << "<di_cfVal species=\"Species_4\">0</di_cfVal>"
       << "</di_canopyFunction>"
       << "<di_spatialSTR>"
       << "<di_sstrVal species=\"Species_1\">550</di_sstrVal>"
       << "<di_sstrVal species=\"Species_2\">35</di_sstrVal>"
       << "<di_sstrVal species=\"Species_4\">10001</di_sstrVal>"
       << "</di_spatialSTR>"
       << "<di_spatialSTRStdDev>"
       << "<di_sstrsdVal species=\"Species_1\">0</di_sstrsdVal>"
       << "<di_sstrsdVal species=\"Species_2\">0</di_sstrsdVal>"
       << "<di_sstrsdVal species=\"Species_4\">0</di_sstrsdVal>"
       << "</di_spatialSTRStdDev>"
       << "<di_mastingSTR>"
       << "<di_mstrVal species=\"Species_1\">385</di_mstrVal>"
       << "<di_mstrVal species=\"Species_2\">214</di_mstrVal>"
       << "<di_mstrVal species=\"Species_4\">126</di_mstrVal>"
       << "</di_mastingSTR>"
       << "<di_mastingSTRStdDev>"
       << "<di_mstrsdVal species=\"Species_1\">0</di_mstrsdVal>"
       << "<di_mstrsdVal species=\"Species_2\">0</di_mstrsdVal>"
       << "<di_mstrsdVal species=\"Species_4\">0</di_mstrsdVal>"
       << "</di_mastingSTRStdDev>"
       << "<di_spatialBeta>"
       << "<di_sbVal species=\"Species_1\">1</di_sbVal>"
       << "<di_sbVal species=\"Species_2\">3.5</di_sbVal>"
       << "<di_sbVal species=\"Species_4\">2</di_sbVal>"
       << "</di_spatialBeta>"
       << "<di_mastingBeta>"
       << "<di_mbVal species=\"Species_1\">2</di_mbVal>"
       << "<di_mbVal species=\"Species_2\">2.5</di_mbVal>"
       << "<di_mbVal species=\"Species_4\">1</di_mbVal>"
       << "</di_mastingBeta>"
       << "<di_weibullCanopyDispersal>"
       << "<di_wcdVal species=\"Species_1\">1.76E-04</di_wcdVal>"
       << "<di_wcdVal species=\"Species_2\">1.82E-04</di_wcdVal>"
       << "<di_wcdVal species=\"Species_4\">9.61E-05</di_wcdVal>"
       << "</di_weibullCanopyDispersal>"
       << "<di_weibullCanopyTheta>"
       << "<di_wctVal species=\"Species_1\">3</di_wctVal>"
       << "<di_wctVal species=\"Species_2\">3</di_wctVal>"
       << "<di_wctVal species=\"Species_4\">3</di_wctVal>"
       << "</di_weibullCanopyTheta>"
       << "<di_weibullMastingDispersal>"
       << "<di_wmdVal species=\"Species_1\">1.76E-04</di_wmdVal>"
       << "<di_wmdVal species=\"Species_2\">1.82E-04</di_wmdVal>"
       << "<di_wmdVal species=\"Species_4\">9.61E-05</di_wmdVal>"
       << "</di_weibullMastingDispersal>"
       << "<di_weibullMastingTheta>"
       << "<di_wmtVal species=\"Species_1\">3</di_wmtVal>"
       << "<di_wmtVal species=\"Species_2\">3</di_wmtVal>"
       << "<di_wmtVal species=\"Species_4\">3</di_wmtVal>"
       << "</di_weibullMastingTheta>"
       << "<di_mastGroup>"
       << "<di_mgVal species=\"Species_1\">1</di_mgVal>"
       << "<di_mgVal species=\"Species_2\">2</di_mgVal>"
       << "<di_mgVal species=\"Species_4\">1</di_mgVal>"
       << "</di_mastGroup>"
       << "<di_mastDrawPerSpecies>"
       << "<di_mdpsVal species=\"Species_1\">0</di_mdpsVal>"
       << "<di_mdpsVal species=\"Species_2\">0</di_mdpsVal>"
       << "<di_mdpsVal species=\"Species_4\">0</di_mdpsVal>"
       << "</di_mastDrawPerSpecies>"
       << "<di_mastPropParticipating>"
       << "<di_mppVal species=\"Species_1\">1.5</di_mppVal>"
       << "<di_mppVal species=\"Species_2\">1</di_mppVal>"
       << "<di_mppVal species=\"Species_4\">1</di_mppVal>"
       << "</di_mastPropParticipating>"
       << "<di_spatialPropParticipating>"
       << "<di_sppVal species=\"Species_1\">1</di_sppVal>"
       << "<di_sppVal species=\"Species_2\">1</di_sppVal>"
       << "<di_sppVal species=\"Species_4\">1</di_sppVal>"
       << "</di_spatialPropParticipating>"
       << "</MastingSpatialDisperse1>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteMastingSpatialDisperseXMLErrorFile3()
/////////////////////////////////////////////////////////////////////////////
const char* WriteMastingSpatialDisperseXMLErrorFile3()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06070101\">"
       << "<plot>"
       << "<timesteps>100</timesteps>"
       << "<randomSeed>0</randomSeed>"
       << "<yearsPerTimestep>1</yearsPerTimestep>"
       << "<plot_lenX>200.0</plot_lenX>"
       << "<plot_lenY>200.0</plot_lenY>"
       << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
       << "<plot_temp_C>12.88171785</plot_temp_C>"
       << "<plot_latitude>55.37</plot_latitude>"
       << "</plot>";

  WriteMastingSpatialDisperseTrees(oOut);

  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>MastingSpatialDisperse</behaviorName>"
       << "<version>1.0</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_4\" type=\"Adult\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>Establishment</behaviorName>"
       << "<version>1.0</version>"
       << "<listPosition>2</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Seed\"/>"
       << "<applyTo species=\"Species_2\" type=\"Seed\"/>"
       << "<applyTo species=\"Species_4\" type=\"Seed\"/>"
       << "</behavior>"
       << "</behaviorList>";

  WriteMastingSpatialDisperseAllometry(oOut);

  oOut << "<GeneralDisperse>"
       << "<di_seedDistributionMethod>0</di_seedDistributionMethod>"
       << "</GeneralDisperse>"
       << "<MastingSpatialDisperse1>"
       << "<di_minDbhForReproduction>"
       << "<di_mdfrVal species=\"Species_1\">10.0</di_mdfrVal>"
       << "<di_mdfrVal species=\"Species_2\">10.0</di_mdfrVal>"
       << "<di_mdfrVal species=\"Species_3\">10.0</di_mdfrVal>"
       << "<di_mdfrVal species=\"Species_4\">10.0</di_mdfrVal>"
       << "</di_minDbhForReproduction>"
       << "<di_mastCDFA>"
       << "<di_mcdfaVal species=\"Species_1\">0.00001</di_mcdfaVal>"
       << "<di_mcdfaVal species=\"Species_2\">1000</di_mcdfaVal>"
       << "<di_mcdfaVal species=\"Species_4\">1000</di_mcdfaVal>"
       << "</di_mastCDFA>"
       << "<di_mastCDFB>"
       << "<di_mcdfbVal species=\"Species_1\">-5</di_mcdfbVal>"
       << "<di_mcdfbVal species=\"Species_2\">-5</di_mcdfbVal>"
       << "<di_mcdfbVal species=\"Species_4\">-5</di_mcdfbVal>"
       << "</di_mastCDFB>"
       << "<di_mastSTRPDF>"
       << "<di_mstrpdfVal species=\"Species_1\">0</di_mstrpdfVal>"
       << "<di_mstrpdfVal species=\"Species_2\">0</di_mstrpdfVal>"
       << "<di_mstrpdfVal species=\"Species_4\">0</di_mstrpdfVal>"
       << "</di_mastSTRPDF>"
       << "<di_canopyFunction>"
       << "<di_cfVal species=\"Species_1\">0</di_cfVal>"
       << "<di_cfVal species=\"Species_2\">0</di_cfVal>"
       << "<di_cfVal species=\"Species_4\">0</di_cfVal>"
       << "</di_canopyFunction>"
       << "<di_spatialSTR>"
       << "<di_sstrVal species=\"Species_1\">550</di_sstrVal>"
       << "<di_sstrVal species=\"Species_2\">35</di_sstrVal>"
       << "<di_sstrVal species=\"Species_4\">10001</di_sstrVal>"
       << "</di_spatialSTR>"
       << "<di_spatialSTRStdDev>"
       << "<di_sstrsdVal species=\"Species_1\">0</di_sstrsdVal>"
       << "<di_sstrsdVal species=\"Species_2\">0</di_sstrsdVal>"
       << "<di_sstrsdVal species=\"Species_4\">0</di_sstrsdVal>"
       << "</di_spatialSTRStdDev>"
       << "<di_mastingSTR>"
       << "<di_mstrVal species=\"Species_1\">385</di_mstrVal>"
       << "<di_mstrVal species=\"Species_2\">214</di_mstrVal>"
       << "<di_mstrVal species=\"Species_4\">126</di_mstrVal>"
       << "</di_mastingSTR>"
       << "<di_mastingSTRStdDev>"
       << "<di_mstrsdVal species=\"Species_1\">0</di_mstrsdVal>"
       << "<di_mstrsdVal species=\"Species_2\">0</di_mstrsdVal>"
       << "<di_mstrsdVal species=\"Species_4\">0</di_mstrsdVal>"
       << "</di_mastingSTRStdDev>"
       << "<di_spatialBeta>"
       << "<di_sbVal species=\"Species_1\">1</di_sbVal>"
       << "<di_sbVal species=\"Species_2\">3.5</di_sbVal>"
       << "<di_sbVal species=\"Species_4\">2</di_sbVal>"
       << "</di_spatialBeta>"
       << "<di_mastingBeta>"
       << "<di_mbVal species=\"Species_1\">2</di_mbVal>"
       << "<di_mbVal species=\"Species_2\">2.5</di_mbVal>"
       << "<di_mbVal species=\"Species_4\">1</di_mbVal>"
       << "</di_mastingBeta>"
       << "<di_weibullCanopyDispersal>"
       << "<di_wcdVal species=\"Species_1\">1.76E-04</di_wcdVal>"
       << "<di_wcdVal species=\"Species_2\">1.82E-04</di_wcdVal>"
       << "<di_wcdVal species=\"Species_4\">9.61E-05</di_wcdVal>"
       << "</di_weibullCanopyDispersal>"
       << "<di_weibullCanopyTheta>"
       << "<di_wctVal species=\"Species_1\">3</di_wctVal>"
       << "<di_wctVal species=\"Species_2\">3</di_wctVal>"
       << "<di_wctVal species=\"Species_4\">3</di_wctVal>"
       << "</di_weibullCanopyTheta>"
       << "<di_weibullMastingDispersal>"
       << "<di_wmdVal species=\"Species_1\">1.76E-04</di_wmdVal>"
       << "<di_wmdVal species=\"Species_2\">1.82E-04</di_wmdVal>"
       << "<di_wmdVal species=\"Species_4\">9.61E-05</di_wmdVal>"
       << "</di_weibullMastingDispersal>"
       << "<di_weibullMastingTheta>"
       << "<di_wmtVal species=\"Species_1\">3</di_wmtVal>"
       << "<di_wmtVal species=\"Species_2\">3</di_wmtVal>"
       << "<di_wmtVal species=\"Species_4\">3</di_wmtVal>"
       << "</di_weibullMastingTheta>"
       << "<di_mastGroup>"
       << "<di_mgVal species=\"Species_1\">1</di_mgVal>"
       << "<di_mgVal species=\"Species_2\">2</di_mgVal>"
       << "<di_mgVal species=\"Species_4\">1</di_mgVal>"
       << "</di_mastGroup>"
       << "<di_mastDrawPerSpecies>"
       << "<di_mdpsVal species=\"Species_1\">0</di_mdpsVal>"
       << "<di_mdpsVal species=\"Species_2\">0</di_mdpsVal>"
       << "<di_mdpsVal species=\"Species_4\">0</di_mdpsVal>"
       << "</di_mastDrawPerSpecies>"
       << "<di_mastPropParticipating>"
       << "<di_mppVal species=\"Species_1\">1</di_mppVal>"
       << "<di_mppVal species=\"Species_2\">1</di_mppVal>"
       << "<di_mppVal species=\"Species_4\">1</di_mppVal>"
       << "</di_mastPropParticipating>"
       << "<di_spatialPropParticipating>"
       << "<di_sppVal species=\"Species_1\">1</di_sppVal>"
       << "<di_sppVal species=\"Species_2\">-1</di_sppVal>"
       << "<di_sppVal species=\"Species_4\">1</di_sppVal>"
       << "</di_spatialPropParticipating>"
       << "</MastingSpatialDisperse1>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteMastingSpatialDisperseXMLErrorFile4()
/////////////////////////////////////////////////////////////////////////////
const char* WriteMastingSpatialDisperseXMLErrorFile4()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06070101\">"
       << "<plot>"
       << "<timesteps>100</timesteps>"
       << "<randomSeed>0</randomSeed>"
       << "<yearsPerTimestep>1</yearsPerTimestep>"
       << "<plot_lenX>200.0</plot_lenX>"
       << "<plot_lenY>200.0</plot_lenY>"
       << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
       << "<plot_temp_C>12.88171785</plot_temp_C>"
       << "<plot_latitude>55.37</plot_latitude>"
       << "</plot>";

  WriteMastingSpatialDisperseTrees(oOut);

  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>MastingSpatialDisperse</behaviorName>"
       << "<version>1.0</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_4\" type=\"Adult\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>Establishment</behaviorName>"
       << "<version>1.0</version>"
       << "<listPosition>2</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Seed\"/>"
       << "<applyTo species=\"Species_2\" type=\"Seed\"/>"
       << "<applyTo species=\"Species_4\" type=\"Seed\"/>"
       << "</behavior>"
       << "</behaviorList>";

  WriteMastingSpatialDisperseAllometry(oOut);

  oOut << "<GeneralDisperse>"
       << "<di_seedDistributionMethod>0</di_seedDistributionMethod>"
       << "</GeneralDisperse>"
       << "<MastingSpatialDisperse1>"
       << "<di_minDbhForReproduction>"
       << "<di_mdfrVal species=\"Species_1\">10.0</di_mdfrVal>"
       << "<di_mdfrVal species=\"Species_2\">10.0</di_mdfrVal>"
       << "<di_mdfrVal species=\"Species_3\">10.0</di_mdfrVal>"
       << "<di_mdfrVal species=\"Species_4\">10.0</di_mdfrVal>"
       << "</di_minDbhForReproduction>"
       << "<di_mastCDFA>"
       << "<di_mcdfaVal species=\"Species_1\">0.00001</di_mcdfaVal>"
       << "<di_mcdfaVal species=\"Species_2\">1000</di_mcdfaVal>"
       << "<di_mcdfaVal species=\"Species_4\">1000</di_mcdfaVal>"
       << "</di_mastCDFA>"
       << "<di_mastCDFB>"
       << "<di_mcdfbVal species=\"Species_1\">-5</di_mcdfbVal>"
       << "<di_mcdfbVal species=\"Species_2\">-5</di_mcdfbVal>"
       << "<di_mcdfbVal species=\"Species_4\">-5</di_mcdfbVal>"
       << "</di_mastCDFB>"
       << "<di_mastSTRPDF>"
       << "<di_mstrpdfVal species=\"Species_1\">0</di_mstrpdfVal>"
       << "<di_mstrpdfVal species=\"Species_2\">0</di_mstrpdfVal>"
       << "<di_mstrpdfVal species=\"Species_4\">0</di_mstrpdfVal>"
       << "</di_mastSTRPDF>"
       << "<di_spatialSTR>"
       << "<di_sstrVal species=\"Species_1\">550</di_sstrVal>"
       << "<di_sstrVal species=\"Species_2\">35</di_sstrVal>"
       << "<di_sstrVal species=\"Species_4\">10001</di_sstrVal>"
       << "</di_spatialSTR>"
       << "<di_canopyFunction>"
       << "<di_cfVal species=\"Species_1\">0</di_cfVal>"
       << "<di_cfVal species=\"Species_2\">0</di_cfVal>"
       << "<di_cfVal species=\"Species_4\">0</di_cfVal>"
       << "</di_canopyFunction>"
       << "<di_spatialSTRStdDev>"
       << "<di_sstrsdVal species=\"Species_1\">0</di_sstrsdVal>"
       << "<di_sstrsdVal species=\"Species_2\">0</di_sstrsdVal>"
       << "<di_sstrsdVal species=\"Species_4\">0</di_sstrsdVal>"
       << "</di_spatialSTRStdDev>"
       << "<di_mastingSTR>"
       << "<di_mstrVal species=\"Species_1\">385</di_mstrVal>"
       << "<di_mstrVal species=\"Species_2\">214</di_mstrVal>"
       << "<di_mstrVal species=\"Species_4\">126</di_mstrVal>"
       << "</di_mastingSTR>"
       << "<di_mastingSTRStdDev>"
       << "<di_mstrsdVal species=\"Species_1\">0</di_mstrsdVal>"
       << "<di_mstrsdVal species=\"Species_2\">0</di_mstrsdVal>"
       << "<di_mstrsdVal species=\"Species_4\">0</di_mstrsdVal>"
       << "</di_mastingSTRStdDev>"
       << "<di_spatialBeta>"
       << "<di_sbVal species=\"Species_1\">1</di_sbVal>"
       << "<di_sbVal species=\"Species_2\">3.5</di_sbVal>"
       << "<di_sbVal species=\"Species_4\">2</di_sbVal>"
       << "</di_spatialBeta>"
       << "<di_mastingBeta>"
       << "<di_mbVal species=\"Species_1\">200</di_mbVal>"
       << "<di_mbVal species=\"Species_2\">2.5</di_mbVal>"
       << "<di_mbVal species=\"Species_4\">1</di_mbVal>"
       << "</di_mastingBeta>"
       << "<di_weibullCanopyDispersal>"
       << "<di_wcdVal species=\"Species_1\">1.76E-04</di_wcdVal>"
       << "<di_wcdVal species=\"Species_2\">1.82E-04</di_wcdVal>"
       << "<di_wcdVal species=\"Species_4\">9.61E-05</di_wcdVal>"
       << "</di_weibullCanopyDispersal>"
       << "<di_weibullCanopyTheta>"
       << "<di_wctVal species=\"Species_1\">3</di_wctVal>"
       << "<di_wctVal species=\"Species_2\">3</di_wctVal>"
       << "<di_wctVal species=\"Species_4\">3</di_wctVal>"
       << "</di_weibullCanopyTheta>"
       << "<di_weibullMastingDispersal>"
       << "<di_wmdVal species=\"Species_1\">1.76E-04</di_wmdVal>"
       << "<di_wmdVal species=\"Species_2\">1.82E-04</di_wmdVal>"
       << "<di_wmdVal species=\"Species_4\">9.61E-05</di_wmdVal>"
       << "</di_weibullMastingDispersal>"
       << "<di_weibullMastingTheta>"
       << "<di_wmtVal species=\"Species_1\">3</di_wmtVal>"
       << "<di_wmtVal species=\"Species_2\">3</di_wmtVal>"
       << "<di_wmtVal species=\"Species_4\">3</di_wmtVal>"
       << "</di_weibullMastingTheta>"
       << "<di_mastGroup>"
       << "<di_mgVal species=\"Species_1\">1</di_mgVal>"
       << "<di_mgVal species=\"Species_2\">2</di_mgVal>"
       << "<di_mgVal species=\"Species_4\">1</di_mgVal>"
       << "</di_mastGroup>"
       << "<di_mastDrawPerSpecies>"
       << "<di_mdpsVal species=\"Species_1\">0</di_mdpsVal>"
       << "<di_mdpsVal species=\"Species_2\">0</di_mdpsVal>"
       << "<di_mdpsVal species=\"Species_4\">0</di_mdpsVal>"
       << "</di_mastDrawPerSpecies>"
       << "<di_mastPropParticipating>"
       << "<di_mppVal species=\"Species_1\">1</di_mppVal>"
       << "<di_mppVal species=\"Species_2\">1</di_mppVal>"
       << "<di_mppVal species=\"Species_4\">1</di_mppVal>"
       << "</di_mastPropParticipating>"
       << "<di_spatialPropParticipating>"
       << "<di_sppVal species=\"Species_1\">1</di_sppVal>"
       << "<di_sppVal species=\"Species_2\">1</di_sppVal>"
       << "<di_sppVal species=\"Species_4\">1</di_sppVal>"
       << "</di_spatialPropParticipating>"
       << "</MastingSpatialDisperse1>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteMastingSpatialDisperseXMLErrorFile5()
/////////////////////////////////////////////////////////////////////////////
const char* WriteMastingSpatialDisperseXMLErrorFile5()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06070101\">"
       << "<plot>"
       << "<timesteps>100</timesteps>"
       << "<randomSeed>0</randomSeed>"
       << "<yearsPerTimestep>1</yearsPerTimestep>"
       << "<plot_lenX>200.0</plot_lenX>"
       << "<plot_lenY>200.0</plot_lenY>"
       << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
       << "<plot_temp_C>12.88171785</plot_temp_C>"
       << "<plot_latitude>55.37</plot_latitude>"
       << "</plot>";

  WriteMastingSpatialDisperseTrees(oOut);

  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>MastingSpatialDisperse</behaviorName>"
       << "<version>1.0</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_4\" type=\"Adult\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>Establishment</behaviorName>"
       << "<version>1.0</version>"
       << "<listPosition>2</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Seed\"/>"
       << "<applyTo species=\"Species_2\" type=\"Seed\"/>"
       << "<applyTo species=\"Species_4\" type=\"Seed\"/>"
       << "</behavior>"
       << "</behaviorList>";

  WriteMastingSpatialDisperseAllometry(oOut);

  oOut << "<GeneralDisperse>"
       << "<di_seedDistributionMethod>0</di_seedDistributionMethod>"
       << "</GeneralDisperse>"
       << "<MastingSpatialDisperse1>"
       << "<di_minDbhForReproduction>"
       << "<di_mdfrVal species=\"Species_1\">10.0</di_mdfrVal>"
       << "<di_mdfrVal species=\"Species_2\">10.0</di_mdfrVal>"
       << "<di_mdfrVal species=\"Species_3\">10.0</di_mdfrVal>"
       << "<di_mdfrVal species=\"Species_4\">10.0</di_mdfrVal>"
       << "</di_minDbhForReproduction>"
       << "<di_mastCDFA>"
       << "<di_mcdfaVal species=\"Species_1\">0.00001</di_mcdfaVal>"
       << "<di_mcdfaVal species=\"Species_2\">1000</di_mcdfaVal>"
       << "<di_mcdfaVal species=\"Species_4\">1000</di_mcdfaVal>"
       << "</di_mastCDFA>"
       << "<di_mastCDFB>"
       << "<di_mcdfbVal species=\"Species_1\">-5</di_mcdfbVal>"
       << "<di_mcdfbVal species=\"Species_2\">-5</di_mcdfbVal>"
       << "<di_mcdfbVal species=\"Species_4\">-5</di_mcdfbVal>"
       << "</di_mastCDFB>"
       << "<di_mastSTRPDF>"
       << "<di_mstrpdfVal species=\"Species_1\">0</di_mstrpdfVal>"
       << "<di_mstrpdfVal species=\"Species_2\">0</di_mstrpdfVal>"
       << "<di_mstrpdfVal species=\"Species_4\">0</di_mstrpdfVal>"
       << "</di_mastSTRPDF>"
       << "<di_spatialSTR>"
       << "<di_sstrVal species=\"Species_1\">550</di_sstrVal>"
       << "<di_sstrVal species=\"Species_2\">35</di_sstrVal>"
       << "<di_sstrVal species=\"Species_4\">10001</di_sstrVal>"
       << "</di_spatialSTR>"
       << "<di_spatialSTRStdDev>"
       << "<di_sstrsdVal species=\"Species_1\">0</di_sstrsdVal>"
       << "<di_sstrsdVal species=\"Species_2\">0</di_sstrsdVal>"
       << "<di_sstrsdVal species=\"Species_4\">0</di_sstrsdVal>"
       << "</di_spatialSTRStdDev>"
       << "<di_canopyFunction>"
       << "<di_cfVal species=\"Species_1\">0</di_cfVal>"
       << "<di_cfVal species=\"Species_2\">0</di_cfVal>"
       << "<di_cfVal species=\"Species_4\">0</di_cfVal>"
       << "</di_canopyFunction>"
       << "<di_mastingSTR>"
       << "<di_mstrVal species=\"Species_1\">385</di_mstrVal>"
       << "<di_mstrVal species=\"Species_2\">214</di_mstrVal>"
       << "<di_mstrVal species=\"Species_4\">126</di_mstrVal>"
       << "</di_mastingSTR>"
       << "<di_mastingSTRStdDev>"
       << "<di_mstrsdVal species=\"Species_1\">0</di_mstrsdVal>"
       << "<di_mstrsdVal species=\"Species_2\">0</di_mstrsdVal>"
       << "<di_mstrsdVal species=\"Species_4\">0</di_mstrsdVal>"
       << "</di_mastingSTRStdDev>"
       << "<di_spatialBeta>"
       << "<di_sbVal species=\"Species_1\">100</di_sbVal>"
       << "<di_sbVal species=\"Species_2\">3.5</di_sbVal>"
       << "<di_sbVal species=\"Species_4\">2</di_sbVal>"
       << "</di_spatialBeta>"
       << "<di_mastingBeta>"
       << "<di_mbVal species=\"Species_1\">2</di_mbVal>"
       << "<di_mbVal species=\"Species_2\">2.5</di_mbVal>"
       << "<di_mbVal species=\"Species_4\">1</di_mbVal>"
       << "</di_mastingBeta>"
       << "<di_weibullCanopyDispersal>"
       << "<di_wcdVal species=\"Species_1\">1.76E-04</di_wcdVal>"
       << "<di_wcdVal species=\"Species_2\">1.82E-04</di_wcdVal>"
       << "<di_wcdVal species=\"Species_4\">9.61E-05</di_wcdVal>"
       << "</di_weibullCanopyDispersal>"
       << "<di_weibullCanopyTheta>"
       << "<di_wctVal species=\"Species_1\">3</di_wctVal>"
       << "<di_wctVal species=\"Species_2\">3</di_wctVal>"
       << "<di_wctVal species=\"Species_4\">3</di_wctVal>"
       << "</di_weibullCanopyTheta>"
       << "<di_weibullMastingDispersal>"
       << "<di_wmdVal species=\"Species_1\">1.76E-04</di_wmdVal>"
       << "<di_wmdVal species=\"Species_2\">1.82E-04</di_wmdVal>"
       << "<di_wmdVal species=\"Species_4\">9.61E-05</di_wmdVal>"
       << "</di_weibullMastingDispersal>"
       << "<di_weibullMastingTheta>"
       << "<di_wmtVal species=\"Species_1\">3</di_wmtVal>"
       << "<di_wmtVal species=\"Species_2\">3</di_wmtVal>"
       << "<di_wmtVal species=\"Species_4\">3</di_wmtVal>"
       << "</di_weibullMastingTheta>"
       << "<di_mastGroup>"
       << "<di_mgVal species=\"Species_1\">1</di_mgVal>"
       << "<di_mgVal species=\"Species_2\">2</di_mgVal>"
       << "<di_mgVal species=\"Species_4\">1</di_mgVal>"
       << "</di_mastGroup>"
       << "<di_mastDrawPerSpecies>"
       << "<di_mdpsVal species=\"Species_1\">0</di_mdpsVal>"
       << "<di_mdpsVal species=\"Species_2\">0</di_mdpsVal>"
       << "<di_mdpsVal species=\"Species_4\">0</di_mdpsVal>"
       << "</di_mastDrawPerSpecies>"
       << "<di_mastPropParticipating>"
       << "<di_mppVal species=\"Species_1\">1</di_mppVal>"
       << "<di_mppVal species=\"Species_2\">1</di_mppVal>"
       << "<di_mppVal species=\"Species_4\">1</di_mppVal>"
       << "</di_mastPropParticipating>"
       << "<di_spatialPropParticipating>"
       << "<di_sppVal species=\"Species_1\">1</di_sppVal>"
       << "<di_sppVal species=\"Species_2\">1</di_sppVal>"
       << "<di_sppVal species=\"Species_4\">1</di_sppVal>"
       << "</di_spatialPropParticipating>"
       << "</MastingSpatialDisperse1>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
//WriteMastingSpatialDisperseXMLErrorFile6()
/////////////////////////////////////////////////////////////////////////////
const char* WriteMastingSpatialDisperseXMLErrorFile6()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06070101\">"
       << "<plot>"
       << "<timesteps>100</timesteps>"
       << "<randomSeed>0</randomSeed>"
       << "<yearsPerTimestep>1</yearsPerTimestep>"
       << "<plot_lenX>200.0</plot_lenX>"
       << "<plot_lenY>200.0</plot_lenY>"
       << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
       << "<plot_temp_C>12.88171785</plot_temp_C>"
       << "<plot_latitude>55.37</plot_latitude>"
       << "</plot>";

  WriteMastingSpatialDisperseTrees(oOut);

  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>MastingSpatialDisperse</behaviorName>"
       << "<version>1.0</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_4\" type=\"Adult\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>Establishment</behaviorName>"
       << "<version>1.0</version>"
       << "<listPosition>2</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Seed\"/>"
       << "<applyTo species=\"Species_2\" type=\"Seed\"/>"
       << "<applyTo species=\"Species_4\" type=\"Seed\"/>"
       << "</behavior>"
       << "</behaviorList>";

  WriteMastingSpatialDisperseAllometry(oOut);

  oOut << "<GeneralDisperse>"
       << "<di_seedDistributionMethod>0</di_seedDistributionMethod>"
       << "</GeneralDisperse>"
       << "<MastingSpatialDisperse1>"
       << "<di_minDbhForReproduction>"
       << "<di_mdfrVal species=\"Species_1\">10.0</di_mdfrVal>"
       << "<di_mdfrVal species=\"Species_2\">10.0</di_mdfrVal>"
       << "<di_mdfrVal species=\"Species_3\">10.0</di_mdfrVal>"
       << "<di_mdfrVal species=\"Species_4\">10.0</di_mdfrVal>"
       << "</di_minDbhForReproduction>"
       << "<di_canopyFunction>"
       << "<di_cfVal species=\"Species_1\">0</di_cfVal>"
       << "<di_cfVal species=\"Species_2\">0</di_cfVal>"
       << "<di_cfVal species=\"Species_4\">0</di_cfVal>"
       << "</di_canopyFunction>"
       << "<di_mastCDFA>"
       << "<di_mcdfaVal species=\"Species_1\">0.00001</di_mcdfaVal>"
       << "<di_mcdfaVal species=\"Species_2\">1000</di_mcdfaVal>"
       << "<di_mcdfaVal species=\"Species_4\">1000</di_mcdfaVal>"
       << "</di_mastCDFA>"
       << "<di_mastCDFB>"
       << "<di_mcdfbVal species=\"Species_1\">-5</di_mcdfbVal>"
       << "<di_mcdfbVal species=\"Species_2\">-5</di_mcdfbVal>"
       << "<di_mcdfbVal species=\"Species_4\">-5</di_mcdfbVal>"
       << "</di_mastCDFB>"
       << "<di_mastSTRPDF>"
       << "<di_mstrpdfVal species=\"Species_1\">0</di_mstrpdfVal>"
       << "<di_mstrpdfVal species=\"Species_2\">0</di_mstrpdfVal>"
       << "<di_mstrpdfVal species=\"Species_4\">0</di_mstrpdfVal>"
       << "</di_mastSTRPDF>"
       << "<di_spatialSTR>"
       << "<di_sstrVal species=\"Species_1\">550</di_sstrVal>"
       << "<di_sstrVal species=\"Species_2\">35</di_sstrVal>"
       << "<di_sstrVal species=\"Species_4\">10001</di_sstrVal>"
       << "</di_spatialSTR>"
       << "<di_spatialSTRStdDev>"
       << "<di_sstrsdVal species=\"Species_1\">0</di_sstrsdVal>"
       << "<di_sstrsdVal species=\"Species_2\">0</di_sstrsdVal>"
       << "<di_sstrsdVal species=\"Species_4\">0</di_sstrsdVal>"
       << "</di_spatialSTRStdDev>"
       << "<di_mastingSTR>"
       << "<di_mstrVal species=\"Species_1\">385</di_mstrVal>"
       << "<di_mstrVal species=\"Species_2\">214</di_mstrVal>"
       << "<di_mstrVal species=\"Species_4\">126</di_mstrVal>"
       << "</di_mastingSTR>"
       << "<di_mastingSTRStdDev>"
       << "<di_mstrsdVal species=\"Species_1\">0</di_mstrsdVal>"
       << "<di_mstrsdVal species=\"Species_2\">0</di_mstrsdVal>"
       << "<di_mstrsdVal species=\"Species_4\">0</di_mstrsdVal>"
       << "</di_mastingSTRStdDev>"
       << "<di_spatialBeta>"
       << "<di_sbVal species=\"Species_1\">1</di_sbVal>"
       << "<di_sbVal species=\"Species_2\">3.5</di_sbVal>"
       << "<di_sbVal species=\"Species_4\">2</di_sbVal>"
       << "</di_spatialBeta>"
       << "<di_mastingBeta>"
       << "<di_mbVal species=\"Species_1\">2</di_mbVal>"
       << "<di_mbVal species=\"Species_2\">2.5</di_mbVal>"
       << "<di_mbVal species=\"Species_4\">1</di_mbVal>"
       << "</di_mastingBeta>"
       << "<di_weibullCanopyDispersal>"
       << "<di_wcdVal species=\"Species_1\">1.76E-04</di_wcdVal>"
       << "<di_wcdVal species=\"Species_2\">1.82E-04</di_wcdVal>"
       << "<di_wcdVal species=\"Species_4\">9.61E-05</di_wcdVal>"
       << "</di_weibullCanopyDispersal>"
       << "<di_weibullCanopyTheta>"
       << "<di_wctVal species=\"Species_1\">3</di_wctVal>"
       << "<di_wctVal species=\"Species_2\">3</di_wctVal>"
       << "<di_wctVal species=\"Species_4\">3</di_wctVal>"
       << "</di_weibullCanopyTheta>"
       << "<di_weibullMastingDispersal>"
       << "<di_wmdVal species=\"Species_1\">1.76E-04</di_wmdVal>"
       << "<di_wmdVal species=\"Species_2\">1.82E-04</di_wmdVal>"
       << "<di_wmdVal species=\"Species_4\">9.61E-05</di_wmdVal>"
       << "</di_weibullMastingDispersal>"
       << "<di_weibullMastingTheta>"
       << "<di_wmtVal species=\"Species_1\">300</di_wmtVal>"
       << "<di_wmtVal species=\"Species_2\">3</di_wmtVal>"
       << "<di_wmtVal species=\"Species_4\">3</di_wmtVal>"
       << "</di_weibullMastingTheta>"
       << "<di_mastGroup>"
       << "<di_mgVal species=\"Species_1\">1</di_mgVal>"
       << "<di_mgVal species=\"Species_2\">2</di_mgVal>"
       << "<di_mgVal species=\"Species_4\">1</di_mgVal>"
       << "</di_mastGroup>"
       << "<di_mastDrawPerSpecies>"
       << "<di_mdpsVal species=\"Species_1\">0</di_mdpsVal>"
       << "<di_mdpsVal species=\"Species_2\">0</di_mdpsVal>"
       << "<di_mdpsVal species=\"Species_4\">0</di_mdpsVal>"
       << "</di_mastDrawPerSpecies>"
       << "<di_mastPropParticipating>"
       << "<di_mppVal species=\"Species_1\">1</di_mppVal>"
       << "<di_mppVal species=\"Species_2\">1</di_mppVal>"
       << "<di_mppVal species=\"Species_4\">1</di_mppVal>"
       << "</di_mastPropParticipating>"
       << "<di_spatialPropParticipating>"
       << "<di_sppVal species=\"Species_1\">1</di_sppVal>"
       << "<di_sppVal species=\"Species_2\">1</di_sppVal>"
       << "<di_sppVal species=\"Species_4\">1</di_sppVal>"
       << "</di_spatialPropParticipating>"
       << "</MastingSpatialDisperse1>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteMastingSpatialDisperseXMLErrorFile7()
/////////////////////////////////////////////////////////////////////////////
const char* WriteMastingSpatialDisperseXMLErrorFile7()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06070101\">"
       << "<plot>"
       << "<timesteps>100</timesteps>"
       << "<randomSeed>0</randomSeed>"
       << "<yearsPerTimestep>1</yearsPerTimestep>"
       << "<plot_lenX>200.0</plot_lenX>"
       << "<plot_lenY>200.0</plot_lenY>"
       << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
       << "<plot_temp_C>12.88171785</plot_temp_C>"
       << "<plot_latitude>55.37</plot_latitude>"
       << "</plot>";

  WriteMastingSpatialDisperseTrees(oOut);

  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>MastingSpatialDisperse</behaviorName>"
       << "<version>1.0</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_4\" type=\"Adult\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>Establishment</behaviorName>"
       << "<version>1.0</version>"
       << "<listPosition>2</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Seed\"/>"
       << "<applyTo species=\"Species_2\" type=\"Seed\"/>"
       << "<applyTo species=\"Species_4\" type=\"Seed\"/>"
       << "</behavior>"
       << "</behaviorList>";

  WriteMastingSpatialDisperseAllometry(oOut);

  oOut << "<GeneralDisperse>"
       << "<di_seedDistributionMethod>0</di_seedDistributionMethod>"
       << "</GeneralDisperse>"
       << "<MastingSpatialDisperse1>"
       << "<di_minDbhForReproduction>"
       << "<di_mdfrVal species=\"Species_1\">10.0</di_mdfrVal>"
       << "<di_mdfrVal species=\"Species_2\">10.0</di_mdfrVal>"
       << "<di_mdfrVal species=\"Species_3\">10.0</di_mdfrVal>"
       << "<di_mdfrVal species=\"Species_4\">10.0</di_mdfrVal>"
       << "</di_minDbhForReproduction>"
       << "<di_canopyFunction>"
       << "<di_cfVal species=\"Species_1\">0</di_cfVal>"
       << "<di_cfVal species=\"Species_2\">0</di_cfVal>"
       << "<di_cfVal species=\"Species_4\">0</di_cfVal>"
       << "</di_canopyFunction>"
       << "<di_mastCDFA>"
       << "<di_mcdfaVal species=\"Species_1\">0.00001</di_mcdfaVal>"
       << "<di_mcdfaVal species=\"Species_2\">1000</di_mcdfaVal>"
       << "<di_mcdfaVal species=\"Species_4\">1000</di_mcdfaVal>"
       << "</di_mastCDFA>"
       << "<di_mastCDFB>"
       << "<di_mcdfbVal species=\"Species_1\">-5</di_mcdfbVal>"
       << "<di_mcdfbVal species=\"Species_2\">-5</di_mcdfbVal>"
       << "<di_mcdfbVal species=\"Species_4\">-5</di_mcdfbVal>"
       << "</di_mastCDFB>"
       << "<di_mastSTRPDF>"
       << "<di_mstrpdfVal species=\"Species_1\">0</di_mstrpdfVal>"
       << "<di_mstrpdfVal species=\"Species_2\">0</di_mstrpdfVal>"
       << "<di_mstrpdfVal species=\"Species_4\">0</di_mstrpdfVal>"
       << "</di_mastSTRPDF>"
       << "<di_spatialSTR>"
       << "<di_sstrVal species=\"Species_1\">550</di_sstrVal>"
       << "<di_sstrVal species=\"Species_2\">35</di_sstrVal>"
       << "<di_sstrVal species=\"Species_4\">10001</di_sstrVal>"
       << "</di_spatialSTR>"
       << "<di_spatialSTRStdDev>"
       << "<di_sstrsdVal species=\"Species_1\">0</di_sstrsdVal>"
       << "<di_sstrsdVal species=\"Species_2\">0</di_sstrsdVal>"
       << "<di_sstrsdVal species=\"Species_4\">0</di_sstrsdVal>"
       << "</di_spatialSTRStdDev>"
       << "<di_mastingSTR>"
       << "<di_mstrVal species=\"Species_1\">385</di_mstrVal>"
       << "<di_mstrVal species=\"Species_2\">214</di_mstrVal>"
       << "<di_mstrVal species=\"Species_4\">126</di_mstrVal>"
       << "</di_mastingSTR>"
       << "<di_mastingSTRStdDev>"
       << "<di_mstrsdVal species=\"Species_1\">0</di_mstrsdVal>"
       << "<di_mstrsdVal species=\"Species_2\">0</di_mstrsdVal>"
       << "<di_mstrsdVal species=\"Species_4\">0</di_mstrsdVal>"
       << "</di_mastingSTRStdDev>"
       << "<di_spatialBeta>"
       << "<di_sbVal species=\"Species_1\">1</di_sbVal>"
       << "<di_sbVal species=\"Species_2\">3.5</di_sbVal>"
       << "<di_sbVal species=\"Species_4\">2</di_sbVal>"
       << "</di_spatialBeta>"
       << "<di_mastingBeta>"
       << "<di_mbVal species=\"Species_1\">2</di_mbVal>"
       << "<di_mbVal species=\"Species_2\">2.5</di_mbVal>"
       << "<di_mbVal species=\"Species_4\">1</di_mbVal>"
       << "</di_mastingBeta>"
       << "<di_weibullCanopyDispersal>"
       << "<di_wcdVal species=\"Species_1\">1.76E-04</di_wcdVal>"
       << "<di_wcdVal species=\"Species_2\">1.82E-04</di_wcdVal>"
       << "<di_wcdVal species=\"Species_4\">9.61E-05</di_wcdVal>"
       << "</di_weibullCanopyDispersal>"
       << "<di_weibullCanopyTheta>"
       << "<di_wctVal species=\"Species_1\">3</di_wctVal>"
       << "<di_wctVal species=\"Species_2\">3</di_wctVal>"
       << "<di_wctVal species=\"Species_4\">300</di_wctVal>"
       << "</di_weibullCanopyTheta>"
       << "<di_weibullMastingDispersal>"
       << "<di_wmdVal species=\"Species_1\">1.76E-04</di_wmdVal>"
       << "<di_wmdVal species=\"Species_2\">1.82E-04</di_wmdVal>"
       << "<di_wmdVal species=\"Species_4\">9.61E-05</di_wmdVal>"
       << "</di_weibullMastingDispersal>"
       << "<di_weibullMastingTheta>"
       << "<di_wmtVal species=\"Species_1\">3</di_wmtVal>"
       << "<di_wmtVal species=\"Species_2\">3</di_wmtVal>"
       << "<di_wmtVal species=\"Species_4\">3</di_wmtVal>"
       << "</di_weibullMastingTheta>"
       << "<di_mastGroup>"
       << "<di_mgVal species=\"Species_1\">1</di_mgVal>"
       << "<di_mgVal species=\"Species_2\">2</di_mgVal>"
       << "<di_mgVal species=\"Species_4\">1</di_mgVal>"
       << "</di_mastGroup>"
       << "<di_mastDrawPerSpecies>"
       << "<di_mdpsVal species=\"Species_1\">0</di_mdpsVal>"
       << "<di_mdpsVal species=\"Species_2\">0</di_mdpsVal>"
       << "<di_mdpsVal species=\"Species_4\">0</di_mdpsVal>"
       << "</di_mastDrawPerSpecies>"
       << "<di_mastPropParticipating>"
       << "<di_mppVal species=\"Species_1\">1</di_mppVal>"
       << "<di_mppVal species=\"Species_2\">1</di_mppVal>"
       << "<di_mppVal species=\"Species_4\">1</di_mppVal>"
       << "</di_mastPropParticipating>"
       << "<di_spatialPropParticipating>"
       << "<di_sppVal species=\"Species_1\">1</di_sppVal>"
       << "<di_sppVal species=\"Species_2\">1</di_sppVal>"
       << "<di_sppVal species=\"Species_4\">1</di_sppVal>"
       << "</di_spatialPropParticipating>"
       << "</MastingSpatialDisperse1>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}
