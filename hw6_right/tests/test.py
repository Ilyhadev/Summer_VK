#!/usr/bin/python3.11
import time
import json
import ujson
import cjson
with open('input.txt', 'r') as file:
    lines = file.readlines()

for line in lines:
    # Perform operations on each line
    line=line

line = line[1:-2]
start_ts = time.time()
json_doc = json.loads(line)
end_ts = time.time()
print (f"{end_ts-start_ts} json")

start_ts = time.time()
ujson_doc = ujson.loads(line)
end_ts = time.time()
print (f"{end_ts-start_ts} ujson")

start_ts = time.time()
cjson_doc = cjson.loads(line)
end_ts = time.time()
print (f"{end_ts-start_ts} cjson")
assert json_doc  == cjson_doc

assert line == cjson.dumps(cjson.loads(line))#



