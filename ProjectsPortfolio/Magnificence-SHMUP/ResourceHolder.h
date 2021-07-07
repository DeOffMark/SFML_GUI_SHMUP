#pragma once
#include <map>
#include <string>
#include <memory>
#include <stdexcept>
#include <cassert>


template <typename Resource>
class ResourceHolder
{
public:
	void load(std::string id, const std::string& filename);

	template <typename Parameter>
	void load(std::string id, const std::string& filename, const Parameter& secondParam);

	Resource& get(std::string id);
	const Resource& get(std::string id) const;


private:
	void insertResource(std::string id, std::unique_ptr<Resource> resource);


private:
	std::map<std::string, std::unique_ptr<Resource>>	mResourceMap;
};


#include "ResourceHolder.inl"