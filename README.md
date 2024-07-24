# Heroes Rising

Heroes Rising is a turn-based RPG game developed in C++ using Qt Creator. This project was created for educational purposes and is non-profit. In Heroes Rising, players can build and customize their characters, enhancing their stats and leveling up.

## Features

### Leveling System
- **Starting Level**: Players start at level 1 with 5 points to distribute among the character's stats (Attack, Dexterity, Vitality, Defense, Luck), all of which start at 1.
- **Leveling Up**: With each level gained, players receive an additional 5 points to distribute. The experience required to level up increases progressively.

### Tavern
A place to rest and recover health. The tavern offers different room options:
- **Basic Room**: Restores 25% health, costs 5 coins.
- **Comfy Room**: Restores 50% health, costs 9 coins.
- **Deluxe Room**: Restores 100% health, costs 17 coins.

### Inventory
Functions as a wardrobe where players can switch weapons and armor.

### Shop
Players can sell items found in battles and purchase better equipment such as weapons and armor.

### Profile
Allows players to view their character's build, reset attributes, and redistribute points if available.

### Battle
Players embark on adventures and encounter enemies along the way. Each time the character levels up, a new and stronger enemy is unlocked.

### Progression
The goal was to have the character reach level 10 before unlocking the final boss, but this stage has not yet been implemented.

## Installation
1. Clone the repository:
   ```bash
   git clone https://github.com/yourusername/HeroesRising.git
   ```
2. Open the project in Qt Creator.
3. Build and run the project.
