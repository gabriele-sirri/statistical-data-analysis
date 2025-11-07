### Running ROOT on Windows

Follow these steps to install and run **ROOT** on Windows:

1. **Download ROOT**

    Visit the official ROOT website: [https://root.cern/install/](https://root.cern/install/)
   * Under **Download a pre-compiled binary distribution**, select the Reelase and then the precompiled binary for Windows.
   * Download and extract the `.zip` file to the folder where you want to install ROOT.

2. **Set Up the Environment**

   * Open **Command Prompt**.
   * Navigate to the `bin` folder of your ROOT installation:

     ```bash
     cd your_path\to\root-6.xx.x\bin
     ```
     *(Replace `your_path\to\...` with the actual path to your ROOT folder.)*

   * To temporarily configure the environment variables for this session, run:
     ```bash
     thisroot.bat
     ```

3. **Run ROOT**

   * Change to the directory where you want to save or run your ROOT scripts:

     ```bash
     cd path\to\your\working_directory
     ```
   * Start ROOT by typing:

     ```bash
     root
     ```

4. **Write and Execute a Script**

   * Create a C++ script using **Notepad**, **Notepad++**, **Visual Studio Code**, or any other text editor.
   * Save the file in your working directory with a `.cpp` extension
     *(e.g., `your_script.cpp`)*.
   * Inside the ROOT prompt, load and execute your script:

     ```bash
     .x your_script.cpp
     ```
