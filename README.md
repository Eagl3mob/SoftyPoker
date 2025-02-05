
### SoftyPoker Sub-Project Objectives

Softy Projects © 2025 by T.E. & E.M. is licensed under a Creative Commons Attribution 4.0 International License (CC BY 4.0). This includes all sub-projects such as SoftyPoker.

---

### Application Start

**Part 1**: On application run, an intro starts which displays 1 of the 5 random images, plays 1 of the 5 random music tracks, and also displays 2 text scrolls using 2 different speeds.

It also displays a logo image effect using fade-in and fade-out effects. The first line of text scrolls under the logo image, while the second line of text scrolls above the logo image.

---

### To-Do and Implementations

- On pressing the "S" button, SoftyPoker enters the main game phase.
- Upon entering the main game phase, the music, text scrolls, and logo stop playing or displaying. The current background stays displayed.

---

### Main Game

- Instructions text will display at the top of the screen.
- Bet text and bet value will display on the left side of the screen.
- Credit text and credit value will display on the left side of the screen.
- A prize table and prize value will display on the right side of the screen.
- Win prize text and win prize value will display on the left side of the prize table.

Credit value starts at 20, Bet value starts at 0.

By pressing the "B" button, 1 value is decreased from the credits value and 1 value is added to the bet value. The maximum bet value is 5. The "B" button cycles between 1 and 5 bet values if the credit is 5 or higher. If the credit value is lower than 5, the "B" button cycles according to the current credit value.

---

### Creating Deck of 52 Cards Randomly

When the bet value is higher than 0, the "D" button can be pressed. By pressing the "D" button, 5 random cards will be drawn and displayed one by one in a smooth transition, but not as an animation.

Each card transition/draw/redraw has a "deal" sound. After the 5 cards are drawn, the user can press the buttons "1, 2, 3, 4, or 5" to toggle "held/unheld" the cards. If a card is toggled as held, it highlights that card. Pressing the same toggle button again will switch the card between held and unheld, playing a sound for "held" and a sound for "unheld". The highlight will toggle on or off accordingly.

---

More game logic will be implemented as development progresses.

---
