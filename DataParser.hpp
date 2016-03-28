#pragma once

#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>

#include "Functions.hpp"

std::string reverseConvertPath(std::vector<std::string> path);
std::vector<std::string> convertPath(std::string path);

class DataParserNavigator
{
	private:
		std::string currentDataObject;
		std::string currentPath;
	public:
		std::string getCurrentDataObject();
		std::string getCurrentPath();
		void setCurrentDataObject(std::string object);
		void setCurrentDataObject(std::string object, std::string path);
		void setCurrentPath(std::string path);
		void goTo(std::string path);
		void goRoot();
		void goBack();
};

class BaseAttribute
{
	private:
		std::string name;
		std::string data;
		std::string dtype;
	public:
		BaseAttribute(std::string bname, std::string btype, std::string bdata);
		std::string getName();
		std::string returnData();
		int getData(int* var);
		double getData(double* var);
		std::string getData(std::string* var);
		bool getData(bool* var);
		void setData(int var);
		void setData(double var);
		void setData(std::string var);
		void setData(bool var);
		std::string getType();
};

class ListAttribute
{
private:
	std::string listId;
	std::string dataType;
	std::vector<BaseAttribute*> dataList;
public:
	ListAttribute(std::string lId, std::string dataType);
	unsigned int getSize();
	std::string getID();
	std::string getType();
	BaseAttribute* getElement(unsigned int index);
	void createElement(std::string element);
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


class ComplexAttribute
{
	private:
		std::string id;
		std::map<std::string, BaseAttribute*> baseAttributes;
		std::vector<std::string> baseAttributeList;
		std::map<std::string, ListAttribute*> listAttributes;
		std::vector<std::string> listAttributeList;
		std::map<std::string, ComplexAttribute*> complexAttributes;
		std::vector<std::string> complexAttributeList;
		std::map<std::string, ListGenerator*> listGenerators;
		std::vector<std::string> listGeneratorsList;
	public:
		ComplexAttribute(std::string attrID);
		ComplexAttribute(const ComplexAttribute& lol);
		ComplexAttribute(std::string attrID, ComplexAttribute* herit);
		ComplexAttribute(std::string attrID, std::vector<ComplexAttribute*>* multipleHerit);
		void heritage(ComplexAttribute* heritTarget);
		unsigned int getClass();
		std::string getID();
		BaseAttribute* getAttribute(std::string attributeName);
		ComplexAttribute* getComplexAttribute(std::string id);
		ListAttribute* getListAttribute(std::string id);
		std::vector<std::string> getAllComplex();
		std::vector<std::string> getAllAttributes();
		std::vector<std::string> getAllLists();
		bool attributeExists(std::string attributeName);
		bool complexExists(std::string attributeName);
		bool listExists(std::string attributeName);
		void createBaseAttribute(std::string name, std::string type, std::string data);
		void pushBaseAttribute(BaseAttribute* attr);
		void createListAttribute(std::string id, std::string type);
		void pushListAttribute(ListAttribute* attr);
		void createListItem(std::string listID, std::string value);
		void createListGenerator(std::string gtarget, std::string gtype, std::string regex);
		void addBoundToListGenerator(std::string listID, int gstart, int gend);
		void generateInList(std::string listID);
		void createComplexAttribute(std::string id);
		void pushComplexAttribute(ComplexAttribute* cmplx);
		void writeAttributes(std::ofstream* file, unsigned int depth = 1);
		void deleteAttribute(std::string id, bool freeMemory = false);
		void deleteComplexAttribute(std::string id, bool freeMemory = false);
		void deleteListAttribute(std::string id, bool freeMemory = false);
};

class DataObject
{
	private:
		std::map<std::string, BaseAttribute*> specialAttributes;
		std::vector<std::string> specialAttributeList;
		std::string objectName;
		std::map<std::string, BaseAttribute*> baseAttributes;
		std::vector<std::string> baseAttributeList;
		std::map<std::string, ListAttribute*> listAttributes;
		std::vector<std::string> listAttributeList;
		std::map<std::string, ComplexAttribute*> complexAttributes;
		std::vector<std::string> complexAttributeList;
		std::map<std::string, ComplexAttribute*> heritComplexAttributes;
		std::vector<std::string> heritComplexAttributeList;
		std::map<std::string, ListGenerator*> listGenerators;
		std::vector<std::string> listGeneratorsList;
	public:
		DataObject(std::string objectname);
		std::string getName();
		ComplexAttribute* getPath(std::vector<std::string> attributePath);
		BaseAttribute* getAttribute(std::vector<std::string> attributePath, std::string attributeName);
		ComplexAttribute* getComplexAttribute(std::vector<std::string> attributePath, std::string id);
		ListAttribute* getListAttribute(std::vector<std::string> attributePath, std::string id);
		std::vector<std::string> getAllComplex(std::vector<std::string> attributePath);
		std::vector<std::string> getAllAttributes(std::vector<std::string> attributePath);
		std::vector<std::string> getAllLists(std::vector<std::string> attributePath);
		bool attributeExists(std::vector<std::string> attributePath, std::string attributeName);
		bool complexExists(std::vector<std::string> attributePath, std::string attributeName);
		bool listExists(std::vector<std::string> attributePath, std::string attributeName);
		void createSpecialAttribute(std::string name, std::string type, std::string data);
		void createBaseAttribute(std::vector<std::string> attributePath, std::string name, std::string type, std::string data);
		void pushBaseAttribute(std::vector<std::string> attributePath, BaseAttribute* attr);
		void createListAttribute(std::vector<std::string> attributePath, std::string id, std::string type);
		void pushListAttribute(std::vector<std::string> attributePath, ListAttribute* attr);
		void createListItem(std::vector<std::string> attributePath, std::string listID, std::string value);
		void createListGenerator(std::vector<std::string> attributePath, std::string gtarget, std::string gtype, std::string regex);
		void addBoundToListGenerator(std::vector<std::string> attributePath, std::string listID, int gstart, int gend);
		void generateInList(std::vector<std::string> attributePath, std::string listID);
		void createComplexAttribute(std::vector<std::string> attributePath, std::string id);
		void pushComplexAttribute(std::vector<std::string> attributePath, ComplexAttribute* cmplx);
		void createHeritComplexAttribute(std::string id);
		void pushHeritComplexAttribute(ComplexAttribute* cmplx);
		void writeAttributes(std::ofstream* file);
		void deleteAttribute(std::vector<std::string> attributePath, std::string id, bool freeMemory = false);
		void deleteComplexAttribute(std::vector<std::string> attributePath, std::string id, bool freeMemory = false);
		void deleteListAttribute(std::vector<std::string> attributePath, std::string id, bool freeMemory = false);
};

class DataParser
{
	private:
		std::string fileName;
		std::map<std::string, DataObject*> objectMap;
		std::vector<std::string> objectList;
		std::vector<std::string> flagList;
		std::ifstream useFile;
		std::ofstream outFile;
		std::string getVarType(std::string line);
		DataParserNavigator* dpNav = NULL;
		bool checkNavigator();
	public:
		DataParser();
		void hookNavigator(DataParserNavigator* dpNav);
		DataParserNavigator* accessNavigator();
		DataObject* accessDataObject(std::string name);
		void createFlag(std::string flag);
		void createDataObject(std::string objectName);
		void pushDataObject(DataObject* object);
		void createSpecialAttribute(std::string object, std::string name, std::string type, std::string data);
		void createSpecialAttribute(std::string name, std::string type, std::string data);
		void createBaseAttribute(std::string object, std::string attributePath, std::string name, std::string data);
		void createBaseAttribute(std::string object, std::string attributePath, std::string name, bool data);
		void createBaseAttribute(std::string object, std::string attributePath, std::string name, int data);
		void createBaseAttribute(std::string object, std::string attributePath, std::string name, double data);
		void createBaseAttribute(std::string name, std::string data);
		void createBaseAttribute(std::string name, bool data);
		void createBaseAttribute(std::string name, int data);
		void createBaseAttribute(std::string name, double data);
		void pushBaseAttribute(std::string object, std::string attributePath, BaseAttribute* attr);
		void pushBaseAttribute(BaseAttribute* attr);
		void createListAttribute(std::string object, std::string attributePath, std::string id, std::string type);
		void createListAttribute(std::string id, std::string type);
		void pushListAttribute(std::string object, std::string attributePath, ListAttribute* attr);
		void pushListAttribute(ListAttribute* attr);
		void createListItem(std::string object, std::string attributePath, std::string listID, std::string value);
		void createListItem(std::string listID, std::string value);
		void createListGenerator(std::string object, std::string attributePath, std::string gtarget, std::string gtype, std::string regex);
		void createListGenerator(std::string gtarget, std::string gtype, std::string regex);
		void addBoundToListGenerator(std::string object, std::string attributePath, std::string listID, int gstart, int gend);
		void addBoundToListGenerator(std::string listID, int gstart, int gend);
		void generateInList(std::string object, std::string attributePath, std::string listID);
		void generateInList(std::string listID);
		void createComplexAttribute(std::string object, std::string attributePath, std::string id);
		void createComplexAttribute(std::string id);
		void pushComplexAttribute(std::string object, std::string attributePath, ComplexAttribute* cmplx);
		void pushComplexAttribute(ComplexAttribute* cmplx);
		void createHeritComplexAttribute(std::string object, std::string id);
		void createHeritComplexAttribute(std::string id);
		void pushHeritComplexAttribute(std::string object, ComplexAttribute* cmplx);
		void pushHeritComplexAttribute(ComplexAttribute* cmplx);
		void parseFile(std::string filename, bool verbose = false);
		void writeFile(std::string filename, bool verbose = false);
		bool hasFlag(std::string flagName);
		unsigned int getAmountOfFlags();
		std::string getFlagAtIndex(int index);
		std::vector<std::string> getAllComplex(std::string object, std::string attributePath);
		std::vector<std::string> getAllComplex();
		std::vector<std::string> getAllAttributes(std::string object, std::string attributePath);
		std::vector<std::string> getAllAttributes();
		std::vector<std::string> getAllLists(std::string object, std::string attributePath);
		std::vector<std::string> getAllLists();
		bool attributeExists(std::string object, std::string attributePath, std::string attributeName);
		bool attributeExists(std::string attributeName);
		bool complexExists(std::string object, std::string attributePath, std::string attributeName);
		bool complexExists(std::string attributeName);
		bool listExists(std::string object, std::string attributePath, std::string attributeName);
		bool listExists(std::string attributeName);
		BaseAttribute* getAttribute(std::string object, std::string attributePath, std::string attributeName);
		BaseAttribute* getAttribute(std::string attributeName);
		ComplexAttribute* getComplexAttribute(std::string object, std::string attributePath, std::string id);
		ComplexAttribute* getComplexAttribute(std::string id);
		ListAttribute* getListAttribute(std::string object, std::string attributePath, std::string listName);
		ListAttribute* getListAttribute(std::string listName);
		unsigned int getListSize(std::string object, std::string attributePath, std::string listName);
		unsigned int getListSize(std::string listName);
		BaseAttribute* getListItem(std::string object, std::string attributePath, std::string listName, int listItem);
		BaseAttribute* getListItem(std::string listName, int listItem);
		std::vector<std::string> getAllDataObjects();
};