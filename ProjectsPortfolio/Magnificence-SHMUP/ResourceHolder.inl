template <typename Resource>
void ResourceHolder<Resource>::load(std::string id, const std::string& filename)
{
	auto found = mResourceMap.find(id);
	if (found == mResourceMap.end()) {
		// Create and load resource
		std::unique_ptr<Resource> resource(new Resource());
		if (!resource->loadFromFile(filename))
			throw std::runtime_error("ResourceHolder::load - Failed to load " + filename);

		// If loading successful, insert resource to map
		insertResource(id, std::move(resource));
	}
}

template <typename Resource>
template <typename Parameter>
void ResourceHolder<Resource>::load(std::string id, const std::string& filename, const Parameter& secondParam)
{
	// Create and load resource
	std::unique_ptr<Resource> resource(new Resource());
	if (!resource->loadFromFile(filename, secondParam))
		throw std::runtime_error("ResourceHolder::load - Failed to load " + filename);

	// If loading successful, insert resource to map
	insertResource(id, std::move(resource));
}

template <typename Resource>
Resource& ResourceHolder<Resource>::get(std::string id)
{
	auto found = mResourceMap.find(id);
	assert(found != mResourceMap.end());

	return *found->second;
}

template <typename Resource>
const Resource& ResourceHolder<Resource>::get(std::string id) const
{
	auto found = mResourceMap.find(id);
	assert(found != mResourceMap.end());

	return *found->second;
}

template <typename Resource>
void ResourceHolder<Resource>::insertResource(std::string id, std::unique_ptr<Resource> resource)
{
	// Insert and check success
	auto inserted = mResourceMap.insert(std::make_pair(id, std::move(resource)));
	assert(inserted.second);
}