//---------------------------------------------------------------------------
// TestFuncResponseSeedPredation
//---------------------------------------------------------------------------
#if !defined(TestFuncResponseSeedPredation_H)
#define TestFuncResponseSeedPredation_H

class clGrid;

/**
 * Tests seed predation. This can't do a thorough test - this will test error
 * processing and cause an output file to be printed of seed model results
 * so the output can be checked manually.
 */


/**
 * Writes an XML file that will create the sim manager so we can create a
 * grid through the proper channels.  Characteristics:
 * <ul>
 * <li>Plot size of 160 m by 160 m.
 * <li>One species.
 * <li>Creates the seed grid with 1 grid cell the size of the plot.
 * <li>Predator initial density:  0.00046875
 * <li>Number of seeds:  51200000
 * <li>Max instantaneous decline rate:  -0.050622442
 * <li>Demographic efficiency:  0.000154258
 * <li>Density-dependent coefficient:  -0.000718667
 * <li>Maximum weekly intake:  7295.4
 * <li>Foraging efficiency:  0.001389
 * <li>Seedfall: 12 weeks.
 * <li>Model run:  52 weeks.
 * </ul>
 * @return Filename just written.
 */
const char* WriteFunResponseSeedPredationXMLFile1();

/**
 * Writes an XML file that will create the sim manager so we can create a
 * grid through the proper channels.  Characteristics:
 * <ul>
 * <li>Plot size of 160 m by 160 m.
 * <li>One species.
 * <li>Disperse behavior is present.
 * <li>Predator initial density:  0.46875
 * <li>Number of seeds:  51200000
 * <li>Max instantaneous decline rate:  -0.050622442
 * <li>Demographic efficiency:  0.000154258
 * <li>Density-dependent coefficient:  -0.000718667
 * <li>Maximum weekly intake:  7295.4
 * <li>Foraging efficiency:  0.001389
 * <li>Seedfall: 12 weeks.
 * <li>Model run:  52 weeks.
 * <li>Preserve predator density:  true.
 * </ul>
 * @return Filename just written.
 */
const char* WriteFunResponseSeedPredationXMLFile2();

/**
 * Writes an XML file that will create the sim manager so we can create a
 * grid through the proper channels.  Characteristics:
 * <ul>
 * <li>Plot size of 160 m by 160 m.
 * <li>One species.
 * <li>Disperse behavior is present.
 * <li>Predator initial density:  0.00046875
 * <li>Number of seeds:  51200000
 * <li>Max instantaneous decline rate:  -0.050622442
 * <li>Demographic efficiency:  0.000154258
 * <li>Density-dependent coefficient:  -0.000718667
 * <li>Maximum weekly intake:  7295.4
 * <li>Foraging efficiency:  0.001389
 * <li>Seedfall: 12 weeks.
 * <li>Model run:  52 weeks.
 * <li>Preserve predator density:  false.
 * </ul>
 * @return Filename just written.
 */
const char* WriteFunResponseSeedPredationXMLFile3();

/**
 * Writes an XML file that will create the sim manager so we can create a
 * grid through the proper channels.  Characteristics:
 * <ul>
 * <li>Plot size of 160 m by 160 m.
 * <li>One species.
 * <li>Disperse behavior is present.
 * <li>Predator initial density:  0.00046875
 * <li>Number of seeds:  51200000
 * <li>Max instantaneous decline rate:  -0.050622442
 * <li>Demographic efficiency:  0.000154258
 * <li>Density-dependent coefficient:  -0.000718667
 * <li>Maximum weekly intake:  7295.4
 * <li>Foraging efficiency:  0.001389
 * <li>Seedfall: 12 weeks.
 * <li>Model run:  52 weeks.
 * <li>Preserve predator density:  true.
 * <li>Seed grid map present, cells are 2 X 4
 * <li>Predator map present, resolution same as seed grid, values in each
 * cell = X + Y
 * </ul>
 * @return Filename just written.
 */
const char* WriteFunResponseSeedPredationXMLFile4();

/**
 * Writes a file with two timesteps where predator densities are to be
 * preserved.
 * @return Filename just written.
 */
const char* WriteFunResponseSeedPredationXMLFile6();

/**
 * Writes a file with two timesteps where predator densities are not to be
 * preserved.
 * @return Filename just written.
 */
const char* WriteFunResponseSeedPredationXMLFile7();

/**
 * Writes a file with multiple species, including one that is not applied to
 * seed predation.
 * @return Filename just written.
 */
const char* WriteFunResponseSeedPredationXMLFile8();

/**
 * Writes a file with multiple species, using both regular and linked seed
 * predation.
 * @return Filename just written.
 */
const char* WriteFunResponseSeedPredationXMLOfftakeTestFile2();

/**
 * Writes a file with multiple species, using linked seed predation.
 * @return Filename just written.
 */
const char* WriteFunResponseSeedPredationXMLOfftakeTestFile3();

/**
 * Writes a file with multiple species, using species- and season-specific
 * parameters.
 * @return Filename just written.
 */
const char* WriteFunResponseSeedPredationXMLOfftakeTestFile4();

/**
 * Creates file that has a predator initial density of 0.
 */
const char* WriteFunResponseSeedPredationXMLErrorFile1();

/**
 * Creates file that has no disperse behaviors.
 */
const char* WriteFunResponseSeedPredationXMLErrorFile2();

/**
 * Creates file that has maps for seed grid and seed predators, and X
 * resolutions don't match.
 */
const char* WriteFunResponseSeedPredationXMLErrorFile3();

/**
 * Creates file that has weeks of seedfall = 0.
 */
const char* WriteFunResponseSeedPredationXMLErrorFile4();

/**
 * Creates file that has weeks of model = 0.
 */
const char* WriteFunResponseSeedPredationXMLErrorFile5();

/**
 * Creates file that has maps for seed grid and seed predators, and Y
 * resolutions don't match.
 */
const char* WriteFunResponseSeedPredationXMLErrorFile6();

/**
 * Creates file that has a map for seed predators, but is missing the
 * data member "num preds".
 */
const char* WriteFunResponseSeedPredationXMLErrorFile7();

/**
 * Creates file where week germination starts is < 0.
 */
const char* WriteFunResponseSeedPredationXMLErrorFile8();

/**
 * Creates file where week germination starts is > 52.
 */
const char* WriteFunResponseSeedPredationXMLErrorFile9();

/**
 * Creates file where proportion germinating is < 0.
 */
const char* WriteFunResponseSeedPredationXMLErrorFile10();

/**
 * Creates file where proportion germinating is > 1.
 */
const char* WriteFunResponseSeedPredationXMLErrorFile11();
//---------------------------------------------------------------------------
#endif // TestFuncResponseSeedPredation_H
