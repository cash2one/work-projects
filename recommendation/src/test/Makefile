version=1.0.0

lang=cn

#TARGETS=indexEngine


#test for index engine

#indexEngine:
#		g++ t_indexEngine.cpp -o t_indexEngine ../indexEngine.cpp -I /home/lscm/codebase/ilplib/include/ -I /home/lscm/codebase/izenelib/include/ -lboost_system -lboost_filesystem /home/lscm/codebase/ilplib/source/knlp/normalize.cpp

#test for recommendengine

TARGETS=recommendEngine

recommendEngine:		
		g++ t_recommendEngine.cpp -o t_recommendEngine ../indexEngine.cpp ../recommendEngine.cpp -I /home/lscm/codebase/ilplib/include/ -I /home/lscm/codebase/izenelib/include/ -lboost_system -lboost_filesystem /home/lscm/codebase/ilplib/source/knlp/normalize.cpp
