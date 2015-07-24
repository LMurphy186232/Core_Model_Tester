//---------------------------------------------------------------------------
// TestClimateCompDepNeighborhoodSurvival
//---------------------------------------------------------------------------
#if !defined(TestClimateCompDepNeighborhoodSurvival_H)
#define TestClimateCompDepNeighborhoodSurvival_H

/**
 * This class tests the clTempDependentNeighborhoodSurvival class.
 */

/**
 * Writes a parameter file to direct testing.
 * @param iYearsPerTimestep The desired number of years per time step.
 * @return Filename written.
 */
const char* WriteClimateCompDepNeighborhoodSurvivalXMLFile(int iYearsPerTimestep );

/**
 * Writes a parameter file to direct testing. One of the values for N
 * equals zero.
 * @return Filename written.
 */
const char* WriteClimateCompDepNeighborhoodSurvivalXMLErrorFile1();

/**
 * Writes a parameter file to direct testing. The value for search radius
 * is less than zero.
 * @return Filename written.
 */
const char* WriteClimateCompDepNeighborhoodSurvivalXMLErrorFile2();

/**
 * Writes a parameter file to direct testing. One of the values for D
 * equals zero.
 * @return Filename written.
 */
const char* WriteClimateCompDepNeighborhoodSurvivalXMLErrorFile3();
//---------------------------------------------------------------------------
#endif // TestClimateCompDepNeighborhoodSurvival_H
