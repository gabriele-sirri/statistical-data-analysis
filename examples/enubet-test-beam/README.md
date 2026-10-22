# ENUBET: energy deposit in a scintillator pad

**Field:** beam instrumentation · **Used in:** extra case for self-study

**Question.** What is the fraction of events with two particles crossing the pad, and what is the detector resolution?

**Source.** Inspired by Figure 4 of “Status of the ENUBET project”, J. Phys.: Conf. Ser. 1056 (2018) 012047.

**Real measurement.** ENUBET Collaboration, “Status of the ENUBET project”, J. Phys.: Conf. Ser. 1056 (2018) 012047: [doi:10.1088/1742-6596/1056/1/012047](https://doi.org/10.1088/1742-6596/1056/1/012047).

| File | Content |
|---|---|
| `data/enubet_histo.dat` | 95 bins of the energy deposit (first bin centre 0.025, width 0.01; 5334 entries); two columns: bin centre, counts |

## Suggested path (self-study)

- **Lab 1/2:** composite non-extended model. One-particle deposit: Landau (mean in [0, 0.4], sigma in [0.005, 0.05]); two-particle deposit: the Landau convolved with itself; both smeared by a Gaussian resolution (sigma in [0.005, 0.08]). See `course/optional/convolution_resolution.ipynb`.
- **After Lab 3:** the resolution and the Landau parameters as nuisance parameters; effect on the 2-particle fraction.
- **After Lab 4:** binned model with HistFactory.
- *Caveat to watch:* correlation between the resolution and the Landau width.

The original exercise text is `exercise-original.md` (draft extraction). Solutions: see the `solutions` branch, if published.
