//---------------------------------------------------------------------------
// TestNCIPestGrowth.cpp
//---------------------------------------------------------------------------
#include "TestNCIPestGrowth.h"
#include <gtest/gtest.h>
#include <fstream>
#include <math.h>
#include "TreePopulation.h"
#include "SimManager.h"
#include "BehaviorBase.h"
#include "NCI/NCIEffectsList.h"

using namespace std;

////////////////////////////////////////////////////////////////////////////
// TestRun1()
////////////////////////////////////////////////////////////////////////////
TEST(NCIPestGrowth, TestRun1) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    clTreePopulation * p_oPop;
    float fDiam, fExpectedDiam;
    int iInf;
    bool b0Yr = false, b1Yr = false, b2Yr = false, b3Yr = false, b4Yr = false,
        b5Yr = false;

    //Load our test file and get our tree population pointers
    p_oSimManager->ReadFile(WriteNCIPestGrowthXMLFile1());
    p_oPop = (clTreePopulation *) p_oSimManager->GetPopulationObject(
        "treepopulation");

    //Now do the run
    p_oSimManager->RunSim(1);

    //Check the diameters and growth of the trees
    clTreeSearch *p_oAllTrees = p_oPop->Find( "all" );
    clTree *p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {
      p_oTree->GetValue(p_oPop->GetIntDataCode("YearsInfested", p_oTree->GetSpecies(), p_oTree->GetType()), &iInf);
      if (0 == iInf) {
        b0Yr = true;

        if (0 == p_oTree->GetSpecies()) {
          fExpectedDiam = 32;
          p_oTree->GetValue(p_oPop->GetDbhCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fDiam);
          EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);
        } else {
          fExpectedDiam = 30;
          p_oTree->GetValue(p_oPop->GetDbhCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fDiam);
          EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);
        }

      } else if (1 == iInf) {
        b1Yr = true;

        if (0 == p_oTree->GetSpecies()) {
          fExpectedDiam = 24.8;
          p_oTree->GetValue(p_oPop->GetDbhCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fDiam);
          EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);
        } else {
          fExpectedDiam = 25.5;
          p_oTree->GetValue(p_oPop->GetDbhCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fDiam);
          EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);
        }
      } else if (2 == iInf) {
        b2Yr = true;

        if (0 == p_oTree->GetSpecies()) {
          fExpectedDiam = 25.63177662;
          p_oTree->GetValue(p_oPop->GetDbhCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fDiam);
          EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);
        } else {
          fExpectedDiam = 27.57944154;
          p_oTree->GetValue(p_oPop->GetDbhCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fDiam);
          EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);
        }
      } else if (3 == iInf) {
        b3Yr = true;

        if (0 == p_oTree->GetSpecies()) {
          fExpectedDiam = 26.11833475;
          p_oTree->GetValue(p_oPop->GetDbhCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fDiam);
          EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);
        } else {
          fExpectedDiam = 28.79583687;
          p_oTree->GetValue(p_oPop->GetDbhCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fDiam);
          EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);
        }
      } else if (4 == iInf) {
        b4Yr = true;

        if (0 == p_oTree->GetSpecies()) {
          fExpectedDiam = 26.46355323;
          p_oTree->GetValue(p_oPop->GetDbhCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fDiam);
          EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);
        } else {
          fExpectedDiam = 29.65888308;
          p_oTree->GetValue(p_oPop->GetDbhCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fDiam);
          EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);
        }
      } else if (5 == iInf) {
        b5Yr = true;

        if (0 == p_oTree->GetSpecies()) {
          fExpectedDiam = 26.73132549;
          p_oTree->GetValue(p_oPop->GetDbhCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fDiam);
          EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);
        } else {
          fExpectedDiam = 30;
          p_oTree->GetValue(p_oPop->GetDbhCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fDiam);
          EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);
        }
      }

      p_oTree = p_oAllTrees->NextTree();
    }

    //Verify that there were actually trees of all the years so things went
    //the way we expected
    EXPECT_TRUE(b0Yr);
    EXPECT_TRUE(b1Yr);
    EXPECT_TRUE(b2Yr);
    EXPECT_TRUE(b3Yr);
    EXPECT_TRUE(b4Yr);
    EXPECT_TRUE(b5Yr);

    delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

////////////////////////////////////////////////////////////////////////////
// TestRun2()
// Testing size dependent infection.
////////////////////////////////////////////////////////////////////////////
TEST(NCIPestGrowth, TestRun2) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    clTreePopulation * p_oPop;
    float fDiam, fExpectedDiam;
    int iInf;
    bool b0Yr = false, b1Yr = false, b2Yr = false, b3Yr = false, b4Yr = false,
        b5Yr = false;

    //Load our test file and get our tree population pointers
    p_oSimManager->ReadFile(WriteNCIPestGrowthXMLFile2());
    p_oPop = (clTreePopulation *) p_oSimManager->GetPopulationObject(
        "treepopulation");

    //Now do the run
    p_oSimManager->RunSim(1);

    //Check the diameters and growth of the trees
    clTreeSearch *p_oAllTrees = p_oPop->Find( "all" );
    clTree *p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {
      p_oTree->GetValue(p_oPop->GetIntDataCode("YearsInfested", p_oTree->GetSpecies(), p_oTree->GetType()), &iInf);
      if (0 == iInf) {
        b0Yr = true;

        if (0 == p_oTree->GetSpecies()) fExpectedDiam = 32;
        else if (1 == p_oTree->GetSpecies()) fExpectedDiam = 26;
        else if (2 == p_oTree->GetSpecies()) fExpectedDiam = 27;
        else fExpectedDiam = 55;

        p_oTree->GetValue(p_oPop->GetDbhCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fDiam);
        EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);

      } else if (1 == iInf) {
        b1Yr = true;

        if (0 == p_oTree->GetSpecies()) fExpectedDiam = 23.517;
        else if (1 == p_oTree->GetSpecies()) fExpectedDiam = 21.436;
        else if (2 == p_oTree->GetSpecies()) fExpectedDiam = 19.169;
        else fExpectedDiam = 50.442;

        p_oTree->GetValue(p_oPop->GetDbhCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fDiam);
        EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);

      } else if (2 == iInf) {
        b2Yr = true;

       if (0 == p_oTree->GetSpecies()) fExpectedDiam = 22.908;
        else if (1 == p_oTree->GetSpecies()) fExpectedDiam = 19.369;
        else if (2 == p_oTree->GetSpecies()) fExpectedDiam = 18.447;
        else fExpectedDiam = 48.374;

        p_oTree->GetValue(p_oPop->GetDbhCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fDiam);
        EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);

      } else if (3 == iInf) {
        b3Yr = true;

        if (0 == p_oTree->GetSpecies()) fExpectedDiam = 22.551;
        else if (1 == p_oTree->GetSpecies()) fExpectedDiam = 18.160;
        else if (2 == p_oTree->GetSpecies()) fExpectedDiam = 18.024;
        else fExpectedDiam = 47.164;

        p_oTree->GetValue(p_oPop->GetDbhCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fDiam);
        EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);

      } else if (4 == iInf) {
        b4Yr = true;

        if (0 == p_oTree->GetSpecies()) fExpectedDiam = 22.298;
        else if (1 == p_oTree->GetSpecies()) fExpectedDiam = 17.302;
        else if (2 == p_oTree->GetSpecies()) fExpectedDiam = 17.724;
        else fExpectedDiam = 46.306;

        p_oTree->GetValue(p_oPop->GetDbhCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fDiam);
        EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);

      } else if (5 == iInf) {
        b5Yr = true;

        if (0 == p_oTree->GetSpecies()) fExpectedDiam = 22.102;
        else if (1 == p_oTree->GetSpecies()) fExpectedDiam = 16.637;
        else if (2 == p_oTree->GetSpecies()) fExpectedDiam = 17.491;
        else fExpectedDiam = 45.640;

        p_oTree->GetValue(p_oPop->GetDbhCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fDiam);
        EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);

      }

      p_oTree = p_oAllTrees->NextTree();
    }

    //Verify that there were actually trees of all the years so things went
    //the way we expected
    EXPECT_TRUE(b0Yr);
    EXPECT_TRUE(b1Yr);
    EXPECT_TRUE(b2Yr);
    EXPECT_TRUE(b3Yr);
    EXPECT_TRUE(b4Yr);
    EXPECT_TRUE(b5Yr);

    delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}



////////////////////////////////////////////////////////////////////////////
// TestRun3()
// Testing size effect shifted lognormal with infection.
////////////////////////////////////////////////////////////////////////////
TEST(NCIPestGrowth, TestRun3) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    clTreePopulation * p_oPop;
    float fDiam, fExpectedDiam;
    int iInf, iNumInf = 0, iNumNotInf = 0;

    //Load our test file and get our tree population pointers
    p_oSimManager->ReadFile(WriteNCIPestGrowthXMLFile3());
    p_oPop = (clTreePopulation *) p_oSimManager->GetPopulationObject(
        "treepopulation");

    //----------------------------------------------------------------------
    //    Timestep 1 - no infestation yet
    //----------------------------------------------------------------------
    p_oSimManager->RunSim(1);

    //Check the diameters and growth of the trees
    clTreeSearch *p_oAllTrees = p_oPop->Find( "all" );
    clTree *p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {
      p_oTree->GetValue(p_oPop->GetIntDataCode("YearsInfested", p_oTree->GetSpecies(), p_oTree->GetType()), &iInf);

      //No trees infested yet
      EXPECT_EQ(0, iInf);

      if (0 == p_oTree->GetSpecies()) fExpectedDiam = 31.58847501;
      else if (1 == p_oTree->GetSpecies()) fExpectedDiam = 41.9544283;
      else if (2 == p_oTree->GetSpecies()) fExpectedDiam = 21.08668128;
      else fExpectedDiam = 48.82197821;

      p_oTree->GetValue(p_oPop->GetDbhCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fDiam);
      EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);

      p_oTree = p_oAllTrees->NextTree();
    }

    //----------------------------------------------------------------------
    //    Timestep 2 - about 50% of trees are infested
    //----------------------------------------------------------------------
    p_oSimManager->RunSim(1);

    //Check the diameters and growth of the trees
    p_oAllTrees = p_oPop->Find( "all" );
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {
      p_oTree->GetValue(p_oPop->GetIntDataCode("YearsInfested", p_oTree->GetSpecies(), p_oTree->GetType()), &iInf);

      if (iInf == 0) iNumNotInf++;
      else iNumInf++;

      if (iInf == 0) {
        if (0 == p_oTree->GetSpecies()) fExpectedDiam = 43.56340538;
        else if (1 == p_oTree->GetSpecies()) fExpectedDiam = 53.93316458;
        else if (2 == p_oTree->GetSpecies()) fExpectedDiam = 29.03219242;
        else fExpectedDiam = 52.29686975;
      } else {
        if (0 == p_oTree->GetSpecies()) fExpectedDiam = 37.16545262;
        else if (1 == p_oTree->GetSpecies()) fExpectedDiam = 48.83391246;
        else if (2 == p_oTree->GetSpecies()) fExpectedDiam = 21.88491666;
        else fExpectedDiam = 51.45248031;
      }

      p_oTree->GetValue(p_oPop->GetDbhCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fDiam);
      EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);

      p_oTree = p_oAllTrees->NextTree();
    }

    //Make sure infestation levels were about right
    EXPECT_LT(fabs(iNumInf - iNumNotInf)/(iNumInf + iNumNotInf), 0.1);

    delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

////////////////////////////////////////////////////////////////////////////
// TestRun4()
// Testing size effect compound exponential with infection.
////////////////////////////////////////////////////////////////////////////
TEST(NCIPestGrowth, TestRun4) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    clTreePopulation * p_oPop;
    float fDiam, fExpectedDiam;
    int iInf, iNumInf = 0, iNumNotInf = 0;

    //Load our test file and get our tree population pointers
    p_oSimManager->ReadFile(WriteNCIPestGrowthXMLFile4());
    p_oPop = (clTreePopulation *) p_oSimManager->GetPopulationObject(
        "treepopulation");

    //----------------------------------------------------------------------
    //    Timestep 1 - no infestation yet
    //----------------------------------------------------------------------
    p_oSimManager->RunSim(1);

    //Check the diameters and growth of the trees
    clTreeSearch *p_oAllTrees = p_oPop->Find( "all" );
    clTree *p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {
      p_oTree->GetValue(p_oPop->GetIntDataCode("YearsInfested", p_oTree->GetSpecies(), p_oTree->GetType()), &iInf);

      //No trees infested yet
      EXPECT_EQ(0, iInf);

      if (0 == p_oTree->GetSpecies()) fExpectedDiam = 31.42255393;
      else if (1 == p_oTree->GetSpecies()) fExpectedDiam = 41.49258845;
      else if (2 == p_oTree->GetSpecies()) fExpectedDiam = 27.04415068;
      else fExpectedDiam = 55.83104019;

      p_oTree->GetValue(p_oPop->GetDbhCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fDiam);
      EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);

      p_oTree = p_oAllTrees->NextTree();
    }

    //----------------------------------------------------------------------
    //    Timestep 2 - about 50% of trees are infested
    //----------------------------------------------------------------------
    p_oSimManager->RunSim(1);

    //Check the diameters and growth of the trees
    p_oAllTrees = p_oPop->Find( "all" );
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {
      p_oTree->GetValue(p_oPop->GetIntDataCode("YearsInfested", p_oTree->GetSpecies(), p_oTree->GetType()), &iInf);

      if (iInf == 0) iNumNotInf++;
      else iNumInf++;

      if (iInf == 0) {
        if (0 == p_oTree->GetSpecies()) fExpectedDiam = 42.91647383;
        else if (1 == p_oTree->GetSpecies()) fExpectedDiam = 52.95891407;
        else if (2 == p_oTree->GetSpecies()) fExpectedDiam = 38.66928702;
        else fExpectedDiam = 66.24214553;
      } else {
        if (0 == p_oTree->GetSpecies()) fExpectedDiam = 42.45519556;
        else if (1 == p_oTree->GetSpecies()) fExpectedDiam = 52.13106634;
        else if (2 == p_oTree->GetSpecies()) fExpectedDiam = 31.33768035;
        else fExpectedDiam = 57.04076823;
      }

      p_oTree->GetValue(p_oPop->GetDbhCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fDiam);
      EXPECT_LT(fabs(fDiam - fExpectedDiam)/fDiam, 0.001);

      p_oTree = p_oAllTrees->NextTree();
    }

    //Make sure infestation levels were about right
    EXPECT_LT(fabs(iNumInf - iNumNotInf)/(iNumInf + iNumNotInf), 0.1);

    delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}


////////////////////////////////////////////////////////////////////////////
// TestErrorProcessing()
////////////////////////////////////////////////////////////////////////////
TEST(NCIPestGrowth, TestErrorProcessing) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    p_oSimManager->ReadFile(WriteNCIPestGrowthXMLErrorFile1());
    FAIL() << "TestNCIPestGrowth error processing didn't catch error for WriteNCIPestGrowthXMLErrorFile1.";
  } catch (modelErr& err) {
    if (err.sFunction.compare("clInfectionEffect::DoSetup") != 0) {
      FAIL() << "TestNCIPestGrowth error processing caught wrong error for WriteNCIPestGrowthXMLErrorFile1.";
    };
  }

  try {
    p_oSimManager->ReadFile(WriteNCIPestGrowthXMLErrorFile2());
    FAIL() << "TestNCIPestGrowth error processing didn't catch error for WriteNCIPestGrowthXMLErrorFile2.";
  } catch (modelErr& err) {
    if (err.sFunction.compare("clInfectionEffectSizeDependent::DoSetup") != 0) {
      FAIL() << "TestNCIPestGrowth error processing caught wrong error for WriteNCIPestGrowthXMLErrorFile2.";
    };
  }

  try {
    p_oSimManager->ReadFile(WriteNCIPestGrowthXMLErrorFile3());
    FAIL() << "TestNCIPestGrowth error processing didn't catch error for WriteNCIPestGrowthXMLErrorFile3.";
  } catch (modelErr& err) {
    if (err.sFunction.compare("clInfectionEffectSizeDependent::DoSetup") != 0) {
      FAIL() << "TestNCIPestGrowth error processing caught wrong error for WriteNCIPestGrowthXMLErrorFile3.";
    };
  }

  try {
    p_oSimManager->ReadFile(WriteNCIPestGrowthXMLErrorFile4());
    FAIL() << "TestNCIPestGrowth error processing didn't catch error for WriteNCIPestGrowthXMLErrorFile4.";
  } catch (modelErr& err) {
    if (err.sFunction.compare("clSizeEffectShiftedLogInf::DoSetup") != 0) {
      FAIL() << "TestNCIPestGrowth error processing caught wrong error for WriteNCIPestGrowthXMLErrorFile4.";
    };
  }

  try {
    p_oSimManager->ReadFile(WriteNCIPestGrowthXMLErrorFile5());
    FAIL() << "TestNCIPestGrowth error processing didn't catch error for WriteNCIPestGrowthXMLErrorFile5.";
  } catch (modelErr& err) {
    if (err.sFunction.compare("clSizeEffectCompoundExpInf::DoSetup") != 0) {
      FAIL() << "TestNCIPestGrowth error processing caught wrong error for WriteNCIPestGrowthXMLErrorFile5.";
    };
  }

  delete p_oSimManager;
}

////////////////////////////////////////////////////////////////////////////
// WriteNCIPestGrowthXMLFile1()
////////////////////////////////////////////////////////////////////////////
const char* WriteNCIPestGrowthXMLFile1() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  //Write file
  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06010101\">"
       << "<plot>"
       << "<timesteps>1</timesteps>"
       << "<yearsPerTimestep>1</yearsPerTimestep>"
       << "<randomSeed>1</randomSeed>"
       << "<plot_lenX>200.0</plot_lenX>"
       << "<plot_lenY>200.0</plot_lenY>"
       << "<plot_latitude>55.37</plot_latitude>"
       << "<plot_precip_mm_yr>1150.64</plot_precip_mm_yr>"
       << "<plot_temp_C>12.88</plot_temp_C>"
       << "<plot_n_dep>3.58</plot_n_dep>"
       << "<plot_seasonal_precipitation>34</plot_seasonal_precipitation>"
       << "<plot_water_deficit>456.2</plot_water_deficit>"
       << "</plot>";

  oOut << "<trees>"
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
       << "<tr_treemap>"
       << "<tm_treeSettings sp=\"Species_1\" tp=\"3\">"
       << "<tm_floatCodes>"
       << "<tm_floatCode label=\"X\">0</tm_floatCode>"
       << "<tm_floatCode label=\"Y\">1</tm_floatCode>"
       << "<tm_floatCode label=\"DBH\">2</tm_floatCode>"
       << "</tm_floatCodes>"
       << "</tm_treeSettings>"
       << "<tm_treeSettings sp=\"Species_2\" tp=\"3\">"
       << "<tm_floatCodes>"
       << "<tm_floatCode label=\"X\">0</tm_floatCode>"
       << "<tm_floatCode label=\"Y\">1</tm_floatCode>"
       << "<tm_floatCode label=\"DBH\">2</tm_floatCode>"
       << "</tm_floatCodes>"
       << "</tm_treeSettings>";
  for (int i = 0; i < 1000; i++) {
    oOut << "<tree sp=\"0\" tp=\"3\">"
         << "<fl c=\"0\">" << clModelMath::GetRand() * 99 << "</fl>" //X
         << "<fl c=\"1\">" << clModelMath::GetRand() * 99 << "</fl>" //Y
         << "<fl c=\"2\">20</fl>" //DBH
         << "</tree>";
  }
  for (int i = 0; i < 1000; i++) {
    oOut << "<tree sp=\"1\" tp=\"3\">"
         << "<fl c=\"0\">" << clModelMath::GetRand() * 99 << "</fl>" //X
         << "<fl c=\"1\">" << clModelMath::GetRand() * 99 << "</fl>" //Y
         << "<fl c=\"2\">15</fl>" //DBH
         << "</tree>";
  }
  oOut << "</tr_treemap>"
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

  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>DensDepInfestation</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>NCIMasterGrowth</behaviorName>"
       << "<version>3</version>"
       << "<listPosition>2</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "</behavior>"
       << "</behaviorList>"

       << "<DensDepInfestation1>"
       << "<di_densDepInfMaxInfestation>1</di_densDepInfMaxInfestation>"
       << "<di_densDepInfA>0.2</di_densDepInfA>"
       << "<di_densDepInfBx>0.3</di_densDepInfBx>"
       << "<di_densDepInfBy>0.2</di_densDepInfBy>"
       << "<di_densDepInfMinDBH>"
       << "<di_ddimdVal species=\"Species_1\">0</di_ddimdVal>"
       << "<di_ddimdVal species=\"Species_2\">0</di_ddimdVal>"
       << "</di_densDepInfMinDBH>"
       << "<di_densDepInfCohortDBH>"
       << "<di_ddicdVal species=\"Species_1\">0</di_ddicdVal>"
       << "<di_ddicdVal species=\"Species_2\">0</di_ddicdVal>"
       << "</di_densDepInfCohortDBH>"
       << "<di_densDepInfPropResistant>"
       << "<di_ddiprVal species=\"Species_1\">0</di_ddiprVal>"
       << "<di_ddiprVal species=\"Species_2\">0</di_ddiprVal>"
       << "</di_densDepInfPropResistant>"
       << "<di_densDepInfPropCondSusceptible>"
       << "<di_ddipcsVal species=\"Species_1\">0</di_ddipcsVal>"
       << "<di_ddipcsVal species=\"Species_2\">0</di_ddipcsVal>"
       << "</di_densDepInfPropCondSusceptible>"
       << "<di_densDepInfStartYear>-5</di_densDepInfStartYear>"
       << "</DensDepInfestation1>"

       << "<NCIMasterGrowth2>"
       << "<nciWhichShadingEffect>" << no_shading << "</nciWhichShadingEffect>"
       << "<nciWhichCrowdingEffect>" << no_crowding_effect << "</nciWhichCrowdingEffect>"
       << "<nciWhichNCITerm>" << no_nci_term << "</nciWhichNCITerm>"
       << "<nciWhichSizeEffect>" << no_size_effect << "</nciWhichSizeEffect>"
       << "<nciWhichDamageEffect>" << no_damage_effect << "</nciWhichDamageEffect>"
       << "<nciWhichPrecipitationEffect>" << no_precip_effect << "</nciWhichPrecipitationEffect>"
       << "<nciWhichTemperatureEffect>" << no_temp_effect << "</nciWhichTemperatureEffect>"
       << "<nciWhichNitrogenEffect>" << no_nitrogen_effect << "</nciWhichNitrogenEffect>"
       << "<nciWhichInfectionEffect> " << infection_effect << "</nciWhichInfectionEffect>"
       << "<gr_stochGrowthMethod>" << deterministic_pdf << "</gr_stochGrowthMethod>"
       << "<gr_nciMaxPotentialGrowth>"
       << "<gr_nmpgVal species=\"Species_1\">12</gr_nmpgVal>"
       << "<gr_nmpgVal species=\"Species_2\">15</gr_nmpgVal>"
       << "</gr_nciMaxPotentialGrowth>"
       << "<nciInfectionEffectA>"
       << "<nieaVal species=\"Species_1\">0.1</nieaVal>"
       << "<nieaVal species=\"Species_2\">0.2</nieaVal>"
       << "</nciInfectionEffectA>"
       << "<nciInfectionEffectB>"
       << "<niebVal species=\"Species_1\">0.4</niebVal>"
       << "<niebVal species=\"Species_2\">0.7</niebVal>"
       << "</nciInfectionEffectB>"
       << "</NCIMasterGrowth2>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteNCIPestGrowthXMLFile2()
////////////////////////////////////////////////////////////////////////////
const char* WriteNCIPestGrowthXMLFile2() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  //Write file
  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06010101\">"
       << "<plot>"
       << "<timesteps>1</timesteps>"
       << "<yearsPerTimestep>1</yearsPerTimestep>"
       << "<randomSeed>1</randomSeed>"
       << "<plot_lenX>200.0</plot_lenX>"
       << "<plot_lenY>200.0</plot_lenY>"
       << "<plot_latitude>55.37</plot_latitude>"
       << "<plot_precip_mm_yr>1150.64</plot_precip_mm_yr>"
       << "<plot_temp_C>12.88</plot_temp_C>"
       << "<plot_n_dep>3.58</plot_n_dep>"
       << "<plot_seasonal_precipitation>34</plot_seasonal_precipitation>"
       << "<plot_water_deficit>456.2</plot_water_deficit>"
       << "</plot>";

  oOut << "<trees>"
       << "<tr_speciesList>"
       << "<tr_species speciesName=\"Species_1\" />"
       << "<tr_species speciesName=\"Species_2\" />"
       << "<tr_species speciesName=\"Species_3\" />"
       << "<tr_species speciesName=\"Species_4\" />"
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
       << "<tr_treemap>"
       << "<tm_treeSettings sp=\"Species_1\" tp=\"3\">"
       << "<tm_floatCodes>"
       << "<tm_floatCode label=\"X\">0</tm_floatCode>"
       << "<tm_floatCode label=\"Y\">1</tm_floatCode>"
       << "<tm_floatCode label=\"DBH\">2</tm_floatCode>"
       << "</tm_floatCodes>"
       << "</tm_treeSettings>"
       << "<tm_treeSettings sp=\"Species_2\" tp=\"3\">"
       << "<tm_floatCodes>"
       << "<tm_floatCode label=\"X\">0</tm_floatCode>"
       << "<tm_floatCode label=\"Y\">1</tm_floatCode>"
       << "<tm_floatCode label=\"DBH\">2</tm_floatCode>"
       << "</tm_floatCodes>"
       << "</tm_treeSettings>"
       << "<tm_treeSettings sp=\"Species_3\" tp=\"3\">"
       << "<tm_floatCodes>"
       << "<tm_floatCode label=\"X\">0</tm_floatCode>"
       << "<tm_floatCode label=\"Y\">1</tm_floatCode>"
       << "<tm_floatCode label=\"DBH\">2</tm_floatCode>"
       << "</tm_floatCodes>"
       << "</tm_treeSettings>"
       << "<tm_treeSettings sp=\"Species_4\" tp=\"3\">"
       << "<tm_floatCodes>"
       << "<tm_floatCode label=\"X\">0</tm_floatCode>"
       << "<tm_floatCode label=\"Y\">1</tm_floatCode>"
       << "<tm_floatCode label=\"DBH\">2</tm_floatCode>"
       << "</tm_floatCodes>"
       << "</tm_treeSettings>";
  for (int i = 0; i < 1000; i++) {
    oOut << "<tree sp=\"0\" tp=\"3\">"
         << "<fl c=\"0\">" << clModelMath::GetRand() * 99 << "</fl>" //X
         << "<fl c=\"1\">" << clModelMath::GetRand() * 99 << "</fl>" //Y
         << "<fl c=\"2\">20</fl>" //DBH
         << "</tree>";
  }
  for (int i = 0; i < 1000; i++) {
    oOut << "<tree sp=\"1\" tp=\"3\">"
         << "<fl c=\"0\">" << clModelMath::GetRand() * 99 << "</fl>" //X
         << "<fl c=\"1\">" << clModelMath::GetRand() * 99 << "</fl>" //Y
         << "<fl c=\"2\">11</fl>" //DBH
         << "</tree>";
  }
  for (int i = 0; i < 1000; i++) {
    oOut << "<tree sp=\"2\" tp=\"3\">"
         << "<fl c=\"0\">" << clModelMath::GetRand() * 99 << "</fl>" //X
         << "<fl c=\"1\">" << clModelMath::GetRand() * 99 << "</fl>" //Y
         << "<fl c=\"2\">15</fl>" //DBH
         << "</tree>";
  }
  for (int i = 0; i < 1000; i++) {
    oOut << "<tree sp=\"3\" tp=\"3\">"
         << "<fl c=\"0\">" << clModelMath::GetRand() * 99 << "</fl>" //X
         << "<fl c=\"1\">" << clModelMath::GetRand() * 99 << "</fl>" //Y
         << "<fl c=\"2\">40</fl>" //DBH
         << "</tree>";
  }
  oOut << "</tr_treemap>"
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
       << "<tr_soahVal species=\"Species_2\">0.0299</tr_soahVal>"
       << "<tr_soahVal species=\"Species_3\">0.0299</tr_soahVal>"
       << "<tr_soahVal species=\"Species_4\">0.0299</tr_soahVal>"
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
       << "<behaviorName>DensDepInfestation</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_4\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_4\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_3\" type=\"Sapling\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>NCIMasterGrowth</behaviorName>"
       << "<version>3</version>"
       << "<listPosition>2</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_4\" type=\"Adult\"/>"
       << "</behavior>"
       << "</behaviorList>"

       << "<DensDepInfestation1>"
       << "<di_densDepInfMaxInfestation>1</di_densDepInfMaxInfestation>"
       << "<di_densDepInfA>0.2</di_densDepInfA>"
       << "<di_densDepInfBx>0.3</di_densDepInfBx>"
       << "<di_densDepInfBy>0.2</di_densDepInfBy>"
       << "<di_densDepInfMinDBH>"
       << "<di_ddimdVal species=\"Species_1\">0</di_ddimdVal>"
       << "<di_ddimdVal species=\"Species_2\">0</di_ddimdVal>"
       << "<di_ddimdVal species=\"Species_3\">0</di_ddimdVal>"
       << "<di_ddimdVal species=\"Species_4\">0</di_ddimdVal>"
       << "</di_densDepInfMinDBH>"
       << "<di_densDepInfCohortDBH>"
       << "<di_ddicdVal species=\"Species_1\">0</di_ddicdVal>"
       << "<di_ddicdVal species=\"Species_2\">0</di_ddicdVal>"
       << "<di_ddicdVal species=\"Species_3\">0</di_ddicdVal>"
       << "<di_ddicdVal species=\"Species_4\">0</di_ddicdVal>"
       << "</di_densDepInfCohortDBH>"
       << "<di_densDepInfPropResistant>"
       << "<di_ddiprVal species=\"Species_1\">0</di_ddiprVal>"
       << "<di_ddiprVal species=\"Species_2\">0</di_ddiprVal>"
       << "<di_ddiprVal species=\"Species_3\">0</di_ddiprVal>"
       << "<di_ddiprVal species=\"Species_4\">0</di_ddiprVal>"
       << "</di_densDepInfPropResistant>"
       << "<di_densDepInfPropCondSusceptible>"
       << "<di_ddipcsVal species=\"Species_1\">0</di_ddipcsVal>"
       << "<di_ddipcsVal species=\"Species_2\">0</di_ddipcsVal>"
       << "<di_ddipcsVal species=\"Species_3\">0</di_ddipcsVal>"
       << "<di_ddipcsVal species=\"Species_4\">0</di_ddipcsVal>"
       << "</di_densDepInfPropCondSusceptible>"
       << "<di_densDepInfStartYear>-5</di_densDepInfStartYear>"
       << "</DensDepInfestation1>"

       << "<NCIMasterGrowth2>"
       << "<nciWhichShadingEffect>" << no_shading << "</nciWhichShadingEffect>"
       << "<nciWhichCrowdingEffect>" << no_crowding_effect << "</nciWhichCrowdingEffect>"
       << "<nciWhichNCITerm>" << no_nci_term << "</nciWhichNCITerm>"
       << "<nciWhichSizeEffect>" << no_size_effect << "</nciWhichSizeEffect>"
       << "<nciWhichDamageEffect>" << no_damage_effect << "</nciWhichDamageEffect>"
       << "<nciWhichPrecipitationEffect>" << no_precip_effect << "</nciWhichPrecipitationEffect>"
       << "<nciWhichTemperatureEffect>" << no_temp_effect << "</nciWhichTemperatureEffect>"
       << "<nciWhichNitrogenEffect>" << no_nitrogen_effect << "</nciWhichNitrogenEffect>"
       << "<nciWhichInfectionEffect>" << infection_effect_size_dep << "</nciWhichInfectionEffect>"
       << "<gr_stochGrowthMethod>" << deterministic_pdf << "</gr_stochGrowthMethod>"
       << "<gr_nciMaxPotentialGrowth>"
       << "<gr_nmpgVal species=\"Species_1\">12</gr_nmpgVal>"
       << "<gr_nmpgVal species=\"Species_2\">15</gr_nmpgVal>"
       << "<gr_nmpgVal species=\"Species_3\">12</gr_nmpgVal>"
       << "<gr_nmpgVal species=\"Species_4\">15</gr_nmpgVal>"
       << "</gr_nciMaxPotentialGrowth>"
       << "<nciInfectionEffectA>"
       << "<nieaVal species=\"Species_1\">-0.1</nieaVal>"
       << "<nieaVal species=\"Species_2\">-0.2</nieaVal>"
       << "<nieaVal species=\"Species_3\">-0.1</nieaVal>"
       << "<nieaVal species=\"Species_4\">-0.2</nieaVal>"
       << "</nciInfectionEffectA>"
       << "<nciInfectionEffectB>"
       << "<niebVal species=\"Species_1\">0.4</niebVal>"
       << "<niebVal species=\"Species_2\">0.7</niebVal>"
       << "<niebVal species=\"Species_3\">0.4</niebVal>"
       << "<niebVal species=\"Species_4\">0.7</niebVal>"
       << "</nciInfectionEffectB>"
       << "<nciInfectionEffectX0>"
       << "<niex0Val species=\"Species_1\">10</niex0Val>"
       << "<niex0Val species=\"Species_2\">26</niex0Val>"
       << "<niex0Val species=\"Species_3\">10</niex0Val>"
       << "<niex0Val species=\"Species_4\">26</niex0Val>"
       << "</nciInfectionEffectX0>"
       << "<nciInfectionEffectXb>"
       << "<niexbVal species=\"Species_1\">1</niexbVal>"
       << "<niexbVal species=\"Species_2\">5</niexbVal>"
       << "<niexbVal species=\"Species_3\">1</niexbVal>"
       << "<niexbVal species=\"Species_4\">5</niexbVal>"
       << "</nciInfectionEffectXb>"
       << "<nciInfectionEffectXp>"
       << "<niexpVal species=\"Species_1\">2</niexpVal>"
       << "<niexpVal species=\"Species_2\">4</niexpVal>"
       << "<niexpVal species=\"Species_3\">2</niexpVal>"
       << "<niexpVal species=\"Species_4\">4</niexpVal>"
       << "</nciInfectionEffectXp>"
       << "</NCIMasterGrowth2>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}


////////////////////////////////////////////////////////////////////////////
// WriteNCIPestGrowthXMLFile3()
////////////////////////////////////////////////////////////////////////////
const char* WriteNCIPestGrowthXMLFile3() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  //Write file
  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06010101\">"
       << "<plot>"
       << "<timesteps>3</timesteps>"
       << "<yearsPerTimestep>1</yearsPerTimestep>"
       << "<randomSeed>1</randomSeed>"
       << "<plot_lenX>200.0</plot_lenX>"
       << "<plot_lenY>200.0</plot_lenY>"
       << "<plot_latitude>55.37</plot_latitude>"
       << "<plot_precip_mm_yr>1150.64</plot_precip_mm_yr>"
       << "<plot_temp_C>12.88</plot_temp_C>"
       << "<plot_n_dep>3.58</plot_n_dep>"
       << "<plot_seasonal_precipitation>34</plot_seasonal_precipitation>"
       << "<plot_water_deficit>456.2</plot_water_deficit>"
       << "</plot>";

  oOut << "<trees>"
       << "<tr_speciesList>"
       << "<tr_species speciesName=\"Species_1\" />"
       << "<tr_species speciesName=\"Species_2\" />"
       << "<tr_species speciesName=\"Species_3\" />"
       << "<tr_species speciesName=\"Species_4\" />"
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
       << "<tr_treemap>"
       << "<tm_treeSettings sp=\"Species_1\" tp=\"3\">"
       << "<tm_floatCodes>"
       << "<tm_floatCode label=\"X\">0</tm_floatCode>"
       << "<tm_floatCode label=\"Y\">1</tm_floatCode>"
       << "<tm_floatCode label=\"DBH\">2</tm_floatCode>"
       << "</tm_floatCodes>"
       << "</tm_treeSettings>"
       << "<tm_treeSettings sp=\"Species_2\" tp=\"3\">"
       << "<tm_floatCodes>"
       << "<tm_floatCode label=\"X\">0</tm_floatCode>"
       << "<tm_floatCode label=\"Y\">1</tm_floatCode>"
       << "<tm_floatCode label=\"DBH\">2</tm_floatCode>"
       << "</tm_floatCodes>"
       << "</tm_treeSettings>"
       << "<tm_treeSettings sp=\"Species_3\" tp=\"3\">"
       << "<tm_floatCodes>"
       << "<tm_floatCode label=\"X\">0</tm_floatCode>"
       << "<tm_floatCode label=\"Y\">1</tm_floatCode>"
       << "<tm_floatCode label=\"DBH\">2</tm_floatCode>"
       << "</tm_floatCodes>"
       << "</tm_treeSettings>"
       << "<tm_treeSettings sp=\"Species_4\" tp=\"3\">"
       << "<tm_floatCodes>"
       << "<tm_floatCode label=\"X\">0</tm_floatCode>"
       << "<tm_floatCode label=\"Y\">1</tm_floatCode>"
       << "<tm_floatCode label=\"DBH\">2</tm_floatCode>"
       << "</tm_floatCodes>"
       << "</tm_treeSettings>";
  for (int i = 0; i < 1000; i++) {
    oOut << "<tree sp=\"0\" tp=\"3\">"
         << "<fl c=\"0\">" << clModelMath::GetRand() * 99 << "</fl>" //X
         << "<fl c=\"1\">" << clModelMath::GetRand() * 99 << "</fl>" //Y
         << "<fl c=\"2\">20</fl>" //DBH
         << "</tree>";
  }
  for (int i = 0; i < 1000; i++) {
    oOut << "<tree sp=\"1\" tp=\"3\">"
         << "<fl c=\"0\">" << clModelMath::GetRand() * 99 << "</fl>" //X
         << "<fl c=\"1\">" << clModelMath::GetRand() * 99 << "</fl>" //Y
         << "<fl c=\"2\">30</fl>" //DBH
         << "</tree>";
  }
  for (int i = 0; i < 1000; i++) {
    oOut << "<tree sp=\"2\" tp=\"3\">"
         << "<fl c=\"0\">" << clModelMath::GetRand() * 99 << "</fl>" //X
         << "<fl c=\"1\">" << clModelMath::GetRand() * 99 << "</fl>" //Y
         << "<fl c=\"2\">11</fl>" //DBH
         << "</tree>";
  }
  for (int i = 0; i < 1000; i++) {
    oOut << "<tree sp=\"3\" tp=\"3\">"
         << "<fl c=\"0\">" << clModelMath::GetRand() * 99 << "</fl>" //X
         << "<fl c=\"1\">" << clModelMath::GetRand() * 99 << "</fl>" //Y
         << "<fl c=\"2\">45</fl>" //DBH
         << "</tree>";
  }
  oOut << "</tr_treemap>"
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
       << "<tr_soahVal species=\"Species_2\">0.0299</tr_soahVal>"
       << "<tr_soahVal species=\"Species_3\">0.0299</tr_soahVal>"
       << "<tr_soahVal species=\"Species_4\">0.0299</tr_soahVal>"
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
       << "<behaviorName>DensDepInfestation</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_4\" type=\"Adult\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>NCIMasterGrowth</behaviorName>"
       << "<version>3</version>"
       << "<listPosition>2</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_4\" type=\"Adult\"/>"
       << "</behavior>"
       << "</behaviorList>"

       << "<DensDepInfestation1>"
       << "<di_densDepInfMaxInfestation>0.5</di_densDepInfMaxInfestation>"
       << "<di_densDepInfA>-100</di_densDepInfA>"
       << "<di_densDepInfBx>0.3</di_densDepInfBx>"
       << "<di_densDepInfBy>0.2</di_densDepInfBy>"
       << "<di_densDepInfMinDBH>"
       << "<di_ddimdVal species=\"Species_1\">0</di_ddimdVal>"
       << "<di_ddimdVal species=\"Species_2\">0</di_ddimdVal>"
       << "<di_ddimdVal species=\"Species_3\">0</di_ddimdVal>"
       << "<di_ddimdVal species=\"Species_4\">0</di_ddimdVal>"
       << "</di_densDepInfMinDBH>"
       << "<di_densDepInfCohortDBH>"
       << "<di_ddicdVal species=\"Species_1\">0</di_ddicdVal>"
       << "<di_ddicdVal species=\"Species_2\">0</di_ddicdVal>"
       << "<di_ddicdVal species=\"Species_3\">0</di_ddicdVal>"
       << "<di_ddicdVal species=\"Species_4\">0</di_ddicdVal>"
       << "</di_densDepInfCohortDBH>"
       << "<di_densDepInfPropResistant>"
       << "<di_ddiprVal species=\"Species_1\">0</di_ddiprVal>"
       << "<di_ddiprVal species=\"Species_2\">0</di_ddiprVal>"
       << "<di_ddiprVal species=\"Species_3\">0</di_ddiprVal>"
       << "<di_ddiprVal species=\"Species_4\">0</di_ddiprVal>"
       << "</di_densDepInfPropResistant>"
       << "<di_densDepInfPropCondSusceptible>"
       << "<di_ddipcsVal species=\"Species_1\">0</di_ddipcsVal>"
       << "<di_ddipcsVal species=\"Species_2\">0</di_ddipcsVal>"
       << "<di_ddipcsVal species=\"Species_3\">0</di_ddipcsVal>"
       << "<di_ddipcsVal species=\"Species_4\">0</di_ddipcsVal>"
       << "</di_densDepInfPropCondSusceptible>"
       << "<di_densDepInfStartYear>2</di_densDepInfStartYear>"
       << "</DensDepInfestation1>"

       << "<NCIMasterGrowth2>"
       << "<nciWhichShadingEffect>" << no_shading << "</nciWhichShadingEffect>"
       << "<nciWhichCrowdingEffect>" << no_crowding_effect << "</nciWhichCrowdingEffect>"
       << "<nciWhichNCITerm>" << no_nci_term << "</nciWhichNCITerm>"
       << "<nciWhichSizeEffect>" << size_effect_shifted_log_inf << "</nciWhichSizeEffect>"
       << "<nciWhichDamageEffect>" << no_damage_effect << "</nciWhichDamageEffect>"
       << "<nciWhichPrecipitationEffect>" << no_precip_effect << "</nciWhichPrecipitationEffect>"
       << "<nciWhichTemperatureEffect>" << no_temp_effect << "</nciWhichTemperatureEffect>"
       << "<nciWhichNitrogenEffect>" << no_nitrogen_effect << "</nciWhichNitrogenEffect>"
       << "<nciWhichInfectionEffect>" << no_infection_effect << "</nciWhichInfectionEffect>"
       << "<gr_stochGrowthMethod>" << deterministic_pdf << "</gr_stochGrowthMethod>"
       << "<gr_nciMaxPotentialGrowth>"
       << "<gr_nmpgVal species=\"Species_1\">12</gr_nmpgVal>"
       << "<gr_nmpgVal species=\"Species_2\">12</gr_nmpgVal>"
       << "<gr_nmpgVal species=\"Species_3\">15</gr_nmpgVal>"
       << "<gr_nmpgVal species=\"Species_4\">15</gr_nmpgVal>"
       << "</gr_nciMaxPotentialGrowth>"
       << "<nciSizeEffectX0>"
       << "<nsex0Val species=\"Species_1\">36.85</nsex0Val>"
       << "<nsex0Val species=\"Species_2\">36.85</nsex0Val>"
       << "<nsex0Val species=\"Species_3\">4.16</nsex0Val>"
       << "<nsex0Val species=\"Species_4\">4.16</nsex0Val>"
       << "</nciSizeEffectX0>"
       << "<nciSizeEffectXb>"
       << "<nsexbVal species=\"Species_1\">2.27</nsexbVal>"
       << "<nsexbVal species=\"Species_2\">2.27</nsexbVal>"
       << "<nsexbVal species=\"Species_3\">1.44</nsexbVal>"
       << "<nsexbVal species=\"Species_4\">1.44</nsexbVal>"
       << "</nciSizeEffectXb>"
       << "<nciSizeEffectXp>"
       << "<nsexpVal species=\"Species_1\">0.23</nsexpVal>"
       << "<nsexpVal species=\"Species_2\">0.23</nsexpVal>"
       << "<nsexpVal species=\"Species_3\">0.005</nsexpVal>"
       << "<nsexpVal species=\"Species_4\">0.005</nsexpVal>"
       << "</nciSizeEffectXp>"
       << "<nciSizeEffectInfX0>"
       << "<nseix0Val species=\"Species_1\">215.21</nseix0Val>"
       << "<nseix0Val species=\"Species_2\">215.21</nseix0Val>"
       << "<nseix0Val species=\"Species_3\">420.11</nseix0Val>"
       << "<nseix0Val species=\"Species_4\">420.11</nseix0Val>"
       << "</nciSizeEffectInfX0>"
       << "<nciSizeEffectInfXb>"
       << "<nseixbVal species=\"Species_1\">1.55</nseixbVal>"
       << "<nseixbVal species=\"Species_2\">1.55</nseixbVal>"
       << "<nseixbVal species=\"Species_3\">1</nseixbVal>"
       << "<nseixbVal species=\"Species_4\">1</nseixbVal>"
       << "</nciSizeEffectInfXb>"
       << "<nciSizeEffectInfXp>"
       << "<nseixpVal species=\"Species_1\">0</nseixpVal>"
       << "<nseixpVal species=\"Species_2\">0</nseixpVal>"
       << "<nseixpVal species=\"Species_3\">16.19</nseixpVal>"
       << "<nseixpVal species=\"Species_4\">16.19</nseixpVal>"
       << "</nciSizeEffectInfXp>"
       << "<nciSizeEffectLowerBound>"
       << "<nselbVal species=\"Species_1\">0</nselbVal>"
       << "<nselbVal species=\"Species_2\">0</nselbVal>"
       << "<nselbVal species=\"Species_3\">15</nselbVal>"
       << "<nselbVal species=\"Species_4\">15</nselbVal>"
       << "</nciSizeEffectLowerBound>"
       << "</NCIMasterGrowth2>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteNCIPestGrowthXMLFile4()
////////////////////////////////////////////////////////////////////////////
const char* WriteNCIPestGrowthXMLFile4() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  //Write file
  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06010101\">"
       << "<plot>"
       << "<timesteps>3</timesteps>"
       << "<yearsPerTimestep>1</yearsPerTimestep>"
       << "<randomSeed>1</randomSeed>"
       << "<plot_lenX>200.0</plot_lenX>"
       << "<plot_lenY>200.0</plot_lenY>"
       << "<plot_latitude>55.37</plot_latitude>"
       << "<plot_precip_mm_yr>1150.64</plot_precip_mm_yr>"
       << "<plot_temp_C>12.88</plot_temp_C>"
       << "<plot_n_dep>3.58</plot_n_dep>"
       << "<plot_seasonal_precipitation>34</plot_seasonal_precipitation>"
       << "<plot_water_deficit>456.2</plot_water_deficit>"
       << "</plot>";

  oOut << "<trees>"
       << "<tr_speciesList>"
       << "<tr_species speciesName=\"Species_1\" />"
       << "<tr_species speciesName=\"Species_2\" />"
       << "<tr_species speciesName=\"Species_3\" />"
       << "<tr_species speciesName=\"Species_4\" />"
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
       << "<tr_treemap>"
       << "<tm_treeSettings sp=\"Species_1\" tp=\"3\">"
       << "<tm_floatCodes>"
       << "<tm_floatCode label=\"X\">0</tm_floatCode>"
       << "<tm_floatCode label=\"Y\">1</tm_floatCode>"
       << "<tm_floatCode label=\"DBH\">2</tm_floatCode>"
       << "</tm_floatCodes>"
       << "</tm_treeSettings>"
       << "<tm_treeSettings sp=\"Species_2\" tp=\"3\">"
       << "<tm_floatCodes>"
       << "<tm_floatCode label=\"X\">0</tm_floatCode>"
       << "<tm_floatCode label=\"Y\">1</tm_floatCode>"
       << "<tm_floatCode label=\"DBH\">2</tm_floatCode>"
       << "</tm_floatCodes>"
       << "</tm_treeSettings>"
       << "<tm_treeSettings sp=\"Species_3\" tp=\"3\">"
       << "<tm_floatCodes>"
       << "<tm_floatCode label=\"X\">0</tm_floatCode>"
       << "<tm_floatCode label=\"Y\">1</tm_floatCode>"
       << "<tm_floatCode label=\"DBH\">2</tm_floatCode>"
       << "</tm_floatCodes>"
       << "</tm_treeSettings>"
       << "<tm_treeSettings sp=\"Species_4\" tp=\"3\">"
       << "<tm_floatCodes>"
       << "<tm_floatCode label=\"X\">0</tm_floatCode>"
       << "<tm_floatCode label=\"Y\">1</tm_floatCode>"
       << "<tm_floatCode label=\"DBH\">2</tm_floatCode>"
       << "</tm_floatCodes>"
       << "</tm_treeSettings>";
  for (int i = 0; i < 1000; i++) {
    oOut << "<tree sp=\"0\" tp=\"3\">"
         << "<fl c=\"0\">" << clModelMath::GetRand() * 99 << "</fl>" //X
         << "<fl c=\"1\">" << clModelMath::GetRand() * 99 << "</fl>" //Y
         << "<fl c=\"2\">20</fl>" //DBH
         << "</tree>";
  }
  for (int i = 0; i < 1000; i++) {
    oOut << "<tree sp=\"1\" tp=\"3\">"
         << "<fl c=\"0\">" << clModelMath::GetRand() * 99 << "</fl>" //X
         << "<fl c=\"1\">" << clModelMath::GetRand() * 99 << "</fl>" //Y
         << "<fl c=\"2\">30</fl>" //DBH
         << "</tree>";
  }
  for (int i = 0; i < 1000; i++) {
    oOut << "<tree sp=\"2\" tp=\"3\">"
         << "<fl c=\"0\">" << clModelMath::GetRand() * 99 << "</fl>" //X
         << "<fl c=\"1\">" << clModelMath::GetRand() * 99 << "</fl>" //Y
         << "<fl c=\"2\">15</fl>" //DBH
         << "</tree>";
  }
  for (int i = 0; i < 1000; i++) {
    oOut << "<tree sp=\"3\" tp=\"3\">"
         << "<fl c=\"0\">" << clModelMath::GetRand() * 99 << "</fl>" //X
         << "<fl c=\"1\">" << clModelMath::GetRand() * 99 << "</fl>" //Y
         << "<fl c=\"2\">45</fl>" //DBH
         << "</tree>";
  }
  oOut << "</tr_treemap>"
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
       << "<tr_soahVal species=\"Species_2\">0.0299</tr_soahVal>"
       << "<tr_soahVal species=\"Species_3\">0.0299</tr_soahVal>"
       << "<tr_soahVal species=\"Species_4\">0.0299</tr_soahVal>"
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
       << "<behaviorName>DensDepInfestation</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_4\" type=\"Adult\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>NCIMasterGrowth</behaviorName>"
       << "<version>3</version>"
       << "<listPosition>2</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_4\" type=\"Adult\"/>"
       << "</behavior>"
       << "</behaviorList>"

       << "<DensDepInfestation1>"
       << "<di_densDepInfMaxInfestation>0.5</di_densDepInfMaxInfestation>"
       << "<di_densDepInfA>-100</di_densDepInfA>"
       << "<di_densDepInfBx>0.3</di_densDepInfBx>"
       << "<di_densDepInfBy>0.2</di_densDepInfBy>"
       << "<di_densDepInfMinDBH>"
       << "<di_ddimdVal species=\"Species_1\">0</di_ddimdVal>"
       << "<di_ddimdVal species=\"Species_2\">0</di_ddimdVal>"
       << "<di_ddimdVal species=\"Species_3\">0</di_ddimdVal>"
       << "<di_ddimdVal species=\"Species_4\">0</di_ddimdVal>"
       << "</di_densDepInfMinDBH>"
       << "<di_densDepInfCohortDBH>"
       << "<di_ddicdVal species=\"Species_1\">0</di_ddicdVal>"
       << "<di_ddicdVal species=\"Species_2\">0</di_ddicdVal>"
       << "<di_ddicdVal species=\"Species_3\">0</di_ddicdVal>"
       << "<di_ddicdVal species=\"Species_4\">0</di_ddicdVal>"
       << "</di_densDepInfCohortDBH>"
       << "<di_densDepInfPropResistant>"
       << "<di_ddiprVal species=\"Species_1\">0</di_ddiprVal>"
       << "<di_ddiprVal species=\"Species_2\">0</di_ddiprVal>"
       << "<di_ddiprVal species=\"Species_3\">0</di_ddiprVal>"
       << "<di_ddiprVal species=\"Species_4\">0</di_ddiprVal>"
       << "</di_densDepInfPropResistant>"
       << "<di_densDepInfPropCondSusceptible>"
       << "<di_ddipcsVal species=\"Species_1\">0</di_ddipcsVal>"
       << "<di_ddipcsVal species=\"Species_2\">0</di_ddipcsVal>"
       << "<di_ddipcsVal species=\"Species_3\">0</di_ddipcsVal>"
       << "<di_ddipcsVal species=\"Species_4\">0</di_ddipcsVal>"
       << "</di_densDepInfPropCondSusceptible>"
       << "<di_densDepInfStartYear>2</di_densDepInfStartYear>"
       << "</DensDepInfestation1>"

       << "<NCIMasterGrowth2>"
       << "<nciWhichShadingEffect>" << no_shading << "</nciWhichShadingEffect>"
       << "<nciWhichCrowdingEffect>" << no_crowding_effect << "</nciWhichCrowdingEffect>"
       << "<nciWhichNCITerm>" << no_nci_term << "</nciWhichNCITerm>"
       << "<nciWhichSizeEffect>" << size_effect_compound_exp_inf << "</nciWhichSizeEffect>"
       << "<nciWhichDamageEffect>" << no_damage_effect << "</nciWhichDamageEffect>"
       << "<nciWhichPrecipitationEffect>" << no_precip_effect << "</nciWhichPrecipitationEffect>"
       << "<nciWhichTemperatureEffect>" << no_temp_effect << "</nciWhichTemperatureEffect>"
       << "<nciWhichNitrogenEffect>" << no_nitrogen_effect << "</nciWhichNitrogenEffect>"
       << "<nciWhichInfectionEffect>" << no_infection_effect << "</nciWhichInfectionEffect>"
       << "<gr_stochGrowthMethod>" << deterministic_pdf << "</gr_stochGrowthMethod>"
       << "<gr_nciMaxPotentialGrowth>"
       << "<gr_nmpgVal species=\"Species_1\">12</gr_nmpgVal>"
       << "<gr_nmpgVal species=\"Species_2\">12</gr_nmpgVal>"
       << "<gr_nmpgVal species=\"Species_3\">15</gr_nmpgVal>"
       << "<gr_nmpgVal species=\"Species_4\">15</gr_nmpgVal>"
       << "</gr_nciMaxPotentialGrowth>"
       << "<nciSizeEffectA>"
       << "<nseaVal species=\"Species_1\">0.12</nseaVal>"
       << "<nseaVal species=\"Species_2\">0.12</nseaVal>"
       << "<nseaVal species=\"Species_3\">0.28</nseaVal>"
       << "<nseaVal species=\"Species_4\">0.28</nseaVal>"
       << "</nciSizeEffectA>"
       << "<nciSizeEffectB>"
       << "<nsebVal species=\"Species_1\">-6.89</nsebVal>"
       << "<nsebVal species=\"Species_2\">-6.89</nsebVal>"
       << "<nsebVal species=\"Species_3\">-13.11</nsebVal>"
       << "<nsebVal species=\"Species_4\">-13.11</nsebVal>"
       << "</nciSizeEffectB>"
       << "<nciSizeEffectC>"
       << "<nsecVal species=\"Species_1\">-0.093</nsecVal>"
       << "<nsecVal species=\"Species_2\">-0.093</nsecVal>"
       << "<nsecVal species=\"Species_3\">-0.5</nsecVal>"
       << "<nsecVal species=\"Species_4\">-0.5</nsecVal>"
       << "</nciSizeEffectC>"
       << "<nciSizeEffectD>"
       << "<nsedVal species=\"Species_1\">1</nsedVal>"
       << "<nsedVal species=\"Species_2\">1</nsedVal>"
       << "<nsedVal species=\"Species_3\">0.54</nsedVal>"
       << "<nsedVal species=\"Species_4\">0.54</nsedVal>"
       << "</nciSizeEffectD>"
       << "<nciSizeEffectInfA>"
       << "<nseiaVal species=\"Species_1\">0.12</nseiaVal>"
       << "<nseiaVal species=\"Species_2\">0.12</nseiaVal>"
       << "<nseiaVal species=\"Species_3\">0.19</nseiaVal>"
       << "<nseiaVal species=\"Species_4\">0.19</nseiaVal>"
       << "</nciSizeEffectInfA>"
       << "<nciSizeEffectInfB>"
       << "<nseibVal species=\"Species_1\">-6.89</nseibVal>"
       << "<nseibVal species=\"Species_2\">-6.89</nseibVal>"
       << "<nseibVal species=\"Species_3\">-6.43</nseibVal>"
       << "<nseibVal species=\"Species_4\">-6.43</nseibVal>"
       << "</nciSizeEffectInfB>"
       << "<nciSizeEffectInfC>"
       << "<nseicVal species=\"Species_1\">-0.52</nseicVal>"
       << "<nseicVal species=\"Species_2\">-0.52</nseicVal>"
       << "<nseicVal species=\"Species_3\">-4.5</nseicVal>"
       << "<nseicVal species=\"Species_4\">-4.5</nseicVal>"
       << "</nciSizeEffectInfC>"
       << "<nciSizeEffectInfD>"
       << "<nseidVal species=\"Species_1\">1.73</nseidVal>"
       << "<nseidVal species=\"Species_2\">1.73</nseidVal>"
       << "<nseidVal species=\"Species_3\">1</nseidVal>"
       << "<nseidVal species=\"Species_4\">1</nseidVal>"
       << "</nciSizeEffectInfD>"
       << "</NCIMasterGrowth2>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteNCIPestGrowthXMLErrorFile1()
////////////////////////////////////////////////////////////////////////////
const char* WriteNCIPestGrowthXMLErrorFile1() {
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
       << "<plot_lenX>200.0</plot_lenX>"
       << "<plot_lenY>200.0</plot_lenY>"
       << "<plot_latitude>55.37</plot_latitude>"
       << "<plot_precip_mm_yr>1150.64</plot_precip_mm_yr>"
       << "<plot_temp_C>12.88</plot_temp_C>"
       << "<plot_n_dep>3.58</plot_n_dep>"
       << "<plot_seasonal_precipitation>34</plot_seasonal_precipitation>"
       << "<plot_water_deficit>456.2</plot_water_deficit>"
       << "</plot>";

  oOut << "<trees>"
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

  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>DensDepInfestation</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>NCIMasterGrowth</behaviorName>"
       << "<version>3</version>"
       << "<listPosition>2</listPosition>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
       << "</behavior>"
       << "</behaviorList>"

       << "<DensDepInfestation1>"
       << "<di_densDepInfMaxInfestation>1</di_densDepInfMaxInfestation>"
       << "<di_densDepInfA>0.2</di_densDepInfA>"
       << "<di_densDepInfBx>0.3</di_densDepInfBx>"
       << "<di_densDepInfBy>0.2</di_densDepInfBy>"
       << "<di_densDepInfMinDBH>"
       << "<di_ddimdVal species=\"Species_1\">0</di_ddimdVal>"
       << "<di_ddimdVal species=\"Species_2\">0</di_ddimdVal>"
       << "</di_densDepInfMinDBH>"
       << "<di_densDepInfCohortDBH>"
       << "<di_ddicdVal species=\"Species_1\">0</di_ddicdVal>"
       << "<di_ddicdVal species=\"Species_2\">0</di_ddicdVal>"
       << "</di_densDepInfCohortDBH>"
       << "<di_densDepInfPropResistant>"
       << "<di_ddiprVal species=\"Species_1\">0</di_ddiprVal>"
       << "<di_ddiprVal species=\"Species_2\">0</di_ddiprVal>"
       << "</di_densDepInfPropResistant>"
       << "<di_densDepInfPropCondSusceptible>"
       << "<di_ddipcsVal species=\"Species_1\">0</di_ddipcsVal>"
       << "<di_ddipcsVal species=\"Species_2\">0</di_ddipcsVal>"
       << "</di_densDepInfPropCondSusceptible>"
       << "<di_densDepInfStartYear>5</di_densDepInfStartYear>"
       << "</DensDepInfestation1>"

       << "<NCIMasterGrowth2>"
       << "<nciWhichShadingEffect>0</nciWhichShadingEffect>"
       << "<nciWhichCrowdingEffect>0</nciWhichCrowdingEffect>"
       << "<nciWhichNCITerm>0</nciWhichNCITerm>"
       << "<nciWhichSizeEffect>0</nciWhichSizeEffect>"
       << "<nciWhichDamageEffect>0</nciWhichDamageEffect>"
       << "<nciWhichPrecipitationEffect>0</nciWhichPrecipitationEffect>"
       << "<nciWhichTemperatureEffect>0</nciWhichTemperatureEffect>"
       << "<nciWhichNitrogenEffect>0</nciWhichNitrogenEffect>"
       << "<nciWhichInfectionEffect>1</nciWhichInfectionEffect>"
       << "<gr_stochGrowthMethod>" << deterministic_pdf << "</gr_stochGrowthMethod>"
       << "<gr_nciMaxPotentialGrowth>"
       << "<gr_nmpgVal species=\"Species_1\">12</gr_nmpgVal>"
       << "<gr_nmpgVal species=\"Species_2\">15</gr_nmpgVal>"
       << "</gr_nciMaxPotentialGrowth>"
       << "<nciInfectionEffectA>"
       << "<nieaVal species=\"Species_1\">0.1</nieaVal>"
       << "<nieaVal species=\"Species_2\">0.2</nieaVal>"
       << "</nciInfectionEffectA>"
       << "<nciInfectionEffectB>"
       << "<niebVal species=\"Species_1\">0.4</niebVal>"
       << "<niebVal species=\"Species_2\">0.7</niebVal>"
       << "</nciInfectionEffectB>"
       << "</NCIMasterGrowth2>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteNCIPestGrowthXMLErrorFile2()
////////////////////////////////////////////////////////////////////////////
const char* WriteNCIPestGrowthXMLErrorFile2() {
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
       << "<plot_lenX>200.0</plot_lenX>"
       << "<plot_lenY>200.0</plot_lenY>"
       << "<plot_latitude>55.37</plot_latitude>"
       << "<plot_precip_mm_yr>1150.64</plot_precip_mm_yr>"
       << "<plot_temp_C>12.88</plot_temp_C>"
       << "<plot_n_dep>3.58</plot_n_dep>"
       << "<plot_seasonal_precipitation>34</plot_seasonal_precipitation>"
       << "<plot_water_deficit>456.2</plot_water_deficit>"
       << "</plot>";

  oOut << "<trees>"
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

  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>DensDepInfestation</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>NCIMasterGrowth</behaviorName>"
       << "<version>3</version>"
       << "<listPosition>2</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "</behavior>"
       << "</behaviorList>"

       << "<DensDepInfestation1>"
       << "<di_densDepInfMaxInfestation>1</di_densDepInfMaxInfestation>"
       << "<di_densDepInfA>0.2</di_densDepInfA>"
       << "<di_densDepInfBx>0.3</di_densDepInfBx>"
       << "<di_densDepInfBy>0.2</di_densDepInfBy>"
       << "<di_densDepInfMinDBH>"
       << "<di_ddimdVal species=\"Species_1\">0</di_ddimdVal>"
       << "<di_ddimdVal species=\"Species_2\">0</di_ddimdVal>"
       << "</di_densDepInfMinDBH>"
       << "<di_densDepInfCohortDBH>"
       << "<di_ddicdVal species=\"Species_1\">0</di_ddicdVal>"
       << "<di_ddicdVal species=\"Species_2\">0</di_ddicdVal>"
       << "</di_densDepInfCohortDBH>"
       << "<di_densDepInfPropResistant>"
       << "<di_ddiprVal species=\"Species_1\">0</di_ddiprVal>"
       << "<di_ddiprVal species=\"Species_2\">0</di_ddiprVal>"
       << "</di_densDepInfPropResistant>"
       << "<di_densDepInfPropCondSusceptible>"
       << "<di_ddipcsVal species=\"Species_1\">0</di_ddipcsVal>"
       << "<di_ddipcsVal species=\"Species_2\">0</di_ddipcsVal>"
       << "</di_densDepInfPropCondSusceptible>"
       << "<di_densDepInfStartYear>-5</di_densDepInfStartYear>"
       << "</DensDepInfestation1>"

       << "<NCIMasterGrowth2>"
       << "<nciWhichShadingEffect>0</nciWhichShadingEffect>"
       << "<nciWhichCrowdingEffect>0</nciWhichCrowdingEffect>"
       << "<nciWhichNCITerm>0</nciWhichNCITerm>"
       << "<nciWhichSizeEffect>0</nciWhichSizeEffect>"
       << "<nciWhichDamageEffect>0</nciWhichDamageEffect>"
       << "<nciWhichPrecipitationEffect>0</nciWhichPrecipitationEffect>"
       << "<nciWhichTemperatureEffect>0</nciWhichTemperatureEffect>"
       << "<nciWhichNitrogenEffect>0</nciWhichNitrogenEffect>"
       << "<nciWhichInfectionEffect>2</nciWhichInfectionEffect>"
       << "<gr_stochGrowthMethod>" << deterministic_pdf << "</gr_stochGrowthMethod>"
       << "<gr_nciMaxPotentialGrowth>"
       << "<gr_nmpgVal species=\"Species_1\">12</gr_nmpgVal>"
       << "<gr_nmpgVal species=\"Species_2\">15</gr_nmpgVal>"
       << "</gr_nciMaxPotentialGrowth>"
       << "<nciInfectionEffectA>"
       << "<nieaVal species=\"Species_1\">0.1</nieaVal>"
       << "<nieaVal species=\"Species_2\">0.2</nieaVal>"
       << "</nciInfectionEffectA>"
       << "<nciInfectionEffectB>"
       << "<niebVal species=\"Species_1\">0.4</niebVal>"
       << "<niebVal species=\"Species_2\">0.7</niebVal>"
       << "</nciInfectionEffectB>"
       << "<nciInfectionEffectX0>"
       << "<niex0Val species=\"Species_1\">0</niex0Val>"
       << "<niex0Val species=\"Species_2\">6</niex0Val>"
       << "</nciInfectionEffectX0>"
       << "<nciInfectionEffectXb>"
       << "<niexbVal species=\"Species_1\">1</niexbVal>"
       << "<niexbVal species=\"Species_2\">5</niexbVal>"
       << "</nciInfectionEffectXb>"
       << "<nciInfectionEffectXp>"
       << "<niexpVal species=\"Species_1\">10</niexpVal>"
       << "<niexpVal species=\"Species_2\">4</niexpVal>"
       << "</nciInfectionEffectXp>"
       << "</NCIMasterGrowth2>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteNCIPestGrowthXMLErrorFile3()
////////////////////////////////////////////////////////////////////////////
const char* WriteNCIPestGrowthXMLErrorFile3() {
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
       << "<plot_lenX>200.0</plot_lenX>"
       << "<plot_lenY>200.0</plot_lenY>"
       << "<plot_latitude>55.37</plot_latitude>"
       << "<plot_precip_mm_yr>1150.64</plot_precip_mm_yr>"
       << "<plot_temp_C>12.88</plot_temp_C>"
       << "<plot_n_dep>3.58</plot_n_dep>"
       << "<plot_seasonal_precipitation>34</plot_seasonal_precipitation>"
       << "<plot_water_deficit>456.2</plot_water_deficit>"
       << "</plot>";

  oOut << "<trees>"
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

  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>DensDepInfestation</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>NCIMasterGrowth</behaviorName>"
       << "<version>3</version>"
       << "<listPosition>2</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "</behavior>"
       << "</behaviorList>"

       << "<DensDepInfestation1>"
       << "<di_densDepInfMaxInfestation>1</di_densDepInfMaxInfestation>"
       << "<di_densDepInfA>0.2</di_densDepInfA>"
       << "<di_densDepInfBx>0.3</di_densDepInfBx>"
       << "<di_densDepInfBy>0.2</di_densDepInfBy>"
       << "<di_densDepInfMinDBH>"
       << "<di_ddimdVal species=\"Species_1\">0</di_ddimdVal>"
       << "<di_ddimdVal species=\"Species_2\">0</di_ddimdVal>"
       << "</di_densDepInfMinDBH>"
       << "<di_densDepInfCohortDBH>"
       << "<di_ddicdVal species=\"Species_1\">0</di_ddicdVal>"
       << "<di_ddicdVal species=\"Species_2\">0</di_ddicdVal>"
       << "</di_densDepInfCohortDBH>"
       << "<di_densDepInfPropResistant>"
       << "<di_ddiprVal species=\"Species_1\">0</di_ddiprVal>"
       << "<di_ddiprVal species=\"Species_2\">0</di_ddiprVal>"
       << "</di_densDepInfPropResistant>"
       << "<di_densDepInfPropCondSusceptible>"
       << "<di_ddipcsVal species=\"Species_1\">0</di_ddipcsVal>"
       << "<di_ddipcsVal species=\"Species_2\">0</di_ddipcsVal>"
       << "</di_densDepInfPropCondSusceptible>"
       << "<di_densDepInfStartYear>-5</di_densDepInfStartYear>"
       << "</DensDepInfestation1>"

       << "<NCIMasterGrowth2>"
       << "<nciWhichShadingEffect>0</nciWhichShadingEffect>"
       << "<nciWhichCrowdingEffect>0</nciWhichCrowdingEffect>"
       << "<nciWhichNCITerm>0</nciWhichNCITerm>"
       << "<nciWhichSizeEffect>0</nciWhichSizeEffect>"
       << "<nciWhichDamageEffect>0</nciWhichDamageEffect>"
       << "<nciWhichPrecipitationEffect>0</nciWhichPrecipitationEffect>"
       << "<nciWhichTemperatureEffect>0</nciWhichTemperatureEffect>"
       << "<nciWhichNitrogenEffect>0</nciWhichNitrogenEffect>"
       << "<nciWhichInfectionEffect>2</nciWhichInfectionEffect>"
       << "<gr_stochGrowthMethod>" << deterministic_pdf << "</gr_stochGrowthMethod>"
       << "<gr_nciMaxPotentialGrowth>"
       << "<gr_nmpgVal species=\"Species_1\">12</gr_nmpgVal>"
       << "<gr_nmpgVal species=\"Species_2\">15</gr_nmpgVal>"
       << "</gr_nciMaxPotentialGrowth>"
       << "<nciInfectionEffectA>"
       << "<nieaVal species=\"Species_1\">0.1</nieaVal>"
       << "<nieaVal species=\"Species_2\">0.2</nieaVal>"
       << "</nciInfectionEffectA>"
       << "<nciInfectionEffectB>"
       << "<niebVal species=\"Species_1\">0.4</niebVal>"
       << "<niebVal species=\"Species_2\">0.7</niebVal>"
       << "</nciInfectionEffectB>"
       << "<nciInfectionEffectX0>"
       << "<niex0Val species=\"Species_1\">10</niex0Val>"
       << "<niex0Val species=\"Species_2\">6</niex0Val>"
       << "</nciInfectionEffectX0>"
       << "<nciInfectionEffectXb>"
       << "<niexbVal species=\"Species_1\">1</niexbVal>"
       << "<niexbVal species=\"Species_2\">0</niexbVal>"
       << "</nciInfectionEffectXb>"
       << "<nciInfectionEffectXp>"
       << "<niexpVal species=\"Species_1\">10</niexpVal>"
       << "<niexpVal species=\"Species_2\">4</niexpVal>"
       << "</nciInfectionEffectXp>"
       << "</NCIMasterGrowth2>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteNCIPestGrowthXMLErrorFile4()
////////////////////////////////////////////////////////////////////////////
const char* WriteNCIPestGrowthXMLErrorFile4() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  //Write file
  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06010101\">"
       << "<plot>"
       << "<timesteps>3</timesteps>"
       << "<yearsPerTimestep>1</yearsPerTimestep>"
       << "<randomSeed>1</randomSeed>"
       << "<plot_lenX>200.0</plot_lenX>"
       << "<plot_lenY>200.0</plot_lenY>"
       << "<plot_latitude>55.37</plot_latitude>"
       << "<plot_precip_mm_yr>1150.64</plot_precip_mm_yr>"
       << "<plot_temp_C>12.88</plot_temp_C>"
       << "<plot_n_dep>3.58</plot_n_dep>"
       << "<plot_seasonal_precipitation>34</plot_seasonal_precipitation>"
       << "<plot_water_deficit>456.2</plot_water_deficit>"
       << "</plot>";

  oOut << "<trees>"
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

  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>DensDepInfestation</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>NCIMasterGrowth</behaviorName>"
       << "<version>3</version>"
       << "<listPosition>2</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "</behavior>"
       << "</behaviorList>"

       << "<DensDepInfestation1>"
       << "<di_densDepInfMaxInfestation>0.5</di_densDepInfMaxInfestation>"
       << "<di_densDepInfA>-100</di_densDepInfA>"
       << "<di_densDepInfBx>0.3</di_densDepInfBx>"
       << "<di_densDepInfBy>0.2</di_densDepInfBy>"
       << "<di_densDepInfMinDBH>"
       << "<di_ddimdVal species=\"Species_1\">0</di_ddimdVal>"
       << "<di_ddimdVal species=\"Species_2\">0</di_ddimdVal>"
       << "</di_densDepInfMinDBH>"
       << "<di_densDepInfCohortDBH>"
       << "<di_ddicdVal species=\"Species_1\">0</di_ddicdVal>"
       << "<di_ddicdVal species=\"Species_2\">0</di_ddicdVal>"
       << "</di_densDepInfCohortDBH>"
       << "<di_densDepInfPropResistant>"
       << "<di_ddiprVal species=\"Species_1\">0</di_ddiprVal>"
       << "<di_ddiprVal species=\"Species_2\">0</di_ddiprVal>"
       << "</di_densDepInfPropResistant>"
       << "<di_densDepInfPropCondSusceptible>"
       << "<di_ddipcsVal species=\"Species_1\">0</di_ddipcsVal>"
       << "<di_ddipcsVal species=\"Species_2\">0</di_ddipcsVal>"
       << "</di_densDepInfPropCondSusceptible>"
       << "<di_densDepInfStartYear>2</di_densDepInfStartYear>"
       << "</DensDepInfestation1>"

       << "<NCIMasterGrowth2>"
       << "<nciWhichShadingEffect>" << no_shading << "</nciWhichShadingEffect>"
       << "<nciWhichCrowdingEffect>" << no_crowding_effect << "</nciWhichCrowdingEffect>"
       << "<nciWhichNCITerm>" << no_nci_term << "</nciWhichNCITerm>"
       << "<nciWhichSizeEffect>" << size_effect_shifted_log_inf << "</nciWhichSizeEffect>"
       << "<nciWhichDamageEffect>" << no_damage_effect << "</nciWhichDamageEffect>"
       << "<nciWhichPrecipitationEffect>" << no_precip_effect << "</nciWhichPrecipitationEffect>"
       << "<nciWhichTemperatureEffect>" << no_temp_effect << "</nciWhichTemperatureEffect>"
       << "<nciWhichNitrogenEffect>" << no_nitrogen_effect << "</nciWhichNitrogenEffect>"
       << "<nciWhichInfectionEffect>" << no_infection_effect << "</nciWhichInfectionEffect>"
       << "<gr_stochGrowthMethod>" << deterministic_pdf << "</gr_stochGrowthMethod>"
       << "<gr_nciMaxPotentialGrowth>"
       << "<gr_nmpgVal species=\"Species_1\">12</gr_nmpgVal>"
       << "<gr_nmpgVal species=\"Species_2\">12</gr_nmpgVal>"
       << "</gr_nciMaxPotentialGrowth>"
       << "<nciSizeEffectX0>"
       << "<nsex0Val species=\"Species_1\">36.85</nsex0Val>"
       << "<nsex0Val species=\"Species_2\">36.85</nsex0Val>"
       << "</nciSizeEffectX0>"
       << "<nciSizeEffectXb>"
       << "<nsexbVal species=\"Species_1\">2.27</nsexbVal>"
       << "<nsexbVal species=\"Species_2\">2.27</nsexbVal>"
       << "</nciSizeEffectXb>"
       << "<nciSizeEffectXp>"
       << "<nsexpVal species=\"Species_1\">0.23</nsexpVal>"
       << "<nsexpVal species=\"Species_2\">0.23</nsexpVal>"
       << "</nciSizeEffectXp>"
       << "<nciSizeEffectInfX0>"
       << "<nseix0Val species=\"Species_1\">215.21</nseix0Val>"
       << "<nseix0Val species=\"Species_2\">215.21</nseix0Val>"
       << "</nciSizeEffectInfX0>"
       << "<nciSizeEffectInfXb>"
       << "<nseixbVal species=\"Species_1\">1.55</nseixbVal>"
       << "<nseixbVal species=\"Species_2\">1.55</nseixbVal>"
       << "</nciSizeEffectInfXb>"
       << "<nciSizeEffectInfXp>"
       << "<nseixpVal species=\"Species_1\">0</nseixpVal>"
       << "<nseixpVal species=\"Species_2\">0</nseixpVal>"
       << "</nciSizeEffectInfXp>"
       << "<nciSizeEffectLowerBound>"
       << "<nselbVal species=\"Species_1\">0</nselbVal>"
       << "<nselbVal species=\"Species_2\">0</nselbVal>"
       << "</nciSizeEffectLowerBound>"
       << "</NCIMasterGrowth2>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteNCIPestGrowthXMLErrorFile5()
////////////////////////////////////////////////////////////////////////////
const char* WriteNCIPestGrowthXMLErrorFile5() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  //Write file
  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06010101\">"
       << "<plot>"
       << "<timesteps>3</timesteps>"
       << "<yearsPerTimestep>1</yearsPerTimestep>"
       << "<randomSeed>1</randomSeed>"
       << "<plot_lenX>200.0</plot_lenX>"
       << "<plot_lenY>200.0</plot_lenY>"
       << "<plot_latitude>55.37</plot_latitude>"
       << "<plot_precip_mm_yr>1150.64</plot_precip_mm_yr>"
       << "<plot_temp_C>12.88</plot_temp_C>"
       << "<plot_n_dep>3.58</plot_n_dep>"
       << "<plot_seasonal_precipitation>34</plot_seasonal_precipitation>"
       << "<plot_water_deficit>456.2</plot_water_deficit>"
       << "</plot>";

  oOut << "<trees>"
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

  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>DensDepInfestation</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>NCIMasterGrowth</behaviorName>"
       << "<version>3</version>"
       << "<listPosition>2</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "</behavior>"
       << "</behaviorList>"

       << "<DensDepInfestation1>"
       << "<di_densDepInfMaxInfestation>0.5</di_densDepInfMaxInfestation>"
       << "<di_densDepInfA>-100</di_densDepInfA>"
       << "<di_densDepInfBx>0.3</di_densDepInfBx>"
       << "<di_densDepInfBy>0.2</di_densDepInfBy>"
       << "<di_densDepInfMinDBH>"
       << "<di_ddimdVal species=\"Species_1\">0</di_ddimdVal>"
       << "<di_ddimdVal species=\"Species_2\">0</di_ddimdVal>"
       << "</di_densDepInfMinDBH>"
       << "<di_densDepInfCohortDBH>"
       << "<di_ddicdVal species=\"Species_1\">0</di_ddicdVal>"
       << "<di_ddicdVal species=\"Species_2\">0</di_ddicdVal>"
       << "</di_densDepInfCohortDBH>"
       << "<di_densDepInfPropResistant>"
       << "<di_ddiprVal species=\"Species_1\">0</di_ddiprVal>"
       << "<di_ddiprVal species=\"Species_2\">0</di_ddiprVal>"
       << "</di_densDepInfPropResistant>"
       << "<di_densDepInfPropCondSusceptible>"
       << "<di_ddipcsVal species=\"Species_1\">0</di_ddipcsVal>"
       << "<di_ddipcsVal species=\"Species_2\">0</di_ddipcsVal>"
       << "</di_densDepInfPropCondSusceptible>"
       << "<di_densDepInfStartYear>2</di_densDepInfStartYear>"
       << "</DensDepInfestation1>"

       << "<NCIMasterGrowth2>"
       << "<nciWhichShadingEffect>" << no_shading << "</nciWhichShadingEffect>"
       << "<nciWhichCrowdingEffect>" << no_crowding_effect << "</nciWhichCrowdingEffect>"
       << "<nciWhichNCITerm>" << no_nci_term << "</nciWhichNCITerm>"
       << "<nciWhichSizeEffect>" << size_effect_compound_exp_inf << "</nciWhichSizeEffect>"
       << "<nciWhichDamageEffect>" << no_damage_effect << "</nciWhichDamageEffect>"
       << "<nciWhichPrecipitationEffect>" << no_precip_effect << "</nciWhichPrecipitationEffect>"
       << "<nciWhichTemperatureEffect>" << no_temp_effect << "</nciWhichTemperatureEffect>"
       << "<nciWhichNitrogenEffect>" << no_nitrogen_effect << "</nciWhichNitrogenEffect>"
       << "<nciWhichInfectionEffect>" << no_infection_effect << "</nciWhichInfectionEffect>"
       << "<gr_stochGrowthMethod>" << deterministic_pdf << "</gr_stochGrowthMethod>"
       << "<gr_nciMaxPotentialGrowth>"
       << "<gr_nmpgVal species=\"Species_1\">12</gr_nmpgVal>"
       << "<gr_nmpgVal species=\"Species_2\">12</gr_nmpgVal>"
       << "</gr_nciMaxPotentialGrowth>"
       << "<nciSizeEffectA>"
       << "<nseaVal species=\"Species_1\">0.12</nseaVal>"
       << "<nseaVal species=\"Species_2\">0.12</nseaVal>"
       << "</nciSizeEffectA>"
       << "<nciSizeEffectB>"
       << "<nsebVal species=\"Species_1\">-6.89</nsebVal>"
       << "<nsebVal species=\"Species_2\">-6.89</nsebVal>"
       << "</nciSizeEffectB>"
       << "<nciSizeEffectC>"
       << "<nsecVal species=\"Species_1\">-0.093</nsecVal>"
       << "<nsecVal species=\"Species_2\">-0.093</nsecVal>"
       << "</nciSizeEffectC>"
       << "<nciSizeEffectD>"
       << "<nsedVal species=\"Species_1\">1</nsedVal>"
       << "<nsedVal species=\"Species_2\">1</nsedVal>"
       << "</nciSizeEffectD>"
       << "<nciSizeEffectInfA>"
       << "<nseiaVal species=\"Species_1\">0.12</nseiaVal>"
       << "<nseiaVal species=\"Species_2\">0.12</nseiaVal>"
       << "</nciSizeEffectInfA>"
       << "<nciSizeEffectInfB>"
       << "<nseibVal species=\"Species_1\">-6.89</nseibVal>"
       << "<nseibVal species=\"Species_2\">-6.89</nseibVal>"
       << "</nciSizeEffectInfB>"
       << "<nciSizeEffectInfC>"
       << "<nseicVal species=\"Species_1\">-0.52</nseicVal>"
       << "<nseicVal species=\"Species_2\">-0.52</nseicVal>"
       << "</nciSizeEffectInfC>"
       << "<nciSizeEffectInfD>"
       << "<nseidVal species=\"Species_1\">1.73</nseidVal>"
       << "<nseidVal species=\"Species_2\">1.73</nseidVal>"
       << "</nciSizeEffectInfD>"
       << "</NCIMasterGrowth2>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}
