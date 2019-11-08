#if !defined(TestNCIMasterQuadratGrowth_H)
#define TestNCIMasterQuadratGrowth_H
#include <fstream>

/**
 * Tests the clNCIMasterQuadratGrowth class and associated effects.
 */

/**
 * Writes a parameter file with the designated number of years per time step.
 * @param iYearsPerTimestep The desired number of years per time step.
 * @param iPrecip Precipitation type.
 * @return Filename written.
 */
const char* WriteNCIQuadratGrowthXMLFile(int iYearsPerTimestep, int iPrecip );

/**
 * Writes a parameter file with the designated number of years per time step.
 * @param iYearsPerTimestep The desired number of years per time step.
 * @param iPrecip Precipitation type.
 * @return Filename written.
 */
const char* WriteNCIQuadratGrowthXMLFile2(int iYearsPerTimestep, int iPrecip );

/**
 * Writes an error condition where max growth for a species is < 0.
 * @return Filename written.
 */
const char* WriteNCIQuadratGrowthXMLErrorFile1();

//---------------------------------------------------------------------------
#endif // TestNCIQuadratGrowth_H
