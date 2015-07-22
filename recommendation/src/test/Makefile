version=1.0.0

lang=cn

#TARGETS=indexEngine


#test for index engine

#indexEngine:
#		g++ t_indexEngine.cpp -o t_indexEngine ../indexEngine.cpp -I /home/lscm/codebase/ilplib/include/ -I /home/lscm/codebase/izenelib/include/ -lboost_system -lboost_filesystem /home/lscm/codebase/ilplib/source/knlp/normalize.cpp

#test for recommendengine

TARGETS=recommendEngine


PUB_DIR:=/home/lscm/codebase
ILP_LIB:=$(PUB_DIR)/ilplib/include/
IZENE_LIB:=$(PUB_DIR)/izenelib/include/
JSON_INC:=/home/lscm/mproj/workproj/github/work-projects/recommendation/include/3third-lib/jsoncpp/include/
JSON_LIB:=/home/lscm/mproj/workproj/github/work-projects/recommendation/include/3third-lib/jsoncpp/lib/

recommendEngine:		
		g++ t_recommendEngine.cpp -o t_recommendEngine ../indexEngine.cpp ../recommendEngine.cpp $(PUB_DIR)/ilplib/source/knlp/normalize.cpp -I $(ILP_LIB) -I $(IZENE_LIB) -I $(JSON_INC) -L $(JSON_LIB) -ljson -lboost_system -lboost_filesystem
