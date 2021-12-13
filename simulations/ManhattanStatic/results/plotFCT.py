#!/usr/bin/env python

import sys
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import random
   
def getResults(file):
    results = pd.read_csv(file, header=None,  names=["FCT"])
    results = results.reset_index(drop=True)
    results = results.dropna()
    print(results)
    return results;

if __name__ == "__main__":
    results = []
    for arg in sys.argv[1:]:
        results.append(getResults(arg))
    for index, result in enumerate(results):
        plt.figure(figsize=(10,7))
        count, bins_count = np.histogram(result["FCT"], bins = result["FCT"].idxmax())
        pdf = count / sum(count)
        cdf = np.cumsum(pdf)
        plt.plot(bins_count[1: ], cdf, label = "CDF", linewidth=3)
        axes = plt.gca()
        axes.set_xlim([result["FCT"].min(), result["FCT"].max()+result["FCT"].max()*0.005])
        axes.set_ylim([0,1])
        plt.xlabel('FCT (sec)', fontsize=28)
        plt.ylabel('CDF', fontsize=28)
        plt.title("FCT", fontsize=35)
        plt.savefig('FCT.png')
    

