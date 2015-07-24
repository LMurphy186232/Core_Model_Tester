//---------------------------------------------------------------------------

#ifndef TestGrowthOrgH
#define TestGrowthOrgH

/**
 * Tests the clGrowthOrg object.  This specifically makes sure that auto-update
 * diameter growth and separate diameter-height growth updating work correctly.
 * The individual growth behaviors are tested elsewhere.
 */

/**
 * Writes a parameter file to direct testing.  This contains two species, with
 * either constant basal area or constant radial growth assigned, with both
 * auto-update and diameter and height increment setting done separately.
 *
 * @return Filename written.
 */
const char* WriteGrowthOrgXMLFile1();

/**
 * Writes a parameter file to direct testing for normal processing run 2.
 * This contains four species, with each one being assigned a diameter-height
 * growth behavior combination that checks all possible precedence request
 * situations.
 * @return Filename written.
 */
const char* WriteGrowthOrgXMLFile2();


/**
 * Writes a parameter file to direct testing for an intentionally triggered
 * error.  This file contains a tree species/type combo that has a diameter-
 * only growth behavior without a corresponding height-only growth behavior.
 *
 * @return Filename written.
 */
const char* WriteGrowthOrgXMLErrorFile1();

/**
 * Writes a parameter file to direct testing for an intentionally triggered
 * error.  This file contains a tree species/type combo that has a height-
 * only growth behavior without a corresponding diameter-only growth behavior.
 *
 * @return Filename written.
 */
const char* WriteGrowthOrgXMLErrorFile2();

//---------------------------------------------------------------------------
#endif
