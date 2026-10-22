# CMS: $H\to ZZ^*\to 4\ell$

**Field:** collider physics · **Used in:** Lab 4 (Exercise B)

**Question.** Is there a signal at 125 GeV in the four-lepton mass spectrum? What is the signal strength, and what does a control region say about the $ZZ$ background?

**Source.** CMS Open Data, tutorial *HiggsExample11-12* (`data/cms_m4l/README.md`). Paper: CMS, arXiv:1207.7235.

**Real measurement.** CMS Collaboration, “Observation of a new boson at a mass of 125 GeV with the CMS experiment at the LHC”, Phys. Lett. B 716 (2012) 30: [arXiv:1207.7235](https://arxiv.org/abs/1207.7235).

| File | Content |
|---|---|
| `data/cms_m4l/_cms_higgs_data.txt` | data histogram, bins of 3 GeV |
| `data/cms_m4l/_cms_higgs_{HZZto4l,ZZto4l,DYto4l,TTbarto4l}.txt` | simulated templates (expected events) |
| `data/cms_m4l/*.root` | the original open-data histogram files |

In the text files, line 1 is an empty underflow bin, lines 2–38 are the signal region (70–181 GeV, 37 bins) and the last line is the **overflow bin** ($m_{4\ell}>181$ GeV: 176 data events), used as a control region for $ZZ$.
