//---------------------------------------------------------------------------
// TestStochasticMort_H
//---------------------------------------------------------------------------
#if !defined(TestStochasticMort_H)
#define TestStochasticMort_H

/**
 * Writes a parameter file for testing. There are four species: one whose
 * mortality rate is 0, one whose mortality rate is 1, one whose mortality
 * rate is 0.25, and one to which mortality does not apply. The number of
 * years per timestep is 1. The behavior is adult stochastic mortality.
 * @return Filename written.
 */
const char* WriteStochasticMortXMLFile1();

/**
 * Writes a parameter file for testing. This is the same as
 * WriteStochasticMortXMLFile1(), except the number of years per timestep is 3
 * and it's juvenile stochastic mortality.
 * @return Filename written.
 */
const char* WriteStochasticMortXMLFile2();
#endif // TestStochasticMort_H
//---------------------------------------------------------------------------


