<!-- TABLE OF CONTENTS -->
<details>
  <summary>Table of Contents</summary>
  <ol>
    <li>
      <a href="#about-the-project">About The Project</a>
      <ul>
        <li><a href="#how-it-works">How It Works</a></li>
        <li><a href="#future-extensions">Future Extensions</a></li>
        <li><a href="#built-with">Built With</a></li>
      </ul>
    </li>
    <li>
      <a href="#getting-started">Getting Started</a>
      <ul>
        <li><a href="#prerequisites">Prerequisites</a></li>
        <li><a href="#installation">Installation</a></li>
      </ul>
    </li>
    <li><a href="#how-to-use">How To Use</a></li>
    <li><a href="#license">License</a></li>
    <li><a href="#contact">Contact</a></li>
  </ol>
</details>

<!-- ABOUT THE PROJECT -->
## 📘 About The Project

**Maze Runner** is a C++ application inspired by **Minecraft**, designed to simulate maze structures and guide a player or agent through them to find an exit. The project emphasizes both performance and user accessibility, allowing anyone to explore algorithmic maze-solving without needing any programming knowledge.

The application runs entirely in the **terminal**, providing a simple interface for users to:
- Build a maze within a Minecraft-inspired environment
- Validate custom maze structures
- Solve the maze using intelligent logic

Users can choose to either:
- Generate a random, playable maze with a single command, or
- Upload their own maze layout for validation and solving.

Validating your maze is essential before solving. An ideal maze:
- Contains no loops
- Has no isolated cells
- Includes exactly one entrance and one exit

If your maze doesn't meet these criteria, the application includes a powerful extension that can automatically **repair broken mazes** and make them suitable for solving.

---

**⚠️ Watch the video for a full walkthrough of the application and how it works — it’s highly recommended before you start!**

<p align="right">(<a href="#table-of-contents">back to top</a>)</p>

## 🧬 How It Works

The **Maze Runner** application is a terminal-based C++ program that allows users to interact with and manipulate mazes through a structured and user-friendly interface.

### Maze Generation
Users can generate randomized mazes by specifying the desired width and height (odd integers only). The maze generation leverages a **recursive backtracking algorithm** to ensure unique and solvable maze patterns on each run. A **dynamic 2D array** is used for memory-efficient construction and manipulation of the maze structure. This design allows users to easily regenerate or resize the maze as needed.

### Custom Maze Import
The application supports importing user-defined maze structures. Once a custom maze is uploaded, it can be validated using integrated algorithms. The validation process uses a combination of **backtracking** and **depth-first search (DFS)** to ensure the maze conforms to the following constraints:
- Exactly one valid entry and exit
- No circular paths (loops)
- No isolated cells

### Minecraft Integration
Once a valid maze structure is confirmed, users can render the maze within a Minecraft world. The system uses Minecraft API to place the maze in a user-specified location, enabling real-time exploration of the generated maze structure.

### Maze Solving
Users can attempt to solve the maze manually or request automated assistance. The system tracks player movement using a **linked list data structure**, allowing for real-time intervention and analysis. The solving agent supports multiple algorithms:
- **Wall-Following Algorithm** (right-hand rule)
- **Breadth-First Search (BFS)** for optimal pathfinding (not recommended due to its instability)

These algorithms ensure reliable and efficient navigation from entry to exit.

### Resource Management
Once the current maze is deleted, the terrain is restored to its original state, as it was before the maze was generated. All memory allocations, including dynamic arrays and linked lists, are efficiently managed and properly deallocated upon program termination. This ensures that the application remains lightweight, with no risk of memory leaks or unnecessary system resource consumption.

<p align="right">(<a href="#table-of-contents">back to top</a>)</p>

## 🔮 Future Extensions
- Improved maze solving feature
- Improved maze validation feature
- More customization

<p align="right">(<a href="#table-of-contents">back to top</a>)</p>

## 🦫 Built With

- C++17
- Spigot API
- g++
- Make
- Terminal 
- lmcpp

<p align="right">(<a href="#table-of-contents">back to top</a>)</p>

<!-- GETTING STARTED -->
## 🎬 Getting Started

Please follow the steps below to set up the project locally.

### Prerequisites

1. Make sure you have C++17 installed.

📦 Install C++17 if not:

- macOS:
    ```sh
    xcode-select --install
    ```
- WSL/Linux:
    ```sh
    sudo apt-get install make g++
    ```

2. Install CMake:

- macOS:
    1. Install Brew if you do not have it yet:
        ```sh
        /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
        ```
    2. Install CMake:
        ```sh
        brew install cmake
        ```
- WSL/Linux:
    ```sh
    sudo apt install cmake
    ```

3. Install mcpp:

- macOS/Linux/WSL:
    ```sh
    cd ~ && mkdir MyWorld
    cd MyWorld
    git clone https://github.com/rozukke/mcpp.git && cd mcpp
    cmake -B build && cd build
    ```
    Then run the commands below (it's okay if they throw errors):
    ```sh
    sudo mkdir /usr/local/lib
    sudo make install
    ```

4. Install Spigot Server:

- macOS/Linux/WSL:
    ```sh
    cd MyWorld
    git clone https://github.com/rozukke/minecraft_tools.git
    ```
    Tips: Run this to avoid any kinds of issues:
    ```sh
    sudo apt update
    sudo apt upgrade
    sudo apt install openjdk-17-jdk
    ```
You will end up having a file `minecraft_tools` somewhere in the MyWorld folder. There should be the file to run the server.  
For WSL/Linux and macOS, it will be called `./start_server.sh` and `./start.command` respectively.  
You have to run this every time you log in to Minecraft to use this application.

5. Join the Minecraft Server:
    ```
    1. Please install Minecraft Java Edition.

    2. Run the Minecraft launcher, then select the Installations tab up the top. Select New Installation, name it "1.19.4", then select "release 1.19.4" from the dropdown and click Create.

    3. Now go back to the Play tab and ensure that you have the 1.19.4 release selected down at the bottom-left.

    4. Click on the Play button. Once the game launches, click on Multiplayer, then Add Server. Enter the details below, with server address "::1", then click Done.

    5. You should now be able to join a game by clicking Join Server or double-clicking the Server that appears.
    ```

---

### Installation

Follow the instructions below to clone and run the project:

1. Clone the repo:
    ```sh
    git clone https://github.com/mov360/Maze-Runner.git
    ```

2. Navigate to the project directory:
    ```sh
    cd Maze-Runner
    ```

3. Build:
    ```sh
    make
    ```

4. Run the server:

- macOS:
    ```sh
    ./start.command
    # or just click on the file
    ```
- WSL/Linux:
    ```sh
    sudo chmod a+x start_server.sh
    ./start_server.sh
    # or just click on the file
    ```

5. Run the application:
    ```sh
    ./mazeRunner
    ```

<p align="right">(<a href="#table-of-contents">back to top</a>)</p>

<!-- HOW TO USE -->
## 📑 How To Use

Please spawn into the server world in Minecraft. Then run the application from your terminal.  
You can use the terminal as a UI to send commands to Minecraft.  
You will be prompted with options in the terminal — you can generate or solve the maze by choosing options.  
The UI is user-friendly and intuitive, but you can also read the use cases below for more detailed guidance.

Once you run the application, you should see the menu.

---

### Step 1: Design a Maze

- Choose **"1) Generate Maze"** by entering `1`.

You now have two options:

#### 1. Generate a Random Maze
- Select **"2) Generate Random Maze"**.
- Move to your desired location in Minecraft.
- Enter the **length** and **width** of the maze when prompted.
- A random maze will be generated and printed in the terminal.

#### 2. Upload Your Own Maze
- Select **"1) Read Maze From Terminal"**.
- Follow the same initial steps.
- **Design your maze manually** using:
  - `x` for walls
  - `.` for paths
- Paste your maze design into the terminal prompt.

---

### Step 2: Validate the Maze

After entering your maze:

- You will be asked to validate it.
- Choose **Yes** or **No** by entering the option number.

If the maze is **not valid**, you can re-validate by selecting **Yes** or **No** again.

---

### Step 3: Build the Maze in Minecraft

- Return to the **Main Menu**.
- Choose **option 2** ("Build Maze").
- The maze will be constructed automatically in your Minecraft world.

---

### Step 4: Solve the Maze

You have two options to solve the maze:

#### 1. Solve Manually
- Choose the **manual solve** option.
- You will be teleported to a random spot inside the maze.

#### 2. Solve Automatically
- Choose **"Show Escape Route"**.
- The application will find and display the escape route.

> ⚡ **Note:** Finding the escape route may take time depending on the maze size and server performance, but it will eventually complete!

---

### Important Reminders

⚠️ **Please do not exit Minecraft before quitting the application properly!**  
Otherwise, it may cause an error.

💡 **Note:**  
The extended solving algorithm is still under development and may behave unexpectedly in certain cases.

<p align="right">(<a href="#table-of-contents">back to top</a>)</p>

---

## 🪪 License

Distributed under the MIT License. See `LICENSE.txt` for more information.

<p align="right">(<a href="#table-of-contents">back to top</a>)</p>

---

## 📬 Contact

**Mohammad Ullah** – [ullahm2004@gmail.com](mailto:ullahm2004@gmail.com)

Project Link: [Maze Runner](https://github.com/mov360/Maze-Runner.git)

<p align="right">(<a href="#table-of-contents">back to top</a>)</p>
