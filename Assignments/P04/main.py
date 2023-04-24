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

from Dice import Die
from Dice import Dice
from rich import print

def dieTester(die, runs=10, testType="sum"):
  if isinstance(die, Die):
    print(f"Testing {die.sides} sided die for {runs} rolls:")
    print("    [ ", end="")
    for i in range(runs):
      print(die.roll(), end=" ")
    print("]")
  else:
    print(
      f"Rolling {len(die.dice)} {die.sides} sided die {runs} times to get the {testType} value:"
    )
    print("    [ ", end="")
    for i in range(runs):
      if testType == "avg":
        print(die.avg(), end=" ")
      elif testType == "min":
        print(die.min(), end=" ")
      elif testType == "max":
        print(die.max(), end=" ")
      else:
        print(die.sum(), end=" ")
    print("]")


if __name__ == '__main__':
  d1 = Die()
  d2 = Die(20)
  d3 = Dice(10, 5)

  dieTester(d1, 10)
  dieTester(d2, 20)
  dieTester(d3, 10, "max")
  dieTester(d3, 10, "min")
  dieTester(d3, 10, "avg")
