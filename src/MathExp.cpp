//Author : Sygmei
//Key : 976938ef7d46c286a2027d73f3a99467bcfa8ff0c1e10bd0016139744ef5404f4eb4d069709f9831f6de74a094944bf0f1c5bf89109e9855290336a66420376f

#include "MathExp.hpp"

namespace obe
{
	namespace Math
	{
		//ExpBloc
		ExpBloc::ExpBloc(std::string content) {
			this->content = content;
		}
		ExpBloc::ExpBloc(std::string content, int priority) {
			this->content = content;
			this->priority = priority;
		}

		//VarDatabase
		void VarDatabase::setStrict(bool strict) {
			this->strict = strict;
		}
		double VarDatabase::getVar(std::string id) {
			if (id == "rand")
				return Functions::Math::randfloat();
			else
			{
				if (varBase.find(id) != varBase.end())
					return varBase[id];
				else
				{
					if (strict)
						std::cout << "<Error:MathExp>[getVar] : " << id << " doesn't exist (Disable strict mode to return 0)" << std::endl;
					else
					{
						std::cout << "<Warning:MathExp>[getVar] : " << id << " doesn't exist (returned 0 in tolerent mode)" << std::endl;
						return 0;
					}
				}
			}

		}
		void VarDatabase::setVar(std::string id, double value) {
			varBase[id] = value;
		}

		//ExpOperator
		ExpOperator::ExpOperator(std::string id, ExpBloc* op, VarDatabase* hook) {
			this->id = id;
			this->op = op;
			this->varBaseHook = hook;
		}
		std::string ExpOperator::getID() {
			return this->id;
		}
		ExpOperator* ExpOperator::getLeftOp() {
			return leftOp;
		}
		ExpOperator* ExpOperator::getRightOp() {
			return rightOp;
		}
		ExpBloc* ExpOperator::getLeftSimpleOp() {
			return leftSimpleOp;
		}
		ExpBloc* ExpOperator::getRightSimpleOp() {
			return rightSimpleOp;
		}
		void ExpOperator::setMembers(ExpBloc* leftOp, ExpBloc* rightOp) {
			this->leftSimpleOp = leftOp;
			this->rightSimpleOp = rightOp;
			this->opMode = 3;
		}
		void ExpOperator::setMembers(ExpOperator* leftOp, ExpOperator* rightOp) {
			this->leftOp = leftOp;
			this->rightOp = rightOp;
			this->opMode = 12;
		}
		void ExpOperator::setMembers(ExpBloc* leftOp, ExpOperator* rightOp) {
			this->leftSimpleOp = leftOp;
			this->rightOp = rightOp;
			this->opMode = 6;
		}
		void ExpOperator::setMembers(ExpOperator* leftOp, ExpBloc* rightOp) {
			this->leftOp = leftOp;
			this->rightSimpleOp = rightOp;
			this->opMode = 9;
		}
		bool ExpOperator::isEndNode() {
			return (opMode == 3);
		}
		int ExpOperator::getOpMode() {
			return opMode;
		}
		double ExpOperator::processResult() {
			if (op->content != "@")
			{
				double leftMember;
				double rightMember;
				if (opMode == 3)
				{
					if (Functions::String::isStringNumeric(leftSimpleOp->content))
						leftMember = std::stod(leftSimpleOp->content);
					else
						leftMember = varBaseHook->getVar(leftSimpleOp->content);
					if (Functions::String::isStringNumeric(rightSimpleOp->content))
						rightMember = std::stod(rightSimpleOp->content);
					else
						rightMember = varBaseHook->getVar(rightSimpleOp->content);
				}
				else if (opMode == 6)
				{
					if (Functions::String::isStringNumeric(leftSimpleOp->content))
						leftMember = std::stod(leftSimpleOp->content);
					else
						leftMember = varBaseHook->getVar(leftSimpleOp->content);
					rightMember = rightOp->processResult();
				}
				else if (opMode == 9)
				{
					leftMember = leftOp->processResult();
					if (Functions::String::isStringNumeric(rightSimpleOp->content))
						rightMember = std::stod(rightSimpleOp->content);
					else
						rightMember = varBaseHook->getVar(rightSimpleOp->content);
				}
				else if (opMode == 12)
				{
					leftMember = leftOp->processResult();
					rightMember = rightOp->processResult();
				}
				if (op->content == "+")
					return leftMember + rightMember;
				else if (op->content == "-")
					return leftMember - rightMember;
				else if (op->content == "*")
					return leftMember * rightMember;
				else if (op->content == "/")
					return leftMember / rightMember;
				else if (op->content == "%")
					return (double)((int)leftMember % (int)rightMember);
				else if (op->content == "^")
					return std::pow(leftMember, rightMember);
			}
			else
			{
				std::string funcName = leftSimpleOp->content;
				std::vector<double> parameterList;
				std::vector<std::string> multipleParameter = Functions::String::split(leftSimpleOp->content, ",");

				for (unsigned int i = 0; i < multipleParameter.size(); i++)
				{
					if (opMode == 3)
					{
						if (Functions::String::isStringNumeric(rightSimpleOp->content))
							parameterList.push_back(std::stod(rightSimpleOp->content));
						else
							parameterList.push_back(varBaseHook->getVar(rightSimpleOp->content));
					}
					else if (opMode == 6)
						parameterList.push_back(rightOp->processResult());
				}
				int parameterNumber = parameterList.size();

				//Add your functions here
				if (funcName == "sin")
					return std::sin(parameterList[0]);
				else if (funcName == "cos")
					return std::cos(parameterList[0]);
				else if (funcName == "tan")
					return std::tan(parameterList[0]);
				else if (funcName == "asin")
					return std::asin(parameterList[0]);
				else if (funcName == "acos")
					return std::acos(parameterList[0]);
				else if (funcName == "atan")
					return std::atan(parameterList[0]);
				else if (funcName == "sinh")
					return std::sinh(parameterList[0]);
				else if (funcName == "cosh")
					return std::cosh(parameterList[0]);
				else if (funcName == "tanh")
					return std::tanh(parameterList[0]);
				else if (funcName == "asinh")
					return std::asinh(parameterList[0]);
				else if (funcName == "acosh")
					return std::acosh(parameterList[0]);
				else if (funcName == "atanh")
					return std::atanh(parameterList[0]);
				else if (funcName == "exp")
					return std::exp(parameterList[0]);
				else if (funcName == "abs")
					return std::abs(parameterList[0]);
				else if (funcName == "log")
					return std::log(parameterList[0]);
				else if (funcName == "log10")
					return std::log10(parameterList[0]);
				else if (funcName == "sqrt")
					return std::sqrt(parameterList[0]);
				else if (funcName == "cbrt")
					return std::cbrt(parameterList[0]);
				else if (funcName == "ceil")
					return std::ceil(parameterList[0]);
				else if (funcName == "floor")
					return std::floor(parameterList[0]);
				else if (funcName == "round")
					return std::round(parameterList[0]);
				else if (funcName == "bound")
				{
				}
				//Custom Functions
				else if (funcName == "heav") //Heaviside Step Function
					return ((parameterList[0] >= 0) ? 1 : 0);
				else if (funcName == "sgn") //Sign Function
					if (parameterList[0] != 0) return (parameterList[0] / std::abs(parameterList[0])); else return 0;
			}
		}

		//MathExp
		MathExp::MathExp(std::string mathexp, bool strict)
		{
			this->mathexp = mathexp;
			this->varBase = new VarDatabase;
			this->varBase->setStrict(strict);
			this->expProcessed = false;
			this->createConstants();
		}
		void MathExp::setExpr(std::string mathexp)
		{
			this->mathexp = mathexp;
			delete this->varBase;
			this->varBase = new VarDatabase;
			this->varBase->setStrict(true);
			this->expProcessed = false;
		}
		void MathExp::createConstants() //Constants
		{
			this->varBase->setVar("pi", Functions::Math::pi);
			this->varBase->setVar("e", std::exp(1));
		}
		void MathExp::buildMathExp(bool verbose)
		{
			if (verbose) std::cout << "Building MathExp" << std::endl;
			if (mathexp != "")
			{
				std::vector<std::string> expOperators = { "+", "-", "*", "/", "%", "^", "(", ")", "@" };
				std::vector<std::string> parsedMathExp = Functions::String::multiSplit(Functions::String::replaceString(mathexp, " ", ""), expOperators);
				blocVec.clear();
				for (unsigned int i = 0; i < parsedMathExp.size(); i++)
					blocVec.push_back(new ExpBloc(parsedMathExp[i]));
				int currentPriority = 0;
				for (unsigned int i = 0; i < blocVec.size(); i++) //Parenthesis Priority
				{
					blocVec[i]->priority = currentPriority;
					if (blocVec[i]->content == "(")
						currentPriority++;
					else if (blocVec[i]->content == ")")
						currentPriority--;
				}
				if (currentPriority != 0 && verbose)
					std::cout << "[MathExp] Warning : Priority Problem : Parenthesis : " << currentPriority << std::endl;
				int i = 0;
				while (i < blocVec.size()) //Negative Numbers
				{
					if (blocVec[i]->content == "-" && i == 0)
					{
						blocVec.insert(blocVec.begin(), new ExpBloc("0", 0));
						i += 2;
					}
					else if (blocVec[i]->content == "-" && blocVec[i - 1]->content == "(")
					{
						blocVec.insert(blocVec.begin() + i, new ExpBloc("0", 0));
						i += 2;
					}
					else
						i++;
				}
				i = 0;
				while (i < blocVec.size()) //Parenthesis removal
				{
					if (blocVec[i]->content == "(" || blocVec[i]->content == ")")
						blocVec.erase(blocVec.begin() + i);
					else
						i++;
				}
				for (unsigned int i = 0; i < blocVec.size(); i++) //Pow / Func Priority
				{
					if (blocVec[i]->content == "^" || blocVec[i]->content == "@")
					{
						if (blocVec[i + 1]->priority == blocVec[i]->priority)
						{
							blocVec[i]->priority++;
							blocVec[i + 1]->priority++;
						}
						else if (blocVec[i + 1]->priority > blocVec[i]->priority)
						{
							int offset = 1;
							while (blocVec[i + offset]->priority > blocVec[i]->priority)
							{
								if (i + offset > blocVec.size() - 1)
									break;
								blocVec[i + offset]->priority++;
								offset++;
							}
							blocVec[i]->priority++;
						}


					}
					else if ((blocVec[i]->content == "*" || blocVec[i]->content == "/")) //Multiplication / Division Priority
					{
						int priorityLevel = blocVec[i]->priority;
						blocVec[i]->priority++;
						int j = i;
						bool continuePriority = true;
						while (continuePriority)
						{
							if (j > 0)
							{
								j--;
								if (blocVec[j]->priority > priorityLevel)
									blocVec[j]->priority++;
								else if (blocVec[j]->content != "+" && blocVec[j]->content != "-" && blocVec[j]->priority == priorityLevel)
									blocVec[j]->priority++;
								else
									continuePriority = false;
							}
							else
								continuePriority = false;
						}
						j = i;
						continuePriority = true;
						while (continuePriority)
						{
							if (j < blocVec.size() - 1)
							{
								j++;
								if (blocVec[j]->priority > priorityLevel)
									blocVec[j]->priority++;
								else if (blocVec[j]->content != "+" && blocVec[j]->content != "-" && blocVec[j]->priority == priorityLevel)
									blocVec[j]->priority++;
								else
									continuePriority = false;
							}
							else
								continuePriority = false;
						}
					}
				}
				if (verbose) std::cout << "Building Tree" << std::endl;
				std::vector<std::string> expSearchOp = { "+", "-", "*", "/", "%", "^", "@" };
				int treeID = 0;
				while (blocVec.size() != 1)
				{
					int greatestPriority = -1;
					int greatestPriorityIndex = -1;
					for (unsigned int i = 0; i < blocVec.size(); i++)
					{
						if (blocVec[i]->priority > greatestPriority && Functions::Vector::isInList(blocVec[i]->content, expSearchOp))
						{
							greatestPriority = blocVec[i]->priority;
							greatestPriorityIndex = i;
						}
					}
					ExpOperator* tempOperation = new ExpOperator(std::to_string(treeID), blocVec[greatestPriorityIndex], varBase);
					if (blocVec[greatestPriorityIndex - 1]->content.substr(0, 1) == "$")
					{
						if (blocVec[greatestPriorityIndex + 1]->content.substr(0, 1) == "$")
							tempOperation->setMembers(expTree[blocVec[greatestPriorityIndex - 1]->content], expTree[blocVec[greatestPriorityIndex + 1]->content]);
						else
							tempOperation->setMembers(expTree[blocVec[greatestPriorityIndex - 1]->content], blocVec[greatestPriorityIndex + 1]);
					}
					else if (blocVec[greatestPriorityIndex + 1]->content.substr(0, 1) == "$")
						tempOperation->setMembers(blocVec[greatestPriorityIndex - 1], expTree[blocVec[greatestPriorityIndex + 1]->content]);
					else
						tempOperation->setMembers(blocVec[greatestPriorityIndex - 1], blocVec[greatestPriorityIndex + 1]);
					blocVec[greatestPriorityIndex] = new ExpBloc("$" + std::to_string(treeID));
					blocVec[greatestPriorityIndex]->priority = greatestPriority;
					expTree["$" + std::to_string(treeID)] = tempOperation;
					blocVec.erase(blocVec.begin() + greatestPriorityIndex - 1);
					blocVec.erase(blocVec.begin() + greatestPriorityIndex);
					treeID++;
					if (verbose) std::cout << "Building Tree State : " << std::endl;
					for (unsigned int i = 0; i < blocVec.size(); i++)
						if (verbose) std::cout << "[{" + std::to_string(blocVec[i]->priority) + "}" + blocVec[i]->content + "]";
					if (verbose) std::cout << std::endl;
				}
				expProcessed = true;
				if (blocVec[0]->content.substr(0, 1) != "$")
				{
					if (Functions::String::isStringNumeric(blocVec[0]->content))
					{
						isResultStatic = true;
						staticResult = std::stod(blocVec[0]->content);
					}
				}
			}
		}

		void MathExp::setVar(std::string varName, double value)
		{
			varBase->setVar(varName, value);
		}

		double MathExp::getResult()
		{
			if (expProcessed)
			{
				if (blocVec[0]->content.substr(0, 1) == "$")
					return expTree[blocVec[0]->content]->processResult();
				else
				{
					if (isResultStatic)
						return staticResult;
					else
						return varBase->getVar(blocVec[0]->content);
				}

			}
			else
				return 0;
		}

		bool MathExp::isStatic()
		{
			return isResultStatic;
		}

		//MathExpObject
		MathExpObject::MathExpObject(double precision)
		{
			this->precision = precision;
			this->registerMathExp("lowerBound", "0");
			this->registerMathExp("upperBound", "t + 1");
			this->registerOutputVar("lowerBound", &lowerBound);
			this->registerOutputVar("upperBound", &upperBound);
		}

		MathExpObject::MathExpObject(double precision, std::string lowerBoundExp, std::string upperBoundExp)
		{
			this->precision = precision;
			this->registerMathExp("lowerBound", lowerBoundExp);
			this->registerMathExp("upperBound", upperBoundExp);
			this->registerOutputVar("lowerBound", &lowerBound);
			this->registerOutputVar("upperBound", &upperBound);
		}

		void MathExpObject::setGlobalVar(std::string id, double value)
		{
			for (it_msmxp iterator = allMxp.begin(); iterator != allMxp.end(); iterator++) {
				iterator->second->setVar(id, value);
			}
		}

		void MathExpObject::setLocalVar(std::string local, std::string id, double value)
		{
			allMxp[local]->setVar(id, value);
		}

		void MathExpObject::registerMathExp(std::string id, std::string mathExp)
		{
			allMxp[id] = new MathExp(mathExp);
			allMxp[id]->buildMathExp();
			this->setLocalVar(id, "precision", this->precision);
		}

		void MathExpObject::registerOutputVar(std::string id, double* varPointer)
		{
			allRes[id] = varPointer;
		}

		void MathExpObject::processAllExp()
		{
			if (!processedOnce)
				t = allMxp["lowerBound"]->getResult();
			t += precision;
			if (processedOnce)
			{
				if (t > *allRes["upperBound"])
					t = *allRes["lowerBound"];
			}
			for (it_msmxp iterator = allMxp.begin(); iterator != allMxp.end(); iterator++) {
				iterator->second->setVar("t", t);
				*allRes[iterator->first] = iterator->second->getResult();
			}
			if (!processedOnce)
			{
				std::vector<std::string> toDelete;
				for (it_msmxp iterator = allMxp.begin(); iterator != allMxp.end(); iterator++) {
					if (iterator->second->isStatic())
						toDelete.push_back(iterator->first);
				}
				for (unsigned int i = 0; i < toDelete.size(); i++)
					allMxp.erase(toDelete[i]);
			}
			else
			{
				for (it_msdbl iterator = allRes.begin(); iterator != allRes.end(); iterator++)
					this->setGlobalVar(iterator->first, *iterator->second);
			}
			processedOnce = true;
		}

		void MathExpObject::setPrecision(double prec)
		{
			this->precision = prec;
			this->setGlobalVar("precision", precision);
		}

		double MathExpObject::getPrecision()
		{
			return this->precision;
		}
	}
}