#include "Ice.h"


namespace Ice
{
	// General method definitions
	bool IceObject::isInstance()
	{
		return type == TYPE::INSTANCE || type == TYPE::LIST || type == TYPE::STRING || type == TYPE::DICT;
	}

	bool IceObject::isTraversable()
	{
		return type == TYPE::LIST || type == TYPE::STRING || type == TYPE::DICT;
	}


	// Definitions for IceFunctionObject
	IceFunctionObject::IceFunctionObject(const VariableList &argDecls, ::std::shared_ptr<BlockExpr> block) : argDecls(argDecls), block(block)
	{
		type = TYPE::FUNCTION;
	}
	

	// Definitions for IceBuiltInFunctionObject
	IceBuiltInFunctionObject::IceBuiltInFunctionObject(::std::function<::std::shared_ptr<IceObject>(Objects)> func) : func(func)
	{
		type = TYPE::BUILT_IN_FUNCTION;
	}


	// Definitions for IceClassObject
	IceClassObject::IceClassObject(const IdentifierList &bases, ::std::shared_ptr<BlockExpr> block) : bases(bases), block(block)
	{
		type = TYPE::CLASS;
	}


	// Definitions for IceInstancesObject
	IceInstanceObject::IceInstanceObject()
	{
		type = TYPE::INSTANCE;
		top = ::std::make_shared<Env>(nullptr);
	}

	IceInstanceObject::IceInstanceObject(::std::shared_ptr<Env> &top)
	{
		type = TYPE::INSTANCE;
		this->top = ::std::make_shared<Env>(top);
	}

	::std::shared_ptr<IceObject> IceInstanceObject::binaryOperate(::std::shared_ptr<IceObject> obj, TOKEN op)
	{
		if (obj->type == TYPE::NONE && op == TOKEN::TCNE)
		{
			return ::std::make_shared<IceBooleanObject>(true);
		}
		else if (obj->type == TYPE::NONE && op == TOKEN::TCEQ)
		{
			return ::std::make_shared<IceBooleanObject>(false);
		}
		else
		{
			return ::std::make_shared<IceBooleanObject>(false);
		}
	}


	// Definitions for IceNoneObject
	IceNoneObject::IceNoneObject()
	{
		type = TYPE::NONE;
	}


	// Definitions for IceIntegerObejct
	IceIntegerObject::IceIntegerObject(long value) : value(value)
	{
		type = TYPE::INT;
	}

	::std::shared_ptr<IceObject> IceIntegerObject::unaryOperate(TOKEN op)
	{
		switch (op)
		{
		case TOKEN::TSUB:
			return ::std::make_shared<IceIntegerObject>(-value);
		default:
			break;
		}
		::std::cout << "doesn't support this operator" << ::std::endl;
		exit(0);
		return nullptr;
	}

	::std::shared_ptr<IceObject> IceIntegerObject::binaryOperate(::std::shared_ptr<IceObject> obj, TOKEN op)
	{
		switch (obj->type)
		{
		case TYPE::INT:
			switch (op)
			{
			case TOKEN::TADD:
				return ::std::make_shared<IceIntegerObject>(value + ::std::dynamic_pointer_cast<IceIntegerObject>(obj)->value);
			case TOKEN::TSUB:
				return ::std::make_shared<IceIntegerObject>(value - ::std::dynamic_pointer_cast<IceIntegerObject>(obj)->value);
			case TOKEN::TMUL:
				return ::std::make_shared<IceIntegerObject>(value * ::std::dynamic_pointer_cast<IceIntegerObject>(obj)->value);
			case TOKEN::TDIV:
				return ::std::make_shared<IceIntegerObject>(value / ::std::dynamic_pointer_cast<IceIntegerObject>(obj)->value);
			case TOKEN::TMOD:
				return ::std::make_shared<IceIntegerObject>(value % ::std::dynamic_pointer_cast<IceIntegerObject>(obj)->value);
			case TOKEN::TCEQ:
				return ::std::make_shared<IceBooleanObject>(value == ::std::dynamic_pointer_cast<IceIntegerObject>(obj)->value);
			case TOKEN::TCNE:
				return ::std::make_shared<IceBooleanObject>(value != ::std::dynamic_pointer_cast<IceIntegerObject>(obj)->value);
			case TOKEN::TCLT:
				return ::std::make_shared<IceBooleanObject>(value < ::std::dynamic_pointer_cast<IceIntegerObject>(obj)->value);
			case TOKEN::TCLE:
				return ::std::make_shared<IceBooleanObject>(value <= ::std::dynamic_pointer_cast<IceIntegerObject>(obj)->value);
			case TOKEN::TCGT:
				return ::std::make_shared<IceBooleanObject>(value > ::std::dynamic_pointer_cast<IceIntegerObject>(obj)->value);
			case TOKEN::TCGE:
				return ::std::make_shared<IceBooleanObject>(value >= ::std::dynamic_pointer_cast<IceIntegerObject>(obj)->value);
			default:
				break;
			}
			break;
		case TYPE::DOUBLE:
			switch (op)
			{
			case TOKEN::TADD:
				return ::std::make_shared<IceDoubleObject>(value + ::std::dynamic_pointer_cast<IceDoubleObject>(obj)->value);
			case TOKEN::TSUB:
				return ::std::make_shared<IceDoubleObject>(value - ::std::dynamic_pointer_cast<IceDoubleObject>(obj)->value);
			case TOKEN::TMUL:
				return ::std::make_shared<IceDoubleObject>(value * ::std::dynamic_pointer_cast<IceDoubleObject>(obj)->value);
			case TOKEN::TDIV:
				return ::std::make_shared<IceDoubleObject>(value / ::std::dynamic_pointer_cast<IceDoubleObject>(obj)->value);
			case TOKEN::TMOD:
				return ::std::make_shared<IceDoubleObject>(value % (long)::std::dynamic_pointer_cast<IceDoubleObject>(obj)->value);
			case TOKEN::TCEQ:
				return ::std::make_shared<IceBooleanObject>(value == ::std::dynamic_pointer_cast<IceDoubleObject>(obj)->value);
			case TOKEN::TCNE:
				return ::std::make_shared<IceBooleanObject>(value != ::std::dynamic_pointer_cast<IceDoubleObject>(obj)->value);
			case TOKEN::TCLT:
				return ::std::make_shared<IceBooleanObject>(value < ::std::dynamic_pointer_cast<IceDoubleObject>(obj)->value);
			case TOKEN::TCLE:
				return ::std::make_shared<IceBooleanObject>(value <= ::std::dynamic_pointer_cast<IceDoubleObject>(obj)->value);
			case TOKEN::TCGT:
				return ::std::make_shared<IceBooleanObject>(value > ::std::dynamic_pointer_cast<IceDoubleObject>(obj)->value);
			case TOKEN::TCGE:
				return ::std::make_shared<IceBooleanObject>(value >= ::std::dynamic_pointer_cast<IceDoubleObject>(obj)->value);
			default:
				break;
			}
			break;
		default:
			break;
		}
		::std::cout << "doesn't support this operator" << ::std::endl;
		exit(0);
		return nullptr;
	}


	// Definitions for IceDoubleObject
	IceDoubleObject::IceDoubleObject(double value) : value(value)
	{
		type = TYPE::DOUBLE;
	}

	::std::shared_ptr<IceObject> IceDoubleObject::unaryOperate(TOKEN op)
	{
		switch (op)
		{
		case TOKEN::TSUB:
			return ::std::make_shared<IceDoubleObject>(-value);
		default:
			break;
		}
		::std::cout << "doesn't support this operator" << ::std::endl;
		exit(0);
		return nullptr;
	}

	::std::shared_ptr<IceObject> IceDoubleObject::binaryOperate(::std::shared_ptr<IceObject> obj, TOKEN op)
	{

		switch (obj->type)
		{
		case TYPE::INT:
			switch (op)
			{
			case TOKEN::TADD:
				return ::std::make_shared<IceDoubleObject>(value + ::std::dynamic_pointer_cast<IceIntegerObject>(obj)->value);
			case TOKEN::TSUB:
				return ::std::make_shared<IceDoubleObject>(value - ::std::dynamic_pointer_cast<IceIntegerObject>(obj)->value);
			case TOKEN::TMUL:
				return ::std::make_shared<IceDoubleObject>(value * ::std::dynamic_pointer_cast<IceIntegerObject>(obj)->value);
			case TOKEN::TDIV:
				return ::std::make_shared<IceDoubleObject>(value / ::std::dynamic_pointer_cast<IceIntegerObject>(obj)->value);
			case TOKEN::TMOD:
				return ::std::make_shared<IceDoubleObject>((long)value % ::std::dynamic_pointer_cast<IceIntegerObject>(obj)->value);
			case TOKEN::TCEQ:
				return ::std::make_shared<IceBooleanObject>(value == ::std::dynamic_pointer_cast<IceIntegerObject>(obj)->value);
			case TOKEN::TCNE:
				return ::std::make_shared<IceBooleanObject>(value != ::std::dynamic_pointer_cast<IceIntegerObject>(obj)->value);
			case TOKEN::TCLT:
				return ::std::make_shared<IceBooleanObject>(value < ::std::dynamic_pointer_cast<IceIntegerObject>(obj)->value);
			case TOKEN::TCLE:
				return ::std::make_shared<IceBooleanObject>(value <= ::std::dynamic_pointer_cast<IceIntegerObject>(obj)->value);
			case TOKEN::TCGT:
				return ::std::make_shared<IceBooleanObject>(value > ::std::dynamic_pointer_cast<IceIntegerObject>(obj)->value);
			case TOKEN::TCGE:
				return ::std::make_shared<IceBooleanObject>(value >= ::std::dynamic_pointer_cast<IceIntegerObject>(obj)->value);
			default:
				break;
			}
			break;
		case TYPE::DOUBLE:
			switch (op)
			{
			case TOKEN::TADD:
				return ::std::make_shared<IceDoubleObject>(value + ::std::dynamic_pointer_cast<IceDoubleObject>(obj)->value);
			case TOKEN::TSUB:
				return ::std::make_shared<IceDoubleObject>(value - ::std::dynamic_pointer_cast<IceDoubleObject>(obj)->value);
			case TOKEN::TMUL:
				return ::std::make_shared<IceDoubleObject>(value * ::std::dynamic_pointer_cast<IceDoubleObject>(obj)->value);
			case TOKEN::TDIV:
				return ::std::make_shared<IceDoubleObject>(value / ::std::dynamic_pointer_cast<IceDoubleObject>(obj)->value);
			case TOKEN::TMOD:
				return ::std::make_shared<IceDoubleObject>((long)value % (long)::std::dynamic_pointer_cast<IceDoubleObject>(obj)->value);
			case TOKEN::TCEQ:
				return ::std::make_shared<IceBooleanObject>(value == ::std::dynamic_pointer_cast<IceDoubleObject>(obj)->value);
			case TOKEN::TCNE:
				return ::std::make_shared<IceBooleanObject>(value != ::std::dynamic_pointer_cast<IceDoubleObject>(obj)->value);
			case TOKEN::TCLT:
				return ::std::make_shared<IceBooleanObject>(value < ::std::dynamic_pointer_cast<IceDoubleObject>(obj)->value);
			case TOKEN::TCLE:
				return ::std::make_shared<IceBooleanObject>(value <= ::std::dynamic_pointer_cast<IceDoubleObject>(obj)->value);
			case TOKEN::TCGT:
				return ::std::make_shared<IceBooleanObject>(value > ::std::dynamic_pointer_cast<IceDoubleObject>(obj)->value);
			case TOKEN::TCGE:
				return ::std::make_shared<IceBooleanObject>(value >= ::std::dynamic_pointer_cast<IceDoubleObject>(obj)->value);
			default:
				break;
			}
			break;
		default:
			break;
		}
		::std::cout << "doesn't support this operator" << ::std::endl;
		exit(0);
		return nullptr;
	}


	// Definitions for IceBooleanObject
	IceBooleanObject::IceBooleanObject(bool value) : value(value)
	{
		type = TYPE::BOOLEAN;
	}

	void IceBooleanObject::show()
	{
		if (value) ::std::cout << "true";
		else ::std::cout << "false";
	}

	::std::shared_ptr<IceObject> IceBooleanObject::unaryOperate(TOKEN op)
	{
		switch (op)
		{
		case TOKEN::TSUB:
			return ::std::make_shared<IceIntegerObject>(-value);
		case TOKEN::TNOT:
			return ::std::make_shared<IceBooleanObject>(!value);
		default:
			break;
		}
		::std::cout << "doesn't support this operator" << ::std::endl;
		exit(0);
		return nullptr;
	}

	::std::shared_ptr<IceObject> IceBooleanObject::binaryOperate(::std::shared_ptr<IceObject> obj, TOKEN op)
	{
		switch (obj->type)
		{
		case TYPE::INT:
			switch (op)
			{
			case TOKEN::TADD:
				return ::std::make_shared<IceIntegerObject>(value + ::std::dynamic_pointer_cast<IceIntegerObject>(obj)->value);
			case TOKEN::TSUB:
				return ::std::make_shared<IceIntegerObject>(value - ::std::dynamic_pointer_cast<IceIntegerObject>(obj)->value);
			case TOKEN::TMUL:
				return ::std::make_shared<IceIntegerObject>(value * ::std::dynamic_pointer_cast<IceIntegerObject>(obj)->value);
			case TOKEN::TDIV:
				return ::std::make_shared<IceIntegerObject>(value / ::std::dynamic_pointer_cast<IceIntegerObject>(obj)->value);
			case TOKEN::TMOD:
				return ::std::make_shared<IceIntegerObject>(value % ::std::dynamic_pointer_cast<IceIntegerObject>(obj)->value);
			case TOKEN::TCEQ:
				return ::std::make_shared<IceBooleanObject>(value == ::std::dynamic_pointer_cast<IceIntegerObject>(obj)->value);
			case TOKEN::TCNE:
				return ::std::make_shared<IceBooleanObject>(value != ::std::dynamic_pointer_cast<IceIntegerObject>(obj)->value);
			case TOKEN::TCLT:
				return ::std::make_shared<IceBooleanObject>(value < ::std::dynamic_pointer_cast<IceIntegerObject>(obj)->value);
			case TOKEN::TCLE:
				return ::std::make_shared<IceBooleanObject>(value <= ::std::dynamic_pointer_cast<IceIntegerObject>(obj)->value);
			case TOKEN::TCGT:
				return ::std::make_shared<IceBooleanObject>(value > ::std::dynamic_pointer_cast<IceIntegerObject>(obj)->value);
			case TOKEN::TCGE:
				return ::std::make_shared<IceBooleanObject>(value >= ::std::dynamic_pointer_cast<IceIntegerObject>(obj)->value);
			default:
				break;
			}
			break;
		case TYPE::DOUBLE:
			switch (op)
			{
			case TOKEN::TADD:
				return ::std::make_shared<IceDoubleObject>(value + ::std::dynamic_pointer_cast<IceDoubleObject>(obj)->value);
			case TOKEN::TSUB:
				return ::std::make_shared<IceDoubleObject>(value - ::std::dynamic_pointer_cast<IceDoubleObject>(obj)->value);
			case TOKEN::TMUL:
				return ::std::make_shared<IceDoubleObject>(value * ::std::dynamic_pointer_cast<IceDoubleObject>(obj)->value);
			case TOKEN::TDIV:
				return ::std::make_shared<IceDoubleObject>(value / ::std::dynamic_pointer_cast<IceDoubleObject>(obj)->value);
			case TOKEN::TMOD:
				return ::std::make_shared<IceDoubleObject>(value % (long)::std::dynamic_pointer_cast<IceDoubleObject>(obj)->value);
			case TOKEN::TCEQ:
				return ::std::make_shared<IceBooleanObject>(value == ::std::dynamic_pointer_cast<IceDoubleObject>(obj)->value);
			case TOKEN::TCNE:
				return ::std::make_shared<IceBooleanObject>(value != ::std::dynamic_pointer_cast<IceDoubleObject>(obj)->value);
			case TOKEN::TCLT:
				return ::std::make_shared<IceBooleanObject>(value < ::std::dynamic_pointer_cast<IceDoubleObject>(obj)->value);
			case TOKEN::TCLE:
				return ::std::make_shared<IceBooleanObject>(value <= ::std::dynamic_pointer_cast<IceDoubleObject>(obj)->value);
			case TOKEN::TCGT:
				return ::std::make_shared<IceBooleanObject>(value > ::std::dynamic_pointer_cast<IceDoubleObject>(obj)->value);
			case TOKEN::TCGE:
				return ::std::make_shared<IceBooleanObject>(value >= ::std::dynamic_pointer_cast<IceDoubleObject>(obj)->value);
			default:
				break;
			}
			break;
		case TYPE::BOOLEAN:
			switch (op)
			{
			case TOKEN::TCEQ:
				return ::std::make_shared<IceBooleanObject>(value == ::std::dynamic_pointer_cast<IceBooleanObject>(obj)->value);
			case TOKEN::TAND:
				return ::std::make_shared<IceBooleanObject>(value && ::std::dynamic_pointer_cast<IceBooleanObject>(obj)->value);
			case TOKEN::TOR:
				return ::std::make_shared<IceBooleanObject>(value || ::std::dynamic_pointer_cast<IceBooleanObject>(obj)->value);
			default:
				break;
			}
		default:
			break;
		}
		::std::cout << "doesn't support this operator" << ::std::endl;
		exit(0);
		return nullptr;
	}


	// Definitions for IceStringObject
	IceStringObject::IceStringObject(::std::string value) : value(value)
	{
		genBuiltInMethods();

		type = TYPE::STRING;

		raw_value = "";
		const char *p = value.c_str();
		while (*p)
		{
			switch (*p)
			{
			case '\n':
				raw_value += "\\n";
				break;
			case '\\':
				raw_value += "\\\\";
				break;
			case '\"':
				raw_value += "\\\"";
				break;
			case '\a':
				raw_value += "\\a";
				break;
			case '\b':
				raw_value += "\\b";
				break;
			case '\0':
				raw_value += "\\0";
				break;
			case '\t':
				raw_value += "\\t";
				break;
			case '\r':
				raw_value += "\\r";
				break;
			case '\f':
				raw_value += "\\f";
				break;
			default:
				raw_value += *p;
				break;
			}
			++p;
		}
	}

	::std::shared_ptr<IceObject> IceStringObject::unaryOperate(TOKEN op)
	{
		::std::string dup = value;
		switch (op)
		{
		case TOKEN::TSUB:
			::std::reverse(dup.begin(), dup.end());
			return ::std::make_shared<IceStringObject>(dup);
		default:
			break;
		}
		::std::cout << "doesn't support this operator" << ::std::endl;
		exit(0);
		return nullptr;
	}

	::std::shared_ptr<IceObject> IceStringObject::binaryOperate(::std::shared_ptr<IceObject> obj, TOKEN op)
	{
		::std::string dup = value;
		switch (obj->type)
		{
		case TYPE::STRING:
			switch (op)
			{
			case TOKEN::TADD:
				return ::std::make_shared<IceStringObject>(value + ::std::dynamic_pointer_cast<IceStringObject>(obj)->value);
			case TOKEN::TCEQ:
				return ::std::make_shared<IceBooleanObject>(value == ::std::dynamic_pointer_cast<IceStringObject>(obj)->value);
			case TOKEN::TCNE:
				return ::std::make_shared<IceBooleanObject>(value != ::std::dynamic_pointer_cast<IceStringObject>(obj)->value);
			default:
				break;
			}
			break;
		case TYPE::INT:
			switch (op)
			{
			case TOKEN::TMUL:
				for (int i = 1; i < ::std::dynamic_pointer_cast<IceIntegerObject>(obj)->value; i++) dup += value;
				return ::std::make_shared<IceStringObject>(dup);
			case TOKEN::TCEQ:
				return ::std::make_shared<IceIntegerObject>(0);
			case TOKEN::TCNE:
				return ::std::make_shared<IceIntegerObject>(1);
			default:
				break;
			}
			break;
		default:
			break;
		}
		::std::cout << "doesn't support this operator" << ::std::endl;
		exit(0);
		return nullptr;
	}

	::std::shared_ptr<IceObject> IceStringObject::getByIndex(::std::shared_ptr<IceObject> _index)
	{
		if (_index->type != TYPE::INT)
		{
			::std::cout << "index type should be integer" << ::std::endl;
			exit(0);
		}
		::std::shared_ptr<IceIntegerObject> index = ::std::dynamic_pointer_cast<IceIntegerObject>(_index);

		if (index->value >= (int)value.size())
		{
			::std::cout << "index out of range" << ::std::endl;
			exit(0);
		}
		::std::string str;
		str += value[index->value];
		::std::shared_ptr<IceStringObject> obj = ::std::make_shared<IceStringObject>(str);
		obj->top->put("self", obj);
		return obj;
	}

	void IceStringObject::genBuiltInMethods()
	{
		top->put("isalpha", ::std::make_shared<IceBuiltInFunctionObject>([&](Objects objects)
		{
			if (objects.size())
			{
				::std::cout << "method isalpha() need no arguments" << ::std::endl;
				exit(0);
			}
			return ::std::dynamic_pointer_cast<IceObject>(::std::make_shared<IceBooleanObject>(value.size() == 1 ? (isalpha(value[0])) : false));
		}));

		top->put("size", ::std::make_shared<IceBuiltInFunctionObject>([&](Objects objects)
		{
			if (objects.size())
			{
				::std::cout << "method size() need no arguments" << ::std::endl;
				exit(0);
			}

			return ::std::dynamic_pointer_cast<IceObject>(::std::make_shared<IceIntegerObject>(value.size()));
		}));
	}


	// Definitions for IceListObject
	IceListObject::IceListObject()
	{
		type = TYPE::LIST;
		genBuiltInMethods();
	}

	IceListObject::IceListObject(Objects objects) : objects(objects)
	{
		type = TYPE::LIST;
		genBuiltInMethods();
	}

	void IceListObject::show()
	{
		::std::cout << "[";
		for (size_t i = 0; i < objects.size(); i++)
		{
			if (i) ::std::cout << ", ";
			objects[i]->show();
		}
		::std::cout << "]";
	}

	::std::shared_ptr<IceObject> IceListObject::unaryOperate(TOKEN op)
	{
		::std::shared_ptr<IceListObject> obj = nullptr;
		switch (op)
		{
		case TOKEN::TSUB:
			obj = ::std::make_shared<IceListObject>();
			for (int i = (int)objects.size() - 1; i >= 0; i--)
			{
				obj->objects.push_back(objects[i]);
			}
			break;
		default:
			break;
		}
		return obj;
	}

	::std::shared_ptr<IceObject> IceListObject::binaryOperate(::std::shared_ptr<IceObject> _obj, TOKEN op)
	{
		if (_obj->type != TYPE::LIST)
		{
			::std::cout << "doesn't support this operator" << ::std::endl;
			exit(0);
		}
		::std::shared_ptr<IceListObject> obj = ::std::dynamic_pointer_cast<IceListObject>(_obj);
		::std::shared_ptr<IceListObject> res_obj = ::std::make_shared<IceListObject>(objects);
		switch (op)
		{
		case TOKEN::TADD:
			for (auto &object : obj->objects)
			{
				res_obj->objects.push_back(object);
			}
			break;
		default:
			break;
		}
		return res_obj;
	}

	::std::shared_ptr<IceObject> IceListObject::getByIndex(::std::shared_ptr<IceObject> _index)
	{
		if (_index->type != TYPE::INT)
		{
			::std::cout << "index type should be integer" << ::std::endl;
			exit(0);
		}
		::std::shared_ptr<IceIntegerObject> index = ::std::dynamic_pointer_cast<IceIntegerObject>(_index);

		if (index->value >= (int)objects.size())
		{
			::std::cout << "index out of range" << ::std::endl;
			exit(0);
		}
		return objects[index->value];
	}

	void IceListObject::setByIndex(::std::shared_ptr<IceObject> _index, ::std::shared_ptr<IceObject> assignment)
	{
		if (_index->type != TYPE::INT)
		{
			::std::cout << "index type should be integer" << ::std::endl;
			exit(0);
		}
		::std::shared_ptr<IceIntegerObject> index = ::std::dynamic_pointer_cast<IceIntegerObject>(_index);

		if (index->value >= (int)objects.size())
		{
			::std::cout << "index out of range" << ::std::endl;
			exit(0);
		}
		objects[index->value] = assignment;
	}

	void IceListObject::genBuiltInMethods()
	{
		top->put("size", ::std::make_shared<IceBuiltInFunctionObject>([&](Objects _objects)
		{
			if (_objects.size())
			{
				::std::cout << "method size() need no arguments" << ::std::endl;
				exit(0);
			}

			return ::std::dynamic_pointer_cast<IceObject>(::std::make_shared<IceIntegerObject>(objects.size()));
		}));

		top->put("empty", ::std::make_shared<IceBuiltInFunctionObject>([&](Objects _objects)
		{
			if (_objects.size())
			{
				::std::cout << "method empty() need no arguments" << ::std::endl;
				exit(0);
			}

			return ::std::dynamic_pointer_cast<IceObject>(::std::make_shared<IceBooleanObject>(objects.empty()));
		}));

		top->put("push_back", ::std::make_shared<IceBuiltInFunctionObject>([&](Objects _objects)
		{
			if (_objects.size() != 1)
			{
				::std::cout << "method push_back() need 1 argument but get others" << ::std::endl;
				exit(0);
			}

			objects.push_back(_objects[0]);
			return ::std::dynamic_pointer_cast<IceObject>(::std::make_shared<IceNoneObject>());
		}));

		top->put("pop_back", ::std::make_shared<IceBuiltInFunctionObject>([&](Objects _objects)
		{
			if (_objects.size())
			{
				::std::cout << "method pop_back() need no arguments" << ::std::endl;
				exit(0);
			}

			objects.pop_back();
			return ::std::dynamic_pointer_cast<IceObject>(::std::make_shared<IceNoneObject>());
		}));

		top->put("front", ::std::make_shared<IceBuiltInFunctionObject>([&](Objects _objects)
		{
			if (_objects.size())
			{
				::std::cout << "method front() need no arguments" << ::std::endl;
				exit(0);
			}

			return objects.front();
		}));

		top->put("back", ::std::make_shared<IceBuiltInFunctionObject>([&](Objects _objects)
		{
			if (_objects.size())
			{
				::std::cout << "method back() need no arguments" << ::std::endl;
				exit(0);
			}

			return objects.back();
		}));

		top->put("clear", ::std::make_shared<IceBuiltInFunctionObject>([&](Objects _objects)
		{
			if (_objects.size())
			{
				::std::cout << "method clear() need no arguments" << ::std::endl;
				exit(0);
			}

			objects.clear();
			return ::std::dynamic_pointer_cast<IceObject>(::std::make_shared<IceNoneObject>());
		}));
	}


	// Definitions for IceDictObject
	IceDictObject::IceDictObject()
	{
		type = TYPE::DICT;
		genBuiltInMethods();
	}

	size_t _KeyObject::hashValue() const
	{
		switch (obj->type)
		{
		case IceObject::TYPE::INT:
			return ::std::hash<long>{}(::std::dynamic_pointer_cast<IceIntegerObject>(obj)->value);
		case IceObject::TYPE::DOUBLE:
			return ::std::hash<double>{}(::std::dynamic_pointer_cast<IceDoubleObject>(obj)->value);
		case IceObject::TYPE::BOOLEAN:
			return ::std::hash<bool>{}(::std::dynamic_pointer_cast<IceBooleanObject>(obj)->value);
		case IceObject::TYPE::STRING:
			return ::std::hash<::std::string>{}(::std::dynamic_pointer_cast<IceStringObject>(obj)->value);
		default:
			break;
		}
		::std::cout << "key for dict should be int, double, boolean or ::std::string" << ::std::endl;
		exit(0);
		return 0;
	}

	void IceDictObject::show()
	{
		::std::cout << "{";
		for (auto iter = objects_map.begin(); iter != objects_map.end(); iter++)
		{
			if (iter != objects_map.begin())
			{
				::std::cout << ", ";
			}
			iter->first.obj->show();
			::std::cout << ": ";
			iter->second->show();
		}
		::std::cout << "}";
	}

	::std::shared_ptr<IceObject> IceDictObject::getByIndex(::std::shared_ptr<IceObject> _key)
	{
        _KeyObject key(_key);
		if (objects_map.find(key) != objects_map.end())
		{
			return objects_map[key];
		}
		else
		{
			return ::std::make_shared<IceNoneObject>();
		}
	}

	void IceDictObject::setByIndex(::std::shared_ptr<IceObject> key, ::std::shared_ptr<IceObject> value)
	{
		objects_map[_KeyObject(key)] = value;
	}

	void IceDictObject::genBuiltInMethods()
	{
		top->put("at", ::std::make_shared<IceBuiltInFunctionObject>([&](Objects objects) 
		{
			if (objects.size() != 1)
			{
				::std::cout << "method at() need one argument" << ::std::endl;
				exit(0);
			}

			return getByIndex(objects[0]);
		}));

		top->put("empty", ::std::make_shared<IceBuiltInFunctionObject>([&](Objects objects)
		{
			if (objects.size())
			{
				::std::cout << "method empty() need no arguments" << ::std::endl;
				exit(0);
			}

			return ::std::dynamic_pointer_cast<IceObject>(::std::make_shared<IceBooleanObject>(objects_map.empty()));
		}));

		top->put("size", ::std::make_shared<IceBuiltInFunctionObject>([&](Objects objects)
		{
			if (objects.size())
			{
				::std::cout << "method size() need no arguments" << ::std::endl;
				exit(0);
			}

			return ::std::dynamic_pointer_cast<IceObject>(::std::make_shared<IceIntegerObject>(objects_map.size()));
		}));

		top->put("clear", ::std::make_shared<IceBuiltInFunctionObject>([&](Objects objects) 
		{
			if (objects.size())
			{
				::std::cout << "method clear() need no arguments" << ::std::endl;
				exit(0);
			}

			objects_map.clear();
			return ::std::dynamic_pointer_cast<IceObject>(::std::make_shared<IceNoneObject>());
		}));

		top->put("insert", ::std::make_shared<IceBuiltInFunctionObject>([&](Objects objects)
		{
			if (objects.size() != 2)
			{
				::std::cout << "method insert() need 2 arguments" << ::std::endl;
				exit(0);
			}

			setByIndex(objects[0], objects[1]);
			return ::std::dynamic_pointer_cast<IceObject>(::std::make_shared<IceNoneObject>());
		}));

		top->put("erase", ::std::make_shared<IceBuiltInFunctionObject>([&](Objects objects) 
		{
			if (objects.size() != 1)
			{
				::std::cout << "method erase() need 1 argument" << ::std::endl;
				exit(0);
			}

			objects_map.erase(_KeyObject(objects[0]));
			return ::std::dynamic_pointer_cast<IceObject>(::std::make_shared<IceNoneObject>());
		}));
	}
}

