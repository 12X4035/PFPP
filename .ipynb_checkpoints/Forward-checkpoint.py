import pandas as pd
import numpy as np

def forward(N, theta, u, d, p, default_x):

    q = (1-d)/(u-d)
    a = ((1-p)/p)*(q/(1-q))
    b = (1-q)/q
    c = (1-p)/(1-q)

    
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
            #U_0
            stock[i][9] = list(map(lambda x: ((1-(1/theta))**(-1))*(x**(1-(1/theta))), stock[i][8]))
            #I_0
            #stock[i][10] = list(map(lambda x: (x**(-1/theta))**(-1), stock[i][8]))
            #I_1
            #stock[i][11] = list(map(lambda x: (1+b)/((c**theta)*((a**(-theta))+b)*x, stock[i][10]))
            #U_1
            stock[i][10] = list(map(lambda x: (((1+b)/((c**(theta))*((a**(-theta))+b)))**(1/theta))*x, stock[i][9]))
            #pi
            stock[i][11] = list(map(lambda x: ((((1+b)/((c**theta)*((a**(-theta))+b)))*((p/q)**theta)-1)/(u-1))*x, stock[i][8]))
            #Exp[U_1]
            stock[i][12] = list(map(lambda  l, m, n : (p**l)*((1-p)**m)*n if (l!=0 and m!=0) \
                                 else (p**l)*n if m==0 \
                                 else ((1-p)**m)*n if l==0 \
                                 else nan \
                                 , stock[i][2], stock[i][3], stock[i][10]))
            
    df = pd.DataFrame(stock)
    df = df.set_index(0)
    df.columns = ["node_num", "up_times", "down_times", "theta", "prob", "up_r", "down_r", "price", "U_0", "U_1", "alpha", "Exp_U1"]
    """
    x = np.linspace(0, 2*np.pi, 10)
    y = np.sin(x)
    plot = figure(title="simple line example", plot_height=300, plot_width=600, y_range=(-20,20))
    
    r = plot.circle(x, y, color="#2222aa")
    r.data_source.data['x'] = df.index
    r.data_source.data['y'] = df["U_1"]
    push_notebook()
    """
    last_u1_mean = list(map(lambda x: np.mean(x), df["Exp_U1"]))[10]
    
    return df["Exp_U1"][10]
    
