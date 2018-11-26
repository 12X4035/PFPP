import pandas as pd
import numpy as np
from scipy.special import comb

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

def backward(N, theta, u, d, p, price_x, default_x):
    
    pi = (((p*(u-1))/((1-p)*(1-d)))**theta)/(u-1+(((p*(u-1))/((1-p)*(1-d)))**theta)*(1-d))


    num = [ i for i in range(N+1)]
    stock = [[ [] for i in range(N+1) ] for j in range(N+1)]
    
    #⇡リスト内包表記のほうが速いらしい         
    #for i in range(N+1):
    #    stock.append([])
    #    for j in range(0,N+1):
    #        stock[i].append([])
    M = p*(1+pi*(u-1))**(1-(1/theta))+(p-1)*(1+pi*(d-1))**(1-(1/theta))
    
    val = value(N+1, u, d, pi, default_x)
    
    for i in range(N+1):
        for j in range(N+1):
            #index
            stock[i][0] = i
            #node_num
            stock[i][1] = num[0:i+1]
            #up_times
            stock[i][2] = num[i::-1]
            #down_times
            stock[i][3] = num[0:i+1]
            #theta
            stock[i][4] = theta
            #prob
            stock[i][5] = p
            #up_r
            stock[i][6] = list(map(lambda x: 0 if x==0 else u**x, num[0:i+1]))
            #down_r
            stock[i][7] = list(map(lambda x: 0 if x==0 else d**x, num[i::-1]))
            #price
            stock[i][8] = list(map(lambda x, y: price_x if x==0 and y==0 else (price_x*x)+(price_x*y) if x==0 or y==0 else (price_x*x*y), stock[i][6], stock[i][7]))
            #value
            
            #if i==N:
            #stock[i][9] = list(map(lambda x:((1-(1/theta))**(-1))*(x**(1-(1/theta))), stock[i][8]))
            #else:
            #stock[i][9] = list(map(lambda x: ((p*((1-(1/theta))**(-1))*((x*(1+pi*(u-1)))**(1-(1/theta)))+((1-p)*((1-(1/theta))**(-1)))*((x*(1+pi*(d-1)))**(1-(1/theta))))**(N-i))*(((1-(1/theta))**(-1))*(x**(1-(1/theta)))) , stock[i][8]))
            #stock[i][9] = list(map(lambda x: ((p*((1-(1/theta))**(-1))*((x*(1+pi*(u-1)))**(1-(1/theta)))+((1-p)*((1-(1/theta))**(-1)))*((x*(1+pi*(d-1)))**(1-(1/theta))))**(N-1-i-1)) , stock[i][8]))
            
            #stock[i][9] = value(N+1, u, d, pi, default_x)[i]
            stock[i][9] = val[i]
            

            #strategy
            #if i==0:
            #    stock[i][10] = 0
            #else:
            #    stock[i][10] = list(map(lambda x, y:(pi*y)/x, stock[i][8], stock[i][9])) 
            
            #stock[i][10] = list(map(lambda x: ((1-(1/theta))**(-1))*(x**(1-(1/theta))), stock[i][9]))
            
            #Wealth
            stock[i][10] = list(map(lambda x: (M**((N+1)-i))*((1/(1-theta))**(-1))*(x)**(1-(1/theta)), stock[i][9]))
            
            #Utility
            stock[i][11] = list(map(lambda x: (1-1/theta)**(-1)*x**(1-1/theta), stock[i][9]))
            #Exp_value
            #stock[i][11] = list(map(lambda  l, m, n : (p**l)*((1-p)**m)*n if (l!=0 and m!=0) \
            #                    else (p**l)*n if m==0 \
            #                    else ((1-p)**m)*n if l==0 \
            #                    else nan \
            stock[i][12] = list(map(lambda  l, m, n : comb(i, l, exact=True)*(p**l)*((1-p)**m)*n if (l!=0 and m!=0) \
                                 else (p**l)*n if m==0 \
                                 else ((1-p)**m)*n if l==0 \
                                 else nan \
                                , stock[i][2], stock[i][3], stock[i][11]))
    df = pd.DataFrame(stock)
    df = df.set_index(0)
    df.columns = ["node_num", "up_times", "down_times", "theta", "prob", "up_r", "down_r", "price", "value", "wealth", "utility", "Exp_val"]
    
    
    return df["Exp_val"][10]
