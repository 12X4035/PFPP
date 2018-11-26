import pandas as pd
import numpy as np
from scipy.special import comb
import random

def delta (theta, a, b, c):
    return ((1+b)/((c**(theta))*((a**(-theta))+b)))

def value(N, u, d, pi, default_x):
    val_arr = []
    recursive = []
    for l in range(2**(N+1)):
        for m in range(2):
            recursive.append(l)
    for l in range(N+1):
        val_arr.append([])
        val_arr[l] = [0 for m in range(2**l)]
        if l==0:
            val_arr[l][l]=default_x
        else:
            for n in range(len(val_arr[l])):
                if (n+1)%2!=0:
                    val_arr[l][n] = val_arr[l-1][recursive[n]]*(1+pi*(u-1))
                if (n+1)%2==0:
                    val_arr[l][n] = val_arr[l-1][recursive[n]]*(1+pi*(d-1))

    return val_arr

def forward(N, theta, u, d, p, default_x):

    random.seed(123)

    q = (1-d)/(u-d)
    a = ((1-p)/p)*(q/(1-q))
    b = (1-q)/q
    c = (1-p)/(1-q)

    stock = []
    tmp = []
    up = []
    down = []
    prob = []
    pi = (delta(theta, a, b, c)*((p/q)**(theta))-1)/(u-1)
    M = p*(1+pi*(u-1))**(1-(1/theta))+(p-1)*(1+pi*(d-1))**(1-(1/theta))
    val = value(N+1, u, d, pi, default_x)
    
    for i in range(N+1):
        stock.append([])
        tmp.append(i)
        for j in range(0,N+1):
            stock[i].append([])
    for i in range(N+1):
        for j in range(N+1):
            #index
            stock[i][0] = i
            #node_num
            stock[i][1] = tmp[0:i+1]
            #up_times
            stock[i][2] = tmp[i::-1]
            #down_times
            stock[i][3] = tmp[0:i+1]
            #theta
            stock[i][4] = theta
            #u
            stock[i][5] = u#[random.random()+1, random.random()]
            #d
            stock[i][6] = d#[random.random()+1, random.random()]
            #p
            stock[i][7] = p#random.random()
            
            stock[i][8] = list(map(lambda x: 0 if x==0 else x, tmp[0:i+1]))
            stock[i][9] = list(map(lambda x: 0 if x==0 else x, tmp[i::-1]))
            #pi(u,d固定では一定)
            #stock[i][10] = (delta(theta, a, b, c)*((p/q)**(theta))-1)/(u-1)
            #price
            #stock[i][10] = list(map(lambda x, y: default_x if x==0 and y==0 else (default_x*x)+(default_x*y) if x==0 or y==0 else (default_x*x)*(default_x*y), stock[i][8], stock[i][9]))
            #value
            stock[i][10] = val[i]
            #Wealth
            stock[i][11] = list(map(lambda x: (M**((N+1)-i))*((1/(1-theta))**(-1))*(x)**(1-(1/theta)), stock[i][10]))
            #U_0
            stock[i][12] = list(map(lambda x: ((1-(1/theta))**(-1))*(x**(1-(1/theta))), stock[i][10]))
            #I_0
            #stock[i][10] = list(map(lambda x: (x**(-1/theta))**(-1), stock[i][8]))
            #I_1
            #stock[i][11] = list(map(lambda x: (1+b)/((c**theta)*((a**(-theta))+b)*x, stock[i][10]))
            #U_1
            stock[i][13] = list(map(lambda x: (((1+b)/((c**(theta))*((a**(-theta))+b)))**(1/theta))*x, stock[i][12]))
            #pi
            stock[i][14] = list(map(lambda x: ((((1+b)/((c**theta)*((a**(-theta))+b)))*((p/q)**theta)-1)/(u-1))*x, stock[i][10]))
            #Exp[U_1]
            stock[i][15] = list(map(lambda  l, m, n : comb(i, l, exact=True)*(p**l)*((1-p)**m)*n if (l!=0 and m!=0) \
                                 else (p**l)*n if m==0 \
                                 else ((1-p)**m)*n if l==0 \
                                 else nan \
                                 , stock[i][2], stock[i][3], stock[i][13]))
            
    df = pd.DataFrame(stock)
    df = df.set_index(0)
    df.columns = ["node_num", "up_times", "down_times", "theta", "up", "down", "prob", "up_r", "down_r", "value", "wealth", "U_0", "U_1", "alpha", "Exp_U1"]
    
    return df["Exp_U1"][10]
    
