CC = g++
CFLAGS = -std=c++11 -Wall -pedantic

file_cpp = mainCPP.cpp 
file_py = mainPY.py
grafic= grafic.py

infoTXT = info
OUT_CPP = $(infoTXT)/infoCpp.txt
OUT_PY = $(infoTXT)/infoPy.txt

ifeq ($(OS), Windows_NT)
	RM = del
	TARGET_CPP = mainCPP.exe
else
	RM = rm
	TARGET_CPP = mainCPP
endif

all:
	$(CC) $(CFLAGS) -o $(TARGET_CPP) $(file_cpp)

clean:
	$(RM) *.exe

run: all
	$(TARGET_CPP) > $(OUT_CPP)
	python $(file_py) > $(OUT_PY)
	python $(grafic)