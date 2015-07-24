//---------------------------------------------------------------------------
// TestStormDamageApplier
//---------------------------------------------------------------------------
#if !defined(TestStormDamageApplier_H)
#define TestStormDamageApplier_H

#include <fstream>

class clTreePopulation;

/**
 * Tests the clStormDamageApplier class.
 */

/**
 * Checks the expected results for timestep 1 of TestNormalProcessingRun1().
 * @param p_oPop Tree population object.
 */
void TestStormDamageApplierRun1Timestep1(clTreePopulation *p_oPop);

/**
 * Checks the expected results for timestep 2 of TestNormalProcessingRun1().
 * @param p_oPop Tree population object.
 */
void TestStormDamageApplierRun1Timestep2(clTreePopulation *p_oPop);

/**
 * Checks the expected results for timestep 3 of TestNormalProcessingRun1().
 * @param p_oPop Tree population object.
 */
void TestStormDamageApplierRun1Timestep3(clTreePopulation *p_oPop);

/**
 * Checks the expected results for timestep 4 of TestNormalProcessingRun1().
 * @param p_oPop Tree population object.
 */
void TestStormDamageApplierRun1Timestep4(clTreePopulation *p_oPop);

/**
 * Checks the expected results for timestep 5 of TestNormalProcessingRun1().
 * @param p_oPop Tree population object.
 */
void TestStormDamageApplierRun1Timestep5(clTreePopulation *p_oPop);

/**
 * Writes the parameter file for TestNormalProcessing1().
 * @return File name of the freshly written parameter file.
 */
const char* WriteStormDamageApplierXMLFile1();

/**
 * Writes the parameter file for TestNormalProcessing2().
 * @return File name of the freshly written parameter file.
 */
const char* WriteStormDamageApplierXMLFile2();

/**
 * Writes the parameter file for MakeGraphs().
 * @return File name of the freshly written parameter file.
 */
const char* WriteStormDamageApplierXMLFile3();

/**
 * Writes an error file where the storm behavior is not also enabled.
 * @return File name of the freshly written parameter file.
 */
const char* WriteStormDamageApplierXMLErrorFile1();

/**
 * Writes an error file where the storm damage applier behavior is applied
 * to seedlings.
 * @return File name of the freshly written parameter file.
 */
const char* WriteStormDamageApplierXMLErrorFile2();

/**
 * Writes an error file where the value for number of years to heal is
 * not positive.
 * @return File name of the freshly written parameter file.
 */
const char* WriteStormDamageApplierXMLErrorFile3();

/**
 * Writes common portions of the test parameter files.  Starts with
 * &lt;randomSeed&gt; and ends with &lt;/allometry&gt;.
 * @param oOut File stream to write to.
 */
void WriteStormDamageApplierCommonStuff(std::fstream &oOut);

/**
 * Writes the behavior list for the test parameter files.
 * @param oOut File stream to write to.
 */
void WriteStormDamageApplierBehaviorList(std::fstream &oOut);
//---------------------------------------------------------------------------
#endif //TestStormDamageApplier_H
