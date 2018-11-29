import pandas as pd
import numpy as np
from scipy.special import comb

def backward(N, theta, u, d, p, default_x):

    pi = ((((p*(u-1))/((1-p)*(1-d)))**theta)-1)/((u - 1)+(((p*(u-1))/((1-p)*(1-d)))**theta)*(1 - d))

    stock = []
    tmp = []
    for i in range(N+1):
        stock.append([])
        tmp.append(i)
        for j in range(0,N+1):
            stock[i].append([])
    for i in range(N+1):
        for j in range(N+1):
            stock[i][0] = i
            stock[i][1] = tmp[0:i+1]
            stock[i][2] = tmp[i::-1]
            stock[i][3] = tmp[0:i+1]
            stock[i][4] = theta
            stock[i][5] = p
            stock[i][6] = list(map(lambda x: 0 if x==0 else u**x, tmp[0:i+1]))
            stock[i][7] = list(map(lambda x: 0 if x==0 else d**x, tmp[i::-1]))
            #price
            stock[i][8] = list(map(lambda x, y: default_x if x==0 and y==0 else (default_x*x)+(default_x*y) if x==0 or y==0 else (default_x*x)*(default_x*y), stock[i][6], stock[i][7]))
            #value
            if i==N:
                stock[i][9] = list(map(lambda x:((1-(1/theta))**(-1))*(x**(1-(1/theta))), stock[i][8]))
            else:
                stock[i][9] = list(map(lambda x: p*((1-(1/theta))**(-1))*((x*(1+pi*(u-1)))**(1-(1/theta)))+((1-p)*((1-(1/theta))**(-1)))*((x*(1+pi*(d-1)))**(1-(1/theta))) , stock[i][8]))
            #strategy
            if i==0:
                stock[i][10] = 0
            else:
                stock[i][10] = list(map(lambda x, y:(pi*y)/x, stock[i][8], stock[i][9]))
            #Exp_value
            stock[i][11] = list(map(lambda  l, m, n : comb(i, l, exact=True)*(p**l)*((1-p)**m)*n if (l!=0 and m!=0) \
                                else (p**l)*n if m==0 \
                                else ((1-p)**m)*n if l==0 \
                                else nan \
                                , stock[i][2], stock[i][3], stock[i][9]))
            
    df = pd.DataFrame(stock)
    df = df.set_index(0)
    df.columns = ["node_num", "up_times", "down_times", "theta", "prob", "up_r", "down_r", "price", "value", "alpha", "Exp_val"]
    
    last_value_mean = list(map(lambda x: np.mean(x), df["Exp_val"]))[10]
    
    return df["Exp_val"][10]
