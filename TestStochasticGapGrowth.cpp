//---------------------------------------------------------------------------
// TestStochasticGapGrowth.cpp
//---------------------------------------------------------------------------
#include "TestStochasticGapGrowth.h"
#include <gtest/gtest.h>
#include "SimManager.h"
#include "TreePopulation.h"
#include <fstream>
#include <math.h>

////////////////////////////////////////////////////////////////////////////
// TestNormalProcessing()
// Tests normal processing. WriteStochasticGapGrowthXMLFile1() does setup. 3
// adult trees are placed so as to create non-gap conditions in certain cells of
// the "Gap Light" grid. A series of juveniles that are potential growers are
// placed in other cells. The simulation is run, and then for gap cells
// containing juveniles, we make sure that there is only one adult and that it
// has a size equal to the minimum adult DBH.
////////////////////////////////////////////////////////////////////////////
TEST(StochasticGapGrowth, TestNormalProcessing) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    clTreePopulation * p_oPop;
    clTreeSearch *p_oAdults;
    clTree *p_oTree;
    char cQuery[100];
    float fDiam, fX, fY;
    int iSpecies, iXGrid, iYGrid,
    i6_4Count = 0, //count of adults in cell (6,4)
    i4_4Count = 0; //count of adults in cell (4,4)

    //Load our test file and get our tree population pointer
    p_oSimManager->ReadFile( WriteStochasticGapGrowthXMLFile1() );
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );

    //Create our adult trees so we have certain cells with non-gap conditions
    fDiam = 11;
    fX = 2.0;
    fY = 10.0;
    p_oPop->CreateTree(fX, fY, 0, clTreePopulation::adult, fDiam);

    fX = 23.0;
    fY = 45.0;
    p_oPop->CreateTree(fX, fY, 0, clTreePopulation::adult, fDiam);

    fX = 9.0;
    fY = 31.0;
    p_oPop->CreateTree(fX, fY, 0, clTreePopulation::adult, fDiam);

    //Create our juveniles
    fDiam = 0.2;
    iSpecies = 1;
    fX = 74.0;
    fY = 12.0;
    p_oPop->CreateTree(fX, fY, iSpecies, clTreePopulation::seedling, fDiam);

    fDiam = 0.2;
    iSpecies = 0;
    fX = 54.0;
    fY = 32.0;
    p_oPop->CreateTree(fX, fY, iSpecies, clTreePopulation::seedling, fDiam);

    fDiam = 0.2;
    iSpecies = 2;
    fX = 3.0;
    fY = 11.0;
    p_oPop->CreateTree(fX, fY, iSpecies, clTreePopulation::seedling, fDiam);

    fDiam = 2;
    iSpecies = 0;
    fX = 33.0;
    fY = 33.0;
    p_oPop->CreateTree(fX, fY, iSpecies, clTreePopulation::sapling, fDiam);

    fDiam = 2;
    iSpecies = 2;
    fX = 34.0;
    fY = 34.0;
    p_oPop->CreateTree(fX, fY, iSpecies, clTreePopulation::sapling, fDiam);

    fDiam = 2;
    iSpecies = 0;
    fX = 35.0;
    fY = 35.0;
    p_oPop->CreateTree(fX, fY, iSpecies, clTreePopulation::sapling, fDiam);

    fDiam = 2;
    iSpecies = 2;
    fX = 36.0;
    fY = 36.0;
    p_oPop->CreateTree(fX, fY, iSpecies, clTreePopulation::sapling, fDiam);

    fDiam = 2;
    iSpecies = 0;
    fX = 10.0;
    fY = 25.0;
    p_oPop->CreateTree(fX, fY, iSpecies, clTreePopulation::sapling, fDiam);

    fDiam = 2;
    iSpecies = 2;
    fX = 11.0;
    fY = 26.0;
    p_oPop->CreateTree(fX, fY, iSpecies, clTreePopulation::sapling, fDiam);

    fDiam = 2;
    iSpecies = 0;
    fX = 12.0;
    fY = 27.0;
    p_oPop->CreateTree(fX, fY, iSpecies, clTreePopulation::sapling, fDiam);

    fDiam = 2;
    iSpecies = 2;
    fX = 13.0;
    fY = 28.0;
    p_oPop->CreateTree(fX, fY, iSpecies, clTreePopulation::sapling, fDiam);

    fDiam = 2;
    iSpecies = 0;
    fX = 14.0;
    fY = 29.0;
    p_oPop->CreateTree(fX, fY, iSpecies, clTreePopulation::sapling, fDiam);

    fDiam = 2;
    iSpecies = 2;
    fX = 15.0;
    fY = 30.0;
    p_oPop->CreateTree(fX, fY, iSpecies, clTreePopulation::sapling, fDiam);

    //Dead tree
    fDiam = 2;
    iSpecies = 0;
    fX = 30;
    fY = 15;
    p_oTree = p_oPop->CreateTree(fX, fY, iSpecies, clTreePopulation::sapling, fDiam);
    p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSpecies, clTreePopulation::sapling), natural);


    //Run the simulation a timestep
    p_oSimManager->RunSim(1);

    //Get all the adults and check 'em out
    sprintf(cQuery, "%s%d", "type=", clTreePopulation::adult);
    p_oAdults = p_oPop->Find(cQuery);
    p_oTree = p_oAdults->NextTree();
    while (p_oTree != NULL) {

      //Get the tree's X and Y location
      p_oTree->GetValue(p_oPop->GetXCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fX);
      p_oTree->GetValue(p_oPop->GetYCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fY);

      //Get the tree's grid numbers
      iXGrid = (int)floor(fX / 8);
      iYGrid = (int)floor(fY / 8);

      if (iXGrid == 2 && iYGrid == 5) {
        //Cell 2, 5 - make sure this is the adult that was already there
        EXPECT_LT(fabs(fX - 23), 0.01);
        EXPECT_LT(fabs(fY - 45), 0.01);
      }
      else if (iXGrid == 6 && iYGrid == 4) {
        //Cell 6,4 - there was one juvenile - make sure it's the one we were
        //expecting
        EXPECT_LT(fabs(fX - 54), 0.01);
        EXPECT_LT(fabs(fY - 32), 0.01);

        //Get the diam - it should be 10
        p_oTree->GetValue(p_oPop->GetDbhCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fDiam);
        EXPECT_LT(fabs(fDiam - 10), 0.1);

        i6_4Count++;
      }
      else if (iXGrid == 0 && iYGrid == 1) {
        //Cell 0,1 - make sure it's the adult that was already there
        EXPECT_LT(fabs(fX - 2), 0.01);
        EXPECT_LT(fabs(fY - 10), 0.01);
      }
      else if (iXGrid == 4 && iYGrid == 4) {
        //Get the diam - it should be 10
        p_oTree->GetValue(p_oPop->GetDbhCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fDiam);
        EXPECT_LT(fabs(fDiam - 10), 0.1);

        //Cell 4,4 - count to make sure we only get 1
        i4_4Count++;
      }
      else if (iXGrid == 1 && iYGrid == 3) {
        //Cell 1,3 - make sure it's the adult that was already there
        EXPECT_LT(fabs(fX - 9), 0.01);
        EXPECT_LT(fabs(fY - 31), 0.01);
      }
      else {
        FAIL() << "Found an unexpected adult at X = " << fX << " << Y = " << fY << ".";
      }
      p_oTree = p_oAdults->NextTree();
    }

    EXPECT_EQ(1, i6_4Count);
    EXPECT_EQ(1, i4_4Count);
    delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

////////////////////////////////////////////////////////////////////////////
// TestErrorProcessing()
// Tests error processing. This tests the case where the gap light behavior
// is not called before the stochastic gap growth behavior.
// WriteStochasticGapGrowthXMLErrorFile1() is used to write the error file.
////////////////////////////////////////////////////////////////////////////
TEST(StochasticGapGrowth, TestErrorProcessing) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try
  {
    p_oSimManager->ReadFile(WriteStochasticGapGrowthXMLErrorFile1());
    FAIL() << "TestStochasticGapGrowth error processing didn't catch error for WriteStochasticGapGrowthXMLErrorFile1.";
  }
  catch (modelErr& err)
  {
    if (err.sFunction.compare("clStochasticGapGrowth::GetData") != 0)
    {
      FAIL() << "TestStochasticGapGrowth error processing caught wrong error for WriteStochasticGapGrowthXMLErrorFile1.";
    }
    ;
  }
  delete p_oSimManager;
}

/////////////////////////////////////////////////////////////////////////////
// WriteStochasticGapGrowthXMLFile1()
/////////////////////////////////////////////////////////////////////////////
const char* WriteStochasticGapGrowthXMLFile1() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
      << "<paramFile fileCode=\"06010101\">"
      << "<plot>"
      << "<timesteps>2</timesteps>"
      << "<rt_timestep>0</rt_timestep>"
      << "<randomSeed>0</randomSeed>"
      << "<yearsPerTimestep>1.0</yearsPerTimestep>"
      << "<plot_lenX>100.0</plot_lenX>"
      << "<plot_lenY>100.0</plot_lenY>"
      << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
      << "<plot_temp_C>12.88171785</plot_temp_C>"
      << "<plot_latitude>0.0</plot_latitude>"
      << "</plot>"
      << "<trees>"
      << "<tr_speciesList>"
      << "<tr_species speciesName=\"Species_1\" />"
      << "<tr_species speciesName=\"Species_2\" />"
      << "<tr_species speciesName=\"Species_3\" />"
      << "</tr_speciesList>"
      << "<tr_seedDiam10Cm>0.1</tr_seedDiam10Cm>"
      << "<tr_minAdultDBH>"
      << "<tr_madVal species=\"Species_1\">10.0</tr_madVal>"
      << "<tr_madVal species=\"Species_2\">10.0</tr_madVal>"
      << "<tr_madVal species=\"Species_3\">10.0</tr_madVal>"
      << "</tr_minAdultDBH>"
      << "<tr_maxSeedlingHeight>"
      << "<tr_mshVal species=\"Species_1\">1.35</tr_mshVal>"
      << "<tr_mshVal species=\"Species_2\">1.35</tr_mshVal>"
      << "<tr_mshVal species=\"Species_3\">1.35</tr_mshVal>"
      << "</tr_maxSeedlingHeight>"
      << "</trees>"
      << "<allometry>"
      << "<tr_canopyHeight>"
      << "<tr_chVal species=\"Species_1\">40.0</tr_chVal>"
      << "<tr_chVal species=\"Species_2\">40.0</tr_chVal>"
      << "<tr_chVal species=\"Species_3\">40.0</tr_chVal>"
      << "</tr_canopyHeight>"
      << "<tr_stdAsympCrownRad>"
      << "<tr_sacrVal species=\"Species_1\">0.7</tr_sacrVal>"
      << "<tr_sacrVal species=\"Species_2\">0.7</tr_sacrVal>"
      << "<tr_sacrVal species=\"Species_3\">0.7</tr_sacrVal>"
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
      << "<tr_cdtdVal species=\"Species_1\">0.7</tr_cdtdVal>"
      << "<tr_cdtdVal species=\"Species_2\">0.7</tr_cdtdVal>"
      << "<tr_cdtdVal species=\"Species_3\">0.7</tr_cdtdVal>"
      << "</tr_conversionDiam10ToDBH>"
      << "<tr_interceptDiam10ToDBH>"
      << "<tr_idtdVal species=\"Species_1\">0</tr_idtdVal>"
      << "<tr_idtdVal species=\"Species_2\">0</tr_idtdVal>"
      << "<tr_idtdVal species=\"Species_3\">0</tr_idtdVal>"
      << "</tr_interceptDiam10ToDBH>"
      << "<tr_stdAsympCrownHt>"
      << "<tr_sachVal species=\"Species_1\">0.7</tr_sachVal>"
      << "<tr_sachVal species=\"Species_2\">0.7</tr_sachVal>"
      << "<tr_sachVal species=\"Species_3\">0.7</tr_sachVal>"
      << "</tr_stdAsympCrownHt>"
      << "<tr_stdCrownHtExp>"
      << "<tr_scheVal species=\"Species_1\">1.0</tr_scheVal>"
      << "<tr_scheVal species=\"Species_2\">1.0</tr_scheVal>"
      << "<tr_scheVal species=\"Species_3\">1.0</tr_scheVal>"
      << "</tr_stdCrownHtExp>"
      << "<tr_slopeOfHeight-Diam10>"
      << "<tr_sohdVal species=\"Species_1\">0.03</tr_sohdVal>"
      << "<tr_sohdVal species=\"Species_2\">0.03</tr_sohdVal>"
      << "<tr_sohdVal species=\"Species_3\">0.03</tr_sohdVal>"
      << "</tr_slopeOfHeight-Diam10>"
      << "<tr_slopeOfAsymHeight>"
      << "<tr_soahVal species=\"Species_1\">0.7</tr_soahVal>"
      << "<tr_soahVal species=\"Species_2\">0.7</tr_soahVal>"
      << "<tr_soahVal species=\"Species_3\">0.7</tr_soahVal>"
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
      << "</allometry>"
      << "<behaviorList>"
      << "<behavior>"
      << "<behaviorName>GapLight</behaviorName>"
      << "<version>1.0</version>"
      << "<listPosition>1</listPosition>"
      << "<applyTo species=\"Species_1\" type=\"Seedling\" />"
      << "<applyTo species=\"Species_2\" type=\"Seedling\" />"
      << "<applyTo species=\"Species_3\" type=\"Seedling\" />"
      << "<applyTo species=\"Species_1\" type=\"Sapling\" />"
      << "<applyTo species=\"Species_2\" type=\"Sapling\" />"
      << "<applyTo species=\"Species_3\" type=\"Sapling\" />"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>StochasticGapGrowth</behaviorName>"
      << "<version>1.0</version>"
      << "<listPosition>2</listPosition>"
      << "<applyTo species=\"Species_1\" type=\"Seedling\" />"
      << "<applyTo species=\"Species_3\" type=\"Seedling\" />"
      << "<applyTo species=\"Species_1\" type=\"Sapling\" />"
      << "<applyTo species=\"Species_3\" type=\"Sapling\" />"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>StochasticMortality</behaviorName>"
      << "<version>1.0</version>"
      << "<listPosition>3</listPosition>"
      << "<applyTo species=\"Species_1\" type=\"Seedling\" />"
      << "<applyTo species=\"Species_3\" type=\"Seedling\" />"
      << "<applyTo species=\"Species_1\" type=\"Sapling\" />"
      << "<applyTo species=\"Species_3\" type=\"Sapling\" />"
      << "</behavior>"
      << "</behaviorList>"
      << "<StochasticMortality3>"
      << "<mo_stochasticMortRate>"
      << "<mo_smrVal species=\"Species_3\">0</mo_smrVal>"
      << "<mo_smrVal species=\"Species_1\">0</mo_smrVal>"
      << "</mo_stochasticMortRate>"
      << "</StochasticMortality3>"
      << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteStochasticGapGrowthXMLErrorFile1()
/////////////////////////////////////////////////////////////////////////////
const char* WriteStochasticGapGrowthXMLErrorFile1() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
      << "<paramFile fileCode=\"06010101\">"
      << "<plot>"
      << "<timesteps>2</timesteps>"
      << "<rt_timestep>0</rt_timestep>"
      << "<randomSeed>0</randomSeed>"
      << "<yearsPerTimestep>1.0</yearsPerTimestep>"
      << "<plot_lenX>100.0</plot_lenX>"
      << "<plot_lenY>100.0</plot_lenY>"
      << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
      << "<plot_temp_C>12.88171785</plot_temp_C>"
      << "<plot_latitude>0.0</plot_latitude>"
      << "</plot>"
      << "<trees>"
      << "<tr_speciesList>"
      << "<tr_species speciesName=\"Species_1\" />"
      << "<tr_species speciesName=\"Species_2\" />"
      << "<tr_species speciesName=\"Species_3\" />"
      << "</tr_speciesList>"
      << "<tr_seedDiam10Cm>0.1</tr_seedDiam10Cm>"
      << "<tr_minAdultDBH>"
      << "<tr_madVal species=\"Species_1\">10.0</tr_madVal>"
      << "<tr_madVal species=\"Species_2\">10.0</tr_madVal>"
      << "<tr_madVal species=\"Species_3\">10.0</tr_madVal>"
      << "</tr_minAdultDBH>"
      << "<tr_maxSeedlingHeight>"
      << "<tr_mshVal species=\"Species_1\">1.35</tr_mshVal>"
      << "<tr_mshVal species=\"Species_2\">1.35</tr_mshVal>"
      << "<tr_mshVal species=\"Species_3\">1.35</tr_mshVal>"
      << "</tr_maxSeedlingHeight>"
      << "</trees>"
      << "<allometry>"
      << "<tr_canopyHeight>"
      << "<tr_chVal species=\"Species_1\">40.0</tr_chVal>"
      << "<tr_chVal species=\"Species_2\">40.0</tr_chVal>"
      << "<tr_chVal species=\"Species_3\">40.0</tr_chVal>"
      << "</tr_canopyHeight>"
      << "<tr_stdAsympCrownRad>"
      << "<tr_sacrVal species=\"Species_1\">0.7</tr_sacrVal>"
      << "<tr_sacrVal species=\"Species_2\">0.7</tr_sacrVal>"
      << "<tr_sacrVal species=\"Species_3\">0.7</tr_sacrVal>"
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
      << "<tr_cdtdVal species=\"Species_1\">0.7</tr_cdtdVal>"
      << "<tr_cdtdVal species=\"Species_2\">0.7</tr_cdtdVal>"
      << "<tr_cdtdVal species=\"Species_3\">0.7</tr_cdtdVal>"
      << "</tr_conversionDiam10ToDBH>"
      << "<tr_stdAsympCrownHt>"
      << "<tr_sachVal species=\"Species_1\">0.7</tr_sachVal>"
      << "<tr_sachVal species=\"Species_2\">0.7</tr_sachVal>"
      << "<tr_sachVal species=\"Species_3\">0.7</tr_sachVal>"
      << "</tr_stdAsympCrownHt>"
      << "<tr_stdCrownHtExp>"
      << "<tr_scheVal species=\"Species_1\">1.0</tr_scheVal>"
      << "<tr_scheVal species=\"Species_2\">1.0</tr_scheVal>"
      << "<tr_scheVal species=\"Species_3\">1.0</tr_scheVal>"
      << "</tr_stdCrownHtExp>"
      << "<tr_slopeOfHeight-Diam10>"
      << "<tr_sohdVal species=\"Species_1\">0.03</tr_sohdVal>"
      << "<tr_sohdVal species=\"Species_2\">0.03</tr_sohdVal>"
      << "<tr_sohdVal species=\"Species_3\">0.03</tr_sohdVal>"
      << "</tr_slopeOfHeight-Diam10>"
      << "<tr_interceptDiam10ToDBH>"
      << "<tr_idtdVal species=\"Species_1\">0</tr_idtdVal>"
      << "<tr_idtdVal species=\"Species_2\">0</tr_idtdVal>"
      << "<tr_idtdVal species=\"Species_3\">0</tr_idtdVal>"
      << "</tr_interceptDiam10ToDBH>"
      << "<tr_interceptDiam10ToDBH>"
      << "<tr_idtdVal species=\"Species_1\">0</tr_idtdVal>"
      << "<tr_idtdVal species=\"Species_2\">0</tr_idtdVal>"
      << "<tr_idtdVal species=\"Species_3\">0</tr_idtdVal>"
      << "</tr_interceptDiam10ToDBH>"
      << "<tr_slopeOfAsymHeight>"
      << "<tr_soahVal species=\"Species_1\">0.7</tr_soahVal>"
      << "<tr_soahVal species=\"Species_2\">0.7</tr_soahVal>"
      << "<tr_soahVal species=\"Species_3\">0.7</tr_soahVal>"
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
      << "</allometry>"
      << "<behaviorList>"
      << "<behavior>"
      << "<behaviorName>StochasticGapGrowth</behaviorName>"
      << "<version>1.0</version>"
      << "<listPosition>1</listPosition>"
      << "<applyTo species=\"Species_1\" type=\"Seedling\" />"
      << "<applyTo species=\"Species_3\" type=\"Seedling\" />"
      << "<applyTo species=\"Species_1\" type=\"Sapling\" />"
      << "<applyTo species=\"Species_3\" type=\"Sapling\" />"
      << "</behavior>"
      << "</behaviorList>"
      << "</paramFile>";

  oOut.close();

  return cFileString;
}

