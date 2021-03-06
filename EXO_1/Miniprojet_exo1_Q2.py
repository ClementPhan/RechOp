# -*- coding: utf-8 -*-
"""
Created on Thu Dec 26 00:01:18 2019

@author: viniv
"""

# -*- coding: utf-8 -*-

# Command to solve the pb in conda prompt (user must be located 
# in the good repository):
# pyomo solve --solver=glpk Miniprojet_exo1_Q2.py data.dat
from pyomo.environ import * 

model = AbstractModel()
# Network Nodes
model.N = Set()
# Network Edges
model.A = Set(within=model.N*model.N)

# Puits nodes 
model.p1 = Param(within=model.N)
model.p2 = Param(within=model.N)
model.p3 = Param(within=model.N)
model.p4 = Param(within=model.N)
model.t = Param(within=model.N)

# Cost for each pipe
model.c = Param(model.A, domain=PositiveIntegers)

# The flow over each arc
model.f = Var(model.A, within=NonNegativeReals, initialize=100)

# The boolean variables : choice of pipe
# Choice : build a regular pipe
model.x = Var(model.A, within=Boolean)
# Choice : build a large pipe
model.y = Var(model.A, within=Boolean)


# Enforce that at most one type of pipe is built for each edge
def choice_rule(model, i, j):
    return model.x[i, j] + model.y[i, j] <= 1

model.choice = Constraint(model.A, rule= choice_rule)
# Enforce an upper limit on the flow across each arc
def limit_rule(model, i, j):
    return model.f[i, j] <= 200*model.x[i, j] + 400*model.y[i, j]

model.limit = Constraint(model.A, rule=limit_rule)

# Enforce flow through each node
def flow_rule(model, k):
    
    if k == value(model.p1):
      return sum(model.f[i,j] for (i,j) in model.A if i == k) == 205
    elif k== value(model.p2):
      return sum(model.f[i,j] for (i,j) in model.A if i == k) == 75
    elif k == value(model.p3):
      return sum(model.f[i,j] for (i,j) in model.A if i == k) == 95
    elif k == value(model.p4):
      return sum(model.f[i,j] for (i,j) in model.A if i == k) == 195
    elif k == value(model.t):
      return sum(model.f[i,j] for (i,j) in model.A if j == k) == 570
    elif sum(model.f[i,j] for (i,j) in model.A if j == k) == 0:
        if sum(model.f[i,j] for (i,j) in model.A if i==k) == 0:
            return Constraint.Feasible
        else: 
            return Constraint.Infeasible
    else:
        if sum(model.f[i,j] for (i,j) in model.A if i==k) == 0:
            return Constraint.Infeasible
        else:
            inFlow = sum(model.f[i,j] for (i,j) in model.A if j == k)
            outFlow = sum(model.f[i,j] for (i,j) in model.A if i == k)
            return (inFlow == outFlow)


model.flow = Constraint(model.N, rule=flow_rule)

# Maximize the flow into the sink nodes
def total_rule(model):
    return sum(model.c[i, j]*(model.x[i, j] + 1.5*model.y[i, j]) for (i, j) in model.A)


model.total = Objective(rule=total_rule, sense=minimize)