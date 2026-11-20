# Examples: real measurements, simplified for teaching

Each case is a **simplified analysis modelled on a real measurement**. Every folder has a `README.md` (the physics, the data and the link to the paper), a `data/` folder and the original exercise text (`exercise-original.md`). Solutions are **not** here: see the `solutions` branch.

## The gallery

**[LHCb: the rarest $B^0$ decay ever observed](lhcb-b0-ppbar/)** · Labs 1 and 2
*In 2017 LHCb saw, for the first time, a $B^0$ meson decay into a proton and an antiproton: about one decay in eighty million. A small peak on a flat background: is it a discovery?* Paper: [arXiv:1709.01156](https://arxiv.org/abs/1709.01156).

![w:420](lhcb-b0-ppbar/fit_result.png)

**[D0: the top quark](top-quark-on-off/)** · Labs 2 and 3
*In 1995 D0 and CDF announced the discovery of the top quark at Fermilab. D0 counted 17 events where 3.8 ± 0.6 were expected from the background. How significant is that?* Paper: [arXiv:hep-ex/9503003](https://arxiv.org/abs/hep-ex/9503003).

<!-- FIGURE: top-quark-on-off/fit_result.png -->

**[OPERA: the appearance of $\nu_\tau$](opera-tau-appearance/)** · Lab 3
*A beam of muon neutrinos goes from CERN to the Gran Sasso laboratory, 730 km away. OPERA looked, with emulsion detectors, for the few tau neutrinos that appear on the way.* Papers: [arXiv:1804.04912](https://arxiv.org/abs/1804.04912), [arXiv:1507.01417](https://arxiv.org/abs/1507.01417).

<!-- FIGURE: opera-tau-appearance/fit_result.png -->

**[CMS: a new boson, in four leptons](cms-higgs-4l/)** · Lab 4
*In 2012 CMS and ATLAS announced a new boson at about 125 GeV. The cleanest signature is its decay into four leptons: a narrow peak over a small background.* Paper: [arXiv:1207.7235](https://arxiv.org/abs/1207.7235).

<!-- FIGURE: cms-higgs-4l/fit_result.png -->

**[MAGIC: gamma rays among cosmic rays](magic-gamma-hadron/)** · Lab 4 (TMVA demo)
*The MAGIC telescopes see the Cherenkov light of the showers that particles produce in the atmosphere. Gamma rays are few, hadrons are many: a classifier has to tell them apart.* Dataset: [UCI](https://archive.ics.uci.edu/dataset/159/magic+gamma+telescope).

<!-- FIGURE: magic-gamma-hadron/fit_result.png -->

**[CUORE-0: the neutrinoless double-beta decay](cuore0/)** · self-study
*Crystals of tellurium oxide, cooled close to absolute zero under the Gran Sasso mountain, wait for a decay that would show that neutrinos are their own antiparticles.* Paper: [arXiv:1504.02454](https://arxiv.org/abs/1504.02454).

<!-- FIGURE: cuore0/fit_result.png -->

**[IceCube: neutrinos that disappear](icecube-oscillations/)** · self-study
*IceCube DeepCore, in the Antarctic ice, measures the atmospheric muon neutrinos that cross the Earth: fewer arrive than expected, because they oscillate.* Paper: [arXiv:1410.7227](https://arxiv.org/abs/1410.7227).

<!-- FIGURE: icecube-oscillations/fit_result.png -->

**[MINOS: oscillations with a beam](minos-oscillations/)** · self-study
*A neutrino beam leaves Fermilab, crosses 735 km of rock, and reaches the MINOS detector in Minnesota: the energy spectrum tells the oscillation parameters.* Paper: [arXiv:1304.6335](https://arxiv.org/abs/1304.6335).

<!-- FIGURE: minos-oscillations/fit_result.png -->

**[ENUBET: a monitored neutrino beam](enubet-test-beam/)** · self-study
*To know how many neutrinos a beam contains, ENUBET measures the leptons produced together with them. The exercise starts from a test-beam histogram.* Paper: [doi:10.1088/1742-6596/1056/1/012047](https://doi.org/10.1088/1742-6596/1056/1/012047).

<!-- FIGURE: enubet-test-beam/fit_result.png -->

## The table

| Case | Field | Role in the course | Data |
|---|---|---|---|
| [`lhcb-b0-ppbar`](lhcb-b0-ppbar/) | flavour | **Lab 1, Lab 2** | 166 masses, a mass histogram |
| [`top-quark-on-off`](top-quark-on-off/) | collider | **Lab 2, Lab 3** | three numbers |
| [`opera-tau-appearance`](opera-tau-appearance/) | neutrino | **Lab 3** | published table |
| [`cms-higgs-4l`](cms-higgs-4l/) | collider | **Lab 4** | CMS Open Data templates |
| [`cuore0`](cuore0/) | nuclear | extra case (self-study) | 233 energies |
| [`icecube-oscillations`](icecube-oscillations/) | neutrino | extra case (self-study) | 64 bins |
| [`minos-oscillations`](minos-oscillations/) | neutrino | extra case (self-study) | 3470 events + MC |
| [`magic-gamma-hadron`](magic-gamma-hadron/) | astroparticle | **Lab 4** (demo C: TMVA), extra case | 19 020 events |
| [`enubet-test-beam`](enubet-test-beam/) | instrumentation | extra case (self-study) | 95-bin histogram |

**Notes**
- The problems are simplified on purpose and imitate the published plots. Do not quote physics results from them.
- `exercise-original.md`: the original statement of the exercise, as plain text (equations, figures and tables are not included).
- The extra cases are for self-study: each has a suggested path to follow on your own after the corresponding lab.
- Adding a case = adding a folder with the same four parts.
