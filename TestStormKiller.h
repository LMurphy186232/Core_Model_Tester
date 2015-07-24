//---------------------------------------------------------------------------
// TestStormKiller
//---------------------------------------------------------------------------
#if !defined(TestStormKiller_H)
#define TestStormKiller_H
#include <fstream>

class clTreePopulation;
class clSimManager;

/**
 * Tests the clStormKiller class.
 */

/**
 * Checks the expected results for timestep 1 of TestNormalProcessingRun1().
 * @param p_oPop Tree population object.
 */
void TestStormKillerRun1Timestep1(clTreePopulation *p_oPop);

/**
 * Checks the expected results for timestep 2 of TestNormalProcessingRun1().
 * @param p_oPop Tree population object.
 */
void TestStormKillerRun1Timestep2(clTreePopulation *p_oPop);

/**
 * Checks the expected results for timestep 3 of TestNormalProcessingRun1().
 * @param p_oPop Tree population object.
 */
void TestStormKillerRun1Timestep3(clTreePopulation *p_oPop);

/**
 * Checks the expected results for timestep 4 of TestNormalProcessingRun1().
 * @param p_oPop Tree population object.
 */
void TestStormKillerRun1Timestep4(clTreePopulation *p_oPop);

/**
 * Checks the expected results for timestep 5 of TestNormalProcessingRun1().
 * @param p_oPop Tree population object.
 */
void TestStormKillerRun1Timestep5(clTreePopulation *p_oPop);

/**
 * Checks the expected results for timestep 1 of TestNormalProcessingRun3().
 * @param p_oPop Tree population object.
 */
void TestStormKillerRun3Timestep1(clTreePopulation *p_oPop);

/**
 * Checks the expected results for timestep 2 of TestNormalProcessingRun3().
 * @param p_oPop Tree population object.
 */
void TestStormKillerRun3Timestep2(clTreePopulation *p_oPop);

/**
 * Checks the expected results for timestep 3 of TestNormalProcessingRun3().
 * @param p_oPop Tree population object.
 */
void TestStormKillerRun3Timestep3(clTreePopulation *p_oPop);

/**
 * Checks the expected results for timestep 4 of TestNormalProcessingRun3().
 * @param p_oPop Tree population object.
 */
void TestStormKillerRun3Timestep4(clTreePopulation *p_oPop);

/**
 * Checks the expected results for timestep 5 of TestNormalProcessingRun3().
 * @param p_oPop Tree population object.
 */
void TestStormKillerRun3Timestep5(clTreePopulation *p_oPop);

/**
 * Tests error processing.
 * @throws error if any of the errors are not caught, or an error other than
 * the intended error is thrown by a parameter file.
 */
void TestErrorProcessing(clSimManager *p_oSimManager);

/**
 * Writes the parameter file for TestNormalProcessing1().
 * @return File name of the freshly written parameter file.
 */
const char* WriteStormKillerXMLFile1();

/**
 * Writes the parameter file for TestNormalProcessing2().
 * @return File name of the freshly written parameter file.
 */
const char* WriteStormKillerXMLFile2();

/**
 * Writes the parameter file for TestNormalProcessing3().
 * @return File name of the freshly written parameter file.
 */
const char* WriteStormKillerXMLFile3();

/**
 * Writes an error file where the storm behavior is not also enabled.  (By
 * necessity the storm damage applier behavior is not enabled either,
 * otherwise it would catch the error.)
 * @return File name of the freshly written parameter file.
 */
const char* WriteStormKillerXMLErrorFile1();

/**
 * Writes an error file where the storm killer behavior is applied
 * to seedlings.
 * @return File name of the freshly written parameter file.
 */
const char* WriteStormKillerXMLErrorFile2();

/**
 * Writes an error file where the storm damage applier behavior is not also
 * enabled.
 * @return File name of the freshly written parameter file.
 */
const char* WriteStormKillerXMLErrorFile3();

/**
 * Writes an error file where the proportion of fully damaged trees that tip
 * up is not a proportion.
 * @return File name of the freshly written parameter file.
 */
const char* WriteStormKillerXMLErrorFile4();

/**
 * Writes an error file where the max snag lifespan is negative.
 * @return File name of the freshly written parameter file.
 */
const char* WriteStormKillerXMLErrorFile5();

/**
 * Writes an error file where mortality behaviors aren't applied to all
 * storm trees.
 * @return File name of the freshly written parameter file.
 */
const char* WriteStormKillerXMLErrorFile6();

/**
 * Writes common portions of the test parameter files.  Starts with
 * &lt;randomSeed&gt; and ends with &lt;/allometry&gt;.
 * @param oOut File stream to write to.
 */
void WriteStormKillerCommonStuff(std::fstream &oOut);

/**
 * Writes a behavior list with snags.
 * @param oOut File stream to write to.
 */
void WriteStormKillerSnagBehaviorList(std::fstream &oOut);

/**
 * Writes a behavior list with no snags.
 * @param oOut File stream to write to.
 */
void WriteStormKillerNoSnagBehaviorList(std::fstream &oOut);

/**
 * Writes common storm parameters.  Starts with &lt;storm&gt; and ends with
 * &lt;/storm&gt;.
 * @param oOut File stream to write to.
 */
void WriteStormKillerStormParameters(std::fstream &oOut);
//---------------------------------------------------------------------------
#endif //TestStormKiller_H
