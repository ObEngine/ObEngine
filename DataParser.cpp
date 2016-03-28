#include "DataParser.hpp"

std::vector<std::string> convertPath(std::string path)
{
	std::vector<std::string> vecPath = {};
	if (fn::String::occurencesInString(path, "/") >= 1)
		vecPath = fn::String::split(path, "/");
	else
	{
		if (path != "")
			vecPath.push_back(path);
	}
	return vecPath;
}

std::string reverseConvertPath(std::vector<std::string> path)
{
	std::string strPath = "";
	for (unsigned int i = 0; i < path.size(); i++)
	{
		strPath += path[i];
		if (i != path.size() - 1)
			strPath += "/";
	}
	return strPath;
}


//DataParserNavigator
std::string DataParserNavigator::getCurrentDataObject() {
	return currentDataObject;
}
std::string DataParserNavigator::getCurrentPath() {
	return currentPath;
}
void DataParserNavigator::setCurrentDataObject(std::string object) {
	currentDataObject = object;
	goRoot();
}
void DataParserNavigator::setCurrentDataObject(std::string object, std::string path) {
	currentDataObject = object;
	currentPath = path;
}
void DataParserNavigator::setCurrentPath(std::string path) {
	currentPath = path;
}
void DataParserNavigator::goTo(std::string path) {
	currentPath += "/" + path;
}
void DataParserNavigator::goRoot() {
	currentPath = "";
}
void DataParserNavigator::goBack() {
	if (currentPath != "")
	{
		if (fn::String::split(currentPath, "/").size() > 1)
			currentPath = fn::Vector::join(fn::String::split(currentPath, "/"), "/", 0, fn::String::split(currentPath, "/").size() - 2);
	}
}

//BaseAttribute
BaseAttribute::BaseAttribute(std::string bname, std::string btype, std::string bdata) {
	name = bname;
	dtype = btype;
	data = bdata;
	if (dtype == "str")
		fn::String::replaceStringInPlace(data, "\"", "");
}
std::string BaseAttribute::getName() {
	return name;
}
std::string BaseAttribute::returnData() {
	if (dtype != "str")
		return data;
	else
		return "\"" + data + "\"";
}
int BaseAttribute::getData(int* var) {
	if (dtype == "int")
		return *var = std::stoi(data);
	else
		std::cout << "<Error:DataParser:BaseAttribute>[getData] : " \
		<< name << " is not a <int> BaseAttribute (" << dtype << ")" <<  std::endl;
}
double BaseAttribute::getData(double* var) {
	if (dtype == "float")	
		return *var = std::stod(data);
	else
		std::cout << "<Error:DataParser:BaseAttribute>[getData] : " \
		<< name << " is not a <float> BaseAttribute (" << dtype << ")" << std::endl;
}
std::string BaseAttribute::getData(std::string* var) {
	if (dtype == "str")
	{
		*var = data;
		return data;
	}
	else
		std::cout << "<Error:DataParser:BaseAttribute>[getData] : " \
		<< name << " is not a <str> BaseAttribute (" << dtype << ")" << std::endl;
}
bool BaseAttribute::getData(bool* var) {
	if (dtype == "bool")
	{
		if (data == "True")
			*var = true;
		else
			*var = false;
		return *var;
	}
	else
		std::cout << "<Error:DataParser:BaseAttribute>[getData] : " \
		<< name << " is not a <bool> BaseAttribute (" << dtype << ")" << std::endl;
}
void BaseAttribute::setData(int var) {
	if (dtype == "int")
		data = std::to_string(var);
	else
		std::cout << "<Error:DataParser:BaseAttribute>[setData] : " \
		<< name << " is not a <int> BaseAttribute (" << dtype << ")" << std::endl;
}
void BaseAttribute::setData(double var) {
	if (dtype == "float")
		data = std::to_string(var);
	else
		std::cout << "<Error:DataParser:BaseAttribute>[setData] : " \
		<< name << " is not a <float> BaseAttribute (" << dtype << ")" << std::endl;
}
void BaseAttribute::setData(std::string var) {
	if (dtype == "str")
		data = var;
	else
		std::cout << "<Error:DataParser:BaseAttribute>[setData] : " \
		<< name << " is not a <str> BaseAttribute (" << dtype << ")" << std::endl;
}
void BaseAttribute::setData(bool var) {
	if (dtype == "bool")
	{
		if (var)
			data = "True";
		else
			data = "False";
	}
	else
		std::cout << "<Error:DataParser:BaseAttribute>[setData] : " \
		<< name << " is not a <bool> BaseAttribute (" << dtype << ")" << std::endl;
}
std::string BaseAttribute::getType() {
	return dtype;
}

//ListAttribute
ListAttribute::ListAttribute(std::string id, std::string type) {
	this->listId = id;
	this->dataType = type;
}
unsigned int ListAttribute::getSize() {
	return dataList.size();
}
std::string ListAttribute::getID() {
	return listId;
}
std::string ListAttribute::getType() {
	return dataType;
}
BaseAttribute* ListAttribute::getElement(unsigned int index) {
	if (index < dataList.size())
		return dataList[index];
	else
		std::cout << "<Error:DataParser:ListAttribute> : Can't access index " << index << " of " \
		<< this->getID() << " (Size:" << dataList.size() << ")" << std::endl;
}
void ListAttribute::createElement(std::string element) {
	BaseAttribute* tempElem = new BaseAttribute("None", dataType, element);
	dataList.push_back(tempElem);
}


//ComplexAttribute
ComplexAttribute::ComplexAttribute(std::string attrID) {
	id = attrID;
}
ComplexAttribute::ComplexAttribute(std::string attrID, ComplexAttribute* herit) {
	id = attrID;
	this->heritage(herit);
}
ComplexAttribute::ComplexAttribute(std::string attrID, std::vector<ComplexAttribute*>* multipleHerit) {
	id = attrID;
	for (unsigned int i = 0; i < multipleHerit->size(); i++)
		this->heritage(multipleHerit->at(i));
}
void ComplexAttribute::heritage(ComplexAttribute* heritTarget) {
	for (unsigned int i = 0; i < heritTarget->getAllAttributes().size(); i++)
	{
		BaseAttribute* currentBaseAttr = heritTarget->getAttribute(heritTarget->getAllAttributes()[i]);
		this->createBaseAttribute(currentBaseAttr->getName(), currentBaseAttr->getType(), currentBaseAttr->returnData());
	}
	for (unsigned int i = 0; i < heritTarget->getAllComplex().size(); i++)
	{
		ComplexAttribute* currentCmplxAttr = heritTarget->getComplexAttribute(heritTarget->getAllComplex()[i]);
		this->createComplexAttribute(currentCmplxAttr->getID());
		this->getComplexAttribute(heritTarget->getAllComplex()[i])->heritage(currentCmplxAttr);
	}
}
std::string ComplexAttribute::getID() {
	return id;
}
BaseAttribute* ComplexAttribute::getAttribute(std::string attributeName) {
	if (baseAttributes.find(attributeName) != baseAttributes.end())
		return baseAttributes[attributeName];
	else
		std::cout << "<Error:DataParser:ComplexAttribute>[getAttribute] : Can't find BaseAttribute " << attributeName << " in " << this->getID() << std::endl;
}
ListAttribute* ComplexAttribute::getListAttribute(std::string id) {
	for (std::map<std::string, ListAttribute*>::iterator it = listAttributes.begin(); it != listAttributes.end(); ++it) {
		if (it->second->getID() == id)
			return it->second;
	}
}
ComplexAttribute* ComplexAttribute::getComplexAttribute(std::string id) {
	for (std::map<std::string, ComplexAttribute*>::iterator it = complexAttributes.begin(); it != complexAttributes.end(); ++it) {
		if (it->second->getID() == id)
			return it->second;
	}
	std::cout << "<Error:DataParser:ComplexAttribute>[getComplexAttribute] : Can't find ComplexAttribute " << id << " in " << this->getID() << std::endl;
}
std::vector<std::string> ComplexAttribute::getAllComplex() {
	return complexAttributeList;
}
std::vector<std::string> ComplexAttribute::getAllAttributes() {
	return baseAttributeList;
}
std::vector<std::string> ComplexAttribute::getAllLists() {
	return listAttributeList;
}
bool ComplexAttribute::attributeExists(std::string attributeName) {
	if (baseAttributes.find(attributeName) == baseAttributes.end())
		return false;
	else
		return true;
}
bool ComplexAttribute::complexExists(std::string attributeName) {
	if (complexAttributes.find(attributeName) == complexAttributes.end())
		return false;
	else
		return true;
}
bool ComplexAttribute::listExists(std::string attributeName) {
	if (listAttributes.find(attributeName) == listAttributes.end())
		return false;
	else
		return true;
}
void ComplexAttribute::createBaseAttribute(std::string name, std::string type, std::string data) {
	BaseAttribute* tempAttr = new BaseAttribute(name, type, data);
	baseAttributes[name] = tempAttr;
	baseAttributeList.push_back(name);
}
void ComplexAttribute::pushBaseAttribute(BaseAttribute* attr) {
	baseAttributes[attr->getName()] = attr;
	baseAttributeList.push_back(attr->getName());
}
void ComplexAttribute::createListAttribute(std::string id, std::string type) {
	ListAttribute* tempAttr = new ListAttribute(id, type);
	listAttributes[id] = tempAttr;
	listAttributeList.push_back(id);
}
void ComplexAttribute::pushListAttribute(ListAttribute* attr) {
	listAttributes[attr->getID()] = attr;
	listAttributeList.push_back(attr->getID());
}
void ComplexAttribute::createListItem(std::string listID, std::string value) {
	listAttributes[listID]->createElement(value);
}
void ComplexAttribute::createListGenerator(std::string gtarget, std::string gtype, std::string regex) {
	if (listAttributes.find(gtarget) != listAttributes.end())
	{
		ListGenerator* lGen = new ListGenerator(gtype, regex, listAttributes[gtarget]);
		listGenerators[gtarget] = lGen;
		listGeneratorsList.push_back(gtarget);
	}
	else
		std::cout << "<Error:DataParser:ComplexAttribute>[createListGenerator] : ListAttribute <" << gtarget << "> does not exists" << std::endl;
}
void ComplexAttribute::addBoundToListGenerator(std::string listID, int gstart, int gend) {
	if (listGenerators.find(listID) != listGenerators.end())
		listGenerators[listID]->addBound(gstart, gend);
	else
	{
		if (listAttributes.find(listID) != listAttributes.end())
			std::cout << "<Error:DataParser:ComplexAttribute>[addBoundToListGenerator] : ListAttribute <" << listID << "> has no ListGenerator" << std::endl;
		else
			std::cout << "<Error:DataParser:ComplexAttribute>[addBoundToListGenerator] : ListAttribute <" << listID << "> does not exists" << std::endl;
	}
}
void ComplexAttribute::generateInList(std::string listID) {
	if (listAttributes.find(listID) != listAttributes.end())
	{
		if (listGenerators.find(listID) != listGenerators.end())
		{
			listGenerators[listID]->generate();
			free(listGenerators[listID]);
			listGenerators.erase(listID);
			listGeneratorsList.erase(std::remove(listGeneratorsList.begin(), listGeneratorsList.end(), listID), listGeneratorsList.end());
		}
		else
			std::cout << "<Error:DataParser:ComplexAttribute>[generateInList] : ListAttribute <" << listID << "> has no ListGenerator" << std::endl;
	}
	else
		std::cout << "<Error:DataParser:ComplexAttribute>[generateInList] : ListAttribute <" << listID << "> does not exists" << std::endl;
}
void ComplexAttribute::createComplexAttribute(std::string id) {
	ComplexAttribute* tempAttr = new ComplexAttribute(id);
	complexAttributes[id] = tempAttr;
	complexAttributeList.push_back(id);
}
void ComplexAttribute::pushComplexAttribute(ComplexAttribute* cmplx) {
	complexAttributes[cmplx->getID()] = cmplx;
	complexAttributeList.push_back(cmplx->getID());
}
void ComplexAttribute::writeAttributes(std::ofstream* file, unsigned int depth) {
	for (unsigned int i = 0; i < depth; i++)
		(*file) << "    ";
	(*file) << "@" << this->id << std::endl;
	for (unsigned int i = 0; i < baseAttributeList.size(); i++)
	{
		for (unsigned int j = 0; j < depth + 1; j++)
			(*file) << "    ";
		(*file) << baseAttributeList[i] << ":" << this->getAttribute(baseAttributeList[i])->returnData() << std::endl;
	}
	for (unsigned int i = 0; i < listAttributeList.size(); i++)
	{
		for (unsigned int j = 0; j < depth + 1; j++)
			(*file) << "    ";
		if (listGenerators.find(listAttributeList[i]) != listGenerators.end())
		{
			std::vector<std::pair<int, int>> allBounds = listGenerators[listAttributeList[i]]->getAllBounds();
			(*file) << "?" << listAttributeList[i] << "(" << this->getListAttribute(listAttributeList[i])->getType() \
				<< ")<" << listGenerators[listAttributeList[i]]->getRegex() << ">{";
			for (unsigned int j = 0; j < allBounds.size(); j++)
			{
				(*file) << allBounds[j].first << "-" << allBounds[j].second;
				if (j != allBounds.size() - 1) (*file) << "," << std::endl;
			}
			(*file) << "}:" << std::endl;
		}
		else
			(*file) << "?" << listAttributeList[i] << "(" << this->getListAttribute(listAttributeList[i])->getType() << "):" << std::endl;
		for (unsigned int k = 0; k < this->getListAttribute(listAttributeList[i])->getSize(); k++)
		{
			for (unsigned int l = 0; l < depth + 2; l++)
				(*file) << "    ";		
			(*file) << this->getListAttribute(listAttributeList[i])->getElement(k)->returnData() << std::endl;
		}
	}
	for (unsigned int i = 0; i < complexAttributeList.size(); i++)
		this->getComplexAttribute(complexAttributeList[i])->writeAttributes(file, depth + 1);
	if (depth == 1)
		(*file) << std::endl;
}
void ComplexAttribute::deleteAttribute(std::string id, bool freeMemory) {
	for (int i = 0; i < baseAttributeList.size(); i++)
	{
		if (baseAttributeList[i] == id)
		{
			baseAttributeList.erase(baseAttributeList.begin() + i);
			break;
		}
	}
	typedef std::map<std::string, BaseAttribute*>::iterator it_type;
	it_type itDel = baseAttributes.find(id);
	if (itDel != baseAttributes.end())
	{
		if (freeMemory)
			free(baseAttributes[id]);
		baseAttributes.erase(itDel);
	}
}
void ComplexAttribute::deleteComplexAttribute(std::string id, bool freeMemory) {
	for (int i = 0; i < complexAttributeList.size(); i++)
	{
		if (complexAttributeList[i] == id)
		{
			complexAttributeList.erase(complexAttributeList.begin() + i);
			break;
		}
	}
	typedef std::map<std::string, ComplexAttribute*>::iterator it_type;
	it_type itDel = complexAttributes.find(id);
	if (itDel != complexAttributes.end())
	{
		if (freeMemory)
			free(complexAttributes[id]);
		complexAttributes.erase(itDel);
	}
}
void ComplexAttribute::deleteListAttribute(std::string id, bool freeMemory) {
	for (int i = 0; i < listAttributeList.size(); i++)
	{
		if (listAttributeList[i] == id)
		{
			listAttributeList.erase(listAttributeList.begin() + i);
			break;
		}
	}
	typedef std::map<std::string, ListAttribute*>::iterator it_type;
	it_type itDel = listAttributes.find(id);
	if (itDel != listAttributes.end())
	{
		if (freeMemory)
			free(listAttributes[id]);
		listAttributes.erase(itDel);
	}
}

//ListGenerator
ListGenerator::ListGenerator(std::string gtype, std::string regex, ListAttribute* gtarget) {
	genType = gtype;
	genRegex = regex;
	genTarget = gtarget;
}
std::string ListGenerator::getRegex() {
	return genRegex;
}
void ListGenerator::addBound(int gstart, int gend) {
	std::pair<int, int> bound = { gstart, gend };
	genBounds.push_back(bound);
}
std::vector<std::pair<int, int>> ListGenerator::getAllBounds() {
	return genBounds;
}
void ListGenerator::generate() {
	for (unsigned int i = 0; i < genBounds.size(); i++)
	{
		int start = genBounds[i].first;
		int stop = genBounds[i].second;
		int step = 0;
		if (genBounds[i].first <= genBounds[i].second)
		{
			for (int j = start; j <= stop; j++)
			{
				std::string elemToCreate = std::to_string(j);
				if (genType == "str")
				{
					elemToCreate = genRegex;
					fn::String::replaceStringInPlace(elemToCreate, "%s", std::to_string(j));
					fn::String::replaceStringInPlace(elemToCreate, "\"", "");
				}
				genTarget->createElement(elemToCreate);
			}
		}
		else if (genBounds[i].first > genBounds[i].second)
		{
			for (int j = start; j >= stop; j--)
			{
				std::string elemToCreate = std::to_string(j);
				if (genType == "str")
				{
					elemToCreate = genRegex;
					fn::String::replaceStringInPlace(elemToCreate, "%s", std::to_string(j));
					fn::String::replaceStringInPlace(elemToCreate, "\"", "");
				}
				genTarget->createElement(elemToCreate);
			}
		}
	}
}

//DataObject
DataObject::DataObject(std::string objectname) {
	this->objectName = objectname;
}
std::string DataObject::getName() {
	return objectName;
}
ComplexAttribute* DataObject::getPath(std::vector<std::string> attributePath){
	if (attributePath.size() > 0)
	{
		int pathIndex = 1;
		ComplexAttribute* getToPath;
		getToPath = this->getComplexAttribute({}, attributePath[0]);
		while (pathIndex != attributePath.size())
		{
			getToPath = getToPath->getComplexAttribute(attributePath[pathIndex]);
			pathIndex++;
		}
		return getToPath;
	}
	else
	{
		ComplexAttribute* tempCmplx = new ComplexAttribute("Root");
		return tempCmplx;
	}
}
BaseAttribute* DataObject::getAttribute(std::vector<std::string> attributePath, std::string attributeName) {
	if (attributePath.size() > 0)
		return getPath(attributePath)->getAttribute(attributeName);
	else
	{
		if (baseAttributes.find(attributeName) != baseAttributes.end())
			return baseAttributes[attributeName];
		else
			std::cout << "<Error:DataParser:DataObject>[getAttribute] : Can't find attribute " << attributeName << \
			" inside " << objectName << std::endl;
	}
}
ListAttribute* DataObject::getListAttribute(std::vector<std::string> attributePath, std::string id) {
	if (attributePath.size() == 0)
		return listAttributes[id];
	else
		return getPath(attributePath)->getListAttribute(id);
}
ComplexAttribute* DataObject::getComplexAttribute(std::vector<std::string> attributePath, std::string id) {
	if (attributePath.size() == 0)
	{
		if (complexAttributes.find(id) != complexAttributes.end())
			return complexAttributes[id];
		else if (heritComplexAttributes.find(id) != heritComplexAttributes.end())
			return heritComplexAttributes[id];
		else
			std::cout << "<Error:DataParser:DataObject>[getComplexAttribute] : Can't find " << id << " in " << objectName << "::" << reverseConvertPath(attributePath) << std::endl;
	}
	else
		return getPath(attributePath)->getComplexAttribute(id);
}
std::vector<std::string> DataObject::getAllComplex(std::vector<std::string> attributePath) {
	if (attributePath.size() > 0)
		return getPath(attributePath)->getAllComplex();
	else
		return complexAttributeList;
}
std::vector<std::string> DataObject::getAllAttributes(std::vector<std::string> attributePath) {
	if (attributePath.size() > 0)
		return getPath(attributePath)->getAllAttributes();
	else
		return baseAttributeList;
}
std::vector<std::string> DataObject::getAllLists(std::vector<std::string> attributePath) {
	if (attributePath.size() > 0)
		return getPath(attributePath)->getAllLists();
	else
		return listAttributeList;
}
bool DataObject::attributeExists(std::vector<std::string> attributePath, std::string attributeName) {
	if (attributePath.size() > 0)
		return getPath(attributePath)->attributeExists(attributeName);
	else
	{
		if (baseAttributes.find(attributeName) == baseAttributes.end())
			return false;
		else
			return true;
	}
}
bool DataObject::complexExists(std::vector<std::string> attributePath, std::string attributeName) {
	if (attributePath.size() > 0)
		return getPath(attributePath)->complexExists(attributeName);
	else
	{
		if (complexAttributes.find(attributeName) == complexAttributes.end())
			return false;
		else
			return true;
	}
}
bool DataObject::listExists(std::vector<std::string> attributePath, std::string attributeName) {
	if (attributePath.size() > 0)
		return getPath(attributePath)->listExists(attributeName);
	else
	{
		if (listAttributes.find(attributeName) == listAttributes.end())
			return false;
		else
			return true;
	}
}
void DataObject::createSpecialAttribute(std::string name, std::string type, std::string data) {
	BaseAttribute* tempAttr = new BaseAttribute(name, type, data);
	specialAttributes[name] = tempAttr;
	specialAttributeList.push_back(name);
}
void DataObject::createBaseAttribute(std::vector<std::string> attributePath, std::string name, std::string type, std::string data) {
	BaseAttribute* tempAttr = new BaseAttribute(name, type, data);
	if (attributePath.size() == 0)
	{
		baseAttributes[name] = tempAttr;
		baseAttributeList.push_back(name);
	}
	else
		getPath(attributePath)->pushBaseAttribute(tempAttr);
}
void DataObject::pushBaseAttribute(std::vector<std::string> attributePath, BaseAttribute* attr) {
	if (attributePath.size() == 0)
	{
		baseAttributes[attr->getName()] = attr;
		baseAttributeList.push_back(attr->getName());
	}
	else
		getPath(attributePath)->pushBaseAttribute(attr);
}
void DataObject::createListAttribute(std::vector<std::string> attributePath, std::string id, std::string type) {
	ListAttribute* tempAttr = new ListAttribute(id, type);
	if (attributePath.size() == 0)
	{
		listAttributes[id] = tempAttr;
		listAttributeList.push_back(id);
	}
	else
		getPath(attributePath)->pushListAttribute(tempAttr);
}
void DataObject::pushListAttribute(std::vector<std::string> attributePath, ListAttribute* attr) {
	if (attributePath.size() == 0)
	{
		listAttributes[attr->getID()] = attr;
		listAttributeList.push_back(attr->getID());
	}
	else
		getPath(attributePath)->pushListAttribute(attr);
}
void DataObject::createListItem(std::vector<std::string> attributePath, std::string listID, std::string value) {
	if (attributePath.size() == 0)
	{
		listAttributes[listID]->createElement(value);
	}
	else
		getPath(attributePath)->createListItem(listID, value);
}
void DataObject::createListGenerator(std::vector<std::string> attributePath, std::string gtarget, std::string gtype, std::string regex) {
	if (attributePath.size() == 0)
	{
		if (listAttributes.find(gtarget) != listAttributes.end())
		{
			ListGenerator* lGen = new ListGenerator(gtype, regex, listAttributes[gtarget]);
			listGenerators[gtarget] = lGen;
			listGeneratorsList.push_back(gtarget);
		}
		else
			std::cout << "<Error:DataParser:DataObject>[createListGenerator] : ListAttribute <" << gtarget << "> does not exists" << std::endl;
	}
	else
		getPath(attributePath)->createListGenerator(gtarget, gtype, regex);
}
void DataObject::addBoundToListGenerator(std::vector<std::string> attributePath, std::string listID, int gstart, int gend) {
	if (attributePath.size() == 0)
	{
		if (listGenerators.find(listID) != listGenerators.end())
			listGenerators[listID]->addBound(gstart, gend);
		else
		{
			if (listAttributes.find(listID) != listAttributes.end())
				std::cout << "<Error:DataParser:DataObject>[addBoundToListGenerator] : ListAttribute <" << listID << "> has no ListGenerator" << std::endl;
			else
				std::cout << "<Error:DataParser:DataObject>[addBoundToListGenerator] : ListAttribute <" << listID << "> does not exists" << std::endl;
		}
	}
	else
		getPath(attributePath)->addBoundToListGenerator(listID, gstart, gend);
}
void DataObject::generateInList(std::vector<std::string> attributePath, std::string listID) {
	if (attributePath.size() == 0)
	{
		if (listAttributes.find(listID) != listAttributes.end())
		{
			if (listGenerators.find(listID) != listGenerators.end())
			{
				listGenerators[listID]->generate();
				free(listGenerators[listID]);
				listGenerators.erase(listID);
				listGeneratorsList.erase(std::remove(listGeneratorsList.begin(), listGeneratorsList.end(), listID), listGeneratorsList.end());
			}
			else
				std::cout << "<Error:DataParser:ComplexAttribute>[generateInList] : ListAttribute <" << listID << "> has no ListGenerator" << std::endl;
		}
		else
			std::cout << "<Error:DataParser:ComplexAttribute>[generateInList] : ListAttribute <" << listID << "> does not exists" << std::endl;
	}
	else
		getPath(attributePath)->generateInList(listID);
}
void DataObject::createComplexAttribute(std::vector<std::string> attributePath, std::string id) {
	if (attributePath.size() == 0)
	{
		ComplexAttribute* tempAttr = new ComplexAttribute(id);
		complexAttributes[id] = tempAttr;
		complexAttributeList.push_back(id);
	}
	else if (attributePath.size() > 0)
	{
		ComplexAttribute* tempAttr = new ComplexAttribute(id);
		getPath(attributePath)->pushComplexAttribute(tempAttr);
	}
}
void DataObject::pushComplexAttribute(std::vector<std::string> attributePath, ComplexAttribute* cmplx) {
	if (attributePath.size() == 0)
	{
		complexAttributes[cmplx->getID()] = cmplx;
		complexAttributeList.push_back(cmplx->getID());
	}
	else if (attributePath.size() > 0)
		getPath(attributePath)->pushComplexAttribute(cmplx);
}

void DataObject::createHeritComplexAttribute(std::string id) {
	ComplexAttribute* tempAttr = new ComplexAttribute(id);
	heritComplexAttributes[id] = tempAttr;
	heritComplexAttributeList.push_back(id);
}

void DataObject::pushHeritComplexAttribute(ComplexAttribute* cmplx) {
	complexAttributes[cmplx->getID()] = cmplx;
	complexAttributeList.push_back(cmplx->getID());
}
void DataObject::writeAttributes(std::ofstream* file) {
	(*file) << objectName << ":" << std::endl;
	for (unsigned int i = 0; i < this->getAllAttributes({}).size(); i++)
	{
		std::string attributeName = this->getAllAttributes({})[i];
		std::string attributeValue = this->getAttribute({}, attributeName)->returnData();
		(*file) << "    ";
		(*file) << attributeName << ":" << attributeValue << std::endl;
	}
	for (unsigned int i = 0; i < this->getAllLists({}).size(); i++)
	{
		ListAttribute* cList = this->getListAttribute(convertPath(""), this->getAllLists({})[i]);
		(*file) << "    ";
		(*file) << "?" << this->getAllLists({})[i] << "(" << cList->getType() << "):" << std::endl;
		for (unsigned int k = 0; k < cList->getSize(); k++)
		{
			(*file) << "        ";
			(*file) << cList->getElement(k)->returnData() << std::endl;
		}
		(*file) << "    ";
	}
	std::string currentPath = "";
	for (unsigned int i = 0; i < this->getAllComplex(convertPath(currentPath)).size(); i++)
	{
		this->getComplexAttribute({}, this->getAllComplex({})[i])->writeAttributes(file);
	}
	(*file) << std::endl;
}
void DataObject::deleteAttribute(std::vector<std::string> attributePath, std::string id, bool freeMemory) {
	if (attributePath.size() == 0)
	{
		for (int i = 0; i < baseAttributeList.size(); i++)
		{
			if (baseAttributeList[i] == id)
			{
				baseAttributeList.erase(baseAttributeList.begin() + i);
				break;
			}
		}
		typedef std::map<std::string, BaseAttribute*>::iterator it_type;
		it_type itDel = baseAttributes.find(id);
		if (itDel != baseAttributes.end())
		{
			if (freeMemory)
				free(baseAttributes[id]);
			baseAttributes.erase(itDel);
		}	
	}
	else if (attributePath.size() > 0)
	{
		getPath(attributePath)->deleteAttribute(id, freeMemory);
	}
}
void DataObject::deleteComplexAttribute(std::vector<std::string> attributePath, std::string id, bool freeMemory) {
	if (attributePath.size() == 0)
	{
		for (int i = 0; i < complexAttributeList.size(); i++)
		{
			if (complexAttributeList[i] == id)
			{
				complexAttributeList.erase(complexAttributeList.begin() + i);
				break;
			}
		}
		typedef std::map<std::string, ComplexAttribute*>::iterator it_type;
		it_type itDel = complexAttributes.find(id);
		if (itDel != complexAttributes.end())
		{
			if (freeMemory)
				free(complexAttributes[id]);
			complexAttributes.erase(itDel);
		}
	}
	else if (attributePath.size() > 0)
	{
		getPath(attributePath)->deleteComplexAttribute(id, freeMemory);
	}
}
void DataObject::deleteListAttribute(std::vector<std::string> attributePath, std::string id, bool freeMemory) {
	if (attributePath.size() == 0)
	{
		for (int i = 0; i < listAttributeList.size(); i++)
		{
			if (listAttributeList[i] == id)
			{
				listAttributeList.erase(listAttributeList.begin() + i);
				break;
			}
		}
		typedef std::map<std::string, ListAttribute*>::iterator it_type;
		it_type itDel = listAttributes.find(id);
		if (itDel != listAttributes.end())
		{
			if (freeMemory)
				free(listAttributes[id]);
			listAttributes.erase(itDel);
		}
	}
	else if (attributePath.size() > 0)
	{
		getPath(attributePath)->deleteListAttribute(id, freeMemory);
	}
}


//DataParser
DataParser::DataParser() {

}
void DataParser::hookNavigator(DataParserNavigator* dpNav) {
	this->dpNav = dpNav;
}
DataParserNavigator* DataParser::accessNavigator() {
	return this->dpNav;
}
bool DataParser::checkNavigator() {
	return dpNav != NULL;
}
DataObject* DataParser::accessDataObject(std::string name) {
	if (objectMap.find(name) != objectMap.end())
		return objectMap[name];
	else
		std::cout << "<Error:DataParser:DataParser>[accessDataObject] : Can't find \"" << name << "\" DataObject" <<std::endl;
}
void DataParser::createFlag(std::string flag) {
	flagList.push_back(flag);
}
bool DataParser::hasFlag(std::string flagName) {
	return std::find(flagList.begin(), flagList.end(), flagName) != flagList.end();
}
unsigned int DataParser::getAmountOfFlags() {
	return flagList.size();
}
std::string DataParser::getFlagAtIndex(int index) {
	return flagList[index];
}
void DataParser::createDataObject(std::string objectName) {
	DataObject* tempObject = new DataObject(objectName);
	objectMap[objectName] = tempObject;
	objectList.push_back(objectName);
	if (checkNavigator()) dpNav->setCurrentDataObject(objectName);
}
void DataParser::pushDataObject(DataObject* object) {
	objectMap[object->getName()] = object;
	objectList.push_back(object->getName());
	if (checkNavigator()) dpNav->setCurrentDataObject(object->getName());
}
void DataParser::createSpecialAttribute(std::string object, std::string name, std::string type, std::string data) {
	this->accessDataObject(object)->createSpecialAttribute(name, type, data);
}
void DataParser::createSpecialAttribute(std::string name, std::string type, std::string data) {
	if (checkNavigator()) this->accessDataObject(dpNav->getCurrentDataObject())->createSpecialAttribute(name, type, data);
}
void DataParser::createBaseAttribute(std::string object, std::string attributePath, std::string name, std::string data) {
	this->accessDataObject(object)->pushBaseAttribute(convertPath(attributePath), new BaseAttribute(name, "str", data));
}
void DataParser::createBaseAttribute(std::string name, std::string data) {
	if (checkNavigator()) this->accessDataObject(dpNav->getCurrentDataObject())->pushBaseAttribute(convertPath(dpNav->getCurrentPath()), new BaseAttribute(name, "str", data));
}
void DataParser::createBaseAttribute(std::string object, std::string attributePath, std::string name, bool data) {
	this->accessDataObject(object)->pushBaseAttribute(convertPath(attributePath), new BaseAttribute(name, "int", data?"True":"False"));
}
void DataParser::createBaseAttribute(std::string name, bool data) {
	if (checkNavigator()) this->accessDataObject(dpNav->getCurrentDataObject())->pushBaseAttribute(convertPath(dpNav->getCurrentPath()), new BaseAttribute(name, "bool", data ? "True" : "False"));
}
void DataParser::createBaseAttribute(std::string object, std::string attributePath, std::string name, int data) {
	this->accessDataObject(object)->pushBaseAttribute(convertPath(attributePath), new BaseAttribute(name, "int", std::to_string(data)));
}
void DataParser::createBaseAttribute(std::string name, int data) {
	if (checkNavigator()) this->accessDataObject(dpNav->getCurrentDataObject())->pushBaseAttribute(convertPath(dpNav->getCurrentPath()), new BaseAttribute(name, "int", std::to_string(data)));
}
void DataParser::createBaseAttribute(std::string object, std::string attributePath, std::string name, double data) {
	this->accessDataObject(object)->pushBaseAttribute(convertPath(attributePath), new BaseAttribute(name, "float", std::to_string(data)));
}
void DataParser::createBaseAttribute(std::string name, double data) {
	if (checkNavigator()) this->accessDataObject(dpNav->getCurrentDataObject())->pushBaseAttribute(convertPath(dpNav->getCurrentPath()), new BaseAttribute(name, "float", std::to_string(data)));
}
void DataParser::pushBaseAttribute(std::string object, std::string attributePath, BaseAttribute* attr) {
	this->accessDataObject(object)->pushBaseAttribute(convertPath(attributePath), attr);
}
void DataParser::pushBaseAttribute(BaseAttribute* attr) {
	if (checkNavigator()) this->accessDataObject(dpNav->getCurrentDataObject())->pushBaseAttribute(convertPath(dpNav->getCurrentPath()), attr);
}
void DataParser::createListAttribute(std::string object, std::string attributePath, std::string id, std::string type) {
	this->accessDataObject(object)->createListAttribute(convertPath(attributePath), id, type);
}
void DataParser::createListAttribute(std::string id, std::string type) {
	if (checkNavigator()) this->accessDataObject(dpNav->getCurrentDataObject())->createListAttribute(convertPath(dpNav->getCurrentPath()), id, type);
}
void DataParser::pushListAttribute(std::string object, std::string attributePath, ListAttribute* attr) {
	this->accessDataObject(object)->pushListAttribute(convertPath(attributePath), attr);
}
void DataParser::pushListAttribute(ListAttribute* attr) {
	if (checkNavigator()) this->accessDataObject(dpNav->getCurrentDataObject())->pushListAttribute(convertPath(dpNav->getCurrentPath()), attr);
}
void DataParser::createListItem(std::string object, std::string attributePath, std::string listID, std::string value) {
	this->accessDataObject(object)->createListItem(convertPath(attributePath), listID, value);
}
void DataParser::createListItem(std::string listID, std::string value) {
	if (checkNavigator()) this->accessDataObject(dpNav->getCurrentDataObject())->createListItem(convertPath(dpNav->getCurrentPath()), listID, value);
}
void DataParser::createListGenerator(std::string object, std::string attributePath, std::string gtarget, std::string gtype, std::string regex) {
	this->accessDataObject(object)->createListGenerator(convertPath(attributePath), gtarget, gtype, regex);
}
void DataParser::createListGenerator(std::string gtarget, std::string gtype, std::string regex) {
	if (checkNavigator()) this->accessDataObject(dpNav->getCurrentDataObject())->createListGenerator(convertPath(dpNav->getCurrentPath()), gtarget, gtype, regex);
}
void DataParser::addBoundToListGenerator(std::string object, std::string attributePath, std::string listID, int gstart, int gend) {
	this->accessDataObject(object)->addBoundToListGenerator(convertPath(attributePath), listID, gstart, gend);
}
void DataParser::addBoundToListGenerator(std::string listID, int gstart, int gend) {
	if (checkNavigator()) this->accessDataObject(dpNav->getCurrentDataObject())->addBoundToListGenerator(convertPath(dpNav->getCurrentPath()), listID, gstart, gend);
}
void DataParser::generateInList(std::string object, std::string attributePath, std::string listID) {
	this->accessDataObject(object)->generateInList(convertPath(attributePath), listID);
}
void DataParser::generateInList(std::string listID) {
	if (checkNavigator()) this->accessDataObject(dpNav->getCurrentDataObject())->generateInList(convertPath(dpNav->getCurrentPath()), listID);
}
void DataParser::createComplexAttribute(std::string object, std::string attributePath, std::string id) {
	this->accessDataObject(object)->createComplexAttribute(convertPath(attributePath), id);
}
void DataParser::createComplexAttribute(std::string id) {
	if (checkNavigator()) this->accessDataObject(dpNav->getCurrentDataObject())->createComplexAttribute(convertPath(dpNav->getCurrentPath()), id);
	if (checkNavigator()) dpNav->goTo(id);
}
void DataParser::pushComplexAttribute(std::string object, std::string attributePath, ComplexAttribute* cmplx) {
	this->accessDataObject(object)->pushComplexAttribute(convertPath(attributePath), cmplx);
}
void DataParser::pushComplexAttribute(ComplexAttribute* cmplx) {
	if (checkNavigator()) this->accessDataObject(dpNav->getCurrentDataObject())->pushComplexAttribute(convertPath(dpNav->getCurrentPath()), cmplx);
	if (checkNavigator()) dpNav->goTo(cmplx->getID());
}
void DataParser::createHeritComplexAttribute(std::string object, std::string id) {
	this->accessDataObject(object)->createHeritComplexAttribute(id);
}
void DataParser::createHeritComplexAttribute(std::string id) {
	if (checkNavigator()) this->accessDataObject(dpNav->getCurrentDataObject())->createHeritComplexAttribute(id);
	if (checkNavigator()) dpNav->goTo(id);
}
void DataParser::pushHeritComplexAttribute(std::string object, ComplexAttribute* cmplx) {
	this->accessDataObject(object)->pushHeritComplexAttribute(cmplx);
}
void DataParser::pushHeritComplexAttribute(ComplexAttribute* cmplx) {
	if (checkNavigator()) this->accessDataObject(dpNav->getCurrentDataObject())->pushHeritComplexAttribute(cmplx);
	if (checkNavigator()) dpNav->goTo(cmplx->getID());
}
unsigned int DataParser::getListSize(std::string object, std::string attributePath, std::string listName) {
	return this->accessDataObject(object)->getListAttribute(convertPath(attributePath), listName)->getSize();
}
unsigned int DataParser::getListSize(std::string listName) {
	if (checkNavigator()) return this->accessDataObject(dpNav->getCurrentDataObject())->getListAttribute(convertPath(dpNav->getCurrentPath()), listName)->getSize();
}
std::vector<std::string> DataParser::getAllComplex(std::string object, std::string attributePath) {
	return this->accessDataObject(object)->getAllComplex(convertPath(attributePath));
}
std::vector<std::string> DataParser::getAllComplex() {
	if (checkNavigator()) return this->accessDataObject(dpNav->getCurrentDataObject())->getAllComplex(convertPath(dpNav->getCurrentPath()));
}
std::vector<std::string> DataParser::getAllAttributes(std::string object, std::string attributePath) {
	return this->accessDataObject(object)->getAllAttributes(convertPath(attributePath));
}
std::vector<std::string> DataParser::getAllAttributes() {
	if (checkNavigator()) return this->accessDataObject(dpNav->getCurrentDataObject())->getAllAttributes(convertPath(dpNav->getCurrentPath()));
}
std::vector<std::string> DataParser::getAllLists(std::string object, std::string attributePath) {
	return this->accessDataObject(object)->getAllLists(convertPath(attributePath));
}
std::vector<std::string> DataParser::getAllLists() {
	if (checkNavigator()) return this->accessDataObject(dpNav->getCurrentDataObject())->getAllLists(convertPath(dpNav->getCurrentPath()));
}
bool DataParser::attributeExists(std::string object, std::string attributePath, std::string attributeName) {
	return this->accessDataObject(object)->attributeExists(convertPath(attributePath), attributeName);
}
bool DataParser::attributeExists(std::string attributeName) {
	if (checkNavigator()) return this->accessDataObject(dpNav->getCurrentDataObject())->attributeExists(convertPath(dpNav->getCurrentPath()), attributeName);
}
bool DataParser::complexExists(std::string object, std::string attributePath, std::string attributeName) {
	return this->accessDataObject(object)->complexExists(convertPath(attributePath), attributeName);
}
bool DataParser::complexExists(std::string attributeName) {
	if (checkNavigator()) return this->accessDataObject(dpNav->getCurrentDataObject())->complexExists(convertPath(dpNav->getCurrentPath()), attributeName);
}
bool DataParser::listExists(std::string object, std::string attributePath, std::string attributeName) {
	return this->accessDataObject(object)->listExists(convertPath(attributePath), attributeName);
}
bool DataParser::listExists(std::string attributeName) {
	if (checkNavigator()) return this->accessDataObject(dpNav->getCurrentDataObject())->listExists(convertPath(dpNav->getCurrentPath()), attributeName);
}
BaseAttribute* DataParser::getAttribute(std::string object, std::string attributePath, std::string attributeName) {
	return this->accessDataObject(object)->getAttribute(convertPath(attributePath), attributeName);
}
BaseAttribute* DataParser::getAttribute(std::string attributeName) {
	if (checkNavigator()) return this->accessDataObject(dpNav->getCurrentDataObject())->getAttribute(convertPath(dpNav->getCurrentPath()), attributeName);
}
BaseAttribute* DataParser::getListItem(std::string object, std::string attributePath, std::string listName, int listItem) {
	return this->accessDataObject(object)->getListAttribute(convertPath(attributePath), listName)->getElement(listItem);
}
BaseAttribute* DataParser::getListItem(std::string listName, int listItem) {
	if (checkNavigator()) return this->accessDataObject(dpNav->getCurrentDataObject())->getListAttribute(convertPath(dpNav->getCurrentPath()), listName)->getElement(listItem);
}
ComplexAttribute* DataParser::getComplexAttribute(std::string object, std::string attributePath, std::string id) {
	return this->accessDataObject(object)->getComplexAttribute(convertPath(attributePath), id);
}
ComplexAttribute* DataParser::getComplexAttribute(std::string id) {
	if (checkNavigator()) return this->accessDataObject(dpNav->getCurrentDataObject())->getComplexAttribute(convertPath(dpNav->getCurrentPath()), id);
}
ListAttribute* DataParser::getListAttribute(std::string object, std::string attributePath, std::string listName) {
	return this->accessDataObject(object)->getListAttribute(convertPath(attributePath), listName);
}
ListAttribute* DataParser::getListAttribute(std::string listName) {
	if (checkNavigator()) return this->accessDataObject(dpNav->getCurrentDataObject())->getListAttribute(convertPath(dpNav->getCurrentPath()), listName);
}
std::string DataParser::getVarType(std::string line) {
	std::string attributeType;
	std::vector<std::string> boolType = { "True", "False" };
	if (fn::Vector::isInList(line, boolType))
		attributeType = "bool";
	else if (line.substr(0, 1) == "\"" && line.substr(line.size() - 1, 1) == "\"")
		attributeType = "str";
	else if (fn::String::isStringFloat(line))
		attributeType = "float";
	else if (fn::String::isStringInt(line))
		attributeType = "int";
	else
		attributeType = "unknown";
	return attributeType;
}
void DataParser::parseFile(std::string filename, bool verbose) {
	useFile.open(filename);
	std::string currentLine;
	std::string parsedLine;
	std::vector<std::string> addPath = {};
	unsigned int currentIndent;
	int currentIndex = 1;
	std::string curCat = "None";
	std::string curList = "None";
	int curListIndent = 0;
	bool errorInFile = false;
	if (useFile.is_open())
	{
		if (verbose) std::cout << "Start Parsing File : " << filename << std::endl;
		while (getline(useFile, currentLine))
		{
			parsedLine = currentLine;
			currentIndent = fn::String::occurencesInString(parsedLine, "    ");
			while (currentIndent < addPath.size() + 1 && addPath.size() > 0)
			{
				addPath.pop_back();
			}
			if (curList != "None")
			{
				if (currentIndent != curListIndent + 1)
				{
					curList = "None";
				}
			}
			fn::String::replaceStringInPlace(parsedLine, "    ", "");
			if (parsedLine != "" && currentIndent == 0)
			{
				if (parsedLine.substr(parsedLine.size() - 1, 1) == ":")
				{
					if (verbose) std::cout << "    Create new DataObject : " << parsedLine.substr(0, parsedLine.size() - 1) << std::endl;
					curCat = parsedLine.substr(0, parsedLine.size() - 1);
					this->createDataObject(curCat);
				}
				else if (parsedLine.substr(0, 6) == "Define" && parsedLine.substr(parsedLine.size() - 1, 1) == ";")
				{
					std::vector<std::string> defineInstructions = fn::String::split(parsedLine, " ");
					if (defineInstructions[1] == "Flag")
					{
						std::string newFlag = defineInstructions[2];
						fn::String::replaceStringInPlace(newFlag, "(", "");
						fn::String::replaceStringInPlace(newFlag, ");", "");
						flagList.push_back(newFlag);
						if (verbose) std::cout << "    Define New Flag : " << newFlag << std::endl;
					}
				}
			}
			else if (curCat != "None" && parsedLine != "" && currentIndent > 0)
			{
				std::vector<std::string> symbolExclusion = { "@", "?" ,"\"", "&", "{"};
				for (unsigned int p = 0; p <= currentIndent; p++)
				{
					if (verbose) std::cout << "    ";
				}
				if (!fn::Vector::isInList(parsedLine.substr(0, 1), symbolExclusion) && fn::String::occurencesInString(parsedLine,":"))
				{
					std::string attributeName = fn::String::split(parsedLine, ":")[0];
					std::string attributeValue = fn::Vector::join(fn::String::split(parsedLine, ":"), ":", 1, 0);
					std::string attributeType = getVarType(attributeValue);
					objectMap[curCat]->createBaseAttribute(addPath, attributeName, attributeType, attributeValue);
					std::string pushIndicator;
					if (addPath.size() == 0) {pushIndicator = curCat+":Root";}
					else {pushIndicator = addPath[addPath.size() - 1];}
					if (verbose) std::cout << "Create base attribute " << attributeName << "(" << attributeValue << ") inside " << pushIndicator << " (Type:" << attributeType << ")" << std::endl;
				}
				else if (parsedLine.substr(0, 1) == "&" && currentIndent == 1)
				{
					std::string specialElement = parsedLine.substr(1);
					std::string attributeName = fn::String::split(specialElement, ":")[0];
					std::string attributeValue = fn::String::split(specialElement, ":")[1];
					std::string attributeType = getVarType(attributeValue);
					objectMap[curCat]->createSpecialAttribute(attributeName, attributeType, attributeValue);
					if (verbose) std::cout << "Create special attribute &" << attributeName << " inside " << curCat << std::endl;
				}
				else if (parsedLine.substr(0, 1) == "@")
				{
					std::string complexElementID = parsedLine.substr(1);
					std::string complexToHeritID;
					std::vector<std::string> complexToHeritIDList;
					std::vector<ComplexAttribute*> complexToHerit;
					if (fn::String::occurencesInString(complexElementID, ":") == 1 && fn::String::split(complexElementID, ":").size() == 2)
					{
						complexToHeritID = fn::String::replaceString(fn::String::split(complexElementID, ":")[1], " ", "");
						complexElementID = fn::String::split(complexElementID, ":")[0];
						complexToHeritIDList = fn::String::split(complexToHeritID, ",");

						for (unsigned int i = 0; i < complexToHeritIDList.size(); i++)
						{
							complexToHerit.push_back(objectMap[curCat]->getComplexAttribute(convertPath(""), complexToHeritIDList[i]));
						}
					}
					objectMap[curCat]->createComplexAttribute(addPath, complexElementID);
					if (verbose) std::cout << "Create cmplx attribute @" << complexElementID << " inside " << curCat + ":" \
						+ objectMap[curCat]->getPath(addPath)->getID() << " (&" << \
						objectMap[curCat]->getPath(addPath) << ")" << std::endl;
					for (unsigned int i = 0; i < complexToHerit.size(); i++)
					{
						for (unsigned int p = 0; p <= currentIndent + 1; p++)
						{
							if (verbose) std::cout << "    ";
						}
						if (verbose) std::cout << "{Herit from : " << complexToHeritIDList[i] << "}" << std::endl;
						objectMap[curCat]->getComplexAttribute(addPath, complexElementID)->heritage(complexToHerit[i]);
					}
						
					addPath.push_back(complexElementID);
				}
				else if (parsedLine.substr(0, 3) == "{@}")
				{
					std::string complexElementID = parsedLine.substr(3);
					objectMap[curCat]->createHeritComplexAttribute(complexElementID);
					if (verbose) std::cout << "Create h_cmplx attribute {@}" << complexElementID << " inside " << curCat + ":" \
						+ objectMap[curCat]->getPath(addPath)->getID() << " (&" << \
						objectMap[curCat]->getPath(addPath) << ")" << std::endl;
					addPath.push_back(complexElementID);
				}
				else if (parsedLine.substr(0, 1) == "?")
				{
					std::string listElementID = parsedLine.substr(1);
					listElementID = fn::String::split(listElementID, "(")[0];
					std::string listElementType = parsedLine.substr(1);
					listElementType = fn::String::split(fn::String::split(listElementType, ")")[0], "(")[1];
					objectMap[curCat]->createListAttribute(addPath, listElementID, listElementType);
					curList = listElementID;
					curListIndent = currentIndent;
					if (verbose) std::cout << "Create list attribute ?" << curList << " inside " << curCat + ":" + objectMap[curCat]->getPath(addPath)->getID() << std::endl;
					if (fn::String::occurencesInString(fn::String::split(parsedLine.substr(1), ")")[1], "<") == 1)
					{
						std::string generatorRegex = fn::String::split(parsedLine.substr(1), "<")[1];
						std::string genIt = fn::String::split(generatorRegex, "{")[1];
						genIt = fn::String::split(genIt, "}")[0];
						generatorRegex = fn::String::split(generatorRegex, ">")[0];
						for (unsigned int p = 0; p <= currentIndent+1; p++)
						{
							if (verbose) std::cout << "    ";
						}
						if (verbose) std::cout << "Generator of type " << listElementType << " hooked to " << listElementID << " with pattern " << generatorRegex << " and iterator " << genIt << std::endl;
						ListGenerator gen(listElementType, generatorRegex, objectMap[curCat]->getListAttribute(addPath,listElementID));
						std::vector<std::string> listOfBounds;
						listOfBounds = fn::String::split(genIt, ",");
						for (unsigned int i = 0; i < listOfBounds.size(); i++)
						{
							if (fn::String::occurencesInString(listOfBounds[i], "-") == 1)
							{
								int startBound = stoi(fn::String::split(listOfBounds[i], "-")[0]);
								int endBound = stoi(fn::String::split(listOfBounds[i], "-")[1]);
								gen.addBound(startBound, endBound);
							}
							else
								gen.addBound(stoi(listOfBounds[i]), stoi(listOfBounds[i]));
						}
						gen.generate();
					}
				}
				else if (curList != "None")
				{
					std::string attributeValue = parsedLine;
					std::string attributeType = getVarType(attributeValue);
					if (attributeType == objectMap[curCat]->getListAttribute(addPath, curList)->getType())
					{
						objectMap[curCat]->getListAttribute(addPath, curList)->createElement(attributeValue);
						if (verbose) std::cout << "Push element " << attributeValue << " inside " << curList << std::endl;
					}
					else
					{
						if (verbose) std::cout << "Error ! Can't push " << attributeType << " inside " << curList << " which is ";
						if (verbose) std::cout << objectMap[curCat]->getListAttribute(addPath, curList)->getType() << " type " << std::endl;
					}
				}
			}
			currentIndex++;
		}
		useFile.close();
		if (verbose) std::cout << "Parsed over.." << std::endl;
	}
	else
		std::cout << "<Error:DataParser:DataParser>[parseFile] : Can't open " << filename << ". File does not exists" << std::endl;
}
void DataParser::writeFile(std::string filename, bool verbose) {
	outFile.open(filename);
	std::vector<DataObject*> orderedDataObjects;
	if (verbose) std::cout << "Displaying data table" << std::endl;
	unsigned int currentDeepness = 1;
	for (unsigned int i = 0; i < this->getAmountOfFlags(); i++)
		outFile << "Define Flag (" << this->getFlagAtIndex(i) << ");" << std::endl;
	outFile << std::endl;
	for (unsigned int objIt = 0; objIt < objectList.size(); objIt++) {
		objectMap[objectList[objIt]]->writeAttributes(&outFile);
	}
	outFile.close();
}
std::vector<std::string> DataParser::getAllDataObjects() {
	return objectList;
}