//---------------------------------------------------------------------------
// TestSizeDependentLogisticMortalityH
//---------------------------------------------------------------------------
#if !defined(TestSizeDependentLogisticMortalityH)
#define TestSizeDependentLogisticMortalityH

/**
 * Writes a parameter file for testing. There are four species. The number of
 * years per timestep is 1.
 * @return Filename written.
 */
const char* WriteSizeDepLogMortXMLFile1();

/**
 * Writes a parameter file for testing. There are four species. The number of
 * years per timestep is 3.
 * @return Filename written.
 */
const char* WriteSizeDepLogMortXMLFile2();
#endif // TestStochasticMort_H
//---------------------------------------------------------------------------


