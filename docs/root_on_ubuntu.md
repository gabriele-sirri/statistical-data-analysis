# ROOT, Jupyter and PyROOT on Ubuntu 24.04

This guide is for **Ubuntu 24.04**, installed natively or inside **WSL** on Windows (WSL is Ubuntu running inside Windows: see [`root_on_wsl.md`](root_on_wsl.md) to install it first, then follow this guide in the Ubuntu terminal).

There are two ways. Pick **one**.

- **Option A: course environment with conda** (fastest, if you already use conda/mamba): from the repository folder, `conda env create -f environment.yml`, then `conda activate sda`. It contains ROOT, PyROOT, Jupyter and the compiler.
- **Option B: ROOT binary from root.cern** (below).

---

## Option B: install ROOT from the binary distribution

**Reference:**  
[ROOT Installation Guide](https://github.com/Programmazione-per-la-Fisica/howto/blob/main/other-OSes/rootGuide.md) by _Programmazione per la Fisica_ 
in Italian

### Steps

#### 1️⃣ Update Packages
```bash
sudo apt update && sudo apt upgrade -y
```

#### 2️⃣ Install Dependencies
```bash
sudo apt install binutils cmake dpkg-dev g++ gcc libssl-dev git \
libx11-dev libxext-dev libxft-dev libxpm-dev python3 libtbb-dev \
libvdt-dev libgif-dev gfortran libpcre3-dev libglu1-mesa-dev \
libglew-dev libftgl-dev libfftw3-dev libcfitsio-dev libgraphviz-dev \
libavahi-compat-libdnssd-dev libldap2-dev python3-dev python3-numpy \
libxml2-dev libkrb5-dev libgsl-dev qtwebengine5-dev \
nlohmann-json3-dev libmysqlclient-dev libgl2ps-dev liblzma-dev \
libxxhash-dev liblz4-dev -y
```

> ⚠️ `libzstd-dev` may cause installation errors — skip if needed.

```bash
sudo apt install libgsl0-dev -y
```

#### 3️⃣ Download and Extract ROOT

Choose the correct ROOT binary for your Linux distribution (the current releases are listed at [root.cern/install](https://root.cern/install/)), then run:

```bash
cd $HOME
wget https://root.cern/download/root_v6.36.04.Linux-ubuntu24.04-x86_64-gcc13.3.tar.gz
tar -xzvf root_v6.36.04.Linux-ubuntu24.04-x86_64-gcc13.3.tar.gz
```

#### 4️⃣ Set Up the ROOT Environment

Add ROOT to your shell startup file, e.g. using the commands below, then **open a new terminal**:

```bash
echo >> ~/.bashrc
echo "source \$HOME/root/bin/thisroot.sh" >> ~/.bashrc
cat ~/.bashrc
```

#### 5️⃣ Verify Installation
```bash
cd $HOME
root
root[] new TBrowser
root[].q
```

Check that PyROOT works: `python3 -c "import ROOT; print(ROOT.gROOT.GetVersion())"`.

---

## Jupyter Notebook

*(With Option A, Jupyter is already in the environment: skip this section.)*

**Reference:**  
[Install Jupyter Notebook on Ubuntu 24.04](https://docs.vultr.com/how-to-install-jupyter-notebook-on-ubuntu-24-04)

```bash
sudo apt install jupyter-notebook -y
jupyter-notebook --version
```
