//---------------------------------------------------------------------------
// TestSpatialDispersal
//---------------------------------------------------------------------------
#if !defined(TestSpatialDispersal_H)
#define TestSpatialDispersal_H

class clGrid;


/**
 * This class tests the spatial dispersal behavior. It writes out parameter
 * files and uses them as input to perform setup; it then sets up the desired
 * initial conditions, causes the behavior to run, then tests its output.
 *
 * Two runs will be tested:  one in which the timestep length is 1 year and the
 * dimensions of the seed grid are explicitly set to 2X4 m, and one in which the
 * timestep length is 4 years and the dimensions of the seed grid are left to
 * default. The first parameter file is run for 2 timesteps to ensure that the
 * seed grid is cleared between timesteps.
 */


/**
 * Verifies the numbers of seeds for timestep 1 during TestDispersal1.
 */
void VerifyXMLFile1Timestep1(clGrid *p_oSeedGrid);

/**
 * Verifies the numbers of seeds for timestep 2 during TestDispersal1. This
 * checks two things:  one, that the number of seeds got cleaned out during
 * timestep cleanup, and two, that the stump was removed.  (So the number
 * of seeds for one species will be slightly different.)
 */
void VerifyXMLFile1Timestep2(clGrid *p_oSeedGrid);


/**
 * Verifies the numbers of seeds during TestDispersal2.
 */
void VerifyXMLFile2(clGrid *p_oSeedGrid);

/**
 * Writes a parameter file to direct testing using the first set of testing
 * conditions. This contains all tree information and disperse information.
 * It also has a tree map so we'll be dealing with a known list of trees.
 * @return Filename written.
 */
const char* WriteSpatialDispersalXMLFile1();

/**
 * Writes a parameter file to direct testing using the second set of testing
 * conditions. This contains all tree information and disperse information.
 * It also has a tree map so we'll be dealing with a known list of trees.
 * @return Filename written.
 */
const char* WriteSpatialDispersalXMLFile2();

/**
 * Re-does test 1, but with the beta and STRs only using one set of tags
 * per function.
 * @return Filename written.
 */
const char* WriteSpatialDispersalXMLFile3();
//---------------------------------------------------------------------------

#endif // TestSpatialDispersal_H
