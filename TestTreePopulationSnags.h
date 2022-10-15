//---------------------------------------------------------------------------
// TestTreePopulationSnags
//---------------------------------------------------------------------------
#if !defined(TestTreePopulationSnags_H)
#define TestTreePopulationSnags_H

#include <stddef.h>
#include <fstream>

class clTreePopulation;
class clTree;
class clTreeSearch;

/**
 * Tests the clTreePopulation class. The test script guiding the test is
 * Population Test.xls.
 */

/**
 * Writes a parameter file for testing. Characteristics:
 * <ul>
 * <li>Two species.
 * <li>There is a behavior which uses snags.
 * <li>There is a behavior which uses stumps, but only for Species 1.
 * <li>There is a tree map with seedlings, saplings, adults, and snags.
 * </ul>
 * @return Filename written.
 */
const char* WriteTreePopulationSnagsFile1();

/**
 * Writes a parameter file for testing. Characteristics:
 * <ul>
 * <li>3 years per timestep.
 * <li>Two species.
 * <li>There is a behavior which uses snags.
 * <li>There is a behavior which uses stumps, but only for Species 1.
 * <li>There is a tree map with seedlings, saplings, adults, and snags.
 * </ul>
 * @return Filename written.
 */
const char* WriteTreePopulationSnagsFile2();

/**
 * Writes a parameter file for testing. Characteristics:
 * <ul>
 * <li>Two species.
 * <li>There is no behavior which uses snags.
 * <li>There is a behavior which uses stumps, but only for Species 1.
 * <li>There is a tree map with seedlings, saplings, adults, and snags.
 * </ul>
 * @return Filename written.
 */
const char* WriteTreePopulationSnagsFile3();

/**
 * Writes a parameter file for testing. Initial densities, snag aware run,
 * but no snag initial densities.
 * @return Filename written.
 */
const char* WriteSnagsInitFileRun1();

/**
 * Writes a parameter file for testing. Both live and snag initial densities,
 * multiple size classes, etc.
 * @return Filename written.
 */
const char* WriteSnagsInitFileRun2();


/**
 * Writes a parameter file for testing. Only snag initial densities, some
 * boundary testing.
 * @return Filename written.
 */
const char* WriteSnagsInitFileRun3();

/**
 * Writes a parameter file for testing. Snag initial densities in a not
 * snag aware run.
 * @return Filename written.
 */
const char* WriteSnagsInitFileRun4();


/**
 * Writes a common portion of the test parameter files.  This writes all
 * tree parameters and the rest of the plot.
 * @param oOut File stream to write to.
 */
void WriteTreePopulationSnagsCommonFileStuff(std::fstream &oOut);

/**
 * Writes a negative number for snag initial densities.
 */
const char* WriteSnagInitErrorFile1();

/**
 * Writes a non-number for snag initial densities.
 */
const char* WriteSnagInitErrorFile2();

/**
 * Size classes are missing.
 */
const char* WriteSnagInitErrorFile3();

/**
 * An unrecognized species is included.
 */
const char* WriteSnagInitErrorFile4();

/**
 * An unrecognized size class is included.
 */
const char* WriteSnagInitErrorFile5();

/**
 * An unrecognized size class is defined.
 */
const char* WriteSnagInitErrorFile6();

/**
 * Attempt to create init snags in the seedling size class.
 */
const char* WriteSnagInitErrorFile7();
//---------------------------------------------------------------------------
#endif // TestTreePopulation_H
