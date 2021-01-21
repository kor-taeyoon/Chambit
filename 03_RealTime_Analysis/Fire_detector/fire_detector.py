import pandas
from haversine import haversine

start = (37.65006, 127.077821)
goal = (37.638562, 127.0754)

print(haversine(start, goal), 'km')


