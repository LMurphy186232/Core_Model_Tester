//---------------------------------------------------------------------------
// TestTreeRemover.cpp
//---------------------------------------------------------------------------
#include "TestTreeRemover.h"
#include <gtest/gtest.h>
#include "SimManager.h"
#include "TreePopulation.h"
#include <fstream>
#include <math.h>

/////////////////////////////////////////////////////////////////////////////
// TestNormalProcessingRun1()
// Tests TreeRemover.  Reads in the file created by WriteTreeRemoverXMLFile1().  The file
// has the following characteristics:
//
// -- 3 species - Species 1, Species 2, Species 3.
// -- Adult self-thinning, applied to adults and snags of species 1 and 2.
// -- Tree remover behavior, applied to adults of Species 1.
// -- Tree map.  Each tree's number equals its X coordinate. The map has
// the following trees:
//   -- X = 1 - Adult, Species 1.
//   -- X = 2 - Adult, Species 1.
//   -- X = 3 - Adult, Species 2.
//   -- X = 4 - Adult, Species 2.
//   -- X = 5 - Adult, Species 3.
//
// The value of the "dead" data member is set to true for trees 1 and 3.  Then
// the TreeRemover behavior is run.  Only tree 1 should go away.
/////////////////////////////////////////////////////////////////////////////
TEST(TreeRemover, TestNormalProcessingRun1)
{
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    clTreePopulation * p_oPop;
    clTreeSearch *p_oAllTrees;
    clTree *p_oTree;
    float fX;
    int iDeadCode, iTreeNum, iDeadVal;

    //Load our file
    p_oSimManager->ReadFile( WriteTreeRemoverXMLFile1() );
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );

    //Set the "dead" data member of trees 1 & 3
    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {

      //Get the X coordinate so we know what tree this is
      p_oTree->GetValue(p_oPop->GetXCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fX);
      iTreeNum = (int)fX;
      if (iTreeNum == 1 || iTreeNum == 3) {

        //Set the dead code to killed
        iDeadCode = p_oPop->GetIntDataCode("dead", p_oTree->GetSpecies(), p_oTree->GetType());
        EXPECT_GT(iDeadCode, -1);

        p_oTree->SetValue(iDeadCode, natural);
      }

      p_oTree = p_oAllTrees->NextTree();
    }

    //Now, run the model one timestep
    p_oSimManager->RunSim(1);

    //Search for all trees again and make sure they are as they should be
    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {

      //Get the X coordinate so we know what tree this is
      p_oTree->GetValue(p_oPop->GetXCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fX);
      iTreeNum = (int)fX;
      if (iTreeNum == 1) {
        //Tree 1 should now be a snag

        iDeadCode = p_oPop->GetIntDataCode("dead", p_oTree->GetSpecies(), p_oTree->GetType());
        EXPECT_GT(iDeadCode, -1);
        p_oTree->GetValue(iDeadCode, &iDeadVal);

        EXPECT_EQ(p_oTree->GetType(), clTreePopulation::snag);
        EXPECT_EQ(iDeadVal, notdead);
      }
      else if (iTreeNum == 3) {
        //Tree 3 should have been left alone - and its dead code should still
        //be true

        iDeadCode = p_oPop->GetIntDataCode("dead", p_oTree->GetSpecies(), p_oTree->GetType());
        EXPECT_GT(iDeadCode, -1);
        p_oTree->GetValue(iDeadCode, &iDeadVal);

        EXPECT_EQ(p_oTree->GetType(), clTreePopulation::adult);
        EXPECT_EQ(iDeadVal, natural);

      }
      else if (iTreeNum == 2 || iTreeNum == 4) {

        //Trees 2 & 4 should have been left alone
        iDeadCode = p_oPop->GetIntDataCode("dead", p_oTree->GetSpecies(), p_oTree->GetType());
        EXPECT_GT(iDeadCode, -1);
        p_oTree->GetValue(iDeadCode, &iDeadVal);

        EXPECT_EQ(p_oTree->GetType(), clTreePopulation::adult);
        EXPECT_EQ(iDeadVal, notdead);
      }
      else {

        //Last tree should have been left alone
        iDeadCode = p_oPop->GetIntDataCode("dead", p_oTree->GetSpecies(), p_oTree->GetType());
        EXPECT_EQ(iDeadCode, -1);
        EXPECT_EQ(p_oTree->GetType(), clTreePopulation::adult);
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
// TestErrorProcessing()
/////////////////////////////////////////////////////////////////////////////
TEST(TreeRemover, TestErrorProcessing)
{
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  //Error processing
  try {
    p_oSimManager->ReadFile( WriteTreeRemoverXMLErrorFile1() );
    FAIL() << "clTreeRemover::GetData failed - didn't catch lack of dead data member.";
  } catch (modelErr& err) {

     if (err.sFunction.compare("clTreeRemover::GetData") != 0) {
       FAIL() << "clTreeRemover::GetData failed - didn't catch lack of dead data member.";
     }
  }
  delete p_oSimManager;
}

/////////////////////////////////////////////////////////////////////////////
// WriteTreeRemoverXMLFile1()
/////////////////////////////////////////////////////////////////////////////
const char* WriteTreeRemoverXMLFile1() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06010101\">"
       << "<plot>"
       << "<timesteps>2</timesteps>"
       << "<yearsPerTimestep>1</yearsPerTimestep>"
       << "<randomSeed>1</randomSeed>"
       << "<plot_lenX>2000</plot_lenX>"
       << "<plot_lenY>200.0</plot_lenY>"
       << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
       << "<plot_temp_C>12.88171785</plot_temp_C>"
       << "<plot_latitude>55.37</plot_latitude>"
       << "</plot>"
       << "<trees>"
       << "<tr_speciesList>"
       << "<tr_species speciesName=\"Species_1\"/>"
       << "<tr_species speciesName=\"Species_2\"/>"
       << "<tr_species speciesName=\"Species_3\"/>"
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
       << "<tree sp=\"0\" tp=\"3\">"
       << "<fl c=\"0\">1</fl>"
       << "<fl c=\"1\">1</fl>"
       << "<fl c=\"2\">30</fl>"
       << "</tree>"
       << "<tree sp=\"0\" tp=\"3\">"
       << "<fl c=\"0\">2</fl>"
       << "<fl c=\"1\">2</fl>"
       << "<fl c=\"2\">30</fl>"
       << "</tree>"
       << "<tree sp=\"1\" tp=\"3\">"
       << "<fl c=\"0\">3</fl>"
       << "<fl c=\"1\">3</fl>"
       << "<fl c=\"2\">30</fl>"
       << "</tree>"
       << "<tree sp=\"1\" tp=\"3\">"
       << "<fl c=\"0\">4</fl>"
       << "<fl c=\"1\">4</fl>"
       << "<fl c=\"2\">30</fl>"
       << "</tree>"
       << "<tree sp=\"2\" tp=\"3\">"
       << "<fl c=\"0\">5</fl>"
       << "<fl c=\"1\">5</fl>"
       << "<fl c=\"2\">33</fl>"
       << "</tree>"
       << "</tr_treemap>"
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
       << "<tr_soahVal species=\"Species_2\">0.0299</tr_soahVal>"
       << "<tr_soahVal species=\"Species_3\">0.0299</tr_soahVal>"
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
       << "<behaviorName>SelfThinning</behaviorName>"
       << "<listPosition>1</listPosition>"
       << "<version>1</version>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Snag\"/>"
       << "<applyTo species=\"Species_1\" type=\"Snag\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>RemoveDead</behaviorName>"
       << "<version>3</version>"
       << "<listPosition>2</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "</behavior>"
       << "</behaviorList>"
       << "<SelfThinning1>"
       << "<mo_selfThinSlope>"
       << "<mo_stsVal species=\"Species_1\">0</mo_stsVal>"
       << "<mo_stsVal species=\"Species_2\">0</mo_stsVal>"
       << "</mo_selfThinSlope>"
       << "<mo_selfThinIntercept>"
       << "<mo_stiVal species=\"Species_1\">0</mo_stiVal>"
       << "<mo_stiVal species=\"Species_2\">0</mo_stiVal>"
       << "</mo_selfThinIntercept>"
       << "<mo_selfThinMaxDbh>"
       << "<mo_stmdVal species=\"Species_1\">10</mo_stmdVal>"
       << "<mo_stmdVal species=\"Species_2\">10</mo_stmdVal>"
       << "</mo_selfThinMaxDbh>"
       << "</SelfThinning1>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteTreeRemoverXMLErrorFile1()
/////////////////////////////////////////////////////////////////////////////
const char* WriteTreeRemoverXMLErrorFile1() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06010101\">" << "<plot>"
       << "<timesteps>2</timesteps>"
       << "<yearsPerTimestep>1</yearsPerTimestep>"
       << "<randomSeed>1</randomSeed>"
       << "<plot_lenX>2000</plot_lenX>"
       << "<plot_lenY>200.0</plot_lenY>"
       << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
       << "<plot_temp_C>12.88171785</plot_temp_C>"
       << "<plot_latitude>55.37</plot_latitude>"
       << "</plot>"
       << "<trees>"
       << "<tr_speciesList>"
       << "<tr_species speciesName=\"Species_1\"/>"
       << "<tr_species speciesName=\"Species_2\"/>"
       << "<tr_species speciesName=\"Species_3\"/>"
       << "</tr_speciesList>"
       << "<tr_seedDiam10Cm>0.1</tr_seedDiam10Cm>"
       << "<tr_canopyHeight>"
       << "<tr_chVal species=\"Species_1\">39.48</tr_chVal>"
       << "<tr_chVal species=\"Species_2\">39.48</tr_chVal>"
       << "<tr_chVal species=\"Species_3\">39.48</tr_chVal>"
       << "</tr_canopyHeight>"
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
       << "<tr_soahVal species=\"Species_2\">0.0299</tr_soahVal>"
       << "<tr_soahVal species=\"Species_3\">0.0299</tr_soahVal>"
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
       << "<behaviorName>SelfThinning</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>RemoveDead</behaviorName>"
       << "<version>3</version>"
       << "<listPosition>2</listPosition>"
       << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
       << "</behavior>"
       << "</behaviorList>"
       << "<SelfThinning1>"
       << "<mo_selfThinSlope>"
       << "<mo_stsVal species=\"Species_1\">0</mo_stsVal>"
       << "<mo_stsVal species=\"Species_2\">0</mo_stsVal>"
       << "</mo_selfThinSlope>"
       << "<mo_selfThinIntercept>"
       << "<mo_stiVal species=\"Species_1\">0</mo_stiVal>"
       << "<mo_stiVal species=\"Species_2\">0</mo_stiVal>"
       << "</mo_selfThinIntercept>"
       << "<mo_selfThinMaxDbh>"
       << "<mo_stmdVal species=\"Species_1\">10</mo_stmdVal>"
       << "<mo_stmdVal species=\"Species_2\">10</mo_stmdVal>"
       << "</mo_selfThinMaxDbh>"
       << "<mo_treeRemNatMortSnagsStanding>"
       << "<mo_trnmssVal species=\"Species_3\">1</mo_trnmssVal>"
       << "</mo_treeRemNatMortSnagsStanding>"
       << "<mo_treeRemDiseaseMortSnagsStanding>"
       << "<mo_trdmssVal species=\"Species_3\">1</mo_trdmssVal>"
       << "</mo_treeRemDiseaseMortSnagsStanding>"
       << "<mo_treeRemInsectMortSnagsStanding>"
       << "<mo_trimssVal species=\"Species_3\">1</mo_trimssVal>"
       << "</mo_treeRemInsectMortSnagsStanding>"
       << "<mo_treeRemStormMortSnagsStanding>"
       << "<mo_trsmssVal species=\"Species_3\">1</mo_trsmssVal>"
       << "</mo_treeRemStormMortSnagsStanding>"
       << "<mo_treeRemFireMortSnagsStanding>"
       << "<mo_trfmssVal species=\"Species_3\">1</mo_trfmssVal>"
       << "</mo_treeRemFireMortSnagsStanding>"
       << "</SelfThinning1>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}
