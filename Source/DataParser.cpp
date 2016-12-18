//Author : Sygmei
//Key : 976938ef7d46c286a2027d73f3a99467bcfa8ff0c1e10bd0016139744ef5404f4eb4d069709f9831f6de74a094944bf0f1c5bf89109e9855290336a66420376f

#include "DataParser.hpp"

namespace mse
{
	namespace Data
	{
		std::vector<std::string> convertPath(std::string path)
		{
			std::vector<std::string> vecPath = {};
			if (Functions::String::occurencesInString(path, "/") >= 1)
				vecPath = Functions::String::split(path, "/");
			else
			{
				if (path != "")
					vecPath.push_back(path);
			}
			return vecPath;
		}

		std::string getDefaultValueForType(std::string type)
		{
			std::string value = "";
			if (type == "string") value = "";
			if (type == "int") value = "0";
			if (type == "float") value = "0.0";
			if (type == "bool") value = "False";
			return value;
		}

		std::string getVarType(std::string var)
		{
			std::string attributeType;
			std::vector<std::string> boolType = { "True", "False" };
			if (Functions::Vector::isInList(var, boolType))
				attributeType = "bool";
			else if (var.substr(0, 1) == "\"" && var.substr(var.size() - 1, 1) == "\"")
				attributeType = "string";
			else if (Functions::String::isStringFloat(var))
				attributeType = "float";
			else if (Functions::String::isStringInt(var))
				attributeType = "int";
			else
				attributeType = "unknown";
			return attributeType;
		}

		std::string Path()
		{
			return "";
		}

		std::string Path(std::string cPath)
		{
			std::cout << "Returns Path : " << cPath << std::endl;
			if (cPath.size() > 0 && Functions::String::extract(cPath, cPath.size() - 1, 0) == "/")
				cPath = Functions::String::extract(cPath, 0, 1);
			return cPath;
		}

		std::string Path(std::vector<std::string> path)
		{
			std::string strPath = "";
			for (unsigned int i = 0; i < path.size(); i++) {
				strPath += path[i];
				if (i != path.size() - 1)
					strPath += "/";
			}
			return strPath;
		}


		//DataParserNavigator
		std::string DataParserNavigator::getFullPath()
		{
			return currentRootAttribute + ((currentPath != "") ? "/" : "") + currentPath;
		}
		std::string DataParserNavigator::getCurrentRootAttribute() {
			return currentRootAttribute;
		}
		std::string DataParserNavigator::getCurrentPath() {
			return currentPath;
		}
		void DataParserNavigator::setCurrentRootAttribute(std::string object) {
			currentRootAttribute = object;
			goRoot();
		}
		void DataParserNavigator::setCurrentRootAttribute(std::string object, std::string path) {
			currentRootAttribute = object;
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
				if (Functions::String::split(currentPath, "/").size() > 1)
				{
					std::vector<std::string> splittedPath = Functions::String::split(currentPath, "/");
					currentPath = Functions::Vector::join(splittedPath, "/", 0, splittedPath.size() - 2);
				}

			}
		}

		//Attribute
		Attribute::Attribute(ContainerAttribute* parent, std::string id, Types::AttributeType type)
		{
			this->id = id;
			this->type = type;
			this->parent = parent;
		}
		void Attribute::removeParent(ContainerAttribute* currentParent)
		{
			if (currentParent == parent) {
				parent = nullptr;
			}
		}
		void Attribute::setAnnotation(std::string annotation)
		{
			this->annotation = annotation;
		}
		std::string Attribute::getAnnotation()
		{
			return annotation;
		}
		std::string Attribute::getID()
		{
			return id;
		}
		Types::AttributeType Attribute::getType()
		{
			return type;
		}
		ContainerAttribute* Attribute::getParent()
		{
			return parent;
		}
		void Attribute::setParent(ContainerAttribute* parent)
		{
			if (this->parent != nullptr) {
				this->parent = parent;
			}
			else {
				std::cout << "<Error:DataParser:Attribute>[setParent] : Attribute " << getNodePath() << " already has a parent" << std::endl;
			}
		}

		std::string Attribute::getNodePath()
		{
			std::vector<std::string> parentChain;
			ContainerAttribute* currentParent = this->getParent();
			while (currentParent != nullptr) {
				parentChain.push_back(currentParent->getID() +
					((currentParent->getAnnotation() != "") ? "<" + currentParent->getAnnotation() + ">" : ""));
				currentParent = currentParent->getParent();
			}
			std::reverse(parentChain.begin(), parentChain.end());
			parentChain.push_back(this->getID() + ((this->getAnnotation() != "") ? "<" + this->getAnnotation() + ">" : ""));
			return Functions::Vector::join(parentChain, "/");
		}

		void Attribute::setID(std::string id)
		{
			if (parent == nullptr) {
				std::cout << "<Error:DataParser:Attribute>[setID] : Can't change ID of " << getNodePath() << " when it has a parent" << std::endl;
			}
		}

		ContainerAttribute::ContainerAttribute(ContainerAttribute* parent, std::string id, Types::AttributeType type) : Attribute(parent, id, type)
		{
		}
		Attribute* ContainerAttribute::removeOwnership(Attribute* element)
		{
			element->removeParent(this);
			return element;
		}

		//BaseAttribute
		BaseAttribute::BaseAttribute(ContainerAttribute* parent, std::string id, std::string btype, std::string bdata) : Attribute(parent, id, Types::BaseAttribute) {
			dtype = btype;
			data = bdata;
			this->parent = parent;
			if (dtype == "string")
				Functions::String::replaceStringInPlace(data, "\"", "");
		}
		BaseAttribute::BaseAttribute(std::string id, std::string btype, std::string bdata) : Attribute(nullptr, id, Types::BaseAttribute)
		{
			dtype = btype;
			data = bdata;
			this->parent = parent;
			if (dtype == "string")
				Functions::String::replaceStringInPlace(data, "\"", "");
		}
		void BaseAttribute::set(int var) {
			if (dtype == "int")
				data = std::to_string(var);
			else
				std::cout << "<Error:DataParser:BaseAttribute>[setData] : " \
				<< getNodePath() << " is not a <int> BaseAttribute (" << dtype << ")" << std::endl;
		}
		void BaseAttribute::set(double var) {
			if (dtype == "float")
				data = std::to_string(var);
			else
				std::cout << "<Error:DataParser:BaseAttribute>[setData] : " \
				<< getNodePath() << " is not a <float> BaseAttribute (" << dtype << ")" << std::endl;
		}
		void BaseAttribute::set(std::string var) {
			if (dtype == "string")
				data = var;
			else
				std::cout << "<Error:DataParser:BaseAttribute>[setData] : " \
				<< getNodePath() << " is not a <string> BaseAttribute (" << dtype << ")" << std::endl;
		}
		void BaseAttribute::set(bool var) {
			if (dtype == "bool") {
				if (var)
					data = "True";
				else
					data = "False";
			}
			else
				std::cout << "<Error:DataParser:BaseAttribute>[setData] : " \
				<< getNodePath() << " is not a <bool> BaseAttribute (" << dtype << ")" << std::endl;
		}
		std::string BaseAttribute::returnData() {
			if (dtype != "string")
				return data;
			else
				return "\"" + data + "\"";
		}
		std::string BaseAttribute::getDataType() {
			return dtype;
		}

		//ListAttribute
		ListAttribute::ListAttribute(ContainerAttribute* parent, std::string id, std::string type) : ContainerAttribute(parent, id, Types::ListAttribute) {
			this->dataType = type;
		}
		ListAttribute::ListAttribute(std::string id, std::string dataType) : ContainerAttribute(nullptr, id, Types::ListAttribute)
		{
			this->dataType = dataType;
		}
		ListAttribute::~ListAttribute()
		{
			for (int i = 0; i < dataList.size(); i++)
				delete dataList[i];
		}
		unsigned int ListAttribute::getSize() {
			return dataList.size();
		}
		std::string ListAttribute::getDataType() {
			return dataType;
		}
		BaseAttribute* ListAttribute::getElement(unsigned int index) {
			if (index < dataList.size())
				return dataList[index];
			else
				std::cout << "<Error:DataParser:ListAttribute> : Can't access index " << index << " of " \
				<< getNodePath() << " (Size:" << dataList.size() << ")" << std::endl;
		}
		void ListAttribute::createElement(std::string element) {
			BaseAttribute* tempElem = new BaseAttribute(this, "#" + std::to_string(dataList.size()), dataType, element);
			dataList.push_back(tempElem);
		}
		Attribute* ListAttribute::extractElement(Attribute* element)
		{
			if (Functions::Vector::isInList(dynamic_cast<BaseAttribute*>(element), dataList)) {
				this->removeOwnership(element);
				Functions::Vector::eraseAll(dataList, dynamic_cast<BaseAttribute*>(element));
			}
			return element;
		}


		//ComplexAttribute
		ComplexAttribute::ComplexAttribute(ComplexAttribute* parent, std::string id) : ContainerAttribute(parent, id, Types::ComplexAttribute) {
			this->parent = parent;
		}
		ComplexAttribute::ComplexAttribute(ComplexAttribute* parent, std::string id, ComplexAttribute* herit)
			: ContainerAttribute(parent, id, Types::ComplexAttribute) {
			this->parent = parent;
			this->heritage(herit);
		}
		ComplexAttribute::ComplexAttribute(ComplexAttribute* parent, std::string id, std::vector<ComplexAttribute*>* multipleHerit)
			: ContainerAttribute(parent, id, Types::ComplexAttribute) {
			this->parent = parent;
			for (unsigned int i = 0; i < multipleHerit->size(); i++)
				this->heritage(multipleHerit->at(i));
		}
		ComplexAttribute::ComplexAttribute(std::string id) : ContainerAttribute(nullptr, id, Types::ComplexAttribute)
		{
		}
		ComplexAttribute::ComplexAttribute(std::string id, ComplexAttribute* herit) : ContainerAttribute(nullptr, id, Types::ComplexAttribute)
		{
			this->heritage(herit);
		}
		ComplexAttribute::ComplexAttribute(std::string id, std::vector<ComplexAttribute*>* multipleHerit)
			: ContainerAttribute(nullptr, id, Types::ComplexAttribute)
		{
			for (unsigned int i = 0; i < multipleHerit->size(); i++)
				this->heritage(multipleHerit->at(i));
		}
		ComplexAttribute::~ComplexAttribute()
		{
			for (auto it = childAttributes.begin(); it != childAttributes.end(); it++)
				delete it->second;
		}
		Attribute* ComplexAttribute::extractElement(Attribute* element)
		{
			if (Functions::Map::isInMap(element, childAttributes)) {
				this->removeOwnership(element);
				childAttributes.erase(element->getID());
				Functions::Vector::eraseAll(childAttributesNames, element->getID());
			}
			return element;
		}
		void ComplexAttribute::heritage(ComplexAttribute* heritTarget) {
			for (unsigned int i = 0; i < heritTarget->getAllBaseAttributes().size(); i++)
			{
				BaseAttribute* currentBaseAttr = heritTarget->getBaseAttribute(heritTarget->getAllBaseAttributes()[i]);
				this->createBaseAttribute(currentBaseAttr->getDataType(), currentBaseAttr->returnData());
			}
			for (unsigned int i = 0; i < heritTarget->getAllComplexAttributes().size(); i++)
			{
				ComplexAttribute* currentCmplxAttr = heritTarget->getComplexAttribute(heritTarget->getAllComplexAttributes()[i]);
				this->createComplexAttribute(currentCmplxAttr->getID());
				this->getComplexAttribute(heritTarget->getAllComplexAttributes()[i])->heritage(currentCmplxAttr);
			}
		}
		ComplexAttribute* ComplexAttribute::operator[](std::string cPath)
		{
			return getPath(cPath);
		}
		ComplexAttribute* ComplexAttribute::at(std::string cPath)
		{
			if (cPath.size() > 0 && Functions::String::extract(cPath, cPath.size() - 1, 0) == "/")
				cPath = Functions::String::extract(cPath, 0, 1);
			return getPath(cPath);
		}
		ComplexAttribute* ComplexAttribute::getPath(std::string attributePath)
		{
			if (attributePath.size() > 0 && Functions::String::extract(attributePath, attributePath.size() - 1, 0) == "/")
				attributePath = Functions::String::extract(attributePath, 0, 1);
			std::vector<std::string> sPath = convertPath(attributePath);
			if (sPath.size() > 0) {
				int pathIndex = 1;
				ComplexAttribute* getToPath;
				getToPath = this->getComplexAttribute(sPath[0]);
				while (pathIndex != sPath.size()) {
					getToPath = getToPath->getComplexAttribute(sPath[pathIndex]);
					pathIndex++;
				}
				return getToPath;
			}
			else {
				return this;
			}
		}
		BaseAttribute* ComplexAttribute::getBaseAttribute(std::string id) {
			if (childAttributes.find(id) != childAttributes.end() && childAttributes[id]->getType() == Types::BaseAttribute)
				return dynamic_cast<BaseAttribute*>(childAttributes[id]);
			else {
				std::cout << "<Error:DataParser:ComplexAttribute>[getAttribute] : Can't find BaseAttribute "
					<< id << " in " << getNodePath() << std::endl;
			}
		}
		ListAttribute* ComplexAttribute::getListAttribute(std::string id) {
			if (childAttributes.find(id) != childAttributes.end() && childAttributes[id]->getType() == Types::ListAttribute)
				return dynamic_cast<ListAttribute*>(childAttributes[id]);
			else {
				std::cout << "<Error:DataParser:ComplexAttribute>[getListAttribute] : Can't find ListAttribute "
					<< id << " in " << getNodePath() << std::endl;
			}
		}
		Types::AttributeType ComplexAttribute::getAttributeType(std::string id)
		{
			if (childAttributes.find(id) != childAttributes.end())
				return childAttributes[id]->getType();
			else
				std::cout << "<Error:DataParser:ComplexAttribute>[getAttributeType] : Attribute " << id << " does not exists" << std::endl;
		}
		std::vector<std::string> ComplexAttribute::getAllAttributes()
		{
			std::vector<std::string> allAttributes;
			for (std::string attributeName : this->childAttributesNames)
				allAttributes.push_back(attributeName);
			return allAttributes;
		}
		ComplexAttribute* ComplexAttribute::getComplexAttribute(std::string id) {
			if (childAttributes.find(id) != childAttributes.end() && childAttributes[id]->getType() == Types::ComplexAttribute) {
				return dynamic_cast<ComplexAttribute*>(childAttributes[id]);
			}
			else {
				std::cout << "<Error:DataParser:ComplexAttribute>[getComplexAttribute] : Can't find ComplexAttribute "
					<< id << " in " << getNodePath() << std::endl;
			}
		}
		std::vector<std::string> ComplexAttribute::getAllComplexAttributes() {
			std::vector<std::string> allComplexAttributes;
			for (std::string attributeName : this->childAttributesNames) {
				if (this->childAttributes[attributeName]->getType() == Types::ComplexAttribute) {
					allComplexAttributes.push_back(attributeName);
				}
			}
			return allComplexAttributes;
		}
		std::vector<std::string> ComplexAttribute::getAllBaseAttributes() {
			std::vector<std::string> allBaseAttributes;
			for (std::string attributeName : this->childAttributesNames) {
				if (this->childAttributes[attributeName]->getType() == Types::BaseAttribute) {
					allBaseAttributes.push_back(attributeName);
				}
			}
			return allBaseAttributes;
		}
		std::vector<std::string> ComplexAttribute::getAllListAttributes() {
			std::vector<std::string> allListAttributes;
			for (std::string attributeName : this->childAttributesNames) {
				if (this->childAttributes[attributeName]->getType() == Types::ListAttribute) {
					allListAttributes.push_back(attributeName);
				}
			}
			return allListAttributes;
		}
		bool ComplexAttribute::containsAttribute(std::string attributeName)
		{
			if (childAttributes.find(attributeName) != childAttributes.end())
				return true;
			else
				return false;
		}
		bool ComplexAttribute::containsBaseAttribute(std::string attributeName) {
			if (childAttributes.find(attributeName) != childAttributes.end() && childAttributes[attributeName]->getType() == Types::BaseAttribute)
				return true;
			else
				return false;
		}
		bool ComplexAttribute::containsComplexAttribute(std::string attributeName) {
			std::cout << "Searching for ComplexAttribute : " << attributeName << std::endl;
			if (childAttributes.find(attributeName) != childAttributes.end() && childAttributes[attributeName]->getType() == Types::ComplexAttribute)
				return true;
			else {
				return false;
			}
		}
		bool ComplexAttribute::containsListAttribute(std::string attributeName) {
			if (childAttributes.find(attributeName) != childAttributes.end() && childAttributes[attributeName]->getType() == Types::ListAttribute)
				return true;
			else
				return false;
		}
		void ComplexAttribute::createBaseAttribute(std::string name, std::string type, std::string data)
		{
			BaseAttribute* tempAttr = new BaseAttribute(this, name, type, data);
			childAttributes[name] = tempAttr;
			childAttributesNames.push_back(name);
		}
		void ComplexAttribute::createBaseAttribute(std::string name, std::string data)
		{
			BaseAttribute* tempAttr = new BaseAttribute(this, name, "string", data);
			childAttributes[name] = tempAttr;
			childAttributesNames.push_back(name);
		}
		void ComplexAttribute::createBaseAttribute(std::string name, bool data)
		{
			BaseAttribute* tempAttr = new BaseAttribute(this, name, "bool", (data == true ? "True" : "False"));
			childAttributes[name] = tempAttr;
			childAttributesNames.push_back(name);
		}
		void ComplexAttribute::createBaseAttribute(std::string name, int data)
		{
			BaseAttribute* tempAttr = new BaseAttribute(this, name, "int", std::to_string(data));
			childAttributes[name] = tempAttr;
			childAttributesNames.push_back(name);
		}
		void ComplexAttribute::createBaseAttribute(std::string name, double data)
		{
			BaseAttribute* tempAttr = new BaseAttribute(this, name, "float", std::to_string(data));
			childAttributes[name] = tempAttr;
			childAttributesNames.push_back(name);
		}
		void ComplexAttribute::pushBaseAttribute(BaseAttribute* attr) {
			//Memory Leak on replace
			childAttributes[attr->getID()] = attr;
			childAttributesNames.push_back(attr->getID());
		}
		void ComplexAttribute::createListAttribute(std::string id, std::string type) {
			ListAttribute* tempAttr = new ListAttribute(this, id, type);
			childAttributes[id] = tempAttr;
			childAttributesNames.push_back(id);
		}
		void ComplexAttribute::pushListAttribute(ListAttribute* attr) {
			childAttributes[attr->getID()] = attr;
			childAttributesNames.push_back(attr->getID());
		}
		void ComplexAttribute::createListItem(std::string listID, std::string value) {
			this->getListAttribute(listID)->createElement(value);
		}
		void ComplexAttribute::createListGenerator(std::string gtarget, std::string gtype, std::string regex) {
			if (childAttributes.find(gtarget) != childAttributes.end() && childAttributes[gtarget]->getType() == Types::ListAttribute)
			{
				ListGenerator* lGen = new ListGenerator(gtype, regex, dynamic_cast<ListAttribute*>(childAttributes[gtarget]));
				listGenerators[gtarget] = lGen;
				listGeneratorsList.push_back(gtarget);
			}
			else {
				std::cout << "<Error:DataParser:ComplexAttribute>[createListGenerator] : ListAttribute <"
					<< gtarget << "> does not exists in " << getNodePath() << std::endl;
			}
		}
		void ComplexAttribute::addBoundToListGenerator(std::string listID, int gstart, int gend) {
			if (listGenerators.find(listID) != listGenerators.end())
				listGenerators[listID]->addBound(gstart, gend);
			else
			{
				if (childAttributes.find(listID) != childAttributes.end() && childAttributes[listID]->getType() == Types::ListAttribute) {
					std::cout << "<Error:DataParser:ComplexAttribute>[addBoundToListGenerator] : ListAttribute <"
						<< listID << "> has no ListGenerator in " << getNodePath() << std::endl;
				}
				else {
					std::cout << "<Error:DataParser:ComplexAttribute>[addBoundToListGenerator] : ListAttribute <"
						<< listID << "> does not exists in " << getNodePath() << std::endl;
				}
			}
		}
		void ComplexAttribute::generateInList(std::string listID) {
			if (childAttributes.find(listID) != childAttributes.end() && childAttributes[listID]->getType() == Types::ListAttribute)
			{
				if (listGenerators.find(listID) != listGenerators.end())
				{
					listGenerators[listID]->generate();
					free(listGenerators[listID]);
					listGenerators.erase(listID);
					listGeneratorsList.erase(std::remove(listGeneratorsList.begin(), listGeneratorsList.end(), listID), listGeneratorsList.end());
				}
				else {
					std::cout << "<Error:DataParser:ComplexAttribute>[generateInList] : ListAttribute <" << listID
						<< "> has no ListGenerator in " << getNodePath() << std::endl;
				}
			}
			else {
				std::cout << "<Error:DataParser:ComplexAttribute>[generateInList] : ListAttribute <" <<
					listID << "> does not exists in " << getNodePath() << std::endl;
			}
		}
		void ComplexAttribute::createComplexAttribute(std::string id) {
			ComplexAttribute* tempAttr = new ComplexAttribute(this, id);
			childAttributes[id] = tempAttr;
			childAttributesNames.push_back(id);
		}
		void ComplexAttribute::pushComplexAttribute(ComplexAttribute* cmplx) {
			childAttributes[cmplx->getID()] = cmplx;
			childAttributesNames.push_back(cmplx->getID());
		}
		void ComplexAttribute::writeAttributes(std::ofstream* file, unsigned int depth) {
			for (unsigned int i = 0; i < depth; i++)
				(*file) << "    ";
			if (depth)
				(*file) << "@" << id << std::endl;
			else
				(*file) << id << ":" << std::endl;
			for (unsigned int i = 0; i < this->getAllBaseAttributes().size(); i++)
			{
				for (unsigned int j = 0; j < depth + 1; j++)
					(*file) << "    ";
				(*file) << this->getAllBaseAttributes()[i] << ":" << this->getBaseAttribute(getAllBaseAttributes()[i])->returnData() << std::endl;
			}
			for (unsigned int i = 0; i < this->getAllListAttributes().size(); i++)
			{
				for (unsigned int j = 0; j < depth + 1; j++)
					(*file) << "    ";
				if (listGenerators.find(this->getAllListAttributes()[i]) != listGenerators.end())
				{
					std::vector<std::pair<int, int>> allBounds = listGenerators[this->getAllListAttributes()[i]]->getAllBounds();
					(*file) << "?" << this->getAllListAttributes()[i] << "(" << this->getListAttribute(this->getAllListAttributes()[i])->getDataType()
						<< ")<" << listGenerators[this->getAllListAttributes()[i]]->getRegex() << ">{";
					for (unsigned int j = 0; j < allBounds.size(); j++)
					{
						(*file) << allBounds[j].first << "-" << allBounds[j].second;
						if (j != allBounds.size() - 1) (*file) << "," << std::endl;
					}
					(*file) << "}:" << std::endl;
				}
				else {
					(*file) << "?" << this->getAllListAttributes()[i] << "("
						<< this->getListAttribute(this->getAllListAttributes()[i])->getDataType() << "):" << std::endl;
				}
				for (unsigned int k = 0; k < this->getListAttribute(this->getAllListAttributes()[i])->getSize(); k++)
				{
					for (unsigned int l = 0; l < depth + 2; l++)
						(*file) << "    ";
					(*file) << this->getListAttribute(this->getAllListAttributes()[i])->getElement(k)->returnData() << std::endl;
				}
			}
			for (unsigned int i = 0; i < this->getAllComplexAttributes().size(); i++)
				this->getComplexAttribute(this->getAllComplexAttributes()[i])->writeAttributes(file, depth + 1);
			if (depth == 0)
				(*file) << std::endl;
		}
		void ComplexAttribute::deleteBaseAttribute(std::string id, bool freeMemory) {
			if (Functions::Vector::isInList(id, this->getAllBaseAttributes())) {
				childAttributesNames.erase(childAttributesNames.begin() + Functions::Vector::indexOfElement(id, this->getAllBaseAttributes()));
			}
			typedef std::map<std::string, Attribute*>::iterator it_type;
			it_type itDel = childAttributes.find(id);
			if (itDel != childAttributes.end() && childAttributes[id]->getType() == Types::BaseAttribute) {
				if (freeMemory)
					delete childAttributes[id];
				childAttributes.erase(itDel);
			}
		}
		void ComplexAttribute::deleteComplexAttribute(std::string id, bool freeMemory) {
			if (Functions::Vector::isInList(id, this->getAllComplexAttributes())) {
				childAttributesNames.erase(childAttributesNames.begin() + Functions::Vector::indexOfElement(id, this->getAllComplexAttributes()));
			}
			typedef std::map<std::string, Attribute*>::iterator it_type;
			it_type itDel = childAttributes.find(id);
			if (itDel != childAttributes.end() && childAttributes[id]->getType() == Types::ComplexAttribute) {
				if (freeMemory)
					delete childAttributes[id];
				childAttributes.erase(itDel);
			}
		}
		void ComplexAttribute::deleteListAttribute(std::string id, bool freeMemory) {
			if (Functions::Vector::isInList(id, this->getAllListAttributes())) {
				childAttributesNames.erase(childAttributesNames.begin() + Functions::Vector::indexOfElement(id, this->getAllListAttributes()));
			}
			typedef std::map<std::string, Attribute*>::iterator it_type;
			it_type itDel = childAttributes.find(id);
			if (itDel != childAttributes.end() && childAttributes[id]->getType() == Types::ListAttribute) {
				if (freeMemory)
					delete childAttributes[id];
				childAttributes.erase(itDel);
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
						if (genType == "string")
						{
							elemToCreate = genRegex;
							Functions::String::replaceStringInPlace(elemToCreate, "%s", std::to_string(j));
							Functions::String::replaceStringInPlace(elemToCreate, "\"", "");
						}
						genTarget->createElement(elemToCreate);
					}
				}
				else if (genBounds[i].first > genBounds[i].second)
				{
					for (int j = start; j >= stop; j--)
					{
						std::string elemToCreate = std::to_string(j);
						if (genType == "string")
						{
							elemToCreate = genRegex;
							Functions::String::replaceStringInPlace(elemToCreate, "%s", std::to_string(j));
							Functions::String::replaceStringInPlace(elemToCreate, "\"", "");
						}
						genTarget->createElement(elemToCreate);
					}
				}
			}
		}

		//ModelObject
		std::map<std::string, ObjectModel*> ObjectModel::modelMap = std::map<std::string, ObjectModel*>();
		ObjectModel::ObjectModel(std::string modelName, std::string objectSignature) : signature("ModelSignature"), body("ModelBody")
		{
			name = modelName;
			Functions::String::StringExtractor signatureRes = Functions::String::extractAllStrings(objectSignature);
			std::string signatureWithoutStrings = Functions::Vector::join(std::get<1>(signatureRes), "&string");
			std::vector<std::string> allParameters = Functions::String::split(signatureWithoutStrings, ",");
			for (int i = 0; i < allParameters.size(); i++) {
				std::vector<std::string> splittedParameter = Functions::String::split(allParameters[i], ":");
				std::string parameterType = Functions::String::replaceString(splittedParameter[0], " ", "");
				std::vector<std::string> parameterRightPart = Functions::String::split(Functions::String::replaceString(splittedParameter[1], " ", ""), "=");
				std::string parameterName = parameterRightPart[0];
				std::string defaultValue = (parameterRightPart.size() == 2) ? parameterRightPart[1] : getDefaultValueForType(parameterType);
				signature.createBaseAttribute(parameterName, parameterType, defaultValue);
			}
		}
		ComplexAttribute ObjectModel::buildModel(std::string objectName, std::string buildSignature)
		{
			Functions::String::StringExtractor signatureRes = Functions::String::extractAllStrings(buildSignature);
			std::string signatureWithoutStrings = Functions::Vector::join(std::get<1>(signatureRes), "&string");
			std::vector<std::string> allParameters = Functions::String::split(signatureWithoutStrings, ",");
			std::vector<std::string> parameterList;
			int stringIndex = 0;
			for (std::string parameter : allParameters) {
				Functions::String::replaceStringInPlace(parameter, " ", "");
				if (parameter == "&string") {
					parameterList.push_back("\"" + std::get<0>(signatureRes)[stringIndex] + "\"");
					stringIndex++;
				}
				else {
					parameterList.push_back(parameter);
				}
			}
			ComplexAttribute objectParameters(objectName);
			std::vector<std::string> signatureAttributes = signature.getAllBaseAttributes();
			if (parameterList.size() > signatureAttributes.size()) {
				std::cout << "<Error:DataParser:ObjectModel>[buildModel] : Too many parameters provided for Model : "
					<< name << " (" << signatureAttributes.size() << " parameters maximum)" << std::endl;
				return nullptr;
			}
			for (int i = 0; i < signatureAttributes.size(); i++) {
				BaseAttribute* currentSignatureParameter = signature.getBaseAttribute(signatureAttributes[i]);
				if (i < parameterList.size()) {
					if (getVarType(parameterList[i]) == currentSignatureParameter->getDataType()) {
						objectParameters.createBaseAttribute(currentSignatureParameter->getID(),
							currentSignatureParameter->getDataType(), parameterList[i]);
					}
					else {
						std::cout << "<Error:DataParser:ObjectModel>[buildModel] : Type mismatch at parameter "
							<< currentSignatureParameter->getID() << " for Model " << name << std::endl;
						return nullptr;
					}
				}
				else {
					objectParameters.createBaseAttribute(currentSignatureParameter->getID(),
						currentSignatureParameter->getDataType(), currentSignatureParameter->returnData());
				}
			}
			ComplexAttribute linkedBody = body;
			//linkedBody.resolveLinking(&objectParameters);
		}
		void ObjectModel::CreateModel(std::string modelName, std::string objectSignature)
		{
			if (modelMap.find(modelName) != modelMap.end()) {
				delete modelMap[modelName];
			}
			modelMap[modelName] = new ObjectModel(modelName, objectSignature);
		}
		ComplexAttribute ObjectModel::BuildObjectFromModel(std::string modelName, std::string objectName, std::string buildSignature)
		{
			if (modelMap.find(modelName) != modelMap.end()) {
				return modelMap[modelName]->buildModel(objectName, buildSignature);
			}
			else {
				std::cout << "<Error:DataParser:ObjectModel>[BuildObjectFromModel] : Can't find ObjectModel : " << modelName << std::endl;
			}
		}

		//DataParser
		DataParser::DataParser()
		{
			this->autoMemory = false;
			root = new ComplexAttribute("root");
			root->setAnnotation("NoFile");
		}
		DataParser::DataParser(bool autoMemoryManagement)
		{
			this->autoMemory = autoMemoryManagement;
			root = new ComplexAttribute("root");
			root->setAnnotation("NoFile");
		}
		DataParser::~DataParser()
		{
			if (autoMemory) {
				if (dpNav != nullptr) delete dpNav;
				delete root;
			}
		}
		DataParserNavigator* DataParser::hookNavigator(DataParserNavigator* dpNav) {
			return (this->dpNav = dpNav);
		}
		DataParserNavigator* DataParser::accessNavigator() {
			return this->dpNav;
		}
		bool DataParser::checkNavigator() {
			return dpNav != NULL;
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
		void DataParser::createRootAttribute(std::string id)
		{
			// Memory Leak on Replace
			root->createComplexAttribute(id);
			if (checkNavigator()) {
				dpNav->setCurrentRootAttribute(id);
			}
		}
		bool DataParser::containsRootAttribute(std::string objectName)
		{
			return (root->containsComplexAttribute(objectName));
		}
		ComplexAttribute* DataParser::extractRootAttribute(std::string rootAttributeName)
		{
			ComplexAttribute* returnAttribute = this->getRootAttribute(rootAttributeName);
			root->extractElement(this->getRootAttribute(rootAttributeName));
			return returnAttribute;
		}
		ComplexAttribute* DataParser::getRootAttribute(std::string id)
		{
			std::cout << "Root equals to : " << root << std::endl;
			if (containsRootAttribute(id)) {
				return root->getComplexAttribute(id);
			}
			else {
				std::cout << "<Error:DataParser:DataParser>[getRootAttribute] : Can't find RootAttribute : "
					<< id << " on " << root->getAnnotation() << std::endl;
			}
		}
		ComplexAttribute* DataParser::getPath(std::string path)
		{
			std::cout << "DAPATH IS / " << path << std::endl;
			if (path.size() > 0 && Functions::String::extract(path, path.size() - 1, 0) == "/")
				path = Functions::String::extract(path, 0, 1);
			if (Functions::String::occurencesInString(path, "/") > 0) {
				std::string subPath = Functions::Vector::join(Functions::String::split(path, "/"), "/", 1);
				std::cout << "Go to : " << Functions::String::split(path, "/")[0] << " then " << subPath << std::endl;
				return getRootAttribute(Functions::String::split(path, "/")[0])->at(subPath);
			}
			else {
				return getRootAttribute(path);
			}
		}
		ComplexAttribute* DataParser::operator[](std::string cPath)
		{
			return getPath(cPath);
		}
		ComplexAttribute* DataParser::at(std::string cPath)
		{
			//HERE
			return nullptr;
		}
		void DataParser::createBaseAttribute(std::string attributePath, std::string name, std::string data) {
			this->getPath(attributePath)->createBaseAttribute(name, "string", data);
		}
		void DataParser::createBaseAttribute(std::string name, std::string data) {
			if (checkNavigator()) {
				this->getRootAttribute(dpNav->getCurrentRootAttribute())
					->getPath(dpNav->getCurrentPath())->createBaseAttribute(name, "string", data);
			}
		}
		void DataParser::createBaseAttribute(std::string attributePath, std::string name, bool data) {
			this->getPath(attributePath)->createBaseAttribute(name, "int", data ? "True" : "False");
		}
		void DataParser::createBaseAttribute(std::string name, bool data) {
			if (checkNavigator()) {
				this->getPath(dpNav->getFullPath())->createBaseAttribute(name, "bool", data ? "True" : "False");
			}
		}
		void DataParser::createBaseAttribute(std::string attributePath, std::string name, int data) {
			this->getPath(attributePath)->createBaseAttribute("int", std::to_string(data));
		}
		void DataParser::createBaseAttribute(std::string name, int data) {
			if (checkNavigator()) {
				this->getPath(dpNav->getFullPath())->createBaseAttribute(name, "int", std::to_string(data));
			}
		}
		void DataParser::createBaseAttribute(std::string attributePath, std::string name, double data) {
			this->getPath(attributePath)->createBaseAttribute("float", std::to_string(data));
		}
		void DataParser::createBaseAttribute(std::string name, double data) {
			if (checkNavigator()) {
				this->getPath(dpNav->getFullPath())->createBaseAttribute(name, "float", std::to_string(data));
			}
		}
		void DataParser::pushBaseAttribute(std::string attributePath, BaseAttribute* attr) {
			this->getPath(attributePath)->pushBaseAttribute(attr);
		}
		void DataParser::pushBaseAttribute(BaseAttribute* attr) {
			if (checkNavigator()) {
				this->getPath(dpNav->getFullPath())->pushBaseAttribute(attr);
			}
		}
		void DataParser::createListAttribute(std::string attributePath, std::string id, std::string type) {
			this->getPath(attributePath)->createListAttribute(id, type);
		}
		void DataParser::createListAttribute(std::string id, std::string type) {
			if (checkNavigator()) {
				this->getPath(dpNav->getFullPath())->createListAttribute(id, type);
			}
		}
		void DataParser::pushListAttribute(std::string attributePath, ListAttribute* attr) {
			this->getPath(attributePath)->pushListAttribute(attr);
		}
		void DataParser::pushListAttribute(ListAttribute* attr) {
			if (checkNavigator()) {
				this->getPath(dpNav->getFullPath())->pushListAttribute(attr);
			}
		}
		void DataParser::createListItem(std::string attributePath, std::string listID, std::string value) {
			this->getPath(attributePath)->createListItem(listID, value);
		}
		void DataParser::createListItem(std::string listID, std::string value) {
			if (checkNavigator()) this->getPath(dpNav->getFullPath())->createListItem(listID, value);
		}
		void DataParser::createListGenerator(std::string attributePath, std::string gtarget, std::string gtype, std::string regex) {
			this->getPath(attributePath)->createListGenerator(gtarget, gtype, regex);
		}
		void DataParser::createListGenerator(std::string gtarget, std::string gtype, std::string regex) {
			if (checkNavigator()) {
				this->getPath(dpNav->getFullPath())->createListGenerator(gtarget, gtype, regex);
			}
		}
		void DataParser::addBoundToListGenerator(std::string attributePath, std::string listID, int gstart, int gend) {
			this->getPath(attributePath)->addBoundToListGenerator(listID, gstart, gend);
		}
		void DataParser::addBoundToListGenerator(std::string listID, int gstart, int gend) {
			if (checkNavigator()) {
				this->getPath(dpNav->getFullPath())->addBoundToListGenerator(listID, gstart, gend);
			}
		}
		void DataParser::generateInList(std::string attributePath, std::string listID) {
			this->getPath(attributePath)->generateInList(listID);
		}
		void DataParser::generateInList(std::string listID) {
			if (checkNavigator()) {
				this->getPath(dpNav->getFullPath())->generateInList(listID);
			}
		}
		void DataParser::createComplexAttribute(std::string attributePath, std::string id) {
			this->getPath(attributePath)->createComplexAttribute(id);
		}
		void DataParser::createComplexAttribute(std::string id) {
			if (checkNavigator()) {
				this->getPath(dpNav->getFullPath())->createComplexAttribute(id);
				dpNav->goTo(id);
			}
		}
		void DataParser::pushComplexAttribute(std::string attributePath, ComplexAttribute* cmplx) {
			this->getPath(attributePath)->pushComplexAttribute(cmplx);
		}
		void DataParser::pushComplexAttribute(ComplexAttribute* cmplx) {
			if (checkNavigator()) {
				this->getPath(dpNav->getFullPath())->pushComplexAttribute(cmplx);
				dpNav->goTo(cmplx->getID());
			}
		}
		unsigned int DataParser::getListSize(std::string attributePath, std::string listName) {
			return this->getPath(attributePath)->getListAttribute(listName)->getSize();
		}
		unsigned int DataParser::getListSize(std::string listName) {
			if (checkNavigator()) {
				return this->getPath(dpNav->getFullPath())->getListAttribute(listName)->getSize();
			}
		}
		std::vector<std::string> DataParser::getAllComplexAttributes(std::string attributePath) {
			return this->getPath(attributePath)->getAllComplexAttributes();
		}
		std::vector<std::string> DataParser::getAllComplexAttributes() {
			if (checkNavigator()) {
				return this->getPath(dpNav->getFullPath())->getAllComplexAttributes();
			}
		}
		std::vector<std::string> DataParser::getAllBaseAttributes(std::string attributePath) {
			return this->getPath(attributePath)->getAllBaseAttributes();
		}
		std::vector<std::string> DataParser::getAllBaseAttributes() {
			if (checkNavigator()) {
				return this->getPath(dpNav->getFullPath())->getAllBaseAttributes();
			}
		}
		std::vector<std::string> DataParser::getAllListAttributes(std::string attributePath) {
			return this->getPath(attributePath)->getAllListAttributes();
		}
		std::vector<std::string> DataParser::getAllListAttributes() {
			if (checkNavigator()) {
				return this->getPath(dpNav->getFullPath())->getAllListAttributes();
			}
		}
		bool DataParser::containsBaseAttribute(std::string attributePath, std::string attributeName) {
			std::cout << "Searching for : " << attributeName << " on path " << attributePath << std::endl;
			return this->getPath(attributePath)->containsBaseAttribute(attributeName);
		}
		bool DataParser::containsBaseAttribute(std::string attributeName) {
			if (checkNavigator()) {
				return this->getPath(dpNav->getFullPath())->containsBaseAttribute(attributeName);
			}
		}
		bool DataParser::containsComplexAttribute(std::string attributePath, std::string attributeName) {
			return this->getPath(attributePath)->containsComplexAttribute(attributeName);
		}
		bool DataParser::containsComplexAttribute(std::string attributeName) {
			if (checkNavigator()) {
				return this->getPath(dpNav->getFullPath())->containsComplexAttribute(attributeName);
			}
		}
		bool DataParser::containsListAttribute(std::string attributePath, std::string attributeName) {
			return this->getPath(attributePath)->containsListAttribute(attributeName);
		}
		bool DataParser::containsListAttribute(std::string attributeName) {
			if (checkNavigator()) {
				return this->getPath(dpNav->getFullPath())->containsListAttribute(attributeName);
			}
		}
		BaseAttribute* DataParser::getBaseAttribute(std::string attributePath, std::string attributeName) {
			return this->getPath(attributePath)->getBaseAttribute(attributeName);
		}
		BaseAttribute* DataParser::getBaseAttribute(std::string attributeName) {
			if (checkNavigator()) return this->getPath(dpNav->getFullPath())->getBaseAttribute(attributeName);
		}
		BaseAttribute* DataParser::getListItem(std::string attributePath, std::string listName, int listItem) {
			return this->getPath(attributePath)->getListAttribute(listName)->getElement(listItem);
		}
		BaseAttribute* DataParser::getListItem(std::string listName, int listItem) {
			if (checkNavigator()) return this->getPath(dpNav->getFullPath())->getListAttribute(listName)->getElement(listItem);
		}
		ComplexAttribute* DataParser::getComplexAttribute(std::string attributePath, std::string id) {
			return this->getPath(attributePath)->getComplexAttribute(id);
		}
		ComplexAttribute* DataParser::getComplexAttribute(std::string id) {
			if (checkNavigator()) return this->getPath(dpNav->getFullPath())->getComplexAttribute(id);
		}
		ListAttribute* DataParser::getListAttribute(std::string attributePath, std::string listName) {
			return this->getPath(attributePath)->getListAttribute(listName);
		}
		ListAttribute* DataParser::getListAttribute(std::string listName) {
			if (checkNavigator()) return this->getPath(dpNav->getFullPath())->getListAttribute(listName);
		}
		bool DataParser::parseFile(std::string filename, bool verbose) {
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
					parsedLine = Functions::String::replaceString(currentLine, "	", "    ");
					currentIndent = Functions::String::occurencesInString(parsedLine, "    ");
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
					Functions::String::replaceStringInPlace(parsedLine, "    ", "");
					if (parsedLine != "" && currentIndent == 0)
					{
						if (parsedLine.substr(parsedLine.size() - 1, 1) == ":")
						{
							if (verbose) std::cout << "    Create new RootAttribute : " << parsedLine.substr(0, parsedLine.size() - 1) << std::endl;
							curCat = parsedLine.substr(0, parsedLine.size() - 1);
							this->createRootAttribute(curCat);
						}
						else if (parsedLine.substr(0, 6) == "Define" && parsedLine.substr(parsedLine.size() - 1, 1) == ";")
						{
							std::vector<std::string> defineInstructions = Functions::String::split(parsedLine, " ");
							if (defineInstructions[1] == "Flag")
							{
								std::string newFlag = defineInstructions[2];
								Functions::String::replaceStringInPlace(newFlag, "(", "");
								Functions::String::replaceStringInPlace(newFlag, ");", "");
								flagList.push_back(newFlag);
								if (verbose) std::cout << "    Define New Flag : " << newFlag << std::endl;
							}
						}
					}
					else if (curCat != "None" && parsedLine != "" && currentIndent > 0)
					{
						std::vector<std::string> symbolExclusion = { "@", "?" ,"\"", "#", "{" };
						for (unsigned int p = 0; p <= currentIndent; p++)
						{
							if (verbose) std::cout << "    ";
						}
						if (!Functions::Vector::isInList(parsedLine.substr(0, 1), symbolExclusion) && Functions::String::occurencesInString(parsedLine, ":"))
						{
							std::string attributeName = Functions::String::split(parsedLine, ":")[0];
							std::vector<std::string> splittedLine = Functions::String::split(parsedLine, ":");
							std::string attributeValue = Functions::Vector::join(splittedLine, ":", 1, 0);
							std::string attributeType = getVarType(attributeValue);
							if (attributeType == "unknown") std::cout << "<Warning:DataParser:DataParser>[parseFile] : " << attributeName << " is unknown type" << std::endl;
							getRootAttribute(curCat)->getPath(Path(addPath))->createBaseAttribute(attributeName, attributeType, attributeValue);
							std::string pushIndicator;
							if (addPath.size() == 0) { pushIndicator = curCat + ":Root"; }
							else { pushIndicator = addPath[addPath.size() - 1]; }
							if (verbose) std::cout << "Create base attribute " << attributeName << "(" << attributeValue << ") inside " << pushIndicator << " (Type:" << attributeType << ")" << std::endl;
						}
						else if (parsedLine.substr(0, 1) == "@")
						{
							std::string complexElementID = parsedLine.substr(1);
							std::string complexToHeritID;
							std::vector<std::string> complexToHeritIDList;
							std::vector<ComplexAttribute*> complexToHerit;
							if (Functions::String::occurencesInString(complexElementID, ":") == 1 && Functions::String::split(complexElementID, ":").size() == 2)
							{
								complexToHeritID = Functions::String::replaceString(Functions::String::split(complexElementID, ":")[1], " ", "");
								complexElementID = Functions::String::split(complexElementID, ":")[0];
								complexToHeritIDList = Functions::String::split(complexToHeritID, ",");

								for (unsigned int i = 0; i < complexToHeritIDList.size(); i++) {
									complexToHerit.push_back(getRootAttribute(curCat)->getComplexAttribute(complexToHeritIDList[i]));
								}
							}
							getRootAttribute(curCat)->getPath(Path(addPath))->createComplexAttribute(complexElementID);
							if (verbose) std::cout << "Create cmplx attribute @" << complexElementID << " inside " << curCat + ":" \
								+ getRootAttribute(curCat)->getPath(Path(addPath))->getID() << " (&" << \
								getRootAttribute(curCat)->getPath(Path(addPath)) << ")" << std::endl;
							for (unsigned int i = 0; i < complexToHerit.size(); i++) {
								for (unsigned int p = 0; p <= currentIndent + 1; p++) {
									if (verbose) std::cout << "    ";
								}
								if (verbose) std::cout << "{Herit from : " << complexToHeritIDList[i] << "}" << std::endl;
								getRootAttribute(curCat)->getPath(Path(addPath))->getComplexAttribute(complexElementID)->heritage(complexToHerit[i]);
							}

							addPath.push_back(complexElementID);
						}
						else if (parsedLine.substr(0, 1) == "?")
						{
							std::string listElementID = parsedLine.substr(1);
							listElementID = Functions::String::split(listElementID, "(")[0];
							std::string listElementType = parsedLine.substr(1);
							listElementType = Functions::String::split(Functions::String::split(listElementType, ")")[0], "(")[1];
							getRootAttribute(curCat)->getPath(Path(addPath))->createListAttribute(listElementID, listElementType);
							curList = listElementID;
							curListIndent = currentIndent;
							if (verbose) {
								std::cout << "Create list attribute ?" << curList << " inside "
									<< curCat + ":" + getRootAttribute(curCat)->getPath(Path(addPath))->getID() << std::endl;
							}
							if (Functions::String::occurencesInString(Functions::String::split(parsedLine.substr(1), ")")[1], "<") == 1) {
								std::string generatorRegex = Functions::String::split(parsedLine.substr(1), "<")[1];
								std::string genIt = Functions::String::split(generatorRegex, "{")[1];
								genIt = Functions::String::split(genIt, "}")[0];
								generatorRegex = Functions::String::split(generatorRegex, ">")[0];
								for (unsigned int p = 0; p <= currentIndent + 1; p++) {
									if (verbose) std::cout << "    ";
								}
								if (verbose) std::cout << "Generator of type " << listElementType << " hooked to " << listElementID << " with pattern " << generatorRegex << " and iterator " << genIt << std::endl;
								ListGenerator gen(listElementType, generatorRegex,
									getRootAttribute(curCat)->getPath(Path(addPath))->getListAttribute(listElementID));
								std::vector<std::string> listOfBounds;
								listOfBounds = Functions::String::split(genIt, ",");
								for (unsigned int i = 0; i < listOfBounds.size(); i++) {
									if (Functions::String::occurencesInString(listOfBounds[i], "-") == 1) {
										int startBound = std::stoi(Functions::String::split(listOfBounds[i], "-")[0]);
										int endBound = std::stoi(Functions::String::split(listOfBounds[i], "-")[1]);
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
							if (attributeType == getRootAttribute(curCat)->getPath(Path(addPath))->getListAttribute(curList)->getDataType())
							{
								getRootAttribute(curCat)->getPath(Path(addPath))->getListAttribute(curList)->createElement(attributeValue);
								if (verbose) std::cout << "Push element " << attributeValue << " inside " << curList << std::endl;
							}
							else
							{
								if (verbose) {
									std::cout << "Error ! Can't push " << attributeType << " inside " << curList << " which is "
										<< getRootAttribute(curCat)->getPath(Path(addPath))->getListAttribute(curList)->getType() << " type " << std::endl;
								}
							}
						}
					}
					currentIndex++;
				}
				useFile.close();
				root->setAnnotation(filename);
				if (verbose) std::cout << "Parsed over.." << std::endl;
				return true;
			}
			else
			{
				std::cout << "<Error:DataParser:DataParser>[parseFile] : Can't open " << filename << ". File does not exists" << std::endl;
				return false;
			}
		}
		void DataParser::writeFile(std::string filename, bool verbose) {
			outFile.open(filename);
			if (verbose) std::cout << "Displaying data table" << std::endl;
			unsigned int currentDeepness = 1;
			for (unsigned int i = 0; i < this->getAmountOfFlags(); i++)
				outFile << "Define Flag (" << this->getFlagAtIndex(i) << ");" << std::endl;
			if (this->getAmountOfFlags() > 0) outFile << std::endl;
			for (unsigned int objIt = 0; objIt < root->getAllComplexAttributes().size(); objIt++) {
				getRootAttribute(root->getAllComplexAttributes()[objIt])->writeAttributes(&outFile);
			}
			outFile.close();
		}
		std::vector<std::string> DataParser::getAllRootAttributes() {
			return root->getAllComplexAttributes();
		}
		void DataParser::deleteRootAttribute(std::string name, bool freeMemory)
		{
			root->deleteComplexAttribute(name, freeMemory);
		}
	}
}