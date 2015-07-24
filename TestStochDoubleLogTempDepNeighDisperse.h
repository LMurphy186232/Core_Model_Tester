//---------------------------------------------------------------------------
// TestStochDoubleLogTempDepNeighDisperse
//---------------------------------------------------------------------------
#if !defined(TestStochDoubleLogTempDepNeighDisperse_H)
#define TestStochDoubleLogTempDepNeighDisperse_H

/**
 * This class tests the clStochDoubleLogTempDepNeighDisperse class.
 */

const char* WriteXMLFile1();
const char* WriteXMLFile2();

/**
 * Writes a parameter file to direct testing.
 * @param iYearsPerTimestep The desired number of years per time step.
 * @return Filename written.
 */
const char* WriteXMLFile34(int iYearsPerTimestep );
//---------------------------------------------------------------------------
#endif // TestStochDoubleLogTempDepNeighDisperse_H
