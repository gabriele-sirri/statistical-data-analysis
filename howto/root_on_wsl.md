# WSL Setup Guide with ROOT, Jupyter, and VS Code (Ubuntu 24.04)

## References
- **Microsoft WSL Commands:**  
  [https://learn.microsoft.com/en-us/windows/wsl/basic-commands](https://learn.microsoft.com/en-us/windows/wsl/basic-commands)

---

## 1. Basic WSL Commands

```powershell
wsl --list --verbose        # List installed distros
wsl --list --online         # Show available distros
wsl --install Ubuntu-24.04  # Install a new distribution (e.g., Ubuntu 24.04)
                            # (add "--name newname" to assign a new name)
wsl --unregister <distro>   # Remove a distribution and all its data (caution!)
wsl --set-default <distro>  # Set a distribution as the default
```

**Tip:**  
To access Linux folders directly in File Explorer, open:  
`\\wsl$\Ubuntu-24.04\home\<username>`


---

## 2. Install ROOT on Ubuntu 24.04

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

#### 3️⃣ Download and Set Up ROOT

note choose the download file according to the actual Linux distribution 

```bash


cd $HOME
wget https://root.cern/download/root_v6.36.04.Linux-ubuntu24.04-x86_64-gcc13.3.tar.gz
tar -xzvf root_v6.36.04.Linux-ubuntu24.04-x86_64-gcc13.3.tar.gz
echo >> ~/.bashrc
echo "source \$HOME/root/bin/thisroot.sh" >> ~/.bashrc
cat ~/.bashrc
exit
```

#### 4️⃣ Verify Installation
```bash
wsl
cd $HOME
root
root[] new TBrowser
root[].q
```

---

## 3. Install Jupyter Notebook on Ubuntu 24.04

**Reference:**  
[Install Jupyter Notebook on Ubuntu 24.04](https://docs.vultr.com/how-to-install-jupyter-notebook-on-ubuntu-24-04)

```bash
sudo apt install jupyter-notebook -y
jupyter-notebook --version
```

---

## 4. Developing in WSL with Visual Studio Code

https://code.visualstudio.com/docs/remote/wsl

> The lab version of VS Code may be outdated.  
> Do **not** use the desktop icon or run `code` from inside WSL.

### Steps

#### 1 Download and Install VS Code
- Visit [https://code.visualstudio.com/](https://code.visualstudio.com/)
- Click **Download for Windows**
- Install as a **user instance**
- Rename the desktop shortcut (e.g., *Visual Studio Code - User*)

#### 2 Setup extensions locally on the UI / client side
- Close the *Welcome* window
- Open the **Extensions** panel (`Ctrl + Shift + X`)
- Install:
  - **WSL**

#### 3 Connect VS Code to WSL
- Click the **blue status bar** (bottom-left corner) → *Connect to WSL*
- When connected, it should display *WSL: Ubuntu-24.04*

#### 2 Setup extensions in WSL side 
- Close the *Welcome* window
- Open the **Extensions** panel (`Ctrl + Shift + X`)
- Install, on the WSL:
  - **Python**
  - **Jupyter**


#### 5 Run Jupyter Notebooks
- Open a new file → choose *Jupyter Notebook*
- In the top-right corner, click **Select Kernel → Python Environments**
- Select the first (recommended) Python environment

 **Your Jupyter Notebook is now running inside WSL!**

---
