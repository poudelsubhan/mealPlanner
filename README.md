# mealPlanner

mealPlanner uses dynamic programming to solve the subset sum problem to determine which meals add up to a given caloric value. The caloric value is set in main.

The subset sum problem asks: given a non-empty set of integers, is there a non-empty subset whose sum is zero? Or, given a set, does any subset sum to a given number n? The problem is a special case of the knapsack problem which means subset sum is NP-complete.

Given a txt file of foods, their caloric values, other nutritional values, and a given caloric amount C, mealPlanner finds all subsets of foods that add up to C. Thus, mealPlanner applies the subset sum problem to counting calories in determining what to eat daily. The dynammic programming solution runs in O(CF) where C is the given caloric amount and F is the number of foods.

food.txt is the "dictionary" file that the program reads. All of the items are from Micheal Matthews "The Shredded Chef." The format for the file is: 
  food name, food type, page in book, calories, protein, carbs, fat, time to prepare

output.txt is an example of what the program outputs. The program, however, displays the items on the terminal instead of writing them to a file. You will have to direct the output to a file yourself. 1000 was the caloric value used for this example instead of a realistic daily value such as 2000 because the resulting file would have been 90.1 MB. Each subset ends in the given caloric sum as a check.
