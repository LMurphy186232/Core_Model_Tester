//---------------------------------------------------------------------------
// TestTempDependentNeighborhoodSurvival
//---------------------------------------------------------------------------
#if !defined(TestTempDependentNeighborhoodSurvival_H)
#define TestTempDependentNeighborhoodSurvival_H

/**
 * This class tests the clTempDependentNeighborhoodSurvival class.
 */

/**
 * Writes a parameter file to direct testing.
 * @param iYearsPerTimestep The desired number of years per time step.
 * @return Filename written.
 */
const char* WriteTempDependentNeighborhoodSurvivalXMLFile(int iYearsPerTimestep );

/**
 * Writes a parameter file to direct testing. One of the values for N
 * equals zero.
 * @return Filename written.
 */
const char* WriteTempDependentNeighborhoodSurvivalXMLErrorFile1();

/**
 * Writes a parameter file to direct testing. The value for search radius
 * is less than zero.
 * @return Filename written.
 */
const char* WriteTempDependentNeighborhoodSurvivalXMLErrorFile2();
//---------------------------------------------------------------------------
#endif // TestTempDependentNeighborhoodSurvival_H
