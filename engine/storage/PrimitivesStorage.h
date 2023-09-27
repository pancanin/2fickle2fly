#ifndef ENGINEV2_COMPONENTS_PRIMITIVESCOMPONENT_H_
#define ENGINEV2_COMPONENTS_PRIMITIVESCOMPONENT_H_

#include <cstdint>
#include <vector>
#include <cstdint>
#include <stdexcept>

template <typename T, typename ID = uint64_t>
class PrimitivesStorage {
public:
	void init(uint16_t maxElements = 16) {
		data.reserve(maxElements);
	}

	T& add(const T& el) {
		data.push_back(el);
		return data[data.size() - 1];
	}

	/// <summary>
	/// Returns a reference to the T in storage.
	/// Storage is the 'home' for T and it manages T's lifecycle.
	/// </summary>
	/// <param name="id">Obtained when creating a T.</param>
	/// <returns>A reference/handle to T. The reference is typically used to change T's state.</returns>
	T& get(ID id) {
		for (int32_t i = 0; i < data.size(); i++) {
			if (data[i].getId() == id) {
				return data[i];
			}
		}
		throw std::logic_error("Attempting to get an element from PrimitivesStorage that does not exist. This signals programming error be prevented in the caller's code.");
	}

	void remove(ID id) {
		for (auto it = data.begin(); it != data.end();) {
			if (it->getId() == id) {
				it = data.erase(it);
			}
			else {
				it++;
			}
		}
	}

	std::vector<T>& elements() {
		return data;
	}
protected:
	std::vector<T> data;
};

#endif /* ENGINEV2_COMPONENTS_PRIMITIVESCOMPONENT_H_ */
