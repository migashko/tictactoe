#!/usr/bin/env python

import subprocess
import sys
import math
import os;

level = -1
player = -1
board = [
  -1, -1, -1,
  -1, -1, -1,
  -1, -1, -1
]

DEVNULL = open(os.devnull, 'wb')

def init():
  
  if not os.path.exists("./build"):
    print("mkdir build")
    os.makedirs("build")

  if not os.path.isfile("./faslib/CMakeLists.txt"):
    print("git update...")
    subprocess.call(["git", "submodule", "update", "--init"], stdin=None, stdout=DEVNULL, stderr=DEVNULL, shell=False)
    
  if not os.path.isfile("./build/CMakeCache.txt"):
    print("initialize...")
    os.chdir("./build")
    subprocess.call(["cmake", ".."], stdin=None, stdout=DEVNULL, stderr=DEVNULL, shell=False)
    os.chdir("..")

def write_level():
  f = open('level.inl', 'w')
  f.write(str(level))
  f.write("\n")
  f.close()

def write_board():
  f = open('board.inl', 'w')
  for i, b in enumerate(board) :
    if b==-1:
      f.write("e")
    elif b==0:
      f.write("o")
    elif b==1:
      f.write("x")
    if i < len(board)-1:
      f.write(",")
  f.write("\n")
  f.close()
      
def comp_move():
  print ("compiling...")
  
  subprocess.call(["rm", "./build/tictactoe"], stdin=None, stdout=DEVNULL, stderr=DEVNULL, shell=False)
  subprocess.call(["make", "--directory=./build", "tictactoe"], stdin=None, stdout=DEVNULL, stderr=DEVNULL, shell=False)
  
  p = subprocess.Popen("./build/tictactoe", stdout=subprocess.PIPE)
  
  out, err = p.communicate()
  print out
  items = out.split()
  
  if len(items) > 8:
    for i, b in enumerate(board):
      if items[i]=='-':
        board[i]=-1
      elif items[i]=='X':
        board[i]=1
      elif items[i]=='O':
        board[i]=0
      
  return len(items)==9

def a1c3(str1):
  if len(str1)!=2:
    return -1
  f = str1[0].lower();
  s = str1[1];
  if f in ['a','b','c'] and s in ['1','2','3']:
    return (ord(f) - ord('a'))*3 + int(s) - 1
  return -1
  
def user_move():
  pos = -1
  while pos==-1:
    str1 = raw_input("Move [0..8, a1..c3]: ")
    if str1.isdigit():
      pos = int(str1)
      if not pos in range(0,9):
        pos=-1
    else:
      pos = a1c3(str1)
    if pos == -1:
      print("ERROR")
      continue
    if board[ pos ] != -1:
      pos = -1  
      print("BUSSY")
  board[ pos ]=player
  
def game():
  write_board()
  if not comp_move():
    return 0
  user_move()
  return 1

if __name__ == '__main__':
  init()
  level = input("Level [0,1,2]: ")
  write_level()
  O, o = 0, 0
  X, x= 1, 1
  fig = input("Figure [X,x,1,O,o,0]: ")
  player=fig
  
  if player==1:
    user_move()
    
  while game():
    pass
