# Running C++ Files in GitHub Codespaces

## 1. Open Codespaces
1. Go to the repository on GitHub.
2. Click on **Code** > **Codespaces**.
3. Click on an existing Codespace or create a new one.

---

## 2. Install a C++ Compiler
If your Codespace environment doesn’t already have a C++ compiler, install it:

1. Open the terminal in Codespaces.
2. Run the following command to install `g++`:
   ```bash
   sudo apt update && sudo apt install g++
   ```

---

## 3. Write Your C++ Code
1. In the file explorer, create a new file with a `.cpp` extension, e.g., `main.cpp`.
2. Write your C++ code in the file.

---

## 4. Compile and Run
You can compile and run your C++ program using the terminal:

1. **Compile the C++ file**:
   ```bash
   g++ -o output main.cpp
   ```
   This generates an executable file named `output`.

2. **Run the compiled program**:
   ```bash
   ./output
   ```

---

## 5. Use Tasks for Automation (Optional)
To streamline the process, configure a build task in Codespaces:

1. Create a `.vscode/tasks.json` file.
2. Add the following configuration:
   ```json
   {
       "version": "2.0.0",
       "tasks": [
           {
               "label": "Build and Run C++",
               "type": "shell",
               "command": "g++",
               "args": [
                   "-g",
                   "${file}",
                   "-o",
                   "${fileDirname}/${fileBasenameNoExtension}"
               ],
               "group": {
                   "kind": "build",
                   "isDefault": true
               },
               "problemMatcher": ["$gcc"],
               "detail": "Generated task for building C++ file"
           }
       ]
   }
   ```
3. Now you can press **Ctrl+Shift+B** (or **Cmd+Shift+B** on macOS) to build and run the program automatically.

---

## 6. Debugging (Optional)
To debug your C++ program:
1. Install the **C/C++ extension** in Codespaces (if not already installed).
2. Configure a `.vscode/launch.json` file for debugging:
   ```json
   {
       "version": "0.2.0",
       "configurations": [
           {
               "name": "C++ Debug",
               "type": "cppdbg",
               "request": "launch",
               "program": "${workspaceFolder}/output",
               "args": [],
               "stopAtEntry": false,
               "cwd": "${workspaceFolder}",
               "environment": [],
               "externalConsole": false,
               "MIMode": "gdb",
               "setupCommands": [
                   {
                       "description": "Enable pretty-printing for gdb",
                       "text": "-enable-pretty-printing",
                       "ignoreFailures": true
                   }
               ],
               "preLaunchTask": "Build and Run C++"
           }
       ]
   }
   ```

---

You can now write, compile, and debug C++ files in GitHub Codespaces!
