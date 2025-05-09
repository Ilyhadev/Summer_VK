#!/usr/bin/python3.11

from setuptools import setup, Extension
def main(): 
	setup(name = "cjson",version = "0.03",author = "ME",date = "13.07.2024",ext_modules=[Extension("cjson",sources = ['cjson.cpp'])])
    
if __name__ == "__main__":
    main()