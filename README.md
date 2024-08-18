# MaDiEn

> Maze Display Engine

Part of a [raycasting game](https://github.com/IOKG04/Maze) I'm working on, that I thought would make sense to split off so I can use it for other things too.

Just so no one is confused about the naming, `MaDiEn` is just the first two letters of each of the three words it stands for, and it is pronounced the same as said words (so `medɪɛn` in IPA if I'm not mistaken).

## Goals

The goal of this project is to have a graphics engine for the terminal.  
As of currently, that specifically means *my* terminal, though I intend on making it more accessible once I have finished everything.

The engine should incoorporate anything from sprites to post processing effects once it is done. More specifically, these are the goals:  
- [ ] Buffers
  - [x] Displaying a buffer in the terminal
    - [ ] Enabling (true) color
  - [ ] Combining buffers in different ways
  - [ ] Sprites (basically just buffers)
    - [ ] Loading sprite data from image files (.qoi probably)
- [ ] Post processing
