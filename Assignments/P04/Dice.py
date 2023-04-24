#############################################################################################
#
#  Author:           Sum'r Rocka
#  Title:            Roll them Bones!
#  Course:           2143
#  Semester:         Spring 2023
#
#  Description:
#        While using the starter code written by Dr. Griffin in class, this program
#        implements dice that can be rolled and manipulated
#        in various ways to be used in a dnd-like fighting game. 
#
#
#  Usage:  d1 = Die()
#
#          dieTester(d1, 10)
#
#  Files: main.py    :  Contains dieTester, a function that tests the die class.
#         Dice.py    :  Cotntains Die and Dice, which represent a single die and plural dice
#                       respectively.
#############################################################################################

import random
import sys

class Die(object):

  def __init__(self, sides=None):
    if not sides:
      self.sides = 6
    else:
      if not isinstance(sides, int):
        print("error: sides is not an integer!")
        sys.exit()
      self.sides = sides

  def roll(self):
    values = [x for x in range(self.sides)]

    random.shuffle(values)

    return values[0] + 1

  def __str__(self):
    return f"[sides: {self.sides}]"


class Dice:

  def __init__(self, sides=None, num_dice=1):
    if not sides:
      print("Need to pass in sides!!!")
      sys.exit()
    

    self.sides = sides

    # create a container
    self.dice = []

    for die in range(num_dice):
      self.dice.append(Die(sides))

  
  def sum(self):
    total = 0
    for d in self.dice:
      total += d.roll()

    return total



  # Description:
  #      Returns the largest roll of a set of dice.
  #
  # Params:
  #      self        : The instance of the class that is being called
  # Returns:
  #      max         : the roll that was the largest in a set
  def max(self):
    max = 0
    for d in self.dice:
      roll = d.roll()
      if roll > max:
        max = roll
    return max

  # Description:
  #      Returns the smallest roll of a set of dice.
  #
  # Params:
  #      self        : The instance of the class that is being called
  # Returns:
  #      max         : the roll that was the smallest in a set
  def min(self):
    min = 1000 #hopefully no 1001 sided die show up...
    for d in self.dice:
      roll = d.roll()
      if roll < min:
        min = roll
    return min
    
  # Description:
  #      Returns the average roll of a set of dice.
  #
  # Params:
  #      self                 : The instance of the class that is being called
  # Returns:
  #      total / numOfRolls   : The average of all the dice rolls
  def avg(self):
    total = 0
    numOfRolls = 0
    for d in self.dice:
      total += d.roll()
      numOfRolls += 1
    return total / numOfRolls


  def roll(self, rollType=None):

    if rollType == 'max':
      return self.max()
    elif rollType == 'min':
      return self.min()
    elif rollType == 'avg':
      return self.avg()
    else:
      return self.sum()

  def __str__(self):
    s = "Dice:[\n    "
    for d in self.dice:
      s = s + str(d)
    s = s + "\n]\n"
    return s
