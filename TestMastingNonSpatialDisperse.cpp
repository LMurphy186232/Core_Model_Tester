//---------------------------------------------------------------------------
// TestMastingNonSpatialDisperse.cpp
//---------------------------------------------------------------------------
#include "TestMastingNonSpatialDisperse.h"
#include <gtest/gtest.h>
#include "TreePopulation.h"
#include "SimManager.h"
#include "MastingNonSpatialDisperse.h"
#include <math.h>
#include <fstream>
#include <iostream>

/////////////////////////////////////////////////////////////////////////////
// NormalProcessingRun1()
// Tests masting non-spatial dispersal, run 1. It does the following:
// Checks that the correct params are used for mast vs. nonmast; checks that
// grouping happens correctly; checks that when there are no trees, basal
// area is split correctly. WriteNonSpatialDisperseXMLFile1 does setup.
/////////////////////////////////////////////////////////////////////////////
TEST(MastingNonSpatialDisperse, NormalProcessingRun1) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    //Feed our file to the sim manager
    p_oSimManager->ReadFile(WriteNonSpatialDisperseXMLFile1());

    clTreePopulation *p_oPop = (clTreePopulation *) p_oSimManager->GetPopulationObject("treepopulation");
    clTreeSearch *p_oAllTrees;
    clBehaviorBase *p_oTemp = p_oSimManager->GetBehaviorObject("MastingNonSpatialDisperse");
    clMastingNonSpatialDisperse *p_oDisp = dynamic_cast<clMastingNonSpatialDisperse*>(p_oTemp);
    clTree *p_oTree;
    int iNumSp1, iNumSp2, iNumSp4;

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
    EXPECT_EQ(192500, iNumSp1);
    EXPECT_EQ(240000, iNumSp2);
    EXPECT_EQ(192500, iNumSp4);
    delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

/////////////////////////////////////////////////////////////////////////////
// NormalProcessingRun2()
// Tests masting non-spatial dispersal, run 2. It does the following:
// Checks that grouping happens correctly; checks that basal area splits
// happen correctly; and checks multi-year timestep.
// WriteNonSpatialDisperseXMLFile2 does setup.
/////////////////////////////////////////////////////////////////////////////
TEST(MastingNonSpatialDisperse, NormalProcessingRun2) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    //Feed our file to the sim manager
    p_oSimManager->ReadFile(WriteNonSpatialDisperseXMLFile2());

    clTreePopulation *p_oPop = (clTreePopulation *) p_oSimManager->GetPopulationObject("treepopulation");
    clBehaviorBase *p_oTemp = p_oSimManager->GetBehaviorObject("MastingNonSpatialDisperse");
    clMastingNonSpatialDisperse *p_oDisp = dynamic_cast<clMastingNonSpatialDisperse*>(p_oTemp);
    clTreeSearch *p_oAllTrees;
    clTree *p_oTree;
    int iNumSp1, iNumSp2, iNumSp4;

    //Create four trees
    p_oPop->CreateTree(1, 1, 0, clTreePopulation::adult, 20.0);
    p_oPop->CreateTree(1, 1, 1, clTreePopulation::adult, 30.0);
    p_oPop->CreateTree(1, 1, 3, clTreePopulation::adult, 40.0);
    //p_oPop->CreateTree(1, 1, 3, clTreePopulation::adult, 15.0);

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
    //std::cout << "iNumSp1 = " << iNumSp1 << "\n";
    //std::cout << "iNumSp2 = " << iNumSp2 << "\n";
    //std::cout << "iNumSp4 = " << iNumSp4 << "\n";
    EXPECT_EQ(48000, iNumSp1);
    EXPECT_EQ(96000, iNumSp2);
    EXPECT_EQ(192000, iNumSp4);

    //Check that the masting flags were correctly set
    EXPECT_EQ(mast, p_oDisp->GetMastEvent(0));
    EXPECT_EQ(nonmast, p_oDisp->GetMastEvent(1));
    EXPECT_EQ(nonmast, p_oDisp->GetMastEvent(2));
    EXPECT_EQ(mast, p_oDisp->GetMastEvent(3));
    delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

/////////////////////////////////////////////////////////////////////////////
// NormalProcessingRun3()
// Tests masting non-spatial dispersal, run 3. It does the following:
// Checks using different draws appropriately. WriteNonSpatialDisperseXMLFile3 does setup.
/////////////////////////////////////////////////////////////////////////////
TEST(MastingNonSpatialDisperse, NormalProcessingRun3) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    //Feed our file to the sim manager
    p_oSimManager->ReadFile(WriteNonSpatialDisperseXMLFile3());

    clTreePopulation *p_oPop = (clTreePopulation *) p_oSimManager->GetPopulationObject("treepopulation");
    clBehaviorBase *p_oTemp = p_oSimManager->GetBehaviorObject("MastingNonSpatialDisperse");
    clMastingNonSpatialDisperse *p_oDisp = dynamic_cast<clMastingNonSpatialDisperse*>(p_oTemp);
    clTreeSearch *p_oAllTrees;
    clTree *p_oTree;
    int iNumSp1, iNumSp2, iNumSp4;

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
    EXPECT_EQ(iNumSp1, 80000);
    EXPECT_EQ(iNumSp2, 153600);
    EXPECT_GT(fabs(iNumSp4 - 8760000)/iNumSp4, 0.1);

    //Check that the masting flags were correctly set
    EXPECT_EQ(nonmast, p_oDisp->GetMastEvent(0));
    EXPECT_EQ(nonmast, p_oDisp->GetMastEvent(1));
    EXPECT_EQ(nonmast, p_oDisp->GetMastEvent(2));
    EXPECT_EQ(mast, p_oDisp->GetMastEvent(3));
    delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

////////////////////////////////////////////////////////////////////////////
// TestErrorProcessing()
////////////////////////////////////////////////////////////////////////////
TEST(MastingNonSpatialDisperse, TestErrorProcessing) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try
  {
    p_oSimManager->ReadFile(WriteNonSpatialDisperseXMLErrorFile1());
    FAIL() << "TestMastingNonSpatialDisperse error processing didn't catch error for WriteNonSpatialDisperseXMLErrorFile1.";
  }
  catch (modelErr& err)
  {
    if (err.sFunction.compare("clMastingNonSpatialDisperse::DoShellSetup") != 0)
    {
      FAIL() << "TestMastingNonSpatialDisperse error processing caught wrong error for WriteNonSpatialDisperseXMLErrorFile1.";
    }
    ;
  }

  try
  {
    p_oSimManager->ReadFile(WriteNonSpatialDisperseXMLErrorFile2());
    FAIL() << "TestMastingNonSpatialDisperse error processing didn't catch error for WriteNonSpatialDisperseXMLErrorFile2.";
  }
  catch (modelErr& err)
  {
    if (err.sFunction.compare("clMastingNonSpatialDisperse::DoShellSetup") != 0)
    {
      FAIL() << "TestMastingNonSpatialDisperse error processing caught wrong error for WriteNonSpatialDisperseXMLErrorFile2.";
    }
    ;
  }

  try
  {
    p_oSimManager->ReadFile(WriteNonSpatialDisperseXMLErrorFile3());
    FAIL() << "TestMastingNonSpatialDisperse error processing didn't catch error for WriteNonSpatialDisperseXMLErrorFile3.";
  }
  catch (modelErr& err)
  {
    if (err.sFunction.compare("clMastingNonSpatialDisperse::DoShellSetup") != 0)
    {
      FAIL() << "TestMastingNonSpatialDisperse error processing caught wrong error for WriteNonSpatialDisperseXMLErrorFile3.";
    }
    ;
  }

  try
  {
    p_oSimManager->ReadFile(WriteNonSpatialDisperseXMLErrorFile4());
    FAIL() << "TestMastingNonSpatialDisperse error processing didn't catch error for WriteNonSpatialDisperseXMLErrorFile4.";
  }
  catch (modelErr& err)
  {
    if (err.sFunction.compare("clMastingNonSpatialDisperse::DoShellSetup") != 0)
    {
      FAIL() << "TestMastingNonSpatialDisperse error processing caught wrong error for WriteNonSpatialDisperseXMLErrorFile4.";
    }
    ;
  }
  delete p_oSimManager;
}

/////////////////////////////////////////////////////////////////////////////
// WriteNonSpatialDisperseXMLFile1()
/////////////////////////////////////////////////////////////////////////////
const char* WriteNonSpatialDisperseXMLFile1()
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
       << "<plot_lenX>100.0</plot_lenX>"
       << "<plot_lenY>100.0</plot_lenY>"
       << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
       << "<plot_temp_C>12.88171785</plot_temp_C>"
       << "<plot_latitude>55.37</plot_latitude>"
       << "</plot>";

  WriteNonSpatialDisperseTrees(oOut);

  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>MastingNonSpatialDisperse</behaviorName>"
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

  WriteNonSpatialDisperseAllometry(oOut);

  oOut << "<MastingNonSpatialDisperse1>"
       << "<di_nonSpatialMastMastFunction>"
       << "<di_nsmmfVal species=\"Species_1\">3</di_nsmmfVal>"
       << "<di_nsmmfVal species=\"Species_2\">3</di_nsmmfVal>"
       << "<di_nsmmfVal species=\"Species_4\">3</di_nsmmfVal>"
       << "</di_nonSpatialMastMastFunction>"
       << "<di_nonSpatialNonMastFunction>"
       << "<di_nsnmfVal species=\"Species_1\">6</di_nsnmfVal>"
       << "<di_nsnmfVal species=\"Species_2\">3</di_nsnmfVal>"
       << "<di_nsnmfVal species=\"Species_4\">3</di_nsnmfVal>"
       << "</di_nonSpatialNonMastFunction>"
       << "<di_nonSpatialMastBinomialP>"
       << "<di_nsmbpVal species=\"Species_1\">1</di_nsmbpVal>"
       << "<di_nsmbpVal species=\"Species_2\">0</di_nsmbpVal>"
       << "<di_nsmbpVal species=\"Species_4\">0.01</di_nsmbpVal>"
       << "</di_nonSpatialMastBinomialP>"
       << "<di_nonSpatialNonMastInvGaussMu>"
       << "<di_nsnmigmVal species=\"Species_1\">45</di_nsnmigmVal>"
       << "</di_nonSpatialNonMastInvGaussMu>"
       << "<di_nonSpatialNonMastInvGaussLambda>"
       << "<di_nsnmiglVal species=\"Species_1\">0.01</di_nsnmiglVal>"
       << "</di_nonSpatialNonMastInvGaussLambda>"
       << "<di_nonSpatialMastNormalMean>"
       << "<di_nsmnmVal species=\"Species_1\">38.5</di_nsmnmVal>"
       << "<di_nsmnmVal species=\"Species_2\">1</di_nsmnmVal>"
       << "<di_nsmnmVal species=\"Species_4\">45</di_nsmnmVal>"
       << "</di_nonSpatialMastNormalMean>"
       << "<di_nonSpatialMastNormalStdDev>"
       << "<di_nsmnsdVal species=\"Species_1\">0</di_nsmnsdVal>"
       << "<di_nsmnsdVal species=\"Species_2\">6</di_nsmnsdVal>"
       << "<di_nsmnsdVal species=\"Species_4\">0</di_nsmnsdVal>"
       << "</di_nonSpatialMastNormalStdDev>"
       << "<di_nonSpatialNonMastNormalMean>"
       << "<di_nsnmnmVal species=\"Species_2\">24</di_nsnmnmVal>"
       << "<di_nsnmnmVal species=\"Species_4\">10001</di_nsnmnmVal>"
       << "</di_nonSpatialNonMastNormalMean>"
       << "<di_nonSpatialNonMastNormalStdDev>"
       << "<di_nsnmnsdVal species=\"Species_2\">0</di_nsnmnsdVal>"
       << "<di_nsnmnsdVal species=\"Species_4\">5</di_nsnmnsdVal>"
       << "</di_nonSpatialNonMastNormalStdDev>"
       << "<di_nonSpatialMastGroup>"
       << "<di_nsmgVal species=\"Species_1\">5</di_nsmgVal>"
       << "<di_nsmgVal species=\"Species_2\">3</di_nsmgVal>"
       << "<di_nsmgVal species=\"Species_4\">5</di_nsmgVal>"
       << "</di_nonSpatialMastGroup>"
       << "<di_seedDistributionMethod>0</di_seedDistributionMethod>"
       << "</MastingNonSpatialDisperse1>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteNonSpatialDisperseXMLFile2()
/////////////////////////////////////////////////////////////////////////////
const char* WriteNonSpatialDisperseXMLFile2()
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
       << "<plot_lenX>80.0</plot_lenX>"
       << "<plot_lenY>100.0</plot_lenY>"
       << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
       << "<plot_temp_C>12.88171785</plot_temp_C>"
       << "<plot_latitude>55.37</plot_latitude>"
       << "</plot>";

  WriteNonSpatialDisperseTrees(oOut);

  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>MastingNonSpatialDisperse</behaviorName>"
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

  WriteNonSpatialDisperseAllometry(oOut);

  oOut << "<MastingNonSpatialDisperse1>"
       << "<di_nonSpatialMastMastFunction>"
       << "<di_nsmmfVal species=\"Species_1\">3</di_nsmmfVal>"
       << "<di_nsmmfVal species=\"Species_2\">3</di_nsmmfVal>"
       << "<di_nsmmfVal species=\"Species_4\">3</di_nsmmfVal>"
       << "</di_nonSpatialMastMastFunction>"
       << "<di_nonSpatialNonMastFunction>"
       << "<di_nsnmfVal species=\"Species_1\">3</di_nsnmfVal>"
       << "<di_nsnmfVal species=\"Species_2\">3</di_nsnmfVal>"
       << "<di_nsnmfVal species=\"Species_4\">3</di_nsnmfVal>"
       << "</di_nonSpatialNonMastFunction>"
       << "<di_nonSpatialMastBinomialP>"
       << "<di_nsmbpVal species=\"Species_1\">1</di_nsmbpVal>"
       << "<di_nsmbpVal species=\"Species_2\">0</di_nsmbpVal>"
       << "<di_nsmbpVal species=\"Species_4\">0.01</di_nsmbpVal>"
       << "</di_nonSpatialMastBinomialP>"
       << "<di_nonSpatialMastNormalMean>"
       << "<di_nsmnmVal species=\"Species_1\">10</di_nsmnmVal>"
       << "<di_nsmnmVal species=\"Species_2\">1</di_nsmnmVal>"
       << "<di_nsmnmVal species=\"Species_4\">10</di_nsmnmVal>"
       << "</di_nonSpatialMastNormalMean>"
       << "<di_nonSpatialMastNormalStdDev>"
       << "<di_nsmnsdVal species=\"Species_1\">0</di_nsmnsdVal>"
       << "<di_nsmnsdVal species=\"Species_2\">0</di_nsmnsdVal>"
       << "<di_nsmnsdVal species=\"Species_4\">0</di_nsmnsdVal>"
       << "</di_nonSpatialMastNormalStdDev>"
       << "<di_nonSpatialNonMastNormalMean>"
       << "<di_nsnmnmVal species=\"Species_1\">12.5</di_nsnmnmVal>"
       << "<di_nsnmnmVal species=\"Species_2\">4</di_nsnmnmVal>"
       << "<di_nsnmnmVal species=\"Species_4\">10001</di_nsnmnmVal>"
       << "</di_nonSpatialNonMastNormalMean>"
       << "<di_nonSpatialNonMastNormalStdDev>"
       << "<di_nsnmnsdVal species=\"Species_1\">45</di_nsnmnsdVal>"
       << "<di_nsnmnsdVal species=\"Species_2\">0</di_nsnmnsdVal>"
       << "<di_nsnmnsdVal species=\"Species_4\">45</di_nsnmnsdVal>"
       << "</di_nonSpatialNonMastNormalStdDev>"
       << "<di_nonSpatialMastGroup>"
       << "<di_nsmgVal species=\"Species_1\">1</di_nsmgVal>"
       << "<di_nsmgVal species=\"Species_2\">2</di_nsmgVal>"
       << "<di_nsmgVal species=\"Species_4\">1</di_nsmgVal>"
       << "</di_nonSpatialMastGroup>"
       << "<di_seedDistributionMethod>0</di_seedDistributionMethod>"
       << "</MastingNonSpatialDisperse1>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteNonSpatialDisperseXMLFile3()
/////////////////////////////////////////////////////////////////////////////
const char* WriteNonSpatialDisperseXMLFile3()
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
       << "<plot_lenX>80.0</plot_lenX>"
       << "<plot_lenY>80.0</plot_lenY>"
       << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
       << "<plot_temp_C>12.88171785</plot_temp_C>"
       << "<plot_latitude>55.37</plot_latitude>"
       << "</plot>";

  WriteNonSpatialDisperseTrees(oOut);

  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>MastingNonSpatialDisperse</behaviorName>"
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

  WriteNonSpatialDisperseAllometry(oOut);

  oOut << "<MastingNonSpatialDisperse1>"
       << "<di_nonSpatialMastMastFunction>"
       << "<di_nsmmfVal species=\"Species_1\">3</di_nsmmfVal>"
       << "<di_nsmmfVal species=\"Species_2\">3</di_nsmmfVal>"
       << "<di_nsmmfVal species=\"Species_4\">6</di_nsmmfVal>"
       << "</di_nonSpatialMastMastFunction>"
       << "<di_nonSpatialNonMastFunction>"
       << "<di_nsnmfVal species=\"Species_1\">3</di_nsnmfVal>"
       << "<di_nsnmfVal species=\"Species_2\">3</di_nsnmfVal>"
       << "<di_nsnmfVal species=\"Species_4\">3</di_nsnmfVal>"
       << "</di_nonSpatialNonMastFunction>"
       << "<di_nonSpatialMastBinomialP>"
       << "<di_nsmbpVal species=\"Species_1\">0</di_nsmbpVal>"
       << "<di_nsmbpVal species=\"Species_2\">0</di_nsmbpVal>"
       << "<di_nsmbpVal species=\"Species_4\">1</di_nsmbpVal>"
       << "</di_nonSpatialMastBinomialP>"
       << "<di_nonSpatialMastNormalMean>"
       << "<di_nsmnmVal species=\"Species_1\">38.5</di_nsmnmVal>"
       << "<di_nsmnmVal species=\"Species_2\">1</di_nsmnmVal>"
       << "</di_nonSpatialMastNormalMean>"
       << "<di_nonSpatialMastNormalStdDev>"
       << "<di_nsmnsdVal species=\"Species_1\">0</di_nsmnsdVal>"
       << "<di_nsmnsdVal species=\"Species_2\">0</di_nsmnsdVal>"
       << "</di_nonSpatialMastNormalStdDev>"
       << "<di_nonSpatialNonMastNormalMean>"
       << "<di_nsnmnmVal species=\"Species_1\">12.5</di_nsnmnmVal>"
       << "<di_nsnmnmVal species=\"Species_2\">24</di_nsnmnmVal>"
       << "<di_nsnmnmVal species=\"Species_4\">876</di_nsnmnmVal>"
       << "</di_nonSpatialNonMastNormalMean>"
       << "<di_nonSpatialNonMastNormalStdDev>"
       << "<di_nsnmnsdVal species=\"Species_1\">0</di_nsnmnsdVal>"
       << "<di_nsnmnsdVal species=\"Species_2\">0</di_nsnmnsdVal>"
       << "<di_nsnmnsdVal species=\"Species_4\">0</di_nsnmnsdVal>"
       << "</di_nonSpatialNonMastNormalStdDev>"
       << "<di_nonSpatialMastGroup>"
       << "<di_nsmgVal species=\"Species_1\">3</di_nsmgVal>"
       << "<di_nsmgVal species=\"Species_2\">2</di_nsmgVal>"
       << "<di_nsmgVal species=\"Species_4\">1</di_nsmgVal>"
       << "</di_nonSpatialMastGroup>"
       << "<di_nonSpatialMastInvGaussMu>"
       << "<di_nsmigmVal species=\"Species_4\">70</di_nsmigmVal>"
       << "</di_nonSpatialMastInvGaussMu>"
       << "<di_nonSpatialMastInvGaussLambda>"
       << "<di_nsmiglVal species=\"Species_4\">0.01</di_nsmiglVal>"
       << "</di_nonSpatialMastInvGaussLambda>"
       << "<di_seedDistributionMethod>0</di_seedDistributionMethod>"
       << "</MastingNonSpatialDisperse1>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}


/////////////////////////////////////////////////////////////////////////////
// WriteNonSpatialDisperseXMLErrorFile1()
/////////////////////////////////////////////////////////////////////////////
const char* WriteNonSpatialDisperseXMLErrorFile1()
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
       << "<plot_lenX>100.0</plot_lenX>"
       << "<plot_lenY>100.0</plot_lenY>"
       << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
       << "<plot_temp_C>12.88171785</plot_temp_C>"
       << "<plot_latitude>55.37</plot_latitude>"
       << "</plot>";

  WriteNonSpatialDisperseTrees(oOut);

  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>MastingNonSpatialDisperse</behaviorName>"
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

  WriteNonSpatialDisperseAllometry(oOut);

  oOut << "<MastingNonSpatialDisperse1>"
       << "<di_nonSpatialMastMastFunction>"
       << "<di_nsmmfVal species=\"Species_1\">3</di_nsmmfVal>"
       << "<di_nsmmfVal species=\"Species_2\">3</di_nsmmfVal>"
       << "<di_nsmmfVal species=\"Species_4\">6</di_nsmmfVal>"
       << "</di_nonSpatialMastMastFunction>"
       << "<di_nonSpatialNonMastFunction>"
       << "<di_nsnmfVal species=\"Species_1\">3</di_nsnmfVal>"
       << "<di_nsnmfVal species=\"Species_2\">3</di_nsnmfVal>"
       << "<di_nsnmfVal species=\"Species_4\">3</di_nsnmfVal>"
       << "</di_nonSpatialNonMastFunction>"
       << "<di_nonSpatialMastBinomialP>"
       << "<di_nsmbpVal species=\"Species_1\">1</di_nsmbpVal>"
       << "<di_nsmbpVal species=\"Species_2\">0</di_nsmbpVal>"
       << "<di_nsmbpVal species=\"Species_4\">0.01</di_nsmbpVal>"
       << "</di_nonSpatialMastBinomialP>"
       << "<di_nonSpatialMastInvGaussMu>"
       << "<di_nsmigmVal species=\"Species_4\">-70</di_nsmigmVal>"
       << "</di_nonSpatialMastInvGaussMu>"
       << "<di_nonSpatialMastInvGaussLambda>"
       << "<di_nsmiglVal species=\"Species_4\">0.01</di_nsmiglVal>"
       << "</di_nonSpatialMastInvGaussLambda>"
       << "<di_nonSpatialMastNormalMean>"
       << "<di_nsmnmVal species=\"Species_1\">38.5</di_nsmnmVal>"
       << "<di_nsmnmVal species=\"Species_2\">1</di_nsmnmVal>"
       << "<di_nsmnmVal species=\"Species_4\">45</di_nsmnmVal>"
       << "</di_nonSpatialMastNormalMean>"
       << "<di_nonSpatialMastNormalStdDev>"
       << "<di_nsmnsdVal species=\"Species_1\">0</di_nsmnsdVal>"
       << "<di_nsmnsdVal species=\"Species_2\">6</di_nsmnsdVal>"
       << "<di_nsmnsdVal species=\"Species_4\">0</di_nsmnsdVal>"
       << "</di_nonSpatialMastNormalStdDev>"
       << "<di_nonSpatialNonMastNormalMean>"
       << "<di_nsnmnmVal species=\"Species_2\">24</di_nsnmnmVal>"
       << "<di_nsnmnmVal species=\"Species_4\">10001</di_nsnmnmVal>"
       << "</di_nonSpatialNonMastNormalMean>"
       << "<di_nonSpatialNonMastNormalStdDev>"
       << "<di_nsnmnsdVal species=\"Species_2\">0</di_nsnmnsdVal>"
       << "<di_nsnmnsdVal species=\"Species_4\">5</di_nsnmnsdVal>"
       << "</di_nonSpatialNonMastNormalStdDev>"
       << "<di_nonSpatialMastGroup>"
       << "<di_nsmgVal species=\"Species_1\">5</di_nsmgVal>"
       << "<di_nsmgVal species=\"Species_2\">3</di_nsmgVal>"
       << "<di_nsmgVal species=\"Species_4\">5</di_nsmgVal>"
       << "</di_nonSpatialMastGroup>"
       << "<di_seedDistributionMethod>0</di_seedDistributionMethod>"
       << "</MastingNonSpatialDisperse1>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteNonSpatialDisperseXMLErrorFile2()
/////////////////////////////////////////////////////////////////////////////
const char* WriteNonSpatialDisperseXMLErrorFile2()
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
       << "<plot_lenX>100.0</plot_lenX>"
       << "<plot_lenY>100.0</plot_lenY>"
       << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
       << "<plot_temp_C>12.88171785</plot_temp_C>"
       << "<plot_latitude>55.37</plot_latitude>"
       << "</plot>";

  WriteNonSpatialDisperseTrees(oOut);

  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>MastingNonSpatialDisperse</behaviorName>"
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

  WriteNonSpatialDisperseAllometry(oOut);

  oOut << "<MastingNonSpatialDisperse1>"
       << "<di_nonSpatialMastMastFunction>"
       << "<di_nsmmfVal species=\"Species_1\">3</di_nsmmfVal>"
       << "<di_nsmmfVal species=\"Species_2\">3</di_nsmmfVal>"
       << "<di_nsmmfVal species=\"Species_4\">3</di_nsmmfVal>"
       << "</di_nonSpatialMastMastFunction>"
       << "<di_nonSpatialNonMastFunction>"
       << "<di_nsnmfVal species=\"Species_1\">6</di_nsnmfVal>"
       << "<di_nsnmfVal species=\"Species_2\">3</di_nsnmfVal>"
       << "<di_nsnmfVal species=\"Species_4\">3</di_nsnmfVal>"
       << "</di_nonSpatialNonMastFunction>"
       << "<di_nonSpatialMastBinomialP>"
       << "<di_nsmbpVal species=\"Species_1\">1</di_nsmbpVal>"
       << "<di_nsmbpVal species=\"Species_2\">0</di_nsmbpVal>"
       << "<di_nsmbpVal species=\"Species_4\">0.01</di_nsmbpVal>"
       << "</di_nonSpatialMastBinomialP>"
       << "<di_nonSpatialNonMastInvGaussMu>"
       << "<di_nsnmigmVal species=\"Species_1\">-45</di_nsnmigmVal>"
       << "</di_nonSpatialNonMastInvGaussMu>"
       << "<di_nonSpatialNonMastInvGaussLambda>"
       << "<di_nsnmiglVal species=\"Species_1\">0.01</di_nsnmiglVal>"
       << "</di_nonSpatialNonMastInvGaussLambda>"
       << "<di_nonSpatialMastNormalMean>"
       << "<di_nsmnmVal species=\"Species_1\">38.5</di_nsmnmVal>"
       << "<di_nsmnmVal species=\"Species_2\">1</di_nsmnmVal>"
       << "<di_nsmnmVal species=\"Species_4\">45</di_nsmnmVal>"
       << "</di_nonSpatialMastNormalMean>"
       << "<di_nonSpatialMastNormalStdDev>"
       << "<di_nsmnsdVal species=\"Species_1\">0</di_nsmnsdVal>"
       << "<di_nsmnsdVal species=\"Species_2\">6</di_nsmnsdVal>"
       << "<di_nsmnsdVal species=\"Species_4\">0</di_nsmnsdVal>"
       << "</di_nonSpatialMastNormalStdDev>"
       << "<di_nonSpatialNonMastNormalMean>"
       << "<di_nsnmnmVal species=\"Species_2\">24</di_nsnmnmVal>"
       << "<di_nsnmnmVal species=\"Species_4\">10001</di_nsnmnmVal>"
       << "</di_nonSpatialNonMastNormalMean>"
       << "<di_nonSpatialNonMastNormalStdDev>"
       << "<di_nsnmnsdVal species=\"Species_2\">0</di_nsnmnsdVal>"
       << "<di_nsnmnsdVal species=\"Species_4\">5</di_nsnmnsdVal>"
       << "</di_nonSpatialNonMastNormalStdDev>"
       << "<di_nonSpatialMastGroup>"
       << "<di_nsmgVal species=\"Species_1\">5</di_nsmgVal>"
       << "<di_nsmgVal species=\"Species_2\">3</di_nsmgVal>"
       << "<di_nsmgVal species=\"Species_4\">5</di_nsmgVal>"
       << "</di_nonSpatialMastGroup>"
       << "<di_seedDistributionMethod>0</di_seedDistributionMethod>"
       << "</MastingNonSpatialDisperse1>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteNonSpatialDisperseXMLErrorFile3()
/////////////////////////////////////////////////////////////////////////////
const char* WriteNonSpatialDisperseXMLErrorFile3()
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
       << "<plot_lenX>100.0</plot_lenX>"
       << "<plot_lenY>100.0</plot_lenY>"
       << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
       << "<plot_temp_C>12.88171785</plot_temp_C>"
       << "<plot_latitude>55.37</plot_latitude>"
       << "</plot>";

  WriteNonSpatialDisperseTrees(oOut);

  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>MastingNonSpatialDisperse</behaviorName>"
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

  WriteNonSpatialDisperseAllometry(oOut);

  oOut << "<MastingNonSpatialDisperse1>"
       << "<di_nonSpatialMastMastFunction>"
       << "<di_nsmmfVal species=\"Species_1\">3</di_nsmmfVal>"
       << "<di_nsmmfVal species=\"Species_2\">3</di_nsmmfVal>"
       << "<di_nsmmfVal species=\"Species_4\">6</di_nsmmfVal>"
       << "</di_nonSpatialMastMastFunction>"
       << "<di_nonSpatialNonMastFunction>"
       << "<di_nsnmfVal species=\"Species_1\">3</di_nsnmfVal>"
       << "<di_nsnmfVal species=\"Species_2\">3</di_nsnmfVal>"
       << "<di_nsnmfVal species=\"Species_4\">3</di_nsnmfVal>"
       << "</di_nonSpatialNonMastFunction>"
       << "<di_nonSpatialMastBinomialP>"
       << "<di_nsmbpVal species=\"Species_1\">1</di_nsmbpVal>"
       << "<di_nsmbpVal species=\"Species_2\">0</di_nsmbpVal>"
       << "<di_nsmbpVal species=\"Species_4\">0.01</di_nsmbpVal>"
       << "</di_nonSpatialMastBinomialP>"
       << "<di_nonSpatialMastInvGaussMu>"
       << "<di_nsmigmVal species=\"Species_4\">70</di_nsmigmVal>"
       << "</di_nonSpatialMastInvGaussMu>"
       << "<di_nonSpatialMastInvGaussLambda>"
       << "<di_nsmiglVal species=\"Species_4\">-0.01</di_nsmiglVal>"
       << "</di_nonSpatialMastInvGaussLambda>"
       << "<di_nonSpatialMastNormalMean>"
       << "<di_nsmnmVal species=\"Species_1\">38.5</di_nsmnmVal>"
       << "<di_nsmnmVal species=\"Species_2\">1</di_nsmnmVal>"
       << "<di_nsmnmVal species=\"Species_4\">45</di_nsmnmVal>"
       << "</di_nonSpatialMastNormalMean>"
       << "<di_nonSpatialMastNormalStdDev>"
       << "<di_nsmnsdVal species=\"Species_1\">0</di_nsmnsdVal>"
       << "<di_nsmnsdVal species=\"Species_2\">6</di_nsmnsdVal>"
       << "<di_nsmnsdVal species=\"Species_4\">0</di_nsmnsdVal>"
       << "</di_nonSpatialMastNormalStdDev>"
       << "<di_nonSpatialNonMastNormalMean>"
       << "<di_nsnmnmVal species=\"Species_2\">24</di_nsnmnmVal>"
       << "<di_nsnmnmVal species=\"Species_4\">10001</di_nsnmnmVal>"
       << "</di_nonSpatialNonMastNormalMean>"
       << "<di_nonSpatialNonMastNormalStdDev>"
       << "<di_nsnmnsdVal species=\"Species_2\">0</di_nsnmnsdVal>"
       << "<di_nsnmnsdVal species=\"Species_4\">5</di_nsnmnsdVal>"
       << "</di_nonSpatialNonMastNormalStdDev>"
       << "<di_nonSpatialMastGroup>"
       << "<di_nsmgVal species=\"Species_1\">5</di_nsmgVal>"
       << "<di_nsmgVal species=\"Species_2\">3</di_nsmgVal>"
       << "<di_nsmgVal species=\"Species_4\">5</di_nsmgVal>"
       << "</di_nonSpatialMastGroup>"
       << "<di_seedDistributionMethod>0</di_seedDistributionMethod>"
       << "</MastingNonSpatialDisperse1>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteNonSpatialDisperseXMLErrorFile4()
/////////////////////////////////////////////////////////////////////////////
const char* WriteNonSpatialDisperseXMLErrorFile4()
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
       << "<plot_lenX>100.0</plot_lenX>"
       << "<plot_lenY>100.0</plot_lenY>"
       << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
       << "<plot_temp_C>12.88171785</plot_temp_C>"
       << "<plot_latitude>55.37</plot_latitude>"
       << "</plot>";

  WriteNonSpatialDisperseTrees(oOut);

  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>MastingNonSpatialDisperse</behaviorName>"
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

  WriteNonSpatialDisperseAllometry(oOut);

  oOut << "<MastingNonSpatialDisperse1>"
       << "<di_nonSpatialMastMastFunction>"
       << "<di_nsmmfVal species=\"Species_1\">3</di_nsmmfVal>"
       << "<di_nsmmfVal species=\"Species_2\">3</di_nsmmfVal>"
       << "<di_nsmmfVal species=\"Species_4\">3</di_nsmmfVal>"
       << "</di_nonSpatialMastMastFunction>"
       << "<di_nonSpatialNonMastFunction>"
       << "<di_nsnmfVal species=\"Species_1\">6</di_nsnmfVal>"
       << "<di_nsnmfVal species=\"Species_2\">3</di_nsnmfVal>"
       << "<di_nsnmfVal species=\"Species_4\">3</di_nsnmfVal>"
       << "</di_nonSpatialNonMastFunction>"
       << "<di_nonSpatialMastBinomialP>"
       << "<di_nsmbpVal species=\"Species_1\">1</di_nsmbpVal>"
       << "<di_nsmbpVal species=\"Species_2\">0</di_nsmbpVal>"
       << "<di_nsmbpVal species=\"Species_4\">0.01</di_nsmbpVal>"
       << "</di_nonSpatialMastBinomialP>"
       << "<di_nonSpatialNonMastInvGaussMu>"
       << "<di_nsnmigmVal species=\"Species_1\">45</di_nsnmigmVal>"
       << "</di_nonSpatialNonMastInvGaussMu>"
       << "<di_nonSpatialNonMastInvGaussLambda>"
       << "<di_nsnmiglVal species=\"Species_1\">-0.01</di_nsnmiglVal>"
       << "</di_nonSpatialNonMastInvGaussLambda>"
       << "<di_nonSpatialMastNormalMean>"
       << "<di_nsmnmVal species=\"Species_1\">38.5</di_nsmnmVal>"
       << "<di_nsmnmVal species=\"Species_2\">1</di_nsmnmVal>"
       << "<di_nsmnmVal species=\"Species_4\">45</di_nsmnmVal>"
       << "</di_nonSpatialMastNormalMean>"
       << "<di_nonSpatialMastNormalStdDev>"
       << "<di_nsmnsdVal species=\"Species_1\">0</di_nsmnsdVal>"
       << "<di_nsmnsdVal species=\"Species_2\">6</di_nsmnsdVal>"
       << "<di_nsmnsdVal species=\"Species_4\">0</di_nsmnsdVal>"
       << "</di_nonSpatialMastNormalStdDev>"
       << "<di_nonSpatialNonMastNormalMean>"
       << "<di_nsnmnmVal species=\"Species_2\">24</di_nsnmnmVal>"
       << "<di_nsnmnmVal species=\"Species_4\">10001</di_nsnmnmVal>"
       << "</di_nonSpatialNonMastNormalMean>"
       << "<di_nonSpatialNonMastNormalStdDev>"
       << "<di_nsnmnsdVal species=\"Species_2\">0</di_nsnmnsdVal>"
       << "<di_nsnmnsdVal species=\"Species_4\">5</di_nsnmnsdVal>"
       << "</di_nonSpatialNonMastNormalStdDev>"
       << "<di_nonSpatialMastGroup>"
       << "<di_nsmgVal species=\"Species_1\">5</di_nsmgVal>"
       << "<di_nsmgVal species=\"Species_2\">3</di_nsmgVal>"
       << "<di_nsmgVal species=\"Species_4\">5</di_nsmgVal>"
       << "</di_nonSpatialMastGroup>"
       << "<di_seedDistributionMethod>0</di_seedDistributionMethod>"
       << "</MastingNonSpatialDisperse1>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteNonSpatialDisperseTrees()
/////////////////////////////////////////////////////////////////////////////
void WriteNonSpatialDisperseTrees(std::fstream &oOut) {
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
// WriteNonSpatialDisperseAllometry()
/////////////////////////////////////////////////////////////////////////////
void WriteNonSpatialDisperseAllometry(std::fstream &oOut) {
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
