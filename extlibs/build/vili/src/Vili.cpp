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
				std::vector<std::string> errorIdParts;
				std::string filename = "";
				std::string message = node->getBaseAttribute("message")->get<std::string>();
				ComplexAttribute* currentParent = node;
				while (currentParent != nullptr)
				{
					if (currentParent->contains(Types::BaseAttribute, "where"))
						location.insert(location.begin(), currentParent->getBaseAttribute("where")->get<std::string>());
					if (currentParent->contains(Types::BaseAttribute, "file") && filename == "")
						filename = currentParent->getBaseAttribute("file")->get<std::string>();
					errorIdParts.push_back(currentParent->getID());
					if (currentParent->getParent() != nullptr)
						currentParent = static_cast<ComplexAttribute*>(currentParent->getParent());
					else
						currentParent = nullptr;
				}
				errorIdParts.pop_back();
				std::reverse(errorIdParts.begin(), errorIdParts.end());
				std::string errorId = Functions::Vector::join(errorIdParts, ".");
				aube::ErrorHandler::Load(errorId, filename, location, message);
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
				t += static_cast<char>(c);
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

	std::ostream& operator<<(std::ostream& stream, const BaseAttribute& attribute)
	{
		stream << attribute.m_data;
		return stream;
	}

	void DataParser::setSpacing(unsigned spacing)
	{
		m_spacing = spacing;
	}

	unsigned DataParser::getSpacing() const
	{
		return m_spacing;
	}

	void DataParser::addInclude(const std::string& filename)
	{
		m_includes.push_back(filename);
	}

	std::vector<std::string> DataParser::getIncludes() const
	{
		return m_includes;
	}

	std::string Types::getDefaultValueForType(Types::DataType type)
	{
		std::string value = "";
		if (type == Types::String) value = "";
		else if (type == Types::Int) value = "0";
		else if (type == Types::Float) value = "0.0";
		else if (type == Types::Bool) value = "False";
		else if (type == Types::Link) value = "&()";
		else if (type == Types::Template) value = "T()";
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
		else if (isalpha(var[0]) && Functions::String::occurencesInString(var, "(") == 1 && var.substr(var.size() - 1, 1) == ")")
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
		else return "Error-Unknown";
	}

	std::string Types::attributeTypeToString(Types::AttributeType type)
	{
		if (type == Types::Attribute) return "Attribute";
		else if (type == Types::ContainerAttribute) return "ContainerAttribute";
		else if (type == Types::BaseAttribute) return "BaseAttribute";
		else if (type == Types::ListAttribute) return "ListAttribute";
		else if (type == Types::ComplexAttribute) return "ComplexAttribute";
		else if (type == Types::LinkAttribute) return "LinkAttribute";
		else return "Error-Unknown";
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
		m_id = id;
		m_type = type;
		m_parent = parent;
	}
	void Attribute::removeParent(ContainerAttribute* currentParent)
	{
		if (m_parent == currentParent || m_parent == nullptr)
			m_parent = nullptr;
		else
			throw aube::ErrorHandler::Raise("Vili.Vili.Attribute.WrongParentRemover", { 
				{"wrongparent", currentParent->getNodePath()}, 
				{"path", getNodePath()} 
			});
	}
	void Attribute::setAnnotation(const std::string& annotation)
	{
		m_annotation = annotation;
	}
	std::string Attribute::getAnnotation()
	{
		return m_annotation;
	}
	std::string Attribute::getID()
	{
		return m_id;
	}
	Types::AttributeType Attribute::getType()
	{
		return m_type;
	}
	ContainerAttribute* Attribute::getParent()
	{
		return m_parent;
	}
	void Attribute::setParent(ContainerAttribute* parent)
	{
		if (m_parent == nullptr)
			m_parent = parent;
		else
			throw aube::ErrorHandler::Raise("Vili.Vili.Attribute.AlreadyHaveParent", { {"path", getNodePath()}, {"parent", parent->getNodePath()} });
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
		if (m_parent == nullptr)
			m_id = id;
		else
			throw aube::ErrorHandler::Raise("Vili.Vili.Attribute.ChangeIDWithParent", { {"path", getNodePath()} });
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
	BaseAttribute::BaseAttribute(ContainerAttribute* parent, const std::string& id, const Types::DataType& dataType, const std::string& data) : Attribute(parent, id, Types::BaseAttribute)
	{
		m_dataType = dataType;
		m_data = data;
	}
	BaseAttribute::BaseAttribute(const std::string& id, const Types::DataType& dataType, const std::string& data) : Attribute(nullptr, id, Types::BaseAttribute)
	{
		m_dataType = dataType;
		m_data = data;
	}
	void BaseAttribute::set(int var)
	{
		if (m_dataType == Types::Int)
			m_data = std::to_string(var);
		else
			throw aube::ErrorHandler::Raise("Vili.Vili.BaseAttribute.WrongIntSet", { {"path", getNodePath()}, {"type", dataTypeToString(m_dataType) } });
	}
	void BaseAttribute::set(double var)
	{
		if (m_dataType == Types::Float)
			m_data = std::to_string(var);
		else
			throw aube::ErrorHandler::Raise("Vili.Vili.BaseAttribute.WrongFloatSet", { { "path", getNodePath() },{ "type", dataTypeToString(m_dataType) } });
	}
	void BaseAttribute::set(const std::string& var)
	{
		if (m_dataType == Types::String)
			m_data = var;
		else
			throw aube::ErrorHandler::Raise("Vili.Vili.BaseAttribute.WrongStringSet", { { "path", getNodePath() },{ "type", dataTypeToString(m_dataType) } });
	}
	void BaseAttribute::set(bool var)
	{
		if (m_dataType == Types::Bool)
		{
			if (var)
				m_data = "True";
			else
				m_data = "False";
		}
		else
			throw aube::ErrorHandler::Raise("Vili.Vili.BaseAttribute.WrongBoolSet", { { "path", getNodePath() },{ "type", dataTypeToString(m_dataType) } });
	}
	void BaseAttribute::autoset(std::string rawData)
	{
		if (Types::getVarType(rawData) == m_dataType)
			m_data = rawData;
		if (m_dataType == Types::String)
			m_data = Functions::String::extract(m_data, 1, 1);
	}
	std::string BaseAttribute::returnData() const
	{
		if (m_dataType != Types::String)
			return m_data;
		else
			return "\"" + m_data + "\"";
	}
	Types::DataType BaseAttribute::getDataType() const
	{
		return m_dataType;
	}
	void BaseAttribute::copy(ContainerAttribute* newParent, std::string newid)
	{
		if (newParent->getType() == Types::ListAttribute)
		{
			if (m_dataType == Types::Int)
				static_cast<ListAttribute*>(newParent)->push(this->get<int>());
			else if (m_dataType == Types::Float)
				static_cast<ListAttribute*>(newParent)->push(this->get<double>());
			else if (m_dataType == Types::Bool)
				static_cast<ListAttribute*>(newParent)->push(this->get<bool>());
			else if (m_dataType == Types::String)
				static_cast<ListAttribute*>(newParent)->push(this->get<std::string>());
		}
		else if (newParent->getType() == Types::ComplexAttribute)
			dynamic_cast<ComplexAttribute*>(newParent)->createBaseAttribute((newid == "") ? m_id : newid, m_dataType, m_data);
	}
	void BaseAttribute::write(std::ofstream* file, unsigned int depth)
	{
		for (unsigned int j = 0; j < depth; j++)
			(*file) << "    ";
		std::string returnedData = returnData();
		if (m_dataType == Types::Float)
		{
			while (returnedData.back() == '0')
				returnedData.pop_back();
			if (returnedData.back() == '.')
				returnedData.pop_back();
		}
		if (m_id.front() != '#')
			(*file) << m_id << ":" << returnedData << std::endl;
		else
			(*file) << returnedData << std::endl;
	}
	BaseAttribute::operator std::string()
	{
		if (m_dataType == Types::String)
			return m_data;
		throw aube::ErrorHandler::Raise("Vili.Vili.BaseAttribute.WrongStringCastOperator", { {"path", getNodePath()} });
	}
	BaseAttribute::operator int()
	{
		if (m_dataType == Types::Int)
			return get<int>();
		throw aube::ErrorHandler::Raise("Vili.Vili.BaseAttribute.WrongIntCastOperator", { { "path", getNodePath() } });
	}

	BaseAttribute::operator double()
	{
		if (m_dataType == Types::Float)
			return get<double>();
		throw aube::ErrorHandler::Raise("Vili.Vili.BaseAttribute.WrongFloatCastOperator", { { "path", getNodePath() } });
	}
	BaseAttribute::operator bool()
	{
		if (m_dataType == Types::Bool)
			return get<bool>();
		throw aube::ErrorHandler::Raise("Vili.Vili.BaseAttribute.WrongBoolCastOperator", { { "path", getNodePath() } });
	}

	//LinkAttribute
	LinkAttribute::LinkAttribute(ComplexAttribute* parent, const std::string& id, const std::string& path) : Attribute(parent, id, Types::LinkAttribute)
	{
		m_path = path;
	}
	Attribute* LinkAttribute::getTarget()
	{
		std::string linkroot = "";
		ComplexAttribute* complexParent = dynamic_cast<ComplexAttribute*>(m_parent);
		if (complexParent->contains(Types::BaseAttribute, "__linkroot__"))
			linkroot = complexParent->getBaseAttribute("__linkroot__")->get<std::string>();
		ContainerAttribute* root = this->getParent();
		while (root->getParent() != nullptr)
			root = root->getParent();
		std::string abspath = linkroot + "/" + m_path;
		Attribute* location = root;
		std::vector<std::string> fullPath = Functions::String::split(abspath, "/");
		for (std::string pathPart : fullPath)
		{
			if (location->getType() == Types::ComplexAttribute)
			{
				ComplexAttribute* complexLocation = static_cast<ComplexAttribute*>(location);
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
					throw aube::ErrorHandler::Raise("Vili.Vili.LinkAttribute.WrongLinkPath", { {"path", getNodePath()}, {"target", m_path}, {"pathpart", pathPart} });
			}
			else if (location->getType() == Types::ListAttribute)
			{
				ListAttribute* listLocation = static_cast<ListAttribute*>(location);
				if (Functions::String::isStringInt(pathPart) && std::stoi(pathPart) < listLocation->size())
					location = listLocation->get(std::stoi(pathPart));
				else
					throw aube::ErrorHandler::Raise("Vili.Vili.LinkAttribute.WrongLinkListIndex", { {"path", getNodePath()}, {"target", m_path}, {"index", pathPart} });
			}
		}
		return location;
	}
	std::string LinkAttribute::getPath() const
	{
		return m_path;
	}
	std::string LinkAttribute::getFullPath() const
	{
		std::string linkroot = "";
		ComplexAttribute* complexParent = dynamic_cast<ComplexAttribute*>(m_parent);
		if (complexParent->contains(Types::BaseAttribute, "__linkroot__"))
			linkroot = complexParent->getBaseAttribute("__linkroot__")->get<std::string>();
		return linkroot + "/" + m_path;

	}
	void LinkAttribute::apply()
	{
		ComplexAttribute* complexParent = dynamic_cast<ComplexAttribute*>(m_parent);
		complexParent->deleteLinkAttribute(m_id);

		if (getTarget()->getType() == Types::ComplexAttribute)
			dynamic_cast<ComplexAttribute*>(getTarget())->copy(complexParent, m_id);
		else if (getTarget()->getType() == Types::ListAttribute)
			dynamic_cast<ListAttribute*>(getTarget())->copy(complexParent, m_id);
		else if (getTarget()->getType() == Types::BaseAttribute)
			dynamic_cast<BaseAttribute*>(getTarget())->copy(complexParent, m_id);
		else if (getTarget()->getType() == Types::LinkAttribute)
			dynamic_cast<LinkAttribute*>(getTarget())->copy(complexParent, m_id);
	}
	bool LinkAttribute::operator==(LinkAttribute compare) const
	{
		return (this->getFullPath() == compare.getFullPath());
	}

	void LinkAttribute::copy(ContainerAttribute* newParent, std::string newid)
	{
		if (newParent->getType() == Types::ComplexAttribute)
			dynamic_cast<ComplexAttribute*>(newParent)->createLinkAttribute((newid == "") ? m_id : newid, m_path);
		else
			throw aube::ErrorHandler::Raise("Vili.Vili.LinkAttribute.WrongCopyTarget", { {"path", getNodePath()}, {"target", newParent->getNodePath()} });
	}
	void LinkAttribute::write(std::ofstream* file, unsigned int depth)
	{
		for (unsigned int j = 0; j < depth; j++)
			(*file) << "    ";
		(*file) << m_id << ":&(" << getPath() << ")" << std::endl;
	}

	//ListAttribute
	ListAttribute::ListAttribute(ContainerAttribute* parent, const std::string& id) : ContainerAttribute(parent, id, Types::ListAttribute)
	{
	}
	ListAttribute::ListAttribute(const std::string& id) : ContainerAttribute(nullptr, id, Types::ListAttribute)
	{
	}
	unsigned int ListAttribute::size() const
	{
		return m_dataList.size();
	}
	BaseAttribute* ListAttribute::get(unsigned int index)
	{
		if (index < m_dataList.size())
			return m_dataList[index].get();
		throw aube::ErrorHandler::Raise("Vili.Vili.ListAttribute.WrongIndex", { 
			{"index", std::to_string(index)}, 
			{"path", getNodePath()}, 
			{"size", std::to_string(m_dataList.size()) } 
		});
	}

	std::vector<BaseAttribute*>::iterator ListAttribute::begin()
	{
		m_iteratorCache.clear();
		for (int i = 0; i < m_dataList.size(); i++)
			m_iteratorCache.push_back(m_dataList[i].get());
		return m_iteratorCache.begin();
	}
	std::vector<BaseAttribute*>::iterator ListAttribute::end()
	{
		return m_iteratorCache.end();
	}
	void ListAttribute::push(const std::string& element)
	{
		m_dataList.push_back(std::make_unique<BaseAttribute>(this, "#" + std::to_string(m_dataList.size()), Types::String, element));
	}
	void ListAttribute::push(const int& element)
	{
		m_dataList.push_back(std::make_unique<BaseAttribute>(this, "#" + std::to_string(m_dataList.size()), Types::Int, std::to_string(element)));
	}
	void ListAttribute::push(const bool& element)
	{
		m_dataList.push_back(std::make_unique<BaseAttribute>(this, "#" + std::to_string(m_dataList.size()), Types::Bool, (element == true) ? "True" : "False"));
	}
	void ListAttribute::push(const double& element)
	{
		m_dataList.push_back(std::make_unique<BaseAttribute>(this, "#" + std::to_string(m_dataList.size()), Types::Float, std::to_string(element)));
	}
	void ListAttribute::insert(unsigned int index, const std::string& element)
	{
		m_dataList.insert(m_dataList.begin() + index, std::make_unique<BaseAttribute>(this, "#" + std::to_string(m_dataList.size()), Types::String, element));
		for (int i = index + 1; i < m_dataList.size(); i++)
		{
			this->removeOwnership(m_dataList[i].get());
			m_dataList[i]->setID("#" + std::to_string(i));
			m_dataList[i]->setParent(this);
		}
	}
	void ListAttribute::insert(unsigned int index, const int& element)
	{
		m_dataList.insert(m_dataList.begin() + index, std::make_unique<BaseAttribute>(this, "#" + std::to_string(m_dataList.size()), Types::Int, std::to_string(element)));
		for (int i = index + 1; i < m_dataList.size(); i++)
		{
			this->removeOwnership(m_dataList[i].get());
			m_dataList[i]->setID("#" + std::to_string(i));
			m_dataList[i]->setParent(this);
		}
	}
	void ListAttribute::insert(unsigned int index, const bool& element)
	{
		m_dataList.insert(m_dataList.begin() + index, std::make_unique<BaseAttribute>(this, "#" + std::to_string(m_dataList.size()), Types::Bool, (element == true) ? "True" : "False"));
		for (int i = index + 1; i < m_dataList.size(); i++)
		{
			this->removeOwnership(m_dataList[i].get());
			m_dataList[i]->setID("#" + std::to_string(i));
			m_dataList[i]->setParent(this);
		}
	}
	void ListAttribute::insert(unsigned int index, const double& element)
	{
		m_dataList.insert(m_dataList.begin() + index, std::make_unique<BaseAttribute>(this, "#" + std::to_string(m_dataList.size()), Types::Float, std::to_string(element)));
		for (int i = index + 1; i < m_dataList.size(); i++)
		{
			this->removeOwnership(m_dataList[i].get());
			m_dataList[i]->setID("#" + std::to_string(i));
			m_dataList[i]->setParent(this);
		}
	}
	void ListAttribute::clear()
	{
		m_dataList.clear();
	}
	void ListAttribute::erase(unsigned int index)
	{
		m_dataList.erase(m_dataList.begin() + index);
	}
	Attribute* ListAttribute::extractElement(Attribute* element)
	{
		if (Functions::Vector::isInList(std::unique_ptr<BaseAttribute>(dynamic_cast<BaseAttribute*>(element)), m_dataList))
		{
			this->removeOwnership(element);
			int indexToRelease = Functions::Vector::indexOfElement(std::unique_ptr<BaseAttribute>(dynamic_cast<BaseAttribute*>(element)), m_dataList);
			m_dataList[indexToRelease].release();
			Functions::Vector::eraseAll(m_dataList, std::unique_ptr<BaseAttribute>(dynamic_cast<BaseAttribute*>(element)));
		}
		return element;
	}
	void ListAttribute::copy(ContainerAttribute* newParent, std::string newid)
	{
		if (newParent->getType() == Types::ComplexAttribute)
		{
			std::string useID = (newid == "") ? m_id : newid;
			dynamic_cast<ComplexAttribute*>(newParent)->createListAttribute(useID);
			for (int i = 0; i < m_dataList.size(); i++)
				m_dataList[i]->copy(dynamic_cast<ComplexAttribute*>(newParent)->getListAttribute(useID));
		}
		else
			throw aube::ErrorHandler::Raise("Vili.Vili.ListAttribute.WrongCopyTarget", { { "path", getNodePath() }, { "target", newParent->getNodePath() } });
	}
	void ListAttribute::write(std::ofstream* file, unsigned int depth)
	{
		for (unsigned int j = 0; j < depth; j++)
			(*file) << "    ";
		(*file) << m_id << ":[" << std::endl;
		for (unsigned int k = 0; k < size(); k++)
			get(k)->write(file, depth + 1);
		for (unsigned int l = 0; l < depth; l++)
			(*file) << "    ";
		(*file) << "]" << std::endl;
	}


	//ComplexAttribute
	ComplexAttribute::ComplexAttribute(ComplexAttribute* parent, const std::string& id) : ContainerAttribute(parent, id, Types::ComplexAttribute)
	{
		m_parent = parent;
	}
	ComplexAttribute::ComplexAttribute(ComplexAttribute* parent, const std::string& id, ComplexAttribute* herit)
		: ContainerAttribute(parent, id, Types::ComplexAttribute)
	{
		m_parent = parent;
		this->heritage(herit);
	}
	ComplexAttribute::ComplexAttribute(ComplexAttribute* parent, const std::string& id, std::vector<ComplexAttribute*>* multipleHerit)
		: ContainerAttribute(parent, id, Types::ComplexAttribute)
	{
		m_parent = parent;
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
		if (Functions::Vector::isInList(element->getID(), m_childAttributesNames))
		{
			this->removeOwnership(element);
			m_childAttributes[element->getID()].release();
			m_childAttributes.erase(element->getID());
			Functions::Vector::eraseAll(m_childAttributesNames, element->getID());
			return element;
		}
		throw aube::ErrorHandler::Raise("Vili.Vili.ComplexAttribute.WrongExtraction", { {"path", getNodePath()}, {"element", element->getNodePath() } });
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
			ComplexAttribute* getToPath = this->getComplexAttribute(sPath[0]);
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
		if (m_childAttributes.find(attributeID) != m_childAttributes.end())
			return m_childAttributes[attributeID].get();
		throw aube::ErrorHandler::Raise("Vili.Vili.ComplexAttribute.WrongGetAttributeKey", { {"attribute", attributeID}, {"path", getNodePath()} });
	}

	BaseAttribute* ComplexAttribute::getBaseAttribute(const std::string& attributeID)
	{
		if (m_childAttributes.find(attributeID) != m_childAttributes.end() && m_childAttributes[attributeID]->getType() == Types::BaseAttribute)
			return static_cast<BaseAttribute*>(m_childAttributes[attributeID].get());
		throw aube::ErrorHandler::Raise("Vili.Vili.ComplexAttribute.WrongGetBaseAttributeKey", { { "attribute", attributeID },{ "path", getNodePath() } });
	}

	ListAttribute* ComplexAttribute::getListAttribute(const std::string& attributeID)
	{
		if (m_childAttributes.find(attributeID) != m_childAttributes.end() && m_childAttributes[attributeID]->getType() == Types::ListAttribute)
			return static_cast<ListAttribute*>(m_childAttributes[attributeID].get());
		throw aube::ErrorHandler::Raise("Vili.Vili.ComplexAttribute.WrongGetListAttributeKey", { { "attribute", attributeID },{ "path", getNodePath() } });
	}
	LinkAttribute* ComplexAttribute::getLinkAttribute(const std::string& attributeID)
	{
		if (m_childAttributes.find(attributeID) != m_childAttributes.end() && m_childAttributes[attributeID]->getType() == Types::LinkAttribute)
			return static_cast<LinkAttribute*>(m_childAttributes[attributeID].get());
		throw aube::ErrorHandler::Raise("Vili.Vili.ComplexAttribute.WrongGetLinkAttributeKey", { { "attribute", attributeID },{ "path", getNodePath() } });
	}
	ComplexAttribute* ComplexAttribute::getComplexAttribute(const std::string& attributeID)
	{
		if (!m_childAttributes.empty() && m_childAttributes.find(attributeID) != m_childAttributes.end() && m_childAttributes[attributeID]->getType() == Types::ComplexAttribute)
			return dynamic_cast<ComplexAttribute*>(m_childAttributes[attributeID].get());
		throw aube::ErrorHandler::Raise("Vili.Vili.ComplexAttribute.WrongGetComplexAttributeKey", { { "attribute", attributeID },{ "path", getNodePath() } });
	}
	Types::AttributeType ComplexAttribute::getAttributeType(const std::string& attributeID)
	{
		return this->get(attributeID)->getType();
	}
	std::vector<std::string> ComplexAttribute::getAll(Types::AttributeType searchType)
	{
		std::vector<std::string> attributes;
		for (std::string attributeID : m_childAttributesNames)
		{
			if (m_childAttributes[attributeID]->getType() == searchType)
				attributes.push_back(attributeID);
			else if (searchType == Types::Attribute)
				attributes.push_back(attributeID);
			else if (searchType == Types::ContainerAttribute && m_childAttributes[attributeID]->getType() == Types::ComplexAttribute)
				attributes.push_back(attributeID);
			else if (searchType == Types::ContainerAttribute && m_childAttributes[attributeID]->getType() == Types::ListAttribute)
				attributes.push_back(attributeID);
		}
		return attributes;
	}
	bool ComplexAttribute::contains(Types::AttributeType searchType, const std::string & attributeID)
	{
		if (m_childAttributes.find(attributeID) != m_childAttributes.end() && m_childAttributes[attributeID]->getType() == searchType)
			return true;
		else
			return false;
	}
	bool ComplexAttribute::contains(const std::string& attributeID)
	{
		if (m_childAttributes.find(attributeID) != m_childAttributes.end())
			return true;
		else
			return false;
	}
	void ComplexAttribute::createBaseAttribute(const std::string& attributeID, const Types::DataType& type, const std::string& data)
	{
		m_childAttributes[attributeID] = std::make_unique<BaseAttribute>(this, attributeID, type, data);
		if (!Functions::Vector::isInList(attributeID, m_childAttributesNames))
			m_childAttributesNames.push_back(attributeID);
	}
	void ComplexAttribute::createBaseAttribute(const std::string& attributeID, const std::string& data)
	{
		m_childAttributes[attributeID] = std::make_unique<BaseAttribute>(this, attributeID, Types::String, data);
		if (!Functions::Vector::isInList(attributeID, m_childAttributesNames))
			m_childAttributesNames.push_back(attributeID);
	}
	void ComplexAttribute::createBaseAttribute(const std::string& attributeID, bool data)
	{
		m_childAttributes[attributeID] = std::make_unique<BaseAttribute>(this, attributeID, Types::Bool, (data == true ? "True" : "False"));
		if (!Functions::Vector::isInList(attributeID, m_childAttributesNames))
			m_childAttributesNames.push_back(attributeID);
	}
	void ComplexAttribute::createBaseAttribute(const std::string& attributeID, int data)
	{
		m_childAttributes[attributeID] = std::make_unique<BaseAttribute>(this, attributeID, Types::Int, std::to_string(data));
		if (!Functions::Vector::isInList(attributeID, m_childAttributesNames))
			m_childAttributesNames.push_back(attributeID);
	}
	void ComplexAttribute::createBaseAttribute(const std::string& attributeID, double data)
	{
		m_childAttributes[attributeID] = std::make_unique<BaseAttribute>(this, attributeID, Types::Float, std::to_string(data));
		if (!Functions::Vector::isInList(attributeID, m_childAttributesNames))
			m_childAttributesNames.push_back(attributeID);
	}
	void ComplexAttribute::pushBaseAttribute(BaseAttribute* attribute)
	{
		m_childAttributes[attribute->getID()] = std::unique_ptr<BaseAttribute>(attribute);
		if (!Functions::Vector::isInList(attribute->getID(), m_childAttributesNames))
			m_childAttributesNames.push_back(attribute->getID());
	}
	void ComplexAttribute::createListAttribute(const std::string& attributeID)
	{
		m_childAttributes[attributeID] = std::make_unique<ListAttribute>(this, attributeID);
		if (!Functions::Vector::isInList(attributeID, m_childAttributesNames))
			m_childAttributesNames.push_back(attributeID);
	}
	void ComplexAttribute::pushListAttribute(ListAttribute* attribute)
	{
		m_childAttributes[attribute->getID()] = std::unique_ptr<ListAttribute>(attribute);
		if (!Functions::Vector::isInList(attribute->getID(), m_childAttributesNames))
			m_childAttributesNames.push_back(attribute->getID());
	}
	void ComplexAttribute::createComplexAttribute(const std::string& attributeID)
	{
		m_childAttributes[attributeID] = std::make_unique<ComplexAttribute>(this, attributeID);
		if (!Functions::Vector::isInList(attributeID, m_childAttributesNames))
			m_childAttributesNames.push_back(attributeID);
	}
	void ComplexAttribute::pushComplexAttribute(ComplexAttribute* attribute)
	{
		m_childAttributes[attribute->getID()] = std::unique_ptr<ComplexAttribute>(attribute);
		if (!Functions::Vector::isInList(attribute->getID(), m_childAttributesNames))
			m_childAttributesNames.push_back(attribute->getID());
	}
	void ComplexAttribute::createLinkAttribute(const std::string& attributeID, const std::string& path)
	{
		m_childAttributes[attributeID] = std::make_unique<LinkAttribute>(this, attributeID, path);
		if (!Functions::Vector::isInList(attributeID, m_childAttributesNames))
			m_childAttributesNames.push_back(attributeID);
	}
	void ComplexAttribute::pushLinkAttribute(LinkAttribute* attribute)
	{
		m_childAttributes[attribute->getID()] = std::unique_ptr<LinkAttribute>(attribute);
		if (!Functions::Vector::isInList(attribute->getID(), m_childAttributesNames))
			m_childAttributesNames.push_back(attribute->getID());
	}
	void ComplexAttribute::write(std::ofstream* file, unsigned int depth)
	{
		for (unsigned int i = 0; i < depth; i++)
			(*file) << "    ";
		if (depth)
			(*file) << "@" << m_id << std::endl;
		else
			(*file) << m_id << ":" << std::endl;
		for (auto& child : m_childAttributesNames)
			m_childAttributes[child]->write(file, depth + 1);
		if (depth == 0)
			(*file) << std::endl;
	}
	void ComplexAttribute::deleteBaseAttribute(const std::string& attributeID, bool freeMemory)
	{
		if (Functions::Vector::isInList(attributeID, this->getAll(Types::BaseAttribute)))
			m_childAttributesNames.erase(m_childAttributesNames.begin() + Functions::Vector::indexOfElement(attributeID, m_childAttributesNames));
		typedef std::map<std::string, std::unique_ptr<Attribute>>::iterator it_type;
		it_type itDel = m_childAttributes.find(attributeID);
		if (itDel != m_childAttributes.end() && m_childAttributes[attributeID]->getType() == Types::BaseAttribute)
		{
			if (!freeMemory)
				m_childAttributes[attributeID].release();
			m_childAttributes.erase(itDel);
		}
	}
	void ComplexAttribute::deleteComplexAttribute(const std::string& attributeID, bool freeMemory)
	{
		if (Functions::Vector::isInList(attributeID, this->getAll(Types::ComplexAttribute)))
			m_childAttributesNames.erase(m_childAttributesNames.begin() + Functions::Vector::indexOfElement(attributeID, m_childAttributesNames));
		typedef std::map<std::string, std::unique_ptr<Attribute>>::iterator it_type;
		it_type itDel = m_childAttributes.find(attributeID);
		if (itDel != m_childAttributes.end() && m_childAttributes[attributeID]->getType() == Types::ComplexAttribute)
		{
			if (!freeMemory)
				m_childAttributes[attributeID].release();
			m_childAttributes.erase(itDel);
		}
	}
	void ComplexAttribute::deleteListAttribute(const std::string& attributeID, bool freeMemory)
	{
		if (Functions::Vector::isInList(attributeID, this->getAll(Types::ListAttribute)))
			m_childAttributesNames.erase(m_childAttributesNames.begin() + Functions::Vector::indexOfElement(attributeID, m_childAttributesNames));
		typedef std::map<std::string, std::unique_ptr<Attribute>>::iterator it_type;
		it_type itDel = m_childAttributes.find(attributeID);
		if (itDel != m_childAttributes.end() && m_childAttributes[attributeID]->getType() == Types::ListAttribute)
		{
			if (!freeMemory)
				m_childAttributes[attributeID].release();
			m_childAttributes.erase(itDel);
		}
	}
	void ComplexAttribute::deleteLinkAttribute(const std::string& attributeID, bool freeMemory)
	{
		if (Functions::Vector::isInList(attributeID, this->getAll(Types::LinkAttribute)))
			m_childAttributesNames.erase(m_childAttributesNames.begin() + Functions::Vector::indexOfElement(attributeID, m_childAttributesNames));
		typedef std::map<std::string, std::unique_ptr<Attribute>>::iterator it_type;
		it_type itDel = m_childAttributes.find(attributeID);
		if (itDel != m_childAttributes.end() && m_childAttributes[attributeID]->getType() == Types::LinkAttribute)
		{
			if (!freeMemory)
				m_childAttributes[attributeID].release();
			m_childAttributes.erase(itDel);
		}
	}
	void ComplexAttribute::copy(ContainerAttribute* newParent, std::string newid)
	{
		std::string useID = (newid == "") ? this->m_id : newid;
		if (newParent->getType() == Types::ComplexAttribute)
		{
			dynamic_cast<ComplexAttribute*>(newParent)->createComplexAttribute(useID);
			for (auto& child : m_childAttributesNames)
			{
				m_childAttributes[child]->copy(dynamic_cast<ComplexAttribute*>(newParent)->getComplexAttribute(useID));
			}
		}
		else
			throw aube::ErrorHandler::Raise("Vili.Vili.ComplexAttribute.WrongCopyTarget", { { "path", getNodePath() },{ "target", newParent->getNodePath() } });
	}
	void ComplexAttribute::walk(std::function<void(ComplexAttribute*)> walkFunction)
	{
		for (std::string& complex : getAll(Types::ComplexAttribute))
			this->getComplexAttribute(complex)->walk(walkFunction);
		walkFunction(this);
	}

	//AttributeConstraintManager
	AttributeConstraintManager::AttributeConstraintManager(ComplexAttribute* parent, std::string path) : m_attribute(parent, "link", path)
	{
	}
	void AttributeConstraintManager::addConstraint(std::function<bool(BaseAttribute*)> constraint)
	{
		m_constraints.push_back(constraint);
	}
	bool AttributeConstraintManager::checkAllConstraints()
	{
		for (std::function<bool(BaseAttribute*)>& constraint : m_constraints)
		{
			if (!constraint(m_attribute.get<BaseAttribute*>()))
				return false;
		}
		if (m_attribute.get<BaseAttribute*>()->getAnnotation() != "Set")
			return false;
		m_attribute.get<BaseAttribute*>()->setAnnotation("UnSet");
		return true;
	}
	LinkAttribute* AttributeConstraintManager::getLinkAttribute()
	{
		return &m_attribute;
	}
	std::string AttributeConstraintManager::getArgumentPath() const
	{
		return m_attribute.getFullPath();
	}

	//DataTemplate
	DataTemplate::DataTemplate() : m_body("root")
	{
	}
	ComplexAttribute* DataTemplate::getBody()
	{
		return &m_body;
	}
	void DataTemplate::build(ComplexAttribute* parent, const std::string& id)
	{
		if (checkSignature())
		{
			m_body.at("__body__")->copy(parent, id);
			std::vector<LinkAttribute*> attributeAddresses;
			for (AttributeConstraintManager& constraintManager : m_signature)
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
			if (m_defaultLinkRoot)
				parent->at(id)->deleteBaseAttribute("__linkroot__");
		}
		else
			throw aube::ErrorHandler::Raise("Vili.Vili.DataTemplate.BuildError", { {"element", id}, {"parent", parent->getNodePath()} });
	}
	bool DataTemplate::checkSignature()
	{
		for (AttributeConstraintManager& constraintManager : m_signature)
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
			m_signatureEnd = true;
			m_signature.push_back(constraintManager);
		}
		else if (!facultative && !m_signatureEnd)
			m_signature.push_back(constraintManager);
		else
			throw aube::ErrorHandler::Raise("Vili.Vili.DataTemplate.WrongFacultativeParameterOrder", { {"index", std::to_string(m_signature.size()) } });
	}
	void DataTemplate::useDefaultLinkRoot()
	{
		m_defaultLinkRoot = true;
	}

	//DataParser
	DataParser::DataParser()
	{
		m_root = std::make_unique<ComplexAttribute>("root");
		m_root->setAnnotation("NoFile");
	}
	DataParser::DataParser(std::string file)
	{
		m_root = std::make_unique<ComplexAttribute>("root");
		m_root->setAnnotation("NoFile");
		parseFile(file);
	}
	ComplexAttribute* DataParser::operator->() const
	{
		return m_root.get();
	}
	void DataParser::createFlag(const std::string& flag)
	{
		m_flagList.push_back(flag);
	}
	bool DataParser::hasFlag(const std::string& flagName)
	{
		return std::find(m_flagList.begin(), m_flagList.end(), flagName) != m_flagList.end();
	}
	unsigned int DataParser::getAmountOfFlags() const
	{
		return m_flagList.size();
	}
	std::string DataParser::getFlagAtIndex(int index)
	{
		return m_flagList[index];
	}
	ComplexAttribute* DataParser::getPath(std::string path) const
	{
		if (path.size() > 0 && Functions::String::extract(path, path.size() - 1, 0) == "/")
			path = Functions::String::extract(path, 0, 1);
		if (Functions::String::occurencesInString(path, "/") > 0)
		{
			std::vector<std::string> splittedPath = Functions::String::split(path, "/");
			std::string subPath = Functions::Vector::join(splittedPath, "/", 1);
			return getPath(Functions::String::split(path, "/")[0])->at(subPath);
		}
		return getRootChild(path);
	}
	ComplexAttribute* DataParser::getRootChild(std::string child) const
	{
		if (child == "")
			return m_root.get();
		return m_root->getComplexAttribute(child);
	}
	ComplexAttribute& DataParser::operator[](std::string cPath) const
	{
		return (*getPath(cPath));
	}
	ComplexAttribute* DataParser::at(std::string cPath) const
	{
		if (cPath.size() > 0 && Functions::String::extract(cPath, cPath.size() - 1, 0) == "/")
			cPath = Functions::String::extract(cPath, 0, 1);
		return getPath(cPath);
	}
	bool DataParser::parseFile(const std::string& filename, bool verbose)
	{
		std::ifstream useFile;
		useFile.open(filename);
		m_root->setAnnotation(filename);
		std::string currentLine;
		std::vector<std::string> addPath = {};
		std::string curCat = "None";
		std::string curList = "None";
		int curListIndent = 0;
		bool inList = false;
		if (useFile.is_open())
		{
			if (verbose) std::cout << "Start Parsing File : " << filename << std::endl;
			while (!safeGetline(useFile, currentLine).eof())
			{
				Functions::String::StringExtractor stringsInLine = Functions::String::extractAllStrings(currentLine);
				std::string rawLine = Functions::Vector::join(std::get<1>(stringsInLine), "");
				Functions::String::replaceStringInPlace(rawLine, "	", std::string(m_spacing, ' '));
				unsigned int currentIndent = 0;
				unsigned int spacingAmount = 0;
				for (int i = 0; i < rawLine.size(); i++)
				{
					if (rawLine[i] == ' ')
					{
						spacingAmount += 1;
						if (spacingAmount == m_spacing)
						{
							spacingAmount = 0;
							currentIndent += 1;
						}
					}
					else
						break;
				}
				Functions::String::replaceStringInPlace(rawLine, std::string(m_spacing, ' '), "");
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
							if (currentRawChar == "," && inList)
							{
								parsedLines.push_back(addParsedLine);
								addParsedLine = "";
							}
							else if (currentRawChar == "[")
							{
								parsedLines.push_back(addParsedLine + "[");
								addParsedLine = "";
								inList = true;
							}
							else if (currentRawChar == "]")
							{
								parsedLines.push_back(addParsedLine);
								parsedLines.push_back("]");
								addParsedLine = "";
								inList = false;
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
							m_root->createComplexAttribute(curCat);
						}
						else if (parsedLine.substr(parsedLine.size() - 1, 1) == ";")
						{
							std::string instructionType = Functions::String::split(parsedLine, "(")[0];
							std::string instructionValue = Functions::String::split(parsedLine, "(")[1];
							instructionValue = Functions::String::split(instructionValue, ")")[0];
							if (instructionType == "Flag")
							{
								m_flagList.push_back(instructionValue);
								if (verbose) std::cout << indenter() << "Define New Flag : " << instructionValue << std::endl;
							}
							else if (instructionType == "Spacing")
							{
								m_spacing = std::stoi(instructionValue);
								if (verbose) std::cout << indenter() << "Define New Spacing : " << m_spacing << std::endl;
							}
							else if (instructionType == "Include")
							{
								if (verbose) std::cout << indenter() << "Include New File : " << instructionValue << std::endl;
								this->parseFile(instructionValue + ".vili", verbose);
								this->addInclude(instructionValue);
								m_root->setAnnotation(filename);
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
												std::vector<std::string> requiredTypes;
												ComplexAttribute* currentArgument = templateBase->at("__init__", std::to_string(i));
												if (currentArgument->contains(Types::BaseAttribute, "type"))
													requiredTypes.push_back(
														currentArgument->getBaseAttribute("type")->get<std::string>()
													);
												else {
													for (int i = 0; i < currentArgument->getListAttribute("types")->size(); i++) {
														requiredTypes.push_back(currentArgument->getListAttribute("types")->get(i)->get<std::string>());
													}
												}
												std::vector<Types::DataType> requiredConstraintTypes;
												for (std::string& reqType : requiredTypes) {
													requiredConstraintTypes.push_back(Types::stringToDataType(reqType));
												}
												newConstraint.addConstraint([requiredConstraintTypes](BaseAttribute* attribute) -> bool
												{
													return (Functions::Vector::isInList(attribute->getDataType(), requiredConstraintTypes));
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
										m_templateList[templateBase->getID()] = newTemplate;
									}
									else
										throw aube::ErrorHandler::Raise("Vili.Vili.DataParser.TemplateMissingInitOrBody", { { "template", instructionValue}, {"file", filename } });
								}
								else
									throw aube::ErrorHandler::Raise("Vili.Vili.DataParser.WrongTemplateBase", { { "attribute", instructionValue },{ "file", filename } });
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
								std::string templateName = attributeValue;
								templateName = Functions::String::split(templateName, "(")[0];
								if (m_templateList.find(templateName) != m_templateList.end())
								{
									std::string argPart = Functions::String::split(attributeValue, "(")[1];
									argPart = argPart.substr(0, argPart.size() - 1);
									std::vector<std::string> templateArgs = Functions::String::split(argPart, ",");
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
									m_templateList[templateName]->build(getRootChild(curCat)->getPath(Path(addPath)), attributeID);
									if (verbose)
									{
										std::cout << indenter() << "Create ComplexAttribute " << attributeID << " from Template <" << templateName
											<< "> inside " << pushIndicator << std::endl;
									}
								}
								else
									throw aube::ErrorHandler::Raise("Vili.Vili.DataParser.UnknownTemplate", { { "template", templateName },{ "id", attributeID },{ "file", filename } });
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
							std::vector<std::string> complexToHeritIDList;
							std::vector<ComplexAttribute*> complexToHerit;
							if (Functions::String::occurencesInString(complexElementID, ":") == 1 && Functions::String::split(complexElementID, ":").size() == 2)
							{
								std::string complexToHeritID = Functions::String::replaceString(Functions::String::split(complexElementID, ":")[1], " ", "");
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
							if (verbose) std::cout << indenter() << "Create Element #" << getPath(curCat)->getPath(Path(addPath))->getListAttribute(curList)->size()
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
								throw aube::ErrorHandler::Raise("Vili.Vili.DataParser.UnknownTypeInList", { {"list", attributeValue}, {"file", filename} });
						}
					}
				}
			}
			useFile.close();
			if (verbose) std::cout << "Parsed over.." << std::endl;
			return true;
		}
		throw aube::ErrorHandler::Raise("Vili.Vili.DataParser.FileNotFound", { {"file", filename} });
	}
	void DataParser::writeFile(const std::string& filename, bool verbose)
	{
		std::ofstream outFile;
		outFile.open(filename);
		if (verbose) std::cout << "Writing DataParser's content on file : " << filename << std::endl;
		if (m_spacing != 4)
		{
			outFile << "Spacing (" << m_spacing << ");" << std::endl;
			if (verbose) std::cout << "Define custom spacing : " << m_spacing << std::endl;
		}
		if (verbose && this->getAmountOfFlags() > 0) std::cout << "    Writing Flags..." << std::endl;
		for (unsigned int i = 0; i < this->getAmountOfFlags(); i++)
		{
			outFile << "Flag (" << this->getFlagAtIndex(i) << ");" << std::endl;
			if (verbose) std::cout << "        Write New Flag : " << this->getFlagAtIndex(i) << std::endl;
		}
		if (this->getAmountOfFlags() > 0) outFile << std::endl;
		if (verbose && m_root->getAll(Types::ComplexAttribute).size() > 0) std::cout << "    Writing RootAttributes..." << std::endl;
		for (std::string& currentRootAttribute : m_root->getAll(Types::ComplexAttribute))
		{
			if (m_templateList.find(currentRootAttribute) == m_templateList.end())
			{
				if (verbose) std::cout << "        Write New RootAttribute : " << currentRootAttribute << std::endl;
				getRootChild(currentRootAttribute)->write(&outFile);
			}
		}
		outFile.close();
	}
}