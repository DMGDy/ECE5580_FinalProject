# config.mk - Configuration settings for building the C++ program

CXX := g++
CXXFLAGS := -fno-inline -Wall -Wextra -std=c++17 -Og -g

# associated directories
SRC_DIR := src
OBJ_DIR := obj
BIN_DIR := bin

TARGET := $(BIN_DIR)/vector_pipeline

