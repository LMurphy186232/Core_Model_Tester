//---------------------------------------------------------------------------
// TestNonSpatialDispersal
//---------------------------------------------------------------------------
#if !defined(TestNonSpatialDispersal_H)
#define TestNonSpatialDispersal_H

/**
 * This class tests the non-spatial dispersal behavior.  It writes out
 * parameter files and uses them as input to perform setup; it then sets up
 * the desired initial conditions, causes the behavior to run, then tests its
 * output.  There will be two normal processing runs.  Both use deterministic
 * seed numbers, which should equal the expected mean +- 1.
 */

/**
 * Writes a parameter file to direct testing using the first set of testing
 * conditions. This contains all tree information and disperse information.
 * It also has a tree map so we'll be dealing with a known list of trees. The
 * timestep length is 1 year.
 * @return Filename written.
 */
const char* WriteNonSpatialDispersalXMLFile1();

/**
 * Writes a parameter file to direct testing using the second set of testing
 * conditions (same as the first set, just different number of years per
 * timestep). This contains all tree information and disperse information. It
 * also has a tree map so we'll be dealing with a known list of trees.  The
 * timestep length is three years.
 * @return Filename written.
 */
const char* WriteNonSpatialDispersalXMLFile2();
//---------------------------------------------------------------------------
#endif // TestNonSpatialDispersal_H
