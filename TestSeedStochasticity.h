//---------------------------------------------------------------------------
// TestSeedStochasticity
//---------------------------------------------------------------------------
#if !defined(TestSeedStochasticity_H)
#define TestSeedStochasticity_H

/**
 * This class tests seed stochasticity. Actual stochastic seed distributions
 * cannot be tested - those must be done visually.
 */

/**
 * Writes a parameter file with five species, one for each disperse object
 * type.
 * @return Filename written.
 */
const char* WriteSeedStochasticityXMLFile1();
//---------------------------------------------------------------------------
#endif // TestSeedStochasticity_H
