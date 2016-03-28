#pragma once

#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>

#include "Functions.hpp"

class ExpBloc
{
public:
	ExpBloc(std::string content);
	ExpBloc(std::string content, int priority);
	std::string content;
	int priority;
};

class VarDatabase
{
	private:
		std::map<std::string, double> varBase;
		bool strict = true;
	public:
		void setStrict(bool strict);
		double getVar(std::string id);
		void setVar(std::string id, double value);
};

class ExpOperator
{
	private:
		std::string id;
		ExpBloc* op;
		VarDatabase* varBaseHook;
		ExpOperator* leftOp;     //X---
		ExpOperator* rightOp;    //-Y--
		ExpBloc* leftSimpleOp;   //--X-
		ExpBloc* rightSimpleOp;  //---Y
		int opMode;              //12 : XY-- ; 9 : X--Y ; 6 : -YX- ; 3 : --XY
		int priority;
	public:
		ExpOperator(std::string id, ExpBloc* op, VarDatabase* hook);
		std::string getID();
		ExpOperator* getLeftOp();
		ExpOperator* getRightOp();
		ExpBloc* getLeftSimpleOp();
		ExpBloc* getRightSimpleOp();
		void setMembers(ExpBloc* leftOp, ExpBloc* rightOp);
		void setMembers(ExpOperator* leftOp, ExpOperator* rightOp);
		void setMembers(ExpBloc* leftOp, ExpOperator* rightOp);
		void setMembers(ExpOperator* leftOp, ExpBloc* rightOp);
		bool isEndNode();
		int getOpMode();
		double processResult();
};

class MathExp
{
	private:
		bool expProcessed;
		std::map<std::string, double> variableList;
		std::vector<ExpBloc*> blocVec;
		std::map<std::string, ExpOperator*> expTree;
		VarDatabase* varBase;
		std::string mathexp;
		std::ifstream mathexpFile;
		void createConstants();
		bool isResultStatic = false;
		double staticResult;
	public:
		MathExp(std::string mathexp, bool strict = true);
		MathExp(int polymorph, std::string file, bool strict = true);
		void buildMathExp(bool verbose = false);
		void setVar(std::string varName, double value);
		double getResult();
		bool isStatic();
};

typedef std::map<std::string, MathExp*>::iterator it_msmxp;
typedef std::map<std::string, double*>::iterator it_msdbl;

class MathExpObject
{
	private:
		std::map<std::string, MathExp*> allMxp;
		std::map<std::string, double*> allRes;
		
	protected:
		double t;
		double lowerBound, upperBound;
		bool processedOnce;
		double precision;

	public:
		MathExpObject(double precision);
		MathExpObject(double precision, std::string lowerBoundExp, std::string upperBoundExp);
		void processAllExp();
		void registerMathExp(std::string id, std::string mathExp);
		void registerOutputVar(std::string id, double* varPointer);
		void setGlobalVar(std::string id, double value);
		void setLocalVar(std::string local, std::string id, double value);
		void setPrecision(double prec);
		double getPrecision();
};