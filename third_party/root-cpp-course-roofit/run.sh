#!/bin/sh
# Run the full course pipeline with ROOT macros:
#   make_toys  : simulator NTuples (sim.root weighted MC, data.root "real data")
#   unbinned   : Part 1 — analytic-shape unbinned mass fit on the data
#   analysis   : RDF analysis with Vary (systematic template histograms)
#   fit        : Part 2 — HistFactory template fit of mu and theta
#   likelihood : Part 3 — likelihood anatomy on the Part-2 workspace
set -e
cd "$(dirname "$0")"

echo "=== step 1: simulator NTuples ==="
root -b -q make_toys.cpp
echo
echo "=== part 1: unbinned analytic-shape fit ==="
root -b -l -q unbinned.cpp
echo
echo "=== part 2a: RDF analysis (+Vary histograms) ==="
root -b -l -q analysis.cpp
echo
echo "=== part 2b: HistFactory fit ==="
root -b -l -q histfactory.cpp
echo
echo "=== part 3: likelihood anatomy ==="
root -b -l -q likelihood.cpp
