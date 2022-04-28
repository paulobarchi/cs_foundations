# encoding: utf-8
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.cm as cm

x = [10, 20, 40, 80, 160, 320, 640, 1280, 2560, 5120]
y = [4.602e-05, 0.000143919, 0.00059525, 0.00303475, 0.0121082, 0.0561292, 0.202083, 1.2074, 9.34098, 73.7442]

title = "PerformanceEvaluation-ConvexHull"

plt.plot(x, y)
plt.xlabel('Number of points (n)')
plt.ylabel('Processing time (in seconds)')
plt.title(title)
#plt.legend(bbox_to_anchor=(1.05, 1), loc=2, borderaxespad=0.)
#plt.ylim(0.01, 1.01)
plt.grid(True)
plt.xscale('log')
fig = plt.gcf()
fig.subplots_adjust(bottom=0.3,right=0.82)

plt.savefig(title + ".png")
#plt.show()