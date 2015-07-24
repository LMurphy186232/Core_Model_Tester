//---------------------------------------------------------------------------
// TestNCIPestGrowth
//---------------------------------------------------------------------------
#if !defined(TestNCIPestGrowth_H)
#define TestNCIPestGrowth_H
#include <fstream>
/**
 * Tests the pest effect of clNCIMasterGrowth.
 */

/**
 * Writes a file for normal processing.
 * @return Filename written.
 */
const char* WriteNCIPestGrowthXMLFile1();

/**
 * Writes a file for normal processing.
 * @return Filename written.
 */
const char* WriteNCIPestGrowthXMLFile2();

/**
 * Writes a file for normal processing.
 * @return Filename written.
 */
const char* WriteNCIPestGrowthXMLFile3();

/**
 * Writes a file for normal processing.
 * @return Filename written.
 */
const char* WriteNCIPestGrowthXMLFile4();

/**
 * Writes an error condition where infestation is not applied to a behavior
 * species.
 * @return Filename written.
 */
const char* WriteNCIPestGrowthXMLErrorFile1();

/**
 * Writes an error condition where X0 in size-dependent infestation is 0.
 * @return Filename written.
 */
const char* WriteNCIPestGrowthXMLErrorFile2();

/**
 * Writes an error condition where Xb in size-dependent infestation is 0.
 * @return Filename written.
 */
const char* WriteNCIPestGrowthXMLErrorFile3();

/**
 * Writes an error condition where infestation is not applied to a behavior
 * species and the shifted lognormal with infestation size effect is being
 * used.
 * @return Filename written.
 */
const char* WriteNCIPestGrowthXMLErrorFile4();

/**
 * Writes an error condition where infestation is not applied to a behavior
 * species and the compound exponential with infestation size effect is being
 * used.
 * @return Filename written.
 */
const char* WriteNCIPestGrowthXMLErrorFile5();

//---------------------------------------------------------------------------
#endif // TestNCIPestGrowth_H
