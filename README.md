[toc]

## XJCO1921-Programming Project – Coursework2 -  conway's game of life with interactive GUI  

Zihan Zhou 2020110026 201487560

### Brief Introduction

This project is a retro game project written in the pure c programming language. The game is known as **Conway's Game of Life,** a 'zero player game' proposed by the famous mathematician, Conway in the 1970s. This project implements an automaton game with a **graphical user interface**(powered by the SDL graphical library), while the player can Observethe progression of evolution at **each step**, **manipulate the game process**(direct prompt or read from a verificated), **change** the game state(**START,PAUSE,SINGLE STEP CLICK,CLICK THE GRID TO TOGGLE THE STATE OF A GRID**), and **save** the game state. 

### How to run the progrmme

#### Game compliation

``` bash
## simply go to the root dir of this project hit
$ make 
## or
$ make all
## if you want to clean the space, use
$ make clean
```

![game](/Users/mac/programming_project2/gol/game.png)

#### Run the programme in different mode

```bash
## After complation, you can run the game in mutiple ways
## 1. direct run, use 
./gol
## 2. use the game.config file, which will be verified
./gol io_files/game.config
## 3. wrong cla, which will prompted as direct run
./gol wrong_url wrong_argc

```

#### Run the automatic test-suite

```bash
## go to the root dir of this project,run
sh auto_test_runner.sh
```

And you will see the test output:

![auto_test](/Users/mac/programming_project2/gol/auto_test.png)

### git URL and Screen Shot of it



URL:https://github.com/zzh8241102/gol

Screen_shot:

![github.com_zzh8241102_gol_commits_main](/Users/mac/programming_project2/gol/github.com_zzh8241102_gol_commits_main.png)
