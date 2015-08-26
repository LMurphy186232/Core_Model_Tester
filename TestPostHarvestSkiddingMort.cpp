//---------------------------------------------------------------------------
// TestPostHarvestSkiddingMort.cpp
//---------------------------------------------------------------------------
#include "TestPostHarvestSkiddingMort.h"
#include <gtest/gtest.h>
#include "SimManager.h"
#include "TreePopulation.h"
#include "BehaviorBase.h"
#include "Grid.h"
#include <fstream>
#include <math.h>

/////////////////////////////////////////////////////////////////////////////
// TestPostHarvestSkiddingMort()
// Tests the post-harvest skidding mortality class.
//
// -- 2000 trees are created in each of 5 different grid cells.
// -- Cells 1-3 were cut this timestep, cell 4 was not cut, and cell 5 was cut
//    6 years earlier.
// -- Cell 2 has higher harvest intensity than cell 1.
// -- Cell 3 has larger trees than cell 1.
// -- Simulation is run for 1 2-y timestep.
// -- A second run is performed where the HarvInten code is not registered.
//    It is otherwise the same as run 1, cell 1. The behavior should treat
//    HarvInten as having a value of 0.
// -- The number of trees of each species remaining in each cell is compared to
//    expected values (+/- 5%).
/////////////////////////////////////////////////////////////////////////////
TEST(PostHarvestSkiddingMort, TestPostHarvestSkiddingMortRun1) {
  clTreePopulation * p_oPop;
  clTreeSearch *p_oAllTrees;
  clTree *p_oTree;
  clGrid *p_oTimeSinceHarvestGrid;
  clGrid *p_oHarvestResultsGrid;
  int *p_iTreeCount;
  int i, iTimeCode, iUpdatedCode, iHarvIntenCode, iSp, iHarvestTypeCode, iXCode;
  short int iX,iY;
  float fCellLength, fTreeX;

  //Create the sim manager and load our file
  clSimManager *p_oSimManager = new clSimManager(7, 1, "");
  try {
    //Set up our tree count array
    p_iTreeCount = new int [5];
    for (i = 0; i < 5; i++) {
      p_iTreeCount[i] = 0;
    }

    p_oSimManager->ReadFile( WritePostHarvestSkiddingMortXMLFile1(1) );
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );

    fCellLength = p_oPop->GetGridCellSize();

    //Set-up the harvest results grid
    p_oHarvestResultsGrid = p_oSimManager->GetGridObject("Harvest Results");

    iHarvestTypeCode = p_oHarvestResultsGrid->GetIntDataCode("Harvest Type");

    //initialize with value of -1, no harvest this timestep
    for (i=0;i<5;i++)
      p_oHarvestResultsGrid->SetValueOfCell( i, 0, iHarvestTypeCode, -1);


    //Set-up the time since harvest grid
    p_oTimeSinceHarvestGrid = p_oSimManager->GetGridObject( "Years Since Last Harvest" );

    //register the data members
    iTimeCode = p_oTimeSinceHarvestGrid->GetIntDataCode( "Time" );
    iUpdatedCode = p_oTimeSinceHarvestGrid->GetIntDataCode( "LastUpdated" );


    //initialize with values
    p_oTimeSinceHarvestGrid->SetValueOfCell( 0, 0, iTimeCode, 0);
    p_oTimeSinceHarvestGrid->SetValueOfCell( 1, 0, iTimeCode, 0);
    p_oTimeSinceHarvestGrid->SetValueOfCell( 2, 0, iTimeCode, 0);
    p_oTimeSinceHarvestGrid->SetValueOfCell( 3, 0, iTimeCode, 1000);
    p_oTimeSinceHarvestGrid->SetValueOfCell( 4, 0, iTimeCode, 6);

    for (i=0;i<5;i++)
      p_oTimeSinceHarvestGrid->SetValueOfCell( i, 0, iUpdatedCode, 0);

    iSp = p_oPop->TranslateSpeciesNameToCode("sp1");

    iXCode = p_oPop->GetXCode(iSp, clTreePopulation::adult);

    //Register code for HarvInten
    iHarvIntenCode = p_oPop->GetFloatDataCode("HarvInten",iSp,clTreePopulation::adult);


    //Create 2000 identical trees in each of 5 cells
    for (i = 0; i < 2000; i++) {
      p_oTree = p_oPop->CreateTree(0*fCellLength,0, iSp, clTreePopulation::adult, 10);
      p_oTree->SetValue(iHarvIntenCode,(float)3.0);
    }
    for (i = 0; i < 2000; i++) {
      p_oTree = p_oPop->CreateTree(1*fCellLength,0, iSp, clTreePopulation::adult, 10);
      p_oTree->SetValue(iHarvIntenCode,(float)10.0);
    }
    for (i = 0; i < 2000; i++) {
      p_oTree = p_oPop->CreateTree(2*fCellLength,0, iSp, clTreePopulation::adult, 20);
      p_oTree->SetValue(iHarvIntenCode,(float)3.0);
    }
    for (i = 0; i < 2000; i++) {
      p_oTree = p_oPop->CreateTree(3*fCellLength,0, iSp, clTreePopulation::adult, 10);
    }
    for (i = 0; i < 2000; i++) {
      p_oTree = p_oPop->CreateTree(4*fCellLength,0, iSp, clTreePopulation::adult, 10);
      p_oTree->SetValue(iHarvIntenCode,(float)10.0);
    }


    //Run for one timestep
    p_oSimManager->RunSim(1);


    //Count the remaining trees
    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {
      if (p_oTree->GetType()==clTreePopulation::adult) {
        p_oTree->GetValue(iXCode, &fTreeX);
        p_oTimeSinceHarvestGrid->GetCellOfPoint(fTreeX,(float)0.0,&iX, &iY);
        p_iTreeCount[iX]++;

      }

      p_oTree = p_oAllTrees->NextTree();
    }


    //Make sure they are as expected

    //cell 0
    EXPECT_LT(fabs(1.0*p_iTreeCount[0] - 1138.1) / (1.0*p_iTreeCount[0]), 0.05);
    //cell 1
    EXPECT_LT(fabs(1.0*p_iTreeCount[1] - 935.2) / (1.0*p_iTreeCount[0]), 0.05);
    //cell 2
    EXPECT_LT(fabs(1.0*p_iTreeCount[2] - 1001.1) / (1.0*p_iTreeCount[0]), 0.05);
    //cell 3
    EXPECT_LT(fabs(1.0*p_iTreeCount[3] - 1620.0) / (1.0*p_iTreeCount[0]), 0.05);
    //cell 4
    EXPECT_LT(fabs(1.0*p_iTreeCount[4] - 1359.5) / (1.0*p_iTreeCount[0]), 0.05);
    //Cleanup
    delete[] p_iTreeCount;
    delete p_oSimManager;
  } catch (modelErr &e) {
    delete[] p_iTreeCount;
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}




TEST(PostHarvestSkiddingMort, TestPostHarvestSkiddingMortRun2) {
  clTreePopulation * p_oPop;
  clTreeSearch *p_oAllTrees;
  clTree *p_oTree;
  clGrid *p_oTimeSinceHarvestGrid;
  clGrid *p_oHarvestResultsGrid;
  int *p_iTreeCount;
  int i, iTimeCode, iUpdatedCode, iSp, iHarvestTypeCode, iXCode;
  short int iX,iY;
  float fCellLength, fTreeX;

  //Create the sim manager and load our file
  clSimManager *p_oSimManager = new clSimManager(7, 1, "");
  try {
    //Set up our tree count array
    p_iTreeCount = new int [5];
    for (i = 0; i < 5; i++) {
      p_iTreeCount[i] = 0;
    }
    p_oSimManager->ReadFile( WritePostHarvestSkiddingMortXMLFile1(2) );
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );
    fCellLength = p_oPop->GetGridCellSize();

    //Reset up our tree count array
    for (i = 0; i < 5; i++) {
      p_iTreeCount[i] = 0;
    }

    //Set-up the harvest results grid
    p_oHarvestResultsGrid = p_oSimManager->GetGridObject("Harvest Results");

    iHarvestTypeCode = p_oHarvestResultsGrid->GetIntDataCode("Harvest Type");

    //initialize with value of -1, no harvest this timestep
    for (i=0;i<5;i++)
      p_oHarvestResultsGrid->SetValueOfCell( i, 0, iHarvestTypeCode, -1);


    //Set-up the time since harvest grid
    p_oTimeSinceHarvestGrid = p_oSimManager->GetGridObject( "Years Since Last Harvest" );

    //register the data members
    iTimeCode = p_oTimeSinceHarvestGrid->GetIntDataCode( "Time" );
    iUpdatedCode = p_oTimeSinceHarvestGrid->GetIntDataCode( "LastUpdated" );

    //initialize with values
    p_oTimeSinceHarvestGrid->SetValueOfCell( 0, 0, iTimeCode, 0);
    p_oTimeSinceHarvestGrid->SetValueOfCell( 0, 0, iUpdatedCode, 0);


    iSp = p_oPop->TranslateSpeciesNameToCode("sp1");
    iXCode = p_oPop->GetXCode(iSp, clTreePopulation::adult);


    //Create 2000 identical trees in first cell
    for (i = 0; i < 2000; i++) {
      p_oTree = p_oPop->CreateTree(0*fCellLength,0, iSp, clTreePopulation::adult, 10);
    }

    //Run for one timestep
    p_oSimManager->RunSim(1);

    //Count the remaining trees
    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {
      if (p_oTree->GetType()==clTreePopulation::adult) {
        p_oTree->GetValue(iXCode, &fTreeX);
        p_oTimeSinceHarvestGrid->GetCellOfPoint(fTreeX,(float)0.0,&iX, &iY);
        p_iTreeCount[iX]++;

      }

      p_oTree = p_oAllTrees->NextTree();
    }


    //Make sure they are as expected

    EXPECT_LT(fabs(1.0*p_iTreeCount[0] - 1230.9) / (1.0*p_iTreeCount[0]), 0.05);


    //Cleanup
    delete[] p_iTreeCount;
    delete p_oSimManager;
  } catch (modelErr &e) {
    delete[] p_iTreeCount;
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}


/////////////////////////////////////////////////////////////////////////////
// WritePostHarvestSkiddingMortXMLFile1()
/////////////////////////////////////////////////////////////////////////////
const char* WritePostHarvestSkiddingMortXMLFile1(int iRun) {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  std::fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  oOut << "<?xml version=\"1.0\" standalone=\"no\"?>"
       << "<paramFile fileCode=\"06080101\">"
       << "<plot>"
       << "<timesteps>1</timesteps>"
       << "<randomSeed>1</randomSeed>"
       << "<yearsPerTimestep>2.0</yearsPerTimestep>"
       << "<plot_lenX>40</plot_lenX>"
       << "<plot_lenY>8</plot_lenY>"
       << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
       << "<plot_temp_C>12.88171785</plot_temp_C>"
       << "<plot_latitude>40.0</plot_latitude>"
       << "</plot>"
       << "<trees>"
       << "<tr_speciesList>"
       << "<tr_species speciesName=\"sp1\"/>"
       << "</tr_speciesList>"
       << "<tr_sizeClasses>"
       << "<tr_sizeClass sizeKey=\"s5.0\"/>"
       << "<tr_sizeClass sizeKey=\"s12.0\"/>"
       << "<tr_sizeClass sizeKey=\"s20.0\"/>"
       << "</tr_sizeClasses>"
       << "<tr_initialDensities>"
       << "<tr_idVals whatSpecies=\"sp1\">"
       << "<tr_initialDensity sizeClass=\"s5.0\">0.0</tr_initialDensity>"
       << "<tr_initialDensity sizeClass=\"s12.0\">0.0</tr_initialDensity>"
       << "<tr_initialDensity sizeClass=\"s20.0\">0.0</tr_initialDensity>"
       << "</tr_idVals>"
       << "</tr_initialDensities>"
       << "<tr_seedDiam10Cm>1.0</tr_seedDiam10Cm>"
       << "<tr_minAdultDBH>"
       << "<tr_madVal species=\"sp1\">5.0</tr_madVal>"
       << "</tr_minAdultDBH>"
       << "<tr_maxSeedlingHeight>"
       << "<tr_mshVal species=\"sp1\">1.35</tr_mshVal>"
       << "</tr_maxSeedlingHeight>"

       << "</trees>"
       << "<behaviorList>";

  if ( iRun==1 ) { //harvest interface is added to run 1 only so that HarvInten is registered
    oOut << "<behavior>"
         << "<behaviorName>HarvestInterface (HarvInten)</behaviorName>"
         << "<version>1.1</version>"
         << "<listPosition>1</listPosition>"
         << "<applyTo species=\"sp1\" type=\"Adult\"/>"
         << "</behavior>";
  }

  oOut << "<behavior>"
       << "<behaviorName>PostHarvestSkiddingMortality</behaviorName>"
       << "<version>1.0</version>";

  if ( iRun==1 )
    oOut << "<listPosition>2</listPosition>";
  else
    oOut << "<listPosition>1</listPosition>";

  oOut << "<applyTo species=\"sp1\" type=\"Adult\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>RemoveDead</behaviorName>"
       << "<version>2.0</version>";

  if ( iRun==1 )
    oOut << "<listPosition>3</listPosition>";
  else
    oOut << "<listPosition>2</listPosition>";

  oOut << "<applyTo species=\"sp1\" type=\"Adult\"></applyTo>"
       << "</behavior>"
       << "</behaviorList>"
       << "<allometry>"
       << "<tr_whatAdultHeightDiam>"
       << "<tr_wahdVal species=\"sp1\">0</tr_wahdVal>"
       << "</tr_whatAdultHeightDiam>"
       << "<tr_whatSaplingHeightDiam>"
       << "<tr_wsahdVal species=\"sp1\">0</tr_wsahdVal>"
       << "</tr_whatSaplingHeightDiam>"
       << "<tr_whatSeedlingHeightDiam>"
       << "<tr_wsehdVal species=\"sp1\">0</tr_wsehdVal>"
       << "</tr_whatSeedlingHeightDiam>"
       << "<tr_whatAdultCrownRadDiam>"
       << "<tr_wacrdVal species=\"sp1\">0</tr_wacrdVal>"
       << "</tr_whatAdultCrownRadDiam>"
       << "<tr_whatSaplingCrownRadDiam>"
       << "<tr_wscrdVal species=\"sp1\">0</tr_wscrdVal>"
       << "</tr_whatSaplingCrownRadDiam>"
       << "<tr_whatAdultCrownHeightHeight>"
       << "<tr_wachhVal species=\"sp1\">0</tr_wachhVal>"
       << "</tr_whatAdultCrownHeightHeight>"
       << "<tr_whatSaplingCrownHeightHeight>"
       << "<tr_wschhVal species=\"sp1\">0</tr_wschhVal>"
       << "</tr_whatSaplingCrownHeightHeight>"
       << "<tr_canopyHeight>"
       << "<tr_chVal species=\"sp1\">15.0</tr_chVal>"
       << "</tr_canopyHeight>"
       << "<tr_stdAsympCrownRad>"
       << "<tr_sacrVal species=\"sp1\">1.0</tr_sacrVal>"
       << "</tr_stdAsympCrownRad>"
       << "<tr_stdCrownRadExp>"
       << "<tr_screVal species=\"sp1\">1.0</tr_screVal>"
       << "</tr_stdCrownRadExp>"
       << "<tr_stdMaxCrownRad>"
       << "<tr_smcrVal species=\"sp1\">10</tr_smcrVal>"
       << "</tr_stdMaxCrownRad>"
       << "<tr_stdAsympCrownHt>"
       << "<tr_sachVal species=\"sp1\">1.0</tr_sachVal>"
       << "</tr_stdAsympCrownHt>"
       << "<tr_stdCrownHtExp>"
       << "<tr_scheVal species=\"sp1\">1.0</tr_scheVal>"
       << "</tr_stdCrownHtExp>"
       << "<tr_conversionDiam10ToDBH>"
       << "<tr_cdtdVal species=\"sp1\">1.0</tr_cdtdVal>"
       << "</tr_conversionDiam10ToDBH>"
       << "<tr_interceptDiam10ToDBH>"
       << "<tr_idtdVal species=\"sp1\">0.0</tr_idtdVal>"
       << "</tr_interceptDiam10ToDBH>"
       << "<tr_slopeOfAsymHeight>"
       << "<tr_soahVal species=\"sp1\">1.0</tr_soahVal>"
       << "</tr_slopeOfAsymHeight>"
       << "<tr_slopeOfHeight-Diam10>"
       << "<tr_sohdVal species=\"sp1\">1.0</tr_sohdVal>"
       << "</tr_slopeOfHeight-Diam10>"
       << "<tr_adultLinearSlope>"
       << "<tr_alsVal species=\"sp1\">1.0</tr_alsVal>"
       << "</tr_adultLinearSlope>"
       << "<tr_adultLinearIntercept>"
       << "<tr_aliVal species=\"sp1\">1.0</tr_aliVal>"
       << "</tr_adultLinearIntercept>"
       << "<tr_adultReverseLinearSlope>"
       << "<tr_arlsVal species=\"sp1\">1.0</tr_arlsVal>"
       << "</tr_adultReverseLinearSlope>"
       << "<tr_adultReverseLinearIntercept>"
       << "<tr_arliVal species=\"sp1\">1.0</tr_arliVal>"
       << "</tr_adultReverseLinearIntercept>"
       << "<tr_saplingLinearSlope>"
       << "<tr_salsVal species=\"sp1\">1.0</tr_salsVal>"
       << "</tr_saplingLinearSlope>"
       << "<tr_saplingLinearIntercept>"
       << "<tr_aliVal species=\"sp1\">1.0</tr_aliVal>"
       << "</tr_saplingLinearIntercept>"
       << "<tr_saplingReverseLinearSlope>"
       << "<tr_sarlsVal species=\"sp1\">1.0</tr_sarlsVal>"
       << "</tr_saplingReverseLinearSlope>"
       << "<tr_saplingReverseLinearIntercept>"
       << "<tr_sarliVal species=\"sp1\">1.0</tr_sarliVal>"
       << "</tr_saplingReverseLinearIntercept>"
       << "<tr_saplingPowerA>"
       << "<tr_sapaVal species=\"sp1\">1.0</tr_sapaVal>"
       << "</tr_saplingPowerA>"
       << "<tr_saplingPowerB>"
       << "<tr_sapbVal species=\"sp1\">1.0</tr_sapbVal>"
       << "</tr_saplingPowerB>"
       << "<tr_seedlingLinearSlope>"
       << "<tr_selsVal species=\"sp1\">1.0</tr_selsVal>"
       << "</tr_seedlingLinearSlope>"
       << "<tr_seedlingLinearIntercept>"
       << "<tr_seliVal species=\"sp1\">1.0</tr_seliVal>"
       << "</tr_seedlingLinearIntercept>"
       << "<tr_seedlingReverseLinearSlope>"
       << "<tr_serlsVal species=\"sp1\">1.0</tr_serlsVal>"
       << "</tr_seedlingReverseLinearSlope>"
       << "<tr_seedlingReverseLinearIntercept>"
       << "<tr_serliVal species=\"sp1\">1.0</tr_serliVal>"
       << "</tr_seedlingReverseLinearIntercept>"
       << "<tr_chRichCrownRadIntercept>"
       << "<tr_crcriVal species=\"sp1\">1.0</tr_crcriVal>"
       << "</tr_chRichCrownRadIntercept>"
       << "<tr_chRichCrownRadAsymp>"
       << "<tr_crcraVal species=\"sp1\">1.0</tr_crcraVal>"
       << "</tr_chRichCrownRadAsymp>"
       << "<tr_chRichCrownRadShape1b>"
       << "<tr_crcrs1bVal species=\"sp1\">1.0</tr_crcrs1bVal>"
       << "</tr_chRichCrownRadShape1b>"
       << "<tr_chRichCrownRadShape2c>"
       << "<tr_crcrs2cVal species=\"sp1\">1.0</tr_crcrs2cVal>"
       << "</tr_chRichCrownRadShape2c>"
       << "<tr_chRichCrownHtIntercept>"
       << "<tr_crchiVal species=\"sp1\">1.0</tr_crchiVal>"
       << "</tr_chRichCrownHtIntercept>"
       << "<tr_chRichCrownHtAsymp>"
       << "<tr_crchaVal species=\"sp1\">1.0</tr_crchaVal>"
       << "</tr_chRichCrownHtAsymp>"
       << "<tr_chRichCrownHtShape1b>"
       << "<tr_crchs1bVal species=\"sp1\">1.0</tr_crchs1bVal>"
       << "</tr_chRichCrownHtShape1b>"
       << "<tr_chRichCrownHtShape2c>"
       << "<tr_crchs2cVal species=\"sp1\">1.0</tr_crchs2cVal>"
       << "</tr_chRichCrownHtShape2c>"
       << "</allometry>"

       << "<grid gridName=\"Years Since Last Harvest\">"
       << "<ma_intCodes>"
       << "<ma_intCode label=\"Time\">0</ma_intCode>"
       << "<ma_intCode label=\"LastUpdated\">1</ma_intCode>"
       << "</ma_intCodes>"
       << "<ma_lengthXCells>8</ma_lengthXCells>"
       << "<ma_lengthYCells>8</ma_lengthYCells>"
       << "</grid>"

       << "<grid gridName=\"Harvest Results\">"
       << "<ma_intCodes>"
       << "<ma_intCode label=\"Harvest Type\">0</ma_intCode>"
       << "</ma_intCodes>"
       << "<ma_lengthXCells>8</ma_lengthXCells>"
       << "<ma_lengthYCells>8</ma_lengthYCells>"
       << "</grid>";

  if (iRun==1) { //harvest interface is added to run 1 only so that HarvInten is registered
    oOut << "<HarvestInterface1>"
         << "<hi_executable>gzip.exe</hi_executable>"
         << "<hi_harvestableTreesFile>x.txt</hi_harvestableTreesFile>"
         << "<hi_treesToHarvestFile>x.txt</hi_treesToHarvestFile>"
         << "<hi_harvestPeriod>50</hi_harvestPeriod>"
         << "<hi_treesToUpdateFile>x.txt</hi_treesToUpdateFile>"
         << "<hi_dataMembers>"
         << "<hi_dataMember>HarvInten</hi_dataMember>"
         << "</hi_dataMembers>"
         << "</HarvestInterface1>"
         << "<PostHarvestSkiddingMortality2>";
  } else {
    oOut << "<PostHarvestSkiddingMortality1>";
  }

  oOut << "<mo_postHarvWindthrowHarvestBasicProb>"
       << "<mo_phwhbpVal species=\"sp1\">0.05</mo_phwhbpVal>"
       << "</mo_postHarvWindthrowHarvestBasicProb>"
       << "<mo_postHarvSnagRecruitHarvestBasicProb>"
       << "<mo_phsrhbpVal species=\"sp1\">0.06</mo_phsrhbpVal>"
       << "</mo_postHarvSnagRecruitHarvestBasicProb>"
       << "<mo_postHarvWindthrowSizeEffect>"
       << "<mo_phwseVal species=\"sp1\">0.003</mo_phwseVal>"
       << "</mo_postHarvWindthrowSizeEffect>"
       << "<mo_postHarvWindthrowHarvestIntensityEffect>"
       << "<mo_phwhieVal species=\"sp1\">0.01</mo_phwhieVal>"
       << "</mo_postHarvWindthrowHarvestIntensityEffect>"
       << "<mo_postHarvSnagRecruitHarvestIntensityEffect>"
       << "<mo_phsrhieVal species=\"sp1\">0.02</mo_phsrhieVal>"
       << "</mo_postHarvSnagRecruitHarvestIntensityEffect>"
       << "<mo_postHarvWindthrowCrowdingEffect>"
       << "<mo_phwceVal species=\"sp1\">0.00004</mo_phwceVal>"
       << "</mo_postHarvWindthrowCrowdingEffect>"
       << "<mo_postHarvSnagRecruitCrowdingEffect>"
       << "<mo_phsrceVal species=\"sp1\">0.0001</mo_phsrceVal>"
       << "</mo_postHarvSnagRecruitCrowdingEffect>"
       << "<mo_postHarvWindthrowHarvestRateParam>"
       << "<mo_phwhrpVal species=\"sp1\">0.2</mo_phwhrpVal>"
       << "</mo_postHarvWindthrowHarvestRateParam>"
       << "<mo_postHarvSnagRecruitHarvestRateParam>"
       << "<mo_phsrhrpVal species=\"sp1\">0.4</mo_phsrhrpVal>"
       << "</mo_postHarvSnagRecruitHarvestRateParam>"
       << "<mo_postHarvCrowdingEffectRadius>5</mo_postHarvCrowdingEffectRadius>"
       << "<mo_postHarvWindthrowBackgroundProb>"
       << "<mo_phwbpVal species=\"sp1\">0.05</mo_phwbpVal>"
       << "</mo_postHarvWindthrowBackgroundProb>"
       << "<mo_postHarvSnagRecruitBackgroundProb>"
       << "<mo_phsrbpVal species=\"sp1\">0.1</mo_phsrbpVal>"
       << "</mo_postHarvSnagRecruitBackgroundProb>"
       << "<mo_postHarvPreHarvestBackgroundMort>"
       << "<mo_phphbmVal species=\"sp1\">0.1</mo_phphbmVal>"
       << "</mo_postHarvPreHarvestBackgroundMort>";
  if (iRun==1)
    oOut << "</PostHarvestSkiddingMortality2>";
  else
    oOut << "</PostHarvestSkiddingMortality1>";

  oOut << "</paramFile>";

  oOut.close();

  return cFileString;
}



