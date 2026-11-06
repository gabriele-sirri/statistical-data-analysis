# Course module: hands-on labs

Four labs of four hours (9:00–13:00), two weeks apart. Tools: **ROOT, RooFit, RooStats, HistFactory**. Python first; modern C++ where it matters.

| Lab | Topic | Slides | Notebooks | Data / case |
|---|---|---|---|---|
| 1 | Data model, RooFit, fits | [`slides/lab1.md`](slides/lab1.md) | [`lab1/`](lab1/) | [`lhcb-b0-ppbar`](../examples/lhcb-b0-ppbar/) |
| 2 | Likelihood, MINUIT, toys, nuisance parameters | [`slides/lab2.md`](slides/lab2.md) | [`lab2/`](lab2) | [`lhcb-b0-ppbar`](../examples/lhcb-b0-ppbar/), [`top-quark-on-off`](../examples/top-quark-on-off/) |
| 3 | Systematics, RooStats, correlations | [`slides/lab3.md`](slides/lab3.md) | [`lab3/`](lab3) | [`top-quark-on-off`](../examples/top-quark-on-off/), [`opera-tau-appearance`](../examples/opera-tau-appearance/) |
| 4 | HistFactory, RDataFrame `Vary`, TMVA demo | [`slides/lab4.md`](slides/lab4.md), [`slides/lab4_tmva.md`](slides/lab4_tmva.md) | [`lab4/`](lab4) | [`cms-higgs-4l`](../examples/cms-higgs-4l/), [`magic-gamma-hadron`](../examples/magic-gamma-hadron/), [`third_party/`](../third_party/) |
| — | Optional: RDataFrame + C++ JIT, convolution, CL$_s$ | — | [`optional/`](optional/) | … |

## How to start
1. **Your own laptop with ROOT** is the default: guides in [`docs/`](../docs), environment `environment.yml`, root README for details.
2. **No working ROOT?** Use **GitHub Codespaces** in a browser on a lab computer (free GitHub account needed; badge in the root README).
3. Run `python course/tools/check_setup.py`: every line must say PASS. Do it before Lab 1.
4. Open `course/lab1/ex_A.ipynb`.

In Codespaces your files stay in your codespace. To submit, download the notebook and upload it on Virtuale. Stop the codespace when you finish. Free quota: 60 hours per month on a 2-core codespace. Closing the browser does **not** stop it: it keeps running (and consuming quota) until the idle timeout, 30 minutes by default.

## What to submit

The outcome of the lab module is **work done** or **work not yet submitted**. *Work done* gives access to the written exam.

| Lab | Notebooks | You submit |
|---|---|---|
| 1 | A, B, C | **2 of 3**, your choice |
| 2 | A, B, C | **2 of 3**, your choice |
| 3 | A, B, C | **2 of 3**, your choice |
| 4 | A, B | **both** A and B |

Total: **8 notebooks**. We work on all of them in class. At the start of each lab we look at the solutions of the previous one, and then they are published.
Each notebook must run top to bottom with every check at `PASS`. Upload them on **Virtuale**, one file per notebook. Notebooks of the same lab are independent: you can choose any two.

## Conventions
- Notebooks have `TODO` cells and **check cells** (`PASS`/`FAIL`). A FAIL stops the notebook.
- Set `MATRICOLA` (your student ID) in the first cell: it seeds your toy data.
- Slides are Markdown (Marp): view with the *Marp for VS Code* extension or `marp file.md --pdf`.
- Solutions: we look at them at the start of the next lab, then they are published (branch `solutions`).
