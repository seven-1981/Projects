# Directory for Audio files
INC_AUDIO=Audio
# Audio files
FILE_AUDIO1=Audio/ALSACardLister.cpp
FILE_AUDIO2=Audio/ALSACardInfoGetter.cpp
FILE_AUDIO3=Audio/ALSACardConfigurator.cpp
FILE_AUDIO4=Audio/ALSACardManager.cpp

# Final include variable
INC=-I $(INC_AUDIO) $(FILE_AUDIO1) -I $(INC_AUDIO) $(FILE_AUDIO2) -I $(INC_AUDIO) $(FILE_AUDIO3) -I $(INC_AUDIO) $(FILE_AUDIO4)

SRC=$(wildcard *.cpp)
BINS=$(SRC:.cpp=)

# Used compiler
CC=g++
# Flags for compiler
CXXFLAGS=-Wall $(INC)
# Flags for linker
LDFLAGS=-lasound

all: $(BINS)
