"""Run this once before Lab 1:  python course/tools/check_setup.py"""
import sys

def step(name, fn):
    try:
        info = fn()
        print(f"PASS  {name}" + (f"  ({info})" if info else ""))
        return True
    except Exception as e:
        print(f"FAIL  {name}  -> {e}")
        return False

def pyroot():
    import ROOT
    return ROOT.__version__

def roofit():
    import ROOT
    x = ROOT.RooRealVar("x", "x", -5, 5)
    g = ROOT.RooGaussian("g", "g", x, ROOT.RooFit.RooConst(0), ROOT.RooFit.RooConst(1))
    data = g.generate(x, 100)
    assert data.numEntries() == 100

def roostats():
    import ROOT
    ROOT.RooStats.ModelConfig("mc")

def tmva():
    import ROOT
    ROOT.TMVA.Tools.Instance()

def cpp_jit():
    import ROOT
    assert ROOT.gInterpreter.Declare("int sda_check() { auto f = [](int a) { return 2 * a; }; return f(21); }")
    assert ROOT.sda_check() == 42

def plotting():
    import numpy, matplotlib  # noqa: F401

results = [
    step("PyROOT import", pyroot),
    step("RooFit: build a pdf and generate toys", roofit),
    step("RooStats: ModelConfig", roostats),
    step("C++ JIT (modern C++ lambda)", cpp_jit),
    step("numpy + matplotlib", plotting),
]
step("TMVA (optional material only)", tmva)
print()
print("ALL GOOD" if all(results) else "Something failed: send the FAIL lines to the instructor.")
sys.exit(0 if all(results) else 1)
