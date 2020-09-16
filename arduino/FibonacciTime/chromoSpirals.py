from scipy.optimize import fmin_powell
# chromoSpirals.py
# ----------------
# Code written by Peter Derlien, University of Sheffield, March 2013
# Draws spiralling patterns of circles using the Golden Angle.
# ----------------

# Import from the numpy and matplotlib packages.
import numpy as np
import matplotlib.pyplot as plt
import matplotlib
from matplotlib.collections import PatchCollection
import matplotlib.patches as mpatches
from pixels import data
from numpy import sin, cos, exp, pi, newaxis
DEG = pi / 180.

ox = 0
oy = 0 # centre of plot

ndiscs = 256
ncols = 8
offset = 0.
tau = (1+5 ** 0.5) / 2.0 # golden ratio approx  =  1.618033989

inc  =  (2 - tau) * 2 * np.pi + offset

hours = (np.arange(12) * (2 * pi) / 12) + 15 * DEG
minutes = np.arange(60) * (2 * pi) / 60
hours %= 2 * pi

theta = 0
k = 8 # scale factor
drad = k * (1 + 5 ** 0.5) / 4.0 # radius of each disc
minv = maxv = 0 # minv and maxv will be used later to display inputs chosen

# now collect in list 'patches' the locations of all the discs
patches = []
xy = np.zeros((ndiscs, 2))
for j in range(ndiscs):
    r = k * j ** 0.5
    theta += inc
    x = ox + r * cos(theta)
    y = oy + r * sin(theta)
    if y > maxv:
        maxv = y
    elif y < minv:
        minv = y
    disc = mpatches.Circle((x, y), drad)
    xy[j] = [x, y]
    patches.append(disc)

# start building the plot 
fig = plt.figure()
ax = plt.axes([0,0,1,1])

# create text to show which inputs the user has chosen
font = "sans-seri" 
maxv = maxv * 0.95
nd = 'ndiscs: ' + str(ndiscs)
plt.text(minv, maxv, nd, ha="center",family=font, size=14)
setting = 'angle offset: '+ str(offset)
plt.text(minv, minv, setting, ha="center",family=font, size=14)
nc = 'ncols: '+ str(ncols)
plt.text(maxv, maxv, nc, ha="left",family=font, size=14)

# build colour cycle, using a number between 0 and 100 for each colour
colcycle = []
s = 100 / ncols
for j in range(ndiscs):
    colcycle.append((j%ncols)*s)
        
# bring together the information for locations and colours of discs
collection = PatchCollection(patches, cmap=matplotlib.cm.jet, alpha=1.0)
collection.set_array(np.array(colcycle))
ax.add_collection(collection)
   
ax.set_xticks([]); ax.set_yticks([]) # suppress display of axes
plt.axis('equal')

y0 = 126
x0 = 128

def transform(x0, y0, scale, rotation):
    xx = (data[:,0] - x0) * scale
    yy = (data[:,1] - y0) * scale
    R = np.array([[cos(rotation), -sin(rotation)],
                  [sin(rotation),  cos(rotation)]])
    xxyy =  (R @ [xx, yy]).T
    return xxyy

def cost(args):
    x0, y0, scale, rotation = args
    xxyy = transform(x0, y0, scale, rotation)
    dsq = (xxyy[:,0,newaxis] - xy[newaxis,:,0]) ** 2 + (xxyy[:,1,newaxis] - xy[newaxis,:,1]) ** 2
    out = sum(np.amin(dsq, axis=1))
    out += 10000 * (scale - 9.84148160e-01) ** 2
    order = np.argmin(dsq, axis=0)
    out += 10000 * (len(xy) - len(set(order)))
    return out

def get_order(args):
    x0, y0, scale, rotation = args
    xxyy = transform(x0, y0, scale, rotation)
    dsq = (xxyy[:,0,newaxis] - xy[newaxis,:,0]) ** 2 + (xxyy[:,1,newaxis] - xy[newaxis,:,1]) ** 2
    return np.argmin(dsq, axis=0)

best_rot = -1
best_cost = 1e9
best_ans = [127.39201288, 126.41080409,   0.98804093,   2.40007726]
if False:
    for rotation in np.arange(360) * DEG:
        guess = np.array([x0, y0, 1, rotation])
        ans = fmin_powell(cost, guess, disp=False)
        c = cost(ans)
        if c < best_cost:
            print(rotation / DEG, c, ans)
            best_cost = c
            best_rot = rotation
            best_ans = ans
c = cost(best_ans)
ans = best_ans        
print(cost(ans))
xxyy = transform(*ans)
plt.plot(xxyy[:,0], xxyy[:,1], 'b.')

strides = [8]
for stride in strides:
    plt.plot(xy[::stride,0], xy[::stride,1], '-')
idx = get_order(ans)
seen = {}
for i in idx:
    if i in seen:
        print('aha! ', i)
    else:
        seen[i] = 1
plt.plot(xy[::ncols,0], xy[::ncols,1])
plt.plot(xxyy[idx[::ncols],0], xxyy[idx[::ncols],1])
print('int16_t fibindex[256] = {')
for i in range(256):
    print('%3d' % idx[i],end=',')
    if i % 21 == 20:
        print()
print('};')

R = np.sqrt(97 ** 2 + 80 ** 2)
for h in np.arange(12):
    hour = hours[h]
    ### find closest LED to each hour
    hour_xy = np.array([cos(hour), -sin(hour)]) * R
    print ('%3d' % np.argmin(np.linalg.norm(xxyy - hour_xy, axis=1)), end=',')
print()

last = 60
tt = np.arctan2(xy[-last:,1], xy[-last:,0])
plt.figure()
plt.plot(xy[-last:,0], xy[-last:,1], 'r*')
plt.show()
print('minute leds')
for m in np.arange(60):
    minute = -minutes[m]
    ### find closest LED to each hour
    print ('%3d' % np.arange(256-last, 256)[np.argmin(np.abs((minute - tt) % (2 * pi)))], end=',') 
print()

plt.show() # display the plot we have built
## [127.371996, 126.424297, .984148160, .000112555232]
