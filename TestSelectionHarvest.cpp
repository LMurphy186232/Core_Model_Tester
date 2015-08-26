//---------------------------------------------------------------------------
// TestSelectionHarvest.cpp
//---------------------------------------------------------------------------
#include "TestSelectionHarvest.h"
#include <gtest/gtest.h>
#include "TreePopulation.h"
#include "SimManager.h"
#include "Grid.h"
#include "ModelMath.h"
#include <fstream>
#include <math.h>

/////////////////////////////////////////////////////////////////////////////
// DoSelectionHarvestRun1()
// Performs the first harvest run. This run has the following characteristics:
// Harvest # |TS |Cut Ranges |Species |Cut Type |Target BA (abs) |Grids
//-----------|---|-----------|--------|---------|----------------|------------
// 1         |1  |0 - 100    |1       |AbsBA    |6               |Whole plot
// The harvest will be performed.  Then the remaining trees are checked to make
// sure the proper ones were left alone.
/////////////////////////////////////////////////////////////////////////////
TEST(SelectionHarvest, DoSelectionHarvestRun1) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    clTreePopulation * p_oPop;
    clTreeSearch *p_oAllTrees;
    clTree *p_oTree;
    float fTemp, fSp0BA, fSp1BA, fSp2BA, fSp3BA, fSp4BA, fSp5BA, fSp6BA, fSp7BA, fSp8BA;

    p_oSimManager->ReadFile(WriteSelectionHarvestXMLFile1());
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );

    //*********************************************
    // Timestep 1
    //*********************************************
    //Run the first timestep
    p_oSimManager->RunSim(1);

    /*Total up the basal area for species 0-8 - we're expecting:
    0 -> 0.667349
    1 -> 0.670889
    2 -> 0.672075
    3 -> 0.657290
    4 -> 0.657124
    5 -> 0.670281
    6 -> 0.658721
    7 -> 0.679859
    8 -> 0.666411
    These values are on a per hectare basis, so for our 4 hectare plot,
    multiply these values by 4*/

    fSp0BA = 0; fSp1BA = 0; fSp2BA = 0; fSp3BA = 0; fSp4BA = 0; fSp5BA = 0; fSp6BA = 0; fSp7BA = 0; fSp8BA = 0;
    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {

      if (p_oTree->GetSpecies() == 0) {
        p_oTree->GetValue(p_oPop->GetDbhCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTemp);
        fSp0BA += clModelMath::CalculateBasalArea(fTemp);

      }
      else if (p_oTree->GetSpecies() == 1) {
        p_oTree->GetValue(p_oPop->GetDbhCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTemp);
        fSp1BA += clModelMath::CalculateBasalArea(fTemp);

      }
      else if (p_oTree->GetSpecies() == 2) {
        p_oTree->GetValue(p_oPop->GetDbhCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTemp);
        fSp2BA += clModelMath::CalculateBasalArea(fTemp);

      }
      else if (p_oTree->GetSpecies() == 3) {
        p_oTree->GetValue(p_oPop->GetDbhCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTemp);
        fSp3BA += clModelMath::CalculateBasalArea(fTemp);

      }
      else if (p_oTree->GetSpecies() == 4) {
        p_oTree->GetValue(p_oPop->GetDbhCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTemp);
        fSp4BA += clModelMath::CalculateBasalArea(fTemp);

      }
      else if (p_oTree->GetSpecies() == 5) {
        p_oTree->GetValue(p_oPop->GetDbhCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTemp);
        fSp5BA += clModelMath::CalculateBasalArea(fTemp);

      }
      else if (p_oTree->GetSpecies() == 6) {
        p_oTree->GetValue(p_oPop->GetDbhCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTemp);
        fSp6BA += clModelMath::CalculateBasalArea(fTemp);

      }
      else if (p_oTree->GetSpecies() == 7) {
        p_oTree->GetValue(p_oPop->GetDbhCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTemp);
        fSp7BA += clModelMath::CalculateBasalArea(fTemp);

      }
      else if (p_oTree->GetSpecies() == 8) {
        p_oTree->GetValue(p_oPop->GetDbhCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTemp);
        fSp8BA += clModelMath::CalculateBasalArea(fTemp);

      }

      p_oTree = p_oAllTrees->NextTree();
    }

    EXPECT_LT(fabs(fSp0BA - 2.669399682)/2.669399682, 0.01);
    EXPECT_LT(fabs(fSp1BA - 2.683527792)/2.683527792, 0.01);
    EXPECT_LT(fabs(fSp2BA - 2.688304923)/2.688304923, 0.01);
    EXPECT_LT(fabs(fSp3BA - 2.629149815)/2.629149815, 0.01);
    EXPECT_LT(fabs(fSp4BA - 2.628489148)/2.628489148, 0.01);
    EXPECT_LT(fabs(fSp5BA - 2.681139227)/2.681139227, 0.01);
    EXPECT_LT(fabs(fSp6BA - 2.634892536)/2.634892536, 0.01);
    EXPECT_LT(fabs(fSp7BA - 2.719457914)/2.719457914, 0.01);
    EXPECT_LT(fabs(fSp8BA - 2.665638962)/2.665638962, 0.01);
    delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

/////////////////////////////////////////////////////////////////////////////
// DoSelectionHarvestRun2()
// Performs the second harvest run. This run has the following characteristics:
// Harvest # |TS |Cut Ranges |Species |Cut Type |Target BA (abs) |Grids
//-----------|---|-----------|--------|---------|----------------|------------
// 1         |1  |0 - 100    |1       |AbsBA    |6.0             |Whole plot
// The harvest will be performed. Then the remaining trees are checked to make
// sure the proper ones were left alone.
/////////////////////////////////////////////////////////////////////////////
TEST(SelectionHarvest, DoSelectionHarvestRun2) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    clTreePopulation * p_oPop;
    clTreeSearch *p_oAllTrees;
    clTree *p_oTree;
    float fTemp, fSp0BA, fSp1BA, fSp2BA, fSp3BA, fSp4BA, fSp5BA, fSp6BA, fSp7BA, fSp8BA;

    p_oSimManager->ReadFile( WriteSelectionHarvestXMLFile2() );
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );

    //*********************************************
    // Timestep 1
    //*********************************************
    //Run the first timestep
    p_oSimManager->RunSim(1);

    /*Total up the basal area for species 0-8 - we're expecting:
    0 -> 0.667349
    1 -> 0.670889
    2 -> 0.672075
    3 -> 0.657290
    4 -> 0.657124
    5 -> 0.670281
    6 -> 0.658721
    7 -> 0.679859
    8 -> 0.666411*/

    fSp0BA = 0; fSp1BA = 0; fSp2BA = 0; fSp3BA = 0; fSp4BA = 0; fSp5BA = 0; fSp6BA = 0; fSp7BA = 0; fSp8BA = 0;
    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {

      if (p_oTree->GetSpecies() == 0) {
        p_oTree->GetValue(p_oPop->GetDbhCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTemp);
        fSp0BA += clModelMath::CalculateBasalArea(fTemp);

      }
      else if (p_oTree->GetSpecies() == 1) {
        p_oTree->GetValue(p_oPop->GetDbhCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTemp);
        fSp1BA += clModelMath::CalculateBasalArea(fTemp);

      }
      else if (p_oTree->GetSpecies() == 2) {
        p_oTree->GetValue(p_oPop->GetDbhCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTemp);
        fSp2BA += clModelMath::CalculateBasalArea(fTemp);

      }
      else if (p_oTree->GetSpecies() == 3) {
        p_oTree->GetValue(p_oPop->GetDbhCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTemp);
        fSp3BA += clModelMath::CalculateBasalArea(fTemp);

      }
      else if (p_oTree->GetSpecies() == 4) {
        p_oTree->GetValue(p_oPop->GetDbhCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTemp);
        fSp4BA += clModelMath::CalculateBasalArea(fTemp);

      }
      else if (p_oTree->GetSpecies() == 5) {
        p_oTree->GetValue(p_oPop->GetDbhCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTemp);
        fSp5BA += clModelMath::CalculateBasalArea(fTemp);

      }
      else if (p_oTree->GetSpecies() == 6) {
        p_oTree->GetValue(p_oPop->GetDbhCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTemp);
        fSp6BA += clModelMath::CalculateBasalArea(fTemp);

      }
      else if (p_oTree->GetSpecies() == 7) {
        p_oTree->GetValue(p_oPop->GetDbhCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTemp);
        fSp7BA += clModelMath::CalculateBasalArea(fTemp);

      }
      else if (p_oTree->GetSpecies() == 8) {
        p_oTree->GetValue(p_oPop->GetDbhCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTemp);
        fSp8BA += clModelMath::CalculateBasalArea(fTemp);

      }

      p_oTree = p_oAllTrees->NextTree();
    }

    EXPECT_LT(fabs(fSp0BA - 2.669399682)/2.669399682, 0.01);
    EXPECT_LT(fabs(fSp1BA - 2.683527792)/2.683527792, 0.01);
    EXPECT_LT(fabs(fSp2BA - 2.688304923)/2.688304923, 0.01);
    EXPECT_LT(fabs(fSp3BA - 2.629149815)/2.629149815, 0.01);
    EXPECT_LT(fabs(fSp4BA - 2.628489148)/2.628489148, 0.01);
    EXPECT_LT(fabs(fSp5BA - 2.681139227)/2.681139227, 0.01);
    EXPECT_LT(fabs(fSp6BA - 2.634892536)/2.634892536, 0.01);
    EXPECT_LT(fabs(fSp7BA - 2.719457914)/2.719457914, 0.01);
    EXPECT_LT(fabs(fSp8BA - 2.665638962)/2.665638962, 0.01);
    delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

/////////////////////////////////////////////////////////////////////////////
// DoSelectionHarvestRun3()
// Performs the third harvest run. This run has the following characteristics:
// Harvest # |TS |Cut Ranges |Species |Cut Type |Target BA (abs) |Grids
//-----------|---|-----------|--------|---------|----------------|------------
// 1         |1  |0 - 100    |1       |AbsBA    |-5              |Whole plot
// The harvest will not be performed.  An error message will be thrown.
/////////////////////////////////////////////////////////////////////////////
TEST(SelectionHarvest, DoSelectionHarvestRun3) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try
  {
    p_oSimManager->ReadFile(WriteSelectionHarvestXMLFile3());
    //*********************************************
    // Timestep 1
    //*********************************************
    //Run the first timestep

    p_oSimManager->RunSim(1);


    FAIL() << "TestSelectionHarvest error processing didn't catch error for WriteSelectionHarvestXMLErrorFile3.";

  }
  catch (modelErr& err)
  {
    if (err.sFunction.compare("clSelectionHarvest::GetData") != 0)
    {
      FAIL() << "TestSelectionHarvest error processing caught wrong error for WriteSelectionHarvestXMLErrorFile3.";
    }
    ;
  }
  delete p_oSimManager;
}

/////////////////////////////////////////////////////////////////////////////
// DoSelectionHarvestRun4()
// Performs the fourth harvest run. This run has the following characteristics:
// Harvest # |TS |Cut Ranges |Species |Cut Type |Target BA (abs) |Grids
//-----------|---|-----------|--------|---------|----------------|------------
// 1         |1  |0-100      |1       |AbsBA    |500             |Whole plot
// The harvest will not be performed. The run will continue.
/////////////////////////////////////////////////////////////////////////////
TEST(SelectionHarvest, DoSelectionHarvestRun4) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    clTreePopulation * p_oPop;
    clTreeSearch *p_oAllTrees;
    clTree *p_oTree;
    float fTemp, fSp0BA, fSp1BA, fSp2BA, fSp3BA, fSp4BA, fSp5BA, fSp6BA, fSp7BA, fSp8BA;

    p_oSimManager->ReadFile( WriteSelectionHarvestXMLFile4() );
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );

    //*********************************************
    // Timestep 1
    //*********************************************
    //Run the first timestep
    p_oSimManager->RunSim(1);

    /*Total up the basal area for species 0-8 - we're expecting:
  0 -> 52.52595042
  1 -> 52.80458235
  2 -> 52.89789588
  3 -> 51.73424761
  4 -> 51.7211388
  5 -> 52.75669056
  6 -> 51.84685909
  7 -> 53.51059508
  8 -> 52.45211713
     */

    fSp0BA = 0; fSp1BA = 0; fSp2BA = 0; fSp3BA = 0; fSp4BA = 0; fSp5BA = 0; fSp6BA = 0; fSp7BA = 0; fSp8BA = 0;
    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {

      if (p_oTree->GetSpecies() == 0) {
        p_oTree->GetValue(p_oPop->GetDbhCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTemp);
        fSp0BA += clModelMath::CalculateBasalArea(fTemp);

      }
      else if (p_oTree->GetSpecies() == 1) {
        p_oTree->GetValue(p_oPop->GetDbhCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTemp);
        fSp1BA += clModelMath::CalculateBasalArea(fTemp);

      }
      else if (p_oTree->GetSpecies() == 2) {
        p_oTree->GetValue(p_oPop->GetDbhCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTemp);
        fSp2BA += clModelMath::CalculateBasalArea(fTemp);

      }
      else if (p_oTree->GetSpecies() == 3) {
        p_oTree->GetValue(p_oPop->GetDbhCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTemp);
        fSp3BA += clModelMath::CalculateBasalArea(fTemp);

      }
      else if (p_oTree->GetSpecies() == 4) {
        p_oTree->GetValue(p_oPop->GetDbhCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTemp);
        fSp4BA += clModelMath::CalculateBasalArea(fTemp);

      }
      else if (p_oTree->GetSpecies() == 5) {
        p_oTree->GetValue(p_oPop->GetDbhCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTemp);
        fSp5BA += clModelMath::CalculateBasalArea(fTemp);

      }
      else if (p_oTree->GetSpecies() == 6) {
        p_oTree->GetValue(p_oPop->GetDbhCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTemp);
        fSp6BA += clModelMath::CalculateBasalArea(fTemp);

      }
      else if (p_oTree->GetSpecies() == 7) {
        p_oTree->GetValue(p_oPop->GetDbhCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTemp);
        fSp7BA += clModelMath::CalculateBasalArea(fTemp);

      }
      else if (p_oTree->GetSpecies() == 8) {
        p_oTree->GetValue(p_oPop->GetDbhCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTemp);
        fSp8BA += clModelMath::CalculateBasalArea(fTemp);

      }

      p_oTree = p_oAllTrees->NextTree();
    }

    EXPECT_LT(fabs(fSp0BA - 52.52595042)/52.52595042, 0.01);
    EXPECT_LT(fabs(fSp1BA - 52.80458235)/52.80458235, 0.01);
    EXPECT_LT(fabs(fSp2BA - 52.89789588)/52.89789588, 0.01);
    EXPECT_LT(fabs(fSp3BA - 51.73424761)/51.73424761, 0.01);
    EXPECT_LT(fabs(fSp4BA - 51.7211388)/51.7211388, 0.01);
    EXPECT_LT(fabs(fSp5BA - 52.75669056)/52.75669056, 0.01);
    EXPECT_LT(fabs(fSp6BA - 51.84685909)/51.84685909, 0.01);
    EXPECT_LT(fabs(fSp7BA - 53.51059508)/53.51059508, 0.01);
    EXPECT_LT(fabs(fSp8BA - 52.45211713)/52.45211713, 0.01);
    delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

/////////////////////////////////////////////////////////////////////////////
// DoSelectionHarvestRun5()
// Performs the fifth harvest run.  This run has the following characteristics:
// Harvest # |TS |Cut Ranges |Species |Cut Type |Target BA (abs) |Grids
//-----------|---|-----------|--------|---------|----------------|------------
// 1         |1  |0-100      |1       |AbsBA                     |Whole plot
// The harvest will not be performed.  An error message will be thrown.
/////////////////////////////////////////////////////////////////////////////
/*TEST(SelectionHarvest, DoSelectionHarvestRun5) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try
  {
    p_oSimManager->ReadFile(WriteSelectionHarvestXMLFile5());
    //Run the first timestep

    p_oSimManager->RunSim(1);

    FAIL() << "TestSelectionHarvest error processing didn't catch error for WriteSelectionHarvestXMLErrorFile5.";
  }
  catch (modelErr& err)
  {
    if (err.sFunction.compare("clSelectionHarvest::GetData") != 0)
    {
      FAIL() << "TestSelectionHarvest error processing caught wrong error for WriteSelectionHarvestXMLErrorFile5.";
    }
    ;
  }
  delete p_oSimManager;
}*/

/////////////////////////////////////////////////////////////////////////////
// DoSelectionHarvestRun6()
// Performs the sixth harvest run. This run has the following characteristics:
// Harvest # |TS |Cut Ranges |Species |Cut Type |Target BA (abs) |Grids
//-----------|---|-----------|--------|---------|----------------|------------
//1          |1  |0-100      |1       |AbsBA    |"bad"           |Whole plot
// The harvest will not be performed.  An error message will be thrown.
/////////////////////////////////////////////////////////////////////////////
TEST(SelectionHarvest, DoSelectionHarvestRun6) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try
  {
    p_oSimManager->ReadFile(WriteSelectionHarvestXMLFile6());
    //*********************************************
    // Timestep 1
    //*********************************************
    //Run the first timestep
    p_oSimManager->RunSim(1);

    FAIL() << "TestSelectionHarvest error processing didn't catch error for WriteSelectionHarvestXMLErrorFile6.";
  }
  catch (modelErr& err)
  {
    if (err.sFunction.compare("FillSingleValue(float)") != 0)
    {
      FAIL() << "TestSelectionHarvest error processing caught wrong error for WriteSelectionHarvestXMLErrorFile6.";
    }
    ;
  }
  delete p_oSimManager;
}


/////////////////////////////////////////////////////////////////////////////
// DoSelectionHarvestRun7()
// Performs the seventh harvest run.  This run has the following characteristics:
// Harvest # |TS |Cut Ranges |Species |Cut Type |Target BA (abs) |Grids
//-----------|---|-----------|--------|---------|----------------|------------
// 1         |1  |0-20, 15-40|1       |AbsBA    |6, 6            | Whole plot
// The harvest will not be performed. An error message will be thrown.
/////////////////////////////////////////////////////////////////////////////
TEST(SelectionHarvest, DoSelectionHarvestRun7) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try
  {
    p_oSimManager->ReadFile(WriteSelectionHarvestXMLFile7());
    //*********************************************
    // Timestep 1
    //*********************************************
    //Run the first timestep

    p_oSimManager->RunSim(1);

    FAIL() << "TestSelectionHarvest error processing didn't catch error for WriteSelectionHarvestXMLErrorFile7.";
  }
  catch (modelErr& err)
  {
    if (err.sFunction.compare("clSelectionHarvest::GetData") != 0)
    {
      FAIL() << "TestSelectionHarvest error processing caught wrong error for WriteSelectionHarvestXMLErrorFile7.";
    }
    ;
  }
  delete p_oSimManager;
}

/////////////////////////////////////////////////////////////////////////////
// DoSelectionHarvestRun8()
// Performs the eigth harvest run.  This run has the following characteristics:
// Harvest # |TS |Cut Ranges |Species |Cut Type |Target BA (abs) |Grids
//-----------|---|-----------|--------|---------|----------------|------------
// 1         |1  |0-20, 40-21|1       |AbsBA    |6, 6            | Whole plot
// The harvest will not be performed.  An error message will be thrown.
/////////////////////////////////////////////////////////////////////////////
TEST(SelectionHarvest, DoSelectionHarvestRun8) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try
  {
    p_oSimManager->ReadFile(WriteSelectionHarvestXMLFile8());
    //*********************************************
    // Timestep 1
    //*********************************************
    //Run the first timestep

    p_oSimManager->RunSim(1);

    FAIL() << "TestSelectionHarvest error processing didn't catch error for WriteSelectionHarvestXMLErrorFile8.";
  }
  catch (modelErr& err)
  {
    if (err.sFunction.compare("clSelectionHarvest::GetData") != 0)
    {
      FAIL() << "TestSelectionHarvest error processing caught wrong error for WriteSelectionHarvestXMLErrorFile8.";
    }
    ;
  }
  delete p_oSimManager;
}


/////////////////////////////////////////////////////////////////////////////
// DoSelectionHarvestRun9()
// Performs the ninth harvest run. This run has the following characteristics:
// Harvest # |TS |Cut Ranges  |Species |Cut Type |Target BA (abs) |Grids
//-----------|---|------------|--------|---------|----------------|------------
// 1         |1  |-5-20, 21-40|1       |AbsBA    |6, 6            | Whole plot
// The harvest will not be performed.  An error message will be thrown.
/////////////////////////////////////////////////////////////////////////////
TEST(SelectionHarvest, DoSelectionHarvestRun9) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try
  {
    p_oSimManager->ReadFile(WriteSelectionHarvestXMLFile9());
    //*********************************************
    // Timestep 1
    //*********************************************
    //Run the first timestep

    p_oSimManager->RunSim(1);

    FAIL() << "TestSelectionHarvest error processing didn't catch error for WriteSelectionHarvestXMLErrorFile9.";
  }
  catch (modelErr& err)
  {
    if (err.sFunction.compare("clSelectionHarvest::GetData") != 0)
    {
      FAIL() << "TestSelectionHarvest error processing caught wrong error for WriteSelectionHarvestXMLErrorFile9.";
    }
    ;
  }
  delete p_oSimManager;
}

/////////////////////////////////////////////////////////////////////////////
// DoSelectionHarvestRun10()
// Performs the tenth harvest run.  This run has the following characteristics:
// Harvest # |TS |Cut Ranges  |Species |Cut Type |Target BA (abs) |Grids
//-----------|---|------------|--------|---------|----------------|------------
// 1         |1  |"bad", 21-40     1   AbsBA          6, 6             Whole plot
// The harvest will not be performed.  An error message will be thrown.
/////////////////////////////////////////////////////////////////////////////
TEST(SelectionHarvest, DoSelectionHarvestRun10) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try
  {
    p_oSimManager->ReadFile(WriteSelectionHarvestXMLFile10());
    //*********************************************
    // Timestep 1
    //*********************************************
    //Run the first timestep

    p_oSimManager->RunSim(1);

    FAIL() << "TestSelectionHarvest error processing didn't catch error for WriteSelectionHarvestXMLErrorFile10.";
  }
  catch (modelErr& err)
  {
    if (err.sFunction.compare("FillSingleValue(float)") != 0)
    {
      FAIL() << "TestSelectionHarvest error processing caught wrong error for WriteSelectionHarvestXMLErrorFile10.";
    }
    ;
  }
  delete p_oSimManager;
}

/////////////////////////////////////////////////////////////////////////////
// DoSelectionHarvestRun11()
// Performs the eleventh harvest run. This run has the following characteristics:
// Harvest # |TS |Cut Ranges |Species |Cut Type |Target BA (abs) |Grids
//-----------|---|-----------|--------|---------|----------------|------------
// 1         |1  |none       |1       |AbsBA    |N/A             |Whole plot
// The harvest will not be performed.  An error message will be thrown.
/////////////////////////////////////////////////////////////////////////////
/*TEST(SelectionHarvest, DoSelectionHarvestRun11) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try
  {
    p_oSimManager->ReadFile(WriteSelectionHarvestXMLFile11());
    //Run the first timestep

    p_oSimManager->RunSim(1);

    FAIL() << "TestSelectionHarvest error processing didn't catch error for WriteSelectionHarvestXMLErrorFile11.";
  }
  catch (modelErr& err)
  {
    if (err.sFunction.compare("clSelectionHarvest::GetData") != 0)
    {
      FAIL() << "TestSelectionHarvest error processing caught wrong error for WriteSelectionHarvestXMLErrorFile11.";
    }
    ;
  }
  delete p_oSimManager;
}*/

/////////////////////////////////////////////////////////////////////////////
// DoSelectionHarvestRun12()
// Performs the twelth harvest run.  This run has the following characteristics:
// Harvest # |TS |Cut Ranges |Species |Cut Type |Target BA (abs) |Grids
//-----------|---|-----------|--------|---------|----------------|------------
//1          |2  |0-100      |1       |AbsBA    |6               |Whole plot
// The harvest will be performed. The purpose of the run is to test the
// TimeSinceHarvest function. Each cell will be given an intial age of 5000
// years. They will be cut as the target BA is lower than initial BA. The
// timeSinceHarvest function will reflect this by returning the timestep length
// as the amount of time elapsed since harvest
/////////////////////////////////////////////////////////////////////////////
TEST(SelectionHarvest, DoSelectionHarvestRun12) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    p_oSimManager->ReadFile(WriteSelectionHarvestXMLFile12());

    /*I expect that a harvest will occur and thus the values in each TimeSinceHarvestGrid
     *cell should be equal to the timestep length which is 1 year.
     */

    //declare the timesinceharvest grid
    clGrid *mp_oTimeSinceHarvestGrid;
    //declare variables for number of rows, number of columns in the grid
    int iTimeValue, iNumCols, iNumRows;
    short int iTime;

    //Run the model
    p_oSimManager->RunSim(0);

    mp_oTimeSinceHarvestGrid = p_oSimManager->GetGridObject("Time Since Harvest");
    iNumCols = mp_oTimeSinceHarvestGrid->GetNumberXCells();
    iNumRows = mp_oTimeSinceHarvestGrid->GetNumberYCells();
    //get the code for the Time data member in the timesinceharvest grid
    iTime = mp_oTimeSinceHarvestGrid->GetIntDataCode("Time");


    //for each cell in the timeSinceHarvest grid get the time since harvest value
    for(int i=0; i<iNumRows; i++)
    {
      for(int j=0; j<iNumCols; j++)
      {
        //Get the time since harvest from the TimeSinceHarvest grid
        mp_oTimeSinceHarvestGrid->GetValueOfCell( i, j, iTime, &iTimeValue );

        //we expect that each time since harvest will be 1 which is the timestep length
        //this is because each cell will be harvested.
        EXPECT_LT(fabs(iTimeValue - 1)/1, 0.01);
      }
    }
    delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

/////////////////////////////////////////////////////////////////////////////
// DoSelectionHarvestRun13()
// Performs the thirteenth harvest run.  This run has the following characteristics:
// Harvest # |TS |Cut Ranges |Species |Cut Type |Target BA (abs) |Grids
//-----------|---|-----------|--------|---------|----------------|------------
// 1         |2  |0-100      |1       |AbsBA    |500             |Whole plot
// The harvest will not be performed. The purpose of the run is to test the
// TimeSinceHarvest function. Each cell will be given an intial age of 5000
// years. They will not be cut as the target BA is too high. The
// timeSinceHarvest function will reflect this by returning the initial age +
// timestep length (5000+1)
/////////////////////////////////////////////////////////////////////////////
TEST(SelectionHarvest, DoSelectionHarvestRun13) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    p_oSimManager->ReadFile(WriteSelectionHarvestXMLFile13());

    /*I expect that a harvest will occur and thus the values in each TimeSinceHarvestGrid
     *cell should be equal to the timestep length which is 1 year.
     */

    //declare the timesinceharvest grid
    clGrid *mp_oTimeSinceHarvestGrid;
    //declare variables for number of rows, number of columns in the grid
    int iTimeValue, iNumCols, iNumRows;
    short int iTime;

    //Run the model
    p_oSimManager->RunSim(0);

    mp_oTimeSinceHarvestGrid = p_oSimManager->GetGridObject("Time Since Harvest");
    iNumCols = mp_oTimeSinceHarvestGrid->GetNumberXCells();
    iNumRows = mp_oTimeSinceHarvestGrid->GetNumberYCells();
    //get the code for the Time data member in the timesinceharvest grid
    iTime = mp_oTimeSinceHarvestGrid->GetIntDataCode("Time");

    //for each cell in the timeSinceHarvest grid get the time since harvest value
    for(int i=0; i<iNumRows; i++)
    {
      for(int j=0; j<iNumCols; j++)
      {
        //Get the time since harvest from the TimeSinceHarvest grid
        mp_oTimeSinceHarvestGrid->GetValueOfCell( i, j, iTime, &iTimeValue );

        //we expect that each time since harvest will be 5001 which is the timestep length
        //plus the initial age.  this is because each cell will be not be harvested.
        EXPECT_LT(fabs(iTimeValue - 5001)/5001, 0.01);
      }
    }
    delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

/////////////////////////////////////////////////////////////////////////////
// WriteSelectionHarvestXMLFile1()
/////////////////////////////////////////////////////////////////////////////
const char* WriteSelectionHarvestXMLFile1()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  std::fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
      << "<paramFile fileCode=\"06010101\">" << "<plot>"
      << "<timesteps>1</timesteps>"
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
      << "</tr_maxSeedlingHeight>";

  oOut.close();

  WriteSelectionHarvestTreeMap(cFileString);

  oOut.open(cFileString, ios::out | ios::app);
  oOut << "</trees>"
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
      << "<behaviorName>SelectionHarvest</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>1</listPosition>"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>Harvest</behaviorName>"
      << "<version>1.0</version>"
      << "<listPosition>2</listPosition>"
      << "</behavior>"
      << "</behaviorList>"
      << "<SelectionHarvest1>"
      << "<sha_CutRange>"
      << "<sha_target_BA>6</sha_target_BA>"
      << "<sha_loDBH>0</sha_loDBH>"
      << "<sha_hiDBH>100</sha_hiDBH>"
      << "</sha_CutRange>"
      << "</SelectionHarvest1>"
      << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteSelectionHarvestXMLFile2()
/////////////////////////////////////////////////////////////////////////////
const char* WriteSelectionHarvestXMLFile2()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  std::fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
      << "<paramFile fileCode=\"06010101\">" << "<plot>"
      << "<timesteps>1</timesteps>"
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
      << "</tr_maxSeedlingHeight>";

  oOut.close();

  WriteSelectionHarvestTreeMap(cFileString);

  oOut.open(cFileString, ios::out | ios::app);
  oOut << "</trees>"
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
      << "<behaviorName>SelectionHarvest</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>1</listPosition>"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>Harvest</behaviorName>"
      << "<version>1.0</version>"
      << "<listPosition>2</listPosition>"
      << "</behavior>"
      << "</behaviorList>"
      << "<SelectionHarvest1>"
      << "<sha_CutRange>"
      << "<sha_target_BA>6.0</sha_target_BA>"
      << "<sha_loDBH>0</sha_loDBH>"
      << "<sha_hiDBH>100</sha_hiDBH>"
      << "</sha_CutRange>"
      << "</SelectionHarvest1>"
      << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteSelectionHarvestXMLFile3()
/////////////////////////////////////////////////////////////////////////////
const char* WriteSelectionHarvestXMLFile3()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  std::fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
      << "<paramFile fileCode=\"06010101\">" << "<plot>"
      << "<timesteps>1</timesteps>"
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
      << "</tr_maxSeedlingHeight>";

  oOut.close();

  WriteSelectionHarvestTreeMap(cFileString);

  oOut.open(cFileString, ios::out | ios::app);
  oOut << "</trees>"
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
      << "<behaviorName>SelectionHarvest</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>1</listPosition>"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>Harvest</behaviorName>"
      << "<version>1.0</version>"
      << "<listPosition>2</listPosition>"
      << "</behavior>"
      << "</behaviorList>"
      << "<SelectionHarvest1>"
      << "<sha_CutRange>"
      << "<sha_target_BA>-5</sha_target_BA>"
      << "<sha_loDBH>0</sha_loDBH>"
      << "<sha_hiDBH>100</sha_hiDBH>"
      << "</sha_CutRange>"
      << "</SelectionHarvest1>"
      << "</paramFile>";

  oOut.close();

  return cFileString;
}


/////////////////////////////////////////////////////////////////////////////
// WriteSelectionHarvestXMLFile4()
/////////////////////////////////////////////////////////////////////////////
const char* WriteSelectionHarvestXMLFile4()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  std::fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
      << "<paramFile fileCode=\"06010101\">" << "<plot>"
      << "<timesteps>1</timesteps>"
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
      << "</tr_maxSeedlingHeight>";

  oOut.close();

  WriteSelectionHarvestTreeMap(cFileString);

  oOut.open(cFileString, ios::out | ios::app);
  oOut << "</trees>"
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
      << "<behaviorName>SelectionHarvest</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>1</listPosition>"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>Harvest</behaviorName>"
      << "<version>1.0</version>"
      << "<listPosition>2</listPosition>"
      << "</behavior>"
      << "</behaviorList>"
      << "<SelectionHarvest1>"
      << "<sha_CutRange>"
      << "<sha_target_BA>1000</sha_target_BA>"
      << "<sha_loDBH>0</sha_loDBH>"
      << "<sha_hiDBH>100</sha_hiDBH>"
      << "</sha_CutRange>"
      << "</SelectionHarvest1>"
      << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteSelectionHarvestXMLFile5()
/////////////////////////////////////////////////////////////////////////////
const char* WriteSelectionHarvestXMLFile5()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  std::fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
      << "<paramFile fileCode=\"06010101\">" << "<plot>"
      << "<timesteps>1</timesteps>"
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
      << "</tr_maxSeedlingHeight>";

  oOut.close();

  WriteSelectionHarvestTreeMap(cFileString);

  oOut.open(cFileString, ios::out | ios::app);
  oOut << "</trees>"
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
      << "<behaviorName>SelectionHarvest</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>1</listPosition>"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>Harvest</behaviorName>"
      << "<version>1.0</version>"
      << "<listPosition>2</listPosition>"
      << "</behavior>"
      << "</behaviorList>"
      << "<SelectionHarvest1>"
      << "<sha_CutRange>"
      << "<sha_target_BA></sha_target_BA>"
      << "<sha_loDBH>0</sha_loDBH>"
      << "<sha_hiDBH>100</sha_hiDBH>"
      << "</sha_CutRange>"
      << "</SelectionHarvest1>"
      << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteSelectionHarvestXMLFile6()
/////////////////////////////////////////////////////////////////////////////
const char* WriteSelectionHarvestXMLFile6()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  std::fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
      << "<paramFile fileCode=\"06010101\">" << "<plot>"
      << "<timesteps>1</timesteps>"
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
      << "</tr_maxSeedlingHeight>";

  oOut.close();

  WriteSelectionHarvestTreeMap(cFileString);

  oOut.open(cFileString, ios::out | ios::app);
  oOut << "</trees>"
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
      << "<behaviorName>SelectionHarvest</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>1</listPosition>"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>Harvest</behaviorName>"
      << "<version>1.0</version>"
      << "<listPosition>2</listPosition>"
      << "</behavior>"
      << "</behaviorList>"
      << "<SelectionHarvest1>"
      << "<sha_CutRange>"
      << "<sha_target_BA>bad</sha_target_BA>"
      << "<sha_loDBH>0</sha_loDBH>"
      << "<sha_hiDBH>100</sha_hiDBH>"
      << "</sha_CutRange>"
      << "</SelectionHarvest1>"
      << "</paramFile>";

  oOut.close();

  return cFileString;
}


/////////////////////////////////////////////////////////////////////////////
// WriteSelectionHarvestXMLFile7()
/////////////////////////////////////////////////////////////////////////////
const char* WriteSelectionHarvestXMLFile7()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  std::fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
      << "<paramFile fileCode=\"06010101\">" << "<plot>"
      << "<timesteps>1</timesteps>"
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
      << "</tr_maxSeedlingHeight>";

  oOut.close();

  WriteSelectionHarvestTreeMap(cFileString);

  oOut.open(cFileString, ios::out | ios::app);
  oOut << "</trees>"
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
      << "<behaviorName>SelectionHarvest</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>1</listPosition>"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>Harvest</behaviorName>"
      << "<version>1.0</version>"
      << "<listPosition>2</listPosition>"
      << "</behavior>"
      << "</behaviorList>"
      << "<SelectionHarvest1>"
      << "<sha_CutRange>"
      << "<sha_target_BA>6</sha_target_BA>"
      << "<sha_loDBH>0</sha_loDBH>"
      << "<sha_hiDBH>20</sha_hiDBH>"
      << "</sha_CutRange>"
      << "<sha_CutRange>"
      << "<sha_target_BA>6</sha_target_BA>"
      << "<sha_loDBH>15</sha_loDBH>"
      << "<sha_hiDBH>100</sha_hiDBH>"
      << "</sha_CutRange>"
      << "</SelectionHarvest1>"
      << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteSelectionHarvestXMLFile8()
/////////////////////////////////////////////////////////////////////////////
const char* WriteSelectionHarvestXMLFile8()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  std::fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
      << "<paramFile fileCode=\"06010101\">" << "<plot>"
      << "<timesteps>1</timesteps>"
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
      << "</tr_maxSeedlingHeight>";

  oOut.close();

  WriteSelectionHarvestTreeMap(cFileString);

  oOut.open(cFileString, ios::out | ios::app);
  oOut << "</trees>"
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
      << "<behaviorName>SelectionHarvest</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>1</listPosition>"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>Harvest</behaviorName>"
      << "<version>1.0</version>"
      << "<listPosition>2</listPosition>"
      << "</behavior>"
      << "</behaviorList>"
      << "<SelectionHarvest1>"
      << "<sha_CutRange>"
      << "<sha_target_BA>6</sha_target_BA>"
      << "<sha_loDBH>0</sha_loDBH>"
      << "<sha_hiDBH>20</sha_hiDBH>"
      << "</sha_CutRange>"
      << "<sha_CutRange>"
      << "<sha_target_BA>6</sha_target_BA>"
      << "<sha_loDBH>100</sha_loDBH>"
      << "<sha_hiDBH>21</sha_hiDBH>"
      << "</sha_CutRange>"
      << "</SelectionHarvest1>"
      << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteSelectionHarvestXMLFile9()
/////////////////////////////////////////////////////////////////////////////
const char* WriteSelectionHarvestXMLFile9()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  std::fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
      << "<paramFile fileCode=\"06010101\">" << "<plot>"
      << "<timesteps>1</timesteps>"
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
      << "</tr_maxSeedlingHeight>";

  oOut.close();

  WriteSelectionHarvestTreeMap(cFileString);

  oOut.open(cFileString, ios::out | ios::app);
  oOut << "</trees>"
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
      << "<behaviorName>SelectionHarvest</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>1</listPosition>"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>Harvest</behaviorName>"
      << "<version>1.0</version>"
      << "<listPosition>2</listPosition>"
      << "</behavior>"
      << "</behaviorList>"
      << "<SelectionHarvest1>"
      << "<sha_CutRange>"
      << "<sha_target_BA>6</sha_target_BA>"
      << "<sha_loDBH>-5</sha_loDBH>"
      << "<sha_hiDBH>20</sha_hiDBH>"
      << "</sha_CutRange>"
      << "<sha_CutRange>"
      << "<sha_target_BA>6</sha_target_BA>"
      << "<sha_loDBH>21</sha_loDBH>"
      << "<sha_hiDBH>100</sha_hiDBH>"
      << "</sha_CutRange>"
      << "</SelectionHarvest1>"
      << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteSelectionHarvestXMLFile10()
/////////////////////////////////////////////////////////////////////////////
const char* WriteSelectionHarvestXMLFile10()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  std::fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
      << "<paramFile fileCode=\"06010101\">" << "<plot>"
      << "<timesteps>1</timesteps>"
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
      << "</tr_maxSeedlingHeight>";

  oOut.close();

  WriteSelectionHarvestTreeMap(cFileString);

  oOut.open(cFileString, ios::out | ios::app);
  oOut << "</trees>"
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
      << "<behaviorName>SelectionHarvest</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>1</listPosition>"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>Harvest</behaviorName>"
      << "<version>1.0</version>"
      << "<listPosition>2</listPosition>"
      << "</behavior>"
      << "</behaviorList>"
      << "<SelectionHarvest1>"
      << "<sha_CutRange>"
      << "<sha_target_BA>6</sha_target_BA>"
      << "<sha_loDBH>bad</sha_loDBH>"
      << "<sha_hiDBH>20</sha_hiDBH>"
      << "</sha_CutRange>"
      << "<sha_CutRange>"
      << "<sha_target_BA>6</sha_target_BA>"
      << "<sha_loDBH>21</sha_loDBH>"
      << "<sha_hiDBH>100</sha_hiDBH>"
      << "</sha_CutRange>"
      << "</SelectionHarvest1>"
      << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteSelectionHarvestXMLFile11()
/////////////////////////////////////////////////////////////////////////////
const char* WriteSelectionHarvestXMLFile11()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  std::fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
      << "<paramFile fileCode=\"06010101\">" << "<plot>"
      << "<timesteps>1</timesteps>"
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
      << "</tr_maxSeedlingHeight>";

  oOut.close();

  WriteSelectionHarvestTreeMap(cFileString);

  oOut.open(cFileString, ios::out | ios::app);
  oOut << "</trees>"
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
      << "<behaviorName>SelectionHarvest</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>1</listPosition>"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>Harvest</behaviorName>"
      << "<version>1.0</version>"
      << "<listPosition>2</listPosition>"
      << "</behavior>"
      << "</behaviorList>"
      << "<SelectionHarvest1>"
      << "<sha_CutRange>"
      << "<sha_target_BA>6</sha_target_BA>"
      << "<sha_loDBH></sha_loDBH>"
      << "<sha_hiDBH></sha_hiDBH>"
      << "</sha_CutRange>"
      << "</SelectionHarvest1>"
      << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteSelectionHarvestXMLFile12()
/////////////////////////////////////////////////////////////////////////////
const char* WriteSelectionHarvestXMLFile12()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  std::fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
      << "<paramFile fileCode=\"06010101\">" << "<plot>"
      << "<timesteps>2</timesteps>"
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
      << "</tr_maxSeedlingHeight>";

  oOut.close();

  WriteSelectionHarvestTreeMap(cFileString);

  oOut.open(cFileString, ios::out | ios::app);
  oOut << "</trees>"
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
      << "<behaviorName>SelectionHarvest</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>1</listPosition>"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>Harvest</behaviorName>"
      << "<version>1.0</version>"
      << "<listPosition>2</listPosition>"
      << "</behavior>"
      << "</behaviorList>"
      << "<SelectionHarvest1>"
      << "<sha_CutRange>"
      << "<sha_target_BA>6</sha_target_BA>"
      << "<sha_loDBH>0</sha_loDBH>"
      << "<sha_hiDBH>100</sha_hiDBH>"
      << "</sha_CutRange>"
      << "<sha_InitialAge>5000</sha_InitialAge>"
      << "</SelectionHarvest1>"
      << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteSelectionHarvestXMLFile13()
/////////////////////////////////////////////////////////////////////////////
const char* WriteSelectionHarvestXMLFile13()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  std::fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
      << "<paramFile fileCode=\"06010101\">" << "<plot>"
      << "<timesteps>2</timesteps>"
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
      << "</tr_maxSeedlingHeight>";

  oOut.close();

  WriteSelectionHarvestTreeMap(cFileString);

  oOut.open(cFileString, ios::out | ios::app);
  oOut << "</trees>"
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
      << "<behaviorName>SelectionHarvest</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>1</listPosition>"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>Harvest</behaviorName>"
      << "<version>1.0</version>"
      << "<listPosition>2</listPosition>"
      << "</behavior>"
      << "</behaviorList>"
      << "<SelectionHarvest1>"
      << "<sha_CutRange>"
      << "<sha_target_BA>500</sha_target_BA>"
      << "<sha_loDBH>0</sha_loDBH>"
      << "<sha_hiDBH>100</sha_hiDBH>"
      << "</sha_CutRange>"
      << "<sha_InitialAge>5000</sha_InitialAge>"
      << "</SelectionHarvest1>"
      << "</paramFile>";

  oOut.close();

  return cFileString;
}
