# TSP Functional
import math
import random

import matplotlib.pyplot as plt
import numpy as np
import xlrd
from pandas import DataFrame
import pandas as pd
from sklearn.utils import shuffle


# Print array function
def print_function(data):
    for i in range(len(data)):
        print(data[i])


# Check if exist in array with no duplicated
def exist_check(Array, item, byKey=0, itemArray=0, returnIndex=0):
    if itemArray == 1 and byKey == 0 and returnIndex == 0:
        Check = item in Array
        return Check
    if itemArray == 0 and byKey == 0 and returnIndex == 0:
        Check = item in Array
        return Check
    if itemArray == 0 and byKey == 0 and returnIndex == 1:
        for i in range(len(Array)):
            if Array[i] == item:
                return i
    return 0


# City Coordinates:
def getCoordinates():
    Coordinates = []
    with open('data_100.txt') as file:
        for line in file.readlines():
            city = line.split(' ')
            Coordinates.append((int(city[0]), int(city[1])))
    return Coordinates


# Create Shuffle Population:
def population(Value, Cities):
    Population = []
    while Value > 0:
        Data = [i for i in range(0, Cities)]
        Data = shuffle(Data)
        Population.append(Data)
        Value -= 1
    return Population


# # Evaluation : Calculate distance of two cities : Sqrt((X1 - X2)^2 + (Y1 - Y2)^2)
def dist(City_one, City_two):
    one = City_one
    two = City_two
    Temp1 = one[0] - two[0]
    Temp2 = one[1] - two[1]
    Temp3 = pow(Temp1, 2) + pow(Temp2, 2)
    Distance = round(math.sqrt(Temp3), 4)
    return Distance


# Calculate "total cost" of each path
def totalCost_Fitness_Calculator(Path, Coordinates, NumberOfCities):
    AllDistance = []
    # from each one to next city
    for i in range(NumberOfCities - 1):
        City1_name = Path[i]
        City2_name = Path[i + 1]
        City_one = Coordinates[City1_name]
        City_two = Coordinates[City2_name]
        Distance = dist(City_one, City_two)
        AllDistance.append(Distance)

    # from last city to first
    City1_name = Path[NumberOfCities - 1]
    City2_name = Path[0]
    City_one = Coordinates[City1_name]
    City_two = Coordinates[City2_name]
    Distance = dist(City_one, City_two)
    AllDistance.append(Distance)

    # calculate sum of all distance
    TotalCost = round(np.sum(AllDistance, axis=0), 4)
    Fitness = round(1 / TotalCost, 8)
    Evaluation = [TotalCost, Fitness]

    return Evaluation


# Calculate "TotalCost", and "Fitness" for all path
def evaluation(Population, Coordinates, NumberOfCities):
    AllEvaluation = []  # just Fitness
    AllFullEvaluation = []  # Total Cost (Distance) and Fitness
    for i in range(len(Population)):
        Evaluation = totalCost_Fitness_Calculator(Population[i], Coordinates, NumberOfCities)
        appendention1 = [i, Evaluation[1]]  # just Fitness
        appendention2 = [i, Evaluation]  # Total Cost and Fitness
        AllEvaluation.append(appendention1)  # just Fitness
        AllFullEvaluation.append(appendention2)  # Total Cost and Fitness

    return AllEvaluation, AllFullEvaluation


# Selection By Abundance and Cumulative Abundance and Random :
def selection(Evaluation, Value):
    Abundance = []  # Abundance or "Faraveni"
    Cumulative_Abundance = []  # The Cumulative Abundance or "Faraveni Tajamoie"
    Cumulative_Abundance_Selection = []  # Select by random from Cumulative Abundance
    # ----------------------------------------------------------- #
    Fitnesses = [Evaluation[i][1][1] for i in range(len(Evaluation))]
    Sort_Fitnesses = sorted(Evaluation, key=lambda x: x[1][1], reverse=True)
    Total_Fitnesses = round(sum(Fitnesses), 8)
    # ----------------------------------------------------------- #
    # Abundance or "Faraveni"
    for i in range(len(Fitnesses)):
        append = [i, round(Fitnesses[i] / Total_Fitnesses, 8)]
        Abundance.append(append)
    Sort_Abundance = sorted(Abundance, key=lambda x: x[1], reverse=True)
    # ----------------------------------------------------------- #
    # The Cumulative Abundance or "Faraveni Tajamoie"
    Total_Abundance = 0
    for i in range(len(Fitnesses)):
        Total_Abundance = Total_Abundance + Abundance[i][1]
        append = [i, round(Total_Abundance, 8)]
        Cumulative_Abundance.append(append)
    # ----------------------------------------------------------- #
    # Select by random from Cumulative Abundance
    while len(Cumulative_Abundance_Selection) < Value:
        randoms = random.uniform(0, 1)
        for j in range(len(Fitnesses)):
            if Cumulative_Abundance[j][1] >= randoms:
                Check = exist_check(Cumulative_Abundance_Selection, Cumulative_Abundance[j], 0, 1)
                if not Check:
                    Cumulative_Abundance_Selection.append(Cumulative_Abundance[j])
                    break
    Sort_Cumulative_Abundance_Selection = sorted(Cumulative_Abundance_Selection, key=lambda x: x[1], reverse=True)
    # ----------------------------------------------------------- #
    # FullAbundance for return
    FullAbundance = []
    FullAbundance.append(Abundance)
    FullAbundance.append(Cumulative_Abundance)
    FullAbundance.append(Cumulative_Abundance_Selection)
    # ----------------------------------------------------------- #

    # ----------------------------------------------------------- #
    return FullAbundance


# Cross Over :
def cross_over(FullAbundance, Population, Value):
    Cumulative_Abundance_Selection = FullAbundance[2]
    Counter = 0
    Child = []
    while Counter < Value:
        First_Item = Cumulative_Abundance_Selection[Counter][0]
        Second_Item = Cumulative_Abundance_Selection[Counter + 1][0]

        Parent1 = Population[First_Item]
        Parent2 = Population[Second_Item]
        Children1, Children2 = make_children(Parent1, Parent2)
        Child.append(Children1)
        Child.append(Children2)
        Counter += 2
    return Child


def make_children(Perent_one, Perent_two):
    randoms = random.randrange(2, len(Perent_one) - 2)
    end = len(Perent_one)
    # Children one with two part
    Children_one1 = Perent_one[0:randoms]
    Children_one2 = Perent_two[randoms:end]
    # Children two with two part
    Children_two1 = Perent_two[0:randoms]
    Children_two2 = Perent_one[randoms:end]
    # Remove duplication
    Remove_one = []
    Remove_two = []
    for i in reversed(range(len(Children_one2))):
        Check1 = exist_check(Children_one1, Children_one2[i])
        Check2 = exist_check(Children_two1, Children_two2[i])
        if Check1:
            append = Children_one2.pop(i)
            Remove_one.append(append)
        if Check2:
            append = Children_two2.pop(i)
            Remove_two.append(append)

    # Make children Complate
    Children_one2 = Children_one2 + list(reversed(Remove_two))
    Children_two2 = Children_two2 + list(reversed(Remove_one))
    # Make child
    Children_one = Children_one1 + Children_one2
    Children_two = Children_two1 + Children_two2
    child = [Children_one, Children_two]

    return Children_one, Children_two


# Mutation :
def mutation(Child, NumberOfCities, Value):
    for i in range(Value):
        randoms = random.randrange(0, NumberOfCities)
        Temp = Child[i][randoms]
        Index = exist_check(Child[i], randoms, 0, 0, 1)
        Child[i][randoms] = randoms
        Child[i][Index] = Temp
    return Child


# Replace The Generation :
def replacement(Population, Parents_Evaluation, Child, Child_Evaluation, Persent, Value):
    # ----------------------------------------------------------- #
    # Child :
    # Child Selection for new generation :
    Child_FullAbundance = selection(Child_Evaluation, Value)
    # CAS = Cumulative_Abundance_Selection :
    Child_CAS = Child_FullAbundance[2]
    # Sort Child Fitness :
    Sort_Child_Fitnesses = sorted(Child_Evaluation, key=lambda x: x[1][1], reverse=True)
    # ----------------------------------------------------------- #
    # Parents or Population :
    # Sort Parents Fitness :
    Sort_Parents_Fitnesses = sorted(Parents_Evaluation, key=lambda x: x[1][1], reverse=True)
    # ----------------------------------------------------------- #
    # Calculate Number of Choosen :
    Choosen = round(Value * (Persent / 100))
    # ----------------------------------------------------------- #
    # Create New Population
    NewPopulation = []
    # ----------------------------------------------------------- #
    # Choose (Value - Choosen) item from parents : by Fitness
    for i in range(Value - Choosen):
        Index = Sort_Parents_Fitnesses[i][0]
        append = Population[Index]
        NewPopulation.append(append)
    # ----------------------------------------------------------- #
    # Choose (Choosen) item from child : by Fitness
    for i in range(Choosen):
        Index = Sort_Child_Fitnesses[i][0]
        append = Child[Index]
        NewPopulation.append(append)

    # Choose (Choosen) item from child : by CAS
    # for i in range(Choosen):
    #     Index = Child_CAS[i][0]
    #     append = Child[Index]
    #     NewPopulation.append(append)
    # ----------------------------------------------------------- #

    return NewPopulation


# Stop Condition Check Type One: if all Chld are same
def stopCondition1(Population, CitiesCoordinates, NumberOfCities, Value):
    # CalCulate Evaluation of Population
    AllEvaluation, FullEvaluation = evaluation(Population, CitiesCoordinates, NumberOfCities)
    # Get first Evaluation find of Population, the best of evaluation
    FirstFindDistance = FullEvaluation[0][1][0]
    FirstFindFitness = FullEvaluation[0][1][1]
    # Check all item of population are the best or not
    Counter = 0
    for i in range(Value):
        if FullEvaluation[i][1][1] == FirstFindFitness:
            Counter += 1

    if Counter == Value:
        return 1
    else:
        return 0


# Stop Condition Check Type Two: if good is stable after some round
def stopCondition2(Population, CitiesCoordinates, NumberOfCities, Value, MinDist):
    # CalCulate Evaluation of Population
    AllEvaluation, FullEvaluation = evaluation(Population, CitiesCoordinates, NumberOfCities)
    Sort_Fitnesses = sorted(FullEvaluation, key=lambda x: x[1][1], reverse=True)
    if MinDist == FullEvaluation[0][1][0]:
        return 1, FullEvaluation[0][1][0], FullEvaluation[0][1][1]
    else:
        return 0, FullEvaluation[0][1][0], FullEvaluation[0][1][1]


# Plot :
def plotData(BestWay, Coordinates, NumberOfCities):
    Way = []
    Label = ['City ' + str(i) for i in range(NumberOfCities)]
    NewLabel = []

    for i in range(NumberOfCities):
        Index = BestWay[i]
        append = Coordinates[Index]
        Way.append(append)
        append = Label[Index]
        NewLabel.append(append)
    # ----------------------------------------------------------- #
    xCoordinates = [Coordinates[i][0] for i in range(len(Coordinates))]
    yCoordinates = [Coordinates[i][1] for i in range(len(Coordinates))]
    xWay = [Way[i][0] for i in range(len(Way))]
    yWay = [Way[i][1] for i in range(len(Way))]
    xWay.append(Way[0][0])
    yWay.append(Way[0][1])
    # ----------------------------------------------------------- #
    # Plot The Location of Cities
    # plt.subplot(1, 2, 1)
    plt.title("The Location of Cities")
    plt.scatter(xCoordinates, yCoordinates)
    Counter = 0
    for x, y in zip(xCoordinates, yCoordinates):
        label = Label[Counter]
        plt.annotate(label,  # this is the text
                     (x, y),  # this is the point to label
                     textcoords="offset points",  # how to position the text
                     xytext=(5, 5),  # distance from text to points (x,y)
                     ha='center')  # horizontal alignment can be left, right or center
        Counter += 1
    plt.show()
    # ----------------------------------------------------------- #
    # Plot The Path We Found
    # plt.subplot(1, 2, 2)
    plt.title("The Path We Found")
    plt.plot(xWay, yWay, 'bo-')
    Counter = 0
    for x, y in zip(xWay, yWay):
        if Counter < NumberOfCities:
            label = NewLabel[Counter]
        if Counter == NumberOfCities:
            label = NewLabel[0]
        plt.annotate(label,  # this is the text
                     (x, y),  # this is the point to label
                     textcoords="offset points",  # how to position the text
                     xytext=(25, 5),  # distance from text to points (x,y)
                     ha='center')  # horizontal alignment can be left, right or center
        Counter += 1
    plt.show()
    # ----------------------------------------------------------- #


# ----------------------------------------------------------- #
# Show Outpot :
def output(FirstPopulation, NewPopulation, New_FullEvaluation, Epok):
    print("\n---------1-----------\n")
    print("First Population:")
    print_function(FirstPopulation)
    print("\n---------2-----------\n")
    print("Last Population:")
    print_function(NewPopulation)
    print("\n---------3-----------\n")
    print("Last Evaluation [Index, [Dist, Fitness]]:")
    print_function(New_FullEvaluation)
    print("\n---------4-----------\n")
    print("Solution:")
    print("\nPath:")
    print(NewPopulation[0])
    print("\nPath Evaluation [Dist, Fitness]:")
    print(New_FullEvaluation[0][1])
    print("\n---------5-----------\n")
    print("Epok:")
    print(Epok)
    print("\n")


# Main Function
def TSP(Value, Persent):
    # Check Run Program :
    if Value % 2 == 1 or Value == 0:
        print("\nWrong inputs!!!\n")
        return

    # 1 Cities Coordinates:
    CitiesCoordinates = getCoordinates()
    NumberOfCities = len(CitiesCoordinates)

    # 2 Create Shuffle Population:
    Population = population(Value, NumberOfCities)
    FirstPopulation = Population

    # **** Start While Loop
    Counter = 50  # Maximume Loop and generation
    Epok = 0  # Epok counter
    MinDist = 300  # minimum distance by chance
    while Counter > 0:
        Epok += 1
        # 3 # Evaluation :
        # Calculate distance of two cities
        # Calculate "total cost" of each path
        # Calculate "TotalCost", and "Fitness" for all path
        AllEvaluation, FullEvaluation = evaluation(Population, CitiesCoordinates, NumberOfCities)
        # 3.1 Selection By Abundance and Cumulative Abundance and Random :
        FullAbundance = selection(FullEvaluation, Value)

        # 4 Cross Over :
        Child = cross_over(FullAbundance, Population, Value)

        # 5 Mutation :
        Child = mutation(Child, NumberOfCities, Value)
        # 5.1 Child Evaluation :
        Child_AllEvaluation, Child_FullEvaluation = evaluation(Child, CitiesCoordinates, NumberOfCities)

        # 6 Replace The Generation :
        NewPopulation = replacement(Population, FullEvaluation, Child, Child_FullEvaluation, Persent, Value)
        New_AllEvaluation, New_FullEvaluation = evaluation(NewPopulation, CitiesCoordinates, NumberOfCities)
        Population = NewPopulation

        # 7 Stop Condition :
        ConditionFlag1 = stopCondition1(Population, CitiesCoordinates, NumberOfCities, Value)
        ConditionFlag2, New_MinDist, New_MinFitness = stopCondition2(Population, CitiesCoordinates, NumberOfCities,
                                                                     Value, MinDist)

        # 7.1 Check Condition :
        if ConditionFlag2 and Epok > 200:
            break
        else:
            MinDist = New_MinDist

        Counter -= 1
    # **** End of While
    # ----------------------------------------------------------- #
    # Output
    output(FirstPopulation, NewPopulation, New_FullEvaluation, Epok)
    # ----------------------------------------------------------- #
    # Plot :
    # plotData(Population[0], CitiesCoordinates, NumberOfCities)
    # ----------------------------------------------------------- #


# ----------------------------------------------------------- #

# Run TSP : (Number Of Population, Present of marge)
TSP(80, 60)
