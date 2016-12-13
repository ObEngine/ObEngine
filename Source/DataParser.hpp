//Author : Sygmei
//Key : 976938ef7d46c286a2027d73f3a99467bcfa8ff0c1e10bd0016139744ef5404f4eb4d069709f9831f6de74a094944bf0f1c5bf89109e9855290336a66420376f

#pragma once

#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>

#include "Functions.hpp"

namespace mse
{
	namespace Data
	{
		std::vector<std::string> convertPath(std::string path);
		std::string getDefaultValueForType(std::string type);
		std::string getVarType(std::string var);
		std::string Path();
		std::string Path(std::vector<std::string> path);
		std::string Path(std::string cPath);
		template <class ... Args>
		std::string Path(std::string cPath, Args ... pathParts);

		namespace Types
		{
			enum AttributeType
			{
				Attribute = 0x0,
				ContainerAttribute = 0x1,
				BaseAttribute = 0x2,
				ListAttribute = 0x3,
				ComplexAttribute = 0x4,
				LinkAttribute = 0x5
			};
		}

		class DataParserNavigator
		{
			private:
				std::string currentRootAttribute;
				std::string currentPath;
			public:
				std::string getFullPath();
				std::string getCurrentRootAttribute();
				std::string getCurrentPath();
				void setCurrentRootAttribute(std::string object);
				void setCurrentRootAttribute(std::string object, std::string path);
				void setCurrentPath(std::string path);
				void goTo(std::string path);
				void goRoot();
				void goBack();
		};

		class ContainerAttribute;
		class Attribute
		{
			protected:
				std::string id;
				Types::AttributeType type = Types::Attribute;
				std::string annotation = "";
				ContainerAttribute* parent = nullptr;
				virtual void removeParent(ContainerAttribute* currentParent);
				virtual ContainerAttribute* getParent();
				friend class ContainerAttribute;
			public:
				Attribute(ContainerAttribute* parent, std::string id, Types::AttributeType type);
				virtual void setAnnotation(std::string annotation);
				virtual std::string getAnnotation();
				virtual std::string getID();
				virtual Types::AttributeType getType();
				virtual void setParent(ContainerAttribute* parent);
				virtual std::string getNodePath();
				virtual void setID(std::string id);
		};

		class ContainerAttribute : public Attribute
		{
			protected:
			public:
				ContainerAttribute(ContainerAttribute* parent, std::string id, Types::AttributeType type);
				virtual Attribute* removeOwnership(Attribute* element);
				virtual Attribute* extractElement(Attribute* element) = 0;
		};

		class LinkAttribute : public Attribute
		{
			private:
				std::string path;
			public:
				LinkAttribute(std::string id, std::string path);
				void copy();
				template <class A>
				A* get();
		};

		class BaseAttribute : public Attribute
		{
			private:
				std::string data;
				std::string dtype;
				ContainerAttribute* parent;
			public:
				BaseAttribute(ContainerAttribute* parent, std::string id, std::string btype, std::string bdata);
				BaseAttribute(std::string id, std::string btype, std::string bdata);
				std::string returnData();
				void set(int var);
				void set(double var);
				void set(std::string var);
				void set(bool var);
				std::string getDataType();
				template <class T> T get() {}
		};

		class ListAttribute : public ContainerAttribute
		{
			private:
				std::string dataType;
				std::vector<BaseAttribute*> dataList;
			public:
				ListAttribute(ContainerAttribute* parent, std::string id, std::string dataType);
				ListAttribute(std::string id, std::string dataType);
				~ListAttribute();
				unsigned int getSize();
				std::string getDataType();
				BaseAttribute* getElement(unsigned int index);
				void createElement(std::string element);
				Attribute* extractElement(Attribute* element);
		};

		class ListGenerator
		{
			private:
				std::string genType;
				std::string genRegex;
				ListAttribute* genTarget;
				std::vector<std::pair<int, int>> genBounds;
				std::vector<int> genItems;
			public:
				ListGenerator(std::string gtype, std::string regex, ListAttribute* gtarget);
				std::string getRegex();
				std::vector<std::pair<int, int>> getAllBounds();
				void addBound(int gstart, int gend);
				void generate();
		};

		class ComplexAttribute : public ContainerAttribute
		{
			private:
				ComplexAttribute* parent = nullptr;
			protected:
				std::map<std::string, Attribute*> childAttributes;
				std::vector<std::string> childAttributesNames;
				std::map<std::string, ListGenerator*> listGenerators;
				std::vector<std::string> listGeneratorsList;
			public:
				ComplexAttribute(ComplexAttribute* parent, std::string id);
				ComplexAttribute(ComplexAttribute* parent, std::string id, ComplexAttribute* herit);
				ComplexAttribute(ComplexAttribute* parent, std::string id, std::vector<ComplexAttribute*>* multipleHerit);
				ComplexAttribute(std::string id);
				ComplexAttribute(std::string id, ComplexAttribute* herit);
				ComplexAttribute(std::string id, std::vector<ComplexAttribute*>* multipleHerit);
				~ComplexAttribute();
				Attribute* extractElement(Attribute* element);
				void heritage(ComplexAttribute* heritTarget);
				ComplexAttribute* getPath(std::string attributePath);
				BaseAttribute* getBaseAttribute(std::string attributeName);
				ComplexAttribute* getComplexAttribute(std::string id);
				ListAttribute* getListAttribute(std::string id);
				Types::AttributeType getAttributeType(std::string id);
				std::vector<std::string> getAllAttributes();
				std::vector<std::string> getAllComplexAttributes();
				std::vector<std::string> getAllBaseAttributes();
				std::vector<std::string> getAllListAttributes();
				bool containsAttribute(std::string attributeName);
				bool containsBaseAttribute(std::string attributeName);
				bool containsComplexAttribute(std::string attributeName);
				bool containsListAttribute(std::string attributeName);
				void createBaseAttribute(std::string name, std::string type, std::string data);
				void createBaseAttribute(std::string name, std::string data);
				void createBaseAttribute(std::string name, bool data);
				void createBaseAttribute(std::string name, int data);
				void createBaseAttribute(std::string name, double data);
				void pushBaseAttribute(BaseAttribute* attr);
				void createListAttribute(std::string id, std::string type);
				void pushListAttribute(ListAttribute* attr);
				void createListItem(std::string listID, std::string value);
				void createListGenerator(std::string gtarget, std::string gtype, std::string regex);
				void addBoundToListGenerator(std::string listID, int gstart, int gend);
				void generateInList(std::string listID);
				void createComplexAttribute(std::string id);
				void pushComplexAttribute(ComplexAttribute* cmplx);
				void writeAttributes(std::ofstream* file, unsigned int depth = 0);
				void deleteBaseAttribute(std::string id, bool freeMemory = false);
				void deleteComplexAttribute(std::string id, bool freeMemory = false);
				void deleteListAttribute(std::string id, bool freeMemory = false);
		};

		class ObjectModel
		{
			private:
				std::string name;
				ComplexAttribute signature;
				ComplexAttribute body;
			protected:
				static std::map<std::string, ObjectModel*> modelMap;
				ObjectModel(std::string modelName, std::string modelSignature);
				ComplexAttribute buildModel(std::string objectName, std::string buildSignature);
			public:
				static void CreateModel(std::string modelName, std::string objectSignature);
				static ComplexAttribute BuildObjectFromModel(std::string modelName, std::string objectName, std::string buildSignature);
		};

		class DataParser
		{
			private:
				std::string fileName;
				ComplexAttribute* root = nullptr;
				std::vector<std::string> flagList;
				std::ifstream useFile;
				std::ofstream outFile;
				bool autoMemory = true;
				DataParserNavigator* dpNav = NULL;
				bool checkNavigator();
			public:
				DataParser();
				DataParser(bool autoMemoryManagement);
				~DataParser();
				DataParserNavigator* hookNavigator(DataParserNavigator* dpNav);
				DataParserNavigator* accessNavigator();
				void createFlag(std::string flag);
				void createRootAttribute(std::string id);
				bool containsRootAttribute(std::string objectName);
				ComplexAttribute* extractRootAttribute(std::string rootAttributeName);
				ComplexAttribute* getRootAttribute(std::string id);
				ComplexAttribute* getPath(std::string path);
				void createBaseAttribute(std::string attributePath, std::string name, std::string data);
				void createBaseAttribute(std::string attributePath, std::string name, bool data);
				void createBaseAttribute(std::string attributePath, std::string name, int data);
				void createBaseAttribute(std::string attributePath, std::string name, double data);
				void createBaseAttribute(std::string name, std::string data);
				void createBaseAttribute(std::string name, bool data);
				void createBaseAttribute(std::string name, int data);
				void createBaseAttribute(std::string name, double data);
				void pushBaseAttribute(std::string attributePath, BaseAttribute* attr);
				void pushBaseAttribute(BaseAttribute* attr);
				void createListAttribute(std::string attributePath, std::string id, std::string type);
				void createListAttribute(std::string id, std::string type);
				void pushListAttribute(std::string attributePath, ListAttribute* attr);
				void pushListAttribute(ListAttribute* attr);
				void createListItem(std::string attributePath, std::string listID, std::string value);
				void createListItem(std::string listID, std::string value);
				void createListGenerator(std::string attributePath, std::string gtarget, std::string gtype, std::string regex);
				void createListGenerator(std::string gtarget, std::string gtype, std::string regex);
				void addBoundToListGenerator(std::string attributePath, std::string listID, int gstart, int gend);
				void addBoundToListGenerator(std::string listID, int gstart, int gend);
				void generateInList(std::string attributePath, std::string listID);
				void generateInList(std::string listID);
				void createComplexAttribute(std::string attributePath, std::string id);
				void createComplexAttribute(std::string id);
				void pushComplexAttribute(std::string attributePath, ComplexAttribute* cmplx);
				void pushComplexAttribute(ComplexAttribute* cmplx);
				bool parseFile(std::string filename, bool verbose = false);
				void writeFile(std::string filename, bool verbose = false);
				bool hasFlag(std::string flagName);
				unsigned int getAmountOfFlags();
				std::string getFlagAtIndex(int index);
				std::vector<std::string> getAllComplexAttributes(std::string attributePath);
				std::vector<std::string> getAllComplexAttributes();
				std::vector<std::string> getAllBaseAttributes(std::string attributePath);
				std::vector<std::string> getAllBaseAttributes();
				std::vector<std::string> getAllListAttributes(std::string attributePath);
				std::vector<std::string> getAllListAttributes();
				bool containsBaseAttribute(std::string attributePath, std::string attributeName);
				bool containsBaseAttribute(std::string attributeName);
				bool containsComplexAttribute(std::string attributePath, std::string attributeName);
				bool containsComplexAttribute(std::string attributeName);
				bool containsListAttribute(std::string attributePath, std::string attributeName);
				bool containsListAttribute(std::string attributeName);
				BaseAttribute* getBaseAttribute(std::string attributePath, std::string attributeName);
				BaseAttribute* getBaseAttribute(std::string attributeName);
				ComplexAttribute* getComplexAttribute(std::string attributePath, std::string id);
				ComplexAttribute* getComplexAttribute(std::string id);
				ListAttribute* getListAttribute(std::string attributePath, std::string listName);
				ListAttribute* getListAttribute(std::string listName);
				unsigned int getListSize(std::string attributePath, std::string listName);
				unsigned int getListSize(std::string listName);
				BaseAttribute* getListItem(std::string attributePath, std::string listName, int listItem);
				BaseAttribute* getListItem(std::string listName, int listItem);
				std::vector<std::string> getAllRootAttributes();
				void deleteRootAttribute(std::string name, bool freeMemory = false);
		};
	}
}

namespace mse
{
	namespace Data
	{
		template <> inline int BaseAttribute::get() {
			if (dtype == "int")
				return std::stoi(data);
			else
				std::cout << "<Error:DataParser:BaseAttribute>[getData] : " \
				<< getNodePath() << " is not a <int> BaseAttribute (" << dtype << ")" << std::endl;
		}
		template <> inline double BaseAttribute::get() {
			if (dtype == "float")
				return std::stod(data);
			else
				std::cout << "<Error:DataParser:BaseAttribute>[getData] : " \
				<< getNodePath() << " is not a <float> BaseAttribute (" << dtype << ")" << std::endl;
		}
		template <> inline bool BaseAttribute::get() {
			if (dtype == "bool")
				return (data == "True") ? true : false;
			else
				std::cout << "<Error:DataParser:BaseAttribute>[getData] : " \
				<< getNodePath() << " is not a <bool> BaseAttribute (" << dtype << ")" << std::endl;
		}
		template <> inline std::string BaseAttribute::get() {
			if (dtype == "string")
				return data;
			else
				std::cout << "<Error:DataParser:BaseAttribute>[getData] : " \
				<< getNodePath() << " is not a <string> BaseAttribute (" << dtype << ")" << std::endl;
		}
		template<class ...Args>
		std::string Path(std::string cPath, Args ...pathParts)
		{
			return cPath + "/" + Path(pathParts...);
		}
	}
}