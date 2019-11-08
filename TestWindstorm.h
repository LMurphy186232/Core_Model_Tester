//---------------------------------------------------------------------------
// TestWindstorm
//---------------------------------------------------------------------------
#if !defined(TestWindstorm_H)
#define TestWindstorm_H
#include <fstream>

/*
 * Tests normal processing Run 8. WriteWindstormXMLFile8() writes the parameter
 * file. This run tests to make sure storms below the minimum intensity are
 * handled correctly.
 * Aspects of the run:
 * <ul>
 * <li>1 year per timestep.</li>
 * <li>No snags.</li>
 * <li>The following trees will be added, with a storm of 0.07 triggered
 * for timestep 1:
 * <ul>
 * <li>Grid (0,0): 1000 trees of Species 1 and 2, DBH 30.</li>
 * <li>Grid (1,0): 1000 trees of Species 1 and 2, DBH 8.</li>
 * </ul></li>
 * </ul>
 *
 * The run proceeds for 1 timestep.  The "Windstorm Results" grid is checked,
 * and the actual number of trees alive and dead is checked as well.
 *
 * @param p_oSimManager Sim Manager object to run our test run.
 */
//void TestNormalProcessingRun8(clSimManager *p_oSimManager);


/**
 * Writes the parameter file for TestNormalProcessing1().
 * @return File name of the freshly written parameter file.
 */
const char* WriteWindstormXMLFile1();

/**
 * Writes the parameter file for TestNormalProcessing2().
 * @return File name of the freshly written parameter file.
 */
const char* WriteWindstormXMLFile2();

/**
 * Writes the parameter file for TestNormalProcessing3().
 * @return File name of the freshly written parameter file.
 */
const char* WriteWindstormXMLFile3();

/**
 * Writes the parameter file for TestNormalProcessing4().
 * @return File name of the freshly written parameter file.
 */
const char* WriteWindstormXMLFile4();

/**
 * Writes the parameter file for TestNormalProcessing5().
 * @return File name of the freshly written parameter file.
 */
const char* WriteWindstormXMLFile5();

/**
 * Writes the parameter file for TestNormalProcessing6().
 * @return File name of the freshly written parameter file.
 */
const char* WriteWindstormXMLFile6();

/**
 * Writes the parameter file for TestNormalProcessing7().
 * @return File name of the freshly written parameter file.
 */
const char* WriteWindstormXMLFile7();

/**
 * Writes the parameter file for TestNormalProcessing8().
 * @return File name of the freshly written parameter file.
 */
const char* WriteWindstormXMLFile8();

/**
 * Writes an error file where the minimum DBH is negative.
 * @return File name of the freshly written parameter file.
 */
const char* WriteWindstormXMLErrorFile1();

/**
 * Writes an error file where the storm damage applier behavior is applied
 * to seedlings.
 * @return File name of the freshly written parameter file.
 */
const char* WriteWindstormXMLErrorFile2();

/**
 * Writes an error file where the timestep to start storms is negative.
 * @return File name of the freshly written parameter file.
 */
const char* WriteWindstormXMLErrorFile3();

/**
 * Writes an error file where the severity of a storm return interval is not
 * between 0 and 1.
 * @return File name of the freshly written parameter file.
 */
const char* WriteWindstormXMLErrorFile4();

/**
 * Writes an error file where mortality behaviors are not applied to all trees.
 * @return File name of the freshly written parameter file.
 */
const char* WriteWindstormXMLErrorFile5();

/**
 * Writes an error file where the storm periodicity is zero.
 * @return File name of the freshly written parameter file.
 */
const char* WriteWindstormXMLErrorFile6();

/**
 * Writes common portions of the test parameter files.  Starts with
 * &lt;randomSeed&gt; and ends with &lt;/allometry&gt;.
 * @param oOut File stream to write to.
 */
void WriteWindstormCommonStuff(std::fstream &oOut);

/**
 * Writes the behavior list for the test parameter files with snags.
 * @param oOut File stream to write to.
 */
void WriteWindstormSnagBehaviorList(std::fstream &oOut);

/**
 * Writes the behavior list for the test parameter files without snags.
 * @param oOut File stream to write to.
 */
void WriteWindstormNoSnagBehaviorList(std::fstream &oOut);
//---------------------------------------------------------------------------
#endif //TestWindstorm_H
