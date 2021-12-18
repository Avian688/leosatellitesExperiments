#!/usr/bin/env python

import sys
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import random
   
def getResults(file):
    results = pd.read_csv(file, header=None,  names=["goodput"])
    results = results.sort_values("goodput")
    results = results.reset_index(drop=True)
    print(results)
    return results;

if __name__ == "__main__":
    results = []
    plt.rcParams['font.family'] = 'serif'
    plt.rcParams["font.serif"] = "Times New Roman"
    for arg in sys.argv[1:]:
        results.append(getResults(arg))
    plt.figure(figsize=(6,3.7))
    plt.xticks(fontsize=21)
    plt.yticks(fontsize=21)
    for index, result in enumerate(results):
        result.index = np.arange(1, len(result) + 1)
        rgb = (random.random(), random.random(), random.random())
        result["goodput"] = result["goodput"].apply(lambda x: x/1000000000)
        plt.plot(list(result.index.values),result["goodput"], c=rgb, drawstyle='steps-post', linewidth=1, label="")
    axes = plt.gca()

    axes.set_xlim([1, 50])
    axes.set_ylim([0,1])
    plt.legend(['IW = 200', 'IW = 600','IW = 1000','IW = 1400','IW = 1800'],loc="lower center", ncol=2,prop={'size': 10}, labelspacing=0.1, fontsize='xx-large')
    plt.xlabel('Rank of Transport Session', fontsize=21)
    plt.ylabel('Goodput (Gbps)', fontsize=21)
    plt.title("Ten Hop Flows Goodput", fontsize=23)
    #plt.xticks((np.arange(0, result["Goodput"].idxmax(), step=250)))
    #plt.legend(loc="lower right")
    x_ticks = [1,10,20,30,40,50]
    plt.xticks(x_ticks)
    plt.subplots_adjust(bottom=0.2, left=0.14)
    plt.savefig('10HopsIWGoodput.png')
    plt.savefig('../../../../../../ResearchWork/GIPReport/ProjectImages/10HopsIWGoodput' +str(index)+ '.pgf', format='pgf')
    

