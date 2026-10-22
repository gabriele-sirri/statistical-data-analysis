# MAGIC: gamma / hadron separation

**Field:** astroparticle physics · **Used in:** Lab 4 (guided demo C: TMVA) · also an extra case for self-study

**Question.** How well can ten image parameters separate gamma showers from hadronic ones, and what significance follows from a given selection?

**Source.** MAGIC gamma telescope dataset (UCI repository, see `data/magic04.names`): simulated Cherenkov telescope events.

**Real measurement.** None: the events are Monte Carlo simulated for the MAGIC telescope. Dataset: [UCI Machine Learning Repository, MAGIC Gamma Telescope](https://archive.ics.uci.edu/dataset/159/magic+gamma+telescope) (CC BY 4.0). Reference: R. K. Bock et al., Nucl. Instrum. Methods A 516 (2004) 511–528.

| File | Content |
|---|---|
| `data/magic04.data` | 19 020 events: 10 image parameters and the class `g` (gamma) or `h` (hadron) |
| `data/magic04.names` | description of the columns |

## Suggested path (self-study)

- **After Lab 2:** study one discriminating variable: fit its distribution for gammas and hadrons.
- **After Lab 3:** efficiency and rejection of a selection (cuts or a classifier), expected yields, significance with the Asimov formula and with RooStats; the selection efficiency as a systematic. The TMVA demo of Lab 4 is `course/lab4/demo_C_tmva.ipynb`.
- **After Lab 4:** binned model of the classifier output.
- *Caveat to watch:* the class balance of the file is not the real one: efficiencies transfer, purity does not.

The original exercise text is `exercise-original.md` (draft extraction). Solutions: see the `solutions` branch, if published.
