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

## 2. Install ROOT and Jupyter

WSL runs Ubuntu: open the Ubuntu terminal and follow [`root_on_ubuntu.md`](root_on_ubuntu.md).

To check it later from Windows, open a new terminal and run `wsl`, then `cd $HOME` and `root`.

---

## 3. Developing in WSL with Visual Studio Code

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
