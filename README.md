# 🏃 Endless Runner – Unreal Engine (C++)

A fast-paced endless runner game developed in Unreal Engine using C++. The player must dodge obstacles and collect power-ups while being chased by a deadly spiked wall that accelerates over time.

## 🎮 Gameplay Overview

- **Object Pooling for Obstacles & Power-Ups**  
  Obstacles and speed-boosting power-ups are managed through object pooling to optimize performance and avoid runtime instantiation.

- **Dynamic Difficulty Scaling**  
  A spiked wall relentlessly pursues the player, increasing its speed over time to raise the challenge.

- **Record Saving System**  
  The game tracks and saves the best survival time locally, displaying it via a UI element in the top-left corner of the screen.

## 🕹️ Controls

- **A** → Move Left  
- **D** → Move Right  
- **Spacebar** → Jump

## 🛠️ Technologies Used

- **Unreal Engine**
- **C++**
- **Object Pooling**
- **SaveGame System**
- **Custom UI Widgets**

## 🎯 Development Focus

- Efficient memory and object management using pooling  
- Real-time difficulty progression  
- Persistent data handling with Unreal’s SaveGame system  
- Responsive input and UI integration

## 🎞️ Gameplay Preview

![Gameplay Preview](Gifs/Gameplay.gif)
