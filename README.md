# Maze Game

A simple maze game developed in C++ using the Simple and Fast Multimedia Library (SFML). Navigate through mazes, collect coins, find keys, and reach the exit. The game features manual and automatic pathfinding modes for enhanced gameplay.

## Features

- **Three Levels**: Each level features a unique maze layout and challenges.
- **Manual Controls**: Move the player manually using keyboard controls.
- **Auto-Search Mode**: Automatically calculates the shortest path to collect coins and reach the goal.
- **Simple 2D Graphics**: Visually appealing, minimalistic graphics for easy navigation.

## How to Play

1. **Download and Setup**:
   - Clone this repository: `git clone https://github.com/yourusername/maze-game.git`.
   - Open the solution file `MazeGame.sln` in Visual Studio.

2. **Build the Solution**:
   - Make sure you have the required dependencies installed (SFML).
   - Set the build configuration to `Debug` or `Release` and the platform to `x64` or `x86` as per your system.
   - Build the project (`Ctrl+Shift+B` in Visual Studio).

3. **Run the Game**:
   - Press `F5` or go to `Debug > Start Debugging` in Visual Studio.

4. **Controls**:
   - Use the **Arrow Keys** or **WASD** to move the character.
   - Click the "Play" button to start the game.
   - Click the "Auto" button to enable automatic pathfinding.
   - Click "Back" to return to the main menu.

## Project Structure

- `MazeGame.sln`: The Visual Studio solution file for the project.
- `main.cpp`: Contains the game logic, rendering, and event handling.
- `GameData/`: Stores graphical assets like textures and icons.
- `README.md`: Documentation for the project.

## Future Improvements

- **Scoring System**: Add a scoring mechanism based on time and collected coins.
- **Sound Effects**: Enhance gameplay with background music and sound effects.
- **New Levels**: Introduce additional levels with increased difficulty.
- **Improved AI**: Optimize automatic pathfinding for better performance.

## Dependencies

- [SFML](https://www.sfml-dev.org/): A multimedia library for C++.

## License

This project is licensed under the MIT License. See the `LICENSE` file for more details.

## Screenshots & Videos

### Sample Gameplay Video

<video src="./sample.mp4" controls width="600">
  Your browser does not support the video tag.
</video>

## Contributing

Contributions are welcome! Feel free to fork the repository and submit pull requests for improvements or bug fixes.
