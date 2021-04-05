//---------------------------------------------------------------------------
// TestMastingDisperseAutocorrelation.cpp
//---------------------------------------------------------------------------
#include "TestMastingDisperseAutocorrelation.h"
#include <gtest/gtest.h>
#include "TreePopulation.h"
#include "SimManager.h"
#include "MastingDisperseAutocorrelation.h"
#include <stdio.h>
#include <fstream>
#include <math.h>
#include <iostream>

/////////////////////////////////////////////////////////////////////////////
// NormalProcessingRun1()
// Mast level is an entered time series
/////////////////////////////////////////////////////////////////////////////
TEST(MastingDisperseAutocorrelation, NormalProcessingRun1) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    //Feed our file to the sim manager
    p_oSimManager->ReadFile(WriteMastingDisperseAutocorrelationXMLFile1());

    clTreePopulation *p_oPop = (clTreePopulation *) p_oSimManager->GetPopulationObject("treepopulation");
    clTreeSearch *p_oAllTrees;
    clBehaviorBase *p_oTemp = p_oSimManager->GetBehaviorObject("MastingDisperseAutocorrelation");
    clMastingDisperseAutocorrelation *p_oDisp = dynamic_cast<clMastingDisperseAutocorrelation*>(p_oTemp);
    clTree *p_oTree;
    float fTemp, fMean, fSD;
    int iNumSp1, iNumSp2, iNumSp4;

    // Check to make sure the entered timeseries is correct
    EXPECT_LT(fabs(p_oDisp->GetMastLevel(1) - 0), 0.00001);
    EXPECT_LT(fabs(p_oDisp->GetMastLevel(2) - 0.74), 0.00001);
    EXPECT_LT(fabs(p_oDisp->GetMastLevel(3) - 1), 0.00001);
    EXPECT_LT(fabs(p_oDisp->GetMastLevel(4) - 0.25), 0.00001);
    EXPECT_LT(fabs(p_oDisp->GetMastLevel(5) - 0.5), 0.00001);

    //Create three trees and assign sps scores so we can check to make sure they are preserved
    p_oTree = p_oPop->CreateTree(1, 1, 0, clTreePopulation::adult, 20.0);
    fTemp = 0.2;
    p_oTree->SetValue(p_oPop->GetFloatDataCode("sps", p_oTree->GetSpecies(), p_oTree->GetType()), fTemp, true, true);
    p_oTree = p_oPop->CreateTree(1, 1, 1, clTreePopulation::adult, 30.0);
    fTemp = 0.5;
    p_oTree->SetValue(p_oPop->GetFloatDataCode("sps", p_oTree->GetSpecies(), p_oTree->GetType()), fTemp, true, true);
    p_oTree = p_oPop->CreateTree(1, 1, 3, clTreePopulation::adult, 40.0);
    fTemp = 0.8;
    p_oTree->SetValue(p_oPop->GetFloatDataCode("sps", p_oTree->GetSpecies(), p_oTree->GetType()), fTemp, true, true);

    //------------------------------------------------------------------------/
    // Timestep 1
    // Mast level of 0, nobody reproduces
    //------------------------------------------------------------------------/
    p_oSimManager->RunSim(1);

    //Make sure the trees still have the same sps, and prev seed scores of 0
    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {
      if (p_oTree->GetType() == clTreePopulation::adult) {
        p_oTree->GetValue(p_oPop->GetFloatDataCode("sps", p_oTree->GetSpecies(), p_oTree->GetType()), &fTemp);
        if (p_oTree->GetSpecies() == 0) {
          EXPECT_LT(fabs(fTemp - 0.2), 0.00001);
        }
        else if (p_oTree->GetSpecies() == 1) {
          EXPECT_LT(fabs(fTemp - 0.5), 0.00001);
        }
        else {
          EXPECT_LT(fabs(fTemp - 0.8), 0.00001);
        }
      }

      p_oTree->GetValue(p_oPop->GetFloatDataCode("prevseeds", p_oTree->GetSpecies(), p_oTree->GetType()), &fTemp);
      EXPECT_EQ(0, fTemp);
      p_oTree = p_oAllTrees->NextTree();
    }

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
    EXPECT_EQ(0, iNumSp1);
    EXPECT_EQ(0, iNumSp2);
    EXPECT_EQ(0, iNumSp4);


    //Create more trees, don't assign sps, make sure they get a score.
    p_oPop->CreateTree(10, 1, 0, clTreePopulation::adult, 20.0);
    p_oPop->CreateTree(10, 1, 1, clTreePopulation::adult, 30.0);
    p_oPop->CreateTree(10, 1, 3, clTreePopulation::adult, 40.0);

    //------------------------------------------------------------------------/
    // Timestep 2
    // Some reproduction, but not species 1, which has parameters to prevent
    //------------------------------------------------------------------------/
    p_oSimManager->RunSim(1);

    //Make sure the trees have the correct sps
    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {
      if (p_oTree->GetType() == clTreePopulation::adult) {
        p_oTree->GetValue(p_oPop->GetXCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTemp);

        if (fabs(fTemp - 10.0) < 0.001) {
          p_oTree->GetValue(p_oPop->GetFloatDataCode("sps", p_oTree->GetSpecies(), p_oTree->GetType()), &fTemp);
          EXPECT_LT(fTemp, 2);
          EXPECT_GT(fTemp, 0);
        } else {
          p_oTree->GetValue(p_oPop->GetFloatDataCode("sps", p_oTree->GetSpecies(), p_oTree->GetType()), &fTemp);
          if (p_oTree->GetSpecies() == 0) {
            EXPECT_LT(fabs(fTemp - 0.2), 0.00001);
          }
          else if (p_oTree->GetSpecies() == 1) {
            EXPECT_LT(fabs(fTemp - 0.5), 0.00001);
          }
          else {
            EXPECT_LT(fabs(fTemp - 0.8), 0.00001);
          }
        }

        p_oTree->GetValue(p_oPop->GetFloatDataCode("prevseeds", p_oTree->GetSpecies(), p_oTree->GetType()), &fTemp);
        if (0 == p_oTree->GetSpecies()) EXPECT_EQ(0, fTemp);
        else EXPECT_GT(fTemp, 0);
      }
      p_oTree = p_oAllTrees->NextTree();
    }

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
    EXPECT_EQ(0, iNumSp1);
    EXPECT_GT(iNumSp2, 0);
    EXPECT_GT(iNumSp4, 0);

    //------------------------------------------------------------------------/
    // Timestep 3
    // More for sps. Create a whole bunch of trees and test the draws
    //------------------------------------------------------------------------/
    for (iNumSp1 = 0; iNumSp1 < 1000; iNumSp1++) {
      p_oPop->CreateTree(10, 1, 0, clTreePopulation::adult, 20.0);
    }
    p_oSimManager->RunSim(1);

    // Calculate mean
    iNumSp1 = 0;
    fMean = 0;
    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {
      if (p_oTree->GetType() == clTreePopulation::adult && 0 == p_oTree->GetSpecies()) {
        p_oTree->GetValue(p_oPop->GetFloatDataCode("sps", p_oTree->GetSpecies(), p_oTree->GetType()), &fTemp);
        fMean += fTemp;
        iNumSp1++;
      }
      p_oTree = p_oAllTrees->NextTree();
    }
    fMean /= iNumSp1;

    //Calculate standard deviation
    fSD = 0;
    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {
      if (p_oTree->GetType() == clTreePopulation::adult && 0 == p_oTree->GetSpecies()) {
        p_oTree->GetValue(p_oPop->GetFloatDataCode("sps", p_oTree->GetSpecies(), p_oTree->GetType()), &fTemp);
        fSD += ((fTemp - fMean) * (fTemp - fMean));
      }
      p_oTree = p_oAllTrees->NextTree();
    }
    fSD /= iNumSp1;
    fSD = sqrt(fSD);

    EXPECT_TRUE(fMean > 0.9 && fMean < 1.1);
    EXPECT_TRUE(fSD > 0 && fSD < 0.2);

    delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

/////////////////////////////////////////////////////////////////////////////
// NormalProcessingRun2()
// Tests second normal processing run.
// Tests seed production numbers. One DBH is above the max. For ease, all
// trees are set to reproduce.
/////////////////////////////////////////////////////////////////////////////
TEST(MastingDisperseAutocorrelation, NormalProcessingRun2) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    //Feed our file to the sim manager
    p_oSimManager->ReadFile(WriteMastingDisperseAutocorrelationXMLFile2());

    clTreePopulation *p_oPop = (clTreePopulation *) p_oSimManager->GetPopulationObject("treepopulation");
    clTreeSearch *p_oAllTrees;
    clTree *p_oTree;
    float fTemp;
    int iNumSp1, iNumSp2, iNumSp4;

    //Create three trees and assign sps scores so we can check to make sure they are preserved
    p_oTree = p_oPop->CreateTree(1, 1, 0, clTreePopulation::adult, 20.0);
    fTemp = 0.2;
    p_oTree->SetValue(p_oPop->GetFloatDataCode("sps", p_oTree->GetSpecies(), p_oTree->GetType()), fTemp, true, true);
    p_oTree = p_oPop->CreateTree(1, 1, 1, clTreePopulation::adult, 30.0);
    fTemp = 0.5;
    p_oTree->SetValue(p_oPop->GetFloatDataCode("sps", p_oTree->GetSpecies(), p_oTree->GetType()), fTemp, true, true);
    p_oTree = p_oPop->CreateTree(1, 1, 3, clTreePopulation::adult, 40.0);
    fTemp = 0.8;
    p_oTree->SetValue(p_oPop->GetFloatDataCode("sps", p_oTree->GetSpecies(), p_oTree->GetType()), fTemp, true, true);

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
    EXPECT_TRUE(131 < iNumSp1 && 136 > iNumSp1);
    EXPECT_TRUE(37225 < iNumSp2 && 37231 > iNumSp2);
    EXPECT_TRUE(1420 < iNumSp4 && 1424 > iNumSp4);

    //Check previous seed values - should match seedling counts
    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {
      if (p_oTree->GetType() == clTreePopulation::adult) {

        p_oTree->GetValue(p_oPop->GetFloatDataCode("prevseeds", p_oTree->GetSpecies(), p_oTree->GetType()), &fTemp);
        if (0 == p_oTree->GetSpecies()) {
          EXPECT_EQ(iNumSp1, fTemp);
        } else if (1 == p_oTree->GetSpecies()) {
          EXPECT_EQ(iNumSp2, fTemp);
        } else {
          EXPECT_EQ(iNumSp4, fTemp);
        }
      }
      p_oTree = p_oAllTrees->NextTree();
    }

    delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

/////////////////////////////////////////////////////////////////////////////
// NormalProcessingRun3()
// Tests probabilities.
/////////////////////////////////////////////////////////////////////////////
TEST(MastingDisperseAutocorrelation, NormalProcessingRun3) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    //Feed our file to the sim manager
    p_oSimManager->ReadFile(WriteMastingDisperseAutocorrelationXMLFile3());

    clTreePopulation *p_oPop = (clTreePopulation *) p_oSimManager->GetPopulationObject("treepopulation");
    clTreeSearch *p_oAllTrees;
    clTree *p_oTree;
    float fTemp;
    int iNumSp1, iNumSp2, iNumSp4;

    //Create three trees and assign sps scores so we can check to make sure they are preserved
    for (iNumSp1 = 0; iNumSp1 < 1000; iNumSp1++) {
      p_oTree = p_oPop->CreateTree(1, 1, 0, clTreePopulation::adult, 20.0);
      fTemp = 0.2;
      p_oTree->SetValue(p_oPop->GetFloatDataCode("sps", p_oTree->GetSpecies(), p_oTree->GetType()), fTemp, true, true);
      p_oTree = p_oPop->CreateTree(1, 1, 1, clTreePopulation::adult, 15.0);
      fTemp = 0.5;
      p_oTree->SetValue(p_oPop->GetFloatDataCode("sps", p_oTree->GetSpecies(), p_oTree->GetType()), fTemp, true, true);
      p_oTree = p_oPop->CreateTree(1, 1, 3, clTreePopulation::adult, 40.0);
      fTemp = 0.8;
      p_oTree->SetValue(p_oPop->GetFloatDataCode("sps", p_oTree->GetSpecies(), p_oTree->GetType()), fTemp, true, true);
    }

    //Run one timestep
    p_oSimManager->RunSim(1);

    //Count the number of trees that reproduced
    iNumSp1 = 0;
    iNumSp2 = 0;
    iNumSp4 = 0;
    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {
      if (p_oTree->GetType() == clTreePopulation::adult) {
        p_oTree->GetValue(p_oPop->GetFloatDataCode("prevseeds", p_oTree->GetSpecies(), p_oTree->GetType()), &fTemp);
        if (fTemp > 0) {
          if (p_oTree->GetSpecies() == 0) iNumSp1++;
          else if (p_oTree->GetSpecies() == 1) iNumSp2++;
          else iNumSp4++;
        }
      }
      p_oTree = p_oAllTrees->NextTree();
    }
    EXPECT_TRUE(iNumSp1 > 800 && iNumSp1 < 850);
    EXPECT_TRUE(iNumSp2 > 650 && iNumSp2 < 730);
    EXPECT_TRUE(iNumSp4 > 700 && iNumSp4 < 750);

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
    EXPECT_TRUE(fabs(iNumSp1 - 22132)/22132 < 0.1);
    EXPECT_TRUE(fabs(iNumSp2 - 36999)/36999 < 0.1);
    EXPECT_TRUE(fabs(iNumSp4 - 2070)/2070 < 0.1);

    delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

/////////////////////////////////////////////////////////////////////////////
// NormalProcessingRun4()
// Testing randomly assigned mast levels
/////////////////////////////////////////////////////////////////////////////
TEST(MastingDisperseAutocorrelation, NormalProcessingRun4) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    //Feed our file to the sim manager
    p_oSimManager->ReadFile(WriteMastingDisperseAutocorrelationXMLFile4());

    clTreePopulation *p_oPop = (clTreePopulation *) p_oSimManager->GetPopulationObject("treepopulation");
    clTreeSearch *p_oAllTrees;
    clBehaviorBase *p_oTemp = p_oSimManager->GetBehaviorObject("MastingDisperseAutocorrelation");
    clMastingDisperseAutocorrelation *p_oDisp = dynamic_cast<clMastingDisperseAutocorrelation*>(p_oTemp);
    clTree *p_oTree;
    float fTemp, fSeeds1, fSeeds2, fMast1;
    int iNumSp1, iNumSp2;

    // Grab the mast levels - should already be assigned
    fMast1 = p_oDisp->GetMastLevel(1);

    //Create some trees, all with seed producer scores of 1
    fTemp = 1;
    fSeeds2 = 54;
    for (iNumSp1 = 0; iNumSp1 < 1000; iNumSp1++) {
      p_oTree = p_oPop->CreateTree(1, 1, 0, clTreePopulation::adult, 30.0);
      p_oTree->SetValue(p_oPop->GetFloatDataCode("sps", p_oTree->GetSpecies(), p_oTree->GetType()), fTemp, true, true);

      p_oTree = p_oPop->CreateTree(1, 1, 1, clTreePopulation::adult, 30.0);
      p_oTree->SetValue(p_oPop->GetFloatDataCode("sps", p_oTree->GetSpecies(), p_oTree->GetType()), fTemp, true, true);
      p_oTree->SetValue(p_oPop->GetFloatDataCode("prevseeds", p_oTree->GetSpecies(), p_oTree->GetType()), fSeeds2, true, true);
    }

    //------------------------------------------------------------------------/
    // Timestep 1
    // Expected seeds produced are equal to mast level for species 1
    //------------------------------------------------------------------------/
    p_oSimManager->RunSim(1);

    //Everybody should have the mast level as previous seeds. There might be
    //a few non-masting individuals but make sure it's not many
    fSeeds1 = fMast1 * 100;
    fSeeds2 = fMast1 * 79.55555556;
    iNumSp1 = 0;
    iNumSp2 = 0;
    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {
      if (p_oTree->GetType() == clTreePopulation::adult) {
        p_oTree->GetValue(p_oPop->GetFloatDataCode("prevseeds", p_oTree->GetSpecies(), p_oTree->GetType()), &fTemp);
        if (fTemp == 0) {
          if (p_oTree->GetSpecies() == 0) iNumSp1++;
          else iNumSp2++;
        } else {
          if (p_oTree->GetSpecies() == 0) {
            EXPECT_TRUE(fTemp == trunc(fSeeds1) || fTemp == (trunc(fSeeds1)+1));
          } else {
            EXPECT_TRUE(fTemp == trunc(fSeeds2) || fTemp == (trunc(fSeeds2)+1));
          }
        }
      }
      p_oTree = p_oAllTrees->NextTree();
    }

    //There shouldn't be many non-reproducers
    EXPECT_TRUE(iNumSp1 < 30);
    EXPECT_TRUE(iNumSp2 < 30);

    //Count the number of seedlings of each type
    iNumSp1 = 0;
    iNumSp2 = 0;
    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {
      if (p_oTree->GetType() == clTreePopulation::seedling) {
        if (p_oTree->GetSpecies() == 0) iNumSp1++;
        else iNumSp2++;
      }
      p_oTree = p_oAllTrees->NextTree();
    }

    //Check the counts
    fSeeds1 = fMast1 * 100000;
    EXPECT_TRUE(fabs(iNumSp1 - fSeeds1)/fSeeds1 < 0.05);

    fSeeds2 = fMast1 * 79555.5555;
    EXPECT_TRUE(fabs(iNumSp2 - fSeeds2)/fSeeds2 < 0.05);

    delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

////////////////////////////////////////////////////////////////////////////
// TestErrorProcessing()
////////////////////////////////////////////////////////////////////////////
TEST(MastingDisperseAutocorrelation, TestErrorProcessing) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try
  {
    p_oSimManager->ReadFile(WriteMastingDisperseAutocorrelationXMLErrorFile1());
    FAIL() << "TestMastingDisperseAutocorrelation error processing didn't catch error for WriteMastingDisperseAutocorrelationXMLErrorFile1.";
  }
  catch (modelErr& err)
  {
    if (err.sFunction.compare("clMastingDisperseAutocorrelation::GetParameterFileData") != 0)
    {
      FAIL() << "TestMastingDisperseAutocorrelation error processing caught wrong error for WriteMastingDisperseAutocorrelationXMLErrorFile1.";
    }
    ;
  }

  try
  {
    p_oSimManager->ReadFile(WriteMastingDisperseAutocorrelationXMLErrorFile2());
    FAIL() << "TestMastingDisperseAutocorrelation error processing didn't catch error for WriteMastingDisperseAutocorrelationXMLErrorFile2.";
  }
  catch (modelErr& err)
  {
    if (err.sFunction.compare("clMastingDisperseAutocorrelation::GetMastTimeseries") != 0)
    {
      FAIL() << "TestMastingDisperseAutocorrelation error processing caught wrong error for WriteMastingDisperseAutocorrelationXMLErrorFile2.";
    }
    ;
  }

  try
  {
    p_oSimManager->ReadFile(WriteMastingDisperseAutocorrelationXMLErrorFile3());
    FAIL() << "TestMastingDisperseAutocorrelation error processing didn't catch error for WriteMastingDisperseAutocorrelationXMLErrorFile3.";
  }
  catch (modelErr& err)
  {
    if (err.sFunction.compare("clMastingDisperseAutocorrelation::GetParameterFileData") != 0)
    {
      FAIL() << "TestMastingDisperseAutocorrelation error processing caught wrong error for WriteMastingDisperseAutocorrelationXMLErrorFile3.";
    }
    ;
  }

  try
  {
    p_oSimManager->ReadFile(WriteMastingDisperseAutocorrelationXMLErrorFile4());
    FAIL() << "TestMastingDisperseAutocorrelation error processing didn't catch error for WriteMastingDisperseAutocorrelationXMLErrorFile4.";
  }
  catch (modelErr& err)
  {
    if (err.sFunction.compare("clMastingDisperseAutocorrelation::GetParameterFileData") != 0)
    {
      FAIL() << "TestMastingDisperseAutocorrelation error processing caught wrong error for WriteMastingDisperseAutocorrelationXMLErrorFile4.";
    }
    ;
  }

  try
  {
    p_oSimManager->ReadFile(WriteMastingDisperseAutocorrelationXMLErrorFile5());
    FAIL() << "TestMastingDisperseAutocorrelation error processing didn't catch error for WriteMastingDisperseAutocorrelationXMLErrorFile5.";
  }
  catch (modelErr& err)
  {
    if (err.sFunction.compare("clMastingDisperseAutocorrelation::GetParameterFileData") != 0)
    {
      FAIL() << "TestMastingDisperseAutocorrelation error processing caught wrong error for WriteMastingDisperseAutocorrelationXMLErrorFile5.";
    }
    ;
  }

  try
  {
    p_oSimManager->ReadFile(WriteMastingDisperseAutocorrelationXMLErrorFile6());
    FAIL() << "TestMastingDisperseAutocorrelation error processing didn't catch error for WriteMastingDisperseAutocorrelationXMLErrorFile7.";
  }
  catch (modelErr& err)
  {
    if (err.sFunction.compare("clMastingDisperseAutocorrelation::GetParameterFileData") != 0)
    {
      FAIL() << "TestMastingDisperseAutocorrelation error processing caught wrong error for WriteMastingDisperseAutocorrelationXMLErrorFile7.";
    }
    ;
  }

  delete p_oSimManager;
}

/////////////////////////////////////////////////////////////////////////////
// WriteMastingDisperseAutocorrelationXMLFile1()
/////////////////////////////////////////////////////////////////////////////
const char* WriteMastingDisperseAutocorrelationXMLFile1()
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
      << "<yearsPerTimestep>1</yearsPerTimestep>"
      << "<plot_lenX>200.0</plot_lenX>"
      << "<plot_lenY>200.0</plot_lenY>"
      << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
      << "<plot_temp_C>12.88171785</plot_temp_C>"
      << "<plot_latitude>55.37</plot_latitude>"
      << "</plot>";

  WriteMastingDisperseAutocorrelationTrees(oOut);

  oOut << "<behaviorList>"
      << "<behavior>"
      << "<behaviorName>MastingDisperseAutocorrelation</behaviorName>"
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

  WriteMastingDisperseAutocorrelationAllometry(oOut);

  oOut << "<GeneralDisperse>"
      << "<di_seedDistributionMethod>0</di_seedDistributionMethod>"
      << "</GeneralDisperse>"
      << "<MastingDisperseAutocorrelation1>"
      << "<di_minDbhForReproduction>"
      << "<di_mdfrVal species=\"Species_1\">10.0</di_mdfrVal>"
      << "<di_mdfrVal species=\"Species_2\">10.0</di_mdfrVal>"
      << "<di_mdfrVal species=\"Species_3\">10.0</di_mdfrVal>"
      << "<di_mdfrVal species=\"Species_4\">10.0</di_mdfrVal>"
      << "</di_minDbhForReproduction>"

      //Mast timeseries
      << "<di_mdaMastTS>"
      << "<di_mdaMTS ts=\"1\">0</di_mdaMTS>"
      << "<di_mdaMTS ts=\"2\">0.74</di_mdaMTS>"
      << "<di_mdaMTS ts=\"3\">1</di_mdaMTS>"
      << "<di_mdaMTS ts=\"4\">0.25</di_mdaMTS>"
      << "<di_mdaMTS ts=\"5\">0.5</di_mdaMTS>"
      << "</di_mdaMastTS>"


      //Maximum DBH for size effects
      << "<di_maxDbhForSizeEffect>"
      << "<di_mdfseVal species=\"Species_1\">100</di_mdfseVal>"
      << "<di_mdfseVal species=\"Species_2\">100</di_mdfseVal>"
      << "<di_mdfseVal species=\"Species_4\">100</di_mdfseVal>"
      << "</di_maxDbhForSizeEffect>"

      //Beta
      << "<di_weibullCanopyBeta>"
      << "<di_wcbVal species=\"Species_1\">1</di_wcbVal>"
      << "<di_wcbVal species=\"Species_2\">1</di_wcbVal>"
      << "<di_wcbVal species=\"Species_4\">1</di_wcbVal>"
      << "</di_weibullCanopyBeta>"

      //Mean STR
      << "<di_weibullCanopySTR>"
      << "<di_wcsVal species=\"Species_1\">1000</di_wcsVal>"
      << "<di_wcsVal species=\"Species_2\">1000</di_wcsVal>"
      << "<di_wcsVal species=\"Species_4\">1000</di_wcsVal>"
      << "</di_weibullCanopySTR>"

      //A, B, and C for fraction participating
      << "<di_mdaReproFracA>"
      << "<di_mdarfaVal species=\"Species_1\">1</di_mdarfaVal>"
      << "<di_mdarfaVal species=\"Species_2\">10000</di_mdarfaVal>"
      << "<di_mdarfaVal species=\"Species_4\">10000</di_mdarfaVal>"
      << "</di_mdaReproFracA>"
      << "<di_mdaReproFracB>"
      << "<di_mdarfbVal species=\"Species_1\">1</di_mdarfbVal>"
      << "<di_mdarfbVal species=\"Species_2\">1</di_mdarfbVal>"
      << "<di_mdarfbVal species=\"Species_4\">1</di_mdarfbVal>"
      << "</di_mdaReproFracB>"
      << "<di_mdaReproFracC>"
      << "<di_mdarfcVal species=\"Species_1\">0</di_mdarfcVal>"
      << "<di_mdarfcVal species=\"Species_2\">1</di_mdarfcVal>"
      << "<di_mdarfcVal species=\"Species_4\">1</di_mdarfcVal>"
      << "</di_mdaReproFracC>"

      //Autocorrelation factor for rho
      << "<di_mdaRhoACF>"
      << "<di_mdaraVal species=\"Species_1\">1</di_mdaraVal>"
      << "<di_mdaraVal species=\"Species_2\">1</di_mdaraVal>"
      << "<di_mdaraVal species=\"Species_4\">1</di_mdaraVal>"
      << "</di_mdaRhoACF>"

      //Standard deviation for noise for rho
      << "<di_mdaRhoNoiseSD>"
      << "<di_mdarnsdVal species=\"Species_1\">0</di_mdarnsdVal>"
      << "<di_mdarnsdVal species=\"Species_2\">0</di_mdarnsdVal>"
      << "<di_mdarnsdVal species=\"Species_4\">0</di_mdarnsdVal>"
      << "</di_mdaRhoNoiseSD>"

      //Slope and intercept of the linear function of DBH for individual
      //probability of reproducting
      << "<di_mdaPRA>"
      << "<di_mdapraVal species=\"Species_1\">0.75</di_mdapraVal>"
      << "<di_mdapraVal species=\"Species_2\">100</di_mdapraVal>"
      << "<di_mdapraVal species=\"Species_4\">100</di_mdapraVal>"
      << "</di_mdaPRA>"
      << "<di_mdaPRB>"
      << "<di_mdaprbVal species=\"Species_1\">0.004</di_mdaprbVal>"
      << "<di_mdaprbVal species=\"Species_2\">0.004</di_mdaprbVal>"
      << "<di_mdaprbVal species=\"Species_4\">0.004</di_mdaprbVal>"
      << "</di_mdaPRB>"

      //Seed producer score standard deviation
      << "<di_mdaSPSSD>"
      << "<di_mdaspssdVal species=\"Species_1\">0.1</di_mdaspssdVal>"
      << "<di_mdaspssdVal species=\"Species_2\">0.1</di_mdaspssdVal>"
      << "<di_mdaspssdVal species=\"Species_4\">0.1</di_mdaspssdVal>"
      << "</di_mdaSPSSD>"

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
      << "</MastingDisperseAutocorrelation1>"
      << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteMastingDisperseAutocorrelationXMLFile2()
/////////////////////////////////////////////////////////////////////////////
const char* WriteMastingDisperseAutocorrelationXMLFile2()
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
        << "<randomSeed>10</randomSeed>"
        << "<yearsPerTimestep>1</yearsPerTimestep>"
        << "<plot_lenX>200.0</plot_lenX>"
        << "<plot_lenY>200.0</plot_lenY>"
        << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
        << "<plot_temp_C>12.88171785</plot_temp_C>"
        << "<plot_latitude>55.37</plot_latitude>"
        << "</plot>";

    WriteMastingDisperseAutocorrelationTrees(oOut);

    oOut << "<behaviorList>"
        << "<behavior>"
        << "<behaviorName>MastingDisperseAutocorrelation</behaviorName>"
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

    WriteMastingDisperseAutocorrelationAllometry(oOut);

    oOut << "<GeneralDisperse>"
        << "<di_seedDistributionMethod>0</di_seedDistributionMethod>"
        << "</GeneralDisperse>"
        << "<MastingDisperseAutocorrelation1>"
        << "<di_minDbhForReproduction>"
        << "<di_mdfrVal species=\"Species_1\">10.0</di_mdfrVal>"
        << "<di_mdfrVal species=\"Species_2\">10.0</di_mdfrVal>"
        << "<di_mdfrVal species=\"Species_3\">10.0</di_mdfrVal>"
        << "<di_mdfrVal species=\"Species_4\">10.0</di_mdfrVal>"
        << "</di_minDbhForReproduction>"

        //Mast timeseries
        << "<di_mdaMastTS>"
        << "<di_mdaMTS ts=\"1\">1</di_mdaMTS>"
        << "<di_mdaMTS ts=\"2\">1</di_mdaMTS>"
        << "<di_mdaMTS ts=\"3\">1</di_mdaMTS>"
        << "<di_mdaMTS ts=\"4\">1</di_mdaMTS>"
        << "<di_mdaMTS ts=\"5\">1</di_mdaMTS>"
        << "</di_mdaMastTS>"


        //Maximum DBH for size effects
        << "<di_maxDbhForSizeEffect>"
        << "<di_mdfseVal species=\"Species_1\">15</di_mdfseVal>"
        << "<di_mdfseVal species=\"Species_2\">100</di_mdfseVal>"
        << "<di_mdfseVal species=\"Species_4\">100</di_mdfseVal>"
        << "</di_maxDbhForSizeEffect>"

        //Beta
        << "<di_weibullCanopyBeta>"
        << "<di_wcbVal species=\"Species_1\">1</di_wcbVal>"
        << "<di_wcbVal species=\"Species_2\">0.8</di_wcbVal>"
        << "<di_wcbVal species=\"Species_4\">2</di_wcbVal>"
        << "</di_weibullCanopyBeta>"

        //Mean STR
        << "<di_weibullCanopySTR>"
        << "<di_wcsVal species=\"Species_1\">1000</di_wcsVal>"
        << "<di_wcsVal species=\"Species_2\">74458</di_wcsVal>"
        << "<di_wcsVal species=\"Species_4\">1000</di_wcsVal>"
        << "</di_weibullCanopySTR>"

        //A, B, and C for fraction participating
        << "<di_mdaReproFracA>"
        << "<di_mdarfaVal species=\"Species_1\">10000</di_mdarfaVal>"
        << "<di_mdarfaVal species=\"Species_2\">10000</di_mdarfaVal>"
        << "<di_mdarfaVal species=\"Species_4\">10000</di_mdarfaVal>"
        << "</di_mdaReproFracA>"
        << "<di_mdaReproFracB>"
        << "<di_mdarfbVal species=\"Species_1\">1</di_mdarfbVal>"
        << "<di_mdarfbVal species=\"Species_2\">1</di_mdarfbVal>"
        << "<di_mdarfbVal species=\"Species_4\">1</di_mdarfbVal>"
        << "</di_mdaReproFracB>"
        << "<di_mdaReproFracC>"
        << "<di_mdarfcVal species=\"Species_1\">1</di_mdarfcVal>"
        << "<di_mdarfcVal species=\"Species_2\">1</di_mdarfcVal>"
        << "<di_mdarfcVal species=\"Species_4\">1</di_mdarfcVal>"
        << "</di_mdaReproFracC>"

        //Autocorrelation factor for rho
        << "<di_mdaRhoACF>"
        << "<di_mdaraVal species=\"Species_1\">2</di_mdaraVal>"
        << "<di_mdaraVal species=\"Species_2\">1</di_mdaraVal>"
        << "<di_mdaraVal species=\"Species_4\">1</di_mdaraVal>"
        << "</di_mdaRhoACF>"

        //Standard deviation for noise for rho
        << "<di_mdaRhoNoiseSD>"
        << "<di_mdarnsdVal species=\"Species_1\">0</di_mdarnsdVal>"
        << "<di_mdarnsdVal species=\"Species_2\">0</di_mdarnsdVal>"
        << "<di_mdarnsdVal species=\"Species_4\">0</di_mdarnsdVal>"
        << "</di_mdaRhoNoiseSD>"

        //Slope and intercept of the linear function of DBH for individual
        //probability of reproducting
        << "<di_mdaPRA>"
        << "<di_mdapraVal species=\"Species_1\">100</di_mdapraVal>"
        << "<di_mdapraVal species=\"Species_2\">100</di_mdapraVal>"
        << "<di_mdapraVal species=\"Species_4\">100</di_mdapraVal>"
        << "</di_mdaPRA>"
        << "<di_mdaPRB>"
        << "<di_mdaprbVal species=\"Species_1\">0.004</di_mdaprbVal>"
        << "<di_mdaprbVal species=\"Species_2\">0.004</di_mdaprbVal>"
        << "<di_mdaprbVal species=\"Species_4\">0.004</di_mdaprbVal>"
        << "</di_mdaPRB>"

        //Seed producer score standard deviation
        << "<di_mdaSPSSD>"
        << "<di_mdaspssdVal species=\"Species_1\">0.1</di_mdaspssdVal>"
        << "<di_mdaspssdVal species=\"Species_2\">0.1</di_mdaspssdVal>"
        << "<di_mdaspssdVal species=\"Species_4\">0.1</di_mdaspssdVal>"
        << "</di_mdaSPSSD>"

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
        << "</MastingDisperseAutocorrelation1>"
        << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteMastingDisperseAutocorrelationXMLFile3()
/////////////////////////////////////////////////////////////////////////////
const char* WriteMastingDisperseAutocorrelationXMLFile3()
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
        << "<randomSeed>10</randomSeed>"
        << "<yearsPerTimestep>1</yearsPerTimestep>"
        << "<plot_lenX>200.0</plot_lenX>"
        << "<plot_lenY>200.0</plot_lenY>"
        << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
        << "<plot_temp_C>12.88171785</plot_temp_C>"
        << "<plot_latitude>55.37</plot_latitude>"
        << "</plot>";

    WriteMastingDisperseAutocorrelationTrees(oOut);

    oOut << "<behaviorList>"
        << "<behavior>"
        << "<behaviorName>MastingDisperseAutocorrelation</behaviorName>"
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

    WriteMastingDisperseAutocorrelationAllometry(oOut);

    oOut << "<GeneralDisperse>"
        << "<di_seedDistributionMethod>0</di_seedDistributionMethod>"
        << "</GeneralDisperse>"
        << "<MastingDisperseAutocorrelation1>"
        << "<di_minDbhForReproduction>"
        << "<di_mdfrVal species=\"Species_1\">10.0</di_mdfrVal>"
        << "<di_mdfrVal species=\"Species_2\">10.0</di_mdfrVal>"
        << "<di_mdfrVal species=\"Species_3\">10.0</di_mdfrVal>"
        << "<di_mdfrVal species=\"Species_4\">10.0</di_mdfrVal>"
        << "</di_minDbhForReproduction>"

        //Mast timeseries
        << "<di_mdaMastTS>"
        << "<di_mdaMTS ts=\"1\">0.2</di_mdaMTS>"
        << "<di_mdaMTS ts=\"2\">1</di_mdaMTS>"
        << "<di_mdaMTS ts=\"3\">1</di_mdaMTS>"
        << "<di_mdaMTS ts=\"4\">1</di_mdaMTS>"
        << "<di_mdaMTS ts=\"5\">1</di_mdaMTS>"
        << "</di_mdaMastTS>"


        //Maximum DBH for size effects
        << "<di_maxDbhForSizeEffect>"
        << "<di_mdfseVal species=\"Species_1\">100</di_mdfseVal>"
        << "<di_mdfseVal species=\"Species_2\">100</di_mdfseVal>"
        << "<di_mdfseVal species=\"Species_4\">100</di_mdfseVal>"
        << "</di_maxDbhForSizeEffect>"

        //Beta
        << "<di_weibullCanopyBeta>"
        << "<di_wcbVal species=\"Species_1\">1</di_wcbVal>"
        << "<di_wcbVal species=\"Species_2\">0.5</di_wcbVal>"
        << "<di_wcbVal species=\"Species_4\">2</di_wcbVal>"
        << "</di_weibullCanopyBeta>"

        //Mean STR
        << "<di_weibullCanopySTR>"
        << "<di_wcsVal species=\"Species_1\">1000</di_wcsVal>"
        << "<di_wcsVal species=\"Species_2\">744</di_wcsVal>"
        << "<di_wcsVal species=\"Species_4\">10</di_wcsVal>"
        << "</di_weibullCanopySTR>"

        //A, B, and C for fraction participating
        << "<di_mdaReproFracA>"
        << "<di_mdarfaVal species=\"Species_1\">10000</di_mdarfaVal>"
        << "<di_mdarfaVal species=\"Species_2\">0.15</di_mdarfaVal>"
        << "<di_mdarfaVal species=\"Species_4\">0.1</di_mdarfaVal>"
        << "</di_mdaReproFracA>"
        << "<di_mdaReproFracB>"
        << "<di_mdarfbVal species=\"Species_1\">1</di_mdarfbVal>"
        << "<di_mdarfbVal species=\"Species_2\">-3</di_mdarfbVal>"
        << "<di_mdarfbVal species=\"Species_4\">-2</di_mdarfbVal>"
        << "</di_mdaReproFracB>"
        << "<di_mdaReproFracC>"
        << "<di_mdarfcVal species=\"Species_1\">1</di_mdarfcVal>"
        << "<di_mdarfcVal species=\"Species_2\">1</di_mdarfcVal>"
        << "<di_mdarfcVal species=\"Species_4\">1</di_mdarfcVal>"
        << "</di_mdaReproFracC>"

        //Autocorrelation factor for rho
        << "<di_mdaRhoACF>"
        << "<di_mdaraVal species=\"Species_1\">2</di_mdaraVal>"
        << "<di_mdaraVal species=\"Species_2\">1</di_mdaraVal>"
        << "<di_mdaraVal species=\"Species_4\">1</di_mdaraVal>"
        << "</di_mdaRhoACF>"

        //Standard deviation for noise for rho
        << "<di_mdaRhoNoiseSD>"
        << "<di_mdarnsdVal species=\"Species_1\">0</di_mdarnsdVal>"
        << "<di_mdarnsdVal species=\"Species_2\">0</di_mdarnsdVal>"
        << "<di_mdarnsdVal species=\"Species_4\">0</di_mdarnsdVal>"
        << "</di_mdaRhoNoiseSD>"

        //Slope and intercept of the linear function of DBH for individual
        //probability of reproducting
        << "<di_mdaPRA>"
        << "<di_mdapraVal species=\"Species_1\">0.75</di_mdapraVal>"
        << "<di_mdapraVal species=\"Species_2\">100</di_mdapraVal>"
        << "<di_mdapraVal species=\"Species_4\">0.75</di_mdapraVal>"
        << "</di_mdaPRA>"
        << "<di_mdaPRB>"
        << "<di_mdaprbVal species=\"Species_1\">0.004</di_mdaprbVal>"
        << "<di_mdaprbVal species=\"Species_2\">0.004</di_mdaprbVal>"
        << "<di_mdaprbVal species=\"Species_4\">0.004</di_mdaprbVal>"
        << "</di_mdaPRB>"

        //Seed producer score standard deviation
        << "<di_mdaSPSSD>"
        << "<di_mdaspssdVal species=\"Species_1\">0.1</di_mdaspssdVal>"
        << "<di_mdaspssdVal species=\"Species_2\">0.1</di_mdaspssdVal>"
        << "<di_mdaspssdVal species=\"Species_4\">0.1</di_mdaspssdVal>"
        << "</di_mdaSPSSD>"

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
        << "</MastingDisperseAutocorrelation1>"
        << "</paramFile>";

    oOut.close();

    return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteMastingDisperseAutocorrelationXMLFile4()
/////////////////////////////////////////////////////////////////////////////
const char* WriteMastingDisperseAutocorrelationXMLFile4()
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
      << "<randomSeed>5</randomSeed>"
      << "<yearsPerTimestep>1</yearsPerTimestep>"
      << "<plot_lenX>200.0</plot_lenX>"
      << "<plot_lenY>200.0</plot_lenY>"
      << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
      << "<plot_temp_C>12.88171785</plot_temp_C>"
      << "<plot_latitude>55.37</plot_latitude>"
      << "</plot>";

  WriteMastingDisperseAutocorrelationTrees(oOut);

  oOut << "<behaviorList>"
      << "<behavior>"
      << "<behaviorName>MastingDisperseAutocorrelation</behaviorName>"
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

  WriteMastingDisperseAutocorrelationAllometry(oOut);

  oOut << "<GeneralDisperse>"
      << "<di_seedDistributionMethod>0</di_seedDistributionMethod>"
      << "</GeneralDisperse>"
      << "<MastingDisperseAutocorrelation1>"
      << "<di_minDbhForReproduction>"
      << "<di_mdfrVal species=\"Species_1\">10.0</di_mdfrVal>"
      << "<di_mdfrVal species=\"Species_2\">10.0</di_mdfrVal>"
      << "</di_minDbhForReproduction>"

      //Maximum DBH for size effects
      << "<di_maxDbhForSizeEffect>"
      << "<di_mdfseVal species=\"Species_1\">100</di_mdfseVal>"
      << "<di_mdfseVal species=\"Species_2\">100</di_mdfseVal>"
      << "</di_maxDbhForSizeEffect>"

      //Beta
      << "<di_weibullCanopyBeta>"
      << "<di_wcbVal species=\"Species_1\">1</di_wcbVal>"
      << "<di_wcbVal species=\"Species_2\">1</di_wcbVal>"
      << "</di_weibullCanopyBeta>"

      //Mean STR
      << "<di_weibullCanopySTR>"
      << "<di_wcsVal species=\"Species_1\">100</di_wcsVal>"
      << "<di_wcsVal species=\"Species_2\">100</di_wcsVal>"
      << "</di_weibullCanopySTR>"

      //A, B, and C for fraction participating
      << "<di_mdaReproFracA>"
      << "<di_mdarfaVal species=\"Species_1\">10000</di_mdarfaVal>"
      << "<di_mdarfaVal species=\"Species_2\">10000</di_mdarfaVal>"
      << "</di_mdaReproFracA>"
      << "<di_mdaReproFracB>"
      << "<di_mdarfbVal species=\"Species_1\">1</di_mdarfbVal>"
      << "<di_mdarfbVal species=\"Species_2\">1</di_mdarfbVal>"
      << "</di_mdaReproFracB>"
      << "<di_mdaReproFracC>"
      << "<di_mdarfcVal species=\"Species_1\">1</di_mdarfcVal>"
      << "<di_mdarfcVal species=\"Species_2\">1</di_mdarfcVal>"
      << "</di_mdaReproFracC>"

      //Autocorrelation factor for rho
      << "<di_mdaRhoACF>"
      << "<di_mdaraVal species=\"Species_1\">2</di_mdaraVal>"
      << "<di_mdaraVal species=\"Species_2\">2</di_mdaraVal>"
      << "</di_mdaRhoACF>"

      //Standard deviation for noise for rho
      << "<di_mdaRhoNoiseSD>"
      << "<di_mdarnsdVal species=\"Species_1\">0</di_mdarnsdVal>"
      << "<di_mdarnsdVal species=\"Species_2\">0</di_mdarnsdVal>"
      << "</di_mdaRhoNoiseSD>"

      //Slope and intercept of the linear function of DBH for individual
      //probability of reproducting
      << "<di_mdaPRA>"
      << "<di_mdapraVal species=\"Species_1\">100</di_mdapraVal>"
      << "<di_mdapraVal species=\"Species_2\">100</di_mdapraVal>"
            << "</di_mdaPRA>"
      << "<di_mdaPRB>"
      << "<di_mdaprbVal species=\"Species_1\">0.004</di_mdaprbVal>"
      << "<di_mdaprbVal species=\"Species_2\">0.004</di_mdaprbVal>"
            << "</di_mdaPRB>"

      //Seed producer score standard deviation
      << "<di_mdaSPSSD>"
      << "<di_mdaspssdVal species=\"Species_1\">0.1</di_mdaspssdVal>"
      << "<di_mdaspssdVal species=\"Species_2\">0.1</di_mdaspssdVal>"
      << "</di_mdaSPSSD>"

      << "<di_canopyFunction>"
      << "<di_cfVal species=\"Species_1\">0</di_cfVal>"
      << "<di_cfVal species=\"Species_2\">0</di_cfVal>"
      << "</di_canopyFunction>"
      << "<di_weibullCanopyDispersal>"
      << "<di_wcdVal species=\"Species_1\">1.76E-04</di_wcdVal>"
      << "<di_wcdVal species=\"Species_2\">1.76E-04</di_wcdVal>"
      << "</di_weibullCanopyDispersal>"
      << "<di_weibullCanopyTheta>"
      << "<di_wctVal species=\"Species_1\">3</di_wctVal>"
      << "<di_wctVal species=\"Species_2\">3</di_wctVal>"
      << "</di_weibullCanopyTheta>"
      << "</MastingDisperseAutocorrelation1>"
      << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteMastingDisperseAutocorrelationTrees()
/////////////////////////////////////////////////////////////////////////////
void WriteMastingDisperseAutocorrelationTrees(std::fstream &oOut) {

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
// WriteMastingDisperseAutocorrelationAllometry()
/////////////////////////////////////////////////////////////////////////////
void WriteMastingDisperseAutocorrelationAllometry(std::fstream &oOut) {

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
// WriteMastingDisperseAutocorrelationTreesForError()
/////////////////////////////////////////////////////////////////////////////
void WriteMastingDisperseAutocorrelationTreesForError(std::fstream &oOut) {

  oOut << "<trees>"
      << "<tr_speciesList>"
      << "<tr_species speciesName=\"Species_1\"/>"
      << "<tr_species speciesName=\"Species_2\"/>"
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
      << "</trees>";
}

/////////////////////////////////////////////////////////////////////////////
// WriteMastingDisperseAutocorrelationAllometryForError()
/////////////////////////////////////////////////////////////////////////////
void WriteMastingDisperseAutocorrelationAllometryForError(std::fstream &oOut) {

  oOut << "<allometry>"
      << "<tr_whatAdultHeightDiam>"
      << "<tr_wahdVal species=\"Species_1\">0</tr_wahdVal>"
      << "<tr_wahdVal species=\"Species_2\">0</tr_wahdVal>"
      << "</tr_whatAdultHeightDiam>"
      << "<tr_whatSaplingHeightDiam>"
      << "<tr_wsahdVal species=\"Species_1\">0</tr_wsahdVal>"
      << "<tr_wsahdVal species=\"Species_2\">0</tr_wsahdVal>"
      << "</tr_whatSaplingHeightDiam>"
      << "<tr_whatSeedlingHeightDiam>"
      << "<tr_wsehdVal species=\"Species_1\">0</tr_wsehdVal>"
      << "<tr_wsehdVal species=\"Species_2\">0</tr_wsehdVal>"
      << "</tr_whatSeedlingHeightDiam>"
      << "<tr_whatAdultCrownRadDiam>"
      << "<tr_wacrdVal species=\"Species_1\">0</tr_wacrdVal>"
      << "<tr_wacrdVal species=\"Species_2\">0</tr_wacrdVal>"
      << "</tr_whatAdultCrownRadDiam>"
      << "<tr_whatSaplingCrownRadDiam>"
      << "<tr_wscrdVal species=\"Species_1\">0</tr_wscrdVal>"
      << "<tr_wscrdVal species=\"Species_2\">0</tr_wscrdVal>"
      << "</tr_whatSaplingCrownRadDiam>"
      << "<tr_whatAdultCrownHeightHeight>"
      << "<tr_wachhVal species=\"Species_1\">0</tr_wachhVal>"
      << "<tr_wachhVal species=\"Species_2\">0</tr_wachhVal>"
      << "</tr_whatAdultCrownHeightHeight>"
      << "<tr_whatSaplingCrownHeightHeight>"
      << "<tr_wschhVal species=\"Species_1\">0</tr_wschhVal>"
      << "<tr_wschhVal species=\"Species_2\">0</tr_wschhVal>"
      << "</tr_whatSaplingCrownHeightHeight>"
      << "<tr_canopyHeight>"
      << "<tr_chVal species=\"Species_1\">39.48</tr_chVal>"
      << "<tr_chVal species=\"Species_2\">39.54</tr_chVal>"
      << "</tr_canopyHeight>"
      << "<tr_stdAsympCrownRad>"
      << "<tr_sacrVal species=\"Species_1\">0.0549</tr_sacrVal>"
      << "<tr_sacrVal species=\"Species_2\">0.0614</tr_sacrVal>"
      << "</tr_stdAsympCrownRad>"
      << "<tr_stdCrownRadExp>"
      << "<tr_screVal species=\"Species_1\">1.0</tr_screVal>"
      << "<tr_screVal species=\"Species_2\">1.0</tr_screVal>"
      << "</tr_stdCrownRadExp>"
      << "<tr_stdMaxCrownRad>"
      << "<tr_smcrVal species=\"Species_1\">10</tr_smcrVal>"
      << "<tr_smcrVal species=\"Species_2\">10</tr_smcrVal>"
      << "</tr_stdMaxCrownRad>"
      << "<tr_stdAsympCrownHt>"
      << "<tr_sachVal species=\"Species_1\">0.389</tr_sachVal>"
      << "<tr_sachVal species=\"Species_2\">0.368</tr_sachVal>"
      << "</tr_stdAsympCrownHt>"
      << "<tr_stdCrownHtExp>"
      << "<tr_scheVal species=\"Species_1\">1.0</tr_scheVal>"
      << "<tr_scheVal species=\"Species_2\">1.0</tr_scheVal>"
      << "</tr_stdCrownHtExp>"
      << "<tr_conversionDiam10ToDBH>"
      << "<tr_cdtdVal species=\"Species_1\">0.8008</tr_cdtdVal>"
      << "<tr_cdtdVal species=\"Species_2\">0.5944</tr_cdtdVal>"
      << "</tr_conversionDiam10ToDBH>"
      << "<tr_interceptDiam10ToDBH>"
      << "<tr_idtdVal species=\"Species_1\">0.0</tr_idtdVal>"
      << "<tr_idtdVal species=\"Species_2\">0.0</tr_idtdVal>"
      << "</tr_interceptDiam10ToDBH>"
      << "<tr_slopeOfAsymHeight>"
      << "<tr_soahVal species=\"Species_1\">0.0299</tr_soahVal>"
      << "<tr_soahVal species=\"Species_2\">0.0241</tr_soahVal>"
      << "</tr_slopeOfAsymHeight>"
      << "<tr_slopeOfHeight-Diam10>"
      << "<tr_sohdVal species=\"Species_1\">0.03418</tr_sohdVal>"
      << "<tr_sohdVal species=\"Species_2\">0.0269</tr_sohdVal>"
      << "</tr_slopeOfHeight-Diam10>"
      << "</allometry>";
}


/////////////////////////////////////////////////////////////////////////////
// WriteMastingDisperseAutocorrelationXMLErrorFile1()
/////////////////////////////////////////////////////////////////////////////
const char* WriteMastingDisperseAutocorrelationXMLErrorFile1()
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
        << "<yearsPerTimestep>1</yearsPerTimestep>"
        << "<plot_lenX>200.0</plot_lenX>"
        << "<plot_lenY>200.0</plot_lenY>"
        << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
        << "<plot_temp_C>12.88171785</plot_temp_C>"
        << "<plot_latitude>55.37</plot_latitude>"
        << "</plot>";

    WriteMastingDisperseAutocorrelationTreesForError(oOut);

    oOut << "<behaviorList>"
        << "<behavior>"
        << "<behaviorName>MastingDisperseAutocorrelation</behaviorName>"
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

    WriteMastingDisperseAutocorrelationAllometryForError(oOut);

    oOut << "<GeneralDisperse>"
        << "<di_seedDistributionMethod>0</di_seedDistributionMethod>"
        << "</GeneralDisperse>"
        << "<MastingDisperseAutocorrelation1>"
        << "<di_minDbhForReproduction>"
        << "<di_mdfrVal species=\"Species_1\">10.0</di_mdfrVal>"
        << "<di_mdfrVal species=\"Species_2\">10.0</di_mdfrVal>"
        << "</di_minDbhForReproduction>"

        //Maximum DBH for size effects
        << "<di_maxDbhForSizeEffect>"
        << "<di_mdfseVal species=\"Species_1\">100</di_mdfseVal>"
        << "<di_mdfseVal species=\"Species_2\">100</di_mdfseVal>"
        << "</di_maxDbhForSizeEffect>"

        //Beta
        << "<di_weibullCanopyBeta>"
        << "<di_wcbVal species=\"Species_1\">1</di_wcbVal>"
        << "<di_wcbVal species=\"Species_2\">1</di_wcbVal>"
        << "</di_weibullCanopyBeta>"

        //Mean STR
        << "<di_weibullCanopySTR>"
        << "<di_wcsVal species=\"Species_1\">1000</di_wcsVal>"
        << "<di_wcsVal species=\"Species_2\">1000</di_wcsVal>"
        << "</di_weibullCanopySTR>"

        //A, B, and C for fraction participating
        << "<di_mdaReproFracA>"
        << "<di_mdarfaVal species=\"Species_1\">1</di_mdarfaVal>"
        << "<di_mdarfaVal species=\"Species_2\">1</di_mdarfaVal>"
        << "</di_mdaReproFracA>"
        << "<di_mdaReproFracB>"
        << "<di_mdarfbVal species=\"Species_1\">1</di_mdarfbVal>"
        << "<di_mdarfbVal species=\"Species_2\">1</di_mdarfbVal>"
        << "</di_mdaReproFracB>"
        << "<di_mdaReproFracC>"
        << "<di_mdarfcVal species=\"Species_1\">0</di_mdarfcVal>"
        << "<di_mdarfcVal species=\"Species_2\">-1</di_mdarfcVal>"
        << "</di_mdaReproFracC>"

        //Autocorrelation factor for rho
        << "<di_mdaRhoACF>"
        << "<di_mdaraVal species=\"Species_1\">1</di_mdaraVal>"
        << "<di_mdaraVal species=\"Species_2\">1</di_mdaraVal>"
        << "</di_mdaRhoACF>"

        //Standard deviation for noise for rho
        << "<di_mdaRhoNoiseSD>"
        << "<di_mdarnsdVal species=\"Species_1\">0</di_mdarnsdVal>"
        << "<di_mdarnsdVal species=\"Species_2\">0</di_mdarnsdVal>"
        << "</di_mdaRhoNoiseSD>"

        //Slope and intercept of the linear function of DBH for individual
        //probability of reproducting
        << "<di_mdaPRA>"
        << "<di_mdapraVal species=\"Species_1\">0.75</di_mdapraVal>"
        << "<di_mdapraVal species=\"Species_2\">0.75</di_mdapraVal>"
        << "</di_mdaPRA>"
        << "<di_mdaPRB>"
        << "<di_mdaprbVal species=\"Species_1\">0.004</di_mdaprbVal>"
        << "<di_mdaprbVal species=\"Species_2\">0.004</di_mdaprbVal>"
        << "</di_mdaPRB>"

        //Seed producer score standard deviation
        << "<di_mdaSPSSD>"
        << "<di_mdaspssdVal species=\"Species_1\">0.1</di_mdaspssdVal>"
        << "<di_mdaspssdVal species=\"Species_2\">0.1</di_mdaspssdVal>"
        << "</di_mdaSPSSD>"

        << "<di_canopyFunction>"
        << "<di_cfVal species=\"Species_1\">0</di_cfVal>"
        << "<di_cfVal species=\"Species_2\">0</di_cfVal>"
        << "</di_canopyFunction>"
        << "<di_weibullCanopyDispersal>"
        << "<di_wcdVal species=\"Species_1\">1.76E-04</di_wcdVal>"
        << "<di_wcdVal species=\"Species_2\">1.82E-04</di_wcdVal>"
        << "</di_weibullCanopyDispersal>"
        << "<di_weibullCanopyTheta>"
        << "<di_wctVal species=\"Species_1\">3</di_wctVal>"
        << "<di_wctVal species=\"Species_2\">3</di_wctVal>"
        << "</di_weibullCanopyTheta>"
        << "</MastingDisperseAutocorrelation1>"
        << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteMastingDisperseAutocorrelationXMLErrorFile2()
/////////////////////////////////////////////////////////////////////////////
const char* WriteMastingDisperseAutocorrelationXMLErrorFile2()
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
      << "<yearsPerTimestep>1</yearsPerTimestep>"
      << "<plot_lenX>200.0</plot_lenX>"
      << "<plot_lenY>200.0</plot_lenY>"
      << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
      << "<plot_temp_C>12.88171785</plot_temp_C>"
      << "<plot_latitude>55.37</plot_latitude>"
      << "</plot>";

  WriteMastingDisperseAutocorrelationTreesForError(oOut);

  oOut << "<behaviorList>"
      << "<behavior>"
      << "<behaviorName>MastingDisperseAutocorrelation</behaviorName>"
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

  WriteMastingDisperseAutocorrelationAllometryForError(oOut);

  oOut << "<GeneralDisperse>"
      << "<di_seedDistributionMethod>0</di_seedDistributionMethod>"
      << "</GeneralDisperse>"
      << "<MastingDisperseAutocorrelation1>"
      << "<di_minDbhForReproduction>"
      << "<di_mdfrVal species=\"Species_1\">10.0</di_mdfrVal>"
      << "<di_mdfrVal species=\"Species_2\">10.0</di_mdfrVal>"
      << "</di_minDbhForReproduction>"

      //Mast timeseries
      << "<di_mdaMastTS>"
      << "<di_mdaMTS ts=\"1\">0</di_mdaMTS>"
      << "<di_mdaMTS ts=\"2\">1.74</di_mdaMTS>"
      << "<di_mdaMTS ts=\"3\">1</di_mdaMTS>"
      << "<di_mdaMTS ts=\"4\">0.25</di_mdaMTS>"
      << "<di_mdaMTS ts=\"5\">0.5</di_mdaMTS>"
      << "</di_mdaMastTS>"

      //Maximum DBH for size effects
      << "<di_maxDbhForSizeEffect>"
      << "<di_mdfseVal species=\"Species_1\">100</di_mdfseVal>"
      << "<di_mdfseVal species=\"Species_2\">100</di_mdfseVal>"
      << "</di_maxDbhForSizeEffect>"

      //Beta
      << "<di_weibullCanopyBeta>"
      << "<di_wcbVal species=\"Species_1\">1</di_wcbVal>"
      << "<di_wcbVal species=\"Species_2\">1</di_wcbVal>"
      << "</di_weibullCanopyBeta>"

      //Mean STR
      << "<di_weibullCanopySTR>"
      << "<di_wcsVal species=\"Species_1\">1000</di_wcsVal>"
      << "<di_wcsVal species=\"Species_2\">1000</di_wcsVal>"
      << "</di_weibullCanopySTR>"

      //A, B, and C for fraction participating
      << "<di_mdaReproFracA>"
      << "<di_mdarfaVal species=\"Species_1\">1</di_mdarfaVal>"
      << "<di_mdarfaVal species=\"Species_2\">1</di_mdarfaVal>"
      << "</di_mdaReproFracA>"
      << "<di_mdaReproFracB>"
      << "<di_mdarfbVal species=\"Species_1\">1</di_mdarfbVal>"
      << "<di_mdarfbVal species=\"Species_2\">1</di_mdarfbVal>"
      << "</di_mdaReproFracB>"
      << "<di_mdaReproFracC>"
      << "<di_mdarfcVal species=\"Species_1\">0</di_mdarfcVal>"
      << "<di_mdarfcVal species=\"Species_2\">1</di_mdarfcVal>"
      << "</di_mdaReproFracC>"

      //Autocorrelation factor for rho
      << "<di_mdaRhoACF>"
      << "<di_mdaraVal species=\"Species_1\">1</di_mdaraVal>"
      << "<di_mdaraVal species=\"Species_2\">1</di_mdaraVal>"
      << "</di_mdaRhoACF>"

      //Standard deviation for noise for rho
      << "<di_mdaRhoNoiseSD>"
      << "<di_mdarnsdVal species=\"Species_1\">0</di_mdarnsdVal>"
      << "<di_mdarnsdVal species=\"Species_2\">0</di_mdarnsdVal>"
      << "</di_mdaRhoNoiseSD>"

      //Slope and intercept of the linear function of DBH for individual
      //probability of reproducting
      << "<di_mdaPRA>"
      << "<di_mdapraVal species=\"Species_1\">0.75</di_mdapraVal>"
      << "<di_mdapraVal species=\"Species_2\">0.75</di_mdapraVal>"
      << "</di_mdaPRA>"
      << "<di_mdaPRB>"
      << "<di_mdaprbVal species=\"Species_1\">0.004</di_mdaprbVal>"
      << "<di_mdaprbVal species=\"Species_2\">0.004</di_mdaprbVal>"
      << "</di_mdaPRB>"

      //Seed producer score standard deviation
      << "<di_mdaSPSSD>"
      << "<di_mdaspssdVal species=\"Species_1\">0.1</di_mdaspssdVal>"
      << "<di_mdaspssdVal species=\"Species_2\">0.1</di_mdaspssdVal>"
      << "</di_mdaSPSSD>"

      << "<di_canopyFunction>"
      << "<di_cfVal species=\"Species_1\">0</di_cfVal>"
      << "<di_cfVal species=\"Species_2\">0</di_cfVal>"
      << "</di_canopyFunction>"
      << "<di_weibullCanopyDispersal>"
      << "<di_wcdVal species=\"Species_1\">1.76E-04</di_wcdVal>"
      << "<di_wcdVal species=\"Species_2\">1.82E-04</di_wcdVal>"
      << "</di_weibullCanopyDispersal>"
      << "<di_weibullCanopyTheta>"
      << "<di_wctVal species=\"Species_1\">3</di_wctVal>"
      << "<di_wctVal species=\"Species_2\">3</di_wctVal>"
      << "</di_weibullCanopyTheta>"
      << "</MastingDisperseAutocorrelation1>"
      << "</paramFile>";

  oOut.close();

  return cFileString;
}


/////////////////////////////////////////////////////////////////////////////
// WriteMastingDisperseAutocorrelationXMLErrorFile3()
/////////////////////////////////////////////////////////////////////////////
const char* WriteMastingDisperseAutocorrelationXMLErrorFile3()
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
        << "<yearsPerTimestep>1</yearsPerTimestep>"
        << "<plot_lenX>200.0</plot_lenX>"
        << "<plot_lenY>200.0</plot_lenY>"
        << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
        << "<plot_temp_C>12.88171785</plot_temp_C>"
        << "<plot_latitude>55.37</plot_latitude>"
        << "</plot>";

    WriteMastingDisperseAutocorrelationTreesForError(oOut);

    oOut << "<behaviorList>"
        << "<behavior>"
        << "<behaviorName>MastingDisperseAutocorrelation</behaviorName>"
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

    WriteMastingDisperseAutocorrelationAllometryForError(oOut);

    oOut << "<GeneralDisperse>"
        << "<di_seedDistributionMethod>0</di_seedDistributionMethod>"
        << "</GeneralDisperse>"
        << "<MastingDisperseAutocorrelation1>"
        << "<di_minDbhForReproduction>"
        << "<di_mdfrVal species=\"Species_1\">10.0</di_mdfrVal>"
        << "<di_mdfrVal species=\"Species_2\">10.0</di_mdfrVal>"
        << "</di_minDbhForReproduction>"

        //Maximum DBH for size effects
        << "<di_maxDbhForSizeEffect>"
        << "<di_mdfseVal species=\"Species_1\">100</di_mdfseVal>"
        << "<di_mdfseVal species=\"Species_2\">100</di_mdfseVal>"
        << "</di_maxDbhForSizeEffect>"

        //Beta
        << "<di_weibullCanopyBeta>"
        << "<di_wcbVal species=\"Species_1\">1</di_wcbVal>"
        << "<di_wcbVal species=\"Species_2\">1</di_wcbVal>"
        << "</di_weibullCanopyBeta>"

        //Mean STR
        << "<di_weibullCanopySTR>"
        << "<di_wcsVal species=\"Species_1\">1000</di_wcsVal>"
        << "<di_wcsVal species=\"Species_2\">1000</di_wcsVal>"
        << "</di_weibullCanopySTR>"

        //A, B, and C for fraction participating
        << "<di_mdaReproFracA>"
        << "<di_mdarfaVal species=\"Species_1\">1</di_mdarfaVal>"
        << "<di_mdarfaVal species=\"Species_2\">1</di_mdarfaVal>"
        << "</di_mdaReproFracA>"
        << "<di_mdaReproFracB>"
        << "<di_mdarfbVal species=\"Species_1\">1</di_mdarfbVal>"
        << "<di_mdarfbVal species=\"Species_2\">1</di_mdarfbVal>"
        << "</di_mdaReproFracB>"
        << "<di_mdaReproFracC>"
        << "<di_mdarfcVal species=\"Species_1\">0</di_mdarfcVal>"
        << "<di_mdarfcVal species=\"Species_2\">1</di_mdarfcVal>"
        << "</di_mdaReproFracC>"

        //Autocorrelation factor for rho
        << "<di_mdaRhoACF>"
        << "<di_mdaraVal species=\"Species_1\">1</di_mdaraVal>"
        << "<di_mdaraVal species=\"Species_2\">1</di_mdaraVal>"
        << "</di_mdaRhoACF>"

        //Standard deviation for noise for rho
        << "<di_mdaRhoNoiseSD>"
        << "<di_mdarnsdVal species=\"Species_1\">0</di_mdarnsdVal>"
        << "<di_mdarnsdVal species=\"Species_2\">-5</di_mdarnsdVal>"
        << "</di_mdaRhoNoiseSD>"

        //Slope and intercept of the linear function of DBH for individual
        //probability of reproducting
        << "<di_mdaPRA>"
        << "<di_mdapraVal species=\"Species_1\">0.75</di_mdapraVal>"
        << "<di_mdapraVal species=\"Species_2\">0.75</di_mdapraVal>"
        << "</di_mdaPRA>"
        << "<di_mdaPRB>"
        << "<di_mdaprbVal species=\"Species_1\">0.004</di_mdaprbVal>"
        << "<di_mdaprbVal species=\"Species_2\">0.004</di_mdaprbVal>"
        << "</di_mdaPRB>"

        //Seed producer score standard deviation
        << "<di_mdaSPSSD>"
        << "<di_mdaspssdVal species=\"Species_1\">0.1</di_mdaspssdVal>"
        << "<di_mdaspssdVal species=\"Species_2\">0.1</di_mdaspssdVal>"
        << "</di_mdaSPSSD>"

        << "<di_canopyFunction>"
        << "<di_cfVal species=\"Species_1\">0</di_cfVal>"
        << "<di_cfVal species=\"Species_2\">0</di_cfVal>"
        << "</di_canopyFunction>"
        << "<di_weibullCanopyDispersal>"
        << "<di_wcdVal species=\"Species_1\">1.76E-04</di_wcdVal>"
        << "<di_wcdVal species=\"Species_2\">1.82E-04</di_wcdVal>"
        << "</di_weibullCanopyDispersal>"
        << "<di_weibullCanopyTheta>"
        << "<di_wctVal species=\"Species_1\">3</di_wctVal>"
        << "<di_wctVal species=\"Species_2\">3</di_wctVal>"
        << "</di_weibullCanopyTheta>"
        << "</MastingDisperseAutocorrelation1>"
        << "</paramFile>";

    oOut.close();

    return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteMastingDisperseAutocorrelationXMLErrorFile4()
/////////////////////////////////////////////////////////////////////////////
const char* WriteMastingDisperseAutocorrelationXMLErrorFile4()
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
        << "<yearsPerTimestep>1</yearsPerTimestep>"
        << "<plot_lenX>200.0</plot_lenX>"
        << "<plot_lenY>200.0</plot_lenY>"
        << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
        << "<plot_temp_C>12.88171785</plot_temp_C>"
        << "<plot_latitude>55.37</plot_latitude>"
        << "</plot>";

    WriteMastingDisperseAutocorrelationTreesForError(oOut);

    oOut << "<behaviorList>"
        << "<behavior>"
        << "<behaviorName>MastingDisperseAutocorrelation</behaviorName>"
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

    WriteMastingDisperseAutocorrelationAllometryForError(oOut);

    oOut << "<GeneralDisperse>"
        << "<di_seedDistributionMethod>0</di_seedDistributionMethod>"
        << "</GeneralDisperse>"
        << "<MastingDisperseAutocorrelation1>"
        << "<di_minDbhForReproduction>"
        << "<di_mdfrVal species=\"Species_1\">10.0</di_mdfrVal>"
        << "<di_mdfrVal species=\"Species_2\">10.0</di_mdfrVal>"
        << "</di_minDbhForReproduction>"

        //Maximum DBH for size effects
        << "<di_maxDbhForSizeEffect>"
        << "<di_mdfseVal species=\"Species_1\">9</di_mdfseVal>"
        << "<di_mdfseVal species=\"Species_2\">100</di_mdfseVal>"
        << "</di_maxDbhForSizeEffect>"

        //Beta
        << "<di_weibullCanopyBeta>"
        << "<di_wcbVal species=\"Species_1\">1</di_wcbVal>"
        << "<di_wcbVal species=\"Species_2\">1</di_wcbVal>"
        << "</di_weibullCanopyBeta>"

        //Mean STR
        << "<di_weibullCanopySTR>"
        << "<di_wcsVal species=\"Species_1\">1000</di_wcsVal>"
        << "<di_wcsVal species=\"Species_2\">1000</di_wcsVal>"
        << "</di_weibullCanopySTR>"

        //A, B, and C for fraction participating
        << "<di_mdaReproFracA>"
        << "<di_mdarfaVal species=\"Species_1\">1</di_mdarfaVal>"
        << "<di_mdarfaVal species=\"Species_2\">1</di_mdarfaVal>"
        << "</di_mdaReproFracA>"
        << "<di_mdaReproFracB>"
        << "<di_mdarfbVal species=\"Species_1\">1</di_mdarfbVal>"
        << "<di_mdarfbVal species=\"Species_2\">1</di_mdarfbVal>"
        << "</di_mdaReproFracB>"
        << "<di_mdaReproFracC>"
        << "<di_mdarfcVal species=\"Species_1\">0</di_mdarfcVal>"
        << "<di_mdarfcVal species=\"Species_2\">1</di_mdarfcVal>"
        << "</di_mdaReproFracC>"

        //Autocorrelation factor for rho
        << "<di_mdaRhoACF>"
        << "<di_mdaraVal species=\"Species_1\">1</di_mdaraVal>"
        << "<di_mdaraVal species=\"Species_2\">1</di_mdaraVal>"
        << "</di_mdaRhoACF>"

        //Standard deviation for noise for rho
        << "<di_mdaRhoNoiseSD>"
        << "<di_mdarnsdVal species=\"Species_1\">0</di_mdarnsdVal>"
        << "<di_mdarnsdVal species=\"Species_2\">0</di_mdarnsdVal>"
        << "</di_mdaRhoNoiseSD>"

        //Slope and intercept of the linear function of DBH for individual
        //probability of reproducting
        << "<di_mdaPRA>"
        << "<di_mdapraVal species=\"Species_1\">0.75</di_mdapraVal>"
        << "<di_mdapraVal species=\"Species_2\">0.75</di_mdapraVal>"
        << "</di_mdaPRA>"
        << "<di_mdaPRB>"
        << "<di_mdaprbVal species=\"Species_1\">0.004</di_mdaprbVal>"
        << "<di_mdaprbVal species=\"Species_2\">0.004</di_mdaprbVal>"
        << "</di_mdaPRB>"

        //Seed producer score standard deviation
        << "<di_mdaSPSSD>"
        << "<di_mdaspssdVal species=\"Species_1\">0.1</di_mdaspssdVal>"
        << "<di_mdaspssdVal species=\"Species_2\">0.1</di_mdaspssdVal>"
        << "</di_mdaSPSSD>"

        << "<di_canopyFunction>"
        << "<di_cfVal species=\"Species_1\">0</di_cfVal>"
        << "<di_cfVal species=\"Species_2\">0</di_cfVal>"
        << "</di_canopyFunction>"
        << "<di_weibullCanopyDispersal>"
        << "<di_wcdVal species=\"Species_1\">1.76E-04</di_wcdVal>"
        << "<di_wcdVal species=\"Species_2\">1.82E-04</di_wcdVal>"
        << "</di_weibullCanopyDispersal>"
        << "<di_weibullCanopyTheta>"
        << "<di_wctVal species=\"Species_1\">3</di_wctVal>"
        << "<di_wctVal species=\"Species_2\">3</di_wctVal>"
        << "</di_weibullCanopyTheta>"
        << "</MastingDisperseAutocorrelation1>"
        << "</paramFile>";

    oOut.close();

    return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteMastingDisperseAutocorrelationXMLErrorFile5()
/////////////////////////////////////////////////////////////////////////////
const char* WriteMastingDisperseAutocorrelationXMLErrorFile5()
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
        << "<yearsPerTimestep>1</yearsPerTimestep>"
        << "<plot_lenX>200.0</plot_lenX>"
        << "<plot_lenY>200.0</plot_lenY>"
        << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
        << "<plot_temp_C>12.88171785</plot_temp_C>"
        << "<plot_latitude>55.37</plot_latitude>"
        << "</plot>";

    WriteMastingDisperseAutocorrelationTreesForError(oOut);

    oOut << "<behaviorList>"
        << "<behavior>"
        << "<behaviorName>MastingDisperseAutocorrelation</behaviorName>"
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

    WriteMastingDisperseAutocorrelationAllometryForError(oOut);

    oOut << "<GeneralDisperse>"
        << "<di_seedDistributionMethod>0</di_seedDistributionMethod>"
        << "</GeneralDisperse>"
        << "<MastingDisperseAutocorrelation1>"
        << "<di_minDbhForReproduction>"
        << "<di_mdfrVal species=\"Species_1\">10.0</di_mdfrVal>"
        << "<di_mdfrVal species=\"Species_2\">10.0</di_mdfrVal>"
        << "</di_minDbhForReproduction>"

        //Maximum DBH for size effects
        << "<di_maxDbhForSizeEffect>"
        << "<di_mdfseVal species=\"Species_1\">100</di_mdfseVal>"
        << "<di_mdfseVal species=\"Species_2\">100</di_mdfseVal>"
        << "</di_maxDbhForSizeEffect>"

        //Beta
        << "<di_weibullCanopyBeta>"
        << "<di_wcbVal species=\"Species_1\">1</di_wcbVal>"
        << "<di_wcbVal species=\"Species_2\">1</di_wcbVal>"
        << "</di_weibullCanopyBeta>"

        //Mean STR
        << "<di_weibullCanopySTR>"
        << "<di_wcsVal species=\"Species_1\">1000</di_wcsVal>"
        << "<di_wcsVal species=\"Species_2\">1000</di_wcsVal>"
        << "</di_weibullCanopySTR>"

        //A, B, and C for fraction participating
        << "<di_mdaReproFracA>"
        << "<di_mdarfaVal species=\"Species_1\">0</di_mdarfaVal>"
        << "<di_mdarfaVal species=\"Species_2\">1</di_mdarfaVal>"
        << "</di_mdaReproFracA>"
        << "<di_mdaReproFracB>"
        << "<di_mdarfbVal species=\"Species_1\">1</di_mdarfbVal>"
        << "<di_mdarfbVal species=\"Species_2\">1</di_mdarfbVal>"
        << "</di_mdaReproFracB>"
        << "<di_mdaReproFracC>"
        << "<di_mdarfcVal species=\"Species_1\">0</di_mdarfcVal>"
        << "<di_mdarfcVal species=\"Species_2\">1</di_mdarfcVal>"
        << "</di_mdaReproFracC>"

        //Autocorrelation factor for rho
        << "<di_mdaRhoACF>"
        << "<di_mdaraVal species=\"Species_1\">1</di_mdaraVal>"
        << "<di_mdaraVal species=\"Species_2\">1</di_mdaraVal>"
        << "</di_mdaRhoACF>"

        //Standard deviation for noise for rho
        << "<di_mdaRhoNoiseSD>"
        << "<di_mdarnsdVal species=\"Species_1\">0</di_mdarnsdVal>"
        << "<di_mdarnsdVal species=\"Species_2\">0</di_mdarnsdVal>"
        << "</di_mdaRhoNoiseSD>"

        //Slope and intercept of the linear function of DBH for individual
        //probability of reproducting
        << "<di_mdaPRA>"
        << "<di_mdapraVal species=\"Species_1\">0.75</di_mdapraVal>"
        << "<di_mdapraVal species=\"Species_2\">0.75</di_mdapraVal>"
        << "</di_mdaPRA>"
        << "<di_mdaPRB>"
        << "<di_mdaprbVal species=\"Species_1\">0.004</di_mdaprbVal>"
        << "<di_mdaprbVal species=\"Species_2\">0.004</di_mdaprbVal>"
        << "</di_mdaPRB>"

        //Seed producer score standard deviation
        << "<di_mdaSPSSD>"
        << "<di_mdaspssdVal species=\"Species_1\">0.1</di_mdaspssdVal>"
        << "<di_mdaspssdVal species=\"Species_2\">0.1</di_mdaspssdVal>"
        << "</di_mdaSPSSD>"

        << "<di_canopyFunction>"
        << "<di_cfVal species=\"Species_1\">0</di_cfVal>"
        << "<di_cfVal species=\"Species_2\">0</di_cfVal>"
        << "</di_canopyFunction>"
        << "<di_weibullCanopyDispersal>"
        << "<di_wcdVal species=\"Species_1\">1.76E-04</di_wcdVal>"
        << "<di_wcdVal species=\"Species_2\">1.82E-04</di_wcdVal>"
        << "</di_weibullCanopyDispersal>"
        << "<di_weibullCanopyTheta>"
        << "<di_wctVal species=\"Species_1\">3</di_wctVal>"
        << "<di_wctVal species=\"Species_2\">3</di_wctVal>"
        << "</di_weibullCanopyTheta>"
        << "</MastingDisperseAutocorrelation1>"
        << "</paramFile>";

    oOut.close();

    return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
//WriteMastingDisperseAutocorrelationXMLErrorFile6()
/////////////////////////////////////////////////////////////////////////////
const char* WriteMastingDisperseAutocorrelationXMLErrorFile6()
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
        << "<yearsPerTimestep>1</yearsPerTimestep>"
        << "<plot_lenX>200.0</plot_lenX>"
        << "<plot_lenY>200.0</plot_lenY>"
        << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
        << "<plot_temp_C>12.88171785</plot_temp_C>"
        << "<plot_latitude>55.37</plot_latitude>"
        << "</plot>";

    WriteMastingDisperseAutocorrelationTreesForError(oOut);

    oOut << "<behaviorList>"
        << "<behavior>"
        << "<behaviorName>MastingDisperseAutocorrelation</behaviorName>"
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

    WriteMastingDisperseAutocorrelationAllometryForError(oOut);

    oOut << "<GeneralDisperse>"
        << "<di_seedDistributionMethod>0</di_seedDistributionMethod>"
        << "</GeneralDisperse>"
        << "<MastingDisperseAutocorrelation1>"
        << "<di_minDbhForReproduction>"
        << "<di_mdfrVal species=\"Species_1\">10.0</di_mdfrVal>"
        << "<di_mdfrVal species=\"Species_2\">10.0</di_mdfrVal>"
        << "</di_minDbhForReproduction>"

        //Maximum DBH for size effects
        << "<di_maxDbhForSizeEffect>"
        << "<di_mdfseVal species=\"Species_1\">100</di_mdfseVal>"
        << "<di_mdfseVal species=\"Species_2\">100</di_mdfseVal>"
        << "</di_maxDbhForSizeEffect>"

        //Beta
        << "<di_weibullCanopyBeta>"
        << "<di_wcbVal species=\"Species_1\">1</di_wcbVal>"
        << "<di_wcbVal species=\"Species_2\">1</di_wcbVal>"
        << "</di_weibullCanopyBeta>"

        //Mean STR
        << "<di_weibullCanopySTR>"
        << "<di_wcsVal species=\"Species_1\">1000</di_wcsVal>"
        << "<di_wcsVal species=\"Species_2\">1000</di_wcsVal>"
        << "</di_weibullCanopySTR>"

        //A, B, and C for fraction participating
        << "<di_mdaReproFracA>"
        << "<di_mdarfaVal species=\"Species_1\">1</di_mdarfaVal>"
        << "<di_mdarfaVal species=\"Species_2\">1</di_mdarfaVal>"
        << "</di_mdaReproFracA>"
        << "<di_mdaReproFracB>"
        << "<di_mdarfbVal species=\"Species_1\">1</di_mdarfbVal>"
        << "<di_mdarfbVal species=\"Species_2\">1</di_mdarfbVal>"
        << "</di_mdaReproFracB>"
        << "<di_mdaReproFracC>"
        << "<di_mdarfcVal species=\"Species_1\">0</di_mdarfcVal>"
        << "<di_mdarfcVal species=\"Species_2\">1</di_mdarfcVal>"
        << "</di_mdaReproFracC>"

        //Autocorrelation factor for rho
        << "<di_mdaRhoACF>"
        << "<di_mdaraVal species=\"Species_1\">1</di_mdaraVal>"
        << "<di_mdaraVal species=\"Species_2\">1</di_mdaraVal>"
        << "</di_mdaRhoACF>"

        //Standard deviation for noise for rho
        << "<di_mdaRhoNoiseSD>"
        << "<di_mdarnsdVal species=\"Species_1\">0</di_mdarnsdVal>"
        << "<di_mdarnsdVal species=\"Species_2\">0</di_mdarnsdVal>"
        << "</di_mdaRhoNoiseSD>"

        //Slope and intercept of the linear function of DBH for individual
        //probability of reproducting
        << "<di_mdaPRA>"
        << "<di_mdapraVal species=\"Species_1\">0.75</di_mdapraVal>"
        << "<di_mdapraVal species=\"Species_2\">0.75</di_mdapraVal>"
        << "</di_mdaPRA>"
        << "<di_mdaPRB>"
        << "<di_mdaprbVal species=\"Species_1\">0.004</di_mdaprbVal>"
        << "<di_mdaprbVal species=\"Species_2\">0.004</di_mdaprbVal>"
        << "</di_mdaPRB>"

        //Seed producer score standard deviation
        << "<di_mdaSPSSD>"
        << "<di_mdaspssdVal species=\"Species_1\">0.1</di_mdaspssdVal>"
        << "<di_mdaspssdVal species=\"Species_2\">-0.1</di_mdaspssdVal>"
        << "</di_mdaSPSSD>"

        << "<di_canopyFunction>"
        << "<di_cfVal species=\"Species_1\">0</di_cfVal>"
        << "<di_cfVal species=\"Species_2\">0</di_cfVal>"
        << "</di_canopyFunction>"
        << "<di_weibullCanopyDispersal>"
        << "<di_wcdVal species=\"Species_1\">1.76E-04</di_wcdVal>"
        << "<di_wcdVal species=\"Species_2\">1.82E-04</di_wcdVal>"
        << "</di_weibullCanopyDispersal>"
        << "<di_weibullCanopyTheta>"
        << "<di_wctVal species=\"Species_1\">3</di_wctVal>"
        << "<di_wctVal species=\"Species_2\">3</di_wctVal>"
        << "</di_weibullCanopyTheta>"
        << "</MastingDisperseAutocorrelation1>"
        << "</paramFile>";

    oOut.close();

    return cFileString;
}

