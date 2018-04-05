#include"util/lf_name_value_collection.h"
namespace LF
{
	std::string lf_name_value_collection::DEFAULT_VALUE = "default value!";
	lf_name_value_collection::lf_name_value_collection()
	{
	}


	lf_name_value_collection::lf_name_value_collection(const lf_name_value_collection& nvc) :
		_map(nvc._map)
	{
	}


	lf_name_value_collection::~lf_name_value_collection()
	{
	}


	lf_name_value_collection& lf_name_value_collection::operator = (const lf_name_value_collection& nvc)
	{
		if (&nvc != this)
		{
			_map = nvc._map;
		}
		return *this;
	}


	void lf_name_value_collection::swap(lf_name_value_collection& nvc)
	{
		std::swap(_map, nvc._map);
	}


	std::string lf_name_value_collection::operator [] (const std::string& name) const
	{
		ConstIterator it = _map.find(name);
		if (it != _map.end())
			return it->second;
		else
			return DEFAULT_VALUE;
	}


	void lf_name_value_collection::set(const std::string& name, const std::string& value)
	{
		Iterator it = _map.find(name);
		if (it != _map.end())
			it->second = value;
	}


	void lf_name_value_collection::add(const std::string& name, const std::string& value)
	{
		_map.insert(std::make_pair(name, value));
	}


	std::string lf_name_value_collection::get(const std::string& name) const
	{
		ConstIterator it = _map.find(name);
		if (it != _map.end())
			return it->second;
		else
			return DEFAULT_VALUE;
	}


	const std::string& lf_name_value_collection::get(const std::string& name, const std::string& defaultValue) const
	{
		ConstIterator it = _map.find(name);
		if (it != _map.end())
			return it->second;
		else
			return defaultValue;
	}


	bool lf_name_value_collection::has(const std::string& name) const
	{
		return _map.find(name) != _map.end();
	}


	lf_name_value_collection::ConstIterator lf_name_value_collection::find(const std::string& name) const
	{
		return _map.find(name);
	}


	lf_name_value_collection::ConstIterator lf_name_value_collection::begin() const
	{
		return _map.begin();
	}


	lf_name_value_collection::ConstIterator lf_name_value_collection::end() const
	{
		return _map.end();
	}


	bool lf_name_value_collection::empty() const
	{
		return _map.empty();
	}


	std::size_t lf_name_value_collection::size() const
	{
		return _map.size();
	}


	void lf_name_value_collection::erase(const std::string& name)
	{
		_map.erase(name);
	}


	void lf_name_value_collection::clear()
	{
		_map.clear();
	}

}