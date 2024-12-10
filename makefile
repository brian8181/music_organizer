# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.

# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.

# License:    None
# File Name:  ./Makefile
# Build Date: Tue Nov 14 04:08:48 PM CST 2023
# Version:    0.0.1

CXX = g++
CXXFLAGS = -Wall -std=c++20 -DDEBUG -g
#CXXFLAGS = -Wall -std=c++17 -DDEBUG -DNO_SHOW -g
BUILD = build
OBJ =  build
SRC = src
LDFLAGS = -static -llibfmt -L/usr/local/lib64/fmt
INCLUDES = -I/usr/local/include/fmt/

all: music_gui

music_gui: music_gui.o 
	 $(CXX) $(CXXFLAGS) $(BUILD)/music_gui.o /usr/local/lib64/libfmt.a -o $(BUILD)/music_gui

music_gui.o:
	$(CXX) $(CXXFLAGS) -c $(SRC)/music_gui.cpp -o $(BUILD)/music_gui.o

clean:
	-rm -f $(BUILD)/*
	