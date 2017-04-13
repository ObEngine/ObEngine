//Author : Sygmei
//Key : 976938ef7d46c286a2027d73f3a99467bcfa8ff0c1e10bd0016139744ef5404f4eb4d069709f9831f6de74a094944bf0f1c5bf89109e9855290336a66420376f

#include "Vili.hpp"

namespace vili
{
	void LoadErrors(std::string errorFile)
	{
		DataParser errors(errorFile);

		errors->walk([](ComplexAttribute* node) -> void {
			if (node->contains(Types::BaseAttribute, "message"))
			{
				std::vector<std::string> location;
				ComplexAttribute* currentParent = node;
				while (currentParent != nullptr)
				{
					if (currentParent->contains(Types::BaseAttribute, "where"))
					{
						location.insert(location.begin(), static_cast<ComplexAttribute*>(currentParent)->getBaseAttribute("where")->get<std::string>());
					}
					if (currentParent->getParent() != nullptr)
						currentParent = static_cast<ComplexAttribute*>(currentParent->getParent());
					else
						currentParent = nullptr;
				}
				std::string errorLocation = Functions::Vector::join(location, ".");
				std::cout << "Error Location : " << errorLocation << std::endl;
			}
		});
	}

	std::istream& safeGetline(std::istream& is, std::string& t)
	{
		t.clear();

		std::istream::sentry se(is, true);
		std::streambuf* sb = is.rdbuf();

		for (;;) {
			int c = sb->sbumpc();
			switch (c) {
			case '\n':
				return is;
			case '\r':
				if (sb->sgetc() == '\n')
					sb->sbumpc();
				return is;
			case EOF:
				if (t.empty())
					is.setstate(std::ios::eofbit);
				return is;
			default:
				t += (char)c;
			}
		}
	}

	std::vector<std::string> convertPath(std::string path)
	{
		std::vector<std::string> vecPath = {};
		if (Functions::String::occurencesInString(path, "/") >= 1)
			vecPath = Functions::String::split(path, "/");
		else if (path != "")
			vecPath.push_back(path);
		return vecPath;
	}

	std::ostream & operator<<(std::ostream& stream, const BaseAttribute& attribute)
	{
		stream << attribute.data;
		return stream;
	}

	std::string Types::getDefaultValueForType(Types::DataType type)
	{
		std::string value = "";
		if (type == Types::String) value = "";
		else if (type == Types::Int) value = "0";
		else if (type == Types::Float) value = "0.0";
		else if (type == Types::Bool) value = "False";
		else if (type == Types::Link) value = "&()";
		else if (type == Types::Template) value = "$()";
		return value;
	}

	Types::DataType Types::getVarType(std::string var)
	{
		Types::DataType attributeType;
		std::vector<std::string> boolType = { "True", "False" };
		if (Functions::Vector::isInList(var, boolType))
			attributeType = Types::Bool;
		else if (Functions::String::occurencesInString(var, "..") == 1
				 && Functions::String::isStringInt(Functions::String::split(var, "..")[0])
				 && Functions::String::isStringInt(Functions::String::split(var, "..")[1]))
		{
			attributeType = Types::Range;
		}
		else if (var.substr(0, 2) == "&(" && var.substr(var.size() - 1, 1) == ")")
			attributeType = Types::Link;
		else if (var.substr(0, 1) == "$" && Functions::String::occurencesInString(var, "(") == 1 && var.substr(var.size() - 1, 1) == ")")
			attributeType = Types::Template;
		else if (var.substr(0, 1) == "\"" && var.substr(var.size() - 1, 1) == "\"")
			attributeType = Types::String;
		else if (Functions::String::isStringFloat(var))
			attributeType = Types::Float;
		else if (Functions::String::isStringInt(var))
			attributeType = Types::Int;
		else
			attributeType = Types::Unknown;
		return attributeType;
	}

	Types::DataType Types::stringToDataType(std::string type)
	{
		if (type == "string" || type == "String")
			return Types::String;
		else if (type == "int" || type == "Int")
			return Types::Int;
		else if (type == "float" || type == "Float")
			return Types::Float;
		else if (type == "bool" || type == "Bool")
			return Types::Bool;
		else if (type == "range" || type == "Range")
			return Types::Range;
		else if (type == "template" || type == "Template")
			return Types::Template;
		else
			return Types::Unknown;
	}

	std::string Types::dataTypeToString(Types::DataType type)
	{
		if (type == Types::String) return "String";
		else if (type == Types::Int) return "Int";
		else if (type == Types::Float) return "Float";
		else if (type == Types::Bool) return "Bool";
		else if (type == Types::Range) return "Range";
		else if (type == Types::Template) return "Template";
		else if (type == Types::Unknown) return "Unknown";
	}

	std::string Types::attributeTypeToString(Types::AttributeType type)
	{
		if (type == Types::Attribute) return "Attribute";
		else if (type == Types::ContainerAttribute) return "ContainerAttribute";
		else if (type == Types::BaseAttribute) return "BaseAttribute";
		else if (type == Types::ListAttribute) return "ListAttribute";
		else if (type == Types::ComplexAttribute) return "ComplexAttribute";
		else if (type == Types::LinkAttribute) return "LinkAttribute";
	}

	//Path
	std::string Path()
	{
		return "";
	}
	std::string Path(std::string cPath)
	{
		if (cPath.size() > 0 && Functions::String::extract(cPath, cPath.size() - 1, 0) == "/")
			cPath = Functions::String::extract(cPath, 0, 1);
		return cPath;
	}
	std::string Path(std::vector<std::string> path)
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

	//Attribute
	Attribute::Attribute(ContainerAttribute* parent, const std::string& id, const Types::AttributeType& type)
	{
		this->id = id;
		this->type = type;
		this->parent = parent;
	}
	void Attribute::removeParent(ContainerAttribute* currentParent)
	{
		if (currentParent == parent || parent == nullptr)
			this->parent = nullptr;
		else
			std::cout << "<Error:Attribute:removeParent>[removeParent] : " << currentParent << " is not " << getNodePath() << "parent's" << std::endl;
	}
	void Attribute::setAnnotation(const std::string& annotation)
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
		if (this->parent == nullptr)
			this->parent = parent;
		else
			std::cout << "<Error:Vili:Attribute>[setParent] : Attribute " << getNodePath() << " already has a parent : " << parent->getNodePath() << std::endl;
	}

	std::string Attribute::getNodePath()
	{
		std::vector<std::string> parentChain;
		ContainerAttribute* currentParent = this->getParent();
		while (currentParent != nullptr)
		{
			parentChain.push_back(currentParent->getID() +
								  ((currentParent->getAnnotation() != "") ? "<" + currentParent->getAnnotation() + ">" : ""));
			currentParent = currentParent->getParent();
		}
		std::reverse(parentChain.begin(), parentChain.end());
		parentChain.push_back(this->getID() + ((this->getAnnotation() != "") ? "<" + this->getAnnotation() + ">" : ""));
		return Functions::Vector::join(parentChain, "/");
	}

	unsigned Attribute::getDepth()
	{
		ContainerAttribute* currentParent = this->getParent();
		unsigned int depth = 0;
		while (currentParent != nullptr)
		{
			depth++;
		}
		return depth;
	}

	void Attribute::setID(const std::string& id)
	{
		if (parent != nullptr)
			std::cout << "<Error:Vili:Attribute>[setID] : Can't change ID of " << getNodePath() << " when it has a parent" << std::endl;
		else
			this->id = id;
	}

	ContainerAttribute::ContainerAttribute(ContainerAttribute* parent, const std::string& id, const Types::AttributeType& type) : Attribute(parent, id, type)
	{
	}
	Attribute* ContainerAttribute::removeOwnership(Attribute* element)
	{
		element->removeParent(this);
		return element;
	}

	//BaseAttribute
	BaseAttribute::BaseAttribute(ContainerAttribute* parent, const std::string& id, const Types::DataType& btype, const std::string& bdata) : Attribute(parent, id, Types::BaseAttribute)
	{
		dtype = btype;
		data = bdata;
		this->parent = parent;
	}
	BaseAttribute::BaseAttribute(const std::string& id, const Types::DataType& btype, const std::string& bdata) : Attribute(nullptr, id, Types::BaseAttribute)
	{
		dtype = btype;
		data = bdata;
		this->parent = parent;
	}
	void BaseAttribute::set(int var)
	{
		if (dtype == Types::Int)
			data = std::to_string(var);
		else
			std::cout << "<Error:Vili:BaseAttribute>[setData] : " \
					  << getNodePath() << " is not a <int> BaseAttribute (" << dtype << ")" << std::endl;
	}
	void BaseAttribute::set(double var)
	{
		if (dtype == Types::Float)
			data = std::to_string(var);
		else
			std::cout << "<Error:Vili:BaseAttribute>[setData] : " \
					  << getNodePath() << " is not a <float> BaseAttribute (" << dtype << ")" << std::endl;
	}
	void BaseAttribute::set(const std::string& var)
	{
		if (dtype == Types::String)
			data = var;
		else
			std::cout << "<Error:Vili:BaseAttribute>[setData] : " \
					  << getNodePath() << " is not a <string> BaseAttribute (" << dtype << ")" << std::endl;
	}
	void BaseAttribute::set(bool var)
	{
		if (dtype == Types::Bool)
		{
			if (var)
				data = "True";
			else
				data = "False";
		}
		else
			std::cout << "<Error:Vili:BaseAttribute>[setData] : " \
					  << getNodePath() << " is not a <bool> BaseAttribute (" << dtype << ")" << std::endl;
	}
	void BaseAttribute::autoset(std::string rawData)
	{
		if (Types::getVarType(rawData) == dtype)
			data = rawData;
		if (dtype == Types::String)
			data = Functions::String::extract(data, 1, 1);
	}
	std::string BaseAttribute::returnData()
	{
		if (dtype != Types::String)
			return data;
		else
			return "\"" + data + "\"";
	}
	Types::DataType BaseAttribute::getDataType()
	{
		return dtype;
	}
	void BaseAttribute::copy(ContainerAttribute* newParent, std::string newid)
	{
		if (newParent->getType() == Types::ListAttribute)
		{
			if (dtype == Types::Int)
				dynamic_cast<ListAttribute*>(newParent)->push(this->get<int>());
			else if (dtype == Types::Float)
				dynamic_cast<ListAttribute*>(newParent)->push(this->get<double>());
			else if (dtype == Types::Bool)
				dynamic_cast<ListAttribute*>(newParent)->push(this->get<bool>());
			else if (dtype == Types::String)
				dynamic_cast<ListAttribute*>(newParent)->push(this->get<std::string>());
		}
		else if (newParent->getType() == Types::ComplexAttribute)
			dynamic_cast<ComplexAttribute*>(newParent)->createBaseAttribute((newid == "") ? this->id : newid, this->dtype, this->data);
	}
	void BaseAttribute::write(std::ofstream* file, unsigned int depth)
	{
		for (unsigned int j = 0; j < depth; j++)
			(*file) << "    ";
		std::string returnedData = returnData();
		if (dtype == Types::Float)
		{
			while (returnedData.back() == '0')
				returnedData.pop_back();
			if (returnedData.back() == '.')
				returnedData.pop_back();
		}
		if (id.front() != '#')
			(*file) << id << ":" << returnedData << std::endl;
		else
			(*file) << returnedData << std::endl;
	}
	BaseAttribute::operator std::string()
	{
		if (dtype == Types::String)
			return data;
		else
			std::cout << "<Error:Vili:BaseAttribute>[cast<string>] : BaseAttribute " << id << " can't be casted into a string" << std::endl;
	}
	BaseAttribute::operator int()
	{
		if (dtype == Types::Int)
			return get<int>();
		else
			std::cout << "<Error:Vili:BaseAttribute>[cast<int>] : BaseAttribute " << id << " can't be casted into a int" << std::endl;
	}
	BaseAttribute::operator double()
	{
		if (dtype == Types::Float)
			return get<double>();
		else
			std::cout << "<Error:Vili:BaseAttribute>[cast<double>] : BaseAttribute " << id << " can't be casted into a double" << std::endl;
	}
	BaseAttribute::operator bool()
	{
		if (dtype == Types::Bool)
			return get<bool>();
		else
			std::cout << "<Error:Vili:BaseAttribute>[cast<bool>] : BaseAttribute " << id << " can't be casted into a bool" << std::endl;
	}

	//LinkAttribute
	LinkAttribute::LinkAttribute(ComplexAttribute* parent, const std::string& id, const std::string& path) : Attribute(parent, id, Types::LinkAttribute)
	{
		this->path = path;
	}
	Attribute* LinkAttribute::getTarget()
	{
		std::string linkroot = "";
		ComplexAttribute* complexParent = dynamic_cast<ComplexAttribute*>(parent);
		if (complexParent->contains(Types::BaseAttribute, "__linkroot__"))
			linkroot = complexParent->getBaseAttribute("__linkroot__")->get<std::string>();
		ContainerAttribute* root = this->getParent();
		while (root->getParent() != nullptr)
			root = root->getParent();
		std::string abspath = linkroot + "/" + path;
		Attribute* location = root;
		std::vector<std::string> fullPath = Functions::String::split(abspath, "/");
		for (std::string pathPart : fullPath)
		{
			if (location->getType() == Types::ComplexAttribute)
			{
				ComplexAttribute* complexLocation = (ComplexAttribute*)location;
				if (complexLocation->contains(Types::ComplexAttribute, pathPart))
					location = complexLocation->getComplexAttribute(pathPart);
				else if (complexLocation->contains(Types::BaseAttribute, pathPart))
				{
					location = complexLocation->getBaseAttribute(pathPart);
					break;
				}
				else if (complexLocation->contains(Types::ListAttribute, pathPart))
					location = complexLocation->getListAttribute(pathPart);
				else
				{
					std::cout << "<Error:Vili:LinkAttribute>[update] : Path doesn't exist : '" << path << "' (" << pathPart << ")" << std::endl;
					break;
				}
			}
			else if (location->getType() == Types::ListAttribute)
			{
				ListAttribute* listLocation = (ListAttribute*)location;
				if (Functions::String::isStringInt(pathPart) && std::stoi(pathPart) < listLocation->getSize())
					location = listLocation->get(std::stoi(pathPart));
				else
				{
					std::cout << "<Error:Vili:LinkAttribute>[update] : ListAttribute at path '" << path << "' doesn't contain index (" << pathPart << ")" << std::endl;
					break;
				}
			}
		}
		return location;
	}
	std::string LinkAttribute::getPath()
	{
		return path;
	}
	std::string LinkAttribute::getFullPath()
	{
		std::string linkroot = "";
		ComplexAttribute* complexParent = dynamic_cast<ComplexAttribute*>(parent);
		if (complexParent->contains(Types::BaseAttribute, "__linkroot__"))
			linkroot = complexParent->getBaseAttribute("__linkroot__")->get<std::string>();
		return linkroot + "/" + path;

	}
	void LinkAttribute::apply()
	{
		ComplexAttribute* complexParent = dynamic_cast<ComplexAttribute*>(parent);
		complexParent->deleteLinkAttribute(id);

		if (getTarget()->getType() == Types::ComplexAttribute)
			dynamic_cast<ComplexAttribute*>(getTarget())->copy(complexParent, id);
		else if (getTarget()->getType() == Types::ListAttribute)
			dynamic_cast<ListAttribute*>(getTarget())->copy(complexParent, id);
		else if (getTarget()->getType() == Types::BaseAttribute)
			dynamic_cast<BaseAttribute*>(getTarget())->copy(complexParent, id);
		else if (getTarget()->getType() == Types::LinkAttribute)
			dynamic_cast<LinkAttribute*>(getTarget())->copy(complexParent, id);
	}
	bool LinkAttribute::operator==(LinkAttribute compare)
	{
		return (this->getFullPath() == compare.getFullPath());
	}

	void LinkAttribute::copy(ContainerAttribute* newParent, std::string newid)
	{
		if (newParent->getType() == Types::ComplexAttribute)
			dynamic_cast<ComplexAttribute*>(newParent)->createLinkAttribute((newid == "") ? this->id : newid, this->path);
		else
			std::cout << "<Error:Vili:LinkAttribute>[copy] : Can't copy a LinkAttribute outside a ComplexAttribute (" << getNodePath() << ")" << std::endl;
	}
	void LinkAttribute::write(std::ofstream* file, unsigned int depth)
	{
		for (unsigned int j = 0; j < depth; j++)
			(*file) << "    ";
		(*file) << id << ":&(" << getPath() << ")" << std::endl;
	}

	//ListAttribute
	ListAttribute::ListAttribute(ContainerAttribute* parent, const std::string& id) : ContainerAttribute(parent, id, Types::ListAttribute)
	{
	}
	ListAttribute::ListAttribute(const std::string& id) : ContainerAttribute(nullptr, id, Types::ListAttribute)
	{
	}
	unsigned int ListAttribute::getSize()
	{
		return dataList.size();
	}
	BaseAttribute* ListAttribute::get(unsigned int index)
	{
		if (index < dataList.size())
			return dataList[index].get();
		else
			std::cout << "<Error:Vili:ListAttribute>[get] : Can't access index " << index << " of " \
					  << getNodePath() << " (Size:" << dataList.size() << ")" << std::endl;
	}
	std::vector<BaseAttribute*>::iterator ListAttribute::begin()
	{
		iteratorCache.clear();
		for (int i = 0; i < dataList.size(); i++)
			iteratorCache.push_back(dataList[i].get());
		return iteratorCache.begin();
	}
	std::vector<BaseAttribute*>::iterator ListAttribute::end()
	{
		return iteratorCache.end();
	}
	void ListAttribute::push(const std::string& element)
	{
		dataList.push_back(std::make_unique<BaseAttribute>(this, "#" + std::to_string(dataList.size()), Types::String, element));
	}
	void ListAttribute::push(const int& element)
	{
		dataList.push_back(std::make_unique<BaseAttribute>(this, "#" + std::to_string(dataList.size()), Types::Int, std::to_string(element)));
	}
	void ListAttribute::push(const bool& element)
	{
		dataList.push_back(std::make_unique<BaseAttribute>(this, "#" + std::to_string(dataList.size()), Types::Bool, (element == true) ? "True" : "False"));
	}
	void ListAttribute::push(const double& element)
	{
		dataList.push_back(std::make_unique<BaseAttribute>(this, "#" + std::to_string(dataList.size()), Types::Float, std::to_string(element)));
	}
	void ListAttribute::insert(unsigned int index, const std::string& element)
	{
		dataList.insert(dataList.begin() + index, std::make_unique<BaseAttribute>(this, "#" + std::to_string(dataList.size()), Types::String, element));
		for (int i = index + 1; i < dataList.size(); i++)
		{
			this->removeOwnership(dataList[i].get());
			dataList[i]->setID("#" + std::to_string(i));
			dataList[i]->setParent(this);
		}
	}
	void ListAttribute::insert(unsigned int index, const int& element)
	{
		dataList.insert(dataList.begin() + index, std::make_unique<BaseAttribute>(this, "#" + std::to_string(dataList.size()), Types::Int, std::to_string(element)));
		for (int i = index + 1; i < dataList.size(); i++)
		{
			this->removeOwnership(dataList[i].get());
			dataList[i]->setID("#" + std::to_string(i));
			dataList[i]->setParent(this);
		}
	}
	void ListAttribute::insert(unsigned int index, const bool& element)
	{
		dataList.insert(dataList.begin() + index, std::make_unique<BaseAttribute>(this, "#" + std::to_string(dataList.size()), Types::Bool, (element == true) ? "True" : "False"));
		for (int i = index + 1; i < dataList.size(); i++)
		{
			this->removeOwnership(dataList[i].get());
			dataList[i]->setID("#" + std::to_string(i));
			dataList[i]->setParent(this);
		}
	}
	void ListAttribute::insert(unsigned int index, const double& element)
	{
		dataList.insert(dataList.begin() + index, std::make_unique<BaseAttribute>(this, "#" + std::to_string(dataList.size()), Types::Float, std::to_string(element)));
		for (int i = index + 1; i < dataList.size(); i++)
		{
			this->removeOwnership(dataList[i].get());
			dataList[i]->setID("#" + std::to_string(i));
			dataList[i]->setParent(this);
		}
	}
	void ListAttribute::clear()
	{
		dataList.clear();
	}
	void ListAttribute::erase(unsigned int index)
	{
		dataList.erase(dataList.begin() + index);
	}
	Attribute* ListAttribute::extractElement(Attribute* element)
	{
		if (Functions::Vector::isInList(std::unique_ptr<BaseAttribute>(dynamic_cast<BaseAttribute*>(element)), dataList))
		{
			this->removeOwnership(element);
			int indexToRelease = Functions::Vector::indexOfElement(std::unique_ptr<BaseAttribute>(dynamic_cast<BaseAttribute*>(element)), dataList);
			dataList[indexToRelease].release();
			Functions::Vector::eraseAll(dataList, std::unique_ptr<BaseAttribute>(dynamic_cast<BaseAttribute*>(element)));
		}
		return element;
	}
	void ListAttribute::copy(ContainerAttribute* newParent, std::string newid)
	{
		if (newParent->getType() == Types::ComplexAttribute)
		{
			std::string useID = (newid == "") ? this->id : newid;
			dynamic_cast<ComplexAttribute*>(newParent)->createListAttribute(useID);
			for (int i = 0; i < dataList.size(); i++)
				dataList[i]->copy(dynamic_cast<ComplexAttribute*>(newParent)->getListAttribute(useID));
		}
		else
			std::cout << "<Error:Vili:ListAttribute>[copy] : Can't copy a ListAttribute outside a ComplexAttribute (" << getNodePath() << ")" << std::endl;
	}
	void ListAttribute::write(std::ofstream* file, unsigned int depth)
	{
		for (unsigned int j = 0; j < depth; j++)
			(*file) << "    ";
		(*file) << id << ":[" << std::endl;
		for (unsigned int k = 0; k < getSize(); k++)
			get(k)->write(file, depth + 1);
		for (unsigned int l = 0; l < depth; l++)
			(*file) << "    ";
		(*file) << "]" << std::endl;
	}


	//ComplexAttribute
	ComplexAttribute::ComplexAttribute(ComplexAttribute* parent, const std::string& id) : ContainerAttribute(parent, id, Types::ComplexAttribute)
	{
		this->parent = parent;
	}
	ComplexAttribute::ComplexAttribute(ComplexAttribute* parent, const std::string& id, ComplexAttribute* herit)
		: ContainerAttribute(parent, id, Types::ComplexAttribute)
	{
		this->parent = parent;
		this->heritage(herit);
	}
	ComplexAttribute::ComplexAttribute(ComplexAttribute* parent, const std::string& id, std::vector<ComplexAttribute*>* multipleHerit)
		: ContainerAttribute(parent, id, Types::ComplexAttribute)
	{
		this->parent = parent;
		for (unsigned int i = 0; i < multipleHerit->size(); i++)
			this->heritage(multipleHerit->at(i));
	}
	ComplexAttribute::ComplexAttribute(const std::string& id) : ContainerAttribute(nullptr, id, Types::ComplexAttribute)
	{
	}
	ComplexAttribute::ComplexAttribute(const std::string& id, ComplexAttribute* herit) : ContainerAttribute(nullptr, id, Types::ComplexAttribute)
	{
		this->heritage(herit);
	}
	ComplexAttribute::ComplexAttribute(const std::string& id, std::vector<ComplexAttribute*>* multipleHerit)
		: ContainerAttribute(nullptr, id, Types::ComplexAttribute)
	{
		for (unsigned int i = 0; i < multipleHerit->size(); i++)
			this->heritage(multipleHerit->at(i));
	}
	Attribute* ComplexAttribute::extractElement(Attribute* element)
	{
		if (Functions::Vector::isInList(element->getID(), childAttributesNames))
		{
			this->removeOwnership(element);
			childAttributes[element->getID()].release();
			childAttributes.erase(element->getID());
			Functions::Vector::eraseAll(childAttributesNames, element->getID());
		}
		else
			std::cout << "<Error:Vili:ComplexAttribute>[extractElement] : " << this->getID() << " doesn't contain Attribute " << element->getID() << std::endl;
		return element;
	}
	void ComplexAttribute::heritage(ComplexAttribute* heritTarget)
	{
		for (auto& child : heritTarget->getAll(Types::Attribute))
			heritTarget->get(child)->copy(this);
	}
	ComplexAttribute& ComplexAttribute::operator[](const std::string& cPath)
	{
		return (*getPath(cPath));
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
		if (sPath.size() > 0)
		{
			int pathIndex = 1;
			ComplexAttribute* getToPath;
			getToPath = this->getComplexAttribute(sPath[0]);
			while (pathIndex != sPath.size())
			{
				getToPath = getToPath->getComplexAttribute(sPath[pathIndex]);
				pathIndex++;
			}
			return getToPath;
		}
		else
			return this;
	}
	Attribute* ComplexAttribute::get(const std::string& attributeID)
	{
		if (childAttributes.find(attributeID) != childAttributes.end())
			return childAttributes[attributeID].get();
		else
			std::cout << "<Error:Vili:ComplexAttribute>[get] : Can't find Attribute " << attributeID << " in " << getNodePath() << std::endl;
	}
	BaseAttribute* ComplexAttribute::getBaseAttribute(const std::string& attributeID)
	{
		if (childAttributes.find(attributeID) != childAttributes.end() && childAttributes[attributeID]->getType() == Types::BaseAttribute)
			return dynamic_cast<BaseAttribute*>(childAttributes[attributeID].get());
		else
		{
			std::cout << "<Error:Vili:ComplexAttribute>[getBaseAttribute] : Can't find BaseAttribute "
					  << attributeID << " in " << getNodePath() << std::endl;
		}
	}
	ListAttribute* ComplexAttribute::getListAttribute(const std::string& attributeID)
	{
		if (childAttributes.find(attributeID) != childAttributes.end() && childAttributes[attributeID]->getType() == Types::ListAttribute)
			return dynamic_cast<ListAttribute*>(childAttributes[attributeID].get());
		else
		{
			std::cout << "<Error:Vili:ComplexAttribute>[getListAttribute] : Can't find ListAttribute "
					  << attributeID << " in " << getNodePath() << std::endl;
		}
	}
	LinkAttribute* ComplexAttribute::getLinkAttribute(const std::string& attributeID)
	{
		if (childAttributes.find(attributeID) != childAttributes.end() && childAttributes[attributeID]->getType() == Types::LinkAttribute)
			return dynamic_cast<LinkAttribute*>(childAttributes[attributeID].get());
		else
		{
			std::cout << "<Error:Vili:ComplexAttribute>[getLinkAttribute] : Can't find LinkAttribute "
					  << attributeID << " in " << getNodePath() << std::endl;
		}
	}
	ComplexAttribute* ComplexAttribute::getComplexAttribute(const std::string& attributeID)
	{
		if (!childAttributes.empty() && childAttributes.find(attributeID) != childAttributes.end() && childAttributes[attributeID]->getType() == Types::ComplexAttribute)
			return dynamic_cast<ComplexAttribute*>(childAttributes[attributeID].get());
		else
		{
			std::cout << "<Error:Vili:ComplexAttribute>[getComplexAttribute] : Can't find ComplexAttribute "
					  << attributeID << " in " << getNodePath() << std::endl;
		}
	}
	Types::AttributeType ComplexAttribute::getAttributeType(const std::string& attributeID)
	{
		if (childAttributes.find(attributeID) != childAttributes.end())
			return childAttributes[attributeID]->getType();
		else
			std::cout << "<Error:Vili:ComplexAttribute>[getAttributeType] : Attribute " << attributeID << " does not exists" << std::endl;
	}
	std::vector<std::string> ComplexAttribute::getAll(Types::AttributeType searchType)
	{
		std::vector<std::string> attributes;
		for (std::string attributeID : this->childAttributesNames)
		{
			if (this->childAttributes[attributeID]->getType() == searchType)
				attributes.push_back(attributeID);
			else if (searchType == Types::Attribute)
				attributes.push_back(attributeID);
			else if (searchType == Types::ContainerAttribute && this->childAttributes[attributeID]->getType() == Types::ComplexAttribute)
				attributes.push_back(attributeID);
			else if (searchType == Types::ContainerAttribute && this->childAttributes[attributeID]->getType() == Types::ListAttribute)
				attributes.push_back(attributeID);
		}
		return attributes;
	}
	bool ComplexAttribute::contains(Types::AttributeType searchType, const std::string & attributeID)
	{
		if (childAttributes.find(attributeID) != childAttributes.end() && childAttributes[attributeID]->getType() == searchType)
			return true;
		else
			return false;
	}
	bool ComplexAttribute::contains(const std::string& attributeID)
	{
		if (childAttributes.find(attributeID) != childAttributes.end())
			return true;
		else
			return false;
	}
	void ComplexAttribute::createBaseAttribute(const std::string& attributeID, const Types::DataType& type, const std::string& data)
	{
		childAttributes[attributeID] = std::make_unique<BaseAttribute>(this, attributeID, type, data);
		if (!Functions::Vector::isInList(attributeID, childAttributesNames))
			childAttributesNames.push_back(attributeID);
	}
	void ComplexAttribute::createBaseAttribute(const std::string& attributeID, const std::string& data)
	{
		childAttributes[attributeID] = std::make_unique<BaseAttribute>(this, attributeID, Types::String, data);
		if (!Functions::Vector::isInList(attributeID, childAttributesNames))
			childAttributesNames.push_back(attributeID);
	}
	void ComplexAttribute::createBaseAttribute(const std::string& attributeID, bool data)
	{
		childAttributes[attributeID] = std::make_unique<BaseAttribute>(this, attributeID, Types::Bool, (data == true ? "True" : "False"));
		if (!Functions::Vector::isInList(attributeID, childAttributesNames))
			childAttributesNames.push_back(attributeID);
	}
	void ComplexAttribute::createBaseAttribute(const std::string& attributeID, int data)
	{
		childAttributes[attributeID] = std::make_unique<BaseAttribute>(this, attributeID, Types::Int, std::to_string(data));
		if (!Functions::Vector::isInList(attributeID, childAttributesNames))
			childAttributesNames.push_back(attributeID);
	}
	void ComplexAttribute::createBaseAttribute(const std::string& attributeID, double data)
	{
		childAttributes[attributeID] = std::make_unique<BaseAttribute>(this, attributeID, Types::Float, std::to_string(data));
		if (!Functions::Vector::isInList(attributeID, childAttributesNames))
			childAttributesNames.push_back(attributeID);
	}
	void ComplexAttribute::pushBaseAttribute(BaseAttribute* attribute)
	{
		childAttributes[attribute->getID()] = std::unique_ptr<BaseAttribute>(attribute);
		if (!Functions::Vector::isInList(attribute->getID(), childAttributesNames))
			childAttributesNames.push_back(attribute->getID());
	}
	void ComplexAttribute::createListAttribute(const std::string& attributeID)
	{
		childAttributes[attributeID] = std::make_unique<ListAttribute>(this, attributeID);
		if (!Functions::Vector::isInList(attributeID, childAttributesNames))
			childAttributesNames.push_back(attributeID);
	}
	void ComplexAttribute::pushListAttribute(ListAttribute* attribute)
	{
		childAttributes[attribute->getID()] = std::unique_ptr<ListAttribute>(attribute);
		if (!Functions::Vector::isInList(attribute->getID(), childAttributesNames))
			childAttributesNames.push_back(attribute->getID());
	}
	void ComplexAttribute::createComplexAttribute(const std::string& attributeID)
	{
		childAttributes[attributeID] = std::make_unique<ComplexAttribute>(this, attributeID);
		if (!Functions::Vector::isInList(attributeID, childAttributesNames))
			childAttributesNames.push_back(attributeID);
	}
	void ComplexAttribute::pushComplexAttribute(ComplexAttribute* attribute)
	{
		childAttributes[attribute->getID()] = std::unique_ptr<ComplexAttribute>(attribute);
		if (!Functions::Vector::isInList(attribute->getID(), childAttributesNames))
			childAttributesNames.push_back(attribute->getID());
	}
	void ComplexAttribute::createLinkAttribute(const std::string& attributeID, const std::string& path)
	{
		childAttributes[attributeID] = std::make_unique<LinkAttribute>(this, attributeID, path);
		if (!Functions::Vector::isInList(attributeID, childAttributesNames))
			childAttributesNames.push_back(attributeID);
	}
	void ComplexAttribute::pushLinkAttribute(LinkAttribute* attribute)
	{
		childAttributes[attribute->getID()] = std::unique_ptr<LinkAttribute>(attribute);
		if (!Functions::Vector::isInList(attribute->getID(), childAttributesNames))
			childAttributesNames.push_back(attribute->getID());
	}
	void ComplexAttribute::write(std::ofstream* file, unsigned int depth)
	{
		for (unsigned int i = 0; i < depth; i++)
			(*file) << "    ";
		if (depth)
			(*file) << "@" << id << std::endl;
		else
			(*file) << id << ":" << std::endl;
		for (auto& child : childAttributesNames)
			childAttributes[child]->write(file, depth + 1);
		if (depth == 0)
			(*file) << std::endl;
	}
	void ComplexAttribute::deleteBaseAttribute(const std::string& attributeID, bool freeMemory)
	{
		if (Functions::Vector::isInList(attributeID, this->getAll(Types::BaseAttribute)))
			childAttributesNames.erase(childAttributesNames.begin() + Functions::Vector::indexOfElement(attributeID, childAttributesNames));
		typedef std::map<std::string, std::unique_ptr<Attribute>>::iterator it_type;
		it_type itDel = childAttributes.find(attributeID);
		if (itDel != childAttributes.end() && childAttributes[attributeID]->getType() == Types::BaseAttribute)
		{
			if (!freeMemory)
				childAttributes[attributeID].release();
			childAttributes.erase(itDel);
		}
	}
	void ComplexAttribute::deleteComplexAttribute(const std::string& attributeID, bool freeMemory)
	{
		if (Functions::Vector::isInList(attributeID, this->getAll(Types::ComplexAttribute)))
			childAttributesNames.erase(childAttributesNames.begin() + Functions::Vector::indexOfElement(attributeID, childAttributesNames));
		typedef std::map<std::string, std::unique_ptr<Attribute>>::iterator it_type;
		it_type itDel = childAttributes.find(attributeID);
		if (itDel != childAttributes.end() && childAttributes[attributeID]->getType() == Types::ComplexAttribute)
		{
			if (!freeMemory)
				childAttributes[attributeID].release();
			childAttributes.erase(itDel);
		}
	}
	void ComplexAttribute::deleteListAttribute(const std::string& attributeID, bool freeMemory)
	{
		if (Functions::Vector::isInList(attributeID, this->getAll(Types::ListAttribute)))
			childAttributesNames.erase(childAttributesNames.begin() + Functions::Vector::indexOfElement(attributeID, childAttributesNames));
		typedef std::map<std::string, std::unique_ptr<Attribute>>::iterator it_type;
		it_type itDel = childAttributes.find(attributeID);
		if (itDel != childAttributes.end() && childAttributes[attributeID]->getType() == Types::ListAttribute)
		{
			if (!freeMemory)
				childAttributes[attributeID].release();
			childAttributes.erase(itDel);
		}
	}
	void ComplexAttribute::deleteLinkAttribute(const std::string& attributeID, bool freeMemory)
	{
		if (Functions::Vector::isInList(attributeID, this->getAll(Types::LinkAttribute)))
			childAttributesNames.erase(childAttributesNames.begin() + Functions::Vector::indexOfElement(attributeID, childAttributesNames));
		typedef std::map<std::string, std::unique_ptr<Attribute>>::iterator it_type;
		it_type itDel = childAttributes.find(attributeID);
		if (itDel != childAttributes.end() && childAttributes[attributeID]->getType() == Types::LinkAttribute)
		{
			if (!freeMemory)
				childAttributes[attributeID].release();
			childAttributes.erase(itDel);
		}
	}
	void ComplexAttribute::copy(ContainerAttribute* newParent, std::string newid)
	{
		std::string useID = (newid == "") ? this->id : newid;
		if (newParent->getType() == Types::ComplexAttribute)
		{
			dynamic_cast<ComplexAttribute*>(newParent)->createComplexAttribute(useID);
			for (auto& child : childAttributesNames)
			{
				childAttributes[child]->copy(dynamic_cast<ComplexAttribute*>(newParent)->getComplexAttribute(useID));
			}
		}
		else
			std::cout << "<Error:Vili:ComplexAttribute>[copy] : Can't copy a ComplexAttribute outside a ComplexAttribute (" << getNodePath() << ")" << std::endl;
	}
	void ComplexAttribute::walk(std::function<void(ComplexAttribute*)> walkFunction)
	{
		for (std::string& complex : getAll(Types::ComplexAttribute))
			this->getComplexAttribute(complex)->walk(walkFunction);
		walkFunction(this);
	}

	//AttributeConstraintManager
	AttributeConstraintManager::AttributeConstraintManager(ComplexAttribute* parent, std::string path) : attribute(parent, "link", path)
	{
	}
	void AttributeConstraintManager::addConstraint(std::function<bool(BaseAttribute*)> constraint)
	{
		constraints.push_back(constraint);
	}
	bool AttributeConstraintManager::checkAllConstraints()
	{
		for (std::function<bool(BaseAttribute*)>& constraint : constraints)
		{
			if (!constraint(attribute.get<BaseAttribute*>()))
				return false;
		}
		if (attribute.get<BaseAttribute*>()->getAnnotation() != "Set")
			return false;
		attribute.get<BaseAttribute*>()->setAnnotation("UnSet");
		return true;
	}
	LinkAttribute* AttributeConstraintManager::getLinkAttribute()
	{
		return &attribute;
	}
	std::string AttributeConstraintManager::getArgumentPath()
	{
		return attribute.getFullPath();
	}

	//DataTemplate
	DataTemplate::DataTemplate() : body("root")
	{
	}
	ComplexAttribute* DataTemplate::getBody()
	{
		return &body;
	}
	void DataTemplate::build(ComplexAttribute* parent, const std::string& id)
	{
		if (checkSignature())
		{
			body.at("__body__")->copy(parent, id);
			std::vector<LinkAttribute*> attributeAddresses;
			for (AttributeConstraintManager& constraintManager : signature)
				attributeAddresses.push_back(constraintManager.getLinkAttribute());
			parent->getComplexAttribute(id)->walk([attributeAddresses](ComplexAttribute* complex)
			{
				for (int i = 0; i < complex->getAll(Types::LinkAttribute).size(); i++)
				{
					for (int j = 0; j < attributeAddresses.size(); j++)
					{
						if ((*complex->getLinkAttribute(complex->getAll(Types::LinkAttribute)[i])) == (*attributeAddresses[j]))
							complex->getLinkAttribute(complex->getAll(Types::LinkAttribute)[i])->apply();
					}
				}
			});
			if (defaultLinkRoot)
				parent->at(id)->deleteBaseAttribute("__linkroot__");
		}
		else
			std::cout << "<Error:Vili:DataTemplate>[build] : Type / Constraint mismatch in Template building for element " << id << std::endl;
	}
	bool DataTemplate::checkSignature()
	{
		for (AttributeConstraintManager& constraintManager : signature)
		{
			if (!constraintManager.checkAllConstraints())
				return false;
		}
		return true;
	}
	void DataTemplate::addConstraintManager(AttributeConstraintManager constraintManager, bool facultative)
	{
		if (facultative)
		{
			signatureEnd = true;
			signature.push_back(constraintManager);
		}
		else if (!facultative && !signatureEnd)
			signature.push_back(constraintManager);
		else
			std::cout << "<Error:Vili:DataTemplate>[addConstraintManager] : Can't use a facultative argument after a non-facultative argument (" << signature.size() << ")" << std::endl;
	}
	void DataTemplate::useDefaultLinkRoot()
	{
		defaultLinkRoot = true;
	}

	//DataParser
	DataParser::DataParser()
	{
		root = std::make_unique<ComplexAttribute>("root");
		root->setAnnotation("NoFile");
	}
	DataParser::DataParser(std::string file)
	{
		root = std::make_unique<ComplexAttribute>("root");
		root->setAnnotation("NoFile");
		parseFile(file);
	}
	ComplexAttribute* DataParser::operator->()
	{
		return root.get();
	}
	void DataParser::createFlag(const std::string& flag)
	{
		flagList.push_back(flag);
	}
	bool DataParser::hasFlag(const std::string& flagName)
	{
		return std::find(flagList.begin(), flagList.end(), flagName) != flagList.end();
	}
	unsigned int DataParser::getAmountOfFlags()
	{
		return flagList.size();
	}
	std::string DataParser::getFlagAtIndex(int index)
	{
		return flagList[index];
	}
	ComplexAttribute* DataParser::getPath(std::string path)
	{
		if (path.size() > 0 && Functions::String::extract(path, path.size() - 1, 0) == "/")
			path = Functions::String::extract(path, 0, 1);
		if (Functions::String::occurencesInString(path, "/") > 0)
		{
			std::vector<std::string> splittedPath = Functions::String::split(path, "/");
			std::string subPath = Functions::Vector::join(splittedPath, "/", 1);
			return getPath(Functions::String::split(path, "/")[0])->at(subPath);
		}
		else
			return getRootChild(path);
	}
	ComplexAttribute* DataParser::getRootChild(std::string child)
	{
		if (child == "")
			return root.get();
		else
			return root->getComplexAttribute(child);
	}
	ComplexAttribute& DataParser::operator[](std::string cPath)
	{
		return (*getPath(cPath));
	}
	ComplexAttribute* DataParser::at(std::string cPath)
	{
		if (cPath.size() > 0 && Functions::String::extract(cPath, cPath.size() - 1, 0) == "/")
			cPath = Functions::String::extract(cPath, 0, 1);
		return getPath(cPath);
	}
	bool DataParser::parseFile(const std::string& filename, bool verbose)
	{
		std::ifstream useFile;
		useFile.open(filename);
		std::string currentLine;
		std::vector<std::string> addPath = {};
		unsigned int spacing = 4;
		std::string curCat = "None";
		std::string curList = "None";
		int curListIndent = 0;
		if (useFile.is_open())
		{
			if (verbose) std::cout << "Start Parsing File : " << filename << std::endl;
			while (!safeGetline(useFile, currentLine).eof())
			{
				Functions::String::StringExtractor stringsInLine = Functions::String::extractAllStrings(currentLine);
				std::string rawLine = Functions::Vector::join(std::get<1>(stringsInLine), "");
				Functions::String::replaceStringInPlace(rawLine, "	", std::string(spacing, ' '));
				unsigned int currentIndent = 0;
				unsigned int spacingAmount = 0;
				for (int i = 0; i < rawLine.size(); i++)
				{
					if (rawLine[i] == ' ')
					{
						spacingAmount += 1;
						if (spacingAmount == spacing)
						{
							spacingAmount = 0;
							currentIndent += 1;
						}
					}
					else
						break;
				}
				Functions::String::replaceStringInPlace(rawLine, std::string(spacing, ' '), "");
				std::vector<std::string> parsedLines;
				std::string addParsedLine = "";
				for (int i = 0; i < std::get<2>(stringsInLine).size(); i++)
				{
					if (std::get<2>(stringsInLine)[i].first == 0)
						addParsedLine += "\"" + std::get<0>(stringsInLine)[std::get<2>(stringsInLine)[i].second] + "\"";
					else
					{
						std::string removeRawSpacing = Functions::String::replaceString(std::get<1>(stringsInLine)[std::get<2>(stringsInLine)[i].second], "	", "");
						Functions::String::replaceStringInPlace(removeRawSpacing, "	", ""); //Tabs
						Functions::String::replaceStringInPlace(removeRawSpacing, " ", ""); //Spaces
						for (int j = 0; j < removeRawSpacing.size(); j++)
						{
							std::string currentRawChar = removeRawSpacing.substr(j, 1);
							if (currentRawChar == ",")
							{
								parsedLines.push_back(addParsedLine);
								addParsedLine = "";
							}
							else if (currentRawChar == "[")
							{
								parsedLines.push_back(addParsedLine + "[");
								addParsedLine = "";
							}
							else if (currentRawChar == "]")
							{
								parsedLines.push_back(addParsedLine);
								parsedLines.push_back("]");
								addParsedLine = "";
							}
							else
								addParsedLine += currentRawChar;
						}
					}
				}
				parsedLines.push_back(addParsedLine);
				for (std::string parsedLine : parsedLines)
				{
					while (currentIndent < addPath.size() + 1 && addPath.size() > 0)
						addPath.pop_back();
					std::function<std::string()> indenter = [curList, currentIndent, curListIndent]()
					{
						std::string strIndent = "";
						if (curList == "None")
						{
							for (unsigned int p = 0; p <= currentIndent; p++)
								strIndent += "    ";
						}
						else
						{
							for (unsigned int p = 0; p <= curListIndent + 1; p++)
								strIndent += "    ";
						}
						return strIndent;
					};
					if (curList != "None" && parsedLine == "]")
						curList = "None";
					if (parsedLine != "" && currentIndent == 0)
					{
						if (parsedLine.substr(parsedLine.size() - 1, 1) == ":")
						{
							if (verbose) std::cout << indenter() << "Create new RootAttribute : " << parsedLine.substr(0, parsedLine.size() - 1) << std::endl;
							curCat = parsedLine.substr(0, parsedLine.size() - 1);
							root->createComplexAttribute(curCat);
						}
						else if (parsedLine.substr(parsedLine.size() - 1, 1) == ";")
						{
							std::string instructionType = Functions::String::split(parsedLine, "(")[0];
							std::string instructionValue = Functions::String::split(parsedLine, "(")[1];
							instructionValue = Functions::String::split(instructionValue, ")")[0];
							if (instructionType == "Flag")
							{
								flagList.push_back(instructionValue);
								if (verbose) std::cout << indenter() << "Define New Flag : " << instructionValue << std::endl;
							}
							else if (instructionType == "Spacing")
							{
								spacing = std::stoi(instructionValue);
								if (verbose) std::cout << indenter() << "Define New Spacing : " << spacing << std::endl;
							}
							else if (instructionType == "Include")
							{
								if (verbose) std::cout << indenter() << "Include New File : " << instructionValue << std::endl;
								this->parseFile(instructionValue + ".vili", verbose);
							}
							else if (instructionType == "Template")
							{
								if (verbose) std::cout << indenter() << "Creating New Template from : " << instructionValue << std::endl;
								ComplexAttribute* templateBase = getRootChild(instructionValue);
								DataTemplate* newTemplate = new DataTemplate();
								if (templateBase != nullptr)
								{
									if (templateBase->contains(Types::ComplexAttribute, "__init__") && templateBase->contains(Types::ComplexAttribute, "__body__"))
									{
										if (!templateBase->contains(Types::BaseAttribute, "__linkroot__"))
										{
											templateBase->at("__body__")->createBaseAttribute("__linkroot__", "/" + instructionValue + "/__init__");
											newTemplate->useDefaultLinkRoot();
										}

										int i = 0;
										while (true)
										{
											if (templateBase->at("__init__")->contains(Types::ComplexAttribute, std::to_string(i)))
											{
												AttributeConstraintManager newConstraint(templateBase, instructionValue + "/__init__/" + std::to_string(i) + "/value");
												std::string requiredType = templateBase->at("__init__", std::to_string(i))->getBaseAttribute("type")->get<std::string>();
												Types::DataType requiredConstraintType = Types::stringToDataType(requiredType);
												newConstraint.addConstraint([requiredConstraintType](BaseAttribute* attribute) -> bool
												{
													return (attribute->getDataType() == requiredConstraintType);
												});
												if (templateBase->at("__init__", std::to_string(i))->contains(Types::BaseAttribute, "defaultValue"))
												{
													std::string defaultValue = templateBase->at<BaseAttribute>("__init__", std::to_string(i), "defaultValue")->returnData();
													newConstraint.addConstraint([defaultValue](BaseAttribute* attribute) -> bool
													{
														if (attribute->getAnnotation() != "Set") {
															attribute->setAnnotation("Set");
															attribute->autoset(defaultValue);
														}
														return true;
													});
												}
												newTemplate->addConstraintManager(newConstraint);
											}
											else
												break;
											i++;
										}
										templateBase->at("__body__")->copy(newTemplate->getBody());
										templateList[templateBase->getID()] = newTemplate;
									}
									else
										std::cout << indenter() << "<Error:Vili:DataParser>[parseFile] : Can't create Template " 
											<< instructionValue << " without __init__ and __body__ in file" << filename << std::endl;
								}
								else
									std::cout << indenter() << "<Error:Vili:DataParser>[parseFile] : Can't create Template from non-existant RootAttribute " 
										<< instructionValue << " in file " << filename << std::endl;
							}
						}
					}
					else if (curCat != "None" && parsedLine != "" && currentIndent > 0)
					{
						std::vector<std::string> symbolExclusion = { "@", "\"", "#" };

						std::string pushIndicator;
						if (addPath.size() == 0)
							pushIndicator = curCat + ":Root";
						else
							pushIndicator = getRootChild(curCat)->getPath(Path(addPath))->getNodePath();

						if (!Functions::Vector::isInList(parsedLine.substr(0, 1), symbolExclusion) && Functions::String::occurencesInString(parsedLine, ":[") == 1)
						{
							std::string listElementID = Functions::String::split(parsedLine, ":")[0];
							getRootChild(curCat)->getPath(Path(addPath))->createListAttribute(listElementID);
							curList = listElementID;
							curListIndent = currentIndent;
							if (verbose)
							{
								std::cout << indenter() << "Create ListAttribute " << curList << " inside " << pushIndicator << std::endl;
							}
						}
						else if (!Functions::Vector::isInList(parsedLine.substr(0, 1), symbolExclusion) && Functions::String::occurencesInString(parsedLine, ":"))
						{
							std::string attributeID = Functions::String::split(parsedLine, ":")[0];
							std::vector<std::string> splittedLine = Functions::String::split(parsedLine, ":");
							std::string attributeValue = Functions::Vector::join(splittedLine, ":", 1, 0);
							Types::DataType attributeType = Types::getVarType(attributeValue);

							if (attributeType == Types::Link)
							{
								getRootChild(curCat)->getPath(Path(addPath))->createLinkAttribute(attributeID, Functions::String::extract(attributeValue, 2, 1));
								if (verbose)
								{
									std::cout << indenter() << "Create LinkAttribute " << attributeID << " linking to " << attributeValue
										<< " inside " << pushIndicator << " (Type:" << attributeType << ")" << std::endl;
								}
							}
							else if (attributeType == Types::Template)
							{
								std::string templateName = attributeValue.substr(1, attributeValue.size() - 1);
								templateName = Functions::String::split(templateName, "(")[0];
								if (templateList.find(templateName) != templateList.end())
								{
									std::string argPart = Functions::String::split(attributeValue, "(")[1];
									argPart = argPart.substr(0, argPart.size() - 1);
									std::vector<std::string> templateArgs = Functions::String::split(argPart, "|");
									int i = 0;
									for (std::string& arg : templateArgs)
									{
										getRootChild(templateName)->at("__init__", std::to_string(i))->deleteBaseAttribute("value", true);
										std::string realArg = arg;
										if (Types::getVarType(realArg) == Types::String)
											realArg = Functions::String::extract(realArg, 1, 1);
										getRootChild(templateName)->at("__init__", std::to_string(i))->createBaseAttribute("value", Types::getVarType(arg), realArg);
										getRootChild(templateName)->at("__init__", std::to_string(i))->getBaseAttribute("value")->setAnnotation("Set");
										i++;
									}
									templateList[templateName]->build(getRootChild(curCat)->getPath(Path(addPath)), attributeID);
									if (verbose)
									{
										std::cout << indenter() << "Create ComplexAttribute " << attributeID << " from Template <" << templateName
											<< "> inside " << pushIndicator << std::endl;
									}
								}
								else
									std::cout << indenter() << "<Error:Vili:DataParser>[parseFile] : Can't build object from inexistant Template : " 
										<< templateName << " for attribute : " << attributeID << " in file " << filename << std::endl;
							}
							else
							{
								if (attributeType == Types::String)
									attributeValue = Functions::String::extract(attributeValue, 1, 1);

								getRootChild(curCat)->getPath(Path(addPath))->createBaseAttribute(attributeID, attributeType, attributeValue);
								if (verbose)
								{
									std::cout << indenter() << "Create BaseAttribute " << attributeID << "(" << attributeValue;
									std::cout << ") inside " << pushIndicator << " (Type:" << attributeType << ")" << std::endl;
								}
							}
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
								complexToHeritIDList = Functions::String::split(complexToHeritID, "|");

								for (unsigned int i = 0; i < complexToHeritIDList.size(); i++)
								{
									complexToHerit.push_back(getRootChild(curCat)->getComplexAttribute(complexToHeritIDList[i]));
								}
							}
							getRootChild(curCat)->getPath(Path(addPath))->createComplexAttribute(complexElementID);
							if (verbose) std::cout << indenter() << "Create ComplexAttribute @" << complexElementID << " inside " 
								<< pushIndicator << std::endl;
							for (unsigned int i = 0; i < complexToHerit.size(); i++)
							{
								if (verbose) std::cout << indenter() << "    {Herit from : " << complexToHeritIDList[i] << "}" << std::endl;
								getRootChild(curCat)->getPath(Path(addPath))->getComplexAttribute(complexElementID)->heritage(complexToHerit[i]);
							}

							addPath.push_back(complexElementID);
						}
						else if (curList != "None")
						{
							std::string attributeValue = parsedLine;
							Types::DataType attributeType = Types::getVarType(attributeValue);
							if (verbose) std::cout << indenter() << "Create Element #" << getPath(curCat)->getPath(Path(addPath))->getListAttribute(curList)->getSize()
													   << "(" << attributeValue << ") of ListAttribute " << curList << std::endl;
							if (attributeType == Types::String)
							{
								attributeValue = Functions::String::extract(attributeValue, 1, 1);
								getRootChild(curCat)->getPath(Path(addPath))->getListAttribute(curList)->push(attributeValue);
							}
							else if (attributeType == Types::Int)
							{
								getRootChild(curCat)->getPath(Path(addPath))->getListAttribute(curList)->push(std::stoi(attributeValue));
							}
							else if (attributeType == Types::Float)
							{
								getRootChild(curCat)->getPath(Path(addPath))->getListAttribute(curList)->push(std::stod(attributeValue));
							}
							else if (attributeType == Types::Bool)
							{
								getRootChild(curCat)->getPath(Path(addPath))->getListAttribute(curList)->push(((attributeValue == "True") ? true : false));
							}
							else if (attributeType == Types::Range)
							{
								int rStart = std::stoi(Functions::String::split(attributeValue, "..")[0]);
								int rEnd = std::stoi(Functions::String::split(attributeValue, "..")[1]);
								int step = 1;
								if (rStart > rEnd)
									step = -1;
								rEnd += step;
								for (int i = rStart; i != rEnd; i += step)
								{
									getRootChild(curCat)->getPath(Path(addPath))->getListAttribute(curList)->push(i);
								}
							}
							else
							{
								std::cout << "<Error:Vili:DataParser>[parseFile] : Can't append unknown type to list (" << attributeValue << ") in file " << filename << std::endl;
							}
						}
					}
				}
			}
			useFile.close();
			root->setAnnotation(filename);
			if (verbose) std::cout << "Parsed over.." << std::endl;
			return true;
		}
		else
		{
			std::cout << "<Error:Vili:DataParser>[parseFile] : Can't open " << filename << ". File does not exists in file " << filename << std::endl;
			return false;
		}
	}
	void DataParser::writeFile(const std::string& filename, bool verbose)
	{
		std::ofstream outFile;
		outFile.open(filename);
		if (verbose) std::cout << "Writing DataParser's content on file : " << filename << std::endl;
		unsigned int currentDeepness = 1;
		if (verbose && this->getAmountOfFlags() > 0) std::cout << "    Writing Flags..." << std::endl;
		for (unsigned int i = 0; i < this->getAmountOfFlags(); i++)
		{
			outFile << "Flag (" << this->getFlagAtIndex(i) << ");" << std::endl;
			if (verbose) std::cout << "        Write New Flag : " << this->getFlagAtIndex(i) << std::endl;
		}
		if (this->getAmountOfFlags() > 0) outFile << std::endl;
		if (verbose && root->getAll(Types::ComplexAttribute).size() > 0) std::cout << "    Writing RootAttributes..." << std::endl;
		for (std::string& currentRootAttribute : root->getAll(Types::ComplexAttribute))
		{
			if (templateList.find(currentRootAttribute) == templateList.end())
			{
				if (verbose) std::cout << "        Write New RootAttribute : " << currentRootAttribute << std::endl;
				getRootChild(currentRootAttribute)->write(&outFile);
			}
		}
		outFile.close();
	}
}