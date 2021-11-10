CXX		=	g++
CXXFLAGS	=	-g -O3 -Wall

all:		predict

predict:	predict.cc trace.cc branch_predictor.cpp branch.h trace.h branch_predictor.h
		$(CXX) $(CXXFLAGS) -o predict predict.cc trace.cc branch_predictor.cpp

clean:
		rm -f predict
